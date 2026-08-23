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

#include "efuse.h"
#include "efuse_config.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <unistd.h>

#include <mtcr.h>
#include <reg_access/reg_access.h>
#include <tools_layouts/reg_access_hca_layouts.h>
#include <tools_layouts/reg_access_switch_layouts.h>
#include <dev_mgt/tools_dev_types.h>
#include <mft_core/mft_core_utils/logger/Logger.h>
#include <common/bit_slice.h>

#ifndef DATA_PATH
#define DATA_PATH "/usr/share/mstflint/efuse"
#endif

#define MQIS_INFO_TYPE_MODEL_NAME 0x1 // MODEL_NAME is part number

static std::string resolve_efuse_config_path()
{
    return std::string(DATA_PATH) + "/" + EFUSE_CONFIG_FILENAME;
}

static std::string instance_label(int inst)
{
    if (inst == 0)
    {
        return "main";
    }
    return "tile[" + std::to_string(inst - 1) + "]";
}

static int32_t sign_extend_6bit(uint8_t val)
{
    if (val & 0x20)
    {
        return static_cast<int32_t>(val | 0xFFFFFFC0);
    }
    return static_cast<int32_t>(val);
}

static int32_t sign_extend_26bit(uint32_t val)
{
    if (val & 0x02000000)
    {
        return static_cast<int32_t>(val | 0xFC000000);
    }
    return static_cast<int32_t>(val);
}

static bool read_device_part_number(mfile* mf, std::string& part_number)
{
    struct reg_access_hca_mqis_reg_ext mqis;
    memset(&mqis, 0, sizeof(mqis));
    mqis.info_type = MQIS_INFO_TYPE_MODEL_NAME;
    mqis.read_length = sizeof(mqis.info_string);

    reg_access_status_t rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqis);
    if (rc != ME_OK)
    {
        LOG.Error("reg_access_mqis failed for part number, rc=" + std::to_string(rc));
        return false;
    }

    int total_len = mqis.info_length;
    if (total_len == 0)
    {
        return false;
    }

    std::vector<char> buf(total_len + 1, '\0');
    int first_chunk = std::min(static_cast<int>(mqis.read_length), total_len);
    memcpy(buf.data(), mqis.info_string, first_chunk);

    int remaining = total_len - first_chunk;
    while (remaining > 0)
    {
        mqis.read_offset = total_len - remaining;
        mqis.read_length =
          remaining > static_cast<int>(sizeof(mqis.info_string)) ? sizeof(mqis.info_string) : remaining;

        rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqis);
        if (rc != ME_OK || mqis.read_length == 0)
        {
            LOG.Error("reg_access_mqis failed for part number, rc=" + std::to_string(rc));
            return false;
        }
        if (mqis.read_offset + mqis.read_length > total_len)
        {
            LOG.Error(
              "mqis.read_offset + mqis.read_length > total_len, read_offset=" + std::to_string(mqis.read_offset) +
              " read_length=" + std::to_string(mqis.read_length) + " total_len=" + std::to_string(total_len));
            return false;
        }
        memcpy(buf.data() + mqis.read_offset, mqis.info_string, mqis.read_length);
        remaining -= mqis.read_length;
    }

    part_number = buf.data();
    LOG.Debug("part_number: " + part_number);
    return true;
}

struct FuseReading
{
    std::string rail_name;
    std::string die_label;
    bool fuse_mismatch;
    double voltage_mv;
};

// Device-neutral view of the MRFV fields this tool consumes. The HCA and switch PRM
// databases declare MRFV as distinct C types whose layouts may diverge, so a reading is
// copied here by the database-specific query and decoded only once.
struct MrfvEntry
{
    u_int8_t fuse_id;
    u_int8_t v;
    u_int8_t fm;
    u_int8_t fm2;
    // Selects which of fm/fm2 holds the mismatch status for the queried fuse_id.
    u_int8_t fm_sel;
    // RAW_AND_VALUE layout
    u_int8_t value_valid;
    u_int32_t value_base;
    u_int8_t value_exponent;
    u_int32_t raw_fuses;
    u_int8_t raw_fuses_highest_bit;
#ifdef EFUSE_CVB_ENABLED
    // CVB layout
    u_int8_t selector;
    u_int8_t selector_cause;
    u_int16_t cvb_voltage;
#endif // EFUSE_CVB_ENABLED
};

