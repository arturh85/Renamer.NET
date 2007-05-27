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
using namespace System::Collections;
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
				   GEMS_SELECT = 4,
/*				   AFTER_REPLACEMENTS = 5,
				   RENAME = 6,*/
				   MAX = 5
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
private: System::Windows::Forms::DataGridView^  gridGems;
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




private: System::Windows::Forms::Button^  buttonLanguageDE;
private: System::Windows::Forms::Button^  buttonLanguageEN;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsGroupID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsSearch;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnBeforeReplacementsReplace;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GemColumnPosition;
private: System::Windows::Forms::DataGridViewComboBoxColumn^  GemColumnGem;
private: System::Windows::Forms::ToolStripButton^  tsRenameFiles;
private: System::Windows::Forms::CheckBox^  checkBoxShowOnlyMatchingFiles;







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
			System::Windows::Forms::Label^  label6;
			System::Windows::Forms::Label^  label11;
			System::Windows::Forms::Label^  label5;
			System::Windows::Forms::Label^  label9;
			System::Windows::Forms::Label^  label4;
			System::Windows::Forms::Label^  label14;
			System::Windows::Forms::Label^  label3;
			System::Windows::Forms::Label^  label2;
			System::Windows::Forms::Label^  label8;
			System::Windows::Forms::Label^  label10;
			System::Windows::Forms::Label^  label7;
			System::Windows::Forms::Panel^  panelFileListInner;
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->tsFileList = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveFileFromList = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsApplyChanges = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDebugAddFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRenameFiles = (gcnew System::Windows::Forms::ToolStripButton());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->chFile = (gcnew System::Windows::Forms::ColumnHeader());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->panelStepContent = (gcnew System::Windows::Forms::Panel());
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
			this->gridGems = (gcnew System::Windows::Forms::DataGridView());
			this->GemColumnPosition = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GemColumnGem = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->panelStepBeforeReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridBeforeReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnBeforeReplacementsID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsGroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsSearch = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnBeforeReplacementsReplace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelStepAfterReplacements = (gcnew System::Windows::Forms::Panel());
			this->gridAfterReplacements = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnAfterReplacementsID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsGroupID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsSearch = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnAfterReplacementsReplace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panelStepInputRule = (gcnew System::Windows::Forms::Panel());
			this->panelTxtInputRule = (gcnew System::Windows::Forms::Panel());
			this->txtInputRule = (gcnew System::Windows::Forms::RichTextBox());
			this->txtInputRuleBorder = (gcnew System::Windows::Forms::TextBox());
			this->toolStrip3 = (gcnew System::Windows::Forms::ToolStrip());
			this->tsSaveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->panelLstInputRules = (gcnew System::Windows::Forms::Panel());
			this->tsInputRuleButtons = (gcnew System::Windows::Forms::ToolStrip());
			this->tsAddInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsRemoveInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->tsDuplicateInputRule = (gcnew System::Windows::Forms::ToolStripButton());
			this->lstInputRules = (gcnew System::Windows::Forms::ListBox());
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
			this->buttonLanguageDE = (gcnew System::Windows::Forms::Button());
			this->buttonLanguageEN = (gcnew System::Windows::Forms::Button());
			label1 = (gcnew System::Windows::Forms::Label());
			label6 = (gcnew System::Windows::Forms::Label());
			label11 = (gcnew System::Windows::Forms::Label());
			label5 = (gcnew System::Windows::Forms::Label());
			label9 = (gcnew System::Windows::Forms::Label());
			label4 = (gcnew System::Windows::Forms::Label());
			label14 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label8 = (gcnew System::Windows::Forms::Label());
			label10 = (gcnew System::Windows::Forms::Label());
			label7 = (gcnew System::Windows::Forms::Label());
			panelFileListInner = (gcnew System::Windows::Forms::Panel());
			panelFileListInner->SuspendLayout();
			this->tsFileList->SuspendLayout();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->panelStepContent->SuspendLayout();
			this->panelStepRuleset->SuspendLayout();
			this->panelCboRulesets->SuspendLayout();
			this->tsRuleset->SuspendLayout();
			this->panelStepGems->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->BeginInit();
			this->panelStepBeforeReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->BeginInit();
			this->panelStepAfterReplacements->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->BeginInit();
			this->panelStepInputRule->SuspendLayout();
			this->panelTxtInputRule->SuspendLayout();
			this->toolStrip3->SuspendLayout();
			this->panelLstInputRules->SuspendLayout();
			this->tsInputRuleButtons->SuspendLayout();
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
			// label6
			// 
			resources->ApplyResources(label6, L"label6");
			label6->Name = L"label6";
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
			// label8
			// 
			resources->ApplyResources(label8, L"label8");
			label8->Name = L"label8";
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
			this->tsFileList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->tsAddFiles, this->tsRemoveFileFromList, 
				this->tsApplyChanges, this->tsDebugAddFiles, this->tsRenameFiles});
			this->tsFileList->Name = L"tsFileList";
			// 
			// tsAddFiles
			// 
			this->tsAddFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->tsAddFiles, L"tsAddFiles");
			this->tsAddFiles->Name = L"tsAddFiles";
			this->tsAddFiles->Click += gcnew System::EventHandler(this, &WizardForm::tsAddFiles_Click);
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
			this->fileList->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragEnter);
			this->fileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &WizardForm::fileList_DragDrop);
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
			this->panelStepContent->Controls->Add(this->panelStepRuleset);
			this->panelStepContent->Controls->Add(this->panelStepGems);
			this->panelStepContent->Controls->Add(this->panelStepBeforeReplacements);
			this->panelStepContent->Controls->Add(this->panelStepAfterReplacements);
			this->panelStepContent->Controls->Add(this->panelStepInputRule);
			this->panelStepContent->Controls->Add(this->panelStepOutputFormat);
			this->panelStepContent->Controls->Add(this->panelStepRename);
			this->panelStepContent->Controls->Add(this->panelNavigation);
			resources->ApplyResources(this->panelStepContent, L"panelStepContent");
			this->panelStepContent->Name = L"panelStepContent";
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
			this->panelStepGems->Controls->Add(this->gridGems);
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
			// gridGems
			// 
			this->gridGems->AllowUserToAddRows = false;
			this->gridGems->AllowUserToDeleteRows = false;
			this->gridGems->AllowUserToResizeRows = false;
			resources->ApplyResources(this->gridGems, L"gridGems");
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
			this->gridGems->SelectionChanged += gcnew System::EventHandler(this, &WizardForm::gridGems_SelectionChanged);
			// 
			// GemColumnPosition
			// 
			this->GemColumnPosition->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
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
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
			this->gridBeforeReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridBeforeReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ColumnBeforeReplacementsID, 
				this->ColumnBeforeReplacementsGroupID, this->ColumnBeforeReplacementsSearch, this->ColumnBeforeReplacementsReplace});
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridBeforeReplacements->DefaultCellStyle = dataGridViewCellStyle5;
			this->gridBeforeReplacements->Name = L"gridBeforeReplacements";
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridBeforeReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
			this->gridBeforeReplacements->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &WizardForm::gridBeforeReplacements_CellValueChanged);
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
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle7->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle7;
			this->gridAfterReplacements->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridAfterReplacements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->ColumnAfterReplacementsID, 
				this->ColumnAfterReplacementsGroupID, this->ColumnAfterReplacementsSearch, this->ColumnAfterReplacementsReplace});
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle8->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridAfterReplacements->DefaultCellStyle = dataGridViewCellStyle8;
			this->gridAfterReplacements->Name = L"gridAfterReplacements";
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle9->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridAfterReplacements->RowHeadersDefaultCellStyle = dataGridViewCellStyle9;
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
			// panelStepInputRule
			// 
			this->panelStepInputRule->Controls->Add(label14);
			this->panelStepInputRule->Controls->Add(this->panelTxtInputRule);
			this->panelStepInputRule->Controls->Add(this->panelLstInputRules);
			this->panelStepInputRule->Controls->Add(label3);
			resources->ApplyResources(this->panelStepInputRule, L"panelStepInputRule");
			this->panelStepInputRule->Name = L"panelStepInputRule";
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
			// buttonLanguageDE
			// 
			resources->ApplyResources(this->buttonLanguageDE, L"buttonLanguageDE");
			this->buttonLanguageDE->Name = L"buttonLanguageDE";
			this->buttonLanguageDE->UseVisualStyleBackColor = true;
			// 
			// buttonLanguageEN
			// 
			resources->ApplyResources(this->buttonLanguageEN, L"buttonLanguageEN");
			this->buttonLanguageEN->Name = L"buttonLanguageEN";
			this->buttonLanguageEN->UseVisualStyleBackColor = true;
			// 
			// WizardForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->buttonLanguageEN);
			this->Controls->Add(this->buttonLanguageDE);
			this->Controls->Add(this->splitContainer);
			this->Controls->Add(this->tsStepButtons);
			this->Name = L"WizardForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &WizardForm::WizardForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &WizardForm::WizardForm_Load);
			panelFileListInner->ResumeLayout(false);
			panelFileListInner->PerformLayout();
			this->tsFileList->ResumeLayout(false);
			this->tsFileList->PerformLayout();
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			this->splitContainer->ResumeLayout(false);
			this->panelStepContent->ResumeLayout(false);
			this->panelStepRuleset->ResumeLayout(false);
			this->panelStepRuleset->PerformLayout();
			this->panelCboRulesets->ResumeLayout(false);
			this->panelCboRulesets->PerformLayout();
			this->tsRuleset->ResumeLayout(false);
			this->tsRuleset->PerformLayout();
			this->panelStepGems->ResumeLayout(false);
			this->panelStepGems->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridGems))->EndInit();
			this->panelStepBeforeReplacements->ResumeLayout(false);
			this->panelStepBeforeReplacements->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridBeforeReplacements))->EndInit();
			this->panelStepAfterReplacements->ResumeLayout(false);
			this->panelStepAfterReplacements->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridAfterReplacements))->EndInit();
			this->panelStepInputRule->ResumeLayout(false);
			this->panelStepInputRule->PerformLayout();
			this->panelTxtInputRule->ResumeLayout(false);
			this->panelTxtInputRule->PerformLayout();
			this->toolStrip3->ResumeLayout(false);
			this->toolStrip3->PerformLayout();
			this->panelLstInputRules->ResumeLayout(false);
			this->panelLstInputRules->PerformLayout();
			this->tsInputRuleButtons->ResumeLayout(false);
			this->tsInputRuleButtons->PerformLayout();
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


		bool aFileCouldBeRenamed() {
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
		}

		void applyChanges(Step step) {
			fileList->BeginUpdate();
			LockWindowUpdate((HWND) (int) fileList->Handle);
			if(step == Step::RULESET_SELECT) {
				reloadFileList();
				if(aFileCouldBeRenamed()) {
					addColumnToFileListForResult();
				}
			} else if (step == Step::BEFORE_REPLACEMENTS) {
				saveBeforeReplacements();
				reloadFileList();
				applyBeforeReplacements();
			} else if (step == Step::OUTPUTFORMAT_SELECT) {
				reloadFileList();
				applyBeforeReplacements();
			} else if (step == Step::INPUTRULES_SELECT) {
				reloadFileList();
				applyBeforeReplacements();
				applyInputRules();
			} else if (step == Step::GEMS_SELECT) {
				saveGems();
				reloadFileList();
				applyBeforeReplacements();
				applyGems();
/*			} else if (step == Step::AFTER_REPLACEMENTS) {
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
			LockWindowUpdate((HWND) 0);
			fileList->EndUpdate();
		}
	
		void reloadFileList() {
			if(fileList->Columns->Count > 1) {
				for(int i=fileList->Columns->Count - 1; i>=1; i--) {
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

			if(fileList->Items->Count > 0)
				fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
			else
				fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::HeaderSize);
		}

		void disableTxtOutputFormat() {
			txtOutputFormat->Enabled = false;
			txtOutputFormat->Text = mCustomStrings->GetString(L"Strings.NoOutputFormatSelected");
		}

		void disableTxtInputRule() {
			txtInputRule->Enabled = false;
			txtInputRule->Text = mCustomStrings->GetString(L"Strings.NoInputRuleSelected");
		}

		void applyGems() {
			fileList->Columns->Add("Result");

			for(int i=0; i<fileList->Items->Count; i++) {
				string resultingFilename;
				if(mRuleset->applyTo(toStlString(fileList->Items[i]->Text), resultingFilename)) {
					fileList->Items[i]->SubItems->Add(toClrString(resultingFilename));
				}
			}

			InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
			vector<Gem*> gems = inputRule.getGems();
			vector<GemValue> gemValues;

			for(int i=0; i<fileList->Items->Count; i++) {
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

			fileList->Columns[0]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
			fileList->Columns[1]->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
		}

		void updateInputRuleGems(sqlite_int64 inputRuleRowId) {
			InputRule& inputRule = mRuleset->getInputRule(inputRuleRowId);
			OutputFormat& outputFormat = mRuleset->getOutputFormat(inputRule.getOutputFormatId());

			vector<string> gemNames;
			
			if(outputFormat.parse(gemNames)) {
				vector<Gem*> gems = inputRule.getGems();
				
				// array of elements parsed out of OutputFormat
				for(unsigned i = 0; i<gemNames.size(); i++) {
					bool found = false;
	
					// array of already existing Gems and their Names
					unsigned j;
					for(j = 0; j<gems.size(); j++) {
						// found is true if the GemName is already in use
						if(gems[j]->getName() == gemNames[i])  {
							found = true;
							// case: UPDATE
							gems[j]->setName(gemNames[i]);
							break;
						}						
					}

					// case: INSERT
					if(found == false) {
						inputRule.addGem(gemNames[i]);
					}
				}

				for(unsigned i=0; i<gems.size(); i++) {
					bool found = false;

					for(unsigned j=0; j<gemNames.size(); j++) {
						if(gems[i]->getName() == gemNames[j])  { 
							found = true;
						}
					}

					// case: DELETE
					if(found == false) {
						gems[i]->remove();
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
			if(mFiles.Contains(pathToFile))
				return ;
			mFiles.Add(pathToFile);
		}


		void setMaxStep(Step newMaxStep) {
			mMaxStep = newMaxStep;
			setStep(mStep);
		}

		void setStep(Step newStep) {
			if(newStep > mMaxStep) {
				if(mStep == Step::RULESET_SELECT && newStep == Step::BEFORE_REPLACEMENTS) {
					if(mRuleset != NULL) {
						if(fileList->Items->Count > 0) {
							mMaxStep = Step::OUTPUTFORMAT_SELECT;
							refreshOutputFormatList();
						}

						else {
							messageLabel->Text = mCustomStrings->GetString(L"Error.NoFilesAdded");
						}
					}

					else {
						messageLabel->Text = mCustomStrings->GetString(L"Error.NoRulesetSelected");
//						messageLabel->Text = L"No OutputFormat selected";
					}
				}
				if(mStep == Step::INPUTRULES_SELECT && newStep == Step::GEMS_SELECT) {
					if(mRuleset && mOutputFormatID > 0) {
						mMaxStep = Step::GEMS_SELECT;
					}

					else {
						messageLabel->Text = mCustomStrings->GetString(L"Error.NoInputRuleSelected");
					}
				}
/*				if(mStep == Step::GEMS_SELECT && newStep == Step::AFTER_REPLACEMENTS) {
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

/*			// onEnter: afterReplacements
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
		String^ rulesetFilenameToName(String^ filename) {
			return Path::GetFileNameWithoutExtension(filename);
		}
#pragma endregion
#pragma region Form Event Handlers
	private: System::Void WizardForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 mCustomStrings = gcnew ComponentResourceManager(UserInterfaceCustomStrings::typeid);
				 mShowOnlyMatchingFiles = false;
#ifndef _DEBUG
				 tsDebugAddFiles->Visible = false;
				 tsDebugLoadRuleset->Visible = false;				 	

				 cboRulesets->Width += 35;
#endif

				 mStepPanelList = gcnew System::Collections::Generic::List<Panel^>();
				 mStepPanelList->Add(panelStepRuleset);
				 mStepPanelList->Add(panelStepBeforeReplacements);
				 mStepPanelList->Add(panelStepOutputFormat);
				 mStepPanelList->Add(panelStepInputRule);
				 mStepPanelList->Add(panelStepGems);
//				 mStepPanelList->Add(panelStepAfterReplacements);
//				 mStepPanelList->Add(panelStepRename);

				 mStepButtonList = gcnew System::Collections::Generic::List<ToolStripButton^>();
				 mStepButtonList->Add(tsStepRuleset);
				 mStepButtonList->Add(tsStepBeforeReplacements);
				 mStepButtonList->Add(tsStepOutputFormat);
				 mStepButtonList->Add(tsStepInputRule);
				 mStepButtonList->Add(tsStepGems);
//				 mStepButtonList->Add(tsStepAfterReplacements);
//				 mStepButtonList->Add(tsStepRename);


				 loadRulesetListFromRegistry();

				 //! select first step
				 mStep = Step::RULESET_SELECT;
				 setMaxStep(Step::RULESET_SELECT);
				 onEnterStepRuleset();
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
			 setStep(Step::GEMS_SELECT);
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
			 for(int i=0; i<fileList->Items->Count; i++) {
				 ListViewItem^ item = fileList->Items[i];
				 String^ originalFilenameWithPath = mFiles[(int) (Int32^) item->Tag];
				 string outputFilename;

				 try {
					 mRuleset->rename(toStlString(originalFilenameWithPath ));
				 }	

				 catch( runtime_error& e) {
				
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
#pragma region Step Specific Code
	#pragma region Step: Ruleset
private: System::Void checkBoxShowOnlyMatchingFiles_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 mShowOnlyMatchingFiles = !mShowOnlyMatchingFiles;
			 applyChanges(mStep);
		 }
	void onEnterStepRuleset() {
		cboRulesets->Items->Clear();
		for(int i=0; i<mKnownRulesets.Count; i++) {
			ListBoxItem^ item = gcnew ListBoxItem();
			item->Text = rulesetFilenameToName(mKnownRulesets[i]);
			item->Tag = mKnownRulesets[i];
			cboRulesets->Items->Add(item);

			if(mRuleset && mRuleset->getName() == toStlString(item->Text))
				cboRulesets->SelectedIndex = i;
		}
		 
		applyChanges(Step::RULESET_SELECT);
	}

	void onLeaveStepRuleset() {

	}

	private: System::Void cboRulesets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 ListBoxItem^ item = (ListBoxItem^) cboRulesets->Items[cboRulesets->SelectedIndex];
				 String^ rulesetFilename = (String^) item->Tag;
				 loadRuleset(rulesetFilename);
				 cboRulesets->Text = toClrString(mRuleset->getName());

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
				 Replacements replacements = mRuleset->getBeforeReplacements();
				 for(int i=0; i<fileList->Items->Count; i++) {
					 ListViewItem^ item = fileList->Items[i];
					 item->Text = toClrString(replacements.replace(toStlString(item->Text)));
				 }
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
							 Replacement replacement = replacements.addReplacement(toStlString(search), toStlString(replace));
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
							 replacement.setRegex(toStlString(search));
							 replacement.setReplacement(toStlString(replace));
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
private: System::Void gridBeforeReplacements_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(mStep == Step::BEFORE_REPLACEMENTS) 
				 applyChanges(mStep);
		 }

#pragma endregion
	#pragma region Step: OutputFormat
			 void refreshOutputFormatList() {
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
			 OutputFormat outputFormat(mRuleset->getDatabase(), rowid);
			 outputFormat.remove();
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
			 OutputFormat outputFormat(mRuleset->getDatabase(), rowid);

			 outputFormat.setFormat(toStlString(txtOutputFormat->Text));

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
				 if(mInputRuleID)
					 updateInputRuleGems(mInputRuleID);
				 refreshInputRuleList();
				 if(lstInputRules->Items->Count > 0)
					 lstInputRules->SelectedIndex = 0;
				 else 
					 disableTxtInputRule();
				 tsSaveInputRule->Visible = false;
				 applyChanges(Step::INPUTRULES_SELECT);
			 }

			 void onLeaveStepInputRules() {

			 }

			 void applyInputRules() {
				 if(mInputRuleID != 0) {
					 InputRule inputRule(mRuleset->getDatabase(), mInputRuleID);
					 vector<GemValue> not_used;
					 for(int i=0; i<fileList->Items->Count; i++) {
						 ListViewItem^ item = fileList->Items[i];
						 if(inputRule.applyTo(toStlString(item->Text), not_used)) 
							 item->BackColor = Color::LightGreen;
						 else
							 item->BackColor = Color::LightCoral;
						 //					 item->Text = toClrString(replacements.replace(toStlString(item->Text)));
					 }
				 }
			 }


	private: System::Void tsAddInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(mCustomStrings->GetString(L"Strings.NewInputRule")));
			 refreshInputRuleList();

			 if(lstInputRules->Items->Count == 1) {
				 lstInputRules->SelectedIndex = 0;
			 }
		 }
	private: System::Void tsRemoveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 InputRule inputRule(mRuleset->getDatabase(), rowid );
			 inputRule.remove();
			 refreshInputRuleList();
			 refreshMaxStep();

			 if(lstInputRules->Items->Count == 0)
				 disableTxtInputRule();
		 }
	private: System::Void tsDuplicateInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1)
				 return ;
			 OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
			 InputRule& inputRule = outputFormat.addInputRule(toStlString(lstInputRules->SelectedItem->ToString()));
			 refreshInputRuleList();
		 }
	private: System::Void tsSaveInputRule_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(lstInputRules->SelectedIndex == -1) 
				 return ;
			 sqlite_int64 rowid = ((_PairStringInt^) ((ListBoxItem^)lstInputRules->SelectedItem)->Tag)->value;
			 InputRule& inputRule = mRuleset->getInputRule(rowid);

			 inputRule.setRegex(toStlString(txtInputRule->Text));

			 int selectedIndex = lstInputRules->SelectedIndex;
			 refreshInputRuleList();
			 lstInputRules->SelectedIndex = selectedIndex;
			 tsSaveInputRule->Visible = false;

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


			 void refreshInputRuleList() {
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
			 }
	#pragma endregion
	#pragma region Step: Gems
			 void loadGems() {
				 gridGems->Rows->Clear();
				 GemColumnGem->Items->Clear();

				 // add empty item to the ComboBox column
				 GemColumnGem->Items->Add("");

				 OutputFormat outputFormat(mRuleset->getDatabase(), mOutputFormatID);
				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 boost::regex regularExpression(inputRule.getRegex());
				 unsigned int subExpressionCount = regularExpression.mark_count();
				 vector<Gem*> gems = inputRule.getGems();

				 for(unsigned i=0; i<gems.size(); i++) {
					 GemColumnGem->Items->Add(toClrString(gems[i]->getName()));
				 }

				 for(unsigned i=0; i < subExpressionCount; i++) {
					 cli::array<Object^>^ values = gcnew cli::array<Object^>(2);
					 values[0] = gcnew Int32(i+1);
					 for(unsigned j=0; j<gems.size(); j++) {
						 if(gems[j]->getPosition() == i+1) {
							 values[1] = gcnew String(toClrString(gems[j]->getName()));
							 gridGems->Rows->Add(values);
						 }
					 }

				 }
			 }

			 void saveGems() {
				 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
				 vector<Gem*> gems = inputRule.getGems();

				 for(int i=0; i<gridGems->Rows->Count; i++) {
					 DataGridViewRow^ row = gridGems->Rows[i];
					 Int32^ position = (Int32^) row->Cells[0]->Value;
					 String^ gemName = (String^) row->Cells[1]->Value;

					 for(unsigned i=0; i<gems.size(); i++) {
						 if(gems[i]->getName() == toStlString(gemName)) {
							 gems[i]->setPosition((int) position);
						 }
					 }
				 }
			 }
			 void onEnterStepGems() {
				 applyChanges(Step::GEMS_SELECT);
				 loadGems();
				 if(mInputRuleID != 0) {
					 InputRule& inputRule = mRuleset->getInputRule(mInputRuleID);
					 txtGemInputRule->Text = toClrString(inputRule.getRegex());
				 }

				 gridGems_SelectionChanged(nullptr, nullptr);
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
	#pragma region Step: AfterReplacements
		 void onEnterStepAfterReplacements() {
//			 applyChanges(Step::AFTER_REPLACEMENTS);
		 }

		 void onLeaveStepAfterReplacements() {

		 }
		 void applyAfterReplacements() {
			 Replacements replacements = mRuleset->getAfterReplacements();
			 for(int i=0; i<fileList->Items->Count; i++) {
				 ListViewItem^ item = fileList->Items[i];
				 item->Text = toClrString(replacements.replace(toStlString(item->Text)));
			 }
		 }

		 void saveAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 Replacements replacements = mRuleset->getAfterReplacements();

			 int rowCount = gridAfterReplacements->Rows->Count;
			 vector<sqlite_int64> replacementsWhichWereNotDeleted ;
			 for(int i=0; i<gridAfterReplacements->Rows->Count; i++) {
				 if(gridAfterReplacements->Rows[i]->Cells[0]->Value == nullptr) {
					 String^ search = (String^)gridAfterReplacements->Rows[i]->Cells[2]->Value;
					 String^ replace = (String^)gridAfterReplacements->Rows[i]->Cells[3]->Value;
					 if(search != nullptr) {
						 if(replace == nullptr)
							 replace = L"";
						 Replacement replacement = replacements.addReplacement(toStlString(search), toStlString(replace));
						 replacementsWhichWereNotDeleted.push_back(replacement.getRowId());
						 gridAfterReplacements->Rows[i]->Cells[0]->Value = gcnew Int32((Int32)replacement.getRowId());
						 gridAfterReplacements->Rows[i]->Cells[1]->Value = gcnew Int32((Int32)replacement.getGroupId());
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
						 Replacement replacement(mRuleset->getDatabase(), rowid);
						 replacement.setRegex(toStlString(search));
						 replacement.setReplacement(toStlString(replace));
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

		 void loadAfterReplacements() {
			 if(mRuleset == NULL) return ;
			 gridAfterReplacements->Rows->Clear();
			 Replacements replacements = mRuleset->getAfterReplacements();
			 vector<Replacement> replacementVector = replacements.getReplacements();

			 for(unsigned int i=0; i<replacementVector.size(); i++) {
				 cli::array<Object^>^ values = gcnew cli::array<Object^>(4);
				 values[0] = gcnew Int32 ((Int32)replacementVector[i].getRowId());
				 values[1] = gcnew Int32 ((Int32)replacementVector[i].getGroupId());
				 values[2] = toClrString(replacementVector[i].getRegex().str());
				 values[3] = toClrString(replacementVector[i].getReplacement());

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
#pragma endregion
#pragma region DebugButtons
private: System::Void tsDebugAddFiles_Click(System::Object^  sender, System::EventArgs^  e) {
		 cli::array<String^>^ files = System::IO::Directory::GetFiles("D:\\Daten\\Develop\\Renamer\\testFiles", "*.avi");
		 for(int i=0; i<files->Length; i++){
			 addFile(files[i]);
		 }

		 applyChanges(mStep);
	 }
private: System::Void tsDebugLoadRuleset_Click(System::Object^  sender, System::EventArgs^  e) {
		 String^ rulesetFilename = L"D:\\home\\windows\\Eigene Dateien\\The Simpsons.ruleset";
		 loadRuleset(rulesetFilename);
		 cboRulesets->Text = toClrString(mRuleset->getName());
	 }
#pragma endregion
#pragma region Footer
};
// --- don't delete after this line (and one line before this line) --- //
}
#pragma endregion



