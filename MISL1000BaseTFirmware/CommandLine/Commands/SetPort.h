#ifndef SETPORT_H
#define SETPORT_H

#include "ICommand.h"
#include "HardwareControl/UIOStream.h"

class SetPort : public ICommand
{
public:
    SetPort();
    ~SetPort();
	
protected:
	//Inherited from ICommand
    bool functionToRun(const KeyValueList &flags, const KeyValueList &parameters);
	void operationSuccess();
	void operationFailed();
    void helpRequested();
};

#endif