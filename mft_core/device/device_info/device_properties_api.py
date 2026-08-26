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

"""Device Properties API for Python.

Provides access to device properties from auto-generated device_properties_data module.
"""

import logging
import sys
import os

# Try 'generated' subdirectory first (Linux), then same directory as fallback (Windows)
_current_dir = os.path.dirname(__file__)
_generated_dir = os.path.join(_current_dir, 'generated')
if _generated_dir not in sys.path:
    sys.path.insert(0, _generated_dir)
if _current_dir not in sys.path:
    sys.path.insert(0, _current_dir)

try:
    from device_properties_data import properties_by_device_id
except ImportError as e:
    sys.stderr.write("Error: Could not import device_properties_data module.\n")
    sys.exit(1)

# Re-export property key/value constants (mirror of device_properties_constants.h) so
# callers can use device_properties_api.PROP_* instead of magic strings.
from device_properties_constants import *  # noqa: F401,F403,E402


# Use MFT_PRINT_LOG environment variable aligned with C++ logger behavior
# (see mft_core_utils/logger/LoggerDefs.h - eLoggerSeverityLevel enum)
# Numeric mapping: 0 = debug, 1 = info, 2 = warning, 3 = error, 4 = critical/fatal
# Values >= 5 map to debug (matches C++ behavior where >= severity_count resets to 0)
# If not set, no logging is done
mft_print_log = os.environ.get('MFT_PRINT_LOG')
if mft_print_log is not None:
    try:
        level_num = int(mft_print_log)
        # Map to Python logging levels
        level_map = {0: logging.DEBUG, 1: logging.INFO, 2: logging.WARNING,
                     3: logging.ERROR, 4: logging.CRITICAL, 5: logging.DEBUG}
        log_level = level_map.get(level_num, logging.CRITICAL)
    except ValueError:
        log_level = logging.CRITICAL
else:
    log_level = logging.CRITICAL

