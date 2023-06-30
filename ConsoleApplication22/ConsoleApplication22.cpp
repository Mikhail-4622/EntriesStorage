#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "Storage.h"
#include "Entry.h"

using namespace std;

class AppUI;

typedef function<void(AppUI*, Storage&)> appfunc;

void test(AppUI* app, Storage& storage) {
    cout << "Hello, World" << endl;
}

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
        functions["test"] = test;
        int a = 42;
        functions["test2"] = [a](AppUI* app, Storage& storage) {
            cout << "Test2 " << a << endl;
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