/*
 *
 * subcommands.cpp - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <sys/stat.h>
#include <map>
#include <bitset>

#include "mtcr.h"
#include "mlxfwops/lib/components/fs_cert_ops.h"
#include <common/compatibility.h>
#include <fw_comps_mgr/fw_comps_mgr.h>
#include <mlxfwops/lib/fw_version.h>
#include "mlxfwops/lib/components/fs_synce_ops.h"
#include "mlxfwops/lib/components/fs_dpa_app_ops.h"
#include "hex64.h"
#include "dev_mgt/tools_dev_types.h"
#include "common/tools_time.h"

#ifndef NO_ZLIB
#include <zlib.h>
#endif
#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif
#include "hex64.h"
#define MAX_IMG_TYPE_LEN 20
#define MODULUS_SIZE 512
#define TOTAL_PUBLIC_KEY_SIZE 532
#define MODULUS_OFFSET 38
#define BP_SIZE 4

#if !defined(__WIN__) && !defined(__DJGPP__) && !defined(UEFI_BUILD) && defined(HAVE_TERMIOS_H)
// used in mygetchar
#include <termios.h>
#endif

#ifdef __WIN__
#include <ctype.h>
#include <win_driver_cif.h>
#include <parser.h>
#endif // WIN

#include "subcommands.h"
#include "tools_layouts/cx4fw_layouts.h"
#include "tools_layouts/image_layout_layouts.h"


#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
#include "cable_access/cdb_cable_commander.h"
#endif

using namespace std;
#ifndef NO_MSTARCHIVE
using namespace mfa2;
#endif
/***********************************
 *  Log file writing implementation
 ************************************/

// global log file header
FILE* flint_log_fh = NULL;

#define BURN_INTERRUPTED 0x1234
#define CABLE_BURN_TIMEOUT_MAX 10
#define CABLE_BURN_RESET_MAX 3 
#define CABLE_BURN_INIT_MAX 120

static int is_arm()
{
#if defined(MST_CPU_arm64)
    return 1;
#else
    return 0;
#endif
}

void close_log()
{
    if (flint_log_fh != NULL)
    {
        fclose(flint_log_fh);
        flint_log_fh = NULL;
    }
    return;
}

static const map<LifeCycleFS4, const char*> life_cycle_fs4_strings = {{FS4_LC_PRODUCTION, "PRODUCTION"},
                                                                      {FS4_LC_GA_SECURED, "GA SECURED"},
                                                                      {FS4_LC_GA_NON_SECURED, "GA NON SECURED"},
                                                                      {FS4_LC_RMA, "RMA"}};
// To keep BWC we translate new life cycle definitions (FS5) to legacy (FS4):
// 'BLANK CHIP' -> 'PRODUCTION'
// 'PRODUCTION' -> 'GA SECURED'
// 'FAILURE ANALYSIS' -> 'RMA'
static const map<LifeCycleFS5, const char*> life_cycle_fs5_strings = {{FS5_LC_BLANK_CHIP, "PRODUCTION"},
                                                                      {FS5_LC_PRE_PRODUCTION, "PRE PRODUCTION"},
                                                                      {FS5_LC_PRODUCTION, "GA SECURED"},
                                                                      {FS5_LC_FAILURE_ANALYSIS, "RMA"}};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char* month_2monstr(int month)
{
    static const char* month_2monstr_arr[] = {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
    };
    int arr_size = (int)ARRAY_SIZE(month_2monstr_arr);
    return month < arr_size ? month_2monstr_arr[month] : "???";
}

