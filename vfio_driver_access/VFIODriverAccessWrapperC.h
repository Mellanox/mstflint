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

#ifndef VFIO_DRIVER_ACCESS_WRAPPER_C_H
#define VFIO_DRIVER_ACCESS_WRAPPER_C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int GetVSECStartOffset(unsigned domain, unsigned bus, unsigned dev, unsigned func, uint64_t* vsecOffset, int* vfioFD);

#ifdef __cplusplus
}
#endif

#endif // VFIO_DRIVER_ACCESS_WRAPPER_C_H