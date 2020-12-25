# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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

# Python Imports
import os
import pickle
import tempfile
import platform
import subprocess

# Common Imports
from binary_file import BinaryFile
from mft_logger import LoggerFactory

# Common Constant
CONFIG_SPACE_PTR_OFFSET = 0X34
MAXIMUN_LEGACY_CAP_SIZE = 0x100
MAX_PCI_OFFSET = 0xfff
MELLANOX_PCI_SKIP_LIST = [0x58, 0x5c] # it is harmful for the device to read offset 0x58 and 0x5c for example
VENDOR_ID_ADDR = 0X0
DEVICE_ID_ADDR = 0x2
# Legacy Capabilities
CAP_PCI_EXPRESS= 0x10
CAP_MSI = 0x05
CAP_MSI_X = 0x11
CAP_POWER_MANAGEMENT = 0x01
CAP_VPD = 0x03
CAP_VSC = 0x09
# Key:ID, value:size
CAP_LEGACY_DICT = {CAP_PCI_EXPRESS: 0x3c,
                   CAP_MSI: 0x10,
                   CAP_MSI_X: 0x8,
                   CAP_POWER_MANAGEMENT: 0x8
                   }
# Extended Capabilities
CAP_AER = 0X1
CAP_ARI = 0X0e
CAP_SRIOV = 0x10
CAP_SECONDRY_PCI_EXPRESS = 0x19
CAP_PHYSICAL_LAYER_GEN4 = 0x26
CAP_DPC= 0x1d
CAP_ACS = 0xd
CAP_ATS = 0xf    
# Key:ID, value:size
CAP_EXTENDED_DICT = {CAP_AER: 0x48,
                    CAP_SRIOV: 0x40,
                    CAP_SECONDRY_PCI_EXPRESS: 0x10,
                    CAP_PHYSICAL_LAYER_GEN4: 0x40,
                    CAP_DPC: 0x40,
                    CAP_ATS: 0x8
                   }

class NotSupportedDeviceException(Exception):
    pass

