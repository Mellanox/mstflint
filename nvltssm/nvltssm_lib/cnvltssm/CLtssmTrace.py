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
import os

from . import cnvltssm_types


class LtssmTraceSdkError(Exception):
    """Raised when a C SDK call fails."""


class CLtssmTrace:
    """ctypes wrapper over the LTSSM trace C SDK, one shared library per process."""

    LIB_PATH_ENV = "MFT_LTSSM_TRACE_LIBRARY_PATH"
    LIB_NAME = "cltssm_trace.so"
    # From <install prefix>/lib64/mstflint/python_tools/mstltssm/nvltssm_lib/cnvltssm/
    # up to the mstltssm directory, which holds the library next to mstltssm.py.
    LIB_RELATIVE_PATH = os.path.join("..", "..")

    _instance = None
    _sdk = None

    def __new__(cls):
        if not cls._instance:
            cls._load_sdk()
            cls._instance = super().__new__(cls)
        return cls._instance

    @classmethod
    def _load_tool_library(cls):
        """Load the library the ltssm_trace_* symbols are linked into.

        It is installed beside the tool's entry point rather than on the loader
        path, so it is addressed by its own location.
        """
        lib_path = os.path.normpath(os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                                 cls.LIB_RELATIVE_PATH, cls.LIB_NAME))

        return ctypes.CDLL(lib_path)

    @classmethod
    def _load_sdk(cls):
        override = os.environ.get(cls.LIB_PATH_ENV)
        try:
            cls._sdk = ctypes.CDLL(override) if override else cls._load_tool_library()
        except OSError as exp:
            raise LtssmTraceSdkError("Failed loading shared-library {} - {}".format(
                override or cls.LIB_NAME, exp))

        cls._sdk.ltssm_trace_open.restype = ctypes.c_int
        cls._sdk.ltssm_trace_open.argtypes = [
            ctypes.c_char_p,
            ctypes.c_char_p,
            ctypes.POINTER(cnvltssm_types.c_ltssm_trace_handle),
        ]

        cls._sdk.ltssm_trace_get_device_info.restype = ctypes.c_int
        cls._sdk.ltssm_trace_get_device_info.argtypes = [
            cnvltssm_types.c_ltssm_trace_handle,
            ctypes.POINTER(cnvltssm_types.c_ltssm_trace_device_info),
        ]

        cls._sdk.ltssm_trace_read_link.restype = ctypes.c_int
        cls._sdk.ltssm_trace_read_link.argtypes = [
            cnvltssm_types.c_ltssm_trace_handle,
            ctypes.c_uint32,
            ctypes.c_uint32,
            ctypes.POINTER(ctypes.POINTER(cnvltssm_types.c_ltssm_trace_field)),
            ctypes.POINTER(ctypes.c_uint32),
        ]

        cls._sdk.ltssm_trace_free_fields.restype = None
        cls._sdk.ltssm_trace_free_fields.argtypes = [
            ctypes.POINTER(cnvltssm_types.c_ltssm_trace_field),
            ctypes.c_uint32,
        ]

        cls._sdk.ltssm_trace_close.restype = None
        cls._sdk.ltssm_trace_close.argtypes = [cnvltssm_types.c_ltssm_trace_handle]

        cls._sdk.ltssm_trace_get_error.restype = ctypes.c_char_p
        cls._sdk.ltssm_trace_get_error.argtypes = [cnvltssm_types.c_ltssm_trace_handle]

    def open(self, dump_file, device_name=None):
        """Open a dump, resolving its device from the dump unless device_name names it."""
        handle = cnvltssm_types.c_ltssm_trace_handle()
        result = self._sdk.ltssm_trace_open(str(dump_file).encode(),
                                            device_name.encode() if device_name else None,
                                            ctypes.byref(handle))
        if result != cnvltssm_types.c_ltssm_trace_result.OK:
            error = self.get_error(handle)
            self.close(handle)
            raise LtssmTraceSdkError(error or "Failed to open {}".format(dump_file))

        return handle

    def get_device_info(self, handle):
        """Return the device the dump was taken from and its LTSSM node names."""
        info = cnvltssm_types.c_ltssm_trace_device_info()
        result = self._sdk.ltssm_trace_get_device_info(handle, ctypes.byref(info))
        if result != cnvltssm_types.c_ltssm_trace_result.OK:
            raise LtssmTraceSdkError(self.get_error(handle) or "Failed to query the device")

        return LtssmDeviceInfo(info)

    def read_link(self, handle, pcore, link):
        """Return the LTSSM fields of one link as {name: (value, address, start_bit, size)}."""
        fields = ctypes.POINTER(cnvltssm_types.c_ltssm_trace_field)()
        num_of_fields = ctypes.c_uint32()
        result = self._sdk.ltssm_trace_read_link(handle, pcore, link, ctypes.byref(fields),
                                                 ctypes.byref(num_of_fields))
        if result != cnvltssm_types.c_ltssm_trace_result.OK:
            raise LtssmTraceSdkError(self.get_error(handle) or
                                     "Failed to read pcore {} link {}".format(pcore, link))

        try:
            return {
                fields[index].name.decode(): LtssmTraceField(fields[index])
                for index in range(num_of_fields.value)
            }
        finally:
            self._sdk.ltssm_trace_free_fields(fields, num_of_fields)

    def close(self, handle):
        self._sdk.ltssm_trace_close(handle)

    def get_error(self, handle):
        error = self._sdk.ltssm_trace_get_error(handle)

        return error.decode() if error else ""


class LtssmTraceField:
    """A leaf field value together with the dump location it came from."""

    def __init__(self, c_field):
        self.value = c_field.value
        self.address = c_field.address
        self.start_bit = c_field.start_bit
        self.size = c_field.size


class LtssmDeviceInfo:
    """The device a dump was taken from and the node names its ADB addresses LTSSM with."""

    NODE_ATTRIBUTES = ("pcore_node", "link_node", "link_status_node", "state_node", "ring_node", "logger_ctrl_node")

    def __init__(self, c_info):
        self.hw_device_id = c_info.hw_device_id
        self.device_name = self._text(c_info.device_name)
        for attribute in self.NODE_ATTRIBUTES:
            setattr(self, attribute, self._text(getattr(c_info, attribute)))

    @staticmethod
    def _text(value):
        return value.decode() if value else ""
