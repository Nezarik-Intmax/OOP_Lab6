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
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		//if(select)
		//	e->Graphics->DrawEllipse(gcnew Pen(Brushes::Red, 10), x - (diameter / 2), y - (diameter / 2), diameter, diameter);
		e->Graphics->FillEllipse(brsh, x - (diameter / 2), y - (diameter / 2), diameter, diameter);
		drawResize(e);
	}
	virtual void drawResize(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(Color::DarkGray);
		e->Graphics->DrawRectangle(gcnew Pen(brsh, 5), x, y, diameter, diameter);
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
	virtual void setSize(int xC, int yC) override{
		int width = getX() - xC;
		int height = getY() - yC;
		int r = sqrt(width * width + height * height);
		setDiameter(r);
	}
	void setDiameter(int r){ this->diameter = r;}
	int getDiameter(){ return this->diameter;}
	virtual void move(int xC, int yC, int w, int h) override{
		if((this->x + xC+(diameter/2) < w) && (this->x + xC - (diameter / 2) > 0))
			this->x += xC;
		if((this->y + yC + (diameter / 2) < h) && (this->y + yC - (diameter / 2) > 0))
			this->y += yC;
	}
};
#endif
