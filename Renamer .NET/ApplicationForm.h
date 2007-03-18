#pragma region Header
#pragma once
#include <vcclr.h>
#include "ruleset.h"
#include "inputRule.h"
#include "clrUtility.h"
#include "stlUtility.h"
#include "stdlib.h"
#include "error.h"

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
	private: Ruleset* ruleSet;
	private: OutputFormat* outputFormat;

	private: bool setEditMode;

    //! set which is currently renamed, if none its empty string
    //! \todo is this really needed because of ruleSet var?
	private: String^ renamingSet; 

	private: static String^ cmdNewSet_DefaultText = L"Neues Set";
	private: static String^ cmdNewSet_SaveText = L"Speichern";

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


	private: System::Windows::Forms::TextBox^  txtNewInput;
	private: System::Windows::Forms::Button^  cmdAddInputRule;

	private: System::Windows::Forms::Button^  cmdAddFiles;
	private: System::Windows::Forms::ListView^  lstInputRules;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ListView^  lstFiles;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripSplitButton^  cmdNewSet;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiNewSet;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiRenameSet;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteSet;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ToolStrip^  toolStrip2;
	private: System::Windows::Forms::ToolStripDropDownButton^  cmdOutputFormat;
	private: System::Windows::Forms::Label^  label3;
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
			System::Windows::Forms::SplitContainer^  splitContainer1;
			System::Windows::Forms::GroupBox^  groupBox1;
			System::Windows::Forms::GroupBox^  groupBox2;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ApplicationForm::typeid));
			this->lstInputRules = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->cmsInputRules = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiDeleteInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiEditInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->txtNewInput = (gcnew System::Windows::Forms::TextBox());
			this->cmdAddInputRule = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lstFiles = (gcnew System::Windows::Forms::ListView());
			this->cmdAddFiles = (gcnew System::Windows::Forms::Button());
			this->cboSets = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->cmdNewSet = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->tsmiNewSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiRenameSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiDeleteSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->cmdOutputFormat = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			splitContainer1->Panel1->SuspendLayout();
			splitContainer1->Panel2->SuspendLayout();
			splitContainer1->SuspendLayout();
			groupBox1->SuspendLayout();
			this->cmsInputRules->SuspendLayout();
			groupBox2->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			splitContainer1->Location = System::Drawing::Point(59, 67);
			splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			splitContainer1->Panel1->Controls->Add(groupBox1);
			// 
			// splitContainer1.Panel2
			// 
			splitContainer1->Panel2->Controls->Add(groupBox2);
			splitContainer1->Size = System::Drawing::Size(583, 260);
			splitContainer1->SplitterDistance = 282;
			splitContainer1->TabIndex = 7;
			// 
			// groupBox1
			// 
			groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			groupBox1->Controls->Add(this->lstInputRules);
			groupBox1->Controls->Add(this->txtNewInput);
			groupBox1->Controls->Add(this->cmdAddInputRule);
			groupBox1->Location = System::Drawing::Point(3, 3);
			groupBox1->Name = L"groupBox1";
			groupBox1->Size = System::Drawing::Size(276, 252);
			groupBox1->TabIndex = 6;
			groupBox1->TabStop = false;
			groupBox1->Text = L"Reguläre Ausdrücke";
			// 
			// lstInputRules
			// 
			this->lstInputRules->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstInputRules->AutoArrange = false;
			this->lstInputRules->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->columnHeader1});
			this->lstInputRules->ContextMenuStrip = this->cmsInputRules;
			this->lstInputRules->FullRowSelect = true;
			this->lstInputRules->Location = System::Drawing::Point(7, 19);
			this->lstInputRules->Name = L"lstInputRules";
			this->lstInputRules->Size = System::Drawing::Size(261, 196);
			this->lstInputRules->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->lstInputRules->TabIndex = 3;
			this->lstInputRules->UseCompatibleStateImageBehavior = false;
			this->lstInputRules->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"InputRules";
			this->columnHeader1->Width = 111;
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
			// txtNewInput
			// 
			this->txtNewInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtNewInput->Location = System::Drawing::Point(7, 223);
			this->txtNewInput->Name = L"txtNewInput";
			this->txtNewInput->Size = System::Drawing::Size(212, 20);
			this->txtNewInput->TabIndex = 2;
			// 
			// cmdAddInputRule
			// 
			this->cmdAddInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddInputRule->Location = System::Drawing::Point(225, 221);
			this->cmdAddInputRule->Name = L"cmdAddInputRule";
			this->cmdAddInputRule->Size = System::Drawing::Size(45, 23);
			this->cmdAddInputRule->TabIndex = 0;
			this->cmdAddInputRule->Text = L"neu";
			this->cmdAddInputRule->UseVisualStyleBackColor = true;
			this->cmdAddInputRule->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdAddInputRule_Click);
			// 
			// groupBox2
			// 
			groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			groupBox2->Controls->Add(this->button1);
			groupBox2->Controls->Add(this->lstFiles);
			groupBox2->Controls->Add(this->cmdAddFiles);
			groupBox2->Location = System::Drawing::Point(3, 3);
			groupBox2->Name = L"groupBox2";
			groupBox2->Size = System::Drawing::Size(291, 257);
			groupBox2->TabIndex = 7;
			groupBox2->TabStop = false;
			groupBox2->Text = L"Dateien";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(6, 336);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"debug";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ApplicationForm::button1_Click);
			// 
			// lstFiles
			// 
			this->lstFiles->AllowDrop = true;
			this->lstFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstFiles->Location = System::Drawing::Point(6, 19);
			this->lstFiles->Name = L"lstFiles";
			this->lstFiles->Size = System::Drawing::Size(277, 196);
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
			this->cmdAddFiles->Location = System::Drawing::Point(210, 221);
			this->cmdAddFiles->Name = L"cmdAddFiles";
			this->cmdAddFiles->Size = System::Drawing::Size(75, 23);
			this->cmdAddFiles->TabIndex = 1;
			this->cmdAddFiles->Text = L"suchen";
			this->cmdAddFiles->UseVisualStyleBackColor = true;
			this->cmdAddFiles->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdSearchFiles_Click);
			// 
			// cboSets
			// 
			this->cboSets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboSets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboSets->FormattingEnabled = true;
			this->cboSets->Location = System::Drawing::Point(69, 14);
			this->cboSets->Name = L"cboSets";
			this->cboSets->Size = System::Drawing::Size(472, 21);
			this->cboSets->TabIndex = 0;
			this->cboSets->SelectedIndexChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_SelectedIndexChanged);
			this->cboSets->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::cboSets_TextChanged);
			this->cboSets->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ApplicationForm::cboSets_KeyDown);
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
			this->txtOutputFormat->Location = System::Drawing::Point(4, 110);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(67, 20);
			this->txtOutputFormat->TabIndex = 3;
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::txtOutputFormat_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(22, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(39, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Format";
			// 
			// dlgAddFiles
			// 
			this->dlgAddFiles->FileName = L"*.*";
			this->dlgAddFiles->Multiselect = true;
			this->dlgAddFiles->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::dlgAddFiles_FileOk);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->cmdNewSet});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Flow;
			this->toolStrip1->Location = System::Drawing::Point(544, 12);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(90, 23);
			this->toolStrip1->TabIndex = 8;
			this->toolStrip1->TabStop = true;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// cmdNewSet
			// 
			this->cmdNewSet->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsmiNewSet, 
				this->tsmiRenameSet, this->tsmiDeleteSet});
			this->cmdNewSet->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cmdNewSet.Image")));
			this->cmdNewSet->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdNewSet->Name = L"cmdNewSet";
			this->cmdNewSet->Size = System::Drawing::Size(89, 20);
			this->cmdNewSet->Text = L"Neues Set";
			this->cmdNewSet->ButtonClick += gcnew System::EventHandler(this, &ApplicationForm::cmdNewSet_ButtonClick);
			// 
			// tsmiNewSet
			// 
			this->tsmiNewSet->Name = L"tsmiNewSet";
			this->tsmiNewSet->Size = System::Drawing::Size(128, 22);
			this->tsmiNewSet->Text = L"Neu";
			this->tsmiNewSet->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiNewSet_Click);
			// 
			// tsmiRenameSet
			// 
			this->tsmiRenameSet->Name = L"tsmiRenameSet";
			this->tsmiRenameSet->Size = System::Drawing::Size(128, 22);
			this->tsmiRenameSet->Text = L"Bearbeiten";
			this->tsmiRenameSet->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiRenameSet_Click);
			// 
			// tsmiDeleteSet
			// 
			this->tsmiDeleteSet->Name = L"tsmiDeleteSet";
			this->tsmiDeleteSet->Size = System::Drawing::Size(128, 22);
			this->tsmiDeleteSet->Text = L"Löschen";
			this->tsmiDeleteSet->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiDeleteSet_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(69, 362);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(564, 96);
			this->richTextBox1->TabIndex = 9;
			this->richTextBox1->Text = L"";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(69, 41);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(472, 21);
			this->comboBox1->TabIndex = 10;
			// 
			// toolStrip2
			// 
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->cmdOutputFormat});
			this->toolStrip2->Location = System::Drawing::Point(544, 39);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(87, 25);
			this->toolStrip2->TabIndex = 11;
			this->toolStrip2->Text = L"toolStrip2";
			// 
			// cmdOutputFormat
			// 
			this->cmdOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cmdOutputFormat.Image")));
			this->cmdOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdOutputFormat->Name = L"cmdOutputFormat";
			this->cmdOutputFormat->Size = System::Drawing::Size(84, 22);
			this->cmdOutputFormat->Text = L"Speichern";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(69, 343);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(77, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"RichTextEditor";
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(655, 519);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->toolStrip2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(splitContainer1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->cboSets);
			this->Controls->Add(this->txtOutputFormat);
			this->Name = L"ApplicationForm";
			this->Opacity = 0.95;
			this->Text = L"Renamer Pre-Alpha";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ApplicationForm::ApplicationForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ApplicationForm::ApplicationForm_Load);
			splitContainer1->Panel1->ResumeLayout(false);
			splitContainer1->Panel2->ResumeLayout(false);
			splitContainer1->ResumeLayout(false);
			groupBox1->ResumeLayout(false);
			groupBox1->PerformLayout();
			this->cmsInputRules->ResumeLayout(false);
			groupBox2->ResumeLayout(false);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->toolStrip2->ResumeLayout(false);
			this->toolStrip2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Renamer Business Logic
		void addInputRule(String^ regexp) 
		{
//			rule->addInputRule(toStdString(regexp));
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
			//rule->removeInputRule(inputRuleID);
		}

		void loadOrCreateSet(String^ setName) 
		{
			exAssert(setName != "");
			if(ruleSet)
				delete ruleSet;
			ruleSet = new Ruleset(toStdWString(setName));

			Text = "Renamer - " + setName;
		}

		void renameSet(String^ oldSetName, String^ newSetName) {
			exAssert(oldSetName != "");
			exAssert(newSetName != "");
			if(ruleSet) {
				string setName = ruleSet->getName();
				if(setName == toStdString(oldSetName)) {
					delete ruleSet;
					File::Move(oldSetName + ".db3", newSetName + ".db3");
					string s = toStdString(newSetName);
					ruleSet = new Ruleset(toStdWString(s));
				} else {
					File::Move(oldSetName + ".db3", newSetName + ".db3");
				}
			}

			else {
				File::Move(oldSetName + ".db3", newSetName + ".db3");
			}
		}

		void deleteSet(String^ setName) {
			if(ruleSet) {
				string ruleSetName = ruleSet->getName();
				if(ruleSetName == toStdString(setName)) {
					delete ruleSet;
					ruleSet = NULL;
				}
			}
			File::Delete(setName + ".db3");
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

//			txtOutputFormat->Text = toClrString( rule ? rule->getOutputFormat() : "");
			//cboSets->Text = toClrString( rule ? rule->getName() : "");
			if(ruleSet)
				selectSet(toClrString(ruleSet->getName()));
		}

		void refreshInputRulesList() 
		{
			assert(ruleSet != NULL);
			if(ruleSet == NULL) return ;

			lstInputRules->Items->Clear();

/*			vector<InputRule> inputRules = ruleSet->getInputRules();
			for(unsigned int i=0; i<inputRules.size(); i++) {
				String^ text = toClrString(inputRules[i].getRegex());
				ListViewItem^ item = gcnew ListViewItem(text,0);
				lstInputRules->Items->Add(item);
			}*/
		}
		
		void selectSet(String^ setName) {
			int i = cboSets->FindString(setName);
			cboSets->SelectedIndex = i;
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
		 ruleSet = NULL;
		 codeRunning = false;
		 renamingSet = "";
		 setSetEditMode(false);
		 refreshSetList();

		 if(cboSets->Items->Count == 0) {
			 tsmiNewSet_Click(sender, e);
		 }

		 else {
			 String^ lastOpenedSetName = Microsoft::VisualBasic::Interaction::GetSetting("Renamer", "Settings", "last_set", "--empty--");
			 
			 if(lastOpenedSetName == "--empty--") {
				 cboSets->SelectedIndex = 0;
			 }
			 else {
				 if(File::Exists(lastOpenedSetName))
					selectSet(lastOpenedSetName);
				 else
					 cboSets->SelectedIndex = 0;
			 }
		 }
	}
	
	private: System::Void ApplicationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 Microsoft::VisualBasic::Interaction::SaveSetting("Renamer", "Settings", "last_set47110815", cboSets->Text);
	}

