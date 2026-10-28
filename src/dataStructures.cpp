#include "dataStructures.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <utility>
#include <sstream>
#include <unordered_map>

#include "utils.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------
// Определение методов класса книги

// Конструктор класса book
book::book(string ID, string title, string author, int yearOfRelease, state curState) {
    this->ID = ID;
    this->title = title;
    this->author = author;
    this->yearOfRelease = yearOfRelease;
    this->curState = curState;
}

// Методы установки значения поля экземпляра класса
void book::setTitle(string title) {
    this->title = title;
}

void book::setAuthor(string author) {
    this->author = author;
}

void book::setYearOfRelease(int yearOfRelease) {
    this->yearOfRelease = yearOfRelease;
}

void book::setState(state curState) {
    this->curState = curState;
}

// Методы получения значения поля экземпляра класса
string book::getID() const  {
    return this->ID;
}

string book::getTitle() const  {
    return this->title;
}

string book::getAuthor() const  {
    return this->author;
}

int book::getYearOfRelease() const  {
    return this->yearOfRelease;
}

state book::getState() const  {
    return this->curState;
}

// Функция создания и заполнения экземпляра класса book по средством ввода с клавиатуры
int book::createBook(bookTable* bTable) {
    int eCode = 0;
    const int n = 5;
    searchParam eParams[n] = {searchParam::ID, searchParam::TITLE, searchParam::AUTHOR, searchParam::YEAROFRELEASE, searchParam::CURSTATE};
    bool exitEntering = false;
    int i = 0;
    // Цикл ввода значений полей с клавиатуры
    while(!exitEntering) {
        system("cls");
        // Обработка кода ошибки выполнения
        errorProcessor(eCode);

        cout << "Создание экземпляра записи книги" << endl
             << "Для выхода нажмите клавишу e на английской раскладке" << endl;
        searchParam param = eParams[i];
        switch (param) {
            case searchParam::ID: {
                string buf;
                cout << "Введите инвертарный номер книги: ";
                getline(cin, buf);
                eCode = eraseSpaces(buf);
                if(eCode != 0) continue;
                if(buf == "e") {
                    exitEntering = true;
                    eCode = 0xAAA0; // Отмена создания записи об экземпляре книги
                    continue;
                }

                if((bTable->searchBook<string>(buf, searchParam::ID))[0] != nullptr) {eCode = 0xFFF8; continue;}
                ID = buf;
                i++;
                eCode = 0;
                break;
            }
            case searchParam::TITLE: {
                string buf;
                cout << "Введите наименование книги: ";
                getline(cin, buf);

                eCode = eraseSpaces(buf);
                if(eCode != 0) continue;
                if(buf == "e") {
                    exitEntering = true;
                    eCode = 0xAAA0; // Отмена создания записи об экземпляре книги
                    continue;
                }

                title = buf;
                i++;
                eCode = 0;
                break;
            }
            case searchParam::AUTHOR: {
                string buf;
                cout << "Введите имя автора: ";
                getline(cin, buf);

                eCode = eraseSpaces(buf);
                if(eCode != 0) continue;
                if(buf == "e") {
                    exitEntering = true;
                    eCode = 0xAAA0; // Отмена создания записи об экземпляре книги
                    continue;
                }

                author = buf;
                i++;
                eCode = 0;
                break;
            }
            case searchParam::YEAROFRELEASE: {
                string buffer;
                int iBuffer;
                size_t pos;
                cout << "Введите год выпуска книги: ";
                getline(cin, buffer);

                eCode = eraseSpaces(buffer);
                if(eCode != 0) continue;
                if(buffer == "e") {
                    exitEntering = true;
                    eCode = 0xAAA0; // Отмена создания записи об экземпляре книги
                    continue;
                }

                // Проверка ввода на наличие каких либо символов кроме цифр и введённого года на соответствие интервалу
                pos = buffer.find_first_not_of("0123456789");
                if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число

                iBuffer = stoi(buffer);
                if(iBuffer > 2026 || iBuffer < 1700) {eCode = 0xFFFC; continue;} // Введённое число выходит за границы интервала

                yearOfRelease = iBuffer;
                i++;
                eCode = 0;
                break;
            }
            case searchParam::CURSTATE: {
                string buffer;
                int iBuffer;
                size_t pos;
                cout << "Введите текущий статус\n(Если книга выдана - введите 1,\nесли книга на складе - введите 2): ";
                getline(cin, buffer);

                eCode = eraseSpaces(buffer);
                if(eCode != 0) continue;
                if(buffer == "e") {
                    exitEntering = true;
                    eCode = 0xAAA0; // Отмена создания записи об экземпляре книги
                    continue;
                }

                pos = buffer.find_first_not_of("0123456789");
                if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число

                iBuffer = stoi(buffer);
                if(iBuffer != 1 && iBuffer != 2) {eCode = 0xFFFC; continue;} // Введенное значение вышло за допустимые границы значений

                if(iBuffer == 1) {
                    curState = GIVEN;
                }
                else if(iBuffer == 2) {
                    curState = INSTOCK;
                }

                exitEntering = true;
                eCode = 0;
                break;
            }
            default:
                break;
        }
    }
    return eCode;
}

