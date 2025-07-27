#ifndef ENCRYPTION_H
#define ENCRYPTION_H

class Encryption
{
public:
    static encrypted_message_t encryptMessage(Message message, EVP_PKEY* pkey);
    static message_t decryptMessage(EncryptedMessage encrypted_message, EVP_PKEY* pkey);
};
#endif //ENCRYPTION_H
