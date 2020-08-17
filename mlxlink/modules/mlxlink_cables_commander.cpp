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

#include "mlxlink_cables_commander.h"

MlxlinkCablesCommander::MlxlinkCablesCommander(Json::Value &jsonRoot): _jsonRoot(jsonRoot)
{
    _moduleNumber = 0;
    _sfp51Paging = false;
    _passiveQsfp = false;
    _localPort = 0;
    _numOfLanes = 0;
}

MlxlinkCablesCommander::~MlxlinkCablesCommander()
{
}

// Read EEPROM data from MCIA register
void MlxlinkCablesCommander::readMCIA(u_int32_t page, u_int32_t size,
        u_int32_t offset, u_int8_t * data, u_int32_t i2cAddress)
{
    string regName = "MCIA";
    resetParser(regName);
    updateField("module", _moduleNumber);
    updateField("size", size);
    updateField("page_number", page);
    updateField("device_address", offset);
    updateField("i2c_device_address", i2cAddress);
    updateField("l", 0);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t i = 0;
    char fieldName[16];
    for ( ; i < size/4 ; i++) {
        sprintf(fieldName, "dword[%d]", i);
        u_int32_t s = getFieldValue(std::string(fieldName));
        s = __be32_to_cpu(s);
        memcpy(data + (i*4), &s, sizeof(u_int32_t));
    }
}

// Write EEPROM data to MCIA register
void MlxlinkCablesCommander::writeMCIA(u_int32_t page, u_int32_t size,
        u_int32_t numberOfZeroBytes, u_int32_t offset, u_int8_t * data,
        u_int32_t i2cAddress)
{
    u_int32_t dataSize = size - numberOfZeroBytes;
    if ((dataSize + offset -1) > EEPROM_PAGE_LENGTH) {
        throw MlxRegException(
                        "Data exceeded the maximum page size (255 bytes), check the offset or data size");
    }
    string regName = "MCIA";
    resetParser(regName);
    updateField("module", _moduleNumber);
    updateField("size", dataSize);
    updateField("page_number", page);
    updateField("device_address", offset);
    updateField("i2c_device_address", i2cAddress);
    updateField("l", 1);
    u_int32_t i = 0;
    char fieldName[16];
    u_int32_t dwordDataSize = (u_int32_t)ceil((double)size/sizeof(u_int32_t));
    u_int32_t *dwordData = (u_int32_t*)malloc(dwordDataSize);
    memset(dwordData, 0, dwordDataSize);
    memcpy(dwordData, data, size);
    for ( ; i < dwordDataSize ; i++) {
        sprintf(fieldName, "dword[%d]", i);
        updateField(fieldName, __cpu_to_be32(dwordData[i]));
    }
    delete dwordData;
    genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
}

// Reading EEPROM data from MCIA register and loading it to readable pages
void MlxlinkCablesCommander::loadEEPRMPage(u_int32_t pageNum, u_int32_t offset,
        u_int8_t* data, u_int32_t i2cAddress)
{
    memset(data, 0, CABLE_PAGE_SIZE);
    u_int32_t pageOffset = 0;
    for (u_int8_t i = 0; i < (CABLE_PAGE_SIZE/EEPROM_MAX_BYTES); i++) {
        pageOffset = EEPROM_MAX_BYTES * i;
        readMCIA(pageNum, EEPROM_MAX_BYTES, offset + pageOffset,
                data + pageOffset, i2cAddress);
    }
}

// Reading specific addres from the page
bool MlxlinkCablesCommander::readFromPage(u_int8_t *pageBuffer, u_int32_t fieldOffset,
                                    void *data, u_int32_t size)
{
    if (pageBuffer) {
        memcpy((u_int8_t *)data, &pageBuffer[fieldOffset], sizeof(u_int8_t) * size);
        return true;
    }
    return false;
}

// Converting byte to u_int16_t
void MlxlinkCablesCommander::bytesToInt16(u_int16_t *bytes)
{
    u_int8_t bytesArr[2];
    memcpy(bytesArr, bytes, 2);
    *bytes = bytesArr[0] << 8 | bytesArr[1];
}

// Converting threshold fields from byte to u_int16_t
void MlxlinkCablesCommander::convertThreshold(ddm_threshold_t &field)
{
    bytesToInt16(&(field.high_alarm));
    bytesToInt16(&(field.low_alarm));
    bytesToInt16(&(field.high_warn));
    bytesToInt16(&(field.low_warn));
}

// Fixing DDM fields from bytes to u_int16_t
void MlxlinkCablesCommander::fixThresholdBytes()
{
    int i = 0;
    convertThreshold(_cableDdm.temperature);
    convertThreshold(_cableDdm.voltage);
    for (i = 0; i < _cableDdm.channels; i++) {
        convertThreshold(_cableDdm.rx_power[i]);
        convertThreshold(_cableDdm.tx_power[i]);
        convertThreshold(_cableDdm.tx_bias[i]);
    }
}

// Reading the flag status accroding to channel number and the status mask
u_int16_t MlxlinkCablesCommander::getStatusBit(u_int32_t channel, u_int16_t val, u_int32_t statusMask)
{
    // For channels 2 and 4, we need the lower nibble
    statusMask = channel % 2? statusMask : statusMask>>4;
    return (val&statusMask) >> ((u_int32_t)log2(statusMask));
}


void MlxlinkCablesCommander::getCmisDdmValues()
{
    string regName = "PDDR";
    resetParser(regName);

    updateField("local_port", _localPort);
    updateField("pnat", 0);
    updateField("page_select", 3);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    _cableDdm.channels = _numOfLanes;
    _cableDdm.temperature.val = getFieldValue("temperature") / 256;
    _cableDdm.voltage.val = getFieldValue("voltage") / 10;

    string laneStr = "";
    for (int lane = 0; lane < _cableDdm.channels; lane++) {
        laneStr = to_string(lane);
        _cableDdm.rx_power[lane].val = (u_int16_t)(10000*pow(10.0, getPower(getFieldValue("rx_power_lane" + laneStr)) / 10.0));
        _cableDdm.tx_power[lane].val = (u_int16_t)(10000*pow(10.0, getPower(getFieldValue("tx_power_lane" + laneStr)) / 10.0));
        _cableDdm.tx_bias[lane].val = getFieldValue("tx_bias_lane" + laneStr);
    }
}

