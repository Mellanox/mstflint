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
#include <iomanip>

#include "common/bit_slice.h"
#include "common/tools_time.h"
#include "reg_access/mcam_capabilities.h"
#include "reg_access/reg_ids.h"
#include "common/package_error_codes.h"
#include <time.h>

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

CableFwManager::CableFwManager(const CmdLineParams& cmdParams, ProgressPrinter printer) :
    _cmdParams(cmdParams), _errMsg(""), _printer(printer), _planned(false)
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
        // Keep the plan's result and report anyway. A package the tool could not read is exactly
        // when its packages table is wanted: it names every metadata file it rejected and why.
        rc = buildUpdatePlan();
    }

    if (rc == MLX_FWM_SUCCESS && _cmdParams.cable_update)
    {
        // Keep the burn result and report anyway: phase 5 is what tells the user which
        // cables failed, and it is most needed exactly when phase 4 did not go cleanly.
        rc = downloadAndActivate();
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

/* PMAOS.oper_status: the cage is empty only on this one value. Every other state - including
 * initializing and plugged_with_error - is a cable that is there and may still be updated. This
 * is the same test mlxlink makes in checkPmaosDown().
 */
#define CABLE_OPER_STATUS_INITIALIZING 0
#define CABLE_OPER_STATUS_PLUGGED_ENABLED 1
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
/* CMIS page 01h bytes 130-131 are the hardware revision major and minor, and the PRM treats them
 * as numbers - but every cable measured so far writes the ASCII revision it also prints as its
 * vendor revision, "A1". Render what the vendor meant when both bytes are printable.
 */
static string cableHwRevisionText(u_int8_t major, u_int8_t minor)
{
    if (isprint(major) && isprint(minor))
    {
        string text;

        text += (char)major;
        text += (char)minor;
        return text;
    }
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
 */
static u_int8_t readCableVendorStatus(mfile* mf, u_int32_t localIndex)
{
    struct reg_access_switch_mfcdr_reg_ext mfcdr;
    bool supported = false;

    if (isRegisterValidAccordingToMcamReg(mf, REG_ID_MFCDR, &supported) != ME_OK || !supported)
    {
        return CABLE_VENDOR_STATUS_UNKNOWN;
    }
    if (isCapabilitySupportedAccordingToMcamReg(mf, MCAM_CAP_MFCDR_MODULE_AND_QUERY_TYPE, isMcamDwordSwapNeeded(mf), &supported) != ME_OK ||
        !supported)
    {
        return CABLE_VENDOR_STATUS_UNKNOWN;
    }
    memset(&mfcdr, 0, sizeof(mfcdr));
    mfcdr.query_type = 1; // module based query; local_port is ignored
    mfcdr.module = (u_int8_t)localIndex;
    reg_access_status_t status = reg_access_mfcdr(mf, REG_ACCESS_METHOD_GET, &mfcdr);
    FWMANAGER_LOG_DEBUG("MFCDR: module %u, status %d, vendor status %d", localIndex, (int)status, (int)mfcdr.status);
    if (status != ME_OK)
    {
        return CABLE_VENDOR_STATUS_UNKNOWN;
    }
    return mfcdr.status;
}

/* The metadata keys this tool reads.
 *
 * The package generator that writes these files is a separate deliverable and no sample exists
 * yet, so the spellings below are this tool's half of the contract and are the one thing to
 * re-check against the first real package. The field *set* is not in doubt: a CM or JDM entry
 * carries the part number and the firmware version, and an ODM entry adds vendor name, OUI,
 * vendor revision and hardware major - which is exactly what decides how narrowly each binary
 * matches.
 */
#define CABLE_YAML_KEY_PART_NUMBER "vendor_pn"
#define CABLE_YAML_KEY_FW_VERSION "fw_version"
#define CABLE_YAML_KEY_IMAGE "image"
#define CABLE_YAML_KEY_SHA256 "sha256"
#define CABLE_YAML_KEY_VENDOR_NAME "vendor_name"
#define CABLE_YAML_KEY_VENDOR_OUI "vendor_oui"
#define CABLE_YAML_KEY_VENDOR_REV "vendor_rev"
#define CABLE_YAML_KEY_HW_REV_MAJOR "hw_rev_major"
#define CABLE_YAML_KEY_BUILD_DATE "build_date"

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
#endif

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
    throw std::runtime_error("reading a ZIP package is not supported on this platform; extract it and pass the "
                             "directory instead");
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

static bool metadataEntriesCollide(const FwPackageEntry& left, const FwPackageEntry& right)
{
    // Compared the way a cable is matched, so two entries collide only when one cable could match both.
    if (left.vendorPartNumber != right.vendorPartNumber || left.fwVersion.major != right.fwVersion.major)
    {
        return false;
    }
    if (left.hasVendorName && right.hasVendorName && !equalsIgnoringCase(left.vendorName, right.vendorName))
    {
        return false;
    }
    if (left.hasVendorOui && right.hasVendorOui && left.vendorOui != right.vendorOui)
    {
        return false;
    }
    if (left.hasVendorRev && right.hasVendorRev && left.vendorRev != right.vendorRev)
    {
        return false;
    }
    if (left.hasHwRevMajor && right.hasHwRevMajor && left.hwRevMajor != right.hwRevMajor)
    {
        return false;
    }
    return true;
}

static bool metadataMatchesCable(const FwPackageEntry& entry, const CableInfo& cable)
{
    const CableFwVersion& running = (cable.runningSlot == CABLE_IMAGE_SLOT_B) ? cable.fwImageB : cable.fwImageA;

    // Part number and firmware major are the two keys every metadata file carries. An image for
    // another major describes a different cable generation, not an upgrade for this one.
    //
    // The part number and the revision are compared exactly: the extended header carries the
    // metadata's own bytes, and the device compares those against the EEPROM, so a cable that
    // differs only in case would be planned and then never matched.
    if (entry.vendorPartNumber != cable.partNumber || entry.fwVersion.major != running.major)
    {
        return false;
    }
    // Each remaining key narrows the match only if the file bothered to state it.
    if (entry.hasVendorName && !equalsIgnoringCase(entry.vendorName, cable.vendorName))
    {
        return false;
    }
    if (entry.hasVendorOui && entry.vendorOui != cable.vendorOui)
    {
        return false;
    }
    if (entry.hasVendorRev && entry.vendorRev != cable.vendorRev)
    {
        return false;
    }
    if (entry.hasHwRevMajor && entry.hwRevMajor != cable.hwRevMajor)
    {
        return false;
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
    return "part number '" + partNumber + "', vendor revision '" + vendorRev + "', hardware major " +
           int_to_string((int)hwRevMajor) + ", product id " + int_to_string((int)productId);
}

/* How the device will decide whether this group's image belongs on a cable. */
static string planEntryHeaderText(const CablePlanEntry& group)
{
    if (group.isWrapped)
    {
        return "extended header built here from " + group.header.text();
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

    key.partNumber = entry.vendorPartNumber;
    key.vendorRev = entry.hasVendorRev ? entry.vendorRev : string();
    key.hwRevMajor = entry.hasHwRevMajor ? entry.hwRevMajor : 0;
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

/* Local ports are not numbered from one and nothing reports the highest, so the PLLP sweep is
 * bounded rather than exact. Measured on Quantum-3: label port 1 sits at local port 129.
 */
#define CABLE_MAX_LOCAL_PORT 256

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
 * so the map a cage needs is built by sweeping it. Only the first sub-port of a split cage is
 * kept - they share one cable.
 */
static void buildLocalPortMap(mfile* mf, map<u_int32_t, u_int32_t>& localPortByCage, u_int32_t cages)
{
    for (u_int32_t localPort = 1; localPort <= CABLE_MAX_LOCAL_PORT && localPortByCage.size() < cages; localPort++)
    {
        struct reg_access_switch_pllp_reg_ext pllp;

        memset(&pllp, 0, sizeof(pllp));
        pllp.local_port = (u_int8_t)(localPort & 0xff);
        pllp.lp_msb = (u_int8_t)((localPort >> 8) & 0x3);
        if (reg_access_pllp(mf, REG_ACCESS_METHOD_GET, &pllp) != ME_OK || pllp.label_port == 0 || pllp.split_num != 0)
        {
            continue;
        }
        localPortByCage.insert(std::make_pair((u_int32_t)pllp.label_port - 1, localPort));
    }
    FWMANAGER_LOG_DEBUG("PLLP sweep: mapped %u cage(s) of %u", (unsigned)localPortByCage.size(), cages);
}

#define CABLE_REPORT_RULE "===================================================="

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

    for (AsicsByGa::iterator asic = _asics.begin(); asic != _asics.end(); ++asic)
    {
        mfile* mf = deviceHandle(asic->second.devName);
        if (mf == NULL)
        {
            _errMsg = "Failed to open " + asic->second.devName + " to query the cables it owns";
            return ERR_CODE_CABLE_UPDATE_FAILED;
        }
        u_int32_t owned = 0;
        for (size_t j = 0; j < _cables.size(); j++)
        {
            if (_cables[j].asicGa == asic->first)
            {
                owned++;
            }
        }
        buildLocalPortMap(mf, asic->second.localPortByCage, owned);
        for (size_t j = 0; j < _cables.size(); j++)
        {
            // This port is never updated, so there is nothing to query it for.
            if (_cables[j].action == CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED)
            {
                continue;
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
        if (_cables[i].isBurnable)
        {
            burnable++;
        }
    }
    emitProgress("-I- Found " + int_to_string((int)plugged) + " cable(s), " + int_to_string((int)burnable) +
                 " of them updatable\n");
    return MLX_FWM_SUCCESS;
}

/* The local port serving a cage, from its owning ASIC's swept map. PDDR needs it; MMAM never
 * names one.
 */
bool CableFwManager::cableLocalPort(const CableInfo& cable, u_int32_t& localPort)
{
    AsicsByGa::const_iterator asic = _asics.find(cable.asicGa);

    if (asic == _asics.end())
    {
        return false;
    }
    map<u_int32_t, u_int32_t>::const_iterator port = asic->second.localPortByCage.find(cable.localIndex);
    if (port == asic->second.localPortByCage.end())
    {
        return false;
    }
    localPort = port->second;
    return true;
}

/* The link state for one cable, which is what mlxlink shows as "State". */
string CableFwManager::readCableLinkStateText(mfile* mf, const CableInfo& cable)
{
    u_int32_t localPort = 0;
    u_int8_t state = 0;

    if (!cableLocalPort(cable, localPort) || readCableLinkState(mf, localPort, state) != ME_OK)
    {
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
    u_int8_t operStatus = 0;

    if (readCableOperStatus(mf, cable.localIndex, operStatus) != ME_OK)
    {
        cable.state = "unreadable";
        return;
    }
    cable.operStatus = operStatus;
    cable.isPlugged = (operStatus != CABLE_OPER_STATUS_UNPLUGGED);
    if (!cable.isPlugged)
    {
        return;
    }

    // PDDR is where the firmware republishes the EEPROM, and it is the source every field mlxlink
    // prints comes from, so the two tools agree. It is addressed by local port; a cage the PLLP
    // sweep could not map falls back to reading the EEPROM directly.
    u_int32_t localPort = 0;

    if (cableLocalPort(cable, localPort))
    {
        cable.isReadable = readCableModuleInfo(mf, localPort, cable);
        if (cable.isReadable && !cable.isPlugged)
        {
            return;
        }
    }
    if (!cable.isReadable && !readCableIdentity(mf, cable))
    {
        return;
    }
    // The firmware does not fill every field of the page - the hardware revision reads zero on
    // every cable measured - so anything it left empty is read off the EEPROM itself.
    fillIdentityGapsFromEeprom(mf, cable);
    cable.isReadable = cableIdentityRead(cable);
    // MFCDR answers this directly where the firmware carries it; the OUI list is what is left
    // when it does not, and a fake cable can copy an OUI.
    u_int8_t vendorStatus = readCableVendorStatus(mf, cable.localIndex);
    cable.vendorStatus = vendorStatus;
    if (vendorStatus != CABLE_VENDOR_STATUS_UNKNOWN)
    {
        cable.isNvidia = (vendorStatus == CABLE_VENDOR_STATUS_NVIDIA);
    }
    else
    {
        cable.isNvidia = (cable.vendorOui == CABLE_NVIDIA_OUI) || (cable.vendorOui == CABLE_NVIDIA_OUI_MELLANOX);
    }
    if (!readCableFwProperties(mf, cable))
    {
        return;
    }
    // A cable that implements neither firmware-update procedure reports protocol 0.
    cable.isBurnable = (cable.managementInterfaceProtocol != 0);
    cable.linkState = readCableLinkStateText(mf, cable);
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
        readPackageArchive(_cmdParams.cable_package, contents);
    }

    for (map<string, vector<u_int8_t> >::const_iterator file = contents.begin(); file != contents.end(); ++file)
    {
        const string& name = file->first;
        if (!hasSuffix(lowered(name), CABLE_METADATA_SUFFIX))
        {
            continue;
        }

        FwPackageEntry entry;
        entry.metadataPath = name;
        // A file that does not parse is recorded against itself and the rest of the package is
        // still usable: one bad metadata file must not cost the user the whole maintenance window.
        try
        {
            string text(file->second.begin(), file->second.end());
            fkyaml::node document = fkyaml::node::deserialize(text);

            if (!document.contains(CABLE_YAML_KEY_PART_NUMBER) || !document.contains(CABLE_YAML_KEY_FW_VERSION) ||
                !document.contains(CABLE_YAML_KEY_IMAGE))
            {
                throw std::runtime_error("missing " CABLE_YAML_KEY_PART_NUMBER ", " CABLE_YAML_KEY_FW_VERSION
                                         " or " CABLE_YAML_KEY_IMAGE);
            }
            entry.vendorPartNumber = document.at(CABLE_YAML_KEY_PART_NUMBER).get_value<std::string>();
            string version = document.at(CABLE_YAML_KEY_FW_VERSION).get_value<std::string>();
            if (!parseCableFwVersion(version, entry.fwVersion))
            {
                throw std::runtime_error("firmware version \"" + version + "\" is not major.minor.subminor");
            }
            // The metadata names its binary relative to itself, so the folder it sits in is what
            // resolves the name.
            entry.imagePath = archiveDirectory(name) + document.at(CABLE_YAML_KEY_IMAGE).get_value<std::string>();

            if (document.contains(CABLE_YAML_KEY_VENDOR_NAME))
            {
                entry.vendorName = document.at(CABLE_YAML_KEY_VENDOR_NAME).get_value<std::string>();
                entry.hasVendorName = true;
            }
            if (document.contains(CABLE_YAML_KEY_VENDOR_OUI))
            {
                int oui = document.at(CABLE_YAML_KEY_VENDOR_OUI).get_value<int>();
                if (oui < 0 || oui > 0xffffff)
                {
                    throw std::runtime_error("states a vendor OUI outside 0..0xffffff");
                }
                entry.vendorOui = (u_int32_t)oui;
                entry.hasVendorOui = true;
            }
            if (document.contains(CABLE_YAML_KEY_VENDOR_REV))
            {
                entry.vendorRev = document.at(CABLE_YAML_KEY_VENDOR_REV).get_value<std::string>();
                entry.hasVendorRev = true;
            }
            if (document.contains(CABLE_YAML_KEY_HW_REV_MAJOR))
            {
                int hwRevMajor = document.at(CABLE_YAML_KEY_HW_REV_MAJOR).get_value<int>();
                if (hwRevMajor < 0 || hwRevMajor > 0xff)
                {
                    throw std::runtime_error("states a hardware major outside 0..0xff");
                }
                entry.hwRevMajor = (u_int8_t)hwRevMajor;
                entry.hasHwRevMajor = true;
            }
            // A metadata file is either a CM/JDM entry, keyed on part number and firmware major
            // alone, or an ODM entry that also pins vendor name, OUI, revision and hardware
            // major. Anything between the two states a key it does not narrow on, so it cannot
            // be told apart from a broader entry for the same cable.
            if (entry.hasVendorName || entry.hasVendorOui || entry.hasVendorRev || entry.hasHwRevMajor)
            {
                if (!entry.hasVendorName || !entry.hasVendorOui || !entry.hasVendorRev || !entry.hasHwRevMajor)
                {
                    throw std::runtime_error("carries some but not all of " CABLE_YAML_KEY_VENDOR_NAME
                                             ", " CABLE_YAML_KEY_VENDOR_OUI ", " CABLE_YAML_KEY_VENDOR_REV
                                             " and " CABLE_YAML_KEY_HW_REV_MAJOR);
                }
            }

            // A package keeps each part number in a folder of its own. The tool matches on what a
            // metadata file declares rather than on where it sits, so a file in the wrong folder
            // would still be used - and the folder it names is where its image is looked up, so a
            // mismatch means the package was assembled wrongly and the pairing cannot be trusted.
            string folder = archiveDirectory(entry.metadataPath);
            if (!folder.empty())
            {
                folder.resize(folder.size() - 1); // archiveDirectory keeps the separator
                size_t parent = folder.find_last_of('/');

                if (parent != string::npos)
                {
                    folder = folder.substr(parent + 1);
                }
                if (!equalsIgnoringCase(folder, entry.vendorPartNumber))
                {
                    throw std::runtime_error("declares " CABLE_YAML_KEY_PART_NUMBER " " + entry.vendorPartNumber +
                                             " but sits in folder " + folder + "; the package needs fixing");
                }
            }

            if (document.contains(CABLE_YAML_KEY_BUILD_DATE))
            {
                entry.buildDate = document.at(CABLE_YAML_KEY_BUILD_DATE).get_value<std::string>();
            }

            map<string, vector<u_int8_t> >::const_iterator image = contents.find(entry.imagePath);
            if (image == contents.end())
            {
                throw std::runtime_error("names an image the package does not hold: " + entry.imagePath);
            }
            // The digest is the one check that the file the metadata describes is the file that
            // will reach the cable, and a wrong image on a cable is unrecoverable in the field.
            string expected;
            if (document.contains(CABLE_YAML_KEY_SHA256))
            {
                expected = document.at(CABLE_YAML_KEY_SHA256).get_value<std::string>();
            }
            else
            {
                throw std::runtime_error("carries no " CABLE_YAML_KEY_SHA256 " for its image");
            }
#ifndef NO_OPEN_SSL
            string actual = sha256Hex(image->second);
            if (!equalsIgnoringCase(expected, actual))
            {
                throw std::runtime_error("digest mismatch for " + entry.imagePath + ": expected " + expected +
                                         ", the image hashes to " + actual);
            }
#endif
            // An extended header the package already carries goes to the device as supplied: the
            // device matches the image against it where its fields match the cable. What the tool
            // must not do is build a second header over an existing one.
            entry.hasExtendedHeader =
              hasCableExtendedHeader(image->second.empty() ? NULL : &image->second[0],
                                                    (u_int32_t)image->second.size());
            entry.isValid = true;
        }
        catch (const std::exception& e)
        {
            entry.isValid = false;
            entry.parseError = e.what();
            rejected++;
        }
        _packages.push_back(entry);
    }

    if (rejected > 0)
    {
        emitProgress("-W- Rejected " + int_to_string((int)rejected) + " unusable metadata file(s) in " +
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

    findPackageConflicts();

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

void CableFwManager::findPackageConflicts()
{
    for (size_t i = 0; i < _packages.size(); i++)
    {
        for (size_t j = i + 1; j < _packages.size(); j++)
        {
            if (!_packages[i].isValid || !_packages[j].isValid || !metadataEntriesCollide(_packages[i], _packages[j]))
            {
                continue;
            }
            _packages[i].isValid = false;
            _packages[j].isValid = false;
            _packages[i].conflictsWith = _packages[j].metadataPath;
            _packages[j].conflictsWith = _packages[i].metadataPath;
            _packages[i].parseError = "cannot be told apart from " + _packages[j].metadataPath;
            _packages[j].parseError = "cannot be told apart from " + _packages[i].metadataPath;
        }
    }
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
        // Left to the OUI list, which is all there is when the firmware gave no verdict.
        if (!cable.isNvidia)
        {
            FWMANAGER_LOG_DEBUG("Cable %u: MFCDR gave no verdict and vendor OUI 0x%06x is not an NVIDIA block",
                                cable.globalPort, cable.vendorOui);
            cable.action = CABLE_ACTION_SKIP_3RD_PARTY;
            continue;
        }
        if (!cable.isBurnable)
        {
            cable.action = CABLE_ACTION_SKIP_NOT_BURNABLE;
            continue;
        }

        const FwPackageEntry* match = NULL;
        for (size_t j = 0; j < _packages.size(); j++)
        {
            if (!_packages[j].isValid || !metadataMatchesCable(_packages[j], cable))
            {
                continue;
            }
            // Two cables of one part number can legitimately need different binaries, so a cable
            // matching two metadata files is a packaging error and not a choice this tool can make.
            if (match != NULL)
            {
                _errMsg = "Cable " + int_to_string((int)cableLabelPort(cable.localIndex)) + " on " + cable.asicDevName +
                          " matches both " + match->metadataPath + " and " + _packages[j].metadataPath +
                          "; fix the package so each cable matches one image";
                return ERR_CODE_MULTI_IMG_SRC_FOUND;
            }
            match = &_packages[j];
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
    if (_printer != NULL)
    {
        _printer(text.c_str());
    }
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

        // The device runs a whole group as one transaction and reports nothing while it does, so
        // this is the only sign of life across a burn that takes minutes.
        emitProgress("-I- Updating group " + groupOfTotal + " on " + _plan[i].asicDevName +
                     ", this can take a while...\n");
        FWMANAGER_LOG_DEBUG("Starting auto update on %s for group %s: %s, %u byte(s), expecting %u cable(s) to update, "
                            "%s",
                            _plan[i].asicDevName.c_str(), groupOfTotal.c_str(), _plan[i].packageImagePath.c_str(),
                            (unsigned)_plan[i].burnImage.size(), (unsigned)_plan[i].cableIndices.size(),
                            planEntryHeaderText(_plan[i]).c_str());
        burnPlanEntry(_plan[i], firstResult);

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
        msleep((unsigned int)_cmdParams.cable_activation_wait * 1000);
        ok = runBurnStage(mf, group.burnImage, false, true, firstResult, lastResult, errMsg, stageName);
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
    if (!ok)
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

    // No progress callback: it reports one completion percentage for a transaction that covers a
    // whole group, so the number names no cable, and it would print on its own rather than through
    // the caller's printer.
    bool ok = fwComps.burnComponents(component, NULL);
    if (!ok)
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
        // A self-activating cable resets, so its link drops and re-trains. Verifying before that
        // finishes reports a working cable as failed.
        if (!_results.empty() && _cmdParams.cable_verify_wait > 0)
        {
            emitProgress("-I- Waiting " + int_to_string(_cmdParams.cable_verify_wait) +
                         " second(s) for the cables to finish re-training\n");
            msleep((unsigned int)_cmdParams.cable_verify_wait * 1000);
        }
        verifyBurnedCables();
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
    int rc = writeReport(text);

    if (rc != MLX_FWM_SUCCESS)
    {
        // The file is gone, the outcome is not, so the report goes to the console rather than
        // nowhere. Announced first, or it reads as output the run meant to produce.
        emitProgress("-W- The report file could not be written, so the report follows here\n");
        emitProgress(text);
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
        result.stateAfter = readCableLinkStateText(mf, current);
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
    report << "Ports scanned:     " << _cables.size() << "\n";
    report << "Modules found:     " << plugged << "\n";
    report << "Updates attempted: "
           << (_cmdParams.cable_update ? int_to_string((int)_results.size()) : string(CABLE_REPORT_NOT_AVAILABLE))
           << "\n";
    report << "Succeeded:         "
           << (_cmdParams.cable_update ? int_to_string((int)succeeded) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    report << "Failed:            "
           << (_cmdParams.cable_update ? int_to_string((int)failed) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    report << "Needs power cycle: "
           << (_cmdParams.cable_update ? int_to_string((int)pending) : string(CABLE_REPORT_NOT_AVAILABLE)) << "\n";
    report << "Skipped:           "
           << ((_cmdParams.cable_query || !_planned) ? string(CABLE_REPORT_NOT_AVAILABLE) : int_to_string((int)skipped))
           << "\n\n";

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
        char oui[16];

        if (entry.hasVendorOui)
        {
            snprintf(oui, sizeof(oui), "0x%06x", entry.vendorOui);
            vendor = entry.hasVendorName ? entry.vendorName + " (" + oui + ")" : string(oui);
        }
        else if (entry.hasVendorName)
        {
            vendor = entry.vendorName;
        }
        vector<string> row;

        row.push_back(entry.imagePath.empty() ? entry.metadataPath : entry.imagePath);
        row.push_back(vendor);
        row.push_back(orNotAvailable(entry.vendorPartNumber));
        row.push_back(entry.hasVendorRev ? entry.vendorRev : string(CABLE_REPORT_NOT_AVAILABLE));
        row.push_back(entry.hasHwRevMajor ? int_to_string((int)entry.hwRevMajor) : string(CABLE_REPORT_NOT_AVAILABLE));
        row.push_back(orNotAvailable(entry.buildDate));
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
    headers.push_back("Build Date");
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
           << "State" << std::setw(12) << "Vendor Rev" << std::setw(8) << "HW Rev" << std::setw(14) << "FW A"
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
           << std::setw(12) << orNotAvailable(cable.vendorRev) << std::setw(8) << cableHwRevisionText(cable)
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
        // report is a different answer, and saying so is the point of the section.
        report << (_cmdParams.cable_update ? "No errors were found" : CABLE_REPORT_NOT_AVAILABLE) << "\n\n";
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
    path += "cable_fw_update_report_" + string(stamp) + ".txt";

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
    emitProgress("-I- Report file: " + path + "\n");
    return MLX_FWM_SUCCESS;
}
