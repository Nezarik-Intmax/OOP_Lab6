#pragma once
using namespace System::Drawing;
ref class PaintFigureBase{
protected:
	int x, y;
	Color color;
	Brush brsh;
	bool select;
public:
	PaintFigureBase():x(0), y(0), select(true){
		color = Color::Black;
		//color = Color::Black;
	}
	PaintFigureBase(int x, int y):x(x), y(y), select(true), color(Color::Black){}
	PaintFigureBase(int x, int y, Color color):x(x), y(y), select(true), color(color){}
	virtual ~PaintFigureBase(){}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e){};
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e, Color){};
	virtual bool checkCollision(int x, int y){
		if((x==y)&&(y==y))
			return true;
		else return false;
	};
	virtual void setX(int x){ this->x = x; }
	virtual void setY(int y){ this->y = y; }
	virtual void setSelect(bool s){ this->select = s; }
	virtual int getX(){ return this->x; }
	virtual int getY(){ return this->y; }
	virtual bool getSelect(){ return this->select; }
	virtual void setSize(int xC, int yC){}
	virtual void setColor(Color color){this->color = color;}
};
