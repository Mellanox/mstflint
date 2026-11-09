#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

"""Unit tests for device_properties_api module."""

import os
import sys
import unittest
try:
    from unittest.mock import MagicMock, patch
except ImportError:  # Python 2
    from mock import MagicMock, patch

# Add the parent directory to the path to import the module under test
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from device_properties_api import (get_property_as_bool, get_property_as_string,  # noqa: E402
                                   get_property_as_uint)


class TestDevicePropertiesAPI(unittest.TestCase):
    """Test cases for device_properties_api functions."""

    def setUp(self):
        """Set up test fixtures."""
        # Mock properties data
        self.mock_properties = {
            "0x220": {
                "name": "ConnectX-7",
                "device_type": "NIC",
                "pci_device_id": "0x220",
                "num_ports": "2",
                "port_width": "0x10",
                "supports_wol": "true",
                "supports_roce": "1",
                "disabled_feature": "false",
                "invalid_number": "not_a_number",
                "empty_value": "",
            }
        }

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_valid(self, mock_props):
        """Test get_property_as_string with valid device_id and property."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_string(0x220, "name")
        self.assertEqual(result, "ConnectX-7")

        result = get_property_as_string(0x220, "device_type")
        self.assertEqual(result, "NIC")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_device_id_as_string(self, mock_props):
        """Test get_property_as_string with device_id as string."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_string("0x220", "name")
        self.assertEqual(result, "ConnectX-7")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_invalid_device(self, mock_props):
        """Test get_property_as_string with invalid device_id raises ValueError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(ValueError):
            get_property_as_string(0x999, "name")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_invalid_property(self, mock_props):
        """Test get_property_as_string with invalid property_name raises KeyError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(KeyError):
            get_property_as_string(0x220, "non_existent_property")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_empty_property_name(self, mock_props):
        """Test get_property_as_string with empty property_name raises TypeError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(TypeError):
            get_property_as_string(0x220, "")

        with self.assertRaises(TypeError):
            get_property_as_string(0x220, None)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_string_empty_value(self, mock_props):
        """Test get_property_as_string when property value is empty."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_string(0x220, "empty_value")
        self.assertEqual(result, "")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_uint_decimal(self, mock_props):
        """Test get_property_as_uint with decimal value."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_uint(0x220, "num_ports")
        self.assertEqual(result, 2)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_uint_hex(self, mock_props):
        """Test get_property_as_uint with hex value."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_uint(0x220, "port_width")
        self.assertEqual(result, 16)

        result = get_property_as_uint(0x220, "pci_device_id")
        self.assertEqual(result, 0x220)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_uint_invalid_value(self, mock_props):
        """Test get_property_as_uint with non-numeric value raises ValueError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(ValueError):
            get_property_as_uint(0x220, "invalid_number")

        with self.assertRaises(ValueError):
            get_property_as_uint(0x220, "name")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_uint_non_existent(self, mock_props):
        """Test get_property_as_uint with non-existent property raises KeyError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(KeyError):
            get_property_as_uint(0x220, "non_existent")

        with self.assertRaises(ValueError):
            get_property_as_uint(0x999, "num_ports")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_uint_empty_property_name(self, mock_props):
        """Test get_property_as_uint with empty property_name raises TypeError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(TypeError):
            get_property_as_uint(0x220, "")

        with self.assertRaises(TypeError):
            get_property_as_uint(0x220, None)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_true_string(self, mock_props):
        """Test get_property_as_bool with 'true' string."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_bool(0x220, "supports_wol")
        self.assertTrue(result)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_one_string(self, mock_props):
        """Test get_property_as_bool with '1' string is not truthy (only "true" is)."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_bool(0x220, "supports_roce")
        self.assertFalse(result)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_false_string(self, mock_props):
        """Test get_property_as_bool with 'false' string."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        result = get_property_as_bool(0x220, "disabled_feature")
        self.assertFalse(result)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_other_values(self, mock_props):
        """Test get_property_as_bool with other values.

        The API only considers "true" as truthy. Everything else is False.
        """
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        # Test with a numeric string
        result = get_property_as_bool(0x220, "num_ports")
        self.assertFalse(result)

        # Test with text string
        result = get_property_as_bool(0x220, "name")
        self.assertFalse(result)

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_non_existent(self, mock_props):
        """Test get_property_as_bool with non-existent property raises KeyError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(KeyError):
            get_property_as_bool(0x220, "non_existent")

        with self.assertRaises(ValueError):
            get_property_as_bool(0x999, "supports_wol")

    @patch('device_properties_api.properties_by_device_id')
    def test_get_property_as_bool_empty_property_name(self, mock_props):
        """Test get_property_as_bool with empty property_name raises TypeError."""
        mock_props.get = MagicMock(
            side_effect=lambda x: self.mock_properties.get(x)
        )

        with self.assertRaises(TypeError):
            get_property_as_bool(0x220, "")

        with self.assertRaises(TypeError):
            get_property_as_bool(0x220, None)


class ConciseTestResult(unittest.TextTestResult):
    """Custom test result with concise output."""

    def getDescription(self, test):
        """Return just the docstring, or method name if no docstring."""
        doc = test.shortDescription()
        return doc if doc else test._testMethodName

    def addSuccess(self, test):
        super(ConciseTestResult, self).addSuccess(test)
        if self.showAll:
            self.stream.writeln()

    def addError(self, test, err):
        super(ConciseTestResult, self).addError(test, err)
        if self.showAll:
            self.stream.writeln()

    def addFailure(self, test, err):
        super(ConciseTestResult, self).addFailure(test, err)
        if self.showAll:
            self.stream.writeln()

    def addSkip(self, test, reason):
        super(ConciseTestResult, self).addSkip(test, reason)
        if self.showAll:
            self.stream.writeln()


class ConciseTestRunner(unittest.TextTestRunner):
    """Custom test runner with concise output."""
    resultclass = ConciseTestResult


if __name__ == '__main__':
    unittest.main(testRunner=ConciseTestRunner)
