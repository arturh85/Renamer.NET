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


using namespace std;

#include <windows.h>
//void coutColor(WORD farbe) {
//    cout << flush;
//    //output_color=output_color | farbe;
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), farbe);
//}

class colorString {
	public:
        enum farben {
            schwarz,
            dunkelblau,
            dunkelgruen,
            blaugruen,
            dunkelrot,
            lila,
            ocker,
            hellgrau,
            dunkelgrau,
            blau,
            gruen,
            zyan,
            rot,
            magenta,
            gelb,
            weiss,
        };

		colorString(farben c, string s) : mValue(s), mColor(c) {};
		virtual ~colorString() {};

		friend ostream&  operator<<(ostream& str, const colorString& cs) {
            cout << flush;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cs.mColor);
		    str << cs.mValue;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), hellgrau);
            cout << flush;

            //background: output_color=(background << 4) | output_color;
            //foreground: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), output_color);

		    return str;
		};

        static const farben defaultColor = hellgrau;

	protected:

	private:
        string mValue;
        farben mColor;
};


string getUserInput(string sQuestion, string sRegex) {

    regex allow(sRegex);

    char szBuffer[256];
    //cin.sync();
    cout << sQuestion;
    cin.getline(szBuffer, 256);
    while (!regex_match(szBuffer, allow)) {
        cout << "Invalid choice.\n";
        cout << sQuestion;
        cin.getline(szBuffer, 256);
    }
    cout << endl;
    return szBuffer;
};

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
        InputRule* actRulePtr = NULL;


        while (state != QUIT) {
            //cout << "1) a
            system("cls");
            string sChoice;
            //cout << "\02731m";

            cout    << "current position: "
                    << ruleSet.getName() << "/";
            if (actFormatPtr) {
                cout << colorString(colorString::dunkelgruen, actFormatPtr->getFormat()) << "/";
            }

            if (actRulePtr) {
                cout << colorString(colorString::gruen, actRulePtr->getRegex()) << "/";
            }
            cout << endl << endl;

            switch (state) {
            case MANAGE_OUTPUTFORMATS: {
                cout << strResult.str();
                strResult.str(""); //clear

                cout << "--> " << colorString(colorString::rot, "Testing") << " <--\n";

                cout << "\nWhat do you want to do?\n"
                        "1) create new outputFormat\n"
                        "2) modify an existing outputFormat\n"
                        "0) quit\n"
                        "q) quit\n";

                sChoice = getUserInput("? ", "[120q]");

                if (sChoice == "1") {
                    try {
                        OutputFormat format = ruleSet.addOutputFormat();
                        string sFormat = getUserInput("Enter outputFormat: ", ".*");
                        format.setFormat(sFormat);

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

                    sChoice = getUserInput("? ", "\\d+|q");

                    for (vector<OutputFormat>::iterator it = formats.begin();
                         it != formats.end(); it++) {

                        if ( cSqlOutFormated(it->getRowId()) == sChoice) {
                            //position.push_back(it->getRowId());
                            actFormatPtr = new OutputFormat(*it);
                            state = MANAGE_OUTPUTFORMAT;
                            break;
                        }
                    }

                    strResult << "invalid choice\n";

                } else if (sChoice == "0") {
                    sChoice = "q";

                } else {
                    strResult << "invalid choice\n";
                }

                break;
            }

            case MANAGE_OUTPUTFORMAT: {
                cout << "\nWhat do you want to do?\n"
                        "1) delete this\n"
                        "2) change this\n"
                        "3) add inputRule\n"
                        "4) modify an existing inputRule\n"
                        "0) back\n"
                        "q) quit\n";

                sChoice = getUserInput("? ", "[12340q]");

                if (sChoice == "0") {
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else if (sChoice == "1") {
                    ruleSet.removeOutputFormat(actFormatPtr->getRowId());
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else if (sChoice == "2") {
                    try {
                        sChoice = getUserInput("new format: ", ".*");
                        actFormatPtr->setFormat(sChoice);
                    } catch (exception& ex) {
                        strResult << "Error: " << ex.what() << endl;
                    };

                } else if (sChoice == "3") {

                    for (bool done = false;!done;)
                        try {
                            //regex userRegex(sRegex);
                            actFormatPtr->addInputRule(getUserInput("regex: ", ".*"));
                        	done = true;
                        } catch (exception &ex) {
                            cout << "Error: " << ex.what() << endl;
                        }

                } else if (sChoice == "4") {
                    vector<InputRule> formats = actFormatPtr->getInputRules();
                    for (vector<InputRule>::iterator it = formats.begin();
                         it != formats.end(); it++) {

                        cout << it->getRowId() << ")\t"
                             << it->getRegex() << endl;
                    }

                    //!\todo if no rule is avaible, the user will be stuck
                    sChoice = getUserInput("? ", "\\d+|q");

                    for (vector<InputRule>::iterator it = formats.begin();
                         it != formats.end(); it++) {

                        if ( cSqlOutFormated(it->getRowId()) == sChoice) {
                            //position.push_back(it->getRowId());
                            actRulePtr = new InputRule(*it);
                            state = MANAGE_INPUTRULE;
                            break;
                        }
                    }

                    strResult << "invalid choice\n";

                } else {
                    strResult << "this should not happen\n";
                }
                break;
            }

            case MANAGE_INPUTRULE: {
                cout << "\nWhat do you want to do?\n"
                        "1) delete this\n"
                        "2) change this\n"
                        "3) add inputRule to outputFormat\n"
                        "0) back\n"
                        "q) quit\n";

                sChoice = getUserInput("? ", "[1230q]");

                if (sChoice == "0") {
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else if (sChoice == "1") {
                    ruleSet.removeOutputFormat(actFormatPtr->getRowId());
                    state = MANAGE_OUTPUTFORMATS;
                    delete actFormatPtr;
                    actFormatPtr = NULL;

                } else if (sChoice == "2") {
                    try {
                        sChoice = getUserInput("new format: ", ".*");
                        actFormatPtr->setFormat(sChoice);
                    } catch (exception& ex) {
                        strResult << "Error: " << ex.what() << endl;
                    };

                } else if (sChoice == "3") {

                    for (bool done = false;!done;)
                        try {
                            //regex userRegex(sRegex);
                            actFormatPtr->addInputRule(getUserInput("regex: ", ".*"));
                        	done = true;
                        } catch (exception &ex) {
                            cout << "Error: " << ex.what() << endl;
                        }

                } else {
                    strResult << "this should not happen\n";
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
