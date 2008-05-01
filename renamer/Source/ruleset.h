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


#ifndef RULESET_H
#define RULESET_H

#include "globals.h"
#include <sqlite3.h>
#include "outputFormat.h"
#include "error.h"

//! Verwaltet Reguläre Ausdrücke
/**
Mehrere Input Reguläre Ausdrücke (z.B. Formate für
die selbe Serie) werden zusammengefaßt in dieser
Klasse, und mit Hilfe eines Output Ausdrucks
in ein gemeinsames Format konvertiert werden können.
*/


const int MAGIC_OWNER_ID = 4711;

//! the root of all objects (so far :)
class Ruleset
{
    public:
        //---------------------------------------------------------------------
        //  constructors & destructor

        //! load a db (std::string)
        Ruleset(string filename);

        //! load a db (std::wstring)
        Ruleset(wstring filename);

        virtual ~Ruleset();

        //---------------------------------------------------------------------
        //  methodes

        //! Wird für jede Datei aufgerufen die umbenannt werden soll
        /** Benennt die Datei aber nicht selber um, sondern
            gibt den neuen Dateinamen zurück
            This uses the before/after replacements.
        */
        bool applyTo(string fileName, string& outputFileName, bool updateHistory = false);

        //! Rename a 'physical' file
        /**
          This updates the history table.
          If false is returned no InputRule is matched.
          If any other error (like bad/duplicate filename) occurs
          an exception is thrown.
        */
        bool rename(string fileName);

        //! this creates a new OutputFormat object
        OutputFormat& addOutputFormat();

        //! gets a collection of OutputFormat objects
        vector<OutputFormat*> getOutputFormats();

		string getFilename() const;
		string getName() const;

        /// these are applied before anything else is done with the filename
        Replacements& getBeforeReplacements() const { return *mBeforeReplacementsPtr; };

        /// these are applied at the very end of everything
        Replacements& getAfterReplacements() const { return *mAfterReplacementsPtr; };

        //! gui convenience
        OutputFormat& getOutputFormat(sqlite_int64 rowid)
            { if (mChildren.count(rowid)==0) throw exNoSuchId();
              return *(mChildren[rowid]); };

        //! gui convenience
        InputRule& getInputRule(sqlite_int64 rowid);

        //! gui convenience
        Gem& getGem(sqlite_int64 rowid);

        //! gui convenience
        Replacement& getReplacement(sqlite_int64 rowid);

        //! save this object and all its children
        void save();

		//! Creates an anonymous ruleset in RAM
		Ruleset();

		//! load a db (boost::filesystem::path)
		Ruleset(boost::filesystem::path filename);

		void removeOutputFormat(sqlite_int64 outputFormatId);

		#ifdef RENAMER_UNIT_TEST
        //! UnitTest this object
        static void unitTest();
        #endif

    private:
        //  attributes
//        string mName;
        string mFilename;
		string mName;

        sqlite3* mDb;
        Replacements* mBeforeReplacementsPtr;
        Replacements* mAfterReplacementsPtr;
        map<sqlite_int64, OutputFormat*> mChildren;

        //  methodes


		//! Creates initial tables
		void initDb(sqlite3* database);


        //! opens Db
        void loadDb(boost::filesystem::path dbFile);
		void loadDb();

        //! disabled for your convenience
        Ruleset ::Ruleset (Ruleset &)
            { throw runtime_error("not implemented"); };

		//! queries all data from ruleset tables on this Sqlite3 db and inserts them to the Sqlite3 db of target
		void copyDb(sqlite3* source, sqlite3* target);
};

//class exBadName : public runtime_error {
//	public:
//		exBadName() : runtime_error("bad name") {};
//		virtual ~exBadName()  throw() {};
//	protected:
//
//	private:
//
//};

class exDbError : public runtime_error {
	public:
		exDbError() : runtime_error("could not open db") {};
		virtual ~exDbError()  throw() {};
	protected:

	private:

};

#endif // RULESET_H
