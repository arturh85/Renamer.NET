#pragma region Header
#pragma once

#include <vcclr.h>
#include "ruleset.h"
#include "inputRule.h"
#include "clrUtility.h"
#include "stlUtility.h"
#include "stdlib.h"
#include "error.h"

#include "ListBoxItem.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::IO;

#pragma endregion
#pragma region Declaration
namespace RenamerNET {

	/// <summary>
	/// Zusammenfassung für WizardForm
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie auch
	///          die Ressourcendateiname-Eigenschaft für das Tool zur Kompilierung verwalteter Ressourcen ändern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abhängt.
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class WizardForm : public System::Windows::Forms::Form
	{
	public:
		WizardForm(void)
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
		~WizardForm()
		{
			if (components)
			{
				delete components;
			}
		}
#pragma endregion
#pragma region Variables
	protected: enum class Step {
				   STEP_RULESET_SELECT = 0,
				   STEP_BEFORE_REPLACEMENTS = 1,
				   STEP_OUTPUTFORMAT_SELECT = 2,
				   STEP_INPUTRULES_SELECT = 3,
				   STEP_GEMS_SELECT = 4,
				   STEP_AFTER_REPLACEMENTS = 5,
				   STEP_RENAME = 6,
				   STEP_MAX = 7
			   };

    // Business Logic Member Variables
	private: Ruleset* mRuleset;
	private: sqlite_int64 mOutputFormatID;
	private: sqlite_int64 mInputRuleID;
	private: sqlite_int64 mGemID;

	protected: Step mStep;
	protected: Step mMaxStep;
	protected: System::Collections::Generic::List<Panel^>^ stepPanelList;
	protected: System::Collections::Generic::List<ToolStripButton^>^ stepButtonList;

	// Tool Strip with Buttons for each Step
	private: System::Windows::Forms::ToolStrip^  tsStepButtons;
	private: System::Windows::Forms::ToolStripButton^  tsStepRuleset;
	private: System::Windows::Forms::ToolStripButton^  tsStepBeforeReplacements;
	private: System::Windows::Forms::ToolStripButton^  tsStepOutputFormat;
	private: System::Windows::Forms::ToolStripButton^  tsStepInputRule;
	private: System::Windows::Forms::ToolStripButton^  tsStepGems;
	private: System::Windows::Forms::ToolStripButton^  tsStepAfterReplacements;
	private: System::Windows::Forms::ToolStripButton^  tsStepRename;


    // Parent Panel for Step Panels
	private: System::Windows::Forms::Panel^  panelStepContent;
	// Panels for each Step
	private: System::Windows::Forms::Panel^  panelStepRuleset;
	private: System::Windows::Forms::Panel^  panelStepBeforeReplacements;
	private: System::Windows::Forms::Panel^  panelStepOutputFormat;
	private: System::Windows::Forms::Panel^  panelStepInputRule;
	private: System::Windows::Forms::Panel^  panelStepGems;
	private: System::Windows::Forms::Panel^  panelStepAfterReplacements;
	private: System::Windows::Forms::Panel^  panelStepRename;

    // Buttons for switching between the steps
	private: System::Windows::Forms::Button^  buttonPreviousStep;
	private: System::Windows::Forms::Button^  buttonNextStep;

	// Controls for the Panel 'Ruleset'
	private: System::Windows::Forms::Button^  buttonRulesetOpenDialog;
	private: System::Windows::Forms::ComboBox^  cboRulesets;
	private: System::Windows::Forms::SaveFileDialog^  saveRulesetFileDialog;
	private: System::Windows::Forms::OpenFileDialog^  openRulesetFileDialog;

	private: System::Windows::Forms::SplitContainer^  splitContainer;

	// Controls for the Panel 'OutputFormat'


	// Container for the Panel of the current Step (Panel Child will have Dock = Fill)

		
    // List of all files relevant to current ruleset


	// tool strip for file list operations








    // to do: categorize the remaining Controls or make them non-member variables



	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;







	private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Panel^  panelFilelist;







private: System::Windows::Forms::Panel^  panelNavigation;
private: System::Windows::Forms::Button^  buttonRulesetSaveDialog;
private: System::Windows::Forms::DataGridView^  gridBeforeReplacements;












private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::ImageList^  imageList1;


private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::ToolStrip^  tsOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsAddOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDeleteOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateOutputFormat;
private: System::Windows::Forms::ListBox^  lstOutputFormat;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::ToolStrip^  toolStrip1;
private: System::Windows::Forms::ToolStripButton^  tsSaveOutputFormat;

private: System::Windows::Forms::TextBox^  txtOutputFormat;
private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::ListBox^  lstInputRules;
private: System::Windows::Forms::Panel^  panel4;
private: System::Windows::Forms::ToolStrip^  toolStrip3;
private: System::Windows::Forms::ToolStripButton^  tsSaveInputRule;
private: System::Windows::Forms::RichTextBox^  txtInputRule;

private: System::Windows::Forms::ToolStrip^  tsInputRuleButtons;

private: System::Windows::Forms::ToolStripButton^  tsAddInputRule;
private: System::Windows::Forms::ToolStripButton^  tsRemoveInputRule;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateInputRule;
private: System::Windows::Forms::Panel^  panel5;
private: System::Windows::Forms::ToolStrip^  tsFileList;
private: System::Windows::Forms::ToolStripButton^  tsAddFiles;
private: System::Windows::Forms::ToolStripButton^  tsRemoveFileFromList;
private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
private: System::Windows::Forms::ListView^  fileList;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GroupID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Search;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Replace;
private: System::Windows::Forms::OpenFileDialog^  fileListopenFileDiag;
private: System::Windows::Forms::ColumnHeader^  chFile;












	// .net container
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WizardForm::typeid));
			this->tsStepButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsStepRuleset = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepBeforeReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepGems = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepAfterReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepRename = (gcnew System::Windows::Forms::ToolStripButton());
			this->openRulesetFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->panelStepContent = (gcnew System::Windows::Forms::Panel());
			this->panelStepBeforeReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridBeforeReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Search = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Replace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panelStepInputRule = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->tsInputRuleButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstInputRules = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panelStepOutputFormat = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tsOutputFormat = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDeleteOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstOutputFormat = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panelStepRename = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->panelStepRuleset = (gcnew System::Windows::Forms::Panel());
			this->buttonRulesetSaveDialog = (gcnew System::Windows::Forms::Button());
			this->buttonRulesetOpenDialog = (gcnew System::Windows::Forms::Button());
			this->cboRulesets = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panelStepGems = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->panelStepAfterReplacements = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panelFilelist = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->tsFileList = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveFileFromList = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->panelNavigation = (gcnew System::Windows::Forms::Panel());
			this->buttonPreviousStep = (gcnew System::Windows::Forms::Button());
			this->buttonNextStep = (gcnew System::Windows::Forms::Button());
			this->saveRulesetFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->fileListopenFileDiag = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
			this->tsStepButtons->SuspendLayout();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->panelStepContent->SuspendLayout();
			this->panelStepBeforeReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->BeginInit();
			this->panelStepInputRule->SuspendLayout();
			this->panel4->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tsInputRuleButtons->SuspendLayout();
			this->panelStepOutputFormat->SuspendLayout();
			this->panel2->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tsOutputFormat->SuspendLayout();
			this->panelStepRename->SuspendLayout();
			this->panelStepRuleset->SuspendLayout();
			this->panelStepGems->SuspendLayout();
			this->panelStepAfterReplacements->SuspendLayout();
			this->panelFilelist->SuspendLayout();
			this->panel5->SuspendLayout();
			this->tsFileList->SuspendLayout();
			this->panelNavigation->SuspendLayout();
			this->SuspendLayout();
			// 
			// tsStepButtons
			// 
			this->tsStepButtons->Dock = System::Windows::Forms::DockStyle::Left;
			this->tsStepButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsStepButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->tsStepRuleset, 
				this->tsStepBeforeReplacements, this->tsStepOutputFormat, this->tsStepInputRule, this->tsStepGems, this->tsStepAfterReplacements, 
				this->tsStepRename});
			this->tsStepButtons->Location = System::Drawing::Point(0, 0);
			this->tsStepButtons->Name = L"tsStepButtons";
			this->tsStepButtons->Size = System::Drawing::Size(123, 477);
			this->tsStepButtons->TabIndex = 4;
			this->tsStepButtons->Text = L"toolStrip1";
			// 
			// tsStepRuleset
			// 
			this->tsStepRuleset->Checked = true;
			this->tsStepRuleset->CheckState = System::Windows::Forms::CheckState::Checked;
			this->tsStepRuleset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepRuleset->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepRuleset.Image")));
			this->tsStepRuleset->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepRuleset->Name = L"tsStepRuleset";
			this->tsStepRuleset->Size = System::Drawing::Size(120, 20);
			this->tsStepRuleset->Text = L"Ruleset";
			this->tsStepRuleset->Click += gcnew System::EventHandler(this, &WizardForm::tsStepRuleset_Click);
			// 
			// tsStepBeforeReplacements
			// 
			this->tsStepBeforeReplacements->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepBeforeReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepBeforeReplacements.Image")));
			this->tsStepBeforeReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepBeforeReplacements->Name = L"tsStepBeforeReplacements";
			this->tsStepBeforeReplacements->Size = System::Drawing::Size(120, 20);
			this->tsStepBeforeReplacements->Text = L"Before Replacements";
			this->tsStepBeforeReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepBeforeReplacements_Click);
			// 
			// tsStepOutputFormat
			// 
			this->tsStepOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepOutputFormat.Image")));
			this->tsStepOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepOutputFormat->Name = L"tsStepOutputFormat";
			this->tsStepOutputFormat->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
			this->tsStepOutputFormat->Size = System::Drawing::Size(120, 20);
			this->tsStepOutputFormat->Text = L"Output Formats";
			this->tsStepOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsStepOutputFormat_Click);
			// 
			// tsStepInputRule
			// 
			this->tsStepInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepInputRule.Image")));
			this->tsStepInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepInputRule->Name = L"tsStepInputRule";
			this->tsStepInputRule->Size = System::Drawing::Size(120, 20);
			this->tsStepInputRule->Text = L"Input Rules";
			this->tsStepInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsStepInputRule_Click);
			// 
			// tsStepGems
			// 
			this->tsStepGems->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepGems->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepGems.Image")));
			this->tsStepGems->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepGems->Name = L"tsStepGems";
			this->tsStepGems->Size = System::Drawing::Size(120, 20);
			this->tsStepGems->Text = L"Gems";
			this->tsStepGems->Click += gcnew System::EventHandler(this, &WizardForm::tsStepGems_Click);
			// 
			// tsStepAfterReplacements
			// 
			this->tsStepAfterReplacements->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepAfterReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepAfterReplacements.Image")));
			this->tsStepAfterReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepAfterReplacements->Name = L"tsStepAfterReplacements";
			this->tsStepAfterReplacements->Size = System::Drawing::Size(120, 20);
			this->tsStepAfterReplacements->Text = L"After Replacements";
			this->tsStepAfterReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepAfterReplacements_Click);
			// 
			// tsStepRename
			// 
			this->tsStepRename->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepRename->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepRename.Image")));
			this->tsStepRename->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepRename->Name = L"tsStepRename";
			this->tsStepRename->Size = System::Drawing::Size(120, 20);
			this->tsStepRename->Text = L"Rename";
			// 
			// openRulesetFileDialog
			// 
			this->openRulesetFileDialog->CheckFileExists = false;
			this->openRulesetFileDialog->DefaultExt = L"ruleset";
			this->openRulesetFileDialog->FileName = L"default.rulset";
			this->openRulesetFileDialog->Filter = L"Ruleset Dateien|*.ruleset";
			this->openRulesetFileDialog->Title = L"Select Ruleset File";
			this->openRulesetFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::openRulesetFileDialog_FileOk);
			// 
			// splitContainer
			// 
			this->splitContainer->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->splitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer->Location = System::Drawing::Point(123, 0);
			this->splitContainer->Name = L"splitContainer";
			this->splitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->panelStepContent);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Controls->Add(this->panelFilelist);
			this->splitContainer->Panel2->Controls->Add(this->panelNavigation);
			this->splitContainer->Size = System::Drawing::Size(459, 477);
			this->splitContainer->SplitterDistance = 273;
			this->splitContainer->TabIndex = 9;
			// 
			// panelStepContent
			// 
			this->panelStepContent->Controls->Add(this->panelStepBeforeReplacements);
			this->panelStepContent->Controls->Add(this->panelStepInputRule);
			this->panelStepContent->Controls->Add(this->panelStepOutputFormat);
			this->panelStepContent->Controls->Add(this->panelStepRename);
			this->panelStepContent->Controls->Add(this->panelStepRuleset);
			this->panelStepContent->Controls->Add(this->panelStepGems);
			this->panelStepContent->Controls->Add(this->panelStepAfterReplacements);
			this->panelStepContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelStepContent->Location = System::Drawing::Point(0, 0);
			this->panelStepContent->Name = L"panelStepContent";
			this->panelStepContent->Size = System::Drawing::Size(457, 271);
			this->panelStepContent->TabIndex = 7;
			// 
			// panelStepBeforeReplacements
			// 
			this->panelStepBeforeReplacements->Controls->Add(this->gridBeforeReplacements);
			this->panelStepBeforeReplacements->Controls->Add(this->label4);
			this->panelStepBeforeReplacements->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelStepBeforeReplacements->Location = System::Drawing::Point(0, 0);
			this->panelStepBeforeReplacements->Name = L"panelStepBeforeReplacements";
			this->panelStepBeforeReplacements->Size = System::Drawing::Size(457, 271);
			this->panelStepBeforeReplacements->TabIndex = 6;
			// 
			// gridBeforeReplacements
			// 
			this->gridBeforeReplacements->AllowDrop = true;
			this->gridBeforeReplacements->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridBeforeReplacements->BackgroundColor = System::Drawing::SystemColors::Control;
			this->gridBeforeReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridBeforeReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ID, 
				this->GroupID, this->Search, this->Replace});
			this->gridBeforeReplacements->Location = System::Drawing::Point(18, 43);
			this->gridBeforeReplacements->Name = L"gridBeforeReplacements";
			this->gridBeforeReplacements->Size = System::Drawing::Size(427, 217);
			this->gridBeforeReplacements->TabIndex = 1;
			// 
			// ID
			// 
			this->ID->HeaderText = L"ID";
			this->ID->Name = L"ID";
			this->ID->Visible = false;
			// 
			// GroupID
			// 
			this->GroupID->HeaderText = L"GroupID";
			this->GroupID->Name = L"GroupID";
			this->GroupID->Visible = false;
			// 
			// Search
			// 
			this->Search->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Search->HeaderText = L"Search";
			this->Search->Name = L"Search";
			// 
			// Replace
			// 
			this->Replace->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Replace->HeaderText = L"Replace";
			this->Replace->Name = L"Replace";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(15, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(112, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Before Replacements:";
			// 
			// panelStepInputRule
			// 
			this->panelStepInputRule->Controls->Add(this->panel4);
			this->panelStepInputRule->Controls->Add(this->panel3);
			this->panelStepInputRule->Controls->Add(this->label3);
			this->panelStepInputRule->Location = System::Drawing::Point(273, 76);
			this->panelStepInputRule->Name = L"panelStepInputRule";
			this->panelStepInputRule->Size = System::Drawing::Size(110, 52);
			this->panelStepInputRule->TabIndex = 5;
			// 
			// panel4
			// 
			this->panel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel4->Controls->Add(this->toolStrip3);
			this->panel4->Controls->Add(this->txtInputRule);
			this->panel4->Location = System::Drawing::Point(6, 200);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(101, 31);
			this->panel4->TabIndex = 4;
			// 
			// toolStrip3
			// 
			this->toolStrip3->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolStrip3->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveInputRule});
			this->toolStrip3->Location = System::Drawing::Point(77, 0);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(24, 31);
			this->toolStrip3->TabIndex = 4;
			this->toolStrip3->Text = L"toolStrip3";
			// 
			// tsSaveInputRule
			// 
			this->tsSaveInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsSaveInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsSaveInputRule.Image")));
			this->tsSaveInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsSaveInputRule->Name = L"tsSaveInputRule";
			this->tsSaveInputRule->Size = System::Drawing::Size(21, 20);
			this->tsSaveInputRule->Text = L"toolStripButton1";
			this->tsSaveInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveInputRule_Click);
			// 
			// txtInputRule
			// 
			this->txtInputRule->Location = System::Drawing::Point(3, 0);
			this->txtInputRule->Multiline = false;
			this->txtInputRule->Name = L"txtInputRule";
			this->txtInputRule->Size = System::Drawing::Size(418, 20);
			this->txtInputRule->TabIndex = 3;
			this->txtInputRule->Text = L"";
			this->txtInputRule->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtInputRule_KeyDown);
			this->txtInputRule->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtInputRule_TextChanged);
			// 
			// panel3
			// 
			this->panel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel3->Controls->Add(this->tsInputRuleButtons);
			this->panel3->Controls->Add(this->lstInputRules);
			this->panel3->Location = System::Drawing::Point(6, 41);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(101, 158);
			this->panel3->TabIndex = 3;
			// 
			// tsInputRuleButtons
			// 
			this->tsInputRuleButtons->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsInputRuleButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsInputRuleButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddInputRule, 
				this->tsRemoveInputRule, this->tsDuplicateInputRule});
			this->tsInputRuleButtons->Location = System::Drawing::Point(77, 0);
			this->tsInputRuleButtons->Name = L"tsInputRuleButtons";
			this->tsInputRuleButtons->Size = System::Drawing::Size(24, 158);
			this->tsInputRuleButtons->TabIndex = 3;
			this->tsInputRuleButtons->Text = L"toolStrip2";
			// 
			// tsAddInputRule
			// 
			this->tsAddInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddInputRule.Image")));
			this->tsAddInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddInputRule->Name = L"tsAddInputRule";
			this->tsAddInputRule->Size = System::Drawing::Size(21, 20);
			this->tsAddInputRule->Text = L"toolStripButton1";
			this->tsAddInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsAddInputRule_Click);
			// 
			// tsRemoveInputRule
			// 
			this->tsRemoveInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsRemoveInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsRemoveInputRule.Image")));
			this->tsRemoveInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsRemoveInputRule->Name = L"tsRemoveInputRule";
			this->tsRemoveInputRule->Size = System::Drawing::Size(21, 20);
			this->tsRemoveInputRule->Text = L"toolStripButton2";
			this->tsRemoveInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveInputRule_Click);
			// 
			// tsDuplicateInputRule
			// 
			this->tsDuplicateInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsDuplicateInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDuplicateInputRule.Image")));
			this->tsDuplicateInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDuplicateInputRule->Name = L"tsDuplicateInputRule";
			this->tsDuplicateInputRule->Size = System::Drawing::Size(21, 20);
			this->tsDuplicateInputRule->Text = L"toolStripButton3";
			this->tsDuplicateInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateInputRule_Click);
			// 
			// lstInputRules
			// 
			this->lstInputRules->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstInputRules->FormattingEnabled = true;
			this->lstInputRules->Location = System::Drawing::Point(3, 4);
			this->lstInputRules->Name = L"lstInputRules";
			this->lstInputRules->Size = System::Drawing::Size(71, 147);
			this->lstInputRules->TabIndex = 2;
			this->lstInputRules->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstInputRules_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 11);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(92, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Choose input rule:";
			// 
			// panelStepOutputFormat
			// 
			this->panelStepOutputFormat->Controls->Add(this->panel2);
			this->panelStepOutputFormat->Controls->Add(this->panel1);
			this->panelStepOutputFormat->Controls->Add(this->label2);
			this->panelStepOutputFormat->Location = System::Drawing::Point(14, 11);
			this->panelStepOutputFormat->Name = L"panelStepOutputFormat";
			this->panelStepOutputFormat->Size = System::Drawing::Size(192, 29);
			this->panelStepOutputFormat->TabIndex = 4;
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->Controls->Add(this->toolStrip1);
			this->panel2->Controls->Add(this->txtOutputFormat);
			this->panel2->Location = System::Drawing::Point(6, 215);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(183, 34);
			this->panel2->TabIndex = 6;
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveOutputFormat});
			this->toolStrip1->Location = System::Drawing::Point(159, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(24, 34);
			this->toolStrip1->TabIndex = 6;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// tsSaveOutputFormat
			// 
			this->tsSaveOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsSaveOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsSaveOutputFormat.Image")));
			this->tsSaveOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsSaveOutputFormat->Name = L"tsSaveOutputFormat";
			this->tsSaveOutputFormat->Size = System::Drawing::Size(21, 20);
			this->tsSaveOutputFormat->Text = L"Save";
			this->tsSaveOutputFormat->ToolTipText = L"Save Output Format";
			this->tsSaveOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveOutputFormat_Click);
			// 
			// txtOutputFormat
			// 
			this->txtOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFormat->Location = System::Drawing::Point(3, 3);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(153, 20);
			this->txtOutputFormat->TabIndex = 5;
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtOutputFormat_TextChanged);
			this->txtOutputFormat->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtOutputFormat_KeyDown);
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->tsOutputFormat);
			this->panel1->Controls->Add(this->lstOutputFormat);
			this->panel1->Location = System::Drawing::Point(6, 28);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(183, 187);
			this->panel1->TabIndex = 5;
			// 
			// tsOutputFormat
			// 
			this->tsOutputFormat->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsOutputFormat->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsOutputFormat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddOutputFormat, 
				this->tsDeleteOutputFormat, this->tsDuplicateOutputFormat});
			this->tsOutputFormat->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->tsOutputFormat->Location = System::Drawing::Point(159, 0);
			this->tsOutputFormat->Name = L"tsOutputFormat";
			this->tsOutputFormat->Size = System::Drawing::Size(24, 187);
			this->tsOutputFormat->TabIndex = 4;
			this->tsOutputFormat->Text = L"toolStrip3";
			// 
			// tsAddOutputFormat
			// 
			this->tsAddOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddOutputFormat.Image")));
			this->tsAddOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddOutputFormat->Name = L"tsAddOutputFormat";
			this->tsAddOutputFormat->Size = System::Drawing::Size(21, 20);
			this->tsAddOutputFormat->Text = L"Add";
			this->tsAddOutputFormat->ToolTipText = L"Add Output Format";
			this->tsAddOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsAddOutputFormat_Click);
			// 
			// tsDeleteOutputFormat
			// 
			this->tsDeleteOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsDeleteOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDeleteOutputFormat.Image")));
			this->tsDeleteOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDeleteOutputFormat->Name = L"tsDeleteOutputFormat";
			this->tsDeleteOutputFormat->Size = System::Drawing::Size(21, 20);
			this->tsDeleteOutputFormat->Text = L"Delete Output Format";
			this->tsDeleteOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDeleteOutputFormat_Click);
			// 
			// tsDuplicateOutputFormat
			// 
			this->tsDuplicateOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsDuplicateOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDuplicateOutputFormat.Image")));
			this->tsDuplicateOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDuplicateOutputFormat->Name = L"tsDuplicateOutputFormat";
			this->tsDuplicateOutputFormat->Size = System::Drawing::Size(21, 20);
			this->tsDuplicateOutputFormat->Text = L"Duplicate Output Format";
			this->tsDuplicateOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateOutputFormat_Click);
			// 
			// lstOutputFormat
			// 
			this->lstOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstOutputFormat->Location = System::Drawing::Point(3, 0);
			this->lstOutputFormat->Name = L"lstOutputFormat";
			this->lstOutputFormat->Size = System::Drawing::Size(153, 173);
			this->lstOutputFormat->TabIndex = 2;
			this->lstOutputFormat->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstOutputFormat_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(18, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(113, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Choose Output Format";
			// 
			// panelStepRename
			// 
			this->panelStepRename->Controls->Add(this->label7);
			this->panelStepRename->Location = System::Drawing::Point(372, 171);
			this->panelStepRename->Name = L"panelStepRename";
			this->panelStepRename->Size = System::Drawing::Size(172, 79);
			this->panelStepRename->TabIndex = 9;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(20, 15);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(47, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Rename";
			// 
			// panelStepRuleset
			// 
			this->panelStepRuleset->Controls->Add(this->buttonRulesetSaveDialog);
			this->panelStepRuleset->Controls->Add(this->buttonRulesetOpenDialog);
			this->panelStepRuleset->Controls->Add(this->cboRulesets);
			this->panelStepRuleset->Controls->Add(this->label1);
			this->panelStepRuleset->Location = System::Drawing::Point(323, 15);
			this->panelStepRuleset->Name = L"panelStepRuleset";
			this->panelStepRuleset->Size = System::Drawing::Size(192, 37);
			this->panelStepRuleset->TabIndex = 3;
			// 
			// buttonRulesetSaveDialog
			// 
			this->buttonRulesetSaveDialog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonRulesetSaveDialog->Location = System::Drawing::Point(24, 58);
			this->buttonRulesetSaveDialog->Name = L"buttonRulesetSaveDialog";
			this->buttonRulesetSaveDialog->Size = System::Drawing::Size(75, 23);
			this->buttonRulesetSaveDialog->TabIndex = 6;
			this->buttonRulesetSaveDialog->Text = L"Save";
			this->buttonRulesetSaveDialog->UseVisualStyleBackColor = true;
			this->buttonRulesetSaveDialog->Click += gcnew System::EventHandler(this, &WizardForm::buttonRulesetSaveDialog_Click);
			// 
			// buttonRulesetOpenDialog
			// 
			this->buttonRulesetOpenDialog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonRulesetOpenDialog->Location = System::Drawing::Point(105, 58);
			this->buttonRulesetOpenDialog->Name = L"buttonRulesetOpenDialog";
			this->buttonRulesetOpenDialog->Size = System::Drawing::Size(75, 23);
			this->buttonRulesetOpenDialog->TabIndex = 5;
			this->buttonRulesetOpenDialog->Text = L"Open";
			this->buttonRulesetOpenDialog->UseVisualStyleBackColor = true;
			this->buttonRulesetOpenDialog->Click += gcnew System::EventHandler(this, &WizardForm::buttonRulesetOpenDialog_Click);
			// 
			// cboRulesets
			// 
			this->cboRulesets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboRulesets->FormattingEnabled = true;
			this->cboRulesets->Location = System::Drawing::Point(18, 58);
			this->cboRulesets->Name = L"cboRulesets";
			this->cboRulesets->Size = System::Drawing::Size(0, 21);
			this->cboRulesets->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Choose ruleset:";
			// 
			// panelStepGems
			// 
			this->panelStepGems->Controls->Add(this->label6);
			this->panelStepGems->Location = System::Drawing::Point(14, 171);
			this->panelStepGems->Name = L"panelStepGems";
			this->panelStepGems->Size = System::Drawing::Size(118, 57);
			this->panelStepGems->TabIndex = 8;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(16, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(74, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Choose gems:";
			// 
			// panelStepAfterReplacements
			// 
			this->panelStepAfterReplacements->Controls->Add(this->label5);
			this->panelStepAfterReplacements->Location = System::Drawing::Point(172, 171);
			this->panelStepAfterReplacements->Name = L"panelStepAfterReplacements";
			this->panelStepAfterReplacements->Size = System::Drawing::Size(150, 47);
			this->panelStepAfterReplacements->TabIndex = 7;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 16);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(100, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"After Replacements";
			// 
			// panelFilelist
			// 
			this->panelFilelist->Controls->Add(this->panel5);
			this->panelFilelist->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelFilelist->Location = System::Drawing::Point(0, 31);
			this->panelFilelist->Name = L"panelFilelist";
			this->panelFilelist->Size = System::Drawing::Size(457, 167);
			this->panelFilelist->TabIndex = 10;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->tsFileList);
			this->panel5->Controls->Add(this->fileList);
			this->panel5->Location = System::Drawing::Point(6, 6);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(448, 158);
			this->panel5->TabIndex = 2;
			// 
			// tsFileList
			// 
			this->tsFileList->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsFileList->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsFileList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddFiles, this->tsRemoveFileFromList, 
				this->toolStripButton7});
			this->tsFileList->Location = System::Drawing::Point(416, 0);
			this->tsFileList->Name = L"tsFileList";
			this->tsFileList->Size = System::Drawing::Size(32, 158);
			this->tsFileList->TabIndex = 2;
			this->tsFileList->Text = L"toolStrip2";
			// 
			// tsAddFiles
			// 
			this->tsAddFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddFiles->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddFiles.Image")));
			this->tsAddFiles->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddFiles->Name = L"tsAddFiles";
			this->tsAddFiles->Size = System::Drawing::Size(29, 20);
			this->tsAddFiles->Text = L"toolStripButton5";
			this->tsAddFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsAddFiles_Click);
			// 
			// tsRemoveFileFromList
			// 
			this->tsRemoveFileFromList->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsRemoveFileFromList->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsRemoveFileFromList.Image")));
			this->tsRemoveFileFromList->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsRemoveFileFromList->Name = L"tsRemoveFileFromList";
			this->tsRemoveFileFromList->Size = System::Drawing::Size(29, 20);
			this->tsRemoveFileFromList->Text = L"toolStripButton6";
			this->tsRemoveFileFromList->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveFileFromList_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(29, 20);
			this->toolStripButton7->Text = L"toolStripButton7";
			// 
			// fileList
			// 
			this->fileList->AllowDrop = true;
			this->fileList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->fileList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->chFile});
			this->fileList->FullRowSelect = true;
			this->fileList->Location = System::Drawing::Point(3, 3);
			this->fileList->MultiSelect = false;
			this->fileList->Name = L"fileList";
			this->fileList->ShowGroups = false;
			this->fileList->Size = System::Drawing::Size(418, 152);
			this->fileList->TabIndex = 1;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::Details;
			// 
			// panelNavigation
			// 
			this->panelNavigation->Controls->Add(this->buttonPreviousStep);
			this->panelNavigation->Controls->Add(this->buttonNextStep);
			this->panelNavigation->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelNavigation->Location = System::Drawing::Point(0, 0);
			this->panelNavigation->Name = L"panelNavigation";
			this->panelNavigation->Size = System::Drawing::Size(457, 31);
			this->panelNavigation->TabIndex = 9;
			// 
			// buttonPreviousStep
			// 
			this->buttonPreviousStep->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPreviousStep->Location = System::Drawing::Point(289, 7);
			this->buttonPreviousStep->Name = L"buttonPreviousStep";
			this->buttonPreviousStep->Size = System::Drawing::Size(75, 23);
			this->buttonPreviousStep->TabIndex = 1;
			this->buttonPreviousStep->Text = L"previous";
			this->buttonPreviousStep->UseVisualStyleBackColor = true;
			this->buttonPreviousStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonPreviousStep_Click);
			// 
			// buttonNextStep
			// 
			this->buttonNextStep->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonNextStep->Location = System::Drawing::Point(370, 7);
			this->buttonNextStep->Name = L"buttonNextStep";
			this->buttonNextStep->Size = System::Drawing::Size(75, 23);
			this->buttonNextStep->TabIndex = 0;
			this->buttonNextStep->Text = L"next";
			this->buttonNextStep->UseVisualStyleBackColor = true;
			this->buttonNextStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonNextStep_Click);
			// 
			// saveRulesetFileDialog
			// 
			this->saveRulesetFileDialog->DefaultExt = L"ruleset";
			this->saveRulesetFileDialog->Filter = L"Ruleset Files|*.ruleset";
			this->saveRulesetFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::saveRulesetFileDialog_FileOk);
			// 
			// imageList1
			// 
			this->imageList1->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// fileListopenFileDiag
			// 
			this->fileListopenFileDiag->FileName = L"*.*";
			this->fileListopenFileDiag->Filter = L"All files|*.*";
			this->fileListopenFileDiag->Multiselect = true;
			this->fileListopenFileDiag->RestoreDirectory = true;
			this->fileListopenFileDiag->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::fileListopenFileDiag_FileOk);
			// 
			// chFile
			// 
			this->chFile->Text = L"File";
			this->chFile->Width = 200;
			// 
			// WizardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 477);
			this->Controls->Add(this->splitContainer);
			this->Controls->Add(this->tsStepButtons);
			this->Name = L"WizardForm";
			this->Text = L"Renamer";
			this->Load += gcnew System::EventHandler(this, &WizardForm::WizardForm_Load);
			this->tsStepButtons->ResumeLayout(false);
			this->tsStepButtons->PerformLayout();
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			this->splitContainer->ResumeLayout(false);
			this->panelStepContent->ResumeLayout(false);
			this->panelStepBeforeReplacements->ResumeLayout(false);
			this->panelStepBeforeReplacements->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->EndInit();
			this->panelStepInputRule->ResumeLayout(false);
			this->panelStepInputRule->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->tsInputRuleButtons->ResumeLayout(false);
			this->tsInputRuleButtons->PerformLayout();
			this->panelStepOutputFormat->ResumeLayout(false);
			this->panelStepOutputFormat->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tsOutputFormat->ResumeLayout(false);
			this->tsOutputFormat->PerformLayout();
			this->panelStepRename->ResumeLayout(false);
			this->panelStepRename->PerformLayout();
			this->panelStepRuleset->ResumeLayout(false);
			this->panelStepRuleset->PerformLayout();
			this->panelStepGems->ResumeLayout(false);
			this->panelStepGems->PerformLayout();
			this->panelStepAfterReplacements->ResumeLayout(false);
			this->panelStepAfterReplacements->PerformLayout();
			this->panelFilelist->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->tsFileList->ResumeLayout(false);
			this->tsFileList->PerformLayout();
			this->panelNavigation->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Business Code
		void createRuleset(String^ rulesetFileName) {
			String^ rulesetName = System::IO::Path::GetFileNameWithoutExtension(rulesetFileName);
			exAssert(rulesetName != "");

			try{
				Ruleset* rs = new Ruleset(toStdWString(rulesetFileName));
				setRuleset(rs);
			}

			catch(exception& e) {
				String^ message = L"Exception: ";
				message += toClrString(e.what());
				MessageBox::Show(message, L"Exception!" );
				return;
			}
		}

		bool loadRuleset(String^ filename) 
		{
			if(!System::IO::File::Exists(filename)) {
				return false;
			}

			exAssert(filename != "");
			String^ rulesetName = System::IO::Path::GetFileNameWithoutExtension(filename);
			exAssert(rulesetName != "");


			
			try {
				Ruleset* rs = new Ruleset(toStdWString(filename));
				setRuleset(rs);
			}

			catch(exception& e) {
				String^ message = L"Exception: ";
				message += toClrString(e.what());
				MessageBox::Show(message, L"Exception!!!!" );
				return false;
			}

			return true;
		}

