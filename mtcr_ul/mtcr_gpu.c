/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *
 */
#include "mtcr_gpu.h"

#include "dev_mgt/tools_dev_types.h"

typedef struct pci_id_range_st {
    unsigned int lower_bound;
    unsigned int upper_bound;
} pci_id_range;

pci_id_range GB100_PCI_IDS[] = {{0x2900, 0x29FF}, {0x2B00, 0x2B7F}, {0x3180, 0x31FF},
                                {0x3200, 0x327F}, {0x3300, 0x33FF}, {0x3400, 0x347F}};

pci_id_range GR100_PCI_IDS[] = {{0x3000, 0x30FF}};

int is_gb100_pci_device(u_int16_t pci_device_id)
{
    unsigned int i = 0;
    for (i = 0; i < sizeof(GB100_PCI_IDS) / sizeof(pci_id_range); i++) {
        if ((pci_device_id >= GB100_PCI_IDS[i].lower_bound) && (pci_device_id <= GB100_PCI_IDS[i].upper_bound)) {
            return true;
        }
    }
    return false;
}

int is_gr100_pci_device(u_int16_t pci_device_id)
{
    unsigned int i = 0;
    for (i = 0; i < sizeof(GR100_PCI_IDS) / sizeof(pci_id_range); i++) {
        if ((pci_device_id >= GR100_PCI_IDS[i].lower_bound) && (pci_device_id <= GR100_PCI_IDS[i].upper_bound)) {
            return true;
        }
    }
    return false;
}

int is_gpu_pci_device(u_int16_t pci_device_id)
{
    return (is_gb100_pci_device(pci_device_id) || is_gr100_pci_device(pci_device_id));
}

bool is_gb100_device(u_int16_t hw_dev_id)
{
    return hw_dev_id == DeviceGB100_HwId;
}

bool is_gr100_device(u_int16_t hw_dev_id)
{
    return hw_dev_id == DeviceGR100_HwId;
}

bool is_gpu_device(u_int16_t hw_dev_id)
{
    return (is_gb100_device(hw_dev_id) || is_gr100_device(hw_dev_id));
}

u_int16_t get_hw_dev_id_by_pci_id(u_int16_t pci_device_id)
{
    if (is_gb100_pci_device(pci_device_id)) {
        return DeviceGB100_HwId;
    } else if (is_gr100_pci_device(pci_device_id)) {
        return DeviceGR100_HwId;
    }
    return 0;
}
