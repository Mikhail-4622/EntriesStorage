#include "Entry.h"
#include <iostream>

using namespace std;

// ������� ������ ������ � ����� ������
ostream& operator<<(ostream& out, const Entry& entry) {
    out << entry.getName() << "\n";
    out << entry.getText() << "\n";
    out << entry.getCreated() << "\n";
    return out;
}