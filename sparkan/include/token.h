#ifndef TOKEN_H
#define TOKEN_H
#include <QString>

class Token {
private:
    QString token;
    long expires_in;
public:

    Token (QString token, long expires_in)
    {
        this->token = token;
        this->expires_in = expires_in;
    }

    QString getToken() { return token; }
    long getExpiresIn () {return expires_in;}
};
#endif
