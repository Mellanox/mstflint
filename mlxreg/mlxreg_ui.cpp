/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include <assert.h>
#include <common/tools_utils.h>
#include "common/tools_algorithm.h"
#include <common/tools_version.h>
#include <mft_utils/mft_sig_handler.h>
#ifndef MST_UL
#include <tools_layouts/adb_dbs.h>
#include <cmdif/cib_cif.h>
#endif
#include "mlxreg_ui.h"
#include "mlxreg_lib/mlxreg_parser.h"

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#define COLUMNS_SPACE 3
#define VALUE_COLUMN_LINE_LEN 14
#define QUERY_COLUMNS_COLUMN_LINE_LEN 58
#ifdef MST_UL
#define MLXREG_EXEC "mstreg"
#else
#define MLXREG_EXEC "mlxreg"
#endif

#define CHECK_UNIQUE_OP(op)                                                        \
    if (op != CMD_UNKNOWN)                                                         \
    {                                                                              \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define CHECK_UNIQUE_STR(op)                                                       \
    if (op != "")                                                                  \
    {                                                                              \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define CHECK_UNIQUE_UINT(op)                                                      \
    if (op != 0)                                                                   \
    {                                                                              \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define PRINT_LINE(len)           \
    for (int i = 0; i < len; i++) \
    {                             \
        printf("=");              \
    }                             \
    printf("\n");

/************************************
* FLAGS Constants
************************************/
#define DEVICE_FLAG                 "device"
#define DEVICE_FLAG_SHORT           'd'
#define HELP_FLAG                   "help"
#define HELP_FLAG_SHORT             'h'
#define VERSION_FLAG                "version"
#define VERSION_FLAG_SHORT          'v'
#define ADB_FILE_FLAG               "adb_file"
#define ADB_FILE_FLAG_SHORT         'a'
#define REG_NAME_FLAG               "reg_name"
#define REG_NAME_FLAG_SHORT         ' '
#define REG_ID_FLAG                 "reg_id"
#define REG_ID_FLAG_SHORT           ' '
#define IDXES_FLAG                  "indexes"
#define IDXES_FLAG_SHORT            'i'
#define OPS_FLAG                    "op"
#define OPS_FLAG_SHORT              'o'
#define REG_LEN_FLAG                "reg_len"
#define REG_LEN_FLAG_SHORT          ' '
#define OP_GET_FLAG                 "get"
#define OP_GET_FLAG_SHORT           'g'
#define OP_SET_FLAG                 "set"
#define OP_SET_FLAG_SHORT           's'
#define OP_SHOW_REG_FLAG            "show_reg"
#define OP_SHOW_REG_FLAG_SHORT      ' '
#define OP_SHOW_REGS_FLAG           "show_regs"
#define OP_SHOW_REGS_FLAG_SHORT     ' '
#define OP_SHOW_ALL_REGS_FLAG       "show_all_regs"
#define OP_SHOW_ALL_REGS_FLAG_SHORT ' '
#define IGNORE_REG_CHECK_FLAG "ignore_reg_check"
#define IGNORE_REG_CHECK_FLAG_SHORT ' '
#define FORCE_FLAG "yes"
#define FORCE_FLAG_SHORT ' '
#define IGNORE_RO "ignore_ro"
#define IGNORE_RO_SHORT ' '
#define FILE_TO_DUMP_BUFFER "output_file"
#define FILE_TO_DUMP_BUFFER_SHORT ' '
#define FILE_IO "file_io"
#define FILE_IO_SHORT ' '
#define OVERWRITE_FLAG "overwrite"
#define OVERWRITE_FLAG_SHORT 'w'
#define FULL_PATH_FLAG "full_path"
#define FULL_PATH_FLAG_SHORT ' '
#define GEN_CMD_BUFFER_FLAG "gen_cmd_buffer"
#define GEN_CMD_BUFFER_FLAG_SHORT ' '
#define NO_DYNAMIC_FLAG "no_dynamic"
#define NO_DYNAMIC_FLAG_SHORT ' '

using namespace mlxreg;
namespace Algorithm = mstflint::common::algorithm;
/************************************
 * Function: stringToPrmAdbType
 ************************************/
static PrmAdbType stringToPrmAdbType(const std::string& deviceType)
{
    if (Algorithm::to_lower_copy(deviceType) == "hca")
        return PrmAdbType::PRM_ADB_TYPE_HCA;
    if (Algorithm::to_lower_copy(deviceType) == "switch")
        return PrmAdbType::PRM_ADB_TYPE_SWITCH;
    if (Algorithm::to_lower_copy(deviceType) == "retimer")
        return PrmAdbType::PRM_ADB_TYPE_RETIMER;
    if (Algorithm::to_lower_copy(deviceType) == "gpu")
        return PrmAdbType::PRM_ADB_TYPE_GPU;
    return PrmAdbType::PRM_ADB_TYPE_UNKNOWN;
}

/************************************
 * Function: MlxRegUi
 ************************************/
MlxRegUi::MlxRegUi() : CommandLineRequester("mlxreg OPTIONS"), _cmdParser("mlxreg")
{
    initCmdParser();
    _device = "";
    _mf = NULL;
    _extAdbFile = "";
    _regName = "";
    _regID = 0;
    _dataStr = "";
    _indexesStr = "";
    _dataLen = 0;
    _ignoreCapCheck = false;
    _op = CMD_UNKNOWN;
    _force = false;
    _ignore_ro = false;
    _output_file = "";
    _file_io = "";
    _overwrite = false;
    _full_path = false;
    _use_dynamic = true;
    _gen_cmd_buffer_device_type = "";

#if defined(EXTERNAL) || defined(MST_UL)
    _isExternal = true;
#else
    _isExternal = false;
#endif
}

/************************************
 * Function: ~MlxRegUi
 ************************************/
MlxRegUi::~MlxRegUi()
{
    if (_mf)
    {
        mclose(_mf);
    }
}

/************************************
 * Function: initCmdParser
 ************************************/
void MlxRegUi::initCmdParser()
{
    AddOptions(DEVICE_FLAG,       DEVICE_FLAG_SHORT, "MstDevice", "Mellanox mst device name");
    AddOptions(HELP_FLAG,         HELP_FLAG_SHORT, "", "Show help message and exit");
    AddOptions(VERSION_FLAG,      VERSION_FLAG_SHORT, "", "Show version and exit");
    AddOptions(ADB_FILE_FLAG,     ADB_FILE_FLAG_SHORT, "AdbFile", "External ADB file");
    AddOptions(REG_NAME_FLAG,     REG_NAME_FLAG_SHORT, "RegisterName", "Access register name");
    AddOptions(REG_ID_FLAG,       REG_ID_FLAG_SHORT, "RegisterID", "Access register ID");
    AddOptions(IDXES_FLAG,        IDXES_FLAG_SHORT, "RegisterData", "Register data");
    AddOptions(OPS_FLAG,          OPS_FLAG_SHORT, "RegisterData", "Register data");
    AddOptions(REG_LEN_FLAG,      REG_LEN_FLAG_SHORT, "RegisterDataLen", "Register data length");
    AddOptions(IGNORE_REG_CHECK_FLAG, IGNORE_REG_CHECK_FLAG_SHORT, "", "");
    AddOptions(OP_GET_FLAG, OP_GET_FLAG_SHORT, "", "Register access GET");
    AddOptions(OP_SET_FLAG, OP_SET_FLAG_SHORT, "RegisterData", "Register access SET");
    AddOptions(OP_SHOW_REG_FLAG, OP_SHOW_REG_FLAG_SHORT, "RegisterName",
               "Print register <reg_name> properties and exit");
    AddOptions(OP_SHOW_REGS_FLAG, OP_SHOW_REGS_FLAG_SHORT, "", "Print available registers names and exit");
    AddOptions(OP_SHOW_ALL_REGS_FLAG, OP_SHOW_ALL_REGS_FLAG_SHORT, "", "");
    AddOptions(FORCE_FLAG, FORCE_FLAG_SHORT, "", "");
    AddOptions(IGNORE_RO, IGNORE_RO_SHORT, "", "Ignore the access check in the SET operation");
    AddOptions(FILE_TO_DUMP_BUFFER, FILE_TO_DUMP_BUFFER_SHORT, "OutputFile",
               "Dump buffer to file instead of sending to device");
    AddOptions(FILE_IO, FILE_IO_SHORT, "FilePath", "Work with file for IO instead of CLI flags");
    AddOptions(OVERWRITE_FLAG, OVERWRITE_FLAG_SHORT, "",
               "Set only specified fields, set unspecified fields to zero (only valid for SET command)");
    AddOptions(FULL_PATH_FLAG, FULL_PATH_FLAG_SHORT, "", "Show field names with full hierarchical path");
    AddOptions(NO_DYNAMIC_FLAG, NO_DYNAMIC_FLAG_SHORT, "",
               "Disable dynamic ADB features, conditional unions and arrays");
    AddOptions(
      GEN_CMD_BUFFER_FLAG, GEN_CMD_BUFFER_FLAG_SHORT, "DeviceType",
      "Generate register buffer without sending to device (offline operation, no device required, only valid for GET/SET with --reg_name). DeviceType: HCA|Switch|Retimer|GPU");
    _cmdParser.AddRequester(this);
}

/************************************
 * Function: printFlagLine
 ************************************/
static void printFlagLine(const char flag_s, string flag_l, string param, string desc)
{
    string sflags_s(1, flag_s);
    if (sflags_s != " ")
    {
        printf(IDENT2 "-%-2s|--%-10s", sflags_s.c_str(), flag_l.c_str());
    }
    else
    {
        printf(IDENT2 "--%-14s", flag_l.c_str());
    }
    if (param.length())
    {
        printf(" <%s>", param.c_str());
    }
    else
    {
        printf("\t");
    }
    printf(IDENT3 ": %-30s\n", desc.c_str());
}

/************************************
 * Function: PrintHelp
 ************************************/
void MlxRegUi::printHelp()
{
    // print opening
    printf(IDENT "NAME:\n" IDENT2 MLXREG_EXEC "\n" IDENT "SYNOPSIS:\n" IDENT2 MLXREG_EXEC " [OPTIONS]\n");
    printf(IDENT "DESCRIPTION:\n" IDENT2
                 "Exposes supported access registers, and allows users to obtain information regarding\n" IDENT2
                 "the registers fields and attributes, and to set and get data with specific\n" IDENT2 "register.\n");
    // print options
    printf("\n");
    printf(IDENT "OPTIONS:\n");
    printFlagLine(HELP_FLAG_SHORT,          HELP_FLAG,         "", "Display help message.");
    printFlagLine(VERSION_FLAG_SHORT,       VERSION_FLAG,      "", "Display version info.");
    printFlagLine(DEVICE_FLAG_SHORT,        DEVICE_FLAG,       "device", "Perform operation for a specified mst device.");
    printFlagLine(ADB_FILE_FLAG_SHORT,      ADB_FILE_FLAG,     "adb_file", "An external ADB file");
    printFlagLine(REG_NAME_FLAG_SHORT,      REG_NAME_FLAG,     "reg_name", "Known access register name");
    printFlagLine(REG_ID_FLAG_SHORT,        REG_ID_FLAG,       "reg_ID", "Access register ID");
    printFlagLine(REG_LEN_FLAG_SHORT,       REG_LEN_FLAG,      "reg_length", "Access register layout length (bytes)");
    printFlagLine(IDXES_FLAG_SHORT,         IDXES_FLAG,        "idxs_vals", "Register indexes");
    printFlagLine(OPS_FLAG_SHORT,           OPS_FLAG,          "ops_vals", "Register optional fields");
    printFlagLine(OP_GET_FLAG_SHORT,        OP_GET_FLAG,       "", "Register access GET");
    printFlagLine(OP_SET_FLAG_SHORT,        OP_SET_FLAG,       "reg_dataStr", "Register access SET");
    printFlagLine(OP_SHOW_REG_FLAG_SHORT, OP_SHOW_REG_FLAG, "reg_name",
                  "Print the fields of a given reg access (must have reg_name)");
    printFlagLine(OP_SHOW_REGS_FLAG_SHORT,  OP_SHOW_REGS_FLAG, "", "Print all available reg access'");
    printFlagLine(FORCE_FLAG_SHORT,         FORCE_FLAG,        "", "Non-interactive mode, answer yes to all questions");
    printFlagLine(OVERWRITE_FLAG_SHORT, OVERWRITE_FLAG, "",
                  "Set only specified fields, set unspecified fields to zero (only valid for SET command)");
    printFlagLine(FULL_PATH_FLAG_SHORT, FULL_PATH_FLAG, "", "Show field names with full hierarchical path");
    printFlagLine(NO_DYNAMIC_FLAG_SHORT, NO_DYNAMIC_FLAG, "",
                  "Disable dynamic ADB features, conditional unions and arrays");
    printFlagLine(
      GEN_CMD_BUFFER_FLAG_SHORT, GEN_CMD_BUFFER_FLAG, "DeviceType",
      "Generate register buffer without sending to device (offline operation, no device required, only valid for GET/SET with --reg_name). DeviceType: HCA|Switch|Retimer|GPU");
    // print usage examples
    printf("\n");
    printf(IDENT "Examples:\n");
    printf(IDENT2 "%-40s: %s\n", "Show all available access register", MLXREG_EXEC " -d <device> --show_regs");
    printf(IDENT2 "%-40s: %s\n", "Show all fields of register PAOS", MLXREG_EXEC " -d <device> --show_reg PAOS");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "GET PAOS with indexes: local port 0x1 and swid 0x5",
           MLXREG_EXEC " -d <device> --get --reg_name PAOS --indexes \"local_port=0x1,swid=0x5\"");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "SET PAOS with indexes: local port 0x1 and swid 0x5, and data: e 0x0",
           MLXREG_EXEC " -d <device> --set \"e=0x0\" --reg_name PAOS --indexes \"local_port=0x1,swid=0x5\"");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Generate buffer without sending to device (offline)",
           MLXREG_EXEC " --get --reg_name PAOS --indexes \"local_port=0x1\" --gen_cmd_buffer gpu");
    printf("\n");
}

