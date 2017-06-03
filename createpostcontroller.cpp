#include "createpostcontroller.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "requestmanager.h"
#include "template.h"
CreatePostController::CreatePostController(QObject *parent)
	: HttpRequestHandler(parent)
{
}

void CreatePostController::service(HttpRequest &request, HttpResponse &response)
{
	HttpSession session =
		RequestManager::sessionStore->getSession(request, response, true);
	QString username = session.get("username").toString();
	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));
	if (username != "test")
	{
		qDebug("RequestMapper: redirect to login page");
		response.redirect("/login");
		return;
	}

	if (request.getParameter("editor1") != nullptr)
	{
		QSqlDatabase db;
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName("database.db");
		db.setUserName("test");
		db.setPassword("hello");

		if (!db.open("test", "hello")) qDebug() << "database error";

		QSqlQuery query;
		// int lastId = query.exec(" SELECT max(id) FROM postList");
		query.prepare(
			"insert into  postList(title "
			",content ,author "
			",date ) values(:title ,:content ,:author "
			",:date );");
		// query.bindValue(":id", lastId + 1);
		query.bindValue(":title", request.getParameter("title"));
		query.bindValue(":content", request.getParameter("editor1"));
		query.bindValue(":author", username);
		query.bindValue(":date", QDateTime::currentDateTime().toString());
		query.exec();
		db.commit();
		db.close();
	}

	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template content =
		RequestManager::templateCache->getTemplate("createPost", language);

	response.write(content.toUtf8());
	Template down =
		RequestManager::templateCache->getTemplate("down", language);
	response.write(down.toUtf8(), true);
}
