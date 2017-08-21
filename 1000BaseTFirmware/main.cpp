#include <stdbool.h>
#include <stdint.h>
#include <memory>
#include <vector>
#include <inc/hw_memmap.h>
#include "driverlib/debug.h"
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include "HardwareControl/GPIOPin.h"
#include "CommandLine/Commands/SetPort.h"

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Demo Task declarations
void demoLEDTask(void *pvParameters);
void demoSerialTask(void *pvParameters);

int main(void)
{
	// Initialize system clock to 120 MHz
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), SYSTEM_CLOCK);
	
	// Create demo tasks
	xTaskCreate(demoLEDTask,
		(const portCHAR *)"LEDs",
		configMINIMAL_STACK_SIZE,
		NULL,
		1,
		NULL);

	vTaskStartScheduler();
	return 0;
	
}


// Flash the LEDs on the launchpad
void demoLEDTask(void *pvParameters)
{
	GPIOPin StatusLEDPin0(GPIOPorts::PORT_F, GPIOPins::PIN_0, PinDirection::OUTPUT);
	GPIOPin StatusLEDPin1(GPIOPorts::PORT_F, GPIOPins::PIN_1, PinDirection::OUTPUT);
	GPIOPin StatusLEDPin2(GPIOPorts::PORT_F, GPIOPins::PIN_2, PinDirection::OUTPUT);
	GPIOPin StatusLEDPin3(GPIOPorts::PORT_F, GPIOPins::PIN_3, PinDirection::OUTPUT);
	
	for (;;)
	{
	    
		StatusLEDPin0.write(GPIOState::HIGH);
		StatusLEDPin1.write(GPIOState::HIGH);
		StatusLEDPin2.write(GPIOState::HIGH);
		StatusLEDPin3.write(GPIOState::HIGH);
		ROM_SysCtlDelay(10000000);

		StatusLEDPin0.write(GPIOState::LOW);
		StatusLEDPin1.write(GPIOState::LOW);
		StatusLEDPin2.write(GPIOState::LOW);
		StatusLEDPin3.write(GPIOState::LOW);
		ROM_SysCtlDelay(10000000);
	}
}