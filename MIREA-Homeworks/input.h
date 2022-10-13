#pragma once

#include "main.h"

class CInput
{
public:
	void In(std::string cMsg = "", size_t iArgs = 0U, std::string cSeparator = " ");
	std::vector<std::string> ToParts(std::string cArgs, std::string cSeparator = " ");

	std::string getBuffer(size_t pos = 0U)
	{
		if (pos < buffer.size()) return buffer.at(pos);
		else return "0";
	}

	size_t getSize()
	{
		return buffer.size();
	}

private:
	void bufferPush(std::string cMsg, std::string cSeparator = " ");

	std::vector<std::string> buffer;

}; extern CInput* Input;