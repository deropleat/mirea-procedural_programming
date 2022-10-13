#include "input.h"

CInput* Input = new CInput;

std::vector<std::string> CInput::ToParts(std::string cArgs, std::string cSeparator)
{
	std::vector<std::string> ret;
	while (cArgs.find(cSeparator) != std::string::npos)
	{
		ret.push_back(cArgs.substr(0U, cArgs.find(cSeparator)));
		cArgs = cArgs.substr(cArgs.find(cSeparator) + cSeparator.length());
	}
	if (cArgs.length() > 0U) ret.push_back(cArgs);

	return ret;
}

void CInput::bufferPush(std::string cMsg, std::string cSeparator)
{
	if (cMsg.length() > 0U) std::cout << cMsg << ": ";
	std::string line;
	while (line.empty()) std::getline(std::cin, line);
	while (line.find(cSeparator) != std::string::npos)
	{
		buffer.push_back(line.substr(0U, line.find(cSeparator)));
		line = line.substr(line.find(cSeparator) + cSeparator.length());
	}
	if (line.length() > 0) buffer.push_back(line);
}

void CInput::In(std::string cMsg, size_t iArgs, std::string cSeparator)
{
	if (cSeparator.length() == 1 || cSeparator == "\\n")
	{
		buffer.clear();
		bufferPush(cMsg, cSeparator);
		while (buffer.size() > iArgs && iArgs > 0U) buffer.erase(buffer.begin() + iArgs);
		while (buffer.size() < iArgs) bufferPush("You missed " + std::to_string(iArgs - buffer.size()) + " argument" + (iArgs - buffer.size() != 1 ? "s" : "") + " (only missed arguments)", cSeparator);
	}
	else std::cout << "Incorrect separator" << SKIPLINE;
}