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
#ifndef MLXLINK_CABLES_COMMANDER_H
#define MLXLINK_CABLES_COMMANDER_H

#include "mlxlink_reg_parser.h"

typedef struct
{
    float val;
    u_int16_t high_warn;
    u_int16_t low_warn;
    u_int16_t high_alarm;
    u_int16_t low_alarm;
    bool high_warn_flag;
    bool low_warn_flag;
    bool high_alarm_flag;
    bool low_alarm_flag;
} ddm_threshold_t;

typedef struct
{
    ddm_threshold_t temperature;
    ddm_threshold_t voltage;
    ddm_threshold_t rx_power[8];
    ddm_threshold_t tx_power[8];
    ddm_threshold_t tx_bias[8];
    int channels;
} cable_ddm_q_t;

#define LOWER_PAGE_OFFSET 0x0
#define UPPER_PAGE_OFFSET 0x80
#define EEPROM_MAX_BYTES 32
#define EEPROM_IDENTIFIER_BYTE_MASK 0xff
#define I2C_ADDR_LOW 0x50
#define I2C_ADDR_HIGH 0x51
#define EEPROM_PAGE_LENGTH 255
#define CABLE_PAGE_SIZE 0x80
#define DWORD_BLOCK_SIZE 32
#define QSFP_CHANNELS 4
#define SFP_CHANNELS 1
#define DDM_THRES_B_SZ 2
#define CMIS_CHANNELS 8
#define CMIS_MODULE_CHANNEL 1
#define MAX_SFF_CODE_VALUE 15

#define EXTENDED_PAGES_1_2_10_11_ADDR 2
#define EXTENDED_PAGES_1_2_10_11_MASK 0x80
#define EXTENDED_PAGES_03_05_13_14_16_17_20_UPTO_2D_2F_ADDR 142
#define EXTENDED_PAGES_03_MASK 0x4
#define EXTENDED_PAGES_05_MASK 0x8
#define EXTENDED_PAGES_13_14_MASK 0x20
#define EXTENDED_PAGES_20_UPTO_2D_2F_MASK 0x40
#define EXTENDED_PAGES_16_17_MASK 0x80
#define EXTENDED_PAGES_15_ADDR 145
#define EXTENDED_PAGES_15_MASK 0x8
#define EXTENDED_PAGES_4_12_ADDR 155
#define EXTENDED_PAGES_4_12_MASK 0x40
#define EXTENDED_PAGES_19_ADDR 162
#define EXTENDED_PAGES_19_MASK 0x40
#define EXTENDED_PAGES_A0_UPTO_AF_ADDR 163
#define EXTENDED_PAGES_A0_UPTO_AF_MASK 0xf
#define EXTENDED_PAGES_9F_ADDR 163
#define EXTENDED_PAGES_9F_MASK 0xC0

#define VOLT_UNIT 1000
#define MILLIVOLT_UNIT 10

#define DEFAULT_PRBS_MODE_STR "PRBS31"
#define DEFAULT_PRBS_RATE_STR "HDR"

typedef struct Page
{
    u_int32_t page;
    u_int16_t offset;
    u_int16_t i2cAddress;
} page_t;

enum MODULE_PAGE
{
    PAGE_0 = 0x0,
    PAGE_01 = 0x1,
    PAGE_02 = 0x2,
    PAGE_03 = 0x3,
    PAGE_04 = 0x4,
    PAGE_05 = 0x5,
    PAGE_10 = 0x10,
    PAGE_11 = 0x11,
    PAGE_12 = 0x12,
    PAGE_13 = 0x13,
    PAGE_14 = 0x14,
    PAGE_15 = 0x15,
    PAGE_16 = 0x16,
    PAGE_17 = 0x17,
    PAGE_19 = 0x19,
    PAGE_20 = 0x20,
    PAGE_21 = 0x21,
    PAGE_2D = 0x2d,
    PAGE_2F = 0x2f,
    PAGE_9F = 0x9F,
    PAGE_A0 = 0xA0,
    PAGE_A1 = 0xA1,
    PAGE_A2 = 0xA2,
    PAGE_A3 = 0xA3,
    PAGE_A7 = 0xA7,
    PAGE_AB = 0xAB,
    PAGE_AF = 0xAF,
    PAGE_LAST
};

using namespace std;

class MlxlinkCablesCommander : public MlxlinkRegParser
{
public:
    MlxlinkCablesCommander(Json::Value& jsonRoot);
    virtual ~MlxlinkCablesCommander();

    vector<MlxlinkCmdPrint> getPagesToDump();
    vector<MlxlinkCmdPrint> getCableDDM();
    void writeToEEPROM(u_int16_t page, u_int16_t offset, vector<u_int8_t>& bytesToWrite);
    MlxlinkCmdPrint readFromEEPRM(u_int16_t page, u_int16_t offset, u_int16_t length);

    void handlePrbsTestMode(const string& ctrl, ModuleAccess_t moduleAccess);
    void showPrbsTestMode();
    void showPrpsDiagInfo();
    void clearPrbsDiagInfo();
    void showControlParams();
    void setControlParams(vector<pair<ControlParam, string>>& params);
    void setSwControlMode();

