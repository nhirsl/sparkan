#ifndef CORESERVICE_H
#define CORESERVICE_H
#include "coreservice_global.h"

#include <QObject>



class CORESERVICE_DLLSPEC CoreService : public QObject
{
    Q_OBJECT
public:
    CoreService(QObject *parent = 0);
    ~CoreService();

    static CoreService* getInstance();
};
#endif // CORESERVICE_H
