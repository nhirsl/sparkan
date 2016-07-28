#include "authenticator.h"
#include <iostream>
#include <QThread>

#include <QNetworkRequest>
#include <QNetworkAccessManager>


#include <QJsonDocument>
#include <QJsonObject>

#include <QMutexLocker>

QUrl oauthAuthorizationUrl("https://api.ciscospark.com/v1/authorize?client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca&response_type=code&redirect_uri=http%3A%2F%2Flocalhost&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here");
Authenticator::Authenticator(QObject* parent)
    :QObject(parent)
{

}

Authenticator::~Authenticator()
{

}


void Authenticator::onCodeReceived(QString code)
{
    QNetworkRequest *request = new QNetworkRequest(QUrl("https://api.ciscospark.com/v1/access_token"));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request->setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    QNetworkAccessManager *nm = new QNetworkAccessManager();
    QString postData = "grant_type=authorization_code&"
                       "client_id=Cf058c9b9c30412326fe40868e333796bfeae17fb58ef709de8a7e8c73850ceca&"
                       "client_secret=5a1b187745e79a6cb2fe6b005a3b3be16b633411374eacb84a38c3c4068fbf50&"
                       "code=" + code + "&redirect_uri=http://localhost";


    connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAccessToken(QNetworkReply*)));
    nm->post(*request, postData.toUtf8());
}

void Authenticator::onAccessToken(QNetworkReply* reply)
{

    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jdoc.object();
    QString auth = json.value("access_token").toString();

    QMutexLocker lock(&m_mutex);
    m_token = auth;
    m_logging_in = false;

    emit newAccessToken(auth);

}

QString Authenticator::getAuthToken()
{
    QMutexLocker lock(&m_mutex);
    if (m_token.isEmpty())
    {
        if (m_logging_in == false)
        {
            m_logging_in = true;
            emit startLogin(oauthAuthorizationUrl);
        }
    }
    return m_token;
}
