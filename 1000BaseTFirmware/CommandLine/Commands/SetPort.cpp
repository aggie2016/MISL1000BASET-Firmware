#include "SetPort.h"

SetPort::SetPort()
{
	KeyValueList flags;
	flags.push_back(std::make_tuple("\\h", "return as hex"));
	flags.push_back(std::make_tuple("\\i", "return as integer"));

	KeyValueList parameters;
	parameters.push_back(std::make_tuple("start address", "the address to start reading from"));
	parameters.push_back(std::make_tuple("end address", "the address to stop reading when reached"));

	setName("Read Register");
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

bool SetPort::processCommand()
{
	printf("Running the read register command\n");
	printf("Received the following arguments:");
	return true;
}
