#include "CHomework4.h"

int euclidAlg(int a, int b, bool isDiv = true)
{
	if (isDiv)
	{
		if (a != 0 && b != 0)
		{
			if (a > b) return euclidAlg(a % b, b);
			else return euclidAlg(a, b % a);
		}
		return a + b;
	}
	else
	{
		if (a == b) return a;
		else
		{
			if (a > b) return euclidAlg(a - b, b, false);
			else return euclidAlg(a, b - a, false);
		}
	}
}

void euclidAlg()
{
	Input->In("Input the 2 nums to get a greatest common div (a, b)", 2U);
	if (Safety::isNumber(BUFFER(0).c_str(), POSITIVE) && Safety::isNumber(BUFFER(1).c_str(), POSITIVE))
	{
		int a = atoi(BUFFER(0).c_str()), b = atoi(BUFFER(1).c_str());
		std::cout << "A greatest common div (by divs) is " << euclidAlg(a, b) << std::endl;
		std::cout << "A greatest common div (by subtracts) is " << euclidAlg(a, b, false) << SKIPLINE;
	}
	else INCORRECT(euclidAlg);
}

bool isPrime(int num)
{
	for (int i = 2; i < static_cast<int>(sqrt(num)) + 1; i++) if (num % i == 0) return false;
	return true;
}

void solEratosfen()
{
	Input->In("Input the 1 num as a limit of list of prime nums (max)", 1U);
	if (Safety::isNumber(BUFFER(0).c_str(), POSITIVE))
	{
		int limit = atoi(BUFFER(0).c_str());
		for (int i = 2; i <= limit; i++) if (isPrime(i)) std::cout << i << " ";
		std::cout << SKIPLINE;
	}
	else INCORRECT(solEratosfen);
}

void getMinPhrase()
{
	Input->In("Input the line(s) to count a min phrase length (you can use \\n)", 0U, "\\n");

	size_t maximum = 0;
	std::string line, phrase = "", sphrases = "", symbs = ".?!";
	std::vector<std::string> parts, supp;
	std::vector<std::vector<std::string>> phrases(Input->getSize());
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		phrase = "", sphrases = "";
		phrases[i].clear();
		line = BUFFER(i);
		supp = { "" };
		for (size_t j = 0U; j < line.length() - 1; j++) if (symbs.find(line.at(j)) != std::string::npos && symbs.find(line.at(j + 1)) == std::string::npos && line.at(j + 1) != 0x20) line = line.substr(0U, j) + std::string(1U, line.at(j)) + " " + line.substr(j + 1);
		parts = Input->ToParts(line);
		for (size_t j = 0U; j < parts.size(); j++)
		{
			supp[supp.size() - 1] += parts.at(j) + " ";
			if (j != parts.size() - 1 && (parts.at(j).at(parts.at(j).length() - 1U) == 0x21 || parts.at(j).at(parts.at(j).length() - 1U) == 0x2E || parts.at(j).at(parts.at(j).length() - 1U) == 0x3F)) supp.push_back("");
		}

		for (size_t j = 0U; j < supp.size(); j++)
		{
			while (supp.at(j).at(0) == 0x20) supp[j] = supp.at(j).substr(1U);
			while (supp.at(j).at(supp.at(j).length() - 1U) == 0x20) supp[j] = supp.at(j).substr(0U, supp.at(j).length() - 1U);
			if (supp.at(j).length() < phrase.length() || phrase.length() == 0U)
			{
				phrase = supp.at(j);
				if (maximum > phrase.length() || maximum == 0U) maximum = phrase.length();
			}
		}
		for (size_t j = 0U; j < supp.size(); j++) if (supp.at(j).length() == phrase.length())
		{
			sphrases += supp.at(j) + " | ";
			phrases.at(i).push_back(supp.at(j));
		}

		if (Input->getSize() > 1U) std::cout << "The minimal length of phrase on the " << i + 1 << " line is " << phrase.length() << " (" << sphrases.substr(0U, sphrases.length() - 3U) << ")" << std::endl;
		else std::cout << "The minimum length of phrase is " << phrase.length() << " (" << sphrases.substr(0U, sphrases.length() - 3U) << ")" << std::endl;
	}
	if (Input->getSize() > 1U)
	{
		std::string maximums = "";
		for (size_t i = 0U; i < phrases.size(); i++) for (size_t j = 0U; j < phrases.at(i).size(); j++) if (phrases.at(i).at(j).length() == maximum) maximums += phrases.at(i).at(j) + " | ";
		std::cout << "The minimum length of phrase is " << maximum << " (" << maximums.substr(0U, maximums.length() - 3U) << ")" << SKIPLINE;
	}
}

