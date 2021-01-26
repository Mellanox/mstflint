/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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

MlxlinkEyeOpener::MlxlinkEyeOpener(Json::Value &jsonRoot): _jsonRoot(jsonRoot)
{
    _pageDataSel = 0;
    _errResBase = 0;
    _eyeDiagDim = 0;
    _measureTime = -1;
    _eyeSel = -1;
    _numOfEyes = 0;
    _symWaiter = "-\\|/";
    _oneLaneScan = false;
    _oneEyeScan = false;
    scanIterations = MAX_ITERATION_SCAN_PCIE;
    initSlredMaps();
}

MlxlinkEyeOpener::~MlxlinkEyeOpener()
{
}

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

void MlxlinkEyeOpener::setPageDataSel(u_int32_t pageDataSel)
{
    _pageDataSel = pageDataSel;
}

void MlxlinkEyeOpener::setErrResBase(u_int32_t errResBase)
{
    _errResBase = errResBase;
}

void MlxlinkEyeOpener::setEyeDiagDim(u_int32_t eyeDiagDim)
{
    _eyeDiagDim = eyeDiagDim;
}

void MlxlinkEyeOpener::setMeasureTime(u_int32_t measureTime)
{
    string timesStr = "";

    for (map<u_int32_t, u_int32_t>::iterator it = _measureTimeMap.begin();
            it != _measureTimeMap.end(); it++) {
        if (it->second == measureTime) {
            _measureTime = it->first;
            break;
        } else {
            timesStr += to_string(it->second) + ",";
        }
    }

    if (_measureTime < 0) {
        string errorMsg = "Invalid measure time : " + to_string(measureTime);
        errorMsg += "\nValid measure times are [" + deleteLastComma(timesStr) + "]";
        throw MlxRegException(errorMsg);
    }
}

void MlxlinkEyeOpener::setEyeSel(const string &eyeSel)
{
    if (pciePort) {
        return;
    }
    string defaultEye = eyeSel;
    if (!eyeSel.empty()) {
        if (!isPam4Speed) {
            throw MlxRegException("Eye selection valid for PAM4 only");
        }
    } else {
        defaultEye = "ALL";
    }
    string eyeList = "";
    for (map<u_int32_t, string>::iterator it = _eyeSelctorMap.begin();
            it != _eyeSelctorMap.end(); it++) {
        if (it->second == defaultEye) {
            _eyeSel = it->first;
            break;
        } else {
            eyeList += it->second + ",";
        }
    }
    if (_eyeSel < 0) {
        string errorMsg = "Invalid eye : " + eyeSel;
        errorMsg += "\nValid eyes selection are [" + deleteLastComma(eyeList) + "]";
        throw MlxRegException(errorMsg);
    }

}

void MlxlinkEyeOpener::setNonInteractiveMode(bool force)
{
    _force = force;
}

bool MlxlinkEyeOpener::askUser(const char *question)
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

void MlxlinkEyeOpener::initWarMsgs()
{
    MlxlinkRecord::printCmdLine("Reading the SerDes receive eye grades", _jsonRoot);
    MlxlinkRecord::printWar("Link measurement or configuration change using Eye Opening may"
            " cause the link to fail and renegotiate.\nOn the PCI express port,"
            " this may lead to link speed degradation or a system hang.", _jsonRoot);
    MlxlinkRecord::printWar("Eye Opening is a tool to quickly obtain link quality evaluation.\n"
            "It is not intended to replace extensive BER testing. the two evaluation mechanisms\n"
            "should be used in conjunction to guarantee the desired link quality.", _jsonRoot);

    u_int32_t eyeSelectTime = _measureTimeMap[_measureTime];
    u_int32_t totalEysScanTime =
            eyeSelectTime * (_eyeSel != MAX_NUMBER_OF_EYES? 1 : MAX_NUMBER_OF_EYES);
    if (lane >= 0){
        numOfLanes = 1;
    }
    scanIterations = pciePort? MAX_ITERATION_SCAN_PCIE : MAX_ITERATION_SCAN_PORT;
    u_int32_t totalScan = totalEysScanTime * numOfLanes * scanIterations;
    char scanTitle [64];
    u_int32_t min = (u_int32_t)totalScan/60;
    u_int32_t sec = (u_int32_t)totalScan%60;
    if (min) {
        sprintf(scanTitle, "Estimated total scan time %02d minute\\s and %02d seconds", min, sec);
    } else {
        sprintf(scanTitle, "Estimated total scan time %02d seconds", sec);
    }
    MlxlinkRecord::printWar(scanTitle, _jsonRoot);
}

