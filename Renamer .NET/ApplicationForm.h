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
	/// Zusammenfassung für ApplicationForm
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

	private: bool ruleSetEditMode;
	private: bool outputFormatEditMode;

    //! set which is currently renamed, if none its empty string
    //! \todo is this really needed because of ruleSet var?
	private: String^ renamingSet; 

	private: static String^ cmdNewSet_DefaultText = L"Neues Set";
	private: static String^ cmdNewSet_SaveText = L"Speichern";
	private: static String^ cmdOutputFormat_DefaultText = L"Bearbeiten";
	private: static String^ cmdOutputFormat_SaveText = L"Speichern";
	private: System::Windows::Forms::ComboBox^  cboRuleSets;


    // Form Controls


	private: System::Windows::Forms::TextBox^  txtOutputFormat;

	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;
	private: System::Windows::Forms::ContextMenuStrip^  cmsInputRules;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteInputRule;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiEditInputRule;
	private: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;



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

	private: System::Windows::Forms::ComboBox^  cboOutputFormats;


	private: System::Windows::Forms::ToolStrip^  toolStrip2;
	private: System::Windows::Forms::ToolStripDropDownButton^  cmdOutputFormat;

	private: System::Windows::Forms::RichTextBox^  txtNewInputRule;
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
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Label^  label2;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ApplicationForm::typeid));
			this->txtNewInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->lstInputRules = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->cmsInputRules = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiDeleteInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiEditInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmdAddInputRule = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lstFiles = (gcnew System::Windows::Forms::ListView());
			this->cmdAddFiles = (gcnew System::Windows::Forms::Button());
			this->cboRuleSets = (gcnew System::Windows::Forms::ComboBox());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->cmdNewSet = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->tsmiNewSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiRenameSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiDeleteSet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cboOutputFormats = (gcnew System::Windows::Forms::ComboBox());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->cmdOutputFormat = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
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
			splitContainer1->Size = System::Drawing::Size(460, 308);
			splitContainer1->SplitterDistance = 220;
			splitContainer1->TabIndex = 7;
			// 
			// groupBox1
			// 
			groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			groupBox1->Controls->Add(this->txtNewInputRule);
			groupBox1->Controls->Add(this->lstInputRules);
			groupBox1->Controls->Add(this->cmdAddInputRule);
			groupBox1->Location = System::Drawing::Point(3, 3);
			groupBox1->Name = L"groupBox1";
			groupBox1->Size = System::Drawing::Size(214, 300);
			groupBox1->TabIndex = 6;
			groupBox1->TabStop = false;
			groupBox1->Text = L"Reguläre Ausdrücke";
			// 
			// txtNewInputRule
			// 
			this->txtNewInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtNewInputRule->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtNewInputRule->Location = System::Drawing::Point(7, 269);
			this->txtNewInputRule->Multiline = false;
			this->txtNewInputRule->Name = L"txtNewInputRule";
			this->txtNewInputRule->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->txtNewInputRule->Size = System::Drawing::Size(150, 23);
			this->txtNewInputRule->TabIndex = 10;
			this->txtNewInputRule->Text = L"";
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
			this->lstInputRules->Size = System::Drawing::Size(199, 244);
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
			// cmdAddInputRule
			// 
			this->cmdAddInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cmdAddInputRule->Location = System::Drawing::Point(163, 269);
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
			groupBox2->Size = System::Drawing::Size(230, 305);
			groupBox2->TabIndex = 7;
			groupBox2->TabStop = false;
			groupBox2->Text = L"Dateien";
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button1->Location = System::Drawing::Point(6, 269);
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
			this->lstFiles->Size = System::Drawing::Size(216, 244);
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
			this->cmdAddFiles->Location = System::Drawing::Point(149, 269);
			this->cmdAddFiles->Name = L"cmdAddFiles";
			this->cmdAddFiles->Size = System::Drawing::Size(75, 23);
			this->cmdAddFiles->TabIndex = 1;
			this->cmdAddFiles->Text = L"suchen";
			this->cmdAddFiles->UseVisualStyleBackColor = true;
			this->cmdAddFiles->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdSearchFiles_Click);
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(38, 17);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(23, 13);
			label1->TabIndex = 2;
			label1->Text = L"Set";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(22, 44);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(39, 13);
			label2->TabIndex = 4;
			label2->Text = L"Format";
			// 
			// cboRuleSets
			// 
			this->cboRuleSets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboRuleSets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboRuleSets->FormattingEnabled = true;
			this->cboRuleSets->Location = System::Drawing::Point(69, 14);
			this->cboRuleSets->Name = L"cboRuleSets";
			this->cboRuleSets->Size = System::Drawing::Size(349, 21);
			this->cboRuleSets->TabIndex = 0;
			this->cboRuleSets->SelectedIndexChanged += gcnew System::EventHandler(this, &ApplicationForm::cboRuleSets_SelectedIndexChanged);
			this->cboRuleSets->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::cboRuleSets_TextChanged);
			this->cboRuleSets->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ApplicationForm::cboRuleSets_KeyDown);
			// 
			// txtOutputFormat
			// 
			this->txtOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFormat->Location = System::Drawing::Point(12, 355);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(0, 20);
			this->txtOutputFormat->TabIndex = 3;
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::txtOutputFormat_TextChanged);
			// 
			// dlgAddFiles
			// 
			this->dlgAddFiles->FileName = L"*.*";
			this->dlgAddFiles->Multiselect = true;
			this->dlgAddFiles->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::dlgAddFiles_FileOk);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->cmdNewSet});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Flow;
			this->toolStrip1->Location = System::Drawing::Point(420, 12);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(91, 23);
			this->toolStrip1->TabIndex = 8;
			this->toolStrip1->TabStop = true;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// cmdNewSet
			// 
			this->cmdNewSet->AutoSize = false;
			this->cmdNewSet->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsmiNewSet, 
				this->tsmiRenameSet, this->tsmiDeleteSet});
			this->cmdNewSet->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cmdNewSet.Image")));
			this->cmdNewSet->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdNewSet->Name = L"cmdNewSet";
			this->cmdNewSet->Size = System::Drawing::Size(90, 20);
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
			// cboOutputFormats
			// 
			this->cboOutputFormats->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboOutputFormats->FormattingEnabled = true;
			this->cboOutputFormats->Location = System::Drawing::Point(69, 41);
			this->cboOutputFormats->Name = L"cboOutputFormats";
			this->cboOutputFormats->Size = System::Drawing::Size(349, 21);
			this->cboOutputFormats->TabIndex = 10;
			this->cboOutputFormats->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ApplicationForm::cboOutputFormats_KeyDown);
			// 
			// toolStrip2
			// 
			this->toolStrip2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->cmdOutputFormat});
			this->toolStrip2->Location = System::Drawing::Point(420, 39);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(93, 25);
			this->toolStrip2->TabIndex = 11;
			this->toolStrip2->Text = L"00";
			// 
			// cmdOutputFormat
			// 
			this->cmdOutputFormat->AutoSize = false;
			this->cmdOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cmdOutputFormat.Image")));
			this->cmdOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdOutputFormat->Name = L"cmdOutputFormat";
			this->cmdOutputFormat->Size = System::Drawing::Size(90, 22);
			this->cmdOutputFormat->Text = L"Speichern";
			this->cmdOutputFormat->Click += gcnew System::EventHandler(this, &ApplicationForm::cmdOutputFormat_Click);
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 387);
			this->Controls->Add(this->toolStrip2);
			this->Controls->Add(splitContainer1);
			this->Controls->Add(label2);
			this->Controls->Add(this->cboOutputFormats);
			this->Controls->Add(label1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->cboRuleSets);
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
//			txtNewInput->Text = "";
			refreshInputRulesList();
		}

		void setRuleSetEditMode(bool val) {
			ruleSetEditMode = val;
			cboRuleSets->DropDownStyle = ruleSetEditMode ? ComboBoxStyle::DropDown : ComboBoxStyle::DropDownList;

			if(ruleSetEditMode) {
				String^ text = cboRuleSets->Text;
				cboRuleSets->Items->Clear();
				cboRuleSets->Text = text;
			} else {
				refreshSetList();
			}
		}

		void setOutputFormatEditMode(bool val) {
			outputFormatEditMode = val;
			cboOutputFormats->DropDownStyle = outputFormatEditMode ? ComboBoxStyle::DropDown : ComboBoxStyle::DropDownList;

			if(outputFormatEditMode) {
				String^ text = cboOutputFormats->Text;
				cboOutputFormats->Items->Clear();
				cboOutputFormats->Text = text;
			} else {
				refreshOutputFormatsList();
			}
		}


		void removeInputRule(long long inputRuleID) {
			//! \todo implement
			//rule->removeInputRule(inputRuleID);
		}

		void loadOrCreateRuleSet(String^ ruleSetName) 
		{
			exAssert(ruleSetName != "");
			if(ruleSet)
				delete ruleSet;
			ruleSet = new Ruleset(toStdWString(ruleSetName));

			Text = "Renamer - " + ruleSetName;
		}

		void renameRuleSet(String^ oldRuleSetName, String^ newRuleSetName) {
			exAssert(oldRuleSetName != "");
			exAssert(newRuleSetName != "");
			if(ruleSet) {
				string ruleSetName = ruleSet->getName();
				if(ruleSetName == toStdString(oldRuleSetName)) {
					delete ruleSet;
					File::Move(oldRuleSetName + ".db3", newRuleSetName + ".db3");
					string s = toStdString(newRuleSetName);
					ruleSet = new Ruleset(toStdWString(s));
				} else {
					File::Move(oldRuleSetName + ".db3", newRuleSetName + ".db3");
				}
			}

			else {
				File::Move(oldRuleSetName + ".db3", newRuleSetName + ".db3");
			}
		}

		void deleteRuleSet(String^ ruleSetName) {
			if(ruleSet) {
				string currentRuleSetName = ruleSet->getName();
				if(currentRuleSetName == toStdString(ruleSetName)) {
					delete ruleSet;
					ruleSet = NULL;
				}
			}
			File::Delete(ruleSetName + ".db3");
		}

		void addFile( String^ pathToFile )
		{
			String^ fileName = System::IO::Path::GetFileNameWithoutExtension(pathToFile);
			ListViewItem^ item = gcnew ListViewItem(fileName);
			item->Tag = pathToFile;
			lstFiles->Items->Add(item);
		}

		void refreshInputRulesList() 
		{
			exAssert(ruleSet != NULL);
			if(ruleSet == NULL) return ;

			lstInputRules->Items->Clear();

/*			vector<InputRule> inputRules = ruleSet->getInputRules();
			for(unsigned int i=0; i<inputRules.size(); i++) {
				String^ text = toClrString(inputRules[i].getRegex());
				ListViewItem^ item = gcnew ListViewItem(text,0);
				lstInputRules->Items->Add(item);
			}*/
		}

		void refreshOutputFormatsList() 
		{
			exAssert(ruleSet != NULL);
			if(ruleSet == NULL) return ;

			cboOutputFormats->Items->Clear();
			vector<OutputFormat> outputFormats = ruleSet->getOutputFormats();
			for(unsigned int i=0; i<outputFormats.size(); i++) {
				cboOutputFormats->Items->Add(toClrString(outputFormats[i].getFormat()));
			}
 
			if(cboOutputFormats->Items->Count == 0)
			{
				setOutputFormatEditMode(true);
			} else {
				selectOutputFormat(0);
				setOutputFormatEditMode(false);
			}
		}

		void refreshSetList() 
		{
			cboRuleSets->Items->Clear();

			using namespace System::IO;
			array<String^>^fileNames = Directory::GetFiles( ".\\", "*.db3" );

			for(int i=0; i<fileNames->Length; i++) {
				String^ fileName = fileNames[i]->Substring(2);
				String^ setName = fileName->Substring(0, fileName->Length-4);
				cboRuleSets->Items->Add(setName);
			}
		}

		void selectRuleSet(int index) {
			refreshSetList();

			exAssert(cboRuleSets->Items->Count > 0);
			cboRuleSets->SelectedIndex = index;
			
			loadOrCreateRuleSet(cboRuleSets->Text);
			refreshInputRulesList();
			refreshOutputFormatsList();
		}

		void selectRuleSet(String^ setName) {
			exAssert(cboRuleSets->Items->Count > 0);
			int i = cboRuleSets->FindString(setName);
			selectRuleSet(i);
		}

		void selectOutputFormat(int index) {
			exAssert(cboOutputFormats->Items->Count > 0);
			cboOutputFormats->SelectedIndex = index;
		}

		void selectOutputFormat(String^ outputFormatName) {
			exAssert(cboOutputFormats->Items->Count > 0);
			int i = cboOutputFormats->FindString(outputFormatName);
			cboOutputFormats->SelectedIndex = i;
		}

