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
#include "mft_utils/mft_utils.h"
// The FreeBSD build's mtcr.h defines u16 and u32 as object-like macros, which rewrite any later
// identifier of that name - including the parameter names in the header below, whose arguments
// then shadow the very types they are cast to. They are set aside across the include and put back
// exactly as they were, which on every other platform means leaving them undefined.
#pragma push_macro("u16")
#pragma push_macro("u32")
#undef u16
#undef u32
#include <fkYAML/node.hpp>
#pragma pop_macro("u32")
#pragma pop_macro("u16")
#ifndef NO_OPEN_SSL
#include <openssl/sha.h>
#endif
#include <zlib.h>
#include <chrono>
#include <iomanip>
#include <fstream>

#include "common/bit_slice.h"
#include "common/tools_time.h"
#include "reg_access/mcam_capabilities.h"
#include "reg_access/reg_ids.h"
#include "common/package_error_codes.h"
#include <time.h>

/* The head of a LinkX FW package (MFT's mlxfwops/lib/fw_linkx_package.h): its magic and the
 * package version behind the build date. Only what the cable flow reads is named here. */
#define MAGIC_NUMBER_LENGTH (8)
#define MAGIC_PATTERN                                  \
    {                                                  \
        0x4e, 0x76, 0x58, 0x63, 0x76, 0x72, 0x46, 0x57 \
    } /* "NvXcvrFW" */
typedef struct /* 32 bytes long, big endian */
{
    u_int8_t magic_num[MAGIC_NUMBER_LENGTH];
    u_int8_t build_date[6];
    u_int8_t header_version;
    u_int8_t fw_product_id; /* Package Major */
    u_int8_t package_minor; /* Package Minor */
    u_int8_t package_subminor_msb;
    u_int8_t package_subminor_lsb;
    u_int8_t reserved[9];
    u_int32_t package_size;
} fw_pkg_file_header_t;

/* The extended header a cable firmware image can carry: its magic and the layout the device
 * matches the image against. Only the pieces the cable flow uses are defined here. */
#define CABLE_EXT_HEADER_MAGIC_STRING "MT2C"
#define CABLE_EXT_HEADER_MAGIC_LENGTH 4
/* The vendor byte sits right behind the magic and the header version. */
#define CABLE_EXT_HEADER_VENDOR_BYTE_OFFSET 5
static bool isCableExtendedHeaderMagic(const u_int8_t* data, u_int32_t len)
{
    return len >= CABLE_EXT_HEADER_MAGIC_LENGTH &&
           !strncmp((const char*)data, CABLE_EXT_HEADER_MAGIC_STRING, CABLE_EXT_HEADER_MAGIC_LENGTH);
}
static bool hasCableExtendedHeader(const u_int8_t* data, u_int32_t len)
{
    return isCableExtendedHeaderMagic(data, len) && len > CABLE_EXT_HEADER_VENDOR_BYTE_OFFSET;
}

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

static reg_access_status_t readAsicGa(mfile* mf, u_int8_t& ga, string& fwVersion)
{
    struct reg_access_hca_mgir_ext mgir;

    memset(&mgir, 0, sizeof(mgir));
    reg_access_status_t status = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
    FWMANAGER_LOG_DEBUG("MGIR: status %d, ga %d, ga_valid %d", (int)status, (int)mgir.hw_info.ga,
                        (int)mgir.hw_info.ga_valid);
    if (status == ME_OK)
    {
        // Reads 0 when ga_valid is clear, so such a system is only mappable if it holds one ASIC;
        // that one is taken as ASIC 0, and a second reporting 0 as well fails as a duplicate.
        ga = mgir.hw_info.ga;
        // The legacy major/minor/sub_minor fields are deprecated and read 0.
        char text[32];
        snprintf(text, sizeof(text), "%u.%u.%u", (unsigned)mgir.fw_info.extended_major,
                 (unsigned)mgir.fw_info.extended_minor, (unsigned)mgir.fw_info.extended_sub_minor);
        fwVersion = text;
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
    FWMANAGER_LOG_DEBUG("MGPIR: status %d, cages %u", (int)status, total);
    return status;
}

static reg_access_status_t readCableMapEntry(mfile* mf, u_int32_t globalIndex, struct reg_access_switch_MMAM_ext& entry)
{
    memset(&entry, 0, sizeof(entry));
    entry.module = (u_int8_t)(globalIndex & 0xff);
    entry.module_msb = (u_int8_t)(globalIndex >> 8);
    reg_access_status_t status = reg_access_mmam(mf, REG_ACCESS_METHOD_GET, &entry);
    FWMANAGER_LOG_DEBUG("MMAM: global %u, status %d, ga %d, local_module %d, module_type %d", globalIndex, (int)status,
                        (int)entry.ga, (int)entry.local_module, (int)entry.module_type);
    return status;
}

CableFwManager::CableFwManager(const CmdLineParams& cmdParams, ProgressPrinter printer, InterruptQuery interrupted) :
    _cmdParams(cmdParams),
    _errMsg(""),
    _printer(printer),
    _interrupted(interrupted),
    _progressLineOpen(false),
    _progressSpinner(0),
    _discoverySeconds(-1),
    _updateSeconds(-1),
    _verificationSeconds(-1),
    _planned(false)
{
}

CableFwManager::~CableFwManager()
{
    for (map<string, mfile*>::iterator it = _openDevices.begin(); it != _openDevices.end(); ++it)
    {
        mclose(it->second);
    }
}

mfile* CableFwManager::deviceHandle(const string& devName)
{
    map<string, mfile*>::iterator it = _openDevices.find(devName);

    if (it != _openDevices.end())
    {
        return it->second;
    }
    mfile* mf = mopen(devName.c_str());
    if (mf != NULL)
    {
        _openDevices[devName] = mf;
    }
    return mf;
}

static double secondsSince(std::chrono::steady_clock::time_point start)
{
    return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
}

int CableFwManager::run()
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
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
    _discoverySeconds = secondsSince(start);

    if (_cmdParams.cable_dry_run || _cmdParams.cable_update)
    {
        // Keep the plan's result and report anyway. A package the tool could not read is exactly
        // when its packages table is wanted: it names every metadata file it rejected and why.
        rc = buildUpdatePlan();
        if (rc != MLX_FWM_SUCCESS && !_planned)
        {
            _notPlannedReason = _errMsg;
        }
    }
    // Nothing has been written yet, so there is nothing to report on.
    if (isInterrupted())
    {
        _errMsg = "Interrupted by the user";
        return ERR_CODE_INTERRUPTED;
    }

    if (rc == MLX_FWM_SUCCESS && _cmdParams.cable_update)
    {
        // Keep the burn result and report anyway: phase 5 is what tells the user which
        // cables failed, and it is most needed exactly when phase 4 did not go cleanly.
        start = std::chrono::steady_clock::now();
        rc = downloadAndActivate();
        // The burn was cancelled and its handle released; the user asked to stop, not for a report.
        if (rc == ERR_CODE_INTERRUPTED)
        {
            // Ends the progress line the burn stopped on, so the caller's error starts a line of its own.
            emitProgress("");
            return rc;
        }
        if (!_results.empty())
        {
            _updateSeconds = secondsSince(start);
        }
    }
    // A plan that was never built is named in the plan section, which already explains the rest.
    if (rc != MLX_FWM_SUCCESS && _cmdParams.cable_update && _results.empty() && _notPlannedReason.empty())
    {
        _notStartedReason = _errMsg;
    }

    int reportRc = verifyAndReport();
    return (rc != MLX_FWM_SUCCESS) ? rc : reportRc;
}

/* What the report prints for anything the cable or the package did not supply. */
#define CABLE_REPORT_NOT_AVAILABLE "N/A"

/* The cable EEPROM lives behind this I2C address on every cage. */
#define CABLE_EEPROM_I2C_ADDRESS 0x50

/* Page 0 upper, where both memory maps keep the identity fields. */
#define CABLE_EEPROM_PAGE0_UPPER_OFFSET 128
#define CABLE_EEPROM_PAGE0_UPPER_SIZE 128

#define CABLE_EEPROM_ID_LEN 16
#define CABLE_EEPROM_REV_LEN 2

/* The vendor OUIs NVIDIA ships cables under. Measured on a switch: a genuine NVIDIA OSFP cable
 * carries 0x48B02D, not the older Mellanox block, so one value is not enough. The list is only
 * the fallback - MFCDR answers the question directly where the firmware supports it.
 */
#define CABLE_NVIDIA_OUI_MELLANOX 0x0002C9
#define CABLE_NVIDIA_OUI 0x48B02D

/* MCQI fw_image_status_bitmap: which image the cable is running, if any. */
#define CABLE_FW_STATUS_BIT_A_RUNNING 0
#define CABLE_FW_STATUS_BIT_B_RUNNING 4

/* MFCDR.status. */
#define CABLE_VENDOR_STATUS_UNKNOWN 0
#define CABLE_VENDOR_STATUS_FAKE 1
#define CABLE_VENDOR_STATUS_NVIDIA 2
#define CABLE_VENDOR_STATUS_NON_NVIDIA 3
// Not an MFCDR value: the firmware carries MFCDR but gave no answer for this cage.
#define CABLE_VENDOR_STATUS_READ_FAILED 0xff

/* PMAOS.oper_status: the cage is empty only on this one value. Every other state - including
 * initializing and plugged_with_error - is a cable that is there and may still be updated. This
 * is the same test mlxlink makes in checkPmaosDown().
 */
#define CABLE_OPER_STATUS_INITIALIZING 0
#define CABLE_OPER_STATUS_PLUGGED_ENABLED 1
#define CABLE_OPER_STATUS_UNPLUGGED 2
#define CABLE_OPER_STATUS_PLUGGED_WITH_ERROR 3

/* What the State column says for a populated cage whose cable could not be read, in place of a
 * link state that would read as N/A and look like an empty cage. Both fit the column.
 */
#define CABLE_STATE_UNREADABLE "Unreadable"
#define CABLE_STATE_PLUGGED_WITH_ERROR "Plugged w/ error"

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
    u_int16_t dateCode;     // 8 ASCII, YYMMDD followed by a 2-character lot code
};

static const CableEepromLayout CMIS_LAYOUT = {129, 145, 148, 164, 166, 182};
static const CableEepromLayout SFF8636_LAYOUT = {148, 165, 168, 184, 196, 212};

/* Page 0 lower, the part of the map every cable implements. */
#define CABLE_EEPROM_FLAT_MEM_OFFSET 2
#define CABLE_EEPROM_FLAT_MEM_BIT 7
#define CABLE_EEPROM_MODULE_STATE_BIT 1
#define CABLE_EEPROM_MODULE_STATE_WIDTH 3
#define CABLE_EEPROM_MODULE_STATE_OFFSET 3
#define CABLE_EEPROM_DATE_LEN 6

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
#define CABLE_EEPROM_CMIS_HW_REV_OFFSET 130

/* The CMIS module state, page 0 byte 3 bits 3:1. This is the state mlxlink reports as
 * "Module State"; SFF-8636 has no equivalent. PMAOS.oper_status is the cage's state, not the
 * cable's, and is used here only to decide whether a cable is plugged in at all.
 */
/* CMIS page 01h bytes 130-131 are the hardware revision major and minor, and CMIS defines them as
 * numbers. Shown in decimal even where a vendor wrote ASCII into them ("A3" reads 65.51): the
 * vendor revision column already carries the text, and metadata matches the major as a number.
 */
static string cableHwRevisionText(u_int8_t major, u_int8_t minor)
{
    return int_to_string((int)major) + "." + int_to_string((int)minor);
}

static const char* cableModuleStateName(u_int8_t moduleState)
{
    switch (moduleState)
    {
        case 1:
            return "LowPwr state";
        case 2:
            return "PwrUp state";
        case 3:
            return "Ready state";
        case 4:
            return "PwrDn state";
        case 5:
            return "Fault state";
        default:
            return CABLE_REPORT_NOT_AVAILABLE;
    }
}

/* SFF-8024 identifier, page 0 byte 0. This is the raw EEPROM byte, not the firmware enum mlxlink
 * prints, so the two are not interchangeable.
 */
static const char* cableIdentifierName(u_int8_t identifier)
{
    switch (identifier)
    {
        case 0x0c:
            return "QSFP";
        case 0x0d:
            return "QSFP+";
        case 0x11:
            return "QSFP28";
        case 0x18:
            return "QSFP-DD";
        case 0x19:
            return "OSFP";
        case 0x1b:
            return "DSFP";
        case 0x1e:
            return "QSFP+ CMIS";
        case 0x03:
            return "SFP";
        default:
            return CABLE_REPORT_NOT_AVAILABLE;
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
    FWMANAGER_LOG_DEBUG("MCIA: module %u, page %d, offset %d, size %d -> status %d, mcia.status %d", localIndex,
                        (int)page, (int)offset, (int)size, (int)status, (int)mcia.status);
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
    FWMANAGER_LOG_DEBUG("PMAOS: module %u, status %d, oper_status %d", localIndex, (int)status, (int)operStatus);
    return status;
}

/* mstflint's isCapabilitySupportedAccordingToMcamReg takes the MCAM dword swap from its caller;
 * it is worked out here the way MFT's version works it out for itself. */
static bool isMcamDwordSwapNeeded(mfile* mf)
{
    dm_dev_id_t devid = DeviceUnknown;
    u_int32_t hwDevId = 0, revId = 0;

    return dm_get_device_id(mf, &devid, &hwDevId, &revId) == ME_OK && dm_dev_is_mcam_dword_swap_needed(devid);
}

/* What MFCDR says a cable is: 0 N/A, 1 fake, 2 NVIDIA, 3 non-NVIDIA.
 *
 * Both MCAM gates are required. Without the capability, query_type reads as reserved and the
 * answer comes back for local port 0 on every cable.
 *
 * Asked by local port, which carries 10 bits; the module field carries 8, and a cage above 255
 * would get another cage's verdict.
 */
static u_int8_t readCableVendorStatus(mfile* mf, bool mapped, u_int32_t localPort)
{
    struct reg_access_switch_mfcdr_reg_ext mfcdr;
    bool supported = false;

    if (isRegisterValidAccordingToMcamReg(mf, REG_ID_MFCDR, &supported) != ME_OK || !supported)
    {
        FWMANAGER_LOG_DEBUG("MFCDR: not supported according to MCAM, so only the vendor OUI is checked");
        return CABLE_VENDOR_STATUS_UNKNOWN;
    }
    if (isCapabilitySupportedAccordingToMcamReg(mf, MCAM_CAP_MFCDR_MODULE_AND_QUERY_TYPE, isMcamDwordSwapNeeded(mf), &supported) != ME_OK ||
        !supported)
    {
        FWMANAGER_LOG_DEBUG("MFCDR: query type not supported according to MCAM, so only the vendor OUI is checked");
        return CABLE_VENDOR_STATUS_UNKNOWN;
    }
    if (!mapped)
    {
        FWMANAGER_LOG_DEBUG("MFCDR: no local port maps to this cage to ask with");
        return CABLE_VENDOR_STATUS_READ_FAILED;
    }
    memset(&mfcdr, 0, sizeof(mfcdr));
    mfcdr.query_type = 0; // local port based query; module is ignored
    mfcdr.local_port = (u_int8_t)(localPort & 0xff);
    mfcdr.lp_msb = (u_int8_t)((localPort >> 8) & 0x3);
    reg_access_status_t status = reg_access_mfcdr(mf, REG_ACCESS_METHOD_GET, &mfcdr);
    FWMANAGER_LOG_DEBUG("MFCDR: local_port %u, status %d, vendor status %d", localPort, (int)status, (int)mfcdr.status);
    if (status != ME_OK)
    {
        return CABLE_VENDOR_STATUS_READ_FAILED;
    }
    return mfcdr.status;
}

/* The metadata keys this tool reads, named after the CMIS fields they match, as the OIF CMIS
 * Firmware Update Package IA (OIF2026.122) spells them. The NVIDIA LinkX release spells three of
 * them differently, and both spellings are read.
 *
 * VendorName and FwLoadName are required. Every other match key is optional, may use ? and *
 * wildcards, and narrows the match only when the entry states it. A key the tool does not know is
 * ignored, as the IA requires.
 */
#define CABLE_YAML_KEY_VENDOR_NAME "VendorName"
#define CABLE_YAML_KEY_VENDOR_PN "VendorPN"
#define CABLE_YAML_KEY_VENDOR_OUI "VendorOUI"
#define CABLE_YAML_KEY_VENDOR_REV "VendorRev"
#define CABLE_YAML_KEY_VENDOR_SN "VendorSN"
#define CABLE_YAML_KEY_HW_MAJOR "ModuleHardwareMajorRevision"
#define CABLE_YAML_KEY_HW_MAJOR_NVIDIA "VendorHWMajor"
#define CABLE_YAML_KEY_HW_MINOR "ModuleHardwareMinorRevision"
#define CABLE_YAML_KEY_ACTIVE_FW "ModuleActiveFirmwareVersion"
#define CABLE_YAML_KEY_LOAD_NAME "FwLoadName"
#define CABLE_YAML_KEY_LOAD_VERSION "FwLoadVersion"
#define CABLE_YAML_KEY_LOAD_VERSION_NVIDIA "FWLoadVersion"
#define CABLE_YAML_KEY_SHA256 "FwUpdateLoadChecksumSHA256"
#define CABLE_YAML_KEY_SHA256_NVIDIA "FwUpdateImageChecksumSHA256"
#define CABLE_YAML_KEY_SHA512 "FwUpdateLoadChecksumSHA512"
#define CABLE_YAML_KEY_SHA512_NVIDIA "FwUpdateImageChecksumSHA512"

#define CABLE_METADATA_SUFFIX ".yaml"

static string lowered(const string& text)
{
    string result = text;

    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = (char)tolower((unsigned char)result[i]);
    }
    return result;
}