void MlxlinkCablesCommander::getQsfpDdThresholds(u_int8_t *page2H)
{
    readFromPage(page2H, QSFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.temperature.high_alarm, 2);
    readFromPage(page2H, QSFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.temperature.low_alarm, 2);
    readFromPage(page2H, QSFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.temperature.high_warn, 2);
    readFromPage(page2H, QSFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.temperature.low_warn, 2);

    readFromPage(page2H, QSFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.voltage.high_alarm, 2);
    readFromPage(page2H, QSFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.voltage.low_alarm, 2);
    readFromPage(page2H, QSFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.voltage.high_warn, 2);
    readFromPage(page2H, QSFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.voltage.low_warn, 2);

    readFromPage(page2H, QSFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.tx_power[0].high_alarm, 2);
    readFromPage(page2H, QSFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.tx_power[0].low_alarm, 2);
    readFromPage(page2H, QSFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.tx_power[0].high_warn, 2);
    readFromPage(page2H, QSFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.tx_power[0].low_warn, 2);

    readFromPage(page2H, QSFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.tx_bias[0].high_alarm, 2);
    readFromPage(page2H, QSFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.tx_bias[0].low_alarm, 2);
    readFromPage(page2H, QSFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.tx_bias[0].high_warn, 2);
    readFromPage(page2H, QSFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.tx_bias[0].low_warn, 2);

    readFromPage(page2H, QSFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.rx_power[0].high_alarm, 2);
    readFromPage(page2H, QSFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.rx_power[0].low_alarm, 2);
    readFromPage(page2H, QSFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.rx_power[0].high_warn, 2);
    readFromPage(page2H, QSFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.rx_power[0].low_warn, 2);
}

void MlxlinkCablesCommander::getCmisModuleFlags(u_int32_t moduleOffset, u_int8_t *page0L)
{
    u_int32_t tempVal = 0;
    readFromPage(page0L, moduleOffset, &tempVal);
    _cableDdm.temperature.high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_TEMP_HWARN_STATUS);
    _cableDdm.temperature.low_warn_flag =  getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_TEMP_LWARN_STATUS);
    _cableDdm.temperature.high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_TEMP_HALARM_STATUS);
    _cableDdm.temperature.low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_TEMP_LALARM_STATUS);
    tempVal = 0;
    readFromPage(page0L, moduleOffset, &tempVal);
    _cableDdm.voltage.high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_VCC_HWARN_STATUS);
    _cableDdm.voltage.low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_VCC_LWARN_STATUS);
    _cableDdm.voltage.high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_VCC_HALARM_STATUS);
    _cableDdm.voltage.low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                                            tempVal, CMIS_VCC_LALARM_STATUS);
}

void MlxlinkCablesCommander::getQsfpDddLanesFlags(u_int8_t *page11H)
{
    u_int16_t txPowerHAlarm = 0;
    u_int16_t txPowerLAlarm = 0;
    u_int16_t txPowerHWarn = 0;
    u_int16_t txPowerLWarn = 0;
    readFromPage(page11H, QSFP_DD_TX_POWER_HALARM_OFFSET - UPPER_PAGE_OFFSET, &txPowerHAlarm);
    readFromPage(page11H, QSFP_DD_TX_POWER_LALARM_OFFSET - UPPER_PAGE_OFFSET, &txPowerLAlarm);
    readFromPage(page11H, QSFP_DD_TX_POWER_HWARN_OFFSET - UPPER_PAGE_OFFSET, &txPowerHWarn);
    readFromPage(page11H, QSFP_DD_TX_POWER_LWARN_OFFSET - UPPER_PAGE_OFFSET, &txPowerLWarn);

    u_int16_t txBiasHAlarm = 0;
    u_int16_t txBiasLAlarm = 0;
    u_int16_t txBiasHWarn = 0;
    u_int16_t txBiasLWarn = 0;
    readFromPage(page11H, QSFP_DD_TX_BIAS_HALARM_OFFSET - UPPER_PAGE_OFFSET, &txBiasHAlarm);
    readFromPage(page11H, QSFP_DD_TX_BIAS_LALARM_OFFSET - UPPER_PAGE_OFFSET, &txBiasLAlarm);
    readFromPage(page11H, QSFP_DD_TX_BIAS_HWARN_OFFSET - UPPER_PAGE_OFFSET, &txBiasHWarn);
    readFromPage(page11H, QSFP_DD_TX_BIAS_LWARN_OFFSET - UPPER_PAGE_OFFSET, &txBiasLWarn);

    u_int16_t rxPowerHAlarm = 0;
    u_int16_t rxPowerLAlarm = 0;
    u_int16_t rxPowerHWarn = 0;
    u_int16_t rxPowerLWarn = 0;
    readFromPage(page11H, QSFP_DD_RX_POWER_HALARM_OFFSET - UPPER_PAGE_OFFSET, &rxPowerHAlarm);
    readFromPage(page11H, QSFP_DD_RX_POWER_LALARM_OFFSET - UPPER_PAGE_OFFSET, &rxPowerLAlarm);
    readFromPage(page11H, QSFP_DD_RX_POWER_HWARN_OFFSET - UPPER_PAGE_OFFSET, &rxPowerHWarn);
    readFromPage(page11H, QSFP_DD_RX_POWER_LWARN_OFFSET - UPPER_PAGE_OFFSET, &rxPowerLWarn);

    for (int i = 0; i < _cableDdm.channels; i++) {
        _cableDdm.rx_power[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, rxPowerLWarn, i);
        _cableDdm.rx_power[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, rxPowerHWarn, i);
        _cableDdm.rx_power[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, rxPowerLAlarm, i);
        _cableDdm.rx_power[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, rxPowerHAlarm, i);

        _cableDdm.tx_power[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, txPowerLWarn, i);
        _cableDdm.tx_power[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, txPowerHWarn, i);
        _cableDdm.tx_power[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, txPowerLAlarm, i);
        _cableDdm.tx_power[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, txPowerHAlarm, i);

        _cableDdm.tx_bias[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, txBiasLWarn, i);
        _cableDdm.tx_bias[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, txBiasHWarn, i);
        _cableDdm.tx_bias[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, txBiasLAlarm, i);
        _cableDdm.tx_bias[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, txBiasHAlarm, i);
    }
}

