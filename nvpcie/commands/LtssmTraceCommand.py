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

import os
import sys
import tempfile

from commands.PcieSwCommand import PcieSwCommand
from commands.CommandFactory import CommandFactory
from resourceparse_lib.utils.common_functions import valid_path_arg_type

# the nvltssm library is imported lazily inside the paths that use it: it is built
# only with --enable-adb-generic-tools, so importing it at module scope would make
# the tool unusable - help included - wherever it is absent. mstdump is imported
# inside the device path for its own reason: it pulls in the build generated
# tools_version, which the help must not need


class LtssmTraceCommand(PcieSwCommand):
    """This class decode the PCIe LTSSM history the device logged and present it.

    The history lives in a ring the firmware keeps in the configuration space, so
    it is read out of an "mstdump" output rather than through a register. A dump
    taken earlier can be decoded, and when none is given the command takes one of
    the device itself - a mitigation until the ring is exposed as a register or
    as a resource of its own, which is what the tool will read then.

    The decode itself belongs to the "nvltssm" tool, which this command drives
    at the python level: same reader, same report.
    """

    COMMAND_NAME = "ltssm"
    COMMAND_GROUP = "trace"
    DESCRIPTION = "decode the PCIe LTSSM history"

    # the dump this command takes of the device is its own input and nothing else,
    # so it is named after the device and removed once the history was read
    _DUMP_FILE_SUFFIX = "_ltssm.dump"

    @classmethod
    def set_argument_parser(cls, parser):
        super().set_argument_parser(parser)
        parser.add_argument("--dump-file", metavar="FILENAME", dest="dump_file", type=valid_path_arg_type,
                            help='Decode an "mstdump" output taken earlier instead of dumping the device')

        # the ring is per link, and a link is named either by the pcore it sits in
        # or by one of the two numbers that pack the same pair
        link_args = parser.add_argument_group('link selection arguments')
        link_args.add_argument("--pcore", type=int, default=0,
                               help='Index of the pcore holding the link (default: 0)')
        link_args.add_argument("--link", type=int, default=0,
                               help='Index of the link within the pcore (default: 0)')
        link_args.add_argument("--port", type=int,
                               help='Port number of the link, taken instead of --pcore and --link')
        link_args.add_argument("--lport", type=int,
                               help='Local port number of the link, taken instead of --pcore and --link')

        parser.add_argument("-o", "--out", metavar="FILENAME", dest="out_file",
                            help='Write the output to FILENAME instead of the screen')

    @classmethod
    def validate_arguments(cls, arguments):
        if not arguments.device and not arguments.dump_file:
            cls._arg_parser.error("one of the arguments -d/--device --dump-file is required")

    def __init__(self, device, dump_file=None, pcore=0, link=0, port=None, lport=None, out_file=None):
        self._device = device
        self._dump_file = dump_file
        self._pcore = pcore
        self._link = link
        self._port = port
        self._lport = lport
        self._out_file = out_file
        self._trace_manager = None

    def run(self):
        if self._dump_file:
            return self._trace(self._dump_file)

        dump_file = self._create_dump_file()
        try:
            self._dump_device(dump_file)
            return self._trace(dump_file)
        finally:
            os.remove(dump_file)

    def _create_dump_file(self):
        """This method create the file the dump of the device is taken into."""
        with tempfile.NamedTemporaryFile(prefix=os.path.basename(self._device),
                                         suffix=self._DUMP_FILE_SUFFIX, delete=False) as dump_file:
            return dump_file.name

    def _dump_device(self, dump_file):
        """This method take the dump the history is read from.

        It is asked for at the fast path of mstdump, which reads the whole
        configuration space in one resource dump where the device supports it,
        and falls back to the address by address read where it does not.
        """
        from nvltssm_lib.LtssmTraceException import LtssmTraceException
        import mstdump

        if mstdump.dump_device(self._device, output_file=dump_file, fast=True):
            raise LtssmTraceException("Failed to dump {0}".format(self._device))

    def _trace(self, dump_file):
        """This method read the history of the selected link and present it."""
        from nvltssm_lib.LtssmTraceManager import LtssmTraceManager
        from nvltssm_lib.formatters.LtssmReportFormatter import LtssmReportFormatter

        self._trace_manager = LtssmTraceManager(dump_file, LtssmReportFormatter(),
                                                self._pcore, self._link, self._port, self._lport)
        output = "\n".join(self._trace_manager.get_output()) + "\n"

        if self._out_file:
            with open(self._out_file, "w") as out_file:
                out_file.write(output)
        else:
            sys.stdout.write(output)

        return 0


CommandFactory.register(LtssmTraceCommand.COMMAND_NAME, LtssmTraceCommand)
