#ifndef SQL_TOOLS
#define SQL_TOOLS

#include "globals.h"

//! sqlite callback that reads the first column to a string
int onReadFirstField(void *param, int argc, char **argv, char **azColName);

//! sqlite callback that reads the first column to a string vector reference
int onAppendFirstColumnToVector(void *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column as a vector to the param
int onAppendAllColumnsToVector(void *param, int argc, char **argv, char **azColName);

//! Prepares a string for use in a SqlStatement
/** This function add singles quotes to the front/back und escapes
    quotes in the middle with even more quotes.
*/
string cSqlStrOut(string sString);

//! Executes a Sql query. Throws runtime_error in case of failure
void exec(string sSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL);

//! Executes a Sql query. Throws runtime_error in case of failure
inline void exec(stringstream& strSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL) {
    exec(strSql.str(), db, cb, param);
};

#endif //SQL_TOOLS
