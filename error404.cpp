#include "error404.h"
#include <iostream>
#include "requestmanager.h"
#include "template.h"
Error404::Error404(QObject *parent) : HttpRequestHandler(parent) {}
void Error404::service(HttpRequest &request, HttpResponse &response)
{
	std::clog << std::endl << "404" << std::endl;
	HttpSession session =
		RequestManager::sessionStore->getSession(request, response, true);
	QString username = session.get("username").toString();
	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));
	response.setStatus(404, "Not found");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template top = RequestManager::templateCache->getTemplate("top", language);
	response.write(top.toUtf8());
	Template content =
		RequestManager::templateCache->getTemplate("404", language);
	response.write(content.toUtf8());
	Template down =
		RequestManager::templateCache->getTemplate("down", language);
	response.write(down.toUtf8(), true);
}
