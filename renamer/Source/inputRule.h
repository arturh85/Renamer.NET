#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"
#include "replacements.h"
#include "gem.h"


//! yummy precious information.
class GemValue : public Gem {
    public:
        //---------------------------------------------------------------------
        //  constructors

        //! creates a new GemValue object.
        GemValue(sqlite3* db, sqlite_int64 ruleId, sqlite_int64 row) :
            Gem(db, ruleId, row) {};

        //---------------------------------------------------------------------
        //  attributes
        string value;
};

//! one rule (regex) to match a filename.
class InputRule {
    public:
        //---------------------------------------------------------------------
        //  constructors


        //! Loads from Database
        InputRule(sqlite3*, sqlite_int64 rowid);

        //! Create a new regex in the database
        InputRule(sqlite3*, boost::regex, sqlite_int64 ownerId);

        //  destructor
        virtual ~InputRule();

        //---------------------------------------------------------------------
        //  methodes

        //! get the regex as a string from the database
        string getRegex() const;
        bool setRegex(string);

        //! Creates 'regexes' and 'history' table
        static void createTables(sqlite3* db);

        //! removes this object and all its children
        void remove();

        Replacements& getReplacements() const { return *mRplPtr; };

        //! get all gems available for this InputRule.
        vector<Gem*> getGems() const;

        //! extract GemValue objects out of a filename
        bool applyTo(string fileName, vector<GemValue>& matches, bool updateHistory = false);

        //! creates a new Gem and attaches it to this InputRule
        Gem& addGem(string name);

        sqlite_int64 getOutputFormatId();


        //! primary key field of the row this object is stored in
        sqlite_int64 getRowId() const
            { return mRow.getRowId(); };

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  constructors

        //! disabled for your convinience
        InputRule(const InputRule&) : mRow(NULL, "regexes") { throw runtime_error("not implemented"); };

        //---------------------------------------------------------------------
        //  attributes
        //sqlite_int64 mRowid;
        TableRow mRow;
        sqlite3* mDb;
        Replacements* mRplPtr;

        //---------------------------------------------------------------------
        //  methods

        //! children
        map<sqlite_int64, Gem*> mChildren;


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
