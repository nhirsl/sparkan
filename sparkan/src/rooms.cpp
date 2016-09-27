#include "rooms.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iterator>
#include "room.h"

Rooms::Rooms(QObject *parent) : QAbstractListModel(parent)
{

}


void Rooms::updateRooms()
{
    if (m_token.isEmpty()) return;
    QString bearer ("Bearer " + m_token);

    request = new QNetworkRequest(QUrl("https://api.ciscospark.com/v1/rooms"));
    nm = new QNetworkAccessManager();
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request->setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request->setRawHeader(QByteArray("Authorization"), QByteArray(bearer.toStdString().c_str()));

    connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotResponse(QNetworkReply*)));
    nm->get(*request);
}

void Rooms::gotResponse(QNetworkReply * reply)
{
    //std::cout << "gotResponse" << reply->readAll().toStdString() << std::endl;

    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jdoc.object();
    QJsonArray items = json.value("items").toArray();
    for (auto it = items.begin(); it != items.end(); it++)
    {
        if((*it).isObject()){
            QJsonObject object = (*it).toObject();
            Room room;
            room.setId(object.value("id").toString());

            room.m_title = object.value("title").toString();
            room.m_type = object.value("type").toString();
            room.m_isLocked = object.value("isLocked").toString();
            room.m_lastActivity = object.value("lastActivity").toString();
            room.m_created = object.value("created").toString();

            bool exist = false;
            foreach (auto it, m_roomList) {
                if (it->m_id == room.m_id)
                {
                    *it = room;
                    exist = true;
                }
            }
            if (!exist)
            {
                Room* room2 = new Room();
                *room2 = room;
                m_roomList.append(room2);
            }

        }
    }
    emit layoutChanged();


    foreach (auto it, m_roomList) {
     std::cout << (*it).m_title.toStdString() << std::endl;
    }
    std::cout << "**********************************************************************" << std::endl;

}

int Rooms::rowCount(const QModelIndex & parent ) const {
    if (parent.isValid())
        return 0;
    return m_roomList.size();
}

QVariant Rooms::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if (role == RoomId)
        data = QVariant(m_roomList.at(index.row())->m_id);
    if (role == NameRole)
        data = QVariant(m_roomList.at(index.row())->m_title);
    if (role == LastUpdated)
        data = QVariant(m_roomList.at(index.row())->m_lastActivity);
    return data;
}

QHash<int, QByteArray> Rooms::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RoomId] = "id";
    roles[NameRole] = "name";
    roles[LastUpdated] = "update_date";

    return roles;
}
void Rooms::setSelectedRoom(QString roomId)
{
    m_selected_room = roomId;
    std::cout << "****" << m_selected_room.toStdString() << "****" << std::endl;

}

