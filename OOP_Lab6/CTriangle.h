#pragma once
#include "PaintFigureBase.h"
class CTriangle: public PaintFigureBase{
private:
	bool a1, a2, a3;
	gcroot<Point> angle1;
	gcroot<Point> angle2;
	gcroot<Point> angle3;
public:
	CTriangle(){}
	CTriangle(int x, int y){
		angle1 = Point(x, y);
		this->x = x;
		this->y = y;
		this->select = true;
		a1 = false;
		a2 = false;
		a3 = false;
		completed = false;
	}
	CTriangle(int x, int y, Color color):angle1(Point(x, y)){
		angle1 = Point(x,y);
		this->select = true;
		this->color = color;
		a1 = false;
		a2 = false;
		a3 = false;
		completed = false;
	}
	CTriangle(int x, int y, int x2, int y2, int x3, int y3, Color color){
		angle1 = Point(x, y);
		angle2 = Point(x2, y2);
		angle3 = Point(x3, y3);
		this->select = true;
		this->color = color;
		a1 = true;
		a2 = true;
		a3 = true;
		completed = true;
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		if(select)
			brsh = Brushes::Red;
		if(a1 && a2 && a3){
			array<Point>^ angles = gcnew array<Point>(3);
			angles[0] = angle1;
			angles[1] = angle2;
			angles[2] = angle3;
			e->Graphics->FillPolygon(brsh, angles);
		}
		else if(a1 && a2)
			e->Graphics->DrawLine(gcnew Pen(brsh), angle1, angle2);
		else if(a1)
			e->Graphics->FillEllipse(brsh, x, y, 3, 3);
	}
	virtual bool checkCollision(int x, int y) override{
		return false;
	}
	virtual void update() override{
		if(!a1){
			a1 = true;
		} else if(!a2){
			a2 = true;
		} else if(!a3){
			a3 = true;
			completed = true;
		}
	}
	virtual void setSize(int xC, int yC) override{
		if(!a1)
			angle1 = Point(xC, yC);
		else if(!a2)
			angle2 = Point(xC, yC);
		else if(!a3)
			angle3 = Point(xC, yC);
	}
};
