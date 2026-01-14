/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXLINK_USER_INPUT_H
#define MLXLINK_USER_INPUT_H

#include <string>
#include <string.h>
#include <stdint.h>
#include <mlxreg/mlxreg_lib/mlxreg_lib.h>
#include <mlxreg/mlxreg_lib/mlxreg_parser.h>
#include "mlxlink_enums.h"

using namespace std;

class UserInput
{
public:
    UserInput();
    virtual ~UserInput(){};
    u_int32_t _labelPort;
    u_int32_t _splitPort;
    u_int32_t _secondSplitPort;
    u_int32_t _forceSplitValue;
    u_int32_t _depth;
    u_int32_t _pcieIndex;
    u_int32_t _node;
    u_int32_t _uniqueCmds;
    u_int32_t _uniqueCableCmds;
    u_int32_t _uniquePcieCmds;
    u_int32_t _networkCmds;
    int _pciSltpPort;
    bool _showModule;
    bool _sendPrbs;
    bool _sendPprt;
    bool _sendPptt;
    bool _prbsTxInv;
    bool _prbsRxInv;
    bool _prbsDcCoupledAllow;
    bool _sendPepc;
    bool _sendPepcForceMode;
    bool _sendPepcANMode;
    bool _pprtTuningTypeFlag;
    bool _toggle;
    bool _linkModeForce;
    bool _pcie;
    bool _links;
    bool _sendDepth;
    bool _sendPcieIndex;
    bool _sendNode;
    bool _sendDpn;
    bool _db;
    bool _sltpLane;
    bool _txPolicy;
    bool _advancedMode;
    bool _portSpecified;
    bool _splitProvided;
    bool _secondSplitProvided;
    bool _forceSplit;
    bool _showSltp;
    bool _showSlrp;
    bool _showCounters;
    bool _showEyeInfo;
    bool _cable;
    bool _dump;
    bool _ddm;
    bool _write;
    bool _read;
    bool gradeScanPerLane;
    bool laneSpecified;
    bool autoCsvName;
    bool _showMultiPortInfo;
    bool _showMultiPortModuleInfo;
    bool _showPlr;
    bool _showKr;
    bool _showRxRecoveryCounters;

    string _device;
    string _extAdbFile;
    string _portType;
    string _paosCmd;
    string _pmaosCmd;
    string _pplmFec;
    string _speedFec;
    string _pplrLB;
    string _prbsMode;
    string _pprtMode;
    string _ppttMode;
    string _pprtModulation;
    string _ppttModulation;
    string _pprtRate;
    string _ppttRate;
    string _pprtTuningType;
    string _csvBer;
    string _testMode;
    string _forceMode;
    string _anMode;
    string _logFile;
    string _linkTraining;
    string _phyRecovery;
    string _phyRecoveryType;
    bool _showPeriodicEq;
    bool _periodicEqIntervalSpecified;
    int _setPeriodicEqInterval;
    int _wdTimer;
    bool _wdTimerSpecified;
    double _testTime;
    u_int32_t _feedbackIndex;
    u_int32_t _feedbackData;
    u_int32_t _iteration;
    std::map<u_int32_t, u_int32_t> _sltpParams;
    std::vector<std::string> _ptysSpeeds;
    std::vector<string> _amberPagesStr;
    u_int32_t _lane;
    u_int32_t _bkvGroupId;
    std::vector<std::string> _bkvRates;
    std::vector<std::string> _bkvRoles;
    std::vector<std::string> _bkvModeBRoles;
    u_int32_t _bkvEntry;
    u_int32_t _bkvAddress;
    u_int32_t _bkvWdata;
    u_int32_t _bkvWmask;
    bool _bkvEntrySpecified;
    bool _bkvAddressSpecified;
    bool _bkvWdataSpecified;
    bool _bkvWmaskSpecified;
    u_int32_t _gvmiAddress;
    vector<string> _bytesToWrite;
    int _page;
    int _offset;
    int _len;
    std::map<u_int32_t, bool> _prbsLanesToSet;
    int _setGroup;
    int _showGroup;
    int _slrgTestIterations;
    vector<string> _labelPorts;

    string eyeSelect;
    int measureTime;
    bool force;
    bool eyeSelectSpecified;

    bool enableRxErrInj;
    int mixerOffset0;
    int mixerOffset1;
    bool showMixers;

    bool enableFecHistogram;
    bool showFecHistogram;
    bool clearFecHistogram;

    map<ModulePrbs_t, string> modulePrbsParams;
    bool isPrbsSelProvided;
    bool isPrbsModeProvided;
    bool isPrbsChProvided;
    bool isPrbsGenProvided;
    bool isPrbsShowDiagProvided;
    bool isPrbsClearDiagProvided;
    ModuleAccess_t prbsModuleAccess;

    bool isModuleConfigParamsProvided;
    vector<pair<ControlParam, string>> configParamsToSet;

    bool isPcieErrInjProvided;
    string errorType;
    int errorDuration;
    int injDelay;
    string dbdf;
    vector<string> parameters;

    int planeIndex;
    bool _forceTxAllowed;
    bool _skipPowerGoodCheck;
    string _sysfsPath;
    bool _sysfsPathGiven;
};

#endif /* MLXLINK_USER_INPUT_H */
