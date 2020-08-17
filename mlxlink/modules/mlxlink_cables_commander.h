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
#ifndef MLXLINK_CABLES_COMMANDER_H
#define MLXLINK_CABLES_COMMANDER_H

//#include "mlxlink_utils.h"
//#include <mtcr.h>
#include "mlxlink_reg_parser.h"

#define SHIFT_0                       0
#define SHIFT_1                       1
#define SHIFT_2                       2
#define SHIFT_3                       3
#define SHIFT_4                       4
#define SHIFT_5                       5
#define SHIFT_6                       6
#define SHIFT_7                       7
#define SHIFT_8                       8
#define SHIFT_9                       9
#define SHIFT_10                      10
#define SHIFT_11                      11
#define SHIFT_12                      12
#define SHIFT_13                      13
#define SHIFT_14                      14
#define SHIFT_15                      15
/*
 * QSFP Paging, Page 0 Low
 */

/* Module Monitor Interrupt Flags - 6-8 */
#define QSFP_TEMP_AW_OFFSET         0x06
#define QSFP_TEMP_HALARM_STATUS     (1 << SHIFT_7)
#define QSFP_TEMP_LALARM_STATUS     (1 << SHIFT_6)
#define QSFP_TEMP_HWARN_STATUS      (1 << SHIFT_5)
#define QSFP_TEMP_LWARN_STATUS      (1 << SHIFT_4)

#define QSFP_VCC_AW_OFFSET          0x07
#define QSFP_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define QSFP_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define QSFP_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define QSFP_VCC_LWARN_STATUS       (1 << SHIFT_4)

/* Channel Monitor Interrupt Flags - 9-21 */
#define QSFP_RX_PWR_12_AW_OFFSET    0x09
#define QSFP_RX_PWR_1_HALARM        (1 << SHIFT_7)
#define QSFP_RX_PWR_1_LALARM        (1 << SHIFT_6)
#define QSFP_RX_PWR_1_HWARN         (1 << SHIFT_5)
#define QSFP_RX_PWR_1_LWARN         (1 << SHIFT_4)
#define QSFP_RX_PWR_2_HALARM        (1 << SHIFT_3)
#define QSFP_RX_PWR_2_LALARM        (1 << SHIFT_2)
#define QSFP_RX_PWR_2_HWARN         (1 << SHIFT_1)
#define QSFP_RX_PWR_2_LWARN         (1 << SHIFT_0)

#define QSFP_RX_PWR_34_AW_OFFSET    0x0A
#define QSFP_RX_PWR_3_HALARM        (1 << SHIFT_7)
#define QSFP_RX_PWR_3_LALARM        (1 << SHIFT_6)
#define QSFP_RX_PWR_3_HWARN         (1 << SHIFT_5)
#define QSFP_RX_PWR_3_LWARN         (1 << SHIFT_4)
#define QSFP_RX_PWR_4_HALARM        (1 << SHIFT_3)
#define QSFP_RX_PWR_4_LALARM        (1 << SHIFT_2)
#define QSFP_RX_PWR_4_HWARN         (1 << SHIFT_1)
#define QSFP_RX_PWR_4_LWARN         (1 << SHIFT_0)

#define QSFP_TX_BIAS_12_AW_OFFSET    0x0B
#define QSFP_TX_BIAS_1_HALARM       (1 << SHIFT_7)
#define QSFP_TX_BIAS_1_LALARM       (1 << SHIFT_6)
#define QSFP_TX_BIAS_1_HWARN        (1 << SHIFT_5)
#define QSFP_TX_BIAS_1_LWARN        (1 << SHIFT_4)
#define QSFP_TX_BIAS_2_HALARM       (1 << SHIFT_3)
#define QSFP_TX_BIAS_2_LALARM       (1 << SHIFT_2)
#define QSFP_TX_BIAS_2_HWARN        (1 << SHIFT_1)
#define QSFP_TX_BIAS_2_LWARN        (1 << SHIFT_0)

