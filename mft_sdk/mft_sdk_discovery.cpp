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

#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <stdint.h>
#include "mft_sdk/mft_sdk_discovery.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mtcr.h"
#include "dev_mgt/tools_dev_types.h"
#include "common/tools_string.h"
#ifdef ENABLE_VFIO
#include "vfio_driver_access/VFIODriverAccessWrapperC.h"
#endif
#ifdef ENABLE_NVML
#include "mft_core/device/nvml/NvmlDiscoveryLib.h"
#endif
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// string_format is used fully-qualified below (mstflint also exposes a global
// string_format, so a using-declaration here would be ambiguous).
using std::string;

const unsigned int MAX_AVAILABLE_DEVICES_FOR_DISCOVERY = 1024;
const unsigned int MAX_PCIe_SUB_INTERFACE_TYPES = 16;

bool isKernelModuleLoaded(const std::string& moduleName)
{
    std::ifstream modulesFile("/proc/modules");
    if (!modulesFile.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(modulesFile, line))
    {
        std::istringstream iss(line);
        std::string name;
        if (!(iss >> name))
            continue;

        if (name == moduleName)
            return true;
    }

    return false;
}

bool resolveRealPath(const std::string& path, std::string& resolvedPath)
{
    char buffer[PATH_MAX];

    if (!realpath(path.c_str(), buffer))
    {
        return false;
    }

    resolvedPath.assign(buffer);
    return true;
}

MstStatus fwctlDeviceNameFromPciDbdf(const std::string& dbdf, std::string& fwctlName)
{
    const char* sysFwctlClass = "/sys/class/fwctl";
    const char* sysPciDevices = "/sys/bus/pci/devices";

    std::string pciPath = std::string(sysPciDevices) + "/" + dbdf;
    std::string pciRealPath;

    if (!resolveRealPath(pciPath, pciRealPath))
    {
        return MST_ERROR_DEVICE_NOT_FOUND;
    }

    DIR* dir = opendir(sysFwctlClass);
    if (!dir)
    {
        return MST_ERROR_INTERFACE_NOT_AVAILABLE;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        const char* name = entry->d_name;

        if (std::strncmp(name, "fwctl", 5) != 0)
        {
            continue;
        }

        std::string deviceLink = std::string(sysFwctlClass) + "/" + name + "/device";

        std::string deviceRealPath;
        if (!resolveRealPath(deviceLink, deviceRealPath))
        {
            continue;
        }

        /* Match fwctl device to PCI DBDF */
        if (deviceRealPath.compare(0, pciRealPath.size(), pciRealPath) == 0)
        {
            fwctlName = name;
            closedir(dir);
            return MST_SUCCESS;
        }
    }

    closedir(dir);
    return MST_ERROR_INTERFACE_NOT_AVAILABLE;
}

MstStatus vfioDeviceFromPciDbdf(const std::string& dbdf, std::string& vfioDevice)
{
#ifndef ENABLE_VFIO
    (void)dbdf;
    (void)vfioDevice;
    return MST_ERROR_INTERFACE_NOT_AVAILABLE;
#else
    if (!CheckifVfioPciDriverIsLoaded())
    {
        return MST_ERROR_INTERFACE_NOT_AVAILABLE;
    }
    const std::string sysPciDevices = "/sys/bus/pci/devices";
    std::string pciPath = sysPciDevices + "/" + dbdf;
    std::string pciRealPath;

    if (!resolveRealPath(pciPath, pciRealPath))
    {
        return MST_ERROR_INTERFACE_NOT_AVAILABLE;
    }

    vfioDevice = "vfio-" + dbdf;
    return MST_SUCCESS;
#endif
}

MstStatus nvidiaDriverDeviceFromPciDbdf(const std::string& dbdf, std::string& nvidiaDriverDevice)
{
#ifdef ENABLE_NVML
    try
    {
        unsigned int minorNumber = getGpuDeviceMinorNumberByBDF(dbdf);
        nvidiaDriverDevice = "/dev/nvidia" + std::to_string(minorNumber);
        return MST_SUCCESS;
    }
    catch (const std::exception& e)
    {
        return MST_ERROR_DEVICE_NOT_FOUND;
    }
#else
    (void)dbdf;
    (void)nvidiaDriverDevice;
    return MST_ERROR_DEVICE_NOT_FOUND;
#endif
}

MstStatus mstDriverDeviceFromPciDbdf(const std::string& dbdf, std::string& mstDriverDevice, bool isMstPciconf)
{
    if (!isKernelModuleLoaded(isMstPciconf ? "mst_pciconf" : "mst_pci"))
    {
        return MST_ERROR_MST_DRIVER_NOT_LOADED;
    }
    mstDriverDevice = dbdf;
    return MST_SUCCESS;
}

