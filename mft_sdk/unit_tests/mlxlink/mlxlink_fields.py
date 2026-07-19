# SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#  Version: $Id$
#

"""
Python mirror of mlxlink/modules/mlxlink_fields.h

Keep in sync with the C++ header to avoid string drift between
C/C++ tests and Python test runners.
"""

# Operational Info field names
FIELD_OPERATIONAL_INFO = "Operational Info"
FIELD_STATE = "State"
FIELD_PHYSICAL_STATE = "Physical state"
FIELD_SPEED = "Speed"
FIELD_WIDTH = "Width"
FIELD_FEC = "FEC"
FIELD_LOOPBACK_MODE = "Loopback Mode"
FIELD_AUTO_NEGOTIATION = "Auto Negotiation"
FIELD_PRIMARY_SECONDARY = "Primary/Secondary"
FIELD_TX_PRECODING_STATUS = "Tx Precoding Status"
FIELD_RX_PRECODING_STATUS = "Rx Precoding Status"

# Port Info field names
FIELD_LABEL_PORT = "Label Port"
FIELD_LOCAL_PORT = "Local Port"

# Host Class Info field names
FIELD_LOCAL_HOST_CLASS = "Local Host Class"
FIELD_REMOTE_HOST_CLASS = "Remote Host Class"

# Counters Info field names
FIELD_PHYSICAL_COUNTERS_AND_BER_INFO = "Physical Counters and BER Info"
FIELD_TIME_SINCE_LAST_CLEAR = "Time Since Last Clear [Min]"
FIELD_SYMBOL_ERRORS = "Symbol Errors"
FIELD_SYMBOL_BER = "Symbol BER"
FIELD_EFFECTIVE_PHYSICAL_ERRORS = "Effective Physical Errors"
FIELD_EFFECTIVE_PHYSICAL_BER = "Effective Physical BER"
FIELD_RAW_PHYSICAL_ERRORS_PER_LANE = "Raw Physical Errors Per Lane"
FIELD_RAW_PHYSICAL_BER = "Raw Physical BER"
FIELD_RAW_PHYSICAL_BER_PER_LANE = "Raw Physical BER Per Lane"
FIELD_LINK_DOWN_COUNTER = "Link Down Counter"
FIELD_LINK_ERROR_RECOVERY_COUNTER = "Link Error Recovery Counter"

# CPO Info field names
FIELD_ELS_INDEX = "ELS Index"
FIELD_ELS_LANE_INDEX = "ELS Lane Index"
FIELD_OE_INDEX = "OE Index"
FIELD_OE_LANE_INDEX = "OE Lane Index"

# Supported Info field names
FIELD_ENABLED_LINK_SPEED = "Enabled Link Speed"
FIELD_SUPPORTED_CABLE_SPEED = "Supported Cable Speed"

# Troubleshooting Info field names
FIELD_STATUS_OPCODE = "Status Opcode"
FIELD_GROUP_OPCODE = "Group Opcode"
FIELD_RECOMMENDATION = "Recommendation"
FIELD_TIME_TO_LINK_UP = "Time to Link Up"

# Tool Information field names
FIELD_FIRMWARE_VERSION = "Firmware Version"
FIELD_MFT_VERSION = "MFT Version"

# DDM Section titles
DDM_SECTION_CABLE_DDM_INFO = "Cable DDM Information"
DDM_SECTION_DDM_FLAGS = "DDM Flags"
DDM_SECTION_DDM_THRESHOLDS = "DDM Thresholds"

# DDM Field names - Cable DDM Information section
DDM_FIELD_TEMPERATURE = "Temperature"
DDM_FIELD_VOLTAGE = "Voltage"
DDM_FIELD_CHANNELS = "Channels"
DDM_FIELD_RX_POWER = "RX Power"
DDM_FIELD_TX_POWER = "TX Power"
DDM_FIELD_TX_BIAS = "TX Bias"

# DDM Flag field suffixes
DDM_FLAG_ALARM_HIGH = " Alarm high"
DDM_FLAG_ALARM_LOW = " Alarm low"
DDM_FLAG_WARNING_HIGH = " Warning high"
DDM_FLAG_WARNING_LOW = " Warning low"

# DDM Flags - Module level (Temperature and Voltage)
DDM_FIELD_TEMPERATURE_ALARM_HIGH = "Temperature Alarm high"
DDM_FIELD_TEMPERATURE_ALARM_LOW = "Temperature Alarm low"
DDM_FIELD_TEMPERATURE_WARNING_HIGH = "Temperature Warning high"
DDM_FIELD_TEMPERATURE_WARNING_LOW = "Temperature Warning low"
DDM_FIELD_VOLTAGE_ALARM_HIGH = "Voltage Alarm high"
DDM_FIELD_VOLTAGE_ALARM_LOW = "Voltage Alarm low"
DDM_FIELD_VOLTAGE_WARNING_HIGH = "Voltage Warning high"
DDM_FIELD_VOLTAGE_WARNING_LOW = "Voltage Warning low"

