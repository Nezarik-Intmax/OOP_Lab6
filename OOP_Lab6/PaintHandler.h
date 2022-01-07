#pragma once
#include "PaintFigureBase.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CGroup.h"
#include <iostream>
#include <string.h>
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
	void resizeAll(int xC, int yC, bool sign){
		for(figures.first(); !figures.eol(); figures.next())
			if(figures.getObject()->getSelect())
				figures.getObject()->resize(xC, yC, sign);
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
			int count = 1;
			fscanf(stream, "%d\n", &count);
			char s[80];
			PaintFigureBase* tmp;
			for(int i = 0; i < count + 1; i++){
				fscanf(stream, "%s", s);
				if(s == "CIRCLE") tmp = new CCircle();
				else if(s == "ELLIPSE") tmp = new CEllipse();
				else if(s == "RECTANGLE") tmp = new CRectangle();
				else if(s == "TRIANGLE") tmp = new CTriangle();
				else if(s == "GROUP") tmp = new CGroup();
				tmp->load(stream);
				figures.add(tmp);
			}
			/*
			char* b;
			int c;
			char a[80];
				b = strstr(s, ":");
				c = b-s;
				strncpy(a, s, c);
				a[c] = '\0';
			*/
			fclose(stream);
		}
	}
};