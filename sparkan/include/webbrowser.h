#ifndef WEBBROWSER_H
#define WEBBROWSER_H
#include "browser.h"

class WebBrowser : public Browser
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
public:
    WebBrowser(QObject *parent = 0);
    QUrl url() const { return m_url;}
    void setUrl(const QUrl url);
public slots:
    virtual void load(const QUrl);
    void onUrlChanged(const QUrl);
private:
    QUrl m_url;
signals:
    void urlChanged(QUrl url);
};

#endif // WEBBROWSER_H
