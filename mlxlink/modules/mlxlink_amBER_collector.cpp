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

#include "mlxlink_amBER_collector.h"
#include <ctime>

MlxlinkAmBerCollector::MlxlinkAmBerCollector(Json::Value& jsonRoot) : _jsonRoot(jsonRoot)
{
    _pnat = 0;
    _localPort = 1;
    _labelPort = _localPort;
    _splitPort = 0;
    _secondSplit = 0;
    _numOfLanes = 0;
    _maxLanes = MAX_NETWORK_LANES;
    _csvFileName = "";
    _mstDevName = "";
    _iteration = 0;
    _testMode = "NOMINAL";
    _depth = 0;
    _pcieIndex = 0;
    _node = 0;
    _protoActive = 0;
    _productTechnology = PRODUCT_16NM;
    _activeSpeed = 0;
    _devID = 0;
    _moduleIndex = 0;
    _slotIndex = 0;

    _isPortIB = false;
    _isPortETH = false;
    _isPortPCIE = false;
    _isMCMSysValid = false;
    _isGBSysValid = false;
    _isValidSensorMvcap = false;
    _isValidSensorMtcap = false;
    _isHca = false;

    _isCmisCable = false;
    _isQsfpCable = false;
    _isSfpCable = false;
    _cablePlugged = false;
    _inPRBSMode = false;
    _invalidate = false;

    _mlxlinkMaps = NULL;

    _baseSheetsList[AMBER_SHEET_GENERAL] = FIELDS_COUNT{4, 4, 4};
    _baseSheetsList[AMBER_SHEET_INDEXES] = FIELDS_COUNT{2, 2, 4};
    _baseSheetsList[AMBER_SHEET_LINK_STATUS] = FIELDS_COUNT{49, 142, 6};
    _baseSheetsList[AMBER_SHEET_MODULE_STATUS] = FIELDS_COUNT{110, 110, 0};
    _baseSheetsList[AMBER_SHEET_SYSTEM] = FIELDS_COUNT{16, 21, 11};
    _baseSheetsList[AMBER_SHEET_SERDES_16NM] = FIELDS_COUNT{376, 736, 0};
    _baseSheetsList[AMBER_SHEET_SERDES_7NM] = FIELDS_COUNT{206, 374, 502};
    _baseSheetsList[AMBER_SHEET_PORT_COUNTERS] = FIELDS_COUNT{35, 0, 50};
    _baseSheetsList[AMBER_SHEET_TROUBLESHOOTING] = FIELDS_COUNT{2, 2, 0};
    _baseSheetsList[AMBER_SHEET_PHY_OPERATION_INFO] = FIELDS_COUNT{17, 17, 15};
    _baseSheetsList[AMBER_SHEET_LINK_UP_INFO] = FIELDS_COUNT{9, 9, 0};
    _baseSheetsList[AMBER_SHEET_LINK_DOWN_INFO] = FIELDS_COUNT{5, 5, 0};
    _baseSheetsList[AMBER_SHEET_TEST_MODE_INFO] = FIELDS_COUNT{68, 136, 0};
    _baseSheetsList[AMBER_SHEET_TEST_MODE_MODULE_INFO] = FIELDS_COUNT{70, 110, 0};
    _baseSheetsList[AMBER_SHEET_PHY_DEBUG_INFO] = FIELDS_COUNT{4, 4, 0};
    _baseSheetsList[AMBER_SHEET_EXT_MODULE_STATUS] = FIELDS_COUNT{102, 102, 0};

    for_each(_baseSheetsList.begin(), _baseSheetsList.end(), [&](pair<AMBER_SHEET, FIELDS_COUNT> sheet) {
        _sheetsList.push_back({sheet.first, sheet.second});
    });
}

MlxlinkAmBerCollector::~MlxlinkAmBerCollector() {}

void MlxlinkAmBerCollector::resetLocalParser(const string& regName)
{
#ifndef VALIDATE_REG_REQUEST
    AmberField::_dataValid = !_invalidate;
#endif
    resetParser(regName);
}

void MlxlinkAmBerCollector::sendRegister(const string& regName, maccess_reg_method_t method)
{
    try
    {
        if (AmberField::_dataValid)
        {
            genBuffSendRegister(regName, method);
        }
    }
    catch (MlxRegException& exc)
    {
#ifdef VALIDATE_REG_REQUEST
        throw MlxRegException(regName + ": " + exc.what());
#else
        AmberField::_dataValid = false;
#endif
    }
}

void MlxlinkAmBerCollector::sendLocalPrmReg(const string& regName, maccess_reg_method_t method, const char* fields, ...)
{
    char fieldsCstr[MAX_FIELDS_BUFFER];
    try
    {
        if (AmberField::_dataValid)
        {
            va_list args;
            va_start(args, fields);
            vsnprintf(fieldsCstr, MAX_FIELDS_BUFFER, fields, args);
            va_end(args);

            sendPrmReg(regName, method, fieldsCstr);
        }
    }
    catch (MlxRegException& exc)
    {
#ifdef VALIDATE_REG_REQUEST
        throw MlxRegException(regName + ": " + exc.what());
#else
        AmberField::_dataValid = false;
#endif
    }
}

string MlxlinkAmBerCollector::getLocalFieldStr(const string& fieldName)
{
    string fieldVal = "N/A";
    try
    {
        fieldVal = getFieldStr(fieldName);
    }
    catch (MlxRegException& exc)
    {
#ifdef VALIDATE_REG_REQUEST
        throw MlxRegException(exc.what());
#endif
    }
    return fieldVal;
}

u_int32_t MlxlinkAmBerCollector::getLocalFieldValue(const string& fieldName)
{
    u_int32_t fieldVal = 0;
    try
    {
        fieldVal = getFieldValue(fieldName);
    }
    catch (MlxRegException& exc)
    {
#ifdef VALIDATE_REG_REQUEST
        throw MlxRegException(exc.what());
#endif
    }
    return fieldVal;
}

void MlxlinkAmBerCollector::startCollector()
{
    if (_localPorts.empty())
    {
        _localPorts.push_back(PortGroup(_localPort, _localPort, 0, 0));
    }

    for (auto it = _localPorts.begin(); it != _localPorts.end(); it++)
    {
        _localPort = it->localPort;
        _labelPort = it->labelPort;
        _splitPort = it->split;
        _secondSplit = it->secondSplit;

        init();
        collect();
        exportToCSV();

        _amberCollection.clear();
        AmberField::reset();
    }
}

void MlxlinkAmBerCollector::init()
{
    try
    {
        _isPortPCIE = (_pnat == PNAT_PCIE);

        if (!_isPortPCIE)
        {
            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);
            genBuffSendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            bool linkUp = getFieldValue("phy_mngr_fsm_state") == PHY_MNGR_ACTIVE_LINKUP;

            _protoActive = getFieldValue("proto_active");

            _isPortIB = (_protoActive == IB) && (_pnat != PNAT_PCIE);
            _isPortETH = (_protoActive == ETH) && (_pnat != PNAT_PCIE);
            _maxLanes = MAX_NETWORK_LANES;

            if (_protoActive == IB)
            {
                _activeSpeed = getFieldValue("link_speed_active");
                _numOfLanes = getFieldValue("link_width_active");
                _maxLanes = MAX_IB_LANES;
            }
            else
            {
                if (linkUp)
                {
                    resetParser(ACCESS_REG_PTYS);
                    updateField("local_port", _localPort);
                    updateField("proto_mask", _protoActive);
                    genBuffSendRegister(ACCESS_REG_PTYS, MACCESS_REG_METHOD_GET);

                    _activeSpeed = _productTechnology >= PRODUCT_16NM ? getFieldValue("ext_eth_proto_oper") :
                                                                        getFieldValue("eth_proto_oper");
                    _numOfLanes = _productTechnology >= PRODUCT_16NM ? _mlxlinkMaps->_ExtETHSpeed2Lanes[_activeSpeed] :
                                                                       _mlxlinkMaps->_ETHSpeed2Lanes[_activeSpeed];
                }
                else
                {
                    resetParser(ACCESS_REG_PMLP);
                    updateField("local_port", _localPort);
                    genBuffSendRegister(ACCESS_REG_PMLP, MACCESS_REG_METHOD_GET);

                    _activeSpeed = 0;
                    _numOfLanes = getFieldValue("width");
                }
            }

            resetLocalParser(ACCESS_REG_PPAOS);
            updateField("local_port", _localPort);
            genBuffSendRegister(ACCESS_REG_PPAOS, MACCESS_REG_METHOD_GET);

            _inPRBSMode = getFieldValue("phy_test_mode_status") == 1;

            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_LOCAL);
            updateField("page_select", PDDR_MODULE_INFO_PAGE);
            genBuffSendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            u_int32_t cableType = getFieldValue("cable_type");
            _cablePlugged = (cableType != UNIDENTIFIED) && (cableType != UNPLUGGED);

            resetLocalParser(ACCESS_REG_PMLP);
            updateField("local_port", _localPort);
            genBuffSendRegister(ACCESS_REG_PMLP, MACCESS_REG_METHOD_GET);

            _moduleIndex = getFieldValue("module_0");
            _slotIndex = getFieldValue("slot_index_0");

            resetLocalParser(ACCESS_REG_PMPT);
            updateField("module", _moduleIndex);
            updateField("slot_index", _slotIndex);
            updateField("host_media", 1);
            updateField("lane_mask", 0x1);
            sendRegister(ACCESS_REG_PMPT, MACCESS_REG_METHOD_GET);

            _moduleHostSt = getFieldValue("status");

            resetLocalParser(ACCESS_REG_PMPT);
            updateField("module", _moduleIndex);
            updateField("slot_index", _slotIndex);
            updateField("host_media", 0);
            updateField("lane_mask", 0x1);
            sendRegister(ACCESS_REG_PMPT, MACCESS_REG_METHOD_GET);

            _moduleMediaSt = getFieldValue("status");

            _inPRBSMode |= (_moduleHostSt >= PMPT_STATUS_GEN_ONLY || _moduleMediaSt >= PMPT_STATUS_GEN_ONLY);
        }
        else
        {
            resetParser(ACCESS_REG_MPEIN);
            updateField("pcie_index", _pcieIndex);
            updateField("depth", _depth);
            updateField("node", _node);
            genBuffSendRegister(ACCESS_REG_MPEIN, MACCESS_REG_METHOD_GET);

            _numOfLanes = getFieldValue("link_width_active");
            _maxLanes = MAX_PCIE_LANES;
        }

        initAmberSheetsToDump();
    }
    catch (...)
    {
    }
}

void MlxlinkAmBerCollector::initAmberSheetsToDump()
{
    // Custom sheet\s dump
    if (!_sheetsToDump.empty())
    {
        _sheetsList.clear();
        for_each(_sheetsToDump.begin(), _sheetsToDump.end(), [&](AMBER_SHEET& sheet) {
            _sheetsList.push_back({sheet, _baseSheetsList[sheet]});
        });
    }
}

bool MlxlinkAmBerCollector::isGBValid()
{
    return _isGBSysValid;
}

bool MlxlinkAmBerCollector::isMCMValid()
{
    return _isMCMSysValid;
}

string MlxlinkAmBerCollector::getCurrentTimeStamp()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    int millis = curTime.tv_usec / 1000;

    char buffer[80];
    std::time_t curTime_secs = curTime.tv_sec;
    strftime(buffer, 80, "%x-%X", localtime(&curTime_secs));

    char currentTime[84] = "";
    sprintf(currentTime, "%s.%03d", buffer, millis);
    return string(currentTime);
}

