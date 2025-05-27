/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#define DBG_PRINTF(...)                   \
    do                                    \
    {                                     \
        if (getenv("MFT_DEBUG") != NULL)  \
        {                                 \
            fprintf(stderr, __VA_ARGS__); \
        }                                 \
    } while (0)

struct VFIODeviceInfo {
    int      deviceFD;
    uint64_t vsecOffset;
};

#define VFIO_DEVICE_PATH            "/dev/vfio/vfio"
#define LOCKDOWN_FILE               "/sys/kernel/security/lockdown"
#define VFIO_PCI_DRIVER_NEW_ID_PATH "/sys/bus/pci/drivers/vfio-pci/new_id"
#define DBDF_STRING                 "VFIO_DEVICE_DBDF"
#define IOMMU_GROUP_HEX             "IOMMU_GROUP_HEX"
#define PCI_CAPABILITY_LIST         0x34
#define PCI_CAP_ID_VSC              0x09
