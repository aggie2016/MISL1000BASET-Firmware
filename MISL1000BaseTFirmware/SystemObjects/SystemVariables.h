#ifndef SYSTEMVARIABLES_H
#define SYSTEMVARIABLES_H

#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <inc/hw_sysctl.h>
#include <driverlib/rom.h>
#include <driverlib/sysctl.h>



enum class SystemPeripheral : uint32_t
{
	PERIPH_ADC0 = 0xf0003800,
	PERIPH_ADC1 = 0xf0003801,
	PERIPH_CAN0 = 0xf0003400,
	PERIPH_CAN1 = 0xf0003401,
	PERIPH_COMP0 = 0xf0003c00,
	PERIPH_EMAC0 = 0xf0009c00,
	PERIPH_EPHY0 = 0xf0003000,
	PERIPH_EPI0 = 0xf0001000,
	PERIPH_GPIOA = 0xf0000800,
	PERIPH_GPIOB = 0xf0000801,
	PERIPH_GPIOC = 0xf0000802,
	PERIPH_GPIOD = 0xf0000803,
	PERIPH_GPIOE = 0xf0000804,
	PERIPH_GPIOF = 0xf0000805,
	PERIPH_GPIOG = 0xf0000806,
	PERIPH_GPIOH = 0xf0000807,
	PERIPH_GPIOJ = 0xf0000808,
	PERIPH_HIBERNATE = 0xf0001400,
	PERIPH_CCM0 = 0xf0007400,
	PERIPH_EEPROM0 = 0xf0005800,
	PERIPH_FAN0 = 0xf0005400,
	PERIPH_FAN1 = 0xf0005401,
	PERIPH_GPIOK = 0xf0000809,
	PERIPH_GPIOL = 0xf000080a,
	PERIPH_GPIOM = 0xf000080b,
	PERIPH_GPION = 0xf000080c,
	PERIPH_GPIOP = 0xf000080d,
	PERIPH_GPIOQ = 0xf000080e,
	PERIPH_GPIOR = 0xf000080f,
	PERIPH_GPIOS = 0xf0000810,
	PERIPH_GPIOT = 0xf0000811,
	PERIPH_I2C0 = 0xf0002000,
	PERIPH_I2C1 = 0xf0002001,
	PERIPH_I2C2 = 0xf0002002,
	PERIPH_I2C3 = 0xf0002003,
	PERIPH_I2C4 = 0xf0002004,
	PERIPH_I2C5 = 0xf0002005,
	PERIPH_I2C6 = 0xf0002006,
	PERIPH_I2C7 = 0xf0002007,
	PERIPH_I2C8 = 0xf0002008,
	PERIPH_I2C9 = 0xf0002009,
	PERIPH_LCD0 = 0xf0009000,
	PERIPH_ONEWIRE0 = 0xf0009800,
	PERIPH_PWM0 = 0xf0004000,
	PERIPH_PWM1 = 0xf0004001,
	PERIPH_QEI0 = 0xf0004400,
	PERIPH_QEI1 = 0xf0004401,
	PERIPH_SSI0 = 0xf0001c00,
	PERIPH_SSI1 = 0xf0001c01,
	PERIPH_SSI2 = 0xf0001c02,
	PERIPH_SSI3 = 0xf0001c03,
	PERIPH_TIMER0 = 0xf0000400,
	PERIPH_TIMER1 = 0xf0000401,
	PERIPH_TIMER2 = 0xf0000402,
	PERIPH_TIMER3 = 0xf0000403,
	PERIPH_TIMER4 = 0xf0000404,
	PERIPH_TIMER5 = 0xf0000405,
	PERIPH_TIMER6 = 0xf0000406,
	PERIPH_TIMER7 = 0xf0000407,
	PERIPH_UART0 = 0xf0001800,
	PERIPH_UART1 = 0xf0001801,
	PERIPH_UART2 = 0xf0001802,
	PERIPH_UART3 = 0xf0001803,
	PERIPH_UART4 = 0xf0001804,
	PERIPH_UART5 = 0xf0001805,
	PERIPH_UART6 = 0xf0001806,
	PERIPH_UART7 = 0xf0001807,
	PERIPH_UDMA = 0xf0000c00,
	PERIPH_USB0 = 0xf0002800,
	PERIPH_WDOG0 = 0xf0000000,
	PERIPH_WDOG1 = 0xf0000001,
	PERIPH_WTIMER0 = 0xf0005c00,
	PERIPH_WTIMER1 = 0xf0005c01,
	PERIPH_WTIMER2 = 0xf0005c02,
	PERIPH_WTIMER3 = 0xf0005c03,
	PERIPH_WTIMER4 = 0xf0005c04,
	PERIPH_WTIMER5 = 0xf0005c05
};
   	



//*****************************************************************************
//
//! Pauses execution of the microcontroller for the time specified in ui32Ms in
//! milliseconds by converting ui32Ms to MCU ticks. This function blocks all
//! other running tasks for the time specified. [USE SPARINGLY].
//!
//! \param ui32Ms the number of milliseconds to pause the MCU
//
//*****************************************************************************
static void delayMs(uint32_t ui32Ms) 
{

    	// 1 clock cycle = 1 / SysCtlClockGet() second
    	// 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    	// 1 second = SysCtlClockGet() / 3
    	// 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    ROM_SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}
    
//*****************************************************************************
//
//! Pauses execution of the microcontroller for the time specified in ui32Us in
//! microseconds by converting ui32Us to MCU ticks. This function blocks all
//! other running tasks for the time specified. [USE SPARINGLY].
//!
//! \param ui32Us the number of microseconds to pause the MCU
//
//*****************************************************************************
static void delayUs(uint32_t ui32Us) 
{
    ROM_SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}



#endif //SystemVariables.h