class PCIDeviceBase(object):
    """
    Base class that represent a PCI device
    """
    def __init__(self, dbdf, debug_level="critical"):
        """
        """
        self.dbdf = dbdf
        self.logger = LoggerFactory().get('mlxpci',debug_level)

        temp_dir = tempfile.gettempdir()
        self.dump_file_path = os.path.join(temp_dir, "{0}.pkl".format(str(self.dbdf)))

        self._pci_conf_space = {} # <capability-id> : <value:integer>
        self._pci_express_offset = None
    
    def read(self, offset, size, skip_offset_list=None):
        """
        Read from PCI configuration space
        skip_offset_list is a list of offsets to skip reading for some offsets
        """
        if self._is_valid_range(offset, size) is False: 
            raise Exception("offset [{0}] with size {1} is not a valid offset to read from.".format(offset, size))
        self.logger.debug("Reading offset[{0}] with size [{1}] for PCI device[{2}]".format(offset, size, self.dbdf))
        
    def write(self, offset, size, bytes_list):
        """
        Write to PCI configuration space
        """
        if self._is_valid_range(offset, size) is False:
            raise Exception("offset [{0}] with size {1} is not a valid offset to write.".format(offset, size))
        self.logger.debug("Writing [{0}] on  offset[{1}]  for PCI device[{2}]".format(bytes_list, offset, self.dbdf))
    
    def save_configuration_space(self, to_file=False):
        """
        Save PCI configuration space of the device
        """
        self.logger.debug("Saving configurations for PCI device[{0}]".format(self.dbdf))
        visited_capabilities = [] # A variable to save the visited capability to avoid an infinite loop

        # read and save PCI header 0x0-0x3f
        self.logger.debug("Reading and saving pci header [0x0-0x3f] ...")
        self._pci_conf_space["pci_header"] = self.read(0x0, 0x40)
        
        self.logger.debug("Reading and saving legacy list ...")
        pci_legacy_ptr =  self.read_byte(CONFIG_SPACE_PTR_OFFSET)
        while pci_legacy_ptr != 0:
            assert 0 < pci_legacy_ptr < MAXIMUN_LEGACY_CAP_SIZE, "Legacy pointer (<{0:#x}>) is out of range".format(pci_legacy_ptr)
            capability_id =  self.read_byte(pci_legacy_ptr)
            if capability_id in CAP_LEGACY_DICT:
                if capability_id in visited_capabilities:
                    raise RuntimeError("Capability id {0} was seen before (avoid infinite loop).".format(capability_id)) 
                cap_size = CAP_LEGACY_DICT[capability_id]
                self._pci_conf_space["{0}_leg".format(capability_id)] = self.read(pci_legacy_ptr,  cap_size)
                visited_capabilities.append(capability_id)
            pci_legacy_ptr = self.read_byte(pci_legacy_ptr + 1)

        self.logger.debug("Reading and saving extended list ...")
        pci_extended_ptr = MAXIMUN_LEGACY_CAP_SIZE
        visited_capabilities = []
        while pci_extended_ptr and pci_extended_ptr != 0xfff: # Reading PCI Extended Configurations on VM will return 0XFFF For FBSD
            assert pci_extended_ptr >= MAXIMUN_LEGACY_CAP_SIZE, "Extended pointer (<{0:#x}>) is out of range".format(pci_extended_ptr)
            capability_id = self.read_word(pci_extended_ptr)
            if capability_id is None: # Reading PCI Extended Configurations on VM will return None
                break
            if capability_id in CAP_EXTENDED_DICT:
                if capability_id in visited_capabilities:
                    raise RuntimeError("Capability id {0} was seen before (avoid infinite loop).".format(capability_id))
                cap_size = CAP_EXTENDED_DICT[capability_id]
                self._pci_conf_space["{0}_ext".format(capability_id)] = self.read(pci_extended_ptr, cap_size)
                visited_capabilities.append(capability_id)
            pci_extended_ptr = self.read_word(pci_extended_ptr + 2) >> 4

        if to_file:
            self.logger.debug("Save PCI configuration space to a file ...")
            with open(self.dump_file_path, 'wb') as f:
                pickle.dump(self._pci_conf_space, f, pickle.HIGHEST_PROTOCOL)
            self.logger.debug("PCI Configuration space dict {0} saved to a file {1}".format(self._pci_conf_space, self.dump_file_path))
            self._pci_conf_space = {}
        self.logger.info("PCI Configurations for [{0} was saved successfully]".format(self.dbdf))
    
    def restore_configuration_space(self):
        """
        Restore PCI configuration space of the device
        """
        self.logger.debug("Restoring configurations for PCI device[{0}]".format(self.dbdf))
        if self._pci_conf_space == {}:
            self._pci_conf_space = self._get_pci_conf_from_file()

        visited_capabilities = [] # Save the visited capability to avoid infinit loop

        # Read and save PCI configuration space offset from 0x0-0xfff
        # Reading the pci conf space one time to have better performance
        cached_data = self.read(offset=0x0, size=MAX_PCI_OFFSET, skip_offset_list=MELLANOX_PCI_SKIP_LIST)
        # write pci header 0x0-0x3f
        self.logger.debug("Writing PCI header [0x0-0x3f] ...")
        self.write(0x0, 0x40,  self._pci_conf_space["pci_header"])

        # Write Legacy list
        self.logger.debug("Writing back Legacy list ...")
        pci_legacy_ptr =  self._fetch_byte(cached_data, CONFIG_SPACE_PTR_OFFSET)
        while pci_legacy_ptr:
            assert 0 < pci_legacy_ptr < MAXIMUN_LEGACY_CAP_SIZE, "Legacy pointer (<{0:#x}>) is out of range".format(pci_legacy_ptr)
            capability_id = self._fetch_byte(cached_data, pci_legacy_ptr)
            if capability_id in CAP_LEGACY_DICT and "{0}_leg".format(capability_id) in self._pci_conf_space:
                if capability_id in visited_capabilities:
                    raise RuntimeError("Capability id {0} was seen before (avoid infinite loop).".format(capability_id))
                cap_size = CAP_LEGACY_DICT[capability_id]
                self.write(pci_legacy_ptr, cap_size, self._pci_conf_space["{0}_leg".format(capability_id)])
                visited_capabilities.append(capability_id)
            pci_legacy_ptr = self._fetch_byte(cached_data, pci_legacy_ptr + 1)

        # Write Extended list
        self.logger.debug("Writing back Extended list ...")
        pci_extended_ptr = MAXIMUN_LEGACY_CAP_SIZE
        visited_capabilities = []
        while pci_extended_ptr and pci_extended_ptr != 0xfff:
            assert pci_extended_ptr >= MAXIMUN_LEGACY_CAP_SIZE, "Extended pointer (<{0:#x}>) is out of range".format(pci_extended_ptr)
            capability_id = self._fetch_word(cached_data, pci_extended_ptr)
            if capability_id is None: # Reading PCI Extended Configurations on VM will return None
                break
            if capability_id in CAP_EXTENDED_DICT and "{0}_ext".format(capability_id) in self._pci_conf_space:
                if capability_id in visited_capabilities:
                    raise RuntimeError("Capability id {0} was seen before (avoid infinite loop).".format(capability_id))
                cap_size = CAP_EXTENDED_DICT[capability_id]
                self.write(pci_extended_ptr, cap_size, self._pci_conf_space["{0}_ext".format(capability_id)])
                visited_capabilities.append(capability_id)
            pci_extended_ptr = self._fetch_word(cached_data, pci_extended_ptr + 2) >> 4
            
        self.logger.info("PCI Configurations for [{0} was restored successfully]".format(self.dbdf))
    
    def _is_valid_range(self, offset, size):
        """
        A method to validate offset and size
        it returns True if the offset is valid, else False
        """
        return (offset + size <= 0xfffe)
    
    def _is_valid_device(self):
        """
        Checks if the device is valid or not
        """
        self._vendor_id = self.read_word(VENDOR_ID_ADDR)
        self._dev_id = self.read_word(DEVICE_ID_ADDR)
        if self._vendor_id == 0xffff and self._dev_id == 0xffff:
            return False
        return True
    
    def _get_pci_express_offset(self):
        """
        Get PCI express offset
        """
        visited_capabilities = []
        pci_legacy_ptr =  self.read_byte(CONFIG_SPACE_PTR_OFFSET)
        while pci_legacy_ptr != 0:
            assert 0 < pci_legacy_ptr < MAXIMUN_LEGACY_CAP_SIZE, "Legacy pointer (<{0:#x}>) is out of range".format(pci_legacy_ptr)
            capability_id =  self.read_byte(pci_legacy_ptr)
            if capability_id == 0x10:
                return pci_legacy_ptr
            if capability_id in CAP_LEGACY_DICT:
                if capability_id in visited_capabilities:
                    raise RuntimeError("Capability id {0} was seen before (avoid infinite loop).".format(capability_id)) 
                visited_capabilities.append(capability_id)
            pci_legacy_ptr = self.read_byte(pci_legacy_ptr + 1)
        raise RuntimeError("Failed to find pci express offset")

    @property
    def dll_link_active(self):
        """
        Get dll link active value
        """
        link_status_reg_offset = 0x12
        link_status_reg_address = self._pci_express_offset + link_status_reg_offset
        link_status_reg_value = self.read_word(link_status_reg_address)
        dll_value_bin = bin(link_status_reg_value).replace('0b', '').zfill(16)[-13-1]  #bit 13
        return int(dll_value_bin)

    @property
    def dll_link_active_reporting_capable(self):
        """
        return Link-capabilites[dll-link-active-reporting-capbale] bit (indicates if dll-link-active is valid)
        """
        link_capabilities_reg_offset = 0xc
        link_capabilities_reg_address = self._pci_express_offset + link_capabilities_reg_offset
        link_capabilities_reg_value = self.read_long(link_capabilities_reg_address)
        dll_reporting_cable_bin = bin(link_capabilities_reg_value).replace('0b', '').zfill(32)[-20-1]  #bit 20
        return int(dll_reporting_cable_bin)

    # Helper methods
    ################
    def _fetch_byte(self, cached_pci_conf, offset):
        """
        Helper method that extract a byte from a data that was read before
        """
        return cached_pci_conf[offset]

    def _fetch_word(self, cached_pci_conf, offset):
        """
        Helper method that extract a word from a data that was read before
        """
        if offset + 1 < len(cached_pci_conf): # Device does not have extended PCI configurationfor VMs
            byte0 = "{0:x}".format(cached_pci_conf[offset]).zfill(2)
            byte1 = "{0:x}".format(cached_pci_conf[offset + 1]).zfill(2)
            return int("{0}{1}".format(byte1, byte0), 16)
        else:
            return None

    def _get_pci_conf_from_file(self):
        """
        This is to load pci conf space from a saved pickle
        """
        self.logger.debug("Reading pci space conf from [{0}]".format(self.dump_file_path))
        try:
            with open(self.dump_file_path, 'rb') as f:
                return pickle.load(f)
        except Exception:
            raise RuntimeError(
                "{0} doesn't exist. Please save before load".format(self.dump_file_path))