#define QSFP_TX_BIAS_34_AW_OFFSET   0x0C
#define QSFP_TX_BIAS_3_HALARM       (1 << SHIFT_7)
#define QSFP_TX_BIAS_3_LALARM       (1 << SHIFT_6)
#define QSFP_TX_BIAS_3_HWARN        (1 << SHIFT_5)
#define QSFP_TX_BIAS_3_LWARN        (1 << SHIFT_4)
#define QSFP_TX_BIAS_4_HALARM       (1 << SHIFT_3)
#define QSFP_TX_BIAS_4_LALARM       (1 << SHIFT_2)
#define QSFP_TX_BIAS_4_HWARN        (1 << SHIFT_1)
#define QSFP_TX_BIAS_4_LWARN        (1 << SHIFT_0)

#define QSFP_TX_PWR_12_AW_OFFSET    0x0D
#define QSFP_TX_PWR_1_HALARM        (1 << SHIFT_7)
#define QSFP_TX_PWR_1_LALARM        (1 << SHIFT_6)
#define QSFP_TX_PWR_1_HWARN         (1 << SHIFT_5)
#define QSFP_TX_PWR_1_LWARN         (1 << SHIFT_4)
#define QSFP_TX_PWR_2_HALARM        (1 << SHIFT_3)
#define QSFP_TX_PWR_2_LALARM        (1 << SHIFT_2)
#define QSFP_TX_PWR_2_HWARN         (1 << SHIFT_1)
#define QSFP_TX_PWR_2_LWARN         (1 << SHIFT_0)

#define QSFP_TX_PWR_34_AW_OFFSET    0x0E
#define QSFP_TX_PWR_3_HALARM        (1 << SHIFT_7)
#define QSFP_TX_PWR_3_LALARM        (1 << SHIFT_6)
#define QSFP_TX_PWR_3_HWARN         (1 << SHIFT_5)
#define QSFP_TX_PWR_3_LWARN         (1 << SHIFT_4)
#define QSFP_TX_PWR_4_HALARM        (1 << SHIFT_3)
#define QSFP_TX_PWR_4_LALARM        (1 << SHIFT_2)
#define QSFP_TX_PWR_4_HWARN         (1 << SHIFT_1)
#define QSFP_TX_PWR_4_LWARN         (1 << SHIFT_0)

/* Module Monitoring Values - 22-33 */
#define QSFP_TEMP_CURR          0x16
#define QSFP_TEMP_MSB_OFFSET     0x16
#define QSFP_TEMP_LSB_OFFSET     0x17

#define QSFP_VCC_CURR           0x1A
#define QSFP_VCC_MSB_OFFSET      0x1A
#define QSFP_VCC_LSB_OFFSET      0x1B

/* Channel Monitoring Values - 34-81 */
#define QSFP_RX_PWR_1_OFFSET     0x22
#define QSFP_RX_PWR_2_OFFSET     0x24
#define QSFP_RX_PWR_3_OFFSET     0x26
#define QSFP_RX_PWR_4_OFFSET     0x28

#define QSFP_TX_BIAS_1_OFFSET    0x2A
#define QSFP_TX_BIAS_2_OFFSET    0x2C
#define QSFP_TX_BIAS_3_OFFSET    0x2E
#define QSFP_TX_BIAS_4_OFFSET    0x30

#define QSFP_TX_PWR_1_OFFSET     0x32
#define QSFP_TX_PWR_2_OFFSET     0x34
#define QSFP_TX_PWR_3_OFFSET     0x36
#define QSFP_TX_PWR_4_OFFSET     0x38

// Page 3 High
#define QSFP_TEMP_HALRM          0x00
#define QSFP_TEMP_LALRM          0x02
#define QSFP_TEMP_HWARN          0x04
#define QSFP_TEMP_LWARN          0x06

#define QSFP_VCC_HALRM           0x10
#define QSFP_VCC_LALRM           0x12
#define QSFP_VCC_HWARN           0x14
#define QSFP_VCC_LWARN           0x16

#define QSFP_RX_PWR_HALRM        0x30
#define QSFP_RX_PWR_LALRM        0x32
#define QSFP_RX_PWR_HWARN        0x34
#define QSFP_RX_PWR_LWARN        0x36

#define QSFP_TX_BIAS_HALRM       0x38
#define QSFP_TX_BIAS_LALRM       0x3A
#define QSFP_TX_BIAS_HWARN       0x3C
#define QSFP_TX_BIAS_LWARN       0x3E

