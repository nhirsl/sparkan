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
    virtual void onStartLogin(const QUrl){}
    virtual void onStopLogin(){}
signals:
    virtual void codeReceived(QString code);
};

#endif // BROWSER_H
