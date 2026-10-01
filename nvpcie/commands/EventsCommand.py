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

from argparse import Namespace
import os

from commands.PcieSwCommand import PcieSwCommand
from commands.CommandFactory import CommandFactory
from resourceparse_lib.formatters.PcieEventFormatter import PcieEventFormatter
from resourceparse_lib.formatters.PcieEventJsonFormatter import PcieEventJsonFormatter
from resourceparse_lib.utils.common_functions import valid_path_arg_type

# the resource-dump side of resourcetools is imported lazily inside the methods that
# use it: it pulls in the resource-dump C SDK, which is not needed to build the parser
# or print the help. The formatters carry no such dependency. The MFT SDK is imported
# the same way, since importing it loads its shared library.


class EventsCommand(PcieSwCommand):
    """This class fetch the PCIe event log of the device and present it.

    Every event comes from one firmware resource, and the view selects which of
    its two event sets to dump through the first index of the dump request - no
    filtering is done tool side. The resource is requested by name and resolved
    to its numeric type by the firmware menu, so no segment id is stored here.

    A dump saved earlier can be presented instead of a device, in which case the
    dump step is skipped and the file is the input of the parse step. The report
    is then only as good as what the file holds: the events of a response the
    tool did not request itself.

    The log a view stands for can also be erased rather than presented, by the
    firmware invalidating the non volatile memory it is kept in. The erasure
    replaces the report, so nothing is dumped and nothing is presented.
    """

    COMMAND_NAME = "events"
    DESCRIPTION = "fetch the PCIe event log"

    # the only PCIe specific data this tool holds - the event resource and the
    # user facing names of the event sets it indexes
    _EVENT_RESOURCE = "PCIE_EVENTS"
    _VIEW_TO_INDEX1 = {
        "critical": 0,                  # crash related events
        "non-critical": 1,              # everything else
    }

    # the output formats offered by the command, each backed by a formatter. Both
    # present the same event model, so both take the same arguments
    _FORMATS = {
        "text": PcieEventFormatter,         # the human readable event log
        "json": PcieEventJsonFormatter,     # the same log, serialized
    }

    # the register the firmware erases an event log through, and the target value
    # naming the log of each view - a view absent from the map cannot be erased
    _CLEAR_REGISTER = "MNVIA"
    _CLEAR_TARGET_FIELD = "target"
    _VIEW_TO_CLEAR_TARGET = {
        "critical": 1,
    }

    _CLEAR_PROMPT = 'The "{0}" event log of {1} will be erased. Continue? [y/N] '
    _CLEAR_CONFIRMATIONS = ("y", "yes")
    _CLEAR_ABORTED_MESSAGE = "Not confirmed, the event log was left as it is."
    _CLEAR_DONE_MESSAGE = 'The "{0}" event log was erased.'
    _CLEAR_SDK_MISSING_MESSAGE = ("Error: --clear needs the mstflint SDK Python bindings, which this "
                                  "installation does not carry. Rebuild and install mstflint with "
                                  "--enable-mstflint-sdk.")

    # walk the dumped segments flat, as the documented event collection does
    _DUMP_DEPTH = 0

    _EVENT_ADB_FILE = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                                   "data", "pcie_event.adb")

    @classmethod
    def set_argument_parser(cls, parser):
        super().set_argument_parser(parser)
        # the view is the index of a dump request, so it says nothing about a dump
        # that was already taken
        input_group = parser.add_mutually_exclusive_group()
        input_group.add_argument("--view", choices=sorted(cls._VIEW_TO_INDEX1), default="critical",
                                 help='The event view to fetch: "critical" for crash related events, '
                                      '"non-critical" for all the other events (default: critical)')
        input_group.add_argument("--dump-file", metavar="FILENAME", dest="dump_file", type=valid_path_arg_type,
                                 help='Present the events of a dump saved earlier instead of dumping the device')
        parser.add_argument("--format", choices=cls._FORMATS.keys(), default=list(cls._FORMATS)[0], dest="output_format",
                            help='The output format: "text" for the human readable event log, '
                                 '"json" to serialize the events (default: {0})'.format(list(cls._FORMATS)[0]))
        parser.add_argument("-o", "--out", metavar="FILENAME", dest="out_file",
                            help='Write the output to FILENAME instead of the screen')
        parser.add_argument("--clear", action="store_true",
                            help='Erase the event log of the selected view instead of presenting it')
        parser.add_argument("--yes", action="store_true", dest="assume_yes",
                            help='Answer the confirmation of --clear, so that it is not asked')

    @classmethod
    def validate_arguments(cls, arguments):
        if not arguments.device and not arguments.dump_file:
            cls._arg_parser.error("one of the arguments -d/--device --dump-file is required")
        if arguments.assume_yes and not arguments.clear:
            cls._arg_parser.error("argument --yes: allowed only with argument --clear")
        if arguments.clear:
            cls._validate_clear_arguments(arguments)

    @classmethod
    def _validate_clear_arguments(cls, arguments):
        """This method reject what an erasure cannot be asked together with.

        An erasure reaches a device and presents no report, so every argument
        describing an input other than a device, or a presentation of one, is
        rejected rather than passed over - a report argument accepted here would
        be silently ignored. An argument left at its default was not asked for.
        """
        if not arguments.device:
            cls._arg_parser.error("argument --clear: -d/--device is required")
        if arguments.dump_file:
            cls._arg_parser.error("argument --dump-file: not allowed with argument --clear")
        if arguments.view not in cls._VIEW_TO_CLEAR_TARGET:
            cls._arg_parser.error('argument --view: "{0}" cannot be erased, the views that can are: {1}'
                                  .format(arguments.view, ", ".join(sorted(cls._VIEW_TO_CLEAR_TARGET))))
        if arguments.output_format != cls._arg_parser.get_default("output_format"):
            cls._arg_parser.error("argument --format: not allowed with argument --clear")
        if arguments.out_file:
            cls._arg_parser.error("argument -o/--out: not allowed with argument --clear")

    def __init__(self, device, view="critical", output_format=list(_FORMATS)[0], out_file=None, dump_file=None,
                 clear=False, assume_yes=False):
        self._device = device
        self._view = view
        self._output_format = output_format
        self._out_file = out_file
        self._dump_file = dump_file
        self._clear = clear
        self._assume_yes = assume_yes

    def run(self):
        if self._clear:
            return self._clear_events()

        formatter_class = self._FORMATS[self._output_format]
        segments = None if self._dump_file else self._fetch_event_segments()
        self._parse_event_segments(segments, formatter_class, self._build_formatter_argv())
        return 0

    def _clear_events(self):
        """This method erase the event log the selected view stands for.

        The firmware keeps the log in non volatile memory, so it is erased by
        invalidating that memory: one register write naming the log as its
        target. The write is the whole operation - nothing is read back, since
        the register states nothing about the log it invalidated.
        """
        if not self._confirm_clear():
            print(self._CLEAR_ABORTED_MESSAGE)
            return 1

        try:
            from mft_sdk import MftSdk, MstPrmRegAccessMethod
        except ImportError:
            print(self._CLEAR_SDK_MISSING_MESSAGE)
            return 1

        with MftSdk(self._device) as sdk:
            sdk.send_prm_register(self._CLEAR_REGISTER, MstPrmRegAccessMethod.MST_PRM_SET,
                                  field_values={self._CLEAR_TARGET_FIELD: self._VIEW_TO_CLEAR_TARGET[self._view]})

        print(self._CLEAR_DONE_MESSAGE.format(self._view))
        return 0

    def _confirm_clear(self):
        """This method ask the user to confirm the erasure, and return whether
        it was confirmed.

        The events are gone once the firmware invalidated them, so the erasure
        is confirmed unless --yes already answered for it. A run with nothing to
        read the answer from - a pipe, or a job with no terminal - has not
        confirmed anything, so it is answered as a refusal rather than reported
        as the read failing.
        """
        if self._assume_yes:
            return True

        try:
            answer = input(self._CLEAR_PROMPT.format(self._view, self._device))
        except EOFError:
            print()
            return False

        return answer.strip().lower() in self._CLEAR_CONFIRMATIONS

    def _build_formatter_argv(self):
        """This method state on the formatter command line what the report header
        can truthfully say about the request the events came from.

        Both formats present that header and default each of its arguments to N/A,
        so an argument this command has nothing true to pass for is left out rather
        than filled in: a saved dump was taken at a view this run did not choose,
        and may have been taken with no device named at all.
        """
        formatter_argv = []
        if self._device:
            formatter_argv += ["--device", self._device]
        if not self._dump_file:
            formatter_argv += ["--view", self._view]
        return formatter_argv

    def _fetch_event_segments(self):
        """This method dump the event resource at the index of the selected view.

        The DumpCommand queries the firmware menu, verifies the resource and the
        index are supported and resolves the resource name, so an unsupported
        view is reported by the menu validation.
        """
        from resourcedump_lib.commands.DumpCommand import DumpCommand

        dump_command = DumpCommand(device=self._device,
                                   segment=self._EVENT_RESOURCE,
                                   index1=self._VIEW_TO_INDEX1[self._view],
                                   depth=self._DUMP_DEPTH)
        dump_command.execute()
        return dump_command.get_segments()

    def _parse_event_segments(self, segments, formatter_class, formatter_argv):
        """This method decode the dumped segments against the adb and present
        them with the given formatter.

        The manager takes the segments of a device dump, and reads the ones of a
        saved dump off the file itself, so the two inputs meet at the same parse.
        It builds the formatter and hands it to both the parser and the printer,
        so the output honours the selected destination.
        """
        from resourceparse_lib.ResourceParseManager import ResourceParseManager
        from resourceparse_lib.parsers.AdbResourceParser import AdbResourceParser

        manager_args = Namespace(verbose=0, out=self._out_file, out_dir=None, dump_file=self._dump_file,
                                 resource_parser=AdbResourceParser, formatter=formatter_class,
                                 input_byte_order="be")
        parser_args = Namespace(adb_file=self._EVENT_ADB_FILE, manager=None)
        # the formatter arguments are built as a command line, so that the
        # defaults of the ones this tool has nothing to pass for are the real ones
        formatter_args = formatter_class.get_arg_parser().parse_args(formatter_argv)
        ResourceParseManager(manager_args, parser_args, formatter_args, segments).parse()


CommandFactory.register(EventsCommand.COMMAND_NAME, EventsCommand)
