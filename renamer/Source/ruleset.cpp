#include "stdafx.h"

#include "ruleset.h"
#include "sqlTools.h"
#include "stlUtility.h"
#include "error.h"

namespace fs = boost::filesystem;
using boost::regex;
using boost::smatch;

Ruleset::Ruleset(string name)
{
    static const regex allowedNames("^\\w[\\w ]*\\w$");
    exAssertDesc(regex_match(name, allowedNames), "invalid name");

    mName = name;
    fs::path dbFile = fs::initial_path() / fs::path(name + ".db3");
    //cout << "dbFile = " << dbFile.native_file_string() << endl;

    bool fIsNew = ( !fs::exists(dbFile) );
    if(sqlite3_open(dbFile.native_file_string().c_str(), &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file");
    }

    if (fIsNew)
      initDb();
}

Ruleset::Ruleset(wstring name)
{
	mName = toStdString(name);
	fs::path dbFile = fs::initial_path() / fs::path(toStdString(name) + ".db3");
	//cout << "dbFile = " << dbFile.native_file_string() << endl;

	bool fIsNew = ( !fs::exists(dbFile) );
	string fileName = dbFile.native_file_string().c_str();
	wstring WfileName = toStdWString(fileName);
	if(sqlite3_open16(WfileName.c_str(), &mDb)) {
		sqlite3_close(mDb);
		throw std::runtime_error("could not open database file");
	}

	if (fIsNew)
	initDb();
}

Ruleset::Ruleset()
{
    mName = "memory";
    if(sqlite3_open(":memory:", &mDb)) {
        sqlite3_close(mDb);
        throw std::runtime_error("could not open database file in memory");
    }

    initDb();
}

Ruleset::~Ruleset()
{
    sqlite3_close(mDb);
}

void Ruleset::initDb() {
    string sSql;

    sSql = "CREATE TABLE options ("
           "   outputFormat string)";
    exec(sSql, mDb);

    sSql = "INSERT INTO options (outputFormat)"
           "VALUES ('')";
    exec(sSql, mDb);

    InputRule::createTables(mDb);
    Replacement::createTables(mDb);
    Replacements::createTables(mDb);
    Gem::createTables(mDb);
    OutputFormat::createTables(mDb);
}

string Ruleset::getName() const {
	return mName;
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

vector<OutputFormat> Ruleset::getOutputFormats() {
    vector<OutputFormat> retVal;
    vector<string> rowids;
    string sSql = "SELECT rowid FROM outputFormats";
    exec(sSql, mDb, onAppendFirstColumnToVector, &rowids);
    for (vector<string>::iterator it = rowids.begin();
         it != rowids.end(); it++) {

        sqlite_int64 rowid = cSqlInFormated<sqlite_int64>(*it);
        OutputFormat newFormat(mDb, rowid);
        retVal.push_back(newFormat);
    }
    return retVal;
}

//! Rename a file
/**
    walks through the InputRules and calls their applyTo-Method
*/
bool Ruleset::applyTo(string fileName, string& outputFileName) {
    vector<OutputFormat> rules = getOutputFormats();

    for (vector<OutputFormat>::iterator it = rules.begin();
         it != rules.end(); it++) {

        if (it->applyTo(fileName, outputFileName)) {
            return true;
        }
    }
    return false;
}

OutputFormat Ruleset::addOutputFormat() {
    OutputFormat retVal(mDb);
    return retVal;
}


#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void testName(string name) {
    {
        Ruleset x(name);
    }

    BOOST_CHECK(fs::exists(name + ".db3"));
    fs::remove(name + ".db3");
}

void Ruleset::unitTest() {
    // test global functions
    vector<string> tmpVector;
    tmpVector = stripVarNames("Atlantis $staffel$x$folge$");
    BOOST_REQUIRE(tmpVector.size() == 2);
    BOOST_CHECK(tmpVector[0] == "staffel");
    BOOST_CHECK(tmpVector[1] == "folge");

    tmpVector.clear();
    tmpVector = stripVarNames("$fieserTest $$_$");
    BOOST_REQUIRE(tmpVector.size() == 1);
    BOOST_CHECK(tmpVector[0] == "_");

    // test Ruleset class
    if (fs::exists(fs::initial_path()/"unitTest.db3"))
        fs::remove(fs::initial_path()/"unitTest.db3");

//    Ruleset myRules("unitTest");
    Ruleset myRules;
    OutputFormat simpleFormat = myRules.addOutputFormat();
    simpleFormat.setFormat("$series$ - $season$x$episode$");

    InputRule ruleStargate = simpleFormat.addInputRule("^(Stargate\\.Atlantis|The\\.Simpsons)\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");
    ruleStargate.addGem("season");
    ruleStargate.addGem("episode");

    //  added 2007-03-18-01.15
    Gem gemSeries = ruleStargate.addGem("series");
    gemSeries.replacers.addReplacement("\\.", " ") ; //Stargate Atlantis
    gemSeries.setPosition(1);
    // --

    //these should work
    string sNewFileName;
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x17");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x18");
    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "Stargate Atlantis - 03x19");


    BOOST_CHECKPOINT("ruleSimpsons");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E10.PDTV.XviD-NoTV.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x10");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E12.PDTV.XviD-LOL.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x12");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E13.PDTV.XviD-2HD.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x13");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E14.PDTV.XviD-LOL.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x14");
    BOOST_CHECK(myRules.applyTo("The.Simpsons.S18E16.PDTV.XviD-LOL.avi", sNewFileName ));
    BOOST_CHECK(sNewFileName == "The Simpsons - 18x16");