MstPcIeSubInterfaceInfo createPCIeSubInterface(MstPCIeSubInterfaceType pcieSubInterfaceType,
                                               const char* subInterfaceIdentifier)
{
    MstPcIeSubInterfaceInfo currentSubInterface;
    currentSubInterface.pcieSubInterfaceType = pcieSubInterfaceType;
    strncpy(currentSubInterface.subInterfaceIdentifier, subInterfaceIdentifier, MAX_DEVICE_IDENTIFIER_LENGTH - 1);
    currentSubInterface.subInterfaceIdentifier[MAX_DEVICE_IDENTIFIER_LENGTH - 1] = '\0';
    return currentSubInterface;
}

MstStatus getPcieBDFFromMfile(mfile* mf, string& pciBDF)
{
    if (!mf || mf->dinfo == nullptr)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    pciBDF = nbu::mft::common::string_format(
      "%04x:%02x:%02x.%x", mf->dinfo->pci.domain, mf->dinfo->pci.bus, mf->dinfo->pci.dev, mf->dinfo->pci.func);
    return MST_SUCCESS;
}

MstStatus getDeviceIdentifierByType(mfile* mf, MstInterfaceType interfaceType, string& deviceIdentifier)
{
    switch (interfaceType)
    {
        case PCIe:
            return getPcieBDFFromMfile(mf, deviceIdentifier);
        default:
            return MST_ERROR_NOT_SUPPORTED;
    }
}

Mdevs translateInterfaceTypeToFlags(MstInterfaceType interfaceType)
{
    switch (interfaceType)
    {
        case PCIe:
            return MDEVS_TAVOR_CR;
        case Infiniband:
            return MDEVS_IB;
        case MTUSB:
        case NDC:
            return MDEVS_I2CM;
        case I2C:
            return MDEVS_DEV_I2C;
        default:
            return Mdevs(0);
    }
}

MstInterfaceType translateFlagsToInterfaceType(Mdevs flags)
{
    switch (flags)
    {
        case MDEVS_TAVOR_CR:
            return PCIe;
        case MDEVS_IB:
            return Infiniband;
        case MDEVS_I2CM:
            return MTUSB;
        case MDEVS_DEV_I2C:
            return I2C;
        default:
            return UnknownInterfaceType;
    }
}

int getDeviceFlags(MstInterfaceType* interfaceTypes, unsigned int numInterfaceTypes)
{
    int flags = 0;
    for (unsigned int i = 0; i < numInterfaceTypes; i++)
    {
        flags |= translateInterfaceTypeToFlags(interfaceTypes[i]);
    }
    return flags;
}

MstProductType getProductType(dm_dev_id_t hwDevId)
{
    if (dm_is_gpu(hwDevId))
    {
        return GPU;
    }
    else if (dm_dev_is_switch(hwDevId))
    {
        return Switch;
    }
    else if (dm_dev_is_hca(hwDevId))
    {
        return NIC;
    }
    else if (dm_dev_is_retimer(hwDevId))
    {
        return Retimer;
    }
    else
    {
        return UnknownProductType;
    }
}

MstDeviceType getDeviceType(dm_dev_id_t hwDevId)
{
    switch (hwDevId)
    {
        case DeviceConnectX4:
            return ConnectX4;
        case DeviceConnectX4LX:
            return ConnectX4LX;
        case DeviceConnectX5:
            return ConnectX5;
        case DeviceConnectX6:
            return ConnectX6;
        case DeviceConnectX6DX:
            return ConnectX6DX;
        case DeviceConnectX6LX:
            return ConnectX6LX;
        case DeviceConnectX7:
            return ConnectX7;
        case DeviceConnectX8:
            return ConnectX8;
        case DeviceConnectX8_Pure_PCIe_Switch:
            return ConnectX8_Pure_PCIe_Switch;
        case DeviceConnectX9:
            return ConnectX9;
        case DeviceConnectX9_Pure_PCIe_Switch:
            return ConnectX9_Pure_PCIe_Switch;
        case DeviceBlueField:
            return BlueField;
        case DeviceBlueField2:
            return BlueField2;
        case DeviceBlueField3:
            return BlueField3;
        case DeviceBlueField4:
            return BlueField4;
        case DeviceSpectrum:
            return Spectrum;
        case DeviceSpectrum2:
            return Spectrum2;
        case DeviceSpectrum3:
            return Spectrum3;
        case DeviceSpectrum4:
            return Spectrum4;
        case DeviceSpectrum5:
            return Spectrum5;
        case DeviceSpectrum6:
            return Spectrum6;
        case DeviceQuantum:
            return Quantum;
        case DeviceQuantum2:
            return Quantum2;
        case DeviceQuantum3:
            return Quantum3;
        case DeviceNVLink6_Switch:
            return NVLink6_Switch;
        case DeviceGB100:
            return GB100;
        case DeviceGR100:
            return GR100;
        default:
            return UnknownDeviceType;
    }
}

