#include "webbrowser.h"
#include <iostream>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent), m_url("http://portal.pstech.rs")
{
}

void WebBrowser::onStartLogin(const QUrl url)
{
    setUrl(url);
}

void WebBrowser::onStopLogin()
{

}

void WebBrowser::onUrlChanged(QUrl url)
{
    QString tName = QThread::currentThread()->objectName();
    QString code = parseUrlForCode(url);
    if (code.isEmpty()) return;
    std::cout << tName.toStdString() <<"Code retrived: " << code.toStdString()  <<std::endl;
    emit codeReceived(code);

}

void WebBrowser::setUrl(const QUrl url)
{
    m_url = url;
    emit urlChanged(m_url);
}
