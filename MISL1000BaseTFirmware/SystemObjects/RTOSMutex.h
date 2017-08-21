#ifndef RTOSMUTEX_H
#define RTOSMUTEX_H

#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/semphr.h"

//Use of this class provides auto-locking and unlocking once the object's lifetime expires.
/*
* blockTimeMs The time in ticks to wait for the semaphore to become
* available. A block time of zero can be used to poll the semaphore. A block
* time of portMAX_DELAY can be used to block indefinitely (provided
* INCLUDE_vTaskSuspend is set to 1 in FreeRTOSConfig.h).
*/
class RTOSMutex
{
public:
	RTOSMutex(xSemaphoreHandle &handle, TickType_t blockTimeMs);
    ~RTOSMutex();
private:
	xSemaphoreHandle m_handle;
};

#endif //RTOSMutex.h