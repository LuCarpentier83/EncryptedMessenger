#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>
#include <memory>
#include <vector>

typedef struct Message {
    std::string sender;
    std::string target;
    std::string content;
    time_t timestamp = time(nullptr);
} message_t;

typedef struct EncryptedMessage {
    std::string receiver_id;
    std::string sender_id;
    std::string cipher_text;
} encrypted_message_t;

#endif //MESSAGE_H
