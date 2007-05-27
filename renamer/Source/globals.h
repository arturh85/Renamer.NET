//! In dieser Datei sollten keine Projektspezifischen
//! Header Dateien eingebunden werden

#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#pragma warning(disable : 4561)
#pragma warning(disable : 4793)
#pragma warning(disable : 4099)
#endif

//  sqlite
#include <sqlite3.h>

// Boost
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/convenience.hpp>
//#include <boost/filesystem/exception.hpp>

//  STL
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#endif //GLOBALS_H
