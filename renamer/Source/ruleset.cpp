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

#include "ruleset.h"
#include "sqlTools.h"
#include "stlUtility.h"
#include "error.h"

using namespace boost::filesystem;
using boost::regex;
using boost::smatch;


Ruleset::Ruleset() {
	mDb = NULL;
	mBeforeReplacementsPtr = NULL;
	mAfterReplacementsPtr = NULL;

	mFilename = "";
	mName = "memory database";

	if(sqlite3_open(":memory:", &mDb)) {
		sqlite3_close(mDb);
		throw std::runtime_error("could not open database file in memory");
	}

	initDb(mDb);

	mBeforeReplacementsPtr = new Replacements(mDb, "rulesetBefore", MAGIC_OWNER_ID);
	mAfterReplacementsPtr = new Replacements(mDb, "rulesetAfter", MAGIC_OWNER_ID);

	loadDb();
}

Ruleset::Ruleset(string filename) {
	mDb = NULL;
	mBeforeReplacementsPtr = NULL;
	mAfterReplacementsPtr = NULL;

	mFilename = filename;
	loadDb(boost::filesystem::path(filename));
};

Ruleset::Ruleset(wstring filename) {
	mDb = NULL;
	mBeforeReplacementsPtr = NULL;
	mAfterReplacementsPtr = NULL;

	mFilename = toStlString(filename);
	loadDb(boost::filesystem::path(toStlString(filename)));
};


Ruleset::Ruleset(boost::filesystem::path filename) {
	mDb = NULL;
	mBeforeReplacementsPtr = NULL;
	mAfterReplacementsPtr = NULL;

	mFilename = filename.file_string();
	loadDb(filename);
};


Ruleset::~Ruleset() {
	// save database back to file
	if(mFilename != "") {
		/*sqlite3* database = NULL;
		if(sqlite3_open(mFilename.c_str(), &database)) {
			sqlite3_close(database);
			throw exDbError();
		}

		copyDb(mDb, database);
		sqlite3_close(database);*/
	}

	sqlite3_close(mDb);

	if(mBeforeReplacementsPtr)
		delete mBeforeReplacementsPtr;
	if(mAfterReplacementsPtr)
		delete mAfterReplacementsPtr;

	for (map<sqlite_int64, OutputFormat*>::iterator it = mChildren.begin();
		it!=mChildren.end() ; it++) {

			delete it->second;
	}
}

void Ruleset::loadDb(path dbFile) {

	static const regex getNameRegex("^.*\\\\(.*)\\.(.*)$");
	boost::smatch nameMatch;
	if(!regex_match(mFilename,nameMatch,getNameRegex)) {
		//! \todo catch this exception
		//        throw exBadName();
	}

	mName = nameMatch[1];

	// open database file
	if(sqlite3_open(dbFile.file_string().c_str(), &mDb)) {
		sqlite3_close(mDb);
		throw exDbError();
	}

	// initialise tables
	try {
		initDb(mDb);
	} catch(...) {} // ignore exception thrown if tables already exist

	// load object model from database to memory representation
	loadDb();
}

void Ruleset::loadDb() {
	if(mBeforeReplacementsPtr)
		delete mBeforeReplacementsPtr;
	if(mAfterReplacementsPtr)
		delete mAfterReplacementsPtr;

	mBeforeReplacementsPtr = new Replacements(mDb, "rulesetBefore", MAGIC_OWNER_ID);
	mAfterReplacementsPtr = new Replacements(mDb, "rulesetAfter", MAGIC_OWNER_ID);

	for(map<sqlite_int64, OutputFormat*>::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
		delete it->second;
	}

	mChildren.clear();
		
	//get outputFormats
	vector<string> rowids;

	stringstream strSql;
	strSql  << "SELECT rowid FROM outputFormats";
	exec(strSql, mDb, onAppendFirstColumnToVector, &rowids);
	for (vector<string>::iterator it = rowids.begin();
		it != rowids.end(); it++) {

			sqlite_int64 rowid = cSqlInFormated<sqlite_int64>(*it);
			OutputFormat* newFormatPtr = new OutputFormat(mDb, rowid);
			mChildren[newFormatPtr->getRowId()] = newFormatPtr;
	}

}

void Ruleset::initDb(sqlite3* database) {
    string sSql;

    InputRule::createTables(database);
    Replacement::createTables(database);
    Replacements::createTables(database);
    Gem::createTables(database);
    OutputFormat::createTables(database);
}

void Ruleset::removeOutputFormat(sqlite_int64 outputFormatId) {
	OutputFormat* outputFormat = mChildren[outputFormatId];
	
	vector<InputRule*> rules = outputFormat->getInputRules();
	for (vector<InputRule*>::iterator it = rules.begin();
		it != rules.end(); it++) {
			outputFormat->removeInputRule((*it)->getRowId());			
	}

	stringstream strSql;
	strSql << "DELETE FROM outputFormats WHERE rowid = "
		<< cSqlOutFormated(outputFormatId);
	exec(strSql, mDb);

	mChildren.erase(outputFormatId);
	delete outputFormat;

	return;
}


