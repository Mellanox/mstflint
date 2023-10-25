# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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


#######################################################
#
# ResourceParser.py
# Created on:      26-Sep-2023 02:33:33 PM
# Original author: astrutsovsky
#
#######################################################

from resourceparse_lib.parsers.ResourceParser import ResourceParser, PARSER_CLASSES

import struct


class RawParser(ResourceParser):
    PARSER_TYPE = "raw"
    NUM_OF_DW_IN_ROW = 4
    SEGMENT_SEPARATOR = "-" * 43

    def __init__(self, parser_args):
        self._num_segments = parser_args.manager.get_num_dumped_segments()

    def get_title(self):
        return "Found {0} segments:".format(self._num_segments)

    def get_segment_separator(self):
        return self.SEGMENT_SEPARATOR

    def parse_segment(self, segment):
        rows = 0
        segment.add_parsed_data("Segment Type: {}".format(hex(segment.get_type())))
        segment.add_parsed_data("Segment Size: {} Bytes".format(len(segment.get_data())))
        segment.add_parsed_data("Segment Data:")
        line = ""
        for dw in struct.unpack("{}I".format(len(segment.get_data()) // 4), segment.get_data()):  # todo: use unpacked segment size instead
            line += '0x{0:0{1}X} '.format(dw, 8)
            rows += 1
            if rows == self.NUM_OF_DW_IN_ROW:
                segment.add_parsed_data(line)
                rows = 0
                line = ""
        if 0 < rows < self.NUM_OF_DW_IN_ROW:
            segment.add_parsed_data(line)

    @staticmethod
    def get_description():
        return \
            """        This parse method outputs the raw data of each segment in hex-view.
"""


PARSER_CLASSES[RawParser.PARSER_TYPE] = RawParser
