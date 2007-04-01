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



    // Form Controls




	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;
	private: System::Windows::Forms::ContextMenuStrip^  cmsInputRules;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiDeleteInputRule;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmiEditInputRule;
	private: System::Windows::Forms::OpenFileDialog^  dlgAddFiles;






















	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  dateiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  extrasToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label4;





	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::ListBox^  listBox1;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ApplicationForm::typeid));
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->cmsInputRules = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tsmiDeleteInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmiEditInputRule = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->dlgAddFiles = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->extrasToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			splitContainer1->Panel1->SuspendLayout();
			splitContainer1->Panel2->SuspendLayout();
			splitContainer1->SuspendLayout();
			this->cmsInputRules->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
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
			splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			splitContainer1->Panel2->Controls->Add(this->toolStrip1);
			splitContainer1->Panel2->Controls->Add(this->statusStrip1);
			splitContainer1->Panel2->Controls->Add(this->listBox1);
			splitContainer1->Size = System::Drawing::Size(854, 408);
			splitContainer1->SplitterDistance = 403;
			splitContainer1->TabIndex = 7;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(16, 28);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(418, 355);
			this->listBox1->TabIndex = 0;
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
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->dateiToolStripMenuItem, 
				this->bearbeitenToolStripMenuItem, this->extrasToolStripMenuItem, this->toolStripMenuItem1});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(879, 24);
			this->menuStrip1->TabIndex = 12;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->openToolStripMenuItem, 
				this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->exitToolStripMenuItem});
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->dateiToolStripMenuItem->Text = L"File";
			this->dateiToolStripMenuItem->Click += gcnew System::EventHandler(this, &ApplicationForm::dateiToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->cutToolStripMenuItem, 
				this->copyToolStripMenuItem, this->pasteToolStripMenuItem, this->deleteToolStripMenuItem});
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->bearbeitenToolStripMenuItem->Text = L"Edit";
			// 
			// extrasToolStripMenuItem
			// 
			this->extrasToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->optionsToolStripMenuItem});
			this->extrasToolStripMenuItem->Name = L"extrasToolStripMenuItem";
			this->extrasToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->extrasToolStripMenuItem->Text = L"Extras";
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
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(105, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"&Open";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveToolStripMenuItem->Text = L"&Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveAsToolStripMenuItem->Text = L"Save &As";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"&Exit";
			// 
			// cutToolStripMenuItem
			// 
			this->cutToolStripMenuItem->Name = L"cutToolStripMenuItem";
			this->cutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->cutToolStripMenuItem->Text = L"&Cut";
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->pasteToolStripMenuItem->Text = L"&Paste";
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->copyToolStripMenuItem->Text = L"&Copy";
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->deleteToolStripMenuItem->Text = L"&Delete";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->optionsToolStripMenuItem->Text = L"&Options";
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->treeView1);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->tableLayoutPanel1);
			this->splitContainer2->Size = System::Drawing::Size(403, 408);
			this->splitContainer2->SplitterDistance = 199;
			this->splitContainer2->TabIndex = 0;
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(3, 3);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(397, 193);
			this->treeView1->TabIndex = 0;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Location = System::Drawing::Point(0, 386);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(447, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripLabel1, 
				this->toolStripButton1, this->toolStripButton2, this->toolStripButton3});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(447, 25);
			this->toolStrip1->TabIndex = 2;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Tag = L"";
			this->toolStripButton1->Text = L"All";
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(34, 22);
			this->toolStripLabel1->Text = L"Show";
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(53, 22);
			this->toolStripButton2->Text = L"Matched";
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(39, 22);
			this->toolStripButton3->Text = L"Failed";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label4->Location = System::Drawing::Point(106, 20);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(186, 18);
			this->label4->TabIndex = 3;
			this->label4->Text = L"label4";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->Location = System::Drawing::Point(106, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(186, 18);
			this->label2->TabIndex = 1;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label3->Location = System::Drawing::Point(3, 20);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(97, 18);
			this->label3->TabIndex = 2;
			this->label3->Text = L"label3";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				103)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 1, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(52, 29);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(295, 173);
			this->tableLayoutPanel1->TabIndex = 0;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ApplicationForm::tableLayoutPanel1_Paint);
			// 
			// ApplicationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(879, 509);
			this->Controls->Add(splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"ApplicationForm";
			this->Opacity = 0.95;
			this->Text = L"Renamer Pre-Alpha";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ApplicationForm::ApplicationForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ApplicationForm::ApplicationForm_Load);
			splitContainer1->Panel1->ResumeLayout(false);
			splitContainer1->Panel2->ResumeLayout(false);
			splitContainer1->Panel2->PerformLayout();
			splitContainer1->ResumeLayout(false);
			this->cmsInputRules->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->ResumeLayout(false);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
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
private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
};
}
#pragma endregion
