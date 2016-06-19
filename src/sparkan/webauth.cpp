#include "webauth.h"
#include <iostream>
#include <QDebug>
//#include <QVBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QNetworkReply>

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

    connect(view->page()->mainFrame(), SIGNAL(urlChanged(QUrl)),     this, SLOT(on_ulrChanged(QUrl)));
    connect(view, SIGNAL(loadStarted()),        this, SLOT(on_loadStarted()));
    connect(view, SIGNAL(loadFinished(bool)),   this, SLOT(on_loadFinished(bool)));
    connect(view->page()->networkAccessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(nm_Finished(QNetworkReply*)));

    QUrl url (oauthAuthorizationUrl.c_str());


    view->load(url);
}


void WebAuth::on_loadFinished(bool ok)
{
    //qWarning() << "loadFinished: " << reply->readAll();
    //qWarning() << "loadFinished: ";
    //qWarning() << "Http ***********************************************************************\n"
    //           << view->page()->mainFrame()->toHtml()
    //           << "******************************************************************************\n";
}


void WebAuth::nm_Finished(QNetworkReply *reply){
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
                //connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_loadFinished(QNetworkReply*)));
                view->load(*request, QNetworkAccessManager::PostOperation, postData.toUtf8());
                //nm->post(*request, postData.toUtf8());
            }
                break;
        }
    }
}
