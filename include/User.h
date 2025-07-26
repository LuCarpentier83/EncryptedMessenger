#ifndef USER_H
#define USER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>


class User {
    inline static int next_user_id;
public:
    static std::shared_ptr<User> getInstance(const std::string& name);

    User(const User&) = delete;
    User& operator=(const User&) = delete;
    ~User() {
        EVP_PKEY_free(user_fullkey);
    };

    std::string publicKey;
    const std::string& getName() const { return this->name;}
    int getUserID() const { return user_id;}
    static void displayUsers();


private:
    explicit User(std::string  name) : name(std::move(name)) {
        user_id = generateUserID();
        user_fullkey = generatePKey();
        filename = std::string(TOKEN_DIR) + "user" + std::to_string(user_id) + ".pem";
        publicKey = createPublicKey();
        createPrivateKey();
    }

    std::string name;

    EVP_PKEY* user_fullkey;
    std::string filename;
    inline static std::unordered_map<std::string, std::shared_ptr<User>> users;
    int user_id = 0;
    EVP_PKEY* getKeyPointer() const { return user_fullkey;}
    EVP_PKEY* generatePKey();
     int generateUserID() {
        return ++next_user_id;
    }
    std::string createPublicKey() const;
    void  createPrivateKey();
};

#endif //USER_H
