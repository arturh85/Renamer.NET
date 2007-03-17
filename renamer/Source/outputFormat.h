#ifndef OUTPUT_FORMAT
#define OUTPUT_FORMAT

#include "globals.h"
#include "inputRule.h"

class OutputFormat {
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! creates a new Replacement object.
        /** All Values are empty */
        OutputFormat(sqlite3* db) : mDb(db), mRow(db, "outputFormats") {}  ;

        //! creates a new Replacement object with existing data
        OutputFormat(sqlite3* db, sqlite_int64 row) :
            mRow(db, "outputFormats", row) {}  ;

        virtual ~OutputFormat() {};

        //---------------------------------------------------------------------
        //  methodes

        //! Creates 'regexes' and 'history' table
        static void createTables(sqlite3* db);

        //! Removes an InputRule from the database
        void removeInputRule(sqlite_int64);

        //! gets a collection of InputRule-Objects
        vector<InputRule> getInputRules();

        //! add new InputRule/regex
        InputRule addInputRule(string regexp);

        /** the output format is the resulting filename
            containing $gems$
        */
        string getFormat() const
            { return mRow.get("format"); };

        /** the output format is the resulting filename
            containing $gems$
        */
        void setFormat(string v)
            {mRow.set("format",v);} ;

        //! Wird für jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zurück
        */
       bool applyTo(string fileName, string& outputFileName);



        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //---------------------------------------------------------------------
        //  attributes
        sqlite3* mDb;
        TableRow mRow;

};

#endif //OUTPUT_FORMAT
