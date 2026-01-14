/*
 * Copyright (c) 2019-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include "mlxlink_commander.h"
#include "common/tools_time.h"
#include <sstream>

using namespace mlxreg;

ModuleField::ModuleField(string uiName, string amberName, bool multiVal, bool perLane, bool requireDdm, bool supported) :
    uiName(uiName),
    amberName(amberName),
    multiVal(multiVal),
    perLane(perLane),
    requireDdm(requireDdm),
    supported(supported)
{
}

MlxlinkCommander::MlxlinkCommander() : _userInput()
{
    _extAdbFile = "";
    _localPort = 0;
    _portType = 0;
    _numOfLanes = MAX_LANES_NUMBER;
    _numOfLanesPcie = 0;
    _moduleLanesMapping = vector<u_int32_t>(MAX_LANES_NUMBER);
    _linkUP = false;
    _plugged = false;
    _userInput._linkModeForce = false;
    _prbsTestMode = false;
    _useExtAdb = true;
    _portPolling = false;
    _speedForce = "";
    _anDisable = 0;
    _cableIdentifier = 0;
    _cableTechnology = 0;
    _cableAtten12G = 0;
    _cableLen = 0;
    _cablePN = "N/A";
    _cableSN = "N/A";
    _moduleTemp = "N/A";
    _cableMediaType = 0;
    _moduleNumber = 0;
    _slotIndex = 0;
    _activeSpeed = 0;
    _activeSpeedEx = 0;
    _isXdrSlowActive = false;
    _laneSpeedFromPptt = 0;
    _protoCapability = 0;
    _deviceCapability = 0;
    _linkSpeed = 0;
    _protoCapabilityEx = false;
    _ddmSupported = false;
    _temperature = 0;
    _cmisCable = false;
    _qsfpCable = false;
    _mngCableUnplugged = false;
    _isPam4Speed = false;
    _ignorePortType = true;
    _ignorePortStatus = true;
    _isGboxPort = false;
    _isSwControled = false;
    _isSwControledStandAlone = false;
    _ignoreIbFECCheck = true;
    _isNVLINK = false;
    _protoAdmin = 0;
    _protoAdminEx = 0;
    _speedBerCsv = 0;
    _fecActive = 0;
    _protoActive = 0;
    _phyMngrFsmState = -1;
    _productTechnology = 0;
    _allUnhandledErrors = "";
    _mlxlinkMaps = MlxlinkMaps::getInstance();
    _cablesCommander = NULL;
    _eyeOpener = NULL;
    _errInjector = NULL;
    _portInfo = NULL;
    _amberCollector = NULL;
    _groupOpcode = MONITOR_OPCODE;
    _loopbackMode = 0;
    _fomStr = "";
    _rxRecoveryCountersCmd.setLineLen(RX_RECOVERY_COUNTERS_LINE_LEN);
}

MlxlinkCommander::~MlxlinkCommander()
{
    if (_cablesCommander)
    {
        delete _cablesCommander;
    }
    if (_eyeOpener)
    {
        delete _eyeOpener;
    }
    if (_errInjector)
    {
        delete _errInjector;
    }
    if (_portInfo)
    {
        delete _portInfo;
    }
    if (_amberCollector)
    {
        delete _amberCollector;
    }
    if (_gvmiAddress)
    {
        writeGvmi(0);
    }
    if (_mf)
    {
        mclose(_mf);
    }
    if (_regLib)
    {
        delete _regLib;
    }
    if (_mlxlinkMaps)
    {
        delete _mlxlinkMaps;
    }
}

void MlxlinkCommander::validatePortType(const string& portTypeStr)
{
    _portType = NETWORK_PORT_TYPE;
    map<string, u_int32_t>::iterator it = _mlxlinkMaps->_networkPorts.find(portTypeStr);
    if (it == _mlxlinkMaps->_networkPorts.end())
    {
        string errMsg = "";
        for (it = _mlxlinkMaps->_networkPorts.begin(); it != _mlxlinkMaps->_networkPorts.end(); it++)
        {
            errMsg += it->first;
            if (it->second == NETWORK_PORT_TYPE)
            {
                errMsg += "(Default)";
            }
            errMsg += ", ";
        }
        errMsg = deleteLastChar(errMsg, 2);
        throw MlxRegException("Invalid port type, valid port types are [" + errMsg + "]");
    }
    else if (it->second != NETWORK_PORT_TYPE_LAST)
    {
        _portType = it->second;
    }

    if ((_portType == NETWORK_PORT_TYPE_NEAR) || (_portType == NETWORK_PORT_TYPE_IC_LR) ||
        (_portType == NETWORK_PORT_TYPE_FAR))
    {
        _isGboxPort = true;
    }

    if (_isGboxPort && !isDSdevice())
    {
        throw MlxRegException("Port types of GEARBOX_HOST, INTERNAL_IC_LR and "
                              "GEARBOX_LINE can be used with Switches supporting downstream devices only");
    }
}

void MlxlinkCommander::gearboxBlock(const string& option)
{
    if (_isGboxPort)
    {
        throw MlxRegException("--" + option + " flag is not applicable for " + _userInput._portType + " port type");
    }
}

void MlxlinkCommander::checkRegCmd()
{
    try
    {
        sendPrmReg(ACCESS_REG_PAOS, GET, "local_port=%d,swid=%d", _localPort, SWID);
    }
    catch (MlxRegException& exp)
    {
        throw MlxRegException("Problem accessing the device. Please verify that driver is up");
    }
    throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
}

void MlxlinkCommander::checkValidFW()
{
    try
    {
        char fwVersion[32];
        u_int32_t tmpLocalPort = _localPort;

        sendPrmReg(ACCESS_REG_MGIR, GET);
        sprintf(fwVersion, "%02d.%02d.%04d", getFieldValue("extended_major"), getFieldValue("extended_minor"),
                getFieldValue("extended_sub_minor"));
        _fwVersion = string(fwVersion);

        if (_userInput._pcie)
        { // Fw validity should be checked, so set the local port to 1.
            _localPort = 1;
        }

        try
        {
            sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_OPERATIONAL_INFO_PAGE);
        }
        catch (MlxRegException& exp)
        {
            if (exp.what_s() != "Please Provide Valid gvmi Address (--gvmi_address <address>)")
            {
                checkRegCmd();
            }
            else
            {
                throw MlxRegException(exp);
            }
        }

        u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");

        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d,group_opcode=%d", PDDR_TROUBLESHOOTING_INFO_PAGE,
                   MONITOR_OPCODE);

        u_int32_t statusOpcode = getFieldValue("monitor_opcode");

        if (phyMngrFsmState == 0 && statusOpcode == 0)
        {
            checkAllPortsStatus();
        }
        _localPort = tmpLocalPort;
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string("Checking valid firmware raised the following exception: ") + string(exc.what()) +
                              string("\n"));
    }
}

u_int32_t MlxlinkCommander::getTechnologyFromMGIR()
{
    sendPrmReg(ACCESS_REG_MGIR, GET);

    return getFieldValue("technology");
}

void MlxlinkCommander::getProductTechnology()
{
    // Use SLTP to get the product technology, for backward compatibility
    try
    {
        sendPrmReg(ACCESS_REG_SLTP, GET);
        _productTechnology = getVersion(getFieldValue("version"));
        if (_productTechnology <= 2)
        {
            _productTechnology = PRODUCT_28NM;
        }
    }
    catch (MlxRegException& exc)
    {
        if (!_productTechnology)
        {
            throw MlxRegException("Unable to get product technology: %s", exc.what_s().c_str());
        }
    }
}

u_int32_t MlxlinkCommander::maxLocalPort()
{
    switch (_devID)
    {
        case DeviceSpectrum:
            return MAX_LOCAL_PORT_ETH;

        case DeviceSwitchIB:
        case DeviceSwitchIB2:
            return MAX_LOCAL_PORT_IB;

        case DeviceQuantum:
            return MAX_LOCAL_PORT_QUANTUM;

        case DeviceQuantum2:
        case DeviceGB100:
        case DeviceGR100:
            return MAX_LOCAL_PORT_QUANTUM2;

        case DeviceQuantum3:
            return MAX_LOCAL_PORT_QUANTUM3;

        case DeviceSpectrum2:
        case DeviceSpectrum3:
            return MAX_LOCAL_PORT_SPECTRUM2;

        case DeviceSpectrum4:
            return MAX_LOCAL_PORT_SPECTRUM4;

        case DeviceSpectrum5:
            return MAX_LOCAL_PORT_SPECTRUM5;

        case DeviceSpectrum6:
            return MAX_LOCAL_PORT_SPECTRUM6;

        default:
            return 0;
    }
    return 0;
}

bool MlxlinkCommander::checkPortStatus(u_int32_t localPort)
{
    sendPrmReg(ACCESS_REG_PDDR, GET, "local_port=%d,page_select=%d", localPort, PDDR_OPERATIONAL_INFO_PAGE);

    u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");

    sendPrmReg(ACCESS_REG_PDDR, GET, "local_port=%d,page_select=%d,group_opcode=%d", localPort,
               PDDR_TROUBLESHOOTING_INFO_PAGE, MONITOR_OPCODE);

    u_int32_t statusOpcode = getFieldValue("monitor_opcode");

    if (!(phyMngrFsmState == 0 && statusOpcode == 0))
    {
        return true;
    }
    return false;
}

void MlxlinkCommander::checkAllPortsStatus()
{
    if (_isHCA)
    {
        checkRegCmd();
    }
    if (_devID == DeviceSpectrum)
    {
        for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
        {
            sendPrmReg(ACCESS_REG_PMLP, GET, "local_port=%d", localPort);

            if (getFieldValue("width") == 0)
            {
                continue;
            }

            if (checkPortStatus(localPort))
            {
                return;
            }
        }
        throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
    }
    else if (dm_dev_is_ib_switch(_devID))
    {
        for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
        {
            sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);

            if (getFieldValue("ib_port") == 0)
            {
                continue;
            }

            if (checkPortStatus(localPort))
            {
                return;
            }
        }
        throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
    }
}

void MlxlinkCommander::validatePortToLC()
{
    bool isDownStreamDevValid = true;

    sendPrmReg(ACCESS_REG_PMLP, GET);

    u_int32_t slotIndex = getFieldValue("slot_index_0");

    try
    {
        sendPrmReg(ACCESS_REG_MDDQ, GET, "query_type=%d,slot_index=%d", 1, slotIndex);
    }
    catch (MlxRegException& exc)
    {
        isDownStreamDevValid = false;
    }

    if (!isDownStreamDevValid)
    {
        if (slotIndex == 0 && _isGboxPort)
        {
            throw MlxRegException("No cards detected on the device.");
        }
    }
    else if (_isGboxPort)
    {
        if (getFieldValue("lc_ready") != 1)
        {
            throw MlxRegException("Invalid port number, Line card %d is not ready", slotIndex);
        }
    }
}

void MlxlinkCommander::handlePortStr(const string& portStr)
{
    auto portParts = MlxlinkRecord::split(portStr, "/");
    // validate arguments
    for (auto it = portParts.begin(); it != portParts.end(); it++)
    {
        if ((*it).empty())
        {
            throw MlxRegException("Argument: %s is invalid.", portStr.c_str());
        }
    }

    /* For Quantum-2:
     * portStr should represent: (cage/port/split) if split sign provided
     *                           (cage/port) if no split sign provided
     * For Other Switches:
     * portStr should represent: (port/split) if split sign provided
     *                           (port) if no split sign provided
     */
    if (portParts.size() > 1)
    {
        strToUint32((char*)portParts[1].c_str(), _userInput._splitPort);
        _userInput._splitProvided = true;
        if (portParts.size() > SECOND_LEVEL_PORT_ACCESS)
        {
            // it's the split part of Quantum-2 (xx/xx/split)
            strToUint32((char*)portParts[2].c_str(), _userInput._secondSplitPort);
            _userInput._secondSplitProvided = true;
        }
        else if (portParts.size() > THIRD_LEVEL_PORT_ACCESS)
        {
            throw MlxRegException("Failed to handle option port");
        }
    }

    strToUint32((char*)portParts[0].c_str(), _userInput._labelPort);
    _userInput._portSpecified = true;
}

void MlxlinkCommander::updateSwControlStatus()
{
    try
    {
        sendPrmReg(ACCESS_REG_MGIR, GET);
        u_int32_t moduleMasterFwDefault = getFieldValue("module_master_fw_default");
        if (moduleMasterFwDefault == MGIR_MODULE_MASTER_FW_DEFAULT_STAND_ALONE)
        {
            _isSwControled = true;
            _isSwControledStandAlone = true;
            return;
        }
    }
    catch (MlxRegException& exc)
    {
    }

    try
    {
        sendPrmReg(ACCESS_REG_MMCR, GET);
    }
    catch (MlxRegException& exc)
    {
        _isSwControled = false;
        return;
    }
    u_int32_t currentModuleControl =
      getFieldValue("curr_module_control[" + to_string((_userInput._labelPort - 1) / 32) + "]");
    u_int32_t portMask = 0;
    portMask = portMask | 1 << ((_userInput._labelPort - 1) % 32);
    if (portMask & currentModuleControl)
    {
        _isSwControled = true;
    }
}

void MlxlinkCommander::findFirstValidPort()
{
    u_int32_t minLabelPort = 0;
    u_int32_t LabelSplit = 0;
    u_int32_t LabelIpil = 0;
    u_int32_t splitStat = 0;
    u_int32_t ipilStat = 0;

    string regName = ACCESS_REG_PLLP, fieldToGet = "label_port";
    if (dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
    {
        regName = ACCESS_REG_PLIB;
        fieldToGet = "ib_port";
    }

    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(regName, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue;
        }
        u_int32_t currentLabelPort = getFieldValue(fieldToGet);
        if (minLabelPort == 0 || currentLabelPort < minLabelPort)
        {
            minLabelPort = currentLabelPort;
            if (!dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
            {
                LabelIpil = getFieldValue("ipil_num");
                LabelSplit = getFieldValue("split_num");
                ipilStat = getFieldValue("ipil_stat");
                splitStat = getFieldValue("split_stat");
            }
        }
    }

    if (!dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
    {
        _userInput._labelPort = minLabelPort;
        if (ipilStat != 0 && splitStat != 0)
        {
            _userInput._splitProvided = true;
            _userInput._splitPort = LabelIpil;
            _userInput._secondSplitProvided = true;
            _userInput._secondSplitPort = LabelSplit + 1;
        }
        else if (ipilStat != 0)
        {
            _userInput._splitProvided = true;
            _userInput._splitPort = LabelIpil;
        }
        else if (splitStat != 0)
        {
            _userInput._splitProvided = true;
            _userInput._splitPort = LabelSplit + 1;
        }
    }
}

void MlxlinkCommander::labelToLocalPort()
{
    _pnat = _userInput._pcie ? PNAT_PCIE : PNAT_LOCAL;

    if ((_isHCA || (_mf->tp == MST_PCICONF && dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))) && _userInput._pcie)
    {
        _dpn.depth = _userInput._depth;
        _dpn.pcieIndex = _userInput._pcieIndex;
        _dpn.node = _userInput._node;

        initValidDPNList();

        if (_userInput._sendDpn)
        {
            int localPort = getLocalPortFromMPIR(_dpn);
            if (localPort >= 0)
            {
                _localPort = localPort;
            }
            else
            {
                throw MlxRegException("Invalid PCIe link: depth, pcie_index and node [%d, %d, %d]", _dpn.depth,
                                      _dpn.pcieIndex, _dpn.node);
            }
        }
        else if (_userInput._portSpecified)
        {
            checkLocalPortDPNMapping(_userInput._labelPort);
            _localPort = _userInput._labelPort;
        }
        else
        {
            if (!_validDpns.empty())
            {
                _dpn = _validDpns[0]; // default DPN link
            }
            _localPort = getLocalPortFromMPIR(_dpn);
        }
        return;
    }
    if (_isHCA)
    {
        labelToHCALocalPort();
        return;
    }
    else if (_userInput._pcie)
    {
        throw MlxRegException("No PCIE in this device!");
    }

    if (_devID == DeviceSpectrum || _devID == DeviceSpectrum2 || _devID == DeviceSpectrum3 ||
        _devID == DeviceSpectrum4 || _devID == DeviceSpectrum5 || 
        _devID == DeviceSpectrum6)
    {
        if (isDSdevice())
        {
            labeltoDSlocalPort();
        }
        else
        {
            labelToLocalPortGenericMapping();
        }
    }
    else if (dm_dev_is_ib_switch(_devID))
    {
        if (_devID == DeviceQuantum3 || dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            labelToLocalPortGenericMapping();
        }
        else
        {
            labelToIBLocalPort();
        }
    }
}

bool MlxlinkCommander::isDSdevice()
{
    bool isDownStreamDevValid = true;

    try
    {
        sendPrmReg(ACCESS_REG_MDDQ, GET, "query_type=1,slot_index=1");
    }
    catch (MlxRegException& exc)
    {
        isDownStreamDevValid = false;
    }

    return isDownStreamDevValid;
}

void MlxlinkCommander::labeltoDSlocalPort()
{
    u_int32_t lineCard = _userInput._labelPort;
    u_int32_t port = _userInput._splitPort;
    bool isLocalPortValid = false;

    if (_userInput._secondSplitProvided)
    {
        throw MlxRegException("No split supported for downstream devices");
    }

    sendPrmReg(ACCESS_REG_MDDQ, GET, "query_type=%d,slot_index=%d", 1, lineCard);

    if (getFieldValue("lc_ready") != 1)
    {
        throw MlxRegException("Invalid port number, Line card %d is not ready", lineCard);
    }

    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLLP, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue;
        }

        if ((getFieldValue("label_port") == port) && (getFieldValue("slot_num") == lineCard))
        {
            _localPort = localPort;
            _slotIndex = lineCard;
            isLocalPortValid = true;
            break;
        }
    }

    if (!isLocalPortValid)
    {
        throw MlxRegException("Invalid port number");
    }
}

void MlxlinkCommander::checkLocalPortDPNMapping(u_int32_t localPort)
{
    for (u_int32_t i = 0; i < _validDpns.size(); i++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_MPIR, GET, "depth=%d,pcie_index=%d,node=%d", _validDpns[i].depth,
                       _validDpns[i].pcieIndex, _validDpns[i].node);
        }
        catch (MlxRegException& exc)
        {
            continue;
        }
        if (getFieldValue("local_port") == localPort)
        {
            _dpn = _validDpns[i];
            return;
        }
    }
    throw MlxRegException("Invalid PCIe local port to depth, pcie_index and node mapping: %d", localPort);
}

int MlxlinkCommander::getLocalPortFromMPIR(DPN& dpn)
{
    if (!isIn(dpn, _validDpns))
    {
        throw MlxRegException("Invalid PCIe link: depth, pcie_index and node [%d, %d, %d]", dpn.depth, dpn.pcieIndex,
                              dpn.node);
    }

    int localPort = 0;
    if (!_userInput._portSpecified)
    {
        try
        {
            sendPrmReg(ACCESS_REG_MPIR, GET, "depth=%d,pcie_index=%d,node=%d", dpn.depth, dpn.pcieIndex, dpn.node);
            localPort = getFieldValue("local_port");
            dpn.bdf = getBDFStr(getFieldValue("bdf0"));
        }
        catch (MlxRegException& exc)
        {
        }
    }
    else
    {
        localPort = _userInput._labelPort;
    }

    return localPort;
}

void MlxlinkCommander::labelToHCALocalPort()
{
    u_int32_t mtype = 0;
    mget_mdevs_type(_mf, &mtype);
    if (_userInput._splitProvided)
    {
        throw MlxRegException("No Splits in HCA!");
    }
    else if (_userInput._labelPort > 1 && !(mtype & (MST_USB_DIMAX)))
    {
        throw MlxRegException("Please Provide the Physical Device of Port " + to_string(_userInput._labelPort));
    }
    else if (_userInput._labelPort > 1 && (mtype & (MST_USB_DIMAX)))
    {
        if (_userInput._labelPort == 2)
        {
            if (_userInput._gvmiAddress == 0)
            {
                throw MlxRegException("Please Provide Valid gvmi Address (--gvmi_address <address>)");
            }
        }
        else
        {
            throw MlxRegException("Please Provide Valid Port Number (1/2)");
        }
    }
    _localPort = 1;
}

void MlxlinkCommander::labelToLocalPortGenericMapping()
{
    u_int32_t foundedLocalPort = 0;

    if (dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
    {
        if (_userInput._splitProvided || _userInput._secondSplitProvided)
        {
            throw MlxRegException("Invalid port number!");
        }
        for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
        {
            try
            {
                sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
            }
            catch (MlxRegException& exp)
            {
                continue;
            }
            if (getFieldValue("ib_port") == _userInput._labelPort)
            {
                foundedLocalPort = localPort;
                break;
            }
        }
    }
    else
    {
        u_int32_t cageIn = _userInput._labelPort;
        u_int32_t ipilIn = 1;
        u_int32_t splitIn = 1;

        u_int32_t splitStat = 0;
        u_int32_t ipilStat = 0;
        for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
        {
            ipilIn = 1;
            splitIn = 1;
            try
            {
                sendPrmReg(ACCESS_REG_PLLP, GET, "local_port=%d", localPort);
            }
            catch (MlxRegException& exp)
            {
                continue;
            }

            ipilStat = getFieldValue("ipil_stat");
            splitStat = getFieldValue("split_stat");
            if (cageIn != getFieldValue("label_port"))
            {
                // if the label port is not the same as the cage in, then nothing to check on the local port continue to
                // the next local port
                continue;
            }
            if (_userInput._secondSplitProvided && (ipilStat == 0 || splitStat == 0))
            {
                throw MlxRegException("Invalid split/inter-port number!");
            }
            if (_userInput._splitProvided && (ipilStat == 0 && splitStat == 0))
            {
                throw MlxRegException("Invalid split/inter-port number!");
            }
            // case -p port/ipil/split
            if (_userInput._secondSplitProvided)
            {
                ipilIn = _userInput._splitPort;
                splitIn = _userInput._secondSplitPort;
            }
            // case -p port/ipil
            else if (_userInput._splitProvided && ipilStat != 0)
            {
                ipilIn = _userInput._splitPort;
            }
            // case -p port/split
            else if (_userInput._splitProvided && splitStat != 0)
            {
                splitIn = _userInput._splitPort;
            }

            if (ipilIn > (u_int32_t)(1 << ipilStat) || (splitIn - 1) > (u_int32_t)(1 << splitStat))
            {
                throw MlxRegException("Invalid split/inter-port number!");
            }

            if ((ipilStat == 0 || ipilIn == getFieldValue("ipil_num")) &&
                (splitStat == 0 || (splitIn - 1) == getFieldValue("split_num")))
            {
                foundedLocalPort = localPort;
                break;
            }
        }
    }

    if (!foundedLocalPort)
    {
        throw MlxRegException("Invalid port number!");
    }
    _localPort = foundedLocalPort;
}

void MlxlinkCommander::labelToIBLocalPort()
{
    u_int32_t labelPort = _userInput._labelPort;
    bool ibSplitReady = isIBSplitReady() && (_devID == DeviceQuantum || _devID == DeviceQuantum2);
    if (_userInput._splitProvided && _devID != DeviceQuantum && _devID != DeviceQuantum2)
    {
        throw MlxRegException("No split in IB!");
    }
    u_int32_t maxLabelPort = _devID == DeviceQuantum2 ? maxLocalPort() / 4 :
                             _devID == DeviceQuantum  ? maxLocalPort() / 2 - 1 :
                                                        maxLocalPort();
    if ((labelPort > maxLabelPort) ||
        (_userInput._secondSplitProvided && _devID != DeviceQuantum2 && !dm_is_gpu(static_cast<dm_dev_id_t>(_devID))) ||
        (_userInput._splitPort > 2))
    {
        throw MlxRegException("Invalid port number!");
    }
    if (_devID == DeviceQuantum || _devID == DeviceQuantum2)
    {
        labelPort = calculatePanelPort(ibSplitReady);
    }
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue; // no reason to fail when one of the ports is not supported, such as in split mode.
        }
        if (getFieldValue("ib_port") == labelPort)
        {
            _localPort = localPort;
            return;
        }
    }
    if ((_devID == DeviceQuantum || _devID == DeviceQuantum2) && ibSplitReady)
    {
        string portStr = "Port " + to_string(_userInput._labelPort);
        string swSplitCmd = "module-type qsfp-split-2";
        if (_devID == DeviceQuantum2)
        {
            portStr = portStr + "/" + to_string(_userInput._splitPort);
            swSplitCmd = "port-type split-2";
        }
        throw MlxRegException(
          "%s is not splitted physically from switch side, Use this command to split it physically:\n"
          "interface ib <port/ports range> %s",
          portStr.c_str(), swSplitCmd.c_str());
    }
}

bool MlxlinkCommander::isIBSplitReady()
{
    u_int32_t max_port = maxLocalPort();
    for (u_int32_t localPort = 1; localPort <= max_port; localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue; // no reason to fail when one of the ports is not supported, such as in split mode.
        }
        if (getFieldValue("ib_port") == max_port / 2)
        {
            return true;
        }
    }
    return false;
}

u_int32_t MlxlinkCommander::calculatePanelPort(bool ibSplitReady)
{
    u_int32_t panelPort = _userInput._labelPort; // by default, the label port is equal to panel port if no split
    bool splitProvided = _devID == DeviceQuantum ? _userInput._splitProvided : _userInput._secondSplitProvided;
    u_int32_t split = _devID == DeviceQuantum ? _userInput._splitPort : _userInput._secondSplitPort;
    if (_devID == DeviceQuantum2)
    {
        // For Quantum-2, user should provide cage/port to access the ports in the cage
        // cage"panelPort"/port"_userInput._splitPort" is converted to label port according to the following equation:
        panelPort = 2 * panelPort + _userInput._splitPort - 2;
    }
    if (ibSplitReady)
    {
        // If split ready, then the panelPort mapping will be chaned
        if (!splitProvided)
        {
            panelPort = (panelPort * 2) - 1; // Access the main port (without providing the split)
                                             // For Quantum will be e.g (port/split): 2/1
                                             // For Quantum-2 will be e.g (cage/port/split): 1/2/1
        }
        else
        {
            if (split != 2)
            {
                throw MlxRegException("Invalid split number!");
            }
            panelPort = 2 * panelPort; // Access the second port (with providing the split)
                                       // For Quantum will be e.g (port/split): 2/2
                                       // For Quantum-2 will be e.g (cage/port/split): 1/2/2
        }
    }
    else if (splitProvided)
    {
        throw MlxRegException("Split mode is not ready!"
                              "\nThis command is used to set the split mode ready from switch side:"
                              "\nsystem profile ib split-ready");
    }

    return panelPort;
}

void MlxlinkCommander::getActualNumOfLanes(u_int32_t linkSpeedActive, bool extended)
{
    std::string rxtx;
    if (_protoActive == IB)
    {
        sendPrmReg(ACCESS_REG_PTYS, GET, "proto_mask=%d", _protoActive);

        _numOfLanes = getFieldValue("ib_link_width_oper");
    }
    else if (_protoActive == ETH)
    {
        if (_linkUP)
        {
            if (extended)
            {
                _numOfLanes = _mlxlinkMaps->_ExtETHSpeed2Lanes[linkSpeedActive];
            }
            else
            {
                _numOfLanes = _mlxlinkMaps->_ETHSpeed2Lanes[linkSpeedActive];
            }
        }
        else
        {
            sendPrmReg(ACCESS_REG_PMLP, GET);

            _numOfLanes = getFieldValue("width");
        }
    }

    sendPrmReg(ACCESS_REG_PMLP, GET);

    rxtx = getFieldValue("rxtx") == 0 ? "tx" : "rx";
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        _moduleLanesMapping[lane] = getFieldValue(rxtx + "_lane_" + to_string(lane));
    }
}

u_int32_t MlxlinkCommander::activeSpeed2gNum(u_int32_t mask, bool extended)
{
    if (extended)
    {
        return _mlxlinkMaps->_EthExtSpeed2gNum[mask];
    }
    return (_protoActive == IB) ? _mlxlinkMaps->_IBSpeed2gNum[mask] : _mlxlinkMaps->_ETHSpeed2gNum[mask];
}

string MlxlinkCommander::activeSpeed2Str(u_int32_t mask, bool extended, bool isXdrSlowActive)
{
    if (isXdrSlowActive)
    {
        return "NVLink-NDR";
    }
    if (extended)
    {
        return _mlxlinkMaps->_EthExtSpeed2Str[mask];
    }
    return (_isNVLINK)          ? _mlxlinkMaps->_NVLINKSpeed2Str[mask] :
           (_protoActive == IB) ? _mlxlinkMaps->_IBSpeed2Str[mask] :
                                  _mlxlinkMaps->_ETHSpeed2Str[mask];
}

void MlxlinkCommander::getCableParams()
{
    try
    {
        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_INFO_PAGE);

        _cableMediaType = getFieldValue("cable_type");
        _cableIdentifier = getFieldValue("cable_identifier");
        _cableTechnology = getFieldValue("cable_technology");
        _plugged = (_cableMediaType != UNPLUGGED);
        _cableAtten12G = (_cableMediaType == PASSIVE) ? getFieldValue("cable_attenuation_12g") : 0;
        _cableLen = getFieldValue("cable_length");
        _cablePN = getAscii("vendor_pn", 16);
        _cableSN = getAscii("vendor_sn", 16);
        _moduleTemp = getTemp(getFieldValue("temperature"));
        _cmisCable = isCMISCable(_cableIdentifier);
        _qsfpCable = isQsfpCable(_cableIdentifier);

        sendPrmReg(ACCESS_REG_PMLP, GET);

        _moduleNumber = getFieldValue("module_0");
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Getting cable parameters via PDDR raised the following exception: ") +
                               string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::inPrbsTestMode()
{
    try
    {
        bool res = checkPaosDown() && checkPpaosTestMode();
        return res;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Checking in PRBS test mode raised the following exception: ") + string(exc.what()) + string("\n");
    }
    return false;
}

bool MlxlinkCommander::checkGBPpaosDown()
{
    sendPrmReg(ACCESS_REG_PPAOS, GET);

    return getFieldValue("phy_status") != PAOS_UP;
}

bool MlxlinkCommander::checkPaosDown()
{
    if (_isGboxPort)
    {
        return checkGBPpaosDown();
    }
    else
    {
        sendPrmReg(ACCESS_REG_PAOS, GET);

        u_int32_t paosOperStatus = getFieldValue("oper_status");
        if (paosOperStatus == PAOS_DOWN)
        {
            return true;
        }
        return false;
    }
}

bool MlxlinkCommander::checkPpaosTestMode()
{
    sendPrmReg(ACCESS_REG_PPAOS, GET);

    u_int32_t ppaosPhyTestModeStatus = getFieldValue("phy_test_mode_status");
    if (ppaosPhyTestModeStatus == PHY_TEST_MODE_STATUS)
    {
        return true;
    }
    return false;
}

bool MlxlinkCommander::handleIBLocalPort(u_int32_t labelPort, bool ibSplitReady)
{
    bool isLabelPortValid = false;
    if ((_devID == DeviceQuantum2 || (_devID == DeviceQuantum && ibSplitReady)))
    {
        labelPort = 2 * labelPort - 1;
    }
    if ((_devID == DeviceQuantum2) && ibSplitReady)
    {
        labelPort = 2 * labelPort - 1;
    }
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue;
        }
        if (getFieldValue("ib_port") == labelPort)
        {
            fillIbPortGroupMap(localPort, labelPort, _userInput._setGroup, ibSplitReady);
            isLabelPortValid = true;
            break;
        }
    }
    return isLabelPortValid;
}

