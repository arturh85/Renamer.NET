#pragma region Header
#pragma once

#include <vcclr.h>
#include "ruleset.h"
#include "inputRule.h"
#include "clrUtility.h"
#include "stlUtility.h"
#include "stdlib.h"
#include "error.h"


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
				   STEP_RULESET_REPLACEMENTS = 1,
				   STEP_OUTPUTFORMAT_SELECT = 2,
				   STEP_INPUTRULES_SELECT = 3,
				   STEP_INPUTRULE_REPLACEMENTS = 4,
				   STEP_GEMS_SELECT = 5,
				   STEP_GEM_REPLACEMENTS = 6,
				   STEP_MAX = 7
			   };

    // Business Logic Member Variables
	private: Ruleset* mRuleset;
	protected: Step mStep;
	protected: Step mMaxStep;
	protected: System::Collections::Generic::List<Panel^>^ stepPanelList;
	protected: System::Collections::Generic::List<ToolStripButton^>^ stepButtonList;

	// Tool Strip with Buttons for each Step
	private: System::Windows::Forms::ToolStrip^  tsStepButtons;
	private: System::Windows::Forms::ToolStripButton^  tsStepRuleset;
	private: System::Windows::Forms::ToolStripButton^  tsStepRulesetReplacements;
	private: System::Windows::Forms::ToolStripButton^  tsStepOutputFormat;
	private: System::Windows::Forms::ToolStripButton^  tsStepInputRule;
	private: System::Windows::Forms::ToolStripButton^  tsStepInputRuleReplacements;
	private: System::Windows::Forms::ToolStripButton^  tsStepGems;
	private: System::Windows::Forms::ToolStripButton^  tsStepGemReplacements;

	// Panels for each Step








    // Buttons for switching between the steps




	// Controls for the Panel 'Ruleset'

	private: System::Windows::Forms::OpenFileDialog^  openRulesetFileDialog;
	private: System::Windows::Forms::SplitContainer^  splitContainer;

	// Controls for the Panel 'OutputFormat'


	// Container for the Panel of the current Step (Panel Child will have Dock = Fill)

		
    // List of all files relevant to current ruleset


	// tool strip for file list operations








    // to do: categorize the remaining Controls or make them non-member variables



	private: System::Windows::Forms::Panel^  panelStepContent;
	private: System::Windows::Forms::Panel^  panelStepRuleset;
	private: System::Windows::Forms::Button^  buttonRulesetOpenDialog;
	private: System::Windows::Forms::ComboBox^  cboRulesets;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panelStepGemReplacements;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Panel^  panelStepGems;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Panel^  panelStepInputRuleReplacements;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Panel^  panelStepRulesetReplacements;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Panel^  panelStepInputRule;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Panel^  panelStepOutputFormat;
	private: System::Windows::Forms::ToolStrip^  tsOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsAddOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDeleteOutputFormat;
private: System::Windows::Forms::TextBox^  txtOutputFormat;
private: System::Windows::Forms::ListView^  lstOutputFormat;


	private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Panel^  panelFilelist;
private: System::Windows::Forms::ToolStrip^  tsFileList;
private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
private: System::Windows::Forms::ListView^  fileList;
private: System::Windows::Forms::Panel^  panelNavigation;
private: System::Windows::Forms::Button^  buttonPreviousStep;
private: System::Windows::Forms::Button^  buttonNextStep;
private: System::Windows::Forms::Button^  buttonRulesetSaveDialog;

