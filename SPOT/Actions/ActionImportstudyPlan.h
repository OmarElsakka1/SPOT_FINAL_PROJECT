#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionImportStudyPlan :
	public Action
{
public:

	ActionImportStudyPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportStudyPlan();
};

