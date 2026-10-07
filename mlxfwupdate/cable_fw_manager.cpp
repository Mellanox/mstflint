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
#include "tools_layouts/cables_layouts.h"
#include "fw_comps_mgr/fw_comps_mgr.h"

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

/* The cable EEPROM lives behind this I2C address on every cage. */
#define CABLE_EEPROM_I2C_ADDRESS 0x50

/* Page 0 upper, where both memory maps keep the identity fields. */
#define CABLE_EEPROM_PAGE0_UPPER_OFFSET 128
#define CABLE_EEPROM_PAGE0_UPPER_SIZE 128

#define CABLE_EEPROM_ID_LEN 16
#define CABLE_EEPROM_REV_LEN 2

/* The one OUI that makes a cable NVIDIA's. */
#define CABLE_NVIDIA_OUI 0x0002C9

/* PMAOS.oper_status: the cage is empty only on this one value. Every other state - including
 * initializing and plugged_with_error - is a cable that is there and may still be updated.
 */
#define CABLE_OPER_STATUS_UNPLUGGED 2

/* Where the identity fields sit, as flat byte addresses in the cable's memory map. CMIS and
 * SFF-8636 disagree on all of them, and the identifier at page 0 byte 0 is what says which map
 * applies (tools_layouts/adb/cable/cable_cmis.adb and cable_qsfp.adb).
 */
struct CableEepromLayout
{
    u_int16_t vendorName;   // 16 ASCII
    u_int16_t vendorOui;    // 3 bytes, most significant first
    u_int16_t partNumber;   // 16 ASCII
    u_int16_t vendorRev;    // 2 ASCII
    u_int16_t serialNumber; // 16 ASCII
};

static const CableEepromLayout CMIS_LAYOUT = {129, 145, 148, 164, 166};
static const CableEepromLayout SFF8636_LAYOUT = {148, 165, 168, 184, 196};

/* CMIS identifiers. Anything else is read as SFF-8636, which is the older map and the safer
 * assumption for an identifier this code has not seen.
 */
static bool isCmisIdentifier(u_int8_t identifier)
{
    return identifier == 0x18 || identifier == 0x19 || identifier == 0x1e;
}

/* CMIS keeps the hardware revision on page 1; SFF-8636 has no such field at all, so a cable on
 * the older map reports major 0 and can never match package metadata that names one.
 */
#define CABLE_EEPROM_CMIS_HW_REV_PAGE 1
#define CABLE_EEPROM_CMIS_HW_REV_MAJOR_OFFSET 130

static const char* cableStateName(u_int8_t operStatus)
{
    switch (operStatus)
    {
        case 0:
            return "initializing";
        case 1:
            return "plugged_enable";
        case CABLE_OPER_STATUS_UNPLUGGED:
            return "unplugged";
        case 3:
            return "module_plugged_with_error";
        case 4:
            return "plugged_disabled";
        default:
            return "unknown";
    }
}

/* EEPROM text is padded with spaces and is not terminated, so it needs both a bound and a trim. */
static string trimmedEepromText(const u_int8_t* bytes, u_int16_t length)
{
    string text((const char*)bytes, length);
    size_t end = text.find_last_not_of(" \t\r\n");

    if (end == string::npos)
    {
        return "";
    }
    text = text.substr(0, end + 1);
    // A field that never held text at all reads as zeros rather than spaces.
    size_t nul = text.find('\0');
    return (nul == string::npos) ? text : text.substr(0, nul);
}

static reg_access_status_t
  readCableEeprom(mfile* mf, u_int32_t localIndex, u_int8_t page, u_int16_t offset, u_int16_t size, u_int8_t* buffer)
{
    struct reg_access_hca_mcia_ext mcia;

    memset(&mcia, 0, sizeof(mcia));
    mcia.module = (u_int8_t)(localIndex & 0xff);
    mcia.module_bits_11_8 = (u_int8_t)((localIndex >> 8) & 0xf);
    mcia.module_bits_14_12 = (u_int8_t)((localIndex >> 12) & 0x7);
    mcia.module_bit_15 = (u_int8_t)((localIndex >> 15) & 0x1);
    mcia.page_number = page;
    mcia.device_address = offset;
    mcia.i2c_device_address = CABLE_EEPROM_I2C_ADDRESS;
    mcia.size = size;
    reg_access_status_t status = reg_access_mcia(mf, REG_ACCESS_METHOD_GET, &mcia);
    if (status != ME_OK)
    {
        return status;
    }
    // MCIA answers ME_OK and reports the real outcome in its own status field, so a read that
    // found no cable, hit an I2C error or was refused looks successful until this is checked.
    if (mcia.status != 0)
    {
        return ME_REG_ACCESS_BAD_PARAM;
    }
    // Each dword carries four EEPROM bytes, most significant first. Extracting by shift rather
    // than by aliasing the buffer keeps it independent of the host's byte order.
    for (u_int16_t i = 0; i < size; i++)
    {
        buffer[i] = (u_int8_t)((mcia.dword[i / 4] >> (8 * (3 - (i % 4)))) & 0xff);
    }
    return ME_OK;
}

