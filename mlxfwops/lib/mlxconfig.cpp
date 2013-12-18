/*
 *
 * flint.cpp - FLash INTerface
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
#include <getopt.h>
#include <sstream>
#include <assert.h>
#include <errno.h>
#include <json/reader.h>
#include <common/print_utils.h>
#include <common/tools_version.h>
#include <adb_parser/adb_parser.h>
#include "mlxconfig.h"
#include "flint_ops.h"
/**************************** Globals *************************/
static const char static_profiles [] = {
#include "profiles.json.dat"
};

#undef PRINT_DEBUG
#define PRINT_DEBUG(fmt, ...)

/************************************
 * Function: int2string
 ************************************/
string int2string(long int number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

/************************************
 * Function: print
 ************************************/
void Pair::print()
{
    cout << "\t\t(" << key << ", " << value + ")";
}

/************************************
 * Function: print
 ************************************/
void Tlv::print()
{
    cout << "\n\tTlv: " << name << ", fields: \n";
    for (size_t i = 0; i < fields.size(); i++)
    {
        fields[i].print();
        cout << ",\n";
    }
}

/************************************
 * Function: print
 ************************************/
void Profile::print()
{
    cout << " Version: " << version << ", id: " << id;
    for (size_t i = 0; i < tlvs.size(); i++)
    {
        tlvs[i].print();
        cout << ",\n";
    }
}

/************************************
 * Function: parseCmdLine
 ************************************/
bool MlxConfig::parseCmdLine(int argc, const char** argv)
{
    this->_cmd = CMD_UNKNOWN;

#define SET_CMD(cmd)\
    do {\
        if (this->_cmd != CMD_UNKNOWN) {\
            printf("config doesn't support multiple commands\n");\
            return false;\
        }\
        else {\
            this->_cmd = cmd;\
        }\
    }\
    while(0)

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "query") || !strcmp(argv[i], "q"))
        {
            SET_CMD(CMD_QUERY);
        }
        else if (!strcmp(argv[i], "set") || !strcmp(argv[i],"s"))
        {
            SET_CMD(CMD_SET);
            if (i >= argc - 1)
            {
                printf("Missing <profile name> for \"set\" option\n");
                return false;
            }
            this->_cmdProfile = argv[i+1];
            i++;
        }
        else if (!strcmp(argv[i], "restore") || !strcmp(argv[i], "r"))
        {
            SET_CMD(CMD_RESTORE);
        }
        else if (!strcmp(argv[i], "lp") || !strcmp(argv[i], "l"))
        {
            SET_CMD(CMD_LIST_PROFILES);
        }
        else if (!strcmp(argv[i], "h") || !strcmp(argv[i], "help"))
        {
            SET_CMD(CMD_HELP);
            return true;
        }
        else if (!strcmp(argv[i], "-pf"))
        {
            if (i >= argc - 1)
            {
                printf("Missing profiles file for \"pf\" option\n");
                return false;
            }
            this->_profilesFile = argv[i+1];
            i++;
        }
        else if (!strcmp(argv[i], "-verbose"))
        {
            this->_verbose = true;
        }
        else if (!strcmp(argv[i], "reconfig")) // For debug
        {
            SET_CMD(CMD_RECONFIG);
        }
        else if (!strcmp(argv[i], "config_info"))
        {
            SET_CMD(CMD_CONFIG_INFO);
        }
        else if (!strcmp(argv[i], "verify") || !strcmp(argv[i], "v"))
        {
            SET_CMD(CMT_VERIFY);
        }
        else
        {
            printf("Unknown config sub-command: %s\n", argv[i]);
            return false;
        }
    }

    return true;
}

/************************************
 * Function: getHelpMessage
 ************************************/
const char* MlxConfig::getHelpMessage()
{
    return
           "  config sub-commands:\n"
           "    s[et] <profile name>      - Burn the given profile and set as the active configuration profile\n"
           "    q[uery]                   - Query the current profile\n"
           "    r[estore]                 - Restore to defaults (Erase all configurations)\n"
           "    l[p]                      - List available and supported profiles\n"
           "    v[erify]                  - Verify configuration section\n\n"
           "  config options:\n"
           "    -verbose                  - Print more details";
}

/************************************
 * Function: getRunExamples
 ************************************/
const char* MlxConfig::getRunExamples()
{
    return
    "* Query/Set/Restore mellanox device's nonvolatile configuration section\n"
    "    Command:\n"
    "        config\n"
    "    Parameters:\n"
    "        s[et] <profile> - to set the reaquired profile\n"
    "        q[uery]         - to query the current profile\n"
    "        r[estore]       - to restore to defaults\n"
    "        l[p]            - to list supported profiles\n"
    "        v[erify]        - Verify configuration section\n\n"
    "    config options:\n"
    "        -verbose        - Print more details\n"
    "    Example:\n"
    "        flint -d /dev/mst/mt4099_pci_cr0 config set 8PF_ETH\n"
    "        flint -d /dev/mst/mt4099_pci_cr0 config query\n"
    "        flint -d /dev/mst/mt4099_pci_cr0 config restore\n"
    "        flint -d /dev/mst/mt4099_pci_cr0 config lp\n";
}

/************************************
 * Function: MlxConfig
 ************************************/
MlxConfig::MlxConfig():
        _lastMsg("None"), _cmd(CMD_UNKNOWN), _verbose(false), _adbDB(0), _adbRoot(0)
{
}

/************************************
 * Function: ~MlxConfig
 ************************************/
MlxConfig::~MlxConfig()
{

}

/************************************
 * Function: loadImageData
 ************************************/
