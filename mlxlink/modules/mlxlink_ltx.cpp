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

#include "mlxlink_ltx.h"
#include "mlxlink_enums.h"
#include "mlxlink_fields.h"
#include "printutil/mlxlink_record.h"
#include <iostream>
#include <sstream>

/* getStrByValue() collapses an unmapped value to "N/A"; LTX reports the raw value instead. */
static string ltxNameByValue(const map<u_int32_t, string>& names, u_int32_t value, const string& unmappedPrefix)
{
    map<u_int32_t, string>::const_iterator it = names.find(value);
    if (it != names.end())
    {
        return it->second;
    }
    stringstream ss;
    ss << unmappedPrefix << value;
    return ss.str();
}

string ltxStatusName(u_int32_t value)
{
    return ltxNameByValue(MlxlinkMaps::getInstance()->_ltxStatus, value, "UNKNOWN_");
}

string ltxFailReasonName(u_int32_t value)
{
    return ltxNameByValue(MlxlinkMaps::getInstance()->_ltxFailReason, value, "RESERVED_");
}

string ltxFailReasonDisplay(u_int32_t value)
{
    return (value == LTX_FAIL_REASON_NONE) ? "" : ltxFailReasonName(value);
}

string formatLtxRawBer(u_int32_t mantissa, u_int32_t mantissaFloat, u_int32_t magnitude)
{
    stringstream ss;
    ss << mantissa << "." << mantissaFloat << "E-" << magnitude;
    return ss.str();
}

string ltxStatusColor(u_int32_t status)
{
    return (status == LTX_STATUS_PASS) ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
}

bool isLtxLoggerEntryPopulated(const LtxLoggerEntry& entry)
{
    return entry.ltxStatus || entry.ltxFailReason || entry.ltxRetryCount || entry.ltxRetryFailCount ||
           entry.effectiveErrors || entry.highestNonZeroHist || entry.rawBerMagnitude || entry.rawBerMantissa ||
           entry.rawBerMantissaFloat || entry.prbsBerMagnitude;
}

string formatLtxHistoryRow(const LtxLoggerEntry& entry)
{
    stringstream ss;
    ss << ltxStatusName(entry.ltxStatus);
    string failReason = ltxFailReasonDisplay(entry.ltxFailReason);
    if (!failReason.empty())
    {
        ss << ", " << failReason;
    }
    ss << ", Retry " << entry.ltxRetryCount << ", Eff Err " << entry.effectiveErrors << ", Hist "
       << entry.highestNonZeroHist << ", Raw BER "
       << formatLtxRawBer(entry.rawBerMantissa, entry.rawBerMantissaFloat, entry.rawBerMagnitude) << ", PRBS BER mag "
       << entry.prbsBerMagnitude;
    return ss.str();
}

vector<LtxLoggerEntry> reindexLtxLogger(const vector<LtxLoggerEntry>& rawEntries, u_int32_t loggerIndex)
{
    const u_int32_t depth = (u_int32_t)rawEntries.size();
    if (depth == 0)
    {
        return vector<LtxLoggerEntry>();
    }

    u_int32_t head = loggerIndex % depth;
    if (isLtxLoggerEntryPopulated(rawEntries[head]))
    {
        vector<LtxLoggerEntry> ordered;
        ordered.reserve(depth);
        for (u_int32_t i = 0; i < depth; i++)
        {
            ordered.push_back(rawEntries[(head + i) % depth]);
        }
        return ordered;
    }

    u_int32_t used = loggerIndex;
    if (used > depth)
    {
        used = depth;
    }
    return vector<LtxLoggerEntry>(rawEntries.begin(), rawEntries.begin() + used);
}

int lastLtxPassIndex(const vector<LtxLoggerEntry>& ordered)
{
    for (int i = (int)ordered.size() - 1; i >= 0; i--)
    {
        if (ordered[i].ltxStatus == LTX_STATUS_PASS)
        {
            return i;
        }
    }
    return -1;
}

string ltxSummaryFieldName(u_int32_t lane, const string& field)
{
    stringstream ss;
    ss << field << "_lane" << lane;
    return ss.str();
}

string ltxLoggerFieldName(u_int32_t lane, u_int32_t idx, const string& field)
{
    stringstream ss;
    ss << "ltx_logger_lane" << lane << "[" << idx << "]." << field;
    return ss.str();
}

