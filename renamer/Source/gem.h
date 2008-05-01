/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


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

        //! save this object and all its children
        void save();

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
