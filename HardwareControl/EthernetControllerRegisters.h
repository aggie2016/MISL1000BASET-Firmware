#ifndef ETHERNET_CONTROLLER_REGISTERS_H
#define ETHERNET_CONTROLLER_REGISTERS_H

#include <HardwareControl/HardwareRegister.h>

#define PORT_1_REGISTER_OFFSET  0x1000
#define PORT_2_REGISTER_OFFSET  0x2000
#define PORT_3_REGISTER_OFFSET  0x3000
#define PORT_4_REGISTER_OFFSET  0x4000
#define PORT_5_REGISTER_OFFSET  0x5000


extern MISL::SPI ethernetController;   

static uint32_t returnEntireRegister(MISL::RegisterValue* val)
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
static MISL::HardwareRegister globalChipID0Register(&ethernetController, 0x0000, 1, "Global Chip ID 0");
static MISL::RegisterValue globalChipIDFixedValue(0, 7, "Fixed Value", MISL::PermissionType::ReadOnly, &globalChipID0Register, returnEntireRegister);

static MISL::HardwareRegister globalChipID1Register(&ethernetController, 0x0001, 1, "Global Chip ID 1");
static MISL::RegisterValue globalChipIDMSB(0, 7, "Chip ID (MSB)", MISL::PermissionType::ReadOnly, &globalChipID1Register, returnEntireRegister);

static MISL::HardwareRegister globalChipID2Register(&ethernetController, 0x0002, 1, "Global Chip ID 2");
static MISL::RegisterValue globalChipIDLSB(0, 7, "Chip ID (LSB)", MISL::PermissionType::ReadOnly, &globalChipID2Register, returnEntireRegister);

static MISL::HardwareRegister globalChipID3Register(&ethernetController, 0x0003, 1, "Global Chip ID 3");
static MISL::RegisterValue revisionID(4, 7, "RevisionID", MISL::PermissionType::ReadOnly, &globalChipID3Register);
static MISL::RegisterValue globalSoftwareReset(0, 0, "RevisionID", MISL::PermissionType::ReadOnly, &globalChipID3Register, MISL::SpecialProperties::SelfClearing);

static MISL::HardwareRegister PMEPinControlRegister(&ethernetController, 0x0006, 1, "PME Pin Control Register");
static MISL::RegisterValue PMEPinOutputEnable(1, 1, "PME Pin Output Enable", MISL::PermissionType::ReadWrite, &PMEPinControlRegister);
static MISL::RegisterValue PMEPinOutputPolarity(0, 0, "PME Pin Output Polarity", MISL::PermissionType::ReadWrite, &PMEPinControlRegister);

static MISL::HardwareRegister GlobalInterruptStatusRegister(&ethernetController, 0x0010, 4, "Global Interrupt Status");
static MISL::RegisterValue LookupEngineStatus(31, 31, "Lookup Engine Status", MISL::PermissionType::ReadOnly, &GlobalInterruptStatusRegister);

