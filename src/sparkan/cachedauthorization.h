#ifndef CACHEDAUTHORIZATION_H
#define CACHEDAUTHORIZATION_H
#include "cachedauthorization.h"
#include <QString>

class CachedAuthorization {
private:
    QString auth;
public:
    QString get();
    void write(QString auth);
};

#endif // CACHEDAUTHORIZATION_H
