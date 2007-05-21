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
				   RULESET_SELECT = 0,
				   BEFORE_REPLACEMENTS = 1,
				   OUTPUTFORMAT_SELECT = 2,
				   INPUTRULES_SELECT = 3,
				   GEMS_SELECT = 4,
				   AFTER_REPLACEMENTS = 5,
				   RENAME = 6,
				   MAX = 7
			   };

    // Business Logic Member Variables
	private: Ruleset* mRuleset;
	private: sqlite_int64 mOutputFormatID;
	private: sqlite_int64 mInputRuleID;
	private: sqlite_int64 mGemID;

	private: List<String^> mFiles;

	private: Step mStep;
	private: Step mMaxStep;
	private: List<Panel^>^ mStepPanelList;
	private: List<ToolStripButton^>^ mStepButtonList;

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



	// Controls for the Panel 'Ruleset'


	private: System::Windows::Forms::SaveFileDialog^  saveRulesetFileDialog;
	private: System::Windows::Forms::OpenFileDialog^  openRulesetFileDialog;

	private: System::Windows::Forms::SplitContainer^  splitContainer;



	// Controls for the Panel 'OutputFormat'


	// Container for the Panel of the current Step (Panel Child will have Dock = Fill)

		
    // List of all files relevant to current ruleset


	// tool strip for file list operations








    // to do: categorize the remaining Controls or make them non-member variables






private: System::Windows::Forms::Panel^  panelFilelist;



private: System::Windows::Forms::DataGridView^  gridBeforeReplacements;


private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::ToolStrip^  tsOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsAddOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDeleteOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateOutputFormat;
private: System::Windows::Forms::ListBox^  lstOutputFormat;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::ToolStrip^  toolStrip1;
private: System::Windows::Forms::ToolStripButton^  tsSaveOutputFormat;

private: System::Windows::Forms::RichTextBox^  txtOutputFormat;
private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::ListBox^  lstInputRules;
private: System::Windows::Forms::Panel^  panel4;


private: System::Windows::Forms::RichTextBox^  txtInputRule;

private: System::Windows::Forms::ToolStrip^  tsInputRuleButtons;

private: System::Windows::Forms::ToolStripButton^  tsAddInputRule;
private: System::Windows::Forms::ToolStripButton^  tsRemoveInputRule;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateInputRule;
private: System::Windows::Forms::Panel^  panel5;
private: System::Windows::Forms::ToolStrip^  tsFileList;
private: System::Windows::Forms::ToolStripButton^  tsAddFiles;
private: System::Windows::Forms::ToolStripButton^  tsRemoveFileFromList;
private: System::Windows::Forms::ToolStripButton^  tsApplyChanges;

private: System::Windows::Forms::ListView^  fileList;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GroupID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Search;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Replace;
private: System::Windows::Forms::OpenFileDialog^  fileListopenFileDiag;
private: System::Windows::Forms::ColumnHeader^  chFile;
private: System::Windows::Forms::Panel^  panelNavigation;
private: System::Windows::Forms::Button^  buttonPreviousStep;
private: System::Windows::Forms::Button^  buttonNextStep;
private: System::Windows::Forms::DataGridView^  gridAfterReplacements;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
private: System::Windows::Forms::Panel^  panel6;
private: System::Windows::Forms::ToolStrip^  tsRuleset;

private: System::Windows::Forms::ToolStripButton^  tsLoadRulesetDialog;
private: System::Windows::Forms::ToolStripButton^  tsSaveRulesetDialog;
private: System::Windows::Forms::ComboBox^  cboRulesets;
private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
private: System::Windows::Forms::ToolStrip^  toolStrip3;
private: System::Windows::Forms::ToolStripButton^  tsSaveInputRule;
private: System::Windows::Forms::DataGridView^  gridGems;


