#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include "inputRule.h"
#include <sqlite3.h>

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
    Ruleset();
    Ruleset(string name);

    //  destructor
    virtual ~Ruleset();

    //  methodes
    InputRule addInputRule(string regexp);
    void setOutputFormat(string exp);
    string getOutputFormat() const;
	void fetchInputRules(vector<string>& outputParam);


    //! Wird f�r jede Datei aufgerufen die umbenannt werden soll
    /** Benennt die Datei aber nicht selber um, sondern
        gibt den neuen Dateinamen zur�ck
    */
    bool applyTo(string fileName, string& outputFileName);

	string getName() const;

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
