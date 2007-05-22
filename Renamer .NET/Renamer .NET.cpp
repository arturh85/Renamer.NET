// Renamer .NET.cpp: Hauptprojektdatei.

#include "Windows.h"
#include "stdafx.h"
#include "ApplicationForm.h"
#include "WizardForm.h"
#include "globals.h"

using namespace RenamerNET;

struct sqlite3 {};

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
	boost::filesystem::path::default_name_check(boost::filesystem::no_check);
	
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew WizardForm());
	return 0;
}
