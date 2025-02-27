#include <cstring>
#include <iostream>
#include <nvml.h>
#include "nvml_device.h"
#include "nvml_lib_wrapper.h"
#include "nvml_exception.h"
#include "reg_access/reg_ids.h"

NvmlDevice::NvmlDevice(const unsigned int deviceIndex)
{
    nvmlReturn_t error = NVML_SUCCESS;

    _nvmlDevice = nullptr;
    _nvmlLibWrapper = std::unique_ptr < NvmlLibWrapper > (new NvmlLibWrapper());


    /* Init device handle by index (e.g. /dev/nvidiaX) */
    error = _nvmlLibWrapper->nvmlDeviceGetHandleByIndex_v2(deviceIndex, &_nvmlDevice);

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

    nvmlReturn_t error = _nvmlLibWrapper->nvmlDeviceGetPciInfo_v3(_nvmlDevice, &pci);

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
    /* Set PRM Buffer version. */
    nvmlPRMBuffer_t prmBuffer;

    memset(&prmBuffer, 0, sizeof(prmBuffer));
    prmBuffer.version = nvmlPRMBuffer_v1;
    prmBuffer.isWrite = isWrite;

    switch (registerID) {
    case REG_ID_MGIR:
        registerStatus = AccessRegisterMGIR(registerData, registerSize, prmBuffer);
        break;

    default:
        throw NvmlException("NVML does not support register ID 0x%x\n", registerID);
    }

    return 0;
}

int NvmlDevice::AccessRegisterMGIR(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mgir.version = nvmlMGIR_v1;
    prmBuffer.regId = NVML_GPU_PRM_MGIR;

    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);

    if (error) {
        std::cout << "Error sending MGIR: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return error;
}
