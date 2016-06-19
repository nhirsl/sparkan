#ifndef WEBAUTH_H
#define WEBAUTH_H
#include <QObject>
#include <QtWebKit/QWebView>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "ui_authview.h"

class WebAuth : public QObject
{
    Q_OBJECT
public slots:
    void nm_Token(QNetworkReply *reply);
    void nm_Redirect(QNetworkReply *reply);

public:
    WebAuth();
    void GetAuth();

signals:
    void on_BareAuth(void);

private:
    QWidget *widget;
    QWebView *view;
    QWebPage *page;
    QWebFrame *frame;
    QString code;

};
#endif // WEBAUTH_H
