#ifndef W5500_H
#define W5500_H

#include <cstdint>
#include <functional>
#include <vector>
#include "IReadWriteDevice.h"

/**
 * @brief Select WIZCHIP.
 * @todo You should select one, \b 5100, \b 5200 ,\b 5500 or etc. \n\n
 *       ex> <code> #define \_WIZCHIP_      5500 </code>
 */
#define WIZCHIP                     5500   // 5100, 5200, 5500

#define W5500_IO_BASE               0x00000000
#define WIZCHIP_IO_MODE_NONE        0x0000
#define WIZCHIP_IO_MODE_BUS         0x0100 /**< Bus interface mode */
#define WIZCHIP_IO_MODE_SPI         0x0200 /**< SPI interface mode */

#define WIZCHIP_IO_MODE_SPI_VDM     (WIZCHIP_IO_MODE_SPI + 1) /**< SPI interface mode for variable length data*/
#define WIZCHIP_IO_MODE_SPI_FDM     (WIZCHIP_IO_MODE_SPI + 2) /**< SPI interface mode for fixed length data mode*/

#define W5500_SPI_VDM_OP            0x00
#define W5500_SPI_FDM_OP_LEN1       0x01
#define W5500_SPI_FDM_OP_LEN2       0x02
#define W5500_SPI_FDM_OP_LEN4       0x03

#define WIZCHIP_ID                  "W5500"
  
#define W5500_SPI_READ			    (0x00 << 2) //< SPI interface Read operation in Control Phase
#define W5500_SPI_WRITE			    (0x01 << 2) //< SPI interface Write operation in Control Phase

#define WIZCHIP_CREG_BLOCK          0x00 	//< Common register block
#define WIZCHIP_SREG_BLOCK(N)       (1+4*N) //< Socket N register block
#define WIZCHIP_TXBUF_BLOCK(N)      (2+4*N) //< Socket N Tx buffer address block
#define WIZCHIP_RXBUF_BLOCK(N)      (3+4*N) //< Socket N Rx buffer address block
#define WIZCHIP_OFFSET_INC(ADDR, N) (ADDR + (N<<8)) //< Increase offset address

/**
 * @brief Define interface mode. \n
 * @todo Should select interface mode as chip. 
 *        - @ref \WIZCHIP_IO_MODE_SPI \n
 *          -@ref \WIZCHIP_IO_MODE_SPI_VDM : Valid only in @ref \WIZCHIP == 5500 \n
 *          -@ref \WIZCHIP_IO_MODE_SPI_FDM : Valid only in @ref \WIZCHIP == 5500 \n
 *        - Others will be defined in future. \n\n
 *        ex> <code> #define \WIZCHIP_IO_MODE \WIZCHIP_IO_MODE_SPI_VDM </code>
 *       
 */
   //#define WIZCHIP_IO_MODE           WIZCHIP_IO_MODE_SPI_FDM
#define WIZCHIP_IO_MODE             WIZCHIP_IO_MODE_SPI_VDM

/**
 * @brief Define I/O base address when BUS IF mode.
 * @todo Should re-define it to fit your system when BUS IF Mode (@ref \_WIZCHIP_IO_MODE_BUS_,
 *       @ref \_WIZCHIP_IO_MODE_BUS_DIR_, @ref \_WIZCHIP_IO_MODE_BUS_INDIR_). \n\n
 *       ex> <code> #define \_WIZCHIP_IO_BASE_      0x00008000 </code>
 */
#define WIZCHIP_IO_BASE             0x00000000  // 
#define WIZCHIP_SOCK_NUM            8   ///< The count of independant socket of @b WIZCHIP

#define PHY_CONFBY_HW               0     ///< Configured PHY operation mode by HW pin
#define PHY_CONFBY_SW               1     ///< Configured PHY operation mode by SW register   
#define PHY_MODE_MANUAL             0     ///< Configured PHY operation mode with user setting.
#define PHY_MODE_AUTONEGO           1     ///< Configured PHY operation mode with auto-negotiation
#define PHY_SPEED_10                0     ///< Link Speed 10
#define PHY_SPEED_100               1     ///< Link Speed 100
#define PHY_DUPLEX_HALF             0     ///< Link Half-Duplex
#define PHY_DUPLEX_FULL             1     ///< Link Full-Duplex
#define PHY_LINK_OFF                0     ///< Link Off
#define PHY_LINK_ON                 1     ///< Link On
#define PHY_POWER_NORM              0     ///< PHY power normal mode
#define PHY_POWER_DOWN              1     ///< PHY power down mode 


