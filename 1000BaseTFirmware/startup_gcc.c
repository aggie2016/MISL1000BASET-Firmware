/*
	This file contains the entry point (Reset_Handler) of your firmware project.
	The reset handled initializes the RAM and calls system library initializers as well as
	the platform-specific initializer and the main() function.
*/
#include "FreeRTOS.h"

extern void *_estack;

#define NULL ((void *)0)

void Reset_Handler();
void Default_Handler();

extern void xPortPendSVHandler(void);
extern void vPortSVCHandler(void);
extern void xPortSysTickHandler(void);

#ifdef DEBUG_DEFAULT_INTERRUPT_HANDLERS
void __attribute__ ((weak)) NMIHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void NMIHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HardFaultHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HardFaultHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) MPUFaultHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void MPUFaultHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) BusFaultHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void BusFaultHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UsageFaultHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UsageFaultHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SvcallHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SvcallHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DebugMonitorHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DebugMonitorHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PendsvHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PendsvHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SystickHandlerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SystickHandlerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortCISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortCISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortDISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortDISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortEISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortEISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART0RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART0RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART1RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART1RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSI0RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSI0RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C0MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C0MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWMFaultISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWMFaultISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWMGenerator0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWMGenerator0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWMGenerator1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWMGenerator1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWMGenerator2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWMGenerator2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) QuadratureEncoder0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void QuadratureEncoder0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADCSequence0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADCSequence0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADCSequence1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADCSequence1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADCSequence2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADCSequence2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADCSequence3ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADCSequence3ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WatchdogTimerISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WatchdogTimerISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer0SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer0SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer0SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer0SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer1SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer1SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer1SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer1SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer2SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer2SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer2SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer2SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) AnalogComparator0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void AnalogComparator0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) AnalogComparator1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void AnalogComparator1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) AnalogComparator2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void AnalogComparator2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SystemControlISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SystemControlISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) FLASHControlISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FLASHControlISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortFISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortFISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortGISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortGISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortHISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortHISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART2RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART2RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSI1RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSI1RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer3SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer3SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer3SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer3SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C1MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C1MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CAN0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CAN1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EthernetISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EthernetISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HibernateISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HibernateISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) USB0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void USB0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PWMGenerator3ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PWMGenerator3ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UdmaSoftwareTransferISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UdmaSoftwareTransferISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UdmaErrorISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UdmaErrorISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC1Sequence0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1Sequence0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC1Sequence1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1Sequence1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC1Sequence2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1Sequence2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC1Sequence3ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1Sequence3ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ExternalBusInterface0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ExternalBusInterface0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortJISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortJISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortKISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortKISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortLISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortLISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSI2RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSI2RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SSI3RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SSI3RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART3RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART3RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART4RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART4RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART5RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART5RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART6RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART6RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) UART7RxTxISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void UART7RxTxISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C2MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C2MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C3MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C3MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer4SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer4SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer4SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer4SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer5SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer5SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer5SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer5SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) FPUISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FPUISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C4MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C4MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C5MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C5MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortMISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortMISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortNISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortNISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TamperISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TamperISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortPISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortPISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP3ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP3ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP4ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP4ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP5ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP5ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP6ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP6ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortP7ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortP7ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ1ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ1ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ2ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ2ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ3ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ3ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ4ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ4ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ5ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ5ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ6ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ6ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortQ7ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortQ7ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortRISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortRISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortSISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortSISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SHA_MD50ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SHA_MD50ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) AES0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void AES0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DES3DES0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DES3DES0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) LCDController0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void LCDController0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer6SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer6SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer6SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer6SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer7SubtimerAISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer7SubtimerAISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) Timer7SubtimerBISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void Timer7SubtimerBISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C6MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C6MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C7MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C7MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HIMScanMatrixKeyboard0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HIMScanMatrixKeyboard0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) OneWire0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void OneWire0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HIMPS_20ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HIMPS_20ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HIMLEDSequencer0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HIMLEDSequencer0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HIMConsumerIR0ISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HIMConsumerIR0ISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C8MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C8MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) I2C9MasterSlaveISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void I2C9MasterSlaveISR();
	asm("bkpt 255");
}

void __attribute__ ((weak)) GPIOPortTISR() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void GPIOPortTISR();
	asm("bkpt 255");
}

