#ifndef __RADIO_INIT_H_
#define __RADIO_INIT_H_

#include "rail.h"

#if !defined(EMU_DCDCINIT_WSTK_DEFAULT)
/* Use emlib defaults */
#define EMU_DCDCINIT_WSTK_DEFAULT       EMU_DCDCINIT_DEFAULT
#endif

#if !defined(CMU_HFXOINIT_WSTK_DEFAULT)
#define CMU_HFXOINIT_WSTK_DEFAULT                                               \
{                                                                               \
  false,        /* Low-noise mode for EFR32 */                                  \
  false,        /* Disable auto-start on EM0/1 entry */                         \
  false,        /* Disable auto-select on EM0/1 entry */                        \
  false,        /* Disable auto-start and select on RAC wakeup */               \
  _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                           \
  0x142,        /* Steady-state CTUNE for WSTK boards without load caps */      \
  _CMU_HFXOSTARTUPCTRL_REGISHWARM_DEFAULT,                                      \
  _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                                      \
  _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT,                                    \
  0x7,          /* Recommended steady-state XO core bias current */             \
  0x6,          /* Recommended peak detection threshold */                      \
  _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                                 \
  0xA,          /* Recommended peak detection timeout  */                       \
  _CMU_HFXOTIMEOUTCTRL_WARMSTEADYTIMEOUT_DEFAULT,                               \
  _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT,                                   \
  _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                                  \
}

#pragma message( "CMU_HFXOINIT_WSTK_DEFAULT defined" )

#endif

#if !defined(RADIO_PTI_INIT)
#define RADIO_PTI_INIT                                                        \
  {                                                                           \
    RADIO_PTI_MODE_UART,    /* Simplest output mode is UART mode */           \
    1600000,                /* Choose 1.6 MHz for best compatibility */       \
    6,                      /* WSTK uses location 6 for DOUT */               \
    gpioPortB,              /* Get the port for this loc */                   \
    12,                     /* Get the pin, location should match above */    \
    6,                      /* WSTK uses location 6 for DCLK */               \
    gpioPortB,              /* Get the port for this loc */                   \
    11,                     /* Get the pin, location should match above */    \
    6,                      /* WSTK uses location 6 for DFRAME */             \
    gpioPortB,              /* Get the port for this loc */                   \
    13,                     /* Get the pin, location should match above */    \
  }

#pragma message( "RADIO_PTI_INIT defined" )
#endif

#if !defined(RADIO_PA_2P4_INIT)
#define RADIO_PA_2P4_INIT                                                     \
  {                                                                           \
    PA_SEL_2P4_HP,    /* Power Amplifier mode */                              \
    PA_VOLTMODE_DCDC, /* Power Amplifier vPA Voltage mode */                  \
    100,              /* Desired output power in dBm * 10 */                  \
    0,                /* Output power offset in dBm * 10 */                   \
    10,               /* Desired ramp time in us */                           \
  }

#pragma message( "RADIO_PA_2P4_INIT defined" )

#endif

#if !defined(RADIO_PA_SUBGIG_INIT)
#define RADIO_PA_SUBGIG_INIT                                                  \
  {                                                                           \
    PA_SEL_SUBGIG,    /* Power Amplifier mode */                              \
    PA_VOLTMODE_DCDC, /* Power Amplifier vPA Voltage mode */                  \
    100,              /* Desired output power in dBm * 10 */                  \
    0,                /* Output power offset in dBm * 10 */                   \
    10,               /* Desired ramp time in us */                           \
  }
#pragma message( "RADIO_PA_SUBGIG_INIT defined" )
#endif

#endif
