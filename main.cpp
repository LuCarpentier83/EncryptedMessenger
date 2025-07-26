#include <iostream>
#include "Message.h"
#include "User.h"
#include "Encryption.h"

using namespace std;

int main() {

    // message_t message;
    // message.content = "Hello Lucas";
    // message.sender = "Maha";
    // message.target = "Lucas";

    auto lucas = User::getInstance("lucas");
    std::cout << lucas->getName() << std::endl;
    cout << lucas->getUserID() << endl;
    cout << lucas->publicKey << endl;

    auto maha = User::getInstance("maha");
    std::cout << maha->getName() << std::endl;
    cout << maha->getUserID() << endl;
    cout << maha->publicKey << endl;

    auto george = User::getInstance("george");
    std::cout << george->getName() << std::endl;
    cout << george->getUserID() << endl;
    cout << george->publicKey << endl;
    return 0;
}