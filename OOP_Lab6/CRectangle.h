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
	CRectangle(int x, int y, int w, int h, Color color):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		int lx = invW ? x-width : x;
		int ly = invH ? y-height : y;
		if(select)
			e->Graphics->DrawRectangle(gcnew Pen(Brushes::Red, 10), lx, ly, width, height);
		e->Graphics->FillRectangle(brsh, lx, ly, width, height);
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
	virtual void move(int xC, int yC, int w, int h) override{
		if((this->x + xC + (width / 2) < w) && (this->x + xC - (width / 2) > 0))
			this->x += xC;
		if((this->y + yC + (height / 2) < h) && (this->y + yC - (height / 2) > 0))
			this->y += yC;
	}
};