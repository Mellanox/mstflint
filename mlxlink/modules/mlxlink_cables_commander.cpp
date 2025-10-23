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

#include "mlxlink_cables_commander.h"

MlxlinkCablesCommander::MlxlinkCablesCommander(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _moduleNumber = 0;
    _slotIndex = 0;
    _sfp51Paging = false;
    _passiveQsfp = false;
    _localPort = 0;
    _numOfLanes = 0;

    _prbsRate = MODULE_PRBS_LANE_RATE_HDR;
    _prbsMode = PRBS31;
    _prbsInv = false;
    _prbsSwap = false;
    _swControlMode = false;
    _prbsLanes = 0;
    _txBiasMultiplier = 1;

    memset(&_cableDdm, 0, sizeof(cable_ddm_q_t));
    // PMCR control fields names
    // pair(UI name, PMCR field name)
    _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_TX_EQ] = make_pair("TX Equalization", "tx_equ_override");
    _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_EMPH] = make_pair("RX Emphasis", "rx_emp_override");
    _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_POST_EMPH] =
      make_pair("RX Post Emphasis", "rx_post_emp_override");
    _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_AMP] = make_pair("RX Amplitude", "rx_amp_override");
}

MlxlinkCablesCommander::~MlxlinkCablesCommander() {}

void MlxlinkCablesCommander::setSwControlMode()
{
    _swControlMode = true;
}

// Read EEPROM data from MCIA register
void MlxlinkCablesCommander::readMCIA(u_int32_t page,
                                      u_int32_t size,
                                      u_int32_t offset,
                                      u_int8_t* data,
                                      u_int32_t i2cAddress)
{
    sendPrmReg(ACCESS_REG_MCIA, GET,
               "module=%d,slot_index=%d,size=%d,page_number=%d,device_address=%d,i2c_device_address=%d", _moduleNumber,
               _slotIndex, size, page, offset, i2cAddress);

    u_int32_t i = 0;
    char fieldName[32];
    for (; i < size / 4; i++)
    {
        sprintf(fieldName, "dword[%d]", i);
        u_int32_t s = getFieldValue(std::string(fieldName));
        s = __be32_to_cpu(s);
        memcpy(data + (i * 4), &s, sizeof(u_int32_t));
    }
}

// Write EEPROM data to MCIA register
void MlxlinkCablesCommander::writeMCIA(u_int32_t page,
                                       u_int32_t size,
                                       u_int32_t numberOfZeroBytes,
                                       u_int32_t offset,
                                       u_int8_t* data,
                                       u_int32_t i2cAddress)
{
    u_int32_t dataSize = size - numberOfZeroBytes;
    if ((dataSize + offset - 1) > EEPROM_PAGE_LENGTH)
    {
        throw MlxRegException("Data exceeded the maximum page size (255 bytes), check the offset or data size");
    }

    u_int32_t i = 0;
    char fieldName[64];
    string dataCmd = "";
    u_int32_t dwordDataSize = (u_int32_t)ceil((double)size / sizeof(u_int32_t));
    u_int32_t* dwordData = (u_int32_t*)malloc(dwordDataSize);
    memset(dwordData, 0, dwordDataSize);
    memcpy(dwordData, data, size);
    for (; i < dwordDataSize; i++)
    {
        sprintf(fieldName, ",dword[%d]=%d", i, __cpu_to_be32(dwordData[i]));
        dataCmd += string(fieldName);
    }
    free(dwordData);

    sendPrmReg(ACCESS_REG_MCIA, SET,
               "module=%d,slot_index=%d,size=%d,page_number=%d,device_address=%d,i2c_device_address=%d%s",
               _moduleNumber, _slotIndex, size, page, offset, i2cAddress, dataCmd.c_str());
}

// Reading EEPROM data from MCIA register and loading it to readable pages
void MlxlinkCablesCommander::loadEEPRMPage(u_int32_t pageNum, u_int32_t offset, u_int8_t* data, u_int32_t i2cAddress)
{
    memset(data, 0, CABLE_PAGE_SIZE);
    u_int32_t pageOffset = 0;
    for (u_int8_t i = 0; i < (CABLE_PAGE_SIZE / EEPROM_MAX_BYTES); i++)
    {
        pageOffset = EEPROM_MAX_BYTES * i;
        readMCIA(pageNum, EEPROM_MAX_BYTES, offset + pageOffset, data + pageOffset, i2cAddress);
    }
}

// Reading specific addres from the page
bool MlxlinkCablesCommander::readFromPage(u_int8_t* pageBuffer, u_int32_t fieldOffset, void* data, u_int32_t size)
{
    if (pageBuffer)
    {
        memcpy((u_int8_t*)data, &pageBuffer[fieldOffset], sizeof(u_int8_t) * size);
        return true;
    }
    return false;
}

// Converting byte to u_int16_t
void MlxlinkCablesCommander::bytesToInt16(u_int16_t* bytes)
{
    u_int8_t bytesArr[2];
    memcpy(bytesArr, bytes, 2);
    *bytes = bytesArr[0] << 8 | bytesArr[1];
}

// Converting threshold fields from byte to u_int16_t
void MlxlinkCablesCommander::convertThreshold(ddm_threshold_t& field)
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
    for (i = 0; i < _cableDdm.channels; i++)
    {
        convertThreshold(_cableDdm.rx_power[i]);
        convertThreshold(_cableDdm.tx_power[i]);
        convertThreshold(_cableDdm.tx_bias[i]);
    }
}

// Reading the flag status accroding to channel number and the status mask
u_int16_t MlxlinkCablesCommander::getStatusBit(u_int32_t channel, u_int16_t val, u_int32_t statusMask)
{
    // For channels 2 and 4, we need the lower nibble
    statusMask = channel % 2 ? statusMask : statusMask >> 4;
    return (val & statusMask) >> ((u_int32_t)log2(statusMask));
}

void MlxlinkCablesCommander::getDdmValuesFromPddr()
{
    if (!_swControlMode)
    {
        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_INFO_PAGE);

        _cableDdm.channels = _numOfLanes;
        _cableDdm.temperature.val = getFieldValue("temperature") / 256;
        _cableDdm.voltage.val = getFieldValue("voltage") / MILLIVOLT_UNIT;
        float txMultiplier = 1;
        try
        {
            _txBiasMultiplier = pow(2, getFieldValue("tx_bias_scaling_factor"));
        }
        catch (const std::exception& e)
        {
            // If the field does not exist, set the multiplier to 1
            // _txBiasMultiplier = 1;
        }

        string laneStr = "";
        for (int lane = 0; lane < _cableDdm.channels; lane++)
        {
            laneStr = to_string(_moduleLanesMapping[lane]);
            _cableDdm.rx_power[lane].val = getPower(getFieldValue("rx_power_lane" + laneStr));
            _cableDdm.tx_power[lane].val = getPower(getFieldValue("tx_power_lane" + laneStr));
            _cableDdm.tx_bias[lane].val = getFieldValue("tx_bias_lane" + laneStr) * _txBiasMultiplier;
        }
    }
}

void MlxlinkCablesCommander::getQsfpDdThresholds(u_int8_t* page2H)
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

void MlxlinkCablesCommander::getCmisModuleFlags(u_int32_t moduleOffset, u_int8_t* page0L)
{
    u_int32_t tempVal = 0;
    readFromPage(page0L, moduleOffset, &tempVal);
    _cableDdm.temperature.high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_TEMP_HWARN_STATUS);
    _cableDdm.temperature.low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_TEMP_LWARN_STATUS);
    _cableDdm.temperature.high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_TEMP_HALARM_STATUS);
    _cableDdm.temperature.low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_TEMP_LALARM_STATUS);
    tempVal = 0;
    readFromPage(page0L, moduleOffset, &tempVal);
    _cableDdm.voltage.high_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_VCC_HWARN_STATUS);
    _cableDdm.voltage.low_warn_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_VCC_LWARN_STATUS);
    _cableDdm.voltage.high_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_VCC_HALARM_STATUS);
    _cableDdm.voltage.low_alarm_flag = getStatusBit(CMIS_MODULE_CHANNEL, tempVal, CMIS_VCC_LALARM_STATUS);
}

void MlxlinkCablesCommander::getQsfpDddLanesFlags(u_int8_t* page11H)
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

    for (int i = 0; i < _cableDdm.channels; i++)
    {
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
    getDdmValuesFromPddr();

    // Read module flags
    u_int8_t* page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
    getCmisModuleFlags(QSFP_DD_MODULE_INFO_OFFSET, page0L);

    // Read lanes flags
    u_int8_t* page11H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_11, UPPER_PAGE_OFFSET, page11H);
    getQsfpDddLanesFlags(page11H);

    // Get cable thresholds
    u_int8_t* page2H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_02, UPPER_PAGE_OFFSET, page2H);
    getQsfpDdThresholds(page2H);

    free(page0L);
    free(page11H);
    free(page2H);
}

