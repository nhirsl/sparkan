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
    QThread* cthread = QThread::currentThread();
    QThread::currentThreadId();
    std::cout << "Loadin: " << QThread::currentThreadId() << std::endl;
}
