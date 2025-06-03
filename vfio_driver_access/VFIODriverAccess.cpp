/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */

#include "VFIODriverAccessWrapperC.h"
#include "VFIODriverAccess.h"
#include "VFIODriverAccessDefs.h"
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/vfio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include "common/tools_filesystem.h"

namespace fs_path = mstflint::common::filesystem;

void VFIODriverAccess::OpenVFIODevices(const std::string& dbdf, int& deviceFD, uint64_t& vsecOffset, uint64_t& addressRegionOffset)
{
    try
    {
        if (VFIODeviceRegistry::GetInstance().Contains(dbdf)) {
            deviceFD = VFIODeviceRegistry::GetInstance().GetDeviceInfo(dbdf).deviceFD;
            vsecOffset = VFIODeviceRegistry::GetInstance().GetDeviceInfo(dbdf).vsecOffset;
            addressRegionOffset = VFIODeviceRegistry::GetInstance().GetDeviceInfo(dbdf).addressRegionOffset;
            DBG_PRINTF("Device %s already opened, returning existing FD: %d, VSEC offset: %lx, Address region offset: %lx\n",
                       dbdf.c_str(),
                       deviceFD,
                       vsecOffset,
                       addressRegionOffset);
            return;
        }

        /* Bind the device to the vfio-pci driver. */
        VFIODriverAccess::bindDeviceToVfioPciDriver(dbdf);

        /* Open the main VFIO control device (/dev/vfio/vfio). */
        /* This is needed to access the VFIO API and manage containers. */
        int vfioFD = OpenVFIODevice();

        /* Find the IOMMU group number that this PCI device belongs to. */
        std::string iommuGroup = FindIOMMUGroupByDBDF(dbdf);

        /* Open the VFIO group device (/dev/vfio/<group>) for this IOMMU group. */
        int groupFD = OpenVFIOGroup(iommuGroup);

        /* Check if the VFIO group is viable (not bound to other drivers, ready for use). */
        CheckVFIOGroupViability(groupFD);

        /* Attach the VFIO group to the main VFIO control device. */
        AttachGroupToContainer(groupFD, vfioFD);

        /* Enable IOMMU for the main VFIO control device. */
        EnableIOMMU(vfioFD);

        /* Get the device file descriptor for the PCI device. */
        /* This allows direct interaction, W/R PCI config space. */
        deviceFD = GetDeviceFD(groupFD, dbdf);

        /* Get the VSEC start offset. */
        GetStartOffsets(deviceFD, vsecOffset, addressRegionOffset);

        /* Insert the device info into the registry. */
        VFIODeviceRegistry::GetInstance().InsertDeviceInfo(dbdf, deviceFD, vsecOffset, addressRegionOffset);

        close(groupFD);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

void VFIODriverAccess::CloseVFIODevices(int deviceFD)
{
    (void)deviceFD;
}

void VFIODriverAccess::GetStartOffsets(int deviceFD, uint64_t& vsecOffset, uint64_t& addressRegionOffset)
{
    struct vfio_region_info region;

    region.argsz = sizeof(region);
    region.index = VFIO_PCI_CONFIG_REGION_INDEX;

    if (ioctl(deviceFD, VFIO_DEVICE_GET_REGION_INFO, &region) < 0) {
        throw std::runtime_error("Failed to get PCI config region info: " + std::string(strerror(errno)));
    }

    DBG_PRINTF("PCI config region size: 0x%llx, offset: 0x%llx\n", region.size, region.offset);

    uint8_t cap_offset = 0;

    if (pread(deviceFD, &cap_offset, sizeof(cap_offset), region.offset + PCI_CAPABILITY_LIST) != sizeof(cap_offset)) {
        throw std::runtime_error("Failed to read PCI capability list pointer: " + std::string(strerror(errno)));
    }

    DBG_PRINTF("Initial Capability List Pointer: %d\n", static_cast < int > (cap_offset));

    uint8_t cap_id = 0;
    uint8_t next_offset = cap_offset;

    vsecOffset = 0;
    addressRegionOffset = region.offset;
    while (next_offset && next_offset < 0xFF) {
        if (pread(deviceFD, &cap_id, sizeof(cap_id), region.offset + next_offset) != sizeof(cap_id)) {
            throw std::runtime_error("Failed to read PCI capability ID: " + std::string(strerror(errno)));
        }

        if (cap_id == PCI_CAP_ID_VSC) {
            DBG_PRINTF("VSEC capability starts at PCI config space offset: 0x%lx\n", vsecOffset);
            vsecOffset = next_offset;
            return;
        }

        if (pread(deviceFD, &next_offset, sizeof(next_offset),
                  region.offset + next_offset + 1) != sizeof(next_offset)) {
            throw std::runtime_error("Failed to read next PCI capability pointer: " + std::string(strerror(errno)));
        }
    }

    DBG_PRINTF("VSC not found in PCI config space.\n");
}

bool VFIODriverAccess::isDeviceBoundToVfioPci(const std::string& dbdf)
{
    std::string linkPath = "/sys/bus/pci/devices/" + dbdf + "/driver";
    char resolvedPath[PATH_MAX] = {0};
    ssize_t len = readlink(linkPath.c_str(), resolvedPath, sizeof(resolvedPath) - 1);

    if (len == -1) {
        return false; /* No driver bound or error */
    }
    resolvedPath[len] = '\0';
    std::string target(resolvedPath);
    return target.find("vfio-pci") != std::string::npos;
}

std::string VFIODriverAccess::getDeviceId(const std::string& dbdf)
{
    std::string path = "/sys/bus/pci/devices/" + dbdf + "/device";
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open: " + path);
    }

    std::string value;
    file >> value;

    /* Remove leading "0x" */
    if (value.rfind("0x", 0) == 0) {
        value = value.substr(2);
    }

    return value;
}

void VFIODriverAccess::bindDeviceToVfioPciDriver(const std::string& dbdf)
{
    if (isDeviceBoundToVfioPci(dbdf)) {
        DBG_PRINTF("Device %s is already bound to vfio-pci\n", dbdf.c_str());
        return;
    }

    std::string deviceId = getDeviceId(dbdf);

    std::ofstream new_id_file(VFIO_PCI_DRIVER_NEW_ID_PATH);
    if (!new_id_file) {
        throw std::runtime_error(std::string("Failed to open new_id file: ") + VFIO_PCI_DRIVER_NEW_ID_PATH);
    }

    new_id_file << "15b3 " + deviceId << std::endl;
    if (!new_id_file) {
        throw std::runtime_error(std::string("Failed to write to ") + VFIO_PCI_DRIVER_NEW_ID_PATH);
    }

    DBG_PRINTF("Device bound to vfio-pci successfully: %s\n", VFIO_PCI_DRIVER_NEW_ID_PATH);
}

bool VFIODriverAccess::CheckifKernelLockdownIsEnabled()
{
    std::ifstream lockdownFile(LOCKDOWN_FILE);
    if (!lockdownFile) {
        DBG_PRINTF("Could not open /sys/kernel/security/lockdown\n");
        return false;
    }

    std::string line;

    std::getline(lockdownFile, line);
    lockdownFile.close();

    size_t start = line.find('[');
    size_t end = line.find(']');

    if ((start != std::string::npos) &&
        (end != std::string::npos) &&
        (end > start)) {
        std::string currentMode = line.substr(start + 1, end - start - 1);
        return currentMode != "none";
    }

    DBG_PRINTF("Unexpected format in lockdown file: %s\n", line.c_str());
    return false;
}

void VFIODriverAccess::CleanupVFIODevice(const std::string& dbdf, int iommuGroup)
{
    /* Step 1: Close group FD */
    if (iommuGroup >= 0) {
        close(iommuGroup);
    }

    /* Step 2: Unbind PCI device from vfio-pci */
    std::string unbind_path = "/sys/bus/pci/devices/" + dbdf + "/driver/unbind";

    std::ofstream unbind_file(unbind_path);
    if (!unbind_file) {
        throw std::runtime_error("Failed to open unbind path: " + unbind_path);
    }

    unbind_file << dbdf;
    unbind_file.close();

    std::string vfio_dev = "/dev/vfio/" + iommuGroup;

    if (access(vfio_dev.c_str(), F_OK) == 0) {
        throw std::runtime_error("VFIO group is still present: " + vfio_dev);
    }
}

std::string VFIODriverAccess::FindIOMMUGroupByDBDF(const std::string& dbdf)
{
    const std::string iommu_path = "/sys/kernel/iommu_groups/";
    mstflint::common::filesystem::path iommu_dir_path(iommu_path);

    for (fs_path::directory_iterator it(iommu_dir_path); it != fs_path::directory_iterator(); ++it) {
        if (!fs_path::is_directory(it->path())) {
            continue;
        }

        std::string group_name = it->path().filename().string();
        if ((group_name == ".") || (group_name == "..")) {
            continue;
        }

        fs_path::path devices_path(it->path().string() + "/devices");
        for (fs_path::directory_iterator dev_it(devices_path); dev_it != fs_path::directory_iterator(); ++dev_it) {
            if (dbdf == dev_it->path().filename().string()) {
                DBG_PRINTF("Found IOMMU group: %s\n", group_name.c_str());
                return group_name;
            }
        }
    }

    throw std::runtime_error("IOMMU group not found for DBDF: " + dbdf);
}

int VFIODriverAccess::OpenVFIODevice()
{
    int fd = open(VFIO_DEVICE_PATH, O_RDWR);

    if (fd < 0) {
        throw std::runtime_error("Failed to open VFIO device: " + std::string(strerror(errno)));
    }

    int api_version = ioctl(fd, VFIO_GET_API_VERSION);

    if (api_version < 0) {
        close(fd);
        throw std::runtime_error("Failed to get VFIO API version: " + std::string(strerror(errno)));
    }

    if (api_version != VFIO_API_VERSION) {
        close(fd);
        throw std::runtime_error("Unsupported VFIO API version: " + std::to_string(api_version));
    }

    return fd;
}

int VFIODriverAccess::OpenVFIOGroup(const std::string& iommuGroup)
{
    std::string path = "/dev/vfio/" + iommuGroup;

    DBG_PRINTF("Opening VFIO group: %s\n", path.c_str());
    int group = open(path.c_str(), O_RDWR);

    if (group < 0) {
        throw std::runtime_error("Failed to open VFIO group: " + std::string(strerror(errno)));
    }
    return group;
}

void VFIODriverAccess::CheckVFIOGroupViability(int groupFD)
{
    struct vfio_group_status status;

    status.argsz = sizeof(status);

    if (ioctl(groupFD, VFIO_GROUP_GET_STATUS, &status) < 0) {
        throw std::runtime_error("Failed to get VFIO group status: " + std::string(strerror(errno)));
    }

    if (!(status.flags & VFIO_GROUP_FLAGS_VIABLE)) {
        throw std::runtime_error("IOMMU group is not viable!");
    }
}

void VFIODriverAccess::AttachGroupToContainer(int groupFD, int vfioFD)
{
    if (ioctl(groupFD, VFIO_GROUP_SET_CONTAINER, &vfioFD) < 0) {
        throw std::runtime_error("Failed to set VFIO group container: " + std::string(strerror(errno)));
    }
}

void VFIODriverAccess::EnableIOMMU(int vfio_fd)
{
    if (ioctl(vfio_fd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU) < 0) {
        throw std::runtime_error("Failed to set IOMMU type 1: " + std::string(strerror(errno)));
    }
}

int VFIODriverAccess::GetDeviceFD(int groupID, const std::string& dbdf)
{
    int fd = ioctl(groupID, VFIO_GROUP_GET_DEVICE_FD, dbdf.c_str());

    if (fd < 0) {
        throw std::runtime_error("Failed to get VFIO device FD: " + std::string(strerror(errno)));
    }
    return fd;
}