/*		void renameRuleset(int rulesetIndex, String^ newRulesetName) {
			if(rulesetList[rulesetIndex]) {
				String^ oldRulesetName = toClrString(rulesetList[rulesetIndex]->getName());
				String^ oldRulesetFileName = toClrString(rulesetList[rulesetIndex]->getFilename());
				String^ newRulesetFileName = oldRulesetFileName->Substring(0, oldRulesetFileName->LastIndexOf(L'\\')+1) + newRulesetName +  oldRulesetFileName->Substring(oldRulesetFileName->LastIndexOf(L'.'));
				// if newRulesetName is invalid, don't rename ...
				if(newRulesetName == "" || System::IO::File::Exists(newRulesetFileName))
					return ;
				delete rulesetList[rulesetIndex];
				File::Move(oldRulesetFileName, newRulesetFileName);
				string s = toStdString(newRulesetName);
				rulesetList[rulesetIndex] = new Ruleset(toStdWString(newRulesetFileName));
			}
		}*/

		void setRuleset(Ruleset* ruleset) {
			if(mRuleset)
				delete mRuleset;
			mRuleset = ruleset;

			refreshOutputFormatList();
			setOutputFormat(0);
			setInputRule(0);
			setGem(0);
		}

		void setOutputFormat(sqlite_int64 id) {
			mOutputFormatID = id;
			refreshInputRuleList();
			refreshMaxStep();
		}

		void setInputRule(sqlite_int64 id) {
			mInputRuleID = id;
			refreshMaxStep();
		}

		void setGem(sqlite_int64 id) {
			mGemID = id;
			refreshMaxStep();
		}

		//! :-)
		void refreshMaxStep() {
			if(mRuleset != NULL) {
				if(mOutputFormatID > 0) {
					if(mInputRuleID > 0) {
						if(mGemID > 0) {
							setMaxStep(Step::STEP_MAX);
						}

						else {
							setMaxStep(Step::STEP_GEMS_SELECT);
						}
					}

					else {
						setMaxStep(Step::STEP_INPUTRULES_SELECT);
					}
				}
				else {
					setMaxStep(Step::STEP_OUTPUTFORMAT_SELECT);
				}
			}
			else {
				setMaxStep(Step::STEP_RULESET_SELECT);
			}
		}

		void deleteRuleset(String^ rulesetFilename) {
			File::Delete(rulesetFilename);
		}

		void addFileToFileList( String^ pathToFile )
		{
			String^ fileName = System::IO::Path::GetFileNameWithoutExtension(pathToFile);
			ListViewItem^ item = gcnew ListViewItem(fileName);
			item->Tag = pathToFile;
			fileList->Items->Add(item);
		}

		void setMaxStep(Step newMaxStep) {
			mMaxStep = newMaxStep;
			setStep(mStep);
		}

		void setStep(Step newStep) {
			if(newStep > mMaxStep) {
				if(mStep == Step::STEP_RULESET_SELECT && newStep == Step::STEP_BEFORE_REPLACEMENTS) {
					if(mRuleset != NULL) {
						mMaxStep = Step::STEP_OUTPUTFORMAT_SELECT;
						refreshOutputFormatList();
					}
				}
				if(mStep == Step::STEP_OUTPUTFORMAT_SELECT && newStep == Step::STEP_INPUTRULES_SELECT) {
					if(mRuleset && mOutputFormatID > 0) {
						mMaxStep = Step::STEP_INPUTRULES_SELECT;
					}
				}
				if(mStep == Step::STEP_INPUTRULES_SELECT && newStep == Step::STEP_GEMS_SELECT) {
					if(mRuleset && mOutputFormatID > 0) {
						mMaxStep = Step::STEP_GEMS_SELECT;
					}
				}
			}

			if(int(newStep) < 0 || int(newStep) >= int(Step::STEP_MAX) || newStep > mMaxStep) {
				return ;
			}

			// onEnter: beforeReplacements
			if(newStep == Step::STEP_BEFORE_REPLACEMENTS && mStep != Step::STEP_BEFORE_REPLACEMENTS) {
				loadBeforeReplacements();	
			}

			// onLeave: beforeReplacements
			if(mStep == Step::STEP_BEFORE_REPLACEMENTS && newStep != Step::STEP_BEFORE_REPLACEMENTS) {
				saveBeforeReplacements();
			}

			// onEnter: outputFormat
			if(newStep == Step::STEP_OUTPUTFORMAT_SELECT && mStep != Step::STEP_OUTPUTFORMAT_SELECT) {
				refreshOutputFormatList();			 
				tsSaveOutputFormat->Visible = false;
			}

			// onEnter: inputRule
			else if(newStep == Step::STEP_INPUTRULES_SELECT && mStep != Step::STEP_INPUTRULES_SELECT) {
				refreshInputRuleList();
				tsSaveInputRule->Visible = false;
			}

			mStep = newStep;

			for(int i=0; i<int(Step::STEP_MAX); i++) {
				stepPanelList[i]->Visible = false;
				stepPanelList[i]->Dock = DockStyle::None;
				stepButtonList[i]->Checked = false;

				if(i > int(mMaxStep)) {
					stepButtonList[i]->Enabled = false;
				}

				else {
					stepButtonList[i]->Enabled = true;
				}
			}

			stepPanelList[int(mStep)]->Visible = true;
			stepPanelList[int(mStep)]->Dock = DockStyle::Fill;
			stepButtonList[int(mStep)]->Checked = true;
		}

		void saveBeforeReplacements() {
			if(mRuleset == NULL) return ;
			Replacements replacements = mRuleset->getBeforeReplacements();

			int rowCount = gridBeforeReplacements->Rows->Count;
			vector<int> replacementsWhichWereNotDeleted ;
			for(int i=0; i<gridBeforeReplacements->Rows->Count; i++) {
				if(gridBeforeReplacements->Rows[i]->Cells[0]->Value == nullptr) {
					String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
					String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
					if(search != nullptr && replace != nullptr) {
						Replacement replacement = replacements.addReplacement(toStdString(search), toStdString(replace));
						replacementsWhichWereNotDeleted.push_back(replacement.getRowId());
						gridBeforeReplacements->Rows[i]->Cells[0]->Value = gcnew Int32(replacement.getRowId());
						gridBeforeReplacements->Rows[i]->Cells[1]->Value = gcnew Int32(replacement.getGroupId());
					}
				}

				else {
					int rowid = (int)((Int32^)gridBeforeReplacements->Rows[i]->Cells[0]->Value);
					String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
					String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
					if(search != nullptr && replace != nullptr) {
						replacementsWhichWereNotDeleted.push_back(rowid);
						Replacement replacement(mRuleset->getDatabase(), rowid);
						replacement.setRegex(toStdString(search));
						replacement.setReplacement(toStdString(replace));
					}
				}
			}

			vector<Replacement> replacementVector = replacements.getReplacements();
			for(unsigned int i=0; i<replacementVector.size(); i++) {
				bool found = false;
				for(unsigned int j=0; j<replacementsWhichWereNotDeleted.size(); j++) {
					if(replacementVector[i].getRowId() == (sqlite_int64) replacementsWhichWereNotDeleted[j]) {
						found = true;
					}
				}

				if(found == false) {
					Replacement replacement(mRuleset->getDatabase(), replacementVector[i].getRowId());
					replacement.remove();
				}
			}
		}

		void loadBeforeReplacements() {
			if(mRuleset == NULL) return ;
			gridBeforeReplacements->Rows->Clear();
			Replacements replacements = mRuleset->getBeforeReplacements();
			vector<Replacement> replacementVector = replacements.getReplacements();

			for(unsigned int i=0; i<replacementVector.size(); i++) {
				cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
				values[0] = gcnew Int32 (replacementVector[i].getRowId());
				values[1] = gcnew Int32 (replacementVector[i].getGroupId());
				values[2] = toClrString(replacementVector[i].getRegex().str());
				values[3] = toClrString(replacementVector[i].getReplacement());

				gridBeforeReplacements->Rows->Add(values);
			}
		}

		void refreshOutputFormatList() {
			if(mRuleset) {
				vector<OutputFormat> outputFormatVector = mRuleset->getOutputFormats();
				
				lstOutputFormat->Items->Clear();				
				for(unsigned int i=0; i<outputFormatVector.size(); i++) {
					ListBoxItem^ lbi = gcnew ListBoxItem();
					lbi->Text = toClrString(outputFormatVector[i].getFormat());
					lbi->Tag = gcnew _PairStringInt(lbi->Text, outputFormatVector[i].getRowId());
					lstOutputFormat->Items->Add(lbi);
				}
			}
		}

		void refreshInputRuleList() {
			if(mRuleset && mOutputFormatID > 0) {
				OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
				vector<InputRule> inputRuleVector = outputFormat.getInputRules();

				lstInputRules->Items->Clear();				
				for(unsigned int i=0; i<inputRuleVector.size(); i++) {
					ListBoxItem^ lbi = gcnew ListBoxItem();
					lbi->Text = toClrString(inputRuleVector[i].getRegex());
					lbi->Tag = gcnew _PairStringInt(lbi->Text, inputRuleVector[i].getRowId());
					lstInputRules->Items->Add(lbi);
				}
			}
		}

