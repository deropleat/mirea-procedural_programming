#include "safedata.h"

bool Safety::isNumber(std::string value, int type)
{
	if (value.length() < 1U) return false;

	int numCounts = 0;
	for (size_t i = 0U; i < value.length(); i++) if (value.at(i) >= 0x30 && value.at(i) <= 0x39) numCounts++;

	if (value.at(0U) == 0x2D) numCounts++;
	if (numCounts == value.length())
	{
		int parsed = atoi(value.c_str());
		return type == POSITIVE && parsed > 0 || type == NEGATIVE && parsed < 0 || type == ISNULL && parsed == 0 || type == ISPLUS && parsed >= 0 || type == ISMINUS && parsed <= 0 || type == ANY;
	}

	return false;
}

bool Safety::isFloat(std::string value, int type)
{
	if (value.length() < 1U) return false;

	size_t numCounts = 0U;
	int dot = Count(value, 0x2E);
	
	switch (dot)
	{
	case 0: return isNumber(value, type);
	case 1: return isNumber(value.substr(0U, value.find(".")), type) && isNumber(value.substr(value.find(".") + 1U), ISPLUS);
	}

	return false;
}

bool Safety::isBool(std::string value)
{
	if (value.length() < 1U) return false;

	ToLower(value);
	std::vector<std::string> values = { "0", "false", "true" };

	for (size_t i = 0U; i < values.size(); i++) if (value == values.at(i)) return true;
	if (isFloat(value)) return true;

	return false;
}

bool Safety::toBool(std::string value)
{
	ToLower(value);
	if (value == "0" || value == "false") return false;
	return true;
}

void Safety::ToLower(std::string& value)
{
	for (size_t i = 0U; i < value.length(); i++) value[i] = std::tolower(value[i]);
}

void Safety::ToUpper(std::string& value)
{
	for (size_t i = 0U; i < value.length(); i++) value[i] = std::toupper(value[i]);
}

int Safety::Count(std::string value, char symbol)
{
	int collected = 0;
	for (size_t i = 0U; i < value.length(); i++) if (value.at(i) == symbol) collected++;
	return collected;
}