#pragma once
#include <msclr/gcroot.h>
#include <iostream>
using namespace System::Drawing;
using namespace msclr;
class PaintFigureBase{
protected:
	int x, y;
	gcroot<Color> color;
	bool select;
public:
	PaintFigureBase():x(0), y(0), select(true){
		color = Color::Black;
	}
	PaintFigureBase(int x, int y):x(x), y(y), select(true), color(Color::Black){}
	PaintFigureBase(int x, int y, Color color):x(x), y(y), select(true), color(color){}
	virtual ~PaintFigureBase(){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e){};
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e, Color){};
	virtual bool checkCollision(int x, int y){
		if((this->x==y)&&(this->y==y))
			return true;
		else return false;
	};
	virtual void setX(int x){ this->x = x; }
	virtual void setY(int y){ this->y = y; }
	virtual void setSelect(bool s = true){ this->select = s; }
	virtual int getX(){ return this->x; }
	virtual int getY(){ return this->y; }
	virtual bool getSelect(){ return this->select; }
	virtual void setSize(int xC, int yC, int w, int h){}
	virtual void resize(int xC, int yC, int w, int h, bool sign){}
	virtual System::String^ getType(){return "BASE";};
	virtual void setColor(Color color){this->color = color;}
	virtual bool checkBorderX(int xC, int w){
		if((xC < w) && (xC > 0))
			return false;
		return true;
	}
	virtual bool checkBorderY(int yC, int h){
		if((yC < h) && (yC > 0))
			return false;
		return true;
	}
	virtual void move(int xC, int yC, int w, int h){
		if(!checkBorderX(xC, w))
			this->x += xC;
		if(!checkBorderY(yC, h))
			this->y += yC;
	}
	virtual void save(std::FILE* stream){};
	virtual void load(std::FILE* stream){};
};
