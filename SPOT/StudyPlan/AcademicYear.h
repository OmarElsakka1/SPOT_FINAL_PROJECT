#pragma once
#include <list>

#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"

//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits = numberofcreditspersemster[0] + numberofcreditspersemster[1] + numberofcreditspersemster[2];		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;
	int numberofcreditspersemster[3]; 
	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	
public:
	AcademicYear();
	virtual ~AcademicYear();
	bool Check_Prequ(Course_Code Pre_Code, SEMESTER semster);
	list<Course*> returncourse(int semst);
	bool Check_Coqu(Course_Code Co_Code, SEMESTER semster);
	bool AddCourse(Course*, SEMESTER );

	void set_numofcreditspersemster(int semster, int numberofcredits);
	int get_numofcreditspersemster(int semster);

	void virtual DrawMe(GUI*) const;
};

