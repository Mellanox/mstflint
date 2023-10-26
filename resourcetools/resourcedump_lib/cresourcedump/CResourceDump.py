# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#######################################################
#
# CResourceDump.py
# ctypes connection to C SDK
# Created on:      5-Sep-2023 8:43:00 AM
# Original author: astrutsovsky
#
#######################################################

# from tools_external_libs import get_external_libs_dir

import sys
import ctypes
import platform
from pathlib import Path
from . import cresourcedump_types


class CResourceDump:
    def CDLL(dist_lib_path, installer_lib_path, *args):
        try:
            # print("Openning: {}".format(dist_lib_path))
            return ctypes.CDLL(str(dist_lib_path), *args)
        except BaseException:
            # print("Openning: {}".format(installer_lib_path))
            return ctypes.CDLL(str(installer_lib_path), *args)

    try:
        c_resource_dump_sdk = None
        rd_sdk_lib_basename = "libresource_dump_sdk"
        so_suffix = ''
        if platform.system() != 'Windows':
            so_suffix = 'so'
            # if debug:
            # c_resource_dump_sdk = ctypes.CDLL(str((Path(__file__).resolve()).parents[1] / "src" / "sdk" / "libresource_dump_sdk.so"), ctypes.RTLD_GLOBAL)
            c_resource_dump_sdk = ctypes.CDLL(str((Path(__file__).resolve()).parents[4] / "sdk" / "{}.{}".format(rd_sdk_lib_basename, so_suffix)), ctypes.RTLD_GLOBAL)
        else:
            mtcr_lib_basename = "libmtcr-1"
            so_suffix = 'dll'
            CDLL(Path(".") / "{}.{}".format(mtcr_lib_basename, so_suffix), Path("..") / "{}.{}".format(mtcr_lib_basename, so_suffix), ctypes.RTLD_GLOBAL)
            c_resource_dump_sdk = CDLL(Path(".") / "{}.{}".format(rd_sdk_lib_basename, so_suffix), Path("..") / "{}.{}".format(rd_sdk_lib_basename, so_suffix), ctypes.RTLD_GLOBAL)
    except OSError as ose:
        print("Error: Failed loading shared-library - {0}. Exiting...".format(ose))
        sys.exit(1)

    c_create_resource_dump = c_resource_dump_sdk.create_resource_dump
    c_create_resource_dump.restype = ctypes.c_uint16
    c_create_resource_dump.argtypes = [
        cresourcedump_types.c_device_attributes,
        cresourcedump_types.c_dump_request,
        ctypes.POINTER(cresourcedump_types.c_resource_dump_data),
        ctypes.c_uint32
    ]

    c_destroy_resource_dump = c_resource_dump_sdk.destroy_resource_dump
    c_destroy_resource_dump.restype = None
    c_destroy_resource_dump.argtypes = [
        cresourcedump_types.c_resource_dump_data
    ]

    c_dump_resource_to_file = c_resource_dump_sdk.dump_resource_to_file
    c_dump_resource_to_file.restype = ctypes.c_uint16
    c_dump_resource_to_file.argtypes = [
        cresourcedump_types.c_device_attributes,
        cresourcedump_types.c_dump_request,
        ctypes.c_uint32,
        ctypes.c_char_p,
        ctypes.c_uint8
    ]

    c_get_resource_dump_error = c_resource_dump_sdk.get_resource_dump_error
    c_get_resource_dump_error.restype = ctypes.c_char_p
    c_get_resource_dump_error.argtypes = []
