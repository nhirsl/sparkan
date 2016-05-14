#include <cstdlib>
#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>
#include "mainwindow.h"

static std::string clientSecret = "5a1b187745e79a6cb2fe6b005a3b3be16b633411374eacb84a38c3c4068fbf50";
static std::string clientId = "Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca";
static std::string oauthAuthorizationUrl = "https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca"
                                           "&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3"
                                           "Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("sparkan");

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
    aboutData.addAuthor(i18n("Nemanja Hiršl"), i18n("Development Lead"), QStringLiteral("nemhirsl@gmail.com"),
                        QStringLiteral("http://alas.matf.bg.ac.rs/~mr97352/"), QStringLiteral("nhirsl"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow* window = new MainWindow();
    window->show();

    return app.exec();
}
