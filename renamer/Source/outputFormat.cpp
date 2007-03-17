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
        InputRule retVal( newRegex, mDb);
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
    string sSql = "SELECT rowid FROM regexes";
    exec(sSql, mDb, onAppendFirstColumnToVector, &rowids);
    for (vector<string>::iterator it = rowids.begin();
         it != rowids.end(); it++) {

        stringstream strRowid(*it);
        sqlite_int64 rowid;
        strRowid >> rowid;
        InputRule newRule( rowid, mDb);
        retVal.push_back(newRule);
    }
    return retVal;
}

void OutputFormat::removeInputRule(sqlite_int64 rowid) {
    stringstream strSql;
    strSql  << "DELETE FROM regexes "
            << "WHERE rowid = " << rowid;
    exec(strSql, mDb);
    return;
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
                algo::replace_all(outputFileName, strVar.str(), itGem->value);
            }
            return true;
        }

    }
    return false;
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
    formatAlpha.addInputRule("dummy");
    formatAlpha.addInputRule("HalloWelt!");
    formatAlpha.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)");

    BOOST_CHECK_THROW(formatAlpha.addInputRule("dummy"), runtime_error);
    BOOST_CHECK_THROW(formatAlpha.addInputRule("HalloWelt!"), runtime_error);
    BOOST_CHECK_THROW(formatAlpha.addInputRule("^Stargate\\.Atlantis\\.S(\\d+)E(\\d+)([\\.-]\\w{0,7})*\\.(\\w+)"), runtime_error);

    BOOST_CHECKPOINT("checkformatAlpha.getInputRules()");
    BOOST_CHECK( formatAlpha.getInputRules().size() == 3);
    BOOST_CHECK( formatAlpha.getInputRules()[0].getRegex() == "dummy");
    BOOST_CHECK( formatAlpha.getInputRules()[1].getRegex() == "HalloWelt!");


    BOOST_CHECKPOINT("Create formatBeta");
    OutputFormat formatBeta(db);

    formatBeta.setFormat("Dr. House - $season$x$episode$");
    InputRule ruleBeta = formatBeta.addInputRule("House\\.S(\\d+)E(\\d+).*");
    ruleBeta.addGem("season");
    ruleBeta.addGem("episode");

    string sNewFilename;
    BOOST_CHECK(formatBeta.applyTo("House.S03E13.HDTV.XviD-LOL", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x13");

    BOOST_CHECK(formatBeta.applyTo("House.S03E14.HDTV.XviD-XOR", sNewFilename));
    BOOST_CHECK(sNewFilename == "Dr. House - 03x14");

}

#endif

