#pragma once
#include "BoxFigure.h"
#include <math.h>
class CEllipse: public CBoxFigure{
public:
	CEllipse(){}
	CEllipse(int x, int y, int w, int h):CBoxFigure(x, y, w, h){}
	CEllipse(int x, int y, int w, int h, Color color):CBoxFigure(x, y, w, h, color){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		e->Graphics->FillEllipse(brsh, x, y, width, height);
		if(select)
			e->Graphics->DrawEllipse(gcnew Pen(Brushes::Red, 6), x + 3, y + 3, width - 6, height - 6);
	}
	virtual bool checkCollision(int xC, int yC) override{
		double a = width/2;
		double b = height/2;
		double xCent = (x + (x2 - x)/2);
		double yCent = (y + (y2 - y)/2);
		double xP = xC - xCent;
		double yP = yC - yCent;
		if(a!=0&&b!=0)
			if((((xP*xP)/(a*a)) + ((yP*yP)/(b*b))) <= 1)
				return true;
		return false;
	}

	virtual System::String^ getType() override{ return "TRIANGLE"; };
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "ELLIPSE %d %d %d %d %d %d %d %d %s\n", x, y, x2, y2, xOrigin, yOrigin, width, height, c.ToString());
	};
};