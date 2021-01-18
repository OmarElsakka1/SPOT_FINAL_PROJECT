#include "StudyPlan.h"



StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
}


//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	// to add the forth part of enumtring b take the course name to complete the mission.
	plan[year - 1]->AddCourse(pC, sem);
    return true;
}


bool StudyPlan::check_Preque(Course_Code Pre_Code, int year, SEMESTER semster)
{
	for (int i = 0; i < year; i++)
	{
		if (i == year -1)
		{
			if (plan[i]->Check_Prequ(Pre_Code, semster) == true)
			{
				return true;
			}
		}
		else 
		{

			if (plan[i]->Check_Prequ(Pre_Code, SEM_CNT) == true)
			{
				return true;
			}
		}
	}
	return false;
}

bool StudyPlan::check_Coque(Course_Code Co_Code, int year, SEMESTER semster)
{
	if (plan[year - 1]->Check_Coqu(Co_Code, semster) == true)
	{
		return true;
	}
	return false;
}

int StudyPlan::Plansize()
{
	return plan.size();
}

list<Course*> StudyPlan::returnsemster(int i, int j)
{
	list<Course*> temp;
	temp = plan[i]->returncourse(j);
	return temp;
}

void StudyPlan::set_numofcreditspersemster(int year, int semst , int numpersemster)
{
	plan[year - 1]->set_numofcreditspersemster(semst, numpersemster);
}

int StudyPlan::get_numofcreditspersemster(int year, int semst)
{
	int number = plan[year - 1]->get_numofcreditspersemster(semst);
	return number;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}

StudyPlan::~StudyPlan()
{
}
