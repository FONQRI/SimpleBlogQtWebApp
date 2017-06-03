#ifndef ERROR404_H
#define ERROR404_H
#include "httprequesthandler.h"

using namespace QtWebApp;

class Error404 : public HttpRequestHandler
{
	Q_OBJECT
public:
	Error404(QObject* parent = 0);
	void service(HttpRequest& request, HttpResponse& response);
};

#endif  // ERROR404_H