/************************************
 * Function: printRegNames
 ************************************/
void MlxRegUi::printRegNames(std::vector<string> regs)
{
    printf("Available Access Registers\n");
    PRINT_LINE(104);
    for (std::vector<string>::size_type i = 0; i != regs.size(); i++)
    {
        printf("%-30s\n", regs[i].c_str());
    }
}


/************************************
 * Function: printBuff
 ************************************/
void MlxRegUi::printBuff(std::vector<u_int32_t> buff)
{
    u_int32_t rawAddr = 0;
    printf("Address    | Data\n");
    PRINT_LINE(23);
    for (std::vector<u_int32_t>::size_type i = 0; i != buff.size(); i++)
    {
        printf("0x%08x | 0x%08x\n", rawAddr, CPU_TO_BE32(buff[i]));
        rawAddr += 4;
    }
    PRINT_LINE(23);
}

/************************************
 * Function: printRawBuffer
 ************************************/
void MlxRegUi::printRawBuffer(std::vector<u_int32_t> buff)
{
    printf("Raw Buffer Data:\n");
    PRINT_LINE(35);
    for (std::vector<u_int32_t>::size_type i = 0; i != buff.size(); i++)
    {
        printf("Word[%02lu]: 0x%08x\n", (unsigned long)i, CPU_TO_BE32(buff[i]));
    }
    PRINT_LINE(35);
}

