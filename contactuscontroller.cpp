#include "contactuscontroller.h"
#include "requestmanager.h"
#include "template.h"
ContactUsController::ContactUsController(QObject *parent)
	: HttpRequestHandler(parent)
{
}

void ContactUsController::service(HttpRequest &request, HttpResponse &response)
{
	HttpSession session =
		RequestManager::sessionStore->getSession(request, response, true);
	QString username = session.get("username").toString();
	QByteArray language = request.getHeader("Accept-Language");
	qDebug("language=%s", qPrintable(language));

	Template content =
		RequestManager::templateCache->getTemplate("contact", language);

	response.write(content.toUtf8(), true);
}
