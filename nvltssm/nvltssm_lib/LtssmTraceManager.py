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
    UNPACKED_SELECTORS = ("pcore", "link")
    PACKED_SELECTORS = ("port", "lport")
    SELECTOR_OPTIONS = UNPACKED_SELECTORS + PACKED_SELECTORS
    DEFAULT_PCORE = 0
    DEFAULT_LINK = 0
    NEGATIVE_SELECTOR_ERROR = "Invalid --{} {}: a link selector cannot be negative"
    MIXED_SELECTOR_ERROR = "Invalid --{} {}: a link selector cannot be given together with --{}"
    NO_SUCH_LINK_ERROR = "{} has no pcore {}, link {}"

    def __init__(self, dump_file, formatter, pcore=None, link=None, port=None, lport=None, device_name=None):
        """A link is named either as a pcore plus a link, or as the port or the local
        port number that packs the same pair, which is taken instead of it.

        A selector left None is one the caller did not name, so an unnamed pcore
        and link fall back to the first of each.

        device_name names the device the dump was taken from, for a dump that does
        not carry its own device id; None reads it out of the dump.
        """
        self._dump_file = dump_file
        self._formatter = formatter
        self._device_name = device_name
        self._validate_selectors(pcore, link, port, lport)
        self._pcore, self._link = self._resolve_link(pcore, link, port, lport)

    @classmethod
    def _validate_selectors(cls, pcore, link, port, lport):
        """Refuse a negative selector, which the reader reads as the unsigned index it wraps into."""
        for option, value in zip(cls.SELECTOR_OPTIONS, (pcore, link, port, lport)):
            if value is not None and value < 0:
                raise LtssmTraceException(cls.NEGATIVE_SELECTOR_ERROR.format(option, value))

    @classmethod
    def mixed_selector_error(cls, pcore, link, port, lport):
        """Answer why a link named in both ways is refused, or None when it is named in one.

        A port or local port number packs a pcore and a link of its own, so naming
        one alongside either of them leaves the request contradicting itself.
        """
        packed = [(option, value) for option, value in zip(cls.PACKED_SELECTORS, (port, lport))
                  if value is not None]
        unpacked = [option for option, value in zip(cls.UNPACKED_SELECTORS, (pcore, link))
                    if value is not None]

        if not packed or not unpacked:
            return None

        return cls.MIXED_SELECTOR_ERROR.format(packed[0][0], packed[0][1], unpacked[0])

    @classmethod
    def _resolve_link(cls, pcore, link, port, lport):
        """Return the (pcore, link) a link selection points at."""
        if port is not None:
            return (port - cls.PORT_BASE) // cls.PORT_STRIDE, port % cls.PORT_STRIDE

        if lport is not None:
            return lport >> cls.LPORT_LINK_BITS, lport & cls.LPORT_LINK_MASK

        return (cls.DEFAULT_PCORE if pcore is None else pcore,
                cls.DEFAULT_LINK if link is None else link)

    def get_output(self):
        try:
            sdk = CLtssmTrace()
        except LtssmTraceSdkError as exp:
            raise LtssmTraceException(str(exp))

        handle = None
        device_info = None
        try:
            handle = sdk.open(self._dump_file, self._device_name)
            device_info = sdk.get_device_info(handle)
            fields = sdk.read_link(handle, self._pcore, self._link)
        except LtssmTraceSdkError as exp:
            raise LtssmTraceException(self._reader_error(device_info, str(exp)))
        finally:
            if handle is not None:
                sdk.close(handle)

        ring = LtssmRing(fields, device_info)

        return self._formatter.get_output(self._dump_file, device_info.device_name, self._pcore, self._link, ring)

    def _reader_error(self, device_info, error):
        """Report a link the device's layout does not hold as the selection it came from, since
        the reader names such a link with the internal nodes it failed to resolve it through.
        """
        if device_info is not None and device_info.pcore_node in error:
            return self.NO_SUCH_LINK_ERROR.format(device_info.device_name, self._pcore, self._link)

        return error
