#pragma once
#include "PaintFigureBase.h"
#include "AbstractFactory.h"

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
	virtual bool checkBorderX(int xC, int w) override{
		bool a = false;
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			if(groupFigures->getObject()->checkBorderX(xC, w))
				a = true;
		}
		return a;
	}
	virtual bool checkBorderY(int yC, int h) override{
		bool a = false;
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
			if(groupFigures->getObject()->checkBorderY(yC, h))
				a = true;
		}
		return a;
	}
	virtual void setSize(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w) && !checkBorderY(yC, h)){
			for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
				groupFigures->getObject()->setSize(xC, yC, w, h);
			}
		}
	}
	virtual void resize(int xC, int yC, int w, int h, bool sign) override{
		if(!checkBorderX(xC, w) && !checkBorderY(yC, h)){
			for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
				groupFigures->getObject()->resize(xC, yC, w, h, sign);
			}
		}
	}
	virtual void move(int xC, int yC, int w, int h) override{
		if(!checkBorderX(xC, w) && !checkBorderY(yC, h)){
			for(groupFigures->first(); !groupFigures->eol(); groupFigures->next()){
				groupFigures->getObject()->move(xC, yC, w, h);
			}
		}
	}
	virtual std::string getType() override{ return "GROUP"; }
	virtual void save(std::FILE* stream) override{
		fprintf(stream, "GROUP %d\n", groupFigures->length());
		for(groupFigures->first(); !groupFigures->eol(); groupFigures->next())
			groupFigures->getObject()->save(stream);
	};
	virtual void load(std::FILE* stream) override{};
	virtual void loadFigures(std::FILE* stream, AbstractFactory* f){
		int count = 0;
		fscanf(stream, "%d\n", &count);
		char s[80];
		PaintFigureBase* tmp;
		for(int i = 0; i < count; i++){
			fscanf(stream, "%s", s);
			tmp = f->createFigure(s);
			tmp->load(stream);
			groupFigures->add(tmp);
		}
	};
};