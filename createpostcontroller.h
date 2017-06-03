#ifndef CREATEPOSTCONTROLLER_H
#define CREATEPOSTCONTROLLER_H
#include "httprequesthandler.h"

using namespace QtWebApp;

class CreatePostController: public HttpRequestHandler
{
	Q_OBJECT
public:
	CreatePostController(QObject* parent = 0);
	void service(HttpRequest& request, HttpResponse& response);

};

#endif // CREATEPOSTCONTROLLER_H
