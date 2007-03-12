#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>

// Boost
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

//! Verwaltet Regul�re Ausdr�cke
/**
Mehrere Input Regul�re Ausdr�cke (z.B. Formate f�r
die selbe Serie) werden zusammengefa�t in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden k�nnen.
*/

class Ruleset
{
public:
    //  constructors

    //! Creates or loads a Ruleset
    Ruleset(string name);

    //  destructor
    virtual ~Ruleset();

    //  methodes
    void addInputRule(string regexp);
    void setOutputFormat(string exp);
    string getOutputFormat() const;

    //! Wird f�r jede Datei aufgerufen die umbenannt werden soll
    /** Benennt die Datei aber nicht selber um, sondern
        gibt den neuen Dateinamen zur�ck
    */
    bool applyTo(string fileName, string& outputFileName);

private:
    //  attributes
//    vector<string> mInputRules;
//    string mOutputRule;
    string mName;
    sqlite3* mDb;

    //  methodes
    void initDb();

};

#endif // RULESET_H
