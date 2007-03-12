#include "ruleset.h"
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <exception>
#include <strstream>

namespace fs = boost::filesystem;
namespace algo = boost::algorithm;

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

Ruleset::~Ruleset()
{
    sqlite3_close(mDb);
}

void exec(string sSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL) {
    int nRetVal = 0;
    char *zErrMsg = 0;

    nRetVal = sqlite3_exec(db, sSql.c_str(), cb, param, &zErrMsg);

    if( nRetVal != SQLITE_OK ){
        string sSqliteErr(zErrMsg);
        sqlite3_free(zErrMsg);
        throw std::runtime_error("sql " + sSql + " failed:" + sSqliteErr);
    }
}


//! Prepares a string for use in a SqlStatement
/** This function add singles quotes to the front/back und escapes
    quotes in the middle with even more quotes.
*/
string cSqlStrOut(string sString) {
//    string sRetVal =  sString;
//    sRetVal = "'" + sRetVal + "'";
//    return sRetVal;
    algo::replace_all(sString, "'", "''");
    return "'" + sString + "'";
}

//! Creates initial tables
void Ruleset::initDb() {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "   regex string UNIQUE)";
    exec(sSql, mDb);

    sSql = "CREATE TABLE options ("
           "   outputFormat string)";
    exec(sSql, mDb);

    sSql = "INSERT INTO options (outputFormat)"
           "VALUES ('')";
    exec(sSql, mDb);
}

//! writes the outputFormat to the database
void Ruleset::setOutputFormat(string exp) {
    string sSql =
        "UPDATE options "
        "SET outputFormat = " + cSqlStrOut(exp) ;
    exec(sSql, mDb);
}

//! sqlite callback that reads the first column to a string
static int onReadFirstField(void *param, int argc, char **argv, char **azColName){
    string* sTarget = static_cast<string*>( param);
    *sTarget = argv[0];
    return SQLITE_OK;
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
void Ruleset::addInputRule(string sRegex) {
    using boost::regex;

    try {

        regex test(sRegex); //to check if this is a valid regex

    } catch (exception& ex) {
//        std::stringstream strErr;
//        strErr  << "failed add regex, reason:"
//                << ex.what();
//        throw runtime_error(strErr.str());
        throw runtime_error(string("failed add regex, reason:") + ex.what());
    }

    string sSql =
        "INSERT INTO regexes (regex) "
        "VALUES (" + cSqlStrOut(sRegex) + ")";
    exec(sSql, mDb);
}

//! sqlite callback that adds the first column to a vector
static int onAppendToVector(void *param, int argc, char **argv, char **azColName){
    vector<string>* targetVector = static_cast<vector<string>*>( param);
    targetVector->push_back(argv[0]);
    return SQLITE_OK;
}


bool Ruleset::applyTo(string fileName, string& outputFileName) {
    using boost::regex;
    using boost::smatch;

    vector<string> regexes;
    string sSql =
        "SELECT regex FROM regexes";
    exec(sSql.c_str(), mDb, onAppendToVector, &regexes);

    for (vector<string>::iterator it=regexes.begin();
         it != regexes.end(); it++) {

        regex currentRegex(*it);
        smatch what;
        if (regex_match(fileName, what, currentRegex)) {

            return true;
        }
    }
    return false;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Ruleset::unitTest() {
//    BOOST_CHECK(1==2);

    if (fs::exists(fs::initial_path()/"unitTest.db3"))
        fs::remove(fs::initial_path()/"unitTest.db3");

    Ruleset myRules("unitTest");
    myRules.addInputRule("dummy");
    myRules.addInputRule("HalloWelt!");
    myRules.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");

    string sDummy;
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT.avi", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));
    BOOST_CHECK(!myRules.applyTo("Notice the ! left", sDummy ));
    BOOST_CHECK(!myRules.applyTo("blah", sDummy ));

}

#endif
