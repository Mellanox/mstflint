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
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <time.h>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <tools_dev_types.h>
#include <reg_access/reg_access.h>
#include <tools_layouts/reg_access_switch_layouts.h>
#include "mlxcfg_ui.h"
#include "mlxcfg_generic_commander.h"

#define DISABLE_SLOT_POWER_LIMITER "DISABLE_SLOT_POWER_LIMITER"
#define DISABLE_SLOT_POWER_LIMITER_WARN                                                                                \
    "\nWARNING: YOU ARE ABOUT TO RE-ENABLE ONE OR MORE NETWORK PORTS THAT HAVE BEEN SHUT DOWN DUE TO INSUFFICIENT "    \
    "POWER ON THE PCIE SLOT."                                                                                          \
    "\nYOUR ACTION MAY RISK PROPER FUNCTIONAL OR PHYSICAL OPERATION OF THE CARD OR OF THE SERVER."                     \
    "\nMELLANOX TECHNOLOGIES HEREBY DISCLAIMS ANY AND ALL LIABILITY RELATED TO ANY DAMAGE CAUSED AS A RESULT OF THIS " \
    "RE-ENABLEMENT."                                                                                                   \
    "\nBY PROCEEDING WITH THIS RE-ENABLEMENT YOU WILL INVALIDATE ANY WARRANTY PROVIDED BY MELLANOX TECHNOLOGIES "      \
    "RELATED TO THIS CARD."                                                                                            \
    "\nIT IS ADVISED TO CHECK THE CARD\'S USER MANUAL FOR POWER SPECIFICATIONS OR TO CONTACT MELLANOX SUPPORT BEFORE " \
    "PERFORMING THIS ACTION."                                                                                          \
    "\nARE YOU SURE YOU WANT TO CONTINUE? [Y/N] [N]: "

#define NEXT_STR "Next Boot"
#define DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "Device Firmware does not support reading "
#define TLV_NAME_MAX_LENGTH 256
#define EXIT_IF_RC_NOT_OK(rc) \
    if (rc != MLX_CFG_OK)     \
    {                         \
        return rc;            \
    }

#define PRINT_SYNTAX_ERROR_AND_EXIT                     \
    printf("-E- Syntax error in: %s\n", line->c_str()); \
    return MLX_CFG_ERROR;

// Signal handler section
void TerminationHandler(int signum);

#ifdef __WIN__
#include <windows.h>

static BOOL CtrlHandler(DWORD fdwCtrlType)
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

    if (fatal_error_in_progress)
    {
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
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
#define SIGNAL_NUM 4
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGPIPE, SIGHUP};
#endif

    // set the signal handler
    for (int i = 0; i < SIGNAL_NUM; i++)
    {
        void (*prevFunc)(int);
        prevFunc = signal(signalList[i], TerminationHandler);
        if (prevFunc == SIG_ERR)
        {
            printf("-E- failed to set signal Handler.");
            exit(MLX_CFG_ERROR);
        }
    }
}

// End of signal handler section.

inline void copyVal(QueryOutputItem& o, const ParamView& p, QueryType qT)
{
    if (qT == QueryDefault)
    {
        o.defVal = p.val;
        o.strDefVal = p.strVal;
    }
    else if (qT == QueryCurrent)
    {
        o.currVal = p.val;
        o.strCurrVal = p.strVal;
    }
    else if (qT == QueryNext)
    {
        o.nextVal = p.val;
        o.strNextVal = p.strVal;
    }
}

inline void copySet(QueryOutputItem& o, const ParamView& p)
{
    o.setVal = p.val;
    o.strSetVal = p.strVal;
}

mlxCfgStatus MlxCfg::err(bool report, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char errBuff[MAX_ERR_STR_LEN] = {0};

    if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN)
    {
        strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
    _errStr = errBuff;
    if (report)
    {
        fprintf(stdout, PRE_ERR_MSG " %s\n", _errStr.c_str());
    }
    va_end(args);
    return MLX_CFG_ERROR;
}

void MlxCfg::printErr()
{
    fprintf(stdout, PRE_ERR_MSG " %s\n", _errStr.c_str());
}

bool MlxCfg::askUser(const char* question, bool add_prefix, bool add_suffix, int requiredYesLevel)
{
    const char* prefix = "";
    if (add_prefix)
    {
        prefix = "\n ";
    }

    const char* suffix = "";
    if (add_suffix)
    {
        suffix = " (y/n) [n] : ";
    }
    if (question == NULL)
    {
        question = "Do you want to continue?";
    }
    printf("%s%s%s", prefix, question, suffix);

    if (_mlxParams.yesLevel >= requiredYesLevel)
    {
        printf("y\n");
    }
    else if (_mlxParams.yesLevel == 1)
    {
        // user gave -y flag but it was not enough for this question.
        printf("n\n");
        return false;
    }
    else
    {
        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);

        if (strcasecmp(answer.c_str(), "y") && strcasecmp(answer.c_str(), "yes"))
        {
            err(false, "Aborted by user.");
            return false;
        }
    }
    return true;
}

void MlxCfg::rebootDevice(const string& device)
{
    string question = "Do you want to reboot the device " + device + " now?";
    if (askUser(question.c_str(), true, true, 2))
    {
        string cmd = "mstfwreset -d " + device + " -y r";
        printf("Rebooting device %s...\n", device.c_str());
        int rc = system(cmd.c_str());
        if (rc != 0)
        {
            fprintf(stderr, "-E- Failed to reboot device (exit code: %d)\n", rc);
        }
    }
}

mlxCfgStatus MlxCfg::queryDevsCfg()
{
    bool shouldFail = false;
    if (_mlxParams.isJsonOutputRequested)
    {
        // create/clear json file
        ofstream jsonOutStream(_mlxParams.NVOutputFile);
        if (jsonOutStream)
        {
            jsonOutStream << "{}" << endl;
            jsonOutStream.close(); // file is good and clear, we can continue to use it later on
        }
        else
        {
            cerr << "Failed to open \"" << _mlxParams.NVOutputFile << "\""
                 << ". Reason: " << std::error_code{errno, std::generic_category()}.message() << endl;
            return MLX_CFG_ERROR;
        }
    }
    if (_mlxParams.device.length())
    {
        if (queryDevCfg(_mlxParams.device.c_str()))
        {
            printErr();
            shouldFail = true;
        }
    }
    else
    {
        int numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL)
        {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0)
        {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        // printf("-D- num of dev: %d , 1st dev : %s\n", numOfDev, buf);
        dev_info* devPtr = dev;
        char pcibuf[32] = {0};

        for (int i = 0; i < numOfDev; i++)
        {
#ifdef __FREEBSD__
            const char* device_name_ptrn = "pci%d:%d:%d:%d";
#else
            const char* device_name_ptrn = "%04x:%02x:%02x.%x";
#endif
            snprintf(pcibuf, 32, device_name_ptrn, devPtr->pci.domain, devPtr->pci.bus, devPtr->pci.dev,
                     devPtr->pci.func);
            if (queryDevCfg(devPtr->pci.conf_dev, pcibuf, i + 1))
            {
                printErr();
                shouldFail = true;
            }
            devPtr++;
        }
        mdevices_info_destroy(dev, numOfDev);
    }
    if (_mlxParams.isJsonOutputRequested)
    {
        if (shouldFail)
        {
            cout << "Query output saved to " << _mlxParams.NVOutputFile << " but one or more devices had an error."
                 << endl;
        }
        else
        {
            cout << "Query output saved to " << _mlxParams.NVOutputFile << " successfully" << endl;
        }
    }
    return shouldFail ? MLX_CFG_ERROR : MLX_CFG_OK;
}

int MlxCfg::printValue(string strVal, u_int32_t val)
{
    string s = numToStr(val);
    u_int32_t n = 0;
    if (strVal == "" || strVal == s || (strToNum(strVal, n, 10) && n == val))
    {
        return printf("%-20u", val);
    }
    if (strVal.find("Array") == string::npos)
    {
        strVal += "(" + s + ")";
    }
    return printf("%-20s", strVal.c_str());
}

int MlxCfg::printParam(string param, u_int32_t val)
{
    if (val == MLXCFG_UNKNOWN)
    {
        return printf("%-20s", "N/A");
    }
    return printValue(param, val);
}

#define PRINT_SPACE_IF_NEEDED(width) \
    if (width >= 20)                 \
    {                                \
        printf(" ");                 \
    }

void MlxCfg::writeParamToJson(Json::Value& oJsonValue, string field, string param, u_int32_t val)
{
    if (val == MLXCFG_UNKNOWN)
    {
        oJsonValue[field] = "N/A";
        return;
    }

    string s = numToStr(val);
    u_int32_t n = 0;
    if (param == "" || param == s || (strToNum(param, n, 10) && n == val))
    {
        oJsonValue[field] = val;
        return;
    }
    if (param.find("Array") == string::npos)
    {
        param += "(" + s + ")";
    }
    oJsonValue[field] = param;
}

