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
			 

			void loadGems() {
				 if(mOutputFormatID == 0 || mInputRuleID == 0)
					 return ; // can't do anything in this case ...

				 LockWindowUpdate((HWND) (int) gridGems->Handle);

				 gridGems->Rows->Clear();
				 GemColumnGem->Items->Clear();

				 // add empty item to the ComboBox column
				 GemColumnGem->Items->Add("");

				 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 
				 vector<std::string> neededGems = outputFormat.parse(outputFormat.getFormat());
				 vector<Gem*> currentGems = inputRule.getGems();

				 // add entries to the combobox
				 for(unsigned i=0; i<neededGems.size(); i++) {
					 GemColumnGem->Items->Add(toClrString(neededGems[i]));
				 }

				 // add the rows to the grid
				 for(unsigned i=0; i < currentGems.size(); i++) {
					 cli::array<Object^>^ values = gcnew cli::array<Object^>(2);
					 values[0] = gcnew Int32(currentGems[i]->getPosition());
					 values[1] = gcnew String(toClrString(currentGems[i]->getName()));

					 gridGems->Rows->Add(values);
				 }

				 LockWindowUpdate((HWND) 0);
			 }

			 void saveGems() {
				 //! \todo: validate that gems are correctly configured by the user
				 if(mInputRuleID == 0)
					 return ;

				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 vector<Gem*> gems = inputRule.getGems();

				 for(int i=0; i<gridGems->Rows->Count; i++) {
					 DataGridViewRow^ row = gridGems->Rows[i];
					 Int32^ position = (Int32^) row->Cells[0]->Value;
					 string gemName = toStlString((String^) row->Cells[1]->Value);

					 Gem* gem = inputRule.getGemByPosition((int) position);
					 assert(gem != NULL);
					 if(gem) {
						 gem->setName(gemName);
					 }
				 }
			 }

			 void onEnterStepGems() {
/*applyChanges(Step::GEMS_SELECT);
				 loadGems();
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 txtGemInputRule->Text = toClrString(inputRule.getRegex());
				 }

				 gridGems_SelectionChanged(nullptr, nullptr);
				 */
			 }

			 void onLeaveStepGems() {
				 saveGems();
			 }
private: System::Void gridGems_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {
				DataGridViewRow^ row;
				
				if(gridGems->SelectedRows->Count == 1 ) 
					row = gridGems->SelectedRows[0]; // MultiLine = false; so only one Row can be selected
				else if(gridGems->SelectedCells->Count == 1) 
					row = gridGems->Rows[gridGems->SelectedCells[0]->RowIndex];
				else
					return ;

				Int32^ position = (Int32^) row->Cells[0]->Value;

				InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				boost::regex regularExpression(inputRule.getRegex());


				// reset text (needed?)
				txtGemInputRule->Text = toClrString(inputRule.getRegex());

				// reset style
				txtGemInputRule->Select(0, txtGemInputRule->Text->Length);
				txtGemInputRule->SelectionFont = gcnew System::Drawing::Font(
					txtGemInputRule->Font->FontFamily->Name, txtGemInputRule->Font->Size, FontStyle::Regular );


				int start = -1;
				int match = 0;
				for(int i=0; i<txtGemInputRule->Text->Length; i++ ) {
					if(start == -1) {
						if(txtGemInputRule->Text[i] == L'(') {
							if( i == 0 || txtGemInputRule->Text[i-1] != L'\\' || 
								(i >= 1 && txtGemInputRule->Text[i-1] == L'\\' && (i < 2 || txtGemInputRule->Text[i-2] == L'\\')) ) { 
									start = i;
							}
						}
					}

					else {
						if(txtGemInputRule->Text[i] == L')') {
							if( txtGemInputRule->Text[i-1] != L'\\' || 
								(i >= 1 && txtGemInputRule->Text[i-1] == L'\\' && (i < 2 || txtGemInputRule->Text[i-2] == L'\\')) ) { 
									match ++;

									if(match == (int) position) {
										txtGemInputRule->Select(start, i - start + 1);
										txtGemInputRule->SelectionFont = gcnew System::Drawing::Font(
											txtGemInputRule->Font->FontFamily->Name, txtGemInputRule->Font->Size, FontStyle::Bold );
									}

									start = -1;
							}
						}
					}
				}
			}
