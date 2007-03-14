#include "StdAfx.h"
#include "Utility.h"

using namespace System;

static bool To_string( String^ source, string &target )
{
	pin_ptr<const wchar_t> wch = PtrToStringChars( source );
	int len = (( source->Length+1) * 2);
	char *ch = new char[ len ];
	bool result = wcstombs( ch, wch, len ) != -1;
	target = ch;
	delete ch;
	return result;
}

static bool To_CharStar( String^ source, char*& target )
{
	pin_ptr<const wchar_t> wch = PtrToStringChars( source );
	int len = (( source->Length+1) * 2);
	target = new char[ len ];
	return wcstombs( target, wch, len ) != -1;
}

string toStdString(String^ source) {
	 string target;
	 To_string(source, target);
	 return target;
}

String^ toClrString( string source )
{
 String^ target = gcnew String( source.c_str() );
 return target;
}