string MlxlinkAmBerCollector::getNodeGUID()
{
    string strGuid;

    if (_isHca)
    {
        resetLocalParser(ACCESS_REG_PGUID);
        updateField("local_port", _localPort);
        sendRegister(ACCESS_REG_PGUID, MACCESS_REG_METHOD_GET);

        strGuid = getRawFieldValueStr("node_guid");
    }
    else
    {
        char charGuid[64];
        resetLocalParser(ACCESS_REG_SPZR);
        sendRegister(ACCESS_REG_SPZR, MACCESS_REG_METHOD_GET);

        sprintf(charGuid, "0x%llx",
                (unsigned long long)add32BitTo64(getFieldValue("node_guid_h"), getFieldValue("node_guid_l")));
        strGuid = string(charGuid);
    }

    return strGuid.empty() ? "N/A" : strGuid;
}

string MlxlinkAmBerCollector::getMACAddress()
{
    char charMac[64];
    string strMac;
    string fieldName;

    if (_isHca)
    {
        resetLocalParser(ACCESS_REG_MGIR);
        sendRegister(ACCESS_REG_MGIR, MACCESS_REG_METHOD_GET);
        fieldName = "manufacturing_base_mac";
    }
    else
    {
        resetLocalParser(ACCESS_REG_SPAD);
        sendRegister(ACCESS_REG_SPAD, MACCESS_REG_METHOD_GET);
        fieldName = "base_mac";
    }

    sprintf(charMac, "0x%llx",
            (unsigned long long)add32BitTo64(getFieldValue(fieldName + "_47_32"), getFieldValue(fieldName + "_31_0")));

    strMac = string(charMac);

    return strMac.empty() ? "N/A" : strMac;
}

vector<AmberField> MlxlinkAmBerCollector::getIndexesInfo()
{
    vector<AmberField> fields;

    if (_isPortIB || _isPortPCIE)
    {
        fields.push_back(AmberField("Node_GUID", getNodeGUID()));
    }

    if (_isPortETH)
    {
        fields.push_back(AmberField("MAC_Address", getMACAddress()));
    }

    AmberField::_dataValid = true;
    string labelPortStr = to_string(_labelPort);
    if ((_splitPort && _splitPort != 1) || (_devID == DeviceQuantum2) || (_devID == DeviceQuantum3) ||
        (_devID == DeviceGB100))
    {
        /* For Quantum-2, the split notation will stand for the port in the cage
         * For other, only add the split notation if it's not 1
         */
        labelPortStr += "/" + to_string(_splitPort);
    }
    if ((_secondSplit && _secondSplit != 1) &&
        ((_devID == DeviceQuantum2) || (_devID == DeviceQuantum3) || (_devID == DeviceGB100)))
    {
        labelPortStr += "/" + to_string(_secondSplit);
    }
    fields.push_back(AmberField("Port_Number", labelPortStr + "(" + to_string(_localPort) + ")", !_isPortPCIE));
    fields.push_back(AmberField("depth", to_string(_depth), _isPortPCIE));
    fields.push_back(AmberField("pcie_index", to_string(_pcieIndex), _isPortPCIE));
    fields.push_back(AmberField("node", to_string(_node), _isPortPCIE));

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getGeneralInfo()
{
    vector<AmberField> fields;

    AmberField::_dataValid = true;

    fields.push_back(AmberField("amBer_Version", AMBER_VERSION));
    fields.push_back(AmberField("TimeStamp", getCurrentTimeStamp()));
    fields.push_back(AmberField("Iteration/Sweep", to_string(_iteration)));
    fields.push_back(AmberField("Test_Description", _testMode));

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getSystemInfo()
{
    vector<AmberField> fields;

    try
    {
        string sysVol = "N/A";
        string sysCur = "N/A";
        string sensNameVoltage = "N/A";
        string sensNameTemp = "N/A";
        string temp = "N/A";

        fields.push_back(AmberField("Device_Description", _mstDevName.c_str()));

        resetLocalParser(ACCESS_REG_MSGI);
        sendRegister(ACCESS_REG_MSGI, MACCESS_REG_METHOD_GET);
        fields.push_back(AmberField("Device_Part_Number", getAscii("part_number", 20)));

        resetLocalParser(ACCESS_REG_MGIR);
        sendRegister(ACCESS_REG_MGIR, MACCESS_REG_METHOD_GET);
        string fwVersion =
          getFieldStr("extended_major") + "." + getFieldStr("extended_minor") + "." + getFieldStr("extended_sub_minor");
        string tech = _mlxlinkMaps->_tech[getFieldValue("technology")];
        fields.push_back(AmberField("Device_FW_Version", fwVersion));

        resetLocalParser(ACCESS_REG_MDIR);
        sendRegister(ACCESS_REG_MDIR, MACCESS_REG_METHOD_GET);
        fields.push_back(AmberField("Device_ID", getRawFieldValueStr("device_id")));
        fields.push_back(AmberField("SerDes_Technology_(16nm/7nm_5nm)", tech));

        resetLocalParser(ACCESS_REG_MVCAP);
        sendRegister(ACCESS_REG_MVCAP, MACCESS_REG_METHOD_GET);
        _isValidSensorMvcap = getFieldValue("sensor_map_lo") & 0x1;
        if (_isValidSensorMvcap)
        {
            resetLocalParser(ACCESS_REG_MVCR);
            sendRegister(ACCESS_REG_MVCR, MACCESS_REG_METHOD_GET);
            sysVol = to_string(getFieldValue("voltage_sensor_value") * 0.01) + "V";
            sysCur = getFieldStr("current_sensor_value");
            sensNameVoltage =
              getFullString(add32BitTo64(getFieldValue("sensor_name_hi"), getFieldValue("sensor_name_lo")));
        }
        fields.push_back(AmberField("System_Voltage", sysVol));
        fields.push_back(AmberField("System_Current", sysCur));
        fields.push_back(AmberField("Voltage/Current_sensor_name", sensNameVoltage));

        resetLocalParser(ACCESS_REG_MTCAP);
        sendRegister(ACCESS_REG_MTCAP, MACCESS_REG_METHOD_GET);
        _isValidSensorMtcap = getFieldValue("sensor_map_lo") & 0x1;
        if (_isValidSensorMtcap)
        {
            resetLocalParser(ACCESS_REG_MTMP);
            sendRegister(ACCESS_REG_MTMP, MACCESS_REG_METHOD_GET);
            temp = getTemp(getFieldValue("temperature"), 8);
            sensNameTemp =
              getFullString(add32BitTo64(getFieldValue("sensor_name_hi"), getFieldValue("sensor_name_lo")));
        }
        fields.push_back(AmberField("Chip_Temp", temp));

        resetLocalParser(ACCESS_REG_MSGI);
        sendRegister(ACCESS_REG_MSGI, MACCESS_REG_METHOD_GET);
        fields.push_back(AmberField("Device_SN", getAscii("serial_number", 24)));

        fields.push_back(AmberField("Temp_sensor_name", sensNameTemp));

        resetLocalParser(ACCESS_REG_PDDR);
        updateField("local_port", _localPort);
        updateField("page_select", PDDR_MODULE_INFO_PAGE);
        sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);
        fields.push_back(AmberField("Module_Temp", getTemp(getFieldValue("temperature")), !_isPortPCIE));
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Device information: %s", exc.what());
    }

    return fields;
}

string MlxlinkAmBerCollector::getClRawBer()
{
    double rawBerCoef = getFieldValue("raw_ber_coef");
    double rawBerMag = getFieldValue("raw_ber_magnitude");
    double rawBer = rawBerCoef * std::pow(10, -rawBerMag);
    double timeSinceLinkUp =
      ((double)add32BitTo64(getFieldValue("time_since_last_clear_high"), getFieldValue("time_since_last_clear_low"))) /
      1000.0;
    double activeRate =
      _protoActive == IB ? _mlxlinkMaps->_IBSpeed2gNum[_activeSpeed] : _mlxlinkMaps->_EthExtSpeed2gNum[_activeSpeed];

    double rateBerLane = (activeRate / _numOfLanes) * pow(10.0, 9);

    double clBer = 0;
    char clBerStr[128];
    if (activeRate)
    {
        clBer = 1 - exp(-1 * rateBerLane * timeSinceLinkUp * rawBer);
    }
    sprintf(clBerStr, "%.1E", clBer);

    return string(clBerStr);
}

vector<AmberField> MlxlinkAmBerCollector::getPhyOperationInfo()
{
    vector<AmberField> fields;

    try
    {
        resetLocalParser(ACCESS_REG_PDDR);
        updateField("local_port", _localPort);
        updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);
        sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

        string phyManagerLinkEnabledStr = "N/A";
        string coreToPhyLinkEnabledStr = "N/A";
        string cableProtoCapStr = "N/A";

        fields.push_back(AmberField("eth_an_fsm_state",
                                    _mlxlinkMaps->_ethANFsmState[getFieldValue("eth_an_fsm_"
                                                                               "state")],
                                    !_isPortPCIE));
        fields.push_back(AmberField("ib_phy_fsm_state",
                                    _mlxlinkMaps->_ibPhyFsmState[getFieldValue("ib_phy_fsm_"
                                                                               "state")],
                                    !_isPortPCIE));
        if (_isPortIB)
        {
            phyManagerLinkEnabledStr =
              getStrByMask(getFieldValue("phy_manager_link_proto_enabled"), _mlxlinkMaps->_IBSpeed2Str);
            coreToPhyLinkEnabledStr =
              getStrByMask(getFieldValue("core_to_phy_link_proto_enabled"), _mlxlinkMaps->_IBSpeed2Str);
            cableProtoCapStr = getStrByMask(getFieldValue("cable_link_speed_cap"), _mlxlinkMaps->_IBSpeed2Str);
        }
        else if (_isPortETH)
        {
            phyManagerLinkEnabledStr =
              getStrByMask(getFieldValue("phy_manager_link_eth_enabled"), _mlxlinkMaps->_EthExtSpeed2Str);
            coreToPhyLinkEnabledStr =
              getStrByMask(getFieldValue("core_to_phy_link_eth_enabled"), _mlxlinkMaps->_EthExtSpeed2Str);
            cableProtoCapStr = getStrByMask(getFieldValue("cable_ext_eth_proto_cap"), _mlxlinkMaps->_EthExtSpeed2Str);
        }
        fields.push_back(AmberField("phy_manager_link_enabled", phyManagerLinkEnabledStr, !_isPortPCIE));
        fields.push_back(AmberField("core_to_phy_link_enabled", coreToPhyLinkEnabledStr, !_isPortPCIE));
        fields.push_back(AmberField("cable_proto_cap", cableProtoCapStr, !_isPortPCIE));
        u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");
        string loopbackMode = (phyMngrFsmState != PHY_MNGR_DISABLED) ?
                                _mlxlinkMaps->_loopbackModeList[getFieldValue("loopback_mode")].second :
                                "-1";
        u_int32_t fecModeRequest = (u_int32_t)log2((float)getFieldValue("fec_mode_request"));
        fields.push_back(AmberField("loopback_mode", loopbackMode, !_isPortPCIE));
        fields.push_back(AmberField("fec_mode_request", _mlxlinkMaps->_fecModeActive[fecModeRequest], !_isPortPCIE));

        if (_isPortPCIE)
        {
            resetLocalParser(ACCESS_REG_MPEIN);
            updateField("depth", _depth);
            updateField("pcie_index", _pcieIndex);
            updateField("node", _node);
            sendRegister(ACCESS_REG_MPEIN, MACCESS_REG_METHOD_GET);

            fields.push_back(AmberField("link_width_enabled", getFieldStr("link_width_enabled") + "x"));
            fields.push_back(AmberField("link_speed_enabled", pcieSpeedStr(getFieldValue("link_speed_enabled"))));
            fields.push_back(AmberField("lane0_physical_position", getFieldStr("lane0_physical_position")));
            fields.push_back(AmberField("num_of_pfs", getFieldStr("num_of_pfs")));
            fields.push_back(AmberField("num_of_vfs", getFieldStr("num_of_vfs")));
            fields.push_back(AmberField("bdf0", getFieldStr("bdf0")));
            fields.push_back(AmberField("max_read_request_size",
                                        _mlxlinkMaps->_maxReadReqSize[getFieldValue("max_read_request_size")]));
            fields.push_back(AmberField("max_payload_size", _mlxlinkMaps->_maxReadReqSize[getFieldValue("max_payload_"
                                                                                                        "size")]));
            fields.push_back(AmberField("pwr_status", _mlxlinkMaps->_pwrStatus[getFieldValue("pwr_status")]));
            fields.push_back(AmberField("port_type", _mlxlinkMaps->_portType[getFieldValue("port_type")]));
            fields.push_back(
              AmberField("link_peer_max_speed", _mlxlinkMaps->_linkPeerMaxSpeed[getFieldValue("link_peer_max_speed")]));
            fields.push_back(AmberField("pci_power", getFieldStr("pci_power") + 'W'));
            fields.push_back(
              AmberField("device_status", getStrByMask(getFieldValue("device_status"), _mlxlinkMaps->_pcieDevStatus)));
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Phy Operation status: %s", exc.what());
    }

    return fields;
}

string MlxlinkAmBerCollector::getBerAndErrorTitle(u_int32_t portType)
{
    string title = "";
    if (portType)
    {
        title = "N/A";
    }
    return title;
}

void MlxlinkAmBerCollector::getPpcntBer(u_int32_t portType, vector<AmberField>& fields)
{
    resetLocalParser(ACCESS_REG_PPCNT);
    updateField("local_port", _localPort);
    if (portType != NETWORK_PORT_TYPE && !_isHca)
    {
        updateField("port_type", portType);
    }
    updateField("grp", PPCNT_STATISTICAL_GROUP);
    sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);

    string preTitle = getBerAndErrorTitle(portType);
    string berStr = to_string(getFieldValue("raw_ber_coef")) + "E-" + to_string(getFieldValue("raw_ber_magnitude"));
    string confLevelStr = preTitle + "Conf_Level_Raw_BER";
    if (portType == NETWORK_PORT_TYPE_MAIN_USR || portType == NETWORK_PORT_TYPE_TILE_USR)
    {
        confLevelStr = "Conf_Level_" + preTitle + "Raw_BER";
    }

    fields.push_back(AmberField(confLevelStr, getClRawBer()));
    fields.push_back(AmberField(preTitle + "Raw_BER", berStr));

    berStr =
      to_string(getFieldValue("effective_ber_coef")) + "E-" + to_string(getFieldValue("effective_ber_magnitude"));
    fields.push_back(AmberField(preTitle + "Effective_BER", berStr));

    if (_isPortETH && (portType == NETWORK_PORT_TYPE_NEAR || portType == NETWORK_PORT_TYPE_FAR))
    {
        string effErrorsStr = to_string(
          add32BitTo64(getFieldValue("phy_effective_errors_high"), getFieldValue("phy_effective_errors_low")));

        fields.push_back(AmberField(preTitle + "Effective_Errors", effErrorsStr));
    }

    if (portType != NETWORK_PORT_TYPE || (portType == NETWORK_PORT_TYPE && _isPortIB))
    {
        berStr =
          to_string(getFieldValue("symbol_fec_ber_coef")) + "E-" + to_string(getFieldValue("symbol_ber_magnitude"));
        fields.push_back(AmberField(preTitle + "Symbol_BER", berStr));

        if (portType != NETWORK_PORT_TYPE)
        {
            u_int64_t symErrors =
              add32BitTo64(getFieldValue("phy_symbol_errors_high"), getFieldValue("phy_symbol_errors_low"));
            fields.push_back(AmberField(preTitle + "Symbol_Errors", to_string(symErrors)));
        }
    }
}