bool MlxConfig::loadImageData(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    assert(flash);
    assert(op);

    if (!flashImageInfo.imageOk)
    {
        _lastMsg = "FW image is empty or corrupted";
        return false;
    }

    // get cfg section info
    _cfgSize =  flashImageInfo.configSize;
    _cfgAddress[0] = flashImageInfo.configAddr1;
    _cfgAddress[1] = flashImageInfo.configAddr2;

    _isFailSafe = flashImageInfo.isFailsafe;
    if (!_isFailSafe)
    {
        _cfgAddress[0] = _cfgAddress[1];
    }

    // check current burnt configuration version
    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
        return false;

    if (activeCfgIdx != -1)
    {
        u_int32_t dword;
        if (!flash->read_phy(_cfgAddress[activeCfgIdx] + 4, &dword, 4))
        {
            _lastMsg = flash->err();
            return false;
        }

        // Parse the  cfg header
        u_int32_t version = htonl(dword) & 0xff;

        if (version != MLX_CFG_VERSION)
        {
            _lastMsg = "Unsupported configuration section version \"" + int2string(version) + "\" was found"
                       "\nThe only supported configuration version by this tools is \"" +
                       int2string(MLX_CFG_VERSION) + "\""+
                       "\nConsider erasing the configuration section with: \"config r\" flint's command ";
            return false;
        }
    }

    // Get json
    vector<u_int8_t> jsonData;
    if (!op->GetProfileList(&flashImageInfo, jsonData))
    {
        _lastMsg = op->err();
        return false;
    }

    string jsonTxt = string((char*)&jsonData[0]);
    // Load profiles mapping
    if (jsonTxt.empty())
    {
        _lastMsg = "Image doesn't contain any profiles info";
        return false;
    }

    if (!parseProfileDb(jsonTxt))
        return false;

    // Get Adabe
    vector<u_int8_t> adabeData;
    if (!op->GetTlvFormatXML(&flashImageInfo, adabeData))
    {
        _lastMsg = op->err();
        return false;
    }

    string adabeTxt = string((char*)&adabeData[0]);
    if (adabeTxt.empty())
    {
        _lastMsg = op->err();
        return false;
    }

    if (_adbDB)
    {
        delete _adbDB;
        _adbDB = 0;
    }
    if (_adbRoot)
    {
        delete _adbRoot;
        _adbDB = 0;
    }

    _adbDB = new Adb;
    if (!_adbDB->loadFromString(adabeTxt.c_str()))
    {
        _lastMsg = _adbDB->getLastError();
        return false;
    }

    // get Root, TlvHeader and CfgHeader nodes
    _adbRoot = _adbDB->createLayout(_adbDB->rootNode);
    if (!_adbRoot)
    {
        _lastMsg = "Can't get root node of TLVs: " + _adbDB->getLastError();
        return false;
    }
    _adbTlvHeader = _adbRoot->getChildByPath("tlv_header");
    _adbCfgHeader = _adbRoot->getChildByPath("cfg_section_header");
    if (!_adbTlvHeader || !_adbCfgHeader)
    {
        _lastMsg = "Can't find one of the tlv_header/cfg_section_header definition in TLVs adabe";
        return false;
    }

    return true;
}

/************************************
 * Function: execute
 ************************************/
bool MlxConfig::execute(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, int argc, const char** argv)
{
    if (!parseCmdLine(argc, argv))
    {
        _lastMsg = "Failed to parse command line arguments";
        return false;
    }

    // This if handles the ugly old FW that configured using old mlxconfig tool
    bool cfgPresent;
    u_int32_t cfgVer;
    if (!isConfigPresent(flash, op, flashImageInfo, cfgPresent, cfgVer))
        return false;

    if (_cmd != CMD_RESTORE && cfgPresent && cfgVer == OLD_MLXCONFIG_VERSION)
    {
        _lastMsg = "Found old version of FW configuration, please use \"mlxconfig\"";
        return false;
    }

    switch (_cmd)
    {
    case CMD_SET:
        return setCfg(flash, op, flashImageInfo, _cmdProfile);
    case CMD_QUERY:
        return queryCfg(flash, op, flashImageInfo);
    case CMD_RESTORE:
        return eraseCfg(flash, op, flashImageInfo);
    case CMD_LIST_PROFILES:
        return listProfilesCfg(flash, op, flashImageInfo);
    case CMD_RECONFIG:
        return reconfigureCfg(flash, op, flashImageInfo);
    case CMD_HELP:
        printf("%s\n", getHelpMessage());
        return true;
    case CMD_CONFIG_INFO:
        return configInfo(flash, op, flashImageInfo);
    case CMT_VERIFY:
        return verifyCfg(flash, op, flashImageInfo);
    default:
        _lastMsg = "No command given. See help for details.";
        return false;
    }
}

/************************************
 * Function: setCfg
 ************************************/
