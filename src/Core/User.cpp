#include "User.h"
#include "Encryption.h"

#include <iostream>

std::shared_ptr<User> User::getInstance(const std::string &name, Broker& broker) {
    auto it = users.find(name);
    if (it == users.end()) {
        User *ptr = new User(name, broker);
        std::shared_ptr<User> user(ptr);
        users[name] = user;
        return user;
    }
    return it->second;
}

void User::displayUsers() {
    for (auto& [key, value] : users) {
        std::cout << "Username : " << key << std::endl;
    }
}

EVP_PKEY *User::generatePKey() {
    EVP_PKEY* user_pkey = nullptr;
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    if (!ctx) {
        std::cout << "Failed to generate context" << std::endl;
        return nullptr;
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cout << "Failed to init keygen" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        std::cout << "Failed to set bit" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    if (EVP_PKEY_keygen(ctx, &user_pkey) <= 0) {
        std::cout << "Failed to generate Key" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    EVP_PKEY_CTX_free(ctx);
    return user_pkey;
}


void User::createPrivateKey() {
    EVP_PKEY* user_fullkey = getKeyPointer();
    BIO* f = BIO_new_file(filename.c_str(), "w");
    if (!f) {
        std::cout << "Failed to write inside pem" << std::endl;
    }
    PEM_write_bio_PrivateKey(f, user_fullkey, nullptr, nullptr, 0, nullptr, nullptr);
    BIO_free(f);
}

std::string User::createPublicKey() const {
    EVP_PKEY* user_fullkey = getKeyPointer();
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        std::cout << "Failed to instantiate bio" << std::endl;
    }
    if (!PEM_write_bio_PUBKEY(bio, user_fullkey)) {
        BIO_free(bio);
        std::cout << "Failed to write bio public key" << std::endl;
    }
    char* data = nullptr;
    long len = BIO_get_mem_data(bio, &data);
    std::string pem(data, len);
    BIO_free(bio);
    return pem;
}

void User::sendMessage(message_t& msg) {
    encrypted_message_t enc_msg;
    enc_msg.sender_id = msg.senderID;
    enc_msg.receiver_id = msg.targetID;
    EVP_PKEY* recipient_key = Encryption::convertPKeyStringToEVP_PKEY(this->publicKey);
    if (recipient_key == nullptr) {
        throw std::runtime_error("Failed to convert recipient pub key");
    }
    enc_msg.cipher_text = Encryption::encryptMessage(msg.content, recipient_key).cipher_text;
    EVP_PKEY_free(recipient_key);
    broker.sendMessage(enc_msg);
}

void User::connectUser() {
    broker.connectUser(user_id);
}

