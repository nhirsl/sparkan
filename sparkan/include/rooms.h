#ifndef ROOMS_H
#define ROOMS_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "room.h"
#include <QHash>
#include <QAbstractListModel>

class Rooms : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString selectedRoom READ selectedRoom WRITE setSelectedRoom NOTIFY selectedRoomChanged)

    QString m_token;
    QString m_selected_room;

    QNetworkAccessManager *nm;
    QNetworkRequest *request;
    QList<Room*> m_roomList;
public:
    enum RoomRoles {
        RoomId = Qt::UserRole + 1,
        NameRole,
        LastUpdated
    };

    explicit Rooms(QObject *parent = 0);
    void setToken(QString token) { m_token = token;}
    void updateRooms();

    QString selectedRoom() {return m_selected_room;}
    void setSelectedRoom(QString roomId);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const ;

signals:
    void selectedRoomChanged(QString roomId);
public slots:
    void gotResponse(QNetworkReply*);
};

#endif // ROOMS_H