void print_time_to_log()
{
    time_t rawtime;
    struct tm* timeinfo;

    if (flint_log_fh == NULL)
    {
        return;
    }
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (!timeinfo)
    {
        printf("localtime returned NULL. Can't print time.\n");
        return;
    }

    fprintf(flint_log_fh, "%-3s %2d %02d:%02d:%02d ", month_2monstr(timeinfo->tm_mon), timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return;
}

int print_line_to_log(const char* format, ...)
{
    va_list args;
    if (flint_log_fh == NULL)
    {
        return 0;
    }
    print_time_to_log();
    va_start(args, format);
    vfprintf(flint_log_fh, format, args);
    va_end(args);
    return 0;
}

int write_cmd_to_log(string fullCmd, sub_cmd_t cmd, bool write)
{
    if (!write)
    {
        return 0;
    }
    char pre_str[50];
    if (flint_log_fh == NULL)
    {
        return 0;
    }
    if (cmd == SC_Brom)
    {
        snprintf(pre_str, 50, "ROM");
    }
    else
    {
        snprintf(pre_str, 50, "FW");
    }
    print_time_to_log();
    fprintf(flint_log_fh, "Start %s burning: ", pre_str);
    fprintf(flint_log_fh, "%s ", fullCmd.c_str());
    fprintf(flint_log_fh, "\n");
    return 0;
}

int write_result_to_log(int is_failed, const char* err_msg, bool write)
{
    if (!write)
    {
        return 0;
    }
    char msg[MAX_ERR_STR_LEN + 1] = {0};
    strncpy(msg, err_msg, MAX_ERR_STR_LEN);
    if (is_failed == 0)
    {
        print_line_to_log("Burn completed successfully\n");
    }
    else if (is_failed == BURN_INTERRUPTED)
    {
        print_line_to_log("Burn interrupted by user\n");
    }
    else
    {
        int msg_len = strlen(msg);
        // cleanup the msg
        for (int i = 0; i < msg_len; i++)
        {
            if (msg[i] == '\n')
            {
                if (i == msg_len - 1)
                {
                    msg[i] = '\0';
                }
                else
                {
                    msg[i] = ' ';
                }
            }
        }
        print_line_to_log("Burn failed: %s\n", msg);
    }
    return 0;
}

bool is_file_exists(const string filename)
{
    /* Check for existence */
#ifdef __WIN__
    if (_access(filename.c_str(), F_OK) != -1)
    {
        return true;
    }
#else
    if (access(filename.c_str(), F_OK) != -1)
    {
        return true;
    }
#endif
    return false;
}

bool is_file_exists(const char* filename)
{
    /* Check for existence */
#ifdef __WIN__
    if (_access(filename, F_OK) != -1)
    {
        return true;
    }
#else
    if (access(filename, F_OK) != -1)
    {
        return true;
    }
#endif
    return false;
}

/*******************
 *  Static functions
 ******************/

static bool str2Num(const char* str, u_int32_t& num)
{
    char* endp;
    u_int32_t tempNum;

    if (!str)
    {
        return false;
    }
    tempNum = strtoul(str, &endp, 0);
    if (*endp)
    {
        return false;
    }
    num = tempNum;
    return true;
}

/*******************
 * Class: Subcommand
 ******************/

#define MAX_ERR_STR_LEN 1024
#define PRE_ERR_MSG "-E-"

bool SubCommand::isCmdSupportLog()
{
    // a subcommand supports Logging if: A & B where:
    // A. it is either Burn, Burn Block or Burn ROM.
    // B. log flag was given in the cmd line.

    switch (_cmdType)
    {
        case SC_Burn:
        case SC_Bb:
        case SC_Brom:
            return _flintParams.log_specified;

        default:
            return false;
    }
    return false;
}

void SubCommand::reportErr(bool shouldPrint, const char* format, ...)
{
    va_list args;

    va_start(args, format);

    if (vsnprintf(_errBuff, FLINT_ERR_LEN, format, args) >= FLINT_ERR_LEN)
    {
        strcpy(&_errBuff[FLINT_ERR_LEN - 5], "...\n");
    }
    // print to the user and to the log if needed
    if (shouldPrint)
    {
        fprintf(stdout, PRE_ERR_MSG " %s", _errBuff);
    }
    write_result_to_log(FLINT_FAILED, _errBuff, isCmdSupportLog());
    va_end(args);

    return;
}

bool SubCommand::getFileSize(const string& filePath, long& fileSize)
{
    FILE* fd = fopen(filePath.c_str(), "rb");
    if (fd == NULL)
    {
        reportErr(true, FLINT_OPEN_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    if (fseek(fd, 0, SEEK_END) < 0)
    {
        fclose(fd);
        reportErr(true, FLINT_FILE_SIZE_ERROR, filePath.c_str());
        return false;
    }
    long FileSize = ftell(fd);
    if (FileSize < 0)
    {
        fclose(fd);
        reportErr(true, FLINT_FILE_SIZE_ERROR, filePath.c_str());
        return false;
    }
    fileSize = FileSize;
    fclose(fd);
    return true;
}

bool SubCommand::readFromFile(const string& filePath, std::vector<u_int8_t>& buff)
{
    FILE* fd = fopen(filePath.c_str(), "rb");
    if (fd == NULL)
    {
        reportErr(true, FLINT_OPEN_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    if (fseek(fd, 0, SEEK_END) < 0)
    {
        fclose(fd);
        reportErr(true, FLINT_FILE_SIZE_ERROR, filePath.c_str());
        return false;
    }
    long fileSize = ftell(fd);
    if (fileSize < 0)
    {
        fclose(fd);
        reportErr(true, FLINT_FILE_SIZE_ERROR, filePath.c_str());
        return false;
    }
    rewind(fd);
    int currentSize = buff.size(); // default 0
    buff.resize(currentSize + fileSize, 0xff);
    // Read
    long read_res = (long)fread(&buff[currentSize], 1, fileSize, fd);
    if (read_res < 0)
    {
        fclose(fd);
        reportErr(true, FLINT_READ_FILE_ERROR, filePath.c_str());
        return false;
    }
    fclose(fd);
    return true;
}
bool SubCommand::writeToFile(string filePath, const std::vector<u_int8_t>& buff)
{
    FILE* fh = fopen(filePath.c_str(), "wb");
    if (fh == NULL)
    {
        reportErr(true, FLINT_OPEN_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    // Write
    if (fwrite(&buff[0], 1, buff.size(), fh) != buff.size())
    {
        fclose(fh);
        reportErr(true, FLINT_WRITE_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    fclose(fh);
    return true;
}

FlintStatus SubCommand::writeImageToFile(const char* file_name, u_int8_t* data, u_int32_t length)
{
    FILE* fh = fopen(file_name, "wb");
    if (fh == NULL)
    {
        reportErr(true, FLINT_OPEN_FILE_ERROR, file_name, strerror(errno));
        return FLINT_FAILED;
    }

    // Write output
    if (fwrite(data, 1, length, fh) != length)
    {
        fclose(fh);
        reportErr(true, FLINT_WRITE_FILE_ERROR, file_name, strerror(errno));
        return FLINT_FAILED;
    }
    fclose(fh);
    return FLINT_SUCCESS;
}

void SubCommand::openLog()
{
    if (isCmdSupportLog())
    {
        flint_log_fh = fopen(_flintParams.log.c_str(), "a+");
        if (flint_log_fh == NULL)
        {
            printf(FLINT_OPEN_LOG_FILE_WARNING, _flintParams.log.c_str(), strerror(errno));
        }
        write_cmd_to_log(_flintParams.fullCmd, _flintParams.cmd, _flintParams.log_specified);
    }
}

int SubCommand::verifyCbFunc(char* str)
{
    printf("%s", str);
    return 0;
}

int SubCommand::CbCommon(int completion, char* preStr, char* endStr)
{
    if (completion < 100)
    {
        printf("\r%s%3d%%", preStr, completion);
    }
    else if (completion == 100)
    {
        printf("\r%sOK  \n", preStr);
    }
    else
    { // printing endStr
        if (endStr)
        {
            printf("\r%s\n", endStr);
        }
    }
    fflush(stdout);
    return 0;
}

// HACK: the endStr is printed when we reach 101% this is for backward compat with the original flint
// output. thus in subcommands that use these callbacks you will see we manually call them at the end with the 101 arg
int SubCommand::burnCbFs3Func(int completion)
{
    char* message = (char*)"Burning FW image without signatures - ";
    char* endStr = (char*)"Restoring signature                     - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::advProgressFunc(int completion, const char* stage, prog_t type, int* unknownProgress)
{
    switch (type)
    {
        case PROG_WITH_PRECENTAGE:
            printf("\r%s - %3d%%", stage, completion);
            break;

        case PROG_OK:
            printf("\r%s -   OK\n", stage);
            break;

        case PROG_STRING_ONLY:
            printf("%s\n", stage);
            break;

        case PROG_WITHOUT_PRECENTAGE:
            if (unknownProgress)
            {
                static const char* progStr[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                                "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
                int size = sizeof(progStr) / sizeof(progStr[0]);
                printf("\r%s - %s", stage, progStr[(*unknownProgress) % size]);
                (*unknownProgress)++;
            }
            break;
    }
    fflush(stdout);
    return 0;
}

int SubCommand::burnCbFs2Func(int completion)
{
    char* message = (char*)"Burning FS2 FW image without signatures - ";
    char* endStr = (char*)"Restoring signature                     - OK";
    if (completion == 102)
    {
        endStr = (char*)"Image was successfully cached by driver.";
    }
    return CbCommon(completion, message, endStr);
}

int SubCommand::bromCbFunc(int completion)
{
    char* message = (char*)"Burning ROM image    - ";
    char* endStr = (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::dromCbFunc(int completion)
{
    char* message = (char*)"Removing ROM image    - ";
    char* endStr = (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::resetCfgCbFunc(int completion)
{
    char* message = (char*)"Resetting NV configuration - ";
    char* endStr = (char*)"Restoring signature        - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::burnBCbFunc(int completion)
{
    return CbCommon(completion, (char*)"");
}

int SubCommand::vsdCbFunc(int completion)
{
    char* message = (char*)"Setting the VSD      - ";
    char* endStr = (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::setKeyCbFunc(int completion)
{
    char* message = (char*)"Setting the HW Key   - ";
    char* endStr = (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::wbCbFunc(int completion)
{
    char* message = (char*)"Writing Block:   - ";
    return CbCommon(completion, message, NULL);
}

#define ERR_BUFF_SIZE 1024

void SubCommand::initDeviceFwParams(char* errBuff, FwOperations::fw_ops_params_t& fwParams)
{
    memset(&fwParams, 0, sizeof(FwOperations::fw_ops_params_t));
    fwParams.errBuff = errBuff;
    fwParams.errBuffSize = ERR_BUFF_SIZE;
    fwParams.flashParams = _flintParams.flash_params_specified ? &_flintParams.flash_params : NULL;
    fwParams.forceLock = _flintParams.clear_semaphore;
    fwParams.hndlType = FHT_MST_DEV;
    fwParams.ignoreCacheRep = _flintParams.override_cache_replacement ? 1 : 0;
    fwParams.mstHndl = strcpy(new char[_flintParams.device.length() + 1], _flintParams.device.c_str());
    fwParams.numOfBanks = _flintParams.banks;
    fwParams.readOnly = false;
    fwParams.noFlashVerify = _flintParams.no_flash_verify;
    fwParams.cx3FwAccess = _flintParams.use_fw;
    fwParams.noFwCtrl = _flintParams.no_fw_ctrl;
    fwParams.mccUnsupported = !_mccSupported;
    fwParams.ignoreCrcCheck = _flintParams.ignore_crc_check;
}

FlintStatus SubCommand::openOps(bool ignoreSecurityAttributes, bool ignoreDToc)
{
    DPRINTF(("SubCommand::openOps\n"));
    char errBuff[ERR_BUFF_SIZE] = {0};
    if (_flintParams.device_specified)
    {
        // fillup the fw_ops_params_t struct
        FwOperations::fw_ops_params_t fwParams;
        initDeviceFwParams(errBuff, fwParams);
        if (_flintParams.image_specified)
        {
            FwOperations::fw_ops_params_t imgFwParams;
            memset(&imgFwParams, 0, sizeof(imgFwParams));
            imgFwParams.psid = NULL;
            imgFwParams.hndlType = FHT_FW_FILE;
            imgFwParams.errBuff = errBuff;
            imgFwParams.errBuffSize = 1024;
            imgFwParams.shortErrors = true;
            imgFwParams.fileHndl = (char*)_flintParams.image.c_str();
            imgFwParams.ignoreCrcCheck = _flintParams.ignore_crc_check;
            if (!FwOperations::imageDevOperationsCreate(fwParams, imgFwParams, &_fwOps, &_imgOps,
                                                        ignoreSecurityAttributes, ignoreDToc))
            {
                /*
                 * Error are being handled after
                 */
            }
        }
        else
        {
            _fwOps = FwOperations::FwOperationsCreate(fwParams);
        }
        delete[] fwParams.mstHndl;
    }
    if (_flintParams.image_specified && !_flintParams.device_specified)
    {
        _imgOps =
          FwOperations::FwOperationsCreate((void*)_flintParams.image.c_str(), NULL, NULL, FHT_FW_FILE, errBuff, 1024);
    }

    if (_flintParams.image_specified && _imgOps == NULL)
    {
        reportErr(true, FLINT_OPEN_FWOPS_IMAGE_ERROR, _flintParams.image.c_str(), strlen(errBuff) != 0 ? errBuff : "");
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified && _fwOps == NULL)
    {
        if (_flintParams.silent == false)
        {
            reportErr(true, FLINT_OPEN_FWOPS_DEVICE_ERROR, _flintParams.device.c_str(),
                      strlen(errBuff) != 0 ? errBuff : "");
        }
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

FlintStatus SubCommand::openIo()
{
    // TODO: consider adding a parameter for when image/device will be opened as "readOnly" in the open routine.
    if (_flintParams.device_specified && _flintParams.image_specified)
    {
        // should not arrive here as we verify params at each subcommand.
        reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified)
    {
        _io = new Flash;
        if (!((Flash*)_io)
               ->open(_flintParams.device.c_str(), _flintParams.clear_semaphore, false, _flintParams.banks,
                      _flintParams.flash_params_specified ? &_flintParams.flash_params : NULL,
                      _flintParams.override_cache_replacement, true, _flintParams.use_fw))
        {
            // if we have Hw_Access command we dont fail straght away
            u_int8_t lockedCrSpace = ((Flash*)_io)->get_cr_space_locked();
            if (lockedCrSpace &&
                (_flintParams.cmd == SC_Hw_Access || (_flintParams.cmd == SC_Set_Key && ((Flash*)_io)->is_fifth_gen())))
            {
                return FLINT_SUCCESS;
            }
            reportErr(true, FLINT_IO_OPEN_ERROR, "Device", (_io)->err());
            delete _io;
            _io = NULL;
            return FLINT_FAILED;
        }
        // we have successfully opened a Flash Obj
        // set no flash verify if needed (default =false)
        ((Flash*)_io)->set_no_flash_verify(_flintParams.no_flash_verify);
    }
    else if (_flintParams.image_specified)
    {
        _io = new FImage;
        if (!((FImage*)_io)->open(_flintParams.image.c_str()))
        {
            reportErr(true, FLINT_IO_OPEN_ERROR, "Image", (_io)->err());
            delete _io;
            _io = NULL;
            return FLINT_FAILED;
        }
    }
    return FLINT_SUCCESS;
}

bool SubCommand::basicVerifyParams()
{
    if (!_flintParams.log_specified)
    {
        char* logFile;
        logFile = getenv(FLINT_LOG_ENV);
        if (logFile)
        {
            _flintParams.log = logFile;
            _flintParams.log_specified = true;
        }
    }
    // open log if needed
    openLog();

    if (_maxCmdParamNum == _minCmdParamNum && _maxCmdParamNum != -1 &&
        (int)_flintParams.cmd_params.size() != _maxCmdParamNum)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), _maxCmdParamNum, _flintParams.cmd_params.size());
        return false;
    }
    else if (_maxCmdParamNum != -1 && (int)_flintParams.cmd_params.size() > _maxCmdParamNum)
    {
        // _maxCmdParamNum == -1 means ignore this check
        if (_maxCmdParamNum)
        {
            reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), _maxCmdParamNum, (int)_flintParams.cmd_params.size());
        }
        else
        {
            reportErr(true, FLINT_CMD_ARGS_ERROR5, _name.c_str());
        }
        return false;
    }
    else if (_minCmdParamNum != -1 && (int)_flintParams.cmd_params.size() < _minCmdParamNum)
    {
        // _minCmdParamNum == -1 means ignore this check
        reportErr(true, FLINT_CMD_ARGS_ERROR3, _name.c_str(), _minCmdParamNum, _flintParams.cmd_params.size());
        return false;
    }

    switch (_v)
    {
        case Wtv_Img:
            if (_flintParams.device_specified == true)
            {
                _flintParams.image_specified ? reportErr(true, FLINT_COMMAND_IMAGE_ERROR2, _name.c_str()) :
                                               reportErr(true, FLINT_COMMAND_IMAGE_ERROR, _name.c_str());
                return false;
            }
            if (_flintParams.image_specified == false)
            {
                reportErr(true, FLINT_NO_IMAGE_ERROR);
                return false;
            }
            break;

        case Wtv_Dev:
            if (_flintParams.image_specified == true)
            {
                _flintParams.device_specified ? reportErr(true, FLINT_COMMAND_DEVICE_ERROR2, _name.c_str()) :
                                                reportErr(true, FLINT_COMMAND_DEVICE_ERROR, _name.c_str());
                return false;
            }
            if (_flintParams.device_specified == false)
            {
                reportErr(true, FLINT_NO_DEVICE_ERROR);
                return false;
            }
            break;

        case Wtv_Dev_And_Img:
            if (_flintParams.linkx_control == false  && _flintParams.linkx_els_control == false)
            {
                if ((_flintParams.image_specified == false) || (_flintParams.device_specified == false))
                {
                    reportErr(true, FLINT_COMMAND_DEVICE_IMAGE_ERROR, _name.c_str());
                    return false;
                }
            }
            break;

        case Wtv_Dev_Or_Img:
            if (_flintParams.image_specified == true && _flintParams.device_specified == true)
            {
                reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
                return false;
            }
            if (_flintParams.device_specified == false && _flintParams.image_specified == false)
            {
                reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
                return false;
            }
            break;

        case Wtv_Uninitilized:

            return true;
        default:
            reportErr(true, FAILED_TO_VERIFY_PARAMS);
            return false;
    }

    if (_flintParams.device_specified && _flintParams.striped_image)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-device", "-striped_image");
        return false;
    }

    if (_flintParams.override_cache_replacement)
    {
        printf(FLINT_OCR_WARRNING);
    }
    return true;
}

FlintStatus SubCommand::preFwOps(bool ignoreSecurityAttributes, bool ignoreDToc)
{
    DPRINTF(("SubCommand::preFwOps\n"));
    if (!basicVerifyParams())
    {
        return FLINT_FAILED;
    }
    if (_flintParams.linkx_control != true && _flintParams.linkx_els_control != true)
    {
        if (!verifyParams())
        {
            return FLINT_FAILED;
        }
    }
    if (_flintParams.mfa2_specified || _flintParams.congestion_control || _flintParams.linkx_control == true ||
        _flintParams.linkx_els_control == true)
    {
        bool saved_value = _flintParams.image_specified;
        _flintParams.image_specified = false;
        FlintStatus result = openOps(true);
        _flintParams.image_specified = saved_value;
        return result;
    }
    else
    {
        return openOps(ignoreSecurityAttributes, ignoreDToc);
    }
}

FlintStatus SubCommand::preFwAccess()
{
    if (!basicVerifyParams())
    {
        return FLINT_FAILED;
    }
    if (!verifyParams())
    {
        return FLINT_FAILED;
    }
    return openIo();
}

SubCommand::~SubCommand()
{
    if (_fwOps != NULL)
    {
        _fwOps->FwCleanUp();
        delete _fwOps;
    }
    if (_imgOps != NULL)
    {
        _imgOps->FwCleanUp();
        delete _imgOps;
    }
    if (_io != NULL)
    {
        _io->close();
        delete _io;
    }
}

// matanel - TODO: duplicated, use same function from fw_ops.cpp
bool SubCommand::getRomsInfo(FBase* io, roms_info_t& romsInfo)
{
    std::vector<u_int8_t> romSector;
    romSector.clear();
    romSector.resize(io->get_effective_size());
    if (!io->read(0, &romSector[0], io->get_effective_size()))
    {
        reportErr(true, FLINT_READ_ERROR, _flintParams.image.c_str(), io->err());
        return false;
    }
    FwOperations::RomInfo info(romSector, false);
    info.ParseInfo();
    info.initRomsInfo(&romsInfo);
    return true;
}

bool SubCommand::getGUIDFromStr(string str, guid_t& guid, string prefixErr)
{
    char* endp;
    u_int64_t g;
    g = strtoull(str.c_str(), &endp, 16);
    if (*endp || (g == 0xffffffffffffffffULL && errno == ERANGE))
    {
        if (prefixErr.size() == 0)
        {
            reportErr(true, INVALID_GUID_SYNTAX, str.c_str(), errno ? strerror(errno) : "");
        }
        else
        {
            reportErr(true, "%s\n", prefixErr.c_str());
        }
        return false;
    }
    guid.h = (u_int32_t)(g >> 32);
    guid.l = (u_int32_t)(g & 0xffffffff);
    return true;
}

#if !defined(__WIN__) && !defined(__DJGPP__) && !defined(UEFI_BUILD) && defined(HAVE_TERMIOS_H)
static int mygetch(void)
{
    struct termios oldt;
    struct termios newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

bool SubCommand::getPasswordFromUser(const char* preStr, char buffer[MAX_PASSWORD_LEN + 1])
{
    char c;
    int pos = 0;

    printf("%s: ", preStr);
    do
    {
        c = mygetch();

        if (((pos < MAX_PASSWORD_LEN)) && isprint(c))
        {
            buffer[pos++] = c;
            printf("%c", '*');
        }
        else if ((c == 8 || c == 127) && pos)
        {
            buffer[pos--] = '\0';
            printf("%s", "\b \b");
        }

    } while (c != '\n');
    printf("\n");
    buffer[pos] = '\0';
    return true;
}

#else
bool SubCommand::getPasswordFromUser(const char* preStr, char buffer[MAX_PASSWORD_LEN + 1])
{
    static HANDLE stdinHndl = NULL;
    DWORD numOfBytesRead = 0;
    DWORD oldConsoleMode, consoleMode;
    BOOL status = FALSE;
    char ch;
    int i;

    if (!stdinHndl)
    {
        // adrianc: this might be problematic if called and stdout was alreading overridden use CIN$ instead
        stdinHndl = GetStdHandle(STD_INPUT_HANDLE);
    }
    printf("%s:", preStr);

    // disable console echoing
    if (!GetConsoleMode(stdinHndl, &oldConsoleMode))
    {
        reportErr(true, FAILED_GET_CONSOLE_MODE);
        return false;
    }

    consoleMode = oldConsoleMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    if (!SetConsoleMode(stdinHndl, consoleMode))
    {
        reportErr(true, FAILED_GET_CONSOLE_MODE);
        return 1;
    }
    // read chars from stdin and print * to stdout using putchar
    for (i = 0;;)
    {
        status = ReadFile(stdinHndl, &ch, sizeof(char), &numOfBytesRead, NULL);
        if (!status || numOfBytesRead != sizeof(char) || ch == '\n' || ch == '\r' || i == (MAX_PASSWORD_LEN - 1))
        {
            // user finished giving the pw
            if (!SetConsoleMode(stdinHndl, oldConsoleMode))
            {
                reportErr(true, FAILED_GET_CONSOLE_MODE);
                return false;
            }
            if (!status || numOfBytesRead != sizeof(char))
            {
                reportErr(true, FAILED_GET_CONSOLE_MODE);
                return false;
            }
            break;
        }
        if (isalpha(ch) || isdigit(ch))
        {
            putchar('*');
            buffer[i++] = ch;
        }
        else if (ch == '\b' && i)
        {
            // delete last astrix and set correct position
            printf("\b \b");
            i--;
        }
    }
    buffer[i] = '\0';
    putchar('\n');
    return true;
}

#endif

//
// Asks user a yes/no question.
// Returns true if user chose Y, false if user chose N.
//

bool SubCommand::askUser(const char* question, bool printAbrtMsg)
{
    if (question == NULL)
    {
        printf("\n Do you want to continue ? (y/n) [n] : ");
    }
    else
    {
        printf("\n %s ? (y/n) [n] : ", question);
    }

    if (_flintParams.yes)
    {
        printf("y\n");
    }
    else
    {
        if (_flintParams.no)
        {
            printf("n\n");
            reportErr(false, "-no flag is set\n");
            return false;
        }

        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);
        // fgets(ansbuff, 30, stdin);
        // if (!fscanf(stdin, "%[^\n]30s", ansbuff)) {
        //	return false;
        //}

        if (strcasecmp(answer.c_str(), "y") && strcasecmp(answer.c_str(), "yes"))
        {
            if (printAbrtMsg)
            {
                reportErr(true, USER_ABORT);
            }
            return false;
        }
    }
    return true;
}

string SubCommand::getRomProtocolStr(u_int8_t proto)
{
    string result;

    switch (proto)
    {
        case ER_IB:
            result = "IB";
            break;

        case ER_ETH:
            result = "ETH";
            break;

        case ER_VPI:
            result = "VPI";
            break;

        default:
            result = "N/A";
    }
    return result;
}

string SubCommand::getRomSuppCpuStr(u_int8_t suppCpu)
{
    string result;

    switch (suppCpu)
    {
        case ERC_AMD64:
            result = "AMD64";
            break;

        case ERC_AARCH64:
            result = "AARCH64";
            break;

        case ERC_AMD64_AARCH64:
            result = "AMD64,AARCH64";
            break;

        case ERC_IA32:
            result = "IA32";
            break;

        default:
            result = "N/A";
    }
    return result;
}

string SubCommand::getExpRomVerStr(const rom_info_t& info)
{
    stringstream verStream;
    if (info.exp_rom_num_ver_fields)
    {
        for (int i = 0; i < info.exp_rom_num_ver_fields; i++)
        {
            verStream << info.exp_rom_ver[i];
            if (i + 1 < info.exp_rom_num_ver_fields)
            {
                verStream << ".";
            }
        }
    }
    return verStream.str();
}

void SubCommand::displayOneExpRomInfo(const rom_info_t& info)
{
    const char* typeStr = FwOperations::expRomType2Str(info.exp_rom_product_id);
    if (info.exp_rom_product_id == 0xf)
    {
        // version id in this case is the freeStr that was moved to exp_rom_ver[0] in mlxfwops
        printf("version_id=%s type=%s ", getExpRomVerStr(info).c_str(), typeStr);
    }
    else
    {
        if (typeStr)
        {
            printf("type=%s ", typeStr);
        }
        else
        {
            printf("0x%x - Unknown ROM product ID\n", info.exp_rom_product_id);
            return;
        }
        printf("version=%s", getExpRomVerStr(info).c_str());
        if (info.exp_rom_product_id >= 0x10)
        {
            if (info.exp_rom_port)
            {
                // Do not display if 0 - port independent
                printf(" port=%d", info.exp_rom_port);
            }
            if (info.exp_rom_product_id != 0x12 && info.exp_rom_proto != 0xff)
            {
                // on CLP(0x12) there is no meaning to protocol
                printf(" proto=%s", getRomProtocolStr(info.exp_rom_proto).c_str());
            }
            if (info.exp_rom_supp_cpu_arch)
            {
                printf(" cpu=%s", getRomSuppCpuStr(info.exp_rom_supp_cpu_arch).c_str());
            }
        }
    }
    return;
}

void SubCommand::displayExpRomInfo(const roms_info_t& romsInfo, const char* preStr)
{
    int i;
    int strLen = strlen(preStr);

    if (romsInfo.num_of_exp_rom > 0)
    {
        for (i = 0; i < romsInfo.num_of_exp_rom; i++)
        {
            // Print the pre string or spaces
            if (i == 0)
            {
                printf("%s", preStr);
            }
            else
            {
                int j;
                for (j = 0; j < strLen; j++)
                {
                    printf("%s", " ");
                }
            }
            // Display a ROM info
            displayOneExpRomInfo(romsInfo.rom_info[i]);
            if (i != romsInfo.num_of_exp_rom - 1)
            {
                // Don't print new line after the info of the last ROM
                printf("\n");
            }
        }
        if (romsInfo.exp_rom_warning)
        {
            printf(" (-W- %s)", romsInfo.exp_rom_warning_msg);
        }
        printf("\n");
    }
    else
    {
        printf("%s", preStr);
        printf("N/A");
        if (romsInfo.exp_rom_err_msg_valid)
        {
            printf(" (-E- %s)", romsInfo.exp_rom_err_msg);
        }
        printf("\n");
    }
    return;
}

bool SubCommand::printGuidLine(guid_t* new_guids, guid_t* old_guids, int guid_index)
{
    printf(GUID_FORMAT GUID_SPACES, new_guids[guid_index].h, new_guids[guid_index].l);
    if (old_guids != NULL)
    {
        printf(GUID_FORMAT, old_guids[guid_index].h, old_guids[guid_index].l);
    }
    else
    {
        printf("      N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printMacLine(guid_t* new_guids, guid_t* old_guids, int mac_index)
{
    printf("    " MAC_FORMAT MAC_SPACES, new_guids[mac_index].h, new_guids[mac_index].l);
    if (old_guids != NULL)
    {
        printf(MAC_FORMAT, old_guids[mac_index].h, old_guids[mac_index].l);
    }
    else
    {
        printf("  N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printGUIDsFunc(guid_t guids[GUIDS],
                                guid_t macs[MACS],
                                guid_t old_guids[GUIDS],
                                guid_t old_macs[MACS],
                                bool print_guids,
                                bool print_macs,
                                int portNum,
                                bool old_guid_fmt)
{
    if (print_guids)
    {
        printf("        Node  GUID:     ");
        printGuidLine(guids, old_guids, 0);
        if (portNum > 0)
        {
            printf("        Port1 GUID:     ");
            printGuidLine(guids, old_guids, 1);
        }
        if (portNum > 1)
        {
            printf("        Port2 GUID:     ");
            printGuidLine(guids, old_guids, 2);
        }
        if (!old_guid_fmt)
        {
            printf("        Sys.Image GUID: ");
            printGuidLine(guids, old_guids, 3);
        }
    }

    if (print_macs)
    {
        printf("        Port1 MAC:      ");
        printMacLine(macs, old_macs, 0);
        printf("        Port2 MAC:      ");
        printMacLine(macs, old_macs, 1);
    }
    return true;
}

bool SubCommand::reportGuidChanges(guid_t* new_guids,
                                   guid_t* new_macs,
                                   guid_t* old_guids,
                                   guid_t* old_macs,
                                   bool printGuids,
                                   bool printMacs,
                                   int guidNum)
{
    // should be used ONLY on FS2 in current implementation
    printf("    You are about to change the Guids/Macs/Uids on the %s:\n\n",
           _flintParams.device_specified ? "device" : "image");
    printf("                        New Values      " GUID_SPACES "Current Values\n");
    printGUIDsFunc(new_guids, new_macs, old_guids, old_macs, printGuids, printMacs, guidNum, guidNum < GUIDS);

    if (!askUser())
    {
        return false;
    }

    return true;
}

// used for dc and dh subcommands

bool SubCommand::unzipDataFile(std::vector<u_int8_t> data, std::vector<u_int8_t>& newData, const char* sectionName)
{
#ifndef NO_ZLIB
    int rc;
    if (data.empty())
    {
        reportErr(true, SECTION_NOT_FOUNT, sectionName);
        return false;
    }
    // restore endianess.
    TOCPUn(&(data[0]), data.size() / 4);

    // uncompress:
    uLongf destLen = data.size();
    destLen *= 40; // Assuming this is the best compression ratio
    vector<u_int8_t> dest(destLen);

    for (int i = 0; i < 32; i++)
    {
        rc = uncompress((Bytef*)&(dest[0]), &destLen, (const Bytef*)&(data[0]), data.size());
        if (rc != Z_BUF_ERROR)
        {
            break;
        }
        destLen *= 2;
        dest.resize(destLen);
    }

    if (rc != Z_OK)
    {
        reportErr(true, UNCOMPRESSS_ERROR, rc);
        return false;
    }
    // printf("%s", (char*)&(dest[0]));

    newData = dest;
    newData[destLen] = 0; // Terminating NULL
    newData.resize(destLen + 1);
    return true;
#else
    // avoid warnings
    (void)data;
    (void)newData;
    (void)sectionName;
    reportErr(true, FLINT_NO_ZLIB_ERROR);
    return false;
#endif
}

bool SubCommand::dumpFile(const char* confFile, std::vector<u_int8_t>& data, const char* sectionName)
{
    FILE* out;
    vector<u_int8_t> dest;

    if (confFile == NULL)
    {
        out = stdout;
    }
    else
    {
        out = fopen(confFile, "w");

        if (out == NULL)
        {
            reportErr(true, OPEN_WRITE_FILE_ERROR, confFile, strerror(errno));
            return false;
        }
    }
    if (unzipDataFile(data, dest, sectionName) == false)
    {
        if (confFile != NULL)
        {
            fclose(out);
        }
        return false;
    }
    fprintf(out, "%s", (char*)&(dest[0]));

    if (confFile != NULL)
    {
        fclose(out);
    }
    return true;
}

bool SubCommand::checkGuidsFlags(u_int16_t devType,
                                 u_int8_t fwType,
                                 bool guidsSpecified,
                                 bool macsSpecified,
                                 bool uidSpecified,
                                 bool ibDev,
                                 bool ethDev)
{
    (void)ibDev;
    if (guidsSpecified || macsSpecified || uidSpecified)
    {
        if (uidSpecified && fwType != FIT_FS3 && fwType != FIT_FS4 && fwType != FIT_FS5 && fwType != FIT_FSCTRL)
        {
            reportErr(true, "-uid flag is applicable only for FS3/FS4/FS5 FW Only.\n");
            return false;
        }
        else if (fwType != FIT_FS2 && !ethDev && macsSpecified)
        {
            reportErr(true, "-mac(s) flag is not applicable for IB MT%d device.\n", devType);
            return false;
        }
    }
    return true;
}

void SubCommand::printMissingGuidErr(bool ibDev, bool ethDev)
{
    const char* missingInfo;
    const char* missingFlags;

    if (ibDev && ethDev)
    {
        missingInfo = "GUIDs / MACs";
        missingFlags = "-guid(s) / -mac(s)";
    }
    else if (ibDev)
    {
        missingInfo = "GUIDs";
        missingFlags = "-guid(s)";
    }
    else
    {
        missingInfo = "MACs";
        missingFlags = "-mac(s)";
    }

    printf("Please specify %s (using command line flags %s ).\n", missingInfo, missingFlags);
    return;
}

bool SubCommand::extractValuesFromString(string valStr, u_int8_t values[2], string origArg)
{
    u_int32_t tempValues[2] = {0, 0};

    if (!extractValuesFromStringAux(valStr, tempValues, origArg))
    {
        return false;
    }

    // perform checks
    if (tempValues[0] > 255 || tempValues[1] > 255)
    {
        reportErr(true, "Invalid argument values for %s, values can't be larger than 255.\n", origArg.c_str());
        return false;
    }
    values[0] = tempValues[0];
    values[1] = tempValues[1];
    return true;
}

bool SubCommand::extractValuesFromString(string valStr, u_int16_t values[2], string origArg)
{
    u_int32_t tempValues[2] = {0, 0};

    if (!extractValuesFromStringAux(valStr, tempValues, origArg))
    {
        return false;
    }

    // perform checks
    if (tempValues[0] > 1024 || tempValues[1] > 1024)
    {
        reportErr(true, "Invalid argument values for %s, values can't be larger than 1024.\n", origArg.c_str());
        return false;
    }
    values[0] = tempValues[0];
    values[1] = tempValues[1];
    return true;
}

bool SubCommand::extractValuesFromStringAux(string valStr, u_int32_t values[2], string origArg)
{
    string tempNumStr;
    // check if we need to extract 2 values or 1
    if (valStr.find(',') != string::npos)
    {
        std::stringstream ss((valStr.c_str()));
        // get first value
        if (!std::getline(ss, tempNumStr, ','))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        if (!str2Num(tempNumStr.c_str(), values[0]))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        // get second value
        if (!std::getline(ss, tempNumStr, ','))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        if (!str2Num(tempNumStr.c_str(), values[1]))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        // make sure no other tokens are present
        if (!(!std::getline(ss, tempNumStr, ',')))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
    }
    else
    {
        if (!str2Num(valStr.c_str(), values[0]))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        values[1] = values[0];
    }

    return true;
}

bool SubCommand::extractUIDArgs(std::vector<string>& cmdArgs, u_int16_t numOfGuids[2], u_int8_t stepSize[2])
{
    // extract num_of_guids and step_size from numGuidsStr, stepStr
    string tag, valStr;
    for (std::vector<string>::iterator it = cmdArgs.begin(); it != cmdArgs.end(); it++)
    {
        std::stringstream ss((it->c_str()));
        // get the tag
        if (!std::getline(ss, tag, '='))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        // get the val
        if (!std::getline(ss, valStr, '='))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        // make sure no other tokens are present
        if (!(!std::getline(ss, valStr, '=')))
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        if (tag == "guids_num")
        {
            if (!extractValuesFromString(valStr, numOfGuids, *it))
            {
                return false;
            }
        }
        else if (tag == "step_size")
        {
            if (!extractValuesFromString(valStr, stepSize, *it))
            {
                return false;
            }
        }
        else
        {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
    }
    return true;
}

const char* SubCommand::fwImgTypeToStr(u_int8_t fwImgType)
{
    switch (fwImgType)
    {
        case FIT_FS2:
            return "FS2";
            break;

        case FIT_FS3:
            return "FS3";
            break;

        case FIT_FS4:
            return "FS4";
            break;

        case FIT_FS5:
            return "FS5";
            break;

        case FIT_FSCTRL:
            return "FSCTRL";
            break;

        case FIT_COMPS:
            return "COMPS";
            break;
        
        case FIT_PLDM_1_0:
            return "PLDM_1_0";
            break;

        default:
            return "Unknown";
            break;
    }
}

/***************************
 * Extract4MBImageSubCommand
 ***********************/
Extract4MBImageSubCommand::Extract4MBImageSubCommand()
{
    _name = "extract_fw_data";
    _desc = "Extract firmware data for firmware controlled updates";
    _extendedDesc = "Extract 4MB firmware image file for firmware controlled updates. "
                    "The extracted data will have the image signature and the device ToCs "
                    "overwritten with 0xFF";
    _flagLong = "extract_fw_data";
    _param = "<out-file>";
    _paramExp = "file - filename to write the extracted data";
    _example = FLINT_NAME " -i fw_image.bin extract_fw_data outputfile.bin";
    _v = Wtv_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Extract_4MB_Image;
}

Extract4MBImageSubCommand::~Extract4MBImageSubCommand() {}

FlintStatus Extract4MBImageSubCommand::executeCommand()
{
    vector<u_int8_t> img;

    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    if (_imgOps->FwType() == FIT_FS2)
    {
        reportErr(true, "Extracting FW Data is applicable only for FS3/FS4 FW.\n");
        return FLINT_FAILED;
    }

    if (!_imgOps->FwExtract4MBImage(img, true, false, false, _flintParams.imageSizeOnly))
    {
        reportErr(true, "Extracting FW Data failed: %s.\n", _imgOps->err());
        return FLINT_FAILED;
    }

    if (!writeToFile(_flintParams.cmd_params[0], img))
    {
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}

/***********************
 * * Class: AddHmacSubCommand
 * ***********************/
AddHmacSubCommand::AddHmacSubCommand()
{
    _name = "sign_with_hmac";
    _desc = "Sign image with HMAC";
    _extendedDesc = "Sign image with HMAC";
    _flagLong = "sign_with_hmac";
    _flagShort = "";
    _paramExp = "None";
    _example = FLINT_NAME " -i fw_image.bin --hmac_key hmac_key_file sign_with_hmac";
    _v = Wtv_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Add_Hmac;
}

AddHmacSubCommand::~AddHmacSubCommand() {}

FlintStatus AddHmacSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_imgOps->FwType() != FIT_FS4)
    {
        reportErr(true, "Signing with HMAC is applicable only for FS4 FW.\n");
        return FLINT_FAILED;
    }

    if (!_imgOps->FwSignWithHmac(_flintParams.key.c_str()))
    {
        reportErr(true, FLINT_HMAC_ERROR, _imgOps->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

bool AddHmacSubCommand::verifyParams()
{
    if (!_flintParams.key_specified)
    {
        reportErr(true, "To sign with HMAC, you must provide a key \n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

/***********************
 * Class: SignSubCommand
 ***********************/
SignSubCommand::SignSubCommand()
{
    _name = "sign";
    _desc = "Sign firmware image file";
    _extendedDesc = "Sign firmware image file";
    _flagLong = "sign";
    _flagShort = "";
    _paramExp = "None";
    _example = FLINT_NAME " -i fw_image.bin [--private_key file.pem --key_uuid uuid_string] sign";
    _v = Wtv_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Sign;
}

SignSubCommand::~SignSubCommand() {}

FlintStatus SignSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_imgOps->FwType() != FIT_FS3 && _imgOps->FwType() != FIT_FS4)
    {
        reportErr(true, IMAGE_SIGN_TYPE_ERROR);
        return FLINT_FAILED;
    }
    else if (!_flintParams.privkey_file.empty() && !_flintParams.privkey_uuid.empty())
    {
        if (_flintParams.privkey2_specified && _flintParams.uuid2_specified)
        {
            if (!_imgOps->FwSignWithTwoRSAKeys(_flintParams.privkey_file.c_str(),
                                               _flintParams.privkey_uuid.c_str(),
                                               _flintParams.privkey2_file.c_str(),
                                               _flintParams.privkey2_uuid.c_str(),
                                               &verifyCbFunc))
            {
                reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
                return FLINT_FAILED;
            }
        }
        else
        {
#if !defined(NO_OPEN_SSL)
            //* Init Signer
            MlxSign::MlxSignRSAViaOpenssl signer(_flintParams.privkey_file.c_str());
            int rc = signer.Init();
            if (rc)
            {
                return FLINT_FAILED;
            }

            if (!_imgOps->SignForFwUpdate(_flintParams.privkey_uuid.c_str(), signer, signer.GetShaType(), &verifyCbFunc))
            {
                reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
                return FLINT_FAILED;
            }
#else
            reportErr(true, "Open SSL functionality is not supported.\n");
            return FLINT_FAILED;
#endif
        }
    }
    else
    {
        if (!_imgOps->FwInsertSHA256(&verifyCbFunc))
        {
            reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
            return FLINT_FAILED;
        }
    }
    return FLINT_SUCCESS;
}

bool SignSubCommand::verifyParams()
{
    if (_flintParams.privkey_file.empty() != _flintParams.privkey_uuid.empty())
    {
        reportErr(true, "To Sign the image with RSA you must provide "
                        "private key and uuid.\n");
        return false;
    }

    if (_flintParams.privkey_file.empty() && _flintParams.privkey2_specified)
    {
        reportErr(true, "Use --private_key if you want to sign with only one key.\n");
        return false;
    }

    if (_flintParams.privkey2_specified != _flintParams.uuid2_specified)
    {
        reportErr(true, "To Sign the image with two RSA keys you must provide "
                        "two private keys and two uuid.\n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }

    return true;
}

/***********************
 * Class: BinaryCompareSubCommand
 **********************/
BinaryCompareSubCommand::BinaryCompareSubCommand()
{
    _name = "Binary compare";
    _desc =
      "Binary compare between device firmware and given BIN file. If there is a silent mode, no progress is displayed.";
    _extendedDesc = _desc;
    _flagLong = "binary_compare";
    _flagShort = "bc";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -i image1.bin  <-silent>/<-s> (optional) bc \n";
    _v = Wtv_Dev_And_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 0;
    _cmdType = SC_Binary_Compare;
    _devQueryRes = 0;
    _mccSupported = false;
    memset(&_devInfo, 0, sizeof(_devInfo));
    memset(&_imgInfo, 0, sizeof(_imgInfo));
    _unknownProgress = 0;
}

BinaryCompareSubCommand::~BinaryCompareSubCommand()
{
#ifndef NO_MSTARCHIVE
    if (_mfa2Pkg != NULL)
    {
        delete _mfa2Pkg;
    }
#endif
}

bool BinaryCompareSubCommand::verifyParams()
{
    if (_flintParams.num_of_args == 2)
    {
        return true;
    }
    else if (_flintParams.num_of_args == 3 && _flintParams.silent == true)
    {
        return true;
    }
    else
    {
        fprintf(stdout,
                "The binary comparison command doesn't accept any flags, except device, image and silent mode.\n");
        return false;
    }
}

FlintStatus BinaryCompareSubCommand::compareMFA2()
{
#ifndef NO_MSTARCHIVE
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    mfile* mf = _fwOps->getMfileObj();
    int is_livefish_mode = dm_is_livefish_mode(mf);
    if (is_livefish_mode == 1)
    {
        _flintParams.override_cache_replacement = true;
    }
    if (!_fwOps->FwQuery(&_devInfo, true, false, true, false, (_flintParams.silent == false)))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), _fwOps->err());
        return FLINT_FAILED;
    }
    vector<u_int8_t> componentBuffer;
    map_string_to_component matchingComponentsMap =
      _mfa2Pkg->getMatchingComponents((char*)_devInfo.fw_info.psid, _devInfo.fw_info.fw_ver);
    u_int32_t matchingSize = matchingComponentsMap.size();
    if (matchingSize == 0)
    {
        printf("\33[2K\r"); // clear the current line
        reportErr(true, "CompareMFA2 : No matching component found for device.\n");
        return FLINT_FAILED;
    }
    std::vector<u_int8_t> imgBuffInFile;
    if (!_fwOps->FwExtract4MBImage(imgBuffInFile, true, (_flintParams.silent == false), true))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    for (u_int32_t choice = 0; choice < matchingSize; choice++)
    {
        if (_mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer) == false)
        {
            reportErr(true, "CompareMFA2 : Error occurred while extracting MFA2\n");
            return FLINT_FAILED;
        }
        unsigned int i = 0;
        for (; i < imgBuffInFile.size(); i++)
        {
            if (componentBuffer[i] != imgBuffInFile[i])
            {
                break;
            }
        }
        if (i == imgBuffInFile.size())
        {
            printf("\33[2K\r"); // clear the current line
            printf("Binary comparison success.\n");
            return FLINT_SUCCESS;
        }
    }
    printf("\33[2K\r"); // clear the current line
    reportErr(true, "Binary comparison failed.\n");
    return FLINT_FAILED;
#else
    reportErr(true, FLINT_NO_MFA2);
    return FLINT_FAILED;
#endif
}

bool BinaryCompareSubCommand::ReadFwOpsImageData(vector<u_int8_t>& deviceBuff, vector<u_int8_t>& imgBuff)
{
    u_int32_t imgSize = 0;
    // on first call we get the image size
    if (!_fwOps->FwReadData(NULL, &imgSize))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return false;
    }
    deviceBuff.resize(imgSize);
    // on second call we fill it
    if (!_fwOps->FwReadData((void*)(&deviceBuff[0]), &imgSize, _flintParams.silent == false))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return false;
    }

    if (!_imgOps->FwExtract4MBImage(imgBuff, false, (_flintParams.silent == false), false, true))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _imgOps->err());
        return false;
    }

    return true;
}

bool BinaryCompareSubCommand::CompareEncryptedFwOpsViaDirectAccess(bool& res)
{
    //* Compare image
    res = false;

    std::vector<u_int8_t> deviceBuff;
    std::vector<u_int8_t> imgBuff;
    if (!ReadFwOpsImageData(deviceBuff, imgBuff))
    {
        return false;
    }

    if (deviceBuff == imgBuff)
    {
        res = true;
    }
    return true;
}
bool BinaryCompareSubCommand::CompareEncryptedFwOpsViaMCC(bool& res)
{
    //* Compare hashes table
    res = false;

    std::vector<u_int8_t> deviceBuff;
    std::vector<u_int8_t> imgBuff;
   if (_imgOps->FwType() == FIT_FS5)
    {
        //* Compare Ncore
        if (!_fwOps->GetNcoreData(deviceBuff))
        {
            reportErr(true, _fwOps->err());
            return false;
        }
        if (!_imgOps->GetNcoreData(imgBuff))
        {
            reportErr(true, _imgOps->err());
            return false;
        }
    }
    else
    {
        //* Compare hashes table
        if (!_fwOps->GetHashesTableData(deviceBuff))
        {
            reportErr(true, _fwOps->err());
            return false;
        }
        if (!_imgOps->GetHashesTableData(imgBuff))
        {
            reportErr(true, _imgOps->err());
            return false;
        }
    }
    
    if (deviceBuff == imgBuff)
    {
        res = true;
    }
    return true;
}

bool BinaryCompareSubCommand::CompareEncryptedFwOps(bool& res)
{
    if (_fwOps->IsFsCtrlOperations())
    {
        return CompareEncryptedFwOpsViaMCC(res);
    }
    else
    {
        return CompareEncryptedFwOpsViaDirectAccess(res);
    }
}

bool BinaryCompareSubCommand::CompareFwOps(bool& res)
{
    //* Legacy binary compare flow for non encrypted images
    res = false;
    std::vector<u_int8_t> deviceBuff;
    std::vector<u_int8_t> imgBuff;
    if (!ReadFwOpsImageData(deviceBuff, imgBuff)) // This call initializes fwops objects with the image data before
                                                  // calling to PrepItocSectionsForCompare
    {
        return false;
    }

    vector<u_int8_t> device_critical;
    vector<u_int8_t> device_non_critical;
    vector<u_int8_t> image_critical;
    vector<u_int8_t> image_non_critical;
    _imgOps->PrepItocSectionsForCompare(image_critical, image_non_critical);
    _fwOps->PrepItocSectionsForCompare(device_critical, device_non_critical);

    if (image_critical == device_critical && image_non_critical == device_non_critical)
    {
        res = true;
    }
    return true;
}

FlintStatus BinaryCompareSubCommand::executeCommand()
{
#ifndef NO_MSTARCHIVE
    string mfa2file = _flintParams.image;
    _mfa2Pkg = MFA2::LoadMFA2Package(mfa2file);
    if (_mfa2Pkg != NULL)
    {
        _flintParams.mfa2_specified = true;
        return compareMFA2();
    }
#endif

    if (preFwOps() == FLINT_FAILED)
    {
        if (_imgOps)
        {
            const char* errMessage = _imgOps->err();
            if (errMessage != NULL && strlen(errMessage) > 0)
            {
                reportErr(true, "Error occurred while executing flint initialization : %s\n", errMessage);
            }
        }
        return FLINT_FAILED;
    }
    mfile* mf = _fwOps->getMfileObj();
    int is_livefish_mode = dm_is_livefish_mode(mf);
    if (is_livefish_mode == 1)
    {
        _flintParams.override_cache_replacement = true;
    }
    // query both image and device
    if (!_fwOps->FwQuery(&_devInfo, true, false, true, false, (_flintParams.silent == false)))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), _fwOps->err());
        return FLINT_FAILED;
    }

    if (!_imgOps->FwQuery(&_imgInfo))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Image", _flintParams.image.c_str(), _imgOps->err());
        return FLINT_FAILED;
    }

    if (strcmp((char*)_imgInfo.fw_info.psid, (char*)_devInfo.fw_info.psid))
    {
        printf("\33[2K\r"); // clear the current line
        reportErr(true, "Binary comparison failed - PSID mismatch.\n");
        return FLINT_FAILED;
    }
    FwVersion img_version = FwOperations::createFwVersion(&_imgInfo.fw_info);
    FwVersion dev_version = FwOperations::createFwVersion(&_devInfo.fw_info);
    if (img_version != dev_version)
    {
        printf("\33[2K\r"); // clear the current line
        reportErr(true, "Binary comparison failed - versions mismatch.\n");
        return FLINT_FAILED;
    }

    bool device_encrypted = false;
    bool image_encrypted = false;
    if (!_fwOps->isEncrypted(device_encrypted))
    {
        reportErr(true, "Failed to identify if device is encrypted.\n");
        return FLINT_FAILED;
    }
    if (!_imgOps->isEncrypted(image_encrypted))
    {
        reportErr(true, "Failed to identify if image is encrypted.\n");
        return FLINT_FAILED;
    }
    if (device_encrypted != image_encrypted)
    {
        reportErr(true, "Binary comparison failed - encryption mismatch.\n");
        return FLINT_FAILED;
    }

    bool compare_res = false;
    if (device_encrypted)
    {
        if (!CompareEncryptedFwOps(compare_res))
        {
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!CompareFwOps(compare_res))
        {
            return FLINT_FAILED;
        }
    }

    if (compare_res == false)
    {
        reportErr(true, "Binary comparison failed - binary mismatch.\n");
        return FLINT_FAILED;
    }
    else
    {
        printf("\33[2K\r"); // clear the current line
        printf("Binary comparison success.\n");
        return FLINT_SUCCESS;
    }
}

/***********************
 * Class: SignRSASubCommand
 ***********************/
SignRSASubCommand::SignRSASubCommand()
{
    _name = "rsa_sign";
    _desc = "Sign firmware image file with RSA";
    _extendedDesc = "Sign firmware image file with RSA";
    _flagLong = "rsa_sign";
    _flagShort = "";
    _paramExp = "None";
    _example = FLINT_NAME " -i fw_image.bin --private_key file.pem"
                          " --public_key file.pub --key_uuid <uuid_string> rsa_sign";
    _v = Wtv_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_RSA_Sign;
}

SignRSASubCommand::~SignRSASubCommand() {}

// TODO - consider moving this functionality to a factory in mlxsign lib
unique_ptr<MlxSign::Signer> SignRSASubCommand::createSigner()
{
    unique_ptr<MlxSign::Signer> signer = nullptr;
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    signer = unique_ptr<MlxSign::Signer>(new MlxSign::MlxSignRSAViaOpenssl(_flintParams.privkey_file.c_str()));
#else
    reportErr(true, "RSA sign is not supported.\n");
#endif

    if (signer != nullptr && signer->Init() != MlxSign::MLX_SIGN_SUCCESS)
    {
        signer.reset();
        reportErr(true, "Failed to initialize signer.\n");
    }
    return signer;
}

FlintStatus SignRSASubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_imgOps->FwType() != FIT_FS4)
    {
        reportErr(true, IMAGE_SIGN_TYPE_ERROR);
        return FLINT_FAILED;
    }

    unique_ptr<MlxSign::Signer> signer_ptr = createSigner();
    if (signer_ptr == nullptr)
    {
        return FLINT_FAILED;
    }

    if (!_imgOps->SignForSecureBoot(_flintParams.pubkey_file.c_str(), _flintParams.privkey_uuid.c_str(), *signer_ptr))
    {
        reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
        return FLINT_FAILED;
    }

    if (!_imgOps->SignForFwUpdate(_flintParams.privkey_uuid.c_str(), *signer_ptr, MlxSign::SHA512, &verifyCbFunc))
    {
        reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
        return FLINT_FAILED;
    }

    //* Fill image_signature section with 0xff
    vector<u_int8_t> signature256Data(IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE, 0xff);
    _imgOps->UpdateSection(signature256Data.data(), FS3_IMAGE_SIGNATURE_256, true, CMD_SET_SIGNATURE, NULL);
    return FLINT_SUCCESS;
}

bool SignRSASubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }

    if (_flintParams.pubkey_file.empty())
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"--public_key\"");
        return false;
    }
    else if (!is_file_exists(_flintParams.pubkey_file.c_str()))
    {
        reportErr(true, SIGN_PUBLIC_KEY_NOT_FOUND, _flintParams.pubkey_file.c_str());
        return false;
    }

    if (_flintParams.privkey_uuid.empty())
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"--key_uuid\"");
        return false;
    }

    if (_flintParams.privkey_file.empty())
    {
        reportErr(true, "To sign the image with RSA you must provide private key.\n");
        return false;
    }
    else if (!is_file_exists(_flintParams.privkey_file.c_str()))
    {
        reportErr(true, SIGN_PRIVATE_KEY_NOT_FOUND, _flintParams.privkey_file.c_str());
        return false;
    }
   
    return true;
}

/***********************
 * Class: BurnSubCommand
 **********************/

BurnSubCommand::BurnSubCommand()
{
    _name = "burn";
    _desc = "Burn flash. Use \"-ir burn\" flag to perform image reactivation prior burning.";
    _extendedDesc = "Burn flash \n"
                    "Performs failsafe FW update from a raw binary image.";
    _flagLong = "burn";
    _flagShort = "b";
    _param = "[-ir]";
    _paramExp = "If supplied, perform image reactivation before burning.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -i image1.bin -ir burn\n" FLINT_NAME " -d " MST_DEV_EXAMPLE2
                          " -guid 0x2c9000100d050 -i image1.bin b";
    _v = Wtv_Dev_And_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Burn;
    _fwType = 0;
    _devQueryRes = 0;
    _mccSupported = true;
    _shouldSkip = false;
    memset(&_devInfo, 0, sizeof(_devInfo));
    memset(&_imgInfo, 0, sizeof(_imgInfo));
    _unknownProgress = 0;
    fwCompsAccess = NULL;
}

BurnSubCommand::~BurnSubCommand()
{
    closeLog();
    if (fwCompsAccess != NULL)
    {
        delete fwCompsAccess;
    }
    if (_burnParams.userVsd != NULL)
    {
        delete[] _burnParams.userVsd;
    }
#ifndef NO_MSTARCHIVE
    if (_mfa2Pkg != NULL)
    {
        delete _mfa2Pkg;
    }
#endif
}

bool BurnSubCommand::verifyMFA2Params(bool IsLiveFish)
{
    if (IsLiveFish)
    {
        if (_flintParams.use_psid == false)
        {
            reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2", "PSID must be supplied in livefish mode");
            return false;
        }
        if (_flintParams.use_latest_fw_version == true && _flintParams.num_of_args != 4)
        {
            reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2", "incorrect flag combination is supplied");
            return false;
        }
        if (_flintParams.use_latest_fw_version == false && _flintParams.num_of_args != 3)
        {
            reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2", "incorrect flag combination is supplied");
            return false;
        }
        return true;
    }
    else
    {
        if (_flintParams.use_latest_fw_version == true && _flintParams.num_of_args != 3)
        {
            reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2", "incorrect flag combination is supplied");
            return false;
        }
        if (_flintParams.use_latest_fw_version == false && _flintParams.num_of_args != 2)
        {
            reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2", "incorrect flag combination is supplied");
            return false;
        }
        return true;
    }
}

bool BurnSubCommand::verifyParams()
{
    if (_flintParams.mfa2_specified)
    {
        return true;
    }
    else if (_flintParams.linkx_control == true && _flintParams.linkx_els_control == true)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "--linkx", "--linkx_els");
        return false;
    }
    else if (_flintParams.linkx_control == true || _flintParams.linkx_els_control == true)
    {
        if (_flintParams.device_specified == false)
        {
            reportErr(true, "Must supply the device (and image, if not only activation required) for cables burn.\n");
            return false;
        }
        if (_flintParams.activate == false && _flintParams.download_transfer == false)
        {
            reportErr(true, "Must supply the download_transfer and/or activation flags for cables burn.\n");
            return false;
        }
        else if (_flintParams.activate == true && _flintParams.download_transfer == false)
        {
            // the image is not necessary if only activation is required
            if (_flintParams.linkx_auto_update == false)
            {
                if (_flintParams.cable_device_index_specified == false ||
                    _flintParams.cable_device_size_specified == false)
                {
                    reportErr(true, "Must supply the linkx <device index and size> or <autoupdate> for activate "
                                    "cables, but not both simultaneously!\n");
                    return false;
                }
            }
            else
            {
                if (_flintParams.cable_device_index_specified == true ||
                    _flintParams.cable_device_size_specified == true)
                {
                    reportErr(true, "Must supply the linkx <device index and size> or <autoupdate> for activate "
                                    "cables, bot not both simultaneously!\n");
                    return false;
                }
            }
            return true;
        }
        else
        {
            if (_flintParams.linkx_auto_update == false)
            {
                if (_flintParams.cable_device_index_specified == false ||
                    _flintParams.cable_device_size_specified == false)
                {
                    reportErr(true, "Must supply the linkx device index and size / or autoupdate for burn cables!\n");
                    return false;
                }
            }
            else
            {
                if (_flintParams.cable_device_index_specified == true ||
                    _flintParams.cable_device_size_specified == true)
                {
                    reportErr(true, "Must supply the linkx device index and size / or autoupdate for burn cables!\n");
                    return false;
                }
            }
            if (_flintParams.image_specified == false)
            {
                reportErr(true, "Must supply the device and image for cables burn.\n");
                return false;
            }
            string image = _flintParams.image;
            if (!is_file_exists(image.c_str()))
            {
                reportErr(true, "The supplied image for cables burn doesn't exist.\n");
                return false;
            }
            struct stat st;
            int status = stat(image.c_str(), &st);
            if (status != 0 || S_ISREG(st.st_mode) == 0)
            {
                reportErr(true, "The supplied image path is not a file.\n");
                return false;
            }
            long fileSize = 0;
            if (getFileSize(image, fileSize) == false)
            {
                reportErr(true, "Can't get the file size from the supplied image for cables burn.\n");
                return false;
            }
            if (fileSize < 8)
            {
                reportErr(true, "The supplied image for cables is not valid.\n");
                return false;
            }
        }
        return true;
    }
    else
    {
        if (_flintParams.cable_device_index_specified == true || _flintParams.cable_device_size_specified == true)
        {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                      "Flags 'cable_device_size'/'cable_device_index' relevant only for cable components.");
            return false;
        }
        if (_flintParams.activate == true || _flintParams.download_transfer == true ||
            _flintParams.activate_delay_sec != 1)
        {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                      "Flags 'activate'/'download_transfer'/'activate_delay_sec' relevant only for cable components.");
            return false;
        }
        if ((_flintParams.guid_specified || _flintParams.guids_specified) && (_flintParams.uid_specified))
        {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                      "either GUIDs / UID (using command line flags -guid(s) / -uid )");
            return false;
        }
        if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified))
        {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                      "either MACs / UID (using command line flags -mac(s) / -uid )");
            return false;
        }
        bool GuidsFromUser = _flintParams.guid_specified || _flintParams.guids_specified ||
                             _flintParams.uid_specified || _flintParams.mac_specified || _flintParams.macs_specified;
        if (GuidsFromUser && _flintParams.use_image_guids)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "GUIDs/UIDs/MACs", "-use_image_guids");
            return false;
        }
        if ((GuidsFromUser || _flintParams.use_image_guids) && _flintParams.blank_guids)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR,
                      _flintParams.use_image_guids ? "-use_image_guids" : "GUIDs/UIDs/MACs", "-blank_guids");
            return false;
        }
        if (_flintParams.guid_specified && _flintParams.guids_specified)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid");
            return false;
        }
        if (_flintParams.mac_specified && _flintParams.macs_specified)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-macs", "-mac");
            return false;
        }
        if (_flintParams.use_image_ps && _flintParams.vsd_specified)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-use_image_ps", "-vsd");
            return false;
        }
        if (_flintParams.ignore_dev_data && !_flintParams.nofs)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITHOUT_FLAG_ERROR, "-nofs", "-ignore_dev_data");
            return false;
        }
        if (_flintParams.use_dev_rom && _flintParams.use_image_rom)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "--use_dev_rom", "--use_image_rom");
            return false;
        }
        if (_flintParams.nofs || _flintParams.allow_psid_change || _flintParams.use_dev_rom)
        {
            // attempt to fallback to legacy flow (direct flash access via FW)
            _mccSupported = false;
        }
        if (_flintParams.image_reactivation && _flintParams.no_fw_ctrl)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-image_reactivation", "-no_fw_ctrl");
            return false;
        }

        if (_flintParams.image_reactivation && _flintParams.override_cache_replacement)
        {
            reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-image_reactivation", "-ocr");
            return false;
        }
    }
    return true;
}

