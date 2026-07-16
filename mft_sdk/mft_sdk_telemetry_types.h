/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id$
 *
 */

#pragma once

#include <mft_sdk/mft_sdk_query.h>
#include <mft_sdk/mft_sdk_types.h>

#define MODULE_INFO_MAX_LENGTH 256
#define MAX_NUM_OF_LANES 16
#define MAX_NUM_OF_BINS 32
#define MAX_NUM_OF_CHANNELS 8

// Telemetry Operational info capability bits:
#define TELEMETRY_OP_INFO_STATE 0            // State of the device.
#define TELEMETRY_OP_INFO_PHYSICAL_STATE 1   // Physical state of the device.
#define TELEMETRY_OP_INFO_SPEED 2            // Speed of the device.
#define TELEMETRY_OP_INFO_WIDTH 3            // Width of the device.
#define TELEMETRY_OP_INFO_FEC 4              // FEC of the device.
#define TELEMETRY_OP_INFO_LOOPBACK_MODE 5    // Loopback mode of the device.
#define TELEMETRY_OP_INFO_AUTO_NEGOTIATION 6 // Auto negotiation of the device.

// Counters Info capability bits:
#define TELEMETRY_COUNTERS_INFO_TIME_SINCE_LAST_CLEAR 0        // Time since last clear.
#define TELEMETRY_COUNTERS_INFO_SYMBOL_ERRORS 1                // Symbol errors.
#define TELEMETRY_COUNTERS_INFO_SYMBOL_BER 2                   // Symbol BER.
#define TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_ERRORS 3    // Effective physical errors.
#define TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_BER 4       // Effective physical BER.
#define TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_ERRORS_PER_LANE 5 // Raw physical errors per lane.
#define TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER_PER_LANE 6    // Raw physical BER per lane.
#define TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER 7             // Raw physical BER.
#define TELEMETRY_COUNTERS_INFO_LINK_DOWN_COUNTER 8            // Link down counter.
#define TELEMETRY_COUNTERS_INFO_LINK_ERROR_RECOVERY_COUNTER 9  // Link error recovery counter.

// Cable DDM Info capability bits:
#define TELEMETRY_CABLE_DDM_INFO_TEMPERATURE 0        // Temperature.
#define TELEMETRY_CABLE_DDM_INFO_VOLTAGE 1            // Voltage.
#define TELEMETRY_CABLE_DDM_INFO_NUMBER_OF_CHANNELS 2 // Number of channels.
#define TELEMETRY_CABLE_DDM_INFO_FLAGS 3              // Flags.
#define TELEMETRY_CABLE_DDM_INFO_CHANNELS 4           // Channels.
#define TELEMETRY_CABLE_DDM_INFO_THRESHOLDS 5         // Thresholds.