void MlxlinkCommander::handleAllGPULocalPorts(std::vector<string> labelPortsStr, bool skipException)
{
    u_int32_t labelPort = 0;
    std::vector<int> markLabelPorts(labelPortsStr.size(), 0);
    bool missingLabelPort = 0;
    u_int32_t i = 0;
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue;
        }
        auto it = std::find(labelPortsStr.begin(), labelPortsStr.end(), to_string(getFieldValue("ib_port")));
        if (it != labelPortsStr.end())
        {
            _localPortsPerGroup.push_back(PortGroup(localPort, getFieldValue("ib_port"), _userInput._setGroup, 0));
            markLabelPorts[std::distance(labelPortsStr.begin(), it)] = 1;
        }
    }
    for (i = 0; i < markLabelPorts.size(); i++)
    {
        if (markLabelPorts[i] == 0)
        {
            missingLabelPort = 1;
            break;
        }
    }
    if (!skipException && missingLabelPort)
    {
        strToUint32((char*)(labelPortsStr[i]).c_str(), labelPort);
        throw MlxRegException("Invalid port number %d!\n", labelPort);
    }
    sort(_localPortsPerGroup.begin(), _localPortsPerGroup.end());
}

void MlxlinkCommander::handleAllNewSwitchesLocalPorts(std::vector<string> labelPortsStr, bool skipException)
{
    u_int32_t labelPort = 0;
    std::vector<int> markLabelPorts(labelPortsStr.size(), 0);
    bool missingLabelPort = 0;
    u_int32_t i = 0;
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLLP, GET, "local_port=%d", localPort);
        }
        catch (MlxRegException& exp)
        {
            continue;
        }
        auto it = std::find(labelPortsStr.begin(), labelPortsStr.end(), to_string(getFieldValue("label_port")));
        if (it != labelPortsStr.end())
        {
            bool isFnmPort = false;
            try
            {
                isFnmPort = getFieldValue("is_fnm");
            }
            catch (...)
            {
            }

            _localPortsPerGroup.push_back(PortGroup(localPort, getFieldValue("label_port"), _userInput._setGroup,
                                                    getFieldValue("ipil_num"), getFieldValue("split_num") + 1,
                                                    isFnmPort));
            markLabelPorts[std::distance(labelPortsStr.begin(), it)] = 1;
        }
    }
    for (i = 0; i < markLabelPorts.size(); i++)
    {
        if (markLabelPorts[i] == 0)
        {
            missingLabelPort = 1;
            break;
        }
    }
    if (!skipException && missingLabelPort)
    {
        strToUint32((char*)(labelPortsStr[i]).c_str(), labelPort);
        throw MlxRegException("Invalid port number %d!\n", labelPort);
    }
    sort(_localPortsPerGroup.begin(), _localPortsPerGroup.end());
}

void MlxlinkCommander::handleAllEthLocalPorts(std::vector<string> labelPortsStr, bool spect2WithGb, bool skipException)
{
    u_int32_t labelPort = 0;
    std::vector<int> markLabelPorts(labelPortsStr.size(), 0);
    u_int32_t ind = 0;
    bool missingLabelPort = 0;
    u_int32_t i = 0;

    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_PMLP, GET, "local_port=%d", localPort);

            if (getFieldValue("width") == 0)
            {
                continue;
            }
        }
        catch (...)
        {
            break;
        }
        auto it = std::find(labelPortsStr.begin(), labelPortsStr.end(), to_string(getFieldValue("module_0") + 1));
        ind = std::distance(labelPortsStr.begin(), it);
        if (it != labelPortsStr.end() && !markLabelPorts[ind])
        {
            fillEthPortGroupMap(localPort, getFieldValue("module_0") + 1, _userInput._setGroup, getFieldValue("width"),
                                spect2WithGb);
            markLabelPorts[std::distance(labelPortsStr.begin(), it)] = 1;
        }
    }
    for (i = 0; i < markLabelPorts.size(); i++)
    {
        if (markLabelPorts[i] == 0)
        {
            missingLabelPort = 1;
            break;
        }
    }
    if (!skipException && missingLabelPort)
    {
        strToUint32((char*)(labelPortsStr[i]).c_str(), labelPort);
        throw MlxRegException("Invalid port number %d!\n", labelPort);
    }
    sort(_localPortsPerGroup.begin(), _localPortsPerGroup.end());
}

void MlxlinkCommander::fillEthPortGroupMap(u_int32_t localPort,
                                           u_int32_t labelPort,
                                           u_int32_t group,
                                           u_int32_t width,
                                           bool spect2WithGb)
{
    if (_ignorePortStatus)
    {
        if (!width)
        {
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
        }
    }
    if (spect2WithGb)
    {
        switch (width)
        {
            case 2:
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort + 1, labelPort, group, 2));
                break;
            case 4:
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
                break;
        }
    }
    else
    {
        try
        {
            sendPrmReg(ACCESS_REG_PLLP, GET, "local_port=%d", localPort);
        }
        catch (...)
        {
            return;
        }
        u_int32_t splitStat = getFieldValue("split_stat");
        if (splitStat == 0)
        {
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
        }
        else
        {
            int found = 0;
            for (int i = 0; i < (int)(pow(2.0, (double)splitStat)) || found < (int)(pow(2.0, (double)splitStat)); i++)
            {
                try
                {
                    sendPrmReg(ACCESS_REG_PMLP, GET, "local_port=%d", localPort + i);

                    if (getFieldValue("width") == 0)
                    {
                        continue;
                    }
                }
                catch (...)
                {
                    continue;
                }
                _localPortsPerGroup.push_back(PortGroup(localPort + i, labelPort, group, found + 1));
                found++;
            }
        }
    }
}

bool MlxlinkCommander::isIbLocalPortValid(u_int32_t localPort)
{
    bool valid = true;
    try
    {
        sendPrmReg(ACCESS_REG_PLIB, GET, "local_port=%d", localPort);
    }
    catch (MlxRegException& exp)
    {
        valid = false;
    }
    return valid;
}

void MlxlinkCommander::fillIbPortGroupMap(u_int32_t localPort, u_int32_t labelPort, u_int32_t group, bool splitReady)
{
    if (splitReady)
    {
        labelPort = (labelPort + 1) / 2;
        if (_devID == DeviceQuantum)
        {
            if (isIbLocalPortValid(localPort + 1))
            {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort + 1, labelPort, group, 2));
            }
            else
            {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            }
        }
        else if (_devID == DeviceQuantum2)
        {
            labelPort = (labelPort / 2) + 1;
            if (isIbLocalPortValid(localPort + 1))
            {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort + 1, labelPort, group, 1, 2));
            }
            else
            {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1, 1));
            }
            if (isIbLocalPortValid(localPort + 3))
            {
                _localPortsPerGroup.push_back(PortGroup(localPort + 2, labelPort, group, 2, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort + 3, labelPort, group, 2, 2));
            }
            else
            {
                _localPortsPerGroup.push_back(PortGroup(localPort + 2, labelPort, group, 2, 1));
            }
        }
    }
    else
    {
        if (_devID == DeviceQuantum)
        {
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
        }
        else if (_devID == DeviceQuantum2)
        {
            labelPort = (labelPort / 2) + 1;
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            _localPortsPerGroup.push_back(PortGroup(localPort + 2, labelPort, group, 2));
        }
    }
}

bool MlxlinkCommander::isSpect2WithGb()
{
    sendPrmReg(ACCESS_REG_MGPIR, GET);

    return getFieldValue("num_of_devices") > 0;
}

vector<string> MlxlinkCommander::localToPortsPerGroup(vector<u_int32_t> localPorts)
{
    u_int32_t labelPort = 0;
    vector<u_int32_t> labelPorts;
    vector<string> labelPortsStr;
    string regName = "";
    string labelPortField = "";

    switch (_devID)
    {
        case DeviceSpectrum2:
            regName = ACCESS_REG_PMLP;
            labelPortField = "module_0";
            break;
        case DeviceQuantum:
        case DeviceQuantum2:
        case DeviceGB100:
        case DeviceGR100:
            regName = ACCESS_REG_PLIB;
            labelPortField = "ib_port";
            break;
        case DeviceQuantum3:
            regName = ACCESS_REG_PLLP;
            labelPortField = "label_port";
            break;
        default:
            regName = ACCESS_REG_PMLP;
            labelPortField = "module_0";
    }

    for (vector<u_int32_t>::iterator it = localPorts.begin(); it != localPorts.end(); ++it)
    {
        try
        {
            sendPrmReg(regName, GET, "local_port=%d", *it);

            if (regName == ACCESS_REG_PMLP && getFieldValue("width") == 0)
            {
                continue;
            }

            labelPort = getFieldValue(labelPortField);
            labelPort = regName == ACCESS_REG_PMLP ? labelPort + 1 : labelPort;
        }
        catch (MlxRegException& exc)
        {
            continue;
        }
        labelPorts.push_back(labelPort);
    }

    sort(labelPorts.begin(), labelPorts.end());

    for (vector<u_int32_t>::iterator it = labelPorts.begin(); it != labelPorts.end(); it++)
    {
        if (!isIn(to_string(*it), labelPortsStr))
        {
            labelPortsStr.push_back(to_string(*it));
        }
    }

    return labelPortsStr;
}

void MlxlinkCommander::handleLabelPorts(std::vector<string> labelPortsStr, bool skipException)
{
    u_int32_t labelPort = 0;
    bool isLabelPortValid = false;
    if (labelPortsStr.size() > maxLocalPort() && !skipException)
    {
        throw MlxRegException("The number of ports is invalid");
    }
    bool ibSplitReady = (_devID == DeviceQuantum || _devID == DeviceQuantum2) ? isIBSplitReady() : false;
    bool spect2WithGb = (_devID == DeviceSpectrum2) ? isSpect2WithGb() : false;
    if (_devID == DeviceQuantum || _devID == DeviceQuantum2)
    {
        for (vector<string>::iterator it = labelPortsStr.begin(); it != labelPortsStr.end(); ++it)
        {
            strToUint32((char*)(*it).c_str(), labelPort);
            isLabelPortValid = handleIBLocalPort(labelPort, ibSplitReady);
            if (!isLabelPortValid && !skipException)
            {
                throw MlxRegException("Invalid port number %d!\n", labelPort);
            }
        }
    }
    else
    {
        if (_devID == DeviceSpectrum2)
        {
            handleAllEthLocalPorts(labelPortsStr, spect2WithGb, skipException);
        }
        else if (_devID == DeviceQuantum3 || _devID == DeviceSpectrum3 || _devID == DeviceSpectrum4 || _devID == DeviceSpectrum5 ||
                 _devID == DeviceSpectrum6)
        {
            handleAllNewSwitchesLocalPorts(labelPortsStr, skipException);
        }
        else if (dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            handleAllGPULocalPorts(labelPortsStr, skipException);
        }
    }
}

string MlxlinkCommander::getCableTechnologyStr(u_int32_t cableTechnology)
{
    string technologyStr = "N/A";
    if (_cmisCable)
    {
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[cableTechnology];
    }
    else if (_qsfpCable)
    {
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[(cableTechnology & 240) >> 4];
    }
    else
    {
        technologyStr = _mlxlinkMaps->_cableTechnologySfp[(cableTechnology & 15)];
    }
    return technologyStr;
}

string MlxlinkCommander::getCableTypeStr(u_int32_t cableType)
{
    string cableTypeStr = "N/A";
    cableTypeStr = getCableType(cableType);
    return cableTypeStr;
}

// Query functions

void MlxlinkCommander::prepareStaticInfoSection(bool valid)
{
    if (!_isSwControled)
    {
        u_int32_t cableVendor = getFieldValue("cable_vendor");
        string complianceStr = getComplianceLabel(getFieldValue("ethernet_compliance_code"),
                                                  getFieldValue("ext_ethernet_compliance_code"),
                                                  (cableVendor != NVIDIA && cableVendor != MELLANOX));
        u_int32_t cableLength = getFieldValue("cable_length");

        setPrintVal(_moduleInfoCmd, "Identifier", _plugged ? getCableIdentifier(_cableIdentifier) : "N/A",
                    ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Compliance", complianceStr, ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Cable Technology", _plugged ? getCableTechnologyStr(_cableTechnology) : "N/A",
                    ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Cable Type", getCableTypeStr(getFieldValue("cable_type")), ANSI_COLOR_RESET, true,
                    valid);
        setPrintVal(_moduleInfoCmd, "OUI", _plugged ? getOui(cableVendor) : "N/A", ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Vendor Name", getAscii("vendor_name", 16), ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Vendor Part Number", getAscii("vendor_pn", 16), ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Vendor Serial Number", getAscii("vendor_sn", 16), ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Rev", getVendorRev(getFieldValue("vendor_rev")), ANSI_COLOR_RESET, true, valid);
        setPrintVal(_moduleInfoCmd, "Wavelength [nm]",
                    (_cableMediaType == PASSIVE) ? "N/A" : to_string(getFieldValue("wavelength")), ANSI_COLOR_RESET,
                    true, valid);
        setPrintVal(_moduleInfoCmd, "Transfer Distance [m]", getCableLengthStr(cableLength, _cmisCable),
                    ANSI_COLOR_RESET, true, valid);
    }
}

void MlxlinkCommander::prepareAttenuationAndFwSection(bool valid)
{
    string cableAttenuation = "N/A";
    string attenuationTitle = "Attenuation (5g,7g,12g";
    bool passive = _cableMediaType == PASSIVE;

    if (_cmisCable)
    {
        attenuationTitle += ",25g";
    }

    if ((_cableIdentifier != IDENTIFIER_SFP) && (_cableIdentifier != IDENTIFIER_QSA))
    {
        if (passive)
        {
            cableAttenuation = getFieldStr("cable_attenuation_5g") + "," + getFieldStr("cable_attenuation_7g") + "," +
                               getFieldStr("cable_attenuation_12g");
            if (_cmisCable)
            {
                cableAttenuation += "," + getFieldStr("cable_attenuation_25g");
            }

            string attenuation53g = getFieldStr("cable_attenuation_53g");
            if (attenuation53g != "0")
            {
                attenuationTitle += ",53g";
                cableAttenuation += "," + attenuation53g;
            }
        }
    }
    attenuationTitle += ")[dB]";

    setPrintVal(_moduleInfoCmd, attenuationTitle, cableAttenuation, ANSI_COLOR_RESET, true, valid);
    if (!_isSwControled)
    {
        setPrintVal(_moduleInfoCmd, "FW Version", getModuleFwVersion(passive, getFieldValue("fw_version")),
                    ANSI_COLOR_RESET, true, valid);
    }
}

void MlxlinkCommander::preparePowerAndCdrSection(bool valid)
{
    string rxCdrState = "N/A";
    string txCdrState = "N/A";
    string powerClassStr = "N/A";
    string maxPowerStr = "N/A";
    if (!_isSwControled)
    {
        if (getFieldValue("rx_cdr_cap") > 0)
        {
            rxCdrState = getRxTxCDRState(getFieldValue("rx_cdr_state"), _numOfLanes);
        }
        if (getFieldValue("tx_cdr_cap") > 0)
        {
            txCdrState = getRxTxCDRState(getFieldValue("tx_cdr_state"), _numOfLanes);
        }

        powerClassStr = getPowerClassStr(_mlxlinkMaps, _cableIdentifier, getFieldValue("cable_power_class"));
        maxPowerStr = getMaxPowerStr(getFieldValue("max_power"));
    }

    setPrintVal(_moduleInfoCmd, "Digital Diagnostic Monitoring", _ddmSupported ? "Yes" : "No", ANSI_COLOR_RESET, true,
                valid);
    setPrintVal(_moduleInfoCmd, "Power Class", (_plugged && _cableMediaType != PASSIVE) ? powerClassStr : "N/A",
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "MAX Power", (_plugged && _cableMediaType != PASSIVE) ? maxPowerStr : "N/A",
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "CDR RX", _plugged ? rxCdrState : "N/A", ANSI_COLOR_RESET, true, valid, true);
    setPrintVal(_moduleInfoCmd, "CDR TX", _plugged ? txCdrState : "N/A", ANSI_COLOR_RESET, true, valid, true);

    // This statement is here for backward compatibility purposes only
    setPrintVal(_moduleInfoCmd, "LOS Alarm", "N/A", ANSI_COLOR_RESET, true, valid);
}

void MlxlinkCommander::prepareDDMSection(bool valid, bool isModuleExtSupported)
{
    std::vector<float> rxPowerLane, txPowerLane, biasCurrentLane;
    float rxPowerHighTH, rxPowerLowTH, txPowerHighTH, txPowerLowTH;
    string biasStr = "N/A", rxPowerStr = "N/A", txPowerStr = "N/A";

    u_int32_t tempNum = getFieldValue("temperature");
    string temp = getTemp(tempNum);
    string tempHighTH = getTemp(getFieldValue("temperature_high_th"));
    string tempLowTH = getTemp(getFieldValue("temperature_low_th"));

    float voltage = getFieldValue("voltage") / 10.0;
    float voltageHighTH = getFieldValue("voltage_high_th") / 10.0;
    float voltageLowTH = getFieldValue("voltage_low_th") / 10.0;

    rxPowerHighTH = getPower(getFieldValue("rx_power_high_th"), isModuleExtSupported);
    rxPowerLowTH = getPower(getFieldValue("rx_power_low_th"), isModuleExtSupported);
    txPowerHighTH = getPower(getFieldValue("tx_power_high_th"), isModuleExtSupported);
    txPowerLowTH = getPower(getFieldValue("tx_power_low_th"), isModuleExtSupported);
    if (isModuleExtSupported)
    {
        rxPowerHighTH = convertFloatPrec(rxPowerHighTH);
        rxPowerLowTH = convertFloatPrec(rxPowerLowTH);
        txPowerHighTH = convertFloatPrec(txPowerHighTH);
        txPowerLowTH = convertFloatPrec(txPowerLowTH);
    }

    float txMultiplier = 1;
    try
    {
        txMultiplier = pow(2, getFieldValue("tx_bias_scaling_factor"));
    }
    catch (const std::exception& e)
    {
        // If the field does not exist, set the multiplier to 1
        // txMultiplier = 1;
    }

    float biasLowTH = getFieldValue("tx_bias_low_th") * txMultiplier / 500.0;
    float biasHighTH = getFieldValue("tx_bias_high_th") * txMultiplier / 500.0;

    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        string laneStr = to_string(_moduleLanesMapping[lane]);
        rxPowerLane.push_back(getPower(getFieldValue("rx_power_lane" + laneStr), isModuleExtSupported));
        txPowerLane.push_back(getPower(getFieldValue("tx_power_lane" + laneStr), isModuleExtSupported));
        biasCurrentLane.push_back(getFieldValue("tx_bias_lane" + laneStr) * txMultiplier / 500.0);
    }

    rxPowerStr =
        getValueAndThresholdsStr<string, float>(getStringFromVector(rxPowerLane), rxPowerLowTH, rxPowerHighTH);
    txPowerStr =
        getValueAndThresholdsStr<string, float>(getStringFromVector(txPowerLane), txPowerLowTH, txPowerHighTH);
    biasStr = getValueAndThresholdsStr<string, float>(getStringFromVector(biasCurrentLane), biasLowTH, biasHighTH);

    setPrintVal(_moduleInfoCmd, "Temperature [C]",
                getValueAndThresholdsStr<string, string>(temp, tempLowTH, tempHighTH), ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Voltage [mV]",
                getValueAndThresholdsStr<float, float>(voltage, voltageLowTH, voltageHighTH), ANSI_COLOR_RESET, true,
                valid);
    setPrintVal(_moduleInfoCmd, "Bias Current [mA]", biasStr, ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Rx Power Current [dBm]", rxPowerStr, ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Tx Power Current [dBm]", txPowerStr, ANSI_COLOR_RESET, true, valid);
}

string MlxlinkCommander::getValuesOfActiveLanes(const string& row, bool moduleLanes)
{
    string newValue = row;

    auto valuesPerLane = MlxlinkRecord::split(newValue, ",");
    vector<string> validValues;
    if (valuesPerLane.size() > 1)
    {
        for (u_int32_t i = 0; i < _numOfLanes; i++)
        {
            if (moduleLanes)
            {
                validValues.push_back(valuesPerLane[_moduleLanesMapping[i]]);
            }
            else
            {
                validValues.push_back(valuesPerLane[i]);
            }
        }

        newValue = getStringFromVector(validValues);
    }

    return newValue;
}

void MlxlinkCommander::pushSnrModuleInfoFields(bool valid)
{
    vector<ModuleField> fieldsToQuery;
    string snrMediaLanes = "N/A";
    string snrHostLanes = "N/A";

    try
    {
        vector<AmberField> moduleInfoFields = _amberCollector->getExtModuleStatus();
        snrMediaLanes = AmberField::getValueFromFields(moduleInfoFields, "snr_media_lane", false);
        snrHostLanes = AmberField::getValueFromFields(moduleInfoFields, "snr_host_lane", false);

        if (snrMediaLanes.find("N/A") != string::npos)
        {
            snrMediaLanes = "N/A";
        }
        else
        {
            findAndReplace(snrMediaLanes, "_", ",");
            snrMediaLanes = getValuesOfActiveLanes(snrMediaLanes, true);
        }

        if (snrHostLanes.find("N/A") != string::npos)
        {
            snrHostLanes = "N/A";
        }
        else
        {
            findAndReplace(snrHostLanes, "_", ",");
            snrHostLanes = getValuesOfActiveLanes(snrHostLanes, true);
        }
    }
    catch (MlxRegException& excep)
    {
    }

    setPrintVal(_moduleInfoCmd, "SNR Media Lanes [dB]", snrMediaLanes, ANSI_COLOR_RESET, true, valid && _ddmSupported,
                true);
    setPrintVal(_moduleInfoCmd, "SNR Host Lanes [dB]", snrHostLanes, ANSI_COLOR_RESET, true, valid && _ddmSupported,
                true);
}

void MlxlinkCommander::prepareBerModuleInfo(bool valid, const vector<AmberField>& moduleInfoFields)
{
    vector<ModuleField> fieldsToQuery;

    fieldsToQuery.push_back(ModuleField("IB Cable Width", "ib_width", true, false, false));
    fieldsToQuery.push_back(ModuleField("Memory Map Revision", "Memory_map_rev", false, false, false));
    fieldsToQuery.push_back(ModuleField("Linear Direct Drive", "linear_direct_drive", false, false, false));
    fieldsToQuery.push_back(ModuleField("Cable Breakout", "cable_breakout", true, false, false));
    fieldsToQuery.push_back(ModuleField("SMF Length", "smf_length", false, false, false));
    fieldsToQuery.push_back(ModuleField("Cable Rx AMP", "cable_rx_amp", false, false, false));
    fieldsToQuery.push_back(ModuleField("Cable Rx Emphasis", "cable_rx_pre_emphasis", false, false, false));
    fieldsToQuery.push_back(ModuleField("Cable Rx Post Emphasis", "cable_rx_post_emphasis", false, false, false));
    fieldsToQuery.push_back(ModuleField("Cable Tx Equalization", "cable_tx_equalization", false, false, false));
    fieldsToQuery.push_back(ModuleField("Wavelength Tolerance", "wavelength_tolerance", false, false, false));
    fieldsToQuery.push_back(ModuleField("Module State", "Module_st", false, false, false));
    fieldsToQuery.push_back(ModuleField("DataPath state [per lane]", "Dp_st_lane", true, true, true));
    fieldsToQuery.push_back(ModuleField("Rx Output Valid [per lane]", "rx_output_valid", true, true, true));
    fieldsToQuery.push_back(ModuleField("Nominal bit rate", "Nominal_Bit_Rate", false, false, false));
    fieldsToQuery.push_back(ModuleField("Rx Power Type", "Rx_Power_Type", false, false, false));
    fieldsToQuery.push_back(ModuleField("Manufacturing Date", "Date_Code", false, false, false));
    fieldsToQuery.push_back(
      ModuleField("Active Set Host Compliance Code", "Active_set_host_compliance_code", false, false, false));
    fieldsToQuery.push_back(
      ModuleField("Active Set Media Compliance Code", "Active_set_media_compliance_code", false, false, false));
    fieldsToQuery.push_back(ModuleField("Error Code Response", "error_code_response", false, false, false));
    fieldsToQuery.push_back(ModuleField("Module FW Fault", "Mod_fw_fault", false, false, true));
    fieldsToQuery.push_back(ModuleField("DataPath FW Fault", "Dp_fw_fault", false, false, true));
    fieldsToQuery.push_back(ModuleField("Tx Fault [per lane]", "tx_fault", true, true, true));
    fieldsToQuery.push_back(ModuleField("Tx LOS [per lane]", "tx_los", true, true, true));
    fieldsToQuery.push_back(ModuleField("Tx CDR LOL [per lane]", "tx_cdr_lol", true, true, true));
    fieldsToQuery.push_back(ModuleField("Rx LOS [per lane]", "rx_los", true, true, true));
    fieldsToQuery.push_back(ModuleField("Rx CDR LOL [per lane]", "rx_cdr_lol", true, true, true));
    fieldsToQuery.push_back(ModuleField("Tx Adaptive EQ Fault [per lane]", "tx_ad_eq_fault", true, true, true));

    pushSnrModuleInfoFields(valid);

    string fieldValue = "";

    for (auto it = fieldsToQuery.begin(); it != fieldsToQuery.end(); it++)
    {
        fieldValue = AmberField::getValueFromFields(moduleInfoFields, it->amberName, !it->perLane);
        if (it->multiVal)
        {
            findAndReplace(fieldValue, "_", ",");
        }
        if (it->perLane)
        {
            fieldValue = getValuesOfActiveLanes(fieldValue, true);
        }

        if ((it->uiName == "Cable Rx Emphasis") && _cmisCable)
        {
            it->uiName += " (Pre)";
        }
        setPrintVal(_moduleInfoCmd, it->uiName, fieldValue, ANSI_COLOR_RESET, true,
                    it->requireDdm ? valid && _ddmSupported : valid, it->perLane);
    }
}

bool MlxlinkCommander::checkIfModuleExtSupported()
{
    bool isModuleExtSupported = false;

    sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d , module_info_ext=0", PDDR_MODULE_INFO_PAGE);
    float rxPowerHighTH_sec = getFieldValue("rx_power_high_th");

    sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d , module_info_ext=1", PDDR_MODULE_INFO_PAGE);
    float rxPowerHighTH_fst = getFieldValue("rx_power_high_th");

    if (rxPowerHighTH_sec != rxPowerHighTH_fst)
    {
        isModuleExtSupported = true;
    }

    return isModuleExtSupported;
}

bool MlxlinkCommander::checkDPNvSupport()
{
    try
    {
        sendPrmReg(ACCESS_REG_MCAM, GET);
        // The MCAM, much like the PCAM is written upside-down
        u_int32_t capMask = getFieldValue("mng_feature_cap_mask[1]");
        return capMask & MCAM_CAP_MASK_DPNV;
    }
    catch (...)
    {
    }
    return false;
}

