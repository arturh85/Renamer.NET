#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"

class InputRule {
    public:
        //  constructors
        InputRule() : mRowid(-1), mDb(NULL) {};
        InputRule(sqlite_int64 rowid, sqlite3* );
        InputRule(boost::regex, sqlite3* );

        //  methodes
        static void createTables(sqlite3* db);
        string getRegex() const;
        bool setRegex(string);
        sqlite_int64 getId() const { return (long) mRowid; };
        bool applyTo(string fileName, string& outputFileName);

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:

        //  attributes
        sqlite_int64 mRowid;
        sqlite3* mDb;

};

struct changeRegexFailure : public exception {
    // Destructor
    virtual ~changeRegexFailure() throw() {};

    // Attributes
    vector<string> fileNames;
    boost::regex oldRegex;
    boost::regex newRegex;
};

#endif //INPUT_RULE