private: System::Windows::Forms::SaveFileDialog^  saveRulesetFileDialog;













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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WizardForm::typeid));
			this->tsStepButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsStepRuleset = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepRulesetReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepInputRuleReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepGems = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepGemReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->openRulesetFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->panelStepContent = (gcnew System::Windows::Forms::Panel());
			this->panelStepRuleset = (gcnew System::Windows::Forms::Panel());
			this->buttonRulesetSaveDialog = (gcnew System::Windows::Forms::Button());
			this->buttonRulesetOpenDialog = (gcnew System::Windows::Forms::Button());
			this->cboRulesets = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panelStepGemReplacements = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->panelStepGems = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->panelStepInputRuleReplacements = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panelStepRulesetReplacements = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panelStepInputRule = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panelStepOutputFormat = (gcnew System::Windows::Forms::Panel());
			this->tsOutputFormat = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDeleteOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->lstOutputFormat = (gcnew System::Windows::Forms::ListView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panelFilelist = (gcnew System::Windows::Forms::Panel());
			this->tsFileList = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->panelNavigation = (gcnew System::Windows::Forms::Panel());
			this->buttonPreviousStep = (gcnew System::Windows::Forms::Button());
			this->buttonNextStep = (gcnew System::Windows::Forms::Button());
			this->saveRulesetFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tsStepButtons->SuspendLayout();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->panelStepContent->SuspendLayout();
			this->panelStepRuleset->SuspendLayout();
			this->panelStepGemReplacements->SuspendLayout();
			this->panelStepGems->SuspendLayout();
			this->panelStepInputRuleReplacements->SuspendLayout();
			this->panelStepRulesetReplacements->SuspendLayout();
			this->panelStepInputRule->SuspendLayout();
			this->panelStepOutputFormat->SuspendLayout();
			this->tsOutputFormat->SuspendLayout();
			this->panelFilelist->SuspendLayout();
			this->tsFileList->SuspendLayout();
			this->panelNavigation->SuspendLayout();
			this->SuspendLayout();
			// 
			// tsStepButtons
			// 
			this->tsStepButtons->Dock = System::Windows::Forms::DockStyle::Left;
			this->tsStepButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsStepButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->tsStepRuleset, 
				this->tsStepRulesetReplacements, this->tsStepOutputFormat, this->tsStepInputRule, this->tsStepInputRuleReplacements, this->tsStepGems, 
				this->tsStepGemReplacements});
			this->tsStepButtons->Location = System::Drawing::Point(0, 0);
			this->tsStepButtons->Name = L"tsStepButtons";
			this->tsStepButtons->Size = System::Drawing::Size(143, 477);
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
			this->tsStepRuleset->Size = System::Drawing::Size(140, 20);
			this->tsStepRuleset->Text = L"Ruleset";
			this->tsStepRuleset->Click += gcnew System::EventHandler(this, &WizardForm::tsStepRuleset_Click);
			// 
			// tsStepRulesetReplacements
			// 
			this->tsStepRulesetReplacements->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepRulesetReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepRulesetReplacements.Image")));
			this->tsStepRulesetReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepRulesetReplacements->Name = L"tsStepRulesetReplacements";
			this->tsStepRulesetReplacements->Size = System::Drawing::Size(140, 20);
			this->tsStepRulesetReplacements->Text = L"Ruleset Replacements";
			this->tsStepRulesetReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepRulesetReplacements_Click);
			// 
			// tsStepOutputFormat
			// 
			this->tsStepOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepOutputFormat.Image")));
			this->tsStepOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepOutputFormat->Name = L"tsStepOutputFormat";
			this->tsStepOutputFormat->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
			this->tsStepOutputFormat->Size = System::Drawing::Size(140, 20);
			this->tsStepOutputFormat->Text = L"Output Formats";
			this->tsStepOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsStepOutputFormat_Click);
			// 
			// tsStepInputRule
			// 
			this->tsStepInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepInputRule->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepInputRule.Image")));
			this->tsStepInputRule->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepInputRule->Name = L"tsStepInputRule";
			this->tsStepInputRule->Size = System::Drawing::Size(140, 20);
			this->tsStepInputRule->Text = L"Input Rules";
			this->tsStepInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsStepInputRule_Click);
			// 
			// tsStepInputRuleReplacements
			// 
			this->tsStepInputRuleReplacements->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepInputRuleReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepInputRuleReplacements.Image")));
			this->tsStepInputRuleReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepInputRuleReplacements->Name = L"tsStepInputRuleReplacements";
			this->tsStepInputRuleReplacements->Size = System::Drawing::Size(140, 20);
			this->tsStepInputRuleReplacements->Text = L"Input Rule Replacements";
			this->tsStepInputRuleReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepInputRuleReplacements_Click);
			// 
			// tsStepGems
			// 
			this->tsStepGems->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepGems->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepGems.Image")));
			this->tsStepGems->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepGems->Name = L"tsStepGems";
			this->tsStepGems->Size = System::Drawing::Size(140, 20);
			this->tsStepGems->Text = L"Gems";
			this->tsStepGems->Click += gcnew System::EventHandler(this, &WizardForm::tsStepGems_Click);
			// 
			// tsStepGemReplacements
			// 
			this->tsStepGemReplacements->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsStepGemReplacements->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsStepGemReplacements.Image")));
			this->tsStepGemReplacements->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsStepGemReplacements->Name = L"tsStepGemReplacements";
			this->tsStepGemReplacements->Size = System::Drawing::Size(140, 20);
			this->tsStepGemReplacements->Text = L"Gem Replacements";
			this->tsStepGemReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepGemReplacements_Click);
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
			this->splitContainer->Location = System::Drawing::Point(143, 0);
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
			this->splitContainer->Size = System::Drawing::Size(599, 477);
			this->splitContainer->SplitterDistance = 273;
			this->splitContainer->TabIndex = 9;
			// 
			// panelStepContent
			// 
			this->panelStepContent->Controls->Add(this->panelStepRuleset);
			this->panelStepContent->Controls->Add(this->panelStepGemReplacements);
			this->panelStepContent->Controls->Add(this->panelStepGems);
			this->panelStepContent->Controls->Add(this->panelStepInputRuleReplacements);
			this->panelStepContent->Controls->Add(this->panelStepRulesetReplacements);
			this->panelStepContent->Controls->Add(this->panelStepInputRule);
			this->panelStepContent->Controls->Add(this->panelStepOutputFormat);
			this->panelStepContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelStepContent->Location = System::Drawing::Point(0, 0);
			this->panelStepContent->Name = L"panelStepContent";
			this->panelStepContent->Size = System::Drawing::Size(597, 271);
			this->panelStepContent->TabIndex = 7;
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
			// panelStepGemReplacements
			// 
			this->panelStepGemReplacements->Controls->Add(this->label7);
			this->panelStepGemReplacements->Location = System::Drawing::Point(352, 187);
			this->panelStepGemReplacements->Name = L"panelStepGemReplacements";
			this->panelStepGemReplacements->Size = System::Drawing::Size(133, 50);
			this->panelStepGemReplacements->TabIndex = 9;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(17, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(103, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Gem Replacements:";
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
			// panelStepInputRuleReplacements
			// 
			this->panelStepInputRuleReplacements->Controls->Add(this->label5);
			this->panelStepInputRuleReplacements->Location = System::Drawing::Point(172, 171);
			this->panelStepInputRuleReplacements->Name = L"panelStepInputRuleReplacements";
			this->panelStepInputRuleReplacements->Size = System::Drawing::Size(150, 47);
			this->panelStepInputRuleReplacements->TabIndex = 7;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 16);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(127, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Input Rule Replacements";
			// 
			// panelStepRulesetReplacements
			// 
			this->panelStepRulesetReplacements->Controls->Add(this->label4);
			this->panelStepRulesetReplacements->Location = System::Drawing::Point(48, 102);
			this->panelStepRulesetReplacements->Name = L"panelStepRulesetReplacements";
			this->panelStepRulesetReplacements->Size = System::Drawing::Size(141, 41);
			this->panelStepRulesetReplacements->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(15, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(117, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Ruleset Replacements:";
			// 
			// panelStepInputRule
			// 
			this->panelStepInputRule->Controls->Add(this->label3);
			this->panelStepInputRule->Location = System::Drawing::Point(323, 102);
			this->panelStepInputRule->Name = L"panelStepInputRule";
			this->panelStepInputRule->Size = System::Drawing::Size(162, 52);
			this->panelStepInputRule->TabIndex = 5;
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
			this->panelStepOutputFormat->Controls->Add(this->tsOutputFormat);
			this->panelStepOutputFormat->Controls->Add(this->txtOutputFormat);
			this->panelStepOutputFormat->Controls->Add(this->lstOutputFormat);
			this->panelStepOutputFormat->Controls->Add(this->label2);
			this->panelStepOutputFormat->Location = System::Drawing::Point(48, 15);
			this->panelStepOutputFormat->Name = L"panelStepOutputFormat";
			this->panelStepOutputFormat->Size = System::Drawing::Size(396, 169);
			this->panelStepOutputFormat->TabIndex = 4;
			// 
			// tsOutputFormat
			// 
			this->tsOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->tsOutputFormat->Dock = System::Windows::Forms::DockStyle::None;
			this->tsOutputFormat->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsOutputFormat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsAddOutputFormat, 
				this->tsDeleteOutputFormat});
			this->tsOutputFormat->Location = System::Drawing::Point(294, 135);
			this->tsOutputFormat->Name = L"tsOutputFormat";
			this->tsOutputFormat->Size = System::Drawing::Size(82, 25);
			this->tsOutputFormat->TabIndex = 3;
			this->tsOutputFormat->Text = L"toolStrip3";
			// 
			// tsAddOutputFormat
			// 
			this->tsAddOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsAddOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsAddOutputFormat.Image")));
			this->tsAddOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsAddOutputFormat->Name = L"tsAddOutputFormat";
			this->tsAddOutputFormat->Size = System::Drawing::Size(34, 22);
			this->tsAddOutputFormat->Text = L"Add";
			this->tsAddOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsAddOutputFormat_Click);
			// 
			// tsDeleteOutputFormat
			// 
			this->tsDeleteOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsDeleteOutputFormat->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsDeleteOutputFormat.Image")));
			this->tsDeleteOutputFormat->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsDeleteOutputFormat->Name = L"tsDeleteOutputFormat";
			this->tsDeleteOutputFormat->Size = System::Drawing::Size(45, 22);
			this->tsDeleteOutputFormat->Text = L"Delete";
			// 
			// txtOutputFormat
			// 
			this->txtOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFormat->Location = System::Drawing::Point(21, 138);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(271, 20);
			this->txtOutputFormat->TabIndex = 2;
			// 
			// lstOutputFormat
			// 
			this->lstOutputFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstOutputFormat->Location = System::Drawing::Point(21, 40);
			this->lstOutputFormat->Name = L"lstOutputFormat";
			this->lstOutputFormat->Size = System::Drawing::Size(271, 104);
			this->lstOutputFormat->TabIndex = 1;
			this->lstOutputFormat->UseCompatibleStateImageBehavior = false;
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
			// panelFilelist
			// 
			this->panelFilelist->Controls->Add(this->tsFileList);
			this->panelFilelist->Controls->Add(this->fileList);
			this->panelFilelist->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelFilelist->Location = System::Drawing::Point(0, 31);
			this->panelFilelist->Name = L"panelFilelist";
			this->panelFilelist->Size = System::Drawing::Size(597, 167);
			this->panelFilelist->TabIndex = 10;
			// 
			// tsFileList
			// 
			this->tsFileList->Dock = System::Windows::Forms::DockStyle::Right;
			this->tsFileList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripButton5, 
				this->toolStripButton6, this->toolStripButton7});
			this->tsFileList->Location = System::Drawing::Point(573, 0);
			this->tsFileList->Name = L"tsFileList";
			this->tsFileList->Size = System::Drawing::Size(24, 167);
			this->tsFileList->TabIndex = 1;
			this->tsFileList->Text = L"toolStrip2";
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(21, 20);
			this->toolStripButton5->Text = L"toolStripButton5";
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(21, 20);
			this->toolStripButton6->Text = L"toolStripButton6";
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(21, 20);
			this->toolStripButton7->Text = L"toolStripButton7";
			// 
			// fileList
			// 
			this->fileList->AllowDrop = true;
			this->fileList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->fileList->Location = System::Drawing::Point(3, 6);
			this->fileList->Name = L"fileList";
			this->fileList->Size = System::Drawing::Size(567, 158);
			this->fileList->TabIndex = 0;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::List;
			this->fileList->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragEnter);
			this->fileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragDrop);
			// 
			// panelNavigation
			// 
			this->panelNavigation->Controls->Add(this->buttonPreviousStep);
			this->panelNavigation->Controls->Add(this->buttonNextStep);
			this->panelNavigation->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelNavigation->Location = System::Drawing::Point(0, 0);
			this->panelNavigation->Name = L"panelNavigation";
			this->panelNavigation->Size = System::Drawing::Size(597, 31);
			this->panelNavigation->TabIndex = 9;
			// 
			// buttonPreviousStep
			// 
			this->buttonPreviousStep->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPreviousStep->Location = System::Drawing::Point(429, 7);
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
			this->buttonNextStep->Location = System::Drawing::Point(510, 7);
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
			// WizardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(742, 477);
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
			this->panelStepRuleset->ResumeLayout(false);
			this->panelStepRuleset->PerformLayout();
			this->panelStepGemReplacements->ResumeLayout(false);
			this->panelStepGemReplacements->PerformLayout();
			this->panelStepGems->ResumeLayout(false);
			this->panelStepGems->PerformLayout();
			this->panelStepInputRuleReplacements->ResumeLayout(false);
			this->panelStepInputRuleReplacements->PerformLayout();
			this->panelStepRulesetReplacements->ResumeLayout(false);
			this->panelStepRulesetReplacements->PerformLayout();
			this->panelStepInputRule->ResumeLayout(false);
			this->panelStepInputRule->PerformLayout();
			this->panelStepOutputFormat->ResumeLayout(false);
			this->panelStepOutputFormat->PerformLayout();
			this->tsOutputFormat->ResumeLayout(false);
			this->tsOutputFormat->PerformLayout();
			this->panelFilelist->ResumeLayout(false);
			this->panelFilelist->PerformLayout();
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

			if(mRuleset != NULL)
				delete mRuleset ;

			try {
				mRuleset  = new Ruleset(toStdWString(rulesetFileName));
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


			if(mRuleset)
				delete mRuleset;

			try {
				mRuleset = new Ruleset(toStdWString(filename));
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
				if(mStep == Step::STEP_RULESET_SELECT && newStep == Step::STEP_RULESET_REPLACEMENTS) {
					if(mRuleset != NULL) {
						mMaxStep = Step::STEP_OUTPUTFORMAT_SELECT;
						refreshOutputFormatList();
					}
				}
			}

			if(int(newStep) < 0 || int(newStep) >= int(Step::STEP_MAX) || newStep > mMaxStep) {
				return ;
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

		void refreshOutputFormatList() {
			if(mRuleset) {
				vector<OutputFormat> outputFormatVector = mRuleset->getOutputFormats();
				
				lstOutputFormat->Items->Clear();				
				for(unsigned int i=0; i<outputFormatVector.size(); i++) {
					ListViewItem^ newListViewItem = gcnew ListViewItem(toClrString(outputFormatVector[i].getFormat()));
					newListViewItem->Tag = outputFormatVector[i].getRowId();
					lstOutputFormat->Items->Add(newListViewItem);
				}
			}
		}

#pragma endregion
#pragma region Event Handlers
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
	private: System::Void WizardForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 stepPanelList = gcnew System::Collections::Generic::List<Panel^>();
				 stepPanelList->Add(panelStepRuleset);
				 stepPanelList->Add(panelStepRulesetReplacements);
				 stepPanelList->Add(panelStepOutputFormat);
				 stepPanelList->Add(panelStepInputRule);
				 stepPanelList->Add(panelStepInputRuleReplacements);
				 stepPanelList->Add(panelStepGems);
				 stepPanelList->Add(panelStepGemReplacements);

				 stepButtonList = gcnew System::Collections::Generic::List<ToolStripButton^>();
				 stepButtonList->Add(tsStepRuleset);
				 stepButtonList->Add(tsStepRulesetReplacements);
				 stepButtonList->Add(tsStepOutputFormat);
				 stepButtonList->Add(tsStepInputRule);
				 stepButtonList->Add(tsStepInputRuleReplacements);
				 stepButtonList->Add(tsStepGems);
				 stepButtonList->Add(tsStepGemReplacements);

				 //! select first step
				 setMaxStep(Step::STEP_RULESET_SELECT);
				 setStep(Step::STEP_RULESET_SELECT);
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
private: System::Void tsStepRulesetReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_RULESET_REPLACEMENTS);
		 }
private: System::Void tsStepInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_INPUTRULES_SELECT);
		 }
private: System::Void tsStepInputRuleReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_INPUTRULE_REPLACEMENTS);
		 }
private: System::Void tsStepGems_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_GEMS_SELECT);
		 }
private: System::Void tsStepGemReplacements_Click(System::Object^  sender, System::EventArgs^  e) {
			 setStep(Step::STEP_GEM_REPLACEMENTS);
		 }
private: System::Void buttonRulesetOpenDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 openRulesetFileDialog->ShowDialog();
		 }
private: System::Void buttonRulesetSaveDialog_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveRulesetFileDialog->ShowDialog();
		 }
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
private: System::Void tsAddOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStdString(txtOutputFormat->Text));

			 refreshOutputFormatList();
		 }
};
// --- don't delete after this line (and one line before this line) --- //
}
#pragma endregion

