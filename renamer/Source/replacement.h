#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"

class Replacement {
    public:
        //  constructors
        Replacement(sqlite3* db) : mRow(db, "replacements") {}  ;

        //  methodes
        static void createTables(sqlite3* db);
        string replace(string);

        void setInheritable(bool v)
            {mRow.set("inheritable",cSqlBoolOut(v));} ;

        string getReplacement() const
            { return mRow.get("replacement"); };

        void setReplacement(string v)
            {mRow.set("replacement",v);} ;

        boost::regex getRegex() const
            { return boost::regex(mRow.get("regex")); };

        void setRegex(boost::regex v)
            {mRow.set("regex", v.str());} ;

        #ifdef RENAMER_UNIT_TEST
        static void unitTest();
        #endif

    private:
        sqlite3* mDb;
        TableRow mRow;
};

#endif //REPLACEMENT_H
