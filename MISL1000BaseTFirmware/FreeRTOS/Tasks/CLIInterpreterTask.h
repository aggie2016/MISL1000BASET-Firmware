/*
 * BlinkLEDTask.h
 *
 *  Created on: Mar 28, 2015
 *      Author: akobyljanec
 */

#ifndef CLIINTERTPRETERTASK_H_
#define CLIINTERTPRETERTASK_H_

#include <algorithm>
#include <string>
#include <vector>
#include "HardwareControl/UIOStream.h"
#include "HardwareControl/ITask.h"
#include "CommandLine/Commands/ICommand.h"
#include "SystemObjects/HelperFunctions.h"

class CLIInterpreterTask : public ITask
{
public:
	CLIInterpreterTask();
	~CLIInterpreterTask();
	void functionToRun();
	CLIInterpreterTask *registerCommand(ICommand *command);

private:
	std::vector<ICommand*> m_commands;
	
};

#endif //CLIInterpreterTask.h