void MlxlinkCablesCommander::prepareQsfpddDdmInfo()
{
    // Read DDM fields from PDDR
    getCmisDdmValues();

    // Read module flags
    u_int8_t *page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
    getCmisModuleFlags(QSFP_DD_MODULE_INFO_OFFSET, page0L);

    // Read lanes flags
    u_int8_t *page11H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_11, UPPER_PAGE_OFFSET, page11H);
    getQsfpDddLanesFlags(page11H);

    // Get cable thresholds
    u_int8_t *page2H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_02, UPPER_PAGE_OFFSET, page2H);
    getQsfpDdThresholds(page2H);

    delete page0L;
    delete page11H;
    delete page2H;
}

void MlxlinkCablesCommander::getSfpDdThresholds(u_int8_t *page0H)
{
    readFromPage(page0H, SFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.temperature.high_alarm, 2);
    readFromPage(page0H, SFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.temperature.low_alarm, 2);
    readFromPage(page0H, SFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.temperature.high_warn, 2);
    readFromPage(page0H, SFP_DD_TEMP_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.temperature.low_warn, 2);

    readFromPage(page0H, SFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.voltage.high_alarm, 2);
    readFromPage(page0H, SFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.voltage.low_alarm, 2);
    readFromPage(page0H, SFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.voltage.high_warn, 2);
    readFromPage(page0H, SFP_DD_VCC_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.voltage.low_warn, 2);

    readFromPage(page0H, SFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.tx_power[0].high_alarm, 2);
    readFromPage(page0H, SFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.tx_power[0].low_alarm, 2);
    readFromPage(page0H, SFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.tx_power[0].high_warn, 2);
    readFromPage(page0H, SFP_DD_TX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.tx_power[0].low_warn, 2);

    readFromPage(page0H, SFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.tx_bias[0].high_alarm, 2);
    readFromPage(page0H, SFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.tx_bias[0].low_alarm, 2);
    readFromPage(page0H, SFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.tx_bias[0].high_warn, 2);
    readFromPage(page0H, SFP_DD_TX_BIAS_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.tx_bias[0].low_warn, 2);

    readFromPage(page0H, SFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET, &_cableDdm.rx_power[0].high_alarm, 2);
    readFromPage(page0H, SFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 2, &_cableDdm.rx_power[0].low_alarm, 2);
    readFromPage(page0H, SFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 4, &_cableDdm.rx_power[0].high_warn, 2);
    readFromPage(page0H, SFP_DD_RX_POWER_THR_OFFSET - UPPER_PAGE_OFFSET + 6, &_cableDdm.rx_power[0].low_warn, 2);
}

