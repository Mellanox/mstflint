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

#ifndef MLXLINK_EYE_OPENER_H
#define MLXLINK_EYE_OPENER_H

#include "mlxlink_reg_parser.h"
#include <mft_utils/mft_sig_handler.h>

#define TIME_DELTA          15
#define MAX_LM_TIME         45
#define LM_WAIT_TIME        3
#define MAX_NUMBER_OF_EYES  3
#define MAX_PROGRESS_VAL    85
#define MAX_NUMBER_OF_LANES 8

// SLRED Defaults
#define DFLT_ERR_RES_SCALE  1
#define DFLT_ERR_RES_BASE   3


// SLRED PCIE Defaults
#define DFLT_MSUR_TIME_PCIE      60
#define DFLT_EYE_DIAG_DIM_PCIE   3
#define MAX_ITERATION_SCAN_PCIE  3

// SLRED Network Defaults
#define DFLT_MSUR_TIME_PORT      30
#define DFLT_EYE_DIAG_DIM_PORT   1
#define MAX_ITERATION_SCAN_PORT  1
#define SLRED_REG               "SLRED"

enum SCAN_TIME {
    MEASURE_10_SEC,
    MEASURE_30_SEC,
    MEASURE_60_SEC,
    MEASURE_90_SEC,
    MEASURE_120_SEC,
    MEASURE_240_SEC,
    MEASURE_480_SEC,
    MEASURE_600_SEC,
    MEASURE_900_SEC
};

enum EYE_SELECT {
    EYE_UP,
    EYE_MID,
    EYE_DOWN,
    EYE_ALL
};

enum SCAN_STATUS {
    EYE_SCAN_NOT_PERFORMED,
    UNSUPPORTED_SCAN_FOR_CURRENT_SPEED,
    SYSTEM_BUSY,
    PERFORMING_EYE_SCAN,
    EYE_SCAN_COMPLETED,
    ERROR_EYE_SCAN_NOT_COMPLETED
};

enum PNAT_ACCESS {
    PNAT_LOCAL = 0, PNAT_LABEL = 1, PNAT_PCIE = 3
};

enum PRODUCT_TECHNOLOGY {
    PRODUCT_40NM = 0,
    PRODUCT_28NM = 1,
    PRODUCT_16NM = 3
};

enum SLRED_LANE_SPEED {
    SLRED_LANE_SPEED_QDR = 2,
    SLRED_LANE_SPEED_FDR10 = 3,
    SLRED_LANE_SPEED_FDR = 4,
    SLRED_LANE_SPEED_EDR = 5,
    SLRED_LANE_SPEED_HDR = 6
};

enum MARGIN_VERSION {
    NO_MARGIN,
    FIGURE_OF_MERIT
};

struct MarginInfo {
    u_int32_t lane, eye, value, status, version, iteration;
    MarginInfo() {
        lane = 0;
        eye = 0;
        value = 0;
        status = 0;
        version = 0;
        iteration = 0;
    }
    MarginInfo(u_int32_t iLane, u_int32_t iEye, u_int32_t iVal,
            u_int32_t iStatus, u_int32_t iVersion, u_int32_t iIteration) {
        lane = iLane;
        eye = iEye;
        value = iVal;
        status = iStatus;
        version = iVersion;
        iteration = iIteration;
    }
};

using namespace std;

class MlxlinkEyeOpener:public MlxlinkRegParser
{
public:
    MlxlinkEyeOpener(Json::Value &jsonRoot);
    virtual ~MlxlinkEyeOpener();

    // Fields setters
    void setPageDataSel(u_int32_t pageDataSel);
    void setErrResBase(u_int32_t errResBase);
    void setEyeDiagDim(u_int32_t eyeDiagDim);
    void setMeasureTime(u_int32_t measureTime);
    void setEyeSel(const string &eyeSel);
    void setNonInteractiveMode(bool force);

    // Eye scan starter function
    void enableGradeScan();

    // Global fields should be taken from mlxlink_commander
    u_int32_t localPort;
    u_int32_t portType;
    bool pciePort;
    int lane;
    u_int32_t protoActive;
    u_int32_t numOfLanes;
    bool isPam4Speed;
    u_int32_t scanIterations;

private:
    // Helper functions
    void initSlredMaps();
    bool askUser(const char *question);
    void initWarMsgs();
    void gradeEyeScanner(u_int32_t iteration, u_int32_t lane, u_int32_t eye);
    void laneEyesScanner(u_int32_t iteration, u_int32_t lane);
    void printField(const string &key, const string &val, bool newLine = true);
    void printTitle(const string &title);
    bool isActiveGenSupported();
    void updatePortType();
    u_int32_t getDeviceVersion();
    void preChecks();
    void printFinalResults();
    void prepareSlred(u_int32_t lane, u_int32_t eye);
    void enableSlredGradeScan(u_int32_t lane, u_int32_t eye);
    void slredStopSignalHandler();
    void getSlredMargin(u_int32_t iteration, u_int32_t lane, u_int32_t eye);
    u_int32_t getSlredStatus(u_int32_t lane, u_int32_t eye);
    string getSlredLaneSpeedStr(u_int32_t lane, u_int32_t eye);
    MarginInfo getMarginInfoFromVector(vector<MarginInfo> &margins,
            u_int32_t iteration, u_int32_t lane, u_int32_t eye);
    vector<MarginInfo> calculateAvgMargins();
    void printAvgMargins();
    void printMarginsSummary();

    // Internal fields
    Json::Value &_jsonRoot;
    int _pageDataSel;
    int _errResBase;
    int _eyeDiagDim;
    int _measureTime;
    int _eyeSel;
    u_int32_t _numOfEyes;
    bool _force;
    bool _oneLaneScan;
    bool _oneEyeScan;
    string _symWaiter;
    vector<MarginInfo> _measuredMargins;
    vector<MarginInfo> _avgMargins;
    map<u_int32_t, u_int32_t> _measureTimeMap;
    map<u_int32_t, string> _eyeSelctorMap;
    map<u_int32_t, string> _scanStatusMap;
    map<u_int32_t, string> _laneSpeedMap;
};

#endif /* MLXLINK_EYE_OPENER_H */
