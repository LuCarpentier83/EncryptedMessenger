#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>

typedef struct {
    std::string sender;
    std::string target;
    std::string content;
    time_t timestamp = time(nullptr);
} Message_t;

class Message {
public:
    Message(const Message_t& msg);
    const std::string& getSender() const;
    const std::string& getTarget() const;
    const std::string& getContent() const;
    const time_t& getTimestamp() const;
private:
    Message_t msg;
};

#endif //MESSAGE_H
