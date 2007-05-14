#pragma once
#include <vcclr.h>

namespace RenamerNET {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class ListBoxItem : public Object {
		public: 
			virtual String^ ToString() override {
				return Text;
			}

		public: 
			String^ Text;
			Object^ Tag;
	};

}