bool MlxConfig::setCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, string profileName, bool silent)
{
    // Pack all tlvs
    u_int8_t *tlvHeaderBuf, *tlvDataBuf;
    u_int32_t totalCfgSize = 0;
    Profile profile;
    u_int32_t crc16;

    if (!flashImageInfo.isConfigurable)
    {
        _lastMsg = "Current FW image isn't configurable";
        return false;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    if (!_isFailSafe)
    {
        if (!silent)
        {
            printf("Burning new configuration in non-fail-safe mode");
            if (!op->ask_user())
            {
                _lastMsg = "Set FW configuration was skipped by user";
                return false;
            }
        }
    }

    int nextActiveCfgIdx;
    if (!getActiveCfgIdx(flash, nextActiveCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }
    nextActiveCfgIdx = nextActiveCfgIdx == -1 ? 0 : nextActiveCfgIdx;
    PRINT_DEBUG("Current active image: %d", nextActiveCfgIdx);
    nextActiveCfgIdx = 1 - nextActiveCfgIdx;
    PRINT_DEBUG("Next active image: %d", nextActiveCfgIdx);

    if (!silent)
    {
        printf("Burning new Configuration");
        fflush(stdout);
    }

    // Check if profile exists
    if (!_profilesMap.count(profileName))
    {
        _lastMsg = "Can't find definition of the given profile: " + profileName;
        goto failed;
    }
    profile = _profilesMap[profileName];

    // Check if profile is supported
    for (size_t i = 0; i < flashImageInfo.supportedProfList.size(); i++)
    {
        if (flashImageInfo.supportedProfList[i] == profile.id)
            break;

        if (i == flashImageInfo.supportedProfList.size() - 1)
        {
            _lastMsg = "Profile " + profileName + " isn't supported";
            return false;
        }
    }

    // Calculate the total required buffer len (in bytes)
    totalCfgSize = _adbCfgHeader->size/8 + _adbTlvHeader->size/8;
    for (size_t i = 0; i < profile.tlvs.size(); i++)
    {
        AdbInstance* node = _adbRoot->getChildByPath(profile.tlvs[i].name);
        if (!node)
        {
            _lastMsg = "Can't find definition (" + profile.tlvs[i].name + ") - Report a bug";
            goto failed;
        }

        totalCfgSize += node->size/8 + _adbTlvHeader->size/8;
    }

    if (totalCfgSize > _cfgSize)
    {
        _lastMsg = "The profile: " + profileName + " size is greater than the configuration section size";
        goto failed;
    }

    if (!op->IsConfigAreaAvialable(flash, &flashImageInfo))
    {
        _lastMsg = "Configuration area overlaps with FW image, maybe you have too large FW image";
        goto failed;
    }

    // Allocate the required amount of memory
    u_int8_t buf[totalCfgSize];
    memset(buf, 0, totalCfgSize); // zerofy all reserved fields

    // Pack the configuration section header (TEMPORARY VALID SIGNATURE WITH CRC16)
    setCfgSectionHeader(buf, CFG_HEADER_SIGNATURE, CFG_SIGNATURE);
    setCfgSectionHeader(buf, CFG_HEADER_MAX_LEN, _cfgSize/4);
    setCfgSectionHeader(buf, CFG_HEADER_VERSION, MLX_CFG_VERSION);
    setCfgSectionHeader(buf, CFG_HEADER_PROFILE_ID, profile.id);
    setCfgSectionHeader(buf, CFG_HEADER_PROFILE_VER, profile.version);
    setCfgSectionHeader(buf, CFG_HEADER_CRC, 0xffff);
    crc16 = calcBECrc16((u_int32_t*)buf, _adbCfgHeader->size/32);
    // set invalid signature with and the calculated crc
    setCfgSectionHeader(buf, CFG_HEADER_SIGNATURE, CFG_INVALID_SIGNATURE);
    setCfgSectionHeader(buf, CFG_HEADER_CRC, crc16);

    // Pack all tlvs
    tlvHeaderBuf = buf + _adbCfgHeader->size/8;
    tlvDataBuf = tlvHeaderBuf + _adbTlvHeader->size/8;
    for (size_t i = 0; i < profile.tlvs.size(); i++)
    {
        // Find the node definition
        string tlvName = profile.tlvs[i].name;
        AdbInstance* node = _adbRoot->getChildByPath(tlvName);
        if (!node)
        {
            _lastMsg = "Can't find node definition for: " + tlvName;
            goto failed;
        }

        int nodeId;
        if (!getTlvNodeId(node, nodeId))
        {
            goto failed;
        }

        int tlvVer;
        if (!getTlvVersion(node, tlvVer))
        {
            goto failed;
        }

        // First fill the tlv content and then the tlv header
        // Go over fields and set their value
        for (size_t j = 0; j < profile.tlvs[i].fields.size(); j++)
        {
            AdbInstance* f;
            f = node->getChildByPath(profile.tlvs[i].fields[j].key);
            if (!f)
            {
                _lastMsg = "Can't find the field: " + profile.tlvs[i].fields[j].key + " in node: " + tlvName;
                goto failed;
            }

            u_int64_t value;
            if (!getFieldIntValue(profile.tlvs[i].fields[j].value, f, value))
            {
                goto failed;
            }

            f->pushBuf(tlvDataBuf, value);
        }

        // Set header with invalid crc16
        setTlvHeader(tlvHeaderBuf, TLV_HEADER_LENGTH, node->size/32);
        setTlvHeader(tlvHeaderBuf, TLV_HEADER_ID, nodeId);
        setTlvHeader(tlvHeaderBuf, TLV_HEADER_CRC, 0xffff);
        setTlvHeader(tlvHeaderBuf, TLV_HEADER_VERSION, tlvVer);
        // Calc crc16
        u_int16_t crc16 = calcBECrc16((u_int32_t*)tlvHeaderBuf, _adbTlvHeader->size/32 + node->size/32);

        // Set the header crc16
        setTlvHeader(tlvHeaderBuf, TLV_HEADER_CRC, crc16);

        // Update next tlvHeader & tlvData buffer pointers
        tlvHeaderBuf += _adbTlvHeader->size/8 + node->size/8;
        tlvDataBuf = tlvHeaderBuf + _adbTlvHeader->size/8;
    }

    // Add last tlv header
    // CRC16 on all section except of the signature (first dwrod) and last dword (the CRC itself)
    setTlvHeader(tlvHeaderBuf, TLV_HEADER_LENGTH, 0);
    setTlvHeader(tlvHeaderBuf, TLV_HEADER_ID, LAST_TLV_ID);
    setTlvHeader(tlvHeaderBuf, TLV_HEADER_CRC, calcBECrc16(((u_int32_t*)buf)+1, (totalCfgSize-4)/4));

    PRINT_DEBUG("Erasing section: 0x%x", _cfgAddress[nextActiveCfgIdx]);
    if (!flash->erase_sector_phy(_cfgAddress[nextActiveCfgIdx]))
    {
        _lastMsg = flash->err();
        goto failed;
    }

    PRINT_DEBUG("Writing %d bytes to cfg section", totalCfgSize);
    if (!flash->write_phy(_cfgAddress[nextActiveCfgIdx]+4, buf+4, totalCfgSize-4, true))
    {
        _lastMsg = flash->err();
        goto failed;
    }

    // ACTIVATE IT BY WRITING VALID SIGNATURE
    // write the signature
    PRINT_DEBUG("Activating image: %d", nextActiveCfgIdx);
    setCfgSectionHeader(buf, CFG_HEADER_SIGNATURE, CFG_SIGNATURE);
    if (!flash->write_phy(_cfgAddress[nextActiveCfgIdx], buf, 4, true))
    {
        _lastMsg = flash->err();
        goto failed;
    }

    if (_isFailSafe)
    {
        // Invalidate current active cfg
        PRINT_DEBUG("Inactivating image: %d", 1- nextActiveCfgIdx);
        setCfgSectionHeader(buf, CFG_HEADER_SIGNATURE, CFG_INVALID_SIGNATURE);
        if (!flash->write_phy(_cfgAddress[1-nextActiveCfgIdx], buf, 4, true))
        {
            _lastMsg = string() + "Failed to invalidate configuration: " + flash->err();
            goto failed;
        }
    }

    if (!silent)
        printf(" - OK\n");
    return true;

failed:
    if (!silent)
        printf(" - FAILED\n");
    return false;
}

/************************************
 * Function: queryCfg
 ************************************/
bool MlxConfig::queryCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    if (!flashImageInfo.isConfigurable)
    {
        _lastMsg = "Current FW image isn't configurable";
        return false;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }

    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1)
    {
        printf("There is no valid configuration\n");
        string profileName = findProfileById(flashImageInfo.defPorfile);
        printf("Default profile is: %s (0x%x)\n", profileName.empty() ? "Unknown" : profileName.c_str(),
                                                    flashImageInfo.defPorfile);
        return true;
    }

    if (_verbose)
        printf("Active configuration image at address: %#x\n", _cfgAddress[activeCfgIdx]);

    u_int8_t buf[_adbCfgHeader->size/8];
    if (!flash->read_phy(_cfgAddress[activeCfgIdx], buf, _adbCfgHeader->size/8))
    {
        _lastMsg = flash->err();
        return false;
    }

    // Parse the  cfg header
    u_int32_t signature, crc16, maxLen, version, profileID, profileVer;
    signature = getCfgSectionHeader(buf, CFG_HEADER_SIGNATURE);
    maxLen = getCfgSectionHeader(buf, CFG_HEADER_MAX_LEN);
    version = getCfgSectionHeader(buf, CFG_HEADER_VERSION);
    profileID = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_ID);
    profileVer = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_VER);
    crc16 = getCfgSectionHeader(buf, CFG_HEADER_CRC);

    // Find the appropriate profile
    string profileName = findProfileById(profileID);
    if (profileName.empty())
    {
        _lastMsg = "Burnt profile ID is: " + int2string(profileID) + ", But can't find it in DB";
        return false;
    }

    printf("Active Profile: %s, Profile Version: 0x%x\n", profileName.c_str(), profileVer);

    // Print TLV contents
    if (_verbose)
    {
        printf("Configuration Section Version: 0x%x\n", version);
        printf("Crc16: 0x%x\n", crc16);
        printf("Tlv contents:\n");
        u_int32_t tlvAddr = _cfgAddress[activeCfgIdx] + _adbCfgHeader->size/8;
        while(1)
        {
            u_int8_t tlvHeaderBuf[_adbTlvHeader->size/8];
            if (!flash->read_phy(tlvAddr, &tlvHeaderBuf, _adbTlvHeader->size/8))
            {
                _lastMsg = flash->err();
                return false;
            }

            u_int16_t len, id, tlvVer, crc;
            len = getTlvHeader(tlvHeaderBuf, TLV_HEADER_LENGTH);
            id = getTlvHeader(tlvHeaderBuf, TLV_HEADER_ID);
            crc = getTlvHeader(tlvHeaderBuf, TLV_HEADER_CRC);
            tlvVer = getTlvHeader(tlvHeaderBuf, TLV_HEADER_VERSION);
            if ((u_int32_t)id == LAST_TLV_ID)
            {
                printf("\tTlv: LAST\n");
                break;
            }

            tlvAddr += _adbTlvHeader->size/8;
            len *= 4;
            u_int8_t buf[len];
            if (!flash->read_phy(tlvAddr, buf, len))
            {
                _lastMsg = flash->err();
                return false;
            }

            // Find the layout for this tlv id
            AdbInstance* node = getTlvById(id);
            if (!node)
            {
                _lastMsg = "Can't find TLV definition for TLV ID: " + int2string(id);
                return false;
            }

            printf("\tTlv: %s (0x%x), version(%d), crc16(0x%x)\n", node->name.c_str(), id, tlvVer, crc);
            vector<AdbInstance*> fields = node->getLeafFields();
            for (size_t i = 0; i < fields.size(); i++)
            {
                AdbInstance* f = fields[i];
                string name = f->fullName(2);
                u_int32_t value = f->popBuf(buf);

                string enumName;
                if (f->intToEnum(value, enumName))
                {
                    printf("\t\t%-20s : %s (0x%x)\n", name.c_str(), enumName.c_str(), value);
                }
                else
                {
                    printf("\t\t%-20s : 0x%x\n", name.c_str(), value);
                }
            }
            tlvAddr += len;
        }
    }

    return true;
}

