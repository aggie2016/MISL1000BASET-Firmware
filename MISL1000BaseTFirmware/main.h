/*
 * main.h
 *
 *  Created on: Mar 28, 2015
 *      Author: Christopher Miller
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <cstdbool>
#include <cstdint>
#include <memory>
#include <vector>
#include <inc/hw_memmap.h>
#include <driverlib/debug.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include <HardwareControl/GPIOPin.h>
#include <HardwareControl/UIOStream.h>
#include <HardwareControl/SPI.h>
#include "SystemObjects/RTOSMutex.h"

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

// System clock rate, 120 MHz
#define SYSTEM_CLOCK    120000000U
uint32_t g_ui32SysClock = SYSTEM_CLOCK;

// Software Version Information
#define MAJOR_VERSION	0
#define MINOR_VERSION	1
#define REVISION		43


/* Peripheral definitions for TM4C1294NCPDT microcontroller */
/* SSI port */
#define ETHOCON_SSI_BASE            SSI1_BASE
#define ETHOCON_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI1

/* GPIO for SSI pins */
/* CLK pin */
#define ETHOCON_SSI_CLK_GPIO_PORT_BASE  GPIOPorts::PORT_B
#define ETHOCON_SSI_CLK                 GPIOPins::PIN_5
/* TX pin */
#define ETHOCON_SSI_TX_GPIO_PORT_BASE   GPIOPorts::PORT_E
#define ETHOCON_SSI_TX                  GPIOPins::PIN_4
/* RX pin */
#define ETHOCON_SSI_RX_GPIO_PORT_BASE   GPIOPorts::PORT_E
#define ETHOCON_SSI_RX                  GPIOPins::PIN_5
/* CS pin */
#define ETHOCON_SSI_FSS_GPIO_PORT_BASE  GPIOPorts::PORT_B
#define ETHOCON_SSI_FSS                 GPIOPins::PIN_4


/* Peripheral definitions for TM4C1294NCPDT microcontroller */
/* SSI port */
#define WIZNET_SSI_BASE            SSI2_BASE
#define WIZNET_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI2

/* GPIO for SSI pins */
/* CLK pin */
#define WIZNET_SSI_CLK_GPIO_PORT_BASE  GPIOPorts::PORT_D
#define WIZNET_SSI_CLK                 GPIOPins::PIN_3
/* TX pin */
#define WIZNET_SSI_TX_GPIO_PORT_BASE   GPIOPorts::PORT_D
#define WIZNET_SSI_TX                  GPIOPins::PIN_1
/* RX pin */
#define WIZNET_SSI_RX_GPIO_PORT_BASE   GPIOPorts::PORT_D
#define WIZNET_SSI_RX                  GPIOPins::PIN_0
/* CS pin */
#define WIZNET_SSI_FSS_GPIO_PORT_BASE  GPIOPorts::PORT_D
#define WIZNET_SSI_FSS                 GPIOPins::PIN_2


void startTasks(std::vector<ITask*> taskList);
bool setupHardware();

#endif /* MAIN_H_ */
