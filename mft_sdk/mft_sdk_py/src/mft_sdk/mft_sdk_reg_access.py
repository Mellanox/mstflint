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

This file provides Python ctypes bindings for the MFT SDK register access functionality.
"""

from ctypes import POINTER, byref, c_char_p, c_uint16, c_uint32, c_void_p, create_string_buffer
from typing import Dict, List, Optional


from .mft_sdk_types import MstDevice
from .mft_sdk_errors import MstStatus, check_status
from .mft_sdk_core import LIB
from .mft_sdk_reg_access_types import (
    MstPrmRegAccessMethod, MstPrmRegisterExpandedMetadata, MstPrmRegisterMap, MstPrmRegisterMetadata
)


def send_prm_register(device_handle: MstDevice, register_name: str, method: MstPrmRegAccessMethod, field_values: Optional[Dict[str, int]] = None) -> Dict[str, int]:
    """
    Send a PRM register request.

    Args:
        device_handle (MstDevice): Device handle
        register_name (str): Name of the register
        method (MstPrmRegAccessMethod): Access method (GET, SET, etc.)
        field_values (Dict[str, int], optional): Dictionary of field values
    Returns:
        Dict[str, int]: Dictionary of field names to values from the register
    """
    c_register_map = MstPrmRegisterMap.c_type()
    c_register_map_p = byref(c_register_map)
    try:
        status = LIB.mstInitRegisterMap(
            device_handle,
            register_name.encode('utf-8'),
            c_register_map_p,
        )

        check_status(MstStatus(status), device_handle)

        if field_values:
            for field_path, value in field_values.items():
                status = LIB.mstSetPRMRegisterField(
                    device_handle,
                    c_register_map_p,
                    field_path.encode('utf-8'),
                    value
                )

                check_status(MstStatus(status), device_handle)

        status = LIB.mstSendPRMRegister(
            device_handle,
            c_register_map_p,
            method.value
        )

        check_status(MstStatus(status), device_handle)

        result = {}
        for i in range(c_register_map.number_of_fields):
            field = c_register_map.fields[i]
            val = c_uint32()
            status = LIB.mstGetPRMRegisterField(
                device_handle,
                c_register_map_p,
                field.name,
                POINTER(c_uint32)(val)
            )
            check_status(MstStatus(status), device_handle)
            result[field.name.decode('utf-8')] = val.value

    finally:
        LIB.mstFreePrmRegisterMap(c_register_map_p)

    return result


# Explicit signature: the raw buffer is passed by pointer, so argtypes must be set to avoid
# 64-bit pointer truncation (ctypes defaults untyped args to c_int).
LIB.mstSendRawPRMRegister.argtypes = [MstDevice, c_uint16, c_uint32, c_void_p, c_uint32]
LIB.mstSendRawPRMRegister.restype = c_uint32  # MstStatus


def send_raw_prm_register(device_handle: MstDevice, register_id: int, method: MstPrmRegAccessMethod, data: bytes) -> bytes:
    """
    Send a PRM register request over a raw buffer, without going through the register layout.

    Use this for a register the caller already serializes itself; send_prm_register is the
    field-based equivalent that needs no manual layout.

    Args:
        device_handle (MstDevice): Device handle
        register_id (int): PRM register ID
        method (MstPrmRegAccessMethod): Access method. Only GET and SET are supported
        data (bytes): The register contents to send. Its length is the register size

    Returns:
        bytes: The register contents after the request, of the same length as data
    """
    buffer = create_string_buffer(data, len(data))

    status = LIB.mstSendRawPRMRegister(
        device_handle,
        register_id,
        method.value,
        buffer,
        len(data)
    )

    check_status(MstStatus(status), device_handle)

    return buffer.raw


def get_all_prm_registers(device_handle: MstDevice) -> List[str]:
    """
    Get all PRM register names.

    Args:
        device_handle (MstDevice): Device handle

    Returns:
        List[str]: List of available register names
    """
    register_names_array = POINTER(c_char_p)()
    num_registers = c_uint32()

    try:
        status = LIB.mstShowAllPRMRegisters(
            device_handle,
            register_names_array,
            num_registers
        )

        check_status(MstStatus(status), device_handle)

        registers = []
        if num_registers.value > 0 and register_names_array:
            for i in range(num_registers.value):
                if register_names_array[i]:
                    registers.append(register_names_array[i].decode('utf-8'))
    finally:
        if register_names_array:
            LIB.mstFreePRMRegisterNamesArray(register_names_array, num_registers.value)

    return registers


def get_register_metadata(device_handle: MstDevice, register_name: str, expanded=False) -> MstPrmRegisterMetadata:
    """
    Get metadata for a PRM register.

    Args:
        device_handle (MstDevice): Device handle
        register_name (str): Name of the register
        expanded (bool, optional): If true, return expanded metadata (enums, etc.)

    Returns:
        MstPrmRegisterMetadata: Register metadata including field information
    """
    metadata_type = MstPrmRegisterExpandedMetadata if expanded else MstPrmRegisterMetadata
    get_metadata = LIB.mstGetRegisterExpandedMetadata if expanded else LIB.mstGetRegisterMetadata
    free_metadata = LIB.mstFreePrmRegisterExpandedMetadata if expanded else LIB.mstFreePrmRegisterMetadata

    metadata = metadata_type.c_type()
    try:
        status = get_metadata(
            device_handle,
            register_name.encode('utf-8'),
            byref(metadata)
        )

        check_status(MstStatus(status), device_handle)
        return metadata_type.from_c(metadata)
    finally:
        free_metadata(byref(metadata))
