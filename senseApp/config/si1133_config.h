/***************************************************************************//**
 *
 * @file si1133_config.h
 * @brief Si1133 Ambient Light and UV sensor configuration file
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

#ifndef __SI1133_CONFIG_H_
#define __SI1133_CONFIG_H_

#define SI1133_CONFIG_I2C_BUS_TIMEOUT ( 1000 )
#define SI1133_CONFIG_DEVICE          ( I2C0 )
#define SI1133_CONFIG_BUS_ADDRESS     ( 0xAA )

#endif
