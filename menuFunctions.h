#include "dataStructures.h"

class TUI {
    private:
        bookTable* table;
        bool exitApp = false;

    public:
        TUI();
        ~TUI();

        int showMainMenu();
        int showAdditionalMainMenu();
        int chooseSParam(searchParam& sParam, string& buf);
        int chooseState(state& newState);
        int chooseFile(string &fileName, bool toWrite);
        int workWithFile(bool toWrite);

        friend void errorProcessor(int eCode);

        int exec();

};





