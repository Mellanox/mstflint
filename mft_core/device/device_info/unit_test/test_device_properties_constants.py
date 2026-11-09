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

"""Drift guard: device_properties_constants.py must stay in sync with device_properties_constants.h.

Parses the #define NAME "VALUE" entries from the C header and asserts the
Python mirror module exposes the identical name -> value mapping. A mismatch
(constant added/removed/renamed on one side only) fails the test.

TODO: This test (like the other test_*.py here) is currently only runnable
manually -- the repo has no py_test targets and CI does not discover Python
unit tests. Wire it up as a Bazel py_test and add it to a CI-run test suite so
the drift guard is enforced automatically rather than by convention.

To run manually, from user/mft_core/device/device_info:
    python3 unit_test/test_device_properties_constants.py
"""

import os
import re
import sys
import unittest

# Add the parent directory to the path to import the module under test
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

import device_properties_constants  # noqa: E402

_HEADER_PATH = os.path.join(os.path.dirname(__file__), '..', 'device_properties_constants.h')
_DEFINE_RE = re.compile(r'^\s*#define\s+(\w+)\s+"(.*)"\s*$')


def _parse_header_defines(path):
    """Return {name: value} for every '#define NAME "VALUE"' line in the header."""
    defines = {}
    with open(path) as f:
        for line in f:
            m = _DEFINE_RE.match(line)
            if m:
                defines[m.group(1)] = m.group(2)
    return defines


def _module_string_constants(module):
    """Return {name: value} for every public ALL-CAPS string constant in the module."""
    return {
        name: value
        for name, value in vars(module).items()
        if not name.startswith('_') and name.isupper() and isinstance(value, str)
    }


class TestDevicePropertiesConstants(unittest.TestCase):
    """Verify device_properties_constants.py mirrors device_properties_constants.h exactly."""

    def setUp(self):
        self.header = _parse_header_defines(_HEADER_PATH)
        self.module = _module_string_constants(device_properties_constants)

    def test_header_has_constants(self):
        # Guard against a parsing regression silently passing the comparison.
        self.assertTrue(self.header, "no #define constants parsed from device_properties_constants.h")

    def test_no_constant_missing_in_python(self):
        missing = sorted(set(self.header) - set(self.module))
        self.assertFalse(
            missing,
            "constants defined in device_properties_constants.h but missing from "
            "device_properties_constants.py: {0}".format(missing))

    def test_no_extra_constant_in_python(self):
        extra = sorted(set(self.module) - set(self.header))
        self.assertFalse(
            extra,
            "constants defined in device_properties_constants.py but missing from "
            "device_properties_constants.h: {0}".format(extra))

    def test_values_match(self):
        mismatched = {
            name: (self.header[name], self.module[name])
            for name in set(self.header) & set(self.module)
            if self.header[name] != self.module[name]
        }
        self.assertFalse(
            mismatched,
            "value mismatch between header and python (name: (h, py)): "
            "{0}".format(mismatched))


if __name__ == '__main__':
    unittest.main()
