#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionImportStudyPlan.h"
#include <algorithm>
Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	getCourseCatalog();
	getCourseOfferings();
	getProgramRequirements();
}

void Registrar::getCourseCatalog()
{
	ifstream finput("C:\\Users\\Omar El-Sakka\\Desktop\\Year2\\C++\\SPOT - CIE202 Project Code Framework\\SPOT\\x64\\courseInfofile.txt");
	char* pch;
	string CourseCode;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	RegRules.CourseCatalog.clear();
	while (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, ",", &context);
		if (pch != NULL)
		{
			CourseInfo CourseCode;
			CourseCode.Code = pch;

			pch = strtok_s(NULL, ",", &context);
			if (pch != NULL)
			{
				CourseCode.Title = pch;
				pch = strtok_s(NULL, ",", &context);
			}
			if (pch != NULL)
			{
				CourseCode.Credits = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}

			if (pch != NULL)
			{
				string s = pch;
				istringstream iss(s);
				int x = 0;
				int y = 0;
				do
				{
					string subs1, subs2;
					iss >> subs1;
					if (x == 1)
					{
						iss >> subs2;
						string sub = subs1 + " " + subs2;
						sub.erase(remove(sub.begin(), sub.end(), ';'), sub.end());
						CourseCode.CoReqList.push_back(sub);
						x = 0;
					}
					if (subs1 == "Coreq:")
					{
						x = 1;
						y = 1;
					}
					if (subs1 == "And" && y == 1)
					{
						x = 1;
					}
				} while (iss);
				if (y == 1)
				{
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (pch != NULL)
			{
				string s = pch;
				istringstream iss(s);
				int x = 0;
				int y = 0;
				do
				{
					string subs1, subs2;
					iss >> subs1;
					if (x == 1)
					{
						iss >> subs2;
						string sub = subs1 + " " + subs2;
						sub.erase(remove(sub.begin(), sub.end(), ';'), sub.end());
						CourseCode.PreReqList.push_back(sub);
						x = 0;
					}
					if (subs1 == "Prereq:")
					{
						x = 1;
						y = 1;
					}
					if (subs1 == "And" && y == 1)
					{
						x = 1;
					}
				} while (iss);
				pch = strtok_s(NULL, ",", &context);
			}
			if (true)
			{
				ifstream finput1("C:\\Users\\Omar El-Sakka\\Desktop\\Year2\\C++\\SPOT - CIE202 Project Code Framework\\SPOT\\x64\\programrequirementsfile.txt");
				char* pch;
				char* context = nullptr;
				const int size = 300;
				char line[size];
				if (finput1.getline(line, size)) //read file line by line
				{ //parse the line
					pch = strtok_s(line, ",", &context);
					for (int i = 0; i < 5; i++)
					{
						if (pch != NULL)
						{
							pch = strtok_s(line, ",", &context);
							finput1.getline(line, size);
						}
					}
					for (int i = 0; i < 2; i++)
					{
						if (finput1.getline(line, size))
						{
							pch = strtok_s(line, ",", &context);
							while (pch != NULL)
							{
								if (CourseCode.Code == pch)
								{
									CourseCode.type = "Univ";
								}
								pch = strtok_s(NULL, ",", &context);
							}
						}
					}
					if (finput1.getline(line, size))
					{
						pch = strtok_s(line, ",", &context);
						while (pch != NULL)
						{
							if (CourseCode.Code == pch)
							{
								CourseCode.type = "Track";
							}
							pch = strtok_s(NULL, ",", &context);
						}
					}
					for (int i = 0; i < 2; i++)
					{
						if (finput1.getline(line, size))
						{
							pch = strtok_s(line, ",", &context);
							while (pch != NULL)
							{
								if (CourseCode.Code == pch)
								{
									CourseCode.type = "Major";
								}
								pch = strtok_s(NULL, ",", &context);
							}
						}
					}
				}
			}
			RegRules.CourseCatalog.push_back(CourseCode);
		}

	}
}
void Registrar::getCourseOfferings()
{
	ifstream finput("C:\\Users\\Omar El-Sakka\\Desktop\\Year2\\C++\\SPOT - CIE202 Project Code Framework\\SPOT\\x64\\courseofferingsfile.txt");
	char* pch;
	char* context = nullptr;
	const int size = 300;
	string redundant; //Note it is so important
	string check;
	RegRules.OffringsList.clear();
	vector<Course_Code> temp;
	char line[size];
	while (finput.getline(line, size)) //read file line by line
	{ //parse the line
		AcademicYearOfferings year;
		pch = strtok_s(line, ",", &context);
		if (pch != NULL)
		{
			year.Year = pch;
			check = pch;
			pch = strtok_s(NULL, ",", &context);
		}
		if (pch != NULL)
		{
			redundant = pch;
			pch = strtok_s(NULL, ",", &context);
			if (redundant == "Semester 1" && pch != NULL)
			{
				while (pch != NULL)
				{
					temp.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			year.Offerings.push_back(temp);
			while (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				if (pch != NULL)
				{
					if (check == pch)
					{
						pch = strtok_s(NULL, ",", &context);
						redundant = pch;
						if (redundant == "Semester 2" && pch != NULL)
						{
							pch = strtok_s(NULL, ",", &context);
							while (pch != NULL)
							{
								temp.push_back(pch);
								pch = strtok_s(NULL, ",", &context);
							}
						}
						year.Offerings.push_back(temp);
					}
					pch = strtok_s(NULL, ",", &context);
				}
			}
			while (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				if (pch != NULL)
				{
					if (check == pch)
					{
						pch = strtok_s(NULL, ",", &context);
						redundant = pch;
						if (redundant == "Semester 3" && pch != NULL)
						{
							pch = strtok_s(NULL, ",", &context);
							while (pch != NULL)
							{
								temp.push_back(pch);
								pch = strtok_s(NULL, ",", &context);
							}
						}
						year.Offerings.push_back(temp);
					}
					pch = strtok_s(NULL, ",", &context);
				}
			}
		}
		RegRules.OffringsList.push_back(year);
	}
}
void Registrar::getProgramRequirements()
{
	ifstream finput("C:\\Users\\Omar El-Sakka\\Desktop\\Year2\\C++\\SPOT - CIE202 Project Code Framework\\SPOT\\x64\\programrequirementsfile.txt");
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	if (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, ",", &context);
		if (pch != NULL)
		{
			RegRules.TotalCredit = stoi(pch);
			pch = strtok_s(NULL, ",", &context);
		}
		if (finput.getline(line, size)) //read file line by line
		{ //parse the line
			int counter;
			pch = strtok_s(line, ",", &context);
			if (pch != NULL)
			{
				counter = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
			if (pch != NULL)
			{
				counter = counter + stoi(pch);
				RegRules.ReqUnivCredits = counter;
				pch = strtok_s(NULL, ",", &context);
				counter = 0;
			}
		}
		if (finput.getline(line, size)) //read file line by line
		{ //parse the line
			pch = strtok_s(line, ",", &context);
			if (pch != NULL)
			{
				RegRules.ReqTrackCredits = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
		}
		if (finput.getline(line, size)) //read file line by line
		{ //parse the line
			int counter;
			pch = strtok_s(line, ",", &context);
			if (pch != NULL)
			{
				counter = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
			if (pch != NULL)
			{
				counter = counter + stoi(pch);
				RegRules.ReqMajorCredits = counter;
				pch = strtok_s(NULL, ",", &context);
				counter = 0;
			}
		}
		if (finput.getline(line, size)) //read file line by line
		{ //parse the line
			pch = strtok_s(line, ",", &context);
			if (pch != NULL)
			{
				RegRules.NumOfConcentrations = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
		}
		if (finput.getline(line, size)) //read file line by line
		{ //parse the line
			pch = strtok_s(line, ",", &context);
			if (pch != NULL)
			{
				RegRules.CreditsOfConcentration1 = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
			if (pch != NULL)
			{
				RegRules.CreditsOfConcentration2 = stoi(pch);
				pch = strtok_s(NULL, ",", &context);
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				while (pch != NULL)
				{
					RegRules.UnivCompulsory.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				while (pch != NULL)
				{
					RegRules.UnivElective.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				while (pch != NULL)
				{
					RegRules.TrackCompulsory.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				while (pch != NULL)
				{
					RegRules.MajorCompulsory.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				while (pch != NULL)
				{
					RegRules.MajorElective.push_back(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
			if (finput.getline(line, size)) //read file line by line
			{ //parse the line
				pch = strtok_s(line, ",", &context);
				if (pch != NULL)
				{
					RegRules.SemMinCredit = stoi(pch);
					pch = strtok_s(NULL, ",", &context);
				}
				if (pch != NULL)
				{
					RegRules.SemMaxCredit = stoi(pch);
					pch = strtok_s(NULL, ",", &context);
				}
			}
		}
	}
}
bool Registrar::getCourseInfo(CourseInfo &Cinfo)
{
	
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	{
		if (RegRules.CourseCatalog[i].Code == Cinfo.Code)
		{
			Cinfo.Title = RegRules.CourseCatalog[i].Title;
			Cinfo.type = RegRules.CourseCatalog[i].type;
			Cinfo.CoReqList = RegRules.CourseCatalog[i].CoReqList;
			Cinfo.PreReqList = RegRules.CourseCatalog[i].PreReqList;
			Cinfo.Credits = RegRules.CourseCatalog[i].Credits;
			return true;
		}
	}
	return false;
}

bool Registrar::checking_Pre(Course_Code Code, int year, SEMESTER semster)
{
	bool check_Pre;
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	{
		if (RegRules.CourseCatalog[i].Code == Code)
		{
			for (int j = 0; j < RegRules.CourseCatalog[i].PreReqList.size(); j++)
			{
				check_Pre = pSPlan->check_Preque(RegRules.CourseCatalog[i].PreReqList[j], year, semster);
				if (check_Pre == false)
				{
					return false;
				}
			}
			return true;
		}
	}
}
bool Registrar::checking_Co(Course_Code Code, int year, SEMESTER semster)
{
	bool check_Co;
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	{
		if (RegRules.CourseCatalog[i].Code == Code)
		{
			for (int j = 0; j < RegRules.CourseCatalog[i].CoReqList.size(); j++)
			{
				check_Co = pSPlan->check_Coque(RegRules.CourseCatalog[i].CoReqList[j], year, semster);
				if (check_Co == false)
				{
					return false;
				}
			}
			return true;
		}
	}
}
bool Registrar::checking()
{
	//pGUI->PrintMsgnew(1200, 550, "omar");
	list<Course*> temp;
	
	vector<string> errors;
	bool checker_Pre;
	bool checker_Co;
	int maxpersemster = 12;
	int minpersemster = 21;
	int initial_value = 570;
	int initial_value2 = 570;
	for (int i = 0; i < pSPlan->Plansize(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp = pSPlan->returnsemster(i, j);
			int number_of_credits = 0;
			int year = i + 1;//actually year-1.
			for (auto it = temp.begin(); it != temp.end(); ++it)
			{
				bool checker_Pre;
				bool checker_Co;
				Course_Code Code = (*it)->getCode();
				number_of_credits += (*it)->getCredits();
				//pSPlan->set_numofcreditspersemster(year, j, number_of_credits);
				if (j == 0)
				{
					checker_Pre = checking_Pre(Code, year, FALL);
					checker_Co = checking_Co(Code, year, FALL);

				}
				if (j == 1)
				{
					checker_Pre = checking_Pre(Code, year, SPRING);
					checker_Co = checking_Co(Code, year, SPRING);
				}
				if (j == 2)
				{
					checker_Pre = checking_Pre(Code, year, SUMMER);
					checker_Co = checking_Co(Code, year, SUMMER);
				}

				if (checker_Pre == true && checker_Co == true)
				{
					(*it)->set_Error_Status("NON");//NO error in Prerequisite, nor corequisite
					for (int i = 0 ; i < errors.size(); i++)
					{
						if (errors[i] == Code)
						{
							initial_value += 20;
							errors.erase(errors.begin() + i);
						}
					}
				}
				else if (checker_Pre == false && checker_Co == true)
				{
					(*it)->set_Error_Status("Prerequisite");//Error Prerequisite
					bool check = true;
					for (int i = 0 ; i <errors.size(); i++)
					{
						if (Code == errors[i])
						{
							check = false;
						}
					}
					if (check == true)
					{
						errors.push_back(Code);
						initial_value -= 20;
						pGUI->PrintMsgnew(1180, initial_value, Code);
						pGUI->DrawCourse(*it);
					}
				}
				else if (checker_Pre == true && checker_Co == false)
				{
					(*it)->set_Error_Status("Corequisite");//Error Prerequisite
					bool check = true;
					for (int i = 0; i < errors.size(); i++)
					{
						if (Code == errors[i])
						{
							check = false;
						}
					}
					if (check == true)
					{
						errors.push_back(Code);
						initial_value -= 20;
						pGUI->PrintMsgnew(1180, initial_value, Code);
						pGUI->DrawCourse(*it);
					}
				}
				else if (checker_Pre == false && checker_Co == false)
				{
					(*it)->set_Error_Status("Prerequisite and Corequisite");//Error Prerequisite
					bool check = true;
					for (int i = 0; i < errors.size(); i++)
					{
						if (Code == errors[i])
						{
							check = false;
						}
					}
					if (check == true)
					{
						errors.push_back(Code);
						initial_value -= 20;
						pGUI->PrintMsgnew(1180, initial_value, Code);
						pGUI->DrawCourse(*it);
					}
				}
			}
			pSPlan->set_numofcreditspersemster(year, j, number_of_credits);
			if ( (number_of_credits < 12 || number_of_credits > 21) &&  (number_of_credits != 0) )//
			{
				string semsts;
				string years;
				if (year == 1)
				{
					years = "year 1";
				}
				if (year == 2)
				{
					years = "year 2";
				}
				if (year == 3)
				{
					years = "year 3";
				}
				if (year == 4)
				{
					years = "year 4";
				}
				if (year == 5)
				{
					years = "year 5";
				}
				if (j == 0)
				{
					semsts = "Fall of ";
				}
				if (j == 1)
				{
					semsts = "Spring of ";
				}
				if (j == 2)
				{
					semsts = "Summer of ";
				}
				string errorstate = semsts + years;
				pGUI->PrintMsgnew(1000, initial_value2, errorstate);
				initial_value2 -= 20;
			}
		}
	}
	return true;
}



//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS: //add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case DEL_CRS: //add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case SAVE:
		RequiredAction = new ActionAddCourse(this);
		//ActionImportStudyPlan(this);
		break;
		//TODO: Add case for each action
	case LOAD:
		RequiredAction = new ActionImportStudyPlan(this);
		break;
	case UNDO:
		RequiredAction = new ActionAddCourse(this);
		break;
	case REDO:
		RequiredAction = new ActionAddCourse(this);
		break;
	case EXIT:
		break;

	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		
		
		UpdateInterface();
		checking();
		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
		
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

Registrar::~Registrar()
{
	delete pGUI;
}
