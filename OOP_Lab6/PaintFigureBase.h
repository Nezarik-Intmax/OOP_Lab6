#pragma once
#include <msclr/gcroot.h>
using namespace System::Drawing;
using namespace msclr;
class PaintFigureBase{
protected:
	int x, y;
	bool completed = true;
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
	virtual void update(){}
	virtual int getX(){ return this->x; }
	virtual int getY(){ return this->y; }
	virtual bool getCompleted(){ return this->completed; }
	virtual bool getSelect(){ return this->select; }
	virtual void setSize(int xC, int yC){}
	virtual void setColor(Color color){this->color = color;}
};
