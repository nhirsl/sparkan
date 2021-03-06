#ifndef AUTHLISTENER_H
#define AUTHLISTENER_H
#include "tokenListener.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <person.h>
#include "rooms.h"


class AuthListener : public TokenListener
{
    Q_OBJECT
private:
    Person* m_me;
    QNetworkRequest *request;
    QNetworkAccessManager *nm;
    Rooms *m_rooms;
public:
    AuthListener(QObject* parent = 0);
    void setMe(Person* me) {m_me = me;}
    void setRooms(Rooms* rooms) { m_rooms = rooms; }
public slots:
    virtual void onNewAccessToken(QString token);
    void gotMe(QNetworkReply* reply);
};

#endif // AUTHLISTENER_H
