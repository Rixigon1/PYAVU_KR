#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>

#include "utils.h"
#include "menuFunctions.h"

using namespace std;



TUI::TUI() {
    table = nullptr;
}

TUI::~TUI() {
    if(table) delete table;
}


int TUI::showMainMenu() {
    string choice;
    if(!table) {
        cout << "Добро пожаловать в приложение учета книжного фонда." << endl
             << "Для выхода нажмите клавишу e на английской раскладке" << endl << endl
             << "Для начала работы введите размер таблицы" << endl << endl;
        getline(cin, choice);

        size_t pos;
        // pos = choice.find_first_not_of(" \t");
        if(int code = eraseSpaces(choice); code != 0) { return code; }
        // if(pos == string::npos) {
        //     return 0xFFFF; // Введена пустая строка
        // }
        // else {
        //     choice = choice.substr(pos);

        //     pos = choice.find_last_not_of(" \t");
        //     if(pos != string::npos) {
        //         choice = choice.substr(0, pos+1);
        //     }
        // }

        if(choice == "e") return 0xDEAD; // Выбран выход из приложения

        pos = choice.find_first_not_of("0123456789");
        if(pos != string::npos) return 0xFFFE; // Введено не число

        int iChoice = stoi(choice);
        if(iChoice == 0) return 0xFFF3;
        table = new bookTable(iChoice);
        system("cls");
    }
    cout << "Выберете желаемое действие: " << endl
         << "1) Добавить новую книгу" << endl
         << "2) Редактировать книгу" << endl
         << "3) Удалить книгу" << endl
         << "4) Поиск книги" << endl
         << "5) Изменить статус книги" << endl
         << "6) Вывести на экран список всех книг" << endl
         << "7) Вывести на экран список доступных книг" << endl
         << "8) Вывести на экран список выданных книг" << endl
         << "9) Загрузить список книг из файла" << endl
         << "10) Сохранить список книг в файл" << endl
         << "11) Справка о работе приложения" << endl
         << "12) Дополнительные функции" << endl
         << "e) Выйти из приложения" << endl << endl;
    cout << ">>";
    getline(cin, choice);

    size_t pos;
    if(int code = eraseSpaces(choice); code != 0) return code;
    // pos = choice.find_first_not_of(" \t");
    // if(pos == string::npos) {
    //     return 0xFFFF; // Введена пустая строка
    // }
    // else {
    //     choice = choice.substr(pos);

    //     pos = choice.find_last_not_of(" \t");
    //     if(pos != string::npos) {
    //         choice = choice.substr(0, pos+1);
    //     }
    // }

    if(choice == "e") return 0xDEAD; // Выбран выход из приложения

    pos = choice.find_first_not_of("0123456789");
    if(pos != string::npos) return 0xFFFE; // Введено не число

    int iChoice = stoi(choice);
    if(iChoice > 12) return 0xFFFD; // Выбран не существующий пункт меню

    return iChoice;
}

int TUI::chooseSParam(searchParam& sParam, string& buf) {
    bool exitChoosing = false;
    bool retMenu = false;
    int eCode = 0;
    string choice;
    int iChoice;
    size_t pos;
    while(!retMenu) {
        while(!exitChoosing) {
            system("cls");
            errorProcessor(eCode);
            cout << "Выберете параметр по которому требуется провести поиск." << endl
                 << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры: " << endl
                 << "1) Инвентарный номер книги" << endl
                 << "2) Имя автора книги" << endl
                 << "3) Название книги" << endl
                 << ">>";
            getline(cin, choice);
            eCode = eraseSpaces(choice);
            if(eCode != 0) continue;
            if(choice == "e") {exitChoosing = true; continue;}
            pos = choice.find_first_not_of("0123456789");
            if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число
            iChoice = stoi(choice);
            if(iChoice > 3) {eCode = 0xFFFD; continue;} // Выбран не существующий пункт меню
            switch (iChoice) {
            case 1:
                sParam = ID;
                exitChoosing = true;
                break;
            case 2:
                sParam = AUTHOR;
                exitChoosing = true;
                break;
            case 3:
                sParam = TITLE;
                exitChoosing = true;
                break;
            default:
                break;
            }
        }
        if(choice == "e") return 0xAAA1;
        exitChoosing = false;
        while(!exitChoosing) {
            system("cls");
            errorProcessor(eCode);
            cout << "Введите значение параметра, по которому будет произведен поиск." << endl
                 << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры: " << endl
                 << ">>";
            getline(cin, choice);
            eCode = eraseSpaces(choice);
            if(eCode != 0) continue;
            if(choice == "e") {exitChoosing = true; eCode = 0xAAA1; continue;}
            buf = choice;
            exitChoosing = true;
            retMenu = true;
        }
    }
    return eCode;
}