/************************************
 * Function: askUser
 ************************************/
bool MlxRegUi::askUser(const char* question)
{
    printf("\n %s ? (y/n) [n] : ", question);
    if (_force)
    {
        printf("y\n");
    }
    else
    {
        mft_restore_and_raise();
        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);
        if (strcasecmp(answer.c_str(), "y") && strcasecmp(answer.c_str(), "yes"))
        {
            return false;
        }
        mft_signal_set_handling(1); // set again in case we move from here to another critical section.
    }
    return true;
}

/************************************
 * Function: HandleOption
 ************************************/
ParseStatus MlxRegUi::HandleOption(string name, string value)
{
    if (name == HELP_FLAG)
    {
        printHelp();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == VERSION_FLAG)
    {
#if defined(EXTERNAL) || defined(MST_UL)
        print_version_string(MLXREG_EXEC, NULL);
#else
        print_version_string("mlxreg (internal)", NULL);
#endif
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == DEVICE_FLAG)
    {
        _device = value;
        return PARSE_OK;
    }
    else if (name == ADB_FILE_FLAG)
    {
        _extAdbFile = value;
        return PARSE_OK;
    }
    else if (name == IDXES_FLAG)
    {
        _indexesStr = value;
        return PARSE_OK;
    }
    else if (name == OPS_FLAG)
    {
        _opsStr = value;
        return PARSE_OK;
    }
    else if (name == REG_NAME_FLAG)
    {
        CHECK_UNIQUE_UINT(_regID);
        CHECK_UNIQUE_UINT(_dataLen);
        _regName = value;
        return PARSE_OK;
    }
    else if (name == REG_ID_FLAG)
    {
        CHECK_UNIQUE_STR(_regName);
        RegAccessParser::strToUint32((char*)value.c_str(), _regID);
        return PARSE_OK;
    }
    else if (name == REG_LEN_FLAG)
    {
        CHECK_UNIQUE_STR(_regName);
        RegAccessParser::strToUint32((char*)value.c_str(), _dataLen);
        return PARSE_OK;
    }
    else if (name == IGNORE_REG_CHECK_FLAG)
    {
        // TODO: remove IGNORE_REG_CHECK_FLAG from UI after 4.14.0 release, it's deprecated
        cout << endl
             << "-W- The flag --" << IGNORE_REG_CHECK_FLAG << " is deprecated and will be removed." << endl
             << endl;
        return PARSE_OK;
    }
    else if (name == FORCE_FLAG)
    {
        _force = true;
        return PARSE_OK;
    }
    else if (name == OP_SET_FLAG)
    {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SET;
        _dataStr = value;
        return PARSE_OK;
    }
    else if (name == OP_GET_FLAG)
    {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_GET;
        return PARSE_OK;
    }
    else if (name == OP_SHOW_REG_FLAG)
    {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_REG;
        _regName = value;
        return PARSE_OK;
    }
    else if (name == OP_SHOW_REGS_FLAG)
    {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_REGS;
        return PARSE_OK;
    }
    else if (name == OP_SHOW_ALL_REGS_FLAG)
    {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_ALL_REGS;
        return PARSE_OK;
    }
#if !defined(EXTERNAL) && !defined(MST_UL)
    else if (name == IGNORE_RO)
    {
        _ignore_ro = true;
        return PARSE_OK;
    }
    else if (name == FILE_TO_DUMP_BUFFER)
    {
        _output_file = value;
        return PARSE_OK;
    }
    else if (name == FILE_IO)
    {
        _file_io = value;
        return PARSE_OK;
    }
#endif
    else if (name == OVERWRITE_FLAG)
    {
        _overwrite = true;
        return PARSE_OK;
    }
    else if (name == FULL_PATH_FLAG)
    {
        _full_path = true;
        return PARSE_OK;
    }
    else if (name == NO_DYNAMIC_FLAG)
    {
        _use_dynamic = false;
        return PARSE_OK;
    }
    else if (name == GEN_CMD_BUFFER_FLAG)
    {
        _gen_cmd_buffer_device_type = value;

        // Validate device type parameter using stringToPrmAdbType
        if (stringToPrmAdbType(value) == PrmAdbType::PRM_ADB_TYPE_UNKNOWN)
        {
            throw MlxRegException("Invalid device type for --gen_cmd_buffer. Valid values: HCA, Switch, Retimer, GPU");
        }

        return PARSE_OK;
    }
    return PARSE_ERROR;
}

