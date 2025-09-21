#include "Encryption.h"
#include <Message.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <iostream>
#include <string>
#include <vector>
#include <openssl/err.h>
#include <stdexcept>

encrypted_message_t Encryption::encryptMessage(std::string message, EVP_PKEY* pkey) {
    // Initialize context
    EVP_PKEY_CTX* ctx;
    ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) {
        throw std::runtime_error("Failed to create EVP_PKEY_CTX");
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to init encrypt");
    }

    // Set up padding
    EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

    // Encryption
    size_t cipherLen;
    std::string raw_text = message;
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

message_t Encryption::decryptMessage(std::string& encrypted_message, std::string filepath) {

    BIO* bio = BIO_new_file(filepath.c_str(), "r");
    if (!bio) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("Error while reading file");
    }

    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    if (!pkey) {
        BIO_free(bio);
        throw std::runtime_error("Error while reading PEM");
    }

    // Initialize context
    EVP_PKEY_CTX* ctx;
    ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) {
        throw std::runtime_error("Failed to create EVP_PKEY_CTX");
    }
    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to init decrypt");
    }

    // Set up padding
    EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

    size_t outLen = 0;
    if (EVP_PKEY_decrypt(ctx, NULL, &outLen, (const unsigned char*)encrypted_message.data(),
                         encrypted_message.size()) <= 0) {

                            EVP_PKEY_CTX_free(ctx);
                            throw std::runtime_error("Failed to get decrypted length");
                         }

    std::vector<unsigned char> decrypted(outLen);
    if (EVP_PKEY_decrypt(ctx, decrypted.data(), &outLen, (const unsigned char*)encrypted_message.data(),
                            encrypted_message.size()) <= 0) {

                            EVP_PKEY_CTX_free(ctx);
                            throw std::runtime_error("Failed to decrypt message");
                        }

    EVP_PKEY_CTX_free(ctx);
    message_t output;
    output.content.assign((char*)decrypted.data(), outLen);
    return output;
}

EVP_PKEY* Encryption::convertPKeyStringToEVP_PKEY(std::string& PKey) {
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
