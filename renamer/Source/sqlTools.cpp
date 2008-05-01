/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


#include "stdafx.h"
#include "sqlTools.h"
#include <boost/algorithm/string/replace.hpp>
#include "error.h"


namespace algo = boost::algorithm;

void exec(string sSql, sqlite3* db, sqlite3_callback cb, void* param) {
    int nRetVal = 0;
    char *zErrMsg = 0;

//    cout << sSql << endl;
    nRetVal = sqlite3_exec(db, sSql.c_str(), cb, param, &zErrMsg);

    if( nRetVal != SQLITE_OK ){
        string sSqliteErr(zErrMsg);
        sqlite3_free(zErrMsg);
        throw std::runtime_error("sql " + sSql + " failed:" + sSqliteErr);
    }
}

int onReadFirstField(void *param, int argc, char **argv, char**) {
    assert(param != NULL);
    assert(argc > 0);
    assert(argv != NULL);
    //cout << azColName[0] << endl;

    string* sTarget = static_cast<string*>(param);
    if (argv[0])
        *sTarget = argv[0];
    else
        *sTarget = "";

    return SQLITE_OK;
}

int onAppendFirstColumnToVector(void *param, int argc, char **argv, char **) {
	vector<string>* output = (vector<string>*) param;

    if (argc > 0) {
        exAssert(argv[0] != NULL);
        output->push_back(string(argv[0]));
    } else
        output->push_back(string(""));

	return SQLITE_OK;
}

int onAppendAllColumnsToMap(void *param, int argc, char **argv, char **azColName) {
	map<string, string>* output = (map<string, string>*) param;

    for (int n = 0; n < argc ; n++ ) {
        if (argv[n] == NULL) {
            (*output)[azColName[n]] = "";
        } else {
            (*output)[azColName[n]] = argv[n];
        }
    }

	return SQLITE_OK;
}

int onAppendAllColumnsToMapVector(void /* vector<map<string,string>> */ *param, int argc, char **argv, char **azColName) {
	vector<map<string, string> >* outputVector = (vector<map<string, string> >*) param;

	map<string,string> output; 

	for (int n = 0; n < argc ; n++ ) {
		if (argv[n] == NULL) {
			output[azColName[n]] = "";
		} else {
			output[azColName[n]] = argv[n];
		}
	}

	outputVector->push_back(output);
	return SQLITE_OK;
}


string cSqlStrOut(string sString) {
//    string sRetVal =  sString;
//    sRetVal = "'" + sRetVal + "'";
//    return sRetVal;
    algo::replace_all(sString, "'", "''");
    return "'" + sString + "'";
}

int onAppendAllColumnsToVector(void *param, int argc, char **argv, char **){
    //mind the space   -> <- here
    vector<vector<string> >* targetVector = static_cast<vector<vector<string> >*>( param);
    vector<string> newVector;
    for (int i=0; i < argc; i++) {
        if (argv[i])
            newVector.push_back(argv[i]);
        else
            newVector.push_back("");
    }

    targetVector->push_back(newVector);
    return SQLITE_OK;
}

string cSqlBoolOut(bool value) {
    return value?"1":"0";
}
