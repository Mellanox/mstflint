# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

from resourceparse_lib.formatters.SegmentFormatter import SegmentFormatter, FORMATTER_CLASSES
from resourceparse_lib.utils import constants as cs

import struct


class AdbBasicFormatter(SegmentFormatter):
    """This class present a decoded segment as the plain "field = value" listing.

    It is the default formatter, and reproduces the output the parser generated
    before formatters were introduced.
    """

    FORMATTER_TYPE = "basic"
    SEGMENT_HEADER_INDENT = 20
    RAW_DATA_DW_IN_ROW = 4
    RAW_DATA_LABEL_WIDTH = 15

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = super().get_arg_parser(prog)

        optional_named = arg_parser.add_argument_group('optional arguments')
        optional_named.add_argument("-r", "--raw", action="store_true", help='Prints the raw data in addition to the parsed data')
        optional_named.add_argument("--hide-segment-header", action="store_true", help='Hide segment header during printing')

        return arg_parser

    @staticmethod
    def get_description():
        return \
            """        This formatter presents each decoded field as a "field = value" line,
        under a header line naming the segment. This is the default output.
"""

    def __init__(self, formatter_args):
        super().__init__(formatter_args)
        self._hide_segment_header = formatter_args.hide_segment_header
        self._raw = formatter_args.raw

    def format_segment_header(self, seg_type, seg_name, additional_info, seg):
        if self._hide_segment_header:
            return
        seg.add_parsed_data(self.SEGMENT_HEADER_INDENT * " " + "Segment - {0} ({1:#06x}){2}".format(seg_name, seg_type, additional_info))

    def format_terminal_field(self, field_name, field_value, seg, layout_item=None):
        seg.add_parsed_data("{} = {}".format(field_name, field_value))

    def format_raw_data(self, seg, is_fallback):
        """This method present the segment bytes as a hex view, either because the
        segment couldn't be decoded or because the raw data was requested.
        """
        # is_fallback - the segment wasn't decoded, so the bytes are the only content
        #               there is and are always presented, regardless of --raw
        # self._raw   - the segment was decoded, and its bytes were asked for on top
        # neither     - the decoded fields are the whole output, nothing to add here
        if not (is_fallback or self._raw):
            return

        hex_list = []
        line_counter = 0
        dw_counter = 0
        seg.add_parsed_data("RAW DATA:")

        for dw in struct.unpack("{}I".format(len(seg.get_data()) // cs.DWORD_SIZE), seg.get_data()):
            hex_list.append('0x{0:0{1}X} '.format(dw, 8))
            dw_counter += 1

            if (dw_counter % self.RAW_DATA_DW_IN_ROW) == 0:
                self._add_raw_data_row(seg, line_counter, hex_list)
                line_counter += 1
                hex_list.clear()

        if len(hex_list) > 0:
            self._add_raw_data_row(seg, line_counter, hex_list)

    @classmethod
    def _add_raw_data_row(cls, seg, line_counter, hex_list):
        """This method add a single hex row, labeled by the dword indexes it holds.
        """
        first_dw = line_counter * cls.RAW_DATA_DW_IN_ROW
        if len(hex_list) > 1:
            label = "DWORD [{0}-{1}]".format(first_dw, first_dw + len(hex_list) - 1)
        else:
            label = "DWORD [{0}]".format(first_dw)
        seg.add_parsed_data("{0:<{1}}:{2}".format(label, cls.RAW_DATA_LABEL_WIDTH, ''.join(hex_list[:])))


FORMATTER_CLASSES[AdbBasicFormatter.FORMATTER_TYPE] = AdbBasicFormatter
