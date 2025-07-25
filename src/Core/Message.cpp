#include "Message.h"
#include <iostream>

Message::Message(const Message_t& msg) : msg(msg) {}

Message::~Message() {
    std::cout << "Object destroyed" << std::endl;
}

const std::string& Message::getContent() const {
    return msg.content;
};

const std::string& Message::getSender() const {
    return msg.sender;
};

const std::string& Message::getTarget() const {
    return msg.target;
};

const time_t& Message::getTimestamp() const {
    return msg.timestamp;
};
