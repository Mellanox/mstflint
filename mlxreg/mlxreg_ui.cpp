/* 
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
#include <common/tools_utils.h>
#include <common/tools_version.h>
#include <mft_utils/mft_sig_handler.h>
#ifndef MST_UL
#include <tools_layouts/adb_dbs.h>
#include <cmdif/cib_cif.h>
#endif
#include "mlxreg_ui.h"

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#ifdef MST_UL
#define MLXREG_EXEC "mstreg"
#else
#define MLXREG_EXEC "mlxreg"
#endif

#define CHECK_UNIQUE_OP(op) \
    if (op != CMD_UNKNOWN) { \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define CHECK_UNIQUE_STR(op) \
    if (op != "") { \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define CHECK_UNIQUE_UINT(op) \
    if (op != 0) { \
        throw MlxRegException("incompatible flags combination, please read help"); \
    }

#define PRINT_LINE(len) \
    for (int i = 0; i < len; i++) { \
        printf("="); \
    } \
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
#define IGNORE_CAP_CHECK_FLAG       "ignore_cap_check"
#define IGNORE_CAP_CHECK_FLAG_SHORT ' '
#define IGNORE_REG_CHECK_FLAG       "ignore_reg_check"
#define IGNORE_REG_CHECK_FLAG_SHORT ' '
#define FORCE_FLAG                  "yes"
#define FORCE_FLAG_SHORT            ' '

using namespace mlxreg;

/************************************
* Function: MlxRegUi
************************************/
MlxRegUi::MlxRegUi() :
    CommandLineRequester("mlxreg OPTIONS"),
    _cmdParser("mlxreg")
{
    initCmdParser();
    _device         = "";
    _mf             = NULL;
    _extAdbFile     = "";
    _regName        = "";
    _regID          = 0;
    _dataStr        = "";
    _indexesStr     = "";
    _dataLen        = 0;
    _ignoreCapCheck = false;
    _op             = CMD_UNKNOWN;
    _mlxRegLib      = NULL;
    _force          = false;
#if defined(EXTERNAL) || defined(MST_UL)
    _isExternal     = true;
#else
    _isExternal     = false;
#endif
}

/************************************
* Function: ~MlxRegUi
************************************/
MlxRegUi::~MlxRegUi()
{
    if (_mf) {
        mclose(_mf);
    }
    if (_mlxRegLib) {
        delete _mlxRegLib;
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
    AddOptions(REG_LEN_FLAG,      REG_LEN_FLAG_SHORT, "RegisterDataLen", "Register data length");
    AddOptions(IGNORE_CAP_CHECK_FLAG, IGNORE_CAP_CHECK_FLAG_SHORT, "", "");
    AddOptions(IGNORE_REG_CHECK_FLAG, IGNORE_REG_CHECK_FLAG_SHORT, "", "");
    AddOptions(OP_GET_FLAG,       OP_GET_FLAG_SHORT, "", "Register access GET");
    AddOptions(OP_SET_FLAG,       OP_SET_FLAG_SHORT, "RegisterData", "Register access SET");
    AddOptions(OP_SHOW_REG_FLAG,  OP_SHOW_REG_FLAG_SHORT, "RegisterName", "Print register <reg_name> properties and exit");
    AddOptions(OP_SHOW_REGS_FLAG, OP_SHOW_REGS_FLAG_SHORT, "", "Print available registers names and exit");
    AddOptions(OP_SHOW_ALL_REGS_FLAG, OP_SHOW_ALL_REGS_FLAG_SHORT, "", "");
    AddOptions(FORCE_FLAG, FORCE_FLAG_SHORT, "", "");
    _cmdParser.AddRequester(this);
}

/************************************
* Function: printFlagLine
************************************/
static void printFlagLine(const char flag_s, string flag_l, string param, string desc)
{
    string sflags_s(1, flag_s);
    if (sflags_s != " ") {
        printf(IDENT2 "-%-2s|--%-10s", sflags_s.c_str(), flag_l.c_str());
    } else {
        printf(IDENT2 "--%-14s", flag_l.c_str());
    }
    if (param.length()) {
        printf(" <%s>", param.c_str());
    } else {
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
    printf(
        IDENT "NAME:\n"
        IDENT2 MLXREG_EXEC "\n"
        IDENT "SYNOPSIS:\n"
        IDENT2 MLXREG_EXEC " [OPTIONS]\n");
    printf(
        IDENT "DESCRIPTION:\n"
        IDENT2 "Exposes supported access registers, and allows users to obtain information regarding\n"
        IDENT2 "the registers fields and attributes, and to set and get data with specific\n"
        IDENT2 "register.\n");
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
    printFlagLine(OP_GET_FLAG_SHORT,        OP_GET_FLAG,       "", "Register access GET");
    printFlagLine(OP_SET_FLAG_SHORT,        OP_SET_FLAG,       "reg_dataStr", "Register access SET");
    printFlagLine(OP_SHOW_REG_FLAG_SHORT,   OP_SHOW_REG_FLAG,  "reg_name", "Print the fields of a given reg access (must have reg_name)");
    printFlagLine(OP_SHOW_REGS_FLAG_SHORT,  OP_SHOW_REGS_FLAG, "", "Print all available reg access'");
    printFlagLine(FORCE_FLAG_SHORT,         FORCE_FLAG,        "", "Non-interactive mode, answer yes to all questions");

    // print usage examples
    printf("\n");
    printf(IDENT "Examples:\n");
    printf(IDENT2 "%-40s: %s\n", "Show all available access register", MLXREG_EXEC " -d <device> --show_regs");
    printf(IDENT2 "%-40s: %s\n", "Show all fields of register PAOS", MLXREG_EXEC " -d <device> --show_reg PAOS");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "GET PAOS with indexes: local port 0x1 and swid 0x5",
           MLXREG_EXEC " -d <device> --get --reg_name PAOS --indexes \"local_port=0x1,swid=0x5\"");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "SET PAOS with indexes: local port 0x1 and swid 0x5, and data: e 0x0",
           MLXREG_EXEC " -d <device> --set \"e=0x0\" --reg_name PAOS --indexes \"local_port=0x1,swid=0x5\"");
    printf("\n");
}

