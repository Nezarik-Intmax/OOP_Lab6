#pragma once
#include "PaintFigureBase.h"

class CRectangle: public PaintFigureBase{
private:
	int xOrigin, yOrigin, x2, y2;
	int width, height;
public:
	CRectangle():width(0),height(0){}
	CRectangle(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->xOrigin = x;
		this->yOrigin = y;
		this->select = true;
	}
	CRectangle(int x, int y, int w, int h, Color color):width(w), height(h){
		this->x = x;
		this->y = y;
		this->x2 = x;
		this->y2 = y;
		this->xOrigin = x;
		this->yOrigin = y;
		this->select = true;
		this->color = color;
	}
	CRectangle(const CRectangle *a){
		this->x = a->x;
		this->y = a->y;
		this->x2 = a->x2;
		this->y2 = a->y2;
		this->xOrigin = a->xOrigin;
		this->yOrigin = a->yOrigin;
		this->select = a->select;
		this->color = a->color;
		this->width = a->width;
		this->height = a->height;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		if(select)
			e->Graphics->DrawRectangle(gcnew Pen(Brushes::Red, 10), x, y, width, height);
		e->Graphics->FillRectangle(brsh, x, y, width, height);
	}
	virtual bool checkCollision(int x, int y) override{
		if((this->x <= x) && (this->x2 >= x))
			if((this->y <= y) && (this->y2 >= y))
				return true;
		return false;
	}
	virtual void setSize(int xC, int yC) override{
		if(xC < xOrigin) x = xC;
		else x2 = xC;
		if(yC < yOrigin) y = yC;
		else y2 = yC;
		setWidth(x2 - x);
		setHeight(y2 - y);
	}
	virtual void resize(int xC, int yC, bool sign) override{
		int s = sign ? 1 : -1;
		if(xC < 0) x += xC * s;
		else if (xC > 0) x2 += xC * s;
		if(yC < 0) y += yC * s;
		else if(yC > 0) y2 += yC * s;
		setWidth(x2 - x);
		setHeight(y2 - y);
	}
	void setWidth(int r){ this->width = r; }
	void setHeight(int r){ this->height = r; }
	int getWidth(){  return this->width; }
	int getHeight(){ return this->height; }
	virtual void move(int xC, int yC, int w, int h) override{
		if((this->x2 + xC <= w) && (this->x + xC >= 0)){
			this->x += xC;
			this->x2 += xC;
			this->xOrigin += xC;
		}
		if((this->y2 + yC <= h) && (this->y + yC >= 0)){
			this->y += yC;
			this->y2 += yC;
			this->yOrigin += yC;
		}
	}
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "RECTANGLE: %d, %d, %d, %d, %d, %d, %d, %d, %s\n", x, y, x2, y2, xOrigin, yOrigin, width, height, c.ToString());
	};
};