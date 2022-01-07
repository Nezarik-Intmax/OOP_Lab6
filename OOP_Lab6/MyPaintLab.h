#pragma once
#include <math.h>
#include "MyContainer.h"
#include "PaintHandler.h"
#include "CCircle.h"
namespace OOPLab6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyPaintLab
	/// </summary>
	public ref class MyPaintLab : public System::Windows::Forms::Form
	{
	public:
		MyPaintLab(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyPaintLab()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Timer^ moveTimer;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->moveTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(12, 67);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(883, 522);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyPaintLab::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyPaintLab::pictureBox1_MouseDown);
			this->pictureBox1->MouseLeave += gcnew System::EventHandler(this, &MyPaintLab::pictureBox1_MouseLeave);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyPaintLab::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyPaintLab::pictureBox1_MouseUp);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 13);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L" руг";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyPaintLab::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(93, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(105, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"ѕр€моугольник";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyPaintLab::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Desktop;
			this->button3->Location = System::Drawing::Point(79, 39);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(20, 20);
			this->button3->TabIndex = 4;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyPaintLab::color_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::HotTrack;
			this->button4->Location = System::Drawing::Point(105, 39);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(20, 20);
			this->button4->TabIndex = 5;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyPaintLab::color_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Yellow;
			this->button5->Location = System::Drawing::Point(131, 39);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(20, 20);
			this->button5->TabIndex = 6;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyPaintLab::color_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Black;
			this->button6->Location = System::Drawing::Point(53, 39);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(20, 20);
			this->button6->TabIndex = 7;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyPaintLab::color_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(204, 13);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(72, 23);
			this->button7->TabIndex = 8;
			this->button7->Text = L"Ёллипс";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyPaintLab::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(282, 13);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(89, 23);
			this->button8->TabIndex = 9;
			this->button8->Text = L"“реугольник";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyPaintLab::button8_Click);
			// 
			// moveTimer
			// 
			this->moveTimer->Tick += gcnew System::EventHandler(this, &MyPaintLab::moveTimer_Tick);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(798, 13);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(97, 23);
			this->button9->TabIndex = 10;
			this->button9->Text = L"Load";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyPaintLab::button9_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(695, 12);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(97, 23);
			this->button10->TabIndex = 11;
			this->button10->Text = L"Save";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyPaintLab::button10_Click);
			// 
			// MyPaintLab
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(907, 601);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->KeyPreview = true;
			this->Name = L"MyPaintLab";
			this->Text = L"MyPaintLab";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyPaintLab::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyPaintLab::MyForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	PaintHandler pHnd;
	Keys inputCom;
	//String inputCom;
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e){
		pHnd.paintAll(e);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
		if(e->KeyValue == 46){
			pHnd.deleteSelected();
			pictureBox1->Invalidate();
		} else if(e->Control){
			pHnd.setMultiSelect(true);
		}
		inputCom = e->KeyCode;
		moveTimer->Enabled = true;
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
		moveTimer->Enabled = false;
		if(e->KeyCode == Keys::G)
			pHnd.group();
		if(e->KeyData == System::Windows::Forms::Keys::ControlKey){
			pHnd.setMultiSelect(false);
		}
		pictureBox1->Invalidate();
	}
	private: System::Void color_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.setColor(((System::Windows::Forms::Button^)sender)->BackColor);
	}
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		pHnd.paintClick(e->X, e->Y);
	}
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		pHnd.proccessDraw(e->X, e->Y);
		pictureBox1->Invalidate();
	}
	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		pHnd.endDraw();
		pictureBox1->Invalidate();
	}
	private: System::Void pictureBox1_MouseLeave(System::Object^ sender, System::EventArgs^ e){
		pHnd.endDraw();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.setType(0);
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.setType(1);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.setType(2);
	}
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.setType(3);
	}
	private: System::Void moveTimer_Tick(System::Object^ sender, System::EventArgs^ e){
		switch(inputCom){
		case Keys::W: pHnd.move(0, -3, pictureBox1->Size.Width, pictureBox1->Size.Height); break;
		case Keys::S: pHnd.move(0, 3, pictureBox1->Size.Width, pictureBox1->Size.Height); break;
		case Keys::D: pHnd.move(3, 0, pictureBox1->Size.Width, pictureBox1->Size.Height); break;
		case Keys::A: pHnd.move(-3, 0, pictureBox1->Size.Width, pictureBox1->Size.Height); break;
		case Keys::I: pHnd.resizeAll(0, -3, !pHnd.getMultiSelect()); break;
		case Keys::K: pHnd.resizeAll(0, 3, !pHnd.getMultiSelect()); break;
		case Keys::L: pHnd.resizeAll(3, 0, !pHnd.getMultiSelect()); break;
		case Keys::J: pHnd.resizeAll(-3, 0, !pHnd.getMultiSelect()); break;
		default:
			break;
		}
		pictureBox1->Invalidate();
	}
	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.save("savefile.txt");
	}
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e){
		pHnd.load("savefile.txt");
		pictureBox1->Invalidate();
	}
};

}