/************************************
* Function: getLongestNodeLen
************************************/
size_t getLongestNodeLen(std::vector<AdbInstance*> root)
{
    size_t len = 0;
    for (std::vector<AdbInstance*>::size_type i = 0; i != root.size(); i++) {
        if (strlen(root[i]->name.c_str()) > len) {
            len = strlen(root[i]->name.c_str());
        }
    }
    return (len + 3);
}

/************************************
* Function: printRegFields
************************************/
void MlxRegUi::printRegFields(vector<AdbInstance*> nodeFields)
{
    int largestName = (int)getLongestNodeLen(nodeFields);
    printf("%-*s | %-10s | %-8s | %-8s | %-8s\n", largestName, "Field Name", "Address (Bytes)", "Offset (Bits)", "Size (Bits)", "Access");
    PRINT_LINE(58 + largestName);
    for (std::vector<AdbInstance*>::size_type i = 0; i != nodeFields.size(); i++) {
        printf("%-*s | 0x%08x      | %-8d      | %-8d    | %-15s\n",
               largestName,
               nodeFields[i]->name.c_str(),
               (nodeFields[i]->offset >> 3) & ~0x3,
               nodeFields[i]->startBit(),
               nodeFields[i]->fieldDesc->eSize(),
               RegAccessParser::getAccess(nodeFields[i]).c_str());
    }
    PRINT_LINE(58 + largestName);;
}

/************************************
* Function: printRegNames
************************************/
void MlxRegUi::printRegNames(std::vector<string> regs)
{
    printf("Available Access Registers\n");
    PRINT_LINE(104);
    for (std::vector<string>::size_type i = 0; i != regs.size(); i++) {
        printf("%-30s\n", regs[i].c_str());
    }
}

/************************************
* Function: printAdbContext
************************************/
void MlxRegUi::printAdbContext(AdbInstance *node, std::vector<u_int32_t> buff)
{
    std::vector<AdbInstance*> subItems = node->getLeafFields();
    int largestName = (int)getLongestNodeLen(subItems);
    printf("%-*s | %-8s\n", largestName, "Field Name", "Data");
    PRINT_LINE(largestName + 14);
    for (std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++) {
        printf("%-*s | 0x%08x\n",
               largestName,
               subItems[i]->name.c_str(),
               (unsigned int)subItems[i]->popBuf((u_int8_t*)&buff[0]));
    }
    PRINT_LINE(largestName + 14);
}

