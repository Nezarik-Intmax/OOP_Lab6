#pragma once
#include "PaintFigureBase.h"

class CSection: public PaintFigureBase{
private:
	int x2, y2;
public:
	CSection(){}
	CSection(int x, int y, int w, int h){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->select = true;
	}
	CSection(int x, int y, int w, int h, Color color){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->select = true;
		this->color = color;
	}
	CSection(const CSection* a){
		this->x = a->x;
		this->y = a->y;
		this->x2 = a->x2;
		this->y2 = a->y2;
		this->select = a->select;
		this->color = a->color;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		e->Graphics->DrawLine(gcnew Pen(color, 2), x, y, x2, y2);
		if(select)
			e->Graphics->DrawLine(gcnew Pen(Brushes::Red, 5), x, y, x2, y2);
	}
	virtual bool checkCollision(int xC, int yC) override{
		if((y2!=y)||(x2!=x)){
			int AB = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
			int AP = sqrt((xC - x) * (xC - x) + (yC - y) * (yC - y));
			int PB = sqrt((x2 - xC) * (x2 - xC) + (y2 - yC) * (y2 - yC));
			if(AB == AP + PB)
				return true;
		}
		return false;
	}
	virtual bool checkBorderX(int xC, int w) override{
		if((this->x2 + xC <= w) && (this->x2 + xC >= 0))
			if((this->x + xC <= w) && (this->x + xC >= 0))
				return false;
		return true;
	}
	virtual bool checkBorderY(int yC, int h) override{
		if((this->y2 + yC <= h) && (this->y2 + yC >= 0))
			if((this->y + yC <= h) && (this->y + yC >= 0))
				return false;
		return true;
	}
	virtual void setSize(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC - x2, w))
			x2 = xC;
		if(!checkBorderY(yC - y2, h))
			y2 = yC;
	}
	virtual void resize(int xC, int yC, int w, int h, bool sign) override{
		int s = sign ? 1 : -1;
		if(!checkBorderX(xC * s, w))
			x2 += xC * s;
		if(!checkBorderY(yC * s, h))
			y2 += yC * s;
	}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w)){
			this->x += xC;
			this->x2 += xC;
		}
		if(!checkBorderY(yC, h)){
			this->y += yC;
			this->y2 += yC;
		}
	}
	virtual std::string getType() override{ return "SECTION"; }
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "SECTION %d %d %d %d %s\n", x, y, x2, y2, c.ToString());
	};
	virtual void load(std::FILE* stream) override{
		char col[80];
		fscanf(stream, "%d", &this->x);
		fscanf(stream, "%d", &this->y);
		fscanf(stream, "%d", &this->x2);
		fscanf(stream, "%d", &this->y2);
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