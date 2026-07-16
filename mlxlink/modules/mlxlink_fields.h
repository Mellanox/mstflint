/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#ifndef MLXLINK_FIELDS_H
#define MLXLINK_FIELDS_H

/*
 * Field display names for telemetry output.
 * Using static const for C/C++ compatibility.
 */

// Operational Info field names
static const char* const FIELD_OPERATIONAL_INFO = "Operational Info";
static const char* const FIELD_STATE = "State";
static const char* const FIELD_PHYSICAL_STATE = "Physical state";
static const char* const FIELD_SPEED = "Speed";
static const char* const FIELD_WIDTH = "Width";
static const char* const FIELD_FEC = "FEC";
static const char* const FIELD_LOOPBACK_MODE = "Loopback Mode";
static const char* const FIELD_AUTO_NEGOTIATION = "Auto Negotiation";
static const char* const FIELD_PRIMARY_SECONDARY = "Primary/Secondary";
static const char* const FIELD_TX_PRECODING_STATUS = "Tx Precoding Status";
static const char* const FIELD_RX_PRECODING_STATUS = "Rx Precoding Status";

// Port Info field names
static const char* const FIELD_LABEL_PORT = "Label Port";
static const char* const FIELD_LOCAL_PORT = "Local Port";

// Host Class Info field names
static const char* const FIELD_LOCAL_HOST_CLASS = "Local Host Class";
static const char* const FIELD_REMOTE_HOST_CLASS = "Remote Host Class";

// Counters Info field names
static const char* const FIELD_PHYSICAL_COUNTERS_AND_BER_INFO = "Physical Counters and BER Info";
static const char* const FIELD_TIME_SINCE_LAST_CLEAR = "Time Since Last Clear [Min]";
static const char* const FIELD_SYMBOL_ERRORS = "Symbol Errors";
static const char* const FIELD_SYMBOL_BER = "Symbol BER";
static const char* const FIELD_EFFECTIVE_PHYSICAL_ERRORS = "Effective Physical Errors";
static const char* const FIELD_EFFECTIVE_PHYSICAL_BER = "Effective Physical BER";
static const char* const FIELD_RAW_PHYSICAL_ERRORS_PER_LANE = "Raw Physical Errors Per Lane";
static const char* const FIELD_RAW_PHYSICAL_BER = "Raw Physical BER";
static const char* const FIELD_RAW_PHYSICAL_BER_PER_LANE = "Raw Physical BER Per Lane";
static const char* const FIELD_LINK_DOWN_COUNTER = "Link Down Counter";
static const char* const FIELD_LINK_ERROR_RECOVERY_COUNTER = "Link Error Recovery Counter";

// CPO Info field names
static const char* const FIELD_ELS_INDEX = "ELS Index";
static const char* const FIELD_ELS_LANE_INDEX = "ELS Lane Index";
static const char* const FIELD_OE_INDEX = "OE Index";
static const char* const FIELD_OE_LANE_INDEX = "OE Lane Index";

// Supported Info field names
static const char* const FIELD_ENABLED_LINK_SPEED = "Enabled Link Speed";
static const char* const FIELD_SUPPORTED_CABLE_SPEED = "Supported Cable Speed";

// Troubleshooting Info field names
static const char* const FIELD_STATUS_OPCODE = "Status Opcode";
static const char* const FIELD_GROUP_OPCODE = "Group Opcode";
static const char* const FIELD_RECOMMENDATION = "Recommendation";
static const char* const FIELD_TIME_TO_LINK_UP = "Time to Link Up";

// Tool Information field names
static const char* const FIELD_FIRMWARE_VERSION = "Firmware Version";
static const char* const FIELD_MFT_VERSION = "MFT Version";
static const char* const FIELD_BKV_VERSION = "BKV Version";

/*
 * Field display names for Cable DDM (Digital Diagnostic Monitoring) output.
 * Using static const for C/C++ compatibility.
 */

// DDM Section titles
static const char* const DDM_SECTION_CABLE_DDM_INFO = "Cable DDM Information";
static const char* const DDM_SECTION_DDM_FLAGS = "DDM Flags";
static const char* const DDM_SECTION_DDM_THRESHOLDS = "DDM Thresholds";