void MlxlinkCommander::showModuleInfo()
{
    if (_isSwControled)
    {
        _allUnhandledErrors += string("No plugged cable detected\n");
        return;
    }

    try
    {
        gearboxBlock(MODULE_INFO_FLAG);

        sendPrmReg(ACCESS_REG_PMAOS, GET, "module=%d,slot_index=%d", _moduleNumber, _slotIndex);

        u_int32_t oper_status = getFieldValue("oper_status");
        bool isModuleExtSupported = false;
        bool valid = (_cableMediaType != UNIDENTIFIED) && _plugged;
        setPrintTitle(_moduleInfoCmd, "Module Info",
                      _productTechnology >= PRODUCT_16NM ? MODULE_INFO_AMBER : MODULE_INFO_LAST);
        if (!_isSwControled)
        {
            isModuleExtSupported = checkIfModuleExtSupported();
            prepareDDMSection(valid, isModuleExtSupported);
        }

        prepareStaticInfoSection(valid);
        prepareAttenuationAndFwSection(valid);
        preparePowerAndCdrSection(valid);
        if (_productTechnology >= PRODUCT_16NM)
        {
            preparePrtlSection();
        }

        initAmBerCollector();
        _amberCollector->init();
        vector<AmberField> moduleInfoFields = _amberCollector->getModuleStatus();

        prepareBerModuleInfo(valid, moduleInfoFields);

        cout << _moduleInfoCmd;

        if (oper_status != 1)
        {
            MlxlinkRecord::printWar(
              "Warning: Cannot get module EEPROM information, module operation status is not 'plugged and enabled'",
              _jsonRoot);
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing Module Info via PDDR raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::preparePrtlSection()
{
    if (_userInput._advancedMode)
    {
        char rttFrmt[64] = "";
        bool isRttSupported = false;
        u_int16_t asicLatency = 0;
        u_int16_t moduleLatency = 0;
        bool valid = true;

        try
        {
            sendPrmReg(ACCESS_REG_PRTL, GET);
        }
        catch (const std::exception& exc)
        {
            valid = false;
        }

        if (valid)
        {
            u_int32_t rttLatencyInt = getFieldValue("round_trip_latency");
            isRttSupported = rttLatencyInt && rttLatencyInt != 0xffffff;
            asicLatency = (u_int16_t)getFieldValue("local_phy_latency");
            moduleLatency = (u_int16_t)getFieldValue("local_mod_dp_latency");

            float rttLatency = ((float)rttLatencyInt) / ((float)getFieldValue("latency_res"));
            snprintf(rttFrmt, sizeof(rttFrmt), "%0.2f", rttLatency);
        }

        setPrintVal(_moduleInfoCmd, "Intra-ASIC Latency [ns]", to_string(asicLatency), ANSI_COLOR_RESET, true,
                    valid && isRttSupported);
        setPrintVal(_moduleInfoCmd, "Module Datapath Latency [ns]", to_string(moduleLatency), ANSI_COLOR_RESET, true,
                    asicLatency != 0);
        setPrintVal(_moduleInfoCmd, "Round Trip Latency [ns]", string(rttFrmt), ANSI_COLOR_RESET, true,
                    moduleLatency != 0);
    }
}

string MlxlinkCommander::getCompliaceLabelForCIMIS(u_int32_t hostCompliance, u_int32_t mediaCompliance)
{
    string complianceStr = "N/A";
    string hostComplianceStr = "";
    string mediaComplianceStr = "";

    switch (_cableMediaType)
    {
        case PASSIVE:
            hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
            break;

        case ACTIVE:
            mediaComplianceStr = _mlxlinkMaps->_activeCableCompliance[mediaCompliance];
            hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
            break;

        case OPTICAL_MODULE:
            if (_cableTechnology == TECHNOLOGY_850NM_VCSEL)
            {
                mediaComplianceStr = _mlxlinkMaps->_mmfCompliance[mediaCompliance];
            }
            else if (_cableTechnology >= TECHNOLOGY_1310NM_VCSEL && _cableTechnology <= TECHNOLOGY_1550NM_EML)
            {
                mediaComplianceStr = _mlxlinkMaps->_smfCompliance[mediaCompliance];
            }
            hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
            break;
    }
    complianceStr = hostComplianceStr;
    if (!mediaComplianceStr.empty())
    {
        complianceStr += "," + mediaComplianceStr;
    }
    return complianceStr;
}

string MlxlinkCommander::getComplianceLabel(u_int32_t compliance, u_int32_t extCompliance, bool ignoreExtBitChk)
{
    string complianceLabel = "N/A";

    if (_cmisCable)
    {
        complianceLabel = getCompliaceLabelForCIMIS(extCompliance, compliance);
    }
    else if (_protoActive == ETH)
    {
        if (_qsfpCable)
        {
            if (compliance)
            {
                complianceLabel = getCompliance(compliance, _mlxlinkMaps->_cableComplianceQsfp, true);
                if (ignoreExtBitChk || (compliance & QSFP_ETHERNET_COMPLIANCE_CODE_EXT))
                {
                    complianceLabel += !complianceLabel.empty() ? "," : "";
                    complianceLabel += getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
                }
            }
            else if (ignoreExtBitChk)
            {
                complianceLabel = getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
            }
        }
        else if (_cableIdentifier == IDENTIFIER_SFP || _cableIdentifier == IDENTIFIER_QSA)
        {
            if (compliance)
            {
                complianceLabel = getCompliance(compliance, _mlxlinkMaps->_cableComplianceSfp, true);
            }
            if (extCompliance)
            {
                complianceLabel = (compliance ? complianceLabel + ", " : "") +
                                  getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
            }
        }
    }
    return complianceLabel;
}

string MlxlinkCommander::getSltpFieldStr(const PRM_FIELD& field)
{
    string fieldStr = getFieldStr(field.prmField, 0, 0, false, true);
    if (field.isSigned)
    {
        fieldStr = to_string(readSigned(getFieldValue(field.prmField, 0, 0, false, true), getFieldSize(field.prmField)));
    }
    return MlxlinkRecord::addSpace(fieldStr, field.uiField.size() + 1, false);
}

void MlxlinkCommander::prepareSltpEdrHdrGen(vector<vector<string>>& sltpLanes, u_int32_t laneNumber)
{
    map<u_int32_t, PRM_FIELD> sltpParam = _mlxlinkMaps->_SltpEdrParams;
    if (_productTechnology == PRODUCT_16NM)
    {
        sltpParam = _mlxlinkMaps->_SltpHdrParams;
    }

    for (auto const& param : sltpParam)
    {
        if ((param.second.fieldAccess & FIELD_ACCESS_R) ||
            (_userInput._advancedMode && (param.second.fieldAccess & FIELD_ACCESS_ADVANCED)))
        {
            sltpLanes[laneNumber].push_back(getSltpFieldStr(param.second));
        }
    }
}

void MlxlinkCommander::prepareSltpNdrGen(std::vector<std::vector<string>>& sltpLanes, u_int32_t laneNumber)
{
    u_int32_t activeSpeed = _protoActive == IB ? _activeSpeed : _activeSpeedEx;
    activeSpeed = activeSpeed == 0 ? _laneSpeedFromPptt : activeSpeed;
    for (auto const& param : _mlxlinkMaps->_SltpNdrParams)
    {
        if ((param.second.validationMask & activeSpeed) || _userInput._pcie)
        {
            sltpLanes[laneNumber].push_back(getSltpFieldStr(param.second));
        }
    }
}

void MlxlinkCommander::prepareSltpXdrGen(std::vector<std::vector<string>>& sltpLanes, u_int32_t laneNumber)
{
    u_int32_t activeSpeed = _protoActive == IB ? _activeSpeed : _activeSpeedEx;
    activeSpeed = activeSpeed == 0 ? _laneSpeedFromPptt : activeSpeed;
    for (auto const& param : _mlxlinkMaps->_SltpXdrParams)
    {
        if ((param.second.validationMask & activeSpeed) || _userInput._pcie)
        {
            sltpLanes[laneNumber].push_back(getSltpFieldStr(param.second));
        }
    }
}

template<typename T, typename Q>
string MlxlinkCommander::getValueAndThresholdsStr(T value, Q lowTH, Q highTH)
{
    stringstream out;
    if (_ddmSupported)
    {
        out << value << " [" << lowTH << ".." << highTH << "]";
    }
    else
    {
        out << "N/A";
    }
    return out.str();
}

void MlxlinkCommander::runningVersion()
{
    setPrintTitle(_toolInfoCmd, "Tool Information", TOOL_INFORMAITON_INFO_LAST, !_prbsTestMode);
    setPrintVal(_toolInfoCmd, "Firmware Version", getFwVersion(), ANSI_COLOR_GREEN, true, !_prbsTestMode);
    setPrintVal(_toolInfoCmd, "amBER Version", AMBER_VERSION, ANSI_COLOR_GREEN, _productTechnology >= PRODUCT_16NM,
                !_prbsTestMode);
    setPrintVal(_toolInfoCmd, PKG_NAME " Version", PKG_VER, ANSI_COLOR_GREEN, true, !_prbsTestMode);
}

void MlxlinkCommander::operatingInfoPage()
{
    try
    {
        getPddrOperInfo();
        int loopbackMode = (_phyMngrFsmState != PHY_MNGR_DISABLED) ? _loopbackMode : -1;
        u_int32_t ethAnFsmState = getFieldValue("eth_an_fsm_state");
        u_int32_t ib_phy_fsm_state = getFieldValue("ib_phy_fsm_state");
        string color =
          MlxlinkRecord::state2Color(_phyMngrFsmState == PHY_MNGR_RX_DISABLE ? YELLOW : (STATUS_COLOR)_phyMngrFsmState);
        _protoActive = getFieldValue("proto_active");
        if (_protoActive == NVLINK)
        {
            _isNVLINK = true;
            _protoActive = IB;
        }

        _linkUP = (_phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);
        _portPolling = _phyMngrFsmState == PHY_MNGR_POLLING;
        _protoCapability = getFieldValue("cable_ext_eth_proto_cap");

        if (_protoActive == IB)
        {
            _protoCapability = getFieldValue("cable_link_speed_cap");
            _activeSpeed = getFieldValue("link_speed_active");
            _protoAdmin = (_phyMngrFsmState != 0) ? getFieldValue("core_to_phy_link_proto_enabled") :
                                                    getFieldValue("phy_manager_link_proto_enabled");
        }

        getPtys();
        bool extended = _activeSpeedEx && _protoAdminEx;
        _isPam4Speed = isPAM4Speed(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive, extended);
        _linkSpeed = extended ? _activeSpeedEx : _activeSpeed;
        _speedBerCsv = activeSpeed2gNum(_linkSpeed, extended);
        _speedStrG = activeSpeed2Str(_linkSpeed, extended, _isXdrSlowActive);
        getActualNumOfLanes(_linkSpeed, extended);

        setPrintTitle(_operatingInfoCmd, "Operational Info", PDDR_OPERATIONAL_INFO_LAST, !_prbsTestMode);

        setPrintVal(_operatingInfoCmd, "State", getStrByValue(_phyMngrFsmState, _mlxlinkMaps->_pmFsmState), color, true,
                    !_prbsTestMode);
        setPrintVal(_operatingInfoCmd, "Physical state",
                    _protoActive == ETH ? getStrByValue(ethAnFsmState, _mlxlinkMaps->_ethANFsmState) :
                                          getStrByValue(ib_phy_fsm_state, _mlxlinkMaps->_ibPhyFsmState),
                    color, !_prbsTestMode);
        setPrintVal(_operatingInfoCmd, "Speed", _speedStrG, color, !_prbsTestMode, _linkUP);
        setPrintVal(_operatingInfoCmd, "Width", to_string(_numOfLanes) + "x", color, !_prbsTestMode, _linkUP);
        setPrintVal(_operatingInfoCmd, "FEC", getStrByValue(_fecActive, _mlxlinkMaps->_fecModeActive),
                    _mlxlinkMaps->_fecModeActive[_fecActive] == "" ? MlxlinkRecord::state2Color(0) : color,
                    !_prbsTestMode, _linkUP);
        setPrintVal(_operatingInfoCmd, "Loopback Mode", _mlxlinkMaps->_loopbackModeList[loopbackMode].second,
                    getLoopbackColor(loopbackMode), true, !_prbsTestMode && loopbackMode != -1);
        setPrintVal(_operatingInfoCmd, "Auto Negotiation", _mlxlinkMaps->_anDisableList[_anDisable] + _speedForce,
                    getAnDisableColor(_anDisable), true, !_prbsTestMode);

        // Checking cable DDM capability
        if (!_isSwControled && (_userInput._networkCmds != 0 || _userInput._ddm || _userInput._dump ||
                                _userInput._write || _userInput._read || _userInput.isModuleConfigParamsProvided ||
                                _userInput.isPrbsSelProvided || _userInput._csvBer != ""))
        {
            sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_INFO_PAGE);
            
            _temperature = getFieldValue("temperature");
            _ddmSupported = bool(_numOfLanes);
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string(exc.what()));
    }
}

bool MlxlinkCommander::isBackplane()
{
    bool isBackplane = false;
    try
    {
        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_INFO_PAGE);
        isBackplane = (getFieldValue("cable_identifier") == IDENTIFIER_BACKPLANE);
    }
    catch (const std::exception& e)
    {
    }

    return isBackplane;
}

void MlxlinkCommander::supportedInfoPage()
{
    try
    {
        setPrintTitle(_supportedInfoCmd, HEADER_SUPPORTED_INFO, PDDR_SUPPORTED_INFO_LAST, !_prbsTestMode);
        u_int32_t speeds_mask = _protoAdminEx ? _protoAdminEx : _protoAdmin;
        string supported_speeds = SupportedSpeeds2Str(_protoActive, speeds_mask, (bool)_protoAdminEx, _isXdrSlowActive);
        string color = MlxlinkRecord::supported2Color(supported_speeds);
        stringstream value;
        value << "0x" << std::hex << setfill('0') << setw(8) << speeds_mask << " (" << supported_speeds << ")"
              << setfill(' ');
        string extStr = "";
        if (_protoCapabilityEx && _protoActive == ETH)
        {
            extStr = " (Ext.)";
        }
        string title = "Enabled Link Speed" + extStr;
        setPrintVal(_supportedInfoCmd, title, value.str(), color, true, !_prbsTestMode, true);
        // Supported cable speed
        supported_speeds = SupportedSpeeds2Str(_protoActive, _protoCapability, _protoCapabilityEx);
        color = MlxlinkRecord::supported2Color(supported_speeds);
        value.str("");
        value.clear();
        value << "0x" << std::hex << setfill('0') << setw(8) << _protoCapability << " (" << supported_speeds << ")"
              << setfill(' ');
        title = "Supported Cable Speed" + extStr;
        if (isBackplane() || _isSwControled)
        {
            setPrintVal(_supportedInfoCmd, title, "N/A", ANSI_COLOR_RED, true, !_prbsTestMode, true);
        }
        else
        {
            setPrintVal(_supportedInfoCmd, title, value.str(), color, true, !_prbsTestMode, true);
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string(exc.what()));
    }
}

void MlxlinkCommander::troubInfoPage()
{
    try
    {
        sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d,group_opcode=%d", PDDR_TROUBLESHOOTING_INFO_PAGE,
                   _groupOpcode);

        u_int32_t monitorOpcode = getFieldValue("monitor_opcode");
        string color = status2Color(monitorOpcode);
        setPrintTitle(_troubInfoCmd, "Troubleshooting Info", PDDR_TRUOBLESHOOTING_INFO_LAST, !_prbsTestMode);

        if (monitorOpcode == CABLE_IS_UNPLUGGED)
        {
            _mngCableUnplugged = true;
        }
        stringstream statusOp;
        statusOp << std::dec << monitorOpcode;
        setPrintVal(_troubInfoCmd, "Status Opcode", statusOp.str(), color, true, !_prbsTestMode);

        string groupOpcode = getGroupStr(monitorOpcode);
        setPrintVal(_troubInfoCmd, "Group Opcode", groupOpcode, color, true, !_prbsTestMode);

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
        setPrintVal(_troubInfoCmd, "Recommendation", message, color, true, !_prbsTestMode);
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string(exc.what()));
    }
}

void MlxlinkCommander::showPddr()
{
    try
    {
        operatingInfoPage();
        supportedInfoPage();
        troubInfoPage();
        runningVersion();
        if (_prbsTestMode && !_userInput._showMultiPortInfo)
        {
            showTestMode();
        }
        else if (!_userInput._showMultiPortInfo && !_userInput._showMultiPortModuleInfo)
        {
            std::cout << _operatingInfoCmd;
            std::cout << _supportedInfoCmd;
            std::cout << _troubInfoCmd;
            std::cout << _toolInfoCmd;
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string("Showing PDDR raised the following exception: \n") + string(exc.what()));
    }
}

void MlxlinkCommander::getPtys()
{
    sendPrmReg(ACCESS_REG_PTYS, GET, "proto_mask=%d", _protoActive);

    if (_protoActive == ETH)
    {
        _activeSpeedEx = getFieldValue("ext_eth_proto_oper");
        _activeSpeed = getFieldValue("eth_proto_oper");
        _protoAdmin = getFieldValue("eth_proto_admin");
        _protoAdminEx = getFieldValue("ext_eth_proto_admin");
        _protoCapabilityEx = getFieldValue("ext_eth_proto_capability");
        _deviceCapability =
          _protoCapabilityEx ? getFieldValue("ext_eth_proto_capability") : getFieldValue("eth_proto_capability");
    }
    else
    {
        _deviceCapability = getFieldValue("ib_proto_capability");
        try
        {
            if (getStrByValue(_phyMngrFsmState, _mlxlinkMaps->_pmFsmState) == "Active" &&
                getFieldValue("xdr_2x_slow_active"))
            {
                _isXdrSlowActive = true;
            }
        }
        catch (const std::exception& e)
        {
        }
    }

    _anDisable = getFieldValue("an_disable_admin");
    if (_anDisable)
    {
        u_int32_t val = _protoAdminEx ? _protoAdminEx : _protoAdmin;
        _speedForce = " - " + SupportedSpeeds2Str(_protoActive, val, (bool)_protoAdminEx);
    }
}

void MlxlinkCommander::getPddrOperInfo()
{
    sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_OPERATIONAL_INFO_PAGE);
    _phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");
    _loopbackMode = getFieldValue("loopback_mode");
    _fecActive = getFieldValue("fec_mode_active");
}

void MlxlinkCommander::showTestMode()
{
    std::map<std::string, std::string> pprtMap = getPprt();
    std::map<std::string, std::string> ppttMap = getPptt();

    setPrintTitle(_testModeInfoCmd, "Test Mode Info", TEST_MODE_INFO_LAST);
    setPrintVal(_testModeInfoCmd, "RX PRBS Mode", pprtMap["pprtPrbsMode"]);
    setPrintVal(_testModeInfoCmd, "TX PRBS Mode", ppttMap["ppttPrbsMode"]);
    setPrintVal(_testModeInfoCmd, "RX Lane Rate", pprtMap["pprtLaneRate"]);
    setPrintVal(_testModeInfoCmd, "TX Lane Rate", ppttMap["ppttLaneRate"]);
    setPrintVal(_testModeInfoCmd, "RX Modulation", pprtMap["pprtModulation"]);
    setPrintVal(_testModeInfoCmd, "TX Modulation", ppttMap["ppttModulation"]);
    setPrintVal(_testModeInfoCmd, "Tuning Status", pprtMap["pprtTuningStatus"]);
    setPrintVal(_testModeInfoCmd, "Lock Status", pprtMap["pprtLockStatus"]);

    cout << _testModeInfoCmd;
}

int MlxlinkCommander::prbsModeToMask(const string& mode)
{
    // SQUARE_WAVE and SQUARE_WAVEA have the same enum
    string modeToCheck = mode;
    if (mode == "SQUARE_WAVE")
    {
        modeToCheck += "A";
    }
    int mask = PRBS31;
    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
         it != _mlxlinkMaps->_prbsModesList.end();
         it++)
    {
        if (modeToCheck == it->second)
        {
            mask = it->first;
            break;
        }
    }
    return mask;
}

string MlxlinkCommander::prbsMaskToMode(u_int32_t mask, u_int32_t modeSelector)
{
    string val = "N/A";
    val = _mlxlinkMaps->_prbsModesList[mask];
    if (modeSelector == PRBS_RX && mask == SQUARE_WAVEA)
    {
        val = deleteLastChar(val); // return SQUARE_WAVE without A
    }
    return val;
}

std::map<std::string, std::string> MlxlinkCommander::getPprt()
{
    std::map<string, string> pprtMap;

    sendPrmReg(ACCESS_REG_PPRT, GET, "e=%d", PPRT_PPTT_ENABLE);

    u_int32_t statusMask = getFieldValue("prbs_lock_status");
    statusMask |= (getFieldValue("prbs_lock_status_ext") << 4);

    pprtMap["pprtPrbsMode"] = prbsMaskToMode(getFieldValue("prbs_mode_admin"), PRBS_RX);
    pprtMap["pprtLaneRate"] = getStrByValue(getFieldValue("lane_rate_oper"), _mlxlinkMaps->_prbsLaneRateList);
    pprtMap["pprtModulation"] = getStrByValue(getFieldValue("modulation"), _mlxlinkMaps->_prbsModulation);
    pprtMap["pprtTuningStatus"] =
      getStrByValue(getFieldValue("prbs_rx_tuning_status"), _mlxlinkMaps->_prbsRxTuningStatus);
    pprtMap["pprtLockStatus"] = prbsMaskToLockStatus(statusMask, _numOfLanes);

    return pprtMap;
}

std::map<std::string, std::string> MlxlinkCommander::getPptt()
{
    std::map<string, string> ppttMap;

    sendPrmReg(ACCESS_REG_PPTT, GET, "e=%d", PPRT_PPTT_ENABLE);

    ppttMap["ppttPrbsMode"] = prbsMaskToMode(getFieldValue("prbs_mode_admin"), PRBS_TX);
    ppttMap["ppttLaneRate"] = getStrByValue(getFieldValue("lane_rate_admin"), _mlxlinkMaps->_prbsLaneRateList);
    ppttMap["ppttModulation"] = getStrByValue(getFieldValue("modulation"), _mlxlinkMaps->_prbsModulation);

    return ppttMap;
}

void MlxlinkCommander::prepareBerInfo()
{
    initAmBerCollector();
    _amberCollector->init();

    _ppcntFields = _amberCollector->getLinkStatus();

    setPrintVal(_berInfoCmd, "Time Since Last Clear [Min]",
                AmberField::getValueFromFields(_ppcntFields, "Time_since_last_clear_[Min]"), ANSI_COLOR_RESET, true,
                _linkUP);
    if (_protoActive == IB)
    {
        setPrintVal(_berInfoCmd, "Symbol Errors", AmberField::getValueFromFields(_ppcntFields, "Symbol_Errors"),
                    ANSI_COLOR_RESET, true, _linkUP);
        setPrintVal(_berInfoCmd, "Symbol BER", AmberField::getValueFromFields(_ppcntFields, "Symbol_BER"),
                    ANSI_COLOR_RESET, true, _linkUP);
    }
    setPrintVal(_berInfoCmd, "Effective Physical Errors",
                AmberField::getValueFromFields(_ppcntFields, "Effective_Errors", true), ANSI_COLOR_RESET, true,
                _linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical BER", AmberField::getValueFromFields(_ppcntFields, "Effective_BER"),
                ANSI_COLOR_RESET, true, _linkUP);

    string phyRawErr = AmberField::getValueFromFields(_ppcntFields, "Raw_Errors_lane", false);
    findAndReplace(phyRawErr, "_", ",");
    phyRawErr = getValuesOfActiveLanes(phyRawErr);

    setPrintVal(_berInfoCmd, "Raw Physical Errors Per Lane", phyRawErr, ANSI_COLOR_RESET, true, _linkUP, true);

    if (_protoActive == ETH)
    {
        sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);

        u_int32_t linkDownCounter = getFieldValue("link_down_events");
        u_int32_t linkRecoveryCounter = getFieldValue("successful_recovery_events");
        setPrintVal(_berInfoCmd, "Link Down Counter", to_string(linkDownCounter), ANSI_COLOR_RESET, true, _linkUP);
        setPrintVal(_berInfoCmd, "Link Error Recovery Counter", to_string(linkRecoveryCounter), ANSI_COLOR_RESET, true,
                    _linkUP);
    }

    if (_productTechnology >= PRODUCT_7NM && !dm_is_gpu((dm_dev_id_t)_devID))
    {
        sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);
        string rawBer = AmberField::getValueFromFields(_ppcntFields, "Raw_BER_lane", false);
        findAndReplace(rawBer, "_", ",");
        rawBer = getValuesOfActiveLanes(rawBer);
        setPrintVal(_berInfoCmd, "Raw Physical BER Per Lane", rawBer, ANSI_COLOR_RESET, true, _linkUP, true);
    }
}

void MlxlinkCommander::prepareBerInfoEDR()
{
    char lastClearTimerBuff[64];

    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);

    double lastClearTimer =
      (double)add32BitTo64(getFieldValue("time_since_last_clear_high"), getFieldValue("time_since_last_clear_low")) /
      60000.0;
    sprintf(lastClearTimerBuff, "%.01f", lastClearTimer);
    string symbolErrors =
      to_string(add32BitTo64(getFieldValue("phy_symbol_errors_high"), getFieldValue("phy_symbol_errors_low")));

    setPrintVal(_berInfoCmd, "Time Since Last Clear [Min]", lastClearTimerBuff, ANSI_COLOR_RESET, true, _linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical Errors", symbolErrors, ANSI_COLOR_RESET, true, _linkUP);

    std::vector<string> rawErrorsPerLane;
    string phy_raw_err = "";
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        string laneStr = to_string(lane);
        phy_raw_err = to_string(add32BitTo64(getFieldValue("phy_raw_errors_lane" + laneStr + "_high"),
                                             getFieldValue("phy_raw_errors_lane" + laneStr + "_low")));
        rawErrorsPerLane.push_back(phy_raw_err);
    }
    setPrintVal(_berInfoCmd, "Raw Physical Errors Per Lane", getStringFromVector(rawErrorsPerLane), ANSI_COLOR_RESET,
                true, _linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical BER",
                getFieldStr("effective_ber_coef") + "E-" + getFieldStr("effective_ber_magnitude"), ANSI_COLOR_RESET,
                true, _linkUP);
    setPrintVal(_berInfoCmd, "Raw Physical BER", getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude"),
                ANSI_COLOR_RESET, true, _linkUP);

    if (_protoActive == ETH)
    {
        sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);

        u_int32_t linkDownCounter = getFieldValue("link_down_events");
        u_int32_t linkRecoveryCounter = getFieldValue("successful_recovery_events");
        setPrintVal(_berInfoCmd, "Link Down Counter", to_string(linkDownCounter), ANSI_COLOR_RESET, true, _linkUP);
        setPrintVal(_berInfoCmd, "Link Error Recovery Counter", to_string(linkRecoveryCounter), ANSI_COLOR_RESET, true,
                    _linkUP);
    }
}

void MlxlinkCommander::showBer()
{
    try
    {
        if (_prbsTestMode)
        {
            showTestModeBer();
            return;
        }
        if (_userInput._pcie)
        {
            showMpcntPerformance(_dpn);
            return;
        }
        setPrintTitle(_berInfoCmd, "Physical Counters and BER Info",
                      _productTechnology >= PRODUCT_16NM ? BER_INFO_NDR_LAST : BER_INFO_LAST);

        if (_productTechnology < PRODUCT_16NM)
        {
            prepareBerInfoEDR();
        }
        else
        {
            prepareBerInfo();
            setPrintVal(_berInfoCmd, "Raw Physical BER", AmberField::getValueFromFields(_ppcntFields, "Raw_BER"),
                        ANSI_COLOR_RESET, true, _linkUP);
        }

        if (_protoActive == IB)
        {
            sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_IB_PORT_COUNTERS_GROUP);

            setPrintVal(_berInfoCmd, "Link Down Counter", getFieldStr("link_downed_counter"), ANSI_COLOR_RESET, true,
                        _linkUP);

            sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);

            u_int32_t linkRecoveryCounter = getFieldValue("successful_recovery_events");
            setPrintVal(_berInfoCmd, "Link Error Recovery Counter", to_string(linkRecoveryCounter), ANSI_COLOR_RESET,
                        true, _linkUP);
        }

        cout << _berInfoCmd;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing BER via PPCNT raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showTestModeBer()
{
    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);

    std::vector<string> errors;
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
    {
        errors.push_back(to_string(add32BitTo64(getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_high"),
                                                getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_low"))));
    }

    char buff[64];
    double val =
      (double)add32BitTo64(getFieldValue("time_since_last_clear_high"), getFieldValue("time_since_last_clear_low")) /
      60000.0;
    sprintf(buff, "%.01f", val);

    setPrintTitle(_testModeBerInfoCmd, "Physical Counters and BER Info (PRBS)", TEST_MODE_BER_INFO_LAST);
    setPrintVal(_testModeBerInfoCmd, "Time Since Last Clear [Min]", buff);
    setPrintVal(_testModeBerInfoCmd, "PRBS Errors", getStringFromVector(errors));
    setPrintVal(_testModeBerInfoCmd, "PRBS BER", getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude"));

    cout << _testModeBerInfoCmd;
}

void MlxlinkCommander::getPcieNdrCounters(uint32_t flitActive)
{
    // This field is supported from cx8 and above.
    if (_productTechnology >= PRODUCT_5NM && flitActive)
    {
        string berStr = to_string(getFieldValue("fber_coef")) + "E-" + to_string(getFieldValue("fber_magnitude"));
        setPrintVal(_mpcntPerfInfCmd, "First BER (FBER)", berStr);
    }

    if (_productTechnology >= PRODUCT_16NM)
    {
        string berStr =
          to_string(getFieldValue("effective_ber_coef")) + "E-" + to_string(getFieldValue("effective_ber_magnitude"));
        setPrintVal(_mpcntPerfInfCmd, "Effective ber", berStr);
    }
}

void MlxlinkCommander::showMpcntPerformance(DPN& dpn)
{
    uint32_t flitActive = 0, recordsNum = MPCNT_PERFORMANCE_INFO_LAST + 3;
    try
    {
        sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", _dpn.depth, _dpn.pcieIndex, _dpn.node);
        flitActive = getFieldValue("flit_active");
        recordsNum += flitActive ? 3 : 0;
    }
    catch (const std::exception& e)
    {
        // For backward compatibility, we will not throw an exception here.
    }

    try
    {
        sendPrmReg(ACCESS_REG_MPCNT, GET, "depth=%d,pcie_index=%d,node=%d,grp=%d", dpn.depth, dpn.pcieIndex, dpn.node,
                   MPCNT_PERFORMANCE_GROUP);

        setPrintTitle(_mpcntPerfInfCmd, "Management PCIe Performance Counters Info", recordsNum);
        setPrintVal(_mpcntPerfInfCmd, "RX Errors", getFieldStr("rx_errors"));
        setPrintVal(_mpcntPerfInfCmd, "TX Errors", getFieldStr("tx_errors"));
        setPrintVal(_mpcntPerfInfCmd, "CRC Error dllp", getFieldStr("crc_error_dllp"));
        setPrintVal(_mpcntPerfInfCmd, "CRC Error tlp", getFieldStr("crc_error_tlp"));

        if (flitActive)
        {
            setPrintVal(_mpcntPerfInfCmd, "FEC Correctable Error count", getFieldStr("fec_correctable_error_counter"));
            setPrintVal(_mpcntPerfInfCmd, "FEC Uncorrectable Error count",
                        getFieldStr("fec_uncorrectable_error_counter"));
        }

        getPcieNdrCounters(flitActive);
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing BER via MPCNT raised the following exception: ") + string(exc.what()) + string("\n");
    }

    cout << _mpcntPerfInfCmd;
}

void MlxlinkCommander::checkPCIeValidity()
{
    if (!_userInput._sendDpn)
    {
        if (_validDpns.size() == 0)
        {
            throw MlxRegException("No valid depth, node and pcie_index detected!");
        }
        else if (_validDpns.size() == 1)
        {
            _dpn = _validDpns[0];
            _localPort = getLocalPortFromMPIR(_dpn);
        }
        else if (_validDpns.size() > 1 && !_userInput._portSpecified)
        {
            throw MlxRegException("The --depth, --pcie_index and --node must be specified!");
        }
    }
}

void MlxlinkCommander::prepare40_28_16nmEyeInfo(u_int32_t numOfLanes)
{
    std::vector<string> physicalGrades;
    std::vector<string> heightLengths;
    std::vector<string> phaseWidths;
    string phaseEONegStr = "N/A";
    string offsetEONegStr = "N/A";
    bool validPhaseHeight = _productTechnology <= PRODUCT_16NM || _userInput._pcie;

    string height_eo_pos("height_eo_pos");
    string height_eo_neg("height_eo_neg");
    string phase_eo_pos("phase_eo_pos");
    string phase_eo_neg("phase_eo_neg");
    if (_productTechnology == PRODUCT_16NM)
    {
        height_eo_pos.append("_mid");
        height_eo_neg.append("_mid");
        phase_eo_pos.append("_mid");
        phase_eo_neg.append("_mid");
    }
    for (u_int32_t lane = 0; lane < numOfLanes; lane++)
    {
        sendPrmReg(ACCESS_REG_SLRG, GET, "lane=%d", lane);

        physicalGrades.push_back(MlxlinkRecord::addSpaceForSlrg(to_string(getFieldValue("grade"))));
        if (validPhaseHeight)
        {
            int offsetEOPos = getHeight(getFieldValue(height_eo_pos));
            int offsetEONeg = getHeight(getFieldValue(height_eo_neg));
            if (_productTechnology == PRODUCT_16NM && (offsetEOPos + offsetEONeg) == 0)
            {
                offsetEONegStr = "N/A";
            }
            else
            {
                offsetEONegStr = to_string(offsetEOPos + offsetEONeg);
            }
            int phaseEOPos = getPhase(getFieldValue(phase_eo_pos));
            int phaseEONeg = getPhase(getFieldValue(phase_eo_neg));
            if (_productTechnology == PRODUCT_16NM && (phaseEOPos + phaseEONeg) == 0)
            {
                phaseEONegStr = "N/A";
            }
            else
            {
                phaseEONegStr = to_string(phaseEOPos + phaseEONeg);
            }

            _fomStr += physicalGrades.back() + " ";
        }
        heightLengths.push_back(MlxlinkRecord::addSpaceForSlrg(offsetEONegStr));
        phaseWidths.push_back(MlxlinkRecord::addSpaceForSlrg(phaseEONegStr));
    }
    if (!_userInput._showMultiPortInfo && !_userInput._showMultiPortModuleInfo)
    {
        setPrintVal(_eyeOpeningInfoCmd, "Physical Grade", getStringFromVector(physicalGrades), ANSI_COLOR_RESET, true,
                    true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Height Eye Opening [mV]", getStringFromVector(heightLengths), ANSI_COLOR_RESET,
                    true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Phase  Eye Opening [psec]", getStringFromVector(phaseWidths), ANSI_COLOR_RESET,
                    true, true, true);
    }
}

void MlxlinkCommander::startSlrgPciScan(u_int32_t numOfLanesToUse)
{
    // Start EOM measurements per lane
    for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++)
    {
        sendPrmReg(ACCESS_REG_SLRG, GET, "lane=%d,fom_measurement=%d", lane, SLRG_EOM_COMPOSITE);
    }
    // For each lane, wait until process finish
    for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++)
    {
        u_int32_t it = 0;
        while (it < SLRG_PCIE_7NM_TIMEOUT)
        {
            sendPrmReg(ACCESS_REG_SLRG, GET, "lane=%d", lane);

            if (getFieldValue("status"))
            {
                break;
            }

            it++;
            msleep(SLRG_PCIE_7NM_SLEEP);
        }
    }
}

void MlxlinkCommander::prepare7nmEyeInfo(u_int32_t numOfLanesToUse)
{
    std::vector<string> legand, initialFom, lastFom, upperFom, midFom, lowerFom;
    u_int32_t status = 0;
    u_int32_t fomMeasurement = SLRG_EOM_NONE;

    if (!_userInput._pcie)
    {
        fomMeasurement = SLRG_EOM_COMPOSITE;
        if (!isNRZSpeed(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
        {
            fomMeasurement |= (SLRG_EOM_UPPER | SLRG_EOM_MIDDLE | SLRG_EOM_LOWER);
        }
    }
    else
    {
        startSlrgPciScan(numOfLanesToUse);
    }

    for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++)
    {
        status = 0;

        sendPrmReg(ACCESS_REG_SLRG, GET, "lane=%d,fom_measurement=%d", lane, fomMeasurement);

        status = getFieldValue("status");
        std::string initialFomStr = status ? getFieldStr("initial_fom", (u_int32_t)8) : "N/A";

        initialFom.push_back(MlxlinkRecord::addSpaceForSlrg(initialFomStr));
        lastFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("last_fom", (u_int32_t)8) : "N/A"));
        upperFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("upper_eye", (u_int32_t)8) : "N/A"));
        midFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("mid_eye", (u_int32_t)8) : "N/A"));
        lowerFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("lower_eye", (u_int32_t)8) : "N/A"));

        _fomStr += initialFomStr + " ";

        legand.push_back(MlxlinkRecord::addSpaceForSlrg(to_string(lane)));
    }
    if (!_userInput._showMultiPortInfo && !_userInput._showMultiPortModuleInfo)
    {
        string fomMode = status ? _mlxlinkMaps->_slrgFomMode[getFieldValue("fom_mode")] : "N/A";
        setPrintVal(_eyeOpeningInfoCmd, "FOM Mode", fomMode, ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Lane", status ? getStringFromVector(legand) : "N/A", ANSI_COLOR_RESET, true,
                    true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Initial FOM", status ? getStringFromVector(initialFom) : "N/A",
                    ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Last FOM", status ? getStringFromVector(lastFom) : "N/A", ANSI_COLOR_RESET,
                    true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Upper Grades", status ? getStringFromVector(upperFom) : "N/A",
                    ANSI_COLOR_RESET, (fomMeasurement & SLRG_EOM_UPPER), true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Mid Grades", status ? getStringFromVector(midFom) : "N/A", ANSI_COLOR_RESET,
                    (fomMeasurement & SLRG_EOM_MIDDLE), true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Lower Grades", status ? getStringFromVector(lowerFom) : "N/A",
                    ANSI_COLOR_RESET, (fomMeasurement & SLRG_EOM_LOWER), true, true);
    }
}