// Module Info capability bits - Vendor Info fields:
#define TELEMETRY_MODULE_INFO_IDENTIFIER 0
#define TELEMETRY_MODULE_INFO_COMPLIANCE 1
#define TELEMETRY_MODULE_INFO_CABLE_TECHNOLOGY 2
#define TELEMETRY_MODULE_INFO_CABLE_TYPE 3
#define TELEMETRY_MODULE_INFO_OUI 4
#define TELEMETRY_MODULE_INFO_VENDOR_NAME 5
#define TELEMETRY_MODULE_INFO_VENDOR_PART_NUMBER 6
#define TELEMETRY_MODULE_INFO_VENDOR_SERIAL_NUMBER 7
#define TELEMETRY_MODULE_INFO_VENDOR_REVISION 8
#define TELEMETRY_MODULE_INFO_WAVELENGTH 9
#define TELEMETRY_MODULE_INFO_TRANSFER_DISTANCE 10
// Module Info capability bits - Attenuation fields:
#define TELEMETRY_MODULE_INFO_ATTENUATION_5G 11
#define TELEMETRY_MODULE_INFO_ATTENUATION_7G 12
#define TELEMETRY_MODULE_INFO_ATTENUATION_12G 13
#define TELEMETRY_MODULE_INFO_ATTENUATION_25G 14
#define TELEMETRY_MODULE_INFO_ATTENUATION_53G 15
// Module Info capability bits - FW Version:
#define TELEMETRY_MODULE_INFO_FW_VERSION 16
// Module Info capability bits - Power and CDR Info fields:
#define TELEMETRY_MODULE_INFO_DIGITAL_DIAGNOSTIC_MONITORING 17
#define TELEMETRY_MODULE_INFO_POWER_CLASS 18
#define TELEMETRY_MODULE_INFO_MAX_POWER 19
#define TELEMETRY_MODULE_INFO_CDR_RX 20
#define TELEMETRY_MODULE_INFO_CDR_TX 21
// Module Info capability bits - Latency Info fields:
#define TELEMETRY_MODULE_INFO_INTRA_ASIC_LATENCY 22
#define TELEMETRY_MODULE_INFO_MODULE_DATAPATH_LATENCY 23
#define TELEMETRY_MODULE_INFO_ROUND_TRIP_LATENCY 24
// Module Info capability bits - BER Module Info fields:
#define TELEMETRY_MODULE_INFO_SNR_MEDIA_LANES 25
#define TELEMETRY_MODULE_INFO_SNR_HOST_LANES 26
#define TELEMETRY_MODULE_INFO_IB_CABLE_WIDTH 27
#define TELEMETRY_MODULE_INFO_MEMORY_MAP_REVISION 28
#define TELEMETRY_MODULE_INFO_LINEAR_DIRECT_DRIVE 29
#define TELEMETRY_MODULE_INFO_CABLE_BREAKOUT 30
#define TELEMETRY_MODULE_INFO_SMF_LENGTH 31
#define TELEMETRY_MODULE_INFO_CABLE_RX_AMP 32
#define TELEMETRY_MODULE_INFO_CABLE_RX_EMPHASIS 33
#define TELEMETRY_MODULE_INFO_CABLE_RX_POST_EMPHASIS 34
#define TELEMETRY_MODULE_INFO_CABLE_TX_EQUALIZATION 35
#define TELEMETRY_MODULE_INFO_WAVELENGTH_TOLERANCE 36
#define TELEMETRY_MODULE_INFO_MODULE_STATE 37
#define TELEMETRY_MODULE_INFO_DATA_PATH_STATE_PER_LANE 38
#define TELEMETRY_MODULE_INFO_RX_OUTPUT_VALID_PER_LANE 39
#define TELEMETRY_MODULE_INFO_NOMINAL_BIT_RATE 40
#define TELEMETRY_MODULE_INFO_RX_POWER_TYPE 41
#define TELEMETRY_MODULE_INFO_MANUFACTURING_DATE 42
#define TELEMETRY_MODULE_INFO_ACTIVE_SET_HOST_COMPLIANCE_CODE 43
#define TELEMETRY_MODULE_INFO_ACTIVE_SET_MEDIA_COMPLIANCE_CODE 44
#define TELEMETRY_MODULE_INFO_ERROR_CODE_RESPONSE 45
#define TELEMETRY_MODULE_INFO_MODULE_FW_FAULT 46
#define TELEMETRY_MODULE_INFO_DATA_PATH_FW_FAULT 47
#define TELEMETRY_MODULE_INFO_TX_FAULT_PER_LANE 48
#define TELEMETRY_MODULE_INFO_TX_LOS_PER_LANE 49
#define TELEMETRY_MODULE_INFO_TX_CDR_LOL_PER_LANE 50
#define TELEMETRY_MODULE_INFO_RX_LOS_PER_LANE 51
#define TELEMETRY_MODULE_INFO_RX_CDR_LOL_PER_LANE 52
#define TELEMETRY_MODULE_INFO_TX_ADAPTIVE_EQ_FAULT_PER_LANE 53

/**
 * @brief Numeric value represented in scientific notation.
 */
typedef struct ScientificNotation_t
{
    double significand; /**< Significant digits of the value. */
    int exponent;       /**< Base-10 exponent of the value. */
} ScientificNotation;

/**
 * @brief Logical operational state of a device port.
 */
typedef enum OperationalInfoState_t
{
    OPERATIONAL_INFO_STATE_DISABLE = 0,
    OPERATIONAL_INFO_STATE_PORT_PLL_DOWN = 1,
    OPERATIONAL_INFO_STATE_POLLING = 2,
    OPERATIONAL_INFO_STATE_ACTIVE = 3,
    OPERATIONAL_INFO_STATE_CLOSE_PORT = 4,
    OPERATIONAL_INFO_STATE_PHYSICAL_LINKUP = 5,
    OPERATIONAL_INFO_STATE_SLEEP = 6,
    OPERATIONAL_INFO_STATE_RX_DISABLE = 7,
    OPERATIONAL_INFO_STATE_SIGNAL_DETECT = 8,
    OPERATIONAL_INFO_STATE_RECEIVER_DETECT = 9,
    OPERATIONAL_INFO_STATE_SYNC_PEER = 10,
    OPERATIONAL_INFO_STATE_NEGOTIATION = 11,
    OPERATIONAL_INFO_STATE_TRAINING = 12,
    OPERATIONAL_INFO_STATE_SUB_FSM_ACTIVE = 13,
} OperationalInfoState;