void MlxlinkCablesCommander::getSfpDdThresholds(u_int8_t* page0H)
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

void MlxlinkCablesCommander::getSfpDddLanesFlags(u_int8_t* page0L)
{
    u_int32_t txPowerInturrept = 0;
    u_int32_t txBiasInturrept = 0;
    u_int32_t rxPowerInturrept = 0;
    readFromPage(page0L, SFP_DD_TX_POWER_INT_OFFSET, &txPowerInturrept);
    readFromPage(page0L, SFP_DD_TX_BIAS_INT_OFFSET, &txBiasInturrept);
    readFromPage(page0L, SFP_DD_RX_POWER_INT_OFFSET, &rxPowerInturrept);

    for (int i = 0; i < _cableDdm.channels; i++)
    {
        _cableDdm.rx_power[i].low_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, rxPowerInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.rx_power[i].high_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, rxPowerInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.rx_power[i].low_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, rxPowerInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.rx_power[i].high_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, rxPowerInturrept >> SFP_DD_HALARM_STATUS, i);

        _cableDdm.tx_power[i].low_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txPowerInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.tx_power[i].high_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txPowerInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.tx_power[i].low_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txPowerInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.tx_power[i].high_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txPowerInturrept >> SFP_DD_HALARM_STATUS, i);

        _cableDdm.tx_bias[i].low_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txBiasInturrept >> SFP_DD_LWARN_STATUS, i);
        _cableDdm.tx_bias[i].high_warn_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txBiasInturrept >> SFP_DD_HWARN_STATUS, i);
        _cableDdm.tx_bias[i].low_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txBiasInturrept >> SFP_DD_LALARM_STATUS, i);
        _cableDdm.tx_bias[i].high_alarm_flag =
          getStatusBit(CMIS_MODULE_CHANNEL, txBiasInturrept >> SFP_DD_HALARM_STATUS, i);
    }
}

void MlxlinkCablesCommander::prepareSfpddDdmInfo()
{
    // Read DDM fields from PDDR
    getDdmValuesFromPddr();

    // Read module flags
    u_int8_t* page0L = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
    getCmisModuleFlags(QSFP_DD_MODULE_INFO_OFFSET, page0L);

    // Read lanes flags
    getSfpDddLanesFlags(page0L);

    // Get cable thresholds
    u_int8_t* page0H = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_0, UPPER_PAGE_OFFSET, page0H);
    getSfpDdThresholds(page0H);

    free(page0H);
    free(page0L);
}

// Preparing QSFP DDM information
void MlxlinkCablesCommander::prepareQSFPDdmInfo()
{
    u_int32_t tempVal = 0;
    u_int8_t* page0L = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
    if (page0L != NULL)
    {
        loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);

        readFromPage(page0L, QSFP_TEMP_AW_OFFSET, &tempVal);
        _cableDdm.temperature.high_warn_flag = (tempVal & QSFP_TEMP_HWARN_STATUS);
        _cableDdm.temperature.low_warn_flag = (tempVal & QSFP_TEMP_LWARN_STATUS);
        _cableDdm.temperature.high_alarm_flag = (tempVal & QSFP_TEMP_HALARM_STATUS);
        _cableDdm.temperature.low_alarm_flag = (tempVal & QSFP_TEMP_LALARM_STATUS);

        tempVal = 0;
        readFromPage(page0L, QSFP_VCC_AW_OFFSET, &tempVal);
        _cableDdm.voltage.high_warn_flag = (tempVal & QSFP_VCC_HWARN_STATUS);
        _cableDdm.voltage.low_warn_flag = (tempVal & QSFP_VCC_LWARN_STATUS);
        _cableDdm.voltage.high_alarm_flag = (tempVal & QSFP_VCC_HALARM_STATUS);
        _cableDdm.voltage.low_alarm_flag = (tempVal & QSFP_VCC_LALARM_STATUS);

        getDdmValuesFromPddr();

        u_int8_t nextTwoChannels = 0;
        for (u_int32_t i = 1; i <= QSFP_CHANNELS; i++)
        {
            nextTwoChannels = (i > QSFP_CHANNELS / 2) ? 1 : 0;
            tempVal = 0;
            readFromPage(page0L, QSFP_RX_PWR_12_AW_OFFSET + nextTwoChannels, &tempVal);

            _cableDdm.rx_power[i - 1].low_warn_flag = getStatusBit(i, tempVal, QSFP_RX_PWR_1_LWARN);
            _cableDdm.rx_power[i - 1].high_warn_flag = getStatusBit(i, tempVal, QSFP_RX_PWR_1_HWARN);
            _cableDdm.rx_power[i - 1].low_alarm_flag = getStatusBit(i, tempVal, QSFP_RX_PWR_1_LALARM);
            _cableDdm.rx_power[i - 1].high_alarm_flag = getStatusBit(i, tempVal, QSFP_RX_PWR_1_HALARM);

            tempVal = 0;
            readFromPage(page0L, QSFP_TX_PWR_12_AW_OFFSET + nextTwoChannels, &tempVal);
            _cableDdm.tx_power[i - 1].low_warn_flag = getStatusBit(i, tempVal, QSFP_TX_PWR_1_LWARN);
            _cableDdm.tx_power[i - 1].high_warn_flag = getStatusBit(i, tempVal, QSFP_TX_PWR_1_HWARN);
            _cableDdm.tx_power[i - 1].low_alarm_flag = getStatusBit(i, tempVal, QSFP_TX_PWR_1_LALARM);
            _cableDdm.tx_power[i - 1].high_alarm_flag = getStatusBit(i, tempVal, QSFP_TX_PWR_1_HALARM);

            tempVal = 0;
            readFromPage(page0L, QSFP_TX_BIAS_12_AW_OFFSET + nextTwoChannels, &tempVal);
            _cableDdm.tx_bias[i - 1].low_warn_flag = getStatusBit(i, tempVal, QSFP_TX_BIAS_1_LWARN);
            _cableDdm.tx_bias[i - 1].high_warn_flag = getStatusBit(i, tempVal, QSFP_TX_BIAS_1_HWARN);
            _cableDdm.tx_bias[i - 1].low_alarm_flag = getStatusBit(i, tempVal, QSFP_TX_BIAS_1_LALARM);
            _cableDdm.tx_bias[i - 1].high_alarm_flag = getStatusBit(i, tempVal, QSFP_TX_BIAS_1_HALARM);
        }

        free(page0L);
    }
}

// Preparing SFP DDM information
void MlxlinkCablesCommander::prepareSFPDdmInfo()
{
    u_int32_t tempVal = 0;
    u_int8_t* sfp51Page = (u_int8_t*)malloc(sizeof(u_int8_t) * CABLE_PAGE_SIZE);
    loadEEPRMPage(PAGE_A2, LOWER_PAGE_OFFSET, sfp51Page, I2C_ADDR_HIGH);

    getDdmValuesFromPddr();

    readFromPage(sfp51Page, SFP51_ALRM_FLG, &tempVal, 2);
    _cableDdm.tx_power[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TX_PWR_LWARN_FLG);
    _cableDdm.tx_power[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TX_PWR_HWARN_FLG);
    _cableDdm.tx_bias[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_BIAS_LWARN_FLG);
    _cableDdm.tx_bias[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_BIAS_HWARN_FLG);
    _cableDdm.voltage.low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_VCC_LWARN_FLG);
    _cableDdm.voltage.high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_VCC_HWARN_FLG);
    _cableDdm.temperature.low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TEMP_LWARN_FLG);
    _cableDdm.temperature.high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TEMP_HWARN_FLG);
    _cableDdm.rx_power[0].low_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_RX_PWR_LWARN_FLG);
    _cableDdm.rx_power[0].high_warn_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_RX_PWR_HWARN_FLG);

    tempVal = 0;
    readFromPage(sfp51Page, SFP51_WARN_FLG, &tempVal, 2);
    _cableDdm.tx_power[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TX_PWR_LALRM_FLG);
    _cableDdm.tx_power[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TX_PWR_HALRM_FLG);
    _cableDdm.tx_bias[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_BIAS_LALRM_FLG);
    _cableDdm.tx_bias[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_BIAS_HALRM_FLG);
    _cableDdm.voltage.low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_VCC_LALRM_FLG);
    _cableDdm.voltage.high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_VCC_HALRM_FLG);
    _cableDdm.temperature.low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TEMP_LALRM_FLG);
    _cableDdm.temperature.high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_TEMP_HALRM_FLG);
    _cableDdm.rx_power[0].low_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_RX_PWR_LALRM_FLG);
    _cableDdm.rx_power[0].high_alarm_flag = getStatusBit(SFP_CHANNELS, tempVal, SFP51_RX_PWR_HALRM_FLG);

    free(sfp51Page);
}