void MlxlinkCommander::prepare5nmEyeInfo(u_int32_t numOfLanesToUse)
{
    std::vector<string> legand, initialFom, lastFom, upperFom, midFom, lowerFom;
    u_int32_t status = 0;
    u_int32_t fomMeasurement = SLRG_EOM_NONE;

    if (!_userInput._pcie)
    {
        fomMeasurement = SLRG_EOM_COMPOSITE;
        if (!isNRZSpeed(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
        {
            fomMeasurement |= (SLRG_EOM_UPPER | SLRG_EOM_MIDDLE | SLRG_EOM_LOWER);
        }
    }
    else
    {
        startSlrgPciScan(numOfLanesToUse);
    }

    for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++)
    {
        status = 0;

        sendPrmReg(ACCESS_REG_SLRG, GET, "lane=%d,fom_measurement=%d", lane, fomMeasurement);

        status = getFieldValue("status");
        std::string initialFomStr = status ? getFieldStr("initial_fom", (u_int32_t)16) : "N/A";

        initialFom.push_back(MlxlinkRecord::addSpaceForSlrg(initialFomStr));
        lastFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("last_fom", (u_int32_t)16) : "N/A"));
        upperFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("upper_eye", (u_int32_t)16) : "N/A"));
        midFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("mid_eye", (u_int32_t)16) : "N/A"));
        lowerFom.push_back(MlxlinkRecord::addSpaceForSlrg(status ? getFieldStr("lower_eye", (u_int32_t)16) : "N/A"));

        _fomStr += initialFomStr + " ";

        legand.push_back(MlxlinkRecord::addSpaceForSlrg(to_string(lane)));
    }

    if (!_userInput._showMultiPortInfo && !_userInput._showMultiPortModuleInfo)
    {
        string fomMode = status ? _mlxlinkMaps->_slrgFomMode5nm[getFieldValue("fom_mode")] : "N/A";
        setPrintVal(_eyeOpeningInfoCmd, "FOM Mode", fomMode, ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Lane", status ? getStringFromVector(legand) : "N/A", ANSI_COLOR_RESET, true,
                    true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Initial FOM", status ? getStringFromVector(initialFom) : "N/A",
                    ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Last FOM", status ? getStringFromVector(lastFom) : "N/A", ANSI_COLOR_RESET,
                    true, true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Upper Grades", status ? getStringFromVector(upperFom) : "N/A",
                    ANSI_COLOR_RESET, (fomMeasurement & SLRG_EOM_UPPER), true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Mid Grades", status ? getStringFromVector(midFom) : "N/A", ANSI_COLOR_RESET,
                    (fomMeasurement & SLRG_EOM_MIDDLE), true, true);
        setPrintVal(_eyeOpeningInfoCmd, "Lower Grades", status ? getStringFromVector(lowerFom) : "N/A",
                    ANSI_COLOR_RESET, (fomMeasurement & SLRG_EOM_LOWER), true, true);
    }
}

void MlxlinkCommander::showEye()
{
    if (_userInput._pcie)
    {
        checkPCIeValidity();
    }

    if (_userInput.planeIndex != -1)
    {
        throw MlxRegException("No plane information is available for show_eye!");
    }

    try
    {
        if (_userInput._pcie)
        {
            sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", _dpn.depth, _dpn.pcieIndex, _dpn.node);

            if (getFieldValue("link_speed_active") < GEN3)
            {
                throw MlxRegException("Eye information available for Gen3 and above");
            }
        }

        u_int32_t numOfLanesToUse = (_userInput._pcie) ? _numOfLanesPcie : _numOfLanes;
        string showEyeTitle = "EYE Opening Info";
        if (_userInput._pcie)
        {
            showEyeTitle += " (PCIe)";
        }
        setPrintTitle(_eyeOpeningInfoCmd, showEyeTitle, EYE_OPENING_INFO_LAST);
        if (_productTechnology <= PRODUCT_16NM)
        {
            prepare40_28_16nmEyeInfo(numOfLanesToUse);
        }
        else if (_productTechnology == PRODUCT_7NM)
        {
            prepare7nmEyeInfo(numOfLanesToUse);
        }
        else if (_productTechnology == PRODUCT_5NM)
        {
            prepare5nmEyeInfo(numOfLanesToUse);
        }
        cout << _eyeOpeningInfoCmd;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing Eye via SLRG raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::fecMaskToUserInputStr(u_int32_t fecCapMask)
{
    u_int32_t mask = 0;
    string validFecStr = "";
    string shortFec = "";
    for (double bitIdx = 0; bitIdx < 16; bitIdx++)
    {
        mask = (u_int32_t)pow(2.0, bitIdx);
        if (fecCapMask & mask)
        {
            if (_mlxlinkMaps->_fecModeMask.count(mask))
            {
                shortFec = _mlxlinkMaps->_fecModeMask[mask].second;
                if (shortFec.find("PLR") != string::npos)
                {
                    continue;
                }
                if (shortFec.find("-544") != string::npos || shortFec.find("-272") != string::npos)
                {
                    shortFec = shortFec.substr(0, 2);
                }
                validFecStr += shortFec + "(" + _mlxlinkMaps->_fecModeMask[mask].first + ")/";
            }
        }
    }
    string auFec = _mlxlinkMaps->_fecModeMask[0].second + "(" + _mlxlinkMaps->_fecModeMask[0].first + ")";
    validFecStr = validFecStr.empty() ? "" : (auFec + "/" + deleteLastChar(validFecStr));
    return validFecStr;
}

string MlxlinkCommander::getSupportedFecForSpeed(const string& speed)
{
    string fecCap = "0x0 (N/A)";
    string protoStr = _protoActive == IB ? "ib_" : "";
    if (!_prbsTestMode)
    {
        string speedToCheck = speed;
        speedToCheck = toLowerCase(speedToCheck);
        if (speedToCheck == "10g" || speedToCheck == "40g")
        {
            speedToCheck = "10g_40g";
        }
        if (speedToCheck == "50g_2x")
        {
            speedToCheck = "50g";
        }
        if (speedToCheck == "100g_4x")
        {
            speedToCheck = "100g";
        }
        fecCap = fecMaskToStr(getFieldValue(protoStr + "fec_override_cap_" + speedToCheck));
    }
    return fecCap;
}

string MlxlinkCommander::fecMaskToStr(u_int32_t mask)
{
    char strMask[32];
    snprintf(strMask, sizeof(strMask), "0x%x (", mask);

    string fecStr = string(strMask);

    if (mask)
    {
        fecStr += getStrByMaskFromPair(mask, _mlxlinkMaps->_fecModeMask, ", ");
    }
    else
    {
        fecStr = "0x0 (N/A";
    }
    fecStr += ")";

    return fecStr;
}

void MlxlinkCommander::showFEC()
{
    try
    {
        sendPrmReg(ACCESS_REG_PPLM, GET);

        string supportedSpeedsStr = SupportedSpeeds2Str(_protoActive, _deviceCapability, _protoCapabilityEx);
        vector<string> supportedSpeeds = MlxlinkRecord::split(supportedSpeedsStr, ",");

        for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++)
        {
            if (isIn((*it).first, supportedSpeeds))
            {
                it->second = getSupportedFecForSpeed((*it).first);
            }
        }

        setPrintTitle(_fecCapInfoCmd, HEADER_FEC_INFO, supportedSpeeds.size() + 1);

        bool noFecDetected = true;
        string bitEthIndecator = "bE";
        for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++)
        {
            if (!(*it).second.empty())
            {
                noFecDetected = false;
            }
            if (isIn((*it).first, supportedSpeeds))
            {
                setPrintVal(_fecCapInfoCmd,
                            "FEC Capability " + (*it).first +
                              ((_productTechnology < PRODUCT_16NM && _protoActive == ETH) ? bitEthIndecator : ""),
                            (*it).second, ANSI_COLOR_RESET, true, true, true);
            }
        }
        if (noFecDetected)
        {
            MlxlinkRecord::printWar("FEC information is not available for InfiniBand protocol", _jsonRoot);
        }
        else
        {
            cout << _fecCapInfoCmd;
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing FEC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::getSltpHeader()
{
    string sep = ",";
    vector<string> sltpHeader;
    map<u_int32_t, PRM_FIELD> sltpParam;
    u_int32_t activeSpeed = _protoActive == IB ? _activeSpeed : _activeSpeedEx;
    activeSpeed = activeSpeed == 0 ? _laneSpeedFromPptt : activeSpeed;

    switch (_productTechnology)
    {
        case PRODUCT_5NM:
            sltpParam = _mlxlinkMaps->_SltpXdrParams;
            break;
        case PRODUCT_7NM:
            sltpParam = _mlxlinkMaps->_SltpNdrParams;
            break;
        case PRODUCT_16NM:
            sltpParam = _mlxlinkMaps->_SltpHdrParams;
            break;
        default:
            sltpParam = _mlxlinkMaps->_SltpEdrParams;
            activeSpeed = _protoActive;
            break;
    }

    for (auto const& param : sltpParam)
    {
        if ((param.second.validationMask & activeSpeed) || _userInput._pcie)
        {
            if ((param.second.fieldAccess & FIELD_ACCESS_R) ||
                (_userInput._advancedMode && (param.second.fieldAccess & FIELD_ACCESS_ADVANCED)))
            {
                sltpHeader.push_back(
                  MlxlinkRecord::addSpace(param.second.uiField, param.second.uiField.size() + 1, false));
            }
        }
    }

    return getStringFromVector(sltpHeader);
}

void MlxlinkCommander::showSltp()
{
    if (_userInput._pcie)
    {
        checkPCIeValidity();
    }
    try
    {
        bool valid = true;
        u_int32_t numOfLanesToUse = (_userInput._pcie) ? _numOfLanesPcie : _numOfLanes;
        std::vector<std::vector<string>> sltpLanes(numOfLanesToUse, std::vector<string>());
        std::vector<std::vector<string>> ppttLanes(numOfLanesToUse, std::vector<string>());
        map<u_int32_t, u_int32_t> ppttSpeeds = _mlxlinkMaps->_ppttSpeedMapping;

        if (_protoActive == ETH && !_isHCA)
        {
            // according to prm, all lanes show be configured to the same speed
            sendPrmReg(ACCESS_REG_PPTT, GET, "lane=%d", 0);
            map<u_int32_t, u_int32_t>::iterator pos = ppttSpeeds.find(getFieldValue("lane_rate_admin"));
            if (pos != ppttSpeeds.end())
            {
                _laneSpeedFromPptt = pos->second;
            }
        }

        string showSltpTitle = "Serdes Tuning Transmitter Info";
        string sltpHeader = getSltpHeader();

        if (_userInput._pcie)
        {
            showSltpTitle += " (PCIe)";
        }
        setPrintTitle(_sltpInfoCmd, showSltpTitle, numOfLanesToUse + 1);

        if (!_linkUP && !_userInput._pcie && !_prbsTestMode)
        {
            setPrintVal(_sltpInfoCmd, "Serdes TX parameters", sltpHeader, ANSI_COLOR_RESET, true, false, true);
            cout << _sltpInfoCmd;
            return;
        }
        setPrintVal(_sltpInfoCmd, "Serdes TX parameters", sltpHeader, ANSI_COLOR_RESET, true, true, true);

        for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++)
        {
            if (_userInput._pcie && _userInput._pciSltpPort != -1)
            {
                sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d,c_db=%d,local_port=%d", lane, _userInput._db,
                           _userInput._pciSltpPort);
            }
            else
            {
                sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d,c_db=%d", lane, _userInput._db);
            }

            switch (_productTechnology)
            {
                case PRODUCT_5NM:
                    prepareSltpXdrGen(sltpLanes, lane);
                    break;
                case PRODUCT_7NM:
                    prepareSltpNdrGen(sltpLanes, lane);
                    break;
                default:
                    prepareSltpEdrHdrGen(sltpLanes, lane);
            }

            if (!getFieldValue("status"))
            {
                valid = false;
            }

            setPrintVal(_sltpInfoCmd, "Lane " + to_string(lane), getStringFromVector(sltpLanes[lane]), ANSI_COLOR_RESET,
                        true, valid, true);
        }
        cout << _sltpInfoCmd;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing SLTP raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::queryBkvCaps(uint8_t& numGroups, uint8_t groupId)
{
    uint8_t numEntries = 0;
    return queryBkvCaps(numGroups, numEntries, groupId);
}

void MlxlinkCommander::queryBkvCaps(uint8_t& numGroups, uint8_t& numEntries, uint8_t groupId, uint8_t entryId)
{
    numGroups = 0;
    numEntries = 0;

    try
    {
        sendPrmReg(ACCESS_REG_PSCD, GET, "lane=%d, page_select=%d", _userInput._lane, PSCD_PAGE_CAPABILITIES);
        numGroups = getFieldValue("total_num_of_groups");

        // If groupId is not -1, validate it and get entries count
        if (groupId != (u_int8_t)-1)
        {
            if (groupId >= numGroups)
            {
                throw MlxRegException("Invalid group ID: " + to_string(groupId) + ". Valid range is 0-" +
                                      to_string(numGroups - 1) + "\n");
            }

            // Get number of entries for this specific group
            string numEntriesField = "num_of_supported_entries_" + to_string(groupId);
            numEntries = getFieldValue(numEntriesField);

            // If entryId is not -1, validate it against the entry count
            if (entryId != (u_int8_t)-1)
            {
                if (entryId >= numEntries)
                {
                    throw MlxRegException("Invalid entry ID: " + to_string(entryId) + " for group " +
                                          to_string(groupId) + ". Valid range is 0-" + to_string(numEntries - 1) +
                                          "\n");
                }
            }
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException(string("Getting BKV Groups capabilities raised the following exception: ") +
                              string(exc.what()) + string("\n"));
    }
}

void MlxlinkCommander::showBkv()
{
    uint8_t numGroups = 0;

    queryBkvCaps(numGroups);

    try
    {
        std::vector<std::string> tableData = {};
        MlxlinkCmdPrint showBkvCmd;

        // Collect data for each group and populate table
        for (uint32_t group = 0; group < numGroups; group++)
        {
            uint32_t posToUpdateWidthInVector = 0;

            try
            {
                // Get data for this group using indexed field names
                string numEntriesField = "num_of_supported_entries_" + to_string(group);
                string filledIndicationField = "filled_indication_" + to_string(group);

                u_int32_t numSupportedEntries = getFieldValue(numEntriesField);
                u_int32_t filledIndication = getFieldValue(filledIndicationField);

                // Update table with group number
                string groupNum = to_string(group);
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, groupNum, groupNum.length());

                // Update table with supported entries count
                string supportedEntriesStr = to_string(numSupportedEntries);
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, supportedEntriesStr, supportedEntriesStr.length());

                // Update table with filled indication
                string filledIndicationStr = filledIndication ? "Yes" : "No";
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, filledIndicationStr, filledIndicationStr.length());
            }
            catch (const std::exception& exc)
            {
                // If we can't get data for this group, add empty entries
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, to_string(group), to_string(group).length());
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, "N/A", 3, false);
                updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupsTableHeader, posToUpdateWidthInVector++,
                                               tableData, "N/A", 3, false);
            }
        }

        // Print title and table
        setPrintTitle(showBkvCmd, "BKV Groups Info", numGroups + 1);
        cout << showBkvCmd;
        printMlxlinkTable(tableData, _mlxlinkMaps->_bkvGroupsTableHeader);
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Processing BKV Groups raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showBkvGroup(bool showEntries, u_int32_t entryFilter)
{
    uint8_t numGroups = 0;
    uint8_t numEntries = 0;

    uint32_t rateMask = 0;
    uint32_t roleMask = 0;
    uint32_t modeBRoleMask = 0;

    // First validate the group ID by getting capabilities
    queryBkvCaps(numGroups, numEntries, _userInput._bkvGroupId, (uint8_t)-1);

    try
    {
        // Get group configuration data
        sendPrmReg(ACCESS_REG_PSCD, GET, "lane=%d, page_select=%d, select_group=%d", _userInput._lane,
                   PSCD_PAGE_CONFIGURATIONS, _userInput._bkvGroupId);

        rateMask = getFieldValue("rate_mask");
        roleMask = getFieldValue("role_mask");
        modeBRoleMask = getFieldValue("mode_b_role_mask");
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Getting BKV Group configuration raised the following exception: ") +
                               string(exc.what()) + string("\n");
    }

    // Section 1: BKV Group Properties
    MlxlinkCmdPrint showBkvGroupPropertiesCmd;

    stringstream value;

    setPrintTitle(showBkvGroupPropertiesCmd, "BKV Group Properties", 4);

    value << "0x" << std::hex << setfill('0') << setw(4) << rateMask << " ("
          << getStrByMask(rateMask, _mlxlinkMaps->_PSCDRateMask2Str, ",") << ")";
    setPrintVal(showBkvGroupPropertiesCmd, "Rate Mask", value.str(), ANSI_COLOR_RESET, true, true);

    value.str("");
    value.clear();
    value << "0x" << std::hex << setfill('0') << setw(2) << roleMask << " ("
          << getStrByMask(roleMask, _mlxlinkMaps->_PSCDRoleMask2Str, ",") << ")";
    setPrintVal(showBkvGroupPropertiesCmd, "Role Mask", value.str(), ANSI_COLOR_RESET, true, true);

    value.str("");
    value.clear();
    value << "0x" << std::hex << setfill('0') << setw(1) << modeBRoleMask << " ("
          << getStrByMask(modeBRoleMask, _mlxlinkMaps->_PSCDModeBRoleMask2Str, ",") << ")";
    setPrintVal(showBkvGroupPropertiesCmd, "Mode B Role Mask", value.str(), ANSI_COLOR_RESET, true, true);

    cout << showBkvGroupPropertiesCmd;

    if (showEntries)
    {
        // Section 2: BKV Group Entries Table
        MlxlinkCmdPrint showBkvGroupEntriesCmd;
        std::vector<std::string> tableData = {};

        uint32_t startEntry = (entryFilter == (uint32_t)-1) ? 0 : entryFilter;
        uint32_t endEntry = (entryFilter == (uint32_t)-1) ? numEntries : entryFilter + 1;
        uint32_t displayedEntries = 0;

        uint32_t address = 0;
        uint32_t wdata = 0;
        uint32_t wmask = 0;

        for (uint32_t entry = startEntry; entry < endEntry; entry++)
        {
            uint32_t posToUpdateWidthInVector = 0;
            displayedEntries++;

            try
            {
                // Get entry data using indexed field names
                string addressField = "address_" + to_string(entry);
                string wdataField = "wdata_" + to_string(entry);
                string wmaskField = "wmask_" + to_string(entry);

                address = getFieldValue(addressField);
                wdata = getFieldValue(wdataField);
                wmask = getFieldValue(wmaskField);
            }
            catch (const std::exception& exc)
            {
                _allUnhandledErrors += string("Getting BKV Group entries raised the following exception: ") +
                                       string(exc.what()) + string("\n");
            }

            // Update table with entry ID
            string entryIdStr = to_string(entry);
            updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupEntriesTableHeader, posToUpdateWidthInVector++,
                                           tableData, entryIdStr, entryIdStr.length());
            stringstream value;

            // Update table with address
            value << "0x" << std::hex << setfill('0') << setw(4) << address;
            string addressStr = value.str();
            updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupEntriesTableHeader, posToUpdateWidthInVector++,
                                           tableData, addressStr, addressStr.length());

            // Update table with wdata
            value.str("");
            value.clear();
            value << "0x" << std::hex << setfill('0') << setw(4) << wdata;
            string wdataStr = value.str();
            updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupEntriesTableHeader, posToUpdateWidthInVector++,
                                           tableData, wdataStr, wdataStr.length());
            // Update table with wmask
            value.str("");
            value.clear();
            value << "0x" << std::hex << setfill('0') << setw(4) << wmask;
            string wmaskStr = value.str();
            updateColumnWidthPopulateTable(_mlxlinkMaps->_bkvGroupEntriesTableHeader, posToUpdateWidthInVector++,
                                           tableData, wmaskStr, wmaskStr.length());
        }

        setPrintTitle(showBkvGroupEntriesCmd, "BKV Group Entries", displayedEntries + 1);
        cout << showBkvGroupEntriesCmd;
        printMlxlinkTable(tableData, _mlxlinkMaps->_bkvGroupEntriesTableHeader);
    }
}

