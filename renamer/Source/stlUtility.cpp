#include "stdafx.h"
#include "globals.h"
#include "stlUtility.h"
#include <stdlib.h>

string toStlString(wstring source) {
	char* cstring = new char[source.size() +2];
	//unused        size_t convertedChars = 0;
	wcstombs(cstring, source.c_str(), source.size()+1);
	string ret(cstring);
	delete[] cstring;
	return ret;
}

wstring toStdWString(string source) {
	wchar_t* wcstring = new wchar_t[source.size() +2];
	//unused        size_t convertedChars = 0;
	mbstowcs(wcstring, source.c_str(), source.size()+1);
	wstring ret(wcstring);
	delete[] wcstring;
	return ret;
}
