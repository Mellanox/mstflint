/*
 * Copyright (c) 2020-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "mlxlink_eye_opener.h"
#include "common/tools_time.h"

MlxlinkEyeOpener::MlxlinkEyeOpener(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _measureTime = -1;
    _eyeSel = -1;
    _numOfEyes = 0;
    _symWaiter = "-\\|/";
    _oneLaneScan = false;
    _oneEyeScan = false;
    scanIterations = MAX_ITERATION_SCAN_PCIE;

    initSlredMaps();
}

MlxlinkEyeOpener::~MlxlinkEyeOpener() {}

void MlxlinkEyeOpener::initSlredMaps()
{
    _measureTimeMap[MEASURE_10_SEC] = 10;
    _measureTimeMap[MEASURE_30_SEC] = 30;
    _measureTimeMap[MEASURE_60_SEC] = 60;
    _measureTimeMap[MEASURE_90_SEC] = 90;
    _measureTimeMap[MEASURE_120_SEC] = 120;
    _measureTimeMap[MEASURE_240_SEC] = 240;
    _measureTimeMap[MEASURE_480_SEC] = 480;
    _measureTimeMap[MEASURE_600_SEC] = 600;
    _measureTimeMap[MEASURE_900_SEC] = 900;

    _eyeSelctorMap[EYE_UP] = "UP";
    _eyeSelctorMap[EYE_MID] = "MID";
    _eyeSelctorMap[EYE_DOWN] = "DOWN";
    _eyeSelctorMap[EYE_ALL] = "ALL";

    _scanStatusMap[EYE_SCAN_NOT_PERFORMED] = "Eye scan was not performed";
    _scanStatusMap[UNSUPPORTED_SCAN_FOR_CURRENT_SPEED] = "Unsupported scan for current speed";
    _scanStatusMap[SYSTEM_BUSY] = "System busy";
    _scanStatusMap[PERFORMING_EYE_SCAN] = "Performing eye scan";
    _scanStatusMap[EYE_SCAN_COMPLETED] = "Eye scan completed";
    _scanStatusMap[ERROR_EYE_SCAN_NOT_COMPLETED] = "Error, eye scan not completed";

    _laneSpeedMap[SLRED_LANE_SPEED_QDR] = "QDR (10 Gb/s) / Gen3 (PCIe)";
    _laneSpeedMap[SLRED_LANE_SPEED_FDR10] = "FDR10 (10GE / 40GE) (10.3125 Gb/s)";
    _laneSpeedMap[SLRED_LANE_SPEED_FDR] = "FDR (56GE) (14.0625 Gb/s) / Gen4 (PCIe)";
    _laneSpeedMap[SLRED_LANE_SPEED_EDR] = "EDR (25GE / 50GE / 100GE) (25.78125 Gb/s) / Gen5 (PCIe)";
    _laneSpeedMap[SLRED_LANE_SPEED_HDR] = "HDR (50GE / 200GE / 400GE) (26.5625Gbd / 53.125Gb/s)";
}

void MlxlinkEyeOpener::setMeasureTime(u_int32_t measureTime)
{
    string timesStr = "";

    for (map<u_int32_t, u_int32_t>::iterator it = _measureTimeMap.begin(); it != _measureTimeMap.end(); it++)
    {
        if (it->second == measureTime)
        {
            _measureTime = it->first;
            break;
        }
        else
        {
            timesStr += to_string(it->second) + ",";
        }
    }

    if (_measureTime < 0)
    {
        string errorMsg = "Invalid measure time : " + to_string(measureTime);
        errorMsg += "\nValid measure times are [" + deleteLastChar(timesStr) + "]";
        throw MlxRegException(errorMsg);
    }
}

void MlxlinkEyeOpener::setEyeSel(const string& eyeSel)
{
    if (_pnat == PNAT_PCIE)
    {
        return;
    }
    string defaultEye = eyeSel;
    if (!eyeSel.empty())
    {
        if (!isPam4Speed)
        {
            throw MlxRegException("Eye selection valid for PAM4 only");
        }
    }
    else
    {
        defaultEye = "ALL";
    }
    string eyeList = "";
    for (map<u_int32_t, string>::iterator it = _eyeSelctorMap.begin(); it != _eyeSelctorMap.end(); it++)
    {
        if (it->second == defaultEye)
        {
            _eyeSel = it->first;
            break;
        }
        else
        {
            eyeList += it->second + ",";
        }
    }
    if (_eyeSel < 0)
    {
        string errorMsg = "Invalid eye : " + eyeSel;
        errorMsg += "\nValid eyes selection are [" + deleteLastChar(eyeList) + "]";
        throw MlxRegException(errorMsg);
    }
}

void MlxlinkEyeOpener::setNonInteractiveMode(bool force)
{
    _force = force;
}

void MlxlinkEyeOpener::initWarMsgs()
{
    MlxlinkRecord::printCmdLine("Reading the SerDes receive eye grades", _jsonRoot);
    MlxlinkRecord::printWar("Link measurement or configuration change using Eye Opening may"
                            " cause the link to fail and renegotiate.\nOn the PCI express port,"
                            " this may lead to link speed degradation or a system hang.",
                            _jsonRoot);
    MlxlinkRecord::printWar("Eye Opening is a tool to quickly obtain link quality evaluation.\n"
                            "It is not intended to replace extensive BER testing. the two evaluation mechanisms\n"
                            "should be used in conjunction to guarantee the desired link quality.",
                            _jsonRoot);

    u_int32_t eyeSelectTime = _measureTimeMap[_measureTime];
    u_int32_t totalEysScanTime = eyeSelectTime * (_eyeSel != MAX_NUMBER_OF_EYES ? 1 : MAX_NUMBER_OF_EYES);
    if (lane >= 0)
    {
        numOfLanes = 1;
    }
    scanIterations = (_pnat == PNAT_PCIE) ? MAX_ITERATION_SCAN_PCIE : MAX_ITERATION_SCAN_PORT;
    u_int32_t totalScan = totalEysScanTime * numOfLanes * scanIterations;
    char scanTitle[64];
    u_int32_t min = (u_int32_t)totalScan / 60;
    u_int32_t sec = (u_int32_t)totalScan % 60;
    if (min)
    {
        sprintf(scanTitle, "Estimated total scan time %02d minute\\s and %02d seconds", min, sec);
    }
    else
    {
        sprintf(scanTitle, "Estimated total scan time %02d seconds", sec);
    }
    MlxlinkRecord::printWar(scanTitle, _jsonRoot);
}

bool MlxlinkEyeOpener::isActiveGenSupported()
{
    sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", depth, pcieIndex, node);

    return (getFieldValue("link_speed_active") >= GEN3);
}

string MlxlinkEyeOpener::prepareSlred(u_int32_t lane, u_int32_t eye)
{
    string fields = "lane=" + to_string(lane);
    fields += ",measure_time=" + to_string(_measureTime);
    fields += ",err_res_scale=" + to_string(DFLT_ERR_RES_SCALE);
    fields += ",err_res_base=" + to_string(DFLT_ERR_RES_BASE);
    fields += ",eye_diag_dim=" + to_string((_pnat == PNAT_PCIE) ? DFLT_EYE_DIAG_DIM_PCIE : DFLT_EYE_DIAG_DIM_PORT);

    if (_pnat != PNAT_PCIE && isPam4Speed)
    {
        fields += ",eye_sel=" + to_string(eye);
    }

    return fields;
}

void MlxlinkEyeOpener::enableSlredGradeScan(u_int32_t lane, u_int32_t eye)
{
    string fields = prepareSlred(lane, eye);

    if ((_numOfEyes == EYE_ALL && eye == EYE_DOWN) || (_numOfEyes != EYE_ALL))
    {
        fields += ",last_scan=1";
    }

    sendPrmReg(ACCESS_REG_SLRED, SET, "en=%d,%s", 1, fields.c_str());
}

void MlxlinkEyeOpener::slredStopSignalHandler()
{
    if (mft_signal_is_fired())
    {
        string fields = prepareSlred(0, 0);
        sendPrmReg(ACCESS_REG_SLRED, SET, "abort=%d,%s", 1, fields.c_str());

        printf("\n\n");
        exit(1);
    }
}

void MlxlinkEyeOpener::getSlredMargin(u_int32_t iteration, u_int32_t lane, u_int32_t eye)
{
    string fields = prepareSlred(lane, eye);
    sendPrmReg(ACCESS_REG_SLRED, SET, fields.c_str());
    // put all margins in one vector for later calculations
    _measuredMargins.push_back(MarginInfo(lane, (_pnat != PNAT_PCIE && isPam4Speed) ? eye : 0, getFieldValue("margin"),
                                          getFieldValue("status"), getFieldValue("margin_version"), iteration));
}

// Get the status of scan for specific lane\eye
u_int32_t MlxlinkEyeOpener::getSlredStatus(u_int32_t lane, u_int32_t eye)
{
    string fields = prepareSlred(lane, eye);
    sendPrmReg(ACCESS_REG_SLRED, GET, fields.c_str());

    return getFieldValue("status");
}

string MlxlinkEyeOpener::getSlredLaneSpeedStr(u_int32_t lane, u_int32_t eye)
{
    string fields = prepareSlred(lane, eye);
    sendPrmReg(ACCESS_REG_SLRED, GET, fields.c_str());

    return _laneSpeedMap[getFieldValue("lane_speed")];
}

// Scan specific eye for specific lane with progress indicator
void MlxlinkEyeOpener::gradeEyeScanner(u_int32_t iteration, u_int32_t lane, u_int32_t eye)
{
    double measureTime = _measureTimeMap[_measureTime] + MAX_LM_TIME;
    u_int32_t currTime = 0;
    enableSlredGradeScan(lane, eye);
    // Throw error if the current speed not supported
    if (getSlredStatus(lane, eye) == UNSUPPORTED_SCAN_FOR_CURRENT_SPEED)
    {
        string errMsg = getSlredLaneSpeedStr(lane, eye).c_str();
        errMsg = errMsg.empty() ? activeSpeedStr : errMsg;
        errMsg = _scanStatusMap[UNSUPPORTED_SCAN_FOR_CURRENT_SPEED] + ": " + errMsg;
        throw MlxRegException(errMsg);
    }
    u_int32_t status = getSlredStatus(lane, eye);
    if (status != EYE_SCAN_COMPLETED)
    {
        while ((status == SYSTEM_BUSY || status == PERFORMING_EYE_SCAN) && (currTime < measureTime))
        {
            fprintf(MlxlinkRecord::stdOut, "\r");
            printField("Scanning status", "", false);
            msleep(1000);
            try
            {
                status = getSlredStatus(lane, eye);
            }
            catch (MlxRegException& exp)
            {
                continue;
            }
            currTime++;
            fprintf(MlxlinkRecord::stdOut, "In progress %c", _symWaiter.at(currTime % (_symWaiter.length())));
            fflush(MlxlinkRecord::stdOut);
            slredStopSignalHandler();
        }
    }
    getSlredMargin(iteration, lane, eye);
}

// scan all grades per lane
void MlxlinkEyeOpener::laneEyesScanner(u_int32_t iteration, u_int32_t lane)
{
    if (isPam4Speed && _eyeSel == MAX_NUMBER_OF_EYES && _pnat != PNAT_PCIE)
    {
        // scan all eyes
        for (u_int32_t i = 0; i < MAX_NUMBER_OF_EYES; i++)
        {
            gradeEyeScanner(iteration, lane, i);
            slredStopSignalHandler();
        }
    }
    else
    {
        // scan: specified eye, pcie margin, or NRZ scan
        gradeEyeScanner(iteration, lane, _eyeSel);
    }
}

void MlxlinkEyeOpener::printField(const string& key, const string& val, bool newLine)
{
    // for JSON format
    if (MlxlinkRecord::jsonFormat && newLine)
    {
        setPrintVal(_cmdOut, key, val, ANSI_COLOR_RESET, true, true, true);
    }
    *MlxlinkRecord::cOut << key << std::setw(PDDR_LINE_LEN - key.length()) << ": ";
    if (newLine)
    {
        *MlxlinkRecord::cOut << val << std::endl;
    }
}

void MlxlinkEyeOpener::printTitle(const string& title)
{
    *MlxlinkRecord::cOut << std::endl << title << std::endl;
    *MlxlinkRecord::cOut << std::string(title.length(), '-') << std::endl;
}

// eye scan is working for 16 nm devices only, and Gen4 pcie speeds
void MlxlinkEyeOpener::preChecks()
{
    if (MlxlinkRecord::jsonFormat && !_force)
    {
        throw MlxRegException("Interactive mode is not available with JSON format, "
                              "use --yes flag to force the execution");
    }

    if (version != PRODUCT_16NM)
    {
        throw MlxRegException("Device not supported!");
    }
    if (_pnat == PNAT_PCIE)
    {
        if (!isActiveGenSupported())
        {
            throw MlxRegException("The current link speed not supported (supports only Gen4)!");
        }
    }
    else
    {
        if (!isPam4Speed)
        {
            _eyeSel = -1;
        }
    }
    if (lane != -1)
    {
        if ((u_int16_t)lane > (numOfLanes - 1))
        {
            throw MlxRegException("Invalid lane index!");
        }
    }
}

MarginInfo MlxlinkEyeOpener::getMarginInfoFromVector(vector<MarginInfo>& margins,
                                                     u_int32_t iteration,
                                                     u_int32_t lane,
                                                     u_int32_t eye)
{
    MarginInfo found;
    vector<MarginInfo>::iterator it = margins.begin();
    for (; it != margins.end(); it++)
    {
        if (it->iteration == iteration && it->lane == lane && it->eye == eye)
        {
            found = *it;
        }
    }
    return found;
}

vector<MarginInfo> MlxlinkEyeOpener::calculateAvgMargins()
{
    u_int32_t value = 0;
    u_int32_t count = 0;
    u_int32_t status = EYE_SCAN_COMPLETED;
    u_int32_t version = 1;
    MarginInfo margin;
    /* Execute the loop over the selected lane(perLane) if onLaneScan selected,
     * else go over all lanes
     * Execute the loop over the selected eye(perEye) if _eyeSel >= 0,
     * else go over all lanes */
    u_int32_t perLane = _oneLaneScan ? (u_int32_t)this->lane : 0;
    u_int32_t perEye = _oneEyeScan ? (u_int32_t)_eyeSel : 0;
    for (u_int32_t lane = perLane; lane < numOfLanes || _oneLaneScan; lane++)
    {
        for (u_int32_t eye = perEye; eye < _numOfEyes || _oneEyeScan; eye++)
        {
            value = 0;
            count = 0;
            status = EYE_SCAN_COMPLETED;
            version = 1;
            for (u_int32_t i = 0; i < scanIterations; i++)
            {
                margin = getMarginInfoFromVector(_measuredMargins, i, lane, eye);
                if (margin.value != 0)
                {
                    value += margin.value;
                    count++;
                }
                else
                {
                    status = margin.status;
                    version = margin.version;
                }
            }
            _avgMargins.push_back(MarginInfo(lane, eye, count ? value / count : 0,
                                             count ? (u_int32_t)EYE_SCAN_COMPLETED : status,
                                             count ? (u_int32_t)FIGURE_OF_MERIT : version, 0));
            if (_oneEyeScan)
            {
                break;
            }
        }
        if (_oneLaneScan)
        {
            break;
        }
    }
    return _avgMargins;
}

