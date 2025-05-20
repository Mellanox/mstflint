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

#include "VFIODriverAccessWrapperC.h"
#include "VFIODriverAccess.h"
#include "VFIODriverAccessDefs.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/vfio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

void VFIODriverAccess::OpenVFIODevices(const std::string& dbdf, int& deviceFD)
{
    try
    {
        // Bind the device to the vfio-pci driver.
        VFIODriverAccess::bindDeviceToVfioPciDriver(dbdf);

        // Open the main VFIO control device (/dev/vfio/vfio).
        // This is needed to access the VFIO API and manage containers.
        int vfioFD = OpenVFIODevice();

        // Find the IOMMU group number that this PCI device belongs to.
        std::string iommuGroup = FindIOMMUGroupByDBDF(dbdf);

        // Open the VFIO group device (/dev/vfio/<group>) for this IOMMU group.
        int groupFD = OpenVFIOGroup(iommuGroup);

        // Check if the VFIO group is viable (not bound to other drivers, ready for use).
        CheckVFIOGroupViability(groupFD);

        // Attach the VFIO group to the main VFIO control device.
        AttachGroupToContainer(groupFD, vfioFD);

        // Enable IOMMU for the main VFIO control device.
        EnableIOMMU(vfioFD);

        // Get the device file descriptor for the PCI device.
        // This allows direct interaction, W/R PCI config space.
        deviceFD = GetDeviceFD(groupFD, dbdf);

        close(groupFD);
    }
    catch (const std::exception& e)
    {
        return;
    }
}

void VFIODriverAccess::CloseVFIODevices(int deviceFD)
{

}

void VFIODriverAccess::GetVSECStartOffset(int deviceFD, uint64_t& vsecOffset)
{
        struct vfio_region_info region;
    region.argsz = sizeof(region);
    region.index = VFIO_PCI_CONFIG_REGION_INDEX;

    if (ioctl(deviceFD, VFIO_DEVICE_GET_REGION_INFO, &region) < 0)
    {
        throw std::runtime_error("Failed to get PCI config region info: " + std::string(strerror(errno)));
    }

    DBG_PRINTF("PCI config region size: 0x%llx, offset: 0x%llx\n", region.size, region.offset);

    uint8_t cap_offset = 0;
    if (pread(deviceFD, &cap_offset, sizeof(cap_offset), region.offset + PCI_CAPABILITY_LIST) != sizeof(cap_offset))
    {
        throw std::runtime_error("Failed to read PCI capability list pointer: " + std::string(strerror(errno)));
    }

    DBG_PRINTF("Initial Capability List Pointer: %d\n", static_cast<int>(cap_offset));

    uint8_t cap_id = 0;
    uint8_t next_offset = cap_offset;

    while (next_offset && next_offset < 0xFF)
    {
        if (pread(deviceFD, &cap_id, sizeof(cap_id), region.offset + next_offset) != sizeof(cap_id))
        {
            throw std::runtime_error("Failed to read PCI capability ID: " + std::string(strerror(errno)));
        }

        if (cap_id == PCI_CAP_ID_VSC)
        {
            DBG_PRINTF("VSEC capability starts at PCI config space offset: 0x%lx\n", vsecOffset);
            vsecOffset = region.offset + next_offset;
        }

        if (pread(deviceFD, &next_offset, sizeof(next_offset), region.offset + next_offset + 1) != sizeof(next_offset))
        {
            throw std::runtime_error("Failed to read next PCI capability pointer: " + std::string(strerror(errno)));
        }
    }

    throw std::runtime_error("VSC not found in PCI config space.");
}

void VFIODriverAccess::bindDeviceToVfioPciDriver(const std::string& hwDevId)
{
    std::ofstream new_id_file(VFIO_PCI_DRIVER_NEW_ID_PATH);
    if (!new_id_file)
    {
        throw std::runtime_error(std::string("Failed to open new_id file: ") + VFIO_PCI_DRIVER_NEW_ID_PATH);
    }

    new_id_file << "15b3 " + hwDevId << std::endl;
    if (!new_id_file)
    {
        throw std::runtime_error(std::string("Failed to write to ") + VFIO_PCI_DRIVER_NEW_ID_PATH);
    }

    DBG_PRINTF("Device bound to vfio-pci successfully: %s\n", VFIO_PCI_DRIVER_NEW_ID_PATH);
}

bool VFIODriverAccess::CheckifKernelLockdownIsEnabled()
{
    std::ifstream lockdownFile(LOCKDOWN_FILE);
    if (!lockdownFile)
    {
        DBG_PRINTF("Could not open /sys/kernel/security/lockdown\n");
        return false;
    }

    std::string line;
    std::getline(lockdownFile, line);
    lockdownFile.close();

    size_t start = line.find('[');
    size_t end = line.find(']');

    if (start != std::string::npos &&
        end != std::string::npos &&
        end > start)
    {
        std::string currentMode = line.substr(start + 1, end - start - 1);
        return currentMode != "none";
    }

    DBG_PRINTF("Unexpected format in lockdown file: %s\n", line.c_str());
    return false;

}

