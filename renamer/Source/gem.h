#ifndef GEM_H
#define GEM_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"

class Gem {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! creates a new Gem object.
        /** All Values are empty */
        Gem(sqlite3* db) : mRow(db, "Gems") {}  ;

        //! creates a new Gem object with existing data
        Gem(sqlite3* db, sqlite_int64 row) : mRow(db, "Gems", row) {}  ;

        //---------------------------------------------------------------------
        //  methodes


        //! Creates Gems table
        static void createTables(sqlite3* db);

        //! if the regex matches it is replaced with this
        string getGem() const
            { return mRow.get("Gem"); };

        //! if the regex matches it is replaced with this
        void setGem(string v)
            {mRow.set("Gem",v);} ;

        //! get Gems.rowid
        sqlite_int64 getRowid() const
          { return cSqlInFormated<sqlite_int64>(mRow.get("rowid")); };

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

#endif //GEM_H
