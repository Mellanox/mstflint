# Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license.

"""
Python mirror of mlxreg/mlxreg_fields.h

Keep in sync with the C header to avoid string drift between
C/C++ tests and Python test runners.
"""

# Section titles
SECTION_REGISTER_LIST = "Register List"
SECTION_REGISTER_METADATA = "Register Metadata"
SECTION_EXPANDED_METADATA = "Expanded Metadata"
SECTION_REGISTER_GET = "Register GET"
SECTION_REGISTER_GET_INDEXED = "Register GET (indexed)"
SECTION_REGISTER_SET = "Register SET"
SECTION_RAW_REGISTER_GET = "Raw Register GET"
SECTION_ERROR_HANDLING = "Error Handling Tests"

# Section titles — full-path tests
SECTION_FULL_PATH_METADATA = "Full Path Metadata"
SECTION_FULL_PATH_GET = "Full Path Register GET"

# Field labels
FIELD_TOTAL = "Total"
FIELD_FIELD_COUNT = "Field Count"
FIELD_INDEXES = "Indexes"
FIELD_DESCRIPTION = "Description"
FIELD_FULL_PATH = "Full Path"
FIELD_ENUMS = "Enums"
