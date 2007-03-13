#pragma once
#include <vcclr.h>
#include "ruleset.h"
extern Ruleset* rule;

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung f�r Form1
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse �ndern, m�ssen Sie auch
	///          die Ressourcendateiname-Eigenschaft f�r das Tool zur Kompilierung verwalteter Ressourcen �ndern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abh�ngt.
	///          Anderenfalls k�nnen die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class ApplicationForm : public System::Windows::Forms::Form
	{
	public:
		ApplicationForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzuf�gen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~ApplicationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cboSets;
	private: System::Windows::Forms::Button^  btnNewSet;
	protected: 

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtOutputFormat;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;





	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  l�schenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;





	private: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  txtNewInput;
	private: System::Windows::Forms::ListBox^  lstInputs;
	private: System::Windows::Forms::Button^  cmdAddInput;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  cmdSearchFiles;
	private: System::Windows::Forms::ListBox^  lstFiles;





	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->cboSets = (gcnew System::Windows::Forms::ComboBox());
			this->btnNewSet = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->l�schenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtNewInput = (gcnew System::Windows::Forms::TextBox());
			this->lstInputs = (gcnew System::Windows::Forms::ListBox());
			this->cmdAddInput = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->cmdSearchFiles = (gcnew System::Windows::Forms::Button());
			this->lstFiles = (gcnew System::Windows::Forms::ListBox());
			this->contextMenuStrip1->SuspendLayout();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// cboSets
			// 
			this->cboSets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboSets->FormattingEnabled = true;
			this->cboSets->Location = System::Drawing::Point(68, 12);
			this->cboSets->Name = L"cboSets";
			this->cboSets->Size = System::Drawing::Size(491, 21);
			this->cboSets->TabIndex = 0;
			this->cboSets->SelectedIndexChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_SelectedIndexChanged);
			this->cboSets->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_TextChanged);
			// 
			// btnNewSet
			// 
			this->btnNewSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnNewSet->Location = System::Drawing::Point(565, 10);
			this->btnNewSet->Name = L"btnNewSet";
			this->btnNewSet->Size = System::Drawing::Size(47, 23);
			this->btnNewSet->TabIndex = 1;
			this->btnNewSet->Text = L"neu";
			this->btnNewSet->UseVisualStyleBackColor = true;
			this->btnNewSet->Click += gcnew System::EventHandler(this, &ApplicationForm::btnNewSet_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(38, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(23, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Set";
			// 
			// txtOutputFormat
			// 
			this->txtOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFormat->Location = System::Drawing::Point(68, 41);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(544, 20);
			this->txtOutputFormat->TabIndex = 3;
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::txtOutputFormat_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Ausgabe";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->l�schenToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(129, 48);
			// 
			// l�schenToolStripMenuItem
			// 
			this->l�schenToolStripMenuItem->Name = L"l�schenToolStripMenuItem";
			this->l�schenToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->l�schenToolStripMenuItem->Text = L"L�schen";
			this->l�schenToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::l�schenToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->bearbeitenToolStripMenuItem->Text = L"Bearbeiten";
			this->bearbeitenToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::bearbeitenToolStripMenuItem_Click_1);
			// 
			// dlgAddFiles
			// 
			this->dlgAddFiles->FileName = L"*.*";
			this->dlgAddFiles->Multiselect = true;
			this->dlgAddFiles->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::dlgAddFiles_FileOk);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->Location = System::Drawing::Point(59, 67);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->groupBox1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->groupBox2);
			this->splitContainer1->Size = System::Drawing::Size(551, 301);
			this->splitContainer1->SplitterDistance = 183;
			this->splitContainer1->TabIndex = 7;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->txtNewInput);
			this->groupBox1->Controls->Add(this->lstInputs);
			this->groupBox1->Controls->Add(this->cmdAddInput);
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(177, 293);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Regul�re Ausdr�cke";
			// 
			// txtNewInput
			// 
			this->txtNewInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtNewInput->Location = System::Drawing::Point(6, 264);
			this->txtNewInput->Name = L"txtNewInput";
			this->txtNewInput->Size = System::Drawing::Size(114, 20);
			this->txtNewInput->TabIndex = 2;
			// 
			// lstInputs
			// 
			this->lstInputs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstInputs->ContextMenuStrip = this->contextMenuStrip1;
			this->lstInputs->FormattingEnabled = true;
			this->lstInputs->Location = System::Drawing::Point(6, 19);
			this->lstInputs->Name = L"lstInputs";
			this->lstInputs->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->lstInputs->Size = System::Drawing::Size(163, 238);
			this->lstInputs->TabIndex = 1;
			// 
			// cmdAddInput
			// 
			this->cmdAddInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddInput->Location = System::Drawing::Point(126, 262);
			this->cmdAddInput->Name = L"cmdAddInput";
			this->cmdAddInput->Size = System::Drawing::Size(45, 23);
			this->cmdAddInput->TabIndex = 0;
			this->cmdAddInput->Text = L"neu";
			this->cmdAddInput->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->cmdSearchFiles);
			this->groupBox2->Controls->Add(this->lstFiles);
			this->groupBox2->Location = System::Drawing::Point(3, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(358, 298);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Dateien";
			// 
			// cmdSearchFiles
			// 
			this->cmdSearchFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdSearchFiles->Location = System::Drawing::Point(277, 262);
			this->cmdSearchFiles->Name = L"cmdSearchFiles";
			this->cmdSearchFiles->Size = System::Drawing::Size(75, 23);
			this->cmdSearchFiles->TabIndex = 1;
			this->cmdSearchFiles->Text = L"suchen";
			this->cmdSearchFiles->UseVisualStyleBackColor = true;
			// 
			// lstFiles
			// 
			this->lstFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstFiles->FormattingEnabled = true;
			this->lstFiles->Location = System::Drawing::Point(9, 19);
			this->lstFiles->Name = L"lstFiles";
			this->lstFiles->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->lstFiles->Size = System::Drawing::Size(343, 238);
			this->lstFiles->TabIndex = 0;
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(623, 375);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtOutputFormat);
			this->Controls->Add(this->cboSets);
			this->Controls->Add(this->btnNewSet);
			this->Name = L"ApplicationForm";
			this->Opacity = 0.95;
			this->Text = L"Renamer Pre-Alpha";
			this->Load += gcnew System::EventHandler(this, &ApplicationForm::ApplicationForm_Load);
			this->contextMenuStrip1->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void onSetSelection() {
				 if(rule)
					 delete rule;
				 string setName = toStdString(cboSets->Text);
				 rule = new Ruleset(setName);
				 //refreshSetList();
				 onUpdateGuiForNewSet();
			 }

	 private: void onUpdateGuiForNewSet() {
				  // update gui elements to this new set
				  refreshInputsList();
				  //refreshSetList();

				  txtOutputFormat->Text = toClrString( rule ? rule->getOutputFormat() : "");
				  cboSets->Text = toClrString( rule ? rule->getName() : "");
			  }

	 private: bool To_string( String^ source, string &target )
	 {
		 pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		 int len = (( source->Length+1) * 2);
		 char *ch = new char[ len ];
		 bool result = wcstombs( ch, wch, len ) != -1;
		 target = ch;
		 delete ch;
		 return result;
	 }

	private: bool To_CharStar( String^ source, char*& target )
	{
		pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		int len = (( source->Length+1) * 2);
		target = new char[ len ];
		return wcstombs( target, wch, len ) != -1;
	}

	private: string toStdString(String^source) {
				string target;
				To_string(source, target);
				return target;
			 }
	 private: String^ toClrString( string source )
	 {
		 String^ target = gcnew String( source.c_str() );
		return target;
	 }


	private: void refreshInputsList() {
				 lstInputs->Items->Clear();
				 vector<string> regExes;
				 if(rule) 
					 rule->fetchInputRules(regExes);

				 for(unsigned int i=0; i<regExes.size(); i++) {
					 lstInputs->Items->Add(toClrString(regExes[i]));
				 }
			 }

	private: void refreshSetList() {
				 cboSets->Items->Clear();

				 using namespace System::IO;
				 array<String^>^fileNames = Directory::GetFiles( ".\\", "*.db3" );

				 for(int i=0; i<fileNames->Length; i++) {
					 String^ fileName = fileNames[i]->Substring(2);
					 String^ setName = fileName->Substring(0, fileName->Length-4);
					 cboSets->Items->Add(setName);
				 }
			 }

	private: System::Void ApplicationForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
		 boost::filesystem::path::default_name_check(boost::filesystem::native);

		 rule = NULL;
		 refreshSetList();
	}
	private: System::Void btnNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
		 if(cboSets->Text == "")
			 return ;
				 
		 if(rule) {
			delete rule;
			rule = NULL;
			cboSets->Text = "";
		 }
		 else
		 {
			rule = new Ruleset(toStdString(cboSets->Text));
		 }
		 onUpdateGuiForNewSet();
	}
