#pragma once
#include <string>

class Entry
{
    std::string name;
    std::string text;
    time_t created;
public:
    Entry(std::string name, std::string text, time_t created) : 
          name(name),
          text(text),
          created(created) {
    }

    std::string getName() const {
        return name;
    }

    std::string getText() const {
        return text;
    }

    time_t getCreated() const {
        return created;
    }
};

std::ostream& operator<<(std::ostream& out, const Entry& entry);