private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
private: System::Windows::Forms::RichTextBox^  txtGemInputRule;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GemColumnPosition;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  GemColumnGem;


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
			System::Windows::Forms::Label^  label1;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WizardForm::typeid));
			System::Windows::Forms::Label^  label5;
			System::Windows::Forms::Label^  label7;
			System::Windows::Forms::Label^  label4;
			System::Windows::Forms::Label^  label3;
			System::Windows::Forms::Label^  label2;
			System::Windows::Forms::Label^  label6;
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
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
			this->panelStepGems = (gcnew System::Windows::Forms::Panel());
			this->txtGemInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->gridGems = (gcnew System::Windows::Forms::DataGridView());
			this->GemColumnPosition = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GemColumnGem = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->panelStepOutputFormat = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtOutputFormat = (gcnew System::Windows::Forms::RichTextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tsOutputFormat = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDeleteOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstOutputFormat = (gcnew System::Windows::Forms::ListBox());
			this->panelStepInputRule = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->tsInputRuleButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstInputRules = (gcnew System::Windows::Forms::ListBox());
			this->panelStepRuleset = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->tsRuleset = (gcnew System::Windows::Forms::ToolStrip());
			this->tsLoadRulesetDialog = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsSaveRulesetDialog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->cboRulesets = (gcnew System::Windows::Forms::ComboBox());
			this->panelStepAfterReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridAfterReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelStepRename = (gcnew System::Windows::Forms::Panel());
			this->panelNavigation = (gcnew System::Windows::Forms::Panel());
			this->buttonPreviousStep = (gcnew System::Windows::Forms::Button());
			this->buttonNextStep = (gcnew System::Windows::Forms::Button());
			this->panelStepBeforeReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridBeforeReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Search = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Replace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelFilelist = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->tsFileList = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveFileFromList = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsApplyChanges = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
			this->saveRulesetFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->fileListopenFileDiag = (gcnew System::Windows::Forms::OpenFileDialog());
			label1 = (gcnew System::Windows::Forms::Label());
			label5 = (gcnew System::Windows::Forms::Label());
			label7 = (gcnew System::Windows::Forms::Label());
			label4 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label6 = (gcnew System::Windows::Forms::Label());
			this->tsStepButtons->SuspendLayout();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->panelStepContent->SuspendLayout();
			this->panelStepGems->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->BeginInit();
			this->panelStepOutputFormat->SuspendLayout();
			this->panel2->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tsOutputFormat->SuspendLayout();
			this->panelStepInputRule->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->tsInputRuleButtons->SuspendLayout();
			this->panelStepRuleset->SuspendLayout();
			this->panel6->SuspendLayout();
			this->tsRuleset->SuspendLayout();
			this->panelStepAfterReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->BeginInit();
			this->panelStepRename->SuspendLayout();
			this->panelNavigation->SuspendLayout();
			this->panelStepBeforeReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->BeginInit();
			this->panelFilelist->SuspendLayout();
			this->panel5->SuspendLayout();
			this->tsFileList->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			label1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label1.Image")));
			label1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label1->Location = System::Drawing::Point(5, 2);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(65, 22);
			label1->TabIndex = 3;
			label1->Text = L"Ruleset";
			label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label5
			// 
			label5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label5.Image")));
			label5->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label5->Location = System::Drawing::Point(6, 7);
			label5->Name = L"label5";
			label5->Size = System::Drawing::Size(122, 13);
			label5->TabIndex = 0;
			label5->Text = L"After Replacements";
			label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label7
			// 
			label7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label7.Image")));
			label7->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label7->Location = System::Drawing::Point(6, 7);
			label7->Name = L"label7";
			label7->Size = System::Drawing::Size(69, 13);
			label7->TabIndex = 0;
			label7->Text = L"Rename";
			label7->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label4
			// 
			label4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label4.Image")));
			label4->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label4->Location = System::Drawing::Point(5, 7);
			label4->Name = L"label4";
			label4->Size = System::Drawing::Size(131, 13);
			label4->TabIndex = 0;
			label4->Text = L"Before Replacements";
			label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label3
			// 
			label3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label3.Image")));
			label3->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label3->Location = System::Drawing::Point(5, 7);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(79, 13);
			label3->TabIndex = 0;
			label3->Text = L"Input rules";
			label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label2
			// 
			label2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label2.Image")));
			label2->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label2->Location = System::Drawing::Point(4, 7);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(102, 13);
			label2->TabIndex = 0;
			label2->Text = L"Output Formats";
			label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label6
			// 
			label6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"label6.Image")));
			label6->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			label6->Location = System::Drawing::Point(5, 7);
			label6->Name = L"label6";
			label6->Size = System::Drawing::Size(56, 13);
			label6->TabIndex = 0;
			label6->Text = L"Gems";
			label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
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
			this->tsStepButtons->Size = System::Drawing::Size(139, 410);
			this->tsStepButtons->TabIndex = 4;
			this->tsStepButtons->Text = L"toolStrip1";
			// 
			// tsStepRuleset
			// 
			this->tsStepRuleset->Checked = true;
			this->tsStepRuleset->CheckState = System::Windows::Forms::CheckState::Checked;
			this->tsStepRuleset->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepRuleset.Image")));
			this->tsStepRuleset->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepRuleset->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepRuleset->Name = L"tsStepRuleset";
			this->tsStepRuleset->Size = System::Drawing::Size(136, 20);
			this->tsStepRuleset->Text = L"Ruleset";
			this->tsStepRuleset->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepRuleset->Click += gcnew System::EventHandler(this, &WizardForm::tsStepRuleset_Click);
			// 
			// tsStepBeforeReplacements
			// 
			this->tsStepBeforeReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepBeforeReplacements.Image")));
			this->tsStepBeforeReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepBeforeReplacements->Name = L"tsStepBeforeReplacements";
			this->tsStepBeforeReplacements->Size = System::Drawing::Size(136, 20);
			this->tsStepBeforeReplacements->Text = L"Before Replacements";
			this->tsStepBeforeReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepBeforeReplacements_Click);
			// 
			// tsStepOutputFormat
			// 
			this->tsStepOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepOutputFormat.Image")));
			this->tsStepOutputFormat->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepOutputFormat->Name = L"tsStepOutputFormat";
			this->tsStepOutputFormat->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
			this->tsStepOutputFormat->Size = System::Drawing::Size(136, 20);
			this->tsStepOutputFormat->Text = L"Output Formats";
			this->tsStepOutputFormat->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->tsStepOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsStepOutputFormat_Click);
			// 
			// tsStepInputRule
			// 
			this->tsStepInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepInputRule.Image")));
			this->tsStepInputRule->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepInputRule->Name = L"tsStepInputRule";
			this->tsStepInputRule->Size = System::Drawing::Size(136, 20);
			this->tsStepInputRule->Text = L"Input Rules";
			this->tsStepInputRule->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsStepInputRule_Click);
			// 
			// tsStepGems
			// 
			this->tsStepGems->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepGems.Image")));
			this->tsStepGems->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepGems->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepGems->Name = L"tsStepGems";
			this->tsStepGems->Size = System::Drawing::Size(136, 20);
			this->tsStepGems->Text = L"Gems";
			this->tsStepGems->Click += gcnew System::EventHandler(this, &WizardForm::tsStepGems_Click);
			// 
			// tsStepAfterReplacements
			// 
			this->tsStepAfterReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepAfterReplacements.Image")));
			this->tsStepAfterReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepAfterReplacements->Name = L"tsStepAfterReplacements";
			this->tsStepAfterReplacements->Size = System::Drawing::Size(136, 20);
			this->tsStepAfterReplacements->Text = L"After Replacements";
			this->tsStepAfterReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepAfterReplacements_Click);
			// 
			// tsStepRename
			// 
			this->tsStepRename->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepRename.Image")));
			this->tsStepRename->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->tsStepRename->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepRename->Name = L"tsStepRename";
			this->tsStepRename->Size = System::Drawing::Size(136, 20);
			this->tsStepRename->Text = L"Rename";
			this->tsStepRename->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
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
			this->splitContainer->Location = System::Drawing::Point(139, 0);
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
			this->splitContainer->Size = System::Drawing::Size(667, 410);
			this->splitContainer->SplitterDistance = 306;
			this->splitContainer->TabIndex = 9;
			// 
			// panelStepContent
			// 
			this->panelStepContent->Controls->Add(this->panelStepGems);
			this->panelStepContent->Controls->Add(this->panelStepOutputFormat);
			this->panelStepContent->Controls->Add(this->panelStepInputRule);
			this->panelStepContent->Controls->Add(this->panelStepRuleset);
			this->panelStepContent->Controls->Add(this->panelStepAfterReplacements);
			this->panelStepContent->Controls->Add(this->panelStepRename);
			this->panelStepContent->Controls->Add(this->panelNavigation);
			this->panelStepContent->Controls->Add(this->panelStepBeforeReplacements);
			this->panelStepContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelStepContent->Location = System::Drawing::Point(0, 0);
			this->panelStepContent->Name = L"panelStepContent";
			this->panelStepContent->Size = System::Drawing::Size(665, 304);
			this->panelStepContent->TabIndex = 7;
			// 
			// panelStepGems
			// 
			this->panelStepGems->Controls->Add(this->txtGemInputRule);
			this->panelStepGems->Controls->Add(this->gridGems);
			this->panelStepGems->Controls->Add(label6);
			this->panelStepGems->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelStepGems->Location = System::Drawing::Point(0, 0);
			this->panelStepGems->Name = L"panelStepGems";
			this->panelStepGems->Size = System::Drawing::Size(665, 271);
			this->panelStepGems->TabIndex = 8;
			// 
			// txtGemInputRule
			// 
			this->txtGemInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtGemInputRule->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtGemInputRule->Location = System::Drawing::Point(9, 239);
			this->txtGemInputRule->Multiline = false;
			this->txtGemInputRule->Name = L"txtGemInputRule";
			this->txtGemInputRule->ReadOnly = true;
			this->txtGemInputRule->Size = System::Drawing::Size(626, 22);
			this->txtGemInputRule->TabIndex = 2;
			this->txtGemInputRule->Text = L"";
			// 
			// gridGems
			// 
			this->gridGems->AllowUserToAddRows = false;
			this->gridGems->AllowUserToDeleteRows = false;
			this->gridGems->AllowUserToResizeRows = false;
			this->gridGems->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridGems->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridGems->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->gridGems->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridGems->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->GemColumnPosition, 
				this->GemColumnGem});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridGems->DefaultCellStyle = dataGridViewCellStyle2;
			this->gridGems->Location = System::Drawing::Point(9, 23);
			this->gridGems->MultiSelect = false;
			this->gridGems->Name = L"gridGems";
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridGems->RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->gridGems->Size = System::Drawing::Size(626, 210);
			this->gridGems->TabIndex = 1;
			this->gridGems->SelectionChanged += gcnew System::EventHandler(this, &WizardForm::gridGems_SelectionChanged);
			// 
			// GemColumnPosition
			// 
			this->GemColumnPosition->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->GemColumnPosition->HeaderText = L"Position";
			this->GemColumnPosition->Name = L"GemColumnPosition";
			this->GemColumnPosition->ReadOnly = true;
			// 
			// GemColumnGem
			// 
			this->GemColumnGem->HeaderText = L"Gem";
			this->GemColumnGem->Name = L"GemColumnGem";
			this->GemColumnGem->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->GemColumnGem->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			// 
			// panelStepOutputFormat
			// 
			this->panelStepOutputFormat->Controls->Add(this->panel2);
			this->panelStepOutputFormat->Controls->Add(this->panel1);
			this->panelStepOutputFormat->Controls->Add(label2);
			this->panelStepOutputFormat->Location = System::Drawing::Point(14, 115);
			this->panelStepOutputFormat->Name = L"panelStepOutputFormat";
			this->panelStepOutputFormat->Size = System::Drawing::Size(337, 61);
			this->panelStepOutputFormat->TabIndex = 4;
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->Controls->Add(this->toolStrip1);
			this->panel2->Controls->Add(this->txtOutputFormat);
			this->panel2->Location = System::Drawing::Point(7, 18);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(328, 26);
			this->panel2->TabIndex = 6;
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveOutputFormat});
			this->toolStrip1->Location = System::Drawing::Point(304, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(24, 26);
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
			this->txtOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFormat->Location = System::Drawing::Point(2, 3);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(298, 20);
			this->txtOutputFormat->TabIndex = 5;
			this->txtOutputFormat->Text = L"";
			this->txtOutputFormat->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtOutputFormat_KeyDown);
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtOutputFormat_TextChanged);
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->tsOutputFormat);
			this->panel1->Controls->Add(this->lstOutputFormat);
			this->panel1->Location = System::Drawing::Point(6, 24);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(328, 0);
			this->panel1->TabIndex = 5;
			// 
			// tsOutputFormat
			// 
			this->tsOutputFormat->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsOutputFormat->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsOutputFormat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddOutputFormat, 
				this->tsDeleteOutputFormat, this->tsDuplicateOutputFormat});
			this->tsOutputFormat->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->tsOutputFormat->Location = System::Drawing::Point(304, 0);
			this->tsOutputFormat->Name = L"tsOutputFormat";
			this->tsOutputFormat->Size = System::Drawing::Size(24, 0);
			this->tsOutputFormat->TabIndex = 4;
			this->tsOutputFormat->Text = L"toolStrip3";
			// 
			// tsAddOutputFormat
			// 
			this->tsAddOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddOutputFormat.Image")));
			this->tsAddOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddOutputFormat->Name = L"tsAddOutputFormat";
			this->tsAddOutputFormat->Size = System::Drawing::Size(23, 20);
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
			this->tsDeleteOutputFormat->Size = System::Drawing::Size(23, 20);
			this->tsDeleteOutputFormat->Text = L"Delete Output Format";
			this->tsDeleteOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDeleteOutputFormat_Click);
			// 
			// tsDuplicateOutputFormat
			// 
			this->tsDuplicateOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsDuplicateOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDuplicateOutputFormat.Image")));
			this->tsDuplicateOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDuplicateOutputFormat->Name = L"tsDuplicateOutputFormat";
			this->tsDuplicateOutputFormat->Size = System::Drawing::Size(23, 20);
			this->tsDuplicateOutputFormat->Text = L"Duplicate Output Format";
			this->tsDuplicateOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateOutputFormat_Click);
			// 
			// lstOutputFormat
			// 
			this->lstOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstOutputFormat->Location = System::Drawing::Point(3, 3);
			this->lstOutputFormat->Name = L"lstOutputFormat";
			this->lstOutputFormat->Size = System::Drawing::Size(298, 4);
			this->lstOutputFormat->TabIndex = 2;
			this->lstOutputFormat->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstOutputFormat_SelectedIndexChanged);
			// 
			// panelStepInputRule
			// 
			this->panelStepInputRule->Controls->Add(this->panel3);
			this->panelStepInputRule->Controls->Add(label3);
			this->panelStepInputRule->Location = System::Drawing::Point(14, 78);
			this->panelStepInputRule->Name = L"panelStepInputRule";
			this->panelStepInputRule->Size = System::Drawing::Size(144, 27);
			this->panelStepInputRule->TabIndex = 5;
			// 
			// panel3
			// 
			this->panel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel3->Controls->Add(this->panel4);
			this->panel3->Controls->Add(this->tsInputRuleButtons);
			this->panel3->Controls->Add(this->lstInputRules);
			this->panel3->Location = System::Drawing::Point(6, 23);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(135, 0);
			this->panel3->TabIndex = 3;
			// 
			// panel4
			// 
			this->panel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel4->Controls->Add(this->toolStrip3);
			this->panel4->Controls->Add(this->txtInputRule);
			this->panel4->Location = System::Drawing::Point(3, 32);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(135, 28);
			this->panel4->TabIndex = 4;
			// 
			// toolStrip3
			// 
			this->toolStrip3->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolStrip3->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveInputRule});
			this->toolStrip3->Location = System::Drawing::Point(111, 0);
			this->toolStrip3->Name = L"toolStrip3";
			this->toolStrip3->Size = System::Drawing::Size(24, 28);
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
			this->txtInputRule->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtInputRule->Location = System::Drawing::Point(3, 0);
			this->txtInputRule->Multiline = false;
			this->txtInputRule->Name = L"txtInputRule";
			this->txtInputRule->Size = System::Drawing::Size(102, 20);
			this->txtInputRule->TabIndex = 3;
			this->txtInputRule->Text = L"";
			this->txtInputRule->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtInputRule_KeyDown);
			this->txtInputRule->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtInputRule_TextChanged);
			// 
			// tsInputRuleButtons
			// 
			this->tsInputRuleButtons->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsInputRuleButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsInputRuleButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddInputRule, 
				this->tsRemoveInputRule, this->tsDuplicateInputRule});
			this->tsInputRuleButtons->Location = System::Drawing::Point(111, 0);
			this->tsInputRuleButtons->Name = L"tsInputRuleButtons";
			this->tsInputRuleButtons->Size = System::Drawing::Size(24, 0);
			this->tsInputRuleButtons->TabIndex = 3;
			this->tsInputRuleButtons->Text = L"toolStrip2";
			// 
			// tsAddInputRule
			// 
			this->tsAddInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddInputRule.Image")));
			this->tsAddInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddInputRule->Name = L"tsAddInputRule";
			this->tsAddInputRule->Size = System::Drawing::Size(23, 20);
			this->tsAddInputRule->Text = L"toolStripButton1";
			this->tsAddInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsAddInputRule_Click);
			// 
			// tsRemoveInputRule
			// 
			this->tsRemoveInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsRemoveInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsRemoveInputRule.Image")));
			this->tsRemoveInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsRemoveInputRule->Name = L"tsRemoveInputRule";
			this->tsRemoveInputRule->Size = System::Drawing::Size(23, 20);
			this->tsRemoveInputRule->Text = L"toolStripButton2";
			this->tsRemoveInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveInputRule_Click);
			// 
			// tsDuplicateInputRule
			// 
			this->tsDuplicateInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsDuplicateInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDuplicateInputRule.Image")));
			this->tsDuplicateInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDuplicateInputRule->Name = L"tsDuplicateInputRule";
			this->tsDuplicateInputRule->Size = System::Drawing::Size(23, 20);
			this->tsDuplicateInputRule->Text = L"toolStripButton3";
			this->tsDuplicateInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateInputRule_Click);
			// 
			// lstInputRules
			// 
			this->lstInputRules->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstInputRules->FormattingEnabled = true;
			this->lstInputRules->Location = System::Drawing::Point(3, 4);
			this->lstInputRules->Name = L"lstInputRules";
			this->lstInputRules->Size = System::Drawing::Size(105, 4);
			this->lstInputRules->TabIndex = 2;
			this->lstInputRules->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstInputRules_SelectedIndexChanged);
			// 
			// panelStepRuleset
			// 
			this->panelStepRuleset->Controls->Add(this->panel6);
			this->panelStepRuleset->Controls->Add(label1);
			this->panelStepRuleset->Location = System::Drawing::Point(14, 11);
			this->panelStepRuleset->Name = L"panelStepRuleset";
			this->panelStepRuleset->Size = System::Drawing::Size(144, 27);
			this->panelStepRuleset->TabIndex = 3;
			// 
			// panel6
			// 
			this->panel6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel6->Controls->Add(this->tsRuleset);
			this->panel6->Controls->Add(this->cboRulesets);
			this->panel6->Location = System::Drawing::Point(6, 31);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(135, 49);
			this->panel6->TabIndex = 7;
			// 
			// tsRuleset
			// 
			this->tsRuleset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tsRuleset->Dock = System::Windows::Forms::DockStyle::None;
			this->tsRuleset->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsRuleset->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsLoadRulesetDialog, 
				this->tsSaveRulesetDialog, this->toolStripButton2});
			this->tsRuleset->Location = System::Drawing::Point(62, 11);
			this->tsRuleset->Name = L"tsRuleset";
			this->tsRuleset->Size = System::Drawing::Size(72, 25);
			this->tsRuleset->TabIndex = 6;
			this->tsRuleset->Text = L"toolStrip2";
			// 
			// tsLoadRulesetDialog
			// 
			this->tsLoadRulesetDialog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsLoadRulesetDialog->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsLoadRulesetDialog.Image")));
			this->tsLoadRulesetDialog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsLoadRulesetDialog->Name = L"tsLoadRulesetDialog";
			this->tsLoadRulesetDialog->Size = System::Drawing::Size(23, 22);
			this->tsLoadRulesetDialog->Text = L"toolStripButton1";
			this->tsLoadRulesetDialog->Click += gcnew System::EventHandler(this, &WizardForm::tsLoadRulesetDialog_Click);
			// 
			// tsSaveRulesetDialog
			// 
			this->tsSaveRulesetDialog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsSaveRulesetDialog->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsSaveRulesetDialog.Image")));
			this->tsSaveRulesetDialog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsSaveRulesetDialog->Name = L"tsSaveRulesetDialog";
			this->tsSaveRulesetDialog->Size = System::Drawing::Size(23, 22);
			this->tsSaveRulesetDialog->Text = L"toolStripButton2";
			this->tsSaveRulesetDialog->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveRulesetDialog_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &WizardForm::toolStripButton2_Click);
			// 
			// cboRulesets
			// 
			this->cboRulesets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboRulesets->FormattingEnabled = true;
			this->cboRulesets->Location = System::Drawing::Point(8, 14);
			this->cboRulesets->Name = L"cboRulesets";
			this->cboRulesets->Size = System::Drawing::Size(51, 21);
			this->cboRulesets->TabIndex = 5;
			// 
			// panelStepAfterReplacements
			// 
			this->panelStepAfterReplacements->Controls->Add(this->gridAfterReplacements);
			this->panelStepAfterReplacements->Controls->Add(label5);
			this->panelStepAfterReplacements->Location = System::Drawing::Point(164, 45);
			this->panelStepAfterReplacements->Name = L"panelStepAfterReplacements";
			this->panelStepAfterReplacements->Size = System::Drawing::Size(143, 27);
			this->panelStepAfterReplacements->TabIndex = 7;
			// 
			// gridAfterReplacements
			// 
			this->gridAfterReplacements->AllowDrop = true;
			this->gridAfterReplacements->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridAfterReplacements->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
			this->gridAfterReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridAfterReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->dataGridViewTextBoxColumn1, 
				this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4});
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridAfterReplacements->DefaultCellStyle = dataGridViewCellStyle5;
			this->gridAfterReplacements->Location = System::Drawing::Point(9, 27);
			this->gridAfterReplacements->Name = L"gridAfterReplacements";
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
			this->gridAfterReplacements->Size = System::Drawing::Size(104, 0);
			this->gridAfterReplacements->TabIndex = 2;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"ID";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Visible = false;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"GroupID";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->Visible = false;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn3->HeaderText = L"Search";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn4->HeaderText = L"Replace";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			// 
			// panelStepRename
			// 
			this->panelStepRename->Controls->Add(label7);
			this->panelStepRename->Location = System::Drawing::Point(164, 78);
			this->panelStepRename->Name = L"panelStepRename";
			this->panelStepRename->Size = System::Drawing::Size(143, 27);
			this->panelStepRename->TabIndex = 9;
			// 
			// panelNavigation
			// 
			this->panelNavigation->Controls->Add(this->buttonPreviousStep);
			this->panelNavigation->Controls->Add(this->buttonNextStep);
			this->panelNavigation->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panelNavigation->Location = System::Drawing::Point(0, 271);
			this->panelNavigation->Name = L"panelNavigation";
			this->panelNavigation->Size = System::Drawing::Size(665, 33);
			this->panelNavigation->TabIndex = 11;
			// 
			// buttonPreviousStep
			// 
			this->buttonPreviousStep->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPreviousStep->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttonPreviousStep.Image")));
			this->buttonPreviousStep->Location = System::Drawing::Point(530, 5);
			this->buttonPreviousStep->Name = L"buttonPreviousStep";
			this->buttonPreviousStep->Size = System::Drawing::Size(48, 23);
			this->buttonPreviousStep->TabIndex = 1;
			this->buttonPreviousStep->UseVisualStyleBackColor = true;
			this->buttonPreviousStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonPreviousStep_Click);
			// 
			// buttonNextStep
			// 
			this->buttonNextStep->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonNextStep->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttonNextStep.Image")));
			this->buttonNextStep->Location = System::Drawing::Point(587, 5);
			this->buttonNextStep->Name = L"buttonNextStep";
			this->buttonNextStep->Size = System::Drawing::Size(48, 23);
			this->buttonNextStep->TabIndex = 0;
			this->buttonNextStep->UseVisualStyleBackColor = true;
			this->buttonNextStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonNextStep_Click);
			// 
			// panelStepBeforeReplacements
			// 
			this->panelStepBeforeReplacements->Controls->Add(this->gridBeforeReplacements);
			this->panelStepBeforeReplacements->Controls->Add(label4);
			this->panelStepBeforeReplacements->Location = System::Drawing::Point(14, 45);
			this->panelStepBeforeReplacements->Name = L"panelStepBeforeReplacements";
			this->panelStepBeforeReplacements->Size = System::Drawing::Size(144, 27);
			this->panelStepBeforeReplacements->TabIndex = 6;
			// 
			// gridBeforeReplacements
			// 
			this->gridBeforeReplacements->AllowDrop = true;
			this->gridBeforeReplacements->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridBeforeReplacements->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle7->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle7;
			this->gridBeforeReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridBeforeReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ID, 
				this->GroupID, this->Search, this->Replace});
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle8->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridBeforeReplacements->DefaultCellStyle = dataGridViewCellStyle8;
			this->gridBeforeReplacements->Location = System::Drawing::Point(9, 27);
			this->gridBeforeReplacements->Name = L"gridBeforeReplacements";
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle9->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle9;
			this->gridBeforeReplacements->Size = System::Drawing::Size(105, 0);
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
			// panelFilelist
			// 
			this->panelFilelist->Controls->Add(this->panel5);
			this->panelFilelist->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelFilelist->Location = System::Drawing::Point(0, 0);
			this->panelFilelist->Name = L"panelFilelist";
			this->panelFilelist->Size = System::Drawing::Size(665, 98);
			this->panelFilelist->TabIndex = 10;
			// 
			// panel5
			// 
			this->panel5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel5->Controls->Add(this->tsFileList);
			this->panel5->Controls->Add(this->fileList);
			this->panel5->Location = System::Drawing::Point(6, 6);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(656, 89);
			this->panel5->TabIndex = 2;
			// 
			// tsFileList
			// 
			this->tsFileList->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsFileList->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsFileList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->tsAddFiles, this->tsRemoveFileFromList, 
				this->tsApplyChanges, this->toolStripButton1});
			this->tsFileList->Location = System::Drawing::Point(632, 0);
			this->tsFileList->Name = L"tsFileList";
			this->tsFileList->Size = System::Drawing::Size(24, 89);
			this->tsFileList->TabIndex = 2;
			this->tsFileList->Text = L"toolStrip2";
			// 
			// tsAddFiles
			// 
			this->tsAddFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsAddFiles->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddFiles.Image")));
			this->tsAddFiles->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddFiles->Name = L"tsAddFiles";
			this->tsAddFiles->Size = System::Drawing::Size(21, 20);
			this->tsAddFiles->Text = L"toolStripButton5";
			this->tsAddFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsAddFiles_Click);
			// 
			// tsRemoveFileFromList
			// 
			this->tsRemoveFileFromList->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsRemoveFileFromList->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsRemoveFileFromList.Image")));
			this->tsRemoveFileFromList->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsRemoveFileFromList->Name = L"tsRemoveFileFromList";
			this->tsRemoveFileFromList->Size = System::Drawing::Size(21, 20);
			this->tsRemoveFileFromList->Text = L"toolStripButton6";
			this->tsRemoveFileFromList->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveFileFromList_Click);
			// 
			// tsApplyChanges
			// 
			this->tsApplyChanges->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tsApplyChanges->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsApplyChanges.Image")));
			this->tsApplyChanges->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsApplyChanges->Name = L"tsApplyChanges";
			this->tsApplyChanges->Size = System::Drawing::Size(21, 20);
			this->tsApplyChanges->Text = L"toolStripButton7";
			this->tsApplyChanges->Click += gcnew System::EventHandler(this, &WizardForm::tsApplyChanges_Click);
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 20);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &WizardForm::toolStripButton1_Click);
			// 
			// fileList
			// 
			this->fileList->AllowDrop = true;
			this->fileList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->fileList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->chFile});
			this->fileList->FullRowSelect = true;
			this->fileList->GridLines = true;
			this->fileList->Location = System::Drawing::Point(3, 3);
			this->fileList->Name = L"fileList";
			this->fileList->ShowGroups = false;
			this->fileList->Size = System::Drawing::Size(626, 83);
			this->fileList->TabIndex = 1;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::Details;
			this->fileList->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragEnter);
			this->fileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragDrop);
			// 
			// chFile
			// 
			this->chFile->Text = L"File";
			this->chFile->Width = 200;
			// 
			// saveRulesetFileDialog
			// 
			this->saveRulesetFileDialog->DefaultExt = L"ruleset";
			this->saveRulesetFileDialog->Filter = L"Ruleset Files|*.ruleset";
			this->saveRulesetFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::saveRulesetFileDialog_FileOk);
			// 
			// fileListopenFileDiag
			// 
			this->fileListopenFileDiag->FileName = L"*.*";
			this->fileListopenFileDiag->Filter = L"All files|*.*";
			this->fileListopenFileDiag->Multiselect = true;
			this->fileListopenFileDiag->RestoreDirectory = true;
			this->fileListopenFileDiag->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::fileListopenFileDiag_FileOk);
			// 
			// WizardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(806, 410);
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
			this->panelStepGems->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->EndInit();
			this->panelStepOutputFormat->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tsOutputFormat->ResumeLayout(false);
			this->tsOutputFormat->PerformLayout();
			this->panelStepInputRule->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->tsInputRuleButtons->ResumeLayout(false);
			this->tsInputRuleButtons->PerformLayout();
			this->panelStepRuleset->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->tsRuleset->ResumeLayout(false);
			this->tsRuleset->PerformLayout();
			this->panelStepAfterReplacements->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->EndInit();
			this->panelStepRename->ResumeLayout(false);
			this->panelNavigation->ResumeLayout(false);
			this->panelStepBeforeReplacements->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->EndInit();
			this->panelFilelist->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->tsFileList->ResumeLayout(false);
			this->tsFileList->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Step Enter/Leave Events

		void onEnterStepRuleset() {
			applyChanges(Step::RULESET_SELECT);
		}

		void onLeaveStepRuleset() {

		}

		// ----------------------------------------- //

		void onEnterStepBeforeReplacements() {
			loadBeforeReplacements();	
			applyChanges(Step::BEFORE_REPLACEMENTS);
		}

		void onLeaveStepBeforeReplacements() {
			saveBeforeReplacements();
		}

		// ----------------------------------------- //

		void onEnterStepOutputFormats() {
			applyChanges(Step::OUTPUTFORMAT_SELECT);
			refreshOutputFormatList();			 
			lstOutputFormat->SelectedIndex = 0;
			tsSaveOutputFormat->Visible = false;
		}

		void onLeaveStepOutputFormats() {

		}

		// ----------------------------------------- //

		void onEnterStepInputRules() {
			if(mInputRuleID)
				updateInputRuleGems(mInputRuleID);
			applyChanges(Step::INPUTRULES_SELECT);
			refreshInputRuleList();
			lstInputRules->SelectedIndex = 0;
			tsSaveInputRule->Visible = false;
		}

		void onLeaveStepInputRules() {

		}

		// ----------------------------------------- //

		void onEnterStepGems() {
			applyChanges(Step::GEMS_SELECT);
			loadGems();
			if(mInputRuleID != 0) {
				InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
				txtGemInputRule->Text = toClrString(inputRule.getRegex());
			}
		}

		void onLeaveStepGems() {
			saveGems();
		}

		// ----------------------------------------- //

		void onEnterStepAfterReplacements() {
			applyChanges(Step::AFTER_REPLACEMENTS);
		}

		void onLeaveStepAfterReplacements() {

		}

		// ----------------------------------------- //

		void onEnterStepRename() {
			applyChanges(Step::RENAME);
		}

		void onLeaveStepRename() {

		}

