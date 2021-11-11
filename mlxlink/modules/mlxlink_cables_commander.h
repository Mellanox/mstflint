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

//#include "mlxlink_utils.h"
//#include <mtcr.h>
#include "mlxlink_reg_parser.h"

typedef struct {
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

typedef struct {
    ddm_threshold_t temperature;
    ddm_threshold_t voltage;
    ddm_threshold_t rx_power[8];
    ddm_threshold_t tx_power[8];
    ddm_threshold_t tx_bias[8];
    int channels;
} cable_ddm_q_t;

#define LOWER_PAGE_OFFSET           0x0
#define UPPER_PAGE_OFFSET           0x80
#define EEPROM_MAX_BYTES            32
#define EEPROM_IDENTIFIER_BYTE_MASK 0xff
#define I2C_ADDR_LOW                0x50
#define I2C_ADDR_HIGH               0x51
#define EEPROM_PAGE_LENGTH          255
#define CABLE_PAGE_SIZE             0x80
#define DWORD_BLOCK_SIZE            32
#define QSFP_CHANNELS               4
#define SFP_CHANNELS                1
#define DDM_THRES_B_SZ              2
#define CMIS_CHANNELS               8
#define CMIS_MODULE_CHANNEL         1

#define EXTENDED_PAGES_1_2_10_11_ADDR   2
#define EXTENDED_PAGES_1_2_10_11_MASK   0x80
#define EXTENDED_PAGES_4_12_ADDR        155
#define EXTENDED_PAGES_4_12_MASK        0x40
#define EXTENDED_PAGES_13_14_ADDR       142
#define EXTENDED_PAGES_13_14_MASK       0x20

#define VOLT_UNIT 1000
#define MILLIVOLT_UNIT 10

typedef struct Page{
    u_int32_t page;
    u_int16_t offset;
    u_int16_t i2cAddress;
} page_t;

enum MODULE_PAGE {
    PAGE_0 = 0x0,
    PAGE_01 = 0x1,
    PAGE_02 = 0x2,
    PAGE_03 = 0x3,
    PAGE_04 = 0x4,
    PAGE_10 = 0x10,
    PAGE_11 = 0x11,
    PAGE_12 = 0x12,
    PAGE_13 = 0x13,
    PAGE_14 = 0x14,
    PAGE_20 = 0x20,
    PAGE_21 = 0x21,
    PAGE_LAST
};

using namespace std;

class MlxlinkCablesCommander :public MlxlinkRegParser{
public:
    MlxlinkCablesCommander(Json::Value &jsonRoot);
    virtual ~MlxlinkCablesCommander();

    void readMCIA(u_int32_t page, u_int32_t size, u_int32_t offset,
            u_int8_t * data, u_int32_t i2cAddress);
    void writeMCIA(u_int32_t page, u_int32_t size, u_int32_t numberOfZeroBytes,
            u_int32_t offset, u_int8_t * data, u_int32_t i2cAddress);

    void initValidPages();
    void loadEEPRMPage(u_int32_t pageNum, u_int32_t offset, u_int8_t* data,
            u_int32_t i2cAddress = I2C_ADDR_LOW);
    void bytesToInt16(u_int16_t *bytes);
    void convertThreshold(ddm_threshold_t &field);
    void fixThresholdBytes();
    vector<MlxlinkCmdPrint> getCableDDM();
    void prepareDDMOutput();
    /**** CMIS helper functions *******/
    void getCmisModuleFlags(u_int32_t moduleOffset, u_int8_t *page0L);
    void getQsfpDdThresholds(u_int8_t *page2H);
    void getSfpDdThresholds(u_int8_t *page0H);
    void getQsfpDddLanesFlags(u_int8_t *page11H);
    void getSfpDddLanesFlags(u_int8_t *page0L);
    void getDdmValuesFromPddr();
    void prepareQsfpddDdmInfo();
    void prepareSfpddDdmInfo();
    /**********************************/
    void prepareQSFPDdmInfo();
    void prepareSFPDdmInfo();
    void prepareThresholdInfo(u_int8_t *page);
    void readCableDDMInfo();
    void setPrintDDMFlagsSection(MlxlinkCmdPrint &cmdPrint,
            const ddm_threshold_t &flags, const string &flagGroup);
    string getDDMThresholdRow(u_int16_t temp, u_int16_t volt,  u_int16_t rxPower,
            u_int16_t txPower, u_int16_t txBias);
    vector<MlxlinkCmdPrint> getPagesToDump();
    bool readFromPage(u_int8_t *pageBuffer, u_int32_t fieldOffset, void *data,
            u_int32_t size = 1);
    void addPageToOutputVector(u_int8_t *pageBuffer, u_int32_t page, u_int32_t offset,
                u_int32_t length);
    void checkParams(u_int16_t page , u_int16_t offset, u_int16_t length);
    void writeToEEPROM(u_int16_t page , u_int16_t offset, vector<u_int8_t> &bytesToWrite);
    MlxlinkCmdPrint readFromEEPRM(u_int16_t page , u_int16_t offset, u_int16_t length);
    u_int16_t getStatusBit(u_int32_t channel, u_int16_t val, u_int32_t statusMask);

    u_int32_t _moduleNumber;
    u_int32_t _cableIdentifier;
    bool _sfp51Paging;
    bool _passiveQsfp;
    u_int32_t _localPort;
    u_int32_t _numOfLanes;

private:
    Json::Value &_jsonRoot;
    vector<page_t> _validPages;
    vector<MlxlinkCmdPrint> _pagesToDump;
    vector<MlxlinkCmdPrint> _cableDDMOutput;
    cable_ddm_q_t _cableDdm;
};

#endif /* MLXLINK_CABLES_COMMANDER_H */