/**
 * @ingroup DATA_TYPE
 *  Interrupt kind when CW_SET_INTRRUPT, CW_GET_INTERRUPT, CW_SET_INTRMASK
 *  and CW_GET_INTRMASK is used in @ref ctlnetwork().
 *  It can be used with OR operation.
 */
enum class W5500InterruptType : uint16_t
{
    WOL              = (1 << 4),   ///< Wake On Lan by receiving the magic packet. Valid in W500.
    PPPOE_TERMINATED = (1 << 5),   ///< PPPoE Disconnected
    DEST_UNREACHED   = (1 << 6),   ///< Destination IP & Port Unreable, No use in W5200 
    IP_CONFLICT      = (1 << 7),   ///< IP conflict occurred
    SOCK_0           = (1 << 8),   ///< Socket 0 interrupt
    SOCK_1           = (1 << 9),   ///< Socket 1 interrupt
    SOCK_2           = (1 << 10),  ///< Socket 2 interrupt
    SOCK_3           = (1 << 11),  ///< Socket 3 interrupt  
    SOCK_4           = (1 << 12),  ///< Socket 4 interrupt, No use in 5100
    SOCK_5           = (1 << 13),  ///< Socket 5 interrupt, No use in 5100
    SOCK_6           = (1 << 14),  ///< Socket 6 interrupt, No use in 5100
    SOCK_7           = (1 << 15),  ///< Socket 7 interrupt, No use in 5100
    SOCK_ALL         = (0xFF << 8) ///< All Socket interrpt   
};

struct PHYConfigurationInfo
{
    uint8_t by;       ///< set by @ref PHY_CONFBY_HW or @ref PHY_CONFBY_SW
    uint8_t mode;     ///< set by @ref PHY_MODE_MANUAL or @ref PHY_MODE_AUTONEGO
    uint8_t speed;    ///< set by @ref PHY_SPEED_10 or @ref PHY_SPEED_100
    uint8_t duplex;   ///< set by @ref PHY_DUPLEX_HALF @ref PHY_DUPLEX_FULL 
    //uint8_t power;  ///< set by @ref PHY_POWER_NORM or @ref PHY_POWER_DOWN
    //uint8_t link;   ///< Valid only in CW_GET_PHYSTATUS. set by @ref PHY_LINK_ON or PHY_DUPLEX_OFF 
}; 

/**
 * @ingroup DATA_TYPE
 *  Network Information for WIZCHIP
 */
struct NetworkInformation
{
    std::vector<uint8_t> mac;  ///< Source Mac Address
    std::vector<uint8_t> ip;   ///< Source IP Address
    std::vector<uint8_t> sn;   ///< Subnet Mask 
    std::vector<uint8_t> gw;   ///< Gateway IP Address
};

/**
 * @ingroup DATA_TYPE
 *  Network mode
 */
enum class NetModeType : uint8_t
{
    NM_FORCEARP  = (1 << 1),  ///< Force to APP send whenever udp data is sent. Valid only in W5500 
    NM_WAKEONLAN = (1 << 5),  ///< Wake On Lan 
    NM_PINGBLOCK = (1 << 4),  ///< Block ping-request
    NM_PPPOE     = (1 << 3),  ///< PPPoE mode
};

/**
 * @ingroup DATA_TYPE
 *  Used in CN_SET_TIMEOUT or CN_GET_TIMEOUT of @ref ctlwizchip() for timeout configruation.
 */
struct W5500NetTimeout
{
    uint8_t  retry_cnt;     ///< retry count 
    uint16_t time_100us;    ///< time unit 100us
};

//----------------------------- W5500 Common Registers IOMAP -----------------------------
/**
 * @ingroup Common_register_group
 * @brief Mode Register address(R/W)\n
 * @ref MR is used for S/W reset, ping block mode, PPPoE mode and etc.
 * @details Each bit of @ref MR defined as follows.
 * <table>
 * 		<tr>  <td>7</td> <td>6</td> <td>5</td> <td>4</td> <td>3</td> <td>2</td> <td>1</td> <td>0</td>   </tr>
 * 		<tr>  <td>RST</td> <td>Reserved</td> <td>WOL</td> <td>PB</td> <td>PPPoE</td> <td>Reserved</td> <td>FARP</td> <td>Reserved</td> </tr>
 * </table>
 * - \ref MR_RST		 	: Reset
 * - \ref MR_WOL       		: Wake on LAN
 * - \ref MR_PB         	: Ping block
 * - \ref MR_PPPOE      	: PPPoE mode
 * - \ref MR_FARP			: Force ARP mode
 */
