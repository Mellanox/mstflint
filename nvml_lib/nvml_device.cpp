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


