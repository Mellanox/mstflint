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

from commands.MlxLinkCommand import MlxLinkCommand
from commands.CommandFactory import CommandFactory


class LinkCommand(MlxLinkCommand):
    """Reports the operational state of the PCIe links of the device.

    The report is the "PCIe Operational (Enabled) Info" section mlxlink reads out
    of MPEIN - the speed and width each link negotiated against the ones it was
    enabled for - one section per link the device reports.
    """

    COMMAND_NAME = "link"
    DESCRIPTION = "show the operational state of the PCIe links"

    @classmethod
    def _telemetry_view(cls):
        from mft_sdk import TelemetryView

        return TelemetryView.OPERATIONAL


CommandFactory.register(LinkCommand.COMMAND_NAME, LinkCommand)
