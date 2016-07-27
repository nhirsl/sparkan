#include "webbrowser.h"
#include <iostream>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent), m_url("http://portal.pstech.rs")
{
}

void WebBrowser::startLogin(const QUrl url)
{
    setUrl(url);
}

void WebBrowser::stopLogin()
{

}

void WebBrowser::onUrlChanged(QUrl url)
{
    QString code = parseUrlForCode(url);
    if (code.isEmpty()) return;
    std::cout << "Code retrived: " << code.toStdString()  <<std::endl;
    emit codeReceived(code);

}

void WebBrowser::setUrl(const QUrl url)
{
    m_url = url;
    emit urlChanged(m_url);
}
