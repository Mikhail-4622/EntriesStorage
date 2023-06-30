#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "Storage.h"
#include "Entry.h"

using namespace std;

class AppUI;


typedef function<void(AppUI*, Storage&)> appfunc;

class AppUI {
    // ���������� ��������� ��� �������� �������
    Entry* create_entry() {
        string name;
        string text;

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Text: ";
        getline(cin, text);

        // �������� ����� �������� ������
        time_t created = time(0);
        return new Entry(name, text, created);
    }
    void printGuide() {
        cout << "��������� �������:" << endl;
        cout << "  list   - ������ ���������� �������" << endl;
        cout << "  add    - ������� ������" << endl;
        cout << "  show   - �������� ������" << endl;
        cout << "  delete - ������� ������" << endl;
        cout << "  exit   - ��������� ���������" << endl;
    }

    Storage& storage;
    unordered_map<string, appfunc> functions;
public:
    AppUI(Storage& storage) : storage(storage) {
        functions["list"] = [](AppUI* app, Storage& storage) {
            vector<string> names = storage.getEntriesNames();
            cout << "���������� ������ ";
            cout << names.size() << ":" << endl;
            for (string name : names) {
                cout << "  " << name << endl;
            }
        };
        functions["add"] = [this](AppUI* app, Storage& storage) {
            storage.add(create_entry());
            storage.save();
        };
        functions["show"] = [](AppUI* app, Storage& storage) {
            string name;
            cout << "��������: ";
            getline(cin, name);
            Entry* entry = storage.getEntry(name);
            if (entry == nullptr) {
                cout << "������ �� �������" << endl;
                return;
            }
            cout << "������ '" << name << "':" << endl;
            cout << entry->getText() << endl;
            cout << "����: " << entry->getCreated() << endl;
        };
        functions["delete"] = [](AppUI* app, Storage& storage) {
            string name;
            cout << "��������: ";
            getline(cin, name);

        };
    }

    void mainloop() {
        printGuide();
        while (true) {
            string cmd;
            cout << "> ";
            getline(cin, cmd);

            auto found = functions.find(cmd);
            if (found != functions.end()) {
                found->second(this, storage);
            }
            else {
                cout << "����� ������� �� ����������" << endl;
            }
        }
    }
};


int main() {
    setlocale(LC_ALL, "");

    // �������� ���������, �������� ����������
    // � ���� ������
    Storage storage("database.txt");
    storage.load();

    AppUI app(storage);
    app.mainloop();

    // ��������� ������ � ����
    storage.save();

    // ��������� ���� � �������� � ��������
    system("notepad.exe database.txt");
    return 0;
}