//string Ruleset::getName() const {
//	return mName;
//}

string Ruleset::getFilename() const {
	return mFilename;
}

//vector<string> stripVarNames(string sString) {
//    static const regex varRegex("\\$(\\w+)\\$");
//    smatch what;
//    vector<string> retVal;
//
//    std::string::const_iterator start, end;
//    start = sString.begin();
//    end = sString.end();
//    boost::match_flag_type flags = boost::match_default;
//    while(regex_search(start, end, what, varRegex, flags))  {
//
//        retVal.push_back(what[1]);
//
//        // update search position:
//        start = what[0].second;
//        // update flags:
//        flags |= boost::match_prev_avail;
//        flags |= boost::match_not_bob;
//    }
//
//    return retVal;
//}

vector<OutputFormat*> Ruleset::getOutputFormats() {
    vector<OutputFormat*> retVal;
    for (map<sqlite_int64, OutputFormat*>::iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

        retVal.push_back(it->second);
    }
    return retVal;
}

bool Ruleset::applyTo(string fileName, string& outputFileName, bool updateHistory) {
    const regex getFilename("^(.*\\\\)?([^/\\\\:?*\"<>|]+)$");
    smatch what, what2;
    if (!regex_match(fileName, what, getFilename)) {
        throw runtime_error("bad filename2");
    }

    string path = what[1];
    string baseName = what[2];
    string sExtension;

	string baseName2 = what[2];
    //if the filename has an extension extract it, and re-add it later

    const regex getExtension("([^/\\\\:?*\"<>|]+)(\\.\\w+)$");
    if (regex_match(baseName, what2, getExtension)) {
		exAssert(what2.size() == 3);
        baseName2 = what2[1];
        sExtension = what2[2];
    }


    //apply replacements
    baseName2 = mBeforeReplacementsPtr->replace(baseName2);

    vector<OutputFormat*> rules = getOutputFormats();
    for (vector<OutputFormat*>::iterator it = rules.begin();
         it != rules.end(); it++) {

        if ((*it)->applyTo(baseName2, outputFileName, updateHistory)) {
            outputFileName = path + outputFileName + sExtension;
            return true;
        }
    }
    return false;
}

OutputFormat& Ruleset::addOutputFormat() {
    OutputFormat* formatPtr = new OutputFormat (mDb);
    mChildren[formatPtr->getRowId()] = formatPtr;
    return *formatPtr;
}

bool Ruleset::rename(string fileName) {
//  path test("/");
//  cout << fileName << endl;

    if (!exists(fileName)) {
    	throw runtime_error("file does not exist");
    }

    string newFilename;
    if (!applyTo(fileName, newFilename, true)) {
        return false;
    }

    //create directories out of the outputformat
    vector<string> dirParts;
    using namespace boost::algorithm;
    split( dirParts, newFilename, is_any_of("\\") );
    if (dirParts.size() > 1) {
    string sSubDir = "";
    vector<string>::iterator itLast = --dirParts.end();
    for (vector<string>::iterator it = dirParts.begin(); it!=itLast ; it++) {
          sSubDir += *it+"\\";
          if (!exists(sSubDir)) {
            create_directory(sSubDir);
          }
        }
    }

    //  cout << ">>" << path+newFilename+sExtension << endl;
    boost::filesystem::rename(fileName, newFilename);
    return true;
}

InputRule& Ruleset::getInputRule(sqlite_int64 rowid) {
    for (map<sqlite_int64, OutputFormat*>::iterator it=mChildren.begin();
         it!=mChildren.end(); it++) {

    	InputRule* rulePtr = it->second->getInputRule(rowid);
    	if (rulePtr) {
    		return *rulePtr;
    	}
    }
    throw exNoSuchId();
}

Gem& Ruleset::getGem(sqlite_int64 rowid) {
    for (map<sqlite_int64, OutputFormat*>::iterator it=mChildren.begin();
         it!=mChildren.end(); it++) {


    	Gem* gemPtr  = it->second->getGem(rowid);
    	if (gemPtr) {
    		return *gemPtr;
    	}
    }
    throw exNoSuchId();
}

void Ruleset::save() {
    for (map<sqlite_int64, OutputFormat*>::iterator it = mChildren.begin();
         it!=mChildren.end(); it++) {

    	it->second->save();
    }

	if(mBeforeReplacementsPtr)
		mBeforeReplacementsPtr->save();
	if(mAfterReplacementsPtr)
		mAfterReplacementsPtr->save();
}

