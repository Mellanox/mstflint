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
 * Coverage-focused tests for mft_sdk_hca_caps.cpp.
 *
 * Group A tests do NOT require any Mellanox/NVIDIA hardware.
 * Group B tests need a real device with fwctl -- pass -d <BDF> to enable them.
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// GROUP A: No device required -- null/invalid parameter validation
// ============================================================================

class MftHcaCapsNoDeviceTest : public ::testing::Test
{
};

TEST_F(MftHcaCapsNoDeviceTest, GetCapTypesListNullDevice)
{
    char** types = nullptr;
    unsigned int num = 0;
    EXPECT_EQ(mstGetCapabilityTypesList(NULL, &types, &num), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapTypesListNullArray)
{
    unsigned int num = 0;
    EXPECT_EQ(mstGetCapabilityTypesList(NULL, NULL, &num), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapTypesListNullCount)
{
    char** types = nullptr;
    EXPECT_EQ(mstGetCapabilityTypesList(NULL, &types, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapByTypeNullDevice)
{
    MstHcaCapabilityMetadata meta;
    memset(&meta, 0, sizeof(meta));
    EXPECT_EQ(mstGetCapabilitiesByType(NULL, "cmd_hca_cap", &meta), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapByTypeNullMeta)
{
    EXPECT_EQ(mstGetCapabilitiesByType(NULL, "cmd_hca_cap", NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, InitCapMapNullDevice)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstInitHcaCapabilityMap(NULL, "cmd_hca_cap", &map), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, InitCapMapNullType)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstInitHcaCapabilityMap(NULL, NULL, &map), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, InitCapMapNullMap)
{
    EXPECT_EQ(mstInitHcaCapabilityMap(NULL, "cmd_hca_cap", NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, QueryCapNullDevice)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstQueryHcaCapability(NULL, "cmd_hca_cap", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                    MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO),
              MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, SetCapNullDevice)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstSetHcaCapability(NULL, "cmd_hca_cap", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                  MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO),
              MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapValueNullDevice)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    uint32_t val = 0;
    EXPECT_EQ(mstGetCapabilityValue(NULL, &map, "cap", &val), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, GetCapValueNullName)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    uint32_t val = 0;
    EXPECT_EQ(mstGetCapabilityValue(NULL, &map, NULL, &val), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, SetCapValueNullDevice)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstSetCapabilityValue(NULL, &map, "cap", 0), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, SetCapValueNullName)
{
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    EXPECT_EQ(mstSetCapabilityValue(NULL, &map, NULL, 0), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, SetCapValueNullMap)
{
    EXPECT_EQ(mstSetCapabilityValue(NULL, NULL, "cap", 0), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, FreeCapMapNull)
{
    EXPECT_EQ(mstFreeHcaCapabilityMap(NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, FreeCapArrayNull)
{
    EXPECT_EQ(mstFreeHcaCapabilitiesArray(NULL, 0), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, FreeCapMetadataNull)
{
    EXPECT_EQ(mstFreeHcaCapabilitiesMetadata(NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsNoDeviceTest, FreeCapMetadataWithNullFields)
{
    MstHcaCapabilityMetadata meta;
    memset(&meta, 0, sizeof(meta));
    meta.fields = nullptr;
    meta.numberOfFields = 0;
    EXPECT_EQ(mstFreeHcaCapabilitiesMetadata(&meta), MST_SUCCESS);
}

// ============================================================================
// GROUP B: Requires device (-d flag) -- typically fwctl
// ============================================================================

class MftHcaCapsDeviceTest : public ::testing::Test
{
protected:
    MstDevice mstDevice = nullptr;
    bool hasDevice = false;

    void SetUp() override
    {
        if (g_devicePci.empty())
        {
            return;
        }
        MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
        if (status == MST_SUCCESS)
        {
            hasDevice = true;
        }
    }

    void TearDown() override
    {
        if (mstDevice)
        {
            mstReleaseDeviceHandle(mstDevice);
        }
    }
};

TEST_F(MftHcaCapsDeviceTest, QueryMultipleCapTypes)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    char** capTypes = nullptr;
    unsigned int numTypes = 0;
    MstStatus status = mstGetCapabilityTypesList(mstDevice, &capTypes, &numTypes);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot get capability types" << std::endl;
        return;
    }
    ASSERT_GT(numTypes, 0u);

    for (unsigned int i = 0; i < numTypes; i++)
    {
        MstHcaCapabilityMap map;
        status = mstInitHcaCapabilityMap(mstDevice, capTypes[i], &map);
        EXPECT_EQ(status, MST_SUCCESS) << "Failed for type: " << capTypes[i];
        if (status == MST_SUCCESS)
        {
            status = mstQueryHcaCapability(mstDevice, capTypes[i], &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                           MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
            EXPECT_EQ(status, MST_SUCCESS) << "Query failed for type: " << capTypes[i];
            mstFreeHcaCapabilityMap(&map);
        }
    }
    mstFreeHcaCapabilitiesArray(capTypes, numTypes);
}

TEST_F(MftHcaCapsDeviceTest, QueryCapModeMax)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_MAX, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    EXPECT_EQ(status, MST_SUCCESS);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, GetCapabilitiesByMultipleTypes)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    char** capTypes = nullptr;
    unsigned int numTypes = 0;
    MstStatus status = mstGetCapabilityTypesList(mstDevice, &capTypes, &numTypes);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot get capability types" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < numTypes; i++)
    {
        MstHcaCapabilityMetadata meta;
        memset(&meta, 0, sizeof(meta));
        status = mstGetCapabilitiesByType(mstDevice, capTypes[i], &meta);
        EXPECT_EQ(status, MST_SUCCESS) << "Failed for type: " << capTypes[i];
        if (status == MST_SUCCESS)
        {
            EXPECT_GT(meta.numberOfFields, 0u) << "No fields for type: " << capTypes[i];
            mstFreeHcaCapabilitiesMetadata(&meta);
        }
    }
    mstFreeHcaCapabilitiesArray(capTypes, numTypes);
}

TEST_F(MftHcaCapsDeviceTest, SetAndGetCapabilityValue)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }

    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    ASSERT_EQ(status, MST_SUCCESS);

    if (map.numberOfCapabilities > 0)
    {
        const char* capName = map.capabilities[0].capabilityName;
        uint32_t origVal = 0;
        status = mstGetCapabilityValue(mstDevice, &map, capName, &origVal);
        EXPECT_EQ(status, MST_SUCCESS);

        status = mstSetCapabilityValue(mstDevice, &map, capName, origVal);
        EXPECT_EQ(status, MST_SUCCESS);
    }
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, InvalidCapabilityType)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstHcaCapabilityMetadata meta;
    memset(&meta, 0, sizeof(meta));
    MstStatus status = mstGetCapabilitiesByType(mstDevice, "nonexistent_cap_type_xyz", &meta);
    EXPECT_NE(status, MST_SUCCESS);
}

TEST_F(MftHcaCapsDeviceTest, InvalidCapabilityName)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }

    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    ASSERT_EQ(status, MST_SUCCESS);

    uint32_t val = 0;
    status = mstGetCapabilityValue(mstDevice, &map, "nonexistent_cap_name_xyz", &val);
    EXPECT_NE(status, MST_SUCCESS);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, QueryCapNullCapType)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    MstStatus status = mstQueryHcaCapability(mstDevice, NULL, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                             MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, QueryCapNullMap)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstStatus status = mstQueryHcaCapability(mstDevice, "cmd_hca_cap", NULL, MST_CAPABILITY_MODE_CURRENT, 0,
                                             MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, SetCapNullCapType)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    MstStatus status = mstSetHcaCapability(mstDevice, NULL, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                           MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, SetCapNullMap)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstStatus status = mstSetHcaCapability(mstDevice, "cmd_hca_cap", NULL, MST_CAPABILITY_MODE_CURRENT, 0,
                                           MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, InitCapMapNullType)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstHcaCapabilityMap map;
    memset(&map, 0, sizeof(map));
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, NULL, &map);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, InitCapMapNullMap)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, "cmd_hca_cap", NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, GetCapValueNullCapName)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    uint32_t val = 0;
    status = mstGetCapabilityValue(mstDevice, &map, NULL, &val);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, SetCapValueNullCapName)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    status = mstSetCapabilityValue(mstDevice, &map, NULL, 0);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, SetCapValueNullMap)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    MstStatus status = mstSetCapabilityValue(mstDevice, NULL, "cap", 0);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftHcaCapsDeviceTest, QueryWithVhcaIdType)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_VHCA_ID, MST_OTHER_FUNCTION_NO);
    // FW only samples function_id/function_id_type when other_function is set, so a
    // VHCA_ID-typed self-query must succeed exactly like the FUNCTION_INDEX one.
    EXPECT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, SetHcaCapabilityWriteBack)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    ASSERT_EQ(status, MST_SUCCESS);

    // Mark every capability to be written back with its just-queried value, so the set
    // is a no-op that never modifies device state.
    std::vector<uint32_t> queriedValues(map.numberOfCapabilities);
    for (unsigned int i = 0; i < map.numberOfCapabilities; i++)
    {
        queriedValues[i] = map.capabilities[i].value;
    }
    for (unsigned int i = 0; i < map.numberOfCapabilities; i++)
    {
        status = mstSetCapabilityValue(mstDevice, &map, map.capabilities[i].capabilityName, queriedValues[i]);
        ASSERT_EQ(status, MST_SUCCESS) << "Capability: " << map.capabilities[i].capabilityName;
    }

    status = mstSetHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                 MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    if (status != MST_SUCCESS)
    {
        // With valid arguments the only failure the SDK reports is the FW/fwctl driver
        // rejecting SET_HCA_CAP (unsupported); the device state is untouched in that case.
        EXPECT_EQ(status, MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES);
        std::cout << "[  SKIPPED ] Device/FW rejected set capability: " << mstGetLastErrorString(mstDevice)
                  << std::endl;
        mstFreeHcaCapabilityMap(&map);
        return;
    }

    // Re-query and verify the write-back left every capability value unchanged.
    MstHcaCapabilityMap requeriedMap;
    status = mstInitHcaCapabilityMap(mstDevice, capType, &requeriedMap);
    ASSERT_EQ(status, MST_SUCCESS);
    status = mstQueryHcaCapability(mstDevice, capType, &requeriedMap, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    ASSERT_EQ(status, MST_SUCCESS);
    ASSERT_EQ(requeriedMap.numberOfCapabilities, map.numberOfCapabilities);
    for (unsigned int i = 0; i < map.numberOfCapabilities; i++)
    {
        EXPECT_EQ(requeriedMap.capabilities[i].value, queriedValues[i])
          << "Capability changed: " << map.capabilities[i].capabilityName;
    }
    mstFreeHcaCapabilityMap(&requeriedMap);
    mstFreeHcaCapabilityMap(&map);
}

TEST_F(MftHcaCapsDeviceTest, QueryOtherFunctionVf)
{
    if (!hasDevice)
    {
        std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl;
        return;
    }
    // Another function can only be targeted when SR-IOV VFs are enabled on the PF under test.
    unsigned int numVfs = 0;
    std::ifstream numVfsFile("/sys/bus/pci/devices/" + g_devicePci + "/sriov_numvfs");
    if (!(numVfsFile >> numVfs) || numVfs == 0)
    {
        std::cout << "[  SKIPPED ] No VF enabled on " << g_devicePci << std::endl;
        return;
    }
    const char* capType = "cmd_hca_cap";
    MstHcaCapabilityMap map;
    MstStatus status = mstInitHcaCapabilityMap(mstDevice, capType, &map);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cannot init capability map" << std::endl;
        return;
    }
    // Function index 0 is the PF itself; its first VF is function index 1.
    status = mstQueryHcaCapability(mstDevice, capType, &map, MST_CAPABILITY_MODE_CURRENT, 1,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_YES);
    EXPECT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    mstFreeHcaCapabilityMap(&map);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
