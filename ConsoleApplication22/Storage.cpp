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

// ���������� ������ � ���������
void Storage::add(Entry* entry) {
    string name = entry->getName();
    auto found = entries.find(name);
    if (found != entries.end()) {
        delete found->second;
    }
    entries[name] = entry;
}

// ������ ������� �� �����
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

// ���������� ������� � ����
void Storage::save() {
    ofstream output(file);
    if (!output.is_open()) {
        throw "could not to open file";
    }
    output << entries.size() << "\n";
    for (auto pair : entries) {
        output << *pair.second;
    }
}