#pragma endregion
#pragma region Event Handlers
	#pragma region Global Event Handlers
	private: System::Void WizardForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 stepPanelList = gcnew System::Collections::Generic::List<Panel^>();
				 stepPanelList->Add(panelStepRuleset);
				 stepPanelList->Add(panelStepBeforeReplacements);
				 stepPanelList->Add(panelStepOutputFormat);
				 stepPanelList->Add(panelStepInputRule);
				 stepPanelList->Add(panelStepGems);
				 stepPanelList->Add(panelStepAfterReplacements);
				 stepPanelList->Add(panelStepRename);

				 stepButtonList = gcnew System::Collections::Generic::List<ToolStripButton^>();
				 stepButtonList->Add(tsStepRuleset);
				 stepButtonList->Add(tsStepBeforeReplacements);
				 stepButtonList->Add(tsStepOutputFormat);
				 stepButtonList->Add(tsStepInputRule);
				 stepButtonList->Add(tsStepGems);
				 stepButtonList->Add(tsStepAfterReplacements);
				 stepButtonList->Add(tsStepRename);

				 //! select first step
				 mStep = Step::STEP_RULESET_SELECT;
				 setMaxStep(Step::STEP_RULESET_SELECT);
			 }
private: System::Void buttonNextStep_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step(int(mStep) + 1));
		 }
