#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>

// Boost
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

//! Verwaltet Reguläre Ausdrücke
/**
Mehrere Input Reguläre Ausdrücke (z.B. Formate für
die selbe Serie) werden zusammengefaßt in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden können.
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

    //! Wird für jede Datei aufgerufen die umbenannt werden soll
    /** Benennt die Datei aber nicht selber um, sondern
        gibt den neuen Dateinamen zurück
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
