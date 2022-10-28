#include "CHomework3.h"

double getPayment(double s, double p, int n)
{
	return p / 100.0 * pow(1.0 + p / 100.0, n) / (pow(1.0 + p / 100.0, n) - 1.0) / 12.0 * s;
}

void Loan()
{
	Input->In("Input the 3 nums for resolve (s, p, n)", 3U);
	if (Safety::isFloat(BUFFER(0).c_str(), POSITIVE) && Safety::isFloat(BUFFER(1).c_str(), POSITIVE) && Safety::isNumber(BUFFER(2).c_str(), POSITIVE))
	{
		double s = atof(BUFFER(0).c_str()), p = atof(BUFFER(1).c_str());
		int n = atoi(BUFFER(2).c_str());

		std::cout << "The monthly payment is " << Safety::SafeNumber(getPayment(s, p, n)) << SKIPLINE;
	}
	else INCORRECT(Loan);
}

void getPercentage()
{
	Input->In("Input the 3 nums for resolve (s, n, m, e [min = 1, max = 6])", 4U);
	if (Safety::isFloat(BUFFER(0).c_str(), POSITIVE) && Safety::isNumber(BUFFER(1).c_str(), POSITIVE) && Safety::isFloat(BUFFER(2).c_str(), POSITIVE) && Safety::isNumber(BUFFER(3).c_str(), POSITIVE))
	{
		double h = 10;
		double s = atof(BUFFER(0).c_str()), m = atof(BUFFER(2).c_str()), e = pow(10, -12), p = h / 10.;
		int n = atoi(BUFFER(1).c_str());
		
		while (h > e)
		{
			h /= 2;
			for (; m - getPayment(s, p, n) >= 0; p += h);
			
			if (p == 0.5) h = e;
			else h /= 2;
			
			for (; m - getPayment(s, p, n) <= 0; p -= h);
		}

		if (p > 0.0) std::cout << "The percentage of loan is " << Safety::SafeNumber(p, static_cast<size_t>(atoi(BUFFER(3).c_str()))) << SKIPLINE;
		else std::cout << "The percentage is incorrect" << SKIPLINE;
	}
	else INCORRECT(getPercentage);
}

void CopyFile()
{
	Input->In("Input the 1 string (file name)", 1U);

	std::string name = BUFFER(0);
	std::ofstream cFile(name + ".txt");
	if (cFile.is_open())
	{
		Input->In("Input the strings for file (you can use \\n)", 0U, "\\n");
		for (size_t i = 0U; i < Input->getSize(); i++) cFile << BUFFER(i) << std::endl;
	}
	cFile.close();

	std::ifstream oFile(name + ".txt");
	if (oFile.is_open())
	{
		std::string line;
		while (std::getline(oFile, line)) std::cout << line << std::endl;
		std::cout << std::endl;
	}
	oFile.close();
}

void Filter()
{
	Input->In("Input the 1 string (file name)", 1U);

	std::string name = BUFFER(0);
	std::ofstream cFile(name + ".txt");
	if (cFile.is_open())
	{
		Input->In("Input the strings for file (you can use \\n)", 0U, "\\n");
		for (size_t i = 0U; i < Input->getSize(); i++) cFile << BUFFER(i) << std::endl;
	}
	cFile.close();

	std::ifstream oFile(name + ".txt");
	if (oFile.is_open())
	{
		std::string line;
		while (std::getline(oFile, line))
		{
			bool isSpace = line.at(0) < 0x30 && line.at(0) > 0x39;
			std::string numbers;
			for (size_t i = 0U; i < line.length(); i++)
			{
				if (line.at(i) >= 0x30 && line.at(i) <= 0x39)
				{
					if (isSpace || line.at(i) != 0x30)
					{
						numbers += line.at(i);
						isSpace = true;
					}
					else numbers += "0 ";
				}
				else if (isSpace)
				{
					numbers += " ";
					isSpace = false;
				}
			}
			std::cout << numbers << std::endl;
		}
	}
	oFile.close();
}

std::string Sort(std::string data)
{
	std::string ret = "", signs = "";

	for (int i = 0x41; i <= 0x5A; i++) for (size_t j = 0U; j < data.length(); j++) if (data.at(j) == i || data.at(j) == i + 0x20) ret += data.at(j);
	for (size_t i = 0U; i < data.length(); i++) if (!(data.at(i) >= 0x41 && data.at(i) <= 0x5A || data.at(i) >= 0x61 && data.at(i) <= 0x7A)) signs += data.at(i);

	return ret + signs;
}

void Sort()
{
	Input->In("Input the 1 string to sort (the length should be 30 symbols)", 1U);

	std::string resolve = BUFFER(0);
	if (resolve.length() == 30) std::cout << Sort(parts.at(i).at(j).c_str()) << " ";
	else INCORRECT(Sort);
	
	/* More advanced version of sort
	Input->In("Input the 1 string to sort (you can use \\n)", 0U, "\\n");

	std::vector<std::vector<std::string>> parts;
	for (size_t i = 0U; i < Input->getSize(); i++) parts.push_back(Input->ToParts(BUFFER(i)));
	for (size_t i = 0U; i < parts.size(); i++)
	{
		for (size_t j = 0U; j < parts.at(i).size(); j++) std::cout << Sort(parts.at(i).at(j).c_str()) << " ";
		std::cout << std::endl;
	} */
	
	std::cout << std::endl;
}

void CHomework3()
{
	new CHomework();
	new CExercise("Loan", []() { Loan(); });
	new CExercise("Loan percentage", []() { getPercentage(); });
	new CExercise("Copy the file", []() { CopyFile(); });
	new CExercise("Filter", []() { Filter(); });
	new CExercise("Sort", []() { Sort(); });
}
