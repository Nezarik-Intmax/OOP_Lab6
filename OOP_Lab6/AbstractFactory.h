#pragma once
#include "PaintFigureBase.h"
class AbstractFactory{
public:
	AbstractFactory(){}
	virtual ~AbstractFactory(){}
	virtual PaintFigureBase* createFigure(const char* s) = 0;
	virtual PaintFigureBase* createFigure(System::String^ s, int xC, int yC, Color color) = 0;
};
