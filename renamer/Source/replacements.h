#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"
#include "replacement.h"

class Replacements {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacements(sqlite3* db, sqlite_int64 ownerId);

        //---------------------------------------------------------------------
        //  methodes

        string replace(string);
        void addReplacement(string regex, string replacement);
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
        Replacements* mParent;
        sqlite_int64 mOwnerId;
};

#endif //REPLACEMENTS_H
