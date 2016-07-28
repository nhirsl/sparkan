#ifndef CORESERVICEIMPL_CPP
#define CORESERVICEIMPL_CPP
#include "coreservice.h"
#include "coreservice_global.h"

#include <QThread>
#include <QMutex>
#include <QObject>

class Authenticator;

class CoreServiceImpl : public CoreService
{
public:
    CoreServiceImpl(QObject *parent = 0);
    ~CoreServiceImpl();


    virtual void setBrowser(const Browser* browser);
signals:
    void fireSignal();

    static CoreService* getInstance();
private:
    static QMutex* static_mutex;
    static CoreServiceImpl* singleton;
    static QThread* service_thread;

    Authenticator* m_authenticator;
};


#endif // CORESERVICEIMPL_CPP
