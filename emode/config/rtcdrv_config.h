/***************************************************************************//**
 *
 * @file rtcdrv_config.h
 * @brief RTCDRV configuration file
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

#ifndef __SILICON_LABS_RTCDRV_CONFIG_H__
#define __SILICON_LABS_RTCDRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup EM_Drivers
 * @{
 ******************************************************************************/

 /***************************************************************************//**
 * @addtogroup RTCDRV
 * @{
 ******************************************************************************/

/// @brief Define the number of timers the application needs.
#define EMDRV_RTCDRV_NUM_TIMERS     (5)

/// @brief Define to include wallclock functionality.
#define EMDRV_RTCDRV_WALLCLOCK_CONFIG

/// @brief Define to enable integration with SLEEP driver.
//#define EMDRV_RTCDRV_SLEEPDRV_INTEGRATION

/** @} (end addtogroup RTCDRV) */
/** @} (end addtogroup EM_Drivers) */

#endif /* __SILICON_LABS_RTCDRV_CONFIG_H__ */
