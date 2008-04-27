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
#include "UserInterfaceCustomStrings.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Security::Permissions;
using namespace System::Threading;
using namespace System::Resources;
using namespace System::Reflection;

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
	/*	
	GEMS_SELECT = 4,
	AFTER_REPLACEMENTS = 5,
	RENAME = 6,*/
	MAX = 4
};

		 // Business Logic Member Variables
private: Ruleset* mRuleset;
private: sqlite_int64 mOutputFormatID;
private: sqlite_int64 mInputRuleID;
private: sqlite_int64 mGemID;
private: List<String^> mFiles;
private: List<String^> mKnownRulesets;
private: Step mStep;
private: Step mMaxStep;
private: bool mShowOnlyMatchingFiles;
private: List<Panel^>^ mStepPanelList;
private: List<ToolStripButton^>^ mStepButtonList;
private: System::ComponentModel::ComponentResourceManager^  mCustomStrings;

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

		 // Panels
private: System::Windows::Forms::Panel^  panelStepRuleset;
private: System::Windows::Forms::Panel^  panelStepBeforeReplacements;
private: System::Windows::Forms::Panel^  panelStepOutputFormat;
private: System::Windows::Forms::Panel^  panelStepInputRule;
private: System::Windows::Forms::Panel^  panelStepGems;
private: System::Windows::Forms::Panel^  panelStepAfterReplacements;
private: System::Windows::Forms::Panel^  panelStepRename;
private: System::Windows::Forms::Panel^  panelFilelist;
private: System::Windows::Forms::Panel^  panelNavigation;
private: System::Windows::Forms::Panel^  panelCboRulesets;
private: System::Windows::Forms::Panel^  panelLstOutputFormats;
private: System::Windows::Forms::Panel^  panelTxtOutputFormat;
private: System::Windows::Forms::Panel^  panelLstInputRules;
private: System::Windows::Forms::Panel^  panelTxtInputRule;
private: System::Windows::Forms::SplitContainer^  splitContainer;

		 // Buttons for switching between the steps
private: System::Windows::Forms::Button^  buttonPreviousStep;
private: System::Windows::Forms::Button^  buttonNextStep;

		 // Panel 'Ruleset'
private: System::Windows::Forms::SaveFileDialog^  saveRulesetFileDialog;
private: System::Windows::Forms::OpenFileDialog^  openRulesetFileDialog;

		 // Panel 'BeforeReplacements'
private: System::Windows::Forms::DataGridView^  gridBeforeReplacements;

		 // Panel 'OutputFormats'
private: System::Windows::Forms::ListBox^  lstOutputFormat;
private: System::Windows::Forms::RichTextBox^  txtOutputFormat;

private: System::Windows::Forms::ToolStrip^  tsOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsAddOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDeleteOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateOutputFormat;
private: System::Windows::Forms::ToolStripButton^  tsSaveOutputFormat;

		 // Panel 'InputRules'
private: System::Windows::Forms::RichTextBox^  txtInputRule;
private: System::Windows::Forms::ListBox^  lstInputRules;

private: System::Windows::Forms::ToolStrip^  tsInputRuleButtons;
private: System::Windows::Forms::ToolStripButton^  tsAddInputRule;
private: System::Windows::Forms::ToolStripButton^  tsRemoveInputRule;
private: System::Windows::Forms::ToolStripButton^  tsDuplicateInputRule;

		 // Panel 'fileList'
private: System::Windows::Forms::ToolStrip^  tsFileList;
private: System::Windows::Forms::ToolStripButton^  tsAddFiles;
private: System::Windows::Forms::ToolStripButton^  tsRemoveFileFromList;
private: System::Windows::Forms::ToolStripButton^  tsApplyChanges;
private: System::Windows::Forms::ToolStrip^  tsTxtOutputFormat;

			 // Controls for the Panel 'Gems'
			 // Controls for the Panel 'AfterReplacements'
			 // Controls for the Panel 'Rename'
	// Container for the Panel of the current Step (Panel Child will have Dock = Fill)
    // List of all files relevant to current ruleset
	// tool strip for file list operations
    // to do: categorize the remaining Controls or make them non-member variables

private: System::Windows::Forms::ListView^  fileList;
private: System::Windows::Forms::OpenFileDialog^  fileListopenFileDiag;
private: System::Windows::Forms::ColumnHeader^  chFile;
private: System::Windows::Forms::DataGridView^  gridAfterReplacements;
private: System::Windows::Forms::ToolStrip^  tsRuleset;
private: System::Windows::Forms::ToolStripButton^  tsLoadRulesetDialog;
private: System::Windows::Forms::ToolStripButton^  tsSaveRulesetDialog;
private: System::Windows::Forms::ComboBox^  cboRulesets;
private: System::Windows::Forms::ToolStripButton^  tsDebugAddFiles;
private: System::Windows::Forms::ToolStrip^  toolStrip3;
private: System::Windows::Forms::ToolStripButton^  tsSaveInputRule;

private: System::Windows::Forms::ToolStripButton^  tsDebugLoadRuleset;
private: System::Windows::Forms::RichTextBox^  txtGemInputRule;
private: System::Windows::Forms::Button^  buttonRenameFiles;
private: System::Windows::Forms::Label^  messageLabel;
private: System::Windows::Forms::TextBox^  txtOutputFormatBorder;
private: System::Windows::Forms::TextBox^  txtInputRuleBorder;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnAfterReplacementsID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnAfterReplacementsGroupID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnAfterReplacementsSearch;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnAfterReplacementsReplace;


private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsGroupID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsSearch;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsReplace;


