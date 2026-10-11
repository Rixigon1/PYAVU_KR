#pragma once

#include <string>

using namespace std;

enum state {GIVEN, INSTOCK};
enum searchParam {ID, TITLE, AUTHOR, YEAROFRELEASE, CURSTATE};

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
        book(string ID, string title = "", string author = "", int yearOfRelease = 0000, state curState = INSTOCK);
        ~book();

        template<typename T>
        void setValue(T value, searchParam sParam) {
            switch (sParam) {
            case TITLE:
                this->title = value;
                break;
            case AUTHOR:
                this->author = value;
                break;
            case YEAROFRELEASE:
                this->yearOfRelease = value;
                break;
            case CURSTATE:
                this->curState = value;
                break;
            default:
                break;
            }
        }

        void setTitle(string title);
        void setAuthor(string author);
        void setYearOfRelease(int yearOfRelease);
        void setState(state curState);

        template<typename T>
        T getValue(searchParam sParam) const {
            switch (sParam) {
            case searchParam::ID:
                return ID;
                break;
            case TITLE:
                return this->title;
                break;
            case AUTHOR:
                return this->author;
                break;
            case YEAROFRELEASE:
                return this->yearOfRelease;
                break;
            case CURSTATE:
                return this->curState;
                break;
            }
        }

        // string getID() const;
        // string getTitle() const;
        // string getAuthor() const;
        // int getYearOfRelease() const;
        // state getState() const;

        bool operator==(const book& otherBook) const;
        friend ostream& operator<<(ostream& out, const book& book);
};

struct bookHasher {
    size_t operator()(const book& otherBook) const;
};

class bookList {
    private:
        // Сделать инициализацию в конструкторе nullptr-ами
        bookList* nextBookList;
        book* thisBook;

    public:
        bookList();
        ~bookList();

        bookList* getNextBookList();
        book* getBook();

        // Добавление в конец списка корзины
        void addBook(book* newBook, int count = 1);

        // Удаление из произвольного места в корзине
        // Поиск элемента идет внутри метода
        // Возвращает -1 если элемент не найден
        int deleteBook(book* remBook, searchParam sParam);

        // Возвращают указатель на книгу, предшевствующей искомой
        template<typename T>
        bookList* searchBook(T sValue, searchParam sParam) {

        }
        bookList* searchByID(string bookID);
        bookList* searchByTitle(string bookTitle);
        bookList* searchByAuthor(string bookAuthor);

        // Проверяет наличие книги в корзине
        bool isInTable(string bookID);
};

class bookTable {
    private:
        bookList** table;
        int tableSize;

        int hash(string bookID);

    public:
        // Пользователь обязан ввести размер таблицы
        bookTable(int tableSize);
        ~bookTable();

        void addBook(book* newBook, int count = 1);
        // Возвращает -1 если элемент не найден
        int deleteBook(book* remBook, searchParam sParam);

        // Возвращают указатель на книгу, предшевствующей искомой
        template<typename T>
        bookList* searchBook(T value, searchParam sParam) {

        }

        bookList* searchByID(int bookID);
        bookList* searchByTitle(string bookTitle);
        bookList* searchByAuthor(string bookAuthor);

        // Чтение и сохранение из/в файла
        void readFromFile(string fileName);
        void writeToFile(string fileName);

        // Вывод информации по запросу пользователя
        void display();
        void display(state neededState);

        // Вывод числа корзин и самой длинной корзины
        void displayBucketCount();
        void displayLongestBucketLength();
};