/**
 * @brief Physical link state reported for Ethernet or InfiniBand ports.
 */
typedef enum operationalInfoPhysicalState_t
{
    // Ethernet Physical states
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ENABLE = 0,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_XMIT_DISABLE = 1,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ABILITY_DETECT = 2,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ACK_DETECT = 3,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_COMPLETE_ACK = 4,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_AN_GOOD_CHECK = 5,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_LINK_UP = 6,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_NEXT_PAGE_WAIT = 7,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_LINK_STAT_CHECK = 8,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_EXTRA_TUNE = 9,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_FIX_REVERSALS = 10,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_IB_FAIL = 11,
    OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_POST_LOCK_TUNE = 12,
    // IB Physical states
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_NA = 100,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_INITIALIZING = 101,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_RECOVER_CONFIG = 102,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_CONFIG_TEST = 103,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_WAIT_REMOTE_TEST = 104,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_WAIT_CFG_ENHANCED = 105,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_CONFIG_IDLE = 106,
    OPERATIONAL_INFO_PHYSICAL_STATE_IB_LINK_UP = 107,
} OperationalInfoPhysicalState;

/**
 * @brief Operational link speed reported for Ethernet, InfiniBand, or NVLink.
 */
typedef enum operationalInfoSpeed_t
{
    // Ethernet
    OPERATIONAL_INFO_SPEED_BASET10M = 0,   // "BaseT10M"
    OPERATIONAL_INFO_SPEED_BASETX100M = 1, // "BaseTx100M"
    OPERATIONAL_INFO_SPEED_BASET1000M = 2, // "BaseT1000M"
    OPERATIONAL_INFO_SPEED_10M = 3,        // "10M"
    OPERATIONAL_INFO_SPEED_100M = 4,       // "100M"
    OPERATIONAL_INFO_SPEED_CX = 5,         // "CX"
    OPERATIONAL_INFO_SPEED_KX = 6,         // "KX"
    OPERATIONAL_INFO_SPEED_CX4 = 7,        // "CX4"
    OPERATIONAL_INFO_SPEED_KX4 = 8,        // "KX4"
    OPERATIONAL_INFO_SPEED_BASET10G = 9,   // "BaseT10G"
    OPERATIONAL_INFO_SPEED_10GBE = 10,     // "10GbE"
    OPERATIONAL_INFO_SPEED_20GBE = 11,     // "20GbE"
    OPERATIONAL_INFO_SPEED_25GBE = 12,     // "25GbE"
    OPERATIONAL_INFO_SPEED_40GBE = 13,     // "40GbE"
    OPERATIONAL_INFO_SPEED_50GBE = 14,     // "50GbE"
    OPERATIONAL_INFO_SPEED_56GBE = 15,     // "56GbE"
    OPERATIONAL_INFO_SPEED_100GBE = 16,    // "100GbE"
    OPERATIONAL_INFO_SPEED_1G = 17,        // "1G"
    OPERATIONAL_INFO_SPEED_2_5G = 18,      // "2.5G"
    OPERATIONAL_INFO_SPEED_5G = 19,        // "5G"
    OPERATIONAL_INFO_SPEED_10G = 20,       // "10G"
    OPERATIONAL_INFO_SPEED_25G = 21,       // "25G"
    OPERATIONAL_INFO_SPEED_40G = 22,       // "40G"
    OPERATIONAL_INFO_SPEED_50G = 23,       // "50G"
    OPERATIONAL_INFO_SPEED_100G = 24,      // "100G"
    OPERATIONAL_INFO_SPEED_200G = 25,      // "200G"
    OPERATIONAL_INFO_SPEED_400G = 26,      // "400G"
    OPERATIONAL_INFO_SPEED_800G = 27,      // "800G"
    OPERATIONAL_INFO_SPEED_1600G = 28,     // "1600G"

    // InfiniBand
    OPERATIONAL_INFO_SPEED_IB_SDR = 100,   // "IB-SDR"
    OPERATIONAL_INFO_SPEED_IB_DDR = 101,   // "IB-DDR"
    OPERATIONAL_INFO_SPEED_IB_QDR = 102,   // "IB-QDR"
    OPERATIONAL_INFO_SPEED_IB_FDR10 = 103, // "IB-FDR10"
    OPERATIONAL_INFO_SPEED_IB_FDR = 104,   // "IB-FDR"
    OPERATIONAL_INFO_SPEED_IB_EDR = 105,   // "IB-EDR"
    OPERATIONAL_INFO_SPEED_IB_HDR = 106,   // "IB-HDR"
    OPERATIONAL_INFO_SPEED_IB_NDR = 107,   // "IB-NDR"
    OPERATIONAL_INFO_SPEED_IB_XDR = 108,   // "IB-XDR"

    // NVLink
    OPERATIONAL_INFO_SPEED_NVLINK_SDR = 200,            // "NVLink-SDR"
    OPERATIONAL_INFO_SPEED_NVLINK_DDR = 201,            // "NVLink-DDR"
    OPERATIONAL_INFO_SPEED_NVLINK_QDR = 202,            // "NVLink-QDR"
    OPERATIONAL_INFO_SPEED_NVLINK_FDR10 = 203,          // "NVLink-FDR10"
    OPERATIONAL_INFO_SPEED_NVLINK_FDR = 204,            // "NVLink-FDR"
    OPERATIONAL_INFO_SPEED_NVLINK_EDR = 205,            // "NVLink-EDR"
    OPERATIONAL_INFO_SPEED_NVLINK_HDR = 206,            // "NVLink-HDR"
    OPERATIONAL_INFO_SPEED_NVLINK_NDR = 207,            // "NVLink-NDR"
    OPERATIONAL_INFO_SPEED_NVLINK_XDR = 208,            // "NVLink-XDR"
    OPERATIONAL_INFO_SPEED_NVLINK_328G_2X_MODE_B = 209, // "NVLink-328G_2X_MODE_B"
    OPERATIONAL_INFO_SPEED_NVLINK_360G_2X_MODE_B = 210, // "NVLink-360G_2X_MODE_B"
    OPERATIONAL_INFO_SPEED_NVLINK_400G_2X_MODE_B = 211, // "NVLink-400G_2X_MODE_B"
    OPERATIONAL_INFO_SPEED_NVLINK_378G_2X_MODE_B = 212, // "NVLink-378G_2X_MODE_B"
    OPERATIONAL_INFO_SPEED_NVLINK_345G_2X_MODE_B = 213, // "NVLink-345G_2X_MODE_B"
} OperationalInfoSpeed;

