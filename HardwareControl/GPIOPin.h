#ifndef GPIOPIN_H
#define GPIOPIN_H

#include <map>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../SystemObjects/SystemVariables.h"
#include "../SystemObjects/ExceptionHandler.h"
#include "../SystemObjects/HelperFunctions.h"

//*****************************************************************************
//
// The following values define the bit field for the ui8Pins argument to
// several of the APIs.
//
//*****************************************************************************
enum class GPIOPins : uint8_t
{
	PIN_0 = 0x00000001,
	PIN_1 = 0x00000002,
	PIN_2 = 0x00000004,
	PIN_3 = 0x00000008,
	PIN_4 = 0x00000010,
	PIN_5 = 0x00000020,
	PIN_6 = 0x00000040,
	PIN_7 = 0x00000080
};

enum class GPIOPorts : uint32_t
{
	PORT_A = GPIO_PORTA_BASE,
	PORT_B = GPIO_PORTB_BASE,
	PORT_C = GPIO_PORTC_BASE,
	PORT_D = GPIO_PORTD_BASE,
	PORT_E = GPIO_PORTE_BASE,
	PORT_F = GPIO_PORTF_BASE,
	PORT_G = GPIO_PORTG_BASE,
	PORT_H = GPIO_PORTH_BASE,
	PORT_J = GPIO_PORTJ_BASE,
	PORT_K = GPIO_PORTK_BASE,
	PORT_L = GPIO_PORTL_BASE,
	PORT_M = GPIO_PORTM_BASE,
	PORT_N = GPIO_PORTN_BASE,
	PORT_P = GPIO_PORTP_BASE,
	PORT_Q = GPIO_PORTQ_BASE,
	PORT_R = GPIO_PORTR_BASE,
	PORT_S = GPIO_PORTS_BASE,
	PORT_T = GPIO_PORTT_BASE
	
};

//*****************************************************************************
//
// Values that can be passed to GPIODirModeSet as the ui32PinIO parameter, and
// returned from GPIODirModeGet.
//
//*****************************************************************************
enum class PinDirection : uint8_t
{
	INPUT = 0x00000000,
	OUTPUT = 0x00000001,
	HW = 0x00000002
};

//*****************************************************************************
//
// Values that can be passed to GPIOIntTypeSet as the ui32IntType parameter,
// and returned from GPIOIntTypeGet.
//
//*****************************************************************************
enum class PinIntType : uint32_t
{
	FALLING_EDGE = 0x00000000, /* Interrupt on falling edge */
	RISING_EDGE = 0x00000004,  /* Interrupt on rising edge */
	BOTH_EDGES = 0x00000001,   /* Interrupt on both edges */
	LOW_LEVEL = 0x00000002,    /* Interrupt on low level */
	HIGH_LEVEL = 0x00000006,   /* Interrupt on high level */
	DISCRETE_INT = 0x00010000  /* Interrupt for individual pins */
};

//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32Strength parameter,
// and returned by GPIOPadConfigGet in the *pui32Strength parameter.
//
//*****************************************************************************
enum class PinDriveStrength : uint8_t
{
	STR_2mA = 0x00000001,	/* 2mA Drive Strength */
	STR_4mA = 0x00000002,	/* 4mA Drive Strength */
	STR_6mA = 0x00000065,	/* 6mA Drive Strength */
	STR_8mA = 0x00000066,	/* 8mA Drive Strength */
	STR_8mA_SC = 0x0000006E,	/* 8mA Drive Strength with slew rate control */
	STR_10mA = 0x00000075,	/* 10mA Drive Strength */
	STR_12mA = 0x00000077	/* 12mA Drive Strength */
};

//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32PadType parameter,
// and returned by GPIOPadConfigGet in the *pui32PadType parameter.
//
//*****************************************************************************
enum class PinType : uint16_t
{
	TYPE_STD = 0x00000008,		  /* Push-Pull */
	TYPE_STD_WPU = 0x0000000A,	  /* Push-Pull with weak pull-up */
	TYPE_STD_WPD = 0x0000000C,	  /* Push-Pull with weak pull-down */
	TYPE_OD = 0x00000009,		  /* Open-drain */
	TYPE_ANALOG = 0x00000000,	  /* Analog comparator */
	TYPE_WAKE_HIGH = 0x00000208,  /* Hibernate wake, high */
	TYPE_WAKE_LOW = 0x00000108    /* Hibernate wake, low */	
};

//*****************************************************************************
//
// Values that can be passed to GPIOIntEnable() and GPIOIntDisable() functions
// in the ui32IntFlags parameter.
//
//*****************************************************************************
enum class InterruptPin : uint16_t
{
	PIN_0 = 0x00000001,
	PIN_1 = 0x00000002,
	PIN_2 = 0x00000004,
	PIN_3 = 0x00000008,
	PIN_4 = 0x00000010,
	PIN_5 = 0x00000020,
	PIN_6 = 0x00000040,
	PIN_7 = 0x00000080,
	DMA = 0x00000100
	
};

enum class GPIOState
{
	HIGH,
	LOW
};

class GPIOPin
{
public:
	GPIOPin(GPIOPorts port, GPIOPins pin, PinDirection direction = PinDirection::OUTPUT);
	virtual ~GPIOPin();
	
	void setGPIODirection(PinDirection direction);
	PinDirection GPIODirection();
		
	void setGPIOIntType(PinIntType intType);
	PinIntType GPIOIntType();
	
	void setGPIOPadType(PinDriveStrength strength, PinType type);
	void getGPIOPadType(PinDriveStrength *strength, PinType *type);
	
	void setIntState(bool enabled);
	void setIntCallback(void(*callback)(void));

	void write(GPIOState state);
	GPIOState read(GPIOPorts port, GPIOPins pins);
    
    GPIOPorts port() const;
    GPIOPins pin() const; 

protected:
	virtual bool initializeGPIO(void);
	
	
private:
	GPIOPorts m_port;
	GPIOPins m_pin;
	void(*m_callback)(void);
	static std::map<GPIOPorts, SystemPeripheral> buildMap();

	const std::map<GPIOPorts, SystemPeripheral> m_sysPortMappings = buildMap();

};

#endif //GPIOPin.h