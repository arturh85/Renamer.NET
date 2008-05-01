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
          { return cSqlInFormated<sqlite_int64>(mRow.get("groupId")); };

        //! set replacements.GroupId
        void setGroupId(sqlite_int64 v)
          { mRow.set("groupId", cSqlOutFormated(v)); };

        //! removes this object and all its children
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

		Replacement(const Replacement& r) : mDb(NULL), mRow(NULL, "replacements") {

		}

        sqlite3* mDb;
        TableRow mRow;
};

#endif //REPLACEMENT_H