vector<AmberField> MlxlinkAmBerCollector::getLinkStatus()
{
    vector<AmberField> fields;
    try
    {
        if (!_isPortPCIE)
        {
            // Getting link status fields for IB and ETH ports
            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);
            sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            fields.push_back(AmberField("Phy_Manager_State", _mlxlinkMaps->_pmFsmState[getFieldValue("phy_mngr_fsm_"
                                                                                                     "state")]));
            fields.push_back(AmberField("Protocol", _mlxlinkMaps->_networkProtocols[_protoActive]));

            resetLocalParser(ACCESS_REG_PTYS);
            updateField("local_port", _localPort);
            updateField("proto_mask", _protoActive);
            sendRegister(ACCESS_REG_PTYS, MACCESS_REG_METHOD_GET);

            float dataRate = ((float)getFieldValue("data_rate_oper")) * 0.1;
            char dataRateStr[64];
            sprintf(dataRateStr, "%.2f", dataRate);
            u_int32_t ethLinkActive = getFieldValue("ext_eth_proto_oper");
            fields.push_back(AmberField("Speed_[Gb/s]", string(dataRateStr)));
            fields.push_back(AmberField("Ethernet_Protocol_Active",
                                        ethLinkActive ? _mlxlinkMaps->_EthExtSpeed2Str[ethLinkActive] : "N/A",
                                        _isPortETH));

            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);
            sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            string linkSpeedActive = SupportedSpeeds2Str(IB, getFieldValue("link_speed_active"), true);
            fields.push_back(
              AmberField("Link_Speed_Active", linkSpeedActive.empty() ? "N/A" : linkSpeedActive, _isPortIB));
            fields.push_back(
              AmberField("Link_Width_Active", linkWidthMaskToStr(getFieldValue("link_width_active")), _isPortIB));
            fields.push_back(AmberField("Active_FEC", _mlxlinkMaps->_fecModeActive[getFieldValue("fec_mode_active")]));
        }
        else
        {
            // Getting link info for PCIE
            resetLocalParser(ACCESS_REG_MPEIN);
            updateField("depth", _depth);
            updateField("pcie_index", _pcieIndex);
            updateField("node", _node);
            sendRegister(ACCESS_REG_MPEIN, MACCESS_REG_METHOD_GET);
            fields.push_back(AmberField("pci_link_speed_active", pcieSpeedStr(getFieldValue("link_speed_active"))));
            fields.push_back(AmberField("pci_link_width_active", to_string(getFieldValue("link_width_active")) + "x"));
        }

        if (!_isPortPCIE)
        {
            resetLocalParser(ACCESS_REG_PPCNT);
            updateField("local_port", _localPort);
            updateField("grp", PPCNT_STATISTICAL_GROUP);
            sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
            float lastClear = (float)add32BitTo64(getFieldValue("time_since_last_clear_high"),
                                                  getFieldValue("time_since_last_clear_low")) /
                              60000.0;
            char timeFrmt[64];
            sprintf(timeFrmt, "%.1f", lastClear);
            fields.push_back(AmberField("Time_since_last_clear_[Min]", string(timeFrmt)));

            getPpcntBer(NETWORK_PORT_TYPE, fields);

            u_int32_t numOfBins = 0;
            bool skipBinLimit = false;
            try
            {
                resetLocalParser(ACCESS_REG_PPHCR);
                updateField("local_port", _localPort);
                genBuffSendRegister(ACCESS_REG_PPHCR, MACCESS_REG_METHOD_GET);
                numOfBins = getFieldValue("num_of_bins");
            }
            catch (...)
            {
                skipBinLimit = true;
            }

            // Getting histogram info for ETH and IB only
            resetLocalParser(ACCESS_REG_PPCNT);
            updateField("local_port", _localPort);
            updateField("grp", PPCNT_HISTOGRAM_GROUP);
            sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
            vector<string> histPerLane;
            u_int64_t histBin = 0;
            string val = "";
            int firstZeroHist = -1;
            for (u_int32_t idx = 0; idx < NUM_OF_BINS; idx++)
            {
                val = "N/A";
                if (idx < numOfBins || (skipBinLimit || !numOfBins))
                {
                    histBin = add32BitTo64(getFieldValue("hist[" + to_string(idx) + "]_hi"),
                                           getFieldValue("hist[" + to_string(idx) + "]_lo"));
                    val = to_string(histBin);
                    if (!histBin && firstZeroHist < 0)
                    {
                        firstZeroHist = idx;
                    }
                }
                histPerLane.push_back(val);
            }
            fields.push_back(AmberField("FC_Zero_Hist", firstZeroHist >= 0 ? to_string(firstZeroHist) : "N/A"));
            fields.push_back(AmberField("Number_of_histogram_bins", to_string(numOfBins)));
            for (u_int32_t idx = 0; idx < NUM_OF_BINS; idx++)
            {
                fields.push_back(AmberField("hist" + to_string(idx), histPerLane[idx]));
            }
            // Getting raw errors per lane for ETH and IB only
            resetLocalParser(ACCESS_REG_PPCNT);
            updateField("local_port", _localPort);
            updateField("grp", PPCNT_STATISTICAL_GROUP);
            sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
            u_int64_t rawError = 0;
            for (u_int32_t lane = 0; lane < MAX_NETWORK_LANES; lane++)
            {
                val = "N/A";
                if (lane < _numOfLanes)
                {
                    rawError = add32BitTo64(getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_high"),
                                            getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_low"));
                    val = to_string(rawError);
                }
                fields.push_back(AmberField("Raw_Errors_lane" + to_string(lane), val));
            }
            resetLocalParser(ACCESS_REG_PPCNT);
            updateField("local_port", _localPort);
            updateField("grp", PPCNT_STATISTICAL_GROUP);
            sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);

            string effErrorsStr = to_string(
              add32BitTo64(getFieldValue("phy_effective_errors_high"), getFieldValue("phy_effective_errors_low")));
            fields.push_back(AmberField("Effective_Errors", effErrorsStr));
            u_int64_t symErrors =
              add32BitTo64(getFieldValue("phy_symbol_errors_high"), getFieldValue("phy_symbol_errors_low"));
            fields.push_back(AmberField("Symbol_Errors", to_string(symErrors)));
        }
        else
        {
            // Getting link errors info for PCIE
            resetLocalParser(ACCESS_REG_MPCNT);
            updateField("depth", _depth);
            updateField("pcie_index", _pcieIndex);
            updateField("node", _node);
            updateField("grp", MPCNT_PERFORMANCE_GROUP);
            sendRegister(ACCESS_REG_MPCNT, MACCESS_REG_METHOD_GET);
            string berStr = to_string(getFieldValue("effective_ber_coef")) + "E-" +
                            to_string(getFieldValue("effective_ber_magnitude"));
            fields.push_back(AmberField("effective_ber_pci", berStr));
            fields.push_back(AmberField("Rx_error_pci", to_string(getFieldValue("rx_errors"))));
            fields.push_back(AmberField("Tx_error_pci", to_string(getFieldValue("tx_errors"))));
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Link Status information: %s", exc.what());
    }

    return fields;
}

void MlxlinkAmBerCollector::fillParamsToFields(const string& title,
                                               const vector<string>& values,
                                               vector<AmberField>& fields)
{
    string val = "";
    string fieldName = "";
    for (u_int32_t idx = 0; idx < values.size(); idx++)
    {
        val = "N/A";
        if (((_numOfLanes - 1) < values.size()) && (idx < _numOfLanes))
        {
            val = values[idx];
        }
        fieldName = "Lane" + to_string(idx) + "_" + title;
        fields.push_back(AmberField(fieldName, val));
    }
}

