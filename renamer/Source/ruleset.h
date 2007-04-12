#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>
#include "outputFormat.h"
#include "PropertyObject.h"

//! Verwaltet Regul�re Ausdr�cke
/**
Mehrere Input Regul�re Ausdr�cke (z.B. Formate f�r
die selbe Serie) werden zusammengefa�t in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden k�nnen.
*/

//! the root of all objects (so far :)
class Ruleset : public PropertyObject
{
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! Creates an anonymous ruleset in RAM
        Ruleset();

        Ruleset(string name);
        Ruleset(wstring name);

        virtual ~Ruleset();

        //---------------------------------------------------------------------
        //  methodes
        //void setOutputFormat(string exp);
        //string getOutputFormat() const;

        //! Wird f�r jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zur�ck
        */
        bool applyTo(string fileName, string& outputFileName);

        //! this creates a new OutputFormat object
        OutputFormat addOutputFormat();

        //! gets a collection of OutputFormat objects
        vector<OutputFormat> getOutputFormats(string sOrderBy = "");

        void removeOutputFormat(sqlite_int64);

        string getName() const;


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
        sqlite3* mDb;

        //  methodes
        //! Creates initial tables
        void initDb();

};

#endif // RULESET_H
