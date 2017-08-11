#include "rsautils.h"


RSAUtils::RSAUtils()
{

}

void RSAUtils::loadFromString(QString str)
{
    BIO* bio = BIO_new_mem_buf(qPrintable(str), -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    if (keyPair != nullptr) free(keyPair);

    keyPair = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);
    if (!keyPair) {
        throw RSAException("Cannot load from public key string!");
    }
}

QString RSAUtils::encryptRSABase64(QString data)
{
    QByteArray binaryData = data.toLocal8Bit();
    QByteArray binaryResult = encryptRSA(binaryData);
    return QString(binaryResult.toBase64());

}

QByteArray RSAUtils::encryptRSA(QByteArray data)
{
    int rsaLen = RSA_size(keyPair);
    QByteArray result(rsaLen, '\0');
    int resultLen = RSA_public_encrypt(data.size(),
                                       (const unsigned char*)data.data(),
                                       (unsigned char*)result.data(),
                                       keyPair,
                                       RSA_PKCS1_PADDING);
    if (resultLen == -1) {
        throw RSAException("Cannot encrypt binary data");
    }

    return result;

}

