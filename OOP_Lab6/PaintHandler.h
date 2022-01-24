#pragma once
#include "PaintFigureBase.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CSection.h"
#include "CGroup.h"
#include "AbstractFactory.h"
#include "Factory.h"
#include <iostream>
#include <string.h>
ref class PaintHandler{
private:
	MyContainer<PaintFigureBase> figures;
	AbstractFactory* factory;
	bool multiSelect = false;
	bool collision = false;
	bool paint = false;
	System::String^ type;
	System::Drawing::Color color;
public:
	PaintHandler():type(""),color(System::Drawing::Color::Black){
		factory = new Factory();
	}
	~PaintHandler(){
		if(factory != nullptr){
			delete(factory);
			factory = nullptr;
		}
	}
	void setType(System::String^ i){
		type = i;
	}
	void setColor(System::Drawing::Color i){
		color = i;
		for(figures.first(); !figures.eol(); figures.next()){
			if(figures.getObject()->getSelect()){
				figures.getObject()->setColor(i);
			}
		}
	}
	void group(){
		CGroup* g = new CGroup();
		for(figures.first(); !figures.eol();){
			if(figures.getObject()->getSelect()){
				g->addFigure(figures.getObject());
				figures.popCurrent();
			} else{
				figures.next();
			}
		}
		figures.add(g);
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
		figures.add(factory->createFigure(this->type, xC, yC, color));
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
	void save(char* filename){
		std::FILE* stream;
		if((stream = fopen(filename, "w")) != nullptr){
			fprintf(stream, "%d\n", figures.length());
			for(figures.first(); !figures.eol(); figures.next())
				figures.getObject()->save(stream);
			fclose(stream);
		}
	}
	void load(char* filename){
		std::FILE* stream;
		if((stream = fopen(filename, "r")) != nullptr){
			int count = 0;
			fscanf(stream, "%d\n", &count);
			char s[80];
			PaintFigureBase* tmp;
			for(int i = 0; i < count; i++){
				fscanf(stream, "%s", s);
				tmp = factory->createFigure(s);
				if(tmp->getType() == "GROUP")
					dynamic_cast<CGroup*>(tmp)->loadFigures(stream, factory);
				else
					tmp->load(stream);
				figures.add(tmp);
			}
			fclose(stream);
		}
	}
};