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

        string read(string field);

        string operator[](const string what) {
            return read(what);
        }

        //---------------------------------------------------------------------
        //  methodes

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        sqlite3* mDb;
        string mTable;
        sqlite_int64 mRowid;

    protected:
        void write(string field, string value);
};

#endif //TABLE_ROW

