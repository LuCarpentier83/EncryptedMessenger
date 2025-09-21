#ifndef BROKER_H
#define BROKER_H

#include "Message.h"
#include <queue>
#include <unordered_map>

class User;

class Broker {
public:
    static Broker& initBroker() {
        static Broker instance;
        return instance;
    }
    Broker(const Broker&) = delete;
    Broker& operator=(const Broker&) = delete;
    ~Broker() = default;

    void registerUser(User* user);
    bool checkRegisteredUser(int user_id);
    void sendMessage(encrypted_message_t message);
    void disconnectUser(int user_id);
    void connectUser(int user_id);
    bool isConnectedUser(int user_id) {
        return std::find(connectedUsers.begin(), connectedUsers.end(), user_id) != connectedUsers.end();
    }
    std::vector<int> getAllConnectedUser() {return connectedUsers;}
    void printUserMessages(int user_id);
    std::queue<encrypted_message_t>& getMessagesForUser(int user_id) {
        return userMessages[user_id];
    }
private:
    Broker(){};
    std::unordered_map<int, std::queue<encrypted_message_t>> userMessages;
    std::unordered_map<int, User> users;
    std::vector<int> connectedUsers;

};
#endif //BROKER_H
