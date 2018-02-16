/***************************************************************************//**
 *
 * @file token_config.h
 * @brief Token configuration parameters
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

#ifndef TOKEN_CONFIG_H_INCLUDED__
#define TOKEN_CONFIG_H_INCLUDED__

#define TOKEN_DEVINFO_BASE_ADDRESS    0x0FE08000
#define TOKEN_LOCKBITS_BASE_ADDRESS   0x0FE04000
#define TOKEN_MAINFLASH_BASE_ADDRESS  0x00000000
#define TOKEN_USERDATA_BASE_ADDRESS   0x0FE00000

#define TOKEN_COUNT 8

#define SB_RADIO_CTUNE_OFFSET          0x0100
#define SB_RADIO_CTUNE_ADDR            (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_CTUNE_OFFSET)
#define SB_RADIO_CTUNE_SIZE            2

#define SB_RADIO_OUTPUT_POWER_OFFSET   0x0702
#define SB_RADIO_OUTPUT_POWER_ADDR     (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_OUTPUT_POWER_OFFSET)
#define SB_RADIO_OUTPUT_POWER_SIZE     2

#define SB_RADIO_CHANNEL_OFFSET        0x0704
#define SB_RADIO_CHANNEL_ADDR          (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_CHANNEL_OFFSET)
#define SB_RADIO_CHANNEL_SIZE          2

#define SB_RADIO_NODE_ID_OFFSET        0x0706
#define SB_RADIO_NODE_ID_ADDR          (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_NODE_ID_OFFSET)
#define SB_RADIO_NODE_ID_SIZE          1

#define SB_RADIO_NODE_ROLE_OFFSET      0x0707
#define SB_RADIO_NODE_ROLE_ADDR        (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_NODE_ROLE_OFFSET)
#define SB_RADIO_NODE_ROLE_SIZE        1

#define SB_RADIO_BEACON_PERIOD_OFFSET  0x0708
#define SB_RADIO_BEACON_PERIOD_ADDR    (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_BEACON_PERIOD_OFFSET)
#define SB_RADIO_BEACON_PERIOD_SIZE    2

#define SB_BALL_COLOUR_OFFSET          0x0710
#define SB_BALL_COLOUR_ADDR            (TOKEN_USERDATA_BASE_ADDRESS + SB_BALL_COLOUR_OFFSET)
#define SB_BALL_COLOUR_SIZE            4

#define SB_BALL_COUNT_OFFSET           0x0714
#define SB_BALL_COUNT_ADDR             (TOKEN_USERDATA_BASE_ADDRESS + SB_BALL_COUNT_OFFSET)
#define SB_BALL_COUNT_SIZE             1


#endif
