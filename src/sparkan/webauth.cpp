#include "webauth.h"
#include <iostream>
#include <QDebug>
//#include <QVBoxLayout>

static std::string oauthAuthorizationUrl = "https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca"
                                           "&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3"
                                           "Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here";

WebAuth::WebAuth() {}

void WebAuth::GetAuth()
{
    QWidget *widget = new QWidget(NULL);
    //QVBoxLayout *layout = new QVBoxLayout(widget);
    view = new QWebView(widget);
    page = view->page();
    frame = page->currentFrame();
    //layout->addWidget(view);
    widget->setWindowState(Qt::WindowMaximized);
    widget->show();

    connect(view, SIGNAL(urlChanged(QUrl)),     this, SLOT(on_ulrChanged(QUrl)));
    //connect(view, SIGNAL(loadStarted()),        this, SLOT(on_loadStarted()));
    //connect(view, SIGNAL(loadFinished(bool)),   this, SLOT(on_loadFinished(bool)));
    //connect(view, SIGNAL(loadProgress(int)),    this, SLOT(on_loadProgress(int)));
    //connect(view, SIGNAL(linkClicked(QUrl)),    this, SLOT(on_linkClicked(QUrl)));

    QUrl url (oauthAuthorizationUrl.c_str());


    view->load(url);
}


void WebAuth::on_ulrChanged(QUrl url)
{
    qWarning() << "Url Changed: " << url << "\n";
    QRegExp rx("[&?]code=(.*?&)");
    if (rx.indexIn(url.toString()) != -1)
        qWarning() << rx.cap();
}

void WebAuth::on_loadStarted()
{
    qWarning() << "loadStarted: ";
}

void WebAuth::on_loadFinished(bool ok)
{
    qWarning() << "loadFinished: ";
}

void WebAuth::on_loadProgress(int progress)
{
    qWarning() << "loadProgress: ";
}

void WebAuth::on_linkClicked(QUrl url)
{
    qWarning() << "linkClicked: " << url.toString();
}
