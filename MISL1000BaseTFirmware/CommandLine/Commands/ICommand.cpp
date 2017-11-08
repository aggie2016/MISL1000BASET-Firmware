#include "ICommand.h"
#include "SystemObjects/HelperFunctions.h"

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
    //Quickly check to see if help dialog was requested.
    if (cli_input.find("--help") != std::string::npos)
    {
        helpRequested();
        return ICommandResult::HelpDialogRequested;
    }
    
    KeyValueList parameters = parseCommandParameters(cli_input);
	if (parameters.size() != m_parameters.size())
	{
		return ICommandResult::ParseFailed;
	}
    
    KeyValueList flags = parseCommandFlags(cli_input);

	//Call the implementation of this command's action created by deriving from this class
    if (!functionToRun(parameters, flags))
	{
		operationFailed();
		return ICommandResult::CommandFailed;
	}

	operationSuccess();
	return ICommandResult::Success;
}

KeyValueList ICommand::parseCommandParameters(std::string cli_input)
{
	//Command will be <command-name> <parameters> <flags (\[A-Z | a-z]){1,}> 
    KeyValueList parsedParameters;
        
    //Ingest the command name
    std::size_t cursorIndex = cli_input.find(m_commandName);
    if (cursorIndex != std::string::npos)
    {
        //Place the cursor at the index of the first character AFTER the command string
        cursorIndex += m_commandName.size();        
    }
    
    // Find all parameters up to the first flag
    std::size_t endOfParametersIndex = cli_input.find('-', cursorIndex);
    
    //Create a substring that contains all characters up to the first flag ('-')
    std::string parameterString = cli_input.substr(cursorIndex, ((endOfParametersIndex - cursorIndex) - 1));
    
    //Create tokenized parameters
    auto tokens = HelperFunctions::splitString(parameterString);
    
    //Match parameters with their friendly names
    for (int i = 0; i < tokens.size() && i < m_parameters.size(); i++)
    {
        std::string parameterName = std::get<0>(m_parameters[i]);
        std::string tokenValue = tokens[i];
        parsedParameters.push_back(std::make_tuple(parameterName, tokenValue));
    }

	//Every parameter is accounted for.
    return parsedParameters;
}

KeyValueList ICommand::parseCommandFlags(std::string cli_input)
{
	//Command will be <command-name> <parameters> <flags (\[A-Z | a-z]){1,}> 
    KeyValueList parsedFlags;
    
    //Ingest the command name
    std::size_t cursorIndex = cli_input.find(m_commandName);
    if (cursorIndex != std::string::npos)
    {
        //Place the cursor at the index of the first character AFTER the command string
        cursorIndex += m_commandName.size();        
    }
    
    for (KeyValuePair flag : m_flags)
    {
        std::size_t flagStartIndex = cli_input.find(std::get<0>(flag), cursorIndex);
        
        if (flagStartIndex == std::string::npos)
        {
            //Flag not found
            continue;
        }
        
        //Ingest the flag (we don't need it)
        flagStartIndex += std::get<0>(flag).size();
        
        //Find the value associated with this flag
        flagStartIndex = cli_input.find_first_not_of(' ', flagStartIndex);
        
        if (flagStartIndex == std::string::npos)
        {
            //Flag value not found
            continue;
        }
        
        //Find the end of this flag value
        size_t endIndex = cli_input.find_first_of(' ', flagStartIndex);
        
        std::string flagValue = cli_input.substr(flagStartIndex, ((endIndex - flagStartIndex) + 1));
        parsedFlags.push_back(std::make_tuple(std::get<0>(flag), flagValue));
    }
    
	//Every parameter is accounted for.
    return parsedFlags;
}

bool ICommand::sortFlagIndexes(const std::tuple<int, int> &a, const std::tuple<int, int> &b)
{
	int indexA = std::get<0>(a);
	int indexB = std::get<0>(b);
	return indexA < indexB;
}