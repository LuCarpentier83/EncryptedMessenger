#pragma once
#include <iostream>

#include "Message.h"
#include <cstring>

using namespace std;

int main() {


    Message_t message;
    message.content = "Hello Lucas";
    message.sender = "Maha";
    message.target = "Lucas";

    std::shared_ptr<Message> ptr_msg = std::make_shared<Message>(message);

    std::cout << ptr_msg->getContent() << std::endl;
    return 0;
}