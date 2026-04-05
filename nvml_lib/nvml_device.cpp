/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <cstring>
#include <iostream>
#include <nvml.h>
#include "nvml_device.h"
#include "nvml_lib_wrapper.h"
#include "nvml_exception.h"
#include "include/mtcr_ul/mtcr_com_defs.h"

NvmlDevice::NvmlDevice(const unsigned int deviceIndex)
{
    nvmlReturn_t error = NVML_SUCCESS;

    _nvmlDevice = nullptr;
    _nvmlLibWrapper = std::unique_ptr < NvmlLibWrapper > (new NvmlLibWrapper());


    /* Init device handle by index (e.g. /dev/nvidiaX) */
    error = _nvmlLibWrapper->nvmlDeviceGetHandleByIndex(deviceIndex, &_nvmlDevice);

    if (_nvmlDevice == nullptr) {
        throw NvmlException("Failed to open MVNL GPU device by index: %d: %s\n",
                            deviceIndex,
                            _nvmlLibWrapper->nvmlErrorString(error));
    }
}

u_int16_t NvmlDevice::GetPciID()
{
    nvmlPciInfo_t pci;

    memset(&pci, 0, sizeof(pci));

    nvmlReturn_t error = _nvmlLibWrapper->nvmlDeviceGetPciInfo(_nvmlDevice, &pci);

    if (error) {
        throw NvmlException("Failed to obtain PCI ID: %s\n",
                            _nvmlLibWrapper->nvmlErrorString(error));
    }
    /* Mask out vendor ID on the lower 16  bits. */
    return ((pci.pciDeviceId & 0xffff0000) >> 16);
}

int NvmlDevice::SendPRMRegister(unsigned char    * registerData,
                                const unsigned int registerSize,
                                const unsigned int registerID,
                                int&               registerStatus,
                                bool               isWrite)
{
    int result = 0;
    unsigned int tlvSize = 20; // OpTLV = 16 bytes + RegTlv = 4 bytes.
    nvmlPRMTLV_v1_t prmBuffer;
    memset(&prmBuffer, 0, sizeof(prmBuffer));

    prmBuffer.dataSize = registerSize + tlvSize;
    memcpy(prmBuffer.inData, registerData, registerSize + tlvSize);

    result = TranslateNvStatus(_nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer));
    memcpy(registerData, prmBuffer.outData, registerSize + tlvSize);
    registerStatus = prmBuffer.status;
    return result;
}

int NvmlDevice::TranslateNvStatus(unsigned int uNvStatus)
{
    switch (uNvStatus)
    {
        case NVML_SUCCESS:
            return ME_REG_ACCESS_OK;
        case NVML_ERROR_INVALID_ARGUMENT:
            return ME_REG_ACCESS_BAD_PARAM;
        case NVML_ERROR_NO_PERMISSION:
            return ME_REG_ACCESS_INSUFFICIENT_PERMISSIONS;
        case NVML_ERROR_NOT_SUPPORTED:
            return ME_REG_ACCESS_REG_NOT_SUPP;
        case NVML_ERROR_ARGUMENT_VERSION_MISMATCH:
            return ME_REG_ACCESS_VER_NOT_SUPP;
        default:
            return uNvStatus;
    }
}


