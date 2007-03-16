#pragma once

#include "globals.h"
#include "vcclr.h"

std::string toStdString(std::wstring source);
std::string toStdString(System::String^ source);
std::wstring toStdWString(System::String^ source);
std::wstring toStdWString(std::string source);

System::String^ toClrString( std::string source );
System::String^ toClrString( std::wstring source );
