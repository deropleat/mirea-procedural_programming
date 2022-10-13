#include "Homework.h"

CData* g_pData = new CData;

CExercise::CExercise(std::string _exName, std::function<void()> _exFunction)
{
	exName = _exName;
	exFunction = _exFunction;

	g_pData->homeworks.at(g_pData->homeworks.size() - 1)->AddExercise(this);
}

void CExercise::Run()
{
	return exFunction();
}

void SetupHomeworks()
{

	CHomework1();
	CHomework2();
	CHomework3();
	CHomework4();
	CHomework5();
}