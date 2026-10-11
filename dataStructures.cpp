#include "dataStructures.h"

#include <iostream>
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

void bookTable::addBook(book* newBook, int count) {
    table[hash(newBook->getValue<string>(ID)) % tableSize]->addBook(newBook, count);
}

int bookTable::deleteBook(book* remBook, searchParam sParam) {
    return table[hash(remBook->getValue<string>(ID)) % tableSize]->deleteBook(remBook, sParam);
}

/*
bookList* searchByID(int bookID);
bookList* searchByTitle(string bookTitle);
bookList* searchByAuthor(string bookAuthor);
*/

// Чтение и сохранение из/в файла
void bookTable::readFromFile(string fileName) {

}
void bookTable::writeToFile(string fileName) {

}

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
    delete table;
}

//--------------------------------------------------------------------------------------------------------------











