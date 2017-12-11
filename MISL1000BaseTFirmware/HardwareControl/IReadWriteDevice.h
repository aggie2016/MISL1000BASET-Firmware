#ifndef IREADWRITE_H
#define IREADWRITE_H

namespace MISL
{
    
    template <typename ReadWriteType>
    class IReadWriteDevice
    {
        public:
            IReadWriteDevice()
            {
            
            }
        
        
            virtual ~IReadWriteDevice()
            {
            
            }
    
            virtual ReadWriteType read() = 0;
            virtual bool write(const ReadWriteType &value)
            {
                //Function must be implemented in derived class for writing values
                return false;
            }
    
            virtual bool open() = 0;
            virtual bool close() = 0;
    };
    
}




#endif // IREADWRITE_H