// Определение оператора == для возможности использования класса book в unordered_map
bool book::operator==(const book& otherBook) const {
    return (this->title == otherBook.title &&
            this->author == otherBook.author &&
            this->yearOfRelease == otherBook.yearOfRelease &&
            this->curState == otherBook.curState);
}

// Определение оператора == для возможности вывода полей книги в стандартный поток вывода
ostream& operator<<(ostream& out, const book& book) {
    out << "Идентификатор книги: " << setw(45) << book.ID << endl
        << "Наименование книги:  " << setw(45) << book.title << endl
        << "Имя автора книги:    " << setw(45) << book.author << endl
        << "Год издания книги:   " << setw(45) << book.yearOfRelease << endl
        << "Статус:              " << setw(45) << ((book.curState == GIVEN) ? "Выдана" : "На складе") << endl;
    return out;
}

// Деструктор класса
book::~book() {}
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

// Переопределение оператора () для определения хеша класса book
size_t bookHasher::operator()(const book& otherBook) const {
    return hash<string>{}(otherBook.getTitle() + "|" +
                          otherBook.getAuthor() + "|" +
                          to_string(otherBook.getYearOfRelease()) + "|" +
                          to_string(otherBook.getState()));
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

// Определение методов класса списка книг

// Конструктор класса списка книг
bookList::bookList() {
    nextBookList = nullptr;
    thisBook = nullptr;
}

// Деструктор класса списка книг
bookList::~bookList() {
    delete thisBook;
}

// Методы получения полей экземпляра класса списка книг
bookList* bookList::getNextBookList() {
    return this->nextBookList;
}

book* bookList::getBook() {
    return thisBook;
}

// Метод удаления всего списка книг
void bookList::deleteAll() {
    if(this->getNextBookList() != nullptr) {
        this->getNextBookList()->deleteAll();
        delete this->getNextBookList();
    }
}

// Метод добавления экземпляра класса book в списко книг
int bookList::addBook(book* newBook) {
    // Проверяем наличие книги в списке книг
    string sID = newBook->getID();
    if((this->searchBook<string>(sID, ID))[0]) return 0xFFF8;

    // Вставка в конец списка книг
    bookList* sBookList = this;
    while(sBookList->nextBookList != nullptr) {
        sBookList = sBookList->nextBookList;
    }
    sBookList->nextBookList = new bookList;
    sBookList->nextBookList->thisBook = newBook;
    return 0;
}

// Метод удаления экземпляра класса book в списко книг
int bookList::deleteBook(string delBookID) {
    // Поиск удаляемой книги и проверка её наличия в списке книг
    bookList* sBookList = (searchBook<string>(delBookID, ID))[0];
    if(sBookList == nullptr) return 0xFFFA;
    // Удаления книги из списка книг
    bookList* delBookList = sBookList->nextBookList;
    sBookList->nextBookList = sBookList->nextBookList->nextBookList;
    delete delBookList;
    return 0;
}


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

// Определение методов класса хеш-таблицы книг

// Конструктор хеш-таблицы учета книг
bookTable::bookTable(int tableSize) {
    this->tableSize = tableSize;
    table = new bookList*[this->tableSize];
    for(int i = 0; i < tableSize; i++) {
        table[i] = new bookList;
    }
    saved = false;
}

// Деструктор хеш-таблицы учета книг
bookTable::~bookTable() {
    for(int i = 0; i < tableSize; i++) {
        table[i]->deleteAll();
        delete table[i];
    }
    delete[] table;
}

// Хеш-функция определния значения хеша инвентарного номера книги

// Переработать в более оптимальную
// Подумать над переполнением
unsigned int bookTable::hash(string bookID) {
    unsigned res = 0;
    for(char c : bookID) {
        res = (res+1) * c + 15;
    }
    return res;
}

// Получение размера таблицы
int bookTable::getSize() {
    return tableSize;
}

// Метод добавления книги в хеш-таблицу учета книг
int bookTable::addBook(book* newBook) {
    vector<bookList*> sBookList;
    //Проверка наличия книги в хеш-таблице
    sBookList = searchBook(newBook->getID(), ID);
    if(sBookList[0] != nullptr) return 0xFFF8;
    saved = false;
    return table[hash(newBook->getID()) % tableSize]->addBook(newBook);
}

// Метод удаления книги из хеш-таблицы учета книг
int bookTable::deleteBook(string delBookID) {
    int eCode = table[hash(delBookID) % tableSize]->deleteBook(delBookID);
    if(eCode == 0) saved = false;
    return eCode;
}

// Метод проверки на пустоту хеш-таблицы
bool bookTable::isEmpty() {
    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        if(iter != nullptr) return false;
    }
    return true;
}

