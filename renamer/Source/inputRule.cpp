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
#include "inputRule.h"
#include "sqlTools.h"
#include "error.h"
#include "outputFormat.h"

using boost::regex;
using boost::smatch;
using namespace boost::filesystem;

InputRule::InputRule(sqlite3* db, sqlite_int64 rowid) :
    mRow(db, "regexes", rowid)
{
    mDb = db;
    mRplPtr = new Replacements(db, "inputRule", rowid );

    //load gems
    vector<string> queryResults;
    stringstream strSql;
    strSql  << "SELECT rowid FROM gems WHERE "
            << "ruleId =" << mRow.getRowId()
            << " ORDER BY position";
    exec(strSql, mDb, onAppendFirstColumnToVector, &queryResults);
    for (vector<string>::iterator it = queryResults.begin();
         it != queryResults.end(); it++) {

        sqlite_int64 childRowId = cSqlInFormated<sqlite_int64>(*it);
        Gem* newGemPtr = new Gem(mDb, mRow.getRowId(), childRowId );
        exAssert(mChildren.count(childRowId) == 0);
        mChildren[childRowId] = newGemPtr;
    }

}

InputRule::InputRule(sqlite3* db, boost::regex exp, sqlite_int64 ownerId)  :
    mRow(db, "regexes")
{
    mDb = db;

    stringstream strRegex;
    strRegex << strRegex;

    mRow.set("regex", cSqlOutFormated(exp));
    mRow.set("outputFormatId", cSqlOutFormated(ownerId));
    mRplPtr = new Replacements(db, "inputRule", mRow.getRowId());
}

InputRule::~InputRule() {
    //delete mRplPtr;

    for (map<sqlite_int64, Gem*>::iterator it = mChildren.begin();
         it!=mChildren.end() ; it++) {

        delete it->second;
    }
}

string InputRule::getRegex() const {
    string sRetVal;
    stringstream strSql;
    strSql  << "SELECT regex FROM regexes WHERE rowid = "
            << mRow.getRowId();
    exec(strSql.str(), mDb, onReadFirstField, &sRetVal );

    if (!sRetVal.size()) {
        throw runtime_error("query returned no results");
    }

    return sRetVal;
}

sqlite_int64 InputRule::getOutputFormatId() {
	string sRetVal;
	stringstream strSql;
	strSql  << "SELECT outputFormatId FROM regexes WHERE rowid = "
		<< mRow.getRowId();
	exec(strSql.str(), mDb, onReadFirstField, &sRetVal );

	if (!sRetVal.size()) {
		throw runtime_error("query returned no results");
	}

	unsigned iRetVal = 0;

	//! \todo: do it better ...

	sscanf(sRetVal.c_str(), "%d", &iRetVal);

	return iRetVal;
}

void InputRule::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE regexes ("
           "    regex string, "
           "    outputFormatId ROWID)";
    exec(sSql, db);

    sSql = "CREATE TABLE history ("
           "   fileName string UNIQUE,"
           "   regex ROWID)";
    exec(sSql, db);

}

//! change regex
bool InputRule::setRegex(string sRegex) {
	regex newRegex;
	newRegex = sRegex;

    vector<string> results;

    stringstream strSql;
    strSql  << "SELECT fileName FROM history "
            << "WHERE regex = " << mRow.getRowId();

    exec(strSql.str(), mDb, onAppendFirstColumnToVector, &results);

    vector<string> mismatches;
    for (vector<string>::iterator it = results.begin();
         it != results.end(); it++) {

        //cout << "-> " << *it << endl;
        if (!regex_match(*it, newRegex)) {
            return false;
        }
    }

    strSql.str(""); //clear
    strSql  << "UPDATE regexes SET "
            << "regex = " << cSqlStrOut(sRegex)
            << " WHERE rowid = " << mRow.getRowId();
    exec(strSql.str(), mDb);
    return true;
}

