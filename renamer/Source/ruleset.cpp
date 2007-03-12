#include "ruleset.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <exception>

namespace fs = boost::filesystem;

Ruleset::Ruleset(string name)
{
    mName = name;
    fs::path dbFile = fs::initial_path()/fs::path(name + ".db3");

    cout << "dbFile = " << dbFile.native_file_string() << endl;


    bool fIsNew = ( !fs::exists(dbFile) );
    if(sqlite3_open("test.db", &mDb)) {
        //throw
        cout << "can't open database" << endl;
        sqlite3_close(mDb);
        exit(1);
    }

//    rc = sqlite3_exec(db, "SELECT * FROM test", callback, 0, &zErrMsg);
//
//    if( rc != SQLITE_OK ){
//        fprintf(stderr, "SQL error: %s\n", zErrMsg);
//        sqlite3_free(zErrMsg);
//    }
//
//    cout << "ending ... " << endl;
//    sqlite3_close(db);
//    return 0;
}

Ruleset::~Ruleset()
{
    sqlite3_close(mDb);
}


