#include "stdafx.h"
#include "TableRow.h"
#include "sqlTools.h"
#include "error.h"
#include "globals.h"

static const sqlite_int64 NO_TABLE = -1;

TableRow::TableRow(sqlite3* db, string table) {
    //we cant do anything useful here because
    //you cant INSERT a empty row. Since we have
    //no field names available here, we cant do
    //anything
    //we will remember that through the magic number
    //NO_TABLE (-1) in mRowid
    mRowid = NO_TABLE;
    mDb = db;
    mTable = table;
}

TableRow::TableRow(sqlite3* db, string table, string field, string value) {
    mRowid = NO_TABLE;
    mDb = db;
    mTable = table;
    set(field, value);
}

TableRow::TableRow(sqlite3* db, string table, sqlite_int64 rowid) {
    mRowid = rowid;
    mDb = db;
    mTable = table;
}

void TableRow::set(string field, string value) {
    stringstream strSql;

    if (mRowid == NO_TABLE) {
        strSql  << "INSERT INTO " << mTable
                << " (" << field
                <<" ) VALUES ( " << cSqlStrOut(value) << ")";
        exec(strSql, mDb);
        mRowid = sqlite3_last_insert_rowid(mDb);
        exAssert(mRowid != -1);

    } else {
        strSql  << "UPDATE " << mTable
                << " SET " << field << " = " << cSqlStrOut(value)
                << " WHERE rowid = " << mRowid;
        exec(strSql, mDb);
    }
}

string TableRow::get(string field) const {
    string sReturn;

    if (mRowid != NO_TABLE) {
        stringstream strSql;
        strSql  << "SELECT " << field
                << " FROM " << mTable
                << " WHERE rowid =" << mRowid;
        exec(strSql, mDb, onReadFirstField, &sReturn);
    }
    return sReturn;
}

sqlite_int64 TableRow::getRowId() const {
    exAssertDesc(mRowid != NO_TABLE, "nothing written yet");
    return mRowid;
};

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE myTable ("
           "   uniqueField string UNIQUE,"
           "   dummy string, "
           "NullColum string)";
    exec(sSql, db);

}

void TableRow::unitTest() {
    using boost::regex;

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
    rowAlpha.set("uniqueField", "Alpha");
    rowAlpha.set("dummy", "How are you?");
    BOOST_CHECK(rowAlpha.get("uniqueField") == "Alpha");
    BOOST_CHECK(rowAlpha.get("dummy") == "How are you?");

    TableRow rowBeta(db, "myTable");
    rowBeta.set("uniqueField", "Beta");
    rowBeta.set("dummy", "40647a02-d248-11db-8314-0800200c9a66");
    BOOST_CHECK(rowBeta.get("uniqueField") == "Beta");
    BOOST_CHECK(rowBeta.get("dummy") == "40647a02-d248-11db-8314-0800200c9a66");

    TableRow rowGamma(db, "myTable");
    rowGamma.set("uniqueField", "Gamma");
    rowGamma.set("dummy", "D'oh''");
    BOOST_CHECK(rowGamma.get("uniqueField") == "Gamma");
    BOOST_CHECK(rowGamma.get("dummy") == "D'oh''");


    BOOST_CHECKPOINT("operator[]");
    BOOST_CHECK(rowAlpha["uniqueField"] == "Alpha");
    BOOST_CHECK(rowAlpha["dummy"] == "How are you?");
    BOOST_CHECK(rowBeta["dummy"] == "40647a02-d248-11db-8314-0800200c9a66");

    BOOST_CHECKPOINT("null behauviour");
    //BOOST_CHECK(rowAlpha["NullColum"] == "");


}

#endif //RENAMER_UNIT_TEST

