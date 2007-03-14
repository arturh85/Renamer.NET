#include "TableRow.h"
#include "sqlTools.h"


TableRow::TableRow(sqlite3* db, string table) {
    //we cant do anything usefull here because
    //you cant INSERT a empty row. Since we have
    //no field names available here, we cant do
    //anything
    //we will rember that through the magic number
    //-1 in mRowid
    mRowid = -1;
    mDb = db;
    mTable = table;
}

TableRow::TableRow(sqlite3* db, string table, sqlite_int64 rowid) {
    mRowid = rowid;
    mDb = db;
    mTable = table;
}

void TableRow::write(string field, string value) {
    stringstream strSql;

    if (mRowid == -1) {
        strSql  << "INSERT INTO " << mTable
                << " (" << field
                <<" ) VALUES ( " << cSqlStrOut(value) << ")";
        exec(strSql, mDb);
        mRowid = sqlite3_last_insert_rowid(mDb);

    } else {
        strSql  << "UPDATE " << mTable
                << " SET " << field << " = " << cSqlStrOut(value)
                << " WHERE rowid = " << mRowid;
        exec(strSql, mDb);
    }
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE myTable ("
           "   someField string UNIQUE,"
           "   dummy string)";
    exec(sSql, db);

}

void TableRow::unitTest() {

    sqlite3* db;
//    // test Ruleset class
//    path dbFileName = initial_path()/"unitTest_InputRule.db3";
//
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.native_file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);

    createTables(db);

    TableRow rowAlpha(db, "myTable");
    rowAlpha.write("someField", "Hi");
    rowAlpha.write("dummy", "How are you?");
}

#endif //RENAMER_UNIT_TEST

