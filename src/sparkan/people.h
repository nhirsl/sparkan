#ifndef PEOPLE_H
#define PEOPLE_H
#include <QObject>
#include <QUrl>
#include "person.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
namespace People
{

    class Me : public QObject
   {
    Q_OBJECT
    public:
        void get();
    public slots:
        void finished(QNetworkReply *);

    };
}
#endif // PEOPLE_H
