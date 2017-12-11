#include "Socket.h"
#include "SystemObjects/HelperFunctions.h"


namespace MISL
{
    
    Socket::Socket(uint8_t sn, SocketType type, uint16_t port, uint8_t flag, W5500* wizchipDevice)
        : m_socketNumber(sn)
        , m_type(type)
        , m_port(port)
        , m_wizchipDevice(wizchipDevice)        
    {
        close();
        
        if (wizchipDevice != nullptr)
        {
            wizchipDevice->writeRegister(Sn_MR(sn), (HelperFunctions::enumToType(type) | (flag & 0xF0)));
        }

        if (!port)
        {
            port = sock_any_port++;
            if (sock_any_port == 0xFFF0)
                sock_any_port = SOCK_ANY_PORT_NUM;
        }
        
        if (wizchipDevice != nullptr)
        {
            wizchipDevice->writeRegister(Sn_PORT(sn), (uint8_t)(port >> 8));
            wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_PORT(sn), 1), (uint8_t)port);
            
            wizchipDevice->writeRegister(Sn_CR(sn), Sn_CR_OPEN);
            
            while (wizchipDevice->readRegister(Sn_CR(sn)));
            
            m_socketIOMode |= ((flag & SF_IO_NONBLOCK) << sn);
            m_socketIsSending &= ~(1 << sn);
            
