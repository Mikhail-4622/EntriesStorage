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



int main() {
    setlocale(LC_ALL, "");

    // Создание хранилища, загрузка сохранённых
    // в файл данных
    Storage storage("database.txt");
    storage.load();

    // Создаём и добавляем запись в хранилище
    storage.add(create_entry());

    // Сохраняем записи в файл
    storage.save();

    // Открываем файл с записями в блокноте
    system("notepad.exe database.txt");
    return 0;
}