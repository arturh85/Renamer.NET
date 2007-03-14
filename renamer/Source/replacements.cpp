#include "replacements.h"
#include "error.h"

Replacements::Replacements(sqlite3* db, sqlite_int64 ownerId, string ownerClass) :
    mDb(db), mOwnerId(ownerId), mOwnerClass(ownerClass)
{
    mParent = NULL;
    exAssert(db!=NULL);
};

Replacements::Replacements(sqlite3* db, sqlite_int64 ownerId, string ownerClass, Replacements& parent) :
    mDb(db), mOwnerId(ownerId), mParent(&parent), mOwnerClass(ownerClass)
{
    exAssert(db!=NULL);
};

void Replacements::addReplacement(string sRegex, string replacement) {
    Replacement newReplacement(mDb);
    newReplacement.setRegex(sRegex);
    newReplacement.setReplacement(replacement);
    newReplacement.setOwnerId(mOwnerId);
    newReplacement.setOwnerClass(mOwnerClass);

//    stringstream strSql;
//    strSql  << "INSERT INTO replacementGroups "
//            << "(replacementId, ownerId) VALUES ( "
//            << newReplacement.getRowid() << ", "
//            << mOwnerId << ")";
//    exec(strSql, mDb);
    return;
}

void Replacements::createTables(sqlite3* db) {
//    stringstream strSql;
//
//    strSql  << "CREATE TABLE replacementGroups ("
//            << "replacementId ROWID, "
//            << "ownerId ROWID) ";
//    exec(strSql, db);
}

vector<Replacement> Replacements::getReplacements() const {
    typedef vector<Replacement> vtype;
    vtype retVal;
    vector<string> rowidStrings;

    stringstream strSql;
    strSql  << "SELECT rowid "
            << "FROM replacements "
            << "WHERE ownerId = " << mOwnerId
            << " AND ownerClass = " << cSqlStrOut(mOwnerClass);
    exec(strSql, mDb, onAppendFirstColumnToVector, &rowidStrings);

    for (vector<string>::iterator it = rowidStrings.begin();
         it != rowidStrings.end(); it++) {

        Replacement newReplacement(mDb, cSqlInFormated<sqlite_int64>(*it));
        retVal.push_back(newReplacement);
    }


    return retVal;
}

string Replacements::replace(string sString) const {
    string sRetVal = sString;
    vector<Replacement> replacements = getReplacements();

    for (int nAttempt = 0; nAttempt < 5; nAttempt++) {
        //cout << "loop: " << sRetVal << " >" << nAttempt << endl;
        bool fLoop = false;
        for (vector<Replacement>::iterator it= replacements.begin();
             it != replacements.end(); it++) {

            string sNewString = it->replace(sRetVal);
            if (sRetVal != sNewString) {
                sRetVal = sNewString;
                fLoop = true;
            }
        }

        if (!fLoop) break;
    }

    if (mParent)
      sRetVal = mParent->replace(sRetVal);

    return sRetVal;
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

    BOOST_CHECKPOINT("create objects");
    Replacements rpAlpha(db, -1, "Replacements::unitTest");
    Replacements rpBeta(db, -100, "Replacements::unitTest");
    rpAlpha.addReplacement("test", "TEST");
    BOOST_CHECK_EQUAL(int(rpAlpha.getReplacements().size()) , 1);

    BOOST_CHECKPOINT("getReplacements()");
    rpBeta.addReplacement("\\d", "Zahl");
    rpAlpha.addReplacement("\\d", "Zahl");
    BOOST_CHECK(rpAlpha.getReplacements().size()==2);

    int n=rpAlpha.getReplacements().size();
    BOOST_CHECK_EQUAL(int(rpAlpha.getReplacements().size()) , 2);

    BOOST_CHECK(rpAlpha.getReplacements()[0].getRegex().str() == "test");
    BOOST_CHECK(rpAlpha.getReplacements()[0].getReplacement() == "TEST");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getRegex().str() == "\\d");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getReplacement() == "Zahl");


    BOOST_CHECKPOINT("replace()");
    BOOST_CHECK(rpAlpha.replace("testing") == "TESTing");
    BOOST_CHECK(rpAlpha.replace("te3sting") == "teZahlsting");


    BOOST_CHECKPOINT("inheritence");
    Replacements rpGamma(db, -200, "Replacements::unitTest", rpAlpha );
    rpGamma.addReplacement("xyz", "?");
    BOOST_CHECK(rpGamma.replace("testing") == "TESTing");
    BOOST_CHECK(rpGamma.replace("te3sting") == "teZahlsting");

    BOOST_CHECKPOINT("ownerClass");
    Replacements rpZeta(db, -200, "foobar");
    BOOST_CHECK_EQUAL(int(rpZeta.getReplacements().size()) , 0);


}

#endif
