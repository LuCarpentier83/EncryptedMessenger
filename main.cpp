#include <iostream>
#include "Message.h"
#include "User.h"
#include "Encryption.h"

using namespace std;

int main() {

    // auto lucas = User::getInstance("lucas");
    // std::cout << lucas->getName() << std::endl;
    // cout << lucas->getUserID() << endl;
    // cout << lucas->publicKey << endl;
    //
    // auto maha = User::getInstance("maha");
    // std::cout << maha->getName() << std::endl;
    // cout << maha->getUserID() << endl;
    // cout << maha->publicKey << endl;
    //
    // auto george = User::getInstance("george");
    // std::cout << george->getName() << std::endl;
    // cout << george->getUserID() << endl;
    // cout << george->publicKey << endl;
    //
    // message_t message;
    // message.content = "Hello Lucas";
    // message.sender = "Maha";
    // message.target = "Lucas";

    // EVP_PKEY* lucas_key = Encryption::convertPKeyStringToEVP_PKEY(lucas->publicKey);
    // encrypted_message_t encrypted_message = Encryption::encryptMessage(message, lucas_key);
    // std::cout << encrypted_message.cipher_text << std::endl;
    // message_t decrypted_message = Encryption::decryptMessage(encrypted_message, TEST_PEM_PATH);
    // std::cout << decrypted_message.content << std::endl;
    return 0;
}