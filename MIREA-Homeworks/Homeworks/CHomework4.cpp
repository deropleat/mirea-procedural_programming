#include "CHomework4.h"

void exFile()
{
	Input->In("Input the 1 string (file name)", 1U);

	std::string name = BUFFER(0);
	std::ofstream cFile(name + ".txt");
	if (cFile.is_open())
	{
		Input->In("Input the 10 nums for put in the file (nums)", 10U);

		bool isNumbers = true;
		for (size_t i = 0; i < Input->getSize(); i++)
		{
			if (!Safety::isFloat(BUFFER(i).c_str()))
			{
				isNumbers = false;
				break;
			}
		}

		if (isNumbers) for (size_t i = 0; i < Input->getSize(); i++) cFile << BUFFER(i) << " ";
		else
		{
			cFile.close();
			INCORRECT(exFile);
		}
	}
	cFile.close();

	std::ifstream oFile(name + ".txt");
	if (oFile.is_open())
	{
		std::string line;
		std::getline(oFile, line);

		auto getSum = [](std::string value)->double
		{
			double ret = 0.0;
			while (value.find(" ") != std::string::npos)
			{
				ret += atof(value.substr(0U, value.find(" ")).c_str());
				value = value.substr(value.find(" ") + 1U);
			}
			if (value.length() > 0) ret += atof(value.c_str());

			return ret;
		};

		std::cout << "The sum of numbers is " << Safety::SafeNumber(getSum(line)) << SKIPLINE;
	}
	oFile.close();
}

int getSign(double x)
{
	return x > 0.0 ? 1 : x < 0.0 ? -1 : 0;
}

void getSign()
{
	Input->In("Input the 1 num (x)", 1U);

	if (Safety::isFloat(BUFFER(0).c_str())) std::cout << "The sign of x is " << getSign(atof(BUFFER(0).c_str())) << SKIPLINE;
	else INCORRECT(getSign);
}

std::string sqrSquare(double w, double h)
{
	return Safety::SafeNumber(w * h);
}

std::string sqrCircle(double r)
{
	return Safety::SafeNumber(M_PI * pow(r, 2));
}

std::string sqrTriangle(double p, double a, double b, double c)
{
	return Safety::SafeNumber(sqrt(p * (p - a) * (p - b) * (p - c)));
}

void getSquare(size_t shape)
{
	switch (shape)
	{
	case 0U:
		Input->In("Input the 2 nums of size the rectangle (width, height)", 2U);
		if (Safety::isFloat(BUFFER(0).c_str(), POSITIVE) && Safety::isFloat(BUFFER(1).c_str(), POSITIVE))
		{
			std::cout << "The square of rectangle is " << sqrSquare(atof(BUFFER(0).c_str()), atof(BUFFER(1).c_str())) << SKIPLINE;
			return;
		}
		break;
	case 1U:
		Input->In("Input the 1 nums of radius the circle (radius)", 1U);
		if (Safety::isFloat(BUFFER(0).c_str(), POSITIVE))
		{
			std::cout << "The square of circle is " << sqrCircle(atof(BUFFER(0).c_str())) << SKIPLINE;
			return;
		}
		break;
	case 2U:
		Input->In("Input the 3 nums for size of sides the triangle (3 sides)", 3U);
		if (Safety::isFloat(BUFFER(0).c_str(), POSITIVE) && Safety::isFloat(BUFFER(1).c_str(), POSITIVE) && Safety::isFloat(BUFFER(2).c_str(), POSITIVE))
		{
			double a = atof(BUFFER(0).c_str()), b = atof(BUFFER(1).c_str()), c = atof(BUFFER(2).c_str());

			if (Safety::isTriangle(a, b, c))
			{
				double p = (a + b + c) / 2.0;
				std::cout << "The square of triangle is " << sqrTriangle(p, a, b, c) << SKIPLINE;
				return;
			}
		}
		break;
	default: break;
	}

	std::cout << "Invalid values" << SKIPLINE;
}

