#ifndef SQL_TOOLS
#define SQL_TOOLS

#include "globals.h"

//! sqlite callback that reads the first column to a string
int onReadFirstField(void *param, int argc, char **argv, char **azColName);

//! Prepares a string for use in a SqlStatement
/** This function add singles quotes to the front/back und escapes
    quotes in the middle with even more quotes.
*/
string cSqlStrOut(string sString);

void exec(string sSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL);

#endif //SQL_TOOLS
