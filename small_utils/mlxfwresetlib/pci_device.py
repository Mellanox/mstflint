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
# --

"""
* $Id           : pci_device.py 2017-11-28
* $Authors      : Roei Yitzhak (roei@mellanox.com)
"""

from __future__ import print_function

from mtcr import MstDevice
from .mcra import Mcra
# TODO fix it latter - need to import the function from mlxfwreset.py
import sys
import os
mlxfwreset_dir = os.path.dirname(os.path.dirname(__file__))
sys.path.append(mlxfwreset_dir)
from dev_mgt import DevMgt
from regaccess import RegAccess


class PciDevice(object):

    def __init__(self, aliases, domain, bus, device, fn):
        '''
        :param aliases:
            windows 'mt4115_pciconf0'
            Linux '/dev/mst/mt4119_pciconf1' , '0e:00.0' , '0000:0e:00.0'
            FreeBSD 'pci0:2:0:0'
        '''

        assert isinstance(domain, int) and isinstance(bus, int) and isinstance(device, int) and isinstance(fn, int)
        assert isinstance(aliases, list)

        self.aliases = aliases

        self.domain = domain
        self.bus = bus
        self.device = device
        self.fn = fn

    def __str__(self):
        return '{0} pci_address={1:04x}:{2:02x}:{3:02x}.{4:01x}'.format([alias for alias in self.aliases], self.domain, self.bus, self.device, self.fn)

    def has_alias(self, alias):
        return alias in self.aliases

    def get_alias(self):
        return self.aliases[0]

    def get_cfg_did(self):

        DEVID_ADDR = [0xf0014, 0, 16]  # Adresses [Base offset length]
        mcra = Mcra()
        return mcra.read(self.aliases[0], DEVID_ADDR[0], DEVID_ADDR[1], DEVID_ADDR[2])
        # return get_cfg_did(self.aliases[0]) # PCI configuration DID

    def is_livefish_mode(self):
        mst_device = MstDevice(self.aliases[0])
        try:
            device_mgt = DevMgt(mst_device)
            res = device_mgt.isLivefishMode() == 1
        finally:
            mst_device.close()
        return res

    def get_manufacturing_base_mac(self):
        # Be-careful : The logic won't work for all devices
        mst_device = MstDevice(self.aliases[0])
        try:
            reg_access = RegAccess(mst_device)
            manufacturing_base_mac = reg_access.getManufacturingBaseMac()
        finally:
            mst_device.close()
        return manufacturing_base_mac
