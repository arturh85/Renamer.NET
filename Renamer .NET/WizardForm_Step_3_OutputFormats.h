#pragma region Business Code

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



void onEnterStepOutputFormats() {
				 applyChanges(Step::OUTPUTFORMAT_SELECT);
				 refreshOutputFormatList();			 
				 if(lstOutputFormat->Items->Count > 0) {
					 if(mOutputFormatID > 0) {
						 int index = -1;
						 for(int i=0; i<lstOutputFormat->Items->Count; i++) {
							 if(((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->Items[i])->Tag)->value == mOutputFormatID) {
								 index = i;
							 }
						 }

						 if(index == -1) {
							 lstOutputFormat->SelectedIndex = 0;
						 } else {
							 lstOutputFormat->SelectedIndex = index;
						 }
					 } else {
						 lstOutputFormat->SelectedIndex = 0;
					 }
				 }
				 else
					 disableTxtOutputFormat();
				 tsSaveOutputFormat->Visible = false;
			 }

			 void onLeaveStepOutputFormats() {

			 }

			 void refreshOutputFormatList() {
				 lstOutputFormat->BeginUpdate();
				 LockWindowUpdate((HWND) (int) lstOutputFormat->Handle);

				 if(mRuleset) {
					 vector<OutputFormat*> outputFormatVector = mRuleset->getOutputFormats();

					 lstOutputFormat->Items->Clear();				
					 for(unsigned int i=0; i<outputFormatVector.size(); i++) {
						 ListBoxItem^ lbi = gcnew ListBoxItem();
						 lbi->Text = toClrString(outputFormatVector[i]->getFormat());
						 lbi->Tag = gcnew _PairStringInt(lbi->Text, outputFormatVector[i]->getRowId());
						 lstOutputFormat->Items->Add(lbi);
					 }
				 }

				 lstOutputFormat->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }

#pragma endregion
#pragma region Event Handlers



	private: System::Void tsAddOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {			 
			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(mCustomStrings->GetString(L"Strings.NewOutputFormat")));
			 refreshOutputFormatList();
			 if(lstOutputFormat->Items->Count == 1) {
				 lstOutputFormat->SelectedIndex = 0;
			 }
		 }
	private: System::Void tsDeleteOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 
			 mRuleset->removeOutputFormat(rowid);
			 refreshOutputFormatList();
			 refreshMaxStep();

			 mOutputFormatID = 0;

			 if(lstOutputFormat->Items->Count == 0)
				 disableTxtOutputFormat();
		 }
	private: System::Void tsDuplicateOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(lstOutputFormat->SelectedItem->ToString()));
			 refreshOutputFormatList();
		 }
	private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1) 
				 return ;
			 tsSaveOutputFormat->Visible = true;
			 

			 int cursorPosition = txtOutputFormat->SelectionStart;

			 txtOutputFormat->Select(0, txtOutputFormat->Text->Length);
			 txtOutputFormat->SelectionColor = Color::Black;

			 int start = -1;
			 for(int i=0; i<txtOutputFormat->Text->Length; i++) {
				 if(txtOutputFormat->Text[i] == L'$') {
					if(start == -1)
						 start = i;
					else {
						txtOutputFormat->Select(start, i - start + 1);
						txtOutputFormat->SelectionColor = Color::Red;
						start = -1;
					}
				 }
			 }
			 txtOutputFormat->Select(cursorPosition,0);
		 }
	private: System::Void txtOutputFormat_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Return && tsSaveOutputFormat->Visible) {
					tsSaveOutputFormat_Click(nullptr, nullptr);
			 }
		 }
	private: System::Void tsSaveOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(rowid);

			 outputFormat.setFormat(toStlString(txtOutputFormat->Text));

			 int selectedIndex = lstOutputFormat->SelectedIndex;
			 refreshOutputFormatList();
			 lstOutputFormat->SelectedIndex = selectedIndex;
			 tsSaveOutputFormat->Visible = false;

			 mRuleset->save();
		 }
	private: System::Void lstOutputFormat_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstOutputFormat->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;
			 txtOutputFormat->Enabled = true;
			 txtOutputFormat->Text = properties->key;
			 mOutputFormatID = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 tsSaveOutputFormat->Visible = false;

			 txtOutputFormat_TextChanged(nullptr, nullptr);
			 refreshMaxStep();
		 }

private: System::Void tsUseAsNewOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			if(fileList->SelectedItems->Count != 1) return ;

			 String^ selectedFilename = fileList->SelectedItems[0]->Text;

			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(selectedFilename));
			 refreshOutputFormatList();

			 lstOutputFormat->SelectedIndex = lstOutputFormat->Items->Count - 1;
			 txtOutputFormat->Focus();
		 }

		 private: String^ escapeRegularExpression(String^ regularExpression, bool unescape) {
			 String^ string = String::Copy(regularExpression);

			 const int escapeCount = 10;

			 cli::array<String^>^ toEscape = gcnew cli::array<String^>(escapeCount);

			 toEscape[0] = L"("; toEscape[1] = L")";
			 toEscape[2] = L"["; toEscape[3] = L"]";
			 toEscape[4] = L"{"; toEscape[5] = L"}";

			 toEscape[6] = L".";
			 toEscape[7] = L"|";
			 toEscape[8] = L"^";
			 toEscape[9] = L"$";
	
			 for(int i=0; i<escapeCount; i++) {
				 if(unescape == false) {
					string = string->Replace(toEscape[i], "\\" + toEscape[i]);
				 } else {
					string = string->Replace("\\" + toEscape[i], toEscape[i]);
				 }
			 }

			 return string;
		 }
#pragma endregion
