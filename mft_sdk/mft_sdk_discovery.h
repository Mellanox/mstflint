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

#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Discovers available devices on the system. Updates the discoveredDevices array with the information of the
     * discovered devices and sets the numDiscoveredDevices to the number of discovered devices. the array is allocated
     * by the function and should be freed by the caller.
     * @param interfaceTypes The interface types to discover.
     * @param numInterfaceTypes The number of interface types to discover.
     * @param discoveredDevices Pointer to the discovered devices information array. will be allocated by the function
     * and should be freed by the caller using freeDiscoveredDevices function.
     * @param numDiscoveredDevices Pointer to the number of discovered devices.
     * @return The status of the operation.
     */
    MstStatus mstDiscoverAvailableDevices(MstInterfaceType* interfaceTypes,
                                          unsigned int numInterfaceTypes,
                                          MstDeviceInfo** discoveredDevices,
                                          unsigned int* numDiscoveredDevices);

    /**
     * @brief Frees the discovered devices array.
     * @param discoveredDevices The discovered devices array.
     * @return The status of the operation.
     */
    MstStatus mstFreeDiscoveredDevices(MstDeviceInfo* discoveredDevices);

    /**
     * @brief Gets the available PCIe sub-interfaces for a device.
     * @param deviceInfo The device information struct obtained from mstDiscoverAvailableDevices function. The device's
     * interface type must be PCIe.
     * @param availableSubInterfaces An array of available PCIe sub-interfaces. will be allocated by the function and
     * should be freed by the caller using mstFreePCIeSubInterfaces function.
     * @param numSubInterfaces Pointer to the number of available PCIe sub-interfaces. will be set by the function.
     * @return The status of the operation.
     *         MST_SUCCESS if available PCIe sub-interfaces were found.
     *         MST_ERROR_UNINITIALIZED if the deviceInfo was not initialized.
     *         MST_ERROR_INVALID_ARGUMENT if the device's interface type is not PCIe.
     *         MST_ERROR_NO_AVAILABLE_DEVICES if no available PCIe sub-interfaces were found.
     *         MST_ERROR_NOT_SUPPORTED if the device's product type is not supported.
     */
    MstStatus mstGetAvailablePCIeSubinterfaces(MstDeviceInfo* deviceInfo,
                                               MstPcIeSubInterfaceInfo** availableSubInterfaces,
                                               unsigned int* numSubInterfaces);

    /**
     * @brief Frees a PCIe sub-interfaces array allocated by mstGetAvailablePCIeSubinterfaces function.
     * @param availableSubInterfaces The available PCIe sub-interfaces array.
     * @return The status of the operation.
     *         MST_SUCCESS if the available PCIe sub-interfaces array was freed successfully.
     *         MST_ERROR_INVALID_ARGUMENT if the availableSubInterfaces was not initialized.
     */
    MstStatus mstFreePCIeSubInterfaces(MstPcIeSubInterfaceInfo* availableSubInterfaces);

    /**
     * @brief Gets a device handle by device identifier.
     * @param mstDevice Pointer to the mstDevice handle.
     * @param deviceIdentifier The device identifier. Can be a BDF, Fwctl device name, a /dev/mst/ file descriptor or
     * other device identifier.
     * @return The status of the operation. In case of error, the error string can be retrieved using
     * mstGetInitErrorString function.
     */
    MstStatus mstGetDeviceHandle(MstDevice* mstDevice, const char* deviceIdentifier);

    /**
     * @brief Gets a device handle by device identifier with an optional I2C secondary address to force.
     * @param mstDevice Pointer to the mstDevice handle.
     * @param deviceIdentifier The device identifier. Can be a BDF, Fwctl device name, a /dev/mst/ file descriptor or
     * other device identifier.
     * @param i2cSecondaryAddress I2C secondary address to force.
     * @return The status of the operation. In case of error, the error string can be retrieved using
     * mstGetInitErrorString function.
     */
    MstStatus mstGetDeviceHandleWithI2cSecondary(MstDevice* mstDevice,
                                                 const char* deviceIdentifier,
                                                 uint8_t i2cSecondaryAddress);

    /**
     * @brief Gets a device handle by BDF.
     * @param mstDevice Pointer to the mstDevice handle.
     * @param pciBDF The PCI BDF of the device.
     * @param subInterfaceType The sub-interface type of the device.
     * @return The status of the operation. In case of error, the error string can be retrieved using
     * mstGetInitErrorString function.
     */
    MstStatus mstGetDeviceHandleByBDF(MstDevice* mstDevice, PciBDF pciBDF, MstPCIeSubInterfaceType subInterfaceType);

    /**
     * @brief Gets a device handle by Fwctl device name.
     * @param mstDevice Pointer to the mstDevice handle.
     * @param fwctlDeviceName The Fwctl device name. e.g. "fwctl0" or "/dev/fwctl/fwctl0"
     * @return The status of the operation. In case of error, the error string can be retrieved using
     * mstGetInitErrorString function.
     */
    MstStatus mstGetDeviceHandleByFwctlDeviceName(MstDevice* mstDevice, const char* fwctlDeviceName);

    /**
     * @brief Releases a device handle.
     * @param mstDevice mstDevice handle.
     * @return The status of the operation.
     */
    MstStatus mstReleaseDeviceHandle(MstDevice mstDevice);

#ifdef __cplusplus
}
#endif