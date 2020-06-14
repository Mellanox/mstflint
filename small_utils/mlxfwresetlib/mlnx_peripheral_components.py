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
#--

"""
* $Id           : mlnx_peripheral_components.py 2017-11-28
* $Authors      : Roei Yitzhak (roei@mellanox.com)
"""
from __future__ import print_function

from __future__ import print_function
import platform
import re
from .pci_device import PciDevice
from .mlxfwreset_utils import cmdExec

class MlnxPeripheralComponents(object):

    SD_SUPPORTED_DID = [0x216,0x212,0x20f,0x20d,0x209,0x20b]  # Connectx6LX,Connectx6DX,Connectx6,Connectx5 (SD device) ,Connectx4/Connectx4Lx (MH device connected as SD)

    def __init__(self):
        self.pci_devices = []
        self.os = platform.system()
        self.discover_pci_devices()

    def discover_pci_devices(self):

        if self.os == 'Linux':
            cmd = 'mdevices_info -vv'
            pattern = r'.*\s+(\S+)\s+(([0-9A-Fa-f]{4})*:*([0-9A-Fa-f]{2}):([0-9A-Fa-f]{2})\.([0-9A-Fa-f]{1,2})).*'
        elif self.os == 'FreeBSD':
            cmd = 'mst status -v'
            pattern = r'.*\s(pci(\d+):(\d+):(\d+):(\d+))\s.*'
        elif self.os == 'Windows':
            cmd = 'mdevices status -v'
            pattern = r'\s*(\S+)\s+\S*bus:dev.fn=(([0-9A-Fa-f]{4})*:*([0-9A-Fa-f]{2}):([0-9A-Fa-f]{2})\.([0-9A-Fa-f]{1})).*'
        else:
            raise RuntimeError("Unsupported OS")

        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get device PCI address")

        for line in out.split('\n'):
            #  print(line)
            try:
                result = re.match(pattern, line)
                if result:
                    aliases = []
                    if self.os == 'Linux':
                        if result.group(1) != 'NA':
                            aliases.append(result.group(1))
                        aliases.append(result.group(2))
                        if result.group(3) is None:
                            domain = 0
                            aliases.append('0000:'+result.group(2))
                        else:
                            domain = int(result.group(3), 16)
                        bus = int(result.group(4), 16)
                        dev = int(result.group(5), 16)
                        fn = int(result.group(6), 16)
                    elif self.os == 'FreeBSD':
                        aliases.append(result.group(1))
                        domain = int(result.group(2))
                        bus = int(result.group(3))
                        dev = int(result.group(4))
                        fn = int(result.group(5))
                    elif self.os == 'Windows':
                        aliases.append(result.group(1)) # mt<id>_pciconf<N>
                        aliases.append(result.group(2)) # dbdf
                        if result.group(3) is None:     # no domain
                            domain = 0
                            aliases.append('0000:'+result.group(2))
                        else:
                            domain = int(result.group(3), 16)
                        bus = int(result.group(4), 16)
                        dev = int(result.group(5), 16)
                        fn = int(result.group(6), 16)
                    else:
                        RuntimeError("Unsupported OS")

                    pci_device = PciDevice(aliases, domain, bus, dev, fn)
                    self.pci_devices.append(pci_device)
            except:
                raise RuntimeError("Failed to get device PCI Address") # Why it's required??? You don't do anything in the excpetion

    def get_pci_device(self, alias):
        for pci_device in self.pci_devices:
            if pci_device.has_alias(alias):
                return pci_device # TODO think if you need to copy
        else:
            raise RuntimeError("Failed to find {0} in pci-devices".format(alias))

    def get_socket_direct_pci_devices(self, usr_pci_device):

        sd_pci_devices = []

        if usr_pci_device.get_cfg_did() in MlnxPeripheralComponents.SD_SUPPORTED_DID:

            usr_manufacturing_base_mac = usr_pci_device.get_manufacturing_base_mac()

            if usr_manufacturing_base_mac == 0:
                raise RuntimeError('Base MAC is N/A')
            else:
                for pci_device in self.pci_devices:

                    # Skip if the current pci-device is the same as user's pci-device
                    if pci_device.domain == usr_pci_device.domain \
                            and pci_device.bus == usr_pci_device.bus \
                            and pci_device.device == usr_pci_device.device:
                        continue

                    # Skip if the current pci-device is not supported for Socket-Direct
                    if pci_device.get_cfg_did() not in MlnxPeripheralComponents.SD_SUPPORTED_DID:
                        continue

                    # Check only function 0 (skip otherwise)
                    if pci_device.fn != 0:
                        continue

                    # Skip if device in livefish mode
                    if pci_device.is_livefish_mode(): continue

                    if usr_manufacturing_base_mac == pci_device.get_manufacturing_base_mac():
                        sd_pci_devices.append(pci_device)

        return sd_pci_devices


if __name__ == '__main__':

    import sys

    device = sys.argv[1]

    peripherals = MlnxPeripheralComponents()
    for pci_device in  peripherals.pci_devices:
        print(pci_device)

    user_pci_device = peripherals.get_pci_device(device)

    print('user pci_device: {0}'.format(user_pci_device))

    res = peripherals.get_socket_direct_pci_devices(user_pci_device)

    print("Socket direct discovery:")
    if len(res):
        for pci_device in res:
            print(pci_device)
    else:
        print("device is not part of socket direct")
