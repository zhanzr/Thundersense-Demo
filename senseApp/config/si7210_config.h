/***************************************************************************//**
 *
 * @file si7210_config.h
 * @brief Si7210 Hall Effect Sensor configuration file
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

#ifndef __SI7210_CONFIG_H_
#define __SI7210_CONFIG_H_

#define SI7210_CONFIG_I2C_DEVICE        I2C0
#define SI7210_CONFIG_I2C_BUS_TIMEOUT   1000
#define SI7210_CONFIG_I2C_BUS_ADDRESS   0x30
#define SI7210_CONFIG_DEVICE_ID         0x11

#define SI7210_CONFIG_PORT_OUT1         gpioPortB
#define SI7210_CONFIG_PIN_OUT1          11

#endif
