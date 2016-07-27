#include "coreservice.h"
#include "coreserviceimpl.h"
#include <iostream>
#include <QDebug>


CoreService::CoreService(QObject *parent)
    : QObject(parent)
{
}

CoreService::~CoreService()
{
}

CoreService* CoreService::getInstance()
{
    return CoreServiceImpl::getInstance();
}

