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
 */

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <errno.h>
#include <utility>

#include <common/tools_version.h>

#include "mlxcfg_ui.h"

using namespace std;


#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"



static void printFlagLine(string flag_s, string flag_l, string param, string desc)
{
    printf(IDENT2"-%s|--%s", flag_s.c_str(), flag_l.c_str());
    if (param.length()) {
        printf(" <%s>", param.c_str());
    } else {
        printf("\t");
    }
    printf(IDENT3": %s\n", desc.c_str());
}

void MlxCfg::printHelp()
{
    // print opening
    printf(IDENT"NAME:\n"
           IDENT2   MLXCFG_NAME"\n"
           IDENT"SYNOPSIS:\n"
           IDENT2    MLXCFG_NAME " [-d <device> ] [-y] <s[et] <parameters to set>|q[uery]|r[eset]>\n");

    // print options
    printf("\n");
    printf(IDENT"OPTIONS:\n");
    printFlagLine("d", "dev", "device", "Perform operation for a specified mst device.");
    printFlagLine("y", "yes", "", "Answer yes in prompt.");
    printFlagLine("v", "version", "", "Display version info.");
    printFlagLine("h", "help", "", "Display help message.");

    //print commands
    printf("\n");
    printf(IDENT"COMMANDS:\n");
    printf(IDENT2"%-24s : %s\n","q[uery]", "query current supported configurations.");
    printf(IDENT2"%-24s : %s\n","s[et]", "set configurations to a specific device.");
    printf(IDENT2"%-24s : %s\n","r[eset]", "reset configurations to their default value.");

    // print supported commands
    printf("\n");
    printf(IDENT"Supported Configurations:\n");
    printf(IDENT2"%-24s : %s\n","SRIOV", "SRIOV_EN=<1|0> NUM_OF_VFS=<NUM>");
    printf(IDENT2"%-24s : %s\n","WOL_PORT1", "WOL_MAGIC_EN_P1");
    printf(IDENT2"%-24s : %s\n","WOL_PORT2", "WOL_MAGIC_EN_P2=<1|0>");
    printf(IDENT2"%-24s : %s\n","VPI_SETTINGS_PORT1", "LINK_TYPE_P1=<1|2|3> , 1=Infiniband 2=Ethernet 3=VPI(auto-sense).");
    printf(IDENT2"%-24s : %s\n","VPI_SETTINGS_PORT2", "LINK_TYPE_P2=<1|2|3>");
    //printf(IDENT2"%-24s : %s\n","BAR_SIZE", "LOG_BAR_SIZE=<Base_2_log_in_mb> , example: for 8Mb bar size set LOG_BAR_SIZE=3");

    // print usage examples
    printf("\n");
    printf(IDENT"Examples:\n");
    printf(IDENT2"%-35s: %s\n", "To query current Configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" query");
    printf(IDENT2"%-35s: %s\n", "To set Configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" set SRIOV_EN=1 NUM_OF_VFS=16 WOL_MAGIC_EN_P1=1");
    printf(IDENT2"%-35s: %s\n", "To reset Configuration", MLXCFG_NAME" -d "MST_DEV_EXAMPLE" reset");
    printf("\n");
    printf(IDENT"Supported devices:\n");
    printf(IDENT2"ConnectX3, ConnectX3-Pro (FW 2.31.5000 and above).\n");
    printf("\n");
}

void MlxCfg::printVersion()
{
    print_version_string(MLXCFG_NAME, "");
}

void MlxCfg::printUsage() {
    printf("\n"IDENT"Usage:\n"
           IDENT2    MLXCFG_NAME " [-d <device> ] [-y] <s[et] <parameters to set>|q[uery]|r[eset]>\n\n");
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
    // we dont support BAR_SZ atm
    if (i == Mcp_Last || i == Mcp_Log_Bar_Size) {
        return err(true, "Unknown Parameter: %s", tag.c_str());
    }
    return MLX_CFG_OK;
}


static bool strToNum(string str, u_int16_t& num, int base=0)
{
    char *endp;
    char* numStr = strcpy(new char[str.size()],str.c_str());
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
    u_int16_t val = 0;
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
        //printf("-D- %s %s\n", tag.c_str(), valstr.c_str());
        if (!strToNum(valstr, val, 10)) {
            return err(true, "Failed to parse %s=%s", tag.c_str(), valstr.c_str());
        }
        // store val in the correct place in  mlxconfig Params
        if (processArg(tag, val)) {
            return MLX_CFG_ERROR;
        }
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
        }else if (arg == "-d" || arg == "--dev") {
            if (++i == argc) {
                return err(true, "missing device name");
            }
            _mlxParams.device = argv[i];
        } else if (arg == "-y" || arg == "--yes") {
            _mlxParams.yes = true;
        } else if (arg == "set" || arg == "s") {
            _mlxParams.cmd = Mc_Set;
            break;

        } else if (arg == "query" || arg == "q") {
            _mlxParams.cmd = Mc_Query;
            break;

        } else if (arg == "reset" || arg == "r") {
            _mlxParams.cmd = Mc_Reset;
            break;
        // hidden flag --force used to ignore parameter checks
        } else if (arg == "--force"){
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
    if (_mlxParams.cmd == Mc_Set && _mlxParams.device.length() == 0) {
        return err(true, "set command expects device to be specified.");
    }

    return extractCfgArgs(argc-i, &(argv[i]));
}
