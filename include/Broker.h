#ifndef BROKER_H
#define BROKER_H

#include "Message.h"
#include "User.h"
#include <queue>

class Broker {
public:
    static Broker& initBroker() {
        static Broker instance;
        return instance;
    }
    Broker(const Broker&) = delete;
    Broker& operator=(const Broker&) = delete;
    ~Broker() = default;

    void registerUser(const User& user);
    bool checkRegisteredUser(int user_id);
private:
    Broker(){};
    std::unordered_map<int, std::queue<Message>> userMessages;
    std::unordered_map<int, User> users;

};
#endif //BROKER_H
