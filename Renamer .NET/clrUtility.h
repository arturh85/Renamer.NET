#pragma once

#include "globals.h"
#include "vcclr.h"

std::string toStdString(System::String^ source);
std::wstring toStdWString(System::String^ source);

System::String^ toClrString( std::string source );
System::String^ toClrString( std::wstring source );

namespace RenamerNET {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class _PairStringInt : public Object 
	{
	public:
		_PairStringInt(String^ key, sqlite_int64 value) : key(key), value(value){}
		String^ key;
		sqlite_int64  value;
	};
}