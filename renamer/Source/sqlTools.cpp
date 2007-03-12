#include "stdafx.h"
#include "sqlTools.h"

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

