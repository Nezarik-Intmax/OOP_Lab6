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

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyPaintLab::pictureBox1_MouseClick);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyPaintLab::pictureBox1_MouseDown);
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
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(261, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// MyPaintLab
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(907, 601);
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
	MyContainer<PaintFigureBase> circles;
	bool ctrl = false;
	bool collision = false;
	bool paint = false;
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
	}
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e){
		for(circles.first(); !circles.eol(); circles.next())
			circles.getObject().node->draw(e);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
		if(e->KeyValue == 46){
			for(circles.first(); !circles.eol();){
				if(circles.getObject().node->getSelect()){
					circles.popCurrent();
				} else{
					circles.next();
				}
			}
			pictureBox1->Invalidate();
		} else if(e->Control){
			ctrl = true;
			label1->Text = "ctrlDOWN";
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
		if(e->KeyData == System::Windows::Forms::Keys::ControlKey){
			ctrl = false;
			label1->Text = "ctrlUP";
		}
	}
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		collision = false;
		PaintFigureBase* a;
		for(circles.first(); !circles.eol(); circles.next()){
			if(!ctrl)
				circles.getObject().node->setSelect(false);
			if(circles.getObject().node->checkCollision(e->X, e->Y)){
				collision = true;
				a = circles.getObject().node;
				if(ctrl){
					circles.getObject().node->setSelect();
				}
			}
		}
		if(!collision){
			a = new CCircle(e->X, e->Y, 100);
			circles.add(a);
			paint = true;
		} else if(!ctrl){
			a->setSelect();
		}
	}
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		if((!collision)&&(paint)){
			circles.last();
			int x = circles.getObject().node->getX() - e->X;
			int y = circles.getObject().node->getY() - e->Y;
			int r = sqrt(x*x+y*y);
			dynamic_cast<CCircle*>(circles.getObject().node)->setRadius(r);
		}
		pictureBox1->Invalidate();
	}
	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		paint = false;
		pictureBox1->Invalidate();
	}
};

}
