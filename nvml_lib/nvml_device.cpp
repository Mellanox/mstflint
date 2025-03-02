#include <cstring>
#include <iostream>
#include <nvml.h>
#include "nvml_device.h"
#include "nvml_lib_wrapper.h"
#include "nvml_exception.h"
#include "reg_access/reg_ids.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "tools_layouts/reg_access_gpu_layouts.h"

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

    case REG_ID_MORD:
        registerStatus = AccessRegisterMORD(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_MCAM:
        registerStatus = AccessRegisterMCAM(registerData, registerSize, prmBuffer);
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

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MGIR: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return error;
}

int NvmlDevice::AccessRegisterMORD(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mord.version = nvmlMORD_v1;
    prmBuffer.regId = NVML_GPU_PRM_MORD;

    /* convert the raw data buffer to HCA PRM struct. */
    reg_access_hca_resource_dump_ext mordHcaReg;

    memset(&mordHcaReg, 0, sizeof(mordHcaReg));
    reg_access_hca_resource_dump_ext_unpack(&mordHcaReg, registerData);
    prmBuffer.mord.segmentType = mordHcaReg.segment_type;
    prmBuffer.mord.seqNum = mordHcaReg.seq_num;
    prmBuffer.mord.vhcaIdValid = mordHcaReg.vhca_id_valid;
    prmBuffer.mord.inlineDump = mordHcaReg.inline_dump;
    prmBuffer.mord.vhcaId = mordHcaReg.vhca_id;
    prmBuffer.mord.index1 = mordHcaReg.index1;
    prmBuffer.mord.index2 = mordHcaReg.index2;
    prmBuffer.mord.numOfObj2 = mordHcaReg.num_of_obj2;
    prmBuffer.mord.numOfObj1 = mordHcaReg.num_of_obj1;
    prmBuffer.mord.deviceOpaque = mordHcaReg.device_opaque;
    prmBuffer.mord.mkey = mordHcaReg.mkey;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MORD: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Convert the IOCTL Data to GPUNet struct. */
    memset(&mordHcaReg, 0, sizeof(mordHcaReg));
    reg_access_gpu_resource_dump_ext mordGpuReg;

    memset(&mordGpuReg, 0, sizeof(mordGpuReg));
    reg_access_gpu_resource_dump_ext_unpack(&mordGpuReg, prmBuffer.data);

    /* Convert the GPUNet struct to original HCA struct. */
    mordHcaReg.segment_type = mordGpuReg.segment_type;
    mordHcaReg.seq_num = mordGpuReg.seq_num;
    mordHcaReg.inline_dump = mordGpuReg.inline_dump;
    mordHcaReg.more_dump = mordGpuReg.more_dump;
    mordHcaReg.index1 = mordGpuReg.index1;
    mordHcaReg.index2 = mordGpuReg.index2;
    mordHcaReg.num_of_obj2 = mordGpuReg.num_of_obj2;
    mordHcaReg.num_of_obj1 = mordGpuReg.num_of_obj1;
    mordHcaReg.device_opaque = mordGpuReg.device_opaque;
    mordHcaReg.size = mordGpuReg.size;
    mordHcaReg.vhca_id_valid = mordGpuReg.vhca_id_valid;
    mordHcaReg.vhca_id = mordGpuReg.vhca_id;
    memcpy(mordHcaReg.inline_data, mordGpuReg.inline_data, sizeof(mordGpuReg.inline_data));

    reg_access_hca_resource_dump_ext_pack(&mordHcaReg, registerData);
    return error;
}


int NvmlDevice::AccessRegisterMCAM(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mcam.version = nvmlMCAM_v1;
    prmBuffer.regId = NVML_GPU_PRM_MCAM;

    /* convert the raw data buffer to PRM struct. */
    reg_access_gpu_mcam_reg_ext mcamReg;

    memset(&mcamReg, 0, sizeof(mcamReg));
    reg_access_gpu_mcam_reg_ext_unpack(&mcamReg, registerData);
    prmBuffer.mcam.accessRegGroup = mcamReg.access_reg_group;
    prmBuffer.mcam.featureGroup = mcamReg.feature_group;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MCAM: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return error;
}
