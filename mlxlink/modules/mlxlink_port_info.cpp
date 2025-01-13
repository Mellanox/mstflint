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

#include "mlxlink_port_info.h"
#include "mlxlink_maps.h"

MlxlinkPortInfo::MlxlinkPortInfo(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _fecActive = 0;
    _histType = HIST_TYPE_AUTO;
    _numOfBins = 0;
    _fieldSep = " \t";
}

MlxlinkPortInfo::~MlxlinkPortInfo() {}

void MlxlinkPortInfo::init()
{
    sendPrmReg(ACCESS_REG_PPHCR, GET);

    if (!getFieldValue("active_hist_type"))
    {
        throw MlxRegException("No histogram info available for the current active FEC");
    }

    if (MlxlinkRecord::jsonFormat)
    {
        _fieldSep = ",";
    }

    _numOfBins = getFieldValue("num_of_bins");
}

void MlxlinkPortInfo::updateBinsRange()
{
    sendPrmReg(ACCESS_REG_PPHCR, GET);

    for (u_int32_t binIdx = 0; binIdx < _numOfBins; ++binIdx)
    {
        HISTOGRAM_BIN histBin = HISTOGRAM_BIN(binIdx, getFieldValue("low_val_" + to_string(binIdx)),
                                              getFieldValue("high_val_" + to_string(binIdx)), 0);
        _binsList.insert(_binsList.begin() + binIdx, histBin);
    }
}

void MlxlinkPortInfo::updateBinsErrorsCount()
{
    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_HISTOGRAM_GROUP);

    for (u_int32_t binIdx = 0; binIdx < _numOfBins; ++binIdx)
    {
        _binsList[binIdx].numOfErrors = add32BitTo64(getFieldValue("hist[" + to_string(binIdx) + "]_hi"),
                                                     getFieldValue("hist[" + to_string(binIdx) + "]_lo"));
    }
}

void MlxlinkPortInfo::showHistogram()
{
    updateBinsRange();
    updateBinsErrorsCount();

    MlxlinkCmdPrint cmdOut = MlxlinkCmdPrint();
    setPrintTitle(cmdOut, "Histogram of FEC Errors", _numOfBins + 2);
    setPrintVal(cmdOut, "Header", "Range" + _fieldSep + "Occurrences", ANSI_COLOR_RESET, true, true, true);
    char infoRow[64];
    for (vector<HISTOGRAM_BIN>::iterator it = _binsList.begin(); it != _binsList.end(); ++it)
    {
        if (it->minRange == it->maxRange)
        {
            sprintf(infoRow, "[%d]  %s%lld", it->maxRange, _fieldSep.c_str(), (unsigned long long int)it->numOfErrors);
        }
        else
        {
            sprintf(infoRow, "[%d:%d]%s%lld", it->minRange, it->maxRange, _fieldSep.c_str(),
                    (unsigned long long int)it->numOfErrors);
        }
        setPrintVal(cmdOut, "Bin " + to_string(it->bin), string(infoRow), ANSI_COLOR_RESET, true, true, true);
    }

    cmdOut.toJsonFormat(_jsonRoot);
    cout << cmdOut;
}

void MlxlinkPortInfo::clearHistogram()
{
    MlxlinkRecord::printCmdLine("Clearing Histogram Counters", _jsonRoot);

    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d,clr=%d", PPCNT_HISTOGRAM_GROUP, 1);
}