void BurnSubCommand::updateBurnParams()
{
    _burnParams.progressFunc =
      _flintParams.silent == true ? (ProgressCallBack)NULL : _fwType == FIT_FS2 ? &burnCbFs2Func : &burnCbFs3Func;

    _burnParams.ProgressFuncAdv.func =
      _flintParams.silent == true ? (f_prog_func_adv)NULL : (f_prog_func_adv)&advProgressFunc;
    _burnParams.ProgressFuncAdv.opaque = &_unknownProgress;

    _burnParams.userGuidsSpecified = _flintParams.guids_specified || _flintParams.guid_specified;
    _burnParams.userMacsSpecified = _flintParams.macs_specified || _flintParams.mac_specified;
    _burnParams.userUidSpecified = _flintParams.uid_specified;
    _burnParams.vsdSpecified = _flintParams.vsd_specified;
    _burnParams.blankGuids = _flintParams.blank_guids;
    _burnParams.burnFailsafe = !_flintParams.nofs;
    _burnParams.allowPsidChange = _flintParams.allow_psid_change;
    _burnParams.useDevImgInfo = _flintParams.use_dev_img_info;
    _burnParams.useImagePs = _flintParams.use_image_ps;
    _burnParams.burnRomOptions = _flintParams.use_image_rom ? FwOperations::ExtBurnParams::BRO_ONLY_FROM_IMG :
                                                              FwOperations::ExtBurnParams::BRO_DEFAULT;
    _burnParams.useImageGuids = _flintParams.use_image_guids;
    _burnParams.singleImageBurn = !_flintParams.dual_image;
    _burnParams.noDevidCheck = _flintParams.no_devid_check;
    _burnParams.skipCiReq = _flintParams.skip_ci_req;
    _burnParams.useImgDevData = _flintParams.ignore_dev_data;
    if (_burnParams.userGuidsSpecified)
    {
        _burnParams.userUids = _flintParams.user_guids;
    }
    if (_burnParams.userUidSpecified)
    {
        _burnParams.userUids.resize(0);
        _burnParams.userUids.push_back(_flintParams.baseUid);
    }
    if (_burnParams.userMacsSpecified)
    {
        if (!_burnParams.userGuidsSpecified)
        {
            // we dont care about the first 4 values
            _burnParams.userUids.resize(GUIDS);
        }
        _burnParams.userUids.push_back(_flintParams.user_macs[0]);
        _burnParams.userUids.push_back(_flintParams.user_macs[1]);
    }
    if (_burnParams.vsdSpecified)
    {
        _burnParams.userVsd = strcpy(new char[_flintParams.vsd.size() + 1], _flintParams.vsd.c_str());
    }

    // make sure its of max size and fill the rest with 0xffff
    guid_t tmpGuid;
    tmpGuid.h = 0xffffffff;
    tmpGuid.l = 0xffffffff;
    _burnParams.userUids.resize(MAX_GUIDS, tmpGuid);
    _burnParams.cpu_utilization = _flintParams.cpu_percent;
    _burnParams.use_cpu_utilization = _flintParams.use_cpu_utilization;
}

#define VERSION_FORMAT(minor) minor < 100 ? "%d.%d.%04d" : "%d.%04d.%04d"
bool BurnSubCommand::checkFwVersion(bool CreateFromImgInfo, u_int16_t fw_ver0, u_int16_t fw_ver1, u_int16_t fw_ver2)
{
    FwVersion current = FwOperations::createFwVersion(&_devInfo.fw_info);
    FwVersion new_version;
    if (CreateFromImgInfo)
    {
        new_version = FwOperations::createFwVersion(&_imgInfo.fw_info);
    }
    else
    {
        new_version = FwOperations::createFwVersion(fw_ver0, fw_ver1, fw_ver2);
    }

    const string current_version_str = current.get_fw_version(VERSION_FORMAT(_devInfo.fw_info.fw_ver[1]), false, "N/A");
    printf("\n    Current FW version on flash:  %s\n", current_version_str.c_str());

    const string next_version_str = new_version.get_fw_version(
      VERSION_FORMAT((CreateFromImgInfo ? _imgInfo.fw_info.fw_ver[1] : fw_ver1)), false, "N/A");
    printf("    New FW version:               %s\n", next_version_str.c_str());

    if (_flintParams.log_specified)
    {
        print_line_to_log("Current FW version on flash: %s,  New FW version: %s\n", current_version_str.c_str(),
                          next_version_str.c_str());
    }

    if (current.is_set() && new_version.is_set())
    {
        if (!current.are_same_branch(new_version))
        {
            printf("\n    Note: The new FW version is on a different branch"
                   " then the current FW version on flash.\n");
        }
        else if (current >= new_version)
        {
            printf("\n    Note: The new FW version is %s the current FW"
                   " version on flash.\n",
                   current == new_version ? "the same as" : "older than");

            if (current == new_version && _flintParams.skip_if_same)
            {
                printf("\n    Skipping burn because firmware versions match and --skip_if_same flag is set.\n");
                _shouldSkip = true;
                return false;
            }

            if (!askUser())
            {
                return false;
            }
        }
    }

    printf("\n");
    _burnParams.ignoreVersionCheck = true;
    return true;
}

bool BurnSubCommand::checkPSID()
{
    if (strlen(_imgInfo.fw_info.psid) != 0 && strlen(_devInfo.fw_info.psid) != 0 &&
        strncmp(_imgInfo.fw_info.psid, _devInfo.fw_info.psid, PSID_LEN))
    {
        if (_flintParams.allow_psid_change)
        {
            printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"
                   "    Note: It is highly recommended not to change the PSID.\n",
                   _devInfo.fw_info.psid, _imgInfo.fw_info.psid);
            if (!askUser())
            {
                return false;
            }
        }
        else
        {
            printf("\n");
            reportErr(true, FLINT_PSID_ERROR, _devInfo.fw_info.psid, _imgInfo.fw_info.psid);
            return false;
        }
    }
    return true;
}

FlintStatus BurnSubCommand::burnFs3()
{
    _shouldSkip = false;
    bool printPreparing = false;
    if (_devQueryRes)
    {
        char errBuff[ERR_BUFF_SIZE] = {0};
        FwOperations::fw_ops_params_t fwParams;
        initDeviceFwParams(errBuff, fwParams);
        FsChecks fsChecks(_devInfo, _fwOps, _imgOps, _burnParams, fwParams);
        if (fsChecks.ExecuteChecks(&_fwOps, _burnParams, _devInfo))
        {
            vector<string> questions;
            fsChecks.GetUserQuestions(questions, "    ");
            delete[] fwParams.mstHndl;
            for (unsigned int i = 0; i < questions.size(); i++)
            {
                printf("\n%s\n", questions[i].c_str());
                if (!askUser())
                {
                    return FLINT_FAILED;
                }
            }
        }
        else
        {
            delete[] fwParams.mstHndl;
            reportErr(true, "Fixes is needed for Flash layout, an error occurred while preparing the operation");
            return FLINT_FAILED;
        }
        printPreparing = fsChecks._isTimeConsumingFixesNeeded;
    }

    // Here we want to burn FS3 device so we check if the image is indeed FS3 image
    if (_imgInfo.fw_type != FIT_FS3 && _imgInfo.fw_type != FIT_FS4 && _imgInfo.fw_type != FIT_FS5)
    {
        reportErr(true, FLINT_IMG_DEV_COMPAT_ERROR, "FS3", "FS3");
        return FLINT_FAILED;
    }
    const char* imgTypeStr = fwImgTypeToStr(_imgInfo.fw_type);
    // on FS3 burn we require query to pass
    if (!_devQueryRes && _burnParams.burnFailsafe)
    {
        reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr, _fwOps->err());
        return FLINT_FAILED;
    }
    // check FwVersion
    if (!checkFwVersion())
    {
        if (_shouldSkip)
        {
            return FLINT_SUCCESS;
        }
        return FLINT_BURN_ABORTED;
    }
    // check Psid
    if (_devQueryRes && !checkPSID())
    {
        return FLINT_FAILED;
    }
    // deal with rom
    if (!dealWithExpRom())
    {
        return FLINT_FAILED;
    }
    bool getRomFromDev = (_burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST);
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo))
    {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type,
               _imgInfo.fw_info.roms_info.exp_rom_com_devid);
        if (!askUser())
        {
            return FLINT_FAILED;
        }
    }
    if (!_burnParams.burnFailsafe)
    {
        printf("Burn process will not be failsafe. No checks will be performed.\n");
        if (_burnParams.useImgDevData)
        {
            printf("ALL flash, including the device data sections will be overwritten.\n");
        }
        printf("If this process fails, computer may remain in an inoperable state.\n");
        if (!askUser())
        {
            return FLINT_FAILED;
        }
    }

    if (printPreparing)
    {
        printf(" Preparing...\n");
    }

    bool device_encrypted = false;
    bool image_encrypted = false;
    if (!_fwOps->isEncrypted(device_encrypted))
    {
        reportErr(true, "Failed to identify if device is encrypted.\n");
        return FLINT_FAILED;
    }
    if (!_imgOps->isEncrypted(image_encrypted))
    {
        reportErr(true, "Failed to identify if image is encrypted.\n");
        return FLINT_FAILED;
    }

    if (device_encrypted && image_encrypted)
    {
        if (!_fwOps->burnEncryptedImage(_imgOps, _burnParams))
        {
            reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr, _fwOps->err());
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams))
        {
            reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr, _fwOps->err());
            return FLINT_FAILED;
        }
    }

    PRINT_PROGRESS(_burnParams.progressFunc, 101);
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    const char* resetRec = _fwOps->FwGetResetRecommandationStr();
    if (resetRec)
    {
        printf("-I- %s\n", resetRec);
    }
    return FLINT_SUCCESS;
}

FlintStatus BurnSubCommand::burnPldmComp(FsPldmOperations* pldmOps, string& componentType)
{
    u_int8_t* buff;
    u_int32_t buffSize = 0;
    if (!pldmOps->GetPldmComponentData(componentType, _devInfo.fw_info.psid, &buff, buffSize))
    {
        reportErr(true, "Failed to get PLDM component data.\n");
        return FLINT_FAILED;
    }

    // TODO: Update the component support check to be in the fwctrl burn function
    FwComponent::comps_ids_t compId = pldmOps->ToCompId(_flintParams.component_type);
    if (compId == FwComponent::COMPID_UNKNOWN || !_fwOps->IsComponentSupported(compId))
    {
        reportErr(true, "Component type %s is not supported by the device.\n", _flintParams.component_type.c_str());
        delete[] buff;
        UnlockDevice(_fwOps);
        return FLINT_FAILED;
    }
    vector<u_int8_t> compData(*buff, *buff + buffSize);
    if (!_fwOps->FwBurnAdvanced(compData, _burnParams, compId))
    {
        reportErr(true, FLINT_FSPLDM_BURN_ERROR, _flintParams.component_type.c_str(), _fwOps->err());
        delete[] buff;
        UnlockDevice(_fwOps);
        return FLINT_FAILED;
    }

    UnlockDevice(_fwOps);
    return FLINT_SUCCESS;
}

