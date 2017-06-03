#ifndef CONTACTUSCONTROLLER_H
#define CONTACTUSCONTROLLER_H
#include "httprequesthandler.h"

using namespace QtWebApp;

class ContactUsController : public HttpRequestHandler
{
	Q_OBJECT
public:
	ContactUsController(QObject* parent = 0);
	void service(HttpRequest& request, HttpResponse& response);
};

#endif  // CONTACTUSCONTROLLER_H
