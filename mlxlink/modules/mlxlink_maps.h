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

#ifndef MLXLINK_MAPS_H
#define MLXLINK_MAPS_H

#include <errno.h>
#include <cstdio>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <mlxreg/mlxreg_lib/mlxreg_lib.h>
#include <mlxreg/mlxreg_lib/mlxreg_parser.h>
#include "mlxlink_user_input.h"
#include "printutil/mlxlink_cmd_print.h"
#include "mlxlink_enums.h"

struct PortGroup
{
    PortGroup()
    {
        localPort = 0;
        labelPort = 0;
        groupId = 0;
        split = 0;
        secondSplit = 0;
        isFnm = false;
    }
    PortGroup(u_int32_t _localPort, u_int32_t _labelPort, u_int32_t _groupId, u_int32_t _split)
    {
        localPort = _localPort;
        labelPort = _labelPort;
        groupId = _groupId;
        split = _split;
        secondSplit = 0;
        isFnm = false;
    }
    PortGroup(u_int32_t _localPort, u_int32_t _labelPort, u_int32_t _groupId, u_int32_t _split, u_int32_t _secondSplit)
    {
        localPort = _localPort;
        labelPort = _labelPort;
        groupId = _groupId;
        split = _split;
        secondSplit = _secondSplit;
        isFnm = false;
    }
    PortGroup(u_int32_t _localPort,
              u_int32_t _labelPort,
              u_int32_t _groupId,
              u_int32_t _split,
              u_int32_t _secondSplit,
              bool _isFnm)
    {
        localPort = _localPort;
        labelPort = _labelPort;
        groupId = _groupId;
        split = _split;
        secondSplit = _secondSplit;
        isFnm = _isFnm;
    }
    u_int32_t localPort;
    u_int32_t labelPort;
    u_int32_t groupId;
    u_int32_t split;
    u_int32_t secondSplit;
    bool isFnm;

    bool operator<(const PortGroup& b) const
    {
        if (labelPort < b.labelPort)
        {
            return true;
        }
        if (labelPort == b.labelPort && split < b.split)
        {
            return true;
        }
        if (labelPort == b.labelPort && split == b.split && secondSplit < b.secondSplit)
        {
            return true;
        }
        return false;
    }
};

struct CAP_VALUE
{
    CAP_VALUE()
    {
        capMask = 0;
        value = 0;
        name = "";
    }
    CAP_VALUE(u_int32_t _cap, u_int32_t _val)
    {
        capMask = _cap;
        value = _val;
        name = "";
    }
    CAP_VALUE(string _name, u_int32_t _cap, u_int32_t _val)
    {
        capMask = _cap;
        value = _val;
        name = _name;
    }
    u_int32_t capMask;
    u_int32_t value;
    string name;
};

struct PRM_FIELD
{
    PRM_FIELD()
    {
        prmField = "";
        uiField = "";
        fieldAccess = 0;
        isSigned = false;
        validationMask = 0;
    }

    PRM_FIELD(string _prmField, string _uiField, u_int32_t _fieldAccess, bool _isSigned)
    {
        prmField = _prmField;
        uiField = _uiField;
        fieldAccess = _fieldAccess;
        isSigned = _isSigned;
        validationMask = 0;
    }

    PRM_FIELD(string _prmField, string _uiField, u_int32_t _fieldAccess, bool _isSigned, u_int32_t _validationMask)
    {
        prmField = _prmField;
        uiField = _uiField;
        fieldAccess = _fieldAccess;
        isSigned = _isSigned;
        validationMask = _validationMask;
    }

    string prmField;
    string uiField;
    u_int32_t fieldAccess;
    bool isSigned;
    u_int32_t validationMask;
};

