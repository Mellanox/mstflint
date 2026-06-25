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

#pragma once

#ifndef MFT_SDK_HCA_CAPS_H
#define MFT_SDK_HCA_CAPS_H

#include <stdbool.h>
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>
#include <mft_sdk/mft_sdk_reg_access.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MST_MAX_CAP_NAME_SIZE 128

    /**
     * @brief HCA capability mode.
     */
    typedef enum MstCapabilityMode_t
    {
        MST_CAPABILITY_MODE_MAX = 0x0,
        MST_CAPABILITY_MODE_CURRENT = 0x1,
    } MstCapabilityMode;

    /**
     * @brief Function identifier type used when querying or setting HCA capabilities.
     */
    typedef enum MstFunctionIdType_t
    {
        MST_FUNCTION_ID_TYPE_FUNCTION_INDEX = 0x0,
        MST_FUNCTION_ID_TYPE_VHCA_ID = 0x1,
    } MstFunctionIdType;

    /**
     * @brief Indicates whether the HCA capability operation targets another function.
     */
    typedef enum MstOtherFunction_t
    {
        MST_OTHER_FUNCTION_NO = 0x0,
        MST_OTHER_FUNCTION_YES = 0x1,
    } MstOtherFunction;

    /**
     * @brief Metadata describing a single HCA capability field.
     */
    typedef struct MstHcaCapabilityFieldMetadata_t
    {
        char name[MST_MAX_CAP_NAME_SIZE]; /**< Capability field name. */
        uint32_t address;                 /**< Field address within the capability layout. */
        uint32_t bitOffset;               /**< Bit offset of the field. */
        uint32_t bitSize;                 /**< Field size in bits. */
        MstPrmAccessType accessType;      /**< Field access type. */
    } MstHcaCapabilityFieldMetadata;

    /**
     * @brief Metadata describing all fields for an HCA capability type.
     */
    typedef struct MstHcaCapabilityMetadata_t
    {
        char capabilityName[MST_MAX_CAP_NAME_SIZE]; /**< Capability type name. */
        uint32_t numberOfFields;                    /**< Number of entries in fields. */
        MstHcaCapabilityFieldMetadata* fields;      /**< Array of capability field metadata entries. */
    } MstHcaCapabilityMetadata;

    /**
     * @brief HCA capability value entry in a capability map.
     */
    typedef struct MstHcaCapability_t
    {
        char capabilityName[MST_MAX_CAP_NAME_SIZE]; /**< Capability name. */
        uint32_t value;                             /**< Capability value. */
        bool set;                                   /**< Indicates whether value has been explicitly set. */
    } MstHcaCapability;

    /**
     * @brief Runtime HCA capability map used to query and set capability values.
     */
    typedef struct MstHcaCapabilityMap_t
    {
        char capabilityType[MST_MAX_CAP_NAME_SIZE]; /**< Capability type name. */
        uint32_t numberOfCapabilities;              /**< Number of entries in capabilities. */
        MstHcaCapability* capabilities;             /**< Array of capability value entries. */
    } MstHcaCapabilityMap;

    /**
     * @brief Gets the list of HCA capabilities types.
     * @param mstDevice mstDevice handle.
     * @param capabilityTypesArray Pointer to the array of capability types. will be allocated by the caller and freed
     * by the caller using mstFreeHcaCapabilitiesArray function.
     * @param numCapabilities The number of capabilities. will be set by the function.
     * @return The status of the operation.
     */
    MstStatus
      mstGetCapabilityTypesList(MstDevice mstDevice, char*** capabilityTypesArray, unsigned int* numCapabilities);
    /**
     * @brief Frees a HCA capabilities array allocated by mstGetCapabilityTypesList function.
     * @param capabilityTypesArray The array of capability types.
     * @param numCapabilities The number of capabilities.
     * @return The status of the operation.
     */
    MstStatus mstFreeHcaCapabilitiesArray(char** capabilityTypesArray, unsigned int numCapabilities);
    /**
     * @brief Gets the list of HCA capabilities by type.
     * @param mstDevice mstDevice handle.
     * @param capabilityType The type of the capability.
     * @param capabilityMetadata Pointer to the capability metadata. will be allocated by the caller and freed
     * by the caller using mstFreeHcaCapabilitiesArray function.
     * @return The status of the operation.
     */
    MstStatus mstGetCapabilitiesByType(MstDevice mstDevice,
                                       const char* capabilityType,
                                       MstHcaCapabilityMetadata* capabilityMetadata);

    /**
     * @brief Frees a HCA capability metadata object allocated by mstGetCapabilitiesByType function.
     * @param capabilityMetadata The capability metadata.
     * @return The status of the operation.
     */
    MstStatus mstFreeHcaCapabilitiesMetadata(MstHcaCapabilityMetadata* capabilityMetadata);
    /**
     * @brief Initializes a HCA capability map.
     * @param mstDevice mstDevice handle.
     * @param capabilityType The type of the capability.
     * @param capabilityMap The capability map.
     * @return The status of the operation.
     */
    MstStatus
      mstInitHcaCapabilityMap(MstDevice mstDevice, const char* capabilityType, MstHcaCapabilityMap* capabilityMap);

    /**
     * @brief Queries a HCA capability.
     * @param mstDevice mstDevice handle.
     * @param capabilityType The type of the capability.
     * @param capabilityMap Pointer to the capability map. should be initialized using mstInitHcaCapabilityMap.
     *         The API allocates memory for internal dynamic fields. should be freed by the caller using
     *         mstFreeHcaCapabilityMap function.
     * @param capabilityMode The mode of the capability.
     * @param functionId The function ID.
     * @param functionIdType The type of the function ID.
     * @param otherFunction Whether to access other function.
     * @return The status of the operation.
     */
    MstStatus mstQueryHcaCapability(MstDevice mstDevice,
                                    const char* capabilityType,
                                    MstHcaCapabilityMap* capabilityMap,
                                    MstCapabilityMode capabilityMode,
                                    uint16_t functionId,
                                    MstFunctionIdType functionIdType,
                                    MstOtherFunction otherFunction);
    /**
     * @brief Sets a HCA capability.
     * @param mstDevice mstDevice handle.
     * @param capabilityType The type of the capability.
     * @param capabilityMap Pointer to the capability map. should be initialized using mstInitHcaCapabilityMap.
     *         The API allocates memory for internal dynamic fields. should be freed by the caller using
     *         mstFreeHcaCapabilityMap function.
     * @param capabilityMode The mode of the capability.
     * @param functionId The function ID.
     * @param functionIdType The type of the function ID.
     * @param otherFunction Whether to access other function.
     * @return The status of the operation.
     */
    MstStatus mstSetHcaCapability(MstDevice mstDevice,
                                  const char* capabilityType,
                                  MstHcaCapabilityMap* capabilityMap,
                                  MstCapabilityMode capabilityMode,
                                  uint16_t functionId,
                                  MstFunctionIdType functionIdType,
                                  MstOtherFunction otherFunction);

    /**
     * @brief Frees a HCA capability map allocated by mstQueryHcaCapability function.
     * @param capabilityMap The capability map.
     * @return The status of the operation.
     */
    MstStatus mstFreeHcaCapabilityMap(MstHcaCapabilityMap* capabilityMap);

    /**
     * @brief Gets the value of a specific HCA capability from a capability map.
     * @param mstDevice mstDevice handle.
     * @param capabilityMap The capability map which was queried using mstQueryHcaCapability function.
     * @param capabilityName The name of the capability.
     * @param capabilityValue Pointer to the capability value. will be set by the function.
     * @return The status of the operation.
     */
    MstStatus mstGetCapabilityValue(MstDevice mstDevice,
                                    MstHcaCapabilityMap* capabilityMap,
                                    const char* capabilityName,
                                    uint32_t* capabilityValue);
    /**
     * @brief Sets the value of a specific HCA capability in a capability map to be set using mstSetHcaCapability
     * function.
     * @param mstDevice mstDevice handle.
     * @param capabilityMap The capability map which was initialized using mstInitHcaCapabilityMap function.
     * @param capabilityName The name of the capability.
     * @param capabilityValue The value to set.
     * @return The status of the operation.
     */
    MstStatus mstSetCapabilityValue(MstDevice mstDevice,
                                    MstHcaCapabilityMap* capabilityMap,
                                    const char* capabilityName,
                                    uint32_t capabilityValue);
#ifdef __cplusplus
}
#endif

#endif