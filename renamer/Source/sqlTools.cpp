#include "stdafx.h"
#include "sqlTools.h"
#include <boost/algorithm/string/replace.hpp>

namespace algo = boost::algorithm;

void exec(string sSql, sqlite3* db, sqlite3_callback cb, void* param) {
    int nRetVal = 0;
    char *zErrMsg = 0;

    nRetVal = sqlite3_exec(db, sSql.c_str(), cb, param, &zErrMsg);

    if( nRetVal != SQLITE_OK ){
        string sSqliteErr(zErrMsg);
        sqlite3_free(zErrMsg);
        throw std::runtime_error("sql " + sSql + " failed:" + sSqliteErr);
    }
}

int onReadFirstField(void *param, int argc, char **argv, char **azColName) {
    string* sTarget = static_cast<string*>( param);
    *sTarget = argv[0];
    return SQLITE_OK;
}

int onAppendFirstColumnToVector(void *param, int argc, char **argv, char **azColName) {
	vector<string>* output = (vector<string>*) param;
	output->push_back(string(argv[0]));
	return SQLITE_OK;
}

string cSqlStrOut(string sString) {
//    string sRetVal =  sString;
//    sRetVal = "'" + sRetVal + "'";
//    return sRetVal;
    algo::replace_all(sString, "'", "''");
    return "'" + sString + "'";
}

int onAppendAllColumnsToVector(void *param, int argc, char **argv, char **azColName){
    //mind the space   -> <- here
    vector<vector<string> >* targetVector = static_cast<vector<vector<string> >*>( param);
    vector<string> newVector;
    for (int i=0; i < argc; i++)
      newVector.push_back(argv[i]);

    targetVector->push_back(newVector);
    return SQLITE_OK;
}
