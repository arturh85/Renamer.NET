#include "stdafx.h"
#include "inputRule.h"

InputRule::InputRule(long rowid, sqlite3* db) {
    mRowid = rowid;
    mDb = db;
}

string InputRule::getRegex() const {
    string sRetVal;
    return sRetVal;
}