struct STRINGDESC
{
	std::string str = "", desc = "", limits = "";
	size_t limit = 0U;
};

void getWord(bool isMax)
{
	Input->In("Input the line(s) to count a " + (isMax ? std::string("max") : std::string("min")) + " word length (you can use \\n)", 0U, "\\n");

	STRINGDESC min, max, def;
	std::string line, alphabet = g_pData->alphabet + "-'";
	std::vector<std::string> parts;
	std::vector<std::vector<std::string>> words(Input->getSize());
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		min = def, max = def;
		words[i].clear();
		line = BUFFER(i);
		for (size_t j = 0U; j < line.length(); j++) if (alphabet.find(line.at(j)) == std::string::npos && line.at(j) >= 0) line = line.substr(0U, j) + " " + line.substr(j + 1);
		parts = Input->ToParts(line);
		for (size_t j = 0U; j < parts.size(); j++)
		{
			if (parts.at(j).length() > max.str.length())
			{
				max.str = parts.at(j);
				if (max.limit < max.str.length()) max.limit = max.str.length();
			}
			if (parts.at(j).length() < min.str.length() || min.str.length() == 0U)
			{
				min.str = parts.at(j);
				if (min.limit > min.str.length() || min.limit == 0U) min.limit = min.str.length();
			}
		}
		for (size_t j = 0U; j < parts.size(); j++)
		{
			if (parts.at(j).length() == min.str.length()) min.desc += parts.at(j) + ", ";
			if (parts.at(j).length() == max.str.length()) max.desc += parts.at(j) + ", ";
			words.at(i).push_back(parts.at(j));
		}

		if (Input->getSize() > 1U && isMax) std::cout << "The minimal length of word on the " << i + 1 << " line is " << max.str.length() << " (" << max.desc.substr(0U, max.desc.length() - 2U) << ")" << std::endl;
		else if (Input->getSize() > 1U && !isMax) std::cout << "The minimal length of word on the " << i + 1 << " line is " << min.str.length() << " (" << min.desc.substr(0U, min.desc.length() - 2U) << ")" << std::endl;
		else if (isMax) std::cout << "The minimum length of word is " << max.str.length() << " (" << max.desc.substr(0U, max.desc.length() - 2U) << ")" << SKIPLINE;
		else std::cout << "The minimum length of word is " << min.str.length() << " (" << min.desc.substr(0U, min.desc.length() - 2U) << ")" << SKIPLINE;
	}
	if (Input->getSize() > 1U)
	{
		for (size_t i = 0U; i < words.size(); i++)
		{
			for (size_t j = 0U; j < words.at(i).size(); j++)
			{
				if (words.at(i).at(j).length() == min.limit) min.limits += words.at(i).at(j) + ", ";
				if (words.at(i).at(j).length() == max.limit) max.limits += words.at(i).at(j) + ", ";
			}
		}
		if (isMax) std::cout << "The maximum length of word is " << max.limit << " (" << max.limits.substr(0U, max.limits.length() - 2U) << ")" << SKIPLINE;
		else std::cout << "The minimum length of word is " << min.limit << " (" << min.limits.substr(0U, min.limits.length() - 2U) << ")" << SKIPLINE;
	}
}

/*void getMinWord()
{
	Input->In("Input the line(s) to count a min word length (you can use \\n)", 0U, "\\n");

	size_t minimum = 0U;
	std::string line, alphabet = g_pData->alphabet + "-'", word = "", swords = "";
	std::vector<std::string> parts;
	std::vector<std::vector<std::string>> words(Input->getSize());
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		word = "", swords = "";
		words[i].clear();
		line = BUFFER(i);
		for (size_t j = 0U; j < line.length(); j++) if (alphabet.find(line.at(j)) == std::string::npos && line.at(j) >= 0)line = line.substr(0U, j) + " " + line.substr(j + 1);
		parts = Input->ToParts(line);
		for (size_t j = 0U; j < parts.size(); j++) if (parts.at(j).length() < word.length() || word.length() == 0U)
		{
			word = parts.at(j);
			if (minimum > word.length() || minimum == 0U) minimum = word.length();
		}
		for (size_t j = 0U; j < parts.size(); j++) if (parts.at(j).length() == word.length())
		{
			swords += parts.at(j) + ", ";
			words.at(i).push_back(parts.at(j));
		}

		if (Input->getSize() > 1U) std::cout << "The minimal length of word on the " << i + 1 << " line is " << word.length() << " (" << swords.substr(0U, swords.length() - 2U) << ")" << std::endl;
		else std::cout << "The minimum length of word is " << word.length() << " (" << swords.substr(0U, swords.length() - 2U) << ")" << SKIPLINE;
	}
	if (Input->getSize() > 1U)
	{
		std::string minimums = "";
		for (size_t i = 0U; i < words.size(); i++) for (size_t j = 0U; j < words.at(i).size(); j++) if (words.at(i).at(j).length() == minimum) minimums += words.at(i).at(j) + ", ";
		std::cout << "The minimum length of word is " << minimum << " (" << minimums.substr(0U, minimums.length() - 2U) << ")" << SKIPLINE;
	}
}*/

