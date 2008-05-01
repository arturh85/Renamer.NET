private: System::Void checkBoxShowOnlyMatchingFiles_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	mShowOnlyMatchingFiles = !mShowOnlyMatchingFiles;
	applyChanges(mStep);
}

void onEnterStepRuleset() {
	cboRulesets->BeginUpdate();
	LockWindowUpdate((HWND) (int) cboRulesets->Handle);

	cboRulesets->Items->Clear();
	for(int i=0; i<mKnownRulesets.Count; i++) {
		ListBoxItem^ item = gcnew ListBoxItem();
		item->Text = Path::GetFileNameWithoutExtension(mKnownRulesets[i]);
		item->Tag = mKnownRulesets[i];
		cboRulesets->Items->Add(item);

		if(mRuleset != NULL && Path::GetFileNameWithoutExtension(toClrString(mRuleset->getFilename())) == item->Text)
			cboRulesets->SelectedIndex = i;
	}
	
	cboRulesets->EndUpdate();
	LockWindowUpdate((HWND) 0);

	applyChanges(Step::RULESET_SELECT);
}

void onLeaveStepRuleset() {

}

private: System::Void cboRulesets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ListBoxItem^ item = (ListBoxItem^) cboRulesets->Items[cboRulesets->SelectedIndex];
	String^ rulesetFilename = (String^) item->Tag;

	if(mRuleset == NULL || rulesetFilename != toClrString(mRuleset->getFilename()))
		loadRuleset(rulesetFilename);
//	cboRulesets->Text = toClrString(mRuleset->getName());

	applyChanges(Step::RULESET_SELECT);
}

private: System::Void openRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	String^ rulesetFilename = openRulesetFileDialog->FileName;
	loadRuleset(rulesetFilename);
}

private: System::Void saveRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	String^ rulesetFilename = saveRulesetFileDialog->FileName;
	createRuleset(rulesetFilename);
}

private: System::Void tsLoadRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	openRulesetFileDialog->ShowDialog();
}

private: System::Void tsSaveRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	saveRulesetFileDialog->ShowDialog();
}