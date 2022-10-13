#include "CHomework1.h"

void getCone()
{
	Input->In("Input the 3 nums for calculate (height, base radius and end radius)", 3U);
	if (Safety::isFloat(BUFFER(0), POSITIVE) && Safety::isFloat(BUFFER(1), POSITIVE) && Safety::isFloat(BUFFER(2), POSITIVE))
	{
		double h = atof(BUFFER(0).c_str()), bR = atof(BUFFER(1).c_str()), r = atof(BUFFER(2).c_str());
		double l = sqrt(pow(bR - r, 2) + pow(h, 2));

		if (Safety::isTriangle(l, h, bR - r))
		{
			std::cout << "V = " << Safety::SafeNumber(M_PI * h * (pow(bR, 2) + bR * r + pow(r, 2)) / 3.0) << std::endl;
			std::cout << "S = " << Safety::SafeNumber(M_PI * (pow(bR, 2) + (bR + r) * l + pow(r, 2))) << SKIPLINE;
		}
		else std::cout << "Solution is not exist" << SKIPLINE;
	}
	else INCORRECT(getCone);
}

void getExpression()
{
	Input->In("Input the 2 nums for resolve the system (x, a)", 2U);
	if (Safety::isFloat(BUFFER(0)) && Safety::isFloat(BUFFER(1)))
	{
		double x = atof(BUFFER(0).c_str()), a = atof(BUFFER(1).c_str());

		if (abs(x) < 1.0 && x != 0.0) std::cout << "w = " << Safety::SafeNumber(a * log(abs(x))) << SKIPLINE;
		else if (a - pow(x, 2) >= 0.0 && abs(x) >= 1.0) std::cout << "w = " << Safety::SafeNumber(sqrt(a - pow(x, 2))) << SKIPLINE;
		else std::cout << "Solution is not exist" << SKIPLINE;
	}
	else INCORRECT(getExpression);
}

void getResult()
{
	Input->In("Input the 3 nums for get the result of function (x, y, b)", 3U);
	if (Safety::isFloat(BUFFER(0)) && Safety::isFloat(BUFFER(1)) && Safety::isFloat(BUFFER(2)))
	{
		double x = atof(BUFFER(0).c_str()), y = atof(BUFFER(1).c_str()), b = atof(BUFFER(2).c_str());

		if (b - y > 0.0 and b - x >= 0.0) std::cout << "z = " << Safety::SafeNumber(log(b - y) * sqrt(b - x)) << SKIPLINE;
		else std::cout << "Solution is not exist" << SKIPLINE;
	}
	else INCORRECT(getResult);
}

void printNumbers()
{
	Input->In("Input the 1 num for setup the start point of counter (N)", 1U);
	if (Safety::isNumber(BUFFER(0).c_str(), POSITIVE))
	{
		int N = atoi(BUFFER(0).c_str());

		for (int i = N; i < N + 10; i++) std::cout << i << " ";
		std::cout << SKIPLINE;
	}
	else INCORRECT(printNumbers);
}

void getTabs()
{
	for (float i = -4; i <= 4; i += 0.5f)
	{
		if (i - 1.f == 0.f) std::cout << "y(" << i << ") is not exist" << std::endl;
		else std::cout << "y(" << i << ") = " << Safety::SafeNumber((pow(i, 2) - 2.f * i + 2.f) / (i - 1.f)) << std::endl;
	}
	std::cout << SKIPLINE;
}

void CHomework2()
{
	new CHomework();
	new CExercise("Cone", []() { getCone(); });
	new CExercise("Branching", []() { getExpression(); });
	new CExercise("Function", []() { getResult(); });
	new CExercise("Sequence", []() { printNumbers(); });
	new CExercise("Tabulation", []() { getTabs(); });
}