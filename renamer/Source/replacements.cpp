#include "replacements.h"
#include "error.h"

Replacements::Replacements(sqlite3* db, sqlite_int64 ownerId) :
    mDb(db), mOwnerId(ownerId)
{
    exAssert(db!=NULL);
};

void Replacements::addReplacement(string sRegex, string replacement) {
    Replacement newReplacement(mDb);
    newReplacement.setRegex(sRegex);
    newReplacement.setReplacement(replacement);
    newReplacement.setOwnerId(mOwnerId);

    stringstream strSql;
    strSql  << "INSERT INTO replacementGroups "
            << "(replacementId, ownerId) VALUES ( "
            << newReplacement.getRowid() << ", "
            << mOwnerId << ")";
    exec(strSql, mDb);
    return;
}

void Replacements::createTables(sqlite3* db) {
    stringstream strSql;

    strSql  << "CREATE TABLE replacementGroups ("
            << "replacementId ROWID, "
            << "ownerId ROWID) ";
    exec(strSql, db);
}

vector<Replacement> Replacements::getReplacements() const {
    typedef vector<Replacement> vtype;
    vtype retVal;
    vector<string> rowidStrings;

    string sSql =
        "SELECT replacementId "
        "FROM replacementGroups "
        "WHERE ownerId = " + cSqlOutFormated(mOwnerId);
    exec(sSql, mDb, onAppendFirstColumnToVector, &rowidStrings);
//    cout << "sql "<< sSql << endl;
//    cout << "COUNT "<< rowidStrings.size() << endl;

    for (vector<string>::iterator it = rowidStrings.begin();
         it != rowidStrings.end(); it++) {

        Replacement newReplacement(mDb, cSqlInFormated<sqlite_int64>(*it));
        retVal.push_back(newReplacement);
    }


    return retVal;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Replacements::unitTest() {
    sqlite3* db;

//    using namespace boost::filesystem;
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
    Replacement::createTables(db);
    createTables(db);

    Replacements rpAlpha(db, -1);
    Replacements rpBeta(db, -100);
    rpAlpha.addReplacement("test", "TEST");
    BOOST_CHECK_EQUAL(int(rpAlpha.getReplacements().size()) , 1);

    rpBeta.addReplacement("\\d", "Zahl");
    rpAlpha.addReplacement("\\d", "Zahl");
    BOOST_CHECK(rpAlpha.getReplacements().size()==2);

    int n=rpAlpha.getReplacements().size();
    BOOST_CHECK_EQUAL(int(rpAlpha.getReplacements().size()) , 2);

    BOOST_CHECK(rpAlpha.getReplacements()[0].getRegex().str() == "test");
    BOOST_CHECK(rpAlpha.getReplacements()[0].getReplacement() == "TEST");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getRegex().str() == "\\d");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getReplacement() == "Zahl");
}

#endif
