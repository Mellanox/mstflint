# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

import ctypes
import os
import inspect
from ctypes import CDLL
from enum import IntEnum

# Mirror C/C++ enums


class Severity(IntEnum):
    DEBUG = 0
    INFO = 1
    WARNING = 2
    ERROR = 3
    FATAL = 4
    DEFAULT = 5


class Layer(IntEnum):
    # Always-enabled meta layer for the logger's own output.
    LOGGER = 0
    MTCR = 1
    REG_ACCESS = 2
    FLINT = 3
    MLXCONFIG = 4
    MLXLINK = 5
    MLXREG = 6
    MFT_CORE = 7
    MLXFWOPS = 8
    MST_TOOL = 9
    EFUSE = 10
    COMMON = 11
    HCA_CAPS = 12


_LIB_NAME = "libmft_logger.so"
_HERE = os.path.dirname(os.path.realpath(__file__))


def _candidate_paths():
    """Where libmft_logger may live, most specific first.

    An installed tool is launched through common/python_wrapper, which puts
    $(libdir)/mstflint/python_tools on PYTHONPATH and $(libdir) on
    LD_LIBRARY_PATH - so the bare name resolves. Running straight from the
    source tree, the .so sits next to this file.
    """
    env = os.environ.get("MFT_LOGGER_LIBRARY_PATH")
    if env:
        yield env
    yield _LIB_NAME
    yield os.path.join(_HERE, _LIB_NAME)
    lib_dir = os.environ.get("MSTFLINT_LIB_DIR")
    if lib_dir:
        yield os.path.join(lib_dir, "mstflint", "python_tools", _LIB_NAME)
        yield os.path.join(lib_dir, _LIB_NAME)


def _load_library():
    errors = []
    for path in _candidate_paths():
        try:
            return CDLL(path)
        except OSError as e:
            errors.append("{0}: {1}".format(path, e))
    raise RuntimeError("Failed to load MFT logger library: {0}".format("; ".join(errors)))


_lib = _load_library()

# Define the C Function Prototypes (argtypes and restype)

# extern "C" void mft_log(int layer, int severity,
#                         const char* file, int line, const char* func,
#                         const char* message)
_lib.mft_log.argtypes = [
    ctypes.c_int,      # layer
    ctypes.c_int,      # severity
    ctypes.c_char_p,   # file
    ctypes.c_int,      # line
    ctypes.c_char_p,   # func
    ctypes.c_char_p,   # message
]
_lib.mft_log.restype = None


class Logger:
    """Pythonic facade over the native mft_logger C ABI."""

    @staticmethod
    def _log_internal(layer, severity, message):
        """Capture caller frame info and forward to the C wrapper."""
        # Two frames back: caller of debug()/info()/... -> _log_internal
        frame = inspect.currentframe().f_back.f_back

        filename = os.path.basename(frame.f_code.co_filename).encode("utf-8")
        line = frame.f_lineno
        func = frame.f_code.co_name.encode("utf-8")
        msg = str(message).encode("utf-8")

        _lib.mft_log(int(layer), int(severity), filename, line, func, msg)

    @classmethod
    def debug(cls, layer, message):
        cls._log_internal(layer, Severity.DEBUG, message)

    @classmethod
    def info(cls, layer, message):
        cls._log_internal(layer, Severity.INFO, message)

    @classmethod
    def warning(cls, layer, message):
        cls._log_internal(layer, Severity.WARNING, message)

    @classmethod
    def error(cls, layer, message):
        cls._log_internal(layer, Severity.ERROR, message)

    @classmethod
    def fatal(cls, layer, message):
        cls._log_internal(layer, Severity.FATAL, message)