Replacement& Ruleset::getReplacement(sqlite_int64 rowid) {
    vector<Replacement*> replacements = mBeforeReplacementsPtr->getReplacements();

    for (vector<Replacement*>::iterator it = replacements.begin();
         it != replacements.end(); it++) {

    	if ((*it)->getRowId() == rowid) {
            return *(*it);
    	}
    }
    throw exNoSuchId();
}

void Ruleset::copyDb(sqlite3* source, sqlite3* target) {
	char* tables[] = { "gems", "history", "options", "outputFormats", "regexes", "replacementGroups", "replacements" };
	const int tableCount = 7; // importent! set this MANUALLY each time you update the tables var

	// Step1: Drop all tables of target

	for(int i=0; i<tableCount; i++) {
		stringstream strSql;
		strSql  << "DROP TABLE " << tables[i];
		sqlite3_exec(target, strSql.str().c_str(), NULL, NULL, NULL);
	}

	// Step2: Create tables on target

	initDb(target);

	// Step3: iterate through all tables of this Ruleset and write them to target

	for(int i=0; i<tableCount; i++) {
		stringstream strSql;
		strSql  << "SELECT * FROM " << tables[i];

		vector<map<string,string> > resultset;
		try {
			exec(strSql.str(), source, onAppendAllColumnsToMapVector, &resultset );
		}

		catch(...) {

		}

		for(unsigned int j=0; j<resultset.size(); j++) {
			map<string,string>& columns = resultset[j];
			stringstream strColumns;		
			stringstream strValues;		
			for(map<string,string>::iterator it = columns.begin(); it != columns.end(); it++) {
				strColumns << it->first;
				strValues << "'" << it->second << "'";

				map<string,string>::iterator nextit = it;
				nextit ++;

				if(nextit != columns.end()) {
					strColumns << ",";
					strValues << ",";
				}
			}

			strSql.str("");
			strSql << "INSERT INTO " << tables[i] << " (" << strColumns.str() << ") VALUES (" << strValues.str() << ")";

			sqlite3_exec(target, strSql.str().c_str(), NULL, NULL, NULL);
		}
	}	
}


#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void testName(string name) {
  BOOST_CHECK_NO_THROW(Ruleset(name));
  if(exists(name))
    remove(name);
}

void testNewRuleset(path dbFileName);
void testSavedRuleset(path dbFileName);

void Ruleset::unitTest() {
    //The.Unit.S02E20.HDTV.XviD-LOL.avi
    //The.Unit.S02E21.HDTV.XviD-XOR.avi

    path dbFileName = initial_path<path>()/"unitTest.db3";
    testNewRuleset(dbFileName);
    testSavedRuleset(dbFileName);
    remove_all("The Unit");
}

void testSavedRuleset(path dbFileName) {
    Ruleset myRules(dbFileName);

    system("echo > The.Unit.S02E18.HDTV.XviD-NoTV.avi");
    BOOST_CHECK(myRules.rename("The.Unit.S02E18.HDTV.XviD-NoTV.avi"));
    BOOST_CHECK(exists("The Unit\\02\\18.avi"));  //whole directory will be removed at the end
}

void testNewRuleset(path dbFileName) {

    BOOST_CHECKPOINT("begin");

//    // test global functions
//    vector<string> tmpVector;
//    tmpVector = stripVarNames("Atlantis $staffel$x$folge$");
//    BOOST_REQUIRE(tmpVector.size() == 2);
//    BOOST_CHECK(tmpVector[0] == "staffel");
//    BOOST_CHECK(tmpVector[1] == "folge");


    if (exists(dbFileName))
        boost::filesystem::remove(dbFileName);

    Ruleset myRules(dbFileName);
//    Ruleset myRules;
    OutputFormat& simpleFormat = myRules.addOutputFormat();
    BOOST_REQUIRE(myRules.getOutputFormats().size() == 1);
    BOOST_REQUIRE_EQUAL(myRules.getOutputFormats()[0] , &simpleFormat);
    simpleFormat.setFormat("$series$ - $season$x$episode$");

    simpleFormat.addInputRule("^(Stargate Atlantis|The Simpsons) S(\\d+)E(\\d+)([ -]\\w{0,7})*");
    myRules.getBeforeReplacements().addReplacement("\\.", " ");

    //these should work
    string sNewFileName;
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS", sNewFileName ));
    BOOST_CHECK_EQUAL(sNewFileName, "Stargate Atlantis - 03x17");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N", sNewFileName ));
    BOOST_CHECK_EQUAL(sNewFileName, "Stargate Atlantis - 03x18");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT", sNewFileName ));
    BOOST_CHECK_EQUAL(sNewFileName, "Stargate Atlantis - 03x19");


    BOOST_CHECKPOINT("ruleSimpsons");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E10.PDTV.XviD-NoTV", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x10");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E12.PDTV.XviD-LOL", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x12");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E13.PDTV.XviD-2HD", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x13");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E14.PDTV.XviD-LOL", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x14");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E16.PDTV.XviD-LOL", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x16");


    OutputFormat& formatAtlantis = myRules.addOutputFormat();
    formatAtlantis.setFormat("Atlantis $staffel$x$folge$");

    BOOST_CHECKPOINT("myRules.applyTo");
    string sDummy;
    //these should work
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT", sDummy ));

    //these lines are intentionally the same
    BOOST_CHECKPOINT("myRules.applyTo (doubles check)");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2", sDummy ));
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2", sDummy ));

    // these are expected the be false
    BOOST_CHECKPOINT("myRules.applyTo (failures)");
    BOOST_CHECK(!myRules.applyTo("Notice the ! left", sDummy ));
    BOOST_CHECK(!myRules.applyTo("blah", sDummy ));
    BOOST_CHECK(!myRules.applyTo("D:\\Daten\\Develop\\Renamer\\testFiles\\14Dr.House.S02E14.Sex.wird.unterschaetzt.German.Dubbed.DVDRIP.WS.XviD-TvR.avi", sDummy ));

    BOOST_CHECKPOINT("check allowed Names");