class MlxlinkMaps
{
private:
    MlxlinkMaps();
    static MlxlinkMaps* instance;
    void initPublicStrings();
    void initPortStateMapping();
    void initFecAndLoopbackMapping();
    void ethSpeedMapping();
    void extEthSpeedMapping();
    void ibSpeedMapping();
    void nvlinkSpeedMapping();
    void speedToLanesMapping();
    void initPortSpeedMapping();
    void initPpcntGroupsMapping();
    void initPrbsMapping();
    void initPpbmcAndPepcMapping();
    void initLinkDownInfoMapping();
    void initLinkUpInfo();
    void initSltpStatusMapping();
    void initPSCDRateMaskMapping();
    void initPSCDRoleMaskMapping();
    void initPSCDModeBRoleMaskMapping();
    void qsfpComlianceMapping();
    void cmisIbComlianceMapping();
    void cimsCableBreakoutMapping();
    void qsfpFarEndCableBreakoutMapping();
    void qsfpNearEndCableBreakoutMapping();
    void rxTxCdrCapMapping();
    void sfpComplianceMapping();
    void extComplianceMapping();
    void hostComplianceMapping();
    void mediaComplianceMapping();
    void activeComplianceMapping();
    void initCableComplianceMapping();
    void initCableTechnologyMapping();
    void initCablePowerClassMapping();
    void cmisModuleStMapping();
    void tempFlagsMapping();
    void vccFlagsMapping();
    void dataPathStateMapping();
    void errorCodeResMapping();
    void modulePrbsMapping();
    void rxPowerTypeMapping();
    void phyHstFsmHdrStateMapping();
    void maxReadReqSizeMapping();
    void pwrStatusMapping();
    void portTypeMapping();
    void linkPeerMaxSpeedMapping();
    void portStateMapping();
    void techMapping();
    void pcieEnumMapping();
    void initEnhancedDebugMapping();
    void initPpttParamsMapping();
    void initPpttSpeedMapping();
    void initPprmOperationRecoveryMapping();
    void initPprmRecoveryStatusMapping();
    void initCableTypeForTableView();
    void initTableHeaders();
    void initPlrRejectModeMapping();
    void initKrMapping();

public:
    static MlxlinkMaps* getInstance();
    virtual ~MlxlinkMaps();

