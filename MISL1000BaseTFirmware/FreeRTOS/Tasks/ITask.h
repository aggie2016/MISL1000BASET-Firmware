/*
 * main.h
 *
 *  Created on: Mar 28, 2015
 *      Author: akobyljanec
 */

#ifndef ITASK_H_
#define ITASK_H_

#include <string>
#include <functional>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define EMPTY_SLOT -1
#define NOT_FOUND -1


class ITask
{
public:
	ITask(std::string TaskName, uint16_t stackSize, UBaseType_t taskPriority = 0);
	virtual ~ITask();
	
	enum class TaskStartResult
	{
		StartedSuccessfully,
		NoSlotMaxPriorityGiven,
		StartedNewPriority,
		FailedToStart
	};
	
	enum class TaskState
	{
		Started,
		Suspended,
		Deleted
	};
	
	void deleteTask();
	void pauseTask();
	void restartTask();
	TaskStartResult startTask();
	virtual void functionToRun() = 0;
	
	std::string name();
	int priority();
	TaskHandle_t handle();

private:
	static int m_TaskPriorityArray[configMAX_PRIORITIES + 1];
	std::string m_taskName;
	uint16_t m_stackSize;
	int m_priority;
	TaskState m_taskState;
	int m_priorityRequested;
	TaskHandle_t m_handle;
	
	int searchForPriority();
	static void callback(void *context);
};

#endif
