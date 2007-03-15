#pragma region Header
#pragma once
#include <vcclr.h>
#include "ruleset.h"
#include "inputRule.h"
#include "Utility.h"

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
#pragma endregion
#pragma region Form Declaration
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
#pragma endregion
#pragma region Form Attributes
	// Attribute 
	private: bool codeRunning;
	private: Ruleset* rule;

	private: bool setEditMode;

    // Form Controls
	private: System::Windows::Forms::ComboBox^  cboSets;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtOutputFormat;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;
	private: System::Windows::Forms::ContextMenuStrip^  cmsInputRules;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteInputRule;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiEditInputRule;

	private: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  txtNewInput;
	private: System::Windows::Forms::Button^  cmdAddInputRule;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  cmdAddFiles;

	private: System::Windows::Forms::ListView^  lstInputRules;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ListView^  lstFiles;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  neuesSetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  umbenennneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  löschenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSplitButton^  cmdNewSet;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmiNewSet;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiRenameSet;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteSet;
	private: System::ComponentModel::IContainer^  components;
#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ApplicationForm::typeid));
			this->cboSets = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->cmsInputRules = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiDeleteInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiEditInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lstInputRules = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->txtNewInput = (gcnew System::Windows::Forms::TextBox());
			this->cmdAddInputRule = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lstFiles = (gcnew System::Windows::Forms::ListView());
			this->cmdAddFiles = (gcnew System::Windows::Forms::Button());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->neuesSetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->umbenennneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->löschenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmdNewSet = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->tsmiNewSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiRenameSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiDeleteSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmsInputRules->SuspendLayout();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// cboSets
			// 
			this->cboSets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboSets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboSets->FormattingEnabled = true;
			this->cboSets->Location = System::Drawing::Point(67, 14);
			this->cboSets->Name = L"cboSets";
			this->cboSets->Size = System::Drawing::Size(523, 21);
			this->cboSets->TabIndex = 0;
			this->cboSets->SelectedIndexChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_SelectedIndexChanged);
			this->cboSets->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_TextChanged);
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
			// cmsInputRules
			// 
			this->cmsInputRules->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmiDeleteInputRule, 
				this->tsmiEditInputRule});
			this->cmsInputRules->Name = L"contextMenuStrip1";
			this->cmsInputRules->Size = System::Drawing::Size(129, 48);
			// 
			// tsmiDeleteInputRule
			// 
			this->tsmiDeleteInputRule->Name = L"tsmiDeleteInputRule";
			this->tsmiDeleteInputRule->Size = System::Drawing::Size(128, 22);
			this->tsmiDeleteInputRule->Text = L"Löschen";
			this->tsmiDeleteInputRule->Click += gcnew System::EventHandler(this, &ApplicationForm::löschenToolStripMenuItem_Click);
			// 
			// tsmiEditInputRule
			// 
			this->tsmiEditInputRule->Name = L"tsmiEditInputRule";
			this->tsmiEditInputRule->Size = System::Drawing::Size(128, 22);
			this->tsmiEditInputRule->Text = L"Bearbeiten";
			this->tsmiEditInputRule->Click += gcnew System::EventHandler(this, &ApplicationForm::bearbeitenToolStripMenuItem_Click_1);
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
			this->groupBox1->Controls->Add(this->cmdAddInputRule);
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 367);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Reguläre Ausdrücke";
			// 
			// lstInputRules
			// 
			this->lstInputRules->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstInputRules->AutoArrange = false;
			this->lstInputRules->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->columnHeader1});
			this->lstInputRules->ContextMenuStrip = this->cmsInputRules;
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
			// cmdAddInputRule
			// 
			this->cmdAddInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddInputRule->Location = System::Drawing::Point(216, 336);
			this->cmdAddInputRule->Name = L"cmdAddInputRule";
			this->cmdAddInputRule->Size = System::Drawing::Size(45, 23);
			this->cmdAddInputRule->TabIndex = 0;
			this->cmdAddInputRule->Text = L"neu";
			this->cmdAddInputRule->UseVisualStyleBackColor = true;
			this->cmdAddInputRule->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdAddInputRule_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->lstFiles);
			this->groupBox2->Controls->Add(this->cmdAddFiles);
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
			this->lstFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
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
			// cmdAddFiles
			// 
			this->cmdAddFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddFiles->Location = System::Drawing::Point(219, 336);
			this->cmdAddFiles->Name = L"cmdAddFiles";
			this->cmdAddFiles->Size = System::Drawing::Size(75, 23);
			this->cmdAddFiles->TabIndex = 1;
			this->cmdAddFiles->Text = L"suchen";
			this->cmdAddFiles->UseVisualStyleBackColor = true;
			this->cmdAddFiles->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdSearchFiles_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripSplitButton1, 
				this->cmdNewSet});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Flow;
			this->toolStrip1->Location = System::Drawing::Point(596, 12);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(80, 23);
			this->toolStrip1->TabIndex = 8;
			this->toolStrip1->TabStop = true;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripSplitButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->neuesSetToolStripMenuItem, 
				this->umbenennneToolStripMenuItem, this->löschenToolStripMenuItem});
			this->toolStripSplitButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->Size = System::Drawing::Size(16, 4);
			this->toolStripSplitButton1->Text = L"toolStripSplitButton1";
			// 
			// neuesSetToolStripMenuItem
			// 
			this->neuesSetToolStripMenuItem->Name = L"neuesSetToolStripMenuItem";
			this->neuesSetToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->neuesSetToolStripMenuItem->Text = L"Neues Set";
			// 
			// umbenennneToolStripMenuItem
			// 
			this->umbenennneToolStripMenuItem->Name = L"umbenennneToolStripMenuItem";
			this->umbenennneToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->umbenennneToolStripMenuItem->Text = L"Umbenennne";
			// 
			// löschenToolStripMenuItem
			// 
			this->löschenToolStripMenuItem->Name = L"löschenToolStripMenuItem";
			this->löschenToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->löschenToolStripMenuItem->Text = L"Löschen";
			// 
			// cmdNewSet
			// 
			this->cmdNewSet->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdNewSet->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsmiNewSet, 
				this->tsmiRenameSet, this->tsmiDeleteSet});
			this->cmdNewSet->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cmdNewSet.Image")));
			this->cmdNewSet->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdNewSet->Name = L"cmdNewSet";
			this->cmdNewSet->Size = System::Drawing::Size(32, 20);
			this->cmdNewSet->Text = L"toolStripSplitButton2";
			this->cmdNewSet->ButtonClick += gcnew System::EventHandler(this, &ApplicationForm::toolStripSplitButton2_ButtonClick);
			// 
			// tsmiNewSet
			// 
			this->tsmiNewSet->Name = L"tsmiNewSet";
			this->tsmiNewSet->Size = System::Drawing::Size(152, 22);
			this->tsmiNewSet->Text = L"Neu";
			this->tsmiNewSet->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiNewSet_Click);
			// 
			// tsmiRenameSet
			// 
			this->tsmiRenameSet->Name = L"tsmiRenameSet";
			this->tsmiRenameSet->Size = System::Drawing::Size(152, 22);
			this->tsmiRenameSet->Text = L"Bearbeiten";
			// 
			// tsmiDeleteSet
			// 
			this->tsmiDeleteSet->Name = L"tsmiDeleteSet";
			this->tsmiDeleteSet->Size = System::Drawing::Size(152, 22);
			this->tsmiDeleteSet->Text = L"Löschen";
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(655, 449);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtOutputFormat);
			this->Controls->Add(this->cboSets);
			this->Name = L"ApplicationForm";
			this->Opacity = 0.95;
			this->Text = L"Renamer Pre-Alpha";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ApplicationForm::ApplicationForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ApplicationForm::ApplicationForm_Load);
			this->cmsInputRules->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Renamer Business Logic
		void addInputRule(String^ regexp) 
		{
			rule->addInputRule(toStdString(regexp));
			txtNewInput->Text = "";
			refreshInputRulesList();
		}

		void setSetEditMode(bool val) {
			setEditMode = val;
			cboSets->DropDownStyle = setEditMode ? ComboBoxStyle::DropDown : ComboBoxStyle::DropDownList;

			if(setEditMode) {
				String^ text = cboSets->Text;
				cboSets->Items->Clear();
				cboSets->Text = text;
			} else {
				refreshSetList();
			}
		}

		void removeInputRule(long long inputRuleID) {
			//! \todo implement
		}

		void loadOrCreateSet(String^ setName) 
		{
			if(rule)
				delete rule;
			rule = new Ruleset(toStdString(setName));

			Text = "Renamer - " + setName;
		}

		void renameSet(String^ oldSetName, String^ newSetName) {
			if(rule) {
				string setName = rule->getName();
				if(setName == toStdString(oldSetName)) {
					delete rule;
					File::Move(oldSetName + ".db3", newSetName + ".db3");
					rule = new Ruleset(toStdString(newSetName));
				}
			}

			else {
				File::Move(oldSetName + ".db3", newSetName + ".db3");
			}
		}

		void removeSet(String^ setName) {

		}

		void addFile( String^ pathToFile )
		{
			String^ fileName = System::IO::Path::GetFileNameWithoutExtension(pathToFile);
			ListViewItem^ item = gcnew ListViewItem(fileName);
			item->Tag = pathToFile;
			lstFiles->Items->Add(item);
		}

		void onSetSelection() 
		{
			loadOrCreateSet(cboSets->Text);
			refreshSetList();
			refreshInputRulesList();

			txtOutputFormat->Text = toClrString( rule ? rule->getOutputFormat() : "");
			cboSets->Text = toClrString( rule ? rule->getName() : "");
		}

		void refreshInputRulesList() 
		{
			assert(rule != NULL);
			if(rule == NULL) return ;

			lstInputRules->Items->Clear();

			vector<InputRule> inputRules = rule->getInputRules();
			for(unsigned int i=0; i<inputRules.size(); i++) {
				String^ text = toClrString(inputRules[i].getRegex());
				ListViewItem^ item = gcnew ListViewItem(text,0);
				lstInputRules->Items->Add(item);
			}
		}

		void refreshSetList() 
		{
			cboSets->Items->Clear();

			using namespace System::IO;
			array<String^>^fileNames = Directory::GetFiles( ".\\", "*.db3" );

			for(int i=0; i<fileNames->Length; i++) {
				String^ fileName = fileNames[i]->Substring(2);
				String^ setName = fileName->Substring(0, fileName->Length-4);
				cboSets->Items->Add(setName);
			}
		}
