#pragma once
#include "PaintFigureBase.h"
#ifndef CCIRCLE_H
#define CCIRCLE_H

class CCircle : public PaintFigureBase{
private:
	int diameter;
public:
	CCircle():diameter(0){}
	CCircle(int x, int y, int r):diameter(r){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CCircle(int x, int y, int r, Color color):diameter(r){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}
	CCircle(const CCircle* a){
		this->x = a->x;
		this->y = a->y;
		this->select = a->select;
		this->color = a->color;
		this->diameter = a->diameter;
	}
	virtual System::String^ getType() override{ return "CIRCLE"; }
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		e->Graphics->FillEllipse(brsh, x - (diameter / 2), y - (diameter / 2), diameter, diameter);
		if(select)
			e->Graphics->DrawEllipse(gcnew Pen(Brushes::Red, 4), x - (diameter / 2) + 2, y - (diameter / 2) + 2, diameter-4, diameter-4);
	}
	virtual bool checkCollision(int x, int y) override{
		int w = (this->x - x) * (this->x - x);
		int h = (this->y - y) * (this->y - y);
		bool inCircle = (diameter / 2 * diameter / 2) >= (w + h);
		if(inCircle)
			return true;
		else
			return false;
	}
	virtual void setSize(int xC, int yC, int w, int h) override{
		int width = abs(getX() - xC);
		int height = abs(getY() - yC);
		int d = width > height ? width * 2 : height * 2;
		setDiameter(d, w, h);
	}
	virtual void resize(int xOffset, int yOffset, int w, int h, bool sign) override{
		int s = sign ? 1 : -1;
		int width = abs(xOffset)*s + diameter / 2;
		int height = abs(yOffset)*s + diameter / 2;
		int d = width*s > height*s ? width * 2 : height * 2;
		setDiameter(d, w, h);
	}
	virtual bool checkBorderX(int xC, int w) override{
		if((this->x + xC + (diameter / 2) < w) && (this->x + xC - (diameter / 2) > 0))
			return false;
		return true;
	}
	virtual bool checkBorderY(int yC, int h) override{
		if((this->y + yC + (diameter / 2) < h) && (this->y + yC - (diameter / 2) > 0))
			return false;
		return true;
	}
	void setDiameter(int r){this->diameter = r;}
	void setDiameter(int d, int w, int h){
		int tmpD = getDiameter();
		setDiameter(d);
		if(checkBorderX(0, w) || checkBorderY(0, h)){
			setDiameter(tmpD);
		}
	}
	int getDiameter(){ return this->diameter;}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w))
			this->x += xC;
		if(!checkBorderY(yC, h))
			this->y += yC;
	}
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "CIRCLE %d %d %d %s\n", x, y, diameter, c.ToString());
	};
	virtual void load(std::FILE* stream) override{
		char col[80];
		fscanf(stream, "%d", &this->x);
		fscanf(stream, "%d", &this->y);
		fscanf(stream, "%d", &this->diameter);
		fscanf(stream, "%s", &col);
		fscanf(stream, "%s", &col);
		int len = strlen(col);
		for(int i=0; i < strlen(col)-2; i++)
			col[i] = col[i+1];
		col[len-2] = '\0';
		System::String^ a = gcnew System::String(col);
		this->color = Color::FromName(a);//ColorTranslator::FromHtml(a); 
	};
};
#endif