private: System::Void buttonPreviousStep_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step(int(mStep) - 1));
		 }
private: System::Void tsStepRuleset_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_RULESET_SELECT);
		 }
private: System::Void tsStepOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_OUTPUTFORMAT_SELECT);
		 }
private: System::Void tsStepBeforeReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_BEFORE_REPLACEMENTS);
		 }
private: System::Void tsStepInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_INPUTRULES_SELECT);
		 }
private: System::Void tsStepAfterReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_AFTER_REPLACEMENTS);
		 }
private: System::Void tsStepGems_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_GEMS_SELECT);
		 }
private: System::Void buttonRulesetOpenDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 openRulesetFileDialog->ShowDialog();
		 }
private: System::Void buttonRulesetSaveDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveRulesetFileDialog->ShowDialog();
		 }
private: System::Void fileList_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 //! files were droped on this control
				 array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData( "FileNameW" ));
				 for(int i=0; i<files->Length; i++)
					 addFileToFileList(files[i]);	
			 }
		 }
private: System::Void fileList_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" ) )
			 {
				 e->Effect = DragDropEffects::Link;
				 return;
			 }
			 e->Effect = DragDropEffects::None;
		 }
#pragma endregion
	#pragma region Step: Ruleset
private: System::Void openRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 String^ rulesetFilename = openRulesetFileDialog->FileName;
			 loadRuleset(rulesetFilename);
			 cboRulesets->Text = toClrString(mRuleset->getName());
		 }
