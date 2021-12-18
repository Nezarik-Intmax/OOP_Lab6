#pragma once
#include "PaintFigureBase.h"
class CTriangle: public PaintFigureBase{
private:
	int width, height;
	bool invW, invH;
	gcroot<Point> angle1;
	gcroot<Point> angle2;
	gcroot<Point> angle3;
public:
	CTriangle():width(0), height(0){}
	CTriangle(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CTriangle(int x, int y, Color color){
		angle1 = Point(x,y);
		this->select = true;
		this->color = color;
	}
	CTriangle(int x, int y, int x2, int y2, int x3, int y3, Color color){
		angle1 = Point(x, y);
		angle2 = Point(x2, y2);
		angle3 = Point(x3, y3);
		this->select = true;
		this->color = color;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		array<Point>^ angles = gcnew array<Point>(3);
		angles[0] = angle1;
		angles[1] = angle2;
		angles[2] = angle3;

		if(select)
			brsh = Brushes::Red;
		e->Graphics->FillPolygon(brsh, angles);
	}
	virtual bool checkCollision(int x, int y) override{
		return false;
	}
	virtual void setSize(int xC, int yC) override{

	}
};
