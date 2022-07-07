# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
# Author:  Ahmed Awwad     ahmadaw@mellanox.com    Created: 2019-Jan

import binascii


class BinaryFile(object):
    """
    Binary File class is dealing with r/w of binary files
    """
    def __init__(self, file_path):
        self._file_path = file_path

    def read_byte(self, offset):
        """
        Read 1B from the pci configuration
        """
        return self.read(1, offset)[0]

    def read_word(self, offset):
        """
        Read 2B for the pci configuration
        """
        bytes_list = self.read(2, offset)
        if bytes_list != []:
            byte0 = "{0:x}".format(bytes_list[0]).zfill(2)
            byte1 = "{0:x}".format(bytes_list[1]).zfill(2)
            return int("{0}{1}".format(byte1, byte0), 16)
        else:
            return None

    def read_long(self, offset):
        """
        Reads 4B from the pci configuration
        """
        bytes_list = self.read(4, offset)
        if bytes_list != []:
            byte0 = "{0:x}".format(bytes_list[0]).zfill(2)
            byte1 = "{0:x}".format(bytes_list[1]).zfill(2)
            byte2 = "{0:x}".format(bytes_list[2]).zfill(2)
            byte3 = "{0:x}".format(bytes_list[3]).zfill(2)
            return int("{0}{1}{2}{3}".format(byte3, byte2, byte1, byte0), 16)
        else:
            return None

    def read(self, size, offset=0, skip_offset_list=None):
        """
        Read a given binary file and return the output as a string in hex representation
        Skip-list is a list of addresses the function need to skip. The function will insert '00' on every address that is skipped
        Example read(size=10, offset=0, skip_offset_list=[0x5]) will read from address 0x0 to address 0x9 and replace address 0x5 with '00'
        """
        try:
            with open(self._file_path, "rb") as f:
                if skip_offset_list:
                    data = binascii.unhexlify("")          # Initialization
                    zero_binary = binascii.unhexlify("00")  # Initialization
                    offset_interval = self._get_read_intervals(skip_offset_list, offset, size)
                    for interval_start, interval_size in offset_interval:
                        if interval_size:  # read interval
                            f.seek(interval_start)
                            data += f.read(interval_size)
                        else:  # add '00' to data
                            data += zero_binary
                else:
                    f.seek(offset)
                    data = f.read(size)
        except Exception as err:
            raise RuntimeError("Failed to parse file: {0} for reading. ERROR: {1}".format(self._file_path, err))
        data = binascii.hexlify(data)
        bytes_as_string = self.chunkstring(data, 2)
        bytes_list = []
        for byte in bytes_as_string:
            if byte != "":
                bytes_list.append(int(byte, 16))
            else:
                bytes_list.append(None)
        return bytes_list

    @staticmethod
    def _get_read_intervals(skip_offset_list, offset, size):
        """
        The method prepare the skip list in order to read a range and skipping on some (dangerous) offsets
        The method return list of tuples
        Example , offset:0, size:10, skiplist=[4, 5]
        The function return [(0, 4),(4, 0), (5, 0) (6, 10)]  when each item is (start, size)
        when size is 0 it means we need to skip this offset
        """
        # remove out of range skip addresses
        for skip_offset in skip_offset_list:
            if skip_offset not in range(offset, size + 1):
                skip_offset_list.remove(skip_offset)
        read_interval_set = set(skip_offset_list)
        # Add offset, offset+size to skip_list
        read_interval_set.add(offset - 1)
        read_interval_set.add(offset + size)

        read_interval_list = sorted(list(read_interval_set))

        result = []
        for start, end in zip(read_interval_list[:-1], read_interval_list[1:]):
            interval_start = start + 1
            interval_end = end
            result.append((interval_start, interval_end - interval_start))   # interval
            result.append((interval_end, 0))                       # skip interval

        result = result[:-1]                               # remove the last tuple (offset+size, 0)
        return sorted(set(result))

    def write(self, bytes_list, size, offset=0):
        """
        A method  to write data to a binary file
        data is a list of values
        """
        data_to_write = ""
        for byte in bytes_list:
            data_to_write += "{0:x}".format(byte).zfill(2)
        if len(data_to_write) > size * 2:
            raise RuntimeError("Failed to write data {0} invalid size".format(data_to_write))
        bin_data = binascii.unhexlify(data_to_write)  # Return the binary data represented by the hexadecimal string
        try:
            with open(self._file_path, "wb") as f:
                f.seek(offset)
                f.write(bin_data)
        except Exception as e:
            raise RuntimeError("Failed writing to a file: {0}. ERROR: {1}".format(self._file_path, e))

    def chunkstring(self, string, length):
        """
        Chunks the string to list of strings in the given length
        """
        return (string[0 + i:length + i] for i in range(0, len(string), length))
