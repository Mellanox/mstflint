/*
 * Copyright (c) 2023-2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <cstring>
#include <fstream>
#include <memory>
#include <string>

#include "NvmlLibWrapper.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"
#include "mtcr.h"

using std::string;
using std::memset;

const unsigned int uMstFileSize = 256;

const string sNETIRPrefix = "netir";

bool IsSupportedDevice(unsigned int uPciDeviceId)
{
    return is_gpu_pci_device(uPciDeviceId);
}

void createMstDir()
{
    // Create mst device dir if doesn't exist.
    std::unique_ptr<OperatingSystemAPI> pOSObject = FactoryOperatingSystemAPI::GetInstance();
    if (!pOSObject)
    {
        LOG_AND_THROW_MFT_ERROR("Failed to create mst device directory");
    }
    pOSObject->CreateDirectoryIfNotExist("/dev/mst");
}

void CreateMstDevice(u_int16_t uPciDeviceId, unsigned int numCreatedDevices, nvmlPciInfo_t& pciInfo)
{
    if (numCreatedDevices == 0)
    {
        createMstDir();
    }
    char fileName[uMstFileSize] = {0};
    snprintf(fileName,
             uMstFileSize - 1,
             "/dev/mst/%s%d_%04x.%x.%02x_gpu%d",
             sNETIRPrefix.c_str(),
             uPciDeviceId,
             pciInfo.domain,
             pciInfo.bus,
             pciInfo.device,
             numCreatedDevices);

    std::ofstream mstDevice(fileName);
    mstDevice.close();
}

nvmlPciInfo_t GetPciInfo(std::unique_ptr<NvmlLibWrapper>& nvmlLibWrapper, nvmlDevice_t nvmlDevice)
{
    nvmlPciInfo_t pciInfo;

    memset(&pciInfo, 0, sizeof(pciInfo));

    nvmlReturn_t error = nvmlLibWrapper->nvmlDeviceGetPciInfo(nvmlDevice, &pciInfo);

    if (error)
    {
        LOG_AND_THROW_MFT_ERROR("Failed to obtain PCI Info: " + std::string(nvmlLibWrapper->nvmlErrorString(error)));
    }

    return pciInfo;
}

unsigned int getGpuDeviceMinorNumberByBDF(const std::string& bdf)
{
    std::unique_ptr<NvmlLibWrapper> nvmlLibWrapper = std::unique_ptr<NvmlLibWrapper>(new NvmlLibWrapper());
    nvmlDevice_t nvmlDevice = nullptr;
    nvmlReturn_t error = nvmlLibWrapper->nvmlDeviceGetHandleByPciBusId(bdf.c_str(), &nvmlDevice);
    if (error != NVML_SUCCESS)
    {
        LOG_AND_THROW_MFT_ERROR("Failed to open NVML GPU device by PCIe BDF: " + bdf + ": " +
                                nvmlLibWrapper->nvmlErrorString(error));
    }
    unsigned int minor = 0;
    error = nvmlLibWrapper->nvmlDeviceGetMinorNumber(nvmlDevice, &minor);
    if (error != NVML_SUCCESS)
    {
        LOG_AND_THROW_MFT_ERROR("Failed to get minor number: " + std::string(nvmlLibWrapper->nvmlErrorString(error)));
    }
    return minor;
}

int detectGpus()
{
    unsigned int gpuDeviceCount = 0;
    unsigned int createdDevices = 0;
    nvmlReturn_t error = NVML_SUCCESS;
    nvmlDevice_t nvmlDevice = nullptr;
    std::unique_ptr<NvmlLibWrapper> nvmlLibWrapper = std::unique_ptr<NvmlLibWrapper>(new NvmlLibWrapper());

    error = nvmlLibWrapper->nvmlDeviceGetCount(&gpuDeviceCount);

    if (error != NVML_SUCCESS)
    {
        LOG_AND_THROW_MFT_ERROR("Failed to detect GPU devices: " + string(nvmlLibWrapper->nvmlErrorString(error)));
    }

    if (gpuDeviceCount == 0)
    {
        LOG_AND_THROW_MFT_ERROR("No supported GPUs found on system");
    }

    for (unsigned int deviceIndex = 0; deviceIndex < gpuDeviceCount; deviceIndex++)
    {
        try
        {
            /* Init device handle by index (e.g. /dev/nvidiaX) */
            error = nvmlLibWrapper->nvmlDeviceGetHandleByIndex(deviceIndex, &nvmlDevice);
            if (nvmlDevice == nullptr)
            {
                LOG_AND_THROW_MFT_ERROR("Failed to open NVML GPU device by index: " + std::to_string(deviceIndex) +
                                        ": " + string(nvmlLibWrapper->nvmlErrorString(error)));
            }
            nvmlPciInfo_t pciInfo = GetPciInfo(nvmlLibWrapper, nvmlDevice);
            u_int16_t pciID =
              ((pciInfo.pciDeviceId & 0xffff0000) >> 16); /* Mask out vendor ID on the lower 16  bits. */

            if (IsSupportedDevice(pciID))
            {
                CreateMstDevice(pciID, createdDevices, pciInfo);
                createdDevices++;
            }
        }
        catch (std::exception& e)
        {
            std::cout << "Warning: " << e.what() << std::endl;
            continue;
        }
    }

    return createdDevices;
}