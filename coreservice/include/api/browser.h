#ifndef BROWSER_H
#define BROWSER_H
#include <QtCore/QObject>
#include <QtCore/QUrl>

class Browser: public QObject
{
    Q_OBJECT
public:
    Browser(QObject *parent):QObject(parent){}
public slots:
    virtual void load(const QUrl){}

};

#endif // BROWSER_H
