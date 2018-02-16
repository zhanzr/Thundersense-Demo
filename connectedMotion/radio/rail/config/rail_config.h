// Copyright 2016 Silicon Laboratories, Inc.
//
//


/***************************************************************************//**
 * @file rail_config.h
 * @brief RAIL Configuration
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/
//=============================================================================
//
//  WARNING: Auto-Generated Radio Config Header  -  DO NOT EDIT
//
//=============================================================================

#ifndef __RAIL_CONFIG_H__
#define __RAIL_CONFIG_H__

#include <stdint.h>
#include "rail_types.h"


extern const uint32_t generated[];

extern const uint32_t *configList[];
extern const char *configNames[];

#define NUM_RAIL_CONFIGS 1

extern RAIL_ChannelConfigEntry_t generated_channels[];
extern const RAIL_ChannelConfig_t generated_channelConfig;

extern const RAIL_ChannelConfig_t *channelConfigs[];
extern const RAIL_FrameType_t *frameTypeConfigList[];

#define RADIO_CONFIG_BASE_FREQUENCY 2450000000UL


#endif // __RAIL_CONFIG_H__