MstStatus updateDeviceInfo(mfile* mf, MstDeviceInfo& deviceInfo)
{
    if (!mf)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    dm_dev_id_t hwDevId = DeviceUnknown;
    uint32_t devid = 0;
    uint32_t revid = 0;
    string deviceIdentifier = "";
    dm_get_device_id(mf, &hwDevId, &devid, &revid);
    deviceInfo.productType = getProductType(hwDevId);
    deviceInfo.deviceType = getDeviceType(hwDevId);
    deviceInfo.interfaceType = translateFlagsToInterfaceType(mf->flags);
    MstStatus status = getDeviceIdentifierByType(mf, deviceInfo.interfaceType, deviceIdentifier);
    if (status != MST_SUCCESS)
    {
        return status;
    }
    strncpy(deviceInfo.deviceIdentifier, deviceIdentifier.c_str(), MAX_DEVICE_IDENTIFIER_LENGTH - 1);
    deviceInfo.deviceIdentifier[MAX_DEVICE_IDENTIFIER_LENGTH - 1] = '\0';
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstGetAvailablePCIeSubinterfaces(MstDeviceInfo* deviceInfo,
                                               MstPcIeSubInterfaceInfo** availableSubInterfaces,
                                               unsigned int* numSubInterfaces)
    {
        if (!deviceInfo)
        {
            return MST_ERROR_UNINITIALIZED;
        }

        if (deviceInfo->interfaceType != PCIe)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MstPcIeSubInterfaceInfo pcieSubInterfaceTypes[MAX_PCIe_SUB_INTERFACE_TYPES];
        memset(pcieSubInterfaceTypes, 0, sizeof(pcieSubInterfaceTypes));
        unsigned int numSubInterfaceDiscovered = 0;
        std::string interfaceIdentifier = "";
        switch (deviceInfo->productType)
        {
            case GPU:
                if (nvidiaDriverDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(NvidiaDriver, interfaceIdentifier.c_str());
                }
                if (mstDriverDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier, false) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(BAR0MSTDriver, interfaceIdentifier.c_str());
                }
                else
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(NvidiaDriver, deviceInfo->deviceIdentifier);
                }
                break;
            case NIC:
                if (fwctlDeviceNameFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(FWCtl, interfaceIdentifier.c_str());
                }
                if (vfioDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(VFIO, interfaceIdentifier.c_str());
                }
                if (mstDriverDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier, true) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(VsecMSTDriver, interfaceIdentifier.c_str());
                }
                else
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(VsecUserLevel, deviceInfo->deviceIdentifier);
                }

                break;
            case Switch:
                if (mstDriverDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier, false) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(BAR0MSTDriver, interfaceIdentifier.c_str());
                }
                else
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(BAR0UserLevel, deviceInfo->deviceIdentifier);
                }
                if (mstDriverDeviceFromPciDbdf(deviceInfo->deviceIdentifier, interfaceIdentifier, true) == MST_SUCCESS)
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(VsecMSTDriver, interfaceIdentifier.c_str());
                }
                else
                {
                    pcieSubInterfaceTypes[numSubInterfaceDiscovered++] =
                      createPCIeSubInterface(VsecUserLevel, deviceInfo->deviceIdentifier);
                }
                break;
            default:
                return MST_ERROR_NOT_SUPPORTED;
        }

        if (numSubInterfaceDiscovered == 0)
        {
            return MST_ERROR_NO_AVAILABLE_DEVICES;
        }

        *availableSubInterfaces = new MstPcIeSubInterfaceInfo[numSubInterfaceDiscovered];
        for (unsigned int i = 0; i < numSubInterfaceDiscovered; i++)
        {
            (*availableSubInterfaces)[i] = pcieSubInterfaceTypes[i];
        }
        *numSubInterfaces = numSubInterfaceDiscovered;
        return MST_SUCCESS;
    }

    MstStatus mstFreePCIeSubInterfaces(MstPcIeSubInterfaceInfo* availableSubInterfaces)
    {
        if (!availableSubInterfaces)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        delete[] availableSubInterfaces;
        return MST_SUCCESS;
    }

    MstStatus mstDiscoverAvailableDevices(MstInterfaceType* interfaceTypes,
                                          unsigned int numInterfaceTypes,
                                          MstDeviceInfo** discoveredDevices,
                                          unsigned int* numDiscoveredDevices)
    {
        if (!interfaceTypes || !discoveredDevices || !numDiscoveredDevices)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        int legacyNumDiscoveredDevices = 0;
        int deviceFlags = getDeviceFlags(interfaceTypes, numInterfaceTypes);
        dev_info* legacyDevInfo = mdevices_info_v(deviceFlags, &legacyNumDiscoveredDevices, 1);
        if ((legacyDevInfo != nullptr) && (legacyNumDiscoveredDevices > 0))
        {
            *numDiscoveredDevices = 0;
            MstDeviceInfo* availableDevices = new MstDeviceInfo[legacyNumDiscoveredDevices];
            memset(availableDevices, 0, sizeof(MstDeviceInfo) * legacyNumDiscoveredDevices);
            for (int i = 0; i < legacyNumDiscoveredDevices; i++)
            {
                mfile* mf = mopen(legacyDevInfo[i].dev_name);
                if (!mf)
                {
                    continue;
                }

                if (updateDeviceInfo(mf, availableDevices[*numDiscoveredDevices]) == MST_SUCCESS)
                {
                    (*numDiscoveredDevices)++;
                }
                mclose(mf);
            }

            *discoveredDevices = new MstDeviceInfo[*numDiscoveredDevices];
            for (unsigned int i = 0; i < *numDiscoveredDevices; i++)
            {
                (*discoveredDevices)[i] = availableDevices[i];
            }
            mdevices_info_destroy(legacyDevInfo, legacyNumDiscoveredDevices);
            delete[] availableDevices;
            return MST_SUCCESS;
        }
        return MST_ERROR_NO_AVAILABLE_DEVICES;
    }

    MstStatus mstFreeDiscoveredDevices(MstDeviceInfo* discoveredDevices)
    {
        if (!discoveredDevices)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        delete[] discoveredDevices;
        return MST_SUCCESS;
    }

    MstStatus mstGetDeviceHandle(MstDevice* mstDevice, const char* deviceIdentifier)
    {
        if (!mstDevice || !deviceIdentifier)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        try
        {
            MftSdk* instance = new MftSdk(deviceIdentifier);
            *mstDevice = reinterpret_cast<MstDevice>(instance);
            return MST_SUCCESS;
        }
        catch (const mft_core::MftGeneralException& e)
        {
            return MST_ERROR_FAILED_TO_OPEN_DEVICE;
        }
    }

