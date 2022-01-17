#pragma once
#include "PaintFigureBase.h"

class CBoxFigure: public PaintFigureBase{
protected:
	int xOrigin, yOrigin, x2, y2;
	int width, height;
public:
	CBoxFigure():width(0), height(0){}
	CBoxFigure(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->xOrigin = x;
		this->yOrigin = y;
		this->select = true;
	}
	CBoxFigure(int x, int y, int w, int h, Color color):width(w), height(h){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->xOrigin = x;
		this->yOrigin = y;
		this->select = true;
		this->color = color;
	}
	virtual void setSize(int xC, int yC, int w, int h) override{
		if(xC < xOrigin){
			if(!checkBorderX(xC - x, w)){
				x = xC;
				setWidth(x2 - x);
			}
		}
		else if(!checkBorderX(xC - x2, w)){
			x2 = xC;
			setWidth(x2 - x);
		}
			if(yC < yOrigin){ 
		if(!checkBorderY(yC - y, h)){
				y = yC;
				setHeight(y2 - y);
			}
		}
		else if(!checkBorderY(yC - y2, h)){
			y2 = yC;
			setHeight(y2 - y);
		}
	}
	virtual void resize(int xC, int yC, int w, int h, bool sign) override{
		int s = sign ? 1 : -1;
		if(!checkBorderX(xC*s, w)){
			if(xC < 0) x += xC * s;
			else if(xC > 0) x2 += xC * s;
			setWidth(x2 - x);
		}
		if(!checkBorderY(yC*s, h)){
			if(yC < 0) y += yC * s;
			else if(yC > 0) y2 += yC * s;
			setHeight(y2 - y);
		}
	}
	void setWidth(int r){ this->width = r; }
	void setHeight(int r){ this->height = r; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	virtual bool checkBorderX(int xC, int w) override{
		if((this->x2 + xC <= w) && (this->x + xC >= 0))
			return false;
		return true;
	}
	virtual bool checkBorderY(int yC, int h) override{
		if((this->y2 + yC <= h) && (this->y + yC >= 0))
			return false;
		return true;
	}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w)){
			this->x += xC;
			this->x2 += xC;
			this->xOrigin += xC;
		}
		if(!checkBorderY(yC, h)){
			this->y += yC;
			this->y2 += yC;
			this->yOrigin += yC;
		}
	}
};