vector<AmberField> MlxlinkAmBerCollector::getSerdesHDR()
{
    vector<AmberField> fields;

    try
    {
        if (!_isPortPCIE)
        {
            vector<vector<string>> slrgParams(SLRG_PARAMS_LAST, vector<string>(_maxLanes, ""));
            vector<vector<string>> sltpParams(SLTP_HDR_LAST, vector<string>(_maxLanes, ""));
            vector<string> sltpStatus;
            u_int32_t lane = 0;
            // Getting 16nm SLRG information for all lanes
            for (; lane < _maxLanes; lane++)
            {
                resetLocalParser(ACCESS_REG_SLRG);
                updateField("local_port", _localPort);
                updateField("lane", lane);
                sendRegister(ACCESS_REG_SLRG, MACCESS_REG_METHOD_GET);

                slrgParams[SLRG_PARAMS_INITIAL_FOM][lane] = getFieldStr("grade");
                slrgParams[SLRG_PARAMS_UPPER_EYE][lane] = getFieldStr("up_eye_grade");
                slrgParams[SLRG_PARAMS_MID_EYE][lane] = getFieldStr("mid_eye_grade");
                slrgParams[SLRG_PARAMS_LOWER_EYE][lane] = getFieldStr("dn_eye_grade");
            }

            fillParamsToFields("Grade", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);
            fillParamsToFields("up_eye_grade", slrgParams[SLRG_PARAMS_UPPER_EYE], fields);
            fillParamsToFields("mid_eye_grade", slrgParams[SLRG_PARAMS_MID_EYE], fields);
            fillParamsToFields("low_eye_grade", slrgParams[SLRG_PARAMS_LOWER_EYE], fields);

            // Getting 16nm SLTP information for all lanes
            for (u_int32_t lane = 0; lane < _maxLanes; lane++)
            {
                resetLocalParser(ACCESS_REG_SLTP);
                updateField("local_port", _localPort);
                updateField("lane", lane);
                sendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_GET);

                sltpParams[SLTP_HDR_PRE_2_TAP][lane] = getFieldStr("pre_2_tap");
                sltpParams[SLTP_HDR_PRE_TAP][lane] = getFieldStr("pre_tap");
                sltpParams[SLTP_HDR_MAIN_TAP][lane] = getFieldStr("main_tap");
                sltpParams[SLTP_HDR_POST_TAP][lane] = getFieldStr("post_tap");
                sltpParams[SLTP_HDR_OB_M2LP][lane] = getFieldStr("ob_m2lp");
                sltpParams[SLTP_HDR_OB_AMP][lane] = getFieldStr("ob_amp");
                sltpParams[SLTP_HDR_OB_ALEV_OUT][lane] = getFieldStr("ob_alev_out");
                sltpStatus.push_back(getFieldValue("status") ? "Valid" : "Invalid");
            }

            fillParamsToFields("tx_status", sltpStatus, fields);
            fillParamsToFields("pre_2_tap", sltpParams[SLTP_HDR_PRE_2_TAP], fields);
            fillParamsToFields("pre_tap", sltpParams[SLTP_HDR_PRE_TAP], fields);
            fillParamsToFields("main_tap", sltpParams[SLTP_HDR_MAIN_TAP], fields);
            fillParamsToFields("post_tap", sltpParams[SLTP_HDR_POST_TAP], fields);
            fillParamsToFields("ob_m2lp", sltpParams[SLTP_HDR_OB_M2LP], fields);
            fillParamsToFields("ob_amp", sltpParams[SLTP_HDR_OB_AMP], fields);
            fillParamsToFields("ob_alev_out", sltpParams[SLTP_HDR_OB_ALEV_OUT], fields);
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get SerDes[16nm] information: %s", exc.what());
    }

    return fields;
}

u_int32_t MlxlinkAmBerCollector::getFomMeasurement()
{
    u_int32_t fomMeasurement = SLRG_EOM_NONE;
    if (!_isPortPCIE)
    {
        fomMeasurement = SLRG_EOM_COMPOSITE;
        if (!isSpeed25GPerLane(_activeSpeed, _protoActive))
        {
            fomMeasurement |= (SLRG_EOM_UPPER | SLRG_EOM_MIDDLE | SLRG_EOM_LOWER);
        }
    }
    else
    {
        for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
        {
            resetParser(ACCESS_REG_SLRG);
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_PCIE);
            updateField("lane", lane);
            updateField("fom_measurment", SLRG_EOM_COMPOSITE);
            genBuffSendRegister(ACCESS_REG_SLRG, MACCESS_REG_METHOD_GET);
        }
        u_int32_t it = 0;
        while (it < SLRG_PCIE_7NM_TIMEOUT)
        {
            resetParser(ACCESS_REG_SLRG);
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_PCIE);
            genBuffSendRegister(ACCESS_REG_SLRG, MACCESS_REG_METHOD_GET);
            if (getFieldValue("status"))
            {
                break;
            }
            it++;
            msleep(SLRG_PCIE_7NM_SLEEP);
        }
    }
    return fomMeasurement;
}

vector<AmberField> MlxlinkAmBerCollector::getSerdesNDR()
{
    vector<AmberField> fields;

    try
    {
        fields.push_back(AmberField("UPHY_version", "N/A"));
        fields.push_back(AmberField("BKV_version", "N/A"));

        vector<vector<string>> slrgParams(SLRG_PARAMS_LAST, vector<string>(_maxLanes, ""));
        vector<vector<string>> sltpParams(SLTP_NDR_LAST + 1, vector<string>(_maxLanes, ""));
        u_int32_t fomMeasurement = getFomMeasurement();
        u_int32_t lane = 0;

        // Getting 7nm SLRG information for all lanes
        for (; lane < _numOfLanes; lane++)
        {
            resetLocalParser(ACCESS_REG_SLRG);
            updateField("local_port", _localPort);
            updateField("lane", lane);
            updateField("pnat", _pnat);
            updateField("fom_measurment", fomMeasurement);
            sendRegister(ACCESS_REG_SLRG, MACCESS_REG_METHOD_GET);

            slrgParams[SLRG_PARAMS_INITIAL_FOM][lane] = getFieldStr("initial_fom");
            slrgParams[SLRG_PARAMS_FOM_MODE][lane] = getFieldStr("fom_mode");
            slrgParams[SLRG_PARAMS_UPPER_EYE][lane] = getFieldStr("upper_eye");
            slrgParams[SLRG_PARAMS_MID_EYE][lane] = getFieldStr("mid_eye");
            slrgParams[SLRG_PARAMS_LOWER_EYE][lane] = getFieldStr("lower_eye");
            slrgParams[SLRG_PARAMS_LAST_FOM][lane] = getFieldStr("last_fom");
        }
        fillParamsToFields("initial_fom", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);

        if (!_isPortPCIE)
        {
            fillParamsToFields("fom_mode", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);
            fillParamsToFields("upper_eye", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);
            fillParamsToFields("mid_eye", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);
            fillParamsToFields("lower_eye", slrgParams[SLRG_PARAMS_INITIAL_FOM], fields);
        }
        fillParamsToFields("composite_eye", slrgParams[SLRG_PARAMS_LAST_FOM], fields);

        if (!_isPortPCIE)
        {
            // Getting 7nm SLTP information for all lanes
            for (lane = 0; lane < _numOfLanes; lane++)
            {
                resetLocalParser(ACCESS_REG_SLTP);
                updateField("local_port", _localPort);
                updateField("lane", lane);
                updateField("pnat", _pnat);
                sendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_GET);

                sltpParams[SLTP_NDR_FIR_PRE3][lane] = getFieldStr("fir_pre3");
                sltpParams[SLTP_NDR_FIR_PRE2][lane] = getFieldStr("fir_pre2");
                sltpParams[SLTP_NDR_FIR_PRE1][lane] = getFieldStr("fir_pre1");
                sltpParams[SLTP_NDR_FIR_MAIN][lane] = getFieldStr("fir_main");
                sltpParams[SLTP_NDR_FIR_POST1][lane] = getFieldStr("fir_post1");
            }
            fillParamsToFields("pre_3_tap", sltpParams[SLTP_NDR_FIR_PRE3], fields);
            fillParamsToFields("pre_2_tap", sltpParams[SLTP_NDR_FIR_PRE2], fields);
            fillParamsToFields("pre_1_tap", sltpParams[SLTP_NDR_FIR_PRE1], fields);
            fillParamsToFields("main_tap", sltpParams[SLTP_NDR_FIR_MAIN], fields);
            fillParamsToFields("post_1_tap", sltpParams[SLTP_NDR_FIR_POST1], fields);
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get SerDes[7nm] information: %s", exc.what());
    }

    return fields;
}

void MlxlinkAmBerCollector::initCableIdentifier(u_int32_t cableIdentifier)
{
    switch (cableIdentifier)
    {
        case IDENTIFIER_QSFP28:
        case IDENTIFIER_QSFP_PLUS:
            _isQsfpCable = true;
            break;
        case IDENTIFIER_SFP:
        case IDENTIFIER_QSA:
            _isSfpCable = true;
            break;
        case IDENTIFIER_SFP_DD:
        case IDENTIFIER_QSFP_DD:
        case IDENTIFIER_OSFP:
        case IDENTIFIER_DSFP:
        case IDENTIFIER_QSFP_CMIS:
            _isCmisCable = true;
            break;
    }
}

void MlxlinkAmBerCollector::getCmisComplianceCode(u_int32_t ethComplianceCode,
                                                  u_int32_t extEthComplianceCode,
                                                  string& ethComplianceStr,
                                                  string& extComplianceStr,
                                                  u_int32_t cableMediaType,
                                                  u_int32_t cableTechnology)
{
    switch (cableMediaType)
    {
        case UNIDENTIFIED:
        case UNPLUGGED:
        default:
            ethComplianceStr = "N/A";
            extComplianceStr = "N/A";
            break;

        case ACTIVE:
            ethComplianceStr = _mlxlinkMaps->_activeCableCompliance[ethComplianceCode];
            ethComplianceStr = ethComplianceStr.empty() ? "N/A" : ethComplianceStr;
            extComplianceStr = _mlxlinkMaps->_cmisHostCompliance[extEthComplianceCode];
            break;

        case OPTICAL_MODULE:
            if (cableTechnology == TECHNOLOGY_850NM_VCSEL)
            {
                ethComplianceStr = _mlxlinkMaps->_mmfCompliance[ethComplianceCode];
            }
            else if (cableTechnology >= TECHNOLOGY_1310NM_VCSEL && cableTechnology <= TECHNOLOGY_1550NM_EML)
            {
                ethComplianceStr = _mlxlinkMaps->_smfCompliance[ethComplianceCode];
            }

            extComplianceStr = _mlxlinkMaps->_cmisHostCompliance[extEthComplianceCode];
            break;

        case PASSIVE:
            ethComplianceStr = "N/A";
            extComplianceStr = _mlxlinkMaps->_cmisHostCompliance[extEthComplianceCode];
            break;
    }
}

void MlxlinkAmBerCollector::getEthComplianceCodes(u_int32_t cableTechnology,
                                                  string& ethComplianceStr,
                                                  string& extComplianceStr,
                                                  u_int32_t cableMediaType)
{
    u_int32_t ethComplianceCode = getFieldValue("ethernet_compliance_code");
    u_int32_t extEthComplianceCode = getFieldValue("ext_ethernet_compliance_code");

    if (_isQsfpCable)
    {
        ethComplianceStr =
          ethComplianceCode ? getCompliance(ethComplianceCode, _mlxlinkMaps->_cableComplianceQsfp, true) : "N/A";
        extComplianceStr = (extEthComplianceCode & QSFP_ETHERNET_COMPLIANCE_CODE_EXT) ?
                             _mlxlinkMaps->_cableComplianceExt[extEthComplianceCode] :
                             "N/A";
    }
    if (_isSfpCable)
    {
        ethComplianceStr =
          ethComplianceCode ? getCompliance(ethComplianceCode, _mlxlinkMaps->_cableComplianceSfp, true) : "N/A";
        extComplianceStr = extEthComplianceCode ? _mlxlinkMaps->_cableComplianceExt[extEthComplianceCode] : "N/A";
    }
    if (_isCmisCable)
    {
        getCmisComplianceCode(ethComplianceCode, extEthComplianceCode, ethComplianceStr, extComplianceStr,
                              cableMediaType, cableTechnology);
    }
}

