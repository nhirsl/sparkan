#ifndef BROWSERCONTROL_H
#define BROWSERCONTROL_H

#include "browser.h"
#include <QtCore/QUrl>
#include <iostream>


class BrowserControl : public QObject
{
    Q_OBJECT
public:
    explicit BrowserControl(QObject *parent = 0);
    void setBrowser(Browser*);
    void startLogin();

signals:
    void load(QUrl);

public slots:

private:
    Browser* m_browser;

    static std::string oauthAuthorizationUrl;

};

#endif // BROWSERCONTROL_H