/************************************
* Function: printAdbContext
************************************/
void MlxRegUi::printBuff(std::vector<u_int32_t> buff)
{
    u_int32_t rawAddr = 0;
    printf("Address    | Data\n");
    PRINT_LINE(23);
    for (std::vector<u_int32_t>::size_type i = 0; i != buff.size(); i++) {
        printf("0x%08x | 0x%08x\n", rawAddr, CPU_TO_BE32(buff[i]));
        rawAddr += 4;
    }
    PRINT_LINE(23);
}

/************************************
* Function: askUser
************************************/
bool MlxRegUi::askUser(const char *question)
{
    printf("\n %s ? (y/n) [n] : ", question);
    if (_force) {
        printf("y\n");
    } else {
        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);
        if (strcasecmp(answer.c_str(), "y") &&
            strcasecmp(answer.c_str(), "yes")) {
            return false;
        }
    }
    return true;
}

/************************************
* Function: HandleOption
************************************/
ParseStatus MlxRegUi::HandleOption(string name, string value)
{
    if (name == HELP_FLAG) {
        printHelp();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
#if defined(EXTERNAL) || defined(MST_UL)
        print_version_string(MLXREG_EXEC, NULL);
#else
        print_version_string("mlxreg (internal)", NULL);
#endif
        return PARSE_OK_WITH_EXIT;
    } else if (name == DEVICE_FLAG) {
        _device = value;
        return PARSE_OK;
    } else if (name == ADB_FILE_FLAG) {
        _extAdbFile = value;
        return PARSE_OK;
    } else if (name == IDXES_FLAG) {
        _indexesStr = value;
        return PARSE_OK;
    } else if (name == REG_NAME_FLAG) {
        CHECK_UNIQUE_UINT(_regID);
        CHECK_UNIQUE_UINT(_dataLen);
        _regName = value;
        return PARSE_OK;
    } else if (name == REG_ID_FLAG) {
        CHECK_UNIQUE_STR(_regName);
        RegAccessParser::strToUint32((char*)value.c_str(), _regID);
        return PARSE_OK;
    } else if (name == REG_LEN_FLAG) {
        CHECK_UNIQUE_STR(_regName);
        RegAccessParser::strToUint32((char*)value.c_str(), _dataLen);
        return PARSE_OK;
    }
#if !defined(EXTERNAL) && !defined(MST_UL)
    else if (name == IGNORE_CAP_CHECK_FLAG) {
        _ignoreCapCheck = true;
        return PARSE_OK;
    }
#endif
    else if (name == IGNORE_REG_CHECK_FLAG) {
        // TODO: remove IGNORE_REG_CHECK_FLAG from UI after 4.14.0 release, it's deprecated
        cout << endl << "-W- The flag --" << IGNORE_REG_CHECK_FLAG
             << " is deprecated and will be removed." << endl << endl;
        return PARSE_OK;
    } else if (name == FORCE_FLAG) {
        _force = true;
        return PARSE_OK;
    } else if (name == OP_SET_FLAG) {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SET;
        _dataStr = value;
        return PARSE_OK;
    } else if (name == OP_GET_FLAG) {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_GET;
        return PARSE_OK;
    } else if (name == OP_SHOW_REG_FLAG) {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_REG;
        _regName = value;
        return PARSE_OK;
    } else if (name == OP_SHOW_REGS_FLAG) {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_REGS;
        return PARSE_OK;
    } else if (name == OP_SHOW_ALL_REGS_FLAG) {
        CHECK_UNIQUE_OP(_op);
        _op = CMD_SHOW_ALL_REGS;
        return PARSE_OK;
    }

    return PARSE_ERROR;
}

/************************************
* Function: paramValidate
************************************/
void MlxRegUi::paramValidate()
{
    if (_device == "") {
        throw MlxRegException("you must provide a device name");
    }
    if (_op == CMD_UNKNOWN) {
        throw MlxRegException("no operation flag, please read help");
    }
    if (_op == CMD_SHOW_REG) {
        if (_regName == "") {
            throw MlxRegException("you must provide reg_name in order to use show_register");
        }
        if (_regID != 0) {
            throw MlxRegException("you can't use show_register with reg_id");
        }
    }
    if (_op == CMD_GET || _op == CMD_SET) {
        if (_regID == 0 && _regName == "") {
            throw MlxRegException("you must provide register name or register id when SET/GET");
        }
        // Unknown mode
        if (_regID != 0) {
            if (_dataLen == 0) {
                throw MlxRegException("you must provide register length when SET/GET using register id");
            }
        }
    }
    if (_op == CMD_SET && _dataStr == "") {
        throw MlxRegException("you must provide registers data string to use SET");
    }
}