    std::map<u_int32_t, std::string> _pmFsmState;
    std::map<u_int32_t, std::string> _priOrSec;
    std::map<u_int32_t, std::string> _proFileFecInUse;
    std::map<u_int32_t, u_int32_t> _ETHSpeed2gRate;
    std::map<u_int32_t, u_int32_t> _IBSpeed2gRate;
    std::map<u_int32_t, std::string> _ibPhyFsmState;
    std::map<u_int32_t, std::string> _phyHstFsmNdrState;
    std::map<u_int32_t, std::string> _phyHstFsmHdrState;
    std::map<u_int32_t, std::string> _psiFsmState;
    std::map<u_int32_t, std::string> _retranModeActive;
    std::map<u_int32_t, std::string> _groupMap;
    std::map<u_int32_t, std::string> _prbsModesList;
    std::map<std::string, u_int32_t> _prbsModulationValue;
    std::map<u_int32_t, std::string> _prbsLaneRateList;
    std::map<std::string, CAP_VALUE> _prbsLaneRate;
    std::map<u_int32_t, std::string> _prbsLaneRateCap;
    std::map<u_int32_t, std::string> _prbsTuningType;
    std::map<u_int32_t, std::string> _prbsEStatus;
    std::map<u_int32_t, std::string> _prbsPStatus;
    std::map<u_int32_t, std::string> _prbsRxTuningStatus;
    std::map<u_int32_t, std::string> _prbsLockStatus;
    std::map<u_int32_t, std::string> _prbsModulation;
    std::map<u_int32_t, std::string> _modulePrbsSt;
    std::map<u_int32_t, std::string> _modulePrbsSwapAdmin;
    std::map<u_int32_t, std::string> _modulePrbsInvAdmin;
    std::map<u_int32_t, std::string> _modulePrbsModulation;
    std::map<u_int32_t, std::string> _modulePrbsRateCapToStr;
    std::map<std::string, u_int32_t> _modulePrbsRateStrToCap;
    std::map<u_int32_t, std::string> _modulePMPDStatus;
    std::map<u_int32_t, std::string> _modulePrbsModeCapToStr;
    std::map<std::string, u_int32_t> _modulePrbsModeStrToCap;
    std::map<ModuleAccess_t, std::string> _moduleScopeToStr;
    std::map<u_int32_t, std::string> _moduleRxAmp;
    std::map<u_int32_t, std::string> _moduleRxAmpCap;
    std::map<u_int32_t, std::string> _pepcStatus;
    std::map<u_int32_t, string> _IBSpeed2Str;
    std::map<u_int32_t, string> _NVLINKSpeed2Str;
    std::map<u_int32_t, string> _EthExtSpeed2Str;
    std::map<u_int32_t, u_int32_t> _IBSpeed2gNum;
    std::map<u_int32_t, u_int32_t> _ETHSpeed2gNum;
    std::map<u_int32_t, string> _ETHSpeed2Str;
    std::map<u_int32_t, u_int32_t> _EthExtSpeed2gNum;
    std::map<u_int32_t, u_int32_t> _ETHSpeed2Lanes;
    std::map<u_int32_t, u_int32_t> _ExtETHSpeed2Lanes;
    std::map<u_int32_t, string> _SLTPBadSetStatus2Str;
    std::map<u_int32_t, string> _SLTP16BadSetStatus2Str;
    std::map<u_int32_t, string> _SLTP7BadSetStatus2Str;
    std::map<u_int32_t, PRM_FIELD> _SltpEdrParams;
    std::map<u_int32_t, PRM_FIELD> _SltpHdrParams;
    std::map<u_int32_t, PRM_FIELD> _SltpNdrParams;
    std::map<u_int32_t, PRM_FIELD> _SltpXdrParams;
    std::map<u_int32_t, std::string> _PSCDRateMask2Str;
    std::map<std::string, uint32_t> _PSCDRateStr2Mask;
    std::map<u_int32_t, std::string> _PSCDRoleMask2Str;
    std::map<std::string, uint32_t> _PSCDRoleStr2Mask;
    std::map<u_int32_t, std::string> _PSCDModeBRoleMask2Str;
    std::map<std::string, uint32_t> _PSCDModeBRoleStr2Mask;
    std::map<u_int32_t, std::string> _ethANFsmState;
    std::map<u_int32_t, std::string> _fecModeActive;
    std::map<u_int32_t, std::string> _plrRejectMode;
    std::map<u_int32_t, std::string> _krExtOper;
    std::map<u_int32_t, std::string> _krPrbsType;
    std::map<u_int32_t, pair<string, string>> _fecModeMask;
    std::vector<pair<string, string>> _fecPerSpeed;
    std::map<u_int32_t, pair<string, string>> _loopbackModeList;
    std::map<u_int32_t, std::string> _anDisableList;
    std::map<u_int32_t, std::string> _tech;
    std::map<u_int32_t, std::string> _cableComplianceSfp;
    std::map<u_int32_t, std::string> _cableComplianceQsfp;
    std::map<u_int32_t, std::string> _cableComplianceCmisIb;
    std::map<u_int32_t, std::string> _tempFlags;
    std::map<u_int32_t, std::string> _vccFlags;
    std::map<u_int32_t, std::string> _dataPathSt;
    std::map<u_int32_t, std::string> _moduleOperSt;
    std::map<u_int32_t, std::string> _moduleErrType;
    std::map<u_int32_t, std::string> _errorCodeRes;
    std::map<u_int32_t, std::string> _cimsCableBreakout;
    std::map<u_int32_t, std::string> _qsfpNearEndCableBreakout;
    std::map<u_int32_t, std::string> _qsfpFarEndCableBreakout;
    std::map<u_int32_t, std::string> _cableComplianceExt;
    std::map<u_int32_t, std::string> _cmisHostCompliance;
    std::map<u_int32_t, std::string> _txInputFreq;
    std::map<u_int32_t, std::string> _rxTxCdrCap;
    std::map<u_int32_t, std::string> _rxPowerType;
    std::map<u_int32_t, std::string> _maxReadReqSize;
    std::map<u_int32_t, std::string> _pwrStatus;
    std::map<u_int32_t, std::string> _portType;
    std::map<u_int32_t, std::string> _linkPeerMaxSpeed;
    std::map<u_int32_t, std::string> _portState;
    std::map<u_int32_t, std::string> _downBlame;
    std::map<u_int32_t, std::string> _pdFsmState;
    std::map<u_int32_t, std::string> _pdFsmStateNdr;
    std::map<u_int32_t, std::string> _negModeActive;
    std::map<u_int32_t, std::string> _upReasonPwr;
    std::map<u_int32_t, std::string> _upReasonDrv;
    std::map<u_int32_t, std::string> _upReasonMng;
    std::map<u_int32_t, std::string> _fastLinkUpStatus;
    std::map<u_int32_t, std::string> _localReasonOpcode;
    std::map<u_int32_t, std::string> _cimsModuleSt;
    std::map<u_int32_t, std::string> _mmfCompliance;
    std::map<u_int32_t, std::string> _smfCompliance;
    std::map<u_int32_t, std::string> _activeCableCompliance;
    std::map<u_int32_t, std::string> _sfpQsfpPowerClass;
    std::map<u_int32_t, std::string> _sfpddPowerClass;
    std::map<u_int32_t, std::string> _qsfpddOsfpPowerClass;
    std::map<u_int32_t, float> _qsfpddPowerClassToValue;
    std::map<u_int32_t, float> _sfpddPowerClassToValue;
    std::map<u_int32_t, std::string> _cableTechnologyQsfp;
    std::map<u_int32_t, std::string> _cableTechnologySfp;
    std::map<u_int32_t, std::string> _ppbmcBerMonitorState;
    std::map<u_int32_t, std::string> _ppbmcBerMonitorType;
    std::map<u_int32_t, std::string> _pepcTwistedPairAn;
    std::map<u_int32_t, std::string> _pepcTwistedPairForceMode;
    std::map<u_int32_t, std::string> _pepcTwistedPairAnMode;
    std::map<u_int32_t, std::string> _pddrLinkDownBlame;
    std::map<u_int32_t, std::string> _pddrLinkDownE2EReasonOpcode;
    std::map<u_int32_t, std::string> _slrgTestStatus;
    std::map<u_int32_t, std::pair<std::string, std::string>> _slrgTestFields;
    std::map<std::string, u_int32_t> _networkPorts;
    std::map<u_int32_t, std::string> _networkProtocols;
    std::map<u_int32_t, std::string> _rxUglState;
    std::map<u_int32_t, std::string> _txUglState;
    std::map<u_int32_t, std::string> _aeState;
    std::map<u_int32_t, std::string> _pllUglState;
    std::map<u_int32_t, std::string> _slrgFomMode;
    std::map<u_int32_t, std::string> _slrgFomMode5nm;
    std::map<u_int32_t, std::string> _pcieDevStatus;
    std::map<u_int32_t, PcieErrType> _pcieErrType;
    std::map<u_int32_t, PRM_FIELD> _ppttParams;
    std::map<u_int32_t, u_int32_t> _ppttSpeedMapping;
    std::map<u_int32_t, std::string> _pprmOperRecovery;
    std::map<u_int32_t, std::string> _pprmRecoveryStatus;
    std::map<u_int32_t, u_int32_t> _ppcntGroups;
    std::map<u_int32_t, std::string> _fecModeActiveForTableDispaly;
    std::map<u_int32_t, std::string> _cableTypeForTableDisplay;
    std::map<u_int32_t, std::string> _phyMgrStateForTableDisplay;

    // Vectors
    std::vector<std::pair<std::string, u_int32_t>> _multiPortInfoTableHeader;
    std::vector<std::pair<std::string, u_int32_t>> _multiPortModuleInfoTableHeader;
    std::vector<std::pair<std::string, u_int32_t>> _bkvGroupsTableHeader;
    std::vector<std::pair<std::string, u_int32_t>> _bkvGroupEntriesTableHeader;

    string _sltpHeader;
    string _showErrorsTitle;
};

#endif /* MLXLINK_MAPS_H */
