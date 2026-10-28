#include <windows.h>

#include "menuFunctions.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TUI ui;
    ui.exec();
}
