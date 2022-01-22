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
		int tmpD = getDiameter();
		setDiameter(d);
		if(!checkBorderX(0, w) && !checkBorderY(0, h)){}
		else setDiameter(tmpD);
	}
	virtual void resize(int xOffset, int yOffset, int w, int h, bool sign) override{
		int s = sign ? 1 : -1;
		int width = abs(xOffset)*s + diameter / 2;
		int height = abs(yOffset)*s + diameter / 2;
		int d = width*s > height*s ? width * 2 : height * 2;
		int tmpD = getDiameter();
		setDiameter(d);
		if(!checkBorderX(0, w) && !checkBorderY(0, h)){}
		else setDiameter(tmpD);
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
	void setDiameter(int r){
		this->diameter = r;
	}
	int getDiameter(){ return this->diameter;}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w))
			this->x += xC;
		if(!checkBorderY(yC, h))
			this->y += yC;
	}
};
#endif
