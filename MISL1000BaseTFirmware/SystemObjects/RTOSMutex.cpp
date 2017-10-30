#include "RTOSMutex.h"


RTOSMutex::RTOSMutex() : m_mutexAttached(false)
{
}

RTOSMutex::RTOSMutex(xSemaphoreHandle &handle, TickType_t time)
    : m_handle(handle),
    m_blockTime(time),
    m_mutexAttached(true)
{
	xSemaphoreTake(handle, time / portTICK_PERIOD_MS);
}


RTOSMutex::~RTOSMutex()
{
    if (m_mutexAttached)
    {
        xSemaphoreGive(m_handle);
    }

}
    

xSemaphoreHandle RTOSMutex::getHandle() const
{
    return m_handle;
}


TickType_t RTOSMutex::getBlockTime() const
{
    return m_blockTime;
}


RTOSMutex& RTOSMutex::operator=(const RTOSMutex &rhs)
{
    m_mutexAttached = rhs.m_mutexAttached;
    m_handle = rhs.m_handle;
}