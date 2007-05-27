#include "stdafx.h"

#include "ruleset.h"
#include "sqlTools.h"
#include "stlUtility.h"
#include "error.h"

namespace fs = boost::filesystem;
using boost::regex;
using boost::smatch;

void Ruleset::loadDb(fs::path dbFile) {

	static const regex getNameRegex("^.*\\\\(.*)\\.(.*)$");
	boost::smatch nameMatch;
	if(!regex_match(mFilename,nameMatch,getNameRegex)) {
    throw exBadName();
	}

	mName = nameMatch[1];

    bool fIsNew = ( !fs::exists(dbFile) );
    if(sqlite3_open(dbFile.native_file_string().c_str(), &mDb)) {
        sqlite3_close(mDb);
        throw exDbError();
    }

    if (fIsNew)
      initDb();

	mBeforeReplacementsPtr = new Replacements(mDb, "rulesetBefore", MAGIC_OWNER_ID);
	mAfterReplacementsPtr = new Replacements(mDb, "rulesetAfter", MAGIC_OWNER_ID);

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

Ruleset::Ruleset(wstring filename) {
    mFilename = toStlString(filename);
    loadDb(boost::filesystem::path(toStlString(filename)));
};

Ruleset::Ruleset() {
    mName = "memory";
    if(sqlite3_open(":memory:", &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file in memory");
    }

    initDb();


    mBeforeReplacementsPtr = new Replacements(mDb, "rulesetBefore", MAGIC_OWNER_ID);
    mAfterReplacementsPtr = new Replacements(mDb, "rulesetAfter", MAGIC_OWNER_ID);
}

Ruleset::Ruleset(boost::filesystem::path filename) {
	mFilename = filename.native_file_string();
  loadDb(filename);
};

Ruleset::Ruleset(string filename) {
  mFilename = filename;
  loadDb(boost::filesystem::path(filename));
};

Ruleset::~Ruleset() {
    for (map<sqlite_int64, OutputFormat*>::iterator it = mChildren.begin();
         it!=mChildren.end() ; it++) {

        delete it->second;
    }

    sqlite3_close(mDb);
}

void Ruleset::initDb() {
    string sSql;

    InputRule::createTables(mDb);
    Replacement::createTables(mDb);
    Replacements::createTables(mDb);
    Gem::createTables(mDb);
    OutputFormat::createTables(mDb);
}

string Ruleset::getName() const {
	return mName;
}

string Ruleset::getFilename() const {
	return mFilename;
}

vector<string> stripVarNames(string sString) {
    static const regex varRegex("\\$(\\w+)\\$");
    smatch what;
    vector<string> retVal;

    std::string::const_iterator start, end;
    start = sString.begin();
    end = sString.end();
    boost::match_flag_type flags = boost::match_default;
    while(regex_search(start, end, what, varRegex, flags))  {

        retVal.push_back(what[1]);

        // update search position:
        start = what[0].second;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }

    return retVal;
}

sqlite3* Ruleset::getDatabase() {
	return mDb;
}

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
    mChildren[formatPtr->getRowId()];
    return *formatPtr;
}

bool Ruleset::rename(string fileName) {
//  path test("/");
//  cout << fileName << endl;

    if (!fs::exists(fileName)) {
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
          if (!fs::exists(sSubDir)) {
            fs::create_directory(sSubDir);
          }
        }
    }

    //  cout << ">>" << path+newFilename+sExtension << endl;
    fs::rename(fileName, newFilename);
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

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void testName(string name) {
  BOOST_CHECK_NO_THROW(Ruleset(name));
  if(fs::exists(name))
    fs::remove(name);
}

void Ruleset::unitTest() {

    BOOST_CHECKPOINT("begin");

    // test global functions
    vector<string> tmpVector;
    tmpVector = stripVarNames("Atlantis $staffel$x$folge$");
    BOOST_REQUIRE(tmpVector.size() == 2);
    BOOST_CHECK(tmpVector[0] == "staffel");
    BOOST_CHECK(tmpVector[1] == "folge");

    // test Ruleset class
    using namespace boost::filesystem;
    path dbFileName = initial_path()/"unitTest.db3";

    if (exists(dbFileName))
        boost::filesystem::remove(dbFileName);

//    Ruleset myRules(dbFileName);
    Ruleset myRules;
    OutputFormat& simpleFormat = myRules.addOutputFormat();
    simpleFormat.setFormat("$series$ - $season$x$episode$");

    InputRule& ruleStargate = simpleFormat.addInputRule("^(Stargate\\.Atlantis|The\\.Simpsons)\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*");
    ruleStargate.addGem("season");
    ruleStargate.addGem("episode");

    //  added 2007-03-18-01.15
    Gem gemSeries = ruleStargate.addGem("series");
    gemSeries.replacers.addReplacement("\\.", " ") ; //Stargate Atlantis
    gemSeries.setPosition(1);
    // --

    //these should work
    string sNewFileName;
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x17");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x18");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x19");


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
    BOOST_CHECK_NO_THROW(!myRules.applyTo("D:\\Daten\\Develop\\Renamer\\testFiles\\14Dr.House.S02E14.Sex.wird.unterschaetzt.German.Dubbed.DVDRIP.WS.XviD-TvR.avi", sDummy ));

    BOOST_CHECKPOINT("check allowed Names");
    BOOST_CHECK_THROW(Ruleset(string("Stargate Atlantis")), exBadName);
    BOOST_CHECK_THROW(Ruleset(string("24")), exBadName);
    BOOST_CHECK_THROW(Ruleset(string("z:\\The Simpsons")), exBadName);
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

//
//
//The.Unit.S02E18.HDTV.XviD-NoTV.avi
//The.Unit.S02E20.HDTV.XviD-LOL.avi
//The.Unit.S02E21.HDTV.XviD-XOR.avi

    InputRule& ruleUnit = unitFormat.addInputRule("The\\.Unit\\.S(\\d+)E(\\d+)\\.HDTV\\.XviD-(NoTV|XOR|LOL)");
    ruleUnit.addGem("season");
    ruleUnit.addGem("episode");

    system("echo > The.Unit.S02E16.HDTV.XviD-NoTV.avi");
    BOOST_CHECK(myRules.rename("The.Unit.S02E16.HDTV.XviD-NoTV.avi"));
    BOOST_CHECK(exists("The Unit\\02\\16.avi"));
    remove_all("The Unit\\02\\16.avi");

//    BOOST_REQUIRE(!exists("tmp"));
//
//    system("echo > tmp\\The.Simpsons.S18E12.PDTV.XviD-LOL.avi");
//    BOOST_CHECK(myRules.rename("tmp\\The.Simpsons.S18E12.PDTV.XviD-LOL.avi"));
//    BOOST_CHECK(exists("tmp\\The Simpsons - 18x12.avi"));
//    remove("tmp\\The Simpsons - 18x12.avi");
//
//    remove_all("tmp");
//    BOOST_CHECK(!exists("tmp"));


    BOOST_CHECKPOINT("BeforeReplacements");
    myRules.getBeforeReplacements().addReplacement("\\.JUNK","");

    system("echo > The.Unit.S02E17.HDTV.JUNK.XviD-XOR.avi");
    BOOST_CHECK(myRules.rename("The.Unit.S02E17.HDTV.JUNK.XviD-XOR.avi"));
    BOOST_CHECK(exists("The Unit\\02\\17.avi"));
    remove_all("The Unit\\02\\17.avi");

}

#endif
