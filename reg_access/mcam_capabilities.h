/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#pragma once

#include "reg_access/reg_access.h"
#include <cstring>

#define MCAM_REG_GROUPS_AMOUNT 4

// functions and constants to extract valid bit in a more generic way
static const unsigned int REG_ACCESS_BASE_GROUP_0_ID = 0x9000;
static const unsigned int REG_ACCESS_BASE_GROUP_1_ID = 0x9080;
static const unsigned int REG_ACCESS_BASE_GROUP_2_ID = 0x9100;
static const unsigned int REG_ACCESS_BASE_GROUP_3_ID = 0x9180;
static const unsigned int MAX_REG_ACCESS_ID = 0x91FF;
static const unsigned int REG_GROUP_LEN = 0x80;

// Warning: before using this enum, please check in the PRM that name and description are up to date
typedef enum
{
    MCAM_CAP_MGIR_PCI_SWITCH_ONLY_MODE = 74, // If set, MGIR.hw_info.pci_switch_only_mode is supported [NIC_only]

    MCAM_CAP_MAX // for validation
} mcam_capability_t;

// Helper function to validate capability range
bool is_valid_mcam_capability(mcam_capability_t cap);

// Helper function to check if a capability is supported according to MCAM register
reg_access_status_t isCapabilitySupportedAccordingToMcamReg(mfile* mf,
                                                            mcam_capability_t capability_number,
                                                            bool dword_swap_needed,
                                                            bool* is_capability_supported);

// Helper function to get the right group index of a register - the registers are grouped into 4 groups in
// MCAM.mng_access_reg_cap_mask
reg_access_status_t getIndexOfRegGroup(unsigned int reg_id, int* idx);

// Helper function to check if a register is supported according to MCAM register
reg_access_status_t isRegisterValidAccordingToMcamReg(mfile* mf, unsigned int reg_id, bool* is_reg_valid);