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

		std::string commandToSearch;
		
		auto commandParts = HelperFunctions::splitString(stringReceived);
		if (commandParts.size())
		{
			commandToSearch = commandParts[0];
		}
		
		std::vector<ICommand*>::iterator commandFound = std::find_if(m_commands.begin(), m_commands.end(), 
			[&commandToSearch](ICommand* item) 
			{ 
				return item->name() == commandToSearch; 
			});
		
		if (commandFound != m_commands.end())
		{
			switch ((*commandFound)->run(stringReceived))
			{
			case ICommandResult::Success:
				MISL::ucout << MISL::endl << "Function success";
				break;
			case ICommandResult::ParseFailed:
    			MISL::ucout << MISL::endl << "Failed to parse command-line input to function: " << m_commands[0]->name() << MISL::endl;
    			MISL::ucout << "Type --help after a command to get detailed help on its use..." << MISL::endl;
				break;
			case ICommandResult::CommandFailed:
				MISL::ucout << MISL::endl << "Execution of command failed: " << m_commands[0]->name();
				break;
			default:
    			break;
			}
		}
		else
		{
			MISL::ucout << "Invalid command entered" << MISL::endl;
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