void getSquare()
{
	Input->In("Input the type of shape (rectangle = 0, circle = 1, triangle = 2 or full name)", 1U);

	size_t shape = SIZE_MAX;
	if (Safety::isNumber(BUFFER(0).c_str(), ISPLUS)) shape = static_cast<size_t>(atoi(BUFFER(0).c_str()));
	else
	{
		std::vector<std::string> shapes = { "rectangle", "circle", "triangle" };
		std::string lShape = BUFFER(0);

		Safety::ToLower(lShape);
		for (size_t i = 0U; i < shapes.size() - 1U; i++) if (lShape == shapes.at(i)) shape = i;
	}

	if (shape > 2) INCORRECT(getSquare)
	else getSquare(shape);
}

void drawFlag()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; i < 8 && j < 8; j++) std::cout << "* ";
		std::cout << std::string(static_cast<size_t>(40 + (i > 7 ? 16 : 0)), '-') << std::endl;
	}
	std::cout << std::endl;
}

void drawSinusOLD()
{
	std::vector<std::string> strings;
	std::string lastChar;
	size_t pos = 0U;
	int prev = -1000;

	for (int i = 0; i < 21; i++) strings.push_back(std::string(90U, 0x20));
	for (int i = 0; i <= 360; i++)
	{
		int angle = i - 180;
		double func = sin(ToRadians(angle));
		int resolved = int(10.0 - round(func * 10.0));
		if (resolved >= 0 && resolved < 21 && pos <= 42)
		{
			double derivative = cos(ToRadians(angle));
			std::string thisChar = derivative > 0.0 ? "/" : "\\";
			if (lastChar.empty()) lastChar = thisChar;
			if (lastChar != thisChar)
			{
				if (lastChar == "\\") strings.at(prev).replace(pos > 0U ? pos - 1U : pos, pos == 21U ? 3U : 2U, pos == 21U ? "\\ /" : "\\/");
				else strings.at(prev).replace(pos > 0U ? pos - 1U : pos, pos == 21U ? 3U : 2U, pos == 21U ? "/ \\" : "/\\");
				if (pos == 21U) pos++;
				pos++;
			}

			if (prev != resolved) pos++;
			strings.at(resolved).replace(pos > 0 ? pos - 1 : pos, 1, thisChar);
			lastChar = thisChar;
			prev = resolved;
		}
	}

	size_t maxLen = 42U;
	for (size_t i = 0U; i < strings.size(); i++) for (size_t j = 0; j < strings.at(i).length(); j++) if (strings.at(i).at(j) == 0x5C || strings.at(i).at(j) == 0x2F) maxLen = std::max(maxLen, j);
	for (size_t i = 0U; i < strings.size(); i++)
	{
		strings[i] = strings.at(i).substr(0U, maxLen + 1U);
		for (size_t j = 0U; j < strings.at(i).length(); j++)
		{
			if (i == 10U) if (strings.at(i).at(j) == 0x20) strings[i][j] = 0x2D;
			if (i == strings.size() - 1U) if (strings.at(i).at(j) == 0x20) strings[i][j] = 0x5F;
		}

		if (strings.at(i).at(21U) == 0x20 || strings.at(i).at(21U) == 0x5F) strings[i][21U] = 0x7C;
		if (i >= 0U && i <= strings.size() - 1U) strings[i] = strings[i] + " ";
		strings[i][strings.at(i).length() - 1U] = 0x7C;
	}
	std::cout << std::string(10U, 0x20) + std::string(43U, 0x5F) + " " << std::endl;
	for (size_t i = 0U; i < strings.size(); i++) std::cout << " " << (i == 10U ? "x = -pi" : std::string(7U, 0x20)) << " |" << strings.at(i) << (i == 10U ? " x = pi" : "") << std::endl;
	std::cout << SKIPLINE;
}

