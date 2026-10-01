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

    The link is chosen by the firmware, not here: the SDK asks for the device's
    PCIe port and mlxlink resolves it to the links the device reports.
    """

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

    def __init__(self, device):
        self._device = device

    def run(self):
        print(self._get_report(), end="")
        return 0

    def _get_report(self):
        """Returns the report mlxlink would have printed for the view."""
        from mft_sdk import MftSdk, TelemetryPortType

        with MftSdk(self._device) as sdk:
            return sdk.get_telemetry_text(views=self._telemetry_view(),
                                          port_type=TelemetryPortType.PCIE)
