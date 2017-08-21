#include "RTOSMutex.h"



RTOSMutex::RTOSMutex(xSemaphoreHandle &handle, TickType_t time)
{
	xSemaphoreTake(handle, time / portTICK_PERIOD_MS);
	m_handle = handle;
}


RTOSMutex::~RTOSMutex()
{
	xSemaphoreGive(m_handle);
}