static reg_access_status_t readCableOperStatus(mfile* mf, u_int32_t localIndex, u_int8_t& operStatus)
{
    struct reg_access_switch_pmaos_reg_ext pmaos;

    memset(&pmaos, 0, sizeof(pmaos));
    pmaos.module = (u_int8_t)(localIndex & 0xff);
    pmaos.module_msb = (u_int8_t)(localIndex >> 8);
    pmaos.slot_index = 0;
    reg_access_status_t status = reg_access_pmaos(mf, REG_ACCESS_METHOD_GET, &pmaos);
    if (status == ME_OK)
    {
        operStatus = pmaos.oper_status;
    }
    return status;
}

/* Whether the cable is a counterfeit.
 *
 * The check belongs to MFCDR (register 0x9178), which returns a status of 0 for N/A, 1 for a fake
 * cable, 2 for an NVIDIA cable and 3 for a non-NVIDIA one, queried per cable with query_type = 1
 * and module = the local cage index:
 *
 *     struct reg_access_switch_mfcdr_reg_ext mfcdr;
 *     memset(&mfcdr, 0, sizeof(mfcdr));
 *     mfcdr.query_type = 1;
 *     mfcdr.module = (u_int8_t)localIndex;
 *     if (reg_access_mfcdr(mf, REG_ACCESS_METHOD_GET, &mfcdr) == ME_OK)
 *     {
 *         return mfcdr.status == 1;
 *     }
 *
 * It needs two gates first: isRegisterValidAccordingToMcamReg(mf, REG_ID_MFCDR, ...) for the
 * register, and isCapabilitySupportedAccordingToMcamReg(mf, MCAM_CAP_MFCDR_MODULE_AND_QUERY_TYPE,
 * ...) for the module-based query - on firmware without the second, query_type reads as reserved
 * and the answer comes back for local port 0 on every cable.
 *
 * MFCDR has no generated C yet: its ADB node carries no pack/unpack and there is no accessor, so
 * the call cannot be written. Until it is generated, no cable is reported as fake and isNvidia
 * rests on the vendor OUI, which is the other method MFCDR's own description names.
 */
static bool isFakeCable(mfile* mf, u_int32_t localIndex)
{
    (void)mf;
    (void)localIndex;
    return false;
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
    u_int32_t present = 0;
    u_int32_t burnable = 0;

    for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = mopen(asic->second.devName.c_str());
        if (mf == NULL)
        {
            _errMsg = "Failed to open " + asic->second.devName + " to query the cables it owns";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }
        for (size_t j = 0; j < _cables.size(); j++)
        {
            // This port is never updated, so there is nothing to query it for.
            if (_cables[j].action == CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED)
            {
                continue;
            }
            // MCIA, PMAOS and MCQI answer for a cage only on the ASIC that owns it, and on a
            // system that numbers cages system-wide the other ASICs answer too, with the wrong
            // cable. Ownership stays what MMAM said in phase 1.
            if (_cables[j].asicGa == asic->first)
            {
                queryCable(mf, _cables[j]);
            }
        }
        mclose(mf);
    }

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].isPlugged)
        {
            present++;
        }
        if (_cables[i].isBurnable)
        {
            burnable++;
        }
    }
    _log +=
      "Found " + int_to_string((int)present) + " cable(s), " + int_to_string((int)burnable) + " of them updatable\n";
    return MLX_FWM_SUCCESS;
}

void CableFwManager::queryCable(mfile* mf, CableInfo& cable)
{
    u_int8_t operStatus = 0;

    if (readCableOperStatus(mf, cable.localIndex, operStatus) != ME_OK)
    {
        cable.state = "unreadable";
        return;
    }
    cable.state = cableStateName(operStatus);
    /* Presence belongs on PDDR.cable_type, the same field mlxlink reads for its own plugged state
     * (UNPLUGGED is 4). PDDR has no generated struct or reg_access accessor yet, so until it has
     * one every cage is taken as plugged and the reads below run on empty cages too:
     *
     *   cable.isPlugged = (cableType != PDDR_CABLE_TYPE_UNPLUGGED);
     *   if (!cable.isPlugged)
     *   {
     *       _log += "Port " + int_to_string((int)cable.globalPort) + ": no cable in the cage, skipping query\n";
     *       return;
     *   }
     */
    cable.isPlugged = true;

    if (!readCableIdentity(mf, cable))
    {
        return;
    }
    cable.isNvidia = (cable.vendorOui == CABLE_NVIDIA_OUI) && !isFakeCable(mf, cable.localIndex);
    if (!readCableFwProperties(mf, cable))
    {
        return;
    }
    // A cable that implements neither firmware-update procedure reports protocol 0.
    cable.isBurnable = (cable.managementInterfaceProtocol != 0);
}

