#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <QList>

class Person {
private:
    QString id;
    QString displayName;
    QList<QString> emails;
public:
    QString getId();
    QString getDisplayName();
};

#endif // PERSON_H
