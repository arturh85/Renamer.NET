#ifndef OUTPUT_FORMAT
#define OUTPUT_FORMAT

#include "globals.h"
#include "inputRule.h"
#include "error.h"

//! an output format is the fileName as the it should be with placeholder for the gems
class OutputFormat {
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! creates a new Replacement object.
        /** All Values are empty */
        OutputFormat(sqlite3* db) : mRow(db, "outputFormats")
            {setFormat(""); };

        //! creates a new Replacement object with existing data
        OutputFormat(sqlite3* db, sqlite_int64 row);

        virtual ~OutputFormat();

        //---------------------------------------------------------------------
        //  methodes

        //! Creates 'regexes' and 'history' table
        static void createTables(sqlite3* db);

        //! gets a collection of InputRule-Objects
        vector<InputRule*> getInputRules();

        //! add new InputRule/regex
        InputRule& addInputRule(string regexp);

        /** the output format is the resulting filename
            containing $gems$
        */
        string getFormat() const
            { return mRow.get("format"); };


		//! strips $gems$ out
		static vector<string> parse(string format);

        /** the output format is the resulting filename
            containing $gems$
        */
        void setFormat(string v);

        //! Wird für jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zurück
        */
       bool applyTo(string fileName, string& outputFileName, bool updateHistory = false);

        //! primary key field of the row this object is stored in
        sqlite_int64 getRowId() const
            { return mRow.getRowId(); };

        //! reomves this object and all its children
        void remove();

        //! B/L
        InputRule* getInputRule(sqlite_int64 rowid)
            { return (mChildren.count(rowid)==0)?NULL:mChildren[rowid]; };

        //! B/L
        Gem* getGem(sqlite_int64 rowid);

        //! save this object and all its children
        void save();

        #ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:

        //! disabled for your convinience
        OutputFormat::OutputFormat(OutputFormat&) : mRow(NULL, "regexes")
            { throw runtime_error("not implemented"); };

        //---------------------------------------------------------------------
        //  attributes
        TableRow mRow;
        map<sqlite_int64, InputRule*> mChildren;

};

#endif //OUTPUT_FORMAT
