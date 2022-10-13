#include "CHomework1.h"

void Name()
{
	std::cout << "Danya" << std::endl;
}

void Math()
{
	Input->In("Input the 2 nums for calculate(a, b)", 2U);
	if (Safety::isFloat(BUFFER(0)) && Safety::isFloat(BUFFER(1)))
	{
		double a = atof(BUFFER(0).c_str()), b = atof(BUFFER(1).c_str());

		std::cout << Safety::SafeNumber(a) << " + " << Safety::SafeNumber(b) << " = " << Safety::SafeNumber(a + b) << std::endl;
		std::cout << Safety::SafeNumber(a) << " - " << Safety::SafeNumber(b) << " = " << Safety::SafeNumber(a - b) << std::endl;
		std::cout << Safety::SafeNumber(a) << " * " << Safety::SafeNumber(b) << " = " << Safety::SafeNumber(a * b) << std::endl;
		if (b == 0.0) std::cout << "Div is impossible" << SKIPLINE;
		else std::cout << Safety::SafeNumber(a) << " / " << Safety::SafeNumber(b) << " = " << Safety::SafeNumber(a / b) << SKIPLINE;
	}
	else INCORRECT(Math);
}

void SquaresAlg(double b, double c)
{
	if (b == 0.0)
	{
		if (c != 0.0) std::cout << "Square roots do not exists" << SKIPLINE;
		else std::cout << "Any num is square root" << SKIPLINE;
	}
	else std::cout << "The x = " << Safety::SafeNumber(-c / b) << SKIPLINE;
}

void Squares()
{
	Input->In("Input the 2 nums for resolve (b, c)", 2U);
	if (Safety::isFloat(BUFFER(0)) && Safety::isFloat(BUFFER(1)))
	{
		double b = atof(BUFFER(0).c_str()), c = atof(BUFFER(1).c_str());

		SquaresAlg(b, c);
	}
	else INCORRECT(Squares);
}

void MoreSquares()
{
	Input->In("Input the 3 nums for resolve (a, b, c)", 3U);
	if (Safety::isFloat(BUFFER(0)) && Safety::isFloat(BUFFER(1)) && Safety::isFloat(BUFFER(2)))
	{
		double a = atof(BUFFER(0).c_str()), b = atof(BUFFER(1).c_str()), c = atof(BUFFER(2).c_str());

		if (a == 0.0) SquaresAlg(b, c);
		else
		{
			double D = pow(b, 2) - 4.0 * a * c;
			if (D < 0.0) std::cout << "Square roots do not exists" << SKIPLINE;
			else if (D == 0.0) std::cout << "x = " << Safety::SafeNumber(-b / 2.0 / a) << SKIPLINE;
			else std::cout << "x1 = " << Safety::SafeNumber((-b + sqrt(D)) / 2.0 / a) << std::endl << "x2 = " << Safety::SafeNumber((-b - sqrt(D)) / 2.0 / a) << SKIPLINE;
		}
	}
	else INCORRECT(MoreSquares);
}

void Lighter()
{
	Input->In("Input the 3 states for resolve (is day, curtains, lamp)", 3U);
	if (Safety::isBool(BUFFER(0)) && Safety::isBool(BUFFER(1)) && Safety::isBool(BUFFER(2)))
	{
		bool isDay = Safety::toBool(BUFFER(0)), isOpen = Safety::toBool(BUFFER(1)), isLamp = Safety::toBool(BUFFER(2));

		if (isDay && isOpen || isLamp) std::cout << "The room are bright" << SKIPLINE;
		else std::cout << "The room are dark" << SKIPLINE;
	}
	else INCORRECT(Lighter);
}

void CHomework1()
{
	new CHomework();
	new CExercise("Name", []() { Name(); });
	new CExercise("Arithmetic", []() { Math(); });
	new CExercise("Equation", []() { Squares(); });
	new CExercise("Again equation", []() { MoreSquares(); });
	new CExercise("Lamp with curtain", []() { Lighter(); });
}