mlxCfgStatus
  MlxCfg::WriteSingleParam(QueryOutputItem& queryOutItem, string deviceIndex, u_int8_t verbose, Json::Value& oJsonValue)
{
    bool showDefault = QUERY_DEFAULT_MASK & verbose;
    bool showCurrent = QUERY_CURRENT_MASK & verbose;
    bool modified = ((showDefault && queryOutItem.nextVal != queryOutItem.defVal) ||
                     (showCurrent && queryOutItem.nextVal != queryOutItem.currVal));

    oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName] = {};
    oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName]["read_only"] = queryOutItem.isReadOnly;
    writeParamToJson(oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName], "next_value",
                     queryOutItem.strNextVal, queryOutItem.nextVal);

    if (showDefault || showCurrent)
    {
        oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName]["modified"] = modified;
    }
    if (showDefault)
    {
        writeParamToJson(oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName], "default_value",
                         queryOutItem.strDefVal, queryOutItem.defVal);
    }
    if (showCurrent)
    {
        writeParamToJson(oJsonValue[deviceIndex]["tlv_configuration"][queryOutItem.mlxconfigName], "current_value",
                         queryOutItem.strCurrVal, queryOutItem.currVal);
    }
    return MLX_CFG_OK;
}

void MlxCfg::printSingleParam(const char* name, QueryOutputItem& queryOutItem, u_int8_t verbose, bool printNewCfg)
{
    bool showDefault = QUERY_DEFAULT_MASK & verbose;
    bool showCurrent = QUERY_CURRENT_MASK & verbose;
    int width = 0;
    string fieldName = increaseIndexIfNeeded(name);

    string diff = " ";
    string readOnly = "  ";

    if ((showDefault && queryOutItem.nextVal != queryOutItem.defVal) ||
        (showCurrent && queryOutItem.nextVal != queryOutItem.currVal))
    {
        diff = "*";
    }
    if (queryOutItem.isReadOnly)
    {
        readOnly = "RO";
    }
    printf("%s%s     %-44s", diff.c_str(), readOnly.c_str(), fieldName.c_str());

    if (showDefault)
    {
        width = printParam(queryOutItem.strDefVal, queryOutItem.defVal);
    }
    if (showCurrent)
    {
        PRINT_SPACE_IF_NEEDED(width)
        width = printParam(queryOutItem.strCurrVal, queryOutItem.currVal);
    }
    PRINT_SPACE_IF_NEEDED(width)
    width = printParam(queryOutItem.strNextVal, queryOutItem.nextVal);

    if (printNewCfg)
    {
        PRINT_SPACE_IF_NEEDED(width)
        if (queryOutItem.setVal == MLXCFG_UNKNOWN)
        {
            printParam(queryOutItem.strNextVal, queryOutItem.nextVal);
        }
        else
        {
            printValue(queryOutItem.strSetVal, queryOutItem.setVal);
        }
    }
    printf("\n");
    return;
}

const char* MlxCfg::getDeviceName(mfile* mf)
{
    u_int32_t chip_rev = 0;
    u_int32_t _dev_id = 0;

    if (dm_get_device_id(mf, &_devType, &_dev_id, &chip_rev))
    {
        return "";
    }
    return dm_dev_type2str(_devType);
}

void MlxCfg::printOpening(mfile* mf, const char* dev, string deviceIndex, Json::Value& oJsonValue)
{
    const char* devType = getDeviceName(mf);
    string deviceNameInfo = "N/A";
    string deviceDescriptionInfo = "N/A";
    std::vector<char> info;
    info.reserve(16);
    if (getDeviceInformationString(mf, Device_Name, info))
    {
        deviceNameInfo = info.data();
    }
    info.clear();
    if (getDeviceInformationString(mf, Device_Description, info))
    {
        deviceDescriptionInfo = info.data();
    }

    if (_mlxParams.isJsonOutputRequested)
    {
        oJsonValue[deviceIndex] = {};
        oJsonValue[deviceIndex]["device_type"] = devType;
        oJsonValue[deviceIndex]["name"] = deviceNameInfo;
        oJsonValue[deviceIndex]["description"] = deviceDescriptionInfo;
        oJsonValue[deviceIndex]["device"] = dev;
        oJsonValue[deviceIndex]["tlv_configuration"] = {};
    }
    else
    {
        printf("\n%s:\n", deviceIndex.c_str());
        printf("----------\n\n");
        printf("%-20s%-20s\n", "Device type:", devType);
        printf("%-20s%-20s\n", "Name:", deviceNameInfo.c_str());
        printf("%-20s%-20s\n", "Description:", deviceDescriptionInfo.c_str());
        printf("%-20s%-20s\n", "Device:", dev);
        printf("\n");
    }
}

void MlxCfg::printConfHeader(bool showDefualt, bool showNew, bool showCurrent)
{
    if (!_mlxParams.isJsonOutputRequested)
    {
        // print configuration Header
        if (showDefualt)
        {
            if (showCurrent)
            {
                printf("%-20s%44s%20s%18s", "Configurations:", "Default", "Current", NEXT_STR);
            }
            else
            {
                printf("%-20s%44s%18s", "Configurations:", "Default", NEXT_STR);
            }
        }
        else
        {
            if (showCurrent)
            {
                printf("%-20s%46s%18s", "Configurations:", "Current", NEXT_STR);
            }
            else
            {
                printf("%-20s%46s", "Configurations:", NEXT_STR);
            }
        }
        if (showNew)
        {
            printf("       %s", "New");
        }
    }
}

void prepareSetInput(vector<QueryOutputItem>& output, vector<ParamView>& params)
{
    for (std::vector<ParamView>::iterator p = params.begin(); p != params.end(); ++p)
    {
        QueryOutputItem o;
        o.mlxconfigName = p->mlxconfigName;
        o.isReadOnly = p->isReadOnlyParam;
        o.defVal = MLXCFG_UNKNOWN;
        o.currVal = MLXCFG_UNKNOWN;
        o.nextVal = MLXCFG_UNKNOWN;
        copySet(o, *p);
        output.push_back(o);
    }
}

void prepareQueryOutput(vector<QueryOutputItem>& output, vector<ParamView>& params, QueryType qT)
{
    for (std::vector<ParamView>::iterator p = params.begin(); p != params.end(); ++p)
    {
        bool found = false;
        for (std::vector<QueryOutputItem>::iterator o = output.begin(); o != output.end(); ++o)
        {
            if (p->mlxconfigName == o->mlxconfigName)
            {
                copyVal(*o, *p, qT);
                found = true;
                break;
            }
        }
        if (!found)
        {
            QueryOutputItem o;
            o.mlxconfigName = p->mlxconfigName;
            o.isReadOnly = p->isReadOnlyParam;
            o.defVal = MLXCFG_UNKNOWN;
            o.currVal = MLXCFG_UNKNOWN;
            o.nextVal = MLXCFG_UNKNOWN;
            o.setVal = MLXCFG_UNKNOWN;
            copyVal(o, *p, qT);
            output.push_back(o);
        }
    }
}

void queryAux(Commander* commander,
              vector<ParamView>& params,
              vector<ParamView>& paramsToQuery,
              vector<string>& failedTLVs,
              QueryType qT,
              bool isWriteOperation)
{
    if (paramsToQuery.size() != 0)
    {
        params = paramsToQuery;
        commander->queryParamViews(params, isWriteOperation, qT);
    }
    else
    {
        commander->queryAll(params, failedTLVs, qT);
    }
}

string checkFailedTLVsVector(const vector<string>& failedTLVs, string queryType)
{
    string failedTLVsErrorMessage = "";
    if (failedTLVs.size() != 0)
    {
        failedTLVsErrorMessage += "    Failed to query the " + queryType + " values of the following TLVs:\n    ";
        CONST_VECTOR_ITERATOR(string, failedTLVs, it)
        {
            failedTLVsErrorMessage += (*it) + " ";
        }
        failedTLVsErrorMessage += "\n";
    }
    return failedTLVsErrorMessage;
}

void MlxCfg::editAndPushItem(std::vector<QueryOutputItem>& queryOutputItemVector,
                             QueryOutputItem& item,
                             u_int32_t arrayIndex)
{
    if (isIndexedStartFromOneSupported(getArrayPrefix(item.mlxconfigName)))
    {
        item.strNextVal = "Array[1.." + numToStr((arrayIndex * MAX_ARRAY_SIZE)) + "]";
    }
    else
    {
        item.strNextVal = "Array[0.." + numToStr((arrayIndex * MAX_ARRAY_SIZE) - 1) + "]";
    }

    item.strCurrVal = item.strNextVal;
    item.strDefVal = item.strNextVal;
    if (isContinuanceArray(item.mlxconfigName))
    {
        item.mlxconfigName = getArrayPrefix(item.mlxconfigName);
    }
    queryOutputItemVector.push_back(item);
}