void MlxRegUi::run(int argc, char **argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT) {
        return;
    } else if (rc == PARSE_ERROR) {
        cout << _cmdParser.GetUsage();
        throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
    }
    paramValidate();
    // Init device
    _mf = mopen(_device.c_str());
    if (!_mf) {
        throw MlxRegException("Failed to open device: \"" + _device + "\", " + strerror(errno));
    }

    if (!MlxRegLib::isDeviceSupported(_mf)) {
        throw MlxRegException("Device is not supported");
    }

    if (_ignoreCapCheck == false) {
        try {
            MlxRegLib::isAccessRegisterSupported(_mf);
        } catch (MlxRegException& exp) {
#if defined(EXTERNAL) || defined(MST_UL)
            throw exp;
#else
            throw MlxRegException("%s. \n   internal only: FW might be old, consider running " \
                    "with --%s (This flag is deprecated)", exp.what(), IGNORE_CAP_CHECK_FLAG);
#endif
        }
    }

    _mlxRegLib = new MlxRegLib(_mf, _extAdbFile, _isExternal);

    std::vector<AdbInstance*> regFields;
    std::vector<string>       regs;
    AdbInstance *regNode = NULL;
    std::vector<u_int32_t>    buff;

    switch (_op) {
    case CMD_SHOW_REG:
        _mlxRegLib->showRegister(_regName, regFields);
        printRegFields(regFields);
        break;

    case CMD_SHOW_REGS:
        _mlxRegLib->showRegisters(regs);
        printRegNames(regs);
        break;

    case CMD_SHOW_ALL_REGS:
        // TODO: remove CMD_SHOW_ALL_REGS from UI after 4.14.0 release, it's deprecated
        cout << endl << "-W- The option --" << OP_SHOW_ALL_REGS_FLAG
             << " is deprecated and will be removed, please use --"
             << OP_SHOW_REGS_FLAG << " instead." << endl << endl;
        _mlxRegLib->showRegisters(regs);
        printRegNames(regs);
        break;

    case CMD_GET:
        {
            if (_regName != "") {
                regNode = _mlxRegLib->findAdbNode(_regName);
            }
            RegAccessParser parser(_dataStr, _indexesStr, regNode, _dataLen);
            buff = parser.genBuff();
            printf("Sending access register...\n\n");
            if (_regName != "") { // Known mode
                _mlxRegLib->sendRegister(_regName, MACCESS_REG_METHOD_GET, buff);
                printAdbContext(regNode, buff);
            } else {          // Unknown mode
                _mlxRegLib->sendRegister(_regID, MACCESS_REG_METHOD_GET, buff);
                printBuff(buff);
            }
        }
        break;

    case CMD_SET:
        {
            if (_regName != "") {
                regNode = _mlxRegLib->findAdbNode(_regName);
            }
            // Read current register data into buffer
            RegAccessParser parserGet(_dataStr, _indexesStr, regNode, _dataLen);
            buff = parserGet.genBuff();
            if (_regName != "") { // Known mode
                _mlxRegLib->sendRegister(_regName, MACCESS_REG_METHOD_GET, buff);
            } else {          // Unknown mode
                _mlxRegLib->sendRegister(_regID, MACCESS_REG_METHOD_GET, buff);
            }
            // Update the register buffer with user inputs
            RegAccessParser parser(_dataStr, _indexesStr, regNode, buff);
            buff = parser.genBuff();
            if (_regName != "") { // Known mode
                printf("You are about to send access register: %s with the following data:\n", _regName.c_str());
                printAdbContext(regNode, buff);
                if (askUser("Do you want to continue")) {
                    printf(" Sending access register...\n");
                    _mlxRegLib->sendRegister(_regName, MACCESS_REG_METHOD_SET, buff);
                }
            } else {          // Unknown mode
                printf("You are about to send access register id: 0x%x with the following data:\n", _regID);
                printBuff(buff);
                if (askUser("Do you want to continue")) {
                    printf(" Sending access register...\n");
                    _mlxRegLib->sendRegister(_regID, MACCESS_REG_METHOD_SET, buff);
                }
            }
        }
        break;

    default:
        break;
    }
}

/************************************
* Function: main
************************************/
int main(int argc, char **argv)
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

