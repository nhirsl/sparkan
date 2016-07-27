#include "browser.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

QRegularExpression rx("localhost.*[&?]code=(.+?)[&^$]");

QString Browser::parseUrlForCode(QUrl url)
{
    QString code;
    QRegularExpressionMatch match = rx.match(url.toString());
    if (match.hasMatch())
    {
        code = match.captured(1);
    }
    return code;
}
