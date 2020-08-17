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

#ifndef MLXLINK_EYE_OPENER_H
#define MLXLINK_EYE_OPENER_H

#include "mlxlink_reg_parser.h"
#include <mft_utils/mft_sig_handler.h>

#define TIME_DELTA          15
#define MAX_NUMBER_OF_EYES  3
#define MAX_PROGRESS_VAL    100
#define MAX_NUMBER_OF_LANES 8

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
struct MarginInfo {
    int lane, eye, value, status;
    MarginInfo() {
        lane = 0;
        eye = 0;
        value = -1;
        status = -1;
    }
    MarginInfo(int iLane, int iEye, int iVal, int iStatus) {
        lane = iLane;
        eye = iEye;
        value = iVal;
        status = iStatus;
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
    bool pciePort;
    int lane;
    u_int32_t protoActive;
    u_int32_t numOfLanes;
    bool isPam4Speed;

private:
    // Helper functions
    void initSlredMaps();
    bool askUser(const char *question);
    void initWarMsgs();
    int gradeEyeScanner(const string &laneTitle, u_int32_t lane, u_int32_t eye);
    void laneEyesScanner(u_int32_t lane);
    void printField(const string &key, const string &val);
    void printTitle(const string &title);
    bool isActiveGenSupported();
    u_int32_t getDeviceVersion();
    void preChecks();
    void printFinalResults();
    void enableSlredGradeScan(u_int32_t lane, u_int32_t eye);
    u_int32_t getSlredMargin(u_int32_t lane, u_int32_t eye);
    u_int32_t getSlredStatus(u_int32_t lane, u_int32_t eye);
    string getSlredLaneSpeedStr(u_int32_t lane, u_int32_t eye);

    // Internal fields
    Json::Value &_jsonRoot;
    int _pageDataSel;
    int _errResBase;
    int _eyeDiagDim;
    int _measureTime;
    int _eyeSel;
    bool _force;

    vector<MarginInfo> measuredMargins;
    map<u_int32_t, u_int32_t> _measureTimeMap;
    map<u_int32_t, string> _eyeSelctorMap;
    map<u_int32_t, string> _scanStatusMap;
    map<u_int32_t, string> _laneSpeedMap;
};

#endif /* MLXLINK_EYE_OPENER_H */
