/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#include "cable_fw_manager.h"
#include "err_msgs.h"
#include "dev_mgt/tools_dev_types.h"
#include "mflash/mflash_types.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_switch_layouts.h"

/* Every MMAM.module_type the PRM defines. */
enum MmamModuleType
{
    MMAM_MODULE_TYPE_BACKPLANE_4X = 0,
    MMAM_MODULE_TYPE_QSFP = 1,
    MMAM_MODULE_TYPE_SFP = 2,
    MMAM_MODULE_TYPE_NO_CAGE = 3,
    MMAM_MODULE_TYPE_BACKPLANE_1X = 4,
    MMAM_MODULE_TYPE_BACKPLANE_2X = 8,
    MMAM_MODULE_TYPE_CHIP2CHIP_4X = 10,
    MMAM_MODULE_TYPE_CHIP2CHIP_2X = 11,
    MMAM_MODULE_TYPE_CHIP2CHIP_1X = 12,
    MMAM_MODULE_TYPE_QSFP_DD = 14,
    MMAM_MODULE_TYPE_OSFP = 15,
    MMAM_MODULE_TYPE_SFP_DD = 16,
    MMAM_MODULE_TYPE_DSFP = 17,
    MMAM_MODULE_TYPE_CHIP2CHIP_8X = 18,
    MMAM_MODULE_TYPE_TWISTED_PAIR = 19,
    MMAM_MODULE_TYPE_BACKPLANE_8X = 20,
    MMAM_MODULE_TYPE_LOOPBACK = 21,
    MMAM_MODULE_TYPE_OE_16X = 22,
    MMAM_MODULE_TYPE_OSFP_ELS = 23,
    MMAM_MODULE_TYPE_QSFP_2X = 24,
    MMAM_MODULE_TYPE_CPO_32X = 25,
    MMAM_MODULE_TYPE_ELS_16 = 26,
    MMAM_MODULE_TYPE_CPO_64X = 27,
    MMAM_MODULE_TYPE_QSFP_1X = 28,
    MMAM_MODULE_TYPE_NPO_16X = 29
};

/* Whether MMAM.ga names the ASIC that owns this module. The PRM marks it Reserved for the
 * backplane and chip2chip types, where a Reserved value reading back as a valid-looking address
 * would attribute a phantom cable to an ASIC that owns no such thing. Nothing else is excluded
 * here: whether a cable is plugged in and can be burned is phase 2's and phase 3's question.
 */
static bool isAsicDetectionSupported(u_int8_t moduleType)
{
    switch (moduleType)
    {
        case MMAM_MODULE_TYPE_BACKPLANE_1X:
        case MMAM_MODULE_TYPE_BACKPLANE_2X:
        case MMAM_MODULE_TYPE_BACKPLANE_4X:
        case MMAM_MODULE_TYPE_BACKPLANE_8X:
        case MMAM_MODULE_TYPE_CHIP2CHIP_1X:
        case MMAM_MODULE_TYPE_CHIP2CHIP_2X:
        case MMAM_MODULE_TYPE_CHIP2CHIP_4X:
        case MMAM_MODULE_TYPE_CHIP2CHIP_8X:
            return false;
        default:
            return true;
    }
}