void MlxlinkCommander::setBkvGroup()
{
    uint8_t numGroups = 0;
    uint32_t rateMask = 0;
    uint32_t roleMask = 0;
    uint32_t modeBRoleMask = 0;

    // First validate the group ID by getting capabilities
    queryBkvCaps(numGroups, _userInput._bkvGroupId);
    {
        return;
    }

    try
    {
        string setParams = "lane=" + to_string(_userInput._lane) +
                           ", page_select=" + to_string(PSCD_PAGE_CONFIGURATIONS) +
                           ", select_group=" + to_string(_userInput._bkvGroupId);

        if (_userInput._bkvRates.size() > 0)
        {
            for (const string& rate : _userInput._bkvRates)
            {
                auto rate_it = _mlxlinkMaps->_PSCDRateStr2Mask.find(rate);
                if (rate_it == _mlxlinkMaps->_PSCDRateStr2Mask.end())
                {
                    throw MlxRegException("Invalid rate: " + rate);
                }
                rateMask |= rate_it->second;
            }
            setParams += ", rate_mask=" + to_string(rateMask);
        }
        if (_userInput._bkvRoles.size() > 0)
        {
            for (const string& role : _userInput._bkvRoles)
            {
                auto role_it = _mlxlinkMaps->_PSCDRoleStr2Mask.find(role);
                if (role_it == _mlxlinkMaps->_PSCDRoleStr2Mask.end())
                {
                    throw MlxRegException("Invalid role: " + role);
                }
                roleMask |= role_it->second;
            }
            setParams += ", role_mask=" + to_string(roleMask);
        }
        if (_userInput._bkvModeBRoles.size() > 0)
        {
            for (const string& modeBRole : _userInput._bkvModeBRoles)
            {
                auto modeBRole_it = _mlxlinkMaps->_PSCDModeBRoleStr2Mask.find(modeBRole);
                if (modeBRole_it == _mlxlinkMaps->_PSCDModeBRoleStr2Mask.end())
                {
                    throw MlxRegException("Invalid mode B role: " + modeBRole);
                }
                modeBRoleMask |= modeBRole_it->second;
            }
            setParams += ", mode_b_role_mask=" + to_string(modeBRoleMask);
        }

        sendPrmReg(ACCESS_REG_PSCD, SET, setParams.c_str());

        // Show the updated properties
        showBkvGroup(false, (u_int8_t)-1);
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Setting BKV Group masks raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::setBkvEntry()
{
    uint8_t numGroups = 0;
    uint8_t numEntries = 0;

    // First validate the group ID and entry ID by getting capabilities
    queryBkvCaps(numGroups, numEntries, _userInput._bkvGroupId, _userInput._bkvEntry);

    try
    {
        string setParams = "lane=" + to_string(_userInput._lane) +
                           ", page_select=" + to_string(PSCD_PAGE_CONFIGURATIONS) +
                           ", select_group=" + to_string(_userInput._bkvGroupId);

        if (_userInput._bkvAddressSpecified)
        {
            setParams += ", address_" + to_string(_userInput._bkvEntry) + "=" + to_string(_userInput._bkvAddress);
        }
        if (_userInput._bkvWdataSpecified)
        {
            setParams += ", wdata_" + to_string(_userInput._bkvEntry) + "=" + to_string(_userInput._bkvWdata);
        }
        if (_userInput._bkvWmaskSpecified)
        {
            setParams += ", wmask_" + to_string(_userInput._bkvEntry) + "=" + to_string(_userInput._bkvWmask);
        }

        sendPrmReg(ACCESS_REG_PSCD, SET, setParams.c_str());

        // Show the updated group with both sections, entries section filtered to specific entry
        showBkvGroup(true, _userInput._bkvEntry);
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Setting BKV Group entry raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showDeviceData()
{
    try
    {
        std::vector<string> showDeviceDataValues;
        bool success = false;

        try
        {
            sendPrmReg(ACCESS_REG_MSGI, GET);
            success = true;
        }
        catch (...)
        {
        }

        setPrintTitle(_showDeviceInfoCmd, "Device Info", DEVICE_INFO_LAST);

        setPrintVal(_showDeviceInfoCmd, "Part Number", success ? getAscii("part_number", 20) : "N/A");
        setPrintVal(_showDeviceInfoCmd, "Part Name", success ? getAscii("product_name", 64) : "N/A");
        setPrintVal(_showDeviceInfoCmd, "Serial Number", success ? getAscii("serial_number", 24) : "N/A");
        setPrintVal(_showDeviceInfoCmd, "Revision", success ? getVendorRev(getFieldValue("revision")) : "N/A");
        setPrintVal(_showDeviceInfoCmd, "FW Version", getFwVersion());

        cout << _showDeviceInfoCmd;

        if (_isHCA)
        {
            MlxlinkRecord::printWar("Note: P/N, Product Name, S/N and Revision are supported only in switches",
                                    _jsonRoot);
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing Device Data via MSGI raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showBerMonitorInfo()
{
    if (_isHCA)
    {
        throw MlxRegException("\"--" BER_MONITOR_INFO_FLAG "\" option is not supported for HCA");
    }
    try
    {
        string monitor_state = "N/A";
        string monitor_type = "N/A";
        string alarm_th = "N/A";
        string warning_th = "N/A";
        string normal_th = "N/A";

        sendPrmReg(ACCESS_REG_PPBMC, GET);

        monitor_state = _mlxlinkMaps->_ppbmcBerMonitorState[getFieldValue("monitor_state")];
        u_int32_t monitor_type_cap = getFieldValue("monitor_type_cap");

        if (monitor_type_cap)
        {
            u_int32_t monitor_type_int = getFieldValue("monitor_type");
            monitor_type = _mlxlinkMaps->_ppbmcBerMonitorType[monitor_type_int];
        }

        setPrintTitle(_showBerMonitorInfo, "BER Monitor Info", BER_MONITOR_INFO_LAST);
        setPrintVal(_showBerMonitorInfo, "BER Monitor State", monitor_state);
        setPrintVal(_showBerMonitorInfo, "BER Monitor Type", monitor_type);

        cout << _showBerMonitorInfo;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing BER Monitor via PPBMC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showExternalPhy()
{
    if (_isSwControled)
    {
        _allUnhandledErrors += string("No plugged cable detected\n");
        return;
    }

    try
    {
        gearboxBlock(PEPC_SHOW_FLAG);

        if (_isHCA || _devID == DeviceSwitchIB || _devID == DeviceSwitchIB2 || _devID == DeviceQuantum ||
            _devID == DeviceQuantum2 || _devID == DeviceQuantum3 || dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            throw MlxRegException("\"--" PEPC_SHOW_FLAG "\" option is not supported for HCA and InfiniBand switches");
        }

        sendPrmReg(ACCESS_REG_PEPC, GET);

        setPrintTitle(_extPhyInfoCmd, "External PHY Info", EXT_PHY_INFO_INFO_LAST);

        setPrintVal(_extPhyInfoCmd, "Twisted Pair Force Mode",
                    getStrByValue(getFieldValue("twisted_pair_force_mode"), _mlxlinkMaps->_pepcTwistedPairForceMode));

        cout << _extPhyInfoCmd;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing External PHY via PEPC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::initValidDPNList()
{
    bool valid = false;
    u_int32_t maxNumOfHost = 4;
    u_int32_t maxNumOfDsPort = 16;
    u_int32_t maxDepth = 4;
    u_int32_t depth, pcieIndex, node;
    string bdf = "";

    if (_validDpns.empty())
    {
        for (pcieIndex = 0; pcieIndex < maxNumOfHost; pcieIndex++)
        {
            try
            {
                sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", 0, pcieIndex, 0);
                valid = getFieldValue("bdf0");
            }
            catch (...)
            {
                valid = false;
            }
            if (valid && getFieldValue("port_type") == PORT_TYPE_EP)
            {
                _validDpns.push_back(DPN(0, pcieIndex, 0, getBDFStr(getFieldValue("bdf0"))));
            }
            else
            {
                if (valid && getFieldValue("port_type") == PORT_TYPE_US)
                {
                    _validDpns.push_back(DPN(0, pcieIndex, 0, getBDFStr(getFieldValue("bdf0"))));
                }
                for (depth = 1; depth < maxDepth; depth++)
                {
                    try
                    {
                        sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", depth, pcieIndex, 0);
                        if (getFieldValue("port_type") == PORT_TYPE_DS)
                        {
                            _validDpns.push_back(DPN(depth, pcieIndex, 0, getBDFStr(getFieldValue("bdf0"))));
                            for (node = 1; node < maxNumOfDsPort; node++)
                            {
                                try
                                {
                                    sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", depth,
                                               pcieIndex, node);
                                    _validDpns.push_back(DPN(depth, pcieIndex, node, getBDFStr(getFieldValue("bdf0"))));
                                }
                                catch (...)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    catch (...)
                    {
                    }
                }
            }
            if (!_isHCA)
            {
                break;
            }
        }
    }
}

void MlxlinkCommander::updateDPNDomain()
{
    static bool updated = false;
    if (updated)
    {
        return;
    }
    updated = true;
    for (u_int32_t i = 0; i < _validDpns.size(); i++)
    {
        try
        {
            sendPrmReg(ACCESS_REG_MPIR, GET, "DPNv=1,depth=%d,pcie_index=%d,node=%d", _validDpns[i].depth,
                       _validDpns[i].pcieIndex, _validDpns[i].node);
            u_int32_t seg_valid = getFieldValue("segment_valid");
            u_int32_t segment_base = getFieldValue("segment_base");
            if (seg_valid)
            {
                char seg_buf[5];
                snprintf(seg_buf, sizeof(seg_buf), "%04x", segment_base);
                _validDpns[i].bdf = string(seg_buf) + ":" + _validDpns[i].bdf;
            }
        }
        catch (const std::exception& exc)
        {
            continue;
        }
    }
}

void MlxlinkCommander::showPcieLinks()
{
    try
    {
        if (_validDpns.size() == 0)
        {
            throw MlxRegException("No valid DPN's detected!");
        }
        setPrintTitle(_validPcieLinks, "Valid PCIe Links", _validDpns.size() + 1);
        setPrintVal(_validPcieLinks, "Legend", "depth ,pcie_index ,node ,port ,bdf", ANSI_COLOR_RESET, true, true,
                    true);
        for (u_int32_t i = 0; i < _validDpns.size(); i++)
        {
            char dpnStr[128];
            int localPort = getLocalPortFromMPIR(_validDpns[i]);
            snprintf(dpnStr, sizeof(dpnStr), "%-5d ,%-10d ,%-4d ,%-4d ,%s", _validDpns[i].depth,
                     _validDpns[i].pcieIndex, _validDpns[i].node, localPort, _validDpns[i].bdf.c_str());
            setPrintVal(_validPcieLinks, "Link " + to_string(i + 1), dpnStr, ANSI_COLOR_RESET, localPort >= 0, true,
                        true);
        }
        cout << _validPcieLinks;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing valid PCIe links raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showPcie()
{
    try
    {
        if (_userInput._links)
        {
            return;
        }
        if (!_userInput._sendDpn && !_userInput._portSpecified)
        {
            if (_validDpns.size() == 0)
            {
                throw MlxRegException("No valid DPN's detected!");
            }
            int localPort = 0;
            for (u_int32_t i = 0; i < _validDpns.size(); i++)
            {
                localPort = getLocalPortFromMPIR(_validDpns[i]);
                if (localPort >= 0)
                {
                    showPcieState(_validDpns[i]);
                }
                if (_userInput.isPcieErrInjProvided)
                {
                    break;
                }
            }
        }
        else
        {
            _localPort = getLocalPortFromMPIR(_dpn);
            showPcieState(_dpn);
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Showing Pcie via MPEIN raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showPcieState(DPN& dpn)
{
    MlxlinkCmdPrint pcieInfoCmd;
    sendPrmReg(ACCESS_REG_MPEIN, GET, "depth=%d,pcie_index=%d,node=%d", dpn.depth, dpn.pcieIndex, dpn.node);

    string linkSpeedEnabled = " (" + pcieSpeedStr(getFieldValue("link_speed_enabled")) + ")";
    string linkWidthEnabled = " (" + to_string((getFieldValue("link_width_enabled"))) + "X)";
    _numOfLanesPcie = getFieldValue("link_width_active");

    setPrintTitle(pcieInfoCmd, "PCIe Operational (Enabled) Info", PCIE_INFO_LAST);

    char dpnStr[15];
    sprintf(dpnStr, "%d, %d, %d", dpn.depth, dpn.pcieIndex, dpn.node);
    setPrintVal(pcieInfoCmd, "Depth, pcie index, node", dpnStr);
    setPrintVal(pcieInfoCmd, "Link Speed Active (Enabled)",
                pcieSpeedStr(getFieldValue("link_speed_active")) + linkSpeedEnabled);
    setPrintVal(pcieInfoCmd, "Link Width Active (Enabled)", to_string(_numOfLanesPcie) + "X" + linkWidthEnabled);

    pcieInfoCmd.toJsonFormat(_jsonRoot);

    cout << pcieInfoCmd;
}

void MlxlinkCommander::collectAMBER()
{
    try
    {
        if (_productTechnology >= PRODUCT_16NM)
        {
            MlxlinkRecord::printCmdLine("Collecting amBER and producing report to " + _userInput._csvBer, _jsonRoot);

            initAmBerCollector();

            if (!_isHCA)
            {
                // If port provided, collect one port only
                if (_userInput._portSpecified)
                {
                    PortGroup pg{_localPort, _userInput._labelPort, 0, _userInput._splitPort};
                    if (_devID == DeviceQuantum2 || _devID == DeviceQuantum3 ||
                        dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
                    {
                        pg.secondSplit = _userInput._secondSplitProvided ? _userInput._secondSplitPort : 0;
                    }
                    if (_amberCollector->_localPorts.empty())
                    {
                        _amberCollector->_localPorts.push_back(pg);
                    }
                }
                else
                {
                    // collect all ports info if the port flag wasn't provided
                    u_int32_t numOfPorts = getNumberOfPorts();
                    vector<string> labelPorts;
                    _ignorePortStatus = false;

                    for (u_int32_t labelPort = 1; labelPort <= numOfPorts; labelPort++)
                    {
                        labelPorts.push_back(to_string(labelPort));
                    }

                    if (_localPortsPerGroup.empty())
                    {
                        handleLabelPorts(labelPorts, true);
                    }
                    _amberCollector->_localPorts = _localPortsPerGroup;
                }
            }

            _amberCollector->startCollector();
        }
        else
        {
            throw MlxRegException(AMBER_COLLECT_FLAG " is not available for "
                                                     "this device, please use " BER_COLLECT_FLAG " flag instead");
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Collecting AMBER raised the following exception: \n") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::collectBER()
{
    try
    {
        if (_productTechnology >= PRODUCT_16NM)
        {
            throw MlxRegException(BER_COLLECT_FLAG " is not available for "
                                                   "this device, please use " AMBER_COLLECT_FLAG " flag instead");
        }

        MlxlinkRecord::printCmdLine("Collecting BER and producing report to " + _userInput._csvBer, _jsonRoot);

        const char* fileName = _userInput._csvBer.c_str();
        ifstream ifile(fileName);
        ofstream berFile(fileName, std::ofstream::app);

        vector<AmberField> fields = getBerFields();

        if (!ifile.good())
        {
            for (const auto& field : fields)
            {
                if (field.isVisible())
                {
                    berFile << field.getUiField();
                    if (field.getFieldIndex() < fields.size())
                    {
                        berFile << ",";
                    }
                }
            }
            berFile << endl;
        }

        // Preparing CSV values
        for (const auto& field : fields)
        {
            if (field.isVisible())
            {
                berFile << field.getUiValue();
                if (field.getFieldIndex() < fields.size())
                {
                    berFile << ",";
                }
            }
        }
        berFile << endl;
        berFile.close();
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Collecting BER and producing report raised the following exception: \n") +
                               string(exc.what()) + string("\n");
    }
}

vector<AmberField> MlxlinkCommander::getBerFields()
{
    vector<AmberField> fields;
    try
    {
        string active_fec = _prbsTestMode ? "N/A" : _mlxlinkMaps->_fecModeActive[_fecActive];
        findAndReplace(active_fec, ",", " ");
        string devicePN = getDevicePN();
        string deviceFW = _fwVersion;
        if (!_isSwControled)
        {
            getCableParams();
        }

        std::map<string, string> errorsVector = getRawEffectiveErrors();
        string protocol = _prbsTestMode ? getPrbsModeRX() : _speedStrG;
        float speed = _prbsTestMode ? getPrbsRateRX() : _speedBerCsv;
        if (_protoActive == IB)
        {
            speed = (speed * _numOfLanes) / MAX_LANES_NUMBER;
        }
        string port = to_string(_userInput._labelPort);
        if (_userInput._splitProvided)
        {
            port += "/" + to_string(_userInput._splitPort);
        }

        fields.push_back(AmberField("Test Mode (Nominal/Corner/Drift)", _userInput._testMode));
        fields.push_back(AmberField("Protocol", protocol));
        fields.push_back(AmberField("Speed [Gb/s]", to_string(speed)));
        fields.push_back(AmberField("Active FEC", active_fec));
        fields.push_back(AmberField("Iteration Number", to_string(_userInput._iteration)));
        fields.push_back(AmberField("Device PN", devicePN));
        fields.push_back(AmberField("FW Version", deviceFW));
        fields.push_back(AmberField("Device ID", "1"));
        fields.push_back(AmberField("Port Number", port));
        fields.push_back(AmberField("Media", getCableMedia(_cableMediaType)));
        fields.push_back(AmberField("Cable PN", _cablePN));
        fields.push_back(AmberField("Length [m]", getCableLengthStr(_cableLen, _cmisCable)));
        fields.push_back(AmberField("Attenuation [dB]", to_string(_cableAtten12G)));
        fields.push_back(AmberField("Test time [Min]", errorsVector["time_since_last_clear_sec"]));
        fields.push_back(AmberField("Raw Errors Lane 0", errorsVector["phy_corrected_bits_lane0"]));
        fields.push_back(AmberField("Raw Errors Lane 1", errorsVector["phy_corrected_bits_lane1"]));
        fields.push_back(AmberField("Raw Errors Lane 2", errorsVector["phy_corrected_bits_lane2"]));
        fields.push_back(AmberField("Raw Errors Lane 3", errorsVector["phy_corrected_bits_lane3"]));
        fields.push_back(AmberField("Raw Errors Lane 4", errorsVector["phy_corrected_bits_lane4"]));
        fields.push_back(AmberField("Raw Errors Lane 5", errorsVector["phy_corrected_bits_lane5"]));
        fields.push_back(AmberField("Raw Errors Lane 6", errorsVector["phy_corrected_bits_lane6"]));
        fields.push_back(AmberField("Raw Errors Lane 7", errorsVector["phy_corrected_bits_lane7"]));
        fields.push_back(AmberField("Total Raw BER", errorsVector["raw_ber"]));
        fields.push_back(AmberField("Raw BER limit", to_string(getRawBERLimit())));
        fields.push_back(AmberField("Effective Errors", errorsVector["eff_errors_counter"]));
        fields.push_back(AmberField("Effective BER", errorsVector["eff_ber"]));
        fields.push_back(AmberField("System Voltage", "N/A"));
        fields.push_back(AmberField("Chip Start Temp", "N/A"));
        fields.push_back(AmberField("Chip End Temp", "N/A"));
        fields.push_back(AmberField("Module Start Temp", _moduleTemp));
        fields.push_back(AmberField("Module End Temp", "N/A"));
        fields.push_back(AmberField("Active RTN", "N/A"));
        fields.push_back(AmberField("Device SN", "N/A"));
        fields.push_back(AmberField("Cable SN", _cableSN));
        fields.push_back(AmberField("RX End BW [Gb/s]", "N/A"));
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Collecting BER and producing report raised the following exception: \n") +
                               string(exc.what()) + string("\n");
    }
    return fields;
}

u_int32_t MlxlinkCommander::readBitFromField(const string& fieldName, u_int32_t bitIndex)
{
    char blockName[128];
    u_int32_t blockSelector = bitIndex / MAX_DWORD_BLOCK_SIZE;
    sprintf(blockName, "%s[%d]", fieldName.c_str(), blockSelector);

    u_int32_t bitMask = (u_int32_t)pow(2.0, (int)(bitIndex - (blockSelector * MAX_DWORD_BLOCK_SIZE)));
    u_int32_t bitValue = (getFieldValue(string(blockName)) & bitMask);

    return bitValue;
}

void MlxlinkCommander::showTxGroupMapping()
{
    try
    {
        if (_devID != DeviceSpectrum2 && _devID != DeviceQuantum && _devID != DeviceQuantum2 &&
            _devID != DeviceQuantum3 && _devID != DeviceQuantum4 && 
            !dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            throw MlxRegException("Port group mapping supported for Spectrum-2 and Quantum switches only!");
        }

        sendPrmReg(ACCESS_REG_PGMR, GET, "local_port=%d,group=%d,pg_sel=%d", 1, _userInput._showGroup, TX_GROUP);

        vector<u_int32_t> localPorts;
        u_int32_t localPortMask = 0;
        for (size_t i = 1; i <= maxLocalPort(); i++)
        {
            localPortMask = readBitFromField("ports_mapping_of_group", i - 1);
            if (localPortMask)
            {
                localPorts.push_back(i);
            }
        }

        string ports = getStringFromVector(localToPortsPerGroup(localPorts));

        setPrintTitle(_portGroupMapping, "Tx Port Group Mapping ", 1);
        char title[64];
        sprintf(title, "Ports Mapped to Group %d", _userInput._showGroup);
        setPrintVal(_portGroupMapping, title, ports, ANSI_COLOR_RESET, true, !_prbsTestMode && !ports.empty(), true);

        cout << _portGroupMapping;
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Showing ports group mapping raised the "
                                      "following exception: ") +
                               string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::getLabelPortString(const PortGroup& portInfo)
{
    string labelPortStr = " " + to_string(portInfo.labelPort);

    if (portInfo.split != 0)
    {
        labelPortStr += "/" + to_string(portInfo.split);
    }

    if (portInfo.secondSplit != 0)
    {
        labelPortStr += "/" + to_string(portInfo.secondSplit);
    }

    labelPortStr += "(" + to_string(portInfo.localPort) + ")";

    // Add IB port information if applicable
    if (_protoActive == IB && !_isHCA)
    {
        sendPrmReg(ACCESS_REG_PLIB, GET);
        labelPortStr += " " + std::to_string(getFieldValue("ib_port"));
    }

    if (portInfo.isFnm)
    {
        labelPortStr += "(FNM)";
    }

    return labelPortStr;
}

void MlxlinkCommander::updatePortModuleInfo(vector<string>& tableData,
                                            const PortGroup& portInfo,
                                            u_int32_t& posToUpdateWidthInVector)
{
    // Update local port and get cable parameters
    _localPort = portInfo.localPort;
    if (!_isSwControled)
    {
        getCableParams();
    }

    // Get cable information strings
    std::string cableLenStr = getCableLengthStr(_cableLen, _cmisCable);
    cableLenStr = (cableLenStr == "0" || cableLenStr == "0.0") ? "" : getCableLengthStr(_cableLen, _cmisCable) + "m";
    std::string cableTypeStr = _isSwControled ? "sw cntrld" : _mlxlinkMaps->_cableTypeForTableDisplay[_cableMediaType];

    // Get speed and color information
    std::string speedStr = getSpeedStrForTableView();
    string color =
      MlxlinkRecord::state2Color(_phyMngrFsmState == PHY_MNGR_RX_DISABLE ? YELLOW : (STATUS_COLOR)_phyMngrFsmState);
    string resetColor = MlxlinkRecord::state2Color(RESET);

    // Update table with cable information
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   _cableSN, _cableSN.length(), !_isSwControled);
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   _cablePN, _cablePN.length(), !_isSwControled);
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   cableLenStr, cableLenStr.length(), !_isSwControled);
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   cableTypeStr, cableTypeStr.length());

    // Update table with port state and speed information
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   color + _mlxlinkMaps->_phyMgrStateForTableDisplay[_phyMngrFsmState] + resetColor,
                                   _mlxlinkMaps->_phyMgrStateForTableDisplay[_phyMngrFsmState].length());
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   speedStr, speedStr.length());
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   _mlxlinkMaps->_fecModeActiveForTableDispaly[_fecActive],
                                   _mlxlinkMaps->_fecModeActiveForTableDispaly[_fecActive].length(),
                                   _phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);

    // Update table with BER information
    std::string berStr = getBerString();
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   berStr, berStr.length());
}

void MlxlinkCommander::showMultiPortModuleInfo()
{
    // Set up table header with appropriate label
    string label_port = (_protoActive == IB) ? "Label(Pport)IBport" : "Label(Pport)";
    _mlxlinkMaps->_multiPortModuleInfoTableHeader.insert(_mlxlinkMaps->_multiPortModuleInfoTableHeader.begin(),
                                                         std::make_pair(label_port, label_port.length()));

    std::vector<std::string> tableData = {};
    updateLocalPortGroup();

    // Process each port group
    for (const auto& portInfo : _localPortsPerGroup)
    {
        u_int32_t posToUpdateWidthInVector = 0;

        // Get and update label port string
        _localPort = portInfo.localPort;
        string labelPortStr = getLabelPortString(portInfo);
        updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortModuleInfoTableHeader, posToUpdateWidthInVector++,
                                       tableData, labelPortStr, labelPortStr.length());

        // Update port information in table
        updatePortModuleInfo(tableData, portInfo, posToUpdateWidthInVector);
    }

    // Print the final table
    printMlxlinkTable(tableData, _mlxlinkMaps->_multiPortModuleInfoTableHeader);
}

void MlxlinkCommander::updatePortInfo(vector<string>& tableData,
                                      const PortGroup& portInfo,
                                      u_int32_t& posToUpdateWidthInVector)
{
    _localPort = portInfo.localPort;
    _fomStr = "";

    string labelPortStr = getLabelPortString(portInfo);
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   labelPortStr, labelPortStr.length());

    std::string speedStr = getSpeedStrForTableView();
    getPddrOperInfo();

    string color =
      MlxlinkRecord::state2Color(_phyMngrFsmState == PHY_MNGR_RX_DISABLE ? YELLOW : (STATUS_COLOR)_phyMngrFsmState);
    string resetColor = MlxlinkRecord::state2Color(RESET);

    // Update state and speed info
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   color + _mlxlinkMaps->_phyMgrStateForTableDisplay[_phyMngrFsmState] + resetColor,
                                   _mlxlinkMaps->_phyMgrStateForTableDisplay[_phyMngrFsmState].length());
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   speedStr, speedStr.length());

    // Update FEC info
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   _mlxlinkMaps->_fecModeActiveForTableDispaly[_fecActive],
                                   _mlxlinkMaps->_fecModeActiveForTableDispaly[_fecActive].length(),
                                   _phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);

    // Update cable info
    if (!_isSwControled)
    {
        getCableParams();
    }
    string cableLenStr = getCableLengthStr(_cableLen, _cmisCable);
    cableLenStr = (cableLenStr == "0" || cableLenStr == "0.0") ? "" : "/" + cableLenStr + "m";
    std::string cableInfoStr =
      _isSwControled ? "sw cntrld" : _mlxlinkMaps->_cableTypeForTableDisplay[_cableMediaType] + cableLenStr;
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   cableInfoStr, cableInfoStr.length(),
                                   !(_cableMediaType == UNPLUGGED || _cableMediaType == UNIDENTIFIED));

    // Update time to link up info
    sendPrmReg(ACCESS_REG_PDDR, GET, "page_select=%d", PDDR_MODULE_LINK_UP_INFO_PAGE);
    string ttluStr = string_format("%.3f sec", (float)(getFieldValue("time_to_link_up")) / 1000);
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   ttluStr, ttluStr.length(), _phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);

    // Update statistical info
    updatePortStatisticalInfo(tableData, posToUpdateWidthInVector);

    // Update eye info
    if (_productTechnology <= PRODUCT_16NM)
    {
        prepare40_28_16nmEyeInfo(_numOfLanes);
    }
    else if (_productTechnology == PRODUCT_7NM)
    {
        prepare7nmEyeInfo(_numOfLanes);
    }
    else if (_productTechnology == PRODUCT_5NM)
    {
        prepare5nmEyeInfo(_numOfLanes);
    }

    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   _fomStr, _fomStr.length());

    // Update BER info
    std::string berStr = getBerString();
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   color + berStr + resetColor, berStr.length());

    // Update link down and FC zero info
    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);
    std::string linkDownStr = getFieldStr("link_down_events");
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   linkDownStr, linkDownStr.length(), _phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);

    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);
    std::string fcZeroHist = to_string(getFieldValue("fc_zero_hist"));
    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   fcZeroHist, fcZeroHist.length(), _phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);
}

void MlxlinkCommander::updatePortStatisticalInfo(vector<string>& tableData, u_int32_t& posToUpdateWidthInVector)
{
    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);
    char buff[64];
    double val =
      (double)add32BitTo64(getFieldValue("time_since_last_clear_high"), getFieldValue("time_since_last_clear_low")) /
      60000.0;
    sprintf(buff, "%.01f min", val);
    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);

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
    sprintf(clBerStr, "%s/%.1E%%", buff, clBer);

    updateColumnWidthPopulateTable(_mlxlinkMaps->_multiPortInfoTableHeader, posToUpdateWidthInVector++, tableData,
                                   clBerStr, strlen(clBerStr));
}

void MlxlinkCommander::showMultiPortInfo()
{
    std::vector<std::string> tableData = {};
    updateLocalPortGroup();

    for (const auto& portInfo : _localPortsPerGroup)
    {
        u_int32_t posToUpdateWidthInVector = 0;
        updatePortInfo(tableData, portInfo, posToUpdateWidthInVector);
    }

    printMlxlinkTable(tableData, _mlxlinkMaps->_multiPortInfoTableHeader);
}

std::map<string, string> MlxlinkCommander::getRawEffectiveErrorsinTestMode()
{
    std::map<string, string> errorsVector;

    sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHY_GROUP);

    errorsVector["phy_corrected_bits_lane0"] =
      to_string(add32BitTo64(getFieldValue("edpl_bip_errors_lane0_high"), getFieldValue("edpl_bip_errors_lane0_low")));
    errorsVector["phy_corrected_bits_lane1"] =
      to_string(add32BitTo64(getFieldValue("edpl_bip_errors_lane1_high"), getFieldValue("edpl_bip_errors_lane1_low")));
    errorsVector["phy_corrected_bits_lane2"] =
      to_string(add32BitTo64(getFieldValue("edpl_bip_errors_lane2_high"), getFieldValue("edpl_bip_errors_lane2_low")));
    errorsVector["phy_corrected_bits_lane3"] =
      to_string(add32BitTo64(getFieldValue("edpl_bip_errors_lane3_high"), getFieldValue("edpl_bip_errors_lane3_low")));
    errorsVector["phy_corrected_bits_lane4"] = "0";
    errorsVector["phy_corrected_bits_lane5"] = "0";
    errorsVector["phy_corrected_bits_lane6"] = "0";
    errorsVector["phy_corrected_bits_lane7"] = "0";

    return errorsVector;
}

