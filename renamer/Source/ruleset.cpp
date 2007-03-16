#include "stdafx.h"

#include "ruleset.h"
#include <boost/filesystem/path.hpp>
#include <exception>
#include <sstream>
#include "sqlTools.h"



namespace fs = boost::filesystem;
using boost::regex;
using boost::smatch;

Ruleset::Ruleset(string name)
{
    mName = name;
    fs::path dbFile = fs::initial_path() / fs::path(name + ".db3");
    //cout << "dbFile = " << dbFile.native_file_string() << endl;

    bool fIsNew = ( !fs::exists(dbFile) );
    if(sqlite3_open(dbFile.native_file_string().c_str(), &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file");
    }

    if (fIsNew)
      initDb();
}

//! Creates an anonymous ruleset in RAM
Ruleset::Ruleset()
{
    mName = "memory";
    if(sqlite3_open(":memory:", &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file in memory");
    }

    initDb();
}

Ruleset::~Ruleset()
{
    sqlite3_close(mDb);
}

//! Creates initial tables
void Ruleset::initDb() {
    string sSql;

    sSql = "CREATE TABLE options ("
           "   outputFormat string)";
    exec(sSql, mDb);

    sSql = "INSERT INTO options (outputFormat)"
           "VALUES ('')";
    exec(sSql, mDb);

    InputRule::createTables(mDb);
    Replacement::createTables(mDb);
}

//! writes the outputFormat to the database
void Ruleset::setOutputFormat(string exp) {
    string sSql =
        "UPDATE options "
        "SET outputFormat = " + cSqlStrOut(exp) ;
    exec(sSql, mDb);
}

//! Reads the outputFormat from the database.
string Ruleset::getOutputFormat() const {
    string sSql =
        "SELECT outputFormat FROM options";
    string sRetVal;
    exec(sSql.c_str(), mDb, onReadFirstField, &sRetVal);

    return sRetVal;
}

string Ruleset::getName() const {
	return mName;
}

//! writes the regex to the database
InputRule Ruleset::addInputRule(string sRegex) {
    try {

        regex newRegex(sRegex); //to check if this is a valid regex
        InputRule retVal( newRegex, mDb);
        return retVal;

    } catch (exception& ex) {
        std::stringstream strErr;
        strErr  << "failed add regex, reason:"
                << ex.what();
        throw runtime_error(strErr.str());
//        throw runtime_error(string("failed add regex, reason:") + ex.what());
    }

}

vector<string> stripVarNames(string sString) {
    static const regex varRegex("\\$(\\w+)\\$");
    smatch what;
    vector<string> retVal;

    std::string::const_iterator start, end;
    start = sString.begin();
    end = sString.end();
    boost::match_flag_type flags = boost::match_default;
    while(regex_search(start, end, what, varRegex, flags))  {

        retVal.push_back(what[1]);

        // update search position:
        start = what[0].second;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }

    return retVal;
}

//! Rename a file
/**
    walks through the InputRules and calls their applyTo-Method
*/
bool Ruleset::applyTo(string fileName, string& outputFileName) {
    vector<InputRule> rules = getInputRules();
    for (vector<InputRule>::iterator it = rules.begin();
         it != rules.end(); it++) {

        if (it->applyTo(fileName, outputFileName)) {
            return true;
        }
    }
    return false;
}

vector<InputRule> Ruleset::getInputRules() {
    vector<InputRule> retVal;
    vector<string> rowids;
    string sSql = "SELECT rowid FROM regexes";
    exec(sSql, mDb, onAppendFirstColumnToVector, &rowids);
    for (vector<string>::iterator it = rowids.begin();
         it != rowids.end(); it++) {

        stringstream strRowid(*it);
        sqlite_int64 rowid;
        strRowid >> rowid;
        InputRule newRule( rowid, mDb);
        retVal.push_back(newRule);
    }
    return retVal;
}

void Ruleset::removeInputRule(sqlite_int64 rowid) {
    stringstream strSql;
    strSql  << "DELETE FROM regexes "
            << "WHERE rowid = " << rowid;
    exec(strSql, mDb);
    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Ruleset::unitTest() {
    // test global functions
    vector<string> tmpVector;
    tmpVector = stripVarNames("Atlantis $staffel$x$folge$");
    BOOST_REQUIRE(tmpVector.size() == 2);
    BOOST_CHECK(tmpVector[0] == "staffel");
    BOOST_CHECK(tmpVector[1] == "folge");

    tmpVector.clear();
    tmpVector = stripVarNames("$fieserTest $$_$");
    BOOST_REQUIRE(tmpVector.size() == 1);
    BOOST_CHECK(tmpVector[0] == "_");

    // test Ruleset class
    if (fs::exists(fs::initial_path()/"unitTest.db3"))
        fs::remove(fs::initial_path()/"unitTest.db3");

//    Ruleset myRules("unitTest");
    Ruleset myRules;
    myRules.setOutputFormat("Atlantis $staffel$x$folge$");

    BOOST_CHECKPOINT("Create myRules");
    myRules.addInputRule("dummy");
    myRules.addInputRule("HalloWelt!");
    myRules.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");

    BOOST_CHECK_THROW(myRules.addInputRule("dummy"), runtime_error);
    BOOST_CHECK_THROW(myRules.addInputRule("HalloWelt!"), runtime_error);
    BOOST_CHECK_THROW(myRules.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)"), runtime_error);

    BOOST_CHECKPOINT("checkmyRules.getInputRules()");
    BOOST_CHECK( myRules.getInputRules().size() == 3);
    BOOST_CHECK( myRules.getInputRules()[0].getRegex() == "dummy");
    BOOST_CHECK( myRules.getInputRules()[1].getRegex() == "HalloWelt!");

    string sDummy;

    BOOST_CHECKPOINT("myRules.applyTo");
    //these should work
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT.avi", sDummy ));

    //these lines are intentionally the same
    BOOST_CHECKPOINT("myRules.applyTo (doubles check)");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));

    // these are expected the be false
    BOOST_CHECKPOINT("myRules.applyTo (failures)");
    BOOST_CHECK(!myRules.applyTo("Notice the ! left", sDummy ));
    BOOST_CHECK(!myRules.applyTo("blah", sDummy ));

    BOOST_CHECKPOINT("myRules.removeInputRule");
    myRules.removeInputRule(myRules.getInputRules()[0].getId());
    BOOST_CHECK( myRules.getInputRules().size() == 2);
    BOOST_CHECK( myRules.getInputRules()[0].getRegex() == "HalloWelt!");

    myRules.removeInputRule(myRules.getInputRules()[0].getId());
    BOOST_CHECK( myRules.getInputRules().size() == 1);

    myRules.removeInputRule(myRules.getInputRules()[0].getId());
    BOOST_CHECK( myRules.getInputRules().size() == 0);
}

#endif
