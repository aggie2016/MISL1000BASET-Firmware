/*
 * BlinkLEDTask.h
 *
 *  Created on: Mar 28, 2015
 *      Author: akobyljanec
 */

#ifndef BLINKLEDTASK_H_
#define BLINKLEDTASK_H_


#include <driverlib/rom.h>
#include "HardwareControl/GPIOPin.h"
#include "HardwareControl/ITask.h"

class BlinkLEDTask : public ITask
{
public:
    BlinkLEDTask();
    ~BlinkLEDTask();
	void functionToRun();
};

#endif

