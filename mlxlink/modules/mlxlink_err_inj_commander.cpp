/*
 * Copyright (C) 2021 Mellanox Technologies Ltd. All rights reserved.
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

#include "mlxlink_err_inj_commander.h"

MlxlinkErrInjCommander::MlxlinkErrInjCommander(Json::Value &jsonRoot): _jsonRoot(jsonRoot)
{
    _localPort = 0;
    _pnat = 0;
    _mixerOffset0 = -1;
    _mixerOffset1 = -1;
    _force = false;
}

MlxlinkErrInjCommander::~MlxlinkErrInjCommander()
{
}

bool MlxlinkErrInjCommander::getUserConfirm()
{
    MlxlinkRecord::printWar("Using this feature may result degradation of "
            "the link or even link failure.\nFor the link to return to normal "
            "operation, link needs to be toggled.", _jsonRoot);
    return askUser("Do you want to continue", _force);
}

u_int16_t MlxlinkErrInjCommander::getMixerOffset(u_int32_t id)
{
    string regName = "PREI";
    resetParser(regName);
    updateField("local_port", _localPort);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    return getFieldValue("mixer_offset" + to_string(id));
}

void MlxlinkErrInjCommander::setMixersOffset()
{
    u_int16_t oldMixer0 = getMixerOffset(0);
    u_int16_t oldMixer1 = getMixerOffset(1);
    string regName = "PREI";
    resetParser(regName);
    updateField("local_port", _localPort);
    if (_mixerOffset0 >= 0) {
        updateField("mixer_offset0", (u_int16_t)_mixerOffset0);
        if (_mixerOffset1 == -1) {
            updateField("mixer_offset1", oldMixer1);
        }
    }
    if (_mixerOffset1 >= 0) {
        updateField("mixer_offset1", (u_int16_t)_mixerOffset1);
        if (_mixerOffset0 == -1) {
            updateField("mixer_offset0", oldMixer0);
        }
    }
    genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
}

void MlxlinkErrInjCommander::updateMixerOffsets()
{
    MlxlinkRecord::printCmdLine("Configuring Eye Center", _jsonRoot);
    if (MlxlinkRecord::jsonFormat && !_force) {
        throw MlxRegException("Interactive mode is not available with JSON format, "
                "use --yes flag to force the execution");
    }
    if (getUserConfirm()) {
        setMixersOffset();
    }
}

void MlxlinkErrInjCommander::showMixersOffset()
{
    MlxlinkCmdPrint cmdOut = MlxlinkCmdPrint();
    setPrintTitle(cmdOut, "Eye Centering Control Information", 2);
    char valueStr[32];
    sprintf(valueStr, "0x%x", getMixerOffset(0));
    setPrintVal(cmdOut, "mixer_offset0", valueStr, ANSI_COLOR_RESET, true);
    sprintf(valueStr, "0x%x", getMixerOffset(1));
    setPrintVal(cmdOut, "mixer_offset1", valueStr, ANSI_COLOR_RESET, true);
    cmdOut.toJsonFormat(_jsonRoot);
    cout << cmdOut;
}

