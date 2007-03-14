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


        #ifdef RENAMER_UNIT_TEST
        static void unitTest();
        #endif

//        //  attributes
//        boost::regex expression;
//        string replacement;
//        bool inherit;

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

//        //!set the regex as string, the string is validated
//        void setRegex(string v)
//            {mRow.set("regex", boost::regex(v).str());} ;
//
//        //!set the regex as string, the string was validated
//        string getRegex() const
//            { return mRow.get("regex"); };

    private:
        sqlite3* mDb;
        TableRow mRow;
};

#endif //REPLACEMENT_H
