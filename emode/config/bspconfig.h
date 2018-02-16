/***************************************************************************//**
 *
 * @file bspconfig.h
 * @brief Provide BSP (board support package) configuration parameters.
 *
 *******************************************************************************
 *
 * @section License
 *
 *  Copyright (C) 2016-2017 Silicon Labs, http://www.silabs.com
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#ifndef BSPCONFIG_H
#define BSPCONFIG_H

#define BSP_STK
#define BSP_TBSENSE

#define BSP_BCC_USART         USART0
#define BSP_BCC_CLK           cmuClock_USART0
#define BSP_BCC_TX_LOCATION   USART_ROUTELOC0_TXLOC_LOC0
#define BSP_BCC_RX_LOCATION   USART_ROUTELOC0_RXLOC_LOC0
#define BSP_BCC_TXPORT        gpioPortA
#define BSP_BCC_TXPIN         0
#define BSP_BCC_RXPORT        gpioPortA
#define BSP_BCC_RXPIN         1
#define BSP_BCC_ENABLE_PORT   gpioPortA
#define BSP_BCC_ENABLE_PIN    5                 /* VCOM_ENABLE */

#define BSP_DISP_ENABLE_PORT  gpioPortD
#define BSP_DISP_ENABLE_PIN   15                /* MemLCD display enable */

#define BSP_GPIO_LEDS
#define BSP_NO_OF_LEDS          2
#define BSP_GPIO_LED0_PORT      gpioPortD
#define BSP_GPIO_LED0_PIN       11
#define BSP_GPIO_LED1_PORT      gpioPortD
#define BSP_GPIO_LED1_PIN       12
#define BSP_GPIO_LEDARRAY_INIT  {{BSP_GPIO_LED0_PORT,BSP_GPIO_LED0_PIN}, {BSP_GPIO_LED1_PORT,BSP_GPIO_LED1_PIN}}

#define BSP_GPIO_BUTTONS
#define BSP_NO_OF_BUTTONS       2
#define BSP_GPIO_PB0_PORT       gpioPortD
#define BSP_GPIO_PB0_PIN        14
#define BSP_GPIO_PB1_PORT       gpioPortD
#define BSP_GPIO_PB1_PIN        15

#define BSP_GPIO_BUTTONARRAY_INIT {{BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN}, {BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN}}

#define BSP_INIT_DEFAULT  0

#if !defined(EMU_DCDCINIT_TBSENSE_DEFAULT)
/* Use emlib defaults */
#define EMU_DCDCINIT_TBSENSE_DEFAULT       EMU_DCDCINIT_DEFAULT
#endif

#if !defined(CMU_HFXOINIT_TBSENSE_DEFAULT)
#define CMU_HFXOINIT_TBSENSE_DEFAULT                                            \
{                                                                               \
  false,        /* Low-noise mode for EFR32 */                                  \
  false,        /* Disable auto-start on EM0/1 entry */                         \
  false,        /* Disable auto-select on EM0/1 entry */                        \
  false,        /* Disable auto-start and select on RAC wakeup */               \
  _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                           \
  0x142,        /* Steady-state CTUNE for TBSENSE boards without load caps */   \
  _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                                      \
  _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT,                                    \
  0x7,          /* Recommended steady-state XO core bias current */             \
  0x6,          /* Recommended peak detection threshold */                      \
  _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                                 \
  0xA,          /* Recommended peak detection timeout  */                       \
  _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT,                                   \
  _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                                  \
}
#endif

#if !defined(RADIO_PTI_INIT)
#define RADIO_PTI_INIT                                                        \
  {                                                                           \
    RADIO_PTI_MODE_UART,    /* Simplest output mode is UART mode */           \
    1600000,                /* Choose 1.6 MHz for best compatibility */       \
    6,                      /* TBSENSE uses location 6 for DOUT */            \
    gpioPortB,              /* Get the port for this loc */                   \
    12,                     /* Get the pin, location should match above */    \
    6,                      /* TBSENSE uses location 6 for DCLK */            \
    gpioPortB,              /* Get the port for this loc */                   \
    11,                     /* Get the pin, location should match above */    \
    6,                      /* TBSENSE uses location 6 for DFRAME */          \
    gpioPortB,              /* Get the port for this loc */                   \
    13,                     /* Get the pin, location should match above */    \
  }
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
#endif

#endif /* BSPCONFIG_H */
