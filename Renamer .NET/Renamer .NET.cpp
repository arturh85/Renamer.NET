// Renamer .NET.cpp: Hauptprojektdatei.

#include "Windows.h"
#include "stdafx.h"
#include "WizardForm.h"
#include "globals.h"

using namespace RenamerNET;
string gInitialRuleset;

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
	if(args->Length > 0 && System::IO::File::Exists(args[0]) && System::IO::Path::GetExtension(args[0]) == L".ruleset") {
		gInitialRuleset = toStlString(args[0]);
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