#define MR                 (W5500_IO_BASE + (0x0000 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define GAR                (W5500_IO_BASE + (0x0001 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define SUBR               (W5500_IO_BASE + (0x0005 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define SHAR               (W5500_IO_BASE + (0x0009 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define SIPR               (W5500_IO_BASE + (0x000F << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define INTLEVEL           (W5500_IO_BASE + (0x0013 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define IR                 (W5500_IO_BASE + (0x0015 << 8) + (WIZCHIP_CREG_BLOCK << 3))

/**
 * @ingroup Common_register_group
 * @brief Interrupt mask register(R/W)
 * @details @ref IMR is used to mask interrupts. Each bit of @ref IMR corresponds to each bit of @ref IR.
 * When a bit of @ref IMR is and the corresponding bit of @ref IR is  an interrupt will be issued. In other words,
 * if a bit of @ref IMR is  an interrupt will not be issued even if the corresponding bit of @ref IR is \n\n
 * Each bit of @ref IMR defined as the following.
 * <table>
 * 		<tr>  <td>7</td> <td>6</td> <td>5</td> <td>4</td> <td>3</td> <td>2</td> <td>1</td> <td>0</td>   </tr>
 * 		<tr>  <td>IM_IR7</td> <td>IM_IR6</td> <td>IM_IR5</td> <td>IM_IR4</td> <td>Reserved</td> <td>Reserved</td> <td>Reserved</td> <td>Reserved</td> </tr>
 * </table>
 * - \ref IM_IR7 : IP Conflict Interrupt Mask
 * - \ref IM_IR6 : Destination unreachable Interrupt Mask
 * - \ref IM_IR5 : PPPoE Close Interrupt Mask
 * - \ref IM_IR4 : Magic Packet Interrupt Mask
 */
#define IMR                 (W5500_IO_BASE + (0x0016 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define SIR                 (W5500_IO_BASE + (0x0017 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define SIMR                (W5500_IO_BASE + (0x0018 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define RTR                 (W5500_IO_BASE + (0x0019 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define RCR                 (W5500_IO_BASE + (0x001B << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PTIMER              (W5500_IO_BASE + (0x001C << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PMAGIC              (W5500_IO_BASE + (0x001D << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PHAR                (W5500_IO_BASE + (0x001E << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PSID                (W5500_IO_BASE + (0x0024 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PMRU                (W5500_IO_BASE + (0x0026 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define UIPR                (W5500_IO_BASE + (0x0028 << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define UPORTR              (W5500_IO_BASE + (0x002C << 8) + (WIZCHIP_CREG_BLOCK << 3))
#define PHYCFGR             (W5500_IO_BASE + (0x002E << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x002F << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0030 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0031 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0032 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0033 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0034 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0035 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0036 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0037 << 8) + (WIZCHIP_CREG_BLOCK << 3))
// Reserved			        (W5500_IO_BASE + (0x0038 << 8) + (WIZCHIP_CREG_BLOCK << 3))
//#define VERSIONR            (W5500_IO_BASE + (0x0039 << 8) + (WIZCHIP_CREG_BLOCK << 3))