private: System::Windows::Forms::ToolStripButton^  tsRenameFiles;
private: System::Windows::Forms::CheckBox^  checkBoxShowOnlyMatchingFiles;
private: System::Windows::Forms::DataGridView^  gridGems;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GemColumnPosition;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  GemColumnGem;
private: System::Windows::Forms::ToolStripButton^  tsAddFolders;
private: System::Windows::Forms::FolderBrowserDialog^  fileListopenFolderDiag;
private: System::Windows::Forms::Panel^  innerPanelInputRules;
private: System::Windows::Forms::ToolStripButton^  tsUseAsNewInputRule;
private: System::Windows::Forms::ToolStripButton^  tsUseAsNewOutputFormat;






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
			System::Windows::Forms::Label^  label8;
			System::Windows::Forms::Label^  label6;
			System::Windows::Forms::Label^  label9;
			System::Windows::Forms::Label^  label4;
			System::Windows::Forms::Label^  label11;
			System::Windows::Forms::Label^  label5;
			System::Windows::Forms::Label^  label14;
			System::Windows::Forms::Label^  label3;
			System::Windows::Forms::Label^  label2;
			System::Windows::Forms::Label^  label10;
			System::Windows::Forms::Label^  label7;
			System::Windows::Forms::Panel^  panelFileListInner;
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle14 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle15 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle16 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle17 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle18 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->tsFileList = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsAddFolders = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveFileFromList = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsApplyChanges = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDebugAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRenameFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsUseAsNewOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsUseAsNewInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->panelStepContent = (gcnew System::Windows::Forms::Panel());
			this->panelStepInputRule = (gcnew System::Windows::Forms::Panel());
			this->innerPanelInputRules = (gcnew System::Windows::Forms::Panel());
			this->panelLstInputRules = (gcnew System::Windows::Forms::Panel());
			this->tsInputRuleButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstInputRules = (gcnew System::Windows::Forms::ListBox());
			this->panelTxtInputRule = (gcnew System::Windows::Forms::Panel());
			this->txtInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->txtInputRuleBorder = (gcnew System::Windows::Forms::TextBox());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->gridGems = (gcnew System::Windows::Forms::DataGridView());
			this->GemColumnPosition = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GemColumnGem = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->panelStepBeforeReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridBeforeReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnBeforeReplacementsID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsGroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsSearch = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsReplace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelStepRuleset = (gcnew System::Windows::Forms::Panel());
			this->checkBoxShowOnlyMatchingFiles = (gcnew System::Windows::Forms::CheckBox());
			this->panelCboRulesets = (gcnew System::Windows::Forms::Panel());
			this->tsRuleset = (gcnew System::Windows::Forms::ToolStrip());
			this->tsLoadRulesetDialog = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsSaveRulesetDialog = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDebugLoadRuleset = (gcnew System::Windows::Forms::ToolStripButton());
			this->cboRulesets = (gcnew System::Windows::Forms::ComboBox());
			this->panelStepGems = (gcnew System::Windows::Forms::Panel());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->txtGemInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->panelStepAfterReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridAfterReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnAfterReplacementsID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsGroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsSearch = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsReplace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelStepOutputFormat = (gcnew System::Windows::Forms::Panel());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->panelTxtOutputFormat = (gcnew System::Windows::Forms::Panel());
			this->txtOutputFormat = (gcnew System::Windows::Forms::RichTextBox());
			this->txtOutputFormatBorder = (gcnew System::Windows::Forms::TextBox());
			this->tsTxtOutputFormat = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->panelLstOutputFormats = (gcnew System::Windows::Forms::Panel());
			this->tsOutputFormat = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDeleteOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstOutputFormat = (gcnew System::Windows::Forms::ListBox());
			this->panelStepRename = (gcnew System::Windows::Forms::Panel());
			this->buttonRenameFiles = (gcnew System::Windows::Forms::Button());
			this->panelNavigation = (gcnew System::Windows::Forms::Panel());
			this->messageLabel = (gcnew System::Windows::Forms::Label());
			this->buttonPreviousStep = (gcnew System::Windows::Forms::Button());
			this->buttonNextStep = (gcnew System::Windows::Forms::Button());
			this->panelFilelist = (gcnew System::Windows::Forms::Panel());
			this->tsStepButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsStepRuleset = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepBeforeReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepOutputFormat = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepGems = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepAfterReplacements = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsStepRename = (gcnew System::Windows::Forms::ToolStripButton());
			this->openRulesetFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveRulesetFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->fileListopenFileDiag = (gcnew System::Windows::Forms::OpenFileDialog());
			this->fileListopenFolderDiag = (gcnew System::Windows::Forms::FolderBrowserDialog());
			label1 = (gcnew System::Windows::Forms::Label());
			label8 = (gcnew System::Windows::Forms::Label());
			label6 = (gcnew System::Windows::Forms::Label());
			label9 = (gcnew System::Windows::Forms::Label());
			label4 = (gcnew System::Windows::Forms::Label());
			label11 = (gcnew System::Windows::Forms::Label());
			label5 = (gcnew System::Windows::Forms::Label());
			label14 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label10 = (gcnew System::Windows::Forms::Label());
			label7 = (gcnew System::Windows::Forms::Label());
			panelFileListInner = (gcnew System::Windows::Forms::Panel());
			panelFileListInner->SuspendLayout();
			this->tsFileList->SuspendLayout();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->panelStepContent->SuspendLayout();
			this->panelStepInputRule->SuspendLayout();
			this->innerPanelInputRules->SuspendLayout();
			this->panelLstInputRules->SuspendLayout();
			this->tsInputRuleButtons->SuspendLayout();
			this->panelTxtInputRule->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->BeginInit();
			this->panelStepBeforeReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->BeginInit();
			this->panelStepRuleset->SuspendLayout();
			this->panelCboRulesets->SuspendLayout();
			this->tsRuleset->SuspendLayout();
			this->panelStepGems->SuspendLayout();
			this->panelStepAfterReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->BeginInit();
			this->panelStepOutputFormat->SuspendLayout();
			this->panelTxtOutputFormat->SuspendLayout();
			this->tsTxtOutputFormat->SuspendLayout();
			this->panelLstOutputFormats->SuspendLayout();
			this->tsOutputFormat->SuspendLayout();
			this->panelStepRename->SuspendLayout();
			this->panelNavigation->SuspendLayout();
			this->panelFilelist->SuspendLayout();
			this->tsStepButtons->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			resources->ApplyResources(label1, L"label1");
			label1->Name = L"label1";
			// 
			// label8
			// 
			resources->ApplyResources(label8, L"label8");
			label8->Name = L"label8";
			// 
			// label6
			// 
			resources->ApplyResources(label6, L"label6");
			label6->Name = L"label6";
			// 
			// label9
			// 
			resources->ApplyResources(label9, L"label9");
			label9->Name = L"label9";
			// 
			// label4
			// 
			resources->ApplyResources(label4, L"label4");
			label4->Name = L"label4";
			// 
			// label11
			// 
			resources->ApplyResources(label11, L"label11");
			label11->Name = L"label11";
			// 
			// label5
			// 
			resources->ApplyResources(label5, L"label5");
			label5->Name = L"label5";
			// 
			// label14
			// 
			resources->ApplyResources(label14, L"label14");
			label14->Name = L"label14";
			// 
			// label3
			// 
			resources->ApplyResources(label3, L"label3");
			label3->Name = L"label3";
			// 
			// label2
			// 
			resources->ApplyResources(label2, L"label2");
			label2->Name = L"label2";
			// 
			// label10
			// 
			resources->ApplyResources(label10, L"label10");
			label10->Name = L"label10";
			// 
			// label7
			// 
			resources->ApplyResources(label7, L"label7");
			label7->Name = L"label7";
			// 
			// panelFileListInner
			// 
			resources->ApplyResources(panelFileListInner, L"panelFileListInner");
			panelFileListInner->Controls->Add(this->tsFileList);
			panelFileListInner->Controls->Add(this->fileList);
			panelFileListInner->Name = L"panelFileListInner";
			// 
			// tsFileList
			// 
			resources->ApplyResources(this->tsFileList, L"tsFileList");
			this->tsFileList->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsFileList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->tsAddFiles, this->tsAddFolders, 
				this->tsRemoveFileFromList, this->tsApplyChanges, this->tsDebugAddFiles, this->tsRenameFiles, this->tsUseAsNewOutputFormat, this->tsUseAsNewInputRule});
			this->tsFileList->Name = L"tsFileList";
			// 
			// tsAddFiles
			// 
			this->tsAddFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsAddFiles, L"tsAddFiles");
			this->tsAddFiles->Name = L"tsAddFiles";
			this->tsAddFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsAddFiles_Click);
			// 
			// tsAddFolders
			// 
			this->tsAddFolders->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsAddFolders, L"tsAddFolders");
			this->tsAddFolders->Name = L"tsAddFolders";
			this->tsAddFolders->Click += gcnew System::EventHandler(this, &WizardForm::tsAddFolders_Click);
			// 
			// tsRemoveFileFromList
			// 
			this->tsRemoveFileFromList->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsRemoveFileFromList, L"tsRemoveFileFromList");
			this->tsRemoveFileFromList->Name = L"tsRemoveFileFromList";
			this->tsRemoveFileFromList->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveFileFromList_Click);
			// 
			// tsApplyChanges
			// 
			this->tsApplyChanges->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsApplyChanges, L"tsApplyChanges");
			this->tsApplyChanges->Name = L"tsApplyChanges";
			this->tsApplyChanges->Click += gcnew System::EventHandler(this, &WizardForm::tsApplyChanges_Click);
			// 
			// tsDebugAddFiles
			// 
			this->tsDebugAddFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsDebugAddFiles, L"tsDebugAddFiles");
			this->tsDebugAddFiles->Name = L"tsDebugAddFiles";
			this->tsDebugAddFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsDebugAddFiles_Click);
			// 
			// tsRenameFiles
			// 
			this->tsRenameFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsRenameFiles, L"tsRenameFiles");
			this->tsRenameFiles->Name = L"tsRenameFiles";
			this->tsRenameFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsRenameFiles_Click);
			// 
			// tsUseAsNewOutputFormat
			// 
			this->tsUseAsNewOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsUseAsNewOutputFormat, L"tsUseAsNewOutputFormat");
			this->tsUseAsNewOutputFormat->Name = L"tsUseAsNewOutputFormat";
			this->tsUseAsNewOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsUseAsNewOutputFormat_Click);
			// 
			// tsUseAsNewInputRule
			// 
			this->tsUseAsNewInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsUseAsNewInputRule, L"tsUseAsNewInputRule");
			this->tsUseAsNewInputRule->Name = L"tsUseAsNewInputRule";
			this->tsUseAsNewInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsUseAsNewInputRule_Click);
			// 
			// fileList
			// 
			this->fileList->AllowDrop = true;
			resources->ApplyResources(this->fileList, L"fileList");
			this->fileList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->chFile});
			this->fileList->FullRowSelect = true;
			this->fileList->GridLines = true;
			this->fileList->Name = L"fileList";
			this->fileList->ShowGroups = false;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::Details;
			this->fileList->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &WizardForm::fileList_MouseDoubleClick);
			this->fileList->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::fileList_SelectedIndexChanged);
			this->fileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragDrop);
			this->fileList->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragEnter);
			this->fileList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::fileList_KeyDown);
			// 
			// chFile
			// 
			resources->ApplyResources(this->chFile, L"chFile");
			// 
			// splitContainer
			// 
			this->splitContainer->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->splitContainer, L"splitContainer");
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->panelStepContent);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Controls->Add(this->panelFilelist);
			// 
			// panelStepContent
			// 
			this->panelStepContent->Controls->Add(this->panelStepInputRule);
			this->panelStepContent->Controls->Add(this->panelStepBeforeReplacements);
			this->panelStepContent->Controls->Add(this->panelStepRuleset);
			this->panelStepContent->Controls->Add(this->panelStepGems);
			this->panelStepContent->Controls->Add(this->panelStepAfterReplacements);
			this->panelStepContent->Controls->Add(this->panelStepOutputFormat);
			this->panelStepContent->Controls->Add(this->panelStepRename);
			this->panelStepContent->Controls->Add(this->panelNavigation);
			resources->ApplyResources(this->panelStepContent, L"panelStepContent");
			this->panelStepContent->Name = L"panelStepContent";
			// 
			// panelStepInputRule
			// 
			this->panelStepInputRule->Controls->Add(this->innerPanelInputRules);
			this->panelStepInputRule->Controls->Add(this->gridGems);
			this->panelStepInputRule->Controls->Add(label14);
			this->panelStepInputRule->Controls->Add(label3);
			resources->ApplyResources(this->panelStepInputRule, L"panelStepInputRule");
			this->panelStepInputRule->Name = L"panelStepInputRule";
			// 
			// innerPanelInputRules
			// 
			resources->ApplyResources(this->innerPanelInputRules, L"innerPanelInputRules");
			this->innerPanelInputRules->Controls->Add(this->panelLstInputRules);
			this->innerPanelInputRules->Controls->Add(this->panelTxtInputRule);
			this->innerPanelInputRules->Name = L"innerPanelInputRules";
			// 
			// panelLstInputRules
			// 
			resources->ApplyResources(this->panelLstInputRules, L"panelLstInputRules");
			this->panelLstInputRules->Controls->Add(this->tsInputRuleButtons);
			this->panelLstInputRules->Controls->Add(this->lstInputRules);
			this->panelLstInputRules->Name = L"panelLstInputRules";
			// 
			// tsInputRuleButtons
			// 
			resources->ApplyResources(this->tsInputRuleButtons, L"tsInputRuleButtons");
			this->tsInputRuleButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsInputRuleButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddInputRule, 
				this->tsRemoveInputRule, this->tsDuplicateInputRule});
			this->tsInputRuleButtons->Name = L"tsInputRuleButtons";
			// 
			// tsAddInputRule
			// 
			this->tsAddInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsAddInputRule, L"tsAddInputRule");
			this->tsAddInputRule->Name = L"tsAddInputRule";
			this->tsAddInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsAddInputRule_Click);
			// 
			// tsRemoveInputRule
			// 
			this->tsRemoveInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsRemoveInputRule, L"tsRemoveInputRule");
			this->tsRemoveInputRule->Name = L"tsRemoveInputRule";
			this->tsRemoveInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsRemoveInputRule_Click);
			// 
			// tsDuplicateInputRule
			// 
			this->tsDuplicateInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsDuplicateInputRule, L"tsDuplicateInputRule");
			this->tsDuplicateInputRule->Name = L"tsDuplicateInputRule";
			this->tsDuplicateInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateInputRule_Click);
			// 
			// lstInputRules
			// 
			resources->ApplyResources(this->lstInputRules, L"lstInputRules");
			this->lstInputRules->FormattingEnabled = true;
			this->lstInputRules->Name = L"lstInputRules";
			this->lstInputRules->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstInputRules_SelectedIndexChanged);
			// 
			// panelTxtInputRule
			// 
			resources->ApplyResources(this->panelTxtInputRule, L"panelTxtInputRule");
			this->panelTxtInputRule->Controls->Add(this->txtInputRule);
			this->panelTxtInputRule->Controls->Add(this->txtInputRuleBorder);
			this->panelTxtInputRule->Controls->Add(this->toolStrip3);
			this->panelTxtInputRule->Name = L"panelTxtInputRule";
			// 
			// txtInputRule
			// 
			resources->ApplyResources(this->txtInputRule, L"txtInputRule");
			this->txtInputRule->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtInputRule->Name = L"txtInputRule";
			this->txtInputRule->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtInputRule_KeyDown);
			this->txtInputRule->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtInputRule_TextChanged);
			// 
			// txtInputRuleBorder
			// 
			resources->ApplyResources(this->txtInputRuleBorder, L"txtInputRuleBorder");
			this->txtInputRuleBorder->Name = L"txtInputRuleBorder";
			// 
			// toolStrip3
			// 
			resources->ApplyResources(this->toolStrip3, L"toolStrip3");
			this->toolStrip3->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip3->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveInputRule});
			this->toolStrip3->Name = L"toolStrip3";
			// 
			// tsSaveInputRule
			// 
			this->tsSaveInputRule->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsSaveInputRule, L"tsSaveInputRule");
			this->tsSaveInputRule->Name = L"tsSaveInputRule";
			this->tsSaveInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveInputRule_Click);
			// 
			// gridGems
			// 
			this->gridGems->AllowUserToAddRows = false;
			this->gridGems->AllowUserToDeleteRows = false;
			this->gridGems->AllowUserToResizeRows = false;
			resources->ApplyResources(this->gridGems, L"gridGems");
			this->gridGems->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle10->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle10->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle10->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle10->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle10->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle10->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridGems->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle10;
			this->gridGems->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridGems->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->GemColumnPosition, 
				this->GemColumnGem});
			dataGridViewCellStyle11->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle11->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle11->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle11->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle11->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle11->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridGems->DefaultCellStyle = dataGridViewCellStyle11;
			this->gridGems->MultiSelect = false;
			this->gridGems->Name = L"gridGems";
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle12->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle12->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle12->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle12->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle12->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridGems->RowHeadersDefaultCellStyle = dataGridViewCellStyle12;
			this->gridGems->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &WizardForm::gridGems_CellValueChanged);
			this->gridGems->SelectionChanged += gcnew System::EventHandler(this, &WizardForm::gridGems_SelectionChanged);
			// 
			// GemColumnPosition
			// 
			this->GemColumnPosition->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->GemColumnPosition->FillWeight = 69;
			resources->ApplyResources(this->GemColumnPosition, L"GemColumnPosition");
			this->GemColumnPosition->Name = L"GemColumnPosition";
			this->GemColumnPosition->ReadOnly = true;
			// 
			// GemColumnGem
			// 
			this->GemColumnGem->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			resources->ApplyResources(this->GemColumnGem, L"GemColumnGem");
			this->GemColumnGem->Name = L"GemColumnGem";
			this->GemColumnGem->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->GemColumnGem->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			// 
			// panelStepBeforeReplacements
			// 
			this->panelStepBeforeReplacements->Controls->Add(label9);
			this->panelStepBeforeReplacements->Controls->Add(this->gridBeforeReplacements);
			this->panelStepBeforeReplacements->Controls->Add(label4);
			resources->ApplyResources(this->panelStepBeforeReplacements, L"panelStepBeforeReplacements");
			this->panelStepBeforeReplacements->Name = L"panelStepBeforeReplacements";
			// 
			// gridBeforeReplacements
			// 
			this->gridBeforeReplacements->AllowDrop = true;
			resources->ApplyResources(this->gridBeforeReplacements, L"gridBeforeReplacements");
			this->gridBeforeReplacements->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle13->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle13->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle13->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle13->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle13->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle13->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle13;
			this->gridBeforeReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridBeforeReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ColumnBeforeReplacementsID, 
				this->ColumnBeforeReplacementsGroupID, this->ColumnBeforeReplacementsSearch, this->ColumnBeforeReplacementsReplace});
			dataGridViewCellStyle14->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle14->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle14->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle14->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle14->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle14->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridBeforeReplacements->DefaultCellStyle = dataGridViewCellStyle14;
			this->gridBeforeReplacements->Name = L"gridBeforeReplacements";
			dataGridViewCellStyle15->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle15->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle15->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle15->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle15->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle15->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle15;
			this->gridBeforeReplacements->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &WizardForm::gridBeforeReplacements_CellValueChanged);
			this->gridBeforeReplacements->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &WizardForm::gridBeforeReplacements_Scroll);
			// 
			// ColumnBeforeReplacementsID
			// 
			resources->ApplyResources(this->ColumnBeforeReplacementsID, L"ColumnBeforeReplacementsID");
			this->ColumnBeforeReplacementsID->Name = L"ColumnBeforeReplacementsID";
			// 
			// ColumnBeforeReplacementsGroupID
			// 
			resources->ApplyResources(this->ColumnBeforeReplacementsGroupID, L"ColumnBeforeReplacementsGroupID");
			this->ColumnBeforeReplacementsGroupID->Name = L"ColumnBeforeReplacementsGroupID";
			// 
			// ColumnBeforeReplacementsSearch
			// 
			this->ColumnBeforeReplacementsSearch->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			resources->ApplyResources(this->ColumnBeforeReplacementsSearch, L"ColumnBeforeReplacementsSearch");
			this->ColumnBeforeReplacementsSearch->Name = L"ColumnBeforeReplacementsSearch";
			// 
			// ColumnBeforeReplacementsReplace
			// 
			this->ColumnBeforeReplacementsReplace->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			resources->ApplyResources(this->ColumnBeforeReplacementsReplace, L"ColumnBeforeReplacementsReplace");
			this->ColumnBeforeReplacementsReplace->Name = L"ColumnBeforeReplacementsReplace";
			// 
			// panelStepRuleset
			// 
			this->panelStepRuleset->Controls->Add(this->checkBoxShowOnlyMatchingFiles);
			this->panelStepRuleset->Controls->Add(label8);
			this->panelStepRuleset->Controls->Add(this->panelCboRulesets);
			this->panelStepRuleset->Controls->Add(label1);
			resources->ApplyResources(this->panelStepRuleset, L"panelStepRuleset");
			this->panelStepRuleset->Name = L"panelStepRuleset";
			// 
			// checkBoxShowOnlyMatchingFiles
			// 
			resources->ApplyResources(this->checkBoxShowOnlyMatchingFiles, L"checkBoxShowOnlyMatchingFiles");
			this->checkBoxShowOnlyMatchingFiles->Name = L"checkBoxShowOnlyMatchingFiles";
			this->checkBoxShowOnlyMatchingFiles->UseVisualStyleBackColor = true;
			this->checkBoxShowOnlyMatchingFiles->CheckedChanged += gcnew System::EventHandler(this, &WizardForm::checkBoxShowOnlyMatchingFiles_CheckedChanged);
			// 
			// panelCboRulesets
			// 
			resources->ApplyResources(this->panelCboRulesets, L"panelCboRulesets");
			this->panelCboRulesets->Controls->Add(this->tsRuleset);
			this->panelCboRulesets->Controls->Add(this->cboRulesets);
			this->panelCboRulesets->Name = L"panelCboRulesets";
			// 
			// tsRuleset
			// 
			resources->ApplyResources(this->tsRuleset, L"tsRuleset");
			this->tsRuleset->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsRuleset->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsLoadRulesetDialog, 
				this->tsSaveRulesetDialog, this->tsDebugLoadRuleset});
			this->tsRuleset->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->tsRuleset->Name = L"tsRuleset";
			// 
			// tsLoadRulesetDialog
			// 
			this->tsLoadRulesetDialog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsLoadRulesetDialog, L"tsLoadRulesetDialog");
			this->tsLoadRulesetDialog->Name = L"tsLoadRulesetDialog";
			this->tsLoadRulesetDialog->Click += gcnew System::EventHandler(this, &WizardForm::tsLoadRulesetDialog_Click);
			// 
			// tsSaveRulesetDialog
			// 
			this->tsSaveRulesetDialog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsSaveRulesetDialog, L"tsSaveRulesetDialog");
			this->tsSaveRulesetDialog->Name = L"tsSaveRulesetDialog";
			this->tsSaveRulesetDialog->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveRulesetDialog_Click);
			// 
			// tsDebugLoadRuleset
			// 
			this->tsDebugLoadRuleset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsDebugLoadRuleset, L"tsDebugLoadRuleset");
			this->tsDebugLoadRuleset->Name = L"tsDebugLoadRuleset";
			this->tsDebugLoadRuleset->Click += gcnew System::EventHandler(this, &WizardForm::tsDebugLoadRuleset_Click);
			// 
			// cboRulesets
			// 
			resources->ApplyResources(this->cboRulesets, L"cboRulesets");
			this->cboRulesets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboRulesets->FormattingEnabled = true;
			this->cboRulesets->Name = L"cboRulesets";
			this->cboRulesets->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::cboRulesets_SelectedIndexChanged);
			// 
			// panelStepGems
			// 
			this->panelStepGems->Controls->Add(this->label13);
			this->panelStepGems->Controls->Add(this->txtGemInputRule);
			this->panelStepGems->Controls->Add(label6);
			resources->ApplyResources(this->panelStepGems, L"panelStepGems");
			this->panelStepGems->Name = L"panelStepGems";
			// 
			// label13
			// 
			resources->ApplyResources(this->label13, L"label13");
			this->label13->Name = L"label13";
			// 
			// txtGemInputRule
			// 
			resources->ApplyResources(this->txtGemInputRule, L"txtGemInputRule");
			this->txtGemInputRule->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtGemInputRule->Name = L"txtGemInputRule";
			this->txtGemInputRule->ReadOnly = true;
			// 
			// panelStepAfterReplacements
			// 
			this->panelStepAfterReplacements->Controls->Add(label11);
			this->panelStepAfterReplacements->Controls->Add(this->gridAfterReplacements);
			this->panelStepAfterReplacements->Controls->Add(label5);
			resources->ApplyResources(this->panelStepAfterReplacements, L"panelStepAfterReplacements");
			this->panelStepAfterReplacements->Name = L"panelStepAfterReplacements";
			// 
			// gridAfterReplacements
			// 
			this->gridAfterReplacements->AllowDrop = true;
			resources->ApplyResources(this->gridAfterReplacements, L"gridAfterReplacements");
			this->gridAfterReplacements->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle16->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle16->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle16->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle16->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle16->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle16->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle16;
			this->gridAfterReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridAfterReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ColumnAfterReplacementsID, 
				this->ColumnAfterReplacementsGroupID, this->ColumnAfterReplacementsSearch, this->ColumnAfterReplacementsReplace});
			dataGridViewCellStyle17->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle17->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle17->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle17->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle17->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle17->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridAfterReplacements->DefaultCellStyle = dataGridViewCellStyle17;
			this->gridAfterReplacements->Name = L"gridAfterReplacements";
			dataGridViewCellStyle18->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle18->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle18->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle18->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle18->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle18->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle18;
			// 
			// ColumnAfterReplacementsID
			// 
			resources->ApplyResources(this->ColumnAfterReplacementsID, L"ColumnAfterReplacementsID");
			this->ColumnAfterReplacementsID->Name = L"ColumnAfterReplacementsID";
			// 
			// ColumnAfterReplacementsGroupID
			// 
			resources->ApplyResources(this->ColumnAfterReplacementsGroupID, L"ColumnAfterReplacementsGroupID");
			this->ColumnAfterReplacementsGroupID->Name = L"ColumnAfterReplacementsGroupID";
			// 
			// ColumnAfterReplacementsSearch
			// 
			this->ColumnAfterReplacementsSearch->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			resources->ApplyResources(this->ColumnAfterReplacementsSearch, L"ColumnAfterReplacementsSearch");
			this->ColumnAfterReplacementsSearch->Name = L"ColumnAfterReplacementsSearch";
			// 
			// ColumnAfterReplacementsReplace
			// 
			this->ColumnAfterReplacementsReplace->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			resources->ApplyResources(this->ColumnAfterReplacementsReplace, L"ColumnAfterReplacementsReplace");
			this->ColumnAfterReplacementsReplace->Name = L"ColumnAfterReplacementsReplace";
			// 
			// panelStepOutputFormat
			// 
			this->panelStepOutputFormat->Controls->Add(this->label12);
			this->panelStepOutputFormat->Controls->Add(this->panelTxtOutputFormat);
			this->panelStepOutputFormat->Controls->Add(this->panelLstOutputFormats);
			this->panelStepOutputFormat->Controls->Add(label2);
			resources->ApplyResources(this->panelStepOutputFormat, L"panelStepOutputFormat");
			this->panelStepOutputFormat->Name = L"panelStepOutputFormat";
			// 
			// label12
			// 
			resources->ApplyResources(this->label12, L"label12");
			this->label12->Name = L"label12";
			// 
			// panelTxtOutputFormat
			// 
			resources->ApplyResources(this->panelTxtOutputFormat, L"panelTxtOutputFormat");
			this->panelTxtOutputFormat->Controls->Add(this->txtOutputFormat);
			this->panelTxtOutputFormat->Controls->Add(this->txtOutputFormatBorder);
			this->panelTxtOutputFormat->Controls->Add(this->tsTxtOutputFormat);
			this->panelTxtOutputFormat->Name = L"panelTxtOutputFormat";
			// 
			// txtOutputFormat
			// 
			resources->ApplyResources(this->txtOutputFormat, L"txtOutputFormat");
			this->txtOutputFormat->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WizardForm::txtOutputFormat_KeyDown);
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &WizardForm::txtOutputFormat_TextChanged);
			// 
			// txtOutputFormatBorder
			// 
			resources->ApplyResources(this->txtOutputFormatBorder, L"txtOutputFormatBorder");
			this->txtOutputFormatBorder->Name = L"txtOutputFormatBorder";
			// 
			// tsTxtOutputFormat
			// 
			resources->ApplyResources(this->tsTxtOutputFormat, L"tsTxtOutputFormat");
			this->tsTxtOutputFormat->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsTxtOutputFormat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsSaveOutputFormat});
			this->tsTxtOutputFormat->Name = L"tsTxtOutputFormat";
			// 
			// tsSaveOutputFormat
			// 
			this->tsSaveOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsSaveOutputFormat, L"tsSaveOutputFormat");
			this->tsSaveOutputFormat->Name = L"tsSaveOutputFormat";
			this->tsSaveOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsSaveOutputFormat_Click);
			// 
			// panelLstOutputFormats
			// 
			resources->ApplyResources(this->panelLstOutputFormats, L"panelLstOutputFormats");
			this->panelLstOutputFormats->Controls->Add(this->tsOutputFormat);
			this->panelLstOutputFormats->Controls->Add(this->lstOutputFormat);
			this->panelLstOutputFormats->Name = L"panelLstOutputFormats";
			// 
			// tsOutputFormat
			// 
			resources->ApplyResources(this->tsOutputFormat, L"tsOutputFormat");
			this->tsOutputFormat->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsOutputFormat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->tsAddOutputFormat, 
				this->tsDeleteOutputFormat, this->tsDuplicateOutputFormat});
			this->tsOutputFormat->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->tsOutputFormat->Name = L"tsOutputFormat";
			// 
			// tsAddOutputFormat
			// 
			this->tsAddOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsAddOutputFormat, L"tsAddOutputFormat");
			this->tsAddOutputFormat->Name = L"tsAddOutputFormat";
			this->tsAddOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsAddOutputFormat_Click);
			// 
			// tsDeleteOutputFormat
			// 
			this->tsDeleteOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsDeleteOutputFormat, L"tsDeleteOutputFormat");
			this->tsDeleteOutputFormat->Name = L"tsDeleteOutputFormat";
			this->tsDeleteOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDeleteOutputFormat_Click);
			// 
			// tsDuplicateOutputFormat
			// 
			this->tsDuplicateOutputFormat->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsDuplicateOutputFormat, L"tsDuplicateOutputFormat");
			this->tsDuplicateOutputFormat->Name = L"tsDuplicateOutputFormat";
			this->tsDuplicateOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsDuplicateOutputFormat_Click);
			// 
			// lstOutputFormat
			// 
			resources->ApplyResources(this->lstOutputFormat, L"lstOutputFormat");
			this->lstOutputFormat->Name = L"lstOutputFormat";
			this->lstOutputFormat->SelectedIndexChanged += gcnew System::EventHandler(this, &WizardForm::lstOutputFormat_SelectedIndexChanged);
			// 
			// panelStepRename
			// 
			this->panelStepRename->Controls->Add(label10);
			this->panelStepRename->Controls->Add(this->buttonRenameFiles);
			this->panelStepRename->Controls->Add(label7);
			resources->ApplyResources(this->panelStepRename, L"panelStepRename");
			this->panelStepRename->Name = L"panelStepRename";
			// 
			// buttonRenameFiles
			// 
			resources->ApplyResources(this->buttonRenameFiles, L"buttonRenameFiles");
			this->buttonRenameFiles->Name = L"buttonRenameFiles";
			this->buttonRenameFiles->UseVisualStyleBackColor = true;
			this->buttonRenameFiles->Click += gcnew System::EventHandler(this, &WizardForm::buttonRenameFiles_Click);
			// 
			// panelNavigation
			// 
			this->panelNavigation->Controls->Add(this->messageLabel);
			this->panelNavigation->Controls->Add(this->buttonPreviousStep);
			this->panelNavigation->Controls->Add(this->buttonNextStep);
			resources->ApplyResources(this->panelNavigation, L"panelNavigation");
			this->panelNavigation->Name = L"panelNavigation";
			// 
			// messageLabel
			// 
			resources->ApplyResources(this->messageLabel, L"messageLabel");
			this->messageLabel->Name = L"messageLabel";
			// 
			// buttonPreviousStep
			// 
			resources->ApplyResources(this->buttonPreviousStep, L"buttonPreviousStep");
			this->buttonPreviousStep->Name = L"buttonPreviousStep";
			this->buttonPreviousStep->UseVisualStyleBackColor = true;
			this->buttonPreviousStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonPreviousStep_Click);
			// 
			// buttonNextStep
			// 
			resources->ApplyResources(this->buttonNextStep, L"buttonNextStep");
			this->buttonNextStep->Name = L"buttonNextStep";
			this->buttonNextStep->UseVisualStyleBackColor = true;
			this->buttonNextStep->Click += gcnew System::EventHandler(this, &WizardForm::buttonNextStep_Click);
			// 
			// panelFilelist
			// 
			this->panelFilelist->Controls->Add(panelFileListInner);
			resources->ApplyResources(this->panelFilelist, L"panelFilelist");
			this->panelFilelist->Name = L"panelFilelist";
			// 
			// tsStepButtons
			// 
			resources->ApplyResources(this->tsStepButtons, L"tsStepButtons");
			this->tsStepButtons->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->tsStepButtons->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->tsStepRuleset, 
				this->tsStepBeforeReplacements, this->tsStepOutputFormat, this->tsStepInputRule, this->tsStepGems, this->tsStepAfterReplacements, 
				this->tsStepRename});
			this->tsStepButtons->Name = L"tsStepButtons";
			// 
			// tsStepRuleset
			// 
			this->tsStepRuleset->Checked = true;
			this->tsStepRuleset->CheckState = System::Windows::Forms::CheckState::Checked;
			resources->ApplyResources(this->tsStepRuleset, L"tsStepRuleset");
			this->tsStepRuleset->Name = L"tsStepRuleset";
			this->tsStepRuleset->Click += gcnew System::EventHandler(this, &WizardForm::tsStepRuleset_Click);
			// 
			// tsStepBeforeReplacements
			// 
			resources->ApplyResources(this->tsStepBeforeReplacements, L"tsStepBeforeReplacements");
			this->tsStepBeforeReplacements->Name = L"tsStepBeforeReplacements";
			this->tsStepBeforeReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepBeforeReplacements_Click);
			// 
			// tsStepOutputFormat
			// 
			resources->ApplyResources(this->tsStepOutputFormat, L"tsStepOutputFormat");
			this->tsStepOutputFormat->Name = L"tsStepOutputFormat";
			this->tsStepOutputFormat->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
			this->tsStepOutputFormat->Click += gcnew System::EventHandler(this, &WizardForm::tsStepOutputFormat_Click);
			// 
			// tsStepInputRule
			// 
			resources->ApplyResources(this->tsStepInputRule, L"tsStepInputRule");
			this->tsStepInputRule->Name = L"tsStepInputRule";
			this->tsStepInputRule->Click += gcnew System::EventHandler(this, &WizardForm::tsStepInputRule_Click);
			// 
			// tsStepGems
			// 
			resources->ApplyResources(this->tsStepGems, L"tsStepGems");
			this->tsStepGems->Name = L"tsStepGems";
			this->tsStepGems->Click += gcnew System::EventHandler(this, &WizardForm::tsStepGems_Click);
			// 
			// tsStepAfterReplacements
			// 
			resources->ApplyResources(this->tsStepAfterReplacements, L"tsStepAfterReplacements");
			this->tsStepAfterReplacements->Name = L"tsStepAfterReplacements";
			this->tsStepAfterReplacements->Click += gcnew System::EventHandler(this, &WizardForm::tsStepAfterReplacements_Click);
			// 
			// tsStepRename
			// 
			resources->ApplyResources(this->tsStepRename, L"tsStepRename");
			this->tsStepRename->Name = L"tsStepRename";
			// 
			// openRulesetFileDialog
			// 
			this->openRulesetFileDialog->CheckFileExists = false;
			this->openRulesetFileDialog->DefaultExt = L"ruleset";
			this->openRulesetFileDialog->FileName = L"default.rulset";
			resources->ApplyResources(this->openRulesetFileDialog, L"openRulesetFileDialog");
			this->openRulesetFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::openRulesetFileDialog_FileOk);
			// 
			// saveRulesetFileDialog
			// 
			this->saveRulesetFileDialog->DefaultExt = L"ruleset";
			resources->ApplyResources(this->saveRulesetFileDialog, L"saveRulesetFileDialog");
			this->saveRulesetFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::saveRulesetFileDialog_FileOk);
			// 
			// fileListopenFileDiag
			// 
			this->fileListopenFileDiag->FileName = L"*.*";
			resources->ApplyResources(this->fileListopenFileDiag, L"fileListopenFileDiag");
			this->fileListopenFileDiag->Multiselect = true;
			this->fileListopenFileDiag->RestoreDirectory = true;
			this->fileListopenFileDiag->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WizardForm::fileListopenFileDiag_FileOk);
			// 
			// WizardForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->splitContainer);
			this->Controls->Add(this->tsStepButtons);
			this->Name = L"WizardForm";
			this->Load += gcnew System::EventHandler(this, &WizardForm::WizardForm_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &WizardForm::WizardForm_FormClosed);
			panelFileListInner->ResumeLayout(false);
			panelFileListInner->PerformLayout();
			this->tsFileList->ResumeLayout(false);
			this->tsFileList->PerformLayout();
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			this->splitContainer->ResumeLayout(false);
			this->panelStepContent->ResumeLayout(false);
			this->panelStepInputRule->ResumeLayout(false);
			this->panelStepInputRule->PerformLayout();
			this->innerPanelInputRules->ResumeLayout(false);
			this->panelLstInputRules->ResumeLayout(false);
			this->panelLstInputRules->PerformLayout();
			this->tsInputRuleButtons->ResumeLayout(false);
			this->tsInputRuleButtons->PerformLayout();
			this->panelTxtInputRule->ResumeLayout(false);
			this->panelTxtInputRule->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->EndInit();
			this->panelStepBeforeReplacements->ResumeLayout(false);
			this->panelStepBeforeReplacements->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->EndInit();
			this->panelStepRuleset->ResumeLayout(false);
			this->panelStepRuleset->PerformLayout();
			this->panelCboRulesets->ResumeLayout(false);
			this->panelCboRulesets->PerformLayout();
			this->tsRuleset->ResumeLayout(false);
			this->tsRuleset->PerformLayout();
			this->panelStepGems->ResumeLayout(false);
			this->panelStepGems->PerformLayout();
			this->panelStepAfterReplacements->ResumeLayout(false);
			this->panelStepAfterReplacements->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->EndInit();
			this->panelStepOutputFormat->ResumeLayout(false);
			this->panelStepOutputFormat->PerformLayout();
			this->panelTxtOutputFormat->ResumeLayout(false);
			this->panelTxtOutputFormat->PerformLayout();
			this->tsTxtOutputFormat->ResumeLayout(false);
			this->tsTxtOutputFormat->PerformLayout();
			this->panelLstOutputFormats->ResumeLayout(false);
			this->panelLstOutputFormats->PerformLayout();
			this->tsOutputFormat->ResumeLayout(false);
			this->tsOutputFormat->PerformLayout();
			this->panelStepRename->ResumeLayout(false);
			this->panelStepRename->PerformLayout();
			this->panelNavigation->ResumeLayout(false);
			this->panelNavigation->PerformLayout();
			this->panelFilelist->ResumeLayout(false);
			this->tsStepButtons->ResumeLayout(false);
			this->tsStepButtons->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Business Code
