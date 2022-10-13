#pragma once

#include "../main.h"

class CHomework;
class CExercise;

class CData
{
public:
	void AddHomework(CHomework* _CHomework)
	{
		homeworks.push_back(_CHomework);
	}

public:
	std::vector<CHomework*> homeworks;
	std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
}; extern CData* g_pData;

class CHomework
{
public:
	CHomework()
	{
		g_pData->AddHomework(this);
	}

	void AddExercise(CExercise* _CExercise)
	{
		exercises.push_back(_CExercise);
	}

public:
	std::vector<CExercise*> exercises;
};

class CExercise
{
public:
	void Run();

	std::string exName;
	std::function<void()> exFunction;

	CExercise(std::string _exName, std::function<void()> _exFunction = {});
};

void SetupHomeworks();