/**
 * @brief Forward error correction mode used by the link.
 */
typedef enum operationalInfoFec_t
{
    OPERATIONAL_INFO_FEC_NO_FEC = 0,       // "No FEC"
    OPERATIONAL_INFO_FEC_FIRECODE_FEC = 1, // "Firecode FEC"
    OPERATIONAL_INFO_FEC_STANDARD_RS_FEC_528_514 = 2,
    OPERATIONAL_INFO_FEC_STANDARD_LL_FEC_271_257 = 3,              // "Standard LL RS-FEC - RS(271,257)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_QUAD_RS_FEC_544_514 = 4,      // "Interleaved Quad RS-FEC - (544,514)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_QUAD_RS_FEC_PLR_546_516 = 5,  // "Interleaved Quad RS-FEC + PLR - (546,516)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_STANDARD_RS_FEC_544_514 = 6,  // "Interleaved_Standard_RS-FEC - (544,514)"
    OPERATIONAL_INFO_FEC_STANDARD_RS_FEC_544_514 = 7,              // "Standard_RS-FEC - (544,514)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_OCTET_RS_FEC_PLR_546_516 = 8, // "Interleaved Octet RS-FEC + PLR - (546,516)"
    OPERATIONAL_INFO_FEC_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_272_258 =
      9, // "Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_272_258 =
      10, // "Interleaved_Ethernet_Consortium_LL_50G_RS_FEC -(272,257+1)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_STANDARD_RS_FEC_PLR_544_514 = 11, // "Interleaved_Standard_RS_FEC_PLR - (544,514)"
    OPERATIONAL_INFO_FEC_RS_FEC_544_514_PLR = 12,                      // "RS-FEC - (544,514) + PLR"
    OPERATIONAL_INFO_FEC_LL_FEC_271_257_PLR = 13,                      // "LL-FEC - (271,257) + PLR"
    OPERATIONAL_INFO_FEC_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_272_258 =
      14, // "Ethernet_Consortium_LL_50G_RS_FEC_PLR -(272,257+1)"
    OPERATIONAL_INFO_FEC_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_272_258 =
      15, // "Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1)"
} OperationalInfoFec;

/**
 * @brief Link loopback mode.
 */
typedef enum operationalInfoLoopbackMode_t
{
    OPERATIONAL_INFO_LOOPBACK_MODE_NO = 0,
    OPERATIONAL_INFO_LOOPBACK_MODE_PHY_REMOTE = 1,
    OPERATIONAL_INFO_LOOPBACK_MODE_PHY_LOCAL = 2,
    OPERATIONAL_INFO_LOOPBACK_MODE_EXTERNAL = 3,
    OPERATIONAL_INFO_LOOPBACK_MODE_LINK_LAYER = 4,
    OPERATIONAL_INFO_LOOPBACK_MODE_NEAR_END_ANALOG = 5,
    OPERATIONAL_INFO_LOOPBACK_MODE_NEAR_END_DIGITAL = 6,
} OperationalInfoLoopbackMode;

