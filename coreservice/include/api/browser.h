#ifndef BROWSER_H
#define BROWSER_H
#include <QObject>
#include <QUrl>

class Browser: public QObject
{
    Q_OBJECT
public:
    Browser(QObject *parent):QObject(parent){}
public slots:
    virtual void load(const QUrl){}
  //  virtual void show();

};

#endif // BROWSER_H
