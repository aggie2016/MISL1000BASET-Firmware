/*
 * SSI.h
 *
 *  Created on: Mar 28, 2015
 *      Author: Christopher Miller
 */

#ifndef SPI_H
#define SPI_H

#include <map>
#include <stdint.h>
#include <stdbool.h>
#include <functional>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include <HardwareControl/GPIOPin.h>
#include <SystemObjects/SystemVariables.h>
#include <SystemObjects/RTOSMutex.h>


namespace MISL
{
    enum class SPIDevice : uint32_t
    {
        SPI0 = (uint32_t) SystemPeripheral::PERIPH_SSI0,
        SPI1 = (uint32_t) SystemPeripheral::PERIPH_SSI1,
        SPI2 = (uint32_t) SystemPeripheral::PERIPH_SSI2,
        SPI3 = (uint32_t) SystemPeripheral::PERIPH_SSI3
    };
    
    enum class SPIBaseDevice : uint32_t
    {
        SPI0 = SSI0_BASE,
        SPI1 = SSI1_BASE,
        SPI2 = SSI2_BASE,
        SPI3 = SSI3_BASE
    };
    
    enum class SPITransmissionMode : uint32_t
    {
        MotoMode0 = SSI_FRF_MOTO_MODE_0,
        MotoMode1 = SSI_FRF_MOTO_MODE_1,
        MotoMode2 = SSI_FRF_MOTO_MODE_2,
        MotoMode3 = SSI_FRF_MOTO_MODE_3,
        TI = SSI_FRF_TI,
        NMW = SSI_FRF_NMW
        
    };
    
    enum class FSSAssertAction
    {
        High,
        Low
    };
    
class SPI
    {
    public:
        SPI(SPIDevice peripheral, GPIOPin rxPin, GPIOPin txPin, GPIOPin clkPin, GPIOPin fssPin, uint32_t systemClock, uint32_t bitRate);
        ~SPI();
        
        void setTransmissionMode(const SPITransmissionMode &mode);
        void setBitRate(const uint32_t &rate);
        
        void attachMutex(const RTOSMutex &mutex);
        void detachMutex();
        
        void assertAction(FSSAssertAction action);
               
        void write(const uint8_t &data);
        uint8_t read();
        
    private:
        static std::map<SPIDevice, SPIBaseDevice> buildMap();
        const std::map<SPIDevice, SPIBaseDevice> m_spiDeviceMappings = buildMap();
    
        xSemaphoreHandle m_mutex;
        TickType_t m_blockingTime;
        bool m_mutexAttached;
        
        SPITransmissionMode m_mode;
        uint32_t m_peripheralBase;
        uint32_t m_systemClock;
        uint32_t m_bitRate;
        GPIOPin m_fssPin;

    };
    

}


#endif