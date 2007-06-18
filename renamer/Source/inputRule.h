#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"
#include "replacements.h"
#include "gem.h"


//! yummy precious information.
struct GemValue {
    //---------------------------------------------------------------------
    //  constructors
    GemValue() : position(0) {};

    //---------------------------------------------------------------------
    //  attributes
    string name;
    string value;
    int position;
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

        //! sets the regex. IMPORTENT! call updateGems() after calling this method
		// \todo can not be done automatically because we can't find out the output format, or can we?
		bool setRegex(string);

        //! Creates 'regexes' and 'history' table
        static void createTables(sqlite3* db);

		//! removes this gem
		void removeGem(sqlite_int64 gemID);

        //! unused
        Replacements& getReplacements() const { return *mRplPtr; };

        //! extract GemValue objects out of a filename
        /**
            This method updates the history table.
        */
        bool applyTo(string fileName, vector<GemValue>& matches, bool updateHistory = false);

        //! add/remove gems according to the format
        void updateGems(string outputFormat);

        //! get all gems available for this InputRule.
        /**
            The result is ordered by gem position.
        */
        vector<Gem*> getGems() const;

		Gem* getGemByPosition(int position) const;

        sqlite_int64 getOutputFormatId();

        //! primary key field of the row this object is stored in
        sqlite_int64 getRowId() const
            { return mRow.getRowId(); };

        //! B/L
        Gem* getGem(sqlite_int64 rowid)
            { return (mChildren.count(rowid)==0) ? NULL:mChildren[rowid]; };

        //! save this object and all its children
        void save();

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  constructors

        //! disabled for your
        InputRule(const InputRule&) : mRow(NULL, "regexes") { throw runtime_error("not implemented"); };

        //---------------------------------------------------------------------
        //  attributes
        TableRow mRow;
        sqlite3* mDb;
        Replacements* mRplPtr;

        //! children
        map<sqlite_int64, Gem*> mChildren;

        //---------------------------------------------------------------------
        //  methods



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
