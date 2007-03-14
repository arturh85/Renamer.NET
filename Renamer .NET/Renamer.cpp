#include "stdafx.h"
#include "Renamer.h"
#include "ApplicationForm.h"
#include "Utility.h"

namespace RenamerNET {

Renamer::Renamer(ApplicationForm^ form) {
	mForm = form;
}

void Renamer::addInputRule(long long inputRuleID) 
{
	//! \todo implement
}

void Renamer::removeInputRule(long long inputRuleID) {
	//! \todo implement
}

void Renamer::loadOrCreateSet(String^ setName) 
{
	 if(rule)
		 delete rule;
	 rule = new Ruleset(toStdString(setName));
}

void Renamer::renameSet(String^ oldSetName, String^ newSetName) {
	 if(rule) {
		 string setName = rule->getName();
		 if(setName == toStdString(oldSetName)) {
			 delete rule;
			 System::IO::File::Move(oldSetName + ".db3", newSetName + ".db3");
			 rule = new Ruleset(toStdString(newSetName));
		 }
	 }

	 else {
		 System::IO::File::Move(oldSetName + ".db3", newSetName + ".db3");
	 }
 }


void Renamer::onSetSelection() 
{
	loadOrCreateSet(mForm->cboSets->Text);
	refreshSetList();
	refreshInputsList();
	mForm->txtOutputFormat->Text = toClrString( rule ? rule->getOutputFormat() : "");
	mForm->cboSets->Text = toClrString( rule ? rule->getName() : "");
}




void Renamer::refreshInputsList() 
{
	 mForm->lstInputs->Items->Clear();
	 vector<string> regExes;
	 if(rule) 
		 rule->fetchInputRules(regExes);

	 for(unsigned int i=0; i<regExes.size(); i++) {
		 mForm->lstInputs->Items->Add(toClrString(regExes[i]));
	 }
}

void Renamer::refreshSetList() 
{
	 mForm->cboSets->Items->Clear();

	 using namespace System::IO;
	 array<String^>^fileNames = Directory::GetFiles( ".\\", "*.db3" );

	 for(int i=0; i<fileNames->Length; i++) {
		 String^ fileName = fileNames[i]->Substring(2);
		 String^ setName = fileName->Substring(0, fileName->Length-4);
		 mForm->cboSets->Items->Add(setName);
	 }
}
}