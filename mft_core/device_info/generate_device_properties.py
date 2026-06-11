#!/usr/bin/env python3
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

"""Generate from JSON files a header (device_properties_data.h) and a Python module (device_properties_data.py)
with device properties in std::unordered_map and dict data structures.

Usage:
    python generate_device_properties.py <json_dir> <output_dir>

Arguments:
    json_dir    - Directory containing JSON files (one file per device)
    output_dir  - Output directory for generated header file and Python module

Input:
    - JSON files where filename (without .json extension) becomes the device ID
    - JSON content is recursively flattened into key-value pairs
    - Nested dictionaries are flattened, lists/arrays converted to strings
    - Booleans converted to "true"/"false" string literals

Output:
    - device_properties_data.h containing:
        * device_<id>_properties map for each device
        * properties_by_device_id map indexing all device's properties maps by device ID
    - device_properties_data.py containing:
        * device_<id>_properties dict for each device
        * properties_by_device_id dict indexing all device's properties dicts by device ID
    - All values stored as std::string (C++) or str (Python) with proper escaping

Compatibility:
    - Python 3 only
"""

import os
import sys
import errno
import json
import argparse


def value_to_str(value):
    """Convert a JSON scalar to a deterministic string representation.

    Uses repr() for floats so the shortest round-trippable form is emitted,
    keeping the generated output reproducible across interpreter versions.
    """
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, float):
        return repr(value)
    return str(value)


def process_json_file(json_file):
    """Process a single JSON file and return device ID and properties map."""
    print("Processing JSON file: {0}".format(json_file))

    # Always read as UTF-8 so the parsed content (and thus the generated
    # output) does not depend on the locale's default encoding.
    f = open(json_file, 'r', encoding='utf-8')
    try:
        data = json.load(f)
    finally:
        f.close()

    device_id = os.path.splitext(os.path.basename(json_file))[0]
    print("Found device ID: {0}".format(device_id))

    # Create a map for this device's properties
    properties = {}

    def set_property(key, new_value):
        # Flattening discards parent keys, so the same leaf name appearing
        # under different nested objects collides. Silently keeping the
        # last-written value would make the output depend on dict iteration
        # order (hash-randomized on Python <= 3.6). Fail loudly instead when
        # the colliding values actually differ.
        if key in properties and properties[key] != new_value:
            raise ValueError(
                "Conflicting values for flattened key '{0}': '{1}' vs '{2}'".format(
                    key, properties[key], new_value))
        properties[key] = new_value

    def flatten_dict(d):
        for key, value in d.items():
            if isinstance(value, dict):
                # Recursively flatten nested dictionaries
                flatten_dict(value)
            elif isinstance(value, list):
                # Handle lists by converting them to strings
                set_property(key, str(value))
            else:
                # Convert value to a deterministic string
                set_property(key, value_to_str(value))

    # Flatten the entire data structure
    flatten_dict(data)

    return device_id, properties


C_LICENSE_HEADER = """\
/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *  Version: $Id$
 *
 */
"""

PY_LICENSE_HEADER = """\
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
"""


