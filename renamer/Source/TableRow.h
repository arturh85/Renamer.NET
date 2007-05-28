#ifndef TABLE_ROW
#define TABLE_ROW

#include "globals.h"

//! generic access to sqlite tables
class TableRow {
    public:
        static const sqlite_int64 NO_TABLE = -1;

        //---------------------------------------------------------------------
        //  constructors

        //! Create a new row
        TableRow(sqlite3* db, string table);

        //! Create a new row and set one value
        TableRow(sqlite3* db, string table, string field, string value);

        //! Load a row
        TableRow(sqlite3* db, string table, sqlite_int64 rowid );

        //! writes to column
        string get(string field) const;

        //! read a column
        void set(string field, string value)
            { mfDirty = true;
              mValues[field] = value;
              if(mRowid == NO_TABLE) save(); };

        string operator[](const string what) const
            { return get(what); }

        //! get the rowId
        sqlite_int64 getRowId() const;

        //! get the connection...
        sqlite3* getDb() const { return mDb; };

        //! store cached data into db
        void save();

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
        map<string, string> mValues;
        bool mfDirty;
};


#endif //TABLE_ROW

