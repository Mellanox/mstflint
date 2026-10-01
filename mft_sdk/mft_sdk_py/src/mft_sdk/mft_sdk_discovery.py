# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""
Python ctypes bindings for the NVIDIA MFT SDK

This file provides Python ctypes bindings for the MFT SDK device discovery functionality.
"""

from ctypes import POINTER, c_int, c_uint32, c_uint8, c_char_p, CDLL, byref
from typing import List, Optional
from .mft_sdk_types import (
    MstDevice, MstInterfaceType, MstPCIeSubInterfaceType,
    MstDeviceInfo, MstPcieSubInterfaceInfo, MstPciBDF
)
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB


def _setup_discovery_functions(lib: CDLL):
    """Setup function signatures for discovery functions"""

    # MstStatus mstDiscoverAvailableDevices(MstInterfaceType* interfaceTypes,
    #                                       unsigned int numInterfaceTypes,
    #                                       MstDeviceInfo** discoveredDevices,
    #                                       unsigned int* numDiscoveredDevices);
    lib.mstDiscoverAvailableDevices.argtypes = [
        POINTER(c_uint32),  # MstInterfaceType*
        c_uint32,           # numInterfaceTypes
        POINTER(POINTER(MstDeviceInfo.c_type)),  # MstDeviceInfo**
        POINTER(c_uint32)   # numDiscoveredDevices*
    ]
    lib.mstDiscoverAvailableDevices.restype = c_uint32  # MstStatus

    # MstStatus mstFreeDiscoveredDevices(MstDeviceInfo* discoveredDevices);
    lib.mstFreeDiscoveredDevices.argtypes = [POINTER(MstDeviceInfo.c_type)]
    lib.mstFreeDiscoveredDevices.restype = c_uint32  # MstStatus

    # MstStatus mstGetAvailablePCIeSubinterfaces(MstDeviceInfo* deviceInfo,
    #                                            MstPcieSubInterfaceInfo** availableSubInterfaces,
    #                                            unsigned int* numSubInterfaces);
    lib.mstGetAvailablePCIeSubinterfaces.argtypes = [
        POINTER(MstDeviceInfo.c_type),  # MstDeviceInfo*
        POINTER(POINTER(MstPcieSubInterfaceInfo.c_type)),  # MstPcieSubInterfaceInfo**
        POINTER(c_uint32)  # numSubInterfaces*
    ]
    lib.mstGetAvailablePCIeSubinterfaces.restype = c_uint32  # MstStatus

    # MstStatus mstFreePCIeSubInterfaces(MstPcieSubInterfaceInfo* availableSubInterfaces);
    lib.mstFreePCIeSubInterfaces.argtypes = [POINTER(MstPcieSubInterfaceInfo.c_type)]
    lib.mstFreePCIeSubInterfaces.restype = c_uint32  # MstStatus

    # MstStatus mstGetDeviceHandleWithI2cSecondary(MstDevice* mstDevice, const char* deviceIdentifier, c_uint8 i2cSecondaryAddress);
    lib.mstGetDeviceHandleWithI2cSecondary.argtypes = [POINTER(MstDevice), c_char_p, c_uint8]
    lib.mstGetDeviceHandleWithI2cSecondary.restype = c_uint32  # MstStatus

    # MstStatus mstGetDeviceHandleByBDF(MstDevice* mstDevice, MstPciBDF pciBDF, MstPCIeSubInterfaceType subInterfaceType);
    lib.mstGetDeviceHandleByBDF.argtypes = [POINTER(MstDevice), MstPciBDF.c_type, c_uint32]
    lib.mstGetDeviceHandleByBDF.restype = c_uint32  # MstStatus

    # MstStatus mstGetDeviceHandleByFwctlDeviceName(MstDevice* mstDevice, const char* fwctlDeviceName);
    lib.mstGetDeviceHandleByFwctlDeviceName.argtypes = [POINTER(MstDevice), c_char_p]
    lib.mstGetDeviceHandleByFwctlDeviceName.restype = c_uint32  # MstStatus

    # MstStatus mstReleaseDeviceHandle(MstDevice mstDevice);
    lib.mstReleaseDeviceHandle.argtypes = [MstDevice]
    lib.mstReleaseDeviceHandle.restype = c_uint32  # MstStatus


_setup_discovery_functions(LIB)


def discover_available_devices(interface_types: Optional[List[MstInterfaceType]] = None) -> List[MstDeviceInfo]:
    """
    Discover available MFT devices on the system.

    Args:
        interface_types: Optional list of MstInterfaceType values to filter by.
                         If None, all interface types will be included.

    Returns:
        List[MstDeviceInfo]: List of discovered device information
    """
    if interface_types is None:
        interface_types = list(MstInterfaceType)

    num_interface_types = len(interface_types)
    interface_types_array = (c_uint32 * num_interface_types)(*interface_types)

    discovered_devices = POINTER(MstDeviceInfo.c_type)()
    num_discovered_devices = c_uint32()

    try:
        status = LIB.mstDiscoverAvailableDevices(
            interface_types_array,
            num_interface_types,
            discovered_devices,
            num_discovered_devices
        )

        check_status(MstStatus(status))

        devices = []
        if num_discovered_devices.value > 0 and discovered_devices:
            for i in range(num_discovered_devices.value):
                devices.append(MstDeviceInfo.from_c(discovered_devices[i]))
    finally:
        if discovered_devices:
            LIB.mstFreeDiscoveredDevices(discovered_devices)

    return devices


def get_available_pcie_subinterfaces(device_info: MstDeviceInfo) -> List[MstPcieSubInterfaceInfo]:
    """
    Get available PCIe sub-interfaces for a device.

    Args:
        device_info (MstDeviceInfo): Device information object

    Returns:
        List[MstPcieSubInterfaceInfo]: Available sub-interfaces for the device
    """
    available_sub_interfaces = POINTER(MstPcieSubInterfaceInfo.c_type)()
    num_sub_interfaces = c_uint32()

    device_info_c = device_info.to_c()
    device_info_ptr = POINTER(MstDeviceInfo.c_type)(device_info_c)

    try:
        status = LIB.mstGetAvailablePCIeSubinterfaces(
            device_info_ptr,
            available_sub_interfaces,
            num_sub_interfaces
        )
        check_status(MstStatus(status))

        sub_interfaces = []
        if num_sub_interfaces.value > 0 and available_sub_interfaces:
            for i in range(num_sub_interfaces.value):
                sub_interfaces.append(MstPcieSubInterfaceInfo.from_c(available_sub_interfaces[i]))

    finally:
        if available_sub_interfaces:
            LIB.mstFreePCIeSubInterfaces(available_sub_interfaces)

    return sub_interfaces


def get_device_handle(device_identifier: str, i2c_secondary_address: c_uint8 = None) -> MstDevice:
    """
    Get a device handle for a given device identifier.

    Args:
        device_identifier (str): Device identifier string
        i2c_secondary_address (c_uint8): I2C secondary address. If None, the I2C secondary address will not be forced.
    Returns:
        MstDevice: Device handle for the specified device
    """
    device_handle = MstDevice()
    if i2c_secondary_address is not None:
        status = LIB.mstGetDeviceHandleWithI2cSecondary(
            byref(device_handle),
            device_identifier.encode('utf-8'),
            i2c_secondary_address
        )
    else:
        status = LIB.mstGetDeviceHandle(byref(device_handle), device_identifier.encode('utf-8'))

    check_status(MstStatus(status))
    return device_handle


def get_device_handle_by_bdf(pci_bdf: MstPciBDF, sub_interface_type: MstPCIeSubInterfaceType) -> MstDevice:
    """
    Get a device handle for a PCI BDF, opened over a specific PCIe sub-interface.

    Args:
        pci_bdf (MstPciBDF): PCI bus-device-function address of the device
        sub_interface_type (MstPCIeSubInterfaceType): Sub-interface to open the device over.
            UnknownPCIeSubInterfaceType is rejected - the SDK resolves the BDF differently per
            sub-interface, so there is nothing to fall back to.

    Returns:
        MstDevice: Device handle for the specified device
    """
    device_handle = MstDevice()
    status = LIB.mstGetDeviceHandleByBDF(
        byref(device_handle),
        pci_bdf.to_c(),
        sub_interface_type
    )

    check_status(MstStatus(status))
    return device_handle


def get_device_handle_by_fwctl_device_name(fwctl_device_name: str) -> MstDevice:
    """
    Get a device handle for an fwctl device.

    Args:
        fwctl_device_name (str): Fwctl device name, e.g. "fwctl0" or "/dev/fwctl/fwctl0"

    Returns:
        MstDevice: Device handle for the specified device
    """
    device_handle = MstDevice()
    status = LIB.mstGetDeviceHandleByFwctlDeviceName(
        byref(device_handle),
        fwctl_device_name.encode('utf-8')
    )

    check_status(MstStatus(status))
    return device_handle


def release_device_handle(device_handle: MstDevice) -> None:
    """
    Release a device handle.

    Args:
        device_handle (MstDevice): Device handle to release
    """
    status = LIB.mstReleaseDeviceHandle(device_handle)
    check_status(MstStatus(status), device_handle)
