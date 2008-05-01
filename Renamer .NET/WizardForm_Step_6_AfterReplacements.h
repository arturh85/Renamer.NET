		 void onEnterStepAfterReplacements() {
//			 applyChanges(Step::AFTER_REPLACEMENTS);
		 }

		 void onLeaveStepAfterReplacements() {

		 }
		 void applyAfterReplacements() {
			 fileList->BeginUpdate();
			 LockWindowUpdate((HWND) (int) fileList->Handle);

			 Replacements replacements = mRuleset->getAfterReplacements();
			 for(int i=0; i<fileList->Items->Count; i++) {
				 ListViewItem^ item = fileList->Items[i];
				 item->Text = toClrString(replacements.replace(toStlString(item->Text)));
			 }

			 fileList->EndUpdate();
			 LockWindowUpdate((HWND) 0);
		 }

		 void saveAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 Replacements& replacements = mRuleset->getAfterReplacements();

			 int rowCount = gridAfterReplacements->Rows->Count;
			 vector<sqlite_int64> replacementsWhichWereNotDeleted ;
			 for(int i=0; i<gridAfterReplacements->Rows->Count; i++) {
				 if(gridAfterReplacements->Rows[i]->Cells[0]->Value == nullptr) {
					 String^ search = (String^)gridAfterReplacements->Rows[i]->Cells[2]->Value;
					 String^ replace = (String^)gridAfterReplacements->Rows[i]->Cells[3]->Value;
					 if(search != nullptr) {
						 if(replace == nullptr)
							 replace = L"";
						 Replacement* replacement = replacements.addReplacement(toStlString(search), toStlString(replace));
						 replacementsWhichWereNotDeleted.push_back(replacement->getRowId());
						 gridAfterReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement->getRowId());
						 gridAfterReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement->getGroupId());
					 }
				 }

				 else {
					 int rowid = (int)((Int32^)gridAfterReplacements->Rows[i]->Cells[0]->Value);
					 String^ search = (String^)gridAfterReplacements->Rows[i]->Cells[2]->Value;
					 String^ replace = (String^)gridAfterReplacements->Rows[i]->Cells[3]->Value;
					 if(search != nullptr) {
						 if(replace == nullptr)
							 replace = L"";

						 replacementsWhichWereNotDeleted.push_back(rowid);
						 Replacement& replacement = mRuleset->getReplacement(rowid);
						 replacement.setRegex(toStlString(search));
						 replacement.setReplacement(toStlString(replace));
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

				 if(found == false) {
					 Replacement& replacement = mRuleset->getReplacement(replacementVector[i]->getRowId());
					 replacement.remove();
				 }
			 }

			 mRuleset->save();
		 }

		 void loadAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 gridAfterReplacements->Rows->Clear();
			 Replacements replacements = mRuleset->getAfterReplacements();
			 vector<Replacement*> replacementVector = replacements.getReplacements();

			 for(unsigned int i=0; i<replacementVector.size(); i++) {
				 cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
				 values[0] = gcnew Int32 ((Int32)replacementVector[i]->getRowId());
				 values[1] = gcnew Int32 ((Int32)replacementVector[i]->getGroupId());
				 values[2] = toClrString(replacementVector[i]->getRegex().str());
				 values[3] = toClrString(replacementVector[i]->getReplacement());

				 gridAfterReplacements->Rows->Add(values);
			 }
		 }