static bool equalsIgnoringCase(const string& left, const string& right)
{
    return lowered(left) == lowered(right);
}

#ifndef NO_OPEN_SSL
static string sha256Hex(const vector<u_int8_t>& data)
{
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char hex[SHA256_DIGEST_LENGTH * 2 + 1];
    SHA256_CTX context;

    memset(hex, 0, sizeof(hex));
    SHA256_Init(&context);
    if (!data.empty())
    {
        SHA256_Update(&context, &data[0], data.size());
    }
    SHA256_Final(digest, &context);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        snprintf(hex + i * 2, 3, "%02x", digest[i]);
    }
    return string(hex);
}

static string sha512Hex(const vector<u_int8_t>& data)
{
    unsigned char digest[SHA512_DIGEST_LENGTH] = {0};
    char hex[SHA512_DIGEST_LENGTH * 2 + 1];
    SHA512_CTX context;

    memset(hex, 0, sizeof(hex));
    SHA512_Init(&context);
    if (!data.empty())
    {
        SHA512_Update(&context, &data[0], data.size());
    }
    SHA512_Final(digest, &context);
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        snprintf(hex + i * 2, 3, "%02x", digest[i]);
    }
    return string(hex);
}
#endif

/* The IA's wildcards: ? is any one character, * any run of characters including none. */
static bool globMatches(const string& pattern, const string& text)
{
    size_t p = 0;
    size_t t = 0;
    size_t star = string::npos;
    size_t resume = 0;

    while (t < text.size())
    {
        if (p < pattern.size() && (pattern[p] == '?' || pattern[p] == text[t]))
        {
            p++;
            t++;
        }
        else if (p < pattern.size() && pattern[p] == '*')
        {
            star = p++;
            resume = t;
        }
        else if (star != string::npos)
        {
            p = star + 1;
            t = ++resume;
        }
        else
        {
            return false;
        }
    }
    while (p < pattern.size() && pattern[p] == '*')
    {
        p++;
    }
    return p == pattern.size();
}

static bool hasWildcard(const string& pattern)
{
    return pattern.find_first_of("*?") != string::npos;
}

/* Versions are written major.minor.subminor, the same three parts MCQI reports. */
static bool parseCableFwVersion(const string& text, CableFwVersion& version)
{
    unsigned int major = 0;
    unsigned int minor = 0;
    unsigned int subminor = 0;

    int consumed = 0;

    // %n is not counted in the return value, so it is only read once all three conversions ran.
    // Without it "28.10.1010.4" parses as 28.10.1010 and the tool reports a version no metadata
    // file ever stated.
    if (text.empty() || !isdigit((unsigned char)text[0]) ||
        sscanf(text.c_str(), "%u.%u.%u%n", &major, &minor, &subminor, &consumed) != 3 || consumed != (int)text.size())
    {
        return false;
    }
    if (major > 0xff || minor > 0xff || subminor > 0xffff)
    {
        return false;
    }
    version.major = (u_int8_t)major;
    version.minor = (u_int8_t)minor;
    version.subminor = (u_int16_t)subminor;
    return true;
}

static int compareCableFwVersions(const CableFwVersion& left, const CableFwVersion& right)
{
    if (left.major != right.major)
    {
        return (left.major < right.major) ? -1 : 1;
    }
    if (left.minor != right.minor)
    {
        return (left.minor < right.minor) ? -1 : 1;
    }
    if (left.subminor != right.subminor)
    {
        return (left.subminor < right.subminor) ? -1 : 1;
    }
    return 0;
}

/* Read the package when it is a ZIP.
 *
 * mstflint carries no ZIP reader (MFT reads it with MinizipArchive), so the ZIP cannot be opened
 * here at all, the same as MFT on aarch64.
 */
static void readPackageArchive(const string& path, map<string, vector<u_int8_t> >& contents)
{
    (void)path;
    (void)contents;
    throw std::runtime_error("reading a ZIP package is not supported on this platform; pass a tgz package, or "
                             "extract it and pass the directory instead");
}

/* The tar and gzip half of the package readers: the OIF CMIS Firmware Update Package IA ships a
 * package as one gzipped tar (.tgz). Unlike the ZIP reader this needs only zlib, so it works on
 * every platform.
 */
#define CABLE_TAR_BLOCK 512
#define CABLE_GZIP_CHUNK 65536
// A package holds a few cable images of a megabyte or two each; anything near this is not one,
// and inflating it unchecked would let a small file exhaust memory.
#define CABLE_PACKAGE_MAX_SIZE (1024u * 1024u * 1024u)

static bool isGzip(const vector<u_int8_t>& data)
{
    return data.size() >= 2 && data[0] == 0x1f && data[1] == 0x8b;
}

static bool isTar(const vector<u_int8_t>& data)
{
    return data.size() >= CABLE_TAR_BLOCK && memcmp(&data[257], "ustar", 5) == 0;
}

static vector<u_int8_t> gunzip(const vector<u_int8_t>& data)
{
    z_stream stream;
    vector<u_int8_t> result;
    vector<u_int8_t> chunk(CABLE_GZIP_CHUNK);

    memset(&stream, 0, sizeof(stream));
    // 16 on top of the window bits selects the gzip wrapper rather than raw zlib.
    if (inflateInit2(&stream, 16 + MAX_WBITS) != Z_OK)
    {
        throw std::runtime_error("cannot start decompressing the package");
    }
    stream.next_in = (Bytef*)&data[0];
    stream.avail_in = (uInt)data.size();
    while (true)
    {
        stream.next_out = &chunk[0];
        stream.avail_out = (uInt)chunk.size();
        int rc = inflate(&stream, Z_NO_FLUSH);
        if (rc != Z_OK && rc != Z_STREAM_END)
        {
            inflateEnd(&stream);
            throw std::runtime_error("is not a valid gzip file");
        }
        result.insert(result.end(), chunk.begin(), chunk.end() - stream.avail_out);
        if (result.size() > CABLE_PACKAGE_MAX_SIZE)
        {
            inflateEnd(&stream);
            throw std::runtime_error("decompresses to more than a firmware package should hold");
        }
        if (rc == Z_STREAM_END)
        {
            // gzip allows several members back to back, and their contents run on as one stream.
            if (stream.avail_in == 0)
            {
                break;
            }
            inflateReset(&stream);
            continue;
        }
        if (stream.avail_in == 0 && stream.avail_out != 0)
        {
            inflateEnd(&stream);
            throw std::runtime_error("is a truncated gzip file");
        }
    }
    inflateEnd(&stream);
    return result;
}

static string tarText(const u_int8_t* field, size_t length)
{
    size_t end = 0;

    while (end < length && field[end] != '\0')
    {
        end++;
    }
    return string((const char*)field, end);
}

/* Tar keys a file by the path it was archived under, often with a leading ./, where the other readers
 * key it relative to the package root.
 */
static string tarRelativePath(const string& name)
{
    size_t start = 0;

    while (true)
    {
        if (name.compare(start, 2, "./") == 0)
        {
            start += 2;
        }
        else if (name.compare(start, 1, "/") == 0)
        {
            start += 1;
        }
        else
        {
            break;
        }
    }
    return name.substr(start);
}

/* The path a pax extended header gives the next entry, from its "length path=value\n" records. */
static string paxPath(const u_int8_t* data, size_t size)
{
    string records((const char*)data, size);
    string path;
    size_t pos = 0;

    while (pos < records.size())
    {
        size_t space = records.find(' ', pos);
        if (space == string::npos)
        {
            break;
        }
        unsigned long length = strtoul(records.substr(pos, space - pos).c_str(), NULL, 10);
        if (length == 0 || pos + length > records.size())
        {
            break;
        }
        string record = records.substr(space + 1, pos + length - space - 2); // drops the trailing newline
        if (record.compare(0, 5, "path=") == 0)
        {
            path = record.substr(5);
        }
        pos += length;
    }
    return path;
}

static void readTarEntries(const vector<u_int8_t>& tar, map<string, vector<u_int8_t> >& contents)
{
    size_t pos = 0;
    string nextName;
    bool ended = false;

    while (pos + CABLE_TAR_BLOCK <= tar.size())
    {
        const u_int8_t* header = &tar[pos];
        bool empty = true;

        for (size_t i = 0; i < CABLE_TAR_BLOCK && empty; i++)
        {
            empty = header[i] == 0;
        }
        // Two zero blocks end the archive; the first is enough to stop on.
        if (empty)
        {
            ended = true;
            break;
        }
        // The checksum is what tells a tar header from arbitrary bytes: the sum of the header with
        // its own field read as spaces.
        unsigned long sum = 0;
        for (size_t i = 0; i < CABLE_TAR_BLOCK; i++)
        {
            sum += (i >= 148 && i < 156) ? (unsigned long)' ' : (unsigned long)header[i];
        }
        if (strtoul(tarText(header + 148, 8).c_str(), NULL, 8) != sum)
        {
            throw std::runtime_error("is not a valid tar archive");
        }
        string name = tarText(header, 100);
        string prefix = tarText(header + 345, 155);
        if (memcmp(header + 257, "ustar", 5) == 0 && !prefix.empty())
        {
            name = prefix + "/" + name;
        }
        if (!nextName.empty())
        {
            name = nextName;
            nextName.clear();
        }
        unsigned long long size = strtoull(tarText(header + 124, 12).c_str(), NULL, 8);
        char type = (char)header[156];

        pos += CABLE_TAR_BLOCK;
        if (size > tar.size() - pos)
        {
            throw std::runtime_error("is a truncated tar archive");
        }
        const u_int8_t* data = tar.empty() ? NULL : &tar[pos];
        if (type == 'L')
        {
            // GNU tar puts a name longer than 100 characters in an entry of its own, ahead of the file.
            nextName = tarText(data, (size_t)size);
        }
        else if (type == 'x')
        {
            nextName = paxPath(data, (size_t)size);
        }
        else if (type == '0' || type == '\0' || type == '7')
        {
            string relative = tarRelativePath(name);
            if (!relative.empty())
            {
                contents[relative] = vector<u_int8_t>(data, data + size);
            }
        }
        // Directories need no entry, and links are dropped as the other readers drop them.
        pos += (size_t)((size + CABLE_TAR_BLOCK - 1) / CABLE_TAR_BLOCK) * CABLE_TAR_BLOCK;
    }
    // Every tar writer ends the archive with zero blocks, so running out of data first means files
    // past this point were lost.
    if (!ended)
    {
        throw std::runtime_error("is a truncated tar archive");
    }
}

/* Read a package file, whichever archive it is: a gzipped tar, a plain tar, or a ZIP. Told apart by
 * content rather than by name, since a package is named however its vendor chose.
 */
static void readPackageFile(const string& path, map<string, vector<u_int8_t> >& contents)
{
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    if (file && file.tellg() > (std::streamoff)CABLE_PACKAGE_MAX_SIZE)
    {
        throw std::runtime_error("is larger than a firmware package should be");
    }
    file.close();
    vector<u_int8_t> data = mft_utils::ReadBinFile(path);

    if (isGzip(data))
    {
        readTarEntries(gunzip(data), contents);
    }
    else if (isTar(data))
    {
        readTarEntries(data, contents);
    }
    else
    {
        readPackageArchive(path, contents);
    }
}

static string pathBaseName(const string& path)
{
    size_t slash = path.find_last_of("/\\");

    return (slash == string::npos) ? path : path.substr(slash + 1);
}

/* Read the package when it is a directory, keyed exactly as the ZIP reader keys it: a path
 * relative to the package root, with forward slashes, so nothing downstream can tell the two
 * apart.
 */
/* How deep a package directory may nest before the walk calls it a loop. */
#define CABLE_PACKAGE_MAX_DEPTH 8

static void readPackageDirectory(const string& path,
                                 const string& prefix,
                                 map<string, vector<u_int8_t> >& contents,
                                 unsigned int depth)
{
    // A package is a folder per part number holding a metadata file and its binary, so nothing
    // legitimate is this deep. The cap is what stops a reparse-point loop on the platforms where
    // IsSymlink() cannot see one, so it has to come before the directory is read.
    if (depth > CABLE_PACKAGE_MAX_DEPTH)
    {
        throw std::runtime_error("is nested deeper than a firmware package should be: " + path);
    }
    vector<string> entries = mft_utils::GetListOfFiles(path);

    for (size_t i = 0; i < entries.size(); i++)
    {
        string relative = prefix.empty() ? pathBaseName(entries[i]) : prefix + "/" + pathBaseName(entries[i]);

        // The archive reader drops symlink entries, so the directory reader has to as well: the
        // same package read the two documented ways must give the same files. A symlinked folder
        // would otherwise deliver every metadata file under it twice, and two identical entries
        // are exactly what the conflict check rejects.
        if (mft_utils::IsSymlink(entries[i]))
        {
            continue;
        }
        if (mft_utils::IsDirectory(entries[i]))
        {
            readPackageDirectory(entries[i], relative, contents, depth + 1);
        }
        else if (mft_utils::IsRegularFile(entries[i]))
        {
            // A FIFO or a device node is not part of a firmware package, and reading one blocks.
            contents[relative] = mft_utils::ReadBinFile(entries[i]);
        }
    }
}

