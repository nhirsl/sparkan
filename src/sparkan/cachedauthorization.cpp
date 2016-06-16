#include <cachedauthorization.h>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QString>


QString CachedAuthorization::get()
{
    QFileInfo infFile(QDir::home(), ".sparkan/auth.cache");
    if (auth.isEmpty() && infFile.exists())
    {

        QFile cache(infFile.absoluteFilePath());
        cache.open(QIODevice::ReadOnly);
        auth = QString(cache.readAll()).trimmed();
    }

    return auth;
}

void CachedAuthorization::write(QString)
{

}
