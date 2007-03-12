#ifndef RULESET_H
#define RULESET_H

#include "globals.h"

//! Verwaltet Regul�re Ausdr�cke
/**
Mehere Input Regul�re Ausdr�cke (z.B. Formate f�r
die selbe Serie) werden zusammengefa�t in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden k�nnen.
*/

class Ruleset
{
public:
    Ruleset();
    virtual ~Ruleset();

    void addInputRule(string regexp);
    void setOutputRule(string exp);

    //! Wird f�r jede Datei aufgerufen die umbenannt werden soll
    /** Benennt die Datei aber nicht selber um, sondern
        gibt den neuen Dateinamen zur�ck
    */
    string applyTo(string fileName);

private:
    vector<string> mInputRules;
    string mOutputRule;
};



#endif // RULESET_H