// Метод проверки сохраненности хеш-таблицы в файл
bool bookTable::isSaved() {
    return saved;
}

// Метод установки флага сохранения хеш-таблицы
void bookTable::changeSaved(bool saved) {
    this->saved = saved;
}

// Чтение хеш-таблицы из файла
int bookTable::readFromFile(const string& fileName) {
    int eCode = 0;
    int readCode = 0;
    string ssBuffer = "";
    fstream fid;
    stringstream ss;


    fid.open(fileName, ios::in);

    if(!fid.is_open()) return 0xFFF4;

    // Циклическое чтение строки со значениями полей экземпляра класса book
    while(getline(fid, ssBuffer)) {
        book* newBook = nullptr;
        ssBuffer += '$';
        int i = 0;
        size_t pos = 0;
        string buffer = "";
        string coordDataBuf = "";
        double coordData = 0;

        // Очистка строкового потока
        ss.str("");
        ss.clear();

        // Удаления символа перевода на новую строку
        pos = ssBuffer.find_first_of("\n");
        if(pos != string::npos) ssBuffer.erase(pos, 1);
        ss << ssBuffer;
        // Чтение полей экземпляра класса book из полученной строки файла
        while(getline(ss, buffer, '$')) {
            if(buffer != "" &&  buffer != "\n") {
                switch (i) {
                case 0:
                    newBook = new book(buffer);
                    if((searchBook(newBook->getID(), searchParam::ID))[0] != nullptr) {
                        readCode = 0xEEEE;
                        delete newBook;
                        newBook = nullptr;
                    }
                    break;
                case 1:
                    if(!newBook) break;
                    newBook->setTitle(buffer);
                    break;
                case 2:
                    if(!newBook) break;
                    newBook->setAuthor(buffer);
                    break;
                case 3:
                    if(!newBook) break;
                    if(eCode != 0) {
                        newBook->setYearOfRelease(0000);
                    }
                    else {
                        newBook->setYearOfRelease(stoi(buffer));
                    }
                    break;
                case 4:
                    if(!newBook) break;
                    if(buffer == "GIVEN") newBook->setState(GIVEN);
                    if(buffer == "INSTOCK") newBook->setState(INSTOCK);
                    break;
                default:
                    break;
                }
            }
            i++;
        }
        if(newBook) eCode = table[hash(newBook->getID()) % tableSize]->addBook(newBook);
    }
    saved = (readCode == 0);
    fid.close();
    return readCode;
}

