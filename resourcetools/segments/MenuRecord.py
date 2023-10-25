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
# MenuRecord.py
# Python implementation of the Class MenuRecord
# Original author: romany
#
#######################################################
import math
from resourcedump_lib.utils import constants as cs
from resourceparse_lib.utils.common_functions import reverse_string_endian
import struct
import sys


class MenuRecord:
    """This class responsible for managing the records of the menu segment and adjust it for printing
       a table for the user.
    """

    menu_record_struct = struct.Struct("HH16s16s16s")

    def __init__(self, rec_data):
        """initialize the class by set and parse the record data.
        """
        self.raw_data = rec_data
        props_bitfield, self.segment_type, self.segment_name, self.segment_index1_name, self.segment_index2_name = self.unpack_menu_record()
        props_str = '{:0b}'.format(props_bitfield).zfill(16)

        # self.segment_type = hex(int('{:0b}'.format(rec_data[cs.MENU_SEGMENT_TYPE_DWORD_LOCATION]).zfill(32)[16:32], 2))
        self.supports_index1 = int(props_str[15:16], 2)
        self.must_have_index1 = int(props_str[14:15], 2)
        self.supports_index2 = int(props_str[13:14], 2)
        self.must_have_index2 = int(props_str[12:13], 2)
        self.supports_num_of_obj1 = int(props_str[11:12], 2)
        self.must_have_num_of_obj1 = int(props_str[10:11], 2)
        self.supports_all_num_of_obj1 = int(props_str[9:10], 2)
        self.supports_active_num_of_obj1 = int(props_str[8:9], 2)
        self.supports_num_of_obj2 = int(props_str[7:8], 2)
        self.must_have_num_of_obj2 = int(props_str[6:7], 2)
        self.supports_all_num_of_obj2 = int(props_str[5:6], 2)
        self.supports_active_num_of_obj2 = int(props_str[4:5], 2)

        self.segment_name = self.segment_name.decode("utf-8").rstrip('\x00')
        self.segment_index1_name = self.segment_index1_name.decode("utf-8").rstrip('\x00')
        self.segment_index2_name = self.segment_index2_name.decode("utf-8").rstrip('\x00')

    # Down goes the code that represents the Menu Record in a pretty table format:
    #                                 EXAMPLE
    # __________________________________________________________________
    #
    #                 Segment Type - 0x1002 (RCV_BUFF)
    #
    # Dump Params                        Applicability    Special Values
    # --------------------------------   --------------   --------------
    # index1 (QPN)                       Mandatory        N/A
    # numOfObj1                          N/A              N/A
    # index2 (DS)                        Optional         N/A
    # numOfObj2                          Optional         All
    # __________________________________________________________________

    def unpack_menu_record(self):
        fields = self.menu_record_struct.unpack_from(self.raw_data)
        props_bitfield, segment_type = fields[:2] if sys.byteorder == 'big' else fields[1::-1]
        segment_name, segment_index1_name, segment_index2_name = fields[2:]
        if sys.byteorder == 'little':
            segment_name = reverse_string_endian(segment_name)
            segment_index1_name = reverse_string_endian(segment_index1_name)
            segment_index2_name = reverse_string_endian(segment_index2_name)
        return props_bitfield, segment_type, segment_name, segment_index1_name, segment_index2_name

    @staticmethod
    def _make_separating_line(new_line=False):
        """This method creates a string that the separation line ('____')"""
        line = cs.MENU_SEGMENT_TABLE_LINE_LEN * cs.MENU_SEGMENT_TABLE_WRAP
        if new_line:
            line += "\n"
        return line

    def _make_segment_type_line(self):
        """This method creates a string that represent segment type line to be printed"""
        line = cs.MENU_SEGMENT_TABLE_SEGMENT_TYPE + hex(self.segment_type) + " ({0})".format(self.segment_name) + "\n"
        padding = 0
        if len(line) < cs.MENU_SEGMENT_TABLE_LINE_LEN:
            padding = cs.MENU_SEGMENT_TABLE_LINE_LEN - len(line)
        line = " " * math.ceil((padding / 2)) + line + " " * round((padding / 2))
        return line

    @staticmethod
    def _make_table_header_line():
        """This method creates a string that represent the header in the table"""
        padding = cs.MENU_SEGMENT_TABLE_DUMP_PARAMS_LEN - len(
            cs.MENU_SEGMENT_TABLE_DUMP_PARAMS) + cs.MENU_SEGMENT_TABLE_GAP
        line = cs.MENU_SEGMENT_TABLE_DUMP_PARAMS + " " * padding
        padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(
            cs.MENU_SEGMENT_TABLE_APPLICABILITY) + cs.MENU_SEGMENT_TABLE_GAP
        line += cs.MENU_SEGMENT_TABLE_APPLICABILITY + " " * padding
        padding = cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES_LEN - len(cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES)
        line += cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES + " " * padding
        return line

    @staticmethod
    def _make_dashes_line():
        """This method creates a string that represent split line ('------') for the table"""
        line = cs.MENU_SEGMENT_TABLE_DASH * cs.MENU_SEGMENT_TABLE_DUMP_PARAMS_LEN
        padding = cs.MENU_SEGMENT_TABLE_GAP
        line += " " * padding
        line += cs.MENU_SEGMENT_TABLE_DASH * cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN
        line += " " * padding
        line += cs.MENU_SEGMENT_TABLE_DASH * cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES_LEN
        return line

    def _make_index_line(self, index_name, supports, must, table_index_line):
        """This method creates a string that represent indexX line to be printed"""
        line = table_index_line + " ({0})".format(index_name)
        padding = cs.MENU_SEGMENT_TABLE_DUMP_PARAMS_LEN - len(line) + cs.MENU_SEGMENT_TABLE_GAP
        line += " " * padding

        if not supports:
            padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_NA)
            applicability = cs.MENU_SEGMENT_TABLE_NA
        else:
            if must:
                padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_MANDATORY)
                applicability = cs.MENU_SEGMENT_TABLE_MANDATORY
            else:
                padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_OPTIONAL)
                applicability = cs.MENU_SEGMENT_TABLE_OPTIONAL

        applicability = applicability + " " * math.ceil(padding)
        line += applicability

        padding = cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES_LEN - len(cs.MENU_SEGMENT_TABLE_NA)
        special_values = cs.MENU_SEGMENT_TABLE_NA + " " * math.ceil(padding / 2)
        line += " " * cs.MENU_SEGMENT_TABLE_GAP
        line += special_values
        return line

    @staticmethod
    def _make_num_of_objs_line(supports, must, table_objs_line, al, active):
        """This method creates a string that represent numOfObjsX line to be printed"""
        line = table_objs_line
        padding = cs.MENU_SEGMENT_TABLE_DUMP_PARAMS_LEN - len(line) + cs.MENU_SEGMENT_TABLE_GAP
        line += " " * padding

        if not supports:
            padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_NA)
            applicability = cs.MENU_SEGMENT_TABLE_NA
        else:
            if must:
                padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_MANDATORY)
                applicability = cs.MENU_SEGMENT_TABLE_MANDATORY
            else:
                padding = cs.MENU_SEGMENT_TABLE_APPLICABILITY_LEN - len(cs.MENU_SEGMENT_TABLE_OPTIONAL)
                applicability = cs.MENU_SEGMENT_TABLE_OPTIONAL

        applicability = applicability + " " * math.ceil(padding)
        line += applicability

        special_values = ""
        if al:
            special_values = cs.MENU_SEGMENT_TABLE_ALL
        if active:
            if special_values:
                special_values += cs.MENU_SEGMENT_TABLE_AND
            special_values += cs.MENU_SEGMENT_TABLE_ACTIVE
        if not special_values:
            special_values = cs.MENU_SEGMENT_TABLE_NA
        padding = cs.MENU_SEGMENT_TABLE_SPECIAL_VALUES_LEN - len(special_values)

        special_values = special_values + " " * math.ceil(padding / 2)
        line += " " * cs.MENU_SEGMENT_TABLE_GAP
        line += special_values
        return line

    def convert_record_obj_to_printable_list(self):
        """This method creates a list of formatted strings that represents the record object """
        printable = []
        printable.append(self._make_separating_line(new_line=True))
        printable.append(self._make_segment_type_line())
        printable.append(self._make_table_header_line())
        printable.append(self._make_dashes_line())
        printable.append(self._make_index_line(self.segment_index1_name, self.supports_index1, self.must_have_index1,
                                               cs.MENU_SEGMENT_TABLE_INDEX1))
        printable.append(self._make_num_of_objs_line(self.supports_num_of_obj1, self.must_have_num_of_obj1,
                                                     cs.MENU_SEGMENT_TABLE_NUM_OF_OBJS1, self.supports_all_num_of_obj1,
                                                     self.supports_active_num_of_obj1))
        printable.append(self._make_index_line(self.segment_index2_name, self.supports_index2,
                                               self.must_have_index2, cs.MENU_SEGMENT_TABLE_INDEX2))
        printable.append(self._make_num_of_objs_line(self.supports_num_of_obj2, self.must_have_num_of_obj2,
                                                     cs.MENU_SEGMENT_TABLE_NUM_OF_OBJS2, self.supports_all_num_of_obj2,
                                                     self.supports_active_num_of_obj2))
        printable.append(self._make_separating_line())
        return printable
