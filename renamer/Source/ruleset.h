#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>
#include "outputFormat.h"

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

        //! Creates an anonymous ruleset in RAM
        Ruleset();

        //! load a db (boost::filesystem::path)
        Ruleset(boost::filesystem::path filename);

        //! load a db (std::string)
        Ruleset(string filename);

        //! load a db (std::wstring)
        Ruleset(wstring filename);

        virtual ~Ruleset();

        //---------------------------------------------------------------------
        //  methodes
        //void setOutputFormat(string exp);
        //string getOutputFormat() const;

        //! Wird für jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zurück
        */
        bool applyTo(string fileName, string& outputFileName, bool updateHistory = false);

        //! Rename a 'phsyical' file
        /**
          This updates the history table.
          If false is returned no InputRule is matched.
          If any other error (like bad/duplicate filename) occours
          an exception is thrown.
        */
        bool rename(string fileName);


        //! this creates a new OutputFormat object
        OutputFormat addOutputFormat();

        //! gets a collection of OutputFormat objects
        vector<OutputFormat> getOutputFormats(string sOrderBy = "");

        string getName() const;
        string getFilename() const;

        ///\todo this is bad :(
        sqlite3* getDatabase();

        ///these are applied before anything else is done with the filename
        Replacements& getBeforeReplacements() const { return *mBeforeReplacementsPtr; };

        ///these are applied at the very end of everyting
        Replacements& getAfterReplacements() const { return *mAfterReplacementsPtr; };

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //  attributes
        string mName;
        string mFilename;
        sqlite3* mDb;
        Replacements* mBeforeReplacementsPtr;
        Replacements* mAfterReplacementsPtr;

        //  methodes
        //! Creates initial tables
        void initDb();

        //! opens Db
        void loadDb(boost::filesystem::path dbFile);

};

class exBadName : public runtime_error {
	public:
		exBadName() : runtime_error("bad name") {};
		virtual ~exBadName()  throw() {};
	protected:

	private:

};

class exDbError : public runtime_error {
	public:
		exDbError() : runtime_error("could not open db") {};
		virtual ~exDbError()  throw() {};
	protected:

	private:

};



#endif // RULESET_H
