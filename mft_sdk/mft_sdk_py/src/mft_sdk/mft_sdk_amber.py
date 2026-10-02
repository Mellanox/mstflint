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

import json
from ctypes import POINTER, byref, c_char, c_char_p, c_uint, c_void_p, sizeof
from enum import IntEnum
from typing import List, Sequence

from .mft_sdk_core import LIB
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_types import CountedArray, MstDevice, MftSdkStruct

MST_AMBER_PORT_MAX_LENGTH = 32
MST_AMBER_FIELD_NAME_MAX = 64
MST_AMBER_VALUE_MAX = 64
MST_AMBER_VERSION_MAX = 16


class AmberSheet(IntEnum):
    """amBER sheets, also the indexes mlxlink's --amber_index accepts."""

    GENERAL = 1
    INDEXES = 2
    LINK_STATUS = 3
    MODULE_STATUS = 4
    SYSTEM = 5
    HDR_SERDES = 6
    NDR_SERDES = 7
    PORT_COUNTERS = 8
    TROUBLESHOOTING = 9
    PHY_OP = 10
    LINK_UP = 11
    LINK_DOWN = 12
    TEST_MODE = 13
    MODULE_TEST_MODE = 14
    EXT_MODULE_STATUS = 16
    SERDES_5NM_GEN7 = 17
    RECOVERY_COUNTERS = 20
    SERDES_5NM_GEN8 = 21


class MstAmberContext(MftSdkStruct):
    """Context an amber call takes.

    size must come first: the SDK reads it to tell which version of this struct the
    caller was built against. An empty label_port collects every port of a switch
    device, a single port on an HCA. An empty sheet_ids collects every sheet.
    """
    size: int = c_uint
    label_port: str = c_char * MST_AMBER_PORT_MAX_LENGTH
    sheet_ids: List[int] = CountedArray(count="sheet_count", count_c_type=c_uint, element_c_type=c_uint)


class MstAmberField(MftSdkStruct):
    """One field collected from an amBER sheet."""
    sheet_id: int = c_uint
    field_name: str = c_char * MST_AMBER_FIELD_NAME_MAX
    value: str = c_char * MST_AMBER_VALUE_MAX


class MstAmberPort(MftSdkStruct):
    """The amBER fields collected for one port."""
    label_port: str = c_char * MST_AMBER_PORT_MAX_LENGTH
    fields: List[MstAmberField] = CountedArray(count="field_count", count_c_type=c_uint)


class MstAmberReport(MftSdkStruct):
    """A full amBER report, one entry per collected port."""
    amber_version: str = c_char * MST_AMBER_VERSION_MAX
    ports: List[MstAmberPort] = CountedArray(count="port_count", count_c_type=c_uint)


LIB.mstGetAmberJson.argtypes = [MstDevice, POINTER(MstAmberContext.c_type), POINTER(c_char_p)]
LIB.mstFreeJsonString.argtypes = [c_void_p]
LIB.mstGetAmberReport.argtypes = [
    MstDevice, POINTER(MstAmberContext.c_type), POINTER(MstAmberReport.c_type)]
LIB.mstFreeAmberReport.argtypes = [POINTER(MstAmberReport.c_type)]


def _build_amber_context(port: str, sheets: Sequence[int]):
    return MstAmberContext(size=sizeof(MstAmberContext.c_type), label_port=port,
                           sheet_ids=list(sheets)).to_c()


def mstGetAmberJson(device_handle: MstDevice, port: str = "", sheets: Sequence[int] = ()) -> dict:
    """Collect amBER as a JSON dict keyed by port; empty port/sheets collect all ports/sheets."""
    context = _build_amber_context(port, sheets)
    json_ptr = c_char_p()
    status = LIB.mstGetAmberJson(device_handle, byref(context), byref(json_ptr))
    check_status(MstStatus(status), device_handle)
    try:
        if not json_ptr.value:
            return {}
        return json.loads(json_ptr.value.decode('utf-8'))
    finally:
        if json_ptr.value:
            LIB.mstFreeJsonString(json_ptr)


def mstGetAmberReport(device_handle: MstDevice, port: str = "", sheets: Sequence[int] = ()) -> dict:
    """Collect amBER as {"amber_version": str, "ports": [...]}; empty port/sheets collect all.

    Each entry in "ports" is {"label_port": str, "fields": [{"sheet_id": int, "field_name": str,
    "value": str}, ...]}, mirroring one MstAmberPort.
    """
    context = _build_amber_context(port, sheets)
    report = MstAmberReport.c_type()
    status = LIB.mstGetAmberReport(device_handle, byref(context), byref(report))
    check_status(MstStatus(status), device_handle)
    try:
        return MstAmberReport.from_c(report).as_dict()
    finally:
        LIB.mstFreeAmberReport(byref(report))
