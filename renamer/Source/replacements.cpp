#include "stdafx.h"
#include "replacements.h"
#include "error.h"
#include "sqlTools.h"
#include <boost/algorithm/string.hpp>

Replacements::Replacements(sqlite3* db, string name, sqlite_int64 ownerId) :
    mDb(db), mName(name), mOwnerId(ownerId)
{
    exAssert(db!=NULL);
    exAssertDesc(ownerId > 0, "ownerId should be greater null");

	sqlite_int64 groupId = 0;

	stringstream strSql;
	strSql  << "SELECT rowid FROM replacementGroups "
		<< "WHERE name = " << cSqlStrOut(mName)
		<< " AND ownerId = " << mOwnerId;
	string sRowId;
	exec(strSql, mDb, onReadFirstField, &sRowId);
	if (sRowId.length() > 0) {
		groupId = cSqlInFormated<sqlite_int64>(sRowId);
	} else {
		strSql.str(""); //clear
		strSql  << "INSERT INTO replacementGroups "
			<< "(name, ownerId) VALUES ("
			<< cSqlStrOut(mName) << ", "
			<< mOwnerId << ")";
		exec(strSql, mDb);

		groupId = sqlite3_last_insert_rowid(mDb);
	}


	vector<string> rowids;		
	strSql.str(""); //clear
	strSql << "SELECT rowid FROM replacements "
		"WHERE groupId = " << cSqlOutFormated(groupId) ;

	exec(strSql, db, onAppendFirstColumnToVector, &rowids);
	for (vector<string>::iterator it = rowids.begin();
		it != rowids.end(); it++) {

			stringstream strRowid(*it);
			sqlite_int64 rowid;
			strRowid >> rowid;
			Replacement* newReplacement = new Replacement(db,  rowid);
			mChildren[newReplacement->getRowId()] = newReplacement;
	}
};

Replacement* Replacements::addReplacement(string sRegex, string replacement) {
    Replacement* newReplacementPtr = new Replacement(mDb);
    newReplacementPtr->setRegex(sRegex);
    newReplacementPtr->setReplacement(replacement);

    //newReplacementPtr->setname(mname);

    stringstream strSql;
    strSql  << "SELECT rowid FROM replacementGroups "
            << "WHERE name = " << cSqlStrOut(mName)
            << " AND ownerId = " << mOwnerId;
    string sRowId;
    exec(strSql, mDb, onReadFirstField, &sRowId);
    if (sRowId.length() > 0) {
        //sqlite_int64 rowId = cSqlInFormated<sqlite_int64>(sRowId);
        newReplacementPtr->setGroupId(cSqlInFormated<sqlite_int64>(sRowId));
    } else {
        strSql.str(""); //clear
        strSql  << "INSERT INTO replacementGroups "
                << "(name, ownerId) VALUES ("
                << cSqlStrOut(mName) << ", "
                << mOwnerId << ")";
        exec(strSql, mDb);

        newReplacementPtr->setGroupId(sqlite3_last_insert_rowid(mDb));
    }

    newReplacementPtr->save();

	mChildren.insert(make_pair(newReplacementPtr->getRowId(), newReplacementPtr));
    return newReplacementPtr;
}

void Replacements::createTables(sqlite3* db) {
    stringstream strSql;

    strSql  << "CREATE TABLE replacementGroups ("
//            << "rowid INTEGER PRIMARY KEY, "
            << "name string, "
            << "ownerId ROWID) ";
    exec(strSql, db);
}

vector<Replacement*> Replacements::getReplacements() const {
	vector<Replacement*> retVal;

	/*
    vector<string> rowidStrings;

    stringstream strSql;
    strSql  << "SELECT rpl.rowid "
               "FROM replacements rpl "
               "JOIN replacementGroups grp "
                    "ON (rpl.groupId = grp.rowid) "
               "WHERE name = " << cSqlStrOut(mName) <<
               " AND ownerId = " << mOwnerId;

//    cout << strSql.str() << endl;
    exec(strSql, mDb, onAppendFirstColumnToVector, &rowidStrings);*/

    for (map<sqlite_int64, Replacement*>::const_iterator it = mChildren.begin();
         it != mChildren.end(); it++) {

//        cout << "rowid " << cSqlInFormated<sqlite_int64>(*it) << endl;
        retVal.push_back(it->second);
    }

    return retVal;
}

