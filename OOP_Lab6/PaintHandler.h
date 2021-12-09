#pragma once
#include "PaintFigureBase.h"
#include "CCircle.h"
ref class PaintHandler{
private:
	MyContainer<PaintFigureBase> figures;
	bool multiSelect = false;
	bool collision = false;
	bool paint;
	int type;
	int color;
public:
	PaintHandler():type(0),color(0){}
	~PaintHandler(){}
	void setType(int i){ type  = i;}
	void setColor(int i){color = i;}
	void setMultiSelect(bool i){ multiSelect = i; }
	void setCollision(bool i){ collision = i; }
	bool checkCollisions(int xC, int yC){
		bool col = false;
		for(figures.first(); !figures.eol(); figures.next()){
			if(figures.getObject().node->checkCollision(xC, yC)){
				col = true;
				figures.getObject().node->setSelect();
				if(!multiSelect){
					if(figures.getObject().prev != nullptr)
						figures.getObject().prev->node->setSelect(false);
				}
			}else{
				if(!multiSelect)
					figures.getObject().node->setSelect(false);
			}
		}
		return col;
	}
	void paintAll(System::Windows::Forms::PaintEventArgs^ e){
		for(figures.first(); !figures.eol(); figures.next())
			figures.getObject().node->draw(e);
	}
	void deleteSelected(){
		for(figures.first(); !figures.eol();){
			if(figures.getObject().node->getSelect()){
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
		figures.add(new CCircle(xC, yC, 100));
		paint = true;
	}
	void proccessDraw(int xC, int yC){
		if((!collision) && (paint)){
			figures.last();
			figures.getObject().node->setSize(xC, yC);
		}
	}
	void endDraw(){
		paint = false;
	}
};