#include "stdafx.h"
#include "globals.h"
#include "stlUtility.h"

string toStdString(wstring source) {
	char* cstring = new char[source.size() +2];
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, cstring, source.size()+1, source.c_str(), _TRUNCATE);
	string ret(cstring);
	delete[] cstring;
	return ret;
}

wstring toStdWString(string source) {
	wchar_t* wcstring = new wchar_t[source.size() +2];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, source.size()+1, source.c_str(), _TRUNCATE);
	wstring ret(wcstring);
	delete[] wcstring;
	return ret;
}