//    myRules.setOutputFormat("Atlantis $staffel$x$folge$");
//
//
//
//    BOOST_CHECKPOINT("myRules.applyTo");
//    //these should work
//    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E17.HR.HDTV.AC3.2.0.XviD-NBS.avi", sDummy ));
//    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E18.READ.NFO.DSR.XviD-NXSPR0N.avi", sDummy ));
//    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E19.HDTV.XviD-MiNT.avi", sDummy ));
//
//    //these lines are intentionally the same
//    BOOST_CHECKPOINT("myRules.applyTo (doubles check)");
//    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));
//    BOOST_CHECK(myRules.applyTo("Stargate.Atlantis.S03E20.HR.HDTV.AC3.2.0.XviD-NBS2.avi", sDummy ));
//
//    // these are expected the be false
//    BOOST_CHECKPOINT("myRules.applyTo (failures)");
//    BOOST_CHECK(!myRules.applyTo("Notice the ! left", sDummy ));
//    BOOST_CHECK(!myRules.applyTo("blah", sDummy ));
//
//    BOOST_CHECKPOINT("myRules.removeInputRule");
//    myRules.removeInputRule(myRules.getInputRules()[0].getId());
//    BOOST_CHECK( myRules.getInputRules().size() == 2);
//    BOOST_CHECK( myRules.getInputRules()[0].getRegex() == "HalloWelt!");
//
//    myRules.removeInputRule(myRules.getInputRules()[0].getId());
//    BOOST_CHECK( myRules.getInputRules().size() == 1);
//
//    myRules.removeInputRule(myRules.getInputRules()[0].getId());
//    BOOST_CHECK( myRules.getInputRules().size() == 0);
//
//
//    BOOST_CHECKPOINT("check allowed Names");
//    testName("Stargate Atlantis");
//    testName("24");
//    BOOST_CHECK_THROW(testName("Some one "), exFileLineDesc);
//    BOOST_CHECK_THROW(testName("Some other?"), exFileLineDesc);
//    BOOST_CHECK_THROW(testName(" Some other"), exFileLineDesc);
//    BOOST_CHECK_THROW(testName(""), exFileLineDesc);

}

#endif
