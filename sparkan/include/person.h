#ifndef PERSON_H
#define PERSON_H
#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QUrl avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
private:
    QString id;
    QString m_displayName;
    QList<QString> emails;
    QUrl m_avatar;
public:
    Person(QObject* parent = 0):QObject(parent) {}

    QString displayName() { return m_displayName;}
    QUrl avatar() { return m_avatar; }

    void setDisplayName(const QString displayname);
    void setAvatar(const QUrl avatar);

signals:
    void displayNameChanged(QString displayName);
    void avatarChanged(QUrl avatar);
};

#endif // PERSON_H
