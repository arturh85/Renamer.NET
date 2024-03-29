//! In dieser Datei sollten keine Projektspezifischen
//! Header Dateien eingebunden werden

/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the authors nor the names of its contributors may
  be used to endorse or promote products derived from this software
  without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/



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
#include <boost/filesystem.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>
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

#ifdef RENAMER_UNIT_TEST
    #include <boost/test/test_tools.hpp>

    //  Log4CPlus
    #include <log4cplus/logger.h>
    #include <log4cplus/configurator.h>
    #include <log4cplus/consoleappender.h>
    using namespace log4cplus;
#endif  //RENAMER_UNIT_TEST

#endif //GLOBALS_H