void drawSinus()
{
	std::vector<std::string> lines;
	for (int i = 0; i < 32; i++)
	{
		if (i == 0) lines.push_back(std::string(6U, 0x20) + std::string(109U, 0x5F));
		else if (i == 16) lines.push_back(" -pi |" + std::string(109U, 0x2D) + "| pi");
		else if (i == 31) lines.push_back(std::string(5U, 0x20) + "|" + std::string(54U, '_') + "|" + std::string(54U, 0x5F) + "|");
		else lines.push_back(std::string(5U, 0x20) + "|" + std::string(54U, 0x20) + "|" + std::string(54U, 0x20) + "|");
	}

	size_t pos = 6U;
	for (double i = -180.0; i <= 180.0; i += 360.0 / 109.0) lines[int(lines.size() / 2 - round(sin(ToRadians((int)i)) * 10.0))][pos++] = '*';
	
	/* If you want to use the tan/ctg or anything else (ctg = 1/tan - USE ONLY THIS FOR IT)
	for (double i = -180.0; i <= 180.0; i += 2.0) // DO NOT USE 1.0 AS A STEP!!!!!!!
	{
		int idx = int(lines.size() / 2 - round(tan(ToRadians((int)i)) * 10.0));
		if (idx < lines.size() && idx != 0) lines[idx][pos++] = '*';
	}*/

	std::cout << std::string(59U, 0x20) << "1.5" << std::endl;
	for (size_t i = 0U; i < lines.size(); i++) std::cout << lines.at(i) << std::endl;
	std::cout << std::string(58U, 0x20) << "-1.5" << std::endl;
}

bool isRoman(std::string value)
{
	std::string chars = "IVXLCDM";

	for (size_t i = 0U; i < value.length(); i++) if (chars.find(value.at(i)) == std::string::npos) return false;
	for (size_t i = 0U; i < chars.length(); i++) if (value.find(std::string(4, chars.at(i))) != std::string::npos || i % 2 == 1 && Safety::Count(value, chars.at(i)) > 1) return false;
	return true;
}

bool isSubtract(std::vector<int>& value, size_t& pos)
{
	if (value.at(pos) < value.at(pos + 1))
	{
		if (std::to_string(value.at(pos)).at(0) == 0x35) return false;
		if (std::to_string(value.at(pos + 1)).length() - std::to_string(value.at(pos)).length() <= 1)
		{
			if (pos > 0) if (abs(value.at(pos - 1)) == abs(value.at(pos))) return false;
			value[pos] *= -1;
			pos++;
		}
		else return false;
	}
	return true;
}

std::string formCorrect(std::string sValue, std::string iValue)
{
	std::string ret = "", chars = "MDCLXVI";
	std::vector<int> parts = { 0, 0, 0, 0 };
	for (size_t i = 0U; i < iValue.length(); i++) parts[4U - iValue.length() + i] = atoi(iValue.substr(i, 1U).c_str());
	for (size_t i = 4U - iValue.length(); i < parts.size(); i++)
	{
		if (parts.at(i) > 0)
		{
			if (parts.at(i) < 4) ret += std::string(parts.at(i), chars.at(i * 2));
			else if (parts.at(i) == 9 && i * 2 - 2 >= 0) ret += std::string(1, chars.at(i * 2)) + std::string(1, chars.at(i * 2 - 2));
			else if (parts.at(i) == 4 && i * 2 - 1 >= 0) ret += std::string(1, chars.at(i * 2)) + std::string(1, chars.at(i * 2 - 1));
			else if (parts.at(i) - 5 >= 0) ret += std::string(1, chars.at(i * 2 - 1)) + std::string(parts.at(i) - 5, chars.at(i * 2));
			else return "undefined";
		}
	}
	return ret;
}

void Translator()
{
	Input->In("Input the 1 string (the roman numbers)", 1U);
	std::string value = BUFFER(0);
	Safety::ToUpper(value);

	if (isRoman(value))
	{
		auto toArabic = [](char num)->int
		{
			std::string chars = "IVXLCDM";
			size_t pos = chars.find(num);

			return (int)pow(10, pos / 2U) * (int)pow(5, pos % 2U);
		};

		std::vector<int> nums;
		for (size_t i = 0U; i < value.length(); i++) nums.push_back(toArabic(value.at(i)));
		for (size_t i = 0U; i < nums.size() - 1U; i++) if (!isSubtract(nums, i)) INCORRECT(Translator);

		int sum = 0;
		for (size_t i = 0U; i < nums.size(); i++) sum += nums.at(i);
		std::string correct = formCorrect(value, std::to_string(sum));
		if (correct != value) std::cout << "\"" << value << "\" is incorrect expression - \"" << correct << "\" is correct" << std::endl;
		std::cout << value << " in roman = " << sum << " in arabic" << SKIPLINE;
	}
	else INCORRECT(Translator);
}

