#pragma once

#include "globals.h"
#include "vcclr.h"

string toStdString(System::String^ source);
System::String^ toClrString( std::string source );
