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
from ctypes import POINTER, byref, c_char_p, c_uint32, c_void_p
from enum import IntEnum, IntFlag

from .mft_sdk_core import LIB
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_types import MstDevice, _build_context
from .mft_sdk_telemetry_types import (
    MstTelemetryContext,
)


# Enum: which kind of port a telemetry request addresses.
class TelemetryPortType(IntEnum):
    """Mirrors MstTelemetryPortType in mft_sdk_telemetry_types.h."""

    NETWORK = 0
    PCIE = 1  # label_port is not used; mlxlink resolves the device's PCIe links


# Enum (IntFlag bitmask): telemetry view flags that can be OR-combined.
class TelemetryView(IntFlag):
    """Selectable telemetry views for mstGetTelemetryJson (combine with |)."""

    OPERATIONAL = 1 << 0
    COUNTERS = 1 << 1
    CABLE_DDM = 1 << 2
    MODULE = 1 << 3
    GENERAL = 1 << 4  # full mlxlink default snapshot (showPddr sections)
    EYE = 1 << 5  # --show_eye
    FEC = 1 << 6  # --show_fec
    SERDES_TX = 1 << 7  # --show_serdes_tx
    BER_MONITOR = 1 << 8  # --show_ber_monitor
    EXTERNAL_PHY = 1 << 9  # --show_external_phy
    PLR = 1 << 10  # --show_plr
    KR = 1 << 11  # --show_kr
    RX_RECOVERY = 1 << 12  # --show_rx_recovery_counters
    FEC_HISTOGRAM = 1 << 13  # --show_histogram
    SHOW_MODULE = MODULE  # alias for the full mlxlink "--show_module" view


# Explicit signatures: these functions return/free heap pointers, so argtypes must be
# set to avoid 64-bit pointer truncation (ctypes defaults untyped args to c_int).
LIB.mstGetTelemetryJson.argtypes = [MstDevice, POINTER(MstTelemetryContext.c_type), c_uint32, POINTER(c_char_p)]
LIB.mstGetTelemetryText.argtypes = [MstDevice, POINTER(MstTelemetryContext.c_type), c_uint32, POINTER(c_char_p)]
LIB.mstFreeJsonString.argtypes = [c_void_p]


def mstGetTelemetryJson(
    device_handle: MstDevice,
    views: TelemetryView = TelemetryView.OPERATIONAL,
    port: str = "",
    port_type: TelemetryPortType = TelemetryPortType.NETWORK,
) -> dict:
    """Get one or more telemetry views aggregated into a single JSON dict."""
    context = _build_context(MstTelemetryContext, port, port_type=int(port_type))
    json_ptr = c_char_p()
    status = LIB.mstGetTelemetryJson(device_handle, byref(context), c_uint32(int(views)), byref(json_ptr))
    check_status(MstStatus(status), device_handle)
    try:
        if not json_ptr.value:
            return {}
        return json.loads(json_ptr.value.decode('utf-8'))
    finally:
        LIB.mstFreeJsonString(json_ptr)


def mstGetTelemetryText(
    device_handle: MstDevice,
    views: TelemetryView = TelemetryView.COUNTERS,
    port: str = "",
    port_type: TelemetryPortType = TelemetryPortType.NETWORK,
) -> str:
    """Get one or more telemetry views as the report mlxlink itself would print.

    Only the views mlxlink reports through a "show" command can be returned; GENERAL,
    MODULE, CABLE_DDM, FEC_HISTOGRAM and OPERATIONAL on a network port raise
    MstException(MST_ERROR_NOT_SUPPORTED). Use mstGetTelemetryJson for those.
    """
    context = _build_context(MstTelemetryContext, port, port_type=int(port_type))
    text_ptr = c_char_p()
    status = LIB.mstGetTelemetryText(device_handle, byref(context), c_uint32(int(views)), byref(text_ptr))
    check_status(MstStatus(status), device_handle)
    try:
        if not text_ptr.value:
            return ""
        return text_ptr.value.decode('utf-8')
    finally:
        LIB.mstFreeJsonString(text_ptr)
