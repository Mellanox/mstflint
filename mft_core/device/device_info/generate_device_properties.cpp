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

// Build-time generator: reads per-device JSON files and emits
//   device_properties_data.h  (C++ static maps)
//   device_properties_data.py (Python dicts, co-installed with the Py API)
//
// Byte-for-byte compatible with the previous Python generator so downstream
// consumers see no behavior change. Runs on the build host; not shipped.

#include <algorithm>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility>
#include <vector>

#include "json/json.h"

namespace {

const char* const C_LICENSE_HEADER =
    "/*\n"
    " * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES\n"
    " * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.\n"
    " *\n"
    " * This software is available to you under a choice of one of two\n"
    " * licenses.  You may choose to be licensed under the terms of the GNU\n"
    " * General Public License (GPL) Version 2, available from the file\n"
    " * COPYING in the main directory of this source tree, or the\n"
    " * OpenIB.org BSD license below:\n"
    " *\n"
    " *     Redistribution and use in source and binary forms, with or\n"
    " *     without modification, are permitted provided that the following\n"
    " *     conditions are met:\n"
    " *\n"
    " *      - Redistributions of source code must retain the above\n"
    " *        copyright notice, this list of conditions and the following\n"
    " *        disclaimer.\n"
    " *\n"
    " *      - Redistributions in binary form must reproduce the above\n"
    " *        copyright notice, this list of conditions and the following\n"
    " *        disclaimer in the documentation and/or other materials\n"
    " *        provided with the distribution.\n"
    " *\n"
    " * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
    " * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
    " * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
    " * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS\n"
    " * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN\n"
    " * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN\n"
    " * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    " * SOFTWARE.\n"
    " *\n"
    " *  Version: $Id$\n"
    " *\n"
    " */\n";

const char* const PY_LICENSE_HEADER =
    "# SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES\n"
    "# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.\n"
    "#\n"
    "# This software is available to you under a choice of one of two\n"
    "# licenses.  You may choose to be licensed under the terms of the GNU\n"
    "# General Public License (GPL) Version 2, available from the file\n"
    "# COPYING in the main directory of this source tree, or the\n"
    "# OpenIB.org BSD license below:\n"
    "#\n"
    "#     Redistribution and use in source and binary forms, with or\n"
    "#     without modification, are permitted provided that the following\n"
    "#     conditions are met:\n"
    "#\n"
    "#      - Redistributions of source code must retain the above\n"
    "#        copyright notice, this list of conditions and the following\n"
    "#        disclaimer.\n"
    "#\n"
    "#      - Redistributions in binary form must reproduce the above\n"
    "#        copyright notice, this list of conditions and the following\n"
    "#        disclaimer in the documentation and/or other materials\n"
    "#        provided with the distribution.\n"
    "#\n"
    "# THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
    "# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
    "# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
    "# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS\n"
    "# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN\n"
    "# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN\n"
    "# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    "# SOFTWARE.\n"
    "#\n"
    "#  Version: $Id$\n"
    "#\n";

using PropMap = std::map<std::string, std::string>;

struct DeviceEntry
{
    std::string device_id;
    PropMap properties;
};

struct IdentityEntry
{
    uint32_t hw_dev_id;
    int hw_rev_id;
    uint32_t pci_device_id;
    bool is_pci_key;
    std::string key_str;
    std::string device_type_str;
};

std::string int64_to_str(int64_t v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

std::string uint64_to_str(uint64_t v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

// Match Python's str(json_int). jsoncpp exposes ints as Int64 or UInt64; pick
// the widest fitting form so negatives round-trip correctly.
std::string json_int_to_str(const Json::Value& v)
{
    if (v.isInt64())
    {
        return int64_to_str(v.asInt64());
    }
    return uint64_to_str(v.asUInt64());
}

// Reproduce Python's str(list) for a JSON array of ints, i.e. "[1, 2, 3]".
std::string array_to_str(const Json::Value& arr)
{
    std::ostringstream oss;
    oss << '[';
    for (Json::ArrayIndex i = 0; i < arr.size(); ++i)
    {
        if (i > 0)
        {
            oss << ", ";
        }
        const Json::Value& e = arr[i];
        if (e.isBool())
        {
            // Python list repr uses True/False, not true/false.
            oss << (e.asBool() ? "True" : "False");
        }
        else if (e.isIntegral())
        {
            oss << json_int_to_str(e);
        }
        else if (e.isString())
        {
            // Python repr on a str inside a list uses single quotes.
            oss << '\'' << e.asString() << '\'';
        }
        else
        {
            // Nested arrays/objects are not part of the current JSON corpus
            // and would call asString() on a container (LogicError in
            // jsoncpp 1.x). Fail loudly at build time instead of emitting
            // silently broken data.
            std::cerr << "Error: array_to_str encountered non-scalar element" << std::endl;
            std::exit(1);
        }
    }
    oss << ']';
    return oss.str();
}

// Convert a JSON scalar to the same string form the old Python value_to_str
// emitted.
std::string value_to_str(const Json::Value& v)
{
    if (v.isBool())
    {
        return v.asBool() ? "true" : "false";
    }
    if (v.isIntegral())
    {
        return json_int_to_str(v);
    }
    if (v.isString())
    {
        return v.asString();
    }
    // Fallback (no float values exist in the current JSON corpus; the Python
    // side used repr() here for round-tripping).
    return v.asString();
}

// Flatten a nested object into a flat leaf-key -> string map. Non-object
// values are stringified; arrays get the Python-repr form.
void flatten(const Json::Value& obj, PropMap& out)
{
    Json::Value::Members names = obj.getMemberNames();
    for (const std::string& key : names)
    {
        const Json::Value& val = obj[key];
        if (val.isObject())
        {
            flatten(val, out);
        }
        else if (val.isArray())
        {
            out[key] = array_to_str(val);
        }
        else
        {
            out[key] = value_to_str(val);
        }
    }
}

// Derive a valid enumerator token from device_name, mirroring the Python
// version's [^0-9A-Za-z_] -> '_' collapse plus strip.
std::string device_type_name(const PropMap& props)
{
    const std::string kDefault = "DEVICE_HW_ID_UNKNOWN";
    auto it = props.find("device_name");
    if (it == props.end() || it->second.empty())
    {
        return kDefault;
    }
    const std::string& name = it->second;
    std::string token;
    token.reserve(name.size());
    bool prev_underscore = false;
    for (char c : name)
    {
        bool ok = (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
        if (ok)
        {
            token.push_back(c);
            prev_underscore = false;
        }
        else if (!prev_underscore)
        {
            token.push_back('_');
            prev_underscore = true;
        }
    }
    // Strip leading/trailing underscores.
    size_t start = token.find_first_not_of('_');
    size_t end = token.find_last_not_of('_');
    if (start == std::string::npos)
    {
        return kDefault;
    }
    return token.substr(start, end - start + 1);
}

// Parse a device-id token: "0x..." (hex) or decimal.
bool parse_dev_id(const std::string& s, uint32_t& out)
{
    if (s.empty())
    {
        return false;
    }
    char* endp = nullptr;
    unsigned long long v = 0;
    errno = 0;
    if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        v = std::strtoull(s.c_str() + 2, &endp, 16);
    }
    else
    {
        v = std::strtoull(s.c_str(), &endp, 10);
    }
    if (errno != 0 || endp == nullptr || *endp != '\0')
    {
        return false;
    }
    out = static_cast<uint32_t>(v);
    return true;
}

// Deep-merge override into base (one level of nesting; matches the Python).
Json::Value merge_revision(const Json::Value& base, const Json::Value& override_val)
{
    Json::Value merged(Json::objectValue);
    for (const std::string& key : base.getMemberNames())
    {
        merged[key] = base[key];
    }
    for (const std::string& key : override_val.getMemberNames())
    {
        const Json::Value& oval = override_val[key];
        if (oval.isObject() && merged.isMember(key) && merged[key].isObject())
        {
            Json::Value inner = merged[key];
            for (const std::string& ikey : oval.getMemberNames())
            {
                inner[ikey] = oval[ikey];
            }
            merged[key] = inner;
        }
        else
        {
            merged[key] = oval;
        }
    }
    return merged;
}

bool ends_with(const std::string& s, const std::string& suffix)
{
    if (s.size() < suffix.size())
    {
        return false;
    }
    return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool process_json_file(const std::string& path,
                       std::vector<DeviceEntry>& out_entries,
                       std::vector<IdentityEntry>& out_identities)
{
    std::cout << "Processing JSON file: " << path << std::endl;

    std::ifstream in(path.c_str(), std::ios::binary);
    if (!in)
    {
        std::cerr << "Error: cannot open " << path << std::endl;
        return false;
    }
    Json::CharReaderBuilder builder;
    Json::Value data;
    std::string errs;
    if (!Json::parseFromStream(builder, in, &data, &errs))
    {
        std::cerr << "Error parsing " << path << ": " << errs << std::endl;
        return false;
    }

    // For status log parity with the old script.
    std::string base = path;
    size_t slash = base.find_last_of('/');
    if (slash != std::string::npos)
    {
        base = base.substr(slash + 1);
    }
    if (ends_with(base, ".json"))
    {
        base = base.substr(0, base.size() - 5);
    }
    std::cout << "Found device ID: " << base << std::endl;

    for (const std::string& top_key : data.getMemberNames())
    {
        uint32_t hw_dev_id_int = 0;
        if (!parse_dev_id(top_key, hw_dev_id_int))
        {
            std::cout << "WARNING: skipping entry with non-numeric hw_dev_id: '" << top_key << "' in "
                      << path << std::endl;
            continue;
        }

        Json::Value top_val = data[top_key];  // copy; we'll strip metadata below

        Json::Value revisions_block;
        bool has_revisions = false;
        if (top_val.isMember("revisions"))
        {
            revisions_block = top_val["revisions"];
            top_val.removeMember("revisions");
            has_revisions = revisions_block.isObject();
        }
        if (top_val.isMember("legacy_dev_id"))
        {
            top_val.removeMember("legacy_dev_id");
        }
        std::string device_type_enum_override;
        if (top_val.isMember("device_type_enum"))
        {
            device_type_enum_override = top_val["device_type_enum"].asString();
            top_val.removeMember("device_type_enum");
        }

        bool pci_keyed = false;
        if (top_val.isMember("pci_keyed"))
        {
            pci_keyed = top_val["pci_keyed"].asBool();
            top_val.removeMember("pci_keyed");
        }

        std::string pci_id;
        uint32_t pci_id_int = 0;
        if (pci_keyed)
        {
            // Use get()/isMember() so we do not insert an empty "general_info"
            // member into top_val when the field is missing (non-const
            // operator[] would insert, and that empty object would then leak
            // into base_props via flatten()).
            const Json::Value gi = top_val.get("general_info", Json::Value(Json::objectValue));
            const Json::Value lst = gi.get("pci_device_id_list", Json::Value(Json::nullValue));
            if (!lst.isArray() || lst.empty())
            {
                std::cout << "WARNING: skipping pci_keyed device with empty pci_device_id_list: '"
                          << top_key << "' in " << path << std::endl;
                continue;
            }
            pci_id_int = static_cast<uint32_t>(lst[0].asUInt64());
            char buf[32];
            std::snprintf(buf, sizeof(buf), "0x%x", pci_id_int);
            pci_id = buf;
        }

        // Base entry (no specific revision)
        PropMap base_props;
        flatten(top_val, base_props);

        std::string base_device_type =
            device_type_enum_override.empty() ? device_type_name(base_props) : device_type_enum_override;

        DeviceEntry de;
        de.device_id = pci_id.empty() ? top_key : pci_id;
        de.properties = base_props;
        out_entries.push_back(de);

        IdentityEntry ie;
        ie.hw_dev_id = hw_dev_id_int;
        ie.hw_rev_id = -1;
        ie.pci_device_id = pci_id.empty() ? 0u : pci_id_int;
        ie.is_pci_key = !pci_id.empty();
        ie.key_str = de.device_id;
        ie.device_type_str = base_device_type;
        out_identities.push_back(ie);

        if (!has_revisions)
        {
            continue;
        }
        // Iterate revisions in sorted order. This is a lexicographic sort on
        // the string keys (so "10" precedes "2"); do NOT switch to numeric
        // sort - the previous Python generator called sorted() on the same
        // string keys and byte-for-byte parity depends on matching it.
        std::vector<std::string> rev_keys = revisions_block.getMemberNames();
        std::sort(rev_keys.begin(), rev_keys.end());
        for (const std::string& rev_str : rev_keys)
        {
            char* endp = nullptr;
            errno = 0;
            long rev_l = std::strtol(rev_str.c_str(), &endp, 10);
            if (errno != 0 || endp == nullptr || *endp != '\0')
            {
                continue;
            }
            int rev_int = static_cast<int>(rev_l);

            Json::Value rev_override = revisions_block[rev_str];
            std::string rev_type_enum;
            if (rev_override.isMember("device_type_enum"))
            {
                rev_type_enum = rev_override["device_type_enum"].asString();
                rev_override.removeMember("device_type_enum");
            }
            if (rev_override.isMember("legacy_dev_id"))
            {
                rev_override.removeMember("legacy_dev_id");
            }

            Json::Value merged = merge_revision(top_val, rev_override);
            PropMap rev_props;
            flatten(merged, rev_props);

            char buf[32];
            std::snprintf(buf, sizeof(buf), "0x%x",
                          (static_cast<uint32_t>(rev_int) << 16) | hw_dev_id_int);
            std::string rev_key = buf;

            DeviceEntry rde;
            rde.device_id = rev_key;
            rde.properties = rev_props;
            out_entries.push_back(rde);

            IdentityEntry rie;
            rie.hw_dev_id = hw_dev_id_int;
            rie.hw_rev_id = rev_int;
            rie.pci_device_id = 0;
            rie.is_pci_key = false;
            rie.key_str = rev_key;
            rie.device_type_str = rev_type_enum.empty() ? device_type_name(rev_props) : rev_type_enum;
            out_identities.push_back(rie);
        }
    }
    return true;
}

// ---------- Header formatting helpers ----------

const size_t COLUMN_LIMIT = 120;

std::string escape_c_string(const std::string& s)
{
    std::string out;
    out.reserve(s.size());
    for (char c : s)
    {
        if (c == '\\')
        {
            out += "\\\\";
        }
        else if (c == '"')
        {
            out += "\\\"";
        }
        else
        {
            out.push_back(c);
        }
    }
    return out;
}

// Escape for a Python double-quoted string literal. Handles the control
// characters that would otherwise produce a SyntaxError or a semantically
// different literal (raw newline, tab, backslash, embedded quote). Non-ASCII
// bytes are emitted as \xHH so the output stays pure-ASCII regardless of the
// source file encoding declaration.
std::string escape_py_string(const std::string& s)
{
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s)
    {
        switch (c)
        {
        case '\\': out += "\\\\"; break;
        case '"':  out += "\\\""; break;
        case '\n': out += "\\n";  break;
        case '\r': out += "\\r";  break;
        case '\t': out += "\\t";  break;
        default:
            if (c < 0x20 || c >= 0x7f)
            {
                char buf[8];
                std::snprintf(buf, sizeof(buf), "\\x%02x", c);
                out += buf;
            }
            else
            {
                out.push_back(static_cast<char>(c));
            }
        }
    }
    return out;
}

// Pack a list of entry strings into rows that fit inside COLUMN_LIMIT.
// Reproduces the greedy packer from the Python generator so the emitted
// header matches clang-format's bin-packing shape.
std::vector<std::string> pack_entries_into_rows(const std::vector<std::string>& entries,
                                                const std::string& base_indent,
                                                int prefer_cols /* 0 = auto */)
{
    std::vector<std::string> lines;
    if (entries.empty())
    {
        return lines;
    }

    std::vector<int> col_range;
    if (prefer_cols > 0)
    {
        col_range.push_back(prefer_cols);
    }
    else
    {
        for (int n = static_cast<int>(entries.size()); n >= 1; --n)
        {
            col_range.push_back(n);
        }
    }

    for (int num_cols : col_range)
    {
        std::vector<std::vector<std::string>> rows;
        for (size_t i = 0; i < entries.size(); i += num_cols)
        {
            std::vector<std::string> row;
            for (size_t j = i; j < entries.size() && j < i + static_cast<size_t>(num_cols); ++j)
            {
                row.push_back(entries[j]);
            }
            rows.push_back(row);
        }

        std::vector<size_t> col_widths(num_cols, 0);
        for (const auto& row : rows)
        {
            for (size_t idx = 0; idx < row.size(); ++idx)
            {
                col_widths[idx] = std::max(col_widths[idx], row[idx].size());
            }
        }

        size_t max_line_len = base_indent.size();
        for (const auto& row : rows)
        {
            size_t line_len = base_indent.size();
            for (size_t idx = 0; idx < row.size(); ++idx)
            {
                line_len += col_widths[idx];
                if (idx + 1 < row.size())
                {
                    line_len += 1;  // space between columns
                }
            }
            max_line_len = std::max(max_line_len, line_len);
        }

        if (max_line_len <= COLUMN_LIMIT)
        {
            for (const auto& row : rows)
            {
                std::string line = base_indent;
                for (size_t idx = 0; idx < row.size(); ++idx)
                {
                    if (idx + 1 < row.size())
                    {
                        // Pad to column width
                        std::string padded = row[idx];
                        padded.append(col_widths[idx] - padded.size(), ' ');
                        line += padded;
                        line += ' ';
                    }
                    else
                    {
                        line += row[idx];
                    }
                }
                lines.push_back(line);
            }
            return lines;
        }
    }

    // Fallback: one per line.
    for (const std::string& e : entries)
    {
        lines.push_back(base_indent + e);
    }
    return lines;
}

std::vector<std::string> format_property_entries(const PropMap& properties,
                                                 const std::string& entry_indent)
{
    std::vector<std::string> lines;

    std::vector<std::string> entries;
    std::vector<std::pair<std::string, std::string>> long_entries;

    for (const auto& kv : properties)
    {
        std::string escaped_value = escape_c_string(kv.second);
        std::string entry = "{\"" + kv.first + "\", \"" + escaped_value + "\"},";
        size_t entry_len = entry_indent.size() + entry.size();
        if (entry_len > COLUMN_LIMIT)
        {
            long_entries.push_back(std::make_pair(kv.first, escaped_value));
        }
        else
        {
            entries.push_back(entry);
        }
    }

    size_t total_entries = entries.size() + long_entries.size();
    size_t max_entry_len = 0;
    for (const std::string& e : entries)
    {
        max_entry_len = std::max(max_entry_len, e.size());
    }

    bool should_pack = false;
    int prefer_cols = 0;

    if (total_entries == 8)
    {
        should_pack = long_entries.empty() && max_entry_len <= 30;
    }
    else if (total_entries == 9)
    {
        should_pack = false;
    }
    else if (total_entries >= 6)
    {
        should_pack = long_entries.empty() && max_entry_len <= 35;
        prefer_cols = 2;
    }
    else
    {
        should_pack = long_entries.empty() && max_entry_len <= 45;
    }

    if (should_pack)
    {
        std::vector<std::string> packed = pack_entries_into_rows(entries, entry_indent, prefer_cols);
        for (const std::string& l : packed)
        {
            lines.push_back(l);
        }
    }
    else
    {
        for (const std::string& e : entries)
        {
            lines.push_back(entry_indent + e);
        }
        for (const auto& kv : long_entries)
        {
            lines.push_back(entry_indent + "{\"" + kv.first + "\",");
            lines.push_back(entry_indent + " \"" + kv.second + "\"},");
        }
    }
    return lines;
}

bool generate_header(const std::vector<DeviceEntry>& devices,
                     const std::vector<IdentityEntry>& identities,
                     const std::string& output_file)
{
    std::cout << "Generating header file: " << output_file << std::endl;
    std::ofstream f(output_file.c_str(), std::ios::binary);
    if (!f)
    {
        std::cerr << "Error: cannot open " << output_file << " for writing" << std::endl;
        return false;
    }

    const std::string indent = "    ";
    const std::string entry_indent = indent + "  ";
    const std::string entry_list_indent = indent + indent;

    f << C_LICENSE_HEADER;
    f << "#ifndef DEVICE_PROPERTIES_DATA_H\n";
    f << "#define DEVICE_PROPERTIES_DATA_H\n\n";
    f << "#include <stdint.h>\n";
    f << "#include <string>\n";
    f << "#include <unordered_map>\n\n";
    f << "#ifdef __cplusplus\n";
    f << "extern \"C\"\n";
    f << "{\n";
    f << "#endif\n\n";

    // Per-device property maps.
    for (const DeviceEntry& d : devices)
    {
        if (d.device_id.empty() || d.properties.empty())
        {
            continue;
        }
        f << indent << "// Properties map for device " << d.device_id << "\n";
        f << indent << "static const std::unordered_map<std::string, std::string> device_"
          << d.device_id << "_properties = {\n";
        for (const std::string& line : format_property_entries(d.properties, entry_indent))
        {
            f << line << "\n";
        }
        f << indent << "};\n\n";
    }

    // properties_by_device_id map.
    f << indent << "// Main device properties map\n";
    std::string properties_decl = indent
        + "static const std::unordered_map<std::string, "
          "const std::unordered_map<std::string, std::string>&> "
          "properties_by_device_id = {";
    if (properties_decl.size() <= COLUMN_LIMIT)
    {
        f << properties_decl << "\n";
    }
    else
    {
        f << indent
          << "static const std::unordered_map<std::string, const std::unordered_map<std::string, std::string>&>\n";
        f << entry_indent << "properties_by_device_id = {\n";
    }

    std::vector<std::string> device_entries;
    for (const DeviceEntry& d : devices)
    {
        if (d.device_id.empty() || d.properties.empty())
        {
            continue;
        }
        device_entries.push_back("{\"" + d.device_id + "\", device_" + d.device_id + "_properties},");
    }
    for (const std::string& line : pack_entries_into_rows(device_entries, entry_list_indent, 3))
    {
        f << line << "\n";
    }
    f << indent << "};\n\n";

    // Identity index.
    f << indent << "// Device identity index for composite (hw_dev_id, rev_id, pci_device_id) resolution\n";
    f << indent << "struct DeviceIdentityEntry {\n";
    f << indent << "    uint32_t hw_dev_id;\n";
    f << indent << "    int hw_rev_id;\n";
    f << indent << "    uint32_t pci_device_id;\n";
    f << indent << "};\n\n";

    f << indent << "static const struct DeviceIdentityEntry device_identity_index[] = {\n";
    for (const IdentityEntry& ie : identities)
    {
        f << indent << "    {" << ie.hw_dev_id << ", " << ie.hw_rev_id << ", " << ie.pci_device_id
          << "},\n";
    }
    f << indent << "};\n\n";
    f << indent
      << "static const unsigned int device_identity_index_size = sizeof(device_identity_index) / "
         "sizeof(device_identity_index[0]);\n\n";

    f << "#ifdef __cplusplus\n";
    f << "}\n";
    f << "#endif\n\n";
    f << "#endif // DEVICE_PROPERTIES_DATA_H\n";

    return static_cast<bool>(f);
}

bool generate_python_module(const std::vector<DeviceEntry>& devices,
                            const std::vector<IdentityEntry>& identities,
                            const std::string& output_file)
{
    std::cout << "Generating Python module: " << output_file << std::endl;
    std::ofstream f(output_file.c_str(), std::ios::binary);
    if (!f)
    {
        std::cerr << "Error: cannot open " << output_file << " for writing" << std::endl;
        return false;
    }

    f << "#!/usr/bin/env python\n";
    f << "# -*- coding: utf-8 -*-\n";
    f << PY_LICENSE_HEADER;
    f << "\n";
    f << "\"\"\"Auto-generated device properties data module.\n";
    f << "\n";
    f << "This module is automatically generated from JSON device files.\n";
    f << "Do not edit manually.\n";
    f << "\"\"\"\n\n";

    for (const DeviceEntry& d : devices)
    {
        if (d.device_id.empty() || d.properties.empty())
        {
            continue;
        }
        f << "# Properties dictionary for device " << d.device_id << "\n";
        f << "device_" << d.device_id << "_properties = {\n";
        for (const auto& kv : d.properties)
        {
            f << "    \"" << escape_py_string(kv.first) << "\": \""
              << escape_py_string(kv.second) << "\",\n";
        }
        f << "}\n\n";
    }

    f << "# Main device properties dictionary\n";
    f << "properties_by_device_id = {\n";
    for (const DeviceEntry& d : devices)
    {
        if (d.device_id.empty() || d.properties.empty())
        {
            continue;
        }
        f << "    \"" << d.device_id << "\": device_" << d.device_id << "_properties,\n";
    }
    f << "}\n\n";

    f << "# Device identity index for composite resolution\n";
    f << "device_identity_index = [\n";
    for (const IdentityEntry& ie : identities)
    {
        f << "    {\"hw_dev_id\": " << ie.hw_dev_id << ", \"hw_rev_id\": " << ie.hw_rev_id
          << ", \"pci_device_id\": " << ie.pci_device_id << "},\n";
    }
    f << "]\n";

    return static_cast<bool>(f);
}

bool read_file_bytes(const std::string& path, std::string& out)
{
    std::ifstream in(path.c_str(), std::ios::binary);
    if (!in)
    {
        return false;
    }
    std::ostringstream oss;
    oss << in.rdbuf();
    out = oss.str();
    return true;
}

// Overwrite final_path only when its bytes differ from tmp_path, so mtime is
// preserved on no-op runs and downstream compiles aren't retriggered.
void finalize_output(const std::string& tmp_path, const std::string& final_path)
{
    std::string new_bytes;
    if (!read_file_bytes(tmp_path, new_bytes))
    {
        return;
    }
    std::string existing;
    if (read_file_bytes(final_path, existing) && existing == new_bytes)
    {
        std::remove(tmp_path.c_str());
        return;
    }
    std::remove(final_path.c_str());
    std::rename(tmp_path.c_str(), final_path.c_str());
}

int mkdir_p(const std::string& path)
{
    if (mkdir(path.c_str(), 0755) == 0)
    {
        return 0;
    }
    if (errno == EEXIST)
    {
        return 0;
    }
    return -1;
}

}  // namespace

int main(int argc, char** argv)
{
    std::cout << "Starting device properties generation" << std::endl;
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <json_dir> <output_dir>" << std::endl;
        return 1;
    }
    std::string json_dir = argv[1];
    std::string output_dir = argv[2];
    std::cout << "Input JSON directory: " << json_dir << std::endl;
    std::cout << "Output directory: " << output_dir << std::endl;

    if (mkdir_p(output_dir) != 0)
    {
        std::cerr << "Error: cannot create output dir " << output_dir << std::endl;
        return 1;
    }

    DIR* d = opendir(json_dir.c_str());
    if (d == nullptr)
    {
        std::cerr << "Error: JSON directory does not exist: " << json_dir << std::endl;
        return 1;
    }

    std::vector<std::string> files;
    struct dirent* ent;
    while ((ent = readdir(d)) != nullptr)
    {
        std::string name = ent->d_name;
        if (ends_with(name, ".json"))
        {
            files.push_back(json_dir + "/" + name);
        }
    }
    closedir(d);

    std::vector<DeviceEntry> devices;
    std::vector<IdentityEntry> identities;
    for (const std::string& p : files)
    {
        if (!process_json_file(p, devices, identities))
        {
            return 1;
        }
    }

    // Sort devices by device_id (string), matching the Python behavior.
    std::sort(devices.begin(), devices.end(),
              [](const DeviceEntry& a, const DeviceEntry& b) { return a.device_id < b.device_id; });

    // Identities: pci-keyed first, then hw_dev_id, then wildcard-rev after
    // specific-rev, then rev.
    std::sort(identities.begin(), identities.end(),
              [](const IdentityEntry& a, const IdentityEntry& b) {
                  if (a.is_pci_key != b.is_pci_key)
                  {
                      return a.is_pci_key && !b.is_pci_key;
                  }
                  if (a.hw_dev_id != b.hw_dev_id)
                  {
                      return a.hw_dev_id < b.hw_dev_id;
                  }
                  bool a_wild = (a.hw_rev_id == -1);
                  bool b_wild = (b.hw_rev_id == -1);
                  if (a_wild != b_wild)
                  {
                      return !a_wild && b_wild;
                  }
                  return a.hw_rev_id < b.hw_rev_id;
              });

    std::string header_out = output_dir + "/device_properties_data.h";
    std::string python_out = output_dir + "/device_properties_data.py";

    if (!generate_header(devices, identities, header_out + ".tmp"))
    {
        return 1;
    }
    finalize_output(header_out + ".tmp", header_out);

    if (!generate_python_module(devices, identities, python_out + ".tmp"))
    {
        return 1;
    }
    finalize_output(python_out + ".tmp", python_out);

    return 0;
}
