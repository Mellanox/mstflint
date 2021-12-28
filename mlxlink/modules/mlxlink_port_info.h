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

#ifndef MLXLINK_PORT_INFO_H
#define MLXLINK_PORT_INFO_H

#include "mlxlink_reg_parser.h"

#define PPHCR_REG               "PPHCR"
#define PPCNT_REG               "PPCNT"

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