/************************************
 * Function: eraseCfg
 ************************************/
bool MlxConfig::eraseCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    // This method must be minimalist, it's shouldn't depend on any image info or old/new fw image.
    // It should always work
    /*if (!flashImageInfo.isConfigurable)
    {
        _lastMsg = "Current FW image isn't configurable";
        return false;
    }*/

    if (!flashImageInfo.imageOk)
    {
     _lastMsg = "FW image is empty or corrupted";
     return false;
    }

    // get cfg section info
    _cfgSize =  flashImageInfo.configSize;
    _cfgAddress[0] = flashImageInfo.configAddr1;
    _cfgAddress[1] = flashImageInfo.configAddr2;

    _isFailSafe = flashImageInfo.isFailsafe;
    if (!_isFailSafe)
    {
     _cfgAddress[0] = _cfgAddress[1];
    }

    if (!op->ask_user("You are trying to restore default configuration, do you want to continue"))
    {
        return true;
    }

    printf("Restoring FW configurations to defaults");
    fflush(stdout);

    if (!flash->erase_sector_phy(_cfgAddress[0]) ||
       (_isFailSafe && !flash->erase_sector_phy(_cfgAddress[1])))
    {
        _lastMsg = flash->err();
        printf(" - FAILED\n");
        return false;
    }

    printf(" - OK\n");
    return true;
}

/************************************
 * Function: listProfilesCfg
 ************************************/
bool MlxConfig::listProfilesCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    if (!flashImageInfo.isConfigurable)
    {
        _lastMsg = "Current FW image isn't configurable";
        return false;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }

    printf("Supported profiles by the current FW image:\n");
    for (size_t i = 0; i < flashImageInfo.supportedProfList.size(); i++)
    {
        string profileName = findProfileById(flashImageInfo.supportedProfList[i]);
        if (profileName.empty())
        {
            _lastMsg = "Can't find profile (" + int2string(flashImageInfo.supportedProfList[i]) +
                       ") definition in current Fw image";
            return false;
        }
        PRINT_COLOR(COLOR_GREEN, "\t%u) %s\n", (unsigned)i, profileName.c_str());
    }

    return true;
}

/************************************
 * Function: reconfigureCfg
 ************************************/
