#include "GPIOPin.h"

GPIOPin::GPIOPin(GPIOPorts port, GPIOPins pin, PinDirection direction)
{
	m_port = port;
	m_pin = pin;
	
	//Enable system peripherals
	initializeGPIO();
	
	//Set direction
	setGPIODirection(direction);
}


GPIOPin::~GPIOPin()
{
}

void GPIOPin::setGPIODirection(PinDirection direction)
{
	uint32_t port = HelperFunctions::enumToType(m_port);
	uint32_t pin = HelperFunctions::enumToType(m_pin);
	
	if (direction == PinDirection::INPUT)
	{
		ROM_GPIOPinTypeGPIOInput(port, pin);	
	}
	else if (direction == PinDirection::OUTPUT)
	{
		ROM_GPIOPinTypeGPIOOutput(port, pin);		
	}
}

PinDirection GPIOPin::GPIODirection()
{
	return PinDirection::OUTPUT;
}
	
void GPIOPin::setGPIOIntType(PinIntType intType)
{
	
}
PinIntType GPIOPin::GPIOIntType()
{
	return PinIntType::BOTH_EDGES;
}
	
void GPIOPin::setGPIOPadType(PinDriveStrength strength, PinType type)
{
	
}
void GPIOPin::getGPIOPadType(PinDriveStrength *strength, PinType *type)
{
	
}

void GPIOPin::write(GPIOState state)
{
	uint32_t port = HelperFunctions::enumToType(m_port);
	uint32_t pin = HelperFunctions::enumToType(m_pin);
	
	if (state == GPIOState::HIGH)
	{
		ROM_GPIOPinWrite(port, pin, pin);	
	}
	else
	{
		ROM_GPIOPinWrite(port, pin, 0);
	}
}

GPIOState GPIOPin::read(GPIOPorts gpioPort, GPIOPins gpioPins)
{
	uint32_t port = HelperFunctions::enumToType(gpioPort);
	uint32_t pin = HelperFunctions::enumToType(gpioPins);
	
	uint32_t result = ROM_GPIOPinRead(port, pin);
	if (result == pin)
	{
		return GPIOState::HIGH;
	}
	else if (result == 0x00)
	{
		return GPIOState::LOW;
	}
	else
	{
		ExceptionHandler::ThrowException("Tried to get GPIO State. Unknown state returned.");
		while (1)
		{
			
		}
	}
	return GPIOState::LOW;
}

	
void GPIOPin::setIntState(bool enabled)
{
	
}

void GPIOPin::setIntCallback(void(*callback)(void))
{
	m_callback = callback;
}

bool GPIOPin::initializeGPIO(void)
{
	//Enable system peripheral
	ROM_SysCtlPeripheralEnable(HelperFunctions::enumToType(m_sysPortMappings.at(m_port)));
	
	ROM_SysCtlDelay(1);
	return true;
}

std::map<GPIOPorts, SystemPeripheral> GPIOPin::buildMap()
{
	//Build constant map of GPIOPorts to SystemPeripherals
	std::map<GPIOPorts, SystemPeripheral> map;
	map[GPIOPorts::PORT_A] = SystemPeripheral::PERIPH_GPIOA;
	map[GPIOPorts::PORT_B] = SystemPeripheral::PERIPH_GPIOB;
	map[GPIOPorts::PORT_C] = SystemPeripheral::PERIPH_GPIOC;
	map[GPIOPorts::PORT_D] = SystemPeripheral::PERIPH_GPIOD;
	map[GPIOPorts::PORT_E] = SystemPeripheral::PERIPH_GPIOE;
	map[GPIOPorts::PORT_F] = SystemPeripheral::PERIPH_GPIOF;
	map[GPIOPorts::PORT_G] = SystemPeripheral::PERIPH_GPIOG;
	map[GPIOPorts::PORT_H] = SystemPeripheral::PERIPH_GPIOH;
	map[GPIOPorts::PORT_J] = SystemPeripheral::PERIPH_GPIOJ;
	map[GPIOPorts::PORT_K] = SystemPeripheral::PERIPH_GPIOK;
	map[GPIOPorts::PORT_L] = SystemPeripheral::PERIPH_GPIOL;
	map[GPIOPorts::PORT_M] = SystemPeripheral::PERIPH_GPIOM;
	map[GPIOPorts::PORT_N] = SystemPeripheral::PERIPH_GPION;
	map[GPIOPorts::PORT_P] = SystemPeripheral::PERIPH_GPIOP;
	map[GPIOPorts::PORT_Q] = SystemPeripheral::PERIPH_GPIOQ;
	map[GPIOPorts::PORT_R] = SystemPeripheral::PERIPH_GPIOR;
	map[GPIOPorts::PORT_S] = SystemPeripheral::PERIPH_GPIOS;
	map[GPIOPorts::PORT_T] = SystemPeripheral::PERIPH_GPIOT;

	return map;
}