int TUI::chooseState(state& newState) {
    int eCode = 0;
    bool exitChoosing = false;
    string choice;
    int iChoice;
    size_t pos;
    while(!exitChoosing) {
        system("cls");
        errorProcessor(eCode);
        cout << "Выберете новое состояние книги" << endl
             << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры: " << endl
             << "1) Выдана" << endl
             << "2) На складе" << endl << endl
             << ">>";
        getline(cin, choice);
        eCode = eraseSpaces(choice);
        if(eCode != 0) continue;
        if(choice == "e") {exitChoosing = true; eCode = 0xAAA3; continue;}
        pos = choice.find_first_not_of("0123456789");
        if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число
        iChoice = stoi(choice);
        if(iChoice > 3) {eCode = 0xFFFD; continue;} // Выбран не существующий пункт меню
        switch (iChoice) {
        case 1:
            newState = GIVEN;
            exitChoosing = true;
            break;
        case 2:
            newState = INSTOCK;
            exitChoosing = true;
            break;
        default:
            break;
        }
    }
    return eCode;
}

int TUI::showAdditionalMainMenu() {
    string choice;
    cout << "Выберете желаемое действие: " << endl
         << "1) Вывести число занятых ячеек таблицы книг" << endl
         << "2) Вывести максимальную длину цепочки среди ячеек в таблице" << endl
         << "3) Вернуться" << endl << endl;
    cout << ">>";
    getline(cin, choice);

    if(int code = eraseSpaces(choice); code != 0) return code;

    size_t pos;
    // pos = choice.find_first_not_of(" \t");
    // if(pos == string::npos) {
    //     return 0xFFFF; // Введена пустая строка
    // }
    // else {
    //     choice = choice.substr(pos);

    //     pos = choice.find_last_not_of(" \t");
    //     if(pos != string::npos) {
    //         choice = choice.substr(0, pos+1);
    //     }
    // }

    pos = choice.find_first_not_of("0123456789");
    if(pos != string::npos) return 0xFFFE; // Введено не число

    int iChoice = stoi(choice);
    if(iChoice > 3) return 0xFFFD; // Выбран не существующий пункт меню

    return iChoice;
}

int TUI::chooseFile(string &fileName, bool toWrite) {
    bool checkExit = 0;
    int eCode = 0;
    fstream fid;
    string checkID;
    int t;
    string menuChooser;
    int iChoice;
    size_t pos;
    bool exitChoosing;

    // Проверка имени файла
    cout << "\nДля возвращения в главное меню нажмите e на английской раскладке клавиатуры"  << endl << endl;
    cout << "Введите имя файла, " << (toWrite ? "в который будет произведена запись" : "из которого будет произведено чтение") << " без расширения (если расширение будет присутствовать, то оно будет изменено на txt): ";
    getline(cin, fileName);

    if(fileName == "e") { // Проверка на команду выхода
        fileName = "";
        eCode = 0xAAA2; // Выход без уведомления пользователя
    }
    else if(fileName.find_first_of("/:*,\"<>/\\") != fileName.npos) { // Проверка на наличие в имени файла специальных символов
        fileName = "";
        eCode = 0xFFF6;
    }
    else {
        // Проверки на наличие пробелов в начале и конце имени файла
        t = fileName.find_first_not_of(" ");
        if (t != fileName.npos && t != 0) {
            fileName.erase(0, t);
        }

        t = fileName.find_last_not_of(" ");

        if (t != fileName.npos && t != 0) {
            fileName.erase(t+1, fileName.length());
        }

        // В случае наличия расширения в имени файла, оно удаляется
        t = fileName.find_last_of(".");
        if (t != fileName.npos && t != 0) {
            fileName.erase(t, fileName.length());
        }

        // Проверка на нулевую длину имени файла
        if(fileName.length() == 0) {
            eCode = 0xFFF5;
        }
        else {
            // Добавление расширения .txt к имени файла, проверка файла на существование
            fileName += ".txt";
            if(toWrite) {
                fid.open(fileName, ios::in);
                if (fid.is_open()) {
                    system("cls");
                    cout << "Файл с таким именем уже существует! Перезаписать файл?" << endl
                         << "1) Да" << endl
                         << "2) Нет" << endl;
                    getline(cin, menuChooser);
                    eCode = eraseSpaces(menuChooser);
                    if(eCode != 0) return eCode;
                    if(menuChooser == "e") {return 0xAAA2;}
                    pos = menuChooser.find_first_not_of("0123456789");
                    if(pos != string::npos) {return 0xFFFE;} // Введено не число
                    iChoice = stoi(menuChooser);
                    if(iChoice > 2 || iChoice == 0) {return 0xFFFD;} // Выбран не существующий пункт меню

                    switch (iChoice) {
                    case 1:
                        fid.close();
                        fid.open(fileName, ios::trunc | ios::out);
                        fid.close();
                        break;
                    case 2:
                        fid.close();
                        return 1;
                        break;
                    default:
                        break;
                    }
                }
                fid.close();
            }
            else {
                fid.open(fileName, ios::in);
                if (!fid.is_open()) {
                    eCode = 0xFFF7;
                    fid.close();
                }
                fid.close();
            }
        }
    }
    return eCode;
}

