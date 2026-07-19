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

#ifndef MLXREG_FIELDS_H
#define MLXREG_FIELDS_H

/*
 * Section and field display names for mlxreg test output.
 * These strings form the parsing contract between C/C++ test
 * output and the Python comparison runner (test_mlxreg.py).
 * Using static const for C/C++ compatibility.
 */

// Section titles
static const char* const SECTION_REGISTER_LIST = "Register List";
static const char* const SECTION_REGISTER_METADATA = "Register Metadata";
static const char* const SECTION_EXPANDED_METADATA = "Expanded Metadata";
static const char* const SECTION_REGISTER_GET = "Register GET";
static const char* const SECTION_REGISTER_GET_INDEXED = "Register GET (indexed)";
static const char* const SECTION_REGISTER_SET = "Register SET";
static const char* const SECTION_RAW_REGISTER_GET = "Raw Register GET";
static const char* const SECTION_ERROR_HANDLING = "Error Handling Tests";

// Section titles — full-path tests
static const char* const SECTION_FULL_PATH_METADATA = "Full Path Metadata";
static const char* const SECTION_FULL_PATH_GET = "Full Path Register GET";

// Field labels
static const char* const FIELD_TOTAL = "Total";
static const char* const FIELD_FIELD_COUNT = "Field Count";
static const char* const FIELD_INDEXES = "Indexes";
static const char* const FIELD_DESCRIPTION = "Description";
static const char* const FIELD_FULL_PATH = "Full Path";
static const char* const FIELD_ENUMS = "Enums";

#endif /* MLXREG_FIELDS_H */
