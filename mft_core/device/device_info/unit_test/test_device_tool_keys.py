#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#
#  Version: $Id$
#

"""Pins the device json values that tools read as behavior.

dev_mgt and mlxfwops in mstflint, and imgen, memaccess and dm_gmon in MFT, read these keys instead of
keeping per-device lists, so editing one changes a tool. Each existing device's values are listed here and
an edit must update them on purpose. A device not listed is new and is only checked for the keys its type
cannot do without.

To run manually, from mft_core/device/device_info, once generated/device_properties_data.py exists:
    python3 unit_test/test_device_tool_keys.py
"""

import os
import sys
import unittest

# device_properties_api sits one level up and loads the generated data itself
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir))

import device_properties_api as api  # noqa: E402

# dm_dev_is_ib_switch() and dm_dev_is_eth_switch() read these for switches only.
SWITCH_KEYS = (api.PROP_SUPPORTS_IB, api.PROP_SUPPORTS_ETH)

IB_SWITCHES = ('Quantum2', 'Quantum3', 'NVLink6_Switch')
ETH_SWITCHES = ('Spectrum', 'Spectrum2', 'Spectrum3', 'Spectrum4', 'Spectrum5', 'Spectrum6')

# Each key's value per existing device; an existing device a key does not list must not set it.
EXPECTED = {
    api.PROP_SUPPORTS_IB: {'true': IB_SWITCHES, 'false': ETH_SWITCHES},
    api.PROP_SUPPORTS_ETH: {'true': ETH_SWITCHES, 'false': IB_SWITCHES},
    api.PROP_IMAGE_LAYOUT_FORMAT: {
        api.IMAGE_LAYOUT_FS3: ('ConnectX4', 'ConnectX4LX', 'Spectrum'),
        api.IMAGE_LAYOUT_FS4: ('ConnectX5', 'ConnectX6', 'ConnectX6DX', 'ConnectX6LX', 'ConnectX7', 'BlueField',
                               'BlueField2', 'BlueField3', 'Spectrum2', 'Spectrum3', 'Spectrum4', 'Spectrum5',
                               'Quantum2'),
        api.IMAGE_LAYOUT_FS5: ('ConnectX8', 'ConnectX8_Pure_PCIe_Switch', 'ConnectX9', 'ConnectX9_Pure_PCIe_Switch',
                               'BlueField4', 'Quantum3', 'NVLink6_Switch', 'ArcusE', 'Arcus2', 'Sagitta',
                               'SagittaRev1', 'SagittaZ'),
        api.IMAGE_LAYOUT_FS6: ('Spectrum6', 'Libra'),
        api.IMAGE_LAYOUT_NA: ('GB100', 'GR100', 'GR150', 'GR150A01P', 'FN100', 'NR10', 'Vera'),
    },
    api.PROP_FW_IMAGE_FORMAT: {
        api.FW_IMAGE_FORMAT_CONNECTIB: ('ConnectX4', 'ConnectX4LX', 'Spectrum'),
        api.FW_IMAGE_FORMAT_FS4: ('ConnectX5', 'ConnectX6', 'ConnectX6DX', 'ConnectX6LX', 'ConnectX7', 'BlueField',
                                  'BlueField2', 'BlueField3', 'Spectrum2', 'Spectrum3', 'Spectrum4', 'Spectrum5',
                                  'Quantum2', 'Menhit'),
        api.FW_IMAGE_FORMAT_FS5: ('ConnectX8', 'ConnectX8_Pure_PCIe_Switch', 'ConnectX9', 'Quantum3', 'NVLink6_Switch',
                                  'ArcusE', 'Arcus2'),
        api.FW_IMAGE_FORMAT_FS6: ('Spectrum6', 'Libra'),
        api.FW_IMAGE_FORMAT_FS4_GPU: ('GB100', 'GR100', 'GR150', 'GR150A01P', 'FN100'),
    },
    api.PROP_FW_IMAGE_SECTION_ADDR_MSB: {
        'true': ('Spectrum6',),
    },
    api.PROP_LIVEFISH_INDICATION_ADDRESS: {
        # mstflint also clears the livefish indication on the Pure PCIe switches.
        0xf813c: ('ConnectX8', 'ConnectX9', 'ConnectX8_Pure_PCIe_Switch', 'ConnectX9_Pure_PCIe_Switch'),
        0xfc13c: ('Quantum3', 'NVLink6_Switch'),
        0xfb058: ('Spectrum6',),
    },
    api.PROP_SMGW_ADDRESS: {
        0xa1000: ('Spectrum',),
        0xa3c00: ('Spectrum2', 'Spectrum3'),
        0xa4000: ('Spectrum4', 'Spectrum5'),
        0x154800: ('Spectrum6',),
        0xa3000: ('Quantum2',),
        0x154400: ('Quantum3', 'NVLink6_Switch'),
    },
    api.PROP_FREE_RUNNING_COUNTER_ADDRESS: {
        0xe3a20: ('ConnectX4', 'ConnectX4LX', 'ConnectX5', 'ConnectX6', 'ConnectX6DX', 'ConnectX6LX', 'BlueField',
                  'BlueField2'),
        0xe3820: ('ConnectX7', 'BlueField3'),
        0x56000: ('ConnectX8', 'ConnectX8_Pure_PCIe_Switch', 'ConnectX9', 'ConnectX9_Pure_PCIe_Switch'),
        0xa2028: ('Spectrum',),
        0xa3a20: ('Spectrum2', 'Spectrum3'),
        0xa3c40: ('Spectrum4', 'Spectrum5'),
        0x154e60: ('Spectrum6',),
        0xa2c20: ('Quantum2',),
        0x154100: ('Quantum3', 'NVLink6_Switch'),
        0x147500: ('ArcusE',),
        0x147900: ('Arcus2',),
        0x308ec20: ('GB100', 'GR100', 'GR150', 'GR150A01P', 'FN100', 'NR10'),
    },
}

