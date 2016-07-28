#ifndef TOKENLISTENER_H
#define TOKENLISTENER_H

#include "coreservice_global.h"

#include <QObject>
#include <QString>

class CORESERVICE_DLLSPEC TokenListener : public QObject
{
    Q_OBJECT
public:
    TokenListener(QObject* parent = 0):QObject(parent){}

public slots:
    virtual void onNewAccessToken(QString token) = 0;
};

#endif