// DDM Field names - Cable DDM Information section
static const char* const DDM_FIELD_TEMPERATURE = "Temperature";
static const char* const DDM_FIELD_VOLTAGE = "Voltage";
static const char* const DDM_FIELD_CHANNELS = "Channels";
static const char* const DDM_FIELD_RX_POWER = "RX Power";
static const char* const DDM_FIELD_TX_POWER = "TX Power";
static const char* const DDM_FIELD_TX_BIAS = "TX Bias";

// DDM Flag field suffixes (to be appended to field names)
static const char* const DDM_FLAG_ALARM_HIGH = " Alarm high";
static const char* const DDM_FLAG_ALARM_LOW = " Alarm low";
static const char* const DDM_FLAG_WARNING_HIGH = " Warning high";
static const char* const DDM_FLAG_WARNING_LOW = " Warning low";

// DDM Flags section - Module level flags (Temperature and Voltage)
static const char* const DDM_FIELD_TEMPERATURE_ALARM_HIGH = "Temperature Alarm high";
static const char* const DDM_FIELD_TEMPERATURE_ALARM_LOW = "Temperature Alarm low";
static const char* const DDM_FIELD_TEMPERATURE_WARNING_HIGH = "Temperature Warning high";
static const char* const DDM_FIELD_TEMPERATURE_WARNING_LOW = "Temperature Warning low";
static const char* const DDM_FIELD_VOLTAGE_ALARM_HIGH = "Voltage Alarm high";
static const char* const DDM_FIELD_VOLTAGE_ALARM_LOW = "Voltage Alarm low";
static const char* const DDM_FIELD_VOLTAGE_WARNING_HIGH = "Voltage Warning high";
static const char* const DDM_FIELD_VOLTAGE_WARNING_LOW = "Voltage Warning low";

// DDM Flags section - Channel level flags (RX Power, TX Power, TX Bias)
static const char* const DDM_FIELD_RX_POWER_ALARM_HIGH = "RX Power Alarm high";
static const char* const DDM_FIELD_RX_POWER_ALARM_LOW = "RX Power Alarm low";
static const char* const DDM_FIELD_RX_POWER_WARNING_HIGH = "RX Power Warning high";
static const char* const DDM_FIELD_RX_POWER_WARNING_LOW = "RX Power Warning low";
static const char* const DDM_FIELD_TX_POWER_ALARM_HIGH = "TX Power Alarm high";
static const char* const DDM_FIELD_TX_POWER_ALARM_LOW = "TX Power Alarm low";
static const char* const DDM_FIELD_TX_POWER_WARNING_HIGH = "TX Power Warning high";
static const char* const DDM_FIELD_TX_POWER_WARNING_LOW = "TX Power Warning low";
static const char* const DDM_FIELD_TX_BIAS_ALARM_HIGH = "TX Bias Alarm high";
static const char* const DDM_FIELD_TX_BIAS_ALARM_LOW = "TX Bias Alarm low";
static const char* const DDM_FIELD_TX_BIAS_WARNING_HIGH = "TX Bias Warning high";
static const char* const DDM_FIELD_TX_BIAS_WARNING_LOW = "TX Bias Warning low";

// DDM Thresholds section field names
static const char* const DDM_FIELD_THRESHOLDS = "Thresholds";
static const char* const DDM_FIELD_HIGH_ALARM_THRESHOLD = "High alarm threshold";
static const char* const DDM_FIELD_LOW_ALARM_THRESHOLD = "Low alarm threshold";
static const char* const DDM_FIELD_HIGH_WARNING_THRESHOLD = "High warning threshold";
static const char* const DDM_FIELD_LOW_WARNING_THRESHOLD = "Low warning threshold";