//----------------------------- W5500 Socket Registers IOMAP -----------------------------
/**
 * @ingroup Socket_register_group
 * @brief socket Mode register(R/W)
 * @details @ref Sn_MR configures the option or protocol type of Socket n.\n\n
 * Each bit of @ref Sn_MR defined as the following.
 * <table>
 * 		<tr>  <td>7</td> <td>6</td> <td>5</td> <td>4</td> <td>3</td> <td>2</td> <td>1</td> <td>0</td>   </tr>
 * 		<tr>  <td>MULTI/MFEN</td> <td>BCASTB</td> <td>ND/MC/MMB</td> <td>UCASTB/MIP6B</td> <td>Protocol[3]</td> <td>Protocol[2]</td> <td>Protocol[1]</td> <td>Protocol[0]</td> </tr>
 * </table>
 * - @ref Sn_MR_MULTI	: Support UDP Multicasting
 * - @ref Sn_MR_BCASTB	: Broadcast block <b>in UDP Multicasting</b>
 * - @ref Sn_MR_ND		: No Delayed Ack(TCP) flag
 * - @ref Sn_MR_MC   	: IGMP version used <b>in UDP mulitcasting</b>
 * - @ref Sn_MR_MMB    	: Multicast Blocking <b>in @ref Sn_MR_MACRAW mode</b>
 * - @ref Sn_MR_UCASTB	: Unicast Block <b>in UDP Multicating</b>
 * - @ref Sn_MR_MIP6B   : IPv6 packet Blocking <b>in @ref Sn_MR_MACRAW mode</b>
 * - <b>Protocol</b>
 * <table>
 * 		<tr>   <td><b>Protocol[3]</b></td> <td><b>Protocol[2]</b></td> <td><b>Protocol[1]</b></td> <td><b>Protocol[0]</b></td> <td>@b Meaning</td>   </tr>
 * 		<tr>   <td>0</td> <td>0</td> <td>0</td> <td>0</td> <td>Closed</td>   </tr>
 * 		<tr>   <td>0</td> <td>0</td> <td>0</td> <td>1</td> <td>TCP</td>   </tr>
 * 		<tr>   <td>0</td> <td>0</td> <td>1</td> <td>0</td> <td>UDP</td>   </tr>
 * 		<tr>   <td>0</td> <td>1</td> <td>0</td> <td>0</td> <td>MACRAW</td>   </tr>
 * </table>
 *	- @ref Sn_MR_MACRAW	: MAC LAYER RAW SOCK \n
 *  - @ref Sn_MR_UDP		: UDP
 *  - @ref Sn_MR_TCP		: TCP
 *  - @ref Sn_MR_CLOSE	: Unused socket
 *  @note MACRAW mode should be only used in Socket 0.
 */
#define Sn_MR(N)           (W5500_IO_BASE + (0x0000 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_CR(N)           (W5500_IO_BASE + (0x0001 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_IR(N)           (W5500_IO_BASE + (0x0002 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))

/**
 * @ingroup Socket_register_group
 * @brief Socket status register(R)
 * @details @ref Sn_SR indicates the status of Socket n.\n
 * The status of Socket n is changed by @ref Sn_CR or some special control packet as SYN, FIN packet in TCP.
 * @par Normal status
 * - @ref SOCK_CLOSED 		: Closed
 * - @ref SOCK_INIT   		: Initiate state
 * - @ref SOCK_LISTEN    	: Listen state
 * - @ref SOCK_ESTABLISHED 	: Success to connect
 * - @ref SOCK_CLOSE_WAIT   : Closing state
 * - @ref SOCK_UDP   		: UDP socket
 * - @ref SOCK_MACRAW  		: MAC raw mode socket
 *@par Temporary status during changing the status of Socket n.
 * - @ref SOCK_SYNSENT   	: This indicates Socket n sent the connect-request packet (SYN packet) to a peer.
 * - @ref SOCK_SYNRECV    	: It indicates Socket n successfully received the connect-request packet (SYN packet) from a peer.
 * - @ref SOCK_FIN_WAIT		: Connection state
 * - @ref SOCK_CLOSING		: Closing state
 * - @ref SOCK_TIME_WAIT	: Closing state
 * - @ref SOCK_LAST_ACK 	: Closing state
 */
#define Sn_SR(N)            (W5500_IO_BASE + (0x0003 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_PORT(N)          (W5500_IO_BASE + (0x0004 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_DHAR(N)          (W5500_IO_BASE + (0x0006 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_DIPR(N)          (W5500_IO_BASE + (0x000C << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_DPORT(N)         (W5500_IO_BASE + (0x0010 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_MSSR(N)          (W5500_IO_BASE + (0x0012 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))

// Reserved			        (W5500_IO_BASE + (0x0014 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TOS(N)           (W5500_IO_BASE + (0x0015 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TTL(N)           (W5500_IO_BASE + (0x0016 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x0017 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x0018 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3)) 
// Reserved			        (W5500_IO_BASE + (0x0019 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x001A << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x001B << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x001C << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
// Reserved			        (W5500_IO_BASE + (0x001D << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_RXBUF_SIZE(N)    (W5500_IO_BASE + (0x001E << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TXBUF_SIZE(N)    (W5500_IO_BASE + (0x001F << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TX_FSR(N)        (W5500_IO_BASE + (0x0020 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TX_RD(N)         (W5500_IO_BASE + (0x0022 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_TX_WR(N)         (W5500_IO_BASE + (0x0024 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_RX_RSR(N)        (W5500_IO_BASE + (0x0026 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_RX_RD(N)         (W5500_IO_BASE + (0x0028 << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_RX_WR(N)         (W5500_IO_BASE + (0x002A << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_IMR(N)           (W5500_IO_BASE + (0x002C << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_FRAG(N)          (W5500_IO_BASE + (0x002D << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))
#define Sn_KPALVTR(N)       (W5500_IO_BASE + (0x002F << 8) + (WIZCHIP_SREG_BLOCK(N) << 3))

