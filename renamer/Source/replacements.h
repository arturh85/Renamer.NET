#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"

class Replacements {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacements(sqlite3* db);

        //---------------------------------------------------------------------
        //  methodes

        string replace(string);

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        sqlite3* mDb;
        Replacements* mParent;
};

#endif //REPLACEMENTS_H
