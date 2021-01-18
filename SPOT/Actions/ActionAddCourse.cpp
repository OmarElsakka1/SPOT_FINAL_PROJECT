#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

#include <iostream>
ActionAddCourse::ActionAddCourse(Registrar * p) :Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	CourseInfo Cinfo;
	Cinfo.Code = code;
	bool check = pReg->getCourseInfo(Cinfo);
	if (check == true)
	{
		ActionData actData = pGUI->GetUserAction("Select a year to add coures to:(To be implemented in phase1) we will just draw coures where user clicks");
		//TODO: add input validation


		int x, y;
		if (actData.actType == DRAW_AREA) //user clicked inside drawing area
		{
			//get coord where user clicked
			x = actData.x;
			y = actData.y;



			graphicsInfo gInfo{ x, y };

			//TODO: given course code, get course title, crd hours from registrar
			//For now, we will add any dummy values
			string Title = Cinfo.Title;
			int crd = Cinfo.Credits;
			Course* pC = new Course(code, Title, crd);
			pC->setGfxInfo(gInfo);
			

			//TODO: Ask registrar to add course to the year selected by the user
			//TODO: add the course to the correct year obtained from registrar
			//For the seke of demo, we will add the course to the 1st year, 1st semester
			StudyPlan* pS = pReg->getStudyPlay();
			pS->AddCourse(pC, 1, FALL);
		}
		return true;
	}

	//TODO: add input validation

}


ActionAddCourse::~ActionAddCourse()
{
}