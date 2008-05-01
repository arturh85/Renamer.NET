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
#include "outputFormat.h"
#include "inputRule.h"
#include <boost/algorithm/string/replace.hpp>

using boost::regex;
using boost::smatch;
namespace algo = boost::algorithm;

void OutputFormat::createTables(sqlite3* db) {
    string sSql;

    sSql = "CREATE TABLE outputFormats ("
           "   format string)";
    exec(sSql, db);
}

OutputFormat::OutputFormat(sqlite3* db, sqlite_int64 row) :
    mRow(db, "outputFormats", row) {

    vector<string> rowids;
    stringstream strSql;
    strSql << "SELECT rowid FROM regexes "
              "WHERE outputFormatId = " << cSqlOutFormated(mRow.getRowId()) ;

    exec(strSql, mRow.getDb(), onAppendFirstColumnToVector, &rowids);
    for (vector<string>::iterator it = rowids.begin();
         it != rowids.end(); it++) {

        stringstream strRowid(*it);
        sqlite_int64 rowid;
        strRowid >> rowid;
        InputRule* newRulePtr = new InputRule(mRow.getDb(),  rowid);
        mChildren[newRulePtr->getRowId()] = newRulePtr;
    }

}

OutputFormat::~OutputFormat() {
    for (map<sqlite_int64, InputRule*>::iterator it = mChildren.begin();
         it!=mChildren.end() ; it++) {

        delete it->second;
    }
}

//! writes the regex to the database
InputRule& OutputFormat::addInputRule(string sRegex) {
    try {
        regex newRegex(sRegex); //to check if this is a valid regex
        InputRule* newRulePtr = new InputRule(mRow.getDb(), newRegex, mRow.getRowId());
        mChildren[newRulePtr->getRowId()] = newRulePtr;
        newRulePtr->updateGems(getFormat());
        return *newRulePtr;

    } catch (exception& ex) {
        std::stringstream strErr;
        strErr  << "failed add regex, reason:"
                << ex.what();
        throw runtime_error(strErr.str());
    }

}

vector<InputRule*> OutputFormat::getInputRules() {
    vector<InputRule*> retVal;

    for (map<sqlite_int64, InputRule*>::iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

        retVal.push_back(it->second);
    }
    return retVal;
}

bool OutputFormat::applyTo(string fileName, string& outputFileName, bool updateHistory) {
    vector<InputRule*> rules = getInputRules();
    for (vector<InputRule*>::iterator it = rules.begin();
         it != rules.end(); it++) {

        outputFileName = getFormat();
        vector<GemValue> gems;
        if ((*it)->applyTo(fileName, gems, updateHistory)) {
            for (vector<GemValue>::iterator itGem = gems.begin();
                 itGem != gems.end(); itGem++) {

                stringstream strVar;
                strVar << "$" << itGem->name << "$";
//                string sValue = itGem->replacers.replace(itGem->value);
//                algo::replace_all(outputFileName, strVar.str(), sValue);
                algo::replace_all(outputFileName, strVar.str(), itGem->value);
            }
            return true;
        }

    }
    return false;
}

vector<string> OutputFormat::parse(string format) {
//	string format = getFormat();
    vector<string> retVal;
	int start = -1;

	for(unsigned int i=0; i<format.length(); i++) {
		if(format[i] == '$') {
			if(start == -1) {
				start = i;
			}

			else {
				string gem = format.substr(start + 1, i - start - 1);

				// check that this gem does not appear twice in the retVal vector
				bool found = false;
				for(unsigned j=0; j<retVal.size(); j++)
					if(retVal[j] == gem)
						found = true;

				if(!found)
					retVal.push_back(gem);
				start = -1;
			}
		}
	}

    return retVal;
//	if(start != -1)
//		return false;
//	return true;
}

void OutputFormat::removeInputRule(sqlite_int64 inputRuleId) {
	InputRule* inputRule = mChildren[inputRuleId];

	vector<Gem*> gems = inputRule->getGems();
	for (vector<Gem*>::iterator it = gems.begin();
		it != gems.end(); it++) {
			inputRule->removeGem((*it)->getRowId());
	}

	stringstream strSql;
	strSql << "DELETE FROM regexes WHERE rowid = "
		<< cSqlOutFormated(inputRuleId);
	//    cout << strSql.str() << endl;
	exec(strSql, mRow.getDb()); 

	mChildren.erase(inputRuleId);
	delete inputRule;
	return;
}

Gem* OutputFormat::getGem(sqlite_int64 rowid) {
    for (map<sqlite_int64, InputRule*>::iterator it=mChildren.begin();
         it!=mChildren.end(); it++) {

    	Gem* gemPtr = it->second->getGem(rowid);
    	if (gemPtr ) {
    		return gemPtr ;
    	}
    }
    return NULL;
}