#define QSFP_TX_PWR_HALRM        0x40
#define QSFP_TX_PWR_LALRM        0x42
#define QSFP_TX_PWR_HWARN        0x44
#define QSFP_TX_PWR_LWARN        0x46

// SFP 51 Paging, Page 0x1 Low
#define SFP51_BASE               0x100

/* A2-based offsets for DOM */

#define SFP51_TEMP_HALRM         0
#define SFP51_TEMP_LALRM         2
#define SFP51_TEMP_HWARN         4
#define SFP51_TEMP_LWARN         6

#define SFP51_VCC_HALRM          8
#define SFP51_VCC_LALRM          10
#define SFP51_VCC_HWARN          12
#define SFP51_VCC_LWARN          14

#define SFP51_BIAS_HALRM         16
#define SFP51_BIAS_LALRM         18
#define SFP51_BIAS_HWARN         20
#define SFP51_BIAS_LWARN         22

#define SFP51_TX_PWR_HALRM       24
#define SFP51_TX_PWR_LALRM       26
#define SFP51_TX_PWR_HWARN       28
#define SFP51_TX_PWR_LWARN       30

#define SFP51_RX_PWR_HALRM       32
#define SFP51_RX_PWR_LALRM       34
#define SFP51_RX_PWR_HWARN       36
#define SFP51_RX_PWR_LWARN       38

#define SFP51_TEMP               96
#define SFP51_VCC                98
#define SFP51_BIAS               100
#define SFP51_TX_PWR             102
#define SFP51_RX_PWR             104

#define SFP51_ALRM_FLG              112
#define SFP51_TX_PWR_LALRM_FLG      (1 << SHIFT_0)
#define SFP51_TX_PWR_HALRM_FLG      (1 << SHIFT_1)
#define SFP51_BIAS_LALRM_FLG        (1 << SHIFT_2)
#define SFP51_BIAS_HALRM_FLG        (1 << SHIFT_3)
#define SFP51_VCC_LALRM_FLG         (1 << SHIFT_4)
#define SFP51_VCC_HALRM_FLG         (1 << SHIFT_5)
#define SFP51_TEMP_LALRM_FLG        (1 << SHIFT_6)
#define SFP51_TEMP_HALRM_FLG        (1 << SHIFT_7)
#define SFP51_RX_PWR_LALRM_FLG      (1 << SHIFT_14)
#define SFP51_RX_PWR_HALRM_FLG      (1 << SHIFT_15)

#define SFP51_WARN_FLG              116
#define SFP51_TX_PWR_LWARN_FLG      (1 << SHIFT_0)
#define SFP51_TX_PWR_HWARN_FLG      (1 << SHIFT_1)
#define SFP51_BIAS_LWARN_FLG        (1 << SHIFT_2)
#define SFP51_BIAS_HWARN_FLG        (1 << SHIFT_3)
#define SFP51_VCC_LWARN_FLG         (1 << SHIFT_4)
#define SFP51_VCC_HWARN_FLG         (1 << SHIFT_5)
#define SFP51_TEMP_LWARN_FLG        (1 << SHIFT_6)
#define SFP51_TEMP_HWARN_FLG        (1 << SHIFT_7)
#define SFP51_RX_PWR_LWARN_FLG      (1 << SHIFT_14)
#define SFP51_RX_PWR_HWARN_FLG      (1 << SHIFT_15)

/*
 * QSFP-DD Paging, Page 0 Low
 */

/* Module Monitor Interrupt Flags */
#define QSFP_DD_MODULE_INFO_OFFSET     0x09
#define CMIS_TEMP_HALARM_STATUS     (1 << SHIFT_3)
#define CMIS_TEMP_LALARM_STATUS     (1 << SHIFT_2)
#define CMIS_TEMP_HWARN_STATUS      (1 << SHIFT_1)
#define CMIS_TEMP_LWARN_STATUS      (1 << SHIFT_0)
#define CMIS_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define CMIS_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define CMIS_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define CMIS_VCC_LWARN_STATUS       (1 << SHIFT_4)