//----------------------------- W5500 Register values  -----------------------------

/* MODE register values */
/**
 * @brief Reset
 * @details If this bit is  All internal registers will be initialized. It will be automatically cleared as after S/W reset.
 */
#define MR_RST                       0x80

/**
 * @brief Wake on LAN
 * @details 0 : Disable WOL mode\n
 * 1 : Enable WOL mode\n
 * If WOL mode is enabled and the received magic packet over UDP has been normally processed, the Interrupt PIN (INTn) asserts to low.
 * When using WOL mode, the UDP Socket should be opened with any source port number. (Refer to Socket n Mode Register (@ref Sn_MR) for opening Socket.)
 * @note The magic packet over UDP supported by W5500 consists of 6 bytes synchronization stream (xFFFFFFFFFFFF and
 * 16 times Target MAC address stream in UDP payload. The options such like password are ignored. You can use any UDP source port number for WOL mode.
 */
#define MR_WOL                       0x20
#define MR_PB                        0x10
#define MR_PPPOE                     0x08
#define MR_FARP                      0x02

#define IR_CONFLICT                  0x80
#define IR_UNREACH                   0x40
#define IR_PPPoE                     0x20
#define IR_MP                        0x10


/* PHYCFGR register value */
#define PHYCFGR_RST                  ~(1<<7)  //< For PHY reset, must operate AND mask.
#define PHYCFGR_OPMD                 (1<<6)   // Configre PHY with OPMDC value
#define PHYCFGR_OPMDC_ALLA           (7<<3)
#define PHYCFGR_OPMDC_PDOWN          (6<<3)
#define PHYCFGR_OPMDC_NA             (5<<3)
#define PHYCFGR_OPMDC_100FA          (4<<3)
#define PHYCFGR_OPMDC_100F           (3<<3)
#define PHYCFGR_OPMDC_100H           (2<<3)
#define PHYCFGR_OPMDC_10F            (1<<3)
#define PHYCFGR_OPMDC_10H            (0<<3)           
#define PHYCFGR_DPX_FULL             (1<<2)
#define PHYCFGR_DPX_HALF             (0<<2)
#define PHYCFGR_SPD_100              (1<<1)
#define PHYCFGR_SPD_10               (0<<1)
#define PHYCFGR_LNK_ON               (1<<0)
#define PHYCFGR_LNK_OFF              (0<<0)

/* IMR register values */
/**
 * @brief IP Conflict Interrupt Mask.
 * @details 0: Disable IP Conflict Interrupt\n
 * 1: Enable IP Conflict Interrupt
 */
#define IM_IR7                  	 0x80
#define IM_IR6                  	 0x40
#define IM_IR5                  	 0x20
#define IM_IR4                  	 0x10

#define Sn_MR_MULTI                  0x80
#define Sn_MR_BCASTB                 0x40
#define Sn_MR_ND                     0x20
#define Sn_MR_UCASTB                 0x10
#define Sn_MR_MACRAW                 0x04
#define Sn_MR_UDP                    0x02
#define Sn_MR_TCP                    0x01
#define Sn_MR_CLOSE                  0x00
#define Sn_MR_MFEN                   Sn_MR_MULTI
#define Sn_MR_MMB                    Sn_MR_ND
#define Sn_MR_MIP6B                  Sn_MR_UCASTB
#define Sn_MR_MC                     Sn_MR_ND

/* Sn_MR alternate values */
/**
 * @brief For Berkeley Socket API
 */
#define SOCK_STREAM                  Sn_MR_TCP
#define SOCK_DGRAM                   Sn_MR_UDP


