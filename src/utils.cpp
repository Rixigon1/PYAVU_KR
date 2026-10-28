#pragma once

#include <string>

#include "utils.h"

using namespace std;

// Функция удаления пробелов начале и конце строки
int eraseSpaces(string& str) {
    size_t pos;
    pos = str.find_first_not_of(" \t");
    if(pos == string::npos) {
        return 0xFFFF; // Введена пустая строка
    }
    else {
        str = str.substr(pos);

        pos = str.find_last_not_of(" \t");
        if(pos != string::npos) {
            str = str.substr(0, pos+1);
        }
    }
    return 0;
}

// Функция обработки кода ошибки
void errorProcessor(int eCode, int iChoice) {
    switch (eCode) {
        // Уведомления о корректном завершении работы выбранного действия над хеш-таблицей книг
        case 0:
            switch (iChoice) {
                case 1:
                    cout << "Новая книга успешно добавлена!" << endl << endl;
                    break;
                case 2:
                    cout << "Книга успешно отредактирована!" << endl << endl;
                    break;
                case 3:
                    cout << "Книга успешно удалена!" << endl << endl;
                    break;
                case 5:
                    cout << "Статус книги успешно изменен!" << endl << endl;
                    break;
                case 9:
                    cout << "Чтение из файла выполнено успешно!" << endl << endl;;
                    break;
                case 10:
                    cout << "Запись в файл выполнена успешно!" << endl << endl;
                    break;
                default:
                    break;
                }
            break;

        // Критические ошибки, при которых дальнейшее выполнение программы невозможно
        case 0xFFFF:
            cout << "Ошибка: введена пустая строка!" << endl << endl;
            break;
        case 0xFFFE:
            cout << "Ошибка: введено не число!" << endl << endl;
            break;
        case 0xFFFD:
            cout << "Ошибка: выбран не существующий пункт меню!" << endl << endl;
            break;
        case 0xFFFA:
            cout << "Ошибка: удаляемая книга отсутствует в списке книг!" << endl << endl;
            break;
        case 0xFFF9:
            cout << "Ошибка: искомая книга не найдена в списке!" << endl << endl;
            break;
        case 0xFFF8:
            cout << "Ошибка: книга с этим инвентарным номером уже существует!" << endl << endl;
            break;
        case 0xFFF7:
            cout << "Ошибка: выбранный файл не возможно открыть!" << endl << endl;
            break;
        case 0xFFF6:
            cout << "Ошибка: в имени файла содержатся недопустимые символы (/:*,\"<>/\\)!" << endl << endl;
            break;
        case 0xFFF5:
            cout << "Ошибка: имя файла не было введено!" << endl << endl;
            break;
        case 0xFFF4:
            cout << "Ошибка: невозможно открыть файл!" << endl << endl;
            break;
        case 0xFFF3:
            cout << "Ошибка: создание таблицы размерностью 0 невозможно!" << endl << endl;
            break;
        case 0xFFF2:
            cout << "Ошибка: новый статус книги совпадает с текущим!" << endl << endl;
            break;
        case 0xFFF1:
            cout << "Ошибка: невозможно совершить выбранную операцию с пустой таблицей!" << endl << endl;
            break;

        // Ошибки, при которых дальнейшее выполнение работы программы возможно
        case 0xEEEE:
            cout << "Ошибка: некоторые инвентарные номера в файле повторяются и не были записаны в таблицу!"  <<  endl << endl;
            break;

        // Уведомления пользователя об отмене выбранного им ранее действия
        case 0xAAA0:
            cout << "Формирование нового экземпляра книги отменено." << endl << endl;
            break;
        case 0xAAA1:
            cout << "Поиск книги отменён." << endl << endl;
            break;
        case 0xAAA2:
            cout << "Ввод имени файла отменен." << endl << endl;
            break;
        case 0xAAA3:
            cout << "Изменение статуса книги отменено." << endl << endl;
            break;
        case 0xAAA4:
            cout << "Редактирование параметров книги отменено." << endl << endl;
            break;
        case 0xAAA5:
            cout << "Чтение книги из файла отменено." << endl << endl;
            break;
        case 0xAAA6:
            cout << "Удаление книги из таблицы отменено." << endl << endl;
            break;
        default:
            break;
    }
}