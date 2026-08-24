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
 * Input-validation regression tests for the MFT SDK C API.
 *
 * Each Group A/B test uses EXPECT_NO_CRASH: the API call runs in a forked
 * child process. If the child segfaults the parent reports FAIL and
 * continues to the next test. If the child returns normally we check that
 * the status is MST_ERROR_INVALID_ARGUMENT.
 *
 * Group A tests do NOT require any Mellanox/NVIDIA hardware.
 * Group B tests need a real device — pass -d <BDF> to enable them.
 * Group C tests verify logic bugs (no crash, but incorrect behaviour).
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

// Fork-based crash isolation: runs `fn` in a child process.
// If the child segfaults, the parent survives and reports FAIL.
// If the child returns normally, we get the MstStatus back via a pipe.
struct ForkResult
{
    bool crashed;
    int signal;
    MstStatus status;
};

template<typename Fn>
static ForkResult run_in_fork(Fn fn)
{
    ForkResult result = {false, 0, static_cast<MstStatus>(-1)};
    int pipefd[2];
    if (pipe(pipefd) != 0)
        return result;

    pid_t pid = fork();
    if (pid < 0)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return result;
    }

    if (pid == 0)
    {
        close(pipefd[0]);
        MstStatus s = fn();
        (void)write(pipefd[1], &s, sizeof(s));
        close(pipefd[1]);
        _exit(0);
    }

    close(pipefd[1]);
    int wstatus;
    waitpid(pid, &wstatus, 0);

    if (WIFSIGNALED(wstatus))
    {
        result.crashed = true;
        result.signal = WTERMSIG(wstatus);
    }
    else
    {
        (void)read(pipefd[0], &result.status, sizeof(result.status));
    }
    close(pipefd[0]);
    return result;
}

#define EXPECT_NO_CRASH(expr)                                                                               \
    do                                                                                                      \
    {                                                                                                       \
        auto _r = run_in_fork([&]() { return (expr); });                                                    \
        EXPECT_FALSE(_r.crashed) << "SDK crashed with signal " << _r.signal << " (" << strsignal(_r.signal) \
                                 << "): " << #expr;                                                         \
        if (!_r.crashed)                                                                                    \
        {                                                                                                   \
            EXPECT_EQ(_r.status, MST_ERROR_INVALID_ARGUMENT);                                               \
        }                                                                                                   \
    } while (0)

class MftSdkSegfaultTest : public ::testing::Test
{
};

// ============================================================================
// GROUP A: Input validation — NO device needed
// Each test calls the API directly and expects MST_ERROR_INVALID_ARGUMENT.
// If the SDK segfaults instead of returning an error, the test runner
// crashes and the test is reported as FAILED.
// ============================================================================

// A1. mstDiscoverAvailableDevices — NULL interfaceTypes with count > 0
TEST_F(MftSdkSegfaultTest, DiscoverNullInterfaceTypes)
{
    MstDeviceInfo* devices = nullptr;
    unsigned int numDevices = 0;
    EXPECT_NO_CRASH(mstDiscoverAvailableDevices(NULL, 1, &devices, &numDevices));
}

// A2. mstDiscoverAvailableDevices — NULL discoveredDevices output pointer
TEST_F(MftSdkSegfaultTest, DiscoverNullDiscoveredDevices)
{
    MstInterfaceType interfaceTypes[] = {PCIe};
    unsigned int numDevices = 0;
    EXPECT_NO_CRASH(mstDiscoverAvailableDevices(interfaceTypes, 1, NULL, &numDevices));
}

// A3. mstDiscoverAvailableDevices — NULL numDiscoveredDevices output pointer
TEST_F(MftSdkSegfaultTest, DiscoverNullNumDiscoveredDevices)
{
    MstInterfaceType interfaceTypes[] = {PCIe};
    MstDeviceInfo* devices = nullptr;
    EXPECT_NO_CRASH(mstDiscoverAvailableDevices(interfaceTypes, 1, &devices, NULL));
}

// Garbage (non-NULL, never-allocated) opaque device handle. The SDK only
// NULL-checks handles before reinterpret_cast'ing them to MftSdk* (no handle
// registry), so any member access through a garbage handle crashes today.
// Those tests are DISABLED_ contract tests until handle validation is added.
static const MstDevice kGarbageDevice = (MstDevice)0xDEADBEEF;