void MlxlinkCablesCommander::getSfpDddLanesFlags(u_int8_t *page0L)
{
    u_int32_t txPowerInturrept = 0;
    u_int32_t txBiasInturrept = 0;
    u_int32_t rxPowerInturrept = 0;
    readFromPage(page0L, SFP_DD_TX_POWER_INT_OFFSET, &txPowerInturrept);
    readFromPage(page0L, SFP_DD_TX_BIAS_INT_OFFSET, &txBiasInturrept);
    readFromPage(page0L, SFP_DD_RX_POWER_INT_OFFSET, &rxPowerInturrept);

    for (int i = 0 ; i < _cableDdm.channels ; i++) {
        _cableDdm.rx_power[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                rxPowerInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.rx_power[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                rxPowerInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.rx_power[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                rxPowerInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.rx_power[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                rxPowerInturrept >> SFP_DD_HALARM_STATUS, i);

        _cableDdm.tx_power[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txPowerInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.tx_power[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txPowerInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.tx_power[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txPowerInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.tx_power[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txPowerInturrept >> SFP_DD_HALARM_STATUS, i);

        _cableDdm.tx_bias[i].low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txBiasInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.tx_bias[i].high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txBiasInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.tx_bias[i].low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txBiasInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.tx_bias[i].high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL,
                txBiasInturrept >> SFP_DD_HALARM_STATUS, i);
    }
}

void MlxlinkCablesCommander::prepareSfpddDdmInfo()
{
    // Read DDM fields from PDDR
    getCmisDdmValues();

    // Read module flags
    u_int8_t *page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
    getCmisModuleFlags(QSFP_DD_MODULE_INFO_OFFSET, page0L);

    // Read lanes flags
    getSfpDddLanesFlags(page0L);

    // Get cable thresholds
    u_int8_t *page0H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, UPPER_PAGE_OFFSET, page0H);
    getSfpDdThresholds(page0H);

    delete page0H;
    delete page0L;
}

// Preparing QSFP DDM information
void MlxlinkCablesCommander::prepareQSFPDdmInfo()
{
    u_int8_t voltage[2] = {0};
    u_int8_t rx_powers[QSFP_CHANNELS * 2] = {0};
    u_int8_t tx_powers[QSFP_CHANNELS * 2] = {0};
    u_int8_t tx_bias[QSFP_CHANNELS * 2] = {0};
    u_int32_t temperature_val = 0;
    u_int32_t tempVal = 0;
    u_int8_t *page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
    readFromPage(page0L, QSFP_TEMP_CURR, &temperature_val, 2);
    readFromPage(page0L, QSFP_TEMP_AW_OFFSET, &tempVal);
    _cableDdm.temperature.high_warn_flag = (tempVal & QSFP_TEMP_HWARN_STATUS);
    _cableDdm.temperature.low_warn_flag = (tempVal & QSFP_TEMP_LWARN_STATUS);
    _cableDdm.temperature.high_alarm_flag = (tempVal & QSFP_TEMP_HALARM_STATUS);
    _cableDdm.temperature.low_alarm_flag = (tempVal & QSFP_TEMP_LALARM_STATUS);

    readFromPage(page0L, QSFP_VCC_CURR, voltage, 2);
    tempVal = 0;
    readFromPage(page0L, QSFP_VCC_AW_OFFSET, &tempVal);
    _cableDdm.voltage.high_warn_flag = (tempVal & QSFP_VCC_HWARN_STATUS);
    _cableDdm.voltage.low_warn_flag = (tempVal & QSFP_VCC_LWARN_STATUS);
    _cableDdm.voltage.high_alarm_flag = (tempVal & QSFP_VCC_HALARM_STATUS);
    _cableDdm.voltage.low_alarm_flag = (tempVal & QSFP_VCC_LALARM_STATUS);

    readFromPage(page0L, QSFP_RX_PWR_1_OFFSET, rx_powers, QSFP_CHANNELS * 2);
    readFromPage(page0L, QSFP_TX_PWR_1_OFFSET, tx_powers, QSFP_CHANNELS * 2);
    readFromPage(page0L, QSFP_TX_BIAS_1_OFFSET, tx_bias, QSFP_CHANNELS * 2);

    u_int8_t nextTwoChannels = 0;
    for (u_int32_t i = 1; i <= QSFP_CHANNELS; i++) {
        nextTwoChannels = (i > QSFP_CHANNELS/2)? 1 : 0;
        tempVal = 0;
        readFromPage(page0L, QSFP_RX_PWR_12_AW_OFFSET + nextTwoChannels, &tempVal);

        _cableDdm.rx_power[i - 1].low_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_RX_PWR_1_LWARN);
        _cableDdm.rx_power[i - 1].high_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_RX_PWR_1_HWARN);
        _cableDdm.rx_power[i - 1].low_alarm_flag = getStatusBit(i, tempVal,
                                                     QSFP_RX_PWR_1_LALARM);
        _cableDdm.rx_power[i - 1].high_alarm_flag = getStatusBit(i, tempVal,
                                                     QSFP_RX_PWR_1_HALARM);

        tempVal = 0;
        readFromPage(page0L, QSFP_TX_PWR_12_AW_OFFSET + nextTwoChannels, &tempVal);
        _cableDdm.tx_power[i - 1].low_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_PWR_1_LWARN);
        _cableDdm.tx_power[i - 1].high_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_PWR_1_HWARN);
        _cableDdm.tx_power[i - 1].low_alarm_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_PWR_1_LALARM);
        _cableDdm.tx_power[i - 1].high_alarm_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_PWR_1_HALARM);

        tempVal = 0;
        readFromPage(page0L, QSFP_TX_BIAS_12_AW_OFFSET + nextTwoChannels, &tempVal);
        _cableDdm.tx_bias[i - 1].low_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_BIAS_1_LWARN);
        _cableDdm.tx_bias[i - 1].high_warn_flag = getStatusBit(i, tempVal,
                                                     QSFP_TX_BIAS_1_HWARN);
        _cableDdm.tx_bias[i - 1].low_alarm_flag = getStatusBit(i, tempVal,
                                                    QSFP_TX_BIAS_1_LALARM);
        _cableDdm.tx_bias[i - 1].high_alarm_flag = getStatusBit(i, tempVal,
                                                    QSFP_TX_BIAS_1_HALARM);
    }

    _cableDdm.channels = QSFP_CHANNELS;
    _cableDdm.temperature.val = (u_int8_t)temperature_val;
    _cableDdm.voltage.val = voltage[0] << 8 | voltage[1];
    for (int i = 0; i < _cableDdm.channels; i++) {
        _cableDdm.rx_power[i].val = rx_powers[2 * i] << 8 | rx_powers[2 * i + 1];
        _cableDdm.tx_power[i].val = tx_powers[2 * i] << 8 | tx_powers[2 * i + 1];
        _cableDdm.tx_bias[i].val  = tx_bias[2 * i] << 8 | tx_bias[2 * i + 1];
    }
    delete page0L;
}

// Preparing SFP DDM information
void MlxlinkCablesCommander::prepareSFPDdmInfo()
{
    u_int8_t voltage[2] = {0};
    u_int8_t rx_powers[QSFP_CHANNELS * 2] = {0};
    u_int8_t tx_powers[QSFP_CHANNELS * 2] = {0};
    u_int8_t tx_bias[QSFP_CHANNELS * 2] = {0};
    u_int32_t temperature_val = 0;
    u_int32_t tempVal = 0;
    u_int8_t *sfp51Page = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_01, LOWER_PAGE_OFFSET, sfp51Page, I2C_ADDR_HIGH);

    readFromPage(sfp51Page, SFP51_TEMP, &temperature_val, 2);
    readFromPage(sfp51Page, SFP51_VCC, voltage, 2);

    tempVal = 0;
    readFromPage(sfp51Page, SFP51_RX_PWR, rx_powers, SFP_CHANNELS * 2);
    readFromPage(sfp51Page, SFP51_TX_PWR, tx_powers, SFP_CHANNELS * 2);
    readFromPage(sfp51Page, SFP51_BIAS, tx_bias, SFP_CHANNELS * 2);

    tempVal = 0;
    readFromPage(sfp51Page, SFP51_ALRM_FLG, &tempVal, 2);
    _cableDdm.tx_power[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TX_PWR_LWARN_FLG);
    _cableDdm.tx_power[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TX_PWR_HWARN_FLG);
    _cableDdm.tx_bias[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_BIAS_LWARN_FLG);
    _cableDdm.tx_bias[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_BIAS_HWARN_FLG);
    _cableDdm.voltage.low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_VCC_LWARN_FLG);
    _cableDdm.voltage.high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_VCC_HWARN_FLG);
    _cableDdm.temperature.low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TEMP_LWARN_FLG);
    _cableDdm.temperature.high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TEMP_HWARN_FLG);
    _cableDdm.rx_power[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_RX_PWR_LWARN_FLG);
    _cableDdm.rx_power[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_RX_PWR_HWARN_FLG);

    tempVal = 0;
    readFromPage(sfp51Page, SFP51_WARN_FLG, &tempVal, 2);
    _cableDdm.tx_power[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TX_PWR_LALRM_FLG);
    _cableDdm.tx_power[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TX_PWR_HALRM_FLG);
    _cableDdm.tx_bias[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_BIAS_LALRM_FLG);
    _cableDdm.tx_bias[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_BIAS_HALRM_FLG);
    _cableDdm.voltage.low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_VCC_LALRM_FLG);
    _cableDdm.voltage.high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_VCC_HALRM_FLG);
    _cableDdm.temperature.low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TEMP_LALRM_FLG);
    _cableDdm.temperature.high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_TEMP_HALRM_FLG);
    _cableDdm.rx_power[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_RX_PWR_LALRM_FLG);
    _cableDdm.rx_power[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal,
                                                SFP51_RX_PWR_HALRM_FLG);

    _cableDdm.channels = SFP_CHANNELS;
    _cableDdm.temperature.val = (u_int8_t)temperature_val;
    _cableDdm.voltage.val = voltage[0] << 8 | voltage[1];
    for (int i = 0; i < _cableDdm.channels; i++) {
        _cableDdm.rx_power[i].val = rx_powers[2 * i] << 8 | rx_powers[2 * i + 1];
        _cableDdm.tx_power[i].val = tx_powers[2 * i] << 8 | tx_powers[2 * i + 1];
        _cableDdm.tx_bias[i].val  = tx_bias[2 * i] << 8 | tx_bias[2 * i + 1];
    }
    delete sfp51Page;
}