int TUI::workWithFile(bool toWrite) {
    string fileName = "";
    int eCode = 0;
    bool exitWork = false;
    while(!exitWork) {
        system("cls");
        errorProcessor(eCode);
        eCode = chooseFile(fileName, toWrite);
        if(eCode == 0xAAA2) return eCode;
        if(eCode != 0) continue;


        if(toWrite) {
            eCode = table->writeToFile(fileName);
        }
        else {
            if(!table->isEmpty()) {
                int tSize = table->getSize();
                delete table;
                table = new bookTable(tSize);
            }
            eCode = table->readFromFile(fileName);
        }
        exitWork = true;

    }
    return 0;
}


// void TUI::errorProcessor(int eCode) {
//     switch (eCode) {
//     case 0:
//         break;
//     case 0xFFFF:
//         cout << "Ошибка: введена пустая строка!" << endl << endl;
//         break;
//     case 0xFFFE:
//         cout << "Ошибка: введено не число!" << endl << endl;
//         break;
//     case 0xFFFD:
//         cout << "Ошибка: выбран не существующий пункт меню!" << endl << endl;
//         break;
//     case 0xFFFA:
//         cout << "Ошибка: удаляемая книга отсутствует в списке книг!" << endl << endl;
//         break;
//     case 0xFFF9:
//         cout << "Ошибка: искомая книга не найдена в списке!" << endl << endl;
//         break;
//     case 0xFFF8:
//         cout << "Ошибка: книга с этим инвентарным номером уже существует!" << endl << endl;
//         break;
//     case 0xFFF7:
//         cout << "Ошибка: выбранный файл не возможно открыть!" << endl << endl;
//         break;
//     case 0xFFF6:
//         cout << "Ошибка: в имени файла содержатся недопустимые символы (/:*,\"<>/\\)!" << endl << endl;
//         break;
//     case 0xFFF5:
//         cout << "Ошибка: имя файла не было введено!" << endl << endl;
//         break;
//     case 0xFFF4:
//         cout << "Ошибка: невозможно открыть файл!" << endl << endl;
//         break;
//     case 0xFFF3:
//         cout << "Ошибка: создание таблицы размерностью 0 невозможно!" << endl << endl;
//         break;
//     case 0xFFF2:
//         cout << "Ошибка: новый статус книги совпадает с текущим!" << endl << endl;
//         break;
//     case 0xAAA0:
//         cout << "Формирование нового экземпляра книги отменено." << endl << endl;
//         break;
//     case 0xAAA1:
//         cout << "Поиск книги отменён." << endl << endl;
//         break;
//     case 0xAAA2:
//         cout << "Ввод имени файла отменен." << endl << endl;
//         break;
//     case 0xAAA3:
//         cout << "Изменение статуса книги отменено." << endl << endl;
//         break;
//     case 0xAAA4:
//         cout << "Редактирование параметров книги отменено." << endl << endl;
//         break;
//     default:
//         break;
//     }
// }