bool CableFwManager::readCableIdentity(mfile* mf, CableInfo& cable)
{
    u_int8_t identifier = 0;
    u_int8_t page0[CABLE_EEPROM_PAGE0_UPPER_SIZE];

    if (readCableEeprom(mf, cable.localIndex, 0, 0, sizeof(identifier), &identifier) != ME_OK)
    {
        return false;
    }
    bool isCmis = isCmisIdentifier(identifier);
    const CableEepromLayout& layout = isCmis ? CMIS_LAYOUT : SFF8636_LAYOUT;

    if (readCableEeprom(mf, cable.localIndex, 0, CABLE_EEPROM_PAGE0_UPPER_OFFSET, sizeof(page0), page0) != ME_OK)
    {
        return false;
    }
    // The layout offsets are flat addresses; the buffer starts at the upper page boundary.
    u_int16_t name = layout.vendorName - CABLE_EEPROM_PAGE0_UPPER_OFFSET;
    u_int16_t part = layout.partNumber - CABLE_EEPROM_PAGE0_UPPER_OFFSET;
    u_int16_t serial = layout.serialNumber - CABLE_EEPROM_PAGE0_UPPER_OFFSET;
    u_int16_t rev = layout.vendorRev - CABLE_EEPROM_PAGE0_UPPER_OFFSET;
    u_int16_t oui = layout.vendorOui - CABLE_EEPROM_PAGE0_UPPER_OFFSET;

    cable.vendorName = trimmedEepromText(&page0[name], CABLE_EEPROM_ID_LEN);
    cable.partNumber = trimmedEepromText(&page0[part], CABLE_EEPROM_ID_LEN);
    cable.serialNumber = trimmedEepromText(&page0[serial], CABLE_EEPROM_ID_LEN);
    cable.vendorRev = trimmedEepromText(&page0[rev], CABLE_EEPROM_REV_LEN);
    cable.vendorOui = ((u_int32_t)page0[oui] << 16) | ((u_int32_t)page0[oui + 1] << 8) | (u_int32_t)page0[oui + 2];

    if (isCmis)
    {
        u_int8_t hwRevMajor = 0;
        if (readCableEeprom(mf, cable.localIndex, CABLE_EEPROM_CMIS_HW_REV_PAGE, CABLE_EEPROM_CMIS_HW_REV_MAJOR_OFFSET,
                            sizeof(hwRevMajor), &hwRevMajor) == ME_OK)
        {
            cable.hwRevMajor = hwRevMajor;
        }
    }
    return true;
}

bool CableFwManager::readCableFwProperties(mfile* mf, CableInfo& cable)
{
    // One manager per cable. RefreshComponentsStatus() caches after its first call, and the LinkX
    // query leaves the queried cable's index behind on the object, so a manager reused across
    // cables discovers components once and then addresses the wrong cage.
    FwCompsMgr fwComps(mf, FwCompsMgr::DEVICE_HCA_SWITCH, 0);
    component_linkx_st properties;

    fwComps.SetIndexAndSize(cableMccIndex(cable.localIndex), 1);
    // The component walk has to run while the manager still addresses the host, which is what the
    // index it was constructed with means.
    if (!fwComps.RefreshComponentsStatus())
    {
        return false;
    }
    memset(&properties, 0, sizeof(properties));
    if (!fwComps.GetComponentLinkxProperties(FwComponent::COMPID_LINKX, &properties))
    {
        return false;
    }

    cable.fwImageA.major = properties.image_a_major;
    cable.fwImageA.minor = properties.image_a_minor;
    cable.fwImageA.subminor = properties.image_a_subminor;
    cable.fwImageB.major = properties.image_b_major;
    cable.fwImageB.minor = properties.image_b_minor;
    cable.fwImageB.subminor = properties.image_b_subminor;
    // Bit 0 of the status bitmap says image A is running, bit 4 says image B is.
    cable.runningSlot = (properties.fw_image_status_bitmap & 0x10) ? CABLE_IMAGE_SLOT_B : CABLE_IMAGE_SLOT_A;
    cable.managementInterfaceProtocol = properties.management_interface_protocol;
    cable.activationType = properties.activation_type;
    return true;
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
