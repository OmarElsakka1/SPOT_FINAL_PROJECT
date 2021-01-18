#pragma once
#include <string>
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;	
};
//constants related to objects to be drawn


enum
{
	CRS_WIDTH = 80,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 37,	//Height of course rectangle to be drawn on screen
	//PLAN_YEAR_WIDTH = CRS_WIDTH * 4,	//width of plan year rectangle to be drawn on screen
	//PLAN_YEAR_HEIGHT	//Height of play year rectangle to be drawn on screen
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
	//course_x_y_code GfxInfoxycode;
public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	//void setcoursexycode(course_x_y_code);
	//course_x_y_code getcoursexycode();
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	virtual ~Drawable();
};

