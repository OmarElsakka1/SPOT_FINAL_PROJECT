#include "AcademicYear.h"
#include "../GUI/GUI.h"

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year

	return true;
}

list<Course*> AcademicYear::returncourse(int semst)
{
	return YearCourses[semst];
}

bool AcademicYear::Check_Prequ(Course_Code Code, SEMESTER semster)
{
	for (int i = 0 ; i < semster ; i++)
	{
		for (auto it = YearCourses[i].begin(); it != YearCourses[i].end(); ++it)
		{
			if ((*it)->getCode() == Code)
			{
				return true;
			}
		}
		
	}
	return false;
}

bool AcademicYear::Check_Coqu(Course_Code Co_Code, SEMESTER semster)
{
	for (auto it = YearCourses[semster].begin(); it != YearCourses[semster].end(); ++it)
	{
		if ((*it)->getCode() == Co_Code)
		{
			return true;
		}
	}
	return false;
}

void AcademicYear::set_numofcreditspersemster(int semster,int numberofcredits)
{
	numberofcreditspersemster[semster] = numberofcredits;
}
int AcademicYear::get_numofcreditspersemster(int semster)
{
	return numberofcreditspersemster[semster];
}

void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course

	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}


