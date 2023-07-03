#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Entry;

// Хранилище записей
class Storage
{
    std::unordered_map<std::string, Entry*> entries;
    std::string file;
public:
    Storage(std::string file) : file(file) {
    }

    ~Storage();

    void add(Entry* entry);
    bool remove(std::string name);
    void load();
    void save();

    Entry* getEntry(std::string name) const;
    std::vector<std::string> getEntriesNames() const;

};

