//! In dieser Datei sollten keine Projektspezifischen
//! Header Dateien eingebunden werden

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#pragma warning(disable : 4561)
#pragma warning(disable : 4793)
#pragma warning(disable : 4099)

#endif

//  sqlite
#include <sqlite3.h>
//typedef long long sqlite_rowid; --> sqlite_int64

// Boost
#include <boost/regex.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/exception.hpp>

//  STL
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