int Generate(int i, int m, int b, int c)
{
	if (i == 0) return 0;
	return (m * Generate(i - 1, m, b, c) + b) % c;
}

void Generate()
{
	Input->In("Input the 4 nums (iteration, m, b, c)", 4U);
	if (Safety::isNumber(BUFFER(0).c_str()) && Safety::isNumber(BUFFER(1).c_str()) && Safety::isNumber(BUFFER(2).c_str()) && Safety::isNumber(BUFFER(3).c_str()))
	{
		int i = atoi(BUFFER(0).c_str()), m = atoi(BUFFER(1).c_str()), b = atoi(BUFFER(2).c_str()), c = atoi(BUFFER(3).c_str());
		if (c != 0) std::cout << "The pseudo-random value is " << Generate(i, m, b, c) << SKIPLINE;
		else INCORRECT(Generate);
	}
	else INCORRECT(Generate);
}

void Matrixes()
{
	int aMatrix[3][4] =
	{
		{ 5, 2, 0, 10 },
		{ 3, 5, 2, 5 },
		{ 20, 0, 0, 0 }
	};

	float bMatrix[4][2] =
	{
		{ 1.2f, 0.5f },
		{ 2.8f, 0.4f },
		{ 5.f, 1.f },
		{ 2.f, 1.5f }
	};

	std::cout << "Table A:" << std::endl;
	std::cout << "	Product  1   2   3   4" << std::endl;
	std::cout << "	Seller" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::string line = std::string(50, ' ');
		line.insert(11, std::to_string(i + 1));
		for (int j = 0; j < 4; j++) line.insert(17 + j * 4, std::to_string(aMatrix[i][j]).c_str());
		std::cout << line << std::endl;
	}

	std::cout << "Table B:" << std::endl;
	std::cout << "	Product    Cost    Comission" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::string line = std::string(50, ' ');
		line.insert(11, std::to_string(i + 1));
		for (int j = 0; j < 2; j++) line.insert(20 + j * 11, std::to_string((int)bMatrix[i][j]).c_str());
		std::cout << line << std::endl;
	}
	
	float cMatrix[3][2]
	{
		{ 0.f, 0.f },
		{ 0.f, 0.f },
		{ 0.f, 0.f }
	};

	int indexes[2][2] = { { 0, 0 }, { 0, 0 } };
	for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 4; k++) cMatrix[i][j] += aMatrix[i][k] * bMatrix[k][j];
	for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++)
	{
		if (cMatrix[i][j] > cMatrix[indexes[j][0]][j]) indexes[j][0] = i;
		else if (cMatrix[i][j] < cMatrix[indexes[j][1]][j]) indexes[j][1] = i;
	}

	float sum[2] = { cMatrix[0][0] + cMatrix[1][0] + cMatrix[2][0], cMatrix[0][1] + cMatrix[1][1] + cMatrix[2][1] };
	std::cout << "1 - The " << indexes[0][0] + 1 << " seller received more money than others" << std::endl <<
		"    The " << indexes[0][1] + 1 << " seller received less money than others" << std::endl <<
		"2 - The " << indexes[1][0] + 1 << " seller received more comission money than others" << std::endl <<
		"    The " << indexes[1][1] + 1 << " seller received less comission money than others" << std::endl <<
		"3 - The general sum of money from the sale is " << sum[0] << std::endl <<
		"4 - The general sum of comission money is " << sum[1] << std::endl <<
		"5 - The general sum of money is " << sum[0] + sum[1] << SKIPLINE;
}

std::string inSystem(int num, int base, int step = 0)
{
	std::string ret;
	while (num)
	{
		ret = std::string(1, g_pData->alphabet.at(num % base)) + ret;
		step++;
		num = int(num / base);
	}
	return ret;
}