/************************************
 * Function: paramValidate
 ************************************/
void MlxRegUi::paramValidate()
{
    // Check for mutual exclusivity between --gen_cmd_buffer and device
    if (!_gen_cmd_buffer_device_type.empty() && !_device.empty())
    {
        throw MlxRegException("--gen_cmd_buffer is an offline operation and cannot be used with -d/--device flag");
    }

    // Device is required only when not using --gen_cmd_buffer
    if (_gen_cmd_buffer_device_type.empty() && _device.empty())
    {
        throw MlxRegException("you must provide a device name");
    }
    if (_op == CMD_UNKNOWN)
    {
        throw MlxRegException("no operation flag, please read help");
    }
    if (_op == CMD_SHOW_REG)
    {
        if (_regName == "")
        {
            throw MlxRegException("you must provide reg_name in order to use show_register");
        }
        if (_regID != 0)
        {
            throw MlxRegException("you can't use show_register with reg_id");
        }
    }
    if (_op == CMD_GET || _op == CMD_SET)
    {
        if (_regID == 0 && _regName == "")
        {
            throw MlxRegException("you must provide register name or register id when SET/GET");
        }
        // Unknown mode
        if (_regID != 0)
        {
            if (_dataLen == 0)
            {
                throw MlxRegException("you must provide register length when SET/GET using register id");
            }
        }
    }
    else // CMD_SHOW_REG, CMD_SHOW_REGS, CMD_SHOW_ALL_REGS
    {
        if (!_indexesStr.empty())
        {
            throw MlxRegException("indexes flag is only valid for SET/GET commands");
        }
        if (!_opsStr.empty())
        {
            throw MlxRegException("ops flag is only valid for SET/GET commands");
        }
    }
    if (_op == CMD_SET && _dataStr == "")
    {
        throw MlxRegException("you must provide registers data string to use SET");
    }
    if (_op != CMD_SET && _overwrite)
    {
        throw MlxRegException("-w/--overwrite flag is only valid for SET command");
    }
    if (!_gen_cmd_buffer_device_type.empty() && (_op != CMD_GET && _op != CMD_SET))
    {
        throw MlxRegException("--gen_cmd_buffer flag is only valid for GET/SET commands");
    }
    if (!_gen_cmd_buffer_device_type.empty() && _regName == "")
    {
        throw MlxRegException("--gen_cmd_buffer flag is only valid with known mode (must provide --reg_name)");
    }
}

