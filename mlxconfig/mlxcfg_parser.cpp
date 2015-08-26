/* Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
#define IDENT4 IDENT2 IDENT



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

static void printConfigurationHeader(string confName, string extraInfo="")
{
    printf(IDENT2"%s: %s\n", confName.c_str(), extraInfo.c_str());
}

static void printConfigurationParameter(string param, string extraInfo)
{
    printf(IDENT4"%-36s : %s\n", param.c_str(), extraInfo.c_str());
}


static void printConfigurationParameter(string param)
{
    printf(IDENT4"%-36s\n", param.c_str());
}

#ifdef MTCR_UL
#define DEVICE_NAME "device"
#else
#define DEVICE_NAME "mst device"
#endif

void MlxCfg::printHelp()
{
    // print opening
    printf(IDENT"NAME:\n"
           IDENT2   MLXCFG_NAME"\n"
           IDENT"SYNOPSIS:\n"
           IDENT2    MLXCFG_NAME " [-d <%s> ] [-y] <s[et] <parameters to set>|q[uery]|r[eset]>\n", DEVICE_NAME);

    // print options
    printf("\n");
    printf(IDENT"OPTIONS:\n");
    printFlagLine("d", "dev", "device", "Perform operation for a specified mst device.");
    printFlagLine("f", "file", "conf_file", "raw configuration file.");
    printFlagLine("h", "help", "", "Display help message.");
    printFlagLine("v", "version", "", "Display version info.");
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
    printConfigurationHeader("PCI Settings");
    printConfigurationParameter("FPP_EN=<1|0>", "enable function per port.");
    printConfigurationParameter("LOG_BAR_SIZE=<base_2_log_in_mb>", "example: for 8Mb bar size set LOG_BAR_SIZE=3.");
    printConfigurationParameter("NUM_OF_VFS=<NUM>", "desired amount of virtual functions.");
    printConfigurationParameter("SRIOV_EN=<0|1>", "enable SR-IOV.");
    printf("\n");
    printConfigurationHeader("IB Dynamically Connect");
    printConfigurationParameter("DCR_LIFO_SIZE=<SIZE>", "The amount of total DCRs available to join linked-lists after hash DCRs.");
    printConfigurationParameter("LOG_DCR_HASH_TABLE_SIZE=<SIZE>", "log2 of the hash table size minus 1.");
    printf("\n");
    printConfigurationHeader("Infiniband Boot Settings");
    printConfigurationParameter("BOOT_PKEY_P1=<PKEY>", "partition key to be used by PXE boot (ConnectX3, ConnectX3-Pro Only).");
    printConfigurationParameter("BOOT_PKEY_P2=<PKEY>", "set 0 for default.");
    printf("\n");
    printConfigurationHeader("Internal Settings");
    printConfigurationParameter("INT_LOG_MAX_PAYLOAD_SIZE=<0|12>", "0=Auto 12=4KB Burst length.");
    printf("\n");
    /*
    printConfigurationHeader("Port Boot State", "Port power settings on boot");
    printConfigurationParameter("BOOT_STATE_P1=<0..3>", "0=Normal operation, 1=SFP power off, 2=SERDES power off, 3=Admin linkDown");
    printConfigurationParameter("BOOT_STATE_P2=<0..3>");
    printf("\n");
    */
    printConfigurationHeader("Preboot Boot Settings", "Settings that control the legacy option ROM.");
    printConfigurationParameter("BOOT_OPTION_ROM_EN_P1=<0|1>", "Disable/Enable boot option ROM.");
    printConfigurationParameter("BOOT_OPTION_ROM_EN_P2=<0|1>");
    printConfigurationParameter("BOOT_VLAN_EN_P1=<0|1>", "Disable/Enable VLAN mode for network boot.");
    printConfigurationParameter("BOOT_VLAN_EN_P2=<0|1>");
    printConfigurationParameter("BOOT_RETRY_CNT_P1=<0..7>", "Number of retries to attempt in case of boot failure.");
    printConfigurationParameter("BOOT_RETRY_CNT_P2=<0..7>", "7 indicates infinite retries.");
    printConfigurationParameter("LEGACY_BOOT_PROTOCOL_P1=<0..3>", "0=None(disable legacy boot), 1=PXE(DHCP/TFTP boot), 2=iSCSI, 3=PXE + iSCSI.");
    printConfigurationParameter("LEGACY_BOOT_PROTOCOL_P2=<0..3>");
    printConfigurationParameter("BOOT_VLAN_P1=<VLAN ID>", "VLAN ID for the network boot.");
    printConfigurationParameter("BOOT_VLAN_P2=<VLAN ID>");
    printf("\n");
    printConfigurationHeader("RoCE Congestion Control ECN");
    printConfigurationParameter("CLAMP_TGT_RATE_AFTER_TIME_INC_P1=<0|1>", "When receiving an CNP, the target rate should be updated if the transmission rate was increased");
    printConfigurationParameter("CLAMP_TGT_RATE_AFTER_TIME_INC_P2=<0|1>", "due to the timer, and not only due to the byte counter. Default=1.");
    printConfigurationParameter("CLAMP_TGT_RATE_P1=<0|1>", "If set, whenever a CNP is processed, the target rate is updated to be the current rate.");
    printConfigurationParameter("CLAMP_TGT_RATE_P2=<0|1>", "Default=1");
    printConfigurationParameter("CNP_DSCP_P1=<0..7>", "The DiffServ Code Point of the generated CNP for this port.");
    printConfigurationParameter("CNP_DSCP_P2=<0..7>", "Default=0.");
    printConfigurationParameter("CNP_802P_PRIO_P1=<NUM>", "The 802.1p priority value of the generated CNP for this port.");
    printConfigurationParameter("CNP_802P_PRIO_P2=<NUM>", "Default=7.");
    printConfigurationParameter("DCE_TCP_G_P1=<NUM>", "Used to update the congestion estimator (alpha) once every dce_tcp_rtt microseconds.");
    printConfigurationParameter("DCE_TCP_G_P2=<NUM>", "Default=64.");
    printConfigurationParameter("DCE_TCP_RTT_P1=<USEC>", "The time between updates of the alpha value, in microseconds.");
    printConfigurationParameter("DCE_TCP_RTT_P2=<USEC>", "Default=2.");
    printConfigurationParameter("INITIAL_ALPHA_VALUE_P1=<NUM>", "The initial value of alpha to use when receiving the first CNP for a flow.");
    printConfigurationParameter("INITIAL_ALPHA_VALUE_P2=<NUM>", "Expressed in a fixed point fraction of 2^10.");
    printConfigurationParameter("MIN_TIME_BETWEEN_CNPS_P1=<USEC>", "Minimum time between sending cnps from the port, in microseconds.");
    printConfigurationParameter("MIN_TIME_BETWEEN_CNPS_P2=<USEC>", "Default=0.");
    printConfigurationParameter("RATE_TO_SET_ON_FIRST_CNP_P1=<RATE_IN_MBIT>", "The rate that is set for the flow when a rate limiter is allocated to it upon first CNP received, in Mbps.");
    printConfigurationParameter("RATE_TO_SET_ON_FIRST_CNP_P2=<RATE_IN_MBIT>", "Default=0.");
    printConfigurationParameter("RATE_REDUCE_MONITOR_PERIOD_P1=<USEC>", "The minimum time between 2 consecutive rate reductions for a single flow.");
    printConfigurationParameter("RATE_REDUCE_MONITOR_PERIOD_P2=<USEC>", "Rate reduction will occur only if a CNP is received during the relevant time interval. Default=2.");
    printConfigurationParameter("RPG_AI_RATE_P1=<RATE_IN_MBIT>", "The rate, in Mbits per second, used to increase rpTargetRate in the RPR_ACTIVE_INCREASE state.");
    printConfigurationParameter("RPG_AI_RATE_P2=<RATE_IN_MBIT>", "Default=10.");
    printConfigurationParameter("RPG_BYTE_RESET_P1=<BYTE_NUM>", "Transmitted data between rate increases if no CNPs are received. Given in Bytes.");
    printConfigurationParameter("RPG_BYTE_RESET_P2=<BYTE_NUM>", "Disabled=0, Default=150.");
    printConfigurationParameter("RPG_GD_P1=<0..15>", "If a CNP is received, the flow rate is reduced at the beginning of the next rate_reduce_monitor_period interval to,");
    printConfigurationParameter("RPG_GD_P2=<0..15>", "(1-Alpha/Gd)*CurrentRate. RPG_GD is given as log2(Gd), where Gd may only be powers of 2. Default=7.");
    printConfigurationParameter("RPG_HAI_RATE_P1=<RATE_IN_MBIT>", "The rate, in Mbits per second, used to increase rpTargetRate in the RPR_HYPER_INCREASE state.");
    printConfigurationParameter("RPG_HAI_RATE_P2=<RATE_IN_MBIT>", "Default=50.");
    printConfigurationParameter("RPG_MAX_RATE_P1=<RATE_IN_MBIT>", "The maximum rate, in Mbits per second, at which an RP can transmit.");
    printConfigurationParameter("RPG_MAX_RATE_P2=<RATE_IN_MBIT>", "Once this limit is reached, the RP rate limited is released and");
    printConfigurationParameter(" ", "the flow is not rate limited any more. Default=0 (Full port speed).");
    printConfigurationParameter("RPG_MIN_DEC_FAC_P1=<1..100>", "The minimum factor by which the current transmit rate can be changed when processing a CNP.");
    printConfigurationParameter("RPG_MIN_DEC_FAC_P2=<1..100>", "Value is given as a percentage (1-100). Default=50.");
    printConfigurationParameter("RPG_MIN_RATE_P1=<RATE_IN_MBIT>", "The minimum value, in Mb per second, for rate to limit.");
    printConfigurationParameter("RPG_MIN_RATE_P2=<RATE_IN_MBIT>", "Default=2000.");
    printConfigurationParameter("RPG_THRESHOLD_P1=<0..31>", "The number of times rpByteStage or rpTimeStage can count before the RP rate control state machine advances states.");
    printConfigurationParameter("RPG_THRESHOLD_P2=<0..31>", "Default=5.");
    printConfigurationParameter("RPG_TIME_RESET_P1=<USEC>", "Time between rate increases if no CNPs are received. Given in u-seconds");
    printConfigurationParameter("RPG_TIME_RESET_P2=<USEC>", "Default=2.");

    printf("\n");
    printConfigurationHeader("RoCE Congestion Control Parameters");
    printConfigurationParameter("ROCE_CC_ALGORITHM_P1=<0|1>", "Congestion control algorithm. 0=ECN, 1=QCN.");
    printConfigurationParameter("ROCE_CC_ALGORITHM_P2=<0|1>");
    printConfigurationParameter("ROCE_CC_PRIO_MASK_P1=<0..255>", "Per priority enable disable bitmask. default 0.");
    printConfigurationParameter("ROCE_CC_PRIO_MASK_P2=<0..255>");
    printf("\n");
    printConfigurationHeader("RoCE V1.5 next protocol");
    printConfigurationParameter("ROCE_NEXT_PROTOCOL=<0..255>", "The next protocol value set in the IPv4/IPv6 packets for RoCE v1.5. The default is 0xFE.");
    printf("\n");
    printConfigurationHeader("VPI Settings", "Control network link type");
    printConfigurationParameter("LINK_TYPE_P1=<1|2|3>", "1=Infiniband 2=Ethernet 3=VPI(auto-sense).");
    printConfigurationParameter("LINK_TYPE_P2=<1|2|3>");
    printf("\n");
    printConfigurationHeader("Wake On LAN");
    printConfigurationParameter("WOL_MAGIC_EN=<0|1>", "5th generation devices only (per physical function).");
    printConfigurationParameter("WOL_MAGIC_EN_P1=<0|1>", "enable wake on magic packet(per port.)");
    printConfigurationParameter("WOL_MAGIC_EN_P2=<0|1>", "4th generation devices only.");
    printf("\n");
    // print usage examples
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
           IDENT2    MLXCFG_NAME " [-d <%s> ] [-y] <s[et] <parameters to set>|q[uery]|r[eset]>\n\n", DEVICE_NAME);
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
    u_int32_t val = 0;
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
        if (!strToNum(valstr, val, 0)) {
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
        } else if (arg == "-f" || arg == "--file") {
            if (++i == argc) {
                return err(true, "missing file name");
            }
            _mlxParams.rawTlvFile = argv[i];
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