# Existing devices that set none of the keys above.
WITHOUT_KEYS = ('CableSFP', 'CableQSFP', 'CableQSFPaging', 'CableCMIS', 'Ardbeg', 'Ardbeg Mirrored',
                'Ardbeg Revision 1', 'Baritone', 'Baritone Mirrored', 'Menhit Version 1', 'Menhit Version 2',
                'ArcusP', 'ArcusP Test Chip', 'ArcusESddv')

EXISTING = set(WITHOUT_KEYS)
for _groups in EXPECTED.values():
    for _names in _groups.values():
        EXISTING.update(_names)


def _expected(key, name):
    """The flattened json string the C getters read for an existing device, or None when it must not set the key."""
    values = [value for value, names in EXPECTED[key].items() if name in names]
    return str(values[0]) if values else None


class TestDeviceToolKeys(unittest.TestCase):

    def test_existing_devices_keep_their_values(self):
        """An existing device reads the values listed above."""
        for hw_id, props in sorted(api.properties_by_device_id.items()):
            name = props.get(api.PROP_DEVICE_NAME)
            if name not in EXISTING:
                continue
            for key in EXPECTED:
                if key in SWITCH_KEYS and not api.is_switch(hw_id):
                    continue
                self.assertEqual(props.get(key), _expected(key, name), '{0} ({1}) {2}'.format(name, hw_id, key))

    def test_existing_devices_still_present(self):
        """Removing or renaming an existing device would skip the check above."""
        names = set(props.get(api.PROP_DEVICE_NAME) for props in api.properties_by_device_id.values())
        self.assertEqual(sorted(EXISTING - names), [])

    def test_switches_set_their_protocols(self):
        """A switch, new ones included, without these is neither IB nor Ethernet and each lookup logs an error."""
        for hw_id, props in sorted(api.properties_by_device_id.items()):
            if not api.is_switch(hw_id):
                continue
            for key in SWITCH_KEYS:
                message = '{0} ({1}) {2}'.format(props.get(api.PROP_DEVICE_NAME), hw_id, key)
                self.assertIn(props.get(key), ('true', 'false'), message)


if __name__ == '__main__':
    unittest.main()
