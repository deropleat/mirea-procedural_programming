#pragma once

#include "main.h"

enum NumberType
{
	ANY = 0,
	POSITIVE,
	NEGATIVE,
	ISPLUS,
	ISMINUS,
	ISNULL
};

namespace Safety
{
	bool isNumber(std::string value, int type = ANY);
	bool isFloat(std::string value, int type = ANY);
	bool isBool(std::string value);
	bool toBool(std::string value);
	void ToLower(std::string& value);
	void ToUpper(std::string& value);
	int Count(std::string value, char symbol);
	
	template<typename t>
	std::string SafeNumber(t value, size_t length = 0U)
	{
		std::string nVal = std::to_string(value);
		std::string ret = nVal.substr(0U, nVal.find(".")), floatpart = nVal.substr(nVal.find(".") + 1U);
		
		for (size_t i = 0U; i < floatpart.length(); i++)
		{
			bool isNull = true;
			std::string subPart = floatpart.substr(i);	
			for (size_t j = 0U; j < subPart.length(); j++)
			{
				if (subPart.at(j) != 0x30)
				{
					isNull = false;
					break;
				}
			}
			if (isNull)
			{
				floatpart = floatpart.substr(0U, i);
				break;
			}
		}

		if (floatpart.length() > 0U)
		{
			if (length == 0U || floatpart.length() < length) return ret + "." + floatpart;
			else return ret + "." + floatpart.substr(0U, length);
		}
		return ret;
	}


	template<typename t>
	bool isTriangle(t a, t b, t c)
	{
		return a + b > c && a + c > b && b + c > a;
	}
}