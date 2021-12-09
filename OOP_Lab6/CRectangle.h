#pragma once
#include "PaintFigureBase.h"

class CRectangle: public PaintFigureBase{
private:
	int width, height;
	bool invW, invH;
public:
	CRectangle():width(0),height(0){}
	CRectangle(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = Brushes::Black;
		if(select)
			brsh = Brushes::Red;
		if(invH && invW)
			e->Graphics->FillRectangle(brsh, x-width, y-height, width, height);
		else if(invH)
			e->Graphics->FillRectangle(brsh, x, y - height, width, height);
		else if(invW)
			e->Graphics->FillRectangle(brsh, x - width, y, width, height);
		else
			e->Graphics->FillRectangle(brsh, x, y, width, height);
	}
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
		invW = (width>0);
		invH = (height>0);
		setWidth(abs(width));
		setHeight(abs(height));
	}
	void setWidth(int r){ this->width = r; }
	void setHeight(int r){ this->height = r; }
	int getWidth(){  return this->width; }
	int getHeight(){ return this->height; }
};