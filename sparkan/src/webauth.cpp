#include "webauth.h"
#include <iostream>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <cachedauthorization.h>

static std::string oauthAuthorizationUrl = "https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca"
                                           "&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3"
                                           "Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here";



WebAuth::WebAuth() {}

void WebAuth::GetAuth()
{

    widget = new QWidget(NULL);
    //QVBoxLayout *layout = new QVBoxLayout(widget);
    view = new QWebView(widget);
    page = view->page();
    frame = page->currentFrame();
    //layout->addWidget(view);
    widget->setWindowState(Qt::WindowMaximized);
    widget->show();

    connect(view->page()->networkAccessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(nm_Redirect(QNetworkReply*)));

    QUrl url (oauthAuthorizationUrl.c_str());


    view->load(url);
}


void WebAuth::nm_Redirect(QNetworkReply *reply){

}

void WebAuth::nm_Token(QNetworkReply *reply)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jdoc.object();
    QString auth = json.value("access_token").toString();


}
