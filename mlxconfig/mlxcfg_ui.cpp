/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <time.h>

#include <tools_dev_types.h>
#include <reg_access/reg_access.h>
#include <mft_sig_handler.h>

#include "mlxcfg_ui.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_generic_commander.h"

#define DISABLE_SLOT_POWER_LIMITER  "DISABLE_SLOT_POWER_LIMITER"
#define DISABLE_SLOT_POWER_LIMITER_WARN \
    "\nWARNING: YOU ARE ABOUT TO RE-ENABLE ONE OR MORE NETWORK PORTS THAT HAVE BEEN SHUT DOWN DUE TO INSUFFICIENT POWER ON THE PCIE SLOT."\
    "\nYOUR ACTION MAY RISK PROPER FUNCTIONAL OR PHYSICAL OPERATION OF THE CARD OR OF THE SERVER."\
    "\nMELLANOX TECHNOLOGIES HEREBY DISCLAIMS ANY AND ALL LIABILITY RELATED TO ANY DAMAGE CAUSED AS A RESULT OF THIS RE-ENABLEMENT."\
    "\nBY PROCEEDING WITH THIS RE-ENABLEMENT YOU WILL INVALIDATE ANY WARRANTY PROVIDED BY MELLANOX TECHNOLOGIES RELATED TO THIS CARD."\
    "\nIT IS ADVISED TO CHECK THE CARD\'S USER MANUAL FOR POWER SPECIFICATIONS OR TO CONTACT MELLANOX SUPPORT BEFORE PERFORMING THIS ACTION."\
    "\nARE YOU SURE YOU WANT TO CONTINUE? [Y/N] [N]: "


#define NEXT_STR "Next Boot"
#define DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "Device Firmware does not support reading "
#define TLV_NAME_MAX_LENGTH 256
#define EXIT_IF_RC_NOT_OK(rc) \
    if (rc != MLX_CFG_OK) { \
        return rc; \
    }

#define PRINT_SYNTAX_ERROR_AND_EXIT \
    printf("-E- Syntax error in: %s\n", line->c_str()); \
    return MLX_CFG_ERROR;

// Signal handler section
void TerminationHandler(int signum);

#ifdef __WIN__
#include <windows.h>

static BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch (fdwCtrlType)
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
        raise(signum);
    }
    fatal_error_in_progress = 1;

    signal(signum, SIG_DFL);
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
    for (int i = 0; i < SIGNAL_NUM; i++) {
        void (*prevFunc)(int);
        prevFunc = signal(signalList[i], TerminationHandler);
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


inline void copyVal(QueryOutputItem&o, const ParamView& p, QueryType qT)
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

inline void copySet(QueryOutputItem&o, const ParamView& p)
{
    o.setVal = p.val;
    o.strSetVal = p.strVal;
}

mlxCfgStatus MlxCfg::err(bool report, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char errBuff[MAX_ERR_STR_LEN] = {0};

    if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN) {
        strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
    _errStr = errBuff;
    if (report) {
        fprintf(stdout, PRE_ERR_MSG " %s\n", _errStr.c_str());
    }
    va_end(args);
    return MLX_CFG_ERROR;
}

void MlxCfg::printErr()
{
    fprintf(stdout, PRE_ERR_MSG " %s\n", _errStr.c_str());
}


bool MlxCfg::askUser(const char *question, bool add_prefix, bool add_suffix)
{
    const char * prefix = "";
    if(add_prefix){
        prefix = "\n ";
    }

    const char * suffix = "";
    if(add_suffix) {
        suffix = " (y/n) [n] : ";
    }
    if (question == NULL) {
        question = "Do you want to continue?";
    }
    printf("%s%s%s", prefix, question, suffix);

    if (_mlxParams.yes) {
        printf("y\n");
    } else {
        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);

        if (strcasecmp(answer.c_str(), "y") &&
            strcasecmp(answer.c_str(), "yes")) {

            err(false, "Aborted by user.");
            return false;
        }
    }
    return true;
}

mlxCfgStatus MlxCfg::queryDevsCfg()
{
    bool shouldFail = false;
    if (_mlxParams.device.length()) {
        if (queryDevCfg(_mlxParams.device.c_str())) {
            printErr();
            shouldFail = true;
        }
    } else {
        int numOfDev;
        dev_info *dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        //printf("-D- num of dev: %d , 1st dev : %s\n", numOfDev, buf);
        dev_info  *devPtr = dev;
        char pcibuf[32] = {0};

        for (int i = 0; i < numOfDev; i++) {
#ifdef __FREEBSD__
            const char *device_name_ptrn = "pci%d:%d:%d:%d";
#else
            const char *device_name_ptrn = "%04x:%02x:%02x.%x";
#endif
            snprintf(pcibuf, 32, device_name_ptrn, devPtr->pci.domain, devPtr->pci.bus, \
                     devPtr->pci.dev, devPtr->pci.func);
            if (queryDevCfg(devPtr->pci.conf_dev, pcibuf, i + 1)) {
                printErr();
                shouldFail = true;
            }
            devPtr++;
        }
        mdevices_info_destroy(dev, numOfDev);
    }
    return shouldFail ? MLX_CFG_ERROR : MLX_CFG_OK;
}

