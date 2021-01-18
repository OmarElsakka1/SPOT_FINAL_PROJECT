#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void getProgramRequirements();
	void getCourseOfferings();
	void getCourseCatalog();
	bool getCourseInfo(CourseInfo&);
	bool checking_Pre(Course_Code Code, int year, SEMESTER semster);
	bool checking_Co(Course_Code Code, int year, SEMESTER semster);
	bool checking();
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;

	void Run();

	~Registrar();
};