void MlxRegUi::readFromFile(string file_name, vector<u_int32_t>& buff, int len)
{
    ifstream file(file_name.c_str(), ios::binary);

    for (int idx = 0; idx < (len / 4); idx++)
    {
        u_int32_t data;
        file.read((char*)&data, sizeof(u_int32_t));
        if (!file)
        {
            MlxRegException("Failed to read from file");
        }
        buff.push_back(__cpu_to_be32(data));
    }

    file.close();
}

void MlxRegUi::writeToFile(string file_name, vector<u_int32_t> buff)
{
    ofstream file(file_name.c_str(), ios::binary | ios::in | ios::out);// Overwrite the file (in/out)
    for (unsigned int idx = 0; idx < buff.size(); idx++)
    {
        u_int32_t data = __cpu_to_be32(buff[idx]);
        file.write((char*)&data, sizeof(u_int32_t));
    }
    file.close();
}

// Implementation of MlxRegUiImpl template functions

// Constructor
template<bool dynamic>
MlxRegUi::MlxRegUiImpl<dynamic>::MlxRegUiImpl(MlxRegUi* ui) : _ui(ui)
{
}

// Destructor
template<bool dynamic>
MlxRegUi::MlxRegUiImpl<dynamic>::~MlxRegUiImpl()
{
    if (_mlxRegLib)
    {
        delete _mlxRegLib;
    }
}

