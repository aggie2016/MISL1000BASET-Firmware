#include <stdbool.h>
#include <stdint.h>
#include <memory>
#include <vector>
#include <inc/hw_memmap.h>
#include <driverlib/debug.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include <HardwareControl/GPIOPin.h>
#include <HardwareControl/UIOStream.h>
#include "SystemObjects/RTOSMutex.h"
#include "main.h"


/* Headers for all user-defined FreeRTOS tasks.
*  Use these as a template if you wish to implement
*  more functions that will share the microcontroller
*  computational cycles. To easily create new tasks, 
*  inherit from ITask and call its default constructors.
*/
#include "FreeRTOS/Tasks/BlinkLEDTask.h"
#include "FreeRTOS/Tasks/CLIInterpreterTask.h"


/* Headers for all user-defined MISL Switch CLI Commands.
*  Use these as a template if you wish to implement
*  more functions that will be added to the command line.
*  To create a new CLI Command, create a new class that inherits
*  from ICommand and then build the parameters for the base class
*  by using the following template:
*
*   //Create a list of optional command-line flags that can be used to 
*   //change the behavior of the implemented function. The first parameter
*	//is the escaped flag. The second is a short textual help message.
* 	KeyValueList flags;
*	flags.push_back(std::make_tuple("\\h", "return as hex"));
*	flags.push_back(std::make_tuple("\\i", "return as integer"));
*
*   //Create a list of command-line parameters that can be used to 
*   //force the behavior of the implemented function. The first parameter
*	//is the parameter name. The second is a short textual help message.
*	KeyValueList parameters;
*	parameters.push_back(std::make_tuple("start address", "the address to start reading from"));
*	parameters.push_back(std::make_tuple("end address", "the address to stop reading when reached"));
*
*	//Set the name of the CLI command
*	setName("Read Register");
*	//Create a short description for the help menu
*	setDescription("reads a register from the system");
*	//Attach the flags and parameters to the command
*	setCommandFlags(flags);
*	setCommandParameters(parameters);
*/
#include "CommandLine/Commands/SetPort.h"

uint32_t g_ui32SysClock = SYSTEM_CLOCK;

//*****************************************************************************
//
//! Mutex to control and block access to the UART RX and TX buffers. Prevents
//! multiple FreeRTOS tasks from interacting with this interface at the same
//! time.
//
//*****************************************************************************
xSemaphoreHandle g_pUARTSemaphore;


void startTasks(std::vector<ITask*> taskList);

int main(void)
{
	// Initialize system clock to 120 MHz
	g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), SYSTEM_CLOCK);
	
	// Create system mutexes
	g_pUARTSemaphore = xSemaphoreCreateMutex();
	
	//Turn character echoing when characters are received from the command-line
	MISL::SetUARTEcho(true);
	
	//Clear the console window
	MISL::ClearConsole();
	
	MISL::ucout << "================================================" << MISL::endl
				<< "=     MISL Gigabit Ethernet Switch Layer       =" << MISL::endl
				<< "=      Embedded Command-Line Interface         =" << MISL::endl
				<< "=                                              =" << MISL::endl
				<< "================================================" << MISL::endl
				<< "Version: "
				<< MAJOR_VERSION << "."
				<< MINOR_VERSION << "."
				<< REVISION	<< MISL::endl;
		
	//Create our base system tasks
	std::vector<ITask*> RTOSTasks;

	CLIInterpreterTask *CLI = new CLIInterpreterTask();
	BlinkLEDTask *BlinkTask = new BlinkLEDTask();
	
	RTOSTasks.push_back(CLI);
	RTOSTasks.push_back(BlinkTask);
	
	
	//Add any new CLI commands to the system here before initialization
	CLI->registerCommand(new SetPort());

	
	/*Start our FreeRTOS tasks
	* Normally calling startTask() would result in the specified ITask instance starting
	* immediately, however since we haven't started the FreeRTOS scheduler, the tasks 
	* will merely be created until we reach the vTaskStartScheduler statement below.
	*/
	startTasks(RTOSTasks);	
	
	
	vTaskStartScheduler();
	return 0;
	
}

void startTasks(std::vector<ITask*> taskList)
{
	for (ITask *task : taskList)
	{
		task->startTask();
	}
}