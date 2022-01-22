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
		setX1(x);
		setX2(x);
		setY1(y);
		this->select = true;
	}
	CTriangle(int x, int y, Color color){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
		setX1(x);
		setX2(x);
		setY1(y);
	}
	CTriangle(const CTriangle *a){
		this->x = a->x;
		this->y = a->y;
		this->select = a->select;
		this->color = a->color;
	}
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
	virtual void setSize(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC - x1, w)){
			setX1(xC);
			setX2(xC);
		}
		if(!checkBorderY(yC - y1, h)){
			setY1(yC);
		}
	}
	virtual void resize(int xC, int yC, int w, int h, bool sign) override{
		int s = sign ? 1 : -1;
		if(!checkBorderX(xC*s, w)){
			if(xC < 0){
				if(x1 < x)
					x1 += xC * s;
				else
					x += xC * s;
				setX2(x1);
			}
			else if(xC > 0){
				if(x1 > x)
					x1 += xC * s;
				else
					x += xC * s;
				setX2(x1);
			}
		}
		if(!checkBorderY(yC*s, h)){
			if(yC < 0){
				if(y1 < y)
					y1 += yC * s;
				else
					y += yC * s;
			} else if(yC > 0){
				if(y1 > y)
					y1 += yC * s;
				else
					y += yC * s;
			}
		}
	}
	virtual bool checkBorderX(int xC, int w) override{
		if((x + xC >= 0) && (x1 + xC <= w) && (x1 + xC >= 0) && (x + xC <= w))
			return false;
		return true;
	}
	virtual bool checkBorderY(int yC, int h) override{
		if((y + yC >= 0) && (y1 + yC <= h) && (y1 + yC >= 0) && (y + yC <= h))
			return false;
		return true;
	}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w)){
			setX(x+xC);
			setX1(x1+xC);
			setX2(x1+xC);
		}
		if(!checkBorderY(yC, h)){
			setY1(y1+yC);
			setY(y+yC);
		}
	}
	virtual void save(std::FILE* stream) override{
		Color c = this->color;
		fprintf(stream, "TRIANGLE %d %d %d %d %d %s\n", x, y, x1, y1, x2, c.ToString());
	};
	virtual void load(std::FILE* stream) override{
		char col[80];
		fscanf(stream, "%d", &this->x);
		fscanf(stream, "%d", &this->y);
		fscanf(stream, "%d", &this->x1);
		fscanf(stream, "%d", &this->y1);
		fscanf(stream, "%d", &this->x2);
		fscanf(stream, "%s", &col);
		fscanf(stream, "%s", &col);
		int len = strlen(col);
		for(int i = 0; i < strlen(col) - 2; i++)
			col[i] = col[i + 1];
		col[len - 2] = '\0';
		System::String^ a = gcnew System::String(col);
		this->color = Color::FromName(a);
	};
};
