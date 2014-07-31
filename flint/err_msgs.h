/*
 *
 * err_msgs.h - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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


#ifndef __ERR_MSGS_H__
#define __ERR_MSGS_H__

/**********************
 * Flint Status Code
 *********************/

typedef enum {
    FLINT_SUCCESS = 0,
    FLINT_FAILED = 1,
    FLINT_BURN_ABORTED = 7
}FlintStatus;

/***********************
 * Flint Error Messages
 **********************/

#define FLINT_CLEAR_SEM_CMD_ERROR             "No command is allowed when -clear_semaphore flag is given.\n"
#define FLINT_COMMAND_FLAGS_ERROR             "For %s command, Please specify %s.\n"
#define FLINT_PARSE_MEM_ERROR                 "Failed to allocate memory for parsing.\n "
#define FLINT_NO_OPTIONS_FOUND_ERROR          "No options found. "
#define FLINT_INVALID_COMMAD_ERROR            "Invalid command: %s\n"
#define FLINT_TOO_MANY_ARGS_ERROR             "Too many arguments. Expected: %d , Recieved: %d\n"
#define FLINT_TOO_FEW_ARGS_ERROR              "Too few arguments. Expected: %d , Recieved: %d\n"
#define FLINT_NO_COMMAND_ERROR                "No command found."
#define FLINT_OPEN_FWOPS_DEVICE_ERROR         "Cannot open Device: %s. %s\n"
#define FLINT_OPEN_FWOPS_IMAGE_ERROR          "Cannot open Image: %s. %s\n"
#define FLINT_DEVICE_AND_IMAGE_ERROR          "Please specify either Device or Image.\n"
#define FLINT_NO_DEVICE_ERROR                 "Please specify Device.\n"
#define FLINT_NO_IMAGE_ERROR                  "Please specify Image file.\n"
#define FLINT_MISSED_ARG_ERROR                "Missed %s parameter after \"%s\" command.\n"
#define FLINT_CMD_ARGS_ERROR                  "Command \"%s\" requires %d arguments, but %d arguments were given\n"
#define FLINT_CMD_ARGS_ERROR2                 "Command \"%s\" requires at most %d arguments, but %d arguments were given\n"
#define FLINT_CMD_ARGS_ERROR3                 "Command \"%s\" requires at least %d arguments, but %d arguments were given\n"
#define FLINT_CMD_ARGS_ERROR4                 "Command \"%s\" requires %d or %d arguments, but %d arguments were given\n"
#define FLINT_INVALID_OPTION_ERROR            "Unknown option \"%s\" for the \"%s\" command. you can use %s.\n"
#define FLINT_INVALID_FLAG_ERROR              "Invalid switch \"%s\" is specified.\n"
#define FLINT_INVALID_UID_NUM_BX_ERROR        "Number of UIDs on BridgeX should be %d\n"
#define FLINT_BX_BAD_MAC_FORMAT_ERROR         "Bad mac ( %4.4x%8.8x ) %s. Please re-burn with a valid MACs value.\n"
#define FLINT_INVALID_FLAG_WITH_FLAG_ERROR    "Cannot specify \"%s\" flag with \"%s\" flag.\n"
#define FLINT_INVALID_FLAG_WITHOUT_FLAG_ERROR "\"%s\" flag must be specified with \"%s\" flag.\n"
#define FLINT_INVALID_FLAG_WITH_CMD_ERROR     "Cannot specify flag: %s with Command: %s\n"
#define FLINT_CMD_VERIFY_ERROR                "FW image verification failed: %s. AN HCA DEVICE CAN NOT BOOT FROM THIS IMAGE.\n"
#define FLINT_FAILED_QUERY_ERROR              "Failed to query %s: %s.%s\n"
#define FLINT_COMMAND_DEVICE_IMAGE_ERROR      "Command \"%s\" requires both image and device to be specified.\n"
#define FLINT_COMMAND_DEVICE_ERROR            "Command \"%s\" requires device, but an image file was given.\n"
#define FLINT_COMMAND_IMAGE_ERROR             "Command \"%s\" requires an image file, but device was given.\n"
#define FLINT_COMMAND_DEVICE_ERROR2           "Command \"%s\" requires device, but both an image file and a device are given.\n"
#define FLINT_COMMAND_IMAGE_ERROR2            "Command \"%s\" requires an image, but both an image file and a device are given.\n"
#define FLINT_HW_SET_ARGS_ERROR               "bad argument of hw set command : %s, it should be in the format PARAM_NAME=VALUE\n"
#define FLINT_HW_COMMAND_ERROR                "HW %s failed. %s\n"
#define FLINT_SWRESET_ERROR                   "Software reset failed. %s\n"
#define FLINT_ERASE_SEC_ERROR                 "Erase sector failed. %s\n"
#define FLINT_INVALID_ADDR_ERROR              "Invalid address \"%s\"\n"
#define FLINT_FLASH_READ_ERROR                "Flash read failed. %s\n"
#define FLINT_FLASH_WRITE_ERROR               "Flash write failed. %s\n"
#define FLINT_INVALID_DATA_ERROR              "Invalid data \"%s\"\n"
#define FLINT_INVALID_SIZE_ERROR              "Invalid size \"%s\", Length should be 4-bytes aligned.\n"
#define FLINT_INVALID_ARG_ERROR               "Invalid argument \"%s\"\n"
#define FLINT_OPEN_FILE_ERROR                 "Cannot open %s: %s\n"
#define FLINT_WRITE_FILE_ERROR                "Failed to write to %s: %s\n"
#define FLINT_IO_OPEN_ERROR                   "Failed to open %s: %s\n"
#define FLINT_IMAGE_READ_ERROR                "Failed to read image. %s\n"
#define FLINT_READ_ERROR                      "Failed to read from %s. %s\n"
#define FLINT_WIN_NOT_SUPP_ERROR              "Command \"%s\" is not supported in windows.\n"
#define FLINT_GEN_COMMAND_ERROR               "Failed to execute command %s. %s\n"
#define FLINT_FS3_BB_ERROR                    "bb command is not supported anymore in FS3 image, please use b for burning FS3 image.\n"
#define FLINT_FS3_BURN_ERROR                  "Burning FS3 image failed: %s\n"
#define FLINT_FS2_BURN_ERROR                  "Burning FS2 image failed: %s\n"
#define FLINT_PSID_ERROR                      "PSID mismatch. The PSID on flash (%s) differs from the PSID in the given image (%s).\n"
#define FLINT_FS2_STRIPED_ERROR               "The -striped_image cannot be used with the burn command\n"
#define FLINT_IMG_DEV_COMPAT_ERROR            "The given device requires an %s image type, but the given image file does not contain an %s FW image\n"
#define FLINT_UNKNOWN_FW_TYPE_ERROR           "Unknown Firmware Type.\n"
#define FLINT_READ_ROM_ERROR                  "Read ROM failed. %s\n"
#define FLINT_SG_GUID_ERROR                   "Cannot set GUIDs: %s\n"
#define FLINT_SG_UID_ERROR                    "Failed to set UID: %s\n"
#define FLINT_MFG_ERROR                       "Failed to set manufacture guids: %s\n"
#define FLINT_VSD_ERROR                       "Failed to set the VSD: %s\n"
#define FLINT_VPD_ERROR                       "Failed to set VPD: %s\n"
#define FLINT_SET_KEY_ERROR                   "Failed to set the HW access key: %s\n"
#define FLINT_RESET_CFG_ERROR                 "Failed to reset Configuration: %s\n"
#define FLINT_FIX_IMG_ERROR                   "Failed to fix device image: %s\n"
#define FLINT_DROM_ERROR                      "Remove ROM failed: %s\n"
#define FLINT_BROM_ERROR                      "Burn ROM failed: %s\n"
#define FLINT_DUMP_ERROR                      "Failed dumping %s : %s\n"
#define FLINT_ROM_QUERY_ERROR                 "Image file rom (%s) query failed. %s\n"
#define FLINT_WB_FILE_ERROR                   "failed to open file: %s. %s\n"
#define FLINT_WB_ERROR                        "write Block Failed. %s\n"
#define FLINT_NO_ZLIB_ERROR					  "Executable was compiled with \"dump files\" option disabled.\n"