static bool hasSuffix(const string& text, const string& suffix)
{
    return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/* Whether two metadata files describe the same cable. Every key both entries constrain has to
 * agree; a key only one of them states cannot separate them, because a cable carrying that value
 * matches both.
 */
/* Archive entries always use forward slashes, whatever wrote them. */
static string archiveDirectory(const string& entryName)
{
    size_t slash = entryName.find_last_of('/');

    return (slash == string::npos) ? "" : entryName.substr(0, slash + 1);
}

/* An OUI as six upper-case hex digits, the form a VendorOUI pattern is compared in. */
static string cableOuiText(u_int32_t oui)
{
    char text[8];

    snprintf(text, sizeof(text), "%06X", oui & 0xffffff);
    return string(text);
}

/* A VendorOUI the metadata wrote as 0x48B02D, 48-B0-2D or 48:b0:2d, brought to the six-digit form. */
static string normalizedOuiPattern(const string& pattern)
{
    string body = pattern;
    string result;

    if (body.size() > 2 && body[0] == '0' && (body[1] == 'x' || body[1] == 'X'))
    {
        body = body.substr(2);
    }
    for (size_t i = 0; i < body.size(); i++)
    {
        if (body[i] != '-' && body[i] != ':' && body[i] != ' ')
        {
            result += (char)toupper((unsigned char)body[i]);
        }
    }
    return result;
}

static bool metadataMatchesCable(const FwPackageEntry& entry, const CableInfo& cable)
{
    const CableFwVersion& running = (cable.runningSlot == CABLE_IMAGE_SLOT_B) ? cable.fwImageB : cable.fwImageA;

    // The IA allows no wildcard here and asks for an exact match.
    if (entry.vendorName != cable.vendorName)
    {
        return false;
    }
    // The load's major is the LinkX product id: an image for another product is not an upgrade for
    // this cable whatever the patterns say, and the device would refuse it.
    if (entry.fwVersion.major != running.major)
    {
        return false;
    }
    // The part number and the revision are compared case and all: the extended header carries the
    // metadata's own bytes, and the device compares those against the EEPROM.
    if (!entry.vendorPartNumber.empty() && !globMatches(entry.vendorPartNumber, cable.partNumber))
    {
        return false;
    }
    if (entry.hasVendorOui && !globMatches(normalizedOuiPattern(entry.vendorOui), cableOuiText(cable.vendorOui)))
    {
        return false;
    }
    if (entry.hasVendorRev && !globMatches(entry.vendorRev, cable.vendorRev))
    {
        return false;
    }
    if (entry.hasVendorSn && !globMatches(entry.vendorSn, cable.serialNumber))
    {
        return false;
    }
    if (entry.hasHwRevMajor && !globMatches(entry.hwRevMajor, int_to_string((int)cable.hwRevMajor)))
    {
        return false;
    }
    if (entry.hasHwRevMinor && !globMatches(entry.hwRevMinor, int_to_string((int)cable.hwRevMinor)))
    {
        return false;
    }
    if (entry.hasActiveFwVersion)
    {
        // The release writes the version zero padded, 070.010.11016, and tools print it bare,
        // 70.10.11016; a pattern in either form matches.
        char padded[32];
        char bare[32];

        snprintf(padded, sizeof(padded), "%03u.%03u.%05u", (unsigned)running.major, (unsigned)running.minor,
                 (unsigned)running.subminor);
        snprintf(bare, sizeof(bare), "%u.%u.%u", (unsigned)running.major, (unsigned)running.minor,
                 (unsigned)running.subminor);
        if (!globMatches(entry.activeFwVersion, padded) && !globMatches(entry.activeFwVersion, bare))
        {
            return false;
        }
    }
    return true;
}

/* The 48-byte header the device matches a cable against, for a package image that carries none of
 * its own.
 *
 * Every field comes from the metadata. The part number and the product id are always there; the
 * hardware major and the vendor revision only when the metadata states them, and zero otherwise,
 * which the device treats as a wildcard. The vendor byte, the firmware minor and build and the
 * reserved bytes are zero.
 */
#define CABLE_EXT_HEADER_PN_LENGTH 16
#define CABLE_EXT_HEADER_REV_LENGTH 2
#define CABLE_EXT_HEADER_RESERVED 12
#define CABLE_EXT_HEADER_SIZE 48

bool CableExtHeaderKey::isComplete() const
{
    return !partNumber.empty() && partNumber.size() <= CABLE_EXT_HEADER_PN_LENGTH &&
           vendorRev.size() <= CABLE_EXT_HEADER_REV_LENGTH && productId != 0;
}

string CableExtHeaderKey::groupKey() const
{
    // Length prefixed rather than delimited, so two headers whose fields differ never produce one
    // key: they would share a burn that only one of them describes.
    return int_to_string((int)partNumber.size()) + ':' + partNumber + int_to_string((int)vendorRev.size()) + ':' +
           vendorRev + ':' + int_to_string((int)hwRevMajor) + ':' + int_to_string((int)productId);
}

string CableExtHeaderKey::text() const
{
    // A zero field is a wildcard, and saying so is clearer than printing the zero.
    string rev = vendorRev.empty() ? string("any") : "'" + vendorRev + "'";
    string hw = (hwRevMajor == 0) ? string("any") : int_to_string((int)hwRevMajor);

    return "part number '" + partNumber + "', vendor revision " + rev + ", hardware major " + hw + ", product id " +
           int_to_string((int)productId);
}

/* How the device will decide whether this group's image belongs on a cable. */
static string planEntryHeaderText(const CablePlanEntry& group)
{
    if (group.isWrapped)
    {
        return "extended header built from the metadata: " + group.header.text();
    }
    if (group.imageHasOwnHeader)
    {
        return "extended header as the package supplied it";
    }
    return "no extended header: the device matches on the product id alone and may reach cables "
           "this plan skipped";
}

/* The header a package image gets from the metadata entry a cable matched.
 *
 * Built from that entry rather than looked up by image path: two metadata files may name the same
 * binary for different part numbers.
 */
static CableExtHeaderKey cableExtHeaderKey(const FwPackageEntry& entry)
{
    CableExtHeaderKey key;

    // A pattern cannot go into the header, which the device compares byte for byte: a wildcard
    // part number leaves the image unwrapped, and a wildcard revision or hardware major is left
    // zero, which the device treats as any.
    key.partNumber = hasWildcard(entry.vendorPartNumber) ? string() : entry.vendorPartNumber;
    key.vendorRev = (entry.hasVendorRev && !hasWildcard(entry.vendorRev)) ? entry.vendorRev : string();
    unsigned int hwRevMajor = 0;
    int consumed = 0;
    if (entry.hasHwRevMajor && sscanf(entry.hwRevMajor.c_str(), "%u%n", &hwRevMajor, &consumed) == 1 &&
        consumed == (int)entry.hwRevMajor.size() && hwRevMajor <= 0xff)
    {
        key.hwRevMajor = (u_int8_t)hwRevMajor;
    }
    key.productId = entry.fwVersion.major;
    return key;
}

static vector<u_int8_t> withExtendedHeader(const CableExtHeaderKey& key, const vector<u_int8_t>& image)
{
    vector<u_int8_t> wrapped;
    u_int32_t imageSize = (u_int32_t)image.size();
    // Least significant byte first, rather than a memcpy of the host's own representation: the
    // device reads these four bytes off the wire, and linux-ppc64 is big endian.
    u_int8_t sizeBytes[4] = {(u_int8_t)(imageSize & 0xff), (u_int8_t)((imageSize >> 8) & 0xff),
                             (u_int8_t)((imageSize >> 16) & 0xff), (u_int8_t)((imageSize >> 24) & 0xff)};
    const char* magic = CABLE_EXT_HEADER_MAGIC_STRING;

    wrapped.assign(magic, magic + CABLE_EXT_HEADER_MAGIC_LENGTH);
    wrapped.push_back(1);                // header version: carries an explicit image size
    wrapped.insert(wrapped.end(), 3, 0); // vendor byte and the reserved pair
    for (size_t i = 0; i < CABLE_EXT_HEADER_PN_LENGTH; i++)
    {
        // The device compares this against the 16-byte EEPROM part number, which is space padded.
        wrapped.push_back((i < key.partNumber.size()) ? (u_int8_t)key.partNumber[i] : (u_int8_t)' ');
    }
    wrapped.push_back(0); // reserved
    wrapped.push_back(key.hwRevMajor);
    for (size_t i = 0; i < CABLE_EXT_HEADER_REV_LENGTH; i++)
    {
        // An omitted revision is zero, the wildcard. A stated one is space padded like the part
        // number above, being the same kind of fixed-width EEPROM ASCII field.
        u_int8_t pad = key.vendorRev.empty() ? 0 : (u_int8_t)' ';
        wrapped.push_back((i < key.vendorRev.size()) ? (u_int8_t)key.vendorRev[i] : pad);
    }
    wrapped.push_back(key.productId);    // the LinkX product id
    wrapped.insert(wrapped.end(), 3, 0); // firmware minor and build
    wrapped.insert(wrapped.end(), sizeBytes, sizeBytes + sizeof(sizeBytes));
    wrapped.insert(wrapped.end(), CABLE_EXT_HEADER_RESERVED, 0);
    wrapped.insert(wrapped.end(), image.begin(), image.end());
    return wrapped;
}

/* The extended header at the front of a wrapped image, as hex, for the debug trace: the bytes are
 * what the device matches a cable against, so they are the thing to look at when a burn stalls.
 */
static string extendedHeaderHex(const vector<u_int8_t>& wrapped)
{
    std::ostringstream text;
    size_t size = (wrapped.size() < CABLE_EXT_HEADER_SIZE) ? wrapped.size() : CABLE_EXT_HEADER_SIZE;

    for (size_t i = 0; i < size; i++)
    {
        text << (i ? " " : "") << std::hex << std::setw(2) << std::setfill('0') << (unsigned)wrapped[i];
    }
    return text.str();
}

/* Every LinkX burn in this tree hands the device eight 0xFF bytes ahead of the image. The device
 * cannot tell this flow from an ordinary cable burn and was never told about it, so what goes on
 * the wire has to be what an ordinary burn puts there: the same prefix, and the extended header at
 * the front of the image behind it, exactly where a package that already carries one puts it.
 */
#define CABLE_BURN_IMAGE_PREFIX_SIZE 8

static string cableFwVersionText(const CableFwVersion& version)
{
    char text[32];

    snprintf(text, sizeof(text), "%02d.%02d.%04d", version.major, version.minor, version.subminor);
    return string(text);
}

static string orNotAvailable(const string& value)
{
    return value.empty() ? CABLE_REPORT_NOT_AVAILABLE : value;
}

/* std::setw pads but never truncates, so a value wider than its column pushes every column after
 * it out of line. One short of the width, so the column always keeps a separating space. */
static string clamped(const string& value, size_t width)
{
    return (value.size() < width) ? value : value.substr(0, width - 1);
}

/* PDDR page_select for the module info page, where the firmware republishes the cable EEPROM. */
#define CABLE_PDDR_MODULE_INFO_PAGE 3

/* PDDR cable_type: the firmware says the cage is empty with this one value. */
#define CABLE_PDDR_TYPE_UNPLUGGED 4

/* The form factor as the firmware names it. This is not the SFF-8024 identifier byte - the two
 * are different number spaces - and it is what mlxlink prints.
 */
static const char* cablePddrIdentifierName(u_int8_t identifier)
{
    switch (identifier)
    {
        case 0:
            return "QSFP28";
        case 1:
            return "QSFP+";
        case 2:
            return "SFP28/SFP+";
        case 3:
            return "QSA";
        case 4:
            return "Backplane";
        case 5:
            return "SFP-DD";
        case 6:
            return "QSFP-DD";
        case 7:
            return "QSFP_CMIS";
        case 8:
            return "OSFP";
        case 9:
            return "C2C";
        case 10:
            return "DSFP";
        case 11:
            return "QSFP_Split";
        case 12:
            return "CPO";
        case 13:
            return "OE";
        case 14:
            return "ELS";
        case 15:
            return "NPO";
        default:
            return CABLE_REPORT_NOT_AVAILABLE;
    }
}

/* PDDR keeps the ASCII identity fields in dword arrays, most significant byte first. NULs are
 * padding wherever they fall - the vendor revision is right-aligned and NUL-padded on the left -
 * but a space is only padding at the end: a vendor name or part number may contain one, and these
 * fields are what the package is matched on.
 */
static string pddrAsciiText(const u_int32_t* words, size_t count)
{
    string text;

    for (size_t i = 0; i < count; i++)
    {
        for (int shift = 24; shift >= 0; shift -= 8)
        {
            char c = (char)((words[i] >> shift) & 0xff);
            if (c != '\0')
            {
                text += c;
            }
        }
    }
    size_t end = text.find_last_not_of(' ');
    return (end == string::npos) ? string() : text.substr(0, end + 1);
}

static string pddrAsciiWord(u_int32_t word)
{
    return pddrAsciiText(&word, 1);
}

/* Read one cable's identity and state off the PDDR module info page. The firmware has already
 * decoded the EEPROM into it, so this is one register read where MCIA takes four, and it is the
 * same source every field mlxlink prints comes from.
 */
static bool readCableModuleInfo(mfile* mf, u_int32_t localPort, CableInfo& cable)
{
    struct reg_access_switch_pddr_reg_ext pddr;

    memset(&pddr, 0, sizeof(pddr));
    pddr.local_port = (u_int8_t)(localPort & 0xff);
    pddr.lp_msb = (u_int8_t)((localPort >> 8) & 0x3);
    pddr.page_select = CABLE_PDDR_MODULE_INFO_PAGE;
    reg_access_status_t status = reg_access_pddr(mf, REG_ACCESS_METHOD_GET, &pddr);
    if (status != ME_OK)
    {
        FWMANAGER_LOG_DEBUG("PDDR module info: local_port %u, status %d", localPort, (int)status);
        return false;
    }

    const struct reg_access_switch_pddr_module_info_ext& info = pddr.page_data.pddr_module_info_ext;

    cable.isPlugged = (info.cable_type != CABLE_PDDR_TYPE_UNPLUGGED);
    if (!cable.isPlugged)
    {
        return true;
    }
    cable.identifier = cablePddrIdentifierName(info.cable_identifier);
    cable.state = cableModuleStateName(info.module_st);
    cable.vendorName = pddrAsciiText(info.vendor_name, 4);
    cable.partNumber = pddrAsciiText(info.vendor_pn, 4);
    cable.serialNumber = pddrAsciiText(info.vendor_sn, 4);
    cable.vendorRev = pddrAsciiWord(info.vendor_rev);
    cable.vendorOui = info.vendor_oui;
    cable.hwRevMajor = info.module_hw_revision_major;
    cable.hwRevMinor = info.module_hw_revision_minor;

    // Eight ASCII characters, year first, of which the last two are a lot code. Rendered the way
    // mlxlink does, which puts the day first.
    string date;
    for (int shift = 56; shift >= 0; shift -= 8)
    {
        char c = (char)((info.date_code >> shift) & 0xff);
        if (c != '\0' && c != ' ')
        {
            date += c;
        }
    }
    if (date.size() >= CABLE_EEPROM_DATE_LEN)
    {
        cable.manufacturingDate = date.substr(4, 2) + "_" + date.substr(2, 2) + "_" + date.substr(0, 2);
    }
    FWMANAGER_LOG_DEBUG("PDDR module info: local_port %u, %s %s pn %s sn %s rev %s oui 0x%06x hw %d.%d", localPort,
                        cable.identifier.c_str(), cable.state.c_str(), cable.partNumber.c_str(),
                        cable.serialNumber.c_str(), cable.vendorRev.c_str(), cable.vendorOui, (int)cable.hwRevMajor,
                        (int)cable.hwRevMinor);
    return true;
}

/* PDDR page_select for the operational info page, which carries the link state machine. */
#define CABLE_PDDR_OPERATIONAL_INFO_PAGE 0

/* Local ports are not numbered from one and nothing reports the highest, so the PLLP sweep runs to
 * the most PLLP can address: local_port plus its 2-bit lp_msb, 10 bits. Measured: label port 1
 * sits at local port 129 on Quantum-3 and at 417 on Spectrum-6, whose local ports reach 516.
 */
#define CABLE_MAX_LOCAL_PORT 1023

/* phy_mngr_fsm_state. The link is carrying traffic on exactly one of these. */
#define CABLE_LINK_STATE_ACTIVE 3
#define CABLE_LINK_STATE_ACTIVE_NAME "Active"

/* The PHY manager link state, which is what mlxlink prints as "State". It is the link, not the
 * cable: a healthy cable with nothing at the far end sits in Polling forever.
 */
static const char* cableLinkStateName(u_int8_t state)
{
    switch (state)
    {
        case 0:
            return "Disable";
        case 1:
            return "Port PLL Down";
        case 2:
            return "Polling";
        case CABLE_LINK_STATE_ACTIVE:
            return "Active";
        case 4:
            return "Close port";
        case 5:
            return "Physical LinkUp";
        case 6:
            return "Sleep";
        case 7:
            return "Rx disable";
        case 8:
            return "Signal detect";
        case 9:
            return "Receiver detect";
        case 10:
            return "Sync peer";
        case 11:
            return "Negotiation";
        case 12:
            return "Training";
        case 13:
            return "SubFSM active";
        default:
            return CABLE_REPORT_NOT_AVAILABLE;
    }
}

static reg_access_status_t readCableLinkState(mfile* mf, u_int32_t localPort, u_int8_t& state)
{
    struct reg_access_switch_pddr_reg_ext pddr;

    memset(&pddr, 0, sizeof(pddr));
    pddr.local_port = (u_int8_t)(localPort & 0xff);
    pddr.lp_msb = (u_int8_t)((localPort >> 8) & 0x3);
    pddr.page_select = CABLE_PDDR_OPERATIONAL_INFO_PAGE;
    reg_access_status_t status = reg_access_pddr(mf, REG_ACCESS_METHOD_GET, &pddr);
    if (status == ME_OK)
    {
        state = pddr.page_data.pddr_operation_info_page_ext.phy_mngr_fsm_state;
    }
    FWMANAGER_LOG_DEBUG("PDDR: local_port %u, status %d, phy_mngr_fsm_state %d", localPort, (int)status, (int)state);
    return status;
}

/* PLLP carries both a local port and the label port it serves, and is indexed by the local port,
 * so the map a cage needs is built by sweeping it. Only the first sub-port of a cage is kept - the
 * one mlxlink resolves a bare label port to - since they share one cable. The same read says
 * whether that port is a service (FNM) port, which is how mlxlink tags one.
 *
 * The whole range is swept: an ASIC can carry sub-ports of cages it does not own, so no count of
 * its own cages tells when it is done. Measured on a four-ASIC Quantum-3: every ASIC carries one
 * split of each cage, and only the GA 0 ASIC carries split 0.
 */
static void buildLocalPortMap(mfile* mf, map<u_int32_t, u_int32_t>& localPortByCage, set<u_int32_t>& serviceCages)
{
    for (u_int32_t localPort = 1; localPort <= CABLE_MAX_LOCAL_PORT; localPort++)
    {
        struct reg_access_switch_pllp_reg_ext pllp;

        memset(&pllp, 0, sizeof(pllp));
        pllp.local_port = (u_int8_t)(localPort & 0xff);
        pllp.lp_msb = (u_int8_t)((localPort >> 8) & 0x3);
        if (reg_access_pllp(mf, REG_ACCESS_METHOD_GET, &pllp) != ME_OK || pllp.label_port == 0)
        {
            continue;
        }
        bool firstSubPort =
          (pllp.ipil_stat == 0 || pllp.ipil_num == 1) && (pllp.split_stat == 0 || pllp.split_num == 0);
        if (firstSubPort)
        {
            localPortByCage.insert(std::make_pair((u_int32_t)pllp.label_port - 1, localPort));
            if (pllp.is_fnm)
            {
                serviceCages.insert((u_int32_t)pllp.label_port - 1);
            }
        }
    }
    FWMANAGER_LOG_DEBUG("PLLP sweep: mapped %u cage(s), %u of them service ports", (unsigned)localPortByCage.size(),
                        (unsigned)serviceCages.size());
}

#define CABLE_REPORT_RULE "===================================================="

/* A phase's duration for the summary, to the second and spelled the way `time` does: "9s", "4m5s". */
static string elapsedText(double seconds)
{
    if (seconds < 0)
    {
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    long total = (long)(seconds + 0.5);

    if (total < 60)
    {
        return int_to_string((int)total) + "s";
    }
    return int_to_string((int)(total / 60)) + "m" + int_to_string((int)(total % 60)) + "s";
}

/* Human-readable local time for the report header. */
static string reportTimestamp()
{
    time_t now = time(0);
    tm* localNow = localtime(&now);
    char stamp[32];

    // strftime keeps the fixed buffer provably in range; the equivalent snprintf does not, because
    // every %d is bounded only by the width of an int.
    if (localNow == NULL || strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", localNow) == 0)
    {
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    return stamp;
}

/* Which image slot is running, if any. runningSlot alone cannot say "neither". */
static string cableRunningSlotText(bool isRunningImage, CableImageSlot slot)
{
    if (!isRunningImage)
    {
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    return (slot == CABLE_IMAGE_SLOT_B) ? "B" : "A";
}

static string cableHwRevisionText(const CableInfo& cable)
{
    if (cable.hwRevMajor == 0 && cable.hwRevMinor == 0)
    {
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    return cableHwRevisionText(cable.hwRevMajor, cable.hwRevMinor);
}

/* The action the report names, spelled as the enumerator it came from.
 *
 * A reader matching a row against the code, or grepping a stored report, wants the constant rather
 * than a sentence that could be reworded; the reason each one means is in the code beside its
 * enumerator.
 */
static const char* cableActionName(CableUpdateAction action)
{
    switch (action)
    {
        case CABLE_ACTION_UPDATE:
            return "UPDATE";
        case CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED:
            return "SKIP_ASIC_DETECTION_NOT_SUPPORTED";
        case CABLE_ACTION_SKIP_NOT_PLUGGED:
            return "SKIP_NOT_PLUGGED";
        case CABLE_ACTION_SKIP_UNREADABLE:
            return "SKIP_UNREADABLE";
        case CABLE_ACTION_SKIP_3RD_PARTY:
            return "SKIP_3RD_PARTY";
        case CABLE_ACTION_SKIP_NOT_BURNABLE:
            return "SKIP_NOT_BURNABLE";
        case CABLE_ACTION_SKIP_NO_FW_FILE:
            return "SKIP_NO_FW_FILE";
        case CABLE_ACTION_SKIP_CURRENT:
            return "SKIP_CURRENT";
        default:
            return "UNDECIDED";
    }
}

/* The device describes itself in one line of semicolon-separated clauses; the first is the part
 * that names the product, and the rest are the mechanical details the report has no use for.
 */
static string deviceDescription(const string& full)
{
    size_t semicolon = full.find(';');
    string text = (semicolon == string::npos) ? full : full.substr(0, semicolon);
    size_t end = text.find_last_not_of(" \t");

    return (end == string::npos) ? "" : text.substr(0, end + 1);
}

static string cdbErrorText(u_int16_t code)
{
    char text[128];

    if (code == MCCE_CDB_ERROR_NOT_RELEVANT)
    {
        return "Not Relevant";
    }
    snprintf(text, sizeof(text), "%s (0x%04x)", PackageErrorCodeToString(code), code);
    return string(text);
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
            emitProgress("-W- Skipped " + string(devs[i].dev_name) + ": the device could not be opened\n");
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
                emitProgress("-W- Skipped " + string(devs[i].dev_name) + ": the device type is not recognised\n");
            }
            else
            {
                emitProgress("-W- Skipped " + string(devs[i].dev_name) +
                             ": recognising the device type failed with error " + int_to_string(devIdRc) + "\n");
            }
            mclose(mf);
            continue;
        }
        if (!dm_dev_is_switch(devType))
        {
            FWMANAGER_LOG_DEBUG("Skipped %s: %s is not a switch", devs[i].dev_name, dm_dev_type2str(devType));
            mclose(mf);
            continue;
        }

        AsicInfo asic;
        u_int8_t ga = 0;
        asic.devName = devs[i].dev_name;
        reg_access_status_t status = readAsicGa(mf, ga, asic.fwVersion);
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

    emitProgress("-I- Found " + int_to_string((int)_asics.size()) + " switch ASIC(s)\n");
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

    mfile* mf = deviceHandle(source->second.devName);
    if (mf == NULL)
    {
        _errMsg = "Failed to open " + source->second.devName + " to read the cable map";
        return ERR_CODE_CABLE_UPDATE_FAILED;
    }

    u_int32_t total = 0;
    reg_access_status_t status = readCageCount(mf, total);
    if (status != ME_OK)
    {
        _errMsg = "Failed to read MGPIR from " + source->second.devName + ": " + reg_access_err2str(status);
        return ERR_CODE_CABLE_UPDATE_FAILED;
    }

    int rc = walkCableMap(mf, total);
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    emitProgress("-I- Found " + int_to_string((int)_cables.size()) + " port(s), scanning for cables\n");
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
            FWMANAGER_LOG_DEBUG("Port %s is of module type %s, which leaves MMAM.ga Reserved, so its owning ASIC "
                                "cannot be identified",
                                globalPort.c_str(), moduleTypeName(entry.module_type).c_str());
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
    u_int32_t plugged = 0;
    u_int32_t burnable = 0;
    u_int32_t unreadable = 0;

    for (AsicsByGa::iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = deviceHandle(asic->second.devName);
        if (mf == NULL)
        {
            _errMsg = "Failed to open " + asic->second.devName + " to query the cables it owns";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }
        buildLocalPortMap(mf, asic->second.localPortByCage, asic->second.serviceCages);
        if (isInterrupted())
        {
            _errMsg = "Interrupted by the user";
            return ERR_CODE_INTERRUPTED;
        }
    }
    setAsideServicePorts();
    // Every map is built before any cage is queried: a cage can be served by an ASIC later in the
    // order than its owner.
    for (AsicsByGa::iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = deviceHandle(asic->second.devName);
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
            if (isInterrupted())
            {
                _errMsg = "Interrupted by the user";
                return ERR_CODE_INTERRUPTED;
            }
            // Query each cage from the ASIC that owns it - only there do MCIA, PMAOS and MCQI
            // answer for the right cable. Ownership is what MMAM said in phase 1.
            if (_cables[j].asicGa == asic->first)
            {
                queryCable(mf, _cables[j]);
            }
        }
    }

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].isPlugged)
        {
            plugged++;
        }
        // Counted the way the plan skips them: an NVIDIA cable whose firmware did not read is as
        // unreadable as one whose identity did not, and neither is updatable. An MFCDR verdict of
        // fake or non-NVIDIA outranks both, as it does in the plan.
        bool isThirdParty = _cables[i].vendorStatus == CABLE_VENDOR_STATUS_FAKE ||
                            _cables[i].vendorStatus == CABLE_VENDOR_STATUS_NON_NVIDIA;
        bool isUnreadable = _cables[i].isPlugged && !isThirdParty &&
                            (!_cables[i].isReadable || _cables[i].vendorStatus == CABLE_VENDOR_STATUS_READ_FAILED ||
                             (_cables[i].isNvidia && !_cables[i].fwRead));
        if (isUnreadable)
        {
            unreadable++;
        }
        else if (_cables[i].isBurnable)
        {
            burnable++;
        }
    }
    // Counted as found, since the cage is populated, but said apart: they are the cables no action can reach.
    emitProgress("-I- Found " + int_to_string((int)plugged) + " cable(s), " + int_to_string((int)burnable) +
                 " of them updatable" +
                 ((unreadable > 0) ? ", " + int_to_string((int)unreadable) + " unreadable" : string()) + "\n");
    return MLX_FWM_SUCCESS;
}