void MlxlinkEyeOpener::printAvgMargins()
{
    bool valid = true;
    string val = "";
    MarginInfo margin;
    /* Execute the loop over the selected lane(perLane) if onLaneScan selected,
     * else go over all lanes
     * Execute the loop over the selected eye(perEye) if _eyeSel >= 0,
     * else go over all lanes */
    u_int32_t perLane = _oneLaneScan ? (u_int32_t)this->lane : 0;
    u_int32_t perEye = _oneEyeScan ? (u_int32_t)_eyeSel : 0;
    for (u_int32_t lane = perLane; lane < numOfLanes || _oneLaneScan; lane++)
    {
        val = "";
        for (u_int32_t eye = perEye; eye < _numOfEyes || _oneEyeScan; eye++)
        {
            margin = getMarginInfoFromVector(_avgMargins, 0, lane, eye);
            valid = (margin.version != 0);
            val += (valid ? to_string(margin.value) : "err") + string("\t,");
            if (_oneEyeScan)
            {
                break;
            }
        }
        printField("Lane " + to_string(lane) + " margin", val.substr(0, val.length() - 1));
        if (_oneLaneScan)
        {
            break;
        }
    }
}

void MlxlinkEyeOpener::printMarginsSummary()
{
    u_int32_t status = 0;
    char failureStr[128];
    char laneIdxStr[64];
    vector<MarginInfo>::iterator it = _avgMargins.begin();
    MarginInfo finalMargin = *it;
    for (; it != _avgMargins.end(); it++)
    {
        status = it->status;
        if (status != EYE_SCAN_COMPLETED || (status == EYE_SCAN_COMPLETED && it->version == NO_MARGIN))
        {
            sprintf(laneIdxStr, "Failure of lane %d", it->lane);
            if (_pnat != PNAT_PCIE && isPam4Speed)
            {
                sprintf(failureStr, "%s, %s eye", laneIdxStr, _eyeSelctorMap[it->eye].c_str());
            }
            else
            {
                sprintf(failureStr, "%s", laneIdxStr);
            }
            printField(string(failureStr),
                       (status == EYE_SCAN_COMPLETED && it->version == NO_MARGIN) ? "Margin not available" :
                                                                                    _scanStatusMap[status]);
        }
        else
        {
            // find the minimum valid margin
            if ((it->value < finalMargin.value) || finalMargin.value == 0)
            {
                finalMargin = *it;
            }
        }
    }
    fprintf(MlxlinkRecord::stdOut, "\n");
    string finalMarginValue =
      (finalMargin.value == 0 && finalMargin.version == 0) ? "N/A" : to_string(finalMargin.value);
    printField("Final margin", finalMarginValue);
}

