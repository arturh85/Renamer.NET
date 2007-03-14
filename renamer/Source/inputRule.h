#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"
#include "replacements.h"

class InputRule {
    public:
        //---------------------------------------------------------------------
        //  constructors
        //InputRule() : mRowid(-1), mDb(NULL) {};

        //! Loads from Database
        InputRule(sqlite_int64 rowid, sqlite3* );

        //! Create a new regex in the database
        InputRule(boost::regex, sqlite3* );

        //  destructor
        virtual ~InputRule();

        //---------------------------------------------------------------------
        //  methodes

        //! get the regex as a string from the database
        string getRegex() const;

        static void createTables(sqlite3* db);
        bool setRegex(string);
        sqlite_int64 getId() const { return (long) mRowid; };
        bool applyTo(string fileName, string& outputFileName);
        Replacements& getReplacements() const { return *mRplPtr; };

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif



    private:
        //---------------------------------------------------------------------
        //  attributes
        sqlite_int64 mRowid;
        sqlite3* mDb;
        Replacements* mRplPtr;

        //---------------------------------------------------------------------
        //  methodes

        //! copies member attributes
        /** dublicates pointer targets, so they can be safely deleted
        */
        void copy(const InputRule& source);

        //! deletes all pointers
        void free();

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