// getLongestNodeLen implementation
template<bool dynamic>
template<typename T, typename>
size_t MlxRegUi::MlxRegUiImpl<dynamic>::getLongestNodeLen(std::vector<T>& parsed_fields)
{
    size_t len = 0;
    for (const auto& field : parsed_fields)
    {
        if (field.name.size() > len)
        {
            len = field.name.size();
        }
    }
    return (len + COLUMNS_SPACE);
}

// printRegFields implementation
template<bool dynamic>
void MlxRegUi::MlxRegUiImpl<dynamic>::printRegFields(AdbInstance* node)
{
    _query_fields.clear();
    _mlxRegLib->getAdb().traverse_layout(node, "", 0, nullptr, 0, QueryField::on_traverse, (void*)this, false, false,
                                         _ui->_full_path);
    int largestName = (int)getLongestNodeLen(_query_fields);
    printf("%-*s | %-10s | %-8s | %-8s | %-8s\n", largestName, "Field Name", "Address (Bytes)", "Offset (Bits)",
           "Size (Bits)", "Access");
    PRINT_LINE(largestName + QUERY_COLUMNS_COLUMN_LINE_LEN);
    for (typename std::vector<QueryField>::const_iterator it = _query_fields.begin(); it != _query_fields.end(); ++it)
    {
        printf("%-*s | 0x%08x      | %-8d      | %-8ld    | %-15s\n",
               largestName,
               it->name.c_str(),
               (uint32_t)(it->offset >> 3) & ~0x3,
               (uint32_t)it->offset & 0x1F,
               (unsigned long)it->size,
               it->access.c_str());
    }
    PRINT_LINE(largestName + QUERY_COLUMNS_COLUMN_LINE_LEN);
}

// onTraverseSaveFieldData implementation
template<bool dynamic>
bool MlxRegUi::MlxRegUiImpl<dynamic>::SentField::on_traverse(const string& calculated_path,
                                                              uint64_t calculated_offset,
                                                              uint64_t calculated_value,
                                                              AdbInstance* instance,
                                                              void* context)
{
    (void)instance;
    (void)calculated_offset;

    MlxRegUiImpl* impl = (MlxRegUiImpl*)context;
    SentField field;

    field.name = calculated_path;
    field.value = calculated_value;
    impl->_parsed_fields.push_back(field);

    return false; // continue traversal
}

// QueryField::on_traverse implementation (empty for now)
template<bool dynamic>
bool MlxRegUi::MlxRegUiImpl<dynamic>::QueryField::on_traverse(const string& calculated_path,
                                                              uint64_t calculated_offset,
                                                              uint64_t calculated_value,
                                                              AdbInstance* instance,
                                                              void* context)
{
    (void)calculated_value;

    MlxRegUiImpl* impl = (MlxRegUiImpl*)context;
    QueryField field;

    field.name = calculated_path;
    field.offset = calculated_offset;
    field.size = instance->fieldDesc->eSize();
    field.access = RegAccessParser::getAccess(instance);
    impl->_query_fields.push_back(field);

    return false; // continue traversal
}

// printAdbContext implementation
template<bool dynamic>
void MlxRegUi::MlxRegUiImpl<dynamic>::printAdbContext(AdbInstance* node, const std::vector<u_int32_t>& buff)
{
    _parsed_fields.clear();
    _mlxRegLib->getAdb().traverse_layout(node, "", 0, (uint8_t*)&buff[0], buff.size() * sizeof(u_int32_t),
                                         SentField::on_traverse, (void*)this, true, false, _ui->_full_path);
    int largestName = (int)getLongestNodeLen(_parsed_fields);
    printf("%-*s | %-8s\n", largestName, "Field Name", "Data");
    PRINT_LINE(largestName + VALUE_COLUMN_LINE_LEN);
    for (typename std::vector<SentField>::const_iterator it = _parsed_fields.begin(); it != _parsed_fields.end(); ++it)
    {
        printf("%-*s | 0x%08x\n", largestName, it->name.c_str(), (uint32_t)it->value);
    }
    PRINT_LINE(largestName + VALUE_COLUMN_LINE_LEN);
}

