#ifndef CORESERVICE_H
#define CORESERVICE_H
#include "coreservice_global.h"


#include <QObject>

class Browser;

class CORESERVICE_DLLSPEC CoreService : public QObject
{
    Q_OBJECT

public:
    CoreService(QObject *parent = 0);
    ~CoreService();

    virtual void setBrowser(const Browser* browser) = 0;
    static CoreService* getInstance();
};
#endif // CORESERVICE_H