/*void getMaxWord()
{
	Input->In("Input the line(s) to count a max word length (you can use \\n)", 0U, "\\n");

	size_t maximum = 0;
	std::string line, alphabet = g_pData->alphabet + "-'", word = "", swords = "";
	std::vector<std::string> parts;
	std::vector<std::vector<std::string>> words(Input->getSize());
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		word = "", swords = "";
		words[i].clear();
		line = BUFFER(i);
		for (size_t j = 0U; j < line.length(); j++) if (alphabet.find(line.at(j)) == std::string::npos && line.at(j) >= 0) line = line.substr(0U, j) + " " + line.substr(j + 1);
		parts = Input->ToParts(line);
		for (size_t j = 0U; j < parts.size(); j++) if (parts.at(j).length() > word.length())
		{
			word = parts.at(j);
			if (maximum < word.length()) maximum = word.length();
		}
		for (size_t j = 0U; j < parts.size(); j++) if (parts.at(j).length() == word.length())
		{
			swords += parts.at(j) + ", ";
			words.at(i).push_back(parts.at(j));
		}

		if (Input->getSize() > 1U) std::cout << "The maximal length of word on the " << i + 1 << " line is " << word.length() << " (" << swords.substr(0U, swords.length() - 2U) << ")" << std::endl;
		else std::cout << "The maximum length of word is " << word.length() << " (" << swords.substr(0U, swords.length() - 2U) << ")" << SKIPLINE;
	}
	if (Input->getSize() > 1U)
	{
		std::string maximums = "";
		for (size_t i = 0U; i < words.size(); i++) for (size_t j = 0U; j < words.at(i).size(); j++) if (words.at(i).at(j).length() == maximum) maximums += words.at(i).at(j) + ", ";
		std::cout << "The maximum length of word is " << maximum << " (" << maximums.substr(0U, maximums.length() - 2U) << ")" << SKIPLINE;
	}
}*/

void getMaxPhrase()
{
	Input->In("Input the line(s) to count a max phrase length (you can use \\n)", 0U, "\\n");

	size_t maximum = 0;
	std::string line, phrase = "", sphrases = "";
	std::vector<std::string> parts, supp;
	std::vector<std::vector<std::string>> phrases(Input->getSize());
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		phrase = "", sphrases = "";
		phrases[i].clear();
		line = BUFFER(i);
		supp = { "" };
		parts = Input->ToParts(BUFFER(i));
		for (size_t j = 0U; j < parts.size(); j++)
		{
			supp[supp.size() - 1] += parts.at(j) + " ";
			if (j != parts.size() - 1 && (parts.at(j).at(parts.at(j).length() - 1U) == 0x21 || parts.at(j).at(parts.at(j).length() - 1U) == 0x2E || parts.at(j).at(parts.at(j).length() - 1U) == 0x3F)) supp.push_back("");
		}

		for (size_t j = 0U; j < supp.size(); j++)
		{
			while (supp.at(j).at(0) == 0x20) supp[j] = supp.at(j).substr(1U);
			while (supp.at(j).at(supp.at(j).length() - 1U) == 0x20) supp[j] = supp.at(j).substr(0U, supp.at(j).length() - 1U);
			if (supp.at(j).length() > phrase.length())
			{
				phrase = supp.at(j);
				if (maximum < phrase.length()) maximum = phrase.length();
			}
		}
		for (size_t j = 0U; j < supp.size(); j++) if (supp.at(j).length() == phrase.length())
		{
			sphrases += supp.at(j) + " | ";
			phrases.at(i).push_back(supp.at(j));
		}

		if (Input->getSize() > 1U) std::cout << "The maximal length of phrase on the " << i + 1 << " line is " << phrase.length() << " (" << sphrases.substr(0U, sphrases.length() - 3U) << ")" << std::endl;
		else std::cout << "The maximum length of phrase is " << phrase.length() << " (" << sphrases.substr(0U, sphrases.length() - 3U) << ")" << std::endl;
	}
	if (Input->getSize() > 1U)
	{
		std::string maximums = "";
		for (size_t i = 0U; i < phrases.size(); i++) for (size_t j = 0U; j < phrases.at(i).size(); j++) if (phrases.at(i).at(j).length() == maximum) maximums += phrases.at(i).at(j) + " | ";
		std::cout << "The maximum length of phrase is " << maximum << " (" << maximums.substr(0U, maximums.length() - 3U) << ")" << SKIPLINE;
	}
}

