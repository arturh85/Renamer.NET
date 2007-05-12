#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>
#include "outputFormat.h"
#include "PropertyObject.h"

//! Verwaltet Reguläre Ausdrücke
/**
Mehrere Input Reguläre Ausdrücke (z.B. Formate für
die selbe Serie) werden zusammengefaßt in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden können.
*/


const int MAGIC_OWNER_ID = 4711;

//! the root of all objects (so far :)
class Ruleset : public PropertyObject
{
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! Creates an anonymous ruleset in RAM
        Ruleset();

        Ruleset(string filename);
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
        bool applyTo(string fileName, string& outputFileName);

        //! this creates a new OutputFormat object
        OutputFormat addOutputFormat();

        //! gets a collection of OutputFormat objects
        vector<OutputFormat> getOutputFormats(string sOrderBy = "");

        void removeOutputFormat(sqlite_int64);

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

        //---------------------------------------------------------------------
        //  methodes (inherited from PropertyObject)
        PropertyObject* toPropertyObjectPtr() const;

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

};

#endif // RULESET_H