/* Channels Monitor Interrupt Flags */
// QSFP-DD from upper page 0x11
#define QSFP_DD_TX_POWER_HALARM_OFFSET  0x8b // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_LALARM_OFFSET  0x8c // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_HWARN_OFFSET   0x8d // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_LWARN_OFFSET   0x8e // 0:7 for 8 channels

#define QSFP_DD_TX_BIAS_HALARM_OFFSET   0x8f // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_LALARM_OFFSET   0x90 // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_HWARN_OFFSET    0x91 // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_LWARN_OFFSET    0x92 // 0:7 for 8 channels

#define QSFP_DD_RX_POWER_HALARM_OFFSET  0x95 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_LALARM_OFFSET  0x96 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_HWARN_OFFSET   0x97 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_LWARN_OFFSET   0x98 // 0:7 for 8 channels

// Thresholds from upper page 0x2
#define QSFP_DD_TEMP_THR_OFFSET         0x80 // halarm 80, lalarm 82, hwarn 84, lwarn 86
#define QSFP_DD_VCC_THR_OFFSET          0x88 // halarm 88, lalarm 90, hwarn 92, lwarn 94
#define QSFP_DD_TX_POWER_THR_OFFSET     0xb0 // halarm b0, lalarm b2, hwarn b4, lwarn b6
#define QSFP_DD_TX_BIAS_THR_OFFSET      0xb8 // halarm b8, lalarm ba, hwarn bc, lwarn be
#define QSFP_DD_RX_POWER_THR_OFFSET     0xc0 // halarm c0, lalarm c2, hwar9n c4, lwarn c6

// SFP-DD from lower page 0
/* Module Monitor Interrupt Flags */
#define SFP_DD_MODULE_INFO_OFFSET      0x11
// See QSFP-DD module section for mask info

#define SFP_DD_VCC_AW_OFFSET           0x11
#define SFP_DD_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define SFP_DD_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define SFP_DD_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define SFP_DD_VCC_LWARN_STATUS       (1 << SHIFT_4)

// Channels monitor interrupt flags from lower page 0x0
#define SFP_DD_TX_POWER_INT_OFFSET      0x8
#define SFP_DD_TX_BIAS_INT_OFFSET       0x9
#define SFP_DD_RX_POWER_INT_OFFSET      0x7
#define SFP_DD_HALARM_STATUS            SHIFT_0 // 0:1 for 2 channels
#define SFP_DD_LALARM_STATUS            SHIFT_2 // 2:3 for 2 channels
#define SFP_DD_HWARN_STATUS             SHIFT_4 // 4:5 for 2 channels
#define SFP_DD_LWARN_STATUS             SHIFT_6 // 6:7 for 2 channels

// Thresholds from upper page 0x2
#define SFP_DD_TEMP_THR_OFFSET          0xb1 // halarm b1, lalarm b3, hwarn b5, lwarn b7
#define SFP_DD_VCC_THR_OFFSET           0xb9 // halarm b9, lalarm bb, hwarn bd, lwarn bf
#define SFP_DD_TX_POWER_THR_OFFSET      0xd1 // halarm d1, lalarm d3, hwarn d5, lwarn d7
#define SFP_DD_TX_BIAS_THR_OFFSET       0xd9 // halarm d9, lalarm db, hwarn dd, lwarn df
#define SFP_DD_RX_POWER_THR_OFFSET      0xe1 // halarm e1, lalarm e3, hwarn e5, lwarn e7

typedef struct {
    u_int16_t val;
    u_int16_t high_warn;
    u_int16_t low_warn;
    u_int16_t high_alarm;
    u_int16_t low_alarm;
    u_int8_t high_warn_flag;
    u_int8_t low_warn_flag;
    u_int8_t high_alarm_flag;
    u_int8_t low_alarm_flag;
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
    void getCmisDdmValues();
    void prepareQsfpddDdmInfo();
    void prepareSfpddDdmInfo();
    /**********************************/
    void prepareQSFPDdmInfo();
    void prepareSFPDdmInfo();
    void prepareThresholdInfo(u_int8_t *page);
    void readCableDDMInfo();
    void setPrintDDMFlagsSection(MlxlinkCmdPrint &cmdPrint, u_int32_t startIndx,
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