void MlxlinkAmBerCollector::getIbComplianceCodes(string& ibComplianceCodeStr)
{
    u_int32_t ibComplianceCode = getFieldValue("ib_compliance_code");
    ibComplianceCodeStr =
      ibComplianceCode ? getCompliance(ibComplianceCode, _mlxlinkMaps->_cableComplianceCmisIb, true) : "N/A";
}

string MlxlinkAmBerCollector::getCableTechnologyStr(u_int32_t cableTechnology)
{
    string technologyStr = "N/A";
    if (_isCmisCable)
    {
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[cableTechnology];
    }
    else if (_isQsfpCable)
    {
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[(cableTechnology & 240) >> 4];
    }
    else
    {
        technologyStr = _mlxlinkMaps->_cableTechnologySfp[(cableTechnology & 15)];
    }
    return technologyStr;
}

string MlxlinkAmBerCollector::getCableBreakoutStr(u_int32_t cableBreakout, u_int32_t cableIdentifier)
{
    string cableBreakoutStr = "";
    string impCh = "";
    string notImpCh = "";

    if (_isCmisCable)
    {
        cableBreakoutStr = _mlxlinkMaps->_cimsCableBreakout[cableBreakout];
        findAndReplace(cableBreakoutStr, "X", getCableIdentifier(cableIdentifier));
    }
    else if (_isQsfpCable)
    {
        u_int32_t near_end_bits = cableBreakout & 0xF;
        u_int32_t far_end_bits = (cableBreakout >> 4) & 0xF;

        for (u_int32_t channel = 1; channel < QSFP_CHANNELS + 1; channel++)
        {
            if (getBitvalue(near_end_bits, channel))
            {
                notImpCh += to_string(channel) + "_";
            }
            else
            {
                impCh += to_string(channel) + "_";
            }
        }
        impCh = deleteLastChar(impCh);
        notImpCh = deleteLastChar(notImpCh);

        if (!impCh.empty())
        {
            cableBreakoutStr = "Channels implemented [" + impCh + "]";
        }
        if (!notImpCh.empty())
        {
            cableBreakoutStr += ",Channels not implemented [" + notImpCh + "]";
        }

        cableBreakoutStr += '/' + _mlxlinkMaps->_qsfpFarEndCableBreakout[far_end_bits];
    }
    else
    {
        cableBreakoutStr = "N/A";
    }

    return cableBreakoutStr;
}

void MlxlinkAmBerCollector::pushModulePerLaneField(vector<AmberField>& fields,
                                                   string fieldName,
                                                   float valueCorrection,
                                                   string laneSep)
{
    float value = 0;
    u_int32_t lanes = MAX_NETWORK_LANES;

    if (_isPortIB)
    {
        lanes = MAX_IB_LANES;
    }

    for (u_int32_t lane = 0; lane < lanes; lane++)
    {
        value = getLocalFieldValue(fieldName + to_string(lane));
        if (fieldName.find("power") != string::npos)
        {
            value = getPower(value);
        }
        fields.push_back(AmberField(fieldName + laneSep + to_string(lane), to_string(value / valueCorrection)));
    }
}

void MlxlinkAmBerCollector::pushModuleDpPerLane(vector<AmberField>& fields, const string str)
{
    string dpStateStr = "N/A";
    string fieldName = str;

    fieldName = toLowerCase(fieldName);

    for (u_int32_t lane = 0; lane < MAX_NETWORK_LANES; lane++)
    {
        string laneStr = to_string(lane);
        dpStateStr = getStrByMask(getLocalFieldValue(fieldName + laneStr), _mlxlinkMaps->_dataPathSt);
        fields.push_back(AmberField(str + laneStr, dpStateStr));
        dpStateStr = "N/A";
    }
}

string
  MlxlinkAmBerCollector::getSmfLength(const u_int32_t smfLength, const u_int32_t cableTechnology, const bool optical)
{
    string lengthStr = "N/A";

    if (cableTechnology >= TECHNOLOGY_1310NM_VCSEL && cableTechnology <= TECHNOLOGY_1550NM_EML && optical)
    {
        bool lengthBasedOn100m = getBitvalue(smfLength, 9);

        u_int32_t length = smfLength & 0XFF;

        if (lengthBasedOn100m)
        {
            length *= 100;
            lengthStr = to_string(length) + "m";
        }
        else
        {
            lengthStr = to_string(length) + "km";
        }
    }

    return lengthStr;
}

string MlxlinkAmBerCollector::getDateCode(u_int64_t dateCode)
{
    string dateCodeStr;
    u_int64_t dateCodeRev = 0;
    u_int64_t tmpDateCode = dateCode;

    while (tmpDateCode)
    {
        dateCodeRev = (dateCodeRev << 16) | (tmpDateCode & 0xffff);
        tmpDateCode = tmpDateCode >> 16;
    }

    if (dateCodeRev)
    {
        for (int i = 56; i > -1; i -= 8)
        {
            char ch = (char)(dateCodeRev >> i);
            if (ch)
            {
                dateCodeStr.push_back(ch);
                if (i % 16 == 0)
                {
                    dateCodeStr.push_back('_');
                }
            }
        }

        dateCodeStr = deleteLastChar(dateCodeStr);
        MlxlinkRecord::trim(dateCodeStr);
        MlxlinkRecord::trim(dateCodeStr, "_");
    }
    else
    {
        dateCodeStr = "N/A";
    }

    return dateCodeStr;
}

void MlxlinkAmBerCollector::getModuleInfoPage(vector<AmberField>& fields)
{
    u_int32_t cableIdentifier = getFieldValue("cable_identifier");
    u_int32_t ibWidth = getFieldValue("ib_width");
    u_int32_t cableTechnology = getFieldValue("cable_technology");
    u_int32_t cableBreakout = getFieldValue("cable_breakout");
    u_int32_t cableMediaType = getFieldValue("cable_type");
    u_int32_t vendorOUI = getFieldValue("vendor_oui");

    bool passive = cableMediaType == PASSIVE;
    bool optical = cableMediaType == OPTICAL_MODULE;
    string ethComplianceStr = "N/A";
    string extComplianceStr = "N/A";
    string ibComplianceCodeStr = "N/A";
    string ibWidthStr = linkWidthMaskToStr(ibWidth);
    string moduleSt = "N/A";
    string activeSetHostComplianceCode = "N/A";
    string activeSetMediaComplianceCode = "N/A";
    string nbrString = "N/A";
    string error_code_res = "N/A";
    char vendorOUIStr[32];
    sprintf(vendorOUIStr, "0x%X", vendorOUI);

    initCableIdentifier(cableIdentifier);
    if (_isPortETH || _isCmisCable)
    {
        getEthComplianceCodes(cableTechnology, ethComplianceStr, extComplianceStr, cableMediaType);
    }
    if (_isPortIB)
    {
        getIbComplianceCodes(ibComplianceCodeStr);
    }

    fields.push_back(AmberField("ethernet_compliance_code", ethComplianceStr, _isPortETH));
    fields.push_back(AmberField("ext_ethernet_compliance_code", extComplianceStr, _isPortETH));
    fields.push_back(AmberField("ib_compliance_code", ibComplianceCodeStr, _isPortIB));
    fields.push_back(AmberField("ib_width", ibWidthStr, _isPortIB));
    fields.push_back(AmberField("Memory_map_rev", getFieldStr("memory_map_rev")));
    fields.push_back(AmberField("Vendor_OUI", string(vendorOUIStr)));
    fields.push_back(AmberField("Cable_PN", getAscii("vendor_pn", 16)));
    fields.push_back(AmberField("Cable_SN", getAscii("vendor_sn", 16)));
    fields.push_back(AmberField("cable_technology", getCableTechnologyStr(cableTechnology)));
    fields.push_back(AmberField("linear_direct_drive", getFieldStr("did_cap")));
    fields.push_back(AmberField("cable_breakout", getCableBreakoutStr(cableBreakout, cableIdentifier)));
    fields.push_back(AmberField("cable_type", getCableType(getFieldValue("cable_type"))));
    fields.push_back(AmberField("cable_vendor", getOui(getFieldValue("cable_vendor"))));
    fields.push_back(AmberField("cable_length", getCableLengthStr(getFieldValue("cable_length"), _isCmisCable) + 'm'));
    fields.push_back(AmberField("smf_length", getSmfLength(getFieldValue("smf_length"), cableTechnology, optical)));
    fields.push_back(AmberField("cable_identifier", getCableIdentifier(getFieldValue("cable_identifier"))));
    fields.push_back(AmberField(
      "cable_power_class",
      getPowerClass(_mlxlinkMaps, cableIdentifier, getFieldValue("cable_power_class"), getFieldValue("max_power"))));
    fields.push_back(AmberField("max_power", getFieldStr("max_power")));
    fields.push_back(AmberField("cable_rx_amp", passive ? "N/A" : getFieldStr("cable_rx_amp")));
    fields.push_back(AmberField("cable_rx_pre_emphasis", passive ? "N/A" : getFieldStr("cable_rx_emphasis")));
    fields.push_back(AmberField("cable_rx_post_emphasis", passive ? "N/A" : getFieldStr("cable_rx_post_emphasis")));
    fields.push_back(AmberField("cable_tx_equalization", passive ? "N/A" : getFieldStr("cable_tx_equalization")));
    fields.push_back(AmberField("cable_attenuation_25g", getFieldStr("cable_attenuation_25g")));
    fields.push_back(AmberField("cable_attenuation_12g", getFieldStr("cable_attenuation_12g")));
    fields.push_back(AmberField("cable_attenuation_7g", getFieldStr("cable_attenuation_7g")));
    fields.push_back(AmberField("cable_attenuation_5g", getFieldStr("cable_attenuation_5g")));
    fields.push_back(
      AmberField("tx_input_freq_sync", getStrByValue(getFieldValue("tx_input_freq_sync"), _mlxlinkMaps->_txInputFreq)));
    fields.push_back(AmberField("rx_cdr_cap", _mlxlinkMaps->_rxTxCdrCap[getFieldValue("rx_cdr_cap")]));
    fields.push_back(AmberField("tx_cdr_cap", _mlxlinkMaps->_rxTxCdrCap[getFieldValue("tx_cdr_cap")]));
    fields.push_back(AmberField("rx_cdr_state", getRxTxCDRState(getFieldValue("rx_cdr_state"), _maxLanes)));
    fields.push_back(AmberField("tx_cdr_state", getRxTxCDRState(getFieldValue("tx_cdr_state"), _maxLanes)));
    fields.push_back(AmberField("vendor_name", getAscii("vendor_name", 16)));
    fields.push_back(AmberField("vendor_rev", getVendorRev(getFieldValue("vendor_rev"))));
    fields.push_back(AmberField("module_fw_version", getModuleFwVersion(passive, getFieldValue("fw_version"))));

    pushModulePerLaneField(fields, "rx_power_lane");
    pushModulePerLaneField(fields, "tx_power_lane");
    pushModulePerLaneField(fields, "tx_bias_lane", 500.0);

    fields.push_back(AmberField("temperature_high_th", getTemp(getFieldValue("temperature_high_th"))));
    fields.push_back(AmberField("temperature_low_th", getTemp(getFieldValue("temperature_low_th"))));
    fields.push_back(AmberField("voltage_high_th", to_string(getFieldValue("voltage_high_th") / 10.0)));
    fields.push_back(AmberField("voltage_low_th", to_string(getFieldValue("voltage_low_th") / 10.0)));
    fields.push_back(AmberField("rx_power_high_th", to_string(getPower(getFieldValue("rx_power_high_th")))));
    fields.push_back(AmberField("rx_power_low_th", to_string(getPower(getFieldValue("rx_power_low_th")))));
    fields.push_back(AmberField("tx_power_high_th", to_string(getPower(getFieldValue("tx_power_high_th")))));
    fields.push_back(AmberField("tx_power_low_th", to_string(getPower(getFieldValue("tx_power_low_th")))));
    fields.push_back(AmberField("tx_bias_high_th", to_string(getFieldValue("tx_bias_high_th") / 500.0)));
    fields.push_back(AmberField("tx_bias_low_th", to_string(getFieldValue("tx_bias_low_th") / 500.0)));
    fields.push_back(AmberField("wavelength", getFieldStr("wavelength")));

    float waveLenTol = float(getFieldValue("wavelength_tolerance")) / 200.0;
    char waveLenTolCh[64];
    sprintf(waveLenTolCh, "%.1f", waveLenTol);
    string waveLenTolStr = waveLenTolCh;

    fields.push_back(AmberField("wavelength_tolerance", passive ? "N/A" : waveLenTolStr + "nm"));

    if (_isCmisCable)
    {
        moduleSt = _mlxlinkMaps->_cimsModuleSt[getFieldValue("module_st")];
    }

    fields.push_back(AmberField("Module_st", moduleSt));

    pushModuleDpPerLane(fields, "Dp_st_lane");

    fields.push_back(AmberField("rx_output_valid", getBitmaskPerLaneStr(getFieldValue("rx_output_valid"))));

    if (cableIdentifier < IDENTIFIER_SFP_DD)
    {
        float nbr = float(getFieldValue("nbr250") * 250) / float(1000);
        char nbrCh[64];
        sprintf(nbrCh, "%.3f", nbr);
        nbrString = nbrCh + string("Gb/s");
    }
    fields.push_back(AmberField("Nominal_Bit_Rate", nbrString));

    fields.push_back(AmberField("Rx_Power_Type", _mlxlinkMaps->_rxPowerType[getFieldValue("rx_power_type")]));
    fields.push_back(
      AmberField("Date_Code", getDateCode(add32BitTo64(getFieldValue("date_code_hi"), getFieldValue("date_code_lo")))));
    fields.push_back(AmberField("Module_Temperature", getTemp(getFieldValue("temperature"))));
    fields.push_back(AmberField("Module_Voltage", to_string(getFieldValue("voltage") / 10.0)));

    if (_isCmisCable)
    {
        activeSetHostComplianceCode = extComplianceStr;
        activeSetMediaComplianceCode = ethComplianceStr;
    }
    fields.push_back(AmberField("Active_set_host_compliance_code", activeSetHostComplianceCode));
    fields.push_back(AmberField("Active_set_media_compliance_code", activeSetMediaComplianceCode));

    if (_isCmisCable)
    {
        error_code_res = getStrByValue(getFieldValue("error_code"), _mlxlinkMaps->_errorCodeRes);
    }
    fields.push_back(AmberField("error_code_response", error_code_res));
}

