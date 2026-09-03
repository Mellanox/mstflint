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
#include "nvtoolslogger/NvToolsLogger.h"
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
        MFT_LOG_ERROR(nvtoolslogger::Layer::EFUSE, ("reg_access_mqis failed for part number, rc=" + std::to_string(rc)).c_str());
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
        mqis.read_length = remaining > static_cast<int>(sizeof(mqis.info_string)) ? sizeof(mqis.info_string) : remaining;

        rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqis);
        if (rc != ME_OK || mqis.read_length == 0)
        {
            MFT_LOG_ERROR(nvtoolslogger::Layer::EFUSE, ("reg_access_mqis failed for part number, rc=" + std::to_string(rc)).c_str());
            return false;
        }
        if (mqis.read_offset + mqis.read_length > total_len)
        {
            MFT_LOG_ERROR(nvtoolslogger::Layer::EFUSE, ("mqis.read_offset + mqis.read_length > total_len, read_offset=" + std::to_string(mqis.read_offset) +
              " read_length=" + std::to_string(mqis.read_length) + " total_len=" + std::to_string(total_len)).c_str());
            return false;
        }
        memcpy(buf.data() + mqis.read_offset, mqis.info_string, mqis.read_length);
        remaining -= mqis.read_length;
    }

    part_number = buf.data();
    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("part_number: " + part_number).c_str());
    return true;
}

struct FuseReading
{
    std::string rail_name;
    std::string die_label;
    bool fuse_mismatch;
    bool is_raw; // true: value is raw fuse bits (print as hex); false: voltage_mv (print as mV)
    double voltage_mv;
    uint32_t raw_value;
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

static void decode_raw_and_value(const MrfvEntry& mrfv, const std::string& rail, int inst, const std::string& die_label, bool allow_raw, std::vector<FuseReading>& readings)
{
    uint8_t value_valid = mrfv.value_valid;
    uint32_t value_base_raw = mrfv.value_base;
    uint8_t value_exponent_raw = mrfv.value_exponent;
    uint8_t raw_fuses_highest_bit = mrfv.raw_fuses_highest_bit;

    if (raw_fuses_highest_bit > 31)
    {
        MFT_LOG_ERROR(nvtoolslogger::Layer::EFUSE, ("raw_fuses_highest_bit=" + std::to_string(raw_fuses_highest_bit) + " out of range for fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst)).c_str());
        return;
    }

    uint32_t raw_fuses = EXTRACT(mrfv.raw_fuses, 0, raw_fuses_highest_bit + 1);

    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst) + " value_valid=" + std::to_string(value_valid) + " value_base=" + std::to_string(value_base_raw) +
              " value_exponent=" + std::to_string(value_exponent_raw) + " raw_fuses=" + std::to_string(raw_fuses) + " raw_fuses_highest_bit=" + std::to_string(raw_fuses_highest_bit)).c_str());

    if (value_valid != 1)
    {
        // value_valid qualifies only value_base/value_exponent, which encode a physical quantity.
        // Identity fuses have none (SPC6 CPO per-OE fuses 17-24), so they report value_valid == 0
        // while raw_fuses stays valid: report the raw bits, masked to raw_fuses_highest_bit + 1
        // above. For voltage fuses the raw bits carry no meaning without base/exponent, so skip.
        if (allow_raw)
        {
            readings.push_back({rail, die_label, false, true, 0.0, raw_fuses});
        }
        return;
    }

    int32_t base = sign_extend_26bit(value_base_raw);
    int32_t exponent = sign_extend_6bit(value_exponent_raw);
    double voltage_mv = base * pow(10.0, exponent) * 1000.0;
    readings.push_back({rail, die_label, false, false, voltage_mv, 0});
}

#ifdef EFUSE_CVB_ENABLED
static void decode_cvb(const MrfvEntry& mrfv, const std::string& rail, int inst, int voltage_type, std::vector<FuseReading>& readings)
{
    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("fuse_id=" + std::to_string(mrfv.fuse_id) + " instance_id=" + std::to_string(inst) + " voltage_type=" + std::to_string(voltage_type) + " selector=" + std::to_string(mrfv.selector) +
              " selector_cause=" + std::to_string(mrfv.selector_cause) + " cvb_voltage=" + std::to_string(mrfv.cvb_voltage)).c_str());

    if (mrfv.selector != 1 || mrfv.selector_cause != 0)
    {
        MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, "Skipping CVB reading: selector/selector_cause not ready");
        return;
    }
    // Per PRM, MRFV CVB layout reports cvb_voltage directly in mV (unlike the
    // RAW_AND_VALUE layout, which encodes base * 10^exponent volts and is converted to mV above).
    readings.push_back({rail, instance_label(inst), false, false, static_cast<double>(mrfv.cvb_voltage), 0});
}
#endif // EFUSE_CVB_ENABLED