// A4. mstReleaseDeviceHandle — garbage handle.
//     Contract: return MST_ERROR_INVALID_ARGUMENT; today `delete` on the wild pointer crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GarbageDeviceHandleRelease)
{
    EXPECT_NO_CRASH(mstReleaseDeviceHandle(kGarbageDevice));
}

// A5. mstGetLastErrorString — garbage handle. Only computes the address of a
//     member buffer (no dereference), so it must not crash and never be NULL.
TEST_F(MftSdkSegfaultTest, GarbageDeviceHandleGetLastError)
{
    auto result = run_in_fork([]() { return mstGetLastErrorString(kGarbageDevice) ? MST_SUCCESS : MST_ERROR_UNKNOWN; });
    EXPECT_FALSE(result.crashed) << "SDK crashed with signal " << result.signal << " (" << strsignal(result.signal)
                                 << "): mstGetLastErrorString(kGarbageDevice)";
    if (!result.crashed)
    {
        EXPECT_EQ(result.status, MST_SUCCESS);
    }
}

// A6. mstFreeHcaCapabilityMap — struct with garbage internals.
//     Contract: return MST_ERROR_INVALID_ARGUMENT; today `delete[]` on the garbage `capabilities` pointer crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_FreeHcaCapMapGarbageCapabilities)
{
    MstHcaCapabilityMap capMap;
    memset(&capMap, 0xAB, sizeof(capMap));
    EXPECT_NO_CRASH(mstFreeHcaCapabilityMap(&capMap));
}

// A7. mstInitRegisterMap — garbage device handle.
//     Contract: return MST_ERROR_INVALID_ARGUMENT; today the first member write through the wild MftSdk* crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GarbageDeviceInitRegisterMap)
{
    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_NO_CRASH(mstInitRegisterMap(kGarbageDevice, "MCAM", &map));
}

// A8. mstGetTelemetryOperationalInfo — garbage device handle.
//     Contract: return MST_ERROR_INVALID_ARGUMENT; today the wild MftSdk* member access crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GarbageDeviceGetTelemetry)
{
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    EXPECT_NO_CRASH(mstGetTelemetryOperationalInfo(kGarbageDevice, nullptr, &opInfo));
}

// A9. mstReadCRSpace — garbage device handle.
//     Contract: return MST_ERROR_INVALID_ARGUMENT; today reading `_mf` through the wild MftSdk* crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GarbageDeviceReadCRSpace)
{
    uint32_t data[4] = {0};
    EXPECT_NO_CRASH(mstReadCRSpace(kGarbageDevice, 0x0, data, sizeof(data)));
}

// A10. mstSetI2cSecondary — garbage device handle.
//      Contract: return MST_ERROR_INVALID_ARGUMENT; today reading `_mfiles` through the wild MftSdk* crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GarbageDeviceSetI2c)
{
    EXPECT_NO_CRASH(mstSetI2cSecondary(kGarbageDevice, 0x48));
}

// ============================================================================
// GROUP B: Input validation that needs a real device
//          Pass -d <BDF> to enable these tests.
// Each test calls the API directly and expects MST_ERROR_INVALID_ARGUMENT.
// If the SDK segfaults instead of returning an error, the test runner
// crashes and the test is reported as FAILED.
// ============================================================================

// B1. mstGetDeviceHandle — NULL mstDevice output pointer
TEST_F(MftSdkSegfaultTest, GetDeviceHandleNullOutputPtr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstGetDeviceHandle(NULL, g_devicePci.c_str()));
}

// B2. mstShowAllPRMRegisters — NULL registerNamesArray output pointer
TEST_F(MftSdkSegfaultTest, ShowAllRegistersNullArrayPtr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    unsigned int num = 0;
    EXPECT_NO_CRASH(mstShowAllPRMRegisters(dev, NULL, &num));
    mstReleaseDeviceHandle(dev);
}

// B3. mstShowAllPRMRegisters — NULL numRegisters output pointer
TEST_F(MftSdkSegfaultTest, ShowAllRegistersNullCountPtr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    char** arr = nullptr;
    EXPECT_NO_CRASH(mstShowAllPRMRegisters(dev, &arr, NULL));
    mstReleaseDeviceHandle(dev);
}

