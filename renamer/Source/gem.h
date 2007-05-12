#ifndef GEM_H
#define GEM_H

#include "globals.h"
#include "TableRow.h"
#include "sqlTools.h"
#include "replacements.h"

//! a gem is the description of a extracted string
class Gem {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! creates a new Gem object.
        /** All Values are empty */
        Gem(sqlite3* db, sqlite_int64 ruleId);

        //! creates a new Gem object with existing data
        Gem(sqlite3* db, sqlite_int64 ruleId, sqlite_int64 row) :
            mDb(db), mRow(db, "Gems", row), replacers(db, "gem", row) { setRuleId(ruleId); }  ;

        //---------------------------------------------------------------------
        //  methodes


        //! Creates Gems table
        static void createTables(sqlite3* db);

        //! get Gems.rowid
        sqlite_int64 getRowId() const
            { return mRow.getRowId(); };
            //{ return cSqlInFormated<sqlite_int64>(mRow.get("rowid")); };

        //! the name of a gem is what the user wants it to be
        string getName() const
            { return mRow.get("name"); };

        //! the name of a gem is what the user wants it to be
        void setName(string v)
            {mRow.set("name",v);} ;

        //! the Position of a gem is what the user wants it to be
        int getPosition() const
            { return cSqlInFormated<int>(mRow.get("position"), -1); };

        //! the Position of a gem is what the user wants it to be
        void setPosition(int v);

        //! the RuleId ties the gem to a InputRule
        sqlite_int64 getRuleId() const
            { return cSqlInFormated<sqlite_int64>(mRow.get("ruleId")); };

        //! reomves this object and all its children
        void remove();

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  attributes
        sqlite3* mDb;
        TableRow mRow;

        //---------------------------------------------------------------------
        //  methodes

        //! the RuleId ties the gem to a InputRule
        void setRuleId(sqlite_int64 v)
            {mRow.set("ruleId", cSqlOutFormated(v));} ;

    public:
        //---------------------------------------------------------------------
        //  attributes
        Replacements replacers;


};

#endif //GEM_H
