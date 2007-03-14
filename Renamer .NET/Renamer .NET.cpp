// Renamer .NET.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "ApplicationForm.h"

#include "sqlite3.h"
#include <string>

#include <boost/program_options.hpp>

using namespace RenamerNET;
using namespace std;

Ruleset* rule = NULL;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	ApplicationForm^ form = gcnew ApplicationForm();
	form->renamer = gcnew Renamer(form);
	Application::Run(form);
	return 0;
}
