#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include "Message.h"

class Encryption
{
public:
    static encrypted_message_t encryptMessage(Message& message, EVP_PKEY* pkey);
    static message_t decryptMessage(EncryptedMessage& encrypted_message, std::string filepath);
    static EVP_PKEY* convertPKeyStringToEVP_PKEY(std::string& PKey);
};
#endif //ENCRYPTION_H
