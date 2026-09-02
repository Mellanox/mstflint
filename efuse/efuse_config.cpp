/*
 * Copyright (c) 2024-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#include "efuse_config.h"

#include <climits>
#include <fstream>

#include <json/reader.h>
#include <json/value.h>

// [CVB-DISABLED] cx9 now uses the RAW_AND_VALUE layout; CVB 'voltage_types' parsing is
// gated behind EFUSE_CVB_ENABLED to allow re-enabling later.
#ifdef EFUSE_CVB_ENABLED
#define NUMBER_OF_VOLTAGE_TYPES 3 // 0=DVDD, 1=AVDD, 2=VDD
#endif                            // EFUSE_CVB_ENABLED

static bool parse_instance_ids(const Json::Value& instance_ids_node, std::vector<int>& instance_ids, std::string& error)
{
    if (!instance_ids_node.isArray() || instance_ids_node.empty())
    {
        error = "JSON config format error: instance_ids must be a non-empty array";
        return false;
    }

    instance_ids.clear();
    for (Json::ArrayIndex idx = 0; idx < instance_ids_node.size(); idx++)
    {
        const Json::Value& instance_value = instance_ids_node[idx];
        if (!instance_value.isInt())
        {
            error =
              "JSON config format error: instance_ids entry at index " + std::to_string(idx) + " must be an integer";
            return false;
        }
        int val = instance_value.asInt();
        if (val < 0 || val > UINT8_MAX)
        {
            error = "JSON config format error: instance_ids entry at index " + std::to_string(idx) + " value " +
                    std::to_string(val) + " out of valid range [0..255]";
            return false;
        }
        instance_ids.push_back(val);
    }
    return true;
}

static bool parse_fuse_entry(const Json::Value& fuse_node,
                             const std::string& device_path,
                             Json::ArrayIndex fuse_idx,
                             FuseConfig& fuse,
                             std::string& error)
{
    std::string path = device_path + ".fuses[" + std::to_string(fuse_idx) + "]";

    if (!fuse_node.isObject())
    {
        error = "JSON config format error: " + device_path + ".fuses entry at index " + std::to_string(fuse_idx) +
                " must be an object";
        return false;
    }

    if (!fuse_node.isMember("fuse_id"))
    {
        error = "JSON config format error: " + path + " missing required field 'fuse_id'";
        return false;
    }
    const Json::Value& fuse_id_node = fuse_node["fuse_id"];
    if (!fuse_id_node.isInt())
    {
        error = "JSON config format error: " + path + ".fuse_id must be an integer";
        return false;
    }

    if (!fuse_node.isMember("name"))
    {
        error = "JSON config format error: " + path + " missing required field 'name'";
        return false;
    }
    const Json::Value& name_node = fuse_node["name"];
    if (!name_node.isString())
    {
        error = "JSON config format error: " + path + ".name must be a string";
        return false;
    }

    int fuse_id_val = fuse_id_node.asInt();
    if (fuse_id_val < 0 || fuse_id_val > UINT8_MAX)
    {
        error = "JSON config format error: " + path + ".fuse_id value " + std::to_string(fuse_id_val) +
                " out of valid range [0..255]";
        return false;
    }

    fuse.fuse_id = fuse_id_val;
    fuse.name = name_node.asString();

    if (!fuse_node.isMember("instance_ids"))
    {
        error = "JSON config format error: " + path + " missing required field 'instance_ids'";
        return false;
    }
    std::string instance_error;
    if (!parse_instance_ids(fuse_node["instance_ids"], fuse.instance_ids, instance_error))
    {
        error = instance_error + " in " + path;
        return false;
    }

    // [CVB-DISABLED] fuse_id == 0 selects the CVB MRFV layout per PRM. While CVB is disabled,
    // reject configs that use it so a stale entry does not silently get parsed as RAW_AND_VALUE
    // and issue an MRFV read with the wrong layout to hardware.
    if (fuse.fuse_id == 0)
    {
        error = "JSON config format error: " + path +
                ".fuse_id == 0 selects the CVB MRFV layout, which is currently disabled in this build";
        return false;
    }

#ifdef EFUSE_CVB_ENABLED
    // fuse_id == 0 is reserved by the PRM for the CVB MRFV layout and selects it at runtime;
    // any other fuse_id uses the RAW_AND_VALUE layout. 'voltage_types' is required iff fuse_id == 0.
    if (fuse_node.isMember("voltage_types"))
    {
        if (fuse.fuse_id != 0)
        {
            error =
              "JSON config format error: " + path + ".voltage_types is only allowed when fuse_id == 0 (CVB layout)";
            return false;
        }
        if (fuse.instance_ids.size() != 1 || fuse.instance_ids[0] != 0)
        {
            error = "JSON config format error: " + path + ".instance_ids must be [0] for CVB layout (fuse_id == 0)";
            return false;
        }
        const Json::Value& vt_node = fuse_node["voltage_types"];
        if (!vt_node.isArray() || vt_node.empty())
        {
            error = "JSON config format error: " + path + ".voltage_types must be a non-empty array";
            return false;
        }
        for (Json::ArrayIndex idx = 0; idx < vt_node.size(); idx++)
        {
            const Json::Value& v = vt_node[idx];
            if (!v.isInt())
            {
                error = "JSON config format error: " + path + ".voltage_types entry at index " + std::to_string(idx) +
                        " must be an integer";
                return false;
            }
            int val = v.asInt();
            if (val < 0 || val >= NUMBER_OF_VOLTAGE_TYPES)
            {
                error = "JSON config format error: " + path + ".voltage_types entry at index " + std::to_string(idx) +
                        " value " + std::to_string(val) + " out of valid range [0.." +
                        std::to_string(NUMBER_OF_VOLTAGE_TYPES - 1) + "] (0=DVDD, 1=AVDD, 2=VDD)";
                return false;
            }
            fuse.voltage_types.push_back(val);
        }
    }
    else if (fuse.fuse_id == 0)
    {
        error =
          "JSON config format error: " + path + " missing required field 'voltage_types' for CVB layout (fuse_id == 0)";
        return false;
    }
#endif // EFUSE_CVB_ENABLED

    // per_oe (optional): read the fuse per Optical Engine. The tool resolves the OE range from
    // MGPIR at runtime and addresses each OE via the MRFV module_index fields. It reads a single
    // fuse template per OE, so instance_ids must be [0], and it is mutually exclusive with the
    // CVB voltage_types layout (fuse_id == 0).
    if (fuse_node.isMember("per_oe"))
    {
        const Json::Value& per_oe_node = fuse_node["per_oe"];
        if (!per_oe_node.isBool())
        {
            error = "JSON config format error: " + path + ".per_oe must be a boolean";
            return false;
        }
        fuse.per_oe = per_oe_node.asBool();
    }

    if (fuse.per_oe)
    {
        if (fuse.fuse_id == 0)
        {
            error = "JSON config format error: " + path + ".per_oe is not allowed with fuse_id == 0 (CVB layout)";
            return false;
        }
        if (fuse_node.isMember("voltage_types"))
        {
            error = "JSON config format error: " + path + ".per_oe is mutually exclusive with voltage_types";
            return false;
        }
        if (fuse.instance_ids.size() != 1 || fuse.instance_ids[0] != 0)
        {
            error = "JSON config format error: " + path + ".per_oe requires instance_ids to be [0]";
            return false;
        }
    }

    return true;
}

static bool parse_device_match(const Json::Value& device_node,
                               const std::string& device_path,
                               uint32_t& hw_dev_id,
                               int& chip_rev_id,
                               std::string& part_number,
                               std::string& error)
{
    if (!device_node.isMember("match"))
    {
        error = "JSON config format error: " + device_path + " missing required field 'match'";
        return false;
    }
    const Json::Value& match_node = device_node["match"];
    if (!match_node.isObject())
    {
        error = "JSON config format error: " + device_path + ".match must be an object";
        return false;
    }

    if (!match_node.isMember("hw_dev_id"))
    {
        error = "JSON config format error: " + device_path + ".match missing required field 'hw_dev_id'";
        return false;
    }
    const Json::Value& hw_dev_id_node = match_node["hw_dev_id"];
    if (!hw_dev_id_node.isUInt())
    {
        error = "JSON config format error: " + device_path + ".match.hw_dev_id must be a non-negative integer";
        return false;
    }
    hw_dev_id = hw_dev_id_node.asUInt();

    if (!match_node.isMember("chip_rev_id"))
    {
        error = "JSON config format error: " + device_path + ".match missing required field 'chip_rev_id'";
        return false;
    }
    const Json::Value& chip_rev_id_node = match_node["chip_rev_id"];
    if (!chip_rev_id_node.isInt())
    {
        error = "JSON config format error: " + device_path + ".match.chip_rev_id must be an integer";
        return false;
    }
    chip_rev_id = chip_rev_id_node.asInt();

    if (!match_node.isMember("part_number"))
    {
        error = "JSON config format error: " + device_path + ".match missing required field 'part_number'";
        return false;
    }
    const Json::Value& part_number_node = match_node["part_number"];
    if (!part_number_node.isString())
    {
        error = "JSON config format error: " + device_path + ".match.part_number must be a string";
        return false;
    }
    part_number = part_number_node.asString();

    return true;
}

static bool parse_device_fuses(const Json::Value& device_node,
                               const std::string& device_path,
                               DeviceConfig& device,
                               std::string& error)
{
    if (!device_node.isMember("fuses"))
    {
        error = "JSON config format error: " + device_path + " missing required field 'fuses'";
        return false;
    }
    const Json::Value& fuses_node = device_node["fuses"];
    if (!fuses_node.isArray() || fuses_node.empty())
    {
        error = "JSON config format error: " + device_path + ".fuses must be a non-empty array";
        return false;
    }

    for (Json::ArrayIndex fuse_idx = 0; fuse_idx < fuses_node.size(); fuse_idx++)
    {
        FuseConfig fuse;
        if (!parse_fuse_entry(fuses_node[fuse_idx], device_path, fuse_idx, fuse, error))
        {
            return false;
        }
        device.fuses.push_back(fuse);
    }

    return true;
}

bool load_matching_device_config(const std::string& path,
                                 uint32_t target_hw_dev_id,
                                 int target_chip_rev_id,
                                 const std::string& target_part_number,
                                 DeviceConfig& device,
                                 int& schema_version,
                                 std::string& error)
{
    std::ifstream config_file(path);
    if (!config_file.is_open())
    {
        error = "Failed to open config file: " + path;
        return false;
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    Json::Value root;
    std::string parse_errors;
    if (!Json::parseFromStream(builder, config_file, &root, &parse_errors))
    {
        error = "Failed to parse config file: " + parse_errors;
        return false;
    }

    if (!root.isObject())
    {
        error = "JSON config format error: Config root must be a JSON object";
        return false;
    }

    if (!root.isMember("schema_version"))
    {
        error = "JSON config format error: missing required field 'schema_version'";
        return false;
    }
    const Json::Value& schema_node = root["schema_version"];
    if (!schema_node.isInt())
    {
        error = "JSON config format error: schema_version must be an integer";
        return false;
    }
    schema_version = schema_node.asInt();

    if (!root.isMember("devices"))
    {
        error = "JSON config format error: missing required field 'devices'";
        return false;
    }
    const Json::Value& devices_node = root["devices"];
    if (!devices_node.isArray() || devices_node.empty())
    {
        error = "JSON config format error: 'devices' must be a non-empty array";
        return false;
    }

    for (Json::ArrayIndex idx = 0; idx < devices_node.size(); idx++)
    {
        const Json::Value& device_node = devices_node[idx];
        if (!device_node.isObject())
        {
            error = "JSON config format error: devices entry at index " + std::to_string(idx) + " must be an object";
            return false;
        }

        std::string device_path = "devices[" + std::to_string(idx) + "]";

        uint32_t hw_dev_id;
        int chip_rev_id;
        std::string part_number;
        if (!parse_device_match(device_node, device_path, hw_dev_id, chip_rev_id, part_number, error))
        {
            return false;
        }

        if (hw_dev_id != target_hw_dev_id || chip_rev_id != target_chip_rev_id)
        {
            continue;
        }
        // Empty part_number in JSON matches any device part number
        if (!part_number.empty() && part_number != target_part_number)
        {
            continue;
        }

        if (!parse_device_fuses(device_node, device_path, device, error))
        {
            return false;
        }

        device.hw_dev_id = hw_dev_id;
        device.chip_rev_id = chip_rev_id;
        device.part_number = part_number;

        return true;
    }

    error = "No matching device config found for hw_dev_id=" + std::to_string(target_hw_dev_id) +
            " chip_rev_id=" + std::to_string(target_chip_rev_id) + " part_number=" + target_part_number;
    return false;
}
