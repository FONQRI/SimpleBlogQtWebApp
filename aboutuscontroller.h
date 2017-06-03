#ifndef ABOUTUSCONTROLLER_H
#define ABOUTUSCONTROLLER_H

#include "httprequesthandler.h"

using namespace QtWebApp;

class AboutUsController : public HttpRequestHandler
{
	Q_OBJECT
public:
	AboutUsController(QObject* parent = 0);
	void service(HttpRequest& request, HttpResponse& response);
};

#endif  // ABOUTUSCONTROLLER_H
