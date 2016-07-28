#include "coreserviceimpl.h"
#include "authenticator.h"
#include "browser.h"
#include <QMutexLocker>
#include <QObject>

QMutex* CoreServiceImpl::static_mutex = new QMutex();
CoreServiceImpl* CoreServiceImpl::singleton = NULL;
QThread*    CoreServiceImpl::service_thread = NULL;

CoreServiceImpl::CoreServiceImpl(QObject *parent)
    :CoreService(parent), m_authenticator(new Authenticator(this))
{

}

CoreServiceImpl::~CoreServiceImpl()
{

}


CoreService* CoreServiceImpl::getInstance()
{
    QMutexLocker lock(static_mutex);

    if (singleton == NULL)
    {
        singleton = new CoreServiceImpl();

        if (service_thread == NULL)
        {
            service_thread = new QThread();
        }

        service_thread->setObjectName("Coreservice main thread");
        service_thread->start();
        singleton->moveToThread(service_thread);
    }


    return singleton;
}

void CoreServiceImpl::setBrowser(const Browser *browser)
{
    QObject::connect(m_authenticator, SIGNAL(startLogin(QUrl)), browser, SLOT(onStartLogin(QUrl)));
    QObject::connect(m_authenticator, SIGNAL(stopLogin()), browser, SLOT(onStopLogin()));
    QObject::connect(browser, SIGNAL(codeReceived(QString)), m_authenticator, SLOT(onCodeReceived(QString)));

}
