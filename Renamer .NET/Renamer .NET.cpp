// Renamer .NET.cpp: Hauptprojektdatei.

/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 

with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 

MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 

EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 

AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 

THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


#include "Windows.h"
#include "stdafx.h"
#include "WizardForm.h"
#include "globals.h"

using namespace RenamerNET;
string gInitialRuleset;
std::vector<string> gInitialFiles;

struct sqlite3 {};

/***************************************************************************************************
	This is only included to *** \todo übersetzung für befriedigen einfügen *** the dependencies
/***************************************************************************************************/

namespace boost {
	namespace re_detail {
		BOOST_REGEX_DECL char BOOST_REGEX_CALL w32_toupper(char c, lcid_type id)
		{
			char result[2];
			int b = ::LCMapStringA(
				id,       // locale identifier
				LCMAP_UPPERCASE,  // mapping transformation type
				&c,  // source string
				1,        // number of characters in source string
				result,  // destination buffer
				1);        // size of destination buffer
			if(b == 0)
				return c;
			return result[0];
		}
	}
}


[STAThreadAttribute]
int main(array<System::String ^> ^args)
{    

	if (::System::Diagnostics::Process::GetProcessesByName(::System::Diagnostics::Process::GetCurrentProcess()->ProcessName)->Length > 1) {
		HWND hwndWindow = FindWindowW(nullptr, L"Renamer");
	
		if(hwndWindow == 0) {
			Thread::Sleep(300);
			hwndWindow = FindWindowW(nullptr, L"Renamer");
		}

		if(hwndWindow != 0) {
			HWND lWnd = FindWindowRecursive(hwndWindow, L"REMOTE-CHANGE");
			if(lWnd != 0) {
				::SendMessageA(lWnd, WM_SETTEXT, 0, (LPARAM) toStlString(args[0]).c_str());
				Application::DoEvents();
			}
			return 0;
		}
	}

	if(args->Length > 0 && System::IO::File::Exists(args[0]) && System::IO::Path::GetExtension(args[0]) == L".ruleset") {
		gInitialRuleset = toStlString(args[0]);
	}

	else if(args->Length > 0) {
		for(int i=0; i<args->Length; i++)
			gInitialFiles.push_back(toStlString(args[i]));
	}


	// Name checker von Boost deaktivieren
	boost::filesystem::path::default_name_check(boost::filesystem::no_check);
	
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew WizardForm());
	return 0;
}
