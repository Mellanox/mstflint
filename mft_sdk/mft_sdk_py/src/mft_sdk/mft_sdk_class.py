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

from ctypes import byref, c_void_p, c_uint8
from typing import Dict, List, Optional, Sequence

from .mft_sdk_core import LIB
from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_reg_access import get_all_prm_registers, get_register_metadata, send_prm_register, send_raw_prm_register, MstPrmRegisterMetadata, MstPrmRegAccessMethod
from .mft_sdk_i2c_access import mstSetI2cSecondary, mstGetI2cSecondary
from .mft_sdk_icmd import mstSendIcmd, MstIcmdAccessMethod
from .mft_sdk_telemetry import (
    mstGetTelemetryJson,
    mstGetTelemetryText,
    TelemetryPortType,
    TelemetryView,
)
from .mft_sdk_amber import mstGetAmberJson, mstGetAmberReport


class MftSdk():
    """Main MFT SDK interface class for device interaction."""

    def __init__(self, device_identifier: str, i2c_secondary_address: c_uint8 = None) -> None:
        """Initialize MFT SDK instance.

        Args:
            device_identifier (str): Device identifier string to open.
            i2c_secondary_address (c_uint8): I2C secondary address to force.
                                            If None, the I2C secondary address will not be forced.
        """
        self._device_handle = c_void_p()
        if i2c_secondary_address is not None:
            status = LIB.mstGetDeviceHandleWithI2cSecondary(
                byref(self._device_handle),
                device_identifier.encode('utf-8'),
                i2c_secondary_address
            )
        else:
            status = LIB.mstGetDeviceHandle(byref(self._device_handle), device_identifier.encode('utf-8'))
        check_status(MstStatus(status))

    def __enter__(self) -> "MftSdk":
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> bool:
        self.close()
        return False

    def close(self) -> None:
        """Release the device handle; idempotent so __exit__/__del__ never double-free."""
        if self._device_handle:
            handle = self._device_handle
            status = MstStatus(LIB.mstReleaseDeviceHandle(handle))
            if status == MstStatus.MST_SUCCESS:
                self._device_handle = c_void_p()
            else:
                check_status(status, handle)

    def __del__(self) -> None:
        try:
            self.close()
        except Exception:
            pass

    def get_all_prm_registers(self) -> List[str]:
        """Get list of all available PRM registers.

        Returns:
            List[str]: Available PRM register names
        """
        return get_all_prm_registers(self._device_handle)

    def get_prm_register_metadata(self, register_name: str, expanded: bool = False) -> MstPrmRegisterMetadata:
        """Get metadata for a PRM register.

        Args:
            register_name (str): Name of the register
            expanded (bool): If true, return expanded metadata

        Returns:
            MstPrmRegisterMetadata: Register metadata
        """
        return get_register_metadata(self._device_handle, register_name, expanded=expanded)

    def send_prm_register(self, register_name: str, access_method: MstPrmRegAccessMethod, field_values: Optional[Dict[str, int]] = None) -> Dict[str, int]:
        """Send PRM register request and return field values.

        Args:
            register_name (str): Name of the register
            access_method (MstPrmRegAccessMethod): Access method (GET, SET, etc.)
            field_values (Optional[Dict[str, int]]): Field values to set

        Returns:
            Dict[str, int]: Register field values
        """
        return send_prm_register(self._device_handle, register_name, access_method, field_values=field_values)

    def send_raw_prm_register(self, register_id: int, access_method: MstPrmRegAccessMethod, data: bytes) -> bytes:
        """Send a PRM register request over a raw, caller-serialized buffer.

        Args:
            register_id (int): PRM register ID
            access_method (MstPrmRegAccessMethod): Access method. Only GET and SET are supported
            data (bytes): The register contents to send

        Returns:
            bytes: The register contents after the request
        """
        return send_raw_prm_register(self._device_handle, register_id, access_method, data)

    def get_telemetry_json(
        self,
        views: TelemetryView = TelemetryView.OPERATIONAL,
        port: str = "",
        port_type: TelemetryPortType = TelemetryPortType.NETWORK,
    ) -> dict:
        """Aggregate one or more telemetry views into a single JSON dict."""
        return mstGetTelemetryJson(self._device_handle, views, port, port_type)

    def get_telemetry_text(
        self,
        views: TelemetryView = TelemetryView.COUNTERS,
        port: str = "",
        port_type: TelemetryPortType = TelemetryPortType.NETWORK,
    ) -> str:
        """Get one or more telemetry views as the report mlxlink itself would print."""
        return mstGetTelemetryText(self._device_handle, views, port, port_type)

    def get_amber_json(self, port: str = "", sheets: Sequence[int] = ()) -> dict:
        """Collect amBER as a JSON dict keyed by port; empty port/sheets collect all ports/sheets."""
        return mstGetAmberJson(self._device_handle, port, sheets)

    def get_amber_report(self, port: str = "", sheets: Sequence[int] = ()) -> dict:
        """Collect amBER as an amber_version envelope over per-port field dicts."""
        return mstGetAmberReport(self._device_handle, port, sheets)

    def set_i2c_secondary_address(self, i2c_secondary_address: int) -> None:
        """Set the I2C secondary address for the device.

        Args:
            i2c_secondary_address (c_uint8): I2C secondary address to set
        """
        return mstSetI2cSecondary(self._device_handle, i2c_secondary_address)

    def get_i2c_secondary_address(self) -> int:
        """Get the I2C secondary address for the device.

        Returns:
            int: Current I2C secondary address
        """
        return mstGetI2cSecondary(self._device_handle)

    def send_icmd(self,
                  opcode: int,
                  data: List[int],
                  method: MstIcmdAccessMethod = MstIcmdAccessMethod.MST_ICMD_WRITE_READ) -> List[int]:
        """Send an ICMD to the device firmware.

        Args:
            opcode (int): ICMD opcode to send
            data (List[int]): Command input, as dwords
            method (MstIcmdAccessMethod): Whether to write the input before executing. Commands that take
                input parameters - queries included - need MST_ICMD_WRITE_READ

        Returns:
            List[int]: The firmware output, as dwords
        """
        return mstSendIcmd(self._device_handle, opcode, data, method)
