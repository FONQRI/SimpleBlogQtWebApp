#ifndef MAINPAGECONTROLLER_H
#define MAINPAGECONTROLLER_H
#include "httprequesthandler.h"

using namespace QtWebApp;

class MainPageController: public HttpRequestHandler
{
	Q_OBJECT
public:
	MainPageController(QObject* parent = 0);
	void service(HttpRequest& request, HttpResponse& response);

};

#endif // MAINPAGECONTROLLER_H
