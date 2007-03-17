#include "stdafx.h"
#include "inputRule.h"
#include "sqlTools.h"
#include <sstream>
#include "sqlTools.h"
#include "error.h"

using boost::regex;
using boost::smatch;
using namespace boost::filesystem;

InputRule::InputRule(sqlite_int64 rowid, sqlite3* db) {
    mRowid = rowid;
    mDb = db;
    mRplPtr = new Replacements(db, rowid, "InputRule");
}

InputRule::InputRule(boost::regex exp, sqlite3* db) {
    mDb = db;

    stringstream strRegex;
    strRegex << strRegex;

    string sSql =
        "INSERT INTO regexes (regex) "
        "VALUES (" + cSqlStrOut(exp.str()) + ")";
    exec(sSql, mDb);

    mRowid = sqlite3_last_insert_rowid(db);
    mRplPtr = new Replacements(db, mRowid, "InputRule");
}

InputRule::~InputRule() {
    //delete mRplPtr;
}

void InputRule::copy(const InputRule& source) {
    mRowid = source.mRowid;
}

string InputRule::getRegex() const {
    string sRetVal;
    stringstream strSql;
    strSql  << "SELECT regex FROM regexes WHERE rowid = "
            << mRowid;
    exec(strSql.str(), mDb, onReadFirstField, &sRetVal );

    if (!sRetVal.size()) {
        throw runtime_error("query returned no results");
    }

    return sRetVal;
}

void InputRule::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "   regex string UNIQUE)";
    exec(sSql, db);

    sSql = "CREATE TABLE history ("
           "   fileName string UNIQUE,"
           "   regex ROWID)";
    exec(sSql, db);

}

//! change regex
bool InputRule::setRegex(string sRegex) {

    regex newRegex(sRegex);
    vector<string> results;

    stringstream strSql;
    strSql  << "SELECT fileName FROM history "
            << "WHERE regex = " << mRowid;

    exec(strSql.str(), mDb, onAppendFirstColumnToVector, &results);

    vector<string> mismatches;
    for (vector<string>::iterator it = results.begin();
         it != results.end(); it++) {

        //cout << "-> " << *it << endl;
        if (!regex_match(*it, newRegex)) {
            return false;
        }
    }

    strSql.str(""); //clear
    strSql  << "UPDATE regexes SET "
            << "regex = " << cSqlStrOut(sRegex)
            << " WHERE rowid = " << mRowid;
    exec(strSql.str(), mDb);
    return true;
}

//! try to match a fileName against a single regex
/**
    This method updates the history table.
*/
bool InputRule::applyTo(string fileName, vector<GemValue>& matches) {
    fileName = mRplPtr->replace(fileName);
    regex exp(getRegex());
    smatch what;
    if (regex_match(fileName, what, exp)) {
        vector<Gem> myGems = getGems();

        //what[0] is the whole matched thing
        exAssertDesc(what.size() > myGems.size(), "matched not all gems");
        for (int nGemIndex=0;nGemIndex < static_cast<int>(myGems.size()); nGemIndex++ ) {
            GemValue newValue(mDb, mRowid,  myGems[nGemIndex].getRowid());
            newValue.value = what[nGemIndex+1]; // 1based
            matches.push_back(newValue);
        }

        stringstream strSql;
        strSql  << "INSERT OR IGNORE INTO history (fileName, regex) "
                << "VALUES ("
                << cSqlStrOut(fileName) << ", "
                << mRowid << ")";
        exec(strSql.str(), mDb);
        return true;
    }

    return false;
}

void InputRule::addGem(string name) {
    Gem newGem(mDb, mRowid);
    newGem.setName(name);
    return;
}

