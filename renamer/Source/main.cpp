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
#include "error.h"

namespace po = boost::program_options;
using boost::regex;
using boost::smatch;

int main(int argc, char** argv)
{
    try {
        //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
        boost::filesystem::path::default_name_check(boost::filesystem::native);

        //Zufallsgenerator initialisieren
        srand(time(NULL));


        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("ruleSet,s", po::value<string>())
//            ("outputFormat,f",po::value<string>())
//            ("addOutputFormat,f",po::value<string>(), ")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if (!vm.count("ruleSet")) {
            cout << "the --set parameter is mandetory.\n";
            return 1;
        }

        Ruleset ruleSet( vm["ruleSet"].as<string>() );

        enum {
            MANAGE_OUTPUTFORMATS,
            MANAGE_OUTPUTFORMAT,
            MANAGE_INPUTRULE,
            MANAGE_GEM,
            MANAGE_REPLACEMENTS,
            QUIT
        } state;
        state = MANAGE_OUTPUTFORMATS;

        stringstream strResult;
        OutputFormat* actFormatPtr = NULL;


        while (state != QUIT) {
            //cout << "1) a
            system("cls");
            string sChoice;

            switch (state) {
            case MANAGE_OUTPUTFORMATS: {
                cout    << "current position: "
                        << ruleSet.getName() << "/\n";

                cout << strResult.str();
                strResult.str(""); //clear

                cout << "\nWhat do you want to do?\n"
                        "1) create new outputFormat\n"
                        "2) modify an existing set\n"
                        "0) quit\n"
                        "q) quit\n";

                cin >> sChoice;
                if (sChoice == "1") {
                    try {
                        cout << "Enter outputFormat: ";

                        char szBuffer[256];
                        cin.sync();
                        cin.getline(szBuffer, 256);

                        OutputFormat format = ruleSet.addOutputFormat();
                        format.setFormat(szBuffer);
                        strResult   << "outputFormat '" << szBuffer
                                    << "' added successful!\n";

                    } catch (exception& ex) {
                        strResult << "Error: " << ex.what() << endl;
                    }

                } else if (sChoice == "2") {
                    vector<OutputFormat> formats = ruleSet.getOutputFormats();
                    for (vector<OutputFormat>::iterator it = formats.begin();
                         it != formats.end(); it++) {

                        cout << it->getRowId() << ")\t"
                             << it->getFormat() << endl;
                    }
                    cin >> sChoice;
                    for (vector<OutputFormat>::iterator it = formats.begin();
                         it != formats.end(); it++) {

                        if ( cSqlOutFormated(it->getRowId()) == sChoice) {
                            //position.push_back(it->getRowId());
                            actFormatPtr = new OutputFormat(*it);
                            state = MANAGE_OUTPUTFORMAT;
                            break;
                        }
                    }

                } else if (sChoice == "0") {
                    sChoice = "q";

                } else {
                    strResult << "invalid choice\n";
                }

                break;
            }

            case MANAGE_OUTPUTFORMAT: {
                cout    << "current position: "
                        << ruleSet.getName() << "/"
                        << actFormatPtr->getFormat() << "/\n";

                cout << "\nWhat do you want to do?\n"
                        "1) delete this\n"
                        "0) back\n"
                        "q) quit\n";

                cin >> sChoice;

                if (sChoice == "0") {
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else if (sChoice == "1") {
                    ruleSet.removeOutputFormat(actFormatPtr->getRowId());
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else {
                    strResult << "invalid choice\n";
                }
                break;
            }

            };

            if (regex_match(sChoice, regex("q"))) {
                state = QUIT;
            }

        };

    } catch (exception& ex) {
        cout << "exception caught: " << ex.what() << endl;

    } catch (...) {
        cout << "unknown exception\n";

    }
    std::cout << std::endl;
    return 0;
}
