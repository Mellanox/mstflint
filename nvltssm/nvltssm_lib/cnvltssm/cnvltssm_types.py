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

import ctypes


class c_ltssm_trace_result:
    """The ltssm_trace_result_t enum of the C SDK."""
    OK = 0
    BAD_PARAM = 1
    ERROR = 2


class c_ltssm_trace_field(ctypes.Structure):
    """The ltssm_trace_field_t struct of the C SDK."""
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("value", ctypes.c_uint32),
        ("address", ctypes.c_uint32),
        ("start_bit", ctypes.c_uint32),
        ("size", ctypes.c_uint32),
    ]


class c_ltssm_trace_device_info(ctypes.Structure):
    """The ltssm_trace_device_info_t struct of the C SDK."""
    _fields_ = [
        ("hw_device_id", ctypes.c_uint32),
        ("device_name", ctypes.c_char_p),
        ("pcore_node", ctypes.c_char_p),
        ("link_node", ctypes.c_char_p),
        ("link_status_node", ctypes.c_char_p),
        ("state_node", ctypes.c_char_p),
        ("ring_node", ctypes.c_char_p),
        ("logger_ctrl_node", ctypes.c_char_p),
    ]


c_ltssm_trace_handle = ctypes.c_void_p
