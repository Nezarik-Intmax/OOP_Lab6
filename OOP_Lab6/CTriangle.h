#pragma once
#include "PaintFigureBase.h"
class CTriangle: public PaintFigureBase{
private:
	int x1, x2, y1;
public:
	CTriangle(){}
	CTriangle(int x, int y){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CTriangle(int x, int y, Color color){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}
	/*CTriangle(int x, int y, int x2, int y2, int x3, int y3, Color color){
		this->x = x;
		this->y = y;
		this->x1 = x2;
		this->y1 = y2;
		this->x2 = x3;
		this->y2 = y3;
		this->select = true;
		this->color = color;
	}*/
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		array<Point>^ angles = gcnew array<Point>(3);
		angles[0] = Point(x2, y);
		angles[1] = Point(x1, y1);
		angles[2] = Point(x, y1);
		if(select){
			e->Graphics->DrawPolygon(gcnew Pen(Brushes::Red, 5), angles);
		}
		e->Graphics->FillPolygon(brsh, angles);
	}
	virtual bool checkCollision(int x0, int y0) override{
		int a = (x2 - x0) * (y1 - y) - (x1 - x2) * (y - y0);
		int b = 0 - (x - x1) * (y1 - y0);
		int c = (x - x0) * (y - y1) - (x2 - x) * (y1 - y0);
		if ((a >= 0 && b >= 0 && c >= 0) || (a < 0 && b < 0 && c < 0))
			return true;
		return false;
	}
	void setX1(int xC){ this->x1 = xC; }
	void setY1(int yC){ this->y1 = yC; }
	void setX2(int xC){ this->x2 = xC - ((xC - this->x)/2); }
	virtual void setSize(int xC, int yC) override{
		setX1(xC);
		setX2(xC);
		setY1(yC);
	}
	virtual void move(int xC, int yC, int w, int h) override{
		if((y + yC >= 0) && (y1 + yC <= h) && (y1 + yC >= 0) && (y + yC <= h)){
			if((x + xC >= 0) && (x1 + xC <= w) && (x1 + xC >= 0) && (x + xC <= w)){
				setX(x+xC);
				setX1(x1+xC);
				setX2(x1+xC);
				setY1(y1+yC);
				setY(y+yC);
			}
		}
	}
};
