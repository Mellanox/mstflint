/*
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

#include "mlxlink_err_inj_commander.h"

MlxlinkErrInjCommander::MlxlinkErrInjCommander(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _mixerOffset0 = -1;
    _mixerOffset1 = -1;
    _force = false;
}

MlxlinkErrInjCommander::~MlxlinkErrInjCommander() {}

bool MlxlinkErrInjCommander::getUserConfirm(const string& msg)
{
    MlxlinkRecord::printWar(msg, _jsonRoot);
    return askUser("Do you want to continue", _force);
}

u_int16_t MlxlinkErrInjCommander::getMixerOffset(u_int32_t id)
{
    sendPrmReg(ACCESS_REG_PREI, GET);

    return getFieldValue("mixer_offset" + to_string(id));
}

void MlxlinkErrInjCommander::setMixersOffset()
{
    u_int16_t mixer0 = getMixerOffset(0);
    u_int16_t mixer1 = getMixerOffset(1);

    if (_mixerOffset0 >= 0)
    {
        mixer0 = (u_int16_t)_mixerOffset0;
    }

    if (_mixerOffset1 >= 0)
    {
        mixer1 = (u_int16_t)_mixerOffset1;
    }

    sendPrmReg(ACCESS_REG_PREI, SET, "mixer_offset0=%d,mixer_offset1=%d", mixer0, mixer1);
}

void MlxlinkErrInjCommander::updateMixerOffsets()
{
    MlxlinkRecord::printCmdLine("Configuring Eye Center", _jsonRoot);
    if (MlxlinkRecord::jsonFormat && !_force)
    {
        throw MlxRegException("Interactive mode is not available with JSON format, "
                              "use --yes flag to force the execution");
    }
    if (getUserConfirm("Using this feature may result degradation of "
                       "the link or even link failure.\nFor the link to return to normal "
                       "operation, link needs to be toggled."))
    {
        setMixersOffset();
    }
}

void MlxlinkErrInjCommander::showMixersOffset()
{
    MlxlinkCmdPrint cmdOut = MlxlinkCmdPrint();
    setPrintTitle(cmdOut, "Eye Centering Control Information", 2);
    char valueStr[32];
    sprintf(valueStr, "0x%x", getMixerOffset(0));
    setPrintVal(cmdOut, "mixer_offset0", valueStr, ANSI_COLOR_RESET, true);
    sprintf(valueStr, "0x%x", getMixerOffset(1));
    setPrintVal(cmdOut, "mixer_offset1", valueStr, ANSI_COLOR_RESET, true);
    cmdOut.toJsonFormat(_jsonRoot);
    cout << cmdOut;
}

string MlxlinkErrInjCommander::getPcieErrInjStatus(u_int32_t errorType)
{
    string status = "Ready";

    if (errorType)
    {
        status = "In Progress";
    }
    return status;
}

void MlxlinkErrInjCommander::showPcieErrInjState(const DPN& dpn)
{
    sendPrmReg(ACCESS_REG_MPEINJ, GET, "depth=%d,pcie_index=%d,node=%d,error_type=%d", dpn.depth, dpn.pcieIndex,
               dpn.node, PCIE_ERR_TYPE_BAD_DLLP_LCRC);

    u_int32_t errType = getFieldValue("error_type");
    string errorStatus = getPcieErrInjStatus(errType);
    string errorTypeStr = _mlxlinkMaps->_pcieErrType[errType].errorTypeStr;
    string errorDuration = getFieldStr("error_duration");
    errorDuration += " " + _mlxlinkMaps->_pcieErrType[errType].unit;
    errorDuration += getFieldValue("error_duration") > 1 ? "s" : "";

    MlxlinkCmdPrint cmdOut = MlxlinkCmdPrint();

    setPrintTitle(cmdOut, "PCIe Error Injection Info", 4);

    setPrintVal(cmdOut, "Error Injection Status", errorStatus);
    setPrintVal(cmdOut, "Error Injection Type", errorTypeStr, ANSI_COLOR_RESET, true, errType);
    setPrintVal(cmdOut, "Error Injection Duration", errorDuration, ANSI_COLOR_RESET, true, errType);

    cmdOut.toJsonFormat(_jsonRoot);

    cout << cmdOut;
}

string MlxlinkErrInjCommander::getValidErrorTypes(bool perDbdf)
{
    string errTypeListStr = "";

    for (const auto& errType : _mlxlinkMaps->_pcieErrType)
    {
        if (!errType.second.errorTypeStr.empty())
        {
            if (errType.second.dbdfValid || !perDbdf)
            {
                errTypeListStr += errType.second.errorTypeStr;
                errTypeListStr += "(" + to_string(errType.first);
                errTypeListStr += "),";
            }
        }
    }

    return deleteLastChar(errTypeListStr);
}

string MlxlinkErrInjCommander::getNumOfValidParams(PcieErrType& errTypeSt)
{
    u_int32_t numOfParams = 0;

    for (const auto& paramValid : errTypeSt.paramsValid)
    {
        if (paramValid)
        {
            numOfParams++;
        }
    }

    if (numOfParams)
    {
        return "Number of valid parameters is " + to_string(numOfParams);
    }
    else
    {
        return "No valid parameters to set";
    }
}

ReqParms MlxlinkErrInjCommander::validateErrType(const string& type,
                                                 int duration,
                                                 int injDelay,
                                                 vector<string> params,
                                                 const string& dbdf)
{
    ReqParms request;

    // Error type validation
    int errTypeSet = -1;
    int dbdfIntSet = 0;
    int paramsSet[4] = {0};

    try
    {
        size_t cptr;
        errTypeSet = stoi(type, &cptr, 0);
        if (cptr != type.size())
        {
            errTypeSet = -1;
        }
    }
    catch (...)
    {
        for (const auto& errType : _mlxlinkMaps->_pcieErrType)
        {
            if (type == errType.second.errorTypeStr)
            {
                errTypeSet = errType.first;
            }
        }
    }

    if (errTypeSet < 0)
    {
        string suggestion = "";
        size_t cost = SIZE_MAX;
        for (const auto& errType : _mlxlinkMaps->_pcieErrType)
        {
            if (!errType.second.errorTypeStr.empty())
            {
                size_t leveCost = LevStrMatch(type, errType.second.errorTypeStr);
                if (leveCost < cost)
                {
                    suggestion = errType.second.errorTypeStr;
                    cost = leveCost;
                }
            }
        }
        if (type.size() <= suggestion.size())
        {
            suggestion = ", do you mean \"" + suggestion + string("\"?\n");
        }
        else
        {
            suggestion = ". ";
        }

        throw MlxRegException("Invalid Error Type %s%sValid error types are [%s]", type.c_str(), suggestion.c_str(),
                              getValidErrorTypes().c_str());
    }
    request.errorType = (u_int32_t)errTypeSet;

    // Error duration validity check
    PcieErrType errTypeSt = _mlxlinkMaps->_pcieErrType[errTypeSet];

    request.errorDuration = errTypeSt.defaultErrDuration;
    request.injectionDelay = errTypeSt.defaultInjDelay;

    if (duration != -1 && !errTypeSt.errorDurationValid)
    {
        throw MlxRegException("The error_duration flag is not valid with error type %s",
                              errTypeSt.errorTypeStr.c_str());
    }
    else if (duration != -1)
    {
        if (((u_int32_t)duration) > errTypeSt.maxErrDuration && ((u_int32_t)duration) < errTypeSt.defaultErrDuration)
        {
            throw MlxRegException("Invalid error duration value for %s: %d", errTypeSt.errorTypeStr.c_str(), duration);
        }
        request.errorDuration = (u_int32_t)duration;
    }

    // Error parameter validity check
    if (params.size() > PCIE_MAX_ERR_PARAM)
    {
        throw MlxRegException("Invalid error parameters set for error type %s. %s",
                              errTypeSt.errorTypeStr.c_str(),
                              getNumOfValidParams(errTypeSt).c_str());
    }
    for (u_int32_t idx = 0; idx < params.size(); idx++)
    {
        if (!errTypeSt.paramsValid[idx])
        {
            throw MlxRegException("Invalid parameters list for error type %s, %s", errTypeSt.errorTypeStr.c_str(),
                                  getNumOfValidParams(errTypeSt).c_str());
        }
        strToUint32((char*)params[idx].c_str(), (u_int32_t&)paramsSet[idx]);
    }

    if (request.errorType == PCIE_ERR_TYPE_UNEXPECTED_CPL && paramsSet[0] == 1 &&
        paramsSet[1] > PCIE_MAX_DURATION_HW_COUNTERS)
    {
        throw MlxRegException("Invalid error parameter value: %d", paramsSet[1]);
    }
    memcpy(request.parameters, paramsSet, sizeof(paramsSet));

    // dbdf validity check
    if (dbdf.empty() && errTypeSt.dbdfValid)
    {
        throw MlxRegException("The dbdf flag should be specified for error type %s", errTypeSt.errorTypeStr.c_str());
    }
    if (!dbdf.empty() && !errTypeSt.dbdfValid)
    {
        throw MlxRegException("The dbdf flag is not valid with error type %s, It's valid with error types [%s]",
                              errTypeSt.errorTypeStr.c_str(), getValidErrorTypes(true).c_str());
    }
    if (!dbdf.empty())
    {
        dbdfIntSet = getBDFInt(dbdf);
        if (dbdfIntSet == -1)
        {
            throw MlxRegException("Invalid dbdf address: %s", dbdf.c_str());
        }
    }
    request.dbdf = (u_int32_t)dbdfIntSet;

    // Injection delay validity check
    if (injDelay != -1)
    {
        if (injDelay > PCIE_MAX_DURATION)
        {
            throw MlxRegException("Invalid injection delay value for %s: %d", errTypeSt.errorTypeStr.c_str(), injDelay);
        }
        request.injectionDelay = (u_int32_t)injDelay;
    }

    return request;
}

void MlxlinkErrInjCommander::startPcieErrInj(const DPN& dpn,
                                             const string& type,
                                             int duration,
                                             int injDelay,
                                             const string& dbdf,
                                             vector<string> params)
{
    MlxlinkRecord::printCmdLine("Starting PCIe Error Injection...", _jsonRoot);

    ReqParms req = validateErrType(type, duration, injDelay, params, dbdf);

    if (MlxlinkRecord::jsonFormat && !_force)
    {
        throw MlxRegException("Interactive mode is not available with JSON format, "
                              "use --yes flag to force the execution");
    }

    if (getUserConfirm("PCIe error injection might cause a PCIe bus failures or a system hang"))
    {
        sendPrmReg(ACCESS_REG_MPEINJ, GET, "depth=%d,pcie_index=%d,node=%d", dpn.depth, dpn.pcieIndex, dpn.node);
        if (getFieldValue("error_type") && req.errorType != 0)
        {
            throw MlxRegException("There is a PCIe error injection process in progress!");
        }
        else
        {
            try
            {
                sendPrmReg(ACCESS_REG_MPEINJ, SET,
                           "depth=%d,pcie_index=%d,node=%d,error_type=%d,error_duration=%d,start_delay=%d,dest_bdf=%d,"
                           "error_params_0=%d,error_params_1=%d,error_params_2=%d,error_params_3=%d",
                           dpn.depth, dpn.pcieIndex, dpn.node, req.errorType, req.errorDuration, req.injectionDelay,
                           req.dbdf, req.parameters[0], req.parameters[1], req.parameters[2], req.parameters[3]);
            }
            catch (MlxRegException& exc)
            {
                throw MlxRegException("Invalid PCIe error injection configuration: %s", exc.what());
            }
        }
    }
}