static string moduleTypeName(u_int8_t moduleType)
{
    switch (moduleType)
    {
        case MMAM_MODULE_TYPE_BACKPLANE_4X:
            return "Backplane_with_4_lanes";
        case MMAM_MODULE_TYPE_QSFP:
            return "QSFP";
        case MMAM_MODULE_TYPE_SFP:
            return "SFP";
        case MMAM_MODULE_TYPE_NO_CAGE:
            return "No_Cage";
        case MMAM_MODULE_TYPE_BACKPLANE_1X:
            return "Backplane_with_single_lane";
        case MMAM_MODULE_TYPE_BACKPLANE_2X:
            return "Backplane_with_two_lanes";
        case MMAM_MODULE_TYPE_CHIP2CHIP_4X:
            return "Chip2Chip4x";
        case MMAM_MODULE_TYPE_CHIP2CHIP_2X:
            return "Chip2Chip2x";
        case MMAM_MODULE_TYPE_CHIP2CHIP_1X:
            return "Chip2Chip1x";
        case MMAM_MODULE_TYPE_QSFP_DD:
            return "QSFP_DD";
        case MMAM_MODULE_TYPE_OSFP:
            return "OSFP";
        case MMAM_MODULE_TYPE_SFP_DD:
            return "SFP_DD";
        case MMAM_MODULE_TYPE_DSFP:
            return "DSFP";
        case MMAM_MODULE_TYPE_CHIP2CHIP_8X:
            return "Chip2Chip8x";
        case MMAM_MODULE_TYPE_TWISTED_PAIR:
            return "Twisted_Pair";
        case MMAM_MODULE_TYPE_BACKPLANE_8X:
            return "Backplane_with_8_lanes";
        case MMAM_MODULE_TYPE_LOOPBACK:
            return "Loopback";
        case MMAM_MODULE_TYPE_OE_16X:
            return "OE_16x";
        case MMAM_MODULE_TYPE_OSFP_ELS:
            return "OSFP_ELS";
        case MMAM_MODULE_TYPE_QSFP_2X:
            return "QSFP_2x";
        case MMAM_MODULE_TYPE_CPO_32X:
            return "CPO_32x";
        case MMAM_MODULE_TYPE_ELS_16:
            return "ELS_16";
        case MMAM_MODULE_TYPE_CPO_64X:
            return "CPO_64x";
        case MMAM_MODULE_TYPE_QSFP_1X:
            return "QSFP_1x";
        case MMAM_MODULE_TYPE_NPO_16X:
            return "NPO_16x";
        default:
            return "unknown type " + int_to_string((int)moduleType);
    }
}

static reg_access_status_t readAsicGa(mfile* mf, u_int8_t& ga)
{
    struct reg_access_hca_mgir_ext mgir;

    memset(&mgir, 0, sizeof(mgir));
    reg_access_status_t status = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
    if (status == ME_OK)
    {
        // Reads 0 when ga_valid is clear, so such a system is only mappable if it holds one ASIC;
        // that one is taken as ASIC 0, and a second reporting 0 as well fails as a duplicate.
        ga = mgir.hw_info.ga;
    }
    return status;
}

static reg_access_status_t readCageCount(mfile* mf, u_int32_t& total)
{
    struct reg_access_switch_mgpir_ext mgpir;

    memset(&mgpir, 0, sizeof(mgpir));
    mgpir.hw_info.slot_index = 0; // INDEX field, selects the main board
    reg_access_status_t status = reg_access_mgpir_switch_ext(mf, REG_ACCESS_METHOD_GET, &mgpir);
    if (status == ME_OK)
    {
        total = ((u_int32_t)mgpir.hw_info.num_of_modules_per_system_msb << 8) |
                (u_int32_t)mgpir.hw_info.num_of_modules_per_system;
    }
    return status;
}

static reg_access_status_t readCableMapEntry(mfile* mf, u_int32_t globalIndex, struct reg_access_switch_MMAM_ext& entry)
{
    memset(&entry, 0, sizeof(entry));
    entry.module = (u_int8_t)(globalIndex & 0xff);
    entry.module_msb = (u_int8_t)(globalIndex >> 8);
    return reg_access_mmam(mf, REG_ACCESS_METHOD_GET, &entry);
}

CableFwManager::CableFwManager(const CmdLineParams& cmdParams) : _cmdParams(cmdParams), _errMsg(""), _log("") {}

CableFwManager::~CableFwManager() {}