private: System::Void saveRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 String^ rulesetFilename = saveRulesetFileDialog->FileName;
			 createRuleset(rulesetFilename);
			 cboRulesets->Text = toClrString(mRuleset->getName());
		 }
#pragma endregion
	#pragma region Step: OutputFormat
private: System::Void tsAddOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {			 
			 OutputFormat outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat("new");
			 refreshOutputFormatList();
		 }
private: System::Void tsDeleteOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 OutputFormat outputFormat(mRuleset->getDatabase(), rowid);
			 outputFormat.remove();
			 refreshOutputFormatList();
			 refreshMaxStep();
		 }
private: System::Void tsDuplicateOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 OutputFormat outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStdString(lstOutputFormat->SelectedItem->ToString()));
			 refreshOutputFormatList();
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1) 
				 return ;
			 tsSaveOutputFormat->Visible = true;
		 }
private: System::Void txtOutputFormat_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Return && tsSaveOutputFormat->Visible) {
					tsSaveOutputFormat_Click(nullptr, nullptr);
			 }
		 }
private: System::Void tsSaveOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 OutputFormat outputFormat(mRuleset->getDatabase(), rowid);

			 outputFormat.setFormat(toStdString(txtOutputFormat->Text));

			 int selectedIndex = lstOutputFormat->SelectedIndex;
			 refreshOutputFormatList();
			 lstOutputFormat->SelectedIndex = selectedIndex;
			 tsSaveOutputFormat->Visible = false;
		 }
