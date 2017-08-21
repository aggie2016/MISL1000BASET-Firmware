#include "CLIInterpreterTask.h"



CLIInterpreterTask::CLIInterpreterTask()
	: ITask("CLI Interpreter Task", 2000, 3)
{
}


CLIInterpreterTask::~CLIInterpreterTask()
{
}

void CLIInterpreterTask::functionToRun()
{
	std::string stringReceived;
	while (true)
	{
		MISL::ucout << "MISL>";		
		MISL::ucin >> stringReceived;

		switch (m_commands[0]->run(stringReceived))
		{
		case ICommandResult::Success:
			MISL::ucout << MISL::endl << "Function success";
			break;
		case ICommandResult::ParseFailed:
			MISL::ucout << MISL::endl << "Failed to parse command-line input to function: " << m_commands[0]->name();
			break;
		case ICommandResult::CommandFailed:
			MISL::ucout << MISL::endl << "Execution of command failed: " << m_commands[0]->name();
			break;
		}
		
		MISL::ucout << MISL::endl;
		
		vTaskDelay(100 / portTICK_PERIOD_MS);						
	}
}

CLIInterpreterTask *CLIInterpreterTask::registerCommand(ICommand *command)
{
	m_commands.push_back(command);
	return this;
}