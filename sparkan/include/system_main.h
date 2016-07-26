#ifndef SYSTEM_MAIN_H
#define SYSTEM_MAIN_H

#include <QThread>

class SystemMain : public QThread
{

    void Run()
    {
        exec();
    }
};
