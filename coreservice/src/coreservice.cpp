#include "coreservice.h"
#include "browsercontrol.h"
#include <iostream>
#include <QDebug>

CoreService* CoreService::singleton = NULL;
QMutex* CoreService::static_mutex = new QMutex();
CoreService::CoreService(QObject *parent)
    : QThread(parent), m_browser_controller(NULL)
{

}

CoreService::~CoreService()
{
    moveToThread(this);

}

void CoreService::run()
{
    std::cout << "run: " << QThread::currentThreadId() << std::endl;
    exec();
}

CoreService* CoreService::getInstance() {
    QMutexLocker locker(static_mutex);

    if (singleton == NULL)
    {
        singleton = new CoreService();
        singleton->start();
    }

    return singleton;
}

QString CoreService::getName()
{
    return "Core Sparkan Service";
}

void CoreService::setBrowser(Browser* browser)
{
    QMutexLocker locker(&m_mutex);
    if (m_browser_controller != NULL)
        return;
    m_browser_controller = new BrowserControl();
    m_browser_controller->moveToThread(this);
    m_browser_controller->setBrowser(browser);
    qWarning() << "Browser is set";

}

void CoreService::getOAuth() {

    std::cout << "getOAuth: " << QThread::currentThreadId() << std::endl;
    if (m_browser_controller != NULL)
    {
        m_browser_controller->startLogin();
    }
}