/* The ASIC and local port serving a cage's first sub-port. PDDR needs them; MMAM never names one.
 *
 * The owner's map is asked first. Where the owner does not carry the first sub-port, another ASIC
 * may: on a four-ASIC Quantum-3 the GA 0 ASIC carries it for every cage. Another ASIC is taken only
 * when none of its own cages has this label number, because where labels restart on each ASIC its
 * entry would be a different cable, and only when it is the one such ASIC.
 */
bool CableFwManager::cableLocalPort(const CableInfo& cable, string& portDevName, u_int32_t& localPort) const
{
    AsicsByGa::const_iterator owner = _asics.find(cable.asicGa);

    if (owner == _asics.end())
    {
        return false;
    }
    map<u_int32_t, u_int32_t>::const_iterator port = owner->second.localPortByCage.find(cable.localIndex);
    if (port != owner->second.localPortByCage.end())
    {
        portDevName = owner->second.devName;
        localPort = port->second;
        return true;
    }
    portDevName.clear();
    for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        if (asic == owner)
        {
            continue;
        }
        port = asic->second.localPortByCage.find(cable.localIndex);
        if (port == asic->second.localPortByCage.end())
        {
            continue;
        }
        bool labelIsItsOwn = false;
        for (size_t i = 0; i < _cables.size() && !labelIsItsOwn; i++)
        {
            labelIsItsOwn = _cables[i].asicGa == asic->first && _cables[i].localIndex == cable.localIndex &&
                            _cables[i].action != CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED;
        }
        if (labelIsItsOwn)
        {
            continue;
        }
        if (!portDevName.empty())
        {
            FWMANAGER_LOG_DEBUG("Cable %u: both %s and %s carry a first sub-port for it, so neither is used",
                                cable.globalPort, portDevName.c_str(), asic->second.devName.c_str());
            portDevName.clear();
            return false;
        }
        portDevName = asic->second.devName;
        localPort = port->second;
    }
    return !portDevName.empty();
}

bool CableFwManager::isServicePort(const CableInfo& cable) const
{
    if (cable.action != CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED)
    {
        string portDevName;
        u_int32_t localPort = 0;

        if (!cableLocalPort(cable, portDevName, localPort))
        {
            return false;
        }
        for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
        {
            if (asic->second.devName == portDevName)
            {
                return asic->second.serviceCages.count(cable.localIndex) != 0;
            }
        }
        return false;
    }
    // Without an owner the port cannot be told apart from another ASIC's port of the same label, so
    // one ASIC calling that label a mission port is enough to keep it.
    bool carried = false;

    for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        if (asic->second.localPortByCage.count(cable.localIndex) == 0)
        {
            continue;
        }
        if (asic->second.serviceCages.count(cable.localIndex) == 0)
        {
            return false;
        }
        carried = true;
    }
    return carried;
}

void CableFwManager::setAsideServicePorts()
{
    vector<CableInfo> kept;
    string ports;

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (!isServicePort(_cables[i]))
        {
            kept.push_back(_cables[i]);
            continue;
        }
        FWMANAGER_LOG_DEBUG("Port %u is a service (FNM) port%s", _cables[i].globalPort,
                            _cmdParams.cable_include_service_ports ? ", included as asked" : ", skipped");
        ports += (ports.empty() ? "" : ", ") + int_to_string((int)_cables[i].globalPort);
        _servicePorts.push_back(_cables[i].globalPort);
    }
    if (_cmdParams.cable_include_service_ports)
    {
        // Named in the trace above, and reported like every other port.
        _servicePorts.clear();
        return;
    }
    if (!_servicePorts.empty())
    {
        emitProgress("-I- Skipping " + int_to_string((int)_servicePorts.size()) + " service (FNM) port(s): " + ports +
                     "; use --cable_include_service_ports to include them\n");
    }
    _cables.swap(kept);
}

