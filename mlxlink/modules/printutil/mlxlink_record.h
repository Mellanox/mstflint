/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#define PDDR_LINE_LEN               34

/*
 * Json output objects name
 */
#define JSON_WARN_SECTION       "warning"
#define JSON_MSG                "message"
#define JSON_STATUS_SECTION     "status"
#define JSON_STATUS_CODE        "code"
#define JSON_RESULT_SECTION     "result"
#define JSON_CONFIG_SECTION     "configurations"
#define JSON_OUTPUT_SECTION     "output"
#define JSON_MASK_TITLE         "mask"
#define JSON_VALUES_TITLE       "values"

/*
 * Output headers name
 */
#define HEADER_SUPPORTED_INFO   "Supported Info"
#define HEADER_FEC_INFO         "FEC Capability Info"

#define PRINT_UNDER_TITLE(len) \
    for (int i = 0; i < len; i++) { \
        printf("-"); \
    } \
    printf("\n");

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum STATUS_COLOR {
    RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, RESET
};

/*
 * Records enums
 */
enum PDDR_OPERATIONAL_INFO {
    PDDR_STATE,
    PDDR_PHYSICAL_STATE,
    PDDR_SPEED,
    PDDR_WIDTH,
    PDDR_FEC,
    PDDR_LOOPBACK_MODE,
    PDDR_AUTO_NEGOTIATION,

    // Insert before PDDR_OPERATIONAL_INFO_LASR
    PDDR_OPERATIONAL_INFO_LAST
};

enum PDDR_SUPPORTED_INFO {
    PDDR_ENABLED_LINK_SPEED,
    PDDR_SUPPORTED_LINK_SPEED,
    // Insert before PDDR_SUPPORTED_INFO_LAST
    PDDR_SUPPORTED_INFO_LAST
};

enum PDDR_TRUOBLESHOOTING_INFO {
    PDDR_STATUS_OPCODE,
    PDDR_GROUP_OPCODE,
    PDDR_RECOMMENDATION,
    PDDR_TIME_TO_LINK_UP,
    // Insert before PDDR_TRUOBLESHOOTING_INFO_LAST
    PDDR_TRUOBLESHOOTING_INFO_LAST
};

enum TEST_MODE_INFO {
    TEST_MODE_PPRT_PRBS_MODE,
    TEST_MODE_PPTT_PRBS_MODE,
    TEST_MODE_PPRT_LANE_RATE,
    TEST_MODE_PPTT_LANE_RATE,
    TEST_MODE_PPRT_TUNING_STATUS,
    TEST_MODE_PPRT_LOCK_STATUS,

    // Insert before TEST_MODE_INFO_LAST
    TEST_MODE_INFO_LAST
};

enum PCIE_INFO {
    PCIE_LINK_DPN,
    PCIE_LINK_SPEED_ACTIVE_ENABLED,
    LINK_WIDTH_ACTIVE_ENABLED,
    DEVICE_STATUS,

    // Insert before PCIE_INFO_LAST
    PCIE_INFO_LAST
};

enum MODULE_INFO {
    MODULE_INFO_IDENTIFIER,
    MODULE_INFO_COMPLIANCE,
    MODULE_INFO_CABLE_TECHNOLOGY,
    MODULE_INFO_CABLE_TYPE,
    MODULE_INFO_OUI,
    MODULE_INFO_VENDOR_NAME,
    MODULE_INFO_VENDOR_PART_NUMBER,
    MODULE_INFO_VENDOR_SERIAL_NUMBER,
    MODULE_INFO_REV,
    MODULE_INFO_ATTENUATION_5G_7G_12G_DB,
    MODULE_INFO_FW_VERSION,
    MODULE_INFO_WAVELENGTH_NM,
    MODULE_INFO_TRANSFER_DISTANCE_M,
    MODULE_INFO_DIGITAL_DIAGNOSTIC_MONITORING,
    MODULE_INFO_POWER_CLASS,
    MODULE_INFO_CDR_RX,
    MODULE_INFO_CDR_TX,
    MODULE_INFO_LOS_ALARM,
    MODULE_INFO_TEMPERATURE_C,
    MODULE_INFO_VOLTAGE,
    MODULE_INFO_BIAS_CURRENT_mA,
    MODULE_INFO_RX_POWER_CURRENT_dBm,
    MODULE_INFO_TX_POWER_CURRENT_dBm,

