#ifndef INPUT_RULE
#define INPUT_RULE

#include "globals.h"

class InputRule {
    public:
        InputRule(long rowid, sqlite3* );
        string getRegex() const;
        void setRegex(string);
        long getId() const { return mRowid; };

    private:
        long mRowid;
        sqlite3* mDb;

};

#endif //INPUT_RULE
