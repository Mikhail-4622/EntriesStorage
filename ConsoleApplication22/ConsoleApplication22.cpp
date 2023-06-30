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
    // Консольный интерфейс для создания записей
    Entry* create_entry() {
        string name;
        string text;

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Text: ";
        getline(cin, text);

        // Получаем время создания записи
        time_t created = time(0);
        return new Entry(name, text, created);
    }
    void printGuide() {
        cout << "Доступные команды:" << endl;
        cout << "  list   - список сохранённых записей" << endl;
        cout << "  add    - создать запись" << endl;
        cout << "  show   - показать запись" << endl;
        cout << "  delete - удалить запись" << endl;
        cout << "  exit   - завершить программу" << endl;
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
                cout << "такой команды не существует" << endl;
            }
        }
    }
};


int main() {
    setlocale(LC_ALL, "");

    // Создание хранилища, загрузка сохранённых
    // в файл данных
    Storage storage("database.txt");
    storage.load();

    AppUI app(storage);
    app.mainloop();

    // Сохраняем записи в файл
    storage.save();

    // Открываем файл с записями в блокноте
    system("notepad.exe database.txt");
    return 0;
}