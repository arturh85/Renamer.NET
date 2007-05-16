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
        InputRule(sqlite3*, boost::regex);

        //  destructor
        virtual ~InputRule();

        //---------------------------------------------------------------------
        //  methodes

        //! get the regex as a string from the database
        string getRegex() const;
        bool setRegex(string);

        //! Creates 'regexes' and 'history' table
        static void createTables(sqlite3* db);

        //! reomves this object and all its children
        void remove();

        sqlite_int64 getId() const { return mRow.getRowId(); };
        Replacements& getReplacements() const { return *mRplPtr; };

        //! get all gems available for this InputRule.
        vector<Gem> getGems() const;

        //! extract GemValue objects out of a filename
        bool applyTo(string fileName, vector<GemValue>& matches);

        //! creates a new Gem and attaches it to this InputRule
        Gem addGem(string name);

        void setOutputFormatId(sqlite_int64 v)
            {mRow.set("outputFormatId", cSqlOutFormated(v)); };

        //! primary key field of the row this object is stored in
        sqlite_int64 getRowId() const
            { return mRow.getRowId(); };

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif



    private:
        //---------------------------------------------------------------------
        //  attributes
        //sqlite_int64 mRowid;
        TableRow mRow;
        sqlite3* mDb;
        Replacements* mRplPtr;

        //---------------------------------------------------------------------
        //  methods

        //! copies member attributes
        /** duplicates pointer targets, so they can be safely deleted
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