// Query MRFV through the switch PRM database and flatten the reading into `entry`.
// [CVB-DISABLED] To restore the CVB layout, re-add the `bool is_cvb, int voltage_type` parameters,
// set `mrfv.data.MRFV_CVB_ext.voltage_type` before the query, and gate each layout's copy on
// `is_cvb` - `data` is a union and only the layout selected by fuse_id is unpacked.
static reg_access_status_t query_mrfv_switch(mfile* mf, int fuse_id, int inst, int module_index, MrfvEntry& entry)
{
    struct reg_access_switch_MRFV_ext mrfv;
    memset(&mrfv, 0, sizeof(mrfv));
    mrfv.fuse_id = static_cast<u_int8_t>(fuse_id);
    mrfv.instance_id = static_cast<u_int8_t>(inst);
    // Per-OE fuses (SPC6 CPO) address the Optical Engine via <module_index_msb, module_index>.
    if (module_index >= 0)
    {
        mrfv.module_index_valid = 1;
        mrfv.module_index = static_cast<u_int8_t>(module_index & 0xFF);
        mrfv.module_index_msb = static_cast<u_int8_t>((module_index >> 8) & 0xFF);
    }

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
static reg_access_status_t query_mrfv_hca(mfile* mf, int fuse_id, int inst, int module_index, MrfvEntry& entry)
{
    struct reg_access_hca_MRFV_ext mrfv;
    memset(&mrfv, 0, sizeof(mrfv));
    mrfv.fuse_id = static_cast<u_int8_t>(fuse_id);
    mrfv.instance_id = static_cast<u_int8_t>(inst);
    // Per-OE fuses (SPC6 CPO) address the Optical Engine via <module_index_msb, module_index>.
    if (module_index >= 0)
    {
        mrfv.module_index_valid = 1;
        mrfv.module_index = static_cast<u_int8_t>(module_index & 0xFF);
        mrfv.module_index_msb = static_cast<u_int8_t>((module_index >> 8) & 0xFF);
    }

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
static void query_one_fuse(mfile* mf, dm_dev_id_t dev_type, const FuseConfig& fuse, int inst, int module_index, const std::string& die_label, std::vector<FuseReading>& readings)
{
    MrfvEntry mrfv;
    memset(&mrfv, 0, sizeof(mrfv));

    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("Querying fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) + " module_index=" + std::to_string(module_index)).c_str());

    reg_access_status_t rc = uses_switch_mrfv_layout(dev_type) ? query_mrfv_switch(mf, fuse.fuse_id, inst, module_index, mrfv) : query_mrfv_hca(mf, fuse.fuse_id, inst, module_index, mrfv);

    if (rc != ME_OK)
    {
        MFT_LOG_ERROR(nvtoolslogger::Layer::EFUSE, ("MRFV query failed for fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) + " error=" + std::to_string(rc)).c_str());
        return;
    }

    if (mrfv.v != 1)
    {
        MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) + " v=" + std::to_string(mrfv.v) + " (not valid). Skipping this fuse reading.").c_str());
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
        readings.push_back({rail, die_label, true, false, 0.0, 0});
        return;
    }
    else if (fuse_mismatch != 0)
    {
        MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("fuse_id=" + std::to_string(fuse.fuse_id) + " instance_id=" + std::to_string(inst) + " unexpected fm=" + std::to_string(mrfv.fm) + " fm_sel=" + std::to_string(mrfv.fm_sel)).c_str());
        return;
    }

    // [CVB-DISABLED] This unconditional call replaces the is_cvb ? decode_cvb : decode_raw_and_value
    // dispatch in the EFUSE_CVB_ENABLED block below. Restore the branch when re-enabling CVB.
    decode_raw_and_value(mrfv, rail, inst, die_label, fuse.per_oe, readings);
#ifdef EFUSE_CVB_ENABLED
    if (is_cvb)
    {
        decode_cvb(mrfv, rail, inst, voltage_type, readings);
    }
    else
    {
        decode_raw_and_value(mrfv, rail, inst, die_label, fuse.per_oe, readings);
    }
#endif // EFUSE_CVB_ENABLED
}

// Resolve the Optical Engine index range for per-OE fuses. Per-OE fuses only exist on SPC6 CPO,
// so gate on MGIR.cpo_indication: on non-CPO systems (cpo_indication == 0) the per-OE fuses are
// skipped cleanly (oe_enabled stays false). A register read failure only costs the per-OE fuses,
// so warn and leave oe_enabled false rather than failing the whole run.
static void resolve_oe_range(mfile* mf, bool& oe_enabled, int& oe_base, int& oe_count)
{
    oe_enabled = false;
    oe_base = 0;
    oe_count = 0;

    struct reg_access_hca_mgir_ext mgir;
    memset(&mgir, 0, sizeof(mgir));
    reg_access_status_t rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
    if (rc != ME_OK)
    {
        fprintf(stderr, "-W- Failed to read MGIR register (rc=%d). Skipping per-Optical-Engine fuses.\n", rc);
        return;
    }
    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("MGIR cpo_indication=" + std::to_string(mgir.hw_info.cpo_indication)).c_str());
    if (mgir.hw_info.cpo_indication == 0)
    {
        MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, "MGIR.cpo_indication == 0 (non-CPO): skipping per-OE fuses");
        return;
    }

    // The OE range comes from the switch MGPIR layout (hw_info.oe_count_local,
    // hw_metadata.oe_base_index_local).
    struct reg_access_switch_mgpir_ext mgpir;
    memset(&mgpir, 0, sizeof(mgpir));
    // The OE fields are scoped to the ASIC (chip/package) rather than to a slot, so slot_index
    // only has to name the main board (0), as in dev_mgt/therm_fw.c.
    mgpir.hw_info.slot_index = 0;
    rc = reg_access_mgpir_switch_ext(mf, REG_ACCESS_METHOD_GET, &mgpir);
    if (rc != ME_OK)
    {
        fprintf(stderr, "-W- Failed to read MGPIR register (rc=%d). Skipping per-Optical-Engine fuses.\n", rc);
        return;
    }

    oe_base = mgpir.hw_metadata.oe_base_index_local;
    oe_count = mgpir.hw_info.oe_count_local;
    oe_enabled = (oe_count > 0);
    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("MGPIR oe_base_index_local=" + std::to_string(oe_base) + " oe_count_local=" + std::to_string(oe_count)).c_str());
}