#pragma endregion
#pragma region Form Handlers

	private: System::Void ApplicationForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 ruleSet = NULL;
		 outputFormat = NULL;
		 codeRunning = false;
		 renamingSet = "";
		 setRuleSetEditMode(false);
		 outputFormatEditMode = false;

		 refreshSetList();

		 if(cboRuleSets->Items->Count == 0) {
			 tsmiNewSet_Click(sender, e); // create new set, let user enter ruleSetName
		 }

		 else {
			 String^ lastOpenedSetName = Microsoft::VisualBasic::Interaction::GetSetting("Renamer", "Settings", "last_set", "--empty--");
			 
			 if(lastOpenedSetName == "--empty--") {
				 selectRuleSet(0);
			 }
			 else {
				 if(File::Exists(lastOpenedSetName))
					 selectRuleSet(lastOpenedSetName);
				 else
					 selectRuleSet(0);
			 }
		 }
	}
	
	private: System::Void ApplicationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 Microsoft::VisualBasic::Interaction::SaveSetting("Renamer", "Settings", "last_set47110815", cboRuleSets->Text);
	}

private: System::Void cboRuleSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(codeRunning) return ;
			 codeRunning = true;
			 selectRuleSet(cboRuleSets->Text);
			 codeRunning = false;
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
/*			 if(ruleSet) {
				ruleSet->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }*/
		 }
