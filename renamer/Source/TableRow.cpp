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
#include "TableRow.h"
#include "sqlTools.h"
#include "error.h"
#include "globals.h"


TableRow::TableRow(sqlite3* db, string table) {
    //we cant do anything useful here because
    //you cant INSERT a empty row. Since we have
    //no field names available here, we cant do
    //anything
    //we will remember that through the magic number
    //NO_TABLE (-1) in mRowid
    mRowid = NO_TABLE;
    mDb = db;
    mTable = table;
    mfDirty = false;
}

TableRow::TableRow(sqlite3* db, string table, string field, string value) {
    mRowid = NO_TABLE;
    mDb = db;
    mTable = table;
    set(field, value);
    mfDirty = false;
}

TableRow::TableRow(sqlite3* db, string table, sqlite_int64 rowid) {

    mRowid = rowid;
    mDb = db;
    mTable = table;
    mfDirty = false;

    stringstream strSql;
    strSql  << "SELECT * "
            << " FROM " << mTable
            << " WHERE rowid =" << mRowid;
    exec(strSql, mDb, onAppendAllColumnsToMap, &mValues);
    if (mValues.size() == 0) {
      stringstream strErrMsg;
      strErrMsg << "no row "
                << rowid << " in table '"
                << table << "'";
      throw runtime_error( strErrMsg.str() );
    }
}

string TableRow::get(string field) const {
//    string sReturn;

//    if (mRowid == NO_TABLE) {
//        return "";
//    }
//
    map<string, string>::const_iterator it = mValues.find(field);
    if (it == mValues.end()) {
      stringstream strErrMsg;
      strErrMsg << "no such column '" << field
                << "' with rowid '" << mRowid << "' in table '"
                << mTable << "'";
      throw runtime_error( strErrMsg.str() );
    } else {
        return it->second;
    }
}

sqlite_int64 TableRow::getRowId() const {
    exAssertDesc(mRowid != NO_TABLE, "nothing written yet");

//    if (mRowid == NO_TABLE) {
//        save();
//    }
    return mRowid;
};

void TableRow::save() {
    exAssertDesc(mValues.size()!=0, "no values");

    if (!mfDirty) {
    	return;
    }
    mfDirty=false;

    stringstream strSql;

    if (mRowid == NO_TABLE) {
        strSql  << "INSERT INTO " << mTable
                << " ("; //<< field
        stringstream strValues;

        for (map<string, string>::iterator it = mValues.begin();
             it!=mValues.end(); it++) {

        	if (it!=mValues.begin()) {
        		strSql << ", ";
        		strValues << ", ";
        	}
        	strSql << it->first;
        	strValues << cSqlStrOut(it->second);
        }

        strSql  << " ) VALUES ( "
                << strValues.str() << ")";

//        cout << strSql.str() << endl;
        exec(strSql, mDb);
        mRowid = sqlite3_last_insert_rowid(mDb);
        exAssert(mRowid != -1);

    } else {
        strSql  << "UPDATE " << mTable << " SET ";
        for (map<string, string>::iterator it = mValues.begin();
             it!=mValues.end(); it++) {

        	if (it!=mValues.begin()) {
        		strSql << ", ";
        	}
        	strSql  << it->first << " = "
                    << cSqlStrOut(it->second);
        }

        strSql << " WHERE rowid = " << mRowid;
        exec(strSql, mDb);
    }

}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE myTable ("
           "   uniqueField string UNIQUE,"
           "   dummy string, "
           "NullColum string)";
    exec(sSql, db);

}

void TableRow::unitTest() {
    using boost::regex;

    sqlite3* db;
//    // test Ruleset class
//    path dbFileName = initial_path<path>()/"unitTest_InputRule.db3";
//
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);

    createTables(db);

    TableRow rowAlpha(db, "myTable");
    rowAlpha.set("uniqueField", "Alpha");
    rowAlpha.set("dummy", "How are you?");
    BOOST_CHECK(rowAlpha.get("uniqueField") == "Alpha");
    BOOST_CHECK(rowAlpha.get("dummy") == "How are you?");

    TableRow rowBeta(db, "myTable");
    rowBeta.set("uniqueField", "Beta");
    rowBeta.set("dummy", "40647a02-d248-11db-8314-0800200c9a66");
    BOOST_CHECK(rowBeta.get("uniqueField") == "Beta");
    BOOST_CHECK(rowBeta.get("dummy") == "40647a02-d248-11db-8314-0800200c9a66");

    TableRow rowGamma(db, "myTable");
    rowGamma.set("uniqueField", "Gamma");
    rowGamma.set("dummy", "D'oh''");
    BOOST_CHECK(rowGamma.get("uniqueField") == "Gamma");
    BOOST_CHECK(rowGamma.get("dummy") == "D'oh''");


    BOOST_CHECKPOINT("operator[]");
    BOOST_CHECK(rowAlpha["uniqueField"] == "Alpha");
    BOOST_CHECK(rowAlpha["dummy"] == "How are you?");
    BOOST_CHECK(rowBeta["dummy"] == "40647a02-d248-11db-8314-0800200c9a66");

    BOOST_CHECKPOINT("null behauviour");
    //BOOST_CHECK(rowAlpha["NullColum"] == "");


}

#endif //RENAMER_UNIT_TEST

