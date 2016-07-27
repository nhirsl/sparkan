#ifndef BROWSER_H
#define BROWSER_H
#include "coreservice_global.h"

#include <QObject>
#include <QString>
#include <QUrl>

class CORESERVICE_DLLSPEC Browser: public QObject
{
    Q_OBJECT
public:
    Browser(QObject *parent):QObject(parent){}

    QString parseUrlForCode(QUrl url);

public slots:
    virtual void startLogin(const QUrl){}
    virtual void stopLogin(){}
signals:
    void codeReceived(QString code);
};

#endif // BROWSER_H
