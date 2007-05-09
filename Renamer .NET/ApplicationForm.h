#pragma region Header
#pragma once
#include <vcclr.h>
#include "ruleset.h"
#include "inputRule.h"
#include "clrUtility.h"
#include "stlUtility.h"
#include "stdlib.h"
#include "error.h"

#include "RulesetProperties.h"

//! List of all loaded Rulesets
	vector<Ruleset*> ruleSets;

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Collections::Generic;
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

    //! Currently used Ruleset
	private: Ruleset* ruleSet;


	private: static String^ WindowTitle = "Renamer";

    // Main Form Controls
	private: System::Windows::Forms::TreeView^  guiObjectTree;
	private: System::Windows::Forms::ListView^  guiFileList;
	private: System::Windows::Forms::TableLayoutPanel^  guiPropertyPanel;
	private: System::Windows::Forms::MenuStrip^  mainMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;

    // MainMenu
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  extrasToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;

	// ToolStrip for FileList filtering
	private: System::Windows::Forms::ToolStripButton^  tsShowAll;
	private: System::Windows::Forms::ToolStripButton^  tsShowMatched;
	private: System::Windows::Forms::ToolStripButton^  tsShowFailed;
	 
	// ContextMenuStrip for Rulesets
	private: System::Windows::Forms::ContextMenuStrip^  cmsRulesets;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiCreateOutputFormat;
			 
    // ContextMenuStrip for OutputFormats	
	private: System::Windows::Forms::ContextMenuStrip^  cmsOutputFormats;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiCreateInputRule;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteOutputFormat;

	// ContextMenuStrip for InputRules	
	private: System::Windows::Forms::ContextMenuStrip^  cmsInputRules;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteInputRule;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiCreateGem;
	private: System::Windows::Forms::SaveFileDialog^  saveAsFileDialog;

	// Dialogs

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;

	// Stuff

	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
	private: System::Windows::Forms::ToolStripButton^  tsBtnAddFiles;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  newFileDialog;
	private: System::Windows::Forms::ContextMenuStrip^  cmsGems;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

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
			System::Windows::Forms::SplitContainer^  splitContainer2;
			System::Windows::Forms::ToolStrip^  fileListToolStrip;
			System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ApplicationForm::typeid));
			System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
			this->guiObjectTree = (gcnew System::Windows::Forms::TreeView());
			this->guiPropertyPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tsShowAll = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsShowMatched = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsShowFailed = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsBtnAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->guiFileList = (gcnew System::Windows::Forms::ListView());
			this->cmsInputRules = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiCreateGem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiDeleteInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->mainMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->extrasToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmsOutputFormats = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiCreateInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiDeleteOutputFormat = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmsRulesets = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiCreateOutputFormat = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->newFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->cmsGems = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			fileListToolStrip = (gcnew System::Windows::Forms::ToolStrip());
			toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			splitContainer1->Panel1->SuspendLayout();
			splitContainer1->Panel2->SuspendLayout();
			splitContainer1->SuspendLayout();
			splitContainer2->Panel1->SuspendLayout();
			splitContainer2->Panel2->SuspendLayout();
			splitContainer2->SuspendLayout();
			fileListToolStrip->SuspendLayout();
			this->cmsInputRules->SuspendLayout();
			this->mainMenuStrip->SuspendLayout();
			this->cmsOutputFormats->SuspendLayout();
			this->cmsRulesets->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			splitContainer1->Location = System::Drawing::Point(12, 27);
			splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			splitContainer1->Panel1->Controls->Add(splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			splitContainer1->Panel2->Controls->Add(fileListToolStrip);
			splitContainer1->Panel2->Controls->Add(this->guiFileList);
			splitContainer1->Size = System::Drawing::Size(724, 277);
			splitContainer1->SplitterDistance = 341;
			splitContainer1->TabIndex = 7;
			// 
			// splitContainer2
			// 
			splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			splitContainer2->Location = System::Drawing::Point(0, 0);
			splitContainer2->Name = L"splitContainer2";
			splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			splitContainer2->Panel1->Controls->Add(this->guiObjectTree);
			// 
			// splitContainer2.Panel2
			// 
			splitContainer2->Panel2->Controls->Add(this->guiPropertyPanel);
			splitContainer2->Size = System::Drawing::Size(341, 277);
			splitContainer2->SplitterDistance = 138;
			splitContainer2->TabIndex = 0;
			// 
			// guiObjectTree
			// 
			this->guiObjectTree->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->guiObjectTree->Location = System::Drawing::Point(3, 3);
			this->guiObjectTree->Name = L"guiObjectTree";
			this->guiObjectTree->Size = System::Drawing::Size(335, 132);
			this->guiObjectTree->TabIndex = 0;
			this->guiObjectTree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &ApplicationForm::guiObjectTree_AfterSelect);
			// 
			// guiPropertyPanel
			// 
			this->guiPropertyPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->guiPropertyPanel->AutoScroll = true;
			this->guiPropertyPanel->ColumnCount = 2;
			this->guiPropertyPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				158)));
			this->guiPropertyPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->guiPropertyPanel->GrowStyle = System::Windows::Forms::TableLayoutPanelGrowStyle::FixedSize;
			this->guiPropertyPanel->Location = System::Drawing::Point(3, 3);
			this->guiPropertyPanel->Name = L"guiPropertyPanel";
			this->guiPropertyPanel->RowCount = 1;
			this->guiPropertyPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->guiPropertyPanel->Size = System::Drawing::Size(335, 119);
			this->guiPropertyPanel->TabIndex = 0;
			// 
			// fileListToolStrip
			// 
			fileListToolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {toolStripLabel1, toolStripSeparator2, 
				this->tsShowAll, this->tsShowMatched, this->tsShowFailed, toolStripSeparator1, this->tsBtnAddFiles});
			fileListToolStrip->Location = System::Drawing::Point(0, 0);
			fileListToolStrip->Name = L"fileListToolStrip";
			fileListToolStrip->Size = System::Drawing::Size(379, 25);
			fileListToolStrip->TabIndex = 2;
			fileListToolStrip->Text = L"toolStrip1";
			// 
			// toolStripLabel1
			// 
			toolStripLabel1->Name = L"toolStripLabel1";
			toolStripLabel1->Size = System::Drawing::Size(37, 22);
			toolStripLabel1->Text = L"Filter:";
			// 
			// toolStripSeparator2
			// 
			toolStripSeparator2->Name = L"toolStripSeparator2";
			toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// tsShowAll
			// 
			this->tsShowAll->BackColor = System::Drawing::SystemColors::Control;
			this->tsShowAll->Checked = true;
			this->tsShowAll->CheckState = System::Windows::Forms::CheckState::Checked;
			this->tsShowAll->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsShowAll->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsShowAll.Image")));
			this->tsShowAll->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsShowAll->Name = L"tsShowAll";
			this->tsShowAll->Size = System::Drawing::Size(26, 22);
			this->tsShowAll->Tag = L"";
			this->tsShowAll->Text = L"All";
			this->tsShowAll->ToolTipText = L"Shows all files, regardless of if they matched or not";
			this->tsShowAll->Click += gcnew System::EventHandler(this, &ApplicationForm::tsShowAll_Click);
			// 
			// tsShowMatched
			// 
			this->tsShowMatched->BackColor = System::Drawing::SystemColors::Control;
			this->tsShowMatched->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsShowMatched->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsShowMatched.Image")));
			this->tsShowMatched->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsShowMatched->Name = L"tsShowMatched";
			this->tsShowMatched->Size = System::Drawing::Size(59, 22);
			this->tsShowMatched->Text = L"Matched";
			this->tsShowMatched->ToolTipText = L"Shows only files which matched the selection";
			this->tsShowMatched->Click += gcnew System::EventHandler(this, &ApplicationForm::tsShowMatched_Click);
			// 
			// tsShowFailed
			// 
			this->tsShowFailed->BackColor = System::Drawing::SystemColors::Control;
			this->tsShowFailed->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsShowFailed->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsShowFailed.Image")));
			this->tsShowFailed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsShowFailed->Name = L"tsShowFailed";
			this->tsShowFailed->Size = System::Drawing::Size(43, 22);
			this->tsShowFailed->Text = L"Failed";
			this->tsShowFailed->ToolTipText = L"Shows only files which failed to matched";
			this->tsShowFailed->Click += gcnew System::EventHandler(this, &ApplicationForm::tsShowFailed_Click);
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1->Name = L"toolStripSeparator1";
			toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// tsBtnAddFiles
			// 
			this->tsBtnAddFiles->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsBtnAddFiles.Image")));
			this->tsBtnAddFiles->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsBtnAddFiles->Name = L"tsBtnAddFiles";
			this->tsBtnAddFiles->Size = System::Drawing::Size(76, 22);
			this->tsBtnAddFiles->Text = L"Add Files";
			this->tsBtnAddFiles->Click += gcnew System::EventHandler(this, &ApplicationForm::tsBtnAddFiles_Click);
			// 
			// guiFileList
			// 
			this->guiFileList->AllowDrop = true;
			this->guiFileList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->guiFileList->FullRowSelect = true;
			this->guiFileList->Location = System::Drawing::Point(3, 28);
			this->guiFileList->MultiSelect = false;
			this->guiFileList->Name = L"guiFileList";
			this->guiFileList->Size = System::Drawing::Size(373, 229);
			this->guiFileList->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->guiFileList->TabIndex = 0;
			this->guiFileList->UseCompatibleStateImageBehavior = false;
			this->guiFileList->View = System::Windows::Forms::View::List;
			this->guiFileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &ApplicationForm::guiFileList_DragDrop);
			this->guiFileList->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &ApplicationForm::guiFileList_DragOver);
			// 
			// cmsInputRules
			// 
			this->cmsInputRules->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmiCreateGem, 
				this->tsmiDeleteInputRule});
			this->cmsInputRules->Name = L"contextMenuStrip1";
			this->cmsInputRules->Size = System::Drawing::Size(134, 48);
			// 
			// tsmiCreateGem
			// 
			this->tsmiCreateGem->Name = L"tsmiCreateGem";
			this->tsmiCreateGem->Size = System::Drawing::Size(133, 22);
			this->tsmiCreateGem->Text = L"Add Gem";
			this->tsmiCreateGem->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiCreateGem_Click);
			// 
			// tsmiDeleteInputRule
			// 
			this->tsmiDeleteInputRule->Name = L"tsmiDeleteInputRule";
			this->tsmiDeleteInputRule->Size = System::Drawing::Size(133, 22);
			this->tsmiDeleteInputRule->Text = L"Delete";
			// 
			// dlgAddFiles
			// 
			this->dlgAddFiles->FileName = L"*.*";
			this->dlgAddFiles->Multiselect = true;
			this->dlgAddFiles->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::dlgAddFiles_FileOk);
			// 
			// mainMenuStrip
			// 
			this->mainMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->extrasToolStripMenuItem, this->toolStripMenuItem1});
			this->mainMenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainMenuStrip->Name = L"mainMenuStrip";
			this->mainMenuStrip->Size = System::Drawing::Size(748, 24);
			this->mainMenuStrip->TabIndex = 12;
			this->mainMenuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->newToolStripMenuItem->Text = L"&New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->openToolStripMenuItem->Text = L"&Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->saveToolStripMenuItem->Text = L"&Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->saveAsToolStripMenuItem->Text = L"Save &As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::saveAsToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->exitToolStripMenuItem->Text = L"&Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// extrasToolStripMenuItem
			// 
			this->extrasToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->optionsToolStripMenuItem});
			this->extrasToolStripMenuItem->Name = L"extrasToolStripMenuItem";
			this->extrasToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->extrasToolStripMenuItem->Text = L"Extras";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->optionsToolStripMenuItem->Text = L"&Options";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(25, 20);
			this->toolStripMenuItem1->Text = L"\?";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// cmsOutputFormats
			// 
			this->cmsOutputFormats->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsmiCreateInputRule, 
				this->tsmiDeleteOutputFormat});
			this->cmsOutputFormats->Name = L"contextMenuStrip1";
			this->cmsOutputFormats->Size = System::Drawing::Size(161, 48);
			// 
			// tsmiCreateInputRule
			// 
			this->tsmiCreateInputRule->Name = L"tsmiCreateInputRule";
			this->tsmiCreateInputRule->Size = System::Drawing::Size(160, 22);
			this->tsmiCreateInputRule->Text = L"Add InputRule";
			this->tsmiCreateInputRule->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiCreateInputRule_Click);
			// 
			// tsmiDeleteOutputFormat
			// 
			this->tsmiDeleteOutputFormat->Name = L"tsmiDeleteOutputFormat";
			this->tsmiDeleteOutputFormat->Size = System::Drawing::Size(160, 22);
			this->tsmiDeleteOutputFormat->Text = L"Delete";
			// 
			// cmsRulesets
			// 
			this->cmsRulesets->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmiCreateOutputFormat});
			this->cmsRulesets->Name = L"contextMenuStrip1";
			this->cmsRulesets->Size = System::Drawing::Size(185, 26);
			// 
			// tsmiCreateOutputFormat
			// 
			this->tsmiCreateOutputFormat->Name = L"tsmiCreateOutputFormat";
			this->tsmiCreateOutputFormat->Size = System::Drawing::Size(184, 22);
			this->tsmiCreateOutputFormat->Text = L"Add OutputFormat";
			this->tsmiCreateOutputFormat->Click += gcnew System::EventHandler(this, &ApplicationForm::tsmiCreateOutputFormat_Click);
			// 
			// saveAsFileDialog
			// 
			this->saveAsFileDialog->DefaultExt = L"db3";
			this->saveAsFileDialog->Filter = L"Renamer Databases (*.db3)|*.db3";
			this->saveAsFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::saveAsFileDialog_FileOk);
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Renamer Databases (*.db3)|*.db3";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::openFileDialog_FileOk);
			// 
			// newFileDialog
			// 
			this->newFileDialog->DefaultExt = L"db3";
			this->newFileDialog->Filter = L"Renamer Databases (*.db3)|*.db3";
			this->newFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ApplicationForm::newFileDialog_FileOk);
			// 
			// cmsGems
			// 
			this->cmsGems->Name = L"cmsGems";
			this->cmsGems->Size = System::Drawing::Size(61, 4);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(357, 354);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(198, 24);
			this->richTextBox1->TabIndex = 13;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &ApplicationForm::richTextBox1_TextChanged);
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(748, 416);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->mainMenuStrip);
			this->Controls->Add(splitContainer1);
			this->MainMenuStrip = this->mainMenuStrip;
			this->Name = L"ApplicationForm";
			this->Opacity = 0.95;
			this->Text = L"Renamer";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ApplicationForm::ApplicationForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ApplicationForm::ApplicationForm_Load);
			splitContainer1->Panel1->ResumeLayout(false);
			splitContainer1->Panel2->ResumeLayout(false);
			splitContainer1->Panel2->PerformLayout();
			splitContainer1->ResumeLayout(false);
			splitContainer2->Panel1->ResumeLayout(false);
			splitContainer2->Panel2->ResumeLayout(false);
			splitContainer2->ResumeLayout(false);
			fileListToolStrip->ResumeLayout(false);
			fileListToolStrip->PerformLayout();
			this->cmsInputRules->ResumeLayout(false);
			this->mainMenuStrip->ResumeLayout(false);
			this->mainMenuStrip->PerformLayout();
			this->cmsOutputFormats->ResumeLayout(false);
			this->cmsRulesets->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Renamer Business Logic
		void createRuleSet(String^ ruleSetFileName) {
			String^ ruleSetName = System::IO::Path::GetFileNameWithoutExtension(ruleSetFileName);
			exAssert(ruleSetName != "");

			try {
				ruleSets.push_back(new Ruleset(toStdWString(ruleSetFileName)));
			}

			catch(exception& e) {
				String^ message = L"Exception: ";
				message += toClrString(e.what());
				MessageBox::Show(message, L"Exception!" );
				return;
			}
		}

		void loadContextStripToEditMenu(System::Windows::Forms::ContextMenuStrip^ cms) {
			if(cms == nullptr)
				return ;

			/*editToolStripMenuItem->DropDownItems->Insert() = cms->Items;
			editToolStripMenuItem->DropDownItems->Add();*/
			
			
			editToolStripMenuItem->DropDownItems->Clear();
			for(int i=0; i<editToolStripMenuItem->DropDownItems->Count; i++) {
				//editToolStripMenuItem->DropDownItems[i]->Visible = false;
			}

			array<ToolStripMenuItem^>^ menuItems = gcnew array<ToolStripMenuItem^>(cms->Items->Count);
			cms->Items->CopyTo(menuItems, 0);

			for(int i=0; i<cms->Items->Count; i++) {
				//ToolStripMenuItem^ tsi = (ToolStripMenuItem^) cms->Items[i];
				//ToolStripMenuItem^ newtsi = gcnew ToolStripMenuItem(tsi->Text);
//				newtsi->Click = tsi->Click;
				
				//tsi->Click->Combine(tsi->Click, newtsi->Click);
				//newtsi->Click += (System::EventHandler ^) 

				editToolStripMenuItem->DropDownItems->Insert(0, menuItems[i]);
			}
//			cms->Items->CopyTo(editToolStripMenuItem->DropDownItems->Add, 0);*/
		}

		bool loadRuleset(String^ filename) 
		{
			if(!System::IO::File::Exists(filename)) {
				return false;
			}

			for(unsigned int i=0; i<ruleSets.size(); i++) {
				if(toClrString(ruleSets[i]->getFilename()) == filename)
					return false;
			}



			exAssert(filename != "");
			String^ ruleSetName = System::IO::Path::GetFileNameWithoutExtension(filename);
			exAssert(ruleSetName != "");



			try {
				ruleSets.push_back(new Ruleset(toStdWString(filename)));
			}

			catch(exception& e) {
				String^ message = L"Exception: ";
				message += toClrString(e.what());
				MessageBox::Show(message, L"Exception!!!!" );
				return false;
			}

			return true;
		}

		void renameRuleSet(int ruleSetIndex, String^ newRuleSetName) {
			if(ruleSets[ruleSetIndex]) {
				String^ oldRuleSetName = toClrString(ruleSets[ruleSetIndex]->getName());
				String^ oldRuleSetFileName = toClrString(ruleSets[ruleSetIndex]->getFilename());
				String^ newRuleSetFileName = oldRuleSetFileName->Substring(0, oldRuleSetFileName->LastIndexOf(L'\\')+1) + newRuleSetName +  oldRuleSetFileName->Substring(oldRuleSetFileName->LastIndexOf(L'.'));
				// if newRuleSetName is invalid, don't rename ...
				if(newRuleSetName == "" || System::IO::File::Exists(newRuleSetFileName))
					return ;
				delete ruleSets[ruleSetIndex];
				File::Move(oldRuleSetFileName, newRuleSetFileName);
				string s = toStdString(newRuleSetName);
				ruleSets[ruleSetIndex] = new Ruleset(toStdWString(newRuleSetFileName));
			}
		}

		void deleteRuleSet(int ruleSetIndex) {
			if(ruleSets[ruleSetIndex]) {
				String^ ruleSetFileNmae = toClrString(ruleSets[ruleSetIndex]->getFilename());
				delete ruleSets[ruleSetIndex];
				ruleSets[ruleSetIndex] = NULL;
				File::Delete(ruleSetFileNmae);
			}
		}

		void addFileToFileList( String^ pathToFile )
		{
			String^ fileName = System::IO::Path::GetFileNameWithoutExtension(pathToFile);
			ListViewItem^ item = gcnew ListViewItem(fileName);
			item->Tag = pathToFile;
			guiFileList->Items->Add(item);
		}

		System::Void ruleSetName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			RichTextBox^ propertyEdit = (RichTextBox^) sender;
			String^ newRuleSetName = propertyEdit->Text;
			int ruleSetIndex = int(((_PairStringInt^) guiObjectTree->SelectedNode->Tag)->value);
			
			if(!System::Text::RegularExpressions::Regex::IsMatch(newRuleSetName, "^[\\w \\.\\-_]*$")) {
				// invalid ruleset name
				propertyEdit->Text = toClrString(ruleSets[ruleSetIndex]->getName());
				return ;
			}

			renameRuleSet(ruleSetIndex, newRuleSetName);
			guiObjectTree->SelectedNode->Text = newRuleSetName;
		}


		void insertPropertyToPanel(int row, String^ label, String^ value, System::EventHandler^ handler_TextChanged) {
			Label^ propertyLabel = gcnew Label();
			propertyLabel->Text = label;

			RichTextBox^ propertyEdit = gcnew RichTextBox();
			propertyEdit->Text = value;
			propertyEdit->Multiline = false;
			propertyEdit->Height = 18;

			// adding event handlers
			if(handler_TextChanged != nullptr)
				propertyEdit->TextChanged += handler_TextChanged;

			guiPropertyPanel->Controls->Add(propertyLabel, 0,row);
			guiPropertyPanel->Controls->Add(propertyEdit,  1,row);

		}

		void loadNodeProperties(TreeNode^ node) {
			_PairStringInt^ properties = (_PairStringInt^) node->Tag;

			guiPropertyPanel->Controls->Clear();

			if(properties->key == L"ruleset") {
				ruleSet = ruleSets[(int) properties->value];
				guiPropertyPanel->RowCount = 1;
				insertPropertyToPanel(0, "Name", toClrString(ruleSet->getName()), gcnew System::EventHandler(this, &ApplicationForm::ruleSetName_TextChanged));
			} else if (properties->key == L"outputformat") {
				_PairStringInt^ rulesetProperties = (_PairStringInt^) node->Parent->Tag;
				ruleSet = ruleSets[(int) rulesetProperties->value];				

				OutputFormat outputFormat(ruleSet->getDatabase(), properties->value);
				guiPropertyPanel->RowCount = 1;
				insertPropertyToPanel(0, "OutputFormat", toClrString(outputFormat.getFormat()), nullptr);
			} else if (properties->key== L"inputrule") {
				_PairStringInt^ rulesetProperties = (_PairStringInt^) node->Parent->Parent->Tag;
				ruleSet = ruleSets[(int) rulesetProperties->value];				

				InputRule inputRule(properties->value, ruleSet->getDatabase());
				guiPropertyPanel->RowCount = 1;
				insertPropertyToPanel(0, "Regular Expression", toClrString(inputRule.getRegex()), nullptr);
			} else if (properties->key == L"gem") {
				_PairStringInt^ rulesetProperties = (_PairStringInt^) node->Parent->Parent->Parent->Tag;
				ruleSet = ruleSets[(int) rulesetProperties->value];				
				_PairStringInt^ inputRuleProperties = (_PairStringInt^) node->Parent->Tag;

				Gem gem(ruleSet->getDatabase(), inputRuleProperties->value, properties->value);
				guiPropertyPanel->RowCount = 1;
				insertPropertyToPanel(0, "Name", toClrString(gem.getName()), nullptr);
			}
		}

		void loadObjectTree() 
		{
			guiObjectTree->Nodes->Clear();

			for(unsigned int i=0; i<ruleSets.size(); i++) {
				TreeNode^ rulesetNode = gcnew TreeNode(toClrString(ruleSets[i]->getName()));
				rulesetNode->ContextMenuStrip = cmsRulesets;
				rulesetNode->Tag = gcnew _PairStringInt(L"ruleset", i);

				guiObjectTree->Nodes->Add(rulesetNode);

				vector<OutputFormat> outputFormats = ruleSets[i]->getOutputFormats();
				for(unsigned int j=0; j<outputFormats.size(); j++) {
					TreeNode^ outputFormatNode = gcnew TreeNode(toClrString(outputFormats[j].getFormat()));
					outputFormatNode->ContextMenuStrip = cmsOutputFormats;
					outputFormatNode->Tag = gcnew _PairStringInt(L"outputformat", outputFormats[j].getRowId());

					rulesetNode->Nodes->Add(outputFormatNode);

					vector<InputRule> inputRules = outputFormats[j].getInputRules();
					for(unsigned int k=0; k<inputRules.size(); k++) {
						TreeNode^ inputRuleNode = gcnew TreeNode(toClrString(inputRules[k].getRegex()));
						inputRuleNode->ContextMenuStrip = cmsInputRules;
						inputRuleNode->Tag = gcnew _PairStringInt(L"inputrule", inputRules[k].getRowId());

						outputFormatNode->Nodes->Add(inputRuleNode);

						vector<Gem> gems = inputRules[k].getGems();
						for(unsigned int l=0; l<gems.size(); l++) {
							TreeNode^ gemNode = gcnew TreeNode(toClrString(gems[l].getName()));
							gemNode->ContextMenuStrip = cmsGems;
							gemNode->Tag = gcnew _PairStringInt(L"gem", gems[l].getRowid());

							inputRuleNode->Nodes->Add(gemNode);
						}
					}
				}
				// select first Ruleset
				if(i == 0)
					guiObjectTree->SelectedNode = rulesetNode;

			}

			if(ruleSets.size() == 0) {
				TreeNode^ dummyNode = gcnew TreeNode("No Rulesets found!");
				dummyNode->Tag = gcnew _PairStringInt(L"dummy", 0);
				guiObjectTree->Nodes->Add(dummyNode);
			}			
		}
