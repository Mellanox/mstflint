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
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>

#include <tools_dev_types.h>

#include "mlxcfg_ui.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_generic_commander.h"

#define NEXT_STR "Next Boot"
#define DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "Device Firmware does not support reading "
#define TLV_NAME_MAX_LENGTH 256
#define EXIT_IF_RC_NOT_OK(rc) \
    if (rc != MLX_CFG_OK) {\
        return rc;\
    }

#define PRINT_SYNTAX_ERROR_AND_EXIT \
    printf("-E- Syntax error in: %s\n", line->c_str());\
    return MLX_CFG_ERROR;

typedef struct reg_access_hca_mqis_reg mqisReg;
#define MAX_REG_DATA 128

// Signal handler section
void TerminationHandler(int signum);

#ifdef __WIN__
#include <windows.h>

static BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch( fdwCtrlType )
    {
      // Handle the CTRL-C signal.
      case CTRL_C_EVENT:
      // CTRL-CLOSE: confirm that the user wants to exit.
      case CTRL_CLOSE_EVENT:
      // Pass other signals to the next handler.
      case CTRL_BREAK_EVENT:
      case CTRL_LOGOFF_EVENT:
      case CTRL_SHUTDOWN_EVENT:
          TerminationHandler(SIGINT);
          return TRUE;

      default:
        return FALSE;
    }
 }

#endif

void TerminationHandler(int signum)
{
    static volatile sig_atomic_t fatal_error_in_progress = 0;

    if (fatal_error_in_progress) {
        raise (signum);
    }
    fatal_error_in_progress = 1;

    signal (signum, SIG_DFL);
    printf("\n Received signal %d.\n", signum);
    fflush(stdout);
    raise(signum);
}


void initHandler()
{
#ifdef __WIN__
#define SIGNAL_NUM 3
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGABRT};
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, true );
#else
#define SIGNAL_NUM 4
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGPIPE, SIGHUP};
#endif

    //set the signal handler
    for (int i=0; i < SIGNAL_NUM ; i++) {
        void (*prevFunc)(int);
        prevFunc = signal(signalList[i],TerminationHandler);
        if (prevFunc == SIG_ERR) {
            printf("-E- failed to set signal Handler.");
            exit(MLX_CFG_ERROR);
        }
    }
}

//End of signal handler section.


#define MAX_ERR_STR_LEN 1024
#define MAX_BUF_SIZE 1024
#define PRE_ERR_MSG "-E-"
#define MLNX_RAW_TLV_FILE_SIG "MLNX_RAW_TLV_FILE"

#ifdef MST_UL
    #define NO_DEV_ERR "No devices found."
#else
    #define NO_DEV_ERR "No devices found, mst might be stopped. You may need to run 'mst start' to load MST modules. "
#endif

typedef struct QueryOutputItem {
    string mlxconfigName;
    u_int32_t nextVal;
    string strNextVal;
    u_int32_t currVal;
    string strCurrVal;
    u_int32_t defVal;
    string strDefVal;
    u_int32_t setVal;
    string strSetVal;
} QueryOutputItem;

inline void copyVal(QueryOutputItem&o , const ParamView& p, QueryType qT)
{
    if (qT == QueryDefault) {
        o.defVal = p.val;
        o.strDefVal = p.strVal;
    } else if (qT == QueryCurrent) {
        o.currVal = p.val;
        o.strCurrVal = p.strVal;
    } else if (qT == QueryNext) {
        o.nextVal = p.val;
        o.strNextVal = p.strVal;
    }
}

inline void copySet(QueryOutputItem&o , const ParamView& p)
{
    o.setVal = p.val;
    o.strSetVal = p.strVal;
}

mlxCfgStatus MlxCfg::err(bool report, const char* fmt, ...)
{
     va_list  args;
     va_start(args, fmt);
     char errBuff[MAX_ERR_STR_LEN] = {0};

     if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN) {
         strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
     _errStr = errBuff;
     if (report) {
         fprintf(stdout,PRE_ERR_MSG" %s\n", _errStr.c_str());
     }
     va_end(args);
     return MLX_CFG_ERROR;
}

void MlxCfg::printErr()
{
    fprintf(stdout,PRE_ERR_MSG" %s\n", _errStr.c_str());
}


