#include "Gem.h"
#include "sqlTools.h"

void Gem::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE Gems ("
           "    regex string, "
           "    Gem string, "
           "    ownerId ROWI, "
           "    ownerClass string)";
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

    Gem rpAlpha(db);

}

#endif
