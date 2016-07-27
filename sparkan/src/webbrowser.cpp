#include "webbrowser.h"
#include <QtCore/QDebug>
#include <iostream>
#include <QUrl>
#include <QThread>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent), m_url("http://portal.pstech.rs")
{
}

void WebBrowser::load(const QUrl url)
{
    QThread::currentThreadId();
    std::cout << "Loadin: " << QThread::currentThreadId() << " url: " << url.toString().toStdString()  <<std::endl;
}

void WebBrowser::onUrlChanged(QUrl url)
{
    std::cout << "onUrlChanged: " << url.toString().toStdString()  <<std::endl;
}

void WebBrowser::setUrl(const QUrl url)
{
    m_url = url;
    emit urlChanged(m_url);
}
