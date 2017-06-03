#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QtSql>
#include <iostream>
#include "filelogger.h"
#include "httplistener.h"
#include "httpsessionstore.h"
#include "requestmanager.h"
/**
 * Search the configuration file.
 * Aborts the application if not found.
 * @return The valid filename
 */

using namespace QtWebApp;
QString searchConfigFile()
{
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QFile file;
    file.setFileName(binDir + "/webApp.ini");
    if (!file.exists())
    {
        file.setFileName(binDir + "/etc/webApp.ini");
        if (!file.exists())
        {
            file.setFileName(binDir + "/../etc/webApp.ini");
            if (!file.exists())
            {
                file.setFileName(binDir + "/../" + appName + "/etc/webApp.ini");
                if (!file.exists())
                {
                    file.setFileName(binDir + "/../../" + appName +
                                     "/etc/webApp.ini");
                    if (!file.exists())
                    {
                        file.setFileName(binDir + "/../../../../../" + appName +
                                         "/etc/webApp.ini");
                        if (!file.exists())
                        {
                            file.setFileName(QDir::rootPath() +
                                             "etc/webApp.ini");
                        }
                    }
                }
            }
        }
    }
    if (file.exists())
    {
        QString configFileName = QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else
    {
        qFatal("config file not found");
    }
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("database.db");
	db.setUserName("test");
	db.setPassword("hello");

	//	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	//		db.setHostName("bigblue");
	//		db.setDatabaseName("database.db");
	//		db.setUserName("test");
	//		db.setPassword("hello");

	if (!db.open("test", "hello")) qDebug() << "database error";

	QSqlQuery query;

	query.exec("select * from postList");
	query.next();
	if (!query.isValid())
	{
		query.exec(
			"create table postList(id INTEGER PRIMARY KEY   "
			"AUTOINCREMENT,title "
			"text,content text,author "
			"text,date text);");
		std::clog << query.lastError().text().toStdString() << std::endl;
	}
	db.close();
    // Load the configuration file
    QString configFileName = searchConfigFile();
    QSettings* listenerSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");

    // Configure logging
    QSettings* logSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    logSettings->beginGroup("logging");
    RequestManager::logger = new FileLogger(logSettings, 10000, &app);
    RequestManager::logger->installMsgHandler();

    // Log the library version
    qDebug("QtWebApp has version %s", getQtWebAppLibVersion());

    // Session store
    QSettings* sessionSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    sessionSettings->beginGroup("sessions");
    RequestManager::sessionStore = new HttpSessionStore(sessionSettings, &app);

    // Static file controller
    QSettings* fileSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    fileSettings->beginGroup("files");
    RequestManager::staticFileController =
        new StaticFileController(fileSettings, &app);

    // Configure template cache
    QSettings* templateSettings =
        new QSettings(configFileName, QSettings::IniFormat, &app);
    templateSettings->beginGroup("templates");
    RequestManager::templateCache = new TemplateCache(templateSettings, &app);

    // Http server
    new HttpListener(listenerSettings, new RequestManager(&app), &app);
    return app.exec();
}
