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


#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"
#include "replacement.h"

//! collection of replacements
class Replacements {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacements(sqlite3* db, string name, sqlite_int64 ownerId);

        //---------------------------------------------------------------------
        //  methods

        //!apply replacements of this object and parents
        string replace(string) const;

        //! attach a new replacement to this object
        Replacement* addReplacement(string regex, string replacement);

        //!get all the replacements attached to this object
        vector<Replacement*> getReplacements() const;

        //! Creates replacementGroups table
        static void createTables(sqlite3* db);

        //! removes this object and all its children
        void remove();

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

        /** this is stored as an attribute, because we don't
            want add an entry to the replacementGroups table
            even if there are no replacements. to do this a row
            is only inserted in the addReplacement method.
        */
        string mName;
        sqlite_int64 mOwnerId;
        map<sqlite_int64, Replacement*> mChildren;
};

#endif //REPLACEMENTS_H
