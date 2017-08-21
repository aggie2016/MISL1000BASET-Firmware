#include "SetPort.h"

SetPort::SetPort()
{
	KeyValueList flags;
	flags.push_back(std::make_tuple("-h", "return as hex"));
	flags.push_back(std::make_tuple("-i", "return as integer"));

	KeyValueList parameters;
	parameters.push_back(std::make_tuple("start address", "the address to start reading from"));
	parameters.push_back(std::make_tuple("end address", "the address to stop reading when reached"));

	setName("set-port");
	setDescription("reads a register from the system");
	setCommandFlags(flags);
	setCommandParameters(parameters);
}

SetPort::~SetPort()
{
}

void SetPort::operationSuccess()
{
}

void SetPort::operationFailed()
{
}

bool SetPort::functionToRun()
{
	int count = 0;
	
	MISL::ucout << "Running the read register command" << MISL::endl;
	MISL::ucout << "Received the following arguments: " << MISL::endl;
	MISL::ucout << "FLAGS:" << MISL::endl;
	
	for (std::string flag : parsedCommandFlags())
	{
		MISL::ucout << "\t[" << count++ << "] " << flag << MISL::endl;
	}
	
	count = 0;
	MISL::ucout << MISL::endl << "PARAMETERS:" << MISL::endl;
	
	for (std::string parameter : parsedCommandParameters())
	{
		MISL::ucout << "\t[" << count++ << "] " << parameter << MISL::endl;
	}
	
	
	return true;
}
