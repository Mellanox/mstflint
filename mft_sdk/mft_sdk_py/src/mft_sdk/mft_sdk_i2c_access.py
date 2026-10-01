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
This file provides Python ctypes bindings for the MFT SDK I2C access functionality.
"""

import ctypes
from ctypes import c_uint8
from typing import List

from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB


def mstSetI2cSecondary(device_handle: MstDevice, newI2cSecondary: int) -> None:
    """
    Set the I2C secondary address.

    Args:
        device_handle (MstDevice): Device handle
        newI2cSecondary (int): New I2C secondary address

    Returns:
        None
    """
    status = LIB.mstSetI2cSecondary(
        device_handle,
        newI2cSecondary
    )
    check_status(MstStatus(status), device_handle)


def mstGetI2cSecondary(device_handle: MstDevice) -> int:
    """
    Get the I2C secondary address.

    Args:
        device_handle (MstDevice): Device handle

    Returns:
        int: I2C secondary address
    """
    value = c_uint8()
    status = LIB.mstGetI2cSecondary(
        device_handle,
        ctypes.byref(value)
    )
    check_status(MstStatus(status), device_handle)
    return value.value
