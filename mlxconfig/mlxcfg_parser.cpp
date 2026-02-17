/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <fstream>

#include <common/tools_version.h>

#include "mlxcfg_ui.h"

#include "mlxcfg_generic_commander.h"
#include "mlxcfg_commander.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"
#include <mft_utils.h>
#include <tools_layouts/reg_access_switch_layouts.h>

using namespace std;

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#define IDENT4 IDENT2 IDENT
#define MAX_SESSION_TIME_IN_MINUTES 10080 // 1 week = 7 * 24 hours * 60 minutes

static void printFlagLine(string flag_s, string flag_l, string param, string desc)
{
    string flags = "-" + flag_s + "|--" + flag_l + (param.length() ? " <" + param + ">" : "");
    printf(IDENT2 "%-16s", flags.c_str());
    printf(IDENT3 ": %s\n", desc.c_str());
}

#ifdef MTCR_UL
#define DEVICE_NAME "device"
#else
#define DEVICE_NAME "mst device"
#endif

void MlxCfg::printHelp()
{
    // print opening
    printf(IDENT "NAME:\n" IDENT2 MLXCFG_NAME "\n" IDENT "SYNOPSIS:\n" IDENT2 MLXCFG_NAME
                 " [Options] <Commands> [Parameters]\n");

    printf(IDENT "DESCRIPTION:\n" IDENT2 "Allows the user to change some of the device configurations without having "
                 "to\n" IDENT2 "create and burn a new firmware.");
    // print options
    printf("\n");
    printf(IDENT "OPTIONS:\n");
    printFlagLine("d", "dev", "device", "Perform operation for a specified MST device.");
    printFlagLine("b", "db", "filename", "Use a specific database file.");
    printFlagLine("f", "file", "conf_file", "raw configuration file.");
    printFlagLine("h", "help", "", "Display help message.");
    printFlagLine("v", "version", "", "Display version info.");
    printFlagLine("e", "enable_verbosity", "", "Show default and current configurations.");
    printFlagLine("j", "json_format", "file",
                  "Save the query output to file in JSON format, only usable with Query command");
    printFlagLine("y", "yes", "", "Answer yes in prompt.");
    printFlagLine("yy", "yyes", "", "Answer yes to all prompts including reboot command.");
    printFlagLine(
      "", "with_default", "",
      "set command will fill any missing parameters with default values. if the final configurations matches the current no set will be done");
    printFlagLine("a", "all_attrs", "", "Show all attributes in the XML template");
    printFlagLine("", "host_id", "", "Specify host id for Per-Host TLV (class 3)");
    printFlagLine("", "pf_index", "", "Specify PF index for Per-Host TLV (class 3)");
    printFlagLine("p", "private_key", "PKEY", "pem file for private key");
    printFlagLine("u", "key_uuid", "UUID", "keypair uuid");
    printFlagLine("eng", "openssl_engine", "ENGINE NAME", "deprecated");
    printFlagLine("k", "openssl_key_id", "IDENTIFIER", "deprecated");
    printFlagLine("t", "device_type", "switch/hca", "Specify the device type");
    printFlagLine("tkn", "token_type", "", "Specify token type.");

    // print commands
    printf("\n");
    printf(IDENT "COMMANDS SUMMARY\n");
    printf(IDENT2 "%-24s : %s\n", "clear_semaphore", "clear the tool semaphore.");
    printf(IDENT2 "%-24s : %s\n", "i|show_confs", "display information about all configurations.");
    printf(IDENT2 "%-24s : %s\n", "q|query", "query supported configurations.");
    printf(IDENT2 "%-24s : %s\n", "r|reset",
           "reset all configurations to their default value. Optionally, resets specific TLV if given.");
    printf(IDENT2 "%-24s : %s\n", "s|set", "set configurations to a specific device.");
    printf(IDENT2 "%-24s : %s\n", "set_raw", "set raw configuration file(5th Generation and above).");
    printf(IDENT2 "%-24s : %s\n", "get_raw", "get raw configuration (5th Generation and above).");
    printf(IDENT2 "%-24s : %s\n", "backup",
           "backup configurations to a file. Use set_raw command to restore file (5th Generation and above).");
    printf(IDENT2 "%-24s : %s\n", "gen_tlvs_file",
           "Generate List of all TLVs. TLVs output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "g <en_xml_template>",
           "Generate XML template. TLVs input file name and XML output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "xml2raw",
           "Generate Raw file from XML file. XML input file name and raw output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "raw2xml",
           "Generate XML file from Raw file. raw input file name and XML output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "xml2bin",
           "Generate binary configuration dump file from XML file. XML input file name and bin output file name must "
           "be specified. (*)");
    printf(
      IDENT2 "%-24s : %s\n", "create_conf",
      "Generate configuration file from XML file. XML input file name and bin output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "apply",
           "Apply a configuration file, that was created with create_conf command. bin input file name must be "
           "specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "challenge_request",
           "Send a token challenge request to the device. Token type must be specified.");
    printf(IDENT2 "%-24s : %s\n", "token_supported", "Query which tokens are supported.");
    printf(IDENT2 "%-24s : %s\n", "query_token_session", "Query the status of a token session.");
    printf(IDENT2 "%-24s : %s\n", "end_token_session", "End an active token session.");
    printf(IDENT2 "%-24s : %s\n", "show_system_conf", "Show available system configurations.");
    printf(IDENT2 "%-24s : %s\n", "set_system_conf", "Apply a system configuration to the device.");
    printf(IDENT2 "%-24s : %s\n", "validate_system_conf", "Validate a system configuration against the device.");

    // print supported commands
    printf("\n");
    printf(IDENT "(*) These commands do not require MST device\n\n");
    printf(IDENT "To show supported configurations by device type, run show_confs command\n");
    printf("\n");

    // print usage examples
    printf("\n");
    printf(IDENT "Examples:\n");
    printf(IDENT2 "%-35s: %s\n", "To query configurations", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " query");
    printf(IDENT2 "%-35s: %s\n", "To query in json format",
           MLXCFG_NAME " -d " MST_DEV_EXAMPLE " -j /tmp/query.json query");
    printf(IDENT2 "%-35s: %s\n", "To query specific parameter", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " q NUM_OF_VFS");
    printf(IDENT2 "%-35s: %s\n", "To set configuration",
           MLXCFG_NAME " -d " MST_DEV_EXAMPLE " set SRIOV_EN=1 NUM_OF_VFS=16 WOL_MAGIC_EN_P1=1");
    printf(IDENT2 "%-35s: %s\n", "To set raw configuration",
           MLXCFG_NAME " -d " MST_DEV_EXAMPLE2 " -f conf_file set_raw");
    printf(IDENT2 "%-35s: %s\n", "To reset configuration", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " reset");
    printf(IDENT2 "%-35s: %s\n", "To reset specific configuration",
           MLXCFG_NAME " -d " MST_DEV_EXAMPLE " reset NV_GLOBAL_PCI_CONF_4");
    printf(IDENT2 "%-35s: %s\n", "To generate tlvs file",
           MLXCFG_NAME " -t HCA gen_tlvs_file <file_path> tlvs.txt");
    printf(IDENT2 "%-35s: %s\n", "To generate xml from tlvs file",
           MLXCFG_NAME " -t HCA gen_xml_template  <file_path> tlvs.txt  <file_path> template.xml");
    printf("\n");
}