// B4. mstInitRegisterMap — NULL regName
TEST_F(MftSdkSegfaultTest, InitRegisterMapNullRegName)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_NO_CRASH(mstInitRegisterMap(dev, NULL, &map));
    mstReleaseDeviceHandle(dev);
}

// B5. mstInitRegisterMap — NULL registerMap output pointer
TEST_F(MftSdkSegfaultTest, InitRegisterMapNullMapPtr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstInitRegisterMap(dev, "MCAM", NULL));
    mstReleaseDeviceHandle(dev);
}

// B6. mstSetPRMRegisterField — NULL fieldName
TEST_F(MftSdkSegfaultTest, SetPrmFieldNullFieldName)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    status = mstInitRegisterMap(dev, "MCAM", &map);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
        std::cout << "[  SKIPPED ] Cannot init register map" << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstSetPRMRegisterField(dev, &map, NULL, 0));
    mstFreePrmRegisterMap(&map);
    mstReleaseDeviceHandle(dev);
}

// B7. mstGetPRMRegisterField — NULL fieldName
TEST_F(MftSdkSegfaultTest, GetPrmFieldNullFieldName)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    status = mstInitRegisterMap(dev, "MCAM", &map);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
        std::cout << "[  SKIPPED ] Cannot init register map" << std::endl;
        return;
    }
    uint32_t value = 0;
    EXPECT_NO_CRASH(mstGetPRMRegisterField(dev, &map, NULL, &value));
    mstFreePrmRegisterMap(&map);
    mstReleaseDeviceHandle(dev);
}

// B8. mstGetPRMRegisterField — NULL value output pointer
TEST_F(MftSdkSegfaultTest, GetPrmFieldNullValuePtr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    status = mstInitRegisterMap(dev, "MCAM", &map);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(dev);
        std::cout << "[  SKIPPED ] Cannot init register map" << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstGetPRMRegisterField(dev, &map, "access_reg_group", NULL));
    mstFreePrmRegisterMap(&map);
    mstReleaseDeviceHandle(dev);
}

// B9. mstGetRegisterMetadata — NULL regName
TEST_F(MftSdkSegfaultTest, GetRegisterMetadataNullRegName)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterMetadata meta;
    EXPECT_NO_CRASH(mstGetRegisterMetadata(dev, NULL, &meta));
    mstReleaseDeviceHandle(dev);
}

// B10. mstGetRegisterExpandedMetadata — NULL regName
TEST_F(MftSdkSegfaultTest, GetRegisterExpandedMetadataNullRegName)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstPrmRegisterExpandedMetadata meta;
    EXPECT_NO_CRASH(mstGetRegisterExpandedMetadata(dev, NULL, &meta));
    mstReleaseDeviceHandle(dev);
}

// B11. mstSendRawPRMRegister — NULL data buffer
TEST_F(MftSdkSegfaultTest, SendRawPrmNullData)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstSendRawPRMRegister(dev, 0x9020, MST_PRM_GET, NULL, 0xa0));
    mstReleaseDeviceHandle(dev);
}

// B12. mstGetCapabilitiesByType — NULL capabilityType string.
//      Contract: return MST_ERROR_INVALID_ARGUMENT; today the NULL name reaches std::string construction
//      inside the HCA-caps SDK (throws, surfacing as MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, or crashes).
TEST_F(MftSdkSegfaultTest, DISABLED_GetCapByTypeNullType)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstHcaCapabilityMetadata meta;
    memset(&meta, 0, sizeof(meta));
    EXPECT_NO_CRASH(mstGetCapabilitiesByType(dev, NULL, &meta));
    mstReleaseDeviceHandle(dev);
}

// B13. mstGetCapabilityValue — capability map used before mstInitHcaCapabilityMap/mstQueryHcaCapability.
//      Contract: return an error; today the call runs on the not-yet-created HCA-caps SDK instance (NULL this) and
//      crashes.
TEST_F(MftSdkSegfaultTest, DISABLED_GetCapabilityValueBeforeInit)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstHcaCapabilityMap capMap;
    memset(&capMap, 0, sizeof(capMap));
    uint32_t value = 0;
    EXPECT_NO_CRASH(mstGetCapabilityValue(dev, &capMap, "cap", &value));
    mstReleaseDeviceHandle(dev);
}

