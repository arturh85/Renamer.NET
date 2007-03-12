// Renamer .NET.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"

#include "sqlite3.h"
#include <string>

#include <boost/program_options.hpp>

using namespace RenamerNET;
using namespace std;

namespace po = boost::program_options;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("add", po::value<string>(), "add a regular expression to the set")
		("set", po::value<string>(), "set to use")
		("setOutputFormat", po::value<string>(), "")
		;

	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());
	return 0;
}
