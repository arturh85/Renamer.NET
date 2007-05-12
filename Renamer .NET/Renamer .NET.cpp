// Renamer .NET.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "ApplicationForm.h"
#include "WizardForm.h"
#include "globals.h"

using namespace RenamerNET;

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
