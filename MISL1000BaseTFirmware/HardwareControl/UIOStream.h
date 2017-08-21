#ifndef UIOSTREAM_H
#define UIOSTREAM_H

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <inc/hw_memmap.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include "string.h"
#include "utils/uartstdio.h"
#include "SystemObjects/RTOSMutex.h"

extern uint32_t g_ui32SysClock;
extern xSemaphoreHandle g_pUARTSemaphore;


namespace MISL
{

	#define UART_TARGETED		1
	#define UART_MAX_BUF_LENGTH	UART_RX_BUFFER_SIZE
	
	static char g_inputBuffer[UART_MAX_BUF_LENGTH];
	static char g_dataBuffer[UART_MAX_BUF_LENGTH];
	
	static std::string endl = "\n";
	
	static void ConfigureUART(void);
	
	
	/*! /fn void MISL::SetUARTEcho(bool state)
	*	Enables or disables the reprinting of characters to the console window
	*	after they are received.
	*/
	static void SetUARTEcho(bool state)
	{
		UARTEchoSet(state);
	}
	
	typedef int ustreamsize;

	
/*! /class MISL::UIStream
*	Thread-Safe UART input stream that implements typical stream buffer overloads
*	based on std::cin. Software that uses this header can call MISL::ucin just 
*	as they would if they were using the std library.
*/	
class UIStream
	{
	public:
		UIStream();
		virtual ~UIStream();
		
		/*! /fn UIStream &UIStream::get(char *buffer, ustreamsize n)
		*	Gets the number of bytes from the UART specified by UART_TARGETED and
		*	places it in the memory address passed to this function. This function
		*	assumes that the user has allocated enough space to contain the number
		*   of bytes collected.
		*/
		UIStream &get(char *buffer, ustreamsize n);
		
		/*! /fn UIStream &UIStream::get(char *buffer, ustreamsize n)
		*	Gets the number of bytes from the UART specified by UART_TARGETED and
		*	places it in the memory address passed to this function broken into tokens
	    *	if the delimiter parameter is provided.This function assumes that the user 
	    *   has allocated enough space to contain the number of bytes collected. 
		*/
		UIStream &get(char *buffer, ustreamsize n, const char &delim);
		
		/*! /fn UIStream &UIStream::gcount()
		*	Returns the number of characters read in the last operation as 32-bit
		*	integer.
		*/
		UIStream &gcount();
		
		/*! /fn UIStream &UIStream::getline(char* s, ustreamsize n = -1)
		*	Reads the UART_TARGETED buffer until a '\n' newline character is reached
		*   unless the number of characters read from the buffer exceeds ustreamsize.
		*/
		UIStream &getline(char* s, ustreamsize n = -1);

		/*! /fn UIStream &UIStream::peek()
		*	Returns the next character in the input stream as a int
		*/
		int peek();

		/*! /fn UIStream &UIStream::read(char* s, streamsize n)
		*	Extracts n characters from the stream and stores them in the array pointed to by s.
		*	This function simply copies a block of data, without checking its contents nor 
		*	appending a null character at the end.
		*/
		UIStream &read(char* s, ustreamsize n);
		
		//Arithemtic Types
		UIStream& operator>>(bool& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (bool)atoi(g_inputBuffer);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(short& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (short)atoi(g_inputBuffer);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(unsigned short& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (unsigned short)strtoul(g_inputBuffer, NULL, 0); 
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(int& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (int)atoi(g_inputBuffer);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(unsigned int& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (unsigned int)strtoul(g_inputBuffer, NULL, 0);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(long& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (long)atol(g_inputBuffer);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(unsigned long& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (unsigned int)strtoul(g_inputBuffer, NULL, 0);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(float& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (float)strtof(g_inputBuffer, NULL);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(double& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = (double)atof(g_inputBuffer);
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}
		UIStream& operator>>(std::string& val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_inputBuffer, UART_MAX_BUF_LENGTH);
			val = g_inputBuffer;
			memset(g_inputBuffer, 0, sizeof(g_inputBuffer));
			return *this;
		}	
		UIStream& operator>>(void * & val)
		{
			memset(g_dataBuffer, 0, sizeof(g_dataBuffer));
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTgets(g_dataBuffer, UART_MAX_BUF_LENGTH);
			val = (void *)g_dataBuffer;
			return *this;
		}
		
		//Stream Buffers [NOT IMPLEMENTED]
		//UIStream& operator>>(streambuf* sb);
		
		//Manipulators
		UIStream& operator>>(UIStream& (*pf)(UIStream&))
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			return *this;
		}
		
	private:
		int lastReadCount;
		
	};
	
	
	/*! /class MISL::UOStream
	*	Thread-Safe UART output stream that implements typical stream buffer overloads
	*	based on std::cout. Software that uses this header can call	MISL::ucout
	*	just as they would if they were using the std library.
	*/	
	class UOStream
	{
	public:
		UOStream();
		virtual ~UOStream();	
		
		UOStream &put(const char &ch);
		UOStream &write(const char* s, ustreamsize n);
		
		UOStream &operator<<(bool val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%s", val);
			return *this;
		}
		
		UOStream &operator<<(char* val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%s", val);
			return *this;
		}
		
		UOStream &operator<<(std::string val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%s", val.c_str());
			return *this;
		}
		
		UOStream &operator<<(short val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(unsigned short val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%u", val);
			return *this;
		}
		
		UOStream &operator<<(int val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(unsigned int val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%u", val);
			return *this;
		}
		
		UOStream &operator<<(long val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(unsigned long val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%u", val);
			return *this;
		}
		
		UOStream &operator<<(long long val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(unsigned long long val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%u", val);
			return *this;
		}
		
		UOStream &operator<<(float val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(double val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(long double val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			UARTprintf("%d", val);
			return *this;
		}
		
		UOStream &operator<<(void* val)
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			return *this;
		}
		
		//Stream Buffers [NOT IMPLEMENTED]
		//UOStream &operator<<(streambuf* sb);
		
		//Stream Manipulators
		UOStream &operator<<(UOStream& (*pf)(UOStream&))
		{
			RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
			return *this;
		}
		
	};
	
	static UIStream ucin;
	static UOStream ucout;
	static UOStream ucerr;	
}


#endif //UIOStream.h