#pragma endregion
#pragma region Form Handlers

	private: System::Void ApplicationForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 Text = WindowTitle;
		 ruleSet = NULL;

		 String^ lastRulesets = Microsoft::VisualBasic::Interaction::GetSetting("Renamer", "Settings", "rulesets", "--empty--");

		 if(lastRulesets != "--empty--" && lastRulesets != "") {
			 array<String^>^ setNames = lastRulesets->Split('|');
			 for(int i=0; i<setNames->Length; i++) {
				 String^ setName = setNames[i];
				 if(!loadRuleset(setNames[i])) {
					 MessageBox::Show("file not found: " + setNames[i], "404");
				 }
			 }
		 }
	
		 loadObjectTree();
	}
	
	private: System::Void ApplicationForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 String^ ruleSetList = L"";

			 for(unsigned int i=0; i<ruleSets.size(); i++) {
					ruleSetList += toClrString(ruleSets[i]->getFilename());
					if(i < (ruleSets.size() -1)) 
						ruleSetList += L"|";
			 }
				 
			 Microsoft::VisualBasic::Interaction::SaveSetting("Renamer", "Settings", "rulesets", ruleSetList);
	}

private: System::Void dlgAddFiles_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 for(int i=0; i<dlgAddFiles->FileNames->Length; i++) {
				 addFileToFileList(dlgAddFiles->FileNames[i]);
			 }	
		 }

