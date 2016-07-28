#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H
#include <QMutex>
#include <QObject>
#include <QString>
#include <QUrl>
#include "coreservice_global.h"
#include <QNetworkReply>

class Authenticator : public QObject
{
    Q_OBJECT
public:
    Authenticator(QObject* parent = 0);
    ~Authenticator();

    QString getAuthToken();

private:
    QMutex m_mutex;
    QString m_token;
    bool m_logging_in;

signals:
    void startLogin(const QUrl);
    void stopLogin();
    void newAccessToken(QString token);

public slots:
    void onCodeReceived(QString code);
    void onAccessToken(QNetworkReply* reply);
};


#endif