//    BOOST_CHECK_THROW(Ruleset(string("Stargate Atlantis")), exBadName);
//    BOOST_CHECK_THROW(Ruleset(string("24")), exBadName);
//    BOOST_CHECK_THROW(Ruleset(string("z:\\The Simpsons")), exBadName);
    BOOST_CHECK_THROW(Ruleset(string("x:\\strangeDir\\The Simpsons.db3")),exDbError);
    BOOST_CHECK_THROW(Ruleset(string("c:\\myDir\\xyz\\24.RULESET")),exDbError);
    BOOST_CHECK_THROW(Ruleset(string("x:\\The Simpsons.ruleset")),exDbError);

    testName(".\\Stargate Atlantis.ruleSet");
    testName(".\\Stargate Atlantis.db3");
    testName("c:\\24.db3");


    BOOST_CHECKPOINT("rename");
    system("echo > The.Simpsons.S18E10.PDTV.XviD-NoTV.avi");
    BOOST_CHECK(myRules.rename("The.Simpsons.S18E10.PDTV.XviD-NoTV.avi"));
    BOOST_CHECK(exists("The Simpsons - 18x10.avi"));
    remove("The Simpsons - 18x10.avi");

    system("echo > The.Simpsons.S18E12.PDTV.XviD-LOL.avi");
    BOOST_CHECK(myRules.rename("The.Simpsons.S18E12.PDTV.XviD-LOL.avi"));
    BOOST_CHECK(exists("The Simpsons - 18x12.avi"));
    remove("The Simpsons - 18x12.avi");


    string tmpDir(getenv("TMP"));
    system(string("echo > ") + tmpDir + "\\The.Simpsons.S18E12.PDTV.XviD-LOL.avi");
    BOOST_CHECK(myRules.rename(tmpDir + "\\The.Simpsons.S18E12.PDTV.XviD-LOL.avi"));
    BOOST_CHECK(exists(tmpDir + "\\The Simpsons - 18x12.avi"));
    remove(tmpDir + "\\The Simpsons - 18x12.avi");


    BOOST_CHECKPOINT("subDirs");
    OutputFormat& unitFormat = myRules.addOutputFormat();
    unitFormat.setFormat("The Unit\\$season$\\$episode$");

    InputRule& ruleUnit = unitFormat.addInputRule("The Unit S(\\d+)E(\\d+) HDTV XviD-(NoTV|XOR|LOL)");
//    InputRule& ruleUnit = unitFormat.addInputRule("The\\.Unit\\.S(\\d+)E(\\d+)\\.HDTV\\.XviD-(NoTV|XOR|LOL)");
    ruleUnit.updateGems("$season$x$episode$");

    system("echo > The.Unit.S02E16.HDTV.XviD-NoTV.avi");
    BOOST_CHECK(myRules.rename("The.Unit.S02E16.HDTV.XviD-NoTV.avi"));
    BOOST_CHECK(exists("The Unit\\02\\16.avi")); //whole directory will be removed at the end

    BOOST_CHECKPOINT("BeforeReplacements");
    myRules.getBeforeReplacements().addReplacement(" JUNK","");

    system("echo > The.Unit.S02E17.HDTV.JUNK.XviD-XOR.avi");
    BOOST_CHECK(myRules.rename("The.Unit.S02E17.HDTV.JUNK.XviD-XOR.avi"));
    BOOST_CHECK(exists("The Unit\\02\\17.avi")); //whole directory will be removed at the end

    myRules.save();
}

#endif
