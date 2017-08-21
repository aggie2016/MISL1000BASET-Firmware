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

ICommandResult ICommand::run(std::string cli_input)
{
	if (!parseCommandParameters(cli_input))
	{
		return ICommandResult::ParseFailed;
	}

	//Call the implementation of this command's action created by deriving from this class
	if (!processCommand())
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
    

	return true;
}