/**************************
 * Flint Warning Messages
 *************************/
#define FLINT_QQ_WARRNING               "-W- Running quick query - Skipping full image integrity checks.\n"
#define FLINT_NOT_MLNX_FW_WARNING      "-W- Not a Mellanox FW image (vendor_id = 0x%04x). VSD and PSID are not displayed.\n"
#define FLINT_BLANK_GUIDS_WARNING      "-W- GUIDs/MACs values and their CRC are not set.\n"
#define FLINT_MULTI_BIT_WARNING        "Multicast bit (bit 40) is set."
#define FLINT_MORE_48_BITS_WARNING     "More than 48 bits are used."
#define FLINT_BAD_MAC_ADRESS_WARNING   "\n-W- Bad mac address ( %4.4x%8.8x ): %s\n"
#define FLINT_MAC_ENTRIES_WARNING      "-W- Cannot get MAC address: Expecting %d entries in guid section, got %d. Probably an old FW image. Please update.\n"
#define FLINT_INTERRUPT_WARRNING       "\n-W- An internal error occurred. This program cannot be interrupted.\n"
#define FLINT_SET_GUIDS_WARRNING       "-W- GUIDs are already set, re-burning image with the new GUIDs ...\n"
#define FLINT_OCR_WARRNING             "\n-W- Firmware flash cache access is enabled. Running in this mode may cause the firmware to hang.\n"
#endif