#ifdef ENABLE_MST_DEV_I2C
    MstStatus mstGetDeviceHandleWithI2cSecondary(MstDevice* mstDevice,
                                                 const char* deviceIdentifier,
                                                 uint8_t i2cSecondaryAddress)
    {
        if (!mstDevice || !deviceIdentifier)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        set_force_i2c_address(i2cSecondaryAddress);
        return mstGetDeviceHandle(mstDevice, deviceIdentifier);
    }
#endif /* ENABLE_MST_DEV_I2C */

    MstStatus mstGetDeviceHandleByBDF(MstDevice* mstDevice, PciBDF pciBDF, MstPCIeSubInterfaceType subInterfaceType)
    {
        string bdfStr = nbu::mft::common::string_format("%04x:%02x:%02x.%x", pciBDF.domain, pciBDF.bus, pciBDF.device, pciBDF.function);
        string deviceIdentifier = "";
        MstStatus status = MST_SUCCESS;
        switch (subInterfaceType)
        {
            case FWCtl:
                status = fwctlDeviceNameFromPciDbdf(bdfStr, deviceIdentifier);
                break;
            case VFIO:
                status = vfioDeviceFromPciDbdf(bdfStr, deviceIdentifier);
                break;
            case NvidiaDriver:
                status = nvidiaDriverDeviceFromPciDbdf(bdfStr, deviceIdentifier);
                break;
            case VsecMSTDriver:
            case BAR0MSTDriver:
                status = mstDriverDeviceFromPciDbdf(bdfStr, deviceIdentifier, subInterfaceType == VsecMSTDriver);
                break;
            case VsecUserLevel:
            case BAR0UserLevel:
                deviceIdentifier = bdfStr;
                break;
            default:
                return MST_ERROR_NOT_SUPPORTED;
        }
        if (status != MST_SUCCESS)
        {
            return status;
        }
        return mstGetDeviceHandle(mstDevice, deviceIdentifier.c_str());
    }

    MstStatus mstGetDeviceHandleByFwctlDeviceName(MstDevice* mstDevice, const char* fwctlDeviceName)
    {
        return mstGetDeviceHandle(mstDevice, fwctlDeviceName);
    }

    MstStatus mstReleaseDeviceHandle(MstDevice mstDevice)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        delete instance;
        mstDevice = nullptr;
        return MST_SUCCESS;
    }

} // extern "C"