// print the final grades and failure information if exists
void MlxlinkEyeOpener::printFinalResults()
{
    calculateAvgMargins();

    printAvgMargins();

    printMarginsSummary();

    if (MlxlinkRecord::jsonFormat)
    {
        _cmdOut.toJsonFormat(_jsonRoot);
        cout << _cmdOut;
    }
}

// start eye scanner for all lanes
void MlxlinkEyeOpener::enableGradeScan()
{
    preChecks();

    initWarMsgs();

    setPrintTitle(_cmdOut, CMD_TITLE, numOfLanes + 10);

    if (askUser("Do you want to continue", _force))
    {
        printTitle(CMD_TITLE);
        _numOfEyes = (_eyeSel != MAX_NUMBER_OF_EYES) ? 1 : MAX_NUMBER_OF_EYES;
        u_int32_t timePerLane = (_measureTimeMap[_measureTime]) * _numOfEyes * scanIterations;
        char timePerLaneStr[64];
        char totalTimeStr[64];
        sprintf(timePerLaneStr, "%02d:%02d", (u_int32_t)timePerLane / 60, (u_int32_t)timePerLane % 60);
        sprintf(totalTimeStr, "%02d:%02d", (u_int32_t)(timePerLane * numOfLanes) / 60,
                (u_int32_t)(timePerLane * numOfLanes) % 60);

        printField("Estimated Total Time [min:sec]", string(totalTimeStr));

        if (lane >= 0)
        {
            _oneLaneScan = true;
            for (u_int32_t i = 0; i < scanIterations; i++)
            {
                laneEyesScanner(i, lane);
            }
        }
        else
        {
            for (u_int32_t i = 0; i < scanIterations; i++)
            {
                for (u_int32_t lane = 0; lane < numOfLanes; lane++)
                {
                    laneEyesScanner(i, lane);
                    slredStopSignalHandler();
                }
            }
        }

        fprintf(MlxlinkRecord::stdOut, "\r");
        printField("Scanning status", "Completed    ", true);
        fflush(MlxlinkRecord::stdOut);

        if (_pnat != PNAT_PCIE && isPam4Speed)
        {
            char gradeTitle[64];
            if (_eyeSel != EYE_ALL)
            {
                sprintf(gradeTitle, "%-8s", _eyeSelctorMap[_eyeSel].c_str());
                _oneEyeScan = true;
            }
            else
            {
                sprintf(gradeTitle, "%-8s,%-8s,%-8s", "UP", "MID", "DOWN");
                _oneEyeScan = false;
            }
            printField("Eye grade", string(gradeTitle));
        }
        printFinalResults();
    }
    else
    {
        MlxlinkRecord::printCmdLine("Operation canceled", _jsonRoot);
    }
}
