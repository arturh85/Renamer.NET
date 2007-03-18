#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"

class Replacement {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! creates a new Replacement object.
        /** All Values are empty */
        Replacement(sqlite3* db) : mRow(db, "replacements") {}  ;

        //! creates a new Replacement object with existing data
        Replacement(sqlite3* db, sqlite_int64 row) : mRow(db, "replacements", row) {}  ;

        //---------------------------------------------------------------------
        //  methodes


        //! Creates replacements table
        static void createTables(sqlite3* db);

        //! a result is returnt regardless wether something matched
        string replace(string);

        //! if the regex matches it is replaced with this
        string getReplacement() const
            { return mRow.get("replacement"); };

        //! if the regex matches it is replaced with this
        void setReplacement(string v)
            {mRow.set("replacement",v);} ;

        //! what should be replaced?
        boost::regex getRegex() const
            { return boost::regex(mRow.get("regex")); };

        //! convenience function with string type parameter
        void setRegex(string v)
            {mRow.set("regex", boost::regex(v).str()  );} ;

        //! what should be replaced?
        void setRegex(boost::regex v)
            {mRow.set("regex", v.str());} ;

        //! get replacements.rowid
        sqlite_int64 getRowid() const
          { return cSqlInFormated<sqlite_int64>(mRow.get("rowid")); };

        //! get replacements.GroupId
        sqlite_int64 getGroupId() const
          { return cSqlInFormated<sqlite_int64>(mRow.get("GroupId")); };

        //! set replacements.GroupId
        void setGroupId(sqlite_int64 v)
          { mRow.set("GroupId", cSqlOutFormated(v)); };

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