#else
void NMIHandlerISR()              __attribute__ ((weak, alias ("Default_Handler")));
void HardFaultHandlerISR()        __attribute__ ((weak, alias ("Default_Handler")));
void MPUFaultHandlerISR()         __attribute__ ((weak, alias ("Default_Handler")));
void BusFaultHandlerISR()         __attribute__ ((weak, alias ("Default_Handler")));
void UsageFaultHandlerISR()       __attribute__ ((weak, alias ("Default_Handler")));
void SvcallHandlerISR()           __attribute__ ((weak, alias ("Default_Handler")));
void DebugMonitorHandlerISR()     __attribute__ ((weak, alias ("Default_Handler")));
void PendsvHandlerISR()           __attribute__ ((weak, alias ("Default_Handler")));
void SystickHandlerISR()          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortAISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortBISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortCISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortDISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortEISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART0RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART1RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void SSI0RxTxISR()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C0MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void PWMFaultISR()                __attribute__ ((weak, alias ("Default_Handler")));
void PWMGenerator0ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void PWMGenerator1ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void PWMGenerator2ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void QuadratureEncoder0ISR()      __attribute__ ((weak, alias ("Default_Handler")));
void ADCSequence0ISR()            __attribute__ ((weak, alias ("Default_Handler")));
void ADCSequence1ISR()            __attribute__ ((weak, alias ("Default_Handler")));
void ADCSequence2ISR()            __attribute__ ((weak, alias ("Default_Handler")));
void ADCSequence3ISR()            __attribute__ ((weak, alias ("Default_Handler")));
void WatchdogTimerISR()           __attribute__ ((weak, alias ("Default_Handler")));
void Timer0SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer0SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer1SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer1SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer2SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer2SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void AnalogComparator0ISR()       __attribute__ ((weak, alias ("Default_Handler")));
void AnalogComparator1ISR()       __attribute__ ((weak, alias ("Default_Handler")));
void AnalogComparator2ISR()       __attribute__ ((weak, alias ("Default_Handler")));
void SystemControlISR()           __attribute__ ((weak, alias ("Default_Handler")));
void FLASHControlISR()            __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortFISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortGISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortHISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART2RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void SSI1RxTxISR()                __attribute__ ((weak, alias ("Default_Handler")));
void Timer3SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer3SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C1MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void CAN0ISR()                    __attribute__ ((weak, alias ("Default_Handler")));
void CAN1ISR()                    __attribute__ ((weak, alias ("Default_Handler")));
void EthernetISR()                __attribute__ ((weak, alias ("Default_Handler")));
void HibernateISR()               __attribute__ ((weak, alias ("Default_Handler")));
void USB0ISR()                    __attribute__ ((weak, alias ("Default_Handler")));
void PWMGenerator3ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void UdmaSoftwareTransferISR()    __attribute__ ((weak, alias ("Default_Handler")));
void UdmaErrorISR()               __attribute__ ((weak, alias ("Default_Handler")));
void ADC1Sequence0ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void ADC1Sequence1ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void ADC1Sequence2ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void ADC1Sequence3ISR()           __attribute__ ((weak, alias ("Default_Handler")));
void ExternalBusInterface0ISR()   __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortJISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortKISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortLISR()               __attribute__ ((weak, alias ("Default_Handler")));
void SSI2RxTxISR()                __attribute__ ((weak, alias ("Default_Handler")));
void SSI3RxTxISR()                __attribute__ ((weak, alias ("Default_Handler")));
void UART3RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART4RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART5RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART6RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void UART7RxTxISR()               __attribute__ ((weak, alias ("Default_Handler")));
void I2C2MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C3MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer4SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer4SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer5SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer5SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void FPUISR()                     __attribute__ ((weak, alias ("Default_Handler")));
void I2C4MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C5MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortMISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortNISR()               __attribute__ ((weak, alias ("Default_Handler")));
void TamperISR()                  __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortPISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP1ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP2ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP3ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP4ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP5ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP6ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortP7ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ1ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ2ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ3ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ4ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ5ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ6ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortQ7ISR()              __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortRISR()               __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortSISR()               __attribute__ ((weak, alias ("Default_Handler")));
void SHA_MD50ISR()                __attribute__ ((weak, alias ("Default_Handler")));
void AES0ISR()                    __attribute__ ((weak, alias ("Default_Handler")));
void DES3DES0ISR()                __attribute__ ((weak, alias ("Default_Handler")));
void LCDController0ISR()          __attribute__ ((weak, alias ("Default_Handler")));
void Timer6SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer6SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer7SubtimerAISR()         __attribute__ ((weak, alias ("Default_Handler")));
void Timer7SubtimerBISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C6MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C7MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void HIMScanMatrixKeyboard0ISR()  __attribute__ ((weak, alias ("Default_Handler")));
void OneWire0ISR()                __attribute__ ((weak, alias ("Default_Handler")));
void HIMPS_20ISR()                __attribute__ ((weak, alias ("Default_Handler")));
void HIMLEDSequencer0ISR()        __attribute__ ((weak, alias ("Default_Handler")));
void HIMConsumerIR0ISR()          __attribute__ ((weak, alias ("Default_Handler")));
void I2C8MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void I2C9MasterSlaveISR()         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOPortTISR()               __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x80] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_estack,
	&Reset_Handler,
	&NMIHandlerISR,
	&HardFaultHandlerISR,
	&MPUFaultHandlerISR,
	&BusFaultHandlerISR,
	&UsageFaultHandlerISR,
	NULL,
	NULL,
	NULL,
	NULL,
	&vPortSVCHandler,
	&DebugMonitorHandlerISR,
	NULL,
	&xPortPendSVHandler,
	&xPortSysTickHandler,
	&GPIOPortAISR,
	&GPIOPortBISR,
	&GPIOPortCISR,
	&GPIOPortDISR,
	&GPIOPortEISR,
	&UART0RxTxISR,
	&UART1RxTxISR,
	&SSI0RxTxISR,
	&I2C0MasterSlaveISR,
	&PWMFaultISR,
	&PWMGenerator0ISR,
	&PWMGenerator1ISR,
	&PWMGenerator2ISR,
	&QuadratureEncoder0ISR,
	&ADCSequence0ISR,
	&ADCSequence1ISR,
	&ADCSequence2ISR,
	&ADCSequence3ISR,
	&WatchdogTimerISR,
	&Timer0SubtimerAISR,
	&Timer0SubtimerBISR,
	&Timer1SubtimerAISR,
	&Timer1SubtimerBISR,
	&Timer2SubtimerAISR,
	&Timer2SubtimerBISR,
	&AnalogComparator0ISR,
	&AnalogComparator1ISR,
	&AnalogComparator2ISR,
	&SystemControlISR,
	&FLASHControlISR,
	&GPIOPortFISR,
	&GPIOPortGISR,
	&GPIOPortHISR,
	&UART2RxTxISR,
	&SSI1RxTxISR,
	&Timer3SubtimerAISR,
	&Timer3SubtimerBISR,
	&I2C1MasterSlaveISR,
	&CAN0ISR,
	&CAN1ISR,
	&EthernetISR,
	&HibernateISR,
	&USB0ISR,
	&PWMGenerator3ISR,
	&UdmaSoftwareTransferISR,
	&UdmaErrorISR,
	&ADC1Sequence0ISR,
	&ADC1Sequence1ISR,
	&ADC1Sequence2ISR,
	&ADC1Sequence3ISR,
	&ExternalBusInterface0ISR,
	&GPIOPortJISR,
	&GPIOPortKISR,
	&GPIOPortLISR,
	&SSI2RxTxISR,
	&SSI3RxTxISR,
	&UART3RxTxISR,
	&UART4RxTxISR,
	&UART5RxTxISR,
	&UART6RxTxISR,
	&UART7RxTxISR,
	&I2C2MasterSlaveISR,
	&I2C3MasterSlaveISR,
	&Timer4SubtimerAISR,
	&Timer4SubtimerBISR,
	&Timer5SubtimerAISR,
	&Timer5SubtimerBISR,
	&FPUISR,
	NULL,
	NULL,
	&I2C4MasterSlaveISR,
	&I2C5MasterSlaveISR,
	&GPIOPortMISR,
	&GPIOPortNISR,
	NULL,
	&TamperISR,
	&GPIOPortPISR,
	&GPIOPortP1ISR,
	&GPIOPortP2ISR,
	&GPIOPortP3ISR,
	&GPIOPortP4ISR,
	&GPIOPortP5ISR,
	&GPIOPortP6ISR,
	&GPIOPortP7ISR,
	&GPIOPortQISR,
	&GPIOPortQ1ISR,
	&GPIOPortQ2ISR,
	&GPIOPortQ3ISR,
	&GPIOPortQ4ISR,
	&GPIOPortQ5ISR,
	&GPIOPortQ6ISR,
	&GPIOPortQ7ISR,
	&GPIOPortRISR,
	&GPIOPortSISR,
	&SHA_MD50ISR,
	&AES0ISR,
	&DES3DES0ISR,
	&LCDController0ISR,
	&Timer6SubtimerAISR,
	&Timer6SubtimerBISR,
	&Timer7SubtimerAISR,
	&Timer7SubtimerBISR,
	&I2C6MasterSlaveISR,
	&I2C7MasterSlaveISR,
	&HIMScanMatrixKeyboard0ISR,
	&OneWire0ISR,
	&HIMPS_20ISR,
	&HIMLEDSequencer0ISR,
	&HIMConsumerIR0ISR,
	&I2C8MasterSlaveISR,
	&I2C9MasterSlaveISR,
	&GPIOPortTISR,
};

void SystemInit();
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.
	#ifdef sram_layout
	asm ("ldr sp, =_estack");
	#endif

	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	SystemInit();
	__libc_init_array();
	(void)main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	//If you get stuck here, your code is missing a handler for some interrupt.
	//Define a 'DEBUG_DEFAULT_INTERRUPT_HANDLERS' macro via VisualGDB Project Properties and rebuild your project.
	//This will pinpoint a specific missing vector.
	for (;;) ;
}
