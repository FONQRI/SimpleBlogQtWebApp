#include "aboutuscontroller.h"
#include "requestmanager.h"
#include "template.h"
AboutUsController::AboutUsController(QObject *parent)
	: HttpRequestHandler(parent)
{
}

void AboutUsController::service(HttpRequest &request, HttpResponse &response)
{
	HttpSession session =
		RequestManager::sessionStore->getSession(request, response, true);
	QString username = session.get("username").toString();
	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));

	Template content =
		RequestManager::templateCache->getTemplate("about", language);

	response.write(content.toUtf8(), true);
}
