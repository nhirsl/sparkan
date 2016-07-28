#include <cstdlib>
#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>
#include "mainwindow.h"
#include <QMessageLogger>
#include <iostream>
#include "cachedauthorization.h"
#include <QtDebug>
#include "people.h"
#include "webauth.h"
#include <QtNetwork/QNetworkProxy>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "coreservice.h"
#include "webbrowser.h"
#include "authlistener.h"
#include <QThread>





static std::string clientSecret = "5a1b187745e79a6cb2fe6b005a3b3be16b633411374eacb84a38c3c4068fbf50";
static std::string clientId = "Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca";

WebAuth *wauth;

void test()
{
    wauth = new WebAuth;
    wauth->GetAuth();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main thread");

    CoreService* core = CoreService::getInstance();
    WebBrowser browser;
    core->setBrowser(&browser);
    //AuthListener auth;
    //auth.setCore(core);
    //auth.getOAuth();
    QQmlApplicationEngine engine;
    auto root_context = engine.rootContext();
    root_context->setContextProperty("myBrowser", &browser);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    browser.setUrl(QUrl("https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here"));

 /*   KLocalizedString::setApplicationDomain("sparkan");

    KAboutData aboutData(
                // The program name used internally. (componentName)
                QStringLiteral("sparkan"),
                // A displayable program name string. (displayName)
                i18n("SparKan"),
                // The program version string. (version)
                QStringLiteral("1.0"),
                // Short description of what the app does. (shortDescription)
                i18n("Spark for K"),
                // The license this code is released under
                KAboutLicense::GPL_V3,
                // Copyright Statement (copyrightStatement = QString())
                i18n("(c) 2016"),
                // Optional text shown in the About box.
                // Can contain any information desired. (otherText)
                i18n("Unofficial Linux client for Cisco Spark"),
                // The program homepage string. (homePageAddress = QString())
                QStringLiteral("https://github.com/nhirsl/sparkan"),
                // The bug report email address
                // (bugsEmailAddress = QLatin1String("submit@bugs.kde.org")
                QStringLiteral("sparkan@googlegroups.com"));
    aboutData.addAuthor(i18n("Veljko Jasikovac"), i18n("Developer"), QStringLiteral("veljko.jasikovac@gmail.com"),
                        QStringLiteral(""), QStringLiteral("veljko.jasikovac"));
    aboutData.addAuthor(i18n("Nebojsa Karan"), i18n("Developer"), QStringLiteral("nebojsakaran1011@gmail.com"),
                        QStringLiteral(""), QStringLiteral("nebojsa1011"));
    aboutData.addAuthor(i18n("Nemanja Hiršl"), i18n("Development Lead"), QStringLiteral("nemhirsl@gmail.com"),
                        QStringLiteral("http://alas.matf.bg.ac.rs/~mr97352/"), QStringLiteral("nhirsl"));
    aboutData.addAuthor(i18n("Nenad Žikić"), i18n("Developer"), QStringLiteral("nenad.zikic@gmail.com"),
                        QStringLiteral(""), QStringLiteral("nzikic"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow* window = new MainWindow();
    window->show();
*/

return app.exec();
}

