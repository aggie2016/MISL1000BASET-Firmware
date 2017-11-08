#ifndef IREAD_WRITE_DEVICE_H
#define IREAD_WRITE_DEVICE_H

#include <cstdint>

namespace MISL
{
    class IReadWriteDevice
    {
    public:
        IReadWriteDevice();
        virtual ~IReadWriteDevice();
            
        virtual uint8_t read() = 0; 
        virtual void write(const uint8_t &data);
        
        virtual bool open() = 0;
        virtual bool close() = 0;
    };
}


#endif