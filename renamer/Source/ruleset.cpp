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

Ruleset::Ruleset()
{
    mName = "memory";
    if(sqlite3_open(":memory:", &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file");
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

    sSql = "CREATE TABLE history ("
           "   fileName string UNIQUE,"
           "   regex ROWID)";
    exec(sSql, mDb);

    sSql = "CREATE TABLE options ("
           "   outputFormat string)";
    exec(sSql, mDb);

    sSql = "INSERT INTO options (outputFormat)"
           "VALUES ('')";
    exec(sSql, mDb);

    InputRule::createTables(mDb);
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

//! sqlite callback that adds each column as a vector to the param
static int onAppendToVector(void *param, int argc, char **argv, char **azColName){
    //mind the space   -> <- here
    vector<vector<string> >* targetVector = static_cast<vector<vector<string> >*>( param);
    vector<string> newVector;
    for (int i=0; i < argc; i++)
      newVector.push_back(argv[i]);

    targetVector->push_back(newVector);
    return SQLITE_OK;
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

bool Ruleset::applyTo(string fileName, string& outputFileName) {

    vector<vector<string> > regexes;
    string sSql =
        "SELECT regex, rowid FROM regexes";
    exec(sSql.c_str(), mDb, onAppendToVector, &regexes);
    for (vector<vector<string> >::iterator it=regexes.begin();
         it != regexes.end(); it++) {

        vector<string>& columns = *it;

        regex currentRegex(columns[0]);
        smatch what;
        if (regex_match(fileName, what, currentRegex)) {
            //vector<string> vars = stripVarNames()
            string sSql =   "INSERT OR IGNORE INTO history (fileName, regex) "
                            "VALUES (" +
                            cSqlStrOut(fileName) + ", " +
                            columns[1] + ")";
            exec(sSql, mDb);
            return true;
        }
    }
    return false;
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

    InputRule rule;
    rule=myRules.addInputRule("dummy");
    BOOST_CHECK(rule.getRegex() == "dummy");

    myRules.addInputRule("HalloWelt!");
    myRules.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");

    string sDummy;

    //these should work
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT.avi", sDummy ));

    //these lines are intentionally the same
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));

    // these are expected the be false
    BOOST_CHECK(!myRules.applyTo("Notice the ! left", sDummy ));
    BOOST_CHECK(!myRules.applyTo("blah", sDummy ));

}

#endif