// Module Info field names
static const char* const FIELD_MODULE_INFO = "Module Info";
static const char* const FIELD_IDENTIFIER = "Identifier";
static const char* const FIELD_COMPLIANCE = "Compliance";
static const char* const FIELD_CABLE_TECHNOLOGY = "Cable Technology";
static const char* const FIELD_CABLE_TYPE = "Cable Type";
static const char* const FIELD_OUI = "OUI";
static const char* const FIELD_VENDOR_NAME = "Vendor Name";
static const char* const FIELD_VENDOR_PART_NUMBER = "Vendor Part Number";
static const char* const FIELD_VENDOR_SERIAL_NUMBER = "Vendor Serial Number";
static const char* const FIELD_VENDOR_REVISION = "Rev";
static const char* const FIELD_WAVELENGTH = "Wavelength [nm]";
static const char* const FIELD_TRANSFER_DISTANCE = "Transfer Distance [m]";
static const char* const FIELD_ATTENUATION = "Attenuation";
static const char* const FIELD_FW_VERSION = "FW Version";
static const char* const FIELD_DIGITAL_DIAGNOSTIC_MONITORING = "Digital Diagnostic Monitoring";
static const char* const FIELD_POWER_CLASS = "Power Class";
static const char* const FIELD_MAX_POWER = "MAX Power";
static const char* const FIELD_CDR_RX = "CDR RX";
static const char* const FIELD_CDR_TX = "CDR TX";
static const char* const FIELD_LOS_ALARM = "LOS Alarm";
static const char* const FIELD_INTRA_ASIC_LATENCY = "Intra-ASIC Latency [ns]";
static const char* const FIELD_MODULE_DATAPATH_LATENCY = "Module Datapath Latency [ns]";
static const char* const FIELD_ROUND_TRIP_LATENCY = "Round Trip Latency [ns]";
static const char* const FIELD_SNR_MEDIA_LANES = "SNR Media Lanes [dB]";
static const char* const FIELD_SNR_HOST_LANES = "SNR Host Lanes [dB]";
static const char* const FIELD_IB_CABLE_WIDTH = "IB Cable Width";
static const char* const FIELD_MEMORY_MAP_REVISION = "Memory Map Revision";
static const char* const FIELD_LINEAR_DIRECT_DRIVE = "Linear Direct Drive";
static const char* const FIELD_CABLE_BREAKOUT = "Cable Breakout";
static const char* const FIELD_SMF_LENGTH = "SMF Length";
static const char* const FIELD_CABLE_RX_AMP = "Cable Rx AMP";
static const char* const FIELD_CABLE_RX_EMPHASIS_PRE = "Cable Rx Emphasis (Pre)";
static const char* const FIELD_CABLE_RX_POST_EMPHASIS = "Cable Rx Post Emphasis";
static const char* const FIELD_CABLE_TX_EQUALIZATION = "Cable Tx Equalization";
static const char* const FIELD_WAVELENGTH_TOLERANCE = "Wavelength Tolerance";
static const char* const FIELD_MODULE_STATE = "Module State";
static const char* const FIELD_DATA_PATH_STATE_PER_LANE = "DataPath state [per lane]";
static const char* const FIELD_RX_OUTPUT_VALID_PER_LANE = "Rx Output Valid [per lane]";
static const char* const FIELD_NOMINAL_BIT_RATE = "Nominal bit rate";
static const char* const FIELD_RX_POWER_TYPE = "Rx Power Type";
static const char* const FIELD_MANUFACTURING_DATE = "Manufacturing Date";
static const char* const FIELD_ACTIVE_SET_HOST_COMPLIANCE_CODE = "Active Set Host Compliance Code";
static const char* const FIELD_ACTIVE_SET_MEDIA_COMPLIANCE_CODE = "Active Set Media Compliance Code";
static const char* const FIELD_ERROR_CODE_RESPONSE = "Error Code Response";
static const char* const FIELD_MODULE_FW_FAULT = "Module FW Fault";
static const char* const FIELD_DATA_PATH_FW_FAULT = "DataPath FW Fault";
static const char* const FIELD_TX_FAULT_PER_LANE = "Tx Fault [per lane]";
static const char* const FIELD_TX_LOS_PER_LANE = "Tx LOS [per lane]";
static const char* const FIELD_TX_CDR_LOL_PER_LANE = "Tx CDR LOL [per lane]";
static const char* const FIELD_RX_LOS_PER_LANE = "Rx LOS [per lane]";
static const char* const FIELD_RX_CDR_LOL_PER_LANE = "Rx CDR LOL [per lane]";
static const char* const FIELD_TX_ADAPTIVE_EQ_FAULT_PER_LANE = "Tx Adaptive EQ Fault [per lane]";