vector<Gem> InputRule::getGems() const {
    vector<Gem> retVal;
    vector<string> queryResults;
    stringstream strSql;
    strSql  << "SELECT rowid FROM gems WHERE "
            << "ruleId =" << mRowid
            << " ORDER BY position";
    exec(strSql, mDb, onAppendFirstColumnToVector, &queryResults);
    for (vector<string>::iterator it = queryResults.begin();
         it != queryResults.end(); it++) {

        Gem newGem(mDb, mRowid, cSqlInFormated<sqlite_int64>(*it) );
        retVal.push_back(newGem);
    }

    return retVal;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void InputRule::unitTest() {
    BOOST_CHECK(true);

    sqlite3* db;

//    // test Ruleset class
//    path dbFileName = initial_path()/"unitTest_InputRule.db3";
//
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
    InputRule::createTables(db);
    Replacement::createTables(db);
    Replacements::createTables(db);
    Gem::createTables(db);

    BOOST_CHECKPOINT("InputRule constructor(regex)");
    InputRule ruleAlpha(regex("(.*)\\.avi"), db);
    InputRule ruleBeta(regex("(.*)\\.mpg"), db);
    InputRule ruleGamma(regex("(.*)\\.jpg"), db);
    ruleAlpha.addGem("fileName");
    ruleBeta.addGem("fileName");
    ruleGamma.addGem("fileName");

    BOOST_CHECKPOINT("getRegex(), first time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    BOOST_CHECKPOINT("getRegex(), second time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );


    vector<GemValue> gems;
    BOOST_CHECKPOINT("applyTo()");
    BOOST_CHECK(ruleAlpha.getGems().size() == 1);
    BOOST_CHECK_NO_THROW(ruleAlpha.applyTo("Test.avi", gems));
    BOOST_CHECK_NO_THROW(!ruleAlpha.applyTo("Test.mpg", gems));
    BOOST_CHECK_NO_THROW(!ruleAlpha.applyTo("Test.jpg", gems));

    BOOST_CHECKPOINT("applyTo() 048f97dc");
    BOOST_CHECK(!ruleBeta.applyTo("Test.avi", gems));
    BOOST_CHECK(ruleBeta.applyTo("Test.mpg", gems));
    BOOST_CHECK(!ruleBeta.applyTo("Test.jpg", gems));

    BOOST_CHECKPOINT("applyTo() 092aed5a");
    BOOST_CHECK(!ruleGamma.applyTo("Test.avi", gems));
    BOOST_CHECK(!ruleGamma.applyTo("Test.mpg", gems));
    BOOST_CHECK(ruleGamma.applyTo("Test.jpg", gems));

    BOOST_CHECKPOINT("applyTo() 6d984e20");

    BOOST_CHECK(ruleAlpha.applyTo("Name mit Blank.avi", gems));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.mpg", gems));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.jpg", gems));

    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.avi", gems));
    BOOST_CHECK(ruleBeta.applyTo("Name mit Blank.mpg", gems));
    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.jpg", gems));

    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.avi", gems));
    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.mpg", gems));
    BOOST_CHECK(ruleGamma.applyTo("Name mit Blank.jpg", gems));


    BOOST_CHECKPOINT("setRegex()");
    BOOST_CHECK(ruleAlpha.setRegex("([\\w ]*)\\.avi"));
    BOOST_CHECK(!ruleAlpha.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleAlpha.setRegex("Test\\..*"));

    BOOST_CHECK(!ruleBeta.setRegex("([\\w ]*)\\.avi"));
    BOOST_CHECK(ruleBeta.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleBeta.setRegex("Test\\..*"));

    BOOST_CHECK(ruleGamma.setRegex("([\\w ]*)\\.jpg"));
    BOOST_CHECK(!ruleGamma.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleGamma.setRegex("Test\\..*"));

    BOOST_CHECKPOINT("getRegex(), third time");
    BOOST_CHECK( ruleAlpha.getRegex() == "([\\w ]*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "([\\w ]*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "([\\w ]*)\\.jpg" );


    BOOST_CHECKPOINT("InputRule constructor(regex)");
    InputRule ruleDelta( ruleAlpha.getId() , db);
    BOOST_CHECK(ruleAlpha.getId() == ruleDelta.getId());
    BOOST_CHECK(ruleAlpha.getRegex() == ruleDelta.getRegex());


    BOOST_CHECKPOINT("replacements");
    InputRule ruleEpsilon(regex("Family Guy S06E13"), db);
    ruleEpsilon.getReplacements().addReplacement("PDTV|XviD|-LOL","");
    ruleEpsilon.getReplacements().addReplacement(" *$","");
    ruleEpsilon.getReplacements().addReplacement("\\."," ");
    ruleEpsilon.getReplacements().addReplacement("avi$","");

    BOOST_CHECK(ruleEpsilon.applyTo("Family.Guy.S06E13.PDTV.XviD-LOL.avi", gems));
    BOOST_CHECK(!ruleAlpha.applyTo("Family.Guy.S06E13.PDTV.XviD-LOL.avi", gems));
    BOOST_CHECK(ruleAlpha.applyTo("Test.avi", gems));

    BOOST_CHECKPOINT("gems");
    ruleEpsilon.addGem("test");
    ruleEpsilon.addGem("foobar");
    BOOST_CHECK(ruleEpsilon.getGems().size() == 2);
    BOOST_CHECK(ruleEpsilon.getGems()[0].getPosition() == 1);
    BOOST_CHECK(ruleEpsilon.getGems()[1].getPosition() == 2);


    BOOST_CHECKPOINT("ruleZeta");
    InputRule ruleZeta(regex("Numb3rs\\.S(\\d+)E(\\d+)\\.HDTV\\.XviD-(NoTV|LOL)"), db);
    ruleZeta.addGem("season");
    ruleZeta.addGem("episode");

    gems.clear();
    BOOST_CHECK(!ruleZeta.applyTo("Numb3rs.S03E13.Mein Titel.HDTV.XviD-NoTV", gems));
    BOOST_CHECK(ruleZeta.applyTo("Numb3rs.S03E13.HDTV.XviD-NoTV", gems));
    BOOST_CHECK(gems[0].getName() == "season");
    BOOST_CHECK(gems[0].value == "03");
    BOOST_CHECK(gems[1].getName() == "episode");
    BOOST_CHECK(gems[1].value == "13");

    gems.clear();
    BOOST_CHECK(ruleZeta.applyTo("Numb3rs.S03E16.HDTV.XviD-LOL", gems));
    BOOST_CHECK(gems[0].getName() == "season");
    BOOST_CHECK(gems[0].value == "03");
    BOOST_CHECK(gems[1].getName() == "episode");
    BOOST_CHECK(gems[1].value == "16");

    //  clean up
    sqlite3_close(db);
}

#endif