/* The link state for one cable, which is what mlxlink shows as "State". */
string CableFwManager::readCableLinkStateText(const CableInfo& cable)
{
    string portDevName;
    u_int32_t localPort = 0;
    u_int8_t state = 0;

    if (!cableLocalPort(cable, portDevName, localPort))
    {
        FWMANAGER_LOG_DEBUG("Cable %u: no local port maps to this cage, so its link state is unknown",
                            cable.globalPort);
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    mfile* portMf = deviceHandle(portDevName);
    if (portMf == NULL)
    {
        FWMANAGER_LOG_DEBUG("Cable %u: %s could not be opened to read its link state", cable.globalPort,
                            portDevName.c_str());
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    reg_access_status_t status = readCableLinkState(portMf, localPort, state);
    if (status != ME_OK)
    {
        FWMANAGER_LOG_DEBUG("Cable %u: link state read failed on %s local port %u, status %d", cable.globalPort,
                            portDevName.c_str(), localPort, (int)status);
        return CABLE_REPORT_NOT_AVAILABLE;
    }
    return cableLinkStateName(state);
}

/* Whether PDDR left anything the EEPROM can supply. */
static bool hasIdentityGap(const CableInfo& cable)
{
    return cable.vendorName.empty() || cable.partNumber.empty() || cable.serialNumber.empty() ||
           cable.vendorRev.empty() || cable.manufacturingDate.empty() || cable.vendorOui == 0 ||
           (cable.hwRevMajor == 0 && cable.hwRevMinor == 0) || cable.identifier == CABLE_REPORT_NOT_AVAILABLE ||
           cable.state == CABLE_REPORT_NOT_AVAILABLE;
}

/* Fill whatever PDDR left empty from the EEPROM, field by field. PDDR stays authoritative for
 * everything it does answer, so the two tools still agree wherever they can.
 */
void CableFwManager::fillIdentityGapsFromEeprom(mfile* mf, CableInfo& cable)
{
    if (!hasIdentityGap(cable))
    {
        return;
    }
    CableInfo eeprom;

    eeprom.localIndex = cable.localIndex;
    // Carried so the identity trace names the port it read, rather than the zero a scratch record
    // is constructed with.
    eeprom.globalPort = cable.globalPort;
    if (!readCableIdentity(mf, eeprom))
    {
        FWMANAGER_LOG_DEBUG("Cable %u: EEPROM read failed, the fields PDDR left empty stay N/A", cable.globalPort);
        return;
    }
    if (cable.vendorName.empty())
    {
        cable.vendorName = eeprom.vendorName;
    }
    if (cable.partNumber.empty())
    {
        cable.partNumber = eeprom.partNumber;
    }
    if (cable.serialNumber.empty())
    {
        cable.serialNumber = eeprom.serialNumber;
    }
    if (cable.vendorRev.empty())
    {
        cable.vendorRev = eeprom.vendorRev;
    }
    if (cable.manufacturingDate.empty())
    {
        cable.manufacturingDate = eeprom.manufacturingDate;
    }
    if (cable.vendorOui == 0)
    {
        cable.vendorOui = eeprom.vendorOui;
    }
    // The hardware revision is a package match key, and PDDR reports zero for it on every cable
    // measured, so the EEPROM is the only place it comes from today.
    if (cable.hwRevMajor == 0 && cable.hwRevMinor == 0)
    {
        cable.hwRevMajor = eeprom.hwRevMajor;
        cable.hwRevMinor = eeprom.hwRevMinor;
    }
    if (cable.identifier == CABLE_REPORT_NOT_AVAILABLE)
    {
        cable.identifier = eeprom.identifier;
    }
    if (cable.state == CABLE_REPORT_NOT_AVAILABLE)
    {
        cable.state = eeprom.state;
    }
}

/* Whether anything identifying came back.
 *
 * A cage can answer PMAOS and PDDR and still report nothing about what is in it - PDDR calls that
 * cable_type Unidentified - and every identity field then reads empty, the vendor OUI as zero. A
 * zero OUI is the absence of an answer, not another vendor's, so without this the OUI fallback
 * reads an unidentified module as a third party cable.
 */
static bool cableIdentityRead(const CableInfo& cable)
{
    return !cable.partNumber.empty() || !cable.vendorName.empty() || !cable.serialNumber.empty() ||
           cable.vendorOui != 0;
}

void CableFwManager::queryCable(mfile* mf, CableInfo& cable)
{
    // Every read below is attempted whatever the ones before it returned, so a cable shows all
    // that could be read about it, and each one that failed says so in the trace.
    u_int8_t operStatus = 0;
    bool pmaosRead = readCableOperStatus(mf, cable.localIndex, operStatus) == ME_OK;

    if (pmaosRead)
    {
        cable.operStatus = operStatus;
    }
    else
    {
        FWMANAGER_LOG_DEBUG("Cable %u: PMAOS read failed", cable.globalPort);
    }

    // PDDR is where the firmware republishes the EEPROM, and it is the source every field mlxlink
    // prints comes from, whether a cable is plugged included, so the two tools agree. It is
    // addressed by local port; a cage the PLLP sweep could not map has no PDDR, and PMAOS decides
    // for it instead.
    string portDevName;
    u_int32_t localPort = 0;
    bool mapped = cableLocalPort(cable, portDevName, localPort);
    // PDDR and MFCDR go to the ASIC carrying the local port, which need not be the owner.
    mfile* portMf = mapped ? deviceHandle(portDevName) : mf;
    if (portMf == NULL)
    {
        mapped = false;
        portMf = mf;
    }
    else if (mapped && portDevName != cable.asicDevName)
    {
        FWMANAGER_LOG_DEBUG("Cable %u: owned by %s, its first sub-port is local port %u on %s", cable.globalPort,
                            cable.asicDevName.c_str(), localPort, portDevName.c_str());
    }
    bool pddrRead = mapped && readCableModuleInfo(portMf, localPort, cable);

    if (pddrRead)
    {
        if (!cable.isPlugged)
        {
            if (pmaosRead && operStatus != CABLE_OPER_STATUS_UNPLUGGED)
            {
                FWMANAGER_LOG_DEBUG("Cable %u: PDDR reports no cable while PMAOS oper_status is %d; PDDR decides",
                                    cable.globalPort, (int)operStatus);
            }
            return;
        }
    }
    else
    {
        FWMANAGER_LOG_DEBUG("Cable %u: %s, so PMAOS decides whether it is plugged", cable.globalPort,
                            mapped ? "PDDR read failed" : "no local port maps to this cage");
        // A cage nothing answered for is unreadable, not empty.
        cable.isPlugged = !pmaosRead || operStatus != CABLE_OPER_STATUS_UNPLUGGED;
        if (!cable.isPlugged)
        {
            return;
        }
    }

    if (pddrRead)
    {
        // The firmware does not fill every field of the page - the hardware revision reads zero
        // on every cable measured - so anything it left empty is read off the EEPROM itself.
        fillIdentityGapsFromEeprom(mf, cable);
    }
    else if (!readCableIdentity(mf, cable))
    {
        FWMANAGER_LOG_DEBUG("Cable %u: EEPROM read failed, its identity is unknown", cable.globalPort);
    }
    cable.isReadable = cableIdentityRead(cable);

    // MFCDR answers this directly where the firmware carries it; the OUI list is what is left
    // when it does not. A fake cable can copy an NVIDIA OUI, so where the firmware could have
    // answered and did not, the cable is unreadable rather than judged by its OUI.
    u_int8_t vendorStatus = readCableVendorStatus(portMf, mapped, localPort);
    cable.vendorStatus = vendorStatus;
    if (vendorStatus == CABLE_VENDOR_STATUS_READ_FAILED)
    {
        cable.isNvidia = false;
    }
    else if (vendorStatus != CABLE_VENDOR_STATUS_UNKNOWN)
    {
        cable.isNvidia = (vendorStatus == CABLE_VENDOR_STATUS_NVIDIA);
    }
    else
    {
        cable.isNvidia = (cable.vendorOui == CABLE_NVIDIA_OUI) || (cable.vendorOui == CABLE_NVIDIA_OUI_MELLANOX);
    }

    if (readCableFwProperties(mf, cable))
    {
        // A cable that implements neither firmware-update procedure reports protocol 0.
        cable.isBurnable = (cable.managementInterfaceProtocol != 0);
    }

    if (!cable.isReadable)
    {
        // Switch FW reports a cage it cannot read the module in as plugged_with_error, which is
        // what mlxlink warns about; any other unreadable cable is named for what the tool saw. A
        // link state would read as N/A here and look like an empty cage.
        cable.linkState = (pmaosRead && operStatus == CABLE_OPER_STATUS_PLUGGED_WITH_ERROR) ?
                            CABLE_STATE_PLUGGED_WITH_ERROR :
                            CABLE_STATE_UNREADABLE;
        return;
    }
    cable.linkState = readCableLinkStateText(cable);
}

bool CableFwManager::readCableIdentity(mfile* mf, CableInfo& cable)
{
    u_int8_t lower[CABLE_EEPROM_MODULE_STATE_OFFSET + 1];
    u_int8_t page0[CABLE_EEPROM_PAGE0_UPPER_SIZE];

    // Page 0 lower carries the identifier, the flat-memory bit and the module state, and every
    // cable implements it.
    if (readCableEeprom(mf, cable.localIndex, 0, 0, sizeof(lower), lower) != ME_OK)
    {
        return false;
    }
    u_int8_t identifier = lower[0];
    bool isCmis = isCmisIdentifier(identifier);
    bool isFlatMem = EXTRACT(lower[CABLE_EEPROM_FLAT_MEM_OFFSET], CABLE_EEPROM_FLAT_MEM_BIT, 1) != 0;

    cable.identifier = cableIdentifierName(identifier);
    // The CMIS module state is what mlxlink shows as "Module State". SFF-8636 has no equivalent.
    if (isCmis)
    {
        u_int8_t moduleState = (u_int8_t)EXTRACT(lower[CABLE_EEPROM_MODULE_STATE_OFFSET], CABLE_EEPROM_MODULE_STATE_BIT,
                                                 CABLE_EEPROM_MODULE_STATE_WIDTH);
        cable.state = cableModuleStateName(moduleState);
    }
    else
    {
        cable.state = CABLE_REPORT_NOT_AVAILABLE;
    }
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
    // Six ASCII digits, year first. Rendered the way mlxlink does, which puts the day first.
    string date = trimmedEepromText(&page0[layout.dateCode - CABLE_EEPROM_PAGE0_UPPER_OFFSET], CABLE_EEPROM_DATE_LEN);
    if (date.size() == CABLE_EEPROM_DATE_LEN)
    {
        cable.manufacturingDate = date.substr(4, 2) + "_" + date.substr(2, 2) + "_" + date.substr(0, 2);
    }

    // The hardware revision lives on page 1, which a flat-memory cable does not implement. MCIA
    // answers such a read with page 0 and a status of 0, so only the flat-memory bit catches it -
    // and the firmware has no revision to report either, so there is nothing to fall back on.
    if (isCmis && !isFlatMem)
    {
        u_int8_t hwRev[2] = {0, 0};
        if (readCableEeprom(mf, cable.localIndex, CABLE_EEPROM_CMIS_HW_REV_PAGE, CABLE_EEPROM_CMIS_HW_REV_OFFSET,
                            sizeof(hwRev), hwRev) == ME_OK)
        {
            cable.hwRevMajor = hwRev[0];
            cable.hwRevMinor = hwRev[1];
        }
    }
    FWMANAGER_LOG_DEBUG("Cable %u: %s %s pn %s sn %s rev %s oui 0x%06x hw %d.%d date %s flat_mem %d", cable.globalPort,
                        cable.identifier.c_str(), cable.state.c_str(), cable.partNumber.c_str(),
                        cable.serialNumber.c_str(), cable.vendorRev.c_str(), cable.vendorOui, (int)cable.hwRevMajor,
                        (int)cable.hwRevMinor, cable.manufacturingDate.c_str(), (int)isFlatMem);
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
        FWMANAGER_LOG_DEBUG("MCQI cable %u: component discovery failed, %s; its firmware versions are unknown",
                            cable.globalPort, (const char*)fwComps.getLastErrMsg());
        return false;
    }
    memset(&properties, 0, sizeof(properties));
    if (!fwComps.GetComponentLinkxProperties(FwComponent::COMPID_LINKX, &properties))
    {
        FWMANAGER_LOG_DEBUG("MCQI cable %u: LinkX properties read failed, %s; its firmware versions are unknown",
                            cable.globalPort, (const char*)fwComps.getLastErrMsg());
        return false;
    }

    cable.fwImageA.major = properties.image_a_major;
    cable.fwImageA.minor = properties.image_a_minor;
    cable.fwImageA.subminor = properties.image_a_subminor;
    cable.fwImageB.major = properties.image_b_major;
    cable.fwImageB.minor = properties.image_b_minor;
    cable.fwImageB.subminor = properties.image_b_subminor;
    // Bit 0 of the status bitmap says image A is running, bit 4 says image B is, and flint reads
    // it the same way. Neither set means no image is running, which is not the same as A.
    bool runsA = EXTRACT(properties.fw_image_status_bitmap, CABLE_FW_STATUS_BIT_A_RUNNING, 1) != 0;
    bool runsB = EXTRACT(properties.fw_image_status_bitmap, CABLE_FW_STATUS_BIT_B_RUNNING, 1) != 0;

    cable.runningSlot = runsB ? CABLE_IMAGE_SLOT_B : CABLE_IMAGE_SLOT_A;
    cable.isRunningImage = runsA || runsB;
    cable.managementInterfaceProtocol = properties.management_interface_protocol;
    cable.activationType = properties.activation_type;
    cable.fwRead = true;
    FWMANAGER_LOG_DEBUG("MCQI cable %u: wire index %u, A %d.%d.%d, B %d.%d.%d, status bitmap 0x%x, info bitmap 0x%x, "
                        "protocol %d, activation %d",
                        cable.globalPort, cableMccIndex(cable.localIndex), (int)cable.fwImageA.major,
                        (int)cable.fwImageA.minor, (int)cable.fwImageA.subminor, (int)cable.fwImageB.major,
                        (int)cable.fwImageB.minor, (int)cable.fwImageB.subminor,
                        (unsigned)properties.fw_image_status_bitmap, (unsigned)properties.fw_image_info_bitmap,
                        (int)cable.managementInterfaceProtocol, (int)cable.activationType);
    return true;
}

int CableFwManager::buildUpdatePlan()
{
    map<string, vector<u_int8_t> > contents;
    int rc = MLX_FWM_SUCCESS;

    // Everything below reads a file the user supplied, so a malformed package must come back as
    // an error code rather than as an exception escaping into the caller.
    try
    {
        rc = loadPackage(contents);
        if (rc == MLX_FWM_SUCCESS)
        {
            rc = decideCableActions();
            // Every cable carries an action from here on. Before it they all carry the default, and
            // a table of them reads as a decision the tool never made.
            _planned = (rc == MLX_FWM_SUCCESS);
        }
        if (rc == MLX_FWM_SUCCESS)
        {
            rc = groupUpdatePlan(contents);
        }
    }
    catch (const std::exception& e)
    {
        _errMsg = "Failed to read " + _cmdParams.cable_package + ": " + e.what();
        return ERR_CODE_FILE_PARSE_FAILED;
    }
    return rc;
}

/* A scalar the metadata may write quoted or bare, "1" or 1, as text. */
static string yamlScalarText(const fkyaml::node& value)
{
    if (value.is_string())
    {
        return value.get_value<std::string>();
    }
    if (value.is_integer())
    {
        return int_to_string((int)value.get_value<int64_t>());
    }
    throw std::runtime_error("holds a value that is neither text nor a number");
}

/* The first of the spellings an entry carries, so the IA's and the NVIDIA release's both read. */
static bool yamlField(const fkyaml::node& entry, const char* key, const char* altKey, string& value)
{
    if (entry.contains(key))
    {
        value = yamlScalarText(entry.at(key));
        return true;
    }
    if (altKey != NULL && entry.contains(altKey))
    {
        value = yamlScalarText(entry.at(altKey));
        return true;
    }
    return false;
}

/* The folder a package file sits in, without its parents, which is the part number a package
 * keeps each cable's files under. Empty for a file at the top of the package.
 */
static string packageFolderName(const string& entryName)
{
    string folder = archiveDirectory(entryName);

    if (folder.empty())
    {
        return folder;
    }
    folder.resize(folder.size() - 1); // archiveDirectory keeps the separator
    size_t parent = folder.find_last_of('/');
    return (parent == string::npos) ? folder : folder.substr(parent + 1);
}

/* One metadata entry, validated against the package files around it. An entry that does not parse
 * comes back invalid with the reason, rather than as an exception.
 */
static FwPackageEntry
  parseMetadataNode(const string& name, const fkyaml::node& node, const map<string, vector<u_int8_t> >& contents)
{
    static const char* const knownKeys[] = {
      CABLE_YAML_KEY_VENDOR_NAME,     CABLE_YAML_KEY_VENDOR_PN,     CABLE_YAML_KEY_VENDOR_OUI,
      CABLE_YAML_KEY_VENDOR_REV,      CABLE_YAML_KEY_VENDOR_SN,     CABLE_YAML_KEY_HW_MAJOR,
      CABLE_YAML_KEY_HW_MAJOR_NVIDIA, CABLE_YAML_KEY_HW_MINOR,      CABLE_YAML_KEY_ACTIVE_FW,
      CABLE_YAML_KEY_LOAD_NAME,       CABLE_YAML_KEY_LOAD_VERSION,  CABLE_YAML_KEY_LOAD_VERSION_NVIDIA,
      CABLE_YAML_KEY_SHA256,          CABLE_YAML_KEY_SHA256_NVIDIA, CABLE_YAML_KEY_SHA512,
      CABLE_YAML_KEY_SHA512_NVIDIA};
    FwPackageEntry entry;
    entry.metadataPath = name;
    // An entry that does not parse is recorded against itself and the rest of the package is
    // still usable: one bad metadata file must not cost the user the whole maintenance window.
    try
    {
        if (!node.is_mapping())
        {
            throw std::runtime_error("is not a set of key: value pairs");
        }
        // The IA has hosts ignore what they do not compare, so a vendor can add keys; the trace
        // says which, since a key spelled wrongly reads the same way.
        for (fkyaml::node::const_iterator item = node.begin(); item != node.end(); ++item)
        {
            if (!item.key().is_string())
            {
                continue;
            }
            string key = item.key().get_value<std::string>();
            bool known = false;
            for (size_t i = 0; i < sizeof(knownKeys) / sizeof(knownKeys[0]); i++)
            {
                known = known || key == knownKeys[i];
            }
            if (!known)
            {
                FWMANAGER_LOG_DEBUG("%s: ignoring %s, which the tool does not match on", name.c_str(), key.c_str());
            }
        }

        string loadName;
        if (!yamlField(node, CABLE_YAML_KEY_VENDOR_NAME, NULL, entry.vendorName) ||
            !yamlField(node, CABLE_YAML_KEY_LOAD_NAME, NULL, loadName))
        {
            throw std::runtime_error("missing " CABLE_YAML_KEY_VENDOR_NAME " or " CABLE_YAML_KEY_LOAD_NAME);
        }
        // The metadata names its binary relative to itself, so the folder it sits in is what
        // resolves the name.
        entry.imagePath = archiveDirectory(name) + loadName;

        // A package keeps each part number in a folder of its own, so an entry that does not
        // state one - a CM or JDM entry never does - takes it from there.
        string folder = packageFolderName(name);
        if (!yamlField(node, CABLE_YAML_KEY_VENDOR_PN, NULL, entry.vendorPartNumber))
        {
            entry.vendorPartNumber = folder;
        }
        else if (!folder.empty() && !hasWildcard(entry.vendorPartNumber) &&
                 !equalsIgnoringCase(folder, entry.vendorPartNumber))
        {
            // The folder is where its image is looked up, so a mismatch means the package was
            // assembled wrongly and the pairing cannot be trusted.
            throw std::runtime_error("declares " CABLE_YAML_KEY_VENDOR_PN " " + entry.vendorPartNumber +
                                     " but sits in folder " + folder + "; the package needs fixing");
        }
        // An OUI written bare, 0x48B02D, reads back as a number; it is put back in hex rather than
        // compared as its decimal value.
        if (node.contains(CABLE_YAML_KEY_VENDOR_OUI) && node.at(CABLE_YAML_KEY_VENDOR_OUI).is_integer())
        {
            int64_t oui = node.at(CABLE_YAML_KEY_VENDOR_OUI).get_value<int64_t>();
            if (oui < 0 || oui > 0xffffff)
            {
                throw std::runtime_error("states a " CABLE_YAML_KEY_VENDOR_OUI " outside 0..0xFFFFFF");
            }
            entry.vendorOui = cableOuiText((u_int32_t)oui);
            entry.hasVendorOui = true;
        }
        else
        {
            entry.hasVendorOui = yamlField(node, CABLE_YAML_KEY_VENDOR_OUI, NULL, entry.vendorOui);
        }
        entry.hasVendorRev = yamlField(node, CABLE_YAML_KEY_VENDOR_REV, NULL, entry.vendorRev);
        entry.hasVendorSn = yamlField(node, CABLE_YAML_KEY_VENDOR_SN, NULL, entry.vendorSn);
        entry.hasHwRevMajor =
          yamlField(node, CABLE_YAML_KEY_HW_MAJOR, CABLE_YAML_KEY_HW_MAJOR_NVIDIA, entry.hwRevMajor);
        entry.hasHwRevMinor = yamlField(node, CABLE_YAML_KEY_HW_MINOR, NULL, entry.hwRevMinor);
        entry.hasActiveFwVersion = yamlField(node, CABLE_YAML_KEY_ACTIVE_FW, NULL, entry.activeFwVersion);

        map<string, vector<u_int8_t> >::const_iterator image = contents.find(entry.imagePath);
        if (image == contents.end())
        {
            throw std::runtime_error("names an image the package does not hold: " + entry.imagePath);
        }
        const vector<u_int8_t>& data = image->second;

        // The checksum is the one check that the file the metadata describes is the file that will
        // reach the cable. The IA makes it optional; when an entry carries it, it has to hold.
        string expected;
#ifndef NO_OPEN_SSL
        if (yamlField(node, CABLE_YAML_KEY_SHA256, CABLE_YAML_KEY_SHA256_NVIDIA, expected) &&
            !equalsIgnoringCase(expected, sha256Hex(data)))
        {
            throw std::runtime_error("SHA-256 mismatch for " + entry.imagePath + ": expected " + expected +
                                     ", the image hashes to " + sha256Hex(data));
        }
        if (yamlField(node, CABLE_YAML_KEY_SHA512, CABLE_YAML_KEY_SHA512_NVIDIA, expected) &&
            !equalsIgnoringCase(expected, sha512Hex(data)))
        {
            throw std::runtime_error("SHA-512 mismatch for " + entry.imagePath + ": expected " + expected +
                                     ", the image hashes to " + sha512Hex(data));
        }
#endif

        // The load version is what the extended header, the plan and the verification all go by.
        // A raw LinkX image states its own, which settles it; any other image needs the metadata to.
        string version;
        bool hasVersion = yamlField(node, CABLE_YAML_KEY_LOAD_VERSION, CABLE_YAML_KEY_LOAD_VERSION_NVIDIA, version);
        if (hasVersion && !parseCableFwVersion(version, entry.fwVersion))
        {
            throw std::runtime_error(CABLE_YAML_KEY_LOAD_VERSION " \"" + version + "\" is not major.minor.build");
        }
        static const u_int8_t linkxMagic[MAGIC_NUMBER_LENGTH] = MAGIC_PATTERN;
        if (data.size() >= sizeof(fw_pkg_file_header_t) && memcmp(&data[0], linkxMagic, MAGIC_NUMBER_LENGTH) == 0)
        {
            fw_pkg_file_header_t linkx;
            CableFwVersion own;

            memcpy(&linkx, &data[0], sizeof(linkx));
            own.major = linkx.fw_product_id;
            own.minor = linkx.package_minor;
            own.subminor = (u_int16_t)((linkx.package_subminor_msb << 8) | linkx.package_subminor_lsb);
            // A wrong major would offer the image to another cable generation under a header
            // claiming it.
            if (hasVersion && compareCableFwVersions(own, entry.fwVersion) != 0)
            {
                throw std::runtime_error(CABLE_YAML_KEY_LOAD_VERSION " " + cableFwVersionText(entry.fwVersion) +
                                         " does not match " + entry.imagePath + ", which is " +
                                         cableFwVersionText(own));
            }
            entry.fwVersion = own;
        }
        else if (!hasVersion)
        {
            throw std::runtime_error("carries no " CABLE_YAML_KEY_LOAD_VERSION
                                     ", and its image does not state a version of its own");
        }
        // The major is the LinkX product id the extended header carries, and no product is zero.
        if (entry.fwVersion.major == 0)
        {
            throw std::runtime_error("load version " + cableFwVersionText(entry.fwVersion) +
                                     " has major 0, which names no cable product");
        }
        // An extended header the package already carries goes to the device as supplied: the
        // device matches the image against it where its fields match the cable. What the tool
        // must not do is build a second header over an existing one.
        entry.hasExtendedHeader =
          hasCableExtendedHeader(data.empty() ? NULL : &data[0], (u_int32_t)data.size());
        entry.isValid = true;
    }
    catch (const std::exception& e)
    {
        entry.isValid = false;
        entry.parseError = e.what();
    }
    return entry;
}

/* One metadata file: a single entry, or a list of entries each matched on its own, as the IA allows. */
vector<FwPackageEntry> CableFwManager::parseMetadataFile(const string& name,
                                                         const vector<u_int8_t>& bytes,
                                                         const map<string, vector<u_int8_t> >& contents) const
{
    vector<FwPackageEntry> entries;

    try
    {
        fkyaml::node document = fkyaml::node::deserialize(string(bytes.begin(), bytes.end()));

        if (document.is_sequence())
        {
            for (fkyaml::node::const_iterator item = document.begin(); item != document.end(); ++item)
            {
                entries.push_back(parseMetadataNode(name, *item, contents));
            }
        }
        else
        {
            entries.push_back(parseMetadataNode(name, document, contents));
        }
    }
    catch (const std::exception& e)
    {
        FwPackageEntry entry;
        entry.metadataPath = name;
        entry.parseError = e.what();
        entries.push_back(entry);
    }
    if (entries.empty())
    {
        FwPackageEntry entry;
        entry.metadataPath = name;
        entry.parseError = "holds no entries";
        entries.push_back(entry);
    }
    return entries;
}

int CableFwManager::loadPackage(map<string, vector<u_int8_t> >& contents)
{
#ifdef NO_OPEN_SSL
    emitProgress("-W- This tool was built without OpenSSL, so the package checksums are not verified\n");
#endif
    u_int32_t rejected = 0;

    if (mft_utils::IsDirectory(_cmdParams.cable_package))
    {
        readPackageDirectory(_cmdParams.cable_package, "", contents, 0);
    }
    else
    {
        readPackageFile(_cmdParams.cable_package, contents);
    }

    for (map<string, vector<u_int8_t> >::const_iterator file = contents.begin(); file != contents.end(); ++file)
    {
        const string& name = file->first;
        if (!hasSuffix(lowered(name), CABLE_METADATA_SUFFIX))
        {
            continue;
        }

        vector<FwPackageEntry> entries = parseMetadataFile(name, file->second, contents);
        for (size_t i = 0; i < entries.size(); i++)
        {
            if (!entries[i].isValid)
            {
                rejected++;
            }
            _packages.push_back(entries[i]);
        }
    }

    if (rejected > 0)
    {
        emitProgress("-W- Rejected " + int_to_string((int)rejected) + " unusable metadata entr(ies) in " +
                     _cmdParams.cable_package + "\n");
        // Which file and why is in the packages table of the report, a line per file.
        for (size_t i = 0; i < _packages.size(); i++)
        {
            if (!_packages[i].isValid)
            {
                FWMANAGER_LOG_DEBUG("Rejected %s: %s", _packages[i].metadataPath.c_str(),
                                    _packages[i].parseError.c_str());
            }
        }
    }

    u_int32_t usable = 0;
    for (size_t i = 0; i < _packages.size(); i++)
    {
        if (_packages[i].isValid)
        {
            usable++;
        }
    }
    if (usable == 0)
    {
        _errMsg = "No usable firmware metadata was found in " + _cmdParams.cable_package;
        return ERR_CODE_IMG_NOT_FOUND;
    }
    emitProgress("-I- Read " + int_to_string((int)usable) + " firmware image(s) from " + _cmdParams.cable_package +
                 "\n");
    return MLX_FWM_SUCCESS;
}

int CableFwManager::decideCableActions()
{
    for (size_t i = 0; i < _cables.size(); i++)
    {
        CableInfo& cable = _cables[i];

        // Phase 1 already ruled on the modules it could not attribute to an ASIC, and nothing
        // here has been able to learn anything further about one.
        if (cable.action == CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED)
        {
            continue;
        }
        if (!cable.isPlugged)
        {
            cable.action = CABLE_ACTION_SKIP_NOT_PLUGGED;
            continue;
        }
        // A cage that answered PMAOS but whose identity did not read is not a third party cable -
        // nothing was learned about it either way.
        //
        // A verdict from MFCDR is checked first, because the firmware answers for the cage rather
        // than from the EEPROM: a counterfeit that presents no identity at all is still a
        // counterfeit, and reporting it as merely unreadable buries the one thing worth knowing.
        if (cable.vendorStatus == CABLE_VENDOR_STATUS_FAKE || cable.vendorStatus == CABLE_VENDOR_STATUS_NON_NVIDIA)
        {
            // Both are one row in the report. Which of the two the firmware said is worth being
            // able to look up afterwards, and this is the only place it is recorded.
            FWMANAGER_LOG_DEBUG(
              "Cable %u: MFCDR reports %s", cable.globalPort,
              (cable.vendorStatus == CABLE_VENDOR_STATUS_FAKE) ? "a fake cable" : "a non-NVIDIA cable");
            cable.action = CABLE_ACTION_SKIP_3RD_PARTY;
            continue;
        }
        if (!cable.isReadable)
        {
            cable.action = CABLE_ACTION_SKIP_UNREADABLE;
            continue;
        }
        if (cable.vendorStatus == CABLE_VENDOR_STATUS_READ_FAILED)
        {
            FWMANAGER_LOG_DEBUG("Cable %u: MFCDR did not answer, so whether it is genuine is unknown",
                                cable.globalPort);
            cable.action = CABLE_ACTION_SKIP_UNREADABLE;
            continue;
        }
        // Left to the OUI list, which is all there is when the firmware gave no verdict.
        if (!cable.isNvidia)
        {
            FWMANAGER_LOG_DEBUG("Cable %u: MFCDR gave no verdict and vendor OUI 0x%06x is not an NVIDIA block",
                                cable.globalPort, cable.vendorOui);
            cable.action = CABLE_ACTION_SKIP_3RD_PARTY;
            continue;
        }
        // Without MCQI nothing is known about its firmware, which is not the same as a cable that
        // cannot be updated.
        if (!cable.fwRead)
        {
            cable.action = CABLE_ACTION_SKIP_UNREADABLE;
            continue;
        }
        if (!cable.isBurnable)
        {
            cable.action = CABLE_ACTION_SKIP_NOT_BURNABLE;
            continue;
        }

        // Several entries can match one cable, typically loads of different versions for the same
        // part number. The IA leaves the choice to the host: the highest load version is taken,
        // and between equal versions the first entry, in package order.
        const FwPackageEntry* match = NULL;
        u_int32_t candidates = 0;
        for (size_t j = 0; j < _packages.size(); j++)
        {
            if (!_packages[j].isValid || !metadataMatchesCable(_packages[j], cable))
            {
                continue;
            }
            candidates++;
            FWMANAGER_LOG_DEBUG("Cable %u: %s matches, load %s", cable.globalPort, _packages[j].metadataPath.c_str(),
                                cableFwVersionText(_packages[j].fwVersion).c_str());
            if (match == NULL || compareCableFwVersions(_packages[j].fwVersion, match->fwVersion) > 0)
            {
                match = &_packages[j];
            }
        }
        if (candidates > 1)
        {
            FWMANAGER_LOG_DEBUG("Cable %u: %u entries match; took %s, load %s, the highest version", cable.globalPort,
                                candidates, match->metadataPath.c_str(), cableFwVersionText(match->fwVersion).c_str());
        }

        if (match == NULL)
        {
            cable.action = CABLE_ACTION_SKIP_NO_FW_FILE;
            continue;
        }

        const CableFwVersion& running = (cable.runningSlot == CABLE_IMAGE_SLOT_B) ? cable.fwImageB : cable.fwImageA;
        if (compareCableFwVersions(match->fwVersion, running) == 0)
        {
            cable.action = CABLE_ACTION_SKIP_CURRENT;
            continue;
        }
        cable.action = CABLE_ACTION_UPDATE;
        // The update always goes into the slot the cable is not running from.
        cable.targetSlot = (cable.runningSlot == CABLE_IMAGE_SLOT_A) ? CABLE_IMAGE_SLOT_B : CABLE_IMAGE_SLOT_A;
        cable.targetVersion = match->fwVersion;
        cable.packageImagePath = match->imagePath;
        cable.packageEntryIndex = (int)(match - &_packages[0]);
        // An older target still goes ahead; it is flagged rather than refused.
        cable.isDowngrade = compareCableFwVersions(match->fwVersion, running) < 0;
    }
    return MLX_FWM_SUCCESS;
}

const FwPackageEntry* CableFwManager::packageEntryFor(const string& imagePath) const
{
    for (size_t i = 0; i < _packages.size(); i++)
    {
        if (_packages[i].isValid && _packages[i].imagePath == imagePath)
        {
            return &_packages[i];
        }
    }
    return NULL;
}

const FwPackageEntry* CableFwManager::matchedEntryFor(const CableInfo& cable) const
{
    if (cable.packageEntryIndex < 0 || (size_t)cable.packageEntryIndex >= _packages.size())
    {
        return NULL;
    }
    return &_packages[cable.packageEntryIndex];
}

int CableFwManager::groupUpdatePlan(const map<string, vector<u_int8_t> >& contents)
{
    map<string, size_t> groupIndex;
    // Whether every cable one image reaches on one ASIC can be given an extended header, keyed the
    // way an unwrapped burn reaches them: by ASIC and image.
    //
    // An image carrying no header is matched on its product id alone, so the burn reaches every
    // cable of that product id the ASIC owns - a cable the plan skipped was burned three times
    // that way on a populated chassis. A header narrows it to the part number its metadata names.
    // Once an entry that cannot be given one is in the burn, the unwrapped image reaches all the
    // others regardless, so the whole set goes unwrapped rather than wrapping part of it for
    // nothing.
    map<string, bool> wrappable;

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].action != CABLE_ACTION_UPDATE)
        {
            continue;
        }
        const FwPackageEntry* entry = matchedEntryFor(_cables[i]);
        // A package that ships its image already wrapped put that header there deliberately, and
        // the image goes to the device as supplied.
        bool canWrap = entry != NULL && !entry->hasExtendedHeader && cableExtHeaderKey(*entry).isComplete();
        string reach = _cables[i].asicDevName + '\n' + _cables[i].packageImagePath;
        map<string, bool>::iterator known = wrappable.find(reach);

        if (known == wrappable.end())
        {
            wrappable[reach] = canWrap;
        }
        else if (!canWrap)
        {
            known->second = false;
        }
    }

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].action != CABLE_ACTION_UPDATE)
        {
            continue;
        }
        const FwPackageEntry* entry = matchedEntryFor(_cables[i]);
        string reach = _cables[i].asicDevName + '\n' + _cables[i].packageImagePath;
        bool wrap = entry != NULL && wrappable[reach];
        CableExtHeaderKey header;

        if (wrap)
        {
            header = cableExtHeaderKey(*entry);
        }
        // One burn carries one image through one ASIC, and an ASIC cannot address another ASIC's
        // cables, so that much of the grouping is forced by the transport rather than chosen. A
        // wrapped image splits the set further when two metadata entries name the same binary,
        // because each entry gets a header of its own.
        string key = reach + (wrap ? '\n' + header.groupKey() : "");
        map<string, size_t>::iterator existing = groupIndex.find(key);
        if (existing == groupIndex.end())
        {
            CablePlanEntry group;
            group.asicDevName = _cables[i].asicDevName;
            group.asicGa = _cables[i].asicGa;
            group.packageImagePath = _cables[i].packageImagePath;
            group.fwVersion = _cables[i].targetVersion;
            group.isWrapped = wrap;
            group.header = header;
            group.imageHasOwnHeader = entry != NULL && entry->hasExtendedHeader;
            groupIndex[key] = _plan.size();
            _plan.push_back(group);
            existing = groupIndex.find(key);
        }
        _plan[existing->second].cableIndices.push_back((u_int32_t)i);
    }

    if (_plan.empty())
    {
        // Name which of the two reasons emptied the plan, because "no update" reads as a clean
        // bill of health and a package that matches nothing is not one.
        u_int32_t current = 0;
        u_int32_t unmatched = 0;

        for (size_t i = 0; i < _cables.size(); i++)
        {
            if (_cables[i].action == CABLE_ACTION_SKIP_CURRENT)
            {
                current++;
            }
            else if (_cables[i].action == CABLE_ACTION_SKIP_NO_FW_FILE)
            {
                unmatched++;
            }
        }
        if (current > 0)
        {
            emitProgress("-I- " + int_to_string((int)current) + " cable(s) already run the version the package offers" +
                         ((unmatched > 0) ? " and " + int_to_string((int)unmatched) + " match no image in it\n" : "\n"));
        }
        else if (unmatched > 0)
        {
            emitProgress("-W- No cable in the system matches any image in " + _cmdParams.cable_package + "\n");
        }
        else
        {
            emitProgress("-I- No cable in the system is eligible for a firmware update\n");
        }
        return MLX_FWM_SUCCESS;
    }

    for (size_t i = 0; i < _plan.size(); i++)
    {
        map<string, vector<u_int8_t> >::const_iterator image = contents.find(_plan[i].packageImagePath);
        if (image == contents.end())
        {
            _errMsg = "The package no longer holds " + _plan[i].packageImagePath;
            return ERR_CODE_IMG_NOT_FOUND;
        }
        if (packageEntryFor(_plan[i].packageImagePath) == NULL)
        {
            _errMsg = "No metadata describes " + _plan[i].packageImagePath;
            return ERR_CODE_IMG_NOT_FOUND;
        }
        vector<u_int8_t> wrapped;

        if (_plan[i].isWrapped)
        {
            wrapped = withExtendedHeader(_plan[i].header, image->second);
        }
        const vector<u_int8_t>& payload = _plan[i].isWrapped ? wrapped : image->second;

        _plan[i].burnImage.reserve(CABLE_BURN_IMAGE_PREFIX_SIZE + payload.size());
        _plan[i].burnImage.assign(CABLE_BURN_IMAGE_PREFIX_SIZE, 0xff);
        _plan[i].burnImage.insert(_plan[i].burnImage.end(), payload.begin(), payload.end());
        FWMANAGER_LOG_DEBUG("Burn image for %s: %u byte(s), %s", _plan[i].packageImagePath.c_str(),
                            (unsigned)_plan[i].burnImage.size(), planEntryHeaderText(_plan[i]).c_str());
        if (_plan[i].isWrapped)
        {
            FWMANAGER_LOG_DEBUG("Extended header for %s: %s", _plan[i].packageImagePath.c_str(),
                                extendedHeaderHex(wrapped).c_str());
        }
    }

    u_int32_t cables = 0;
    for (size_t i = 0; i < _plan.size(); i++)
    {
        cables += (u_int32_t)_plan[i].cableIndices.size();
    }
    emitProgress("-I- Planned " + int_to_string((int)cables) + " cable update(s) in " +
                 int_to_string((int)_plan.size()) + " group(s)\n");
    return MLX_FWM_SUCCESS;
}