private: System::Void cboSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 onSetSelection();
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				rule->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }
		 }
private: System::Void cboSets_TextChanged(System::Object^  sender, System::EventArgs^  e) {
/*
			 if(rule) {
				string setName = rule->getName();
				delete rule;
				System::IO::File::Move(toClrString(setName), cboSets->Text);
				rule = new Ruleset(toStdString(cboSets->Text));
			 }

			 else {
				rule = new Ruleset(toStdString(cboSets->Text));
			 }*/
		 }
private: System::Void cmdAddInput_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				 rule->addInputRule(toStdString(txtNewInput->Text));
				 txtNewInput->Text = "";
				 refreshInputsList();
			 }
			 //lstInputs->Items->Add(txtNewInput->Text);
		 }
private: System::Void bearbeitenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			// lstInputs->Items->SelectedItem->Font->Bold;
		 }
private: System::Void lstInputs_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 
		 }
private: System::Void bearbeitenToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void l�schenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 lstInputs->Items->RemoveAt(lstInputs->SelectedIndex);
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 dlgAddFiles->ShowDialog();
		 }
private: System::Void dlgAddFiles_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 for(int i=0; i<dlgAddFiles->FileNames->Length; i++) {
				 lstFiles->Items->Add(dlgAddFiles->FileNames[i]);
			 }
		 }
};
}