int CableFwManager::run()
{
    int rc = discoverSystem();
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    rc = discoverCables();
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    if (_cmdParams.cable_dry_run || _cmdParams.cable_update)
    {
        rc = buildUpdatePlan();
        if (rc != MLX_FWM_SUCCESS)
        {
            return rc;
        }
    }

    if (_cmdParams.cable_update)
    {
        // Keep the burn result and report anyway: phase 5 is what tells the user which
        // cables failed, and it is most needed exactly when phase 4 did not go cleanly.
        rc = downloadAndActivate();
    }

    int reportRc = verifyAndReport();
    return (rc != MLX_FWM_SUCCESS) ? rc : reportRc;
}

int CableFwManager::discoverSystem()
{
    int devsNum = 0;
    dev_info* devs = mdevices_info(MDEVS_TAVOR_CR, &devsNum);

    if (devs == NULL || devsNum == 0)
    {
        // No advice to start MST goes with this: the scan finds devices by DBDF whether or not the
        // modules are loaded, so nothing reported here is a fault 'mst start' would address.
        _errMsg = "No devices found";
        return ERR_CODE_NO_DEVICES_FOUND;
    }

    int rc = collectSwitchAsics(devs, devsNum);
    mdevices_info_destroy(devs, devsNum);
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    return buildCableMap();
}

int CableFwManager::collectSwitchAsics(dev_info* devs, int devsNum)
{
    for (int i = 0; i < devsNum; i++)
    {
        mfile* mf = mopen(devs[i].dev_name);
        if (mf == NULL)
        {
            _log += "-W- Skipped " + string(devs[i].dev_name) + ": the device could not be opened\n";
            continue;
        }

        dm_dev_id_t devType = DeviceUnknown;
        u_int32_t hwDevId = 0;
        u_int32_t hwRev = 0;
        int devIdRc = dm_get_device_id_without_prints(mf, &devType, &hwDevId, &hwRev);
        if (devIdRc != 0)
        {
            if (devIdRc == MFE_UNSUPPORTED_DEVICE)
            {
                _log += "-W- Skipped " + string(devs[i].dev_name) + ": the device type is not recognised\n";
            }
            else
            {
                _log += "-W- Skipped " + string(devs[i].dev_name) + ": recognising the device type failed with error " +
                        int_to_string(devIdRc) + "\n";
            }
            mclose(mf);
            continue;
        }
        if (!dm_dev_is_switch(devType))
        {
            _log += "-I- Skipped " + string(devs[i].dev_name) + ": " + dm_dev_type2str(devType) + " is not a switch\n";
            mclose(mf);
            continue;
        }

        AsicInfo asic;
        u_int8_t ga = 0;
        asic.devName = devs[i].dev_name;
        reg_access_status_t status = readAsicGa(mf, ga);
        mclose(mf);
        if (status != ME_OK)
        {
            _errMsg = "Failed to read MGIR from " + asic.devName + ": " + reg_access_err2str(status);
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }

        // The Geographical Address is the only name a cable gives for its owner, so two ASICs
        // sharing one makes every cable ambiguous. Keying the map by it catches that here, on the
        // ASIC that collides, rather than as a property of the finished set - and it is what a
        // system leaving MGIR.hw_info.ga_valid clear looks like from here, since the Reserved
        // field then reads 0 on every ASIC.
        AsicsByGa::const_iterator clash = _asics.find(ga);
        if (clash != _asics.end())
        {
            _errMsg = "Switch ASICs " + clash->second.devName + " and " + asic.devName +
                      " report the same Geographical Address " + int_to_string(ga) +
                      ", so cable ownership cannot be resolved";
            return ERR_CODE_CABLE_NOT_SUPPORTED;
        }
        _asics[ga] = asic;
    }

    if (_asics.empty())
    {
        _errMsg = "No switch ASIC was found; cable firmware update runs on switch systems only";
        return ERR_CODE_CABLE_NOT_SUPPORTED;
    }

    _log += "-I- Found " + int_to_string((int)_asics.size()) + " switch ASIC(s)\n";
    return MLX_FWM_SUCCESS;
}

