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
	virtual void SetX(int x){ this->x = x; }
	virtual void SetY(int y){ this->y = y; }
	virtual void SetSelect(bool s = true){ this->select = s; }
	virtual int GetX(){ return this->x; }
	virtual int GetY(){ return this->y; }
	virtual bool GetSelect(){ return this->select; }
};