void CableFwManager::emitProgress(const string& text)
{
    // Guarded rather than required: losing a progress line is a defect, but faulting in the middle
    // of a burn costs a switch reboot.
    if (_printer == NULL)
    {
        return;
    }
    // A burn that stopped mid-stage leaves its progress line unterminated.
    if (_progressLineOpen)
    {
        _printer("\n");
        _progressLineOpen = false;
    }
    _printer(text.c_str());
}

bool CableFwManager::isInterrupted() const
{
    return _interrupted != NULL && _interrupted();
}

/* The burn stages a user waits on, named for what they do. The component manager reports the
 * others too (initialize, verify, lock), which pass too fast to be worth a line.
 */
static string burnStageLabel(const string& stage)
{
    if (stage.compare(0, 7, "Writing") == 0)
    {
        return "Downloading the image to the switch";
    }
    if (stage == "FSMST_DOWNSTREAM_DEVICE_TRANSFER")
    {
        return "Transferring the image to the cables";
    }
    if (stage == "FSMST_ACTIVATE")
    {
        return "Activating the cables";
    }
    return string();
}

int CableFwManager::burnProgress(int completion, const char* stage, prog_t type, void* opaque)
{
    CableFwManager* self = static_cast<CableFwManager*>(opaque);
    string label = burnStageLabel(stage != NULL ? stage : "");

    if (!label.empty() && self->_printer != NULL)
    {
        static const char* spinner[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                        "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
        char percent[8];
        string line;

        switch (type)
        {
            case PROG_WITH_PRECENTAGE:
                snprintf(percent, sizeof(percent), "%3d%%", completion);
                line = "\r      " + label + " - " + percent;
                break;

            case PROG_WITHOUT_PRECENTAGE:
                line = "\r      " + label + " - " +
                       spinner[self->_progressSpinner++ % (int)(sizeof(spinner) / sizeof(spinner[0]))];
                break;

            case PROG_OK:
                line = "\r      " + label + " - OK     \n";
                break;

            default:
                break;
        }
        if (!line.empty())
        {
            self->_printer(line.c_str());
            self->_progressLineOpen = (type != PROG_OK);
        }
    }
    // Non-zero makes the component manager stop, and its destructor then cancels the update and
    // releases the handle - what flint does on Ctrl-C, whatever the stage.
    return self->isInterrupted() ? 1 : 0;
}

/* What the user is told before the first byte reaches a cable.
 *
 * A fleet burn takes minutes and a stalled one costs a switch reboot, so the one thing that has to
 * be on the terminal while there is still time to stop it is which cables are about to change and
 * to what. Which file each change comes from goes to the debug trace instead: it is one file for a
 * whole group, and the report names it either way.
 */
void CableFwManager::announceUpdatePlan()
{
    std::ostringstream text;
    u_int32_t cables = 0;

    for (size_t i = 0; i < _plan.size(); i++)
    {
        cables += (u_int32_t)_plan[i].cableIndices.size();
    }
    text << "-I- Updating " << cables << " cable(s):\n";
    for (size_t i = 0; i < _plan.size(); i++)
    {
        for (size_t j = 0; j < _plan[i].cableIndices.size(); j++)
        {
            const CableInfo& cable = _cables[_plan[i].cableIndices[j]];
            const CableFwVersion& running = (cable.runningSlot == CABLE_IMAGE_SLOT_B) ? cable.fwImageB : cable.fwImageA;
            // A cable executing neither image has no version to change from, and runningSlot reads
            // as A when nothing is running - so the slot would otherwise be reported as the one in
            // use. Zeroes from an unread MCQI render as a real 00.00.0000 for the same reason.
            bool showRunning = cable.fwRead && cable.isRunningImage;

            text << "      Port " << std::left << std::setw(6) << cable.globalPort << std::setw(22)
                 << clamped(orNotAvailable(cable.partNumber), 22) << std::setw(14)
                 << (showRunning ? cableFwVersionText(running) : string(CABLE_REPORT_NOT_AVAILABLE)) << "-> "
                 << cableFwVersionText(cable.targetVersion) << (cable.isDowngrade ? "  (downgrade)" : "") << "\n";
        }
        if (!_plan[i].isWrapped && !_plan[i].imageHasOwnHeader)
        {
            // Left in the trace rather than on the console: it is the first thing to check if a
            // cable outside this plan turns out to have been burned.
            FWMANAGER_LOG_DEBUG("%s carries no extended header, so the device matches it on the product id alone - a "
                                "cable outside this plan being burned would be why",
                                _plan[i].packageImagePath.c_str());
        }
    }
    emitProgress(text.str());
}

int CableFwManager::downloadAndActivate()
{
    // The MCCE capability is a precondition of burning, not of running.
    if (_plan.empty())
    {
        return MLX_FWM_SUCCESS;
    }
    int rc = checkNoStopOnErrorSupport();

    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }
    announceUpdatePlan();

    for (size_t i = 0; i < _plan.size(); i++)
    {
        if (isInterrupted())
        {
            _errMsg =
              "Interrupted by the user; " + int_to_string((int)(_plan.size() - i)) + " group(s) were not started";
            return ERR_CODE_INTERRUPTED;
        }
        size_t firstResult = _results.size();
        for (size_t j = 0; j < _plan[i].cableIndices.size(); j++)
        {
            const CableInfo& cable = _cables[_plan[i].cableIndices[j]];
            CableUpdateResult result;

            result.globalIndex = cable.globalIndex;
            result.globalPort = cable.globalPort;
            result.localIndex = cable.localIndex;
            result.asicGa = cable.asicGa;
            result.asicDevName = cable.asicDevName;
            result.stateBefore = cable.linkState;
            result.status = "not attempted";
            _results.push_back(result);
        }
        string groupOfTotal = int_to_string((int)(i + 1)) + " of " + int_to_string((int)_plan.size());

        // The stages below it show their own progress.
        emitProgress("-I- Updating group " + groupOfTotal + " on " + _plan[i].asicDevName + "\n");
        FWMANAGER_LOG_DEBUG("Starting auto update on %s for group %s: %s, %u byte(s), expecting %u cable(s) to update, "
                            "%s",
                            _plan[i].asicDevName.c_str(), groupOfTotal.c_str(), _plan[i].packageImagePath.c_str(),
                            (unsigned)_plan[i].burnImage.size(), (unsigned)_plan[i].cableIndices.size(),
                            planEntryHeaderText(_plan[i]).c_str());
        burnPlanEntry(_plan[i], firstResult);
        if (isInterrupted())
        {
            _errMsg = "Interrupted by the user; the update of group " + groupOfTotal + " was cancelled";
            if (i + 1 < _plan.size())
            {
                _errMsg += " and " + int_to_string((int)(_plan.size() - i - 1)) + " group(s) were not started";
            }
            return ERR_CODE_INTERRUPTED;
        }

        u_int32_t burned = 0;

        for (size_t r = firstResult; r < _results.size(); r++)
        {
            burned += _results[r].burnAccepted ? 1 : 0;
        }
        // What the device accepted, not the verdict: phase 5 can still fail a cable that came back
        // in a worse state than it started.
        emitProgress("-I- Group " + groupOfTotal + " finished: " + int_to_string((int)burned) + " of " +
                     int_to_string((int)_plan[i].cableIndices.size()) + " cable(s) burned\n");
    }

    // The verdict is phase 5's: a cable can still be confirmed there, and a cable that came back
    // in a worse state than it started fails the update even though its burn was accepted.
    return MLX_FWM_SUCCESS;
}

