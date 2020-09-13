/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#include <stdint.h>
#include "mlxlink_user_input.h"

using namespace std;

UserInput::UserInput()
{
    _labelPort = 1;
    _splitPort = 0;
    _depth = 0;
    _pcieIndex = 0;
    _node = 0;
    _lane = 0;
    _sendPrbs = false;
    _sendPprt = false;
    _sendPptt = false;
    _sendPepc = false;
    _sendPepcForceMode = false;
    _sendPepcANMode = false;
    _pprtTuningTypeFlag = false;
    _toggle = true;
    _pcie = false;
    _links = false;
    _showSltp = false;
    _showSlrp = false;
    _showCounters = false;
    _showEyeInfo = false;
    _sendDepth = false;
    _sendPcieIndex = false;
    _sendNode = false;
    _sendDpn = false;
    _db = false;
    _sltpLane = false;
    _advancedMode = false;
    _specifiedPort = false;
    _cable = false;
    _dump = false;
    _ddm = false;
    _write = false;
    _read = false;
    _logFilePath = "";
    _portType = "NETWORK";
    _paosCmd = "";
    _pplmFec = "";
    _speedFec = "";
    _pplrLB = "";
    _prbsMode = "";
    _pprtMode = "PRBS31";
    _ppttMode = "PRBS31";
    _pprtRate = "";
    _ppttRate = "";
    _pprtTuningType = "";
    _csvBer = "";
    _testMode = "Nominal";
    _forceMode = "";
    _anMode = "";
    _iteration = 0;
    _testTime = 0.05;
    _feedbackIndex = 0;
    _feedbackData = 0;
    _gvmiAddress = 0;
    _page = -1;
    _offset = -1;
    _len = -1;
    _setGroup = -1;
    _showGroup = -1;

    eyeSelect = "";
    eyeSelectSpecified = false;
    measureTime = -1;
    force = false;
    gradeScanPerLane = false;
}
