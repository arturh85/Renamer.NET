/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


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

	refreshMaxStep();
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
	refreshMaxStep();
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