private: System::Void cboRuleSets_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void cmdNewInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(ruleSet) {
//				 addInputRule(txtNewInput->Text);
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
			 else if(ruleSetEditMode == true) {
				 // we are finishing renaming a set
				 String^ newSetName = cboRuleSets->Text;
				 renameRuleSet(renamingSet, newSetName);
				 renamingSet = "";
				 //refreshSetList();
				 cmdNewSet->Text = cmdNewSet_DefaultText;
				 //cboRuleSets->Text = newSetName;
				 //exAssert(cboRuleSets->Text == newSetName);
				 setRuleSetEditMode(false);
				 //exAssert(cboRuleSets->Text == newSetName);
				 //onSetSelection();
				 selectRuleSet(newSetName);
			 }
		 }
private: System::Void tsmiNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(ruleSetEditMode == false) {
				// enable entering a new set name
				setRuleSetEditMode(true);
				cmdNewSet->Text = cmdNewSet_SaveText;
				cboRuleSets->Text = "";
			 } else {
				 // disable edit mode and create the set
				 cmdNewSet->Text = cmdNewSet_DefaultText;
				 String^ setName = cboRuleSets->Text;
				 setRuleSetEditMode(false);
				 if(setName->Length > 0) {
					 loadOrCreateRuleSet(setName);
					 refreshSetList();
					 selectRuleSet(setName);
					 //cboRuleSets->Text = setName;
					 //onSetSelection();
				 }
			 }
		 }