/**
 * @brief Auto-negotiation mode for operational link information.
 */
typedef enum operationalInfoAutoNegotiation_t
{
    OPERATIONAL_INFO_AUTO_NEGOTIATION_ENABLE = 0,
    OPERATIONAL_INFO_AUTO_NEGOTIATION_FORCE = 1,
} OperationalInfoAutoNegotiation;

/**
 * @brief Cable technology reported by module information.
 */
typedef enum ModuleInfoCableTechnology_t
{
    MODULE_INFO_CABLE_TECHNOLOGY_850NM_VCSEL = 0,
    MODULE_INFO_CABLE_TECHNOLOGY_1310NM_VCSEL,
    MODULE_INFO_CABLE_TECHNOLOGY_1550NM_VCSEL,
    MODULE_INFO_CABLE_TECHNOLOGY_1310NM_FP,
    MODULE_INFO_CABLE_TECHNOLOGY_1310NM_DFB,
    MODULE_INFO_CABLE_TECHNOLOGY_1550NM_DFB,
    MODULE_INFO_CABLE_TECHNOLOGY_1310NM_EML,
    MODULE_INFO_CABLE_TECHNOLOGY_1550NM_EML,
    MODULE_INFO_CABLE_TECHNOLOGY_OTHERS,
    MODULE_INFO_CABLE_TECHNOLOGY_1490NM_DFB,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_UNEQ,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_PASV,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_NEAR_FAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_FAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_NEAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_LINEAR,
    MODULE_INFO_CABLE_TECHNOLOGY_LASER_C_BAND,
    MODULE_INFO_CABLE_TECHNOLOGY_LASER_L_BAND,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_LINEAR_NEAR_FAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_LINEAR_FAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_COP_LINEAR_NEAR_END,
    MODULE_INFO_CABLE_TECHNOLOGY_NA = 21,
    MODULE_INFO_CABLE_TECHNOLOGY_PASSIVE,
    MODULE_INFO_CABLE_TECHNOLOGY_ACTIVE,
} ModuleInfoCableTechnology;

/**
 * @brief Module identifier form factor.
 */
typedef enum ModuleInfoIdentifier_t
{
    MODULE_INFO_IDENTIFIER_NA = 0,
    MODULE_INFO_IDENTIFIER_QSFP28,
    MODULE_INFO_IDENTIFIER_QSFP_PLUS,
    MODULE_INFO_IDENTIFIER_SFP28_SFP_PLUS,
    MODULE_INFO_IDENTIFIER_QSA,
    MODULE_INFO_IDENTIFIER_BACKPLANE,
    MODULE_INFO_IDENTIFIER_SFP_DD,
    MODULE_INFO_IDENTIFIER_QSFP_DD,
    MODULE_INFO_IDENTIFIER_QSFP_CMIS,
    MODULE_INFO_IDENTIFIER_OSFP,
    MODULE_INFO_IDENTIFIER_C2C,
    MODULE_INFO_IDENTIFIER_DSFP,
    MODULE_INFO_IDENTIFIER_QSFP_SPLIT_CABLE,
    MODULE_INFO_IDENTIFIER_CPO,
    MODULE_INFO_IDENTIFIER_OE,
    MODULE_INFO_IDENTIFIER_ELS,
} ModuleInfoIdentifier;

/**
 * @brief Cable or module type reported by module information.
 */
typedef enum ModuleInfoCableType_t
{
    MODULE_INFO_CABLE_TYPE_NA = 0,
    MODULE_INFO_CABLE_TYPE_UNIDENTIFIED,
    MODULE_INFO_CABLE_TYPE_ACTIVE,
    MODULE_INFO_CABLE_TYPE_OPTICAL_MODULE,
    MODULE_INFO_CABLE_TYPE_PASSIVE,
    MODULE_INFO_CABLE_TYPE_UNPLUGGED,
    MODULE_INFO_CABLE_TYPE_TWISTED_PAIR,
    MODULE_INFO_CABLE_TYPE_CPO,
    MODULE_INFO_CABLE_TYPE_OE,
    MODULE_INFO_CABLE_TYPE_ELS,
} ModuleInfoCableType;

/**
 * @brief Vendor OUI classification reported by module information.
 */
typedef enum ModuleInfoOui_t
{
    MODULE_INFO_OUI_NA = 0,
    MODULE_INFO_OUI_OTHER,
    MODULE_INFO_OUI_MELLANOX,
    MODULE_INFO_OUI_KNOWN_OUI,
    MODULE_INFO_OUI_NVIDIA,
} ModuleInfoOui;

