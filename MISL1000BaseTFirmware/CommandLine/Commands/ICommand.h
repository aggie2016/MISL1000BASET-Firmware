#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <algorithm>
#include <string>
#include <vector>
#include <tuple>

typedef std::vector<std::tuple<std::string, std::string>> KeyValueList;
typedef std::tuple<std::string, std::string> KeyValuePair;

enum class ICommandResult {
	Success,
	ParseFailed,
	CommandFailed
};


/*! \class ICommand.h
 *	\brief Interface the encapsulates the basic functionality of a cli command
 *
 *
 *
 */
class ICommand
{
public:
	ICommand() {};
	virtual ~ICommand();

	void setName(std::string name);
	std::string name();
	void setDescription(std::string description);
	std::string description();
	void setCommandFlags(KeyValueList flags);
	KeyValueList commandFlags();
	void setCommandParameters(KeyValueList parameters);
	KeyValueList commandParameters();
	
	std::vector<std::string> parsedCommandFlags();
	std::vector<std::string> parsedCommandParameters();

	ICommandResult run(std::string cli_input);

protected:
	//Pure virtual functions for execution and success/failure of a command
	virtual bool functionToRun() = 0;
	virtual void operationSuccess() = 0;
	virtual void operationFailed() = 0;

private:
	std::string m_commandName;
	std::string m_description;
	KeyValueList m_flags;
	KeyValueList m_parameters;
	std::vector<std::string> m_parsedFlags;
	std::vector<std::string> m_parsedParameters;
	bool parseCommandParameters(std::string cli_input);
	static bool sortFlagIndexes(const std::tuple<int, int> &a, const std::tuple<int, int> &b);
};

#endif // !ICOMMAND_H