// sendCmdBasedOnFileIo implementation
template<bool dynamic>
void MlxRegUi::MlxRegUiImpl<dynamic>::sendCmdBasedOnFileIo(maccess_reg_method_t cmd, int reg_size)
{
    std::vector<u_int32_t> buff;

    //* read input from file
    _ui->readFromFile(_ui->_file_io, buff, reg_size);

    //* Send GET command
    _mlxRegLib->sendRegister(_ui->_regName, cmd, buff);

    //* Write output to file (for GET)
    if (cmd == MACCESS_REG_METHOD_GET)
    {
        _ui->writeToFile(_ui->_file_io, buff);
    }
}

// run implementation
template<bool dynamic>
void MlxRegUi::MlxRegUiImpl<dynamic>::run()
{
    // Init device only when not using --gen_cmd_buffer (offline operation)
    if (_ui->_gen_cmd_buffer_device_type.empty())
    {
        _ui->_mf = mopen_adv(_ui->_device.c_str(), (MType)(MST_DEFAULT | MST_LINKX_CHIP));
    if (!_ui->_mf)
    {
        throw MlxRegException("Failed to open device: \"" + _ui->_device + "\", " + strerror(errno));
    }

    if (!MlxRegUiImpl<dynamic>::MlxRegLib::isDeviceSupported(_ui->_mf))
    {
        throw MlxRegException("Device is not supported");
    }

    _mlxRegLib = new typename MlxRegUiImpl<dynamic>::MlxRegLib(_ui->_mf, _ui->_extAdbFile, _ui->_isExternal);
    }
    else
    {
        // For --gen_cmd_buffer, create MlxRegLib without device (offline mode)
        PrmAdbType deviceType = stringToPrmAdbType(_ui->_gen_cmd_buffer_device_type);
        _mlxRegLib =
          new typename MlxRegUiImpl<dynamic>::MlxRegLib(NULL, _ui->_extAdbFile, _ui->_isExternal, deviceType);
    }

    std::vector<typename MlxRegUiImpl<dynamic>::AdbInstance*> regFields;
    std::vector<string> regs;
    typename MlxRegUiImpl<dynamic>::AdbInstance* regNode = NULL;
    std::vector<u_int32_t> buff;
    u_int32_t max_reg_size = _ui->_mf != NULL ? mget_max_reg_size(_ui->_mf, MACCESS_REG_METHOD_GET) : ICMD_MAX_REG_SIZE;

    if (_ui->_regName != "" && (_ui->_op == CMD_SHOW_REG || _ui->_op == CMD_GET || _ui->_op == CMD_SET))
    {
        _mlxRegLib->set_current_node(_ui->_regName);
    }

    switch (_ui->_op)
    {
        case CMD_SHOW_REG:
            regNode = _mlxRegLib->get_current_node();
            printRegFields(regNode);
            break;

        case CMD_SHOW_REGS:
            _mlxRegLib->showRegisters(regs);
            _ui->printRegNames(regs);
            break;

        case CMD_SHOW_ALL_REGS:
            // TODO: remove CMD_SHOW_ALL_REGS from UI after 4.14.0 release, it's deprecated
            cout << endl
                 << "-W- The option --" << OP_SHOW_ALL_REGS_FLAG << " is deprecated and will be removed, please use --"
                 << OP_SHOW_REGS_FLAG << " instead." << endl
                 << endl;
            _mlxRegLib->showRegisters(regs);
            _ui->printRegNames(regs);
            break;

        case CMD_GET:
        {
            if (_ui->_file_io != "")
            {
                assert(_ui->_regName != "");
                int reg_size = (_mlxRegLib->get_current_node()->get_size()) / 8; // in Bytes
                sendCmdBasedOnFileIo(MACCESS_REG_METHOD_GET, reg_size);
                break;
            }

            if (_ui->_regName != "")
            {
                regNode = _mlxRegLib->get_current_node();
            }
            typename MlxRegUiImpl<dynamic>::RegAccessParser parser(
              _ui->_dataStr, _ui->_indexesStr, _ui->_opsStr, &_mlxRegLib->getAdb(), regNode,
              _ui->_dataLen ? _ui->_dataLen : max_reg_size, false, _ui->_full_path);
            buff = parser.genBuff();
            if (!_ui->_gen_cmd_buffer_device_type.empty())
            {
                printf("Generated GET buffer for register: %s\n", _ui->_regName.c_str());
                std::vector<u_int32_t> generatedBuff =
                  _mlxRegLib->generate_cmd_buffer(_ui->_regName, MACCESS_REG_METHOD_GET, buff);
                _ui->printRawBuffer(generatedBuff);
            }
            else
            {
                printf("Sending access register...\n\n");
                if (_ui->_regName != "")
                { // Known mode
                    _mlxRegLib->sendRegister(_ui->_regName, MACCESS_REG_METHOD_GET, buff);
                    printAdbContext(regNode, buff);
                }
                else
                { // Unknown mode
                    _mlxRegLib->sendRegister(_ui->_regID, MACCESS_REG_METHOD_GET, buff);
                _ui->printBuff(buff);
            }
        }
        }
        break;

        case CMD_SET:
        {
            if (_ui->_file_io != "")
            {
                int reg_size = (_mlxRegLib->get_current_node()->get_size()) / 8; // in Bytes
                sendCmdBasedOnFileIo(MACCESS_REG_METHOD_SET, reg_size);
                break;
            }

            if (_ui->_regName != "")
            {
                regNode = _mlxRegLib->get_current_node();
            }
            // Read current register data into buffer
            typename MlxRegUiImpl<dynamic>::RegAccessParser parserGet(
              _ui->_dataStr, _ui->_indexesStr, _ui->_opsStr, &_mlxRegLib->getAdb(), regNode,
              _ui->_dataLen ? _ui->_dataLen : max_reg_size, _ui->_ignore_ro, _ui->_full_path);
            buff = parserGet.genBuff();
            if (!_ui->_overwrite && _ui->_gen_cmd_buffer_device_type.empty())
            {
                if (_ui->_regName != "")
                { // Known mode
                    _mlxRegLib->sendRegister(_ui->_regName, MACCESS_REG_METHOD_GET, buff);
                }
                else
                { // Unknown mode
                    _mlxRegLib->sendRegister(_ui->_regID, MACCESS_REG_METHOD_GET, buff);
                }
            }
            // Update the register buffer with user inputs
            typename MlxRegUiImpl<dynamic>::RegAccessParser parser(_ui->_dataStr, _ui->_indexesStr, _ui->_opsStr,
                                                                   &_mlxRegLib->getAdb(), regNode, buff,
                                                                   _ui->_ignore_ro, _ui->_full_path);
            buff = parser.genBuff();
            if (_ui->_output_file != "")
            {
                printAdbContext(regNode, buff);
                _mlxRegLib->dumpRegisterData(_ui->_output_file, buff);
                break;
            }
            if (!_ui->_gen_cmd_buffer_device_type.empty())
            {
                printf("Generated SET buffer for register: %s\n", _ui->_regName.c_str());
                std::vector<u_int32_t> generatedBuff =
                  _mlxRegLib->generate_cmd_buffer(_ui->_regName, MACCESS_REG_METHOD_SET, buff);
                _ui->printRawBuffer(generatedBuff);
            }
            else
            {
            if (_ui->_regName != "")
                { // Known mode
                    printf("You are about to send access register: %s with the following data:\n",
                           _ui->_regName.c_str());
                    printAdbContext(regNode, buff);
                    if (_ui->askUser("Do you want to continue"))
                    {
                        printf(" Sending access register...\n");
                        _mlxRegLib->sendRegister(_ui->_regName, MACCESS_REG_METHOD_SET, buff);
                    }
                }
                else
                { // Unknown mode
                    printf("You are about to send access register id: 0x%x with the following data:\n", _ui->_regID);
                    _ui->printBuff(buff);
                    if (_ui->askUser("Do you want to continue"))
                    {
                        printf(" Sending access register...\n");
                        _mlxRegLib->sendRegister(_ui->_regID, MACCESS_REG_METHOD_SET, buff);
                    }
                }
            }
        }
        break;

        default:
            break;
    }
}