int CableFwManager::checkNoStopOnErrorSupport()
{
    for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = deviceHandle(asic->second.devName);
        if (mf == NULL)
        {
            _errMsg = "Failed to open " + asic->second.devName + " to check its firmware update support";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }
        bool supported = false;
        reg_access_status_t status = isRegisterValidAccordingToMcamReg(mf, REG_ID_MCCE, &supported);
        if (status != ME_OK)
        {
            _errMsg = "Failed to read MCAM from " + asic->second.devName + " to check its cable update support";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }
        if (!supported)
        {
            _errMsg = "The firmware on " + asic->second.devName +
                      " cannot report which cable failed a burn, so one bad cable would strand the rest; align the "
                      "firmware across the system before updating cables";
            return ERR_CODE_CABLE_NOT_SUPPORTED;
        }
    }
    return MLX_FWM_SUCCESS;
}

void CableFwManager::burnPlanEntry(const CablePlanEntry& group, size_t firstResult)
{
    size_t lastResult = firstResult + group.cableIndices.size();
    string errMsg;

    mfile* mf = deviceHandle(group.asicDevName);
    if (mf == NULL)
    {
        for (size_t i = firstResult; i < lastResult; i++)
        {
            _results[i].phase = "download";
            _results[i].status = "download: " + group.asicDevName + " could not be opened";
        }
        return;
    }
    string stageName;

    // The wait belongs between the transfer and the activation, and it is only there for cables
    // that need it; with none asked for, the burn runs as one transaction, the way it is shipped.
    bool separateActivation = _cmdParams.cable_activation_wait > 0;
    bool ok = runBurnStage(mf, group.burnImage, true, !separateActivation, firstResult, lastResult, errMsg, stageName);
    if (ok && separateActivation)
    {
        // In slices, so Ctrl-C does not have to wait out the whole pause.
        for (int waited = 0; waited < _cmdParams.cable_activation_wait * 10 && !isInterrupted(); waited++)
        {
            msleep(100);
        }
        if (isInterrupted())
        {
            ok = false;
            stageName = "activation";
            errMsg = "activation: interrupted by the user before it started";
        }
        else
        {
            ok = runBurnStage(mf, group.burnImage, false, true, firstResult, lastResult, errMsg, stageName);
        }
    }

    for (size_t i = firstResult; i < lastResult; i++)
    {
        if (_results[i].status == "not attempted")
        {
            // The device picks the cables itself in this mode, so a group that came back clean
            // covered everything the plan expected of it.
            _results[i].succeeded = ok;
            _results[i].burnAccepted = ok;
            _results[i].status = ok ? "burned" : errMsg;
            if (!ok)
            {
                _results[i].phase = stageName;
            }
        }
    }
    // An interrupted burn is reported once, by the caller, as the reason the run ended.
    if (!ok && !isInterrupted())
    {
        emitProgress("-E- Cable update failed on " + group.asicDevName + " for " + group.packageImagePath + ": " +
                     errMsg + "\n");
    }
}

bool CableFwManager::runBurnStage(mfile* mf,
                                  const vector<u_int8_t>& image,
                                  bool download,
                                  bool activate,
                                  size_t firstResult,
                                  size_t lastResult,
                                  string& errMsg,
                                  string& stageName)
{
    // A manager that has queried a cable keeps that cable's index and sends it on every command
    // afterwards, so the burn gets one of its own.
    FwCompsMgr fwComps(mf, FwCompsMgr::DEVICE_HCA_SWITCH, 0);
    FwComponent component;

    // With both legs in one transaction the request cannot say which of them failed; only the
    // device's own counters can, and they are read once the burn comes back.
    stageName = download ? (activate ? "burn" : "download") : "activation";
    string stage = stageName + ": ";

    fwComps.GenerateHandle();
    // No index and no range: with auto update set the device matches the image against its own
    // cables, and the plan's list is what the group is expected to cover rather than an
    // instruction. no_stop_on_error is what keeps one bad cable from stranding the rest.
    fwComps.SetIndexAndSize(0, 0, true, activate, download, 0, true);
    if (!fwComps.RefreshComponentsStatus())
    {
        errMsg = stage + string((const char*)fwComps.getLastErrMsg());
        return false;
    }
    if (!component.init(image, (u_int32_t)image.size(), FwComponent::COMPID_LINKX))
    {
        errMsg = stage + "failed to prepare the firmware image";
        return false;
    }

    // The percentages are the whole group's, one transaction for every cable in it.
    ProgressCallBackAdvSt progress;

    memset(&progress, 0, sizeof(progress));
    progress.func = &CableFwManager::burnProgress;
    progress.opaque = this;
    bool ok = fwComps.burnComponents(component, &progress);
    if (!ok && isInterrupted())
    {
        errMsg = stage + "interrupted by the user";
    }
    else if (!ok)
    {
        if (download && activate)
        {
            stageName = (fwComps.GetTransferErrorCount() > 0) ?
                          "download" :
                          ((fwComps.GetActivateErrorCount() > 0) ? "activation" : stageName);
            stage = stageName + ": ";
        }
        errMsg = stage + (const char*)fwComps.getLastErrMsg();
        if (fwComps.isSpecificError)
        {
            errMsg += " " + fwComps.getLastSpecificError();
        }
    }

    // The failure log has to be drained before the manager goes out of scope, and before anything
    // else calls SetIndexAndSize on it, which is what clears it.
    const std::vector<FwCompsMgr::burn_failure_t>& failures = fwComps.GetBurnFailures();
    u_int32_t transferFailures = fwComps.GetTransferErrorCount();
    u_int32_t named = 0;

    for (size_t i = 0; i < failures.size(); i++)
    {
        // The device reports the cable in the number the user already sees, so it is matched
        // against the label port rather than shifted.
        for (size_t j = firstResult; j < lastResult; j++)
        {
            if (cableLabelPort(_results[j].localIndex) != failures[i].module_id)
            {
                continue;
            }
            named++;
            _results[j].succeeded = false;
            _results[j].burnAccepted = false;
            _results[j].hasDeviceError = true;
            _results[j].phase = (i < transferFailures) ? "download" : "activation";
            _results[j].mccErrorCode = failures[i].mcc_error_code;
            _results[j].cdbErrorCode = failures[i].cdb_error_code;
            // Named here, while the manager that produced the code is still addressing the
            // device, the way flint names both error codes together.
            _results[j].mccErrorText = fwComps.GetMccErrorString(failures[i].mcc_error_code);
            _results[j].status =
              (i < transferFailures) ? "download: rejected by the device" : "activation: rejected by the device";
        }
    }
    // burnComponents() reports success whatever the error counts say, and the per-cable detail
    // comes from a separate MCCE read that can come back empty or name a cable outside this
    // group. Failures nobody could name leave the whole group indeterminate, never burned.
    if (fwComps.GetBurnErrorCount() > named)
    {
        if (download && activate)
        {
            // One leg clean attributes the failure to the other; errors on both cannot be split.
            if (fwComps.GetTransferErrorCount() == 0)
            {
                stageName = "activation";
            }
            else if (fwComps.GetActivateErrorCount() == 0)
            {
                stageName = "download";
            }
        }
        errMsg = stageName + ": the device reported " + int_to_string((int)fwComps.GetBurnErrorCount()) +
                 " failure(s) it could not identify";
        return false;
    }
    return ok;
}

int CableFwManager::verifyAndReport()
{
    if (_cmdParams.cable_update)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        // A self-activating cable resets, so its link drops and re-trains. Verifying before that
        // finishes reports a working cable as failed.
        if (!_results.empty() && _cmdParams.cable_verify_wait > 0)
        {
            emitProgress("-I- Waiting " + int_to_string(_cmdParams.cable_verify_wait) +
                         " second(s) for the cables to finish re-training\n");
            msleep((unsigned int)_cmdParams.cable_verify_wait * 1000);
        }
        verifyBurnedCables();
        if (!_results.empty())
        {
            _verificationSeconds = secondsSince(start);
        }
    }
    u_int32_t regressed = 0;
    u_int32_t pending = 0;

    for (size_t i = 0; i < _results.size(); i++)
    {
        if (_results[i].stateRegressed)
        {
            regressed++;
        }
        if (_results[i].pendingPowerCycle)
        {
            pending++;
        }
    }
    if (regressed > 0)
    {
        emitProgress("-W- " + int_to_string((int)regressed) + " cable(s) had not come back up after " +
                     int_to_string(_cmdParams.cable_verify_wait) +
                     "s; check with 'mstlink -d <device> --port <label port> -m' before believing it\n");
        emitProgress("-W- If the link is Active there, re-run with a larger --cable_verify_wait\n");
    }
    if (pending > 0)
    {
        // The cable runs its old image until the power cycle happens, and nothing else on the
        // console says so.
        emitProgress("-W- " + int_to_string((int)pending) +
                     " cable(s) will run the new firmware only after a host power cycle\n");
    }
    collectReportDetails();

    // The verdict is settled before the file is written, so a report that cannot be written still
    // reports the update outcome instead of replacing it with a file error.
    int verdict = MLX_FWM_SUCCESS;

    for (size_t i = 0; i < _results.size(); i++)
    {
        if (!_results[i].succeeded)
        {
            _errMsg = "One or more cables did not complete the update; see the report";
            verdict = ERR_CODE_CABLE_UPDATE_FAILED;
            break;
        }
    }
    string text = buildReport();
    string verdictMsg = _errMsg;

    if (!_cmdParams.cable_report_file_only)
    {
        emitProgress(text);
    }
    int rc = writeReport(text);

    if (rc != MLX_FWM_SUCCESS)
    {
        if (_cmdParams.cable_report_file_only)
        {
            // The file is gone, the outcome is not, so a report kept off the screen goes there
            // rather than nowhere. Announced first, or it reads as output the run meant to produce.
            emitProgress("-W- The report file could not be written, so the report follows here\n");
            emitProgress(text);
        }
        else
        {
            emitProgress("-W- The report file could not be written\n");
        }
        if (verdict == MLX_FWM_SUCCESS)
        {
            return rc;
        }
        _errMsg = verdictMsg;
        return verdict;
    }
    return verdict;
}

void CableFwManager::verifyBurnedCables()
{
    for (size_t i = 0; i < _results.size(); i++)
    {
        CableUpdateResult& result = _results[i];
        const CableInfo* cable = NULL;

        for (size_t j = 0; j < _cables.size(); j++)
        {
            if (_cables[j].globalIndex == result.globalIndex)
            {
                cable = &_cables[j];
                break;
            }
        }
        if (cable == NULL)
        {
            continue;
        }

        mfile* mf = deviceHandle(result.asicDevName);
        if (mf == NULL)
        {
            result.succeeded = false;
            if (result.burnAccepted)
            {
                result.phase = "verification";
                result.status = "verification: " + result.asicDevName + " could not be reopened";
            }
            continue;
        }
        CableInfo current = *cable;
        bool read = readCableFwProperties(mf, current);

        // A link that was carrying traffic before the update has to be carrying it after. This is
        // the thing an operator actually loses. A
        // state the register would not report is unknown rather than down.
        result.stateAfter = readCableLinkStateText(current);
        result.stateRegressed = (result.stateBefore == CABLE_LINK_STATE_ACTIVE_NAME) &&
                                (result.stateAfter != CABLE_LINK_STATE_ACTIVE_NAME) &&
                                (result.stateAfter != CABLE_REPORT_NOT_AVAILABLE);
        if (read)
        {
            result.readBack = true;
            result.fwImageA = current.fwImageA;
            result.fwImageB = current.fwImageB;
            result.runningSlot = current.runningSlot;
            result.isRunningImage = current.isRunningImage;
        }
        // Phase 5 can confirm a burn the device accepted; it can never overturn one it refused,
        // and the reason it refused is the only thing that tells the operator what to do next.
        if (!result.burnAccepted)
        {
            continue;
        }
        if (!read)
        {
            result.succeeded = false;
            result.phase = "verification";
            result.status = "verification: the cable did not answer";
            continue;
        }
        if (result.stateRegressed)
        {
            result.succeeded = false;
            result.phase = "verification";
            result.status = "link was " + orNotAvailable(result.stateBefore) + " before the update and is " +
                            orNotAvailable(result.stateAfter) + " now";
            continue;
        }
        // runningSlot reads as A when nothing is running, so without this a cable left executing
        // no image after the burn matches its own target slot and reports a successful update.
        if (!current.isRunningImage)
        {
            result.succeeded = false;
            result.phase = "verification";
            result.status = "no image is running after the update";
            continue;
        }
        const CableFwVersion& running =
          (current.runningSlot == CABLE_IMAGE_SLOT_B) ? current.fwImageB : current.fwImageA;
        if (current.runningSlot == cable->targetSlot && compareCableFwVersions(running, cable->targetVersion) == 0)
        {
            result.succeeded = true;
            result.status = "updated to " + cableFwVersionText(running);
            continue;
        }
        // A cable that activates only on a host power cycle is still running its old image here.
        // That is a pending power cycle only if the image actually reached the slot it was
        // written to; otherwise the device took nothing and said nothing.
        const CableFwVersion& target = (cable->targetSlot == CABLE_IMAGE_SLOT_B) ? current.fwImageB : current.fwImageA;
        if (cable->activationType == 0 && compareCableFwVersions(target, cable->targetVersion) == 0)
        {
            result.succeeded = true;
            result.pendingPowerCycle = true;
            result.pendingVersion = cable->targetVersion;
            result.status = "burned, pending a host power cycle to run " + cableFwVersionText(cable->targetVersion);
            continue;
        }
        result.succeeded = false;
        result.phase = "verification";
        result.status = "still running " + cableFwVersionText(running) + " after the update";
    }
}

