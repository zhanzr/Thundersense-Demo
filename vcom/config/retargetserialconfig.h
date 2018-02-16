/***************************************************************************//**
 *
 * @file retargetserialconfig.h
 * @brief Provide stdio retargeting configuration parameters
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

#ifndef __RETARGETSERIALCONFIG_H
#define __RETARGETSERIALCONFIG_H

/* Override if needed with commandline parameter -DRETARGET_xxx */

#if !defined(RETARGET_USART0) && !defined(RETARGET_VCOM)
#define RETARGET_USART0    /* Use USART0 by default. */
#endif

#if defined(RETARGET_USART0) || defined(RETARGET_VCOM)
  #define RETARGET_IRQ_NAME    USART0_RX_IRQHandler         /* UART IRQ Handler */
  #define RETARGET_CLK         cmuClock_USART0              /* HFPER Clock */
  #define RETARGET_IRQn        USART0_RX_IRQn               /* IRQ number */
  #define RETARGET_UART        USART0                       /* UART instance */
  #define RETARGET_TX          USART_Tx                     /* Set TX to USART_Tx */
  #define RETARGET_RX          USART_Rx                     /* Set RX to USART_Rx */

  #define RETARGET_TX_LOCATION 0                            /* Location of of USART TX pin */
  #define RETARGET_RX_LOCATION 0                            /* Location of of USART RX pin */

  #define RETARGET_TXPORT      gpioPortA                    /* UART transmission port */
  #define RETARGET_TXPIN       0                            /* UART transmission pin */
  #define RETARGET_RXPORT      gpioPortA                    /* UART reception port */
  #define RETARGET_RXPIN       1                            /* UART reception pin */
  #define RETARGET_USART       1                            /* Includes em_usart.h */

  #define RETARGET_PERIPHERAL_ENABLE()

#else
#error "Illegal USART selection."
#endif

#endif