void linesToPhrase()
{
	Input->In("Input the line(s) to separate by sentences (you can use \\n)", 0U, "\\n");

	std::string line;
	std::vector<std::string> parts, supp;
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		line = BUFFER(i);
		parts = Input->ToParts(BUFFER(i));
		supp = { "" };
		for (size_t j = 0U; j < parts.size(); j++)
		{
			supp[supp.size() - 1] += parts.at(j) + " ";
			if (j != parts.size() - 1 && (parts.at(j).at(parts.at(j).length() - 1U) == 0x21 || parts.at(j).at(parts.at(j).length() - 1U) == 0x2E || parts.at(j).at(parts.at(j).length() - 1U) == 0x3F)) supp.push_back("");
		}
		
		for (size_t j = 0U; j < supp.size(); j++)
		{
			while (supp.at(j).at(0) == 0x20) supp[j] = supp.at(j).substr(1U);
			while (supp.at(j).at(supp.at(j).length() - 1U) == 0x20) supp[j] = supp.at(j).substr(0U, supp.at(j).length() - 1U);
			std::cout << supp.at(j) << std::endl;
		}
	}
	std::cout << std::endl;
}

void rowsToCols()
{
	Input->In("Input the line(s) to transform to word's columns (you can use \\n)", 0U, "\\n");
	
	std::vector<std::string> parts;
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		parts = Input->ToParts(BUFFER(i));
		for (size_t j = 0U; j < parts.size(); j++) std::cout << parts.at(j) << std::endl;
	}
	std::cout << std::endl;
}

void replaceEscape()
{
	Input->In("Input the 1 char as the separator", 1U);
	std::string sep = BUFFER(0);
	if (sep.length() != 1) INCORRECT(replaceEscape);

	Input->In("Input a line(s) for separate (you can use \\n)", 0U, "\\n");

	std::vector<std::string> parts;
	for (size_t i = 0U; i < Input->getSize(); i++)
	{
		parts = Input->ToParts(BUFFER(i), sep);
		for (size_t j = 0U; j < parts.size(); j++) std::cout << "\"" << parts.at(j) << "\" ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void handleSubEx(int subEx)
{
	std::vector<std::vector<std::function<void()>>> fn =
	{
		{ []() { replaceEscape(); }, []() { rowsToCols(); } , []() { linesToPhrase(); }, []() { getWord(true); }, []() { getMaxPhrase(); }, []() { getWord(false); }, []() { getMinPhrase(); }, []() { return; }, []() { return; }, []() { return; }},
		{ []() { return; }, []() { return; } , []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }},
		{ []() { return; }, []() { return; } , []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }},
		{ []() { return; }, []() { return; } , []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }, []() { return; }}
	};
	fn.at(static_cast<size_t>(static_cast<int>(subEx / 10))).at(static_cast<size_t>(subEx - static_cast<int>(subEx / 10) * 10))();
}

void handleFiles()
{
	Input->In("Select the number of sub-exercise", 1U);
	if (Safety::isNumber(BUFFER(0).c_str(), POSITIVE))
	{
		int subEx = atoi(BUFFER(0).c_str());
		if (subEx <= 40)
		{
			handleSubEx(subEx - 1);
			return;
		}
	}
	INCORRECT(handleFiles);
}

void CHomework5()
{
	new CHomework();
	new CExercise("Algorithm of Euclid", []() { euclidAlg(); });
	new CExercise("Solution of Eratosfen", []() { solEratosfen(); });
	new CExercise("Handle a text files", []() { handleFiles(); });
}