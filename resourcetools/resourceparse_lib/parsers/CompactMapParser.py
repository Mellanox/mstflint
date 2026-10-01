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

from resourceparse_lib.utils import constants as cs
from resourceparse_lib.utils.common_functions import is_resource_segment, valid_path_arg_type
from resourceparse_lib.utils.Exceptions import ResourceParseException
from resourceparse_lib.parsers.ResourceParser import ResourceParser, PARSER_CLASSES
from resourceparse_lib.formatters.AdbBasicFormatter import AdbBasicFormatter

import lzma
import struct


class CompactMapParser(ResourceParser):
    PARSER_TYPE = "cm"

    WARNING_COUNT_MISMATCH = " Number of data dwords ({0}) doesn't match the number of CSV addresses ({1})"
    WARNING_NON_DWORD_SIZE = " Segment size for compact-map parsing is not dword-aligned, {0} trailing byte(s) ignored"

    CSV_SUFFIX = ".csv"
    CSV_XZ_SUFFIX = ".csv.xz"

    value_struct = struct.Struct('I')

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = super().get_arg_parser(prog)

        required_named = arg_parser.add_argument_group('required arguments')
        required_named.add_argument("-c", "--csv-file", type=valid_path_arg_type, required=True,
                                    help='Location of the mstdump-style CSV file describing the addresses, '
                                         'either a "{0}" or a compressed "{1}" file'.format(cls.CSV_SUFFIX, cls.CSV_XZ_SUFFIX))

        return arg_parser

    @classmethod
    def get_supported_formatters(cls):
        # this parse method emits its own text, so only the basic formatter
        # (which yields that same output) is compatible for now
        return [AdbBasicFormatter.FORMATTER_TYPE]

    def __init__(self, parser_args, formatter):
        self._formatter = formatter
        self._load_addresses(parser_args.csv_file)

    @classmethod
    def _open_csv(cls, csv_file_path):
        """This method opens an mstdump database for reading as text, decompressing
        it when it is shipped compressed, the way the databases are installed.
        """
        if csv_file_path.endswith(cls.CSV_XZ_SUFFIX):
            return lzma.open(csv_file_path, 'rt')
        if csv_file_path.endswith(cls.CSV_SUFFIX):
            return open(csv_file_path, 'r')
        raise ResourceParseException("Unsupported CSV file '{0}', expected a '{1}' or a '{2}' file".format(
            csv_file_path, cls.CSV_SUFFIX, cls.CSV_XZ_SUFFIX))

    def _load_addresses(self, csv_file_path):
        """This method reads an mstdump-style CSV file and builds a flat list of
        byte addresses into self._addresses. Each non-comment line is
        'addr, size, enable_addr' where addr is a byte address and size is a
        number of dwords, both in mstdump notation - decimal, or hexadecimal
        with an '0x' prefix. Each entry is expanded to 'addr + 4*i' for i in
        range(size). The enable_addr column is ignored.
        """
        self._addresses = []
        stripped_line = ""
        try:
            with self._open_csv(csv_file_path) as csv_file:
                for line in csv_file:
                    stripped_line = line.strip()
                    if not stripped_line or stripped_line.startswith('#'):
                        continue
                    fields = stripped_line.split(',')
                    base_address = int(fields[0].strip(), 0)
                    size_in_dwords = int(fields[1].strip(), 0)
                    for i in range(size_in_dwords):
                        self._addresses.append(base_address + i * cs.DWORD_SIZE)
        except (IOError, OSError, lzma.LZMAError, UnicodeDecodeError) as e:
            raise ResourceParseException("Failed to read CSV file '{0}': {1}".format(csv_file_path, e))
        except (ValueError, IndexError) as e:
            raise ResourceParseException("Failed to parse CSV file '{0}', invalid line '{1}': {2}".format(
                csv_file_path, stripped_line, e))

    def parse_segment(self, segment):
        if is_resource_segment(segment.get_type()):
            data_start_position = cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW * cs.DWORD_SIZE
            payload_data = segment.get_data()[data_start_position:]

            remainder = len(payload_data) % cs.DWORD_SIZE
            if remainder > 0:
                segment.add_parsed_data("# Warning: {}".format(self.WARNING_NON_DWORD_SIZE.format(remainder)))
                payload_data = payload_data[:len(payload_data) - remainder]

            values = [value for (value,) in self.value_struct.iter_unpack(payload_data)]

            if len(values) != len(self._addresses):
                segment.add_parsed_data("# Warning: {}".format(
                    self.WARNING_COUNT_MISMATCH.format(len(values), len(self._addresses))))

            for address, value in zip(self._addresses, values):
                segment.add_parsed_data("0x{:08x} 0x{:08x}".format(address, value))

    def validate(self):
        return super().validate()

    @staticmethod
    def get_description():
        return \
            """        This parse method assumes that the provided resource-segments represent a flat stream
        of value dwords, and receives the matching addresses from an mstdump-style CSV file
        (see --csv-file). It outputs each address-value pair in a new line (similar to mstdump).
"""


PARSER_CLASSES[CompactMapParser.PARSER_TYPE] = CompactMapParser
