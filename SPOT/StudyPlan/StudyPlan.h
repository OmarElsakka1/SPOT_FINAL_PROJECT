#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"

//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	//plan is a list of academic years
	
	string PlanNotes;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool check_Preque(Course_Code pre_course,int year, SEMESTER semster);
	bool check_Coque(Course_Code co_course, int year, SEMESTER semster);
	list<Course*> returnsemster(int i, int j);
	void set_numofcreditspersemster(int year, int semst, int numpersemster);
	int get_numofcreditspersemster(int year, int semst);
	int Plansize();
	
	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
};

