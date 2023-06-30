#include <fstream>
#include <iostream>
#include <string>
#include "Storage.h"
#include "Entry.h"

using namespace std;

Storage::~Storage() {
    for (auto pair : entries) {
        delete pair.second;
    }
    entries.clear();
}

// Добавление записи в хранилище
void Storage::add(Entry* entry) {
    string name = entry->getName();
    auto found = entries.find(name);
    if (found != entries.end()) {
        delete found->second;
    }
    entries[name] = entry;
}

// Чтение записей из файла
void Storage::load() {
    ifstream input(file);
    int count;
    input >> count;
    input.ignore(1, '\n');
    for (int i = 0; i < count; i++) {
        string name;
        string text;
        time_t created;
        getline(input, name);
        getline(input, text);
        input >> created;
        input.ignore(1, '\n');
        add(new Entry(name, text, created));
    }
}

// Сохранение записей в файл
void Storage::save() {
    ofstream output(file);
    if (!output.is_open()) {
        throw "could not to open file";
    }
    output << entries.size() << "\n";
    for (auto pair : entries) {
        output << *pair.second;
    }
    output.close();
}

// Получение записи по названию
Entry* Storage::getEntry(std::string name) const {
    auto found = entries.find(name);
    if (found != entries.end()) {
        return found->second;
    }
    return nullptr;
}
// Получение списка названий записей в хранилище
std::vector<std::string> Storage::getEntriesNames() const {
    std::vector<std::string> names;
    for (auto pair : entries) {
        names.push_back(pair.first);
    }
    return names;
}