private: System::Void lstOutputFormat_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstOutputFormat->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;
			 txtOutputFormat->Text = properties->key;
			 mOutputFormatID = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 tsSaveOutputFormat->Visible = false;
		 }
#pragma endregion
	#pragma region Step: InputRule
private: System::Void tsAddInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			 InputRule inputRule = outputFormat.addInputRule("new");
			 refreshInputRuleList();
		 }
private: System::Void tsRemoveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 InputRule inputRule(mRuleset->getDatabase(), rowid );
			 inputRule.remove();
			 refreshInputRuleList();
			 refreshMaxStep();
		 }
private: System::Void tsDuplicateInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			 InputRule inputRule = outputFormat.addInputRule(toStdString(lstInputRules->SelectedItem->ToString()));
			 refreshInputRuleList();
		 }
private: System::Void tsSaveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 InputRule inputRule(mRuleset->getDatabase(), rowid);

			 inputRule.setRegex(toStdString(txtInputRule->Text));

			 int selectedIndex = lstInputRules->SelectedIndex;
			 refreshInputRuleList();
			 lstInputRules->SelectedIndex = selectedIndex;
			 tsSaveInputRule->Visible = false;
		 }
private: System::Void lstInputRules_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstInputRules->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;
			 txtInputRule->Text = properties->key;
			 mInputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 tsSaveInputRule->Visible = false;
		 }