#pragma endregion
#pragma region Business Code
		void applyChanges(Step step) {
			if(step == Step::RULESET_SELECT) {
				 reloadFileList();
			} else if (step == Step::BEFORE_REPLACEMENTS) {
				 saveBeforeReplacements();
				 reloadFileList();
				 Replacements replacements = mRuleset->getBeforeReplacements();
				 for(int i=0; i<fileList->Items->Count; i++) {
					 ListViewItem^ item = fileList->Items[i];
					 item->Text = toClrString(replacements.replace(toStdString(item->Text)));
				 }
			} else if (step == Step::INPUTRULES_SELECT) {
				 reloadFileList();
				 Replacements replacements = mRuleset->getBeforeReplacements();
				 for(int i=0; i<fileList->Items->Count; i++) {
					 ListViewItem^ item = fileList->Items[i];
					 item->Text = toClrString(replacements.replace(toStdString(item->Text)));
				 }

				 if(mInputRuleID != 0) {
					 InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
					 vector<GemValue> not_used;
					 for(int i=0; i<fileList->Items->Count; i++) {
						 ListViewItem^ item = fileList->Items[i];
						 if(inputRule.applyTo(toStdString(item->Text), not_used)) 
							 item->BackColor = Color::Green;
						 else
							 item->BackColor = Color::Red;
	//					 item->Text = toClrString(replacements.replace(toStdString(item->Text)));
					 }
				 }
			} else if (step == Step::GEMS_SELECT) {
				reloadFileList();
				Replacements replacements = mRuleset->getBeforeReplacements();
				for(int i=0; i<fileList->Items->Count; i++) {
					ListViewItem^ item = fileList->Items[i];
					item->Text = toClrString(replacements.replace(toStdString(item->Text)));
				}
				
				fileList->Columns->Add("Result");

				for(int i=0; i<fileList->Items->Count; i++) {
					string resultingFilename;
					if(mRuleset->applyTo(toStdString(fileList->Items[i]->Text), resultingFilename)) {
						fileList->Items[i]->SubItems->Add(toClrString(resultingFilename));
					}
				}
			}
		}

		void updateInputRuleGems(sqlite_int64 inputRuleRowId) {
			InputRule inputRule(mRuleset->getDatabase(), inputRuleRowId);
			OutputFormat outputFormat(mRuleset->getDatabase(), inputRule.getOutputFormatId());

			vector<string> gemNames;
			
			if(outputFormat.parse(gemNames)) {
				vector<Gem> gems = inputRule.getGems();
				
				// array of elements parsed out of OutputFormat
				for(unsigned i = 0; i<gemNames.size(); i++) {
					bool found = false;
	
					// array of already existing Gems and their Names
					for(unsigned j = 0; j<gems.size(); j++) {
						// found is true if the GemName is already in use
						if(gems[j].getName() == gemNames[i])  {
							found = true;
							break;
						}						
					}

					// case: UPDATE
					if(found == true) {
						gems[j].setName(gemNames[i]);
					}

					// case: INSERT
					else {
						inputRule.addGem(gemNames[i]);
					}
				}

				for(unsigned i=0; i<gems.size(); i++) {
					bool found = false;

					for(unsigned j=0; j<gemNames.size(); j++) {
						if(gems[i].getName() == gemNames[j])  { 
							found = true;
						}
					}

					// case: DELETE
					if(found == false) {
						gems[i].remove();
					}
				}
			}
		}

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
/*					OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
					vector<string> not_used;
					if(!outputFormat.parse(not_used)) {
						setMaxStep(Step::OUTPUTFORMAT_SELECT);
						return ;
					}*/

					if(mInputRuleID > 0) {
						if(mGemID > 0) {
							setMaxStep(Step::MAX);
						}

						else {
							setMaxStep(Step::GEMS_SELECT);
						}
					}

					else {
						setMaxStep(Step::INPUTRULES_SELECT);
					}
				}
				else {
					setMaxStep(Step::OUTPUTFORMAT_SELECT);
				}
			}
			else {
				setMaxStep(Step::RULESET_SELECT);
			}
		}

		void deleteRuleset(String^ rulesetFilename) {
			File::Delete(rulesetFilename);
		}

		void addFile( String^ pathToFile )
		{
			String^ fileName = System::IO::Path::GetFileNameWithoutExtension(pathToFile);
			if(mFiles.Contains(fileName))
				return ;
			mFiles.Add(pathToFile);

			// add to fileList Control
			ListViewItem^ item = gcnew ListViewItem(fileName);
			item->Tag = mFiles.Count - 1;
			fileList->Items->Add(item);
		}

		void reloadFileList() {
			if(fileList->Columns->Count > 1) {
				for(int i=1; i<fileList->Columns->Count; i++) {
					fileList->Columns->RemoveAt(i);
				}
			}

			fileList->Items->Clear();

			for(int i=0; i<mFiles.Count; i++) {
				String^ fileName = System::IO::Path::GetFileNameWithoutExtension(mFiles[i]);
				ListViewItem^ item = gcnew ListViewItem(fileName);
				item->Tag = i;
				fileList->Items->Add(item);
			}
		}

		void setMaxStep(Step newMaxStep) {
			mMaxStep = newMaxStep;
			setStep(mStep);
		}

		void setStep(Step newStep) {
			if(newStep > mMaxStep) {
				if(mStep == Step::RULESET_SELECT && newStep == Step::BEFORE_REPLACEMENTS) {
					if(mRuleset != NULL) {
						mMaxStep = Step::OUTPUTFORMAT_SELECT;
						refreshOutputFormatList();
					}
				}
				if(mStep == Step::OUTPUTFORMAT_SELECT && newStep == Step::INPUTRULES_SELECT) {
					if(mRuleset && mOutputFormatID > 0) {
						mMaxStep = Step::INPUTRULES_SELECT;
					}
				}
				if(mStep == Step::INPUTRULES_SELECT && newStep == Step::GEMS_SELECT) {
					if(mRuleset && mOutputFormatID > 0) {
						mMaxStep = Step::GEMS_SELECT;
					}
				}
			}

			if(int(newStep) < 0 || int(newStep) >= int(Step::MAX) || newStep > mMaxStep) {
				return ;
			}

			// onEnter: Ruleset
			if(newStep == Step::RULESET_SELECT && mStep != Step::RULESET_SELECT) {
				onEnterStepRuleset();
			}

			// onLeave: Ruleset
			if(mStep == Step::RULESET_SELECT && newStep != Step::RULESET_SELECT) {
				onLeaveStepRuleset();
			}

			// onEnter: beforeReplacements
			if(newStep == Step::BEFORE_REPLACEMENTS && mStep != Step::BEFORE_REPLACEMENTS) {
				onEnterStepBeforeReplacements();
			}

			// onLeave: beforeReplacements
			if(mStep == Step::BEFORE_REPLACEMENTS && newStep != Step::BEFORE_REPLACEMENTS) {
				onLeaveStepBeforeReplacements();
			}

			// onEnter: outputFormat
			if(newStep == Step::OUTPUTFORMAT_SELECT && mStep != Step::OUTPUTFORMAT_SELECT) {
				onEnterStepOutputFormats();
			}

			// onLeave: outputFormat
			if(mStep == Step::OUTPUTFORMAT_SELECT && newStep != Step::OUTPUTFORMAT_SELECT) {
				onLeaveStepOutputFormats();
			}

			// onEnter: inputRule
			if(newStep == Step::INPUTRULES_SELECT && mStep != Step::INPUTRULES_SELECT) {
				onEnterStepInputRules();
			}

			// onLeave: inputRule
			if(mStep == Step::INPUTRULES_SELECT && newStep != Step::INPUTRULES_SELECT) {
				onLeaveStepInputRules();
			}

			// onEnter: Gems
			if(newStep == Step::GEMS_SELECT && mStep != Step::GEMS_SELECT) {
				onEnterStepGems();
			}

			// onLeave: Gems
			if(mStep == Step::GEMS_SELECT && newStep != Step::GEMS_SELECT) {
				onLeaveStepGems();
			}

			// onEnter: afterReplacements
			if(newStep == Step::AFTER_REPLACEMENTS && mStep != Step::AFTER_REPLACEMENTS) {
				onEnterStepAfterReplacements();
			}

			// onLeave: afterReplacements
			if(mStep == Step::AFTER_REPLACEMENTS && newStep != Step::AFTER_REPLACEMENTS) {
				onLeaveStepAfterReplacements();
			}

			// onEnter: Rename
			if(newStep == Step::RENAME && mStep != Step::RENAME) {
				onEnterStepRename();
			}

			// onLeave: Rename
			if(mStep == Step::RENAME && newStep != Step::RENAME) {
				onLeaveStepRename();
			}

			mStep = newStep;

			for(int i=0; i<int(Step::MAX); i++) {
				mStepPanelList[i]->Visible = false;
				mStepPanelList[i]->Dock = DockStyle::None;
				mStepButtonList[i]->Checked = false;

				if(i > int(mMaxStep)) {
					mStepButtonList[i]->Enabled = false;
				}

				else {
					mStepButtonList[i]->Enabled = true;
				}
			}

			mStepPanelList[int(mStep)]->Visible = true;
			mStepPanelList[int(mStep)]->Dock = DockStyle::Fill;
			mStepButtonList[int(mStep)]->Checked = true;
		}

		void saveBeforeReplacements() {
			if(mRuleset == NULL) return ;
			Replacements replacements = mRuleset->getBeforeReplacements();

			int rowCount = gridBeforeReplacements->Rows->Count;
			vector<sqlite_int64> replacementsWhichWereNotDeleted ;
			for(int i=0; i<gridBeforeReplacements->Rows->Count; i++) {
				if(gridBeforeReplacements->Rows[i]->Cells[0]->Value == nullptr) {
					String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
					String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
					if(search != nullptr) {
						if(replace == nullptr)
							replace = L"";
						Replacement replacement = replacements.addReplacement(toStdString(search), toStdString(replace));
						replacementsWhichWereNotDeleted.push_back(replacement.getRowId());
						gridBeforeReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement.getRowId());
						gridBeforeReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement.getGroupId());
					}
				}

				else {
					int rowid = (int)((Int32^)gridBeforeReplacements->Rows[i]->Cells[0]->Value);
					String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
					String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
					if(search != nullptr) {
						if(replace == nullptr)
							replace = L"";

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
					if(replacementVector[i].getRowId() == replacementsWhichWereNotDeleted[j]) {
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
				values[0] = gcnew Int32 ((Int32)replacementVector[i].getRowId());
				values[1] = gcnew Int32 ((Int32)replacementVector[i].getGroupId());
				values[2] = toClrString(replacementVector[i].getRegex().str());
				values[3] = toClrString(replacementVector[i].getReplacement());

				gridBeforeReplacements->Rows->Add(values);
			}
		}

		void loadGems() {
			gridGems->Rows->Clear();
			GemColumnGem->Items->Clear();

			// add empty item to the ComboBox column
			GemColumnGem->Items->Add("");
			
			OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
			boost::regex regularExpression(inputRule.getRegex());
			unsigned int subExpressionCount = regularExpression.mark_count();
			vector<Gem> gems = inputRule.getGems();

			for(unsigned i=0; i<gems.size(); i++) {
				GemColumnGem->Items->Add(toClrString(gems[i].getName()));
			}

			for(unsigned i=0; i < subExpressionCount; i++) {
				cli::array<Object^>^ values = gcnew cli::array<Object^>(2);
				values[0] = gcnew Int32(i+1);
				for(unsigned j=0; j<gems.size(); j++) {
					if(gems[j].getPosition() == i+1) {
						values[1] = gcnew String(toClrString(gems[j].getName()));
						gridGems->Rows->Add(values);
					}
				}

			}
		}

		void saveGems() {
			InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
			vector<Gem> gems = inputRule.getGems();

			for(int i=0; i<gridGems->Rows->Count; i++) {
				DataGridViewRow^ row = gridGems->Rows[i];
				Int32^ position = (Int32^) row->Cells[0]->Value;
				String^ gemName = (String^) row->Cells[1]->Value;

				for(unsigned i=0; i<gems.size(); i++) {
					if(gems[i].getName() == toStdString(gemName)) {
						gems[i].setPosition((int) position);
					}
				}
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
	#pragma region Global: Form
		private: System::Void WizardForm_Load(System::Object^  sender, System::EventArgs^  e) {
					 mStepPanelList = gcnew System::Collections::Generic::List<Panel^>();
					 mStepPanelList->Add(panelStepRuleset);
					 mStepPanelList->Add(panelStepBeforeReplacements);
					 mStepPanelList->Add(panelStepOutputFormat);
					 mStepPanelList->Add(panelStepInputRule);
					 mStepPanelList->Add(panelStepGems);
					 mStepPanelList->Add(panelStepAfterReplacements);
					 mStepPanelList->Add(panelStepRename);

					 mStepButtonList = gcnew System::Collections::Generic::List<ToolStripButton^>();
					 mStepButtonList->Add(tsStepRuleset);
					 mStepButtonList->Add(tsStepBeforeReplacements);
					 mStepButtonList->Add(tsStepOutputFormat);
					 mStepButtonList->Add(tsStepInputRule);
					 mStepButtonList->Add(tsStepGems);
					 mStepButtonList->Add(tsStepAfterReplacements);
					 mStepButtonList->Add(tsStepRename);

					 //! select first step
					 mStep = Step::RULESET_SELECT;
					 setMaxStep(Step::RULESET_SELECT);

					 toolStripButton1_Click(nullptr, nullptr);
					 toolStripButton2_Click(nullptr, nullptr);
				 }
	private: System::Void buttonNextStep_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step(int(mStep) + 1));
			 }
	private: System::Void buttonPreviousStep_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step(int(mStep) - 1));
			 }
	private: System::Void tsStepRuleset_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::RULESET_SELECT);
			 }
	private: System::Void tsStepOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::OUTPUTFORMAT_SELECT);
			 }
	private: System::Void tsStepBeforeReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::BEFORE_REPLACEMENTS);
			 }
	private: System::Void tsStepInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::INPUTRULES_SELECT);
			 }
	private: System::Void tsStepAfterReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::AFTER_REPLACEMENTS);
			 }
	private: System::Void tsStepGems_Click(System::Object^  sender, System::EventArgs^  e) {
				 setStep(Step::GEMS_SELECT);
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
						 addFile(files[i]);	
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
	#pragma region Global: fileList
	private: System::Void fileListopenFileDiag_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 for(int i=0; i<fileListopenFileDiag->FileNames->Length; i++) {
					 addFile(fileListopenFileDiag->FileNames[i]);
				 }
			 }
	private: System::Void tsAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
				 fileListopenFileDiag->ShowDialog();
			 }
	private: System::Void tsRemoveFileFromList_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(fileList->FocusedItem != nullptr)
					 fileList->Items->Remove(fileList->FocusedItem);
			 }
	private: System::Void tsApplyChanges_Click(System::Object^  sender, System::EventArgs^  e) {
				applyChanges(mStep);
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
			 if(mRuleset != NULL) {
				 String^ oldRulesetFilename = toClrString(mRuleset->getFilename());
				 if(System::IO::File::Exists(rulesetFilename)) {
					 System::IO::File::Delete(rulesetFilename);
				 }
				 System::IO::File::Copy(oldRulesetFilename, rulesetFilename);
				 loadRuleset(rulesetFilename);
			 }

			 else {
				 createRuleset(rulesetFilename);
			 }
			 cboRulesets->Text = toClrString(mRuleset->getName());
		 }
	private: System::Void tsLoadRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 openRulesetFileDialog->ShowDialog();
		 }
	private: System::Void tsSaveRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveRulesetFileDialog->ShowDialog();
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
			 

			 int cursorPosition = txtOutputFormat->SelectionStart;

			 txtOutputFormat->Select(0, txtOutputFormat->Text->Length);
			 txtOutputFormat->SelectionColor = Color::Black;

			 int start = -1;
			 for(int i=0; i<txtOutputFormat->Text->Length; i++) {
				 if(txtOutputFormat->Text[i] == L'$') {
					if(start == -1)
						 start = i;
					else {
						txtOutputFormat->Select(start, i - start + 1);
						txtOutputFormat->SelectionColor = Color::Red;
						start = -1;
					}
				 }
			 }
			 txtOutputFormat->Select(cursorPosition,0);
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

			 txtOutputFormat_TextChanged(nullptr, nullptr);
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

			 updateInputRuleGems(mInputRuleID);
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
	#pragma region Step: Gems
