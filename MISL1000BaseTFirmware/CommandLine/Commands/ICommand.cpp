#include "ICommand.h"

ICommand::~ICommand()
{
}

void ICommand::setName(std::string name)
{
	m_commandName = name;
}

std::string ICommand::name()
{
	return m_commandName;
}

void ICommand::setDescription(std::string description)
{
	m_description = description;
}

std::string ICommand::description()
{
	return m_description;
}

void ICommand::setCommandFlags(KeyValueList flags)
{
	m_flags = flags;
}

KeyValueList ICommand::commandFlags()
{
	return m_flags;
}

void ICommand::setCommandParameters(KeyValueList parameters)
{
	m_parameters = parameters;
}

KeyValueList ICommand::commandParameters()
{
	return m_parameters;
}

std::vector<std::string> ICommand::parsedCommandFlags()
{
	return m_parsedFlags;
}

std::vector<std::string> ICommand::parsedCommandParameters()
{
	return m_parsedParameters;
}

ICommandResult ICommand::run(std::string cli_input)
{
	if (!parseCommandParameters(cli_input))
	{
		return ICommandResult::ParseFailed;
	}

	//Call the implementation of this command's action created by deriving from this class
	if (!functionToRun())
	{
		operationFailed();
		return ICommandResult::CommandFailed;
	}

	operationSuccess();
	return ICommandResult::Success;
}

bool ICommand::parseCommandParameters(std::string cli_input)
{
	//Command will be <command-name> <flags (\[A-Z | a-z]){1,}> <parameters>
 
	std::vector<std::tuple<int, int>> flagRanges;
	
	//Clear all past values
	m_parsedFlags.clear();
	m_parsedParameters.clear();
	
	
	//Check for all flags (if any)
	for (KeyValuePair flag : m_flags)
	{
		int startIndex = 0;
		std::string flagName = std::get<0>(flag);
		startIndex = cli_input.find(flagName, 0);
		
		if (startIndex != std::string::npos)
		{
			m_parsedFlags.push_back(flagName);
			flagRanges.push_back(std::make_tuple(startIndex, startIndex + flagName.size()));	
		}
	}
	

	std::sort(flagRanges.begin(), flagRanges.end(), sortFlagIndexes);		
	int cursor = m_commandName.size();
				
	//Get all characters up to the first flag if possible
	if (flagRanges.size() > 0)
	{
		std::string parameter = (cli_input.substr(cursor, std::get<0>(flagRanges[0]) - cursor));
		//Remove spaces (if any) to get just the parameter
		parameter.erase(std::remove_if(parameter.begin(), parameter.end(), isspace), parameter.end());
		if (parameter.size() > 0)
		{
			m_parsedParameters.push_back(parameter);
		}
		cursor = std::get<1>(flagRanges[0]);
	}
		
	//Seach for parameters inside the range of the flags 
	for (int i = 0; i < flagRanges.size(); i++)
	{
		if (flagRanges.size() > (i + 1))
		{
			//Flag found somewhere in the middle of the command string
			std::string parameter = (cli_input.substr(std::get<1>(flagRanges[i]), std::get<0>(flagRanges[i + 1]) - std::get<1>(flagRanges[i])));
			//Remove spaces (if any) to get just the parameter
			parameter.erase(std::remove_if(parameter.begin(), parameter.end(), isspace), parameter.end());
			if (parameter.size() > 0)
			{
				m_parsedParameters.push_back(parameter);
			}
		}
		else
		{
			//Flag found at the end of the cli string
			std::string parameter = (cli_input.substr(std::get<1>(flagRanges[i]), cli_input.size() - std::get<1>(flagRanges[i])));
			//Remove spaces (if any) to get just the parameter
			parameter.erase(std::remove_if(parameter.begin(), parameter.end(), isspace), parameter.end());
			if (parameter.size() > 0)
			{
				m_parsedParameters.push_back(parameter);
			}
		}
	}
	
	if (m_parsedParameters.size() != m_parameters.size())
	{
		//We failed to find some of the required parameters
		return false;
	}
	
	//Every parameter is accounted for.
	return true;
}

bool ICommand::sortFlagIndexes(const std::tuple<int, int> &a, const std::tuple<int, int> &b)
{
	int indexA = std::get<0>(a);
	int indexB = std::get<0>(b);
	return indexA < indexB;
}