void MlxRegUi::run(int argc, char** argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT)
    {
        return;
    }
    else if (rc != PARSE_OK)
    {
        cout << _cmdParser.GetUsage();
        throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
    }
    paramValidate();

    // Runtime dispatch based on --no_dynamic flag (dynamic by default)
    if (_use_dynamic)
    {
        MlxRegUiImpl<true> impl(this);
        impl.run();
    }
    else
    {
        MlxRegUiImpl<false> impl(this);
        impl.run();
    }
}

/************************************
 * Function: main
 ************************************/
int main(int argc, char** argv)
{
    try
    {
        mft_signal_set_msg((char*)"Interrupted, Exiting...");
        mft_signal_set_handling(1);
        MlxRegUi mlxReg;
        mlxReg.run(argc, argv);
    }
    catch (MlxRegException& exp)
    {
        fprintf(stderr, "-E- %s\n", exp.what());
        return 1;
    }
    catch (AdbException& exp)
    {
        fprintf(stderr, "-E- %s\n", exp.what());
        return 1;
    }
    catch (const std::exception& exp)
    {
        fprintf(stderr, "-E- General Exception:%s\n", exp.what());
        return 1;
    }
    return 0;
}

// Explicit template instantiations
template class MlxRegUi::MlxRegUiImpl<false>;
template class MlxRegUi::MlxRegUiImpl<true>;
