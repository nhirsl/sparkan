#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include "people.h"
#include "cachedauthorization.h"
#include <iostream>

namespace People {

    void Me::get() {
        qWarning() << "get";
        QNetworkRequest *request = new QNetworkRequest(QUrl("https://api.ciscospark.com/v1/people/me"));
        CachedAuthorization *auth = new CachedAuthorization();
        std::string bearer = "Bearer " + auth->get().toStdString();
        std::cout << (bearer);
        request->setRawHeader(QByteArray("Authorization"), QByteArray(bearer.c_str()));
        request->setRawHeader(QByteArray("Accept"), QByteArray("application/json"));

        QNetworkAccessManager *nm = new QNetworkAccessManager();
        nm->get(*request);
        QObject::connect(nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    }

    void Me::finished(QNetworkReply *replay) {
        qWarning() << "finished";
        qDebug() << replay->readAll();

    }

}
