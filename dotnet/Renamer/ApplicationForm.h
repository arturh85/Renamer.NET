#pragma once
#include <vcclr.h>
#include "ruleset.h"
extern Ruleset* rule;

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie auch
	///          die Ressourcendateiname-Eigenschaft für das Tool zur Kompilierung verwalteter Ressourcen ändern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abhängt.
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cboSets;
	private: System::Windows::Forms::Button^  btnNewSet;
	protected: 

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtOutputFormat;

	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cboSets = (gcnew System::Windows::Forms::ComboBox());
			this->btnNewSet = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtOutputFormat = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// cboSets
			// 
			this->cboSets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->cboSets->FormattingEnabled = true;
			this->cboSets->Location = System::Drawing::Point(67, 14);
			this->cboSets->Name = L"cboSets";
			this->cboSets->Size = System::Drawing::Size(318, 21);
			this->cboSets->TabIndex = 0;
			this->cboSets->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cboSets_SelectedIndexChanged);
			// 
			// btnNewSet
			// 
			this->btnNewSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnNewSet->Location = System::Drawing::Point(391, 12);
			this->btnNewSet->Name = L"btnNewSet";
			this->btnNewSet->Size = System::Drawing::Size(47, 23);
			this->btnNewSet->TabIndex = 1;
			this->btnNewSet->Text = L"neu";
			this->btnNewSet->UseVisualStyleBackColor = true;
			this->btnNewSet->Click += gcnew System::EventHandler(this, &Form1::btnNewSet_Click);
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
			this->txtOutputFormat->Location = System::Drawing::Point(67, 41);
			this->txtOutputFormat->Name = L"txtOutputFormat";
			this->txtOutputFormat->Size = System::Drawing::Size(371, 20);
			this->txtOutputFormat->TabIndex = 3;
			this->txtOutputFormat->TextChanged += gcnew System::EventHandler(this, &Form1::txtOutputFormat_TextChanged);
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(450, 455);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtOutputFormat);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnNewSet);
			this->Controls->Add(this->cboSets);
			this->Name = L"Form1";
			this->Text = L"Renamer Pre-Alpha";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void onSetSelection() {
				 if(rule)
					 delete rule;
				 string setName = toStdString(cboSets->Text);
				 boost::filesystem::path dbFile = boost::filesystem::initial_path() / boost::filesystem::path(setName + ".db3");

				 rule = new Ruleset(setName);
				 refreshSetList();

				 txtOutputFormat->Text = toClrString( rule->getOutputFormat());;
			 }

	 private: bool To_string( String^ source, string &target )
	 {
		 pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		 int len = (( source->Length+1) * 2);
		 char *ch = new char[ len ];
		 bool result = wcstombs( ch, wch, len ) != -1;
		 target = ch;
		 delete ch;
		 return result;
	 }

	private: bool To_CharStar( String^ source, char*& target )
	{
		pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		int len = (( source->Length+1) * 2);
		target = new char[ len ];
		return wcstombs( target, wch, len ) != -1;
	}

	private: string toStdString(String^source) {
				string target;
				To_string(source, target);
				return target;
			 }
	 private: String^ toClrString( string source )
	 {
		 String^ target = gcnew String( source.c_str() );
		return target;
	 }

	private: void refreshSetList() {
				 cboSets->Items->Clear();

				 using namespace System::IO;
				 array<String^>^fileNames = Directory::GetFiles( ".\\", "*.db3" );

				 for(int i=0; i<fileNames->Length; i++) {
					 String^ fileName = fileNames[i]->Substring(2);
					 String^ setName = fileName->Substring(0, fileName->Length-4);
					 cboSets->Items->Add(setName);
				 }
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
		 boost::filesystem::path::default_name_check(boost::filesystem::native);

		 rule = NULL;
		 refreshSetList();
	}
	private: System::Void btnNewSet_Click(System::Object^  sender, System::EventArgs^  e) {
		 if(rule) {
			delete rule;
			rule = NULL;
			cboSets->Text = "";
		 }
		 else
		 {
			rule = new Ruleset(toStdString(cboSets->Text));
			refreshSetList();
		 }
	}
private: System::Void cboSets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 onSetSelection();
		 }
private: System::Void txtOutputFormat_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rule) {
				rule->setOutputFormat(toStdString(txtOutputFormat->Text));
			 }
		 }
};
}