FlintStatus BurnSubCommand::PldmToFwOps(FsPldmOperations* pldmOps)
{
    std::string psid(_devInfo.fw_info.psid);
    u_int8_t* buff;
    u_int32_t buffSize = 0;
    // if psid empty in fwpkg the first component will be extracted
    if (!pldmOps->GetPldmComponentData("FW", psid, &buff, buffSize))
    {
        if (pldmOps->err())
        {
            reportErr(true, "%s\n", pldmOps->err());
            return FLINT_FAILED;
        }
        else
        {
            psid = "";
            if (!pldmOps->GetPldmComponentData("FW", psid, &buff, buffSize))
            {
                reportErr(true, "The component was not found in the PLDM fwpkg.\n");
                return FLINT_FAILED;
            }
        }
    }

    // extract devid from device
    mfile* mf = _fwOps->getMfileObj();
    dm_dev_id_t devid_t = DeviceUnknown;
    u_int32_t devid = 0, revid = 0;
    int rc = dm_get_device_id(mf, &devid_t, &devid, &revid);
    if (rc != 0)
    {
        reportErr(true, "Can not detect the device type.\n");
        return FLINT_FAILED;
    }

    // extract devid from fwpkg
    u_int16_t swDevId = 0;
    if (!psid.empty())
    {
        if (!pldmOps->GetPldmDescriptor(psid, DEV_ID_TYPE, swDevId))
        {
            reportErr(true, "DEVICE ID descriptor is not found in the PLDM fwpkg for PSID: %s.\n", psid.c_str());
            delete[] buff;
            return FLINT_FAILED;
        }
    }
    else
    {
        swDevId = dm_dev_type2sw_id(devid_t);
    }

    // create new image ops
    FwOperations* newImageOps = NULL;
    if (!pldmOps->CreateFwOpsImage((u_int32_t*)buff, buffSize, &newImageOps, swDevId, true))
    {
        reportErr(true, "Failed to use image from PLDM fwpkg. %s\n", pldmOps->err());
        return FLINT_FAILED;
    }
    delete _imgOps;
    _imgOps = newImageOps;
    delete[] buff;

    // query the image to get the device id and check if it is compatible with the device
    if (!_imgOps->FwQuery(&_imgInfo))
    {
        reportErr(true, "Failed to query the PLDM fwpkg image.\n");
        return FLINT_FAILED;
    }

    dm_dev_id_t imageType = dm_dev_sw_id2type(_imgInfo.fw_info.pci_device_id);
    if (devid_t != imageType)
    {
        reportErr(true, "PCI Device ID in PLDM fwpkg is not compatible with the Device ID on the device.\n");
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}

FlintStatus BurnSubCommand::burnFs2()
{
    _shouldSkip = false;
    if (_flintParams.striped_image)
    {
        reportErr(true, FLINT_FS2_STRIPED_ERROR);
        return FLINT_FAILED;
    }
    if (_imgInfo.fw_type != FIT_FS2)
    {
        reportErr(true, FLINT_IMG_DEV_COMPAT_ERROR, "FS2", "FS2");
        return FLINT_FAILED;
    }
    if (_burnParams.use_cpu_utilization)
    {
        if (_burnParams.cpu_utilization < 1 || _burnParams.cpu_utilization > 5)
        {
            reportErr(true, FLINT_ILLEGAL_CPU_VALUE);
            return FLINT_FAILED;
        }
    }
    // CheckMatchingHwDevId is done in mlxfwops burn routine.
    // CheckMatchingDevId is done in mlxfwops burn routine.

    (void)dealWithExpRom();
    bool getRomFromDev = _burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo))
    {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type,
               _imgInfo.fw_info.roms_info.exp_rom_com_devid);
        if (!askUser())
        {
            return FLINT_FAILED;
        }
    }

    // deal with guids
    if (!dealWithGuids())
    {
        return FLINT_FAILED;
    }

    // deal with failsifity should be made in fwops as we dont know if image/device fw is failsafe
    if (_burnParams.burnFailsafe & (!_imgInfo.fw_info.is_failsafe || !_devInfo.fw_info.is_failsafe))
    {
        if ((!_imgInfo.fw_info.is_failsafe && !_devInfo.fw_info.is_failsafe))
        {
            // When both image and flash are non-failsafe, flint will burn in a non-failsafe mode
            _burnParams.burnFailsafe = false;
        }
        else
        {
            // when only one of image and flash is non-failsafe, flint will fail with appropriate message
            reportErr(true,
                      "Failsafe burn failed: FW image in the %s is non failsafe.\n"
                      "    you cannot burn a%s failsafe image over a%s failsafe image in a failsafe mode.\n"
                      "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n",
                      _imgInfo.fw_info.is_failsafe ? "flash" : "given file", _imgInfo.fw_info.is_failsafe ? "" : " non",
                      _devInfo.fw_info.is_failsafe ? "" : " non");
            return FLINT_FAILED;
        }
    }

    // deal with vsd
    if (!dealWithVSD())
    {
        return FLINT_FAILED;
    }

    // check versions
    if (!checkFwVersion())
    {
        if (_shouldSkip)
        {
            return FLINT_SUCCESS;
        }
        return FLINT_BURN_ABORTED;
    }
    // check Psid
    if (_devQueryRes && !checkPSID())
    {
        return FLINT_FAILED;
    }

    // Warn if a fw which does not support config is burnt over fw that does support config
    // The other way (new fw with config, old fw w/o config) is a normal update flow.
    // Update: all fw should now support config sectors, so we just check any mismatch in the config pads

    // Verify config offset. Should never be different between image and flash (unless changing PSID).
    if (_imgInfo.fs2_info.config_pad != _devInfo.fs2_info.config_pad)
    {
        printf("\n");
        printf("-W- Configuration section offset on flash (%u sectors) differs from the"
               " Configuration section offset in the given image (%u sectors)."
               " Current device configuration (if exists) will be deleted.\n",
               _devInfo.fs2_info.config_pad,
               _imgInfo.fs2_info.config_pad);
        if (_burnParams.allowPsidChange)
        {
            if (!askUser())
            {
                return FLINT_FAILED;
            }
        }
        else
        {
            reportErr(true, "Use the '-allow_psid_change' flag to force this change.\n");
            return FLINT_FAILED;
        }
    }

    if (!_burnParams.burnFailsafe)
    {
        printf("Burn process will not be failsafe. No checks will be performed.\n");
        printf("ALL flash, including the Invariant Sector will be overwritten.\n");
        printf("If this process fails, computer may remain in an inoperable state.\n");
        if (!askUser())
        {
            return FLINT_FAILED;
        }
    }

    // Finally we can burn
    if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams))
    {
        reportErr(true, FLINT_FS2_BURN_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    PRINT_PROGRESS(_burnParams.progressFunc, 101);
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    if (_burnParams.burnStatus.imageCachedSuccessfully)
    {
        PRINT_PROGRESS(_burnParams.progressFunc, 102);
    }
    return FLINT_SUCCESS;
}

bool BurnSubCommand::dealWithVSD()
{
    if (!(_burnParams.vsdSpecified || _burnParams.useImagePs) &&
        !((strlen(_devInfo.fw_info.psid) != 0 && _devInfo.fw_info.vsd_sect_found)))
    {
        printf("\n");
        if (_burnParams.burnFailsafe)
        {
            reportErr(
              true, "Can not extract VSD/PSID info from flash.\n"
                    "    Can not burn in a failsafe mode. Please use \"-nofs\" flag to burn in a non failsafe mode.\n");
            return false;
        }
        else
        {
            printf("-W- Can not extract VSD/PSID info from flash.\n\n"
                   "    To use a specific VSD, abort and re-burn specifying the\n"
                   "    needed info (using command line flags -vsd / -use_image_ps).\n"
                   "    You can also continue burn using blank VSD.\n");
            if (!askUser())
            {
                return false;
            }
        }
    }
    return true;
}

bool BurnSubCommand::dealWithGuids()
{
    bool read_guids = true;
    bool ib_dev;
    bool eth_dev;
    // Get the FW types
    FwOperations::SetDevFlags(_imgInfo.fw_info.chip_type, _imgInfo.fw_info.dev_type, (fw_img_type)_imgInfo.fw_type,
                              ib_dev, eth_dev);
    // setDevFlags(_imgInfo, ib_dev, eth_dev);

    // Check if there is a need to read guids
    if (_burnParams.useImageGuids || _burnParams.blankGuids || (_burnParams.userGuidsSpecified && ib_dev) ||
        (_burnParams.userMacsSpecified))
    {
        read_guids = false;
    }
    // Check if the burnt FW is ok and readable in order to get the GUIDs later
    if (read_guids && !_devQueryRes)
    {
        // printMissingGuidErr(ib_dev, eth_dev);
        if (_burnParams.burnFailsafe)
        {
            reportErr(true,
                      "Can not extract GUIDs/MACs info from flash, %s\n"
                      "    Can not burn in a failsafe mode.\n"
                      "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n",
                      _fwOps->err());
        }
        else
        {
            reportErr(true, "Can not extract GUIDs/MACs info from flash, %s", _fwOps->err());
            printMissingGuidErr(ib_dev, eth_dev);
        }
        return false;
    }
    // Check guids flag to ensure correct patching of guids in mlxfwops
    bool is_guids_specified =
      _burnParams.userGuidsSpecified || _burnParams.userMacsSpecified || _burnParams.userUidSpecified;
    if (is_guids_specified)
    {
        if (!checkGuidsFlags(_imgInfo.fw_info.dev_type, _fwType, _burnParams.userGuidsSpecified,
                             _burnParams.userMacsSpecified, _burnParams.userUidSpecified, ib_dev, eth_dev))
        {
            return false;
        }
    }
    // report guid changes if needed. and update the user_guids vector in _burnParams
    if (is_guids_specified || _flintParams.use_image_guids)
    {
        guid_t* new_guids = (_burnParams.userGuidsSpecified || _burnParams.userUidSpecified) ?
                              &_burnParams.userUids[0] :
                              _devInfo.fs2_info.guids;
        guid_t* new_macs =
          _burnParams.userMacsSpecified != 0 ? &_burnParams.userUids[GUIDS] : &_devInfo.fs2_info.guids[GUIDS];
        guid_t* old_guids = !_devQueryRes ? NULL : _devInfo.fs2_info.guids;
        guid_t* old_macs = old_guids != NULL ? &old_guids[GUIDS] : NULL;
        if (!is_guids_specified && _flintParams.use_image_guids)
        {
            new_guids = _imgInfo.fs2_info.guids;
            new_macs = &_imgInfo.fs2_info.guids[GUIDS];
        }
        // printf("-D- l=%d, h=%d\n", new_macs->l, new_macs->h);
        if (!reportGuidChanges(new_guids, new_macs, old_guids, old_macs, ib_dev, eth_dev, _imgInfo.fs2_info.guid_num))
        {
            return false;
        }
    }
    return true;
}

bool BurnSubCommand::dealWithExpRom()
{
    bool getRomFromDev = false;

    // Check exp rom:
    bool fs2Cond;

    if (_fwType != FIT_FS2)
    {
        _burnParams.burnRomOptions = FwOperations::ExtBurnParams::BRO_ONLY_FROM_IMG;
        bool cond = _devQueryRes && IS_HCA(_devInfo.fw_info.chip_type);
        if (cond && _flintParams.use_dev_rom)
        {
            if (_devInfo.fw_info.roms_info.num_of_exp_rom > 0)
            {
                if (!strcmp(_devInfo.fw_info.product_ver, "") && !strcmp(_imgInfo.fw_info.product_ver, ""))
                {
                    _burnParams.burnRomOptions = FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
                }
                else if (_flintParams.allow_rom_change)
                {
                    _burnParams.burnRomOptions = FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
                }
                else
                {
                    // error, please use allow_rom_change flag
                    reportErr(true, "The device FW contains common FW/ROM Product Version - "
                                    "The ROM cannot be updated separately.\n");
                    return false;
                }
            }
            else
            {
                if (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0)
                {
                    if (!askUser("No Expansion ROM found in the device, "
                                 "Do you want to use the ROM from the image file",
                                 false))
                    {
                        return false;
                    }
                }
                else
                {
                    if (!askUser("No Expansion ROM found in the device"
                                 ", Do you want to continue"))
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    FwVersion dev_version = FwOperations::createFwVersion(&_devInfo.fw_info);
    bool rom_condition =
      (FwOperations::IsFwSupportingRomModify(dev_version) || (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0));
    fs2Cond = (_devQueryRes && IS_HCA(_devInfo.fw_info.chip_type) && rom_condition && !_flintParams.use_image_rom &&
               !strcmp(_devInfo.fw_info.product_ver, "") && !strcmp(_imgInfo.fw_info.product_ver, ""));

    if (fs2Cond)
    {
        // Enter here when:
        //                  The fw on the flash is OK (passed query, and it should pass verify in mlxfwops) &&
        //                  ( The device is connectx ||  connectib    )&&
        //                  The image fw supports modifying ROM OR it contains ROM &&.
        //                  The user didn't ask to burn the image rom. &&
        //                  The  fw on the flash doesn't contain product version

        if (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0 && _devInfo.fw_info.roms_info.num_of_exp_rom > 0)
        {
            printf("\n    Note: Both the image file and the flash contain a ROM image.\n"
                   "          Select \"yes\" to use the ROM from the given image file.\n"
                   "          Select \"no\" to keep the existing ROM in the flash\n");

            displayExpRomInfo(_devInfo.fw_info.roms_info, "    Current ROM info on flash: ");
            displayExpRomInfo(_imgInfo.fw_info.roms_info, "    ROM info from image file : ");
            if (!askUser("Use the ROM from the image file", false))
            {
                getRomFromDev = true;
            }
            else
            {
                getRomFromDev = false;
            }
        }
        else if (!(_imgInfo.fw_info.roms_info.num_of_exp_rom > 0) && _devInfo.fw_info.roms_info.num_of_exp_rom > 0)
        {
            getRomFromDev = true;
        }
    }
    if (getRomFromDev)
    {
        _burnParams.burnRomOptions = FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
    }
    return true;
}

bool BurnSubCommand::checkMatchingExpRomDevId(const fw_info_t& info)
{
    if ((info.fw_info.roms_info.num_of_exp_rom > 0) && (info.fw_info.dev_type) &&
        (info.fw_info.roms_info.exp_rom_com_devid != EXP_ROM_GEN_DEVID) &&
        (info.fw_info.roms_info.exp_rom_com_devid != MISS_MATCH_DEV_ID) &&
        (info.fw_info.dev_type != info.fw_info.roms_info.exp_rom_com_devid))
    {
        return false;
    }
    return true;
}

void BurnSubCommand::cleanInterruptedCommand()
{
    if (_flintParams.device_specified)
    {
        UnlockDevice(_fwOps);
        _fwOps->restoreWriteProtectInfo();
    }
}

FlintStatus BurnSubCommand::BurnCMISCable()
{
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
    DPRINTF(("BurnSubCommand::BurnCMISCable\n"));
    CableBurnFlow burnFlow(CableBurnFlow::Burn3rdParty);
    std::vector<u_int8_t> fwImage;
    std::vector<u_int8_t> vendorData;


    if (_flintParams.image.empty() && !_flintParams.activate && !_flintParams.commit_module_image &&
        !_flintParams.run_module_image)
    {
        reportErr(true, "Must provide an image or activate an image.\n");
        return FLINT_FAILED;
    }

    if (_flintParams.activate && (_flintParams.commit_module_image || _flintParams.run_module_image))
    {
        reportErr(true, "Cannot specify activate command with run_module_image or commit_module_image.\n");
        return FLINT_FAILED;
    }

    if (!_flintParams.image.empty())
    {
        if (burnFlow == CableBurnFlow::Burn3rdParty)
        {
            if (!readFromFile(_flintParams.image, fwImage))
            {
                return FLINT_FAILED;
            }
            if (!_flintParams.moduleVendorDataFile.empty())
            {
                if (!readFromFile(_flintParams.moduleVendorDataFile, vendorData))
                {
                    return FLINT_FAILED;
                }
            }
            if (_flintParams.moduleCommandTimeout.empty())
            {
                _flintParams.moduleCommandTimeout = "10000";
            }
        }
        else
        {
            reportErr(true, "Provided cable and image are not supported.\n");
            return FLINT_BURN_ABORTED;
        }
    }

    u_int8_t countResets = 0;
    u_int8_t countRetry = 0;

    FlintStatus rc = FLINT_FAILED;

    while (countResets < CABLE_BURN_RESET_MAX && countRetry < CABLE_BURN_TIMEOUT_MAX && rc != FLINT_SUCCESS)
    {
        rc = PerformBurn(fwImage, vendorData);

        if (rc != FLINT_SUCCESS)
        {
            if (rc == FLINT_BURN_ERROR)
            {
                if (ResetModule(_flintParams.device))
                {
                    return FLINT_FAILED;
                }
                DPRINTF(("BurnSubCommand::BurnCMISCable retry burn after reset, counter = %d.\n", countResets));
                countResets++;
            }
            else if (rc == FLINT_BURN_TO)
            {
                DPRINTF(("BurnSubCommand::BurnCMISCable retry burn after to, counter = %d.\n", countRetry));
                countRetry++;
            }
            else
            {
                return rc;
            }
        }
    }

    return rc;

#else
    reportErr(true, "FW update on cables is not supported.\n");
    return FLINT_FAILED;
#endif
}

FlintStatus BurnSubCommand::ResetModule(string device)
{
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
    cableAccess cblAccess((char*)device.c_str());
    if (!cblAccess.init())
    {
        reportErr(true, "%s", cblAccess.getLastErrMsg().c_str());
        return FLINT_FAILED;
    }
    if (!cblAccess.resetCable())
    {
        reportErr(true, "%s", cblAccess.getLastErrMsg().c_str());
        return FLINT_FAILED;
    }

    return WaitForModuleInit(device);
#else
    (void)device;
    reportErr(true, "FW update on cables is not supported.\n");
    return FLINT_FAILED;
#endif
}

FlintStatus BurnSubCommand::WaitForModuleInit(string device)
{
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
    u_int32_t counter = 0;
    cableAccess cblAccess((char*)device.c_str());
    while (!cblAccess.init() && counter < CABLE_BURN_INIT_MAX)
    {
        msleep(1000);
        ++counter;
    }
    if (counter >= CABLE_BURN_INIT_MAX)
    {
        reportErr(true, "cable initialization failed after reset!\n");
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
#else
    (void)device;
    reportErr(true, "FW update on cables is not supported.\n");
    return FLINT_FAILED;
#endif
}

FlintStatus BurnSubCommand::PerformBurn(std::vector<u_int8_t>& fwImage, std::vector<u_int8_t>& vendorData)
{
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
    try
    {
        FwManagementCdbCommander cableCommander(_flintParams.device,false);

        if (!_flintParams.modulePassword.empty())
        {
            cableCommander.SetPassword(_flintParams.modulePassword);
        }

        if (!_flintParams.moduleCommandTimeout.empty())
        {
            cableCommander.SetCommandWaitingTime(_flintParams.moduleCommandTimeout);
        }

        if (!_flintParams.image.empty())
        {
            cableCommander.DownloadFWImage(
              fwImage, vendorData,
              [](int completion) { return CbCommon(completion, (char*)"FW update progress: ", (char*)"completed "); });
        }

        if (_flintParams.activate)
        {
            cableCommander.ActivateImage();
            if (ResetModule(_flintParams.device))
            {
                return FLINT_FAILED;
            }
        }

        if (_flintParams.run_module_image)
        {
            cableCommander.RunImage();
        }

        if (_flintParams.commit_module_image)
        {
            cableCommander.CommitImage();
        }
    }
    catch (const std::exception& e)
    {
        DPRINTF(("BurnSubCommand::PerformBurn cable burn failed with erro =%s\n", e.what()));
        string err = "got unknown status (0x43) in response to cdb command.";
        string err2 = "time out while waiting for command completion.";
        string err3 = "Cable access R/W failed status: 4. ";
        if (e.what() == err || e.what() == err3)
        {
            return FLINT_BURN_ERROR;
        }
        if (e.what() == err2)
        {
            return FLINT_BURN_TO;
        }
        cerr << e.what() << endl;
        return FLINT_FAILED;
    }
    catch (...)
    {
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
#else
    (void)fwImage;
    (void)vendorData;
    reportErr(true, "FW update on cables is not supported.\n");
    return FLINT_FAILED;
#endif
}

FlintStatus BurnSubCommand::executeCommand()
{
    if (_flintParams.linkx_control == true || _flintParams.linkx_els_control == true)
    {
        if (!verifyParams())
        {
            return FLINT_FAILED;
        }
        int opaque = 0;
        ProgressCallBackAdvSt ProgressFuncAdv;
        ProgressFuncAdv.func = (f_prog_func_adv)&advProgressFunc;
        ProgressFuncAdv.opaque = &opaque;
        FwComponent::comps_ids_t fwComponent =
          _flintParams.linkx_control ? FwComponent::COMPID_LINKX : FwComponent::COMPID_LINKX_ELS;
        return BurnLinkX(_flintParams.device, _flintParams.cableDeviceIndex, _flintParams.cableDeviceSize,
                         _flintParams.image, _flintParams.linkx_auto_update, _flintParams.activate,
                         _flintParams.download_transfer, _flintParams.activate_delay_sec, &ProgressFuncAdv,
                         fwComponent);
    }

    if (_flintParams.device.find("_cable") != string::npos && _flintParams.device.find("_rt") == string::npos)
    {
        FlintStatus rc = FLINT_SUCCESS;
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
        rc = BurnCMISCable();
#else
        reportErr(true, "FW update on cables is not supported.\n");
        rc = FLINT_FAILED;
#endif
        return rc;
    }

#ifndef NO_MSTARCHIVE
    string mfa2file = _flintParams.image;
    _mfa2Pkg = MFA2::LoadMFA2Package(mfa2file);
    if (_mfa2Pkg != NULL)
    {
        _flintParams.mfa2_specified = true;
    }
#endif
    if (_flintParams.image_reactivation)
    {
        if (preFwOps(true) == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
        if (!_fwOps->FwReactivateImage())
        {
            reportErr(true, FLINT_FAILED_IMAGE_REACTIVATION_ERROR, _flintParams.device.c_str(), _fwOps->err());
            return FLINT_FAILED;
        }
        printf("\n-I- FW Image Reactivation succeeded.\n\n");
        _fwOps = _imgOps = NULL;
        if (preFwOps() == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
    }
    else if (_flintParams.mfa2_specified)
    {
        bool saved_value = _flintParams.silent;
        _flintParams.silent = true;
        FlintStatus res = preFwOps();
        _flintParams.silent = saved_value;
        if (res == FLINT_FAILED)
        {
            _flintParams.override_cache_replacement = true;
            if (preFwOps() == FLINT_FAILED)
            {
                return FLINT_FAILED;
            }
        }
        mfile* mf = _fwOps->getMfileObj();
        int is_livefish_mode = dm_is_livefish_mode(mf);
        if (verifyMFA2Params(is_livefish_mode == 1) == false)
        {
            return FLINT_FAILED;
        }
        // check if the device is in FW control mode ("mcc flow"). Other flow is unsupported.
        if (is_livefish_mode)
        {
            /*reportErr(true, "Burning MFA2 is not supported in Livefish mode.\n");
            return FLINT_FAILED;*/
            dm_dev_id_t devid_t;
            u_int32_t devid;
            u_int32_t revid;
            int rc = dm_get_device_id(mf, &devid_t, &devid, &revid);
            if (rc != 0)
            {
                reportErr(true, "Burning MFA2: can't get device Id");
                return FLINT_FAILED;
            }
            return burnMFA2LiveFish(devid_t);
        }
        bool is_fw_ctrl = _fwOps->IsFsCtrlOperations();
        if (!is_fw_ctrl)
        {
            reportErr(true, "Burning MFA2 is not supported without FW control.\n");
            return FLINT_FAILED;
        }
        else
        {
            updateBurnParams();
            if (_flintParams.use_psid == true)
            {
                reportErr(true, FLINT_COMMAND_INCORRECT_FLAGS_ERROR, "Burn MFA2",
                          "incorrect flag combination is supplied");
                return FLINT_FAILED;
            }
            if (LockDevice(_fwOps) == FLINT_FAILED)
            {
                return FLINT_FAILED;
            }
            FlintStatus burnResult = burnMFA2();
            if (UnlockDevice(_fwOps) == FLINT_FAILED)
            {
                return FLINT_FAILED;
            }
            return burnResult;
        }
    }
    else if (_flintParams.congestion_control)
    {
        return burnCongestionControl();
    }
    else
    {
        if (preFwOps() == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
    }
    if (LockDevice(_fwOps) == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // set fw type

    // updateBurnParams with input given by user
    _fwType = _fwOps->FwType();
    updateBurnParams();

    // query both image and device (deviceQuery can fail but we save rc)
    _devQueryRes = _fwOps->FwQuery(&_devInfo, true, false, true, false, (_flintParams.silent == false));
    
    if (_imgOps->FwType() == FIT_PLDM_1_0)
    {
        string component_type = _flintParams.component_type.empty() ? "FW" : _flintParams.component_type;
        FsPldmOperations* pldmOps = dynamic_cast<FsPldmOperations*>(_imgOps);
        if (pldmOps == nullptr)
        {
            reportErr(true, "Failed to create PLDM operations.\n");
            return FLINT_FAILED;
        }
        if (!pldmOps->LoadPldmPackage())
        {
            reportErr(true, "Failed to load PLDM fwpkg.\n");
            return FLINT_FAILED;
        }

        if (strlen(_devInfo.fw_info.psid) == 0)
        {
            reportErr(true, "-E- Cant get psid from Device.\n");
            return FLINT_FAILED;
        }

        if (component_type == "FW")
        {
            if (PldmToFwOps(pldmOps) == FLINT_FAILED)
            {
                reportErr(true, "%s", pldmOps->err());
                return FLINT_FAILED;
            }
        }
        else
        {
            return burnPldmComp(pldmOps, component_type);
        }
    }

    if (_imgOps->FwType() == FIT_COMPS)
    {
        FsCompsOperations* compsOps = dynamic_cast<FsCompsOperations*>(_imgOps);
        if (_flintParams.yes)
        {
            _burnParams.ignoreVersionCheck = true;
        }
        if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams, compsOps->GetComponentID()))
        {
            reportErr(true, FLINT_FSX_BURN_ERROR, "FIT_COMPS", _fwOps->err());
            return FLINT_FAILED;
        }
        else
        {
            cout << "-I- Component FW burn finished successfully." << endl;
            const char* resetRec = _imgOps->FwGetResetRecommandationStr();
            if (resetRec)
            {
                printf("-I- %s\n", resetRec);
            }
            return FLINT_SUCCESS;
        }
    }

    if (_fwOps->IsFifthGen())
    {
        if (_flintParams.mac_specified || _flintParams.macs_specified)
        {
            UnlockDevice(_fwOps);
            reportErr(true, FLINT_INVALID_FLAG_ERROR_5TH_GEN, _flintParams.macs_specified ? "-macs" : "-mac");
            return FLINT_FAILED;
        }
        if (_flintParams.guid_specified || _flintParams.guids_specified)
        {
            UnlockDevice(_fwOps);
            reportErr(true, FLINT_INVALID_FLAG_ERROR_5TH_GEN, _flintParams.guids_specified ? "-guids" : "-guid");
            return FLINT_FAILED;
        }
    }

    bool device_encrypted = false;
    bool image_encrypted = false;
    if (!_fwOps->isEncrypted(device_encrypted))
    {
        reportErr(true, "Failed to identify if device is encrypted.\n");
        return FLINT_FAILED;
    }
    if (!_imgOps->isEncrypted(image_encrypted))
    {
        reportErr(true, "Failed to identify if image is encrypted.\n");
        return FLINT_FAILED;
    }

    if (device_encrypted != image_encrypted && _fwType != FIT_FS5)
    {
        reportErr(true, "Burning %sencrypted image on %sencrypted device is not allowed.\n",
                  image_encrypted ? "" : "non-", device_encrypted ? "" : "non-");
        return FLINT_FAILED;
    }

    if (!_imgOps->FwQuery(&_imgInfo))
    {
        UnlockDevice(_fwOps);
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "image", _flintParams.image.c_str(), _imgOps->err());
        return FLINT_FAILED;
    }

    if (_imgOps->GetIsReducedImage() && _burnParams.useImgDevData)
    {
        // useImgDevData indicator is initialized by the --ignore_dev_data flag
        reportErr(true, "ignore_dev_data flag is not applicable with the given reduced image.\n");
        return FLINT_FAILED;
    }

    // Abort if the image is restricted according to the Security-Version
    if (_fwOps->IsSecurityVersionViolated(_imgInfo.fs3_info.image_security_version))
    {
        reportErr(true, "The image you're trying to burn is restricted. Aborting ... \n");
        return FLINT_FAILED;
    }

    if (_flintParams.use_image_guids && _fwType != FIT_FS2)
    {
        UnlockDevice(_fwOps);
        reportErr(true, "The \"--use_image_guids\" flag is supported only for GEN4 devices.\n");
        return FLINT_FAILED;
    }
    if (_fwType == FIT_FS3 || _fwType == FIT_FS4 || _fwType == FIT_FS5 || _fwType == FIT_FSCTRL)
    {
        u_int32_t devid = 0;
        mfile* mf = _fwOps->getMfileObj();
        if (mf != NULL)
        { // Patch for BF1
            int is_livefish_mode = dm_is_livefish_mode(mf);
            if (is_livefish_mode == 1)
            {
                if (mread4(mf, 0xf0014, &devid) != 4)
                {
                    devid = 0;
                }
                else
                {
                    devid &= 0xffff; // remove revid (BF1-rev1 is 0x00010211)
                    if (devid == BF_HW_ID && is_arm())
                    {
                        // for Bluefield need also check the life cycle, but only on ARM side!
                        string bf_lifecycle_file = "/sys/bus/platform/drivers/mlx-bootctl/lifecycle_state";
                        bool IsHmacAllowed = true;
                        if (is_file_exists(bf_lifecycle_file))
                        {
                            std::vector<u_int8_t> buff;
                            if (readFromFile(bf_lifecycle_file, buff))
                            {
                                if (buff.size() >= 10)
                                { // LIFE_CYCLE should not be GA Secured
                                    if (buff[0] == 'G' && buff[1] == 'A' && buff[2] == ' ' && buff[3] == 'S' &&
                                        buff[4] == 'e' && buff[5] == 'c' && buff[6] == 'u' && buff[7] == 'r' &&
                                        buff[8] == 'e' && buff[9] == 'd')
                                    {
                                        IsHmacAllowed = false;
                                    }
                                    if (IsHmacAllowed == true)
                                    {
                                        _burnParams.use_chip_type = true;
                                        _burnParams.chip_type = FwOperations::getChipType(devid);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        FlintStatus res = burnFs3();
        UnlockDevice(_fwOps);
        return res;
    }
    else if (_fwType == FIT_FS2)
    {
        FlintStatus res = burnFs2();
        UnlockDevice(_fwOps);
        return res;
    }
    // unknown fw type
    reportErr(true, FLINT_UNKNOWN_FW_TYPE_ERROR);
    if (UnlockDevice(_fwOps) == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

u_int32_t SubCommand::getUserChoice(u_int32_t maximumValue)
{
    u_int32_t choice = 0xffff;
    while (true)
    {
        int res = scanf("%d", &choice);
        if (res != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid data entered, try again!\n");
            continue;
        }
        if (choice > maximumValue)
        {
            printf("Please choose the version or 0 to exit:\n");
            continue;
        }
        break;
    }
    if (choice == 0)
    {
        exit(0);
    }
    return choice;
}

FlintStatus BurnSubCommand::burnMFA2LiveFish(dm_dev_id_t devid_t)
{
#ifndef NO_MSTARCHIVE
    int deviceMajorVer = 0;
    if (DeviceConnectX4 == devid_t)
    {
        deviceMajorVer = 12;
    }
    else if (DeviceConnectX4LX == devid_t)
    {
        deviceMajorVer = 14;
    }
    else if (DeviceConnectX5 == devid_t)
    {
        deviceMajorVer = 16;
    }
    else if (DeviceConnectX6 == devid_t)
    {
        deviceMajorVer = 20;
    }
    else if (DeviceConnectX6DX == devid_t)
    {
        deviceMajorVer = 22;
    }
    else if (DeviceConnectX6LX == devid_t)
    {
        deviceMajorVer = 26;
    }
    else
    {
        reportErr(true, "The MFA2 burning is not supported in livefish for current device %d", (int)devid_t);
        return FLINT_FAILED;
    }

    vector<u_int8_t> componentBuffer;
    if (_flintParams.use_psid == false)
    {
        reportErr(true, "Must supply \"--psid\" flag while burning device in the livefish mode with MFA2\n");
        return FLINT_FAILED;
    }
    char* psid = (char*)_flintParams.psid.c_str();
    u_int16_t fw_ver[3];
    fw_ver[0] = deviceMajorVer;
    fw_ver[1] = 0xff;
    fw_ver[2] = 0xffff;
    map_string_to_component matchingComponentsMap = _mfa2Pkg->getMatchingComponents(psid, fw_ver);
    u_int32_t matchingSize = matchingComponentsMap.size();
    if (matchingSize == 0)
    {
        reportErr(true, "No matching binaries found for device %s\n", _flintParams.device.c_str());
        return FLINT_FAILED;
    }
    else
    {
        if (matchingSize == 1)
        {
            _mfa2Pkg->unzipComponent(matchingComponentsMap, 0, componentBuffer);
        }
        else
        {
            if (_flintParams.use_latest_fw_version == true)
            {
                if (_mfa2Pkg->unzipLatestVersionComponent(matchingComponentsMap, componentBuffer) == false)
                {
                    return FLINT_FAILED;
                }
            }
            else
            {
                int i = 1;
                printf("------FW Version Selection for %s------\n", _flintParams.device.c_str());
                for (map_string_to_component::iterator it = matchingComponentsMap.begin();
                     it != matchingComponentsMap.end();
                     it++)
                {
                    printf("%d. %s\n", i++, it->first.c_str());
                }
                printf("-I- Please choose the version or 0 to exit:\n");
                u_int32_t choice = getUserChoice(matchingSize) - 1;
                if (_mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer) == false)
                {
                    return FLINT_FAILED;
                }
                while (getchar() != '\n')
                    ; // clean the stdin buffer
            }
        }
    }

    _flintParams.override_cache_replacement = true;
    _flintParams.image_specified = false;

    if (openOps(true, true) == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    struct image_layout_uid_entry base_guid = {0, 0, 0, 0};
    struct image_layout_uid_entry base_mac = {0, 0, 0, 0};

    bool NeedToSetMacManually = true;
    if (_fwOps->FwQuery(&_devInfo, true, false, true, false, (_flintParams.silent == false)))
    {
        if (_devInfo.fs3_info.fs3_uids_info.guid_format == IMAGE_LAYOUT_UIDS)
        {
            base_guid.num_allocated = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_guid.num_allocated;
            base_guid.num_allocated_msb = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_guid.num_allocated_msb;
            base_guid.step = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_guid.step;
            base_guid.uid = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_guid.uid;
            base_mac.num_allocated = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_mac.num_allocated;
            base_mac.num_allocated_msb = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_mac.num_allocated_msb;
            base_mac.step = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_mac.step;
            base_mac.uid = _devInfo.fs3_info.fs3_uids_info.image_layout_uids.base_mac.uid;
            NeedToSetMacManually = false;
        }
    }

    u_int8_t fs4_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0xAB, 0xCD, 0xEF, 0x00,
                                      0xFA, 0xDE, 0x12, 0x34, 0x56, 0x78, 0xDE, 0xAD};
    u_int8_t fs3_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0x8C, 0xDF, 0xD0, 0x00,
                                      0xDE, 0xAD, 0x92, 0x70, 0x41, 0x54, 0xBE, 0xEF};
    _fwType = _fwOps->FwType();
    if (_fwType == FIT_FS4 || _fwType == FIT_FSCTRL)
    {
        for (u_int8_t i = 0; i < sizeof(fs4_image_signature); i++)
        {
            componentBuffer[i] = fs4_image_signature[i];
        }
    }
    else if (_fwType == FIT_FS3)
    {
        for (u_int8_t i = 0; i < sizeof(fs3_image_signature); i++)
        {
            componentBuffer[i] = fs3_image_signature[i];
        }
    }
    else if (_fwType == FIT_FS5)
    {
        reportErr(true, "burning MFA2 in livefish mode is not supported for FS5 and FS6");
        return FLINT_FAILED;
    }

    string fileName = "/tmp/temp.bin"; // Get temp name
    writeImageToFile(fileName.c_str(), componentBuffer.data(), componentBuffer.size());
    _flintParams.image_specified = true;
    _flintParams.image = fileName;

    if (openOps(true, true) == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_fwOps->RemoveWriteProtection() == false)
    {
        reportErr(true, "Failed to disable flash write protection: %s", _fwOps->err());
        return FLINT_FAILED;
    }

    if (_imgOps->RestoreDevToc(componentBuffer, psid, devid_t, base_guid, base_mac) == false)
    {
        reportErr(true, "Failed to restore DTOCs for device %s: %s.\n", _flintParams.device.c_str(), _imgOps->err());
        return FLINT_FAILED;
    }
    writeImageToFile(fileName.c_str(), componentBuffer.data(), componentBuffer.size());
    if (openOps(true, false) == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (!_imgOps->FwQuery(&_imgInfo))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Image", _flintParams.image.c_str(), _imgOps->err());
        return FLINT_FAILED;
    }
    _flintParams.nofs = true;
    _flintParams.ignore_dev_data = true;
    _flintParams.override_cache_replacement = true;
    _flintParams.guid_specified = true;
    if (NeedToSetMacManually)
    {
        printf("Warning: No valid GUID/MAC found on the device flash. You will need to set it manually.\n");
    }
    updateBurnParams();
    _burnParams.allowPsidChange = true;

    return burnFs3();
#else
    (void)devid_t;
    reportErr(true, FLINT_NO_MFA2);
    return FLINT_FAILED;
#endif
}

FlintStatus BurnSubCommand::burnCongestionControl()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (!_fwOps->FwQuery(&_devInfo))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), _fwOps->err());
        return FLINT_FAILED;
    }
    bool is_fw_ctrl = _fwOps->IsFsCtrlOperations();
    if (!is_fw_ctrl)
    {
        reportErr(true, "Burning CongestionControl is not supported without FW control.\n");
        return FLINT_FAILED;
    }

    vector<u_int8_t> componentBuffer;
    if (!readFromFile(_flintParams.image, componentBuffer))
    {
        return FLINT_FAILED;
    }

    int sig = FwOperations::getFileSignature(_flintParams.image.c_str());
    if (sig != FwOperations::IMG_SIG_TYPE_CC)
    { // i.e we failed to check the magic pattern of the file
        reportErr(true, "Burning CC image failed: Wrong Image signature\n");
        return FLINT_FAILED;
    }
    updateBurnParams();
    componentBuffer[0] = 0xff; // due the FW needs.
    componentBuffer[1] = 0xff; // due the FW needs.
    componentBuffer[2] = 0xff; // due the FW needs.
    componentBuffer[3] = 0xff; // due the FW needs.
    bool res = _fwOps->FwBurnAdvanced(componentBuffer, _burnParams, FwComponent::COMPID_CONGESTION_CONTROL);
    if (!res)
    {
        reportErr(true, "Burning CC image failed: %s, FW error\n", _fwOps->err());
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}

FlintStatus BurnSubCommand::burnMFA2()
{
#ifndef NO_MSTARCHIVE
    vector<u_int8_t> componentBuffer;
    map_string_to_component matchingComponentsMap;
    if (!_fwOps->FwQuery(&_devInfo, true, false, true, false, (_flintParams.silent == false)))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), _fwOps->err());
        return FLINT_FAILED;
    }
    printf("-I- Fetching FW versions from MFA2 image, this operation may take a minute, please wait..\n");
    u_int16_t fw_ver[3];
    fw_ver[0] = _devInfo.fw_info.fw_ver[0];
    fw_ver[1] = 0xff;
    fw_ver[2] = 0xffff;
    matchingComponentsMap = _mfa2Pkg->getMatchingComponents((char*)_devInfo.fw_info.psid, fw_ver);
    u_int32_t matchingSize = matchingComponentsMap.size();
    if (matchingSize == 0)
    {
        reportErr(true, "No matching binaries found for device %s\n", _flintParams.device.c_str());
        return FLINT_FAILED;
    }
    else
    {
        // If there is only one matching FW binary, unzip it
        if (matchingSize == 1)
        {
            _mfa2Pkg->unzipComponent(matchingComponentsMap, 0, componentBuffer);
        }
        else
        {
            // user wants the latest version automatically
            if (_flintParams.use_latest_fw_version == true)
            {
                if (_mfa2Pkg->unzipLatestVersionComponent(matchingComponentsMap, componentBuffer) == false)
                {
                    return FLINT_FAILED;
                }
            }
            // otherwise, user must supply required version
            else
            {
                int i = 1;
                printf("------FW Version Selection for %s------\n", _flintParams.device.c_str());
                for (map_string_to_component::iterator it = matchingComponentsMap.begin();
                     it != matchingComponentsMap.end();
                     it++)
                {
                    printf("%d. %s\n", i++, it->first.c_str());
                }
                printf("-I- Please choose the version or 0 to exit:\n");
                u_int32_t choice = getUserChoice(matchingSize) - 1;
                if (_mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer) == false)
                {
                    return FLINT_FAILED;
                }
                while (getchar() != '\n')
                    ; // clean the stdin buffer
                map_string_to_component::iterator itAtOffset = matchingComponentsMap.begin();
                std::advance(itAtOffset, choice);
                Component* requiredComponent = &itAtOffset->second;
                VersionExtension version = requiredComponent->getComponentDescriptor().getVersionExtension();
                // check FwVersion
                u_int32_t fw_ver0 = version.getMajor();
                u_int32_t fw_ver1 = version.getMinor();
                u_int32_t fw_ver2 = version.getSubMinor();
                if (!checkFwVersion(false, fw_ver0, fw_ver1, fw_ver2))
                {
                    return FLINT_BURN_ABORTED;
                }
            }
        }
    }
    const char* imgTypeStr = fwImgTypeToStr(_devInfo.fw_type);
    bool res = _fwOps->FwBurnAdvanced(componentBuffer, _burnParams);
    if (!res)
    {
        reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr, _fwOps->err());
        return FLINT_FAILED;
    }
    else
    {
        PRINT_PROGRESS(_burnParams.progressFunc, 101);
        write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
        const char* resetRec = _fwOps->FwGetResetRecommandationStr();
        if (resetRec)
        {
            printf("-I- %s\n", resetRec);
        }
        return FLINT_SUCCESS;
    }
#else
    reportErr(true, FLINT_NO_MFA2);
    return FLINT_FAILED;
#endif
}

/***********************
 * Class: QuerySubCommand
 **********************/

bool QuerySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "full")
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "full");
        return false;
    }
    return true;
}

bool QuerySubCommand::checkMac(u_int64_t mac, string& warrStr)
{
    if ((mac >> 40) & 0x1)
    {
        warrStr = FLINT_MULTI_BIT_WARNING;
        return false;
    }

    if (mac >> 48)
    {
        warrStr = FLINT_MORE_48_BITS_WARNING;
        return false;
    }

    return true;
}

bool QuerySubCommand::displayFs2Uids(const fw_info_t& fwInfo)
{
    const char* mac_indent = "";
    bool ibDev;
    bool ethDev;
    FwOperations::SetDevFlags(fwInfo.fw_info.chip_type, fwInfo.fw_info.dev_type, (fw_img_type)fwInfo.fw_type, ibDev,
                              ethDev);
    // setDevFlags(fwInfo, ibDev, ethDev);
    int numPorts = 2;
    // we do not support cards with one port anymore.

    // GUIDS:
    if (ibDev)
    {
        // report("GUID Des:        Node             Port1            ");
        printf("Description:           Node             ");
        if (numPorts > 0)
        {
            printf("Port1            ");
        }
        if (numPorts > 1)
        {
            printf("Port2            ");
        }
        printf("Sys image\n");

        printf("GUIDs:                 ");
        for (u_int32_t i = 0; i < GUIDS; i++)
        {
            if ((i == 1 && numPorts < 1) || (i == 2 && numPorts < 2))
            {
                continue;
            }
            printf(GUID_FORMAT " ", fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l);
        }
        if (numPorts > 0)
        {
            mac_indent = "                 ";
        }
    }
    // MACS:
    if (ethDev)
    {
        if (fwInfo.fs2_info.guid_num == 6)
        {
            if (!ibDev)
            {
                printf("Description:  %s    Port1            Port2\n", mac_indent);
            }
            else
            {
                printf("\n");
            }
            printf("MACs:          %s       ", mac_indent);
            for (u_int32_t i = GUIDS; i < 6; i++)
            {
                printf("     " MAC_FORMAT, fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l);
            }

            for (u_int32_t i = GUIDS; i < 6; i++)
            {
                u_int64_t mac = (((u_int64_t)fwInfo.fs2_info.guids[i].h) << 32) | fwInfo.fs2_info.guids[i].l;
                string warrStr;
                if (!fwInfo.fs2_info.blank_guids && !checkMac(mac, warrStr))
                {
                    if (i == GUIDS)
                    {
                        printf("\n\n");
                    }
                    printf(FLINT_BAD_MAC_ADRESS_WARNING, fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l,
                           warrStr.c_str());
                }
            }
        }
        else
        {
            printf(FLINT_MAC_ENTRIES_WARNING, 6, fwInfo.fs2_info.guid_num);
        }
    }

    printf("\n");
    return true;
}
#define NA_STR "N/A"
#define BASE_STR "Base"
#define PRINT_FS3_OR_NEWER_UID(uid1, str, printStep, isGuid)             \
    if (uid1.uid)                                                        \
    {                                                                    \
        if (isGuid)                                                      \
        {                                                                \
            printf("%-18s     %016" U64H_FMT_GEN, str, uid1.uid);        \
        }                                                                \
        else                                                             \
        {                                                                \
            printf("%-18s     %012" U64H_FMT_GEN "    ", str, uid1.uid); \
        }                                                                \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        printf("%-18s     %-16s", str, NA_STR);                          \
    }                                                                    \
    if (uid1.num_allocated)                                              \
    {                                                                    \
        printf("        %d", uid1.num_allocated);                        \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        printf("       %s", NA_STR);                                     \
    }                                                                    \
    if (printStep)                                                       \
    {                                                                    \
        if (uid1.step)                                                   \
        {                                                                \
            printf("        %d", uid1.step);                             \
        }                                                                \
        else                                                             \
        {                                                                \
            printf("       %s", NA_STR);                                 \
        }                                                                \
    }                                                                    \
    printf("\n");

#define PRINT_FS4_OR_NEWER_UID(uid1, str, printStep, isGuid)                      \
    if (uid1.uid)                                                                 \
    {                                                                             \
        if (isGuid)                                                               \
        {                                                                         \
            printf("%-18s     %016" U64H_FMT_GEN, str, uid1.uid);                 \
        }                                                                         \
        else                                                                      \
        {                                                                         \
            printf("%-18s     %012" U64H_FMT_GEN "    ", str, uid1.uid);          \
        }                                                                         \
    }                                                                             \
    else                                                                          \
    {                                                                             \
        printf("%-18s     %-16s", str, NA_STR);                                   \
    }                                                                             \
    if (uid1.num_allocated || uid1.num_allocated_msb)                             \
    {                                                                             \
        printf("        %d", uid1.num_allocated + (uid1.num_allocated_msb << 8)); \
    }                                                                             \
    else                                                                          \
    {                                                                             \
        printf("       %s", NA_STR);                                              \
    }                                                                             \
    if (printStep)                                                                \
    {                                                                             \
        if (uid1.step)                                                            \
        {                                                                         \
            printf("        %d", uid1.step);                                      \
        }                                                                         \
        else                                                                      \
        {                                                                         \
            printf("       %s", NA_STR);                                          \
        }                                                                         \
    }                                                                             \
    printf("\n");

static inline void printGuid(const std::string& label, uint64_t guid)
{
    printf("%-18s     %016" U64H_FMT_GEN "\n", label.c_str(), guid);
}

static inline void printPguidGuids(const multi_asic_guids_t* guids)
{
    printGuid("System GUID:", guids->sys_guid);
    printGuid("Node GUID:", guids->node_guid);
    printGuid("Port GUID:", guids->port_guid);
    printGuid("Allocated GUID:", guids->allocated_guid);
}

static inline void
  printFs3OrNewerUids(struct fs3_uid_entry uid, struct fs3_uid_entry orig_uid, string guidMac, bool printStep)
{
    string prefix = BASE_STR + string(" ") + guidMac + ":";
    bool isGuid = guidMac.find("GUID") != string::npos ? true : false;

    PRINT_FS3_OR_NEWER_UID(uid, prefix.c_str(), printStep, isGuid);
    if (uid.uid != orig_uid.uid || uid.num_allocated != orig_uid.num_allocated ||
        (printStep && uid.step != orig_uid.step))
    {
        // Print MFG UIDs as well
        prefix = "Orig " + prefix;
        PRINT_FS3_OR_NEWER_UID(orig_uid, prefix.c_str(), printStep, isGuid);
    }
}

static inline void
  printFs4OrNewerUids(struct fs4_uid_entry uid, struct fs4_uid_entry orig_uid, string guidMac, bool printStep)
{
    string prefix = BASE_STR + string(" ") + guidMac + ":";
    bool isGuid = guidMac.find("GUID") != string::npos ? true : false;

    PRINT_FS4_OR_NEWER_UID(uid, prefix.c_str(), printStep, isGuid);
    if (uid.uid != orig_uid.uid || uid.num_allocated != orig_uid.num_allocated ||
        uid.num_allocated_msb != orig_uid.num_allocated_msb || (printStep && uid.step != orig_uid.step))
    {
        // Print MFG UIDs as well
        prefix = "Orig " + prefix;
        PRINT_FS4_OR_NEWER_UID(orig_uid, prefix.c_str(), printStep, isGuid);
    }
}

bool QuerySubCommand::displayFs3Uids(const fw_info_t& fwInfo, bool isStripedImage)
{
    if (fwInfo.fs3_info.fs3_uids_info.guid_format == IMAGE_LAYOUT_UIDS || isStripedImage)
    {
        // new GUIDs format
        printf("Description:           UID                GuidsNumber\n");
        printFs4OrNewerUids(fwInfo.fs3_info.fs3_uids_info.image_layout_uids.base_guid,
                            fwInfo.fs3_info.orig_fs3_uids_info.image_layout_uids.base_guid, "GUID", false);
        printFs4OrNewerUids(fwInfo.fs3_info.fs3_uids_info.image_layout_uids.base_mac,
                            fwInfo.fs3_info.orig_fs3_uids_info.image_layout_uids.base_mac, "MAC", false);
    }
    else if (fwInfo.fs3_info.fs3_uids_info.guid_format == MULTI_ASIC_GUIDS)
    {
        printFs4OrNewerUids(fwInfo.fs3_info.fs3_uids_info.multi_asic_guids.image_layout_uids.base_guid,
                            fwInfo.fs3_info.orig_fs3_uids_info.multi_asic_guids.image_layout_uids.base_guid, "GUID",
                            false);
        printFs4OrNewerUids(fwInfo.fs3_info.fs3_uids_info.multi_asic_guids.image_layout_uids.base_mac,
                            fwInfo.fs3_info.orig_fs3_uids_info.multi_asic_guids.image_layout_uids.base_mac, "MAC",
                            false);
        printPguidGuids(&fwInfo.fs3_info.fs3_uids_info.multi_asic_guids);
    }
    else
    {
        printf("Description:           UID                GuidsNumber  Step\n");
        string firstGuid = (fwInfo.fw_info.chip_type != CT_SWITCH_IB) ? "GUID1" : "GUID";
        string firstMac = (fwInfo.fw_info.chip_type != CT_SWITCH_IB) ? "MAC1" : "MAC";

        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.guids[0],
                            fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.guids[0], firstGuid, true);
        if (fwInfo.fw_info.chip_type != CT_SWITCH_IB)
        {
            printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.guids[1],
                                fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.guids[1], "GUID2", true);
        }
        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.macs[0],
                            fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.macs[0], firstMac, true);
        if (fwInfo.fw_info.chip_type != CT_SWITCH_IB)
        {
            printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.macs[1],
                                fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.macs[1], "MAC2", true);
        }
    }
    return true;
}

