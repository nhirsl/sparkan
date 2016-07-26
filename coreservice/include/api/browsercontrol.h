#ifndef BROWSERCONTROL_H
#define BROWSERCONTROL_H
#include "coreservice_global.h"
#include "browser.h"
#include <QUrl>
#include <iostream>


class CORESERVICE_DLLSPEC BrowserControl : public QObject
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