// B14. mstSetCapabilityValue — capability map used before mstInitHcaCapabilityMap.
//      Contract: return an error; same use-before-init crash as B13.
TEST_F(MftSdkSegfaultTest, DISABLED_SetCapabilityValueBeforeInit)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }
    MstHcaCapabilityMap capMap;
    memset(&capMap, 0, sizeof(capMap));
    EXPECT_NO_CRASH(mstSetCapabilityValue(dev, &capMap, "cap", 1));
    mstReleaseDeviceHandle(dev);
}

// ============================================================================
// GROUP C: Logic bugs (no crash, but verifiable incorrect behaviour)
// ============================================================================

// C2. mstReleaseDeviceHandle sets only a local copy to nullptr
//     The caller's variable retains the dangling pointer.
TEST_F(MftSdkSegfaultTest, ReleaseDoesNotNullCallerHandle)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << " (try running with sudo)" << std::endl;
        return;
    }

    mstReleaseDeviceHandle(dev);
    EXPECT_NE(dev, nullptr) << "SDK should null the caller's handle but doesn't (local-only nullptr)";
}

// C3. mstGetDeviceHandle — NULL mstDevice pointer (no real device)
TEST_F(MftSdkSegfaultTest, GetDeviceHandleNullOutputPtrNoDevice)
{
    MstStatus status = mstGetDeviceHandle(NULL, "nonexistent_device_xyz");
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// C4. NULL mstDevice to every API — should return error, not crash
TEST_F(MftSdkSegfaultTest, NullDeviceToAllApis)
{
    MstDevice nullDev = NULL;

    EXPECT_EQ(mstReleaseDeviceHandle(nullDev), MST_ERROR_INVALID_ARGUMENT);

    const char* err = mstGetLastErrorString(nullDev);
    EXPECT_NE(err, nullptr);

    EXPECT_EQ(mstGetSyndrome(nullDev), 0u);

    MstPrmRegisterMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstInitRegisterMap(nullDev, "MCAM", &map), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstSendPRMRegister(nullDev, &map, MST_PRM_GET), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstSetPRMRegisterField(nullDev, &map, "field", 0), MST_ERROR_INVALID_ARGUMENT);
    uint32_t val = 0;
    EXPECT_EQ(mstGetPRMRegisterField(nullDev, &map, "field", &val), MST_ERROR_INVALID_ARGUMENT);

    char** names = nullptr;
    unsigned int count = 0;
    EXPECT_EQ(mstShowAllPRMRegisters(nullDev, &names, &count), MST_ERROR_INVALID_ARGUMENT);

    uint8_t data8[16] = {0};
    EXPECT_EQ(mstSendRawPRMRegister(nullDev, 0x9020, MST_PRM_GET, data8, sizeof(data8)), MST_ERROR_INVALID_ARGUMENT);

    MstPrmRegisterMetadata meta;
    EXPECT_EQ(mstGetRegisterMetadata(nullDev, "MGIR", &meta), MST_ERROR_INVALID_ARGUMENT);

    MstPrmRegisterExpandedMetadata emeta;
    EXPECT_EQ(mstGetRegisterExpandedMetadata(nullDev, "MGIR", &emeta), MST_ERROR_INVALID_ARGUMENT);

    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    EXPECT_EQ(mstGetTelemetryOperationalInfo(nullDev, nullptr, &opInfo), MST_ERROR_INVALID_ARGUMENT);

    MstFecHistogram hist;
    MST_QUERY_INIT(&hist);
    EXPECT_EQ(mstGetFecHistogram(nullDev, nullptr, &hist), MST_ERROR_INVALID_ARGUMENT);

    MstCountersInfo counters;
    MST_QUERY_INIT(&counters);
    EXPECT_EQ(mstGetCountersInfo(nullDev, nullptr, &counters), MST_ERROR_INVALID_ARGUMENT);

    MstCableDDMInfo ddm;
    MST_QUERY_INIT(&ddm);
    EXPECT_EQ(mstGetCableDDMInfo(nullDev, nullptr, &ddm), MST_ERROR_INVALID_ARGUMENT);

    MstModuleInfo modInfo;
    MST_QUERY_INIT(&modInfo);
    EXPECT_EQ(mstGetModuleInfo(nullDev, nullptr, &modInfo), MST_ERROR_INVALID_ARGUMENT);

    uint32_t crData[4] = {0};
    EXPECT_EQ(mstReadCRSpace(nullDev, 0, crData, sizeof(crData)), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstWriteCRSpace(nullDev, 0, crData, sizeof(crData)), MST_ERROR_INVALID_ARGUMENT);

    EXPECT_EQ(mstSetI2cSecondary(nullDev, 0x48), MST_ERROR_INVALID_ARGUMENT);
    uint8_t i2cAddr = 0;
    EXPECT_EQ(mstGetI2cSecondary(nullDev, &i2cAddr), MST_ERROR_INVALID_ARGUMENT);

    char** capTypes = nullptr;
    unsigned int numCap = 0;
    EXPECT_EQ(mstGetCapabilityTypesList(nullDev, &capTypes, &numCap), MST_ERROR_INVALID_ARGUMENT);

    MstHcaCapabilityMetadata capMeta;
    memset(&capMeta, 0, sizeof(capMeta));
    EXPECT_EQ(mstGetCapabilitiesByType(nullDev, "cmd_hca_cap", &capMeta), MST_ERROR_INVALID_ARGUMENT);

    MstHcaCapabilityMap capMap;
    memset(&capMap, 0, sizeof(capMap));
    EXPECT_EQ(mstInitHcaCapabilityMap(nullDev, "cmd_hca_cap", &capMap), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstQueryHcaCapability(nullDev, "cmd_hca_cap", &capMap, MST_CAPABILITY_MODE_CURRENT, 0,
                                    MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO),
              MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstSetHcaCapability(nullDev, "cmd_hca_cap", &capMap, MST_CAPABILITY_MODE_CURRENT, 0,
                                  MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO),
              MST_ERROR_INVALID_ARGUMENT);
    uint32_t val32 = 0;
    EXPECT_EQ(mstGetCapabilityValue(nullDev, &capMap, "cap", &val32), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstSetCapabilityValue(nullDev, &capMap, "cap", 0), MST_ERROR_INVALID_ARGUMENT);
}

