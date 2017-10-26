
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef __ERR_MSGS__
#define __ERR_MSGS__

enum {
    MLX_FWM_SUCCESS = 0,
    ERR_CODE_QUERY_FAILED = 1,
    ERR_CODE_PROG_FAILED  = 2,
    ERR_CODE_BAD_CMD_ARGS = 3,
    ERR_CODE_CREATE_LOG_FAIL = 4,
    ERR_CODE_FETCH_LOCAL_DEVICES_FAIL = 5,
    ERR_CODE_SERVER_DOWNLOAD_FAILED = 6,
    ERR_CODE_MEM_ALLOC_FAIL = 7,
    ERR_CODE_INTERNAL_ERR = 8,
    ERR_CODE_IMG_NOT_FOUND = 9,
    ERR_CODE_CREATE_OUTPUT_FILE_FAIL = 10,
    ERR_CODE_MULTI_IMG_SRC_FOUND = 11,
    ERR_CODE_BAD_INI_FILE = 12,
    ERR_CODE_SERVER_RETRIEVE_FAIL = 13,
    ERR_CODE_WRITE_FILE_FAIL = 14,
    ERR_CODE_EXTRACT_IMAGE_FAIL = 15,
    ERR_CODE_MIXED_VERSIONS_FOUND = 16,
    ERR_CODE_FILE_PARSE_FAILED = 17,
    ERR_CODE_INTERRUPTED = 18,
    ERR_CODE_NOT_ROOT    = 19,
    ERR_CODE_NO_DEVICES_FOUND = 20,
    ERR_CODE_NO_DEVICES_FOUND_LVIM = 171,
    ERR_CODE_CLEAR_SEMAPORE = 21,
    ERR_CODE_UNKNOWN_EXPANSION_ROM = 22,
    ERR_CODE_UNSUPPORTED_DEVICE = 23,
    ERR_CODE_ONLINE_UPDATE_CONNECTION_ERROR = 24,
    ERR_CODE_ONLINE_UPDATE_INTERNAL_ERR = 25,
    ERR_CODE_INVALID_CHOICE = 26,
    ERR_CODE_NONE_FAIL_SAFE = 27,
    ERR_CODE_SERVER_QUERY_FAILED = 28,
    ERR_CODES_NUM
};

#define ERR_MSG_QUERY_FAILED             "Failed to query one or more devices"
#define ERR_MSG_PROG_FAILED              "Failed to program device"
#define ERR_MSG_BAD_CMD_ARGS             "Bad command line arguments"
#define ERR_MSG_CREATE_LOG_FAIL          "Failed to create log file"
#define ERR_MSG_FETCH_LOCAL_DEVICES_FAIL "Failed during device query"
#define ERR_MSG_SERVER_DOWNLOAD_FAILED   "Failed to download from server"
#define ERR_MSG_MEM_ALLOC_FAIL           "Failed to allocate memory"
#define ERR_MSG_INTERNAL_ERR             "Internal Error"
#define ERR_MSG_IMG_NOT_FOUND            "No relevant image found for one or more devices"
#define ERR_MSG_CREATE_OUTPUT_FILE_FAIL  "Failed to create output file"
#define ERR_MSG_MULTI_IMG_SRC_FOUND      "Failed due to multiple image source ambiguity"
#define ERR_MSG_BAD_INI_FILE             "Error parsing ini file"
#define ERR_MSG_SERVER_RETRIEVE_FAIL     "Failed to retrieve from server"
#define ERR_MSG_WRITE_FILE_FAIL          "Failed to write file"
#define ERR_MSG_EXTRACT_IMAGE_FAIL       "Failed to extract image"
#define ERR_MSG_MIXED_VERSIONS_FOUND     "Mixed component versions found"
#define ERR_MSG_FILE_PARSE_FAILED        "Failed while parsing file"
#define ERR_MSG_INTERRUPTED              "Interrupted by user"
#define ERR_MSG_NOT_ROOT                 "User is not root"
#define ERR_MSG_NO_DEVICES_FOUND         "No devices found or specified"
#define ERR_MSG_CLEAR_SEMAPORE           "Clear semaphore failure"
#define ERR_MSG_UNKNOWN_EXPANSION_ROM    "Unknown expansion rom"
#define ERR_MSG_UNSUPPORTED_DEVICE       "Device is not supported in online update"
#define ERR_MSG_ONLINE_UPDATE_CONNECTION_ERROR "Failed to communicate with Server"
#define ERR_MSG_ONLINE_UPDATE_INTERNAL_ERR   "Internal Error in online update"
#define ERR_MSG_IVALID_CHOICE                "Select choice is invalid"
#define ERR_MSG_NONE_FAIL_SAFE               "Burn is fail safe, None fail safe required"
#define ERR_MSG_SERVER_QUERY                 "Failed to query PSIDs from server"

#endif
