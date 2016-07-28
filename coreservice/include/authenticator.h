#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H
#include <QMutex>
#include <QObject>
#include <QString>
#include <QUrl>
#include "coreservice_global.h"

class Authenticator : public QObject
{
    Q_OBJECT
public:
    Authenticator(QObject* parent = 0);
    ~Authenticator();

private:
    QMutex mutex;

signals:
    void startLogin(const QUrl);
    void stopLogin();

public slots:
    void onCodeReceived(QString code);
};


#endif