void MlxCfg::printVersion()
{
    print_version_string(MLXCFG_NAME, "");
}

void MlxCfg::printUsage()
{
    printHelp();
}

bool MlxCfg::tagExsists(string tag)
{
    VECTOR_ITERATOR(ParamView, _mlxParams.setParams, it)
    {
        if (it->mlxconfigName == tag)
        {
            return true;
        }
    }
    return false;
}

inline const char* cmdNVInputFileTag(mlxCfgCmd cmd, const char* def)
{
    return (cmd == Mc_XML2Raw || cmd == Mc_XML2Bin || cmd == Mc_CreateConf) ? "XML" :
           (cmd == Mc_Raw2XML)                                              ? "Raw" :
           (cmd == Mc_GenXMLTemplate)                                       ? "TLVs" :
           (cmd == Mc_Apply)                                                ? "Configuration" :
                                                                              def;
}

inline const char* cmdNVOutputFileTag(mlxCfgCmd cmd, const char* def)
{
    return (cmd == Mc_XML2Raw)        ? "Raw" :
           (cmd == Mc_Raw2XML)        ? "XML" :
           (cmd == Mc_GenXMLTemplate) ? "XML" :
           (cmd == Mc_XML2Bin)        ? "Bin" :
           (cmd == Mc_CreateConf)     ? "Configuration" :
                                        def;
}

