#pragma once
#include "PaintFigureBase.h"

class CGroup: public PaintFigureBase{
private:
	gcroot<MyContainer<PaintFigureBase>^> groupFigures;
public:
	CGroup(){
		groupFigures = gcnew MyContainer<PaintFigureBase>;
	}
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
	virtual void setColor(Color color) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->setColor(color);
		}
	}
	virtual void setSelect(bool s = true) override{
		this->select = s;
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->setSelect(s);
		}
	}
	virtual void setSize(int xC, int yC, int w, int h) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->setSize(xC, yC, w, h);
		}
	}
	virtual void resize(int xC, int yC, int w, int h, bool sign) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->resize(xC, yC, w, h, sign);
		}
	}
	virtual void move(int xC, int yC, int w, int h) override{
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			groupFigures->getObject()->move(xC, yC, w, h);
		}
	}
	virtual void save(std::FILE* stream) override{
		fprintf(stream, "GROUP %d\n", groupFigures->length());
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next())
			groupFigures->getObject()->save(stream);
	};
	virtual void load(std::FILE* stream) override{
		int count = 0;
		fscanf(stream, "%d\n", &count);
		char s[80];
		PaintFigureBase* tmp;
		for(int i = 0; i < count; i++){
			fscanf(stream, "%s", s);
			if(!strcmp(s, "CIRCLE")) tmp = new CCircle();
			else if(!strcmp(s, "ELLIPSE")) tmp = new CEllipse();
			else if(!strcmp(s, "RECTANGLE")) tmp = new CRectangle();
			else if(!strcmp(s, "TRIANGLE")) tmp = new CTriangle();
			else if(!strcmp(s, "GROUP")) tmp = new CGroup();
			tmp->load(stream);
			groupFigures->add(tmp);
		}
	};
};