void OutputFormat::setFormat(string format) {
    mRow.set("format",format);
    vector<InputRule*> rules = getInputRules();
    for (vector<InputRule*>::iterator it = rules.begin(); it!=rules.end() ; it++) {
    	(*it)->updateGems(format);
    }
}

void OutputFormat::save() {
    mRow.save();
    for (map<sqlite_int64, InputRule*>::iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

    	it->second->save();
    }

    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void OutputFormat::unitTest() {
    sqlite3* db;

//    using namespace boost::filesystem;
//    path dbFileName = initial_path<path>()/"unitTest_OutputFormat.db3";
//
//    if (exists(dbFileName))
//        remove(dbFileName);
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
    OutputFormat::createTables(db);


    BOOST_CHECKPOINT("Create formatAlpha");
    OutputFormat formatAlpha(db);
    BOOST_CHECK(query("SELECT COUNT(*) FROM outputFormats", db) == "1");
    BOOST_CHECK_THROW(OutputFormat formatAlpha(db, -1), runtime_error);
    formatAlpha.addInputRule("dummy");
    formatAlpha.addInputRule("HalloWelt!");
    formatAlpha.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");

//    BOOST_CHECK_THROW(formatAlpha.addInputRule("dummy"), runtime_error);
//    BOOST_CHECK_THROW(formatAlpha.addInputRule("HalloWelt!"), runtime_error);
//    BOOST_CHECK_THROW(formatAlpha.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)"), runtime_error);

    BOOST_CHECKPOINT("checkformatAlpha.getInputRules()");
    BOOST_REQUIRE( formatAlpha.getInputRules().size() == 3);
    BOOST_CHECK( formatAlpha.getInputRules()[0]->getRegex() == "dummy");
    BOOST_CHECK( formatAlpha.getInputRules()[1]->getRegex() == "HalloWelt!");


    BOOST_CHECKPOINT("Create formatBeta");
    OutputFormat formatBeta(db);
    BOOST_CHECK(query("SELECT COUNT(*) FROM outputFormats", db) == "2");

    formatBeta.setFormat("Dr. House - $season$x$episode$");
//    InputRule& ruleBeta = formatBeta.addInputRule("House\\.S(\\d+)E(\\d+).*");
//    ruleBeta.updateGems("$season$x$episode$");
    formatBeta.addInputRule("House\\.S(\\d+)E(\\d+).*");
    BOOST_REQUIRE(formatBeta.getInputRules().size() >= 1);
    BOOST_CHECK(formatBeta.getInputRules()[0]->getGems().size() == 2);

    string sNewFilename;
    BOOST_CHECK(formatBeta.applyTo("House.S03E13.HDTV.XviD-LOL", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x13");

    BOOST_CHECK(formatBeta.applyTo("House.S03E14.HDTV.XviD-XOR", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x14");


    BOOST_CHECKPOINT("Create formatGamma");
    OutputFormat formatGamma(db);
    BOOST_CHECK(query("SELECT COUNT(*) FROM outputFormats", db) == "3");
    formatGamma.setFormat("$name$");
//    InputRule& ruleGamma = formatGamma.addInputRule("(.*)");
    formatGamma.addInputRule("(.*)");
    BOOST_REQUIRE(formatGamma.getInputRules().size() > 0);
    BOOST_CHECK(formatGamma.getInputRules().size() == 1);
    BOOST_CHECK(formatGamma.getInputRules()[0]->getRegex() == "(.*)");

//    ruleGamma.addGem("name").replacers.addReplacement("\\."," ");
//    ruleGamma.updateGems("$name$");
//    BOOST_REQUIRE(formatGamma.getInputRules()[0]->getGems().size() == 1);
//    BOOST_CHECK(formatGamma.getInputRules()[0]->getGems()[0]->replacers.getReplacements().size() == 1);
//    //BOOST_CHECK(ruleGamma.addGem("name").replacers.getReplacements().size() == 1);
//    BOOST_CHECK(formatGamma.applyTo("House.S03E13.HDTV.XviD-LOL", sNewFilename));
//    BOOST_CHECK(sNewFilename == "House S03E13 HDTV XviD-LOL");
////    cout << "sNewFilename " << sNewFilename << endl;

    BOOST_CHECKPOINT("Create formatZeta");
    BOOST_CHECK_THROW(OutputFormat formatZeta(db, -1), runtime_error);
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM outputFormats", db) , "3");

    BOOST_CHECKPOINT("delete formatZeta");
    formatAlpha.remove();
    formatBeta.remove();
    formatGamma.remove();
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM outputFormats", db) , "0");
    BOOST_CHECK_EQUAL(query("SELECT COUNT(*) FROM regexes", db) , "0");

}

#endif

