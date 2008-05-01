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