string Replacements::replace(string sString) const {
    string sRetVal = sString;
    vector<Replacement*> replacements = getReplacements();

    for (int nAttempt = 0; nAttempt < 5; nAttempt++) {
        //cout << "loop: " << sRetVal << " >" << nAttempt << endl;
        bool fLoop = false;
        for (vector<Replacement*>::iterator it= replacements.begin();
             it != replacements.end(); it++) {

            string sNewString = (*it)->replace(sRetVal);
            if (sRetVal != sNewString) {
                sRetVal = sNewString;
                fLoop = true;
            }
        }

        if (!fLoop) break;
    }

	boost::trim(sRetVal);

    return sRetVal;
}

void Replacements::remove() {
    stringstream strSql;
    strSql  << "DELETE  FROM replacements "
               "WHERE groupId IN ("
                  "SELECT rowid FROM replacementGroups "
                  "WHERE name = " << cSqlStrOut(mName) <<
                  " AND ownerId = " << mOwnerId <<
                ")";

    exec(strSql, mDb);

    strSql.str("");
    strSql  << "DELETE FROM replacementGroups "
                  "WHERE name = " << cSqlStrOut(mName) <<
                  " AND ownerId = " << mOwnerId;
    exec(strSql, mDb);
    return;
}

void Replacements::save() {
	for (map<sqlite_int64, Replacement*>::iterator it = mChildren.begin();
		it!=mChildren.end(); it++) {

			it->second->save();
	}

	return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void Replacements::unitTest() {
    BOOST_CHECKPOINT("begin");

    sqlite3* db;

//    using namespace boost::filesystem;
//    path dbFileName = initial_path<path>()/"unitTest_Replacements.db3";
//    if (exists(dbFileName))
//        boost::filesystem::remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.file_string().c_str(), &db)) {
    if(sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        throw std::runtime_error("could not open database file");
    }
    BOOST_REQUIRE(db!=NULL);
    Replacement::createTables(db);
    createTables(db);

    BOOST_CHECKPOINT("create objects");
    Replacements rpAlpha(db, "Replacements::unitTest", 1);
    Replacements rpBeta(db, "Replacements::unitTest", 100);
    //BOOST_CHECK_THROW(Replacements rpGamma(db, "Replacements::unitTest"), runtime_error);
    rpAlpha.addReplacement("test", "TEST");
    BOOST_REQUIRE(int(rpAlpha.getReplacements().size()) == 1);

    BOOST_CHECKPOINT("getReplacements()");
    rpBeta.addReplacement("\\d", "Zahl");
    rpAlpha.addReplacement("\\d", "Zahl");
    BOOST_REQUIRE(rpAlpha.getReplacements().size() == 2);

    BOOST_REQUIRE_EQUAL(int(rpAlpha.getReplacements().size()) , 2);
    BOOST_CHECK(rpAlpha.getReplacements()[0].getRegex().str() == "test");
    BOOST_CHECK(rpAlpha.getReplacements()[0].getReplacement() == "TEST");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getRegex().str() == "\\d");
    BOOST_CHECK(rpAlpha.getReplacements()[1].getReplacement() == "Zahl");


    BOOST_CHECKPOINT("replace()");
    BOOST_CHECK(rpAlpha.replace("testing") == "TESTing");
    BOOST_CHECK(rpAlpha.replace("te3sting") == "teZahlsting");


    BOOST_CHECKPOINT("Gamma");
    Replacements rpGamma(db, "Replacements::unitTest", 1);
    BOOST_REQUIRE_EQUAL(int(rpGamma.getReplacements().size()) , 2);
    BOOST_CHECK(rpGamma.getReplacements()[0].getRegex().str() == "test");
    BOOST_CHECK(rpGamma.getReplacements()[0].getReplacement() == "TEST");
    BOOST_CHECK(rpGamma.getReplacements()[1].getRegex().str() == "\\d");
    BOOST_CHECK(rpGamma.getReplacements()[1].getReplacement() == "Zahl");
}

#endif
