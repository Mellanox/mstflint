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

This file provides Python ctypes bindings for the MFT SDK ICMD functionality.
"""

from ctypes import c_uint32
from enum import IntEnum
from typing import List

from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB


class MstIcmdAccessMethod(IntEnum):
    """ICMD access methods - whether the input buffer is written before executing"""
    MST_ICMD_WRITE_READ = 1
    MST_ICMD_READ_ONLY = 2


def mstSendIcmd(device_handle: MstDevice,
                opcode: int,
                data: List[int],
                method: MstIcmdAccessMethod = MstIcmdAccessMethod.MST_ICMD_WRITE_READ) -> List[int]:
    """
    Send an ICMD to the device firmware.

    Args:
        device_handle (MstDevice): Device handle
        opcode (int): ICMD opcode to send
        data (List[int]): Command input, as dwords
        method (MstIcmdAccessMethod): Whether to write the input before executing. Commands that take
            input parameters - queries included - need MST_ICMD_WRITE_READ

    Returns:
        List[int]: The firmware output, as dwords
    """
    c_data = (c_uint32 * len(data))(*data)
    status = LIB.mstSendIcmd(
        device_handle,
        opcode,
        c_data,
        len(c_data) * 4,
        method
    )
    check_status(MstStatus(status), device_handle)
    return list(c_data)