// Preparing thresholds information
void MlxlinkCablesCommander::prepareThresholdInfo(u_int8_t *thresholdPage)
{
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TEMP_HALRM : QSFP_TEMP_HALRM,
            &_cableDdm.temperature.high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TEMP_LALRM : QSFP_TEMP_LALRM,
            &_cableDdm.temperature.low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TEMP_HWARN : QSFP_TEMP_HWARN,
            &_cableDdm.temperature.high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TEMP_LWARN : QSFP_TEMP_LWARN,
            &_cableDdm.temperature.low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging? SFP51_VCC_HALRM : QSFP_VCC_HALRM,
            &_cableDdm.voltage.high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_VCC_LALRM : QSFP_VCC_LALRM,
            &_cableDdm.voltage.low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_VCC_HWARN : QSFP_VCC_HWARN,
            &_cableDdm.voltage.high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_VCC_LWARN : QSFP_VCC_LWARN,
            &_cableDdm.voltage.low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging? SFP51_RX_PWR_HALRM : QSFP_RX_PWR_HALRM,
            &_cableDdm.rx_power[0].high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_RX_PWR_LALRM : QSFP_RX_PWR_LALRM,
            &_cableDdm.rx_power[0].low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_RX_PWR_HWARN : QSFP_RX_PWR_HWARN,
            &_cableDdm.rx_power[0].high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_RX_PWR_LWARN : QSFP_RX_PWR_LWARN,
            &_cableDdm.rx_power[0].low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging? SFP51_TX_PWR_HALRM : QSFP_TX_PWR_HALRM,
            &_cableDdm.tx_power[0].high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TX_PWR_LALRM : QSFP_TX_PWR_LALRM,
            &_cableDdm.tx_power[0].low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TX_PWR_HWARN : QSFP_TX_PWR_HWARN,
            &_cableDdm.tx_power[0].high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_TX_PWR_LWARN : QSFP_TX_PWR_LWARN,
            &_cableDdm.tx_power[0].low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging? SFP51_BIAS_HALRM : QSFP_TX_BIAS_HALRM,
            &_cableDdm.tx_bias[0].high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_BIAS_LALRM : QSFP_TX_BIAS_LALRM,
            &_cableDdm.tx_bias[0].low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_BIAS_HWARN : QSFP_TX_BIAS_HWARN,
            &_cableDdm.tx_bias[0].high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging? SFP51_BIAS_LWARN : QSFP_TX_BIAS_LWARN,
            &_cableDdm.tx_bias[0].low_warn, 2);

}

// Reading cable DDM information
void MlxlinkCablesCommander::readCableDDMInfo()
{
    u_int8_t *thresholdPage = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);

    switch(_cableIdentifier) {
    case IDENTIFIER_QSFP28:
    case IDENTIFIER_QSFP_PLUS:
        prepareQSFPDdmInfo();
        loadEEPRMPage(PAGE_03, UPPER_PAGE_OFFSET, thresholdPage);
        prepareThresholdInfo(thresholdPage);
        break;
    case IDENTIFIER_SFP:
    case IDENTIFIER_QSA:
        prepareSFPDdmInfo();
        loadEEPRMPage(PAGE_01, LOWER_PAGE_OFFSET, thresholdPage, I2C_ADDR_HIGH);
        prepareThresholdInfo(thresholdPage);
        break;
    case IDENTIFIER_SFP_DD:
    case IDENTIFIER_QSFP_DD:
    case IDENTIFIER_OSFP:
        prepareQsfpddDdmInfo();
        break;
    }

    fixThresholdBytes();

    delete thresholdPage;
}

