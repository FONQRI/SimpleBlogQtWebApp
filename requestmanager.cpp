#include "requestmanager.h"
#include <iostream>
HttpSessionStore* RequestManager::sessionStore = 0;
StaticFileController* RequestManager::staticFileController = 0;
TemplateCache* RequestManager::templateCache = 0;
Logger* RequestManager::logger = 0;

RequestManager::RequestManager(QObject* parent) : HttpRequestHandler(parent) {}
void RequestManager::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path = request.getPath();
	std::clog << std::endl
			  << ("RequestMapper: path=%s", path.data()) << std::endl;
    HttpSession session = sessionStore->getSession(request, response, false);
    QString username = session.get("username").toString();
    logger->set("currentUser", username);

    QByteArray sessionId = sessionStore->getSessionId(request, response);
	//        if (sessionId.isEmpty() && path != "/login")
	//        {
	//            qDebug("RequestMapper: redirect to login page");
	//            response.redirect("/login");
	//            return;
	//        }

	if (path == "/")
    {
		mainPageController.service(request, response);
    }
	else if (path == "/create")
	{
		createPostController.service(request, response);
    }
    else if (path == "/login")
    {
        loginController.service(request, response);
    }
	else if (path == "/contactus")
	{
		contactUsController.service(request, response);
	}
	else if (path == "/aboutus")
	{
		aboutUsController.service(request, response);
	}
    else if (path.startsWith("/files"))
    {
        staticFileController->service(request, response);
    }
    else
    {
		error404.service(request, response);
    }

    qDebug("RequestMapper: finished request");
    logger->clear(true, true);
}