void MlxCfg::removeContinuanceArray(std::vector<QueryOutputItem>& OutputItemOut,
                                    std::vector<QueryOutputItem>& OutputItemIn)
{
    QueryOutputItem* queryItem = NULL;
    u_int32_t arrayCounter = 0;

    VECTOR_ITERATOR(QueryOutputItem, OutputItemIn, o)
    {
        if (getArraySuffix(o->mlxconfigName) == getArraySuffixByInterval(arrayCounter * MAX_ARRAY_SIZE) &&
            !isIndexedMlxconfigName(o->mlxconfigName))
        {
            arrayCounter++;
            queryItem = &*o;
            continue;
        }
        // In case that we have another continuance array right after end of a continuance array
        else if (getArraySuffix(o->mlxconfigName) == getArraySuffixByInterval(0) && queryItem != NULL &&
                 !isIndexedMlxconfigName(o->mlxconfigName))
        {
            editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
            arrayCounter = 1;
            queryItem = &*o;
            continue;
        }

        if (queryItem != NULL)
        {
            editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
        }

        queryItem = NULL;
        arrayCounter = 0;
        OutputItemOut.push_back(*o);
    }
    // if item is not null (we have last member that need push)
    if (queryItem != NULL)
    {
        editAndPushItem(OutputItemOut, *queryItem, arrayCounter);
    }
}

mlxCfgStatus MlxCfg::queryDevCfg(Commander* commander,
                                 const char* dev,
                                 bool isWriteOperation,
                                 const char* pci,
                                 int devIndex,
                                 bool printNewCfg)
{
    (void)pci;
    std::vector<QueryOutputItem> output;
    std::vector<QueryOutputItem> newoutput;
    std::vector<ParamView> params, defaultParams, currentParams;
    bool failedToGetCfg = false, isParamsDiffer = false;
    bool isParamsReadOnly = false;
    bool defaultSupported = false, currentSupported = false, isPrivNvOtherHostSupported = false;
    bool showDefault = false, showCurrent = false;

    Json::Value oJsonValue;
    if (_mlxParams.isJsonOutputRequested)
    {
        ifstream jsonInputStream(_mlxParams.NVOutputFile);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true;
        JSONCPP_STRING errs;
        bool rc = parseFromStream(builder, jsonInputStream, &oJsonValue, &errs);
        jsonInputStream.close();
        if (!rc)
        {
            cerr << "failed to read json file [" << _mlxParams.NVOutputFile << "]" << endl;
            return MLX_CFG_ERROR;
        }
    }

    string deviceIndex = "Device #" + std::to_string(devIndex);
    printOpening(commander->mf(), dev, deviceIndex, oJsonValue);

    vector<string> defaultFailedTLVs, currentFailedTLVs, nextFailedTLVs;

    try
    {
        if (_mlxParams.enableVerbosity)
        {
            commander->getGlobalCapabilities(defaultSupported, currentSupported, isPrivNvOtherHostSupported);
        }

        showDefault = defaultSupported;
        showCurrent = currentSupported;

        printConfHeader(showDefault, printNewCfg, showCurrent);
        printf("\n");

        if (printNewCfg)
        {
            VECTOR_ITERATOR(ParamView, _mlxParams.setParams, p)
            {
                // update the user param next value with the value the user asked to set
                commander->updateParamViewValue(*p, p->setVal, QueryNext);
            }
            prepareSetInput(output, _mlxParams.setParams);
        }

        if (showDefault)
        {
            queryAux(commander, defaultParams, _mlxParams.setParams, defaultFailedTLVs, QueryDefault, isWriteOperation);
        }
        if (showCurrent)
        {
            queryAux(commander, currentParams, _mlxParams.setParams, currentFailedTLVs, QueryCurrent, isWriteOperation);
        }
        queryAux(commander, params, _mlxParams.setParams, nextFailedTLVs, QueryNext, isWriteOperation);
    }
    catch (MlxcfgException& e)
    {
        err(false, "%s", e._err.c_str());
        return MLX_CFG_ERROR_EXIT;
    }

    if (showDefault)
    {
        prepareQueryOutput(output, defaultParams, QueryDefault);
    }
    if (showCurrent)
    {
        prepareQueryOutput(output, currentParams, QueryCurrent);
    }
    prepareQueryOutput(output, params, QueryNext);

    removeContinuanceArray(newoutput, output);

    uint8_t verbosity =
      QUERY_NEXT_MASK | (showDefault ? QUERY_DEFAULT_MASK : 0) | (showCurrent ? QUERY_CURRENT_MASK : 0);

    if (_mlxParams.isJsonOutputRequested)
    {
        // write output table to json file:
        VECTOR_ITERATOR(QueryOutputItem, newoutput, o)
        {
            WriteSingleParam(*o, deviceIndex, verbosity, oJsonValue);
        }
    }
    else
    {
        // print output table:
        VECTOR_ITERATOR(QueryOutputItem, newoutput, o)
        {
            printSingleParam(o->mlxconfigName.c_str(), *o, verbosity, printNewCfg);
            isParamsDiffer |= (showDefault && (o->nextVal != o->defVal)) || (showCurrent && (o->nextVal != o->currVal));
            isParamsReadOnly |= o->isReadOnly;
        }
    }

    string failedTLVsErrorMessage = "Failed to query some of the TLVs:\n";
    failedTLVsErrorMessage += checkFailedTLVsVector(defaultFailedTLVs, "default");
    failedTLVsErrorMessage += checkFailedTLVsVector(currentFailedTLVs, "current");
    failedTLVsErrorMessage += checkFailedTLVsVector(nextFailedTLVs, "next");

    if (!_mlxParams.isJsonOutputRequested)
    {
        if (isParamsDiffer)
        {
            printf("The '*' shows parameters with next value different "
                   "from default/current value.\n");
        }
        if (isParamsReadOnly)
        {
            printf("\nThe 'RO' shows parameters which are for read only and cannot be changed\n");
        }
    }

    if (_mlxParams.enableVerbosity)
    {
        if (!defaultSupported && !currentSupported)
        {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "default and current configurations\n");
        }
        else if (!defaultSupported)
        {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "default configurations\n");
        }
        else if (!currentSupported)
        {
            printf(DEFAULT_CURRENT_NOT_SUPPORTED_PREFIX "current configurations\n");
        }
    }

    if (_mlxParams.isJsonOutputRequested)
    {
        ofstream jsonOutputStream(_mlxParams.NVOutputFile);
        Json::StreamWriterBuilder jsonWriter;
        std::string oJsonString = Json::writeString(jsonWriter, oJsonValue);
        jsonOutputStream << oJsonString;
        jsonOutputStream << endl;
        jsonOutputStream.close();
    }

    if (params.size() == 0)
    {
        err(false, "Device doesn't support any configuration changes.");
        return MLX_CFG_ERROR_EXIT;
    }

    if (defaultFailedTLVs.size() != 0 || currentFailedTLVs.size() != 0 || nextFailedTLVs.size() != 0)
    {
        err(false, "%s", failedTLVsErrorMessage.c_str());
        return MLX_CFG_ERROR;
    }

    return failedToGetCfg ? MLX_CFG_ERROR : MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::queryDevCfg(const char* dev, const char* pci, int devIndex, bool printNewCfg)
{
    bool isWriteOperation = false;
    Commander* commander = createCommander(string(dev), false, false);
    if (!commander)
    {
        return MLX_CFG_ERROR;
    }

    mlxCfgStatus rc = queryDevCfg(commander, dev, isWriteOperation, pci, devIndex, printNewCfg);
    delete commander;
    return rc;
}

const char* MlxCfg::getConfigWarning(const string& mlx_config_name, const string& set_val)
{
    if (mlx_config_name == DISABLE_SLOT_POWER_LIMITER)
    {
        if (set_val == "1" || strcasecmp(set_val.c_str(), "true") == 0)
        {
            return DISABLE_SLOT_POWER_LIMITER_WARN;
        }
    }
    return NULL;
}

