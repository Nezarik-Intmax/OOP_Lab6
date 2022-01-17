#pragma once
#include "BoxFigure.h"

class CRectangle: public CBoxFigure{
public:
	CRectangle(){}
	CRectangle(int x, int y, int w, int h):CBoxFigure(x,y,w,h){}
	CRectangle(int x, int y, int w, int h, Color color):CBoxFigure(x,y,w,h, color){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		if(select)
			e->Graphics->DrawRectangle(gcnew Pen(Brushes::Red, 10), x, y, width, height);
		e->Graphics->FillRectangle(brsh, x, y, width, height);
	}
	virtual bool checkCollision(int x, int y) override{
		if((this->x <= x) && (this->x2 >= x))
			if((this->y <= y) && (this->y2 >= y))
				return true;
		return false;
	}
};