string QuerySubCommand::printSecurityAttrInfo(u_int32_t m)
{
    string attr = "";
    if (m & SMM_SECURE_FW)
    {
        attr += "secure-fw";
    }
    else if (m & SMM_SIGNED_FW)
    {
        attr += "signed-fw";
    }
    else
    {
        attr += NA_STR;
        return attr;
    }
    if (m & SMM_DEBUG_FW)
    {
        attr += ", debug";
    }
    if (m & SMM_DEV_FW)
    {
        attr += ", dev";
    }
    if (m & SMM_CS_TOKEN)
    {
        attr += ", cs-token";
    }
    if (m & SMM_DBG_TOKEN)
    {
        attr += ", dbg-token";
    }
    if (m & SMM_CRYTO_TO_COMMISSIONING)
    {
        attr += ", crypto-to-commissioning";
    }
    if (m & SMM_RMCS_TOKEN)
    {
        attr += ", rmcs-token";
    }
    if (m & SMM_RMDT_TOKEN)
    {
        attr += ", rmdt-token";
    }

    return attr;
}

FlintStatus QuerySubCommand::printImageInfo(const fw_info_t& fwInfo)
{
    bool isFs4 = (fwInfo.fw_type == FIT_FS4 || fwInfo.fw_type == FIT_FS5) ? true : false;
    FwVersion image_version = FwOperations::createFwVersion(&fwInfo.fw_info);
    printf("Image type:            %s\n", fwImgTypeToStr(fwInfo.fw_type));
    if (fwInfo.fw_info.isfu_major)
    {
        printf("FW ISSU Version:       %d\n", fwInfo.fw_info.isfu_major);
    }

    if (image_version.is_set())
    {
        printf("FW Version:            %s\n",
               image_version.get_fw_version(VERSION_FORMAT(fwInfo.fw_info.fw_ver[1])).c_str());
    }

    if (fwInfo.fw_info.fw_rel_date[0] || fwInfo.fw_info.fw_rel_date[1] || fwInfo.fw_info.fw_rel_date[2])
    {
        printf("FW Release Date:       %x.%x.%x\n", fwInfo.fw_info.fw_rel_date[0], fwInfo.fw_info.fw_rel_date[1],
               fwInfo.fw_info.fw_rel_date[2]);
    }
    if (fwInfo.fw_info.min_fit_ver[0] || fwInfo.fw_info.min_fit_ver[1] || fwInfo.fw_info.min_fit_ver[2] ||
        fwInfo.fw_info.min_fit_ver[3])
    {
        printf("Min FIT Version:       %d.%d.%d.%d\n", fwInfo.fw_info.min_fit_ver[0], fwInfo.fw_info.min_fit_ver[1],
               fwInfo.fw_info.min_fit_ver[2], fwInfo.fw_info.min_fit_ver[3]);
    }
    if ((fwInfo.fw_info.mic_ver[0] || fwInfo.fw_info.mic_ver[1] || fwInfo.fw_info.mic_ver[2]))
    {
        printf("MIC Version:           %d.%d.%d\n", fwInfo.fw_info.mic_ver[0], fwInfo.fw_info.mic_ver[1],
               fwInfo.fw_info.mic_ver[2]);
    }
    if (strlen(fwInfo.fw_info.product_ver))
    {
        printf("Product Version:       %s\n", fwInfo.fw_info.product_ver);
    }
    if (fwInfo.fw_info.roms_info.exp_rom_found)
    {
        displayExpRomInfo(fwInfo.fw_info.roms_info, "Rom Info:              ");
    }
    char* imageVSD = (char*)fwInfo.fs3_info.image_vsd;
    char* deviceVSD = NULL;
    if (isFs4)
    {
        deviceVSD = (char*)fwInfo.fs3_info.deviceVsd;
    }
    else
    {
        deviceVSD = (char*)fwInfo.fw_info.vsd;
    }

    if (strlen(imageVSD) == 0)
    {
        if (deviceVSD == NULL || strlen(deviceVSD) == 0)
        {
            imageVSD = (char*)NA_STR;
        }
        else
        {
            imageVSD = deviceVSD;
        }
    }
    printf("Image VSD:             %s\n", imageVSD);
    printf("PSID:                  %s\n", fwInfo.fw_info.psid);
    printf("Security Attributes:   %s\n", printSecurityAttrInfo(fwInfo.fs3_info.security_mode).c_str());

    if (isFs4)
    { // Security Version is supported in Connectx-6dx and up
        printf("Security Ver:          %d\n", fwInfo.fs3_info.image_security_version);
    }

    string updateMethod = "Legacy";
    if (fwInfo.fs3_info.security_mode & SMM_MCC_EN)
    {
        updateMethod = "fw_ctrl";
    }
    printf("Default Update Method: %s\n", updateMethod.c_str());
    return FLINT_SUCCESS;
}

void QuerySubCommand::PrintLifeCycle(const life_cycle_t& lifeCycle)
{
    try
    {
        string lifeCycleString = "";
        if (lifeCycle.version_field == 0)
        {
            lifeCycleString = life_cycle_fs4_strings.at(static_cast<LifeCycleFS4>(lifeCycle.value));
        }
        else
        {
            lifeCycleString = life_cycle_fs5_strings.at(static_cast<LifeCycleFS5>(lifeCycle.value));
        }
        printf("Life cycle:            %s\n", lifeCycleString.c_str());
    }
    catch (const std::out_of_range& e)
    {
        reportErr(true, "The life cycle value is out of range: %u\n", lifeCycle.value);
    }
}

bool HwSubCommand::PrintWriteProtectedBits(const ext_flash_attr_t& attr)
{
    int flash_index = 0;
    int rc = attr.mf_get_write_protect_rc_array[flash_index];
    bool ret_val = true;
    write_protect_info_t protect_info = attr.protect_info_array[flash_index];
    if (rc == MFE_OK)
    {
        std::bitset<BP_SIZE> bp_bits(protect_info.bp_val); // convert bp_val to binary
        string tbs_bit = (protect_info.tbs_bit ? "1" : "0");
        int msb = BP_SIZE - 1;
        std::cout << "  TBS, BP[" << msb << ":0]            " << tbs_bit << ", " << bp_bits << endl;
    }
    else
    {
        if (rc != MFE_NOT_SUPPORTED_OPERATION)
        {
            ret_val = false;
        }
    }
    return ret_val;
}

bool HwSubCommand::FillAttrIfNeeded(ext_flash_attr_t& attr, char* param_val_str, char* param_name)
{
    bool rc = true;

    std::string param_name_str(param_name);
    if (param_name_str.find(WRITE_PROTECT) != std::string::npos) // making sure this is a hw set WRITE_PROTECT command
    {
        char *tb, *num_str, *sec;
        char* param_val_str_copy = new char[strlen(param_val_str) + 1];
        strcpy(param_val_str_copy,
               param_val_str); // copying param_val_str so it won't be corrupted by strtok and could be used later on

        tb = strtok(param_val_str_copy, ",");
        num_str = strtok((char*)NULL, "-");
        sec = strtok((char*)NULL, "");
        if (tb == NULL || num_str == NULL || sec == NULL) // we only want to set TBS so we need to initialize get_attr
        {                                                 // which will be needed to get existing write protect data

            attr.type_str = (char*)NULL;
            if (!((Flash*)_io)->get_attr(attr))
            {
                reportErr(true, FLINT_HW_COMMAND_ERROR, "set", _io->err());
                if (attr.type_str)
                {
                    delete[] attr.type_str;
                }
                rc = false;
            }
        }

        delete[] param_val_str_copy;
    }

    return rc;
}

FlintStatus QuerySubCommand::printInfo(const fw_info_t& fwInfo, bool fullQuery)
{
    DPRINTF(("QuerySubCommand::printInfo fullQuery=%d\n", fullQuery));
    bool isFs2 = (fwInfo.fw_type == FIT_FS2) ? true : false;
    bool isFs3 = (fwInfo.fw_type == FIT_FS3) ? true : false;
    bool isFs4 = (fwInfo.fw_type == FIT_FS4 || fwInfo.fw_type == FIT_FS5) ? true : false;
    bool isFsCtrl = (fwInfo.fw_type == FIT_FSCTRL) ? true : false;
    FwOperations* ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    FwVersion image_version = FwOperations::createFwVersion(&fwInfo.fw_info);
    FwVersion running_version = FwOperations::createRunningFwVersion(&fwInfo.fw_info);
    bool isStripedImage = ops->GetIsReducedImage();

    printf("Image type:            %s\n", fwImgTypeToStr(fwInfo.fw_type));
    if (fwInfo.fw_info.isfu_major)
    {
        printf("FW ISSU Version:       %d\n", fwInfo.fw_info.isfu_major);
    }

    if (image_version.is_set())
    {
        printf("FW Version:            %s\n",
               image_version.get_fw_version(VERSION_FORMAT(fwInfo.fw_info.fw_ver[1])).c_str());
        if (nextBootFwVer)
        {
            // if nextBootFwVer is true, no need to print all the other values.
            return FLINT_SUCCESS;
        }
        if (image_version != running_version && running_version.is_set())
        {
            printf("FW Version(Running):   %s\n",
                   running_version.get_fw_version(VERSION_FORMAT(fwInfo.fw_info.running_fw_ver[1])).c_str());
        }
    }
    else if (nextBootFwVer)
    {
        if (_flintParams.device_specified)
        {
            mfile* mf = _fwOps->getMfileObj();
            if (mf != NULL)
            {
                if ((mf->flags & MDEVS_IB) == 0)
                { // not IB device
                    // if nextBootFwVer is true, and no next boot fw version, print running version (this version is
                    // next_boot_fw_ver as well)
                    printf("FW Version:            %s\n",
                           running_version.get_fw_version(VERSION_FORMAT(fwInfo.fw_info.running_fw_ver[1])).c_str());
                }
            }
        }
        return FLINT_SUCCESS;
    }

    if (fwInfo.fw_info.fw_rel_date[0] || fwInfo.fw_info.fw_rel_date[1] || fwInfo.fw_info.fw_rel_date[2])
    {
        printf("FW Release Date:       %x.%x.%x\n", fwInfo.fw_info.fw_rel_date[0], fwInfo.fw_info.fw_rel_date[1],
               fwInfo.fw_info.fw_rel_date[2]);
    }
    if (fullQuery)
    {
        // there is no full query atm just quick query
        if (fwInfo.fw_info.min_fit_ver[0] || fwInfo.fw_info.min_fit_ver[1] || fwInfo.fw_info.min_fit_ver[2] ||
            fwInfo.fw_info.min_fit_ver[3])
        {
            printf("Min FIT Version:       %d.%d.%d.%d\n", fwInfo.fw_info.min_fit_ver[0], fwInfo.fw_info.min_fit_ver[1],
                   fwInfo.fw_info.min_fit_ver[2], fwInfo.fw_info.min_fit_ver[3]);
        }
        if ((fwInfo.fw_info.mic_ver[0] || fwInfo.fw_info.mic_ver[1] || fwInfo.fw_info.mic_ver[2]))
        {
            printf("MIC Version:           %d.%d.%d\n", fwInfo.fw_info.mic_ver[0], fwInfo.fw_info.mic_ver[1],
                   fwInfo.fw_info.mic_ver[2]);
        }
        if (isFs2)
        {
            if (fwInfo.fs2_info.config_sectors)
            {
                printf("Config Sectors:        %d\n", fwInfo.fs2_info.config_sectors);
            }
            if (fwInfo.fs2_info.config_pad)
            {
                printf("Config Pad:            %d\n", fwInfo.fs2_info.config_pad);
            }
            if (strlen(fwInfo.fs2_info.prs_name))
            {
                printf("PRS Name:              %s\n", fwInfo.fs2_info.prs_name);
            }
        }
        else
        {
            // FS3
            if (strlen(fwInfo.fs3_info.prs_name))
            {
                printf("PRS Name:              %s\n", fwInfo.fs3_info.prs_name);
            }
            if (strlen(fwInfo.fs3_info.orig_prs_name))
            {
                printf("Orig PRS Name:         %s\n", fwInfo.fs3_info.orig_prs_name);
            }
            if (strlen(fwInfo.fs3_info.name))
            {
                printf("Part Number:           %s\n", fwInfo.fs3_info.name);
            }
            if (strlen(fwInfo.fs3_info.description))
            {
                printf("Description:           %s\n", fwInfo.fs3_info.description);
            }
        }
    }

    if (strlen(fwInfo.fw_info.product_ver))
    {
        printf("Product Version:       %s\n", fwInfo.fw_info.product_ver);
    }
    if (fwInfo.fw_info.roms_info.exp_rom_found)
    {
        displayExpRomInfo(fwInfo.fw_info.roms_info, "Rom Info:              ");
    }
    else if (_flintParams.skip_rom_query)
    {
        printf("Rom Info:              type=UEFI version=skipped cpu=skipped\n");
        printf("                       type=PXE  version=skipped devid=skipped cpu=skipped\n");
        printf("                       type=NVMe version=skipped devid=skipped cpu=skipped\n");
    }
    if (isFs2)
    {
        printf("Device ID:             %d\n", fwInfo.fw_info.dev_type);
    }

    if (isFs2 && fwInfo.fs2_info.access_key_exists)
    {
        printf("HW Access Key:         ");
        if (fwInfo.fs2_info.access_key_value.l || fwInfo.fs2_info.access_key_value.h)
        {
            printf("Enabled\n");
        }
        else
        {
            printf("Disabled\n");
        }
    }

    if (!isFs2)
    {
        /*i.e its fs3/fs4*/
        if (!displayFs3Uids(fwInfo, isStripedImage))
        {
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!displayFs2Uids(fwInfo))
        {
            return FLINT_FAILED;
        }
    }

    // VSD, PSID
    if (!fwInfo.fw_info.vsd_vendor_id || fwInfo.fw_info.vsd_vendor_id == MELLANOX_VENDOR_ID)
    {
        if (!isFs2)
        {
            char* imageVSD = (char*)fwInfo.fs3_info.image_vsd;
            char* deviceVSD = NULL;

            if (_flintParams.device_specified == false && _flintParams.image_specified == true)
            {
                // we're making query on BIN file only
                deviceVSD = (char*)fwInfo.fw_info.vsd;
            }
            else if (isFs4 && !_flintParams.no_fw_ctrl && !_flintParams.override_cache_replacement)
            {
                deviceVSD = (char*)fwInfo.fs3_info.deviceVsd;
            }
            else
            {
                deviceVSD = (char*)fwInfo.fw_info.vsd;
            }
            if (strlen(imageVSD) == 0)
            {
                imageVSD = (char*)NA_STR;
            }
            if (strlen(deviceVSD) == 0)
            {
                deviceVSD = (char*)NA_STR;
            }
            printf("Image VSD:             %s\n", imageVSD);
            printf("Device VSD:            %s\n", deviceVSD);
            printf("PSID:                  %s\n", fwInfo.fw_info.psid);
            if (!isStripedImage && strncmp(fwInfo.fw_info.psid, fwInfo.fs3_info.orig_psid, 13) != 0)
            {
                if (strlen(fwInfo.fs3_info.orig_psid))
                {
                    printf("Orig PSID:             %s\n", fwInfo.fs3_info.orig_psid);
                }
                else
                {
                    printf("Orig PSID:             %s\n", NA_STR);
                }
            }
        }
        else
        {
            printf("VSD:                   %s\n", fwInfo.fw_info.vsd);
            printf("PSID:                  %s\n", fwInfo.fw_info.psid);
        }
    }
    else
    {
        printf(FLINT_NOT_MLNX_FW_WARNING, fwInfo.fw_info.vsd_vendor_id);
    }

    if (isFs3 || isFs4 || isFsCtrl)
    {
        printf("Security Attributes:   %s\n", printSecurityAttrInfo(fwInfo.fs3_info.security_mode).c_str());
    }

    if (isFs4 && _flintParams.image_specified)
    { // Security Version is supported in Connectx-6dx and up
        printf("Security Ver:          %d\n", fwInfo.fs3_info.image_security_version);
    }

    if ((isFs3 || isFs4 || isFsCtrl) && fullQuery)
    {
        string updateMethod = "Legacy";
        if (fwInfo.fs3_info.security_mode & SMM_MCC_EN)
        {
            updateMethod = "fw_ctrl";
        }
        printf("Default Update Method: %s\n", updateMethod.c_str());
    }

    if (fullQuery && _flintParams.device_specified)
    {
        if (ops->IsFsCtrlOperations())
        { // working only on devices with FW control
            if (ops->IsLifeCycleSupported())
            { // from CX6 and above
                PrintLifeCycle(fwInfo.fs3_info.life_cycle);
            }
            if (ops->IsSecureBootSupported())
            { // from CX6DX and above
                printf("Secure Boot Capable:   %s\n", fwInfo.fs3_info.sec_boot == 1 ? "Enabled" : "Disabled");

                if (fwInfo.fs3_info.device_security_version_access_method == MFSV)
                {
                    printf("EFUSE Security Ver:    %d\n", fwInfo.fs3_info.device_security_version_mfsv.efuses_sec_ver);
                    printf("Image Security Ver:    %d\n", fwInfo.fs3_info.device_security_version_mfsv.img_sec_ver);

                    string efuses_programming_info;
                    if (fwInfo.fs3_info.device_security_version_mfsv.efuses_prog_method == 0)
                    {
                        if (fwInfo.fs3_info.device_security_version_mfsv.efuses_prog_en == 0)
                        {
                            efuses_programming_info = "Manually ; Disabled"; // disabled
                        }
                        else
                        {
                            efuses_programming_info = "Manually ; Enabled"; // next boot only
                        }
                    }
                    else
                    {
                        efuses_programming_info = "Automatically"; // every boot
                    }
                    printf("Security Ver Program:  %s\n", efuses_programming_info.c_str());
                }

                if (ops->IsEncryptionSupported())
                {
                    printf("Encryption:            %s\n", fwInfo.fs3_info.encryption == 1 ? "Enabled" : "Disabled");
                }
            }
        }
        else
        { // No fw control
            if (ops->IsSecureBootSupported())
            { // CX6DX onwards
                if (ops->IsLifeCycleAccessible(fwInfo.fw_info.chip_type))
                {
                    printf("Image Boot Status:     %d\n", fwInfo.fs3_info.global_image_status);
                    PrintLifeCycle(fwInfo.fs3_info.life_cycle);
                    if (fwInfo.fs3_info.life_cycle.version_field == 0 &&
                        CRSpaceRegisters::IsLifeCycleSecured(fwInfo.fs3_info.life_cycle))
                    {
                        if (fwInfo.fs3_info.device_security_version_access_method == DIRECT_ACCESS)
                        {
                            printf("EFUSE Security Ver:    %d\n", fwInfo.fs3_info.device_security_version_gw);
                        }
                        printf("Image Security Ver:    %d\n", fwInfo.fs3_info.image_security_version);
                    }
                }
            }
        }
    }

    if (isFs2 && fwInfo.fs2_info.blank_guids)
    {
        // blankGuids only exsists in FS2 image type in mlxfwops why?
        printf(FLINT_BLANK_GUIDS_WARNING);
    }

    if (fwInfo.fs3_info.ini_file_version)
    {
        printf("INI revision:          0x%x\n", fwInfo.fs3_info.ini_file_version);
    }

    if (fwInfo.fs3_info.geo_address_valid)
    {
        printf("Geographical Address:  ASIC %x\n", fwInfo.fs3_info.geo_address);
    }

    if (fwInfo.fs3_info.socket_direct)
    {
        printf("Socket Direct:         Yes\n");
        if (fwInfo.fs3_info.is_aux_card_connected_valid)
        {
            if (fwInfo.fs3_info.aux_card_connected)
            {
                printf("Aux Card is Connected: Yes\n");
            }
            else
            {
                printf("Aux Card is Connected: No\n");
            }
        }
    }

    if (fwInfo.fs3_info.independent_module)
    {
        std::string independent_module_str = "";
        if (fwInfo.fs3_info.independent_module != 1 && fwInfo.fs3_info.independent_module != 2)
        {
            independent_module_str = "Unknown";
        }
        else
        {
            independent_module_str =
              fwInfo.fs3_info.independent_module == 1 ? "Independent Mode Supported" : "Standalone Mode Supported";
        }

        printf("Independent Module:    %s\n", independent_module_str.c_str());
    }

    if (fwInfo.fs3_info.pci_switch_only_mode_valid)
    {
        std::string switch_mode_only = fwInfo.fs3_info.pci_switch_only_mode ? "Enabled" : "Disabled";
        printf("PCIe switch mode only: %s\n", switch_mode_only.c_str());
    }

    return FLINT_SUCCESS;
}

QuerySubCommand::QuerySubCommand()
{
    _name = "query";
    _desc = "Query misc. flash/firmware characteristics, use \"full\" to get more information.";
    _extendedDesc = "Query miscellaneous FW and flash parameters \n"
                    "Display FW Version, GUIDs, PSID, and other info";
    _flagLong = "query";
    _flagShort = "q";
    _param = "[full]";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " query";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Query;
    _mccSupported = true;
}

QuerySubCommand::~QuerySubCommand() {}

FlintStatus QuerySubCommand::queryMFA2()
{
#ifndef NO_MSTARCHIVE
    if (_flintParams.use_psid == false)
    {
        reportErr(true, "Must supply \"--psid\" flag while querying MFA2 archive\n");
        return FLINT_FAILED;
    }
    char* psid = (char*)_flintParams.psid.c_str();
    u_int16_t fw_ver[3];
    fw_ver[0] = 0xff;
    fw_ver[1] = 0xff;
    fw_ver[2] = 0xffff;
    map_string_to_component matchingComponentsMap = _mfa2Pkg->getMatchingComponents(psid, fw_ver);
    u_int32_t matchingSize = matchingComponentsMap.size();
    if (matchingSize == 0)
    {
        reportErr(true, "No matching binaries found for MFA2 %s\n", _flintParams.image.c_str());
        return FLINT_FAILED;
    }
    else
    {
        int i = 1;
        u_int8_t fs4_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0xAB, 0xCD, 0xEF, 0x00,
                                          0xFA, 0xDE, 0x12, 0x34, 0x56, 0x78, 0xDE, 0xAD};
        u_int8_t fs3_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0x8C, 0xDF, 0xD0, 0x00,
                                          0xDE, 0xAD, 0x92, 0x70, 0x41, 0x54, 0xBE, 0xEF};
        map_string_to_component::iterator it = matchingComponentsMap.begin();
        printf("\n*******************************\n");
        for (u_int32_t index = 0; index < matchingSize && it != matchingComponentsMap.end(); index++, it++)
        {
            const ComponentDescriptor& compDescr = it->second.getComponentDescriptor();
            u_int8_t deviceMajorVer = compDescr.getVersionExtension().getMajor();
            vector<u_int8_t> componentBuffer;
            _mfa2Pkg->unzipComponent(matchingComponentsMap, index, componentBuffer);
            char errBuff[ERR_BUFF_SIZE] = {0};
            string fileName = "/tmp/temp.bin"; // Get temp name
            if (deviceMajorVer >= 16)
            {
                for (u_int8_t i = 0; i < sizeof(fs4_image_signature); i++)
                {
                    componentBuffer[i] = fs4_image_signature[i];
                }
            }
            else
            {
                for (u_int8_t i = 0; i < sizeof(fs3_image_signature); i++)
                {
                    componentBuffer[i] = fs3_image_signature[i];
                }
            }
            writeImageToFile(fileName.c_str(), componentBuffer.data(), componentBuffer.size());
            _flintParams.image_specified = true;
            _flintParams.image = fileName;
            _imgOps = FwOperations::FwOperationsCreate((void*)_flintParams.image.c_str(), NULL, NULL, FHT_FW_FILE,
                                                       errBuff, ERR_BUFF_SIZE, _flintParams.ignore_crc_check);
            fw_info_t fwInfo;
            if (!_imgOps->FwQuery(&fwInfo, true, false, true, true))
            {
                reportErr(true, FLINT_FAILED_QUERY_ERROR, "image", _flintParams.image.c_str(), _imgOps->err());
                return FLINT_FAILED;
            }
            printf("Component %d\n", i++);
            if (printImageInfo(fwInfo) == FLINT_FAILED)
            {
                return FLINT_FAILED;
            }
            printf("*******************************\n");
        }
    }
#endif
    return FLINT_SUCCESS;
}

#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
FlintStatus QuerySubCommand::QueryCableAttributes()
{
    DPRINTF(("QuerySubCommand::QueryCableAttributes\n"));

    try
    {
        FwManagementCdbCommander cableCommander(_flintParams.device.c_str());
        cout << cableCommander.GetCmisFWIndicationStrings();
    }
    catch (const std::exception& e)
    {
        reportErr(true, "FW Info query failed, %s\n", e.what());
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}
#endif

FlintStatus QuerySubCommand::executeCommand()
{
    DPRINTF(("QuerySubCommand::executeCommand\n"));

    if (_flintParams.linkx_control == true)
    {
        if (_flintParams.device_specified == false)
        {
            reportErr(true, FLINT_NO_DEVICE_ERROR);
            return FLINT_FAILED;
        }
        if (_flintParams.downstream_device_ids.size() == 0)
        {
            reportErr(true, "Flag \"--downstream_device_ids\" with values should be provided.\n");
            return FLINT_FAILED;
        }
        return QueryLinkX(_flintParams.device, _flintParams.output_file, _flintParams.downstream_device_ids);
    }
    if (_flintParams.device.find("_cable") != string::npos && _flintParams.device.find("_rt") == string::npos)
    {
        FlintStatus rc = FLINT_SUCCESS;
#if defined(CABLES_SUPPORT) && !defined(MST_CPU_armv7l_umbriel)
        rc = QueryCableAttributes();
#else
        reportErr(true, "Query on cable devices is not supported.\n");
        rc = FLINT_FAILED;
#endif

        return rc;
    }
    if (_flintParams.image_specified)
    {
#ifndef NO_MSTARCHIVE
        string mfa2file = _flintParams.image;
        _mfa2Pkg = MFA2::LoadMFA2Package(mfa2file);
        if (_mfa2Pkg != NULL)
        {
            _flintParams.mfa2_specified = true;
            return queryMFA2();
        }
#endif
    }
    if (_flintParams.low_cpu)
    {
        set_increase_poll_time(1);
    }
    if (_flintParams.next_boot_fw_ver)
    {
        nextBootFwVer = true;
    }
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    if (_flintParams.image_specified && _imgOps->FwType() == FIT_PLDM_1_0)
    {
        u_int8_t* buff;
        u_int32_t buffSize = 0;
        FsPldmOperations* pldmOps = dynamic_cast<FsPldmOperations*>(_imgOps);

        if (!pldmOps->LoadPldmPackage())
        {
            reportErr(true, "Failed to load PLDM package.\n");
            return FLINT_FAILED;
        }

        std::string componentType("FW");
        if (!pldmOps->GetPldmComponentData(componentType, _flintParams.psid, &buff, buffSize))
        {
            if (pldmOps->err())
            {
                reportErr(true, "%s\n", pldmOps->err());
            }
            else
            {
                reportErr(true, "The component was not found in the PLDM.\n");
            }
            return FLINT_FAILED;
        }

        u_int16_t swDevId = 0;
        if (!pldmOps->GetPldmDescriptor(_flintParams.psid, DEV_ID_TYPE, swDevId))
        {
            reportErr(true, "DEVICE ID descriptor is not found in the PLDM.\n");
            delete[] buff;
            return FLINT_FAILED;
        }
        FwOperations* newImageOps = NULL;
        pldmOps->CreateFwOpsImage((u_int32_t*)buff, buffSize, &newImageOps, swDevId, true);
        delete _imgOps;
        _imgOps = newImageOps;
        delete[] buff;

        _flintParams.striped_image = true;
    }

    fw_info_t fwInfo;
    FwOperations* ops;
    bool fullQuery = false;
    // check on what we are working
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    if (!ops->FwQuery(&fwInfo, !_flintParams.skip_rom_query, _flintParams.striped_image))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, _flintParams.device_specified ? "Device" : "image",
                  _flintParams.device_specified ? _flintParams.device.c_str() : _flintParams.image.c_str(), ops->err());
        return FLINT_FAILED;
    }

    if (ops->FwType() == FIT_COMPS)
    {
        ops->PrintQuery();
        return FLINT_SUCCESS;
    }

    // print fw_info nicely to the user
    // we actually dont use "regular" query , just quick
    // ORENK - no use to display quick query message to the user if we dont do it in any other way
    if (_flintParams.cmd_params.size() == 1)
    {
        fullQuery = true;
    }
    FlintStatus queryResult = printInfo(fwInfo, fullQuery);
    return queryResult;
}

/***********************
 * Class: QueryComponentSubCommand
 **********************/

QueryComponentSubCommand::QueryComponentSubCommand()
{
    _name = "query components";
    _desc = "Queries components on a given device via FW.";
    _extendedDesc = "";
    _flagLong = "query_components";
    _flagShort = "qc";
    _param = "";
    _paramExp = "None";
    _example =  FLINT_NAME " -d /dev/mst/mt53100_pciconf0 --component_type sync_clock query_components\n" FLINT_NAME
                           " -d /dev/mst/mt53100_pciconf0 --component_type dpa_component query_components\n"
                 " -d /dev/mst/mt4129_pciconf1 --component_type digital_cacert query_components /tmp/outfile\n";
    _v = Wtv_Dev;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 0;
    _cmdType = SC_Query_Components;
    _mccSupported = true;
}

QueryComponentSubCommand::~QueryComponentSubCommand() {}

FlintStatus QueryComponentSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_fwOps->IsFsCtrlOperations())
    {
        FlintStatus rc = FLINT_SUCCESS;
        switch (_comp)
        {
            case FwComponent::COMPID_CLOCK_SYNC_EEPROM:
                rc = querySyncE();
                break;
            case FwComponent::DIGITAL_CACERT:
                rc = QueryCertStatus();
                break;
            #if ENABLE_DPA
            case FwComponent::DPA_COMPONENT:
                rc = QueryDpaApps();
                break;
            #endif
            case FwComponent::COMPID_UNKNOWN:
            default:
                reportErr(true, "Unknown component type given.\n");
                return FLINT_FAILED;
        }
        if (rc != FLINT_SUCCESS)
        {
            return rc;
        }
    }
    else
    {
        reportErr(true, "Command is not supported in the current state of this device.\n");
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}

bool QueryComponentSubCommand::verifyParams()
{
    _comp = FwComponent::getCompId(_flintParams.component_type);
    if (_flintParams.component_type.empty())
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"--component_type\"");
        return false;
    }
    if (_comp == FwComponent::DIGITAL_CACERT && _flintParams.cmd_params.size() == 1 && _flintParams.cert_uuid.empty())
    {
        reportErr(true, "For query_components with specific output file, Please specify cert_uuid.\n");
        return false;
    }
    return true;
}

FlintStatus QueryComponentSubCommand::querySyncE()
{
    vector<u_int8_t> firstDeviceData, secondDeviceData;

    if (!_fwOps->QueryComponentData(FwComponent::COMPID_CLOCK_SYNC_EEPROM, 1, firstDeviceData))
    {
        reportErr(true, "%s\n", _fwOps->err());
        return FLINT_FAILED;
    }
    if (!_fwOps->QueryComponentData(FwComponent::COMPID_CLOCK_SYNC_EEPROM, 2, secondDeviceData))
    {
        reportErr(true, "%s\n", _fwOps->err());
        return FLINT_FAILED;
    }

    if (firstDeviceData.empty() && secondDeviceData.empty())
    {
        reportErr(true, "failed getting info from the device.\n");
        return FLINT_FAILED;
    }

    FsSyncEOperations::PrintComponentData(firstDeviceData, 1);
    FsSyncEOperations::PrintComponentData(secondDeviceData, 2);

    return FLINT_SUCCESS;
}

FlintStatus QueryComponentSubCommand::QueryDpaApps()
{
#if ENABLE_DPA
#ifndef MST_CPU_armv7l_umbriel // {

    vector<u_int8_t> dpaAppsRawData;
    u_int32_t dpaAppIndex = 0;
    if (!_fwOps->QueryComponentData(FwComponent::DPA_COMPONENT, dpaAppIndex, dpaAppsRawData))
    {
        reportErr(true, "Failed to query DPA component data.\n");
        return FLINT_FAILED;
    }
    unique_ptr<FsDpaAppOperations> FsDpaAppOps(new FsDpaAppOperations(dpaAppsRawData));

    if (!FsDpaAppOps->PrintQuery())
    {
        reportErr(true, "%s\n", FsDpaAppOps->err());
        return FLINT_FAILED;
    }

#endif // } MST_CPU_armv7l_umbriel
#else
    reportErr(true, "DPA support is not enabled in this build.\n");
    return FLINT_FAILED;
#endif // ENABLE_DPA
    return FLINT_SUCCESS;
}