bool MlxCfg::askUser(const char* question)
{
if (question == NULL) {
     printf("\n Do you want to continue ? (y/n) [n] : ");
 } else {
     printf("\n %s ? (y/n) [n] : ", question);
 }

 if (_mlxParams.yes)
     printf("y\n");
 else {
     fflush(stdout);
     std::string answer;
     std::getline(std::cin, answer);

     if (  strcasecmp(answer.c_str(), "y") &&
           strcasecmp(answer.c_str(), "yes"))  {

         err(false, "Aborted by user.");
         return false;
     }
 }
 return true;
}

mlxCfgStatus MlxCfg::queryDevsCfg()
{
    bool shouldFail= false;
    if (_mlxParams.device.length()) {

        if (queryDevCfg(_mlxParams.device.c_str())) {
            printErr();
            shouldFail= true;
        }
    } else {
        int  numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        //printf("-D- num of dev: %d , 1st dev : %s\n", numOfDev, buf);
        dev_info  *devPtr = dev;
        char pcibuf[32]= {0};

        for(int i=0 ; i < numOfDev ; i++) {
#ifdef __FREEBSD__
            const char* device_name_ptrn = "pci%d:%d:%d:%d";
#else
            const char* device_name_ptrn = "%04x:%02x:%02x.%x";
#endif
            snprintf(pcibuf,32, device_name_ptrn, devPtr->pci.domain, devPtr->pci.bus,\
                    devPtr->pci.dev, devPtr->pci.func);
            if (queryDevCfg(devPtr->pci.conf_dev, pcibuf, i+1)){
                printErr();
                shouldFail = true;
            }
            devPtr++;
        }
        mdevices_info_destroy(dev, numOfDev);
    }
    return shouldFail? MLX_CFG_ERROR : MLX_CFG_OK;
}

static void printValue(string strVal, u_int32_t val)
{
    string s = numToStr(val);
    u_int32_t n;
    if(strVal == "" || strVal == s || (strToNum(strVal, n) && n == val)) {
        printf("%-16u", val);
    } else {
        if (strVal.find("Array") == string::npos) {
            strVal += "(" + s + ")";
        }
        printf("%-16s", strVal.c_str());
    }
}

static void printParam(string param, u_int32_t val)
{
    if (val == MLXCFG_UNKNOWN) {
            printf("%-16s", "N/A");
        } else {
            printValue(param, val); 
        }
    return;
}

static void printOneParam(const char* name, QueryOutputItem o,
        u_int8_t verbose, bool printNewCfg)
{
    bool showDefault = QUERY_DEFAULT_MASK & verbose;
    bool showCurrent = QUERY_CURRENT_MASK & verbose;

    if ((showDefault && o.nextVal != o.defVal) ||
            (showCurrent && o.nextVal != o.currVal)) {
        printf("*        %-36s", name);
    } else {
        printf("         %-36s", name);
    }
    if (showDefault) {
        printParam(o.strDefVal, o.defVal);
    }
    if (showCurrent) {
        printParam(o.strCurrVal, o.currVal);
    }
    printParam(o.strNextVal, o.nextVal);

    if (printNewCfg) {
        if (o.setVal == MLXCFG_UNKNOWN) {
            printParam(o.strNextVal, o.nextVal);
        } else {
            printValue(o.strSetVal, o.setVal);
        }
    }
    printf("\n");
    return;

}

const char* MlxCfg::getDeviceName(const char* dev)
{
    mfile* mf;
    u_int32_t chip_rev;
    u_int32_t _dev_id;
    _devType = DeviceUnknown;

    mf = mopen(dev);
    if (!mf) {
        return "";
    }
    if (dm_get_device_id(mf, &_devType, &_dev_id, &chip_rev)) {
        mclose(mf);
        return "";
    }
    mclose(mf);
    return dm_dev_type2str(_devType);
}