logging.basicConfig(level=log_level,
                    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger('device_properties_api')


# ============================================================================
# Core property access functions
# ============================================================================

def get_property_as_string(device_id, property_name):
    """Get property value as string.

    Args:
        device_id: Device ID as integer (e.g., 0x220)
        property_name: Property name to retrieve

    Returns:
        Property value as string

    Raises:
        TypeError: If property_name is empty or None
        ValueError: If device_id is invalid
        KeyError: If property not found
    """
    if not property_name:
        error_msg = "-E- property_name cannot be empty or None"
        logger.error(error_msg)
        raise TypeError(error_msg)

    device_id_str = "0x{0:x}".format(device_id) if isinstance(device_id, int) else str(device_id)

    # Lookup the device's property map
    device_props = properties_by_device_id.get(device_id_str)
    if device_props is None:
        error_msg = "-E- Unsupported Device ID {0}".format(device_id_str)
        logger.error(error_msg)
        raise ValueError(error_msg)

    # Lookup the property in the device's property map
    result = device_props.get(property_name)
    if result is None:
        error_msg = "-E- the following field is not available in device_info: \"{0}\"".format(property_name)
        logger.error(error_msg)
        raise KeyError(error_msg)

    logger.debug("get_property_as_string: device_id={0}, {1}={2}".format(device_id_str, property_name, result))
    return result


def get_property_as_uint(device_id, property_name):
    """Get property value as unsigned integer.

    Args:
        device_id: Device ID as integer (e.g., 0x220)
        property_name: Property name to retrieve

    Returns:
        Property value as integer

    Raises:
        TypeError: If property_name is empty or None
        ValueError: If device_id is invalid or value cannot be converted to int
        KeyError: If property not found
    """
    if not property_name:
        error_msg = "-E- property_name cannot be empty or None"
        logger.error(error_msg)
        raise TypeError(error_msg)

    device_id_str = "0x{0:x}".format(device_id) if isinstance(device_id, int) else str(device_id)

    # Will raise exception if device is invalid or property not found
    value = get_property_as_string(device_id, property_name)

    try:
        result = int(value, 16) if value.startswith("0x") else int(value)
    except ValueError:
        error_msg = "-E- Invalid numeric value for property \"{0}\": {1}".format(property_name, value)
        logger.error(error_msg)
        raise ValueError(error_msg)

    logger.debug("get_property_as_uint: device_id={0}, {1}={2} (0x{2:x})".format(device_id_str, property_name, result))
    return result


def get_property_as_int(device_id, property_name):
    """Get property value as signed integer. Raises on error."""
    return get_property_as_uint(device_id, property_name)


def get_property_as_bool(device_id, property_name):
    """Get property value as boolean.

    Args:
        device_id: Device ID as integer (e.g., 0x220)
        property_name: Property name to retrieve

    Returns:
        True if value is "true", False otherwise

    Raises:
        TypeError: If property_name is empty or None
        ValueError: If device_id is invalid
        KeyError: If property not found
    """
    if not property_name:
        error_msg = "-E- property_name cannot be empty or None"
        logger.error(error_msg)
        raise TypeError(error_msg)

    device_id_str = "0x{0:x}".format(device_id) if isinstance(device_id, int) else str(device_id)

    # Will raise exception if device is invalid or property not found
    value = get_property_as_string(device_id, property_name)
    result = value == "true"

    logger.debug("get_property_as_bool: device_id={0}, {1}={2}".format(
        device_id_str, property_name, "true" if result else "false"))
    return result


# ============================================================================
# Device ID constants (mirrors device_hw_ids.h eDeviceID enum)
# ============================================================================

DEVICE_HW_ID_UNKNOWN = -1
ConnectX4 = 0x209
ConnectX4LX = 0x20b
ConnectX5 = 0x20d
ConnectX6 = 0x20f
ConnectX6DX = 0x212
ConnectX6LX = 0x216
ConnectX7 = 0x218
ConnectX8 = 0x21e
ConnectX8_Pure_PCIe_Switch = 0x222
ConnectX9_Pure_PCIe_Switch = 0x228
ConnectX9 = 0x224
ConnectX10 = 0x226
BlueField = 0x211
BlueField2 = 0x214
BlueField3 = 0x21c
BlueField4 = 0x224
BlueField4_PCIID = 0xa2df
SwitchIB = 0x247
SwitchIB2 = 0x24b
Spectrum = 0x249
Spectrum2 = 0x24e
Spectrum3 = 0x250
Spectrum4 = 0x254
Spectrum5 = 0x270
Spectrum6 = 0x274
Spectrum7 = 0x2A2
Quantum = 0x24d
Quantum2 = 0x257
Quantum3 = 0x25b
NVLink6_Switch = 0x278
NVLink7_Switch = 0x27c
NVLink8_Switch = 0x2a0
GB100 = 0x2900
GR100 = 0x3000
GR150 = 0x3480
GR150A01P = 0x13480
NR10 = 0x4088
FN100 = 0x3780
CableSFP = 0x3
Baritone = 0x6b
Ardbeg = 0x6e
Menhit = 0x6f
Ardbeg_Revision_1 = 0x7e
ArcusP_Test_Chip = 0x7f
CableQSFPaging = 0x11
CableCMIS = 0x19
CableCMIS0x1e = 0x1e
Ardbeg_Mirrored = 0x70
Baritone_Mirrored = 0x71
Menhit_Version_1 = 0x72
Menhit_Version_2 = 0x73
ArcusP = 0x80
ArcusE = 0x282
Arcus2 = 0x288
Libra = 0x286
ArcusESddv = 0x82
Sagitta = 0x84
SagittaZ = 0x90
CableQSFP = 0xd
Vera = 0x2f95


def _build_device_vector():
    ids = []
    for key in properties_by_device_id:
        dev_id = int(key, 16)
        ids.append(dev_id)
    ids.sort()
    return ids


_DEVICE_VECTOR = _build_device_vector()


# ============================================================================
# Convenience type-check functions
# ============================================================================

def is_nic(device_id):
    return get_property_as_string(device_id, PROP_DEVICE_TYPE) == DEVICE_TYPE_NIC


def is_switch(device_id):
    return get_property_as_string(device_id, PROP_DEVICE_TYPE) == DEVICE_TYPE_SWITCH


def is_cable(device_id):
    return get_property_as_string(device_id, PROP_DEVICE_TYPE) == DEVICE_TYPE_CABLE


def is_linkx(device_id):
    return get_property_as_string(device_id, PROP_DEVICE_TYPE) == DEVICE_TYPE_LINKX


def is_retimer(device_id):
    return get_property_as_string(device_id, PROP_DEVICE_TYPE) == DEVICE_TYPE_RETIMER


def is_4th_gen_nic(device_id):
    return False


def is_5th_gen_nic(device_id):
    return is_nic(device_id) and not is_4th_gen_nic(device_id)


def is_fs2(device_id):
    return get_property_as_string(device_id, PROP_IMAGE_LAYOUT_FORMAT) == IMAGE_LAYOUT_FS2


def is_fs3(device_id):
    return get_property_as_string(device_id, PROP_IMAGE_LAYOUT_FORMAT) == IMAGE_LAYOUT_FS3


def is_fs4(device_id):
    return get_property_as_string(device_id, PROP_IMAGE_LAYOUT_FORMAT) == IMAGE_LAYOUT_FS4


def is_fs5(device_id):
    return get_property_as_string(device_id, PROP_IMAGE_LAYOUT_FORMAT) == IMAGE_LAYOUT_FS5


# ============================================================================
# Enumeration utilities
# ============================================================================

def _is_deprecated(dev_id):
    return False


def get_device_id_from_str(dev_name):
    """Return the integer device ID for the given device name, or DEVICE_HW_ID_UNKNOWN."""
    if not dev_name:
        return DEVICE_HW_ID_UNKNOWN
    # "BlueField4" resolves to BlueField4_PCIID (0xa2df) via the loop, because
    # 0x224's JSON device_name is "ConnectX9" and 0xa2df's is "BlueField4".
    # This matches the C++ get_device_id_from_str and the MFT implementation.
    for dev_id in _DEVICE_VECTOR:
        if get_property_as_string(dev_id, PROP_DEVICE_NAME) == dev_name:
            return dev_id
    return DEVICE_HW_ID_UNKNOWN


def get_all_device_ids():
    """Return the full device vector as a list."""
    return list(_DEVICE_VECTOR)


def get_num_of_devices():
    return len(_DEVICE_VECTOR)


def get_device_name_by_index(i):
    return get_property_as_string(_DEVICE_VECTOR[i], PROP_DEVICE_NAME)


def get_device_name_by_id(dev_id):
    return get_property_as_string(dev_id, PROP_DEVICE_NAME)


def get_all_tracer_supported_ids():
    """Return device IDs supported by tracers (non-deprecated NICs, switches, ArcusE, Arcus2)."""
    result = []
    for dev_id in _DEVICE_VECTOR:
        if _is_deprecated(dev_id):
            continue
        if is_nic(dev_id) or is_switch(dev_id) or dev_id in (ArcusE, Arcus2):
            result.append(dev_id)
    return result


def get_num_of_tracer_supported_devices():
    return len(get_all_tracer_supported_ids())


def get_all_5th_gen_nics():
    return [dev_id for dev_id in _DEVICE_VECTOR if is_5th_gen_nic(dev_id)]


def resolve_functional_device_id(hw_dev_id, rev_id=-1, pci_device_id=0):
    """Resolve the functional device ID from the full hardware identity.

    Returns the eDeviceID enum value (as int) that should be used for all
    property lookups. This handles PCI disambiguation (BlueField4) and
    revision disambiguation.
    """
    from device_properties_data import device_identity_index

    # Priority 1: PCI device ID match (e.g. BlueField4, which shares hw_dev_id
    # 0x224 with ConnectX9 and is disambiguated by its PCI device id).
    if pci_device_id != 0:
        for e in device_identity_index:
            if e['pci_device_id'] == pci_device_id:
                return pci_device_id

    # Priority 2: Exact revision match
    if rev_id >= 0:
        for e in device_identity_index:
            if e['hw_dev_id'] == hw_dev_id and e['hw_rev_id'] == rev_id:
                return (rev_id << 16) | hw_dev_id

    # Priority 3: Base hw_dev_id
    return hw_dev_id
