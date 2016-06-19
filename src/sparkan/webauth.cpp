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
    if (reply->error() == QNetworkReply::NoError) {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        switch (statusCode) {
            case 301:
            case 302:
            case 307:
            QUrl url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            QRegularExpression rx("localhost.*[&?]code=(.+?)[&^$]");
            QRegularExpressionMatch match = rx.match(url.toString());
            if (match.hasMatch())
            {
                view->stop();
                widget->hide();

                qWarning() << "Captured: " << match.captured(1);
                QNetworkRequest *request = new QNetworkRequest(QUrl("https://api.ciscospark.com/v1/access_token"));
                request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
                request->setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
                QNetworkAccessManager *nm = new QNetworkAccessManager();
                QString postData = "grant_type=authorization_code&"
                                   "client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca&"
                                   "client_secret=5a1b187745e79a6cb2fe6b005a3b3be16b633411374eacb84a38c3c4068fbf50&"
                                   "code=" + match.captured(1) + "&redirect_uri=http://localhost";

                qWarning() << " Auth url: " << postData;
                connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(nm_Token(QNetworkReply*)));
                //view->load(*request, QNetworkAccessManager::PostOperation, postData.toUtf8());
                nm->post(*request, postData.toUtf8());
            }
                break;
        }
    }
}

void WebAuth::nm_Token(QNetworkReply *reply)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    if (jdoc.isArray()) qWarning() << "Json is Array";
    if (jdoc.isObject()) qWarning() << "Json is Object";
    if (jdoc.isEmpty()) qWarning() << "Json is Empty";
    if (jdoc.isNull()) qWarning() << "Json is NULL";
    QJsonObject json = jdoc.object();
    qWarning() << "access_token" << json.value("access_token").toString();
}
