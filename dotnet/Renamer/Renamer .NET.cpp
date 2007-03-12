// Renamer .NET.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"

#include "sqlite3.h"

using namespace RenamerNET;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	sqlite3_open(0, 0);
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());
	return 0;
}
