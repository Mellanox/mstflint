#!/usr/bin/env python
# -*- coding: utf-8 -*-
# SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

"""Drift guard: device_properties_api.py eDeviceID mirror must stay in sync
with device_hw_ids.h.

device_properties_api.py hand-copies the eDeviceID enum from device_hw_ids.h
as plain Python integer constants. This test parses both sources as text (no
import, so it does not depend on the generated device_properties_data module)
and asserts every device-ID constant mirrored in Python matches the C enum.

The Python mirror is intentionally a subset of the C enum (it omits entries the
Python tooling never references, e.g. DEVICE_DUMMY), so the check is:
every Python device-ID constant must exist in device_hw_ids.h with an
identical value. A renamed/removed/re-valued constant on either side that
breaks that invariant fails the test.

The test additionally enforces JSON coverage: every per-device file under
json/ (named "<hw_id>.json") must have a matching id in BOTH device_hw_ids.h
and device_properties_api.py. This catches a new device added as JSON without
a corresponding enum member / Python constant.

TODO: Like the other test_*.py here, this is currently only runnable manually
(no py_test target / CI discovery). Wire it into a Bazel py_test suite so the
drift guard is enforced automatically.

To run manually, from user/mft_core/device/device_info:
    python3 unit_test/test_device_id_constants.py
"""

import glob
import os
import re
import sys
import unittest

_THIS_DIR = os.path.dirname(__file__)
_HEADER_PATH = os.path.join(_THIS_DIR, '..', 'device_hw_ids.h')
_PY_API_PATH = os.path.join(_THIS_DIR, '..', 'device_properties_api.py')
_JSON_DIR = os.path.join(_THIS_DIR, '..', 'json')

# JSON device files are named "<hw_id>.json", e.g. "0x1e.json".
_JSON_ID_RE = re.compile(r'^(0[xX][0-9A-Fa-f]+)\.json$')

# Matches "NAME = 0x1ff," (enum member) or "NAME = -1" (Python constant).
# Also matches "NAME = DEVICE_IDENTITY(0x3480, 1)," for revision-specific entries.
# Requires the value to be a bare integer literal or DEVICE_IDENTITY macro so it
# never matches '#define BLUEFIELD4_PCI_ID 41695' (no '=') or expression assignments
# such as 'log_level = level_map.get(...)' in device_properties_api.py.
_INT_CONST_RE = re.compile(
    r'^\s*([A-Za-z_]\w*)\s*=\s*(-?0[xX][0-9A-Fa-f]+|-?\d+)\s*,?\s*$')
_DEVICE_IDENTITY_RE = re.compile(
    r'^\s*([A-Za-z_]\w*)\s*=\s*DEVICE_IDENTITY\(\s*(0[xX][0-9A-Fa-f]+|\d+)\s*,\s*(\d+)\s*\)\s*,?\s*$')


def _parse_int_constants(path):
    """Return {name: int_value} for every 'NAME = <int literal>' or DEVICE_IDENTITY line."""
    constants = {}
    with open(path) as f:
        for line in f:
            m = _INT_CONST_RE.match(line)
            if m:
                name, raw = m.group(1), m.group(2)
                base = 16 if raw.lower().lstrip('-').startswith('0x') else 10
                constants[name] = int(raw, base)
                continue
            m = _DEVICE_IDENTITY_RE.match(line)
            if m:
                name = m.group(1)
                hw_id_raw = m.group(2)
                rev_raw = m.group(3)
                hw_base = 16 if hw_id_raw.lower().startswith('0x') else 10
                hw_id = int(hw_id_raw, hw_base)
                rev = int(rev_raw)
                constants[name] = ((rev & 0xF) << 16) | (hw_id & 0xFFFF)
    return constants


def _parse_json_device_ids(json_dir):
    """Return {int_value: '<hw_id>.json'} for every per-device JSON file."""
    ids = {}
    for path in glob.glob(os.path.join(json_dir, '0[xX]*.json')):
        m = _JSON_ID_RE.match(os.path.basename(path))
        if m:
            ids[int(m.group(1), 16)] = os.path.basename(path)
    return ids


class TestDeviceIdConstants(unittest.TestCase):
    """Verify device_properties_api.py mirrors the device_hw_ids.h enum."""

    def setUp(self):
        self.header = _parse_int_constants(_HEADER_PATH)
        self.python = _parse_int_constants(_PY_API_PATH)
        self.json_ids = _parse_json_device_ids(_JSON_DIR)

    def test_header_has_constants(self):
        # Guard against a parsing regression silently passing the comparison.
        self.assertTrue(self.header, "no enum constants parsed from device_hw_ids.h")

    def test_python_has_constants(self):
        self.assertTrue(self.python, "no device-ID constants parsed from device_properties_api.py")

    def test_no_python_constant_missing_from_header(self):
        missing = sorted(set(self.python) - set(self.header))
        self.assertFalse(
            missing,
            "device-ID constants defined in device_properties_api.py but absent "
            "from device_hw_ids.h (renamed/removed?): {0}".format(missing))

    def test_values_match(self):
        mismatched = {
            name: ("0x{0:x}".format(self.header[name]), "0x{0:x}".format(self.python[name]))
            for name in set(self.header) & set(self.python)
            if self.header[name] != self.python[name]
        }
        self.assertFalse(
            mismatched,
            "value mismatch between device_hw_ids.h and device_properties_api.py "
            "(name: (header, python)): {0}".format(mismatched))

    def test_json_ids_found(self):
        # Guard against a path/parsing regression silently passing the coverage checks.
        self.assertTrue(self.json_ids, "no per-device JSON files parsed from {0}".format(_JSON_DIR))

    def test_every_json_id_in_header(self):
        header_values = set(self.header.values())
        missing = sorted(
            self.json_ids[v] for v in set(self.json_ids) - header_values)
        self.assertFalse(
            missing,
            "JSON device ids with no matching eDeviceID member in device_hw_ids.h: "
            "{0}".format(missing))

    def test_every_json_id_in_python(self):
        python_values = set(self.python.values())
        missing = sorted(
            self.json_ids[v] for v in set(self.json_ids) - python_values)
        self.assertFalse(
            missing,
            "JSON device ids with no matching constant in device_properties_api.py: "
            "{0}".format(missing))


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0]])
