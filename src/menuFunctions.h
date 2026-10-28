#include "dataStructures.h"

// Определние класса текстового интерфейса работы с программой
class TUI {
    private:
        bookTable* table;     // Указатель на хеш-таблицу учета книг
        bool exitApp = false; // Флаг завершения работы программы

    public:
        // Конструктор и деструктор класса интерфейса
        TUI();
        ~TUI();

        // Метод вывода главного меню программы
        int showMainMenu();
        // Метод вывода дополнительного функционала работы с хеш-таблицей
        int showAdditionalMainMenu();
        // Метод выбора параметра, по которому будет произведен поиск
        int chooseSParam(searchParam& sParam, string& buf);
        // Метод установки нового статуса книги на складе
        int chooseState(state& newState);
        // Метод ввода имени файла
        int chooseFile(string &fileName, bool toWrite);
        // Метод работы с файлом
        int workWithFile(bool toWrite);

        // Обявление функции дружественной по отношению к классу интерфейса
        friend void errorProcessor(int eCode);

        // Метод инициализации работы программы
        int exec();

};