class LinuxPCIDevice(PCIDeviceBase):
    """
    PCI device for Linux
    """
    PCI_CONF_FILE_BASE_PATH = "/sys/bus/pci/devices"
    def __init__(self, dbdf, debug_level="critical"):
        super(LinuxPCIDevice, self).__init__(dbdf, debug_level)
        self._pci_conf_file = "{0}/{1}/config".format(LinuxPCIDevice.PCI_CONF_FILE_BASE_PATH, self.dbdf)
        self._bin_file = BinaryFile(self._pci_conf_file)
        if self._is_valid_device() == False:
            self.logger.debug("Device is not supported to save/load pci configurations")
            raise NotSupportedDeviceException("Device is not supported to save/load pci configurations")
        self._pci_express_offset = self._get_pci_express_offset()

    def read(self, offset, size, skip_offset_list=None):
        super(LinuxPCIDevice, self).read(offset, size, skip_offset_list)
        try:
            return self._bin_file.read(offset=offset, size=size, skip_offset_list=skip_offset_list)
        except Exception as e:
            raise RuntimeError("Failed to read offset [{0}] with size [{1}] for PCI device [{2}]. Error is [{3}]".format(offset, size, self.dbdf, e))
    
    def read_byte(self, offset):
        return self._bin_file.read_byte(offset)
    
    def read_word(self, offset):
        assert offset % 2 == 0, "Offset should be aligned to 2"
        return self._bin_file.read_word(offset)

    def read_long(self, offset):
        assert offset % 4 == 0, "Offset should be aligned to 4"
        return self._bin_file.read_long(offset)

    def write(self, offset, size, bytes_list):
        super(LinuxPCIDevice, self).write(offset, size, bytes_list)
        self._bin_file.write(bytes_list=bytes_list, offset=offset, size=size)
        self.logger.debug("Data was Written [{0}] to  offset[{1}] for PCI device [{2}]".format(bytes_list, offset, self.dbdf))    


