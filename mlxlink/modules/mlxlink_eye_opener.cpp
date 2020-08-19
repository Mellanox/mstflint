/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#include "mlxlink_eye_opener.h"

MlxlinkEyeOpener::MlxlinkEyeOpener(Json::Value &jsonRoot): _jsonRoot(jsonRoot)
{
    _pageDataSel = 0;
    _errResBase = 0;
    _eyeDiagDim = 0;
    _measureTime = -1;
    _eyeSel = -1;

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

    u_int32_t eyeSelectTime = _measureTimeMap[_measureTime] + TIME_DELTA;
    u_int32_t totalEysScanTime =
            eyeSelectTime * (_eyeSel != MAX_NUMBER_OF_EYES? 1 : MAX_NUMBER_OF_EYES);
    if (lane >= 0){
        numOfLanes = 1;
    }
    u_int32_t totalScan = totalEysScanTime * numOfLanes;
    char scanTitle [64];
    sprintf(scanTitle, "Estimated total scan time %02d minutes and %02d seconds",
            (u_int32_t)totalScan/60, (u_int32_t)totalScan%60);
    MlxlinkRecord::printWar(scanTitle, _jsonRoot);
}

u_int32_t MlxlinkEyeOpener::getDeviceVersion()
{
    string regName = "SLRG";
    resetParser(regName);
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

void MlxlinkEyeOpener::enableSlredGradeScan(u_int32_t lane, u_int32_t eye)
{
    string regName = "SLRED";
    resetParser(regName);
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", lane);
    updateField("measure_time", _measureTime);
    if (!pciePort && isPam4Speed) {
        updateField("eye_sel", eye);
    }
    /*if (pciePort || (isPam4Speed && eye == EYE_DOWN) || !isPam4Speed) {
        updateField("last_scan", 1);
    }*/
    updateField("en", 1);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
}

u_int32_t MlxlinkEyeOpener::getSlredMargin(u_int32_t lane, u_int32_t eye)
{
    u_int32_t gradeVal = 0;
    string regName = "SLRED";
    resetParser(regName);
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", lane);
    updateField("page_data_sel", 0);
    updateField("measure_time", _measureTime);
    if (!pciePort && isPam4Speed) {
        updateField("eye_sel", eye);
    }

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    gradeVal = getFieldValue("margin");

    return gradeVal;
}

// Get the status of scan for specific lane\eye
u_int32_t MlxlinkEyeOpener::getSlredStatus(u_int32_t lane, u_int32_t eye)
{
    u_int32_t slredStatus = 0;
    string regName = "SLRED";
    resetParser(regName);
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", lane);
    updateField("measure_time", _measureTime);
    if (!pciePort && isPam4Speed) {
        updateField("eye_sel", eye);
    }
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    slredStatus = getFieldValue("status");

    return slredStatus;
}

string MlxlinkEyeOpener::getSlredLaneSpeedStr(u_int32_t lane, u_int32_t eye)
{
    string regName = "SLRED";
    resetParser(regName);
    updateField("local_port", localPort);
    updateField("pnat", (pciePort) ? PNAT_PCIE : PNAT_LOCAL);
    updateField("lane", lane);
    updateField("measure_time", _measureTime);
    if (!pciePort) { // and PAM4
        updateField("eye_sel", eye);
    }
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return _laneSpeedMap[getFieldValue("lane_speed")];
}
// Scan specific eye for specific lane with progress indicator
int MlxlinkEyeOpener::gradeEyeScanner(const string &laneTitle, u_int32_t lane, u_int32_t eye)
{
    int eyeVal = -1;
    double measureTime = _measureTimeMap[_measureTime] + TIME_DELTA;

    enableSlredGradeScan(lane, eye);
    // Throw error if the current speed not supported
    if (getSlredStatus(lane, eye) == UNSUPPORTED_SCAN_FOR_CURRENT_SPEED) {
        throw MlxRegException("%s: %s",
                _scanStatusMap[UNSUPPORTED_SCAN_FOR_CURRENT_SPEED].c_str(),
                getSlredLaneSpeedStr(lane, eye).c_str());
    }
    double msDelay = 1000 * (measureTime/MAX_PROGRESS_VAL);
    double secDelay = msDelay / 1000;
    for (u_int32_t progress = 0; progress < MAX_PROGRESS_VAL; progress++) {
        measureTime -= secDelay;
        printf("\r%s%02d%s", laneTitle.c_str(),
                (int)(((progress*1.0)/MAX_PROGRESS_VAL) * 100.0), "%");
        fflush(stdout);
        printf("\r");
        msleep(msDelay);
        if (mft_signal_is_fired()) {
            printf("\n\n");
            exit(1);
        }
    }
    u_int32_t status = getSlredStatus(lane, eye);
    if (status  == EYE_SCAN_COMPLETED) {
        eyeVal = getSlredMargin(lane, eye);
    }

    // put all margins in one vector to get the minimum one later
    measuredMargins.push_back(MarginInfo(lane, eye, eyeVal, status));

    return eyeVal;
}

// scan all grades per lane
void MlxlinkEyeOpener::laneEyesScanner(u_int32_t lane)
{
    char title1[128];
    char title[256];
    sprintf(title1, "Lane %d margin", lane);
    sprintf(title, "%*s: ", (int)(2-PDDR_LINE_LEN), title1);
    string laneGrades = string(title);

    char gradeStr[64];
    int gradeValue = 0;
    string gradeSeparator = ",\t";

    if (isPam4Speed && _eyeSel == MAX_NUMBER_OF_EYES && !pciePort) {
        // scan all eyes
        for (u_int32_t i = 0 ; i < MAX_NUMBER_OF_EYES; i++) {
            if (i != (MAX_NUMBER_OF_EYES-1)) {
                gradeSeparator = ",";
            }
            gradeValue = gradeEyeScanner(laneGrades, lane, i);
            if (gradeValue >= 0) {
                sprintf(gradeStr, "%-7d%s", gradeValue, gradeSeparator.c_str());
            } else {
                sprintf(gradeStr, "%-7s%s","err", gradeSeparator.c_str());
            }
            laneGrades += string(gradeStr);
        }
    } else {
        // scan: specified eye, pcie margin, or NRZ scan
        gradeValue = gradeEyeScanner(laneGrades, lane, _eyeSel);
        if (gradeValue >= 0) {
            sprintf(gradeStr, "%-7d%s", gradeValue, gradeSeparator.c_str());
        } else {
            sprintf(gradeStr, "%-7s%s", "err", gradeSeparator.c_str());
        }
        laneGrades += string(gradeStr);
    }
    printf("%s\n", laneGrades.substr(0,laneGrades.length()-2).c_str());
}

void MlxlinkEyeOpener::printField(const string &key, const string &val)
{
    cout << key << std::setw(PDDR_LINE_LEN - key.length()) << ": ";
    cout << val << std::endl;
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
        localPort = 0;
        if (!isActiveGenSupported()) {
            throw MlxRegException("The current link speed not supported (supports only Gen4)!");
        }
    } else {
        if (!isPam4Speed) {
            _eyeSel = -1;
        }
    }
    if (lane >= 0) {
        if ((u_int32_t)lane > (numOfLanes-1)) {
            throw MlxRegException("Invalid lane index!");
        }
    }
}

