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
using namespace boost::filesystem;


using namespace std;

#include <windows.h>

//  Prototypes
enum consoleStates{
    MANAGE_OUTPUTFORMATS,
    MANAGE_OUTPUTFORMAT,
    MANAGE_INPUTRULE,
    MANAGE_GEM,
    MANAGE_REPLACEMENTS,
    QUIT
};

//  Implementations
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
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

class consoleState {
	public:
		virtual ~consoleState() {};

		/**
            If NULL is returend this state will be deleted.
		*/
		virtual consoleState* command(string cmd, string param) = 0;

		/**
            If FALSE is returend this state will be deleted.
		*/
		virtual bool enterState() { return true; };
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

regex buildRegex(vector<string> samples) {
    vector<string> regexParts;
    bool fCommandMode = true;

    for (vector<string>::iterator it = samples.begin();
         it!=samples.end();it++ ) {
           cout << *it << endl;
     }

    for (bool fEverythingMatched = false;!fEverythingMatched ; ) {

        string sInput = getUserInput( fCommandMode?": ":"" ,".*");
        if (fCommandMode) {
            if (sInput == "begin") {
            	fCommandMode = false;
                continue;

            } else if (sInput == "undo") {
                if (regexParts.size() > 0)
                    regexParts.pop_back();

            } else if (regex_match(sInput,regex("help|\\?"))) {
                cout << "<begin> enter regex\n"
                        "<undo> last input\n";
                continue;

            } else {

            }
        } else {
            if (sInput.length()) {
                regexParts.push_back(sInput);
            } else {
                fCommandMode = true;
                continue;
            }

        }



        if (regexParts.size() == 0) {
            //just output the variable names;
            for (vector<string>::iterator it = samples.begin();
                 it!=samples.end();it++ ) {
                   cout << *it << endl;
             }

        } else {

            string sRegex = "^";
            for (vector<string>::iterator it=regexParts.begin();
                 it != regexParts.end();it++ ) {

                sRegex+=*it;
            }

            try {
                cout << colorString(colorString::weiss, sRegex) << endl;
                regex testRegex(sRegex);
//                bool fPopOnFailure = true;

                for (vector<string>::iterator it = samples.begin();
                     it!=samples.end();it++ ) {

    //               string::const_iterator start, end;
    //               start = it->begin();
    //               end = it->end();
                    smatch what;

                    if (regex_search(*it, what, testRegex)) {

                       cout << colorString(colorString::gruen, what[0])
                            << it->substr(what[0].length())
                            << endl;
                    } else {
                       cout << colorString(colorString::rot, *it) << endl;
                       fCommandMode = true;
//                       if (fPopOnFailure) {
//                           fPopOnFailure = false;
//                           fCommandMode = true;
//                           //regexParts.pop_back();
//                       }
                    }

                }

            } catch (exception &ex) {
                fCommandMode = true;
                cout << colorString(colorString::rot, string("Error: ") + ex.what()) << endl;
            }


        }

//        string sInput = getUserInput( "" ,".*");

    }
    return regex();
}

int train(Ruleset& rules, vector<path> files);

int main(int argc, char** argv) {
    try {
        //Zufallsgenerator initialisieren
        srand(time(NULL));

        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("ruleSet,s", po::value<string>())
            ("inputFile,f", po::value<vector<string> >()->multitoken(), "get filenames from here")
//            ("inputFile,f", po::value<vector<string> >(&files)->multitoken(), "get filenames from here")
//            ("outputFormat,f",po::value<string>())
//            ("addOutputFormat,f",po::value<string>(), ")
        ;

        po::variables_map vm;
//        po::store(po::parse_command_line(argc, argv, desc), vm);

        po::positional_options_description posDesc;
        posDesc.add("inputFile", -1);
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(posDesc).run(), vm);

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

        //enumarate files
        vector<string> filesFullpath = vm["inputFile"].as<vector<string> >();
        vector<path> fileNames;
        for (vector<string>::iterator it = filesFullpath.begin();
             it!=filesFullpath.end();it++ ) {

               path file(*it);
               //cout << basename(file.leaf()) << endl;
//               fileNames.push_back(basename(file.leaf()));
                if (!is_directory(*it)) {
                    fileNames.push_back(*it);
                }
         }

        if (vm.count("ruleSet")) {
        	return train(ruleSet, fileNames);
        }

//        regex newRegex = buildRegex(fileNames);
//        cout << "newRegex " << newRegex << endl;
//        return 0;

//        stringstream strResult;
//        OutputFormat* actFormatPtr = NULL;
//        InputRule* actRulePtr = NULL;

//        consoleStates currentState = MANAGE_OUTPUTFORMATS;
//        stack<PropertyObject*> propertyStack;
//
//
//        while (currentState != QUIT) {
//            system("cls");
//            string sChoice;
//
//            cout    << "current position: "
//                    << ruleSet.getName() << "/";
//            if (actFormatPtr) {
//                cout << colorString(colorString::dunkelgruen, actFormatPtr->getFormat()) << "/";
//            }
//
//            if (actRulePtr) {
//                cout << colorString(colorString::gruen, actRulePtr->getRegex()) << "/";
//            }
//            cout << endl << endl;
//
//
//            switch (currentState) {
//                case MANAGE_OUTPUTFORMATS: {
//                    currentState = manageOutputFormats(propertyStack);
//                    break;
//                }
//            }; //switch state
//
//        }


    } catch (exception& ex) {
        cout << "exception caught: " << ex.what() << endl;

    } catch (...) {
        cout << "unknown exception\n";

    }
    std::cout << std::endl;
    return 0;
}

