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


void onEnterStepBeforeReplacements() {
	loadBeforeReplacements();	
	applyChanges(Step::BEFORE_REPLACEMENTS);
}

void onLeaveStepBeforeReplacements() {
	saveBeforeReplacements();
}

void applyBeforeReplacements() {
	fileList->BeginUpdate();
	LockWindowUpdate((HWND) (int) fileList->Handle);

	Replacements& replacements = mRuleset->getBeforeReplacements();
	for(int i=0; i<fileList->Items->Count; i++) {
		ListViewItem^ item = fileList->Items[i];
		item->Text = toClrString(replacements.replace(toStlString(item->Text)));
	}

	fileList->EndUpdate();
	LockWindowUpdate((HWND) 0);
}

void saveBeforeReplacements() {
	if(mRuleset == NULL) return ;
	Replacements& replacements = mRuleset->getBeforeReplacements();

	int rowCount = gridBeforeReplacements->Rows->Count;
	vector<sqlite_int64> replacementsWhichWereNotDeleted ;
	for(int i=0; i<gridBeforeReplacements->Rows->Count; i++) {
		//gridBeforeReplacements->Rows[i]->Cells[0]->Style->BackColor = Color::White;

		// if replacement does not exist yet, add one
		if(gridBeforeReplacements->Rows[i]->Cells[0]->Value == nullptr) {
			String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
			String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
			if(search != nullptr) {
				if(replace == nullptr)
					replace = L"";
				try {
					Replacement* replacement = replacements.addReplacement(toStlString(escapeRegularExpression(search, false)), toStlString(replace));
					replacementsWhichWereNotDeleted.push_back(replacement->getRowId());
					gridBeforeReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement->getRowId());
					gridBeforeReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement->getGroupId());
				} catch (...) {
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->BackColor = Color::LightCoral;
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->SelectionBackColor = Color::LightCoral;
				}
			}
		}
		
		// if replacement already exists, update it
		else {
			int rowid = (int)((Int32^)gridBeforeReplacements->Rows[i]->Cells[0]->Value);
			String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
			String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
			if(search != nullptr) {
				if(replace == nullptr)
					replace = L"";

				replacementsWhichWereNotDeleted.push_back(rowid);
				Replacement& replacement = mRuleset->getReplacement(rowid);
				
				try {
					replacement.setRegex(toStlString(escapeRegularExpression(search, false)));
					replacement.setReplacement(toStlString(replace));
				} catch (...) {
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->BackColor = Color::LightCoral;
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->SelectionBackColor = Color::LightCoral;
				}
			}
		}
	}

	vector<Replacement*> replacementVector = replacements.getReplacements();
	for(unsigned int i=0; i<replacementVector.size(); i++) {
		bool found = false;
		for(unsigned int j=0; j<replacementsWhichWereNotDeleted.size(); j++) {
			if(replacementVector[i]->getRowId() == replacementsWhichWereNotDeleted[j]) {
				found = true;
			}
		}

		// replacement was removed, so remove it ...
		if(found == false) {
			Replacement& replacement = mRuleset->getReplacement(replacementVector[i]->getRowId());
			replacement.remove();
		}
	}

	// save the changes from the object modell to the database
	mRuleset->save();
}

void loadBeforeReplacements() {
	LockWindowUpdate((HWND) (int) gridBeforeReplacements->Handle);

	if(mRuleset == NULL) return ;
	gridBeforeReplacements->Rows->Clear();
	Replacements& replacements = mRuleset->getBeforeReplacements();
	vector<Replacement*> replacementVector = replacements.getReplacements();

	for(unsigned int i=0; i<replacementVector.size(); i++) {
		cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
		values[0] = gcnew Int32 ((Int32)replacementVector[i]->getRowId());
		values[1] = gcnew Int32 ((Int32)replacementVector[i]->getGroupId());
		values[2] = escapeRegularExpression(toClrString(replacementVector[i]->getRegex().str()), true);
		values[3] = toClrString(replacementVector[i]->getReplacement());

		gridBeforeReplacements->Rows->Add(values);
	}

	LockWindowUpdate((HWND) 0);
}

private: System::Void gridBeforeReplacements_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	 if(mStep == Step::BEFORE_REPLACEMENTS) {
		 saveBeforeReplacements();
		 applyChanges(mStep);
	 }
}

 private: System::Void gridBeforeReplacements_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
	 
 }