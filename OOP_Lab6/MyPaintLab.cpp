#include "MyPaintLab.h"
#include "MyContainer.h"
#include "CCircle.h"
#include "PaintHandler.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	OOPLab6::MyPaintLab form;
	Application::Run(% form);
}