void VFIODriverAccess::CleanupVFIODevice(const std::string& dbdf, const int iommuGroup)
{
    // Step 1: Close group FD
    if (iommuGroup >= 0)
    {
        close(iommuGroup);
    }

    // Step 2: Unbind PCI device from vfio-pci
    std::string unbind_path = "/sys/bus/pci/devices/" + dbdf + "/driver/unbind";
    std::ofstream unbind_file(unbind_path);
    if (!unbind_file)
    {
        throw std::runtime_error("Failed to open unbind path: " + unbind_path);
    }

    unbind_file << dbdf;
    unbind_file.close();

    std::string vfio_dev = "/dev/vfio/" + iommuGroup;
    if (access(vfio_dev.c_str(), F_OK) == 0)
    {
        throw std::runtime_error("VFIO group is still present: " + vfio_dev);
    }
}

std::string VFIODriverAccess::FindIOMMUGroupByDBDF(const std::string& dbdf)
{
    const std::string iommu_path = "/sys/kernel/iommu_groups/";
    DIR* iommu_dir = opendir(iommu_path.c_str());
    if (!iommu_dir)
    {
        perror("opendir");
        return "";
    }

    struct dirent* group_entry;
    while ((group_entry = readdir(iommu_dir)) != nullptr)
    {
        if (group_entry->d_type != DT_DIR)
        {
            continue;
        }

        std::string group_name = group_entry->d_name;
        if (group_name == "." || group_name == "..")
        {
            continue;
        }

        std::string devices_path = iommu_path + group_name + "/devices/";
        DIR* dev_dir = opendir(devices_path.c_str());
        if (!dev_dir)
        {
            continue;
        }

        struct dirent* dev_entry;
        while ((dev_entry = readdir(dev_dir)) != nullptr)
        {
            if (dbdf == dev_entry->d_name)
            {
                closedir(dev_dir);
                closedir(iommu_dir);
                DBG_PRINTF("Found IOMMU group: %s\n", group_name.c_str());
                return group_name; // Found!
            }
        }

        closedir(dev_dir);
    }

    closedir(iommu_dir);
    throw std::runtime_error("IOMMU group not found for DBDF: " + dbdf);
}

int VFIODriverAccess::OpenVFIODevice()
{
    int fd = open(VFIO_DEVICE_PATH, O_RDWR);
    if (fd < 0)
    {
        throw std::runtime_error("Failed to open VFIO device: " + std::string(strerror(errno)));
    }

    int api_version = ioctl(fd, VFIO_GET_API_VERSION);
    if (api_version < 0)
    {
        close(fd);
        throw std::runtime_error("Failed to get VFIO API version: " + std::string(strerror(errno)));
    }

    if (api_version != VFIO_API_VERSION)
    {
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
    if (group < 0)
    {
        throw std::runtime_error("Failed to open VFIO group: " + std::string(strerror(errno)));
    }
    return group;
}

void VFIODriverAccess::CheckVFIOGroupViability(int groupFD)
{
    struct vfio_group_status status;
    status.argsz = sizeof(status);

    if (ioctl(groupFD, VFIO_GROUP_GET_STATUS, &status) < 0)
    {
        throw std::runtime_error("Failed to get VFIO group status: " + std::string(strerror(errno)));
    }

    if (!(status.flags & VFIO_GROUP_FLAGS_VIABLE))
    {
        throw std::runtime_error("IOMMU group is not viable!");
    }
}

void VFIODriverAccess::AttachGroupToContainer(int groupFD, int vfioFD)
{
    if (ioctl(groupFD, VFIO_GROUP_SET_CONTAINER, &vfioFD) < 0)
    {
        throw std::runtime_error("Failed to set VFIO group container: " + std::string(strerror(errno)));
    }
}

void VFIODriverAccess::EnableIOMMU(int vfio_fd)
{
    if (ioctl(vfio_fd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU) < 0)
    {
        throw std::runtime_error("Failed to set IOMMU type 1: " + std::string(strerror(errno)));
    }
}

int VFIODriverAccess::GetDeviceFD(int groupID, const std::string& dbdf)
{
    int fd = ioctl(groupID, VFIO_GROUP_GET_DEVICE_FD, dbdf.c_str());
    if (fd < 0)
    {
        throw std::runtime_error("Failed to get VFIO device FD: " + std::string(strerror(errno)));
    }
    return fd;
}