// Preparing thresholds information
void MlxlinkCablesCommander::prepareThresholdInfo(u_int8_t* thresholdPage)
{
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TEMP_HALRM : QSFP_TEMP_HALRM, &_cableDdm.temperature.high_alarm,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TEMP_LALRM : QSFP_TEMP_LALRM, &_cableDdm.temperature.low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TEMP_HWARN : QSFP_TEMP_HWARN, &_cableDdm.temperature.high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TEMP_LWARN : QSFP_TEMP_LWARN, &_cableDdm.temperature.low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging ? SFP51_VCC_HALRM : QSFP_VCC_HALRM, &_cableDdm.voltage.high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_VCC_LALRM : QSFP_VCC_LALRM, &_cableDdm.voltage.low_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_VCC_HWARN : QSFP_VCC_HWARN, &_cableDdm.voltage.high_warn, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_VCC_LWARN : QSFP_VCC_LWARN, &_cableDdm.voltage.low_warn, 2);

    readFromPage(thresholdPage, _sfp51Paging ? SFP51_RX_PWR_HALRM : QSFP_RX_PWR_HALRM,
                 &_cableDdm.rx_power[0].high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_RX_PWR_LALRM : QSFP_RX_PWR_LALRM, &_cableDdm.rx_power[0].low_alarm,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_RX_PWR_HWARN : QSFP_RX_PWR_HWARN, &_cableDdm.rx_power[0].high_warn,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_RX_PWR_LWARN : QSFP_RX_PWR_LWARN, &_cableDdm.rx_power[0].low_warn,
                 2);

    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TX_PWR_HALRM : QSFP_TX_PWR_HALRM,
                 &_cableDdm.tx_power[0].high_alarm, 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TX_PWR_LALRM : QSFP_TX_PWR_LALRM, &_cableDdm.tx_power[0].low_alarm,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TX_PWR_HWARN : QSFP_TX_PWR_HWARN, &_cableDdm.tx_power[0].high_warn,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_TX_PWR_LWARN : QSFP_TX_PWR_LWARN, &_cableDdm.tx_power[0].low_warn,
                 2);

    readFromPage(thresholdPage, _sfp51Paging ? SFP51_BIAS_HALRM : QSFP_TX_BIAS_HALRM, &_cableDdm.tx_bias[0].high_alarm,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_BIAS_LALRM : QSFP_TX_BIAS_LALRM, &_cableDdm.tx_bias[0].low_alarm,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_BIAS_HWARN : QSFP_TX_BIAS_HWARN, &_cableDdm.tx_bias[0].high_warn,
                 2);
    readFromPage(thresholdPage, _sfp51Paging ? SFP51_BIAS_LWARN : QSFP_TX_BIAS_LWARN, &_cableDdm.tx_bias[0].low_warn,
                 2);
}

// Reading cable DDM information
void MlxlinkCablesCommander::readCableDDMInfo()
{
    u_int8_t* thresholdPage = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));

    switch (_cableIdentifier)
    {
        case IDENTIFIER_QSFP28:
        case IDENTIFIER_QSFP_PLUS:
        case IDENTIFIER_QSFP_SPLIT_CABLE:
            prepareQSFPDdmInfo();
            loadEEPRMPage(PAGE_03, UPPER_PAGE_OFFSET, thresholdPage);
            prepareThresholdInfo(thresholdPage);
            break;
        case IDENTIFIER_SFP:
        case IDENTIFIER_QSA:
            prepareSFPDdmInfo();
            loadEEPRMPage(PAGE_A2, LOWER_PAGE_OFFSET, thresholdPage, I2C_ADDR_HIGH);
            prepareThresholdInfo(thresholdPage);
            break;
        case IDENTIFIER_SFP_DD:
            prepareSfpddDdmInfo();
            break;
        case IDENTIFIER_QSFP_DD:
        case IDENTIFIER_OSFP:
        case IDENTIFIER_DSFP:
        case IDENTIFIER_QSFP_CMIS:
            prepareQsfpddDdmInfo();
            break;
        default:
            free(thresholdPage);
            throw MlxRegException("Cable does not support DDM");
    }

    fixThresholdBytes();

    free(thresholdPage);
}

