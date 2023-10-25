# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# --


#######################################################
#
# constants.py
# Python implementation of resource dump constants
# This file will supply all the constants needed
# for the resource parse tool
# Original author: talve
#
#######################################################

TOOL_NAME = "ResourceParse"

RESOURCE_DUMP_SEGMENT_TYPE_INFO = 0xfffe
RESOURCE_DUMP_SEGMENT_TYPE_MENU = 0xffff
RESOURCE_DUMP_SEGMENT_TYPE_REFERENCE = 0xfffd

# segment start/end specify where the 'type' attr starts and ends in the raw_data of each segment.
# should be 0-16 bits
SEGMENT_SIZE_DWORD_LOCATION = 0
SEGMENT_AGGREGATE_DWORD_LOCATION = 1
SEGMENT_AGGREGATE_BIT = 31

RAW_DATA_FILE_TYPE_BIN = 0
RAW_DATA_FILE_TYPE_HUMAN_READABLE = 1
RAW_DATA_FILE_TYPE_JSON = 2
DWORD_SIZE = 4

RESOURCE_SEGMENT_START_OFFSET_IN_DW = 4
RESOURCE_SEGMENT_START_OFFSET_IN_BYTES = 4 * RESOURCE_SEGMENT_START_OFFSET_IN_DW
PARSER_NUM_OF_DW_IN_ROW = 4
PARSER_STRING_NOT_FOUND = -1

DATA_PRINTER_SEPARATOR = 80 * "-"

WARNING_SIZE_DOESNT_MATCH = " Segment size({0} DWs) doesn't match the adb segment size({1} DWs)"
WARNING_FAILED_EVAL_CONDITION = ' Failed evaluating condition: {}, at field - "{}", exporting field by default'
WARNING_WRONG_PAIR_SIZE = " Segment size for Address-Value parsing is odd"

PARENT_PREFIX_LIST = ["#(parent)", "$(parent)"]
SEGMENT_PREFIX = "$(segment)"
