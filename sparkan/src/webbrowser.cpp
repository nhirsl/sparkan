#include "webbrowser.h"
#include <QtCore/QDebug>
#include <iostream>
#include <QUrl>
#include <QThread>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent)
{

}

void WebBrowser::load(const QUrl url)
{
    QThread::currentThreadId();
    std::cout << "Loadin: " << QThread::currentThreadId() << " url: " << url.toString().toStdString()  <<std::endl;
}