/* Sn_CR values */
/**
 * @brief Initialize or open socket
 * @details Socket n is initialized and opened according to the protocol selected in Sn_MR(P3:P0).
 * The table below shows the value of @ref Sn_SR corresponding to @ref Sn_MR.\n
 * <table>
 *   <tr>  <td>\b Sn_MR (P[3:0])</td> <td>\b Sn_SR</td>            		 </tr>
 *   <tr>  <td>Sn_MR_CLOSE  (000</td> <td></td>         	   		 </tr>
 *   <tr>  <td>Sn_MR_TCP  (001</td> <td>SOCK_INIT (0x13)</td>  		 </tr>
 *   <tr>  <td>Sn_MR_UDP  (010</td>  <td>SOCK_UDP (0x22)</td>  		 </tr>
 *   <tr>  <td>S0_MR_MACRAW  (100</td>  <td>SOCK_MACRAW (0x02)</td>  </tr>
 * </table>
 */
#define Sn_CR_OPEN                   0x01
#define Sn_CR_LISTEN                 0x02
#define Sn_CR_CONNECT                0x04
#define Sn_CR_DISCON                 0x08
#define Sn_CR_CLOSE                  0x10
#define Sn_CR_SEND                   0x20
#define Sn_CR_SEND_MAC               0x21
#define Sn_CR_SEND_KEEP              0x22
#define Sn_CR_RECV                   0x40

#define Sn_IR_SENDOK                 0x10
#define Sn_IR_TIMEOUT                0x08
#define Sn_IR_RECV                   0x04
#define Sn_IR_DISCON                 0x02
#define Sn_IR_CON                    0x01

#define SOCK_CLOSED                  0x00
#define SOCK_INIT                    0x13
#define SOCK_LISTEN                  0x14
#define SOCK_SYNSENT                 0x15
#define SOCK_SYNRECV                 0x16
#define SOCK_ESTABLISHED             0x17
#define SOCK_FIN_WAIT                0x18
#define SOCK_CLOSING                 0x1A
#define SOCK_TIME_WAIT               0x1B
#define SOCK_CLOSE_WAIT              0x1C
#define SOCK_LAST_ACK                0x1D
#define SOCK_UDP                     0x22
#define SOCK_MACRAW                  0x42

#define IPPROTO_IP                   0        //< Dummy for IP 
#define IPPROTO_ICMP                 1        //< Control message protocol
#define IPPROTO_IGMP                 2        //< Internet group management protocol
#define IPPROTO_GGP                  3        //< Gateway^2 (deprecated)
#define IPPROTO_TCP                  6        //< TCP
#define IPPROTO_PUP                  12       //< PUP
#define IPPROTO_UDP                  17       //< UDP
#define IPPROTO_IDP                  22       //< XNS idp
#define IPPROTO_ND                   77       //< UNOFFICIAL net disk protocol
#define IPPROTO_RAW                  255      //< Raw IP packet

namespace MISL
{   
    
    class Socket;
    
    class W5500
    {
    public:
        W5500(IReadWriteDevice<uint8_t>* device);
        ~W5500();
              
        bool initChip(const std::vector<uint8_t>& txsize, const std::vector<uint8_t>& rxsize);
        
        void resetChip();
        void resetPHY();
        std::string deviceName();
        
        W5500InterruptType interrupt();
        void clearInterrupt(const W5500InterruptType& interrupt);
        
        W5500InterruptType interruptMask();
        void setInterruptMask(const W5500InterruptType& mask);
        
        uint16_t interruptInterval();
        void interruptInterval(const uint16_t& interval);
        
        PHYConfigurationInfo PHYStatus();
        
        PHYConfigurationInfo PHYConfiguration();
        void setPHYConfiguration(const PHYConfigurationInfo& config);
        
        uint8_t PHYPowerMode();
        bool setPHYPowerMode(const uint8_t& mode);
        
        NetModeType networkMode();
        void setNetworkMode(const NetModeType& mode);
        
        NetworkInformation networkInfo();
        void setNetworkInfo(const NetworkInformation& info);
        
        uint8_t linkStatus();
        
        W5500NetTimeout retryTimeout();
        void setRetryTimeout(const W5500NetTimeout& timeout);     
        
    protected:
        uint8_t readRegister(const uint32_t& address);
        void writeRegister(const uint32_t& address, const uint8_t& value);
        
        std::vector<uint8_t> readRegisters(const uint32_t& address, const uint16_t& count);
        void writeRegisters(const uint32_t& address, const std::vector<uint8_t>& buffer);
        
    private:
        IReadWriteDevice<uint8_t>* m_w5500Interface;
        std::function<void(void)> m_enterCriticalFunction;
        std::function<void(void)> m_exitCriticalFunction;
        friend class Socket;
    };
    
}



#endif // W5500_H


