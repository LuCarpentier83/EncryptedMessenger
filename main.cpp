#include <iostream>

#include "Message.h"
#include <cstring>

using namespace std;

int main() {


    Message_t message;
    message.content = "Hello Lucas";
    message.sender = "Maha";
    message.target = "Lucas";

    Message msg(message);
    msg.getContent();
    return 0;
}