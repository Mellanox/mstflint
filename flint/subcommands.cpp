/*
 *
 * subcommands.cpp - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>

#include <common/compatibility.h>

#ifndef NO_ZLIB
    #include <zlib.h>
#endif

#define MAX_IMG_TYPE_LEN 20

#if !defined(__WIN__) && !defined(__DJGPP__) && !defined(UEFI_BUILD) && defined(HAVE_TERMIOS_H)
// used in mygetchar
    #include <termios.h>
#endif

#ifdef __WIN__
    #include <ctype.h>
    #include <win_driver_cif.h>
#endif // WIN

#include "subcommands.h"

using namespace std;

/***********************************
 *  Log file writing implementation
 ************************************/

//global log file header
FILE *flint_log_fh = NULL;

#define BURN_INTERRUPTED 0x1234

void close_log()
{
    if (flint_log_fh != NULL) {
        fclose(flint_log_fh);
        flint_log_fh = NULL;
    }
    return;
}

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char*   month_2monstr(int month)
{
    static const char *month_2monstr_arr[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec",
    };
    int arr_size = (int)ARRAY_SIZE(month_2monstr_arr);
    return month < arr_size ? month_2monstr_arr[month] : "???";
}

void print_time_to_log()
{
    time_t rawtime;
    struct tm *timeinfo;

    if (flint_log_fh == NULL) {
        return;
    }
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (!timeinfo) {
        printf("localtime returned NULL. Can't print time.\n");
        return;
    }

    fprintf(flint_log_fh, "%-3s %2d %02d:%02d:%02d ", month_2monstr(timeinfo->tm_mon), timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return;
}

int print_line_to_log(const char *format, ...)
{
    va_list args;
    if (flint_log_fh == NULL) {
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
    if (!write) {
        return 0;
    }
    char pre_str[50];
    if (flint_log_fh == NULL) {
        return 0;
    }
    if (cmd == SC_Brom) {
        snprintf(pre_str, 50, "ROM");
    } else {
        snprintf(pre_str, 50, "FW");
    }
    print_time_to_log();
    fprintf(flint_log_fh, "Start %s burning: ", pre_str);
    fprintf(flint_log_fh, "%s ", fullCmd.c_str());
    fprintf(flint_log_fh, "\n");
    return 0;
}

int write_result_to_log(int is_failed, const char *err_msg, bool write)
{
    if (!write) {
        return 0;
    }
    char msg[MAX_ERR_STR_LEN + 1] = {0};
    strncpy(msg, err_msg, MAX_ERR_STR_LEN);
    if (is_failed == 0) {
        print_line_to_log("Burn completed successfully\n");
    } else if (is_failed == BURN_INTERRUPTED) {
        print_line_to_log("Burn interrupted by user\n");
    } else {
        int msg_len = strlen(msg);
        // cleanup the msg
        for (int i = 0; i < msg_len; i++) {
            if (msg[i] == '\n') {
                if (i == msg_len - 1) {
                    msg[i] = '\0';
                } else {
                    msg[i] = ' ';
                }
            }
        }
        print_line_to_log("Burn failed: %s\n", msg);
    }
    return 0;
}
/*******************
 *  Static functions
 ******************/

static bool str2Num(const char *str, u_int32_t& num)
{
    char *endp;
    u_int32_t tempNum;

    if (!str) {
        return false;
    }
    tempNum = strtoul(str, &endp, 0);
    if (*endp) {
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

    switch (_cmdType) {
    case SC_Burn:
    case SC_Bb:
    case SC_Brom:
        return _flintParams.log_specified;

    default:
        return false;
    }
    return false;
}

void SubCommand::reportErr(bool shouldPrint, const char *format, ...)
{
    va_list args;

    va_start(args, format);

    if (vsnprintf(_errBuff, FLINT_ERR_LEN, format, args) >= FLINT_ERR_LEN) {
        strcpy(&_errBuff[FLINT_ERR_LEN - 5], "...\n");
    }
    //print to the user and to the log if needed
    if (shouldPrint) {
        fprintf(stdout, PRE_ERR_MSG " %s", _errBuff);
    }
    write_result_to_log(FLINT_FAILED, _errBuff, isCmdSupportLog());
    va_end(args);

    return;
}

bool SubCommand::writeToFile(string filePath, const std::vector<u_int8_t>& buff)
{
    FILE *fh = fopen(filePath.c_str(), "wb");
    if (fh == NULL) {
        reportErr(true, FLINT_OPEN_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    // Write
    if (fwrite(&buff[0], 1, buff.size(), fh) != buff.size()) {
        fclose(fh);
        reportErr(true, FLINT_WRITE_FILE_ERROR, filePath.c_str(), strerror(errno));
        return false;
    }
    fclose(fh);
    return true;
}

FlintStatus SubCommand::writeImageToFile(const char *file_name, u_int8_t *data, u_int32_t length)
{
    FILE *fh = fopen(file_name, "wb");
    if (fh == NULL) {
        reportErr(true, "Can not open %s: %s\n", file_name, strerror(errno));
        return FLINT_FAILED;
    }

    // Write output
    if (fwrite(data, 1, length, fh) != length) {
        fclose(fh);
        reportErr(true, "Failed to write to %s: %s\n", file_name, strerror(errno));
        return FLINT_FAILED;
    }
    fclose(fh);
    return FLINT_SUCCESS;
}

void SubCommand::openLog()
{
    if (isCmdSupportLog()) {
        flint_log_fh = fopen(_flintParams.log.c_str(), "a+");
        if (flint_log_fh == NULL) {
            printf("-W- Failed to open log file \"%s\": %s. No logs will be saved\n", _flintParams.log.c_str()
                   , strerror(errno));
        }
        write_cmd_to_log(_flintParams.fullCmd, _flintParams.cmd, _flintParams.log_specified);
    }
}

int SubCommand::verifyCbFunc(char *str)
{
    printf("%s", str);
    return 0;
}


int SubCommand::CbCommon(int completion, char *preStr, char *endStr)
{
    if (completion < 100) {
        printf("\r%s%3d%%", preStr, completion);
    } else if (completion == 100) {
        printf("\r%sOK  \n", preStr);
    } else {    // printing endStr
        if (endStr) {
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
    char *message = (char*)"Burning FW image without signatures - ";
    char *endStr =  (char*)"Restoring signature                     - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::advProgressFunc(int completion, const char *stage, prog_t type, int *unknownProgress)
{
    switch (type) {
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
        if (unknownProgress) {
            static const char *progStr[] = { "[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]", "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]" };
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
    char *message = (char*)"Burning FS2 FW image without signatures - ";
    char *endStr =  (char*)"Restoring signature                     - OK";
    if (completion == 102) {
        endStr = (char*)"Image was successfully cached by driver.";
    }
    return CbCommon(completion, message, endStr);
}

int SubCommand::bromCbFunc(int completion)
{
    char *message = (char*)"Burning ROM image    - ";
    char *endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::dromCbFunc(int completion)
{
    char *message = (char*)"Removing ROM image    - ";
    char *endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::resetCfgCbFunc(int completion)
{
    char *message = (char*)"Resetting NV configuration - ";
    char *endStr =  (char*)"Restoring signature        - OK";
    return CbCommon(completion, message, endStr);
}


int SubCommand::burnBCbFunc(int completion)
{
    return CbCommon(completion, (char*)"");
}

int SubCommand::vsdCbFunc(int completion)
{
    char *message = (char*)"Setting the VSD      - ";
    char *endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::setKeyCbFunc(int completion)
{
    char *message = (char*)"Setting the HW Key   - ";
    char *endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::wbCbFunc(int completion)
{
    char *message = (char*)"Writing Block:   - ";
    return CbCommon(completion, message, NULL);
}

#define ERR_BUFF_SIZE 1024

void SubCommand::initDeviceFwParams(char *errBuff, FwOperations::fw_ops_params_t& fwParams)
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
}

FlintStatus SubCommand:: openOps()
{
    char errBuff[ERR_BUFF_SIZE] = {0};
    if (_flintParams.device_specified) {
        // fillup the fw_ops_params_t struct
        FwOperations::fw_ops_params_t fwParams;
        initDeviceFwParams(errBuff, fwParams);
        if (_flintParams.image_specified) {
            FwOperations::fw_ops_params_t imgFwParams;
            memset(&imgFwParams, 0, sizeof(imgFwParams));
            imgFwParams.psid = NULL;
            imgFwParams.hndlType = FHT_FW_FILE;
            imgFwParams.errBuff = errBuff;
            imgFwParams.errBuffSize = 1024;
            imgFwParams.shortErrors = true;
            imgFwParams.fileHndl = (char*)_flintParams.image.c_str();
            if (!FwOperations::imageDevOperationsCreate(fwParams, imgFwParams, &_fwOps, &_imgOps)) {
                /*
                 * Error are being handled after
                 */
            }
        } else {
            _fwOps = FwOperations::FwOperationsCreate(fwParams);
        }
        delete[] fwParams.mstHndl;
    }
    if (_flintParams.image_specified && !_flintParams.device_specified) {
        _imgOps = FwOperations::FwOperationsCreate((void*)_flintParams.image.c_str(), NULL, NULL, \
                                                   FHT_FW_FILE, errBuff, 1024);
    }
    if (_flintParams.image_specified && _imgOps == NULL) {
        reportErr(true, FLINT_OPEN_FWOPS_IMAGE_ERROR, _flintParams.image.c_str(), strlen(errBuff) != 0 ? errBuff : "");
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified && _fwOps == NULL) {
        reportErr(true, FLINT_OPEN_FWOPS_DEVICE_ERROR, _flintParams.device.c_str(), strlen(errBuff) != 0 ? errBuff : "");
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}



FlintStatus SubCommand:: openIo()
{
    //TODO: consider adding a parameter for when image/device will be opened as "readOnly" in the open routine.
    if (_flintParams.device_specified && _flintParams.image_specified) {
        //should not arrive here as we verify params at each subcommand.
        reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified) {
        _io = new Flash;
        if (!((Flash*)_io)->open(_flintParams.device.c_str(), _flintParams.clear_semaphore, false, _flintParams.banks, \
                                 _flintParams.flash_params_specified ? &_flintParams.flash_params : NULL, _flintParams.override_cache_replacement, true, _flintParams.use_fw)) {
            // if we have Hw_Access command we dont fail straght away
            u_int8_t lockedCrSpace = ((Flash*)_io)->get_cr_space_locked();
            if (lockedCrSpace && (_flintParams.cmd == SC_Hw_Access ||
                                  (_flintParams.cmd == SC_Set_Key && ((Flash*)_io)->is_fifth_gen()))) {
                return FLINT_SUCCESS;
            }
            reportErr(true, FLINT_IO_OPEN_ERROR, "Device", (_io)->err());
            delete _io;
            _io = NULL;
            return FLINT_FAILED;
        }
        // we have successfully opened a Flash Obj
        //set no flash verify if needed (default =false)
        ((Flash*)_io)->set_no_flash_verify(_flintParams.no_flash_verify);
    } else if (_flintParams.image_specified) {
        _io = new FImage;
        if (!((FImage*)_io)->open(_flintParams.image.c_str())) {
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
    if (!_flintParams.log_specified) {
        char *logFile;
        logFile = getenv(FLINT_LOG_ENV);
        if (logFile) {
            _flintParams.log = logFile;
            _flintParams.log_specified = true;
        }
    }
    //open log if needed
    openLog();

    if (_maxCmdParamNum == _minCmdParamNum && _maxCmdParamNum != -1 && (int)_flintParams.cmd_params.size() != _maxCmdParamNum) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), _maxCmdParamNum, _flintParams.cmd_params.size());
        return false;
    } else if (_maxCmdParamNum != -1 && (int)_flintParams.cmd_params.size() > _maxCmdParamNum) {
        // _maxCmdParamNum == -1 means ignore this check
        if (_maxCmdParamNum) {
            reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), _maxCmdParamNum, _flintParams.cmd_params.size());
        } else {
            reportErr(true, FLINT_CMD_ARGS_ERROR5, _name.c_str());
        }
        return false;
    } else if (_minCmdParamNum != -1 && (int)_flintParams.cmd_params.size() < _minCmdParamNum) {
        // _minCmdParamNum == -1 means ignore this check
        reportErr(true, FLINT_CMD_ARGS_ERROR3, _name.c_str(), _minCmdParamNum, _flintParams.cmd_params.size());
        return false;
    }

    switch (_v) {
    case Wtv_Img:
        if (_flintParams.device_specified == true) {
            _flintParams.image_specified ? reportErr(true, FLINT_COMMAND_IMAGE_ERROR2, _name.c_str()) :
            reportErr(true, FLINT_COMMAND_IMAGE_ERROR, _name.c_str());
            return false;
        }
        if (_flintParams.image_specified == false) {
            reportErr(true, FLINT_NO_IMAGE_ERROR);
            return false;
        }
        break;

    case Wtv_Dev:
        if (_flintParams.image_specified == true) {
            _flintParams.device_specified ? reportErr(true, FLINT_COMMAND_DEVICE_ERROR2, _name.c_str()) :
            reportErr(true, FLINT_COMMAND_DEVICE_ERROR, _name.c_str());
            return false;
        }
        if (_flintParams.device_specified == false) {
            reportErr(true, FLINT_NO_DEVICE_ERROR);
            return false;
        }
        break;

    case Wtv_Dev_And_Img:
        if ((_flintParams.image_specified == false) || (_flintParams.device_specified == false)) {
            reportErr(true, FLINT_COMMAND_DEVICE_IMAGE_ERROR, _name.c_str());
            return false;
        }
        break;

    case Wtv_Dev_Or_Img:
        if (_flintParams.image_specified == true && _flintParams.device_specified == true) {
            reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
            return false;
        }
        if (_flintParams.device_specified == false  && _flintParams.image_specified == false) {
            reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
            return false;
        }
        break;

    default:
        reportErr(true, "Failed to verify parms(internal error).");
        return false;
    }

    if (_flintParams.device_specified && _flintParams.striped_image) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-device", "-striped_image");
        return false;
    }

    if (_flintParams.override_cache_replacement) {
        printf(FLINT_OCR_WARRNING);
    }
    return true;
}

FlintStatus SubCommand::preFwOps()
{
    if (!basicVerifyParams()) {
        return FLINT_FAILED;
    }
    if (!verifyParams()) {
        return FLINT_FAILED;
    }
    return openOps();
}

FlintStatus SubCommand::preFwAccess()
{
    if (!basicVerifyParams()) {
        return FLINT_FAILED;
    }
    if (!verifyParams()) {
        return FLINT_FAILED;
    }
    return openIo();
}

SubCommand::~SubCommand()
{
    if (_fwOps != NULL) {
        _fwOps->FwCleanUp();
        delete _fwOps;
    }
    if (_imgOps != NULL) {
        _imgOps->FwCleanUp();
        delete _imgOps;
    }
    if (_io != NULL) {
        _io->close();
        delete _io;
    }


}

bool SubCommand::getRomsInfo(FBase *io, roms_info_t& romsInfo)
{
    std::vector<u_int8_t> romSector;
    romSector.clear();
    romSector.resize(io->get_size());
    if (!io->read(0, &romSector[0], io->get_size())) {
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
    char *endp;
    u_int64_t g;
    g = strtoull(str.c_str(), &endp, 16);
    if (*endp || (g == 0xffffffffffffffffULL && errno == ERANGE)) {
        if (prefixErr.size() == 0) {
            reportErr(true, "Invalid GUID syntax (%s) %s\n", str.c_str(), errno ? strerror(errno) : "");
        } else {
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
    struct termios oldt,
                   newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

bool SubCommand::getPasswordFromUser(const char *preStr, char buffer[MAX_PASSWORD_LEN + 1])
{
    char c;
    int pos = 0;

    printf("%s: ", preStr);
    do {
        c = mygetch();

        if (((pos < MAX_PASSWORD_LEN)) && isprint(c)) {
            buffer[pos++] = c;
            printf("%c", '*');
        } else if ((c == 8 || c == 127) && pos) {
            buffer[pos--] = '\0';
            printf("%s", "\b \b");
        }


    } while (c != '\n');
    printf("\n");
    buffer[pos] = '\0';
    return true;
}

#else
bool SubCommand::getPasswordFromUser(const char *preStr, char buffer[MAX_PASSWORD_LEN + 1])
{
    static HANDLE stdinHndl = NULL;
    DWORD numOfBytesRead = 0;
    DWORD oldConsoleMode, consoleMode;
    BOOL status = FALSE;
    char ch;
    int i;

    if (!stdinHndl) {
        // adrianc: this might be problematic if called and stdout was alreading overridden use CIN$ instead
        stdinHndl = GetStdHandle(STD_INPUT_HANDLE);
    }
    printf("%s:", preStr);

    // disable console echoing
    if (!GetConsoleMode(stdinHndl, &oldConsoleMode)) {
        reportErr(true, "Failed to get console mode.\n");
        return false;
    }

    consoleMode = oldConsoleMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    if (!SetConsoleMode(stdinHndl, consoleMode)) {
        reportErr(true, "Failed to set console mode.\n");
        return 1;
    }
    // read chars from stdin and print * to stdout using putchar
    for (i = 0;;) {
        status = ReadFile(stdinHndl, &ch, sizeof(char), &numOfBytesRead, NULL);
        if (!status || numOfBytesRead != sizeof(char) || ch == '\n' || ch == '\r' || i == (MAX_PASSWORD_LEN - 1)) {
            // user finished giving the pw
            if (!SetConsoleMode(stdinHndl, oldConsoleMode)) {
                reportErr(true, "Failed to restore console mode.\n");
                return false;
            }
            if (!status || numOfBytesRead != sizeof(char)) {
                reportErr(true, "Failed to get input from console.\n");
                return false;
            }
            break;
        }
        if (isalpha(ch) || isdigit(ch)) {
            putchar('*');
            buffer[i++] = ch;
        } else if (ch == '\b' && i) {
            //delete last astrix and set correct position
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

bool SubCommand::askUser(const char *question, bool printAbrtMsg)
{
    if (question == NULL) {
        printf("\n Do you want to continue ? (y/n) [n] : ");
    } else {
        printf("\n %s ? (y/n) [n] : ", question);

    }

    if (_flintParams.yes) {
        printf("y\n");
    } else {
        if (_flintParams.no) {
            printf("n\n");
            reportErr(false, "-no flag is set\n");
            return false;
        }

        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);
        //fgets(ansbuff, 30, stdin);
        //if (!fscanf(stdin, "%[^\n]30s", ansbuff)) {
        //	return false;
        //}

        if (strcasecmp(answer.c_str(), "y") &&
            strcasecmp(answer.c_str(), "yes")) {

            if (printAbrtMsg) {
                reportErr(true, "Aborted by user\n");
            }
            return false;
        }
    }
    return true;
}

string SubCommand::getRomProtocolStr(u_int8_t proto)
{
    string result;

    switch (proto) {
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

    switch (suppCpu) {
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
    if (info.exp_rom_num_ver_fields) {
        for (int i = 0; i < info.exp_rom_num_ver_fields; i++) {
            verStream << info.exp_rom_ver[i];
            if (i + 1 < info.exp_rom_num_ver_fields) {
                verStream << ".";
            }
        }
    }
    return verStream.str();
}

void SubCommand::displayOneExpRomInfo(const rom_info_t& info)
{
    const char *typeStr = FwOperations::expRomType2Str(info.exp_rom_product_id);
    if (info.exp_rom_product_id == 0xf) {
        // version id in this case is the freeStr that was moved to exp_rom_ver[0] in mlxfwops
        printf("version_id=%s type=%s ", getExpRomVerStr(info).c_str(), typeStr);
    } else {
        if (typeStr) {
            printf("type=%s ", typeStr);
        } else {
            printf("0x%x - Unknown ROM product ID\n", info.exp_rom_product_id);
            return;
        }
        printf("version=%s", getExpRomVerStr(info).c_str());
        if (info.exp_rom_product_id >= 0x10) {
            if (info.exp_rom_port) {
                // Do not display if 0 - port independent
                printf(" port=%d", info.exp_rom_port);
            }
            if (info.exp_rom_product_id != 0x12 && info.exp_rom_proto != 0xff) {
                // on CLP(0x12) there is no meaning to protocol
                printf(" proto=%s", getRomProtocolStr(info.exp_rom_proto).c_str());
            }
            if (info.exp_rom_supp_cpu_arch) {
                printf(" cpu=%s", getRomSuppCpuStr(info.exp_rom_supp_cpu_arch).c_str());
            }
        }
    }
    return;
}


void SubCommand::displayExpRomInfo(const roms_info_t& romsInfo, const char *preStr)
{
    int i;
    int strLen = strlen(preStr);

    if (romsInfo.num_of_exp_rom > 0) {
        for (i = 0; i < romsInfo.num_of_exp_rom; i++) {
            // Print the pre string or spaces
            if (i == 0) {
                printf("%s", preStr);
            } else {
                int j;
                for (j = 0; j < strLen; j++) {
                    printf("%s", " ");
                }
            }
            // Display a ROM info
            displayOneExpRomInfo(romsInfo.rom_info[i]);
            if (i != romsInfo.num_of_exp_rom - 1) {
                // Don't print new line after the info of the last ROM
                printf("\n");
            }
        }
        if (romsInfo.exp_rom_warning) {
            printf(" (-W- %s)", romsInfo.exp_rom_warning_msg);
        }
        printf("\n");
    } else {
        printf("%s", preStr);
        printf("N/A");
        if (romsInfo.exp_rom_err_msg_valid) {
            printf(" (-E- %s)", romsInfo.exp_rom_err_msg);
        }
        printf("\n");
    }
    return;
}

bool SubCommand::printGuidLine(guid_t *new_guids, guid_t *old_guids, int guid_index)
{
    printf(GUID_FORMAT GUID_SPACES, new_guids[guid_index].h, new_guids[guid_index].l);
    if (old_guids != NULL) {
        printf(GUID_FORMAT,  old_guids[guid_index].h, old_guids[guid_index].l);
    } else {
        printf("      N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printMacLine(guid_t *new_guids, guid_t *old_guids, int mac_index)
{
    printf("    " MAC_FORMAT MAC_SPACES, new_guids[mac_index].h, new_guids[mac_index].l);
    if (old_guids != NULL) {
        printf(MAC_FORMAT, old_guids[mac_index].h, old_guids[mac_index].l);
    } else {
        printf("  N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printGUIDsFunc(guid_t guids[GUIDS], guid_t macs[MACS], guid_t old_guids[GUIDS], \
                                guid_t old_macs[MACS], bool print_guids, bool print_macs, int portNum, bool old_guid_fmt)
{

    if (print_guids) {
        printf("        Node  GUID:     ");
        printGuidLine(guids, old_guids, 0);
        if (portNum > 0) {
            printf("        Port1 GUID:     ");
            printGuidLine(guids, old_guids, 1);
        }
        if (portNum > 1) {
            printf("        Port2 GUID:     ");
            printGuidLine(guids, old_guids, 2);
        }
        if (!old_guid_fmt) {
            printf("        Sys.Image GUID: ");
            printGuidLine(guids, old_guids, 3);
        }
    }

    if (print_macs) {
        printf("        Port1 MAC:      ");
        printMacLine(macs, old_macs, 0);
        printf("        Port2 MAC:      ");
        printMacLine(macs, old_macs, 1);
    }
    return true;
}

bool SubCommand::reportGuidChanges(guid_t *new_guids, guid_t *new_macs, \
                                   guid_t *old_guids, guid_t *old_macs, bool printGuids, \
                                   bool printMacs, int guidNum)
{
    //should be used ONLY on FS2 in current implementation
    printf("    You are about to change the Guids/Macs/Uids on the %s:\n\n", _flintParams.device_specified ? "device" : "image");
    printf("                        New Values      " GUID_SPACES "Current Values\n");
    printGUIDsFunc(new_guids, new_macs,
                   old_guids, old_macs,
                   printGuids,
                   printMacs,
                   guidNum,
                   guidNum < GUIDS);

    if (!askUser()) {
        return false;
    }

    return true;
}

//used for dc and dh subcommands

bool SubCommand::unzipDataFile(std::vector<u_int8_t> data, std::vector<u_int8_t> &newData, const char *sectionName)
{
#ifndef NO_ZLIB
    int rc;
    if (data.empty()) {
        reportErr(true, "%s section not found in the given image.", sectionName);
        return false;
    }
    // restore endianess.
    TOCPUn(&(data[0]), data.size() / 4);

    // uncompress:
    uLongf destLen = data.size();
    destLen *= 40; // Assuming this is the best compression ratio
    vector<u_int8_t> dest(destLen);

    for (int i = 0; i < 32; i++) {
        rc = uncompress((Bytef*)&(dest[0]), &destLen,
                        (const Bytef*)&(data[0]), data.size());
        if (rc != Z_BUF_ERROR) {
            break;
        }
        destLen *= 2;
        dest.resize(destLen);
    }

    if (rc != Z_OK) {
        reportErr(true, "Failed uncompressing FW configuration section. uncompress returns %d", rc);
        return false;
    }
    // printf("%s", (char*)&(dest[0]));

    newData = dest;
    newData[destLen] = 0; // Terminating NULL
    newData.resize(destLen + 1);
    return true;
#else
    // avoid warnings
    (void) data;
    (void) newData;
    (void) sectionName;
    reportErr(true, FLINT_NO_ZLIB_ERROR);
    return false;
#endif
}

bool SubCommand::dumpFile(const char *confFile, std::vector<u_int8_t>& data, const char *sectionName)
{
    FILE *out;
    vector<u_int8_t> dest;

    if (confFile == NULL) {
        out = stdout;
    } else {
        out = fopen(confFile, "w");

        if (out == NULL) {
            reportErr(true, "Can not open file %s for write: %s.", confFile, strerror(errno));
            return false;
        }
    }
    if (unzipDataFile(data, dest, sectionName) == false) {
        if (confFile != NULL) {
            fclose(out);
        }
        return false;
    }
    fprintf(out, "%s", (char*)&(dest[0]));

    if (confFile != NULL) {
        fclose(out);
    }
    return true;
}

bool SubCommand::checkGuidsFlags(u_int16_t devType, u_int8_t fwType,
                                 bool guidsSpecified, bool macsSpecified, bool uidSpecified, bool ibDev, bool ethDev)
{
    (void)ibDev;
    if (guidsSpecified || macsSpecified || uidSpecified) {
        if (uidSpecified && fwType != FIT_FS3 && fwType != FIT_FS4 && fwType != FIT_FSCTRL) {
            reportErr(true, "-uid flag is applicable only for FS3/FS4 FW Only.\n");
            return false;
        } else if (fwType != FIT_FS2 && !ethDev && macsSpecified) {
            reportErr(true, "-mac(s) flag is not applicable for IB MT%d device.\n", devType);
            return false;
        }
    }
    return true;
}

void SubCommand::printMissingGuidErr(bool ibDev, bool ethDev)
{
    const char *missingInfo;
    const char *missingFlags;

    if (ibDev && ethDev) {
        missingInfo  = "GUIDs / MACs";
        missingFlags = "-guid(s) / -mac(s)";
    } else if (ibDev) {
        missingInfo  = "GUIDs";
        missingFlags = "-guid(s)";
    } else {
        missingInfo  = "MACs";
        missingFlags = "-mac(s)";
    }

    printf("Please specify %s (using command line flags %s ).\n", missingInfo, missingFlags);
    return;
}

bool SubCommand::extractValuesFromString(string valStr, u_int8_t values[2], string origArg)
{
    // check if we need to extract 2 values or 1
    u_int32_t tempNum0 = 0, tempNum1 = 0;
    string tempNumStr;
    if (valStr.find(',') != string::npos) {
        std::stringstream ss((valStr.c_str()));
        // get first value
        if (!std::getline(ss, tempNumStr, ',')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        if (!str2Num(tempNumStr.c_str(), tempNum0)) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        // get second value
        if (!std::getline(ss, tempNumStr, ',')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        if (!str2Num(tempNumStr.c_str(), tempNum1)) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        // make sure no other tokens are present
        if (!(!std::getline(ss, tempNumStr, ','))) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
    } else {
        if (!str2Num(valStr.c_str(), tempNum0)) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, origArg.c_str());
            return false;
        }
        tempNum1 = tempNum0;
    }
    // perform checks
    if (tempNum0 >= 255 || tempNum1 >= 255) {
        reportErr(true, "Invalid argument values, values should be taken from the range [0..254]\n");
        return false;
    }
    values[0] = tempNum0;
    values[1] = tempNum1;
    return true;
}

bool SubCommand::extractUIDArgs(std::vector<string>& cmdArgs, u_int8_t numOfGuids[2], u_int8_t stepSize[2])
{
    //extract num_of_guids and step_size from numGuidsStr, stepStr
    string tag, valStr;
    for (std::vector<string>::iterator it = cmdArgs.begin(); it != cmdArgs.end(); it++) {
        std::stringstream ss((it->c_str()));
        // get the tag
        if (!std::getline(ss, tag, '=')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        // get the val
        if (!std::getline(ss, valStr, '=')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        // make sure no other tokens are present
        if (!(!std::getline(ss, valStr, '='))) {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
        if (tag == "guids_num") {
            if (!extractValuesFromString(valStr, numOfGuids, *it)) {
                return false;
            }
        } else if (tag == "step_size") {
            if (!extractValuesFromString(valStr, stepSize, *it)) {
                return false;
            }
        } else {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
    }
    return true;
}

const char* SubCommand::fwImgTypeToStr(u_int8_t fwImgType)
{
    switch (fwImgType) {
    case FIT_FS2:
        return "FS2";
        break;

    case FIT_FS3:
        return "FS3";
        break;

    case FIT_FS4:
        return "FS4";
        break;

    case FIT_FSCTRL:
        return "FSCTRL";
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

Extract4MBImageSubCommand::~Extract4MBImageSubCommand()
{

}

FlintStatus Extract4MBImageSubCommand::executeCommand()
{
    vector<u_int8_t> img;

    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    if (_imgOps->FwType() == FIT_FS2) {
        reportErr(true, "Extracting FW Data is applicable only for FS3/FS4 FW.\n");
        return FLINT_FAILED;
    }

    if (!_imgOps->FwExtract4MBImage(img, true)) {
        reportErr(true, "Extracting FW Data failed: %s.\n", _imgOps->err());
        return FLINT_FAILED;
    }

    if (!writeToFile(_flintParams.cmd_params[0], img)) {
        return FLINT_FAILED;
    }

    return FLINT_SUCCESS;
}

/***********************
 * * Class: AddHmacSubCommand
 * ***********************/
AddHmacSubCommand:: AddHmacSubCommand()
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

AddHmacSubCommand:: ~AddHmacSubCommand()
{

}

FlintStatus AddHmacSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    if (_imgOps->FwType() != FIT_FS4) {
        reportErr(true, "Signing with HMAC is applicable only for FS4 FW.\n");
        return FLINT_FAILED;
    }

    if (!_imgOps->FwSignWithHmac(_flintParams.key.c_str())) {
                reportErr(true, FLINT_HMAC_ERROR, _imgOps->err());
                return FLINT_FAILED;
            }
    return FLINT_SUCCESS;
}

bool AddHmacSubCommand::verifyParams()
{
    if (!_flintParams.key_specified) {
        reportErr(true, "To sign with HMAC, you must provide a key \n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1,
                  (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

/***********************
* Class: SignSubCommand
***********************/
SignSubCommand:: SignSubCommand()
{
    _name = "sign";
    _desc = "Sign firmware image file";
    _extendedDesc = "Sign firmware image file";
    _flagLong = "sign";
    _flagShort = "";
    _paramExp = "None";
    _example = FLINT_NAME " -i fw_image.bin [--private_key file.pem --key_uuid uuid.bin] sign";
    _v = Wtv_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Sign;
}

SignSubCommand:: ~SignSubCommand()
{

}

FlintStatus SignSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    if (_imgOps->FwType() != FIT_FS3 &&  _imgOps->FwType() != FIT_FS4) {
        reportErr(true, "Image signing is applicable only for FS3/FS4 FW.\n");
        return FLINT_FAILED;
    }

    if (_flintParams.privkey_specified && _flintParams.uuid_specified) {
        if (_flintParams.privkey2_specified && _flintParams.uuid2_specified) {
            if (!_imgOps->FwSignWithTwoRSAKeys(_flintParams.privkey_file.c_str(),
                                               _flintParams.privkey_uuid.c_str(),
                                               _flintParams.privkey2_file.c_str(),
                                               _flintParams.privkey2_uuid.c_str(),
                                               &verifyCbFunc)) {
                reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
                return FLINT_FAILED;
            }
        } else {
            if (!_imgOps->FwSignWithOneRSAKey(_flintParams.privkey_file.c_str(),
                                              _flintParams.privkey_uuid.c_str(),
                                              &verifyCbFunc)) {
                reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
                return FLINT_FAILED;
            }
        }
    } else {
        if (!_imgOps->FwInsertSHA256(&verifyCbFunc)) {
            reportErr(true, FLINT_SIGN_ERROR, _imgOps->err());
            return FLINT_FAILED;
        }
    }

    return FLINT_SUCCESS;
}

bool SignSubCommand::verifyParams()
{
    if (_flintParams.privkey_specified ^ _flintParams.uuid_specified) {
        reportErr(true, "To Sign the image with RSA you must provide "
                  "private key and uuid.\n");
        return false;
    }

    if (!_flintParams.privkey_specified && _flintParams.privkey2_specified) {
        reportErr(true, "Use --private_key if you want to sign with only one key.\n");
        return false;
    }

    if (_flintParams.privkey2_specified ^ _flintParams.uuid2_specified) {
        reportErr(true, "To Sign the image with two RSA keys you must provide "
                  "two private keys and two uuid.\n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1,
                  (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

/***********************
 * Class: BurnSubCommand
 **********************/

BurnSubCommand:: BurnSubCommand()
{
    _name = "burn";
    _desc = "Burn flash";
    _extendedDesc = "Burn flash \n"
                    "Performs failsafe FW update from a raw binary image.";
    _flagLong = "burn";
    _flagShort = "b";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -i image1.bin burn\n"
               FLINT_NAME " -d " MST_DEV_EXAMPLE2 " -guid 0x2c9000100d050 -i image1.bin b";
    _v = Wtv_Dev_And_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Burn;
    _fwType = 0;
    _devQueryRes = 0;
    _mccSupported = true;
    memset(&_devInfo, 0, sizeof(_devInfo));
    memset(&_imgInfo, 0, sizeof(_imgInfo));
    _unknownProgress = 0;
}

BurnSubCommand:: ~BurnSubCommand()
{
    closeLog();
    if (_burnParams.userVsd != NULL) {
        delete[] _burnParams.userVsd;
    }
}

bool BurnSubCommand::verifyParams()
{
    if ((_flintParams.guid_specified || _flintParams.guids_specified) && (_flintParams.uid_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either GUIDs / UID (using command line flags -guid(s) / -uid )");
        return false;
    }
    if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either MACs / UID (using command line flags -mac(s) / -uid )");
        return false;
    }
    bool GuidsFromUser = _flintParams.guid_specified || _flintParams.guids_specified || \
                         _flintParams.uid_specified || \
                         _flintParams.mac_specified || _flintParams.macs_specified;
    if (GuidsFromUser && _flintParams.use_image_guids) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "GUIDs/UIDs/MACs", "-use_image_guids");
        return false;
    }
    if ((GuidsFromUser || _flintParams.use_image_guids) && _flintParams.blank_guids) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, _flintParams.use_image_guids ? \
                  "-use_image_guids" : "GUIDs/UIDs/MACs", "-blank_guids");
        return false;
    }
    if (_flintParams.guid_specified && _flintParams.guids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid");
        return false;
    }
    if (_flintParams.mac_specified && _flintParams.macs_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-macs", "-mac");
        return false;
    }
    if (_flintParams.use_image_ps && _flintParams.vsd_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-use_image_ps", "-vsd");
        return false;
    }
    if (_flintParams.ignore_dev_data && !_flintParams.nofs) {
        reportErr(true, FLINT_INVALID_FLAG_WITHOUT_FLAG_ERROR, "-nofs", "-ignore_dev_data");
        return false;
    }
    if (_flintParams.use_dev_rom && _flintParams.use_image_rom) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "--use_dev_rom", "--use_image_rom");
        return false;
    }
    if (_flintParams.nofs || _flintParams.allow_psid_change || _flintParams.use_dev_rom) {
        // attempt to fallback to legacy flow (direct flash access via FW)
        _mccSupported = false;
    }
    return true;
}

void BurnSubCommand::updateBurnParams()
{
    _burnParams.progressFunc = _flintParams.silent == true ? (ProgressCallBack)NULL : \
                                                             _fwType == FIT_FS2 ? &burnCbFs2Func : &burnCbFs3Func;

    _burnParams.ProgressFuncAdv.func = _flintParams.silent == true ? (f_prog_func_adv)NULL : (f_prog_func_adv) & advProgressFunc;
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
    _burnParams.burnRomOptions = _flintParams.use_image_rom ? FwOperations::ExtBurnParams::BRO_ONLY_FROM_IMG \
                                 : FwOperations::ExtBurnParams::BRO_DEFAULT;
    _burnParams.useImageGuids = _flintParams.use_image_guids;
    _burnParams.singleImageBurn = !_flintParams.dual_image;
    _burnParams.noDevidCheck = _flintParams.no_devid_check;
    _burnParams.skipCiReq = _flintParams.skip_ci_req;
    _burnParams.useImgDevData = _flintParams.ignore_dev_data;
    if (_burnParams.userGuidsSpecified) {
        _burnParams.userUids = _flintParams.user_guids;
    }
    if (_burnParams.userUidSpecified) {
        _burnParams.userUids.resize(0);
        _burnParams.userUids.push_back(_flintParams.baseUid);
    }
    if (_burnParams.userMacsSpecified) {
        if (!_burnParams.userGuidsSpecified) {
            //we dont care about the first 4 values
            _burnParams.userUids.resize(GUIDS);
        }
        _burnParams.userUids.push_back(_flintParams.user_macs[0]);
        _burnParams.userUids.push_back(_flintParams.user_macs[1]);
    }
    if (_burnParams.vsdSpecified) {
        _burnParams.userVsd = strcpy(new char[_flintParams.vsd.size() + 1], _flintParams.vsd.c_str());
    }

    //make sure its of max size and fill the rest with 0xffff
    guid_t tmpGuid;
    tmpGuid.h = 0xffffffff;
    tmpGuid.l = 0xffffffff;
    _burnParams.userUids.resize(MAX_GUIDS, tmpGuid);
}

#define VERSION_FORMAT(minor) minor < 100 ? "%d.%d.%04d" : "%d.%04d.%04d"
bool BurnSubCommand::checkFwVersion()
{
    char curr_ver[124], new_ver[124];
    printf("\n");
    printf("    Current FW version on flash:  ");
    if (_devInfo.fw_info.fw_ver[0] != 0) {
        // i.e if we have a fw_version we assume this is != 0
        snprintf(curr_ver, 124, VERSION_FORMAT(_devInfo.fw_info.fw_ver[1]), _devInfo.fw_info.fw_ver[0], _devInfo.fw_info.fw_ver[1], _devInfo.fw_info.fw_ver[2]);
    } else {
        snprintf(curr_ver, 124, "N/A");
    }
    printf("%s", curr_ver); printf("\n");

    printf("    New FW version:               ");
    if (_imgInfo.fw_info.fw_ver[0] != 0) {
        snprintf(new_ver, 124, VERSION_FORMAT(_imgInfo.fw_info.fw_ver[1]), _imgInfo.fw_info.fw_ver[0], _imgInfo.fw_info.fw_ver[1], _imgInfo.fw_info.fw_ver[2]);
    } else {
        snprintf(new_ver, 124, "N/A");
    }
    printf("%s", new_ver); printf("\n");

    if (_flintParams.log_specified) {
        print_line_to_log("Current FW version on flash: %s,  New FW version: %s\n", curr_ver, new_ver);
    }
    int verStatus;

    if (_devInfo.fw_info.fw_ver[0] != 0  &&
        _imgInfo.fw_info.fw_ver[0] != 0) {
        // nofs pitfall here - on nofs burn no fwver of device
        verStatus = FwOperations::FwVerLessThan(_devInfo.fw_info.fw_ver, _imgInfo.fw_info.fw_ver);
        if (verStatus == FVI_EQUAL || verStatus == FVI_GREATER) {
            printf("\n    Note: The new FW version is %s the current FW version on flash.\n", verStatus == FVI_EQUAL ? "the same as" : "older than");
            if (!askUser()) {
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
    if (strlen(_imgInfo.fw_info.psid) != 0  && strlen(_devInfo.fw_info.psid) != 0 &&
        strncmp(_imgInfo.fw_info.psid, _devInfo.fw_info.psid, PSID_LEN)) {
        if (_flintParams.allow_psid_change) {
            printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"
                   "    Note: It is highly recommended not to change the PSID.\n",
                   _devInfo.fw_info.psid, _imgInfo.fw_info.psid);
            if (!askUser()) {
                return false;
            }
        } else {
            printf("\n");
            reportErr(true, FLINT_PSID_ERROR, _devInfo.fw_info.psid, _imgInfo.fw_info.psid);
            return false;
        }
    }
    return true;
}

FlintStatus BurnSubCommand::burnFs3()
{
    bool printPreparing = false;
    if (_devQueryRes) {
        char errBuff[ERR_BUFF_SIZE] = {0};
        FwOperations::fw_ops_params_t fwParams;
        initDeviceFwParams(errBuff, fwParams);
        FsChecks fsChecks(_devInfo, _fwOps, _imgOps, _burnParams, fwParams);
        if (fsChecks.ExecuteChecks(&_fwOps, _burnParams, _devInfo)) {
            vector<string> questions;
            fsChecks.GetUserQuestions(questions, "    ");
            delete[] fwParams.mstHndl;
            for (unsigned int i = 0; i < questions.size(); i++) {
                printf("\n%s\n", questions[i].c_str());
                if (!askUser()) {
                    return FLINT_FAILED;
                }
            }
        } else {
            delete[] fwParams.mstHndl;
            reportErr(true, "Fixes is needed for Flash layout, an error occurred while preparing the operation");
            return FLINT_FAILED;
        }
        printPreparing = fsChecks._isTimeConsumingFixesNeeded;
    }

    // Here we want to burn FS3 device so we check if the image is indeed FS3 image
    if (_imgInfo.fw_type != FIT_FS3 && _imgInfo.fw_type != FIT_FS4) {
        reportErr(true, FLINT_IMG_DEV_COMPAT_ERROR, "FS3", "FS3");
        return FLINT_FAILED;
    }
    const char *imgTypeStr = fwImgTypeToStr(_imgInfo.fw_type);
    // on FS3 burn we require query to pass
    if (!_devQueryRes && _burnParams.burnFailsafe) {
        reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr,  _fwOps->err());
        return FLINT_FAILED;
    }
    //check FwVersion
    if (!checkFwVersion()) {
        return FLINT_BURN_ABORTED;
    }
    // check Psid
    if (_devQueryRes && !checkPSID()) {
        return FLINT_FAILED;
    }
    // deal with rom
    if (!dealWithExpRom()) {
        return FLINT_FAILED;
    }
    bool getRomFromDev = (_burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST);
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo)) {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type, \
               _imgInfo.fw_info.roms_info.exp_rom_com_devid);
        if (!askUser()) {
            return FLINT_FAILED;
        }
    }
    if (!_burnParams.burnFailsafe) {
        printf("Burn process will not be failsafe. No checks will be performed.\n");
        if (_burnParams.useImgDevData) {
            printf("ALL flash, including the device data sections will be overwritten.\n");
        }
        printf("If this process fails, computer may remain in an inoperable state.\n");
        if (!askUser()) {
            return FLINT_FAILED;
        }
    }

    if (printPreparing) {
        printf(" Preparing...\n");
    }

    if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams)) {
        reportErr(true, FLINT_FSX_BURN_ERROR, imgTypeStr, _fwOps->err());
        return FLINT_FAILED;
    }
    PRINT_PROGRESS(_burnParams.progressFunc, 101);
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    const char *resetRec = _fwOps->FwGetResetRecommandationStr();
    if (resetRec) {
        printf("-I- %s\n", resetRec);
    }
    return FLINT_SUCCESS;
}

FlintStatus BurnSubCommand::burnFs2()
{

    if (_flintParams.striped_image) {
        reportErr(true, FLINT_FS2_STRIPED_ERROR);
        return FLINT_FAILED;
    }
    if (_imgInfo.fw_type != FIT_FS2) {
        reportErr(true, FLINT_IMG_DEV_COMPAT_ERROR, "FS2", "FS2");
        return FLINT_FAILED;
    }

    //CheckMatchingHwDevId is done in mlxfwops burn routine.
    //CheckMatchingDevId is done in mlxfwops burn routine.

    (void)dealWithExpRom();
    bool getRomFromDev = _burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo)) {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type, \
               _imgInfo.fw_info.roms_info.exp_rom_com_devid);
        if (!askUser()) {
            return FLINT_FAILED;
        }
    }

    //deal with guids
    if (!dealWithGuids()) {
        return FLINT_FAILED;
    }

    //deal with failsifity should be made in fwops as we dont know if image/device fw is failsafe
    if (_burnParams.burnFailsafe & (!_imgInfo.fw_info.is_failsafe || !_devInfo.fw_info.is_failsafe)) {

        if ((!_imgInfo.fw_info.is_failsafe && !_devInfo.fw_info.is_failsafe)) {
            // When both image and flash are non-failsafe, flint will burn in a non-failsafe mode
            _burnParams.burnFailsafe = false;
        } else {
            // when only one of image and flash is non-failsafe, flint will fail with appropriate message
            reportErr(true, "Failsafe burn failed: FW image in the %s is non failsafe.\n"
                      "    you cannot burn a%s failsafe image over a%s failsafe image in a failsafe mode.\n"
                      "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n",
                      _imgInfo.fw_info.is_failsafe ? "flash" : "given file",  _imgInfo.fw_info.is_failsafe ? "" : " non", \
                      _devInfo.fw_info.is_failsafe ? "" : " non");
            return FLINT_FAILED;
        }
    }

    //deal with vsd
    if (!dealWithVSD()) {
        return FLINT_FAILED;
    }

    //check versions
    if (!checkFwVersion()) {
        return FLINT_BURN_ABORTED;
    }
    //check Psid
    if (_devQueryRes && !checkPSID()) {
        return FLINT_FAILED;
    }

    // Warn if a fw which does not support config is burnt over fw that does support config
    // The other way (new fw with config, old fw w/o config) is a normal update flow.
    // Update: all fw should now support config sectors, so we just check any mismatch in the config pads


    // Verify config offset. Should never be different between image and flash (unless changing PSID).
    if (_imgInfo.fs2_info.config_pad != _devInfo.fs2_info.config_pad) {
        printf("\n");
        printf("-W- Configuration section offset on flash (%u sectors) differs from the"
               " Configuration section offset in the given image (%u sectors)."
               " Current device configuration (if exists) will be deleted.\n",
               _devInfo.fs2_info.config_pad,
               _imgInfo.fs2_info.config_pad);
        if (_burnParams.allowPsidChange) {
            if (!askUser()) {
                return FLINT_FAILED;
            }
        } else {
            reportErr(true, "Use the '-allow_psid_change' flag to force this change.\n");
            return FLINT_FAILED;
        }
    }

    if (!_burnParams.burnFailsafe) {
        printf("Burn process will not be failsafe. No checks will be performed.\n");
        printf("ALL flash, including the Invariant Sector will be overwritten.\n");
        printf("If this process fails, computer may remain in an inoperable state.\n");
        if (!askUser()) {
            return FLINT_FAILED;
        }
    }

    //Finally we can burn
    if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams)) {
        reportErr(true, FLINT_FS2_BURN_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    PRINT_PROGRESS(_burnParams.progressFunc, 101);
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    if (_burnParams.burnStatus.imageCachedSuccessfully) {
        PRINT_PROGRESS(_burnParams.progressFunc, 102);
    }
    return FLINT_SUCCESS;
}

bool BurnSubCommand::dealWithVSD()
{
    if (!(_burnParams.vsdSpecified || _burnParams.useImagePs) && !((strlen(_devInfo.fw_info.psid) != 0 \
                                                                    && _devInfo.fw_info.vsd_sect_found))) {
        printf("\n");
        if (_burnParams.burnFailsafe) {
            reportErr(true, "Can not extract VSD/PSID info from flash.\n"
                      "    Can not burn in a failsafe mode. Please use \"-nofs\" flag to burn in a non failsafe mode.\n");
            return false;
        } else {
            printf("-W- Can not extract VSD/PSID info from flash.\n\n"
                   "    To use a specific VSD, abort and re-burn specifying the\n"
                   "    needed info (using command line flags -vsd / -use_image_ps).\n"
                   "    You can also continue burn using blank VSD.\n");
            if (!askUser()) {
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
    FwOperations::SetDevFlags(_imgInfo.fw_info.chip_type, _imgInfo.fw_info.dev_type, (fw_img_type)_imgInfo.fw_type, ib_dev, eth_dev);
    //setDevFlags(_imgInfo, ib_dev, eth_dev);

    // Check if there is a need to read guids
    if (_burnParams.useImageGuids || _burnParams.blankGuids
        || (_burnParams.userGuidsSpecified && ib_dev)
        || (_burnParams.userMacsSpecified)) {
        read_guids = false;
    }
    // Check if the burnt FW is ok and readable in order to get the GUIDs later
    if (read_guids && !_devQueryRes) {
        //printMissingGuidErr(ib_dev, eth_dev);
        if (_burnParams.burnFailsafe) {
            reportErr(true,
                      "Can not extract GUIDs/MACs info from flash, %s\n"
                      "    Can not burn in a failsafe mode.\n"
                      "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n", _fwOps->err());
        } else {
            reportErr(true, "Can not extract GUIDs/MACs info from flash, %s", _fwOps->err());
            printMissingGuidErr(ib_dev, eth_dev);
        }
        return false;
    }
    // Check guids flag to ensure correct patching of guids in mlxfwops
    bool is_guids_specified = _burnParams.userGuidsSpecified
                              || _burnParams.userMacsSpecified
                              || _burnParams.userUidSpecified;
    if (is_guids_specified) {
        if (!checkGuidsFlags(_imgInfo.fw_info.dev_type, _fwType, \
                              _burnParams.userGuidsSpecified, _burnParams.userMacsSpecified, _burnParams.userUidSpecified, ib_dev, eth_dev)) {
            return false;
        }
    }
    //report guid changes if needed. and update the user_guids vector in _burnParams
    if (is_guids_specified || _flintParams.use_image_guids) {
        guid_t *new_guids = (_burnParams.userGuidsSpecified || _burnParams.userUidSpecified) ? \
                            &_burnParams.userUids[0] : _devInfo.fs2_info.guids;
        guid_t *new_macs = _burnParams.userMacsSpecified != 0 ? &_burnParams.userUids[GUIDS] : &_devInfo.fs2_info.guids[GUIDS];
        guid_t *old_guids = !_devQueryRes ? NULL : _devInfo.fs2_info.guids;
        guid_t *old_macs = old_guids != NULL ? &old_guids[GUIDS] : NULL;
        if (!is_guids_specified && _flintParams.use_image_guids) {
            new_guids = _imgInfo.fs2_info.guids;
            new_macs = &_imgInfo.fs2_info.guids[GUIDS];
        }
        //printf("-D- l=%d, h=%d\n", new_macs->l, new_macs->h);
        if (!reportGuidChanges(new_guids, new_macs, old_guids, old_macs, ib_dev, \
                               eth_dev, _imgInfo.fs2_info.guid_num)) {
            return false;
        }

    }
    return true;
}

#define IS_HCA(chipType) \
    (((chipType) == CT_CONNECTX) || ((chipType) == CT_CONNECT_IB) || ((chipType) == CT_CONNECTX4) || ((chipType) == CT_CONNECTX4_LX) || ((chipType) == CT_CONNECTX5) || ((chipType) == CT_BLUEFIELD))

bool BurnSubCommand::dealWithExpRom()
{
    bool getRomFromDev = false;

    // Check exp rom:
    bool fs2Cond;

    if (_fwType != FIT_FS2) {
        _burnParams.burnRomOptions =
            FwOperations::ExtBurnParams::BRO_ONLY_FROM_IMG;
        bool cond = _devQueryRes && IS_HCA(_devInfo.fw_info.chip_type);
        if (cond && _flintParams.use_dev_rom) {
            if (_devInfo.fw_info.roms_info.num_of_exp_rom > 0) {
                if (!strcmp(_devInfo.fw_info.product_ver, "") && !strcmp(_imgInfo.fw_info.product_ver, "")) {
                    _burnParams.burnRomOptions =
                        FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
                } else if (_flintParams.allow_rom_change) {
                    _burnParams.burnRomOptions =
                        FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
                } else {
                    //error, please use allow_rom_change flag
                    reportErr(true, "The device FW contains common FW/ROM Product Version - "
                              "The ROM cannot be updated separately.\n");
                    return false;
                }
            } else {
                if (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0) {
                    if (!askUser("No Expansion ROM found in the device, "
                                 "Do you want to use the ROM from the image file",
                                 false)) {
                        return false;
                    }
                } else {
                    if (!askUser("No Expansion ROM found in the device"
                                 ", Do you want to continue")) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    fs2Cond = (_devQueryRes && IS_HCA(_devInfo.fw_info.chip_type) && \
               (FwOperations::IsFwSupportingRomModify(_devInfo.fw_info.fw_ver) || (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0)) \
               && !_flintParams.use_image_rom && !strcmp(_devInfo.fw_info.product_ver, "") && !strcmp(_imgInfo.fw_info.product_ver, ""));

    if (fs2Cond) {
        // Enter here when:
        //                  The fw on the flash is OK (passed query, and it should pass verify in mlxfwops) &&
        //                  ( The device is connectx ||  connectib    )&&
        //                  The image fw supports modifying ROM OR it contains ROM &&.
        //                  The user didn't ask to burn the image rom. &&
        //                  The  fw on the flash doesn't contain product version

        if (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0 && _devInfo.fw_info.roms_info.num_of_exp_rom > 0) {
            printf("\n    Note: Both the image file and the flash contain a ROM image.\n"
                   "          Select \"yes\" to use the ROM from the given image file.\n"
                   "          Select \"no\" to keep the existing ROM in the flash\n");

            displayExpRomInfo(_devInfo.fw_info.roms_info, "    Current ROM info on flash: ");
            displayExpRomInfo(_imgInfo.fw_info.roms_info, "    ROM info from image file : ");
            if (!askUser("Use the ROM from the image file", false)) {
                getRomFromDev = true;
            } else {
                getRomFromDev = false;
            }
        } else if (!(_imgInfo.fw_info.roms_info.num_of_exp_rom > 0) && _devInfo.fw_info.roms_info.num_of_exp_rom > 0) {
            getRomFromDev = true;
        }
    }
    if (getRomFromDev) {
        _burnParams.burnRomOptions = FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
    }
    return true;
}

bool BurnSubCommand::checkMatchingExpRomDevId(const fw_info_t& info)
{
    if ((info.fw_info.roms_info.num_of_exp_rom > 0) && (info.fw_info.dev_type)
        && (info.fw_info.roms_info.exp_rom_com_devid != EXP_ROM_GEN_DEVID) \
        && (info.fw_info.roms_info.exp_rom_com_devid != MISS_MATCH_DEV_ID)
        && (info.fw_info.dev_type != info.fw_info.roms_info.exp_rom_com_devid)) {
        return false;
    }
    return true;
}

FlintStatus BurnSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //set fw type
    _fwType = _fwOps->FwType();
    // query both image and device (deviceQuery can fail but we save rc)
    _devQueryRes = _fwOps->FwQuery(&_devInfo);
    if (!_imgOps->FwQuery(&_imgInfo)) {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "image", _flintParams.image.c_str(), _imgOps->err());
        return FLINT_FAILED;
    }
    //updateBurnParams with input given by user
    updateBurnParams();

    if (_fwType == FIT_FS3 || _fwType == FIT_FS4 || _fwType == FIT_FSCTRL) {
        return burnFs3();
    } else if (_fwType == FIT_FS2) {
        return burnFs2();
    }
    // unknown fw type
    reportErr(true, FLINT_UNKNOWN_FW_TYPE_ERROR);
    return FLINT_FAILED;
}

/***********************
 * Class: QuerySubCommand
 **********************/

bool QuerySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "full") {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "full");
        return false;
    }
    return true;
}

bool QuerySubCommand::checkMac(u_int64_t mac, string& warrStr)
{
    if ((mac >> 40) & 0x1) {

        warrStr = FLINT_MULTI_BIT_WARNING;
        return false;
    }

    if (mac >> 48) {
        warrStr = FLINT_MORE_48_BITS_WARNING;
        return false;
    }

    return true;
}

bool QuerySubCommand::displayFs2Uids(const fw_info_t& fwInfo)
{
    const char *mac_indent = "";
    bool ibDev;
    bool ethDev;
    FwOperations::SetDevFlags(fwInfo.fw_info.chip_type, fwInfo.fw_info.dev_type, (fw_img_type)fwInfo.fw_type, ibDev, ethDev);
    //setDevFlags(fwInfo, ibDev, ethDev);
    int numPorts = 2;
    if ((fwInfo.fw_info.chip_type == CT_IS4 || fwInfo.fw_info.chip_type == CT_SWITCHX)) {
        numPorts = 0;
    }
    //we do not support cards with one port anymore.

    // GUIDS:
    if (ibDev) {
        //report("GUID Des:        Node             Port1            ");
        printf("Description:           Node             ");
        if (numPorts > 0) {
            printf("Port1            ");
        }
        if (numPorts > 1) {
            printf("Port2            ");
        }
        printf("Sys image\n");

        printf("GUIDs:                 ");
        for (u_int32_t i = 0; i < GUIDS; i++) {
            if ((i == 1 && numPorts < 1) ||
                (i == 2 && numPorts < 2)) {
                continue;
            }
            printf(GUID_FORMAT " ", fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l);
        }
        if (numPorts > 0) {
            mac_indent = "                 ";
        }
    }
    // MACS:
    if (ethDev) {
        if (fwInfo.fs2_info.guid_num == 6) {
            if (!ibDev) {
                printf("Description:  %s    Port1            Port2\n", mac_indent);
            } else if (fwInfo.fw_info.chip_type == CT_SWITCHX) {
                printf("\nDescription:           Base             Switch\n");
            } else {
                printf("\n");
            }
            printf("MACs:          %s       ", mac_indent);
            for (u_int32_t i = GUIDS; i < 6; i++) {
                printf("     " MAC_FORMAT, fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l);
            }

            for (u_int32_t i = GUIDS; i < 6; i++) {
                u_int64_t mac = (((u_int64_t)fwInfo.fs2_info.guids[i].h) << 32) | fwInfo.fs2_info.guids[i].l;
                string warrStr;
                if (!fwInfo.fs2_info.blank_guids && !checkMac(mac, warrStr)) {
                    if (i == GUIDS) {
                        printf("\n\n");
                    }
                    printf(FLINT_BAD_MAC_ADRESS_WARNING, fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l, warrStr.c_str());
                }
            }
        } else {
            printf(FLINT_MAC_ENTRIES_WARNING, 6, fwInfo.fs2_info.guid_num);
        }
    }

    printf("\n");
    return true;
}
#define NA_STR "N/A"
#define BASE_STR "Base"
#define PRINT_FS3_OR_NEWER_UID(uid1, str, printStep, isGuid) \
    if (uid1.uid) { \
        if (isGuid) { \
            printf("%-18s     %016" U64H_FMT_GEN, str, uid1.uid); \
        } else { \
            printf("%-18s     %012" U64H_FMT_GEN "    ", str, uid1.uid); \
        } \
    } else { \
        printf("%-18s     %-16s", str, NA_STR); \
    } \
    if (uid1.num_allocated) { \
        printf("        %d", uid1.num_allocated); \
    } else { \
        printf("       %s", NA_STR); \
    } \
    if (printStep) { \
        if (uid1.step) { \
            printf("        %d", uid1.step); \
        } else { \
            printf("       %s", NA_STR); \
        } \
    } \
    printf("\n");

static inline void printFs3OrNewerUids(struct fs3_uid_entry uid, struct fs3_uid_entry orig_uid, string guidMac, bool printStep)
{
    string prefix = BASE_STR + string(" ") + guidMac + ":";
    bool isGuid = guidMac.find("GUID") != string::npos ? true : false;

    PRINT_FS3_OR_NEWER_UID(uid, prefix.c_str(), printStep, isGuid);
    if (uid.uid !=  orig_uid.uid || uid.num_allocated != orig_uid.num_allocated  || (printStep && uid.step != orig_uid.step)) {
        // Print MFG UIDs as well
        prefix = "Orig " + prefix;
        PRINT_FS3_OR_NEWER_UID(orig_uid, prefix.c_str(), printStep, isGuid);
    }
}

bool QuerySubCommand::displayFs3Uids(const fw_info_t& fwInfo)
{
    if (fwInfo.fs3_info.fs3_uids_info.valid_field) {
        // new GUIDs format
        printf("Description:           UID                GuidsNumber\n");
        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cx4_uids.base_guid, fwInfo.fs3_info.orig_fs3_uids_info.cx4_uids.base_guid, "GUID", false);
        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cx4_uids.base_mac, fwInfo.fs3_info.orig_fs3_uids_info.cx4_uids.base_mac, "MAC", false);
    } else {
        printf("Description:           UID                GuidsNumber  Step\n");
        string firstGuid = (fwInfo.fw_info.chip_type != CT_SWITCH_IB) ? "GUID1" : "GUID";
        string firstMac = (fwInfo.fw_info.chip_type != CT_SWITCH_IB) ? "MAC1" : "MAC";

        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.guids[0], fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.guids[0], firstGuid, true);
        if (fwInfo.fw_info.chip_type != CT_SWITCH_IB) {
            printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.guids[1], fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.guids[1], "GUID2", true);
        }
        printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.macs[0], fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.macs[0], firstMac, true);
        if (fwInfo.fw_info.chip_type != CT_SWITCH_IB) {
            printFs3OrNewerUids(fwInfo.fs3_info.fs3_uids_info.cib_uids.macs[1], fwInfo.fs3_info.orig_fs3_uids_info.cib_uids.macs[1], "MAC2", true);
        }
    }
    return true;
}

string QuerySubCommand::printSecurityAttrInfo(u_int32_t m)
{
    string attr = "";
    if (m & SMM_SECURE_FW) {
        attr += "secure-fw";
    } else if (m & SMM_SIGNED_FW) {
        attr += "signed-fw";
    } else {
        attr += NA_STR;
        return attr;
    }
    if (m & SMM_DEBUG_FW) {
        attr += ", debug";
    }
    if (m & SMM_DEV_FW) {
        attr += ", dev";
    }
    if (m & SMM_CS_TOKEN) {
        attr += ", cs-token";
    }
    if (m & SMM_DBG_TOKEN) {
        attr += ", dbg-token";
    }
    return attr;
}

FlintStatus QuerySubCommand::printInfo(const fw_info_t& fwInfo, bool fullQuery)
{
    bool isFs2    = (fwInfo.fw_type == FIT_FS2) ? true : false;
    bool isFs3    = (fwInfo.fw_type == FIT_FS3) ? true : false;
    bool isFs4    = (fwInfo.fw_type == FIT_FS4) ? true : false;
    bool isFsCtrl = (fwInfo.fw_type == FIT_FSCTRL) ? true : false;

    printf("Image type:            %s\n", fwImgTypeToStr(fwInfo.fw_type));

    if (fwInfo.fw_info.fw_ver[0] || fwInfo.fw_info.fw_ver[1] || fwInfo.fw_info.fw_ver[2]) {
        char versionStr[64] = {0};
        snprintf(versionStr, 64, VERSION_FORMAT(fwInfo.fw_info.fw_ver[1]), fwInfo.fw_info.fw_ver[0], fwInfo.fw_info.fw_ver[1],
                 fwInfo.fw_info.fw_ver[2]);
        printf("FW Version:            %s\n", versionStr);
        if (nextBootFwVer) {
            return FLINT_SUCCESS;
        }
        if ((fwInfo.fw_info.running_fw_ver[0] || fwInfo.fw_info.running_fw_ver[1] || fwInfo.fw_info.running_fw_ver[2]) && \
            (fwInfo.fw_info.running_fw_ver[0] != fwInfo.fw_info.fw_ver[0] || \
             fwInfo.fw_info.running_fw_ver[1] != fwInfo.fw_info.fw_ver[1] || \
             fwInfo.fw_info.running_fw_ver[2] != fwInfo.fw_info.fw_ver[2])) {
            snprintf(versionStr, 64, VERSION_FORMAT(fwInfo.fw_info.running_fw_ver[1]), fwInfo.fw_info.running_fw_ver[0], fwInfo.fw_info.running_fw_ver[1],
                     fwInfo.fw_info.running_fw_ver[2]);
            printf("FW Version(Running):   %s\n", versionStr);
        }
    }
    else if (nextBootFwVer) {
        char versionStr[64] = {0};
        if (!fwInfo.fw_info.fw_ver[0] || fwInfo.fw_info.fw_ver[1] || fwInfo.fw_info.fw_ver[2]) {
            snprintf(versionStr, 64, VERSION_FORMAT(fwInfo.fw_info.running_fw_ver[1]), fwInfo.fw_info.running_fw_ver[0], fwInfo.fw_info.running_fw_ver[1],
                 fwInfo.fw_info.running_fw_ver[2]);
            printf("FW Version:            %s\n", versionStr);
        }
    }
    if (nextBootFwVer) {
        return FLINT_SUCCESS;
    }

    if (fwInfo.fw_info.fw_rel_date[0] || fwInfo.fw_info.fw_rel_date[1] || fwInfo.fw_info.fw_rel_date[2]) {
        printf("FW Release Date:       %x.%x.%x\n", fwInfo.fw_info.fw_rel_date[0], fwInfo.fw_info.fw_rel_date[1], \
               fwInfo.fw_info.fw_rel_date[2]);
    }

    if (fullQuery) {
        // there is no full query atm just quick query
        if (fwInfo.fw_info.min_fit_ver[0] || fwInfo.fw_info.min_fit_ver[1] \
            || fwInfo.fw_info.min_fit_ver[2] || fwInfo.fw_info.min_fit_ver[3]) {
            printf("Min FIT Version:       %d.%d.%d.%d\n", fwInfo.fw_info.min_fit_ver[0], \
                   fwInfo.fw_info.min_fit_ver[1], fwInfo.fw_info.min_fit_ver[2], fwInfo.fw_info.min_fit_ver[3]);
        }
        if ((fwInfo.fw_info.mic_ver[0] || fwInfo.fw_info.mic_ver[1] || fwInfo.fw_info.mic_ver[2])) {
            printf("MIC Version:           %d.%d.%d\n", fwInfo.fw_info.mic_ver[0], \
                   fwInfo.fw_info.mic_ver[1], fwInfo.fw_info.mic_ver[2]);
        }
        if (isFs2) {
            if (fwInfo.fs2_info.config_sectors) {
                printf("Config Sectors:        %d\n", fwInfo.fs2_info.config_sectors);
            }
            if (fwInfo.fs2_info.config_pad) {
                printf("Config Pad:            %d\n", fwInfo.fs2_info.config_pad);
            }
            if (strlen(fwInfo.fs2_info.prs_name)) {
                printf("PRS Name:              %s\n", fwInfo.fs2_info.prs_name);
            }
        } else {
            // FS3
            if (strlen(fwInfo.fs3_info.prs_name)) {
                printf("PRS Name:              %s\n", fwInfo.fs3_info.prs_name);
            }
            if (strlen(fwInfo.fs3_info.orig_prs_name)) {
                printf("Orig PRS Name:         %s\n", fwInfo.fs3_info.orig_prs_name);
            }
            if (strlen(fwInfo.fs3_info.name)) {
                printf("Part Number:           %s\n", fwInfo.fs3_info.name);
            }
            if (strlen(fwInfo.fs3_info.description)) {
                printf("Description:           %s\n", fwInfo.fs3_info.description);
            }
        }
    }

    if (strlen(fwInfo.fw_info.product_ver)) {
        printf("Product Version:       %s\n", fwInfo.fw_info.product_ver);
    }

    if (fwInfo.fw_info.roms_info.exp_rom_found) {
        displayExpRomInfo(fwInfo.fw_info.roms_info, "Rom Info:              ");
    }
    else {
        printf("Rom Info:              N/A\n");
    }

    if (isFs2) {
        printf("Device ID:             %d\n", fwInfo.fw_info.dev_type);
    }

    if (isFs2 && fwInfo.fs2_info.access_key_exists) {
        printf("HW Access Key:         ");
        if (fwInfo.fs2_info.access_key_value.l || fwInfo.fs2_info.access_key_value.h) {
            printf("Enabled\n");
        } else {
            printf("Disabled\n");
        }
    }

    if (!isFs2) {
        /*i.e its fs3/fs4*/
        if (!displayFs3Uids(fwInfo)) {
            return FLINT_FAILED;
        }
    } else {
        if (!displayFs2Uids(fwInfo)) {
            return FLINT_FAILED;
        }
    }

    // VSD, PSID
    if (!fwInfo.fw_info.vsd_vendor_id || fwInfo.fw_info.vsd_vendor_id == MELLANOX_VENDOR_ID) {
        if (!isFs2) {
            const char *imageVSD = fwInfo.fs3_info.image_vsd;
            const char *deviceVSD = fwInfo.fw_info.vsd;
            if (strlen(imageVSD) == 0) {
                imageVSD = NA_STR;
            }
            if (strlen(deviceVSD) == 0) {
                deviceVSD = NA_STR;
            }
            printf("Image VSD:             %s\n", imageVSD);
            printf("Device VSD:            %s\n", deviceVSD);
            printf("PSID:                  %s\n", fwInfo.fw_info.psid);
            if (strncmp(fwInfo.fw_info.psid, fwInfo.fs3_info.orig_psid, 13) != 0) {
                if (strlen(fwInfo.fs3_info.orig_psid)) {
                    printf("Orig PSID:             %s\n", fwInfo.fs3_info.orig_psid);
                } else {
                    printf("Orig PSID:             %s\n", NA_STR);
                }
            }
        } else {
            printf("VSD:                   %s\n", fwInfo.fw_info.vsd);
            printf("PSID:                  %s\n", fwInfo.fw_info.psid);
        }
    } else {
        printf(FLINT_NOT_MLNX_FW_WARNING, fwInfo.fw_info.vsd_vendor_id);
    }

    if (isFs3 || isFs4 || isFsCtrl) {
        printf("Security Attributes:   %s\n",
               printSecurityAttrInfo(fwInfo.fs3_info.security_mode).c_str());
    }
    if ((isFs3 || isFs4 || isFsCtrl) && fullQuery) {
        string updateMethod = "Legacy";
        if (fwInfo.fs3_info.security_mode & SMM_MCC_EN) {
            updateMethod = "fw_ctrl";
        }
        printf("Default Update Method: %s\n", updateMethod.c_str());
    }
    if (isFs2 && fwInfo.fs2_info.blank_guids) {
        //blankGuids only exsists in FS2 image type in mlxfwops why?
        printf(FLINT_BLANK_GUIDS_WARNING);
    }
    return FLINT_SUCCESS;
}

QuerySubCommand:: QuerySubCommand()
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

QuerySubCommand:: ~QuerySubCommand()
{

}

FlintStatus QuerySubCommand::executeCommand()
{
    if (_flintParams.low_cpu) {
        increase_poll_time = 1;
    }
    if (_flintParams.next_boot_fw_ver) {
        nextBootFwVer = true;
    }
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    fw_info_t fwInfo;
    FwOperations *ops;
    bool fullQuery = false;
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    if (!ops->FwQuery(&fwInfo, !_flintParams.skip_rom_query, _flintParams.striped_image)) {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, _flintParams.device_specified ? "Device" : "image",
                  _flintParams.device_specified ? _flintParams.device.c_str() : _flintParams.image.c_str(), ops->err());
        return FLINT_FAILED;
    }
    //print fw_info nicely to the user
    // we actually dont use "regular" query , just quick
    //ORENK - no use to display quick query message to the user if we dont do it in any other way
    if (_flintParams.cmd_params.size() == 1) {
        fullQuery = true;
    }
    return printInfo(fwInfo, fullQuery);
}

/***********************
* Class: VerifySubCommand
***********************/
VerifySubCommand:: VerifySubCommand()
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

VerifySubCommand:: ~VerifySubCommand()
{

}

bool VerifySubCommand::verifyParams()
{

    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "showitoc") {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "swhoitoc");
        return false;
    }

    return true;
}




FlintStatus VerifySubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops;
    bool showItoc = (_flintParams.cmd_params.size() == 1) ? true : false;
    //check on what we are wroking
    int opaque = 0;
    ProgressCallBackAdvSt advProgress;
    advProgress.func = (f_prog_func_adv) & advProgressFunc;
    advProgress.opaque = &opaque;
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    FwOperations::ExtVerifyParams verifyParams(&verifyCbFunc);
    verifyParams.isStripedImage = _flintParams.striped_image;
    verifyParams.showItoc = showItoc;
    verifyParams.progressFuncAdv = &advProgress;
    if (!ops->FwVerifyAdv(verifyParams)) {
        printf("\n\n");
        reportErr(true, FLINT_CMD_VERIFY_ERROR, ops->err());

        return FLINT_FAILED;
    }
    //get status of blank guids in fs2 only can either bring from FwVerify as another parameter. ask mohammad
    if (ops->FwType() == FIT_FS2) {
        fw_info_t fwInfo;
        if (!ops->FwQuery(&fwInfo, true,  _flintParams.striped_image)) {
            printf("\n\n");
            reportErr(true, "Failed to get Guids status. %s\n", ops->err());
            return FLINT_FAILED;
        }
        if (fwInfo.fs2_info.blank_guids) {
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
SwResetSubCommand:: SwResetSubCommand()
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

SwResetSubCommand:: ~SwResetSubCommand()
{

}


bool SwResetSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus SwResetSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    printf("-I- Sending reset command to device %s ...\n", _flintParams.device.c_str());
    if (!_fwOps->FwSwReset()) {
        reportErr(true, FLINT_SWRESET_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf("-I- Reset command accepted by the device.\n");
    return FLINT_SUCCESS;
}

/***********************
 * Class: BromSubCommand
 **********************/
BromSubCommand:: BromSubCommand()
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

BromSubCommand:: ~BromSubCommand()
{
    closeLog();
    _fRom.close();
}

FlintStatus BromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;
    // query device
    if (!ops->FwQuery(&_info)) {
        reportErr(true, FLINT_FAILED_QUERY_ERROR, "Device", _flintParams.device.c_str(),
                  ops->err());
        return FLINT_FAILED;
    }
    // get roms info
    if (!_fRom.open(_flintParams.cmd_params[0].c_str())) {
        reportErr(true, FLINT_BROM_ERROR, _fRom.err());
        return FLINT_FAILED;
    }
    if (!getRomsInfo(&_fRom, _romsInfo)) {
        return FLINT_FAILED;
    }
    //check devids
    if ((_romsInfo.num_of_exp_rom > 0) && (_info.fw_info.dev_type)
        && (_romsInfo.exp_rom_com_devid != EXP_ROM_GEN_DEVID) \
        && (_romsInfo.exp_rom_com_devid != MISS_MATCH_DEV_ID)
        && (_info.fw_info.dev_type != _romsInfo.exp_rom_com_devid)) {
        printf("-W- Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", \
               _info.fw_info.dev_type, _romsInfo.exp_rom_com_devid);
        if (!askUser()) {
            return FLINT_FAILED;
        }
    }
    char romVer1[50], romVer2[50];
    printf("\n");
    const char *infoStr = "    Current ROM info on flash: ";
    const char *infoStr2 = "    New ROM info:              ";
    if (_info.fw_info.roms_info.num_of_exp_rom > 0) {
        displayExpRomInfo(_info.fw_info.roms_info, infoStr);
        sprintf(romVer1, "%s", getExpRomVerStr(_info.fw_info.roms_info.rom_info[0]).c_str());
    } else {
        printf("%s", infoStr);
        snprintf(romVer1, 50, "N/A");
        printf("%s\n", romVer1);
    }
    displayExpRomInfo(_romsInfo, infoStr2);
    sprintf(romVer2, "%s", getExpRomVerStr(_romsInfo.rom_info[0]).c_str());
    //add new line to space up before showing burn precentage
    printf("\n");
    //print correct msg to log
    if (_info.fw_info.roms_info.num_of_exp_rom != 0) {
        print_line_to_log("Current ROM version on flash (1st ROM of %d): %s, New ROM version (1st ROM of %d): %s\n", \
                          _info.fw_info.roms_info.num_of_exp_rom, romVer1, _romsInfo.num_of_exp_rom, romVer2);
    } else {
        print_line_to_log("Current ROM version on flash: %s, New ROM version(1st ROM of %d): %s\n", romVer1, _romsInfo.num_of_exp_rom, romVer2);
    }
    // burn the rom
    printf("-I- Preparing to burn ROM ...\n");
    if (!ops->FwBurnRom(&_fRom, _flintParams.allow_rom_change, true, bromCbFunc)) {
        reportErr(true, FLINT_BROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    bromCbFunc(101);
    printf("\n");
    const char *resignStr = ops->FwGetReSignMsgStr();
    if (resignStr) {
        printf("%s", resignStr);
    }
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    return FLINT_SUCCESS;
}

/***********************
 * Class: Delete ROM
 **********************/
DromSubCommand:: DromSubCommand()
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

DromSubCommand:: ~DromSubCommand()
{

}

bool DromSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    // leave an empty line before printing from callback
    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;

    printf("\n");
    printf("-I- Preparing to remove ROM ...\n");
    if (!ops->FwDeleteRom(_flintParams.allow_rom_change, dromCbFunc)) {
        reportErr(true, FLINT_DROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    dromCbFunc(101);
    const char *resignStr = ops->FwGetReSignMsgStr();
    if (resignStr) {
        printf("%s", resignStr);
    }
    return FLINT_SUCCESS;
}
/***********************
 * Class: Read ROM
 **********************/
RromSubCommand:: RromSubCommand()
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

RromSubCommand:: ~RromSubCommand()
{

}

bool RromSubCommand::verifyParams()
{
    FILE *file;
    if ((file = fopen(_flintParams.cmd_params[0].c_str(), "r")) != NULL) {
        fclose(file);
        printf(
            "\n-W- The given ROM file is existing, you are going to overwrite it.\n");
        if (!askUser()) {
            return false;
        }
    }
    return true;
}

FlintStatus RromSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //get the rom sector if present.
    std::vector<u_int8_t> romSect;
    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwReadRom(romSect)) {
        reportErr(true, FLINT_READ_ROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    //TOCPUn(&(romSect[0]), romSect.size()/4);
    if (!writeToFile(_flintParams.cmd_params[0], romSect)) {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}



/***********************
 * Class:
 **********************/
BbSubCommand:: BbSubCommand()
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

BbSubCommand:: ~BbSubCommand()
{
    closeLog();
}

bool BbSubCommand:: verifyParams()
{
    if (_flintParams.cmd_params.size() != 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 0, (int)(_flintParams.cmd_params.size()));
        return false;
    }
    printf("\n    Note: This option is only recommended for advanced users. Press Yes to continue");
    if (!askUser()) {
        return false;
    }
    return true;
}

FlintStatus BbSubCommand:: executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    if (_fwOps->FwType() == FIT_FS3) {
        reportErr(true, FLINT_FS3_BB_ERROR);
        return FLINT_FAILED;
    }


    printf("\n");
    printf("Block burn: The given image will be burnt as is. No fields (such\n");
    printf("as GUIDS,VSD) are taken from current image on flash.\n");
    printf("Burn process will not be failsafe. No checks will be performed.\n");
    printf("ALL flash, including the Invariant Sector will be overwritten.\n");
    printf("If this process fails, computer may remain in an inoperable state.\n");
    if (!askUser()) {
        return FLINT_FAILED;
    }
    ProgressCallBack progressFunc = _flintParams.silent == true ? (ProgressCallBack)NULL : &burnBCbFunc;
    if (!_fwOps->FwBurnBlock(_imgOps, progressFunc)) {
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
SgSubCommand:: SgSubCommand()
{
    _name = "sg";
    _desc = "Set GUIDs.";
    _extendedDesc = "Set GUIDs/MACs/UIDs in the given device/image.\n"
                    "Use -guid(s), -mac(s) and -uid(s) flags to set the desired values.\n"
                    "- On pre-ConnectX devices, the sg command  is used in production to apply GUIDs/MACs values to"
                    " cards that were pre-burnt with blank GUIDs. It is not meant for use in field.\n"
                    "- On 4th generation devices, this command can operate on both image file and image on flash.\n"
                    "If the GUIDs/MACs/UIDs in the image on flash are non-blank, flint will re-burn the current"
                    " image using the given GUIDs/MACs/UIDs.";
    _flagLong = "sg";
    _flagShort = "";
    _param = "[guids_num=<num|num_port1,num_port2> step_size=<size|size_port1,size_port2>] | [nocrc]";
    _paramExp = "nocrc: (optional) When specified the flint would not update the full image crc after changing the guids\n"
                "guids_num: (optional) number of GUIDs to be allocated per physical port (FS3 Only)\n"
                "step_size: (optional) step size between GUIDs (FS3 Only)\n"
                "Note: guids_num/step_size values can be specified per port or for both ports";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " -guid 0x0002c9000100d050 sg" "\n"
               FLINT_NAME " -d " MST_DEV_EXAMPLE4 " -guid 0x0002c9000100d050 -mac 0x0002c900d050 sg";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 2;
    _cmdType = SC_Sg;
    _ops     = NULL;
    _mccSupported = true;
    memset(&_info, 0, sizeof(_info));
    memset(&_sgParams, 0, sizeof(_sgParams));
    memset(&(_sgParams.numOfGUIDsPP), 0xff, sizeof(_sgParams.numOfGUIDsPP));
    memset(&(_sgParams.stepSizePP), 0xff, sizeof(_sgParams.stepSizePP));
    _sgParams.usePPAttr = true;
}

SgSubCommand:: ~SgSubCommand()
{

}

bool SgSubCommand::verifyParams()
{
    if ((_flintParams.cmd_params.size() == 1 && _flintParams.cmd_params[0] != "nocrc") || \
        (_flintParams.cmd_params.size() == 2 && \
         !extractUIDArgs(_flintParams.cmd_params, _sgParams.numOfGUIDsPP, _sgParams.stepSizePP))) {
        reportErr(true, "The sg parameter should be \"nocrc\", \"guids_num=<num> step_size=<size>\" or nothing\n");
        return false;
    }

    if (_flintParams.cmd_params.size() > 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (!(_flintParams.guid_specified || _flintParams.guids_specified || \
          _flintParams.uid_specified || \
          _flintParams.mac_specified || _flintParams.macs_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "GUIDs / MACs / UID (using command line flags -guid(s) / -mac(s) / -uid)");
        return false;
    }
    if ((_flintParams.guid_specified || _flintParams.guids_specified) && (_flintParams.uid_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either GUIDs / UIDs (using command line flags -guid(s) / -uid)");
        return false;
    }
    if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either MACs / UIDs (using command line flags -mac(s) / -uid)");
        return false;
    }
    if (_flintParams.guid_specified && _flintParams.guids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid");
        return false;
    }
    if (_flintParams.mac_specified && _flintParams.macs_specified) {
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
    if (_sgParams.guidsSpecified) {

        _sgParams.userGuids = _flintParams.user_guids;
    }
    if (_sgParams.macsSpecified) {
        if (!_sgParams.guidsSpecified) {
            //it inits the guids with zeroes but mlxfwops will set them to 0xffff
            //can set default init if needed
            _sgParams.userGuids.resize(GUIDS);
        }
        _sgParams.userGuids.push_back(_flintParams.user_macs[0]);
        _sgParams.userGuids.push_back(_flintParams.user_macs[1]);
    }
    if (_sgParams.uidSpecified) {
        _sgParams.userGuids.resize(0);
        _sgParams.userGuids.push_back(_flintParams.baseUid);
    }
    _sgParams.userGuids.resize(MAX_GUIDS);
}

bool SgSubCommand::CheckSetGuidsFlags()
{
    bool ibDev;
    bool ethDev;
    FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev, ethDev);
    //setDevFlags(_info, ibDev,ethDev);

    if (_sgParams.macsSpecified || _sgParams.guidsSpecified || _sgParams.uidSpecified) {
        if (!checkGuidsFlags(_info.fw_info.dev_type, _info.fw_type, \
                             _sgParams.guidsSpecified, _sgParams.macsSpecified, _sgParams.uidSpecified, ibDev, ethDev)) {
            return false;
        }
    } else {
        printf("-E- ");
        printMissingGuidErr(ibDev, ethDev);
        printf("\n");
        return false;
    }

    return true;
}

FlintStatus SgSubCommand::sgFs2()
{
    //different behaviours for fs2 device with blank guids and fs2 device with guids or image
    //different behaviour if isfailesafe or not
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, _flintParams.cmd_params.size());
    }

    if (_flintParams.device_specified && !_info.fs2_info.blank_guids) {
        // 2- FS2 device with no blank Guids
        printf(FLINT_SET_GUIDS_WARRNING);
    }

    if (!CheckSetGuidsFlags()) {
        return FLINT_FAILED;
    }

    if (_flintParams.image_specified || !_info.fs2_info.blank_guids) {
        //report guid changes
        bool ethDev;
        bool ibDev;
        FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev, ethDev);
        //setDevFlags(_info, ibDev, ethDev);
        //decide what are our new guids/macs
        guid_t *new_guids = (_sgParams.guidsSpecified || _sgParams.uidSpecified) ? &_sgParams.userGuids[0] : &_info.fs2_info.guids[0];
        guid_t *new_macs =  _sgParams.macsSpecified ? &_sgParams.userGuids[GUIDS] : &_info.fs2_info.guids[GUIDS];

        if (!reportGuidChanges(new_guids, new_macs, &_info.fs2_info.guids[0], &_info.fs2_info.guids[GUIDS], ibDev, \
                               ethDev, _info.fs2_info.guid_num)) {
            return FLINT_FAILED;
        }
    }
    if (!_ops->FwSetGuids(_sgParams, &verifyCbFunc, &burnCbFs2Func)) {
        reportErr(true, FLINT_SG_GUID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    burnCbFs2Func(101);
    return FLINT_SUCCESS;
}

#define FW_RESET_MSG "To load new configuration run mlxfwreset or reboot machine"

FlintStatus SgSubCommand::sgFs3()
{
    if (!CheckSetGuidsFlags()) {
        return FLINT_FAILED;
    }
    if (_flintParams.guids_specified || _flintParams.macs_specified) {
        string flag = _flintParams.guids_specified ? "-guids" : "-macs";
        reportErr(true, FLINT_NOT_SUPP_UID_FLAG_ERROR, flag.c_str());
        return FLINT_FAILED;
    }

    // TODO: create method that checks the flags for FS3/FS2
    if (_info.fw_info.chip_type == CT_CONNECT_IB || _info.fw_info.chip_type == CT_SWITCH_IB) {
        if (!_flintParams.uid_specified) {
            reportErr(true, FLINT_NO_UID_FLAG_ERROR);
            return FLINT_FAILED;
        }
        // for connectib we just need the base guid so we put it in the first location.
        _sgParams.userGuids.resize(1);
        _sgParams.userGuids[0] = _flintParams.baseUid;
    } else {
        if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified) {
            reportErr(true, FLINT_NO_GUID_MAC_FLAGS_ERROR);
            return FLINT_FAILED;
        }
        if (_flintParams.uid_specified) {
            _sgParams.userGuids.resize(1);
            _sgParams.userGuids[0] = _flintParams.baseUid;
        } else {
            // guids and/or macs were specified
            guid_t tmpGuid;
            tmpGuid.h = 0;
            tmpGuid.l = 0;
            _sgParams.userGuids.resize(2);
            _sgParams.userGuids[0] = _sgParams.guidsSpecified ? _flintParams.user_guids[0] : tmpGuid;
            _sgParams.userGuids[1] = _sgParams.macsSpecified ? _flintParams.user_macs[0] : tmpGuid;
        }
    }

    if (!_ops->FwSetGuids(_sgParams, &verifyCbFunc)) {
        reportErr(true, FLINT_SG_UID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified) {
        printf("-I- %s\n", FW_RESET_MSG);
    }
    return FLINT_SUCCESS;
}

FlintStatus SgSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    // query device
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    bool stripedImage = _flintParams.striped_image && _flintParams.image_specified;
    if (!_ops->FwQuery(&_info, true, stripedImage)) {
        reportErr(true, FLINT_SG_GUID_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    setUserGuidsAndMacs();
    if (_info.fw_type == FIT_FS2) {
        return sgFs2();
    }
    return sgFs3();
}

/*****************************
* Class: Set Manufacture GUIDs
*****************************/
SmgSubCommand:: SmgSubCommand()
{
    _name = "smg";
    _desc = "Set manufacture GUIDs (For FS3/FS4 image only).";
    _extendedDesc = "Set manufacture GUID, Set manufacture GUIDs in the given FS3/FS4 image.\n"
                    "Use -uid flag to set the desired GUIDs, intended for production use only.";
    _flagLong = "smg";
    _flagShort = "";
    _param = "[guids_num=<num|num_port1,num_port2> step_size=<size|size_port1,size_port2>]";
    _paramExp = "guids_num: (optional) number of GUIDs to be allocated per physical port\n"
                "step_size: (optional) step size between GUIDs\n"
                "Note: guids_num/step_size values can be specified per port or for both ports";
    _example = FLINT_NAME " -i fw_image.bin -uid 0x0002c9000100d050 smg"
#ifndef __WIN__
               "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3 " -uid 0x0002c9000100d050 smg (should be used when device is idle)"
#endif
               "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE4 " -guid 0x0002c9000100d050 -mac 0x0002c900d050 smg (should be used when device is idle)";
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

SmgSubCommand:: ~SmgSubCommand()
{

}

bool SmgSubCommand::verifyParams()
{
    if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"-uid or -guid/-mac\" flags");
        return false;
    }
    if (_flintParams.guids_specified) {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, "\"-guids\"", _name.c_str(), "\"-guid\"");
        return false;
    }
    if (_flintParams.macs_specified) {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, "\"-macs\"", _name.c_str(), "\"-mac\"");
        return false;
    }
    if (_flintParams.uid_specified && (_flintParams.guid_specified || _flintParams.mac_specified)) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "\"-uid\"", "\"-guid\"/-mac\"");
        return false;
    }

    if (_flintParams.cmd_params.size() != 0 && _flintParams.cmd_params.size() != 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR4, _name.c_str(), 0, 2, _flintParams.cmd_params.size());
        return false;
    }

    if (_flintParams.cmd_params.size() == 2 && \
        !extractUIDArgs(_flintParams.cmd_params, _baseGuid.num_of_guids_pp, _baseGuid.step_size_pp)) {
        return false;
    }

    if (_flintParams.uid_specified) {
        _baseGuid.set_mac_from_guid = true;
    }

    _baseGuid.base_guid_specified = _flintParams.uid_specified || _flintParams.guid_specified;
    if (_baseGuid.base_guid_specified) {
        _baseGuid.base_guid = _flintParams.uid_specified ? _flintParams.baseUid : _flintParams.user_guids[0];
    }

    _baseGuid.base_mac_specified = _flintParams.mac_specified;
    if (_baseGuid.base_mac_specified) {
        _baseGuid.base_mac = _flintParams.user_macs[0];
    }
    //printf("-D-"GUID_FORMAT"\n", _baseGuid.h, _baseGuid.l);
    return true;
}

FlintStatus SmgSubCommand::executeCommand()
{
    if (preFwOps()) {
        return FLINT_FAILED;
    }
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    //TODO: dispaly MFG guid changes
    bool stripedImage = _flintParams.striped_image && _flintParams.image_specified;
    if (!_ops->FwQuery(&_info, true, stripedImage)) {
        reportErr(true, FLINT_MFG_ERROR, _ops->err());
        return FLINT_FAILED;
    }

    if (_info.fw_info.chip_type == CT_CONNECT_IB || _info.fw_info.chip_type == CT_SWITCH_IB) {
        if (!_flintParams.uid_specified) {
            reportErr(true, "Can not set GUIDs/MACs: uid is not specified, please run with -uid flag.\n");
            return FLINT_FAILED;
        }
    } else {
        if (!_flintParams.uid_specified && !_flintParams.guid_specified && !_flintParams.mac_specified) {
            reportErr(true, "Can not set GUIDs/MACs: GUIDs/MACs are not specified, please run with -uid/-guid/-mac flags.\n");
            return FLINT_FAILED;
        }
    }

    bool ret;
    ret = _ops->FwSetMFG(_baseGuid, &verifyCbFunc);
    if (!ret) {
        reportErr(true, FLINT_MFG_ERROR, _ops->err());
        return FLINT_FAILED;
    }
    if (_flintParams.device_specified && _info.fw_type != FIT_FS2) {
        printf("-I- %s\n", FW_RESET_MSG);
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: Set Vpd Subcommand
 **********************/
SetVpdSubCommand:: SetVpdSubCommand()
{
    _name = "set vpd";
    _desc = "Set read-only VPD (For FS3/FS4 image only).";
    _extendedDesc = "Set Read-only VPD, Set VPD in the given FS3/FS4 image, intended for production use only.";
    _flagLong = "set_vpd";
    _flagShort = "";
    _param = "[vpd file]";
    _paramExp = "vpd file: bin file containing the vpd data";
    _example = FLINT_NAME " -i fw_image.bin set_vpd vpd.bin"
#ifndef __WIN__
               "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3 " -override_cache_replacement set_vpd vpd.bin (should be used when device is idle)"
#endif
    ;
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Vpd;
}

SetVpdSubCommand:: ~SetVpdSubCommand()
{

}

FlintStatus SetVpdSubCommand:: executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetVPD((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc)) {
        reportErr(true, FLINT_VPD_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: SetPublicKeysSubcommand
 **********************/
SetPublicKeysSubCommand:: SetPublicKeysSubCommand()
{
    _name = "set public keys";
    _desc = "Set Public Keys (For FS3/FS4 image only).";
    _extendedDesc = "Set Public Keys in the given FS3/FS4 image.";
    _flagLong = "set_public_keys";
    _flagShort = "";
    _param = "[public keys binary file]";
    _paramExp = "public keys file: bin file containing the public keys data";
    _example = FLINT_NAME " -i fw_image.bin set_public_keys publickeys.bin";
    _v = Wtv_Img;
    _maxCmdParamNum = 1;
    _minCmdParamNum = 1;
    _cmdType = SC_Set_Public_Keys;
}

SetPublicKeysSubCommand:: ~SetPublicKeysSubCommand()
{
}

FlintStatus SetPublicKeysSubCommand:: executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _imgOps;
    if (!ops->FwSetPublicKeys((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc)) {
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

SetForbiddenVersionsSubCommand:: ~SetForbiddenVersionsSubCommand()
{
}

FlintStatus SetForbiddenVersionsSubCommand:: executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _imgOps;
    if (!ops->FwSetForbiddenVersions((char*)_flintParams.cmd_params[0].c_str(), &verifyCbFunc)) {
        reportErr(true, FLINT_SET_FORBIDDEN_VERSIONS_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: Set VSD
 **********************/
SvSubCommand:: SvSubCommand()
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
               "\n" FLINT_NAME " -d " MST_DEV_EXAMPLE3 " -vsd VSD_STRING -override_cache_replacement sv (should be used when device is idle)\n"
#endif
    ;
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 0;
    _cmdType = SC_Sv;
}

SvSubCommand:: ~SvSubCommand()
{

}

bool SvSubCommand::verifyParams()
{
    if (!_flintParams.vsd_specified) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"-vsd\"");
        return false;
    }
    // we verify that -vsd has a parameter in the cmd parser

    return true;
}

FlintStatus SvSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetVSD((char*)_flintParams.vsd.c_str(), &vsdCbFunc, &verifyCbFunc)) {
        reportErr(true, FLINT_VSD_ERROR, ops->err());
        return FLINT_FAILED;
    }

    if (ops->FwType() == FIT_FS2) {
        // print "restoring signature" on FS2 to be consistent with FS3 output
        vsdCbFunc(101);
    }
    return FLINT_SUCCESS;
}



/*******************************
 * Class: Read Image SubCommand
 ******************************/
RiSubCommand:: RiSubCommand()
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
}

RiSubCommand:: ~RiSubCommand()
{

}

FlintStatus RiSubCommand::executeCommand()
{
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    // Check if we have permission to write to file
    FILE *fh;
    if ((fh = fopen(_flintParams.cmd_params[0].c_str(), "wb")) == NULL) {
        reportErr(true, "Can not open %s: %s\n", _flintParams.cmd_params[0].c_str(), strerror(errno));
        return FLINT_FAILED;
    } else {
        fclose(fh);
    }
    u_int32_t imgSize;
    //on first call we get the image size
    if (!_fwOps->FwReadData(NULL, &imgSize)) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    std::vector<u_int8_t> imgBuff(imgSize);
    //on second call we fill it
    if (!_fwOps->FwReadData((void*)(&imgBuff[0]), &imgSize)) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    return writeImageToFile(_flintParams.cmd_params[0].c_str(), &(imgBuff[0]), imgSize);
}

/***********************
 * Class: Dump Conf SubCommand
 **********************/
DcSubCommand:: DcSubCommand()
{
    _name = "dc";
    _desc = "Dump Configuration: print fw configuration file for the given image.";
    _extendedDesc = "Print (to screen or to a file) the FW configuration text file used by the image generation process.\n"
                    "This command would fail if the image does not contain a FW configuration section."
                    " Existence of this section depends on the version of the image generation tool.";
    _flagLong = "dc";
    _flagShort = "";
    _param = "[out-file]";
    _paramExp = "file: (optional) filename to write the dumped configuration to. If not given,"
                " the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " dc";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Dc;
}

DcSubCommand:: ~DcSubCommand()
{

}

bool DcSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DcSubCommand::executeCommand()
{
    FwOperations *ops;
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char *file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*) NULL;
    if (!ops->FwGetSection((ops->FwType() == FIT_FS2) ? (int)H_FW_CONF : (int)FS3_DBG_FW_INI, _sect, _flintParams.striped_image)) {
        reportErr(true, FLINT_DUMP_ERROR, "Fw Configuration", ops->err());
        return FLINT_FAILED;
    }
    if (!dumpFile(file, _sect, "Fw Configuration")) {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class:Dump Hash SubCommand
 **********************/
DhSubCommand:: DhSubCommand()
{
    _name = "dh";
    _desc = "Dump Hash: dump the hash if it is integrated in the FW image";
    _extendedDesc = "Print (to screen or to a file) the HASH text file used by the FW.\n"
                    "This command would fail if the image does not contain a Hash file.";
    _flagLong = "dh";
    _flagShort = "";
    _param = "[out-file]";
    _paramExp = "file - (optional) filename to write the dumped tracer hash file to. If not given,"
                " the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " dh hash.csv";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 1;
    _cmdType = SC_Dh;
}

DhSubCommand:: ~DhSubCommand()
{

}

bool DhSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DhSubCommand::executeCommand()
{
    FwOperations *ops;
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char *file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*) NULL;
    if (!ops->FwGetSection(H_HASH_FILE, _sect,  _flintParams.striped_image)) {
        reportErr(true, FLINT_DUMP_ERROR, "Hash file", ops->err());
        return FLINT_FAILED;
    }
    if (!dumpFile(file, _sect, "Fw Configuration")) {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class:Set Key SubCommand
 **********************/
SetKeySubCommand:: SetKeySubCommand()
{
    _name = "set_key";
    _desc = "Set/Update the HW access key which is used to enable/disable access to HW.\n"
            "The key can be provided in the command line or interactively typed after the command is given\n"
            "NOTE: The new key is activated only after the device is reset.";
    _extendedDesc = "Set/Update the HW access key which is used to enable/disable access to HW.";
    _flagLong = "set_key";
    _flagShort = "";
    _param = "[key]";
    _paramExp = "key: (optional) The new key you intend to set (in hex).";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " set_key 1234deaf5678";
    _v = Wtv_Dev;
    _maxCmdParamNum = 1;
    _cmdType = SC_Set_Key;
    _getKeyInter = false;
    memset(&_userKey, 0, sizeof(_userKey));
}

SetKeySubCommand:: ~SetKeySubCommand()
{

}

bool SetKeySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1) {
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
    if (strlen(keyArr) == 0) {
        reportErr(true, FLINT_INVALID_PASSWORD);
        return false;
    }

    if (!getGUIDFromStr(keyArr, _userKey, \
                        "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
        return false;
    }
    // verify key
    hw_key_t verKey;
    getPasswordFromUser("Verify Key ", keyArr);
    if (!getGUIDFromStr(keyArr, verKey, \
                        "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
        return false;
    }
    if (_userKey.h != verKey.h || _userKey.l != verKey.l) {
        reportErr(true, FLINT_SET_KEY_ERROR, "The keys you entered did not match.");
        return false;
    }
    return true;
}

FlintStatus SetKeySubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    if (_getKeyInter) {
        if (!getKeyInteractively()) {
            return FLINT_FAILED;
        }
    } else {
        if (!getGUIDFromStr(_flintParams.cmd_params[0], _userKey, \
                            "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
            return FLINT_FAILED;
        }
    }
    if (((Flash*)_io)->is_fifth_gen()) {
        if (((Flash*)_io)->get_cr_space_locked()) {
            printf("-I- HW access already disabled\n");
            return FLINT_SUCCESS;
        }
        // In 5th gen treat set as disable hw access
        u_int64_t key = ((u_int64_t)_userKey.h << 32) | _userKey.l;
        if (!((Flash*)_io)->disable_hw_access(key)) {
            reportErr(true, FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
        }
        printf("-I- Secure Host was enabled successfully on the device.\n");
    } else {
        _io->close();
        delete _io;
        _io = NULL;
        if (preFwOps() == FLINT_FAILED) {
            return FLINT_FAILED;
        }
        if (!_fwOps->FwSetAccessKey(_userKey, &setKeyCbFunc)) {
            reportErr(true, FLINT_SET_KEY_ERROR, _fwOps->err());
            return FLINT_FAILED;
        }
        setKeyCbFunc(101);
        printf("\n-I- New key was updated successfully in the flash. " \
               "In order to activate the new key you should reboot or restart the driver.\n");
    }

    return FLINT_SUCCESS;
}

/***********************
 * Class:HwAccess SubCommand
 **********************/
HwAccessSubCommand:: HwAccessSubCommand()
{
    _name = "hw_access";
    _desc = "Enable/disable the access to the HW.\n"
            "The key can be provided in the command line or interactively typed after the command is given";
    _extendedDesc = "Enable/disable the access to the HW.";
    _flagLong = "hw_access";
    _flagShort = "";
    _param = "<enable|disable> [key]";
    _paramExp = "<enable/disable>: Specify if you intend to disable or enable the HW access.\n"
                "You will be asked to type a key when you try to enable HW access.\n"
                "key: The key you intend to use for enabling the HW access, or disabling it in 5th Gen devices.\n"
                "Key format consists of at most 16 Hexadecimal digits.";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw_access enable";
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _cmdType = SC_Hw_Access;
}

HwAccessSubCommand:: ~HwAccessSubCommand()
{

}

bool HwAccessSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() == 0) {
        reportErr(true, FLINT_MISSED_ARG_ERROR, "<disable/enable>", _name.c_str());
        return false;
    }
    if (_flintParams.cmd_params.size() > 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (_flintParams.cmd_params[0] != "enable" && _flintParams.cmd_params[0] != "disable") {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "enable or disable");
        return false;
    }
    return true;
}

FlintStatus HwAccessSubCommand:: disableHwAccess()
{
    if (((Flash*)_io)->get_cr_space_locked()) {
        printf("-I- HW access already disabled\n");
    } else {
        if (((Flash*)_io)->is_fifth_gen()) {
            SubCommand *setKey = new SetKeySubCommand();
            _flintParams.cmd_params.erase(_flintParams.cmd_params.begin());
            setKey->setParams(_flintParams);
            FlintStatus rc = setKey->executeCommand();
            delete setKey;
            return rc;
        } else {

            if (!((Flash*)_io)->disable_hw_access()) {
                printf(FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
                return FLINT_FAILED;
            }
        }

    }
    return FLINT_SUCCESS;
}
FlintStatus HwAccessSubCommand:: enableHwAccess()
{
    u_int64_t key;
    if (((Flash*)_io)->get_cr_space_locked() == 0) {
        printf("-I- HW access already enabled\n");
    } else {
        hw_key_t keyStruct;
        //now we need to get the key from the user (either given in the parameters or we get it during runtime)
        if (_flintParams.cmd_params.size() == 2) {
            if (!getGUIDFromStr(_flintParams.cmd_params[1], keyStruct, \
                                "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
                return FLINT_FAILED;
            }
        } else {//we need to get the key from user during runtime
            char keyArr[MAX_PASSWORD_LEN + 1] = {0};
            getPasswordFromUser("Enter Key ", keyArr);
            if (strlen(keyArr) == 0) {
                reportErr(true, FLINT_INVALID_PASSWORD);
                return FLINT_FAILED;
            }
            if (!getGUIDFromStr(keyArr, keyStruct, \
                                "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
                return FLINT_FAILED;
            }
        }
        key = ((u_int64_t)keyStruct.h << 32) | keyStruct.l;
        if (!((Flash*)_io)->enable_hw_access(key)) {
            reportErr(true, FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
        }
        printf("-I- The Secure Host was disabled successfully on the device.\n");
    }
    return FLINT_SUCCESS;
}

FlintStatus HwAccessSubCommand:: executeCommand()
{
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    if (_flintParams.cmd_params[0] == "disable") {
        return disableHwAccess();
    }
    //else its enable hw access
    return enableHwAccess();
}

/***********************
 * Class: Hw SubCommand
 **********************/
HwSubCommand:: HwSubCommand()
{
#ifndef EXTERNAL
    _name = "hw";
    _desc = "Set/query HW info and flash attributes.";
    _extendedDesc = "Access HW info and flash attributes.";
    _flagLong = "hw";
    _flagShort = "";
    _param = "<query|set> [ATTR=VAL]";
    _paramExp = "query: query HW info\n"
                "set [ATTR=VAL]: set flash attribure\n"
                "Supported attributes:\n"
                "    QuadEn: can be 0 or 1\n"
                "    DummyCycles: can be [1..15]\n"
                "    Flash[0|1|2|3].WriteProtected can be:\n"
                "        <Top|Bottom>,<1|2|4|8|16|32|64>-<Sectors|SubSectors>";
    _example = "flint -d " MST_DEV_EXAMPLE1 " hw query\n"
               FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw set QuadEn=1\n"
               FLINT_NAME " -d " MST_DEV_EXAMPLE1 " hw set Flash1.WriteProtected=Top,1-SubSectors";
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

HwSubCommand:: ~HwSubCommand()
{

}

bool HwSubCommand::verifyParams()
{
#ifdef EXTERNAL
    if (_flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }

    if (_flintParams.cmd_params[0] != "query") {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "query");
        return false;
    }
#else
    if (_flintParams.cmd_params.size() > 2 || _flintParams.cmd_params.size() == 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params[0] != "query") && (_flintParams.cmd_params[0] != "set")) {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "query or set");
        return false;
    }
    if ((_flintParams.cmd_params[0] == "set") && (_flintParams.cmd_params.size() != 2)) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
#endif

    return true;
}

FlintStatus HwSubCommand::printAttr(const ext_flash_attr_t& attr)
{
    printf("HW Info:\n");
    printf("  HwDevId               %d\n",     attr.hw_dev_id);
    printf("  HwRevId               0x%x\n",   attr.rev_id);

    printf("Flash Info:\n");
    if (attr.type_str != NULL) {
        // we don't print the flash type in old devices
        printf("  Type                  %s\n",     attr.type_str);
    }
    printf("  TotalSize             0x%x\n",   attr.size);
    printf("  Banks                 0x%x\n",   attr.banks_num);
    printf("  SectorSize            0x%x\n",   attr.sector_size);
    printf("  WriteBlockSize        0x%x\n",   attr.block_write);
    printf("  CmdSet                0x%x\n",   attr.command_set);

    // Quad EN query
    if (attr.quad_en_support) {
        switch (attr.mf_get_quad_en_rc) {
        case MFE_OK:
            printf("  " QUAD_EN_PARAM "                %d\n", attr.quad_en);
            break;

        case MFE_MISMATCH_PARAM:
            printf("-E- There is a mismatch in the " QUAD_EN_PARAM " attribute between the flashes attached to the device\n");
            break;

        case MFE_NOT_SUPPORTED_OPERATION:
            break;

        default:
            printf("Failed to get " QUAD_EN_PARAM " attribute: %s (%s)", \
                   errno == 0 ? "" : strerror(errno), mf_err2str(attr.mf_get_quad_en_rc));
            return FLINT_FAILED;
        }
    }
    // Dummy Cycles query
    if (attr.dummy_cycles_support) {
        switch (attr.mf_get_dummy_cycles_rc) {
        case MFE_OK:
            printf("  " DUMMY_CYCLES_PARAM "           %d\n", attr.dummy_cycles);
            break;

        case MFE_MISMATCH_PARAM:
            printf("-E- There is a mismatch in the " DUMMY_CYCLES_PARAM " attribute between the flashes attached to the device\n");
            break;

        case MFE_NOT_SUPPORTED_OPERATION:
            break;

        default:
            printf("Failed to get " DUMMY_CYCLES_PARAM " attribute: %s (%s)", \
                   errno == 0 ? "" : strerror(errno), mf_err2str(attr.mf_get_dummy_cycles_rc));
            return FLINT_FAILED;
        }
    }
    // Flash write protected info query
    if (attr.write_protect_support) {
        int bank;
        int rc;
        for (bank = 0; bank < attr.banks_num; bank++) {
            write_protect_info_t protect_info = attr.protect_info_array[bank];
            rc = attr.mf_get_write_protect_rc_array[bank];
            if (rc == MFE_OK) {
                printf("  " FLASH_NAME "%d." WRITE_PROTECT "   ", bank);
                if (protect_info.sectors_num != 0) {
                    printf("%s,", (protect_info.is_bottom ? WP_BOTTOM_STR : WP_TOP_STR));
                    printf("%d-", protect_info.sectors_num);
                    printf("%s\n", (protect_info.is_subsector ? WP_SUBSEC_STR : WP_SEC_STR));
                } else {
                    printf(WP_DISABLED_STR "\n");
                }
            } else {
                if (rc != MFE_NOT_SUPPORTED_OPERATION) {
                    // We ignore the read when operation is not supported!
                    printf("Failed to get write_protected info: %s (%s)", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
                    return FLINT_FAILED;
                }
            }
        }
    }
    return FLINT_SUCCESS;
}

FlintStatus HwSubCommand::executeCommand()
{
    //init fw operation object
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    if (_flintParams.cmd_params[0] == "set") {
        char *cmdParam = strcpy(new char[_flintParams.cmd_params[1].size() + 1],
                                _flintParams.cmd_params[1].c_str());
        char *paramName, *paramValStr;
        paramName = strtok(cmdParam, "=");
        paramValStr = strtok(NULL, "=");
        //printf("-D- param_name = %s, param_val_str=%s, cmdParam=%s\n", paramName, paramValStr, cmdParam);
        if (paramName == NULL || paramValStr == NULL) {
            delete[] cmdParam;
            reportErr(true, FLINT_HW_SET_ARGS_ERROR, _flintParams.cmd_params[1].c_str());
            return FLINT_FAILED;
        }
        if (!((Flash*) _io)->set_attr(paramName, paramValStr)) {
            delete[] cmdParam;
            reportErr(true, FLINT_HW_COMMAND_ERROR, "set", _io->err());
            return FLINT_FAILED;
        }
        printf("-I- %s parameter was set successfully\n", paramName);
        delete[] cmdParam;
    } else {
        ext_flash_attr_t attr;
        attr.type_str = (char*)NULL;
        if (!((Flash*) _io)->get_attr(attr)) {
            reportErr(true, FLINT_HW_COMMAND_ERROR, "query", _io->err());
            if (attr.type_str) {
                delete[] attr.type_str;
            }
            return FLINT_FAILED;
        }
        FlintStatus rc = printAttr(attr);
        //str is allocated in get_attr
        if (attr.type_str) {
            delete[] attr.type_str;
        }
        if (rc == FLINT_FAILED) {
            return FLINT_FAILED;
        }

    }
    return FLINT_SUCCESS;
}

/**************************
 * Class: Erase SubCommand
 *************************/
EraseSubCommand:: EraseSubCommand()
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

EraseSubCommand:: ~EraseSubCommand()
{

}

FlintStatus EraseSubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    char *addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char    *endp;
    // Address of sector to erase
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    // Erase
    if (!((Flash*)_io)->erase_sector(addr)) {
        reportErr(true, FLINT_ERASE_SEC_ERROR, _io->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/*****************************
* Class: Read Dword SubCommand
*****************************/
RwSubCommand:: RwSubCommand()
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

RwSubCommand:: ~RwSubCommand()
{

}

FlintStatus RwSubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char *addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char *endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    if (_flintParams.device_specified ? !((Flash*)_io)->read(addr, &data) \
        : !((FImage*)_io)->read(addr, &data)) {
        reportErr(true, FLINT_FLASH_READ_ERROR, _io->err());
        return FLINT_FAILED;
    }
    printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));
    return FLINT_SUCCESS;
}

/******************************
* Class: Write Dword Subcommand
******************************/
WwSubCommand:: WwSubCommand()
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
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 2;
    _cmdType = SC_Ww;
}

WwSubCommand:: ~WwSubCommand()
{

}

FlintStatus WwSubCommand::executeCommand()
{
    //init fw operation object
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char *addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char *dataStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    char *endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    data = strtoul(dataStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_DATA_ERROR, _flintParams.cmd_params[1].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    delete[] dataStr;
    data = __cpu_to_be32(data);
    if (!((Flash*)_io)->write(addr, data)) {
        reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}
/***************************************
* Class: Write Dword No Erase SubCommand
***************************************/
WwneSubCommand:: WwneSubCommand()
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

WwneSubCommand:: ~WwneSubCommand()
{

}

FlintStatus WwneSubCommand::executeCommand()
{
    //init fw operation object
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    u_int32_t data;
    char *addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    char *dataStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    char *endp;
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    data = strtoul(dataStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_DATA_ERROR, _flintParams.cmd_params[1].c_str());
        delete[] addrStr;
        delete[] dataStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    delete[] dataStr;
    data = __cpu_to_be32(data);
    if (!((Flash*)_io)->write(addr, &data, 4, true)) {
        reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/**************************************
* Class:Write Block  SubCommand
**************************************/
WbSubCommand:: WbSubCommand()
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
    _v = Wtv_Dev;
    _maxCmdParamNum = 2;
    _minCmdParamNum = 2;
    _cmdType = SC_Wb;
}

WbSubCommand:: ~WbSubCommand()
{

}

bool WbSubCommand::extractData(const std::vector<string>& cmdParams, u_int32_t *addr, std::vector<u_int8_t>& data)
{
    // get address
    char *endp;
    char *addrStr = strcpy(new char[cmdParams[1].size() + 1], cmdParams[1].c_str());
    *addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, cmdParams[1].c_str());
        delete[] addrStr;
        return false;
    }
    delete[] addrStr;
    // get data
    FImage img;
    if (!img.open(cmdParams[0].c_str())) {
        reportErr(true, FLINT_WB_FILE_ERROR, cmdParams[0].c_str(), img.err());
        return false;
    }
    //copy data to vector
    data.resize(img.getBufLength());
    if (!img.getBuf()) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, img.err());
        return false;
    }
    memcpy(&data[0], img.getBuf(), img.getBufLength());

    return true;
}

FlintStatus WbSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    std::vector<u_int8_t> data;
    if (!extractData(_flintParams.cmd_params, &addr, data)) {
        return FLINT_FAILED;
    }
    //printf("-D- writing to addr:0x%08x %lu bytes\n",addr , data.size());
    if (!_fwOps->FwWriteBlock(addr, data, wbCbFunc)) {
        reportErr(true, FLINT_WB_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    wbCbFunc(101);
    return FLINT_SUCCESS;
}

/**************************************
* Class:Write Block No Erase SubCommand
**************************************/
WbneSubCommand:: WbneSubCommand()
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

WbneSubCommand:: ~WbneSubCommand()
{

}

bool WbneSubCommand::writeBlock(u_int32_t addr, std::vector<u_int32_t> dataVec)
{
    //we should work only on flash.
    //check if flash is big enough
    if (addr + (dataVec.size() * 4) > ((Flash*)_io)->get_size()) {
        reportErr(true, "Writing %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                  (unsigned int)(dataVec.size() * 4), (unsigned int)addr, (unsigned int)_io->get_size());
        return false;
    }
    if (!((Flash*)_io)->write(addr, &dataVec[0], (dataVec.size() * 4), true)) {
        reportErr(true, FLINT_FLASH_WRITE_ERROR, _io->err());
        return false;
    }
    return true;
}

bool WbneSubCommand::extractData(const std::vector<string>& cmdParams, u_int32_t *addr, std::vector<u_int32_t>& data)
{
    char *endp;
    char *addrStr = strcpy(new char[cmdParams[0].size() + 1], cmdParams[0].c_str());
    *addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, cmdParams[0].c_str());
        delete[] addrStr;
        return false;
    }
    delete[] addrStr;
    char *sizeStr = strcpy(new char[cmdParams[1].size() + 1], cmdParams[1].c_str());
    u_int32_t size = strtoul(sizeStr, &endp, 0);
    if (*endp || size % 4 || size / 4 != (cmdParams.size() - 2)) {
        reportErr(true, FLINT_INVALID_SIZE_ERROR, sizeStr);
        delete[] sizeStr;
        return false;
    }
    delete[] sizeStr;
    for (u_int32_t i = 2; i < cmdParams.size(); i++) {
        char *dataStr = strcpy(new char[cmdParams[i].size() + 1], cmdParams[i].c_str());
        data.push_back(__cpu_to_be32(strtoul(dataStr, &endp, 0)));
        if (*endp) {
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
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t addr;
    std::vector<u_int32_t> data;
    if (!extractData(_flintParams.cmd_params, &addr, data)) {
        return FLINT_FAILED;
    }
    //printf("-D- writing to addr:0x%08x %lu bytes\n",addr , data.size()*4);
    if (!writeBlock(addr, data)) {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 * Class: ReadBlock
 **********************/
RbSubCommand:: RbSubCommand()
{
    _name = "rb";
    _desc = "Read  a data block from flash";
    _extendedDesc = "Read a data block from the flash and write it to a file or to screen.";
    _flagLong = "rb";
    _flagShort = "";
    _param = "<addr> <size> [out-file]";
    _paramExp = "addr - address of block\n"
                "size - size of data to read in bytes\n"
                "file - filename to write the block (raw binary). If not given, the data is printed to screen";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE1 " rb 0x10000 100 file.bin";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 3;
    _minCmdParamNum = 2;
    _cmdType = SC_Rb;
}

RbSubCommand:: ~RbSubCommand()
{

}

bool RbSubCommand::readBlock(u_int32_t addr, std::vector<u_int8_t>& buff, bool isFlash)
{
    FwOperations *ops = isFlash ? _fwOps : _imgOps;
    if (!ops->FwReadBlock(addr, buff.size(), buff)) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, ops->err());
        return false;
    }
    return true;
}

bool RbSubCommand::printToScreen(const std::vector<u_int8_t>& buff)
{
    for (u_int32_t i = 0; i < buff.size(); i += 4) {
        u_int32_t word = *((u_int32_t*)(&buff[0] + i));
        word  = __be32_to_cpu(word);
        printf("0x%08x ", word);
    }
    printf("\n");
    return true;
}

FlintStatus RbSubCommand::executeCommand()
{
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    bool wTF = _flintParams.cmd_params.size() == 3 ? true : false;
    //extract address and size to read from cmdline
    u_int32_t addr;
    u_int32_t size;
    char *endp;
    char *addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1], _flintParams.cmd_params[0].c_str());
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    char *sizeStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1], _flintParams.cmd_params[1].c_str());
    size = strtoul(sizeStr, &endp, 0);
    if (*endp || size % 4) {
        reportErr(true, FLINT_INVALID_SIZE_ERROR, sizeStr);
        delete[] sizeStr;
        return FLINT_FAILED;
    }
    delete[] sizeStr;
    //init byte vector and fill it with data
    std::vector<u_int8_t> data(size);
    if (!readBlock(addr, data, _flintParams.device_specified)) {
        return FLINT_FAILED;
    }
    //print either to file or to screen
    FlintStatus rc;
    if (wTF) {
        rc = writeToFile(_flintParams.cmd_params[2], data) == true ? FLINT_SUCCESS : FLINT_FAILED;
    } else {
        rc = printToScreen(data) == true ? FLINT_SUCCESS : FLINT_FAILED;
    }
    return rc;
}

/***********************
 * Class: ClearSemaphore
 **********************/
ClearSemSubCommand:: ClearSemSubCommand()
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

ClearSemSubCommand:: ~ClearSemSubCommand()
{

}

FlintStatus ClearSemSubCommand::executeCommand()
{
    _flintParams.clear_semaphore = true;
    return preFwAccess();
}


/***********************
 * Class: RomQuery
 **********************/
RomQuerySubCommand:: RomQuerySubCommand()
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

RomQuerySubCommand:: ~RomQuerySubCommand()
{

}


FlintStatus RomQuerySubCommand::executeCommand()
{
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    getRomsInfo(_io, _romsInfo);
    if (_romsInfo.exp_rom_err_msg_valid != 0) {
        reportErr(true, FLINT_ROM_QUERY_ERROR, _flintParams.image.c_str(), _romsInfo.exp_rom_err_msg);
        return FLINT_FAILED;
    }
    displayExpRomInfo(_romsInfo, "Rom Info: ");
    return FLINT_SUCCESS;

}

/***********************
 * Class: ResetCfg
 **********************/
ResetCfgSubCommand:: ResetCfgSubCommand()
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

ResetCfgSubCommand:: ~ResetCfgSubCommand()
{

}


FlintStatus ResetCfgSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    printf("-W- Resetting device configuration using Flint should be done as a last resort.\n");
    printf("-W- Please attempt to reset configuration via mlxconfig tool if possible.\n");
    printf("-W- Only proceed if you know what you are doing.\n");
    if (!askUser("reset non-volatile configuration")) {
        return FLINT_FAILED;
    }

    printf("Resetting...");
    if (!_fwOps->FwResetNvData()) {
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
FiSubCommand:: FiSubCommand()
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

FiSubCommand:: ~FiSubCommand()
{

}


FlintStatus FiSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

    if (!askUser("Fix device fw?")) {
        return FLINT_FAILED;
    }

    if (!_fwOps->FwShiftDevData(&verifyCbFunc)) {
        reportErr(true, FLINT_FIX_IMG_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf("\n-I- Fw was successfully fixed. reboot or restart the driver is required.\n");
    return FLINT_SUCCESS;

}

/***********************
 * Class: CheckSum
 **********************/
CheckSumSubCommand:: CheckSumSubCommand()
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

CheckSumSubCommand:: ~CheckSumSubCommand()
{

}

bool CheckSumSubCommand::extractChecksumFromStr(string str, u_int8_t checkSum[16])
{
    char ptr[2];
    int i = 15;
    if (str.size() < 2) {
        reportErr(true, FLINT_CHECKSUM_LEN_ERROR);
        return false;
    }
    if (!strncasecmp(str.c_str(), "0x", 2)) {
        // str starts with 0x or 0X, remove prefix
        str = &(str.c_str()[2]);
    }

    if (str.size() != 32) {
        reportErr(true, FLINT_CHECKSUM_LEN_ERROR);
        return false;
    }
    stringstream ss(str);
    while (i >= 0) {
        ss.read(ptr, 2);
        if (!isxdigit(ptr[0]) || !isxdigit(ptr[1])) {
            reportErr(true, FLINT_CHECKSUM_HEX_ERROR);
            return false;
        }
        checkSum[i] = (u_int8_t)strtoul(ptr, NULL, 16);
        if (!checkSum[i] && strncmp(ptr, "00", 2)) {
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
    for (int i = 15; i >= 0; i--) {
        char chunk[3];
        snprintf(chunk, 3, "%02x", chksm[i]);
        ss << chunk;
    }
    string s = ss.str();
    return s;
}

FlintStatus CheckSumSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _fwOps ? _fwOps : _imgOps;
    printf("-I- Calculating Checksum ...\n");
    if (!ops->FwCalcMD5(_checkSum)) {
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
TimeStampSubCommand:: TimeStampSubCommand()
{
    _name = "time stamp";
    _desc = "FW time stamping.";
    _extendedDesc = "set/query/reset time stamp on device/image.";
    _flagLong = "timestamp";
    _flagShort = "ts";
    _param = "<set|query|reset> [timestamp] [FW version]";
    _paramExp = "set <timestamp> [FW version] : set the specified timestamp. if set on device FW version must be specified\n"
                "timestamp should comply with ISO 8601 format and provided with UTC timezone: YYYY-MM-DDThh:mm:ssZ\n"
                "query : query device/image to view the timestamp\n"
                "reset : reset the timestamp, remove the timestamp from device/image.\n";
    _example = FLINT_NAME " -d " MST_DEV_EXAMPLE4 " ts set 2015-12-24T14:52:33Z 14.12.1100\n"
               FLINT_NAME " -d " MST_DEV_EXAMPLE4 " ts reset\n"
               FLINT_NAME " -i ./fw4115.bin ts set\n"
               FLINT_NAME " -i ./fw4115.bin ts query";
    _v = Wtv_Dev_Or_Img;
    _maxCmdParamNum = 3;
    _minCmdParamNum = 1;
    _cmdType = SC_Time_Stamp;
    memset(&_userFwVer, 0, sizeof(_userFwVer));
    memset(&_userTsEntry, 0, sizeof(_userTsEntry));
    _operation = TS_No_Command;
    _ops = (FwOperations*)NULL;
}

TimeStampSubCommand:: ~TimeStampSubCommand()
{

}
bool TimeStampSubCommand::parseFwVersion(string verStr)
{
    unsigned int major = 0;
    unsigned int minor = 0;
    unsigned int subminor = 0;
    int count = sscanf(verStr.c_str(), "%02d.%02d.%04d", &major, &minor, &subminor);
    if (count != 3) {
        count = sscanf(verStr.c_str(), "%02d.%04d.%04d", &major, &minor, &subminor);
        if (count != 3) {
            reportErr(true, "Failed to parse FW version. expected format: MM.mm.ssss\n");
            return false;
        }
    }
    _userFwVer.fw_ver_major = major;
    _userFwVer.fw_ver_minor = minor;
    _userFwVer.fw_ver_subminor = subminor;
    //printf("-D- Fw version: %d.%d.%d\n", _userFwVer.fw_ver_major, _userFwVer.fw_ver_minor, _userFwVer.fw_ver_subminor);
    return true;
}

#define BCD2_TO_NUM(bcd) \
    ((((bcd) >> 4 & 0xf) * 10) + ((bcd) & 0xf))

#define BCD4_TO_NUM(bcd) \
    ((BCD2_TO_NUM((bcd) >> 8 & 0xff) * 100) + (BCD2_TO_NUM((bcd) & 0xff)))

#define NUM2_TO_BCD(num) \
    ((((num) / 10) * 16) + ((num) % 10))

#define NUM4_TO_BCD(num) \
    ((NUM2_TO_BCD((num) / 100) * 256) + NUM2_TO_BCD((num) % 100))

u_int8_t TimeStampSubCommand::getDaysInMonth(u_int16_t year, u_int8_t month)
{
    u_int8_t days = 0;
    bool isLeapYear = year % 4 == 0; // evenly divisible by 4
    isLeapYear &= (year % 100 != 0) || (year % 400 == 0); // not evenly divided by 100 or  evenly divisible by 400
    switch (month) {
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
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = gmtime(&rawTime);
    if (!timeInfo) {
        reportErr(true, "gmtime returned NULL. Can't get machine's UTC time.");
        return;
    }

    _userTsEntry.ts_year = NUM4_TO_BCD(timeInfo->tm_year + 1900);
    _userTsEntry.ts_month = NUM2_TO_BCD(timeInfo->tm_mon + 1);
    _userTsEntry.ts_day = NUM2_TO_BCD(timeInfo->tm_mday);
    _userTsEntry.ts_hour = NUM2_TO_BCD(timeInfo->tm_hour);
    _userTsEntry.ts_minutes = NUM2_TO_BCD(timeInfo->tm_min);
    _userTsEntry.ts_seconds =  NUM2_TO_BCD(timeInfo->tm_sec);

    //printf("-D- timestamp: %04x-%02x-%02xT%02x:%02x:%02x\n", _userTsEntry.ts_year, _userTsEntry.ts_month,
    //                                                        _userTsEntry.ts_day, _userTsEntry.ts_hour, _userTsEntry.ts_minutes, _userTsEntry.ts_seconds);
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
    if (*tsStr.rbegin() != 'Z') {
        reportErr(true, "Failed to parse timestamp: Timestamp timezone must be UTC. format should be: YYYY-MM-DDThh:mm:ssZ\n");
        return false;
    }
    // scan and store
    int count = sscanf(tsStr.c_str(), "%04d-%02d-%02dT%02d:%02d:%02dZ", &year, &month, &day, &hour, &minutes, &seconds);
    if (count != 6) {
        reportErr(true, "Failed to parse timestamp: input should be compliant to the following ISO 8601 format: YYYY-MM-DDThh:mm:ssZ\n");
        return false;
    }
    // check time args
    if (month == 0 || month > 12) {
        reportErr(true, "Failed to parse timestamp: illegal month value (%d)\n", month);
        return false;
    }
    if (day > getDaysInMonth(year, month)) {
        reportErr(true, "Failed to parse timestamp: illegal day value (%d)\n", day);
        return false;
    }
    if (hour  > 23 || minutes  > 59 || seconds  > 59) {
        reportErr(true, "Failed to parse timestamp: illegal time value (%02d:%02d:%02d)\n", hour, minutes, seconds);
        return false;
    }
    // store as BCD
    _userTsEntry.ts_year = NUM4_TO_BCD(year);
    _userTsEntry.ts_month = NUM2_TO_BCD(month);
    _userTsEntry.ts_day = NUM2_TO_BCD(day);
    _userTsEntry.ts_hour = NUM2_TO_BCD(hour);
    _userTsEntry.ts_minutes = NUM2_TO_BCD(minutes);
    _userTsEntry.ts_seconds =  NUM2_TO_BCD(seconds);

    //printf("-D- timestamp: %04x-%02x-%02xT%02x:%02x:%02x\n", _userTsEntry.ts_year, _userTsEntry.ts_month,
    //                                                        _userTsEntry.ts_day, _userTsEntry.ts_hour, _userTsEntry.ts_minutes, _userTsEntry.ts_seconds);
    return true;
}

bool TimeStampSubCommand::verifyParams()
{
    if (_flintParams.cmd_params[0] == "query") {
        if (_flintParams.cmd_params.size() > 1) {
            reportErr(true, "query operation requires no arguments.\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Query;
    } else if (_flintParams.cmd_params[0] == "set") {
        if (_flintParams.image_specified && _flintParams.cmd_params.size() > 2) {
            reportErr(true, "too many arguments for set operation on image.\n");
            return false;
        } else if (_flintParams.device_specified && _flintParams.cmd_params.size() != 3) {
            reportErr(true, "set operation on device requires timestamp and FW version arguments.\n\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Set;
        // attempt to parse timestamp and fw version
        if (_flintParams.image_specified && _flintParams.cmd_params.size() == 1) {
            // take time from machine
            getMachineUTCTime();
        } else if (!parseTimeStamp(_flintParams.cmd_params[1])) {
            return false;
        }
        if (_flintParams.device_specified && !parseFwVersion(_flintParams.cmd_params[2])) {
            return false;
        }
    } else if (_flintParams.cmd_params[0] == "reset") {
        if (_flintParams.cmd_params.size() > 1) {
            reportErr(true, "erase operation requires no arguments.\n");
            return false;
        }
        _operation = TimeStampSubCommand::TS_Reset;
    } else {
        reportErr(true, "Unknown operation, allowed operations: query/set/reset.\n");
        return false;
    }
    return true;
}

void TimeStampSubCommand::printTsAndFwVer(string prefix, struct tools_open_ts_entry& tsEntry, struct tools_open_fw_version& fwVer)
{
    printf("%-24s: %04x-%02x-%02xT%02x:%02x:%02xZ    %02d.%02d.%04d\n", prefix.c_str(), tsEntry.ts_year, tsEntry.ts_month, tsEntry.ts_day,
           tsEntry.ts_hour, tsEntry.ts_minutes, tsEntry.ts_seconds,
           fwVer.fw_ver_major, fwVer.fw_ver_minor, fwVer.fw_ver_subminor);
}

bool TimeStampSubCommand::queryTs()
{
    struct tools_open_ts_entry tsEntry;
    struct tools_open_fw_version fwVer;
    memset(&tsEntry, 0, sizeof(tsEntry));
    memset(&fwVer, 0, sizeof(fwVer));
    // get and Print Current Running FW TS in case of device
    if (_flintParams.device_specified) {
        if (!_ops->FwQueryTimeStamp(tsEntry, fwVer, true)) {
            printf("%-24s: N/A. %s\n", "Current timestamp", _ops->err());
        } else {
            printTsAndFwVer("Current timestamp", tsEntry, fwVer);
        }
    }
    // get and print next FW timestamp
    if (!_ops->FwQueryTimeStamp(tsEntry, fwVer, false)) {
        printf("%-24s: N/A. %s\n", "Next timestamp", _ops->err());
    } else {
        printTsAndFwVer("Next timestamp", tsEntry, fwVer);
    }
    return true;
}

bool TimeStampSubCommand::setTs()
{
    if (!_ops->FwSetTimeStamp(_userTsEntry, _userFwVer)) {
        reportErr(false, "%s", _ops->err());
        return false;
    }
    return true;
}

bool TimeStampSubCommand::resetTs()
{
    if (!_ops->FwResetTimeStamp()) {
        reportErr(false, "%s", _ops->err());
        return false;
    }
    return true;
}

FlintStatus TimeStampSubCommand::executeCommand()
{
    bool rc;

    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    _ops = _flintParams.device_specified ? _fwOps : _imgOps;
    (void)_ops;
    switch (_operation) {
    case TimeStampSubCommand::TS_Set:
        rc = setTs();
        break;

    case TimeStampSubCommand::TS_Query:
        rc = queryTs();
        break;

    case TimeStampSubCommand::TS_Reset:
        rc = resetTs();
        break;

    default:
        // should not be reached
        reportErr(true, "Failed to perform timestamp operation: Unknown Error\n");
        return FLINT_FAILED;
    }
    if (!rc) {
        printf("-E- Failed to perform timestamp %s operation. %s\n", _flintParams.cmd_params[0].c_str(), _errBuff);
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}


/***********************
 * Class: CacheImage
 **********************/
CacheImageSubCommand:: CacheImageSubCommand()
{
    _name = "cache image";
    _desc = "cache FW image(Windows only).";
    _extendedDesc = "cache the FW image using Mellanox driver to allow faster FW load time upon loading the driver(Windows only).";
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

CacheImageSubCommand:: ~CacheImageSubCommand()
{

}

FlintStatus CacheImageSubCommand:: executeCommand()
{
#ifdef __WIN__
    int rc;

    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    rc = wdcif_send_image_cache_request(((Flash*)_io)->getMfileObj());
    if (rc) {
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