bool MlxConfig::reconfigureCfg(Flash* flash, Operations* op, Operations::ImageInfo &newImageInfo)
{
    if (!newImageInfo.isConfigurable)
    {
        return true;
    }
    if (!loadImageData(flash, op, newImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, newImageInfo, true))
    {
        return false;
    }

    // get the burnt profile
    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1)
    {
        return true;
    }

    u_int8_t buf[_adbCfgHeader->size/8];
    if (!flash->read_phy(_cfgAddress[activeCfgIdx], buf, _adbCfgHeader->size/8))
    {
        _lastMsg = flash->err();
        return false;
    }

    // Parse the cfg header
    u_int32_t profileID, profileVer;
    profileID = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_ID);
    profileVer = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_VER);

    if (profileID == CUSTOM_PROFILE_ID) // No need to reconfigure
    {
        return true;
    }

    // find definition for this profile in the current Fw Image json
    // Find the appropriate profile
    string profileName = findProfileById(profileID);
    if (profileName.empty())
    {
        _lastMsg = "Burnt profile ID is: " + int2string(profileID) + ", But can't find it in current Fw Image Profiles";
        return false;
    }

    if (_profilesMap[profileName].version ==  profileVer) // No need to reconfigure
    {
        return true;
    }

    printf("Reconfiguring FW configuration section");
    fflush(stdout);
    bool rc = setCfg(flash, op, newImageInfo, profileName, true);
    if (rc)
        printf(" - OK\n");
    else
        printf(" - FAILED\n");

    return rc;
}

/************************************
 * Function: verifyCfg
 ************************************/
bool MlxConfig::verifyCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, bool silent)
{
    if (!flashImageInfo.isConfigurable)
    {
        _lastMsg = "Current FW image isn't configurable";
        return false;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1)
        return true;

    // verify the configuration header
    u_int8_t buf[flashImageInfo.configSize];
    if (!flash->read_phy(_cfgAddress[activeCfgIdx], buf, _adbCfgHeader->size/8))
    {
        _lastMsg = flash->err();
        return false;
    }

    // Parse the cfg header
    u_int32_t cfgCrc, expCfgCrc;
    cfgCrc = getCfgSectionHeader(buf, CFG_HEADER_CRC);

    // calc expected crc16
    setCfgSectionHeader(buf, CFG_HEADER_CRC, 0xffff);
    expCfgCrc = calcBECrc16((u_int32_t*)buf, _adbCfgHeader->size/32);
    if (!crcVerify(_cfgAddress[activeCfgIdx], _adbCfgHeader->size/8, "FW Configurations Header", cfgCrc, expCfgCrc, silent))
    {
        _lastMsg = "Configuration Section Header Data Integrity Error - CRC check failed";
        return false;
    }

    u_int32_t tlvAddr = _cfgAddress[activeCfgIdx] + _adbCfgHeader->size/8;
    int tlvIdx = 0;
    while(1)
    {
        if (!flash->read_phy(tlvAddr, buf, _adbTlvHeader->size/8))
        {
            _lastMsg = flash->err();
            return false;
        }

        u_int32_t tlvCrc, expTlvCrc, id, len;
        id = getTlvHeader(buf, TLV_HEADER_ID);
        tlvCrc = getTlvHeader(buf, TLV_HEADER_CRC);
        len = getTlvHeader(buf, TLV_HEADER_LENGTH);

        if ((u_int32_t)id == LAST_TLV_ID)
        {
            break;
        }

        if (!flash->read_phy(tlvAddr + _adbTlvHeader->size/8, buf + _adbTlvHeader->size/8, len*4))
        {
            _lastMsg = flash->err();
            return false;
        }

        setTlvHeader(buf, TLV_HEADER_CRC, 0xffff);
        expTlvCrc = calcBECrc16((u_int32_t*)buf, len + _adbTlvHeader->size/32);
        if (!crcVerify(tlvAddr, len*4 + _adbTlvHeader->size/8,
                       "Tlv[" + int2string(tlvIdx) + "]",
                       tlvCrc, expTlvCrc, silent))
        {
            _lastMsg = "Tlv[" + int2string(tlvIdx) + "] Data Integrity Error - CRC check failed";
            return false;
        }

        tlvAddr += _adbTlvHeader->size/8 + len*4;
        tlvIdx++;
    }

    return true;
}

/************************************
 * Function: configInfo
 ************************************/
bool MlxConfig::configInfo(Flash* /*flash*/, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    printf("FW image configuration info:\n");
    printf("============================\n");

    if (!flashImageInfo.isConfigurable)
    {
        printf("Image isn't configurable\n");
        return false;
    }

    // Todo - need optimization - verify will call loadImageData again
    /*if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }*/

    if (!flashImageInfo.isFailsafe)
    {
        printf("Configuration Section Address: %#x\n", flashImageInfo.configAddr1);
    }
    else
    {
        printf("Configuration Section 1 Address: %#x\n", flashImageInfo.configAddr1);
        printf("Configuration Section 2 Address: %#x\n", flashImageInfo.configAddr2);
    }

    printf("Configuration Section Size: %#x\n", flashImageInfo.configSize);
    printf("Default Profile: %#x\n", flashImageInfo.defPorfile);

    printf("Profiles Json Contents:\n");
    vector<u_int8_t> jsonData;
    if (!op->GetProfileList(&flashImageInfo, jsonData))
    {
        _lastMsg = op->err();
        return false;
    }

    string jsonStr = string((char*)&jsonData[0]);
    if (jsonStr.empty())
    {
        _lastMsg = "Image doesn't contain any profiles info";
        return false;
    }
    printf("%s\n", jsonStr.c_str());


    printf("Tlv Format Adabe Contents:\n");
    vector<u_int8_t> adbData;
    if (!op->GetTlvFormatXML(&flashImageInfo, adbData))
    {
        _lastMsg = op->err();
        return false;
    }

    string adbStr = string((char*)&adbData[0]);
    if (adbStr.empty())
    {
        _lastMsg = "Image doesn't contain any TLVs format info";
        return false;
    }
    printf("%s\n", adbStr.c_str());

    return true;
}

/************************************
 * Function: isConfigPresent
 ************************************/
bool MlxConfig::isConfigPresent(Flash* flash, Operations* /*op*/,
                                Operations::ImageInfo &flashImageInfo,
                                bool &presents, u_int32_t &configVer)
{
    if (!flashImageInfo.imageOk)
    {
     _lastMsg = "FW image is empty or corrupted";
     return false;
    }

    // get cfg section info
    _cfgSize =  flashImageInfo.configSize;
    _cfgAddress[0] = flashImageInfo.configAddr1;
    _cfgAddress[1] = flashImageInfo.configAddr2;

    _isFailSafe = flashImageInfo.isFailsafe;
    if (!_isFailSafe)
    {
     _cfgAddress[0] = _cfgAddress[1];
    }

    int activeIdx;
    if (!getActiveCfgIdx(flash, activeIdx))
    {
        return false;
    }

    presents = activeIdx != -1;
    // get config version
    if (presents)
    {
        u_int32_t dword;
        if (!flash->read_phy(_cfgAddress[activeIdx] + 4, &dword, 4))
        {
            _lastMsg = flash->err();
            return false;
        }

        // Parse the  cfg header
        configVer = htonl(dword) & 0xff;
    }
    return true;
}

