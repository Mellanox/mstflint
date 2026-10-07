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

/* The extended header a cable firmware image can carry: its magic and the layout the device
 * matches the image against. Only the pieces the cable flow uses are defined here. */
#define CABLE_EXT_HEADER_MAGIC_STRING "MT2C"
#define CABLE_EXT_HEADER_MAGIC_LENGTH 4
struct cable_ext_header
{
    u_int32_t magicPattern;
    u_int8_t headerVersion;
    u_int8_t vendorOUI;
    u_int16_t reserved;
    u_int32_t vendorPN[4];
    u_int8_t reserved2;
    u_int8_t vendorHWMajor;
    u_int16_t vendorRev;
    u_int8_t vendorFWMajor;
    u_int8_t vendorFWMinor;
    u_int16_t vendorFWbuild;
    u_int32_t imageSize;
    u_int32_t reserved3[3];
};
static bool isCableExtendedHeaderMagic(const u_int8_t* data, u_int32_t len)
{
    return len >= CABLE_EXT_HEADER_MAGIC_LENGTH &&
           !strncmp((const char*)data, CABLE_EXT_HEADER_MAGIC_STRING, CABLE_EXT_HEADER_MAGIC_LENGTH);
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

CableFwManager::~CableFwManager()
{
    if (!_tempDir.empty())
    {
        RemoveDir(_tempDir);
    }
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
#define CABLE_YAML_KEY_SHA_ALT "sha"
#define CABLE_YAML_KEY_VENDOR_NAME "vendor_name"
#define CABLE_YAML_KEY_VENDOR_OUI "vendor_oui"
#define CABLE_YAML_KEY_VENDOR_REV "vendor_rev"
#define CABLE_YAML_KEY_HW_REV_MAJOR "hw_rev_major"

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

    if (sscanf(text.c_str(), "%u.%u.%u", &major, &minor, &subminor) != 3)
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
static void readPackageDirectory(const string& path, const string& prefix, map<string, vector<u_int8_t> >& contents)
{
    vector<string> entries = mft_utils::GetListOfFiles(path);

    for (size_t i = 0; i < entries.size(); i++)
    {
        string relative = prefix.empty() ? pathBaseName(entries[i]) : prefix + "/" + pathBaseName(entries[i]);

        if (mft_utils::IsDirectory(entries[i]))
        {
            readPackageDirectory(entries[i], relative, contents);
        }
        else
        {
            contents[relative] = mft_utils::ReadBinFile(entries[i]);
        }
    }
}

/* Archive entries always use forward slashes, whatever wrote them. */
static string archiveDirectory(const string& entryName)
{
    size_t slash = entryName.find_last_of('/');

    return (slash == string::npos) ? "" : entryName.substr(0, slash + 1);
}

static string archiveBaseName(const string& entryName)
{
    size_t slash = entryName.find_last_of('/');

    return (slash == string::npos) ? entryName : entryName.substr(slash + 1);
}

static bool hasSuffix(const string& text, const string& suffix)
{
    return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/* Build the 48-byte extended header the device validates the image against.
 *
 * Only the keys the tool actually matched on are filled. Everything else is left zero, which the
 * device treats as a wildcard, so the device ends up checking exactly what the metadata claimed
 * and nothing the tool had to invent.
 */
static vector<u_int8_t> withExtendedHeader(const FwPackageEntry& entry, const vector<u_int8_t>& image)
{
    struct cable_ext_header header;
    vector<u_int8_t> output;

    memset(&header, 0, sizeof(header));
    // The magic is four ASCII characters at offset 0, not a number: written as an integer it
    // would come out reversed on a little-endian host.
    memcpy(&header, CABLE_EXT_HEADER_MAGIC_STRING, CABLE_EXT_HEADER_MAGIC_LENGTH);
    header.headerVersion = 1; // carries an explicit imageSize rather than implying it from the file
    memcpy(header.vendorPN, entry.vendorPartNumber.c_str(),
           (entry.vendorPartNumber.size() < sizeof(header.vendorPN)) ? entry.vendorPartNumber.size() :
                                                                       sizeof(header.vendorPN));
    header.vendorFWMajor = entry.fwVersion.major;
    header.vendorFWMinor = entry.fwVersion.minor;
    header.vendorFWbuild = entry.fwVersion.subminor;
    header.imageSize = (u_int32_t)image.size();

    output.resize(sizeof(header) + image.size());
    memcpy(&output[0], &header, sizeof(header));
    if (!image.empty())
    {
        memcpy(&output[sizeof(header)], &image[0], image.size());
    }
    return output;
}

static bool metadataMatchesCable(const FwPackageEntry& entry, const CableInfo& cable)
{
    // The part number is the one key every metadata file carries.
    if (!equalsIgnoringCase(entry.vendorPartNumber, cable.partNumber))
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
    if (entry.hasVendorRev && !equalsIgnoringCase(entry.vendorRev, cable.vendorRev))
    {
        return false;
    }
    if (entry.hasHwRevMajor && entry.hwRevMajor != cable.hwRevMajor)
    {
        return false;
    }
    return true;
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
    _log += "-W- This tool was built without OpenSSL, so the package checksums are not verified\n";
#endif
    u_int32_t rejected = 0;

    if (mft_utils::IsDirectory(_cmdParams.cable_package))
    {
        readPackageDirectory(_cmdParams.cable_package, "", contents);
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
                entry.vendorOui = (u_int32_t)document.at(CABLE_YAML_KEY_VENDOR_OUI).get_value<int>();
                entry.hasVendorOui = true;
            }
            if (document.contains(CABLE_YAML_KEY_VENDOR_REV))
            {
                entry.vendorRev = document.at(CABLE_YAML_KEY_VENDOR_REV).get_value<std::string>();
                entry.hasVendorRev = true;
            }
            if (document.contains(CABLE_YAML_KEY_HW_REV_MAJOR))
            {
                entry.hwRevMajor = (u_int8_t)document.at(CABLE_YAML_KEY_HW_REV_MAJOR).get_value<int>();
                entry.hasHwRevMajor = true;
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
            else if (document.contains(CABLE_YAML_KEY_SHA_ALT))
            {
                expected = document.at(CABLE_YAML_KEY_SHA_ALT).get_value<std::string>();
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
            entry.hasExtendedHeader = isCableExtendedHeaderMagic(
              image->second.empty() ? NULL : &image->second[0], (u_int32_t)image->second.size());
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
        _log += "Rejected " + int_to_string((int)rejected) + " unusable metadata file(s) in " +
                _cmdParams.cable_package + "\n";
        for (size_t i = 0; i < _packages.size(); i++)
        {
            if (!_packages[i].isValid)
            {
                _log += "  " + _packages[i].metadataPath + ": " + _packages[i].parseError + "\n";
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
    _log += "Read " + int_to_string((int)usable) + " firmware image(s) from " + _cmdParams.cable_package + "\n";
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
            cable.action = CABLE_ACTION_SKIP_NOT_PRESENT;
            continue;
        }
        if (!cable.isNvidia)
        {
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
        // An older target still goes ahead; it is flagged rather than refused.
        cable.isDowngrade = compareCableFwVersions(match->fwVersion, running) < 0;
    }
    return MLX_FWM_SUCCESS;
}

int CableFwManager::groupUpdatePlan(const map<string, vector<u_int8_t> >& contents)
{
    map<string, size_t> groupIndex;

    for (size_t i = 0; i < _cables.size(); i++)
    {
        if (_cables[i].action != CABLE_ACTION_UPDATE)
        {
            continue;
        }
        // One burn carries one image through one ASIC, and an ASIC cannot address another ASIC's
        // cables, so the grouping is forced by the transport rather than chosen.
        string key = _cables[i].asicDevName + '\n' + _cables[i].packageImagePath;
        map<string, size_t>::iterator existing = groupIndex.find(key);
        if (existing == groupIndex.end())
        {
            CablePlanEntry group;
            group.asicDevName = _cables[i].asicDevName;
            group.asicGa = _cables[i].asicGa;
            group.packageImagePath = _cables[i].packageImagePath;
            group.fwVersion = _cables[i].targetVersion;
            groupIndex[key] = _plan.size();
            _plan.push_back(group);
            existing = groupIndex.find(key);
        }
        _plan[existing->second].cableIndices.push_back((u_int32_t)i);
    }

    if (_plan.empty())
    {
        _log += "No cable needs an update\n";
        return MLX_FWM_SUCCESS;
    }

    // The burn opens a file, and a ZIP entry has no path on disk, so every image is extracted -
    // with the extended header prepended when the package binary had none. The package itself is
    // never modified and the copies never reach the report.
    string prefix = (string)TMP_DIR + PATH_SEPARATOR + "cable_fw_update_";
    if (CreateTempDir(prefix, _tempDir) < 0)
    {
        _errMsg = "Failed to create a temporary directory for the firmware images";
        return ERR_CODE_WRITE_FILE_FAIL;
    }

    for (size_t i = 0; i < _plan.size(); i++)
    {
        map<string, vector<u_int8_t> >::const_iterator image = contents.find(_plan[i].packageImagePath);
        if (image == contents.end())
        {
            _errMsg = "The package no longer holds " + _plan[i].packageImagePath;
            return ERR_CODE_IMG_NOT_FOUND;
        }
        const FwPackageEntry* entry = NULL;
        for (size_t j = 0; j < _packages.size(); j++)
        {
            if (_packages[j].isValid && _packages[j].imagePath == _plan[i].packageImagePath)
            {
                entry = &_packages[j];
                break;
            }
        }
        if (entry == NULL)
        {
            _errMsg = "No metadata describes " + _plan[i].packageImagePath;
            return ERR_CODE_IMG_NOT_FOUND;
        }

        vector<u_int8_t> payload = entry->hasExtendedHeader ? image->second : withExtendedHeader(*entry, image->second);
        _plan[i].burnImagePath =
          _tempDir + PATH_SEPARATOR + int_to_string((int)i) + "_" + archiveBaseName(_plan[i].packageImagePath);
        mft_utils::WriteToBinFile(_plan[i].burnImagePath, payload);
    }

    u_int32_t cables = 0;
    for (size_t i = 0; i < _plan.size(); i++)
    {
        cables += (u_int32_t)_plan[i].cableIndices.size();
    }
    _log += "Planned " + int_to_string((int)cables) + " cable update(s) in " + int_to_string((int)_plan.size()) +
            " group(s)\n";
    return MLX_FWM_SUCCESS;
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
