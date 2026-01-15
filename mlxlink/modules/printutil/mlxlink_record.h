/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 *
 */

#ifndef MLXLINKRECORD_H
#define MLXLINKRECORD_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <common/compatibility.h>
#include <json/json.h>

#define PDDR_LINE_LEN 37
#define RX_RECOVERY_COUNTERS_LINE_LEN 46

/*
 * Json output objects name
 */
#define JSON_WARN_SECTION "warning"
#define JSON_MSG "message"
#define JSON_STATUS_SECTION "status"
#define JSON_STATUS_CODE "code"
#define JSON_RESULT_SECTION "result"
#define JSON_CONFIG_SECTION "configurations"
#define JSON_OUTPUT_SECTION "output"
#define JSON_MASK_TITLE "mask"
#define JSON_VALUES_TITLE "values"

/*
 * Output headers name
 */
#define HEADER_SUPPORTED_INFO "Supported Info"
#define HEADER_FEC_INFO "FEC Capability Info"
#define HEADER_PLR_INFO "PLR Info"
#define HEADER_KR_INFO "KR Info"
#define HEADER_RX_RECOVERY_COUNTERS "Rx Recovery Counters"
#define HEADER_PERIODIC_EQ "PEQ info"

#define PRINT_UNDER_TITLE(len)    \
    for (int i = 0; i < len; i++) \
    {                             \
        printf("-");              \
    }                             \
    printf("\n");

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 IDENT IDENT2

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

enum STATUS_COLOR
{
    RED,
    BLUE,
    YELLOW,
    GREEN,
    MAGENTA,
    CYAN,
    RESET
};

enum STATUS_DDM_FLAGS_TYPE
{
    DDM_FLAG_WARN,
    DDM_FLAG_ALARM
};

/*
 * Records size
 */
#define TOOL_INFORMAITON_INFO_LAST 4
#define PDDR_OPERATIONAL_INFO_LAST 7
#define PDDR_SUPPORTED_INFO_LAST 2
#define PDDR_TRUOBLESHOOTING_INFO_LAST 4
#define TEST_MODE_INFO_LAST 8
#define PCIE_INFO_LAST 4
#define MODULE_INFO_LAST 53
#define MODULE_INFO_AMBER 126
#define BER_INFO_LAST 7
#define BER_INFO_NDR_LAST 12
#define TEST_MODE_BER_INFO_LAST 4
#define MPCNT_PERFORMANCE_INFO_LAST 4
#define MPCNT_TIMER_INFO_LAST 1
#define EYE_OPENING_INFO_LAST 9
#define FEC_CAP_INFO_LAST 6
#define DEVICE_INFO_LAST 5
#define BER_MONITOR_INFO_LAST 2
#define EXT_PHY_INFO_INFO_LAST 1
#define LINK_DOWN_BLAME_INFO_LAST 2
#define MODULE_PMPT_INFO_LAST 8
#define MODULE_PMPD_INFO_LAST 6
#define PLR_INFO_LAST 3
#define KR_INFO_LAST 5
#define RX_RECOVERY_COUNTERS_LAST 10
#define PERIODIC_EQ_INFO_LAST 2

class MlxlinkRecord
{
public:
    MlxlinkRecord();
    virtual ~MlxlinkRecord();
    friend std::ostream& operator<<(std::ostream& out, const MlxlinkRecord& mlxlinkRecord);

    static std::string state2Color(u_int32_t state);
    static std::string ddmFlagValue2Color(u_int32_t val, u_int32_t type);
    static std::string supported2Color(const std::string& supported);
    static void changeColorOS(const std::string& color, bool newLine = false);
    static short unsigned int getWinColor(const std::string& color);
    static void
      printFlagLine(const char sflag_s, const std::string& flag_l, const std::string& param, const std::string& desc);
    static void printFlagLineWithAcronym(const char flag_s,
                                         const std::string& flag_l,
                                         const char flag_acr_s,
                                         const std::string& flag_acr_l,
                                         const std::string& param,
                                         const std::string& desc);
    static std::string addSpace(const std::string& str, u_int32_t size, bool right = true);
    static std::string addSpaceForDDM(const std::string& str);
    static std::string addSpaceForSlrg(const std::string& str);
    static std::string addSpaceForModulePrbs(const std::string& str);
    static void printErrorsSection(const std::string& title, const std::string& lines);
    static void printCmdLine(const std::string& line, Json::Value& jsonRoot);
    static void printErr(const std::string& err);
    static void printWar(const std::string& war, Json::Value& jsonRoot);
    static std::vector<std::string> split(const std::string& str, const std::string& delim = " ");
    static void trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

    std::string key;
    std::string val;
    std::string color;
    bool visible;
    bool arrayValue;
    bool colorKey;
    int lineLen;
    static bool jsonFormat;
    static std::ostream* cOut;
    static FILE* stdOut;
};

std::ostream& operator<<(std::ostream& out, const MlxlinkRecord& mlxlinkRecord);

#endif /* MLXLINKRECORD_H */