FlintStatus QueryComponentSubCommand::QueryCertStatus()
{
#if ENABLE_DPA
    vector<u_int8_t> cacertRawData;
    if (!_fwOps->ReadMccComponent(cacertRawData, FwComponent::DIGITAL_CACERT))
    {
        reportErr(true, "Failed to read cacert.\n");
        return FLINT_FAILED;
    }

    unique_ptr<FsCertOperations> FsCertOps(new FsCertOperations(cacertRawData));

    string certUuid;
    copy_if(_flintParams.cert_uuid.begin(), _flintParams.cert_uuid.end(), std::back_inserter(certUuid),
            [](char ch) { return ch != '-'; });

    string outputFile = _flintParams.cmd_params.size() ? _flintParams.cmd_params[0] : "";
    if (!FsCertOps->GetCert(certUuid, outputFile))
    {
        reportErr(true, "%s\n", FsCertOps->err());
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
#else
    reportErr(true, "QueryCertStatus for DPA is not supported.\n");
    return FLINT_FAILED;
#endif
}


/***********************
 * Class: ImageReactivationSubCommand
 ***********************/
ImageReactivationSubCommand::ImageReactivationSubCommand()
{
    _name = "image_reactivation";
    _desc = "Reactivate previous flash image. For FW controlled devices only.";
    _extendedDesc = "Reactivate previous flash image by moving the magic pattern.";
    _flagLong = "image_reactivate";
    _flagShort = "ir";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " image_reactivate";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_Image_Reactivation;
    _mccSupported = true;
}

bool ImageReactivationSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (_flintParams.no_fw_ctrl)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_CMD_ERROR, "-no_fw_ctrl", "image_reactivation");
        return false;
    }

    if (_flintParams.override_cache_replacement)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_CMD_ERROR, "-ocr", "image_reactivation");
        return false;
    }

    return true;
}

ImageReactivationSubCommand::~ImageReactivationSubCommand() {}

FlintStatus ImageReactivationSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    fw_info_t fwInfo;
    FwOperations* ops = _fwOps;
    if (!ops->FwQuery(&fwInfo))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), ops->err());
        return FLINT_FAILED;
    }
    if (!_fwOps->FwReactivateImage())
    {
        reportErr(true, FLINT_FAILED_IMAGE_REACTIVATION_ERROR, _flintParams.device.c_str(), ops->err());
        return FLINT_FAILED;
    }
    printf("\n-I- FW Image Reactivation succeeded.\n\n");
    return FLINT_SUCCESS;
}
/***********************
 * Class: VerifySubCommand
 ***********************/
VerifySubCommand::VerifySubCommand()
{
    _name = "verify";
    _desc = "Verify entire flash, use \"showitoc\" to see ITOC headers in FS3/FS4 image only.";
    _extendedDesc = "Verify entire flash.";
    _flagLong = "verify";
    _flagShort = "v";
    _param = "[showitoc]";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " v";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Verify;
}

VerifySubCommand::~VerifySubCommand() {}

bool VerifySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "showitoc")
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "showitoc");
        return false;
    }

    return true;
}

FlintStatus VerifySubCommand::executeCommand()
{
    if (_flintParams.image_specified == true && _flintParams.device_specified == true)
    {
        // Verify based on binary compare
        BinaryCompareSubCommand bc;
        _flintParams.silent = true;
        bc.setParams(_flintParams);
        FlintStatus bc_res = bc.executeCommand();
        if (bc_res == FLINT_SUCCESS)
        {
            printf("\n-I- FW image verification succeeded. Image is bootable.\n\n");
        }
        else
        {
            reportErr(true, FLINT_CMD_VERIFY_ERROR_2);
        }
        return bc_res;
    }

    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    FwOperations* ops;
    bool showItoc = (_flintParams.cmd_params.size() == 1) ? true : false;
    // check on what we are wroking
    int opaque = 0;
    ProgressCallBackAdvSt advProgress;
    advProgress.func = (f_prog_func_adv)&advProgressFunc;
    advProgress.opaque = &opaque;
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    FwOperations::ExtVerifyParams verifyParams(&verifyCbFunc);
    verifyParams.isStripedImage = _flintParams.striped_image;
    verifyParams.showItoc = showItoc;
    verifyParams.progressFuncAdv = &advProgress;
    if (!ops->FwVerifyAdv(verifyParams))
    {
        reportErr(true, FLINT_CMD_VERIFY_ERROR, ops->err());
        return FLINT_FAILED;
    }
    // get status of blank guids in fs2 only can either bring from FwVerify as another parameter. ask mohammad
    if (ops->FwType() == FIT_FS2)
    {
        fw_info_t fwInfo;
        if (!ops->FwQuery(&fwInfo, true, _flintParams.striped_image))
        {
            printf("\n\n");
            reportErr(true, "Failed to get Guids status. %s\n", ops->err());
            return FLINT_FAILED;
        }
        if (fwInfo.fs2_info.blank_guids)
        {
            printf("\n\n");
            reportErr(true, FLINT_CMD_VERIFY_ERROR, "BLANK GUIDS");
            return FLINT_FAILED;
        }
    }
    printf("\n-I- FW image verification succeeded. Image is bootable.\n\n");
    return FLINT_SUCCESS;
}

/***********************
 * Class: SwResetSubCommand
 **********************/
SwResetSubCommand::SwResetSubCommand()
{
    _name = "swreset";
    _desc = "SW reset the target switch device."
            "This command is supported only in the In-Band access method.";
    _extendedDesc = "SW reset the target switch device. This command is supported only in the In-Band"
                    " access method.";
    _flagLong = "swreset";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = "None";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_Swreset;
}

SwResetSubCommand::~SwResetSubCommand() {}

bool SwResetSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus SwResetSubCommand::executeCommand()
{
    mfile* mf = NULL;
    dm_dev_id_t devid_type;
    u_int32_t devid, revid;

    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    mf = _fwOps->getMfileObj();
    int rc = dm_get_device_id(mf, &devid_type, &devid, &revid);
    if (rc != 0)
    {
        reportErr(true, "can't get device Id.\n");
        return FLINT_FAILED;
    }
    (void)devid;
    (void)revid;

    if (!IsDeviceSupported(devid_type))
    {
        return FLINT_FAILED;
    }

    printf("-I- Sending reset command to device %s ...\n", _flintParams.device.c_str());
    if (!_fwOps->FwSwReset())
    {
        reportErr(true, FLINT_SWRESET_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf("-I- Reset command accepted by the device.\n");

    return FLINT_SUCCESS;
}

bool SwResetSubCommand::IsDeviceSupported(dm_dev_id_t dev_id)
{
    if (dm_dev_is_ib_switch(dev_id))
    {
        return true;
    }

    reportErr(true, "Device %s doesn't support swreset command.\n", dm_dev_type2str(dev_id));
    return false;
}

/***********************
 * Class: BromSubCommand
 **********************/
BromSubCommand::BromSubCommand()
{
    _name = "brom";
    _desc = "Burn the specified ROM file on the flash.";
    _extendedDesc = "Burn the specified exp-ROM on the flash.";
    _flagLong = "brom";
    _flagShort = "";
    _param = "<ROM-file>";
    _paramExp = "file: The exp-ROM file.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " brom exp-rom.rom";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Brom;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    memset(&_info, 0, sizeof(_info));
    memset(&_romsInfo, 0, sizeof(_romsInfo));
}

BromSubCommand::~BromSubCommand()
{
    closeLog();
    _fRom.close();
}

FlintStatus BromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    // query device
    if (!ops->FwQuery(&_info))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(), ops->err());
        return FLINT_FAILED;
    }
    // get roms info
    if (!_fRom.open(_flintParams.cmd_params[0].c_str()))
    {
        reportErr(true, FLINT_BROM_ERROR, _fRom.err());
        return FLINT_FAILED;
    }
    if (!getRomsInfo(&_fRom, _romsInfo))
    {
        return FLINT_FAILED;
    }
    // check devids
    if ((_romsInfo.num_of_exp_rom > 0) && (_info.fw_info.dev_type) &&
        (_romsInfo.exp_rom_com_devid != EXP_ROM_GEN_DEVID) && (_romsInfo.exp_rom_com_devid != MISS_MATCH_DEV_ID) &&
        (_info.fw_info.dev_type != _romsInfo.exp_rom_com_devid))
    {
        printf("-W- Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _info.fw_info.dev_type,
               _romsInfo.exp_rom_com_devid);
        if (!askUser())
        {
            return FLINT_FAILED;
        }
    }
    char romVer1[50], romVer2[50];
    printf("\n");
    const char* infoStr = "    Current ROM info on flash: ";
    const char* infoStr2 = "    New ROM info:              ";
    if (_info.fw_info.roms_info.num_of_exp_rom > 0)
    {
        displayExpRomInfo(_info.fw_info.roms_info, infoStr);
        sprintf(romVer1, "%s", getExpRomVerStr(_info.fw_info.roms_info.rom_info[0]).c_str());
    }
    else
    {
        printf("%s", infoStr);
        snprintf(romVer1, 50, "N/A");
        printf("%s\n", romVer1);
    }
    displayExpRomInfo(_romsInfo, infoStr2);
    sprintf(romVer2, "%s", getExpRomVerStr(_romsInfo.rom_info[0]).c_str());
    // add new line to space up before showing burn precentage
    printf("\n");
    // print correct msg to log
    if (_info.fw_info.roms_info.num_of_exp_rom != 0)
    {
        print_line_to_log("Current ROM version on flash (1st ROM of %d): %s, New ROM version (1st ROM of %d): %s\n",
                          _info.fw_info.roms_info.num_of_exp_rom, romVer1, _romsInfo.num_of_exp_rom, romVer2);
    }
    else
    {
        print_line_to_log("Current ROM version on flash: %s, New ROM version(1st ROM of %d): %s\n", romVer1,
                          _romsInfo.num_of_exp_rom, romVer2);
    }
    // burn the rom
    printf("-I- Preparing to burn ROM ...\n");
    if (!ops->FwBurnRom(&_fRom, _flintParams.allow_rom_change, true, bromCbFunc))
    {
        reportErr(true, FLINT_BROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    bromCbFunc(101);
    printf("\n");
    const char* resignStr = ops->FwGetReSignMsgStr();
    if (resignStr)
    {
        printf("%s", resignStr);
    }
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    return FLINT_SUCCESS;
}

/***********************
 * Class: Delete ROM
 **********************/
DromSubCommand::DromSubCommand()
{
    _name = "drom";
    _desc = "Remove the ROM section from the flash.";
    _extendedDesc = "Remove the exp-ROM from the flash if it is existing.";
    _flagLong = "drom";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " drom";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Drom;
}

DromSubCommand::~DromSubCommand() {}

bool DromSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // leave an empty line before printing from callback
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    printf("\n");
    printf("-I- Preparing to remove ROM ...\n");
    if (!ops->FwDeleteRom(_flintParams.allow_rom_change, dromCbFunc))
    {
        reportErr(true, FLINT_DROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    dromCbFunc(101);
    const char* resignStr = ops->FwGetReSignMsgStr();
    if (resignStr)
    {
        printf("%s", resignStr);
    }
    return FLINT_SUCCESS;
}
/***********************
 * Class: Read ROM
 **********************/
RromSubCommand::RromSubCommand()
{
    _name = "rrom";
    _desc = "Read the ROM section from the flash.";
    _extendedDesc = "Read the exp-ROM from the flash if it is existing.";
    _flagLong = "rrom";
    _flagShort = "";
    _param = "<out-file>";
    _paramExp = "file: filename to write the exp-ROM to.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " rrom exp-rom.rom";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Rrom;
}

RromSubCommand::~RromSubCommand() {}

bool RromSubCommand::verifyParams()
{
    FILE* file;
    if ((file = fopen(_flintParams.cmd_params[0].c_str(), "r")) != NULL)
    {
        fclose(file);
        printf("\n-W- The given ROM file is existing, you are going to overwrite it.\n");
        if (!askUser())
        {
            return false;
        }
    }
    return true;
}

FlintStatus RromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // get the rom sector if present.
    std::vector<u_int8_t> romSect;
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwReadRom(romSect))
    {
        reportErr(true, FLINT_READ_ROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    // TOCPUn(&(romSect[0]), romSect.size()/4);
    if (!writeToFile(_flintParams.cmd_params[0], romSect))
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class:
 **********************/
BbSubCommand::BbSubCommand()
{
    _name = "bb";
    _desc = "Burn Block - Burns the given image as is. No checks are done.";
    _extendedDesc = "Burns entire flash verbatim from raw binary image. No checks are done on the flash or on the"
                    " given image file. No fields (such as VSD or Guids) are read from flash.";
    _flagLong = "bb";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -i image1.bin bb";
    _v = Wtv_Dev_And_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Bb;
}

BbSubCommand::~BbSubCommand()
{
    closeLog();
}

bool BbSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)(_flintParams.cmd_params.size()));
        return false;
    }
    printf("\n    Note: This option is only recommended for advanced users. Press Yes to continue");
    if (!askUser())
    {
        return false;
    }
    return true;
}

FlintStatus BbSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    if (_fwOps->FwType() == FIT_FS3 || _fwOps->FwType() == FIT_FS4 || _fwOps->FwType() == FIT_FSCTRL)
    {
        reportErr(true, FLINT_FS3_BB_ERROR);
        return FLINT_FAILED;
    }
    printf("\n");
    printf("Block burn: The given image will be burnt as is. No fields (such\n");
    printf("as GUIDS,VSD) are taken from current image on flash.\n");
    printf("Burn process will not be failsafe. No checks will be performed.\n");
    printf("ALL flash, including the Invariant Sector will be overwritten.\n");
    printf("If this process fails, computer may remain in an inoperable state.\n");
    if (!askUser())
    {
        return FLINT_FAILED;
    }
    ProgressCallBack progressFunc = _flintParams.silent == true ? (ProgressCallBack)NULL : &burnBCbFunc;
    if (!_fwOps->FwBurnBlock(_imgOps, progressFunc))
    {
        reportErr(true, "Non failsafe burn failed: %s\n", _fwOps->err());
        return FLINT_FAILED;
    }
    printf("\n");
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    return FLINT_SUCCESS;
}

/***********************
 * Class:
 **********************/
SgSubCommand::SgSubCommand()
{
    _name = "sg";
    _desc = "guids_num=<num|num_port1,num_port2> step_size=<size|size_port1,size_port2> Set GUIDs.";
    _extendedDesc = "Set GUIDs/MACs/UIDs in the given device/image.\n"
                    "Use -guid(s), -mac(s) and -uid(s) flags to set the desired values.\n"
                    "- On pre-ConnectX devices, the sg command  is used in production to apply GUIDs/MACs values to"
                    " cards that were pre-burnt with blank GUIDs. It is not meant for use in field.\n"
                    "- On 4th and 5th  generation devices, this command can operate on both image file and image on flash.\n"
                    "If the GUIDs/MACs/UIDs in the image on flash are non-blank, flint will re-burn the current"
                    " image using the given GUIDs/MACs/UIDs.";
    _flagLong = "sg";
    _flagShort = "";
    _param = "[nocrc]";
    _paramExp =
      "nocrc: (optional) When specified the flint would not update the full image crc after changing the guids\n"
      "guids_num: (optional) number of GUIDs to be allocated per physical port (FS3 Only)\n"
      "step_size: (optional) step size between GUIDs (FS3 Only)\n"
      "Note: guids_num/step_size values can be specified per port or for both ports";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -guid 0x0002c9000100d050 sg"
                          "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE4 " -guid 0x0002c9000100d050 -mac 0x0002c900d050 sg";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 2;
    _cmdType = SC_Sg;
    _ops = NULL;
    _mccSupported = true;
    memset(&_info, 0, sizeof(_info));
    ClearGuidStruct(_sgParams);
    _sgParams.usePPAttr = true;
}

void SubCommand::ClearGuidStruct(FwOperations::sg_params_t& sgParams)
{
    sgParams.updateCrc = false;    // default should be set to true
    sgParams.stripedImage = false; // default shuold be set to false unless working on striped image file
    sgParams.macsSpecified = false;
    sgParams.guidsSpecified = false;
    sgParams.uidSpecified = false; // valid for ConnectIB only
    sgParams.userGuids.resize(0);
    sgParams.numOfGUIDs = 0;    // number of GUIDs to allocate for each port. keep zero for default. (FS3 image Only)
    sgParams.stepSize = 0;      // step size between GUIDs. keep zero for default. (FS3 Image Only)
    sgParams.usePPAttr = false; // if set, use the per port attributes below (FS3 Image Only)
    memset(&(sgParams.numOfGUIDsPP), 0xff, sizeof(sgParams.numOfGUIDsPP));
    memset(&(sgParams.stepSizePP), 0xff, sizeof(sgParams.stepSizePP));
}

SgSubCommand::~SgSubCommand() {}

bool SgSubCommand::verifyParams()
{
    if ((_flintParams.cmd_params.size() == 1 && _flintParams.cmd_params[0] != "nocrc") ||
        (_flintParams.cmd_params.size() == 2 &&
         !extractUIDArgs(_flintParams.cmd_params, _sgParams.numOfGUIDsPP, _sgParams.stepSizePP)))
    {
        reportErr(true, "The sg parameter should be \"nocrc\", \"guids_num=<num> step_size=<size>\" or nothing\n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 2)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (!(_flintParams.guid_specified || _flintParams.guids_specified || _flintParams.uid_specified ||
          _flintParams.mac_specified || _flintParams.macs_specified))
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                  "GUIDs / MACs / UID (using command line flags -guid(s) / -mac(s) / -uid)");
        return false;
    }
    if ((_flintParams.guid_specified || _flintParams.guids_specified) && (_flintParams.uid_specified))
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                  "either GUIDs / UIDs (using command line flags -guid(s) / -uid)");
        return false;
    }
    if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified))
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(),
                  "either MACs / UIDs (using command line flags -mac(s) / -uid)");
        return false;
    }
    if (_flintParams.guid_specified && _flintParams.guids_specified)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid");
        return false;
    }
    if (_flintParams.mac_specified && _flintParams.macs_specified)
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-macs", "-mac");
        return false;
    }

    _sgParams.guidsSpecified = _flintParams.guid_specified || _flintParams.guids_specified;
    _sgParams.macsSpecified = _flintParams.mac_specified || _flintParams.macs_specified;
    _sgParams.uidSpecified = _flintParams.uid_specified;
    _sgParams.updateCrc = !(_flintParams.cmd_params.size() == 1);
    _sgParams.stripedImage = _flintParams.striped_image;
    return true;
}

void SgSubCommand::setUserGuidsAndMacs()
{
    // _sgParams.userGuids contains either guids and macs (or just guids) or just uids
    // we are required to specifiy to mlxfwops a guid vector of MAX_GUIDS size regardless if user gives only guids
    // or only macs or uids
    if (_sgParams.guidsSpecified)
    {
        _sgParams.userGuids = _flintParams.user_guids;
    }
    if (_sgParams.macsSpecified)
    {
        if (!_sgParams.guidsSpecified)
        {
            // it inits the guids with zeroes but mlxfwops will set them to 0xffff
            // can set default init if needed
            _sgParams.userGuids.resize(GUIDS);
        }
        _sgParams.userGuids.push_back(_flintParams.user_macs[0]);
        _sgParams.userGuids.push_back(_flintParams.user_macs[1]);
    }
    if (_sgParams.uidSpecified)
    {
        _sgParams.userGuids.resize(0);
        _sgParams.userGuids.push_back(_flintParams.baseUid);
    }
    _sgParams.userGuids.resize(MAX_GUIDS);
}

bool SgSubCommand::CheckSetGuidsFlags()
{
    bool ibDev;
    bool ethDev;
    FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev,
                              ethDev);
    // setDevFlags(_info, ibDev,ethDev);

    if (_sgParams.macsSpecified || _sgParams.guidsSpecified || _sgParams.uidSpecified)
    {
        if (!checkGuidsFlags(_info.fw_info.dev_type, _info.fw_type, _sgParams.guidsSpecified, _sgParams.macsSpecified,
                             _sgParams.uidSpecified, ibDev, ethDev))
        {
            return false;
        }
    }
    else
    {
        printf("-E- ");
        printMissingGuidErr(ibDev, ethDev);
        printf("\n");
        return false;
    }

    return true;
}

FlintStatus SgSubCommand::sgFs2()
{
    // different behaviours for fs2 device with blank guids and fs2 device with guids or image
    // different behaviour if isfailesafe or not
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
    }

    if (_flintParams.device_specified && !_info.fs2_info.blank_guids)
    {
        // 2- FS2 device with no blank Guids
        printf(FLINT_SET_GUIDS_WARRNING);
    }

    if (!CheckSetGuidsFlags())
    {
        return FLINT_FAILED;
    }

    if (_flintParams.image_specified || !_info.fs2_info.blank_guids)
    {
        // report guid changes
        bool ethDev;
        bool ibDev;
        FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev,
                                  ethDev);
        // setDevFlags(_info, ibDev, ethDev);
        // decide what are our new guids/macs
        guid_t* new_guids =
          (_sgParams.guidsSpecified || _sgParams.uidSpecified) ? &_sgParams.userGuids[0] : &_info.fs2_info.guids[0];
        guid_t* new_macs = _sgParams.macsSpecified ? &_sgParams.userGuids[GUIDS] : &_info.fs2_info.guids[GUIDS];

        if (!reportGuidChanges(new_guids, new_macs, &_info.fs2_info.guids[0], &_info.fs2_info.guids[GUIDS], ibDev,
                               ethDev, _info.fs2_info.guid_num))
        {
            return FLINT_FAILED;
        }
    }
    if (!_ops->FwSetGuids(_sgParams, &verifyCbFunc, &burnCbFs2Func))
    {
        reportErr(true, FLINT_SG_GUID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    burnCbFs2Func(101);
    return FLINT_SUCCESS;
}

#ifndef MST_UL
#define FW_RESET_MSG "To load new configuration run mlxfwreset or reboot machine"
#else
#define FW_RESET_MSG "To load new configuration run mstfwreset or reboot machine"
#endif

FlintStatus SgSubCommand::sgFs3()
{
    if (!CheckSetGuidsFlags())
    {
        return FLINT_FAILED;
    }
    if (_flintParams.guids_specified || _flintParams.macs_specified)
    {
        string flag = _flintParams.guids_specified ? "-guids" : "-macs";
        reportErr(true, FLINT_NOT_SUPP_UID_FLAG_ERROR, flag.c_str());
        return FLINT_FAILED;
    }

    // ArcusE doesn't have DEV_INFO section
    if (_info.fw_info.chip_type == CT_ARCUSE)
    {
        reportErr(true, FLINT_INVALID_COMMAD_ERROR, "ArcusE device/image is not supported.");
        return FLINT_FAILED;
    }

    // TODO: create method that checks the flags for FS3/FS2
    if (_info.fw_info.chip_type == CT_CONNECT_IB || _info.fw_info.chip_type == CT_SWITCH_IB)
    {
        if (!_flintParams.uid_specified)
        {
            reportErr(true, FLINT_NO_UID_FLAG_ERROR);
            return FLINT_FAILED;
        }
        // for connectib we just need the base guid so we put it in the first location.
        _sgParams.userGuids.resize(1);
        _sgParams.userGuids[0] = _flintParams.baseUid;
    }
    else
    {
        if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified)
        {
            reportErr(true, FLINT_NO_GUID_MAC_FLAGS_ERROR);
            return FLINT_FAILED;
        }
        if (_flintParams.uid_specified)
        {
            _sgParams.userGuids.resize(1);
            _sgParams.userGuids[0] = _flintParams.baseUid;
        }
        else
        {
            // guids and/or macs were specified
            guid_t tmpGuid;
            tmpGuid.h = 0;
            tmpGuid.l = 0;
            _sgParams.userGuids.resize(2);
            _sgParams.userGuids[0] = _sgParams.guidsSpecified ? _flintParams.user_guids[0] : tmpGuid;
            _sgParams.userGuids[1] = _sgParams.macsSpecified ? _flintParams.user_macs[0] : tmpGuid;
        }
    }

    if (!_ops->FwSetGuids(_sgParams, &verifyCbFunc))
    {
        reportErr(true, FLINT_SG_UID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified)
    {
        printf("-I- %s\n", FW_RESET_MSG);
    }
    return FLINT_SUCCESS;
}

FlintStatus SgSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // query device
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    bool stripedImage = _flintParams.striped_image && _flintParams.image_specified;
    if (!_ops->FwQuery(&_info, true, stripedImage))
    {
        reportErr(true, FLINT_SG_GUID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    setUserGuidsAndMacs();
    if (_info.fw_type == FIT_FS2)
    {
        return sgFs2();
    }
    FlintStatus setGuidResult = sgFs3();
    return setGuidResult;
}

/*****************************
 * Class: Set Manufacture GUIDs
 *****************************/
SmgSubCommand::SmgSubCommand()
{
    _name = "smg";
    _desc = "Set manufacture GUIDs (For FS3/FS4 image only).";
    _extendedDesc = "Set manufacture GUID, Set manufacture GUIDs in the given FS3/FS4/FS5 image.\n"
                    "Use -uid flag to set the desired GUIDs, intended for production use only.";
    _flagLong = "smg";
    _flagShort = "";
    _param = "guids_num=<num|num_port1,num_port2> step_size=<size|size_port1,size_port2>";
    _paramExp = "guids_num: (optional) number of GUIDs to be allocated per physical port\n"
                "step_size: (optional) step size between GUIDs\n"
                "Note: guids_num/step_size values can be specified per port or for both ports";
    _example = FLINT_NAME " -i fw_image.bin -uid 0x0002c9000100d050 smg"
#ifndef __WIN__
                          "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3
                          " -uid 0x0002c9000100d050 smg (should be used when device is idle)"
#endif
                          "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE4
                          " -guid 0x0002c9000100d050 -mac 0x0002c900d050 smg (should be used when device is idle)";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 2;
    _cmdType = SC_Smg;
    _ops = NULL;
    memset(&_baseGuid, 0, sizeof(_baseGuid));
    memset(&_info, 0, sizeof(_info));
    memset(&(_baseGuid.num_of_guids_pp), 0xff, sizeof(_baseGuid.num_of_guids_pp));
    memset(&(_baseGuid.step_size_pp), 0xff, sizeof(_baseGuid.step_size_pp));
    _baseGuid.use_pp_attr = 1;
}

SmgSubCommand::~SmgSubCommand() {}

bool SmgSubCommand::verifyParams()
{
    if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified)
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"-uid or -guid/-mac\" flags");
        return false;
    }
    if (_flintParams.guids_specified)
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, "\"-guids\"", _name.c_str(), "\"-guid\"");
        return false;
    }
    if (_flintParams.macs_specified)
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, "\"-macs\"", _name.c_str(), "\"-mac\"");
        return false;
    }
    if (_flintParams.uid_specified && (_flintParams.guid_specified || _flintParams.mac_specified))
    {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "\"-uid\"", "\"-guid\"/-mac\"");
        return false;
    }

    if (_flintParams.cmd_params.size() != 0 && _flintParams.cmd_params.size() != 2)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR4, _name.c_str(), 0, 2, (int)_flintParams.cmd_params.size());
        return false;
    }

    if (_flintParams.cmd_params.size() == 2 &&
        !extractUIDArgs(_flintParams.cmd_params, _baseGuid.num_of_guids_pp, _baseGuid.step_size_pp))
    {
        return false;
    }

    if (_flintParams.uid_specified)
    {
        _baseGuid.set_mac_from_guid = true;
    }

    _baseGuid.base_guid_specified = _flintParams.uid_specified || _flintParams.guid_specified;
    if (_baseGuid.base_guid_specified)
    {
        _baseGuid.base_guid = _flintParams.uid_specified ? _flintParams.baseUid : _flintParams.user_guids[0];
    }

    _baseGuid.base_mac_specified = _flintParams.mac_specified;
    if (_baseGuid.base_mac_specified)
    {
        _baseGuid.base_mac = _flintParams.user_macs[0];
    }
    // printf("-D-"GUID_FORMAT"\n", _baseGuid.h, _baseGuid.l);
    return true;
}