/**
 * @brief Module state reported by CMIS module information.
 */
typedef enum ModuleInfoModuleState_t
{
    MODULE_INFO_MODULE_STATE_NA = 0,
    MODULE_INFO_MODULE_STATE_LOWPWR,
    MODULE_INFO_MODULE_STATE_PWRUP,
    MODULE_INFO_MODULE_STATE_READY,
    MODULE_INFO_MODULE_STATE_PWRDN,
    MODULE_INFO_MODULE_STATE_FAULT,
} ModuleInfoModuleState;

/**
 * @brief Receive optical power reporting type.
 */
typedef enum ModuleInfoRxPowerType_t
{
    MODULE_INFO_RX_POWER_TYPE_NA = 0,
    MODULE_INFO_RX_POWER_TYPE_OMA,
    MODULE_INFO_RX_POWER_TYPE_AVERAGE_POWER,
} ModuleInfoRxPowerType;

/**
 * @brief Module configuration status or error code response.
 */
typedef enum ModuleInfoErrorCodeResponse_t
{
    MODULE_INFO_ERROR_CODE_RESPONSE_NA = 0,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_UNDEFINED,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_SUCCESS,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_INVALID_APP_SEL,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_INVALID_DATA_PATH,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_INVALID_SI,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_LANES_IN_USE,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_PARTIAL_DATA_PATH,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_IN_PROGRESS,
    MODULE_INFO_ERROR_CODE_RESPONSE_CONFIG_REJECTED_INVALID_VS_SI,
} ModuleInfoErrorCodeResponse;

/**
 * @brief Operational information reported for a device port.
 */
typedef struct MstTelemetryOperationalInfo_t
{
    mstQueryHeader header;                          /**< Query response header. */
    OperationalInfoState state;                     /**< Logical operational state. */
    OperationalInfoPhysicalState physicalState;     /**< Physical link state. */
    OperationalInfoSpeed speed;                     /**< Link speed. */
    uint8_t width;                                  /**< Link width. */
    OperationalInfoFec fec;                         /**< Forward error correction mode. */
    OperationalInfoLoopbackMode loopbackMode;       /**< Loopback mode. */
    OperationalInfoAutoNegotiation autoNegotiation; /**< Auto-negotiation mode. */
} MstTelemetryOperationalInfo;

/**
 * @brief Single FEC histogram bin.
 */
typedef struct MstFecHistogramBin_t
{
    uint32_t minRange;    /**< Inclusive lower error-count range for the bin. */
    uint32_t maxRange;    /**< Inclusive upper error-count range for the bin. */
    uint64_t numOfErrors; /**< Number of errors observed in the bin range. */
} MstFecHistogramBin;

/**
 * @brief FEC error histogram telemetry.
 */
typedef struct MstFecHistogram_t
{
    mstQueryHeader header;                    /**< Query response header. */
    uint8_t numberOfBins;                     /**< Number of valid entries in bins. */
    MstFecHistogramBin bins[MAX_NUM_OF_BINS]; /**< FEC histogram bins. */
} MstFecHistogram;

/**
 * @brief Error count for a single link lane.
 */
typedef struct MstErrorsPerLane_t
{
    uint32_t errorsPerLane; /**< Number of errors reported for the lane. */
} MstErrorsPerLane;

/**
 * @brief Link counter telemetry.
 */
typedef struct MstCountersInfo_t
{
    mstQueryHeader header;                                       /**< Query response header. */
    double timeSinceLastClear;                                   /**< Time since counters were last cleared. */
    uint32_t symbolErrors;                                       /**< Symbol error count. */
    ScientificNotation symbolBER;                                /**< Symbol bit error rate. */
    uint32_t effectivePhysicalErrors;                            /**< Effective physical error count. */
    ScientificNotation effectivePhysicalBER;                     /**< Effective physical bit error rate. */
    uint32_t numberOfLanes;                                      /**< Number of valid lane entries. */
    MstErrorsPerLane rawPhysicalErrorsPerLane[MAX_NUM_OF_LANES]; /**< Raw physical errors per lane. */
    ScientificNotation rawPhysicalBERPerLane[MAX_NUM_OF_LANES];  /**< Raw physical BER per lane. */
    ScientificNotation rawPhysicalBER;                           /**< Aggregate raw physical BER. */
    uint32_t linkDownCounter;                                    /**< Link down counter. */
    uint32_t linkErrorRecoveryCounter;                           /**< Link error recovery counter. */
} MstCountersInfo;

/**
 * @brief Digital diagnostic monitoring alarm and warning flags.
 */