// Метод записи в файл хещ-таблицы
int bookTable::writeToFile(const string& fileName) {
    fstream fid;
    stringstream ss;

    fid.open(fileName, ios::out);
    if(!fid.is_open()) return 0xFFF4;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            ss << curBook->getID() << "$"
               << curBook->getTitle() << "$"
               << curBook->getAuthor() << "$"
               << curBook->getYearOfRelease() << "$";

            if((curBook->getState()) == GIVEN) ss << "GIVEN" << "\n";
            if((curBook->getState()) == INSTOCK) ss << "INSTOCK" << "\n";
            fid << ss.str();
            ss.str("");
            ss.clear();
            iter = iter->getNextBookList();
        }
    }
    saved = true;
    return 0;
}

// Вывод всех записей о книга в хеш-таблице
void bookTable::display() {
    // Неупорядоченный словарь найденных книг
    // Ключ - книга
    // Значение - пара, первый элемент которой это количество найденых книг
    //                  второй элемент - вектор инвентарных номеров одинаковых книг
    unordered_map<book, pair<int, vector<string>>, bookHasher> displayMap;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            // Если книга встретилась впервые - добавление её в словарь
            if(!displayMap.contains(*curBook)) {
                displayMap.insert({*(curBook), make_pair(1, vector<string>{curBook->getID()})});
            }
            // Иначе (если уже стречалась - увеличений счетчика и добавление инвентарного номера книги в словарь)
            else {
                displayMap[*curBook].first++;
                displayMap[*curBook].second.push_back(curBook->getID());
            }
            iter = iter->getNextBookList();
        }
    }

    string sep(30, '-');
    for(const auto& p : displayMap) {
        cout << p.first << endl
             << "Количество: " << setw(39) << p.second.first << endl
             << "Инвентарные номера книг: " << endl;
        for(const string& str : p.second.second) {
            cout << setw(51) << str << endl;
        }
        cout << endl << sep << endl;
    }
}

// Перегрузка метода вывода всех записей о книгах в хеш-таблице
// Выводятся только те записи о книгах, которые соответствуют заданному пользователем статусу наличия на складе
// Метод полностью аналогичен методу вывода всех записей о книгах, за исключением наличия проверки статуса книги
void bookTable::display(state neededState) {
    unordered_map<book, pair<int, vector<string>>, bookHasher> displayMap;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            if(curBook->getState() == neededState) {
                if(!displayMap.contains(*curBook)) {
                    displayMap.insert({*(curBook), make_pair(1, vector<string>{curBook->getID()})});
                }
                else {
                    displayMap[*curBook].first++;
                    displayMap[*curBook].second.push_back(curBook->getID());
                }
            }
            iter = iter->getNextBookList();
        }
    }

    string sep(30, '-');
    for(const auto& p : displayMap) {
        cout << p.first << endl
             << "Количество: " << setw(30) << p.second.first << endl
             << "Инвентарные номера книг: " << endl;
        for(const string& str : p.second.second) {
            cout << "\t" << str << endl;
        }
        cout << endl << sep << endl;
    }
}

// Вывод числа занятых корзин хеш-таблицы
void bookTable::displayBucketCount() {
    int count = 0;
    for(int i = 0; i < tableSize; i++) {
        if(table[i]->getNextBookList() != nullptr) count++;
    }
    cout << "Количество занятых ячеек: " << count << endl;
}

// Вывод самого длинного списка книг среди всех корзин хеш-таблицы
void bookTable::displayLongestBucketLength() {
    int maxLen = 0;
    for(int i = 0; i < tableSize; i++) {
        int count = 0;
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            count++;
            iter = iter->getNextBookList();
        }
        maxLen = max(maxLen, count);
    }
    cout << "Максимальная длина ячейки: " << maxLen << endl;
}
//--------------------------------------------------------------------------------------------------------------











