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


#ifndef SQL_TOOLS
#define SQL_TOOLS

#include "globals.h"

//! sqlite callback that reads the first column to a string
int onReadFirstField(void /* string */ *param, int argc, char **argv, char **azColName);

//! sqlite callback that reads the first column to a string vector reference
int onAppendFirstColumnToVector(void /* vector<string> */ *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column as a vector to the param
int onAppendAllColumnsToVector(void /* vector<string> */ *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column as a vector to the param
int onAppendAllColumnsToMap(void /* map<string,string> */ *param, int argc, char **argv, char **azColName);

//! sqlite callback that adds each column to a map<string,string> for each row
int onAppendAllColumnsToMapVector(void /* vector<map<string,string>> */ *param, int argc, char **argv, char **azColName);

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
