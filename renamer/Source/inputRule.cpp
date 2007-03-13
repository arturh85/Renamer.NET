#include "stdafx.h"
#include "inputRule.h"
#include "sqlTools.h"
#include <sstream>
#include "sqlTools.h"

using boost::regex;

//InputRule::InputRule(sqlite_rowid rowid, sqlite3* db) {
//    mRowid = rowid;
//    mDb = db;
//}

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

//! Creates 'regexes' table
void InputRule::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "   regex string UNIQUE)";
    exec(sSql, db);

}

//! change regex
void InputRule::setRegex(string sRegex) {
    regex newRegex(sRegex);
    vector<vector<string> > results;

    stringstream strSql;
    strSql  << "SELECT history.fileName "
            << "WHERE regexes.rowid = " << mRowid;
    exec(strSql.str(), mDb, onAppendAllColumnsToVector, &results);

    for (vector<vector<string> >::iterator it = results.begin();
         it != results.end(); it++) {

        vector<string>& row = *it;
    }
    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void InputRule::unitTest() {
    BOOST_CHECK(true);

    sqlite3* db;

    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);

    InputRule::createTables(db);

    InputRule ruleAlpha(regex("(.*)\\.avi"), db);
    InputRule ruleBeta(regex("(.*)\\.mpg"), db);
    InputRule ruleGamma(regex("(.*)\\.jpg"), db);

    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    //!\todo this doesnt work, see http://tinyurl.com/3x984x
    BOOST_WARN_THROW( string("a"), exception );
    BOOST_WARN_NO_THROW( InputRule ruleAlpha(regex("("), db));

    //  clean up
    sqlite3_close(db);
}

#endif