int MlxCfg::printValue(string strVal, u_int32_t val)
{
    string s = numToStr(val);
    u_int32_t n;
    if (strVal == "" || strVal == s || (strToNum(strVal, n, 10) && n == val)) {
        return printf("%-16u", val);
    }
    if (strVal.find("Array") == string::npos) {
        strVal += "(" + s + ")";
    }
    return printf("%-16s", strVal.c_str());
}

int MlxCfg::printParam(string param, u_int32_t val)
{
    if (val == MLXCFG_UNKNOWN) {
        return printf("%-16s", "N/A");
    }
    return printValue(param, val);
}

#define PRINT_SPACE_IF_NEEDED(width) \
    if(width > 16) {\
        printf(" ");\
    }

void MlxCfg::printSingleParam(const char *name,
        QueryOutputItem & queryOutItem, u_int8_t verbose, bool printNewCfg)
{
    bool showDefault = QUERY_DEFAULT_MASK & verbose;
    bool showCurrent = QUERY_CURRENT_MASK & verbose;
    int width = 0;
    string fieldName = increaseIndexIfNeeded(name);

    if ((showDefault && queryOutItem.nextVal != queryOutItem.defVal) ||
        (showCurrent && queryOutItem.nextVal != queryOutItem.currVal)) {
        printf("*        %-36s", fieldName.c_str());
    } else {
        printf("         %-36s", fieldName.c_str());
    }
    if (showDefault) {
        width = printParam(queryOutItem.strDefVal, queryOutItem.defVal);
    }
    if (showCurrent) {
        PRINT_SPACE_IF_NEEDED(width)
        width = printParam(queryOutItem.strCurrVal, queryOutItem.currVal);
    }
    PRINT_SPACE_IF_NEEDED(width)
    width = printParam(queryOutItem.strNextVal, queryOutItem.nextVal);

    if (printNewCfg) {
        PRINT_SPACE_IF_NEEDED(width)
        if (queryOutItem.setVal == MLXCFG_UNKNOWN) {
            printParam(queryOutItem.strNextVal, queryOutItem.nextVal);
        } else {
            printValue(queryOutItem.strSetVal, queryOutItem.setVal);
        }
    }
    printf("\n");
    return;

}

