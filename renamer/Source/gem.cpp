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
#include "Gem.h"
#include "sqlTools.h"
#include "error.h"

Gem::Gem(sqlite3* db, sqlite_int64 ruleId) :
    mDb(db), mRow(db, "Gems", "ruleId", cSqlOutFormated(ruleId)),
    replacers(db, "gem", mRow.getRowId())
{
    //setRuleId(ruleId);

    stringstream strSql;
    string sMaxPos;
    strSql  << "SELECT MAX(position) "
            << "FROM gems WHERE "
            << "ruleId = " << ruleId;
    exec(strSql, mDb, onReadFirstField, &sMaxPos);
    setPosition(cSqlInFormated<sqlite_int64>(sMaxPos,0)+1);

    Replacements newReplacements(mDb, "gem", mRow.getRowId() );
}

void Gem::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE gems ("
           "    ruleId ROWID , "
//           "    regexId ROWID, "
           "    name string, "
           "    position int)";
//           "    replacementGrpId)";
    exec(sSql, db);

//    sSql = "CREATE INDEX Gems_GroupedPrimaryKey "
//           "ON Gems ("
//           " ruleId, regexId)";
//    exec(sSql, db);

}

void Gem::setPosition(int v) {
    exAssertDesc(v>0, "minimal gem.position is 1");

//    stringstream strSql;
//    strSql  << "UPDATE gems SET "
//            << "position = position + 1 "
//            << "WHERE ruleId = " << getRuleId()
//            << " AND position >= " << v;
//    exec(strSql, mDb);

    mRow.set("position", cSqlOutFormated(v));
}

void Gem::save() {
    mRow.save();

    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Gem::unitTest() {
    BOOST_CHECKPOINT("begin");

    using boost::regex;

    sqlite3* db;
//    using namespace boost::filesystem;
//    path dbFileName = initial_path<path>()/"unitTest_Gem.db3";
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);
    BOOST_CHECKPOINT("create Tables");
    createTables(db);
    Replacement::createTables(db);
    Replacements::createTables(db);

    BOOST_CHECKPOINT("gemAlpha");
    Gem gemAlpha(db, 112233);
    gemAlpha.setName("Test");
    BOOST_CHECK(gemAlpha.getName() =="Test");
    gemAlpha.setPosition(1);
    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 1);
    BOOST_CHECK_EQUAL(gemAlpha.getRuleId(), 112233);

    BOOST_CHECKPOINT("gemBeta");
    Gem gemBeta(db, 112233);
    gemBeta.setName("Umlaute: ÖÄÜöäü");
    BOOST_CHECK(gemBeta.getName() =="Umlaute: ÖÄÜöäü");
    gemBeta.setPosition(2);
    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 2);
    BOOST_CHECK_EQUAL(gemBeta.getRuleId(), 112233);

    BOOST_CHECKPOINT("gemGamma");
    Gem gemGamma(db, 112233);
    gemGamma.setName("Umlaute: ÖÄÜöäü");
    BOOST_CHECK(gemGamma.getName() =="Umlaute: ÖÄÜöäü");
    gemGamma.setPosition(3);
    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 3);
    BOOST_CHECK_EQUAL(gemGamma.getRuleId(), 112233);
    BOOST_CHECK_THROW(gemGamma.setPosition(-1), exFileLineDesc);
    BOOST_CHECK_THROW(gemGamma.setPosition(0), exFileLineDesc);
//    gemGamma.setPosition(2);
//    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 1);
//    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 3);
//    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 2);

    BOOST_CHECKPOINT("gemDelta");
    Gem gemDelta(db, 112233);
    gemDelta.setPosition(4);
    BOOST_CHECK_EQUAL(gemDelta.getPosition(), 4);
//    gemDelta.setPosition(1);
//    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 2);
//    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 4);
//    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 3);
//    BOOST_CHECK_EQUAL(gemDelta.getPosition(), 1);

    BOOST_CHECKPOINT("replacers");
    gemAlpha.replacers.addReplacement(".*","test");
    BOOST_CHECK(gemAlpha.replacers.getReplacements().size()==1);

    BOOST_CHECKPOINT("clean up");
    gemAlpha.remove();
    gemBeta.remove();
    gemDelta.remove();
    gemGamma.remove();
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM gems", db) , "0");
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM replacements", db) , "0");
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM replacementGroups", db) , "0");


}

#endif
