			 void onEnterStepInputRules() {
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 txtGemInputRule->Text = toClrString(inputRule.getRegex());
					 loadGems();
					 gridGems_SelectionChanged(nullptr, nullptr);
				 }

				 if(mInputRuleID != 0 && lstInputRules->Items->Count >= 2) 
					 tsMergeInputRules->Visible = true;
				 else
					 tsMergeInputRules->Visible = false;

				 mMergeRuleID_1 = 0;
				 mMergeRuleID_2 = 0;

				 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);

				 txtCurrentOutputFormat->Text = toClrString(outputFormat.getFormat());

				 int cursorPosition = txtCurrentOutputFormat->SelectionStart;

				 txtCurrentOutputFormat->Select(0, txtCurrentOutputFormat->Text->Length);
				 txtCurrentOutputFormat->SelectionColor = Color::Black;

				 int start = -1;
				 for(int i=0; i<txtCurrentOutputFormat->Text->Length; i++) {
					 if(txtCurrentOutputFormat->Text[i] == L'$') {
						 if(start == -1)
							 start = i;
						 else {
							 txtCurrentOutputFormat->Select(start, i - start + 1);
							 txtCurrentOutputFormat->SelectionColor = Color::Red;
							 start = -1;
						 }
					 }
				 }

				 txtCurrentOutputFormat->Select(cursorPosition,0);

				 refreshInputRuleList();
				 if(lstInputRules->Items->Count > 0)
					 lstInputRules->SelectedIndex = 0;
				 else 
					 disableTxtInputRule();
				 tsSaveInputRule->Visible = false;
				 applyChanges(Step::INPUTRULES_SELECT);
			 }

			 void onLeaveStepInputRules() {
				 saveGems();
			 }

			 void applyInputRules() {
				 fileList->BeginUpdate();
				 LockWindowUpdate((HWND) (int) fileList->Handle);
	
				 // determine which files are matched with this input rule
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 vector<GemValue> not_used;
					 for(int i=0; i<fileList->Items->Count; i++) {
						 ListViewItem^ item = fileList->Items[i];
						 if(inputRule.applyTo(toStlString(item->Text), not_used)) 
							 item->BackColor = Color::LightGreen;
						 else
							 item->BackColor = Color::LightCoral;
					 }
				 }

				 // determine which files are matched with all other input rules
				 for(int j=0; j<lstInputRules->Items->Count; j++) {
					int inputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->Items[j])->Tag)->value;

					if(inputRuleID != mInputRuleID) {
						InputRule& inputRule = mRuleset->getInputRule(inputRuleID);
						vector<GemValue> not_used;
						for(int i=0; i<fileList->Items->Count; i++) {
							ListViewItem^ item = fileList->Items[i];

							if(item->BackColor == Color::LightCoral && inputRule.applyTo(toStlString(item->Text), not_used)) 
								item->BackColor = Color::Yellow;
						}
					}
				 }

				 fileList->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }


	private: System::Void tsAddInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(mCustomStrings->GetString(L"Strings.NewInputRule")));

			 mRuleset->save();

			 refreshInputRuleList();

			 lstInputRules->SelectedIndex = lstInputRules->Items->Count - 1;
			 applyChanges(mStep);

			 // TODO: move selection to the last character
			 txtInputRule->Focus();

			 if(mInputRuleID != 0 && lstInputRules->Items->Count >= 2) 
					 tsMergeInputRules->Visible = true;
				 else
					 tsMergeInputRules->Visible = false;
	}
	private: System::Void tsRemoveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 outputFormat.removeInputRule(rowid);

			 refreshInputRuleList();
			 refreshMaxStep();

			 disableTxtInputRule();
			 mInputRuleID = 0;

			 tsMergeInputRules->Visible = false;

			 applyChanges(mStep);
		 }
	private: System::Void tsDuplicateInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(lstInputRules->SelectedItem->ToString()));
			 refreshInputRuleList();

			 if(mInputRuleID != 0 && lstInputRules->Items->Count >= 2) 
					 tsMergeInputRules->Visible = true;
				 else
					 tsMergeInputRules->Visible = false;

		 }
	private: System::Void tsSaveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = mRuleset->getInputRule(rowid);

			 try {
				 inputRule.setRegex(toStlString(txtInputRule->Text));
				 inputRule.updateGems(outputFormat.getFormat());
			 }

			 catch(...) {
				 // the input rule entered appears to be invalid
	
				 txtInputRule->BackColor = Color::LightCoral;
				 return ;
			 }

			 //! \todo: find out what BackColor should be usually ...
			 txtInputRule->BackColor = txtOutputFormat->BackColor;

			 int selectedIndex = lstInputRules->SelectedIndex;
			 refreshInputRuleList();
			 lstInputRules->SelectedIndex = selectedIndex;
			 tsSaveInputRule->Visible = false;

			 ListBoxItem^ lbi = (ListBoxItem^) lstInputRules->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;

			 properties->key = txtInputRule->Text;

			 mRuleset->save();
			 applyInputRules();
			 applyChanges(mStep);
		 }
	private: System::Void lstInputRules_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstInputRules->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;

			 if(mMergeRuleID_1 != 0) {
				 mMergeRuleID_2 = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;


				 InputRule& inputRule1 = mRuleset->getInputRule(mMergeRuleID_1);
				 InputRule& inputRule2 = mRuleset->getInputRule(mMergeRuleID_2);

				 String^ rule1 = toClrString(inputRule1.getRegex());
				 String^ rule2 = toClrString(inputRule2.getRegex());


				 String^ mergedRule = mergeInputRules(rule1, rule2);
				 endMergeInputRuleMode();

				 if(mergedRule != nullptr) {
					
					OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
	

					try {
					    InputRule& inputRule = outputFormat.addInputRule(toStlString(mergedRule));
					mInputRuleID = inputRule.getRowId();
						
					} catch(...) {
						return ;
					}


					outputFormat.removeInputRule(inputRule1.getRowId());
					outputFormat.removeInputRule(inputRule2.getRowId());

					mRuleset->save();
					refreshInputRuleList();

					return ;
				 }
			 }

			 txtInputRule->Enabled = true;
			 txtInputRule->Text = properties->key;
			 mInputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 tsSaveInputRule->Visible = false;

			 loadGems();
			 applyInputRules();
			 applyChanges(mStep);
			 
			 if(mInputRuleID != 0 && lstInputRules->Items->Count >= 2) 
					 tsMergeInputRules->Visible = true;
				 else
					 tsMergeInputRules->Visible = false;
			 
		 }
	private: System::Void txtInputRule_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 tsSaveInputRule->Visible = true;
		 }
	private: System::Void txtInputRule_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Return && tsSaveInputRule->Visible) {
				 tsSaveInputRule_Click(nullptr, nullptr);
			 }
		 }


			 void refreshInputRuleList() {
				 lstInputRules->BeginUpdate();
				 LockWindowUpdate((HWND) (int) lstInputRules->Handle);

				 if(mRuleset && mOutputFormatID > 0) {
					 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
					 vector<InputRule*> inputRuleVector = outputFormat.getInputRules();

					 lstInputRules->Items->Clear();				
					 for(unsigned int i=0; i<inputRuleVector.size(); i++) {
						 ListBoxItem^ lbi = gcnew ListBoxItem();
						 lbi->Text = toClrString(inputRuleVector[i]->getRegex());
						 lbi->Tag = gcnew _PairStringInt(lbi->Text, inputRuleVector[i]->getRowId());
						 lstInputRules->Items->Add(lbi);
					 }
				 }

				 lstInputRules->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }
private: System::Void gridGems_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(mRuleset == NULL) 
				 return ;
			 
			 saveGems();
			 mRuleset->save();
			 applyChanges(mStep);
		 }

private: String^ mergeInputRules(String^ rule1, String^ rule2) {
			 // TODO: implement
			return nullptr;
		 }

 private: System::Void tsUseAsNewInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			if(fileList->SelectedItems->Count != 1) return ;

			String^ selectedFilename = fileList->SelectedItems[0]->Text;

			selectedFilename = escapeRegularExpression(selectedFilename, false);

			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(selectedFilename));

			 mRuleset->save();

			 refreshInputRuleList();

			 lstInputRules->SelectedIndex = lstInputRules->Items->Count - 1;
			 applyChanges(mStep);

			 txtInputRule->Focus();

			 if(mInputRuleID != 0 && lstInputRules->Items->Count >= 2) 
					 tsMergeInputRules->Visible = true;
			 else
				 tsMergeInputRules->Visible = false;


		 }



