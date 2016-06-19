#ifndef WEBAUTH_H
#define WEBAUTH_H
#include <QObject>
#include <QtWebKit/QWebView>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class WebAuth : public QObject
{
    Q_OBJECT
public slots:
    void on_ulrChanged(QUrl url);
    void on_loadStarted(void);
    void on_loadFinished(bool ok);
    void on_loadProgress(int progress);
    void on_linkClicked(QUrl url);
    void nm_Finished(QNetworkReply *reply);

public:
    WebAuth();
    void GetAuth();

signals:
    void on_BareAuth(void);

private:
    QWebView *view;
    QWebPage *page;
    QWebFrame *frame;
    QString code;

};
#endif // WEBAUTH_H