void applyChanges(Step step) {
	if(step == Step::RULESET_SELECT) {
		reloadFileList();
		if(aFileCouldBeRenamed()) {
			addColumnToFileListForResult();
		}
	} else if (step == Step::BEFORE_REPLACEMENTS) {
		reloadFileList();
		applyBeforeReplacements();
	} else if (step == Step::OUTPUTFORMAT_SELECT) {
		reloadFileList();
		applyBeforeReplacements();
	} else if (step == Step::INPUTRULES_SELECT) {
		reloadFileList();
		applyBeforeReplacements();
		applyInputRules();
		applyGems();

		/*			
	} else if (step == Step::GEMS_SELECT) {
	} else if (step == Step::AFTER_REPLACEMENTS) {
		saveAfterReplacements();
		reloadFileList();
		applyBeforeReplacements();
		applyGems();
		applyAfterReplacements();
	} else if (step == Step::RENAME) {
		reloadFileList();
		applyBeforeReplacements();
		applyGems();
		applyAfterReplacements();*/
	}
}
	
void reloadFileList() {
	fileList->BeginUpdate();
	LockWindowUpdate((HWND) (int) fileList->Handle);

	SCROLLINFO scrollInfo;
	memset(&scrollInfo, sizeof(SCROLLINFO), 0);

	scrollInfo.cbSize = sizeof(SCROLLINFO);
	scrollInfo.fMask = SIF_ALL;

	GetScrollInfo((HWND) (int) fileList->Handle, SB_VERT, &scrollInfo);

	// remove all columns but the first
	if(fileList->Columns->Count > 1) {
		for(int i=fileList->Columns->Count - 1; i>=1; i--) {
			fileList->Columns->RemoveAt(i);
		}
	}

	// remove all entries
	fileList->Items->Clear();

	// add all entries
	for(int i=0; i<mFiles.Count; i++) {
		String^ fileName = System::IO::Path::GetFileNameWithoutExtension(mFiles[i]);
		ListViewItem^ item = gcnew ListViewItem(fileName);
		item->Tag = i;
		fileList->Items->Add(item);
	}

	if(fileList->Items->Count > 0)
		fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
	else
		fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::HeaderSize);

	SetScrollInfo((HWND) (int) fileList->Handle, SB_VERT, &scrollInfo, true);

	fileList->EndUpdate();
	LockWindowUpdate((HWND) 0);
}

