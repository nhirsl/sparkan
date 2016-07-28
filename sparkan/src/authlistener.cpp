#include "authlistener.h"
#include <iostream>
#include <QNetworkReply>

#include <QNetworkRequest>
#include <QNetworkAccessManager>


#include <QJsonDocument>
#include <QJsonObject>

AuthListener::AuthListener(QObject *parent):TokenListener(parent)
{


}

void AuthListener::gotMe(QNetworkReply* reply)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jdoc.object();
    QString displayName = json.value("displayName").toString();
    QUrl avatar = json.value("avatar").toString();

    std::cout <<"AuthListener::gotMe" << displayName.toStdString() <<  std::endl << std::flush;
    if (m_me != NULL){
        m_me->setDisplayName(displayName);
        m_me->setAvatar(avatar);
    }
}

void AuthListener::onNewAccessToken(QString token)
{
    std::cout << "AuthListener::onNewAccessToken" << std::endl << std::flush;
    QString bearer ("Bearer " + token);

    request = new QNetworkRequest(QUrl("https://api.ciscospark.com/v1/people/me"));
    nm = new QNetworkAccessManager();
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request->setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request->setRawHeader(QByteArray("Authorization"), QByteArray(bearer.toStdString().c_str()));

    connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotMe(QNetworkReply*)));
    nm->get(*request);
}


