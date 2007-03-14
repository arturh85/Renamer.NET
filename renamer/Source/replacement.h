#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"

class Replacement {
    public:
        //  methodes
        static void createTables(sqlite3* db);
        string replace(string);


        #ifdef RENAMER_UNIT_TEST
        static void unitTest();
        #endif

        //  attributes
        boost::regex expression;
        string replacement;
        bool inherit;
};

#endif //REPLACEMENT_H
