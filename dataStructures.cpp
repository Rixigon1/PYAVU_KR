#include "dataStructures.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <utility>
#include <sstream>
#include <unordered_map>

#include "utils.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------
// Определение класса книги
book::book(string ID, string title, string author, int yearOfRelease, state curState) {
    this->ID = ID;
    this->title = title;
    this->author = author;
    this->yearOfRelease = yearOfRelease;
    this->curState = curState;
}

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

// 0xFFFE
int checkID(int enteredID) {

}

int book::createBook(bookTable* bTable) {
    int eCode = 0;
    const int n = 5;
    searchParam eParams[n] = {searchParam::ID, searchParam::TITLE, searchParam::AUTHOR, searchParam::YEAROFRELEASE, searchParam::CURSTATE};
    bool exitEntering = false;
    int i = 0;
    while(!exitEntering) {
        system("cls");
        errorProcessor(eCode);

        if(eCode == 0xFFFE) cout << "Ошибка: введено не число!" << endl << endl;
        else if(eCode == 0xFFFF) cout << "Ошибка: введена пустая строка!" << endl << endl;
        else if(eCode == 0xFFFC) cout << "Ошибка: введёное значение выходит за допустимые границы!" << endl << endl;

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
            if(bTable->searchBook<string>(buf, searchParam::ID) != nullptr) {eCode = 0xFFF8; continue;}
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

            pos = buffer.find_first_not_of("0123456789");
            if(pos != string::npos) {eCode = 0xFFFE; continue;} // Введено не число

            iBuffer = stoi(buffer);
            if(iBuffer > 2026 || iBuffer < 1700) {eCode = 0xFFFC; continue;}

            yearOfRelease = iBuffer;
            i++;
            eCode = 0;
            break;
        }
        case searchParam::CURSTATE: {
            string buffer;
            int iBuffer;
            size_t pos;
            cout << "Введите текущий статус (Книга выдана - введите 1, книга на складе - введите 2): ";
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
        break;
        default:
            break;
        }
    }
    return eCode;
}

bool book::operator==(const book& otherBook) const {
    return (this->title == otherBook.title &&
            this->author == otherBook.author &&
            this->yearOfRelease == otherBook.yearOfRelease &&
            this->curState == otherBook.curState);
}

ostream& operator<<(ostream& out, const book& book) {
    out << "Идентификатор книги: " << setw(45) << book.ID << endl
        << "Наименование книги:  " << setw(45) << book.title << endl
        << "Имя автора книги:    " << setw(45) << book.author << endl
        << "Год издания книги:   " << setw(45) << book.yearOfRelease << endl
        << "Статус:              " << setw(45) << ((book.curState == GIVEN) ? "Выдана" : "На складе") << endl;
    return out;
}

book::~book() {

}
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

size_t bookHasher::operator()(const book& otherBook) const {
    return hash<string>{}(otherBook.getTitle() + "|" +
                          otherBook.getAuthor() + "|" +
                          to_string(otherBook.getYearOfRelease()) + "|" +
                          to_string(otherBook.getState()));
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
// Определение списка книг
bookList::bookList() {
    nextBookList = nullptr;
    thisBook = nullptr;
}

bookList::~bookList() {
    delete thisBook;
}

void bookList::deleteAll() {
    if(this->getNextBookList() != nullptr) {
        this->getNextBookList()->deleteAll();
        delete this->getNextBookList();
    }
}

bookList* bookList::getNextBookList() {
    return this->nextBookList;
}

book* bookList::getBook() {
    return thisBook;
}

int bookList::addBook(book* newBook) {
    string sID = newBook->getID();
    if(this->searchBook<string>(sID, ID)) return 0xFFF8;

    bookList* sBookList = this;
    while(sBookList->nextBookList != nullptr) {
        sBookList = sBookList->nextBookList;
    }
    sBookList->nextBookList = new bookList;
    sBookList->nextBookList->thisBook = newBook;
    return 0;
}

int bookList::deleteBook(string delBookID) {
    // bookList* listHead = this;
    bookList* sBookList = searchBook<string>(delBookID, ID);
    if(sBookList == nullptr) return 0xFFFA;
    // int code = (sBookList == nullptr) ? 0xFFFA : 0;
    bookList* delBookList = sBookList->nextBookList;
    sBookList->nextBookList = sBookList->nextBookList->nextBookList;
    delete delBookList;
    return 0;
}



//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
// Определение таблицы книг
bookTable::bookTable(int tableSize) {
    this->tableSize = tableSize;
    table = new bookList*[this->tableSize];
    for(int i = 0; i < tableSize; i++) {
        table[i] = new bookList;
    }
}

bookTable::~bookTable() {
    for(int i = 0; i < tableSize; i++) {
        table[i]->deleteAll();
        delete table[i];
    }
    delete[] table;
}

// Переработать в более оптимальную
// Подумать над переполнением
unsigned int bookTable::hash(string bookID) {
    unsigned res = 0;
    for(char c : bookID) {
        res = (res+1) * c + 15;
    }
    return res;
}

int bookTable::getSize() {
    return tableSize;
}

int bookTable::addBook(book* newBook) {
    bookList* sBookList;
    sBookList = searchBook(newBook->getID(), ID);
    if(sBookList != nullptr) return 0xFFF8;
    saved = false;
    return table[hash(newBook->getID()) % tableSize]->addBook(newBook);
}

int bookTable::deleteBook(string delBookID) {
    saved = false;
    return table[hash(delBookID) % tableSize]->deleteBook(delBookID);
}

/*
bookList* searchByID(int bookID);
bookList* searchByTitle(string bookTitle);
bookList* searchByAuthor(string bookAuthor);
*/

bool bookTable::isEmpty() {
    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        if(iter != nullptr) return false;
    }
    return true;
}