std::string inSystemFloat(double num, double base)
{
	std::string ret;
	std::vector<double> values;
	while (abs(num - int(num)) != 0.0)
	{
		for (size_t i = 0; i < values.size(); i++) if (values.at(i) == num * base) return "(" + ret + ")";
		ret += std::string(1, g_pData->alphabet.at(int(num * base)));
		if (ret.length() > 10) return "(~" + ret + ")";
		values.push_back(num * base);
		num = abs(double(num * base) - int(num * base));
	}
	return ret;
}

int fromSystem(std::string value, size_t base)
{
	int ret = 0;
	std::string alphabet = g_pData->alphabet.substr(0U, base);

	if (base == 10) return atoi(value.c_str());
	else for (size_t i = 0; i < value.length(); i++) if (alphabet.find(value.at(abs((int)i - (int)value.length() + 1))) != std::string::npos) ret += alphabet.find(value.at(abs((int)i - (int)value.length() + 1))) * (int)pow(base, i);
	return ret;
}

double fromFloat(std::string value, size_t base)
{
	double ret = 0.0;
	std::string alphabet = g_pData->alphabet.substr(0U, base);

	if (base == 10) return atof(value.c_str()) / pow(10, value.length());
	else for (size_t i = 0; i < value.length(); i++) if (alphabet.find(value.at(i)) != std::string::npos) ret += alphabet.find(value.at(i)) * pow(base, -int(i + 1));
	return ret;
}

bool isSystemIn(std::string value, size_t base)
{
	std::string alphabet = g_pData->alphabet.substr(0U, base);

	for (size_t i = 0; i < value.length(); i++) if (alphabet.find(value.at(i)) == std::string::npos) return false;
	return true;
}

void numSystems()
{
	Input->In("Input the 3 nums (value, current base, new base)", 3U);
	if (Safety::isNumber(BUFFER(1).c_str(), POSITIVE) && Safety::isNumber(BUFFER(2).c_str(), POSITIVE))
	{
		std::string value = BUFFER(0).c_str();
		int oldb = atoi(BUFFER(1).c_str()), newb = atoi(BUFFER(2).c_str()), valid = 0;

		if (clamp(oldb, 2, (int)g_pData->alphabet.length()) == oldb && clamp(newb, 2, (int)g_pData->alphabet.length()) == newb)
		{
			bool isMinus = false;
			if (value.at(0) == 0x2D)
			{
				value = value.substr(1);
				isMinus = true;
			}

			int dots = Safety::Count(value, '.');
			if (dots == 0)
			{
				if (isSystemIn(value, oldb))
				{
					std::cout << (isMinus ? "-" : "") << value << "[" << oldb << "] = " << (isMinus ? "-" : "") << inSystem(fromSystem(value, oldb), newb) << "[" << newb << "]" << SKIPLINE;
					return;
				}
			}
			else if (dots == 1)
			{
				std::string nofloat = value.substr(0, value.find("."));
				std::string floatpart = value.substr(value.find(".") + 1);
				if (isSystemIn(nofloat, oldb) && isSystemIn(floatpart, oldb))
				{
					nofloat = inSystem(fromSystem(nofloat, oldb), newb);
					std::cout << nofloat << fromFloat(floatpart, oldb) << std::endl;
					floatpart = inSystemFloat(fromFloat(floatpart, oldb), (double)newb);
					std::cout << (isMinus ? "-" : "") << value << "[" << oldb << "] = " << (isMinus ? "-" : "") << nofloat << "." << floatpart << "[" << newb << "]" << SKIPLINE;
					return;
				}
			}
		}
	}
	INCORRECT(numSystems);
}

void CHomework4()
{
	new CHomework();
	new CExercise("File", []() { exFile(); });
	new CExercise("Sign", []() { getSign(); });
	new CExercise("Shapes", []() { getSquare(); });
	new CExercise("Flag", []() { drawFlag(); });
	new CExercise("Sinus", []() { drawSinus(); });
	new CExercise("Romane's translator", []() { Translator(); });
	new CExercise("Generator of pseudo-random numbers", []() { Generate(); });
	new CExercise("Multiply of matrixes", []() { Matrixes(); });
	new CExercise("Number systems", []() { numSystems(); });
}
