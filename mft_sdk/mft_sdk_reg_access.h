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

#include <stdint.h>
#include <stdbool.h>
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief PRM register access method.
     */
    typedef enum
    {
        MST_PRM_GET = 1,
        MST_PRM_SET = 2,
        MST_PRM_SET_READ_MODIFY_WRITE = 3,
    } MstPrmRegAccessMethod;

    /**
     * @brief Access type of a PRM register field.
     */
    typedef enum MstPrmAccessType_t
    {
        MST_PRM_ACCESS_UNKNOWN,
        MST_PRM_ACCESS_RO,
        MST_PRM_ACCESS_WO,
        MST_PRM_ACCESS_RW,
        MST_PRM_ACCESS_INDEX,
        MST_PRM_ACCESS_OP,
    } MstPrmAccessType;

    /**
     * @brief Basic metadata describing a field in a PRM register.
     */
    typedef struct MstPrmRegisterFieldMetadata_t
    {
        char name[256];              /**< Field name. */
        uint32_t address;            /**< Field address within the register layout. */
        uint32_t bitOffset;          /**< Bit offset of the field. */
        uint32_t bitSize;            /**< Field size in bits. */
        MstPrmAccessType accessType; /**< Field access type. */
    } MstPrmRegisterFieldMetadata;

    /**
     * @brief Basic metadata describing a PRM register.
     */
    typedef struct MstPrmRegisterMetadata_t
    {
        char name[32];                       /**< Register name. */
        uint32_t number_of_fields;           /**< Number of entries in fields. */
        MstPrmRegisterFieldMetadata* fields; /**< Array of field metadata entries. */
    } MstPrmRegisterMetadata;

    /**
     * @brief Named enumeration value for a PRM register field.
     */
    typedef struct MstPrmRegisterEnum_t
    {
        char name[128]; /**< Enumeration value name. */
        uint32_t value; /**< Enumeration numeric value. */
    } MstPrmRegisterEnum;

    /**
     * @brief Expanded metadata describing a PRM register field.
     */
    typedef struct MstPrmRegisterFieldExpandedMetadata_t
    {
        MstPrmRegisterFieldMetadata basicMetadata; /**< Basic field metadata. */
        char description[8192];                    /**< Field description text. */
        char fullPath[256];                        /**< Full field path in the register layout. */
        uint32_t number_of_enums;                  /**< Number of entries in enums. */
        MstPrmRegisterEnum* enums;                 /**< Array of named enumeration values. */
    } MstPrmRegisterFieldExpandedMetadata;

    /**
     * @brief Expanded metadata describing a PRM register.
     */
    typedef struct MstPrmRegisterExpandedMetadata_t
    {
        char name[32];                               /**< Register name. */
        uint32_t number_of_fields;                   /**< Number of entries in fields. */
        MstPrmRegisterFieldExpandedMetadata* fields; /**< Array of expanded field metadata entries. */
    } MstPrmRegisterExpandedMetadata;

    /**
     * @brief Field value entry in a PRM register map.
     */
    typedef struct MstPrmRegisterField_t
    {
        char name[256]; /**< Field name. */
        uint32_t value; /**< Field value. */
        bool set;       /**< Indicates whether value has been explicitly set. */
    } MstPrmRegisterField;

    /**
     * @brief Runtime PRM register map used to set, get, and send register fields.
     */
    typedef struct MstPrmRegisterMap_t
    {
        char name[32];               /**< Register name. */
        uint32_t number_of_fields;   /**< Number of entries in fields. */
        MstPrmRegisterField* fields; /**< Array of register field values. */
    } MstPrmRegisterMap;

    /**
     * @brief Initializes a PRM register layout that can be sent using mstSendPRMRegister function.
     * Field values can be set using mstSetPRMRegisterField function.
     * @param mstDevice mstDevice handle.
     * @param regName The name of the PRM register.
     * @param registerMap The layout of the PRM register. will be allocated by the function and should be freed by
     * the caller using mstFreePrmRegisterMap function.
     * @return The status of the operation.
     */
    MstStatus mstInitRegisterMap(MstDevice mstDevice, const char* regName, MstPrmRegisterMap* registerMap);

    /**
     * @brief Frees a PRM register map allocated by mstInitRegisterMap function.
     * @param registerMap The layout of the PRM register.
     * @return The status of the operation.
     */
    MstStatus mstFreePrmRegisterMap(MstPrmRegisterMap* registerMap);

    /**
     * @brief Sends a PRM register request using a register map.
     * @param mstDevice mstDevice handle.
     * @param registerMap The layout of the PRM register, should be obtained by mstInitRegisterMap function. Field
     * values can be set using mstSetPRMRegisterField function.
     * @param method The method of the PRM register.
     * @return The status of the operation.
     */
    MstStatus
      mstSendPRMRegister(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const MstPrmRegAccessMethod method);

    /**
     * @brief Sets a PRM register field's value.
     * @param mstDevice mstDevice handle.
     * @param registerMap The layout of the PRM register, should be obtained by mstInitRegisterMap function.
     * @param fieldName The name of the field to set. Must match a field name in the register map.
     * @param value The value to set.
     * @return The status of the operation.
     */
    MstStatus mstSetPRMRegisterField(MstDevice mstDevice,
                                     MstPrmRegisterMap* registerMap,
                                     const char* fieldName,
                                     uint32_t value);

    /**
     * @brief Gets a PRM register field's value.
     * @param mstDevice mstDevice handle.
     * @param registerMap The layout of the PRM register, should be obtained by mstInitRegisterMap function.
     * @param fieldName The name of the field to get. Must match a field name in the register map.
     * @param value Pointer to the value of the field. will be set by the function.
     * @return The status of the operation.
     */
    MstStatus mstGetPRMRegisterField(MstDevice mstDevice,
                                     MstPrmRegisterMap* registerMap,
                                     const char* fieldName,
                                     uint32_t* value);

    /**
     * @brief Sends a raw PRM register request.
     * @param mstDevice mstDevice handle.
     * @param regId The ID of the PRM register.
     * @param method The method of the PRM register.
     * @param data The data buffer representing the PRM register.
     * @param dataSize The size of the data buffer.
     * @return The status of the operation.
     */
    MstStatus mstSendRawPRMRegister(MstDevice mstDevice,
                                    const uint16_t regId,
                                    const MstPrmRegAccessMethod method,
                                    void* data,
                                    const uint32_t dataSize);

    /**
     * @brief Shows all PRM registers.
     * @param mstDevice mstDevice handle.
     * @param registerNamesArray The array of register names. will be allocated by the function and should be freed by
     * the caller using mstFreePRMRegisterNamesArray function.
     * @param numRegisters Pointer to the number of registers. will be set by the function.
     * @return The status of the operation.
     */
    MstStatus mstShowAllPRMRegisters(MstDevice mstDevice, char*** registerNamesArray, unsigned int* numRegisters);

    /**
     * @brief Frees a PRM register names array allocated by mstShowAllPRMRegisters function.
     * @param registerNamesArray The array of register names.
     * @param numRegisters The number of registers.
     * @return The status of the operation.
     */
    MstStatus mstFreePRMRegisterNamesArray(char** registerNamesArray, unsigned int numRegisters);

    /**
     * @brief Gets the metadata of a PRM register.
     * @param mstDevice mstDevice handle.
     * @param regName The name of the PRM register.
     * @param registerMetadata The metadata of the PRM register. will be allocated by the function and should be freed
     * by the caller using mstFreePrmRegisterMetadata function.
     * @return The status of the operation.
     */
    MstStatus mstGetRegisterMetadata(MstDevice mstDevice, const char* regName, MstPrmRegisterMetadata* registerMetadata);

    /**
     * @brief Frees a PRM register metadata object allocated by mstGetRegisterMetadata function.
     * @param registerMetadata The metadata of the PRM register.
     * @return The status of the operation.
     */
    MstStatus mstFreePrmRegisterMetadata(MstPrmRegisterMetadata* registerMetadata);

    /**
     * @brief Gets the expanded metadata of a PRM register.
     * @param mstDevice mstDevice handle.
     * @param regName The name of the PRM register.
     * @param registerMetadata The metadata of the PRM register. will be allocated by the function and should be freed
     * by the caller using mstFreePrmRegisterExpandedMetadata function.
     * @return The status of the operation.
     */
    MstStatus mstGetRegisterExpandedMetadata(MstDevice mstDevice,
                                             const char* regName,
                                             MstPrmRegisterExpandedMetadata* registerMetadata);

    /**
     * @brief Frees a PRM register expanded metadata object allocated by mstGetRegisterExpandedMetadata function.
     * @param registerMetadata The metadata of the PRM register.
     * @return The status of the operation.
     */
    MstStatus mstFreePrmRegisterExpandedMetadata(MstPrmRegisterExpandedMetadata* registerMetadata);

#ifdef __cplusplus
}
#endif