#pragma once
#include "PaintFigureBase.h"
#ifndef CCIRCLE_H
#define CCIRCLE_H

class CCircle : public PaintFigureBase{
private:
	int radius;
public:
	CCircle():radius(0){}
	CCircle(int x, int y, int r):radius(r){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CCircle(int x, int y, int r, Color color):radius(r){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		if(select)
			brsh = Brushes::Red;
		e->Graphics->FillEllipse(brsh, x - (radius / 2), y - (radius / 2), radius, radius);
	}
	virtual bool checkCollision(int x, int y) override{
		if((this->x - (radius / 2) <= x)&&(this->x + (radius / 2) >= x))
			if((this->y - (radius / 2) <= y)&&(this->y + (radius / 2) >= y))
				return true;
			else
				return false;
		else
			return false;
	}
	virtual void setSize(int xC, int yC) override{
		int width = getX() - xC;
		int height = getY() - yC;
		int r = sqrt(width * width + height * height);
		setRadius(r);
	}
	void setRadius(int r){ this->radius = r;}
	int getRadius(){ return this->radius;}
};
#endif
