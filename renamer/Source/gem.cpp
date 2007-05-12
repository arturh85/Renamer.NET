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

    stringstream strSql;
    strSql  << "UPDATE gems SET "
            << "position = position + 1 "
            << "WHERE ruleId = " << getRuleId()
            << " AND position >= " << v;
    exec(strSql, mDb);

    mRow.set("position", cSqlOutFormated(v));
}

void Gem::remove() {
    stringstream strSql;
    strSql << "DELETE FROM gems WHERE rowid = "
           << cSqlOutFormated(getRowId());
    //cout << strSql.str() << endl;
    exec(strSql, mDb);
    return;

}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Gem::unitTest() {
    using boost::regex;

    sqlite3* db;
//    using namespace boost::filesystem;
//    path dbFileName = initial_path()/"unitTest_Gem.db3";
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.native_file_string().c_str(), &db)) {
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
    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 1);
    BOOST_CHECK_EQUAL(gemAlpha.getRuleId(), 112233);

    BOOST_CHECKPOINT("gemBeta");
    Gem gemBeta(db, 112233);
    gemBeta.setName("Umlaute: ÖÄÜöäü");
    BOOST_CHECK(gemBeta.getName() =="Umlaute: ÖÄÜöäü");
    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 2);
    BOOST_CHECK_EQUAL(gemBeta.getRuleId(), 112233);

    BOOST_CHECKPOINT("gemGamma");
    Gem gemGamma(db, 112233);
    gemGamma.setName("Umlaute: ÖÄÜöäü");
    BOOST_CHECK(gemGamma.getName() =="Umlaute: ÖÄÜöäü");
    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 3);
    BOOST_CHECK_EQUAL(gemGamma.getRuleId(), 112233);
    BOOST_CHECK_THROW(gemGamma.setPosition(-1), exFileLineDesc);
    BOOST_CHECK_THROW(gemGamma.setPosition(0), exFileLineDesc);
    gemGamma.setPosition(2);
    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 1);
    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 3);
    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 2);

    BOOST_CHECKPOINT("gemDelta");
    Gem gemDelta(db, 112233);
    BOOST_CHECK_EQUAL(gemDelta.getPosition(), 4);
    gemDelta.setPosition(1);
    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 2);
    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 4);
    BOOST_CHECK_EQUAL(gemGamma.getPosition(), 3);
    BOOST_CHECK_EQUAL(gemDelta.getPosition(), 1);

    BOOST_CHECKPOINT("replacers");
    gemAlpha.replacers.addReplacement(".*","test");
    BOOST_CHECK(gemAlpha.replacers.getReplacements().size()==1);

    BOOST_CHECKPOINT("clean up");
    gemAlpha.remove();
    gemBeta.remove();
    gemDelta.remove();
    gemGamma.remove();
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM gems", db) , "0");


}

#endif
