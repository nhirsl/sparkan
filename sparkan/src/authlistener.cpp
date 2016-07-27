#include "authlistener.h"

AuthListener::AuthListener(QObject *parent):QObject(parent)
{

}

void AuthListener::setCore(CoreService *core)
{
    //connect(this, SIGNAL(OAuth()), core, SLOT(getOAuth()));
}


void AuthListener::getOAuth()
{
    emit OAuth();
}
