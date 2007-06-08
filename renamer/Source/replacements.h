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
