#pragma once
#include "Message.h"
#include <iostream>

Message::Message(const Message_t& msg) {
    this->msg = msg;
}

const std::string& Message::getContent() const {
    std::cout << msg.content << std::endl;
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
