#ifndef ROOM_H
#define ROOM_H
#include <QString>


class Room
{

public:
    Room();
    QString m_id;
    QString m_title;
    QString m_type;
    QString m_isLocked;
    QString m_lastActivity;
    QString m_created;
    void setId (QString id) { m_id = id; }
};

#endif // ROOM_H