private: System::Void cboSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(codeRunning) return ;
			 codeRunning = true;
			 onSetSelection();
			 codeRunning = false;
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
/*			 if(ruleSet) {
				ruleSet->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }*/
		 }
private: System::Void cboSets_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void cmdNewInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(ruleSet) {
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
private: System::Void cmdNewSet_ButtonClick(System::Object^  sender, System::EventArgs^  e) {
			 if(renamingSet == "")
				tsmiNewSet_Click(sender, e);
			 else if(setEditMode == true) {
				 // we are finishing renaming a set
				 String^ newSetName = cboSets->Text;
				 renameSet(renamingSet, newSetName);
				 renamingSet = "";
				 //refreshSetList();
				 cmdNewSet->Text = cmdNewSet_DefaultText;
				 //cboSets->Text = newSetName;
				 //exAssert(cboSets->Text == newSetName);
				 setSetEditMode(false);
				 //exAssert(cboSets->Text == newSetName);
				 //onSetSelection();
				 selectSet(newSetName);
			 }
		 }
private: System::Void tsmiNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(setEditMode == false) {
				// enable entering a new set name
				setSetEditMode(true);
				cmdNewSet->Text = cmdNewSet_SaveText;
				cboSets->Text = "";
			 } else {
				 // disable edit mode and create the set
				 cmdNewSet->Text = cmdNewSet_DefaultText;
				 String^ setName = cboSets->Text;
				 setSetEditMode(false);
				 if(setName->Length > 0) {
					 loadOrCreateSet(setName);
					 refreshSetList();
					 selectSet(setName);
					 //cboSets->Text = setName;
					 //onSetSelection();
				 }
			 }
		 }
private: System::Void tsmiRenameSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(cboSets->Items->Count == 0 ||setEditMode == true)
				 return ;
			 renamingSet = cboSets->Text;
			 setSetEditMode(true);
			 cmdNewSet->Text = cmdNewSet_SaveText;
		 }
private: System::Void cboSets_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(setEditMode && e->KeyCode == Keys::Return) {
				cmdNewSet_ButtonClick(sender, e);
			 }

			 if(setEditMode && e->KeyCode == Keys::Escape) {
				 if(renamingSet == "") {
					// we are creating a new set, abort that
					 setSetEditMode(false);
					 refreshSetList();
				 } else {
					 // we are renaming a set, abort that and set text back to previous...
					 setSetEditMode(false);
					 refreshSetList();
					 cboSets->Text = renamingSet;
					 renamingSet = "";
					 onSetSelection();
				 }
			 }
		 }
private: System::Void tsmiDeleteSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 deleteSet(cboSets->Text);
			 refreshSetList();
			 if(cboSets->Items->Count > 0)
				cboSets->SelectedIndex = 0;
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		 }
};
}
#pragma endregion