private: System::Void tsmiRenameSet_Click(System::Object^  sender, System::EventArgs^  e) {
			/* if(cboRuleSets->Items->Count == 0 ||ruleSetEditMode == true)
				 return ;
			 renamingSet = cboRuleSets->Text;
			 setRuleSetEditMode(true);
			 cmdNewSet->Text = cmdNewSet_SaveText;*/
		 }
private: System::Void guiObjectTree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 loadNodeProperties(e->Node);
			 //loadContextStripToEditMenu(e->Node->ContextMenuStrip);
		 }
private: System::Void tsmiCreateOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat newOutputFormat = ruleSet->addOutputFormat();
			 newOutputFormat.setFormat("new OutputFormat");

			 loadObjectTree();
		 }
private: System::Void tsmiCreateGem_Click(System::Object^  sender, System::EventArgs^  e) {
			 sqlite_int64  rowid = ((_PairStringInt^)(guiObjectTree->SelectedNode->Tag))->value;
			 InputRule senderInputRule(rowid, ruleSet->getDatabase());
			 Gem newGem = senderInputRule.addGem("new Gem");

			 loadObjectTree();
		 }
private: System::Void tsmiCreateInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 sqlite_int64  rowid = ((_PairStringInt^)(guiObjectTree->SelectedNode->Tag))->value;
			 OutputFormat senderOutputFormat(ruleSet->getDatabase(), rowid);
			 InputRule newInputRule = senderOutputFormat.addInputRule("new InputRule");

			 loadObjectTree();
		 }
