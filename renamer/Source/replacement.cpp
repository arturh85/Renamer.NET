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

    Replacement rpAlpha;
    rpAlpha.expression = "A";
    rpAlpha.replacement = "X";
    BOOST_CHECK(rpAlpha.replace("ABC") == "XBC");
    BOOST_CHECK(rpAlpha.replace("abcABCCBA") == "abcXBCCBX");
    BOOST_CHECK(rpAlpha.replace("abc") != "XBC");

}

#endif