FlintStatus SmgSubCommand::executeCommand()
{
    if (preFwOps())
    {
        return FLINT_FAILED;
    }
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    // TODO: dispaly MFG guid changes
    bool stripedImage = _flintParams.striped_image && _flintParams.image_specified;
    if (!_ops->FwQuery(&_info, true, stripedImage))
    {
        reportErr(true, FLINT_MFG_ERROR, _ops->err());
        return FLINT_FAILED;
    }

    if (_info.fw_info.chip_type == CT_CONNECT_IB || _info.fw_info.chip_type == CT_SWITCH_IB)
    {
        if (!_flintParams.uid_specified)
        {
            reportErr(true, "Can not set GUIDs/MACs: uid is not specified, please run with -uid flag.\n");
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified)
        {
            reportErr(true,
                      "Can not set GUIDs/MACs: GUIDs/MACs are not specified, please run with -uid/-guid/-mac flags.\n");
            return FLINT_FAILED;
        }
    }

    bool ret;
    ret = _ops->FwSetMFG(_baseGuid, &verifyCbFunc);
    if (!ret)
    {
        reportErr(true, FLINT_MFG_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified && _info.fw_type != FIT_FS2)
    {
        printf("-I- %s\n", FW_RESET_MSG);
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: Set Attestation Cert Chain Subcommand
 **********************/
SetCertChainSubCommand::SetCertChainSubCommand()
{
    _name = "set attestation certificate chain";
    _desc = "Set read-only attestation certificate chain (For FS4 image only).";
    _extendedDesc = "Set Read-only attestation certificate chain, Set attestation certificate chain in the given FS4 "
                    "image, intended for production use only.";
    _flagLong = "set_attestation_cert_chain";
    _flagShort = "";
    _param = "<Certificate chain file>";
    _paramExp = "Certificate chain file: bin file containing the certificate chain data";
    _example = FLINT_NAME
      " -i fw_image.bin set_attestation_cert_chain cert_chain.bin"
#ifndef __WIN__
      "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3
      " -override_cache_replacement set_attestation_cert_chain cert_chain.bin (should be used when device is idle)"
#endif
      ;
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Cert_Chain;
}

FlintStatus SetCertChainSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetCertChain((char*)_flintParams.cmd_params[0].c_str(), _flintParams.cert_chain_index, &verifyCbFunc))
    {
        reportErr(true, FLINT_CERT_CHAIN_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: Set Vpd Subcommand
 **********************/
SetVpdSubCommand::SetVpdSubCommand()
{
    _name = "set vpd";
    _desc = "Set read-only VPD (For FS3/FS4 image only).";
    _extendedDesc = "Set Read-only VPD, Set VPD in the given FS3/FS4 image, intended for production use only.";
    _flagLong = "set_vpd";
    _flagShort = "";
    _param = "<vpd file>";
    _paramExp = "vpd file: bin file containing the vpd data";
    _example = FLINT_NAME " -i fw_image.bin set_vpd vpd.bin"
#ifndef __WIN__
                          "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3
                          " -override_cache_replacement set_vpd vpd.bin (should be used when device is idle)"
#endif
      ;
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Vpd;
}

FlintStatus SetVpdSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetVPD((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc))
    {
        reportErr(true, FLINT_VPD_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: SetPublicKeysSubcommand
 **********************/
SetPublicKeysSubCommand::SetPublicKeysSubCommand()
{
    _name = "set public keys";
    _desc = "Set Public Keys (For FS3/FS4 image only).";
    _extendedDesc = "Set Public Keys in the given FS3/FS4 image.";
    _flagLong = "set_public_keys";
    _flagShort = "";
    _param = "<public keys binary file>";
    _paramExp = "public keys file: bin file containing the public keys data";
    _example = FLINT_NAME " -i fw_image.bin set_public_keys publickeys.bin";
    _v = Wtv_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Public_Keys;
}

SetPublicKeysSubCommand::~SetPublicKeysSubCommand() {}

FlintStatus SetPublicKeysSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _imgOps;
    if (!ops->FwSetPublicKeys((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc))
    {
        reportErr(true, FLINT_SET_PUBLIC_KEYS_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: SetForbiddenVersionsSubcommand
 **********************/
SetForbiddenVersionsSubCommand::SetForbiddenVersionsSubCommand()
{
    _name = "set forbidden versions";
    _desc = "Set Forbidden Versions (For FS3/FS4 image only).";
    _extendedDesc = "Set Forbidden Versions in the given FS3/FS4 image.";
    _flagLong = "set_forbidden_versions";
    _flagShort = "";
    _param = "[forbidden versions binary file]";
    _paramExp = "forbidden versions file: bin file containing the forbidden versions data";
    _example = FLINT_NAME " -i fw_image.bin set_forbidden_versions forbidden_versions.bin";
    _v = Wtv_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Forbidden_Versions;
}

SetForbiddenVersionsSubCommand::~SetForbiddenVersionsSubCommand() {}

FlintStatus SetForbiddenVersionsSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _imgOps;
    if (!ops->FwSetForbiddenVersions((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc))
    {
        reportErr(true, FLINT_SET_FORBIDDEN_VERSIONS_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: Set VSD
 **********************/
SvSubCommand::SvSubCommand()
{
    _name = "sv";
    _desc = "Set the VSD.";
    _extendedDesc = "Set VSD in the given device/image.\n"
                    "Use -vsd flag to set the desired VSD string.";
    _flagLong = "sv";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -vsd VSD_STRING sv"
#ifndef __WIN__
                          "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3
                          " -vsd VSD_STRING -override_cache_replacement sv (should be used when device is idle)\n"
#endif
      ;
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Sv;
}

SvSubCommand::~SvSubCommand() {}

bool SvSubCommand::verifyParams()
{
    if (!_flintParams.vsd_specified)
    {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"-vsd\"");
        return false;
    }
    // we verify that -vsd has a parameter in the cmd parser

    return true;
}

FlintStatus SvSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetVSD((char*)_flintParams.vsd.c_str(), &vsdCbFunc, &verifyCbFunc))
    {
        reportErr(true, FLINT_VSD_ERROR, ops->err());
        return FLINT_FAILED;
    }

    if (ops->FwType() == FIT_FS2)
    {
        // print "restoring signature" on FS2 to be consistent with FS3 output
        vsdCbFunc(101);
    }
    return FLINT_SUCCESS;
}

/*******************************
 * Class: Read Image SubCommand
 ******************************/
RiSubCommand::RiSubCommand()
{
    _name = "ri";
    _desc = "Read the fw image on the flash.";
    _extendedDesc = "Read the FW image from flash and write it to a file.";
    _flagLong = "ri";
    _flagShort = "";
    _param = "<out-file>";
    _paramExp = "file: filename to write the image to (raw binary).";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " ri file.bin";
    _v = Wtv_Dev;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Ri;
    _mccSupported =
      false; // Read image isn't supported by MCC flow since it can't read Device area (DTOC and its sections)
}

RiSubCommand::~RiSubCommand() {}

FlintStatus RiSubCommand::executeCommand()
{
    // init fw operation object
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // Check if we have permission to write to file
    FILE* fh;
    if ((fh = fopen(_flintParams.cmd_params[0].c_str(), "wb")) == NULL)
    {
        reportErr(true, "Can not open %s: %s\n", _flintParams.cmd_params[0].c_str(), strerror(errno));
        return FLINT_FAILED;
    }
    else
    {
        fclose(fh);
    }
    u_int32_t imgSize;
    // on first call we get the image size
    if (!_fwOps->FwReadData(NULL, &imgSize))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    std::vector<u_int8_t> imgBuff(imgSize);
    // on second call we fill it
    if (!_fwOps->FwReadData((void*)(&imgBuff[0]), &imgSize))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    FlintStatus writeImageRes = writeImageToFile(_flintParams.cmd_params[0].c_str(), &(imgBuff[0]), imgSize);
    return writeImageRes;
}

/***********************
 * Class: Dump Conf SubCommand
 **********************/
DcSubCommand::DcSubCommand()
{
    _name = "dc";
    _desc = "Dump Configuration: print fw configuration file for the given image.";
    _extendedDesc =
      "Print (to screen or to a file) the FW configuration text file used by the image generation process.\n"
      "This command would fail if the image does not contain a FW configuration section."
      " Existence of this section depends on the version of the image generation tool.";
    _flagLong = "dc";
    _flagShort = "";
    _param = "<out-file>";
    _paramExp = "file: (optional) filename to write the dumped configuration to. If not given,"
                " the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " dc";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Dc;
}

DcSubCommand::~DcSubCommand() {}

bool DcSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DcSubCommand::executeCommand()
{
    FwOperations* ops;
    // init fw operation object
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char* file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*)NULL;
    if (!ops->FwGetSection((ops->FwType() == FIT_FS2) ? (int)H_FW_CONF : (int)FS3_DBG_FW_INI, _sect,
                           _flintParams.striped_image))
    {
        reportErr(true, FLINT_DUMP_ERROR, "Fw Configuration", ops->err());
        return FLINT_FAILED;
    }
    if (!dumpFile(file, _sect, "Fw Configuration"))
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class:Dump Hash SubCommand
 **********************/
DhSubCommand::DhSubCommand()
{
    _name = "dh";
    _desc = "Dump Hash: dump the hash if it is integrated in the FW image";
    _extendedDesc = "Print (to screen or to a file) the HASH text file used by the FW.\n"
                    "This command would fail if the image does not contain a Hash file.";
    _flagLong = "dh";
    _flagShort = "";
    _param = "<out-file>";
    _paramExp = "file - (optional) filename to write the dumped tracer hash file to. If not given,"
                " the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " dh hash.csv";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Dh;
}

DhSubCommand::~DhSubCommand() {}

bool DhSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DhSubCommand::executeCommand()
{
    FwOperations* ops;
    // init fw operation object
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    // check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char* file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*)NULL;
    if (!ops->FwGetSection(H_HASH_FILE, _sect, _flintParams.striped_image))
    {
        reportErr(true, FLINT_DUMP_ERROR, "Hash file", ops->err());
        return FLINT_FAILED;
    }
    if (!dumpFile(file, _sect, "Fw Configuration"))
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class:Set Key SubCommand
 **********************/
SetKeySubCommand::SetKeySubCommand()
{
    _name = "set_key";
    _desc = "Set/Update the HW access key which is used to enable/disable access to HW.\n"
            "The key can be provided in the command line or interactively typed after the command is given\n"
            "NOTE: The new key is activated only after the device is reset.";
    _extendedDesc = "Set/Update the HW access key which is used to enable/disable access to HW.";
    _flagLong = "set_key";
    _flagShort = "";
    _param = "<key>";
    _paramExp = "key: (optional) The new key you intend to set (in hex).";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " set_key 1234deaf5678";
    _v = Wtv_Dev;
    _maxCmdParamNum = 1;
    _cmdType = SC_Set_Key;
    _getKeyInter = false;
    memset(&_userKey, 0, sizeof(_userKey));
}

SetKeySubCommand::~SetKeySubCommand() {}

bool SetKeySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    _getKeyInter = (_flintParams.cmd_params.size() == 0);
    return true;
}

bool SetKeySubCommand::getKeyInteractively()
{
    char keyArr[MAX_PASSWORD_LEN + 1] = {0};
    getPasswordFromUser("Enter Key ", keyArr);
    if (strlen(keyArr) == 0)
    {
        reportErr(true, FLINT_INVALID_PASSWORD);
        return false;
    }

    if (!getGUIDFromStr(keyArr, _userKey,
                        "Invalid Key syntax, it should contain only hexa numbers and of appropriate length."))
    {
        return false;
    }
    // verify key
    hw_key_t verKey;
    getPasswordFromUser("Verify Key ", keyArr);
    if (!getGUIDFromStr(keyArr, verKey,
                        "Invalid Key syntax, it should contain only hexa numbers and of appropriate length."))
    {
        return false;
    }
    if (_userKey.h != verKey.h || _userKey.l != verKey.l)
    {
        reportErr(true, FLINT_SET_KEY_ERROR, "The keys you entered did not match.");
        return false;
    }
    return true;
}

FlintStatus SetKeySubCommand::executeCommand()
{
    _flintParams.silent = true;
    if (preFwOps() == FLINT_FAILED)
    {
        _flintParams.silent = false;
        if (preFwAccess() == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
    }
    if (_getKeyInter)
    {
        if (!getKeyInteractively())
        {
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!getGUIDFromStr(_flintParams.cmd_params[0], _userKey,
                            "Invalid Key syntax, it should contain only hexa numbers and of appropriate length."))
        {
            return FLINT_FAILED;
        }
    }
    
    if (_fwOps != nullptr)
    {
        if (_fwOps->FwType() == FIT_FS2)
        {
            if (!_fwOps->FwSetAccessKey(_userKey, &setKeyCbFunc))
            {
                reportErr(true, FLINT_SET_KEY_ERROR, _fwOps->err());
                return FLINT_FAILED;
            }
            setKeyCbFunc(101);
            printf("\n-I- New key was updated successfully in the flash. "
                   "In order to activate the new key you should reboot or restart the driver.\n");
        }
        else
        {
            if (!_fwOps->FwSetAccessKey(_userKey, &setKeyCbFunc))
            {
                reportErr(true, FLINT_SET_KEY_ERROR, _fwOps->err());
                return FLINT_FAILED;
            }
        }
    }
    else
    {
        if (((Flash*)_io)->is_fifth_gen())
        {
            if (((Flash*)_io)->get_cr_space_locked())
            {
                printf("-I- HW access already disabled\n");
                return FLINT_SUCCESS;
            }
            // In 5th gen treat set as disable hw access
            u_int64_t key = ((u_int64_t)_userKey.h << 32) | _userKey.l;
            if (!((Flash*)_io)->disable_hw_access(key))
            {
                reportErr(true, FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
                return FLINT_FAILED;
            }
            printf("-I- Secure Host was enabled successfully on the device.\n");
        }
        else
        {
            reportErr(true, FLINT_SET_KEY_ERROR, "Unsupported operation");
            return FLINT_FAILED;
        }
    }

    return FLINT_SUCCESS;
}

/***********************
 * Class:HwAccess SubCommand
 **********************/
HwAccessSubCommand::HwAccessSubCommand()
{
    _name = "hw_access";
    _desc = "Enable/disable the access to the HW.\n"
            "The key can be provided in the command line or interactively typed after the command is given";
    _extendedDesc = "Enable/disable the access to the HW.";
    _flagLong = "hw_access";
    _flagShort = "";
    _param = "[enable/disable] <key>";
    _paramExp = "<enable/disable>: Specify if you intend to disable or enable the HW access.\n"
                "You will be asked to type a key when you try to enable HW access.\n"
                "key: The key you intend to use for enabling the HW access, or disabling it in 5th Gen devices.\n"
                "Key format consists of at most 16 Hexadecimal digits.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw_access enable";
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _cmdType = SC_Hw_Access;
}

HwAccessSubCommand::~HwAccessSubCommand() {}

bool HwAccessSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() == 0)
    {
        reportErr(true, FLINT_MISSED_ARG_ERROR, "<disable/enable>", _name.c_str());
        return false;
    }
    if (_flintParams.cmd_params.size() > 2)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (_flintParams.cmd_params[0] != "enable" && _flintParams.cmd_params[0] != "disable")
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(),
                  "enable or disable");
        return false;
    }
    return true;
}

FlintStatus HwAccessSubCommand::disableHwAccess()
{
    if (_fwOps != nullptr)
    {
        u_int8_t secureHostState = 0;
        if (!_fwOps->GetSecureHostState(secureHostState))
        {
            return FLINT_SUCCESS;
        }
        if (secureHostState)
        {
            printf("-I- HW access already disabled\n");
            return FLINT_SUCCESS;
        }
    }
    else
    {
        if (((Flash*)_io)->get_cr_space_locked())
        {
            printf("-I- HW access already disabled\n");
            return FLINT_SUCCESS;
        }
    }

    if (_fwOps != nullptr)
    {
        SubCommand* setKey = new SetKeySubCommand();
        _flintParams.cmd_params.erase(_flintParams.cmd_params.begin());
        setKey->setParams(_flintParams);
        FlintStatus rc = setKey->executeCommand();
        delete setKey;
        return rc;
    }
    else
    {
        if (!((Flash*)_io)->disable_hw_access())
        {
            printf(FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
        }
    }

    return FLINT_SUCCESS;
}
FlintStatus HwAccessSubCommand::enableHwAccess()
{
    if (_fwOps != nullptr)
    {
        u_int8_t secureHostState = 0;
        if (!_fwOps->GetSecureHostState(secureHostState))
        {
            return FLINT_SUCCESS;
        }
        if (!secureHostState)
        {
            printf("-I- HW access already enabled\n");
            return FLINT_SUCCESS;
        }
    }
    else
    {
        if (((Flash*)_io)->get_cr_space_locked() == 0)
        {
            printf("-I- HW access already enabled\n");
            return FLINT_SUCCESS;
        }
    }
    u_int64_t key;
    hw_key_t keyStruct;
    // now we need to get the key from the user (either given in the parameters or we get it during runtime)
    if (_flintParams.cmd_params.size() == 2)
    {
        if (!getGUIDFromStr(_flintParams.cmd_params[1], keyStruct,
                            "Invalid Key syntax, it should contain only hexa numbers and of appropriate length."))
        {
            return FLINT_FAILED;
        }
    }
    else
    { // we need to get the key from user during runtime
        char keyArr[MAX_PASSWORD_LEN + 1] = {0};
        getPasswordFromUser("Enter Key ", keyArr);
        if (strlen(keyArr) == 0)
        {
            reportErr(true, FLINT_INVALID_PASSWORD);
            return FLINT_FAILED;
        }
        if (!getGUIDFromStr(keyArr, keyStruct,
                            "Invalid Key syntax, it should contain only hexa numbers and of appropriate length."))
        {
            return FLINT_FAILED;
        }
    }

    key = ((u_int64_t)keyStruct.h << 32) | keyStruct.l;

    if (_fwOps != nullptr)
    {
        if (!_fwOps->ChangeSecureHostState(0, key))
        {
            return FLINT_SUCCESS;
        }
    }
    else
    {
        if (!((Flash*)_io)->enable_hw_access(key))
        {
            reportErr(true, FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
        }
    }
    printf("-I- The Secure Host was disabled successfully on the device.\n");

    return FLINT_SUCCESS;
}

FlintStatus HwAccessSubCommand::executeCommand()
{
    _flintParams.silent = true;
    if (preFwOps() == FLINT_FAILED)
    {
        _flintParams.silent = false;
        if (preFwAccess() == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
    }
    if (_flintParams.cmd_params[0] == "disable")
    {
        return disableHwAccess();
    }
    // else its enable hw access
    return enableHwAccess();
}

/***********************
 * Class: Hw SubCommand
 **********************/
HwSubCommand::HwSubCommand()
{
#ifndef EXTERNAL
    _name = "hw";
    _desc = "Set/query HW info and flash attributes.";
    _extendedDesc = "Access HW info and flash attributes.";
    _flagLong = "hw";
    _flagShort = "";
    _param = "[query/set] <ATTR=VAL>";
    _paramExp = "query: query HW info\n"
                "set [ATTR=VAL]: set flash attribure\n"
                "Supported attributes:\n"
                "    QuadEn: can be 0 or 1\n"
                "    DummyCycles: can be [1..15]\n"
                "    Flash[0|1|2|3].WriteProtected can be:\n"
                "        <Top|Bottom>,<1|2|4|8|16|32|64>-<Sectors|SubSectors>\n"
                "    DriverStrength: can be:\n"
                "        For Winbond flashes: [25,50,75,100](%)\n"
                "        For Micron flashes:  [22,44,66,100](%)\n"
                "        For Macronix MX25K16XXX flashes:  [41,70,83,100](%)\n"
                "        For Macronix MX25UXXX flashes:  [24,26,30,34,41,52,76,146](%)\n"
                "        For Issi flashes:  [16,25,33,50,75,100](%)\n";
    _example = "flint -d " MST_DEV_EXAMPLE1 " hw query\n" FLINT_NAME " -d " MST_DEV_EXAMPLE1
               " hw set QuadEn=1\n" FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw set Flash1.WriteProtected=Top,1-SubSectors";
#else
    _name = "Hw";
    _desc = "Query HW info and flash attributes.";
    _extendedDesc = "Query HW info and flash attributes.";
    _flagLong = "hw";
    _flagShort = "";
    _param = "query";
    _paramExp = "query";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw query";
#endif
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 1;
    _cmdType = SC_Hw;
}

HwSubCommand::~HwSubCommand() {}

bool HwSubCommand::verifyParams()
{
#ifdef EXTERNAL
    if (_flintParams.cmd_params[0] != "query")
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "query");
        return false;
    }
    if (_flintParams.cmd_params.size() != 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
#else
    if (_flintParams.cmd_params.size() > 2 || _flintParams.cmd_params.size() == 0)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params[0] != "query") && (_flintParams.cmd_params[0] != "set"))
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "query or set");
        return false;
    }
    if ((_flintParams.cmd_params[0] == "set") && (_flintParams.cmd_params.size() != 2))
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
#endif

    return true;
}

FlintStatus HwSubCommand::printAttr(const ext_flash_attr_t& attr)
{
    printf("HW Info:\n");
    printf("  HwDevId                 %d\n", attr.hw_dev_id);
    printf("  HwRevId                 0x%x\n", attr.rev_id);

    printf("Flash Info:\n");
    if (attr.type_str != NULL)
    {
        // we don't print the flash type in old devices
        printf("  Type                    %s\n", attr.type_str);
    }
    printf("  TotalSize               0x%x\n", attr.size);
    printf("  Banks                   0x%x\n", attr.banks_num);
    printf("  SectorSize              0x%x\n", attr.sector_size);
    printf("  WriteBlockSize          0x%x\n", attr.block_write);
    printf("  CmdSet                  0x%x\n", attr.command_set);

    // Quad EN query
    if (attr.quad_en_support)
    {
        switch (attr.mf_get_quad_en_rc)
        {
            case MFE_OK:
                printf("  " QUAD_EN_PARAM "                  %d\n", attr.quad_en);
                break;

            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the " QUAD_EN_PARAM
                       " attribute between the flashes attached to the device\n");
                break;

            case MFE_NOT_SUPPORTED_OPERATION:
                printf("Quad En not supported operation.\n");
                break;
            case MFE_NOT_IMPLEMENTED:
                printf("Quad En not implemented.\n");
                break;
            default:
                printf("Failed to get " QUAD_EN_PARAM " attribute: %s (%s)", errno == 0 ? "" : strerror(errno),
                       mf_err2str(attr.mf_get_quad_en_rc));
                return FLINT_FAILED;
        }
    }
    // Dummy Cycles query
    if (attr.dummy_cycles_support)
    {
        switch (attr.mf_get_dummy_cycles_rc)
        {
            case MFE_OK:
                printf("  " DUMMY_CYCLES_PARAM "             %d\n", attr.dummy_cycles);
                break;

            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the " DUMMY_CYCLES_PARAM
                       " attribute between the flashes attached to the device\n");
                break;

            case MFE_NOT_SUPPORTED_OPERATION:
                break;

            default:
                printf("Failed to get " DUMMY_CYCLES_PARAM " attribute: %s (%s)", errno == 0 ? "" : strerror(errno),
                       mf_err2str(attr.mf_get_dummy_cycles_rc));
                return FLINT_FAILED;
        }
    }
    // Flash write protected info query
    if (attr.write_protect_support)
    {
        int bank;
        int rc;
        for (bank = 0; bank < attr.banks_num; bank++)
        {
            write_protect_info_t protect_info = attr.protect_info_array[bank];
            rc = attr.mf_get_write_protect_rc_array[bank];
            if (rc == MFE_OK)
            {
                printf("  " FLASH_NAME "%d." WRITE_PROTECT "   ", bank);
                if (protect_info.sectors_num != 0)
                {
                    printf("%s,", (protect_info.is_bottom ? WP_BOTTOM_STR : WP_TOP_STR));
                    printf("%d-", protect_info.sectors_num);
                    printf("%s\n", (protect_info.is_subsector ? WP_SUBSEC_STR : WP_SEC_STR));
                }
                else
                {
                    printf(WP_DISABLED_STR "\n");
                }
            }
            else
            {
                if (rc != MFE_NOT_SUPPORTED_OPERATION)
                {
                    // We ignore the read when operation is not supported!
                    printf("Failed to get write_protected info: %s (%s)", errno == 0 ? "" : strerror(errno),
                           mf_err2str(rc));
                    return FLINT_FAILED;
                }
            }
        }
    }
    // Driver-strength query
    if (attr.driver_strength_support)
    {
        switch (attr.mf_get_driver_strength_rc)
        {
            case MFE_OK:
                printf("  " DRIVER_STRENGTH_PARAM "          %d%%\n", attr.driver_strength);
                break;

            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the " DRIVER_STRENGTH_PARAM
                       " attribute between the flashes attached to the device\n");
                break;

            case MFE_NOT_SUPPORTED_OPERATION:
                printf("Driver-strength not supported operation.\n");
                break;
            case MFE_NOT_IMPLEMENTED:
                printf("Driver-strength not implemented.\n");
                break;
            case MFE_REG_ACCESS_METHOD_NOT_SUPP:
                printf("Driver-strength not supported by FW, retry with -ocr.\n");
                break;
            default:
                printf("Failed to get " DRIVER_STRENGTH_PARAM " attribute: %s (%s)", errno == 0 ? "" : strerror(errno),
                       mf_err2str(attr.mf_get_driver_strength_rc));
                return FLINT_FAILED;
        }
    }
    printf("  JEDEC_ID                0x%06x\n",
           attr.jedec_id & 0xffffff); // JEDEC_ID is built from 3B, so we mask last byte
    
    if (attr.write_protect_support)
    {
        if (!PrintWriteProtectedBits(attr))
        {
            return FLINT_FAILED;
        }
    }

    // SRWD query
    if (attr.srwd_support && attr.write_protect_support)
    {
        switch (attr.mf_get_srwd_rc)
        {
            case MFE_OK:
                printf("  " SRWD_PARAM "                    %d\n", attr.srwd);
                break;

            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the " SRWD_PARAM
                       " attribute between the flashes attached to the device\n");
                break;

            case MFE_NOT_SUPPORTED_OPERATION:
                printf(SRWD_PARAM " not supported operation.\n");
                break;
            case MFE_NOT_IMPLEMENTED:
                printf(SRWD_PARAM "not implemented.\n");
                break;
            default:
                printf("Failed to get " SRWD_PARAM " attribute: %s (%s)", errno == 0 ? "" : strerror(errno),
                       mf_err2str(attr.mf_get_srwd_rc));
                return FLINT_FAILED;
        }
    }

    // CMP query
    if (attr.cmp_support && attr.write_protect_support)
    {
        switch (attr.mf_get_cmp_rc)
        {
            case MFE_OK:
                printf("  " CMP_PARAM "                     %d\n", attr.cmp);
                break;

            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the " CMP_PARAM
                       " attribute between the flashes attached to the device\n");
                break;

            case MFE_NOT_SUPPORTED_OPERATION:
                printf(CMP_PARAM " not supported operation.\n");
                break;
            case MFE_NOT_IMPLEMENTED:
                printf(CMP_PARAM "not implemented.\n");
                break;
            default:
                printf("Failed to get " CMP_PARAM " attribute: %s (%s)", errno == 0 ? "" : strerror(errno),
                       mf_err2str(attr.mf_get_cmp_rc));
                return FLINT_FAILED;
        }
    }

    if (attr.series_code_support)
    {
        printf("  " SERIES_CODE_PARAM "              0x%02X\n", attr.series_code);
    }

    return FLINT_SUCCESS;
}

FlintStatus HwSubCommand::executeCommand()
{
    // init fw operation object
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    dm_dev_id_t devid_t;
    u_int32_t devid;
    u_int32_t revid;
    mfile* mf = ((Flash*)_io)->getMfileObj();
    int rc = dm_get_device_id(mf, &devid_t, &devid, &revid);
    (void)devid;
    (void)revid;
    if (rc != 0)
    {
        reportErr(true, "HW command: can't get device Id");
        return FLINT_FAILED;
    }
    if (_flintParams.cmd_params[0] == "set")
    {
        char* cmdParam = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
        char *paramName, *paramValStr;
        paramName = strtok(cmdParam, "=");
        paramValStr = strtok(NULL, "=");
        // printf("-D- param_name = %s, param_val_str=%s, cmdParam=%s\n", paramName, paramValStr, cmdParam);
        if (paramName == NULL || paramValStr == NULL)
        {
            delete[] cmdParam;
            reportErr(true, FLINT_HW_SET_ARGS_ERROR, _flintParams.cmd_params[1].c_str());
            return FLINT_FAILED;
        }

        ext_flash_attr_t attr;
        memset(&attr, 0, sizeof(ext_flash_attr_t));
        if (!FillAttrIfNeeded(attr, paramValStr, paramName))
        {
            delete[] cmdParam;
            return FLINT_FAILED;
        }
        if (!((Flash*)_io)->set_attr(paramName, paramValStr, attr))
        {
            delete[] cmdParam;
            reportErr(true, FLINT_HW_COMMAND_ERROR, "set", _io->err());
            return FLINT_FAILED;
        }
        printf("-I- %s parameter was set successfully\n", paramName);
        delete[] cmdParam;
    }
    else
    {
        ext_flash_attr_t attr;
        attr.type_str = (char*)NULL;
        if (!((Flash*)_io)->get_attr(attr))
        {
            reportErr(true, FLINT_HW_COMMAND_ERROR, "query", _io->err());
            if (attr.type_str)
            {
                delete[] attr.type_str;
            }
            return FLINT_FAILED;
        }
        FlintStatus rc = printAttr(attr);
        // str is allocated in get_attr
        if (attr.type_str)
        {
            delete[] attr.type_str;
        }
        if (rc == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
    }
    return FLINT_SUCCESS;
}

/**************************
 * Class: Erase SubCommand
 *************************/
EraseSubCommand::EraseSubCommand()
{
    _name = "erase";
    _desc = "Erases sector.";
    _extendedDesc = "Erases a sector that contains specified address.";
    _flagLong = "erase";
    _flagShort = "e";
    _param = "<addr>";
    _paramExp = "addr - address of word in sector that you want to erase.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " erase 0x10000";
    _v = Wtv_Dev;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Erase;
}

EraseSubCommand::~EraseSubCommand() {}

FlintStatus EraseSubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char* endp;
    // Address of sector to erase
    addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    // Erase
    if (!((Flash*)_io)->erase_sector(addr))
    {
        reportErr(true, FLINT_ERASE_SEC_ERROR, _io->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/*****************************
 * Class: Read Dword SubCommand
 *****************************/
RwSubCommand::RwSubCommand()
{
    _name = "rw";
    _desc = "Read one dword from flash";
    _extendedDesc = "Read one dword from flash.";
    _flagLong = "rw";
    _flagShort = "";
    _param = "<addr>";
    _paramExp = "addr - address of word to read";
    _example = "flint -d " MST_DEV_EXAMPLE1 " rw 0x20";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Rw;
}

RwSubCommand::~RwSubCommand() {}

FlintStatus RwSubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char* endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    if (_flintParams.device_specified ? !((Flash*)_io)->read(addr, &data) : !((FImage*)_io)->read(addr, &data))
    {
        reportErr(true, FLINT_FLASH_READ_ERROR, _io->err());
        return FLINT_FAILED;
    }
    printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));
    return FLINT_SUCCESS;
}

/******************************
 * Class: Write Dword Subcommand
 ******************************/
WwSubCommand::WwSubCommand()
{
    _name = "ww";
    _desc = "Write one dword to flash";
    _extendedDesc = "Write one dword to flash.\n"
                    "Note that the utility will read an entire flash sector,"
                    " modify one word and write the sector back. This may take a few seconds.";
    _flagLong = "ww";
    _flagShort = "";
    _param = "<addr> <data>";
    _paramExp = "addr - address of word\n"
                "data - value of word";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " ww 0x10008 0x5a445a44";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 2;
    _cmdType = SC_Ww;
}

WwSubCommand::~WwSubCommand() {}

FlintStatus WwSubCommand::executeCommand()
{
    // init fw operation object
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char* dataStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    char* endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    data = strtoul(dataStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_DATA_ERROR, _flintParams.cmd_params[1].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    delete[] dataStr;
    data = __cpu_to_be32(data);
    // TODO - align below write function for Flash and FImage classes
    if (_io->is_flash())
    {
        if (!((Flash*)_io)->write(addr, data))
        {
            reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
            return FLINT_FAILED;
        }
    }
    else
    {
        if (!_io->write(addr, &data, 0x4))
        {
            reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
            return FLINT_FAILED;
        }
    }
    return FLINT_SUCCESS;
}
/***************************************
 * Class: Write Dword No Erase SubCommand
 ***************************************/
WwneSubCommand::WwneSubCommand()
{
    _name = "wwne";
    _desc = "Write one dword to flash without sector erase";
    _extendedDesc = "Write one dword to flash without sector erase.\n"
                    "Note that the result of operation is undefined and depends on flash type."
                    " Usually \"bitwise AND\" (&) between specified word and previous flash contents will be"
                    " written to specified address.";
    _flagLong = "wwne";
    _flagShort = "";
    _param = "<addr> <data>";
    _paramExp = "addr - address of word\n"
                "data - value of word";
    _example = "flint -d " MST_DEV_EXAMPLE1 " wwne 0x10008 0x5a445a44";
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 2;
    _cmdType = SC_Wwne;
}

WwneSubCommand::~WwneSubCommand() {}

FlintStatus WwneSubCommand::executeCommand()
{
    // init fw operation object
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char* dataStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    char* endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    data = strtoul(dataStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_DATA_ERROR, _flintParams.cmd_params[1].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    delete[] dataStr;
    data = __cpu_to_be32(data);
    if (!((Flash*)_io)->write(addr, &data, 4, true))
    {
        reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/**************************************
 * Class:Write Block  SubCommand
 **************************************/
WbSubCommand::WbSubCommand()
{
    _name = "wb";
    _desc = "Write a data block to flash.";
    _extendedDesc = "Write a block of data to the flash.";
    _flagLong = "wb";
    _flagShort = "";
    _param = "<data-file> <addr>";
    _paramExp = "data-file - file that contains the data to be written\n"
                "addr - address to write the block to\n";

    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " wb myData.bin 0x0";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 2;
    _cmdType = SC_Wb;
}

WbSubCommand::~WbSubCommand() {}

bool WbSubCommand::extractData(const std::vector<string>& cmdParams, u_int32_t* addr, std::vector<u_int8_t>& data)
{
    // get address
    char* endp;
    char* addrStr = strcpy(new char[cmdParams[1].size() + 1], cmdParams[1].c_str());
    *addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, cmdParams[1].c_str());
        delete[] addrStr;
        return false;
    }
    delete[] addrStr;
    // get data
    FImage img;
    if (!img.open(cmdParams[0].c_str()))
    {
        reportErr(true, FLINT_WB_FILE_ERROR, cmdParams[0].c_str(), img.err());
        return false;
    }
    // copy data to vector
    data.resize(img.getBufLength());
    if (!img.getBuf())
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, img.err());
        return false;
    }
    memcpy(&data[0], img.getBuf(), img.getBufLength());

    return true;
}

FlintStatus WbSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    std::vector<u_int8_t> data;
    if (!extractData(_flintParams.cmd_params, &addr, data))
    {
        return FLINT_FAILED;
    }
    // printf("-D- writing to addr:0x%08x %lu bytes\n",addr , data.size());
    FwOperations* ops;
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    if (!ops->FwWriteBlock(addr, data, wbCbFunc))
    {
        reportErr(true, FLINT_WB_ERROR, ops->err());
        return FLINT_FAILED;
    }
    wbCbFunc(101);
    return FLINT_SUCCESS;
}

/**************************************
 * Class:Write Block No Erase SubCommand
 **************************************/
WbneSubCommand::WbneSubCommand()
{
    _name = "wbne";
    _desc = "Write a data block to flash without sector erase.";
    _extendedDesc = "Write a block of data to the flash without erasing.";
    _flagLong = "wbne";
    _flagShort = "";
    _param = "<addr> <size> <data ...>";
    _paramExp = "addr - address of block\n"
                "size - size of data to write in bytes\n"
                "data - data to write - space separated dwords";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " wbne 0x10000 12 0x30000 0x76800 0x5a445a44";
    _v = Wtv_Dev;
    _minCmdParamNum = 3;
    _cmdType = SC_Wbne;
}

WbneSubCommand::~WbneSubCommand() {}

bool WbneSubCommand::writeBlock(u_int32_t addr, std::vector<u_int32_t> dataVec)
{
    // we should work only on flash.
    // check if flash is big enough
    if (addr + (dataVec.size() * 4) > ((Flash*)_io)->get_effective_size())
    {
        reportErr(true, "Writing %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                  (unsigned int)(dataVec.size() * 4), (unsigned int)addr, (unsigned int)_io->get_effective_size());
        return false;
    }
    if (!((Flash*)_io)->write(addr, &dataVec[0], (dataVec.size() * 4), true))
    {
        reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
        return false;
    }
    return true;
}

bool WbneSubCommand::extractData(const std::vector<string>& cmdParams, u_int32_t* addr, std::vector<u_int32_t>& data)
{
    char* endp;
    char* addrStr = strcpy(new char[cmdParams[0].size() + 1], cmdParams[0].c_str());
    *addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, cmdParams[0].c_str());
        delete[] addrStr;
        return false;
    }
    delete[] addrStr;
    char* sizeStr = strcpy(new char[cmdParams[1].size() + 1], cmdParams[1].c_str());
    u_int32_t size = strtoul(sizeStr, &endp, 0);
    if (*endp || size % 4 || size / 4 != (cmdParams.size() - 2))
    {
        reportErr(true, FLINT_INVALID_SIZE_ERROR, sizeStr);
        delete[] sizeStr;
        return false;
    }
    delete[] sizeStr;
    for (u_int32_t i = 2; i < cmdParams.size(); i++)
    {
        char* dataStr = strcpy(new char[cmdParams[i].size() + 1], cmdParams[i].c_str());
        data.push_back(__cpu_to_be32(strtoul(dataStr, &endp, 0)));
        if (*endp)
        {
            reportErr(true, FLINT_INVALID_DATA_ERROR, dataStr);
            delete[] dataStr;
            return false;
        }
        delete[] dataStr;
    }
    return true;
}

