#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>
#include "outputFormat.h"
#include "error.h"

//! Verwaltet Reguläre Ausdrücke
/**
Mehrere Input Reguläre Ausdrücke (z.B. Formate für
die selbe Serie) werden zusammengefaßt in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden können.
*/


const int MAGIC_OWNER_ID = 4711;

//! the root of all objects (so far :)
class Ruleset
{
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! load a db (std::string)
        Ruleset(string filename);

        //! load a db (std::wstring)
        Ruleset(wstring filename);

        virtual ~Ruleset();

        //---------------------------------------------------------------------
        //  methodes

        //! Wird für jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zurück
            This uses the before/after replacements.
        */
        bool applyTo(string fileName, string& outputFileName, bool updateHistory = false);

        //! Rename a 'physical' file
        /**
          This updates the history table.
          If false is returned no InputRule is matched.
          If any other error (like bad/duplicate filename) occurs
          an exception is thrown.
        */
        bool rename(string fileName);

        //! this creates a new OutputFormat object
        OutputFormat& addOutputFormat();

        //! gets a collection of OutputFormat objects
        vector<OutputFormat*> getOutputFormats();

		string getFilename() const;
		string getName() const;

        /// these are applied before anything else is done with the filename
        Replacements& getBeforeReplacements() const { return *mBeforeReplacementsPtr; };

        /// these are applied at the very end of everything
        Replacements& getAfterReplacements() const { return *mAfterReplacementsPtr; };

        //! gui convenience
        OutputFormat& getOutputFormat(sqlite_int64 rowid)
            { if (mChildren.count(rowid)==0) throw exNoSuchId();
              return *(mChildren[rowid]); };

        //! gui convenience
        InputRule& getInputRule(sqlite_int64 rowid);

        //! gui convenience
        Gem& getGem(sqlite_int64 rowid);

        //! gui convenience
        Replacement& getReplacement(sqlite_int64 rowid);

        //! save this object and all its children
        void save();

		//! Creates an anonymous ruleset in RAM
		Ruleset();

		//! load a db (boost::filesystem::path)
		Ruleset(boost::filesystem::path filename);

		void removeOutputFormat(sqlite_int64 outputFormatId);

		#ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //  attributes
//        string mName;
        string mFilename;
		string mName;

        sqlite3* mDb;
        Replacements* mBeforeReplacementsPtr;
        Replacements* mAfterReplacementsPtr;
        map<sqlite_int64, OutputFormat*> mChildren;

        //  methodes


		//! Creates initial tables
		void initDb(sqlite3* database);


        //! opens Db
        void loadDb(boost::filesystem::path dbFile);
		void loadDb();

        //! disabled for your convenience
        Ruleset ::Ruleset (Ruleset &)
            { throw runtime_error("not implemented"); };

		//! queries all data from ruleset tables on this Sqlite3 db and inserts them to the Sqlite3 db of target
		void copyDb(sqlite3* source, sqlite3* target);
};

//class exBadName : public runtime_error {
//	public:
//		exBadName() : runtime_error("bad name") {};
//		virtual ~exBadName()  throw() {};
//	protected:
//
//	private:
//
//};

class exDbError : public runtime_error {
	public:
		exDbError() : runtime_error("could not open db") {};
		virtual ~exDbError()  throw() {};
	protected:

	private:

};

#endif // RULESET_H
