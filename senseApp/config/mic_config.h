/***************************************************************************//**
 *
 * @file mic_config.h
 * @brief SPV1840LR5H-B MEMS Microphone configuration file
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

#ifndef __MIC_CONFIG_H_
#define __MIC_CONFIG_H_

#include "em_adc.h"

#define MIC_CONFIG_ADC_POSSEL           adcPosSelAPORT2XCH23
#define MIC_CONFIG_ADC_ACQ_TIME         adcAcqTime1
#define MIC_CONFIG_ADC_CLOCK_FREQ       1000000

#define MIC_CONFIG_USE_LETIMER          0

#if MIC_CONFIG_USE_LETIMER
   #define MIC_CONFIG_TIMER                LETIMER0
   #define MIC_CONFIG_TIMER_CMU_CLK        cmuClock_LETIMER0

   #define MIC_CONFIG_PRS_CH               0
   #define MIC_CONFIG_ADC_PRSSEL           adcPRSSELCh0
   #define MIC_CONFIG_PRS_SOURCE           PRS_CH_CTRL_SOURCESEL_LETIMER0
   #define MIC_CONFIG_PRS_SIGNAL           PRS_CH_CTRL_SIGSEL_LETIMER0CH0
#else
   #define MIC_CONFIG_PRS_CH               4
   #define MIC_CONFIG_ADC_PRSSEL           adcPRSSELCh4
   #define MIC_CONFIG_PRS_SOURCE           PRS_CH_CTRL_SOURCESEL_CMU
   #define MIC_CONFIG_PRS_SIGNAL           PRS_CH_CTRL_SIGSEL_CMUCLKOUT1
#endif

#define MIC_CONFIG_DMA_CH               0

#endif