string MlxlinkAmBerCollector::getBitmaskPerLaneStr(u_int32_t bitmask)
{
    string bitMaskStr = "";
    for (u_int32_t lane = 0; lane < MAX_NETWORK_LANES; lane++)
    {
        bitMaskStr += getBitvalue(bitmask, lane + 1) ? "1" : "0";
        if (lane != 7)
        {
            bitMaskStr += ",";
        }
    }

    return bitMaskStr;
}

void MlxlinkAmBerCollector::getModuleLatchedFlagInfoPage(vector<AmberField>& fields)
{
    string modFwFault = "N/A";
    string dpFwFault = "N/A";
    string txLoss = "N/A";
    string txAdEqFault = "N/A";
    if (_isCmisCable)
    {
        modFwFault = getFieldStr("mod_fw_fault");
        dpFwFault = getFieldStr("dp_fw_fault");
    }

    fields.push_back(AmberField("Temp_flags", getStrByMask(getFieldValue("temp_flags"), _mlxlinkMaps->_tempFlags)));
    fields.push_back(AmberField("Vcc_flags", getStrByMask(getFieldValue("vcc_flags"), _mlxlinkMaps->_vccFlags)));
    fields.push_back(AmberField("Mod_fw_fault", modFwFault));
    fields.push_back(AmberField("Dp_fw_fault", dpFwFault));
    fields.push_back(AmberField("tx_fault", getBitmaskPerLaneStr(getFieldValue("tx_fault"))));
    if (!_isSfpCable)
    {
        txLoss = getBitmaskPerLaneStr(getFieldValue("tx_los"));
    }
    fields.push_back(AmberField("tx_los", txLoss));
    fields.push_back(AmberField("tx_cdr_lol", getBitmaskPerLaneStr(getFieldValue("tx_cdr_lol"))));
    if (!_isSfpCable)
    {
        txAdEqFault = getBitmaskPerLaneStr(getFieldValue("tx_ad_eq_fault"));
    }
    fields.push_back(AmberField("tx_ad_eq_fault", txAdEqFault));
    fields.push_back(AmberField("tx_power_hi_al", getBitmaskPerLaneStr(getFieldValue("tx_power_hi_al"))));
    fields.push_back(AmberField("tx_power_lo_al", getBitmaskPerLaneStr(getFieldValue("tx_power_lo_al"))));
    fields.push_back(AmberField("tx_power_hi_war", getBitmaskPerLaneStr(getFieldValue("tx_power_hi_war"))));
    fields.push_back(AmberField("tx_power_lo_war", getBitmaskPerLaneStr(getFieldValue("tx_power_lo_war"))));
    fields.push_back(AmberField("tx_bias_hi_al", getBitmaskPerLaneStr(getFieldValue("tx_bias_hi_al"))));
    fields.push_back(AmberField("tx_bias_lo_al", getBitmaskPerLaneStr(getFieldValue("tx_bias_lo_al"))));
    fields.push_back(AmberField("tx_bias_hi_war", getBitmaskPerLaneStr(getFieldValue("tx_bias_hi_war"))));
    fields.push_back(AmberField("tx_bias_lo_war", getBitmaskPerLaneStr(getFieldValue("tx_bias_lo_war"))));
    fields.push_back(AmberField("rx_los", getBitmaskPerLaneStr(getFieldValue("rx_los"))));
    fields.push_back(AmberField("rx_cdr_lol", getBitmaskPerLaneStr(getFieldValue("rx_cdr_lol"))));
    fields.push_back(AmberField("rx_power_hi_al", getBitmaskPerLaneStr(getFieldValue("rx_power_hi_al"))));
    fields.push_back(AmberField("rx_power_lo_al", getBitmaskPerLaneStr(getFieldValue("rx_power_lo_al"))));
    fields.push_back(AmberField("rx_power_hi_war", getBitmaskPerLaneStr(getFieldValue("rx_power_hi_war"))));
    fields.push_back(AmberField("rx_power_lo_war", getBitmaskPerLaneStr(getFieldValue("rx_power_lo_war"))));
}

