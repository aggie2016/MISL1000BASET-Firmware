#include "UIOStream.h"

using namespace MISL;

static bool g_UARTConfigured = false;

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
static void MISL::ConfigureUART(void)
{
	

	//
	// Enable the GPIO Peripheral used by UART1.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	//
	// Enable UART1
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

	//
	// Configure GPIO Pins for UART mode.
	//
	ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
	ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
	ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	
	//
	// Initialize the UART for console I/O.
	//
	UARTStdioConfig(1, 115200, g_ui32SysClock);
}

UIStream::UIStream()
{
	if (!g_UARTConfigured)
	{
		ConfigureUART();
		g_UARTConfigured = true;
	}
}

UIStream::~UIStream()
{
	
}

/*! /fn UIStream &UIStream::get(char *buffer, ustreamsize n)
*	Gets the number of bytes from the UART specified by UART_TARGETED and
*	places it in the memory address passed to this function. This function
*	assumes that the user has allocated enough space to contain the number
*   of bytes collected.
*/
UIStream &UIStream::get(char *buffer, ustreamsize n)
{
	RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
	return *this;
}
		
/*! /fn UIStream &UIStream::get(char *buffer, ustreamsize n)
*	Gets the number of bytes from the UART specified by UART_TARGETED and
*	places it in the memory address passed to this function broken into tokens
*	if the delimiter parameter is provided.This function assumes that the user 
*   has allocated enough space to contain the number of bytes collected. 
*/
UIStream &UIStream::get(char *buffer, ustreamsize n, const char &delim)
{
	RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
	return *this;
}
		
/*! /fn UIStream &UIStream::gcount()
*	Returns the number of characters read in the last operation as 32-bit
*	integer.
*/
UIStream &UIStream::gcount()
{
	return *this;
}
		
/*! /fn UIStream &UIStream::getline(char* s, ustreamsize n = -1)
*	Reads the UART_TARGETED buffer until a '\n' newline character is reached
*   unless the number of characters read from the buffer exceeds ustreamsize.
*/
UIStream &UIStream::getline(char* s, ustreamsize n)
{
	RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
	return *this;
}

/*! /fn UIStream &UIStream::peek()
*	Returns the next character in the input stream as a int
*/
int UIStream::peek()
{
	RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
	
	//Character not in buffer
	return -1;
}

/*! /fn UIStream &UIStream::read(char* s, streamsize n)
*	Extracts n characters from the stream and stores them in the array pointed to by s.
*	This function simply copies a block of data, without checking its contents nor 
*	appending a null character at the end.
*/
UIStream &UIStream::read(char* s, ustreamsize n)
{
	RTOSMutex UARTMutex(g_pUARTSemaphore, portMAX_DELAY);
	
	return *this;
}



UOStream::UOStream()
{
	if (!g_UARTConfigured)
	{
		ConfigureUART();
		g_UARTConfigured = true;
	}
}

UOStream::~UOStream()
{
	
}

UOStream &UOStream::put(const char &ch)
{
	return *this;
}
UOStream &UOStream::write(const char* s, ustreamsize n)
{
	return *this;
}

