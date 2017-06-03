#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include "aboutuscontroller.h"
#include "contactuscontroller.h"
#include "createpostcontroller.h"
#include "error404.h"
#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "logger.h"
#include "logincontroller.h"
#include "mainpagecontroller.h"
#include "staticfilecontroller.h"
#include "templatecache.h"

using namespace QtWebApp;

class RequestManager : public HttpRequestHandler
{
    Q_OBJECT

public:
    RequestManager(QObject* parent = 0);
    void service(HttpRequest& request, HttpResponse& response);
    static HttpSessionStore* sessionStore;
    static StaticFileController* staticFileController;
    static TemplateCache* templateCache;
    static Logger* logger;

private:
	CreatePostController createPostController;
    LoginController loginController;
	MainPageController mainPageController;
	Error404 error404;
	ContactUsController contactUsController;
	AboutUsController aboutUsController;
};
#endif  // REQUESTMANAGER_H
