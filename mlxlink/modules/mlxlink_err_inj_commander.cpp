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

