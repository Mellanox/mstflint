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

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_DEVICE_IDENTIFIER_LENGTH 256

    /**
     * @brief Opaque handle to an MST device opened through the MFT SDK.
     */
    typedef struct mstDevice_t* MstDevice;

    /**
     * @brief Device access interface type.
     */
    typedef enum MstInterfaceType
    {
        PCIe,
        Infiniband,
        MTUSB,
        NDC,
        I2C,
        UnknownInterfaceType
    } MstInterfaceType;

    /**
     * @brief PCIe access sub-interface type.
     */
    typedef enum MstPCIeSubInterfaceType
    {
        FWCtl,
        VFIO,
        VsecMSTDriver,
        BAR0MSTDriver,
        VsecUserLevel,
        BAR0UserLevel,
        NvidiaDriver,
        UnknownPCIeSubInterfaceType
    } MstPCIeSubInterfaceType;

    /**
     * @brief High-level product family of an MST device.
     */
    typedef enum MstProductType
    {
        NIC,
        Switch,
        GPU,
        Retimer,
        UnknownProductType
    } MstProductType;

    /**
     * @brief Specific NVIDIA device generation or platform type.
     */
    typedef enum MstDeviceType
    {
        ConnectX4,
        ConnectX4LX,
        ConnectX5,
        ConnectX6,
        ConnectX6DX,
        ConnectX6LX,
        ConnectX7,
        ConnectX8,
        ConnectX8_Pure_PCIe_Switch,
        ConnectX9,
        ConnectX9_Pure_PCIe_Switch,
        BlueField,
        BlueField2,
        BlueField3,
        BlueField4,
        Spectrum,
        Spectrum2,
        Spectrum3,
        Spectrum4,
        Spectrum5,
        Spectrum6,
        Quantum,
        Quantum2,
        Quantum3,
        NVLink6_Switch,
        GB100,
        GR100,
        UnknownDeviceType
    } MstDeviceType;

    /**
     * @brief PCIe sub-interface information for an MST device.
     */
    typedef struct MstPcieSubInterfaceInfo_t
    {
        MstPCIeSubInterfaceType pcieSubInterfaceType;              /**< PCIe sub-interface type. */
        char subInterfaceIdentifier[MAX_DEVICE_IDENTIFIER_LENGTH]; /**< PCIe sub-interface identifier string. */
    } MstPcieSubInterfaceInfo;

    /**
     * @brief Basic identifying information for an MST device.
     */
    typedef struct MstDeviceInfo_t
    {
        MstProductType productType;                          /**< High-level product family. */
        MstDeviceType deviceType;                            /**< Specific device type. */
        MstInterfaceType interfaceType;                      /**< Access interface type. */
        char deviceIdentifier[MAX_DEVICE_IDENTIFIER_LENGTH]; /**< Device identifier string, for example BDF or LID. */
    } MstDeviceInfo;

    /**
     * @brief PCI bus-device-function address.
     */
    typedef struct MstPciBDF_t
    {
        uint32_t domain;   /**< PCI domain number. */
        uint32_t bus;      /**< PCI bus number. */
        uint32_t device;   /**< PCI device number. */
        uint32_t function; /**< PCI function number. */
    } MstPciBDF;

    /**
     * @brief Firmware version triplet.
     */
    typedef struct MstFwVersion_t
    {
        uint8_t chipId; /**< Firmware chip identifier. */
        uint8_t major;  /**< Major firmware version. */
        uint8_t minor;  /**< Minor firmware version. */
    } MstFwVersion;

    /**
     * @brief Calendar date.
     */
    typedef struct MstDate_t
    {
        uint16_t year; /**< Year. */
        uint8_t month; /**< Month. */
        uint8_t day;   /**< Day of month. */
    } MstDate;

#ifdef __cplusplus
}
#endif