static bool read_fuse_values(mfile* mf, dm_dev_id_t dev_type, const DeviceConfig& config, std::vector<FuseReading>& readings, std::string& error)
{
    MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, (std::string("device_type=") + dm_dev_type2str(dev_type) + " using MRFV layout: " + (uses_switch_mrfv_layout(dev_type) ? "switch" : "hca")).c_str());

    // Resolve the OE range once, only if the matched device has any per-OE fuse.
    bool has_per_oe = std::any_of(config.fuses.begin(), config.fuses.end(), [](const FuseConfig& f) { return f.per_oe; });
    bool oe_enabled = false;
    int oe_base = 0;
    int oe_count = 0;
    if (has_per_oe)
    {
        // per_oe enumerates Optical Engines using the switch MGPIR OE fields
        // (hw_metadata.oe_base_index_local, hw_info.oe_count_local). The NIC/HCA MGPIR layout
        // (reg_access_mgpir / tools_mgpir) does not expose these OE fields, so per_oe is only
        // supported on switch devices. Fail clearly instead of reading OE data that isn't there.
        if (!uses_switch_mrfv_layout(dev_type))
        {
            error = "per_oe fuses require the switch MGPIR Optical Engine fields, which are not available on non-switch devices";
            return false;
        }
        resolve_oe_range(mf, oe_enabled, oe_base, oe_count);
    }

    // [CVB-DISABLED] Only the RAW_AND_VALUE layout is active. To restore the CVB layout,
    // dispatch on `fuse.fuse_id == 0` and iterate `fuse.voltage_types` per PRM.
    for (const auto& fuse : config.fuses)
    {
        if (fuse.per_oe)
        {
            if (!oe_enabled)
            {
                // non-CPO or no OEs: skip per-OE fuses cleanly
                MFT_LOG_DEBUG(nvtoolslogger::Layer::EFUSE, ("Skipping per-OE fuse_id=" + std::to_string(fuse.fuse_id) + " (" + fuse.name + "): no Optical Engines reported (oe_count=" + std::to_string(oe_count) + ")").c_str());
                continue;
            }
            for (int i = oe_base; i < oe_base + oe_count; i++)
            {
                query_one_fuse(mf, dev_type, fuse, 0, i, "oe[" + std::to_string(i) + "]", readings);
            }
        }
        else
        {
            for (int inst : fuse.instance_ids)
            {
                query_one_fuse(mf, dev_type, fuse, inst, -1, instance_label(inst), readings);
            }
        }
    }

    return true;
}

