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

This file provides Python ctypes bindings for the MFT SDK CR space access functionality.
"""

from ctypes import POINTER, c_uint32
from typing import List

from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB


def mstReadCRSpace(device_handle: MstDevice, address: int, byte_length: int) -> List[int]:
    """
    Read bytes from CR space.

    Args:
        device_handle (MstDevice): Device handle
        address (int): Address to read from
        byte_length (int): Number of bytes to read

    Returns:
        List[int]: Data read from CR space
    """
    num_dwords = byte_length // 4
    c_data = (c_uint32 * num_dwords)()
    status = LIB.mstReadCRSpace(
        device_handle,
        address,
        c_data,
        byte_length
    )
    check_status(MstStatus(status), device_handle)
    return c_data


def mstWriteCRSpace(device_handle: MstDevice, address: int, data: List[int], byte_length: int) -> None:
    """
    Write to CR space.

    Args:
        device_handle (MstDevice): Device handle
        address (int): Address to write to
        data (List[int]): Data to write to CR space
        byte_length (int): Number of bytes to write

    Returns:
        None
    """
    c_data = (c_uint32 * len(data))(*data)
    status = LIB.mstWriteCRSpace(
        device_handle,
        address,
        c_data,
        byte_length
    )
    check_status(MstStatus(status), device_handle)