// Cable Technology display values
static const char* const CABLE_TECH_850NM_VCSEL = "850 nm VCSEL";
static const char* const CABLE_TECH_1310NM_VCSEL = "1310 nm VCSEL";
static const char* const CABLE_TECH_1550NM_VCSEL = "1550 nm VCSEL";
static const char* const CABLE_TECH_1310NM_FP = "1310 nm FP laser";
static const char* const CABLE_TECH_1310NM_DFB = "1310 nm DFB laser";
static const char* const CABLE_TECH_1550NM_DFB = "1550 nm DFB laser";
static const char* const CABLE_TECH_1310NM_EML = "1310 nm EML";
static const char* const CABLE_TECH_1550NM_EML = "1550 nm EML";
static const char* const CABLE_TECH_OTHERS = "Other / Undefined";
static const char* const CABLE_TECH_1490NM_DFB = "1490 nm DFB laser";
static const char* const CABLE_TECH_COP_UNEQ = "Copper cable, passive, unequalized";
static const char* const CABLE_TECH_COP_PASV = "Copper cable, passive, equalized";
static const char* const CABLE_TECH_COP_NEAR_FAR_END = "Copper cable with near and far end limiting active equalizers";
static const char* const CABLE_TECH_COP_FAR_END = "Copper cable with far end limiting active equalizers";
static const char* const CABLE_TECH_COP_NEAR_END = "Copper cable with near end limiting active equalizers";
static const char* const CABLE_TECH_COP_LINEAR = "Copper cable with linear active equalizers";
static const char* const CABLE_TECH_LASER_C_BAND = "C-band tunable laser";
static const char* const CABLE_TECH_LASER_L_BAND = "B-band tunable laser";
static const char* const CABLE_TECH_COP_LINEAR_NEAR_FAR_END =
  "Copper cable with near end and far end linear active equalizers";
static const char* const CABLE_TECH_COP_LINEAR_FAR_END = "Copper cable with far end linear active equalizers";
static const char* const CABLE_TECH_COP_LINEAR_NEAR_END = "Copper cable with near end linear active equalizers";
static const char* const CABLE_TECH_PASSIVE = "Passive";
static const char* const CABLE_TECH_ACTIVE = "Active";

// Cable Identifier display values
static const char* const IDENTIFIER_STR_QSFP28 = "QSFP28";
static const char* const IDENTIFIER_STR_QSFP_PLUS = "QSFP+";
static const char* const IDENTIFIER_STR_SFP28_SFP_PLUS = "SFP28/SFP+";
static const char* const IDENTIFIER_STR_QSA = "QSA (QSFP->SFP)";
static const char* const IDENTIFIER_STR_BACKPLANE = "Backplane";
static const char* const IDENTIFIER_STR_SFP_DD = "SFP-DD";
static const char* const IDENTIFIER_STR_QSFP_DD = "QSFP-DD";
static const char* const IDENTIFIER_STR_QSFP_CMIS = "QSFP_CMIS";
static const char* const IDENTIFIER_STR_OSFP = "OSFP";
static const char* const IDENTIFIER_STR_C2C = "C2C";
static const char* const IDENTIFIER_STR_DSFP = "DSFP";
static const char* const IDENTIFIER_STR_CPO = "CPO";
static const char* const IDENTIFIER_STR_OE = "OE";
static const char* const IDENTIFIER_STR_ELS = "ELS";