bool MlxCfg::getDeviceDescription(const char* dev, MlxCfg::deviceDescription op, vector<char>& infoString)
{
    mqisReg mqisRegister;
    mfile* mf;
    mf = mopen(dev);
    if (!mf) {
       return false;
    }
    reg_access_status_t rc;
    int maxDataSize = mget_max_reg_size(mf) - sizeof(mqisRegister);
    if (maxDataSize > MAX_REG_DATA) {
        maxDataSize = sizeof(mqisRegister);
    }
    std::vector<u_int32_t> dataVector(maxDataSize / 4, 0);

    memset(&mqisRegister, 0, sizeof(mqisReg));
    if (op == Device_Name){
       mqisRegister.info_type = 0x1;
    } else if (op == Device_Description_info) {
       mqisRegister.info_type = 0x2;
    }
    mqisRegister.read_length = maxDataSize;
    mqisRegister.info_string = dataVector.data();

    rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
    if (rc) {
       mclose(mf);
       return false;
    }
    int infoSize = mqisRegister.info_length;
    infoString.resize(infoSize+1, 0);
    if (mqisRegister.info_length > maxDataSize) {
        dataVector.resize((infoSize + 3) / 4);
        int leftSize = infoSize - maxDataSize;
        while (leftSize > 0) {
            mqisRegister.read_offset = infoSize - leftSize;
            mqisRegister.read_length = leftSize > maxDataSize ? maxDataSize : leftSize;
            mqisRegister.info_string = dataVector.data() + (mqisRegister.read_offset / 4);

            rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
            if (rc) {
               mclose(mf);
               return false;
            }
            leftSize = leftSize - maxDataSize;
        }
    }

    memcpy(infoString.data(), dataVector.data(), infoSize);
    mclose(mf);
    string str = string (infoString.data());
    if (str.length() == 0) {
        return false;
    }
    return true;
}

void MlxCfg::printOpening(const char* dev, int devIndex)
{
    printf("\nDevice #%d:\n", devIndex);
    printf("----------\n\n");
    const char * devType = getDeviceName(dev);
    printf("%-16s%-16s\n", "Device type:", devType);
    if ((_devType != DeviceConnectX3 && _devType != DeviceConnectX3Pro && _devType != DeviceConnectX2))
    {
        std::vector<char> info;
        info.reserve(16);
        if (! getDeviceDescription(dev, Device_Name, info)) {
            printf("%-16s%-16s\n", "Name:", "N/A");
        } else {
            printf("%-16s%-16s\n", "Name:", info.data());
        }
        info.clear();
        if (! getDeviceDescription(dev, Device_Description_info, info)) {
            printf("%-16s%-16s\n", "Description:", "N/A");
        } else {
            printf("%-16s%-16s\n", "Description:", info.data());
        }
    }
    printf("%-16s%-16s\n", "Device:", dev);
}

void MlxCfg::printConfHeader(bool showDefualt, bool showNew, bool showCurrent)
{
    //print configuration Header
    if (showDefualt) {
        if (showCurrent) {
            printf("%-16s%36s%16s%18s","Configurations:","Default","Current",
                    NEXT_STR);
        } else {
            printf("%-16s%36s%18s","Configurations:","Default", NEXT_STR);
        }
    } else {
        if (showCurrent) {
            printf("%-16s%36s%18s","Configurations:","Current", NEXT_STR);
        } else {
            printf("%-16s%38s","Configurations:", NEXT_STR);
        }
    }
    if (showNew) {
        printf("       %s", "New");
    }
}

void prepareSetInput(vector<QueryOutputItem>& output,
        vector<ParamView>& params)
{
    VECTOR_ITERATOR(ParamView, params, p) {
        QueryOutputItem o;
        o.mlxconfigName = p->mlxconfigName;
        o.defVal = MLXCFG_UNKNOWN;
        o.currVal = MLXCFG_UNKNOWN;
        o.nextVal = MLXCFG_UNKNOWN;
        copySet(o, *p);
        output.push_back(o);
    }
}

void prepareQueryOutput(vector<QueryOutputItem>& output,
        vector<ParamView>& params, QueryType qT)
{
    VECTOR_ITERATOR(ParamView, params, p) {
        bool found = false;
        VECTOR_ITERATOR(QueryOutputItem, output, o) {
            if (p->mlxconfigName == o->mlxconfigName) {
                copyVal(*o, *p, qT);
                found = true;
                break;
            }
        }
        if(!found) {
            QueryOutputItem o;
            o.mlxconfigName = p->mlxconfigName;
            o.defVal = MLXCFG_UNKNOWN;
            o.currVal = MLXCFG_UNKNOWN;
            o.nextVal = MLXCFG_UNKNOWN;
            o.setVal = MLXCFG_UNKNOWN;
            copyVal(o, *p, qT);
            output.push_back(o);
        }
    }
}

void queryAux(Commander* commander, vector<ParamView>& params,
        vector<ParamView>& paramsToQuery, QueryType qT)
{
    if (paramsToQuery.size() != 0) {
        params = paramsToQuery;
        commander->queryParamViews(params, qT);
    } else {
        commander->queryAll(params, qT);
    }
}

