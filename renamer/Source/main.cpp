/** \mainpage Renamer

Renamer ist ein Programm zum Umbenennen von Dateien.

Das besondere an diesem Programm soll sein,
das man Sets an regulären Ausdrücken anlegen
und pflegen kann, um nach einer Einrichtungszeit
neue Dateien mit den vorhandenen Regeln direkt
umbennnen kann.

*/

#include "globals.h"
#include <boost/program_options.hpp>
#include <sqlite3.h>

namespace po = boost::program_options;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char** argv)
{
    sqlite3* db;
    int rc;
    char *zErrMsg = 0;

    if(sqlite3_open("test.db", &db)) {
        cout << "can't open database" << endl;
        sqlite3_close(db);
        exit(1);
    }

    rc = sqlite3_exec(db, "SELECT * FROM test", callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    cout << "ending ... " << endl;
    sqlite3_close(db);
    return 0;


    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("add", po::value<string>(), "add a regular expression to the set")
        ("set", po::value<string>(), "set to use")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("set")) {
        std::cout << "Set was "
     << vm["set"].as<string>() << ".\n";
    } else {
        std::cout << "Set parameter must be given\n";
    }

	std::cout << std::endl;
	return 0;
}
