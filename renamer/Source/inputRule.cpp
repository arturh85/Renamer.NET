#include "stdafx.h"
#include "inputRule.h"
#include "sqlTools.h"
#include <sstream>
#include "sqlTools.h"

using boost::regex;
using boost::smatch;
using namespace boost::filesystem;

InputRule::InputRule(sqlite_int64 rowid, sqlite3* db) {
    mRowid = rowid;
    mDb = db;
}

InputRule::InputRule(boost::regex exp, sqlite3* db) {
    mDb = db;

    stringstream strRegex;
    strRegex << strRegex;

    string sSql =
        "INSERT INTO regexes (regex) "
        "VALUES (" + cSqlStrOut(exp.str()) + ")";
    exec(sSql, mDb);

    mRowid = sqlite3_last_insert_rowid(db);
}

string InputRule::getRegex() const {
    string sRetVal;
    stringstream strSql;
    strSql  << "SELECT regex FROM regexes WHERE rowid = "
            << mRowid;
    exec(strSql.str(), mDb, onReadFirstField, &sRetVal );

    return sRetVal;
}

//! Creates 'regexes' and 'history' table
void InputRule::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "   regex string UNIQUE)";
    exec(sSql, db);

    sSql = "CREATE TABLE history ("
           "   fileName string UNIQUE,"
           "   regex ROWID)";
    exec(sSql, db);

}

//! change regex
bool InputRule::setRegex(string sRegex) {

    regex newRegex(sRegex);
    vector<string> results;

    stringstream strSql;
    strSql  << "SELECT fileName FROM history "
            << "WHERE regex = " << mRowid;

    exec(strSql.str(), mDb, onAppendFirstColumnToVector, &results);

    vector<string> mismatches;
    for (vector<string>::iterator it = results.begin();
         it != results.end(); it++) {

        //cout << "-> " << *it << endl;

    }
    return true;
}

//! try to match a fileName against a single regex
/**
    This method updates the history table.
*/
bool InputRule::applyTo(string fileName, string& outputFileName) {
    regex exp(getRegex());
    smatch what;
    if (regex_match(fileName, what, exp)) {
        //vector<string> vars = stripVarNames()
        stringstream strSql;
        strSql  << "INSERT INTO history (fileName, regex) "
                << "VALUES ("
                << cSqlStrOut(fileName) << ", "
                << mRowid << ")";
        exec(strSql.str(), mDb);
        return true;
    }

    return false;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void InputRule::unitTest() {
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

    InputRule::createTables(db);

    BOOST_CHECKPOINT("InputRule new regex constructor");
    InputRule ruleAlpha(regex("(.*)\\.avi"), db);
    InputRule ruleBeta(regex("(.*)\\.mpg"), db);
    InputRule ruleGamma(regex("(.*)\\.jpg"), db);

    BOOST_CHECKPOINT("getRegex(), first time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    BOOST_CHECKPOINT("getRegex(), second time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    BOOST_CHECKPOINT("applyTo()");
    string sDummy;
    BOOST_CHECK(ruleAlpha.applyTo("Test.avi", sDummy));
    BOOST_CHECK(!ruleAlpha.applyTo("Test.mpg", sDummy));
    BOOST_CHECK(!ruleAlpha.applyTo("Test.jpg", sDummy));

    BOOST_CHECK(!ruleBeta.applyTo("Test.avi", sDummy));
    BOOST_CHECK(ruleBeta.applyTo("Test.mpg", sDummy));
    BOOST_CHECK(!ruleBeta.applyTo("Test.jpg", sDummy));

    BOOST_CHECK(!ruleGamma.applyTo("Test.avi", sDummy));
    BOOST_CHECK(!ruleGamma.applyTo("Test.mpg", sDummy));
    BOOST_CHECK(ruleGamma.applyTo("Test.jpg", sDummy));

    BOOST_CHECK(ruleAlpha.applyTo("Name mit Blank.avi", sDummy));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.mpg", sDummy));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.jpg", sDummy));

    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.avi", sDummy));
    BOOST_CHECK(ruleBeta.applyTo("Name mit Blank.mpg", sDummy));
    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.jpg", sDummy));

    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.avi", sDummy));
    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.mpg", sDummy));
    BOOST_CHECK(ruleGamma.applyTo("Name mit Blank.jpg", sDummy));

    BOOST_CHECKPOINT("setRegex()");
    BOOST_CHECK(ruleAlpha.setRegex("Test\\.*"));

    //  clean up
    sqlite3_close(db);
}

#endif
