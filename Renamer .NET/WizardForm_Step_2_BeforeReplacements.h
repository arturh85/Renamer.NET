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
