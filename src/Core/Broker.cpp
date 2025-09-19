#include "Broker.h"
#include "User.h"

#include <iostream>

void Broker::registerUser(User* user) {
    if (user == nullptr) {
        return;
    }
    int id = user->getUserID();
    auto it = userMessages.find(id);
    if (it == userMessages.end()) {
        userMessages[id] = std::queue<encrypted_message_t>();
        std::cout << "Sucessfully registered " << user->getName() << std::endl;
    }
}

bool Broker::checkRegisteredUser(int user_id){
    return userMessages.find(user_id) != userMessages.end();
}

void Broker::sendMessage(encrypted_message_t msg) {
    auto it = userMessages.find(msg.receiver_id);
    if (it == userMessages.end()) {
        throw std::runtime_error("Receiver not found.");
    }
    it->second.push(msg);
}

void Broker::connectUser(int user_id) {
    if (std::find(connectedUsers.begin(), connectedUsers.end(), user_id) == connectedUsers.end()) {
        connectedUsers.push_back(user_id);
        return;
    }
    std::cout << "User with ID number " << user_id << "is already connected." << std::endl;
}

void Broker::disconnectUser(int user_id) {
    auto it = std::find(connectedUsers.begin(), connectedUsers.end(), user_id);
    if (it != connectedUsers.end()) {
        connectedUsers.erase(it);
        return;
    }
    std::cout << "User with ID number " << user_id << "was not connected." << std::endl;
}
