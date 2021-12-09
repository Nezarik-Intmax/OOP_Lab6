#pragma once
using namespace System::Drawing;
class PaintFigureBase{
public:
	int x, y;
	bool select;
	PaintFigureBase():x(0), y(0), select(true){}
	PaintFigureBase(int x, int y):x(x), y(y), select(true){}
	virtual ~PaintFigureBase(){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e){};
	virtual bool checkCollision(int x, int y){
		if((x==y)&&(y==y))
			return true;
		else return false;
	};
	virtual void setX(int x){ this->x = x; }
	virtual void setY(int y){ this->y = y; }
	virtual void setSelect(bool s = true){ this->select = s; }
	virtual int getX(){ return this->x; }
	virtual int getY(){ return this->y; }
	virtual bool getSelect(){ return this->select; }
	virtual void setSize(int xC, int yC){}
};
