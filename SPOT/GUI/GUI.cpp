#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>

GUI::GUI()
{
	pWind = new window(WindWidth, WindHeight, wx, wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";
	/*
	I DREW THE ICONS IN THE MENU BAR BY
	1- ADDING ITEM IN THE (enum MENU_ITEM) IN GUI.h
	2- ADDING THE PATH OF THE PHOTO HERE
	NOTE 1 : THE PHOTO MUST BE JPG TYPE (WITH PAINTER ALL TYPES CAN BE JPG)
	NOTE 2 : THE FIRST FILE IN THE PATH IS LOCATED IN THE PROJECT FILE "SPOT"
	*/
	MenuItemImages[ITM_DELETE] = "GUI\\Images\\Menu\\Delete.JPG";
	MenuItemImages[ITM_UNDO] = "GUI\\Images\\Menu\\UNDO.JPG";
	MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\REDO.JPG";
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\SAVE.jpg";
	MenuItemImages[ITM_LOAD] = "GUI\\Images\\Menu\\LOAD.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar(); //Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

void GUI::PrintMsgnew(int x, int y, string msg) const
{
	ClearStatusBar(); //Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = x;
	int MsgY = y;

	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{

	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
		pWind->SetPen(DrawColor, 2);
	if (pCrs->get_Error_Status() == "NON")
	{
		pWind->SetBrush(FillColor);
	}
	else if (pCrs->get_Error_Status() == "Prerequisite")
	{
		pWind->SetBrush(ConnColor);
	}
	else if (pCrs->get_Error_Status() == "Corequisite")
	{
		pWind->SetBrush(StatusBarColor);
	}
	else if (pCrs->get_Error_Status() == "Prerequisite and Corequisite") 
	{
		pWind->SetBrush(HiColor);
	}
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY)
{
	//
	//
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pY->getGfxInfo();
	/*for (int i = 80; i < 640; i += 112)
	{
	pWind->DrawLine(0, i, 1300, i);
	}
	for (int i = 80; i < 640; i += 37.34)
	{
	pWind->DrawLine(80, i, 1300, i);
	}
	for (int i = 80; i < 640; i += 112)
	{
	pWind->DrawRectangle(0, i, 80, i);
	}*/
	// Error printing
	//pWind->SetFont(60 * 0.4, NORMAL_PRINT, BY_NAME, "Gramound");
	//pWind->SetPen(RED, 5);
	//int Code_x12 = 140 * 0.68;
	//int Code_y12 = 325 * 0.38;
	//pWind->DrawString(Code_x12, Code_y12, "CRITICAL ISSUES");
	
	//
	// VERTICAL 2 LINES
	pWind->DrawLine(80, 80, 80, 640);
	pWind->DrawLine(175, 80, 175, 640);
	pWind->DrawLine(1285, 80, 1285, 640);
	pWind->DrawLine(0, 80, 0, 640);
	pWind->DrawLine(1000, 80, 1000, 640);
	pWind->DrawLine(1150, 80, 1150, 400);
	// HORIZONTAL LINES
	pWind->DrawLine(0, 80, 1300, 80);
	pWind->DrawLine(1000, 130, 1300, 130);
	pWind->DrawLine(1000, 400, 1300, 400);

	pWind->DrawLine(80, 117.3, 1000, 117.3);
	pWind->DrawLine(80, 154.6, 1000, 154.6);

	pWind->DrawLine(0, 191.7, 1000, 191.7);
	pWind->DrawLine(80, 229.3, 1000, 229.3);
	pWind->DrawLine(80, 266.63, 1000, 266.63);

	pWind->DrawLine(0, 303.97, 1000, 303.97);
	pWind->DrawLine(80, 341.3, 1000, 341.3);
	pWind->DrawLine(80, 378.63, 1000, 378.63);

	pWind->DrawLine(0, 415.97, 1000, 415.97);
	pWind->DrawLine(80, 453.3, 1000, 453.3);
	pWind->DrawLine(80, 490.63, 1000, 490.63);

	pWind->DrawLine(0, 527.96, 1000, 527.96);
	pWind->DrawLine(80, 565.3, 1000, 565.3);
	pWind->DrawLine(80, 602.63, 1000, 602.63);
	pWind->DrawLine(0, 639, 1000, 639);

	int Code_x = 80 * 0.15;
	int Code_y = 80 + 112 * 0.38;
	pWind->SetFont(60 * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK_BRUSH, 5);
	ostringstream crd;
	crd << "crd:" << endl;
	pWind->DrawString(Code_x, Code_y, "Year 1");

	///
	int Code_x1 = 80 * 0.15;
	int Code_y1 = 80 + 417 * 0.38;
	pWind->DrawString(Code_x1, Code_y1, "Year 2");
	////
	int Code_x2 = 80 * 0.15;
	int Code_y2 = 80 + 710 * 0.38;
	pWind->DrawString(Code_x2, Code_y2, "Year 3");
	///
	int Code_x3 = 80 * 0.15;
	int Code_y3 = 80 + 1005 * 0.38;
	pWind->DrawString(Code_x3, Code_y3, "Year 4");
	///
	int Code_x4 = 80 * 0.15;
	int Code_y4 = 80 + 1300 * 0.38;
	pWind->DrawString(Code_x4, Code_y4, "Year 5");
	////////////////////////////////////////////////////////////////////////////////////////
	//SUB LINES
	pWind->SetFont(60 * 0.4, NORMAL_PRINT, BY_NAME, "Gramound");
	pWind->SetPen(RED, 5);
	int Code_x11 = 160 * 0.68;
	int Code_y11 = 230 * 0.38;
	pWind->DrawString(Code_x11, Code_y11, "Fall");
	int Code_x12 = 140 * 0.68;
	int Code_y12 = 325 * 0.38;
	pWind->DrawString(Code_x12, Code_y12, "Spring");
	int Code_x13 = 130 * 0.68;
	int Code_y13 = 420 * 0.38;
	pWind->DrawString(Code_x13, Code_y13, "Summer");
	//
	int Code_x21 = 160 * 0.68;
	int Code_y21 = 515 * 0.38;
	pWind->DrawString(Code_x21, Code_y21, "Fall");
	int Code_x22 = 140 * 0.68;
	int Code_y22 = 616 * 0.38;
	pWind->DrawString(Code_x22, Code_y22, "Spring");
	int Code_x23 = 130 * 0.68;
	int Code_y23 = 712 * 0.38;
	pWind->DrawString(Code_x23, Code_y23, "Summer");
	//
	int Code_x31 = 160 * 0.68;
	int Code_y31 = 806 * 0.38;
	pWind->DrawString(Code_x31, Code_y31, "Fall");
	int Code_x32 = 140 * 0.68;
	int Code_y32 = 909 * 0.38;
	pWind->DrawString(Code_x32, Code_y32, "Spring");
	int Code_x33 = 130 * 0.68;
	int Code_y33 = 1009 * 0.38;
	pWind->DrawString(Code_x33, Code_y33, "Summer");
	//
	int Code_x41 = 160 * 0.68;
	int Code_y41 = 1109 * 0.38;
	pWind->DrawString(Code_x41, Code_y41, "Fall");
	int Code_x42 = 140 * 0.68;
	int Code_y42 = 1209 * 0.38;
	pWind->DrawString(Code_x42, Code_y42, "Spring");
	int Code_x43 = 130 * 0.68;
	int Code_y43 = 1309 * 0.38;
	pWind->DrawString(Code_x43, Code_y43, "Summer");
	//
	int Code_x51 = 160 * 0.68;
	int Code_y51 = 1409 * 0.38;
	pWind->DrawString(Code_x51, Code_y51, "Fall");
	int Code_x52 = 140 * 0.68;
	int Code_y52 = 1509 * 0.38;
	pWind->DrawString(Code_x52, Code_y52, "Spring");
	int Code_x53 = 130 * 0.68;
	int Code_y53 = 1609 * 0.38;
	pWind->DrawString(Code_x53, Code_y53, "Summer");

	///TODO: compelete this function to:
	pWind->SetFont(60 * 0.3, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(ORANGE, 5);
	int Code_xerror1 = 1520 * 0.68;
	int Code_yerror1 = 230 * 0.38;
	int Code_xerror11 = 1535 * 0.68;
	int Code_yerror11 = 270 * 0.38;

	pWind->DrawString(Code_xerror1, Code_yerror1, "MODERATE");
	pWind->DrawString(Code_xerror11, Code_yerror11, "ISSUES");

	pWind->SetFont(60 * 0.3, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 5);

	int Code_xerror2 = 1730 * 0.68;
	int Code_yerror2 = 230 * 0.38;
	int Code_xerror22 = 1740 * 0.68;
	int Code_yerror22 = 270 * 0.38;

	pWind->DrawString(Code_xerror2, Code_yerror2, "CRITICAL");
	pWind->DrawString(Code_xerror22, Code_yerror22, "ISSUES");
	
	
	// 1- Draw a rectangle for the academic year
	// 2- Draw a sub-rectangle for each semester
	//Then each course should be drawn inside rect of its year/sem
	
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y); //Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE) //if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK) //mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS }; //Add course
				case ITM_DELETE: return ActionData{ DEL_CRS }; //DELETE
				case ITM_UNDO: return ActionData{ UNDO }; //Add course
				case ITM_REDO: return ActionData{ REDO }; //Add course
				case ITM_SAVE: return ActionData{ SAVE }; //SAVE
				case ITM_LOAD: return ActionData{ LOAD }; //Add course
				case ITM_EXIT: return ActionData{ EXIT }; //Exit

				default: return ActionData{ MENU_BAR }; //A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y }; //user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar



	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13: //ENTER key is pressed
			return userInput;

		case 8: //BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}




GUI::~GUI()
{
	delete pWind;
}