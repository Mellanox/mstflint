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

#include "mlxcfg_generic_commander.h"
#include "mlxcfg_commander.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"

using namespace std;


#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#define IDENT4 IDENT2 IDENT

#define FIFTH_GENERATION_LIST "Connect-IB/Connect-X4/LX"
#define FOURTH_GENERATION_LIST "ConnectX3/Pro"

static void printFlagLine(string flag_s, string flag_l, string param, string desc)
{
    string flags = "-" + flag_s + "|--" + flag_l + (param.length() ?  " <" + param + ">" : "");
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
    printf(IDENT "NAME:\n"
           IDENT2 MLXCFG_NAME "\n"
           IDENT "SYNOPSIS:\n"
           IDENT2 MLXCFG_NAME " [Options] <Commands> [Parameters]\n");

    printf(IDENT "DESCRIPTION:\n"
          IDENT2 "Allows the user to change some of the device configurations without having to\n"
          IDENT2 "create and burn a new firmware.");
    // print options
    printf("\n");
    printf(IDENT "OPTIONS:\n");
    printFlagLine("d", "dev", "device", "Perform operation for a specified MST device.");
    printFlagLine("b", "db", "filename", "Use a specific database file.");
    printFlagLine("f", "file", "conf_file", "raw configuration file.");
    printFlagLine("h", "help", "", "Display help message.");
    printFlagLine("v", "version", "", "Display version info.");
    printFlagLine("e", "enable_verbosity", "", "Show default and current configurations.");
    printFlagLine("y", "yes", "", "Answer yes in prompt.");
    printFlagLine("a", "all_attrs", "", "Show all attributes in the XML template");
    printFlagLine("p", "private_key", "", "pem file for private key");
    printFlagLine("u", "key_uuid", "", "keypair uuid");

    //print commands
    printf("\n");
    printf(IDENT "COMMANDS:\n");
    printf(IDENT2 "%-24s : %s\n", "clear_semaphore", "clear the tool semaphore.");
    printf(IDENT2 "%-24s : %s\n", "i[show_confs]", "display information about all configurations.");
    printf(IDENT2 "%-24s : %s\n", "q[uery]", "query supported configurations.");
    printf(IDENT2 "%-24s : %s\n", "r[eset]", "reset all configurations to their default value.");
    printf(IDENT2 "%-24s : %s\n", "s[et]", "set configurations to a specific device.");
    printf(IDENT2 "%-24s : %s\n", "set_raw", "set raw configuration file.(only "  FIFTH_GENERATION_LIST ".)");
    printf(IDENT2 "%-24s : %s\n", "backup", "backup configurations to a file (only "  FIFTH_GENERATION_LIST ".). Use set_raw command to restore file.");
    printf(IDENT2 "%-24s : %s\n", "gen_tlvs_file", "Generate List of all TLVs. TLVs output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "g[en_xml_template]", "Generate XML template. TLVs input file name and XML output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "xml2raw", "Generate Raw file from XML file. XML input file name and raw output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "raw2xml", "Generate XML file from Raw file. raw input file name and XML output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "xml2bin", "Generate binary configuration dump file from XML file. XML input file name and bin output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "create_conf", "Generate configuration file from XML file. XML input file name and bin output file name must be specified. (*)");
    printf(IDENT2 "%-24s : %s\n", "apply", "Apply a configuration file, that was created with create_conf command. bin input file name must be specified. (*)");

    // print supported commands
    printf("\n");
    printf(IDENT "(*) These commands do not require MST device\n\n");
    printf(IDENT "To show supported configurations by device type, run show_confs command\n");
    printf("\n");



    // print usage examples
    printf("\n");
    printf(IDENT "Examples:\n");
    printf(IDENT2 "%-35s: %s\n", "To query configurations", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " query");
    printf(IDENT2 "%-35s: %s\n", "To set configuration", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " set SRIOV_EN=1 NUM_OF_VFS=16 WOL_MAGIC_EN_P1=1");
    printf(IDENT2 "%-35s: %s\n", "To set raw configuration", MLXCFG_NAME " -d " MST_DEV_EXAMPLE2 " -f conf_file set_raw");
    printf(IDENT2 "%-35s: %s\n", "To reset configuration", MLXCFG_NAME " -d " MST_DEV_EXAMPLE " reset");
    printf("\n");
    printf(IDENT "Supported devices:\n");
    printf(IDENT2 "4th Generation devices: ConnectX3, ConnectX3-Pro (FW 2.31.5000 and above).\n");
    printf(IDENT2 "5th Generation devices: ConnectIB, ConnectX4, ConnectX4-LX, ConnectX5.\n");
    printf("\n");
    printf(IDENT "Note: query device to view supported configurations by Firmware.\n");
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
    VECTOR_ITERATOR(ParamView, _mlxParams.setParams, it) {
        if (it->mlxconfigName == tag) {
            return true;
        }
    }
    return false;
}

inline const char* cmdNVInputFileTag(mlxCfgCmd cmd, const char *def)
{
    return (cmd == Mc_XML2Raw || cmd == Mc_XML2Bin || cmd == Mc_CreateConf) ?
           "XML" : (cmd == Mc_Raw2XML) ?
           "Raw" : (cmd == Mc_GenXMLTemplate) ?
           "TLVs" : (cmd == Mc_Apply) ?
           "Configuration" : def;
}

inline const char* cmdNVOutputFileTag(mlxCfgCmd cmd, const char *def)
{
    return (cmd == Mc_XML2Raw) ?
           "Raw" : (cmd == Mc_Raw2XML) ?
           "XML" : (cmd == Mc_GenXMLTemplate) ?
           "XML" : (cmd == Mc_XML2Bin) ?
           "Bin" : (cmd == Mc_CreateConf) ?
           "Configuration" : def;
}

mlxCfgStatus MlxCfg::extractNVInputFile(int argc, char *argv[])
{
    if (argc < 1) {
        return err(true, "%s input file is missing",
                   cmdNVInputFileTag(_mlxParams.cmd, ""));
    }
    _mlxParams.NVInputFile = argv[0];
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractNVOutputFile(int argc, char *argv[])
{
    if (argc < 1) {
        return err(true, "%s output file is missing",
                   cmdNVOutputFileTag(_mlxParams.cmd, ""));
    }
    _mlxParams.NVOutputFile = argv[0];
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractQueryCfgArgs(int argc, char *argv[])
{
    int i = 0;

    for (; i < argc; i++) {
        ParamView pv;
        string mlxconfigName = argv[i];
        if (isIndexedMlxconfigName(mlxconfigName)) {
            string indexStr = parseIndexStr(mlxconfigName);
            vector<u_int32_t> indexes;
            bool isStartFromOneSupported = false;
            extractIndexes(indexStr, indexes);
            if (indexes.size() > 1) {
                size_t p = mlxconfigName.find('[');
                if (p == std::string::npos) {
                    return err(true, "Expected a parameter with index");
                }
                mlxconfigName = mlxconfigName.substr(0, p);
                isStartFromOneSupported = isIndexedStartFromOneSupported(mlxconfigName);

                VECTOR_ITERATOR(u_int32_t, indexes, it) {
                    ParamView paramView;
                    if (isStartFromOneSupported) {
                        if ((int32_t)*it <= 0) {
                            printf("-E- Index is out of range.Minimal index is 1\n");
                            return MLX_CFG_ERROR_NO_USAGE;
                        }
                        else {
                            (*it)--;
                        }
                    }
                    paramView.mlxconfigName = mlxconfigName + "[" + numToStr(*it) + "]";
                    _mlxParams.setParams.push_back(paramView);
                }
                continue;
            } else {
                
                size_t p = mlxconfigName.find('[');
                string subStr = mlxconfigName.substr(0, p);
                if (isIndexedStartFromOneSupported(subStr)) {
                    if ((int32_t)indexes[0] <= 0) {
                        printf("-E- Index is out of range.Minimal index is 1\n");
                        return MLX_CFG_ERROR_NO_USAGE;
                    }
                    pv.mlxconfigName = subStr + "[" + numToStr(indexes[0] - 1) + "]";
                    
                }
                else {
                    pv.mlxconfigName = mlxconfigName;
                }
            }
        } else {
            pv.mlxconfigName = mlxconfigName;
        }
        _mlxParams.setParams.push_back(pv);
    }

    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::extractSetCfgArgs(int argc, char *argv[])
{
    int i = 0;
    string tag, strVal;

    for (; i < argc; i++) {
        char *ptr;
        // get the tag
        ptr = strtok(argv[i], "=");
        if (!ptr) {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }
        tag = ptr; // hopefully its calling copy function.
        // get the val
        ptr = strtok(NULL, "=");
        if (!ptr) {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }
        strVal = ptr;
        if (strtok(NULL, "=")) {
            return err(true, "Invalid Configuration argument %s", argv[i]);
        }

        if (tagExsists(tag)) {
            return err(true, "Duplicate parameter, %s.", tag.c_str());
        }

        ParamView pv;

        if (isIndexedMlxconfigName(tag)) {
            string indexStr = parseIndexStr(tag);
            vector<u_int32_t> indexes;
            extractIndexes(indexStr, indexes);
            bool isStartFromOneSupported = false;
            if (indexes.size() > 1) {
                size_t p = tag.find('[');
                if (p == std::string::npos) {
                    return err(true, "Expected a parameter with index");
                }
                string mlxconfigName = tag.substr(0, p);
                isStartFromOneSupported = isIndexedStartFromOneSupported(mlxconfigName);
                VECTOR_ITERATOR(u_int32_t, indexes, it) {
                    ParamView paramView;
                    paramView.setVal = strVal;

                    if (isStartFromOneSupported) {
                        if (*it == 0) {
                            printf("-E- Index 0 is out of range.Minimal index is 1\n");
                            return MLX_CFG_ERROR_NO_USAGE;
                        }
                        else {
                            (*it)--;
                        }
                    }

                    paramView.mlxconfigName = mlxconfigName + "[" + numToStr(*it) + "]";
                    _mlxParams.setParams.push_back(paramView);
                }
                continue;
            } else {
                size_t p = tag.find('[');
                string subStr = tag.substr(0, p);
                if (isIndexedStartFromOneSupported(subStr)) {
                    if (indexes[0] == 0) {
                        printf("-E- Index 0 is out of range.Minimal index is 1\n");
                        return MLX_CFG_ERROR_NO_USAGE;
                    }
                    pv.mlxconfigName = subStr + "[" + numToStr(indexes[0] - 1) + "]";

                }
                else {
                    pv.mlxconfigName = tag;
                }
            }
        } else {
            pv.mlxconfigName = tag;
        }

        pv.setVal = strVal;
        _mlxParams.setParams.push_back(pv);

    }
    return MLX_CFG_OK;
}



mlxCfgStatus MlxCfg::parseArgs(int argc, char *argv[])
{
    int i = 1;
    for (; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v" || arg == "--version") {
            printVersion();
            return MLX_CFG_OK_EXIT;
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return MLX_CFG_OK_EXIT;
        } else if (arg == "-d" || arg == "--dev") {
            if (++i == argc) {
                return err(true, "missing device name");
            }
            _mlxParams.device = argv[i];
        } else if (arg == "-b" || arg == "--db") {
            if (++i == argc) {
                return err(true, "missing database file name");
            }
            _mlxParams.dbName = argv[i];
        } else if (arg == "-y" || arg == "--yes") {
            _mlxParams.yes = true;
        } else if (arg == "-f" || arg == "--file") {
            if (++i == argc) {
                return err(true, "missing file name");
            }
            _mlxParams.rawTlvFile = argv[i];
        } else if (arg == "-e" || arg == "--enable_verbosity") {
            _mlxParams.enableVerbosity = true;
        } else if (arg == "-a" || arg == "--all_attrs") {
            _mlxParams.allAttrs = true;
        } else if (arg == "-p" || arg == "--private_key") {
            if (++i == argc) {
                return err(true, "missing file name");
            }
            _mlxParams.privPemFile = argv[i];
        } else if (arg == "-u" || arg == "--key_uuid") {
            if (++i == argc) {
                return err(true, "missing file name");
            }
            _mlxParams.keyPairUUID = argv[i];
        } else if (arg == "set" || arg == "s") {
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
        } else if (arg == "backup") {
            _mlxParams.cmd = Mc_Backup;
            break;
        } else if (arg == "gen_tlvs_file" || arg == "t") {
            _mlxParams.cmd = Mc_GenTLVsFile;
            break;
        } else if (arg == "gen_xml_template" || arg == "g") {
            _mlxParams.cmd = Mc_GenXMLTemplate;
            break;
        } else if (arg == "raw2xml" || arg == "r") {
            _mlxParams.cmd = Mc_Raw2XML;
            break;
        } else if (arg == "xml2raw" || arg == "x") {
            _mlxParams.cmd = Mc_XML2Raw;
            break;
        } else if (arg == "xml2bin") {
            _mlxParams.cmd = Mc_XML2Bin;
            break;
        } else if (arg == "create_conf") {
            _mlxParams.cmd = Mc_CreateConf;
            break;
        } else if (arg == "apply") {
            _mlxParams.cmd = Mc_Apply;
            break;
        } else if (arg == "show_confs" || arg == "i") {
            _mlxParams.cmd = Mc_ShowConfs;
            break;
            // hidden flag --force used to ignore parameter checks
        } else if (arg == "--force") {
            _mlxParams.force = true;
        } else {
            return err(true, "invalid argument: %s", arg.c_str());
        }
    }
    i++;
    if (_mlxParams.cmd == Mc_UnknownCmd) {
        return err(true, "No command found. For more information please read the help message:");
    }
    // we parsed input until the set/query/reset cmd
    if (i == argc && _mlxParams.cmd == Mc_Set) {
        return err(true, "missing configuration arguments. For more information please run " MLXCFG_NAME " -h|--help.");
    }
    if (i != argc && (_mlxParams.cmd == Mc_Reset)) {
        return err(true, "%s command expects no argument but %d argument received", "reset", argc - i);
    }
    if ((_mlxParams.cmd == Mc_Set || _mlxParams.cmd == Mc_Clr_Sem || _mlxParams.cmd == Mc_Set_Raw || _mlxParams.cmd == Mc_Backup || _mlxParams.cmd == Mc_ShowConfs || _mlxParams.cmd == Mc_Apply) && _mlxParams.device.length() == 0) {
        return err(true, "%s command expects device to be specified.",
                   _mlxParams.cmd == Mc_Set ?
                   "set" : _mlxParams.cmd == Mc_Set_Raw ?
                   "set_raw" : _mlxParams.cmd == Mc_Clr_Sem ?
                   "clear_semaphore" : _mlxParams.cmd == Mc_Backup ?
                   "backup" : _mlxParams.cmd == Mc_Apply ?
                   "apply" : "show_confs");
    }
    if ((_mlxParams.cmd == Mc_Set_Raw && _mlxParams.rawTlvFile.size() == 0 )) {
        return err(true, "set_raw command expects raw TLV file to be specified.");
    }
    if ((_mlxParams.cmd == Mc_Backup && _mlxParams.rawTlvFile.size() == 0 )) {
        return err(true, "backup command expects file to be specified.");
    }
    if (((_mlxParams.cmd != Mc_Set_Raw && _mlxParams.cmd != Mc_Backup) &&
         _mlxParams.rawTlvFile.size() != 0 )) {
        return err(true, "raw TLV file can only be specified with set_raw command.");
    }

    if (_mlxParams.cmd == Mc_GenTLVsFile) {
        return extractNVOutputFile(argc - i, &(argv[i]));
    }

    if (_mlxParams.cmd == Mc_Apply) {
        return extractNVInputFile(argc - i, &(argv[i]));
    }

    if (_mlxParams.cmd == Mc_CreateConf &&
        (_mlxParams.privPemFile.empty() ^ _mlxParams.keyPairUUID.empty())) {
        return err(true, "if you want to sign the configuration file you have to provide private pem file and key pair uuid file");
    }

    if (_mlxParams.cmd == Mc_GenXMLTemplate
        || _mlxParams.cmd == Mc_XML2Raw
        || _mlxParams.cmd == Mc_Raw2XML
        || _mlxParams.cmd == Mc_XML2Bin
        || _mlxParams.cmd == Mc_CreateConf) {
        mlxCfgStatus rc = extractNVInputFile(argc - i, &(argv[i]));
        if (rc != MLX_CFG_OK) {
            return rc;
        }
        return extractNVOutputFile(argc - i - 1, &(argv[i + 1]));
    }


    try {
        if (_mlxParams.cmd == Mc_Query) {
            return extractQueryCfgArgs(argc - i, &(argv[i]));
        } else {
            return extractSetCfgArgs(argc - i, &(argv[i]));
        }
    } catch (MlxcfgException& e) {
        return err(true, "%s", e._err.c_str());
    }
}