int TUI::exec() {
    int eCode = 0;
    while(!exitApp) {
        // Обработка eCode
        errorProcessor(eCode);
        eCode = showMainMenu();
        // cout << endl << eCode << endl;x
        switch (eCode) {
        case 1: {
            system("cls");
            book* newBook = new book;
            eCode = newBook->createBook(table);
            if(eCode == 0) eCode = table->addBook(newBook);
            if(eCode != 0) delete newBook;
            system("cls");
            break;
        }
        case 2: {
            // Не реализовано
            system("cls");
            string sID;
            cout << "Введите инвентарный номер книги, которую требуется отредактировать: " << endl
                 << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры" << endl
                 << ">>";
            getline(cin, sID);
            eCode = eraseSpaces(sID);
            if(eCode != 0) continue;
            if(sID == "e") {eCode = 0x0; continue;}
            bookList* sBookList = table->searchBook(sID, ID);
            if(sBookList == nullptr) {eCode= 0xFFF9; continue;}

            bool exitEdit1 = false;

            string sep(30, '-');
            string buffer;
            int iBuffer;
            while(!exitEdit1) {
                system("cls");
                errorProcessor(eCode);
                cout << "Текущие параметры книги:" << endl
                     << *(sBookList->getNextBookList()->getBook()) << endl
                     << sep << endl << endl;
                cout << "Выберете редактируемый параметр: " << endl
                     << "1) Имя автора" << endl
                     << "2) Название книги" << endl
                     << "3) Год выпуска книги" << endl << endl
                     << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры" << endl
                     << ">>";
                getline(cin, buffer);
                eCode = eraseSpaces(buffer);
                if(eCode != 0) continue;
                if(buffer == "e") {exitEdit1 = true; continue;}
                size_t pos;
                pos = buffer.find_first_not_of("0123456789");
                if(pos != string::npos) {eCode = 0xFFFE; continue;}
                iBuffer = stoi(buffer);
                if(iBuffer == 0) {eCode = 0xFFFD; continue;}
                bool exitEdit2 = false;
                switch (iBuffer) {
                case 1:
                    while(!exitEdit2) {
                        system("cls");
                        errorProcessor(eCode);
                        cout << "Введите имя автора"
                             << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры" << endl
                             << ">>";
                        getline(cin, buffer);
                        eCode = eraseSpaces(buffer);
                        if(eCode != 0) continue;
                        if(buffer == "e") {exitEdit1 = true; exitEdit2 = true; continue;};
                        sBookList->getNextBookList()->getBook()->setAuthor(buffer);
                        exitEdit2 = true;
                    }
                    break;
                case 2:
                    while(!exitEdit2) {
                        system("cls");
                        errorProcessor(eCode);
                        cout << "Введите название книги"
                             << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры" << endl
                             << ">>";
                        getline(cin, buffer);
                        eCode = eraseSpaces(buffer);
                        if(eCode != 0) continue;
                        if(buffer == "e") {exitEdit1 = true; exitEdit2 = true; continue;};
                        sBookList->getNextBookList()->getBook()->setTitle(buffer);
                        exitEdit2 = true;
                    }
                    system("cls");
                    break;
                case 3:
                    while(!exitEdit2) {
                        system("cls");
                        errorProcessor(eCode);
                        cout << "Введите год издания книги"
                             << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры" << endl
                             << ">>";
                        getline(cin, buffer);
                        eCode = eraseSpaces(buffer);
                        if(eCode != 0) continue;
                        if(buffer == "e") {exitEdit1 = true; exitEdit2 = true; continue;};
                        size_t pos;
                        pos = buffer.find_first_not_of("0123456789");
                        if(pos != string::npos) {eCode = 0xFFFE; continue;}
                        iBuffer = stoi(buffer);
                        if(iBuffer > 2026 || iBuffer < 1700) {eCode = 0xFFFC; continue;}
                        sBookList->getNextBookList()->getBook()->setYearOfRelease(iBuffer);
                        exitEdit2 = true;
                    }
                    system("cls");
                    break;
                default:
                    break;
                }
                system("cls");
            }
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            string sID;
            cout << "Введите инвентарный номер книги, которую требуется удалить: " << endl
                 << ">>";
            getline(cin, sID);
            eCode = eraseSpaces(sID);
            if(eCode != 0) continue;
            eCode = table->deleteBook(sID);
            system("cls");
            break;
        }
        case 4: {
            searchParam sParam;
            string buf;
            bookList* sBookList;
            eCode = chooseSParam(sParam, buf);
            if(eCode == 0) {
                sBookList = table->searchBook(buf, sParam);
                if(sBookList == nullptr) eCode = 0xFFF9;
                else {
                    cout << "Сведения об искомой книге: " << endl
                         << *(sBookList->getNextBookList()->getBook()) << endl << endl
                         << "Нажмите любую клавишу для возвращения в главное меню" << endl
                         << ">>";
                    getch();
                }
            }
            system("cls");
            break;
        }
        case 5: {
            system("cls");
            state newState;
            string sID;
            bookList* sBookList;
            cout << "Введите инвентарный номер книги, статус которой требуется изменить: " << endl
                 << ">>";
            getline(cin, sID);
            eCode = eraseSpaces(sID);
            if(eCode != 0) continue;
            eCode = chooseState(newState);
            if(eCode != 0) continue;
            sBookList = table->searchBook(sID, ID);
            if(sBookList == nullptr) {eCode = 0xFFF9; continue;}
            if(sBookList->getNextBookList()->getBook()->getState() == newState) {eCode = 0xFFF2; system("cls"); continue;}

            sBookList->getNextBookList()->getBook()->setState(newState);
            system("cls");
            break;
        }
        case 6:
            system("cls");
            table->display();
            cout << endl << "Нажмите любую клавишу чтобы продолжить." << endl
                 << ">>";
            getch();
            system("cls");
            break;
        case 7:
            system("cls");
            table->display(INSTOCK);
            cout << endl << "Нажмите любую клавишу чтобы продолжить." << endl
                 << ">>";
            getch();
            system("cls");
            break;
        case 8:
            system("cls");
            table->display(GIVEN);
            cout << endl << "Нажмите любую клавишу чтобы продолжить." << endl
                 << ">>";
            getch();
            system("cls");
            break;
        case 9: {
            system("cls");
            eCode = 0;
            bool exitReading = false;
            bool bEmpty = table->isEmpty();
            string choice;
            int iChoice;
            size_t pos;
            if(!bEmpty and !table->isSaved()) {
                system("cls");
                while(!exitReading) {
                    errorProcessor(eCode);
                    cout << "Текущая таблица не сохранена. Выберете действие над таблицей:" << endl
                         << "Для возвращения в главное меню нажмите e на английской раскладке клавиатуры: " << endl
                         << "1) Сохранить текущую таблицу и открыть новую таблицу из файла" << endl
                         << "2) Удалить текущую таблицу и открыть новую таблицу из файла" << endl << endl
                         << ">>";
                    getline(cin, choice);
                    eCode = eraseSpaces(choice);
                    if(eCode != 0) continue;
                    if(choice == "e") {exitReading = true; eCode = 0xAAA3; continue;}
                    pos = choice.find_first_not_of("0123456789");
                    if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число
                    iChoice = stoi(choice);
                    if(iChoice >= 3 || iChoice == 0) {eCode = 0xFFFD; continue;} // Выбран не существующий пункт меню
                    switch (iChoice) {
                    case 1: {
                        eCode = workWithFile(true);
                        if(eCode != 0) {exitReading = true; continue;}
                        int tSize = table->getSize();
                        delete table;
                        table = new bookTable(tSize);
                        exitReading = true;
                        break;
                    }
                    case 2: {
                        int tSize = table->getSize();
                        delete table;
                        table = new bookTable(tSize);
                        exitReading = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
            if(eCode != 0) continue;
            eCode = workWithFile(false);
            system("cls");
            if(eCode == 0) cout << "Чтение из файла выполнено успешно!" << endl << endl;
            break;
        }
        case 10: {
            system("cls");
            bool bEmpty = table->isEmpty();
            if(bEmpty) {eCode = 0xFFF1; continue;}
            eCode = workWithFile(true);
            system("cls");
            if(eCode == 0) cout << "Запись в файл выполнена успешно!" << endl << endl;
            break;
        }
        case 11:
            system("cls");
            cout << "To be continued" << endl;
            getch();
            system("cls");
            break;
        case 12:
            system("cls");
            errorProcessor(eCode);
            eCode = showAdditionalMainMenu();
            // cout << endl << eCode << endl;
            // getch();
            switch (eCode) {
            case 1:
                system("cls");
                table->displayBucketCount();
                cout << endl << "Нажмите любую клавишу чтобы продолжить." << endl
                     << ">>";
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                table->displayLongestBucketLength();
                cout << endl << "Нажмите любую клавишу чтобы продолжить." << endl
                     << ">>";
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                eCode = 0;
                break;
            default:
                break;
            }
            system("cls");
            break;
        case 0xDEAD:
            exitApp = true;
            break;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}




