/***************************************************************************//**
 *
 * @file i2cspmconfig.h
 * @brief I2C SPM driver configuration parameters
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

#ifndef __SILICON_LABS_I2CSPM_CONFIG_H__
#define __SILICON_LABS_I2CSPM_CONFIG_H__

/* I2C SPM driver config. This default override only works if one I2C interface
   is in use. If multiple interfaces are in use, define the peripheral setup
   inside the application in a I2CSPM_Init_TypeDef and then pass the initialization
   struct to I2CSPM_Init(). */

#define I2CSPM_INIT_DEFAULT                                                    \
  { I2C0,                      /* Use I2C instance 0 */                        \
    gpioPortC,                 /* SCL port */                                  \
    11,                        /* SCL pin */                                   \
    gpioPortC,                 /* SDA port */                                  \
    10,                        /* SDA pin */                                   \
    15,                        /* Port location of SCL signal */               \
    15,                        /* Port location of SDA signal */               \
    0,                         /* Use currently configured reference clock */  \
    I2C_FREQ_STANDARD_MAX,     /* Set to standard rate  */                     \
    i2cClockHLRStandard,       /* Set to use 4:4 low/high duty cycle */        \
  }

#define I2CSPM_TRANSFER_TIMEOUT 300000

#endif

