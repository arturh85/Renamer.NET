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

//! writes the regex to the database
InputRule OutputFormat::addInputRule(string sRegex) {
    try {
        regex newRegex(sRegex); //to check if this is a valid regex
        InputRule retVal(mDb, newRegex);
        retVal.setOutputFormatId(mRow.getRowId());
        return retVal;
    } catch (exception& ex) {
        std::stringstream strErr;
        strErr  << "failed add regex, reason:"
                << ex.what();
        throw runtime_error(strErr.str());
    }

}

vector<InputRule> OutputFormat::getInputRules() {
    vector<InputRule> retVal;
    vector<string> rowids;
    stringstream strSql;
    strSql << "SELECT rowid FROM regexes "
              "WHERE outputFormatId = " << cSqlOutFormated(mRow.getRowId()) ;

    exec(strSql, mDb, onAppendFirstColumnToVector, &rowids);
    for (vector<string>::iterator it = rowids.begin();
         it != rowids.end(); it++) {

        stringstream strRowid(*it);
        sqlite_int64 rowid;
        strRowid >> rowid;
        InputRule newRule(mDb,  rowid);
        retVal.push_back(newRule);
    }
    return retVal;
}

bool OutputFormat::applyTo(string fileName, string& outputFileName) {
    vector<InputRule> rules = getInputRules();
    for (vector<InputRule>::iterator it = rules.begin();
         it != rules.end(); it++) {

        outputFileName = getFormat();
        vector<GemValue> gems;
        if (it->applyTo(fileName, gems)) {
            for (vector<GemValue>::iterator itGem = gems.begin();
                 itGem != gems.end(); itGem++) {

                stringstream strVar;
                strVar << "$" << itGem->getName() << "$";
                string sValue = itGem->replacers.replace(itGem->value);
                algo::replace_all(outputFileName, strVar.str(), sValue);
            }
            return true;
        }

    }
    return false;
}

bool OutputFormat::parse(vector<string>& gemNames) {
	string format = getFormat();
	int start = -1;

	for(unsigned int i=0; i<format.length(); i++) {
		if(format[i] == '$') {
			if(start == -1) {
				start = i;
			}

			else {
				gemNames.push_back(format.substr(start + 1, i - start - 1));
				start = -1;
			}
		}
	}

	if(start != -1)
		return false;
	return true;
}

void OutputFormat::remove() {
    vector<InputRule> rules = getInputRules();
    for (vector<InputRule>::iterator it = rules.begin();
         it != rules.end(); it++) {

      it->remove();
    }

    stringstream strSql;
    strSql << "DELETE FROM outputFormats WHERE rowid = "
           << cSqlOutFormated(getRowId());
    exec(strSql, mDb);
    return;
}

#ifdef RENAMER_UNIT_TEST
#include <boost/test/test_tools.hpp>

void OutputFormat::unitTest() {
    sqlite3* db;

//    using namespace boost::filesystem;
//    path dbFileName = initial_path()/"unitTest_OutputFormat.db3";
//
//    if (exists(dbFileName))
//        remove(dbFileName);
//
//    if(sqlite3_open(dbFileName.native_file_string().c_str(), &db)) {
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
    BOOST_CHECK( formatAlpha.getInputRules().size() == 3);
    BOOST_CHECK( formatAlpha.getInputRules()[0].getRegex() == "dummy");
    BOOST_CHECK( formatAlpha.getInputRules()[1].getRegex() == "HalloWelt!");


    BOOST_CHECKPOINT("Create formatBeta");
    OutputFormat formatBeta(db);
    BOOST_CHECK(query("SELECT COUNT(*) FROM outputFormats", db) == "2");

    formatBeta.setFormat("Dr. House - $season$x$episode$");
    InputRule ruleBeta = formatBeta.addInputRule("House\\.S(\\d+)E(\\d+).*");
    ruleBeta.addGem("season");
    ruleBeta.addGem("episode");

    string sNewFilename;
    BOOST_CHECK(formatBeta.applyTo("House.S03E13.HDTV.XviD-LOL", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x13");

    BOOST_CHECK(formatBeta.applyTo("House.S03E14.HDTV.XviD-XOR", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x14");


    BOOST_CHECKPOINT("Create formatGamma");
    OutputFormat formatGamma(db);
    BOOST_CHECK(query("SELECT COUNT(*) FROM outputFormats", db) == "3");
    formatGamma.setFormat("$name$");
    InputRule ruleGamma = formatGamma.addInputRule("(.*)");
    BOOST_REQUIRE(formatGamma.getInputRules().size() > 0);
    BOOST_CHECK(formatGamma.getInputRules().size() == 1);
    BOOST_CHECK(formatGamma.getInputRules()[0].getRegex() == "(.*)");

    ruleGamma.addGem("name").replacers.addReplacement("\\."," ");
    BOOST_REQUIRE(formatGamma.getInputRules()[0].getGems().size() == 1);
    BOOST_CHECK(formatGamma.getInputRules()[0].getGems()[0].replacers.getReplacements().size() == 1);
    //BOOST_CHECK(ruleGamma.addGem("name").replacers.getReplacements().size() == 1);
    BOOST_CHECK(formatGamma.applyTo("House.S03E13.HDTV.XviD-LOL", sNewFilename));
    BOOST_CHECK(sNewFilename == "House S03E13 HDTV XviD-LOL");
//    cout << "sNewFilename " << sNewFilename << endl;

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

