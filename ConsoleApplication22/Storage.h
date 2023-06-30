#pragma once
#include <string>
#include <unordered_map>

class Entry;

// ��������� �������
class Storage
{
    std::unordered_map<std::string, Entry*> entries;
    std::string file;
public:
    Storage(std::string file) : file(file) {
    }

    ~Storage();

    void add(Entry* entry);
    void load();
    void save();
};

