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

void InputRule::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "   regex string UNIQUE)";
    exec(sSql, db);

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
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_WARN_NO_THROW( ruleAlpha.getRegex() == "(.*)\\.avi" );

    //!\todo this doesnt work, see http://tinyurl.com/3x984x
    BOOST_WARN_THROW( string("a"), exception );
    BOOST_WARN_NO_THROW( InputRule ruleAlpha(regex("("), db));

    //  clean up
    sqlite3_close(db);
}

#endif