# DDM Flags - Channel level (RX Power, TX Power, TX Bias)
DDM_FIELD_RX_POWER_ALARM_HIGH = "RX Power Alarm high"
DDM_FIELD_RX_POWER_ALARM_LOW = "RX Power Alarm low"
DDM_FIELD_RX_POWER_WARNING_HIGH = "RX Power Warning high"
DDM_FIELD_RX_POWER_WARNING_LOW = "RX Power Warning low"
DDM_FIELD_TX_POWER_ALARM_HIGH = "TX Power Alarm high"
DDM_FIELD_TX_POWER_ALARM_LOW = "TX Power Alarm low"
DDM_FIELD_TX_POWER_WARNING_HIGH = "TX Power Warning high"
DDM_FIELD_TX_POWER_WARNING_LOW = "TX Power Warning low"
DDM_FIELD_TX_BIAS_ALARM_HIGH = "TX Bias Alarm high"
DDM_FIELD_TX_BIAS_ALARM_LOW = "TX Bias Alarm low"
DDM_FIELD_TX_BIAS_WARNING_HIGH = "TX Bias Warning high"
DDM_FIELD_TX_BIAS_WARNING_LOW = "TX Bias Warning low"

# DDM Thresholds section field names
DDM_FIELD_THRESHOLDS = "Thresholds"
DDM_FIELD_HIGH_ALARM_THRESHOLD = "High alarm threshold"
DDM_FIELD_LOW_ALARM_THRESHOLD = "Low alarm threshold"
DDM_FIELD_HIGH_WARNING_THRESHOLD = "High warning threshold"
DDM_FIELD_LOW_WARNING_THRESHOLD = "Low warning threshold"

# Module Info field names
FIELD_MODULE_INFO = "Module Info"
FIELD_IDENTIFIER = "Identifier"
FIELD_COMPLIANCE = "Compliance"
FIELD_CABLE_TECHNOLOGY = "Cable Technology"
FIELD_CABLE_TYPE = "Cable Type"
FIELD_OUI = "OUI"
FIELD_VENDOR_NAME = "Vendor Name"
FIELD_VENDOR_PART_NUMBER = "Vendor Part Number"
FIELD_VENDOR_SERIAL_NUMBER = "Vendor Serial Number"
FIELD_VENDOR_REVISION = "Rev"
FIELD_WAVELENGTH = "Wavelength [nm]"
FIELD_TRANSFER_DISTANCE = "Transfer Distance [m]"
FIELD_ATTENUATION = "Attenuation"
FIELD_FW_VERSION = "FW Version"
FIELD_DIGITAL_DIAGNOSTIC_MONITORING = "Digital Diagnostic Monitoring"
FIELD_POWER_CLASS = "Power Class"
FIELD_MAX_POWER = "MAX Power"
FIELD_CDR_RX = "CDR RX"
FIELD_CDR_TX = "CDR TX"
FIELD_LOS_ALARM = "LOS Alarm"
FIELD_INTRA_ASIC_LATENCY = "Intra-ASIC Latency [ns]"
FIELD_MODULE_DATAPATH_LATENCY = "Module Datapath Latency [ns]"
FIELD_ROUND_TRIP_LATENCY = "Round Trip Latency [ns]"
FIELD_SNR_MEDIA_LANES = "SNR Media Lanes [dB]"
FIELD_SNR_HOST_LANES = "SNR Host Lanes [dB]"
FIELD_IB_CABLE_WIDTH = "IB Cable Width"
FIELD_MEMORY_MAP_REVISION = "Memory Map Revision"
FIELD_LINEAR_DIRECT_DRIVE = "Linear Direct Drive"
FIELD_CABLE_BREAKOUT = "Cable Breakout"
FIELD_SMF_LENGTH = "SMF Length"
FIELD_CABLE_RX_AMP = "Cable Rx AMP"
FIELD_CABLE_RX_EMPHASIS_PRE = "Cable Rx Emphasis (Pre)"
FIELD_CABLE_RX_POST_EMPHASIS = "Cable Rx Post Emphasis"
FIELD_CABLE_TX_EQUALIZATION = "Cable Tx Equalization"
FIELD_WAVELENGTH_TOLERANCE = "Wavelength Tolerance"
FIELD_MODULE_STATE = "Module State"
FIELD_DATA_PATH_STATE_PER_LANE = "DataPath state [per lane]"
FIELD_RX_OUTPUT_VALID_PER_LANE = "Rx Output Valid [per lane]"
FIELD_NOMINAL_BIT_RATE = "Nominal bit rate"
FIELD_RX_POWER_TYPE = "Rx Power Type"
FIELD_MANUFACTURING_DATE = "Manufacturing Date"
FIELD_ACTIVE_SET_HOST_COMPLIANCE_CODE = "Active Set Host Compliance Code"
FIELD_ACTIVE_SET_MEDIA_COMPLIANCE_CODE = "Active Set Media Compliance Code"
FIELD_ERROR_CODE_RESPONSE = "Error Code Response"
FIELD_MODULE_FW_FAULT = "Module FW Fault"
FIELD_DATA_PATH_FW_FAULT = "DataPath FW Fault"
FIELD_TX_FAULT_PER_LANE = "Tx Fault [per lane]"
FIELD_TX_LOS_PER_LANE = "Tx LOS [per lane]"
FIELD_TX_CDR_LOL_PER_LANE = "Tx CDR LOL [per lane]"
FIELD_RX_LOS_PER_LANE = "Rx LOS [per lane]"
FIELD_RX_CDR_LOL_PER_LANE = "Rx CDR LOL [per lane]"
FIELD_TX_ADAPTIVE_EQ_FAULT_PER_LANE = "Tx Adaptive EQ Fault [per lane]"

# FEC Histogram field names
FIELD_HISTOGRAM_OF_FEC_ERRORS = "Histogram of FEC Errors"

# Common field values
NA_FIELD_VALUE = "N/A"
