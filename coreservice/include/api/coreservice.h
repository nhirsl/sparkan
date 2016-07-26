#ifndef CORESERVICE_H
#define CORESERVICE_H
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QObject>

#include <browser.h>


class BrowserControl;

class CoreService : public QThread
{
    Q_OBJECT
private:
    CoreService(QObject *parent = 0);
    ~CoreService();
public:
    static CoreService* getInstance();

public:
    QString getName();
    void setBrowser(Browser*);
protected:
    void run();
private: //Static fields
    static CoreService* singleton;
    static QMutex* static_mutex;

private:
    QMutex m_mutex;

    BrowserControl* m_browser_controller;

public slots:
    void getOAuth();
signals:
    void onOAuth(QString);


};

#endif // CORESERVICE_H
