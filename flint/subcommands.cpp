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
 *     conditions are met:FwVerify
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

#if !defined(__WIN__) && !defined(__DJGPP__) && !defined(UEFI_BUILD) && defined(HAVE_TERMIOS_H)
    // used in mygetchar
    #include <termios.h>
#endif

#include "subcommands.h"

using namespace std;

#define INDENT "\t\t\t\t\t\t"
#define INDENTEX "\t"

/***********************************
 *  Log file writing implementation
************************************/

//global log file header
FILE* flint_log_fh = NULL;

#define BURN_INTERRUPTED 0x1234

void close_log()
{
    if (flint_log_fh != NULL) {
        fclose(flint_log_fh);
        flint_log_fh = NULL;
    }
    return;
}

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

const char*   month_2monstr (int month) {
    static const char* month_2monstr_arr[] = {
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
    int arr_size = (int)ARR_SIZE(month_2monstr_arr);
    return month < arr_size ? month_2monstr_arr[month] : "???";
}

void print_time_to_log()
{
    time_t rawtime;
    struct tm * timeinfo;

    if (flint_log_fh == NULL) {
        return;
    }
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    fprintf(flint_log_fh, "%-3s %2d %02d:%02d:%02d ", month_2monstr(timeinfo->tm_mon), timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return;
}

int print_line_to_log(const char* format, ...)
{
    va_list  args;
    if (flint_log_fh == NULL) {
        return 0;
    }
    print_time_to_log();
    va_start(args, format);
    vfprintf(flint_log_fh, format, args);
    va_end(args);
    return 0;
}

int write_cmd_to_log(string fullCmd , sub_cmd_t cmd, bool write)
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

int write_result_to_log(int is_failed, const char* err_msg, bool write)
{
    if (!write) {
        return 0;
    }
    char msg[MAX_ERR_STR_LEN];
    strcpy(msg, err_msg);
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

static bool str2Num(const char* str, u_int32_t& num) {
    char* endp;
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

bool SubCommand::isCmdSupportLog() {
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
    va_list  args;

    va_start(args, format);

    if (vsnprintf(_errBuff, FLINT_ERR_LEN, format, args) >= FLINT_ERR_LEN) {
        strcpy(&_errBuff[FLINT_ERR_LEN - 5], "...\n");
    }
    //print to the user and to the log if needed
    if (shouldPrint) {
        fprintf(stdout,PRE_ERR_MSG" %s",_errBuff);
    }
    write_result_to_log(FLINT_FAILED,_errBuff, isCmdSupportLog());
    va_end(args);

    return;
}

bool SubCommand::writeToFile(string filePath, const std::vector<u_int8_t>& buff) {
    FILE* fh;
    if ((fh = fopen(filePath.c_str(), "wb")) == NULL) {
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

int SubCommand::verifyCbFunc(char* str)
{
    printf("%s", str);
    return 0;
}

int SubCommand::CbCommon(int completion, char*preStr, char* endStr)
{
    if (completion < 100) {
            printf("\r%s%%%03d", preStr, completion);
        }else if (completion == 100) {
            printf("\r%sOK  \n", preStr);
        } else {// printing endStr
            if (endStr){
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
    char* message = (char*)"Burning FS3 FW image without signatures - ";
    char* endStr =  (char*)"Restoring signature                     - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::burnCbFs2Func(int completion)
{
    char* message = (char*)"Burning FS2 FW image without signatures - ";
    char* endStr =  (char*)"Restoring signature                     - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::bromCbFunc(int completion)
{
    char* message = (char*)"Burning ROM image    - ";
    char* endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::dromCbFunc(int completion)
{
    char* message = (char*)"Removing ROM image    - ";
    char* endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::resetCfgCbFunc(int completion)
{
    char* message = (char*)"Resetting NV configuration - ";
    char* endStr =  (char*)"Restoring signature        - OK";
    return CbCommon(completion, message, endStr);
}


int SubCommand::burnBCbFunc(int completion)
{
    return CbCommon(completion,(char*)"");
}

int SubCommand::vsdCbFunc(int completion)
{
    char* message = (char*)"Setting the VSD      - ";
    char* endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::setKeyCbFunc(int completion)
{
    char* message = (char*)"Setting the HW Key   - ";
    char* endStr =  (char*)"Restoring signature  - OK";
    return CbCommon(completion, message, endStr);
}

int SubCommand::wbCbFunc(int completion)
{
    char* message = (char*)"Writing Block:   - ";
    return CbCommon(completion, message, NULL);
}

#define ERR_BUFF_SIZE 1024
FlintStatus SubCommand:: openOps()
{
    char errBuff[ERR_BUFF_SIZE];
    errBuff[0] = '\0';
    if (_flintParams.device_specified) {
        // fillup the fw_ops_params_t struct
        FwOperations::fw_ops_params_t fwParams;
        memset(&fwParams, 0 , sizeof(FwOperations::fw_ops_params_t));
        fwParams.errBuff = errBuff;
        fwParams.errBuffSize = ERR_BUFF_SIZE;
        fwParams.flashParams =_flintParams.flash_params_specified ? &_flintParams.flash_params : NULL;
        fwParams.forceLock = _flintParams.clear_semaphore;
        fwParams.hndlType = FHT_MST_DEV;
        fwParams.ignoreCacheRep = _flintParams.override_cache_replacement ? 1 : 0;
        fwParams.mstHndl = strcpy(new char[_flintParams.device.length()+1],_flintParams.device.c_str());
        fwParams.numOfBanks = _flintParams.banks;
        fwParams.readOnly = false;
        fwParams.noFlashVerify = _flintParams.no_flash_verify;
        _fwOps = FwOperations::FwOperationsCreate(fwParams);
        delete[] fwParams.mstHndl;
    }
    if (_flintParams.image_specified) {
        _imgOps = FwOperations::FwOperationsCreate((void*)_flintParams.image.c_str(), NULL, NULL,\
                FHT_FW_FILE, errBuff, 1024);
    }
    if (_flintParams.device_specified && _fwOps == NULL)
    {
        reportErr(true, FLINT_OPEN_FWOPS_DEVICE_ERROR, _flintParams.device.c_str(), strlen(errBuff) != 0 ? errBuff : "");
        return FLINT_FAILED;
    }
    if (_flintParams.image_specified && _imgOps == NULL)
    {
        reportErr(true, FLINT_OPEN_FWOPS_IMAGE_ERROR, _flintParams.image.c_str(), strlen(errBuff) != 0 ? errBuff : "");
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
                NULL, _flintParams.override_cache_replacement)) {
            // if we have Hw_Access command we dont fail straght away
            if (_flintParams.cmd == SC_Hw_Access && ((Flash*)_io)->get_cr_space_locked()) {
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
        char* logFile;
        logFile = getenv(FLINT_LOG_ENV);
        if (logFile) {
            _flintParams.log = logFile;
            _flintParams.log_specified = true;
        }
    }
    //open log if needed
    openLog();
    switch (_v) {
    case Wtv_Img:
        if ( _flintParams.device_specified == true) {
                _flintParams.image_specified ? reportErr(true, FLINT_COMMAND_IMAGE_ERROR2,_name.c_str()) :
                        reportErr(true, FLINT_COMMAND_IMAGE_ERROR, _name.c_str());
                return false;
            }
            if ( _flintParams.image_specified == false ) {
                reportErr(true, FLINT_NO_IMAGE_ERROR);
                return false;
            }
            break;
    case Wtv_Dev:
        if ( _flintParams.image_specified == true) {
                _flintParams.device_specified ? reportErr(true, FLINT_COMMAND_DEVICE_ERROR2,_name.c_str()) :
                        reportErr(true, FLINT_COMMAND_DEVICE_ERROR, _name.c_str());
                return false;
            }
            if ( _flintParams.device_specified == false ) {
                reportErr(true, FLINT_NO_DEVICE_ERROR);
                return false;
            }
            break;
    case Wtv_Dev_And_Img:
        if (( _flintParams.image_specified == false) || ( _flintParams.device_specified == false)) {
            reportErr(true, FLINT_COMMAND_DEVICE_IMAGE_ERROR, _name.c_str());
            return false;
        }
        break;
    case Wtv_Dev_Or_Img:
        if ( _flintParams.image_specified == true && _flintParams.device_specified == true) {
                reportErr(true, FLINT_DEVICE_AND_IMAGE_ERROR);
                return false;
            }
        if ( _flintParams.device_specified == false  && _flintParams.image_specified == false ) {
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

bool SubCommand::getRomsInfo(FBase* io, roms_info_t& romsInfo)
{
    std::vector<u_int8_t> romSector;
    romSector.clear();
    romSector.resize(io->get_size());
    if (!io->read(0, &romSector[0], io->get_size())) {
           reportErr(true, FLINT_READ_ERROR,_flintParams.image.c_str(), io->err());
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
    if (*endp || (g == 0xffffffffffffffffULL && errno == ERANGE)) {
        if (prefixErr.size() == 0) {
            reportErr(true, "Invalid GUID syntax (%s) %s \n", str.c_str(), errno ? strerror(errno) : "" );
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
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

bool SubCommand::getPasswordFromUser(const char *preStr, char buffer[MAX_PASSWORD_LEN+1])
{
    char c;
    int pos = 0;

    printf("%s: ", preStr);
    do {
        c = mygetch();

        if( ((pos < MAX_PASSWORD_LEN)) && isprint(c) ) {
            buffer[ pos++ ] = c;
            printf("%c", '*');
        } else if( (c == 8 || c == 127) && pos ) {
            buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }


    } while( c != '\n' );
    printf("\n");
    buffer[pos] = '\0';
    return true;
}

#else
bool SubCommand::getPasswordFromUser(const char *preStr, char buffer[MAX_PASSWORD_LEN+1])
{
    //TODO: Buffer Overflow danger use loop with gets() or istream
    printf("%s: ", preStr);
    scanf("%256s", buffer);
    return true;
}

#endif

//
// Asks user a yes/no question.
// Returns true if user chose Y, false if user chose N.
//

bool SubCommand::askUser(const char *question, bool printAbrtMsg) {
    if (question == NULL) {
        printf("\n Do you want to continue ? (y/n) [n] : ");
    } else {
        printf("\n %s ? (y/n) [n] : ", question);

    }

    if (_flintParams.yes)
        printf("y\n");
    else {
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
        //  return false;
        //}

        if (  strcasecmp(answer.c_str(), "y") &&
              strcasecmp(answer.c_str(), "yes"))  {

            if (printAbrtMsg) {
            reportErr(true, "Aborted by user\n");
            }
            return false;
        }
    }
    return true;
}

void SubCommand::displayOneExpRomInfo(const rom_info_t& info) {

	const char* typeStr = FwOperations::expRomType2Str(info.exp_rom_product_id);
    if (info.exp_rom_product_id == 0xf) {// version id in this case is the freeStr that was moved to exp_rom_ver[0] in mlxfwops
        printf("devid=%d version_id=%d type=%s ", info.exp_rom_dev_id,info.exp_rom_ver[0], typeStr);
    } else {
    	if (typeStr) {
    		printf("type=%s ", typeStr);
    	} else {
    		 printf("0x%x - Unknown ROM product ID\n", info.exp_rom_product_id);
    		 return;
    	}

        printf("version=%d", info.exp_rom_ver[0]);
        if (info.exp_rom_product_id >= 0x10) {
            printf(".%d.%d", info.exp_rom_ver[1], info.exp_rom_ver[2]);

            if (info.exp_rom_dev_id != EXP_ROM_GEN_DEVID) {
                // Do not display if 0 - ROM is the same for all device IDs
                printf(" devid=%d", info.exp_rom_dev_id);
            }
            if (info.exp_rom_port) {
                // Do not display if 0 - port independent
                printf(" port=%d", info.exp_rom_port);
            }
            if (info.exp_rom_product_id != 0x12) { // on CLP(0x12) there is no meaning to protocol
            	printf(" proto=");
            	switch (info.exp_rom_proto) {
            	case ER_IB:
            		printf("IB");
            		break;
            	case ER_ETH:
            		printf("ETH");
            		break;
            	case ER_VPI:
            		printf("VPI");
            		break;
            	default:
            		printf("0x%x", info.exp_rom_proto);
            	}
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
                for ( j = 0; j < strLen; j++) {
                    printf("%s", " ");
                }
            }
            // Display a ROM info
            displayOneExpRomInfo(romsInfo.rom_info[i]);
            if (i != romsInfo.num_of_exp_rom - 1) { // Don't print new line after the info of the last ROM
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

bool SubCommand::printGuidLine(guid_t* new_guids, guid_t* old_guids, int guid_index)
{
    printf(GUID_FORMAT GUID_SPACES, new_guids[guid_index].h, new_guids[guid_index].l);
    if (old_guids != NULL) {
        printf(GUID_FORMAT,  old_guids[guid_index].h, old_guids[guid_index].l);
    }else {
        printf("      N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printBxGuids(guid_t* new_guids, guid_t* old_guids, int index, int num_of_guids, const char* pre_str)
{
    int guid_index = index;
    int _is_wwpn = ((guid_index - BI_WWPNS) % BX_SLICE_GUIDS);

    for (int i = 0; i < num_of_guids; i++) {
        printf("    G%d", (index >= BX_SLICE_GUIDS));
        if (i == 0 && _is_wwpn) {
           printf(" Node  %s:      ", pre_str);
        } else {
            int j = _is_wwpn ? i : i + 1;
            printf(" Port%d %s:      ", j, pre_str);
        }
        printGuidLine(new_guids, old_guids,  guid_index);
        guid_index++;
    }
    return true;
}

bool SubCommand::printMacLine(guid_t* new_guids, guid_t* old_guids, int mac_index)
{
    printf("    "MAC_FORMAT MAC_SPACES, new_guids[mac_index].h, new_guids[mac_index].l);
    if (old_guids != NULL) {
        printf(MAC_FORMAT, old_guids[mac_index].h, old_guids[mac_index].l);
    } else {
        printf("  N/A");
    }
    printf("\n");
    return true;
}

bool SubCommand::printBxMacs(guid_t* new_guids, guid_t* old_guids, int index, int num_of_guids, const char* pre_str)
{
    int guid_index = index;

    for (int i = 0; i < num_of_guids; i++) {
        printf("    G%d", (index >= BX_SLICE_GUIDS));
        printf(" Port%d %s:      ", i + 1, pre_str);
        printMacLine(new_guids, old_guids, guid_index);
        guid_index++;
    }
    return true;
}

bool SubCommand::printUidsFunc(guid_t* new_guids, guid_t* old_guids)
{
    int base_index = 0, guid_index;

    for (int i = 0; i < BX_SLICES_NUM; i++) {
        base_index = i * BX_SLICE_GUIDS;
        // Init Guids
        printBxGuids(new_guids, old_guids, base_index + BI_GUIDS, BX_NP_GUIDS, "Guid");
        printBxMacs (new_guids, old_guids, base_index + BI_IMACS, BX_IMACS,    "IMAC");
        printBxMacs (new_guids, old_guids, base_index + BI_EMACS, BX_EMACS,    "EMAC");
        printBxGuids(new_guids, old_guids, base_index + BI_WWNNS, BX_WWNNS,    "WWNN");
        printBxGuids(new_guids, old_guids, base_index + BI_WWPNS, BX_WWPNS,    "WWPN");
     }

    // Init SysGuid
    //INCR_GUID(base_guid1, user_guids[Operations::BI_SYS_GUID], 7);
    guid_index = BI_SYS_GUID;
    printf("    System   GUID:      ");
    printGuidLine(new_guids, old_guids,  guid_index);
    return true;
}

bool SubCommand::printGUIDsFunc(guid_t guids[GUIDS],guid_t macs[MACS], guid_t old_guids[GUIDS],\
        guid_t old_macs[MACS], bool print_guids, bool print_macs, int portNum, bool old_guid_fmt) {

    if (print_guids) {
        printf("        Node  GUID:     ");
        printGuidLine(guids,old_guids, 0);
        if (portNum > 0) {
            printf("        Port1 GUID:     ");
            printGuidLine(guids,old_guids, 1);
        }
        if (portNum > 1) {
            printf("        Port2 GUID:     ");
            printGuidLine(guids,old_guids, 2);
        }
        if (!old_guid_fmt) {
            printf("        Sys.Image GUID: ");
            printGuidLine(guids,old_guids, 3);
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

bool SubCommand::reportGuidChanges(guid_t* new_guids, guid_t* new_macs,\
                                    guid_t* old_guids, guid_t* old_macs, bool printGuids,\
                                    bool printMacs, bool printUids, int guidNum)
{
    //should be used ONLY on FS2 in current implementation
    printf("    You are about to change the Guids/Macs/Uids on the %s:\n\n", _flintParams.device_specified ? "device" : "image");
    printf("                        New Values      " GUID_SPACES "Current Values\n");
    if (printUids) {
        printUidsFunc(new_guids, old_guids );
    } else {
       printGUIDsFunc(new_guids, new_macs,
                  old_guids, old_macs,
                  printGuids,
                  printMacs,
                  guidNum,
                  guidNum < GUIDS);
    }
    if (!askUser())
        return false;

    return true;
}

bool SubCommand::fwVerLessThan(const u_int16_t r1[3], const u_int16_t r2[3])
{
    for (int i = 0; i < 3 ; i++) {
        if (r1[i] < r2[i]) {
            return true;
        }
        else if (r1[i] > r2[i]) {
            return false;
        }
    }
    return false; // equal versions
}

//used for dc and dh subcommands

bool SubCommand::unzipDataFile (std::vector<u_int8_t> data, std::vector<u_int8_t> &newData, const char *sectionName)
{
#ifndef NO_ZLIB
    int rc;
    if (data.empty()) {
        reportErr(true, "%s section not found in the given image.", sectionName);
        return false;
    }
    // restore endianess.
    TOCPUn(&(data[0]), data.size()/4);

    // uncompress:
    uLongf destLen = data.size();
    destLen *= 40; // Assuming this is the best compression ratio
    vector<u_int8_t> dest(destLen);

    for (int i = 0; i < 32; i++) {
        rc = uncompress((Bytef *)&(dest[0]), &destLen,
                            (const Bytef *)&(data[0]), data.size());
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

bool SubCommand::dumpFile(const char* confFile, std::vector<u_int8_t>& data, const char *sectionName) {
    FILE* out;
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
        return false;
    }
    fprintf(out, "%s", (char*)&(dest[0]));

    if (confFile != NULL) {
        fclose(out);
    }
    return true;
}

bool SubCommand::checkGuidsFlags (chip_type_t ct, u_int16_t devType, u_int8_t fwType,
                            bool guidsSpecified, bool macsSpecified, bool uidsSpecified) {

    if (guidsSpecified || macsSpecified || uidsSpecified) {
        if (ct == CT_BRIDGEX) {
            if (macsSpecified || guidsSpecified) {
                reportErr(true, "-mac(s)/-guid(s) flags is not applicable for MT%d.\n",devType);
                return false;
            }
        } else {
            if (uidsSpecified) {
                reportErr(true, "-uid(s) flag is applicable only for BridgeX and FS3 FW.\n");
                return false;
            } else if (fwType != FIT_FS2 && macsSpecified ) {
                reportErr(true, "-mac(s) flag is not applicable for IB MT%d device.\n", devType);
                return false;
            }// else if (!_fwOps->CntxEthOnly() && guids_specified) {
            //     return errmsg("-guid(s) flag is not applicable for IB MT%d device.\n",
            //                  devType);
            //}
        }
    }
    return true;
}

void SubCommand::printMissingGuidErr(bool ibDev, bool ethDev, bool bxDev)
{
    const char* missingInfo;
    const char* missingFlags;

    if (bxDev) {
        missingInfo  = "UIDs (GUIDs / MACs / WWNs)";
        missingFlags = "-uid(s)";
    } else {
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

    }
    printf("Please specify %s (using command line flags %s ).\n", missingInfo, missingFlags);
    return;
}

bool SubCommand::extractUIDArgs(std::vector<string>& cmdArgs, u_int8_t& numOfGuids, u_int8_t& stepSize){
    //extract num_of_guids and step_size from numGuidsStr, stepStr
    u_int32_t tempNumOfGuids = 0;
    u_int32_t tempStepSize = 0;
    string tag, valStr;
    for (std::vector<string>::iterator it = cmdArgs.begin(); it != cmdArgs.end(); it++) {
        std::stringstream ss((it->c_str()));
        // get the tag
        if (!std::getline(ss, tag, '=')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR,it->c_str());
            return false;
        }
        // get the val
        if (!std::getline(ss, valStr, '=')) {
            reportErr(true, FLINT_INVALID_ARG_ERROR,it->c_str());
            return false;
        }
        // make sure no other tokens are present
        if (!(!std::getline(ss, valStr, '='))) {
            reportErr(true, FLINT_INVALID_ARG_ERROR,it->c_str());
            return false;
        }
        if (tag == "guids_num") {
            if (!str2Num(valStr.c_str(), tempNumOfGuids)) {
                reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
                return false;
            }
        } else if (tag == "step_size") {
            if (!str2Num(valStr.c_str(), tempStepSize)) {
                reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
                return false;
            }
        } else {
            reportErr(true, FLINT_INVALID_ARG_ERROR, it->c_str());
            return false;
        }
    }
    // perform checks
    if (tempNumOfGuids <= 0 || tempNumOfGuids >= 256 ||  tempStepSize<=0 || tempStepSize>=256) {
        reportErr(true, "Invalid argument values, values should be taken from the range [1..255]\n");
        return false;
    }
    numOfGuids = tempNumOfGuids;
    stepSize = tempStepSize;
    return true;
}

/***********************
 *Class: BurnSubCommand
 **********************/

BurnSubCommand:: BurnSubCommand()
{
    _name = "burn";
    _desc = "Burn flash";
    _extendedDesc = "Burn flash \n"
                    INDENTEX"Performs failsafe FW update from a raw binary image.";
    _flagLong = "burn";
    _flagShort = "b";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" -i image1.bin burn\n"
              INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE2" -guid 0x2c9000100d050 -i image1.bin b";
    _v = Wtv_Dev_And_Img;
    _cmdType = SC_Burn;
    _fwType = 0;
    _devQueryRes = 0;
    memset(&_devInfo, 0, sizeof(_devInfo));
    memset(&_imgInfo, 0, sizeof(_imgInfo));
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
    if ((_flintParams.guid_specified || _flintParams.guid_specified) && (_flintParams.uid_specified || _flintParams.uids_specified)) {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either GUIDs / UIDs (using command line flags -guid(s) / -uid(s) )");
            return false;
        }
    if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified || _flintParams.uids_specified)) {
            reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either MACs / UIDs (using command line flags -mac(s) / -uid(s) )");
            return false;
        }
    bool GuidsFromUser = _flintParams.guid_specified || _flintParams.guid_specified ||\
            _flintParams.uid_specified || _flintParams.uids_specified|| \
            _flintParams.mac_specified || _flintParams.macs_specified;
    if (GuidsFromUser && _flintParams.use_image_guids) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR,"GUIDs/UIDs/MACs", "-use_image_guids");
        return false;
    }
    if ((GuidsFromUser || _flintParams.use_image_guids) && _flintParams.blank_guids) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, _flintParams.use_image_guids ? \
                "-use_image_guids" : "GUIDs/UIDs/MACs", "-blank_guids");
        return false;
    }
    if (_flintParams.guid_specified && _flintParams.guids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid" );
        return false;
    }
    if (_flintParams.mac_specified && _flintParams.macs_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-macs", "-mac" );
        return false;
    }
    if (_flintParams.uid_specified && _flintParams.uids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-uids", "-uid" );
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
    return true;
}

void BurnSubCommand::updateBurnParams()
{
    _burnParams.progressFunc = _flintParams.silent == true ? (ProgressCallBack)NULL :\
    		_fwType == FIT_FS2? &burnCbFs2Func : &burnCbFs3Func;
    _burnParams.userGuidsSpecified = _flintParams.guids_specified || _flintParams.guid_specified;
    _burnParams.userMacsSpecified = _flintParams.macs_specified || _flintParams.mac_specified;
    _burnParams.userUidsSpecified = _flintParams.uids_specified || _flintParams.uid_specified;
    _burnParams.vsdSpecified = _flintParams.vsd_specified;
    _burnParams.blankGuids = _flintParams.blank_guids;
    _burnParams.burnFailsafe = !_flintParams.nofs;
    _burnParams.allowPsidChange = _flintParams.allow_psid_change;
    _burnParams.useImagePs = _flintParams.use_image_ps;
    _burnParams.burnRomOptions = _flintParams.use_image_rom ? FwOperations::ExtBurnParams::BRO_ONLY_FROM_IMG \
                                                                : FwOperations::ExtBurnParams::BRO_DEFAULT ;
    _burnParams.useImageGuids = _flintParams.use_image_guids;
    _burnParams.singleImageBurn = !_flintParams.dual_image;
    _burnParams.noDevidCheck = _flintParams.no_devid_check;
    _burnParams.useImgDevData = _flintParams.ignore_dev_data;
    if (_burnParams.userGuidsSpecified) {
        _burnParams.userUids = _flintParams.user_guids;
    }
    if (_burnParams.userUidsSpecified) {
        _burnParams.userUids = _flintParams.user_uids;
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
        _burnParams.userVsd = strcpy(new char[_flintParams.vsd.size()+1], _flintParams.vsd.c_str());
    }
    //make sure its of max size and fill the rest with 0xffff
    _burnParams.userUids.resize(MAX_GUIDS, (guid_t){0xffffffff,0xffffffff});
}

bool BurnSubCommand::checkFwVersion()
{
    char curr_ver[124], new_ver[124];
    printf("\n");
    printf("    Current FW version on flash:  ");
    if (_devInfo.fw_info.fw_ver[0] != 0) { // i.e if we have a fw_version we assume this is != 0
        snprintf(curr_ver, 124, "%d.%d.%d", _devInfo.fw_info.fw_ver[0], _devInfo.fw_info.fw_ver[1], _devInfo.fw_info.fw_ver[2]);
    } else {
        snprintf(curr_ver, 124, "N/A");
    }
    printf("%s", curr_ver); printf("\n");

    printf("    New FW version:               ");
    if (_imgInfo.fw_info.fw_ver[0] != 0) {
        snprintf(new_ver, 124, "%d.%d.%d", _imgInfo.fw_info.fw_ver[0], _imgInfo.fw_info.fw_ver[1], _imgInfo.fw_info.fw_ver[2]);
    } else {
        snprintf(new_ver, 124, "N/A");
    }
    printf("%s", new_ver); printf("\n");

    if (_flintParams.log_specified) {
        print_line_to_log("Current FW version on flash: %s,  New FW version: %s\n", curr_ver, new_ver);
    }
    bool updateRequired = true;

    if (_devInfo.fw_info.fw_ver[0] != 0  &&
            _imgInfo.fw_info.fw_ver[0] != 0) {
        updateRequired = fwVerLessThan(_devInfo.fw_info.fw_ver,_imgInfo.fw_info.fw_ver);
    }

    if (!updateRequired) {
        printf("\n    Note: The new FW version is not newer than the current FW version on flash.\n");
        if (!askUser()) {
            return false;
        }
    }
    printf("\n");
    _burnParams.ignoreVersionCheck = true;
    return true;

}

bool BurnSubCommand::checkPSIDAndIbEth()
{
    //bool ib_dev;
    //bool eth_dev;
    //setDevFlags(_devInfo, ib_dev, eth_dev);
    //all FW now support both ETH and IB so the OLD IB/ETH FW check is not needed anymore (see old implementation of flint)

    if (strlen(_imgInfo.fw_info.psid) != 0  && strlen(_devInfo.fw_info.psid) != 0 &&
            strncmp( _imgInfo.fw_info.psid, _devInfo.fw_info.psid, PSID_LEN)) {
        if (_flintParams.allow_psid_change) {
                 printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"
                        "    Note: It is highly recommended not to change the PSID.\n",
                        _devInfo.fw_info.psid, _imgInfo.fw_info.psid);
                 if (! askUser()) {
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
    // Here we want to burn FS3 device so we check if the image is indeed FS3 image
    if (_imgInfo.fw_type != FIT_FS3) {
        reportErr(true, FLINT_IMG_DEV_COMPAT_ERROR, "FS3", "FS3");
        return FLINT_FAILED;
        }
    // on FS3 burn we require query to pass
    if (!_devQueryRes && _burnParams.burnFailsafe) {
        reportErr(true, FLINT_FS3_BURN_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }

    //check FwVersion
    if ( !checkFwVersion()) {
        return FLINT_BURN_ABORTED;
    }
    // check Psid
    if (_devQueryRes && !checkPSIDAndIbEth()) {
        return FLINT_FAILED;
    }
    // deal with rom

    dealWithExpRom();
    bool getRomFromDev = ( _burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST);
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo)) {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type,\
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
    if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams)) {
        reportErr(true, FLINT_FS3_BURN_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    PRINT_PROGRESS(_burnParams.progressFunc, 101);

    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    const char* resetRec = _fwOps->FwGetResetRecommandationStr();
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

    dealWithExpRom();
    bool getRomFromDev = _burnParams.burnRomOptions == FwOperations::ExtBurnParams::BRO_FROM_DEV_IF_EXIST;
    if (!getRomFromDev && !checkMatchingExpRomDevId(_imgInfo)) {
        printf("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", _imgInfo.fw_info.dev_type,\
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
            _imgInfo.fw_info.is_failsafe ? "flash" : "given file",  _imgInfo.fw_info.is_failsafe? "" : " non",\
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
    if (_devQueryRes && !checkPSIDAndIbEth()) {
        return FLINT_FAILED;
    }

    // Warn if a fw which does not support config is burnt over fw that does support config
    // The other way (new fw with config, old fw w/o config) is a normal update flow.
    // Update: all fw should now support config sectors, so we just check any missmatch in the config pads


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
    if (!_fwOps->FwBurnAdvanced(_imgOps, _burnParams))
    {
        reportErr(true, FLINT_FS2_BURN_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    PRINT_PROGRESS(_burnParams.progressFunc, 101);
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
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
    bool bx_dev;
    // Get the FW types
    bx_dev = _imgInfo.fw_info.chip_type == CT_BRIDGEX;
    FwOperations::SetDevFlags(_imgInfo.fw_info.chip_type, _imgInfo.fw_info.dev_type, (fw_img_type)_imgInfo.fw_type, ib_dev, eth_dev);
    //setDevFlags(_imgInfo, ib_dev, eth_dev);

    // Check if there is a need to read guids
    if (_burnParams.useImageGuids || _burnParams.blankGuids
            || (_burnParams.userGuidsSpecified && ib_dev)
            || (_burnParams.userMacsSpecified)
            || (_burnParams.userUidsSpecified && bx_dev)) {
        read_guids = false;
    }
    // Check if the burnt FW is ok and readable in order to get the GUIDs later
    if (read_guids && !_devQueryRes) {
        //printMissingGuidErr(ib_dev, eth_dev, bx_dev);
        if (_burnParams.burnFailsafe) {
            reportErr(true,
                    "Can not extract GUIDs/MACs info from flash, %s\n"
                            "    Can not burn in a failsafe mode.\n"
                            "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n", _fwOps->err());
        } else {
            reportErr(true, "Can not extract GUIDs/MACs info from flash, %s", _fwOps->err());
            printMissingGuidErr(ib_dev, eth_dev, bx_dev);
        }
        return false;
    }
    // Check guids flag to ensure correct patching of guids in mlxfwops
    bool is_guids_specified = _burnParams.userGuidsSpecified
            || _burnParams.userMacsSpecified
            || _burnParams.userUidsSpecified;
    if (is_guids_specified) {
        if (!checkGuidsFlags((chip_type_t)_imgInfo.fw_info.chip_type, _imgInfo.fw_info.dev_type, _fwType,\
                _burnParams.userGuidsSpecified, _burnParams.userMacsSpecified, _burnParams.userUidsSpecified)) {
            return false;
        }
    }
    //report guid changes if needed. and update the user_guids vector in _burnParams
     if (is_guids_specified || _flintParams.use_image_guids) {
         guid_t* new_guids = ( _burnParams.userGuidsSpecified || _burnParams.userUidsSpecified )?\
                 &_burnParams.userUids[0] : _devInfo.fs2_info.guids;
         guid_t* new_macs = _burnParams.userMacsSpecified != 0 ? &_burnParams.userUids[GUIDS] : &_devInfo.fs2_info.guids[GUIDS];
         guid_t* old_guids = !_devQueryRes ? NULL : _devInfo.fs2_info.guids;
         guid_t* old_macs = old_guids != NULL ? &old_guids[GUIDS] : NULL;
         if (!is_guids_specified && _flintParams.use_image_guids) {
             new_guids = _imgInfo.fs2_info.guids;
             new_macs = &_imgInfo.fs2_info.guids[GUIDS];
         }
         //printf("-D- l=%d, h=%d\n", new_macs->l, new_macs->h);
             if (!reportGuidChanges(new_guids, new_macs, old_guids, old_macs, ib_dev,\
                     eth_dev, bx_dev, _imgInfo.fs2_info.guid_num)) {
                 return false;
             }

    }
    return true;
}

void BurnSubCommand::dealWithExpRom()
{
    bool getRomFromDev = false;
    // Check exp rom:
    bool fs2Cond = _fwType == FIT_FS2? (_devQueryRes && _devInfo.fw_info.chip_type == CT_CONNECTX && \
            (FwOperations::IsFwSupportingRomModify(_devInfo.fw_info.fw_ver) || (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0))\
            && !_flintParams.use_image_rom && !strcmp(_devInfo.fw_info.product_ver,"") && !strcmp(_imgInfo.fw_info.product_ver, "")) : false;

    bool fs3Cond = _fwType == FIT_FS3 ? (_devQueryRes && (_devInfo.fw_info.chip_type == CT_CONNECT_IB || _devInfo.fw_info.chip_type == CT_CONNECTX) && \
            (FwOperations::IsFwSupportingRomModify(_devInfo.fw_info.fw_ver) || (_imgInfo.fw_info.roms_info.num_of_exp_rom > 0))\
            && !_flintParams.use_image_rom) && !strcmp(_devInfo.fw_info.product_ver,"") && !strcmp(_imgInfo.fw_info.product_ver, "") : false;

    bool cond = _fwType == FIT_FS2 ? fs2Cond : fs3Cond;

    if (cond) {
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
    return;
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
    if (!_imgOps->FwQuery(&_imgInfo))
        {
            reportErr(true, FLINT_FAILED_QUERY_ERROR, "image", _flintParams.image.c_str(), _imgOps->err());
            return FLINT_FAILED;
        }
    //updateBurnParams with input given by user
    updateBurnParams();
    if (_fwType == FIT_FS3) {
        return burnFs3();
    } else if (_fwType == FIT_FS2) {
    return burnFs2();
    }
    // unknown fw type
    reportErr(true, FLINT_UNKNOWN_FW_TYPE_ERROR);
    return FLINT_FAILED;
}

/***********************
 *Class: QuerySubCommand
 **********************/

bool QuerySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "full")
    {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, _flintParams.cmd_params[0].c_str(), _name.c_str(), "full");
        return false;
    }
    return true;
}

bool QuerySubCommand::checkMac(u_int64_t mac, string& warrStr) {
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

bool QuerySubCommand::reportBxGuidsQuery(const guid_t* guids, int base1, int guids_num, int index, const char* pre_str)
{
    int i, first_index, base, wwnns_index;

    printf("G%d %-14s", index, pre_str);
    first_index = index * BX_SLICE_GUIDS;
    if (base1 == BI_WWPNS) {
        wwnns_index = first_index + (BX_SLICE_GUIDS - 1);
        printf(GUID_FORMAT " ", guids[wwnns_index].h, guids[wwnns_index].l);
    }
    base = first_index + base1;
    for (i = base; i < base + guids_num; i++) {
        int j = i;
        // HACK
        if (i == BI_GUIDS + BX_SLICE_GUIDS) {
            // We display the same node guid on the two slices.
            j = BI_GUIDS;
        }
        printf(GUID_FORMAT " ", guids[j].h, guids[j].l);
    }
    printf("\n");
    return true;
}


bool QuerySubCommand::reportBxMacsQuery(const guid_t* guids, int base1, int guids_num, int index, const char* pre_str)
{
    int i, base;

    base = index * BX_SLICE_GUIDS + base1;
    printf("G%d %-30s", index, pre_str);
    for (i = base; i < base + guids_num; i++) {
            printf("     " MAC_FORMAT , guids[i].h, guids[i].l);
    }
    printf("\n");
    return true;
}

bool QuerySubCommand::reportBxMacsWarnings(const guid_t* guids, int index, int warning, int user_uids)
{
    int i, base;
    int is_first = 1;
    base = index * BX_SLICE_GUIDS + BI_IMACS;
    for (i = base; i < base + BX_MACS; i++) {
         u_int64_t mac = (((u_int64_t)guids[i].h) << 32) | guids[i].l;
         string warrStr;
         if (!checkMac(mac, warrStr)) {
             if (warning) {
                 if (is_first) {
                     printf("\n\n");
                     is_first = 0;
                 }
                 printf(FLINT_BAD_MAC_ADRESS_WARNING, guids[i].h, guids[i].l, warrStr.c_str());
             } else {
                 printf(FLINT_BX_BAD_MAC_FORMAT_ERROR,
                        guids[i].h,
                        guids[i].l,
                        user_uids ? "given" : "found on flash");
                 return false;
             }
         }
     }
     return true;
}


bool QuerySubCommand::displayFs2Uids(const fw_info_t& fwInfo)
{
    const char* mac_indent = "";
    bool ibDev;
    bool ethDev;
    FwOperations::SetDevFlags(fwInfo.fw_info.chip_type, fwInfo.fw_info.dev_type, (fw_img_type)fwInfo.fw_type, ibDev, ethDev);
    //setDevFlags(fwInfo, ibDev, ethDev);
    int numPorts = 2;
    if ((fwInfo.fw_info.chip_type == CT_IS4) || (fwInfo.fw_info.chip_type == CT_SWITCHX)) {
        numPorts = 0;
    }
    //we do not support cards with one port anymore.

    // GUIDS:

    if (fwInfo.fw_info.chip_type == CT_BRIDGEX) {
        int i;
        if (fwInfo.fs2_info.guid_num != BX_ALL_GUIDS) {
            reportErr(true, FLINT_INVALID_UID_NUM_BX_ERROR, BX_ALL_GUIDS);
            return false;
        }
        printf("Description:     Node             Port1            Port2            Port3            Port4\n");
        for (i = 0; i < BX_SLICES_NUM; i++) {
            reportBxGuidsQuery(fwInfo.fs2_info.guids, BI_GUIDS,  BX_NP_GUIDS, i, "GUIDs:");
            reportBxMacsQuery(fwInfo.fs2_info.guids,  BI_IMACS, BX_IMACS,    i, "IMACs:");
            reportBxMacsQuery(fwInfo.fs2_info.guids,  BI_EMACS, BX_EMACS,    i, "EMACs:");
            reportBxGuidsQuery(fwInfo.fs2_info.guids, BI_WWPNS, BX_WWPNS,    i, "WWNs: ");
        }
        printf("SYS GUID:        " GUID_FORMAT " ",\
                fwInfo.fs2_info.guids[fwInfo.fs2_info.guid_num - 1].h,\
                fwInfo.fs2_info.guids[fwInfo.fs2_info.guid_num - 1].l);
        if (!fwInfo.fs2_info.blank_guids) {
            for (i = 0; i < BX_SLICES_NUM; i++) {
                reportBxMacsWarnings(fwInfo.fs2_info.guids, i, 1, 0);
            }
        }
    } else {
        if (ibDev) {
            //report("GUID Des:        Node             Port1            ");
            printf("Description:     Node             ");
            if (numPorts > 0)
                printf("Port1            ");
            if (numPorts > 1)
                printf("Port2            ");
            printf( "Sys image\n");

            printf("GUIDs:           ");
            for (u_int32_t i=0; i < GUIDS; i++) {
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
                    printf("Description:%s     Port1            Port2\n", mac_indent);
                } else if (fwInfo.fw_info.chip_type == CT_SWITCHX) {
                    printf("\nDescription:     Base             Switch\n");
                } else {
                    printf("\n");
                }
                printf("MACs:    %s       ", mac_indent);
                for (u_int32_t i=GUIDS; i < 6; i++) {
                    printf("     " MAC_FORMAT , fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l);
                }

                for (u_int32_t i=GUIDS; i < 6; i++) {
                    u_int64_t mac = (((u_int64_t)fwInfo.fs2_info.guids[i].h) << 32) | fwInfo.fs2_info.guids[i].l;
                    string warrStr;
                    if (!fwInfo.fs2_info.blank_guids && !checkMac(mac, warrStr)) {
                        if (i==GUIDS) printf("\n\n");
                        printf(FLINT_BAD_MAC_ADRESS_WARNING, fwInfo.fs2_info.guids[i].h, fwInfo.fs2_info.guids[i].l, warrStr.c_str());
                    }
                }
            } else {
                printf(FLINT_MAC_ENTRIES_WARNING, 6, fwInfo.fs2_info.guid_num);
            }
        }
    }
    printf("\n");
    return true;
}

#define BASE_STR "Base"
#define PRINT_FS3_UID(uid1, str) printf("%-16s %016"U64H_FMT_GEN"        %d        %d\n", str, uid1.uid, uid1.num_allocated, uid1.step);
#define PRINT_FS3_UIDS(uid1, uid2, str) {\
    	PRINT_FS3_UID(uid1, BASE_STR" "str":");\
    if (uid1.uid !=  uid2.uid || uid1.num_allocated != uid2.num_allocated  || uid1.step != uid2.step) {\
        PRINT_FS3_UID(uid2, "Orig " BASE_STR " "str":");\
    } \
}

bool QuerySubCommand::displayFs3Uids(const fw_info_t& fwInfo)
{
    printf("Description:     UID                GuidsNumber  Step\n");
    PRINT_FS3_UIDS(fwInfo.fs3_info.fs3_uids_info.guids[0], fwInfo.fs3_info.orig_fs3_uids_info.guids[0], "GUID1");
    PRINT_FS3_UIDS(fwInfo.fs3_info.fs3_uids_info.guids[1], fwInfo.fs3_info.orig_fs3_uids_info.guids[1], "GUID2");
    PRINT_FS3_UIDS(fwInfo.fs3_info.fs3_uids_info.macs[0], fwInfo.fs3_info.orig_fs3_uids_info.macs[0], "MAC1");
    PRINT_FS3_UIDS(fwInfo.fs3_info.fs3_uids_info.macs[1], fwInfo.fs3_info.orig_fs3_uids_info.macs[1], "MAC2");
    return true;
}



FlintStatus QuerySubCommand::printInfo(const fw_info_t& fwInfo, bool fullQuery)
{
    bool isFs2  = (fwInfo.fw_type == FIT_FS2) ? true : false;
    printf("Image type:      %s\n",(isFs2)? "FS2" : "FS3");

    if (fwInfo.fw_info.fw_ver[0] || fwInfo.fw_info.fw_ver[1] || fwInfo.fw_info.fw_ver[2]) {
        printf("FW Version:      %d.%d.%d\n", fwInfo.fw_info.fw_ver[0], fwInfo.fw_info.fw_ver[1],\
                fwInfo.fw_info.fw_ver[2]);
    }

    if (fwInfo.fw_info.fw_rel_date[0] || fwInfo.fw_info.fw_rel_date[1] || fwInfo.fw_info.fw_rel_date[2]) {
        printf("FW Release Date: %x.%x.%x\n", fwInfo.fw_info.fw_rel_date[0], fwInfo.fw_info.fw_rel_date[1],\
                fwInfo.fw_info.fw_rel_date[2]);
    }

    if (fullQuery) { // there is no full query atm just quick query
        if (fwInfo.fw_info.min_fit_ver[0] || fwInfo.fw_info.min_fit_ver[1]\
                || fwInfo.fw_info.min_fit_ver[2]||fwInfo.fw_info.min_fit_ver[3]) {
            printf("Min FIT Version: %d.%d.%d.%d\n", fwInfo.fw_info.min_fit_ver[0],\
                    fwInfo.fw_info.min_fit_ver[1], fwInfo.fw_info.min_fit_ver[2], fwInfo.fw_info.min_fit_ver[3]);
        }
        if ((fwInfo.fw_info.mic_ver[0] || fwInfo.fw_info.mic_ver[1] || fwInfo.fw_info.mic_ver[2])) {
            printf("MIC Version:     %d.%d.%d\n", fwInfo.fw_info.mic_ver[0],\
                    fwInfo.fw_info.mic_ver[1], fwInfo.fw_info.mic_ver[2]);
        }
        if (isFs2)
        {   if (fwInfo.fs2_info.config_sectors)
                printf("Config Sectors:  %d\n", fwInfo.fs2_info.config_sectors);
            if (fwInfo.fs2_info.config_pad) {
                    printf("Config Pad:      %d\n", fwInfo.fs2_info.config_pad);
        }

        }
    }

    if (strlen(fwInfo.fw_info.product_ver)) {
        printf("Product Version: %s\n", fwInfo.fw_info.product_ver);
    }

    if (fwInfo.fw_info.roms_info.exp_rom_found) {
        displayExpRomInfo(fwInfo.fw_info.roms_info, "Rom Info:        ");
    }

    if (isFs2)
    {
        printf("Device ID:       %d\n", fwInfo.fw_info.dev_type);
    }

    if (isFs2 && fwInfo.fs2_info.access_key_exists) {
        printf("HW Access Key:   ");
        if (fwInfo.fs2_info.access_key_value.l || fwInfo.fs2_info.access_key_value.h) {
            printf("Enabled\n");
        } else {
            printf("Disabled\n");
        }
    }

    if (!isFs2)/*i.e its fs3*/{
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
            printf("Image VSD:       %s\n", fwInfo.fs3_info.image_vsd);
            printf("Device VSD:      %s\n", fwInfo.fw_info.vsd);
            printf("PSID:            %s\n", fwInfo.fw_info.psid);
            if (strncmp(fwInfo.fw_info.psid, fwInfo.fs3_info.orig_psid, 13) != 0) {
                printf("Orig PSID:       %s\n", fwInfo.fs3_info.orig_psid);
            }
        } else {
            printf("VSD:             %s\n", fwInfo.fw_info.vsd);
            printf("PSID:            %s\n", fwInfo.fw_info.psid);
        }
    } else {
        printf(FLINT_NOT_MLNX_FW_WARNING, fwInfo.fw_info.vsd_vendor_id);
    }

    if (isFs2 && fwInfo.fs2_info.blank_guids) { //blankGuids only exsists in FS2 image type in mlxfwops why?
        printf(FLINT_BLANK_GUIDS_WARNING);
    }
    return FLINT_SUCCESS;
}

QuerySubCommand:: QuerySubCommand()
{
    _name = "query";
    _desc = "Query misc. flash/firmware characteristics, use \"full\"\n"
            INDENT"to get more information.";
    _extendedDesc = "Query miscellaneous FW and flash parameters \n"
                INDENTEX"Display FW Version, GUIDs, PSID, and other info";
    _flagLong = "query";
    _flagShort = "q";
    _param = "[full]";
    _paramExp = "None";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" query";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Query;
}

QuerySubCommand:: ~QuerySubCommand()
{

}

FlintStatus QuerySubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    fw_info_t fwInfo;
    FwOperations* ops;
    bool fullQuery = false;
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    if (!ops->FwQuery(&fwInfo, true, _flintParams.striped_image))
    {
        reportErr(true, FLINT_FAILED_QUERY_ERROR,_flintParams.device_specified? "Device" : "image",
                _flintParams.device_specified? _flintParams.device.c_str() : _flintParams.image.c_str(), ops->err());
        return FLINT_FAILED;
    }
    //print fw_info nicely to the user
    // we actually dont use "regular" query , just quick
    //ORENK - no use to display quick query message to the user if we dont do it in any other way
    if (_flintParams.cmd_params.size() == 1) {
        fullQuery=true;
    }
    return printInfo(fwInfo, fullQuery);
}

/***********************
 *Class: VerifySubCommand
 ***********************/
VerifySubCommand:: VerifySubCommand()
{
    _name = "verify";
    _desc = "Verify entire flash, use \"showitoc\" to see ITOC headers\n"
            INDENT"in FS3 image only.";
    _extendedDesc = "Verify entire flash.";
    _flagLong = "verify";
    _flagShort = "v";
    _param = "[showitoc]";
    _paramExp = "None";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" v";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Verify;
}

VerifySubCommand:: ~VerifySubCommand()
{

}

bool VerifySubCommand::verifyParams()
{

    if (_flintParams.cmd_params.size() > 1)
    {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str(), 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    if ((_flintParams.cmd_params.size() == 1) && _flintParams.cmd_params[0] != "showitoc")
    {
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
    FwOperations* ops;
    bool showItoc = (_flintParams.cmd_params.size() == 1) ? true : false;
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    if (!ops->FwVerify(&verifyCbFunc, _flintParams.striped_image, showItoc)) {
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
 *Class: SwResetSubCommand
 **********************/
SwResetSubCommand:: SwResetSubCommand() {
    _name = "swreset";
    _desc = "SW reset the target un-managed switch device. This command\n"
            INDENT"is supported only in the In-Band access method.";
    _extendedDesc = "SW reset the target un-managed switch device. This command\n"
                INDENTEX"is supported only in the In-Band access method.";
    _flagLong = "swreset";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = "None";
    _v = Wtv_Dev;
    _cmdType = SC_Swreset;
}

SwResetSubCommand:: ~SwResetSubCommand() {

}


bool SwResetSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() != 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 0, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus SwResetSubCommand::executeCommand()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    printf("-I- Resetting device %s ...\n", _flintParams.device.c_str());
            if (!_fwOps->FwSwReset()) {
                reportErr(true, FLINT_SWRESET_ERROR, _fwOps->err());
                return FLINT_FAILED;
            }
    return FLINT_SUCCESS;
}

/***********************
 *Class: BromSubCommand
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" brom exp-rom.rom";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Brom;
    memset(&_info, 0, sizeof(_info));
    memset(&_romsInfo, 0, sizeof(_romsInfo));
}

BromSubCommand:: ~BromSubCommand()
{
    closeLog();
    _fRom.close();
}

bool BromSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}


bool BromSubCommand::getExpRomStrVer(roms_info_t& roms_info, char* version) {
    if (roms_info.rom_info[0].exp_rom_product_id >= 0x10) {
        sprintf(version, "%d.%d.%d", roms_info.rom_info[0].exp_rom_ver[0], roms_info.rom_info[0].exp_rom_ver[1],
                roms_info.rom_info[0].exp_rom_ver[2]);
    } else {
        sprintf(version, "%d", roms_info.rom_info[0].exp_rom_ver[0]);
    }
    return true;
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
        printf("-W- Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n",\
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
        getExpRomStrVer(_info.fw_info.roms_info, romVer1);
    } else {
        printf("%s", infoStr);
        snprintf(romVer1, 50, "N/A");
        printf("%s\n", romVer1);
    }
    displayExpRomInfo(_romsInfo, infoStr2);
    getExpRomStrVer(_romsInfo, romVer2);
    //add new line to space up before showing burn precentage
    printf("\n");
    //print correct msg to log
    if (_info.fw_info.roms_info.num_of_exp_rom != 0) {
        print_line_to_log("Current ROM version on flash (1st ROM of %d): %s, New ROM version (1st ROM of %d): %s\n",\
                        _info.fw_info.roms_info.num_of_exp_rom, romVer1, _romsInfo.num_of_exp_rom, romVer2);
    } else {
        print_line_to_log("Current ROM version on flash: %s, New ROM version(1st ROM of %d): %s\n",romVer1, _romsInfo.num_of_exp_rom, romVer2);
    }
    // burn the rom
    printf("-I- Preparing to burn ROM ...\n");
    if (!ops->FwBurnRom(&_fRom, _flintParams.allow_rom_change, true, bromCbFunc)) {
            reportErr(true, FLINT_BROM_ERROR, ops->err());
            return FLINT_FAILED;
        }
    bromCbFunc(101);
    printf("\n");
    write_result_to_log(FLINT_SUCCESS, "", _flintParams.log_specified);
    return FLINT_SUCCESS;
}

/***********************
 *Class: Delete ROM
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" drom";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Drom;
}

DromSubCommand:: ~DromSubCommand()
{

}

bool DromSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 0) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 0, (int)_flintParams.cmd_params.size());
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
    if(!ops->FwDeleteRom(_flintParams.allow_rom_change, dromCbFunc)) {
        reportErr(true, FLINT_DROM_ERROR, ops->err());
        return FLINT_FAILED;
    }
    dromCbFunc(101);
    return FLINT_SUCCESS;
}
/***********************
 *Class: Read ROM
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" rrom exp-rom.rom";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Rrom;
}

RromSubCommand:: ~RromSubCommand()
{

}

bool RromSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    FILE * file;
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
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
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
 *Class:
 **********************/
BbSubCommand:: BbSubCommand()
{
    _name = "bb";
    _desc = "Burn Block - Burns the given image as is. No checks are done.";
    _extendedDesc = "Burns entire flash verbatim from raw binary image. No checks are done on the flash or\n"
                INDENTEX"on the given image file. No fields (such as VSD or Guids) are read from flash.";
    _flagLong = "bb";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" -i image1.bin bb";
    _v = Wtv_Dev_And_Img;
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
 *Class:
 **********************/
SgSubCommand:: SgSubCommand()
{
    _name = "sg";
    _desc = "Set GUIDs.";
    _extendedDesc = "Set GUIDs/MACs/UIDs in the given device/image.\n"
                INDENTEX"Use -guid(s), -mac(s) and -uid(s) flags to set the desired values.\n"
                INDENTEX"- On pre-ConnectX devices, the sg command  is used in production to apply GUIDs/MACs values\n"
                INDENTEX"to cards that were pre-burnt with blank GUIDs. It is not meant for\n"
                INDENTEX"use in field.\n"
                INDENTEX"- On 4th generation devices, this command can operate on both image file and image on flash.\n"
                INDENTEX"If the GUIDs/MACs/UIDs in the image on flash are non-blank,\n"
                INDENTEX"flint will re-burn the current image using the given GUIDs/MACs/UIDs.";
    _flagLong = "sg";
    _flagShort = "";
    _param = "[guids_num=<num> step_size=<size>] | [nocrc]";
    _paramExp = "nocrc: (optional) When specified the flint would not update\n"
                INDENTEX"the full image crc after changing the guids\n"
                INDENTEX"num_of_guids: number of GUIDs to be allocated per physical port (FS3 Only)\n"
                INDENTEX"step_size: step size between GUIDs (FS3 Only)";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" -guid 0x0002c9000100d050 sg";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Sg;
    _ops     = NULL;
    memset(&_info, 0, sizeof(_info));
    memset(&_sgParams, 0, sizeof(_sgParams));
}

SgSubCommand:: ~SgSubCommand()
{

}

bool SgSubCommand::verifyParams()
{
    if ((_flintParams.cmd_params.size() == 1 && _flintParams.cmd_params[0] != "nocrc")||\
            (_flintParams.cmd_params.size() == 2 && \
                    !extractUIDArgs(_flintParams.cmd_params, _sgParams.numOfGUIDs, _sgParams.stepSize))) {
        reportErr(true, "The sg parameter should be \"nocrc\", \"guids_num=<num> step_size=<size>\" or nothing\n");
        return false;
    }

    if (_flintParams.cmd_params.size()> 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2,_name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    if (!(_flintParams.guid_specified || _flintParams.guids_specified ||\
            _flintParams.uid_specified || _flintParams.uids_specified || \
            _flintParams.mac_specified || _flintParams.macs_specified)){
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "GUIDs / MACs (using command line flags -guid(s) / -mac(s) )");
        return false;
    }
    if ((_flintParams.guid_specified || _flintParams.guid_specified) && (_flintParams.uid_specified || _flintParams.uids_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either GUIDs / UIDs (using command line flags -guid(s) / -uid(s) )");
        return false;
    }
    if ((_flintParams.mac_specified || _flintParams.macs_specified) && (_flintParams.uid_specified || _flintParams.uids_specified)) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "either MACs / UIDs (using command line flags -mac(s) / -uid(s) )");
        return false;
    }
    if (_flintParams.guid_specified && _flintParams.guids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-guids", "-guid" );
        return false;
    }
    if (_flintParams.mac_specified && _flintParams.macs_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-macs", "-mac" );
        return false;
    }
    if (_flintParams.uid_specified && _flintParams.uids_specified) {
        reportErr(true, FLINT_INVALID_FLAG_WITH_FLAG_ERROR, "-uids", "-uid" );
        return false;
    }

    _sgParams.guidsSpecified = _flintParams.guid_specified || _flintParams.guids_specified;
    _sgParams.macsSpecified = _flintParams.mac_specified || _flintParams.macs_specified;
    _sgParams.uidsSpecified = _flintParams.uid_specified || _flintParams.uids_specified;
    _sgParams.updateCrc = !(_flintParams.cmd_params.size() == 1);
    _sgParams.stripedImage = _flintParams.striped_image;

    return true;
}

void SgSubCommand::setUserGuidsAndMacs()
{
    // _sgParams.userGuids contains either guids and macs (or just guids) or just uids
    // we are required to specifiy to mlxfwops a guid vector of MAX_GUIDS size regardless if user gives only guids
    // or only macs or uids
    if ( _sgParams.guidsSpecified) {

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
    if (_sgParams.uidsSpecified) {
        _sgParams.userGuids = _flintParams.user_uids;
    }
    _sgParams.userGuids.resize(MAX_GUIDS);
}

bool SgSubCommand::CheckSetGuidsFlags()
{
    bool ibDev;
    bool ethDev;
    bool bxDev = _info.fw_info.chip_type == CT_BRIDGEX;
    FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev, ethDev);
    //setDevFlags(_info, ibDev,ethDev);

    if (_sgParams.macsSpecified || _sgParams.guidsSpecified || _sgParams.uidsSpecified) {
        if (!checkGuidsFlags((chip_type_t)_info.fw_info.chip_type, _info.fw_info.dev_type,_info.fw_type,\
                _sgParams.guidsSpecified, _sgParams.macsSpecified, _sgParams.uidsSpecified)) {
            return false;
        }
    } else {
        printf("-E- ");
        printMissingGuidErr(ibDev, ethDev, bxDev);
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

    if (!CheckSetGuidsFlags()){
        return FLINT_FAILED;
    }

    if (_flintParams.image_specified || !_info.fs2_info.blank_guids) {
        //report guid changes
        bool ethDev;
        bool ibDev;
        bool bxDev = _info.fw_info.chip_type == CT_BRIDGEX;
        FwOperations::SetDevFlags(_info.fw_info.chip_type, _info.fw_info.dev_type, (fw_img_type)_info.fw_type, ibDev, ethDev);
        //setDevFlags(_info, ibDev, ethDev);
        //decide what are our new guids/macs
        guid_t *new_guids = (_sgParams.guidsSpecified ||_sgParams.uidsSpecified) ? & _sgParams.userGuids[0] : &_info.fs2_info.guids[0] ;
        guid_t *new_macs =  _sgParams.macsSpecified ? &_sgParams.userGuids[GUIDS] : &_info.fs2_info.guids[GUIDS] ;

        if (!reportGuidChanges(new_guids, new_macs, &_info.fs2_info.guids[0], &_info.fs2_info.guids[GUIDS], ibDev,\
                ethDev, bxDev, _info.fs2_info.guid_num)){
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

FlintStatus SgSubCommand::sgFs3()
{
    if ( _flintParams.uid_specified) {
        // for connectib we just need the base guid so we put it in the first location.
        _sgParams.userGuids.resize(1);
        _sgParams.userGuids[0]= _flintParams.baseUid;
        if (!_ops->FwSetGuids(_sgParams, &verifyCbFunc)) {
            reportErr(true, FLINT_SG_UID_ERROR, _ops->err());
            return FLINT_FAILED;
        }
    } else {
        reportErr(true, "Can not set GUIDs/MACs: uid is not specified, please run with -uid flag.\n");
        return FLINT_FAILED;
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
 *Class: Set Manufacture GUIDs
 *****************************/
SmgSubCommand:: SmgSubCommand()
{
    _name = "smg";
    _desc = "Set manufacture GUIDs (For FS3 image only).";
    _extendedDesc = "Set manufacture GUID, Set manufacture GUIDs in the given FS3 image.\n"
                INDENTEX"Use -uid flag to set the desired GUIDs, intended for production use only.";
    _flagLong = "smg";
    _flagShort = "";
    _param = "[guids_num=<num> step_size=<size>]";
    _paramExp = "guids_num: number of GUIDs to be allocated per physical port\n"
                INDENTEX"step_size: step size between GUIDs";
    _example = FLINT_NAME" -i fw_image.bin -uid 0x0002c9000100d050 smg"
#ifndef __WIN__
    		"\n"INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE3" -uid 0x0002c9000100d050 smg (should be used when device is idle)"
#endif
    		;
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Smg;
    memset(&_baseGuid, 0, sizeof(_baseGuid));
}

SmgSubCommand:: ~SmgSubCommand()
{

}

bool SmgSubCommand::verifyParams()
{
    if (!_flintParams.uid_specified) {
        reportErr(true, FLINT_COMMAND_FLAGS_ERROR, _name.c_str(), "\"-uid\" flag");
        return false;
    }
    if (_flintParams.uids_specified) {
        reportErr(true, FLINT_INVALID_OPTION_ERROR, "\"-uids\"", _name.c_str(), "\"-uid\"");
        return false;
    }

    if (_flintParams.cmd_params.size() != 0 && _flintParams.cmd_params.size() != 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR4, _name.c_str(), 0, 2, _flintParams.cmd_params.size());
        return false;
    }

    if (_flintParams.cmd_params.size() == 2 &&\
        !extractUIDArgs(_flintParams.cmd_params, _baseGuid.num_of_guids, _baseGuid.step_size)) {
        return false;
    }
    _baseGuid.uid = _flintParams.baseUid;
    //printf("-D-"GUID_FORMAT"\n", _baseGuid.h, _baseGuid.l);
    return true;
}

FlintStatus SmgSubCommand::executeCommand()
{
    if (preFwOps()) {
        return FLINT_FAILED;
    }
    FwOperations *ops = _flintParams.device_specified ? _fwOps : _imgOps;
    //TODO: dispaly MFG guid changes
    bool ret;
    if (_flintParams.cmd_params.size() == 2) {
        ret = ops->FwSetMFG(_baseGuid, &verifyCbFunc);
    } else {
        ret = ops->FwSetMFG(_baseGuid.uid, &verifyCbFunc);
    }
    if (!ret) {
        reportErr(true, FLINT_MFG_ERROR, ops->err());
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 *Class: Set Vpd Subcommand
 **********************/
SetVpdSubCommand:: SetVpdSubCommand()
{
    _name = "set vpd";
    _desc = "Set read-only VPD (For FS3 image only).";
    _extendedDesc = "Set Read-only VPD, Set VPD in the given FS3 image, intended for production use only.";
    _flagLong = "set_vpd";
    _flagShort = "";
    _param = "[vpd file]";
    _paramExp = "vpd file: bin file containing the vpd data";
    _example = FLINT_NAME" -i fw_image.bin set_vpd vpd.bin"
#ifndef __WIN__
    			"\n"INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE3" -override_cache_replacement set_vpd vpd.bin (should be used when device is idle)"
#endif
    			;
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Set_Vpd;
}

SetVpdSubCommand:: ~SetVpdSubCommand()
{

}

bool SetVpdSubCommand:: verifyParams()
{
    if( _flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
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
 *Class: Set VSD
 **********************/
SvSubCommand:: SvSubCommand()
{
    _name = "sv";
    _desc = "Set the VSD.";
    _extendedDesc = "Set VSD in the given device/image.\n"
                INDENTEX"Use -vsd flag to set the desired VSD string.";
    _flagLong = "sv";
    _flagShort = "";
    _param = "";
    _paramExp = "None";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" -vsd VSD_STRING sv"
#ifndef __WIN__
    		"\n"INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE3" -vsd VSD_STRING -override_cache_replacement sv (should be used when device is idle)\n"
#endif
    		;
    _v = Wtv_Dev_Or_Img;
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
    FwOperations* ops = _flintParams.device_specified ? _fwOps : _imgOps;
    if (!ops->FwSetVSD((char*)_flintParams.vsd.c_str(), &vsdCbFunc, &verifyCbFunc)) {
        reportErr(true, FLINT_VSD_ERROR, ops->err());
        return FLINT_FAILED;
    }
    vsdCbFunc(101);
    return FLINT_SUCCESS;
}



/*******************************
 *Class: Read Image SubCommand
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" ri file.bin";
    _v = Wtv_Dev;
    _cmdType = SC_Ri;
}

RiSubCommand:: ~RiSubCommand()
{

}

bool RiSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus RiSubCommand::executeCommand() {
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    // Check if we have permission to write to file
    FILE* fh;
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
    if (!_fwOps->FwReadData((void*)(&imgBuff[0]),&imgSize)) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    return writeImageToFile(_flintParams.cmd_params[0].c_str(), &(imgBuff[0]), imgSize );
}

FlintStatus RiSubCommand::writeImageToFile(const char *file_name, u_int8_t *data, u_int32_t length)
{
    FILE* fh;
    if ((fh = fopen(file_name, "wb")) == NULL) {
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

/***********************
 *Class: Dump Conf SubCommand
 **********************/
DcSubCommand:: DcSubCommand() {
    _name = "dc";
    _desc = "Dump Configuration: print fw configuration file for the given image.";
    _extendedDesc = "Print (to screen or to a file) the FW configuration text file used by the image generation process.\n"
                INDENTEX"This command would fail if the image does not contain a FW configuration section. Existence of this\n"
                INDENTEX"section depends on the version of the image generation tool.";
    _flagLong = "dc";
    _flagShort = "";
    _param = "[out-file]";
    _paramExp = "file: (optional) filename to write the dumped configuration to. If not given, the data\n"
                INDENTEX"is printed to screen";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" dc";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Dc;
}

DcSubCommand:: ~DcSubCommand() {

}

bool DcSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DcSubCommand::executeCommand() {
    FwOperations* ops;
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char* file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*) NULL;
    if (!ops->FwGetSection(H_FW_CONF, _sect, _flintParams.striped_image)) {
        reportErr(true, FLINT_DUMP_ERROR, "Fw Configuration", ops->err());
        return FLINT_FAILED;
    }
    if (!dumpFile(file, _sect, "Fw Configuration")) {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/***********************
 *Class:Dump Hash SubCommand
 **********************/
DhSubCommand:: DhSubCommand()
{
    _name = "dh";
    _desc = "Dump Hash: dump the hash if it is integrated in the FW image";
    _extendedDesc = "Print (to screen or to a file) the HASH text file used by the FW.\n"
                INDENTEX"This command would fail if the image does not contain a Hash file.";
    _flagLong = "dh";
    _flagShort = "";
    _param = "[out-file]";
    _paramExp = "file - (optional) filename to write the dumped tracer hash file to. If not given, the data\n"
                INDENTEX"is printed to screen";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" dh hash.csv";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Dh;
}

DhSubCommand:: ~DhSubCommand()
{

}

bool DhSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() > 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    return true;
}

FlintStatus DhSubCommand::executeCommand() {
    FwOperations* ops;
    //init fw operation object
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    //check on what we are wroking
    ops = (_flintParams.device_specified) ? _fwOps : _imgOps;
    const char* file = _flintParams.cmd_params.size() == 1 ? _flintParams.cmd_params[0].c_str() : (const char*) NULL;
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
 *Class:Set Key SubCommand
 **********************/
SetKeySubCommand:: SetKeySubCommand()
{
    _name = "set_key";
    _desc = "Set/Update the HW access key which is used to enable/disable access to HW.\n"
            INDENT"The key can be provided in the command line or interactively typed after\n"
            INDENT"the command is given\n"
            INDENT"NOTE: The new key is activated only after the device is reset.";
    _extendedDesc = "Set/Update the HW access key which is used to enable/disable access to HW.";
    _flagLong = "set_key";
    _flagShort = "";
    _param = "[key]";
    _paramExp = "key: (optional) The new key you intend to set (in hex).";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" set_key 1234deaf5678";
    _v = Wtv_Dev;
    _cmdType = SC_Set_Key;
    _getKeyInter = false;
    memset(&_userKey, 0, sizeof(_userKey));
}

SetKeySubCommand:: ~SetKeySubCommand()
{

}

bool SetKeySubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() > 1 ) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    _getKeyInter = (_flintParams.cmd_params.size() == 0);
    return true;
}

bool SetKeySubCommand::getKeyInteractively()
{
    char keyArr[MAX_PASSWORD_LEN+1];
    getPasswordFromUser("Enter Key ", keyArr );
    if (!getGUIDFromStr(keyArr, _userKey,\
                       "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
    return false;
    }
    // verify key
    hw_key_t verKey;
    getPasswordFromUser("Verify Key ", keyArr );
    if (!getGUIDFromStr(keyArr, verKey,\
                       "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
    return false;
    }
    if (_userKey.h != verKey.h || _userKey.l != verKey.l) {
        reportErr(true, FLINT_SET_KEY_ERROR, "The keys you entered did not match.");
        return false;
    }
    return true;
}

FlintStatus SetKeySubCommand::executeCommand ()
{
    if (preFwOps() == FLINT_FAILED) {
        return FLINT_FAILED;
    }

#ifdef __WN__
    reportErr(true, FLINT_WIN_NOT_SUPP_ERROR, _name);
    return FLINT_FAILED;
#endif

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
    if (!_fwOps->FwSetAccessKey(_userKey, &setKeyCbFunc)) {
        reportErr(true, FLINT_SET_KEY_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    setKeyCbFunc(101);
    printf("\n-I- New key was updated successfully in the flash. "\
            "In order to activate the new key you should reboot or restart the driver.\n");

    return FLINT_SUCCESS;
}

/***********************
 *Class:HwAccess SubCommand
 **********************/
HwAccessSubCommand:: HwAccessSubCommand()
{
    _name = "hw_access";
    _desc = "Enable/disable the access to the HW.\n"
            INDENT"The key can be provided in the command line or interactively typed after\n"
            INDENT"the command is given";
    _extendedDesc = "Enable/disable the access to the HW.";
    _flagLong = "hw_access";
    _flagShort = "";
    _param = "<enable|disable> [key]";
    _paramExp = "<enable/disable>: Specify if you intend to disable or enable the HW access.\n"
                INDENTEX"                   You will be asked to type a key when you try to enable HW access.\n"
                INDENTEX"key:               (optional) The key you intend to use for enabling the HW access.\n"
    			INDENTEX"                   Key format consists of at most 16 Hexadecimal digits.";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" hw_access enable";
    _v = Wtv_Dev;
    _cmdType = SC_Hw_Access;
}

HwAccessSubCommand:: ~HwAccessSubCommand()
{

}

bool HwAccessSubCommand::verifyParams()
{
    if (_flintParams.cmd_params.size() == 0) {
        reportErr(true, FLINT_MISSED_ARG_ERROR,"<disable/enable>",_name.c_str());
        return false;
    }
    if (_flintParams.cmd_params.size() > 2) {
        reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 2, (int)_flintParams.cmd_params.size());
        return false;
    }
    if( _flintParams.cmd_params[0] != "enable" && _flintParams.cmd_params[0] != "disable") {
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
        if (!((Flash*)_io)->disable_hw_access()) {
            printf(FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
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
             if (!getGUIDFromStr(_flintParams.cmd_params[1], keyStruct,\
                     "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
                 return FLINT_FAILED;
             }
        } else {//we need to get the key from user during runtime
            char keyArr[MAX_PASSWORD_LEN+1];
            getPasswordFromUser("Enter Key ", keyArr );
            if (!getGUIDFromStr(keyArr, keyStruct,\
                    "Invalid Key syntax, it should contain only hexa numbers and of appropriate length.")) {
                return FLINT_FAILED;
            }
        }
        key = ((u_int64_t)keyStruct.h << 32) | keyStruct.l;
        if (!((Flash*)_io)->enable_hw_access(key)) {
            reportErr(true, FLINT_GEN_COMMAND_ERROR, _name.c_str(), _io->err());
            return FLINT_FAILED;
        }
    }
    return FLINT_SUCCESS;
}

FlintStatus HwAccessSubCommand:: executeCommand()
{
#ifdef __WIN__
    reportErr(true, FLINT_WIN_NOT_SUPP_ERROR, _name.c_str());
    return FLINT_FAILED;
#endif
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
 *Class: Hw SubCommand
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
       INDENTEX"set [ATTR=VAL]: set flash attribure\n"
       INDENTEX"Supported attributes:\n"
       INDENTEX"    QuadEn: can be 0 or 1\n"
       INDENTEX"    DummyCycles: can be [1..15]\n"
       INDENTEX"    Flash[0|1|2|3].WriteProtected can be:\n"
       INDENTEX"        <Top|Bottom>,<1|2|4|8|16|32|64>-<Sectors|SubSectors>";
    _example = "flint -d "MST_DEV_EXAMPLE1" hw query\n"
            INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE1" hw set QuadEn=1\n"
            INDENTEX FLINT_NAME" -d "MST_DEV_EXAMPLE1" hw set Flash1.WriteProtected=Top,1-SubSectors";
#else
    _name = "Hw";
    _desc = "Query HW info and flash attributes.";
    _extendedDesc = "Query HW info and flash attributes.";
    _flagLong = "hw";
    _flagShort = "";
    _param = "query";
    _paramExp = "query";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" hw query";
#endif
    _v = Wtv_Dev;
    _cmdType = SC_Hw;
}

HwSubCommand:: ~HwSubCommand()
{

}

bool HwSubCommand::verifyParams() {
#ifdef EXTERNAL
     if (_flintParams.cmd_params.size() != 1) {
         reportErr(true, FLINT_CMD_ARGS_ERROR2, _name.c_str(), 1, (int)_flintParams.cmd_params.size());
         return false;
     }

     if (_flintParams.cmd_params[0] != "query"){
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
         reportErr(true, FLINT_CMD_ARGS_ERROR, _name.c_str(),2 , (int)_flintParams.cmd_params.size());
         return false;
     }
#endif

     return true;
}

FlintStatus HwSubCommand::printAttr(const ext_flash_attr_t& attr) {
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
    printf("  SectorSize            0x%x\n",   attr.sector_size );
    printf("  WriteBlockSize        0x%x\n",   attr.block_write);
    printf("  CmdSet                0x%x\n",   attr.command_set);

    // Quad EN query
    if (attr.quad_en_support) {
        switch (attr.mf_get_quad_en_rc) {
            case MFE_OK:
                printf("  "QUAD_EN_PARAM"                %d\n", attr.quad_en);
                break;
            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the "QUAD_EN_PARAM" attribute between the flashes attached to the device\n");
                break;
            case MFE_NOT_SUPPORTED_OPERATION:
                break;
            default:
                printf("Failed to get "QUAD_EN_PARAM" attribute: %s (%s)",\
                        errno == 0 ? "" : strerror(errno), mf_err2str(attr.mf_get_quad_en_rc));
                return FLINT_FAILED;
        }
    }
    // Dummy Cycles query
    if (attr.dummy_cycles_support) {
        switch (attr.mf_get_dummy_cycles_rc) {
            case MFE_OK:
                printf("  "DUMMY_CYCLES_PARAM"           %d\n", attr.dummy_cycles);
                break;
            case MFE_MISMATCH_PARAM:
                printf("-E- There is a mismatch in the "DUMMY_CYCLES_PARAM" attribute between the flashes attached to the device\n");
                break;
            case MFE_NOT_SUPPORTED_OPERATION:
                break;
            default:
                printf("Failed to get "DUMMY_CYCLES_PARAM" attribute: %s (%s)",\
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
                printf("  "FLASH_NAME"%d."WRITE_PROTECT"   ", bank);
                if (protect_info.sectors_num != 0) {
                    printf("%s,", (protect_info.is_bottom ? WP_BOTTOM_STR : WP_TOP_STR));
                    printf("%d-", protect_info.sectors_num);
                    printf("%s\n", (protect_info.is_subsector ? WP_SUBSEC_STR : WP_SEC_STR));
                } else {
                    printf(WP_DISABLED_STR"\n");
                }
            } else {
                if (rc != MFE_NOT_SUPPORTED_OPERATION) { // We ignore the read when operation is not supported!
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
        char* cmdParam = strcpy(new char[_flintParams.cmd_params[1].size() + 1],
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
 *Class: Erase SubCommand
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" erase 0x10000";
    _v = Wtv_Dev;
    _cmdType = SC_Erase;
}

EraseSubCommand:: ~EraseSubCommand()
{

}

bool EraseSubCommand::verifyParams() {
    if (_flintParams.cmd_params.size() != 1) {
        reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 1, (int)_flintParams.cmd_params.size());
        return false;
    }
    //parameter format will be checked in executeCommand.
    return true;
}

FlintStatus EraseSubCommand::executeCommand() {
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    u_int32_t   addr;
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
 *Class: Read Dword SubCommand
 *****************************/
RwSubCommand:: RwSubCommand() {
    _name = "rw";
    _desc = "Read one dword from flash";
    _extendedDesc = "Read one dword from flash.";
    _flagLong = "rw";
    _flagShort = "";
    _param = "<addr>";
    _paramExp = "addr - address of word to read";
    _example = "flint -d "MST_DEV_EXAMPLE1" rw 0x20";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Rw;
}

RwSubCommand:: ~RwSubCommand() {

}

bool RwSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() != 1) {
            reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 1, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

FlintStatus RwSubCommand::executeCommand() {
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
    if (_flintParams.device_specified ? !((Flash*)_io)->read(addr, &data)\
            : !((FImage*)_io)->read(addr, &data)) {
        reportErr(true, FLINT_FLASH_READ_ERROR, _io->err());
        return FLINT_FAILED;
        }
    printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));
    return FLINT_SUCCESS;
}

/******************************
 *Class: Write Dword Subcommand
 ******************************/
WwSubCommand:: WwSubCommand()
{
    _name = "ww";
    _desc = "Write one dword to flash";
    _extendedDesc = "Write one dword to flash.\n"
                INDENTEX"Note that the utility will read an entire flash sector,\n"
                INDENTEX"modify one word and write the sector back. This may take\n"
                INDENTEX"a few seconds.";
    _flagLong = "ww";
    _flagShort = "";
    _param = "<addr> <data>";
    _paramExp = "addr - address of word\n"
                INDENTEX"data - value of word";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" ww 0x10008 0x5a445a44";
    _v = Wtv_Dev;
    _cmdType = SC_Ww;
}

WwSubCommand:: ~WwSubCommand()
{

}

bool WwSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() != 2) {
            reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 2, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

FlintStatus WwSubCommand::executeCommand() {
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
    data =strtoul(dataStr, &endp, 0);
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
 *Class: Write Dword No Erase SubCommand
 ***************************************/
WwneSubCommand:: WwneSubCommand()
{
    _name = "wwne";
    _desc = "Write one dword to flash without sector erase";
    _extendedDesc = "Write one dword to flash without sector erase.\n"
                INDENTEX"Note that the result of operation is undefined and depends\n"
                INDENTEX"on flash type. Usually \"bitwise AND\" (&) between specified\n"
                INDENTEX"word and previous flash contents will be written to\n"
                INDENTEX"specified address.";
    _flagLong = "wwne";
    _flagShort = "";
    _param = "<addr> <data>";
    _paramExp = "addr - address of word\n"
                INDENTEX"data - value of word";
    _example = "flint -d "MST_DEV_EXAMPLE1" wwne 0x10008 0x5a445a44";
    _v = Wtv_Dev;
    _cmdType = SC_Wwne;
}

WwneSubCommand:: ~WwneSubCommand()
{

}

bool WwneSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() != 2) {
            reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 2, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

FlintStatus WwneSubCommand::executeCommand() {
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
    data =strtoul(dataStr, &endp, 0);
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
 *Class:Write Block  SubCommand
 **************************************/
WbSubCommand:: WbSubCommand() {
    _name = "wb";
    _desc = "Write a data block to flash.";
    _extendedDesc = "Write a block of data to the flash.";
    _flagLong = "wb";
    _flagShort = "";
    _param = "<data-file> <addr>";
    _paramExp = "data-file - file that contains the data to be written\n"
                INDENTEX"addr - address to write the block to\n";

    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" wb myData.bin 0x0";
    _v = Wtv_Dev;
    _cmdType = SC_Wb;
}

WbSubCommand:: ~WbSubCommand() {

}

bool WbSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() != 2) {
            reportErr(true, FLINT_CMD_ARGS_ERROR,_name.c_str() , 2, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

bool WbSubCommand::extractData(const std::vector<string>& cmdParams , u_int32_t* addr, std::vector<u_int8_t>& data) {
    // get address
    char *endp;
    char* addrStr = strcpy(new char[cmdParams[1].size() + 1],cmdParams[1].c_str());
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
    memcpy(&data[0], img.getBuf(), img.getBufLength());

    return true;
}

FlintStatus WbSubCommand::executeCommand() {
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
 *Class:Write Block No Erase SubCommand
 **************************************/
WbneSubCommand:: WbneSubCommand() {
    _name = "wbne";
    _desc = "Write a data block to flash without sector erase.";
    _extendedDesc = "Write a block of data to the flash without erasing.";
    _flagLong = "wbne";
    _flagShort = "";
    _param = "<addr> <size> <data ...>";
    _paramExp = "addr - address of block\n"
                INDENTEX"size - size of data to write in bytes\n"
                INDENTEX"data - data to write - space seperated dwords";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" wbne 0x10000 12 0x30000 0x76800 0x5a445a44";
    _v = Wtv_Dev;
    _cmdType = SC_Wbne;
}

WbneSubCommand:: ~WbneSubCommand() {

}

bool WbneSubCommand::writeBlock(u_int32_t addr, std::vector<u_int32_t> dataVec) {
    //we should work only on flash.
    //check if flash is big enough
    if (addr + (dataVec.size()*4) > ((Flash*)_io)->get_size()) {
       reportErr(true, "Writing %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                            (unsigned int)(dataVec.size()*4), (unsigned int)addr, (unsigned int)_io->get_size());
       return false;
    }
    if (!((Flash*)_io)->write(addr, &dataVec[0], (dataVec.size()*4), true)) {
        reportErr(true, FLINT_FLASH_WRITE_ERROR,_io->err());
        return false;
    }
    return true;
}

bool WbneSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() < 3) {
            reportErr(true, FLINT_CMD_ARGS_ERROR3,_name.c_str() , 3, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

bool WbneSubCommand::extractData(const std::vector<string>& cmdParams , u_int32_t* addr, std::vector<u_int32_t>& data) {
    char *endp;
    char* addrStr = strcpy(new char[cmdParams[0].size() + 1],cmdParams[0].c_str());
    *addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, cmdParams[0].c_str());
        delete[] addrStr;
        return false;
    }
    delete[] addrStr;
    char* sizeStr = strcpy(new char[cmdParams[1].size() + 1],cmdParams[1].c_str());
    u_int32_t size = strtoul(sizeStr, &endp, 0);
    if (*endp || size % 4 || size/4 != (cmdParams.size()-2)) {
                    reportErr(true, FLINT_INVALID_SIZE_ERROR, sizeStr);
                    delete[] sizeStr;
                    return false;
                }
    delete[] sizeStr;
    for (u_int32_t i = 2; i < cmdParams.size(); i++) {
        char* dataStr = strcpy(new char[cmdParams[i].size() + 1],cmdParams[i].c_str());
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

FlintStatus WbneSubCommand::executeCommand() {
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
 *Class: ReadBlock
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
                INDENTEX"size - size of data to read in bytes\n"
                INDENTEX"file - filename to write the block (raw binary). If not given, the data\n"
                INDENTEX"is printed to screen";
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" rb 0x10000 100 file.bin";
    _v = Wtv_Dev_Or_Img;
    _cmdType = SC_Rb;
}

RbSubCommand:: ~RbSubCommand()
{

}

bool RbSubCommand::readBlock(u_int32_t addr, std::vector<u_int8_t>& buff, bool isFlash) {
    //check if flash is big enough
    if (addr + buff.size() > _io->get_size()) {
        reportErr(true, "Reading %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                            (unsigned int)(buff.size()), (unsigned int)addr, (unsigned int)_io->get_size());
        return false;
    }
    //read from flash/image
    if (isFlash ? !((Flash*)_io)->read(addr, &buff[0], buff.size()) :\
            !((FImage*)_io)->read(addr, &buff[0], buff.size())) {
        reportErr(true, FLINT_IMAGE_READ_ERROR, _io->err());
        return false;
    }
    return true;
}

bool RbSubCommand::verifyParams() {
        if (_flintParams.cmd_params.size() < 2) {
            reportErr(true, FLINT_CMD_ARGS_ERROR3,_name.c_str() , 2, (int)_flintParams.cmd_params.size());
            return false;
        }
    return true;
}

bool RbSubCommand::printToScreen(const std::vector<u_int8_t>& buff) {
    for (u_int32_t i=0; i < buff.size(); i+=4) {
        u_int32_t word = *((u_int32_t*)(&buff[0] + i));
        word  = __be32_to_cpu(word);
        printf("0x%08x ", word);
    }
    printf("\n");
    return true;
}

FlintStatus RbSubCommand::executeCommand() {
       //init fw operation object
    if (preFwAccess() == FLINT_FAILED) {
        return FLINT_FAILED;
    }
    bool wTF = _flintParams.cmd_params.size() == 3 ? true : false;
    //extract address and size to read from cmdline
    u_int32_t addr;
    u_int32_t size;
    char *endp;
    char* addrStr = strcpy(new char[_flintParams.cmd_params[0].size() + 1],_flintParams.cmd_params[0].c_str());
    addr = strtoul(addrStr, &endp, 0);
    if (*endp) {
        reportErr(true, FLINT_INVALID_ADDR_ERROR, _flintParams.cmd_params[0].c_str());
        delete[] addrStr;
        return FLINT_FAILED;
    }
    delete[] addrStr;
    char* sizeStr = strcpy(new char[_flintParams.cmd_params[1].size() + 1],_flintParams.cmd_params[1].c_str());
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
        rc = writeToFile(_flintParams.cmd_params[2], data) == true ? FLINT_SUCCESS : FLINT_FAILED ;
    } else {
        rc = printToScreen(data) == true ? FLINT_SUCCESS : FLINT_FAILED ;
    }
    return rc;
}

/***********************
 *Class: ClearSemaphore
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" -clear_semaphore";
    _v = Wtv_Dev;
    _cmdType = SC_Clear_Sem;
}

ClearSemSubCommand:: ~ClearSemSubCommand()
{

}

FlintStatus ClearSemSubCommand::executeCommand()
{
    return preFwAccess();
}


/***********************
 *Class: RomQuery
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
    _example = FLINT_NAME" -i ROM_image.bin qrom ";
    _v = Wtv_Img;
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
    if (_romsInfo.exp_rom_err_msg_valid != 0){
        reportErr(true, FLINT_ROM_QUERY_ERROR, _flintParams.image.c_str(), _romsInfo.exp_rom_err_msg);
        return FLINT_FAILED;
    }
    displayExpRomInfo(_romsInfo , "Rom Info: ");
    return FLINT_SUCCESS;

}

/***********************
 *Class: ResetCfg
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" reset_cfg";
    _v = Wtv_Dev;
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
    if (!_fwOps->FwResetNvData()){
    	printf(" Failed!\n");
        reportErr(true, FLINT_RESET_CFG_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf(" SUCCESS!\n");
    printf("\n-I- Configuration were successfully reset. reboot or restart the driver is required.\n");

    return FLINT_SUCCESS;

}

/***********************
 *Class: FixImage
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
    _example = FLINT_NAME" -d "MST_DEV_EXAMPLE1" fi";
    _v = Wtv_Dev;
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

    if (!_fwOps->FwShiftDevData(&verifyCbFunc)){
        reportErr(true, FLINT_FIX_IMG_ERROR, _fwOps->err());
        return FLINT_FAILED;
    }
    printf("\n-I- Fw was successfully fixed. reboot or restart the driver is required.\n");
    return FLINT_SUCCESS;

}
