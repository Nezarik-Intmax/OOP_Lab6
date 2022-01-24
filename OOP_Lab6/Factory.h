#pragma once
#include "AbstractFactory.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CSection.h"
#include "CGroup.h"
class Factory : public AbstractFactory{
public:
	Factory(){}
	~Factory(){}
	virtual PaintFigureBase* createFigure(const char* s) override{
		if(!strcmp(s, "CIRCLE")) return new CCircle();
		else if(!strcmp(s, "ELLIPSE")) return new CEllipse();
		else if(!strcmp(s, "RECTANGLE")) return new CRectangle();
		else if(!strcmp(s, "TRIANGLE")) return new CTriangle();
		else if(!strcmp(s, "SECTION")) return new CSection();
		else if(!strcmp(s, "GROUP")) return new CGroup();
		else return new PaintFigureBase();
	}
	virtual PaintFigureBase* createFigure(System::String^ s, int xC, int yC, Color color) override{
		if(s == "CIRCLE") return new CCircle(xC, yC, 100, color);
		else if(s == "ELLIPSE") return new CEllipse(xC, yC, 10, 10, color);
		else if(s == "RECTANGLE") return new CRectangle(xC, yC, 10, 10, color);
		else if(s == "TRIANGLE") return new CTriangle(xC, yC, color);
		else if(s == "SECTION") return new CSection(xC, yC, 10, 10, color);
		else if(s == "GROUP") return new CGroup();
		else return new PaintFigureBase(xC, yC, color);
	}
};