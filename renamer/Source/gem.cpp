#include "Gem.h"
#include "sqlTools.h"

void Gem::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE Gems ("
           "    ruleId ROWID, "
           "    regexId ROWID, "
           "    name string, "
           "    position int)";
    exec(sSql, db);

}


#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Gem::unitTest() {
    using boost::regex;
    using namespace boost::filesystem;

    sqlite3* db;
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
    createTables(db);

    Gem gemAlpha(db);
    gemAlpha.setName("Test");
    gemAlpha.setPosition(123);
    gemAlpha.setRuleId(112233);
    BOOST_CHECK(gemAlpha.getName() =="Test");
    BOOST_CHECK_EQUAL(gemAlpha.getPosition(), 123);
    BOOST_CHECK_EQUAL(gemAlpha.getRuleId(), 112233);

    Gem gemBeta(db);
    gemBeta.setName("Umlaute: ÖÄÜöäü");
    gemBeta.setPosition(123);
    gemBeta.setRuleId(-1);
    BOOST_CHECK(gemBeta.getName() =="Umlaute: ÖÄÜöäü");
    BOOST_CHECK_EQUAL(gemBeta.getPosition(), 123);
    BOOST_CHECK_EQUAL(gemBeta.getRuleId(), -1);
}

#endif