string ltxNvl5PortFieldName(const string& field)
{
    return "port_info." + field;
}

string ltxNvl5LaneFieldName(u_int32_t lane, const string& field)
{
    stringstream ss;
    ss << "lane_lt_x_feq_ber[" << lane << "]." << field;
    return ss.str();
}

string ltxNvl5IterFieldName(u_int32_t lane, u_int32_t iter, const string& field)
{
    stringstream ss;
    ss << "lane_lt_x_feq_ber[" << lane << "].iter_table[" << iter << "]." << field;
    return ss.str();
}

string nvl5LastFailStageName(u_int32_t value)
{
    switch (value)
    {
        case LTX_NVL5_FAIL_STAGE_OK:
            return "ok";
        case LTX_NVL5_FAIL_STAGE_PHY_UPDATE_REJECTED:
            return "phy_update_rejected";
        case LTX_NVL5_FAIL_STAGE_FORCE_NO_VALID_ENTRY:
            return "force_no_valid_entry";
        case LTX_NVL5_FAIL_STAGE_PHY_BAD_INDEX_OVERFLOW:
            return "phy_bad_index_overflow";
        case LTX_NVL5_FAIL_STAGE_RESERVED_1:
            return "reserved_1";
        case LTX_NVL5_FAIL_STAGE_RESERVED_4:
            return "reserved_4";
        default:
        {
            stringstream ss;
            ss << "unknown_" << value;
            return ss.str();
        }
    }
}

string nvl5ViolationTypeName(u_int32_t value)
{
    switch (value)
    {
        case LTX_NVL5_VIOLATION_NONE:
            return "none";
        case LTX_NVL5_VIOLATION_NO_SERDES_STAMP:
            return "no_serdes_stamp";
        case LTX_NVL5_VIOLATION_NO_PHY_STAMP:
            return "no_phy_stamp";
        case LTX_NVL5_VIOLATION_BOTH:
            return "both";
        default:
        {
            stringstream ss;
            ss << "unknown_" << value;
            return ss.str();
        }
    }
}

string formatNvl5Ber(u_int32_t coeff, u_int32_t coeffFloat, u_int32_t magnitude, bool isWinner)
{
    stringstream ss;
    ss << coeff << "." << coeffFloat << "E-" << magnitude;
    if (isWinner)
    {
        ss << "*";
    }
    return ss.str();
}

MlxlinkLtx::MlxlinkLtx(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _mlxlinkMaps = NULL;
    _silentMode = false;
}

MlxlinkLtx::~MlxlinkLtx() {}

void MlxlinkLtx::fetchPddrPage(u_int32_t pageSelect)
{
    try
    {
        sendPrmReg(ACCESS_REG_PDDR, REG_GET, "page_select=%d", pageSelect);
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("LTX is not supported for the current device!");
    }
}

void MlxlinkLtx::toJsonFormat()
{
    _ltxStatusCmd.toJsonFormat(_jsonRoot);
    _ltxNvl5PortCmd.toJsonFormat(_jsonRoot);
    for (u_int32_t lane = 0; lane < LTX_LANE_COUNT; lane++)
    {
        _ltxLoggerHistoryCmds[lane].toJsonFormat(_jsonRoot);
        _ltxNvl5LaneCmds[lane].toJsonFormat(_jsonRoot);
    }
}

static void appendLtxTableCell(vector<pair<string, u_int32_t>>& header,
                               u_int32_t& pos,
                               vector<string>& tableData,
                               const string& val,
                               const string& color = "")
{
    string displayed = color.empty() ? val : (color + val + ANSI_COLOR_RESET);
    updateColumnWidthPopulateTable(header, pos++, tableData, displayed, (u_int32_t)val.length());
}

void MlxlinkLtx::printLtxTable(const string& title,
                               const vector<string>& tableData,
                               const vector<pair<string, u_int32_t>>& tableHeader,
                               const vector<u_int32_t>& separatorAfterRows)
{
    MlxlinkCmdPrint titleCmd;
    setPrintTitle(titleCmd, title, 1);
    if (!_silentMode)
    {
        std::cout << titleCmd;
    }
    if (!MlxlinkRecord::jsonFormat && !_silentMode)
    {
        printMlxlinkTable(tableData, tableHeader, separatorAfterRows);
    }
}

