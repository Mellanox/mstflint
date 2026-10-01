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

from ctypes import CDLL, c_char, c_char_p, c_uint32, POINTER, c_bool
from enum import IntEnum
from typing import List

from .mft_sdk_core import LIB
from .mft_sdk_types import CountedArray, MstDevice, MftSdkStruct

REGISTER_NAME_SIZE = 32
DESCRIPTION_SIZE = 8192
FULL_PATH_SIZE = 256
ENUM_NAME_SIZE = 128


class MstPrmRegAccessMethod(IntEnum):
    """PRM register access methods"""
    MST_PRM_GET = 1
    MST_PRM_SET = 2
    MST_PRM_SET_READ_MODIFY_WRITE = 3


class MstPrmAccessType(IntEnum):
    """PRM access types"""
    MST_PRM_ACCESS_UNKNOWN = 0
    MST_PRM_ACCESS_RO = 1
    MST_PRM_ACCESS_WO = 2
    MST_PRM_ACCESS_RW = 3
    MST_PRM_ACCESS_INDEX = 4
    MST_PRM_ACCESS_OP = 5


class MstPrmRegisterFieldMetadata(MftSdkStruct):
    """PRM register field metadata"""
    name: str = c_char * FULL_PATH_SIZE
    address: int = c_uint32
    bitOffset: int = c_uint32
    bitSize: int = c_uint32
    accessType: MstPrmAccessType = c_uint32


class MstPrmRegisterMetadata(MftSdkStruct):
    """PRM register metadata"""
    name: str = c_char * REGISTER_NAME_SIZE
    fields: List[MstPrmRegisterFieldMetadata] = CountedArray(count="number_of_fields")


class MstPrmRegisterEnum(MftSdkStruct):
    """PRM register enum value"""
    name: str = c_char * ENUM_NAME_SIZE
    value: int = c_uint32


class MstPrmRegisterFieldExpandedMetadata(MstPrmRegisterFieldMetadata):
    """PRM register field metadata, with its description and enumeration values"""
    description: str = c_char * DESCRIPTION_SIZE
    full_path: str = c_char * FULL_PATH_SIZE
    enums: List[MstPrmRegisterEnum] = CountedArray(count="number_of_enums")


class MstPrmRegisterExpandedMetadata(MftSdkStruct):
    """PRM register metadata, expanded per field"""
    name: str = c_char * REGISTER_NAME_SIZE
    fields: List[MstPrmRegisterFieldExpandedMetadata] = CountedArray(count="number_of_fields")


class MstPrmRegisterField(MftSdkStruct):
    """PRM register field"""
    name: str = c_char * FULL_PATH_SIZE
    value: int = c_uint32
    set: bool = c_bool


class MstPrmRegisterMap(MftSdkStruct):
    """PRM register map"""
    name: str = c_char * REGISTER_NAME_SIZE
    fields: List[MstPrmRegisterField] = CountedArray(count="number_of_fields")


def _setup_reg_access_functions(lib: CDLL):
    """Setup function signatures for register access functions"""

    # MstStatus mstInitRegisterMap(MstDevice mstDevice, const char* regName, MstPrmRegisterMap* registerMap);
    lib.mstInitRegisterMap.argtypes = [MstDevice, c_char_p, POINTER(MstPrmRegisterMap.c_type)]
    lib.mstInitRegisterMap.restype = c_uint32  # MstStatus

    # MstStatus mstFreePrmRegisterMap(MstPrmRegisterMap* registerMap);
    lib.mstFreePrmRegisterMap.argtypes = [POINTER(MstPrmRegisterMap.c_type)]
    lib.mstFreePrmRegisterMap.restype = c_uint32  # MstStatus

    # MstStatus mstSendPRMRegister(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const MstPrmRegAccessMethod method);
    lib.mstSendPRMRegister.argtypes = [MstDevice, POINTER(MstPrmRegisterMap.c_type), c_uint32]
    lib.mstSendPRMRegister.restype = c_uint32  # MstStatus

    # MstStatus mstSetPRMRegisterField(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t value);
    lib.mstSetPRMRegisterField.argtypes = [MstDevice, POINTER(MstPrmRegisterMap.c_type), c_char_p, c_uint32]
    lib.mstSetPRMRegisterField.restype = c_uint32  # MstStatus

    # MstStatus mstGetPRMRegisterField(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t* value);
    lib.mstGetPRMRegisterField.argtypes = [MstDevice, POINTER(MstPrmRegisterMap.c_type), c_char_p, POINTER(c_uint32)]
    lib.mstGetPRMRegisterField.restype = c_uint32  # MstStatus

    # MstStatus mstShowAllPRMRegisters(MstDevice mstDevice, char*** registerNamesArray, unsigned int* numRegisters);
    lib.mstShowAllPRMRegisters.argtypes = [MstDevice, POINTER(POINTER(c_char_p)), POINTER(c_uint32)]
    lib.mstShowAllPRMRegisters.restype = c_uint32  # MstStatus

    # MstStatus mstFreePRMRegisterNamesArray(char** registerNamesArray, unsigned int numRegisters);
    lib.mstFreePRMRegisterNamesArray.argtypes = [POINTER(c_char_p), c_uint32]
    lib.mstFreePRMRegisterNamesArray.restype = c_uint32  # MstStatus

    # MstStatus mstGetRegisterMetadata(MstDevice mstDevice, const char* regName, MstPrmRegisterMetadata* registerMetadata);
    lib.mstGetRegisterMetadata.argtypes = [MstDevice, c_char_p, POINTER(MstPrmRegisterMetadata.c_type)]
    lib.mstGetRegisterMetadata.restype = c_uint32  # MstStatus

    # MstStatus mstFreePrmRegisterMetadata(MstPrmRegisterMetadata* registerMetadata);
    lib.mstFreePrmRegisterMetadata.argtypes = [POINTER(MstPrmRegisterMetadata.c_type)]
    lib.mstFreePrmRegisterMetadata.restype = c_uint32  # MstStatus

    lib.mstGetRegisterExpandedMetadata.argtypes = [
        MstDevice, c_char_p, POINTER(MstPrmRegisterExpandedMetadata.c_type)]
    lib.mstGetRegisterExpandedMetadata.restype = c_uint32  # MstStatus

    lib.mstFreePrmRegisterExpandedMetadata.argtypes = [POINTER(MstPrmRegisterExpandedMetadata.c_type)]
    lib.mstFreePrmRegisterExpandedMetadata.restype = c_uint32  # MstStatus


_setup_reg_access_functions(LIB)
