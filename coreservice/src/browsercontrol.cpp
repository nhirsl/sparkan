#include "browsercontrol.h"

std::string BrowserControl::oauthAuthorizationUrl = "https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca"
                                             "&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3"
                                             "Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here";

BrowserControl::BrowserControl(QObject *parent)
  : QObject(parent),
  m_browser(NULL)
{

}

void BrowserControl::setBrowser(Browser* browser)
{
    if (m_browser != NULL)
    {
        //TODO: Implementin disconect;
    }
    m_browser = browser;
    connect(this, SIGNAL(load(QUrl)), m_browser, SLOT(load(QUrl)));
}

void BrowserControl::startLogin()
{
    emit load(QUrl(oauthAuthorizationUrl.c_str()));
}
