#pragma once
#include "PaintFigureBase.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
enum figType{CIRCLE, ELLIPSE, RECTANGLE, TRIANGLE};
ref class PaintHandler{
private:
	MyContainer<PaintFigureBase> figures;
	bool multiSelect = false;
	bool collision = false;
	bool paint = false;
	int type;
	System::Drawing::Color color;
public:
	PaintHandler():type(0),color(System::Drawing::Color::Black){}
	~PaintHandler(){}
	void setType(int i){ type  = i;}
	void setColor(System::Drawing::Color i){
		color = i;
		for(figures.first(); !figures.eol(); figures.next()){
			if(figures.getObject()->getSelect()){
				figures.getObject()->setColor(i);
			}
		}
	}
	void setMultiSelect(bool i){ multiSelect = i; }
	bool getMultiSelect(){ return multiSelect; }
	void setCollision(bool i){ collision = i; }
	bool checkCollisions(int xC, int yC){
		bool col = false;
		for(figures.last(); !figures.eol(); figures.prev()){
			if(!col){
				if(figures.getObject()->checkCollision(xC, yC)){
					figures.getObject()->setSelect(!figures.getObject()->getSelect());
					col = true;
				} else if(!multiSelect)
					figures.getObject()->setSelect(false);
			}
			else if(!multiSelect)
				figures.getObject()->setSelect(false);
			else break;
		}
		return col;
	}
	void paintAll(System::Windows::Forms::PaintEventArgs^ e){
		for(figures.first(); !figures.eol(); figures.next())
			figures.getObject()->draw(e);
	}
	void resizeAll(int xC, int yC, int w, int h, bool sign){
		for(figures.first(); !figures.eol(); figures.next())
			if(figures.getObject()->getSelect())
				figures.getObject()->resize(xC, yC, w, h, sign);
	}
	void deleteSelected(){
		for(figures.first(); !figures.eol();){
			if(figures.getObject()->getSelect()){
				figures.popCurrent();
			} else{
				figures.next();
			}
		}
	}
	void paintClick(int xC, int yC){
		collision = this->checkCollisions(xC, yC);
		if(!collision){
			this->startDraw(xC, yC);
		}
	}
	void startDraw(int xC, int yC){
		switch(this->type){
		case CIRCLE:
			figures.add(new CCircle(xC, yC, 100, color));
			break;
		case ELLIPSE:
			figures.add(new CEllipse(xC, yC, 10, 10, color));
			break;
		case RECTANGLE:
			figures.add(new CRectangle(xC, yC, 10, 10, color));
			break;
		case TRIANGLE:
			figures.add(new CTriangle(xC, yC, color));
			break;
		default:
			figures.add(new CCircle(xC, yC, 100, color));
		}
		paint = true;
	}
	void proccessDraw(int xC, int yC, int w, int h){
		if((!collision) && (paint)){
			figures.last();
			figures.getObject()->setSize(xC, yC, w, h);
		}
	}
	void endDraw(){
		paint = false;
	}
	void move(int x, int y, int w, int h){
		for(figures.first(); !figures.eol(); figures.next()){
			if(figures.getObject()->getSelect()){
				figures.getObject()->move(x, y, w, h);
			}
		}
	}
};