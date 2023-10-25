# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# --


#######################################################
#
# types.py
# ctypes connection to C SDK
# Created on:      29-Aug-2023 5:15:00 PM
# Original author: astrutsovsky
#
#######################################################

import ctypes


class c_resource_dump_data(ctypes.Structure):
    _fields_ = [
        ("dump_obj", ctypes.c_void_p),
        ("data", ctypes.POINTER(ctypes.c_ubyte)),
        ("size", ctypes.c_uint32),
        ("endianess", ctypes.c_uint8),
    ]


class c_dump_request(ctypes.Structure):
    _fields_ = [
        ("resource_id", ctypes.c_uint16),
        ("index1", ctypes.c_uint32),
        ("index2", ctypes.c_uint32),
        ("num_of_obj1", ctypes.c_uint16),
        ("num_of_obj2", ctypes.c_uint16),
    ]


class c_device_attributes(ctypes.Structure):
    _fields_ = [
        ("device_name", ctypes.c_char_p),
        ("vhca", ctypes.c_uint16),
        ("rdma_name", ctypes.c_char_p),
    ]
