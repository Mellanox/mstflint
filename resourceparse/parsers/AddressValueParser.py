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
# Created on:      12-Jun-2023 11:13:33 AM
# Original author: astrutsovsky
#
#######################################################

from utils import constants as cs
from utils.common_functions import calculate_aligned_offset, is_resource_segment
from parsers.ResourceParser import ResourceParser, PARSER_CLASSES


class AddressValueParser(ResourceParser):
    def __init__(self, parser_args):
        pass

    def parse_segment(self, segment):
        if is_resource_segment(segment.get_type()):
            data_start_position = cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW
            dword_array = segment.get_data()[data_start_position:]

            num_pairs = len(dword_array)
            remainder = num_pairs % 2

            if remainder > 0:
                segment.add_parsed_data("# Warning: {}".format(cs.WARNING_WRONG_PAIR_SIZE))

            for i in range(0, num_pairs - remainder, 2):
                segment.add_parsed_data("0x{:08x} 0x{:08x}".format(dword_array[i], dword_array[i + 1]))

    def validate(self):
        return super().validate()

    @staticmethod
    def get_description():
        return \
            """        This parsing method assumes that the provided resource-segments represents a memory map
        by dword pairs of address-value, and outputs each pair in a new line (similar to mstdump).
"""


PARSER_CLASSES["map"] = AddressValueParser
