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
    void receiveMessage(int user_id);
    void disconnectUser(int user_id);
    void connectUser(int user_id);
    bool isConnectedUser(int user_id) {
        return users.at(user_id).connected;
    }
    std::vector<int> getAllConnectedUser() {
        std::vector<int> connected_ids;
        for (const auto& pair : users) {
            if (pair.second.connected) {
                connected_ids.push_back(pair.first);
            }
        }
        return connected_ids;
    }
    std::vector<int> getAllUser() {
        std::vector<int> all_users;
        for (const auto& pair : users) {
            all_users.push_back(pair.first);
        }
        return all_users;
    }
    void printUserMessages(int user_id);
    std::queue<encrypted_message_t>& getMessagesForUser(int user_id) {
        return users.at(user_id).messages;
    }
    User* getUserById(int user_id) {
        auto it = users.find(user_id);
        if (it == users.end()) {
            throw std::runtime_error("User does not exist");
        }
        return it->second.user;
    }
private:
    Broker(){};
    struct UserData {
        User* user;
        std::queue<encrypted_message_t> messages;
        bool connected;
    };
    std::unordered_map<int, UserData> users;


};
#endif //BROKER_H
