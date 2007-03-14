#include "TableRow.h"
#include "sqlTools.h"
#include "error.h"


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
        exAssert(mRowid != -1);

    } else {
        strSql  << "UPDATE " << mTable
                << " SET " << field << " = " << cSqlStrOut(value)
                << " WHERE rowid = " << mRowid;
        exec(strSql, mDb);
    }
}

string TableRow::read(string field) {
    string sReturn;

    if (mRowid != -1) {
        stringstream strSql;
        strSql  << "SELECT " << field
                << " FROM " << mTable
                << " WHERE rowid =" << mRowid;
        exec(strSql, mDb, onReadFirstField, &sReturn);
    }
    return sReturn;
}

//string TableRow::operator[](const string what) {
//    return
//}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE myTable ("
           "   uniqueField string UNIQUE,"
           "   dummy string)";
    exec(sSql, db);

}

class foobar : public TableRow {
    public:
        foobar(sqlite3*  db) : TableRow(db, "myTable") {};

        void set(string field, string value) {
            write(field, value);
        };
};

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

    foobar rowAlpha(db);
    rowAlpha.write("uniqueField", "Hi");
    rowAlpha.write("dummy", "How are you?");
    BOOST_CHECK(rowAlpha.read("uniqueField") == "Hi");
    BOOST_CHECK(rowAlpha.read("dummy") == "How are you?");

    foobar rowBeta(db);
    rowBeta.write("uniqueField", "dummy");
    rowBeta.write("dummy", "40647a02-d248-11db-8314-0800200c9a66");
    BOOST_CHECK(rowBeta.read("uniqueField") == "dummy");
    BOOST_CHECK(rowBeta.read("dummy") == "40647a02-d248-11db-8314-0800200c9a66");

    foobar rowGamma(db);
    rowGamma.write("uniqueField", "test");
    rowGamma.write("dummy", "How are you?");
    BOOST_CHECK(rowGamma.read("uniqueField") == "test");
    BOOST_CHECK(rowGamma.read("dummy") == "How are you?");

    BOOST_CHECK(rowAlpha.read("uniqueField") == "Hi");
    BOOST_CHECK(rowAlpha.read("dummy") == "How are you?");

    BOOST_CHECKPOINT("operator[]");
    BOOST_CHECK(rowAlpha["uniqueField"] == "Hi");
    BOOST_CHECK(rowAlpha["dummy"] == "How are you?");
    BOOST_CHECK(rowBeta["dummy"] == "40647a02-d248-11db-8314-0800200c9a66");

}

#endif //RENAMER_UNIT_TEST

