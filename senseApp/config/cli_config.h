/***************************************************************************//**
 *
 * @file cli_config.h
 * @brief Command Line Interface configuration file
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

#ifndef _CLI_CONFIG_H_
#define _CLI_CONFIG_H_

#include <stdio.h>

#define CLI_CONFIG_DEFAULT_VSPRINTF_FUNCTION    vsprintf

#define CLI_CONFIG_CMDLINE_MAX_STRING_LENGTH    80
#define CLI_CONFIG_CMDLINE_MAX_ARGUMENT_COUNT   16
#define CLI_CONFIG_CMDLINE_HISTORY_COUNT        5
#define CLI_CONFIG_CMDLINE_DEFAULT_TIMEOUT      1
#define CLI_CONFIG_MAX_INLINE_HELP_CMDS         3

#define CLI_CONFIG_PRINTF_BUFFER_SIZE           256

#define CLI_CONFIG_MAX_STRING_LENGTH            256

#define CLI_CONFIG_CMD_MAX_STRING_LENGTH        16

#define CLI_CONFIG_LOGIN_ATTEMPT_COUNT          3
#define CLI_CONFIG_LOGOUT_FUNC_MAX_ARGS         3

#define CLI_CONFIG_USER_LEVEL_MAX               10
#define CLI_CONFIG_USER_MAX_COUNT               1
#define CLI_CONFIG_USER_NAME_MAX_LENGTH         8
#define CLI_CONFIG_USER_PASS_MAX_LENGTH         8

#define CLI_CONFIG_PROMPT_STRING_LENGTH         8

#define CLI_CONFIG_MAX_CMDS                     128

#define CLI_CONFIG_CMDLINE_CHAR_COMPUTER_PREFIX ':'

#endif

