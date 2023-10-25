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
# constants.py
# Python implementation of resource dump constants
# This file will supply all the constants needed
# for the resource parse tool
# Original author: talve
#
#######################################################

from resourcedump_lib.utils import constants as cs
from argparse import ArgumentTypeError
from pathlib import Path

import sys


def calculate_aligned_offset(offset, size, alignment=32):
    """This method calculate the new offset inside the dword
    since the data inside has a different bit index
    """
    return (int(offset / alignment) * alignment) + alignment - size - (offset % alignment) if size < alignment else offset


def is_resource_segment(seg_type):
    """This method check if the seg type is resource segment
    """
    return cs.RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MAX >= seg_type >= cs.RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MIN


def valid_path_arg_type(path_str):
    p = Path(path_str)
    if p.is_file():
        return path_str
    raise ArgumentTypeError("invalid file: {}".format(path_str))


def reverse_string_endian(s):
    """This method converts list of chars stored as BE numbers to LE string."""
    len_4_mul = len(s) // 4 * 4
    s = [reversed(s[i:i + 4]) for i in range(0, len_4_mul, 4)]
    if (len(s) % 4 != 0):
        s.append(reversed(s[len_4_mul, 4:len(s)]))
    s = bytes([item for word in s for item in word])
    return s
