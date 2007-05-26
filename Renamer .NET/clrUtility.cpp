#include "StdAfx.h"
#include "clrUtility.h"

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

string toStlString(String^ source) {
	 string target;
	 To_string(source, target);
	 return target;
}

wstring toStdWString(System::String^ source) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars = 
		(const wchar_t*)(Marshal::StringToHGlobalUni(source)).ToPointer();
	wstring ret(chars);
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return ret;
}

String^ toClrString( string source )
{
 String^ target = gcnew String( source.c_str() );
 return target;
}

String^ toClrString( wstring source )
{
	String^ target = gcnew String(source.c_str());
	return target;
}
