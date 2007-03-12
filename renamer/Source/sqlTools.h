#ifndef SQL_TOOLS
#define SQL_TOOLS

#include "globals.h"

//! sqlite callback that reads the first column to a string
int onReadFirstField(void *param, int argc, char **argv, char **azColName);

void exec(string sSql, sqlite3* db, sqlite3_callback cb=NULL, void* param=NULL);

#endif //SQL_TOOLS
