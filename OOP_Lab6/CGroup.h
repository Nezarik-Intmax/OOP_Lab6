#pragma once
#include "PaintFigureBase.h"

class CGroup: public PaintFigureBase{
private:
	int count;
	int width, height;
	gcroot<MyContainer<PaintFigureBase>^> groupFigures;
public:
	CGroup():width(0), height(0){
		groupFigures = gcnew MyContainer<PaintFigureBase>;
	}
	/*CGroup(int x, int y, int w, int h):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
	}
	CGroup(int x, int y, int w, int h, Color color):width(w), height(h){
		this->x = x;
		this->y = y;
		this->select = true;
		this->color = color;
	}*/
	void addFigure(PaintFigureBase* fig){
		groupFigures->add(fig);
	}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next())
			groupFigures->getObject()->draw(e);
	}
	virtual bool checkCollision(int xC, int yC) override{
		bool col = false;
		for(groupFigures->last(); !groupFigures->eol(); groupFigures->prev()){
			if(groupFigures->getObject()->checkCollision(xC, yC)){
				col = true;
				break;
			}
		}
		return col;
	}
	virtual void setSelect(bool s = true) override{
		this->select = s;
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->setSelect(s);
		}
	}
	virtual void setSize(int xC, int yC) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->setSize(xC, yC);
		}
	}
	virtual void resize(int xC, int yC, bool sign) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->resize(xC, yC, sign);
		}
	}
	void setWidth(int r){ this->width = r; }
	void setHeight(int r){ this->height = r; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	virtual void move(int xC, int yC, int w, int h) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->move(xC, yC, w, h);
		}
	}
};