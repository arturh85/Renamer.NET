#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"

class InputRule {
    public:
        //  constructors
        InputRule() : mRowid(-1), mDb(NULL) {};
        InputRule(sqlite_int64 rowid, sqlite3* );
        InputRule(boost::regex, sqlite3* );

        //  methodes
        static void createTables(sqlite3* db);
        string getRegex() const;
        void setRegex(string);
        long getId() const { return mRowid; };

        #ifdef RENAMER_UNIT_TEST
        static void unitTest();
        #endif

    private:

        //  attributes
        sqlite_int64 mRowid;
        sqlite3* mDb;

};

#endif //INPUT_RULE
