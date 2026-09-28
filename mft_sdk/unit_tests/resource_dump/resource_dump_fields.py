# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license.

"""
Python mirror of resource_dump/resource_dump_fields.h

Keep in sync with the C header to avoid string drift between
C/C++ tests and Python test runners.
"""

# Section titles
RD_SECTION_RESOURCE_MENU = "Resource Menu"
RD_SECTION_RESOURCE_DUMP = "Resource Dump"
RD_SECTION_ERROR_HANDLING = "Resource Dump Error Handling"

# Record and field labels
RD_FIELD_SEGMENT_TYPE = "Segment Type"
RD_FIELD_INDEX1 = "index1"
RD_FIELD_INDEX2 = "index2"
RD_FIELD_NUM_OF_OBJ1 = "num_of_obj1"
RD_FIELD_NUM_OF_OBJ2 = "num_of_obj2"
RD_FIELD_NAME = "name"
RD_FIELD_SPECIAL = "special"
RD_FIELD_SIZE = "Size"
RD_FIELD_SEGMENTS = "Segments"
RD_FIELD_LAYOUT = "Layout"
RD_FIELD_FILE = "File"
RD_FIELD_TOTAL = "Total"
RD_FIELD_SKIPPED = "Skipped"
RD_FIELD_CASE = "Case"
RD_FIELD_STATUS = "Status"

# Applicability vocabulary — mirrors resourcedump's menu table
RD_APPLICABILITY_MANDATORY = "Mandatory"
RD_APPLICABILITY_OPTIONAL = "Optional"
RD_APPLICABILITY_NA = "N/A"

# Special-value vocabulary — mirrors resourcedump's menu table
RD_SPECIAL_ALL = "all"
RD_SPECIAL_ACTIVE = "active"
RD_SPECIAL_SEPARATOR = ","
RD_SPECIAL_NA = "N/A"

# The four dump parameters a menu record describes, in the order both the SDK
# and resourcedump print them.
DUMP_PARAMS = (RD_FIELD_INDEX1, RD_FIELD_NUM_OF_OBJ1, RD_FIELD_INDEX2, RD_FIELD_NUM_OF_OBJ2)

# Segment types that frame every dump; see the resource dump PRM section.
SEGMENT_TYPE_TERMINATE = 0xfffb
SEGMENT_TYPE_MENU = 0xffff
