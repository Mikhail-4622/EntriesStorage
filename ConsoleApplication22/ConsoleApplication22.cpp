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
        functions["list"] = [](AppUI* app, Storage& storage) {
            vector<string> names = storage.getEntriesNames();
            cout << "Сохранённые записи ";
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
            cout << "название: ";
            getline(cin, name);
            Entry* entry = storage.getEntry(name);
            if (entry == nullptr) {
                cout << "запись не найдена" << endl;
                return;
            }
            cout << "Запись '" << name << "':" << endl;
            cout << entry->getText() << endl;
            cout << "дата: " << entry->getCreated() << endl;
        };
        functions["delete"] = [](AppUI* app, Storage& storage) {
            string name;
            cout << "название: ";
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