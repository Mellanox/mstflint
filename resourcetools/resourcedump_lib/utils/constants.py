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
# for the resource dump tool
# Original author: romany
#
#######################################################

TOOL_NAME = "ResourceDump"
RESOURCE_DUMP_COMMAND_TYPE_QUERY = "query"
RESOURCE_DUMP_COMMAND_TYPE_DUMP = "dump"

RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE = 0xffffffff
RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MIN = 0x0000
RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MAX = 0xfeff
RESOURCE_DUMP_SEGMENT_TYPE_NOTICE = 0xfff9
RESOURCE_DUMP_SEGMENT_TYPE_COMMAND = 0xfffa
RESOURCE_DUMP_SEGMENT_TYPE_TERMINATE = 0xfffb
RESOURCE_DUMP_SEGMENT_TYPE_ERROR = 0xfffc
RESOURCE_DUMP_SEGMENT_TYPE_INFO = 0xfffe
RESOURCE_DUMP_SEGMENT_TYPE_MENU = 0xffff
RESOURCE_DUMP_SEGMENT_TYPE_REFERENCE = 0xfffd


DEVICE_RDMA = "__AUTO__"
INF_DEPTH = -1 + 2**32
DEFAULT_VHCA = 0xFFFF

DWORD_SIZE = 4

# segment start/end specify where the 'type' attr starts and ends in the raw_data of each segment.
# should be 0-16 bits
SEGMENT_TYPE_DWORD_LOCATION = 0
SEGMENT_SIZE_DWORD_LOCATION = 0
SEGMENT_TYPE_START = 16
SEGMENT_TYPE_END = 32
SEGMENT_SIZE_START = 0
SEGMENT_SIZE_END = 16
MENU_SEGMENT_NUM_OF_RECORDS_DWORD_LOCATION = 1
MENU_SEGMENT_NUM_OF_RECORDS_START = 16
MENU_SEGMENT_NUM_OF_RECORDS_END = 32

MENU_SEGMENT_TYPE_DWORD_LOCATION = 0
MENU_SEGMENT_DWORD_SUPPORT_ATTRS_LOCATION = 0
MENU_SEGMENT_SEGMENT_NAME_DWORD_LOCATION_START = 1
MENU_SEGMENT_SEGMENT_NAME_DWORD_LOCATION_END = 5
MENU_SEGMENT_INDEX_NAME_1_DWORD_LOCATION_START = 5
MENU_SEGMENT_INDEX_NAME_1_DWORD_LOCATION_END = 9
MENU_SEGMENT_INDEX_NAME_2_DWORD_LOCATION_START = 9
MENU_SEGMENT_INDEX_NAME_2_DWORD_LOCATION_END = 13

NUM_OF_OBJ_ALL = 65535
NUM_OF_OBJ_ACTIVE = 65534

MENU_SEGMENT_TABLE_SEGMENT_TYPE = "Segment Type - "
MENU_SEGMENT_TABLE_DUMP_PARAMS = "Dump Params"
MENU_SEGMENT_TABLE_APPLICABILITY = "Applicability"
MENU_SEGMENT_TABLE_SPECIAL_VALUES = "Special Values"
MENU_SEGMENT_TABLE_MANDATORY = "Mandatory"
MENU_SEGMENT_TABLE_OPTIONAL = "Optional"
MENU_SEGMENT_TABLE_INDEX1 = "index1"
MENU_SEGMENT_TABLE_INDEX2 = "index2"
MENU_SEGMENT_TABLE_NUM_OF_OBJS1 = "num_of_obj1"
MENU_SEGMENT_TABLE_NUM_OF_OBJS2 = "num_of_obj2"
MENU_SEGMENT_TABLE_ALL = "all"
MENU_SEGMENT_TABLE_ACTIVE = "active"
MENU_SEGMENT_TABLE_LINE_LEN = 66
MENU_SEGMENT_TABLE_DUMP_PARAMS_LEN = 32
MENU_SEGMENT_TABLE_APPLICABILITY_LEN = 14
MENU_SEGMENT_TABLE_SPECIAL_VALUES_LEN = 14
MENU_SEGMENT_TABLE_GAP = 3
MENU_SEGMENT_TABLE_NA = "N/A"
MENU_SEGMENT_TABLE_DASH = "-"
MENU_SEGMENT_TABLE_AND = ","
MENU_SEGMENT_TABLE_WRAP = "_"
