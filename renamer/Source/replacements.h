#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"

class Replacements {
    public:
        //  constructors
        Replacements(sqlite3* db) : mDb(db) {};

        #ifdef RENAMER_UNIT_TEST
        static void unitTest();
        #endif

    private:
        sqlite3* mDb;
};

#endif //REPLACEMENTS_H
