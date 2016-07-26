#ifndef AUTHLISTENER_H
#define AUTHLISTENER_H
#include "coreservice.h"


class AuthListener : public QObject
{
    Q_OBJECT
public:
    AuthListener(QObject* parent = 0);
    ~AuthListener(){}
    void setCore(CoreService* core);
    void getOAuth();

signals:
    void OAuth();
};

#endif // AUTHLISTENER_H
