/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id$
 *
 */

#ifndef MLXLINK_LTX_H
#define MLXLINK_LTX_H

#include "mlxlink_maps.h"
#include "mlxlink_reg_parser.h"
#include <string>
#include <vector>

using namespace std;

const u_int32_t LTX_LANE_COUNT = 2;
const u_int32_t LTX_LOGGER_DEPTH = 10;
const u_int32_t LTX_NVL5_ITER_DEPTH = 5;

/* Printed record counts per lane, asserted against the *_INFO_LAST capacities in the commander. */
const u_int32_t LTX_SUMMARY_FIELDS_PER_LANE = 7;
const u_int32_t LTX_NVL5_LANE_FIELDS = 7;

struct LtxLoggerEntry
{
    u_int32_t ltxStatus;
    u_int32_t ltxFailReason;
    u_int32_t ltxRetryCount;
    u_int32_t ltxRetryFailCount;
    u_int32_t effectiveErrors;
    u_int32_t highestNonZeroHist;
    u_int32_t rawBerMagnitude;
    u_int32_t rawBerMantissa;
    u_int32_t rawBerMantissaFloat;
    u_int32_t prbsBerMagnitude;

    LtxLoggerEntry() :
        ltxStatus(0),
        ltxFailReason(0),
        ltxRetryCount(0),
        ltxRetryFailCount(0),
        effectiveErrors(0),
        highestNonZeroHist(0),
        rawBerMagnitude(0),
        rawBerMantissa(0),
        rawBerMantissaFloat(0),
        prbsBerMagnitude(0)
    {
    }
};

struct LtxLaneSummary
{
    u_int32_t ltxStatus;
    u_int32_t ltxFailReason;
    u_int32_t ltxRetryCount;
    u_int32_t rawBerMagTarget;
    u_int32_t rawBerMantTarget;
    u_int32_t rawBerMantFloatTarget;
    u_int32_t histTarget;
    u_int32_t ltxLoggerIndex;

    LtxLaneSummary() :
        ltxStatus(0),
        ltxFailReason(0),
        ltxRetryCount(0),
        rawBerMagTarget(0),
        rawBerMantTarget(0),
        rawBerMantFloatTarget(0),
        histTarget(0),
        ltxLoggerIndex(0)
    {
    }
};

string ltxStatusName(u_int32_t value);
string ltxFailReasonName(u_int32_t value);
string ltxFailReasonDisplay(u_int32_t value);
string formatLtxRawBer(u_int32_t mantissa, u_int32_t mantissaFloat, u_int32_t magnitude);
string formatLtxHistoryRow(const LtxLoggerEntry& entry);
string ltxStatusColor(u_int32_t status);

bool isLtxLoggerEntryPopulated(const LtxLoggerEntry& entry);
vector<LtxLoggerEntry> reindexLtxLogger(const vector<LtxLoggerEntry>& rawEntries, u_int32_t loggerIndex);
int lastLtxPassIndex(const vector<LtxLoggerEntry>& ordered);

/* NVL6 PDDR page 0xf field paths used by mlxreg after page_select. */
string ltxSummaryFieldName(u_int32_t lane, const string& field);
string ltxLoggerFieldName(u_int32_t lane, u_int32_t idx, const string& field);

string ltxNvl5PortFieldName(const string& field);
string ltxNvl5LaneFieldName(u_int32_t lane, const string& field);
string ltxNvl5IterFieldName(u_int32_t lane, u_int32_t iter, const string& field);

string nvl5LastFailStageName(u_int32_t value);
string nvl5ViolationTypeName(u_int32_t value);
string formatNvl5Ber(u_int32_t coeff, u_int32_t coeffFloat, u_int32_t magnitude, bool isWinner);

class MlxlinkLtx : public MlxlinkRegParser
{
public:
    MlxlinkLtx(Json::Value& jsonRoot);
    virtual ~MlxlinkLtx();

    void showLtxNvl5();
    void showLtxNvl6();
    void toJsonFormat();

    MlxlinkMaps* _mlxlinkMaps;
    bool _silentMode;
    MlxlinkCmdPrint _ltxStatusCmd;
    MlxlinkCmdPrint _ltxLoggerHistoryCmds[LTX_LANE_COUNT];
    MlxlinkCmdPrint _ltxNvl5PortCmd;
    MlxlinkCmdPrint _ltxNvl5LaneCmds[LTX_LANE_COUNT];

private:
    void fetchPddrPage(u_int32_t pageSelect);
    void printLtxTable(const string& title,
                       const vector<string>& tableData,
                       const vector<pair<string, u_int32_t>>& tableHeader,
                       const vector<u_int32_t>& separatorAfterRows = vector<u_int32_t>());

    Json::Value& _jsonRoot;
};

#endif /* MLXLINK_LTX_H */
