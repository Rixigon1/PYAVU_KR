#pragma once

#include <string>

using namespace std;

enum state {GIVEN, INSTOCK};
enum searchParam {ID, TITLE, AUTHOR, YEAROFRELEASE, CURSTATE};

class bookTable;

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
        book(string ID = "", string title = "", string author = "", int yearOfRelease = 0000, state curState = INSTOCK);
        ~book();

        // template<typename T>
        // void setValue(T value, searchParam sParam) {
        //     switch (sParam) {
        //     case TITLE:
        //         this->title = value;
        //         break;
        //     case AUTHOR:
        //         this->author = value;
        //         break;
        //     case YEAROFRELEASE:
        //         this->yearOfRelease = value;
        //         break;
        //     case CURSTATE:
        //         this->curState = value;
        //         break;
        //     default:
        //         break;
        //     }
        // }

        void setTitle(string title);
        void setAuthor(string author);
        void setYearOfRelease(int yearOfRelease);
        void setState(state curState);

        string getID() const;
        string getTitle() const;
        string getAuthor() const;
        int getYearOfRelease() const;
        state getState() const;

        int createBook(bookTable* bTable);

        bool operator==(const book& otherBook) const;
        friend ostream& operator<<(ostream& out, const book& book);
        friend void errorProcessor(int eCode);
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

        void deleteAll();

        // Добавление в конец списка корзины
        int addBook(book* newBook);

        // Удаление из произвольного места в корзине
        // Поиск элемента идет внутри метода
        // Возвращает -1 если элемент не найден
        // template<typename T>
        // int deleteBook(T value, searchParam sParam) {
        //     bookList* listHead = this;
        //     bookList* sBookList = searchBook<T>(value, sParam);
        //     int code = (sBookList == nullptr) ? -1 : 0;
        //     bookList* delBookList = sBookList->nextBookList;
        //     sBookList->nextBookList = sBookList->nextBookList->nextBookList;
        //     delete delBookList;
        //     return code;
        // }

        int deleteBook(string delBookID);

        // Возвращают указатель на книгу, предшевствующей искомой
        template<typename T>
        bookList* searchBook(T sValue, searchParam sParam) {
            bookList* sBookList = this;

            while(sBookList->nextBookList != nullptr) {
                switch (sParam) {
                case ID:
                    if(sBookList->nextBookList->thisBook->getID() == sValue) return sBookList;
                    break;
                case TITLE:
                    if(sBookList->nextBookList->thisBook->getTitle() == sValue) return sBookList;
                    break;
                case AUTHOR:
                    if(sBookList->nextBookList->thisBook->getAuthor() == sValue) return sBookList;
                    break;
                default:
                    return nullptr;
                    break;
                }
                sBookList = sBookList->nextBookList;
            }
            return nullptr;
        }

        /*
        bookList* searchByID(string bookID);
        bookList* searchByTitle(string bookTitle);
        bookList* searchByAuthor(string bookAuthor);
        */
};

class bookTable {
    private:
        bookList** table;
        int tableSize;
        bool saved;

        unsigned int hash(string bookID);

    public:
        // Пользователь обязан ввести размер таблицы
        bookTable(int tableSize);
        ~bookTable();

        int getSize();

        int addBook(book* newBook);
        // Возвращает -1 если элемент не найден


        int deleteBook(string delBookID);

        // Возвращают указатель на книгу, предшевствующей искомой
        template<typename T>
        bookList* searchBook(T value, searchParam sParam) {
            switch (sParam) {
            case ID: {
                bookList* bucket = table[hash(value) % tableSize];
                bookList* sBookList = bucket->searchBook(value, sParam);
                return sBookList;
                break;
            }
            case TITLE:
                for(int i = 0; i < tableSize; i++) {
                    bookList* bucket = table[i];
                    bookList* sBookList;
                    if((sBookList = bucket->searchBook(value, sParam)) != nullptr) {
                        return sBookList;
                    }
                }
                return nullptr;
                break;
            case AUTHOR:
                for(int i = 0; i < tableSize; i++) {
                    bookList* bucket = table[i];
                    bookList* sBookList;
                    if((sBookList = bucket->searchBook(value, sParam)) != nullptr) {
                        return sBookList;
                    }
                }
                return nullptr;
                break;
            default:
                break;
            }
        }

        /*
        bookList* searchByID(int bookID);
        bookList* searchByTitle(string bookTitle);
        bookList* searchByAuthor(string bookAuthor);
        */

        bool isEmpty();
        bool isSaved();

        friend int checkID(string enteredID);

        // Чтение и сохранение из/в файла
        int readFromFile(const string& fileName);
        int writeToFile(const string& fileName);

        // Вывод информации по запросу пользователя
        void display();
        void display(state neededState);

        // Вывод числа корзин и самой длинной корзины
        void displayBucketCount();
        void displayLongestBucketLength();
};

