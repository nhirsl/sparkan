#include <cstdlib>
#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>
#include <QMessageLogger>
#include <iostream>
#include "cachedauthorization.h"
#include <QtDebug>
#include "people.h"
#include <QtNetwork/QNetworkProxy>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "coreservice.h"
#include "webbrowser.h"
#include "authlistener.h"
#include <QThread>
#include <QProcessEnvironment>

#include <QRegularExpression>
#include <QRegularExpressionMatch>





static std::string clientSecret = "5a1b187745e79a6cb2fe6b005a3b3be16b633411374eacb84a38c3c4068fbf50";
static std::string clientId = "Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca";



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main thread");
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString proxy = env.value("https_proxy");

    if (!proxy.trimmed().isEmpty())
    {
        std::cout << "proxy: " << proxy.toStdString() << std::endl << std::flush;
        QRegularExpression rx(R"(https?:\/\/(.*):(\d.*)\/?)");
        QRegularExpressionMatch match = rx.match(proxy);
        if (match.lastCapturedIndex() == 2)
        {
            std::cout << "hostname: " << match.captured(1).toStdString() << "; port: " << match.captured(2).toStdString() << ";" << std::endl << std::flush;
            QNetworkProxy proxy;
            proxy.setType(QNetworkProxy::HttpProxy);
            proxy.setHostName(match.captured(1));
            proxy.setPort(match.captured(2).toInt());
         // proxy.setUser("username");
         // proxy.setPassword("password");
            QNetworkProxy::setApplicationProxy(proxy);
        }
    }

    QQmlApplicationEngine engine;
    auto root_context = engine.rootContext();

    WebBrowser browser;
    Person me;
    AuthListener authlistener;
    authlistener.setMe(&me);

    root_context->setContextProperty("myBrowser", &browser);
    root_context->setContextProperty("Me", &me);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    CoreService* core = CoreService::getInstance();
    core->setBrowser(&browser);
    core->addOAuthListener(&authlistener);
    QString oauth = core->getAuthToken();
    if (!oauth.isEmpty()) authlistener.onNewAccessToken(oauth);

return app.exec();
}

