


#include "BlinkLEDTask.h"

BlinkLEDTask::BlinkLEDTask()
	: ITask("Blink Task", 200, 2)
{
	
}


BlinkLEDTask::~BlinkLEDTask()
{
}

void BlinkLEDTask::functionToRun()
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
		vTaskDelay(250 / portTICK_PERIOD_MS);

		StatusLEDPin0.write(GPIOState::LOW);
		StatusLEDPin1.write(GPIOState::LOW);
		StatusLEDPin2.write(GPIOState::LOW);
		StatusLEDPin3.write(GPIOState::LOW);
		vTaskDelay(250 / portTICK_PERIOD_MS);
	}
}