    u_int32_t _moduleNumber;
    u_int32_t _slotIndex;
    u_int32_t _cableIdentifier;
    bool _sfp51Paging;
    bool _passiveQsfp;
    u_int32_t _numOfLanes;
    vector<u_int32_t> _moduleLanesMapping;
    MlxlinkMaps* _mlxlinkMaps;
    map<ModulePrbs_t, string> _modulePrbsParams;

private:
    /**** MCIA helper funcitons ****/
    void readMCIA(u_int32_t page, u_int32_t size, u_int32_t offset, u_int8_t* data, u_int32_t i2cAddress);
    void writeMCIA(u_int32_t page,
                   u_int32_t size,
                   u_int32_t numberOfZeroBytes,
                   u_int32_t offset,
                   u_int8_t* data,
                   u_int32_t i2cAddress);
    void initValidPages();
    void loadEEPRMPage(u_int32_t pageNum, u_int32_t offset, u_int8_t* data, u_int32_t i2cAddress = I2C_ADDR_LOW);
    void bytesToInt16(u_int16_t* bytes);
    void convertThreshold(ddm_threshold_t& field);
    void fixThresholdBytes();
    void prepareDDMOutput();
    /**** CMIS helper functions *******/
    void getCmisModuleFlags(u_int32_t moduleOffset, u_int8_t* page0L);
    void getQsfpDdThresholds(u_int8_t* page2H);
    void getSfpDdThresholds(u_int8_t* page0H);
    void getQsfpDddLanesFlags(u_int8_t* page11H);
    void getSfpDddLanesFlags(u_int8_t* page0L);
    void getDdmValuesFromPddr();
    void prepareQsfpddDdmInfo();
    void prepareSfpddDdmInfo();
    /**********************************/
    void prepareQSFPDdmInfo();
    void prepareSFPDdmInfo();
    void prepareThresholdInfo(u_int8_t* page);
    void readCableDDMInfo();
    void setPrintDDMFlagsSection(MlxlinkCmdPrint& cmdPrint, const ddm_threshold_t& flags, const string& flagGroup);
    string getDDMThresholdRow(u_int16_t temp, u_int16_t volt, u_int16_t rxPower, u_int16_t txPower, u_int16_t txBias);
    bool readFromPage(u_int8_t* pageBuffer, u_int32_t fieldOffset, void* data, u_int32_t size = 1);
    void addPageToOutputVector(u_int8_t* pageBuffer, u_int32_t page, u_int32_t offset, u_int32_t length);
    void checkParams(u_int16_t offset, u_int16_t length);
    u_int16_t getStatusBit(u_int32_t channel, u_int16_t val, u_int32_t statusMask);

    void getNumOfModuleLanes();
    u_int32_t getRateAdminFromStr(u_int32_t cap, const string& rateStr);
    u_int32_t getModeAdminFromStr(u_int32_t cap, const string& adminStr, ModuleAccess_t moduleAccess);
    bool getInvAdminFromStr(u_int32_t cap, const string& invStr, ModuleAccess_t moduleAccess);
    bool getSwapAdminFromStr(u_int32_t cap, const string& swapStr, ModuleAccess_t moduleAccess);
    u_int32_t getLanesFromStr(u_int32_t cap, const string& lanesStr);
    void getPMPTConfiguration(ModuleAccess_t moduleAccess,
                              vector<string>& prbsPattern,
                              vector<string>& prbsRate,
                              vector<string>& prbsInv,
                              vector<string>& prbsSwap);
    void getPMPDInfo(vector<string>& traffic, vector<string>& errors, vector<string>& ber, vector<string>& snr);
    string getPMPDLockStatus();
    void checkAndParsePMPTCap(ModuleAccess_t moduleAccess);
    u_int32_t getPMPTStatus(ModuleAccess_t moduleAccess);
    void sendPMPT(ModuleAccess_t moduleAccess);
    void enablePMPT(ModuleAccess_t moduleAccess);
    void disablePMPT();

    u_int32_t pmcrStrToValue(ControlParam paramId, const string& value);
    string getPMCRCapValueStr(u_int32_t valueCap, ControlParam paramId);
    void checkPMCRFieldsCap(vector<pair<ControlParam, string>>& params);
    string buildPMCRRequest(ControlParam paramId, const string& value);

    Json::Value& _jsonRoot;
    vector<page_t> _validPages;
    vector<MlxlinkCmdPrint> _pagesToDump;
    vector<MlxlinkCmdPrint> _cableDDMOutput;
    cable_ddm_q_t _cableDdm;
    u_int32_t _prbsRate;
    u_int32_t _prbsMode;
    bool _prbsInv;
    bool _prbsSwap;
    bool _swControlMode;
    u_int32_t _prbsLanes;
    map<ControlParam, pair<string, string>> _modulePMCRParams;
    float _txBiasMultiplier;
};

#endif /* MLXLINK_CABLES_COMMANDER_H */
