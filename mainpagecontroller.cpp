#include "mainpagecontroller.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "requestmanager.h"
#include "template.h"
MainPageController::MainPageController(QObject *parent)
	: HttpRequestHandler(parent)
{
}

void MainPageController::service(HttpRequest &request, HttpResponse &response)
{
	HttpSession session =
		RequestManager::sessionStore->getSession(request, response, true);
	QString username = session.get("username").toString();
	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("database.db");
	db.setUserName("test");
	db.setPassword("hello");

	if (!db.open("test", "hello")) qDebug() << "database error";

	QSqlQuery query;
	query.exec(" select count(*) from postList;");
	query.first();
	size_t lastId = query.value(0).toInt();
	query.exec("SELECT * From postList");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template content =
		RequestManager::templateCache->getTemplate("mainPage", language);
	content.loop("blogPost", lastId);
	for (size_t i = 0; i < lastId; i++)
	{
		QString number = QString::number(i);
		query.next();
		content.setVariable("blogPost" + number + ".title",
							query.value(1).toString());
		content.setVariable("blogPost" + number + ".contentPost",
							query.value(2).toString());
		content.setVariable("blogPost" + number + ".author",
							query.value(3).toString());
		content.setVariable("blogPost" + number + ".date",
							query.value(4).toString());
	}

	response.write(content.toUtf8(), true);

	db.close();
}
