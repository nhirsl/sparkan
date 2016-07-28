#ifndef WEBBROWSER_H
#define WEBBROWSER_H
#include "browser.h"

class WebBrowser : public Browser
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

public:
    WebBrowser(QObject *parent = 0);
    QUrl url() const { return m_url;}
    bool visible() const { return m_visible;}
    void setUrl(const QUrl url);

public slots:
    virtual void onStartLogin(const QUrl);
    virtual void onStopLogin();
    void onUrlChanged(const QUrl);

private:
    QUrl m_url;
    bool m_visible;

signals:
    void urlChanged(QUrl url);
    void visibleChanged(bool visible);
};

#endif // WEBBROWSER_H