bool bookTable::isSaved() {
    return saved;
}

// Чтение и сохранение из/в файла
int bookTable::readFromFile(const string& fileName) {
    int eCode = 0;
    string ssBuffer = "";
    fstream fid;
    stringstream ss;
    book* newBook;
    // if(eCode != 0) return eCode;

    // cout << "Чтение списка целей" << endl << endl;

    // eCode = chooseFile(fileName, false);


    fid.open(fileName, ios::in);

    if(!fid.is_open()) return 0xFFF4;

    while(getline(fid, ssBuffer)) {
        ssBuffer += '$';
        int i = 0;
        size_t pos = 0;
        string buffer = "";
        string coordDataBuf = "";
        double coordData = 0;
        ss.str("");
        ss.clear();
        // Чтение строки цели и её координат
        pos = ssBuffer.find_first_not_of(' ');
        if(pos == string::npos) continue;
        ssBuffer = ssBuffer.substr(pos);
        pos = ssBuffer.find_first_of("\n");
        if(pos != string::npos) ssBuffer.erase(pos, 1);
        ss << ssBuffer;
        // Добавление цели и её координат в список
        while(getline(ss, buffer, '$')) {
            if(buffer != "" &&  buffer != "\n") {
                switch (i) {
                case 0:
                    // eCode = eraseSpaces(buffer);
                    newBook = new book(buffer);
                    break;
                case 1:
                    // eCode = eraseSpaces(buffer);
                    newBook->setTitle(buffer);
                    break;
                case 2:
                    // eCode = eraseSpaces(buffer);
                    newBook->setAuthor(buffer);
                    break;
                case 3:
                    // eCode = eraseSpaces(buffer);
                    if(eCode != 0) {
                        newBook->setYearOfRelease(0000);
                    }
                    else {
                        newBook->setYearOfRelease(stoi(buffer));
                    }
                    break;
                case 4:
                    // eCode = eraseSpaces(buffer);
                    if(buffer == "GIVEN") newBook->setState(GIVEN);
                    if(buffer == "INSTOCK") newBook->setState(INSTOCK);
                    break;
                default:
                    break;
                }
            }
            i++;
        }
        eCode = table[hash(newBook->getID()) % tableSize]->addBook(newBook);
        // if(eCode != 0) delete newBook;
    }
    saved = true;
    fid.close();
    return 0;
}
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





// Вывод информации по запросу пользователя
// Печатается только один ID для всей группы
void bookTable::display() {
    unordered_map<book, pair<int, vector<string>>, bookHasher> displayMap;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            if(!displayMap.contains(*curBook)) {
                displayMap.insert({*(curBook), make_pair(1, vector<string>{curBook->getID()})});
            }
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
        for(auto str : p.second.second) {
            cout << setw(51) << str << endl;
        }
        cout << endl << sep << endl;
    }
}
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
        for(auto str : p.second.second) {
            cout << "\t" << str << endl;
        }
        cout << endl << sep << endl;
    }
}

// Вывод числа корзин и самой длинной корзины
void bookTable::displayBucketCount() {
    int count = 0;
    for(int i = 0; i < tableSize; i++) {
        if(table[i]->getNextBookList() != nullptr) count++;
    }
    cout << "Количество занятых ячеек: " << count << endl;
}
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











