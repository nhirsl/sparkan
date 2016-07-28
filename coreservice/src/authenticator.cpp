#include "authenticator.h"
#include <QObject>
#include <QString>
#include <iostream>

Authenticator::Authenticator(QObject* parent)
    :QObject(parent)
{

}

Authenticator::~Authenticator()
{

}

void Authenticator::onCodeReceived(QString code)
{
    std::cout << "onCodeReceived " << code.toStdString();
}