            while (wizchipDevice->readRegister(Sn_SR(sn)) == SOCK_CLOSED);
        }       
    }


    Socket::~Socket()
    {
        if (isOpen())
        {
            close();
        }
    }
    
    
    uint8_t Socket::socketNumber()
    {
        return m_socketNumber;
    }
    
    
    uint16_t Socket::port()
    {
        return m_port;
    }
    
    
    SocketType Socket::type()
    {
        return m_type;
    }
        
    SocketError Socket::close()
    {
        SocketError result = CHECK_SOCKNUM();  
        if (result != SocketError::NoError)
        {
            return result;
        }
        
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_CLOSE);
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));
        
        m_wizchipDevice->writeRegister(Sn_IR(m_socketNumber), (0xFF & 0x1F));
        m_socketIsSending &= ~(1 << m_socketNumber);
        
        while (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber)) != SOCK_CLOSED);
        
        return SocketError::NoError;
    }
    

    bool Socket::isOpen()
    {
        return true;
    }    
    
    
    SocketError Socket::listen()
    {
        SocketError result = CHECK_SOCKNUM();  
        if (result != SocketError::NoError)
        {
            return result;
        }
        
        result = CHECK_SOCKMODE(m_type);  
        if (result != SocketError::NoError)
        {
            return result;
        }
        
        result = CHECK_SOCKINIT();  
        if (result != SocketError::NoError)
        {
            return result;
        }
        
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_LISTEN);
        while(m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));;
        
        while (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber)) != SOCK_LISTEN)
        {
            if (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)) == SOCK_CLOSED)
            {
                close();
                return SocketError::SocketClosedUnexpectedly;
            }
            
        }
        
        return SocketError::NoError;
    }
    
    
    SocketError Socket::connect(const std::vector<uint8_t>& address, uint16_t port)
    {
        SocketError result = CHECK_SOCKNUM();
        if (result != SocketError::NoError)
        {
            return result;
        }
        result = CHECK_SOCKMODE((SocketType)Sn_MR_TCP);
        if (result != SocketError::NoError)
        {
            return result;
        }
        result = CHECK_SOCKINIT();
        if (result != SocketError::NoError)
        {
            return result;
        }
        
        if (address.size() < 4)
        {
            return SocketError::InvalidIPAddress;
        }
        
        uint32_t targetAddress;
        targetAddress = ((uint32_t)address[0] & 0x000000FF);
        targetAddress = (targetAddress << 8) + ((uint32_t)address[1] & 0x000000FF);
        targetAddress = (targetAddress << 8) + ((uint32_t)address[2] & 0x000000FF);
        targetAddress = (targetAddress << 8) + ((uint32_t)address[3] & 0x000000FF);
        if (targetAddress == 0xFFFFFFFF || targetAddress == 0)
        {
            return SocketError::InvalidIPAddress;
        }
        
        if (port == 0)
        {
            return SocketError::PortNumberZeroProvided;
        }
        
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }       
        
        //Register target IP address with W5500 socket specified
        m_wizchipDevice->writeRegisters(Sn_DIPR(m_socketNumber), address);
        
        //Register target port number with W5500 socket specified
        m_wizchipDevice->writeRegister(Sn_DPORT(m_socketNumber), (uint8_t)(port >> 8));
        m_wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_DPORT(m_socketNumber), 1), (uint8_t)port);
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_CONNECT);
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));
        
        if (m_socketIOMode & (1 << m_socketNumber))
        {
            return SocketError::SocketBusy;
        }
        
        while (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber)) != SOCK_ESTABLISHED)
        {
            if ((m_wizchipDevice->readRegister(Sn_IR(m_socketNumber)) & 0x1F) & Sn_IR_TIMEOUT)
            {
                m_wizchipDevice->writeRegister(Sn_IR(m_socketNumber) & 0x1F, Sn_IR_TIMEOUT);
                
                return SocketError::TimeoutOccurred;
            }            
        }
        
        return SocketError::NoError;
    }
    
    
    SocketError Socket::disconnect()
    {
        SocketError result = CHECK_SOCKNUM();
        if (result != SocketError::NoError)
        {
            return result;
        }
        result = CHECK_SOCKMODE((SocketType)Sn_MR_TCP);
        if (result != SocketError::NoError)
        {
            return result;
        }    
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }              
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_DISCON);  
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));
        
        m_socketIsSending &= ~(1 << m_socketNumber);
        
        if (m_socketIOMode & (1 << m_socketNumber))
        {
            return SocketError::SocketBusy;
        }
        
        while (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber)) != SOCK_CLOSED)
        {
            if ((m_wizchipDevice->readRegister(Sn_IR(m_socketNumber)) & 0x1F) & Sn_IR_TIMEOUT)
            {
                close();
                return SocketError::TimeoutOccurred;
            }
        }
        
        return SocketError::NoError;
    }
        
    int32_t Socket::send(const std::vector<uint8_t>& data, uint16_t length)
    {
        uint8_t tmp = 0;
        uint16_t freesize = 0;
        
        SocketError result = CHECK_SOCKNUM();
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        result = CHECK_SOCKMODE((SocketType)Sn_MR_TCP);
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        result = CHECK_SOCKDATA(length);
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        
        if (m_wizchipDevice == nullptr)
        {
            return (int32_t)SocketError::NoWizchipDeviceProvided;    
        }              
        
        tmp = m_wizchipDevice->readRegister(Sn_SR(m_socketNumber));
        if (tmp != SOCK_ESTABLISHED && tmp != SOCK_CLOSE_WAIT)
        {
            return (int32_t)SocketError::InvalidSocketStatus;
        }
        
        if (m_socketIsSending & (1 << m_socketNumber))
        {
            tmp = (m_wizchipDevice->readRegister(Sn_IR(m_socketNumber)) & 0x1F);
            if (tmp & Sn_IR_SENDOK)
            {
                m_wizchipDevice->writeRegister(Sn_IR(m_socketNumber), (Sn_IR_SENDOK & 0x1F));
                m_socketIsSending &= ~(1 << m_socketNumber);
            }
            else if (tmp & Sn_IR_TIMEOUT)
            {
                close();
                return (int32_t)SocketError::TimeoutOccurred;
            }
            else return (int32_t)SocketError::SocketBusy;
        }
        
        freesize = m_wizchipDevice->readRegister(Sn_TXBUF_SIZE(m_socketNumber)) << 10;
        if (length > freesize)
        {
            length = freesize;
        }
        
        while (1)
        {
            freesize = getSn_TX_FSR(m_socketNumber);
            tmp = m_wizchipDevice->readRegister(Sn_SR(m_socketNumber));
            if ((tmp != SOCK_ESTABLISHED) && (tmp != SOCK_CLOSE_WAIT))
            {
                close();
                return (int32_t)SocketError::InvalidSocketStatus;
            }
            if ((m_socketIOMode & (1 << m_socketNumber)) && (length > freesize))
            {
                return (int32_t)SocketError::SocketBusy;
            }
            if (length <= freesize)
            {
                break;
            }
        }
           
        sendData(data);
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_SEND);  
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));
        
        m_socketIsSending |= (1 << m_socketNumber);
        
        return length;
    }
    
    
    int32_t Socket::receive(std::vector<uint8_t>& data, uint16_t length)
    {
        uint8_t tmp = 0;
        uint16_t receiveSize = 0;
        
        SocketError result = CHECK_SOCKNUM();
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        result = CHECK_SOCKMODE((SocketType)Sn_MR_TCP);
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        result = CHECK_SOCKDATA(length);
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        
        if (m_wizchipDevice == nullptr)
        {
            return (int32_t)SocketError::NoWizchipDeviceProvided;    
        }    
        
        receiveSize = m_wizchipDevice->readRegister(Sn_RXBUF_SIZE(m_socketNumber)) << 10;
        if (receiveSize < length)
        {
            length = receiveSize;
        }
        
        while (1)
        {       
            receiveSize = getSn_RX_RSR(m_socketNumber);
            tmp = m_wizchipDevice->readRegister(Sn_SR(m_socketNumber));
        
            if (tmp != SOCK_ESTABLISHED)
            {
                if (tmp == SOCK_CLOSE_WAIT)
                {
                    if (receiveSize != 0)
                    {
                        break;
                    }
                    else if (getSn_TX_FSR(m_socketNumber) == (m_wizchipDevice->readRegister(Sn_TXBUF_SIZE(m_socketNumber)) << 10))
                    {
                        close();
                        return (int32_t)SocketError::InvalidSocketStatus;
                    }
                }
                else
                {
                    close();
                    return (int32_t)SocketError::InvalidSocketStatus;
                }  
            }
            if ((m_socketIOMode & (1 << m_socketNumber)) & (receiveSize == 0))
            {
                return (int32_t)SocketError::SocketBusy;
            }
            if (receiveSize != 0)
            {
                break;
            }          
        }
        
        if (receiveSize < length)
        {
            length = receiveSize;
        }
        receiveData(data, length);
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_RECV);  
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));        
        
        return length;
        
    }
        
    int32_t Socket::sendTo(const std::vector<uint8_t>& data, uint16_t length, const std::vector<uint8_t>& address, uint16_t port)
    {
        uint8_t tmp = 0;
        uint16_t freesize = 0;        
        
        SocketError result = CHECK_SOCKNUM();
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }      
        if (m_wizchipDevice == nullptr)
        {
            return (int32_t)SocketError::NoWizchipDeviceProvided;    
        }    
        
        switch (m_wizchipDevice->readRegister(Sn_MR(m_socketNumber)) & 0x0F)
        {
            case Sn_MR_UDP:
            case Sn_MR_MACRAW:
                break;
            default:
                return (int32_t)SocketError::InvalidSocketMode;
        }
        
        result = CHECK_SOCKDATA(length);
        if (result != SocketError::NoError)
        {
            return (int32_t)result;
        }
        
        if (address.size() < 4)
        {
            return (int32_t)SocketError::InvalidIPAddress;
        }
        
        if (port == 0)
        {
            tmp = m_wizchipDevice->readRegister(Sn_SR(m_socketNumber));
        }
        if (tmp != SOCK_MACRAW && tmp != SOCK_UDP)
        {
            return (int32_t)SocketError::InvalidSocketStatus;
        }
        
        m_wizchipDevice->writeRegisters(Sn_DIPR(m_socketNumber), address);

        m_wizchipDevice->writeRegister(Sn_DPORT(m_socketNumber), (uint8_t)(port >> 8));
        m_wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_DPORT(m_socketNumber), 1), (uint8_t)  port);  
        
        freesize = m_wizchipDevice->readRegister(Sn_TXBUF_SIZE(m_socketNumber)) << 10;
        
        if (length > freesize)
        {
            length = freesize;
        }
        
        while (1)
        {
            freesize = getSn_TX_FSR(m_socketNumber);
            if (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber)) == SOCK_CLOSED)
            {
                return (int32_t)SocketError::SocketClosedUnexpectedly;
            }
            if ((m_socketIOMode & (1 << m_socketNumber)) && (length > freesize))
            {
                return (int32_t)SocketError::SocketBusy;
            }
            if (length < freesize)
            {
                break;
            }
        }
        
        sendData(data);
        
        m_wizchipDevice->writeRegister(Sn_CR(m_socketNumber), Sn_CR_SEND);
        
        while (m_wizchipDevice->readRegister(Sn_CR(m_socketNumber)));
        
        while (1)
        {
            tmp = (m_wizchipDevice->readRegister(Sn_IR(m_socketNumber)) & 0x1F);
            if (tmp & Sn_IR_SENDOK)
            {
                m_wizchipDevice->writeRegister(Sn_IR(m_socketNumber), (Sn_IR_SENDOK & 0x1F));
                break;
            }
            else if (tmp & Sn_IR_TIMEOUT)
            {
                m_wizchipDevice->writeRegister(Sn_IR(m_socketNumber), (Sn_IR_TIMEOUT & 0x1F));    
                return (int32_t)SocketError::TimeoutOccurred;
            }
        }
        
        return length;
    }
    
    
    int32_t Socket::receiveFrom(std::vector<uint8_t>& data, uint16_t length, const std::vector<uint8_t>& address, uint16_t port)
    {
        
    }
    
    
    uint16_t Socket::getSn_TX_FSR(uint8_t sn)
    {
        uint16_t val = 0, val1 = 0;
        
        if (m_wizchipDevice == nullptr)
        {
            return -1;    
        }              
        
        do
        {
            val1 = m_wizchipDevice->readRegister(Sn_TX_FSR(sn));
            val1 = (val1 << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn), 1));
            if (val1 != 0)
            {
                val = m_wizchipDevice->readRegister(Sn_TX_FSR(sn));
                val = (val << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn), 1));
            }
        } while (val != val1);

        return val;
    }





    uint16_t Socket::getSn_RX_RSR(uint8_t sn)
    {
        uint16_t val = 0, val1 = 0;
        
        do
        {
            val1 = m_wizchipDevice->readRegister(Sn_RX_RSR(sn));
            val1 = (val1 << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn), 1));
            if (val1 != 0)
            {
                val = m_wizchipDevice->readRegister(Sn_RX_RSR(sn));
                val = (val << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn), 1));
            }
        } while (val != val1);

        return val;
    }
    
    
    
    SocketError Socket::CHECK_SOCKNUM()
    {
        if (m_socketNumber > WIZCHIP_SOCK_NUM)
            return SocketError::InvalidSocketNumber;    
        return SocketError::NoError;
    }
    
    
    SocketError Socket::CHECK_SOCKMODE(SocketType mode)
    {
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }      
        
        if (m_wizchipDevice->readRegister(Sn_MR(m_socketNumber) & 0x0F) != (uint16_t)mode)
        {
            return SocketError::InvalidSocketMode;
        }
        
        return SocketError::NoError;
    }
    
    
    SocketError Socket::CHECK_SOCKINIT()
    {
        if (m_wizchipDevice == nullptr)
        {
            return SocketError::NoWizchipDeviceProvided;    
        }     
        
        if (m_wizchipDevice->readRegister(Sn_SR(m_socketNumber) != SOCK_INIT))
        {
            return SocketError::SocketNotInitialized;
        }        
        
        return SocketError::NoError;
    }
    
    
    SocketError Socket::CHECK_SOCKDATA(uint32_t length)
    {
        if (length == 0)
        {
            return SocketError::DataLengthError;
        }
        
        return SocketError::NoError;
    }
    
    
    void Socket::sendData(const std::vector<uint8_t>& data)
    {
        uint16_t ptr = 0;
        uint32_t addrsel = 0;

        if (data.size() == 0)
        {
            return;
        }
        
        ptr = (m_wizchipDevice->readRegister(Sn_TX_WR(m_socketNumber)) << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_TX_WR(m_socketNumber), 1));
        
        addrsel = ((uint32_t)ptr << 8) + (WIZCHIP_TXBUF_BLOCK(m_socketNumber) << 3);
        
        m_wizchipDevice->writeRegisters(addrsel, data);
        
        ptr += data.size();

        m_wizchipDevice->writeRegister(Sn_TX_WR(m_socketNumber), (uint8_t)(ptr >> 8));
        m_wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_TX_WR(m_socketNumber), 1), (uint8_t) ptr);
    }
    
    
    void Socket::receiveData(std::vector<uint8_t>& buffer, uint16_t length)
    {
        uint16_t ptr = 0;
        uint32_t addrsel = 0;

        if (length == 0)
        {
            return;
        }
        
        ptr = ((m_wizchipDevice->readRegister(Sn_RX_RD(m_socketNumber)) << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_RX_RD(m_socketNumber), 1)));
        addrsel = ((uint32_t)ptr << 8) + (WIZCHIP_RXBUF_BLOCK(m_socketNumber) << 3);
        
        buffer = m_wizchipDevice->readRegisters(addrsel, length);
        ptr += length;
        
        m_wizchipDevice->writeRegister(Sn_RX_RD(m_socketNumber), (uint8_t)(ptr >> 8));
        m_wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_RX_RD(m_socketNumber), 1), (uint8_t) ptr);
    }
    
    
    void Socket::receiveIgnore(uint16_t length)
    {
        uint16_t ptr = 0;
        
        ptr = ((m_wizchipDevice->readRegister(Sn_RX_RD(m_socketNumber)) << 8) + m_wizchipDevice->readRegister(WIZCHIP_OFFSET_INC(Sn_RX_RD(m_socketNumber), 1)));
        ptr += length;
        
        m_wizchipDevice->writeRegister(Sn_RX_RD(m_socketNumber), (uint8_t)(ptr >> 8));
        m_wizchipDevice->writeRegister(WIZCHIP_OFFSET_INC(Sn_RX_RD(m_socketNumber), 1), (uint8_t) ptr);
    }
    
}

