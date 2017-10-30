#ifndef ETHERNET_CONTROLLER_REGISTERS_H
#define ETHERNET_CONTROLLER_REGISTERS_H

#include <HardwareControl/HardwareRegister.h>

static uint32_t returnEntireRegister(RegisterValue* val)
{
    return val->parent()->value();
}


/*
 * All registers for the ethernet controller are defined here.
 * The semi automatic update mechanism requires the starting and
 * ending bit of the register value as well as a custom (or static)
 * delegate that returns the bit-manipulated value.
 *
 */
static HardwareRegister globalChipID0Register(0x0000, 1, "Global Chip ID 0");
static RegisterValue globalChipIDFixedValue(0, 7, "Fixed Value", PermissionType::ReadOnly, &globalChipID0Register, returnEntireRegister);

static HardwareRegister globalChipID1Register(0x0001, 1, "Global Chip ID 1");
static RegisterValue globalChipIDMSB(0, 7, "Chip ID (MSB)", PermissionType::ReadOnly, &globalChipID1Register, returnEntireRegister);

static HardwareRegister globalChipID2Register(0x0002, 1, "Global Chip ID 2");
static RegisterValue globalChipIDLSB(0, 7, "Chip ID (LSB)", PermissionType::ReadOnly, &globalChipID2Register, returnEntireRegister);

static HardwareRegister globalChipID3Register(0x0003, 1, "Global Chip ID 3");
static RegisterValue revisionID(4, 7, "RevisionID", PermissionType::ReadOnly, &globalChipID3Register);
static RegisterValue globalSoftwareReset(0, 0, "RevisionID", PermissionType::ReadOnly, &globalChipID3Register, SpecialProperties::SelfClearing);

static HardwareRegister PMEPinControlRegister(0x0006, 1, "PME Pin Control Register");
static RegisterValue PMEPinOutputEnable(1, 1, "PME Pin Output Enable", PermissionType::ReadWrite, &PMEPinControlRegister);
static RegisterValue PMEPinOutputPolarity(0, 0, "PME Pin Output Polarity", PermissionType::ReadWrite, &PMEPinControlRegister);

static HardwareRegister GlobalInterruptStatusRegister(0x0010, 4, "Global Interrupt Status");
static RegisterValue LookupEngineStatus(31, 31, "Lookup Engine Status", PermissionType::ReadOnly, &GlobalInterruptStatusRegister);

static HardwareRegister GlobalInterruptMaskRegister(0x0014, 4, "Global Interrupt Status");
static RegisterValue LookupEngineMask(31, 31, "Lookup Engine Interrupt Mask", PermissionType::ReadWrite, &GlobalInterruptMaskRegister);

static HardwareRegister GlobalPortInterruptStatusRegister(0x0018, 4, "Global Port Interrupt Status Register");
static RegisterValue Port7InterruptStatus(6, 6, "Port 7 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port6InterruptStatus(5, 5, "Port 6 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port5InterruptStatus(4, 4, "Port 5 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port4InterruptStatus(3, 3, "Port 4 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port3InterruptStatus(2, 2, "Port 3 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port2InterruptStatus(1, 1, "Port 2 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static RegisterValue Port1InterruptStatus(0, 0, "Port 1 Interrupt Status", PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);

static HardwareRegister GlobalPortInterruptMaskRegister(0x001C, 4, "Global Port Interrupt Mask Register");
static RegisterValue Port7InterruptMask(6, 6, "Port 7 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static RegisterValue Port5InterruptMask(4, 4, "Port 5 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static RegisterValue Port4InterruptMask(3, 3, "Port 4 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static RegisterValue Port3InterruptMask(2, 2, "Port 3 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static RegisterValue Port2InterruptMask(1, 1, "Port 2 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static RegisterValue Port1InterruptMask(0, 0, "Port 1 Interrupt Mask", PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);

static HardwareRegister PowerDownControl0Register(0x0201, 1, "Power Down Control 0 Register");
static RegisterValue PLLPowerDown(5, 5, "PLL Power Down", PermissionType::ReadWrite, &PowerDownControl0Register);
static RegisterValue PowerManagementMode(3, 4, "Power Management Mode", PermissionType::ReadWrite, &PowerDownControl0Register);

static HardwareRegister SwitchOperationRegister(0x0300, 1, "Switch Operation Register");
static RegisterValue SoftHardwareReset(1, 1, "Soft Hardware Reset", PermissionType::ReadWrite, &SwitchOperationRegister, SpecialProperties::SelfClearing);
static RegisterValue StartSwitch(0, 0, "Start Switch", PermissionType::ReadWrite, &SwitchOperationRegister);

static HardwareRegister SwitchMACAddress0Register(0x0302, 1, "Switch MAC Address 0 Register");
static RegisterValue SwitchMACAddress0(0, 7, "MAC Address 0", PermissionType::ReadWrite, &SwitchMACAddress0Register, returnEntireRegister);

static HardwareRegister SwitchMACAddress1Register(0x0303, 1, "Switch MAC Address 1 Register");
static RegisterValue SwitchMACAddress1(0, 7, "MAC Address 1", PermissionType::ReadWrite, &SwitchMACAddress1Register, returnEntireRegister);

static HardwareRegister SwitchMACAddress2Register(0x0304, 1, "Switch MAC Address 2 Register");
static RegisterValue SwitchMACAddress2(0, 7, "MAC Address 2", PermissionType::ReadWrite, &SwitchMACAddress2Register, returnEntireRegister);

static HardwareRegister SwitchMACAddress3Register(0x0305, 1, "Switch MAC Address 3 Register");
static RegisterValue SwitchMACAddress3(0, 7, "MAC Address 3", PermissionType::ReadWrite, &SwitchMACAddress3Register, returnEntireRegister);

static HardwareRegister SwitchMACAddress4Register(0x0306, 1, "Switch MAC Address 4 Register");
static RegisterValue SwitchMACAddress4(0, 7, "MAC Address 4", PermissionType::ReadWrite, &SwitchMACAddress4Register, returnEntireRegister);

static HardwareRegister SwitchMACAddress5Register(0x0307, 1, "Switch MAC Address 5 Register");
static RegisterValue SwitchMACAddress5(0, 7, "MAC Address 5", PermissionType::ReadWrite, &SwitchMACAddress5Register, returnEntireRegister);

static HardwareRegister SwitchMTURegister(0x030A, 2, "Switch MTU Register");
static RegisterValue SwitchMTU(0, 13, "MTU Value", PermissionType::ReadWrite, &SwitchMTURegister);

static HardwareRegister SwitchLookupEngineControl0Register(0x0310, 1, "Switch Lookup Engine Control 0 Register");
static RegisterValue VLANEnable(7, 7, "802.1Q VLAN Enable", PermissionType::ReadWrite, &SwitchLookupEngineControl0Register);
static RegisterValue DropInvalidVID(6, 6, "Drop Invalid VID", PermissionType::ReadWrite, &SwitchLookupEngineControl0Register);

#endif