// [CVB-DISABLED] cx9 now uses the RAW_AND_VALUE MRFV layout. The CVB layout code paths
// are gated behind EFUSE_CVB_ENABLED (not deleted) so they can be re-enabled if a future
// device needs the MRFV CVB layout. Define EFUSE_CVB_ENABLED to restore.
#ifdef EFUSE_CVB_ENABLED
static const char* cvb_rail_name(int voltage_type)
{
    switch (voltage_type)
    {
        case 0:
            return "dvdd";
        case 1:
            return "avdd";
        case 2:
            return "vdd";
        default:
            return "unknown";
    }
}
#endif // EFUSE_CVB_ENABLED

static void
  decode_raw_and_value(const MrfvEntry& mrfv, const std::string& rail, int inst, std::vector<FuseReading>& readings)
{
    uint8_t value_valid = mrfv.value_valid;
    uint32_t value_base_raw = mrfv.value_base;
    uint8_t value_exponent_raw = mrfv.value_exponent;
    uint8_t raw_fuses_highest_bit = mrfv.raw_fuses_highest_bit;

    if (raw_fuses_highest_bit > 31)
    {
        LOG.Error("raw_fuses_highest_bit=" + std::to_string(raw_fuses_highest_bit) +
                  " out of range for fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst));
        return;
    }

    uint32_t raw_fuses = EXTRACT(mrfv.raw_fuses, 0, raw_fuses_highest_bit + 1);

    LOG.Debug("fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst) +
              " value_valid=" + std::to_string(value_valid) + " value_base=" + std::to_string(value_base_raw) +
              " value_exponent=" + std::to_string(value_exponent_raw) + " raw_fuses=" + std::to_string(raw_fuses) +
              " raw_fuses_highest_bit=" + std::to_string(raw_fuses_highest_bit));

    if (value_valid != 1)
    {
        return;
    }

    int32_t base = sign_extend_26bit(value_base_raw);
    int32_t exponent = sign_extend_6bit(value_exponent_raw);
    double voltage_mv = base * pow(10.0, exponent) * 1000.0;
    readings.push_back({rail, instance_label(inst), false, voltage_mv});
}

#ifdef EFUSE_CVB_ENABLED
static void decode_cvb(const MrfvEntry& mrfv,
                       const std::string& rail,
                       int inst,
                       int voltage_type,
                       std::vector<FuseReading>& readings)
{
    LOG.Debug("fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst) +
              " voltage_type=" + std::to_string(voltage_type) + " selector=" + std::to_string(mrfv.selector) +
              " selector_cause=" + std::to_string(mrfv.selector_cause) +
              " cvb_voltage=" + std::to_string(mrfv.cvb_voltage));

    if (mrfv.selector != 1 || mrfv.selector_cause != 0)
    {
        LOG.Debug("Skipping CVB reading: selector/selector_cause not ready");
        return;
    }
    // Per PRM, MRFV CVB layout reports cvb_voltage directly in mV (unlike the
    // RAW_AND_VALUE layout, which encodes base * 10^exponent volts and is converted to mV above).
    readings.push_back({rail, instance_label(inst), false, static_cast<double>(mrfv.cvb_voltage)});
}
#endif // EFUSE_CVB_ENABLED

// Query MRFV through the switch PRM database and flatten the reading into `entry`.
// [CVB-DISABLED] To restore the CVB layout, re-add the `bool is_cvb, int voltage_type` parameters,
// set `mrfv.data.MRFV_CVB_ext.voltage_type` before the query, and gate each layout's copy on
// `is_cvb` - `data` is a union and only the layout selected by fuse_id is unpacked.
static reg_access_status_t query_mrfv_switch(mfile* mf, int fuse_id, int inst, MrfvEntry& entry)
{
    struct reg_access_switch_MRFV_ext mrfv;
    memset(&mrfv, 0, sizeof(mrfv));
    mrfv.fuse_id = static_cast<u_int8_t>(fuse_id);
    mrfv.instance_id = static_cast<u_int8_t>(inst);

    reg_access_status_t rc = reg_access_mrfv_switch(mf, REG_ACCESS_METHOD_GET, &mrfv);
    if (rc != ME_OK)
    {
        return rc;
    }

    entry.fuse_id = mrfv.fuse_id;
    entry.v = mrfv.v;
    entry.fm = mrfv.fm;
    entry.fm2 = mrfv.fm2;
    entry.fm_sel = mrfv.fm_sel;
    entry.value_valid = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_valid;
    entry.value_base = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_base;
    entry.value_exponent = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_exponent;
    entry.raw_fuses = mrfv.data.MRFV_RAW_AND_VALUE_ext.raw_fuses;
    entry.raw_fuses_highest_bit = mrfv.data.MRFV_RAW_AND_VALUE_ext.raw_fuses_highest_bit;
#ifdef EFUSE_CVB_ENABLED
    entry.selector = mrfv.data.MRFV_CVB_ext.selector;
    entry.selector_cause = mrfv.data.MRFV_CVB_ext.selector_cause;
    entry.cvb_voltage = mrfv.data.MRFV_CVB_ext.cvb_voltage;
#endif // EFUSE_CVB_ENABLED
    return rc;
}

// Query MRFV through the HCA PRM database and flatten the reading into `entry`.
// [CVB-DISABLED] See query_mrfv_switch for how to restore the CVB layout.
static reg_access_status_t query_mrfv_hca(mfile* mf, int fuse_id, int inst, MrfvEntry& entry)
{
    struct reg_access_hca_MRFV_ext mrfv;
    memset(&mrfv, 0, sizeof(mrfv));
    mrfv.fuse_id = static_cast<u_int8_t>(fuse_id);
    mrfv.instance_id = static_cast<u_int8_t>(inst);

    reg_access_status_t rc = reg_access_mrfv(mf, REG_ACCESS_METHOD_GET, &mrfv);
    if (rc != ME_OK)
    {
        return rc;
    }

    entry.fuse_id = mrfv.fuse_id;
    entry.v = mrfv.v;
    entry.fm = mrfv.fm;
    entry.fm2 = mrfv.fm2;
    entry.fm_sel = mrfv.fm_sel;
    entry.value_valid = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_valid;
    entry.value_base = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_base;
    entry.value_exponent = mrfv.data.MRFV_RAW_AND_VALUE_ext.value_exponent;
    entry.raw_fuses = mrfv.data.MRFV_RAW_AND_VALUE_ext.raw_fuses;
    entry.raw_fuses_highest_bit = mrfv.data.MRFV_RAW_AND_VALUE_ext.raw_fuses_highest_bit;
#ifdef EFUSE_CVB_ENABLED
    entry.selector = mrfv.data.MRFV_CVB_ext.selector;
    entry.selector_cause = mrfv.data.MRFV_CVB_ext.selector_cause;
    entry.cvb_voltage = mrfv.data.MRFV_CVB_ext.cvb_voltage;
#endif // EFUSE_CVB_ENABLED
    return rc;
}

// Retimers are described by the switch PRM database; everything else uses the HCA one.
static bool uses_switch_mrfv_layout(dm_dev_id_t dev_type)
{
    return dm_dev_is_switch(dev_type) || dm_dev_is_retimer(dev_type);
}

// Query one MRFV reading and append the decoded value to `readings`.
// [CVB-DISABLED] Only the RAW_AND_VALUE layout is active. To restore the CVB layout,
// re-add `bool is_cvb, int voltage_type` parameters and the `#if 0` branches below.
static void
  query_one_fuse(mfile* mf, dm_dev_id_t dev_type, const FuseConfig& fuse, int inst, std::vector<FuseReading>& readings)
{
    MrfvEntry mrfv;
    memset(&mrfv, 0, sizeof(mrfv));

    LOG.Debug("Querying fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst));

    reg_access_status_t rc = uses_switch_mrfv_layout(dev_type) ? query_mrfv_switch(mf, fuse.fuse_id, inst, mrfv) :
                                                                 query_mrfv_hca(mf, fuse.fuse_id, inst, mrfv);

    if (rc != ME_OK)
    {
        LOG.Error("MRFV query failed for fuse_id=" + std::to_string(fuse.fuse_id) +
                  " instance_id=" + std::to_string(inst) + " error=" + std::to_string(rc));
        return;
    }

    if (mrfv.v != 1)
    {
        LOG.Debug("fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) +
                  " v=" + std::to_string(mrfv.v) + " (not valid). Skipping this fuse reading.");
        return;
    }

    // [CVB-DISABLED] was: is_cvb ? cvb_rail_name(voltage_type) : fuse.name;
    std::string rail = fuse.name;

    // Per PRM, fm_sel picks which field reports the fuse mismatch for the queried fuse_id.
    // Deliberately not gated on MCAM capability bit 95: FW predating fm2/fm_sel returns fm_sel=0,
    // so we fall back to fm. Gate on the bit if older NICs ever need explicit support.
    uint8_t fuse_mismatch = (mrfv.fm_sel == 1) ? mrfv.fm2 : mrfv.fm;

    if (fuse_mismatch == 1)
    {
        readings.push_back({rail, instance_label(inst), true, 0.0});
        return;
    }
    else if (fuse_mismatch != 0)
    {
        LOG.Debug("fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) + " fm_sel=" +
                  std::to_string(mrfv.fm_sel) + " unexpected fuse mismatch value=" + std::to_string(fuse_mismatch));
        return;
    }

    // [CVB-DISABLED] This unconditional call replaces the is_cvb ? decode_cvb : decode_raw_and_value
    // dispatch in the EFUSE_CVB_ENABLED block below. Restore the branch when re-enabling CVB.
    decode_raw_and_value(mrfv, rail, inst, readings);
#ifdef EFUSE_CVB_ENABLED
    if (is_cvb)
    {
        decode_cvb(mrfv, rail, inst, voltage_type, readings);
    }
    else
    {
        decode_raw_and_value(mrfv, rail, inst, readings);
    }
#endif // EFUSE_CVB_ENABLED
}

static std::vector<FuseReading> read_fuse_values(mfile* mf, dm_dev_id_t dev_type, const DeviceConfig& config)
{
    std::vector<FuseReading> readings;

    LOG.Debug(std::string("device_type=") + dm_dev_type2str(dev_type) +
              " using MRFV layout: " + (uses_switch_mrfv_layout(dev_type) ? "switch" : "hca"));

    // [CVB-DISABLED] Only the RAW_AND_VALUE layout is active. To restore the CVB layout,
    // dispatch on `fuse.fuse_id == 0` and iterate `fuse.voltage_types` per PRM.
    for (const auto& fuse : config.fuses)
    {
        for (int inst : fuse.instance_ids)
        {
            query_one_fuse(mf, dev_type, fuse, inst, readings);
        }
    }

    return readings;
}

static void print_fuse_readings(dm_dev_id_t dev_type,
                                u_int32_t hw_dev_id,
                                u_int32_t chip_rev,
                                const std::string& part_number,
                                const std::vector<FuseReading>& readings)
{
    printf("Device:       %s\n", dm_dev_type2str(dev_type));
    printf("HW ID:        %u (rev %u)\n", hw_dev_id, chip_rev);
    if (!part_number.empty())
    {
        printf("Part number:  %s\n", part_number.c_str());
    }

    if (readings.empty())
    {
        printf("\nNo fuse voltage readings available.\n");
        return;
    }

    printf("\nFuse Voltage Readings:\n");
    printf("  %-16s%-16s%s\n", "RAIL", "DIE", "VOLTAGE");
    for (const auto& r : readings)
    {
        if (r.fuse_mismatch)
        {
            printf("  %-16s%-16sFuse mismatch detected\n", r.rail_name.c_str(), r.die_label.c_str());
        }
        else
        {
            printf("  %-16s%-16s%.1f mV\n", r.rail_name.c_str(), r.die_label.c_str(), r.voltage_mv);
        }
    }
}

void EfuseTool::InitCmdParser()
{
    AddDescription("Print fuse voltage readings (from MRFV prm-register).");
    AddOptions(
      "device", 'd', "<device>", "MST device path (required). Example: /dev/mst/mt53124_pciconf0", false, true);
    AddOptions(
      "config", 'c', "<config_file>", "Path to efuse config JSON file (overrides installed config)", false, false);
    AddOptions("help", 'h', "", "Show this help message and exit");
    _cmdParser.AddRequester(this);
}

ParseStatus EfuseTool::HandleOption(std::string name, std::string value)
{
    if (name == "device")
    {
        _device = value;
        return PARSE_OK;
    }
    else if (name == "config")
    {
        _configFile = value;
        return PARSE_OK;
    }
    else if (name == "help")
    {
        printf("%s\n", _cmdParser.GetUsage().c_str());
        return PARSE_OK_WITH_EXIT;
    }
    return PARSE_ERROR;
}

ParseStatus EfuseTool::ParseCmdLine(int argc, char* argv[])
{
    ParseStatus status = _cmdParser.ParseOptions(argc, argv, false);
    if (status != PARSE_OK)
    {
        return status;
    }
    if (_device.empty())
    {
        fprintf(stderr, "-E- Missing device argument. Use -d <mst_device>.\n");
        return PARSE_ERROR_SHOW_USAGE;
    }
    return PARSE_OK;
}

int EfuseTool::Run()
{
    int ret = 1;

    mfile* mf = mopen_adv(_device.c_str(), MST_DEFAULT);
    if (!mf)
    {
        fprintf(stderr, "-E- Failed to open device %s\n", _device.c_str());
        return 1;
    }

    if (dm_is_livefish_mode(mf))
    {
        fprintf(stderr, "-E- Device is in livefish mode. This tool requires running firmware.\n");
        goto cleanup;
    }

    {
        dm_dev_id_t dev_type = DeviceUnknown;
        u_int32_t hw_dev_id = 0;
        u_int32_t dm_hw_rev = 0;
        if (dm_get_device_id(mf, &dev_type, &hw_dev_id, &dm_hw_rev))
        {
            fprintf(stderr, "-E- Failed to identify device.\n");
            goto cleanup;
        }
        // Match efuse_config.json by mfile::rev_id (raw silicon stepping), not
        // tools_dev_types' hw_rev_id, which is normalized (e.g. forced to 0 on the MGIR path).
        u_int32_t chip_rev = mf->rev_id;

        std::string part_number;
        if (!read_device_part_number(mf, part_number))
        {
            LOG.Error("Failed to read part number from device (MQIS register)");
            fprintf(stderr, "-E- Failed to read part number from device.\n");
            goto cleanup;
        }

        std::string config_path;
        if (!_configFile.empty())
        {
            config_path = _configFile;
        }
        else
        {
            config_path = resolve_efuse_config_path();
        }
        if (config_path.empty())
        {
            fprintf(stderr, "-E- Failed to resolve efuse config path.\n");
            goto cleanup;
        }
        DeviceConfig device_config;
        int schema_version = 0;
        std::string config_error;
        if (!load_matching_device_config(config_path,
                                         hw_dev_id,
                                         static_cast<int>(chip_rev),
                                         part_number,
                                         device_config,
                                         schema_version,
                                         config_error))
        {
            LOG.Error(config_error + " hw_dev_id=" + std::to_string(hw_dev_id) +
                      " chip_rev_id=" + std::to_string(chip_rev));
            fprintf(stderr, "-E- %s\n", config_error.c_str());
            goto cleanup;
        }

        if (schema_version != 1)
        {
            fprintf(stderr, "-E- Unsupported schema_version %d. Only version 1 is supported.\n", schema_version);
            goto cleanup;
        }

        std::vector<FuseReading> readings = read_fuse_values(mf, dev_type, device_config);
        print_fuse_readings(dev_type, hw_dev_id, chip_rev, part_number, readings);
        ret = 0;
    }

cleanup:
    mclose(mf);
    return ret;
}

std::string EfuseTool::GetUsage()
{
    return _cmdParser.GetUsage();
}

int main(int argc, char* argv[])
{
    EfuseTool efuse;

    ParseStatus status = efuse.ParseCmdLine(argc, argv);
    if (status == PARSE_OK_WITH_EXIT)
    {
        return 0;
    }
    else if (status == PARSE_ERROR_SHOW_USAGE)
    {
        printf("%s\n", efuse.GetUsage().c_str());
        return 1;
    }
    else if (status != PARSE_OK)
    {
        fprintf(stderr, "-E- Failed to parse arguments.\n");
        printf("%s\n", efuse.GetUsage().c_str());
        return 1;
    }

    return efuse.Run();
}