/************************************
 * Function: setNonFailSafeCfg
 ************************************/
bool MlxConfig::setNonFailSafeCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo)
{
    u_int32_t zeros = 0;

    if (!flashImageInfo.isConfigurable)
    {
        PRINT_DEBUG("Fw image isn't configurable");
        return true;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }

    // get active section index
    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1 || activeCfgIdx == 1)
    {
        PRINT_DEBUG("no need to move cfg section");
        return true;
    }

    printf("Moving current FW configuration to Non-Fail-Safe sections");
    fflush(stdout);
    u_int8_t buf[_cfgSize];
    // read cfg from section 0
    PRINT_DEBUG("Reading section: 0x%x", _cfgAddress[0]);
    if (!flash->read_phy(_cfgAddress[0], buf, _cfgSize))
    {
        goto failed;
    }

    // erase section 1
    PRINT_DEBUG("Erasing section: 0x%x", _cfgAddress[1]);
    if (!flash->erase_sector_phy(_cfgAddress[1]))
    {
        goto failed;

    }

    // write section 1
    PRINT_DEBUG("Writing %d bytes to cfg section 1", _cfgSize);
    if (!flash->write_phy(_cfgAddress[1]+4, buf+4, _cfgSize-4, true))
    {
        goto failed;
    }

    // activate section 1 - write valid signature to first dword
    if (!flash->write_phy(_cfgAddress[1], buf, 4, true))
    {
        goto failed;
    }

    // invalidate first cfg section
    if (!flash->write_phy(_cfgAddress[0], &zeros, 4, true))
    {
        goto failed;
    }

    printf(" - OK\n");
    return true;

failed:
    _lastMsg = flash->err();
    printf(" - FAILED\n");
    return false;
}

/************************************
 * Function: queryProfile
 ************************************/
bool MlxConfig::queryProfile(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo,
                  u_int32_t &profileID, string &profileName)
{
    profileName = "NONE";

    if (!flashImageInfo.isConfigurable)
    {
        PRINT_DEBUG("Fw image isn't configurable");
        return false;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }

    // get active section index
    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1)
    {
        PRINT_DEBUG("There are no configurations");
        profileID = 0;
        profileName = "Unknown";
        return true;
    }

    // read the current burnt profile
    u_int8_t buf[_adbCfgHeader->size/8];
    if (!flash->read_phy(_cfgAddress[activeCfgIdx], buf, _adbCfgHeader->size/8))
    {
        _lastMsg = flash->err();
        return false;
    }

    // Parse the cfg header
    profileID = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_ID);

    if (profileID == CUSTOM_PROFILE_ID) // No need to reconfigure
    {
        PRINT_DEBUG("Current profile is custom");
        profileName = "Custom";
    }
    else
    {
        profileName = findProfileById(profileID);
    }

    if (profileName.empty())
    {
        _lastMsg = "Can't find profile " + int2string(profileID) + " name";
        return false;
    }
    return true;
}
/************************************
 * Function: checkExistProfileCompat
 ************************************/
bool MlxConfig::checkExistProfileCompat(Flash* flash, Operations* op,
                             Operations::ImageInfo &flashImageInfo,
                             Operations::ImageInfo &newImageInfo,
                             bool& compat)
{
    string profileName = "NONE";
    u_int32_t profileID = 0;

    if (!flashImageInfo.isConfigurable)
    {
        PRINT_DEBUG("Old Fw image isn't configurable");
        goto compatible;
    }

    if (!loadImageData(flash, op, flashImageInfo))
        return false;

    // Todo - need optimization - verify will call loadImageData again
    if (!verifyCfg(flash, op, flashImageInfo, true))
    {
        return false;
    }

    PRINT_DEBUG("Checking new FW image compatibility with existing configurations...");
    // get active section index
    int activeCfgIdx;
    if (!getActiveCfgIdx(flash, activeCfgIdx))
    {
        _lastMsg = "Failed to get the current active configuration: " + _lastMsg;
        return false;
    }

    if (activeCfgIdx == -1)
    {
        PRINT_DEBUG("There are no configurations");
        goto compatible;
    }

    // read the current burnt profile
    u_int8_t buf[_adbCfgHeader->size/8];
    if (!flash->read_phy(_cfgAddress[activeCfgIdx], buf, _adbCfgHeader->size/8))
    {
        _lastMsg = flash->err();
        return false;
    }

    // Parse the cfg header
    profileID = getCfgSectionHeader(buf, CFG_HEADER_PROFILE_ID);
    if (profileID == CUSTOM_PROFILE_ID) // No need to reconfigure
    {
        PRINT_DEBUG("Current profile is custom - it's always compatible");
        goto compatible;
    }

    // find definition for this profile in the current Fw Image json
    // Find the appropriate profile
    profileName = findProfileById(profileID);

    // if new image isn't configurable then it's not compatible (implicitly)
    if (!newImageInfo.isConfigurable)
        goto incompatible;

    // Check whether this profile is supported by new image or not
    for (size_t i = 0; i < newImageInfo.supportedProfList.size(); i++)
    {
        if (newImageInfo.supportedProfList[i] == (u_int32_t)profileID)
            goto compatible;
    }

incompatible:
    PRINT_DEBUG("New FW image is incompatible with existing FW configurations: profile %s (0x%x)!!!",
                profileName.c_str(), profileID);
    compat = false;
    return true;

compatible:
    PRINT_DEBUG("New FW image is compatible with existing FW configurations");
    compat = true;
    return true;
}

/************************************
 * Function: parseProfileDb
 ************************************/