// print the final grades and failure information if exists
void MlxlinkEyeOpener::printFinalResults()
{
    u_int32_t numberOfFailers = 0;
    int status = 0;
    vector<MarginInfo>::iterator it = measuredMargins.begin();
    MarginInfo finalMargin = *it;
    for(;it != measuredMargins.end(); it++) {
        status = it->status;
        if (status != EYE_SCAN_COMPLETED) {
            numberOfFailers++;
            char failureStr1[64];
            char failureStr[128];
            sprintf(failureStr1, "Failure of lane %d", it->lane);
            if (!pciePort) {
                sprintf(failureStr, "%s, %s eye", failureStr1, _eyeSelctorMap[it->eye].c_str());
            }
            printField(string(failureStr), _scanStatusMap[status]);
        } else {
            // find the minimum valid margin
            // update the finalMargin if its equal -1, to point to the first valid margin
            // The second condition will be satisfied for one time only
            if ((it->value < finalMargin.value) || (finalMargin.value < 0)) {
                finalMargin = *it;
            }
        }
    }
    printField("Final margin", finalMargin.value < 0? "N/A" : to_string(finalMargin.value));
}

// start eye scanner for all lanes
void MlxlinkEyeOpener::enableGradeScan()
{
    preChecks();

    initWarMsgs();

    if (askUser("Do you want to continue")) {
        printTitle("Eye Grades per lane info");

        u_int32_t numOfEyes = (_eyeSel != MAX_NUMBER_OF_EYES)? 1 : MAX_NUMBER_OF_EYES;
        u_int32_t timePerLane = (_measureTimeMap[_measureTime] + TIME_DELTA) * numOfEyes;
        char timePerLaneStr[64];
        char totalTimeStr[64];
        sprintf(timePerLaneStr, "%02d:%02d",
                (u_int32_t)timePerLane/60, (u_int32_t)timePerLane%60);
        sprintf(totalTimeStr, "%02d:%02d [%d lane]",
                  (u_int32_t)(timePerLane*numOfLanes)/60,
                  (u_int32_t)(timePerLane*numOfLanes)%60, numOfLanes);

        printField("Time per-lane \\ Total Time", string(timePerLaneStr) +
                " \\ " + string(totalTimeStr));

        if (!pciePort && isPam4Speed) {
            char gradeTitle[64];
            if (_eyeSel != EYE_ALL) {
                sprintf(gradeTitle, "%-8s", _eyeSelctorMap[_eyeSel].c_str());
            } else {
                sprintf(gradeTitle, "%-8s%-8s%-8s", "UP", "MID", "DOWN");
            }
            printField("Eye grade", string(gradeTitle));
        }
        if (lane >= 0) {
            laneEyesScanner(lane);
        } else {
            for ( u_int32_t i = 0; i < numOfLanes; i++) {
                laneEyesScanner(i);
            }
        }
        printFinalResults();
    } else {
        MlxlinkRecord::printCmdLine("Operation canceled", _jsonRoot);
    }
}