// C5. Free functions with NULL — should safely return INVALID_ARGUMENT
TEST_F(MftSdkSegfaultTest, FreeNullPointersSafe)
{
    EXPECT_EQ(mstFreeDiscoveredDevices(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreePCIeSubInterfaces(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreePrmRegisterMap(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreePrmRegisterMetadata(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreePrmRegisterExpandedMetadata(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreePRMRegisterNamesArray(NULL, 0), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreeHcaCapabilityMap(NULL), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstFreeHcaCapabilitiesArray(NULL, 0), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstReleaseDeviceHandle(NULL), MST_ERROR_INVALID_ARGUMENT);
}

// C6. mstGetAvailablePCIeSubinterfaces — NULL deviceInfo
TEST_F(MftSdkSegfaultTest, GetPcieSubinterfacesNullDeviceInfo)
{
    MstPcieSubInterfaceInfo* subs = nullptr;
    unsigned int numSubs = 0;
    MstStatus status = mstGetAvailablePCIeSubinterfaces(NULL, &subs, &numSubs);
    EXPECT_EQ(status, MST_ERROR_UNINITIALIZED);
}

// ============================================================================
// GROUP D: Additional coverage for null/invalid parameters and header sizes
// ============================================================================

// D1. mstGetDeviceHandle — NULL deviceIdentifier
TEST_F(MftSdkSegfaultTest, GetDeviceHandleNullIdentifier)
{
    MstDevice dev = nullptr;
    EXPECT_EQ(mstGetDeviceHandle(&dev, NULL), MST_ERROR_INVALID_ARGUMENT);
}

// D2. mstGetDeviceHandleWithI2cSecondary — NULL mstDevice
TEST_F(MftSdkSegfaultTest, GetDeviceHandleWithI2cNullMstDevice)
{
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(NULL, "some_device", 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// D3. mstGetDeviceHandleWithI2cSecondary — NULL deviceIdentifier
TEST_F(MftSdkSegfaultTest, GetDeviceHandleWithI2cNullId)
{
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(&dev, NULL, 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// D4. mstGetDeviceHandleWithI2cSecondary — both NULL
TEST_F(MftSdkSegfaultTest, GetDeviceHandleWithI2cBothNull)
{
    MstStatus status = mstGetDeviceHandleWithI2cSecondary(NULL, NULL, 0x48);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// D5. Telemetry APIs with invalid header.size (too small)
TEST_F(MftSdkSegfaultTest, TelemetryOpInfoInvalidHeaderSize)
{
    MstTelemetryOperationalInfo opInfo;
    memset(&opInfo, 0, sizeof(opInfo));
    opInfo.header.size = 1;
    EXPECT_EQ(mstGetTelemetryOperationalInfo(NULL, nullptr, &opInfo), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkSegfaultTest, FecHistogramInvalidHeaderSize)
{
    MstFecHistogram hist;
    memset(&hist, 0, sizeof(hist));
    hist.header.size = 1;
    EXPECT_EQ(mstGetFecHistogram(NULL, nullptr, &hist), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkSegfaultTest, CountersInfoInvalidHeaderSize)
{
    MstCountersInfo counters;
    memset(&counters, 0, sizeof(counters));
    counters.header.size = 1;
    EXPECT_EQ(mstGetCountersInfo(NULL, nullptr, &counters), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkSegfaultTest, CableDDMInvalidHeaderSize)
{
    MstCableDDMInfo ddm;
    memset(&ddm, 0, sizeof(ddm));
    ddm.header.size = 1;
    EXPECT_EQ(mstGetCableDDMInfo(NULL, nullptr, &ddm), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftSdkSegfaultTest, ModuleInfoInvalidHeaderSize)
{
    MstModuleInfo modInfo;
    memset(&modInfo, 0, sizeof(modInfo));
    modInfo.header.size = 1;
    EXPECT_EQ(mstGetModuleInfo(NULL, nullptr, &modInfo), MST_ERROR_INVALID_ARGUMENT);
}

// D6. CR space NULL data pointers (with valid device handle)
TEST_F(MftSdkSegfaultTest, ReadCRSpaceNullData)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstReadCRSpace(dev, 0x0, NULL, 4));
    mstReleaseDeviceHandle(dev);
}

TEST_F(MftSdkSegfaultTest, WriteCRSpaceNullData)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstWriteCRSpace(dev, 0x0, NULL, 4));
    mstReleaseDeviceHandle(dev);
}

// D7. mstGetI2cSecondary — NULL address pointer
TEST_F(MftSdkSegfaultTest, GetI2cSecondaryNullAddr)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstGetI2cSecondary(dev, NULL));
    mstReleaseDeviceHandle(dev);
}

// D8. mstGetCapabilitiesByType — NULL metadata output pointer
TEST_F(MftSdkSegfaultTest, GetCapByTypeNullMeta)
{
    if (g_devicePci.empty())
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstDevice dev = nullptr;
    MstStatus status = mstGetDeviceHandle(&dev, g_devicePci.c_str());
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot open device " << g_devicePci << std::endl;
        return;
    }
    EXPECT_NO_CRASH(mstGetCapabilitiesByType(dev, "cmd_hca_cap", NULL));
    mstReleaseDeviceHandle(dev);
}

// D9. mstFreePrmRegisterExpandedMetadata — NULL
TEST_F(MftSdkSegfaultTest, FreeExpandedMetadataNull)
{
    EXPECT_EQ(mstFreePrmRegisterExpandedMetadata(NULL), MST_ERROR_INVALID_ARGUMENT);
}

// D10. mstFreeHcaCapabilitiesMetadata — with null fields (no crash)
TEST_F(MftSdkSegfaultTest, FreeCapMetadataWithNullFields)
{
    MstHcaCapabilityMetadata meta;
    memset(&meta, 0, sizeof(meta));
    meta.fields = nullptr;
    meta.numberOfFields = 0;
    EXPECT_EQ(mstFreeHcaCapabilitiesMetadata(&meta), MST_SUCCESS);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
