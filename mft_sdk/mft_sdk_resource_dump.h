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
#include <stddef.h>
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Length of the name fields in a resource menu record, excluding the terminator. */
#define MST_RESOURCE_DUMP_NAME_LENGTH 16

/** Dump the vHCA the device handle itself belongs to. */
#define MST_RESOURCE_DUMP_OWN_VHCA ((uint16_t)-1)

/** Follow reference segments to an unlimited depth. */
#define MST_RESOURCE_DUMP_INFINITE_DEPTH ((uint32_t)-1)

    /**
     * @brief Byte order of the raw dump data handed back to the caller.
     * Only MST_RESOURCE_DUMP_ENDIANNESS_BIG reverses the byte order of the data; the other two hand it
     * back in host byte order, so on a little endian host they are the same request.
     */
    typedef enum MstResourceDumpEndianness_t
    {
        MST_RESOURCE_DUMP_ENDIANNESS_NATIVE = 0, /**< Host byte order. */
        MST_RESOURCE_DUMP_ENDIANNESS_BIG,        /**< Big endian. */
        MST_RESOURCE_DUMP_ENDIANNESS_LITTLE,     /**< Little endian. */
    } MstResourceDumpEndianness;

    /**
     * @brief A single resource dump request: which resource segment to dump and how.
     * The supported indices and object counts of a resource are described by its
     * MstResourceMenuRecord entry, obtained from mstGetResourceMenu function.
     */
    typedef struct MstResourceDumpRequest_t
    {
        uint16_t resourceId;       /**< Segment type of the resource to dump. */
        uint32_t index1;           /**< First resource index, if the resource supports one. */
        uint32_t index2;           /**< Second resource index, if the resource supports one. */
        uint16_t numOfObj1;        /**< Number of objects of the first index to dump. */
        uint16_t numOfObj2;        /**< Number of objects of the second index to dump. */
        uint32_t depth;            /**< Reference segment depth, MST_RESOURCE_DUMP_INFINITE_DEPTH for all. */
        uint16_t vhca;             /**< vHCA to dump, MST_RESOURCE_DUMP_OWN_VHCA for the device's own. */
        bool stripControlSegments; /**< Drop the info/command/reference control segments from the result. */
    } MstResourceDumpRequest;

    /**
     * @brief One resource in the device's resource menu, describing which request
     * parameters that resource accepts.
     */
    typedef struct MstResourceMenuRecord_t
    {
        uint16_t segmentType;                                /**< Resource id to pass in a dump request. */
        char segmentName[MST_RESOURCE_DUMP_NAME_LENGTH + 1]; /**< Resource name, in the requested byte order. */
        char index1Name[MST_RESOURCE_DUMP_NAME_LENGTH + 1];  /**< Name of the first index, empty if unsupported. */
        char index2Name[MST_RESOURCE_DUMP_NAME_LENGTH + 1];  /**< Name of the second index, empty if unsupported. */
        bool supportIndex1;                                  /**< index1 is accepted. */
        bool mustHaveIndex1;                                 /**< index1 is mandatory. */
        bool supportIndex2;                                  /**< index2 is accepted. */
        bool mustHaveIndex2;                                 /**< index2 is mandatory. */
        bool supportNumOfObj1;                               /**< numOfObj1 is accepted. */
        bool mustHaveNumOfObj1;                              /**< numOfObj1 is mandatory. */
        bool numOfObj1SupportsAll;                           /**< numOfObj1 accepts the "all objects" value. */
        bool numOfObj1SupportsActive;                        /**< numOfObj1 accepts the "active objects" value. */
        bool supportNumOfObj2;                               /**< numOfObj2 is accepted. */
        bool mustHaveNumOfObj2;                              /**< numOfObj2 is mandatory. */
        bool numOfObj2SupportsAll;                           /**< numOfObj2 accepts the "all objects" value. */
        bool numOfObj2SupportsActive;                        /**< numOfObj2 accepts the "active objects" value. */
    } MstResourceMenuRecord;

    /**
     * @brief The list of resources a device can dump.
     */
    typedef struct MstResourceMenu_t
    {
        uint32_t numberOfRecords;       /**< Number of entries in records. */
        MstResourceMenuRecord* records; /**< Array of resource menu entries. */
    } MstResourceMenu;

    /**
     * @brief A dumped resource, as a raw resource dump segment stream.
     */
    typedef struct MstResourceDumpData_t
    {
        unsigned char* data;                  /**< Dump data buffer. */
        uint32_t size;                        /**< Valid size of data in bytes. */
        MstResourceDumpEndianness endianness; /**< Byte order the data is laid out in. */
    } MstResourceDumpData;

    /**
     * @brief Gets the list of resources the device can dump.
     * @param mstDevice mstDevice handle.
     * @param endianness Byte order of the underlying menu record data. The name fields carry the device's own bytes
     * and are not decoded: with MST_RESOURCE_DUMP_ENDIANNESS_NATIVE every four byte group of a name reads in reverse
     * on a little endian host. MST_RESOURCE_DUMP_ENDIANNESS_BIG lays every record field out in big endian, so on a
     * little endian host the names read as text but segmentType and the boolean fields do not carry their values.
     * @param menu The device's resource menu. The records array will be allocated by the function and should be freed
     * by the caller using mstFreeResourceMenu function.
     * @return The status of the operation.
     */
    MstStatus mstGetResourceMenu(MstDevice mstDevice, MstResourceDumpEndianness endianness, MstResourceMenu* menu);

    /**
     * @brief Frees a resource menu allocated by mstGetResourceMenu function.
     * @param menu The resource menu.
     * @return The status of the operation.
     */
    MstStatus mstFreeResourceMenu(MstResourceMenu* menu);

    /**
     * @brief Dumps a resource into a buffer allocated by the SDK.
     * @param mstDevice mstDevice handle.
     * @param request The resource to dump.
     * @param endianness The required byte order of the dump data.
     * @param dumpData The dump result. Its data buffer will be allocated by the function and should be freed by the
     * caller using mstFreeResourceDump function.
     * @return The status of the operation.
     */
    MstStatus mstDumpResource(MstDevice mstDevice,
                              const MstResourceDumpRequest* request,
                              MstResourceDumpEndianness endianness,
                              MstResourceDumpData* dumpData);

    /**
     * @brief Frees a dump result allocated by mstDumpResource function.
     * @param dumpData The dump result.
     * @return The status of the operation.
     */
    MstStatus mstFreeResourceDump(MstResourceDumpData* dumpData);

    /**
     * @brief Dumps a resource into a caller provided buffer.
     * @param mstDevice mstDevice handle.
     * @param request The resource to dump.
     * @param endianness The required byte order of the dump data.
     * @param buffer The buffer to dump into. May be NULL to only query the required size.
     * @param bufferSize The allocated size of buffer in bytes.
     * @param dumpSize Pointer to the size of the dump in bytes. Set by the function even when the buffer is too small,
     * so it can be used to size the buffer for a second call.
     * @return The status of the operation. MST_ERROR_INSUFFICIENT_BUFFER if bufferSize is smaller than dumpSize.
     */
    MstStatus mstDumpResourceToBuffer(MstDevice mstDevice,
                                      const MstResourceDumpRequest* request,
                                      MstResourceDumpEndianness endianness,
                                      unsigned char* buffer,
                                      size_t bufferSize,
                                      size_t* dumpSize);

    /**
     * @brief Dumps a resource into a binary file.
     * @param mstDevice mstDevice handle.
     * @param request The resource to dump.
     * @param endianness The required byte order of the dump data.
     * @param filename Path of the output file.
     * @return The status of the operation.
     */
    MstStatus mstDumpResourceToFile(MstDevice mstDevice,
                                    const MstResourceDumpRequest* request,
                                    MstResourceDumpEndianness endianness,
                                    const char* filename);

#ifdef __cplusplus
}
#endif