// Preparing and formating DDM flags section
void MlxlinkCablesCommander::setPrintDDMFlagsSection(MlxlinkCmdPrint &cmdPrint,
        u_int32_t startIndx, const ddm_threshold_t &flags, const string &flagGroup)
{
    char strBuff[32];
    string flagColor;
    sprintf(strBuff, "%0d", flags.high_alarm_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_ALARM);
    setPrintVal(cmdPrint, startIndx, IDENT + flagGroup + " Alarm high",
            strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d", flags.high_warn_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_WARN);
    setPrintVal(cmdPrint, startIndx + 1, IDENT + flagGroup +" Warning high",
            strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d", flags.low_warn_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_WARN);
    setPrintVal(cmdPrint, startIndx + 2, IDENT + flagGroup + " Warning low",
            strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d\n", flags.low_alarm_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_ALARM);
    setPrintVal(cmdPrint, startIndx + 3, IDENT + flagGroup + " Alarm low",
            strBuff, flagColor, true, true, false, true);
}

// Preparing threshold row for all DDM fields
string MlxlinkCablesCommander::getDDMThresholdRow(u_int16_t temp, u_int16_t volt,
        u_int16_t rxPower, u_int16_t txPower, u_int16_t txBias)
{
    string row = "";
    char strBuff[32];
    sprintf(strBuff, "%dC", (signed char) (temp >> 8));
    row = MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.4fV", ((double)volt) / 10000);
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.4fdBm", mw_to_dbm(((double)rxPower) / 10000));
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.4fdBm", mw_to_dbm(((double)txPower) / 10000));
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.4fmA", ((double)txBias) / 500);
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff));
    return row;
}

// Preparing DDM output by filling MlxlinkCmdPrint objects
void MlxlinkCablesCommander::prepareDDMOutput()
{
    MlxlinkCmdPrint cableDDMCmd = MlxlinkCmdPrint();
    setPrintTitle(cableDDMCmd,"Cable DDM Information", 6);

    char strBuff[32];
    sprintf(strBuff, "%dC", _cableDdm.temperature.val);
    setPrintVal(cableDDMCmd, 0, "Temperature", strBuff, ANSI_COLOR_RESET, true);

    sprintf(strBuff, "%.4fV", ((double)_cableDdm.voltage.val) / 10000);
    setPrintVal(cableDDMCmd, 1, "Voltage", strBuff, ANSI_COLOR_RESET, true);

    int i = 0;
    string title = "";
    string rxPower = "";
    string txPower = "";
    string txBias = "";
    for (i = 0; i < _cableDdm.channels; i++) {
        sprintf(strBuff, "Channel %d", i + 1);
        title += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.4fdBm",
                mw_to_dbm(((double)_cableDdm.rx_power[i].val) / 10000));
        rxPower += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.4fdBm",
                mw_to_dbm(((double)_cableDdm.tx_power[i].val) / 10000));
        txPower += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.4fmA",
                ((double)_cableDdm.tx_bias[i].val) / 500);
        txBias += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    }
    title = deleteLastComma(title);
    rxPower = deleteLastComma(rxPower);
    txPower = deleteLastComma(txPower);
    txBias = deleteLastComma(txBias);
    int skipTitle = (_cableDdm.channels == 1);
    if (!skipTitle) {
        setPrintVal(cableDDMCmd, 2, "Channels", title, ANSI_COLOR_RESET, true,
                true, true);
    }
    setPrintVal(cableDDMCmd, 3 - skipTitle, "RX Power", rxPower,
            ANSI_COLOR_RESET, true, true, true);
    setPrintVal(cableDDMCmd, 4 - skipTitle, "TX Power", txPower,
            ANSI_COLOR_RESET, true, true, true);
    setPrintVal(cableDDMCmd, 5 - skipTitle, "TX Bias", txBias,
            ANSI_COLOR_RESET, true, true, true);

    cableDDMCmd.toJsonFormat(_jsonRoot);
    _cableDDMOutput.push_back(cableDDMCmd);

    MlxlinkCmdPrint cableDDMFlags = MlxlinkCmdPrint();
    string flagStr = "Status";
    setPrintTitle(cableDDMFlags,"DDM Flags", 9);
    setPrintDDMFlagsSection(cableDDMFlags, cableDDMFlags.getCurrRow(),
            _cableDdm.temperature, "Temperature");
    setPrintDDMFlagsSection(cableDDMFlags, cableDDMFlags.getCurrRow(),
            _cableDdm.voltage, "Voltage");
    cableDDMFlags.toJsonFormat(_jsonRoot);
    _cableDDMOutput.push_back(cableDDMFlags);

    for (i = 0; i < _cableDdm.channels; i++) {
        MlxlinkCmdPrint channelFlags = MlxlinkCmdPrint();
        if (_cableDdm.channels == 1) {
            sprintf(strBuff, "Channel");
        } else {
            sprintf(strBuff, "Channel %d", i + 1);
        }
        setPrintTitle(channelFlags, string(strBuff) + " Flags", 13);
        setPrintDDMFlagsSection(channelFlags, channelFlags.getCurrRow(),
                _cableDdm.rx_power[i], "RX Power");
        setPrintDDMFlagsSection(channelFlags, channelFlags.getCurrRow(),
                _cableDdm.tx_power[i], "TX Power");
        setPrintDDMFlagsSection(channelFlags, channelFlags.getCurrRow(),
                _cableDdm.tx_bias[i], "TX Bias");
        channelFlags.toJsonFormat(_jsonRoot);
        _cableDDMOutput.push_back(channelFlags);
    }

    MlxlinkCmdPrint cableDDMThresholds= MlxlinkCmdPrint();
    setPrintTitle(cableDDMThresholds,"DDM Thresholds", 50);

    setPrintVal(cableDDMThresholds, cableDDMThresholds.getCurrRow(),
            "Thresholds",
            MlxlinkRecord::addSpaceForDDM(string("Temperature")) + "," +
            MlxlinkRecord::addSpaceForDDM(string("Voltage")) + "," +
            MlxlinkRecord::addSpaceForDDM(string("RX Power")) + "," +
            MlxlinkRecord::addSpaceForDDM(string("TX Power")) + "," +
            MlxlinkRecord::addSpaceForDDM(string("TX Bias")),
            ANSI_COLOR_RESET, true, true, true);

    string row = getDDMThresholdRow(_cableDdm.temperature.high_alarm,
                              _cableDdm.voltage.high_alarm,
                              _cableDdm.rx_power[0].high_alarm,
                              _cableDdm.tx_power[0].high_alarm,
                              _cableDdm.tx_bias[0].high_alarm);
    setPrintVal(cableDDMThresholds, cableDDMThresholds.getCurrRow(),
            "High alarm threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.high_warn,
                       _cableDdm.voltage.high_warn,
                       _cableDdm.rx_power[0].high_warn,
                       _cableDdm.tx_power[0].high_warn,
                       _cableDdm.tx_bias[0].high_warn);
    setPrintVal(cableDDMThresholds, cableDDMThresholds.getCurrRow(),
            "High warning threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.low_warn ,
                       _cableDdm.voltage.low_warn,
                       _cableDdm.rx_power[0].low_warn,
                       _cableDdm.tx_power[0].low_warn,
                       _cableDdm.tx_bias[0].low_warn);
    setPrintVal(cableDDMThresholds, cableDDMThresholds.getCurrRow(),
            "Low warn threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.low_alarm,
                       _cableDdm.voltage.low_alarm,
                       _cableDdm.rx_power[0].low_alarm,
                       _cableDdm.tx_power[0].low_alarm,
                       _cableDdm.tx_bias[0].low_alarm);
    setPrintVal(cableDDMThresholds, cableDDMThresholds.getCurrRow(),
            "Low alarm threshold", row, ANSI_COLOR_RESET, true, true, true);

    cableDDMThresholds.toJsonFormat(_jsonRoot);
    _cableDDMOutput.push_back(cableDDMThresholds);

}

