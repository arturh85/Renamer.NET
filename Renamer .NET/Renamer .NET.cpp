// Renamer .NET.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "ApplicationForm.h"
#include "globals.h"

using namespace RenamerNET;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	boost::filesystem::path::default_name_check(boost::filesystem::native);

	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew ApplicationForm());
	return 0;
}
