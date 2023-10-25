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

from resourceparse_lib.utils import constants as cs
from resourceparse_lib.utils.common_functions import calculate_aligned_offset, is_resource_segment, valid_path_arg_type
from resourceparse_lib.utils.Exceptions import ResourceParseException
from resourceparse_lib.parsers.ResourceParser import ResourceParser, PARSER_CLASSES
from resourceparse_lib.parsers.AdbParser import AdbParser
import os
import re
import math
import struct


class AdbResourceParser(ResourceParser):
    PARSER_TYPE = "adb"

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = super().get_arg_parser(prog)

        required_named = arg_parser.add_argument_group('required arguments')
        required_named.add_argument("-a", "--adb-file", type=valid_path_arg_type, required=True, help='Location of the ADB file')

        optional_named = arg_parser.add_argument_group('optional arguments')
        optional_named.add_argument("-r", "--raw", action="store_true", help='Prints the raw data in addition to the parsed data')

        return arg_parser

    @staticmethod
    def get_description():
        return \
            """        This parse method receives an adb file and parses each segment data
        according to the adb layout of the node with segment_id attribute corresponds to the segment
"""

    def __init__(self, parser_args):
        self._adb_file_path = parser_args.adb_file
        self._adb_obj = AdbParser(self._adb_file_path)
        self._segment_map = self._adb_obj.segment_id_nodes_dict
        self._raw = parser_args.raw
        self._manager = parser_args.manager

    # Segment Parsing

    def get_title(self):
        return "Parse {0} segments:".format(self._manager.get_num_dumped_segments())

    def get_segment_separator(self):
        return cs.DATA_PRINTER_SEPARATOR

    def parse_segment(self, seg):
        """This method responsible for the parsing algorithm that take the raw data of
        each segment and generate his content according the adb map
        """

        seg_for_parse = False
        if seg.get_type() in self._segment_map:
            segment_name = self._build_union_prefix(self._segment_map[seg.get_type()].nodeDesc) \
                + self._segment_map[seg.get_type()].name
            if not self._is_seg_size_match_adb_seg_size(len(seg.get_data()), seg.get_type()):
                seg.add_parsed_data("Warning:{}".format(cs.WARNING_SIZE_DOESNT_MATCH.format(
                    len(seg.get_data()) - cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW,
                    math.ceil(self._segment_map[seg.get_type()].size / 32))))
            seg_for_parse = True
        else:
            # reference segment is missing in the adb (this will help the user understand the type)
            if seg.get_type() == cs.RESOURCE_DUMP_SEGMENT_TYPE_REFERENCE:
                segment_name = "segment_reference"
            else:
                segment_name = "UNKNOWN"

        seg.add_parsed_data(20 * " " + "Segment - {0} ({1:#06x}){2}".format(segment_name, seg.get_type(), seg.additional_title_info()))

        if is_resource_segment(seg.get_type()):
            data_start_position = cs.RESOURCE_SEGMENT_START_OFFSET_IN_BYTES
        else:
            data_start_position = 0

        # offset is in bits so converting is to bit array and store it at a member is better then pass it as an argument
        # for a recursive method
        bytes_array = seg.get_data('big')[data_start_position:]
        self._current_bit_array = ''.join(format(x, '08b') for x in bytes_array)

        if seg_for_parse:
            segment_layout_layout = self._segment_map[seg.get_type()]
            segment_parse_method = segment_layout_layout.parse_method
            if segment_parse_method == 'adb':
                for field in self._segment_map[seg.get_type()].subItems:
                    if field.nodeDesc and field.nodeDesc.isUnion and field.uSelector:
                        self._parse_union_selector_field(field, seg)
                    else:
                        prefix = self._build_union_prefix(field.nodeDesc)
                        self._parse_seg_field(field, prefix + field.name, 0, seg)
                if self._raw:
                    self._build_and_add_raw_data(seg)
            else:
                segment_resource_parser = PARSER_CLASSES.get(segment_parse_method)
                if segment_resource_parser:
                    segment_resource_parser([]).parse_segment(seg)
                else:
                    self._build_and_add_raw_data(seg)
        else:  # if segment not for parse, need to set raw data
            self._build_and_add_raw_data(seg)
        seg._parsed_data.extend(seg.get_messages())

    @classmethod
    def _build_and_add_raw_data(cls, seg):
        """This method build the raw data in the right format and add it to the
        parsed data of the segment.
        """
        hex_list = []
        line_counter = 0
        dw_counter = 0
        seg.add_parsed_data("RAW DATA:")

        for dw in struct.unpack("{}I".format(len(seg.get_data()) // 4), seg.get_data()):
            hex_list.append('0x{0:0{1}X} '.format(dw, 8))
            dw_counter += 1

            if (dw_counter % cs.PARSER_NUM_OF_DW_IN_ROW) == 0:
                seg.add_parsed_data("{:<15}:{}".format("DWORD [{0}-{1}]".format(line_counter * 4, (line_counter * 4) + (len(hex_list) - 1)), ''.join(hex_list[:])))
                line_counter += 1
                hex_list.clear()

        if len(hex_list) > 1:
            seg.add_parsed_data("{:<15}:{}".format("DWORD [{0}-{1}]".format(line_counter * 4, (line_counter * 4) + (len(hex_list) - 1)), ''.join(hex_list[:])))
        elif len(hex_list) == 1:
            seg.add_parsed_data("{:<15}:{}".format("DWORD [{0}]".format(line_counter * 4), ''.join(hex_list[:])))

    @classmethod
    def _build_union_prefix(cls, node_desc):
        """This method build the prefix for the struct in order to give the user
        information indicate if the node is a union
        """
        if not node_desc:
            prefix = ""
        else:
            if node_desc.isUnion:
                prefix = "(UNION)"
            else:
                prefix = ""
        return prefix

    def _is_seg_size_match_adb_seg_size(self, seg_size, seg_type):
        """This method check if the dumped segment size is same like in the ADB definitions.
        """
        adb_seg_size = math.ceil(self._segment_map[seg_type].size / 8)
        dumped_data_size = seg_size
        # first 4 dw's at the resource segment is not a part of the ADB definition so we not consider them
        if is_resource_segment(seg_type):
            dumped_data_size -= cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW * cs.DWORD_SIZE
        if adb_seg_size != dumped_data_size:
            return False
        return True

    def _parse_union_selector_field(self, field, seg):
        """This method parse union field and present only the relevant field
        (selected by the selector)
        """
        union_field_offset = calculate_aligned_offset(field.uSelector.offset, field.uSelector.size)
        selected_field_enum = field.uSelector.dict[int(self._current_bit_array[union_field_offset:union_field_offset + field.uSelector.size], 2)]
        for item in field.subItems:
            if item.attrs['selected_by'] == selected_field_enum:
                self._parse_seg_field(item, item.name, 0, seg)

    def _parse_seg_field(self, field, field_str, offset_shift, seg):  # offset_shift is 0 unless parsing a sub-tree of varaible-size arrays
        """This method is a recursive method that build the inner fields
        """
        try:
            if field.condition and not field.condition.evaluate(self._current_bit_array):
                return
        except ResourceParseException as rpe:
            seg.add_parsed_data("Warning:{}".format(cs.WARNING_FAILED_EVAL_CONDITION.format(str(rpe), field_str)))

        num_unlimited_elements = 1
        if field.is_unlimited_array:
            unlimited_array_start_offset = calculate_aligned_offset(field.offset, field.size)
            segment_remainder_size = len(self._current_bit_array) - unlimited_array_start_offset
            num_unlimited_elements = segment_remainder_size // field.size

        for i in range(num_unlimited_elements):
            array_suffix = "[" + str(i) + "]" if field.is_unlimited_array else ""
            element_field_str = field_str + array_suffix
            element_offset_shift = offset_shift + field.size * i

            if field.enum_dict:
                self._parse_enum_field(field, element_field_str, element_offset_shift, seg)

            elif len(field.subItems) > 0:
                for sub_field in field.subItems:
                    prefix = self._build_union_prefix(sub_field.nodeDesc)
                    self._parse_seg_field(sub_field, element_field_str + "." + prefix + sub_field.name, element_offset_shift, seg)
            else:
                field_offset = calculate_aligned_offset(field.offset + element_offset_shift, field.size)
                if len(self._current_bit_array) >= (field_offset + field.size):
                    value = hex(int(self._current_bit_array[field_offset:field_offset + field.size], 2))
                    if ("printf" in field.attrs):
                        value = self._parse_printf_format(value, field.attrs["printf"])
                    seg.add_parsed_data("{} = {}".format(element_field_str, value))

    def _parse_enum_field(self, field, field_str, offset_shift, seg):
        """This method parse enum field and present the enum name as well as the enum value.
        """
        field_offset = calculate_aligned_offset(field.offset + offset_shift, field.size)
        enum_value = int(self._current_bit_array[field_offset:field_offset + field.size], 2)
        if len(self._current_bit_array) >= (field_offset + field.size):
            if enum_value in field.enum_dict:
                seg.add_parsed_data("{} = ({} = {})".format(field_str, field.enum_dict[enum_value], hex(enum_value)))
            else:
                seg.add_parsed_data("{} = {}".format(field_str, hex(enum_value)))

    def _parse_printf_format(self, value, format):
        """ Enables specifying how a field should be dumped
            %d - dump field as decimal
            %x – dump field as hexadecimal
            %b - dump field as binary
            %s – dump field as ASCII tex"""

        cases = ['d', 'x', 'b', 's']
        new_val = ''
        tmp_val = value.split("0x")[1]
        str_list = []
        str_list[:0] = format

        for i, c in enumerate(str_list):
            f = ""
            if (i + 1 < len(str_list)):
                if (c == '%' or c + str_list[i + 1] == '0x' or c + str_list[i + 1] == c + 'x'):
                    if (c == '%' and str_list[i + 1] in cases):
                        f = c + str_list[i + 1]
                        del str_list[i]
                    if (i + 1 < len(str_list)):
                        if (c + str_list[i + 1] == '0x'):
                            new_val += '0x'
                            del str_list[i]
                    if (f == '%d'):
                        new_val += str(int(tmp_val, 16))
                    if (f == '%x'):
                        new_val += str(tmp_val)
                    if (f == '%b'):
                        new_val += str(bin(int(tmp_val, 16)).replace("0b", ""))
                    if (f == '%s'):
                        new_val += str(tmp_val)
                    if (i + 2 < len(str_list)):
                        if (c + str_list[i + 1] + str_list[i + 2] == '%' + str_list[i + 1] + 'x'):
                            new_val += (int(str_list[i + 1]) - 1) * ' ' + str(tmp_val)
                            for _ in range(2):
                                del str_list[i]
                    if (i + 2 < len(str_list)):
                        if (c + str_list[i + 1] + str_list[i + 2] == '%' + str_list[i + 1] + str_list[i + 2] and str_list[i + 1].isdigit()):
                            new_val += (int(str_list[i + 2]) - 1) * '0' + str(tmp_val)
                            for _ in range(3):
                                del str_list[i]
                else:
                    new_val += c
            else:
                new_val += c

        return new_val

    # Validation

    def validate(self):
        self._validate_adb_version_with_notice(self._adb_file_path)

    def _validate_adb_version_with_notice(self, adb_file_path):
        """This method perform the fw version validation stages and send a proper notice msg
        if needed.
        """
        adb_name = os.path.splitext(os.path.basename(adb_file_path))[0]
        if self._is_adb_name_in_version_format(adb_name):
            adb_fw_version = self._retrieve_adb_version_from_valid_format(adb_name)
            dump_fw_version = self._manager.retrieve_adb_version_from_info_segment()
            if adb_fw_version != dump_fw_version:
                # self._get_next_notice_counter() todo: return this mechanism
                self._manager._printer.print_notice_before_parse("Notice - {0}".format(
                    "adb fw version {0} is used for parsing while dump fw version is {1}".format(adb_fw_version,
                                                                                                 dump_fw_version)))
        else:
            # self._get_next_notice_counter() todo: return this mechanism
            self._manager._printer.print_notice_before_parse(
                "Notice - {0}".format("Adb name is not according the version format, can't validate adb fw version"))

    @classmethod
    def _is_adb_name_in_version_format(cls, adb_name):
        """This method check if the adb file name has the version format define by arch.
        """
        match = re.fullmatch("fw-[0-9]+-rel-[0-9]{2}_[0-9]{2}_[0-9]{4}", adb_name)
        if match is not None:
            if match.string == adb_name:
                return True
        return False

    @classmethod
    def _retrieve_adb_version_from_valid_format(cls, adb_name):
        """This method extract the fw_version from the file name assuming that
        file already checked and has the right version format.
        """
        version = re.findall("[0-9]{2}_[0-9]{2}_[0-9]{4}", adb_name)[0]
        version_list = version.split("_")
        return "{0}.{1}.{2}".format(version_list[0], version_list[1], version_list[2])

    def _get_next_warning_counter(self):  # todo: return this mechanism
        """This method return get the next free index to help generate
         the a uniq key for the warning msg.
        """
        return 5


PARSER_CLASSES[AdbResourceParser.PARSER_TYPE] = AdbResourceParser