// Query cable DDM info from cable EEPRM
vector<MlxlinkCmdPrint> MlxlinkCablesCommander::getCableDDM()
{
    readCableDDMInfo();
    prepareDDMOutput();
    return _cableDDMOutput;
}

// Preparing pages to be dumped
void MlxlinkCablesCommander::addPageToOutputVector(u_int8_t *pageBuffer, u_int32_t page,
        u_int32_t offset, u_int32_t length)
{
    MlxlinkCmdPrint pageDump = MlxlinkCmdPrint();
    char title[64];
    char LineOffset[32];
    char val[32];
    u_int32_t  bytesPerLine = 4;
    sprintf(title, "Page: 0x%x, Offset: %03d, Length: 0x%x", page, offset, length);
    setPrintTitle(pageDump, string(title), CABLE_PAGE_SIZE/bytesPerLine);

    u_int32_t row;
    for (row = 0; row < length/bytesPerLine; row++) {
        sprintf(LineOffset, "%03d",row * bytesPerLine + offset);
        sprintf(val, "%02x,%02x,%02x,%02x", pageBuffer[row*bytesPerLine],
                                            pageBuffer[row*bytesPerLine+1],
                                            pageBuffer[row*bytesPerLine+2],
                                            pageBuffer[row*bytesPerLine+3]);
        setPrintVal(pageDump, row, LineOffset, val, ANSI_COLOR_RESET, true,
                true, true);
    }
    pageDump.toJsonFormat(_jsonRoot);
    _pagesToDump.push_back(pageDump);
}

