#ifndef __RADIO_REGS_H_
#define __RADIO_REGS_H_

/*
0x000 MODEM_STATUS R Status Register
0x004 MODEM_TIMDETSTATUS R Timing Detection Status Register
0x008 MODEM_FREQOFFEST R Frequency Offset Estimate
0x00C MODEM_AFCADJRX R AFC Adjustment RX
0x010 MODEM_AFCADJTX R AFC Adjustment TX
0x014 MODEM_MIXCTRL RW Analog mixer control
0x018 MODEM_CTRL0 RW Control Register 0
0x01C MODEM_CTRL1 RW Control Register 1
0x020 MODEM_CTRL2 RW Control Register 2 !!This register contains hidden bitfields!!
0x024 MODEM_CTRL3 RW Control Register 3 !!This register contains hidden bitfields!!
0x028 MODEM_CTRL4 RW Control Register 4 !!This register contains hidden bitfields!!
0x02C MODEM_CTRL5 RW Control Register 5
0x030 MODEM_TXBR RW Transmit Baudrate
0x034 MODEM_RXBR RW Receive Baudrate
0x038 MODEM_CF RW Channel Filter !!This register contains hidden bitfields!!
0x03C MODEM_PRE RW Preamble Register
0x040 MODEM_SYNC0 RW Sync word 0
0x044 MODEM_SYNC1 RW Sync word 1
0x048 MODEM_TIMING RW Timing Register
0x04C MODEM_DSSS0 RW DSSS symbol 0 Register
0x050 MODEM_MODINDEX RW Modulation Index
0x054 MODEM_AFC RW Automatic Frequency Control
0x058 MODEM_AFCADJLIM RW AFC Adjustment Limit
0x05C MODEM_SHAPING0 RW Shaping Coefficients
0x060 MODEM_SHAPING1 RW Shaping Coefficients
0x064 MODEM_SHAPING2 RW Shaping Coefficients
0x068 MODEM_RAMPCTRL RW Ramping Register !!This register contains hidden bitfields!!
0x06C MODEM_RAMPLEV RW Ramping Register
0x070 MODEM_ROUTEPEN RW I/O Routing Pin Enable Register
0x074 MODEM_ROUTELOC0 RW I/O Routing Location Register
0x078 MODEM_ROUTELOC1 RW I/O Routing Location Register
0x080 MODEM_IF R Interrupt Flags
0x084 MODEM_IFS W1 Interrupt Flag Set Register
0x088 MODEM_IFC (R)W1 Interrupt Flag Clear Register
0x08C MODEM_IEN RW Interrupt Enable Register
EFR32 Wireless Gecko
Radio Transceiver
silabs.com | Smart. Connected. Energy-friendly. Preliminary Rev. 0.4 | 273
Offset Name Type Description
0x090 MODEM_CMD W1 Command register
0x098 MODEM_DCCOMP RW DC Offset compensation Filter Settings
0x09C MODEM_DCCOMPFILTINIT RW DC Offset compensation Filter Intialization
0x100 MODEM_DCESTI R DC Offset Estimated value
0x400 MODEM_RAM0_RAMDATA RW Content of DEMOD RAM x
0x404 MODEM_RAM1_RAMDATA RW Content of DEMOD RAM x

*/

#define RADIO_MODEM_BASE           0x40086000

#define RADIO_MODEM_STATUS         ( RADIO_MODEM_BASE + 0x000 )
#define RADIO_MODEM_TIMDETSTATUS   ( RADIO_MODEM_BASE + 0x004 )
#define RADIO_MODEM_FREQOFFEST     ( RADIO_MODEM_BASE + 0x008 )
#define RADIO_MODEM_AFCADJRX       ( RADIO_MODEM_BASE + 0x00C )
#define RADIO_MODEM_AFCADJTX       ( RADIO_MODEM_BASE + 0x010 )
#define RADIO_MODEM_MIXCTRL        ( RADIO_MODEM_BASE + 0x014 )
#define RADIO_MODEM_CTRL0          ( RADIO_MODEM_BASE + 0x018 )
#define RADIO_MODEM_CTRL1          ( RADIO_MODEM_BASE + 0x01C )
#define RADIO_MODEM_CTRL2          ( RADIO_MODEM_BASE + 0x020 )
#define RADIO_MODEM_CTRL3          ( RADIO_MODEM_BASE + 0x024 )
#define RADIO_MODEM_CTRL4          ( RADIO_MODEM_BASE + 0x028 )
#define RADIO_MODEM_CTRL5          ( RADIO_MODEM_BASE + 0x02C )
#define RADIO_MODEM_TXBR           ( RADIO_MODEM_BASE + 0x030 )
#define RADIO_MODEM_RXBR           ( RADIO_MODEM_BASE + 0x034 )
#define RADIO_MODEM_CF             ( RADIO_MODEM_BASE + 0x038 )
#define RADIO_MODEM_PRE            ( RADIO_MODEM_BASE + 0x03C )
#define RADIO_MODEM_SYNC0          ( RADIO_MODEM_BASE + 0x040 )
#define RADIO_MODEM_SYNC1          ( RADIO_MODEM_BASE + 0x044 )
#define RADIO_MODEM_TIMING         ( RADIO_MODEM_BASE + 0x048 )
#define RADIO_MODEM_DSSS0          ( RADIO_MODEM_BASE + 0x04c )
#define RADIO_MODEM_MODINDEX       ( RADIO_MODEM_BASE + 0x050 )
#define RADIO_MODEM_AFC            ( RADIO_MODEM_BASE + 0x054 )
#define RADIO_MODEM_AFCADJLIM      ( RADIO_MODEM_BASE + 0x058 ) 
#define RADIO_MODEM_SHAPING0       ( RADIO_MODEM_BASE + 0x05C )
#define RADIO_MODEM_SHAPING1       ( RADIO_MODEM_BASE + 0x060 )
#define RADIO_MODEM_SHAPING2       ( RADIO_MODEM_BASE + 0x064 )
#define RADIO_MODEM_RAMPCTRL       ( RADIO_MODEM_BASE + 0x068 )
#define RADIO_MODEM_RAMPLEV        ( RADIO_MODEM_BASE + 0x06C )
#define RADIO_MODEM_ROUTEPEN       ( RADIO_MODEM_BASE + 0x070 )
#define RADIO_MODEM_ROUTELOC0      ( RADIO_MODEM_BASE + 0x074 )
#define RADIO_MODEM_ROUTELOC1      ( RADIO_MODEM_BASE + 0x078 )
#define RADIO_MODEM_IF             ( RADIO_MODEM_BASE + 0x080 )
#define RADIO_MODEM_IFS            ( RADIO_MODEM_BASE + 0x084 )
#define RADIO_MODEM_IFC            ( RADIO_MODEM_BASE + 0x088 )
#define RADIO_MODEM_IEN            ( RADIO_MODEM_BASE + 0x08C )
#define RADIO_MODEM_CMD            ( RADIO_MODEM_BASE + 0x090 )
#define RADIO_MODEM_DCCOMP         ( RADIO_MODEM_BASE + 0x098 )
#define RADIO_MODEM_DCCOMPFILTINIT ( RADIO_MODEM_BASE + 0x09C )   
#define RADIO_MODEM_DCESTI         ( RADIO_MODEM_BASE + 0x100 )
#define RADIO_MODEM_RAM0_RAMDATA   ( RADIO_MODEM_BASE + 0x400 ) 
#define RADIO_MODEM_RAM1_RAMDATA   ( RADIO_MODEM_BASE + 0x404 )

#endif
