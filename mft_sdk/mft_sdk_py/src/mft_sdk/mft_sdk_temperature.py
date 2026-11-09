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
This file provides Python ctypes bindings for the MFT SDK device temperature functionality.
"""

import ctypes
from ctypes import CDLL, POINTER, c_int32, c_uint32

from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB


def _setup_temperature_functions(lib: CDLL):
    """Setup function signatures for temperature functions"""

    # MstStatus mstGetDeviceTemperature(MstDevice mstDevice, int32_t* temperature);
    lib.mstGetDeviceTemperature.argtypes = [MstDevice, POINTER(c_int32)]
    lib.mstGetDeviceTemperature.restype = c_uint32  # MstStatus


_setup_temperature_functions(LIB)


def get_device_temperature(device_handle: MstDevice) -> int:
    """
    Get the current device temperature, equivalent to `mget_temp -d <device>`.

    The value is the highest reading across the device's internal thermal diodes and,
    on CPO systems, its module sensors.

    Args:
        device_handle (MstDevice): Device handle

    Returns:
        int: Device temperature in whole degrees Celsius

    Raises:
        MftSdkException: MST_ERROR_TEMPERATURE_NOT_AVAILABLE if the device answered but no
            sensor produced a valid reading. MftSdkNotSupportedException for a device
            in livefish mode or a GPU ASIC.
    """
    temperature = c_int32()
    status = LIB.mstGetDeviceTemperature(
        device_handle,
        ctypes.byref(temperature)
    )
    check_status(MstStatus(status), device_handle)
    return temperature.value
