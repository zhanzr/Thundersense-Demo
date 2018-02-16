/***************************************************************************//**
 *
 * @file mx25_config.h
 * @brief MX25R8035F NOR flash configuration file
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

#ifndef __MX25_CONFIG_H
#define __MX25_CONFIG_H

#include "em_device.h"
#include "em_gpio.h"

#define MX25_PORT_MOSI         gpioPortC
#define MX25_PIN_MOSI          6
#define MX25_PORT_MISO         gpioPortC
#define MX25_PIN_MISO          7
#define MX25_PORT_SCLK         gpioPortC
#define MX25_PIN_SCLK          8
#define MX25_PORT_CS           gpioPortA
#define MX25_PIN_CS            4

#define MX25_USART             USART1
#define MX25_USART_CLK         cmuClock_USART1

#define MX25_USART_LOC_MOSI    USART_ROUTELOC0_TXLOC_LOC11
#define MX25_USART_LOC_MISO    USART_ROUTELOC0_RXLOC_LOC11
#define MX25_USART_LOC_SCLK    USART_ROUTELOC0_CLKLOC_LOC11

#endif