class FreeBSDPCIDevice(PCIDeviceBase):
    """
    PCI device for FreeBSD
    """ 
    def __init__(self, dbdf, debug_level="debug"):
        super(FreeBSDPCIDevice, self).__init__(dbdf, debug_level)
        if self._is_valid_device() == False:
            self.logger.debug("Device is not supported to save/load pci configurations")
            raise NotSupportedDeviceException("Device is not supported to save/load pci configurations")
        self._pci_express_offset = self._get_pci_express_offset()

    def read(self, offset, size, skip_offset_list=None):
        super(FreeBSDPCIDevice, self).read(offset, size, skip_offset_list)
        try:
            if skip_offset_list:
                read_intervals = BinaryFile._get_read_intervals(skip_offset_list, offset, size)
            else:
                read_intervals = [(offset, offset+size)]

            bytes_as_string = []
            for interval_start, interval_size in read_intervals:
                if interval_size:
                    pciconf_aligned_offset = ((interval_start / 4) * 4) # pciconf reads in aligment of 4 bytes
                    pciconf_size_offset = offset % 4
                    interval_size = interval_size + pciconf_size_offset # in case you want to read from adress not devidable by 4
                    read_cmd = "pciconf -r {0} {1}:{2}".format(self.dbdf, pciconf_aligned_offset, interval_size)
                    rc, out, err = exec_cmd(read_cmd)
                    if rc:
                        raise RuntimeError("Failed to read using cmd {0}, Error[{1}]".format(read_cmd, err))
                    pci_hex_data_list = out.replace("\n", " ").split(" ") # Remove new lines + split on spaces
                    for hex_str in pci_hex_data_list:
                        if hex_str != '':  # little endian 
                            bytes_as_string += [hex_str[6:8] , hex_str[4:6] , hex_str[2:4] , hex_str[0:2]]
                else:
                    bytes_as_string.append("00")
        except Exception as e:
            raise RuntimeError("Failed to read offset [{0}] with size [{1}] for PCI device [{2}]. Error is [{3}]".format(offset, size, self.dbdf, e))

        bytes_list = []
        actual_offset = offset - pciconf_aligned_offset
        bytes_as_string = bytes_as_string[actual_offset:actual_offset + size]
        for byte in bytes_as_string:
            if byte != "":
                bytes_list.append(int(byte, 16))
            else:
                bytes_list.append(None)
        return bytes_list
    
    def read_byte(self, offset):
        """
        Reads 1B from the pci configuration
        """
        return self.read(offset, 1)[0]

    def read_word(self, offset):
        """
        Reads 2B from the pci configuration
        """
        assert offset % 2 == 0, "Offset should be aligned to 2"
        bytes_list = self.read(offset, 2)
        if bytes_list != []:
            byte0 = "{0:x}".format(bytes_list[0]).zfill(2)
            byte1 = "{0:x}".format(bytes_list[1]).zfill(2)
            return int("{0}{1}".format(byte1, byte0), 16)
        else:
            return None

    def read_long(self, offset):
        """
        Read 4B from the pci configuration
        """
        assert offset % 4 == 0, "Offset should be aligned to 4"
        bytes_list = self.read(offset, 4)
        if bytes_list != []:
            byte0 = "{0:x}".format(bytes_list[0]).zfill(2)
            byte1 = "{0:x}".format(bytes_list[1]).zfill(2)
            byte2 = "{0:x}".format(bytes_list[2]).zfill(2)
            byte3 = "{0:x}".format(bytes_list[3]).zfill(2)
            return int("{0}{1}{2}{3}".format(byte3, byte2, byte1, byte0), 16)
        else:
            return None

    def write(self, offset, size, bytes_list):
        super(FreeBSDPCIDevice, self).write(offset, size, bytes_list)
        assert offset % 4 == 0, "Offset {0} is not aligned to 4".format(offset)

        data_to_write = ''
        for byte in bytes_list:
            data_to_write += "{0:x}".format(byte).zfill(2)

        write_cmd = "pciconf -w {0} {1} {2}".format(self.dbdf, offset, data_to_write)
        rc, out, err = exec_cmd(write_cmd)
        if rc:
            raise RuntimeError("Failed to write pci conf space data using cmd {0}, Error[{1}]".format(write_cmd, err))
        
        self.logger.debug("Data was Written [{0}] to  offset[{1}] for PCI device [{2}]".format(data_to_write, offset, self.dbdf))


def exec_cmd(cmd):
    """
    This is for executing commands
    """
    p = subprocess.Popen(cmd,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         universal_newlines=False,
                         shell=True)
    output = p.communicate()
    stat = p.wait()
    return stat, output[0].decode('utf-8'), output[1].decode('utf-8')  # RC, Stdout, Stderr

class PCIDeviceFactory(object):
    """
    A factory class for get the right PCIDevice
    """
    @staticmethod
    def get(dbdf, debug_level="critical"):
        machine_platform = platform.platform()
        if "Linux" in machine_platform:
            return LinuxPCIDevice(dbdf, debug_level)
        elif "FreeBSD" in machine_platform:
            return FreeBSDPCIDevice(dbdf, debug_level)
        else:
            raise RuntimeError("OS [%s] is not supported yet." % machine_platform)