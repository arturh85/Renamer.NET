#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"

class Replacement {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacement(sqlite3* db) : mRow(db, "replacements") {}  ;

        //---------------------------------------------------------------------
        //  methodes


        //! Creates replacements table
        static void createTables(sqlite3* db);

        //! a result is returnt regardless wether something matched
        string replace(string);

        //! if the regex match it is replaced with this
        string getReplacement() const
            { return mRow.get("replacement"); };

        //! if the regex match it is replaced with this
        void setReplacement(string v)
            {mRow.set("replacement",v);} ;

        //! what should be replaced?
        boost::regex getRegex() const
            { return boost::regex(mRow.get("regex")); };

        //! what should be replaced?
        void setRegex(boost::regex v)
            {mRow.set("regex", v.str());} ;

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  attributes

        sqlite3* mDb;
        TableRow mRow;
};

#endif //REPLACEMENT_H
