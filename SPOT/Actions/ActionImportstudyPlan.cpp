#include "ActionImportstudyPlan.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

#include <iostream>
ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) :Action(p)
{
}

bool ActionImportStudyPlan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ifstream FILE("C:\\Users\\Omar El-Sakka\\Desktop\\Year2\\C++\\SPOT - CIE202 Project Code Framework\\SPOT\\x64\\CIE-StudyPlan.txt");
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	Course_Code code;
	string year;
	string semst;
	vector<vector<Course_Code>> yearvector;
	while (FILE.getline(line, size))
	{
		vector<Course_Code> semstervector;
		pch = strtok_s(line, ",", &context);
		while (pch != NULL)
		{
			semstervector.push_back(pch);
			pch = strtok_s(NULL, ",", &context);
		}
		yearvector.push_back(semstervector);
	}
	//pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	//Course_Code code = pGUI->GetSrting();
	double y = 80;
	double yearshift = -32;
	string yeartemp = "test";
	for (int i = 0; i < yearvector.size(); i++)
	{
		double x = 175;
		double disx = (810 / yearvector[i].size());
		for (int j = 0; j < yearvector[i].size(); j++)
		{
			if (j == 0)
			{
				year = yearvector[i][j];
				if (yeartemp != yearvector[i][j])
				{
					yearshift += 112;
					yeartemp = yearvector[i][j];
				}
			}
			if (j == 1)
			{
				semst = yearvector[i][j];
				x = 175;
				if (semst != "Fall")
				{
					y += 37.3;
				}
				else
				{
					y = yearshift;
				}
			}
			if (j >= 2)
			{
				x += disx;
				code = yearvector[i][j];
				CourseInfo Cinfo;
				Cinfo.Code = code;
				bool check = pReg->getCourseInfo(Cinfo);
				ActionData actData;
				actData.x = x;
				actData.y = y;
				actData.actType = DRAW_AREA;
				graphicsInfo gInfo{ x, y };
				string Title = "TEST";
				int crd = 0;
				if (check == true)
				{
					string Title = Cinfo.Title;
					crd = Cinfo.Credits;
				}
				Course* pC = new Course(code, Title, crd);
				pC->setGfxInfo(gInfo);
				//ginfodonebyme.push_back(gInfo);  //created mainly by me
				//Coder.push_back(code);   //created mainly by me
				StudyPlan* pS = pReg->getStudyPlay();
				int yearint = 0;
				if (true)
				{
					if (year == "Year 1")
					{
						yearint = 1;
					}
					else if (year == "Year 2")
					{
						yearint = 2;
					}
					else if (year == "Year 3")
					{
						yearint = 3;
					}
					else if (year == "Year 4")
					{
						yearint = 4;
					}
					else if (year == "Year 5")
					{
						yearint = 5;
					}

					if (semst == "Fall")
					{
						pS->AddCourse(pC, yearint, FALL);
					}
					else if (semst == "Spring")
					{
						pS->AddCourse(pC, yearint, SPRING);
					}
					else if (semst == "Summer")
					{
						pS->AddCourse(pC, yearint, SUMMER);
					}
				}
			}
		}
	}
	return true;

}

//TODO: add input validation}


ActionImportStudyPlan::~ActionImportStudyPlan()
{

}