mlxCfgStatus MlxCfg::queryDevCfg(Commander* commander, const char* dev,const char* pci,
        int devIndex, bool printNewCfg)
{
    (void) pci;
    std::vector<QueryOutputItem> output;
    std::vector<ParamView> params, defaultParams, currentParams;
    bool failedToGetCfg = false, isParamsDiffer = false;
    bool defaultSupported = false, currentSupported = false;
    bool showDefault = false, showCurrent = false;

    printOpening(dev, devIndex);
    printf("\n");

    try {

        if (_mlxParams.enableVerbosity) {
            if (commander->isDefaultSupported()) {
                defaultSupported = true;
            }
            if (commander->isCurrentSupported()) {
                currentSupported = true;
            }
        }

        showDefault = defaultSupported;
        showCurrent = currentSupported;

        printConfHeader(showDefault, printNewCfg, showCurrent);
        printf("\n");

        if (printNewCfg) {
            VECTOR_ITERATOR(ParamView, _mlxParams.setParams, p) {
                commander->updateParamViewValue(*p, p->setVal);
            }
            prepareSetInput(output, _mlxParams.setParams);
        }

        if (showDefault) {
            queryAux(commander, defaultParams, _mlxParams.setParams, QueryDefault);
        }
        if (showCurrent) {
            queryAux(commander, currentParams, _mlxParams.setParams, QueryCurrent);
        }
        queryAux(commander, params, _mlxParams.setParams, QueryNext);
    } catch (MlxcfgException& e) {
        err(false, "%s", e._err.c_str());
        return MLX_CFG_ERROR_EXIT;
    }

    if (showDefault) {
        prepareQueryOutput(output, defaultParams, QueryDefault);
    }
    if (showCurrent) {
        prepareQueryOutput(output, currentParams, QueryCurrent);
    }
    prepareQueryOutput(output, params, QueryNext);
    
    //print output table:
    VECTOR_ITERATOR(QueryOutputItem, output, o) {
        printOneParam(o->mlxconfigName.c_str(),
                *o,
                QUERY_NEXT_MASK |
                    (showDefault ? QUERY_DEFAULT_MASK :0) |
                    (showCurrent ? QUERY_CURRENT_MASK : 0),
                printNewCfg);
        isParamsDiffer |= (showDefault && (o->nextVal != o->defVal))
                || (showCurrent && (o->nextVal != o->currVal));
    }

    if (isParamsDiffer) {
        printf("The '*' shows parameters with next value different "
                "from default/current value.\n");
    }

    if (_mlxParams.enableVerbosity) {
        if (!defaultSupported && !currentSupported) {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX
                    "default and current configurations\n");
        } else if (!defaultSupported) {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX
                    "default configurations\n");
        } else if (!currentSupported) {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX
                    "current configurations\n");
        }
    }

    if (params.size() == 0) {
        err(false, "Device doesn't support any configuration changes.");
        return MLX_CFG_ERROR_EXIT;
    }

    return failedToGetCfg ? MLX_CFG_ERROR : MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::queryDevCfg(const char* dev,const char* pci,
        int devIndex, bool printNewCfg)
{
    mlxCfgStatus rc;
    Commander* commander = NULL;
    try {
        commander = Commander::create(string(dev), _mlxParams.dbName);
    } catch (MlxcfgException& e) {
        delete commander;
        return err(false, "%s", e._err.c_str());
    }

    rc = queryDevCfg(commander, dev, pci, devIndex, printNewCfg);
    delete commander;
    return rc;
}

mlxCfgStatus MlxCfg::setDevCfg()
{
    Commander* commander = NULL;

    try {
        commander = Commander::create(string(_mlxParams.device),
                _mlxParams.dbName);
    } catch (MlxcfgException& e) {
        delete commander;
        err(false, "%s", e._err.c_str());
        printErr();
        return MLX_CFG_ERROR;
    }

    if (queryDevCfg(commander, _mlxParams.device.c_str(), NULL, 1, true)
            == MLX_CFG_ERROR_EXIT){
        delete commander;
        printErr();
        return MLX_CFG_ERROR;
    }

    // even if there is problem fetching the current cfg we will attempt to write the new info
    // if the user agrees

    if (_mlxParams.force) {
        printf("\n-W- Force flag specified, the validity of the Parameters will not be checked !\n");
        printf("-W- Incorrect configuration might yield unexpected results. running in this mode is not recommended.");
    }
    // ask user
    if(!askUser("Apply new Configuration?")) {
        delete commander;
        printErr();
        return MLX_CFG_ABORTED;
    }

    try {
        printf("Applying... ");
        commander->setCfg(_mlxParams.setParams, _mlxParams.force);
        printf("Done!\n");
        const char* resetStr = commander->loadConfigurationGetStr();
        printf("-I- %s\n", resetStr);
        delete commander;
        return MLX_CFG_OK;
    } catch (MlxcfgException& e) {
        delete commander;
        printf("Failed!\n");
        err(true, "%s", e._err.c_str());
        return MLX_CFG_ERROR;
    }
}

