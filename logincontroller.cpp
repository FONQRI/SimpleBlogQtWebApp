#include "logincontroller.h"
#include <QTime>
#include "requestmanager.h"
LoginController::LoginController(QObject *parent) : HttpRequestHandler(parent)
{
    // empty
}

void LoginController::service(HttpRequest &request, HttpResponse &response)
{
    HttpSession session =
        RequestManager::sessionStore->getSession(request, response, true);

    QByteArray username = request.getParameter("username");
    QByteArray password = request.getParameter("password");

    qDebug("username=%s", username.constData());
    qDebug("password=%s", password.constData());

	if (username == "test" and password == "hello")
	{
		session.set("username", username);
		session.set("logintime", QTime::currentTime());
		response.redirect("/create");
		return;
	}
	else if (!username.isEmpty())
	{
		session.set("username", "false");
	}

	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));

	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template top = RequestManager::templateCache->getTemplate("top", language);
	response.write(top.toUtf8());
	Template content =
		RequestManager::templateCache->getTemplate("loginPage", language);
	content.setCondition("false",
						 session.get("username") == "false" ? true : false);
	response.write(content.toUtf8());
	Template down =
		RequestManager::templateCache->getTemplate("down", language);
	response.write(down.toUtf8(), true);
}
