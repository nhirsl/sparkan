#ifndef AUTHLISTENER_H
#define AUTHLISTENER_H
#include "tokenListener.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>


class AuthListener : public TokenListener
{
    Q_OBJECT
private:
    QNetworkRequest *request;
    QNetworkAccessManager *nm;
public:
    AuthListener(QObject* parent = 0);
public slots:
    virtual void onNewAccessToken(QString token);
    void gotMe(QNetworkReply* reply);
};

#endif // AUTHLISTENER_H