void MlxlinkEyeOpener::updatePortType()
{
    if (portType) {
        updateField("port_type", portType);
    }
}

u_int32_t MlxlinkEyeOpener::getDeviceVersion()
{
    string regName = "SLRG";
    resetParser(regName);
    updatePortType();
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t version = getVersion(getFieldValue("version"));

    return version;
}

bool MlxlinkEyeOpener::isActiveGenSupported()
{
    string regName = "MPEIN";
    resetParser(regName);
    updateField("pcie_index", 0);
    updateField("depth", 0);
    updateField("node", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t activeGen = getFieldValue("link_speed_active");

    return (activeGen & GEN4);
}

void MlxlinkEyeOpener::prepareSlred(u_int32_t lane, u_int32_t eye)
{
    resetParser(SLRED_REG);
    updatePortType();
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", lane);
    updateField("measure_time", _measureTime);
    updateField("err_res_scale", DFLT_ERR_RES_SCALE);
    updateField("err_res_base", DFLT_ERR_RES_BASE);
    updateField("eye_diag_dim", pciePort?DFLT_EYE_DIAG_DIM_PCIE:DFLT_EYE_DIAG_DIM_PORT);
    if (!pciePort && isPam4Speed) {
        updateField("eye_sel", eye);
    }
}

void MlxlinkEyeOpener::enableSlredGradeScan(u_int32_t lane, u_int32_t eye)
{
    prepareSlred(lane, eye);
    if ((_numOfEyes == EYE_ALL && eye == EYE_DOWN) || (_numOfEyes != EYE_ALL)) {
        updateField("last_scan", 1);
    }
    updateField("en", 1);
    genBuffSendRegister(SLRED_REG, MACCESS_REG_METHOD_SET);
}

void MlxlinkEyeOpener::slredStopSignalHandler()
{
    if (mft_signal_is_fired()) {
        prepareSlred(0, 0);
        updateField("abort", 1);
        genBuffSendRegister(SLRED_REG, MACCESS_REG_METHOD_SET);

        printf("\n\n");
        exit(1);
    }
}

void MlxlinkEyeOpener::getSlredMargin(u_int32_t iteration, u_int32_t lane, u_int32_t eye)
{
    prepareSlred(lane, eye);
    updateField("page_data_sel", 0);
    genBuffSendRegister(SLRED_REG, MACCESS_REG_METHOD_GET);
    // put all margins in one vector for later calculations
    _measuredMargins.push_back(MarginInfo(lane,
            (!pciePort && isPam4Speed)? eye : 0, getFieldValue("margin"),
            getFieldValue("status"), getFieldValue("margin_version"), iteration));
}

// Get the status of scan for specific lane\eye
u_int32_t MlxlinkEyeOpener::getSlredStatus(u_int32_t lane, u_int32_t eye)
{
    prepareSlred(lane, eye);
    genBuffSendRegister(SLRED_REG, MACCESS_REG_METHOD_GET);

    return getFieldValue("status");
}

string MlxlinkEyeOpener::getSlredLaneSpeedStr(u_int32_t lane, u_int32_t eye)
{
    prepareSlred(lane, eye);
    genBuffSendRegister(SLRED_REG, MACCESS_REG_METHOD_GET);

    return _laneSpeedMap[getFieldValue("lane_speed")];
}

// Scan specific eye for specific lane with progress indicator
void MlxlinkEyeOpener::gradeEyeScanner(u_int32_t iteration, u_int32_t lane, u_int32_t eye)
{
    double measureTime = _measureTimeMap[_measureTime] + MAX_LM_TIME;
    u_int32_t currTime = 0;
    enableSlredGradeScan(lane, eye);
    // Throw error if the current speed not supported
    if (getSlredStatus(lane, eye) == UNSUPPORTED_SCAN_FOR_CURRENT_SPEED) {
        throw MlxRegException("%s: %s",
                _scanStatusMap[UNSUPPORTED_SCAN_FOR_CURRENT_SPEED].c_str(),
                getSlredLaneSpeedStr(lane, eye).c_str());
    }
    u_int32_t status = getSlredStatus(lane, eye);
    if (status != EYE_SCAN_COMPLETED) {
        while ((status == SYSTEM_BUSY || status == PERFORMING_EYE_SCAN)
                && (currTime < measureTime)) {
            printf("\r");
            printField("Scanning status", "", false);
            msleep(1000);
            try {
                status = getSlredStatus(lane, eye);
            } catch (MlxRegException& exp) {
                continue;
            }
            currTime++;
            printf("In progress %c", _symWaiter.at(currTime%(_symWaiter.length())));
            fflush(stdout);
            slredStopSignalHandler();
        }
    }
    getSlredMargin(iteration, lane, eye);
}

// scan all grades per lane
void MlxlinkEyeOpener::laneEyesScanner(u_int32_t iteration, u_int32_t lane)
{
    if (isPam4Speed && _eyeSel == MAX_NUMBER_OF_EYES && !pciePort) {
        // scan all eyes
        for (u_int32_t i = 0 ; i < MAX_NUMBER_OF_EYES; i++) {
            gradeEyeScanner(iteration, lane, i);
            slredStopSignalHandler();
        }
    } else {
        // scan: specified eye, pcie margin, or NRZ scan
        gradeEyeScanner(iteration, lane, _eyeSel);
    }
}

void MlxlinkEyeOpener::printField(const string &key, const string &val, bool newLine)
{
    cout << key << std::setw(PDDR_LINE_LEN - key.length()) << ": ";
    if (newLine) {
        cout << val << std::endl;
    }
}

void MlxlinkEyeOpener::printTitle(const string &title)
{
    cout << std::endl << title << std::endl;
    cout << std::string(title.length(), '-') << std::endl;
}

// eye scan is working for 16 nm devices only, and Gen4 pcie speeds
void MlxlinkEyeOpener::preChecks()
{
    if (getDeviceVersion() != PRODUCT_16NM) {
        throw MlxRegException("Device not supported!");
    }
    if (pciePort) {
        if (!isActiveGenSupported()) {
            throw MlxRegException("The current link speed not supported (supports only Gen4)!");
        }
    } else {
        if (!isPam4Speed) {
            _eyeSel = -1;
        }
    }
    if (lane != -1) {
        if ((u_int16_t)lane > (numOfLanes-1)) {
            throw MlxRegException("Invalid lane index!");
        }
    }
}

MarginInfo MlxlinkEyeOpener::getMarginInfoFromVector(
        vector<MarginInfo> &margins, u_int32_t iteration, u_int32_t lane,
        u_int32_t eye)
{
    MarginInfo found;
    vector<MarginInfo>::iterator it = margins.begin();
    for (;it != margins.end(); it++) {
        if (it->iteration == iteration && it->lane == lane && it->eye == eye) {
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
    u_int32_t perLane = _oneLaneScan? (u_int32_t)this->lane : 0;
    u_int32_t perEye = _oneEyeScan? (u_int32_t)_eyeSel:0;
    for (u_int32_t lane = perLane; lane < numOfLanes || _oneLaneScan; lane++) {
        for (u_int32_t eye = perEye; eye < _numOfEyes || _oneEyeScan; eye++) {
            value = 0;
            count = 0;
            status = EYE_SCAN_COMPLETED;
            version = 1;
            for (u_int32_t i = 0; i < scanIterations; i++) {
                margin = getMarginInfoFromVector(_measuredMargins, i, lane, eye);
                if (margin.value != 0) {
                    value += margin.value;
                    count++;
                } else {
                    status = margin.status;
                    version = margin.version;
                }
            }
            _avgMargins.push_back(MarginInfo(lane, eye, count? value/count : 0,
                    count? (u_int32_t)EYE_SCAN_COMPLETED : status,
                    count? (u_int32_t)FIGURE_OF_MERIT: version, 0));
            if (_oneEyeScan){
                break;
            }
        }
        if (_oneLaneScan) {
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
    u_int32_t perLane = _oneLaneScan? (u_int32_t)this->lane : 0;
    u_int32_t perEye = _oneEyeScan? (u_int32_t)_eyeSel:0;
    for (u_int32_t lane = perLane; lane < numOfLanes || _oneLaneScan; lane++) {
        val = "";
        for (u_int32_t eye = perEye; eye < _numOfEyes || _oneEyeScan; eye++) {
            margin = getMarginInfoFromVector(_avgMargins, 0, lane, eye);
            valid = (margin.version != 0);
            val += (valid? to_string(margin.value): "err") + string("\t,");
            if (_oneEyeScan) {
                break;
            }
        }
        printField("Lane " + to_string(lane) + " margin", val.substr(0, val.length()-1));
        if (_oneLaneScan) {
            break;
        }
    }
}

void MlxlinkEyeOpener::printMarginsSummary()
{
    u_int32_t status = 0;
    char failureStr[64];
    vector<MarginInfo>::iterator it = _avgMargins.begin();
    MarginInfo finalMargin = *it;
    for (;it != _avgMargins.end(); it++) {
        status = it->status;
        if (status != EYE_SCAN_COMPLETED ||
                (status == EYE_SCAN_COMPLETED && it->version == NO_MARGIN)) {
            sprintf(failureStr, "Failure of lane %d", it->lane);
            if (!pciePort && isPam4Speed) {
                sprintf(failureStr + strlen(failureStr), ", %s eye", _eyeSelctorMap[it->eye].c_str());
            }
            printField(string(failureStr),
                    (status == EYE_SCAN_COMPLETED &&
                            it->version == NO_MARGIN)? "Margin not available" : _scanStatusMap[status]);
        } else {
            // find the minimum valid margin
            if ((it->value < finalMargin.value) || finalMargin.value == 0) {
                finalMargin = *it;
            }
        }
    }
    printf("\n");
    printField("Final margin", finalMargin.value == 0? "N/A" : to_string(finalMargin.value));
}

// print the final grades and failure information if exists
void MlxlinkEyeOpener::printFinalResults()
{

    calculateAvgMargins();

    printAvgMargins();

    printMarginsSummary();
}

// start eye scanner for all lanes
void MlxlinkEyeOpener::enableGradeScan()
{
    preChecks();

    initWarMsgs();

    if (askUser("Do you want to continue")) {
        printTitle("Eye Grades per lane info");

        _numOfEyes = (_eyeSel != MAX_NUMBER_OF_EYES)? 1 : MAX_NUMBER_OF_EYES;
        u_int32_t timePerLane = (_measureTimeMap[_measureTime]) * _numOfEyes * scanIterations;
        char timePerLaneStr[64];
        char totalTimeStr[64];
        sprintf(timePerLaneStr, "%02d:%02d",
                (u_int32_t)timePerLane/60, (u_int32_t)timePerLane%60);
        sprintf(totalTimeStr, "%02d:%02d",
                  (u_int32_t)(timePerLane*numOfLanes)/60,
                  (u_int32_t)(timePerLane*numOfLanes)%60);

        printField("Estimated Total Time [min:sec]", string(totalTimeStr));

        if (lane >= 0) {
            _oneLaneScan = true;
            for (u_int32_t i = 0; i< scanIterations; i++) {
                laneEyesScanner(i, lane);
            }
        } else {
            for (u_int32_t i = 0; i< scanIterations; i++) {
                for ( u_int32_t lane = 0; lane < numOfLanes; lane++) {
                    laneEyesScanner(i, lane);
                    slredStopSignalHandler();
                }
            }
        }
        printf("\r");
        printField("Scanning status", "Completed    ", true);
        fflush(stdout);
        if (!pciePort && isPam4Speed) {
            char gradeTitle[64];
            if (_eyeSel != EYE_ALL) {
                sprintf(gradeTitle, "%-8s", _eyeSelctorMap[_eyeSel].c_str());
                _oneEyeScan = true;
            } else {
                sprintf(gradeTitle, "%-8s%-8s%-8s", "UP", "MID", "DOWN");
                _oneEyeScan = false;
            }
            printField("Eye grade", string(gradeTitle));
        }
        printFinalResults();
    } else {
        MlxlinkRecord::printCmdLine("Operation canceled", _jsonRoot);
    }
}