FlintStatus WbneSubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    std::vector<u_int32_t> data;
    if (!extractData(_flintParams.cmd_params, &addr, data))
    {
        return FLINT_FAILED;
    }
    // printf("-D- writing to addr:0x%08x %lu bytes\n",addr , data.size()*4);
    if (!writeBlock(addr, data))
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: ReadBlock
 **********************/
RbSubCommand::RbSubCommand()
{
    _name = "rb";
    _desc = "Read  a data block from flash";
    _extendedDesc = "Read a data block from the flash and write it to a file or to screen.";
    _flagLong = "rb";
    _flagShort = "";
    _param = "<addr> <size> <out-file>";
    _paramExp = "addr - address of block\n"
                "size - size of data to read in bytes\n"
                "file - filename to write the block (raw binary). If not given, the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " rb 0x10000 100 file.bin";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 3;
    _minCmdParamNum = 2;
    _cmdType = SC_Rb;
}

RbSubCommand::~RbSubCommand() {}

bool RbSubCommand::readBlock(u_int32_t addr, std::vector<u_int8_t>& buff, bool isFlash)
{
    FwOperations* ops = isFlash ? _fwOps : _imgOps;
    if (!ops->FwReadBlock(addr, buff.size(), buff))
    {
        reportErr(true, FLINT_IMAGE_READ_ERROR, ops->err());
        return false;
    }
    return true;
}

bool RbSubCommand::printToScreen(const std::vector<u_int8_t>& buff, bool hexdump_format)
{
    if (hexdump_format)
    {
        for (u_int32_t i = 0; i < buff.size(); i += 16)
        {
            // Print addr
            printf("%08x  ", i);
            // Print bytes
            for (u_int32_t j = 0; (j < 16) && (i + j < buff.size()); j++)
            {
                printf("%02x ", buff[i + j]);
                if (j == 7)
                    printf(" ");
            }
            // Print ASCII
            printf(" |");
            for (u_int32_t j = 0; (j < 16) && (i + j < buff.size()); j++)
            {
                printf("%c", isprint(buff[i + j]) ? buff[i + j] : '.');
            }
            // Print new line
            printf("|\n");
        }
    }
    else
    {
        for (u_int32_t i = 0; i < buff.size(); i += 4)
        {
            u_int32_t word = *((u_int32_t*)(&buff[0] + i));
            word = __be32_to_cpu(word);
            printf("0x%08x ", word);
        }
    }
    printf("\n");
    return true;
}

FlintStatus RbSubCommand::executeCommand()
{
    // init fw operation object
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    bool wTF = _flintParams.cmd_params.size() == 3 ? true : false;
    // extract address and size to read from cmdline
    u_int32_t addr;
    u_int32_t size;
    char* endp;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    addr = strtoul(addrStr, &endp, 0);
    if (*endp)
    {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    char* sizeStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    size = strtoul(sizeStr, &endp, 0);
    if (*endp || size % 4)
    {
        reportErr(true, FLINT_INVALID_SIZE_ERROR, sizeStr);
        delete[] sizeStr;
        return FLINT_FAILED;
    }
    delete[] sizeStr;
    // init byte vector and fill it with data
    std::vector<u_int8_t> data(size);
    if (!readBlock(addr, data, _flintParams.device_specified))
    {
        return FLINT_FAILED;
    }
    // print either to file or to screen
    FlintStatus rc;
    if (wTF)
    {
        rc = writeToFile(_flintParams.cmd_params[2], data) == true ? FLINT_SUCCESS : FLINT_FAILED;
    }
    else
    {
        rc = printToScreen(data, _flintParams.hexdump_format) == true ? FLINT_SUCCESS : FLINT_FAILED;
    }
    return rc;
}

/***********************
 * Class: ClearSemaphore
 **********************/
ClearSemSubCommand::ClearSemSubCommand()
{
    _name = "clear_semaphore";
    _desc = "Clear flash semaphore.";
    _extendedDesc = "Clear flash semaphore.";
    _flagLong = "clear_semaphore";
    _flagShort = "";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -clear_semaphore";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_Clear_Sem;
}

ClearSemSubCommand::~ClearSemSubCommand() {}

FlintStatus ClearSemSubCommand::executeCommand()
{
    _flintParams.clear_semaphore = true;
    return preFwAccess();
}

/***********************
 * Class: RomQuery
 **********************/
RomQuerySubCommand::RomQuerySubCommand()
{
    _name = "qrom";
    _desc = "query ROM image.";
    _extendedDesc = "query ROM image.";
    _flagLong = "qrom";
    _flagShort = "";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -i ROM_image.bin qrom ";
    _v = Wtv_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Qrom;
    memset(&_romsInfo, 0, sizeof(_romsInfo));
}

RomQuerySubCommand::~RomQuerySubCommand() {}

FlintStatus RomQuerySubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    getRomsInfo(_io, _romsInfo);
    if (_romsInfo.exp_rom_err_msg_valid != 0)
    {
        reportErr(true, FLINT_ROM_QUERY_ERROR, _flintParams.image.c_str(), _romsInfo.exp_rom_err_msg);
        return FLINT_FAILED;
    }
    displayExpRomInfo(_romsInfo, "Rom Info: ");
    return FLINT_SUCCESS;
}

/***********************
 * Class: ResetCfg
 **********************/
ResetCfgSubCommand::ResetCfgSubCommand()
{
    _name = "reset_cfg";
    _desc = "reset non-volatile configuration.";
    _extendedDesc = "reset non-volatile configuration to their default value.";
    _flagLong = "reset_cfg";
    _flagShort = "r";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " reset_cfg";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_ResetCfg;
}

ResetCfgSubCommand::~ResetCfgSubCommand() {}

FlintStatus ResetCfgSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    printf("-W- Resetting device configuration using Flint should be done as a last resort.\n");
    printf("-W- Please attempt to reset configuration via mlxconfig tool if possible.\n");
    printf("-W- Only proceed if you know what you are doing.\n");
    if (!askUser("reset non-volatile configuration"))
    {
        return FLINT_FAILED;
    }

    printf("Resetting...");
    if (!_fwOps->FwResetNvData())
    {
        printf(" Failed!\n");
        reportErr(true, FLINT_RESET_CFG_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf(" SUCCESS!\n");
    printf("\n-I- Configuration were successfully reset. reboot or restart the driver is required.\n");

    return FLINT_SUCCESS;
}

/***********************
 * Class: FixImage
 **********************/
FiSubCommand::FiSubCommand()
{
    _name = "fix image";
    _desc = "fix image on N25Q0XX flash.";
    _extendedDesc = "fix image on N25Q0XX flash.(shifting all device data sectors)";
    _flagLong = "fi";
    _flagShort = "";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " fi";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_Fix_Img;
}

FiSubCommand::~FiSubCommand() {}

FlintStatus FiSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    if (!askUser("Fix device fw?"))
    {
        return FLINT_FAILED;
    }

    if (!_fwOps->FwShiftDevData(&verifyCbFunc))
    {
        reportErr(true, FLINT_FIX_IMG_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf("\n-I- Fw was successfully fixed. reboot or restart the driver is required.\n");
    return FLINT_SUCCESS;
}

/***********************
 * Class: CheckSum
 **********************/
CheckSumSubCommand::CheckSumSubCommand()
{
    _name = "checksum";
    _desc = "perform MD5 checksum on FW.";
    _extendedDesc = "perform an MD5 checksum on relevant(non-persistent between FW upgrades) data on device/image.";
    _flagLong = "checksum";
    _flagShort = "cs";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " checksum";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Check_Sum;
    memset(_checkSum, 0, sizeof(_checkSum));
}

CheckSumSubCommand::~CheckSumSubCommand() {}

bool CheckSumSubCommand::extractChecksumFromStr(string str, u_int8_t checkSum[16])
{
    char ptr[2];
    int i = 15;
    if (str.size() < 2)
    {
        reportErr(true, FLINT_CHECKSUM_LEN_ERROR);
        return false;
    }
    if (!strncasecmp(str.c_str(), "0x", 2))
    {
        // str starts with 0x or 0X, remove prefix
        str = &(str.c_str()[2]);
    }

    if (str.size() != 32)
    {
        reportErr(true, FLINT_CHECKSUM_LEN_ERROR);
        return false;
    }
    stringstream ss(str);
    while (i >= 0)
    {
        ss.read(ptr, 2);
        if (!isxdigit(ptr[0]) || !isxdigit(ptr[1]))
        {
            reportErr(true, FLINT_CHECKSUM_HEX_ERROR);
            return false;
        }
        checkSum[i] = (u_int8_t)strtoul(ptr, NULL, 16);
        if (!checkSum[i] && strncmp(ptr, "00", 2))
        {
            reportErr(true, FLINT_CHECKSUM_PARSE_ERROR);
            return false;
        }
        i--;
    }
    return true;
}

string CheckSumSubCommand::checkSum2Str(u_int8_t chksm[16])
{
    stringstream ss;
    for (int i = 15; i >= 0; i--)
    {
        char chunk[3];
        snprintf(chunk, 3, "%02x", chksm[i]);
        ss << chunk;
    }
    string s = ss.str();
    return s;
}

FlintStatus CheckSumSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    FwOperations* ops = _fwOps ? _fwOps : _imgOps;
    printf("-I- Calculating Checksum ...\n");
    if (!ops->FwCalcMD5(_checkSum))
    {
        reportErr(true, FLINT_CHECKSUM_ERROR, (_flintParams.device_specified ? "device" : "image"), ops->err());
        return FLINT_FAILED;
    }
    // just print it!
    printf("Checksum: %s\n", checkSum2Str(_checkSum).c_str());
    return FLINT_SUCCESS;
}

/***********************
 * Class: TimeStamp
 **********************/
TimeStampSubCommand::TimeStampSubCommand()
{
    _name = "time stamp";
    _desc = "<timestamp> <FW version>  FW time stamping.";
    _extendedDesc = "set/query/reset time stamp on device/image.";
    _flagLong = "timestamp";
    _flagShort = "ts";
    _param = "[set/query/reset] ";
    _paramExp =
      "set <timestamp> [FW version] : set the specified timestamp. if set on device FW version must be specified\n"
      "timestamp should comply with ISO 8601 format and provided with UTC timezone: YYYY-MM-DDThh:mm:ssZ\n"
      "query : query device/image to view the timestamp\n"
      "reset : reset the timestamp, remove the timestamp from device/image.\n";
    _example =
      FLINT_NAME " -d " MST_DEV_EXAMPLE4 " ts set 2015-12-24T14:52:33Z 14.12.1100\n" FLINT_NAME " -d " MST_DEV_EXAMPLE4
                 " ts reset\n" FLINT_NAME " -i ./fw4115.bin ts set\n" FLINT_NAME " -i ./fw4115.bin ts query";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 3;
    _minCmdParamNum = 1;
    _cmdType = SC_Time_Stamp;
    memset(&_userFwVer, 0, sizeof(_userFwVer));
    memset(&_userTsEntry, 0, sizeof(_userTsEntry));
    _operation = TS_No_Command;
    _ops = (FwOperations*)NULL;
    _mccSupported = true;
}

TimeStampSubCommand::~TimeStampSubCommand() {}
bool TimeStampSubCommand::parseFwVersion(string verStr)
{
    unsigned int major = 0;
    unsigned int minor = 0;
    unsigned int subminor = 0;
    int count = sscanf(verStr.c_str(), "%02d.%02d.%04d", &major, &minor, &subminor);
    if (count != 3)
    {
        count = sscanf(verStr.c_str(), "%02d.%04d.%04d", &major, &minor, &subminor);
        if (count != 3)
        {
            reportErr(true, "Failed to parse FW version. expected format: MM.mm.ssss\n");
            return false;
        }
    }
    _userFwVer.fw_ver_major = major;
    _userFwVer.fw_ver_minor = minor;
    _userFwVer.fw_ver_subminor = subminor;
    // printf("-D- Fw version: %d.%d.%d\n", _userFwVer.fw_ver_major, _userFwVer.fw_ver_minor,
    // _userFwVer.fw_ver_subminor);
    return true;
}

#define BCD2_TO_NUM(bcd) ((((bcd) >> 4 & 0xf) * 10) + ((bcd)&0xf))

#define BCD4_TO_NUM(bcd) ((BCD2_TO_NUM((bcd) >> 8 & 0xff) * 100) + (BCD2_TO_NUM((bcd)&0xff)))

#define NUM2_TO_BCD(num) ((((num) / 10) * 16) + ((num) % 10))

#define NUM4_TO_BCD(num) ((NUM2_TO_BCD((num) / 100) * 256) + NUM2_TO_BCD((num) % 100))

u_int8_t TimeStampSubCommand::getDaysInMonth(u_int16_t year, u_int8_t month)
{
    u_int8_t days = 0;
    bool isLeapYear = year % 4 == 0;                      // evenly divisible by 4
    isLeapYear &= (year % 100 != 0) || (year % 400 == 0); // not evenly divided by 100 or  evenly divisible by 400
    switch (month)
    {
        case 2:
            days = isLeapYear ? 29 : 28;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;

        default:
            break;
    }
    return days;
}

void TimeStampSubCommand::getMachineUTCTime()
{
    time_t rawTime;
    struct tm* timeInfo;
    time(&rawTime);
    timeInfo = gmtime(&rawTime);
    if (!timeInfo)
    {
        reportErr(true, "gmtime returned NULL. Can't get machine's UTC time.");
        return;
    }

    _userTsEntry.ts_year = NUM4_TO_BCD(timeInfo->tm_year + 1900);
    _userTsEntry.ts_month = NUM2_TO_BCD(timeInfo->tm_mon + 1);
    _userTsEntry.ts_day = NUM2_TO_BCD(timeInfo->tm_mday);
    _userTsEntry.ts_hour = NUM2_TO_BCD(timeInfo->tm_hour);
    _userTsEntry.ts_minutes = NUM2_TO_BCD(timeInfo->tm_min);
    _userTsEntry.ts_seconds = NUM2_TO_BCD(timeInfo->tm_sec);

    // printf("-D- timestamp: %04x-%02x-%02xT%02x:%02x:%02x\n", _userTsEntry.ts_year, _userTsEntry.ts_month,
    //                                                        _userTsEntry.ts_day, _userTsEntry.ts_hour,
    //                                                        _userTsEntry.ts_minutes, _userTsEntry.ts_seconds);
    return;
}

bool TimeStampSubCommand::parseTimeStamp(string tsStr)
{
    unsigned int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;
    unsigned int hour = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;
    if (*tsStr.rbegin() != 'Z')
    {
        reportErr(
          true, "Failed to parse timestamp: Timestamp timezone must be UTC. format should be: YYYY-MM-DDThh:mm:ssZ\n");
        return false;
    }
    // scan and store
    int count = sscanf(tsStr.c_str(), "%04d-%02d-%02dT%02d:%02d:%02dZ", &year, &month, &day, &hour, &minutes, &seconds);
    if (count != 6)
    {
        reportErr(true, "Failed to parse timestamp: input should be compliant to the following ISO 8601 format: "
                        "YYYY-MM-DDThh:mm:ssZ\n");
        return false;
    }
    // check time args
    if (month == 0 || month > 12)
    {
        reportErr(true, "Failed to parse timestamp: illegal month value (%d)\n", month);
        return false;
    }
    if (day > getDaysInMonth(year, month))
    {
        reportErr(true, "Failed to parse timestamp: illegal day value (%d)\n", day);
        return false;
    }
    if (hour > 23 || minutes > 59 || seconds > 59)
    {
        reportErr(true, "Failed to parse timestamp: illegal time value (%02d:%02d:%02d)\n", hour, minutes, seconds);
        return false;
    }
    // store as BCD
    _userTsEntry.ts_year = NUM4_TO_BCD(year);
    _userTsEntry.ts_month = NUM2_TO_BCD(month);
    _userTsEntry.ts_day = NUM2_TO_BCD(day);
    _userTsEntry.ts_hour = NUM2_TO_BCD(hour);
    _userTsEntry.ts_minutes = NUM2_TO_BCD(minutes);
    _userTsEntry.ts_seconds = NUM2_TO_BCD(seconds);

    // printf("-D- timestamp: %04x-%02x-%02xT%02x:%02x:%02x\n", _userTsEntry.ts_year, _userTsEntry.ts_month,
    //                                                        _userTsEntry.ts_day, _userTsEntry.ts_hour,
    //                                                        _userTsEntry.ts_minutes, _userTsEntry.ts_seconds);
    return true;
}

bool TimeStampSubCommand::verifyParams()
{
    if (_flintParams.cmd_params[0] == "query")
    {
        if (_flintParams.cmd_params.size() > 1)
        {
            reportErr(true, "query operation requires no arguments.\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Query;
    }
    else if (_flintParams.cmd_params[0] == "set")
    {
        if (_flintParams.image_specified && _flintParams.cmd_params.size() > 2)
        {
            reportErr(true, "too many arguments for set operation on image.\n");
            return false;
        }
        else if (_flintParams.device_specified && _flintParams.cmd_params.size() != 3)
        {
            reportErr(true, "set operation on device requires timestamp and FW version arguments.\n\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Set;
        // attempt to parse timestamp and fw version
        if (_flintParams.image_specified && _flintParams.cmd_params.size() == 1)
        {
            // take time from machine
            getMachineUTCTime();
        }
        else if (!parseTimeStamp(_flintParams.cmd_params[1]))
        {
            return false;
        }
        if (_flintParams.device_specified && !parseFwVersion(_flintParams.cmd_params[2]))
        {
            return false;
        }
    }
    else if (_flintParams.cmd_params[0] == "reset")
    {
        if (_flintParams.cmd_params.size() > 1)
        {
            reportErr(true, "erase operation requires no arguments.\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Reset;
    }
    else
    {
        reportErr(true, "Unknown operation, allowed operations: query/set/reset.\n");
        return false;
    }
    return true;
}

void TimeStampSubCommand::printTsAndFwVer(string prefix,
                                          struct tools_open_ts_entry& tsEntry,
                                          struct tools_open_fw_version& fwVer)
{
    printf("%-24s: %04x-%02x-%02xT%02x:%02x:%02xZ    %02d.%02d.%04d\n", prefix.c_str(), tsEntry.ts_year,
           tsEntry.ts_month, tsEntry.ts_day, tsEntry.ts_hour, tsEntry.ts_minutes, tsEntry.ts_seconds,
           fwVer.fw_ver_major, fwVer.fw_ver_minor, fwVer.fw_ver_subminor);
}

bool TimeStampSubCommand::queryTs()
{
    struct tools_open_ts_entry tsEntry;
    struct tools_open_fw_version fwVer;
    memset(&tsEntry, 0, sizeof(tsEntry));
    memset(&fwVer, 0, sizeof(fwVer));
    // get and Print Current Running FW TS in case of device
    if (_flintParams.device_specified)
    {
        if (!_ops->FwQueryTimeStamp(tsEntry, fwVer, true))
        {
            printf("%-24s: N/A. %s\n", "Current timestamp", _ops->err());
        }
        else
        {
            printTsAndFwVer("Current timestamp", tsEntry, fwVer);
        }
    }
    // get and print next FW timestamp
    if (!_ops->FwQueryTimeStamp(tsEntry, fwVer, false))
    {
        printf("%-24s: N/A. %s\n", "Next timestamp", _ops->err());
    }
    else
    {
        printTsAndFwVer("Next timestamp", tsEntry, fwVer);
    }
    return true;
}

bool TimeStampSubCommand::setTs()
{
    if (!_ops->FwSetTimeStamp(_userTsEntry, _userFwVer))
    {
        reportErr(false, "%s", _ops->err());
        return false;
    }
    return true;
}

bool TimeStampSubCommand::resetTs()
{
    if (!_ops->FwResetTimeStamp())
    {
        reportErr(false, "%s", _ops->err());
        return false;
    }
    return true;
}

FlintStatus TimeStampSubCommand::executeCommand()
{
    bool rc;
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    fw_info_t fwInfo;
    if (!_ops->FwQuery(&fwInfo))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, _flintParams.device_specified ? "Device" : "Image",
                  _flintParams.device_specified ? _flintParams.device.c_str() : _flintParams.image.c_str(),
                  _ops->err());
        return FLINT_FAILED;
    }
    chip_type_t chip = fwInfo.fw_info.chip_type;
    bool IsValidDevice = (chip == CT_CONNECTX4 || chip == CT_CONNECTX4_LX);

    switch (_operation)
    {
        case TimeStampSubCommand::TS_Set:
            if (!IsValidDevice)
            {
                reportErr(true, "Failed to perform timestamp set operation. Failed to set timestamp. Time stamping not "
                                "supported by FW.\n");
                return FLINT_FAILED;
            }
            rc = setTs();
            break;

        case TimeStampSubCommand::TS_Query:
            if (!IsValidDevice)
            {
                printf("Current timestamp : N/A. Failed to query timestamp. Time stamping not supported by FW.\n");
                printf("Next timestamp :    N/A. Failed to query timestamp. Time stamping not supported by FW.\n");
                return FLINT_FAILED;
            }
            rc = queryTs();
            break;

        case TimeStampSubCommand::TS_Reset:
            if (!IsValidDevice)
            {
                reportErr(true, "Failed to perform timestamp reset operation. Failed to reset timestamp. Time stamping "
                                "not supported by FW.\n");
                return FLINT_FAILED;
            }
            rc = resetTs();
            break;

        default:
            // should not be reached
            reportErr(true, "Failed to perform timestamp operation: Unknown Error\n");
            return FLINT_FAILED;
    }
    if (!rc)
    {
        printf("-E- Failed to perform timestamp %s operation. %s\n", _flintParams.cmd_params[0].c_str(), _errBuff);
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: CacheImage
 **********************/
CacheImageSubCommand::CacheImageSubCommand()
{
    _name = "cache image";
    _desc = "cache FW image(Windows only).";
    _extendedDesc =
      "cache the FW image using Mellanox driver to allow faster FW load time upon loading the driver(Windows only).";
    _flagLong = "cache_image";
    _flagShort = "ci";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " cache_image";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _minCmdParamNum = 0;
    _cmdType = SC_Cache_Image;
}

CacheImageSubCommand::~CacheImageSubCommand() {}

FlintStatus CacheImageSubCommand::executeCommand()
{
#ifdef __WIN__
    int rc;

    if (preFwAccess() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }
    rc = wdcif_send_image_cache_request(((Flash*)_io)->getMfileObj());
    if (rc)
    {
        reportErr(true, FLINT_CACHE_IMAGE_ERROR, wdcif_err_str(rc));
        return FLINT_FAILED;
    }
    printf("\n-I- FW was successfully cached by driver.\n");
    return FLINT_SUCCESS;
#else
    reportErr(true, FLINT_WIN_ONLY_SUPP_ERROR, _name.c_str());
    return FLINT_FAILED;
#endif
}

FlintStatus SubCommand::LockDevice(FwOperations* fwOps)
{
#ifdef __WIN__
    // relevant only on devices
    if (_flintParams.device_specified)
    {
        if (fwOps->FwType() == FIT_FS3 || fwOps->FwType() == FIT_FS4 || fwOps->FwType() == FIT_FSCTRL)
        {
            mfile* mFile = fwOps->getMfileObj();
            if (m_ToolsSync.init(mFile) != TOOLS_SYNC_OK)
            {
                reportErr(true, "Flint can't continue - prevention issue. Please try again later.");
                return FLINT_FAILED;
            }
        }
    }
#else
    (void)fwOps;
#endif
    return FLINT_SUCCESS;
}

FlintStatus SubCommand::UnlockDevice(FwOperations* fwOps)
{
#ifdef __WIN__
    // relevant only on devices
    if (_flintParams.device_specified)
    {
        if (fwOps->FwType() == FIT_FS3 || fwOps->FwType() == FIT_FS4 || fwOps->FwType() == FIT_FSCTRL)
        {
            if (m_ToolsSync.close() != NAMED_SYNC_OK)
            {
                reportErr(true, "Prevention cannot unlock device.");
                return FLINT_FAILED;
            }
        }
    }
#else
    (void)fwOps;
#endif
    return FLINT_SUCCESS;
}

#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
/***********************
 * Class: ExportPublicSubCommand
 ***********************/
ExportPublicSubCommand::ExportPublicSubCommand()
{
    _name = "export_public_key";
    _desc = "Export public key from PEM file or BIN file";
    _extendedDesc = "Export public key from PEM file or BIN file";
    _flagLong = "export_public_key";
    _flagShort = "";
    _paramExp = "None";
    _example = FLINT_NAME "[--private_key file.pem --key_uuid uuid string] OR -i <BIN file> --output_file <filename> ";
    _v = Wtv_Uninitilized;
    _maxCmdParamNum = 0;
    _cmdType = SC_Sign;
}

ExportPublicSubCommand::~ExportPublicSubCommand() {}

bool ExportPublicSubCommand::verifyParams()
{
    if (_flintParams.privkey_file.empty() && _flintParams.image_specified == false)
    {
        reportErr(true,
                  "Incorrect input. To export the public key you must provide private key PEM file OR BIN file.\n");
        return false;
    }
    if (!_flintParams.privkey_file.empty() && _flintParams.image_specified == true)
    {
        reportErr(true, "Incorrect input. To export the public key you must provide private key [PEM file AND UUID "
                        "string] OR BIN file.\n");
        return false;
    }
    if (_flintParams.output_file_specified == false)
    {
        reportErr(true, "Incorrect input. To export the public key you must provide output file name.\n");
        return false;
    }
    if (!_flintParams.privkey_file.empty())
    {
        if (!is_file_exists(_flintParams.privkey_file.c_str()))
        {
            reportErr(true, "Incorrect input. Can't find private key file %s \n", _flintParams.privkey_file.c_str());
            return false;
        }
        if (_flintParams.privkey_uuid.empty())
        {
            reportErr(true, "Incorrect input. To export the public key you must provide [private key PEM file AND UUID "
                            "string].UUID string is missing.\n");
            return false;
        }
        for (string::const_iterator it = _flintParams.privkey_uuid.begin(); it != _flintParams.privkey_uuid.end(); ++it)
        {
            if (!isxdigit(*it))
            {
                reportErr(true, "Bad UUID format. UUID string must contain hexadecimal digits only.\n");
                return false;
            }
        }
        if (_flintParams.privkey_uuid.size() != UUID_LEN * 2)
        {
            reportErr(true, "Incorrect input. The size of UUID string must be exactly %u bytes.\n", UUID_LEN * 2);
            return false;
        }
    }
    else if (_flintParams.image_specified == true)
    {
        if (!is_file_exists(_flintParams.image.c_str()))
        {
            reportErr(true, "Can't find BIN file %s \n", _flintParams.image.c_str());
            return false;
        }
        if (!_flintParams.privkey_uuid.empty())
        {
            reportErr(true, "To export the public key from the BIN you should not provide [UUID string].UUID string is "
                            "extracted from the BIN file.\n");
            return false;
        }
    }
    return true;
}

FlintStatus ExportPublicSubCommand::executeCommand()
{
    vector<unsigned char> resultBuffer;
    if (!_flintParams.privkey_file.empty())
    { // working with PEM file
        if (!verifyParams())
        {
            return FLINT_FAILED;
        }
        vector<unsigned char> outputBuffer;
        bool IsPemFile8Format = false;
        u_int32_t keySize = 0;
        string PemFile = _flintParams.privkey_file;
        if (!FwOperations::CheckPemKeySize(PemFile, keySize))
        {
            reportErr(true, "Cannot parse the PEM file!\n");
            return FLINT_FAILED;
        }
        if (keySize != 512)
        {
            reportErr(true, "The PEM file has to be 4096 bit!\n");
            return FLINT_FAILED;
        }
        Hex64Manipulations hex64;
        if (hex64.ParsePemFile(PemFile, outputBuffer, IsPemFile8Format) == false)
        {
            reportErr(true, "Cannot parse the PEM file!\n");
            return FLINT_FAILED;
        }
        resultBuffer.resize(TOTAL_PUBLIC_KEY_SIZE);
        if (IsPemFile8Format)
        {
            for (unsigned int i = MODULUS_OFFSET; i < MODULUS_OFFSET + MODULUS_SIZE; i++)
            {
                resultBuffer[i - MODULUS_OFFSET + 20] = outputBuffer[i];
            }
        }
        else
        {
            for (unsigned int i = 12; i < 524; i++)
            {
                resultBuffer[i + 8] = outputBuffer[i];
            }
        }
        resultBuffer[0] = 0;
        resultBuffer[1] = 1;
        resultBuffer[2] = 0;
        resultBuffer[3] = 1;
        string strData = _flintParams.privkey_uuid;
        for (size_t i = 0; i < UUID_LEN * 2; i += 2)
        {
            char tmpBuf[3] = {0};
            tmpBuf[0] = strData[i];
            tmpBuf[1] = strData[i + 1];
            unsigned int dwData = 0;
            sscanf(tmpBuf, "%x", &dwData);
            resultBuffer[i / 2 + 4] = (u_int8_t)dwData;
        }
    }
    else
    { // working with the BIN file
        if (preFwOps() == FLINT_FAILED)
        {
            return FLINT_FAILED;
        }
        if (_imgOps->FwType() != FIT_FS4)
        {
            reportErr(true, "Extracting public key is applicable only for FS4 FW.\n");
            return FLINT_FAILED;
        }
        if (!_imgOps->GetRSAPublicKey(resultBuffer))
        {
            reportErr(true, "Extracting public key failed - %s.\n", _imgOps->err());
            return FLINT_FAILED;
        }
        resultBuffer.resize(TOTAL_PUBLIC_KEY_SIZE);
    }
    writeToFile(_flintParams.output_file, resultBuffer);
    return FLINT_SUCCESS;
}
#endif


/***********************
 * Class: QueryBfbComponentsSubCommand
 ***********************/
QueryBfbComponentsSubCommand::QueryBfbComponentsSubCommand()
{
    _name = "query_bfb_components";
    _desc = "Query BFB components version";
    _extendedDesc = "Query and display information about BFB components in the device";
    _flagLong = "query_bfb_components";
    _flagShort = "qbfb";
    _param = "";
    _paramExp = "";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " query_bfb_components";
    _v = Wtv_Dev;
    _maxCmdParamNum = 0;
    _cmdType = SC_Query_Bfb_Components;
    _mccSupported = true;
    _pending = false;
};

QueryBfbComponentsSubCommand::~QueryBfbComponentsSubCommand() {}

FlintStatus QueryBfbComponentsSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED)
    {
        return FLINT_FAILED;
    }

    if (!_fwOps->getBFBComponentsVersions(_name_to_version, _pending))
    {
        return FLINT_FAILED;
    }

    printComponents();
    return FLINT_SUCCESS;
}

bool QueryBfbComponentsSubCommand::verifyParams()
{
    _pending = _flintParams.pending;

    if (!_flintParams.device_specified)
    {
        reportErr(true, FLINT_NO_DEVICE_ERROR);
        return false;
    }

    if (!_flintParams.cmd_params.empty())
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }

    return isDeviceSupported();
}

bool QueryBfbComponentsSubCommand::isDeviceSupported()
{
    mfile* mf = mopen(_flintParams.device.c_str());
    if (!mf)
    {
        reportErr(true, "Failed to open device: %s\n", _flintParams.device.c_str());
        return false;
    }

    dm_dev_id_t devid_type = DeviceUnknown;
    u_int32_t devid = 0, revid = 0;
    int rc = dm_get_device_id(mf, &devid_type, &devid, &revid);
    mclose(mf);

    if (rc != 0)
    {
        reportErr(true, "Can't get device ID.\n");
        return false;
    }

    if (devid_type != DeviceBlueField3)
    {
        reportErr(true, "query_bfb_components sub-command is supported for BlueField3 only. Device provided: %s\n",
                  dm_dev_type2str(devid_type));
        return false;
    }

    return true;
}

void QueryBfbComponentsSubCommand::printComponents()
{
    printf("{\n\n");
    printf(
      "    \"//\": \"This JSON represents a Redfish Software Inventory collection containing multiple software components.\",\n\n");
    printf("    \"Name\": \"BFB File Content\",\n\n");
    printf("    \"Members\": [\n");

    size_t id = 1;
    for (const auto& name_version_pair : _name_to_version)
    {
        printf("        {\n");
        printf("            \"Id\": \"%zu\",\n", id++);
        printf("            \"Name\": \"%s\",\n", name_version_pair.first.c_str());
        printf("            \"Version\": \"%s\",\n", name_version_pair.second.c_str());
        printf("        }%s\n", (id <= _name_to_version.size()) ? "," : "");
    }

    printf("    ],\n\n");
    printf("    \"Members@odata.count\": %zu\n", _name_to_version.size());
    printf("}\n");
}