// Fetching supported pages from cable EEPROM
void MlxlinkCablesCommander::initValidPages()
{
    page_t p;
    p = (page_t){PAGE_0, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
    _validPages.push_back(p);
    bool qsfpCable = (_cableIdentifier == IDENTIFIER_QSFP28 ||
                _cableIdentifier == IDENTIFIER_QSFP_PLUS);
    bool cmisCable = (_cableIdentifier == IDENTIFIER_SFP_DD ||
            _cableIdentifier == IDENTIFIER_QSFP_DD);
    if(cmisCable || qsfpCable || _sfp51Paging) {
        p = (page_t){PAGE_0, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
        _validPages.push_back(p);
    }
    if (_sfp51Paging) {
        p = (page_t){PAGE_01, LOWER_PAGE_OFFSET, I2C_ADDR_HIGH};
        _validPages.push_back(p);
    }
    if (qsfpCable && !_passiveQsfp) {
        u_int8_t *page0H =  (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
        loadEEPRMPage(PAGE_0, UPPER_PAGE_OFFSET, page0H);
        u_int8_t optionsValue = 0;
        readFromPage(page0H, 195 - 0x80, &optionsValue);
        delete page0H;
        if (optionsValue & 0x40) { //check bit 6 for support page_01
            p = (page_t){PAGE_01, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
        if (optionsValue & 0x80) { //check bit 7 for support page_02
            p = (page_t){PAGE_02, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
        p = (page_t){PAGE_03, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
        _validPages.push_back(p);
        if (optionsValue & 0x01) { //check bit 0 for support page_20 and page_21
            p = (page_t){PAGE_20, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
            p = (page_t){PAGE_21, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
    }
    if (cmisCable) {
        // (QSFP-DD)
        // if 2:7=0, dump page 0x1
        //           dump page 0x2
        //           dump page 0x10
        //           dump page 0x11
        // (SFP-DD)
        // if 2:7=0, dump page 0x1
        u_int8_t extendedPages = 0;
        u_int8_t *page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
        loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);;
        readFromPage(page0L, EXTENDED_PAGES_1_2_10_11_ADDR, &extendedPages);
        delete page0L;
        if (!(extendedPages & EXTENDED_PAGES_1_2_10_11_MASK)) {
            p = (page_t){PAGE_01, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
            p = (page_t){PAGE_01, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
            if (_cableIdentifier == IDENTIFIER_QSFP_DD) {
                p = (page_t){PAGE_02, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = (page_t){PAGE_02, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = (page_t){PAGE_10, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = (page_t){PAGE_10, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = (page_t){PAGE_11, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = (page_t){PAGE_11, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);

                // if p 1, B155:6=1, dump page 0x4 (L&H)
                //                   dump page 0x12 (L&H)
                //         B142:5=1, dump page 0x13 (L&H)
                //                   dump page 0x14 (L&H)
                u_int8_t *page1H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
                loadEEPRMPage(PAGE_01, UPPER_PAGE_OFFSET, page1H);;
                u_int8_t extendedQsfpPages = 0;
                readFromPage(page1H,
                        (EXTENDED_PAGES_4_12_ADDR - UPPER_PAGE_OFFSET),
                        &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_4_12_MASK) {
                    p = (page_t){PAGE_04, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_04, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_12, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_12, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                extendedQsfpPages = 0;
                readFromPage(page1H,
                        (EXTENDED_PAGES_13_14_ADDR - UPPER_PAGE_OFFSET),
                        &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_13_14_MASK) {
                    p = (page_t){PAGE_13, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_13, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_14, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = (page_t){PAGE_14, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                delete page1H;
            }
        }
    }
}

// Query dump EEPROM pages
vector<MlxlinkCmdPrint> MlxlinkCablesCommander::getPagesToDump()
{
    initValidPages();
    for (u_int32_t i = 0; i< _validPages.size(); i++) {
        u_int8_t *pageP = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
        loadEEPRMPage(_validPages[i].page, _validPages[i].offset, pageP, _validPages[i].i2cAddress);;
        addPageToOutputVector(pageP, _validPages[i].page, _validPages[i].offset, CABLE_PAGE_SIZE);
        delete pageP;
    }
    return _pagesToDump;
}

// Write a vector of bytes to cable EEPROM
void MlxlinkCablesCommander::writeToEEPROM(u_int16_t page , u_int16_t offset,
        vector<u_int8_t> &bytesToWrite)
{
    // check the page, offset and data size validity
    checkParams(page, offset, bytesToWrite.size());

    u_int32_t numberOfZeroBytes = 0;
    // adding zero bytes to work with dword blocks
    for (; numberOfZeroBytes < bytesToWrite.size()%4; numberOfZeroBytes++) {
        bytesToWrite.push_back(0x0);
    }
    u_int32_t numberOfAllignedBytes = bytesToWrite.size();
    u_int8_t *data = (u_int8_t*) malloc(sizeof(u_int8_t) * bytesToWrite.size());
    memcpy(data, &bytesToWrite[0], sizeof(u_int8_t) * bytesToWrite.size());
    u_int32_t i2cAddress = I2C_ADDR_LOW;
    if (_sfp51Paging && page == PAGE_01) {
        i2cAddress = I2C_ADDR_HIGH;
    }
    writeMCIA(page, numberOfAllignedBytes, numberOfZeroBytes, offset, data, i2cAddress);
    delete data;
}
// Checking read command parameters and initializing the valid pages
void MlxlinkCablesCommander::checkParams(u_int16_t page , u_int16_t offset, u_int16_t length)
{
    if (offset > (EEPROM_PAGE_LENGTH+1)) {
        throw MlxRegException(
                "Invalid offset value %d. It must be within range [0-255].", offset);
    }
    if (length > (EEPROM_PAGE_LENGTH+1)) {
        throw MlxRegException(
                "Invalid length value %d. It must be within range [0-255].", length);
    }
    if ((length + offset) > (EEPROM_PAGE_LENGTH+1)) {
        throw MlxRegException(
                "The length of bytes exceeded the page size.", length);
    }
    initValidPages();
    bool lowerPageAccess = offset < CABLE_PAGE_SIZE;
    bool upperPageAccess = (offset > (CABLE_PAGE_SIZE - 1)) ||
                                    ((length + offset) > CABLE_PAGE_SIZE);
    bool lowerValid = false;
    bool upperValid = false;
    for (u_int32_t i = 0; i < _validPages.size(); i++) {
        if (_validPages[i].page == page) {
            if (lowerPageAccess) {
                if (_validPages[i].offset == LOWER_PAGE_OFFSET){
                    lowerValid = true;
                }
            }
            if (upperPageAccess) {
                if (_validPages[i].offset == UPPER_PAGE_OFFSET) {
                    upperValid = true;
                }
            }
            if (lowerPageAccess && upperPageAccess) {
                if (lowerValid && upperValid) {
                    break;
                }
            } else if (lowerValid || upperValid){
                break;
            }
        } else if (i == _validPages.size()-1) {
            throw MlxRegException("Invalid access to page 0x%x", page);
        }
    }
    if (lowerPageAccess && !lowerValid) {
        throw MlxRegException(
                "Invalid access to page 0x%x low", page);
    } else if (upperPageAccess && !upperValid) {
        throw MlxRegException(
                "Invalid access to page 0x%x high", page);
    }
}

// Reading specific offset\page from cable EEPRM
MlxlinkCmdPrint MlxlinkCablesCommander::readFromEEPRM(u_int16_t page , u_int16_t offset,
        u_int16_t length)
{
    checkParams(page, offset, length);

    u_int8_t *pageL = (u_int8_t*) malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    u_int8_t *pageH = NULL;
    u_int32_t i2cAddress = I2C_ADDR_LOW;
    // if SFP51 paging is supported, then we use i2c 0x51 to Access page 1
    if (_sfp51Paging && page == PAGE_01) {
        i2cAddress = I2C_ADDR_HIGH;
    }
    loadEEPRMPage(page, LOWER_PAGE_OFFSET, pageL, i2cAddress);
    if ((length + offset)  > CABLE_PAGE_SIZE ) {
        pageH = (u_int8_t*) malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
        loadEEPRMPage(page, UPPER_PAGE_OFFSET, pageH);
    }
    char label[32];
    char val[32];
    u_int8_t byteVal = 0;
    u_int32_t i;
    MlxlinkCmdPrint bytesOutput = MlxlinkCmdPrint();
    setPrintTitle(bytesOutput, "Cable Read Output", length + 1);

    u_int32_t currOffset = 0;
    for (i = 0; i < length ; ++i) {
        currOffset = offset + i;
        sprintf(label, "page[%d].Byte[%d]", page, currOffset);
        if (currOffset < CABLE_PAGE_SIZE) {
            readFromPage(pageL, currOffset, &byteVal);
            sprintf(val, "0x%02x", byteVal);
        } else {
            readFromPage(pageH, currOffset - UPPER_PAGE_OFFSET, &byteVal);
            sprintf(val, "0x%02x", byteVal);
        }
        setPrintVal(bytesOutput, bytesOutput.getCurrRow(), label, val,
                ANSI_COLOR_RESET, true, true, true);
    }
    bytesOutput.toJsonFormat(_jsonRoot);

    delete pageL;
    delete pageH;
    return bytesOutput;
}