void CableFwManager::collectReportDetails()
{
    for (AsicsByGa::iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = deviceHandle(asic->second.devName);

        if (mf == NULL)
        {
            continue;
        }
        FwCompsMgr fwComps(mf, FwCompsMgr::DEVICE_HCA_SWITCH, 0);
        vector<u_int8_t> info;
        if (fwComps.getDeviceHWInfo(FwCompsMgr::MQIS_REGISTER_DEVICE_DESCRIPTION_INFO, info) && !info.empty())
        {
            asic->second.description = deviceDescription(string((const char*)&info[0]));
        }
    }
}

string CableFwManager::buildReport()
{
    std::ostringstream report;
    u_int32_t plugged = 0;
    u_int32_t skipped = 0;
    u_int32_t succeeded = 0;
    u_int32_t failed = 0;
    u_int32_t pending = 0;

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].isPlugged)
        {
            plugged++;
        }
        if (_cables[i].action != CABLE_ACTION_UPDATE && _cables[i].action != CABLE_ACTION_UNDECIDED)
        {
            skipped++;
        }
    }
    for (size_t i = 0; i < _results.size(); i++)
    {
        if (_results[i].succeeded)
        {
            succeeded++;
        }
        else
        {
            failed++;
        }
        if (_results[i].pendingPowerCycle)
        {
            pending++;
        }
    }

    // One device line, from the first ASIC: every ASIC in a chassis carries the same description,
    // and the per-ASIC detail is what --verbose is for.
    string description = _asics.empty() ? string() : _asics.begin()->second.description;

    report << CABLE_REPORT_RULE << "\n";
    report << "PLUGGABLE MODULE FIRMWARE UPDATE REPORT\n";
    report << "Date: " << reportTimestamp() << "\n";
    report << "Device: " << orNotAvailable(description) << "\n";
    report << "Mode: " << (_cmdParams.cable_update ? "update" : (_cmdParams.cable_dry_run ? "dry run" : "query"))
           << "\n";
    report << CABLE_REPORT_RULE << "\n\n";

    if (_cmdParams.verbose)
    {
        for (AsicsByGa::const_iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
        {
            report << "ASIC " << (int)asic->first << "\n";
            report << "  Device      : " << asic->second.devName << "\n";
            report << "  FW Version  : " << orNotAvailable(asic->second.fwVersion) << "\n";
        }
        report << "\n";
    }

    report << "SUMMARY\n-------\n";
    report << "Ports scanned:     " << _cables.size() + _servicePorts.size() << "\n";
    report << "Modules found:     " << plugged << "\n";
    report << "Updates attempted: "
           << (_cmdParams.cable_update ? int_to_string((int)_results.size()) : string(CABLE_REPORT_NOT_AVAILABLE))
           << "\n";
    report << "Succeeded:         "
           << (_cmdParams.cable_update ? int_to_string((int)succeeded) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    report << "Failed:            "
           << (_cmdParams.cable_update ? int_to_string((int)failed) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    // Service ports were set aside before any cable was queried, so no table lists them; this is
    // where they are accounted for.
    string skippedText = CABLE_REPORT_NOT_AVAILABLE;

    if (_planned)
    {
        skippedText = int_to_string((int)(skipped + _servicePorts.size()));
    }
    else
    {
        // A query, or a plan that was never built, rules on no port; the service ports are set aside
        // either way.
        skippedText = int_to_string((int)_servicePorts.size());
    }
    report << "Skipped:           " << skippedText << "\n";
    report << "Needs power cycle: "
           << (_cmdParams.cable_update ? int_to_string((int)pending) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    report << "Discovery time:    " << elapsedText(_discoverySeconds) << "\n";
    report << "Update time:       " << elapsedText(_updateSeconds) << "\n";
    report << "Verification time: " << elapsedText(_verificationSeconds) << "\n\n";

    appendPackagesTable(report);
    appendDiscoveryTable(report);
    appendPlanTable(report);
    appendVerificationTable(report);
    appendErrorsTable(report);

    report << CABLE_REPORT_RULE << "\n";
    return report.str();
}

/* Two spaces, so the widest value in a column still ends clear of the next one. */
#define CABLE_REPORT_COLUMN_GAP 2

/* The width a column needs for its header and every value in it.
 *
 * Text that comes from the package or from the device has no length the tool can rely on, so a
 * fixed width would either cut it or push every column after it out of line.
 */
static int columnWidth(const string& header, const vector<string>& values)
{
    size_t width = header.size();

    for (size_t i = 0; i < values.size(); i++)
    {
        if (values[i].size() > width)
        {
            width = values[i].size();
        }
    }
    return (int)(width + CABLE_REPORT_COLUMN_GAP);
}

/* A header row and its rows, every column as wide as it needs to be. The last column is left
 * unpadded, since nothing follows it.
 */
static void
  appendSizedTable(std::ostringstream& report, const vector<string>& headers, const vector<vector<string> >& rows)
{
    vector<int> widths;

    for (size_t column = 0; column + 1 < headers.size(); column++)
    {
        vector<string> values;

        for (size_t i = 0; i < rows.size(); i++)
        {
            values.push_back(rows[i][column]);
        }
        widths.push_back(columnWidth(headers[column], values));
    }
    report << std::left;
    for (size_t column = 0; column + 1 < headers.size(); column++)
    {
        report << std::setw(widths[column]) << headers[column];
    }
    report << headers.back() << "\n";
    for (size_t i = 0; i < rows.size(); i++)
    {
        for (size_t column = 0; column + 1 < headers.size(); column++)
        {
            report << std::setw(widths[column]) << rows[i][column];
        }
        report << rows[i].back() << "\n";
    }
}

/* Every metadata file the package held, whether or not it was usable. */
void CableFwManager::appendPackagesTable(std::ostringstream& report)
{
    report << "FW UPDATE PACKAGES\n------------------\n";
    if (_packages.empty())
    {
        report << CABLE_REPORT_NOT_AVAILABLE << "\n\n";
        return;
    }
    vector<vector<string> > rows;

    for (size_t i = 0; i < _packages.size(); i++)
    {
        const FwPackageEntry& entry = _packages[i];
        string vendor = CABLE_REPORT_NOT_AVAILABLE;

        if (!entry.vendorName.empty())
        {
            vendor = entry.hasVendorOui ? entry.vendorName + " (" + entry.vendorOui + ")" : entry.vendorName;
        }
        vector<string> row;

        row.push_back(entry.imagePath.empty() ? entry.metadataPath : entry.imagePath);
        row.push_back(vendor);
        row.push_back(orNotAvailable(entry.vendorPartNumber));
        row.push_back(entry.hasVendorRev ? entry.vendorRev : string(CABLE_REPORT_NOT_AVAILABLE));
        row.push_back(entry.hasHwRevMajor ? entry.hwRevMajor : string(CABLE_REPORT_NOT_AVAILABLE));
        row.push_back(entry.hasActiveFwVersion ? entry.activeFwVersion : string(CABLE_REPORT_NOT_AVAILABLE));
        row.push_back(cableFwVersionText(entry.fwVersion));
        row.push_back(entry.isValid ? string("yes") : "no (" + entry.parseError + ")");
        rows.push_back(row);
    }
    vector<string> headers;

    headers.push_back("File");
    headers.push_back("Vendor (OUI)");
    headers.push_back("Vendor PN");
    headers.push_back("Vendor Rev");
    headers.push_back("HW Rev Major");
    headers.push_back("Active FW Match");
    headers.push_back("FW Version");
    headers.push_back("Valid");
    appendSizedTable(report, headers, rows);
    report << "\n";
}

/* The columns every per-cable table opens with. */
void CableFwManager::appendCableColumns(std::ostringstream& report, bool withAsic)
{
    report << std::left << std::setw(6) << "Port";
    if (withAsic)
    {
        report << std::setw(6) << "ASIC" << std::setw(11) << "Label Port";
    }
    report << std::setw(18) << "Vendor" << std::setw(20) << "Vendor PN" << std::setw(18) << "Vendor SN" << std::setw(17)
           << "State" << std::setw(12) << "Vendor Rev" << std::setw(14) << "HW Rev (dec)" << std::setw(14) << "FW A"
           << std::setw(14) << "FW B" << std::setw(12) << "FW Running";
}

void CableFwManager::appendCableRow(std::ostringstream& report, const CableInfo& cable, bool withAsic)
{
    // Zeroes are what an unread MCQI leaves behind, and they render as a real 00.00.0000.
    bool showFirmware = cable.isPlugged && cable.fwRead;

    report << std::left << std::setw(6) << cable.globalPort;
    if (withAsic)
    {
        // MMAM leaves local_module Reserved for exactly the ports it leaves ga Reserved, so
        // neither number means anything for those.
        bool attributed = (cable.action != CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED);

        report << std::setw(6) << (attributed ? int_to_string((int)cable.asicGa) : string(CABLE_REPORT_NOT_AVAILABLE))
               << std::setw(11)
               << (attributed ? int_to_string((int)cableLabelPort(cable.localIndex)) :
                                string(CABLE_REPORT_NOT_AVAILABLE));
    }
    report << std::setw(18) << orNotAvailable(cable.vendorName) << std::setw(20) << orNotAvailable(cable.partNumber)
           << std::setw(18) << orNotAvailable(cable.serialNumber) << std::setw(17) << orNotAvailable(cable.linkState)
           << std::setw(12) << orNotAvailable(cable.vendorRev) << std::setw(14) << cableHwRevisionText(cable)
           << std::setw(14) << (showFirmware ? cableFwVersionText(cable.fwImageA) : string(CABLE_REPORT_NOT_AVAILABLE))
           << std::setw(14) << (showFirmware ? cableFwVersionText(cable.fwImageB) : string(CABLE_REPORT_NOT_AVAILABLE))
           << std::setw(12)
           << (cable.fwRead ? cableRunningSlotText(cable.isRunningImage, cable.runningSlot) :
                              string(CABLE_REPORT_NOT_AVAILABLE));
}

/* What phase 2 found, before anything was decided or burned. */
void CableFwManager::appendDiscoveryTable(std::ostringstream& report)
{
    report << "DISCOVERY (pre-update state)\n----------------------------\n";
    if (_cables.empty())
    {
        report << CABLE_REPORT_NOT_AVAILABLE << "\n\n";
        return;
    }
    appendCableColumns(report, _cmdParams.verbose);
    report << "\n";
    for (size_t i = 0; i < _cables.size(); i++)
    {
        appendCableRow(report, _cables[i], _cmdParams.verbose);
        report << "\n";
    }
    report << "\n";
}

/* What phase 3 decided. Query mode never runs it, so there is nothing to show there. */
void CableFwManager::appendPlanTable(std::ostringstream& report)
{
    report << "FW UPDATE PLAN\n--------------\n";
    if (!_notPlannedReason.empty())
    {
        report << "Not planned: " << _notPlannedReason << "\n\n";
        return;
    }
    if (_cmdParams.cable_query || _cables.empty() || !_planned)
    {
        report << CABLE_REPORT_NOT_AVAILABLE << "\n\n";
        return;
    }
    // The image path comes from the package, so its column is sized to the paths this plan holds.
    vector<string> files;

    for (size_t i = 0; i < _cables.size(); i++)
    {
        files.push_back(orNotAvailable(_cables[i].packageImagePath));
    }
    int fileWidth = columnWidth("FW File", files);

    appendCableColumns(report, false);
    report << std::setw(14) << "Target FW" << std::setw(fileWidth) << "FW File"
           << "Action\n";
    for (size_t i = 0; i < _cables.size(); i++)
    {
        const CableInfo& cable = _cables[i];

        appendCableRow(report, cable, false);
        report << std::setw(14)
               << ((cable.action == CABLE_ACTION_UPDATE) ? cableFwVersionText(cable.targetVersion) :
                                                           string(CABLE_REPORT_NOT_AVAILABLE))
               << std::setw(fileWidth) << files[i] << cableActionName(cable.action)
               << (cable.isDowngrade ? " (downgrade)" : "") << "\n";
    }
    report << "\n";
}

/* What phase 5 read back. Only an update reaches it. */
void CableFwManager::appendVerificationTable(std::ostringstream& report)
{
    report << "VERIFICATION (post-update state)\n--------------------------------\n";
    if (!_cmdParams.cable_update || _results.empty())
    {
        report << CABLE_REPORT_NOT_AVAILABLE << "\n\n";
        return;
    }
    appendCableColumns(report, false);
    report << "Status\n";
    for (size_t i = 0; i < _results.size(); i++)
    {
        const CableUpdateResult& result = _results[i];
        CableInfo after;

        // The identity is the cable's; the firmware and the state are what phase 5 read back.
        for (size_t j = 0; j < _cables.size(); j++)
        {
            if (_cables[j].globalIndex == result.globalIndex)
            {
                after = _cables[j];
                break;
            }
        }
        after.linkState = result.stateAfter;
        after.fwImageA = result.fwImageA;
        after.fwImageB = result.fwImageB;
        after.runningSlot = result.runningSlot;
        after.isRunningImage = result.isRunningImage;
        after.fwRead = result.readBack;

        appendCableRow(report, after, false);
        report << orNotAvailable(result.status) << "\n";
    }
    report << "\n";
}

void CableFwManager::appendErrorsTable(std::ostringstream& report)
{
    vector<vector<string> > rows;

    for (size_t i = 0; i < _results.size(); i++)
    {
        if (_results[i].succeeded)
        {
            continue;
        }
        string asicError = CABLE_REPORT_NOT_AVAILABLE;
        string moduleError = CABLE_REPORT_NOT_AVAILABLE;

        // Both codes come from one MCCE record. Without one there is nothing to name, and code 0
        // reads as a clean status rather than as the absence of an answer.
        if (_results[i].hasDeviceError)
        {
            char mccText[128];

            snprintf(mccText, sizeof(mccText), "%s (0x%02x)",
                     _results[i].mccErrorText.empty() ? CABLE_REPORT_NOT_AVAILABLE : _results[i].mccErrorText.c_str(),
                     _results[i].mccErrorCode);
            asicError = mccText;
            moduleError = cdbErrorText(_results[i].cdbErrorCode);
        }
        vector<string> row;

        row.push_back(int_to_string((int)_results[i].globalPort));
        row.push_back(int_to_string((int)_results[i].asicGa));
        row.push_back(int_to_string((int)cableLabelPort(_results[i].localIndex)));
        row.push_back(orNotAvailable(_results[i].phase));
        row.push_back(asicError);
        row.push_back(moduleError);
        rows.push_back(row);
    }

    report << "ERRORS\n------\n";
    if (rows.empty())
    {
        // N/A is for a section the run never reached. An update that burned and found nothing to
        // report is a different answer, and saying so is the point of the section - as is an update
        // that stopped before its first burn, which found nothing because it tried nothing.
        if (!_notStartedReason.empty())
        {
            report << "The update did not start: " << _notStartedReason << "\n\n";
            return;
        }
        bool reached = _cmdParams.cable_update && _notPlannedReason.empty();
        report << (reached ? "No errors were found" : CABLE_REPORT_NOT_AVAILABLE) << "\n\n";
        return;
    }

    // The device answers in its own per-ASIC label port, so both numbers are always here:
    // nothing else lets an MCCE report be lined up with a cable.
    vector<string> headers;

    headers.push_back("Port");
    headers.push_back("ASIC");
    headers.push_back("Label Port");
    headers.push_back("Phase");
    headers.push_back("ASIC Error Code");
    headers.push_back("Module Error Code");
    appendSizedTable(report, headers, rows);
    report << "\n";
}

int CableFwManager::writeReport(const string& text)
{
    time_t now = time(0);
    tm* localNow = localtime(&now);
    char stamp[32];

    if (localNow == NULL || strftime(stamp, sizeof(stamp), "%Y%m%d_%H%M%S", localNow) == 0)
    {
        _errMsg = "Failed to read the current time for the report file name";
        return ERR_CODE_WRITE_FILE_FAIL;
    }

    string path = _cmdParams.cable_report_dir;
    if (!path.empty())
    {
        path += PATH_SEPARATOR;
    }
    path += "module_fw_update_report_" + string(stamp) + ".txt";

    FILE* file = fopen(path.c_str(), "w");
    if (file == NULL)
    {
        _errMsg = "Failed to open " + path + " for writing";
        return ERR_CODE_WRITE_FILE_FAIL;
    }
    bool written = fputs(text.c_str(), file) != EOF;
    // Closing is where a full disk surfaces, since it flushes what was buffered.
    written = (fclose(file) == 0) && written;
    if (!written)
    {
        _errMsg = "Failed to write " + path;
        return ERR_CODE_WRITE_FILE_FAIL;
    }
    emitProgress("-I- Report saved to " + path + "\n");
    return MLX_FWM_SUCCESS;
}
