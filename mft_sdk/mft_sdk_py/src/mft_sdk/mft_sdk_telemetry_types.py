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

from ctypes import c_char, c_uint

from .mft_sdk_types import MftSdkStruct

# Mirrors MST_TELEMETRY_PORT_MAX_LENGTH in mft_sdk_telemetry_types.h
MST_TELEMETRY_PORT_MAX_LENGTH = 32


class MstTelemetryContext(MftSdkStruct):
    """Context a telemetry call takes.

    size must come first: the SDK reads it to tell which version of this struct the
    caller was built against, and never reads past it. An empty label_port selects
    the device default port. port_type comes last, behind the size guard, so a caller
    built against the older struct stays valid and reads as NETWORK.
    """
    size: int = c_uint
    label_port: str = c_char * MST_TELEMETRY_PORT_MAX_LENGTH
    port_type: int = c_uint
