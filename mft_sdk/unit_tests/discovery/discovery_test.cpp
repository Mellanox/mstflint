/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

/*
 * Coverage-focused tests for mft_sdk_discovery.cpp.
 *
 * Group A tests do NOT require any Mellanox/NVIDIA hardware.
 * Group B tests need a real device -- pass -d <BDF> to enable them.
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

// EnvVarGuard comes from test_utils.h (shared by all unified/so test TUs).

// Mirrors isKernelModuleLoaded() in mft_sdk_discovery.cpp: the SDK decides
// driver-backed sub-interface availability by scanning /proc/modules.
static bool isKernelModuleLoaded(const std::string& moduleName)
{
    std::ifstream modulesFile("/proc/modules");
    std::string line;
    while (std::getline(modulesFile, line))
    {
        std::istringstream iss(line);
        std::string name;
        if ((iss >> name) && name == moduleName)
        {
            return true;
        }
    }
    return false;
}

// Returns the BDF of the first discovered PCIe device, or false when none is
// available (callers soft-skip in that case).
static bool getFirstDiscoveredPcieBdf(MstPciBDF& bdf)
{
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    if (mstDiscoverAvailableDevices(types, 1, &devices, &numDevices) != MST_SUCCESS)
    {
        return false;
    }
    bool found = false;
    if (numDevices > 0)
    {
        unsigned int domain = 0, bus = 0, device = 0, func = 0;
        found = sscanf(devices[0].deviceIdentifier, "%x:%x:%x.%x", &domain, &bus, &device, &func) == 4;
        bdf.domain = domain;
        bdf.bus = bus;
        bdf.device = device;
        bdf.function = func;
    }
    mstFreeDiscoveredDevices(devices);
    return found;
}

class MftSdkDiscoveryNoDeviceTest : public ::testing::Test
{
};

class MftSdkDiscoveryDeviceTest : public ::testing::Test
{
protected:
    bool hasDevice = false;

    void SetUp() override
    {
        if (!g_devicePci.empty())
        {
            hasDevice = true;
        }
    }
};

// ============================================================================
// GROUP A: No device required
// ============================================================================

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleNullIdentifier)
{
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleInvalidDevice)
{
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, "nonexistent_device_xyz_12345");
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_OPEN_DEVICE);

    const char* initErr = mstGetInitErrorString();
    EXPECT_NE(initErr, nullptr);
    EXPECT_GT(strlen(initErr), 0u) << "Init error string should be non-empty after failed open";
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByFwctlInvalid)
{
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByFwctlDeviceName(&dev, "fwctl99999");
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_OPEN_DEVICE);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfUnsupportedType)
{
    MstPciBDF bdf = {0, 0, 0, 0};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, UnknownPCIeSubInterfaceType);
    EXPECT_EQ(status, MST_ERROR_NOT_SUPPORTED);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfFwctlNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, FWCtl);
    EXPECT_NE(status, MST_SUCCESS);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfVfioNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VFIO);
    // vfioDeviceFromPciDbdf returns this both when vfio_pci is not loaded and
    // when the BDF has no /sys/bus/pci/devices entry, so it is deterministic.
    EXPECT_EQ(status, MST_ERROR_INTERFACE_NOT_AVAILABLE);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfNvidiaDriverNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, NvidiaDriver);
    // nvidiaDriverDeviceFromPciDbdf maps any NVML lookup failure (missing
    // libnvidia-ml or no GPU at the BDF) to this status.
    EXPECT_EQ(status, MST_ERROR_DEVICE_NOT_FOUND);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfVsecMSTDriverNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VsecMSTDriver);
    EXPECT_NE(status, MST_SUCCESS);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfBAR0MSTDriverNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, BAR0MSTDriver);
    EXPECT_NE(status, MST_SUCCESS);
}

// VsecMSTDriver is backed by the mst_pciconf kernel module (see
// mstDriverDeviceFromPciDbdf in mft_sdk_discovery.cpp): without it the exact
// driver error is returned before the BDF is even used; with it, opening a
// really discovered BDF must succeed.
TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfVsecMSTDriverModuleState)
{
    if (!isKernelModuleLoaded("mst_pciconf"))
    {
        MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
        MstDevice dev = nullptr;
        MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VsecMSTDriver);
        EXPECT_EQ(status, MST_ERROR_MST_DRIVER_NOT_LOADED);
        return;
    }

    MstPciBDF bdf = {0, 0, 0, 0};
    if (!getFirstDiscoveredPcieBdf(bdf))
    {
        std::cout << "[  SKIPPED ] mst_pciconf loaded but no PCIe device discovered" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VsecMSTDriver);
    EXPECT_EQ(status, MST_SUCCESS) << mstGetInitErrorString();
    if (status == MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
    }
}

// Same contract as above for BAR0MSTDriver, which is backed by mst_pci.
TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfBAR0MSTDriverModuleState)
{
    if (!isKernelModuleLoaded("mst_pci"))
    {
        MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
        MstDevice dev = nullptr;
        MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, BAR0MSTDriver);
        EXPECT_EQ(status, MST_ERROR_MST_DRIVER_NOT_LOADED);
        return;
    }

    MstPciBDF bdf = {0, 0, 0, 0};
    if (!getFirstDiscoveredPcieBdf(bdf))
    {
        std::cout << "[  SKIPPED ] mst_pci loaded but no PCIe device discovered" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, BAR0MSTDriver);
    EXPECT_EQ(status, MST_SUCCESS) << mstGetInitErrorString();
    if (status == MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
    }
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfVsecUserLevelNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VsecUserLevel);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_OPEN_DEVICE);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleByBdfBAR0UserLevelNonexistent)
{
    MstPciBDF bdf = {0xFFFF, 0xFF, 0x1F, 0x7};
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, BAR0UserLevel);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_OPEN_DEVICE);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleWithI2cNullDevice)
{
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(NULL, "some_device", 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleWithI2cNullId)
{
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(&dev, NULL, 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetDeviceHandleWithI2cBothNull)
{
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(NULL, NULL, 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetPcieSubinterfacesNonPcieInterface)
{
    MstDeviceInfo info;
    memset(&info, 0, sizeof(info));
    info.interfaceType = Infiniband;
    MstPcieSubInterfaceInfo* subs = nullptr;
    unsigned int numSubs = 0;
    MstStatus status = mstGetAvailablePCIeSubinterfaces(&info, &subs, &numSubs);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetPcieSubinterfacesUnsupportedProduct)
{
    MstDeviceInfo info;
    memset(&info, 0, sizeof(info));
    info.interfaceType = PCIe;
    info.productType = CPU;
    strncpy(info.deviceIdentifier, "0000:ff:1f.7", MAX_DEVICE_IDENTIFIER_LENGTH - 1);
    MstPcieSubInterfaceInfo* subs = nullptr;
    unsigned int numSubs = 0;
    MstStatus status = mstGetAvailablePCIeSubinterfaces(&info, &subs, &numSubs);
    EXPECT_EQ(status, MST_ERROR_NOT_SUPPORTED);
}

// GPU branch of mstGetAvailablePCIeSubinterfaces: an optional NVML-resolved
// /dev/nvidiaN NvidiaDriver entry, then BAR0MSTDriver when mst_pci is loaded
// or an NvidiaDriver BDF fallback otherwise.
TEST_F(MftSdkDiscoveryNoDeviceTest, GetPcieSubinterfacesGpuProduct)
{
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    if (mstDiscoverAvailableDevices(types, 1, &devices, &numDevices) != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] No PCIe devices discovered" << std::endl;
        return;
    }
    bool mstPciLoaded = isKernelModuleLoaded("mst_pci");
    bool foundGpu = false;
    for (unsigned int i = 0; i < numDevices; i++)
    {
        if (devices[i].productType != GPU)
        {
            continue;
        }
        foundGpu = true;
        MstPcieSubInterfaceInfo* subs = nullptr;
        unsigned int numSubs = 0;
        ASSERT_EQ(mstGetAvailablePCIeSubinterfaces(&devices[i], &subs, &numSubs), MST_SUCCESS);
        ASSERT_GE(numSubs, 1u);
        ASSERT_LE(numSubs, 2u);
        if (numSubs == 2)
        {
            EXPECT_EQ(subs[0].pcieSubInterfaceType, NvidiaDriver);
            EXPECT_EQ(strncmp(subs[0].subInterfaceIdentifier, "/dev/nvidia", strlen("/dev/nvidia")), 0);
        }
        EXPECT_EQ(subs[numSubs - 1].pcieSubInterfaceType, mstPciLoaded ? BAR0MSTDriver : NvidiaDriver);
        EXPECT_STREQ(subs[numSubs - 1].subInterfaceIdentifier, devices[i].deviceIdentifier);
        mstFreePCIeSubInterfaces(subs);
    }
    mstFreeDiscoveredDevices(devices);
    if (!foundGpu)
    {
        std::cout << "[  SKIPPED ] No GPU device discovered" << std::endl;
    }
}

// Switch branch of mstGetAvailablePCIeSubinterfaces: exactly one BAR0 entry
// (BAR0MSTDriver with mst_pci, else BAR0UserLevel) followed by one Vsec entry
// (VsecMSTDriver with mst_pciconf, else VsecUserLevel), all on the device BDF.
TEST_F(MftSdkDiscoveryNoDeviceTest, GetPcieSubinterfacesSwitchProduct)
{
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    if (mstDiscoverAvailableDevices(types, 1, &devices, &numDevices) != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] No PCIe devices discovered" << std::endl;
        return;
    }
    bool mstPciLoaded = isKernelModuleLoaded("mst_pci");
    bool mstPciconfLoaded = isKernelModuleLoaded("mst_pciconf");
    bool foundSwitch = false;
    for (unsigned int i = 0; i < numDevices; i++)
    {
        if (devices[i].productType != Switch)
        {
            continue;
        }
        foundSwitch = true;
        MstPcieSubInterfaceInfo* subs = nullptr;
        unsigned int numSubs = 0;
        ASSERT_EQ(mstGetAvailablePCIeSubinterfaces(&devices[i], &subs, &numSubs), MST_SUCCESS);
        ASSERT_EQ(numSubs, 2u);
        EXPECT_EQ(subs[0].pcieSubInterfaceType, mstPciLoaded ? BAR0MSTDriver : BAR0UserLevel);
        EXPECT_STREQ(subs[0].subInterfaceIdentifier, devices[i].deviceIdentifier);
        EXPECT_EQ(subs[1].pcieSubInterfaceType, mstPciconfLoaded ? VsecMSTDriver : VsecUserLevel);
        EXPECT_STREQ(subs[1].subInterfaceIdentifier, devices[i].deviceIdentifier);
        mstFreePCIeSubInterfaces(subs);
    }
    mstFreeDiscoveredDevices(devices);
    if (!foundSwitch)
    {
        std::cout << "[  SKIPPED ] No Switch device discovered" << std::endl;
    }
}

TEST_F(MftSdkDiscoveryNoDeviceTest, DiscoverRedfishNoDevices)
{
    MstInterfaceType types[] = {Redfish};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    MstStatus status = mstDiscoverAvailableDevices(types, 1, &devices, &numDevices);
    EXPECT_EQ(status, MST_ERROR_NO_AVAILABLE_DEVICES);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, DiscoverNullDiscoveredDevices)
{
    MstInterfaceType types[] = {PCIe};
    unsigned int numDevices = 0;
    MstStatus status = mstDiscoverAvailableDevices(types, 1, NULL, &numDevices);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, DiscoverNullNumDiscoveredDevices)
{
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    MstStatus status = mstDiscoverAvailableDevices(types, 1, &devices, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetLastErrorNullDevice)
{
    const char* err = mstGetLastErrorString(NULL);
    EXPECT_NE(err, nullptr);
    EXPECT_STREQ(err, "MST Device was not initialized");
}

TEST_F(MftSdkDiscoveryNoDeviceTest, GetInitErrorAfterFailedOpen)
{
    MstDevice dev = nullptr;
    mstGetDeviceHandle(&dev, "nonexistent_device_coverage_test");
    const char* initErr = mstGetInitErrorString();
    EXPECT_NE(initErr, nullptr);
    EXPECT_GT(strlen(initErr), 0u);
}

// g_initError (mft_sdk_errors.cpp) is thread_local: an open failure in a
// worker thread must be visible there but never leak into this thread's
// init error string (which stays exactly as it was, empty on a fresh thread).
TEST_F(MftSdkDiscoveryNoDeviceTest, InitErrorStringIsThreadLocal)
{
    const char* bogusDevice = "nonexistent_device_thread_local_test";
    std::string mainErrBefore = mstGetInitErrorString();

    MstStatus threadStatus = MST_SUCCESS;
    std::string threadErr;
    std::thread worker(
      [&]()
      {
          MstDevice dev = nullptr;
          threadStatus = mstGetDeviceHandle(&dev, bogusDevice);
          threadErr = mstGetInitErrorString();
      });
    worker.join();

    EXPECT_EQ(threadStatus, MST_ERROR_FAILED_TO_OPEN_DEVICE);
    EXPECT_NE(threadErr.find(bogusDevice), std::string::npos)
      << "Worker thread should observe its own init error, got: " << threadErr;
    EXPECT_STREQ(mstGetInitErrorString(), mainErrBefore.c_str())
      << "Worker-thread init error leaked into the main thread";
}

TEST_F(MftSdkDiscoveryNoDeviceTest, ReleaseNullHandle)
{
    EXPECT_EQ(mstReleaseDeviceHandle(NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, FreeDiscoveredDevicesNull)
{
    EXPECT_EQ(mstFreeDiscoveredDevices(NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkDiscoveryNoDeviceTest, FreePcieSubInterfacesNull)
{
    EXPECT_EQ(mstFreePCIeSubInterfaces(NULL), MST_ERROR_INVALID_ARGUMENT);
}

// In the standalone build (MFT_SDK_STANDALONE_BUILD, set for every lib the
// unit tests link against) the MftSdk constructor forces MFT_CONFIG_PATH to
// /etc/mft_sdk/mft.conf when unset (setDefaultSdkConfigPath in
// mft_sdk_class.cpp); this runs even when the open itself fails. The
// mstflint-built libmft_sdk.so (which this harness also runs against) does
// not implement the standalone default, so an untouched env var soft-skips.
TEST_F(MftSdkDiscoveryNoDeviceTest, ConfigPathForcedDefaultWhenUnset)
{
    EnvVarGuard envVarGuard("MFT_CONFIG_PATH", "");
    unsetenv("MFT_CONFIG_PATH");
    MstDevice dev = nullptr;
    mstGetDeviceHandle(&dev, "nonexistent_device_config_path_test");
    const char* configPath = std::getenv("MFT_CONFIG_PATH");
    if (configPath == nullptr)
    {
        std::cout << "[  SKIPPED ] SDK does not force a default config path (non-standalone build)" << std::endl;
        return;
    }
    EXPECT_STREQ(configPath, "/etc/mft_sdk/mft.conf");
}

TEST_F(MftSdkDiscoveryNoDeviceTest, ConfigPathPresetValueUntouched)
{
    EnvVarGuard envVarGuard("MFT_CONFIG_PATH", "/tmp/mft_sdk_test_custom.conf");
    MstDevice dev = nullptr;
    mstGetDeviceHandle(&dev, "nonexistent_device_config_path_test");
    EXPECT_STREQ(std::getenv("MFT_CONFIG_PATH"), "/tmp/mft_sdk_test_custom.conf");
}

// ============================================================================
// GROUP B: Requires device (-d flag)
// ============================================================================

TEST_F(MftSdkDiscoveryDeviceTest, DiscoverPcieAndVerifyDeviceInfo)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    MstStatus status = mstDiscoverAvailableDevices(types, 1, &devices, &numDevices);
    ASSERT_EQ(status, MST_SUCCESS);
    ASSERT_GT(numDevices, 0u);

    for (unsigned int i = 0; i < numDevices; i++)
    {
        EXPECT_EQ(devices[i].interfaceType, PCIe);
        EXPECT_NE(devices[i].productType, UnknownProductType);
        EXPECT_GT(strlen(devices[i].deviceIdentifier), 0u);
    }
    mstFreeDiscoveredDevices(devices);
}

TEST_F(MftSdkDiscoveryDeviceTest, DiscoverAndEnumerateSubInterfaces)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstInterfaceType types[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    MstStatus status = mstDiscoverAvailableDevices(types, 1, &devices, &numDevices);
    ASSERT_EQ(status, MST_SUCCESS);

    for (unsigned int i = 0; i < numDevices; i++)
    {
        MstPcieSubInterfaceInfo* subs = nullptr;
        unsigned int numSubs = 0;
        status = mstGetAvailablePCIeSubinterfaces(&devices[i], &subs, &numSubs);
        EXPECT_EQ(status, MST_SUCCESS);
        if (status == MST_SUCCESS)
        {
            EXPECT_GT(numSubs, 0u);
            for (unsigned int j = 0; j < numSubs; j++)
            {
                EXPECT_NE(subs[j].pcieSubInterfaceType, UnknownPCIeSubInterfaceType);
                EXPECT_GT(strlen(subs[j].subInterfaceIdentifier), 0u);
            }
            mstFreePCIeSubInterfaces(subs);
        }
    }
    mstFreeDiscoveredDevices(devices);
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleByBdfVsecUserLevel)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    unsigned int domain = 0, bus = 0, device = 0, func = 0;
    sscanf(g_devicePci.c_str(), "%x:%x:%x.%x", &domain, &bus, &device, &func);
    MstPciBDF bdf = {domain, bus, device, func};

    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, VsecUserLevel);
    if (status == MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
    }
    else
    {
        std::cout << "[     INFO ] VsecUserLevel not available for this device (status=" << status << ")" << std::endl;
    }
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleByBdfBAR0UserLevel)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    unsigned int domain = 0, bus = 0, device = 0, func = 0;
    sscanf(g_devicePci.c_str(), "%x:%x:%x.%x", &domain, &bus, &device, &func);
    MstPciBDF bdf = {domain, bus, device, func};

    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, BAR0UserLevel);
    if (status == MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
    }
    else
    {
        std::cout << "[     INFO ] BAR0UserLevel not available for this device (status=" << status << ")" << std::endl;
    }
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleByBdfAllSubTypes)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    unsigned int domain = 0, bus = 0, device = 0, func = 0;
    sscanf(g_devicePci.c_str(), "%x:%x:%x.%x", &domain, &bus, &device, &func);
    MstPciBDF bdf = {domain, bus, device, func};

    MstPCIeSubInterfaceType subTypes[] = {FWCtl,         VFIO,          NvidiaDriver, VsecMSTDriver,
                                          BAR0MSTDriver, VsecUserLevel, BAR0UserLevel};

    for (auto subType : subTypes)
    {
        MstDevice dev = nullptr;
        MstStatus status = mstGetDeviceHandleByBDF(&dev, bdf, subType);
        if (status == MST_SUCCESS)
        {
            mstReleaseDeviceHandle(dev);
        }
    }
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleByFwctlValid)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleByFwctlDeviceName(&dev, "fwctl0");
    if (status == MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
    }
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleOpenAndRelease)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[     INFO ] Cannot open device " << g_devicePci << " (status=" << status << ")" << std::endl;
        return;
    }
    EXPECT_NE(dev, nullptr);

    status = mstReleaseDeviceHandle(dev);
    EXPECT_EQ(status, MST_SUCCESS);
}

TEST_F(MftSdkDiscoveryDeviceTest, GetDeviceHandleWithI2cSecondary)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }

    // Save original I2C secondary so we can restore after the test,
    // avoiding state pollution for subsequent tests.
    uint8_t origAddr = 0;
    {
        MstDevice tmpDev = nullptr;
        MstStatus s = mstGetDeviceHandle(&tmpDev, g_devicePci.c_str());
        if (s == MST_SUCCESS)
        {
            mstGetI2cSecondary(tmpDev, &origAddr);
            mstReleaseDeviceHandle(tmpDev);
        }
    }

    // Choose an address different from the current one so we can confirm
    // that mstGetDeviceHandleWithI2cSecondary actually sets it.
    uint8_t testAddr = (origAddr != 0x48) ? 0x48 : 0x50;

    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(&dev, g_devicePci.c_str(), testAddr);
    if (status == MST_SUCCESS)
    {
        uint8_t addr = 0;
        EXPECT_EQ(mstGetI2cSecondary(dev, &addr), MST_SUCCESS);
        // The forced I2C secondary address only takes effect when the device is
        // reached over an I2C transport; for PCIe-accessed devices it does not
        // apply and reads back as 0 (testAddr is never 0). Only verify the
        // round-trip when the address was actually applied.
        if (addr != 0)
        {
            EXPECT_EQ(addr, testAddr);
        }
        else
        {
            std::cout << "[  SKIPPED ] Device not accessed over I2C; "
                         "secondary address not applicable"
                      << std::endl;
        }

        mstSetI2cSecondary(dev, origAddr);
        mstReleaseDeviceHandle(dev);
    }
}

TEST_F(MftSdkDiscoveryDeviceTest, DiscoverMultipleInterfaceTypes)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstInterfaceType types[] = {PCIe, Infiniband};
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    MstStatus status = mstDiscoverAvailableDevices(types, 2, &devices, &numDevices);
    if (status == MST_SUCCESS)
    {
        EXPECT_GT(numDevices, 0u);
        mstFreeDiscoveredDevices(devices);
    }
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
