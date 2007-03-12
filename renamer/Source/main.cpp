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
#include "ruleSet.h"
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
    cout    << "count " << argc << endl
            << argv[4] << endl;
    return 0;

    try {
        //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
        boost::filesystem::path::default_name_check(boost::filesystem::native);

        //Zufallsgenerator initialisieren
        srand(time(NULL));


        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("add", po::value<string>(), "add a regular expression to the set")
            ("set", po::value<string>(), "set to use")
            ("outputFormat", po::value<string>(), "cc")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if (!vm.count("set")) {
            cout << "the --set parameter is mandetory.\n";
            return 1;
        }

        Ruleset ruleSet( vm["set"].as<string>() );

        if (vm.count("outputFormat")) {
            ruleSet.setOutputFormat( vm["outputFormat"].as<string>() );
            cout << "set outputformat to " << ruleSet.getOutputFormat() << endl;
            return 0;
        }

        if (vm.count("add")) {
            ruleSet.addInputRule( vm["add"].as<string>() );
            cout << "add " << vm["add"].as<string>() << endl;
            return 0;
        }

    } catch (exception& ex) {
        cout << "exception caught: " << ex.what() << endl;

    } catch (...) {
        cout << "unknown exception\n";

    }
    std::cout << std::endl;
    return 0;
}
