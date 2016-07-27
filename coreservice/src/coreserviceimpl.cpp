#include "coreserviceimpl.h"
#include <QMutexLocker>


QMutex* CoreServiceImpl::static_mutex = new QMutex();
CoreServiceImpl* CoreServiceImpl::singleton = NULL;
QThread*    CoreServiceImpl::service_thread = NULL;

CoreServiceImpl::CoreServiceImpl(QObject *parent)
    :CoreService(parent)
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
