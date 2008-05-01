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


void onEnterStepRename() {
//			 applyChanges(Step::RENAME);
		 }

		 void onLeaveStepRename() {

		 }
private: System::Void buttonRenameFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 for(int i=fileList->Items->Count -1; i>=0 ; i--) {
				 ListViewItem^ item = fileList->Items[i];
				 String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];


				 String^ originalDirectory = IO::Path::GetDirectoryName(originalFilenameWithPath);
				 String^ originalExtension = IO::Path::GetExtension(originalFilenameWithPath);

				 String^ filenameWithBeforeReplacementsAndWithoutDirectoryAndWithoutExtension = item->Text;

				 string resultingFilename;

				 if(mRuleset->applyTo(toStlString(filenameWithBeforeReplacementsAndWithoutDirectoryAndWithoutExtension), resultingFilename)) {
					 String^ finalFilenameWithPath = originalDirectory + L"\\" + toClrString(resultingFilename) + originalExtension;
					 File::Move(originalFilenameWithPath, finalFilenameWithPath);
					 mFiles.RemoveAt((int) (Int32^)item->Tag);
				 }

				 applyChanges(mStep);
			 }
		 }

