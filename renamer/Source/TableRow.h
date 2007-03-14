#ifndef TABLE_ROW
#define TABLE_ROW

#include "globals.h"

class TableRow {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! Create a new row
        TableRow(sqlite3* db, string table);

        //! Load a row
        TableRow(sqlite3* db, string table, sqlite_int64 rowid );

        //! writes to column
        string get(string field) const;

        //! read a column
        void set(string field, string value);

        string operator[](const string what) const {
            return get(what);
        }

        //---------------------------------------------------------------------
        //  methodes

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  attributes

        sqlite3* mDb;
        string mTable;
        sqlite_int64 mRowid;
};


#endif //TABLE_ROW

