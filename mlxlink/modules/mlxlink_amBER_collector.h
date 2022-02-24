/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#ifndef MLXLINK_AMBER_COLLECTOR_H
#define MLXLINK_AMBER_COLLECTOR_H

#include "mlxlink_reg_parser.h"
#include "amber_field.h"

//Un-comment to see access register failures
//#define VALIDATE_REG_REQUEST

using namespace std;

struct FIELDS_COUNT {
    u_int32_t numOfIbFields;
    u_int32_t numOfEthFields;
    u_int32_t numOfPcieFields;
};

class MlxlinkAmBerCollector :public MlxlinkRegParser {
public:
    MlxlinkAmBerCollector(Json::Value &jsonRoot);
    virtual ~MlxlinkAmBerCollector();

    virtual void init();
    // Main functions
    vector<AmberField> getIndexesInfo();
    vector<AmberField> getGeneralInfo();
    virtual vector<AmberField> getSystemInfo();
    virtual vector<AmberField> getLinkStatus();
    virtual vector<AmberField> getSerdesHDR();
    virtual vector<AmberField> getSerdesNDR();
    virtual vector<AmberField> getModuleStatus();
    virtual vector<AmberField> getPortCounters();
    virtual vector<AmberField> getTroubleshootingInfo();
    virtual vector<AmberField> getPhyOperationInfo();
    virtual vector<AmberField> getLinkUpInfo();
    virtual vector<AmberField> getLinkDownInfo();
    virtual vector<AmberField> getTestModeInfo();
    virtual vector<AmberField> getTestModeModuleInfo();

    void getPpcntBer(u_int32_t portType, vector<AmberField> &fields);
    bool isGBValid();
    bool isMCMValid();

    void startCollector();

    u_int32_t _pnat;
    u_int32_t _localPort;
    u_int32_t _depth;
    u_int32_t _pcieIndex;
    u_int32_t _node;
    u_int32_t _devID;
    u_int32_t _productTechnology;
    string _csvFileName;
    string _mstDevName;
    u_int32_t _iteration;
    string _testMode;
    MlxlinkMaps *_mlxlinkMaps;
    vector<PortGroup> _localPorts; // will be valid for switches
    bool _isHca;

private:
    string getRawFieldValue(const string fieldName);
    string getNodeGUID();
    string getMACAddress();
    string getCurrentTimeStamp();
    void getEthComplianceCodes(u_int32_t cableTechnology , string &ethComplianceStr , string &extComplianceStr, u_int32_t cableMediaType);
    void getIbComplianceCodes(string &ibComplianceCodeStr);
    string getCableTechnologyStr(u_int32_t cableTechnology);
    string getCableBreakoutStr(u_int32_t cableBreakout, u_int32_t cableIdentifier);
    void calcRxTxPowerLane(vector<AmberField> &fields ,string str);
    void getModuleInfoPage(vector<AmberField> &fields);
    string getSmfLength(const u_int32_t smfLength, const u_int32_t cableTechnology, const bool optical);
    string getDateCode(u_int64_t dateCode);
    void loopAllLanesStr(vector<AmberField> &fields ,const string str);
    void getTxBiasLane(vector<AmberField> &fields);
    string getByMap(u_int32_t flags,  std::map<u_int32_t, std::string> map);
    void getCmisComplianceCode(u_int32_t ethComplianceCode, u_int32_t extEthComplianceCode, string &ethComplianceStr , string &extComplianceStr, u_int32_t cableMediaType, u_int32_t cableTechnology);
    void  initCableIdentifier(u_int32_t cableIdentifier);
    void getModuleLatchedFlagInfoPage(vector<AmberField> &fields);
    void groupValidIf(bool condition);
    void getTestModeModulePMPT(vector<AmberField> &fields, string moduleSide, ModuleAccess_t mode);
    void getTestModeModulePMPD(vector<AmberField> &fields, string moduleSide);

    bool _isQsfpCable;
    bool _isSfpCable;
    bool _cablePlugged;
    bool _invalidate;
    u_int32_t _labelPort;
    u_int32_t _splitPort;
    u_int32_t _secondSplit;
    map<AMBER_SHEET, vector<AmberField>> _amberCollection;

protected:
    string getBitmaskPerLaneStr(u_int32_t bitmask);
    void resetLocalParser(const string &regName);
    string getLocalFieldStr(const string &fieldName);
    u_int32_t getLocalFieldValue(const string &fieldName);
    void sendRegister(const string &regName, maccess_reg_method_t method);

    void fillParamsToFields(const string &title, const vector<string> &values,
                            vector<AmberField> &fields, bool laneLimit = true);
    string getPrbsModeCap(u_int32_t modeSelector, u_int32_t capsMask);
    string getPrpsRateCap(u_int32_t capsMask);
    virtual void getTestModePrpsInfo(const string &prbsReg, vector<vector<string>> &params);

    // Helper functions
    virtual string getBerAndErrorTitle(u_int32_t portType);
    string getClRawBer();

    // Callers
    vector<AmberField> collectSheet(AMBER_SHEET sheet);
    void collect();

    u_int32_t fixFieldsData();
    void exportToCSV();
    void exportToConsole();

    bool _isCmisCable;
    bool _isPortIB;
    bool _isPortETH;
    bool _isPortPCIE;
    bool _isMCMSysValid;
    bool _isGBSysValid;
    bool _isValidSensorMvcap;
    bool _isValidSensorMtcap;
    bool _inPRBSMode;
    u_int32_t _moduleHostSt;
    u_int32_t _moduleMediaSt;

    Json::Value &_jsonRoot;
    vector<MlxlinkCmdPrint> _amBerCollectorOutput;
    map<AMBER_SHEET, FIELDS_COUNT> _sheetsList;

    u_int32_t _activeSpeed;
    u_int32_t _protoActive;
    u_int32_t _numOfLanes;
    u_int32_t _moduleIndex;
    u_int32_t _slotIndex;
    u_int32_t _maxLanes;
};

#endif /* MLXLINK_AMBER_COLLECTOR_H */
