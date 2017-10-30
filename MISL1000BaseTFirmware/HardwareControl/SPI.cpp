#include "SPI.h"


namespace MISL
{
    SPI::SPI(SPIDevice peripheral, GPIOPin rxPin, GPIOPin txPin, GPIOPin clkPin, GPIOPin fssPin, uint32_t systemClock, uint32_t bitRate)
        : m_mutexAttached(false),
        m_mode(SPITransmissionMode::MotoMode0),
        m_peripheralBase(HelperFunctions::enumToType(m_spiDeviceMappings.at(peripheral))),
        m_systemClock(systemClock),
        m_bitRate(bitRate),
        m_fssPin(fssPin)
    {
        ROM_SysCtlPeripheralEnable(HelperFunctions::enumToType(peripheral));
        ROM_GPIOPinTypeSSI((uint32_t)txPin.port(), (uint32_t)txPin.pin());
        ROM_GPIOPinTypeSSI((uint32_t)rxPin.port(), (uint32_t)rxPin.pin());
        ROM_GPIOPinTypeSSI((uint32_t)clkPin.port(), (uint32_t)clkPin.pin());
        
        if (peripheral == SPIDevice::SPI1)
        {
            ROM_GPIOPinConfigure(GPIO_PB5_SSI1CLK);
            ROM_GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);
            ROM_GPIOPinConfigure(GPIO_PE5_SSI1XDAT1); 
        }
        else if (peripheral == SPIDevice::SPI2)
        {
            ROM_GPIOPinConfigure(GPIO_PD3_SSI2CLK);
            ROM_GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);
            ROM_GPIOPinConfigure(GPIO_PD1_SSI2XDAT0); 
        }
                
        ROM_SSIConfigSetExpClk(m_peripheralBase, systemClock, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, bitRate, 8);
        ROM_SSIEnable(m_peripheralBase);
    }


    SPI::~SPI()
    {
    }
    
    
    void SPI::setTransmissionMode(const SPITransmissionMode &mode)
    {
        ROM_SSIConfigSetExpClk(m_peripheralBase, m_systemClock, HelperFunctions::enumToType(mode), SSI_MODE_MASTER, m_bitRate, 8);
    }

    
    void SPI::setBitRate(const uint32_t &rate)
    {
        ROM_SSIConfigSetExpClk(m_peripheralBase, m_systemClock, HelperFunctions::enumToType(m_mode), SSI_MODE_MASTER, rate, 8);
    }
        
    
    void SPI::attachMutex(const RTOSMutex &mutex)
    {
        m_mutex = mutex.getHandle();
        m_blockingTime = mutex.getBlockTime();
        m_mutexAttached = true;
    }
    
    
    void SPI::detachMutex()
    {
        m_mutex = nullptr;
        m_mutexAttached = false;
    }
    
    
    void SPI::assertAction(FSSAssertAction action)
    {
        if (action == FSSAssertAction::High)
        {
            while (SSIBusy(m_peripheralBase));
            m_fssPin.write(GPIOState::HIGH);
        }
        else if (action == FSSAssertAction::Low)
        {
            while (SSIBusy(m_peripheralBase));
            m_fssPin.write(GPIOState::LOW);
        }
    }
            
    void SPI::write(const uint8_t &data)
    {       
        if (m_mutexAttached)
        {
            RTOSMutex handle(m_mutex, m_blockingTime);
            uint32_t temp;
            SSIDataPut(m_peripheralBase, data);
            SSIDataGet(m_peripheralBase, &temp);
        }
        else 
        {
            uint32_t temp;
            SSIDataPut(m_peripheralBase, data);
            SSIDataGet(m_peripheralBase, &temp);
        }    
    }
    
    
    uint8_t SPI::read()
    {
        uint32_t temp;
      
        if (m_mutexAttached)
        {
            RTOSMutex handle(m_mutex, m_blockingTime);
            SSIDataPut(m_peripheralBase, 0x00);
            SSIDataGet(m_peripheralBase, &temp);

        }
        else 
        {
            SSIDataPut(m_peripheralBase, 0x00);
            SSIDataGet(m_peripheralBase, &temp);
        }
           
        return temp & 0xFF;
    }
    
    
    std::map<SPIDevice, SPIBaseDevice> SPI::buildMap()
    {
    	//Build constant map of GPIOPorts to SystemPeripherals
        std::map<SPIDevice, SPIBaseDevice> map;
        map[SPIDevice::SPI0] = SPIBaseDevice::SPI0;
        map[SPIDevice::SPI1] = SPIBaseDevice::SPI1;
        map[SPIDevice::SPI2] = SPIBaseDevice::SPI2;
        map[SPIDevice::SPI3] = SPIBaseDevice::SPI3;
        return map;
    }
}
