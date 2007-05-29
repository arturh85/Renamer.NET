#include "stdafx.h"
#include "replacement.h"
#include "sqlTools.h"

string Replacement::replace(string sString) {
    using namespace boost;

    string sRetVal;
    sRetVal = boost::regex_replace(sString, getRegex(), getReplacement());
    return sRetVal;
}

void Replacement::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE replacements ("
           "    regex string, "
           "    replacement string, "
           "    groupId ROWID)";
    exec(sSql, db);

}

void Replacement::remove() {
    stringstream strSql;
    strSql << "DELETE FROM replacements WHERE rowid = "
           << cSqlOutFormated(getRowId());
    //cout << strSql.str() << endl;
    exec(strSql, mDb);
    return;

}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Replacement::unitTest() {
    using boost::regex;
    using namespace boost::filesystem;

    sqlite3* db;
//    path dbFileName = initial_path<path>()/"unitTest_Replacement.db3";
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);
    createTables(db);

    Replacement rpAlpha(db);
    rpAlpha.setRegex(regex("A"));
    rpAlpha.setReplacement("X");
    rpAlpha.setGroupId(4711);
    BOOST_CHECK(rpAlpha.getRegex() == regex("A"));
    BOOST_CHECK(rpAlpha.getReplacement() == "X");
    BOOST_CHECK(rpAlpha.getGroupId() == 4711);

    BOOST_CHECK(rpAlpha.replace("ABC") == "XBC");
    BOOST_CHECK(rpAlpha.replace("ABCEFG") == "XBCEFG");
    BOOST_CHECK(rpAlpha.replace("abcABCCBA") == "abcXBCCBX");

    BOOST_CHECK(rpAlpha.replace("abc") != "XBC");

    BOOST_CHECKPOINT("getRowId");
    BOOST_CHECK(rpAlpha.getRowId() == sqlite3_last_insert_rowid(db));


    Replacement rpBeta(db);
    rpBeta.setRegex(regex("\\."));
    rpBeta.setReplacement(" ");
    BOOST_CHECK(rpBeta.replace("Family.Guy.S06E13.PDTV.XviD-LOL.avi") == "Family Guy S06E13 PDTV XviD-LOL avi");

    BOOST_CHECKPOINT("clean up");
    rpAlpha.remove();
    rpBeta.remove();
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM replacements", db) , "0");

}

#endif