class stateBeginTraining : public consoleState {
	public:
		stateBeginTraining(Ruleset& r, vector<path> f) :
            mRules(r), mFiles(f) {};

		virtual ~stateBeginTraining() {};
		virtual consoleState* command(string cmd, string param);
        virtual bool enterState();

    private:
        Ruleset& mRules;
        vector<path> mFiles;
        vector<path> mUnmatchedFiles;
};

consoleState* stateBeginTraining::command(string cmd, string param) {
    if (cmd == "?") {
    	cout << "Avaible commands:\n"
                "p preview unmatched file after replacements took place\n"
                "+ add replacement\n"
                "? this message\n"
                "q quit imidietly\n";
    	return this;

    } else if (cmd == "p") {
        // show filenames after first replacements
    	for (vector<path>::iterator it = mFiles.begin(); it!=mFiles.end(); it++) {
    	    cout    << mRules.getBeforeReplacements()
    	                     .replace(basename(*it))
                    << endl;
    	}
    	return this;

    } else if (cmd == "+") {

        regex newRegex;
        try {
        	newRegex = param;
        } catch (exception &ex) {
            cout << "this does not seem to be regular expression.\n";
            return this;
        }


        bool fMatchedAtLeastOne = false;
    	for (vector<path>::iterator it = mFiles.begin(); it!=mFiles.end(); it++) {
    	    string sTmp = mRules.getBeforeReplacements()
                                .replace(basename(*it));

            if (regex_search(sTmp, newRegex) ) {
                fMatchedAtLeastOne = true;
            }
    	}

    	if (!fMatchedAtLeastOne) {
    		cout << "expression did not match anything. discarding.\n";
    		return this;
    	}

        string sReplacement;
        cout << "replace with: ";
        cin >> sReplacement;

        mRules.getBeforeReplacements().addReplacement(param, sReplacement);
        cout    << "replace '" << param << "' with "
                << sReplacement << "
                ;
        return this;

    } else {
    	cout << "Unkown command\n";
    	return this;
    }
    return NULL;
}

bool stateBeginTraining::enterState() {
    //remove matched filenames
    vector<path> mUnmatchedFiles;
    for (vector<path>::iterator it = mFiles.begin(); it!=mFiles.end(); it++) {
        string sDummy;
        if (!exists(*it)) {
        	cout << "File '" << it->file_string() << "' does not exist\n";

        }else if (!mRules.applyTo(it->file_string(), sDummy)) {
            mUnmatchedFiles.push_back(*it);
        }
    }

    if (mUnmatchedFiles.size() > 0) {
    	cout    << "there are " << mUnmatchedFiles.size()
                << " unmatched files left\n";
    } else {
    	cout    << "all " << mFiles.size()
                << " files matched. quiting training session.\n";
    }

    return (mUnmatchedFiles.size() > 0);
}

int train(Ruleset& rules, vector<path> files) {

    stack<consoleState*> stateStack;
    stateStack.push( new stateBeginTraining(rules, files));
    consoleState* lastState = NULL;
    while (stateStack.size() > 0) {

    	consoleState* currentState = stateStack.top();
        if  ((lastState!=currentState) && (!currentState->enterState())) {
            stateStack.pop();
            delete currentState;
            break;
        }
        lastState=currentState;

    	string sInput = getUserInput("", ".+");

    	const regex splitCmdWithParam("^ *([^ ]) *(.*)$");
    	const regex splitCmdWithoutParam("^ *([^ ]) *$");
    	smatch what;
        string sCmd;
        string sParam;
        if (regex_match(sInput, what, splitCmdWithParam)) {
            exAssert(what.size() == 3);
            sCmd = what[1];
            sParam = what[2];

        } else if (regex_match(sInput, what, splitCmdWithoutParam)) {
            exAssert(what.size() == 2);
            sCmd = what[1];

        } else {
        	throw runtime_error("could not parse user input");
        }

    	if (what[1] == "q") {
    		while (stateStack.size() > 0) {
    			delete stateStack.top();
    			stateStack.pop();
    		}
    		break;
    	}

    	consoleState* nextState = currentState->command(what[1], what[2]);
    	if (nextState == NULL) {
    		delete currentState;
    		stateStack.pop();

    	} else if (currentState != nextState) {
            stateStack.push(nextState);
    	}
    }

    return 0;
};
