#include "replacement.h"
#include "sqlTools.h"

string Replacement::replace(string sString) {
    string sRetVal;

    sRetVal = regex_replace(sString, expression, replacement);

    return sRetVal;
}

//! Creates replacements table
void Replacement::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE replacements ("
           "    regex string UNIQUE, "
           "    replacement string)";
    exec(sSql, db);

}


#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Replacement::unitTest() {
    BOOST_CHECK(true);

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

    Replacement rpAlpha(db);
    rpAlpha.expression = "A";
    rpAlpha.replacement = "X";

    rpAlpha.write("replacement", "X");
    BOOST_CHECK(rpAlpha["replacement"] == "X");

    BOOST_CHECK(rpAlpha.replace("ABC") == "XBC");
    BOOST_CHECK(rpAlpha.replace("abcABCCBA") == "abcXBCCBX");
    BOOST_CHECK(rpAlpha.replace("abc") != "XBC");

}

#endif
