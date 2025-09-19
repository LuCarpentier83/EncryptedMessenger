#include "Broker.h"

void Broker::registerUser(const User& user) {
    auto it = userMessages.find(user.getUserID());
    if (it == userMessages.end()) {
        userMessages[user.getUserID()] = std::queue<Message>();
    }
}

bool Broker::checkRegisteredUser(int user_id){
    return userMessages[user_id] != userMessages.end();
}
