#ifndef REPLACEMENTS_H
#define REPLACEMENTS_H

#include "globals.h"
#include "replacement.h"

class Replacements {
    public:
        //---------------------------------------------------------------------
        //  constructors
        Replacements(sqlite3* db, string name, sqlite_int64 ownerId);

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

        /** this is stored as an attribute, because we dont
            wont add an entry to the replacementGroups table
            even if there are no replacements. to do this a row
            is only inserted in the addReplacement method.
        */
        string mName;
        sqlite_int64 mOwnerId;

//        /** this point is null if no replacements
//            available
//        */
//        TableRow* mGroupPtr;


//        Replacements* mParent;
};

#endif //REPLACEMENTS_H
