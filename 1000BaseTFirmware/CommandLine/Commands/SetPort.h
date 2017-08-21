#ifndef SETPORT_H
#define SETPORT_H

#include "ICommand.h"

class SetPort : public ICommand
{
public:
    SetPort();
    ~SetPort();
	
protected:
	//Inherited from ICommand
	bool processCommand();
	void operationSuccess();
	void operationFailed();

};

#endif