static MISL::HardwareRegister GlobalInterruptMaskRegister(&ethernetController, 0x0014, 4, "Global Interrupt Status");
static MISL::RegisterValue LookupEngineMask(31, 31, "Lookup Engine Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalInterruptMaskRegister);

static MISL::HardwareRegister GlobalPortInterruptStatusRegister(&ethernetController, 0x0018, 4, "Global Port Interrupt Status Register");
static MISL::RegisterValue Port7InterruptStatus(6, 6, "Port 7 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port6InterruptStatus(5, 5, "Port 6 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port5InterruptStatus(4, 4, "Port 5 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port4InterruptStatus(3, 3, "Port 4 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port3InterruptStatus(2, 2, "Port 3 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port2InterruptStatus(1, 1, "Port 2 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);
static MISL::RegisterValue Port1InterruptStatus(0, 0, "Port 1 Interrupt Status", MISL::PermissionType::ReadOnly, &GlobalPortInterruptStatusRegister);

static MISL::HardwareRegister GlobalPortInterruptMaskRegister(&ethernetController, 0x001C, 4, "Global Port Interrupt Mask Register");
static MISL::RegisterValue Port7InterruptMask(6, 6, "Port 7 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static MISL::RegisterValue Port5InterruptMask(4, 4, "Port 5 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static MISL::RegisterValue Port4InterruptMask(3, 3, "Port 4 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static MISL::RegisterValue Port3InterruptMask(2, 2, "Port 3 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static MISL::RegisterValue Port2InterruptMask(1, 1, "Port 2 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);
static MISL::RegisterValue Port1InterruptMask(0, 0, "Port 1 Interrupt Mask", MISL::PermissionType::ReadWrite, &GlobalPortInterruptMaskRegister);

static MISL::HardwareRegister PowerDownControl0Register(&ethernetController, 0x0201, 1, "Power Down Control 0 Register");
static MISL::RegisterValue PLLPowerDown(5, 5, "PLL Power Down", MISL::PermissionType::ReadWrite, &PowerDownControl0Register);
static MISL::RegisterValue PowerManagementMode(3, 4, "Power Management Mode", MISL::PermissionType::ReadWrite, &PowerDownControl0Register);

static MISL::HardwareRegister SwitchOperationRegister(&ethernetController, 0x0300, 1, "Switch Operation Register");
static MISL::RegisterValue SoftHardwareReset(1, 1, "Soft Hardware Reset", MISL::PermissionType::ReadWrite, &SwitchOperationRegister, MISL::SpecialProperties::SelfClearing);
static MISL::RegisterValue StartSwitch(0, 0, "Start Switch", MISL::PermissionType::ReadWrite, &SwitchOperationRegister);

static MISL::HardwareRegister SwitchMACAddress0Register(&ethernetController, 0x0302, 1, "Switch MAC Address 0 Register");
static MISL::RegisterValue SwitchMACAddress0(0, 7, "MAC Address 0", MISL::PermissionType::ReadWrite, &SwitchMACAddress0Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMACAddress1Register(&ethernetController, 0x0303, 1, "Switch MAC Address 1 Register");
static MISL::RegisterValue SwitchMACAddress1(0, 7, "MAC Address 1", MISL::PermissionType::ReadWrite, &SwitchMACAddress1Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMACAddress2Register(&ethernetController, 0x0304, 1, "Switch MAC Address 2 Register");
static MISL::RegisterValue SwitchMACAddress2(0, 7, "MAC Address 2", MISL::PermissionType::ReadWrite, &SwitchMACAddress2Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMACAddress3Register(&ethernetController, 0x0305, 1, "Switch MAC Address 3 Register");
static MISL::RegisterValue SwitchMACAddress3(0, 7, "MAC Address 3", MISL::PermissionType::ReadWrite, &SwitchMACAddress3Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMACAddress4Register(&ethernetController, 0x0306, 1, "Switch MAC Address 4 Register");
static MISL::RegisterValue SwitchMACAddress4(0, 7, "MAC Address 4", MISL::PermissionType::ReadWrite, &SwitchMACAddress4Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMACAddress5Register(&ethernetController, 0x0307, 1, "Switch MAC Address 5 Register");
static MISL::RegisterValue SwitchMACAddress5(0, 7, "MAC Address 5", MISL::PermissionType::ReadWrite, &SwitchMACAddress5Register, returnEntireRegister);

static MISL::HardwareRegister SwitchMTURegister(&ethernetController, 0x030A, 2, "Switch MTU Register");
static MISL::RegisterValue SwitchMTU(0, 13, "MTU Value", MISL::PermissionType::ReadWrite, &SwitchMTURegister);

static MISL::HardwareRegister SwitchLookupEngineControl0Register(&ethernetController, 0x0310, 1, "Switch Lookup Engine Control 0 Register");
static MISL::RegisterValue VLANEnable(7, 7, "802.1Q VLAN Enable", MISL::PermissionType::ReadWrite, &SwitchLookupEngineControl0Register);
static MISL::RegisterValue DropInvalidVID(6, 6, "Drop Invalid VID", MISL::PermissionType::ReadWrite, &SwitchLookupEngineControl0Register);

//Port registers
static MISL::HardwareRegister PHYBasicStatusRegister(&ethernetController, 0x0102, 2, "Port PHY Basic Status Register");
static MISL::RegisterValue PHY100BaseT4Status(15, 15, "100Base-T4", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHY100BaseTXFullDuplex(14, 14, "100Base-TX Full Duplex", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHY100BaseTXHalfDuplex(13, 13, "100Base-TX Half Duplex", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHY10MBsFullDuplex(12, 12, "10Mb/s Full Duplex", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHY10MBsHalfDuplex(11, 11, "10Mb/s Half Duplex", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYMFPreambleSuppression(6, 6, "MF Preamble Suppression", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYAutoNegotiationComplete(5, 5, "Auto-Negotiation Complete", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYRemoteFarEndFault(4, 4, "Remote (Far End) Fault", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYAutoNegotiationAbility(3, 3, "Auto-Negotiation Ability", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYLinkStatus(2, 2, "Port Link Status", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYJabberDetect(1, 1, "Port Jabber Detected", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);
static MISL::RegisterValue PHYExtendedCapability(0, 0, "Port Extended Capability", MISL::PermissionType::ReadOnly, &PHYBasicStatusRegister);

static MISL::HardwareRegister PortDefaultTagRegister(&ethernetController, 0x0100, 2, "Port PHY Default VLAN Tag Register");
static MISL::RegisterValue PriorityCodePoint(15, 13, "Priority Code Point", MISL::PermissionType::ReadWrite, &PortDefaultTagRegister);
static MISL::RegisterValue DropEligibleIndicator(12, 12, "Drop Eligible Indicator (DEI)", MISL::PermissionType::ReadWrite, &PortDefaultTagRegister);
static MISL::RegisterValue VLANIdentifier(11, 0, "VLAN Indicator (VID)", MISL::PermissionType::ReadWrite, &PortDefaultTagRegister);

static MISL::HardwareRegister PortPME_WOLEventRegister(&ethernetController, 0x0013, 1, "Port PME or WOL Event Register");
static MISL::RegisterValue MagicPacketDetect(2, 2, "Magic Packet Detected", MISL::PermissionType::ReadWrite, &PortPME_WOLEventRegister);
static MISL::RegisterValue LinkUpDetect(1, 1, "Link Up Detected", MISL::PermissionType::ReadWrite, &PortPME_WOLEventRegister);
static MISL::RegisterValue EnergyDetect(0, 0, "Energy Detected", MISL::PermissionType::ReadWrite, &PortPME_WOLEventRegister);

#endif