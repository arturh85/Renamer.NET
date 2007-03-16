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

        //! get Gems.rowid
        sqlite_int64 getRowid() const
            { return cSqlInFormated<sqlite_int64>(mRow.get("rowid")); };

        //! the name of a gem is what the user wants it to be
        string getName() const
            { return mRow.get("name"); };

        //! the name of a gem is what the user wants it to be
        void setName(string v)
            {mRow.set("name",v);} ;

        //! the Position of a gem is what the user wants it to be
        int getPosition() const
            { return cSqlInFormated<int>(mRow.get("position")); };

        //! the Position of a gem is what the user wants it to be
        void setPosition(int v)
            {mRow.set("position", cSqlOutFormated(v));} ;

        //! the RuleId ties the gem to a InputRule
        sqlite_int64 getRuleId() const
            { return cSqlInFormated<sqlite_int64>(mRow.get("ruleId")); };

        //! the RuleId ties the gem to a InputRule
        void setRuleId(sqlite_int64 v)
            {mRow.set("ruleId", cSqlOutFormated(v));} ;


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
