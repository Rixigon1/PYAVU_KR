#include <iostream>
#include <windows.h>

#include "menuFunctions.h"
#include "fileFunctions.h"
#include "dataStructures.h"

using namespace std;

int main()
{
    // std::setlocale(LC_ALL, "Russian");
    // std::setlocale(LC_ALL, ".UTF-8");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TUI ui;
    ui.exec();
}