// Cable Type display values
static const char* const CABLE_TYPE_STR_UNIDENTIFIED = "Unidentified";
static const char* const CABLE_TYPE_STR_ACTIVE = "Active cable (active copper / optics)";
static const char* const CABLE_TYPE_STR_OPTICAL_MODULE = "Optical Module (separated)";
static const char* const CABLE_TYPE_STR_PASSIVE = "Passive copper cable";
static const char* const CABLE_TYPE_STR_UNPLUGGED = "Cable unplugged";
static const char* const CABLE_TYPE_STR_TWISTED_PAIR = "Twisted Pair";
static const char* const CABLE_TYPE_STR_CPO = "CPO";
static const char* const CABLE_TYPE_STR_OE = "OE";
static const char* const CABLE_TYPE_STR_ELS = "ELS";

// OUI display values
static const char* const OUI_STR_OTHER = "Other";
static const char* const OUI_STR_MELLANOX = "Mellanox";
static const char* const OUI_STR_KNOWN_OUI = "Known OUI";
static const char* const OUI_STR_NVIDIA = "Nvidia";

// Module State display values
static const char* const MODULE_STATE_STR_LOWPWR = "LowPwr state";
static const char* const MODULE_STATE_STR_PWRUP = "PwrUp state";
static const char* const MODULE_STATE_STR_READY = "Ready state";
static const char* const MODULE_STATE_STR_PWRDN = "PwrDn state";
static const char* const MODULE_STATE_STR_FAULT = "Fault state";

// Rx Power Type display values
static const char* const RX_POWER_TYPE_STR_OMA = "OMA";
static const char* const RX_POWER_TYPE_STR_AVERAGE_POWER = "Average power";

// Cable Compliance QSFP display values (for SDK mapping)
static const char* const CABLE_COMPLIANCE_QSFP_STR_UNSPECIFIED = "Unspecified";
static const char* const CABLE_COMPLIANCE_QSFP_STR_40G_ACTIVE_CABLE_XLPPI = "40G Active Cable (XLPPI)";
static const char* const CABLE_COMPLIANCE_QSFP_STR_40GBASE_LR4 = "40GBASE-LR4";
static const char* const CABLE_COMPLIANCE_QSFP_STR_40GBASE_SR4 = "40GBASE-SR4";
static const char* const CABLE_COMPLIANCE_QSFP_STR_40GBASE_CR4 = "40GBASE-CR4";
static const char* const CABLE_COMPLIANCE_QSFP_STR_10GBASE_SR = "10GBASE-SR";
static const char* const CABLE_COMPLIANCE_QSFP_STR_10GBASE_LR = "10GBASE-LR";
static const char* const CABLE_COMPLIANCE_QSFP_STR_10GBASE_LRM = "10GBASE-LRM";
static const char* const CABLE_COMPLIANCE_QSFP_STR_EXT = "Extended Specification Compliance valid";

// Cable Compliance SFP display values (for SDK mapping)
static const char* const CABLE_COMPLIANCE_SFP_STR_UNSPECIFIED = "Unspecified";
static const char* const CABLE_COMPLIANCE_SFP_STR_10G_BASE_SR = "10G Base-SR";
static const char* const CABLE_COMPLIANCE_SFP_STR_10G_BASE_LR = "10G Base-LR";
static const char* const CABLE_COMPLIANCE_SFP_STR_10G_BASE_LRM = "10G Base-LRM";
static const char* const CABLE_COMPLIANCE_SFP_STR_10G_BASE_ER = "10G Base-ER";

// Error Code Response display values
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_UNDEFINED = "ConfigUndefined";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_SUCCESS = "ConfigSuccess";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED = "ConfigRejected";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_INVALID_APP_SEL = "ConfigRejectedInvalidAppSel";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_INVALID_DATA_PATH = "ConfigRejectedInvalidDataPath";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_INVALID_SI = "ConfigRejectedInvalidSI";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_LANES_IN_USE = "ConfigRejectedLanesInUse";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_PARTIAL_DATA_PATH = "ConfigRejectedPartialDataPath";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_IN_PROGRESS = "ConfigInProgress";
static const char* const ERROR_CODE_RESPONSE_STR_CONFIG_REJECTED_INVALID_VS_SI = "ConfigRejectedInvalidVS_SI";

// Common field values
static const char* const NA_FIELD_VALUE = "N/A";

#endif /* MLXLINK_FIELDS_H */
