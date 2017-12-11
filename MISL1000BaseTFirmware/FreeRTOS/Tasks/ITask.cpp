#include "ITask.h"



ITask::ITask(std::string TaskName, uint16_t stackSize, UBaseType_t priority)
	: m_taskName(TaskName), m_stackSize(stackSize), m_priorityRequested(priority), m_handle(nullptr)
{
	if (!priority)
	{ 
		//No priority specified, so we'll assign one automatically
		//Search the task priority array for an empty slot and set that priority as taken
		int possiblePriority = searchForPriority();
		if (possiblePriority == NOT_FOUND)
		{
			//No priorities availble. Assign the lowest priority to this new task.
			m_priority = configMAX_PRIORITIES - 1;
		}
		else
		{
			//Task priority available for use.
			m_priority = possiblePriority;
		}
	}
	else if (priority >= configMAX_PRIORITIES)
	{
		//The user provided a priority greater than or equal to the max allowed
		//Set the task priority to configMAX_PRIORITIES - 1 (last slot) and set that priority as taken
		m_priority = configMAX_PRIORITIES - 1;
		if (m_TaskPriorityArray[m_priority] == EMPTY_SLOT)
		{
			//Task priority available for use.
			m_priority = priority;
			m_TaskPriorityArray[m_priority] = m_priority;
		}
	}
	else
	{	
		//The user provided us with a priority from 1 to (configMAX_PRIORITIES-1)
		if (m_TaskPriorityArray[priority] == EMPTY_SLOT)
		{
			//Task priority available for use.
			m_priority = priority;
			m_TaskPriorityArray[m_priority] = m_priority;
		}
		else
		{
			//The slot they requested is not available, choose one at random.
			int possiblePriority = searchForPriority();
			if (possiblePriority == NOT_FOUND)
			{
				//No priorities availble. Assign the lowest priority to this new task.
				m_priority = configMAX_PRIORITIES - 1;
			}
			else
			{
				//Task priority available for use.
				m_priority = possiblePriority;
			}
		}	
	}	
}


ITask::~ITask()
{
	if (m_handle)
	{
		vTaskDelete(m_handle);
		m_handle = nullptr;
		m_taskState = TaskState::Deleted;
	}
}

void ITask::deleteTask()
{
	if (m_handle)
	{
		vTaskDelete(m_handle);
		m_handle = nullptr;
		m_taskState = TaskState::Deleted;
	}
}


void ITask::pauseTask()
{
	if (m_handle)
	{
		vTaskSuspend(m_handle);
		m_taskState = TaskState::Suspended;
	}
}

void ITask::restartTask()
{
	if (m_taskState == TaskState::Suspended && m_handle)
	{
		vTaskResume(m_handle);
		m_taskState = TaskState::Started;
	}
}

ITask::TaskStartResult ITask::startTask()
{
	TaskStartResult startResult = TaskStartResult::StartedSuccessfully;

	xTaskCreate(callback, (const portCHAR *)m_taskName.c_str(), m_stackSize, this, m_priority, &m_handle);
	
	
	if (m_priority != m_priorityRequested && m_handle)
	{
		startResult = TaskStartResult::StartedNewPriority;
	}
	else if (m_priority == (configMAX_PRIORITIES - 1) && (m_priorityRequested != (configMAX_PRIORITIES - 1) || m_priorityRequested > configMAX_PRIORITIES))
	{
		startResult = TaskStartResult::NoSlotMaxPriorityGiven;
	}
	else if (m_handle)
	{
		startResult = TaskStartResult::StartedSuccessfully;
	}
	else
	{
		startResult = TaskStartResult::FailedToStart;
	}
	m_taskState = TaskState::Started;
	
	return startResult;
}

std::string ITask::name()
{
	return m_taskName;
}

int ITask::priority()
{
	return m_priority;
}

TaskHandle_t ITask::handle()
{
	return m_handle;
}

int ITask::m_TaskPriorityArray[configMAX_PRIORITIES + 1] = { 0 };

int ITask::searchForPriority()
{
	for (int i = 1; i < configMAX_PRIORITIES; i++)
	{
		if (m_TaskPriorityArray[i] != -1)
		{
			return i;
		}
	}
	return -1;
}
		
void ITask::callback(void *context)
{
	ITask* taskReferenced = static_cast<ITask*>(context);
	if (taskReferenced)
	{
		taskReferenced->functionToRun();
	}
}