#ifndef WEBBROWSER_H
#define WEBBROWSER_H
#include "browser.h"

class WebBrowser : public Browser
{
public:
    WebBrowser(QObject *parent = 0);
public slots:
    virtual void load(const QUrl);
};

#endif // WEBBROWSER_H
