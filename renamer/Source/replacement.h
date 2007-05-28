#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"

//! a regex with replacement values, which stored in the db
class Replacement {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! creates a new Replacement object.
        /** All Values are empty */
        Replacement(sqlite3* db) : mDb(db), mRow(db, "replacements") {}  ;

        //! creates a new Replacement object with existing data
        Replacement(sqlite3* db, sqlite_int64 row) : mDb(db), mRow(db, "replacements", row) {}  ;

        //---------------------------------------------------------------------
        //  methods


        //! Creates replacements table
        static void createTables(sqlite3* db);

        //! a result is returned regardless whether something matched
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
        sqlite_int64 getRowId() const
          { return mRow.getRowId(); };

        //! get replacements.GroupId
        sqlite_int64 getGroupId() const
          { return cSqlInFormated<sqlite_int64>(mRow.get("GroupId")); };

        //! set replacements.GroupId
        void setGroupId(sqlite_int64 v)
          { mRow.set("GroupId", cSqlOutFormated(v)); };

        //! reomves this object and all its children
        void remove();

        //! save this to db
        void save() { mRow.save(); };

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
