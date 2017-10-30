#include "main.h"

//*****************************************************************************
//
//! Mutex to control and block access to the UART RX and TX buffers. Prevents
//! multiple FreeRTOS tasks from interacting with this interface at the same
//! time.
//
//*****************************************************************************
xSemaphoreHandle g_pUARTSemaphore;

int main(void)
{
	// Initialize system clock to 120 MHz
	g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), SYSTEM_CLOCK);
	
	// Create system mutexes
	g_pUARTSemaphore = xSemaphoreCreateMutex();
	/*
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
		
    
    //Initialize all system hardware
    if (!setupHardware())
    {
        MISL::ucout << "[ERROR]: Failed to initialize hardware resources..." << MISL::endl
                    << "\tAttempting to resolve, system will reset." << MISL::endl;
    }
    */
	//Create our base system tasks
	std::vector<ITask*> RTOSTasks;

	CLIInterpreterTask *CLI = new CLIInterpreterTask();
	BlinkLEDTask *BlinkTask = new BlinkLEDTask();
	
	RTOSTasks.push_back(CLI);
	RTOSTasks.push_back(BlinkTask);
	
    GPIOPin SPIRx(ETHOCON_SSI_RX_GPIO_PORT_BASE, ETHOCON_SSI_RX, PinDirection::HW);
    GPIOPin SPITx(ETHOCON_SSI_TX_GPIO_PORT_BASE, ETHOCON_SSI_TX, PinDirection::HW);
    GPIOPin SPIClk(ETHOCON_SSI_CLK_GPIO_PORT_BASE, ETHOCON_SSI_CLK, PinDirection::HW);
    GPIOPin SPIFss(ETHOCON_SSI_FSS_GPIO_PORT_BASE, ETHOCON_SSI_FSS, PinDirection::OUTPUT);
    
    GPIOPin WSPIRx(WIZNET_SSI_RX_GPIO_PORT_BASE, WIZNET_SSI_RX, PinDirection::HW);
    GPIOPin WSPITx(WIZNET_SSI_TX_GPIO_PORT_BASE, WIZNET_SSI_TX, PinDirection::HW);
    GPIOPin WSPIClk(WIZNET_SSI_CLK_GPIO_PORT_BASE, WIZNET_SSI_CLK, PinDirection::HW);
    GPIOPin WSPIFss(WIZNET_SSI_FSS_GPIO_PORT_BASE, WIZNET_SSI_FSS, PinDirection::OUTPUT);
    
    
    MISL::SPI ethernetController(MISL::SPIDevice::SPI1, SPIRx, SPITx, SPIClk, SPIFss, g_ui32SysClock, 1000000);
    
    MISL::SPI wiznetWebServer(MISL::SPIDevice::SPI2, WSPIRx, WSPITx, WSPIClk, WSPIFss, g_ui32SysClock, 1000000);

    
    //Procedure to connect W5500 over 100Mbps:   
    //Turn off auto-negotiation
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x40);
    ethernetController.write(0x0A);
    ethernetController.write(0x20);
    ethernetController.write(0x00);
    ethernetController.write(0x01);    
    //Manually set port speed to 100Mbps
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x40);
    ethernetController.write(0x0A);
    ethernetController.write(0x20);
    ethernetController.write(0x00);
    ethernetController.write(0x21);
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x40);
    ethernetController.write(0x0A);
    ethernetController.write(0x20);
    ethernetController.write(0x20);
    ethernetController.write(0x00);
    //Turn off auto MDI/MDI-X
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x40);
    ethernetController.write(0x0A);
    ethernetController.write(0x27);
    ethernetController.write(0x20);
    ethernetController.write(0x40);    
    //Turn on MDI-X mode
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x40);
    ethernetController.write(0x0A);
    ethernetController.write(0x27);
    ethernetController.write(0x20);
    ethernetController.write(0x40);
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    
    //Check port status
    ethernetController.assertAction(MISL::FSSAssertAction::High);
    ethernetController.assertAction(MISL::FSSAssertAction::Low);
    ethernetController.write(0x60);
    ethernetController.write(0x0A);
    ethernetController.write(0x20);
    ethernetController.write(0x60);
    uint32_t chipID = ethernetController.read();
    ethernetController.assertAction(MISL::FSSAssertAction::High);

    
    wiznetWebServer.assertAction(MISL::FSSAssertAction::High);
    wiznetWebServer.assertAction(MISL::FSSAssertAction::Low);
    wiznetWebServer.write(0x00);
    wiznetWebServer.write(0x2E);
    wiznetWebServer.write(0x00);
    uint32_t wiznetChipID = wiznetWebServer.read();
    wiznetWebServer.assertAction(MISL::FSSAssertAction::High);
    
	//Add any new CLI commands to the system here before initialization
	CLI->registerCommand(new SetPort());

    //Address is 0x5103
        
    //0000 1010 0010 0000 0110 0000  
    //0000 1010 0010 0111 0010 0000
    
	/*Start our FreeRTOS tasks
	* Normally calling startTask() would result in the specified ITask instance starting
	* immediately, however since we haven't started the FreeRTOS scheduler, the tasks 
	* will merely be created until we reach the vTaskStartScheduler statement below.
	*/
	startTasks(RTOSTasks);	
	
	
	vTaskStartScheduler();
	return 0;
	
}

bool setupHardware()
{
        	
    //Everything is configured properly
    return true;
}

void startTasks(std::vector<ITask*> taskList)
{
	for (ITask *task : taskList)
	{
		task->startTask();
	}
}