bool InputRule::applyTo(string fileName, vector<GemValue>& matches, bool updateHistory) {
    fileName = mRplPtr->replace(fileName);
    regex exp(getRegex());
    smatch what;
    if (regex_match(fileName, what, exp)) {
        vector<Gem*> myGems = getGems();

        //what[0] is the whole matched thing
		// removed by arturh
//        exAssertDesc(what.size() > myGems.size(), "matched not all gems");

        for (unsigned int nGemIndex=0;
             nGemIndex < myGems.size() && nGemIndex < what.size();
             nGemIndex++ ) {

            GemValue newValue;
            //GemValue newValue(mDb, mRow.getRowId(),  myGems[nGemIndex]->getRowId());
            //newValue.value = getReplacements().replace(what[nGemIndex+1]); // 1based
            newValue.value = what[nGemIndex+1]; // 1based
            newValue.position = myGems[nGemIndex]->getPosition();
            newValue.name = myGems[nGemIndex]->getName();
            matches.push_back(newValue);
        }

        if (updateHistory) {
          stringstream strSql;
          strSql  << "INSERT OR IGNORE INTO history (fileName, regex) "
                  << "VALUES ("
                  << cSqlStrOut(fileName) << ", "
                  << mRow.getRowId() << ")";
          exec(strSql.str(), mDb);
        }
        return true;
    }

    return false;
}


void InputRule::removeGem(sqlite_int64 gemID) {
	mChildren[gemID]->replacers.remove();

	stringstream strSql;
	strSql << "DELETE FROM gems WHERE rowid = "
		<< cSqlOutFormated(gemID);
	//cout << strSql.str() << endl;
	exec(strSql, mDb);

	delete mChildren[gemID];
	mChildren.erase(gemID);
}


vector<Gem*> InputRule::getGems() const {
    vector<Gem*> retVal;

    for (map<sqlite_int64, Gem*>::const_iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

        retVal.push_back(it->second);
    }
    return retVal;
}

Gem* InputRule::getGemByPosition(int position) const {
	for (map<sqlite_int64, Gem*>::const_iterator it = mChildren.begin();
		it!=mChildren.end(); it++) {

		Gem* gem = it->second;

		if(gem->getPosition() == position )
			return gem;
	}
	return NULL;
}

void InputRule::updateGems(string outputFormat) {
	boost::regex r(getRegex());

	unsigned int brackets = (unsigned) r.mark_count() - 1;

	/** \todo verify:
			gems must be ordered by bracket occureance (first gem must be the one for the first bracket, etc.

	**/

    vector<Gem*> gems = getGems();
	int gemCount = gems.size();
    vector<string> gemNames =  OutputFormat::parse(outputFormat);
	unsigned int gemNameCount = gemNames.size();

    for (unsigned int n=0; n<brackets; n++) {
        Gem* newGemPtr = NULL;
		// we need to create a new gem
    	if (n >= mChildren.size() ) {
            newGemPtr = new Gem(mDb, mRow.getRowId());
            mChildren[newGemPtr->getRowId()] = newGemPtr;

			// the following should not be done, because it would f*@k up this loop
			//            gems.push_back(newGemPtr);

			if(gemNameCount > n)
				newGemPtr->setName(gemNames[n]);
			else
				newGemPtr->setName("");
    	} else {
			// if the gem does already exist, we only set the position value
			// to get values that sum up, so we can rely on them.
    	    newGemPtr = gems[n];
    	}

        newGemPtr->setPosition(n+1); // positions are starting at 1
	}

	// remove gems which have no corresponding brackets
	for(unsigned i=brackets; i<gems.size(); i++) {
		removeGem(gems[i]->getRowId());
	}
}

