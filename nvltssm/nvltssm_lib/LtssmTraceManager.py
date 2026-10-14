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

from nvltssm_lib.LtssmRing import LtssmRing
from nvltssm_lib.LtssmTraceException import LtssmTraceException
from nvltssm_lib.cnvltssm.CLtssmTrace import CLtssmTrace, LtssmTraceSdkError


class LtssmTraceManager:
    """Turns a dump plus a link selection into the report lines of a formatter."""

    # A port number counts pcores from 20 and carries the link as its last digit.
    PORT_BASE = 20
    PORT_STRIDE = 10
    # A local port number packs the pcore above the three link bits.
    LPORT_LINK_BITS = 3
    LPORT_LINK_MASK = 0x7

    def __init__(self, dump_file, formatter, pcore=0, link=0, port=None, lport=None, device_name=None):
        """A link is named either as a pcore plus a link, or as the port or the local
        port number that packs the same pair, which is taken instead of it.

        device_name names the device the dump was taken from, for a dump that does
        not carry its own device id; None reads it out of the dump.
        """
        self._dump_file = dump_file
        self._formatter = formatter
        self._device_name = device_name
        self._pcore, self._link = self._resolve_link(pcore, link, port, lport)

    @classmethod
    def _resolve_link(cls, pcore, link, port, lport):
        """Return the (pcore, link) a link selection points at."""
        if port is not None:
            return (port - cls.PORT_BASE) // cls.PORT_STRIDE, port % cls.PORT_STRIDE

        if lport is not None:
            return lport >> cls.LPORT_LINK_BITS, lport & cls.LPORT_LINK_MASK

        return pcore, link

    def get_output(self):
        try:
            sdk = CLtssmTrace()
        except LtssmTraceSdkError as exp:
            raise LtssmTraceException(str(exp))

        handle = None
        try:
            handle = sdk.open(self._dump_file, self._device_name)
            device_info = sdk.get_device_info(handle)
            fields = sdk.read_link(handle, self._pcore, self._link)
        except LtssmTraceSdkError as exp:
            raise LtssmTraceException(str(exp))
        finally:
            if handle is not None:
                sdk.close(handle)

        ring = LtssmRing(fields, device_info)

        return self._formatter.get_output(self._dump_file, device_info.device_name, self._pcore, self._link, ring)
