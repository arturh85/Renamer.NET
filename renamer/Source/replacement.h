#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"
#include "TableRow.h"

class Replacement : public TableRow {
    public:
        //  constructors
        Replacement(sqlite3* db) : TableRow(db, "replacements") {}  ;

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

    private:
        sqlite3* mDb;

};

#endif //REPLACEMENT_H