static_assert(LTX_STATUS_INFO_LAST == LTX_LANE_COUNT * LTX_SUMMARY_FIELDS_PER_LANE,
              "LTX_STATUS_INFO_LAST must hold every summary field of every lane");
static_assert(LTX_LOGGER_HISTORY_LAST == LTX_LOGGER_DEPTH, "LTX_LOGGER_HISTORY_LAST must hold the whole logger ring");
static_assert(LTX_NVL5_LANE_INFO_LAST == LTX_NVL5_LANE_FIELDS + LTX_NVL5_ITER_DEPTH,
              "LTX_NVL5_LANE_INFO_LAST must hold every lane field plus every iteration");

void MlxlinkLtx::showLtxNvl6()
{
    bool origFullPath = _full_path;
    _full_path = true;
    try
    {
        fetchPddrPage(PDDR_LINK_HEALTH_FEC_MEASURE_PAGE);

        setPrintTitle(_ltxStatusCmd, HEADER_LTX_STATUS, LTX_STATUS_INFO_LAST);

        vector<pair<string, u_int32_t>> statusHeader = _mlxlinkMaps->_ltxStatusTableHeader;
        vector<pair<string, u_int32_t>> historyHeader = _mlxlinkMaps->_ltxLoggerHistoryTableHeader;
        vector<string> statusData;
        vector<string> historyData;
        vector<u_int32_t> historySepAfterRows;
        u_int32_t historyRowCount = 0;

        for (u_int32_t lane = 0; lane < LTX_LANE_COUNT; lane++)
        {
            LtxLaneSummary summary;
            summary.ltxStatus = getFieldValue(ltxSummaryFieldName(lane, "ltx_status"));
            summary.ltxFailReason = getFieldValue(ltxSummaryFieldName(lane, "ltx_fail_reason"));
            summary.ltxRetryCount = getFieldValue(ltxSummaryFieldName(lane, "ltx_retry_count"));
            summary.rawBerMagTarget = getFieldValue(ltxSummaryFieldName(lane, "raw_ber_mag_target"));
            summary.rawBerMantTarget = getFieldValue(ltxSummaryFieldName(lane, "raw_ber_mant_target"));
            summary.rawBerMantFloatTarget = getFieldValue(ltxSummaryFieldName(lane, "raw_ber_mant_float_target"));
            summary.histTarget = getFieldValue(ltxSummaryFieldName(lane, "hist_target"));
            summary.ltxLoggerIndex = getFieldValue(ltxSummaryFieldName(lane, "ltx_logger_index"));

            vector<LtxLoggerEntry> rawEntries(LTX_LOGGER_DEPTH);
            for (u_int32_t idx = 0; idx < LTX_LOGGER_DEPTH; idx++)
            {
                LtxLoggerEntry entry;
                entry.ltxStatus = getFieldValue(ltxLoggerFieldName(lane, idx, "ltx_status"));
                entry.ltxFailReason = getFieldValue(ltxLoggerFieldName(lane, idx, "ltx_fail_reason"));
                entry.ltxRetryCount = getFieldValue(ltxLoggerFieldName(lane, idx, "ltx_retry_count"));
                entry.ltxRetryFailCount = getFieldValue(ltxLoggerFieldName(lane, idx, "ltx_retry_fail_count"));
                entry.effectiveErrors = getFieldValue(ltxLoggerFieldName(lane, idx, "effective_errors"));
                entry.highestNonZeroHist = getFieldValue(ltxLoggerFieldName(lane, idx, "highest_non_zero_hist"));
                entry.rawBerMagnitude = getFieldValue(ltxLoggerFieldName(lane, idx, "raw_ber_magnitude"));
                entry.rawBerMantissa = getFieldValue(ltxLoggerFieldName(lane, idx, "raw_ber_mantissa"));
                entry.rawBerMantissaFloat = getFieldValue(ltxLoggerFieldName(lane, idx, "raw_ber_mantissa_float"));
                entry.prbsBerMagnitude = getFieldValue(ltxLoggerFieldName(lane, idx, "prbs_ber_magnitude"));
                rawEntries[idx] = entry;
            }

            vector<LtxLoggerEntry> ordered = reindexLtxLogger(rawEntries, summary.ltxLoggerIndex);
            int passIdx = lastLtxPassIndex(ordered);
            string measuredBer = "-";
            string measuredHist = "-";
            if (passIdx >= 0)
            {
                measuredBer = formatLtxRawBer(ordered[passIdx].rawBerMantissa, ordered[passIdx].rawBerMantissaFloat,
                                              ordered[passIdx].rawBerMagnitude);
                measuredHist = to_string(ordered[passIdx].highestNonZeroHist);
            }

            string lanePrefix = "Lane " + to_string(lane) + " ";
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_STATUS, ltxStatusName(summary.ltxStatus),
                        ltxStatusColor(summary.ltxStatus));
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_FAIL_REASON, ltxFailReasonName(summary.ltxFailReason),
                        summary.ltxFailReason ? ANSI_COLOR_RED : ANSI_COLOR_RESET);
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_RETRY, to_string(summary.ltxRetryCount));
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_RAW_BER, measuredBer);
            setPrintVal(
              _ltxStatusCmd, lanePrefix + FIELD_LTX_RAW_BER_TARGET,
              formatLtxRawBer(summary.rawBerMantTarget, summary.rawBerMantFloatTarget, summary.rawBerMagTarget));
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_HIST, measuredHist);
            setPrintVal(_ltxStatusCmd, lanePrefix + FIELD_LTX_HIST_TARGET, to_string(summary.histTarget));

            string historyTitle = string(HEADER_LTX_LOGGER_HISTORY) + " Lane " + to_string(lane);
            setPrintTitle(_ltxLoggerHistoryCmds[lane], historyTitle, LTX_LOGGER_HISTORY_LAST);
            for (u_int32_t i = 0; i < ordered.size(); i++)
            {
                setPrintVal(_ltxLoggerHistoryCmds[lane], "#" + to_string(i), formatLtxHistoryRow(ordered[i]),
                            ltxStatusColor(ordered[i].ltxStatus));
            }

            u_int32_t statusPos = 0;
            appendLtxTableCell(statusHeader, statusPos, statusData, to_string(lane));
            appendLtxTableCell(statusHeader, statusPos, statusData, ltxStatusName(summary.ltxStatus),
                               ltxStatusColor(summary.ltxStatus));
            appendLtxTableCell(statusHeader, statusPos, statusData, ltxFailReasonDisplay(summary.ltxFailReason));
            appendLtxTableCell(statusHeader, statusPos, statusData, to_string(summary.ltxRetryCount));
            appendLtxTableCell(statusHeader, statusPos, statusData, measuredBer);
            appendLtxTableCell(
              statusHeader, statusPos, statusData,
              formatLtxRawBer(summary.rawBerMantTarget, summary.rawBerMantFloatTarget, summary.rawBerMagTarget));
            appendLtxTableCell(statusHeader, statusPos, statusData, measuredHist);
            appendLtxTableCell(statusHeader, statusPos, statusData, to_string(summary.histTarget));

            for (u_int32_t i = 0; i < ordered.size(); i++)
            {
                if (i == 0 && historyRowCount > 0)
                {
                    historySepAfterRows.push_back(historyRowCount - 1);
                }
                u_int32_t historyPos = 0;
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(lane));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(i));
                appendLtxTableCell(historyHeader, historyPos, historyData, ltxStatusName(ordered[i].ltxStatus),
                                   ltxStatusColor(ordered[i].ltxStatus));
                appendLtxTableCell(historyHeader, historyPos, historyData,
                                   ltxFailReasonDisplay(ordered[i].ltxFailReason));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(ordered[i].ltxRetryCount));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(ordered[i].ltxRetryFailCount));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(ordered[i].effectiveErrors));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(ordered[i].highestNonZeroHist));
                appendLtxTableCell(historyHeader, historyPos, historyData,
                                   formatLtxRawBer(ordered[i].rawBerMantissa, ordered[i].rawBerMantissaFloat,
                                                   ordered[i].rawBerMagnitude));
                appendLtxTableCell(historyHeader, historyPos, historyData, to_string(ordered[i].prbsBerMagnitude));
                historyRowCount++;
            }
        }

        printLtxTable(HEADER_LTX_STATUS, statusData, statusHeader);
        printLtxTable(HEADER_LTX_LOGGER_HISTORY, historyData, historyHeader, historySepAfterRows);
    }
    catch (...)
    {
        _full_path = origFullPath;
        throw;
    }
    _full_path = origFullPath;
}