private: System::Void txtInputRule_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 tsSaveInputRule->Visible = true;
		 }
private: System::Void txtInputRule_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Return && tsSaveInputRule->Visible) {
				 tsSaveInputRule_Click(nullptr, nullptr);
			 }
		 }
#pragma endregion


/*	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
//MessageBox::Show("Hallo Welt!");

// Create a new DataTable.
//System.Data.DataTable table = new DataTable("ParentTable");
System::Data::DataTable^ table = gcnew DataTable("ParentTable");
// Declare variables for DataColumn and DataRow objects.
DataColumn^ column;
//				 DataRow^ row;

// Create new DataColumn, set DataType, 
// ColumnName and add to DataTable.    
column = gcnew DataColumn();
column->DataType = System::Type::GetType("System.Int32");
column->ColumnName = "id";
column->ReadOnly = true;
column->Unique = true;
column->AutoIncrement = true;
// Add the Column to the DataColumnCollection.
table->Columns->Add(column);

// Create second column.
column = gcnew DataColumn();
column->DataType = System::Type::GetType("System.String");
column->ColumnName = "ParentItem";
column->AutoIncrement = false;
column->Caption = "ParentItem";
column->ReadOnly = false;
column->Unique = false;

// Add the column to the table.
table->Columns->Add(column);

// Make the ID column the primary key column.
/*DataColumn[]^ PrimaryKeyColumns;
PrimaryKeyColumns = gcnew DataColumn[1];
PrimaryKeyColumns[0] = table->Columns["id"];
table->PrimaryKey = PrimaryKeyColumns;


//				 dataGridView1->DataSource = table;
//				 dataGridView1->Allow

}*/

private: System::Void fileListopenFileDiag_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 for(int i=0; i<fileListopenFileDiag->FileNames->Length; i++) {
				addFileToFileList(fileListopenFileDiag->FileNames[i]);
			 }
		 }
private: System::Void tsAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			fileListopenFileDiag->ShowDialog();
		 }
private: System::Void tsRemoveFileFromList_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(fileList->Items[0]->FocusedItem != nullptr)
				fileList->Items->Remove(fileList->Items.FocusedItem);
		 }
};
// --- don't delete after this line (and one line before this line) --- //
}
#pragma endregion