bool MlxConfig::parseProfileDb(const string &jsonTxt)
{
    Json::Value root;
    Json::Reader reader;
    bool  res = reader.parse(jsonTxt, root);
    if (!res)
    {
        _lastMsg = "Failed to parse profiles: " + reader.getFormatedErrorMessages();
        return false;
    }

    Json::Value::Members profileNames = root.getMemberNames();
    for (size_t i = 0; i < profileNames.size(); i++)
    {
        Profile profile;
        string profileName = profileNames[i];

        // Get profile info object
        Json::Value profileObj = root.get(profileName, Json::nullValue);
        if (!profileObj.isObject())
        {
            _lastMsg = "Expected object value in profile: " + profileName + ", not: " + int2string(profileObj.type());
            return false;
        }

        // Get profile version
        int version = profileObj.get("version", -1).asInt();
        if (version == -1)
        {
            _lastMsg = "Missing version for profile: " + profileName;
            return false;
        }

        // Get profile id
        int id = profileObj.get("profile_id", -1).asInt();
        if (id == -1)
        {
            _lastMsg = "Missing profile_id for profile: " + profileName;
            return false;
        }

        // Get tlvs list
        Json::Value tlvsObj = profileObj.get("tlvs", Json::nullValue);
        if (!tlvsObj.isArray())
        {
            _lastMsg = "Expected object tlv to be array in profile: " + profileName + ", not: " + int2string(tlvsObj.type());
            return false;
        }

        // Go over all tlvs
        for (size_t j = 0; j < tlvsObj.size(); j++)
        {
            Tlv tlv;

            Json::Value tlvObj = tlvsObj.get(j, Json::nullValue);
            if (!tlvObj.isObject())
            {
                _lastMsg = "expected object value for tlv[: " + int2string(j) + "] profile: " + profileName + ", not: " + int2string(tlvObj.type());
                return false;
            }

            if (!tlvObj.isMember("TLV_NAME"))
            {
                _lastMsg = "Missing TLV_NAME in value object for tlv[: " + int2string(j) + "] profile: " + profileName;
                return false;
            }
            tlv.name = tlvObj.get("TLV_NAME", Json::nullValue).asString();

            // Get tlv fields/value object
            Json::Value::Members fieldsNames = tlvObj.getMemberNames();
            for (size_t k = 0; k < fieldsNames.size(); k++)
            {
                Pair pair;
                pair.key = fieldsNames[k];
                if (fieldsNames[k] == "TLV_NAME")
                    continue;

                Json::Value val = tlvObj.get(fieldsNames[k], Json::nullValue);
                if (val.isIntegral())
                {
                    pair.value = int2string(val.asInt());
                }
                else if (val.isString())
                {
                    pair.value = val.asString();
                }
                else
                {
                    _lastMsg = "expected int/string value for field: " + fieldsNames[k] + " tlv[: " +
                                int2string(j) + "] profile: " + profileName + ", not: " + int2string(tlvObj.type());
                    return false;
                }
                tlv.fields.push_back(pair);
            }

            profile.tlvs.push_back(tlv);
        }

        // add the new Profile to the profiles map
        profile.id = id;
        profile.version = version;

        _profilesMap[profileName] = profile;
    }

    return true;
}

/************************************
 * Function: checkOldFW
 ************************************/
bool MlxConfig::checkOldFW(Operations::ImageInfo &flashImageInfo)
{
    // If this the FW that was sent to HP then we need exit and let user run the old mlxconfig tool
    // This is because tof he major changes in mlxconfig definitions.
    Operations::ImageInfo info;
    if (flashImageInfo.fwVer[0] == 2 &&
        flashImageInfo.fwVer[1] == 10 &&
       (flashImageInfo.fwVer[2] == 0 || flashImageInfo.fwVer[2] == 1000))
    {
        _lastMsg = "You're FW version: " + int2string(flashImageInfo.fwVer[0]) + "." +\
                                           int2string(flashImageInfo.fwVer[1]) + "." +\
                                           int2string(flashImageInfo.fwVer[2]) +
                   " is too old for this tool, consider updating to newer FW or use the old \"mlxconfig\" instead";
        return false;
    }

    return true;
}

/************************************
 * Function: getActiveCfgIdx
 ************************************/
bool MlxConfig::getActiveCfgIdx(Flash* flash, int& idx) // -1 means no active configuration
{
    u_int32_t data0, data1;
    // Read first dword from cfg0
    PRINT_DEBUG("Reading first dword from : 0x%x and 0x%x", _cfgAddress[0], _cfgAddress[1]);
    if (!flash->read_phy(_cfgAddress[0], &data0) ||
        !flash->read_phy(_cfgAddress[1], &data1))
    {
        _lastMsg = flash->err();
        return false;
    }
    PRINT_DEBUG("0x%x - 0x%x", data0, data1);

    if (ntohl(data0) == CFG_SIGNATURE)
        idx = 0;
    else if (ntohl(data1) == CFG_SIGNATURE)
        idx = 1;
    else
        idx = -1;
    return true;
}

/************************************
 * Function: setTlvHeader
 ************************************/
void MlxConfig::setTlvHeader(u_int8_t* buf, enum TlvHeaderField field, u_int32_t value)
{
    AdbInstance* f;

    switch (field)
    {
    case TLV_HEADER_LENGTH:
        f = _adbTlvHeader->getChildByPath("length");
        break;
    case TLV_HEADER_ID:
        f = _adbTlvHeader->getChildByPath("id");
        break;
    case TLV_HEADER_CRC:
        f = _adbTlvHeader->getChildByPath("crc16");
        break;
    case TLV_HEADER_VERSION:
        f = _adbTlvHeader->getChildByPath("version");
        break;
    default:
        assert(0);
    }

    f->pushBuf(buf, value);
}

/************************************
 * Function: getTlvHeader
 ************************************/
u_int32_t MlxConfig::getTlvHeader(u_int8_t* buf, enum TlvHeaderField field)
{
    AdbInstance* f;

    switch (field)
    {
    case TLV_HEADER_LENGTH:
        f = _adbTlvHeader->getChildByPath("length");
        break;
    case TLV_HEADER_ID:
        f = _adbTlvHeader->getChildByPath("id");
        break;
    case TLV_HEADER_CRC:
        f = _adbTlvHeader->getChildByPath("crc16");
        break;
    case TLV_HEADER_VERSION:
        f = _adbTlvHeader->getChildByPath("version");
        break;
    default:
        assert(0);
    }

    return f->popBuf(buf);
}

/************************************
 * Function: setCfgSectionHeader
 ************************************/
