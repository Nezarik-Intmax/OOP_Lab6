#pragma once
ref class PaintHandler{
private:
	MyContainer<PaintFigureBase> figures;
	bool multiSelect = false;
	bool collision = false;
public:
	int type;
	int color;
	PaintHandler():type(0),color(0){}
	~PaintHandler(){}
	void setType(int i){ type  = i;}
	void setColor(int i){color = i;}
};