vector<AmberField> MlxlinkAmBerCollector::getModuleStatus()
{
    vector<AmberField> fields;

    try
    {
        if (!_isPortPCIE)
        {
            resetLocalParser(ACCESS_REG_PMAOS);
            updateField("module", _moduleIndex);
            updateField("slot_index", _slotIndex);
            sendRegister(ACCESS_REG_PMAOS, MACCESS_REG_METHOD_GET);

            u_int32_t operSt = getFieldValue("oper_status");
            string operStStr = getStrByValue(operSt, _mlxlinkMaps->_moduleOperSt);
            string errTypeStr = "N/A";
            if (operSt == MODULE_OPER_STATUS_PLUGGED_WITH_ERROR)
            {
                errTypeStr = getStrByValue(getFieldValue("error_type"), _mlxlinkMaps->_moduleErrType);
            }

            fields.push_back(AmberField("module_oper_status", operStStr));
            fields.push_back(AmberField("module_error_type", errTypeStr));

            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("page_select", PDDR_MODULE_INFO_PAGE);
            sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            if (!_cablePlugged)
            {
                AmberField::_dataValid = false;
            }
            getModuleInfoPage(fields);

            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("page_select", PDDR_MODULE_LATCHED_FLAG_INFO_PAGE);
            sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            if (!_cablePlugged)
            {
                AmberField::_dataValid = false;
            }
            getModuleLatchedFlagInfoPage(fields);
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Module status: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getPortCounters()
{
    vector<AmberField> fields;
    try
    {
        // Getting counters for ETH and IB ports
        if (!_isPortPCIE)
        {
            // Getting IB link errors
            if (_isPortIB)
            {
                resetLocalParser(ACCESS_REG_PPCNT);
                updateField("local_port", _localPort);
                updateField("grp", PPCNT_IB_PORT_COUNTERS_GROUP);
                sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
                fields.push_back(AmberField("LinkErrorRecoveryCounter", getFieldStr("link_error_recovery_counter")));
                fields.push_back(AmberField("PortRcvRemotePhysicalErrors", getFieldStr("port_rcv_remote_physical_"
                                                                                       "errors")));
                fields.push_back(AmberField("PortRcvErrors", getFieldStr("port_rcv_errors")));
                fields.push_back(AmberField("PortXmitDiscards", getFieldStr("port_xmit_discards")));
                fields.push_back(AmberField("PortRcvSwitchRelayErrors", getFieldStr("port_rcv_switch_relay_errors")));
                fields.push_back(AmberField("ExcessiveBufferOverrunErrors", getFieldStr("excessive_buffer_overrun_"
                                                                                        "errors")));
                fields.push_back(AmberField("LocalLinkIntegrityErrors", getFieldStr("local_link_integrity_errors")));
                fields.push_back(AmberField("PortRcvConstraintErrors", getFieldStr("port_rcv_constraint_errors")));
                fields.push_back(AmberField("PortXmitConstraintErrors", getFieldStr("port_xmit_constraint_errors")));
                fields.push_back(AmberField("VL15Dropped", getFieldStr("vl_15_dropped")));
                fields.push_back(AmberField("PortXmitData", getFieldStr("port_xmit_data")));
                fields.push_back(AmberField("PortRcvData", getFieldStr("port_rcv_data")));
                fields.push_back(AmberField("PortXmitPkts", getFieldStr("port_xmit_pkts")));
                fields.push_back(AmberField("PortRcvPkts", getFieldStr("port_rcv_pkts")));
                fields.push_back(AmberField("PortXmitWait", getFieldStr("port_xmit_wait")));
                // Getting port extended counters info
                resetLocalParser(ACCESS_REG_PPCNT);
                updateField("local_port", _localPort);
                updateField("grp", PPCNT_EXT_IB_PORT_COUNTERS_GROUP);
                sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);

                fields.push_back(AmberField(
                  "PortXmitDataExtended",
                  to_string(add32BitTo64(getFieldValue("port_xmit_data_high"), getFieldValue("port_xmit_data_low")))));
                fields.push_back(AmberField(
                  "PortRcvDataExtended",
                  to_string(add32BitTo64(getFieldValue("port_rcv_data_high"), getFieldValue("port_rcv_data_low")))));
                fields.push_back(AmberField(
                  "PortXmitPktsExtended",
                  to_string(add32BitTo64(getFieldValue("port_xmit_pkts_high"), getFieldValue("port_xmit_pkts_low")))));
                fields.push_back(AmberField(
                  "PortRcvPktsExtended",
                  to_string(add32BitTo64(getFieldValue("port_rcv_pkts_high"), getFieldValue("port_rcv_pkts_low")))));

                // Getting engress counters
                resetLocalParser(ACCESS_REG_PPCNT);
                updateField("local_port", _localPort);
                updateField("grp", PPCNT_DISC_COUNTERS_GROUP);
                sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
                fields.push_back(AmberField(
                  "PortSwLifetimeLimitDiscards",
                  to_string(add32BitTo64(getFieldValue("egress_sll_high"), getFieldValue("egress_sll_low")))));
                fields.push_back(AmberField("PortSwHOQLifetimeLimitDiscards",
                                            to_string(add32BitTo64(getFieldValue("egress_hoq_stall_high"),
                                                                   getFieldValue("egress_hoq_stall_low")))));
                // Getting PLR counters data
                resetLocalParser(ACCESS_REG_PPCNT);
                updateField("local_port", _localPort);
                updateField("grp", PPCNT_PLR_GROUP);
                sendRegister(ACCESS_REG_PPCNT, MACCESS_REG_METHOD_GET);
                fields.push_back(AmberField(
                  "PlrRcvCodes",
                  to_string(add32BitTo64(getFieldValue("plr_rcv_codes_high"), getFieldValue("plr_rcv_codes_low")))));
                fields.push_back(AmberField("PlrRcvCodeErr",
                                            to_string(add32BitTo64(getFieldValue("plr_rcv_code_err_high"),
                                                                   getFieldValue("plr_rcv_code_err_low")))));
                fields.push_back(AmberField("PlrRcvUncorrectableCode",
                                            to_string(add32BitTo64(getFieldValue("plr_rcv_uncorrectable_code_high"),
                                                                   getFieldValue("plr_rcv_uncorrectable_code_low")))));
                fields.push_back(AmberField(
                  "PlrXmitCodes",
                  to_string(add32BitTo64(getFieldValue("plr_xmit_codes_high"), getFieldValue("plr_xmit_codes_low")))));
                fields.push_back(AmberField("PlrXmitRetryCodes",
                                            to_string(add32BitTo64(getFieldValue("plr_xmit_retry_codes_high"),
                                                                   getFieldValue("plr_xmit_retry_codes_low")))));
                fields.push_back(AmberField("PlrXmitRetryEvents",
                                            to_string(add32BitTo64(getFieldValue("plr_rcv_codes_high"),
                                                                   getFieldValue("plr_xmit_retry_events_low")))));
                fields.push_back(AmberField("PlrSyncEvents",
                                            to_string(add32BitTo64(getFieldValue("plr_sync_events_high"),
                                                                   getFieldValue("plr_sync_events_low")))));
                fields.push_back(AmberField("PlrCodesLoss",
                                            to_string(add32BitTo64(getLocalFieldValue("plr_codes_loss_high"),
                                                                   getLocalFieldValue("plr_codes_loss_low")))));
                fields.push_back(AmberField(
                  "PlrXmitRetryEventsWithinTSecMax",
                  to_string(add32BitTo64(getLocalFieldValue("plr_xmit_retry_events_within_t_sec_max_high"),
                                         getLocalFieldValue("plr_xmit_retry_events_within_t_sec_max_low")))));
            }
        }
        else
        {
            // Getting the PCIE errors fields (PCIE only)
            resetLocalParser(ACCESS_REG_MPCNT);
            updateField("depth", _depth);
            updateField("pcie_index", _pcieIndex);
            updateField("node", _node);
            updateField("grp", MPCNT_PERFORMANCE_GROUP);
            sendRegister(ACCESS_REG_MPCNT, MACCESS_REG_METHOD_GET);

            fields.push_back(AmberField("crc_error_dllp", getFieldStr("crc_error_dllp")));
            fields.push_back(AmberField("crc_error_tlp", getFieldStr("crc_error_tlp")));
            fields.push_back(AmberField("tx_overflow_buffer_pkt",
                                        to_string(add32BitTo64(getFieldValue("tx_overflow_buffer_pkt_hi"),
                                                               getFieldValue("tx_overflow_buffer_pkt_lo")))));
            fields.push_back(AmberField("outbound_stalled_reads", getFieldStr("outbound_stalled_reads")));
            fields.push_back(AmberField("outbound_stalled_writes", getFieldStr("outbound_stalled_writes")));
            fields.push_back(AmberField("outbound_stalled_reads_events", getFieldStr("outbound_stalled_reads_events")));
            fields.push_back(AmberField("outbound_stalled_writes_events", getFieldStr("outbound_stalled_writes_"
                                                                                      "events")));
            fields.push_back(AmberField("tx_overflow_buffer_marked_pkt",
                                        to_string(add32BitTo64(getFieldValue("tx_overflow_buffer_marked_pkt_hi"),
                                                               getFieldValue("tx_overflow_buffer_marked_pkt_lo")))));
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Port Counters information: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getTroubleshootingInfo()
{
    vector<AmberField> fields;

    try
    {
        if (!_isPortPCIE)
        {
            resetLocalParser(ACCESS_REG_PDDR);
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_LOCAL);
            updateField("page_select", PDDR_TROUBLESHOOTING_INFO_PAGE);
            updateField("group_opcode", MONITOR_OPCODE);
            sendRegister(ACCESS_REG_PDDR, MACCESS_REG_METHOD_GET);

            string message = "";
            char txt[16], c;
            u_int32_t message_buf;
            bool finalize = false;
            for (int i = 0; i < PDDR_STATUS_MESSAGE_LENGTH_SWITCH; i++)
            {
                string path = "status_message[";
                sprintf(txt, "%d", i);
                path.append(txt);
                path.append("]");
                message_buf = getFieldValue(path);
                for (int k = 24; k > -1; k -= 8)
                {
                    c = (char)(message_buf >> k);
                    if (c == '\0')
                    {
                        finalize = true;
                        break;
                    }
                    message.push_back(c);
                }
                if (finalize == true)
                {
                    break;
                }
            }

            fields.push_back(AmberField("Advanced_Status_Opcode", getFieldStr("monitor_opcode")));
            fields.push_back(AmberField("Status_Message", message));
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Troubleshooting information: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getLinkUpInfo()
{
    vector<AmberField> fields;

    try
    {
        // Access regs: [PDDR.linkup_info_page]
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get LinkUp information: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getLinkDownInfo()
{
    vector<AmberField> fields;

    try
    {
        // Access regs: [PDDR.linkdown_info_page]
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get LinkDown information: %s", exc.what());
    }

    return fields;
}

string MlxlinkAmBerCollector::getPrbsModeCap(u_int32_t modeSelector, u_int32_t capsMask)
{
    string modeCapStr = "";
    u_int32_t mask = 0;
    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
         it != _mlxlinkMaps->_prbsModesList.end();
         it++)
    {
        mask = PRBS31_CAP << it->first;
        if (capsMask & mask)
        {
            modeCapStr += it->second;
            if (modeSelector == PRBS_RX && mask == SQUARE_WAVEA_CAP)
            {
                // return SQUARE_WAVE without A for RX pattern
                modeCapStr = deleteLastChar(modeCapStr);
            }
            modeCapStr += ",";
        }
    }
    return deleteLastChar(modeCapStr);
}

void MlxlinkAmBerCollector::getTestModePrpsInfo(const string& prbsReg, vector<vector<string>>& params)
{
    string laneRateStr = "lane_rate_admin";
    if (prbsReg == ACCESS_REG_PPRT)
    {
        laneRateStr = "lane_rate_oper";
    }

    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        resetLocalParser(prbsReg);
        updateField("local_port", _localPort);
        updateField("lane", lane);
        updateField("pnat", _pnat);
        sendRegister(prbsReg, MACCESS_REG_METHOD_GET);

        if (prbsReg == ACCESS_REG_PPRT)
        {
            params[PRBS_PARAMS_RX_TUNING_STATUS][lane] =
              getStrByValue(getFieldValue("prbs_rx_tuning_status"), _mlxlinkMaps->_prbsRxTuningStatus);
            params[PRBS_PARAMS_LOCK_STATUS][lane] =
              getStrByValue(getFieldValue("prbs_lock_status"), _mlxlinkMaps->_prbsLockStatus);
        }
        params[PRBS_PARAMS_E][lane] = getStrByValue(getFieldValue("e"), _mlxlinkMaps->_prbsEStatus);
        params[PRBS_PARAMS_P][lane] = getStrByValue(getFieldValue("p"), _mlxlinkMaps->_prbsPStatus);
        params[PRBS_PARAMS_MODES_CAP][lane] = getPrbsModeCap(PRBS_TX, getFieldValue("prbs_modes_cap"));
        params[PRBS_PARAMS_MODE_ADMIN][lane] =
          getStrByValue(getFieldValue("prbs_mode_admin"), _mlxlinkMaps->_prbsModesList);
        params[PRBS_PARAMS_MODULATION][lane] =
          getStrByValue(getFieldValue("modulation"), _mlxlinkMaps->_prbsModulation);
        params[PRBS_PARAMS_LANE_RATE_CAP][lane] =
          getStrByMask(getFieldValue("lane_rate_cap"), _mlxlinkMaps->_prbsLaneRateCap);
        params[PRBS_PARAMS_LANE_RATE_ADMIN][lane] =
          getStrByValue(getFieldValue(laneRateStr), _mlxlinkMaps->_prbsLaneRateList);
    }
}

vector<AmberField> MlxlinkAmBerCollector::getTestModeInfo()
{
    vector<AmberField> fields;
    try
    {
        vector<vector<string>> pprtParams(PRBS_PARAMS_LAST, vector<string>(_maxLanes, ""));
        vector<vector<string>> ppttParams(PRBS_PARAMS_LAST, vector<string>(_maxLanes, ""));
        getTestModePrpsInfo(ACCESS_REG_PPRT, pprtParams);
        getTestModePrpsInfo(ACCESS_REG_PPTT, ppttParams);

        fillParamsToFields("prbs_rx_tuning_status", pprtParams[PRBS_PARAMS_RX_TUNING_STATUS], fields);
        fillParamsToFields("prbs_rx_lock_status", pprtParams[PRBS_PARAMS_LOCK_STATUS], fields);
        fillParamsToFields("prbs_rx_enable", pprtParams[PRBS_PARAMS_E], fields);
        fillParamsToFields("prbs_rx_polarity", pprtParams[PRBS_PARAMS_P], fields);
        fillParamsToFields("prbs_rx_modes_cap", pprtParams[PRBS_PARAMS_MODES_CAP], fields);
        fillParamsToFields("prbs_rx_mode_admin", pprtParams[PRBS_PARAMS_MODE_ADMIN], fields);
        fillParamsToFields("prbs_rx_modulation", pprtParams[PRBS_PARAMS_MODULATION], fields);
        fillParamsToFields("prbs_rx_lane_rate_cap", pprtParams[PRBS_PARAMS_LANE_RATE_CAP], fields);
        fillParamsToFields("prbs_rx_lane_rate_admin", pprtParams[PRBS_PARAMS_LANE_RATE_ADMIN], fields);

        fillParamsToFields("prbs_tx_enable", ppttParams[PRBS_PARAMS_E], fields);
        fillParamsToFields("prbs_tx_polarity", ppttParams[PRBS_PARAMS_P], fields);
        fillParamsToFields("prbs_tx_modes_cap", ppttParams[PRBS_PARAMS_MODES_CAP], fields);
        fillParamsToFields("prbs_tx_mode_admin", ppttParams[PRBS_PARAMS_MODE_ADMIN], fields);
        fillParamsToFields("prbs_tx_modulation", ppttParams[PRBS_PARAMS_MODULATION], fields);
        fillParamsToFields("prbs_tx_lane_rate_cap", ppttParams[PRBS_PARAMS_LANE_RATE_CAP], fields);
        fillParamsToFields("prbs_tx_lane_rate_admin", ppttParams[PRBS_PARAMS_LANE_RATE_ADMIN], fields);
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Test Mode information: %s", exc.what());
    }

    return fields;
}

void MlxlinkAmBerCollector::getTestModeModulePMPT(vector<AmberField>& fields, string moduleSide, ModuleAccess_t mode)
{
    resetLocalParser(ACCESS_REG_PMPT);
    updateField("module", _moduleIndex);
    updateField("slot_index", _slotIndex);
    updateField("host_media", moduleSide == "host");
    updateField("ch_ge", (u_int32_t)mode);
    sendRegister(ACCESS_REG_PMPT, MACCESS_REG_METHOD_GET);

    string modeStr = mode == MODULE_PRBS_ACCESS_GEN ? "generator" : "checker";

    fields.push_back(AmberField("prbs_" + modeStr + "_pattern_cap_" + moduleSide,
                                getPrbsModeCap(PRBS_RX, getFieldValue("prbs_modes_cap"))));
    fields.push_back(AmberField("prbs_" + modeStr + "_pattern_admin_" + moduleSide,
                                getStrByValue(getFieldValue("prbs_mode_admin"), _mlxlinkMaps->_prbsModesList)));
    fields.push_back(AmberField("prbs_" + modeStr + "_msb_lsb_swap_" + moduleSide,
                                getStrByValue(getFieldValue("swap_admin"), _mlxlinkMaps->_modulePrbsSwapAdmin)));
    fields.push_back(AmberField("prbs_" + modeStr + "_polarity_" + moduleSide,
                                getStrByValue(getFieldValue("invt_admin"), _mlxlinkMaps->_modulePrbsInvAdmin)));
    fields.push_back(AmberField("prbs_" + modeStr + "_modulation_" + moduleSide,
                                getStrByValue(getFieldValue("modulation"), _mlxlinkMaps->_modulePrbsModulation)));
    fields.push_back(AmberField("prbs_" + modeStr + "_lane_rate_cap_" + moduleSide,
                                getStrByMask(getFieldValue("lane_rate_cap"), _mlxlinkMaps->_modulePrbsRateCapToStr)));
    fields.push_back(AmberField("prbs_" + modeStr + "_lane_rate_admin_" + moduleSide,
                                getStrByValue(getFieldValue("lane_rate_admin"), _mlxlinkMaps->_modulePrbsRateCapToStr)));
}

void MlxlinkAmBerCollector::getTestModeModulePMPD(vector<AmberField>& fields, string moduleSide)
{
    vector<vector<string>> pmpdParams(PMPD_PARAM_LAST, vector<string>(_maxLanes, ""));

    for (u_int32_t lane = 0; lane < _maxLanes; lane++)
    {
        resetLocalParser(ACCESS_REG_PMPD);
        updateField("module", _moduleIndex);
        updateField("slot_index", _slotIndex);
        updateField("host_media", moduleSide == "host");
        updateField("lane", lane);
        sendRegister(ACCESS_REG_PMPD, MACCESS_REG_METHOD_GET);

        pmpdParams[PMPD_PARAM_STATUS][lane] = getStrByValue(getFieldValue("status"), _mlxlinkMaps->_modulePMPDStatus);
        pmpdParams[PMPD_PARAM_PRBS_BITS][lane] =
          to_string(add32BitTo64(getFieldValue("prbs_bits_high"), getFieldValue("prbs_bits_low")));
        pmpdParams[PMPD_PARAM_PRBS_ERRORS][lane] =
          to_string(add32BitTo64(getFieldValue("prbs_errors_high"), getFieldValue("prbs_errors_low")));
        pmpdParams[PMPD_PARAM_SNR][lane] = getFieldStr("measured_snr") + "dB";
        pmpdParams[PMPD_PARAM_BER][lane] = getFieldStr("ber_coef") + "E-" + getFieldStr("ber_magnitude");
    }

    fillParamsToFields("prbs_checker_status_" + moduleSide, pmpdParams[PMPD_PARAM_STATUS], fields);
    fillParamsToFields("prbs_checker_bits_" + moduleSide, pmpdParams[PMPD_PARAM_PRBS_BITS], fields);
    fillParamsToFields("prbs_checker_errors_" + moduleSide, pmpdParams[PMPD_PARAM_PRBS_ERRORS], fields);
    fillParamsToFields("prbs_checker_snr_" + moduleSide, pmpdParams[PMPD_PARAM_SNR], fields);
    fillParamsToFields("prbs_checker_ber_" + moduleSide, pmpdParams[PMPD_PARAM_BER], fields);
}

vector<AmberField> MlxlinkAmBerCollector::getTestModeModuleInfo()
{
    vector<AmberField> fields;

    try
    {
        fields.push_back(AmberField("prbs_status_host", getStrByValue(_moduleHostSt, _mlxlinkMaps->_modulePrbsSt)));
        getTestModeModulePMPT(fields, "host", MODULE_PRBS_ACCESS_CH);
        getTestModeModulePMPT(fields, "host", MODULE_PRBS_ACCESS_GEN);
        getTestModeModulePMPD(fields, "host");

        fields.push_back(AmberField("prbs_status_media", getStrByValue(_moduleMediaSt, _mlxlinkMaps->_modulePrbsSt)));
        getTestModeModulePMPT(fields, "media", MODULE_PRBS_ACCESS_CH);
        getTestModeModulePMPT(fields, "media", MODULE_PRBS_ACCESS_GEN);
        getTestModeModulePMPD(fields, "media");
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Test Mode Module information: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getPhyDebugInfo()
{
    vector<AmberField> fields;

    try
    {
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Phy Debug information: %s", exc.what());
    }

    return fields;
}

vector<AmberField> MlxlinkAmBerCollector::getExtModuleStatus()
{
    vector<AmberField> fields;

    try
    {
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Failed to get Extended Module information: %s", exc.what());
    }

    return fields;
}

void MlxlinkAmBerCollector::groupValidIf(bool condition)
{
    if (condition)
    {
        _invalidate = false;
    }
    else
    {
        _invalidate = true;
    }
}

vector<AmberField> MlxlinkAmBerCollector::collectSheet(AMBER_SHEET sheet)
{
    vector<AmberField> fields;
    bool invalidSheet = false;
    _invalidate = false;
    fields.push_back(AmberField("N/A", "N/A"));

    AmberField::reset();

    switch (sheet)
    {
        case AMBER_SHEET_GENERAL:
            fields = getGeneralInfo();
            break;
        case AMBER_SHEET_INDEXES:
            fields = getIndexesInfo();
            break;
        case AMBER_SHEET_LINK_STATUS:
            fields = getLinkStatus();
            break;
        case AMBER_SHEET_MODULE_STATUS:
            fields = getModuleStatus();
            break;
        case AMBER_SHEET_SYSTEM:
            fields = getSystemInfo();
            break;
        case AMBER_SHEET_SERDES_16NM:
            groupValidIf(_productTechnology == PRODUCT_16NM);
            fields = getSerdesHDR();
            break;
        case AMBER_SHEET_SERDES_7NM:
            groupValidIf(_productTechnology == PRODUCT_7NM);
            fields = getSerdesNDR();
            break;
        case AMBER_SHEET_PORT_COUNTERS:
            if (!_inPRBSMode)
            {
                fields = getPortCounters();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_TROUBLESHOOTING:
            if (!_inPRBSMode)
            {
                fields = getTroubleshootingInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_PHY_OPERATION_INFO:
            if (!_inPRBSMode)
            {
                fields = getPhyOperationInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_LINK_UP_INFO:
            if (!_inPRBSMode)
            {
                fields = getLinkUpInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_LINK_DOWN_INFO:
            if (!_inPRBSMode)
            {
                fields = getLinkDownInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_TEST_MODE_INFO:
            if (_inPRBSMode)
            {
                fields = getTestModeInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_TEST_MODE_MODULE_INFO:
            if (_inPRBSMode)
            {
                fields = getTestModeModuleInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_PHY_DEBUG_INFO:
            if (!_inPRBSMode)
            {
                fields = getPhyDebugInfo();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        case AMBER_SHEET_EXT_MODULE_STATUS:
            if (!_inPRBSMode)
            {
                fields = getExtModuleStatus();
            }
            else if (isIn(sheet, _sheetsToDump))
            {
                invalidSheet = true;
            }
            break;
        default:
            throw MlxRegException("Invalid amBER page index: %d", sheet);
    }

    if (!_sheetsToDump.empty())
    {
        if (invalidSheet)
        {
            string mode = _inPRBSMode ? "Operational mode" : "PRBS test mode";
            throw MlxRegException("Page %d is valid in %s only!", sheet, mode.c_str());
        }
    }
    return fields;
}

void MlxlinkAmBerCollector::collect()
{
    for (const auto& sheet : _sheetsList)
    {
        auto sheetFields = collectSheet(sheet.first);
        if (sheetFields.empty() || sheetFields.back().getUiField() != "N/A")
        {
            _amberCollection[sheet.first] = sheetFields;
        }
    }
}

u_int32_t MlxlinkAmBerCollector::fixFieldsData()
{
    u_int32_t lastFieldIndexPerGroup = 0;
    u_int32_t totalFields = 0;

    for (auto it = _amberCollection.begin(); it != _amberCollection.end(); it++)
    {
        for (auto fieldIt = (*it).second.begin(); fieldIt != (*it).second.end();)
        {
            if ((*fieldIt).getFieldIndex() == 0)
            {
                (*it).second.erase(fieldIt);
            }
            else
            {
                ++fieldIt;
            }
        }
    }
    for (auto it = _amberCollection.begin(); it != _amberCollection.end(); it++)
    {
        if (_isPortPCIE)
        {
            lastFieldIndexPerGroup = _sheetsList[getSheetIndex((*it).first)].second.numOfPcieFields;
        }
        else if (_isPortETH)
        {
            lastFieldIndexPerGroup = _sheetsList[getSheetIndex((*it).first)].second.numOfEthFields;
        }
        else if (_isPortIB)
        {
            lastFieldIndexPerGroup = _sheetsList[getSheetIndex((*it).first)].second.numOfIbFields;
        }
        for (u_int32_t fieldIdx = (*it).second.size() + 1; fieldIdx <= lastFieldIndexPerGroup; fieldIdx++)
        {
            (*it).second.push_back(AmberField("F" + to_string(totalFields + fieldIdx), "N/A", fieldIdx));
        }
        totalFields += lastFieldIndexPerGroup;
    }
    return totalFields;
}

u_int32_t MlxlinkAmBerCollector::getSheetIndex(AMBER_SHEET sheet)
{
    u_int32_t index = 0;
    for (; index < _sheetsList.size(); index++)
    {
        if (_sheetsList[index].first == sheet)
        {
            break;
        }
    }
    return index;
}

void MlxlinkAmBerCollector::exportToCSV()
{
    const char* fileName = _csvFileName.c_str();
    ifstream ifile(fileName);
    ofstream berFile(fileName, std::ofstream::app);

    u_int32_t totalNumOfFields = fixFieldsData();
    // Preparing CSV header line
    if (!ifile.good())
    {
        if (!berFile.good())
        {
            throw MlxRegException("The provided file path does not exist!");
        }
        // Going over all groups inside _amberCollection and getting the field name for each one
        for (const auto& sheet : _sheetsList)
        {
            for (const auto& field : _amberCollection[sheet.first])
            {
                if (field.isVisible())
                {
                    berFile << field.getUiField();
                    if (field.getFieldIndex() < totalNumOfFields)
                    {
                        berFile << ",";
                    }
                }
            }
        }
        berFile << endl;
    }
    // Preparing CSV values
    // Going over all groups inside _amberCollection and getting the field value for each one
    for (const auto& sheet : _sheetsList)
    {
        for (const auto& field : _amberCollection[sheet.first])
        {
            if (field.isVisible())
            {
                berFile << field.getUiValue();
                if (field.getFieldIndex() < totalNumOfFields)
                {
                    berFile << ",";
                }
            }
        }
    }

    berFile << endl;
    berFile.close();
}

void MlxlinkAmBerCollector::exportToConsole()
{
    // Printing all fields to the console (for debugging, will be removed later)
    for (auto it = _amberCollection.begin(); it != _amberCollection.end(); it++)
    {
        for (auto fieldIt = (*it).second.begin(); fieldIt != (*it).second.end(); fieldIt++)
        {
            if ((*fieldIt).isVisible())
            {
                cout << *fieldIt << endl;
            }
        }
    }
}
