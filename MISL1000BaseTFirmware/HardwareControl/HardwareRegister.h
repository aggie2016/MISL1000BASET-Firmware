#ifndef HARDWARE_REGISTER_H
#define HARDWARE_REGISTER_H


#include <cstdint>
#include <functional>
#include <string>
#include <vector>

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
        RegisterValue(uint8_t startBit, uint8_t endBit, std::string description, 
            PermissionType type, HardwareRegister *parent, SpecialProperties specialProperty = SpecialProperties::None);
    
        RegisterValue(uint8_t startBit, uint8_t endBit, std::string description, 
                      PermissionType type, HardwareRegister *parent, std::function<uint32_t(RegisterValue*)> updateFunction, SpecialProperties specialProperty = SpecialProperties::None);
    
        uint32_t value();
        HardwareRegister* parent();
        void setParent(HardwareRegister *reg);
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
        HardwareRegister(uint32_t baseAddr, uint16_t size, std::string name);
    
        uint32_t baseAddress();
        uint32_t value();
        uint16_t sizeInBytes();
        std::string name();   
        void update();
 
        friend class RegisterValue;
    
        static void AddChildRegister(HardwareRegister *reg, RegisterValue *value)
        {
            value->setParent(reg);
            reg->m_values.push_back(value);
        }
    
    
    private:
        std::string m_name;
        uint32_t m_baseAddress;
        uint16_t m_size;
        uint32_t m_lastValue;     
        std::vector<RegisterValue*> m_values;
        static void updateValue(HardwareRegister* reg);
        static void updateAllValues(HardwareRegister* reg);
          
};

static uint32_t getStandardValue(RegisterValue* val)
{
    return (val->parent()->value() & ((((1 << (val->endBit() + 1)) - 1) >> val->startBit()) << val->startBit())) >> val->startBit();
}


//Global Registers [0x0000 - 0x00FF]

/* 5.1.1.1 - Global Chip ID 0 Register */



#endif