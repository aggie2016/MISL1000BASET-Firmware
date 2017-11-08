#include "HardwareRegister.h"

namespace MISL
{
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
        if (m_parent)
        {
            m_parent->m_values.push_back(this);
        }
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

    uint32_t RegisterValue::value(uint32_t offset)
    {
        if (m_updateDelegate && parent())
        {
            uint32_t originalBaseAddr = parent()->m_baseAddress;
            parent()->m_baseAddress |= offset;
            uint32_t registerValue = m_updateDelegate(this);
            parent()->m_baseAddress = originalBaseAddr;
            return registerValue;
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




    HardwareRegister::HardwareRegister(IReadWriteDevice* device, uint32_t baseAddr, uint16_t size, std::string name)
        : m_name(name)
        , m_baseAddress(baseAddr)
        , m_size(size)
        , m_device(device)
    {
    }

    std::string HardwareRegister::name()
    {
        return m_name;
    }

    void HardwareRegister::AddChildRegister(HardwareRegister *reg, RegisterValue *value)
    {
        value->setParent(reg);
        reg->m_values.push_back(value);
    }

    uint32_t HardwareRegister::value()
    {
        return updateValue(this);
    }

    uint32_t HardwareRegister::value(uint32_t offset)
    {
        uint32_t originalBaseAddr = m_baseAddress;
        m_baseAddress |= offset;
        uint32_t registerValue = updateValue(this);
        m_baseAddress = originalBaseAddr;
        return registerValue;
    }

    uint32_t HardwareRegister::updateValue(HardwareRegister* reg)
    {
        uint32_t lastValue = 0;
 
        if (!reg->m_device)
        {
            //[TODO]: Throw NullExceptionError from MISL::ExceptionHandler
            return 0;
        }
    
        for (uint32_t address = reg->m_baseAddress; 
            address < (reg->m_baseAddress + reg->m_size); 
            address++)
        {
            uint32_t dataToSend = (address << 5 | 0x60000000);
            reg->m_device->open();
            reg->m_device->write((uint8_t)((dataToSend & 0xFF000000) >> 24));
            reg->m_device->write((uint8_t)((dataToSend & 0x00FF0000) >> 16));
            reg->m_device->write((uint8_t)((dataToSend & 0x0000FF00) >> 8));
            reg->m_device->write((uint8_t)((dataToSend & 0x000000FF) >> 0));
            uint32_t regValue =  (((uint32_t)reg->m_device->read()) << (((reg->m_size - 1) - (address - reg->m_baseAddress)) * 8));
            lastValue |= regValue;
            reg->m_device->close();   
        }
    
        return lastValue;
    
    }

    static uint32_t getStandardValue(RegisterValue* val)
    {
        return (val->parent()->value() & ((((1 << (val->endBit() + 1)) - 1) >> val->startBit()) << val->startBit())) >> val->startBit();
    }
}
