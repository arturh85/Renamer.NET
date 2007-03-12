#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>

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

    #ifdef RENAMER_UNIT_TEST
    static void unitTest();
    #endif

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