const char* MlxCfg::getDeviceName(const char *dev)
{
    mfile *mf;
    u_int32_t chip_rev;
    u_int32_t _dev_id;

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

void MlxCfg::printOpening(const char *dev, int devIndex)
{
    printf("\nDevice #%d:\n", devIndex);
    printf("----------\n\n");
    const char *devType = getDeviceName(dev);
    printf("%-16s%-16s\n", "Device type:", devType);
    if (!dm_is_4th_gen(_devType)) {
        std::vector<char> info;
        info.reserve(16);
        if (!getDeviceInformationString(dev, Device_Name, info)) {
            printf("%-16s%-16s\n", "Name:", "N/A");
        } else {
            printf("%-16s%-16s\n", "Name:", info.data());
        }
        info.clear();
        if (!getDeviceInformationString(dev, Device_Description, info)) {
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
            printf("%-16s%36s%16s%18s", "Configurations:", "Default", "Current",
                   NEXT_STR);
        } else {
            printf("%-16s%36s%18s", "Configurations:", "Default", NEXT_STR);
        }
    } else {
        if (showCurrent) {
            printf("%-16s%36s%18s", "Configurations:", "Current", NEXT_STR);
        } else {
            printf("%-16s%38s", "Configurations:", NEXT_STR);
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
        if (!found) {
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

void queryAux(Commander *commander, vector<ParamView>& params,
              vector<ParamView>& paramsToQuery, vector<string>& failedTLVs, QueryType qT)
{
    if (paramsToQuery.size() != 0) {
        params = paramsToQuery;
        commander->queryParamViews(params, qT);
    } else {
        commander->queryAll(params, failedTLVs, qT);
    }
}

string checkFailedTLVsVector(const vector<string>& failedTLVs, string queryType)
{
    string failedTLVsErrorMessage = "";
    if (failedTLVs.size() != 0) {
        failedTLVsErrorMessage += "    Failed to query the " + queryType + " values of the following TLVs:\n    ";
        CONST_VECTOR_ITERATOR(string, failedTLVs, it) {
            failedTLVsErrorMessage += (*it) + " ";
        }
        failedTLVsErrorMessage += "\n";
    }
    return failedTLVsErrorMessage;
}

void MlxCfg::editAndPushItem(std::vector<QueryOutputItem>& queryOutputItemVector, QueryOutputItem& item, u_int32_t arrayIndex)
{
    if (isIndexedStartFromOneSupported(getArrayPrefix(item.mlxconfigName))) {
        item.strNextVal = "Array[1.." + numToStr((arrayIndex * MAX_ARRAY_SIZE)) + "]";
    }
    else {
        item.strNextVal = "Array[0.." + numToStr((arrayIndex * MAX_ARRAY_SIZE) -1) + "]";
    }

    item.strCurrVal = item.strNextVal;
    item.strDefVal = item.strNextVal;
    if (arrayIndex > 1) {
        item.mlxconfigName = getArrayPrefix(item.mlxconfigName);
    }
    queryOutputItemVector.push_back(item);
}

void MlxCfg::removeContinuanceArray(std::vector<QueryOutputItem>& OutputItemOut, std::vector<QueryOutputItem>& OutputItemIn)
{
    QueryOutputItem* queryItem = NULL;;
    u_int32_t arrayCounter = 0;

    VECTOR_ITERATOR(QueryOutputItem, OutputItemIn, o) {

        if (getArraySuffix(o->mlxconfigName) == getArraySuffixByInterval(arrayCounter * MAX_ARRAY_SIZE)
            && !isIndexedMlxconfigName(o->mlxconfigName)) {
            arrayCounter++;
            queryItem = &*o;
            continue;
        }
        // in case that we have another continuance array right after end of a continuance array
        else if (getArraySuffix(o->mlxconfigName) == getArraySuffixByInterval(0) && queryItem != NULL
            && !isIndexedMlxconfigName(o->mlxconfigName)) {
            editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
            arrayCounter = 1;
            queryItem = &*o;
            continue;
        }

        if (queryItem != NULL) {
            editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
        }

        queryItem = NULL;
        arrayCounter = 0;
        OutputItemOut.push_back(*o);
    }
    // if item is not null (we have last member that need push)
    if (queryItem != NULL) {
        editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
    }
}

mlxCfgStatus MlxCfg::queryDevCfg(Commander *commander, const char *dev, const char *pci,
                                 int devIndex, bool printNewCfg)
{
    (void) pci;
    std::vector<QueryOutputItem> output;
    std::vector<QueryOutputItem> newoutput;
    std::vector<ParamView> params, defaultParams, currentParams;
    bool failedToGetCfg = false, isParamsDiffer = false;
    bool defaultSupported = false, currentSupported = false;
    bool showDefault = false, showCurrent = false;

    printOpening(dev, devIndex);
    printf("\n");

    vector<string> defaultFailedTLVs, currentFailedTLVs, nextFailedTLVs;

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
            queryAux(commander, defaultParams, _mlxParams.setParams, defaultFailedTLVs, QueryDefault);
        }
        if (showCurrent) {
            queryAux(commander, currentParams, _mlxParams.setParams, currentFailedTLVs, QueryCurrent);
        }
        queryAux(commander, params, _mlxParams.setParams, nextFailedTLVs, QueryNext);
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

    removeContinuanceArray(newoutput, output);

    //print output table:
    VECTOR_ITERATOR(QueryOutputItem, newoutput, o) {
        printSingleParam(o->mlxconfigName.c_str(),
                      *o,
                      QUERY_NEXT_MASK |
                      (showDefault ? QUERY_DEFAULT_MASK : 0) |
                      (showCurrent ? QUERY_CURRENT_MASK : 0),
                      printNewCfg);
        isParamsDiffer |= (showDefault && (o->nextVal != o->defVal))
                          || (showCurrent && (o->nextVal != o->currVal));
    }

    string failedTLVsErrorMessage = "Failed to query some of the TLVs:\n";
    failedTLVsErrorMessage += checkFailedTLVsVector(defaultFailedTLVs, "default");
    failedTLVsErrorMessage += checkFailedTLVsVector(currentFailedTLVs, "current");
    failedTLVsErrorMessage += checkFailedTLVsVector(nextFailedTLVs, "next");

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

    if (defaultFailedTLVs.size() != 0 ||
        currentFailedTLVs.size() != 0 || nextFailedTLVs.size() != 0) {
        err(false, "%s", failedTLVsErrorMessage.c_str());
        return MLX_CFG_ERROR;
    }

    return failedToGetCfg ? MLX_CFG_ERROR : MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::queryDevCfg(const char *dev, const char *pci,
                                 int devIndex, bool printNewCfg)
{
    mlxCfgStatus rc;
    Commander *commander = NULL;
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

const char * MlxCfg::getConfigWarning(const string & mlx_config_name,
        const string & set_val)
{
    if(mlx_config_name == DISABLE_SLOT_POWER_LIMITER) {
        if(set_val == "1" || strcasecmp(set_val.c_str(), "true") == 0) {
            return DISABLE_SLOT_POWER_LIMITER_WARN;
        }
    }
    return NULL;
}

mlxCfgStatus MlxCfg::setDevCfg()
{
    Commander *commander = NULL;

    try {
        commander = Commander::create(string(_mlxParams.device),
                                      _mlxParams.dbName);
    } catch (MlxcfgException& e) {
        delete commander;
        err(false, "%s", e._err.c_str());
        printErr();
        return MLX_CFG_ERROR;
    }
    // check if there is a set of DISABLE_SLOT_POWER
    //for mlx_config_name
    VECTOR_ITERATOR(ParamView, _mlxParams.setParams, p) {
        const char * warning_msg = getConfigWarning(p->mlxconfigName, p->setVal);
        if(warning_msg){
            if(!askUser(warning_msg, false, false)) {
                delete commander;
                printErr();
                return MLX_CFG_ABORTED;
            }
        }
    }

    if (queryDevCfg(commander, _mlxParams.device.c_str(), NULL, 1, true)
        == MLX_CFG_ERROR_EXIT) {
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
    if (!askUser("Apply new Configuration?")) {
        delete commander;
        printErr();
        return MLX_CFG_ABORTED;
    }

    try {
        printf("Applying... ");
        commander->setCfg(_mlxParams.setParams, _mlxParams.force);
        printf("Done!\n");
        const char *resetStr = commander->loadConfigurationGetStr();
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
        snprintf(buff, 256, "Reset configuration for device %s?", _mlxParams.device.c_str());
        if (!askUser(buff)) {
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
        int numOfDev;
        dev_info *dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        if (!askUser("Reset configuration for all devices?")) {
            printErr();
            mdevices_info_destroy(dev, numOfDev);
            return MLX_CFG_ABORTED;
        }
        printf("Applying... ");

        dev_info *devPtr = dev;
        bool shouldFail = false;

        for (int i = 0; i < numOfDev; i++) {
            if (resetDevCfg(devPtr->pci.conf_dev)) {
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
    Commander *commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    printf("-W- Forcefully clearing device Semaphore...\n");
    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        commander->clearSemaphore();
    } catch (MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander != NULL) {
        delete commander;
    }

    if (rc == MLX_CFG_OK) {
        printf(" Done!\n");
    } else {
        printf(" Failed!\n");
    }

    return rc;
}

mlxCfgStatus MlxCfg::devRawCfg(RawTlvMode mode)
{
    Commander *commander = NULL;
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
        ifs.close();
        // dump raw TLVs from the file
        std::string dumpStr;
        int tlvIdx = 1;
        if (mode == SET_RAW) {
            for (std::vector<std::vector<u_int32_t> >::iterator it = rawTlvsAsDw.begin();
                    it != rawTlvsAsDw.end(); it++, tlvIdx++) {
                commander->dumpRawCfg(*it, dumpStr);
                printf("Raw TLV #%d Info:\n%s\n", tlvIdx, dumpStr.c_str());
            }
        }
        // ask user
        if (mode == SET_RAW) {
            if (!askUser("Operation intended for advanced users.\n "\
                    "Are you sure you want to apply raw TLV file?")) {
                printErr();
                delete commander;
                return MLX_CFG_ABORTED;
            }
            printf("Applying... ");
        }
        tlvIdx = 1;
        // set each of the raw TLVs
        std::vector<u_int32_t> queryData;
        for (std::vector<std::vector<u_int32_t> >::iterator it = rawTlvsAsDw.begin();
                it != rawTlvsAsDw.end(); it++, tlvIdx++) {
            if (mode == SET_RAW) {
                commander->setRawCfg(*it);
            } else {
                queryData = commander->getRawCfg(*it);
                commander->dumpRawCfg(queryData, dumpStr);
                printf("Raw TLV #%d Info:\n%s\n", tlvIdx, dumpStr.c_str());
            }
        }
        //send mfrl command to fw
        //this command indicate to the fw that next time perst signal go down
        //[reboot] fw need to perform reset )
        commander->loadConfigurationGetStr();
    } catch (MlxcfgException& e) {
        delete commander;
        return err(true, "Failed to run %s command: %s",
                mode == SET_RAW ? "set_raw" : "get_raw", e._err.c_str());
    }
    if (commander != NULL) {
        delete commander;
    }
    // done successfully
    printf("Done!\n");
    if (mode == SET_RAW) {
        printf("-I- Please reboot machine to load new configurations.\n");
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::backupCfg()
{
    FILE *file;
    Commander *commander = NULL;
    vector<BackupView> views;

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("Collecting...\n");
        commander->backupCfgs(views);
        delete commander;
    } catch (MlxcfgException& e) {
        printf(" Failed!\n");
        if (commander) {
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

        for (std::vector<BackupView>::iterator it = views.begin();
             it != views.end(); it++) {
            fprintf(file, "%% TLV Type: 0x%08x, Writer ID: %s(0x%02x)"
                    ", Writer Host ID: 0x%02x\n",
                    it->type,
                    writerIdToStr((WriterId)(it->writerId)).c_str(),
                    it->writerId,
                    it->writerHostId);
            vector<u_int8_t> v = it->tlvBin;
            for (size_t i = 0; i < v.size() / 4; i++) {
                fprintf(file, "0x%08x ", __cpu_to_be32(((u_int32_t*)v.data())[i]));
            }
            fprintf(file, "\n");
        }

        fclose(file);

        printf("Done!\n");
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::tlvLine2DwVec(const std::string& tlvStringLine, std::vector<u_int32_t>& tlvVec)
{
    tlvVec.resize(0);
    std::string dwStr;
    u_int32_t dw;
    char *p = NULL;
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

mlxCfgStatus MlxCfg::resetDevCfg(const char *dev)
{
    Commander *commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    try {
        commander = Commander::create(dev, _mlxParams.dbName);
        commander->invalidateCfgs();
        commander->loadConfigurationGetStr(); //why to call this? seems needless
    } catch (MlxcfgException& e) {
        err(false, "%s", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander) {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::showDevConfs()
{
    Commander *commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("\nList of configurations the device %s may support:\n", _mlxParams.device.c_str());
        commander->printLongDesc(stdout);
    } catch (MlxcfgException& e) {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander) {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::readBinFile(string fileName, vector<u_int32_t>& buff)
{
    streampos size;

    std::ifstream ifs(fileName.c_str(),
                      ios::in | ios::binary | ios::ate);
    if (ifs.fail()) {
        return err(true, "Failed to open file: %s", fileName.c_str());
    }
    size = ifs.tellg();
    if (size % 4 != 0) {
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
    FILE *file = fopen(_mlxParams.NVOutputFile.c_str(), "wb");
    if (!file) {
        return err(true, "Failed to open file: %s",
                   _mlxParams.NVOutputFile.c_str());
    }
    for (u_int32_t i = 0; i < content.size() * 4; i += 4) {
        const size_t count = 4;
        size_t writtenCount = fwrite(((u_int8_t*)content.data()) + i, 1, count, file);
        if (writtenCount != count || ferror(file)) {
            fclose(file);
            return err(true, "Write failed: %s.", strerror(errno));
        }
    }
    fclose(file);
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(string content)
{
    FILE *file = fopen(_mlxParams.NVOutputFile.c_str(), "w");
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
        GenericCommander commander(NULL, _mlxParams.dbName,_mlxParams.deviceType == Switch);
        commander.genTLVsList(tlvs);
        VECTOR_ITERATOR(string, tlvs, it) {
            sprintf(buff, "%-50s0\n", it->c_str());
            (*it) = buff;
        }
    } catch (MlxcfgException& e) {
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
        for (unsigned i = 0; i < tLine.size(); i++) {
            if (tLine[i] != ' ' && tLine[i] != '\t') {
                tlvName += tLine[i];
            } else {
                while ((tLine[i] == ' ' || tLine[i] == '\t')
                       && (++i < tLine.size())) {
                }
                ;
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
        GenericCommander commander(NULL, _mlxParams.dbName,_mlxParams.deviceType == Switch);
        commander.genXMLTemplate(tlvs, xmlTemplate, _mlxParams.allAttrs);
    } catch (MlxcfgException& e) {
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
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType == Switch);
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
    } catch (MlxcfgException& e) {
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
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType == Switch);
        if (isBin) {
            commander.XML2Bin(xml, binBuff, false);
        } else {
            commander.XML2Raw(xml, raw);
        }
    } catch (MlxcfgException& e) {
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
#if defined(NO_OPEN_SSL)
    printf("-E- Not Implemented");
    return MLX_CFG_ERROR_EXIT;
#else
    string xml;
    vector<u_int32_t> buff;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(xml);
    EXIT_IF_RC_NOT_OK(rc)

    try {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType == Switch);
        commander.createConf(xml, buff);
        if (!_mlxParams.privPemFile.empty() &&
            !_mlxParams.keyPairUUID.empty()) {
            commander.sign(buff, _mlxParams.privPemFile,
                           _mlxParams.keyPairUUID);
        }
        else if (!_mlxParams.opensslEngine.empty() &&
                 !_mlxParams.opensslKeyId.empty() &&
                 !_mlxParams.keyPairUUID.empty()) {
            commander.sign(buff, "", _mlxParams.keyPairUUID,
                           _mlxParams.opensslEngine, _mlxParams.opensslKeyId);
        }
        else {
            commander.sign(buff);
        }
    } catch (MlxcfgException& e) {
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
#endif
}

mlxCfgStatus MlxCfg::apply()
{
    vector<u_int32_t> buff;
    vector<u_int8_t> bytesBuff;
    Commander *commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(buff);
    EXIT_IF_RC_NOT_OK(rc)

    copyDwVectorToBytesVector(buff, bytesBuff);

    try {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName);
        printf("Applying...\n");
        ((GenericCommander*)commander)->apply(bytesBuff);
    } catch (MlxcfgException& e) {
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


mlxCfgStatus MlxCfg::remoteTokenKeepAlive()
{
    mlxCfgStatus status = MLX_CFG_OK;
    mfile *mf = NULL;

    mf = mopen(_mlxParams.device.c_str());
    if (!mf) {
        printf("-E- failed opening the device.\n");
        return MLX_CFG_ERROR;
    }

    if ((mf->flags & MDEVS_IB) == 0) { //not IB device
        return err(true, "specified device is not an IB device.\n");
    }

    KeepAliveSession session(mf, _mlxParams.sessionId, _mlxParams.sessionTimeInSec);

    if (_mlxParams.isSleepTimeBetweenCommandsInput) {
        session.setSleepTimeBetweenCommands(_mlxParams.keepAliveSleepTimeBetweenCommands);
    }
    if (_mlxParams.isSleepTimeOnCommandTOInput) {
        session.setSleepTimeOnCommandTO(_mlxParams.keepAliveSleepTimeOnCommandTO);
    }

    keepAliveStatus sessionStatus = session.runSession();
    if (sessionStatus != KEEP_ALIVE_OK) {
        status = MLX_CFG_ERROR;
    }
    else {
        printf("Keep alive session has ended successfully.\n");
    }

    mclose(mf);

    return status;
}

bool MlxCfg::runMTCQ(mfile* mf, struct reg_access_switch_mtcq_reg_ext* mtcq_reg)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;

    mft_signal_set_handling(1);
    rc = reg_access_mtcq(mf, REG_ACCESS_METHOD_GET, mtcq_reg);
    dealWithSignal();
    if (rc) {
        return err(true, "failed getting response from the device, error %d.", rc);        
    }

    return true;
}

void MlxCfg::printArray(const u_int32_t arr[], int len)
{
    int i = 0;

    if (len < 0) {
        throw MlxcfgException("Invalid array length was given.\n");
    }

    for (; i < len; ++i) {
        printf("%08x", arr[i]);
    }
    printf("\n");
}

void MlxCfg::printHexArrayAsAscii(const u_int32_t arr[], int len) 
{
    u_int8_t byteArray[4];    
    int i = 0, j = 0;

    if (len < 0) {
        throw MlxcfgException("Invalid array length was given.\n");
    }    

    for (i = 0; i < len; ++i) {
        
        memcpy(byteArray, &arr[i], 4);        
        for (j = 3; j >= 0; --j) {
            printf("%c", byteArray[j]);
        }
    }
    printf("\n");
}

mlxCfgStatus MlxCfg::getChallenge()
{
    u_int32_t base_mac[2];

    mfile *mf = mopen(_mlxParams.device.c_str());
    if (!mf) {
        printf("-E- failed to open the device.\n");
        return MLX_CFG_ERROR;
    }

    if ((mf->flags & MDEVS_IB) == 0) { //not IB device
        return err(true, "specified device is not an IB device.\n");
    }

    struct reg_access_switch_mtcq_reg_ext mtcq_reg;
    memset(&mtcq_reg, 0, sizeof(mtcq_reg));
    mtcq_reg.token_opcode = _mlxParams.tokenID;
    if (!runMTCQ(mf, &mtcq_reg)) {
        return MLX_CFG_ERROR;
    }
    base_mac[0] = mtcq_reg.base_mac & 0xffffffff;
    base_mac[1] = (mtcq_reg.base_mac >> 32) & 0xffffffff;

    printf("Token opcode:       %x\n", mtcq_reg.token_opcode);
    printf("Keypair uuid:       ");
    printArray(mtcq_reg.keypair_uuid, 4);
    printf("Base mac:           %08x%08x\n", base_mac[1], base_mac[0]);
    printf("PSID:               ");
    printHexArrayAsAscii(mtcq_reg.psid, 4);
    printf("FW version:         %x%08x\n", mtcq_reg.fw_version_39_32, mtcq_reg.fw_version_31_0);
    printf("Source address:     ");
    printArray(mtcq_reg.source_address, 4);
    printf("Session id:         %x\n", mtcq_reg.session_id);
    printf("Challenge version:  %x\n", mtcq_reg.challenge_version);
    printf("Challenge:          ");
    printArray(mtcq_reg.challenge, 8);

    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::queryTokenSupport()
{
    mfile *mf = mopen(_mlxParams.device.c_str());
    if (!mf) {
        printf("-E- failed opening the device.\n");
        return MLX_CFG_ERROR;
    }

    tools_open_mcam mcam;
    memset(&mcam, 0, sizeof(mcam));    
    reg_access_status_t rc = ME_REG_ACCESS_OK;
    rc = reg_access_mcam(mf, REG_ACCESS_METHOD_GET, &mcam);
    if (rc) {
        return err(true, "failed getting response from the device, error %d.", rc);
    }
    
    printf("CS tokens supported:       %d\n", EXTRACT(mcam.mng_feature_cap_mask[2], 6, 1));
    printf("Debug FW tokens supported: %d\n", EXTRACT(mcam.mng_feature_cap_mask[2], 7, 1));

    return MLX_CFG_OK;
}

bool MlxCfg::runMDSR(mfile* mf, struct reg_access_switch_mdsr_reg_ext* mdsr_reg, reg_access_method_t method)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;

    mft_signal_set_handling(1);
    rc = reg_access_mdsr(mf, method, mdsr_reg);
    dealWithSignal();
    
    if (rc) {
        return err(true, "failed getting response from the device, error %d.", rc);
    }

    return true;
}

mlxCfgStatus MlxCfg::queryTokenSession()
{
    mfile *mf = mopen(_mlxParams.device.c_str());
    if (!mf) {
        return err(true, "failed opening the device.");
    }

    struct reg_access_switch_mdsr_reg_ext mdsr_reg;
    memset(&mdsr_reg, 0, sizeof(mdsr_reg));
    if (!runMDSR(mf, &mdsr_reg, REG_ACCESS_METHOD_GET)) {
        return MLX_CFG_ERROR;
    }
    processMDSRData(mdsr_reg, true);

    return MLX_CFG_OK;
}

void MlxCfg::processMDSRData(const struct reg_access_switch_mdsr_reg_ext& mdsr_reg, bool isQuery)
{
    static const char* additional_info_to_string[6] = {"No additional information available.",
                                                       "There is no debug session in progress.",
                                                       "FW is not secured, debug session cannot be ended.",
                                                       "Fail - Debug end request cannot be accepted.",
                                                       "Fail - Host is not allowed to query debug session.",
                                                       "Debug session active."};

    if (mdsr_reg.status == 0) {
        if (isQuery) {
            printf("%s\n", additional_info_to_string[mdsr_reg.additional_info]);
        }
        else {
            printf("Debug session ended successfully\n");
        }
    }
    else {
        if (mdsr_reg.additional_info > 5) {
            printf("-E- invalid code in info.\n");
        }
        else {
            printf("%s\n", additional_info_to_string[mdsr_reg.additional_info]);
        }
    }
}

mlxCfgStatus MlxCfg::endTokenSession()
{
    mfile *mf = mopen(_mlxParams.device.c_str());
    if (!mf) {
        return err(true, "failed opening the device.");
    }

    struct reg_access_switch_mdsr_reg_ext mdsr_reg;
    memset(&mdsr_reg, 0, sizeof(mdsr_reg));
    mdsr_reg.end = 1;
    if (!runMDSR(mf, &mdsr_reg, REG_ACCESS_METHOD_SET)) {
        return MLX_CFG_ERROR;
    }

    processMDSRData(mdsr_reg, false);
    
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::execute(int argc, char *argv[])
{
    mlxCfgStatus rc = parseArgs(argc, argv);
    if (rc) {
        if (rc == MLX_CFG_OK_EXIT) {
            rc = MLX_CFG_OK;
        } else if (rc != MLX_CFG_ERROR_NO_USAGE) {
            printUsage();
        }
        return rc;
    }

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
        ret = devRawCfg(SET_RAW);
        break;

    case Mc_Get_Raw:
        ret = devRawCfg(GET_RAW);
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
    case Mc_RemoteTokenKeepAlive:
        ret = remoteTokenKeepAlive();
        break;
    case Mc_ChallengeRequest:
        ret = getChallenge();
        break;
    case Mc_TokenSupported:
        ret = queryTokenSupport();
        break;
    case Mc_QueryTokenSession:
        ret = queryTokenSession();
        break;
    case Mc_EndTokenSession:
        ret = endTokenSession();
        break;
    default:
        // should not reach here.
        return err(true, "invalid command.");
    }
    return ret;
}

int main(int argc, char *argv[])
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

const char* KeepAliveSession::_mkdcErrorToString[5] = {"OK", "BAD_SESSION_ID", "BAD_KEEP_ALIVE_COUNTER",
                                                       "BAD_SOURCE_ADDRESS", "SESSION_TIMEOUT"};

const u_int32_t KeepAliveSession::_keepAliveTimestampInSec = 600;

KeepAliveSession::KeepAliveSession(mfile *mf, u_int16_t sessionId, u_int32_t sessionTimeInSec):
    _mf(mf),
    _sessionId(sessionId),
    _sessionTimeLeftInSec(sessionTimeInSec),
    _SleepTimeOnCommandTO(1),
    _SleepTimeBetweenCommands(300)
{
    memset(&_mkdc_reg, 0, sizeof(_mkdc_reg));
    _mkdc_reg.session_id = sessionId;

    srand(time(NULL));
    _mkdc_reg.current_keep_alive_counter = rand();
}

keepAliveStatus KeepAliveSession::runSession()
{
    time_t mkdcRunTime;
    u_int32_t sleepTimeInSec = 0;
    u_int32_t sleepBetweenCommandsInSec = _SleepTimeBetweenCommands;

    if (sleepBetweenCommandsInSec >= _keepAliveTimestampInSec) {
        return err(true, "Specified cycle time must be shorter than %d seconds.", _keepAliveTimestampInSec);
    }

    if (_sessionTimeLeftInSec < _keepAliveTimestampInSec) {
        return err(true, "Specified session time must be longer than %d minutes.", _keepAliveTimestampInSec / 60);
    }
    
    while (_sessionTimeLeftInSec >= _keepAliveTimestampInSec) {
        mkdcRunTime = 0;
        if (runMKDC(_mf, &_mkdc_reg, mkdcRunTime) != KEEP_ALIVE_OK) {
            return KEEP_ALIVE_ERROR;
        }
        if (processMKDCData(&_mkdc_reg) != KEEP_ALIVE_OK) {
            return KEEP_ALIVE_ERROR;
        }
        _sessionTimeLeftInSec -= mkdcRunTime;

        if (_sessionTimeLeftInSec > _keepAliveTimestampInSec) {
            if (sleepBetweenCommandsInSec > (_sessionTimeLeftInSec - _keepAliveTimestampInSec)) {
                //* sleep until last MKDC is needed (which is when _keepAliveTimestampInSec seconds are left for the session)
                sleepBetweenCommandsInSec = _sessionTimeLeftInSec - _keepAliveTimestampInSec;
            }
        }
        else {
            //* sleep until session time ends
            sleepBetweenCommandsInSec = _sessionTimeLeftInSec;
        }

        sleepTimeInSec = sleepBetweenCommandsInSec;
        msleep(sleepTimeInSec * 1000);
        _sessionTimeLeftInSec -= sleepBetweenCommandsInSec;
    }

    return KEEP_ALIVE_OK;
}

keepAliveStatus KeepAliveSession::runMKDC(mfile* mf, reg_access_switch_mkdc_reg_ext* mkdc_reg, time_t& timer)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;
    time_t start = 0;
    int status = 0;

    start = time(NULL);
    mft_signal_set_handling(1);
    rc = reg_access_mkdc(mf, REG_ACCESS_METHOD_GET, mkdc_reg);
    dealWithSignal();
    timer = time(NULL) - start;

    while ((rc == ME_ICMD_STATUS_EXECUTE_TO) && ((u_int32_t)timer < _keepAliveTimestampInSec)) {
        u_int32_t sleep_time_in_sec = _SleepTimeOnCommandTO;

        msleep(sleep_time_in_sec * 1000);

        mft_signal_set_handling(1);
        rc = reg_access_mkdc(mf, REG_ACCESS_METHOD_GET, mkdc_reg);
        dealWithSignal();

        timer = time(NULL) - start;
    }

    if (rc == ME_REG_ACCESS_REG_NOT_SUPP) {
        return err(true, "MKDC access register is not supported.");
    }
    else if (rc) {
        return err(true, "cannot access MKDC register, error code is %d.");
    }

    return KEEP_ALIVE_OK;
}

keepAliveStatus KeepAliveSession::processMKDCData(reg_access_switch_mkdc_reg_ext* mkdc_reg)
{
    if (mkdc_reg->error_code != 0) {
        return err(true, "keep alive session failed. error code: %s.", _mkdcErrorToString[mkdc_reg->error_code]);
    }
    if (mkdc_reg->session_id != _sessionId) {        
        return err(true, "received wrong session id.");
    }

    mkdc_reg->current_keep_alive_counter = mkdc_reg->next_keep_alive_counter;

    return KEEP_ALIVE_OK;
}

void KeepAliveSession::setSleepTimeOnCommandTO(u_int32_t sleepTime)
{
    _SleepTimeOnCommandTO = sleepTime;
}

void KeepAliveSession::setSleepTimeBetweenCommands(u_int32_t sleepTime)
{
    _SleepTimeBetweenCommands = sleepTime;
}

keepAliveStatus KeepAliveSession::err(bool report, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char errBuff[MAX_ERR_STR_LEN] = {0};

    if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN) {
        strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
    if (report) {
        fprintf(stdout, PRE_ERR_MSG " %s\n", errBuff);
    }
    va_end(args);
    return KEEP_ALIVE_ERROR;
}