void disableTxtOutputFormat() {
	txtOutputFormat->Enabled = false;
	txtOutputFormat->Text = mCustomStrings->GetString(L"Strings.NoOutputFormatSelected");
}

void disableTxtInputRule() {
	txtInputRule->Enabled = false;
	txtInputRule->Text = mCustomStrings->GetString(L"Strings.NoInputRuleSelected");
}

// find out if there is any file which could be renamed 
bool aFileCouldBeRenamed() {
	if(mRuleset == NULL)
		return false;

	bool found = false;
	for(int i=0; i<fileList->Items->Count; i++) {
		ListViewItem^ item = fileList->Items[i];
		String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];

		string outputFilename;
		if(mRuleset->applyTo(toStlString(originalFilenameWithPath), outputFilename)) {
			found = true;
		}
	}
	return found;
}

void addColumnToFileListForResult() {
	if(mRuleset == NULL)
		return ;

	fileList->BeginUpdate();
	LockWindowUpdate((HWND) (int) fileList->Handle);

	fileList->Columns->Add(mCustomStrings->GetString(L"Columns.RenamingResult"));

	for(int i=fileList->Items->Count - 1; i>=0; i--) {
		ListViewItem^ item = fileList->Items[i];
		String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];
		String^ fileName = System::IO::Path::GetFileNameWithoutExtension(originalFilenameWithPath);


		string outputFilename;

		if(mRuleset->applyTo(toStlString(originalFilenameWithPath), outputFilename)) {
			ListViewItem::ListViewSubItem^ subitem = gcnew ListViewItem::ListViewSubItem();
			subitem->Text = Path::GetFileNameWithoutExtension(toClrString(outputFilename));
			item->SubItems->Add(subitem);
		} else if(mShowOnlyMatchingFiles) {
			fileList->Items->Remove(item);
		}
	}

	fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
	fileList->Columns[1]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);

	fileList->EndUpdate();
	LockWindowUpdate((HWND) 0);
}