int CableFwManager::buildCableMap()
{
    // MMAM's index space is the global one, so the map belongs to the system and is read once.
    AsicsByGa::const_iterator source = _asics.find(0);

    if (source == _asics.end())
    {
        _errMsg = "No switch ASIC reports Geographical Address 0, so MGIR is not reporting "
                  "Geographical Addresses correctly and cable ownership cannot be resolved";
        return ERR_CODE_CABLE_NOT_SUPPORTED;
    }

    mfile* mf = mopen(source->second.devName.c_str());
    if (mf == NULL)
    {
        _errMsg = "Failed to open " + source->second.devName + " to read the cable map";
        return ERR_CODE_CABLE_UPDATE_FAILED;
    }

    u_int32_t total = 0;
    reg_access_status_t status = readCageCount(mf, total);
    if (status != ME_OK)
    {
        mclose(mf);
        _errMsg = "Failed to read MGPIR from " + source->second.devName + ": " + reg_access_err2str(status);
        return ERR_CODE_CABLE_UPDATE_FAILED;
    }

    int rc = walkCableMap(mf, total);
    mclose(mf);
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    _log += "-I- Found " + int_to_string((int)_cables.size()) + " port(s), scanning for cables\n";
    return MLX_FWM_SUCCESS;
}

int CableFwManager::walkCableMap(mfile* mf, u_int32_t total)
{
    // Each global index is visited once, so no cable can be entered twice and nothing has to be
    // de-duplicated afterwards.
    for (u_int32_t globalIndex = 0; globalIndex < total; globalIndex++)
    {
        struct reg_access_switch_MMAM_ext entry;
        CableInfo cable;

        cable.globalIndex = globalIndex;
        cable.globalPort = globalIndex + 1;
        string globalPort = int_to_string((int)cable.globalPort);

        reg_access_status_t status = readCableMapEntry(mf, globalIndex, entry);
        if (status != ME_OK)
        {
            // MGPIR said how many ports the system has, so every index below that count is one the
            // firmware is expected to answer for. A refusal is a fault rather than an empty cage,
            // and carrying on would silently hand back a map missing exactly the port that failed.
            _errMsg = "Failed to read MMAM for port " + globalPort + " of " + int_to_string((int)total) + ": " +
                      reg_access_err2str(status);
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }

        cable.localIndex = ((u_int32_t)entry.local_module_msb << 8) | (u_int32_t)entry.local_module;
        cable.moduleType = entry.module_type;

        if (!isAsicDetectionSupported(entry.module_type))
        {
            // Recorded rather than dropped: the report accounts for every module the system
            // reported, and the reason a module was left alone is part of that account.
            cable.action = CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED;
            cable.asicGa = 0; // default, the action is what reports this port as skipped
            _log += "-W- Port " + globalPort + " is of module type " + moduleTypeName(entry.module_type) +
                    ", which leaves MMAM.ga Reserved, so its owning ASIC cannot be identified\n";
            _cables.push_back(cable);
            continue;
        }

        AsicsByGa::const_iterator owner = _asics.find(entry.ga);
        if (owner == _asics.end())
        {
            // The module names an owner that is not in the map, so it cannot be addressed and
            // neither can anything else be concluded about it. Reporting the system as partly
            // mapped would hide exactly the cable the user came to update.
            _errMsg = "Port " + globalPort + " reports Geographical Address " + int_to_string((int)entry.ga) +
                      ", but no switch ASIC with that address was found in the system";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }

        cable.asicGa = entry.ga;
        cable.asicDevName = owner->second.devName;
        _cables.push_back(cable);
    }
    return MLX_FWM_SUCCESS;
}

int CableFwManager::discoverCables()
{
    _errMsg = "Phase 2 (cable discovery) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::buildUpdatePlan()
{
    _errMsg = "Phase 3 (analysis and planning) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::downloadAndActivate()
{
    _errMsg = "Phase 4 (download and activate) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::verifyAndReport()
{
    _errMsg = "Phase 5 (verification and report) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}
