#include "Encryption.h"
#include <Message.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <iostream>
#include <string>

encrypted_message_t Encryption::encryptMessage(message_t& message, EVP_PKEY* pkey) {
    // Initialize context
    EVP_PKEY_CTX* ctx;
    ctx = EVP_PKEY_CTX_new(pkey, NULL);
    EVP_PKEY_encrypt_init(ctx);

    // Set up padding
    EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

    // Encryption
    size_t cipherLen;
    std::string raw_text = message.content;
    EVP_PKEY_encrypt(ctx, NULL, &cipherLen, (const unsigned char *) raw_text.c_str(), raw_text.size());
    unsigned char* cipherText = (unsigned  char *) OPENSSL_malloc(cipherLen);
    EVP_PKEY_encrypt(ctx, cipherText, &cipherLen, (const unsigned char *) raw_text.c_str(), raw_text.size());

    // Create output
    encrypted_message_t output;
    output.cipher_text.assign( (char*) cipherText, cipherLen);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    OPENSSL_free(cipherText);

    return output;
}

message_t Encryption::decryptMessage(EncryptedMessage& encrypted_message, EVP_PKEY* pkey)
{
    return message_t{};
}

EVP_PKEY* Encryption::convertPKeyStringToEVP_PKEY(std::string& PKey)
{
    const char* pubkey_pem_str = PKey.c_str();

    BIO* bio = BIO_new_mem_buf(pubkey_pem_str, -1);
    if (!bio) {
        std::cout << "Error while reading string PKey" << std::endl;
        return nullptr;
    }

    EVP_PKEY* pubkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    if (!pubkey) {
        std::cout << "Failed to convert to EVP_PKEY" << std::endl;
    }

    BIO_free(bio);
    return pubkey;
}