typedef struct MstCableDDMAlarmFlags_t
{
    uint8_t highAlarm;   /**< High alarm flag. */
    uint8_t lowAlarm;    /**< Low alarm flag. */
    uint8_t highWarning; /**< High warning flag. */
    uint8_t lowWarning;  /**< Low warning flag. */
} MstCableDDMAlarmFlags;

/**
 * @brief Digital diagnostic monitoring threshold values.
 */
typedef struct MstCableDDMThresholds_t
{
    float highWarning; /**< High warning threshold. */
    float lowWarning;  /**< Low warning threshold. */
    float highAlarm;   /**< High alarm threshold. */
    float lowAlarm;    /**< Low alarm threshold. */
} MstCableDDMThresholds;

/**
 * @brief Cable temperature DDM telemetry.
 */
typedef struct MstCableDDMTemperatureInfo_t
{
    int16_t value;                    /**< Temperature value. */
    MstCableDDMThresholds thresholds; /**< Temperature thresholds. */
    MstCableDDMAlarmFlags alarmFlags; /**< Temperature alarm and warning flags. */
} MstCableDDMTemperatureInfo;

/**
 * @brief Cable voltage DDM telemetry.
 */
typedef struct MstCableDDMVoltageInfo_t
{
    double value;                     /**< Voltage value. */
    MstCableDDMThresholds thresholds; /**< Voltage thresholds. */
    MstCableDDMAlarmFlags alarmFlags; /**< Voltage alarm and warning flags. */
} MstCableDDMVoltageInfo;

/**
 * @brief Per-channel cable power or bias DDM telemetry.
 */
typedef struct MstCableDDMPowerInfo_t
{
    float value[MAX_NUM_OF_CHANNELS];                      /**< Per-channel values. */
    MstCableDDMThresholds thresholds;                      /**< Shared thresholds for the values. */
    MstCableDDMAlarmFlags alarmFlags[MAX_NUM_OF_CHANNELS]; /**< Per-channel alarm and warning flags. */
} MstCableDDMPowerInfo;

/**
 * @brief Cable digital diagnostic monitoring telemetry.
 */
typedef struct MstCableDDMInfo_t
{
    mstQueryHeader header;                  /**< Query response header. */
    MstCableDDMTemperatureInfo temperature; /**< Temperature telemetry. */
    MstCableDDMVoltageInfo voltage;         /**< Voltage telemetry. */
    MstCableDDMPowerInfo rxPower;           /**< RX power telemetry. */
    MstCableDDMPowerInfo txPower;           /**< TX power telemetry. */
    MstCableDDMPowerInfo txBias;            /**< TX bias telemetry. */
    uint32_t numberOfChannels;              /**< Number of valid channel entries. */
} MstCableDDMInfo;

/**
 * @brief Vendor and identification information for a cable module.
 */
typedef struct MstModuleInfoVendor_t
{
    ModuleInfoIdentifier identifier;                 /**< Module identifier form factor. */
    char compliance[MODULE_INFO_MAX_LENGTH];         /**< Module compliance string. */
    ModuleInfoCableTechnology cableTechnology;       /**< Cable technology. */
    ModuleInfoCableType cableType;                   /**< Cable or module type. */
    ModuleInfoOui oui;                               /**< Vendor OUI classification. */
    char vendorName[MODULE_INFO_MAX_LENGTH];         /**< Vendor name. */
    char vendorPartNumber[MODULE_INFO_MAX_LENGTH];   /**< Vendor part number. */
    char vendorSerialNumber[MODULE_INFO_MAX_LENGTH]; /**< Vendor serial number. */
    char vendorRevision[MODULE_INFO_MAX_LENGTH];     /**< Vendor revision. */
    uint32_t wavelength;                             /**< Wavelength. */
    float transferDistance;                          /**< Transfer distance. */
} MstModuleInfoVendor;

/**
 * @brief Cable attenuation values by signaling rate.
 */
typedef struct MstAttenuation_t
{
    uint8_t attenuation5g;  /**< Attenuation at 5G. */
    uint8_t attenuation7g;  /**< Attenuation at 7G. */
    uint8_t attenuation12g; /**< Attenuation at 12G. */
    uint8_t attenuation25g; /**< Attenuation at 25G. */
    uint8_t attenuation53g; /**< Attenuation at 53G. */
} MstAttenuation;

/**
 * @brief Module power class and clock-data-recovery information.
 */
