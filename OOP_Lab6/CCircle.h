#pragma once
#include "PaintFigureBase.h"
#ifndef CCIRCLE_H
#define CCIRCLE_H

class CCircle : public PaintFigureBase{
private:
	int radius;
public:
	CCircle():radius(0){
		this->x=0;
		this->y=0;
		this->select=0;
	}
	CCircle(int x, int y, int r):radius(r){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	void draw(System::Windows::Forms::PaintEventArgs^ e){
		Brush^ brsh = Brushes::Black;
		if(select)
			brsh = Brushes::Red;
		e->Graphics->FillEllipse(brsh, x-(radius/2), y-(radius/2), radius, radius);
	}
	bool checkCollision(int x, int y){
		if((this->x - (radius / 2) <= x)&&(this->x + (radius / 2) >= x))
			if((this->y - (radius / 2) <= y)&&(this->y + (radius / 2) >= y))
				return true;
			else
				return false;
		else
			return false;
	}
	void setRadius(int r){ this->radius = r;}
	int getRadius(){ return this->radius;}
};
#endif
