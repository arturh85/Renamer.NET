#pragma once

#include <vcclr.h>
#include "ruleset.h"

namespace RenamerNET {

ref class ApplicationForm;

public ref class Renamer {
public:
	Renamer(ApplicationForm^ form);

	void addInputRule(long long inputRuleID) ;
	void removeInputRule(long long inputRuleID) ;
	void loadOrCreateSet(System::String^ setName);
	void renameSet(System::String^ oldSetName, System::String^ newSetName) ;
	void onSetSelection() ;
	void refreshInputsList();
	void refreshSetList();
private:
	ApplicationForm^ mForm;
};
}