void applyGems() {
	fileList->BeginUpdate();
	LockWindowUpdate((HWND) (int) fileList->Handle);

	fileList->Columns->Add("Result");

	for(int i=0; i<fileList->Items->Count; i++) {
		string resultingFilename;
		if(mRuleset->applyTo(toStlString(fileList->Items[i]->Text), resultingFilename)) {
			fileList->Items[i]->SubItems->Add(toClrString(resultingFilename));
		}
	}

	for(int i=0; i<fileList->Items->Count; i++) {
		for(int k=0; k<lstInputRules->Items->Count; k++) {
			int inputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->Items[k])->Tag)->value;

			InputRule& inputRule = mRuleset->getInputRule(inputRuleID);
			vector<Gem*> gems = inputRule.getGems();
			vector<GemValue> gemValues;

			gemValues.clear();
			if(inputRule.applyTo(toStlString(fileList->Items[i]->Text), gemValues)) {
				if(fileList->Columns->Count == 2) {
					for(unsigned j=0; j<gems.size(); j++)
						fileList->Columns->Add(toClrString(gems[j]->getName()));
				}
				for(unsigned j=0; j<gemValues.size(); j++) {
					fileList->Items[i]->SubItems->Add(toClrString(gemValues[j].value));
				}
			}
		}
	}

	fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
	fileList->Columns[1]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);

	fileList->EndUpdate();
	LockWindowUpdate((HWND) 0);
}

void loadRulesetListFromRegistry() {
	// load list of known rulesets from registry
	String^ lastRulesets = Microsoft::VisualBasic::Interaction::GetSetting("Renamer", "Settings", "KnownRulesets", "--empty--");

	if(lastRulesets != "--empty--" && lastRulesets != "") {
		array<String^>^ rulesetNames = lastRulesets->Split('|');
		for(int i=0; i<rulesetNames->Length; i++) {
			String^ rulesetName = rulesetNames[i];
			if(IO::File::Exists(rulesetName)) {
				mKnownRulesets.Add(rulesetName);
			}
		}
	}
}

void saveRulesetListToRegistry() {
	String^ rulesetStringList = L"";

	for(int i=0; i<mKnownRulesets.Count; i++) {
		rulesetStringList += mKnownRulesets[i];
		// don't add a | on the end of the list, only in between filenames
		if(i < (mKnownRulesets.Count - 1)) 
			rulesetStringList += L"|";
	}

	Microsoft::VisualBasic::Interaction::SaveSetting("Renamer", "Settings", "KnownRulesets", rulesetStringList);
}

//! Creates a new ruleset. If file @ rulesetFilename does exist, it will be deleted
void createRuleset(String^ rulesetFilename) {
	String^ rulesetName = System::IO::Path::GetFileNameWithoutExtension(rulesetFilename);
	exAssert(rulesetName != "");

	if(File::Exists(rulesetFilename)) {
		File::Delete(rulesetFilename);
	}

	try{
		Ruleset* rs = new Ruleset(toStdWString(rulesetFilename));
		setRuleset(rs);
	}

	catch(exception& e) {
		String^ message = L"Exception: ";
		message += toClrString(e.what());
		MessageBox::Show(message, L"Exception!" );
		return;
	}
}

//! Loads an existing ruleset. This function returns false if file does not exist, or could not be loaded, otherwise true
bool loadRuleset(String^ rulesetFilename) 
{
	if(!System::IO::File::Exists(rulesetFilename)) {
		return false;
	}

	exAssert(rulesetFilename != "");
	String^ rulesetName = System::IO::Path::GetFileNameWithoutExtension(rulesetFilename);
	exAssert(rulesetName != "");

	try {
		Ruleset* rs = new Ruleset(toStdWString(rulesetFilename));
		setRuleset(rs);
	}

	catch(exception& e) {
		String^ message = L"Exception: ";
		message += toClrString(e.what());
		MessageBox::Show(message, L"Exception" );
		return false;
	}

	return true;
}