// Preparing and formating DDM flags section
void MlxlinkCablesCommander::setPrintDDMFlagsSection(MlxlinkCmdPrint& cmdPrint,
                                                     const ddm_threshold_t& flags,
                                                     const string& flagGroup)
{
    char strBuff[32];
    string flagColor;
    sprintf(strBuff, "%0d", flags.high_alarm_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_ALARM);
    setPrintVal(cmdPrint, IDENT + flagGroup + " Alarm high", strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d", flags.high_warn_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_WARN);
    setPrintVal(cmdPrint, IDENT + flagGroup + " Warning high", strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d", flags.low_warn_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_WARN);
    setPrintVal(cmdPrint, IDENT + flagGroup + " Warning low", strBuff, flagColor, true, true, false, true);
    sprintf(strBuff, "%0d\n", flags.low_alarm_flag);
    flagColor = MlxlinkRecord::ddmFlagValue2Color(atoi(strBuff), DDM_FLAG_ALARM);
    setPrintVal(cmdPrint, IDENT + flagGroup + " Alarm low", strBuff, flagColor, true, true, false, true);
}

// Preparing threshold row for all DDM fields
string MlxlinkCablesCommander::getDDMThresholdRow(u_int16_t temp,
                                                  u_int16_t volt,
                                                  u_int16_t rxPower,
                                                  u_int16_t txPower,
                                                  u_int16_t txBias)
{
    string row = "";
    char strBuff[32];
    sprintf(strBuff, "%dC", (signed char)(temp >> 8));
    row = MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.3fV", ((double)volt) / 10000);
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.3fdBm", mw_to_dbm(((double)rxPower) / 10000));
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.3fdBm", mw_to_dbm(((double)txPower) / 10000));
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    sprintf(strBuff, "%.3fmA", ((double)txBias) / 500);
    row += MlxlinkRecord::addSpaceForDDM(string(strBuff));
    return row;
}

// Preparing DDM output by filling MlxlinkCmdPrint objects
void MlxlinkCablesCommander::prepareDDMOutput()
{
    MlxlinkCmdPrint cableDDMCmd = MlxlinkCmdPrint();
    setPrintTitle(cableDDMCmd, "Cable DDM Information", 6);

    char strBuff[32];
    sprintf(strBuff, "%dC", (int)_cableDdm.temperature.val);
    setPrintVal(cableDDMCmd, "Temperature", strBuff, ANSI_COLOR_RESET, true);

    sprintf(strBuff, "%.4fV", ((double)_cableDdm.voltage.val) / VOLT_UNIT);
    setPrintVal(cableDDMCmd, "Voltage", strBuff, ANSI_COLOR_RESET, true);

    int i = 0;
    string title = "";
    string rxPower = "";
    string txPower = "";
    string txBias = "";
    for (i = 0; i < _cableDdm.channels; i++)
    {
        sprintf(strBuff, "Channel %d", i + 1);
        title += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.3fdBm", (double)_cableDdm.rx_power[i].val);
        rxPower += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.3fdBm", (double)_cableDdm.tx_power[i].val);
        txPower += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
        sprintf(strBuff, "%.3fmA", ((double)_cableDdm.tx_bias[i].val) / 500);
        txBias += MlxlinkRecord::addSpaceForDDM(string(strBuff)) + ",";
    }
    title = deleteLastChar(title);
    rxPower = deleteLastChar(rxPower);
    txPower = deleteLastChar(txPower);
    txBias = deleteLastChar(txBias);
    int skipTitle = (_cableDdm.channels == 1);
    if (!skipTitle)
    {
        setPrintVal(cableDDMCmd, "Channels", title, ANSI_COLOR_RESET, true, _cableDdm.channels > 0, true);
    }
    setPrintVal(cableDDMCmd, "RX Power", rxPower, ANSI_COLOR_RESET, true, _cableDdm.channels > 0, true);
    setPrintVal(cableDDMCmd, "TX Power", txPower, ANSI_COLOR_RESET, true, _cableDdm.channels > 0, true);
    setPrintVal(cableDDMCmd, "TX Bias", txBias, ANSI_COLOR_RESET, true, _cableDdm.channels > 0, true);

    cableDDMCmd.toJsonFormat(_jsonRoot);
    _cableDDMOutput.push_back(cableDDMCmd);

    MlxlinkCmdPrint cableDDMFlags = MlxlinkCmdPrint();
    string flagStr = "Status";
    setPrintTitle(cableDDMFlags, "DDM Flags", 9);
    setPrintDDMFlagsSection(cableDDMFlags, _cableDdm.temperature, "Temperature");
    setPrintDDMFlagsSection(cableDDMFlags, _cableDdm.voltage, "Voltage");
    cableDDMFlags.toJsonFormat(_jsonRoot);
    _cableDDMOutput.push_back(cableDDMFlags);

    for (i = 0; i < _cableDdm.channels; i++)
    {
        MlxlinkCmdPrint channelFlags = MlxlinkCmdPrint();
        if (_cableDdm.channels == 1)
        {
            sprintf(strBuff, "Channel");
        }
        else
        {
            sprintf(strBuff, "Channel %d", i + 1);
        }
        setPrintTitle(channelFlags, string(strBuff) + " Flags", 13);
        setPrintDDMFlagsSection(channelFlags, _cableDdm.rx_power[i], "RX Power");
        setPrintDDMFlagsSection(channelFlags, _cableDdm.tx_power[i], "TX Power");
        setPrintDDMFlagsSection(channelFlags, _cableDdm.tx_bias[i], "TX Bias");
        channelFlags.toJsonFormat(_jsonRoot);
        _cableDDMOutput.push_back(channelFlags);
    }

    MlxlinkCmdPrint cableDDMThresholds = MlxlinkCmdPrint();
    setPrintTitle(cableDDMThresholds, "DDM Thresholds", 50);

    setPrintVal(
      cableDDMThresholds, "Thresholds",
      MlxlinkRecord::addSpaceForDDM(string("Temperature")) + "," + MlxlinkRecord::addSpaceForDDM(string("Voltage")) +
        "," + MlxlinkRecord::addSpaceForDDM(string("RX Power")) + "," +
        MlxlinkRecord::addSpaceForDDM(string("TX Power")) + "," + MlxlinkRecord::addSpaceForDDM(string("TX Bias")),
      ANSI_COLOR_RESET, true, true, true);

    string row = getDDMThresholdRow(_cableDdm.temperature.high_alarm,
                                    _cableDdm.voltage.high_alarm,
                                    _cableDdm.rx_power[0].high_alarm,
                                    _cableDdm.tx_power[0].high_alarm,
                                    _cableDdm.tx_bias[0].high_alarm * _txBiasMultiplier);
    setPrintVal(cableDDMThresholds, "High alarm threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.high_warn,
                             _cableDdm.voltage.high_warn,
                             _cableDdm.rx_power[0].high_warn,
                             _cableDdm.tx_power[0].high_warn,
                             _cableDdm.tx_bias[0].high_warn * _txBiasMultiplier);
    setPrintVal(cableDDMThresholds, "High warning threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.low_warn,
                             _cableDdm.voltage.low_warn,
                             _cableDdm.rx_power[0].low_warn,
                             _cableDdm.tx_power[0].low_warn,
                             _cableDdm.tx_bias[0].low_warn * _txBiasMultiplier);
    setPrintVal(cableDDMThresholds, "Low warning threshold", row, ANSI_COLOR_RESET, true, true, true);

    row = getDDMThresholdRow(_cableDdm.temperature.low_alarm,
                             _cableDdm.voltage.low_alarm,
                             _cableDdm.rx_power[0].low_alarm,
                             _cableDdm.tx_power[0].low_alarm,
                             _cableDdm.tx_bias[0].low_alarm * _txBiasMultiplier);
    setPrintVal(cableDDMThresholds, "Low alarm threshold", row, ANSI_COLOR_RESET, true, true, true);

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
void MlxlinkCablesCommander::addPageToOutputVector(u_int8_t* pageBuffer,
                                                   u_int32_t page,
                                                   u_int32_t offset,
                                                   u_int32_t length)
{
    MlxlinkCmdPrint pageDump = MlxlinkCmdPrint();
    char title[64];
    char LineOffset[32];
    char val[32];
    u_int32_t bytesPerLine = 4;
    sprintf(title, "Page: 0x%x, Offset: %03d, Length: 0x%x", page, offset, length);
    setPrintTitle(pageDump, string(title), CABLE_PAGE_SIZE / bytesPerLine);

    u_int32_t row;
    for (row = 0; row < length / bytesPerLine; row++)
    {
        sprintf(LineOffset, "%03d", row * bytesPerLine + offset);
        sprintf(val, "%02x,%02x,%02x,%02x", pageBuffer[row * bytesPerLine], pageBuffer[row * bytesPerLine + 1],
                pageBuffer[row * bytesPerLine + 2], pageBuffer[row * bytesPerLine + 3]);
        setPrintVal(pageDump, LineOffset, val, ANSI_COLOR_RESET, true, true, true);
    }
    pageDump.toJsonFormat(_jsonRoot);
    _pagesToDump.push_back(pageDump);
}

// Fetching supported pages from cable EEPROM
void MlxlinkCablesCommander::initValidPages()
{
    page_t p = page_t{PAGE_0, LOWER_PAGE_OFFSET, I2C_ADDR_LOW};
    _validPages.push_back(p);
    bool qsfpCable = (_cableIdentifier == IDENTIFIER_QSFP28 || _cableIdentifier == IDENTIFIER_QSFP_PLUS);
    bool cmisCable = (_cableIdentifier == IDENTIFIER_SFP_DD || _cableIdentifier == IDENTIFIER_QSFP_DD ||
                      _cableIdentifier == IDENTIFIER_OSFP || _cableIdentifier == IDENTIFIER_DSFP ||
                      _cableIdentifier == IDENTIFIER_QSFP_CMIS);
    if (cmisCable || qsfpCable || _sfp51Paging)
    {
        p = page_t{PAGE_0, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
        _validPages.push_back(p);
    }
    if (_sfp51Paging)
    {
        p = page_t{PAGE_A2, LOWER_PAGE_OFFSET, I2C_ADDR_HIGH};
        _validPages.push_back(p);
    }
    if (qsfpCable && !_passiveQsfp)
    {
        u_int8_t* page0H = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
        loadEEPRMPage(PAGE_0, UPPER_PAGE_OFFSET, page0H);
        u_int8_t optionsValue = 0;
        readFromPage(page0H, 195 - 0x80, &optionsValue);
        free(page0H);
        if (optionsValue & 0x40)
        { // check bit 6 for support page_01
            p = page_t{PAGE_01, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
        if (optionsValue & 0x80)
        { // check bit 7 for support page_02
            p = page_t{PAGE_02, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
        p = page_t{PAGE_03, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
        _validPages.push_back(p);
        if (optionsValue & 0x01)
        { // check bit 0 for support page_20 and page_21
            p = page_t{PAGE_20, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
            p = page_t{PAGE_21, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
        }
    }
    if (cmisCable)
    {
        // (QSFP-DD)
        // if 2:7=0, dump page 0x1
        //           dump page 0x2
        //           dump page 0x10
        //           dump page 0x11
        // (SFP-DD)
        // if 2:7=0, dump page 0x1
        u_int8_t extendedPages = 0;
        u_int8_t* page0L = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
        loadEEPRMPage(PAGE_0, LOWER_PAGE_OFFSET, page0L);
        ;
        readFromPage(page0L, EXTENDED_PAGES_1_2_10_11_ADDR, &extendedPages);
        free(page0L);
        /*
        if P 0x0L, B2:7=0, dump:
            01h,
            02h,
            10h,
            11h
        */
        if (!(extendedPages & EXTENDED_PAGES_1_2_10_11_MASK))
        {
            p = page_t{PAGE_01, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
            _validPages.push_back(p);
            if (_cableIdentifier != IDENTIFIER_SFP_DD)
            {
                p = page_t{PAGE_02, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = page_t{PAGE_10, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);
                p = page_t{PAGE_11, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                _validPages.push_back(p);

                u_int8_t* page1H = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
                loadEEPRMPage(PAGE_01, UPPER_PAGE_OFFSET, page1H);
                ;
                /*
                if P 0x1H, B142:2=1 dump:
                    03h
                if P 0x1H, B142:3=1 dump:
                    05h
                if P 0x1H, B142:5=1 dump:
                    13h,
                    14h
                if P 0x1H, B142:6=1 dump:
                    20h-2Dh,
                    2Fh
                if P 0x1H, B142:7=1 dump:
                    16h,
                    17h
                */
                u_int8_t extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_03_05_13_14_16_17_20_UPTO_2D_2F_ADDR - UPPER_PAGE_OFFSET),
                             &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_03_MASK)
                {
                    p = page_t{PAGE_03, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                if (extendedQsfpPages & EXTENDED_PAGES_05_MASK)
                {
                    p = page_t{PAGE_05, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                if (extendedQsfpPages & EXTENDED_PAGES_13_14_MASK)
                {
                    p = page_t{PAGE_13, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = page_t{PAGE_14, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                if (extendedQsfpPages & EXTENDED_PAGES_16_17_MASK)
                {
                    p = page_t{PAGE_16, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = page_t{PAGE_17, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }
                if (extendedQsfpPages & EXTENDED_PAGES_20_UPTO_2D_2F_MASK)
                {
                    for (u_int32_t page = PAGE_20; page <= PAGE_2D; page++)
                    {
                        p = page_t{page, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                        _validPages.push_back(p);
                    }
                    p = page_t{PAGE_2F, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }

                /*
                if P 0x1H, B145:3=1 dump:
                    15h
                */
                extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_15_ADDR - UPPER_PAGE_OFFSET), &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_15_MASK)
                {
                    p = page_t{PAGE_15, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }

                /*
                if P 0x1H, B155:6=1 dump:
                    04h,
                    12h
                */
                extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_4_12_ADDR - UPPER_PAGE_OFFSET), &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_4_12_MASK)
                {
                    p = page_t{PAGE_04, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                    p = page_t{PAGE_12, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }

                /*
                if P 0x1H, B162:6=1 dump:
                    19h,
                */
                extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_19_ADDR - UPPER_PAGE_OFFSET), &extendedQsfpPages);
                if (extendedQsfpPages & EXTENDED_PAGES_19_MASK)
                {
                    p = page_t{PAGE_19, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }

                /*
                if P 0x1H, B163:0-4=1 dump:
                    A0h
                elif P 0x1H, B163:0-4=2 dump:
                    A0h-A1h
                elif P 0x1H, B163:0-4=3 dump:
                    A0h-A2h
                elif P 0x1H, B163:0-4=4 dump:
                    A0h-A3h
                elif P 0x1H, B163:0-4=5 dump:
                    A0h-A7h
                elif P 0x1H, B163:0-4=6 dump:
                    A0h-Abh
                elif P 0x1H, B163:0-4=7 dump:
                    A0h-Afh
                */
                extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_A0_UPTO_AF_ADDR - UPPER_PAGE_OFFSET), &extendedQsfpPages);
                extendedQsfpPages = extendedQsfpPages & EXTENDED_PAGES_A0_UPTO_AF_MASK;
                if (extendedQsfpPages > 0 && extendedQsfpPages <= 7)
                {
                    u_int32_t end_page = 0;
                    if (extendedQsfpPages == 1)
                        end_page = PAGE_A0;
                    if (extendedQsfpPages == 2)
                        end_page = PAGE_A1;
                    if (extendedQsfpPages == 3)
                        end_page = PAGE_A2;
                    if (extendedQsfpPages == 4)
                        end_page = PAGE_A3;
                    if (extendedQsfpPages == 5)
                        end_page = PAGE_A7;
                    if (extendedQsfpPages == 6)
                        end_page = PAGE_AB;
                    if (extendedQsfpPages == 7)
                        end_page = PAGE_AF;
                    for (u_int32_t page = PAGE_A0; page <= end_page; page++)
                    {
                        p = page_t{page, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                        _validPages.push_back(p);
                    }
                }
                /*
                if P 0x1H, B163:6-7=1 dump:
                    9Fh
                if P 0x1H, B163:6-7=2 dump:
                    9Fh
                */
                extendedQsfpPages = 0;
                readFromPage(page1H, (EXTENDED_PAGES_9F_ADDR - UPPER_PAGE_OFFSET), &extendedQsfpPages);
                extendedQsfpPages = extendedQsfpPages & EXTENDED_PAGES_9F_MASK;
                extendedQsfpPages = extendedQsfpPages >> 6;
                if (extendedQsfpPages > 0 && extendedQsfpPages < 3)
                {
                    p = page_t{PAGE_9F, UPPER_PAGE_OFFSET, I2C_ADDR_LOW};
                    _validPages.push_back(p);
                }

                free(page1H);
            }
        }
    }
    std::sort(_validPages.begin(), _validPages.end(), [](const page_t& a, const page_t& b) { return a.page < b.page; });
}

// Query dump EEPROM pages
vector<MlxlinkCmdPrint> MlxlinkCablesCommander::getPagesToDump()
{
    initValidPages();
    for (u_int32_t i = 0; i < _validPages.size(); i++)
    {
        u_int8_t* pageP = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
        if (pageP != NULL)
        {
            loadEEPRMPage(_validPages[i].page, _validPages[i].offset, pageP, _validPages[i].i2cAddress);
            ;
            addPageToOutputVector(pageP, _validPages[i].page, _validPages[i].offset, CABLE_PAGE_SIZE);
            free(pageP);
        }
    }
    return _pagesToDump;
}

// Write a vector of bytes to cable EEPROM
void MlxlinkCablesCommander::writeToEEPROM(u_int16_t page, u_int16_t offset, vector<u_int8_t>& bytesToWrite)
{
    // check the page, offset and data size validity
    checkParams(offset, bytesToWrite.size());

    u_int32_t numberOfZeroBytes = 0;
    // adding zero bytes to work with dword blocks
    for (; numberOfZeroBytes < bytesToWrite.size() % 4; numberOfZeroBytes++)
    {
        bytesToWrite.push_back(0x0);
    }
    u_int32_t numberOfAllignedBytes = bytesToWrite.size();
    u_int8_t* data = (u_int8_t*)malloc(sizeof(u_int8_t) * bytesToWrite.size());
    memcpy(data, &bytesToWrite[0], sizeof(u_int8_t) * bytesToWrite.size());
    u_int32_t i2cAddress = I2C_ADDR_LOW;
    if (_sfp51Paging && page == PAGE_01)
    {
        i2cAddress = I2C_ADDR_HIGH;
    }
    writeMCIA(page, numberOfAllignedBytes, numberOfZeroBytes, offset, data, i2cAddress);
    free(data);
}
// Checking read command parameters and initializing the valid pages
void MlxlinkCablesCommander::checkParams(u_int16_t offset, u_int16_t length)
{
    if (offset > (EEPROM_PAGE_LENGTH + 1))
    {
        throw MlxRegException("Invalid offset value %d. It must be within range [0-255].", offset);
    }
    if (length > (EEPROM_PAGE_LENGTH + 1))
    {
        throw MlxRegException("Invalid length value %d. It must be within range [0-255].", length);
    }
    if ((length + offset) > (EEPROM_PAGE_LENGTH + 1))
    {
        throw MlxRegException("The length of bytes exceeded the page size.", length);
    }
}

// Reading specific offset\page from cable EEPRM
MlxlinkCmdPrint MlxlinkCablesCommander::readFromEEPRM(u_int16_t page, u_int16_t offset, u_int16_t length)
{
    checkParams(offset, length);

    u_int8_t* pageL = NULL;
    u_int8_t* pageH = NULL;
    u_int32_t i2cAddress = I2C_ADDR_LOW;
    // if SFP51 paging is supported, then we use i2c 0x51 to Access page 1
    if (_sfp51Paging && (page >= PAGE_01 || offset >= CABLE_PAGE_SIZE))
    {
        i2cAddress = I2C_ADDR_HIGH;
    }
    pageL = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
    loadEEPRMPage(page, LOWER_PAGE_OFFSET, pageL, i2cAddress);
    if ((length + offset) > CABLE_PAGE_SIZE)
    {
        pageH = (u_int8_t*)calloc(CABLE_PAGE_SIZE, sizeof(u_int8_t));
        loadEEPRMPage(page, UPPER_PAGE_OFFSET, pageH);
    }
    char label[32];
    char val[32];
    u_int8_t byteVal = 0;
    u_int32_t i = 0;
    MlxlinkCmdPrint bytesOutput = MlxlinkCmdPrint();
    setPrintTitle(bytesOutput, "Cable Read Output", length + 1);

    u_int32_t currOffset = 0;
    for (i = 0; i < length; ++i)
    {
        currOffset = offset + i;
        sprintf(label, "page[%d].Byte[%d]", page, currOffset);
        if (currOffset < CABLE_PAGE_SIZE)
        {
            readFromPage(pageL, currOffset, &byteVal);
            sprintf(val, "0x%02x", byteVal);
        }
        else
        {
            readFromPage(pageH, currOffset - UPPER_PAGE_OFFSET, &byteVal);
            sprintf(val, "0x%02x", byteVal);
        }
        setPrintVal(bytesOutput, label, val, ANSI_COLOR_RESET, true, true, true);
    }
    bytesOutput.toJsonFormat(_jsonRoot);

    free(pageL);
    free(pageH);
    return bytesOutput;
}

u_int32_t MlxlinkCablesCommander::getModeAdminFromStr(u_int32_t cap, const string& adminStr, ModuleAccess_t moduleAccess)
{
    int modeAdmin = _prbsMode;
    string confStr = adminStr.empty() ? DEFAULT_PRBS_MODE_STR : adminStr;
    modeAdmin = _mlxlinkMaps->_modulePrbsModeStrToCap[confStr];
    if (!modeAdmin || !(modeAdmin & cap))
    {
        string validRates = "[";
        for (auto it = _mlxlinkMaps->_modulePrbsModeCapToStr.begin(); it != _mlxlinkMaps->_modulePrbsModeCapToStr.end();
             it++)
        {
            if (it->first & cap)
            {
                validRates += it->second + ",";
            }
        }
        validRates = deleteLastChar(validRates);
        validRates += "]";
        throw MlxRegException("Invalid PRBS pattern for the %s [%s]\nValid values are: %s",
                              _mlxlinkMaps->_moduleScopeToStr[moduleAccess].c_str(), confStr.c_str(),
                              validRates.c_str());
    }
    return (int)log2((float)modeAdmin);
}

u_int32_t MlxlinkCablesCommander::getRateAdminFromStr(u_int32_t cap, const string& rateStr)
{
    int rateAdmin = _prbsRate;
    string confStr = rateStr.empty() ? DEFAULT_PRBS_RATE_STR : rateStr;
    rateAdmin = _mlxlinkMaps->_modulePrbsRateStrToCap[confStr];
    if (!rateAdmin || !(rateAdmin & cap))
    {
        string validRates = "[";
        for (auto it = _mlxlinkMaps->_modulePrbsRateStrToCap.begin(); it != _mlxlinkMaps->_modulePrbsRateStrToCap.end();
             it++)
        {
            if (it->second & cap)
            {
                validRates += it->first + ",";
            }
        }
        validRates = deleteLastChar(validRates);
        validRates += "]";
        throw MlxRegException("Invalid PRBS lane rate configuration [%s]\nValid configurations are: %s",
                              confStr.c_str(), validRates.c_str());
    }
    return rateAdmin;
}

bool MlxlinkCablesCommander::getInvAdminFromStr(u_int32_t cap, const string& invStr, ModuleAccess_t moduleAccess)
{
    bool invAdmin = false;
    if (!invStr.empty())
    {
        invAdmin = true;
        if (!cap)
        {
            throw MlxRegException("PRBS inversion is not supported by the %s",
                                  _mlxlinkMaps->_moduleScopeToStr[moduleAccess].c_str());
        }
    }
    return invAdmin;
}

bool MlxlinkCablesCommander::getSwapAdminFromStr(u_int32_t cap, const string& swapStr, ModuleAccess_t moduleAccess)
{
    bool swapAdmin = false;
    if (!swapStr.empty())
    {
        swapAdmin = true;
        if (!cap)
        {
            throw MlxRegException("PAM4 MSB <-> LSB swapping is not supported by the %s",
                                  _mlxlinkMaps->_moduleScopeToStr[moduleAccess].c_str());
        }
    }
    return swapAdmin;
}

u_int32_t MlxlinkCablesCommander::getLanesFromStr(u_int32_t cap, const string& lanesStr)
{
    u_int32_t laneMask = 0;
    string temp = lanesStr;
    if (!lanesStr.empty())
    {
        if (!cap)
        {
            throw MlxRegException("No support of per lane configuration by the module");
        }
        auto lanesVec = MlxlinkRecord::split(temp, ",");
        u_int32_t val = 0;
        for (auto it = lanesVec.begin(); it != lanesVec.end(); it++)
        {
            strToUint32((char*)(*it).c_str(), val);
            if (val > (_numOfLanes - 1))
            {
                throw MlxRegException("Invalid lane index [%d], valid lanes range is [0 to %d]", val,
                                      (_numOfLanes - 1));
            }
            laneMask |= (u_int32_t)pow(2.0, (double)val);
        }
    }
    return laneMask;
}

void MlxlinkCablesCommander::getNumOfModuleLanes()
{
    try
    {
        // As a WA, use module_width for MEDIA and HOST lanes
        // TODO: use module_media_width once it be supported
        // if (_modulePrbsParams[MODULE_PRBS_SELECT] == "HOST") {
        sendPrmReg(ACCESS_REG_PMTM, GET, "module=%d,slot_index=%d", _moduleNumber, _slotIndex);

        _numOfLanes = getFieldValue("module_width");
        //} else {
        //_numOfLanes = getFieldValue("module_media_width");
        //}
    }
    catch (MlxRegException& exc)
    {
    }
}

void MlxlinkCablesCommander::checkAndParsePMPTCap(ModuleAccess_t moduleAccess)
{
    bool regFaild = false;
    try
    {
        sendPrmReg(ACCESS_REG_PMPT, GET, "module=%d,slot_index=%d,lane_mask=%d", _moduleNumber, _slotIndex, 1);
    }
    catch (MlxRegException& exc)
    {
        regFaild = true;
    }
    if (regFaild || getFieldValue("status") == PMPT_STATUS_NOT_SUPPORTED)
    {
        throw MlxRegException("Module doesn't support PRBS and diagnostics data");
    }
    _prbsRate = getRateAdminFromStr(getFieldValue("lane_rate_cap"), _modulePrbsParams[ModulePrbs_t(MODULE_PRBS_RATE)]);

    // read the other PMPT caps according to the prbsRate
    sendPrmReg(ACCESS_REG_PMPT, GET, "module=%d,slot_index=%d,host_media=%d,lane_mask=%d,ch_ge=%d,modulation=%d",
               _moduleNumber, _slotIndex, _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 1, (u_int32_t)moduleAccess,
               _prbsRate >= MODULE_PRBS_LANE_RATE_HDR);

    u_int32_t chAccessShift = moduleAccess == MODULE_PRBS_ACCESS_CH ? MODULE_PRBS_GEN_INV : 0;

    _prbsMode = getModeAdminFromStr(getFieldValue("prbs_modes_cap"),
                                    _modulePrbsParams[ModulePrbs_t(MODULE_PRBS_GEN_PAT + chAccessShift)], moduleAccess);
    _prbsInv = getInvAdminFromStr(getFieldValue("invt_cap"),
                                  _modulePrbsParams[ModulePrbs_t(MODULE_PRBS_GEN_INV + chAccessShift)], moduleAccess);
    _prbsSwap = getSwapAdminFromStr(
      getFieldValue("swap_cap"), _modulePrbsParams[ModulePrbs_t(MODULE_PRBS_GEN_SWAP + chAccessShift)], moduleAccess);
    _prbsLanes =
      getLanesFromStr(getFieldValue("ls"), _modulePrbsParams[ModulePrbs_t(MODULE_PRBS_GEN_LANES + chAccessShift)]);
}

u_int32_t MlxlinkCablesCommander::getPMPTStatus(ModuleAccess_t moduleAccess)
{
    sendPrmReg(ACCESS_REG_PMPT, GET, "module=%d,slot_index=%d,host_media=%d,lane_mask=%d,ch_ge=%d", _moduleNumber,
               _slotIndex, _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 1, (u_int32_t)moduleAccess);

    return getFieldValue("status");
}

void MlxlinkCablesCommander::sendPMPT(ModuleAccess_t moduleAccess)
{
    checkAndParsePMPTCap(moduleAccess);

    sendPrmReg(ACCESS_REG_PMPT, SET,
               "module=%d,slot_index=%d,host_media=%d,lane_mask=%d,ch_ge=%d,e=%d,prbs_mode_admin=%d,lane_rate_admin=%d,"
               "invt_admin=%d,swap_admin=%d,le=%d,modulation=%d",
               _moduleNumber, _slotIndex, _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST",
               _prbsLanes ? _prbsLanes : 0xff, (u_int32_t)moduleAccess, 1, _prbsMode, _prbsRate, _prbsInv, _prbsSwap,
               _prbsLanes != 0, _prbsRate >= MODULE_PRBS_LANE_RATE_HDR);

    if (getPMPTStatus(moduleAccess) == PMPT_STATUS_CONFIG_ERROR)
    {
        throw MlxRegException("Unsupported configuration setting");
    }
}

void MlxlinkCablesCommander::enablePMPT(ModuleAccess_t moduleAccess)
{
    switch (moduleAccess)
    {
        case MODULE_PRBS_ACCESS_CH:
        case MODULE_PRBS_ACCESS_GEN:
            sendPMPT(moduleAccess);
            break;
        case MODULE_PRBS_ACCESS_CH_GEN:
            sendPMPT(MODULE_PRBS_ACCESS_CH);
            sendPMPT(MODULE_PRBS_ACCESS_GEN);
            break;
        default:
            sendPMPT(MODULE_PRBS_ACCESS_BOTH);
    }
}

void MlxlinkCablesCommander::disablePMPT()
{
    sendPrmReg(ACCESS_REG_PMPT, SET, "module=%d,slot_index=%d,host_media=%d,lane_mask=%d", _moduleNumber, _slotIndex,
               _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 0xff);
}

void MlxlinkCablesCommander::handlePrbsTestMode(const string& ctrl, ModuleAccess_t moduleAccess)
{
    if (ctrl == "EN")
    {
        MlxlinkRecord::printCmdLine("Enabling Module PRBS Test Mode", _jsonRoot);
        getNumOfModuleLanes();
        enablePMPT(moduleAccess);
    }
    else if (ctrl == "DS")
    {
        MlxlinkRecord::printCmdLine("Disabling Module PRBS Test Mode", _jsonRoot);
        disablePMPT();
    }
    else
    {
        throw MlxRegException("Invalid PRBS Module mode, please check the help menu");
    }
}

void MlxlinkCablesCommander::getPMPTConfiguration(ModuleAccess_t moduleAccess,
                                                  vector<string>& prbsPattern,
                                                  vector<string>& prbsRate,
                                                  vector<string>& prbsInv,
                                                  vector<string>& prbsSwap)
{
    sendPrmReg(ACCESS_REG_PMPT, GET, "module=%d,slot_index=%d,host_media=%d,lane_mask=%d,ch_ge=%d", _moduleNumber,
               _slotIndex, _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 1, (u_int32_t)moduleAccess);

    u_int32_t index = (u_int32_t)pow(2.0, (double)getFieldValue("prbs_mode_admin"));
    prbsPattern.push_back(MlxlinkRecord::addSpaceForModulePrbs(_mlxlinkMaps->_modulePrbsModeCapToStr[index]));

    index = getFieldValue("lane_rate_admin");
    prbsRate.push_back(MlxlinkRecord::addSpaceForModulePrbs(_mlxlinkMaps->_modulePrbsRateCapToStr[index]));

    string capStr = getFieldValue("invt_cap") ? "" : "Not Supported";
    string adminStr = getFieldValue("invt_admin") ? "Yes" : "No";
    prbsInv.push_back(MlxlinkRecord::addSpaceForModulePrbs(!capStr.empty() ? capStr : adminStr));

    capStr = getFieldValue("swap_cap") ? "" : "Not Supported";
    adminStr = getFieldValue("swap_admin") ? "Yes" : "No";
    prbsSwap.push_back(MlxlinkRecord::addSpaceForModulePrbs(!capStr.empty() ? capStr : adminStr));
}

string MlxlinkCablesCommander::getPMPDLockStatus()
{
    string lockStatusStr = "";

    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        sendPrmReg(ACCESS_REG_PMPD, GET, "module=%d,slot_index=%d,host_media=%d,lane=%d", _moduleNumber, _slotIndex,
                   _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", lane);

        lockStatusStr += MlxlinkRecord::addSpaceForModulePrbs(_mlxlinkMaps->_modulePMPDStatus[getFieldValue("status")]);
        lockStatusStr += ",";
        // Print only one indecation for each cap if it's not supported
        if (getFieldValue("status") == PMPD_STATUS_NOT_SUPPORTED)
        {
            break;
        }
    }

    if (!lockStatusStr.empty())
    {
        lockStatusStr = deleteLastChar(lockStatusStr);
    }

    return lockStatusStr;
}

void MlxlinkCablesCommander::showPrbsTestMode()
{
    MlxlinkCmdPrint prbsOutput = MlxlinkCmdPrint();
    setPrintTitle(prbsOutput, "Module PRBS Test Mode", MODULE_PMPT_INFO_LAST);

    getNumOfModuleLanes();

    try
    {
        sendPrmReg(ACCESS_REG_PMPT, GET, "module=%d,slot_index=%d,host_media=%d,lane_mask=%d", _moduleNumber,
                   _slotIndex, _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 1);
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("Device doesn't support Module PRBS and diagnostics data");
    }

    setPrintVal(prbsOutput, "Status", _mlxlinkMaps->_modulePrbsSt[getFieldValue("status")]);
    setPrintVal(prbsOutput, "Lock Status [per lane]", getPMPDLockStatus(), ANSI_COLOR_RESET, true, true, true);

    vector<string> prbsAcces, prbsPattern, prbsRate, prbsInv, prbsSwap;
    prbsAcces.push_back(MlxlinkRecord::addSpaceForModulePrbs("Checker"));
    prbsAcces.push_back(MlxlinkRecord::addSpaceForModulePrbs("Generator"));

    getPMPTConfiguration(MODULE_PRBS_ACCESS_CH, prbsPattern, prbsRate, prbsInv, prbsSwap);
    getPMPTConfiguration(MODULE_PRBS_ACCESS_GEN, prbsPattern, prbsRate, prbsInv, prbsSwap);

    setPrintVal(prbsOutput, "PRBS Access", getStringFromVector(prbsAcces), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(prbsOutput, "PRBS Pattern", getStringFromVector(prbsPattern), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(prbsOutput, "PRBS Lane Rate ", getStringFromVector(prbsRate), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(prbsOutput, "PRBS Inversion", getStringFromVector(prbsInv), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(prbsOutput, "PRBS MSB<->LSB Swap", getStringFromVector(prbsSwap), ANSI_COLOR_RESET, true, true, true);

    prbsOutput.toJsonFormat(_jsonRoot);

    cout << prbsOutput;
}

void MlxlinkCablesCommander::getPMPDInfo(vector<string>& traffic,
                                         vector<string>& errors,
                                         vector<string>& ber,
                                         vector<string>& snr)
{
    string traficStr, errorsStr, berStr, snrStr;
    bool skipErrorCap = false;
    bool skipBerCap = false;
    bool skipSnrCap = false;
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        sendPrmReg(ACCESS_REG_PMPD, GET, "module=%d,slot_index=%d,host_media=%d,lane=%d", _moduleNumber, _slotIndex,
                   _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", lane);

        traficStr = to_string(add32BitTo64(getFieldValue("prbs_bits_high"), getFieldValue("prbs_bits_low")));
        errorsStr = to_string(add32BitTo64(getFieldValue("prbs_errors_high"), getFieldValue("prbs_errors_low")));
        berStr = to_string(getFieldValue("ber_coef")) + "E-" + to_string(getFieldValue("ber_magnitude"));
        snrStr = getFieldValue("measured_snr") ? (to_string(getFieldValue("measured_snr")) + " dB") : "N/A";

        traffic.push_back(MlxlinkRecord::addSpaceForModulePrbs(traficStr));

        if (!skipErrorCap)
        {
            errors.push_back(
              MlxlinkRecord::addSpaceForModulePrbs(getFieldValue("errors_cap") ? errorsStr : "Not Supported"));
        }
        if (!skipBerCap)
        {
            ber.push_back(MlxlinkRecord::addSpaceForModulePrbs(getFieldValue("ber_cap") ? berStr : "Not Supported"));
        }
        if (!skipSnrCap)
        {
            snr.push_back(MlxlinkRecord::addSpaceForModulePrbs(getFieldValue("snr_cap") ? snrStr : "Not Supported"));
        }
        // Print only one indication for each cap if it's not supported
        if (getFieldValue("errors_cap") == 0)
        {
            skipErrorCap = true;
        }
        if (getFieldValue("ber_cap") == 0)
        {
            skipBerCap = true;
        }
        if (getFieldValue("snr_cap") == 0)
        {
            skipSnrCap = true;
        }
    }
}

void MlxlinkCablesCommander::showPrpsDiagInfo()
{
    vector<string> traffic, errors, ber, snr;
    MlxlinkCmdPrint diagOutput = MlxlinkCmdPrint();

    getNumOfModuleLanes();

    setPrintTitle(diagOutput, "Module PRBS Diagnostic Counters", MODULE_PMPD_INFO_LAST);

    getPMPDInfo(traffic, errors, ber, snr);

    setPrintVal(diagOutput, "PRBS Traffic (bits) [per lane]", getStringFromVector(traffic), ANSI_COLOR_RESET, true,
                true, true);
    setPrintVal(diagOutput, "PRBS Errors [per lane]", getStringFromVector(errors), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(diagOutput, "PRBS BER [per lane]", getStringFromVector(ber), ANSI_COLOR_RESET, true, true, true);
    setPrintVal(diagOutput, "Measured SNR [per lane]", getStringFromVector(snr), ANSI_COLOR_RESET, true, true, true);

    diagOutput.toJsonFormat(_jsonRoot);

    cout << diagOutput;
}

void MlxlinkCablesCommander::clearPrbsDiagInfo()
{
    MlxlinkRecord::printCmdLine("Clearing PRBS Diagnostic Counters", _jsonRoot);

    sendPrmReg(ACCESS_REG_PMPD, GET, "module=%d,slot_index=%d,host_media=%d,cl=%d", _moduleNumber, _slotIndex,
               _modulePrbsParams[MODULE_PRBS_SELECT] == "HOST", 1);
}

void MlxlinkCablesCommander::showControlParams()
{
    MlxlinkCmdPrint controlParamsOutput = MlxlinkCmdPrint();
    setPrintTitle(controlParamsOutput, "Module Control Parameters", CABLE_CONTROL_PARAMETERS_SET_RX_AMP);

    u_int32_t txEq = 0;
    u_int32_t rxPostEmph = 0;
    u_int32_t rxAmp = 0;
    float rxEmph = 0.0;
    if (!_isSwControled)
    {
        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_INFO_PAGE);

        txEq = getFieldValue("cable_tx_equalization");
        rxEmph = (double)getFieldValue("cable_rx_emphasis");
        rxPostEmph = getFieldValue("cable_rx_post_emphasis");
        rxAmp = getFieldValue("cable_rx_amp");
    }

    bool isCmis = _cableIdentifier >= IDENTIFIER_SFP_DD;

    sendPrmReg(ACCESS_REG_PMCR, GET);

    if (isCmis)
    {
        _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_EMPH].first += " (pre)";
        rxEmph /= 2;
    }
    char rxEmphStr[64];
    sprintf(rxEmphStr, "%.1f", rxEmph);

    string strFmt = txEq ? to_string(txEq) + " dB" : "No Equalization";
    strFmt = getFieldValue("tx_equ_override_cap") ? strFmt : "Not Supported";
    setPrintVal(controlParamsOutput, _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_TX_EQ].first, strFmt);

    strFmt = (isCmis ? rxEmphStr : to_string((u_int32_t)rxEmph)) + " dB";
    strFmt = (rxEmph > 0) ? strFmt : "No Equalization";
    strFmt = getFieldValue("rx_emp_override_cap") ? strFmt : "Not Supported";
    setPrintVal(controlParamsOutput, _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_EMPH].first, strFmt);

    strFmt = rxPostEmph ? to_string(rxPostEmph) + " dB" : "No Equalization";
    strFmt = getFieldValue("rx_post_emp_override_cap") ? strFmt : "Not Supported";
    setPrintVal(controlParamsOutput, _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_POST_EMPH].first, strFmt,
                ANSI_COLOR_RESET, isCmis);

    strFmt = _mlxlinkMaps->_moduleRxAmp[rxAmp];
    strFmt = getFieldValue("rx_amp_override_cap") ? strFmt : "Not Supported";
    setPrintVal(controlParamsOutput, _modulePMCRParams[CABLE_CONTROL_PARAMETERS_SET_RX_AMP].first, strFmt);

    controlParamsOutput.toJsonFormat(_jsonRoot);
    cout << controlParamsOutput;
}

u_int32_t MlxlinkCablesCommander::pmcrStrToValue(ControlParam paramId, const string& value)
{
    double valueToSet = 0;
    bool invalidConfiguration = false;
    bool isCmis = _cableIdentifier >= IDENTIFIER_SFP_DD;
    bool isDecemal = false;
    string valueStr = value;

    try
    {
        toUpperCase(valueStr);
        valueToSet = valueStr == "NE" ? 0 : stod(value);
        isDecemal = (valueToSet - (int)valueToSet) > 0;
    }
    catch (exception& exc)
    {
        invalidConfiguration = true;
    }

    if (isDecemal && !isCmis && paramId == CABLE_CONTROL_PARAMETERS_SET_RX_EMPH)
    {
        invalidConfiguration = true;
    }

    if (isCmis && paramId == CABLE_CONTROL_PARAMETERS_SET_RX_EMPH)
    {
        _modulePMCRParams[paramId].first += " (pre)";
        valueToSet *= 2;
        if ((valueToSet - (int)valueToSet) > 0)
        {
            invalidConfiguration = true;
        }
    }

    if ((valueToSet < 0) || (valueStr == "0" && paramId != CABLE_CONTROL_PARAMETERS_SET_RX_AMP) ||
        (valueToSet > MAX_SFF_CODE_VALUE) || (isDecemal && paramId != CABLE_CONTROL_PARAMETERS_SET_RX_EMPH))
    {
        invalidConfiguration = true;
    }

    if (invalidConfiguration)
    {
        u_int32_t capVal = getFieldValue(_modulePMCRParams[paramId].second + "_value_cap");
        string capStr = "";
        if (capVal)
        {
            capStr = "\nSupported configuration values are [";
            capStr += getPMCRCapValueStr(capVal, paramId);
            capStr += "]";
        }
        throw MlxRegException("Invalid %s configuration: %s %s", _modulePMCRParams[paramId].first.c_str(),
                              value.c_str(), capStr.c_str());
    }

    return (u_int32_t)valueToSet;
}

string MlxlinkCablesCommander::getPMCRCapValueStr(u_int32_t valueCap, ControlParam paramId)
{
    string capStr = "";

    if (paramId == CABLE_CONTROL_PARAMETERS_SET_RX_AMP)
    {
        capStr = getStrByMask(valueCap, _mlxlinkMaps->_moduleRxAmpCap);
    }
    else
    {
        char tmpFmt[64];
        for (u_int32_t val = 0; val <= valueCap; val++)
        {
            if (val == 0)
            {
                capStr += "NE,";
            }
            else if (_cableIdentifier >= IDENTIFIER_SFP_DD && paramId == CABLE_CONTROL_PARAMETERS_SET_RX_EMPH)
            {
                sprintf(tmpFmt, "%.1f,", ((float)val / 2.0));
                capStr += string(tmpFmt);
            }
            else
            {
                sprintf(tmpFmt, "%d,", val);
                capStr += string(tmpFmt);
            }
        }
        capStr = deleteLastChar(capStr);
    }

    return capStr;
}

void MlxlinkCablesCommander::checkPMCRFieldsCap(vector<pair<ControlParam, string>>& params)
{
    sendPrmReg(ACCESS_REG_PMCR, GET);

    // Check provided params exestance capability
    string fieldName = "";
    for (auto it = params.begin(); it != params.end(); it++)
    {
        fieldName = _modulePMCRParams[it->first].first;
        if (it->first == CABLE_CONTROL_PARAMETERS_SET_RX_POST_EMPH && _cableIdentifier < IDENTIFIER_SFP_DD)
        {
            throw MlxRegException("%s configuration is valid for CMIS only", fieldName.c_str());
        }
        if (!getFieldValue(_modulePMCRParams[it->first].second + "_cap"))
        {
            throw MlxRegException("%s configuration is not supported for the current module", fieldName.c_str());
        }
    }

    // Check provided params value capability
    bool invalidVal = false;
    u_int32_t valueToSet = 0;
    u_int32_t valueCap = 0;
    string validCapStr = "";
    for (auto it = params.begin(); it != params.end(); it++)
    {
        fieldName = _modulePMCRParams[it->first].second;
        valueToSet = pmcrStrToValue(it->first, it->second);
        valueCap = getFieldValue(fieldName + "_value_cap");
        if (it->first == CABLE_CONTROL_PARAMETERS_SET_RX_AMP)
        {
            valueToSet = (u_int32_t)pow(2.0, (double)valueToSet);
            if (!(valueCap & valueToSet))
            {
                invalidVal = true;
            }
        }
        else if (valueToSet > valueCap)
        {
            invalidVal = true;
        }
        if (invalidVal)
        {
            if (valueCap)
            {
                validCapStr = "\nSupported configuration values are [";
                validCapStr += getPMCRCapValueStr(valueCap, it->first);
                validCapStr += "]";
            }
            throw MlxRegException("Not supported %s configuration value: %s %s",
                                  _modulePMCRParams[it->first].first.c_str(), it->second.c_str(), validCapStr.c_str());
        }
    }
}

string MlxlinkCablesCommander::buildPMCRRequest(ControlParam paramId, const string& value)
{
    u_int32_t valueToSet = pmcrStrToValue(paramId, value);

    string pmcrReq = _modulePMCRParams[paramId].second + "_cntl=2,";
    pmcrReq += _modulePMCRParams[paramId].second + "_value=" + to_string((u_int32_t)valueToSet);

    return pmcrReq;
}

void MlxlinkCablesCommander::setControlParams(vector<pair<ControlParam, string>>& params)
{
    MlxlinkRecord::printCmdLine("Overriding Cable Control Parameters", _jsonRoot);

    checkPMCRFieldsCap(params);

    string fieldsStr = "";
    string pmcrFieldsRequest = "";
    try
    {
        for (auto it = params.begin(); it != params.end(); it++)
        {
            fieldsStr += _modulePMCRParams[it->first].first + ", ";
            pmcrFieldsRequest += buildPMCRRequest(it->first, it->second);
            pmcrFieldsRequest += ",";
        }

        pmcrFieldsRequest = deleteLastChar(pmcrFieldsRequest);
        sendPrmReg(ACCESS_REG_PMCR, SET, pmcrFieldsRequest.c_str());
    }
    catch (MlxRegException& exc)
    {
        fieldsStr = deleteLastChar(fieldsStr, 2);
        throw MlxRegException("Failed to set Control Parameters [%s]:\n%s", fieldsStr.c_str(), exc.what());
    }
}
