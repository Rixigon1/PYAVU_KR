#pragma once

#include <string>
#include <vector>

using namespace std;

// Перечисляемые типы данных для определения статуса на книги на складе и типа поля соответственно
enum state {GIVEN, INSTOCK};
enum searchParam {ID, TITLE, AUTHOR, YEAROFRELEASE, CURSTATE};

// Объявление класса хещ-таблицы учета книг
class bookTable;

// Класс книги
class book {
    private:
        string ID;         // Инвентарный номер книги
        string title;      // Название книги
        string author;     // Имя автора
        int yearOfRelease; // Год выпуска книги
        state curState;    // Текущий статус книги на складе


    public:
        // Конструктор и деструктор класса book
        book(string ID = "", string title = "", string author = "", int yearOfRelease = 0000, state curState = INSTOCK);
        ~book();

        // Методы установки значения поля экземпляра класса
        void setTitle(string title);
        void setAuthor(string author);
        void setYearOfRelease(int yearOfRelease);
        void setState(state curState);

        // Методы получения значения поля экземпляра класса
        string getID() const;
        string getTitle() const;
        string getAuthor() const;
        int getYearOfRelease() const;
        state getState() const;

        // Функция создания и заполнения экземпляра класса book по средством ввода с клавиатуры
        int createBook(bookTable* bTable);

        // Определение оператора == для возможности использования класса book в unordered_map
        bool operator==(const book& otherBook) const;
        // Определение оператора == для возможности вывода полей книги в стандартный поток вывода
        friend ostream& operator<<(ostream& out, const book& book);
        // Объявление функции дружественной по отношению к классу
        friend void errorProcessor(int eCode);
};

// Вспомогательная структура для определения хеша класса book
struct bookHasher {
    // Переопределение оператора () для определения хеша класса book
    size_t operator()(const book& otherBook) const;
};

// Определение класса списка книг
class bookList {
    private:
        bookList* nextBookList; // Указатель на следующую ячейку в списке книг
        book* thisBook;         // Указатель на хранимую книгу

    public:
        // Конструктор и деструкторв класса списка книг
        bookList();
        ~bookList();


        // Методы получения полей экземпляра класса списка книг
        bookList* getNextBookList();
        book* getBook();

        // Метод удаления всего списка книг
        void deleteAll();

        // Метод добавления экземпляра класса book в списко книг
        int addBook(book* newBook);
        // Метод удаления экземпляра класса book в списко книг
        int deleteBook(string delBookID);

        // ПЕРЕДЕЛАТЬ ПОД ПОИСК ВСЕХ ЭЛЕМЕНТОВ ДЛЯ ЗНАЧЕНИЙ АВТОР И НАЗВАНИЕ
        // Метод поиска книги с заданным пользователем параметром
        template<typename T>
        vector<bookList*> searchBook(T sValue, searchParam sParam) {
            bookList* sBookList = this;
            vector<bookList*> searchResult;

            while(sBookList->nextBookList != nullptr) {
                switch (sParam) {
                case ID:
                    if(sBookList->nextBookList->thisBook->getID() == sValue) searchResult.push_back(sBookList);
                    break;
                case TITLE:
                    if(sBookList->nextBookList->thisBook->getTitle() == sValue) searchResult.push_back(sBookList);
                    break;
                case AUTHOR:
                    if(sBookList->nextBookList->thisBook->getAuthor() == sValue) searchResult.push_back(sBookList);
                    break;
                default:
                    break;
                }
                sBookList = sBookList->nextBookList;
            }
            if(searchResult.empty()) searchResult = {nullptr};
            return searchResult;
        }
};

// Определение класса хеш-таблицы книги
class bookTable {
    private:
        bookList** table; // Указатель на массив списков книг
        int tableSize;    // Размер массива списка книг
        bool saved;       // Флаг сохранения хеш-таблицы в файл

        // Хеш-функция определния значения хеша инвентарного номера книги
        unsigned int hash(string bookID);

    public:
        // Конструктор и деструктор хеш-таблицы учета книг
        bookTable(int tableSize);
        ~bookTable();

        // Получение размера таблицы
        int getSize();

        // Метод добавления книги в хеш-таблицу учета книг
        int addBook(book* newBook);
        int deleteBook(string delBookID);


        // ПЕРЕДЕЛАТЬ ПОД ПОИСК ВСЕХ ЭЛЕМЕНТОВ ДЛЯ ЗНАЧЕНИЙ АВТОР И НАЗВАНИЕ
        // Шаблонный метод поиска книги по заданному пользователем параметру
        template<typename T>
        vector<bookList*> searchBook(T value, searchParam sParam) {

            switch (sParam) {
            case ID: {
                bookList* bucket = table[hash(value) % tableSize];
                vector<bookList*> sBookList = bucket->searchBook(value, sParam);
                return sBookList;
                break;
            }
            case TITLE: {
                vector<bookList*> searchResult;
                for(int i = 0; i < tableSize; i++) {
                    bookList* bucket = table[i];
                    vector<bookList*> sBookList;
                    if((sBookList = bucket->searchBook(value, sParam))[0] != nullptr) {
                        searchResult.insert(searchResult.end(), sBookList.begin(), sBookList.end());
                    }
                }
                if(searchResult.empty()) searchResult = {nullptr};
                return searchResult;
                break;
            }
            case AUTHOR: {
                vector<bookList*> searchResult;
                for(int i = 0; i < tableSize; i++) {
                    bookList* bucket = table[i];
                    vector<bookList*> sBookList;
                    if((sBookList = bucket->searchBook(value, sParam))[0] != nullptr) {
                        searchResult.insert(searchResult.end(), sBookList.begin(), sBookList.end());
                    }
                }
                if(searchResult.empty()) searchResult = {nullptr};
                return searchResult;
                break;
            }
            default:
                return {nullptr};
                break;
            }
        }

        // Метод проверки на пустоту хеш-таблицы
        bool isEmpty();
        // Метод проверки сохраненности хеш-таблицы в файл
        bool isSaved();
        // Метод установки флага сохранения хеш-таблицы
        void changeSaved(bool saved);

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