private: System::Void tsmiRenameSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(cboRuleSets->Items->Count == 0 ||ruleSetEditMode == true)
				 return ;
			 renamingSet = cboRuleSets->Text;
			 setRuleSetEditMode(true);
			 cmdNewSet->Text = cmdNewSet_SaveText;
		 }
private: System::Void cboRuleSets_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(ruleSetEditMode && e->KeyCode == Keys::Return) {
				cmdNewSet_ButtonClick(sender, e);
			 }

			 if(ruleSetEditMode && e->KeyCode == Keys::Escape) {
				 if(renamingSet == "") {
					// we are creating a new set, abort that
					 setRuleSetEditMode(false);
					 refreshSetList();
				 } else {
					 // we are renaming a set, abort that and set text back to previous...
					 setRuleSetEditMode(false);
					 refreshSetList();
					 renamingSet = "";

					 selectRuleSet(renamingSet);
				 }
			 }
		 }
private: System::Void tsmiDeleteSet_Click(System::Object^  sender, System::EventArgs^  e) {
			 deleteRuleSet(cboRuleSets->Text);
			 refreshSetList();
			 if(cboRuleSets->Items->Count > 0)
				 selectRuleSet(0);
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void cmdOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat outputFormat = ruleSet->addOutputFormat();
			 outputFormat.setFormat(toStdString(cboOutputFormats->Text));

			 // \todo implement
			 setOutputFormatEditMode(false);
		 }
private: System::Void cboOutputFormats_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(outputFormatEditMode) {
				
			 }
		 }
};
}
#pragma endregion
