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

#pragma once

#define BLUEFIELD4_PCI_ID 41695
#include <stdint.h>

#ifndef DEVICE_IDENTITY
#define DEVICE_IDENTITY(hw_dev_id, rev_id) (((uint32_t)(rev_id)&0xFU) << 16 | ((uint32_t)(hw_dev_id)&0xFFFFU))
#endif

typedef enum
{
    DEVICE_HW_ID_UNKNOWN = -1,
    DEVICE_DUMMY = 0,
    ConnectX4 = 0x209,
    ConnectX4LX = 0x20b,
    ConnectX5 = 0x20d,
    ConnectX6 = 0x20f,
    ConnectX6DX = 0x212,
    ConnectX6LX = 0x216,
    ConnectX7 = 0x218,
    ConnectX8 = 0x21e,
    ConnectX8_Pure_PCIe_Switch = 0x222,
    ConnectX9_Pure_PCIe_Switch = 0x228,
    ConnectX9 = 0x224,
    ConnectX10 = 0x226,
    BlueField = 0x211,
    BlueField2 = 0x214,
    BlueField3 = 0x21c,
    BlueField4 = 0x224,
    BlueField4_PCIID = 0xa2df,
    SwitchIB = 0x247,
    SwitchIB2 = 0x24b,
    Spectrum = 0x249,
    Spectrum2 = 0x24e,
    Spectrum3 = 0x250,
    Spectrum4 = 0x254,
    Spectrum5 = 0x270,
    Spectrum6 = 0x274,
    Spectrum7 = 0x2A2,
    Quantum = 0x24d,
    Quantum2 = 0x257,
    Quantum3 = 0x25b,
    NVLink6_Switch = 0x278,
    NVLink7_Switch = 0x27c,
    NVLink8_Switch = 0x2a0,
    GB100 = 0x2900,
    GR100 = 0x3000,
    GR150 = 0x3480,
    GR150A01P = DEVICE_IDENTITY(0x3480, 1),
    NR10 = 0x4088,
    FN100 = 0x3780,
    CableSFP = 0x3,
    Baritone = 0x6b,
    Ardbeg = 0x6e,
    Menhit = 0x6f,
    Ardbeg_Revision_1 = 0x7e,
    ArcusP_Test_Chip = 0x7f,
    CableQSFPaging = 0x11,
    CableCMIS = 0x19,
    CableCMIS0x1e = 0x1e,
    Ardbeg_Mirrored = 0x70,
    Baritone_Mirrored = 0x71,
    Menhit_Version_1 = 0x72,
    Menhit_Version_2 = 0x73,
    ArcusP = 0x80,
    ArcusE = 0x282,
    Arcus2 = 0x288,
    Libra = 0x286,
    ArcusESddv = 0x82,
    Sagitta = 0x84,
    SagittaZ = 0x90,
    CableQSFP = 0xd,
    Vera = 0x2f95

} eDeviceID;