#include "replacement.h"
#include "sqlTools.h"

string Replacement::replace(string sString) {
    using namespace boost;

    string sRetVal;
    sRetVal = boost::regex_replace(sString, getRegex(), getReplacement());
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
    using boost::regex;
    using namespace boost::filesystem;

    sqlite3* db;
//    path dbFileName = initial_path()/"unitTest_Replacement.db3";
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
    rpAlpha.setRegex(regex("A"));
    rpAlpha.setReplacement("X");
    BOOST_CHECK(rpAlpha.getRegex() == regex("A"));
    BOOST_CHECK(rpAlpha.getReplacement() == "X");

    BOOST_CHECK(rpAlpha.replace("ABC") == "XBC");
    BOOST_CHECK(rpAlpha.replace("abcABCCBA") == "abcXBCCBX");
    BOOST_CHECK(rpAlpha.replace("abc") != "XBC");

}

#endif