std::map<string, string> MlxlinkCommander::getRawEffectiveErrors()
{
    std::map<string, string> errorsVector;
    if (_prbsTestMode)
    {
        errorsVector = getRawEffectiveErrorsinTestMode();
    }
    else
    {
        sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);

        errorsVector["phy_corrected_bits_lane0"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane0_high"), getFieldValue("phy_raw_errors_lane0_low")));
        errorsVector["phy_corrected_bits_lane1"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane1_high"), getFieldValue("phy_raw_errors_lane1_low")));
        errorsVector["phy_corrected_bits_lane2"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane2_high"), getFieldValue("phy_raw_errors_lane2_low")));
        errorsVector["phy_corrected_bits_lane3"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane3_high"), getFieldValue("phy_raw_errors_lane3_low")));
        errorsVector["phy_corrected_bits_lane4"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane4_high"), getFieldValue("phy_raw_errors_lane4_low")));
        errorsVector["phy_corrected_bits_lane5"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane5_high"), getFieldValue("phy_raw_errors_lane5_low")));
        errorsVector["phy_corrected_bits_lane6"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane6_high"), getFieldValue("phy_raw_errors_lane6_low")));
        errorsVector["phy_corrected_bits_lane7"] = to_string(
          add32BitTo64(getFieldValue("phy_raw_errors_lane7_high"), getFieldValue("phy_raw_errors_lane7_low")));
    }

    errorsVector["time_since_last_clear_sec"] = to_string(
      (add32BitTo64((float)getFieldValue("time_since_last_clear_high"), getFieldValue("time_since_last_clear_low"))) /
      1000.0 / 60.0);
    errorsVector["raw_errors_counter"] =
      to_string(add32BitTo64(getFieldValue("phy_corrected_bits_high"), getFieldValue("phy_corrected_bits_low")));
    errorsVector["raw_ber"] = getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude");
    errorsVector["eff_errors_counter"] =
      to_string(add32BitTo64(getFieldValue("phy_symbol_errors_high"), getFieldValue("phy_symbol_errors_low")));
    errorsVector["eff_ber"] = getFieldStr("effective_ber_coef") + "E-" + getFieldStr("effective_ber_magnitude");

    return errorsVector;
}

string MlxlinkCommander::getSupportedPrbsRates(u_int32_t modeSelector)
{
    string regName = ACCESS_REG_PPRT;
    if (modeSelector == PRBS_TX)
    {
        regName = ACCESS_REG_PPTT;
    }
    sendPrmReg(regName, GET);

    u_int32_t capsMask = getFieldValue("lane_rate_cap");
    string modeCapStr = "";

    for (auto it = _mlxlinkMaps->_prbsLaneRate.begin(); it != _mlxlinkMaps->_prbsLaneRate.end(); it++)
    {
        if (capsMask & (it->second).capMask)
        {
            modeCapStr += it->first + string(",");
        }
    }

    return deleteLastChar(modeCapStr);
}

string MlxlinkCommander::getSupportedPrbsModes(u_int32_t modeSelector)
{
    string regName = ACCESS_REG_PPRT;
    if (modeSelector == PRBS_TX)
    {
        regName = ACCESS_REG_PPTT;
    }
    sendPrmReg(regName, GET);

    u_int32_t capsMask = getFieldValue("prbs_modes_cap");
    capsMask = modeSelector == PRBS_RX ? capsMask & 0x1ffe3fff : capsMask;
    string modeCapStr = "";
    // Iterating over the supported modes according to capability mask
    // And preparing them in one string
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

string MlxlinkCommander::getPrbsModeRX()
{
    sendPrmReg(ACCESS_REG_PPRT, GET, "e=%d", PPRT_PPTT_ENABLE);

    return prbsMaskToMode(getFieldValue("prbs_mode_admin"), PRBS_RX);
}

u_int32_t MlxlinkCommander::getPrbsRateRX()
{
    sendPrmReg(ACCESS_REG_PPRT, GET, "e=%d", PPRT_PPTT_ENABLE);

    return prbsMaskToRateNum(getFieldValue("lane_rate_oper"));
}

float MlxlinkCommander::getRawBERLimit()
{
    float limit;
    if (_userInput._testMode == "NOMINAL" || _userInput._testMode == "Nominal")
    {
        switch (_speedBerCsv)
        {
            case 25:
            case 50:
            case 100:
                if (_mlxlinkMaps->_fecModeActive[_fecActive] == _mlxlinkMaps->_fecModeActive[0])
                {
                    limit = pow(10.0, NOMINAL_25G_NO_FEC);
                }
                else if (_cableAtten12G <= 15)
                {
                    limit = pow(10.0, NOMINAL_25G_LOW_ATTN);
                }
                else
                {
                    limit = pow(10.0, NOMINAL_25G_HIGH_ATTN);
                }
                break;

            case 10:
                limit = pow(10.0, NOMINAL_10G);
                break;

            case 56:
            case 40:
                limit = pow(10.0, NOMINAL_56G_40G);
                break;

            default:
                limit = pow(10.0, NOMINAL_DEFAULT);
        }
    }
    else
    {
        switch (_speedBerCsv)
        {
            case 25:
            case 50:
            case 100:
                if (_mlxlinkMaps->_fecModeActive[_fecActive] == _mlxlinkMaps->_fecModeActive[0])
                {
                    limit = 3.0 * pow(10.0, CORNER_25G_NO_FEC);
                }
                else if (_cableAtten12G <= 15)
                {
                    limit = pow(10.0, CORNER_25G_LOW_ATTN);
                }
                else
                {
                    limit = pow(10.0, CORNER_25G_HIGH_ATTN);
                }
                break;

            case 10:
                limit = pow(10.0, CORNER_10G);
                break;

            case 56:
            case 40:
                limit = pow(10.0, CORNER_56G_40G);
                break;

            default:
                limit = pow(10.0, CORNER_DEFAULT);
        }
    }
    return limit;
}

string MlxlinkCommander::getFwVersion()
{
    return _fwVersion;
}

string MlxlinkCommander::getDevicePN()
{
    try
    {
        sendPrmReg(ACCESS_REG_MSGI, GET);
    }
    catch (...)
    {
        return "N/A";
    }

    return getAscii("part_number", 20);
}

// Config functions

void MlxlinkCommander::clearCounters()
{
    try
    {
        MlxlinkRecord::printCmdLine("Clearing Counters", _jsonRoot);
        if (_mf->tp != MST_IB)
        {
            sendPrmReg(ACCESS_REG_PPCNT, SET, "clr=%d,grp=%d", 1, PPCNT_ALL_GROUPS);
        }
        else
        {
            // Clearing counters via GET method instead of SET due to register being too large for MADs.
            for (auto const& group : _mlxlinkMaps->_ppcntGroups)
            {
                sendPrmReg(ACCESS_REG_PPCNT, GET, "clr=%d,grp=%d", 1, group.first);
            }
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Clearing counters via PPCNT raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::isPmaosResetToggleSupported()
{
    bool supported = false;
    // checking force_down cap
    // important note: by FW implmentation the feature_cap_mask is implemented reversed.
    // meaning bit 14 in PRM will be in feature_cap_mask[(128-14)\32 -1]
    u_int64_t fdCapMask = PCAM_PMAOS_RESET_TOGGLE_CAP_MASK; // feature_cap_mask.Bit 14 (feature_cap_mask[3].bit 14)

    sendPrmReg(ACCESS_REG_PCAM, GET);

    supported = getFieldValue("feature_cap_mask[3]") & fdCapMask;
    return supported;
}

bool MlxlinkCommander::isForceDownSupported()
{
    bool supported = false;
    if (_isHCA)
    {
        // checking force_down cap
        // important note: by FW implmentation the feature_cap_mask is implemented reversed.
        // meaning bit 45 in PRM will be in feature_cap_mask[(128-45)\32 -1]
        u_int64_t fdCapMask = PCAM_FORCE_DOWN_CAP_MASK; // feature_cap_mask.Bit 45 (feature_cap_mask[2].bit 13)

        sendPrmReg(ACCESS_REG_PCAM, GET);

        supported = getFieldValue("feature_cap_mask[2]") & fdCapMask;
    }
    return supported;
}

void MlxlinkCommander::sendGBPaosCmd(PAOS_ADMIN adminStatus, bool forceDown)
{
    try
    {
        string forceDownCmd = "";
        if (forceDown)
        {
            forceDownCmd = ",fpd=1";
        }
        sendPrmReg(ACCESS_REG_PPAOS, SET, "phy_status_admin=%d%s", adminStatus == PAOS_UP, forceDownCmd.c_str());
    }
    catch (const std::exception& exc)
    {
        string portCommand = (adminStatus == PAOS_DOWN) ? "down" : "up";
        throw MlxRegException("Sending port " + portCommand + " command failed, " + string(exc.what()));
    }
}

void MlxlinkCommander::sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown)
{
    try
    {
        if (_isGboxPort)
        {
            sendGBPaosCmd(adminStatus, forceDown);
        }
        else
        {
            // Send force down for test mode only
            string forceDownCmd = "";
            if (!_userInput._prbsMode.empty())
            {
                if (forceDown)
                {
                    forceDownCmd = ",fd=1";
                }
            }
            sendPrmReg(ACCESS_REG_PAOS, SET, "admin_status=%d,ase=%d%s", adminStatus, 1, forceDownCmd.c_str());
        }
    }
    catch (const std::exception& exc)
    {
        string portCommand = (adminStatus == PAOS_DOWN) ? "down" : "up";
        throw MlxRegException("Sending port " + portCommand + " command failed");
    }
}

bool MlxlinkCommander::checkPmaosDown()
{
    sendPrmReg(ACCESS_REG_PMLP, GET);
    _moduleNumber = getFieldValue("module_0");
    sendPrmReg(ACCESS_REG_PMAOS, GET, "module=%d", _moduleNumber);

    u_int32_t paosOperStatus = getFieldValue("oper_status");
    return (paosOperStatus == PMAOS_OPER_UNPLUGGED);
}

void MlxlinkCommander::sendPmaosCmd(PMAOS_ADMIN adminStatus)
{
    sendPrmReg(ACCESS_REG_PMLP, GET);
    _moduleNumber = getFieldValue("module_0");
    try
    {
        if (adminStatus == PMAOS_TOGGLE)
        {
            sendPrmReg(ACCESS_REG_PMAOS, SET, "module=%d,rst=%d,ase=%d", _moduleNumber, 1, 1);
        }
        else
        {
            sendPrmReg(ACCESS_REG_PMAOS, SET, "module=%d,admin_status=%d,ase=%d", _moduleNumber, adminStatus, 1);
        }
    }
    catch (const std::exception& exc)
    {
        string portCommand = (adminStatus == PMAOS_DISABLED) ? "down" :
                             (adminStatus == PMAOS_ENABLED)  ? "up" :
                                                               "toggle";
        throw MlxRegException("Sending module number: " + to_string(_moduleNumber) + " with a " + portCommand +
                              " command failed at:" + exc.what());
    }
}

void MlxlinkCommander::sendPmaos()
{
    if (_isSwControled)
    {
        _allUnhandledErrors += string("No plugged cable detected\n");
        return;
    }

    try
    {
        PMAOS_CMD pmaosCmd = pmaos_to_int(_userInput._pmaosCmd);
        switch (pmaosCmd)
        {
            case PMAOS_UP:
                sendPmaosUP();
                return;

            case PMAOS_DN:
                sendPmaosDown();
                return;

            case PMAOS_TG:
                sendPmaosToggle();
                return;

            case PMAOS_NO:
            default:
                return;
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Sending PMAOS raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::sendPmaosDown()
{
    MlxlinkRecord::printCmdLine("PMAOS: Configuring Module State (Down)", _jsonRoot);
    sendPmaosCmd(PMAOS_DISABLED);
    msleep(1000);
    if (!checkPmaosDown())
    {
        throw MlxRegException("Module state is not unplugged, Aborting...");
    }
}

void MlxlinkCommander::sendPmaosUP()
{
    MlxlinkRecord::printCmdLine("PMAOS: Configuring Module State (Up)", _jsonRoot);
    sendPmaosCmd(PMAOS_ENABLED);
}

void MlxlinkCommander::sendPmaosToggle()
{
    bool pmaosToggleSupported = isPmaosResetToggleSupported();
    if (pmaosToggleSupported)
    {
        MlxlinkRecord::printCmdLine("PMAOS: Configuring Module State (Reset)", _jsonRoot);
        sendPmaosCmd(PMAOS_TOGGLE);
    }
    else
    {
        sendPmaosDown();
        msleep(1000);
        sendPmaosUP();
    }
}

void MlxlinkCommander::sendPaos()
{
    try
    {
        PAOS_CMD paosCmd = paos_to_int(_userInput._paosCmd);
        switch (paosCmd)
        {
            case UP:
                sendPaosUP();
                return;

            case DN:
                sendPaosDown();
                return;

            case TG:
                sendPaosToggle();
                return;

            case NO:
            default:
                return;
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Sending PAOS raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::sendPaosDown(bool toggleCommand)
{
    MlxlinkRecord::printCmdLine("Configuring Port State (Down)", _jsonRoot);

    bool forceDown = isForceDownSupported();
    // try to force down the port
    sendPaosCmd(PAOS_DOWN, forceDown);
    msleep(2000); // wait for 2 sec before checking the status
    // Verify the link status after down command
    if (!checkPaosDown())
    {
        // in case of using old fw version (older than xx.28.xxxx)
        if (_isHCA && !forceDown && !_userInput._prbsMode.empty() && !toggleCommand)
        {
            string message = "Enabling PRBS is not supported in the "
                             "current FW version. Please contact Nvidia networking division support.";
            throw MlxRegException(message);
        }
        else if (_isHCA && !toggleCommand)
        {
            string protocol = (_protoActive == IB) ? "IB" : "ETH";
            string message = "port is not Down, for some reasons:\n";
            message +=
              "1- The link is configured to be up, run this command if KEEP_" + protocol + "_LINK_UP_Px is True:\n";
            message +=
              "   mlxconfig -d " + _userInput._device + " set KEEP_" + protocol + "_LINK_UP_P<port_number>=0\n";
            message += "2- Port management is enabled (management protocol requiring the link to remain up, PAOS "
                       "won't manage to disable the port)\n";
            message += "3- In case of multi-host please verify all hosts are not holding the port up";
            throw MlxRegException(message);
        }
        // Toggle command == true or not HCA
        else
        {
            throw MlxRegException("Port is not Down, Aborting...");
        }
    }
}

void MlxlinkCommander::sendPaosUP()
{
    MlxlinkRecord::printCmdLine("Configuring Port State (Up)", _jsonRoot);
    sendPaosCmd(PAOS_UP);
}

void MlxlinkCommander::sendPaosToggle()
{
    sendPaosDown(true);
    sendPaosUP();
}

void MlxlinkCommander::setPlaneIndex(int planeIndex)
{
    int suppPlanes = -1;

    try
    {
        sendPrmReg(ACCESS_REG_PPCR, GET, "local_port=%d", 1);
        suppPlanes = getFieldValue("num_of_planes");
    }
    catch (...)
    {
        // If the PPCR reg is not supported, this also means that the device does not support planarization
    }

    if (suppPlanes == -1 && planeIndex >= 0)
    {
        throw MlxRegException("Invalid usage of the plane flag, the provided device does not support planarization");
    }

    if (planeIndex > suppPlanes)
    {
        throw MlxRegException("Invalid plane index selection, maximum number of available planes to query is %d",
                              suppPlanes);
    }

    // set the planeInd field in reg_parser class
    if (planeIndex == -1)
    {
        _planeInd = 0;
    }
    else
    {
        _planeInd = planeIndex;
    }
}

bool MlxlinkCommander::isTransmitAllowed(u_int32_t localPort, u_int32_t protoActive)
{
    // the mlxlink_reg_parser already handles lp_msb when localPort is provided
    sendPrmReg(ACCESS_REG_PTYS, GET, "local_port=%d,proto_mask=%d", localPort, protoActive);
    u_int32_t txAllowed = getFieldValue("transmit_allowed");
    return txAllowed;
}

void MlxlinkCommander::handlePrbsSWControlledChecks()
{
    string modulePath = _userInput._sysfsPath;
    bool modulePresent = isModulePresent(modulePath);
    if (modulePresent)
    {
        if (_mf->tp == MST_REMOTE)
        {
            throw MlxRegException("SW controlled PRBS test mode is not supported for remote connection.");
        }
        if (!(_userInput._skipPowerGoodCheck || isModulePoweredOn(modulePath)))
        {
            throw MlxRegException(
              "PRBS test mode is not supported for the current port!\nmodule <%s> is not powered on",
              modulePath.c_str());
        }

        if (!isTransmitAllowed(_localPort, _protoActive))
        {
            if (_userInput._forceTxAllowed)
            {
                string warMsg =
                  "Transmission is not allowed, but force_tx_allowed is set. Tool will attempt to set it now.";
                MlxlinkRecord::printWar(warMsg, _jsonRoot);
                if (!askUser("Do you want to continue", _userInput.force))
                {
                    throw MlxRegException("Operation canceled by user");
                }
            }
            else
            {
                throw MlxRegException("PRBS test mode is not supported for the current port!\nTransmit not allowed");
            }
        }
        sendPrmReg(ACCESS_REG_PTYS, GET, "local_port=%d,proto_mask=%d", _localPort, _protoActive);
        sendPrmRegWithoutReset(ACCESS_REG_PTYS, SET,
                               "local_port=%d,proto_mask=%d,ee_tx_ready=1,tx_ready_e=3,transmit_allowed=1", _localPort,
                               _protoActive);
        sendPaosToggle();
    }
    else
    {
        string warMsg =
          "module <" + modulePath +
          "> was not found, if you are sure the module is set correctly you can skip SW controlled checks and continue to set PRBS test mode\n";
        MlxlinkRecord::printWar(warMsg, _jsonRoot);
        if (!askUser("Do you want to continue with PRBS test mode", _userInput.force))
        {
            throw MlxRegException("Operation canceled by user after module was not found");
        }
    }
}

void MlxlinkCommander::handlePrbs()
{
    if (_isSwControled && _userInput._prbsMode == "EN") // this covers both SW controlled and independent module.
    {
        handlePrbsSWControlledChecks();
    }
    else
    {
        // at this point we know we are running PRBS on a FW controlled module, need to throw error if the user used one
        // of the SW controlled flags.
        if (_userInput._skipPowerGoodCheck || _userInput._forceTxAllowed || _userInput._sysfsPathGiven)
        {
            throw MlxRegException("SW controlled flags are not supported for FW controlled modules");
        }
    }

    try
    {
        if (_userInput._prbsMode == "EN")
        {
            checkDcCouple();
            checkPprtPptt();
            if (_prbsTestMode)
            {
                sendPrbsPpaos(false);
            }
            sendPaosDown();
            if (checkPaosDown())
            {
                MlxlinkRecord::printCmdLine("Configuring Port to Physical Test Mode", _jsonRoot);
                resetPprtPptt();
                sendPprtPptt();
                sendPrbsPpaos(true, _userInput._prbsDcCoupledAllow);
            }
            else
            {
                throw MlxRegException("Port is not down, unable to enter test mode");
            }
        }
        else if (_userInput._prbsMode == "DS")
        {
            MlxlinkRecord::printCmdLine("Configuring Port to Regular Operation", _jsonRoot);
            if (_prbsTestMode)
            {
                sendPrbsPpaos(false);
            }
            resetPprtPptt();
            sendPaosToggle();
        }
        else if (_userInput._prbsMode == "TU")
        {
            if (_prbsTestMode)
            {
                MlxlinkRecord::printCmdLine("Performing Tuning", _jsonRoot);
                startTuning();
            }
            else
            {
                throw MlxRegException("Port is not configured for physical test mode. Please see help");
            }
        }
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Handling PRBS raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::checkPRBSModeCap(u_int32_t modeSelector, u_int32_t capMask)
{
    string modeToCheck = _userInput._pprtMode;
    string prbsModeStr = "RX";
    if (modeSelector == PRBS_TX)
    {
        modeToCheck = _userInput._ppttMode;
        prbsModeStr = "TX";
    }
    // for RX mode: SQUARE_WAVE and SQUARE_WAVEA have the same enum
    if (modeSelector == PRBS_RX && modeToCheck == "SQUARE_WAVE")
    {
        modeToCheck += "A";
    }

    // Fetching mode capability from mode list
    u_int32_t modeCap = 0;

    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
         it != _mlxlinkMaps->_prbsModesList.end();
         it++)
    {
        if (modeToCheck == it->second)
        {
            modeCap = PRBS31_CAP << it->first;
            break;
        }
    }
    // checking if the fetched capability supported in cap mask or not
    if (!(modeCap & capMask))
    {
        string errStr = "Device does not support " + prbsModeStr + " PRBS pattern \"" +
                        (modeSelector == PRBS_TX ? _userInput._ppttMode : _userInput._pprtMode) +
                        "\" in physical test mode.";
        errStr += "\nValid RX PRBS modes Are: " + getSupportedPrbsModes(PRBS_RX);
        errStr += "\nValid TX PRBS modes Are: " + getSupportedPrbsModes(PRBS_TX);
        errStr += "\nDefault PRBS Mode is PRBS31";
        throw MlxRegException(errStr);
    }
}

void MlxlinkCommander::checkPrbsRegsCap(const string& prbsReg, const string& laneRate)
{
    u_int32_t modeSelector = (prbsReg == "PPTT") ? PRBS_TX : PRBS_RX;

    sendPrmReg(prbsReg, GET);

    bool invalidRateStr = !laneRate.empty() && !_mlxlinkMaps->_prbsLaneRate[laneRate].capMask;

    u_int32_t laneRateCap = _mlxlinkMaps->_prbsLaneRate[laneRate].capMask ?
                              _mlxlinkMaps->_prbsLaneRate[laneRate].capMask :
                              (u_int32_t)LANE_RATE_EDR_CAP;

    string laneRateStr = laneRate.empty() ? "EDR/25G/50G/100G (25.78125 Gb/s)" : laneRate;

    if (invalidRateStr || !(laneRateCap & getFieldValue("lane_rate_cap")))
    {
        string errStr = "Device does not support lane rate " + laneRateStr + " in physical test mode.\n";
        string rxRates = getSupportedPrbsRates(PRBS_RX);
        string txRates = getSupportedPrbsRates(PRBS_TX);
        if (rxRates.empty())
        {
            rxRates = "No Valid RX PRBS lane rate";
        }
        else
        {
            rxRates = "Valid RX PRBS lane rates: " + rxRates;
        }
        errStr += rxRates + "\n";
        if (txRates.empty())
        {
            txRates = "No Valid TX PRBS lane rate";
        }
        else
        {
            txRates = "Valid TX PRBS lane rates: " + txRates;
        }
        errStr += txRates + "\n";
        errStr += "Default PRBS Lane Rate is EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)";
        throw MlxRegException(errStr);
    }

    checkPRBSModeCap(modeSelector, getFieldValue("prbs_modes_cap"));

    if (!_userInput._prbsLanesToSet.empty())
    {
        if (getFieldValue("ls") != 1)
        {
            throw MlxRegException("Device does not support per lane configuration");
        }
    }
}

void MlxlinkCommander::checkPprtPptt()
{
    if (!_userInput._prbsLanesToSet.empty())
    {
        u_int32_t maxLaneIndex = _numOfLanes - 1;
        for (map<u_int32_t, bool>::iterator it = _userInput._prbsLanesToSet.begin();
             it != _userInput._prbsLanesToSet.end();
             it++)
        {
            if (it->second && (it->first > maxLaneIndex))
            {
                throw MlxRegException("Invalid lane index: %d", it->first);
            }
        }
    }

    checkPrbsModulation("PPRT");
    checkPrbsModulation("PPTT");

    checkPrbsRegsCap("PPRT", _userInput._pprtRate);
    checkPrbsRegsCap("PPTT", _userInput._ppttRate);

    if (_userInput._prbsTxInv)
    {
        checkPrbsPolCap("PPTT");
    }
    if (_userInput._prbsRxInv)
    {
        checkPrbsPolCap("PPRT");
    }
}

void MlxlinkCommander::checkPrbsModulation(const string& prbsReg)
{
    string modulation = prbsReg == "PPRT" ? _userInput._pprtModulation : _userInput._ppttModulation;
    string invalidModulation = prbsReg == "PPRT" ? "RX" : "TX";

    if (!modulation.empty() && _mlxlinkMaps->_prbsModulationValue.count(modulation) == 0)
    {
        vector<string> modulationKeys;

        // transform the map to a vector of strings
        std::transform(_mlxlinkMaps->_prbsModulationValue.begin(), _mlxlinkMaps->_prbsModulationValue.end(),
                       std::back_inserter(modulationKeys), [](const pair<string, uint32_t>& p) { return p.first; });
        string valid_modulations = getStringFromVector(modulationKeys);
        throw MlxRegException("Invalid %s modulation: %s, valid values are: %s", invalidModulation.c_str(),
                              modulation.c_str(), valid_modulations.c_str());
    }
}

void MlxlinkCommander::checkPrbsPolCap(const string& prbsReg)
{
    string invalidPol = "TX";
    if (prbsReg == "PPRT")
    {
        invalidPol = "RX";
    }

    sendPrmReg(prbsReg, GET);

    if (!getFieldValue("p_c"))
    {
        throw MlxRegException("PRBS " + invalidPol + " polarity inversion not supported");
    }
}

void MlxlinkCommander::checkDcCouple()
{
    sendPrmReg(ACCESS_REG_PPAOS, GET);
    int dcCoupledPort = getFieldValue("dc_cpl_port");
    if (!dcCoupledPort && _userInput._prbsDcCoupledAllow)
    {
        throw MlxRegException("Allowing DC coupling PRBS isn't supported to non DC coupled ports");
    }
    else if (dcCoupledPort && !_userInput._prbsDcCoupledAllow)
    {
        throw MlxRegException("When enabling test_mode in DC coupled ports, DC coupling should be allowed!");
    }
    else if (dcCoupledPort && _userInput._prbsDcCoupledAllow)
    {
        string warMsg =
          "Warning: DC couple system must be powered on both sides of the physical link prior to enabling test mode.\n";
        warMsg += "System may be harmed and product lifetime may shortened if not ensured.";
        MlxlinkRecord::printWar(warMsg, _jsonRoot);
        if (!askUser("Do you want to continue", _userInput.force))
        {
            throw MlxRegException("Operation canceled by user");
        }
    }
}

void MlxlinkCommander::sendPrbsPpaos(bool testMode, bool dc_cpl_allow)
{
    if (dc_cpl_allow)
    {
        sendPrmReg(ACCESS_REG_PPAOS, SET, "phy_test_mode_admin=%d,dc_cpl_allow=%d",
                   (testMode ? PPAOS_PHY_TEST_MODE : PPAOS_REGULAR_OPERATION), PPAOS_DC_CPL_ALLOW);
    }
    else
    {
        sendPrmReg(ACCESS_REG_PPAOS, SET, "phy_test_mode_admin=%d",
                   (testMode ? PPAOS_PHY_TEST_MODE : PPAOS_REGULAR_OPERATION));
    }
}

void MlxlinkCommander::startTuning()
{
    sendPrmReg(ACCESS_REG_PPRT, SET, "e=%d,s=%d", PPRT_PPTT_ENABLE, PPRT_PPTT_START_TUNING);
}

void MlxlinkCommander::prbsConfiguration(const string& prbsReg,
                                         bool enable,
                                         u_int32_t laneRate,
                                         u_int32_t prbsMode,
                                         bool perLaneConfig,
                                         bool prbsPolInv,
                                         u_int32_t modulation)
{
    const string rateToUpdate = (prbsReg == "PPRT") ? "lane_rate_oper" : "lane_rate_admin";

    auto buildPrbsRegArgs = [&]() -> string
    {
        stringstream cmd;
        if (prbsPolInv)
        {
            cmd << ",p=1";
        }
        // Handle modulation field
        if (modulation != PRBS_MODULATION_DEFAULT)
        {
            // User specified modulation
            cmd << ",modulation=" << modulation;
        }
        else if (laneRate >= PRBS_HDR && laneRate <= PRBS_XDR)
        {
            // Default behavior for high-speed rates
            cmd << ",modulation=" << PRBS_MODULATION_PAM4_ENCODING;
        }
        else
        {
            // Default behavior for low-speed rates
            cmd << ",modulation=" << PRBS_MODULATION_NRZ;
        }


        cmd << ",e=" << enable << "," << rateToUpdate << "=" << laneRate << ",prbs_mode_admin=" << prbsMode;
        return cmd.str();
    };

    if (perLaneConfig)
    {
        for (const auto& lane : _userInput._prbsLanesToSet)
        {
            const string prbsRegArgs = buildPrbsRegArgs();
            sendPrmReg(prbsReg, SET, "le=%d,lane=%d%s", perLaneConfig, lane.first, prbsRegArgs.c_str());
        }
    }
    else
    {
        const string prbsRegArgs = buildPrbsRegArgs();
        sendPrmReg(prbsReg, SET, prbsRegArgs.c_str());
    }
}

void MlxlinkCommander::sendPprtPptt()
{
    bool perLaneConfig = (!_userInput._prbsLanesToSet.empty()) && (_userInput._prbsLanesToSet.size() != _numOfLanes);
    u_int32_t rxRate = _mlxlinkMaps->_prbsLaneRate[_userInput._pprtRate].capMask ?
                         _mlxlinkMaps->_prbsLaneRate[_userInput._pprtRate].value :
                         (u_int32_t)PRBS_EDR;
    u_int32_t txRate = _mlxlinkMaps->_prbsLaneRate[_userInput._ppttRate].capMask ?
                         _mlxlinkMaps->_prbsLaneRate[_userInput._ppttRate].value :
                         (u_int32_t)PRBS_EDR;

    u_int32_t rxModulation = !_userInput._pprtModulation.empty() ?
                               _mlxlinkMaps->_prbsModulationValue[_userInput._pprtModulation] :
                               (u_int32_t)PRBS_MODULATION_DEFAULT;
    u_int32_t txModulation = !_userInput._ppttModulation.empty() ?
                               _mlxlinkMaps->_prbsModulationValue[_userInput._ppttModulation] :
                               (u_int32_t)PRBS_MODULATION_DEFAULT;

    prbsConfiguration("PPRT", true, rxRate, prbsModeToMask(_userInput._pprtMode), perLaneConfig, _userInput._prbsRxInv, rxModulation);
    prbsConfiguration("PPTT", true, txRate, prbsModeToMask(_userInput._ppttMode), perLaneConfig, _userInput._prbsTxInv, txModulation);
}

void MlxlinkCommander::resetPprtPptt()
{
    try
    {
        if (_prbsTestMode)
        {
            prbsConfiguration("PPRT", false, PRBS_EDR, PRBS31, false, false, PRBS_MODULATION_DEFAULT);
            prbsConfiguration("PPTT", false, PRBS_EDR, PRBS31, false, false, PRBS_MODULATION_DEFAULT);
        }
    }
    catch (MlxRegException& exc)
    {
        // Not necessary to handle if clearing PPRT and PPTT failed
        // They already cleared before enabling the test mode
    }
}

void MlxlinkCommander::validateSpeedStr()
{
    // Normalize IB speeds (Ignore IB- from infiniband speeds)
    for (vector<string>::iterator it = _userInput._ptysSpeeds.begin(); it != _userInput._ptysSpeeds.end(); it++)
    {
        size_t found = (*it).find("IB-");
        if (found != std::string::npos)
        {
            *it = (*it).erase(found, found + 3);
        }
    }
    // get list of all valid speeds (ETH, ETH extended, and IB)
    string validSpeedStr = "";
    // include NRZ speeds only for devices not supporting extended speeds
    if (!(_protoCapabilityEx && _protoActive == ETH))
    {
        validSpeedStr = SupportedSpeeds2Str(ETH, BIT_MASK_ALL_DWORD, false);
    }
    validSpeedStr += "," + SupportedSpeeds2Str(ETH, BIT_MASK_ALL_DWORD, true);
    validSpeedStr += "," + SupportedSpeeds2Str(IB, BIT_MASK_ALL_DWORD, false);
    string speedToCheck = "";
    size_t fromIndex = 0;
    size_t toIndex = 0;
    for (vector<string>::iterator it = _userInput._ptysSpeeds.begin(); it != _userInput._ptysSpeeds.end(); it++)
    {
        fromIndex = validSpeedStr.find(*it);
        toIndex = validSpeedStr.find_first_of(',', fromIndex);
        if (fromIndex != string::npos)
        {
            speedToCheck = validSpeedStr.substr(fromIndex, toIndex - fromIndex);
        }
        if (toUpperCase(speedToCheck) != *it)
        {
            throw MlxRegException("%s is invalid speed configuration", (*it).c_str());
        }
    }

    if (isIn(string("56G"), _userInput._ptysSpeeds) && _userInput._linkModeForce == true)
    {
        throw MlxRegException("No support of 56G FORCE mode");
    }
}

void MlxlinkCommander::sendPtys()
{
    try
    {
        if (_prbsTestMode)
        {
            throw MlxRegException("Cannot Configure Port Speeds in Physical Test Mode. Please Disable First");
        }

        MlxlinkRecord::printCmdLine("Configuring Port Speeds", _jsonRoot);

        validateSpeedStr();

        u_int32_t ptysMask = 0x0;
        string ptysExtraCmd = "";
        string protoAdminField = "";
        for (u_int32_t i = 0; i < _userInput._ptysSpeeds.size(); i++)
        {
            ptysMask |= ptysSpeedToMask(_userInput._ptysSpeeds[i]);
        }
        if (_userInput._linkModeForce == true)
        {
            gearboxBlock(PTYS_LINK_MODE_FORCE_FLAG);

            ptysExtraCmd += ",an_disable_admin=1";
        }
        if (_protoActive == IB)
        {
            if (_userInput._linkModeForce == false)
            {
                ptysMask |= 0x1;
            }
            ptysExtraCmd += ",ib_link_width_admin=7";
            protoAdminField = "ib_proto_admin";
        }
        else
        {
            if (_productTechnology >= PRODUCT_16NM)
            {
                protoAdminField = "ext_eth_proto_admin";
            }
            else
            {
                protoAdminField = "eth_proto_admin";
            }
        }

        sendPrmReg(ACCESS_REG_PTYS, SET, "proto_mask=%d,%s=%d%s", _protoActive, protoAdminField.c_str(), ptysMask,
                   ptysExtraCmd.c_str());
    }
    catch (const std::exception& exc)
    {
        string errMsg = string(exc.what());
        if (errMsg.find(OPERATIONAL_ERROR_STR) != string::npos)
        {
            errMsg = "Invalid speed configurations";
        }
        _allUnhandledErrors += string("Sending PTYS (Configuring port speeds) "
                                      "raised the following exception: ") +
                               errMsg + string("\n");
    }
}

u_int32_t MlxlinkCommander::ptysSpeedToMask(const string& speed)
{
    bool extended = _productTechnology >= PRODUCT_16NM;
    u_int32_t speedMask = 0;

    checkSupportedSpeed(speed, _protoCapability, extended);

    if (_protoActive == IB)
    {
        speedMask = ptysSpeedToMaskIB(speed);
    }
    else if (extended)
    {
        speedMask = ptysSpeedToExtMaskETH(speed);
    }
    else
    {
        speedMask = ptysSpeedToMaskETH(speed);
    }

    return speedMask;
}

void MlxlinkCommander::checkSupportedSpeed(const string& speed, u_int32_t protoCap, bool extSpeed)
{
    u_int32_t mask = 0;
    u_int32_t diffProto = 0;
    string errStr = "";
    string supportedSpeedStr = "";
    if (!extSpeed)
    {
        mask = (_protoActive == IB) ? ptysSpeedToMaskIB(speed) : ptysSpeedToMaskETH(speed);
        diffProto = (_protoActive == IB) ? ptysSpeedToMaskETH(speed) : ptysSpeedToMaskIB(speed);
    }
    else
    {
        mask = (_protoActive == IB) ? ptysSpeedToMaskIB(speed) : ptysSpeedToExtMaskETH(speed);
        diffProto = (_protoActive == IB) ? ptysSpeedToExtMaskETH(speed) : ptysSpeedToMaskIB(speed);
    }
    supportedSpeedStr = SupportedSpeeds2Str(_protoActive, protoCap, extSpeed);
    if (!supportedSpeedStr.empty())
    {
        errStr = "Supported Speeds Are: " + supportedSpeedStr;
    }
    if (diffProto)
    {
        throw MlxRegException(speed + " is not supported by Protocol!\n" + errStr);
    }
    if (!(mask & protoCap) && _linkUP)
    {
        throw MlxRegException(speed + " is not supported by Device!\n" + errStr);
    }
}

void MlxlinkCommander::sendPplm()
{
    try
    {
        if (_prbsTestMode)
        {
            throw MlxRegException("Cannot Configure FEC in Physical Test Mode. Please Disable First.");
        }
        MlxlinkRecord::printCmdLine("Configuring Port FEC", _jsonRoot);
        if (_protoActive == IB && _ignoreIbFECCheck)
        {
            throw MlxRegException("FEC Configuration is Valid for ETHERNET only!");
        }
        if (!_linkUP && _userInput._speedFec == "")
        {
            throw MlxRegException("When Port is Not Active, You Must Specify the Speed to Configure FEC (--fec_speed "
                                  "<speed>)");
        }

        checkPplmCap(); // after calling checkPplmCap, _userInput._speedFec will be changed to the correct fec speed

        string fecSpeedStr = speedToFecSpeedStr(_speedStrG, _numOfLanes);
        string speedToConfigure = (_linkUP && _userInput._speedFec == "") ? fecSpeedStr : _userInput._speedFec;
        u_int32_t fecAdmin = fecToBit(_userInput._pplmFec, speedToConfigure);
        string pplmFecCmd = "";
        if (speedToConfigure == "50g" || speedToConfigure == "25g")
        { // 25g and 50g must be set the same
            pplmFecCmd += "fec_override_admin_25g=" + to_string(fecAdmin);
            pplmFecCmd += ",fec_override_admin_50g=" + to_string(fecAdmin);
        }
        else
        {
            pplmFecCmd = string(_protoActive == IB ? "ib_" : "") + "fec_override_admin_" + speedToConfigure;
            pplmFecCmd += "=" + to_string(fecAdmin);
        }

        sendPrmReg(ACCESS_REG_PPLM, SET, pplmFecCmd.c_str());
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Sending PPLM (Configuring port FEC) raised the following exception: ") +
                               string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::speedToFecSpeedStr(const string& speed, u_int32_t numOfLanes)
{
    string fecSpeedStrFormat = "";
    string numberOfLanesStr = to_string(numOfLanes) + "x";
    if (_protoActive == IB)
    {
        string speedStr = speed;
        if (speedStr.find("IB-") != string::npos)
        {
            speedStr = speedStr.substr(3);
        }
        fecSpeedStrFormat = toLowerCase(speedStr);
    }
    else
    {
        if (speed == "1600G")
        {
            fecSpeedStrFormat = "1600g_" + numberOfLanesStr;
        }
        if (speed == "800G")
        {
            fecSpeedStrFormat = "800g_" + numberOfLanesStr;
        }
        if (speed == "400G")
        {
            fecSpeedStrFormat = "400g_" + numberOfLanesStr;
        }
        if (speed == "200G")
        {
            fecSpeedStrFormat = "200g_" + numberOfLanesStr;
        }
        if (speed == "100G")
        {
            if (numOfLanes == 4)
            {
                fecSpeedStrFormat = "100g";
            }
            else
            {
                fecSpeedStrFormat = "100g_" + numberOfLanesStr;
            }
        }
        if (speed == "50G")
        {
            if (numOfLanes == 1)
            {
                fecSpeedStrFormat = "50g_" + numberOfLanesStr;
            }
            else
            {
                fecSpeedStrFormat = "50g";
            }
        }
        if (speed == "100GbE")
        {
            fecSpeedStrFormat = "100g";
        }
        if (speed == "50GbE")
        {
            fecSpeedStrFormat = "50g";
        }
        if (speed == "25GbE" || speed == "25G")
        {
            fecSpeedStrFormat = "25g";
        }
        if (speed == "40GbE" || speed == "40G" || speed == "10GbE" || speed == "10G")
        {
            fecSpeedStrFormat = "10g_40g";
        }
        if (speed == "56GbE")
        {
            fecSpeedStrFormat = "56g";
        }
    }
    return fecSpeedStrFormat;
}

u_int32_t MlxlinkCommander::fecToBit(const string& fec, const string& speedStrG)
{
    string fecToCheck = fec;
    u_int32_t fecAdmin = FEC_MODE_MASK_AU;

    // Work with different RS and LL FEC for HDR, NDR and ETH PAM4 speeds
    if ((speedStrG == "ndr" || speedStrG == "hdr") ||
        (speedStrG.find("x") != string::npos && speedStrG != "100g_4x" && speedStrG != "50g_2x"))
    {
        if (fec == _mlxlinkMaps->_fecModeMask[FEC_MODE_MASK_RS_528].second)
        {
            fecToCheck += "-544";
        }
        else if (fec == _mlxlinkMaps->_fecModeMask[FEC_MODE_MASK_LL_271].second && speedStrG != "hdr")
        {
            fecToCheck += "-272";
        }
    }
    for (auto it = _mlxlinkMaps->_fecModeMask.begin(); it != _mlxlinkMaps->_fecModeMask.end(); it++)
    {
        if (it->second.second == fecToCheck)
        {
            fecAdmin = it->first;
        }
    }
    return fecAdmin;
}

u_int32_t MlxlinkCommander::getFecCapForCheck(const string& speedStr)
{
    u_int32_t fecCapMask = 0;

    sendPrmReg(ACCESS_REG_PPLM, GET);

    try
    {
        fecCapMask = getFieldValue(string(_protoActive == IB ? "ib_" : "") + "fec_override_cap_" + speedStr);
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("\nFEC configuration is not available for this speed: " + speedStr);
    }

    return fecCapMask;
}

void MlxlinkCommander::checkPplmCap()
{
    string speedFec = _userInput._speedFec;
    string uiSpeed = _userInput._speedFec;
    if (_linkUP && _userInput._speedFec.empty())
    {
        speedFec = speedToFecSpeedStr(_speedStrG, _numOfLanes);
        uiSpeed = _speedStrG;
    }
    // Validate the speed
    if (!_userInput._speedFec.empty())
    {
        vector<string> supportedSpeeds =
          MlxlinkRecord::split(SupportedSpeeds2Str(_protoActive, _deviceCapability, _protoCapabilityEx), ",");
        string speedToCheck = _userInput._speedFec;
        speedToCheck = toUpperCase(speedToCheck);
        if (_protoCapabilityEx)
        {
            if (speedToCheck == "50G")
            {
                speedToCheck += "_2X";
            }
            else if (speedToCheck == "100G")
            {
                speedToCheck += "_4X";
            }
        }
        if (!isIn(speedToCheck, supportedSpeeds))
        {
            string validSpeeds = "";
            if (!supportedSpeeds.empty())
            {
                validSpeeds = ", valid FEC speed configurations are [";
                for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++)
                {
                    if (isIn(it->first, supportedSpeeds))
                    {
                        validSpeeds += it->first + ",";
                    }
                }
                validSpeeds = !validSpeeds.empty() ? deleteLastChar(validSpeeds) : validSpeeds;
                validSpeeds = validSpeeds + "]";
            }
            throw MlxRegException("\nFEC speed %s is not valid%s", uiSpeed.c_str(), validSpeeds.c_str());
        }
    }
    // Validate the FEC for the speed
    if (speedFec == "10g" || speedFec == "40g")
    {
        speedFec = "10g_40g";
    }
    if (speedFec == "50g_2x")
    {
        speedFec = "50g";
    }
    if (speedFec == "100g_4x")
    {
        speedFec = "100g";
    }
    _userInput._speedFec = speedFec;
    u_int32_t fecCap = getFecCapForCheck(_userInput._speedFec);
    if (_userInput._pplmFec != "AU" && !(fecToBit(_userInput._pplmFec, _userInput._speedFec) & fecCap))
    {
        string supportedFec = fecMaskToUserInputStr(fecCap);
        string validFecs = fecMaskToUserInputStr(BIT_MASK_ALL_DWORD);
        string errorMsg = _userInput._pplmFec + " FEC is not supported in " + uiSpeed + " speed, ";
        if (validFecs.find(_userInput._pplmFec) == string::npos || _userInput._pplmFec.size() <= 1)
        {
            errorMsg = _userInput._pplmFec + " FEC configuration is not valid, ";
        }
        if (supportedFec.empty())
        {
            errorMsg += "it's not available for this speed";
        }
        else
        {
            errorMsg += "valid FEC configurations are [" + supportedFec + "]";
        }
        throw MlxRegException("\n" + errorMsg);
    }
}

void MlxlinkCommander::getSltpAlevOut(u_int32_t lane)
{
    if (_userInput._pcie && _userInput._pciSltpPort != -1)
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d,local_port=%d", lane, _userInput._pciSltpPort);
    }
    else
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d", lane);
    }

    _userInput._sltpParams[SLTP_HDR_OB_ALEV_OUT] = getFieldValue("ob_alev_out");
}

void MlxlinkCommander::getSltpRegAndLeva(u_int32_t lane)
{
    if (_userInput._pcie && _userInput._pciSltpPort != -1)
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d,local_port=%d", lane, _userInput._pciSltpPort);
    }
    else
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d", lane);
    }

    _userInput._sltpParams[SLTP_EDR_OB_REG] = getFieldValue("ob_reg");
    _userInput._sltpParams[SLTP_EDR_OB_LEVA] = getFieldValue("ob_leva");
}

u_int32_t MlxlinkCommander::getLaneSpeed(u_int32_t lane)
{
    if (_userInput._pcie && _userInput._pciSltpPort != -1)
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d,local_port=%d", lane, _userInput._pciSltpPort);
    }
    else
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "lane=%d", lane);
    }

    return getFieldValue("lane_speed");
}

void MlxlinkCommander::validateNumOfParamsForNDRGen()
{
    u_int32_t params;
    string errMsg = "Invalid set of Transmitter Parameters, ";
    errMsg += "valid parameters for the active speed are: ";
    if ((!_linkSpeed && _devID == DeviceSpectrum4) ||
        isSpeed100GPerLane(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
    {
        params = SLTP_NDR_LAST;
        errMsg += "fir_pre3,fir_pre2,fir_pre1,fir_main,fir_post1,drv_amp";
    }
    else if (isSpeed50GPerLane(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
    {
        params = SLTP_NDR_DRV_AMP;
        errMsg += "fir_pre2,fir_pre1,fir_main,fir_post1,drv_amp";
    }
    else
    {
        params = SLTP_NDR_FIR_POST1;
        errMsg += "fir_pre1,fir_main,fir_post1,drv_amp";
    }
    if (_userInput._sltpParams.size() != params)
    {
        throw MlxRegException(errMsg);
    }
    for (map<u_int32_t, u_int32_t>::iterator it = _userInput._sltpParams.begin(); it != _userInput._sltpParams.end();
         it++)
    {
        if (((int)it->second) > MAX_SBYTE || ((int)it->second) < MIN_SBYTE)
        {
            throw MlxRegException("Invalid Transmitter Parameters values");
        }
    }
}

void MlxlinkCommander::validateNumOfParamsForXDRGen()
{
    u_int32_t params;
    string errMsg = "Invalid set of Transmitter Parameters, ";
    errMsg += "valid parameters for the active speed are: ";
    if (isSpeed200GPerLane(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
    {
        params = SLTP_XDR_LAST; // 9 taps are valid for 200G speed + drv_amp
        errMsg +=
        "fir_pre4 ,fir_pre3 ,fir_pre2 ,fir_pre1 ,fir_main ,fir_post1 ,fir_post2 ,fir_post3 ,fir_post4 ,fir_post5 ,fir_post6 ,fir_post7 ,drv_amp";
    }
    else if (isSpeed100GPerLane(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
    {
        params = SLTP_NDR_LAST; // 5 taps are valid for 100G speed + drv_amp
        errMsg += "fir_pre3,fir_pre2,fir_pre1,fir_main,fir_post1,drv_amp";
    }
    else if (isSpeed50GPerLane(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive))
    {
        params = SLTP_NDR_DRV_AMP; // 4 taps are valid for 50G speed + drv_amp
        errMsg += "fir_pre2,fir_pre1,fir_main,fir_post1,drv_amp";
    }
    else
    {
        params = SLTP_NDR_FIR_POST1; // 3 taps are valid for 25G speed + drv_amp
        errMsg += "fir_pre1,fir_main,fir_post1,drv_amp";
    }
    if (_userInput._sltpParams.size() != params)
    {
        throw MlxRegException(errMsg);
    }
    for (map<u_int32_t, u_int32_t>::iterator it = _userInput._sltpParams.begin(); it != _userInput._sltpParams.end();
         it++)
    {
        if (((int)it->second) > MAX_SBYTE || ((int)it->second) < MIN_SBYTE)
        {
            throw MlxRegException("Invalid Transmitter Parameters values");
        }
    }
}

void MlxlinkCommander::checkSltpParamsSize()
{
    u_int32_t sltpParamsSize = SLTP_EDR_OB_REG;
    if (_productTechnology == PRODUCT_16NM)
    {
        sltpParamsSize = SLTP_HDR_OB_ALEV_OUT;
        for (map<u_int32_t, u_int32_t>::iterator it = _userInput._sltpParams.begin();
             it != _userInput._sltpParams.end();
             it++)
        {
            if (((int)it->second) > MAX_SBYTE || ((int)it->second) < MIN_SBYTE)
            {
                throw MlxRegException("Invalid Transmitter Parameters values");
            }
        }
    }
    else if (_productTechnology == PRODUCT_7NM)
    {
        validateNumOfParamsForNDRGen();
    }
    else if (_productTechnology >= PRODUCT_5NM)
    {
        validateNumOfParamsForXDRGen();
    }
    else if (_userInput._advancedMode)
    {
        sltpParamsSize = SLTP_EDR_LAST;
    }
    if (_userInput._sltpParams.size() != sltpParamsSize && _productTechnology != PRODUCT_7NM &&
        _productTechnology != PRODUCT_5NM)
    {
        throw MlxRegException("Invalid set of Transmitter Parameters");
    }
}

string MlxlinkCommander::updateSltpEdrHdrFields()
{
    map<u_int32_t, PRM_FIELD> sltpParam = _mlxlinkMaps->_SltpEdrParams;
    string sltpParamCmd = "";
    char hdrEdrParamBuff[32] = "";
    if (_productTechnology == PRODUCT_16NM)
    {
        sltpParam = _mlxlinkMaps->_SltpHdrParams;
    }

    for (auto const& param : sltpParam)
    {
        if (param.second.fieldAccess & (FIELD_ACCESS_W | FIELD_ACCESS_ADVANCED))
        {
            snprintf(hdrEdrParamBuff, 32, "%s=%d,", param.second.prmField.c_str(), _userInput._sltpParams[param.first]);
            sltpParamCmd += string(hdrEdrParamBuff);
        }
    }

    return deleteLastChar(sltpParamCmd);
}

string MlxlinkCommander::updateSltpNdrFields()
{
    string sltpParamsCmd = "";
    u_int32_t activeSpeed = _protoActive == IB ? _activeSpeed : _activeSpeedEx;
    u_int32_t paramShift = 2; // Assuming that the active speed is NRZ, so user params will represent NRZ params
    char paramValueBuff[32] = "";

    if (isSpeed100GPerLane(activeSpeed, _protoActive))
    {
        paramShift = 0;
    }
    else if (isSpeed50GPerLane(activeSpeed, _protoActive))
    {
        paramShift = 1;
    }

    for (auto const& param : _mlxlinkMaps->_SltpNdrParams)
    {
        if ((param.second.validationMask & activeSpeed) || _userInput._pcie)
        {
            snprintf(paramValueBuff, sizeof(paramValueBuff), "%s=%d", param.second.prmField.c_str(),
                     _userInput._sltpParams[param.first - paramShift]);
            sltpParamsCmd += string(paramValueBuff);
            sltpParamsCmd += ",";
        }
    }

    return deleteLastChar(sltpParamsCmd);
}

string MlxlinkCommander::updateSltpXdrFields()
{
    string sltpParamsCmd = "";
    u_int32_t activeSpeed = _protoActive == IB ? _activeSpeed : _activeSpeedEx;
    u_int32_t paramShift = 3; // Assuming that the active speed is NRZ, so user params will represent NRZ params
    char paramValueBuff[32] = "";

    if (isSpeed200GPerLane(activeSpeed, _protoActive))
    {
        paramShift = 0;
    }
    if (isSpeed100GPerLane(activeSpeed, _protoActive))
    {
        paramShift = 1;
    }
    else if (isSpeed50GPerLane(activeSpeed, _protoActive))
    {
        paramShift = 2;
    }

    for (auto const& param : _mlxlinkMaps->_SltpXdrParams)
    {
        if ((param.second.validationMask & activeSpeed) || _userInput._pcie)
        {
            snprintf(paramValueBuff, sizeof(paramValueBuff), "%s=%d", param.second.prmField.c_str(),
                     _userInput._sltpParams[param.first - paramShift]);
            sltpParamsCmd += string(paramValueBuff);
            sltpParamsCmd += ",";
        }
    }

    return deleteLastChar(sltpParamsCmd);
}

string MlxlinkCommander::getSltpStatus()
{
    if (_userInput._pcie && _userInput._pciSltpPort != -1)
    {
        sendPrmReg(ACCESS_REG_SLTP, GET, "local_port=%d", _userInput._pciSltpPort);
    }
    else
    {
        sendPrmReg(ACCESS_REG_SLTP, GET);
    }

    string statusStr = "Invalid parameters";
    u_int32_t status = getFieldValue("ob_bad_stat");
    if (status)
    {
        switch (_productTechnology)
        {
            case PRODUCT_40NM:
            case PRODUCT_28NM:
                statusStr = _mlxlinkMaps->_SLTPBadSetStatus2Str[status];
                break;
            case PRODUCT_16NM:
                statusStr = _mlxlinkMaps->_SLTP16BadSetStatus2Str[status];
                break;
            case PRODUCT_7NM:
            case PRODUCT_5NM:
                statusStr = _mlxlinkMaps->_SLTP7BadSetStatus2Str[status];
                break;
        }
    }
    return statusStr;
}

void MlxlinkCommander::sendSltp()
{
    if (_isSwControled)
    {
        _allUnhandledErrors += string("No plugged cable detected\n");
        return;
    }

    string sltpParamsCmd = "";
    MlxlinkRecord::printCmdLine("Configuring Port Transmitter Parameters", _jsonRoot);

    checkSltpParamsSize();

    if (_userInput._sltpLane && _userInput._lane >= _numOfLanes)
    {
        throw MlxRegException("Could Not find Lane " + to_string(_userInput._lane));
    }
    if (_userInput._txPolicy && _productTechnology < PRODUCT_7NM)
    {
        throw MlxRegException("--" SLTP_TX_POLICY_FLAG " flag is not valid for this device");
    }

    try
    {
        if ((_devID == DeviceSpectrum2 || _devID == DeviceQuantum || _devID == DeviceQuantum2 ||
             _devID == DeviceQuantum3 || dm_is_gpu(static_cast<dm_dev_id_t>(_devID))) &&
            _userInput._db)
        {
            u_int32_t portGroup = getPortGroup(_localPort);
            MlxlinkRecord::printWar("Port " + to_string(_userInput._labelPort) + " is mapped to group " +
                                      to_string(portGroup) +
                                      ".\nPlease "
                                      "notice that the new settings will be implemented in all ports "
                                      "mapped to group " +
                                      to_string(portGroup),
                                    _jsonRoot);
        }
        u_int32_t laneSpeed = 0;
        for (u_int32_t lane = 0; lane < _numOfLanes; lane++)
        {
            if (_userInput._sltpLane && _userInput._lane != lane)
            {
                continue;
            }
            if (_userInput._db && lane != 0)
            {
                break;
            }

            msleep(SLTP_LANE_SPEED_SLEEP);
            laneSpeed = getLaneSpeed(lane);

            switch (_productTechnology)
            {
                case PRODUCT_5NM:
                    sltpParamsCmd = updateSltpXdrFields();
                    break;
                case PRODUCT_7NM:
                    sltpParamsCmd = updateSltpNdrFields();
                    break;
                case PRODUCT_16NM:
                    getSltpAlevOut(lane);
                    sltpParamsCmd = updateSltpEdrHdrFields();
                    break;
                default:
                {
                    if (!_userInput._advancedMode)
                    {
                        getSltpRegAndLeva(lane);
                    }
                    sltpParamsCmd = updateSltpEdrHdrFields();
                }
                break;
            }
            if (sltpParamsCmd == "")
            {
                throw MlxRegException("Current Speed does not match the provided parameters");
            }
            sendPrmReg(ACCESS_REG_SLTP, SET, "lane=%d,lane_speed=%d,tx_policy=%d,c_db=%d,%s", lane, laneSpeed,
                       _userInput._txPolicy, _userInput._db || _userInput._txPolicy, sltpParamsCmd.c_str());
        }
    }
    catch (MlxRegException& exc)
    {
        string errorMsg = "";
        if (sltpParamsCmd == "")
        {
            errorMsg = exc.what();
        }
        else
        {
            errorMsg = getSltpStatus();
        }
        _allUnhandledErrors += string("Configuring Port Transmitter Parameters raised the following exception:\n"
                                      "Failed to send parameter set: ") +
                               errorMsg + "\n";
    }
}

string MlxlinkCommander::getLoopbackStr(u_int32_t loopbackCapMask)
{
    string loopbackStr = _mlxlinkMaps->_loopbackModeList[LOOPBACK_MODE_NO].first + "(" +
                         _mlxlinkMaps->_loopbackModeList[LOOPBACK_MODE_NO].second + ")/";
    for (const auto& lbConf : _mlxlinkMaps->_loopbackModeList)
    {
        if ((lbConf.first & loopbackCapMask) && !lbConf.second.second.empty())
        {
            loopbackStr += lbConf.second.first + "(" + lbConf.second.second + ")/";
        }
    }
    return deleteLastChar(loopbackStr);
}

void MlxlinkCommander::checkPplrCap()
{
    sendPrmReg(ACCESS_REG_PPLR, GET);

    u_int32_t loopBackCap = getFieldValue("lb_cap");
    u_int32_t loopBackVal = getLoopbackMode(_userInput._pplrLB);
    if (loopBackVal != LOOPBACK_MODE_NO)
    {
        if (!(loopBackCap & getLoopbackMode(_userInput._pplrLB)))
        {
            string supportedLoopbacks = getLoopbackStr(loopBackCap);
            throw MlxRegException(
              "\n%s Loopback configuration is not supported, supported Loopback configurations are [%s]",
              _userInput._pplrLB.c_str(), supportedLoopbacks.c_str());
        }
    }
    if (loopBackVal == LOOPBACK_MODE_REMOTE && _productTechnology < PRODUCT_7NM)
    {
        string warMsg = "Remote loopback mode pre-request (all should be satisfied):\n";
        warMsg += "1. Remote loopback is supported only in force mode.\n";
        warMsg += "   please use the --link_mode_force flag if force mode not configured\n";
        warMsg += "2. Remote loopback is supported for 25G per lane only.\n";
        warMsg += "3. If the NIC has 2 ports, please make sure that both ports are in the same speed.";
        MlxlinkRecord::printWar(warMsg, _jsonRoot);
    }
}

void MlxlinkCommander::sendPplr()
{
    try
    {
        MlxlinkRecord::printCmdLine("Configuring Port Loopback", _jsonRoot);

        checkPplrCap();

        sendPrmReg(ACCESS_REG_PPLR, SET, "lb_en=%d", getLoopbackMode(_userInput._pplrLB));
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors += string("Sending PPLR (Configuring port loopback) raised the following exception: ") +
                               string(exc.what()) + string("\n");
    }
}

u_int32_t MlxlinkCommander::getLoopbackMode(const string& lb)
{
    auto it = find_if(_mlxlinkMaps->_loopbackModeList.begin(), _mlxlinkMaps->_loopbackModeList.end(),
                      [lb](pair<u_int32_t, pair<string, string>> lpConf) { return lb == lpConf.second.first; });

    if (it == _mlxlinkMaps->_loopbackModeList.end())
    {
        throw MlxRegException("Invalid loopback option: %s, see tool usage \"%s --help\"", lb.c_str(), MLXLINK_EXEC);
    }

    return it->first;
}

void MlxlinkCommander::sendPepc()
{
    if (_isSwControled)
    {
        _allUnhandledErrors += string("No plugged cable detected\n");
        return;
    }

    try
    {
        gearboxBlock(PEPC_SET_FLAG);

        if (_isHCA || _devID == DeviceSwitchIB || _devID == DeviceSwitchIB2 || _devID == DeviceQuantum ||
            _devID == DeviceQuantum2 || _devID == DeviceQuantum3 || dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            throw MlxRegException("\"--" PEPC_SET_FLAG "\" option is not supported for HCA and InfiniBand switches");
        }
        MlxlinkRecord::printCmdLine("Configuring External PHY", _jsonRoot);
        string regName = "PEPC";

        // Get old values of PEPC fields
        sendPrmReg(ACCESS_REG_PEPC, GET);

        u_int32_t forceMode_int = getFieldValue("twisted_pair_force_mode");
        u_int32_t anMode_int = getFieldValue("twisted_pair_an_mode");

        // Set new values of PEPC fields
        u_int32_t forceMode = forceMode_int;
        if (_userInput._sendPepcForceMode)
        {
            forceMode = pepc_force_mode_to_int(_userInput._forceMode);
        }

        sendPrmReg(ACCESS_REG_PEPC, SET, "twisted_pair_an_mode=%d,twisted_pair_force_mode=%d", anMode_int, forceMode);
    }
    catch (const std::exception& exc)
    {
        _allUnhandledErrors +=
          string("Sending PEPC (Configuring External PHY parameters) raised the following exception: ") +
          string(exc.what()) + string("\n");
    }
}

u_int32_t MlxlinkCommander::getPortGroup(u_int32_t localPort)
{
    sendPrmReg(ACCESS_REG_PGMR, GET, "local_port=%d,pg_sel=%d", (localPort - 1), TX_LOCAL_PORT);

    return getFieldValue("group_of_port");
}

void MlxlinkCommander::setTxGroupMapping()
{
    try
    {
        if (_devID != DeviceSpectrum2 && _devID != DeviceQuantum && _devID != DeviceQuantum2 &&
            _devID != DeviceQuantum3 && !dm_is_gpu(static_cast<dm_dev_id_t>(_devID)))
        {
            throw MlxRegException("Port group mapping supported for Spectrum-2 and Quantum switches only!");
        }

        MlxlinkRecord::printCmdLine("Configuring Ports-Group Mapping", _jsonRoot);
        handleLabelPorts(_userInput._labelPorts);

        u_int32_t blockSelector, bitMask;
        u_int32_t blocksToSet[4] = {0, 0, 0, 0};
        u_int32_t localPort = 0;
        for (vector<PortGroup>::iterator it = _localPortsPerGroup.begin(); it != _localPortsPerGroup.end(); it++)
        {
            localPort = it->localPort;
            blockSelector = (localPort - 1) / MAX_DWORD_BLOCK_SIZE;
            bitMask = (u_int32_t)pow(2.0, (int)((localPort - 1) - (blockSelector * MAX_DWORD_BLOCK_SIZE)));
            blocksToSet[blockSelector] |= (bitMask);
        }
        sendPrmReg(ACCESS_REG_PGMR, SET,
                   "local_port=%d,pg_sel=%d,group=%d,"
                   "ports_mapping_of_group[0]=%d,ports_mapping_of_group[1]=%d,"
                   "ports_mapping_of_group[2]=%d,ports_mapping_of_group[3]=%d",
                   1, TX_GROUP, _userInput._setGroup, blocksToSet[0], blocksToSet[1], blocksToSet[2], blocksToSet[3]);
    }
    catch (const std::exception& exc)
    {
        string errorMsg = string(exc.what());
        if (errorMsg == OPERATIONAL_ERROR_STR)
        {
            errorMsg = "Invalid configuration values";
        }
        _allUnhandledErrors +=
          string("Configuring ports group mapping raised the following exception: ") + errorMsg + string("\n");
    }
}

///////////////////////////////////////////////

// Cable operation
// Cable helper functions

bool MlxlinkCommander::isPassiveQSFP()
{
    switch (_cableIdentifier)
    {
        case IDENTIFIER_QSFP28:
        case IDENTIFIER_QSFP_PLUS:
            return (_cableMediaType == PASSIVE);
    }
    return false;
}

bool MlxlinkCommander::isSFP51Paging()
{
    // TODO check page 0 byte 64 bit 4, if set, then SFP51, else SFP.
    bool sfpQsaCable = (_cableIdentifier == IDENTIFIER_SFP || _cableIdentifier == IDENTIFIER_QSA);
    bool readSfp51 = false;
    if (_ddmSupported && sfpQsaCable && _temperature != 0)
    {
        readSfp51 = true;
    }
    return readSfp51;
}

void MlxlinkCommander::printOuptputVector(vector<MlxlinkCmdPrint>& cmdOut)
{
    for (vector<MlxlinkCmdPrint>::iterator ptr = cmdOut.begin(); ptr < cmdOut.end(); ptr++)
    {
        cout << *ptr;
    }
}

void MlxlinkCommander::initCablesCommander()
{
    gearboxBlock(CABLE_FLAG);

    if (isBackplane())
    {
        throw MlxRegException("Command not supported for backplane ports!");
    }

    if (_plugged && !_mngCableUnplugged)
    {
        _cablesCommander = new MlxlinkCablesCommander(_jsonRoot);
        _cablesCommander->_mf = _mf;
        _cablesCommander->_regLib = _regLib;
        _cablesCommander->_gvmiAddress = _gvmiAddress;
        _cablesCommander->_moduleNumber = _moduleNumber;
        _cablesCommander->_slotIndex = _slotIndex;
        _cablesCommander->_localPort = _localPort;
        _cablesCommander->_numOfLanes = _numOfLanes;
        _cablesCommander->_moduleLanesMapping = _moduleLanesMapping;
        _cablesCommander->_cableIdentifier = _cableIdentifier;
        _cablesCommander->_mlxlinkMaps = _mlxlinkMaps;
        _cablesCommander->_sfp51Paging = isSFP51Paging();
        _cablesCommander->_passiveQsfp = isPassiveQSFP();
    }
    else
    {
        throw MlxRegException("No plugged cable detected");
    }
}

void MlxlinkCommander::showCableDump()
{
    try
    {
        initCablesCommander();
        vector<MlxlinkCmdPrint> dumpOutput = _cablesCommander->getPagesToDump();
        printOuptputVector(dumpOutput);
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Dumping EEPROM pages raised the following exception: " + exc.what_s() + "\n";
    }
}

void MlxlinkCommander::showCableDDM()
{
    try
    {
        initCablesCommander();
        if (_isSwControled)
        {
            _cablesCommander->setSwControlMode();
        }
        if (_ddmSupported)
        {
            vector<MlxlinkCmdPrint> ddmOutput = _cablesCommander->getCableDDM();
            printOuptputVector(ddmOutput);
        }
        else
        {
            throw MlxRegException("Cable does not support DDM");
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Showing DDM info raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

vector<u_int8_t> MlxlinkCommander::validateBytes(const vector<string>& strBytes)
{
    vector<u_int8_t> intData;
    u_int32_t byteVal = 0;
    for (u_int32_t i = 0; i < strBytes.size(); i++)
    {
        strToUint32((char*)strBytes[i].c_str(), byteVal);
        if (byteVal > 255)
        {
            throw MlxRegException("Invalid byte value %d. It must be within range [0-255].", byteVal);
        }
        intData.push_back(byteVal);
    }
    return intData;
}

void MlxlinkCommander::writeCableEEPROM()
{
    try
    {
        initCablesCommander();
        MlxlinkRecord::printCmdLine("Writing To Cable EEPROM", _jsonRoot);
        if (_plugged && !_mngCableUnplugged)
        {
            vector<u_int8_t> bytesToWrite = validateBytes(_userInput._bytesToWrite);
            _cablesCommander->writeToEEPROM(_userInput._page, _userInput._offset, bytesToWrite);
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Writing cable EEPROM raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::readCableEEPROM()
{
    try
    {
        initCablesCommander();
        MlxlinkCmdPrint bytesOutput =
          _cablesCommander->readFromEEPRM(_userInput._page, _userInput._offset, _userInput._len);
        cout << bytesOutput;
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Reading cable EEPROM raised the following exception: " + exc.what_s() + "\n";
    }
}

void MlxlinkCommander::performControlParams()
{
    try
    {
        initCablesCommander();
        if (_cableMediaType == ACTIVE || _cableMediaType == OPTICAL_MODULE)
        {
            if (_userInput.configParamsToSet.empty())
            {
                _cablesCommander->showControlParams();
            }
            else
            {
                if (_linkUP)
                {
                    throw MlxRegException("Control parameters can be configured when the port is Disabled only\n");
                }
                else
                {
                    _cablesCommander->setControlParams(_userInput.configParamsToSet);
                }
            }
        }
        else
        {
            throw MlxRegException("Control parameters are valid over Active/Optical modules only");
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Reading cable EEPROM raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::performModulePrbsCommands()
{
    try
    {
        initCablesCommander();
        if (_cmisCable)
        {
            if (_cableMediaType == ACTIVE || _cableMediaType == OPTICAL_MODULE)
            {
                if (_userInput.modulePrbsParams[MODULE_PRBS_SELECT] != "HOST" &&
                    _userInput.modulePrbsParams[MODULE_PRBS_SELECT] != "MEDIA")
                {
                    throw MlxRegException("Invalid module side PRBS select, please check the help menu");
                }
                _cablesCommander->_modulePrbsParams = _userInput.modulePrbsParams;
                if (_userInput.isPrbsModeProvided)
                {
                    ModuleAccess_t prbsModuleAccess = MODULE_PRBS_ACCESS_BOTH;
                    if (_userInput.isPrbsChProvided && !_userInput.isPrbsGenProvided)
                    {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_CH;
                    }
                    else if (!_userInput.isPrbsChProvided && _userInput.isPrbsGenProvided)
                    {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_GEN;
                    }
                    else if (_userInput.isPrbsChProvided && _userInput.isPrbsGenProvided)
                    {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_CH_GEN;
                    }
                    _cablesCommander->handlePrbsTestMode(_userInput.modulePrbsParams[MODULE_PRBS_MODE],
                                                         prbsModuleAccess);
                }
                else
                {
                    _cablesCommander->showPrbsTestMode();
                }

                if (_userInput.isPrbsShowDiagProvided)
                {
                    _cablesCommander->showPrpsDiagInfo();
                }

                if (_userInput.isPrbsClearDiagProvided)
                {
                    _cablesCommander->clearPrbsDiagInfo();
                }
            }
            else
            {
                throw MlxRegException("The PRBS test mode supported over Active/Optical modules only");
            }
        }
        else
        {
            throw MlxRegException("The PRBS test mode supported for CMIS modules only");
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += "Module PRBS test mode raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::initEyeOpener()
{
    try
    {
        gearboxBlock(MARGIN_SCAN_FLAG);
        if (_linkUP || _userInput._pcie)
        {
            _eyeOpener = new MlxlinkEyeOpener(_jsonRoot);
            _eyeOpener->_mf = _mf;
            _eyeOpener->_regLib = _regLib;
            _eyeOpener->_gvmiAddress = _gvmiAddress;
            _eyeOpener->_localPort = _localPort;
            _eyeOpener->_pnat = _pnat;
            _eyeOpener->version = _productTechnology;
            _eyeOpener->depth = _dpn.depth;
            _eyeOpener->pcieIndex = _dpn.pcieIndex;
            _eyeOpener->node = _dpn.node;
            _eyeOpener->numOfLanes = _userInput._pcie ? _numOfLanesPcie : _numOfLanes;
            _eyeOpener->lane = _userInput.gradeScanPerLane ? _userInput._lane : -1;
            _eyeOpener->isPam4Speed = _isPam4Speed || ((_linkSpeed == IB_LINK_SPEED_HDR) && (_protoActive == IB));
            _eyeOpener->activeSpeedStr = _speedStrG;

            if (_userInput.measureTime < 0)
            {
                if (_userInput._pcie)
                {
                    _userInput.measureTime = DFLT_MSUR_TIME_PCIE;
                }
                else
                {
                    _userInput.measureTime = DFLT_MSUR_TIME_PORT;
                }
            }
            _eyeOpener->setMeasureTime(_userInput.measureTime);
            _eyeOpener->setEyeSel(_userInput.eyeSelect);
            _eyeOpener->setNonInteractiveMode(_userInput.force);

            _eyeOpener->enableGradeScan();
        }
        else
        {
            throw MlxRegException("port must be active");
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += string("Reading SerDes receive eye grade raised the following"
                                      " exception:\n") +
                               string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::initErrInj()
{
    _errInjector = new MlxlinkErrInjCommander(_jsonRoot);
    _errInjector->_regLib = _regLib;
    _errInjector->_localPort = _localPort;
    _errInjector->_force = _userInput.force;
    _errInjector->_mlxlinkMaps = _mlxlinkMaps;
}

void MlxlinkCommander::handleRxErrInj()
{
    try
    {
        gearboxBlock(PREI_RX_ERR_INJ_FLAG);

        if (!_isHCA)
        {
            throw MlxRegException("This feature supporting NIC's only");
        }
        if (_productTechnology != PRODUCT_28NM)
        {
            throw MlxRegException("This feature supporting 28nm products only");
        }
        if (_prbsTestMode)
        {
            throw MlxRegException("This feature not working while PRBS test mode is active");
        }
        if (!_linkUP)
        {
            throw MlxRegException("Port must be active");
        }
        if (!isSpeed25GPerLane(_activeSpeed, _protoActive))
        {
            throw MlxRegException("This feature supporting 25G per lane speeds only");
        }
        if (_fecActive != FEC_MODE_NO_FEC)
        {
            throw MlxRegException("This feature supporting links running with NO-FEC only");
        }

        initErrInj();

        if (_userInput.mixerOffset0 >= 0 || _userInput.mixerOffset1 >= 0)
        {
            _errInjector->_mixerOffset0 = _userInput.mixerOffset0;
            _errInjector->_mixerOffset1 = _userInput.mixerOffset1;
            _errInjector->updateMixerOffsets();
        }
        else
        {
            _errInjector->showMixersOffset();
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors +=
          string("Reading RX error injection raised the following exception:\n") + string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::isMpeinjSupported()
{
    try
    {
        sendPrmReg(ACCESS_REG_MPEINJ, GET, "depth=%d,pcie_index=%d,node=%d", _dpn.depth, _dpn.pcieIndex, _dpn.node);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

void MlxlinkCommander::handlePCIeErrInj()
{
    if (!isMpeinjSupported())
    {
        throw MlxRegException("The current device does not support PCIe Error Injection!");
    }

    initErrInj();

    if (_userInput.errorType.empty())
    {
        _errInjector->showPcieErrInjState(_dpn);
    }
    else
    {
        _errInjector->startPcieErrInj(_dpn, _userInput.errorType, _userInput.errorDuration, _userInput.injDelay,
                                      _userInput.dbdf, _userInput.parameters);
    }
}

bool MlxlinkCommander::isPPHCRSupported()
{
    bool supported = true;
    try
    {
        sendPrmReg(ACCESS_REG_PPHCR, GET);
    }
    catch (MlxRegException& exc)
    {
        supported = false;
    }
    return supported;
}

void MlxlinkCommander::initPortInfo()
{
    try
    {
        if (_prbsTestMode)
        {
            throw MlxRegException("FEC Histogram is valid with normal link operation only");
        }
        if (_userInput._pcie)
        {
            throw MlxRegException("FEC Histogram is not available for PCIe links");
        }
        if (!isPPHCRSupported())
        {
            throw MlxRegException("FEC Histogram is not supported for the current device");
        }
        if (!_linkUP)
        {
            throw MlxRegException("FEC Histogram is valid with active link operation only");
        }

        _portInfo = new MlxlinkPortInfo(_jsonRoot);
        _portInfo->_regLib = _regLib;
        _portInfo->_localPort = _localPort;
        _portInfo->_portType = _portType;
        _portInfo->_fecActive = _fecActive;
        _portInfo->_planeInd = _userInput.planeIndex;
        _portInfo->_isHCA = _isHCA;
        _portInfo->init();

        if (_userInput.showFecHistogram)
        {
            _portInfo->showHistogram();
        }
        else if (_userInput.clearFecHistogram)
        {
            _portInfo->clearHistogram();
        }
    }
    catch (MlxRegException& exc)
    {
        _allUnhandledErrors += string("Providing FEC histogram cause the following"
                                      " exception:\n") +
                               string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::setAmBerCollectorFields()
{
    _amberCollector->_regLib = _regLib;
    _amberCollector->_pnat = _pnat;
    _amberCollector->_localPort = _localPort;
    _amberCollector->_csvFileName = _userInput._csvBer;
    _amberCollector->_iteration = _userInput._iteration;
    _amberCollector->_testMode = _userInput._testMode;
    _amberCollector->_depth = _dpn.depth;
    _amberCollector->_pcieIndex = _dpn.pcieIndex;
    _amberCollector->_node = _dpn.node;
    _amberCollector->_mlxlinkMaps = _mlxlinkMaps;
    _amberCollector->_isHca = _isHCA;
    _amberCollector->_devID = _devID;
    _amberCollector->_productTechnology = _productTechnology;
    _amberCollector->_mstDevName = _userInput._device;
    _amberCollector->_planeInd = _userInput.planeIndex;
}

void MlxlinkCommander::initAmBerCollector()
{
    if (!_amberCollector)
    {
        _amberCollector = new MlxlinkAmBerCollector(_jsonRoot);
        setAmBerCollectorFields();
    }
}

void MlxlinkCommander::prepareJsonOut()
{
    _operatingInfoCmd.toJsonFormat(_jsonRoot);
    _supportedInfoCmd.toJsonFormat(_jsonRoot);
    _troubInfoCmd.toJsonFormat(_jsonRoot);
    _toolInfoCmd.toJsonFormat(_jsonRoot);
    _testModeInfoCmd.toJsonFormat(_jsonRoot);
    _moduleInfoCmd.toJsonFormat(_jsonRoot);
    _berInfoCmd.toJsonFormat(_jsonRoot);
    _testModeBerInfoCmd.toJsonFormat(_jsonRoot);
    _mpcntPerfInfCmd.toJsonFormat(_jsonRoot);
    _mpcntTimerInfCmd.toJsonFormat(_jsonRoot);
    _eyeOpeningInfoCmd.toJsonFormat(_jsonRoot);
    _fecCapInfoCmd.toJsonFormat(_jsonRoot);
    _sltpInfoCmd.toJsonFormat(_jsonRoot);
    _showDeviceInfoCmd.toJsonFormat(_jsonRoot);
    _showBerMonitorInfo.toJsonFormat(_jsonRoot);
    _extPhyInfoCmd.toJsonFormat(_jsonRoot);
    _linkBlameInfoCmd.toJsonFormat(_jsonRoot);
    _validPcieLinks.toJsonFormat(_jsonRoot);
    _portGroupMapping.toJsonFormat(_jsonRoot);
    _plrInfoCmd.toJsonFormat(_jsonRoot);
    _krInfoCmd.toJsonFormat(_jsonRoot);
    _rxRecoveryCountersCmd.toJsonFormat(_jsonRoot);
    _periodicEqInfoCmd.toJsonFormat(_jsonRoot);

    bool errorExist = _allUnhandledErrors != "";
    _jsonRoot[JSON_STATUS_SECTION][JSON_STATUS_CODE] = errorExist ? 1 : 0;
    _jsonRoot[JSON_STATUS_SECTION][JSON_MSG] = errorExist ? _allUnhandledErrors : "success";

    if (!_jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION])
    {
        _jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION] = "N/A";
    }
}

u_int32_t MlxlinkCommander::getNumberOfPorts()
{
    int numOfPorts = 0;
    if (dm_is_gpu(static_cast<dm_dev_id_t>(_devID)) || _devID == DeviceSpectrum3 || _devID == DeviceQuantum3 || _isHCA)
    {
        sendPrmReg(ACCESS_REG_MGIR, GET);
        numOfPorts = getFieldValue("num_ports");
    }
    else
    {
        sendPrmReg(ACCESS_REG_MGPIR, GET);
        numOfPorts = getFieldValue("num_of_modules");
    }
    return numOfPorts;
}

string MlxlinkCommander::getBerString()
{
    string berString = "";
    if (_phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP)
    {
        sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_STATISTICAL_GROUP);
        string symBer = (_protoActive == ETH) ?
                          "N/A" :
                          string_format("%dE-%d", getFieldValue("symbol_ber_coef"),
                                                          getFieldValue("symbol_ber_magnitude"));

        berString = string_format(
          "%s/%dE-%d/%dE-%d", symBer.c_str(), getFieldValue("effective_ber_coef"),
          getFieldValue("effective_ber_magnitude"), getFieldValue("raw_ber_coef"), getFieldValue("raw_ber_magnitude"));
    }
    return berString;
}

void MlxlinkCommander::updateLocalPortGroup()
{
    u_int32_t numOfPorts = getNumberOfPorts();
    vector<string> localPorts;
    localPorts.reserve(numOfPorts); // Reserve memory to size 'numOfPorts'

    for (u_int32_t localPort = 1; localPort <= numOfPorts; localPort++)
    {
        localPorts.push_back(to_string(localPort));
    }
    if (_isHCA)
    {
        // NICs have only one port
        _localPortsPerGroup.push_back(PortGroup(1, 1, 0, 0));
    }
    else
    {
        handleLabelPorts(localPorts, true);
    }
}

std::string MlxlinkCommander::getSpeedStrForTableView()
{
    std::string speedStr = "";

    if (_protoActive == IB)
    {
        getPddrOperInfo(); // fsm_state + fec
        _activeSpeed = getFieldValue("link_speed_active");
    }
    else
    {
        getPtys(); // get port speed
        _activeSpeed =
          _productTechnology >= PRODUCT_16NM ? getFieldValue("ext_eth_proto_oper") : getFieldValue("eth_proto_oper");
        getPddrOperInfo(); // fsm_state + fec
    }

    _linkUP = (_phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);
    bool extended = _activeSpeedEx && _protoAdminEx;
    _linkSpeed = extended ? _activeSpeedEx : _activeSpeed;
    _isPam4Speed = isPAM4Speed(_protoActive == IB ? _activeSpeed : _activeSpeedEx, _protoActive, extended);
    _speedStrG = activeSpeed2Str(_linkSpeed, extended);
    getActualNumOfLanes(_linkSpeed, extended);
    if (_phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP)
    {
        speedStr = _speedStrG + "_" + std::to_string(_numOfLanes) + "x";
    }

    return speedStr;
}

void MlxlinkCommander::showPlr()
{
    try
    {
        sendPrmReg(ACCESS_REG_PPLM, GET);
        setPrintTitle(_plrInfoCmd, HEADER_PLR_INFO, PLR_INFO_LAST);
        setPrintVal(_plrInfoCmd, "PLR Reject Mode",
                    getStrByValue(getFieldValue("plr_reject_mode"), _mlxlinkMaps->_plrRejectMode));
        setPrintVal(_plrInfoCmd, "PLR Margin Threshold", to_string(getFieldValue("plr_margin_th")));
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("PLR is not supported for the current device!");
    }
    cout << _plrInfoCmd;
}

void MlxlinkCommander::showKr()
{
    try
    {
        sendPrmReg(ACCESS_REG_PTASv2, GET);
        setPrintTitle(_krInfoCmd, HEADER_KR_INFO, KR_INFO_LAST);
        // According to arch, the xdr_lt_cap field will reflect the kr_ext_oper capability.
        bool krExtSupported = getFieldValue("xdr_lt_cap") != 0;
        setPrintVal(_krInfoCmd, "Support Non-Standard Training Flow",
                    getStrByValue(getFieldValue("kr_ext_oper"), _mlxlinkMaps->_krExtOper), ANSI_COLOR_RESET, true,
                    krExtSupported);
        bool iterSupported = getFieldValue("iterations_cap") != 0;
        setPrintVal(_krInfoCmd, "Number of Iterations", to_string(getFieldValue("num_of_iter_oper")), ANSI_COLOR_RESET,
                    true, iterSupported);
        setPrintVal(_krInfoCmd, "Time for Iteration", to_string(getFieldValue("iter_time_oper")), ANSI_COLOR_RESET,
                    true, iterSupported);
        bool berTargetSupported = getFieldValue("ber_target_cap") != 0;
        setPrintVal(_krInfoCmd, "BER Target",
                    getFieldStr("ber_target_coef_oper") + "E-" + getFieldStr("ber_target_magnitude_oper"),
                    ANSI_COLOR_RESET, true, berTargetSupported);
        bool prbsTypeSupported = getFieldValue("prbs_type_cap") != 0;
        setPrintVal(_krInfoCmd, "PRBS Type", getStrByValue(getFieldValue("prbs_type_oper"), _mlxlinkMaps->_krPrbsType),
                    ANSI_COLOR_RESET, true, prbsTypeSupported);
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("KR is not supported for the current device!");
    }
    cout << _krInfoCmd;
}

void MlxlinkCommander::showRxRecoveryCounters()
{
    if (_userInput._showRxRecoveryCounters && _isHCA)
    {
        throw MlxRegException("Rx Recovery counters are not supported for the current device!");
    }

    try
    {
        string hostSerdesFeqStatus = "N/A", hostLogicReLockStatus = "N/A", operRecoveryType = "N/A",
               operRecoveryStatus = "N/A";
        try
        {
            setPrintTitle(_rxRecoveryCountersCmd, HEADER_RX_RECOVERY_COUNTERS, RX_RECOVERY_COUNTERS_LAST);

            sendPrmReg(ACCESS_REG_PPRM, GET);

            hostSerdesFeqStatus =
              getStrByValue(getFieldValue(_mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES]),
                            _mlxlinkMaps->_pprmRecoveryStatus);
            hostLogicReLockStatus =
              getStrByValue(getFieldValue(_mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG]),
                            _mlxlinkMaps->_pprmRecoveryStatus);
            if (hostSerdesFeqStatus != _mlxlinkMaps->_pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE] &&
                hostSerdesFeqStatus !=
                  _mlxlinkMaps->_pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE_SUPPORT_IN_NEGOTIATION])
            {
                operRecoveryType = _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES];
                operRecoveryStatus = hostSerdesFeqStatus;
            }
            else if (hostLogicReLockStatus != _mlxlinkMaps->_pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE] &&
                     hostLogicReLockStatus !=
                       _mlxlinkMaps->_pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE_SUPPORT_IN_NEGOTIATION])
            {
                operRecoveryType = _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG];
                operRecoveryStatus = hostLogicReLockStatus;
            }
            else
            {
                // operRecoveryType = "N/A";
                operRecoveryStatus = _mlxlinkMaps->_pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE];
            }

            setPrintVal(_rxRecoveryCountersCmd, "Operational Recovery Type", operRecoveryType);
            setPrintVal(_rxRecoveryCountersCmd, "Operational Recovery Status", operRecoveryStatus);

            string operTimeHostSerdesFeq = to_string(getFieldValue("oper_time_host_serdes_feq") * 10);
            setPrintVal(_rxRecoveryCountersCmd, "Oper Time Host Serdes Feq [msec]", operTimeHostSerdesFeq);
        }
        catch (MlxRegException& exc)
        {
            throw MlxRegException("Querying PPRM failed with the following exception: %s", exc.what());
        }
        try
        {
            sendPrmReg(ACCESS_REG_PPCNT, GET, "grp=%d", PPCNT_PHYSICAL_LAYER_RECOVERY_COUNTERS);
            string totalSuccessfulRecoveryEvents = to_string(getFieldValue("total_successful_recovery_events"));
            setPrintVal(_rxRecoveryCountersCmd, "Total Successful Recovery Events", totalSuccessfulRecoveryEvents);

            string timeInLastHostLogicalRecovery = to_string(getFieldValue("time_in_last_host_logical_recovery"));
            setPrintVal(_rxRecoveryCountersCmd, "Time in Last Host Logical Recovery [msec]",
                        timeInLastHostLogicalRecovery);

            string timeInLastHostSerdesFeqRecovery = to_string(getFieldValue("time_in_last_host_serdes_feq_recovery"));
            setPrintVal(_rxRecoveryCountersCmd, "Time in Last Host Serdes Feq Recovery [msec]",
                        timeInLastHostSerdesFeqRecovery);

            string timeSinceLastRecovery = to_string(getFieldValue("time_since_last_recovery"));
            setPrintVal(_rxRecoveryCountersCmd, "Time Since Last Recovery [msec]", timeSinceLastRecovery);

            string lastHostLogicalRecoveryAttemptsCount =
              to_string(getFieldValue("last_host_logical_recovery_attempts_count"));
            setPrintVal(_rxRecoveryCountersCmd, "Last Host Logical Recovery Attempts Count",
                        lastHostLogicalRecoveryAttemptsCount);

            string lastHostSerdesFeqAttemptsCount = to_string(getFieldValue("last_host_serdes_feq_attempts_count"));
            setPrintVal(_rxRecoveryCountersCmd, "Last Host Serdes Feq Attempts Count", lastHostSerdesFeqAttemptsCount);

            u_int32_t timeBetweenLast2Recoveries = getFieldValue("time_between_last_2_recoveries");
            setPrintVal(
              _rxRecoveryCountersCmd, "Time Between Last 2 Recoveries [msec]",
              timeBetweenLast2Recoveries != 65535 ? to_string(timeBetweenLast2Recoveries) : "More than 1 min");
        }
        catch (MlxRegException& exc)
        {
            string errorMsg = "";
            if (_isSwControled)
            {
                errorMsg = string("No plugged cable detected");
            }
            else
            {
                errorMsg = string("Querying PPCNT failed with the following exception: ") + string(exc.what());
            }
            throw MlxRegException(errorMsg);
        }
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("Showing rx recovery counters raised the following exception:\n" + string(exc.what()));
    }
    cout << _rxRecoveryCountersCmd;
}

void MlxlinkCommander::handlePhyRecovery()
{
    string cmdArgs = "";
    u_int32_t hostSerdesFeqStatus = 0, hostLogicReLockStatus = 0;
    try
    {
        sendPrmReg(ACCESS_REG_PPRM, GET);
        hostSerdesFeqStatus = getFieldValue(_mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES]);
        hostLogicReLockStatus = getFieldValue(_mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG]);

        if (_userInput._phyRecovery == "EN")
        {
            u_int32_t recoveryTypeCap = getFieldValue("recovery_types_cap");
            if (recoveryTypeCap == 0)
            {
                throw MlxRegException("PHY Recovery Type is not supported for the current device!");
            }
            if (_userInput._phyRecoveryType == _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES])
            {
                if ((recoveryTypeCap & PPRM_OPERATION_RECOVERY_HOST_SERDES) == 0)
                {
                    throw MlxRegException("Host Serdes Feq Recovery Type is not supported for the current device!");
                }
                MlxlinkRecord::printCmdLine("Configuring PHY Recovery Type: " +
                                              _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES],
                                            _jsonRoot);

                cmdArgs += _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES] + string("=") +
                           string(to_string(PPRM_RECOVERY_STATUS_ENABLE));
            }
            else if (_userInput._phyRecoveryType == _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG])
            {
                if ((recoveryTypeCap & PPRM_OPERATION_RECOVERY_HOST_LOG) == 0)
                {
                    throw MlxRegException("Host Logic Re-Lock Recovery Type is not supported for the current device!");
                }
                MlxlinkRecord::printCmdLine(
                  "Configuring PHY Recovery Type: " + _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG],
                  _jsonRoot);

                cmdArgs += _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG] + string("=") +
                           string(to_string(PPRM_RECOVERY_STATUS_ENABLE));
            }
            else
            {
                throw MlxRegException("Invalid PHY Recovery Type!");
            }
            sendPrmRegWithoutReset(ACCESS_REG_PPRM, SET, cmdArgs.c_str());
        }
        else if (_userInput._phyRecovery == "DS")
        {
            if (_userInput._phyRecoveryType == _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES])
            {
                MlxlinkRecord::printCmdLine("Disabling PHY Recovery Type: " +
                                              _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES],
                                            _jsonRoot);
                cmdArgs += _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG] + "=" +
                           to_string(hostLogicReLockStatus) + "," +
                           _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES] + string("=") +
                           string(to_string(PPRM_RECOVERY_STATUS_DISABLE_SUPPORT_IN_NEGOTIATION));
            }
            else if (_userInput._phyRecoveryType == _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG])
            {
                MlxlinkRecord::printCmdLine(
                  "Disabling PHY Recovery Type: " + _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG],
                  _jsonRoot);
                cmdArgs += _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES] + "=" +
                           to_string(hostSerdesFeqStatus) + "," +
                           _mlxlinkMaps->_pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG] + string("=") +
                           string(to_string(PPRM_RECOVERY_STATUS_DISABLE_SUPPORT_IN_NEGOTIATION));
            }
            else
            {
                throw MlxRegException("Invalid PHY Recovery Type!");
            }
            sendPrmRegWithoutReset(ACCESS_REG_PPRM, SET, cmdArgs.c_str());
        }
        sendPaosToggle();
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("Handling PHY Recovery command raised the following exception:\n" + string(exc.what()));
    }
}

void MlxlinkCommander::handleLinkTraining()
{
    try
    {
        string cmdArgs = "";
        sendPrmReg(ACCESS_REG_PTASv2, GET);

        if (_userInput._linkTraining == "EN" || _userInput._linkTraining == "EN_EXT")
        {
            if (getFieldValue("xdr_lt_cap") == 0 || getFieldValue("kr_ext_cap") == 0)
            {
                throw MlxRegException("Link Training is not supported for the current device!");
            }
            cmdArgs += "xdr_lt_c2c_en=" + to_string(XDR_LT_C2C_EN_XDR_LT_C2C_ENABLED_LT);

            if (_userInput._linkTraining == "EN_EXT")
            {
                cmdArgs += ",kr_ext_req=" + to_string(KR_EXT_REQ_KR_EXT_ENABLED_ADVANCED_ALGO);
            }
            else
            {
                cmdArgs += ",kr_ext_req=" + to_string(KR_EXT_REQ_KR_EXT_REGULAR_LT);
            }
            sendPaosDown();
            MlxlinkRecord::printCmdLine("Enabling Link Training", _jsonRoot);
            sendPrmReg(ACCESS_REG_PTASv2, GET);
            sendPrmRegWithoutReset(ACCESS_REG_PTASv2, SET, cmdArgs.c_str());
            sendPaosUP();
        }
        else if (_userInput._linkTraining == "DS")
        {
            cmdArgs += "xdr_lt_c2c_en=" + to_string(XDR_LT_C2C_EN_XDR_LT_C2C_DISABLED_LT) +
                       ",kr_ext_req=" + to_string(KR_EXT_REQ_FW_DEFAULT);
            sendPaosDown();
            MlxlinkRecord::printCmdLine("Disabling Link Training", _jsonRoot);
            sendPrmReg(ACCESS_REG_PTASv2, GET);
            sendPrmRegWithoutReset(ACCESS_REG_PTASv2, SET, cmdArgs.c_str());
            sendPaosUP();
        }
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("Handling Link Training command raised the following exception:\n" + string(exc.what()));
    }
}

void MlxlinkCommander::showPeriodicEq()
{
    try
    {
        sendPrmReg(ACCESS_REG_SLLM, GET);
        setPrintTitle(_periodicEqInfoCmd, HEADER_PERIODIC_EQ, PERIODIC_EQ_INFO_LAST);
        setPrintVal(_periodicEqInfoCmd, "PEQ Interval Applied [uS]",
                    to_string(getFieldValue("peq_interval_period", 0, 0, true) * 10));
        setPrintVal(_periodicEqInfoCmd, "PEQ Interval Oper [uS]",
                    to_string(getFieldValue("peq_interval_period_oper") * 10));
    }
    catch (MlxRegException& exc)
    {
        throw MlxRegException("Periodic EQ is not supported for the current device!\n" + string(exc.what()));
    }
    cout << _periodicEqInfoCmd;
}

void MlxlinkCommander::setPeriodicEq()
{
    try
    {
        sendPrmReg(ACCESS_REG_SLLM, GET);

        // WA until FW supports this field
        // sendPrmReg(ACCESS_REG_SLLM, SET, "peq_cap=1");

        bool brLanesCap = getFieldValue("br_lanes_cap") != 0;
        bool periodicEqIntervalSupported = getFieldValue("peq_cap") != 0;
        if (!periodicEqIntervalSupported)
        {
            throw MlxRegException("Periodic EQ is not supported for the current device!");
        }
        // make sure all ports are down before setting the periodic eq interval
        if (!checkAllPortsDown())
        {
            throw MlxRegException("All ports must be down before setting the PEQ interval!");
        }
        configurePeqForAllPorts(brLanesCap);
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Setting Periodic EQ raised the following exception:\n" + string(exc.what()));
    }
}

bool MlxlinkCommander::checkAllPortsDown()
{
    cout << "\nChecking all ports are down";
    try
    {
        updateLocalPortGroup();

        for (const auto& portInfo : _localPortsPerGroup)
        {
            _localPort = portInfo.localPort;
            if (!checkPaosDown())
            {
                return false;
            }
        }
        cout << " DONE" << endl;
        return true;
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Setting Periodic EQ raised the following exception:\n" + string(exc.what()));
    }
}

void MlxlinkCommander::configurePeqForAllPorts(bool brLanesCap)
{
    string cmdArgs = "";
    try
    {
        int totalPortsNum = _localPortsPerGroup.size();
        int currentPortIndex = 1;

        for (const auto& portInfo : _localPortsPerGroup)
        {
            cmdArgs = "peq_cap=1,peq_interval_period=" + to_string(_userInput._setPeriodicEqInterval / 10);
            _localPort = portInfo.localPort;
            if (brLanesCap)
            {
                cmdArgs += ",br_lanes=1";
                sendPrmReg(ACCESS_REG_SLLM, SET, cmdArgs.c_str());
            }
            else
            {
                string locCmdArgs = cmdArgs;
                locCmdArgs += ",lane=0";
                sendPrmReg(ACCESS_REG_SLLM, SET, locCmdArgs.c_str());
                locCmdArgs = cmdArgs;
                locCmdArgs += ",lane=1";
                sendPrmReg(ACCESS_REG_SLLM, SET, locCmdArgs.c_str());
            }
            printProgressBar(currentPortIndex * 100 / totalPortsNum, "Setting Periodic EQ Interval", "");
            currentPortIndex++;
        }
    }
    catch (const std::exception& exc)
    {
        throw MlxRegException("Setting Periodic EQ raised the following exception:\n" + string(exc.what()));
    }
}
