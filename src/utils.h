#pragma once

#include <iostream>
#include <string>

using namespace std;

// Функция удаления пробелов начале и конце строки
int eraseSpaces(string& str);

// Функция обработки кода ошибки
void errorProcessor(int eCode, int iChoice = 0);
