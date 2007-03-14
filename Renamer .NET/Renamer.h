#pragma once

#include <vcclr.h>
#include "ruleset.h"

namespace RenamerNET {
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class ApplicationForm;

public ref class Renamer {
public:

	Renamer(ApplicationForm^ form);
	

	void addFile(String^ pathToFile);
	void addInputRule(long long inputRuleID) ;
	void removeInputRule(long long inputRuleID) ;
	void loadOrCreateSet(String^ setName);
	void renameSet(String^ oldSetName, System::String^ newSetName) ;
	void onSetSelection() ;
	void refreshInputsList();
	void refreshSetList();
private:
	ApplicationForm^ mForm;
};
}