def generate_header(devices, output_file):
    """Generate the C header file with device properties data."""
    print("Generating header file: {0}".format(output_file))
    # newline='\n' keeps line endings LF on every OS; encoding='utf-8' makes bytes locale-independent.
    f = open(output_file, 'w', encoding='utf-8', newline='\n')
    try:
        indent = '    '
        entry_indent = indent + '  '
        entry_list_indent = indent + indent
        column_limit = 120

        f.write(C_LICENSE_HEADER)
        f.write('#ifndef DEVICE_PROPERTIES_DATA_H\n')
        f.write('#define DEVICE_PROPERTIES_DATA_H\n\n')
        f.write('#include <string>\n')
        f.write('#include <unordered_map>\n\n')
        f.write('#ifdef __cplusplus\n')
        f.write('extern "C"\n')
        f.write('{\n')
        f.write('#endif\n\n')

        def pack_entries_into_rows(entries, base_indent, prefer_cols=None):
            if not entries:
                return []
            if prefer_cols:
                col_range = [prefer_cols]
            else:
                col_range = range(len(entries), 0, -1)
            for num_cols in col_range:
                rows = []
                for i in range(0, len(entries), num_cols):
                    rows.append(entries[i:i + num_cols])
                col_widths = [0] * num_cols
                for row in rows:
                    for idx, entry in enumerate(row):
                        col_widths[idx] = max(col_widths[idx], len(entry))
                max_line_len = len(base_indent)
                for row in rows:
                    line_len = len(base_indent)
                    for idx, entry in enumerate(row):
                        line_len += col_widths[idx]
                        if idx < len(row) - 1:
                            line_len += 1
                    max_line_len = max(max_line_len, line_len)
                if max_line_len <= column_limit:
                    lines = []
                    for row in rows:
                        parts = []
                        for idx, entry in enumerate(row):
                            if idx < len(row) - 1:
                                parts.append(entry.ljust(col_widths[idx]))
                            else:
                                parts.append(entry)
                        lines.append(base_indent + ' '.join(parts))
                    return lines
            return [base_indent + entry for entry in entries]

        def format_property_entries(properties):
            lines = []
            sorted_keys = sorted(properties.keys())
            entries = []
            long_entries = []
            for key in sorted_keys:
                value = properties[key]
                str_value = str(value)
                escaped_value = str_value.replace('\\', '\\\\').replace('"', '\\"')
                entry = '{{"{}","{}"}},'.format(key, escaped_value)
                entry_len = len(entry_indent) + len(entry)
                if entry_len > column_limit:
                    long_entries.append((key, escaped_value))
                else:
                    entries.append(entry)
            total_entries = len(entries) + len(long_entries)
            max_entry_len = max([len(e) for e in entries]) if entries else 0
            should_pack = False
            prefer_cols = None
            if total_entries == 8:
                should_pack = len(long_entries) == 0 and max_entry_len <= 30
            elif total_entries == 9:
                should_pack = False
            elif total_entries >= 6:
                should_pack = len(long_entries) == 0 and max_entry_len <= 35
                prefer_cols = 2
            else:
                should_pack = len(long_entries) == 0 and max_entry_len <= 45
            if should_pack:
                lines.extend(pack_entries_into_rows(entries, entry_indent, prefer_cols))
            else:
                for entry in entries:
                    lines.append(entry_indent + entry)
                for key, escaped_value in long_entries:
                    lines.append('{}{{"{}",'.format(entry_indent, key))
                    lines.append('{} "{}"}},'.format(entry_indent, escaped_value))
            return lines

        for device_id, properties in devices:
            if device_id and properties:
                f.write('{}// Properties map for device {}\n'.format(indent, device_id))
                f.write('{}static const std::unordered_map<std::string, std::string> device_{}_properties = {{\n'.format(
                    indent, device_id))
                for line in format_property_entries(properties):
                    f.write('{}\n'.format(line))
                f.write('{}}};\n\n'.format(indent))

        f.write('{}// Main device properties map\n'.format(indent))
        properties_decl = ('{}static const std::unordered_map<std::string, '
                           'const std::unordered_map<std::string, std::string>&> '
                           'properties_by_device_id = {{').format(indent)
        if len(properties_decl) <= column_limit:
            f.write(properties_decl + '\n')
        else:
            f.write('{}static const std::unordered_map<std::string, const std::unordered_map<std::string, std::string>&>\n'.format(indent))
            f.write('{}properties_by_device_id = {{\n'.format(entry_indent))

        device_entries = []
        for device_id, properties in devices:
            if device_id and properties:
                device_entries.append('{{"{}",device_{}_properties}},'.format(device_id, device_id))

        packed_lines = pack_entries_into_rows(device_entries, entry_list_indent, prefer_cols=3)
        for line in packed_lines:
            f.write('{}\n'.format(line))
        f.write('{}}};\n\n'.format(indent))

        f.write('#ifdef __cplusplus\n')
        f.write('}\n')
        f.write('#endif\n\n')
        f.write('#endif // DEVICE_PROPERTIES_DATA_H\n')
    finally:
        f.close()
    print("Header file generated successfully")


def generate_python_module(devices, output_file):
    """Generate the Python module with device properties data."""
    print("Generating Python module: {0}".format(output_file))
    f = open(output_file, 'w', encoding='utf-8', newline='\n')
    try:
        f.write('#!/usr/bin/env python\n')
        f.write('# -*- coding: utf-8 -*-\n')
        f.write(PY_LICENSE_HEADER)
        f.write('\n')
        f.write('"""Auto-generated device properties data module.\n')
        f.write('\n')
        f.write('This module is automatically generated from JSON device files.\n')
        f.write('Do not edit manually.\n')
        f.write('"""\n\n')
        for device_id, properties in devices:
            if device_id and properties:
                f.write('# Properties dictionary for device {0}\n'.format(device_id))
                f.write('device_{0}_properties = {{\n'.format(device_id))
                for key, value in sorted(properties.items()):
                    str_value = str(value)
                    escaped_value = str_value.replace('\\', '\\\\').replace('"', '\\"')
                    f.write('    "{0}": "{1}",\n'.format(key, escaped_value))
                f.write('}\n\n')
        f.write('# Main device properties dictionary\n')
        f.write('properties_by_device_id = {\n')
        for device_id, properties in devices:
            if device_id and properties:
                f.write('    "{0}": device_{0}_properties,\n'.format(device_id))
        f.write('}\n')
    finally:
        f.close()
    print("Python module generated successfully")


def main():
    print("Starting device properties generation")

    parser = argparse.ArgumentParser(description='Generate device properties header file')
    parser.add_argument('json_dir', help='Directory containing JSON files')
    parser.add_argument('output_dir', help='Directory for generated files')
    args = parser.parse_args()
    json_dir = os.path.abspath(args.json_dir)
    output_dir = os.path.abspath(args.output_dir)

    print("Input JSON directory: {0}".format(json_dir))
    print("Output directory: {0}".format(output_dir))

    try:
        os.makedirs(output_dir)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise

    devices = []
    failed_files = []
    if not os.path.exists(json_dir):
        sys.stderr.write("Error: JSON directory does not exist: {0}\n".format(json_dir))
        sys.exit(1)

    for json_file in os.listdir(json_dir):
        if json_file.endswith('.json'):
            full_path = os.path.join(json_dir, json_file)
            try:
                device_id, properties = process_json_file(full_path)
                devices.append((device_id, properties))
            except Exception as e:
                sys.stderr.write("Error processing {0}: {1}\n".format(full_path, str(e)))
                failed_files.append(full_path)

    if failed_files:
        sys.stderr.write("Failed to process {0} file(s):\n".format(len(failed_files)))
        for f in failed_files:
            sys.stderr.write("  {0}\n".format(f))
        sys.exit(1)

    # Sort devices by device_id for deterministic output
    devices.sort(key=lambda x: x[0])

    generate_header(devices, os.path.join(output_dir, 'device_properties_data.h'))
    generate_python_module(devices, os.path.join(output_dir, 'device_properties_data.py'))


if __name__ == '__main__':
    main()
