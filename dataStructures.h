#pragma once

#include <string>

using namespace std;

enum state {GIVEN, INSTOCK};

class book {
    private:
        /* Вопрос: ID оставить на выбор пользователя для гибкости программы в разных организациях
         *         или же сделать для него определенную маску?
        */
        string ID;
        string title;
        string author;
        int yearOfRelease;
        state curState;

    public:
        book(string title = "", string author = "", int yearOfRelease = 0000, state curState = INSTOCK);
        ~book();

        void setTitle(string title);
        void setAuthor(string author);
        void setYearOfRelease(int year);
        void setState(state state);

        string getID();
        string getTitle();
        string getAuthor();
        int getYearOfRelease();
        state getState();

        void displayData();
};

class bookList {
    private:
        // Сделать инициализацию в конструкторе nullptr-ами
        book* nextBook;
        book* thisBook;

    public:
        bookList();
        ~bookList();

        book* getNextBook();

        // Добавление в конец списка корзины
        void addBook(book* newBook, int count = 1);
        // Добваление в произвольное место списка корзины
        void addBook(book* newBook, book* prevBook, int count = 1);

        // Удаление из произвольного места в корзине
        void deleteBook(book* remBook, book* prevBook);

        // Возвращают указатель на книгу, предшевствующей искомой
        book* searchByID(string bookID);
        book* searchByTitle(string bookTitle);
        book* searchByAuthor(string bookAuthor);

        // Проверяет наличие книги в корзине
        bool isInTable(string bookID);
};

class bookTable {
    private:
        book* table;
        int tableSize;

        int hash(string bookID);

    public:
        // Пользователь обязан ввести размер таблицы
        bookTable(int tableSize);
        ~bookTable();

        void addBook(book* newBook);
        void deleteBook(book* remBook);

        // Возвращают указатель на книгу, предшевствующей искомой
        book* searchByID(int bookID);
        book* searchByTitle(string bookTitle);
        book* searchByAuthor(string bookAuthor);

        // Чтение и сохранение из/в файла
        void readFromFile(string fileName);
        void writeToFile(string fileName);

        // Вывод информации по запросу пользователя
        void display();
        void display(state neededState);

        // Вывод числа корзин и самой длинной корзины
        void displayBucketCount();
        void displayLongestBucket();
};

