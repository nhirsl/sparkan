#include "webbrowser.h"
#include <QtCore/QDebug>

WebBrowser::WebBrowser(QObject *parent) : Browser(parent)
{

}

void WebBrowser::load(const QUrl url)
{
    qWarning() << "Loadin: " << url.toString();
}
