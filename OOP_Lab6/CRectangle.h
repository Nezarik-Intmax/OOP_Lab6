#pragma once
#include "BoxFigure.h"

class CRectangle: public CBoxFigure{
public:
	CRectangle(){}
	CRectangle(int x, int y, int w, int h):CBoxFigure(x,y,w,h){}
	CRectangle(int x, int y, int w, int h, Color color):CBoxFigure(x,y,w,h, color){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		e->Graphics->FillRectangle(brsh, x, y, width, height);
		if(select)
			e->Graphics->DrawRectangle(gcnew Pen(Brushes::Red, 6), x+3, y+3, width-6, height-6);
	}
	virtual bool checkCollision(int x, int y) override{
		if((this->x <= x) && (this->x2 >= x))
			if((this->y <= y) && (this->y2 >= y))
				return true;
		return false;
	}
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "RECTANGLE %d %d %d %d %d %d %d %d %s\n", x, y, x2, y2, xOrigin, yOrigin, width, height, c.ToString());
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