    // Insert before MODULE_INFO_LAST
    MODULE_INFO_LAST
};

enum BER_INFO {
    BER_TIME_SINCE_LAST_CLEAR,
    BER_EFFECTIVE_PHYSICAL_ERRORS,
    BER_EFFECTIVE_PHYSICAL_BER,
    BER_RAW_PHYSICAL_BER,
    BER_RAW_PHYSICAL_ERRORS_PER_LANE,
    BER_LINK_DOWNED_COUNTER,
    BER_LINK_RECOVERY_COUNTER,

    // Insert before BER_INFO_LAST
    BER_INFO_LAST
};

enum TEST_MODE_BER_INFO {
    TEST_MODE_BER_TIME_SINCE_LAST_CLEAR,
    TEST_MODE_BER_PRBS_ERRORS,
    TEST_MODE_BER,

    // Insert before TEST_MODE_BER_INFO_LAST
    TEST_MODE_BER_INFO_LAST
};

enum MPCNT_PERFORMANCE_INFO {
    MPCNT_RX_ERRORS,
    MPCNT_TX_ERRORS,
    MPCNT_CRC_ERROR_DLLP,
    MPCNT_CRC_ERROR_TLP,

    // Insert before MPCNT_PERFORMANCE_INFO_LAST
    MPCNT_PERFORMANCE_INFO_LAST
};

enum MPCNT_TIMER_INFO {
    MPCNT_DL_DOWN,

    // Insert before MPCNT_PERFORMANCE_INFO_LAST
    MPCNT_TIMER_INFO_LAST
};

enum EYE_OPENING_INFO {
    EYE_PHYSICAL_GRADE,
    EYE_HEIGHT_EYE_OPENING,
    EYE_PHASE_EYE_OPENING,

    // Insert before EYE_OPENING_INFO_LAST
    EYE_OPENING_INFO_LAST
};

enum FEC_CAP_INFO {
    FEC_CAP_100G,
    FEC_CAP_50G,
    FEC_CAP_40G,
    FEC_CAP_25G,
    FEC_CAP_10G,

    // Insert before FEC_CAP_INFO_LASE
    FEC_CAP_INFO_LASE
};

enum DEVICE_INFO {
    DEVICE_PART_NUMBER,
    DEVICE_PART_NAME,
    DEVICE_SERIAL_NUMBER,
    DEVICE_REVISION,
    DEVICE_FW_VERSION,

    // Insert before DEVICE_INFO_LAST
    DEVICE_INFO_LAST
};

enum BER_MONITOR_INFO {
    BER_MONITOR_STATE,
    BER_MONITOR_TYPE,

    // Insert before BER_MONITOR_INFO_LAST
    BER_MONITOR_INFO_LAST
};

enum EXT_PHY_INFO {
    EXT_PHY_TWISTED_PAIR_FORCE_MODE,

    EXT_PHY_INFO_INFO_LAST
};

enum LINK_DOWN_BLAME_INFO {
    LINK_DOWN_BLAME,
    LINK_DOWN_REASON,

    LINK_DOWN_BLAME_INFO_LAST
};

class MlxlinkRecord {

public:
    MlxlinkRecord();
    virtual ~MlxlinkRecord();
    friend std::ostream & operator << (std::ostream &out, const MlxlinkRecord &mlxlinkRecord);

    std::string key;
    std::string val;
    std::string color;
    bool visible;
    bool arrayValue;
    static bool jsonFormat;

    static std::string state2Color(u_int32_t state);
    static std::string supported2Color(const std::string &supported);
    static void changeColorOS(const std::string &color, bool newLine = false);
    static short unsigned int getWinColor(const std::string &color);
    static void printFlagLine(const char sflag_s, const std::string &flag_l,
            const std::string &param, const std::string &desc);
    static std::string addSpaceForSlrg(const std::string &str);
    static void printErrorsSection(const std::string &title, const std::string &lines);
    static void printCmdLine(const std::string &line, Json::Value &jsonRoot);
    static void printErr(const std::string &err);
    static void printWar(const std::string &war, Json::Value &jsonRoot);
    static std::vector<std::string> split(const std::string& str, const std::string &delim = " ");
    static void trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
};

std::ostream & operator << (std::ostream &out, const MlxlinkRecord &mlxlinkRecord);

#endif /* MLXLINKRECORD_H */
