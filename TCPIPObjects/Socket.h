#ifndef SOCKET_H
#define SOCKET_H

#include "HardwareControl/W5500.h"

namespace MISL
{
    
    #define SOCK_IO_BLOCK           0     ///< Socket Block IO Mode in @ref setsockopt().
    #define SOCK_IO_NONBLOCK        1     ///< Socket Non-block IO Mode in @ref setsockopt().
    #define SF_IO_NONBLOCK          0x01  ///< Socket nonblock io mode. It used parameter in \ref socket().
    
    #define SOCK_ANY_PORT_NUM       0xC000;
    static uint16_t sock_any_port = SOCK_ANY_PORT_NUM;
    
    enum class SocketState
    {
        OK    = 1,
        BUSY  = 0,
        FATAL = -1000
    };
    
    enum class SocketError
    {
        InvalidSocketNumber = -1,
        InvalidSocketOption = -2,
        SocketNotInitialized = -3,
        SocketClosedUnexpectedly = -4,
        InvalidSocketMode = -5,
        InvalidSocketFlag = -6,
        InvalidSocketStatus = -7,
        InvalidArgument = -10,
        PortNumberZeroProvided = -11,
        InvalidIPAddress = -12,
        TimeoutOccurred = -13,
        DataLengthError = -14,
        BufferInsufficient = -15, 
        NoWizchipDeviceProvided = -16,
        SocketBusy = -17,        
        InvalidPacketLength = -1001,
        NoError = 1
    };
    
    enum class SocketType : uint8_t
    {
        TCP = 1,
        UDP,
        MACRAW
    };
   
    enum class SocketInterruptType
    {
        Connected    = (1 << 0),    ///< connected
        Disconnected = (1 << 1),    ///< disconnected
        Received     = (1 << 2),    ///< data received
        Timeout      = (1 << 3),    ///< timeout occurred
        Sent         = (1 << 4),    ///< send ok
        All          = 0x1F,        ///< all interrupt
    };    
    
class Socket
    {
    public:   
        Socket(uint8_t sn, SocketType type, uint16_t port, uint8_t flag, W5500* wizchipDevice);
        ~Socket();
        
        uint8_t socketNumber();
        uint16_t port();
        SocketType type();
        
        
        bool isOpen();
        SocketError close();        
        SocketError listen();
        SocketError connect(const std::vector<uint8_t>& address, uint16_t port);
        SocketError disconnect();
        
        int32_t send(const std::vector<uint8_t>& data, uint16_t length);
        int32_t receive(std::vector<uint8_t>& data, uint16_t length);
        
        int32_t sendTo(const std::vector<uint8_t>& data, uint16_t length, const std::vector<uint8_t>& address, uint16_t port);
        int32_t receiveFrom(std::vector<uint8_t>& data, uint16_t length, const std::vector<uint8_t>& address, uint16_t port);
        
    private:
        uint8_t m_socketNumber;
        SocketType m_type;
        uint16_t m_port;
        W5500* m_wizchipDevice;
        
        uint16_t m_socketIOMode = 0;
        uint16_t m_socketIsSending = 0;
        
        
        SocketError CHECK_SOCKNUM();
        SocketError CHECK_SOCKMODE(SocketType mode);
        SocketError CHECK_SOCKINIT();
        SocketError CHECK_SOCKDATA(uint32_t length);
        
        void sendData(const std::vector<uint8_t>& data);
        void receiveData(std::vector<uint8_t>& buffer, uint16_t length);
        void receiveIgnore(uint16_t length);
        
        uint16_t getSn_TX_FSR(uint8_t sn);
        uint16_t getSn_RX_RSR(uint8_t sn);
    };


    
}


#endif