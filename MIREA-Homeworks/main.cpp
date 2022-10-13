#include "main.h"

int main()
{
	SetupHomeworks();
	std::string cmd;
	size_t homework, exercise;
	while (true)
	{
		Input->In("Select the number of homework (or exit or shorted x-y)", 1U);
		cmd = BUFFER(0);
		if (cmd == "0") SENDERROR("Incorrect data", 0);
		if (cmd == "exit") break;

		if (cmd.at(0) == 0x2D) SENDERROR("Incorrect data", 1);
		if (Safety::Count(cmd, 0x2D) <= 1)
		{
			if (cmd.find("-") == std::string::npos)
			{
				if (Safety::isNumber(cmd, POSITIVE) && clamp(atoi(cmd.c_str()), 1, int(g_pData->homeworks.size())) == atoi(cmd.c_str())) homework = static_cast<size_t>(atoi(cmd.c_str()) - 1);
				else SENDERROR("Incorrect number of homework", 2);

				for (size_t i = 0U; i < g_pData->homeworks.at(homework)->exercises.size(); i++) std::cout << i + 1 << ". " << g_pData->homeworks.at(homework)->exercises.at(i)->exName << std::endl;
				Input->In("Select the number of exercise", 1U);
				cmd = BUFFER(0);

				if (Safety::isNumber(cmd, POSITIVE) && clamp(atoi(cmd.c_str()), 1, int(g_pData->homeworks.at(homework)->exercises.size())) == atoi(cmd.c_str())) exercise = static_cast<size_t>(atoi(cmd.c_str()) - 1);
				else SENDERROR("Incorrect number of exercise", 3);
			}
			else
			{
				if (cmd.length() >= 3 && cmd.at(0) != 0x2D)
				{
					std::vector<std::string> works = { cmd.substr(0, cmd.find("-")), cmd.substr(cmd.find("-") + 1) };
					if (Safety::isNumber(works.at(0), POSITIVE) && clamp(atoi(works.at(0).c_str()), 1, int(g_pData->homeworks.size())) == atoi(works.at(0).c_str()))
					{
						homework = static_cast<size_t>(atoi(works.at(0).c_str()) - 1);
						if (Safety::isNumber(works.at(1), POSITIVE) && clamp(atoi(works.at(1).c_str()), 1, int(g_pData->homeworks.at(homework)->exercises.size())) == atoi(works.at(1).c_str())) exercise = static_cast<size_t>(atoi(works.at(1).c_str()) - 1);
						else SENDERROR("Incorrect number of exercise", 3);
					}
					else SENDERROR("Incorrect number of homework", 2);
				}
				else SENDERROR("Incorrect short-link", 4);
			}
			g_pData->homeworks.at(homework)->exercises.at(exercise)->Run();
		}
		else SENDERROR("Incorrect data", 1);
	}
	return 0;
}