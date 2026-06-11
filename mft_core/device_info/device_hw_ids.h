/*
 * Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#pragma once

#define BLUEFIELD4_PCI_ID 41695

typedef enum
{
    DEVICE_HW_ID_UNKNOWN = -1,
    DEVICE_DUMMY = 0,
    ConnectIB = 0x1ff,
    ConnectX3 = 0x1f5,
    ConnectX3Pro = 0x1f7,
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
    GB100 = 0x2900,
    GR100 = 0x3000,
    GR150 = 0x3480,
    GR150A01P = 0x3481,
    NR10 = 0x4080,
    FN100 = 0x3780,
    AbirGearBox = 0x256,
    AbirTileGearBox = 0x259,
    AmosGearBox = 0x252,
    AmosGearBoxManager = 0x253,
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
