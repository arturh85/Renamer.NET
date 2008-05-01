/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


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