mlxCfgStatus MlxCfg::resetDevsCfg()
{
    // check if a single device was specified and apply reset for this device only
    if (_mlxParams.device.length()) {
        char buff[256] = {0};
        snprintf(buff,256,"Reset configuration for device %s? ", _mlxParams.device.c_str());
        if (!askUser(buff)){
            printErr();
            return MLX_CFG_ABORTED;
        }

        printf("Applying... ");
        if (resetDevCfg(_mlxParams.device.c_str())) {
            printf("Failed!\n");
            printErr();
            return MLX_CFG_ERROR;
        }
    } else {
        // reset all devices.
        int  numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        if (!askUser("Reset configuration for all devices? ")){
            printErr();
            mdevices_info_destroy(dev, numOfDev);
            return MLX_CFG_ABORTED;
        }
        printf("Applying... ");

        dev_info *devPtr = dev;
        bool shouldFail= false;

        for(int i=0 ; i < numOfDev ; i++) {
            if (resetDevCfg(devPtr->pci.conf_dev)){
                shouldFail = true;
            }
            devPtr++;

        }
        mdevices_info_destroy(dev, numOfDev);
        if (shouldFail) {
            printf("Failed!\n");
            return MLX_CFG_ERROR;
        }

    }
    // done successfully
    printf("Done!\n");
    printf("-I- Please reboot machine to load new configurations.\n");
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::clrDevSem()
{
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    printf("-W- Forcefully clearing device Semaphore...\n");
    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        commander->clearSemaphore();
    } catch(MlxcfgException& e){
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if(commander != NULL) {
        delete commander;
    }

    if(rc == MLX_CFG_OK) {
        printf(" Done!\n");
    } else {
        printf(" Failed!\n");
    }

    return rc;
}

mlxCfgStatus MlxCfg::setDevRawCfg()
{
    Commander* commander = NULL;
    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        // open file
        std::ifstream ifs(_mlxParams.rawTlvFile.c_str());
        if (ifs.fail()) {
            delete commander;
            return err(true, "Failed to open file: %s", _mlxParams.rawTlvFile.c_str());
        }
        std::vector<std::vector<u_int32_t> > rawTlvsAsDw;
        rawTlvsAsDw.resize(0);
        // Check file Sig
        std::string startLine;
        std::getline(ifs, startLine);
        if (startLine != MLNX_RAW_TLV_FILE_SIG) {
            delete commander;
            return err(true, "Invalid raw TLV file header.");
        }
        // parse the rest of the Lines
        int lineIdx = 1;
        for (std::string line; std::getline(ifs, line); lineIdx++) {
            std::vector<u_int32_t> rawTlvVec;
            if (line.empty() || line[0] == '%') { // comment - skip
                continue;
            }
            // convert line to DW
            if (tlvLine2DwVec(line, rawTlvVec)) {
                delete commander;
                return err(true, "Failed to parse Raw TLV at line %d: %s", lineIdx, _errStr.c_str());
            }
            rawTlvsAsDw.push_back(rawTlvVec);
        }
        // dump raw TLVs from the file
        std::string dumpStr;
        int tlvIdx = 1;
        for (std::vector<std::vector<u_int32_t> >::iterator it = rawTlvsAsDw.begin(); it != rawTlvsAsDw.end(); it++, tlvIdx++) {
            commander->dumpRawCfg(*it, dumpStr);
            printf("Raw TLV #%d Info:\n%s\n", tlvIdx, dumpStr.c_str());
        }
        // ask user
        if(!askUser("Operation intended for advanced users.\n Are you sure you want to apply raw TLV file?")) {
            printErr();
            delete commander;
            return MLX_CFG_ABORTED;
        }
        printf("Applying... ");
        // set each of the raw TLVs
        tlvIdx = 1;
        for (std::vector<std::vector<u_int32_t> >::iterator it = rawTlvsAsDw.begin(); it != rawTlvsAsDw.end(); it++, tlvIdx++) {
            commander->setRawCfg(*it);
        }
    } catch(MlxcfgException& e) {
        delete commander;
        return err(true, "Failed to run set_raw command: %s", e._err.c_str());
    }
    if (commander != NULL) {
        delete commander;
    }
    // done successfully
    printf("Done!\n");
    printf("-I- Please reboot machine to load new configurations.\n");
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::backupCfg()
{
    FILE * file;
    Commander* commander = NULL;
    vector<BackupView> views;

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("Collecting...\n");
        commander->backupCfgs(views);
        delete commander;
    } catch(MlxcfgException& e) {
        printf(" Failed!\n");
        if(commander) {
            delete commander;
        }
        return err(true, "Failed to backup the configurations: %s", e._err.c_str());
    }

    //check if views empty
    if (views.empty()) {
        printf("No TLVs were found.\n");
    } else {
        // open file
        printf("Saving output...\n");
        file = fopen(_mlxParams.rawTlvFile.c_str(), "w");
        if (file == NULL) {
            return err(true, "Failed to open file: %s", _mlxParams.rawTlvFile.c_str());
        }

        fprintf(file, "%s\n", MLNX_RAW_TLV_FILE_SIG);

        for(std::vector<BackupView>::iterator it = views.begin();
                it != views.end(); it++) {
            fprintf(file, "%% TLV Type: 0x%08x, Writer ID: %s(0x%02x)"
                    ", Writer Host ID: 0x%02x\n",
                    it->type,
                    writerIdToStr((WriterId)(it->writerId)).c_str(),
                    it->writerId,
                    it->writerHostId);
            vector<u_int8_t> v = it->tlvBin;
            for(size_t i = 0; i < v.size() / 4; i++) {
                fprintf(file, "0x%08x ", __cpu_to_be32(((u_int32_t*)v.data())[i]));
            }
            fprintf(file, "\n");
        }

        fclose(file);

        printf("Done!\n");
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::tlvLine2DwVec(const std::string& tlvStringLine, std::vector<u_int32_t>& tlvVec) {
    tlvVec.resize(0);
    std::string dwStr;
    u_int32_t dw;
    char* p = NULL;
    std::istringstream isstm(tlvStringLine);
    while (isstm >> dwStr) {
        dw = strtoul(dwStr.c_str(), &p, 0);
        if (*p) {
            return err(false, "Input is not an unsigned number: %s", dwStr.c_str());
        }
        tlvVec.push_back(dw);
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::resetDevCfg(const char* dev)
{
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    try {
        commander = Commander::create(dev, _mlxParams.dbName);
        commander->invalidateCfgs();
        commander->loadConfigurationGetStr(); //why to call this? seems needless
    } catch (MlxcfgException& e) {
        err(false, "%s", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if(commander) {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::showDevConfs()
{
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("\nList of configurations the device %s may support:\n", _mlxParams.device.c_str());
        commander->printLongDesc(stdout);
    } catch (MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if(commander) {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::readBinFile(string fileName, vector<u_int32_t>& buff)
{
    streampos size;

    std::ifstream ifs(fileName.c_str(),
            ios::in|ios::binary|ios::ate);
    if (ifs.fail()) {
        return err(true, "Failed to open file: %s", fileName.c_str());
    }
    size = ifs.tellg();
    if (size%4 != 0) {
        return err(true, "File %s is not DW aligned", fileName.c_str());
    }
    buff.resize((size_t)size / 4);
    ifs.seekg(0, ios::beg);
    ifs.read((char*)buff.data(), size);
    ifs.close();
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::readNVInputFile(vector<u_int32_t>& buff)
{
    return readBinFile(_mlxParams.NVInputFile, buff);
}

mlxCfgStatus MlxCfg::readNVInputFile(vector<string>& lines)
{
    std::ifstream ifs(_mlxParams.NVInputFile.c_str());
    if (ifs.fail()) {
        return err(true, "Failed to open file: %s",
                _mlxParams.NVInputFile.c_str());
    }
    for (std::string line; std::getline(ifs, line);) {
        lines.push_back(line);
    }
    return MLX_CFG_OK;
}


mlxCfgStatus MlxCfg::readNVInputFile(string& content)
{
    vector<string> lines;
    mlxCfgStatus rc = readNVInputFile(lines);
    if (rc != MLX_CFG_OK) {
        return rc;
    }

    VECTOR_ITERATOR(string, lines, l) {
        content += *l;
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(vector<u_int32_t> content)
{
    FILE* file = fopen(_mlxParams.NVOutputFile.c_str(), "wb");
    if (!file) {
        return err(true, "Failed to open file: %s",
                _mlxParams.NVOutputFile.c_str());
    }
    for (u_int32_t i = 0 ; i < content.size() * 4; i += 4) {
        size_t cnt = fwrite(((u_int8_t*)content.data()) + i ,1 , 4 , file);
        (void)cnt; // avoid annoying unused return code/ unused variable in certain compilers
        if (ferror(file)) {
            fclose(file);
            return err(true, "Write failed: %s.", strerror(errno));
        }
    }
    fclose(file);
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(string content)
{
    FILE* file = fopen(_mlxParams.NVOutputFile.c_str(), "w");
    if (!file) {
        return err(true, "Failed to open file: %s",
                _mlxParams.NVOutputFile.c_str());
    }
    fprintf(file, "%s", content.c_str());
    fclose(file);
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(vector<string> lines)
{
    string content;
    VECTOR_ITERATOR(string, lines, l) {
        content += *l;
    }
    return writeNVOutputFile(content);
}

mlxCfgStatus MlxCfg::genTLVsFile()
{
    char buff[TLV_NAME_MAX_LENGTH];
    vector<string> tlvs;
    mlxCfgStatus rc = MLX_CFG_OK;

    try {
        GenericCommander commander(NULL, _mlxParams.dbName);
        commander.genTLVsList(tlvs);
        VECTOR_ITERATOR(string, tlvs, it) {
            sprintf(buff, "%-50s0\n", it->c_str());
            (*it) = buff;
        }
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK) {
        printf("Saving output...\n");
        rc = writeNVOutputFile(tlvs);
        if (rc == MLX_CFG_OK) {
            printf("Done!\n");
        }
    }

    return rc;
}

mlxCfgStatus MlxCfg::genXMLTemplate()
{
    string xmlTemplate;
    vector<string> lines, tlvs;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(lines);
    EXIT_IF_RC_NOT_OK(rc)

    VECTOR_ITERATOR(string, lines, line) {
        string tlvName;
        string tLine = mlxcfg_trim(*line);
        for(unsigned i = 0; i < tLine.size(); i++) {
            if (tLine[i] != ' ' && tLine[i] != '\t') {
                tlvName += tLine[i];
            } else {
                while ((tLine[i] == ' ' || tLine[i] == '\t')
                        && (++i < tLine.size())) { };
                if ((i == tLine.size()) ||
                        (tLine[i] != '0' && tLine[i] != '1') ||
                        (i != tLine.size() - 1) ||
                        tlvName.empty()) {
                    PRINT_SYNTAX_ERROR_AND_EXIT
                }
                if (tLine[i] == '1') {
                    tlvs.push_back(tlvName);
                }
                break;
            }
        }
        if (tlvName == tLine) {
            PRINT_SYNTAX_ERROR_AND_EXIT
        }
    }

    if (tlvs.size() == 0) {
        printf("-E- Empty TLV configurations file was provided or no TLV configurations were selected.\n");
        return MLX_CFG_ERROR;
    }

    try {
        GenericCommander commander(NULL, _mlxParams.dbName);
        commander.genXMLTemplate(tlvs, xmlTemplate, _mlxParams.allAttrs);
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK) {
        printf("Saving output...\n");
        rc = writeNVOutputFile(xmlTemplate);
        if (rc == MLX_CFG_OK) {
            printf("Done!\n");
        }
    }

    return rc;
}


mlxCfgStatus MlxCfg::raw2XMLAux(bool isBin)
{
    string xmlTemplate;
    vector<string> lines;
    vector<u_int32_t> buff;
    mlxCfgStatus rc = MLX_CFG_OK;

    if (isBin) {
        rc = readNVInputFile(buff);
    } else {
        rc = readNVInputFile(lines);
    }
    EXIT_IF_RC_NOT_OK(rc)

    try {
        GenericCommander commander(NULL, _mlxParams.dbName);
        if (isBin) {
            //commander.bin2XML(buff, xmlTemplate);
        } else {
            if (lines.size() == 0) {
                fprintf(stderr, "-E- Empty file was provided\n");
                rc = MLX_CFG_ERROR;
            } else {
                commander.raw2XML(lines, xmlTemplate);
            }
        }
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK) {
        printf("Saving output...\n");
        rc = writeNVOutputFile(xmlTemplate);
        if (rc == MLX_CFG_OK) {
            printf("Done!\n");
        }
    }

    return rc;
}

mlxCfgStatus MlxCfg::raw2XML()
{
    return raw2XMLAux(false);
}

mlxCfgStatus MlxCfg::XML2RawAux(bool isBin)
{
    string xml, raw;
    vector<u_int32_t> binBuff;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(xml);
    EXIT_IF_RC_NOT_OK(rc)

    try {
        GenericCommander commander(NULL, _mlxParams.dbName);
        if (isBin) {
            commander.XML2Bin(xml, binBuff, false);
        } else {
            commander.XML2Raw(xml, raw);
        }
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK) {
        printf("Saving output...\n");
        if (isBin) {
            rc = writeNVOutputFile(binBuff);
        } else {
            rc = writeNVOutputFile(raw);
        }
        if (rc == MLX_CFG_OK) {
            printf("Done!\n");
        }
    }

    return rc;
}

mlxCfgStatus MlxCfg::XML2Raw()
{
    return XML2RawAux(false);
}

mlxCfgStatus MlxCfg::XML2Bin()
{
    return XML2RawAux(true);
}

mlxCfgStatus MlxCfg::createConf()
{
    string xml;
    vector<u_int32_t> buff;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(xml);
    EXIT_IF_RC_NOT_OK(rc)

    try {
        GenericCommander commander(NULL, _mlxParams.dbName);
        commander.createConf(xml, buff);
        if (!_mlxParams.privPemFile.empty() && !_mlxParams.keyPairUUID.empty()) {
            commander.sign(buff, _mlxParams.privPemFile, _mlxParams.keyPairUUID);
        } else {
            commander.sign(buff);
        }
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK) {
        printf("Saving output...\n");
        rc = writeNVOutputFile(buff);
        if (rc == MLX_CFG_OK) {
            printf("Done!\n");
        }
    }

    return rc;
}

mlxCfgStatus MlxCfg::apply()
{
    vector<u_int32_t> buff;
    vector<u_int8_t> bytesBuff;
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(buff);
    EXIT_IF_RC_NOT_OK(rc)

    copyDwVectorToBytesVector(buff, bytesBuff);

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("Applying...\n");
        ((GenericCommander*)commander)->apply(bytesBuff);
    } catch(MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander != NULL) {
        delete commander;
    }

    if (rc == MLX_CFG_OK) {
        printf("Done!\n");
    }

    return rc;
}

mlxCfgStatus MlxCfg::execute(int argc, char* argv[])
{
    mlxCfgStatus rc = parseArgs(argc, argv);
    if (rc) {
        if (rc == MLX_CFG_OK_EXIT) {
            rc = MLX_CFG_OK;
        } else {
            printUsage();
        }
        return rc;
    }
    //return test(_mlxParams.device.c_str());
    mlxCfgStatus ret;
    switch (_mlxParams.cmd) {
    case Mc_ShowConfs:
        ret = showDevConfs();
        break;
    case Mc_Query:
        ret = queryDevsCfg();
        break;
    case Mc_Set:
        ret = setDevCfg();
        break;
    case Mc_Reset:
        ret = resetDevsCfg();
        break;
    case Mc_Clr_Sem:
        ret = clrDevSem();
        break;
    case Mc_Set_Raw:
        ret = setDevRawCfg();
        break;
    case Mc_Backup:
        ret = backupCfg();
        break;
    case Mc_GenTLVsFile:
        ret = genTLVsFile();
        break;
    case Mc_GenXMLTemplate:
        ret = genXMLTemplate();
        break;
    case Mc_Raw2XML:
        ret = raw2XML();
        break;
    case Mc_XML2Raw:
        ret = XML2Raw();
        break;
    case Mc_XML2Bin:
        ret = XML2Bin();
        break;
    case Mc_CreateConf:
        ret = createConf();
        break;
    case Mc_Apply:
        ret = apply();
        break;
    default:
        // should not reach here.
        return err(true, "invalid command.");
    }
    return ret;
}

int main(int argc, char* argv[])
{
    try
    {
    initHandler();
    MlxCfg mc;
    return mc.execute(argc, argv);
    }
    catch (std::exception& e)
    {
        printf("-E- %s\n", e.what());
        return MLX_CFG_ERROR;
    }
}

