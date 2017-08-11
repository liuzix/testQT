#ifndef RSAUTILS_H
#define RSAUTILS_H
#include <QString>
#include <QException>

#include <openssl/rsa.h>
#include <openssl/pem.h>

class RSAUtils
{
public:
    RSAUtils();
    void loadFromString(QString str);
    QString encryptRSABase64(QString data);
    QByteArray encryptRSA(QByteArray data);

private:
    RSA* keyPair;
};

class RSAException: public QException {
private:
    QString msg;
public:
    RSAException (const QString& message) : msg(message) {}

    void raise() const { throw *this; }

    RSAException *clone() const { return new RSAException(msg); }
};

#endif // RSAUTILS_H
