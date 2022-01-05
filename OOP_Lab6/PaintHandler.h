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
	void setCollision(bool i){ collision = i; }
	bool checkCollisions(int xC, int yC){
		bool col = false;
		for(figures.first(); !figures.eol(); figures.next()){
			if(figures.getObject()->checkCollision(xC, yC)){
				figures.getObject()->setSelect(!figures.getObject()->getSelect());
				if(!multiSelect && col){
					figures.prev();
					figures.getObject()->setSelect(false);
					figures.next();
				}
				col = true;
			}else{
				if(!multiSelect)
					figures.getObject()->setSelect(false);
			}
		}
		return col;
	}
	void paintAll(System::Windows::Forms::PaintEventArgs^ e){
		for(figures.first(); !figures.eol(); figures.next())
			figures.getObject()->draw(e);
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
	void proccessDraw(int xC, int yC){
		if((!collision) && (paint)){
			figures.last();
			figures.getObject()->setSize(xC, yC);
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