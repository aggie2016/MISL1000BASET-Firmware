#ifndef HARDWARE_REGISTER_H
#define HARDWARE_REGISTER_H


#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "HardwareControl/IReadWriteDevice.h"


namespace MISL
{
    enum class PermissionType
    {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    enum class SpecialProperties
    {
        None,
        SelfClearing
    };


    class HardwareRegister;
    class RegisterValue;

    static uint32_t getStandardValue(RegisterValue* val);

    class RegisterValue
    {
    public:
        RegisterValue(uint8_t startBit,
            uint8_t endBit,
            std::string description, 
            PermissionType type,
            HardwareRegister *parent,
            SpecialProperties specialProperty = SpecialProperties::None);
    
        RegisterValue(uint8_t startBit,
            uint8_t endBit,
            std::string description, 
            PermissionType type,
            HardwareRegister *parent,
            std::function<uint32_t(RegisterValue*)> updateFunction,
            SpecialProperties specialProperty = SpecialProperties::None);
    
        uint32_t value();
        uint32_t value(uint32_t offset);
    
        HardwareRegister* parent();
        void setParent(HardwareRegister *reg);
    
        //Properties of a hardware register value used to calculate its value. Passed to the updateDelegate().
        uint8_t startBit();
        uint8_t endBit();
        std::string description();
        PermissionType permission();
    
    private:
        uint8_t m_startBit;
        uint8_t m_endBit;
        std::string m_description;
        PermissionType m_permission;
        HardwareRegister *m_parent;
        std::function<uint32_t(RegisterValue*)> m_updateDelegate;
        SpecialProperties m_properties;
    };

    class HardwareRegister
    {
    public:
        HardwareRegister(IReadWriteDevice* device, uint32_t baseAddr, uint16_t size, std::string name);
    
        uint32_t value();
        uint32_t value(uint32_t offset);
        std::string name();   
        static void AddChildRegister(HardwareRegister *reg, RegisterValue *value);
    
        friend class RegisterValue;
       
    private:
        std::string m_name;
        uint32_t m_baseAddress;
        uint16_t m_size;   
        std::vector<RegisterValue*> m_values;
        IReadWriteDevice* m_device;
    
        static uint32_t updateValue(HardwareRegister* reg);   
    };

}




//Global Registers [0x0000 - 0x00FF]

/* 5.1.1.1 - Global Chip ID 0 Register */



#endif