void InputRule::save() {
    mRow.save();
    for (map<sqlite_int64, Gem*>::iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

    	it->second->save();
    }

    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void InputRule::unitTest() {
    BOOST_CHECK(true);

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

    BOOST_CHECKPOINT("create Tables");
    InputRule::createTables(db);
    Replacement::createTables(db);
    Replacements::createTables(db);
    Gem::createTables(db);

    BOOST_CHECKPOINT("InputRule constructor(regex)");
    InputRule ruleAlpha(db, regex("(.*)\\.avi"), -1);
    InputRule ruleBeta(db, regex("(.*)\\.mpg"), -1);
    InputRule ruleGamma(db, regex("(.*)\\.jpg"), -1);
    ruleAlpha.updateGems("$fileName$");
    ruleBeta.updateGems("$fileName$");
    ruleGamma.updateGems("$fileName$");
    BOOST_CHECK(ruleAlpha.getGems().size() == 1);
    BOOST_CHECK(ruleBeta.getGems().size() == 1);
    BOOST_CHECK(ruleGamma.getGems().size() == 1);

    BOOST_CHECKPOINT("get gem");
    BOOST_REQUIRE(ruleAlpha.getGems().size() == 1);
    BOOST_CHECK(ruleAlpha.getGems()[0]->getName() == "fileName");

    BOOST_CHECKPOINT("getRegex(), first time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );

    BOOST_CHECKPOINT("getRegex(), second time");
    BOOST_CHECK( ruleAlpha.getRegex() == "(.*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "(.*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "(.*)\\.jpg" );


    vector<GemValue> gems;
    BOOST_CHECKPOINT("applyTo()");
    BOOST_CHECK(ruleAlpha.getGems().size() == 1);
    BOOST_CHECK_NO_THROW(ruleAlpha.applyTo("Test.avi", gems, true));
    BOOST_CHECK_NO_THROW(!ruleAlpha.applyTo("Test.mpg", gems, true));
    BOOST_CHECK_NO_THROW(!ruleAlpha.applyTo("Test.jpg", gems, true));

    BOOST_CHECKPOINT("applyTo() 048f97dc");
    BOOST_CHECK(!ruleBeta.applyTo("Test.avi", gems, true));
    BOOST_CHECK(ruleBeta.applyTo("Test.mpg", gems, true));
    BOOST_CHECK(!ruleBeta.applyTo("Test.jpg", gems, true));

    BOOST_CHECKPOINT("applyTo() 092aed5a");
    BOOST_CHECK(!ruleGamma.applyTo("Test.avi", gems, true));
    BOOST_CHECK(!ruleGamma.applyTo("Test.mpg", gems, true));
    BOOST_CHECK(ruleGamma.applyTo("Test.jpg", gems, true));

    BOOST_CHECKPOINT("applyTo() 6d984e20");

    BOOST_CHECK(ruleAlpha.applyTo("Name mit Blank.avi", gems, true));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.mpg", gems, true));
    BOOST_CHECK(!ruleAlpha.applyTo("Name mit Blank.jpg", gems, true));

    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.avi", gems, true));
    BOOST_CHECK(ruleBeta.applyTo("Name mit Blank.mpg", gems, true));
    BOOST_CHECK(!ruleBeta.applyTo("Name mit Blank.jpg", gems, true));

    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.avi", gems, true));
    BOOST_CHECK(!ruleGamma.applyTo("Name mit Blank.mpg", gems, true));
    BOOST_CHECK(ruleGamma.applyTo("Name mit Blank.jpg", gems, true));


    BOOST_CHECKPOINT("setRegex()");
    BOOST_CHECK(ruleAlpha.setRegex("([\\w ]*)\\.avi"));
    BOOST_CHECK(!ruleAlpha.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleAlpha.setRegex("Test\\..*"));

    BOOST_CHECK(!ruleBeta.setRegex("([\\w ]*)\\.avi"));
    BOOST_CHECK(ruleBeta.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleBeta.setRegex("Test\\..*"));

    BOOST_CHECK(ruleGamma.setRegex("([\\w ]*)\\.jpg"));
    BOOST_CHECK(!ruleGamma.setRegex("([\\w ]*)\\.mpg"));
    BOOST_CHECK(!ruleGamma.setRegex("Test\\..*"));

    BOOST_CHECKPOINT("getRegex(), third time");
    BOOST_CHECK( ruleAlpha.getRegex() == "([\\w ]*)\\.avi" );
    BOOST_CHECK( ruleBeta.getRegex() == "([\\w ]*)\\.mpg" );
    BOOST_CHECK( ruleGamma.getRegex() == "([\\w ]*)\\.jpg" );


    BOOST_CHECKPOINT("InputRule constructor(regex)");
    InputRule ruleDelta(db, ruleAlpha.getRowId());
    BOOST_CHECK(ruleAlpha.getRowId() == ruleDelta.getRowId());
    BOOST_CHECK(ruleAlpha.getRegex() == ruleDelta.getRegex());


    BOOST_CHECKPOINT("replacements");
    InputRule ruleEpsilon(db, regex("Family Guy S06E13"), -1);
    ruleEpsilon.getReplacements().addReplacement("PDTV|XviD|-LOL","");
    ruleEpsilon.getReplacements().addReplacement(" *$","");
    ruleEpsilon.getReplacements().addReplacement("\\."," ");
    ruleEpsilon.getReplacements().addReplacement("avi$","");

    BOOST_CHECK(ruleEpsilon.applyTo("Family.Guy.S06E13.PDTV.XviD-LOL.avi", gems, true));
    BOOST_CHECK(!ruleAlpha.applyTo("Family.Guy.S06E13.PDTV.XviD-LOL.avi", gems, true));

    BOOST_CHECKPOINT("gems");
    ruleEpsilon.updateGems("lalala $test$ dsklkdsalk$foobar$kjjlk");
    BOOST_REQUIRE(ruleEpsilon.getGems().size() == 2);
    BOOST_CHECK(ruleEpsilon.getGems()[0]->getPosition() == 1);
    BOOST_CHECK(ruleEpsilon.getGems()[1]->getPosition() == 2);


    BOOST_CHECKPOINT("ruleZeta");
    InputRule ruleZeta(db, regex("Numb3rs\\.S(\\d+)E(\\d+)\\.HDTV\\.XviD-(NoTV|LOL)"), -1);
    ruleZeta.updateGems("Numb3rs - $season$x$episode$");
    BOOST_REQUIRE(ruleZeta.getGems().size() == 2);
    BOOST_CHECK(ruleZeta.getGems()[0]->getPosition() == 1);
    BOOST_CHECK(ruleZeta.getGems()[1]->getPosition() == 2);
    BOOST_CHECK(ruleZeta.getGems()[0]->getName() == "season");
    BOOST_CHECK(ruleZeta.getGems()[1]->getName() == "episode");

    gems.clear();
    BOOST_CHECK(!ruleZeta.applyTo("Numb3rs.S03E13.Mein Titel.HDTV.XviD-NoTV", gems, true));
    BOOST_CHECK(ruleZeta.applyTo("Numb3rs.S03E13.HDTV.XviD-NoTV", gems, true));
    BOOST_REQUIRE(gems.size() == 2);
    BOOST_CHECK(gems[0].name == "season");
    BOOST_CHECK(gems[0].value == "03");
    BOOST_CHECK(gems[1].name == "episode");
    BOOST_CHECK(gems[1].value == "13");

    gems.clear();
    BOOST_CHECK(ruleZeta.applyTo("Numb3rs.S03E16.HDTV.XviD-LOL", gems, true));
    BOOST_CHECK(gems[0].name == "season");
    BOOST_CHECK(gems[0].value == "03");
    BOOST_CHECK(gems[1].name == "episode");
    BOOST_CHECK(gems[1].value == "16");

    BOOST_CHECKPOINT("clean up");
//    ruleAlpha.remove();
//    ruleBeta.remove();
//    ruleGamma.remove();
//    ruleEpsilon.remove();
//    ruleZeta.remove();
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM regexes", db) , "0");
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM gems", db) , "0");

    sqlite3_close(db);
}

#endif