void setRuleset(Ruleset* ruleset) {
	if(mRuleset)
		delete mRuleset;
	mRuleset = ruleset;

	if(mRuleset == NULL)
		return ;

	String^ rulesetFilename = toClrString(ruleset->getFilename());
	if(!mKnownRulesets.Contains(rulesetFilename)) {
		mKnownRulesets.Add(rulesetFilename);
		ListBoxItem^ item = gcnew ListBoxItem();
		item->Text = Path::GetFileNameWithoutExtension(rulesetFilename);
		item->Tag = rulesetFilename;
		cboRulesets->Items->Add(item);

		saveRulesetListToRegistry();
	}

	for(int i=0; i<cboRulesets->Items->Count; i++) {
		ListBoxItem^ item = (ListBoxItem^) cboRulesets->Items[i];
		String^ filenameWithPath = (String^) item->Tag;

		if(rulesetFilename->Equals(filenameWithPath)) {
			cboRulesets->SelectedIndex = i;
			break;
		}
	}

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
		if(mStep == Step::RULESET_SELECT && mFiles.Count == 0) {
			setMaxStep(Step::RULESET_SELECT);
			return ;
		}

		if(mOutputFormatID > 0) {
/*			OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			vector<string> not_used;
			if(!outputFormat.parse(not_used)) {
				setMaxStep(Step::OUTPUTFORMAT_SELECT);
				return ;
			}*/
			setMaxStep(Step::INPUTRULES_SELECT);
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
	if(mFiles.Contains(pathToFile))
		return ;
	mFiles.Add(pathToFile);
}


void setMaxStep(Step newMaxStep) {
	mMaxStep = newMaxStep;
	setStep(mStep);
}

void setStep(Step newStep) {
	tsUseAsNewInputRule->Visible = false;
	tsUseAsNewOutputFormat->Visible = false;


	if(newStep > mMaxStep) {
		if(mStep == Step::RULESET_SELECT && newStep == Step::BEFORE_REPLACEMENTS) {
			if(mRuleset != NULL) {
				mMaxStep = Step::OUTPUTFORMAT_SELECT;
				refreshOutputFormatList();
			}

			else {
				messageLabel->Text = mCustomStrings->GetString(L"Error.NoRulesetSelected");
//						messageLabel->Text = L"No OutputFormat selected";
			}
		}
/*		if(mStep == Step::INPUTRULES_SELECT && newStep == Step::GEMS_SELECT) {
			if(mRuleset && mOutputFormatID > 0) {
				mMaxStep = Step::GEMS_SELECT;
			}

			else {
				messageLabel->Text = mCustomStrings->GetString(L"Error.NoInputRuleSelected");
			}
		}*/
/*		if(mStep == Step::GEMS_SELECT && newStep == Step::AFTER_REPLACEMENTS) {
			// todo: validate gem
			mMaxStep = Step::AFTER_REPLACEMENTS;
		}
		if(mStep == Step::AFTER_REPLACEMENTS && newStep == Step::RENAME) {
			mMaxStep = Step::RENAME;
		}*/
	}

	if(int(newStep) < 0 || int(newStep) >= int(Step::MAX) || newStep > mMaxStep) {
		return ;
	}

	messageLabel->Text = L"";

	if(newStep != mStep) {
		if(mRuleset)
			mRuleset->save();
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
/*	if(newStep == Step::GEMS_SELECT && mStep != Step::GEMS_SELECT) {
		onEnterStepGems();
	}

	// onLeave: Gems
	if(mStep == Step::GEMS_SELECT && newStep != Step::GEMS_SELECT) {
		onLeaveStepGems();
	}*/

/*	// onEnter: afterReplacements
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
	}*/

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

#pragma endregion
#pragma region Form Event Handlers
private: System::Void WizardForm_Load(System::Object^  sender, System::EventArgs^  e) {
	mCustomStrings = gcnew ComponentResourceManager(UserInterfaceCustomStrings::typeid);
	mShowOnlyMatchingFiles = false;

#ifndef _DEBUG
	tsDebugAddFiles->Visible = false;
	tsDebugLoadRuleset->Visible = false;				 	

	cboRulesets->Width += 25;
#endif

	mStepPanelList = gcnew System::Collections::Generic::List<Panel^>();
	mStepPanelList->Add(panelStepRuleset);
	mStepPanelList->Add(panelStepBeforeReplacements);
	mStepPanelList->Add(panelStepOutputFormat);
	mStepPanelList->Add(panelStepInputRule);
	//				 mStepPanelList->Add(panelStepGems);
	//				 mStepPanelList->Add(panelStepAfterReplacements);
	//				 mStepPanelList->Add(panelStepRename);

	mStepButtonList = gcnew System::Collections::Generic::List<ToolStripButton^>();
	mStepButtonList->Add(tsStepRuleset);
	mStepButtonList->Add(tsStepBeforeReplacements);
	mStepButtonList->Add(tsStepOutputFormat);
	mStepButtonList->Add(tsStepInputRule);
	//				 mStepButtonList->Add(tsStepGems);
	//				 mStepButtonList->Add(tsStepAfterReplacements);
	//				 mStepButtonList->Add(tsStepRename);


	loadRulesetListFromRegistry();

	//! select first step
	mStep = Step::RULESET_SELECT;
	setMaxStep(Step::RULESET_SELECT);
	onEnterStepRuleset();

	extern string gInitialRuleset;

	if(gInitialRuleset.size() > 0) {
		loadRuleset(toClrString(gInitialRuleset));
	}
}

private: System::Void WizardForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	saveRulesetListToRegistry();

	if(mRuleset != NULL)
		delete mRuleset;
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
//			 setStep(Step::AFTER_REPLACEMENTS);
}

private: System::Void tsStepGems_Click(System::Object^  sender, System::EventArgs^  e) {
//	setStep(Step::GEMS_SELECT);
}

private: System::Void buttonRulesetOpenDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	openRulesetFileDialog->ShowDialog();
}

private: System::Void buttonRulesetSaveDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	saveRulesetFileDialog->ShowDialog();
}
#pragma endregion
#pragma region fileList
private: System::Void fileList_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" )) {
				 //! files were dropped on this control
				 array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData( "FileNameW" ));
				 for(int i=0; i<files->Length; i++)
					 addFile(files[i]);	
			 }

			 applyChanges(mStep);
		 }
private: System::Void fileList_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			 if ( e->Data->GetDataPresent( "FileNameW" ))
			 {
				 e->Effect = DragDropEffects::Link;
				 return;
			 }
			 e->Effect = DragDropEffects::None;
		 }


private: System::Void tsRenameFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 for(int i=fileList->Items->Count - 1; i>=0; i--) {
				 ListViewItem^ item = fileList->Items[i];
				 String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];
				 string outputFilename;

				 try {
					 if(mRuleset->rename(toStlString(originalFilenameWithPath ))) {
						mFiles.RemoveAt((int) (Int32^)item->Tag);
					 }
				 }	

				 catch( runtime_error& e) {
					 messageLabel->Text = toClrString(e.what());
				 }
			 }

			 applyChanges(mStep);
		 }

private: System::Void fileListopenFileDiag_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 for(int i=0; i<fileListopenFileDiag->FileNames->Length; i++) {
				 addFile(fileListopenFileDiag->FileNames[i]);
			 }

			 applyChanges(mStep);
		 }
private: System::Void tsAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 fileListopenFileDiag->ShowDialog();
		 }
private: System::Void tsRemoveFileFromList_Click(System::Object^  sender, System::EventArgs^  e) {
			 for(int i=fileList->SelectedIndices->Count - 1; i>=0; i--) {
				 int itemIndex = fileList->SelectedIndices[i];
				 int fileIndex = (int) (Int32^) fileList->Items[itemIndex]->Tag;
				 String^ fileName = mFiles[fileIndex];
				 String^ fileName2 = fileList->Items[fileList->SelectedIndices[i]]->Text;
				 mFiles.RemoveAt(fileIndex);
			 }
			 
			 applyChanges(mStep);
		 }
private: System::Void tsApplyChanges_Click(System::Object^  sender, System::EventArgs^  e) {
			applyChanges(mStep);
		 }
#pragma endregion

	#pragma region Step: Ruleset

private: System::Void checkBoxShowOnlyMatchingFiles_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	mShowOnlyMatchingFiles = !mShowOnlyMatchingFiles;
	applyChanges(mStep);
}

void onEnterStepRuleset() {
	cboRulesets->BeginUpdate();
	LockWindowUpdate((HWND) (int) cboRulesets->Handle);

	cboRulesets->Items->Clear();
	for(int i=0; i<mKnownRulesets.Count; i++) {
		ListBoxItem^ item = gcnew ListBoxItem();
		item->Text = Path::GetFileNameWithoutExtension(mKnownRulesets[i]);
		item->Tag = mKnownRulesets[i];
		cboRulesets->Items->Add(item);

		if(mRuleset != NULL && Path::GetFileNameWithoutExtension(toClrString(mRuleset->getFilename())) == item->Text)
			cboRulesets->SelectedIndex = i;
	}
	
	cboRulesets->EndUpdate();
	LockWindowUpdate((HWND) 0);

	applyChanges(Step::RULESET_SELECT);
}

void onLeaveStepRuleset() {

}

private: System::Void cboRulesets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ListBoxItem^ item = (ListBoxItem^) cboRulesets->Items[cboRulesets->SelectedIndex];
	String^ rulesetFilename = (String^) item->Tag;

	if(mRuleset == NULL || rulesetFilename != toClrString(mRuleset->getFilename()))
		loadRuleset(rulesetFilename);
//	cboRulesets->Text = toClrString(mRuleset->getName());

	applyChanges(Step::RULESET_SELECT);
}

private: System::Void openRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	String^ rulesetFilename = openRulesetFileDialog->FileName;
	loadRuleset(rulesetFilename);
}

private: System::Void saveRulesetFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	String^ rulesetFilename = saveRulesetFileDialog->FileName;
	createRuleset(rulesetFilename);
}

private: System::Void tsLoadRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	openRulesetFileDialog->ShowDialog();
}

private: System::Void tsSaveRulesetDialog_Click(System::Object^  sender, System::EventArgs^  e) {
	saveRulesetFileDialog->ShowDialog();
}

	#pragma endregion
	#pragma region Step: BeforeReplacements

void onEnterStepBeforeReplacements() {
	loadBeforeReplacements();	
	applyChanges(Step::BEFORE_REPLACEMENTS);
}

void onLeaveStepBeforeReplacements() {
	saveBeforeReplacements();
}

void applyBeforeReplacements() {
	fileList->BeginUpdate();
	LockWindowUpdate((HWND) (int) fileList->Handle);

	Replacements& replacements = mRuleset->getBeforeReplacements();
	for(int i=0; i<fileList->Items->Count; i++) {
		ListViewItem^ item = fileList->Items[i];
		item->Text = toClrString(replacements.replace(toStlString(item->Text)));
	}

	fileList->EndUpdate();
	LockWindowUpdate((HWND) 0);
}

