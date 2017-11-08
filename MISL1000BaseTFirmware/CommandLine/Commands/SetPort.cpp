#include "SetPort.h"

SetPort::SetPort()
{
	KeyValueList flags;
	flags.push_back(std::make_tuple("-state", "state for this port [on | off]"));
    flags.push_back(std::make_tuple("-speed", "set speed in Mbps [0-1000]"));
    flags.push_back(std::make_tuple("-state", "state for this port [on | off]"));    

	KeyValueList parameters;
	parameters.push_back(std::make_tuple("port number", "port number to modify [0-5]"));

	setName("set-port");
	setDescription("Configures port-based settings for the integrated KSZ9897R ethernet controller.");
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

void SetPort::helpRequested()
{
    MISL::ucout << "Help for command [ " << name() << " ]:" << MISL::endl;
    MISL::ucout << "\tSyntax: " << name() << " <port-number [1-5]>" << MISL::endl;
    MISL::ucout << "\tOptions: " << MISL::endl;
    for (KeyValuePair pair : commandFlags())
    {
        MISL::ucout << "\t\t" << std::get<0>(pair) << "  " << std::get<1>(pair) << MISL::endl;
    }
}

bool SetPort::functionToRun(const KeyValueList &parameters, const KeyValueList &flags)
{
	int count = 0;
	
	MISL::ucout << "Running the read register command" << MISL::endl;
	MISL::ucout << "Received the following arguments: " << MISL::endl;
	MISL::ucout << "FLAGS:" << MISL::endl;
	
    for (KeyValuePair flag : flags)
	{
		MISL::ucout << "\t[" << count++ << "] FLAG: " << std::get<0>(flag) << " | VALUE: " << std::get<1>(flag) << MISL::endl;
	}
    if (!flags.size())
	{
		MISL::ucout << "==== NO FLAGS PARSED ====";
	}
	
	count = 0;
	MISL::ucout << MISL::endl << "PARAMETERS:" << MISL::endl;
	
    for (KeyValuePair parameter : parameters)
	{
    	MISL::ucout << "\t[" << count++ << "] PARAMETER: " << std::get<0>(parameter) << " | VALUE: " << std::get<1>(parameter) << MISL::endl;
	}
	
	
	return true;
}
