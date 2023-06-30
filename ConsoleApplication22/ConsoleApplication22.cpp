#include <iostream>
#include <string>
#include "Storage.h"
#include "Entry.h"

using namespace std;



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

    // �������� ���������, �������� ����������
    // � ���� ������
    Storage storage("database.txt");
    storage.load();

    mainloop(storage);

    // ��������� ������ � ����
    storage.save();

    // ��������� ���� � �������� � ��������
    system("notepad.exe database.txt");
    return 0;
}