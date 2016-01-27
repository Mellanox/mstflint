/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <errno.h>
#include <utility>

#include <common/tools_version.h>

#include "mlxcfg_ui.h"

using namespace std;


#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#define IDENT4 IDENT2 IDENT



static void printFlagLine(string flag_s, string flag_l, string param, string desc)
{
    printf(IDENT2"-%s|--%s", flag_s.c_str(), flag_l.c_str());
    if (param.length()) {
        printf(" <%s>", param.c_str());
    } else if (flag_l.length() < 8){
        printf("\t");
    }
    printf(IDENT3": %s\n", desc.c_str());
}

#ifdef MTCR_UL
#define DEVICE_NAME "device"
#else
#define DEVICE_NAME "mst device"
#endif

void MlxCfg::printHelp(bool longDesc)
{
    // print opening
    printf(IDENT"NAME:\n"
           IDENT2   MLXCFG_NAME"\n"
           IDENT"SYNOPSIS:\n"
           IDENT2    MLXCFG_NAME " [-d <%s> ] [-y|-e] <s[et] <parameters to set>|q[uery]|r[eset]>\n", DEVICE_NAME);

    // print options
    printf("\n");
    printf(IDENT"OPTIONS:\n");
    printFlagLine("d", "dev", "device", "Perform operation for a specified mst device.");
    printFlagLine("f", "file", "conf_file", "raw configuration file.");
    printFlagLine("h", "help", "", "Display help message.");
    printFlagLine("hh", "full_help", "", "Display full help message.");
    printFlagLine("v", "version", "", "Display version info.");
    printFlagLine("e", "show_default", "", "Show default configurations.");
    printFlagLine("y", "yes", "", "Answer yes in prompt.");

    //print commands
    printf("\n");
    printf(IDENT"COMMANDS:\n");
    printf(IDENT2"%-24s : %s\n","clear_semaphore", "clear the tool semaphore.");
    printf(IDENT2"%-24s : %s\n","q[uery]", "query current supported configurations.");
    printf(IDENT2"%-24s : %s\n","r[eset]", "reset all configurations to their default value.");
    printf(IDENT2"%-24s : %s\n","s[et]", "set configurations to a specific device.");
    printf(IDENT2"%-24s : %s\n","set_raw", "set raw configuration file.(5th generation devices only.)");

    // print supported commands
    printf("\n");
    printf(IDENT"Supported Configurations:\n");
    printf("\n");

    if(longDesc) {
        _allInfo.printLongDesc();
    } else {
        _allInfo.printShortDesc();
    }

    // print usage examples
    printf("\n");
    printf(IDENT"Examples:\n");
    printf(IDENT2"%-35s: %s\n", "To query current configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" query");
    printf(IDENT2"%-35s: %s\n", "To set configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" set SRIOV_EN=1 NUM_OF_VFS=16 WOL_MAGIC_EN_P1=1");
    printf(IDENT2"%-35s: %s\n", "To set raw configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE2" -f conf_file set_raw");
    printf(IDENT2"%-35s: %s\n", "To reset configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" reset");
    printf("\n");
    printf(IDENT"Supported devices:\n");
    printf(IDENT2"4th Generation devices: ConnectX3, ConnectX3-Pro (FW 2.31.5000 and above).\n");
    printf(IDENT2"5th Generation devices: ConnectIB, ConnectX4, ConnectX4-LX.\n");
    printf("\n");
    printf(IDENT"Note: query device to view supported configurations.\n");
    printf("\n");
}

void MlxCfg::printVersion()
{
    print_version_string(MLXCFG_NAME, "");
}

void MlxCfg::printUsage() {
    printf("\n"IDENT"Usage:\n"
           IDENT2    MLXCFG_NAME " [-d <%s> ] [-y|-e] <s[et] <parameters to set>|q[uery]|r[eset]>\n\n", DEVICE_NAME);
}

bool MlxCfg::tagExsists(mlxCfgParam tag) {
    for (std::vector<cfgInfo>::iterator it = _mlxParams.params.begin() ; it != _mlxParams.params.end(); it++) {
        if (it->first == tag) {
            return true;
        }
    }
    return false;
}

mlxCfgStatus MlxCfg::processArg(string tag, u_int32_t val)
{
    int i;
    std::vector<cfgInfo>::iterator it;
    for ( i = (int)Mcp_Sriov_En ; i < (int)Mcp_Last ; i++) {
        if (tag == MlxCfgParams::param2str[i]) {
            if (tagExsists((mlxCfgParam)i)) {
                return err(true, "Duplicate parameter, %s.", tag.c_str());
            }
            _mlxParams.params.push_back(cfgInfo((mlxCfgParam)i, val));
            break;
        }
    }
    if (i == Mcp_Last) {
        return err(true, "Unknown Parameter: %s", tag.c_str());
    }
    return MLX_CFG_OK;
}


static bool strToNum(string str, u_int32_t& num, int base=0)
{
    char *endp;
    char* numStr = strcpy(new char[str.size() + 1],str.c_str());
    num = strtoul(numStr, &endp, base);
    if (*endp) {
        delete[] numStr;
        return false;
    }
    delete[] numStr;
    // check errno
    if (errno == ERANGE) {
        return false;
    }
    return true;
}

mlxCfgStatus MlxCfg::extractCfgArgs(int argc, char* argv[])
{
    int i = 0;
    string tag;
    string valstr;
    u_int32_t val = 0;
    mlxCfgParam param = Mcp_Last;
    for (;i < argc;i++) {
        char* ptr;
        // get the tag
        ptr = strtok(argv[i], "=");
        if (!ptr) {
            return err(true, "invalid Configuration argument %s", argv[i]);
        }
        tag = ptr; // hopefully its calling copy function.
        // get the val
        ptr = strtok(NULL, "=");
        if (!ptr) {
            return err(true, "invalid Configuration argument %s", argv[i]);
        }
        valstr = ptr;
        if (strtok(NULL, "=")) {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }

        if(_allInfo.parseParam(tag, valstr, val, param)) {
            if(param == Mcp_Last) {
                return err(true, "Unknown Parameter: %s", tag.c_str());
            } else {
                return err(true, "Failed to parse %s=%s", tag.c_str(), valstr.c_str());
            }
        }

        if(tagExsists(param)) {
            return err(true, "Duplicate parameter, %s.", tag.c_str());
        }
        _mlxParams.params.push_back(cfgInfo((mlxCfgParam)param, val));
    }
    return MLX_CFG_OK;
}



mlxCfgStatus MlxCfg::parseArgs(int argc, char* argv[])
{
    int i = 1;
    for (; i<argc; i++) {
        string arg = argv[i];
        if (arg == "-v" || arg == "--version") {
            printVersion();
            return MLX_CFG_OK_EXIT;
        } else if (arg == "-h" || arg == "--help"){
            printHelp();
            return MLX_CFG_OK_EXIT;
        } else if (arg == "-hh" || arg == "--full_help"){
            printHelp(true);
            return MLX_CFG_OK_EXIT;
        } else if (arg == "-d" || arg == "--dev") {
            if (++i == argc) {
                return err(true, "missing device name");
            }
            _mlxParams.device = argv[i];
        } else if (arg == "-y" || arg == "--yes") {
            _mlxParams.yes = true;
        } else if (arg == "-f" || arg == "--file") {
            if (++i == argc) {
                return err(true, "missing file name");
            }
            _mlxParams.rawTlvFile = argv[i];
        } else if (arg == "-e" || arg == "--show_default") {
            _mlxParams.showDefault = true;
        }else if (arg == "set" || arg == "s") {
            _mlxParams.cmd = Mc_Set;
            break;

        } else if (arg == "query" || arg == "q") {
            _mlxParams.cmd = Mc_Query;
            break;

        } else if (arg == "reset" || arg == "r") {
            _mlxParams.cmd = Mc_Reset;
            break;

        } else if (arg == "clear_semaphore") {
            _mlxParams.cmd = Mc_Clr_Sem;
            break;
        } else if (arg == "set_raw") {
            _mlxParams.cmd = Mc_Set_Raw;
            break;
        // hidden flag --force used to ignore parameter checks
        }else if (arg == "--force"){
            _mlxParams.force = true;
        } else {
            return err(true, "invalid argument: %s", arg.c_str());
        }
    }
    i++;
    if (_mlxParams.cmd == Mc_UnknownCmd) {
        return err(true, "No command found. For more information please run "MLXCFG_NAME" -h|--help.");
    }
    // we parsed input until the set/query/reset cmd
    if (i == argc && _mlxParams.cmd == Mc_Set) {
        return err(true, "missing configuration arguments. For more information please run "MLXCFG_NAME" -h|--help.");
    }
    if (i != argc && (_mlxParams.cmd == Mc_Reset || _mlxParams.cmd == Mc_Query)) {
        return err(true, "%s command expects no argument but %d argument recieved", (_mlxParams.cmd == Mc_Reset) ? "reset" : "query", argc -i);
    }
    if ((_mlxParams.cmd == Mc_Set || _mlxParams.cmd == Mc_Clr_Sem || _mlxParams.cmd == Mc_Set_Raw) && _mlxParams.device.length() == 0) {
        return err(true, "%s command expects device to be specified.", _mlxParams.cmd == Mc_Set ? "set" : _mlxParams.cmd == Mc_Set_Raw ? "set_raw" : "clear_semaphore");
    }
    if ((_mlxParams.cmd == Mc_Set_Raw && _mlxParams.rawTlvFile.size() == 0 )) {
        return err(true, "set_raw command expects raw TLV file to be specified.");
    }
    if ((_mlxParams.cmd != Mc_Set_Raw && _mlxParams.rawTlvFile.size() != 0 )) {
        return err(true, "raw TLV file can only be specified with set_raw command.");
    }

    return extractCfgArgs(argc-i, &(argv[i]));
}

mlxCfgStatus MlxCfgParamParser::parseUserInput(string input, u_int32_t& val)
{
    std::map<string, u_int32_t>::iterator it;
    //first check if it is a numeric value
    if(strToNum(input, val, 0)) {
        return MLX_CFG_OK;
    }
    for(it = _strMap.begin(); it != _strMap.end(); it++){
        if(compareVal(it->first, input)){
            val = it->second;
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

string MlxCfgParamParser::getShortDescStrAux()
{
    string s;
    std::map<string, u_int32_t>::iterator it;

    s = _name + "=<";

    if(_strMap.size() == 0) {
        s += _allowedValues;
    } else {
        //printf first str
        it = _strMap.begin();
        s += it->first;
        it++;
        for(; it != _strMap.end(); it++)
        {
            s += "|";
            s += it->first;
        }
    }

    s += ">";
    return s;
}

void MlxCfgParamParser::printShortDesc()
{
    printf(IDENT4"%s\n", getShortDescStrAux().c_str());
}

void MlxCfgParamParser::splitAndPrintDesc(string desc)
{
    if(desc.length() > 129) {
        //find index of last space in first 129 chars and split there
        int i = desc.substr(0, 129).find_last_of(' ');
        string desc2 = desc.substr(i, (desc.length() - i));
        printf(IDENT4"%-46s   %s\n", "", desc.substr(0, i).c_str());
        splitAndPrintDesc(desc2);
    } else {
        printf(IDENT4"%-46s   %s\n", "", desc.c_str());
    }
}

bool MlxCfgParamParser::compareVal(string a, string b)
{
    if(a.length() != b.length()){
        return false;
    }

    for(unsigned int i = 0; i < a.length(); i++) {
        if(tolower(a[i]) != tolower(b[i])){
            return false;
        }
    }

    return true;
}

void MlxCfgParamParser::printLongDesc()
{
    string shortDesc = getShortDescStrAux();
    if(_desc.length() > 129) {
        //find index of last space in first 129 chars and split there
        int i = _desc.substr(0, 129).find_last_of(' ');
        string desc2 = _desc.substr(i, (_desc.length() - i));
        printf(IDENT4"%-46s : %s\n", shortDesc.c_str(), _desc.substr(0, i).c_str());
        splitAndPrintDesc(desc2);
    } else {
        printf(IDENT4"%-46s : %s\n", shortDesc.c_str(), _desc.c_str());
    }
}

string MlxCfgParamParser::getStrVal(u_int32_t val){
    std::map<string, u_int32_t>::iterator it;
    if(val == MLXCFG_UNKNOWN) {
        return "MLXCFG_UNKNOWN";
    }
    if(_strMap.size() == 0) {
        return "";
    } else {
        for(it = _strMap.begin(); it != _strMap.end(); it++){
            if(val == it->second){
                return it->first;
            }
        }
        //not a legal value, print it as it
        return "";
    }
}

bool mlxCfgParamParserCompare(MlxCfgParamParser a, MlxCfgParamParser b)
{
    return a.getName() < b.getName();
}

vector<MlxCfgParamParser> MlxCfgInfo::getParamsMapValues()
{
    vector<MlxCfgParamParser> vals;
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it;
    for(it = _params.begin(); it != _params.end(); it++)
    {
        vals.push_back(it->second);
    }
    return vals;
}

void MlxCfgInfo::printShortDesc()
{
    printf("\n");
    printf(IDENT2"%s: %s\n",_name.c_str(), _title.c_str());

    vector<MlxCfgParamParser> vals = getParamsMapValues();
    std::sort(vals.begin(), vals.end(), mlxCfgParamParserCompare);

    for(unsigned int i = 0; i < vals.size(); i++)
    {
        vals[i].printShortDesc();
    }
}

void MlxCfgInfo::printLongDesc()
{
    printf("\n");
    printf(IDENT2"%s: %s\n",_name.c_str(), _title.c_str());

    vector<MlxCfgParamParser> vals = getParamsMapValues();
    std::sort(vals.begin(), vals.end(), mlxCfgParamParserCompare);

    for(unsigned int i = 0; i < vals.size(); i++)
    {
        vals[i].printLongDesc();
    }
}

mlxCfgStatus MlxCfgInfo::getParamParser(mlxCfgParam p, MlxCfgParamParser& paramParser)
{
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it = _params.find(p);
    if(it == _params.end()) {
        return MLX_CFG_ERROR;
    }
    paramParser = it->second;
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfgInfo::getParamParser(string name, MlxCfgParamParser& paramParser)
{
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it;
    for(it = _params.begin(); it != _params.end(); it++)
    {
        if(name == it->second.getName()) {
            paramParser = it->second;
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

MlxCfgInfo MlxCfgAllInfo::createPciSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Fpp_En] = MlxCfgParamParser(Mcp_Fpp_En, "FPP_EN", "Enable function per port", paramMap);
    params[Mcp_Log_Bar_Size] = MlxCfgParamParser(Mcp_Log_Bar_Size, "LOG_BAR_SIZE", "example: for 8Mb bar size set LOG_BAR_SIZE=3 (4th Generation)", "base_2_log_in_mb");
    params[Mcp_Sriov_En] = MlxCfgParamParser(Mcp_Sriov_En, "SRIOV_EN", "Enable SR-IOV", paramMap);
    params[Mcp_PF_Log_Bar_Size] = MlxCfgParamParser(Mcp_PF_Log_Bar_Size, "PF_LOG_BAR_SIZE", "example: for 8Mb bar size set PF_LOG_BAR_SIZE=3 (5th Generation)", "base_2_log_in_mb");
    params[Mcp_VF_Log_Bar_Size] = MlxCfgParamParser(Mcp_VF_Log_Bar_Size, "VF_LOG_BAR_SIZE", "example: for 8Mb bar size set VF_LOG_BAR_SIZE=3 (5th Generation)", "base_2_log_in_mb");
    params[Mcp_Num_Of_Vfs] = MlxCfgParamParser(Mcp_Num_Of_Vfs, "NUM_OF_VFS", "desired amount of virtual functions", "NUM");
    params[Mcp_Num_Pf_Msix] = MlxCfgParamParser(Mcp_Num_Pf_Msix, "NUM_PF_MSIX", "Number of MSI-X vectors and EQs per PF (5th Generation)", "NUM");
    params[Mcp_Num_Vf_Msix] = MlxCfgParamParser(Mcp_Num_Vf_Msix, "NUM_VF_MSIX", "Number of MSI-X vectors and EQs per VF (5th Generation)", "NUM");
    return MlxCfgInfo("PCI Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createIBDynamicallyConnect()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //IB Dynamically Connect
    params[Mcp_Dcr_Lifo_Size] = MlxCfgParamParser(Mcp_Dcr_Lifo_Size, "DCR_LIFO_SIZE", "The amount of total DCRs available to join linked-lists after hash DCRs", "SIZE");
    params[Mcp_Log_Dcr_Hash_Table_Size] = MlxCfgParamParser(Mcp_Log_Dcr_Hash_Table_Size, "LOG_DCR_HASH_TABLE_SIZE", "log2 of the hash table size minus 1", "SIZE");
    return MlxCfgInfo("IB Dynamically Connect", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createInfinibandBootSettings()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Infiniband Boot Settings
    params[Mcp_Boot_Pkey_P1] = MlxCfgParamParser(Mcp_Boot_Pkey_P1, "BOOT_PKEY_P1", "partition key to be used by PXE boot (ConnectX3, ConnectX3-Pro Only)", "PKEY");
    params[Mcp_Boot_Pkey_P2] = MlxCfgParamParser(Mcp_Boot_Pkey_P2, "BOOT_PKEY_P2", "set 0 for default", "PKEY");
    return MlxCfgInfo("Infiniband Boot Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createInternalSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Internal Settings
    paramMap["Auto"] = 0;
    paramMap["4KB"] = 12;
    params[Mcp_Log_Tpt_Size] = MlxCfgParamParser(Mcp_Log_Tpt_Size, "INT_LOG_MAX_PAYLOAD_SIZE", """Burst length", paramMap);
    return MlxCfgInfo("Internal Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createPrebootBootSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Preboot Boot Settings
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Boot_Option_Rom_En_P1] = MlxCfgParamParser(Mcp_Boot_Option_Rom_En_P1, "BOOT_OPTION_ROM_EN_P1", "Disable/Enable boot option ROM", paramMap);
    params[Mcp_Boot_Option_Rom_En_P2] = MlxCfgParamParser(Mcp_Boot_Option_Rom_En_P2, "BOOT_OPTION_ROM_EN_P2", "", paramMap);
    params[Mcp_Boot_Vlan_En_P1] = MlxCfgParamParser(Mcp_Boot_Vlan_En_P1, "BOOT_VLAN_EN_P1", "Disable/Enable VLAN mode for network boot", paramMap);
    params[Mcp_Boot_Vlan_En_P2] = MlxCfgParamParser(Mcp_Boot_Vlan_En_P2, "BOOT_VLAN_EN_P2", "", paramMap);
    params[Mcp_Boot_Retry_Cnt_P1] = MlxCfgParamParser(Mcp_Boot_Retry_Cnt_P1, "BOOT_RETRY_CNT_P1", "Number of retries to attempt in case of boot failure. 7 indicates infinite retries.", "0..7");
    params[Mcp_Boot_Retry_Cnt_P2] = MlxCfgParamParser(Mcp_Boot_Retry_Cnt_P2, "BOOT_RETRY_CNT_P2", "", "0..7");
    paramMap.clear();
    paramMap["None"] = 0;
    paramMap["PXE"] = 1;
    paramMap["iSCSI"] = 2;
    paramMap["Both"] = 3;
    params[Mcp_Legacy_Boot_Protocol_P1] = MlxCfgParamParser(Mcp_Legacy_Boot_Protocol_P1, "LEGACY_BOOT_PROTOCOL_P1", "None: disable legacy boot. PXE: DHCP/TFTP boot. Both: PXE and iSCSI", paramMap);
    params[Mcp_Legacy_Boot_Protocol_P2] = MlxCfgParamParser(Mcp_Legacy_Boot_Protocol_P2, "LEGACY_BOOT_PROTOCOL_P2", "", paramMap);
    params[Mcp_Boot_Vlan_P1] = MlxCfgParamParser(Mcp_Boot_Vlan_P1, "BOOT_VLAN_P1", "VLAN ID for the network boot", "VLAN ID");
    params[Mcp_Boot_Vlan_P2] = MlxCfgParamParser(Mcp_Boot_Vlan_P2, "BOOT_VLAN_P2", "", "VLAN ID");
    return MlxCfgInfo("Preboot Boot Settings", "Settings that control the legacy option ROM", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCECongestionControlECN()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE Congestion Control ECN
    params[Mcp_Clamp_Tgt_Rate_P1] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_P1, "CLAMP_TGT_RATE_P1","If set, whenever a CNP is processed,"
                  " the target rate is updated to be the current rate. Default=1"
              ,"0|1");
    params[Mcp_Clamp_Tgt_Rate_P2] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_P2, "CLAMP_TGT_RATE_P2","","0|1");
    params[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1, "CLAMP_TGT_RATE_AFTER_TIME_INC_P1",
                "When receiving an CNP, the target rate should"
                    " be updated if the transmission rate was increased"
                    " due to the timer, and not only due to the byte counter"". Default=1"
                ,"0|1");
    params[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2, "CLAMP_TGT_RATE_AFTER_TIME_INC_P2","","0|1");
    params[Mcp_Rpg_Time_Reset_P1] = MlxCfgParamParser(Mcp_Rpg_Time_Reset_P1, "RPG_TIME_RESET_P1"
              ,"Time between rate increases if no CNPs are received. Given in u-seconds. Default=2"
              ,"USEC");
    params[Mcp_Rpg_Time_Reset_P2] = MlxCfgParamParser(Mcp_Rpg_Time_Reset_P2, "RPG_TIME_RESET_P2","","USEC");
    params[Mcp_Rpg_Byte_Reset_P1] = MlxCfgParamParser(Mcp_Rpg_Byte_Reset_P1, "RPG_BYTE_RESET_P1"
              ,"Transmitted data between rate increases if no CNPs are received. Given in Bytes. "
               "Disabled=0, Default=150"
              ,"BYTE_NUM");
    params[Mcp_Rpg_Byte_Reset_P2] = MlxCfgParamParser(Mcp_Rpg_Byte_Reset_P2, "RPG_BYTE_RESET_P2","","BYTE_NUM");
    params[Mcp_Rpg_Threshold_P1] = MlxCfgParamParser(Mcp_Rpg_Threshold_P1, "RPG_THRESHOLD_P1"
             ,"The number of times rpByteStage or rpTimeStage can count before the RP rate control "
              "state machine advances states. Default=5"
             ,"0..31");
    params[Mcp_Rpg_Threshold_P2] = MlxCfgParamParser(Mcp_Rpg_Threshold_P2, "RPG_THRESHOLD_P2","","0..31");
    params[Mcp_Rpg_Max_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Max_Rate_P1, "RPG_MAX_RATE_P1"
            ,"The maximum rate, in Mbits per second, at which an RP can transmit. "
             "Once this limit is reached, the RP rate limited is released and "
             "the flow is not rate limited any more. Default=0 (Full port speed)."
            ,"RATE_IN_MBIT");
    params[Mcp_Rpg_Max_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Max_Rate_P2, "RPG_MAX_RATE_P2","","RATE_IN_MBIT");
    params[Mcp_Rpg_Ai_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Ai_Rate_P1, "RPG_AI_RATE_P1","The rate, in Mbits per second,"
            " used to increase rpTargetRate in the RPR_ACTIVE_INCREASE state."
            " Default=10."
           ,"RATE_IN_MBIT");
    params[Mcp_Rpg_Ai_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Ai_Rate_P2, "RPG_AI_RATE_P2","","RATE_IN_MBIT");
    params[Mcp_Rpg_Hai_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Hai_Rate_P1, "RPG_HAI_RATE_P1"
            ,"The rate, in Mbits per second, used to increase rpTargetRate in the RPR_HYPER_INCREASE state."
             " Default=50"
            ,"RATE_IN_MBIT");
    params[Mcp_Rpg_Hai_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Hai_Rate_P2, "RPG_HAI_RATE_P2","","RATE_IN_MBIT");
    params[Mcp_Rpg_Gd_P1] = MlxCfgParamParser(Mcp_Rpg_Gd_P1, "RPG_GD_P1"
            ,"If a CNP is received, the flow rate is reduced at the beginning of the next rate_reduce_monitor_period interval to,"
             "(1-Alpha/Gd)*CurrentRate. RPG_GD is given as log2(Gd), where Gd may only be powers of 2. Default=7."
            ,"0..15");
    params[Mcp_Rpg_Gd_P2] = MlxCfgParamParser(Mcp_Rpg_Gd_P2, "RPG_GD_P2","","0..15");
    params[Mcp_Rpg_Min_Dec_Fac_P1] = MlxCfgParamParser(Mcp_Rpg_Min_Dec_Fac_P1, "RPG_MIN_DEC_FAC_P1"
            ,"The minimum factor by which the current transmit rate can be changed when processing a CNP."
             "Value is given as a percentage (1-100). Default=50."
            ,"1..100");
    params[Mcp_Rpg_Min_Dec_Fac_P2] = MlxCfgParamParser(Mcp_Rpg_Min_Dec_Fac_P2, "RPG_MIN_DEC_FAC_P2","","1..100");
    params[Mcp_Rpg_Min_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Min_Rate_P1, "RPG_MIN_RATE_P1"
            ,"The minimum value, in Mb per second, for rate to limit. Default=2000"
            ,"RATE_IN_MBIT");
    params[Mcp_Rpg_Min_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Min_Rate_P2, "RPG_MIN_RATE_P2","","RATE_IN_MBIT");
    params[Mcp_Rate_To_Set_On_First_Cnp_P1] = MlxCfgParamParser(Mcp_Rate_To_Set_On_First_Cnp_P1, "RATE_TO_SET_ON_FIRST_CNP_P1"
            ,"The rate that is set for the flow when a rate limiter is allocated to it upon first CNP received, in Mbps. "
             "Default=0"
            ,"RATE_IN_MBIT");
    params[Mcp_Rate_To_Set_On_First_Cnp_P2] = MlxCfgParamParser(Mcp_Rate_To_Set_On_First_Cnp_P2, "RATE_TO_SET_ON_FIRST_CNP_P2","","RATE_IN_MBIT");
    params[Mcp_Dce_Tcp_G_P1] = MlxCfgParamParser(Mcp_Dce_Tcp_G_P1, "DCE_TCP_G_P1"
            ,"Used to update the congestion estimator (alpha) once every dce_tcp_rtt microseconds. Default=64"
            ,"NUM");
    params[Mcp_Dce_Tcp_G_P2] = MlxCfgParamParser(Mcp_Dce_Tcp_G_P2, "DCE_TCP_G_P2","","NUM");
    params[Mcp_Dce_Tcp_Rtt_P1] = MlxCfgParamParser(Mcp_Dce_Tcp_Rtt_P1, "DCE_TCP_RTT_P1"
            ,"The time between updates of the alpha value, in microseconds. Default=2"
            ,"USEC");
    params[Mcp_Dce_Tcp_Rtt_P2] = MlxCfgParamParser(Mcp_Dce_Tcp_Rtt_P2, "DCE_TCP_RTT_P2","","USEC");
    params[Mcp_Rate_Reduce_Monitor_Period_P1] = MlxCfgParamParser(Mcp_Rate_Reduce_Monitor_Period_P1, "RATE_REDUCE_MONITOR_PERIOD_P1"
            ,"The minimum time between 2 consecutive rate reductions for a single flow. "
             "Rate reduction will occur only if a CNP is received during the relevant time interval. Default=2."
            ,"USEC");
    params[Mcp_Rate_Reduce_Monitor_Period_P2] = MlxCfgParamParser(Mcp_Rate_Reduce_Monitor_Period_P2, "RATE_REDUCE_MONITOR_PERIOD_P2","","USEC");
    params[Mcp_Initial_Alpha_Value_P1] = MlxCfgParamParser(Mcp_Initial_Alpha_Value_P1, "INITIAL_ALPHA_VALUE_P1"
            ,"The initial value of alpha to use when receiving the first CNP for a flow. "
             "Expressed in a fixed point fraction of 2^10."
            ,"NUM");
    params[Mcp_Initial_Alpha_Value_P2] = MlxCfgParamParser(Mcp_Initial_Alpha_Value_P2, "INITIAL_ALPHA_VALUE_P2","","NUM");
    params[Mcp_Min_Time_Between_Cnps_P1] = MlxCfgParamParser(Mcp_Min_Time_Between_Cnps_P1, "MIN_TIME_BETWEEN_CNPS_P1"
            ,"Minimum time between sending cnps from the port, in microseconds. Default=0"
            ,"USEC");
    params[Mcp_Min_Time_Between_Cnps_P2] = MlxCfgParamParser(Mcp_Min_Time_Between_Cnps_P2, "MIN_TIME_BETWEEN_CNPS_P2","","USEC");
    params[Mcp_Cnp_Dscp_P1] = MlxCfgParamParser(Mcp_Cnp_Dscp_P1, "CNP_DSCP_P1"
            ,"The DiffServ Code Point of the generated CNP for this port. Default=0"
            ,"0..7");
    params[Mcp_Cnp_Dscp_P2] = MlxCfgParamParser(Mcp_Cnp_Dscp_P2, "CNP_DSCP_P2","","0..7");
    params[Mcp_Cnp_802p_Prio_P1] = MlxCfgParamParser(Mcp_Cnp_802p_Prio_P1, "CNP_802P_PRIO_P1"
            ,"The 802.1p priority value of the generated CNP for this port. Default=7"
            ,"NUM");
    params[Mcp_Cnp_802p_Prio_P2] = MlxCfgParamParser(Mcp_Cnp_802p_Prio_P2, "CNP_802P_PRIO_P2","","NUM");
    return MlxCfgInfo("RoCE Congestion Control ECN", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCEV1_5NextProtocol()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE V1.5 next protocol
    params[Mcp_RoCE_Next_Protocol] = MlxCfgParamParser(Mcp_RoCE_Next_Protocol, "ROCE_NEXT_PROTOCOL",
            "The next protocol value set in the IPv4/IPv6 packets for RoCE v1.5. The default is 0xFE.", "0..255");

    return MlxCfgInfo("RoCE V1.5 next protocol", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCECongestionControlParameters()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE Congestion Control Parameters
    paramMap["ECN"] = 0;
    paramMap["QCN"] = 1;
    params[Mcp_RoCE_CC_Algorithm_P1] = MlxCfgParamParser(Mcp_RoCE_CC_Algorithm_P1, "ROCE_CC_ALGORITHM_P1", "Congestion control algorithm.", paramMap);
    params[Mcp_RoCE_CC_Algorithm_P2] = MlxCfgParamParser(Mcp_RoCE_CC_Algorithm_P2, "ROCE_CC_ALGORITHM_P2", "", paramMap);
    params[Mcp_RoCE_CC_Prio_Mask_P1] = MlxCfgParamParser(Mcp_RoCE_CC_Prio_Mask_P1, "ROCE_CC_PRIO_MASK_P1", "Per priority enable disable bitmask. default 0", "0..255");
    params[Mcp_RoCE_CC_Prio_Mask_P2] = MlxCfgParamParser(Mcp_RoCE_CC_Prio_Mask_P2, "ROCE_CC_PRIO_MASK_P2", "", "0..255");
    return MlxCfgInfo("RoCE Congestion Control Parameters", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createVPISettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //VPI Settings
    paramMap["IB"] = 1;
    paramMap["ETH"] = 2;
    paramMap["VPI"] = 3;
    params[Mcp_Link_Type_P1] = MlxCfgParamParser(Mcp_Link_Type_P1, "LINK_TYPE_P1", "", paramMap);
    params[Mcp_Link_Type_P2] = MlxCfgParamParser(Mcp_Link_Type_P2, "LINK_TYPE_P2", "", paramMap);
    return MlxCfgInfo("VPI Settings", "Control network link type", params);
}

MlxCfgInfo MlxCfgAllInfo::createWakeOnLAN()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Wake On LAN
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Wol_Magic_En] = MlxCfgParamParser(Mcp_Wol_Magic_En, "WOL_MAGIC_EN", "5th generation devices only (per physical function)", paramMap);
    params[Mcp_Wol_Magic_En_P1] = MlxCfgParamParser(Mcp_Wol_Magic_En_P1, "WOL_MAGIC_EN_P1", "enable wake on magic packet(per port.)", paramMap);
    params[Mcp_Wol_Magic_En_P2] = MlxCfgParamParser(Mcp_Wol_Magic_En_P2, "WOL_MAGIC_EN_P2", "4th generation devices only", paramMap);
    return MlxCfgInfo("Wake On LAN", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createExternalPort()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    paramMap["False"] = 0;
    paramMap["True"] = 1;

    //External ports
    params[Mcp_Port_Owner] = MlxCfgParamParser(Mcp_Port_Owner, "PORT_OWNER", "If Set, Indicates this function of this host own the external physical port.", paramMap);
    params[Mcp_Allow_Rd_Counters] = MlxCfgParamParser(Mcp_Allow_Rd_Counters, "ALLOW_RD_COUNTERS", "If Set, Indicates this function of this host allowed to rd counters of external physical port.", paramMap);
    return MlxCfgInfo("External Ports", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createBootSettingsExt()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Boot Settings Extras
    paramMap["IPv4"] = 0;
    paramMap["IPv6"] = 1;
    paramMap["IPv4_IPv6"] = 2;
    paramMap["IPv6_IPv4"] = 3;
    params[Mcp_Boot_Settings_Ext_IP_Ver] = MlxCfgParamParser(Mcp_Boot_Settings_Ext_IP_Ver, "IP_VER", "Select which IP protocol version will be used by flexboot. 5th Generation only.", paramMap);
    params[Mcp_Boot_Settings_Ext_IP_Ver_P1] = MlxCfgParamParser(Mcp_Boot_Settings_Ext_IP_Ver_P1, "IP_VER_P1", "Select which IP protocol version will be used by flexboot, 4th Generation (per port).", paramMap);
    params[Mcp_Boot_Settings_Ext_IP_Ver_P2] = MlxCfgParamParser(Mcp_Boot_Settings_Ext_IP_Ver_P2, "IP_VER_P2", "", paramMap);
    return MlxCfgInfo("Boot Settings Extras", "These parameters are relevant only for servers using legacy BIOS PXE boot (flexboot).", params);
}

bool sortCfg(MlxCfgInfo a, MlxCfgInfo b)
{
    return a.getName() < b.getName();
}

MlxCfgAllInfo::MlxCfgAllInfo()
{
    //Initialize all the configurations
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    _allInfo.push_back(createPciSettings());
    _allInfo.push_back(createIBDynamicallyConnect());
    _allInfo.push_back(createInfinibandBootSettings());
    _allInfo.push_back(createInternalSettings());
    _allInfo.push_back(createPrebootBootSettings());
    _allInfo.push_back(createRoCECongestionControlECN());
    _allInfo.push_back(createRoCEV1_5NextProtocol());
    _allInfo.push_back(createRoCECongestionControlParameters());
    _allInfo.push_back(createVPISettings());
    _allInfo.push_back(createWakeOnLAN());
    _allInfo.push_back(createExternalPort());
    _allInfo.push_back(createBootSettingsExt());
    std::sort(_allInfo.begin(), _allInfo.end(), sortCfg);
}

void MlxCfgAllInfo::printShortDesc()
{
    for(u_int32_t i = 0; i < _allInfo.size(); i++){
        _allInfo[i].printShortDesc();
    }
}

void MlxCfgAllInfo::printLongDesc()
{
    for(u_int32_t i = 0; i < _allInfo.size(); i++){
        _allInfo[i].printLongDesc();
    }
}

mlxCfgStatus MlxCfgAllInfo::getParamParser(mlxCfgParam p, MlxCfgParamParser& paramParser)
{
    for(u_int32_t j = 0; j < _allInfo.size(); j++){
        if(_allInfo[j].getParamParser(p, paramParser) == MLX_CFG_OK) {
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

mlxCfgStatus MlxCfgAllInfo::parseParam(string tag, string strVal, u_int32_t& val, mlxCfgParam& param)
{
    MlxCfgParamParser paramParser;
    for(u_int32_t j = 0; j < _allInfo.size(); j++){
        if(_allInfo[j].getParamParser(tag, paramParser) == MLX_CFG_OK) {
            param = paramParser.getParam();
            return (paramParser.parseUserInput(strVal, val)) ?
                    MLX_CFG_ERROR :
                    MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}
