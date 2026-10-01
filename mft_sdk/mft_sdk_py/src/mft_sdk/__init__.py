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

This package provides Python bindings for the NVIDIA Mellanox Firmware Tools (MFT) SDK,
allowing Python applications to interact with NVIDIA network devices through the MFT SDK API.

Main classes and functions:
- MftSdk: Main SDK interface class for device interaction
- Device discovery functions to find available devices
- Register access functionality for low-level device configuration
- Comprehensive error handling and type definitions
"""

from .mft_sdk_class import MftSdk
from .mft_sdk_discovery import (
    discover_available_devices,
    get_available_pcie_subinterfaces,
    get_device_handle,
    get_device_handle_by_bdf,
    get_device_handle_by_fwctl_device_name,
    release_device_handle
)
from .mft_sdk_types import (
    MstDevice,
    MstInterfaceType,
    MstPCIeSubInterfaceType,
    MstProductType,
    MstDeviceType,
    MstDeviceInfo,
    MstPcieSubInterfaceInfo,
    MstPciBDF,
)
from .mft_sdk_errors import (
    MstStatus,
    MftSdkException,
    MftSdkUninitializedException,
    MftSdkInvalidArgumentException,
    MftSdkNotSupportedException,
    MftSdkNoPermissionException,
    MftSdkDeviceNotFoundException,
    status_to_exception,
    check_status,
    get_last_error_string,
    get_init_error_string,
    get_syndrome,
)
from .mft_sdk_reg_access import (
    send_prm_register,
    send_raw_prm_register,
    get_all_prm_registers,
    get_register_metadata
)
from .mft_sdk_reg_access_types import (
    MstPrmRegAccessMethod,
    MstPrmAccessType,
    MstPrmRegisterMetadata,
    MstPrmRegisterFieldMetadata,
    MstPrmRegisterField,
    MstPrmRegisterMap
)
from .mft_sdk_cr_space_access import (
    mstReadCRSpace,
    mstWriteCRSpace
)
from .mft_sdk_i2c_access import (
    mstSetI2cSecondary,
    mstGetI2cSecondary
)
from .mft_sdk_icmd import (
    mstSendIcmd,
    MstIcmdAccessMethod
)
from .mft_sdk_telemetry import (
    mstGetTelemetryJson,
    mstGetTelemetryText,
    TelemetryPortType,
    TelemetryView,
)
from .mft_sdk_temperature import (
    get_device_temperature,
)

__all__ = [
    "MftSdk",

    "discover_available_devices",
    "get_available_pcie_subinterfaces",
    "get_device_handle",
    "get_device_handle_by_bdf",
    "get_device_handle_by_fwctl_device_name",
    "release_device_handle",

    "MstDevice",
    "MstInterfaceType",
    "MstPCIeSubInterfaceType",
    "MstProductType",
    "MstDeviceType",
    "MstDeviceInfo",
    "MstPcieSubInterfaceInfo",
    "MstPciBDF",

    "MstStatus",
    "MftSdkException",
    "MftSdkUninitializedException",
    "MftSdkInvalidArgumentException",
    "MftSdkNotSupportedException",
    "MftSdkNoPermissionException",
    "MftSdkDeviceNotFoundException",
    "status_to_exception",
    "check_status",
    "get_last_error_string",
    "get_init_error_string",
    "get_syndrome",

    "send_prm_register",
    "send_raw_prm_register",
    "get_all_prm_registers",
    "get_register_metadata",
    "MstPrmRegAccessMethod",
    "MstPrmAccessType",
    "MstPrmRegisterMetadata",
    "MstPrmRegisterFieldMetadata",
    "MstPrmRegisterField",
    "MstPrmRegisterMap",

    "mstReadCRSpace",
    "mstWriteCRSpace",

    "mstSetI2cSecondary",
    "mstGetI2cSecondary",

    "mstSendIcmd",
    "MstIcmdAccessMethod",

    "mstGetTelemetryJson",
    "mstGetTelemetryText",

    "TelemetryPortType",
    "TelemetryView",



    "get_device_temperature",
]