#pragma endregion
#pragma region Form Handlers

	private: System::Void ApplicationForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 rule = NULL;
		 codeRunning = false;
		 setSetEditMode(false);
		 refreshSetList();

		 if(cboSets->Items->Count == 0) {
			 setSetEditMode(true);
		 }

		 else {
			 String^ lastOpenedSetName = Microsoft::VisualBasic::Interaction::GetSetting("Renamer", "Settings", "last_set", "test");
			 
			 if(lastOpenedSetName == "test") {
				 cboSets->SelectedIndex = 0;
			 }
			 else {
				 cboSets->SelectedIndex = cboSets->FindString(lastOpenedSetName);
			 }
		 }
	}
	
	private: System::Void ApplicationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 Microsoft::VisualBasic::Interaction::SaveSetting("Renamer", "Settings", "last_set47110815", cboSets->Text);
	}

	private: System::Void cmdNewSet_Click(System::Object^  sender, System::EventArgs^  e) {

	}
private: System::Void cboSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(codeRunning) return ;
			 codeRunning = true;
			 onSetSelection();
			 codeRunning = false;
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				rule->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }
		 }
private: System::Void cboSets_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void cmdNewInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				 addInputRule(txtNewInput->Text);
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
#pragma region Drag&Drop Support
private: System::Void lstFiles_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			/*array<String^>^ formats =  e->Data->GetFormats() ;*/

			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 //! files were droped on this control
  			    array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData( "FileNameW" ));
				for(int i=0; i<files->Length; i++)
					addFile(files[i]);	
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
#pragma endregion
private: System::Void cmdAddInputRule_Click(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void toolStripSplitButton2_ButtonClick(System::Object^  sender, System::EventArgs^  e) {
			 tsmiNewSet_Click(sender, e);
		 }
private: System::Void tsmiNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(setEditMode == false) {
				// enable entering a new set name
				setSetEditMode(true);
				cboSets->Text = "";
			 } else {
				 // disable edit mode and create the set
				 String^ setName = cboSets->Text;
				 loadOrCreateSet(setName);
				 setSetEditMode(false);
				 cboSets->SelectedIndex = cboSets->FindString(setName);
				 onSetSelection();
			 }
		 }
};
}
#pragma endregion
