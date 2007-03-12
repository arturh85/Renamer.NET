#include "ruleset.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <exception>

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
        throw runtime_error("sql " + sSql + " failed:" + sSqliteErr);
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
           "   id int,"
           "   regex string)";
    exec(sSql, mDb);

    sSql = "CREATE TABLE options ("
           "   outputFormat string)";
    exec(sSql, mDb);

    sSql = "INSERT INTO options (outputFormat)"
           "VALUES ('')";
    exec(sSql, mDb);
}

void Ruleset::setOutputFormat(string exp) {
    string sSql =
        "UPDATE options "
        "SET outputFormat = " + cSqlStrOut(exp) ;
    exec(sSql, mDb);
}


static int onReadFirstField(void *param, int argc, char **argv, char **azColName){
    string* sTarget = static_cast<string*>( param);
    *sTarget = argv[0];
    return SQLITE_OK;
}

string Ruleset::getOutputFormat() const {
    int nRetVal = 0;
    char *zErrMsg = 0;
    string sSql =
        "SELECT outputFormat FROM options";

    string sRetVal;
    exec(sSql.c_str(), mDb, onReadFirstField, &sRetVal);

    return sRetVal;
}
