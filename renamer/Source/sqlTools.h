#ifndef SQL_TOOLS
#define SQL_TOOLS

#include "globals.h"

//! sqlite callback that reads the first column to a string
int onReadFirstField(void *param, int argc, char **argv, char **azColName);

//! sqlite callback that reads the first column to a string vector reference
int onAppendFirstColumnToVector(void *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column as a vector to the param
int onAppendAllColumnsToVector(void *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column as a vector to the param
int onAppendAllColumnsToMap(void *param, int argc, char **argv, char **azColName);

//! Prepares a string for use in a SqlStatement
/** This function add singles quotes to the front/back und escapes
    quotes in the middle with even more quotes.
*/
string cSqlStrOut(string sString);
string cSqlBoolOut(bool);

//! kind of a lazy type conversion
/** If it can be shifted through a stream, you'll get a result.
*/
template<typename T>
T cSqlInFormated(string sString) {
    stringstream strValue(sString);
    T retVal;
    strValue >> retVal;
    return retVal;
}

//! kind of a lazy type conversion
/** If it can be shifted through a stream, you'll get a result.
    2nd param is returnt if this did not work out.
*/
template<typename T>
T cSqlInFormated(string sString, T defaultValue) {
    stringstream strValue(sString);
    T retVal = defaultValue;
    strValue >> retVal;
    return retVal;
}

//! kind of a lazy type conversion
/** If it can be shifted through a stream, you'll get a result.
*/
template<typename T>
string cSqlOutFormated(T value) {
    stringstream strValue;
    strValue << value;
    return strValue.str();
}

//! Executes a Sql query. Throws runtime_error in case of failure
void exec(string sSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL);

//! Executes a Sql query. Throws runtime_error in case of failure
inline void exec(stringstream& strSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL) {
    exec(strSql.str(), db, cb, param);
};

//! Executes a Sql query. And returns the value of the first field or nothing
inline string query(stringstream strSql, sqlite3* db) {
    string sRetVal;
    exec(strSql.str(), db, onReadFirstField, &sRetVal);
    return sRetVal;
};

//! Executes a Sql query. And returns the value of the first field or nothing
inline string query(string sSql, sqlite3* db) {
    string sRetVal;
    exec(sSql, db, onReadFirstField, &sRetVal);
    return sRetVal;
};

#endif //SQL_TOOLS