void saveBeforeReplacements() {
	if(mRuleset == NULL) return ;
	Replacements& replacements = mRuleset->getBeforeReplacements();

	int rowCount = gridBeforeReplacements->Rows->Count;
	vector<sqlite_int64> replacementsWhichWereNotDeleted ;
	for(int i=0; i<gridBeforeReplacements->Rows->Count; i++) {
		//gridBeforeReplacements->Rows[i]->Cells[0]->Style->BackColor = Color::White;

		// if replacement does not exist yet, add one
		if(gridBeforeReplacements->Rows[i]->Cells[0]->Value == nullptr) {
			String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
			String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
			if(search != nullptr) {
				if(replace == nullptr)
					replace = L"";
				try {
					Replacement* replacement = replacements.addReplacement(toStlString(search), toStlString(replace));
					replacementsWhichWereNotDeleted.push_back(replacement->getRowId());
					gridBeforeReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement->getRowId());
					gridBeforeReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement->getGroupId());
				} catch (...) {
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->BackColor = Color::LightCoral;
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->SelectionBackColor = Color::LightCoral;
				}
			}
		}
		
		// if replacement already exists, update it
		else {
			int rowid = (int)((Int32^)gridBeforeReplacements->Rows[i]->Cells[0]->Value);
			String^ search = (String^)gridBeforeReplacements->Rows[i]->Cells[2]->Value;
			String^ replace = (String^)gridBeforeReplacements->Rows[i]->Cells[3]->Value;
			if(search != nullptr) {
				if(replace == nullptr)
					replace = L"";

				replacementsWhichWereNotDeleted.push_back(rowid);
				Replacement& replacement = mRuleset->getReplacement(rowid);
				
				try {
					replacement.setRegex(toStlString(search));
					replacement.setReplacement(toStlString(replace));
				} catch (...) {
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->BackColor = Color::LightCoral;
					gridBeforeReplacements->Rows[i]->Cells[2]->Style->SelectionBackColor = Color::LightCoral;
				}
			}
		}
	}

	vector<Replacement*> replacementVector = replacements.getReplacements();
	for(unsigned int i=0; i<replacementVector.size(); i++) {
		bool found = false;
		for(unsigned int j=0; j<replacementsWhichWereNotDeleted.size(); j++) {
			if(replacementVector[i]->getRowId() == replacementsWhichWereNotDeleted[j]) {
				found = true;
			}
		}

		// replacement was removed, so remove it ...
		if(found == false) {
			Replacement& replacement = mRuleset->getReplacement(replacementVector[i]->getRowId());
			replacement.remove();
		}
	}

	// save the changes from the object modell to the database
	mRuleset->save();
}

void loadBeforeReplacements() {
	LockWindowUpdate((HWND) (int) gridBeforeReplacements->Handle);

	if(mRuleset == NULL) return ;
	gridBeforeReplacements->Rows->Clear();
	Replacements& replacements = mRuleset->getBeforeReplacements();
	vector<Replacement*> replacementVector = replacements.getReplacements();

	for(unsigned int i=0; i<replacementVector.size(); i++) {
		cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
		values[0] = gcnew Int32 ((Int32)replacementVector[i]->getRowId());
		values[1] = gcnew Int32 ((Int32)replacementVector[i]->getGroupId());
		values[2] = toClrString(replacementVector[i]->getRegex().str());
		values[3] = toClrString(replacementVector[i]->getReplacement());

		gridBeforeReplacements->Rows->Add(values);
	}

	LockWindowUpdate((HWND) 0);
}

private: System::Void gridBeforeReplacements_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	 if(mStep == Step::BEFORE_REPLACEMENTS) {
		 saveBeforeReplacements();
		 applyChanges(mStep);
	 }
}

#pragma endregion
	#pragma region Step: OutputFormat
			 void refreshOutputFormatList() {
				 lstOutputFormat->BeginUpdate();
				 LockWindowUpdate((HWND) (int) lstOutputFormat->Handle);

				 if(mRuleset) {
					 vector<OutputFormat*> outputFormatVector = mRuleset->getOutputFormats();

					 lstOutputFormat->Items->Clear();				
					 for(unsigned int i=0; i<outputFormatVector.size(); i++) {
						 ListBoxItem^ lbi = gcnew ListBoxItem();
						 lbi->Text = toClrString(outputFormatVector[i]->getFormat());
						 lbi->Tag = gcnew _PairStringInt(lbi->Text, outputFormatVector[i]->getRowId());
						 lstOutputFormat->Items->Add(lbi);
					 }
				 }

				 lstOutputFormat->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }

			 void onEnterStepOutputFormats() {
				 applyChanges(Step::OUTPUTFORMAT_SELECT);
				 refreshOutputFormatList();			 
				 if(lstOutputFormat->Items->Count > 0)
					 lstOutputFormat->SelectedIndex = 0;
				 else
					 disableTxtOutputFormat();
				 tsSaveOutputFormat->Visible = false;
			 }

			 void onLeaveStepOutputFormats() {

			 }
	private: System::Void tsAddOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {			 
			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(mCustomStrings->GetString(L"Strings.NewOutputFormat")));
			 refreshOutputFormatList();
			 if(lstOutputFormat->Items->Count == 1) {
				 lstOutputFormat->SelectedIndex = 0;
			 }
		 }
	private: System::Void tsDeleteOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 
			 mRuleset->removeOutputFormat(rowid);
			 refreshOutputFormatList();
			 refreshMaxStep();

			 if(lstOutputFormat->Items->Count == 0)
				 disableTxtOutputFormat();
		 }
	private: System::Void tsDuplicateOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstOutputFormat->SelectedIndex == -1)
				 return ;
			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(lstOutputFormat->SelectedItem->ToString()));
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
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(rowid);

			 outputFormat.setFormat(toStlString(txtOutputFormat->Text));

			 int selectedIndex = lstOutputFormat->SelectedIndex;
			 refreshOutputFormatList();
			 lstOutputFormat->SelectedIndex = selectedIndex;
			 tsSaveOutputFormat->Visible = false;

			 mRuleset->save();
		 }
	private: System::Void lstOutputFormat_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstOutputFormat->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;
			 txtOutputFormat->Enabled = true;
			 txtOutputFormat->Text = properties->key;
			 mOutputFormatID = ((_PairStringInt^) ((ListBoxItem^)lstOutputFormat->SelectedItem)->Tag)->value;
			 tsSaveOutputFormat->Visible = false;

			 txtOutputFormat_TextChanged(nullptr, nullptr);
			 refreshMaxStep();
		 }
	#pragma endregion
	#pragma region Step: InputRule
			 void onEnterStepInputRules() {
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 txtGemInputRule->Text = toClrString(inputRule.getRegex());
					 loadGems();
					 gridGems_SelectionChanged(nullptr, nullptr);
				 }

				 refreshInputRuleList();
				 if(lstInputRules->Items->Count > 0)
					 lstInputRules->SelectedIndex = 0;
				 else 
					 disableTxtInputRule();
				 tsSaveInputRule->Visible = false;
				 applyChanges(Step::INPUTRULES_SELECT);
			 }

			 void onLeaveStepInputRules() {
				 saveGems();
			 }

			 void applyInputRules() {
				 fileList->BeginUpdate();
				 LockWindowUpdate((HWND) (int) fileList->Handle);
	
				 // determine which files are matched with this input rule
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 vector<GemValue> not_used;
					 for(int i=0; i<fileList->Items->Count; i++) {
						 ListViewItem^ item = fileList->Items[i];
						 if(inputRule.applyTo(toStlString(item->Text), not_used)) 
							 item->BackColor = Color::LightGreen;
						 else
							 item->BackColor = Color::LightCoral;
					 }
				 }

				 // determine which files are matched with all other input rules
				 for(int j=0; j<lstInputRules->Items->Count; j++) {
					int inputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->Items[j])->Tag)->value;

					if(inputRuleID != mInputRuleID) {
						InputRule& inputRule = mRuleset->getInputRule(inputRuleID);
						vector<GemValue> not_used;
						for(int i=0; i<fileList->Items->Count; i++) {
							ListViewItem^ item = fileList->Items[i];

							if(item->BackColor == Color::LightCoral && inputRule.applyTo(toStlString(item->Text), not_used)) 
								item->BackColor = Color::Yellow;
						}
					}
				 }

				 fileList->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }


	private: System::Void tsAddInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(mCustomStrings->GetString(L"Strings.NewInputRule")));

			 mRuleset->save();

			 refreshInputRuleList();

			 lstInputRules->SelectedIndex = lstInputRules->Items->Count - 1;
			 applyChanges(mStep);

			 txtInputRule->Focus();
	}
	private: System::Void tsRemoveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 outputFormat.removeInputRule(rowid);
			 refreshInputRuleList();
			 refreshMaxStep();

			 //if(lstInputRules->Items->Count == 0) {
				 disableTxtInputRule();
				 mInputRuleID = 0;
			 //}

			 applyChanges(mStep);
		 }
	private: System::Void tsDuplicateInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(lstInputRules->SelectedItem->ToString()));
			 refreshInputRuleList();
		 }
	private: System::Void tsSaveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = mRuleset->getInputRule(rowid);

			 try {
				 inputRule.setRegex(toStlString(txtInputRule->Text));
				 inputRule.updateGems(outputFormat.getFormat());
			 }

			 catch(...) {
				 // the input rule entered appears to be invalid
	
				 txtInputRule->BackColor = Color::LightCoral;
				 return ;
			 }

			 //! \todo: find out what BackColor should be usually ...
			 txtInputRule->BackColor = txtOutputFormat->BackColor;

			 int selectedIndex = lstInputRules->SelectedIndex;
			 refreshInputRuleList();
			 lstInputRules->SelectedIndex = selectedIndex;
			 tsSaveInputRule->Visible = false;

			 mRuleset->save();
			 applyInputRules();
			 applyChanges(mStep);
		 }
	private: System::Void lstInputRules_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 ListBoxItem^ lbi = (ListBoxItem^) lstInputRules->SelectedItem;
			 if(lbi == nullptr)
				 return ;
			 _PairStringInt^ properties = (_PairStringInt^)lbi->Tag;
			 txtInputRule->Enabled = true;
			 txtInputRule->Text = properties->key;
			 mInputRuleID = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 tsSaveInputRule->Visible = false;

			 loadGems();
			 applyInputRules();
			 applyChanges(mStep);
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


			 void refreshInputRuleList() {
				 lstInputRules->BeginUpdate();
				 LockWindowUpdate((HWND) (int) lstInputRules->Handle);

				 if(mRuleset && mOutputFormatID > 0) {
					 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
					 vector<InputRule*> inputRuleVector = outputFormat.getInputRules();

					 lstInputRules->Items->Clear();				
					 for(unsigned int i=0; i<inputRuleVector.size(); i++) {
						 ListBoxItem^ lbi = gcnew ListBoxItem();
						 lbi->Text = toClrString(inputRuleVector[i]->getRegex());
						 lbi->Tag = gcnew _PairStringInt(lbi->Text, inputRuleVector[i]->getRowId());
						 lstInputRules->Items->Add(lbi);
					 }
				 }

				 lstInputRules->EndUpdate();
				 LockWindowUpdate((HWND) 0);
			 }
	#pragma endregion
	#pragma region Step: Gems
			 void loadGems() {
				 if(mOutputFormatID == 0 || mInputRuleID == 0)
					 return ; // can't do anything in this case ...

				 LockWindowUpdate((HWND) (int) gridGems->Handle);

				 gridGems->Rows->Clear();
				 GemColumnGem->Items->Clear();

				 // add empty item to the ComboBox column
				 GemColumnGem->Items->Add("");

				 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 
				 vector<std::string> neededGems = outputFormat.parse(outputFormat.getFormat());
				 vector<Gem*> currentGems = inputRule.getGems();

				 // add entries to the combobox
				 for(unsigned i=0; i<neededGems.size(); i++) {
					 GemColumnGem->Items->Add(toClrString(neededGems[i]));
				 }

				 // add the rows to the grid
				 for(unsigned i=0; i < currentGems.size(); i++) {
					 cli::array<Object^>^ values = gcnew cli::array<Object^>(2);
					 values[0] = gcnew Int32(currentGems[i]->getPosition());
					 values[1] = gcnew String(toClrString(currentGems[i]->getName()));

					 gridGems->Rows->Add(values);
				 }

				 LockWindowUpdate((HWND) 0);
			 }

			 void saveGems() {
				 //! \todo: validate that gems are correctly configured by the user
				 if(mInputRuleID == 0)
					 return ;

				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 vector<Gem*> gems = inputRule.getGems();

				 for(int i=0; i<gridGems->Rows->Count; i++) {
					 DataGridViewRow^ row = gridGems->Rows[i];
					 Int32^ position = (Int32^) row->Cells[0]->Value;
					 string gemName = toStlString((String^) row->Cells[1]->Value);

					 Gem* gem = inputRule.getGemByPosition((int) position);
					 assert(gem != NULL);
					 if(gem) {
						 gem->setName(gemName);
					 }
				 }
			 }

			 void onEnterStepGems() {
/*applyChanges(Step::GEMS_SELECT);
				 loadGems();
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 txtGemInputRule->Text = toClrString(inputRule.getRegex());
				 }

				 gridGems_SelectionChanged(nullptr, nullptr);
				 */
			 }

			 void onLeaveStepGems() {
				 saveGems();
			 }
