#include "W5500.h"

namespace MISL
{
    W5500::W5500(IReadWriteDevice<uint8_t>* device)
    {
        m_w5500Interface = device;
    }


    W5500::~W5500()
    {
    }
    
    
    bool W5500::initChip(const std::vector<uint8_t>& txsize, const std::vector<uint8_t>& rxsize)
    {
        int8_t tmp = 0;
        
        resetChip();
        
        for (uint8_t value : txsize)
        {
            tmp += value;
        }
        if (tmp > 16)
        {
            return false;
        }
        for (int i = 0; i < txsize.size(); i++)
        {
            writeRegister(Sn_TXBUF_SIZE(i), txsize[i]);
        }
        
        tmp = 0;
        for (uint8_t value : rxsize)
        {
            tmp += value;
        }
        if (tmp > 16)
        {
            return false;
        }
        for (int i = 0; i < rxsize.size(); i++)
        {
            writeRegister(Sn_RXBUF_SIZE(i), rxsize[i]);
        }
        
        return true;
    }
    
    
    void W5500::resetChip()
    {
        std::vector <uint8_t> gw = { 0x00, 0x00, 0x00, 0x00 };
        std::vector <uint8_t> mac = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        
        writeRegisters(SHAR, mac);
        gw = readRegisters(GAR, 4);
        gw = readRegisters(SUBR, 4);
        gw = readRegisters(SIPR, 4);
        
        writeRegister(MR, MR_RST);
        readRegister(MR);
        
        writeRegisters(SHAR, mac);
        writeRegisters(GAR, gw);
        writeRegisters(SUBR, gw);
        writeRegisters(SIPR, gw);
    }
    
    
    void W5500::resetPHY()
    {
        uint8_t tmp = readRegister(PHYCFGR);
        tmp &= PHYCFGR_RST;
        
        writeRegister(PHYCFGR, tmp);
        tmp = readRegister(PHYCFGR);
        tmp |= ~PHYCFGR_RST;
        
        writeRegister(PHYCFGR, tmp);
    }
    
    
    std::string W5500::deviceName()
    {
        return WIZCHIP_ID;
    }
    
        
    W5500InterruptType W5500::interrupt()
    {
        uint8_t ir = 0, sir = 0, ret = 0;
        
        ir = readRegister(IR) & 0xF0;
        sir = readRegister(SIR);
        
        ret = sir;
        ret = (ret << 8) + ir;
        
        return (W5500InterruptType)ret;
    }
    
    
    void W5500::clearInterrupt(const W5500InterruptType& interrupt)
    {
        uint8_t ir = (uint8_t)interrupt;
        uint8_t sir = (uint8_t)((uint16_t)interrupt >> 8);
        
        writeRegister(IR, (ir & 0xF0));
        writeRegister(SIR, sir);
    }
    
           
    W5500InterruptType W5500::interruptMask()
    {
        uint8_t imr = 0, simr = 0, ret = 0;
        
        imr = readRegister(IMR);
        simr = readRegister(SIMR);
        
        ret = simr;
        ret = (ret << 8) + imr;
        
        return (W5500InterruptType)ret;
    }
    
    
    void W5500::setInterruptMask(const W5500InterruptType& mask)
    {
        uint8_t imr = (uint8_t)mask;
        uint8_t simr = (uint8_t)((uint16_t)mask >> 8);
        
        writeRegister(IMR, imr);
        writeRegister(SIMR, simr);
    }
        
    
    uint16_t W5500::interruptInterval()
    {
        
    }
    
    
    void W5500::interruptInterval(const uint16_t& interval)
    {
        
    }
        
    
    PHYConfigurationInfo W5500::PHYStatus()
    {
        PHYConfigurationInfo info;
        uint8_t tmp = readRegister(PHYCFGR);
        
        info.duplex = (tmp & PHYCFGR_DPX_FULL) ? PHY_DUPLEX_FULL : PHY_DUPLEX_HALF;
        info.speed  = (tmp & PHYCFGR_SPD_100) ? PHY_SPEED_100 : PHY_SPEED_10;
        
        return info;
    }
        
    
    PHYConfigurationInfo W5500::PHYConfiguration()
    {
        uint8_t tmp = 0;
        PHYConfigurationInfo info;
        
        tmp = readRegister(PHYCFGR);
        info.by   = (tmp & PHYCFGR_OPMD) ? PHY_CONFBY_SW : PHY_CONFBY_HW;
        switch (tmp & PHYCFGR_OPMDC_ALLA)
        {
        case PHYCFGR_OPMDC_ALLA:
        case PHYCFGR_OPMDC_100FA: 
            info.mode = PHY_MODE_AUTONEGO;
            break;
        default:
            info.mode = PHY_MODE_MANUAL;
            break;
        }
        switch (tmp & PHYCFGR_OPMDC_ALLA)
        {
        case PHYCFGR_OPMDC_100FA:
        case PHYCFGR_OPMDC_100F:
        case PHYCFGR_OPMDC_100H:
            info.speed = PHY_SPEED_100;
            break;
        default:
            info.speed = PHY_SPEED_10;
            break;
        }
        switch (tmp & PHYCFGR_OPMDC_ALLA)
        {
        case PHYCFGR_OPMDC_100FA:
        case PHYCFGR_OPMDC_100F:
        case PHYCFGR_OPMDC_10F:
            info.duplex = PHY_DUPLEX_FULL;
            break;
        default:
            info.duplex = PHY_DUPLEX_HALF;
            break;
        }       
        
        return info;
    }
    
    
    void W5500::setPHYConfiguration(const PHYConfigurationInfo& config)
    {
        uint8_t tmp = 0;
        if (config.by == PHY_CONFBY_SW)
            tmp |= PHYCFGR_OPMD;
        else
            tmp &= ~PHYCFGR_OPMD;
        if (config.mode == PHY_MODE_AUTONEGO)
            tmp |= PHYCFGR_OPMDC_ALLA;
        else
        {
            if (config.duplex == PHY_DUPLEX_FULL)
            {
                if (config.speed == PHY_SPEED_100)
                    tmp |= PHYCFGR_OPMDC_100F;
                else
                    tmp |= PHYCFGR_OPMDC_10F;
            }   
            else
            {
                if (config.speed == PHY_SPEED_100)
                    tmp |= PHYCFGR_OPMDC_100H;
                else
                    tmp |= PHYCFGR_OPMDC_10H;
            }
        }
        
        writeRegister(PHYCFGR, tmp);
        resetPHY();
    }
    
        
    uint8_t W5500::PHYPowerMode()
    {
        int8_t tmp = 0;
        if (readRegister(PHYCFGR) & PHYCFGR_OPMDC_PDOWN)
        {
            tmp = PHY_POWER_DOWN;
        }
        else
        {
            tmp = PHY_POWER_NORM;
        }
        
        return tmp;
    }
    
    
    bool W5500::setPHYPowerMode(const uint8_t& mode)
    {
        uint8_t tmp = 0;
        tmp = readRegister(PHYCFGR);
        if ((tmp & PHYCFGR_OPMD) == 0) return -1;
        tmp &= ~PHYCFGR_OPMDC_ALLA;         
        if (mode == PHY_POWER_DOWN)
            tmp |= PHYCFGR_OPMDC_PDOWN;
        else
            tmp |= PHYCFGR_OPMDC_ALLA;
        writeRegister(PHYCFGR, tmp);
        resetPHY();
        tmp = readRegister(PHYCFGR);
        if (mode == PHY_POWER_DOWN)
        {
            if (tmp & PHYCFGR_OPMDC_PDOWN) return 0;
        }
        else
        {
            if (tmp & PHYCFGR_OPMDC_ALLA) return 0;
        }

        return -1;        
    }
        
    
    NetModeType W5500::networkMode()
    {
        return (NetModeType)readRegister(MR);
    }
    
    
    void W5500::setNetworkMode(const NetModeType& mode)
    {
        uint8_t tmp = 0;
        tmp = readRegister(MR);
        tmp |= (uint8_t)mode;
        writeRegister(MR, tmp);
    }
    
        
    NetworkInformation W5500::networkInfo()
    {
        NetworkInformation info;
        info.mac = readRegisters(SHAR, 6);
        info.gw = readRegisters(GAR, 4);
        info.sn = readRegisters(SUBR, 4);
        info.ip = readRegisters(SIPR, 4);
        return info;
    }
    
    
    void W5500::setNetworkInfo(const NetworkInformation& info)
    {
        if (info.mac.size())
        {
            writeRegisters(SHAR, info.mac);
        }
        if (info.gw.size())
        {
            writeRegisters(GAR, info.gw);            
        }
        if (info.sn.size())
        {
            writeRegisters(SUBR, info.sn);            
        }
        if (info.ip.size())
        {
            writeRegisters(SIPR, info.ip);                 
        }
    }
    
        
    uint8_t W5500::linkStatus()
    {
        int8_t tmp;
        
        if (readRegister(PHYCFGR) & PHYCFGR_LNK_ON)
        {
            tmp = PHY_LINK_ON;
        }
        else
        {
            tmp = PHY_LINK_OFF;
        }
        
        return tmp;
    }
        
    
    W5500NetTimeout W5500::retryTimeout()
    {
        W5500NetTimeout timeout;
        
        timeout.retry_cnt = readRegister(RCR);
        timeout.time_100us = (readRegister(RTR) << 8) + readRegister(WIZCHIP_OFFSET_INC(RTR, 1));
        
        return timeout;
    }
    
    
    void W5500::setRetryTimeout(const W5500NetTimeout& timeout)
    {
        writeRegister(RCR, timeout.retry_cnt);
        writeRegister(RTR, (uint8_t)(timeout.time_100us >> 8));
        writeRegister(WIZCHIP_OFFSET_INC(RTR, 1), (uint8_t)timeout.time_100us);
    }
    
    
    uint8_t W5500::readRegister(const uint32_t& address)
    {
        uint32_t startAddress = address;
        uint8_t result;
        
        if (m_w5500Interface == nullptr)
        {
            //No interface defined. This class needs an IReadWriteDevice<T> to operate properly.
            return 0;
        }
        
        if (m_enterCriticalFunction != nullptr)
        {
            m_enterCriticalFunction();
        }
        
        m_w5500Interface->open();
    
        startAddress |= (W5500_SPI_READ | W5500_SPI_VDM_OP);
        
        m_w5500Interface->write((startAddress & 0x00FF0000) >> 16);
        m_w5500Interface->write((startAddress & 0x0000FF00) >> 8);
        m_w5500Interface->write((startAddress & 0x000000FF) >> 0);        
        
        result = m_w5500Interface->read();
        
        m_w5500Interface->close();
            
        if (m_exitCriticalFunction != nullptr)
        {
            m_exitCriticalFunction();
        }
        
        return result; 
    }
    
    
    void W5500::writeRegister(const uint32_t& address, const uint8_t& value)
    {      
        uint32_t startAddress = address;
        
        if (m_w5500Interface == nullptr)
        {
            //No interface defined. This class needs an IReadWriteDevice<T> to operate properly.
            return;
        }
        
        if (m_enterCriticalFunction != nullptr)
        {
            m_enterCriticalFunction();
        }
        
        m_w5500Interface->open();
    
        startAddress |= (W5500_SPI_WRITE | W5500_SPI_VDM_OP);
        
        m_w5500Interface->write((startAddress & 0x00FF0000) >> 16);
        m_w5500Interface->write((startAddress & 0x0000FF00) >> 8);
        m_w5500Interface->write((startAddress & 0x000000FF) >> 0);        
        m_w5500Interface->write(value);
        
        m_w5500Interface->close();
            
        if (m_exitCriticalFunction != nullptr)
        {
            m_exitCriticalFunction();
        }       
    }
        
    
    std::vector<uint8_t> W5500::readRegisters(const uint32_t& address, const uint16_t& count)
    {
        uint32_t startAddress = address;
        std::vector<uint8_t> result;
        
        if (m_w5500Interface == nullptr)
        {
            //No interface defined. This class needs an IReadWriteDevice<T> to operate properly.
            return result;
        }
        
        if (m_enterCriticalFunction != nullptr)
        {
            m_enterCriticalFunction();
        }
        
        m_w5500Interface->open();
    
        startAddress |= (W5500_SPI_READ | W5500_SPI_VDM_OP);
        
        m_w5500Interface->write((startAddress & 0x00FF0000) >> 16);
        m_w5500Interface->write((startAddress & 0x0000FF00) >> 8);
        m_w5500Interface->write((startAddress & 0x000000FF) >> 0);        
        
        for (int i = 0; i < count; i++)
        {
            result.push_back(m_w5500Interface->read());   
        }
        
        m_w5500Interface->close();
            
        if (m_exitCriticalFunction != nullptr)
        {
            m_exitCriticalFunction();
        }
        
        return result; 
    }
    
    
    void W5500::writeRegisters(const uint32_t& address, const std::vector<uint8_t>& buffer)
    {
        uint32_t startAddress = address;
        
        if (m_w5500Interface == nullptr)
        {
            //No interface defined. This class needs an IReadWriteDevice<T> to operate properly.
            return;
        }
        
        if (m_enterCriticalFunction != nullptr)
        {
            m_enterCriticalFunction();
        }
        
        m_w5500Interface->open();
    
        startAddress |= (W5500_SPI_WRITE | W5500_SPI_VDM_OP);
        
        m_w5500Interface->write((startAddress & 0x00FF0000) >> 16);
        m_w5500Interface->write((startAddress & 0x0000FF00) >> 8);
        m_w5500Interface->write((startAddress & 0x000000FF) >> 0);    
        
        for (uint8_t value : buffer)
        {
            m_w5500Interface->write(value);
        }
        
        m_w5500Interface->close();
            
        if (m_exitCriticalFunction != nullptr)
        {
            m_exitCriticalFunction();
        }             
    }
    
    
}


