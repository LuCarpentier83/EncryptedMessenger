#include "Broker.h"
#include "User.h"
#include "Encryption.h"

#include <iostream>
#include <queue>

void Broker::registerUser(User* user) {
    if (user == nullptr) {
        return;
    }
    int id = user->getUserID();
    auto it = users.find(id);
    if (it == users.end()) {
        users[id] = UserData{user, std::queue<encrypted_message_t>(), false};
        std::cout << "Sucessfully registered " << user->getName() << std::endl;
    }
}

bool Broker::checkRegisteredUser(int user_id){
    return users.find(user_id) != users.end();
}

void Broker::sendMessage(encrypted_message_t msg) {
    if (!users.at(msg.sender_id).connected) {
        return;
    }
    auto it = users.find(msg.receiver_id);
    if (it == users.end()) {
        throw std::runtime_error("Receiver not found.");
    }
    it->second.messages.push(msg);
}

void Broker::receiveMessage(int user_id) {
    if (!users.at(user_id).connected) {
        return;
    }
    auto& queue = getMessagesForUser(user_id);
    while (!queue.empty()) {
        encrypted_message_t& enc_msg = queue.front();
        message_t clear_msg = Encryption::decryptMessage(enc_msg.cipher_text, TEST_PEM_PATH);
        std::cout << clear_msg.content << std::endl;
        queue.pop();
    }
}

void Broker::connectUser(int user_id) {
    auto it = users.find(user_id);
    if (it == users.end()) {
        return;
    }
    if (it->second.connected) {
        std::cout << "User with ID number " << user_id << " is already connected." << std::endl;
        return;
    }
    it->second.connected = true;
}


void Broker::disconnectUser(int user_id) {
    auto it = users.find(user_id);
    if (it == users.end()) {
        return;
    }
    if (!it->second.connected) {
        std::cout << "User with ID number " << user_id << " is already disconnected." << std::endl;
        return;
    }
    it->second.connected = false;
    std::cout << "User with ID number " << user_id << " is now disconnected." << std::endl;
}

void Broker::printUserMessages(int user_id) {
    auto it = users.find(user_id);
    if (it == users.end()) {
        std::cout << "No messages for this user " << user_id << std::endl;
        return;
    }
    std::queue<encrypted_message_t> copy = it->second.messages;
    std::cout << "Messages for user " << user_id << " :" << std::endl;
    while (!copy.empty()) {
        const encrypted_message_t& msg = copy.front();
        std::cout << "From: " << msg.sender_id << ", Content: " << msg.cipher_text << std::endl;
        copy.pop();
    }
}