void MlxConfig::setCfgSectionHeader(u_int8_t* buf, enum CfgHeaderField field, u_int32_t value)
{
    AdbInstance* f;

    switch (field)
    {
    case CFG_HEADER_SIGNATURE:
        f = _adbCfgHeader->getChildByPath("signature");
        break;
    case CFG_HEADER_MAX_LEN:
        f = _adbCfgHeader->getChildByPath("max_len");
        break;
    case CFG_HEADER_VERSION:
        f = _adbCfgHeader->getChildByPath("version");
        break;
    case CFG_HEADER_PROFILE_ID:
        f = _adbCfgHeader->getChildByPath("profile_id");
        break;
    case CFG_HEADER_PROFILE_VER:
        f = _adbCfgHeader->getChildByPath("profile_ver");
        break;
    case CFG_HEADER_CRC:
        f = _adbCfgHeader->getChildByPath("crc16");
        break;
    default:
        assert(0);
    }

    f->pushBuf(buf, value);
}

/************************************
 * Function: getCfgSectionHeader
 ************************************/
u_int32_t MlxConfig::getCfgSectionHeader(u_int8_t* buf, enum CfgHeaderField field)
{
    AdbInstance* f;

    switch (field)
    {
    case CFG_HEADER_SIGNATURE:
        f = _adbCfgHeader->getChildByPath("signature");
        break;
    case CFG_HEADER_MAX_LEN:
        f = _adbCfgHeader->getChildByPath("max_len");
        break;
    case CFG_HEADER_VERSION:
        f = _adbCfgHeader->getChildByPath("version");
        break;
    case CFG_HEADER_PROFILE_ID:
        f = _adbCfgHeader->getChildByPath("profile_id");
        break;
    case CFG_HEADER_PROFILE_VER:
        f = _adbCfgHeader->getChildByPath("profile_ver");
        break;
    case CFG_HEADER_CRC:
        f = _adbCfgHeader->getChildByPath("crc16");
        break;
    default:
        assert(0);
    }

    return f->popBuf(buf);
}

/************************************
 * Function: calcBECrc16
 ************************************/
u_int16_t MlxConfig::calcBECrc16(const u_int32_t* buf, int num_of_dwords)
{
    Crc16 crc;
    for (int i = 0; i < num_of_dwords; i++)
    {
        crc << ntohl(buf[i]);
    }
    crc.finish();

    return crc.get();
}

/************************************
 * Function: MlxConfig::getTlvById
 ************************************/
AdbInstance* MlxConfig::getTlvById(int id)
{
    for (size_t i = 0; i < _adbRoot->subItems.size(); i++)
    {
        int tlvId;
        if (!getTlvNodeId(_adbRoot->subItems[i], tlvId))
            return NULL;

        if (tlvId == id)
            return _adbRoot->subItems[i];
    }

    return NULL;
}

/************************************
 * Function: getTlvNodeId
 ************************************/
bool MlxConfig::getTlvNodeId(AdbInstance* node, int &tlvId)
{
    string tlvIdAttr = node->getAttr("tlv_id");
    assert(!tlvIdAttr.empty());

    errno = 0;
    tlvId = strtoul(tlvIdAttr.c_str(), 0, 0);
    if (tlvId == 0 && errno == ERANGE)
    {
       _lastMsg = string("The given tlv id for: ") + node->name + " is invalid";
       return false;
    }

    if (tlvId < 0 || tlvId > (int)LAST_TLV_ID)
    {
       _lastMsg = string("The given tlv id:") + tlvIdAttr + " for: " + node->name + " is out of range";
       return false;
    }

    return true;
}

/************************************
 * Function: getTlvVersion
 ************************************/
bool MlxConfig::getTlvVersion(AdbInstance* node, int &version)
{
    version = 0;

    // Go over all fields
    for (size_t i = 0; i < node->subItems.size(); i++)
    {
        AdbInstance* field = node->subItems[i];
        string minVerAttr = field->getAttr("min_ver");
        int fieldMinVer = 0;

        if (minVerAttr.empty())
        {
            fieldMinVer = 0;
        }
        else
        {
            errno = 0;
            fieldMinVer = strtoul(minVerAttr.c_str(), 0, 0);
            if (fieldMinVer == 0 && errno == ERANGE)
            {
               _lastMsg = string("The given min_ver for field: ") + field->fullName() +
                                 " within node: " + node->name + " is invalid";
               return false;
            }
        }

        // set version to the maximum between current version and current field
        version = version > fieldMinVer ? version : fieldMinVer;
    }

    return true;
}

/************************************
 * Function: getFieldIntValue
 ************************************/
bool MlxConfig::getFieldIntValue(string strVal, AdbInstance* field, u_int64_t &intVal)
{
    char* p;
    intVal = strtoul(strVal.c_str(), &p, 0);

    if (*p != 0) // Enum
    {
        if (!field->enumToInt(strVal, intVal))
        {
            _lastMsg = "Can't find enum (" + strVal + ") value for field: " + field->fullName();
            return false;
        }
    }

    return true;
}

/************************************
 * Function: findProfileById
 ************************************/
string MlxConfig::findProfileById(u_int32_t profileID)
{
    map<string, Profile>::iterator it;

    for (it = _profilesMap.begin(); it != _profilesMap.end(); it++)
    {
        if (it->second.id == profileID)
        {
            return it->first;
        }
    }
    return string();
}

/************************************
 * Function: printProfileDB
 ************************************/
void MlxConfig::printProfileDB()
{
    map<string, Profile>::iterator iter;

    for (iter = _profilesMap.begin(); iter != _profilesMap.end(); iter++)
    {
        cout << "Profile: " << iter->first << ", ";
        iter->second.print();
        cout << endl;
    }
}

/************************************
 * Function: getLastError
 ************************************/
std::string MlxConfig::getLastError() const
{
    return _lastMsg;
}

/************************************
 * Function: crcVerify
 ************************************/
bool MlxConfig::crcVerify(u_int32_t startAddr, u_int32_t size, string title,
                    u_int32_t crc, u_int32_t expectedCrc, bool silent)
{
    if (!silent)
        printf(CRC_CHECK_OUTPUT, PRE_CRC_OUTPUT, startAddr, startAddr + size - 1, size, title.c_str());
    if (crc == expectedCrc)
    {
        if (!silent)
            printf(" - OK\n");
        return true;
    }
    else
    {
        if (!silent)
            printf(" - wrong CRC (exp:0x%x, act:0x%x)\n", expectedCrc, crc);
        return false;
    }
}