private: System::Void tsShowAll_Click(System::Object^  sender, System::EventArgs^  e) {
			 tsShowAll->Checked = true;
			 tsShowMatched->Checked = false;
			 tsShowFailed->Checked = false;
		 }
private: System::Void tsShowMatched_Click(System::Object^  sender, System::EventArgs^  e) {
			 tsShowAll->Checked = false;
			 tsShowMatched->Checked = true;
			 tsShowFailed->Checked = false;
		 }
private: System::Void tsShowFailed_Click(System::Object^  sender, System::EventArgs^  e) {
			 tsShowAll->Checked = false;
			 tsShowMatched->Checked = false;
			 tsShowFailed->Checked = true;
		 }
#pragma region Drag&Drop Support
private: System::Void guiFileList_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 /*array<String^>^ formats =  e->Data->GetFormats() ;*/

			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 //! files were droped on this control
				 array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData( "FileNameW" ));
				 for(int i=0; i<files->Length; i++)
					 addFileToFileList(files[i]);	
			 }
		 }
private: System::Void guiFileList_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 e->Effect = DragDropEffects::Link;
				 return;
			 }
			 e->Effect = DragDropEffects::None;
		 }
#pragma endregion

private: System::Void tsBtnAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 dlgAddFiles->ShowDialog();
		 }
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 openFileDialog->ShowDialog();
		 }
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //! \todo Ask yourself if we really need this Save button?
		 }
private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveAsFileDialog->FileName = toClrString(ruleSet->getFilename());
			 saveAsFileDialog->ShowDialog();
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
		 }
private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 newFileDialog->FileName = "Unnamed Ruleset.db3";
			 newFileDialog->ShowDialog();
		 }
private: System::Void saveFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

		 }
private: System::Void saveAsFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 if(!e->Cancel) {
				 System::IO::File::Copy(toClrString(ruleSet->getFilename()), saveAsFileDialog->FileName);
				 loadRuleset(saveAsFileDialog->FileName);
				 loadObjectTree();
			 }
		 }
private: System::Void newFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 if(!e->Cancel) {
				createRuleSet(newFileDialog->FileName);
				loadRuleset(newFileDialog->FileName);
				loadObjectTree();
			 }
		 }
private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 if(!e->Cancel) {
				 loadRuleset(openFileDialog->FileName);
				 loadObjectTree();
			 }
		 }
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
#pragma endregion
