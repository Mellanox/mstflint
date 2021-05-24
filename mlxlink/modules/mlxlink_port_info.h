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

#ifndef MLXLINK_PORT_INFO_H
#define MLXLINK_PORT_INFO_H

#include "mlxlink_reg_parser.h"

#define PPHCR_REG               "PPHCR"
#define PPCNT_REG               "PPCNT"
#define PPCNT_HISTOGRAM_GRP     0x23

enum HISTOGRAM_TYPE {
    HIST_TYPE_AUTO,
    HIST_TYPE_KP4,
    HIST_TYPE_LL,
    HIST_TYPE_KR4
};

struct HISTOGRAM_BIN {
    HISTOGRAM_BIN () {
        bin = 0;
        minRange = 0;
        maxRange = 0;
        numOfErrors = 0;
    }
    HISTOGRAM_BIN (u_int32_t _bin, u_int32_t _minRange, u_int32_t _maxRange,
            u_int64_t _numOfErrors) {
        bin = _bin;
        minRange = _minRange;
        maxRange = _maxRange;
        numOfErrors = _numOfErrors;
    }
    u_int32_t bin;
    u_int32_t minRange;
    u_int32_t maxRange;
    u_int64_t numOfErrors;
};

using namespace std;

class MlxlinkPortInfo :public MlxlinkRegParser{

public:
    MlxlinkPortInfo(Json::Value &jsonRoot);
    virtual ~MlxlinkPortInfo();

    void init();
    void showHistogram();
    void clearHistogram();

    u_int32_t _localPort;
    u_int32_t _pnat;
    u_int32_t _portType;
    u_int32_t _fecActive;

private:
    void resetPPHCR();
    void resetPPCNT();
    u_int32_t getNumberOfBins();
    void updateBinsRange();
    void updateBinsErrorsCount();

    Json::Value &_jsonRoot;
    HISTOGRAM_TYPE _histType;
    u_int32_t _numOfBins;
    vector<HISTOGRAM_BIN> _binsList;
    string _fieldSep;
};

#endif /* MLXLINK_PORT_INFO_H */
