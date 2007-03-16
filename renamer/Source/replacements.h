#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"
#include "replacement.h"

class Replacements {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacements(sqlite3* db, sqlite_int64 ownerId, string ownerClass);
        Replacements(sqlite3* db, sqlite_int64 ownerId, string ownerClass, Replacements& parent);

        //---------------------------------------------------------------------
        //  methodes

        //!apply replacements of this object and parents
        string replace(string) const;

        //! attach a new replacement to this object
        void addReplacement(string regex, string replacement);

        //!get all the replacements attached to this object
        vector<Replacement> getReplacements() const;

        //! Creates replacementGroups table
        static void createTables(sqlite3* db);

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  attributes

        sqlite3* mDb;
        sqlite_int64 mOwnerId;
        string mOwnerClass;
        Replacements* mParent;
};

#endif //REPLACEMENTS_H
