#pragma once
#include <vcclr.h>
#include "ruleset.h"
#include "Renamer.h"
#include "Utility.h"

extern Ruleset* rule;

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Zusammenfassung für Form1
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie auch
	///          die Ressourcendateiname-Eigenschaft für das Tool zur Kompilierung verwalteter Ressourcen ändern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abhängt.
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class ApplicationForm : public System::Windows::Forms::Form
	{
	public:
		ApplicationForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
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

	public: bool codeRunning;
	public: Renamer^ renamer;
	public: System::Windows::Forms::ComboBox^  cboSets;
	public: System::Windows::Forms::Button^  btnNewSet;
	protected: 

	protected: 

	private: System::Windows::Forms::Label^  label1;
	public: System::Windows::Forms::TextBox^  txtOutputFormat;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;





	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  löschenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;





	public: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	public: System::Windows::Forms::TextBox^  txtNewInput;

	public: System::Windows::Forms::Button^  cmdAddInput;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	public: System::Windows::Forms::Button^  cmdSearchFiles;

	public: System::Windows::Forms::ListView^  lstInputRules;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	public: System::Windows::Forms::ListView^  lstFiles;
	public: 
	public: 






	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
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
			this->löschenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lstInputRules = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->txtNewInput = (gcnew System::Windows::Forms::TextBox());
			this->cmdAddInput = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lstFiles = (gcnew System::Windows::Forms::ListView());
			this->cmdSearchFiles = (gcnew System::Windows::Forms::Button());
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
			this->cboSets->Size = System::Drawing::Size(523, 21);
			this->cboSets->TabIndex = 0;
			this->cboSets->SelectedIndexChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_SelectedIndexChanged);
			this->cboSets->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_TextChanged);
			// 
			// btnNewSet
			// 
			this->btnNewSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnNewSet->Location = System::Drawing::Point(597, 10);
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
			this->txtOutputFormat->Size = System::Drawing::Size(576, 20);
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
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->löschenToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(129, 48);
			// 
			// löschenToolStripMenuItem
			// 
			this->löschenToolStripMenuItem->Name = L"löschenToolStripMenuItem";
			this->löschenToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->löschenToolStripMenuItem->Text = L"Löschen";
			this->löschenToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::löschenToolStripMenuItem_Click);
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
			this->splitContainer1->Size = System::Drawing::Size(583, 375);
			this->splitContainer1->SplitterDistance = 273;
			this->splitContainer1->TabIndex = 7;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->lstInputRules);
			this->groupBox1->Controls->Add(this->txtNewInput);
			this->groupBox1->Controls->Add(this->cmdAddInput);
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 367);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Reguläre Ausdrücke";
			// 
			// lstInputRules
			// 
			this->lstInputRules->AutoArrange = false;
			this->lstInputRules->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->columnHeader1});
			this->lstInputRules->ContextMenuStrip = this->contextMenuStrip1;
			this->lstInputRules->Location = System::Drawing::Point(7, 19);
			this->lstInputRules->Name = L"lstInputRules";
			this->lstInputRules->Size = System::Drawing::Size(252, 311);
			this->lstInputRules->TabIndex = 3;
			this->lstInputRules->UseCompatibleStateImageBehavior = false;
			this->lstInputRules->View = System::Windows::Forms::View::List;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"InputRules";
			// 
			// txtNewInput
			// 
			this->txtNewInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtNewInput->Location = System::Drawing::Point(6, 338);
			this->txtNewInput->Name = L"txtNewInput";
			this->txtNewInput->Size = System::Drawing::Size(204, 20);
			this->txtNewInput->TabIndex = 2;
			// 
			// cmdAddInput
			// 
			this->cmdAddInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddInput->Location = System::Drawing::Point(216, 336);
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
			this->groupBox2->Controls->Add(this->lstFiles);
			this->groupBox2->Controls->Add(this->cmdSearchFiles);
			this->groupBox2->Location = System::Drawing::Point(3, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(300, 372);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Dateien";
			// 
			// lstFiles
			// 
			this->lstFiles->AllowDrop = true;
			this->lstFiles->Location = System::Drawing::Point(6, 19);
			this->lstFiles->Name = L"lstFiles";
			this->lstFiles->Size = System::Drawing::Size(288, 311);
			this->lstFiles->TabIndex = 2;
			this->lstFiles->UseCompatibleStateImageBehavior = false;
			this->lstFiles->View = System::Windows::Forms::View::List;
			this->lstFiles->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &ApplicationForm::lstFiles_DragEnter);
			this->lstFiles->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &ApplicationForm::lstFiles_DragDrop);
			this->lstFiles->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &ApplicationForm::lstFiles_DragOver);
			this->lstFiles->DragLeave += gcnew System::EventHandler(this, &ApplicationForm::lstFiles_DragLeave);
			// 
			// cmdSearchFiles
			// 
			this->cmdSearchFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdSearchFiles->Location = System::Drawing::Point(219, 336);
			this->cmdSearchFiles->Name = L"cmdSearchFiles";
			this->cmdSearchFiles->Size = System::Drawing::Size(75, 23);
			this->cmdSearchFiles->TabIndex = 1;
			this->cmdSearchFiles->Text = L"suchen";
			this->cmdSearchFiles->UseVisualStyleBackColor = true;
			this->cmdSearchFiles->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdSearchFiles_Click);
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(655, 449);
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

	private: System::Void ApplicationForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
		 boost::filesystem::path::default_name_check(boost::filesystem::native);

		 rule = NULL;
		 codeRunning = false;
		 renamer->refreshSetList();
	}
	private: System::Void btnNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
		/* if(cboSets->Text == "")
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
		 onUpdateGuiForNewSet();*/

		 renamer->refreshSetList();
	}
private: System::Void cboSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(codeRunning) return ;
			 codeRunning = true;
			 renamer->onSetSelection();
			 codeRunning = false;
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				rule->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }
		 }
private: System::Void cboSets_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void cmdAddInput_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				 rule->addInputRule(toStdString(txtNewInput->Text));
				 txtNewInput->Text = "";
				 renamer->refreshInputsList();
			 }
			 //lstInputs->Items->Add(txtNewInput->Text);
		 }
private: System::Void bearbeitenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			// lstInputs->Items->SelectedItem->Font->Bold;
		 }
private: System::Void bearbeitenToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void löschenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 for(int i=0; i < lstInputRules->SelectedItems->Count; i++)
				 lstInputRules->Items->Remove(lstInputRules->SelectedItems[i]);

			 //if(lstInputs->SelectedIndex != -1)
		 }
private: System::Void cmdSearchFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 dlgAddFiles->ShowDialog();
		 }
private: System::Void dlgAddFiles_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 for(int i=0; i<dlgAddFiles->FileNames->Length; i++) {
				 ListViewItem^ item = gcnew ListViewItem(dlgAddFiles->FileNames[i]);
				 lstFiles->Items->Add(item);
			 }	
		 }
private: System::Void lstFiles_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			/*array<String^>^ formats =  e->Data->GetFormats() ;*/

			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 //! files were droped on this control
  			    array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData( "FileNameW" ));
				for(int i=0; i<files->Length; i++)
					renamer->addFile(files[i]);	
			 }
		 }
private: System::Void lstFiles_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		 }
private: System::Void lstFiles_DragLeave(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lstFiles_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 e->Effect = DragDropEffects::Link;
				 return;
			 }
			 e->Effect = DragDropEffects::None;
		 }
};
}