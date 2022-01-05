#pragma once
#include "PaintFigureBase.h"
#include <math.h>
class CEllipse: public PaintFigureBase{
private:
	int width, height;
	bool invW, invH;
public:
	CEllipse():width(0), height(0){}
	CEllipse(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CEllipse(int x, int y, int w, int h, Color color):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		int lx = invW ? x - width : x;
		int ly = invH ? y - height : y;
		if(select)
			e->Graphics->DrawEllipse(gcnew Pen(Brushes::Red, 10), x, y, width, height);
		e->Graphics->FillEllipse(brsh, x, y, width, height);
	}
	/*virtual bool checkCollision(int x, int y) override{
		int w = (this->x - x) * (this->x - x);
		int h = (this->y - y) * (this->y - y);
		int l, r, t, b;
		l = !invW ? 1 : -1;
		t = !invH ? 1 : -1;
		bool inCircle = (((x - this->x)^2 / (width/2)^2) + ((y - this->y)^2 / (height/2)^2)) <= 1;
		if(inCircle)
			return true;
		else
			return false;
	}*/
	virtual bool checkCollision(int x, int y) override{
		int l, r, t, b;
		l = !invW ? this->x : this->x - width;
		r = !invW ? this->x + width : this->x;
		t = !invH ? this->y : this->y - height;
		b = !invH ? this->y + height : this->y;
		if((l <= x) && (r >= x))
			if((t <= y) && (b >= y))
				return true;
			else
				return false;
		else
			return false;
	}
	virtual void setSize(int xC, int yC) override{
		int width = getX() - xC;
		int height = getY() - yC;
		invW = (width > 0);
		invH = (height > 0);
		setWidth(abs(width));
		setHeight(abs(height));
	}
	void setWidth(int r){ this->width = r; }
	void setHeight(int r){ this->height = r; }
	virtual void move(int xC, int yC, int w, int h) override{
		if((this->x + xC + width < w) && (this->x + xC - width > 0))
			this->x += xC;
		if((this->y + yC + height < h) && (this->y + yC - height > 0))
			this->y += yC;
	}
};