#include "replacements.h"
#include "error.h"

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

Replacements::Replacements(sqlite3* db) :
    mDb(db)
{
    exAssert(db!=NULL);
};

void Replacements::unitTest() {
    sqlite3* db;
//    path dbFileName = initial_path()/"unitTest_Replacements.db3";
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.native_file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);
//    createTables(db);

    Replacements rpAlpha(db);
}

#endif
