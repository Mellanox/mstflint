/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef RESOURCE_DUMP_FIELDS_H
#define RESOURCE_DUMP_FIELDS_H

/*
 * Section and field display names for resource dump test output.
 * These strings form the parsing contract between C/C++ test output and the
 * Python comparison runners (test_menu.py / test_dump.py / test_error_handling.py).
 * The applicability and special-value vocabularies deliberately match what
 * `resourcedump query` prints, so a comparison is a plain string equality.
 */

/* Section titles */
static const char* const RD_SECTION_RESOURCE_MENU = "Resource Menu";
static const char* const RD_SECTION_RESOURCE_DUMP = "Resource Dump";
static const char* const RD_SECTION_ERROR_HANDLING = "Resource Dump Error Handling";

/* Record and field labels */
static const char* const RD_FIELD_SEGMENT_TYPE = "Segment Type";
static const char* const RD_FIELD_INDEX1 = "index1";
static const char* const RD_FIELD_INDEX2 = "index2";
static const char* const RD_FIELD_NUM_OF_OBJ1 = "num_of_obj1";
static const char* const RD_FIELD_NUM_OF_OBJ2 = "num_of_obj2";
static const char* const RD_FIELD_NAME = "name";
static const char* const RD_FIELD_SPECIAL = "special";
static const char* const RD_FIELD_SIZE = "Size";
static const char* const RD_FIELD_SEGMENTS = "Segments";
static const char* const RD_FIELD_LAYOUT = "Layout";
static const char* const RD_FIELD_FILE = "File";
static const char* const RD_FIELD_TOTAL = "Total";
static const char* const RD_FIELD_SKIPPED = "Skipped";
static const char* const RD_FIELD_CASE = "Case";
static const char* const RD_FIELD_STATUS = "Status";

/* The menu segment, advertised by every device that supports resource dump. */
#define SEGMENT_TYPE_MENU 0xffff

/* Applicability vocabulary — mirrors resourcedump's menu table */
static const char* const RD_APPLICABILITY_MANDATORY = "Mandatory";
static const char* const RD_APPLICABILITY_OPTIONAL = "Optional";
static const char* const RD_APPLICABILITY_NA = "N/A";

/* Special-value vocabulary — mirrors resourcedump's menu table */
static const char* const RD_SPECIAL_ALL = "all";
static const char* const RD_SPECIAL_ACTIVE = "active";
static const char* const RD_SPECIAL_SEPARATOR = ",";
static const char* const RD_SPECIAL_NA = "N/A";

#endif /* RESOURCE_DUMP_FIELDS_H */