void MlxlinkLtx::showLtxNvl5()
{
    bool origFullPath = _full_path;
    _full_path = true;
    try
    {
        fetchPddrPage(PDDR_LINK_HEALTH_FEC_MEASURE_NVL5_PAGE);

        string restoreCount = to_string(getFieldValue(ltxNvl5PortFieldName("ltx_restore_count")));
        string totalRounds = to_string(getFieldValue(ltxNvl5PortFieldName("ltx_total_rounds_cnt")));
        string berMeasDone = to_string(getFieldValue(ltxNvl5PortFieldName("num_ber_meas_done")));
        string autoReversals = to_string(getFieldValue(ltxNvl5PortFieldName("auto_reversals_applied")));
        string limiterAllow = to_string(getFieldValue(ltxNvl5PortFieldName("ltx_limiter_allow")));
        string reachedMaxRetry = to_string(getFieldValue(ltxNvl5PortFieldName("ltx_reached_max_retry")));
        string enteredLtxFlow = to_string(getFieldValue(ltxNvl5PortFieldName("entered_ltx_flow")));
        string berBasedInProgress = to_string(getFieldValue(ltxNvl5PortFieldName("ber_based_in_progress")));

        setPrintTitle(_ltxNvl5PortCmd, HEADER_LTX_NVL5, LTX_NVL5_PORT_INFO_LAST);
        setPrintVal(_ltxNvl5PortCmd, "LTX Restore Count", restoreCount);
        setPrintVal(_ltxNvl5PortCmd, "LTX Total Rounds", totalRounds);
        setPrintVal(_ltxNvl5PortCmd, "BER Measurements Done", berMeasDone);
        setPrintVal(_ltxNvl5PortCmd, "Auto Reversals Applied", autoReversals);
        setPrintVal(_ltxNvl5PortCmd, "LTX Limiter Allow", limiterAllow);
        setPrintVal(_ltxNvl5PortCmd, "LTX Reached Max Retry", reachedMaxRetry);
        setPrintVal(_ltxNvl5PortCmd, "Entered LTX Flow", enteredLtxFlow);
        setPrintVal(_ltxNvl5PortCmd, "BER Based In Progress", berBasedInProgress);

        vector<pair<string, u_int32_t>> portHeader = _mlxlinkMaps->_ltxNvl5PortTableHeader;
        vector<string> portData;
        u_int32_t portPos = 0;
        appendLtxTableCell(portHeader, portPos, portData, restoreCount);
        appendLtxTableCell(portHeader, portPos, portData, totalRounds);
        appendLtxTableCell(portHeader, portPos, portData, berMeasDone);
        appendLtxTableCell(portHeader, portPos, portData, autoReversals);
        appendLtxTableCell(portHeader, portPos, portData, limiterAllow);
        appendLtxTableCell(portHeader, portPos, portData, reachedMaxRetry);
        appendLtxTableCell(portHeader, portPos, portData, enteredLtxFlow);
        appendLtxTableCell(portHeader, portPos, portData, berBasedInProgress);
        printLtxTable(HEADER_LTX_NVL5, portData, portHeader);

        vector<pair<string, u_int32_t>> laneHeader = _mlxlinkMaps->_ltxNvl5LaneTableHeader;
        vector<pair<string, u_int32_t>> iterHeader = _mlxlinkMaps->_ltxNvl5IterTableHeader;
        vector<string> laneData;
        vector<string> iterData;

        for (u_int32_t lane = 0; lane < LTX_LANE_COUNT; lane++)
        {
            u_int32_t storesDone = getFieldValue(ltxNvl5LaneFieldName(lane, "stores_done"));
            u_int32_t winnerIdx = getFieldValue(ltxNvl5LaneFieldName(lane, "winner_idx"));
            u_int32_t protocolViolation = getFieldValue(ltxNvl5LaneFieldName(lane, "protocol_violation"));
            u_int32_t violationIdx = getFieldValue(ltxNvl5LaneFieldName(lane, "violation_idx"));
            u_int32_t violationType = getFieldValue(ltxNvl5LaneFieldName(lane, "violation_type"));
            u_int32_t lastFailStage = getFieldValue(ltxNvl5LaneFieldName(lane, "last_fail_stage"));
            u_int32_t forceApplied = getFieldValue(ltxNvl5LaneFieldName(lane, "force_applied"));
            string violTypeName = nvl5ViolationTypeName(violationType);
            string failStage = nvl5LastFailStageName(lastFailStage);

            string title = string(HEADER_LTX_NVL5) + " Lane " + to_string(lane);
            setPrintTitle(_ltxNvl5LaneCmds[lane], title, LTX_NVL5_LANE_INFO_LAST);
            setPrintVal(_ltxNvl5LaneCmds[lane], "Stores", to_string(storesDone));
            setPrintVal(_ltxNvl5LaneCmds[lane], "Winner", to_string(winnerIdx));
            setPrintVal(_ltxNvl5LaneCmds[lane], "Violation", to_string(protocolViolation));
            setPrintVal(_ltxNvl5LaneCmds[lane], "Viol idx", to_string(violationIdx));
            setPrintVal(_ltxNvl5LaneCmds[lane], "Viol type", violTypeName, ANSI_COLOR_RESET, true,
                        protocolViolation != 0);
            setPrintVal(_ltxNvl5LaneCmds[lane], "Fail stage", failStage);
            setPrintVal(_ltxNvl5LaneCmds[lane], "Force", to_string(forceApplied));

            u_int32_t lanePos = 0;
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(lane));
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(storesDone));
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(winnerIdx));
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(protocolViolation));
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(violationIdx));
            appendLtxTableCell(laneHeader, lanePos, laneData, protocolViolation ? violTypeName : "");
            appendLtxTableCell(laneHeader, lanePos, laneData, failStage);
            appendLtxTableCell(laneHeader, lanePos, laneData, to_string(forceApplied));

            u_int32_t stored = storesDone;
            if (stored > LTX_NVL5_ITER_DEPTH)
            {
                stored = LTX_NVL5_ITER_DEPTH;
            }
            for (u_int32_t iter = 0; iter < stored; iter++)
            {
                u_int32_t berMag = getFieldValue(ltxNvl5IterFieldName(lane, iter, "ber_magnitude"));
                u_int32_t berCoeff = getFieldValue(ltxNvl5IterFieldName(lane, iter, "ber_coeff"));
                u_int32_t berCoeffFloat = getFieldValue(ltxNvl5IterFieldName(lane, iter, "ber_coeff_float"));
                u_int32_t serdesValid = getFieldValue(ltxNvl5IterFieldName(lane, iter, "serdes_valid"));
                u_int32_t phyValid = getFieldValue(ltxNvl5IterFieldName(lane, iter, "phy_valid"));
                u_int32_t measInvalid = getFieldValue(ltxNvl5IterFieldName(lane, iter, "meas_invalid"));
                string ber = formatNvl5Ber(berCoeff, berCoeffFloat, berMag, iter == winnerIdx);
                stringstream row;
                row << ber << ", serdes_valid=" << serdesValid << ", phy_valid=" << phyValid
                    << ", meas_invalid=" << measInvalid;
                setPrintVal(_ltxNvl5LaneCmds[lane], "i" + to_string(iter), row.str());

                u_int32_t iterPos = 0;
                appendLtxTableCell(iterHeader, iterPos, iterData, to_string(lane));
                appendLtxTableCell(iterHeader, iterPos, iterData, to_string(iter));
                appendLtxTableCell(iterHeader, iterPos, iterData, ber);
                appendLtxTableCell(iterHeader, iterPos, iterData, to_string(serdesValid));
                appendLtxTableCell(iterHeader, iterPos, iterData, to_string(phyValid));
                appendLtxTableCell(iterHeader, iterPos, iterData, to_string(measInvalid));
            }
        }

        printLtxTable(HEADER_LTX_NVL5_LANES, laneData, laneHeader);
        printLtxTable(HEADER_LTX_NVL5_ITERS, iterData, iterHeader);
    }
    catch (...)
    {
        _full_path = origFullPath;
        throw;
    }
    _full_path = origFullPath;
}
