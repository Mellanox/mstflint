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
This file provides Python ctypes bindings for the MFT SDK error handling.
"""

from ctypes import Structure, c_uint32, c_char, c_char_p, CDLL
from enum import IntEnum
from .mft_sdk_types import MstDevice
from .mft_sdk_core import LIB


class MstStatus(IntEnum):
    """Status codes for MFT SDK operations"""
    MST_SUCCESS = 0
    MST_ERROR_UNINITIALIZED = 1
    MST_ERROR_INVALID_ARGUMENT = 2
    MST_ERROR_NOT_SUPPORTED = 3
    MST_ERROR_NO_PERMISSION = 4
    MST_ERROR_NO_AVAILABLE_DEVICES = 5
    MST_ERROR_DEVICE_NOT_FOUND = 6
    MST_ERROR_INTERFACE_NOT_AVAILABLE = 7
    MST_ERROR_MST_DRIVER_NOT_LOADED = 8
    MST_ERROR_FAILED_TO_ALLOCATE_MEMORY = 9
    MST_ERROR_FAILED_TO_OPEN_DEVICE = 10
    MST_ERROR_FAILED_TO_SEND_ACCESS_REG = 11
    MST_ERROR_FAILED_TO_GET_TELEMETRY = 12
    MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES = 13
    MST_ERROR_FAILED_TO_READ_CR_SPACE = 14
    MST_ERROR_FAILED_TO_WRITE_CR_SPACE = 15
    MST_ERROR_FAILED_TO_SET_I2C_SECONDARY = 16
    MST_ERROR_UNKNOWN = 17
    MST_ERROR_FAILED_TO_SEND_ICMD = 18
    MST_ERROR_TEMPERATURE_NOT_AVAILABLE = 19
    MST_ERROR_INSUFFICIENT_BUFFER = 20
    MST_ERROR_FAILED_TO_DUMP_RESOURCE = 21
    MST_ERROR_FAILED_TO_COLLECT_AMBER = 22


def _setup_error_functions(lib: CDLL):
    # const char* mstGetLastErrorString(MstDevice mstDevice);
    lib.mstGetLastErrorString.argtypes = [MstDevice]
    lib.mstGetLastErrorString.restype = c_char_p

    # const char* mstGetInitErrorString(void);
    lib.mstGetInitErrorString.argtypes = []
    lib.mstGetInitErrorString.restype = c_char_p

    # uint32_t mstGetSyndrome(MstDevice mstDevice);
    lib.mstGetSyndrome.argtypes = [MstDevice]
    lib.mstGetSyndrome.restype = c_uint32


_setup_error_functions(lib=LIB)


class MftSdkException(Exception):
    """Base exception for MFT SDK errors"""
    def __init__(self, status: MstStatus, message: str):
        self.status = status
        self.message = message
        super().__init__(f"MFT SDK Error {status.name}: {message}")


class MftSdkUninitializedException(MftSdkException):
    """Thrown when SDK is uninitialized"""
    pass


class MftSdkInvalidArgumentException(MftSdkException):
    """Thrown when invalid arguments are provided"""
    pass


class MftSdkNotSupportedException(MftSdkException):
    """Thrown when operation is not supported"""
    pass


class MftSdkNoPermissionException(MftSdkException):
    """Thrown when insufficient permissions"""
    pass


class MftSdkDeviceNotFoundException(MftSdkException):
    """Thrown when device is not found"""
    pass


def status_to_exception(status: MstStatus, message: str = "") -> MftSdkException:
    """Convert MstStatus to appropriate exception.

    Args:
        status (MstStatus): Status code to convert
        message (str): Optional error message

    Returns:
        MftSdkException: Appropriate exception instance for the status
    """
    if status == MstStatus.MST_ERROR_UNINITIALIZED:
        return MftSdkUninitializedException(status, message)
    elif status == MstStatus.MST_ERROR_INVALID_ARGUMENT:
        return MftSdkInvalidArgumentException(status, message)
    elif status == MstStatus.MST_ERROR_NOT_SUPPORTED:
        return MftSdkNotSupportedException(status, message)
    elif status == MstStatus.MST_ERROR_NO_PERMISSION:
        return MftSdkNoPermissionException(status, message)
    elif status == MstStatus.MST_ERROR_DEVICE_NOT_FOUND:
        return MftSdkDeviceNotFoundException(status, message)
    else:
        return MftSdkException(status, message)


def check_status(status: MstStatus, device_handle: MstDevice = None):
    """Check status and raise exception if not successful.

    Args:
        status (MstStatus): Status code to check
        device_handle (MstDevice): Device handle for retrieving error string

    Raises:
        MftSdkException: If status indicates an error
    """
    if device_handle:
        message = get_last_error_string(device_handle)
    else:
        message = get_init_error_string()
    if status != MstStatus.MST_SUCCESS:
        raise status_to_exception(status, message)


def get_last_error_string(device_handle: MstDevice) -> str:
    """
    Get the last error string for a given device.

    Args:
        device_handle: MstDevice handle

    Returns:
        Error string
    """
    error_str = LIB.mstGetLastErrorString(device_handle)
    if error_str:
        return error_str.decode('utf-8')
    return ""


def get_init_error_string() -> str:
    """
    Get initialization error string.

    Returns:
        Initialization error string
    """
    error_str = LIB.mstGetInitErrorString()
    if error_str:
        return error_str.decode('utf-8')
    return ""


def get_syndrome(device_handle: MstDevice) -> int:
    """
    Get the syndrome code reported by the device for the last failed operation.

    Args:
        device_handle: MstDevice handle

    Returns:
        Syndrome code
    """
    return LIB.mstGetSyndrome(device_handle)