mlxCfgStatus MlxCfg::extractNVInputFile(int argc, char* argv[])
{
    if (argc < 1)
    {
        return err(true, "%s input file is missing", cmdNVInputFileTag(_mlxParams.cmd, ""));
    }
    _mlxParams.NVInputFile = argv[0];
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractNVOutputFile(int argc, char* argv[])
{
    if (argc < 1)
    {
        return err(true, "%s output file is missing", cmdNVOutputFileTag(_mlxParams.cmd, ""));
    }
    _mlxParams.NVOutputFile = argv[0];
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractQueryCfgArgs(int argc, char* argv[])
{
    int i = 0;

    for (; i < argc; i++)
    {
        ParamView pv;
        string mlxconfigName = argv[i];
        if (isIndexedMlxconfigName(mlxconfigName))
        {
            string indexStr = parseIndexStr(mlxconfigName);
            vector<u_int32_t> indexes;
            bool isStartFromOneSupported = false;
            extractIndexes(indexStr, indexes);
            if (indexes.size() > 1)
            {
                size_t p = mlxconfigName.find('[');
                if (p == std::string::npos)
                {
                    return err(true, "Expected a parameter with index");
                }
                mlxconfigName = mlxconfigName.substr(0, p);
                isStartFromOneSupported = isIndexedStartFromOneSupported(mlxconfigName);

                VECTOR_ITERATOR(u_int32_t, indexes, it)
                {
                    ParamView paramView;
                    if (isStartFromOneSupported)
                    {
                        if ((int32_t)*it <= 0)
                        {
                            printf("-E- Index is out of range.Minimal index is 1\n");
                            return MLX_CFG_ERROR_NO_USAGE;
                        }
                        else
                        {
                            (*it)--;
                        }
                    }
                    paramView.mlxconfigName = mlxconfigName + "[" + numToStr(*it) + "]";
                    _mlxParams.setParams.push_back(paramView);
                }
                continue;
            }
            else
            {
                size_t p = mlxconfigName.find('[');
                string subStr = mlxconfigName.substr(0, p);
                if (isIndexedStartFromOneSupported(subStr))
                {
                    if ((int32_t)indexes[0] <= 0)
                    {
                        printf("-E- Index is out of range.Minimal index is 1\n");
                        return MLX_CFG_ERROR_NO_USAGE;
                    }
                    pv.mlxconfigName = subStr + "[" + numToStr(indexes[0] - 1) + "]";
                }
                else
                {
                    pv.mlxconfigName = mlxconfigName;
                }
            }
        }
        else
        {
            pv.mlxconfigName = mlxconfigName;
        }
        _mlxParams.setParams.push_back(pv);
    }

    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractSetCfgArgs(int argc, char* argv[])
{
    int i = 0;
    string tag, strVal;

    for (; i < argc; i++)
    {
        char* ptr;
        // get the tag
        ptr = strtok(argv[i], "=");
        if (!ptr)
        {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }
        tag = ptr;
        // get the val
        ptr = strtok(NULL, "=");
        if (!ptr)
        {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }
        strVal = ptr;
        if (strtok(NULL, "="))
        {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }

        if (tagExsists(tag))
        {
            return err(true, "Duplicate parameter, %s.", tag.c_str());
        }

        ParamView pv;

        if (isIndexedMlxconfigName(tag))
        {
            string indexStr = parseIndexStr(tag);
            vector<u_int32_t> indexes;
            extractIndexes(indexStr, indexes);
            bool isStartFromOneSupported = false;
            if (indexes.size() > 1)
            {
                size_t p = tag.find('[');
                if (p == std::string::npos)
                {
                    return err(true, "Expected a parameter with index");
                }
                string mlxconfigName = tag.substr(0, p);
                isStartFromOneSupported = isIndexedStartFromOneSupported(mlxconfigName);
                VECTOR_ITERATOR(u_int32_t, indexes, it)
                {
                    ParamView paramView;
                    paramView.setVal = strVal;

                    if (isStartFromOneSupported)
                    {
                        if (*it == 0)
                        {
                            printf("-E- Index 0 is out of range.Minimal index is 1\n");
                            return MLX_CFG_ERROR_NO_USAGE;
                        }
                        else
                        {
                            (*it)--;
                        }
                    }

                    paramView.mlxconfigName = mlxconfigName + "[" + numToStr(*it) + "]";
                    _mlxParams.setParams.push_back(paramView);
                }
                continue;
            }
            else
            {
                size_t p = tag.find('[');
                string subStr = tag.substr(0, p);
                if (isIndexedStartFromOneSupported(subStr))
                {
                    if (indexes[0] == 0)
                    {
                        printf("-E- Index 0 is out of range.Minimal index is 1\n");
                        return MLX_CFG_ERROR_NO_USAGE;
                    }
                    pv.mlxconfigName = subStr + "[" + numToStr(indexes[0] - 1) + "]";
                }
                else
                {
                    pv.mlxconfigName = tag;
                }
            }
        }
        else
        {
            pv.mlxconfigName = tag;
        }

        pv.setVal = strVal;
        _mlxParams.setParams.push_back(pv);
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::getNumberFromString(const char* str, u_int32_t& num)
{
    char* end = NULL;
    num = strtoul(str, &end, 0);
    if (*end != '\0')
    {
        return err(true, "argument is not a number: %s", str);
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::parseArgs(int argc, char* argv[])
{
    mlxCfgStatus status = MLX_CFG_OK;
    int i = 1;
    for (; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "-v" || arg == "--version")
        {
            printVersion();
            return MLX_CFG_OK_EXIT;
        }
        else if (arg == "-h" || arg == "--help")
        {
            printHelp();
            return MLX_CFG_OK_EXIT;
        }
        else if (arg == "-d" || arg == "--dev")
        {
            if (++i == argc)
            {
                return err(true, "missing device name");
            }
            _mlxParams.device = argv[i];
        }
        else if (arg == "-t" || arg == "--device_type")
        {
            if (++i == argc)
            {
                return err(true, "missing device type");
            }
            Device_Type dType = getDeviceTypeFromString(argv[i]);
            if (dType == Device_Type::UNSUPPORTED_DEVICE)
            {
                return err(true, "Unsupported device name given, please specify \"switch\" or \"hca\"device type");
            }
            _mlxParams.deviceType = dType;
        }
        else if (arg == "-b" || arg == "--db")
        {
            if (++i == argc)
            {
                return err(true, "missing database file name");
            }
            _mlxParams.dbName = argv[i];
        }
        else if (arg == "-j" || arg == "--json_format")
        {
            if (++i == argc)
            {
                return err(true, "missing .json output file");
            }
            _mlxParams.isJsonOutputRequested = true;
            _mlxParams.NVOutputFile = argv[i];
        }
        else if (arg == "-yy" || arg == "--yyes")
        {
            _mlxParams.yesLevel = 2;
        }
        else if (arg == "-y" || arg == "--yes")
        {
            _mlxParams.yesLevel = 1;
        }
        else if (arg == "-f" || arg == "--file")
        {
            if (++i == argc)
            {
                return err(true, "missing file name");
            }
            _mlxParams.rawTlvFile = argv[i];
        }
        else if (arg == "-e" || arg == "--enable_verbosity")
        {
            _mlxParams.enableVerbosity = true;
        }
        else if (arg == "-a" || arg == "--all_attrs")
        {
            _mlxParams.allAttrs = true;
        }
        else if (arg == "--host_id")
        {
            if (++i == argc)
            {
                return err(true, "missing host id value");
            }
            u_int32_t hostIdNum = 0;
            status = getNumberFromString(argv[i], hostIdNum);
            if (status != MLX_CFG_OK)
            {
                return status;
            }
            if (hostIdNum > 63)
            {
                return err(true, "host_id out of range (0..63)");
            }
            _mlxParams.userHostIdParam = (u_int8_t)hostIdNum;
            _mlxParams.userHostIdPfValid = true;
        }
        else if (arg == "--pf_index")
        {
            if (++i == argc)
            {
                return err(true, "missing pf index value");
            }
            u_int32_t pfIdxNum = 0;
            status = getNumberFromString(argv[i], pfIdxNum);
            if (status != MLX_CFG_OK)
            {
                return status;
            }
            if (pfIdxNum > 255)
            {
                return err(true, "pf_index out of range (0..255)");
            }
            _mlxParams.userPfIndexParam = (u_int8_t)pfIdxNum;
            _mlxParams.userHostIdPfValid = true;
        }
        else if (arg == "--with_default")
        {
            _mlxParams.completeSetWithDefault = true;
        }
        else if (arg == "-p" || arg == "--private_key")
        {
            if (++i == argc)
            {
                return err(true, "missing file name");
            }
            _mlxParams.privPemFile = argv[i];
        }
        else if (arg == "-u" || arg == "--key_uuid")
        {
            if (++i == argc)
            {
                return err(true, "missing file name");
            }
            _mlxParams.keyPairUUID = argv[i];
        }
        else if (arg == "-eng" || arg == "--openssl_engine")
        {
            return err(true, "The '--openssl_engine' and '-eng' flags have been deprecated.\n");
        }
        else if (arg == "-k" || arg == "--openssl_key_id")
        {
            return err(true, "The '--openssl_key_id' and '-k' flags have been deprecated.\n");
        }
        else if ((arg == "-tkn") || (arg == "--token_type"))
        {
            if (++i == argc)
            {
                return err(true, "missing token type");
            }
            _mlxParams.tokenName = argv[i];
        }
        // hidden flag --force used to ignore parameter checks
        else if (arg == "--force")
        {
            _mlxParams.force = true;
        }
        else if (arg == "set" || arg == "s")
        {
            _mlxParams.cmd = Mc_Set;
            break;
        }
        else if (arg == "query" || arg == "q")
        {
            _mlxParams.cmd = Mc_Query;
            break;
        }
        else if (arg == "reset" || arg == "r")
        {
            _mlxParams.cmd = Mc_Reset;
            break;
        }
        else if (arg == "clear_semaphore")
        {
            _mlxParams.cmd = Mc_Clr_Sem;
            break;
        }
        else if (arg == "set_raw")
        {
            _mlxParams.cmd = Mc_Set_Raw;
            break;
        }
        else if (arg == "get_raw")
        {
            _mlxParams.cmd = Mc_Get_Raw;
            break;
        }
        else if (arg == "backup")
        {
            _mlxParams.cmd = Mc_Backup;
            break;
        }
        else if (arg == "gen_tlvs_file" || arg == "t")
        {
            _mlxParams.cmd = Mc_GenTLVsFile;
            break;
        }
        else if (arg == "gen_xml_template" || arg == "g")
        {
            _mlxParams.cmd = Mc_GenXMLTemplate;
            break;
        }
        else if (arg == "raw2xml")
        {
            _mlxParams.cmd = Mc_Raw2XML;
            break;
        }
        else if (arg == "xml2raw" || arg == "x")
        {
            _mlxParams.cmd = Mc_XML2Raw;
            break;
        }
        else if (arg == "xml2bin")
        {
            _mlxParams.cmd = Mc_XML2Bin;
            break;
        }
        else if (arg == "create_conf")
        {
            _mlxParams.cmd = Mc_CreateConf;
            break;
        }
        else if (arg == "apply")
        {
            _mlxParams.cmd = Mc_Apply;
            break;
        }
        else if (arg == "show_confs" || arg == "i")
        {
            _mlxParams.cmd = Mc_ShowConfs;
            break;
        }
        else if (arg == "challenge_request")
        {
            _mlxParams.cmd = Mc_ChallengeRequest;
            break;
        }
        else if (arg == "token_supported")
        {
            _mlxParams.cmd = Mc_TokenSupported;
            break;
        }
        else if (arg == "query_token_session")
        {
            _mlxParams.cmd = Mc_QueryTokenSession;
            break;
        }
        else if (arg == "end_token_session")
        {
            _mlxParams.cmd = Mc_EndTokenSession;
            break;
        }
        else if (arg == "remote_token_keep_alive")
        {
            _mlxParams.cmd = Mc_RemoteTokenKeepAlive;
            break;
        }
        else if (arg == "show_system_conf")
        {
            _mlxParams.cmd = Mc_ShowSystemConf;
            break;
        }
        else if (arg == "set_system_conf")
        {
            _mlxParams.cmd = Mc_SetSystemConf;
            break;
        }
        else if (arg == "validate_system_conf")
        {
            _mlxParams.cmd = Mc_ValidateSystemConf;
            break;
        }
        else
        {
            return err(true, "invalid argument: %s", arg.c_str());
        }
    }
    i++;
    if (_mlxParams.cmd == Mc_UnknownCmd)
    {
        return err(true, "No command found. For more information please read the help message:");
    }
    // we parsed input until the set/query/reset cmd
    if (i == argc && _mlxParams.cmd == Mc_Set)
    {
        return err(true, "missing configuration arguments. For more information please run " MLXCFG_NAME " -h|--help.");
    }

    if ((_mlxParams.cmd != Mc_Query) && _mlxParams.isJsonOutputRequested)
    {
        return err(true, "Json format is only supported for query command.");
    }

    if ((_mlxParams.cmd != Mc_Set) && _mlxParams.completeSetWithDefault)
    {
        return err(true, "with_default is only supported for set command.");
    }

    if ((_mlxParams.cmd == Mc_Set || _mlxParams.cmd == Mc_Clr_Sem || _mlxParams.cmd == Mc_Set_Raw ||
         _mlxParams.cmd == Mc_Get_Raw || _mlxParams.cmd == Mc_Backup || _mlxParams.cmd == Mc_ShowConfs ||
         _mlxParams.cmd == Mc_Apply || _mlxParams.cmd == Mc_RemoteTokenKeepAlive ||
         _mlxParams.cmd == Mc_ChallengeRequest || _mlxParams.cmd == Mc_TokenSupported ||
         _mlxParams.cmd == Mc_QueryTokenSession || _mlxParams.cmd == Mc_EndTokenSession ||
         _mlxParams.cmd == Mc_SetSystemConf || _mlxParams.cmd == Mc_ValidateSystemConf) &&
        _mlxParams.device.length() == 0)
    {
        return err(true, "%s command expects device to be specified.",
                   _mlxParams.cmd == Mc_Set                  ? "set" :
                   _mlxParams.cmd == Mc_Set_Raw              ? "set_raw" :
                   _mlxParams.cmd == Mc_Get_Raw              ? "get_raw" :
                   _mlxParams.cmd == Mc_Clr_Sem              ? "clear_semaphore" :
                   _mlxParams.cmd == Mc_Backup               ? "backup" :
                   _mlxParams.cmd == Mc_Apply                ? "apply" :
                   _mlxParams.cmd == Mc_ChallengeRequest     ? "challenge_request" :
                   _mlxParams.cmd == Mc_TokenSupported       ? "token_supported" :
                   _mlxParams.cmd == Mc_QueryTokenSession    ? "query_token_session" :
                   _mlxParams.cmd == Mc_EndTokenSession      ? "end_token_session" :
                   _mlxParams.cmd == Mc_RemoteTokenKeepAlive ? "remote_token_keep_alive" :
                   _mlxParams.cmd == Mc_SetSystemConf        ? "set_system_conf" :
                   _mlxParams.cmd == Mc_ValidateSystemConf   ? "validate_system_conf" :
                                                               "show_confs");
    }
    if (((_mlxParams.cmd == Mc_Set_Raw || _mlxParams.cmd == Mc_Get_Raw) && _mlxParams.rawTlvFile.size() == 0))
    {
        if (_mlxParams.cmd == Mc_Set_Raw)
        {
            return err(true, "set_raw command expects raw TLV file to be specified.");
        }
        else
        {
            return err(true, "get_raw command expects raw TLV file to be specified.");
        }
    }
    if ((_mlxParams.cmd == Mc_Backup && _mlxParams.rawTlvFile.size() == 0))
    {
        return err(true, "backup command expects file to be specified.");
    }
    if ((((_mlxParams.cmd != Mc_Set_Raw && _mlxParams.cmd != Mc_Get_Raw) && _mlxParams.cmd != Mc_Backup) &&
         _mlxParams.rawTlvFile.size() != 0))
    {
        return err(true, "raw TLV file can only be specified with set_raw, get_raw and backup commands.");
    }

    if (_mlxParams.cmd == Mc_GenTLVsFile)
    {
        return extractNVOutputFile(argc - i, &(argv[i]));
    }

    if (_mlxParams.cmd == Mc_Apply)
    {
        return extractNVInputFile(argc - i, &(argv[i]));
    }

    if (_mlxParams.cmd == Mc_CreateConf)
    {
        if (!_mlxParams.keyPairUUID.empty() ^ (!_mlxParams.privPemFile.empty()))
        {
            return err(true,
                       "if you want to sign the configuration file you have to "
                       "provide key pair UUID file with either private pem file "
                       "or OpenSSL engine and key identifier");
        }
    }

    if (_mlxParams.cmd == Mc_ChallengeRequest)
    {
        _mlxParams.tokenChallengeID = MlxCfgToken::GetTokenType(_mlxParams.tokenName);
        if (_mlxParams.tokenChallengeID == McTokenTypeUnknown)
        {
            return err(true, "invalid token type.");
        }
        if (_mlxParams.tokenChallengeID == McTokenTypeCS || _mlxParams.tokenChallengeID == McTokenTypeDBG)
        {
            return err(true, "must provide challenge-based token type for challange_request command.");
        }
    }

    if (_mlxParams.cmd == Mc_QueryTokenSession ||
        (_mlxParams.cmd == Mc_EndTokenSession && !_mlxParams.tokenName.empty()))
    {
        _mlxParams.tokenStatusID = MlxCfgToken::GetTokenStatusType(_mlxParams.tokenName);
        if (_mlxParams.tokenStatusID == McTokenStatusTypeUnknown)
        {
            return err(true, "invalid token type");
        }
    }

    if (_mlxParams.cmd == Mc_QueryTokenSession && _mlxParams.deviceType == UNSUPPORTED_DEVICE)
    {
        return err(true, "device type must be specified with query_token_session command");
    }

    if ((_mlxParams.cmd == Mc_ChallengeRequest && (_mlxParams.tokenChallengeID == McTokenTypeUnknown)) ||
        (_mlxParams.cmd != Mc_ChallengeRequest && (_mlxParams.tokenChallengeID != McTokenTypeUnknown)))
    {
        return err(true, "-tkn/--token_type must be specified with challenge_request command");
    }

    if ((_mlxParams.cmd == Mc_RemoteTokenKeepAlive && !_mlxParams.isSessionIDGiven) ||
        (_mlxParams.cmd != Mc_RemoteTokenKeepAlive && _mlxParams.isSessionIDGiven))
    {
        return err(true, "-s/--session_id should be specified with remote_token_keep_alive command");
    }
    if ((_mlxParams.isSleepTimeBetweenCommandsInput || _mlxParams.isSleepTimeOnCommandTOInput) &&
        _mlxParams.cmd != Mc_RemoteTokenKeepAlive)
    {
        return err(true,
                   "sleep times for keep alive session can only be specified with remote_token_keep_alive command");
    }
    if (_mlxParams.isSessionTimeGiven && _mlxParams.cmd != Mc_RemoteTokenKeepAlive)
    {
        return err(true,
                   "session time for keep alive session can only be specified with remote_token_keep_alive command");
    }

    if (_mlxParams.cmd == Mc_GenXMLTemplate || _mlxParams.cmd == Mc_XML2Raw || _mlxParams.cmd == Mc_Raw2XML ||
        _mlxParams.cmd == Mc_XML2Bin || _mlxParams.cmd == Mc_CreateConf)
    {
        mlxCfgStatus rc = extractNVInputFile(argc - i, &(argv[i]));
        if (rc != MLX_CFG_OK)
        {
            return rc;
        }
        return extractNVOutputFile(argc - i - 1, &(argv[i + 1]));
    }

    if (_mlxParams.cmd == Mc_SetSystemConf || _mlxParams.cmd == Mc_ValidateSystemConf)
    {
        // set_system_conf and validate_system_conf require a configuration name
        if (argc - i < 1)
        {
            return err(true, "%s command requires a configuration name.",
                       _mlxParams.cmd == Mc_SetSystemConf ? "set_system_conf" : "validate_system_conf");
        }
        _mlxParams.systemConfName = argv[i];
        return MLX_CFG_OK;
    }

    try
    {
        if (_mlxParams.cmd == Mc_Query || _mlxParams.cmd == Mc_Reset)
        {
            return extractQueryCfgArgs(argc - i, &(argv[i]));
        }
        else
        {
            return extractSetCfgArgs(argc - i, &(argv[i]));
        }
    }
    catch (MlxcfgException& e)
    {
        return err(true, "%s", e._err.c_str());
    }
}