static void print_fuse_readings(dm_dev_id_t dev_type, u_int32_t hw_dev_id, u_int32_t chip_rev, const std::string& part_number, const std::vector<FuseReading>& readings)
{
    printf("Device:       %s\n", dm_dev_type2str(dev_type));
    printf("HW ID:        %u (rev %u)\n", hw_dev_id, chip_rev);
    if (!part_number.empty())
    {
        printf("Part number:  %s\n", part_number.c_str());
    }

    if (readings.empty())
    {
        printf("\nNo fuse readings available.\n");
        return;
    }

    // Pad the columns to the widest entry so long rail or die names keep a gap to the
    // next column instead of running into it.
    const int column_gap = 2;
    int rail_col = static_cast<int>(strlen("RAIL"));
    int die_col = static_cast<int>(strlen("DIE"));
    for (const auto& r : readings)
    {
        rail_col = std::max(rail_col, static_cast<int>(r.rail_name.size()));
        die_col = std::max(die_col, static_cast<int>(r.die_label.size()));
    }
    rail_col += column_gap;
    die_col += column_gap;

    printf("\nFuse Readings:\n");
    printf("  %-*s%-*s%s\n", rail_col, "RAIL", die_col, "DIE", "VALUE");
    for (const auto& r : readings)
    {
        if (r.fuse_mismatch)
        {
            printf("  %-*s%-*sFuse mismatch detected\n", rail_col, r.rail_name.c_str(), die_col, r.die_label.c_str());
        }
        else if (r.is_raw)
        {
            printf("  %-*s%-*s0x%X\n", rail_col, r.rail_name.c_str(), die_col, r.die_label.c_str(), r.raw_value);
        }
        else
        {
            printf("  %-*s%-*s%.1f mV\n", rail_col, r.rail_name.c_str(), die_col, r.die_label.c_str(), r.voltage_mv);
        }
    }
}

void EfuseTool::InitCmdParser()
{
    AddDescription("Print fuse voltage readings (from MRFV prm-register).");
    AddOptions("device", 'd', "<device>", "MST device path (required). Example: /dev/mst/mt53124_pciconf0", false, true);
    AddOptions("config", 'c', "<config_file>", "Path to efuse config JSON file (overrides installed config)", false, false);
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
        u_int32_t dm_hw_rev = 0; // unused; tools_dev_types hw_rev_id is not the chip stepping
        if (dm_get_device_id(mf, &dev_type, &hw_dev_id, &dm_hw_rev))
        {
            fprintf(stderr, "-E- Failed to identify device.\n");
            goto cleanup;
        }
        (void)dm_hw_rev;
        // Match efuse_config.json by the raw chip revision reported by the device
        // (mfile::rev_id), not by tools_dev_types' hw_rev_id, which is normalized
        // (e.g. forced to 0 on the MGIR path) and does not reflect the silicon stepping.
        u_int32_t chip_rev = mf->rev_id;

        std::string part_number;
        if (!read_device_part_number(mf, part_number))
        {
            fprintf(stderr, "-E- Failed to read part number from device (MQIS register).\n");
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
        if (!load_matching_device_config(config_path, hw_dev_id, static_cast<int>(chip_rev), part_number, device_config, schema_version, config_error))
        {
            fprintf(stderr, "-E- %s\n", config_error.c_str());
            goto cleanup;
        }

        if (schema_version != 1)
        {
            fprintf(stderr, "-E- Unsupported schema_version %d. Only version 1 is supported.\n", schema_version);
            goto cleanup;
        }

        std::vector<FuseReading> readings;
        std::string read_error;
        if (!read_fuse_values(mf, dev_type, device_config, readings, read_error))
        {
            fprintf(stderr, "-E- %s\n", read_error.c_str());
            goto cleanup;
        }
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
