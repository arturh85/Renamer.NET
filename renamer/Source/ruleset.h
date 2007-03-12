#ifndef RULESET_H
#define RULESET_H

#include "globals.h"

//! Verwaltet Reguläre Ausdrücke
/**
Mehere Input Reguläre Ausdrücke (z.B. Formate für
die selbe Serie) werden zusammengefaßt in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden können.
*/

class Ruleset
{
public:
    Ruleset();
    virtual ~Ruleset();

    void addInputRule(string regexp);
    void setOutputRule(string exp);

    //! Wird für jede Datei aufgerufen die umbenannt werden soll
    /** Benennt die Datei aber nicht selber um, sondern
        gibt den neuen Dateinamen zurück
    */
    string applyTo(string fileName);

private:
    vector<string> mInputRules;
    string mOutputRule;
};



#endif // RULESET_H
