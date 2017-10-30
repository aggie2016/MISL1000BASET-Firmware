#include "HardwareRegister.h"

RegisterValue::RegisterValue(uint8_t startBit,
    uint8_t endBit,
    std::string description, 
    PermissionType type,
    HardwareRegister *parent,
    SpecialProperties specialProperty)
    : m_startBit(startBit)
    , m_endBit(endBit)
    , m_description(description)
    , m_permission(type)
    , m_parent(parent)
    , m_updateDelegate(getStandardValue)
    , m_properties(specialProperty)
{
    m_parent->m_values.push_back(this);
}


RegisterValue::RegisterValue(uint8_t startBit,
    uint8_t endBit,
    std::string description, 
    PermissionType type,
    HardwareRegister *parent,
    std::function<uint32_t(RegisterValue*)> updateFunction,
    SpecialProperties specialProperty)
    : m_startBit(startBit)
    , m_endBit(endBit)
    , m_description(description)
    , m_permission(type)
    , m_parent(parent)
    , m_updateDelegate(updateFunction)
    , m_properties(specialProperty)
{
    m_parent->m_values.push_back(this);
}


uint32_t RegisterValue::value()
{
    if (m_updateDelegate)
    {
        return m_updateDelegate(this);
    }
    else
    {
        return 0;   
    }
}


HardwareRegister* RegisterValue::parent()
{
    return m_parent;
}

uint8_t RegisterValue::startBit()
{
    return m_startBit;
}


uint8_t RegisterValue::endBit()
{
    return m_endBit;
}


std::string RegisterValue::description()
{
    return m_description;   
}


PermissionType RegisterValue::permission()
{
    return m_permission;
}




HardwareRegister::HardwareRegister(uint32_t baseAddr, uint16_t size, std::string name)
    : m_name(name),
    m_baseAddress(baseAddr),
    m_size(size),
    m_lastValue(0)
{
}

uint32_t HardwareRegister::baseAddress()
{
    return m_baseAddress;
}


uint32_t HardwareRegister::value()
{
    return m_lastValue;
}


uint16_t HardwareRegister::sizeInBytes()
{
    return m_size;
}


std::string HardwareRegister::name()
{
    return m_name;
}

void HardwareRegister::update()
{
    updateValue(this);
}

void HardwareRegister::updateValue(HardwareRegister* reg)
{
    //reg->m_lastValue = NEXT N registers in HardwareRegister
}


void HardwareRegister::updateAllValues(HardwareRegister* reg)
{
    /* 
     * Update main register value from SSI port. This will be used
     * to calculate all of the child registers.
     */
    updateValue(reg);
    
    for (RegisterValue *value : reg->m_values)
    {
        //Update each register segement in order to construct the register as a whole
        reg->m_lastValue |= value->value();
    }
}