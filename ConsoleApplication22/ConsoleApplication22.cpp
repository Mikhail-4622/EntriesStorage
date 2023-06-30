#include <iostream>
#include <string>
#include "Storage.h"
#include "Entry.h"

using namespace std;



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

void mainloop(Storage& storage) {
    printGuide();
    while (true) {
        string cmd;
        cout << "> ";
        getline(cin, cmd);
    }
}


int main() {
    setlocale(LC_ALL, "");

    // Создание хранилища, загрузка сохранённых
    // в файл данных
    Storage storage("database.txt");
    storage.load();

    mainloop(storage);

    // Сохраняем записи в файл
    storage.save();

    // Открываем файл с записями в блокноте
    system("notepad.exe database.txt");
    return 0;
}