private: System::Void gridGems_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {
				DataGridViewRow^ row;
				
				if(gridGems->SelectedRows->Count == 1 ) 
					row = gridGems->SelectedRows[0]; // MultiLine = false; so only one Row can be selected
				else if(gridGems->SelectedCells->Count == 1) 
					row = gridGems->Rows[gridGems->SelectedCells[0]->RowIndex];
				else
					return ;

				Int32^ position = (Int32^) row->Cells[0]->Value;

				InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
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
							if( i == 0 || txtGemInputRule->Text[i-1] != L'\\' || 
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
	#pragma region Step: AfterReplacements
		 void onEnterStepAfterReplacements() {
//			 applyChanges(Step::AFTER_REPLACEMENTS);
		 }

		 void onLeaveStepAfterReplacements() {

		 }
		 void applyAfterReplacements() {
			 fileList->BeginUpdate();
			 LockWindowUpdate((HWND) (int) fileList->Handle);

			 Replacements replacements = mRuleset->getAfterReplacements();
			 for(int i=0; i<fileList->Items->Count; i++) {
				 ListViewItem^ item = fileList->Items[i];
				 item->Text = toClrString(replacements.replace(toStlString(item->Text)));
			 }

			 fileList->EndUpdate();
			 LockWindowUpdate((HWND) 0);
		 }

		 void saveAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 Replacements& replacements = mRuleset->getAfterReplacements();

			 int rowCount = gridAfterReplacements->Rows->Count;
			 vector<sqlite_int64> replacementsWhichWereNotDeleted ;
			 for(int i=0; i<gridAfterReplacements->Rows->Count; i++) {
				 if(gridAfterReplacements->Rows[i]->Cells[0]->Value == nullptr) {
					 String^ search = (String^)gridAfterReplacements->Rows[i]->Cells[2]->Value;
					 String^ replace = (String^)gridAfterReplacements->Rows[i]->Cells[3]->Value;
					 if(search != nullptr) {
						 if(replace == nullptr)
							 replace = L"";
						 Replacement* replacement = replacements.addReplacement(toStlString(search), toStlString(replace));
						 replacementsWhichWereNotDeleted.push_back(replacement->getRowId());
						 gridAfterReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement->getRowId());
						 gridAfterReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement->getGroupId());
					 }
				 }

				 else {
					 int rowid = (int)((Int32^)gridAfterReplacements->Rows[i]->Cells[0]->Value);
					 String^ search = (String^)gridAfterReplacements->Rows[i]->Cells[2]->Value;
					 String^ replace = (String^)gridAfterReplacements->Rows[i]->Cells[3]->Value;
					 if(search != nullptr) {
						 if(replace == nullptr)
							 replace = L"";

						 replacementsWhichWereNotDeleted.push_back(rowid);
						 Replacement& replacement = mRuleset->getReplacement(rowid);
						 replacement.setRegex(toStlString(search));
						 replacement.setReplacement(toStlString(replace));
					 }
				 }
			 }

			 vector<Replacement*> replacementVector = replacements.getReplacements();
			 for(unsigned int i=0; i<replacementVector.size(); i++) {
				 bool found = false;
				 for(unsigned int j=0; j<replacementsWhichWereNotDeleted.size(); j++) {
					 if(replacementVector[i]->getRowId() == replacementsWhichWereNotDeleted[j]) {
						 found = true;
					 }
				 }

				 if(found == false) {
					 Replacement& replacement = mRuleset->getReplacement(replacementVector[i]->getRowId());
					 replacement.remove();
				 }
			 }

			 mRuleset->save();
		 }

		 void loadAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 gridAfterReplacements->Rows->Clear();
			 Replacements replacements = mRuleset->getAfterReplacements();
			 vector<Replacement*> replacementVector = replacements.getReplacements();

			 for(unsigned int i=0; i<replacementVector.size(); i++) {
				 cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
				 values[0] = gcnew Int32 ((Int32)replacementVector[i]->getRowId());
				 values[1] = gcnew Int32 ((Int32)replacementVector[i]->getGroupId());
				 values[2] = toClrString(replacementVector[i]->getRegex().str());
				 values[3] = toClrString(replacementVector[i]->getReplacement());

				 gridAfterReplacements->Rows->Add(values);
			 }
		 }
#pragma endregion
	#pragma region Step: Rename
		 void onEnterStepRename() {
//			 applyChanges(Step::RENAME);
		 }

		 void onLeaveStepRename() {

		 }
private: System::Void buttonRenameFiles_Click(System::Object^  sender, System::EventArgs^  e) {
			 for(int i=fileList->Items->Count -1; i>=0 ; i--) {
				 ListViewItem^ item = fileList->Items[i];
				 String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];


				 String^ originalDirectory = IO::Path::GetDirectoryName(originalFilenameWithPath);
				 String^ originalExtension = IO::Path::GetExtension(originalFilenameWithPath);

				 String^ filenameWithBeforeReplacementsAndWithoutDirectoryAndWithoutExtension = item->Text;

				 string resultingFilename;

				 if(mRuleset->applyTo(toStlString(filenameWithBeforeReplacementsAndWithoutDirectoryAndWithoutExtension), resultingFilename)) {
					 String^ finalFilenameWithPath = originalDirectory + L"\\" + toClrString(resultingFilename) + originalExtension;
					 File::Move(originalFilenameWithPath, finalFilenameWithPath);
					 mFiles.RemoveAt((int) (Int32^)item->Tag);
				 }

				 applyChanges(mStep);
			 }
		 }

#pragma endregion

#pragma region DebugButtons
private: System::Void tsDebugAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
		cli::array<String^>^ directories = System::IO::Directory::GetDirectories("Z:\\Serien\\Southpark");
		 for(int j=0; j<directories->Length; j++){
			 cli::array<String^>^ files = System::IO::Directory::GetFiles(directories[j], "*.avi");
			 for(int i=0; i<files->Length; i++){
				 addFile(files[i]);
			 }
		 }

		 applyChanges(mStep);
	 }
private: System::Void tsDebugLoadRuleset_Click(System::Object^  sender, System::EventArgs^  e) {
		 String^ rulesetFilename = L"D:\\home\\windows\\Eigene Dateien\\Serien\\The Simpsons.ruleset";
		 loadRuleset(rulesetFilename);
		 cboRulesets->Text = Path::GetFileNameWithoutExtension(toClrString(mRuleset->getFilename()));
	 }
#pragma endregion
#pragma region Footer
private: System::Void gridGems_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 saveGems();
			 applyChanges(mStep);
		 }
private: System::Void gridBeforeReplacements_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 
		 }
private: System::Void fileList_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 // \!todo start selected file using system -> start (should bring up default media player)
		 }
private: System::Void tsAddFolders_Click(System::Object^  sender, System::EventArgs^  e) {
			 fileListopenFolderDiag->ShowDialog();
			 String^ path = fileListopenFolderDiag->SelectedPath;

			 cli::array<String^>^ directories = System::IO::Directory::GetDirectories(path);
			 for(int j=0; j<directories->Length; j++){
				 cli::array<String^>^ files = System::IO::Directory::GetFiles(directories[j], "*.*");
				 for(int i=0; i<files->Length; i++){
					 addFile(files[i]);
				 }
			 }
			 cli::array<String^>^ files = System::IO::Directory::GetFiles(path, "*.*");
			 for(int i=0; i<files->Length; i++){
				 addFile(files[i]);
			 }
			 applyChanges(mStep);
		 }
private: System::Void fileList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->Control && e->KeyCode == Keys::A)
			 {
				 fileList->SelectedIndices->Clear();
				 for(int i=0; i<fileList->Items->Count; i++)
					fileList->SelectedIndices->Add(i);
			 }

			 else if(e->KeyCode == Keys::Delete) {
				 tsRemoveFileFromList_Click(nullptr, nullptr);
			 }
		 }
private: System::Void fileList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(fileList->SelectedIndices->Count == 1) {
				 if(mStep == Step::INPUTRULES_SELECT) 
					tsUseAsNewInputRule->Visible = true;
				 else if (mStep == Step::OUTPUTFORMAT_SELECT) 
					tsUseAsNewOutputFormat->Visible = true;			 
			 } else {
					tsUseAsNewOutputFormat->Visible = false;			 
					tsUseAsNewInputRule->Visible = false;
			 }
		 }
private: System::Void tsUseAsNewOutputFormat_Click(System::Object^  sender, System::EventArgs^  e) {
			if(fileList->SelectedItems->Count != 1) return ;

			 String^ selectedFilename = fileList->SelectedItems[0]->Text;

			 OutputFormat& outputFormat = mRuleset->addOutputFormat();
			 outputFormat.setFormat(toStlString(selectedFilename));
			 refreshOutputFormatList();

			 lstOutputFormat->SelectedIndex = lstOutputFormat->Items->Count - 1;
			 txtOutputFormat->Focus();
		 }
private: System::Void tsUseAsNewInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			if(fileList->SelectedItems->Count != 1) return ;

			String^ selectedFilename = fileList->SelectedItems[0]->Text;

			 selectedFilename->Replace("[", "\\[");
			 selectedFilename->Replace("]", "\\]");

			 selectedFilename->Replace("{", "\\{");
			 selectedFilename->Replace("}", "\\}");

			 selectedFilename->Replace("(", "\\(");
			 selectedFilename->Replace(")", "\\)");

			 selectedFilename->Replace(".", "\\.");
			 selectedFilename->Replace("$", "\\$");
			 selectedFilename->Replace("^", "\\^");
			 selectedFilename->Replace("|", "\\|");

			 OutputFormat& outputFormat = mRuleset->getOutputFormat(mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(selectedFilename));

			 mRuleset->save();

			 refreshInputRuleList();

			 lstInputRules->SelectedIndex = lstInputRules->Items->Count - 1;
			 applyChanges(mStep);

			 txtInputRule->Focus();

		 }
};
// --- don't delete after this line (and one line before this line) --- //
}
#pragma endregion