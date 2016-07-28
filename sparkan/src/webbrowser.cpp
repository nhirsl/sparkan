#include "webbrowser.h"
#include <iostream>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent), m_url("http://portal.pstech.rs"), m_visible(false)
{
}

void WebBrowser::onStartLogin(const QUrl url)
{
    setUrl(url);
    m_visible = true;
    emit visibleChanged(m_visible);
}

void WebBrowser::onStopLogin()
{
    setUrl(QUrl("about:blank"));
    emit visibleChanged(m_visible = false);
}

void WebBrowser::onUrlChanged(QUrl url)
{
    QString tName = QThread::currentThread()->objectName();
    QString code = parseUrlForCode(url);
    if (code.isEmpty()) return;
    std::cout << tName.toStdString() <<"Code retrived: " << code.toStdString()  <<std::endl;
    emit codeReceived(code);
    onStopLogin();

}

void WebBrowser::setUrl(const QUrl url)
{
    m_url = url;
    emit urlChanged(m_url);
}