mlxCfgStatus MlxCfg::updateDefaultParamsWithUserValues(std::vector<ParamView>& userParams,
                                                       std::vector<ParamView>& defaultParams)
{
    mlxCfgStatus rc = MLX_CFG_OK;
    // Convert defaultParams to a map for fast lookup by mlxconfigName
    // key = mlxconfig name , value = index in defaultParam
    std::unordered_map<std::string, size_t> defaultParamsIndexMap;
    for (size_t i = 0; i < defaultParams.size(); ++i)
    {
        defaultParamsIndexMap[defaultParams[i].mlxconfigName] = i;
    }

    // add any missing default params to userParams
    for (vector<ParamView>::iterator userParam = userParams.begin(); userParam != userParams.end(); ++userParam)
    {
        string parsedMlxconfigName = userParam->mlxconfigName;
        bool isArrayParam = false;
        u_int32_t index = 0;
        if (isIndexedMlxconfigName(userParam->mlxconfigName))
        {
            parseIndexedMlxconfigName(userParam->mlxconfigName, parsedMlxconfigName, index);
            isArrayParam = true;
        }
        if (defaultParamsIndexMap.count(parsedMlxconfigName) == 0)
        {
            cerr << "Error: " << parsedMlxconfigName << " does not exist in default parameters" << endl;
            return MLX_CFG_ERROR;
        }
        int mapIndex = defaultParamsIndexMap[parsedMlxconfigName];

        if (isArrayParam)
        {
            defaultParams[mapIndex].arrayVal[index] = (*userParam).val;
        }
        else
        {
            defaultParams[mapIndex].val = (*userParam).val;
        }
    }

    return rc;
}

// Compare params vectors by mlxconfigName, regardless of order for example  userParams and paramsCurrent
void MlxCfg::compareCurrentParamsVectors(const std::vector<ParamView>& currentVec,
                                         const std::vector<ParamView>& OtherVec,
                                         std::vector<ParamView>& paramMlxconfigNameDiffList)
{
    for (const ParamView& currentParam : currentVec)
    {
        // skip read only params
        if (currentParam.isReadOnlyParam)
        {
            continue;
        }
        for (const ParamView& otherParam : OtherVec)
        {
            if (currentParam.mlxconfigName == otherParam.mlxconfigName)
            {
                if (currentParam.arrayVal.size() > 0)
                {
                    for (u_int32_t i = 0; i < currentParam.arrayVal.size(); i++)
                    {
                        if (currentParam.arrayVal[i] != otherParam.arrayVal[i])
                        {
                            paramMlxconfigNameDiffList.push_back(currentParam);
                            break;
                        }
                    }
                }
                else
                {
                    if (currentParam.val != otherParam.val)
                    {
                        paramMlxconfigNameDiffList.push_back(currentParam);
                    }
                }
            }
        }
    }
}

// This function is slow, it can take around 10-20 seconds to query all the parameters and then around 1 ms for the
// rest.
void MlxCfg::setDevCfgWithDefault(Commander* commander,
                                  std::vector<ParamView>& alignCurrentToDefault,
                                  std::vector<ParamView>& alignNextToCurrent)
{
    //  1 Query all
    std::vector<ParamView> paramsCurrent = {};
    std::vector<ParamView> paramsDefault = {};
    std::vector<ParamView> paramsNext = {};
    std::vector<ParamView> paramsCurrentToNext = {};

    std::vector<string> currentFailedTLVs = {};
    std::vector<string> defaultFailedTLVs = {};
    std::vector<string> nextFailedTLVs = {};

    commander->queryAll(paramsCurrent, currentFailedTLVs, QueryCurrent);
    commander->queryAll(paramsDefault, defaultFailedTLVs, QueryDefault);
    commander->queryAll(paramsNext, nextFailedTLVs, QueryNext);

    // 2 merge paramsCurrent and _mlxParams.setParams
    std::vector<ParamView> userParams = _mlxParams.setParams;
    VECTOR_ITERATOR(ParamView, userParams, p)
    {
        // update the user param next value with the value the user asked to set
        commander->updateParamViewValue(*p, p->setVal, QueryNext);
    }
    updateDefaultParamsWithUserValues(userParams, paramsDefault);

    // 3 compare current with default
    compareCurrentParamsVectors(paramsCurrent, paramsDefault, alignCurrentToDefault);

    // 4 compare current with next, only take params that are not going to be reset.
    // compareCurrentParamsVectors(paramsCurrent, paramsNext, alignNextToCurrent);
    compareCurrentParamsVectors(paramsCurrent, paramsNext, paramsCurrentToNext);
    for (const ParamView& param : paramsCurrentToNext)
    {
        if (!isParamViewInList(param, alignCurrentToDefault))
        {
            alignNextToCurrent.push_back(param);
        }
    }
}

