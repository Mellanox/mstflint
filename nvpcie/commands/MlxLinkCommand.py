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

from abc import abstractmethod
from argparse import ArgumentTypeError

from commands.PcieSwCommand import PcieSwCommand

# the MFT SDK is imported lazily inside the methods that use it: it loads the SDK
# shared library at import time, which is not needed to build the parser or print
# the help - and is not present in a source tree that was never built.


class MlxLinkCommand(PcieSwCommand):
    """Base of the nvpcie sub-commands that report a PCIe link through the
    MFT SDK telemetry layer.

    A sub-command selects one telemetry view and nothing else. What it reports is
    mlxlink's own report, captured by the SDK rather than printed by it, so the
    output is the same one mlxlink produces for "--port_type PCIE" and there is
    no tool side layout to keep in step with it.

    A link may be named by its local port or by its depth/pcie_index/node, the two
    ways "mlxlink --port_type PCIE --show_links" lists it. When neither is given,
    mlxlink resolves the device's PCIe port to the links the device reports.
    """

    @classmethod
    def set_argument_parser(cls, parser):
        super().set_argument_parser(parser)
        # the two name the same link, so they are alternatives rather than a pair
        link_args = parser.add_mutually_exclusive_group()
        link_args.add_argument("--port", type=int,
                               help='Local port of the PCIe link, as "mlxlink --show_links" lists it')
        link_args.add_argument("--dpn", metavar="D/P/N", type=cls._dpn_arg_type,
                               help='Depth, pcie index and node of the PCIe link, e.g. 0/0/0')

    @staticmethod
    def _dpn_arg_type(dpn_str):
        """This method parse a DPN written as "depth/pcie_index/node" into its three numbers."""
        parts = dpn_str.split("/")
        if len(parts) != 3 or not all(part.isdigit() for part in parts):
            raise ArgumentTypeError("invalid DPN: {0}, expected depth/pcie_index/node".format(dpn_str))
        dpn = tuple(int(part) for part in parts)
        # the SDK carries each number in a C unsigned int, which a larger value would wrap around in
        if any(number > 0xFFFFFFFF for number in dpn):
            raise ArgumentTypeError("invalid DPN: {0}, each number must be at most 4294967295".format(dpn_str))
        return dpn

    @classmethod
    def validate_arguments(cls, arguments):
        if not arguments.device:
            cls._arg_parser.error("the following arguments are required: -d/--device")

    @classmethod
    @abstractmethod
    def _telemetry_view(cls):
        """Returns the MFT SDK telemetry view the command reports.

        It is a method rather than a class constant so that naming the view does
        not import the SDK at module scope, which would make the tool unusable -
        help included - wherever the SDK library is missing.
        """
        pass

    def __init__(self, device, port=None, dpn=None):
        self._device = device
        self._port = port
        self._dpn = dpn

    def run(self):
        print(self._get_report(), end="")
        return 0

    def _get_report(self):
        """Returns the report mlxlink would have printed for the view."""
        from mft_sdk import MftSdk, TelemetryPortType

        # local port 0 names a link, so only None means no port
        depth, pcie_index, node = self._dpn or (None, None, None)
        with MftSdk(self._device) as sdk:
            return sdk.get_telemetry_text(views=self._telemetry_view(),
                                          port="" if self._port is None else str(self._port),
                                          port_type=TelemetryPortType.PCIE,
                                          depth=depth, pcie_index=pcie_index, node=node)
