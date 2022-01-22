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
  
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "ELLIPSE %d %d %d %d %d %d %d %d %s\n", x, y, x2, y2, xOrigin, yOrigin, width, height, c.ToString());
	};
	virtual void load(std::FILE* stream) override{
		char col[80];
		fscanf(stream, "%d", &this->x);
		fscanf(stream, "%d", &this->y);
		fscanf(stream, "%d", &this->x2);
		fscanf(stream, "%d", &this->y2);
		fscanf(stream, "%d", &this->xOrigin);
		fscanf(stream, "%d", &this->yOrigin);
		fscanf(stream, "%d", &this->width);
		fscanf(stream, "%d", &this->height);
		fscanf(stream, "%s", &col);
		fscanf(stream, "%s", &col);
		int len = strlen(col);
		for(int i = 0; i < strlen(col) - 2; i++)
			col[i] = col[i + 1];
		col[len - 2] = '\0';
		System::String^ a = gcnew System::String(col);
		this->color = Color::FromName(a);//ColorTranslator::FromHtml(a); 
	};
};