private: System::Void gridGems_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {
				DataGridViewRow^ row;
				
				if(gridGems->SelectedRows->Count == 1 ) 
					row = gridGems->SelectedRows[0]; // MultiLine = false; so only one Row can be selected
				else if(gridGems->SelectedCells->Count == 1) 
					row = gridGems->Rows[gridGems->SelectedCells[0]->RowIndex];
				else
					return ;

				Int32^ position = (Int32^) row->Cells[0]->Value;

				InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
				boost::regex regularExpression(inputRule.getRegex());


				// reset text (needed?)
				txtGemInputRule->Text = toClrString(inputRule.getRegex());

				// reset style
				txtGemInputRule->Select(0, txtGemInputRule->Text->Length);
				txtGemInputRule->SelectionFont = gcnew System::Drawing::Font(
					txtGemInputRule->Font->FontFamily->Name, txtGemInputRule->Font->Size, FontStyle::Regular );


				int start = -1;
				int match = 0;
				for(int i=0; i<txtGemInputRule->Text->Length; i++ ) {
					if(start == -1) {
						if(txtGemInputRule->Text[i] == L'(') {
							if( txtGemInputRule->Text[i-1] != L'\\' || 
								(i >= 1 && txtGemInputRule->Text[i-1] == L'\\' && (i < 2 || txtGemInputRule->Text[i-2] == L'\\')) ) { 
									start = i;
							}
						}
					}

					else {
						if(txtGemInputRule->Text[i] == L')') {
							if( txtGemInputRule->Text[i-1] != L'\\' || 
								(i >= 1 && txtGemInputRule->Text[i-1] == L'\\' && (i < 2 || txtGemInputRule->Text[i-2] == L'\\')) ) { 
									match ++;

									if(match == (int) position) {
										txtGemInputRule->Select(start, i - start + 1);
										txtGemInputRule->SelectionFont = gcnew System::Drawing::Font(
											txtGemInputRule->Font->FontFamily->Name, txtGemInputRule->Font->Size, FontStyle::Bold );
									}

									start = -1;
							}
						}
					}
				}
			}
#pragma endregion

	#pragma region DebugButtons
	private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			 cli::array<String^>^ files = System::IO::Directory::GetFiles("D:\\Daten\\Develop\\Renamer\\testFiles", "*.avi");
			 for(int i=0; i<files->Length; i++){
				 addFile(files[i]);
			 }
		 }
	private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ rulesetFilename = L"D:\\home\\windows\\Eigene Dateien\\The Simpsons.ruleset";
			 loadRuleset(rulesetFilename);
			 cboRulesets->Text = toClrString(mRuleset->getName());
		 }
	#pragma endregion
#pragma endregion
#pragma region Footer
};
// --- don't delete after this line (and one line before this line) --- //
}
#pragma endregion



