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

#include "mlxlink_port_info.h"
#include "mlxlink_maps.h"

MlxlinkPortInfo::MlxlinkPortInfo(Json::Value &jsonRoot): _jsonRoot(jsonRoot)
{
    _localPort = 0;
    _pnat = 0;
    _portType = 0;
    _fecActive = 0;
    _histType = HIST_TYPE_AUTO;
    _numOfBins = 0;
    _fieldSep = " \t";
}

MlxlinkPortInfo::~MlxlinkPortInfo()
{
}

void MlxlinkPortInfo::resetPPHCR()
{
    resetParser(PPHCR_REG);
    updateField("local_port", _localPort);
    updateField("pnat", _pnat);
    updateField("hist_type", _histType);
}

void MlxlinkPortInfo::resetPPCNT()
{
    resetParser(PPCNT_REG);
    updateField("local_port", _localPort);
    updateField("pnat", _pnat);
    updateField("grp", PPCNT_HISTOGRAM_GRP);
}

u_int32_t MlxlinkPortInfo::getNumberOfBins()
{
    resetPPHCR();
    genBuffSendRegister(PPHCR_REG, MACCESS_REG_METHOD_GET);

    return getFieldValue("num_of_bins");
}

void MlxlinkPortInfo::init()
{
    resetPPHCR();
    genBuffSendRegister(PPHCR_REG, MACCESS_REG_METHOD_GET);

    if (!getFieldValue("active_hist_type")) {
        throw MlxRegException("No histogram info available for the current active FEC");
    }

    if (MlxlinkRecord::jsonFormat) {
        _fieldSep = ",";
    }

    _numOfBins = getNumberOfBins();
}

void MlxlinkPortInfo::updateBinsRange()
{
    resetPPHCR();
    genBuffSendRegister(PPHCR_REG, MACCESS_REG_METHOD_GET);

    for (u_int32_t binIdx = 0; binIdx < _numOfBins; ++binIdx) {
        HISTOGRAM_BIN histBin = HISTOGRAM_BIN(binIdx,
                getFieldValue("low_val_" + to_string(binIdx)),
                getFieldValue("high_val_" + to_string(binIdx)) , 0);
        _binsList.insert(_binsList.begin() + binIdx, histBin);
    }
}

void MlxlinkPortInfo::updateBinsErrorsCount()
{
    resetPPCNT();
    genBuffSendRegister(PPCNT_REG, MACCESS_REG_METHOD_GET);

    for (u_int32_t binIdx = 0; binIdx < _numOfBins; ++binIdx) {
        _binsList[binIdx].numOfErrors  = add32BitTo64(
                                    getFieldValue("hi_" + to_string(binIdx)),
                                    getFieldValue("lo_" + to_string(binIdx)));
    }
}

void MlxlinkPortInfo::showHistogram()
{
    updateBinsRange();
    updateBinsErrorsCount();

    MlxlinkCmdPrint cmdOut = MlxlinkCmdPrint();
    setPrintTitle(cmdOut, "Histogram of FEC Errors", _numOfBins + 2);
    setPrintVal(cmdOut, "Header", "Range" + _fieldSep + "Occurrences",
                ANSI_COLOR_RESET, true, true, true);
    char infoRow[64];
    for (vector<HISTOGRAM_BIN>::iterator it = _binsList.begin();
         it != _binsList.end(); ++it) {
        if (it->minRange == it->maxRange) {
            sprintf(infoRow, "[%d]  %s%lld", it->maxRange,  _fieldSep.c_str(),
                    (unsigned long long int)it->numOfErrors);
        } else {
            sprintf(infoRow, "[%d:%d]%s%lld" , it->minRange, it->maxRange,
                    _fieldSep.c_str(), (unsigned long long int)it->numOfErrors);
        }
        setPrintVal(cmdOut, "Bin " + to_string(it->bin), string(infoRow),
                ANSI_COLOR_RESET, true, true, true);
    }

    cmdOut.toJsonFormat(_jsonRoot);
    cout << cmdOut;
}

void MlxlinkPortInfo::clearHistogram()
{
    MlxlinkRecord::printCmdLine("Clearing Histogram Counters", _jsonRoot);

    resetPPCNT();
    updateField("clr", 1);
    genBuffSendRegister(PPCNT_REG, MACCESS_REG_METHOD_SET);
}

