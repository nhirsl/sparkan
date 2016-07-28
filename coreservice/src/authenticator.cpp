#include "authenticator.h"
#include <iostream>
#include <QThread>

Authenticator::Authenticator(QObject* parent)
    :QObject(parent)
{

}

Authenticator::~Authenticator()
{

}


void Authenticator::onCodeReceived(QString code)
{
    QString tName = QThread::currentThread()->objectName();
    std::cout << tName.toStdString() <<" onCodeReceived " << code.toStdString() << std::endl << std::flush;
}


