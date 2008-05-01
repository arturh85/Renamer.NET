/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


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


		void removeInputRule(sqlite_int64 inputRuleId);

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

        //! disabled for your convenience
        OutputFormat::OutputFormat(OutputFormat&) : mRow(NULL, "regexes")
            { throw runtime_error("not implemented"); };

        //---------------------------------------------------------------------
        //  attributes
        TableRow mRow;
        map<sqlite_int64, InputRule*> mChildren;

};

#endif //OUTPUT_FORMAT
