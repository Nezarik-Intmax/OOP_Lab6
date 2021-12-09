#pragma once

#ifndef CCIRCLE_H
#define CCIRCLE_H
using namespace System::Drawing;

class CCircle{
private:
	int x, y, radius;
	bool select;
public:
	CCircle():x(0),y(0),radius(0), select(true){}
	CCircle(int x, int y, int r):x(x),y(y),radius(r), select(true){}
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
	void SetX(int x){ this->x = x;}
	void SetY(int y){ this->y = y;}
	void SetRadius(int r){ this->radius = r;}
	void SetSelect(bool s=true){ this->select = s;}
	int GetX(){ return this->x;}
	int GetY(){ return this->y;}
	int GetRadius(){ return this->radius;}
	bool GetSelect(){ return this->select; }
};

#endif