typedef struct MstPowerAndCdrInfo_t
{
    bool digitalDiagnosticMonitoring;        /**< Indicates whether DDM is supported. */
    char powerClass[MODULE_INFO_MAX_LENGTH]; /**< Module power class string. */
    char maxPower[MODULE_INFO_MAX_LENGTH];   /**< Maximum power string. */
    uint8_t cdrRx[MAX_NUM_OF_LANES];         /**< RX CDR status per lane. */
    uint8_t cdrTx[MAX_NUM_OF_LANES];         /**< TX CDR status per lane. */
} MstPowerAndCdrInfo;

/**
 * @brief Module latency information.
 */
typedef struct MstLatencyInfo_t
{
    uint16_t intraAsicLatency;      /**< Intra-ASIC latency. */
    uint16_t moduleDatapathLatency; /**< Module datapath latency. */
    float roundTripLatency;         /**< Round-trip latency. */
} MstLatencyInfo;

/**
 * @brief Signal-to-noise ratio information per module lane.
 */
typedef struct MstSnrInfo_t
{
    float snrMediaLanes[MAX_NUM_OF_LANES]; /**< SNR values for media lanes. */
    float snrHostLanes[MAX_NUM_OF_LANES];  /**< SNR values for host lanes. */
} MstSnrInfo;

/**
 * @brief BER-related module information.
 */
typedef struct MstBerModuleInfo_t
{
    MstSnrInfo snrInfo;                                        /**< SNR information. */
    char ibCableWidth[MODULE_INFO_MAX_LENGTH];                 /**< InfiniBand cable width string. */
    uint8_t memoryMapRevision;                                 /**< Module memory map revision. */
    uint8_t linearDirectDrive;                                 /**< Linear direct-drive capability or status. */
    char cableBreakout[MODULE_INFO_MAX_LENGTH];                /**< Cable breakout string. */
    uint32_t smfLength;                                        /**< Single-mode fiber length. */
    uint8_t cableRxAmp;                                        /**< Cable RX amplitude. */
    uint8_t cableRxEmphasis;                                   /**< Cable RX emphasis. */
    uint8_t cableRxPostEmphasis;                               /**< Cable RX post-emphasis. */
    uint8_t cableTxEqualization;                               /**< Cable TX equalization. */
    float wavelengthTolerance;                                 /**< Wavelength tolerance. */
    ModuleInfoModuleState moduleState;                         /**< Module state. */
    uint8_t dataPathStatePerLane[MAX_NUM_OF_LANES];            /**< Data path state per lane. */
    uint8_t rxOutputValidPerLane[MAX_NUM_OF_LANES];            /**< RX output-valid indication per lane. */
    float nominalBitRate;                                      /**< Nominal bit rate. */
    ModuleInfoRxPowerType rxPowerType;                         /**< RX power reporting type. */
    MstDate manufacturingDate;                                 /**< Module manufacturing date. */
    char activeSetHostComplianceCode[MODULE_INFO_MAX_LENGTH];  /**< Active set host compliance code. */
    char activeSetMediaComplianceCode[MODULE_INFO_MAX_LENGTH]; /**< Active set media compliance code. */
    ModuleInfoErrorCodeResponse errorCodeResponse;             /**< Configuration status or error code response. */
    uint8_t moduleFwFault;                                     /**< Module firmware fault indication. */
    uint8_t dataPathFwFault;                                   /**< Data path firmware fault indication. */
    uint8_t txFaultPerLane[MAX_NUM_OF_LANES];                  /**< TX fault indication per lane. */
    uint8_t txLosPerLane[MAX_NUM_OF_LANES];                    /**< TX loss-of-signal indication per lane. */
    uint8_t txCdrLolPerLane[MAX_NUM_OF_LANES];                 /**< TX CDR loss-of-lock indication per lane. */
    uint8_t rxLosPerLane[MAX_NUM_OF_LANES];                    /**< RX loss-of-signal indication per lane. */
    uint8_t rxCdrLolPerLane[MAX_NUM_OF_LANES];                 /**< RX CDR loss-of-lock indication per lane. */
    uint8_t txAdaptiveEqFaultPerLane[MAX_NUM_OF_LANES];        /**< TX adaptive EQ fault indication per lane. */
} MstBerModuleInfo;

/**
 * @brief Complete module information telemetry response.
 */
typedef struct MstModuleInfo_t
{
    mstQueryHeader header;              /**< Query response header. */
    MstModuleInfoVendor vendorInfo;     /**< Vendor and identification information. */
    MstAttenuation attenuationInfo;     /**< Attenuation information. */
    MstFwVersion fwVersion;             /**< Module firmware version. */
    MstPowerAndCdrInfo powerAndCdrInfo; /**< Power and CDR information. */
    MstLatencyInfo latencyInfo;         /**< Latency information. */
    MstBerModuleInfo berModuleInfo;     /**< BER-related module information. */
} MstModuleInfo;