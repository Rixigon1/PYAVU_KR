#include "dataStructures.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <unordered_map>

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


// string book::getID() const {
//     return this->ID;
// }

// string book::getTitle() const {
//     return this->title;
// }

// string book::getAuthor() const {
//     return this->author;
// }

// int book::getYearOfRelease() const {
//     return this->yearOfRelease;
// }

// state book::getState() const {
//     return this->curState;
// }

int book::createBook() {
    int eCode = 0;

    return eCode;
}

bool book::operator==(const book& otherBook) const {
    return (this->title == otherBook.title &&
            this->author == otherBook.author &&
            this->yearOfRelease == otherBook.yearOfRelease &&
            this->curState == otherBook.curState);
}

ostream& operator<<(ostream& out, const book& book) {
    out << "Идентификатор книги: " << setw(30) << ID << endl
        << "Наименование книги:  " << setw(30) << book.getValue<string>(TITLE) << endl
        << "Имя автора книги:    " << setw(30) << book.getValue<string>(AUTHOR) << endl
        << "Год издания книги:   " << setw(30) << book.getValue<int>(YEAROFRELEASE) << endl
        << "Статус:              " << setw(30) << book.getValue<state>(CURSTATE) << endl;
    return out;
}

book::~book() {

}
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

size_t bookHasher::operator()(const book& otherBook) const {
    return hash<string>{}(otherBook.getValue<string>(TITLE) + "|" +
                          otherBook.getValue<string>(AUTHOR) + "|" +
                          to_string(otherBook.getValue<int>(YEAROFRELEASE)) + "|" +
                          to_string(otherBook.getValue<state>(CURSTATE)));
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
// Определение списка книг
bookList::bookList() {
    nextBookList = nullptr;
    thisBook = nullptr;
}

bookList* bookList::getNextBookList() {
    return this->nextBookList;
}

book* bookList::getBook() {
    return thisBook;
}

void bookList::addBook(book* newBook) {
    bookList* sBookList = this;
    while(sBookList->nextBookList != nullptr) {
        sBookList = sBookList->nextBookList;
    }
    sBookList->nextBookList = new bookList;
    sBookList->nextBookList->thisBook = newBook;
    delete sBookList;
}

int bookList::deleteBook(string delBookID) {
    bookList* listHead = this;
    bookList* sBookList = searchBook<string>(delBookID, ID);
    int code = (sBookList == nullptr) ? -1 : 0;
    bookList* delBookList = sBookList->nextBookList;
    sBookList->nextBookList = sBookList->nextBookList->nextBookList;
    return code;
}

bookList::~bookList() {
    delete thisBook;
    delete nextBookList;
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

// Переработать более оптимальную
int bookTable::hash(string bookID) {
    int res = 0;
    for(char c : bookID) {
        res = res * c + 15;
    }
    return res;
}

void bookTable::addBook(book* newBook) {
    table[hash(newBook->getValue<string>(ID)) % tableSize]->addBook(newBook);
}

int bookTable::deleteBook(string delBookID) {
    return table[hash(delBookID) % tableSize]->deleteBook(delBookID);
}

/*
bookList* searchByID(int bookID);
bookList* searchByTitle(string bookTitle);
bookList* searchByAuthor(string bookAuthor);
*/

// Чтение и сохранение из/в файла
void bookTable::readFromFile(const string& fileName) {


}
void bookTable::writeToFile(const string& fileName) {

}

// // Функция округления координаты цели
// string to_string_fixed_precision(double value, int n = 3) {
//     stringstream ss;
//     ss << fixed << setprecision(n) << value;
//     return ss.str();
// }

// Шаблоны для функции записи и чтения талицы из файла

// // Функция чтения списка целей
// int readTargetList(string& fileName) {
//     int eCode = 0;
//     string buffer = "";
//     fstream fid;
//     stringstream ss;
//     book* newBook = new book;
//     newBook->createBook();
//     if(eCode != 0) return eCode;

//     // cout << "Чтение списка целей" << endl << endl;

//     // eCode = chooseFile(fileName, false);


//     fid.open(fileName, ios::in);
//     while(getline(fid, buffer)) {
//         buffer += ' ';
//         int firstPosOfSpace = 0;
//         string targetNameBuf = "";
//         string coordDataBuf = "";
//         double coordData = 0;
//         ss.str("");
//         ss.clear();
//         // Чтение строки цели и её координат
//         firstPosOfSpace = buffer.find_first_not_of(' ');
//         if(firstPosOfSpace == buffer.npos) continue;
//         buffer = buffer.substr(firstPosOfSpace);
//         ss << buffer;
//         // Добавление цели и её координат в список
//         getline(ss, targetNameBuf, ' ');
//         curTarget = addTargetEnd(targetHead, targetNameBuf);
//         while(getline(ss, coordDataBuf, '|')) {
//             if(coordDataBuf != "" &&  coordDataBuf != "\n") {
//                 coordData = stod(coordDataBuf);
//                 addCoordEnd(curTarget, coordData);
//             }
//         }
//     }
//     fid.close();
//     return eCode;
// }
// // Функция сохранения списка в файл
// int saveListToFile(string &fileName, target* targetHead) {
//     int eCode = 0;
//     fstream fid;
//     target* bufTar = targetHead->targetPtr;
//     coordinate* bufCoord = nullptr;

//     cout << "Сохранение списка целей" << endl << endl;

//     eCode = chooseFile(fileName, true);
//     if(eCode != 0) return eCode;

//     fid.open(fileName, ios::out);

//     // Перебор и запись целей
//     while(bufTar != nullptr) {
//         fid << bufTar->data << ' ';
//         bufCoord = bufTar->coordPtr;
//         // Перебор и запись координат цели
//         while(bufCoord != nullptr) {
//             fid << bufCoord->coordData << ' ';
//             bufCoord = bufCoord->coordPtr;
//         }
//         fid << endl;
//         bufTar = bufTar->targetPtr;
//     }
//     return eCode;
// }



// Вывод информации по запросу пользователя
// Формат текста UTF-8
void bookTable::display() {
    unordered_map<book, int, bookHasher> displayMap;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            if(!displayMap.contains(*curBook)) {
                displayMap.insert({*(curBook), 1});
            }
            else {
                displayMap[*curBook]++;
            }
            iter = iter->getNextBookList();
        }
    }

    for(const auto& p : displayMap) {
        cout << p.first << endl
             << "Количество: " << setw(30) << p.second << endl << endl;
    }
}
void bookTable::display(state neededState) {
    unordered_map<book, int, bookHasher> displayMap;

    for(int i = 0; i < tableSize; i++) {
        bookList* iter = table[i]->getNextBookList();
        while(iter != nullptr) {
            book* curBook = iter->getBook();
            if(curBook->getValue<state>(CURSTATE) == neededState) {
                if(!displayMap.contains(*curBook)) {
                    displayMap.insert({*(curBook), 1});
                }
                else {
                    displayMap[*curBook]++;
                }
                iter = iter->getNextBookList();
            }
        }
    }

    for(const auto& p : displayMap) {
        cout << p.first << endl
             << "Количество: " << setw(30) << p.second << endl << endl;
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
    cout << "Максимальная длина ячейки:" << maxLen << endl;
}


bookTable::~bookTable() {
    for(int i = 0; i < tableSize; i++) {
        delete table[i];
    }
    delete table;
}

//--------------------------------------------------------------------------------------------------------------