mlxCfgStatus MlxCfg::handlecompleteSetWithDefault(Commander* commander)
{
    std::vector<ParamView> alignCurrentToDefault = {};
    std::vector<ParamView> alignNextToCurrent = {};
    setDevCfgWithDefault(commander, alignCurrentToDefault, alignNextToCurrent);
    bool userWantToAlign = false;

    if (alignNextToCurrent.size() > 0)
    {
        cout << "differences found between next boot value and current value on " << alignNextToCurrent.size()
             << " parameters" << endl;
        if (askUser("Do you want to align next boot value to current value?"))
        {
            userWantToAlign = true;
            unordered_set<string> setParamsMlxconfigName;
            for (const ParamView& p : _mlxParams.setParams)
            {
                setParamsMlxconfigName.insert(p.mlxconfigName);
            }

            // strip alignment arrays
            std::vector<ParamView> alignNextToCurrentFlat = {};
            for (const ParamView& pView : alignNextToCurrent)
            {
                if (pView.arrayVal.size() > 0)
                {
                    for (u_int32_t i = 0; i < pView.arrayVal.size(); i++)
                    {
                        ParamView pViewFlat = pView;
                        pViewFlat.mlxconfigName = pViewFlat.mlxconfigName + "[" + numToStr(i) + "]";
                        pViewFlat.setVal = numToStr(pView.arrayVal[i]);
                        alignNextToCurrentFlat.push_back(pViewFlat);
                    }
                }
                else
                {
                    alignNextToCurrentFlat.push_back(pView);
                }
            }

            // make sure we don't add parameter that is already in the setParams
            for (const ParamView& pView : alignNextToCurrentFlat)
            {
                if (!isParamViewInList(pView, _mlxParams.setParams))
                {
                    _mlxParams.setParams.push_back(pView);
                }
            }
        }
    }

    if (alignCurrentToDefault.size() == 0 && !userWantToAlign)
    {
        cout << "Nothing to set" << endl;
        return MLX_CFG_OK_EXIT;
    }

    // else continue to reset and set
    // ask user
    if (!askUser("Apply reset and set?"))
    {
        printErr();
        return MLX_CFG_ABORTED;
    }

    // invalidate each different TLV separately.
    commander->invalidateCfg(alignCurrentToDefault);
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::setDevCfgWithParams(Commander* commander, std::vector<ParamView>& setParams)
{
    bool isWriteOperation = true;

    // check if there is a set of DISABLE_SLOT_POWER
    // for mlx_config_name
    for (vector<ParamView>::iterator p = setParams.begin(); p != setParams.end(); ++p)
    {
        const char* warning_msg = getConfigWarning(p->mlxconfigName, p->setVal);
        if (warning_msg)
        {
            if (!askUser(warning_msg, false, false))
            {
                printErr();
                return MLX_CFG_ABORTED;
            }
        }
    }

    if (_mlxParams.completeSetWithDefault)
    {
        mlxCfgStatus rc = handlecompleteSetWithDefault(commander);
        if (rc != MLX_CFG_OK)
        {
            if (rc == MLX_CFG_OK_EXIT)
            {
                return MLX_CFG_OK;
            }
            return rc;
        }
    }

    if (queryDevCfg(commander, _mlxParams.device.c_str(), isWriteOperation, NULL, 1, true) == MLX_CFG_ERROR_EXIT)
    {
        printErr();
        return MLX_CFG_ERROR;
    }

    // even if there is problem fetching the current cfg we will attempt to write the new info
    // if the user agrees

    if (_mlxParams.force)
    {
        printf("\n-W- Force flag specified, the validity of the Parameters will not be checked !\n");
        printf("-W- Incorrect configuration might yield unexpected results. running in this mode is not recommended.");
    }

    if (!_mlxParams.completeSetWithDefault)
    {
        // ask user (if we didn't ask before in the set with default mode)
        if (!askUser("Apply new Configuration?"))
        {
            printErr();
            return MLX_CFG_ABORTED;
        }
    }

    try
    {
        printf("Applying... ");
        commander->setCfg(setParams, _mlxParams.force);
        printf("Done!\n");
        const char* resetStr = commander->loadConfigurationGetStr();
        printf("-I- %s\n", resetStr);
        return MLX_CFG_OK;
    }
    catch (MlxcfgException& e)
    {
        printf("Failed!\n");
        err(true, "%s", e._err.c_str());
        return MLX_CFG_ERROR;
    }
}

Commander* MlxCfg::createCommander(const string& device, bool forceCreate, bool useMaxPort)
{
    Commander* commander = NULL;
    try
    {
        commander = Commander::create(device, _mlxParams.dbName, forceCreate, _mlxParams.deviceType, useMaxPort);
        commander->setHostFunctionParams(_mlxParams.userHostIdParam, _mlxParams.userPfIndexParam,
                                         _mlxParams.userHostIdPfValid);
    }
    catch (MlxcfgException& e)
    {
        delete commander;
        err(false, "%s", e._err.c_str());
        printErr();
        return NULL;
    }
    return commander;
}

mlxCfgStatus MlxCfg::setDevCfg()
{
    Commander* commander = createCommander(_mlxParams.device, false, false);
    if (!commander)
    {
        return MLX_CFG_ERROR;
    }

    mlxCfgStatus rc = setDevCfgWithParams(commander, _mlxParams.setParams);
    delete commander;
    return rc;
}

mlxCfgStatus MlxCfg::resetDevsCfg()
{
    // check if a single device was specified and apply reset for this device only
    if (_mlxParams.device.length())
    {
        char buff[256] = {0};
        snprintf(buff, 256, "Reset configuration for device %s?", _mlxParams.device.c_str());
        if (!askUser(buff))
        {
            printErr();
            return MLX_CFG_ABORTED;
        }

        printf("Applying... ");
        if (resetDevCfg(_mlxParams.device.c_str()))
        {
            printf("Failed!\n");
            printErr();
            return MLX_CFG_ERROR;
        }
    }
    else
    {
        // reset all devices.
        int numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL)
        {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0)
        {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        if (!askUser("Reset configuration for all devices?"))
        {
            printErr();
            mdevices_info_destroy(dev, numOfDev);
            return MLX_CFG_ABORTED;
        }
        printf("Applying... ");

        dev_info* devPtr = dev;
        bool shouldFail = false;

        for (int i = 0; i < numOfDev; i++)
        {
            if (resetDevCfg(devPtr->pci.conf_dev))
            {
                shouldFail = true;
            }
            devPtr++;
        }
        mdevices_info_destroy(dev, numOfDev);
        if (shouldFail)
        {
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
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, true, _mlxParams.deviceType, false);
        commander->clearSemaphore();
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander != NULL)
    {
        delete commander;
    }

    if (rc == MLX_CFG_OK)
    {
        printf(" Done!\n");
    }
    else
    {
        printf(" Failed!\n");
    }

    return rc;
}

mlxCfgStatus MlxCfg::devRawCfg(RawTlvMode mode)
{
    Commander* commander = NULL;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);
        // open file
        std::ifstream ifs(_mlxParams.rawTlvFile.c_str());
        if (ifs.fail())
        {
            delete commander;
            return err(true, "Failed to open file: %s", _mlxParams.rawTlvFile.c_str());
        }
        std::vector<std::vector<u_int32_t>> rawTlvsAsDw;
        rawTlvsAsDw.resize(0);
        // Check file Sig
        std::string startLine;
        std::getline(ifs, startLine);
        if (startLine != MLNX_RAW_TLV_FILE_SIG)
        {
            delete commander;
            return err(true, "Invalid raw TLV file header.");
        }
        // parse the rest of the Lines
        int lineIdx = 1;
        for (std::string line; std::getline(ifs, line); lineIdx++)
        {
            std::vector<u_int32_t> rawTlvVec;
            if (line.empty() || line[0] == '%')
            { // comment - skip
                continue;
            }
            // convert line to DW
            if (tlvLine2DwVec(line, rawTlvVec))
            {
                delete commander;
                return err(true, "Failed to parse Raw TLV at line %d: %s", lineIdx, _errStr.c_str());
            }
            rawTlvsAsDw.push_back(rawTlvVec);
        }
        ifs.close();
        // dump raw TLVs from the file
        std::string dumpStr;
        int tlvIdx = 1;
        if (mode == SET_RAW)
        {
            for (std::vector<std::vector<u_int32_t>>::iterator it = rawTlvsAsDw.begin(); it != rawTlvsAsDw.end();
                 it++, tlvIdx++)
            {
                commander->dumpRawCfg(*it, dumpStr);
                printf("Raw TLV #%d Info:\n%s\n", tlvIdx, dumpStr.c_str());
            }
        }
        // ask user
        if (mode == SET_RAW)
        {
            if (!askUser("Operation intended for advanced users.\n "
                         "Are you sure you want to apply raw TLV file?"))
            {
                printErr();
                delete commander;
                return MLX_CFG_ABORTED;
            }
            printf("Applying... ");
        }
        tlvIdx = 1;
        // set each of the raw TLVs
        std::vector<u_int32_t> queryData;
        for (std::vector<std::vector<u_int32_t>>::iterator it = rawTlvsAsDw.begin(); it != rawTlvsAsDw.end();
             it++, tlvIdx++)
        {
            if (mode == SET_RAW)
            {
                commander->setRawCfg(*it);
            }
            else
            {
                queryData = commander->getRawCfg(*it);
                commander->dumpRawCfg(queryData, dumpStr);
                printf("Raw TLV #%d Info:\n%s\n", tlvIdx, dumpStr.c_str());
            }
        }
        // send mfrl command to fw
        // this command indicate to the fw that next time perst signal go down
        //[reboot] fw need to perform reset )
        commander->loadConfigurationGetStr();
    }
    catch (MlxcfgException& e)
    {
        delete commander;
        return err(true, "Failed to run %s command: %s", mode == SET_RAW ? "set_raw" : "get_raw", e._err.c_str());
    }
    if (commander != NULL)
    {
        delete commander;
    }
    // done successfully
    printf("Done!\n");
    if (mode == SET_RAW)
    {
        printf("-I- Please reboot machine to load new configurations.\n");
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::backupCfg(string deviceName)
{
    FILE* file;
    Commander* commander = NULL;
    vector<BackupView> views;

    try
    {
        commander = Commander::create(deviceName, _mlxParams.dbName, false, _mlxParams.deviceType, false);
        printf("Collecting...\n");
        commander->backupCfgs(views);
        delete commander;
    }
    catch (MlxcfgException& e)
    {
        printf(" Failed!\n");
        if (commander)
        {
            delete commander;
        }
        return err(true, "Failed to backup the configurations: %s", e._err.c_str());
    }

    // check if views empty
    if (views.empty())
    {
        printf("No TLVs were found.\n");
    }
    else
    {
        // open file
        printf("Saving output...\n");
        file = fopen(_mlxParams.rawTlvFile.c_str(), "w");
        if (file == NULL)
        {
            return err(true, "Failed to open file: %s", _mlxParams.rawTlvFile.c_str());
        }

        fprintf(file, "%s\n", MLNX_RAW_TLV_FILE_SIG);

        for (std::vector<BackupView>::iterator it = views.begin(); it != views.end(); it++)
        {
            // u_int32_t tlvType = it->type_index;
            // tlvType += it->type_class << 24;
            fprintf(file,
                    "%% TLV Type: 0x%08x, Writer ID: %s(0x%02x)"
                    ", Writer Host ID: 0x%02x\n",
                    it->type, writerIdToStr((WriterId)(it->writerId)).c_str(), it->writerId, it->writerHostId);
            vector<u_int8_t> v = it->tlvBin;
            for (size_t i = 0; i < v.size() / 4; i++)
            {
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
    char* p = NULL;
    std::istringstream isstm(tlvStringLine);
    while (isstm >> dwStr)
    {
        dw = strtoul(dwStr.c_str(), &p, 0);
        if (*p)
        {
            return err(false, "Input is not an unsigned number: %s", dwStr.c_str());
        }
        tlvVec.push_back(dw);
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::resetDevCfg(const char* dev)
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = createCommander(string(dev), false, false);
    if (!commander)
    {
        return MLX_CFG_ERROR;
    }

    try
    {
        if (_mlxParams.setParams.size() == 0)
        {
            commander->invalidateCfgs();
        }
        else
        {
            VECTOR_ITERATOR(ParamView, _mlxParams.setParams, p)
            {
                commander->invalidateCfg((*p).mlxconfigName);
            }
        }
        commander->loadConfigurationGetStr(); // why to call this? seems needless
    }
    catch (MlxcfgException& e)
    {
        err(false, "%s", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    delete commander;
    return rc;
}

mlxCfgStatus MlxCfg::showDevConfs()
{
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);
        printf("\nList of configurations the device %s may support:\n", _mlxParams.device.c_str());
        commander->printLongDesc(stdout);
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander)
    {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::readBinFile(string fileName, vector<u_int32_t>& buff)
{
    streampos size;

    std::ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);
    if (ifs.fail())
    {
        return err(true, "Failed to open file: %s", fileName.c_str());
    }
    size = ifs.tellg();
    if (size % 4 != 0)
    {
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
    if (ifs.fail())
    {
        return err(true, "Failed to open file: %s", _mlxParams.NVInputFile.c_str());
    }
    for (std::string line; std::getline(ifs, line);)
    {
        lines.push_back(line);
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::readNVInputFile(string& content)
{
    vector<string> lines;
    mlxCfgStatus rc = readNVInputFile(lines);
    if (rc != MLX_CFG_OK)
    {
        return rc;
    }

    VECTOR_ITERATOR(string, lines, l)
    {
        content += *l;
    }
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(vector<u_int32_t> content)
{
    FILE* file = fopen(_mlxParams.NVOutputFile.c_str(), "wb");
    if (!file)
    {
        return err(true, "Failed to open file: %s", _mlxParams.NVOutputFile.c_str());
    }
    for (u_int32_t i = 0; i < content.size() * 4; i += 4)
    {
        const size_t count = 4;
        size_t writtenCount = fwrite(((u_int8_t*)content.data()) + i, 1, count, file);
        if (writtenCount != count || ferror(file))
        {
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
    if (!file)
    {
        return err(true, "Failed to open file: %s", _mlxParams.NVOutputFile.c_str());
    }
    fprintf(file, "%s", content.c_str());
    fclose(file);
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::writeNVOutputFile(vector<string> lines)
{
    string content;
    VECTOR_ITERATOR(string, lines, l)
    {
        content += *l;
    }
    return writeNVOutputFile(content);
}

mlxCfgStatus MlxCfg::genTLVsFile()
{
    char buff[TLV_NAME_MAX_LENGTH];
    vector<string> tlvs;
    mlxCfgStatus rc = MLX_CFG_OK;

    try
    {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType);
        commander.genTLVsList(tlvs);
        VECTOR_ITERATOR(string, tlvs, it)
        {
            sprintf(buff, "%-50s0\n", it->c_str());
            (*it) = buff;
        }
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Saving output...\n");
        rc = writeNVOutputFile(tlvs);
        if (rc == MLX_CFG_OK)
        {
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

    VECTOR_ITERATOR(string, lines, line)
    {
        string tlvName;
        string tLine = mlxcfg_trim(*line);
        for (unsigned i = 0; i < tLine.size(); i++)
        {
            if (tLine[i] != ' ' && tLine[i] != '\t')
            {
                tlvName += tLine[i];
            }
            else
            {
                while ((tLine[i] == ' ' || tLine[i] == '\t') && (++i < tLine.size()))
                {
                };
                if ((i == tLine.size()) || (tLine[i] != '0' && tLine[i] != '1') || (i != tLine.size() - 1) ||
                    tlvName.empty())
                {
                    PRINT_SYNTAX_ERROR_AND_EXIT
                }
                if (tLine[i] == '1')
                {
                    tlvs.push_back(tlvName);
                }
                break;
            }
        }
        if (tlvName == tLine)
        {
            PRINT_SYNTAX_ERROR_AND_EXIT
        }
    }

    if (tlvs.size() == 0)
    {
        printf("-E- Empty TLV configurations file was provided or no TLV configurations were selected.\n");
        return MLX_CFG_ERROR;
    }

    try
    {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType);
        commander.genXMLTemplate(tlvs, xmlTemplate, _mlxParams.allAttrs);
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Saving output...\n");
        rc = writeNVOutputFile(xmlTemplate);
        if (rc == MLX_CFG_OK)
        {
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

    if (isBin)
    {
        rc = readNVInputFile(buff);
    }
    else
    {
        rc = readNVInputFile(lines);
    }
    EXIT_IF_RC_NOT_OK(rc)

    try
    {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType);
        if (isBin)
        {
            // commander.bin2XML(buff, xmlTemplate);
        }
        else
        {
            if (lines.size() == 0)
            {
                fprintf(stderr, "-E- Empty file was provided\n");
                rc = MLX_CFG_ERROR;
            }
            else
            {
                commander.raw2XML(lines, xmlTemplate);
            }
        }
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Saving output...\n");
        rc = writeNVOutputFile(xmlTemplate);
        if (rc == MLX_CFG_OK)
        {
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

    try
    {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType);
        if (isBin)
        {
            commander.XML2Bin(xml, binBuff, false);
        }
        else
        {
            commander.XML2Raw(xml, raw);
        }
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Saving output...\n");
        if (isBin)
        {
            rc = writeNVOutputFile(binBuff);
        }
        else
        {
            rc = writeNVOutputFile(raw);
        }
        if (rc == MLX_CFG_OK)
        {
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

    try
    {
        GenericCommander commander(NULL, _mlxParams.dbName, _mlxParams.deviceType);
        commander.createConf(xml, buff);

        if (!_mlxParams.privPemFile.empty() && !_mlxParams.keyPairUUID.empty())
        {
            commander.sign(buff, _mlxParams.privPemFile, _mlxParams.keyPairUUID);
        }
        else
        {
            commander.sign(buff);
        }
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Saving output...\n");
        rc = writeNVOutputFile(buff);
        if (rc == MLX_CFG_OK)
        {
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
    Commander* commander = NULL;
    mlxCfgStatus rc = MLX_CFG_OK;

    rc = readNVInputFile(buff);
    EXIT_IF_RC_NOT_OK(rc)

    copyDwVectorToBytesVector(buff, bytesBuff);

    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, true, _mlxParams.deviceType, false);
        printf("Applying...\n");
        ((GenericCommander*)commander)->apply(bytesBuff);
    }
    catch (MlxcfgException& e)
    {
        printf("-E- %s\n", e._err.c_str());
        rc = MLX_CFG_ERROR;
    }

    if (commander != NULL)
    {
        delete commander;
    }

    if (rc == MLX_CFG_OK)
    {
        printf("Done!\n");
    }

    return rc;
}

mlxCfgStatus MlxCfg::getChallenge()
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = nullptr;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, true, _mlxParams.deviceType, false);
        MlxCfgToken token(commander->mf());

        token.GetAndPrintChallenge(_mlxParams.tokenChallengeID, false);
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err.c_str() << endl;
        rc = MLX_CFG_ERROR;
    }
    if (commander)
    {
        delete commander;
    }
    return rc;
}

mlxCfgStatus MlxCfg::remoteTokenKeepAlive()
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = nullptr;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);

        if (dm_is_ib_access(commander->mf()) == 0) // not IB device
        {
            throw MlxcfgException("specified device is not an IB device");
        }

        MlxCfgToken token(commander->mf());
        token.RemoteTokenKeepAlive(_mlxParams.sessionId,
                                   _mlxParams.sessionTimeInSec,
                                   _mlxParams.isSleepTimeBetweenCommandsInput,
                                   _mlxParams.keepAliveSleepTimeBetweenCommands,
                                   _mlxParams.isSleepTimeOnCommandTOInput,
                                   _mlxParams.keepAliveSleepTimeOnCommandTO);

        printf("Keep alive session has ended successfully.\n");
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err.c_str() << endl;
        rc = MLX_CFG_ERROR;
    }
    if (commander)
    {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::queryTokenSupport()
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = nullptr;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);

        MlxCfgToken token(commander->mf());
        token.QueryTokenSupport();
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err.c_str() << endl;
        rc = MLX_CFG_ERROR;
    }
    if (commander)
    {
        delete commander;
    }
    return rc;
}

mlxCfgStatus MlxCfg::queryTokenSession()
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = nullptr;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);
        MlxCfgToken token(commander->mf());
        token.QueryTokenSession(_mlxParams.tokenStatusID);
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err.c_str() << endl;
        rc = MLX_CFG_ERROR;
    }
    if (commander)
    {
        delete commander;
    }
    return rc;
}

mlxCfgStatus MlxCfg::endTokenSession()
{
    mlxCfgStatus rc = MLX_CFG_OK;
    Commander* commander = nullptr;
    try
    {
        commander = Commander::create(_mlxParams.device, _mlxParams.dbName, false, _mlxParams.deviceType, false);
        MlxCfgToken token(commander->mf());
        token.EndTokenSession(_mlxParams.tokenStatusID);
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err.c_str() << endl;
        rc = MLX_CFG_ERROR;
    }
    if (commander)
    {
        delete commander;
    }

    return rc;
}

mlxCfgStatus MlxCfg::showSystemConf()
{
    Commander* commander = createCommander(_mlxParams.device, false, true);
    if (!commander)
    {
        return MLX_CFG_ERROR;
    }

    try
    {
        const char* deviceName = getDeviceName(commander->mf());

        // Show all configurations available for this device (already grouped by name)
        std::map<std::string, std::vector<std::shared_ptr<SystemConfiguration>>> configs =
          commander->getAllSystemConfigurations(deviceName);

        if (configs.empty())
        {
            cout << "No system configurations available for device " << deviceName << endl;
            delete commander;
            return MLX_CFG_OK;
        }
        cout << "System configurations available for " << deviceName << " devices:" << endl << endl;

        for (const auto& entry : configs)
        {
            cout << "Configuration name: " << entry.first << endl;
            cout << "--------------------------------" << endl;
            for (const auto& config : entry.second)
            {
                cout << "\tASIC[" << config->asicNumber << "] Description: " << endl;
                cout << "\t\t" << config->parametersString << endl;
            }
        }
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err << endl;
        delete commander;
        return MLX_CFG_ERROR;
    }

    delete commander;
    return MLX_CFG_OK;
}

bool isAggregatedDevice(const string& device)
{
    return device.find("_pciconf_agg_") != string::npos;
}

// Returns list of (device_name, ga) pairs from an aggregated device file
static std::vector<std::pair<std::string, int>> getAggregatedDeviceList(const std::string& aggregatedDevice)
{
    std::vector<std::pair<std::string, int>> devices;

    // Parse JSON array: [{"device": "name", "ga": 0}, ...]
	Json::Value root;
    ifstream jsonInputStream(aggregatedDevice);
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    bool rc = parseFromStream(builder, jsonInputStream, &root, &errs);
    jsonInputStream.close();
	if (!rc)
    {
        cerr << "-E- Failed to parse aggregated device file: " << aggregatedDevice << endl;
        return devices;
    }

    if (!root.isArray())
    {
        cerr << "-E- Invalid aggregated device file format (expected array)" << endl;
        return devices;
    }

    for (const auto& entry : root)
    {
        if (!entry.isObject() || !entry.isMember("device") || !entry.isMember("ga"))
        {
            cerr << "-W- Skipping invalid entry in aggregated device file" << endl;
            continue;
        }
        std::string deviceName = entry["device"].asString();
        int ga = entry["ga"].asInt();
        devices.push_back(std::make_pair(deviceName, ga));
    }

    return devices;
}

mlxCfgStatus MlxCfg::parseParametersString(const std::string& parametersString, std::vector<ParamView>& outParams)
{
    // Save current setParams
    std::vector<ParamView> savedParams = _mlxParams.setParams;
    _mlxParams.setParams.clear();

    // Convert string to argc/argv format
    std::vector<std::string> tokens;
    std::istringstream iss(parametersString);
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }

    // Create argv array
    std::vector<char*> argv;
    for (auto& t : tokens)
    {
        argv.push_back(&t[0]);
    }

    // Call extractSetCfgArgs
    mlxCfgStatus rc = extractSetCfgArgs((int)argv.size(), argv.data());

    // Get the result
    outParams = _mlxParams.setParams;

    // Restore original setParams
    _mlxParams.setParams = savedParams;

    return rc;
}

// gets the list of devices (pairs of device_name and ga) from an aggregated device file
// and validates it matches the requested configuration.
mlxCfgStatus MlxCfg::getAggregatedDeviceConfigs(const std::string& confName,
                                                const int confAsic,
                                                std::vector<std::pair<std::string, int>>& devList)
{
    if (confAsic != -1)
    {
        cerr << "-E- Using aggregated device requires full system configuration name without specifying the asic in []"
             << endl;
        return MLX_CFG_ERROR;
    }

    // 1. Get list of devices (pairs of device_name and ga)
    devList = getAggregatedDeviceList(_mlxParams.device);
    if (devList.empty())
    {
        cerr << "-E- No devices found in aggregated device" << endl;
        return MLX_CFG_ERROR;
    }

    // 2. Create commander from the first device
    Commander* commander = createCommander(devList[0].first, false, true);
    if (!commander)
    {
        return MLX_CFG_ERROR;
    }

    // 3. Get the list of system configurations by confName and validate count
    std::vector<std::shared_ptr<SystemConfiguration>> configs =
      commander->getSystemConfigurationsByName(confName, getDeviceName(commander->mf()));
    if (configs.empty())
    {
        cerr << "-E- System configuration '" << confName << "' not found" << endl;
        delete commander;
        return MLX_CFG_ERROR;
    }

    // 4. Make sure size of the configuration list matches the size of the list of devices
    if (configs.size() != devList.size())
    {
        cerr << "-E- Configuration has " << configs.size() << " asic entries but found " << devList.size() << " devices"
             << endl;
        delete commander;
        return MLX_CFG_ERROR;
    }
    delete commander;

    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::setSystemConf()
{
    // check if we are running on a single device or an aggregated device.
    // if single device, conf should be of format <name>_<asic>
    // if aggregated device, conf should be of format <name>
    string confName = "";
    int confAsic = -1;
    mlxCfgStatus rc = MLX_CFG_OK;
    parseSystemConfName(_mlxParams.systemConfName, confName, confAsic);

    if (isAggregatedDevice(_mlxParams.device))
    {
        std::vector<std::pair<std::string, int>> devList;
        rc = getAggregatedDeviceConfigs(confName, confAsic, devList);
        if (rc != MLX_CFG_OK)
        {
            return rc;
        }

        // For each device, apply the corresponding configuration (matched by ga -> asicNumber)
        int failedDevices = 0;
        for (const auto& devEntry : devList)
        {
            const std::string& mstDevicePath = devEntry.first;
            int ga = devEntry.second;

            rc = setSingleDeviceSystemConf(mstDevicePath, confName, ga, true);
            if (rc != MLX_CFG_OK)
            {
                cerr << "-E- Failed to apply configuration to device " << mstDevicePath << endl;
                failedDevices++;
                break;
            }
        }
        if (failedDevices > 0)
        {
            return MLX_CFG_ERROR;
        }

        // 6. if finished successfully, ask if user want to reboot each device now.
        for (const auto& devEntry : devList)
        {
            rebootDevice(devEntry.first);
        }
    }
    else
    {
        // Single device case
        if (confAsic == -1)
        {
            cerr << "-E- Using single device requires specifying system configuration name and asic in the format "
                    "<conf_name>[asic_number]"
                 << endl;
            return MLX_CFG_ERROR;
        }
        rc = setSingleDeviceSystemConf(_mlxParams.device, confName, confAsic, false);
        if (rc != MLX_CFG_OK)
        {
            cerr << "-E- Failed to apply configuration to device " << _mlxParams.device << endl;
            return rc;
        }

        // 6. ask if user want to reboot now.
        rebootDevice(_mlxParams.device);
    }
    return rc;
}

mlxCfgStatus MlxCfg::setSingleDeviceSystemConf(const std::string& mstDevicePath,
                                               const std::string& confName,
                                               int confAsic,
                                               bool shouldBackup)
{
    mlxCfgStatus rc = MLX_CFG_OK;
    string backupDeviceName = _mlxParams.device;
    _mlxParams.device = mstDevicePath;

    if (shouldBackup)
    {
        // before applying the configuration, we want to run a backup command to a temp file.
        // Extract just the device name from the path (after the last '/')
        string devNameOnly = mstDevicePath;
        size_t lastSlash = mstDevicePath.rfind('/');
        if (lastSlash != string::npos)
        {
            devNameOnly = mstDevicePath.substr(lastSlash + 1);
        }
        _mlxParams.rawTlvFile = getTempFolder() + "mlxconfig_backup_" + devNameOnly + ".bck.cfg";
        printf("Backing up current configuration to temp file: %s\n", _mlxParams.rawTlvFile.c_str());
        backupCfg(mstDevicePath);
    }

    Commander* commander = createCommander(mstDevicePath, false, true);
    if (!commander)
    {
        _mlxParams.device = backupDeviceName;
        return MLX_CFG_ERROR;
    }

    // For system configuration, ignore FW write support check to allow writing anyway
    commander->setIgnoreWriteSupport(true);
    string devName = getDeviceName(commander->mf());
    std::shared_ptr<SystemConfiguration> config = commander->getSystemConfiguration(confName, confAsic, devName);
    if (!config)
    {
        cerr << "-E- System configuration '" << confName << "' with asic " << confAsic << " not found" << endl;
        delete commander;
        _mlxParams.device = backupDeviceName;
        return MLX_CFG_ERROR;
    }

    printf("Applying configuration '%s' (asic %d) to device %s...\n", confName.c_str(), confAsic,
           mstDevicePath.c_str());

    std::vector<ParamView> setParams;
    if (parseParametersString(config->parametersString, setParams) != MLX_CFG_OK)
    {
        delete commander;
        _mlxParams.device = backupDeviceName;
        return MLX_CFG_ERROR;
    }

    _mlxParams.setParams = setParams;
    rc = setDevCfgWithParams(commander, _mlxParams.setParams);
    delete commander;

    _mlxParams.device = backupDeviceName;
    return rc;
}

mlxCfgStatus
  MlxCfg::validateSingleDeviceSystemConf(const std::string& mstDevicePath, const std::string& confName, int confAsic)
{
    // Save and set device name
    string backupDeviceName = _mlxParams.device;
    _mlxParams.device = mstDevicePath;

    Commander* commander = createCommander(mstDevicePath, false, true);
    if (!commander)
    {
        _mlxParams.device = backupDeviceName;
        return MLX_CFG_ERROR;
    }

    try
    {
        // 1. Get the configuration from the database
        std::shared_ptr<SystemConfiguration> config =
          commander->getSystemConfiguration(confName, confAsic, getDeviceName(commander->mf()));
        if (!config)
        {
            cerr << "-E- System configuration '" << confName << "' with asic " << confAsic << " not found" << endl;
            delete commander;
            _mlxParams.device = backupDeviceName;
            return MLX_CFG_ERROR;
        }

        // 2. Parse the parameters_string to get expected ParamViews
        std::vector<ParamView> expectedParams;
        mlxCfgStatus rc = parseParametersString(config->parametersString, expectedParams);
        if (rc != MLX_CFG_OK)
        {
            cerr << "-E- Failed to parse configuration parameters" << endl;
            delete commander;
            _mlxParams.device = backupDeviceName;
            return MLX_CFG_ERROR;
        }

        // 3. Query the device's next boot configuration for these parameters
        // Query each parameter individually to handle failures gracefully
        std::vector<ParamView> queriedParams;
        std::vector<std::string> skippedParams;
        for (auto& param : expectedParams)
        {
            try
            {
                std::vector<ParamView> singleParam = {param};
                commander->queryParamViews(singleParam, false, QueryNext);
                queriedParams.push_back(singleParam[0]);
            }
            catch (...)
            {
                skippedParams.push_back(param.mlxconfigName);
            }
        }

        // 4. Compare and report differences
        cout << "Validating system configuration '" << confName << "[" << confAsic << "]' on device " << mstDevicePath
             << endl;
        cout << "------------------------------------------------------------------------" << endl;

        bool allMatch = true;
        for (auto& queriedParam : queriedParams)
        {
            // Get actual device value (from query)
            u_int32_t actualVal = queriedParam.val;
            std::string actualStrVal = queriedParam.strVal;

            // Convert expected setVal to numeric value using updateParamViewValue
            std::string expectedSetVal = queriedParam.setVal;
            ParamView expectedParam = queriedParam; // Copy to get same TLV context
            commander->updateParamViewValue(expectedParam, expectedSetVal, QueryNext);
            u_int32_t expectedVal = expectedParam.val;
            std::string expectedStrVal = expectedParam.strVal; // strVal is set by updateParamViewValue

            if (expectedVal != actualVal)
            {
                allMatch = false;
                // If strVal wasn't set properly, try hex format if actual is hex
                if (expectedStrVal.empty() || expectedStrVal == expectedSetVal)
                {
                    if (actualStrVal.size() >= 2 && actualStrVal.substr(0, 2) == "0x")
                    {
                        std::stringstream ss;
                        ss << "0x" << std::hex << expectedVal;
                        expectedStrVal = ss.str();
                    }
                    else
                    {
                        expectedStrVal = expectedSetVal;
                    }
                }
                cout << "  MISMATCH: " << queriedParam.mlxconfigName << "\tExpected: " << expectedStrVal
                     << "\tActual: " << actualStrVal << endl;
            }
            else
            {
                cout << "  OK:       " << queriedParam.mlxconfigName << " = " << actualStrVal << endl;
            }
        }

        // Report skipped parameters
        if (!skippedParams.empty())
        {
            cout << endl;
            cout << "  SKIPPED (failed to query):" << endl;
            for (const auto& paramName : skippedParams)
            {
                cout << "    - " << paramName << endl;
            }
        }

        cout << "------------------------------------------------------------------------" << endl;
        if (allMatch)
        {
            cout << "Result: Device configuration MATCHES the system configuration." << endl;
        }
        else
        {
            cout << "Result: Device configuration does NOT match the system configuration." << endl;
        }

        delete commander;
        _mlxParams.device = backupDeviceName;
        return allMatch ? MLX_CFG_OK : MLX_CFG_ERROR;
    }
    catch (MlxcfgException& e)
    {
        cerr << "-E- " << e._err << endl;
        delete commander;
        _mlxParams.device = backupDeviceName;
        return MLX_CFG_ERROR;
    }
}

mlxCfgStatus MlxCfg::validateSystemConf()
{
    string confName = "";
    int confAsic = -1;
    mlxCfgStatus rc = MLX_CFG_OK;
    parseSystemConfName(_mlxParams.systemConfName, confName, confAsic);

    if (isAggregatedDevice(_mlxParams.device))
    {
        std::vector<std::pair<std::string, int>> devList;
        rc = getAggregatedDeviceConfigs(confName, confAsic, devList);
        if (rc != MLX_CFG_OK)
        {
            return rc;
        }

        // Validate each device
        cout << "Validating system configuration '" << confName << "' on aggregated device" << endl;
        cout << "=========================================================================" << endl;

        int failedDevices = 0;
        for (const auto& devEntry : devList)
        {
            const std::string& mstDevicePath = devEntry.first;
            int ga = devEntry.second;

            cout << endl;
            rc = validateSingleDeviceSystemConf(mstDevicePath, confName, ga);
            if (rc != MLX_CFG_OK)
            {
                failedDevices++;
            }
        }

        cout << endl;
        cout << "=========================================================================" << endl;
        if (failedDevices > 0)
        {
            cout << "Overall Result: " << failedDevices << " out of " << devList.size()
                 << " devices do NOT match the configuration." << endl;
            return MLX_CFG_ERROR;
        }
        else
        {
            cout << "Overall Result: All " << devList.size() << " devices match the configuration." << endl;
            return MLX_CFG_OK;
        }
    }
    else
    {
        // Single device case
        if (confAsic == -1)
        {
            cerr << "-E- Using single device requires specifying system configuration name and asic in the format "
                    "<conf_name>[asic_number]"
                 << endl;
            return MLX_CFG_ERROR;
        }
        return validateSingleDeviceSystemConf(_mlxParams.device, confName, confAsic);
    }
}

mlxCfgStatus MlxCfg::execute(int argc, char* argv[])
{
    mlxCfgStatus rc = parseArgs(argc, argv);
    if (rc)
    {
        if (rc == MLX_CFG_OK_EXIT)
        {
            rc = MLX_CFG_OK;
        }
        else if (rc != MLX_CFG_ERROR_NO_USAGE)
        {
            printUsage();
        }
        return rc;
    }



    switch (_mlxParams.cmd)
    {
        case Mc_ShowConfs:
            rc = showDevConfs();
            break;

        case Mc_Query:
            rc = queryDevsCfg();
            break;

        case Mc_Set:
            rc = setDevCfg();
            break;

        case Mc_Reset:
            rc = resetDevsCfg();
            break;

        case Mc_Clr_Sem:
            rc = clrDevSem();
            break;

        case Mc_Set_Raw:
            rc = devRawCfg(SET_RAW);
            break;

        case Mc_Get_Raw:
            rc = devRawCfg(GET_RAW);
            break;

        case Mc_Backup:
            rc = backupCfg(_mlxParams.device);
            break;

        case Mc_GenTLVsFile:
            rc = genTLVsFile();
            break;

        case Mc_GenXMLTemplate:
            rc = genXMLTemplate();
            break;

        case Mc_Raw2XML:
            rc = raw2XML();
            break;

        case Mc_XML2Raw:
            rc = XML2Raw();
            break;

        case Mc_XML2Bin:
            rc = XML2Bin();
            break;
        case Mc_CreateConf:
            rc = createConf();
            break;
        case Mc_Apply:
            rc = apply();
            break;
        case Mc_RemoteTokenKeepAlive:
            rc = remoteTokenKeepAlive();
            break;
        case Mc_ChallengeRequest:
            rc = getChallenge();
            break;
        case Mc_TokenSupported:
            rc = queryTokenSupport();
            break;
        case Mc_QueryTokenSession:
            rc = queryTokenSession();
            break;
        case Mc_EndTokenSession:
            rc = endTokenSession();
            break;
        case Mc_ShowSystemConf:
            rc = showSystemConf();
            break;
        case Mc_SetSystemConf:
            rc = setSystemConf();
            break;
        case Mc_ValidateSystemConf:
            rc = validateSystemConf();
            break;
        default:
            // should not reach here.
            return err(true, "invalid command.");
    }

    if (rc == MLX_CFG_OK_EXIT)
    {
        rc = MLX_CFG_OK;
    }
    return rc;
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
