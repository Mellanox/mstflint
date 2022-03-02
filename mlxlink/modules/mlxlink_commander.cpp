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

#include "mlxlink_commander.h"

using namespace mlxreg;

MlxlinkCommander::MlxlinkCommander() : _userInput()

{
    _device = "";
    _extAdbFile = "";
    _localPort = 0;
    _portType = 0;
    _numOfLanes = MAX_LANES_NUMBER;
    _numOfLanesPcie = 0;
    _linkUP = false;
    _plugged = false;
    _linkModeForce = false;
    _prbsTestMode = false;
    _useExtAdb = true;
    _isHCA = false;
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
    _uniqueCmds = 0;
    _networkCmds = 0;
    _activeSpeed = 0;
    _activeSpeedEx = 0;
    _protoCapability = 0;
    _deviceCapability = 0;
    _linkSpeed = 0;
    _protoCapabilityEx = false;
    _ddmSupported = false;
    _cmisCable = false;
    _qsfpCable = false;
    _mngCableUnplugged = false;
    _isPam4Speed = false;
    _ignorePortType = true;
    _ignorePortStatus = true;
    _isGboxPort = false;
    _ignoreIbFECCheck = true;
    _protoAdmin = 0;
    _protoAdminEx = 0;
    _speedBerCsv = 0;
    _fecActive = 0;
    _protoActive = 0;
    _productTechnology = 0;
    _allUnhandledErrors = "";
    _mlxlinkMaps = MlxlinkMaps::getInstance();
    _cablesCommander = NULL;
    _eyeOpener = NULL;
    _errInjector = NULL;
    _portInfo = NULL;
    _amberCollector = NULL;
    _uniqueCableCmds = 0;
}

MlxlinkCommander::~MlxlinkCommander()
{
    if (_cablesCommander) {
        delete _cablesCommander;
    }
    if (_eyeOpener) {
        delete _eyeOpener;
    }
    if (_errInjector) {
        delete _errInjector;
    }
    if (_portInfo) {
        delete _portInfo;
    }
    if (_amberCollector) {
        delete _amberCollector;
    }
    if (_gvmiAddress) {
        writeGvmi(0);
    }
    if (_mf) {
        mclose(_mf);
    }
    if (_regLib) {
        delete _regLib;
    }
    if (_mlxlinkLogger) {
        delete _mlxlinkLogger;
    }
    if(_mlxlinkMaps) {
        delete _mlxlinkMaps;
    }
}

void MlxlinkCommander::updatePortType()
{
    if (!_isHCA) {
        try {
            updateField("port_type", _portType);
        } catch (MlxRegException &exc) {
            // Ignore updating the port type field if it's not exist
        }
    }
}

void MlxlinkCommander::validatePortType(const string &portTypeStr)
{
    _portType = NETWORK_PORT_TYPE;
    map<string, u_int32_t>::iterator it =
            _mlxlinkMaps->_networkPorts.find(portTypeStr);
    if (it == _mlxlinkMaps->_networkPorts.end()) {
        string errMsg = "";
        for (it = _mlxlinkMaps->_networkPorts.begin();
             it != _mlxlinkMaps->_networkPorts.end(); it++) {
            errMsg  += it->first;
            if (it->second == NETWORK_PORT_TYPE) {
                errMsg += "(Default)";
            }
            errMsg += ", ";
        }
        errMsg = deleteLastChar(errMsg, 2);
        throw MlxRegException("Invalid port type, valid port types are [" + errMsg + "]");
    } else if (it->second != NETWORK_PORT_TYPE_LAST) {
        _portType = it->second;
    }

    if ((_portType == NETWORK_PORT_TYPE_NEAR) ||
        (_portType == NETWORK_PORT_TYPE_IC_LR) ||
        (_portType == NETWORK_PORT_TYPE_FAR)) {
        _isGboxPort = true;
    }

    if(_isGboxPort && !isDSdevice()) {
        throw MlxRegException("Port types of GEARBOX_HOST, INTERNAL_IC_LR and "\
                              "GEARBOX_LINE can be used with Switches supporting downstream devices only");
    }
}

void MlxlinkCommander::gearboxBlock(const string &option)
{
    if (_isGboxPort) {
        throw MlxRegException("--" + option + " flag is not applicable for " +
                _userInput._portType + " port type");
    }
}

void MlxlinkCommander::checkRegCmd()
{
    string regName = "PAOS";
    resetParser(regName);
    updateField("local_port", _localPort);
    updateField("swid", SWID);
    try {
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    } catch (MlxRegException& exp) {
        throw MlxRegException("Problem accessing the device. Please verify that driver is up");
    }
    throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
}

void MlxlinkCommander::checkValidFW()
{
    try {
        u_int32_t tmpLocalPort = _localPort;
        struct connectib_icmd_get_fw_info fw_info;
        memset(&fw_info, 0, sizeof(fw_info));
        gcif_get_fw_info(_mf, &fw_info);
        char fwVersion [32];
        sprintf(fwVersion, "%02d.%02d.%04d", fw_info.fw_version.MAJOR,
                fw_info.fw_version.MINOR, fw_info.fw_version.SUBMINOR);
        _fwVersion = string(fwVersion);
        if(_userInput._pcie){ // Fw validity should be checked, so set the local port to 1.
            _localPort = 1;
        }
        string regName = "PDDR";
        resetParser(regName);
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);

        try {

            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (MlxRegException& exp) {
            if (exp.what_s() != "Please Provide Valid gvmi Address (--gvmi_address <address>)") {
                checkRegCmd();
            } else {
                throw MlxRegException(exp);
            }
        }

        u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");

        resetParser(regName);
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_TROUBLESHOOTING_INFO_PAGE);
        updateField("group_opcode", ADVANCED_OPCODE);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        u_int32_t statusOpcode = getFieldValue("advanced_opcode");

        if (phyMngrFsmState == 0 && statusOpcode == 0) {
            checkAllPortsStatus();
        }
        _localPort = tmpLocalPort;
    } catch (const std::exception &exc) {
        throw MlxRegException(string(
                "Checking valid firmware raised the following exception: ") +
                string(exc.what()) + string("\n"));
    }
}

void MlxlinkCommander::getProductTechnology()
{
    try {
        if (_devID == DeviceConnectX7 || _devID == DeviceQuantum2) {
            resetParser(ACCESS_REG_MGIR);

            genBuffSendRegister(ACCESS_REG_MGIR, MACCESS_REG_METHOD_GET);

            _productTechnology = getFieldValue("technology");
        } else {
            resetParser(ACCESS_REG_SLRG);
            updateField("local_port", _localPort);
            updateField("pnat", (_userInput._pcie) ? PNAT_PCIE : PNAT_LOCAL);

            genBuffSendRegister(ACCESS_REG_SLRG, MACCESS_REG_METHOD_GET);

            _productTechnology = getVersion(getFieldValue("version"));
        }
    } catch (MlxRegException &exc) {
        throw MlxRegException(
                "Unable to get product technology: %s", exc.what_s().c_str());
    }
}

u_int32_t MlxlinkCommander::maxLocalPort()
{
    switch (_devID) {
    case DeviceSpectrum:
        return MAX_LOCAL_PORT_ETH;

    case DeviceSwitchIB:
    case DeviceSwitchIB2:
        return MAX_LOCAL_PORT_IB;

    case DeviceQuantum:
        return MAX_LOCAL_PORT_QUANTUM;

    case DeviceQuantum2:
        return MAX_LOCAL_PORT_QUANTUM2;

    case DeviceSpectrum2:
    case DeviceSpectrum3:
        return MAX_LOCAL_PORT_SPECTRUM2;

    case DeviceSpectrum4:
        return MAX_LOCAL_PORT_SPECTRUM4;

    default:
        return 0;
    }
    return 0;
}

bool MlxlinkCommander::checkPortStatus(u_int32_t localPort)
{
    string regName = "PDDR";
    resetParser(regName);
    updatePortType();

    updateField("local_port", localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");

    resetParser(regName);
    updatePortType();

    updateField("local_port", localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("page_select", PDDR_TROUBLESHOOTING_INFO_PAGE);
    updateField("group_opcode", ADVANCED_OPCODE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    u_int32_t statusOpcode = getFieldValue("advanced_opcode");

    if (!(phyMngrFsmState == 0 && statusOpcode == 0)) {
        return true;
    }
    return false;
}

void MlxlinkCommander::checkAllPortsStatus()
{
    if (_isHCA) {
        checkRegCmd();
    }
    if (_devID == DeviceSpectrum) {
        string regName = "PMLP";
        for (u_int32_t localPort = 1; localPort <= maxLocalPort();
             localPort++) {
            resetParser(regName);
            updateField("local_port", localPort);

            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            if (getFieldValue("width") == 0) {
                continue;
            }
            if (checkPortStatus(localPort)) {
                return;
            }
        }
        throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
    } else if (dm_dev_is_ib_switch(_devID)) {
        string regName = "PLIB";
        for (u_int32_t localPort = 1; localPort <= maxLocalPort();
             localPort++) {
            resetParser(regName);
            updateField("local_port", localPort);

            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            if (getFieldValue("ib_port") == 0) {
                continue;
            }
            if (checkPortStatus(localPort)) {
                return;
            }
        }
        throw MlxRegException("FW Version " + _fwVersion + " is not supported. Please update FW.");
    }
}

void MlxlinkCommander::validatePortToLC()
{
    bool isDownStreamDevValid = true;
    string regName = "PMLP";
    resetParser(regName);
    updateField("local_port", _localPort);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    u_int32_t slotIndex = getFieldValue("slot_index_0");

    try {
        regName = "MDDQ";
        resetParser(regName);
        updateField("query_type", 1); //1 for slot query
        updateField("slot_index", slotIndex);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    } catch (MlxRegException &exc) {
        isDownStreamDevValid = false;
    }

    if (!isDownStreamDevValid) {
        if (slotIndex == 0 && _isGboxPort) {
            throw MlxRegException("No cards detected on the device.");
        }
    } else if (_isGboxPort) {
        if (getFieldValue("lc_ready") != 1) {
            throw MlxRegException("Invalid port number, Line card %d is not ready", slotIndex);
        }
    }
}

void MlxlinkCommander::handlePortStr(const string &portStr)
{
    auto portParts = MlxlinkRecord::split(portStr, "/");
    // validate arguments
    for (auto it = portParts.begin(); it != portParts.end(); it++) {
        if ((*it).empty()) {
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
    if (portParts.size() > 1) {
        strToUint32((char*) portParts[1].c_str(), _userInput._splitPort);
        _userInput._splitProvided = true;
        if (portParts.size() > SECOND_LEVEL_PORT_ACCESS) {
            // it's the split part of Quantum-2 (xx/xx/split)
            strToUint32((char*) portParts[2].c_str(), _userInput._secondSplitPort);
            _userInput._secondSplitProvided = true;
        } else if (portParts.size() > THIRD_LEVEL_PORT_ACCESS) {
            throw MlxRegException("Failed to handle option port");
        }
    }

    strToUint32((char*) portParts[0].c_str(), _userInput._labelPort);
    _userInput._portSpecified = true;
}

void MlxlinkCommander::labelToLocalPort() {
    if (_isHCA && _userInput._pcie) {
        _dpn.depth = _userInput._depth;
        _dpn.pcieIndex = _userInput._pcieIndex;
        _dpn.node = _userInput._node;
        initValidDPNList();
        if (_userInput._sendDpn) {
            int localPort = getLocalPortFromMPIR(_dpn);
            if (localPort >= 0) {
                _localPort = localPort;
            } else {
                throw MlxRegException("Invalid PCIe link: depth, pcie_index and node [%d, %d, %d]",
                        _dpn.depth, _dpn.pcieIndex, _dpn.node);
            }
        } else if (_userInput._portSpecified){
            checkLocalPortDPNMapping(_userInput._labelPort);
            _localPort = _userInput._labelPort;
        } else {
            if (!_validDpns.empty()) {
                _dpn = _validDpns[0]; //default DPN link
            }
            _localPort = _dpn.pcieIndex;
            if (_dpn.depth > 0) {
                _localPort = _dpn.node + DBN_TO_LOCAL_PORT_BASE;
            }
        }
        return;
    }
    if (_isHCA) {
        labelToHCALocalPort();
        return;
    } else if(_userInput._pcie) {
        throw MlxRegException("No PCIE in Switch!");
    }

    if (_devID == DeviceSpectrum || _devID == DeviceSpectrum2 ||
        _devID == DeviceSpectrum3 || _devID == DeviceSpectrum4) {
        if (isDSdevice()) {
            labeltoDSlocalPort();
        } else {
            labelToSpectLocalPort();
        }
    } else if (dm_dev_is_ib_switch(_devID)) {
        labelToIBLocalPort();
    }
}

bool MlxlinkCommander::isDSdevice()
{
    bool isDownStreamDevValid = true;

    try {
        resetParser(ACCESS_REG_MDDQ);
        updateField("query_type", 1);
        updateField("slot_index", 1);
        genBuffSendRegister(ACCESS_REG_MDDQ, MACCESS_REG_METHOD_GET);
    } catch (MlxRegException &exc) {
        isDownStreamDevValid = false;
    }

    return isDownStreamDevValid;
}

void MlxlinkCommander::labeltoDSlocalPort()
{
    u_int32_t lineCard = _userInput._labelPort;
    u_int32_t port = _userInput._splitPort;
    bool isLocalPortValid = false;

    if (_userInput._secondSplitProvided) {
        throw MlxRegException("No split supported for downstream devices");
    }

    for (u_int32_t localPort = 1 ; localPort <= maxLocalPort(); localPort++) {
        resetParser(ACCESS_REG_PLLP);
        updateField("local_port", localPort);
        try {
            genBuffSendRegister(ACCESS_REG_PLLP, MACCESS_REG_METHOD_GET);
        } catch(MlxRegException &exp) {
            continue;
        }

        if ((getFieldValue("label_port") == port) && (getFieldValue("slot_num") == lineCard)) {
            _localPort = localPort;
            _slotIndex = lineCard;
            isLocalPortValid = true;
            break;
        }
    }

    if (!isLocalPortValid) {
        throw MlxRegException("Invalid port number");
    }

    resetParser(ACCESS_REG_MDDQ);
    updateField("query_type", 1);
    updateField("slot_index", lineCard);
    genBuffSendRegister(ACCESS_REG_MDDQ, MACCESS_REG_METHOD_GET);

    if (getFieldValue("lc_ready") != 1) {
        throw MlxRegException("Invalid port number, Line card %d is not ready", lineCard);
    }
}

void MlxlinkCommander::checkLocalPortDPNMapping(u_int32_t localPort)
{
    string regName = "MPIR";
    for (u_int32_t i = 0 ; i < _validDpns.size(); i++) {
        resetParser(regName);
        updateField("depth", _validDpns[i].depth);
        updateField("pcie_index", _validDpns[i].pcieIndex);
        updateField("node", _validDpns[i].node);
        try {
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (MlxRegException &exc) {
            continue;
        }
        if (getFieldValue("local_port") == localPort) {
            _dpn = _validDpns[i];
            return;
        }
    }
    throw MlxRegException("Invalid PCIe local port to depth, pcie_index and node mapping: %d", localPort);
}

int MlxlinkCommander::getLocalPortFromMPIR(DPN& dpn)
{
    if (!isIn(dpn, _validDpns)) {
        throw MlxRegException("Invalid PCIe link: depth, pcie_index and node [%d, %d, %d]",
                dpn.depth, dpn.pcieIndex, dpn.node);
    }

    int localPort= -1;
    if(!_userInput._portSpecified &&
            !(dpn.depth == 0 && dpn.node == 0 && dpn.pcieIndex ==0)) {
        string regName = "MPIR";
        resetParser(regName);
        updateField("depth", dpn.depth);
        updateField("pcie_index", dpn.pcieIndex);
        updateField("node", dpn.node);
        try{
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            localPort = getFieldValue("local_port");
        } catch(MlxRegException &exc) {
        }
    } else if (_userInput._portSpecified) {
        localPort = _userInput._labelPort;
    } else {
        localPort = 0;
    }
    return localPort;
}

void MlxlinkCommander::labelToHCALocalPort()
{
    u_int32_t mtype = 0;
    mget_mdevs_type(_mf, &mtype);
    if (_userInput._splitProvided) {
        throw MlxRegException("No Splits in HCA!");
    } else if (_userInput._labelPort > 1
            && !(mtype & (MST_USB | MST_USB_DIMAX))) {
        throw MlxRegException(
                "Please Provide the Physical Device of Port "
                        + to_string(_userInput._labelPort));
    } else if (_userInput._labelPort > 1
            && (mtype & (MST_USB | MST_USB_DIMAX))) {
        if (_userInput._labelPort == 2) {
            if (_userInput._gvmiAddress == 0) {
                throw MlxRegException(
                        "Please Provide Valid gvmi Address (--gvmi_address <address>)");
            }
        } else {
            throw MlxRegException("Please Provide Valid Port Number (1/2)");
        }
    }
    _localPort = 1;
}

void MlxlinkCommander::labelToSpectLocalPort()
{
    string regName;
    u_int32_t spectWithGearBox = 0;
    if (_devID >= DeviceSpectrum2) {
        regName = "MGPIR";
        resetParser(regName);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        spectWithGearBox = getFieldValue("num_of_devices");
    }
    regName = "PMLP";
    string splitStr = to_string(
            (_userInput._splitPort > 0) ?
                    _userInput._splitPort - 1 : _userInput._splitPort);
    int splitAdjustment = 0;
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++) {
        resetParser(regName);
        updateField("local_port", localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        _numOfLanes = getFieldValue("width");
        if (_numOfLanes == 0) {
            continue;
        }
        splitAdjustment = 0;
        if ((getFieldValue("module_0") + 1)  == _userInput._labelPort) {
            checkWidthSplit();
            if (_userInput._splitProvided) {
                if (_devID == DeviceSpectrum3 || _devID == DeviceSpectrum4 ||
                    (_devID != DeviceSpectrum && !spectWithGearBox)) {
                    if (_devID == DeviceSpectrum2 && _numOfLanes == 4) {
                        splitAdjustment = 2;
                    } else if (!((_devID == DeviceSpectrum2 && _numOfLanes == 2) ||
                            ((_devID == DeviceSpectrum3 || _devID == DeviceSpectrum4) && _numOfLanes == 4))) {
                        splitAdjustment = -1;
                    }
                } else if (_devID == DeviceSpectrum2 && spectWithGearBox){
                    if (_numOfLanes != 4) {
                        splitAdjustment = -1;
                    }
                } else {
                    splitAdjustment = -1;
                }
                _localPort = localPort + _userInput._splitPort + splitAdjustment;
            } else {
                _localPort = localPort;
            }
            updateField("local_port", _localPort);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            if ((getFieldValue("module_0") + 1) == _userInput._labelPort) {
                return;
            }
        }
    }
    throw MlxRegException(
                "Failed to find Local Port, please provide valid Port Number");
}

void MlxlinkCommander::checkWidthSplit()
{
    if (_userInput._splitProvided) {
        if (_userInput._secondSplitProvided) {
            throw MlxRegException("Invalid port number!");
        }
        switch (_userInput._splitPort) {
        case 1:
            throw MlxRegException("Invalid split number!");
        case 2:
            if (_numOfLanes < 4 ||
                ((_devID == DeviceSpectrum3 || _devID == DeviceSpectrum4) && _numOfLanes == 4)) {
                return;
            }
            break;
        case 3:
        case 4:
            if (_numOfLanes == 1 ||
                ((_devID == DeviceSpectrum3 || _devID == DeviceSpectrum4) && _numOfLanes == 2)) {
                return;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            if ((_devID == DeviceSpectrum3 || _devID == DeviceSpectrum4) && _numOfLanes == 1) {
                return;
            }
            break;
        default:
            break;
        }
        throw MlxRegException(
                  "Port " + to_string(_userInput._labelPort) + "/"
                  + to_string(_userInput._splitPort)
                  + " does not exist!");
    }
}

void MlxlinkCommander::labelToIBLocalPort()
{
    u_int32_t labelPort = _userInput._labelPort;
    bool ibSplitReady = isIBSplitReady() && (_devID == DeviceQuantum || _devID == DeviceQuantum2);
    if (_userInput._splitProvided && _devID != DeviceQuantum && _devID != DeviceQuantum2) {
        throw MlxRegException("No split in IB!");
    }
    u_int32_t maxLabelPort = _devID == DeviceQuantum2? maxLocalPort()/4 :
                             _devID == DeviceQuantum? maxLocalPort()/2 - 1 : maxLocalPort();
    if ((labelPort > maxLabelPort) ||
        (_userInput._secondSplitProvided && _devID != DeviceQuantum2) ||
        (_userInput._splitPort > 2)) {
        throw MlxRegException("Invalid port number!");
    }
    if (_devID == DeviceQuantum || _devID == DeviceQuantum2) {
        labelPort = calculatePanelPort(ibSplitReady);
    }
    string regName = "PLIB";
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++) {
        resetParser(regName);
        updateField("local_port", localPort);
        try {
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (MlxRegException& exp) {
            continue; // no reason to fail when one of the ports is not supported, such as in split mode.
        }
        if (getFieldValue("ib_port") == labelPort) {
            _localPort = localPort;
            return;
        }
    }
    if ((_devID == DeviceQuantum || _devID == DeviceQuantum2) && ibSplitReady) {
        string portStr = "Port " + to_string(_userInput._labelPort);
        string swSplitCmd = "module-type qsfp-split-2";
        if (_devID == DeviceQuantum2) {
            portStr = portStr + "/" + to_string(_userInput._splitPort);
            swSplitCmd = "port-type split-2";
        }
        throw MlxRegException("%s is not splitted physically from switch side, Use this command to split it physically:\n"
                              "interface ib <port/ports range> %s", portStr.c_str(), swSplitCmd.c_str());
    }
}

bool MlxlinkCommander::isIBSplitReady() {
    string regName = "PLIB";
    u_int32_t max_port = maxLocalPort();
    for (u_int32_t localPort = 1; localPort <= max_port; localPort++) {
        resetParser(regName);
        updateField("local_port", localPort);
        try {
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (MlxRegException& exp) {
            continue; // no reason to fail when one of the ports is not supported, such as in split mode.
        }
        if (getFieldValue("ib_port") == max_port/2) {
            return true;
        }
    }
    return false;
}

u_int32_t MlxlinkCommander::calculatePanelPort(bool ibSplitReady)
{
    u_int32_t panelPort = _userInput._labelPort; // by default, the label port is equal to panel port if no split
    bool splitProvided = _devID == DeviceQuantum ? _userInput._splitProvided
                                                 : _userInput._secondSplitProvided;
    u_int32_t split = _devID == DeviceQuantum ? _userInput._splitPort
                                              : _userInput._secondSplitPort;
    if (_devID == DeviceQuantum2) {
        // For Quantum-2, user should provide cage/port to access the ports in the cage
        // cage"panelPort"/port"_userInput._splitPort" is converted to label port according to the following equation:
        panelPort = 2 * panelPort + _userInput._splitPort - 2;
    }
    if (ibSplitReady) {
        // If split ready, then the panelPort mapping will be chaned
        if (!splitProvided) {
            panelPort = (panelPort * 2) - 1; // Access the main port (without providing the split)
                                             // For Quantum will be e.g (port/split): 2/1
                                             // For Quantum-2 will be e.g (cage/port/split): 1/2/1
        } else {
            if (split != 2) {
                throw MlxRegException("Invalid split number!");
            }
            panelPort = 2 * panelPort; // Access the second port (with providing the split)
                                       // For Quantum will be e.g (port/split): 2/2
                                       // For Quantum-2 will be e.g (cage/port/split): 1/2/2
        }
    } else if (splitProvided) {
        throw MlxRegException("Split mode is not ready!"
                              "\nThis command is used to set the split mode ready from switch side:"
                              "\nsystem profile ib split-ready");
    }

    return panelPort;
}

void MlxlinkCommander::checkStrLength(const string &str)
{
    if (str.size() > MAX_INPUT_LENGTH) {
        throw MlxRegException("Argument: %s... is invalid.", str.substr(0, MAX_INPUT_LENGTH).c_str());
    }
}

void MlxlinkCommander::getActualNumOfLanes(u_int32_t linkSpeedActive, bool extended)
{
    if (_protoActive == IB) {
        string regName = "PTYS";
        resetParser(regName);
        updateField("local_port", _localPort);
        updateField("proto_mask", _protoActive);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        _numOfLanes = getFieldValue("ib_link_width_oper");
    } else if (_protoActive == ETH) {
        if (_linkUP) {
            if (extended) {
                _numOfLanes = _mlxlinkMaps->_ExtETHSpeed2Lanes[linkSpeedActive];
            } else {
                _numOfLanes = _mlxlinkMaps->_ETHSpeed2Lanes[linkSpeedActive];
            }
        } else {
            string regName = "PMLP";
            resetParser(regName);
            updateField("local_port", _localPort);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

            _numOfLanes = getFieldValue("width");
        }
    }
}

u_int32_t MlxlinkCommander::activeSpeed2gNum(u_int32_t mask, bool extended)
{
    if(extended) {
        return _mlxlinkMaps->_EthExtSpeed2gNum[mask];
    }
    return (_protoActive == IB) ? _mlxlinkMaps->_IBSpeed2gNum[mask] : _mlxlinkMaps->_ETHSpeed2gNum[mask];
}

string MlxlinkCommander::activeSpeed2Str(u_int32_t mask, bool extended)
{
    if(extended) {
        return _mlxlinkMaps->_EthExtSpeed2Str[mask];
    }
    return (_protoActive == IB) ? _mlxlinkMaps->_IBSpeed2Str[mask] : _mlxlinkMaps->_ETHSpeed2Str[mask];
}

void MlxlinkCommander::getCableParams()
{
    try {
        string regName = "PDDR";
        resetParser(regName);

        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_MODULE_INFO_PAGE);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

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
        regName = "PMLP";
        resetParser(regName);
        updateField("local_port", _localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        _moduleNumber = getFieldValue("module_0");
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Getting cable parameters via PDDR raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::inPrbsTestMode()
{
    try {
        bool res = checkPaosDown() && checkPpaosTestMode();
        return res;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Checking in PRBS test mode raised the following exception: ") + string(exc.what()) + string("\n");
    }
    return false;
}

bool MlxlinkCommander::checkGBPpaosDown()
{
    string regName = "PPAOS";
    resetParser(regName);
    updatePortType();

    updateField("swid", SWID);
    updateField("local_port", _localPort);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return getFieldValue("phy_status") != PAOS_UP;
}

bool MlxlinkCommander::checkPaosDown()
{
    if (_isGboxPort) {
        return checkGBPpaosDown();
    } else {
        string regName = "PAOS";
        resetParser(regName);
        updateField("swid", SWID);
        updateField("local_port", _localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        u_int32_t paosOperStatus = getFieldValue("oper_status");
        if (paosOperStatus == PAOS_DOWN) {
            return true;
        }
        return false;
    }
}

bool MlxlinkCommander::checkPpaosTestMode()
{
    string regName = "PPAOS";
    resetParser(regName);
    updatePortType();

    updateField("swid", SWID);
    updateField("local_port", _localPort);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t ppaosPhyTestModeStatus = getFieldValue("phy_test_mode_status");
    if (ppaosPhyTestModeStatus == PHY_TEST_MODE_STATUS) {
        return true;
    }
    return false;
}

void MlxlinkCommander::getSltpParamsFromVector(std::vector<string> sltpParams)
{
    for (u_int32_t i = 0; i < sltpParams.size(); i++) {
        strToInt32((char*) sltpParams[i].c_str(), _userInput._sltpParams[i]);
    }
}

std::vector<string> MlxlinkCommander::parseParamsFromLine(const string & ParamsLine)
{
    std::vector<string> paramVector;
    string param;
    stringstream stream(ParamsLine);
    while (getline(stream, param, ',')) {
        if (param == "") {
            throw  MlxRegException("Wrong input format");
        }
        paramVector.push_back(param.c_str());
    }
    return paramVector;
}

void MlxlinkCommander::getprbsLanesFromParams(std::vector<string> prbsLanesParams)
{
    u_int32_t lane = 0;
    vector<string>::iterator it = prbsLanesParams.begin();
    while (it != prbsLanesParams.end()) {
        strToUint32((char *)(*it).c_str(), lane);
        _userInput._prbsLanesToSet[lane] = true;
        it++;
    }
}

int MlxlinkCommander::handleIBLocalPort(u_int32_t labelPort, bool ibSplitReady)
{
    string regName = "PLIB";
    int targetLocalPort = -1;
    if ((_devID == DeviceQuantum2 || (_devID == DeviceQuantum && ibSplitReady))) {
        labelPort = 2 * labelPort - 1;
    }
    if (_devID == DeviceQuantum2 && ibSplitReady) {
        labelPort = 2 * labelPort - 1;
    }
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++) {
        resetParser(regName);
        updateField("local_port", localPort);
        try {
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (MlxRegException& exp) {
            continue;
        }
        if (getFieldValue("ib_port") == labelPort) {
            targetLocalPort = localPort;
            fillIbPortGroupMap(targetLocalPort, labelPort, _userInput._setGroup, ibSplitReady);
            break;
        }
    }
    return targetLocalPort;
}

int MlxlinkCommander::handleEthLocalPort(u_int32_t labelPort, bool spect2WithGb)
{
    string regName = "PMLP";
    int targetLocalPort = -1;
    for (u_int32_t localPort = 1; localPort <= maxLocalPort(); localPort++) {
        resetParser(regName);
        updateField("local_port", localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        if (getFieldValue("width") == 0) {
            continue;
        }
        if (getFieldValue("module_0") + 1
                == labelPort) {
            targetLocalPort = localPort;
            fillEthPortGroupMap(localPort, labelPort, _userInput._setGroup,
                    getFieldValue("width"), spect2WithGb);
            break;
        }
    }
    return targetLocalPort;
}

void MlxlinkCommander::fillEthPortGroupMap(u_int32_t localPort,u_int32_t labelPort,
        u_int32_t group, u_int32_t width, bool spect2WithGb)
{
    if(_ignorePortStatus) {
        if (!width) {
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
        }
    }
    if (spect2WithGb) {
        switch (width) {
        case 2:
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            _localPortsPerGroup.push_back(PortGroup(localPort+1, labelPort, group, 2));
            break;
        case 4:
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
            break;
        }
    } else {
        switch (width) {
        case 1:
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            _localPortsPerGroup.push_back(PortGroup(localPort+1, labelPort, group, 2));
            _localPortsPerGroup.push_back(PortGroup(localPort+2, labelPort, group, 3));
            _localPortsPerGroup.push_back(PortGroup(localPort+3, labelPort, group, 4));
            break;
        case 2:
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            _localPortsPerGroup.push_back(PortGroup(localPort+2, labelPort, group, 2));
            break;
        case 4:
        case 8:
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
            break;
        }
    }
}

bool MlxlinkCommander::isIbLocalPortValid(u_int32_t localPort)
{
    bool valid = true;
    resetParser(ACCESS_REG_PLIB);
    updateField("local_port", localPort);
    try {
        genBuffSendRegister(ACCESS_REG_PLIB, MACCESS_REG_METHOD_GET);
    } catch (MlxRegException& exp) {
        valid = false;
    }
    return valid;
}

void MlxlinkCommander::fillIbPortGroupMap(u_int32_t localPort,u_int32_t labelPort,
        u_int32_t group, bool splitReady)
{
    if (splitReady) {
        labelPort = (labelPort + 1) / 2;
        if (_devID == DeviceQuantum) {
            if (isIbLocalPortValid(localPort+1)) {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort+1, labelPort, group, 2));
            } else {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            }
        } else if (_devID == DeviceQuantum2) {
            labelPort = (labelPort / 2) + 1;
            if (isIbLocalPortValid(localPort+1)) {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort+1, labelPort, group, 1, 2));
            } else {
                _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1, 1));
            }
            if (isIbLocalPortValid(localPort+3)) {
                _localPortsPerGroup.push_back(PortGroup(localPort+2, labelPort, group, 2, 1));
                _localPortsPerGroup.push_back(PortGroup(localPort+3, labelPort, group, 2, 2));
            } else {
                _localPortsPerGroup.push_back(PortGroup(localPort+2, labelPort, group, 2, 1));
            }
        }
    } else {
        if (_devID == DeviceQuantum) {
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
        } else if (_devID == DeviceQuantum2) {
            labelPort = (labelPort / 2) + 1;
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
            _localPortsPerGroup.push_back(PortGroup(localPort+2, labelPort, group, 2));
        }
    }
}

bool MlxlinkCommander::isSpect2WithGb()
{
    string regName = "MGPIR";
    resetParser(regName);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    return getFieldValue("num_of_devices") > 0;
}

vector<string> MlxlinkCommander::localToPortsPerGroup(vector<u_int32_t> localPorts)
{
    u_int32_t labelPort = 0;
    vector<u_int32_t> labelPorts;
    vector<string> labelPortsStr;
    string regName;
    for (vector<u_int32_t>::iterator it = localPorts.begin();
            it != localPorts.end(); ++it) {
        if (_devID == DeviceSpectrum2) {
            regName = "PMLP";
            resetParser(regName);
            updateField("local_port", *it);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            if (getFieldValue("width") == 0) {
                continue;
            }
            labelPort = (getFieldValue("module_0")) + 1;
        } else if (_devID == DeviceQuantum || _devID == DeviceQuantum2) {
            regName = "PLIB";
            resetParser(regName);
            updateField("local_port", *it);
            try {
                genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
                labelPort = getFieldValue("ib_port");
            } catch (MlxRegException &exc) {
                continue;
            }
        }
        labelPorts.push_back(labelPort);
    }
    sort(labelPorts.begin(), labelPorts.end());
    for (vector<u_int32_t>::iterator it = labelPorts.begin();
            it != labelPorts.end(); it++) {
        if (!isIn(to_string(*it), labelPortsStr)) {
            labelPortsStr.push_back(to_string(*it));
        }
    }
    return labelPortsStr;
}

void MlxlinkCommander::handleLabelPorts(std::vector<string> labelPortsStr, bool skipException)
{
    u_int32_t labelPort = 0;
    int localPort = -1;
    if (labelPortsStr.size() > maxLocalPort() && !skipException) {
        throw MlxRegException("The number of ports is invalid");
    }
    bool ibSplitReady = (_devID == DeviceQuantum || _devID == DeviceQuantum2)? isIBSplitReady() : false;
    bool spect2WithGb = (_devID == DeviceSpectrum2)? isSpect2WithGb() : false;
    for (vector<string>::iterator it = labelPortsStr.begin(); it != labelPortsStr.end(); ++it) {
        strToUint32((char *)(*it).c_str(), labelPort);
        if (_devID == DeviceSpectrum2 || _devID == DeviceSpectrum3) {
            localPort = handleEthLocalPort(labelPort, spect2WithGb);
        } else if (_devID == DeviceQuantum || _devID == DeviceQuantum2) {
            localPort = handleIBLocalPort(labelPort, ibSplitReady);
        }
        if (localPort < 0 && !skipException) {
            throw MlxRegException("Invalid port number %d!\n", labelPort);
        }
    }
}

string MlxlinkCommander::getCableTechnologyStr(u_int32_t cableTechnology)
{
    string technologyStr = "N/A";
    if (_cmisCable) {
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[cableTechnology];
    } else if (_qsfpCable){
        technologyStr = _mlxlinkMaps->_cableTechnologyQsfp[(cableTechnology & 240) >> 4];
    } else {
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
    u_int32_t cableVendor = getFieldValue("cable_vendor");
    string complianceStr = getComplianceLabel(
                            getFieldValue("ethernet_compliance_code"),
                            getFieldValue("ext_ethernet_compliance_code"),
                            (cableVendor != NVIDIA && cableVendor != MELLANOX));
    u_int32_t cableLength = getFieldValue("cable_length");

    setPrintVal(_moduleInfoCmd, "Identifier",
            _plugged ? getCableIdentifier(_cableIdentifier) : "N/A",
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Compliance",
            complianceStr, ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Technology",
            _plugged ? getCableTechnologyStr(_cableTechnology) : "N/A",
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Type",
            getCableTypeStr(getFieldValue("cable_type")),
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "OUI",
            _plugged ? getOui(cableVendor) : "N/A", ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Vendor Name",
            getAscii("vendor_name", 16), ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Vendor Part Number",
            getAscii("vendor_pn", 16), ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Vendor Serial Number",
            getAscii("vendor_sn", 16), ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Rev", getVendorRev(getFieldValue("vendor_rev")),
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Wavelength [nm]",
            (_cableMediaType == PASSIVE) ? "N/A" : to_string(getFieldValue("wavelength")),
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Transfer Distance [m]",
            getCableLengthStr(cableLength , _cmisCable), ANSI_COLOR_RESET, true, valid);
}

void MlxlinkCommander::prepareAttenuationAndFwSection(bool valid)
{
    string cableAttenuation = "N/A";
    string attenuationTitle = "Attenuation (5g,7g,12g";
    bool passive = _cableMediaType == PASSIVE;
    if (_cmisCable) {
        attenuationTitle += ",25g";
    }
    attenuationTitle += ") [dB]";
    if (_cableIdentifier != IDENTIFIER_SFP && _cableIdentifier != IDENTIFIER_QSA) {
        if (passive) {
            cableAttenuation = getFieldStr("cable_attenuation_5g") + ","
                    + getFieldStr("cable_attenuation_7g") + ","
                    + getFieldStr("cable_attenuation_12g");
            if (_cmisCable) {
                cableAttenuation += "," + getFieldStr("cable_attenuation_25g");
            }
        }
    }

    setPrintVal(_moduleInfoCmd, attenuationTitle,
            cableAttenuation, ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "FW Version",
            getFwVersion(passive,getFieldValue("fw_version")), ANSI_COLOR_RESET, true, valid);

}

void MlxlinkCommander::preparePowerAndCdrSection(bool valid)
{
    string rxCdrState = "N/A";
    string txCdrState = "N/A";
    if (getFieldValue("rx_cdr_cap") > 0) {
        rxCdrState = getRxTxCDRState(getFieldValue("rx_cdr_state"),_numOfLanes);
    }
    if (getFieldValue("tx_cdr_cap") > 0) {
        txCdrState = getRxTxCDRState(getFieldValue("tx_cdr_state"),_numOfLanes);
    }
    string powerClassStr = getPowerClass(_mlxlinkMaps,_cableIdentifier , getFieldValue("cable_power_class"),
                                    getFieldValue("max_power"));

    setPrintVal(_moduleInfoCmd, "Digital Diagnostic Monitoring",
            _ddmSupported ? "Yes" : "No", ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd,"Power Class",
            (_plugged && _cableMediaType != PASSIVE) ? powerClassStr : "N/A",
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "CDR RX", _plugged ? rxCdrState : "N/A",
            ANSI_COLOR_RESET, true, valid, true);
    setPrintVal(_moduleInfoCmd,"CDR TX", _plugged ? txCdrState : "N/A",
            ANSI_COLOR_RESET, true, valid, true);
    setPrintVal(_moduleInfoCmd, "LOS Alarm", "N/A",
            ANSI_COLOR_RESET, true, valid);
}

void MlxlinkCommander::prepareDDMSection(bool valid)
{
    std::vector<float> rxPowerLane, txPowerLane, biasCurrentLane;

    u_int32_t tempNum = getFieldValue("temperature");
    string temp       = getTemp(tempNum);
    string tempHighTH = getTemp(getFieldValue("temperature_high_th"));
    string tempLowTH  = getTemp(getFieldValue("temperature_low_th"));

    float voltage       = getFieldValue("voltage") / 10.0;
    float voltageHighTH = getFieldValue("voltage_high_th") / 10.0;
    float voltageLowTH  = getFieldValue("voltage_low_th") / 10.0;

    float rxPowerHighTH = getPower(getFieldValue("rx_power_high_th"));
    float rxPowerLowTH  = getPower(getFieldValue("rx_power_low_th"));
    float txPowerHighTH = getPower(getFieldValue("tx_power_high_th"));
    float txPowerLowTH  = getPower(getFieldValue("tx_power_low_th"));
    float biasLowTH = getFieldValue("tx_bias_low_th") / 500.0;
    float biasHighTH = getFieldValue("tx_bias_high_th") / 500.0;

    for (u_int32_t lane = 0; lane < _numOfLanes; lane++) {
        string laneStr = to_string(lane);
        rxPowerLane.push_back(getPower(getFieldValue("rx_power_lane" + laneStr)));
        txPowerLane.push_back(getPower(getFieldValue("tx_power_lane" + laneStr)));
        biasCurrentLane.push_back(getFieldValue("tx_bias_lane" + laneStr) / 500.0);
    }

    setPrintVal(_moduleInfoCmd, "Temperature [C]",
            getValueAndThresholdsStr<string, string>(temp, tempLowTH, tempHighTH),
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Voltage [mV]",
            getValueAndThresholdsStr<float, float>(voltage, voltageLowTH, voltageHighTH),
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Bias Current [mA]",
            getValueAndThresholdsStr<string, float>(
                    getStringFromVector(biasCurrentLane), biasLowTH, biasHighTH),
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Rx Power Current [dBm]",
            getValueAndThresholdsStr<string, float>(
                    getStringFromVector(rxPowerLane), rxPowerLowTH, rxPowerHighTH),
                    ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Tx Power Current [dBm]",
            getValueAndThresholdsStr<string, float>(
                    getStringFromVector(txPowerLane), txPowerLowTH, txPowerHighTH),
                    ANSI_COLOR_RESET, true, valid);
}

string MlxlinkCommander::getValuesOfActiveLanes(const string &row)
{
    string newValue = row;

    auto valuesPerLane = MlxlinkRecord::split(newValue, ",");

    if (valuesPerLane.size() > 1) {
        valuesPerLane.erase(valuesPerLane.begin() + _numOfLanes, valuesPerLane.end());
        newValue = getStringFromVector(valuesPerLane);
    }

    return newValue;
}
void MlxlinkCommander::prepareBerModuleInfoNdr(bool valid)
{
    initAmBerCollector();
    _amberCollector->init();

    vector<AmberField> moduleInfoFields =  _amberCollector->getModuleStatus();

    vector<MODULE_FIELD> fieldsToQuery;

    fieldsToQuery.push_back(MODULE_FIELD{"IB Cable Width", "ib_width",true, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Memory Map Revision", "Memory_map_rev",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Linear Direct Drive", "linear_direct_drive",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Cable Breakout", "cable_breakout",true, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"SMF Length", "smf_length",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"MAX Power", "max_power",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Cable Rx AMP", "cable_rx_amp",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Cable Rx Emphasis", "cable_rx_emphasis",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Cable Rx Post Emphasis", "cable_rx_post_emphasis",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Cable Tx Equalization", "cable_tx_equalization",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Wavelength Tolerance", "wavelength_tolerance",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Module State", "Module_st",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"DataPath state [per lane]", "Dp_st_lane",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Rx Output Valid [per lane]", "rx_output_valid",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Rx Input Valid [per lane]", "rx_input_valid",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Nominal bit rate", "Nominal_Bit_Rate",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Rx Power Type", "Rx_Power_Type",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Manufacturing Date", "Date_code",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Active Set Host Compliance Code", "Active_set_host_compliance_code",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Active Set Media Compliance Code", "Active_set_media_compliance_code",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Error Code Response", "error_code_response",false, false, false});
    fieldsToQuery.push_back(MODULE_FIELD{"Module FW Fault", "Mod_fw_fault",false, false, true});
    fieldsToQuery.push_back(MODULE_FIELD{"DataPath FW Fault", "Dp_fw_fault",false, false, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Tx Fault [per lane]", "tx_fault",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Tx LOS [per lane]", "tx_los",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Tx CDR LOL [per lane]", "tx_cdr_lol",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Rx LOS [per lane]", "rx_los",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Rx CDR LOL [per lane]", "rx_cdr_lol",true, true, true});
    fieldsToQuery.push_back(MODULE_FIELD{"Tx Adaptive EQ Fault [per lane]", "tx_ad_eq_fault",true, true, true});

    string fieldValue = "";
    for (auto it = fieldsToQuery.begin(); it != fieldsToQuery.end(); it++) {
        fieldValue = AmberField::getValueFromFields(moduleInfoFields, it->amberName, !it->perLane);
        if (it->multiVal) {
            findAndReplace(fieldValue, "_", ",");
        }
        if (it->perLane) {
            fieldValue = getValuesOfActiveLanes(fieldValue);
        }

        if (it->uiName == "Cable Rx Emphasis" && _cmisCable) {
            it->uiName += " (Pre)";
        }
        setPrintVal(_moduleInfoCmd, it->uiName, fieldValue, ANSI_COLOR_RESET, true,
                    it->requireDdm? valid && _ddmSupported : valid, it->perLane);
    }
}

void MlxlinkCommander::showModuleInfo()
{
    try {
        gearboxBlock(MODULE_INFO_FLAG);

        string regName = "PMAOS";
        resetParser(regName);
        updateField("module", _moduleNumber);
        updateField("slot_index", _slotIndex);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        u_int32_t oper_status = getFieldValue("oper_status");

        regName = "PDDR";
        resetParser(regName);
        updatePortType();

        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_MODULE_INFO_PAGE);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        setPrintTitle(_moduleInfoCmd,"Module Info",
                      _productTechnology >= PRODUCT_16NM ? MODULE_INFO_AMBER : MODULE_INFO_LAST);
        bool valid = (_cableMediaType != UNIDENTIFIED) && _plugged;

        prepareStaticInfoSection(valid);
        prepareAttenuationAndFwSection(valid);
        preparePowerAndCdrSection(valid);
        prepareDDMSection(valid);
        if (_productTechnology >= PRODUCT_16NM) {
            prepareBerModuleInfoNdr(valid);
        }
        cout << _moduleInfoCmd;

        if (oper_status != 1) {
            MlxlinkRecord::printWar("Warning: Cannot get module EEPROM information, module operation status is not 'plugged and enabled'", _jsonRoot);
        }
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing Module Info via PDDR raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::getCompliaceLabelForCIMIS(u_int32_t hostCompliance,
        u_int32_t mediaCompliance)
{
    string complianceStr = "N/A";
    string hostComplianceStr = "";
    string mediaComplianceStr = "";
    switch (_cableMediaType) {
    case PASSIVE:
        hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
        break;
    case ACTIVE:
        mediaComplianceStr = _mlxlinkMaps->_activeCableCompliance[mediaCompliance];
        hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
        break;
    case OPTICAL_MODULE:
        if (_cableTechnology == TECHNOLOGY_850NM_VCSEL) {
            mediaComplianceStr = _mlxlinkMaps->_mmfCompliance[mediaCompliance];
        } else if(_cableTechnology >= TECHNOLOGY_1310NM_VCSEL &&
                _cableTechnology <= TECHNOLOGY_1550NM_EML) {
            mediaComplianceStr = _mlxlinkMaps->_smfCompliance[mediaCompliance];
        }
        hostComplianceStr = _mlxlinkMaps->_cmisHostCompliance[hostCompliance];
        break;
    }
    complianceStr = hostComplianceStr;
    if (!mediaComplianceStr.empty()) {
        complianceStr += "," + mediaComplianceStr;
    }
    return complianceStr;
}

string MlxlinkCommander::getComplianceLabel(u_int32_t compliance,
        u_int32_t extCompliance, bool ignoreExtBitChk)
{
    string complianceLabel = "N/A";
    if (_cmisCable) {
        complianceLabel = getCompliaceLabelForCIMIS(extCompliance,compliance);
    } else if (_protoActive == ETH) {
        if (_qsfpCable) {
            if (compliance) {
                complianceLabel =
                        getCompliance(compliance, _mlxlinkMaps->_cableComplianceQsfp, true);
                if (ignoreExtBitChk ||
                        (compliance & QSFP_ETHERNET_COMPLIANCE_CODE_EXT)) {
                    complianceLabel += !complianceLabel.empty() ? "," : "";
                    complianceLabel += getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
                }
            } else if (ignoreExtBitChk) {
                complianceLabel =
                        getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
            }
        } else if (_cableIdentifier == IDENTIFIER_SFP || _cableIdentifier == IDENTIFIER_QSA) {
            if (compliance) {
                complianceLabel = getCompliance(compliance, _mlxlinkMaps->_cableComplianceSfp, true);
            }
            if(extCompliance) {
                complianceLabel = (compliance? complianceLabel + ", ":"") +
                        getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
            }
        }
    }
    return complianceLabel;
}

void MlxlinkCommander::prepareSltp28_40nm(std::vector<std::vector<string> > &sltpLanes,
        u_int32_t laneNumber)
{
    sltpLanes[laneNumber].push_back(getFieldStr("polarity"));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_tap0"));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_tap1"));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_tap2"));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_bias"));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_preemp_mode"));
    if (_userInput._advancedMode) {
        sltpLanes[laneNumber].push_back(getFieldStr("ob_reg"));
        sltpLanes[laneNumber].push_back(getFieldStr("ob_leva"));
    }
}

void MlxlinkCommander::prepareSltp16nm(std::vector<std::vector<string> > &sltpLanes,
        u_int32_t laneNumber)
{
    // The first four fields are stored as a signed integers
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("pre_2_tap"))));
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("pre_tap"))));
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("main_tap"))));
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("post_tap"))));
    sltpLanes[laneNumber].push_back(to_string(readSigned(getFieldValue("ob_m2lp"), getFieldSize("ob_m2lp"))));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_amp"));
}

void MlxlinkCommander::prepareSltp7nm(std::vector<std::vector<string> > &sltpLanes,
        u_int32_t laneNumber)
{
    if (isSpeed100GPerLane(_protoActive == IB? _activeSpeed : _activeSpeedEx,
                           _protoActive)) {
        sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_pre3"))));
        sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_pre2"))));
    } else if (isSpeed50GPerLane(_protoActive == IB? _activeSpeed : _activeSpeedEx,
                           _protoActive)) {
        sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_pre2"))));
    }
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_pre1"))));
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_main"))));
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("fir_post1"))));
}

template<typename T, typename Q>
string MlxlinkCommander::getValueAndThresholdsStr(T value, Q lowTH, Q highTH)
{
    stringstream out;
    if (_ddmSupported) {
        out << value << " [" << lowTH << ".." << highTH << "]";
    } else {
        out << "N/A";
    }
    return out.str();
}

void MlxlinkCommander::strToInt32(char *str, u_int32_t &value)
{
    char *endp;
    value = strtol(str, &endp, 0);
    if (*endp) {
        throw MlxRegException("Argument: %s is invalid.", str);
    }
}

void MlxlinkCommander::runningVersion()
{
    setPrintTitle(_toolInfoCmd,"Tool Information", TOOL_INFORMAITON_INFO_LAST, !_prbsTestMode);
    setPrintVal(_toolInfoCmd,"Firmware Version", _fwVersion, ANSI_COLOR_GREEN,true, !_prbsTestMode);
    setPrintVal(_toolInfoCmd,"amBER Version", AMBER_VERSION, ANSI_COLOR_GREEN,
                _productTechnology >= PRODUCT_16NM, !_prbsTestMode);
    setPrintVal(_toolInfoCmd, PKG_NAME " Version", PKG_VER, ANSI_COLOR_GREEN,true, !_prbsTestMode);
}

void MlxlinkCommander::operatingInfoPage()
{
    try {
        string regName = "PDDR";
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        _protoActive = getFieldValue("proto_active");
        _fecActive = getFieldValue("fec_mode_active");
        u_int32_t phyMngrFsmState = getFieldValue("phy_mngr_fsm_state");
        int loopbackMode = (phyMngrFsmState != PHY_MNGR_DISABLED) ? getFieldValue("loopback_mode") : -1;
        _linkUP = (phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP);
        _portPolling = phyMngrFsmState == PHY_MNGR_POLLING;
        _protoCapability = getFieldValue("cable_ext_eth_proto_cap");
        if(_protoActive == IB) {
            _protoCapability = getFieldValue("cable_link_speed_cap");
            _activeSpeed = getFieldValue("link_speed_active");
            _protoAdmin = (phyMngrFsmState != 0) ?
                        getFieldValue("core_to_phy_link_proto_enabled") :
                        getFieldValue("phy_manager_link_proto_enabled");
        }
        getPtys();
        bool extended = _activeSpeedEx && _protoAdminEx;
        _isPam4Speed = isPAM4Speed(_protoActive == IB?_activeSpeed:_activeSpeedEx,
                                   _protoActive, extended);
        _linkSpeed = extended? _activeSpeedEx:_activeSpeed;
        getActualNumOfLanes(_linkSpeed, extended);

        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_OPERATIONAL_INFO_PAGE);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        setPrintTitle(_operatingInfoCmd,"Operational Info",
                PDDR_OPERATIONAL_INFO_LAST,!_prbsTestMode);

        _speedBerCsv = activeSpeed2gNum(_linkSpeed, extended);
        _speedStrG = activeSpeed2Str(_linkSpeed, extended);
        string color = MlxlinkRecord::state2Color(phyMngrFsmState == PHY_MNGR_RX_DISABLE ? YELLOW
                                                                                         : (STATUS_COLOR) phyMngrFsmState);
        setPrintVal(_operatingInfoCmd,"State",
                _mlxlinkMaps->_pmFsmState[phyMngrFsmState], color,true, !_prbsTestMode);
        string physical_state =
                _mlxlinkMaps->_ethANFsmState[getFieldValue("eth_an_fsm_state")];
        setPrintVal(_operatingInfoCmd, "Physical state",
                physical_state, color, !_prbsTestMode);
        setPrintVal(_operatingInfoCmd, "Speed", _speedStrG, color,
                !_prbsTestMode,_linkUP);
        setPrintVal(_operatingInfoCmd, "Width",
                to_string(_numOfLanes) + "x", color, !_prbsTestMode, _linkUP);

        u_int32_t fec_mode = getFieldValue("fec_mode_active");
        string fec_mode_str = _mlxlinkMaps->_fecModeActive[fec_mode];
        setPrintVal(_operatingInfoCmd, "FEC",
                fec_mode_str == "" ? "N/A" : fec_mode_str,
                fec_mode_str == "" ? MlxlinkRecord::state2Color(0) : color, !_prbsTestMode, _linkUP);

        setPrintVal(_operatingInfoCmd, "Loopback Mode",
                _mlxlinkMaps->_loopbackModeList[loopbackMode],
                getLoopbackColor(loopbackMode), true, !_prbsTestMode && loopbackMode != -1);
        setPrintVal(_operatingInfoCmd, "Auto Negotiation",
                _mlxlinkMaps->_anDisableList[_anDisable] + _speedForce,
                getAnDisableColor(_anDisable), true, !_prbsTestMode);
        // Checking cable DDM capability
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_MODULE_INFO_PAGE);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        _ddmSupported = getFieldValue("temperature") && _numOfLanes ;

    } catch (const std::exception &exc) {
        throw MlxRegException(string(exc.what()));
    }
}

void MlxlinkCommander::supportedInfoPage()
{
    try {
        setPrintTitle(_supportedInfoCmd, HEADER_SUPPORTED_INFO,
                PDDR_SUPPORTED_INFO_LAST, !_prbsTestMode);
        u_int32_t speeds_mask = _protoAdminEx ? _protoAdminEx: _protoAdmin;
        string supported_speeds = SupportedSpeeds2Str(_protoActive, speeds_mask,
                (bool)_protoAdminEx);
        string color = MlxlinkRecord::supported2Color(supported_speeds);
        stringstream value;
        value << "0x" << std::hex << setfill('0') << setw(8) << speeds_mask \
                << " (" << supported_speeds << ")" << setfill(' ');
        string extStr = "";
        if (_protoCapabilityEx && _protoActive == ETH) {
            extStr = " (Ext.)";
        }
        string title = "Enabled Link Speed" + extStr;
        setPrintVal(_supportedInfoCmd, title, value.str(),color, true, !_prbsTestMode, true);
        // Supported cable speed
        supported_speeds = SupportedSpeeds2Str(_protoActive, _protoCapability, _protoCapabilityEx);
        color = MlxlinkRecord::supported2Color(supported_speeds);
        value.str("");
        value.clear();
        value << "0x" << std::hex << setfill('0') << setw(8) << _protoCapability \
                << " (" << supported_speeds << ")" << setfill(' ');
        title = "Supported Cable Speed" + extStr;
        setPrintVal(_supportedInfoCmd, title,
                value.str(),color, true, !_prbsTestMode, true);
    } catch (const std::exception &exc) {
        throw MlxRegException(string(exc.what()));
    }
}

void MlxlinkCommander::troubInfoPage()
{
    try {
        string regName = "PDDR";
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("page_select", PDDR_TROUBLESHOOTING_INFO_PAGE);
        updateField("group_opcode", ADVANCED_OPCODE);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        u_int32_t advancedOpcode = getFieldValue("advanced_opcode");
        string color = status2Color(advancedOpcode);
        setPrintTitle(_troubInfoCmd,"Troubleshooting Info",
                PDDR_TRUOBLESHOOTING_INFO_LAST, !_prbsTestMode);

        if (advancedOpcode == CABLE_IS_UNPLUGGED) {
            _mngCableUnplugged = true;
        }
        stringstream statusOp;
        statusOp << std::dec << advancedOpcode;
        setPrintVal(_troubInfoCmd, "Status Opcode",
                statusOp.str(),color, true, !_prbsTestMode);

        string groupOpcode = getGroupStr(advancedOpcode);
        setPrintVal(_troubInfoCmd, "Group Opcode",
                groupOpcode,color, true, !_prbsTestMode);

        string message = "";
        char txt[16], c;
        u_int32_t message_buf;
        bool finalize = false;

        for (int i = 0; i < PDDR_STATUS_MESSAGE_LENGTH_SWITCH; i++) {
            string path = "status_message[";
            sprintf(txt, "%d", i);
            path.append(txt);
            path.append("]");
            message_buf = getFieldValue(path);
            for (int k = 24; k > -1; k -= 8) {
                c = (char)(message_buf >> k);
                if (c == '\0') {
                    finalize = true;
                    break;
                }
                message.push_back(c);
            }
            if (finalize == true) {
                break;
            }
        }
        setPrintVal(_troubInfoCmd, "Recommendation",
                message,color, true, !_prbsTestMode);
    } catch (const std::exception &exc) {
        throw MlxRegException(string(exc.what()));
    }
}

void MlxlinkCommander::showPddr()
{
    try {
        operatingInfoPage();
        supportedInfoPage();
        troubInfoPage();
        runningVersion();
        if (_prbsTestMode) {
            showTestMode();
        } else {
            std::cout << _operatingInfoCmd;
            std::cout << _supportedInfoCmd;
            std::cout << _troubInfoCmd;
            std::cout << _toolInfoCmd;
        }
    } catch (const std::exception &exc) {
        throw MlxRegException(string("Showing PDDR raised the following exception: \n") + string(exc.what()));
    }
}

void MlxlinkCommander::getPtys()
{
    string regName = "PTYS";
    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("proto_mask", _protoActive);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    if(_protoActive == ETH) {
        _activeSpeedEx = getFieldValue("ext_eth_proto_oper");
        _activeSpeed = getFieldValue("eth_proto_oper");
        _protoAdmin = getFieldValue("eth_proto_admin");
        _protoAdminEx = getFieldValue("ext_eth_proto_admin");
        _protoCapabilityEx = getFieldValue("ext_eth_proto_capability");
        _deviceCapability =  _protoCapabilityEx ? getFieldValue("ext_eth_proto_capability")
                                                : getFieldValue("eth_proto_capability");
    } else {
        _deviceCapability = getFieldValue("ib_proto_capability");
    }

    _anDisable = getFieldValue("an_disable_admin");
    if (_anDisable) {
        u_int32_t val = _protoAdminEx ? _protoAdminEx : _protoAdmin;
        _speedForce = " - " + SupportedSpeeds2Str(_protoActive, val,
                (bool)_protoAdminEx);
    }
}

void MlxlinkCommander::showTestMode()
{
    std::map<std::string, std::string> pprtMap = getPprt();
    std::map<std::string, std::string> ppttMap = getPptt();

    setPrintTitle(_testModeInfoCmd,"Test Mode Info", TEST_MODE_INFO_LAST);
    setPrintVal(_testModeInfoCmd, "RX PRBS Mode", pprtMap["pprtPrbsMode"]);
    setPrintVal(_testModeInfoCmd, "TX PRBS Mode", ppttMap["ppttPrbsMode"]);
    setPrintVal(_testModeInfoCmd, "RX Lane Rate", pprtMap["pprtLaneRate"]);
    setPrintVal(_testModeInfoCmd, "TX Lane Rate", ppttMap["ppttLaneRate"]);
    setPrintVal(_testModeInfoCmd, "Tuning Status", pprtMap["pprtTuningStatus"]);
    setPrintVal(_testModeInfoCmd, "Lock Status", pprtMap["pprtLockStatus"]);

    cout << _testModeInfoCmd;
}

int MlxlinkCommander::prbsModeToMask(const string &mode)
{
    // SQUARE_WAVE and SQUARE_WAVEA have the same enum
    string modeToCheck = mode;
    if (mode == "SQUARE_WAVE") {
        modeToCheck += "A";
    }
    int mask = PRBS31;
    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
            it !=  _mlxlinkMaps->_prbsModesList.end(); it++) {
        if (modeToCheck == it->second) {
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
    if (modeSelector == PRBS_RX && mask == SQUARE_WAVEA) {
        val = deleteLastChar(val); // return SQUARE_WAVE without A
    }
    return val;
}

std::map<std::string, std::string> MlxlinkCommander::getPprt()
{
    string regName = "PPRT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("e", PPRT_PPTT_ENABLE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    std::map<string, string> pprtMap;
    pprtMap["pprtPrbsMode"] = prbsMaskToMode(
        getFieldValue("prbs_mode_admin"), PRBS_RX);
    pprtMap["pprtLaneRate"] = prbsMaskToLaneRate(
        getFieldValue("lane_rate_oper"));
    pprtMap["pprtTuningStatus"] = prbsMaskToTuningStatus(
        getFieldValue("prbs_rx_tuning_status"));
    bool pcie = _userInput._pcie;
    u_int32_t numOfLanesToUse = (pcie) ? _numOfLanesPcie : _numOfLanes;
    u_int32_t statusMask = getFieldValue("prbs_lock_status");
    statusMask |= (getFieldValue("prbs_lock_status_ext") << 4);
    pprtMap["pprtLockStatus"] = prbsMaskToLockStatus(statusMask, numOfLanesToUse);
    return pprtMap;
}

std::map<std::string, std::string> MlxlinkCommander::getPptt()
{
    string regName = "PPTT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("e", PPRT_PPTT_ENABLE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    std::map<string, string> ppttMap;
    ppttMap["ppttPrbsMode"] = prbsMaskToMode(
        getFieldValue("prbs_mode_admin"), PRBS_TX);
    ppttMap["ppttLaneRate"] = prbsMaskToLaneRate(
        getFieldValue("lane_rate_admin"));

    return ppttMap;
}

void MlxlinkCommander::showMpcntTimers(DPN& dpn)
{
    string regName = "MPCNT";
    resetParser(regName);
    updateField("depth",dpn.depth);
    updateField("pcie_index", dpn.pcieIndex);
    updateField("node", dpn.node);
    updateField("grp", MPCNT_TIMERS_GROUPS);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    setPrintTitle(_mpcntTimerInfCmd, "Management PCIe Timers Counters Info",
            MPCNT_TIMER_INFO_LAST);
    setPrintVal(_mpcntTimerInfCmd, "dl down", getFieldStr("dl_down"));

    cout << _mpcntTimerInfCmd;
}

void MlxlinkCommander::prepareBerInfo()
{
    initAmBerCollector();
    _amberCollector->init();

    _ppcntFields = _amberCollector->getLinkStatus();

    setPrintVal(_berInfoCmd, "Time Since Last Clear [Min]",
                AmberField::getValueFromFields(_ppcntFields, "Time_since_last_clear_[Min]"),
                ANSI_COLOR_RESET, true, _linkUP);
    if (_protoActive == IB) {
        setPrintVal(_berInfoCmd, "Symbol Errors",
                    AmberField::getValueFromFields(_ppcntFields, "Symbol_Errors"),
                    ANSI_COLOR_RESET, true, _linkUP);
        setPrintVal(_berInfoCmd, "Symbol BER",
                    AmberField::getValueFromFields(_ppcntFields, "Symbol_BER"),
                    ANSI_COLOR_RESET, true, _linkUP);
    }
    setPrintVal(_berInfoCmd, "Effective Physical Errors",
                AmberField::getValueFromFields(_ppcntFields, "Effective_Errors"),
                ANSI_COLOR_RESET, true, _linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical BER",
                AmberField::getValueFromFields(_ppcntFields, "Effective_BER"),
                ANSI_COLOR_RESET, true, _linkUP);

    string phyRawErr = AmberField::getValueFromFields(_ppcntFields, "Raw_Errors_Lane", false);
    findAndReplace(phyRawErr, "_", ",");
    phyRawErr = getValuesOfActiveLanes(phyRawErr);

    setPrintVal(_berInfoCmd, "Raw Physical Errors Per Lane", phyRawErr, ANSI_COLOR_RESET, true, _linkUP, true);

}

void MlxlinkCommander::prepareBerInfoEDR()
{
    string regName = "PPCNT";
    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_STATISTICAL_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    char buff[64];
    float val = (float)add32BitTo64(
            getFieldValue("time_since_last_clear_high"),
            getFieldValue("time_since_last_clear_low"))/60000.0;
    sprintf(buff, "%.01f", val);
    setPrintVal(_berInfoCmd, "Time Since Last Clear [Min]", buff,
            ANSI_COLOR_RESET,true,_linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical Errors",
            to_string(add32BitTo64(
                    getFieldValue("phy_symbol_errors_high"),
                    getFieldValue("phy_symbol_errors_low"))),
            ANSI_COLOR_RESET,true,_linkUP);

    std::vector<string> rawErrorsPerLane;
    string phy_raw_err = "";
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++) {
        string laneStr = to_string(lane);
        phy_raw_err = to_string(add32BitTo64(
                getFieldValue("phy_raw_errors_lane" + laneStr + "_high"),
                getFieldValue("phy_raw_errors_lane" + laneStr + "_low")));
        rawErrorsPerLane.push_back(phy_raw_err);
    }
    setPrintVal(_berInfoCmd, "Raw Physical Errors Per Lane",
            getStringFromVector(rawErrorsPerLane), ANSI_COLOR_RESET,true,_linkUP);
    setPrintVal(_berInfoCmd, "Effective Physical BER",
            getFieldStr("effective_ber_coef") + "E-" + getFieldStr("effective_ber_magnitude"),
            ANSI_COLOR_RESET,true,_linkUP);
    setPrintVal(_berInfoCmd, "Raw Physical BER",
            getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude"),
            ANSI_COLOR_RESET,true,_linkUP);
}

void MlxlinkCommander::showBer()
{
    if (_userInput._pcie) {
        checkPCIeValidity();
        showMpcntTimers(_dpn);
    }
    try {
        if (_prbsTestMode) {
            showTestModeBer();
            return;
        }
        if (_userInput._pcie) {
            showMpcntPerformance(_dpn);
            return;
        }
        setPrintTitle(_berInfoCmd,"Physical Counters and BER Info",
                      _productTechnology >= PRODUCT_16NM? BER_INFO_NDR_LAST : BER_INFO_LAST);

        if (_productTechnology < PRODUCT_16NM) {
            prepareBerInfoEDR();
        } else {
            prepareBerInfo();
            setPrintVal(_berInfoCmd, "Raw Physical BER", AmberField::getValueFromFields(_ppcntFields, "Raw_BER"),
                        ANSI_COLOR_RESET, true, _linkUP);
        }

        if (_protoActive == IB) {
            string regName = "PPCNT";
            resetParser(regName);
            updatePortType();
            updateField("local_port", _localPort);
            updateField("swid", SWID);
            updateField("pnat", PNAT_LOCAL);
            updateField("grp", PPCNT_IB_PORT_COUNTERS_GROUP);
            updateField("clr", 0);
            updateField("prio_tc", 0);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            setPrintVal(_berInfoCmd, "Link Down Counter", getFieldStr("link_downed_counter"),
                        ANSI_COLOR_RESET,true,_linkUP);
            setPrintVal(_berInfoCmd, "Link Error Recovery Counter", getFieldStr("link_error_recovery_counter"),
                        ANSI_COLOR_RESET,true,_linkUP);
        }

        cout << _berInfoCmd;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing BER via PPCNT raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showTestModeBer()
{
    string regName = "PPCNT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_STATISTICAL_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    std::vector<string> errors;
    for (u_int32_t lane = 0; lane < _numOfLanes; lane++) {
        errors.push_back(to_string(add32BitTo64(
                getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_high"),
                getFieldValue("phy_raw_errors_lane" + to_string(lane) + "_low"))));
    }

    char buff[64];
    float val = (float)add32BitTo64(
            getFieldValue("time_since_last_clear_high"),
            getFieldValue("time_since_last_clear_low"))/60000.0;
    sprintf(buff, "%.01f", val);

    setPrintTitle(_testModeBerInfoCmd, "Physical Counters and BER Info (PRBS)",
            TEST_MODE_BER_INFO_LAST);
    setPrintVal(_testModeBerInfoCmd, "Time Since Last Clear [Min]",buff);
    setPrintVal(_testModeBerInfoCmd, "PRBS Errors", getStringFromVector(errors));
    setPrintVal(_testModeBerInfoCmd, "PRBS BER",
            getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude"));

    cout <<_testModeBerInfoCmd;
}

void MlxlinkCommander::getPcieNdrCounters()
{
    if (_productTechnology >= PRODUCT_16NM) {
        string berStr = to_string(getFieldValue("effective_ber_coef")) + "E-" +
                        to_string(getFieldValue("effective_ber_magnitude"));
        setPrintVal(_mpcntPerfInfCmd, "Effective ber", berStr);
    }
}

void MlxlinkCommander::showMpcntPerformance(DPN& dpn)
{
    string regName = "MPCNT";
    resetParser(regName);

    updateField("depth",dpn.depth);
    updateField("pcie_index", dpn.pcieIndex);
    updateField("node", dpn.node);
    updateField("grp", MPCNT_PERFORMANCE_GROUP);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    setPrintTitle(_mpcntPerfInfCmd, "Management PCIe Performance Counters Info",
            MPCNT_PERFORMANCE_INFO_LAST + 2);
    setPrintVal(_mpcntPerfInfCmd, "RX Errors",getFieldStr("rx_errors"));
    setPrintVal(_mpcntPerfInfCmd, "TX Errors",getFieldStr("tx_errors"));
    setPrintVal(_mpcntPerfInfCmd, "CRC Error dllp",getFieldStr("crc_error_dllp"));
    setPrintVal(_mpcntPerfInfCmd, "CRC Error tlp",getFieldStr("crc_error_tlp"));

    getPcieNdrCounters();

    cout << _mpcntPerfInfCmd;
}

void MlxlinkCommander::checkPCIeValidity()
{
    if (!_userInput._sendDpn) {
        if (_validDpns.size() == 0) {
            throw MlxRegException("No valid depth, node and pcie_index detected!");
        } else if (_validDpns.size() == 1){
            _dpn = _validDpns[0];
            _localPort = getLocalPortFromMPIR(_dpn);
        } else if (_validDpns.size() > 1 && !_userInput._portSpecified){
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
    string regName = "SLRG";
    bool validPhaseHeight = _productTechnology == PRODUCT_40NM ||
                            _productTechnology == PRODUCT_28NM ||
                            _productTechnology == PRODUCT_16NM ||
                            _userInput._pcie;
    string height_eo_pos("height_eo_pos");
    string height_eo_neg("height_eo_neg");
    string phase_eo_pos("phase_eo_pos");
    string phase_eo_neg("phase_eo_neg");
    if (_productTechnology == PRODUCT_16NM) {
        height_eo_pos.append("_mid");
        height_eo_neg.append("_mid");
        phase_eo_pos.append("_mid");
        phase_eo_neg.append("_mid");
    }
    for (u_int32_t i = 0; i < numOfLanes; i++) {
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", (_userInput._pcie) ? PNAT_PCIE : PNAT_LOCAL);
        updateField("lane", i);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        physicalGrades.push_back(MlxlinkRecord::addSpaceForSlrg(
                to_string(getFieldValue("grade"))));
        if (validPhaseHeight) {
            int offsetEOPos = getHeight(getFieldValue(height_eo_pos));
            int offsetEONeg = getHeight(getFieldValue(height_eo_neg));
            if(_productTechnology == PRODUCT_16NM && (offsetEOPos + offsetEONeg) == 0){
                offsetEONegStr = "N/A";
            }else{
                offsetEONegStr = to_string(offsetEOPos + offsetEONeg);
            }
            int phaseEOPos = getPhase(getFieldValue(phase_eo_pos));
            int phaseEONeg = getPhase(getFieldValue(phase_eo_neg));
            if(_productTechnology == PRODUCT_16NM && (phaseEOPos + phaseEONeg) == 0){
                phaseEONegStr = "N/A";
            }else{
                phaseEONegStr = to_string(phaseEOPos + phaseEONeg);
            }
        }
        heightLengths.push_back(MlxlinkRecord::addSpaceForSlrg(offsetEONegStr));
        phaseWidths.push_back(MlxlinkRecord::addSpaceForSlrg(phaseEONegStr));
    }

    setPrintVal(_eyeOpeningInfoCmd, "Physical Grade",
            getStringFromVector(physicalGrades), ANSI_COLOR_RESET, true,true, true);
    setPrintVal(_eyeOpeningInfoCmd, "Height Eye Opening [mV]",
            getStringFromVector(heightLengths), ANSI_COLOR_RESET, true,true, true);
    setPrintVal(_eyeOpeningInfoCmd, "Phase  Eye Opening [psec]",
            getStringFromVector(phaseWidths), ANSI_COLOR_RESET, true, true, true);
}

void MlxlinkCommander::prepare7nmEyeInfo(u_int32_t numOfLanesToUse)
{
    string regName = "SLRG";
    std::vector<string> legand, initialFom, lastFom, upperFom, midFom, lowerFom;

    u_int32_t fomMeasurement = SLRG_COMPOSITE_EYE;
    if (!isSpeed25GPerLane(_activeSpeed, _protoActive)) {
        fomMeasurement |= (SLRG_UPPER_EYE | SLRG_MIDDLE_EYE | SLRG_LOWER_EYE);
    }

    for (u_int32_t lane = 0; lane < numOfLanesToUse; lane++) {
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", (_userInput._pcie) ? PNAT_PCIE : PNAT_LOCAL);
        updateField("lane", lane);
        updateField("fom_measurment", fomMeasurement);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        initialFom.push_back(MlxlinkRecord::addSpaceForSlrg(
               getFieldValue("status")? to_string(getFieldValue("initial_fom")) : "N/A"));
        lastFom.push_back(MlxlinkRecord::addSpaceForSlrg(
               (fomMeasurement & SLRG_COMPOSITE_EYE)? getFieldStr("last_fom") : "N/A"));
        upperFom.push_back(MlxlinkRecord::addSpaceForSlrg(
               (fomMeasurement & SLRG_UPPER_EYE)? getFieldStr("upper_eye") : "N/A"));
        midFom.push_back(MlxlinkRecord::addSpaceForSlrg(
               (fomMeasurement & SLRG_MIDDLE_EYE)? getFieldStr("mid_eye") : "N/A"));
        lowerFom.push_back(MlxlinkRecord::addSpaceForSlrg(
               (fomMeasurement & SLRG_LOWER_EYE)? getFieldStr("lower_eye") : "N/A"));
        legand.push_back(MlxlinkRecord::addSpaceForSlrg(to_string(lane)));
    }

    string fomMode = _mlxlinkMaps->_slrgFomMode[getFieldValue("fom_mode")];
    setPrintVal(_eyeOpeningInfoCmd, "FOM Mode", fomMode,
                ANSI_COLOR_RESET, !fomMode.empty(), true, true);
    setPrintVal(_eyeOpeningInfoCmd, "Lane", getStringFromVector(legand),
                    ANSI_COLOR_RESET, !legand.empty(), true, true);
    setPrintVal(_eyeOpeningInfoCmd, "Initial FOM", getStringFromVector(initialFom),
                ANSI_COLOR_RESET, !initialFom.empty(), true, true);
    setPrintVal(_eyeOpeningInfoCmd, "Last FOM", getStringFromVector(lastFom),
                ANSI_COLOR_RESET, !lastFom.empty(), (fomMeasurement & SLRG_COMPOSITE_EYE), true);
    setPrintVal(_eyeOpeningInfoCmd, "Upper Grades", getStringFromVector(upperFom),
                ANSI_COLOR_RESET, !upperFom.empty(), (fomMeasurement & SLRG_UPPER_EYE), true);
    setPrintVal(_eyeOpeningInfoCmd, "Mid Grades", getStringFromVector(midFom),
                ANSI_COLOR_RESET, !midFom.empty(), (fomMeasurement & SLRG_MIDDLE_EYE), true);
    setPrintVal(_eyeOpeningInfoCmd, "Lower Grades", getStringFromVector(lowerFom),
                ANSI_COLOR_RESET, !lowerFom.empty(), (fomMeasurement & SLRG_LOWER_EYE), true);
}

void MlxlinkCommander::showEye()
{
    if (_userInput._pcie){
        checkPCIeValidity();
    }
    try {
        u_int32_t numOfLanesToUse = (_userInput._pcie) ? _numOfLanesPcie : _numOfLanes;
        string showEyeTitle = "EYE Opening Info";
        if (_userInput._pcie) {
            showEyeTitle += " (PCIe)";
        }
        setPrintTitle(_eyeOpeningInfoCmd, showEyeTitle, EYE_OPENING_INFO_LAST);
        if (_productTechnology == PRODUCT_16NM ||
                _productTechnology == PRODUCT_28NM ||
                _productTechnology == PRODUCT_40NM) {
            prepare40_28_16nmEyeInfo(numOfLanesToUse);
        } else if (_productTechnology == PRODUCT_7NM) {
            prepare7nmEyeInfo(numOfLanesToUse);
        }
        cout << _eyeOpeningInfoCmd;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing Eye via SLRG raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::fecMaskToUserInputStr(u_int32_t fecCapMask)
{
    u_int32_t mask = 0;
    string validFecStr = "";
    string shortFec = "";
    for (double bitIdx = 0; bitIdx < 16; bitIdx++) {
        mask = (u_int32_t)pow(2.0, bitIdx);
        if (fecCapMask & mask) {
            if (_mlxlinkMaps->_fecModeMask.count(mask)) {
                shortFec = _mlxlinkMaps->_fecModeMask[mask].second;
                if (shortFec.find("PLR") != string::npos) {
                    continue;
                }
                if (shortFec.find("-544") != string::npos || shortFec.find("-272") != string::npos) {
                    shortFec = shortFec.substr(0, 2);
                }
                validFecStr += shortFec + "(" + _mlxlinkMaps->_fecModeMask[mask].first + ")/";
            }
        }
    }
    string auFec =  _mlxlinkMaps->_fecModeMask[0].second + "(" +  _mlxlinkMaps->_fecModeMask[0].first + ")";
    validFecStr = validFecStr.empty()? "" : (auFec + "/" + deleteLastChar(validFecStr));
    return validFecStr;
}

string MlxlinkCommander::getSupportedFecForSpeed(const string &speed)
{
    string fecCap = "0x0 (N/A)";
    string protoStr = _protoActive == IB? "ib_" : "";
    if (!_prbsTestMode) {
        string speedToCheck = speed;
        speedToCheck =  toLowerCase(speedToCheck);
        if (speedToCheck == "10g" || speedToCheck == "40g") {
            speedToCheck = "10g_40g";
        }
        if (speedToCheck == "50g_2x") {
            speedToCheck = "50g";
        }
        if (speedToCheck == "100g_4x") {
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

    if (mask) {
        fecStr += getStrByMaskFromPair(mask, _mlxlinkMaps->_fecModeMask, ", ");
    } else {
        fecStr = "0x0 (N/A";
    }
    fecStr += ")";

    return fecStr;
}

void MlxlinkCommander::showFEC()
{
    try {
        resetParser(ACCESS_REG_PPLM);
        updateField("local_port", _localPort);
        genBuffSendRegister(ACCESS_REG_PPLM, MACCESS_REG_METHOD_GET);

        string supportedSpeedsStr = SupportedSpeeds2Str(_protoActive, _deviceCapability, _protoCapabilityEx);
        vector<string> supportedSpeeds = MlxlinkRecord::split(supportedSpeedsStr, ",");

        for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++) {
            if (isIn((*it).first, supportedSpeeds)) {
                it->second = getSupportedFecForSpeed((*it).first);
            }
        }

        setPrintTitle(_fecCapInfoCmd, HEADER_FEC_INFO, supportedSpeeds.size() + 1);

        bool noFecDetected = true;
        string bitEthIndecator = "bE";
        for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++) {
            if (!(*it).second.empty()) {
                noFecDetected = false;
            }
            if (isIn((*it).first, supportedSpeeds)) {
                setPrintVal(_fecCapInfoCmd, "FEC Capability " + (*it).first +
                                            ((_productTechnology < PRODUCT_16NM &&
                                              _protoActive == ETH) ? bitEthIndecator : ""), (*it).second,
                            ANSI_COLOR_RESET, true, true, true);
            }
        }
        if (noFecDetected) {
            MlxlinkRecord::printWar("FEC information is not available for InfiniBand protocol", _jsonRoot);
        } else {
            cout << _fecCapInfoCmd;
        }
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing FEC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showSltp()
{
    if (_userInput._pcie){
        checkPCIeValidity();
    }
    try {
        string regName = "SLTP";

        bool valid = true;
        u_int32_t numOfLanesToUse =
            (_userInput._pcie) ? _numOfLanesPcie : _numOfLanes;
        std::vector<std::vector<string> > sltpLanes(numOfLanesToUse,
                                                    std::vector<string>());
        string showSltpTitle = "Serdes Tuning Transmitter Info";
        if (_userInput._pcie) {
            showSltpTitle += " (PCIe)";
        }
        setPrintTitle(_sltpInfoCmd, showSltpTitle, numOfLanesToUse+1);
        if (_productTechnology == PRODUCT_7NM) {
            _mlxlinkMaps->_sltpHeader = "fir_pre1,fir_main,fir_post1";
            if (isSpeed100GPerLane(
                    _protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
                _mlxlinkMaps->_sltpHeader = "fir_pre3,fir_pre2," + _mlxlinkMaps->_sltpHeader;
            } else if (isSpeed50GPerLane(
                _protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
                _mlxlinkMaps->_sltpHeader = "fir_pre2," + _mlxlinkMaps->_sltpHeader;
            }
        } else if (_productTechnology == PRODUCT_16NM) {
            _mlxlinkMaps->_sltpHeader = "pre2Tap,preTap,mainTap,postTap,m2lp,amp";
        } else {
            _mlxlinkMaps->_sltpHeader = "Pol,tap0,tap1,tap2,bias,preemp_mode";
            if (_userInput._advancedMode) {
                _mlxlinkMaps->_sltpHeader += ",reg,leva";
            }
        }
        if (!_linkUP && !_userInput._pcie && !_prbsTestMode) {
            setPrintVal(_sltpInfoCmd, "Serdes TX parameters", _mlxlinkMaps->_sltpHeader,ANSI_COLOR_RESET, true, false, true);
            cout << _sltpInfoCmd;
            return;
        }
        setPrintVal(_sltpInfoCmd, "Serdes TX parameters", _mlxlinkMaps->_sltpHeader, ANSI_COLOR_RESET, true,true, true);
        for (u_int32_t i = 0; i < numOfLanesToUse; i++) {
            resetParser(regName);
            updatePortType();
            updateField("local_port", _localPort);
            updateField("pnat", (_userInput._pcie) ? PNAT_PCIE : PNAT_LOCAL);
            updateField("lane", i);
            updateField("c_db", _userInput._db);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            if (_productTechnology == PRODUCT_16NM) {
                prepareSltp16nm(sltpLanes, i);
            } else if (_productTechnology == PRODUCT_7NM) {
                prepareSltp7nm(sltpLanes, i);
            } else {
                prepareSltp28_40nm(sltpLanes, i);
            }
            if (!getFieldValue("status")) {
                valid = false;
            }
            setPrintVal(_sltpInfoCmd, "Lane " + to_string(i),
                    getStringFromVector(sltpLanes[i]),ANSI_COLOR_RESET, true,valid, true);
        }
        cout << _sltpInfoCmd;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing SLTP raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showDeviceData()
{
    try {
        std::vector<string> showDeviceDataValues;
        string regName = "MSGI";
        bool success = false;
        try {
            resetParser(regName);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            success = true;
        } catch (...) { }
        setPrintTitle(_showDeviceInfoCmd, "Device Info", DEVICE_INFO_LAST);
        setPrintVal(_showDeviceInfoCmd, "Part Number", success ? getDevicePN() : "N/A");
        setPrintVal(_showDeviceInfoCmd,"Part Name", success ? getDeviceProductName() : "N/A");
        setPrintVal(_showDeviceInfoCmd, "Serial Number", success ? getDeviceSN() : "N/A");
        setPrintVal(_showDeviceInfoCmd, "Revision", success ? getDeviceRev() : "N/A");
        setPrintVal(_showDeviceInfoCmd, "FW Version", getDeviceFW());

        cout << _showDeviceInfoCmd;

        if (_isHCA) {
            MlxlinkRecord::printWar("Note: P/N, Product Name, S/N and Revision are supported only in switches", _jsonRoot);
        }

    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing Device Data via MSGI raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showBerMonitorInfo()
{
    if (_isHCA) {
        throw MlxRegException("\"--" BER_MONITOR_INFO_FLAG "\" option is not supported for HCA");
    }
    try {
        string regName = "PPBMC";
        string monitor_state = "N/A";
        string monitor_type = "N/A";
        string alarm_th = "N/A";
        string warning_th = "N/A";
        string normal_th = "N/A";
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        monitor_state = _mlxlinkMaps->_ppbmcBerMonitorState[getFieldValue("monitor_state")];
        u_int32_t monitor_type_int = getFieldValue("monitor_type");
        monitor_type = _mlxlinkMaps->_ppbmcBerMonitorType[monitor_type_int];

        setPrintTitle(_showBerMonitorInfo, "BER Monitor Info", BER_MONITOR_INFO_LAST);
        setPrintVal(_showBerMonitorInfo, "BER Monitor State", monitor_state);
        setPrintVal(_showBerMonitorInfo, "BER Monitor Type", monitor_type);

        cout << _showBerMonitorInfo;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing BER Monitor via PPBMC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showExternalPhy()
{
    try {
        gearboxBlock(PEPC_SHOW_FLAG);
        if (_isHCA || _devID == DeviceSwitchIB || _devID == DeviceSwitchIB2
                || _devID == DeviceQuantum || _devID == DeviceQuantum2) {
            throw MlxRegException("\"--" PEPC_SHOW_FLAG "\" option is not supported for HCA and InfiniBand switches");
        }
        string regName = "PEPC";
        string twisted_pair_an = "N/A";
        string twisted_pair_force_mode = "N/A";
        string twisted_pair_an_mode = "N/A";
        resetParser(regName);
        updateField("local_port", _localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        twisted_pair_force_mode = _mlxlinkMaps->_pepcTwistedPairForceMode[getFieldValue("twisted_pair_force_mode")];
        setPrintTitle(_extPhyInfoCmd, "External PHY Info", EXT_PHY_INFO_INFO_LAST);
        setPrintVal(_extPhyInfoCmd, "Twisted Pair Force Mode", twisted_pair_force_mode);
        cout << _extPhyInfoCmd;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing External PHY via PEPC raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::initValidDPNList()
{
    if (!_validDpns.empty()) {
        return;
    }
    string regName = "MPEIN";
    bool valid = false;
    u_int32_t maxNumOfHost = 4;
    u_int32_t maxNumOfDsPort = 16;
    u_int32_t maxDepth = 4;
    u_int32_t depth, pcie_index, node;

    for (pcie_index = 0; pcie_index < maxNumOfHost; pcie_index++) {
        resetParser(regName);
        updateField("pcie_index", pcie_index);
        updateField("depth", 0);
        updateField("node", 0);
        try {
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
            valid = getFieldValue("bdf0");
        } catch (...) {
            valid = false;
        }
        if (valid && getFieldValue("port_type") == PORT_TYPE_EP) {
            _validDpns.push_back(DPN(0, pcie_index, 0));
        } else {
            if (valid && getFieldValue("port_type") == PORT_TYPE_US) {
                _validDpns.push_back(DPN(0, pcie_index, 0));
            }
            for (depth = 1; depth < maxDepth; depth++) {
                resetParser(regName);
                updateField("pcie_index", pcie_index);
                updateField("depth", depth);
                updateField("node", 0);
                try {
                    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
                    if (getFieldValue("port_type") == PORT_TYPE_DS) {
                        _validDpns.push_back(DPN(depth, pcie_index, 0));
                        for (node = 1; node < maxNumOfDsPort; node++) {
                            resetParser(regName);
                            updateField("pcie_index", pcie_index);
                            updateField("depth", depth);
                            updateField("node", node);
                            try {
                                genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
                                _validDpns.push_back(DPN(depth, pcie_index, node));
                            } catch (...) {
                                break;
                            }
                        }
                    }
                } catch (...) {
                }
            }
        }
        //break should be removed after fixing pcie index validity from the fw (for switches only)
        //bug 1775657
        if (!_isHCA) {
            break;
        }
    }
}

void MlxlinkCommander::showPcieLinks()
{
    try {
        if (_validDpns.size() == 0) {
            throw MlxRegException("No valid DPN's detected!");
        }
        setPrintTitle(_validPcieLinks,"Valid PCIe Links", _validDpns.size()+1);
        setPrintVal(_validPcieLinks, "Legend", "depth, pcie_index, node, port",
                ANSI_COLOR_RESET, true, true, true);
        for(u_int32_t i = 0; i < _validDpns.size(); i++) {
            char dpnStr [20];
            int localPort  = getLocalPortFromMPIR(_validDpns[i]);
            sprintf(dpnStr,"%d, %d, %d, %d", _validDpns[i].depth,
                    _validDpns[i].pcieIndex, _validDpns[i].node, localPort);
            setPrintVal(_validPcieLinks, "Link " + to_string(i+1), dpnStr,
                    ANSI_COLOR_RESET, localPort >= 0, true, true);
        }
        cout << _validPcieLinks;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing valid PCIe links raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showPcie()
{
    try {
        if (_userInput._links) {
            return;
        }
        if(!_userInput._sendDpn && !_userInput._portSpecified) {
            if (_validDpns.size() == 0) {
                throw MlxRegException("No valid DPN's detected!");
            }
            int localPort = 0;
            for(u_int32_t i = 0; i < _validDpns.size(); i++) {
                localPort = getLocalPortFromMPIR(_validDpns[i]);
                if (localPort >= 0) {
                    showPcieState(_validDpns[i]);
                }
            }
        } else {
            showPcieState(_dpn);
        }
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing Pcie via MPEIN raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showPcieState(DPN& dpn)
{
    string regName = "MPEIN";
    resetParser(regName);

    _pcieInfoCmd = MlxlinkCmdPrint();
    updateField("pcie_index", dpn.pcieIndex);
    updateField("depth", dpn.depth);
    updateField("node", dpn.node);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    string linkSpeedEnabled = " ("
                              + pcieSpeedStr(getFieldValue("link_speed_enabled")) + ")";
    string linkWidthEnabled = " ("
                              + to_string((getFieldValue("link_width_enabled")))
                              + "X)";
    _numOfLanesPcie = getFieldValue("link_width_active");

    setPrintTitle(_pcieInfoCmd,"PCIe Operational (Enabled) Info", PCIE_INFO_LAST);

    char dpnStr [15];
    sprintf(dpnStr,"%d, %d, %d", dpn.depth, dpn.pcieIndex, dpn.node);
    setPrintVal(_pcieInfoCmd, "Depth, pcie index, node", dpnStr);
    setPrintVal(_pcieInfoCmd, "Link Speed Active (Enabled)",
            pcieSpeedStr(getFieldValue("link_speed_active"))+ linkSpeedEnabled);
    setPrintVal(_pcieInfoCmd, "Link Width Active (Enabled)",
            to_string(_numOfLanesPcie) + "X" + linkWidthEnabled);
    setPrintVal(_pcieInfoCmd, "Device Status",
            getFieldValue("device_status") ? pcieDeviceStatusStr(getFieldValue("device_status")):"N/A");

    cout << _pcieInfoCmd;
}

void MlxlinkCommander::collectAMBER()
{
    try {
        if (_productTechnology >= PRODUCT_16NM) {
            initAmBerCollector();

            if (!_isHCA) {
                // If port provided, collect one port only
                if (_userInput._portSpecified) {
                    PortGroup pg {_localPort, _userInput._labelPort, 0, _userInput._splitPort};
                    if (_devID == DeviceQuantum2) {
                        pg.secondSplit = _userInput._secondSplitProvided ? _userInput._secondSplitPort
                                                                         : 0;
                    }
                    _amberCollector->_localPorts.push_back(pg);
                } else {
                    // collect all ports info if the port flag wasn't provided
                    string regName = "MGPIR";
                    resetParser(regName);
                    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
                    u_int32_t numOfPorts = getFieldValue("num_of_modules");
                    vector<string> labelPorts;
                    _ignorePortStatus = false;
                    for (u_int32_t labelPort = 1; labelPort <= numOfPorts; labelPort ++) {
                        labelPorts.push_back(to_string(labelPort));
                    }
                    handleLabelPorts(labelPorts, true);
                    _amberCollector->_localPorts = _localPortsPerGroup;
                }
            }

            _amberCollector->startCollector();
        } else {
            throw MlxRegException(AMBER_COLLECT_FLAG " is not available for "\
                  "this device, please use " BER_COLLECT_FLAG " flag instead");
        }
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Collecting AMBER raised the following exception: \n") +
                                      string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::collectBER()
{
    try {
        if (_productTechnology >= PRODUCT_16NM) {
            throw MlxRegException(BER_COLLECT_FLAG " is not available for "\
                  "this device, please use " AMBER_COLLECT_FLAG " flag instead");
        }

        const char *fileName = _userInput._csvBer.c_str();
        ifstream ifile(fileName);
        ofstream berFile;

        if (!ifile) {
            berFile.open(fileName, std::ofstream::app);
            berFile << _mlxlinkMaps->_berCollectTitle << endl;
        } else {
            berFile.open(fileName, std::ofstream::app);
        }

        MlxlinkRecord::printCmdLine("Collecting BER and producing report to " +
                _userInput._csvBer , _jsonRoot);

        string active_fec = _prbsTestMode ? "N/A" : _mlxlinkMaps->_fecModeActive[_fecActive];
        findAndReplace(active_fec, ",", " ");
        string devicePN = getDevicePN(true);
        string deviceFW = getDeviceFW();
        getCableParams();
        u_int32_t linkDown = getLinkDown();
        std::map<std::string, float>  errorsVector = getRawEffectiveErrors();
        float rawBerLimit = getRawBERLimit();
        string result =
            (getResult(errorsVector, rawBerLimit, linkDown)) ?
            "Pass" : "Fail";
        string protocol = _prbsTestMode ? getPrbsModeRX() : _speedStrG;
        u_int32_t speed = _prbsTestMode ? getPrbsRateRX() : _speedBerCsv;
        if (_protoActive == IB) {
            speed = (speed * _numOfLanes) / MAX_LANES_NUMBER;
        }
        string port = to_string(_userInput._labelPort);
        if (_userInput._splitProvided) {
            port += "/"  + to_string(_userInput._splitPort) ;
        }
        berFile << _userInput._testMode << ',' << protocol << ','
                << speed << ',' << active_fec << ',' << _userInput._iteration << ','
                << devicePN << ',' << deviceFW << ',' << '1' << ','
                << port << ','
                << getCableMedia(_cableMediaType) << ','
                << _cablePN << ','
                << getCableLengthStr(_cableLen, _cmisCable) << ','
                << _cableAtten12G << ','
                << errorsVector["time_since_last_clear_sec"] / 60 << ','
                << errorsVector["phy_corrected_bits_lane0"] << ','
                << errorsVector["phy_corrected_bits_lane1"] << ','
                << errorsVector["phy_corrected_bits_lane2"] << ','
                << errorsVector["phy_corrected_bits_lane3"] << ','
                << errorsVector["phy_corrected_bits_lane4"] << ','
                << errorsVector["phy_corrected_bits_lane5"] << ','
                << errorsVector["phy_corrected_bits_lane6"] << ','
                << errorsVector["phy_corrected_bits_lane7"] << ',' << linkDown
                << ',' << errorsVector["raw_ber"] << ',' << rawBerLimit << ','
                << errorsVector["eff_errors_counter"] << ','
                << errorsVector["eff_ber"] << ',' << result << ','
                << "N/A,N/A,N/A," << _moduleTemp << ',' << _moduleTemp << ",N/A,N/A," << _cableSN << ",N/A";
        berFile << endl;
        berFile.close();
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string(
                "Collecting BER and producing report raised the following exception: \n") + string(exc.what()) + string("\n");
    }
}

u_int32_t MlxlinkCommander::readBitFromField(const string &fieldName, u_int32_t bitIndex)
{
    char blockName[128];
    u_int32_t blockSelector = bitIndex/MAX_DWORD_BLOCK_SIZE;
    sprintf(blockName, "%s[%d]", fieldName.c_str(), blockSelector);

    u_int32_t bitMask = (u_int32_t)pow(2.0, (int)(bitIndex - (blockSelector * MAX_DWORD_BLOCK_SIZE)));
    u_int32_t bitValue = (getFieldValue(string(blockName)) & bitMask);

    return bitValue;
}

void MlxlinkCommander::showTxGroupMapping()
{
    try {
        if (_devID != DeviceSpectrum2 &&  _devID != DeviceQuantum && _devID != DeviceQuantum2) {
            throw MlxRegException("Port group mapping supported for Spectrum-2 and Quantum switches only!");
        }
        string regName = "PGMR";
        resetParser(regName);

        updateField("local_port", 1); // it will not affect the request
        updateField("group", _userInput._showGroup);
        updateField("pnat", PNAT_LOCAL);
        updateField("pg_sel", TX_GROUP);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        vector<u_int32_t> localPorts;
        u_int32_t localPortMask = 0;
        for (size_t i = 1; i <= maxLocalPort(); i++) {
            localPortMask = readBitFromField("ports_mapping_of_group", i-1);
            if (localPortMask) {
                localPorts.push_back(i);
            }
        }
        string ports = getStringFromVector(localToPortsPerGroup(localPorts));
        setPrintTitle(_portGroupMapping, "Tx Port Group Mapping ", 1);
        char title[64];
        sprintf(title, "Ports Mapped to Group %d", _userInput._showGroup);
        setPrintVal(_portGroupMapping, title, ports, ANSI_COLOR_RESET, true,
                !_prbsTestMode && !ports.empty(), true);

        cout << _portGroupMapping;
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Showing ports group mapping raised the "
                "following exception: ") + string(exc.what()) + string("\n");
    }
}

int MlxlinkCommander::getLinkDown()
{
    string regName = "PPCNT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_PHY_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return getFieldValue("link_down_events");
}

std::map<std::string, float>  MlxlinkCommander::getRawEffectiveErrorsinTestMode()
{
    string regName = "PPCNT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_PHY_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    std::map<string, float> errorsVector;
    errorsVector["phy_corrected_bits_lane0"] = add32BitTo64(getFieldValue(
                                                                "edpl_bip_errors_lane0_high"),
                                                            getFieldValue("edpl_bip_errors_lane0_low"));
    errorsVector["phy_corrected_bits_lane1"] = add32BitTo64(getFieldValue(
                                                                "edpl_bip_errors_lane1_high"),
                                                            getFieldValue("edpl_bip_errors_lane1_low"));
    errorsVector["phy_corrected_bits_lane2"] = add32BitTo64(getFieldValue(
                                                                "edpl_bip_errors_lane2_high"),
                                                            getFieldValue("edpl_bip_errors_lane2_low"));
    errorsVector["phy_corrected_bits_lane3"] = add32BitTo64(getFieldValue(
                                                                "edpl_bip_errors_lane3_high"),
                                                            getFieldValue("edpl_bip_errors_lane3_low"));
    errorsVector["time_since_last_clear_sec"] = (add32BitTo64(getFieldValue(
                                                                  "time_since_last_clear_high"),
                                                              getFieldValue("time_since_last_clear_low"))) / 1000;

    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_STATISTICAL_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    float effBerCoef = 0, effBerMag = 0, rawBerCoef = 0, rawBerMag = 0;
    float raw_ber = 0, eff_ber = 0;
    int raw_errors_counter = 0, eff_errors_counter = 0;
    eff_errors_counter = add32BitTo64(getFieldValue("phy_symbol_errors_high"),
                                      getFieldValue("phy_symbol_errors_low"));
    raw_errors_counter = add32BitTo64(getFieldValue("phy_corrected_bits_high"),
                                      getFieldValue("phy_corrected_bits_low"));
    rawBerCoef = getFieldValue("raw_ber_coef");
    rawBerMag = getFieldValue("raw_ber_magnitude");
    effBerCoef = getFieldValue("effective_ber_coef");
    effBerMag = getFieldValue("effective_ber_magnitude");
    raw_ber = rawBerCoef * std::pow(10, -rawBerMag);
    eff_ber = effBerCoef * std::pow(10, -effBerMag);

    errorsVector["raw_errors_counter"] = raw_errors_counter;
    errorsVector["raw_ber"] = raw_ber;
    errorsVector["eff_errors_counter"] = eff_errors_counter;
    errorsVector["eff_ber"] = eff_ber;

    return errorsVector;
}

std::map<string, float> MlxlinkCommander::getRawEffectiveErrors()
{
    if (_prbsTestMode) {
        return getRawEffectiveErrorsinTestMode();
    }
    string regName = "PPCNT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("swid", SWID);
    updateField("pnat", PNAT_LOCAL);
    updateField("grp", PPCNT_STATISTICAL_GROUP);
    updateField("clr", 0);
    updateField("prio_tc", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    std::map<string, float> errorsVector;
    errorsVector["phy_corrected_bits_lane0"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane0_high"),
                                                            getFieldValue("phy_raw_errors_lane0_low"));
    errorsVector["phy_corrected_bits_lane1"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane1_high"),
                                                            getFieldValue("phy_raw_errors_lane1_low"));
    errorsVector["phy_corrected_bits_lane2"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane2_high"),
                                                            getFieldValue("phy_raw_errors_lane2_low"));
    errorsVector["phy_corrected_bits_lane3"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane3_high"),
                                                            getFieldValue("phy_raw_errors_lane3_low"));
    errorsVector["phy_corrected_bits_lane4"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane4_high"),
                                                            getFieldValue("phy_raw_errors_lane4_low"));
    errorsVector["phy_corrected_bits_lane5"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane5_high"),
                                                            getFieldValue("phy_raw_errors_lane5_low"));
    errorsVector["phy_corrected_bits_lane6"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane6_high"),
                                                            getFieldValue("phy_raw_errors_lane6_low"));
    errorsVector["phy_corrected_bits_lane7"] = add32BitTo64(getFieldValue(
                                                                "phy_raw_errors_lane7_high"),
                                                            getFieldValue("phy_raw_errors_lane7_low"));
    errorsVector["time_since_last_clear_sec"] = (add32BitTo64(getFieldValue(
                                                                  "time_since_last_clear_high"),
                                                              getFieldValue("time_since_last_clear_low"))) / 1000;

    float effBerCoef = 0, effBerMag = 0, rawBerCoef = 0, rawBerMag = 0;
    float raw_ber = 0, eff_ber = 0;
    int raw_errors_counter = 0, eff_errors_counter = 0;
    eff_errors_counter = add32BitTo64(getFieldValue("phy_symbol_errors_high"),
                                      getFieldValue("phy_symbol_errors_low"));
    raw_errors_counter = add32BitTo64(getFieldValue("phy_corrected_bits_high"),
                                      getFieldValue("phy_corrected_bits_low"));
    rawBerCoef = getFieldValue("raw_ber_coef");
    rawBerMag = getFieldValue("raw_ber_magnitude");
    effBerCoef = getFieldValue("effective_ber_coef");
    effBerMag = getFieldValue("effective_ber_magnitude");
    raw_ber = rawBerCoef * std::pow(10, -rawBerMag);
    eff_ber = effBerCoef * std::pow(10, -effBerMag);

    errorsVector["raw_errors_counter"] = raw_errors_counter;
    errorsVector["raw_ber"] = raw_ber;
    errorsVector["eff_errors_counter"] = eff_errors_counter;
    errorsVector["eff_ber"] = eff_ber;

    return errorsVector;
}

string MlxlinkCommander::getSupportedPrbsRates(u_int32_t modeSelector)
{
    string regName = "PPRT";
    if (modeSelector == PRBS_TX) {
        regName = "PPTT";
    }
    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t capsMask = getFieldValue("lane_rate_cap");
    string modeCapStr = "";

    for (auto it = _mlxlinkMaps->_prbsLaneRate.begin(); it !=  _mlxlinkMaps->_prbsLaneRate.end(); it++) {
        if (capsMask & (it->second).capMask) {
            modeCapStr += it->first + string(",");
        }
    }

    return deleteLastChar(modeCapStr);
}

string MlxlinkCommander::getSupportedPrbsModes(u_int32_t modeSelector)
{
    string regName = "PPRT";
    if (modeSelector == PRBS_TX) {
        regName = "PPTT";
    }
    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t capsMask = getFieldValue("prbs_modes_cap");
    capsMask = modeSelector == PRBS_RX? capsMask & 0xffe3fff : capsMask;
    string modeCapStr = "";
    // Iterating over the supported modes according to capability mask
    // And preparing them in one string
    u_int32_t mask = 0;
    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
            it !=  _mlxlinkMaps->_prbsModesList.end(); it++) {
        mask = PRBS31_CAP << it->first;
        if (capsMask & mask) {
            modeCapStr += it->second;
            if (modeSelector == PRBS_RX && mask == SQUARE_WAVEA_CAP) {
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
    string regName = "PPRT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("e", PPRT_PPTT_ENABLE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return prbsMaskToMode(getFieldValue("prbs_mode_admin"), PRBS_RX);
}

u_int32_t MlxlinkCommander::getPrbsRateRX()
{
    string regName = "PPRT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("e", PPRT_PPTT_ENABLE);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return prbsMaskToRateNum(getFieldValue("lane_rate_oper"));
}

float MlxlinkCommander::getRawBERLimit()
{
    float limit;
    if (_userInput._testMode == "NOMINAL"
        || _userInput._testMode == "Nominal") {
        switch (_speedBerCsv) {
        case 25:
        case 50:
        case 100:
            if (_mlxlinkMaps->_fecModeActive[_fecActive] == _mlxlinkMaps->_fecModeActive[0]) {
                limit = pow(10.0, NOMINAL_25G_NO_FEC);
            } else if (_cableAtten12G <= 15) {
                limit = pow(10.0, NOMINAL_25G_LOW_ATTN);
            } else {
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
    } else {
        switch (_speedBerCsv) {
        case 25:
        case 50:
        case 100:
            if (_mlxlinkMaps->_fecModeActive[_fecActive] == _mlxlinkMaps->_fecModeActive[0]) {
                limit = 3.0 * pow(10.0, CORNER_25G_NO_FEC);
            } else if (_cableAtten12G <= 15) {
                limit = pow(10.0, CORNER_25G_LOW_ATTN);
            } else {
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

bool MlxlinkCommander::getResult(std::map<std::string, float>  errorsVector, float rawBerLimit, int linkDown)
{
    float timeSinceLastClearSec = errorsVector["time_since_last_clear_sec"];
    if (timeSinceLastClearSec == 0
        || 1 / (timeSinceLastClearSec * _speedBerCsv * pow(10.0, 9))
        > getRawBERLimit()) {
        return false;
    }
    if (errorsVector["raw_ber"] < rawBerLimit
        && errorsVector["eff_ber"] < rawBerLimit && linkDown == 0) {
        return true;
    }
    return false;
}

string MlxlinkCommander::getDevicePN(bool queryMSGI)
{
    if (queryMSGI) {
        string regName = "MSGI";
        try {
            resetParser(regName);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (...) {
            return "N/A";
        }
    }
    return getAscii("part_number", 20);
}

string MlxlinkCommander::getDeviceSN(bool queryMSGI)
{
    if (queryMSGI) {
        string regName = "MSGI";
        try {
            resetParser(regName);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (...) {
            return "N/A";
        }
    }
    return getAscii("serial_number", 24);
}

string MlxlinkCommander::getDeviceProductName(bool queryMSGI)
{
    if (queryMSGI) {
        string regName = "MSGI";
        try {
            resetParser(regName);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (...) {
            return "N/A";
        }
    }
    return getAscii("product_name", 64);
}

string MlxlinkCommander::getDeviceRev(bool queryMSGI)
{
    if (queryMSGI) {
        string regName = "MSGI";
        try {
            resetParser(regName);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        } catch (...) {
            return "N/A";
        }
    }
    return getVendorRev(getFieldValue("revision"));
}

string MlxlinkCommander::getDeviceFW()
{
    return _fwVersion;
}

// Config functions

void MlxlinkCommander::clearCounters()
{
    try {
        MlxlinkRecord::printCmdLine("Clearing Counters", _jsonRoot);

        string regName = "PPCNT";
        resetParser(regName);
        updatePortType();

        updateField("local_port", _localPort);
        updateField("swid", SWID);
        updateField("pnat", PNAT_LOCAL);
        updateField("grp", PPCNT_ALL_GROUPS);
        updateField("prio_tc", 0);
        updateField("clr", 1);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Clearing counters via PPCNT raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::isForceDownSupported()
{
    bool supported = false;
    if (_isHCA) {
        //checking force_down cap
        u_int64_t fdCapMask = PCAM_FORCE_DOWN_CAP_MASK; //feature_cap_mask.Bit 45 (feature_cap_mask[2].bit 13)
        string regName = "PCAM";
        resetParser(regName);

        updateField("feature_group", 0);
        updateField("access_reg_group", 0);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        supported = getFieldValue("feature_cap_mask[2]") & fdCapMask;
    }
    return supported;
}

void MlxlinkCommander::sendGBPaosCmd(PAOS_ADMIN adminStatus, bool forceDown)
{
    try {
        string regName = "PPAOS";
        resetParser(regName);
        updateField("swid", SWID);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("phy_status_admin", adminStatus == PAOS_UP);
        if (forceDown) {
            updateField("fpd", forceDown);
        }

        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        string portCommand = (adminStatus == PAOS_DOWN)? "down" : "up";
        throw MlxRegException(
                "Sending port " + portCommand + " command failed, " + string(exc.what()));
    }
}

void MlxlinkCommander::sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown)
{
    try {
        if (_isGboxPort) {
            sendGBPaosCmd(adminStatus, forceDown);
        } else {
            string regName = "PAOS";
            resetParser(regName);
            updateField("swid", SWID);
            updateField("local_port", _localPort);
            updateField("admin_status", adminStatus);
            updateField("ase", 1);
            // Send force down for test mode only
            if (!_userInput._prbsMode.empty()) {
                if (forceDown) {
                    updateField("fd", 1);
                }
            }
            genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
        }
    } catch (const std::exception &exc) {
        string portCommand = (adminStatus == PAOS_DOWN)? "down" : "up";
        throw MlxRegException("Sending port " + portCommand + " command failed");
    }
}

void MlxlinkCommander::sendPaos()
{
    try {
        PAOS_CMD paosCmd = paos_to_int(_userInput._paosCmd);
        switch (paosCmd) {
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
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Sending PAOS raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::sendPaosDown(bool toggleCommand)
{
    MlxlinkRecord::printCmdLine("Configuring Port State (Down)", _jsonRoot);

    bool forceDown = isForceDownSupported();
    // try to force down the port
    sendPaosCmd(PAOS_DOWN, forceDown);
    msleep(1000); // wait for 1 sec before checking the status
    // Verify the link status after down command
    if (!checkPaosDown()) {
        if (_isHCA) {
            // in case of using old fw version (older than xx.28.xxxx)
            if (!forceDown && !_userInput._prbsMode.empty()) {
                string message = "Enabling PRBS is not supported in the "
                        "current FW version. Please contact Nvidia networking division support.";
                throw MlxRegException(message);
            } else if (!toggleCommand){
                string protocol = (_protoActive == IB) ? "IB" : "ETH";
                string message = "port is not Down, for some reasons:\n";
                message += "1- The link is configured to be up, run this command if KEEP_" + protocol + "_LINK_UP_Px is True:\n";
                message += "   mlxconfig -d " + _device + " set KEEP_" + protocol + "_LINK_UP_P<port_number>=0\n";
                message += "2- Port management is enabled (management protocol requiring the link to remain up, PAOS won't manage to disable the port)\n";
                message += "3- In case of multi-host please verify all hosts are not holding the port up";
                throw MlxRegException(message);
            }
        } else {
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

void MlxlinkCommander::handlePrbs()
{
    try {
        if (_userInput._prbsMode == "EN") {
            checkPprtPptt();
            if (_prbsTestMode) {
                sendPrbsPpaos(false);
            }
            sendPaosDown();
            if (checkPaosDown()) {
                MlxlinkRecord::printCmdLine("Configuring Port to Physical Test Mode", _jsonRoot);
                resetPprtPptt();
                sendPprtPptt();
                sendPrbsPpaos(true);
            } else {
                throw MlxRegException("Port is not down, unable to enter test mode");
            }
        } else if (_userInput._prbsMode == "DS") {
            MlxlinkRecord::printCmdLine("Configuring Port to Regular Operation", _jsonRoot);
            if (_prbsTestMode) {
                sendPrbsPpaos(false);
            }
            resetPprtPptt();
            sendPaosToggle();
        } else if (_userInput._prbsMode == "TU") {
            if (_prbsTestMode) {
                MlxlinkRecord::printCmdLine("Performing Tuning", _jsonRoot);
                startTuning();
            } else {
                throw MlxRegException(
                          "Port is not configured for physical test mode. Please see help");
            }
        }
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Handling PRBS raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::checkPRBSModeCap(u_int32_t modeSelector, u_int32_t capMask)
{
    string modeToCheck = _userInput._pprtMode;
    string prbsModeStr = "RX";
    if (modeSelector == PRBS_TX) {
        modeToCheck = _userInput._ppttMode;
        prbsModeStr = "TX";
    }
    // for RX mode: SQUARE_WAVE and SQUARE_WAVEA have the same enum
    if (modeSelector == PRBS_RX && modeToCheck == "SQUARE_WAVE") {
        modeToCheck += "A";
    }

    switch(modeToCheck[-1])
    {
        case '8':
            findAndReplace(modeToCheck,"8","A");
            break;
        case '4':
            findAndReplace(modeToCheck,"4","B");
            break;
        case '2':
            findAndReplace(modeToCheck,"2","C");
            break;
        case '1':
            findAndReplace(modeToCheck,"1","D");
            break;
    }

    // Fetching mode capability from mode list
    u_int32_t modeCap = 0;

    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_prbsModesList.begin();
            it !=  _mlxlinkMaps->_prbsModesList.end(); it++) {
        if (modeToCheck == it->second) {
            modeCap = PRBS31_CAP << it->first;
            break;
        }
    }
    // checking if the fetched capability supported in cap mask or not
    if (!(modeCap & capMask)) {
        string errStr = "Device does not support " + prbsModeStr +
                        " PRBS pattern \"" + modeToCheck +
                        "\" in physical test mode.";
        errStr += "\nValid RX PRBS modes Are: " + getSupportedPrbsModes(PRBS_RX);
        errStr += "\nValid TX PRBS modes Are: " + getSupportedPrbsModes(PRBS_TX);
        errStr += "\nDefault PRBS Mode is PRBS31";
        throw MlxRegException(errStr);
    }
}

void MlxlinkCommander::checkPrbsRegsCap(const string &prbsReg, const string &laneRate)
{
    u_int32_t modeSelector = (prbsReg == "PPTT") ? PRBS_TX : PRBS_RX;
    resetParser(prbsReg);
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    genBuffSendRegister(prbsReg, MACCESS_REG_METHOD_GET);

    bool invalidRateStr = !laneRate.empty() && !_mlxlinkMaps->_prbsLaneRate[laneRate].capMask;

    u_int32_t laneRateCap = _mlxlinkMaps->_prbsLaneRate[laneRate].capMask ?
                _mlxlinkMaps->_prbsLaneRate[laneRate].capMask : (u_int32_t)LANE_RATE_EDR_CAP;

    string laneRateStr = laneRate.empty() ? _mlxlinkMaps->_prbsLaneRateList[PRBS_EDR] : laneRate; // Default lane rate

    if (invalidRateStr || !(laneRateCap & getFieldValue("lane_rate_cap"))) {
        string errStr = "Device does not support lane rate " + laneRateStr + " in physical test mode.\n";
        string rxRates =  getSupportedPrbsRates(PRBS_RX);
        string txRates =  getSupportedPrbsRates(PRBS_TX);
        if (rxRates.empty()) {
            rxRates = "No Valid RX PRBS lane rate";
        } else {
            rxRates = "Valid RX PRBS lane rates: " + rxRates;
        }
        errStr += rxRates + "\n";
        if (txRates.empty()) {
            txRates = "No Valid TX PRBS lane rate";
        } else {
            txRates = "Valid TX PRBS lane rates: " + txRates;
        }
        errStr += txRates + "\n";
        errStr += "Default PRBS Lane Rate is EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)";
        throw MlxRegException(errStr);
    }

    checkPRBSModeCap(modeSelector, getFieldValue("prbs_modes_cap"));

    if (!_userInput._prbsLanesToSet.empty()) {
        if (getFieldValue("ls") != 1) {
            throw MlxRegException("Device does not support per lane configuration");
        }
    }
}

void MlxlinkCommander::checkPprtPptt()
{
    if (!_userInput._prbsLanesToSet.empty()) {
        u_int32_t maxLaneIndex = _numOfLanes - 1;
        for (map<u_int32_t, bool>::iterator it = _userInput._prbsLanesToSet.begin();
                it != _userInput._prbsLanesToSet.end(); it++) {
            if (it->second && (it->first > maxLaneIndex)) {
                throw MlxRegException("Invalid lane index: %d", it->first);
            }
        }
    }
    checkPrbsRegsCap("PPRT", _userInput._pprtRate);
    checkPrbsRegsCap("PPTT", _userInput._ppttRate);
    if (_userInput._prbsTxInv) {
        checkPrbsPolCap("PPTT");
    }
    if (_userInput._prbsRxInv) {
        checkPrbsPolCap("PPRT");
    }
}

void MlxlinkCommander::checkPrbsPolCap(const string &prbsReg)
{
    string invalidPol = "TX";
    if (prbsReg == "PPRT") {
        invalidPol = "RX";
    }
    resetParser(prbsReg);
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    genBuffSendRegister(prbsReg, MACCESS_REG_METHOD_GET);

    if (!getFieldValue("p_c")) {
        throw MlxRegException("PRBS " + invalidPol + " polarity inversion not supported");
    }
}

void MlxlinkCommander::sendPrbsPpaos(bool testMode)
{
    string regName = "PPAOS";
    resetParser(regName);
    updatePortType();

    updateField("swid", SWID);
    updateField("local_port", _localPort);
    updateField("phy_test_mode_admin",
                (testMode ? PPAOS_PHY_TEST_MODE : PPAOS_REGULAR_OPERATION));

    genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
}

void MlxlinkCommander::startTuning()
{
    string regName = "PPRT";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("e", PPRT_PPTT_ENABLE);
    updateField("s", PPRT_PPTT_START_TUNING);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
}

void MlxlinkCommander::prbsConfiguration(const string &prbsReg, bool enable,
        u_int32_t laneRate, u_int32_t prbsMode, bool perLaneConfig, bool prbsPolInv)
{
    string rateToUpdate = prbsReg == "PPRT"? "lane_rate_oper" : "lane_rate_admin";
    if (perLaneConfig) {
        for (map<u_int32_t, bool>::iterator it = _userInput._prbsLanesToSet.begin();
                it != _userInput._prbsLanesToSet.end(); it++) {
            resetParser(prbsReg);
            updatePortType();
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_LOCAL);
            updateField("e", enable);
            updateField(rateToUpdate , laneRate);
            updateField("prbs_mode_admin", prbsMode);
            updateField("le", perLaneConfig);
            if (prbsPolInv) {
                updateField("p", prbsPolInv);
            }
            updateField("lane", it->first);
            if(laneRate == PRBS_HDR) {
                updateField("modulation", PRBS_PAM4_ENCODING);
            }
            if (prbsReg == "PPRT") {
                updateField("s", 0);
            }
            genBuffSendRegister(prbsReg, MACCESS_REG_METHOD_SET);
        }
    } else {
        resetParser(prbsReg);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", PNAT_LOCAL);
        updateField("e", enable);
        updateField(rateToUpdate, laneRate);
        updateField("le", 0);
        if (prbsPolInv) {
            updateField("p", prbsPolInv);
        }
        updateField("prbs_mode_admin", prbsMode);
        if(laneRate == PRBS_HDR) {
            updateField("modulation", PRBS_PAM4_ENCODING);
        }
        if (prbsReg == "PPRT") {
            updateField("s", 0);
        }
        genBuffSendRegister(prbsReg, MACCESS_REG_METHOD_SET);
    }
}

void MlxlinkCommander::sendPprtPptt()
{
    bool perLaneConfig = (!_userInput._prbsLanesToSet.empty()) &&
                       ( _userInput._prbsLanesToSet.size() != _numOfLanes);
    u_int32_t rxRate = _mlxlinkMaps->_prbsLaneRate[_userInput._pprtRate].capMask?
            _mlxlinkMaps->_prbsLaneRate[_userInput._pprtRate].value : (u_int32_t)PRBS_EDR;
    u_int32_t txRate = _mlxlinkMaps->_prbsLaneRate[_userInput._ppttRate].capMask?
                _mlxlinkMaps->_prbsLaneRate[_userInput._ppttRate].value : (u_int32_t)PRBS_EDR;
    prbsConfiguration("PPRT", true, rxRate,
                      prbsModeToMask(_userInput._pprtMode), perLaneConfig,
                      _userInput._prbsRxInv);
    prbsConfiguration("PPTT", true, txRate,
                      prbsModeToMask(_userInput._ppttMode), perLaneConfig,
                      _userInput._prbsTxInv);
}

void MlxlinkCommander::resetPprtPptt()
{
    try {
        if (_prbsTestMode) {
            prbsConfiguration("PPRT", false, PRBS_EDR, PRBS31, false, false);
            prbsConfiguration("PPTT", false, PRBS_EDR, PRBS31, false, false);
        }
    } catch (MlxRegException &exc) {
        // Not necessary to handle if clearing PPRT and PPTT failed
        // They already cleared before enabling the test mode
    }
}

void MlxlinkCommander::validateSpeedStr()
{
    // Normalize IB speeds (Ignore IB- from infiniband speeds)
    for (vector<string>::iterator it = _ptysSpeeds.begin();
                it != _ptysSpeeds.end(); it++) {
        size_t found = (*it).find("IB-");
        if (found != std::string::npos) {
            *it = (*it).erase(found, found + 3);
        }
    }
    // get list of all valid speeds (ETH, ETH extended, and IB)
    string validSpeedStr = "";
    // include NRZ speeds only for devices not supporting extended speeds
    if (!(_protoCapabilityEx && _protoActive == ETH)) {
        validSpeedStr = SupportedSpeeds2Str(ETH, BIT_MASK_ALL_DWORD, false);
    }
    validSpeedStr += "," + SupportedSpeeds2Str(ETH, BIT_MASK_ALL_DWORD, true);
    validSpeedStr += "," + SupportedSpeeds2Str(IB, BIT_MASK_ALL_DWORD, false);
    string speedToCheck = "";
    size_t fromIndex = 0;
    size_t toIndex = 0;
    for (vector<string>::iterator it = _ptysSpeeds.begin();
            it != _ptysSpeeds.end(); it++) {
        fromIndex = validSpeedStr.find(*it);
        toIndex = validSpeedStr.find_first_of(',', fromIndex);
        if (fromIndex != string::npos) {
            speedToCheck = validSpeedStr.substr(fromIndex, toIndex - fromIndex);
        }
        if (toUpperCase(speedToCheck) != *it) {
            throw MlxRegException("%s is invalid speed configuration", (*it).c_str());
        }
    }

    if (isIn(string("56G"), _ptysSpeeds) && _linkModeForce == true) {
        throw MlxRegException("No support of 56G FORCE mode");
    }
}

void MlxlinkCommander::sendPtys()
{
    try {
        if (_prbsTestMode) {
            throw MlxRegException("Cannot Configure Port Speeds in Physical Test Mode. Please Disable First");
        }
        MlxlinkRecord::printCmdLine("Configuring Port Speeds", _jsonRoot);
        validateSpeedStr();
        string regName = "PTYS";
        resetParser(regName);
        updatePortType();

        updateField("local_port", _localPort);
        updateField("proto_mask", _protoActive);
        u_int32_t ptysMask = 0x0;
        string proto = (_protoActive == IB) ? "ib" : "eth";
        for (u_int32_t i = 0; i < _ptysSpeeds.size(); i++) {
            ptysMask |= ptysSpeedToMask(_ptysSpeeds[i]);
        }
        if (_linkModeForce == true) {
            gearboxBlock(PTYS_LINK_MODE_FORCE_FLAG);
            updateField("an_disable_admin", 1);
        }
        if (_protoActive == IB) {
            if (_linkModeForce == false) {
                ptysMask |= 0x1;
            }
            updateField("ib_link_width_admin", 7);
            updateField("ib_proto_admin", ptysMask);
        } else {
            if (_productTechnology >= PRODUCT_16NM) {
                updateField("ext_eth_proto_admin", ptysMask);
            } else {
                updateField("eth_proto_admin", ptysMask);
            }
        }
        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        string errMsg = string(exc.what());
        if (errMsg.find(OPERATIONAL_ERROR_STR) != string::npos) {
            errMsg = "Invalid speed configurations";
        }
        _allUnhandledErrors += string("Sending PTYS (Configuring port speeds) "\
                "raised the following exception: ") + errMsg + string("\n");
    }
}

u_int32_t MlxlinkCommander::ptysSpeedToMask(const string & speed)
{
    bool extended = _productTechnology >= PRODUCT_16NM;
    u_int32_t speedMask = 0;

    checkSupportedSpeed(speed, _protoCapability, extended);

    if (_protoActive == IB) {
        speedMask =  ptysSpeedToMaskIB(speed);
    } else if (extended) {
        speedMask =  ptysSpeedToExtMaskETH(speed);
    } else {
        speedMask =  ptysSpeedToMaskETH(speed);
    }

    return speedMask;
}

void MlxlinkCommander::checkSupportedSpeed(const string & speed, u_int32_t protoCap, bool extSpeed)
{
    u_int32_t mask = 0;
    u_int32_t diffProto = 0;
    string errStr = "";
    string supportedSpeedStr = "";
    if (!extSpeed) {
         mask =
            (_protoActive == IB) ?
            ptysSpeedToMaskIB(speed) : ptysSpeedToMaskETH(speed);
         diffProto =
            (_protoActive == IB) ?
            ptysSpeedToMaskETH(speed) : ptysSpeedToMaskIB(speed);
    } else {
        mask =
           (_protoActive == IB) ?
           ptysSpeedToMaskIB(speed) : ptysSpeedToExtMaskETH(speed);
        diffProto =
           (_protoActive == IB) ?
           ptysSpeedToExtMaskETH(speed) : ptysSpeedToMaskIB(speed);
    }
    supportedSpeedStr = SupportedSpeeds2Str(_protoActive, protoCap, extSpeed);
    if (!supportedSpeedStr.empty()) {
        errStr = "Supported Speeds Are: " + supportedSpeedStr;
    }
    if (diffProto) {
        throw MlxRegException(speed + " is not supported by Protocol!\n" + errStr);
    }
    if (!(mask & protoCap) && _linkUP) {
        throw MlxRegException(speed + " is not supported by Device!\n" + errStr);
    }
}

void MlxlinkCommander::sendPplm()
{
    try {
        if (_prbsTestMode) {
            throw MlxRegException("Cannot Configure FEC in Physical Test Mode. Please Disable First.");
        }
        MlxlinkRecord::printCmdLine("Configuring Port FEC", _jsonRoot);
        if (_protoActive == IB && _ignoreIbFECCheck) {
            throw MlxRegException("FEC Configuration is Valid for ETHERNET only!");
        }
        if (!_linkUP && _userInput._speedFec == "") {
            throw MlxRegException("When Port is Not Active, You Must Specify the Speed to Configure FEC (--fec_speed <speed>)");
        }

        checkPplmCap(); // after calling checkPplmCap, _userInput._speedFec will be changed to the correct fec speed

        resetParser(ACCESS_REG_PPLM);
        updatePortType();
        updateField("local_port", _localPort);

        string speedToConfigure = (_linkUP && _userInput._speedFec == "") ? speedToFecSpeedStr(_speedStrG, _numOfLanes)
                                                                          : _userInput._speedFec;
        u_int32_t fecAdmin = fecToBit(_userInput._pplmFec, speedToConfigure);
        if (speedToConfigure == "50g" || speedToConfigure == "25g") { // 25g and 50g must be set the same
            updateField("fec_override_admin_25g", fecAdmin);
            updateField("fec_override_admin_50g", fecAdmin);
        } else {
            updateField(string(_protoActive == IB ? "ib_":"") + "fec_override_admin_" + speedToConfigure, fecAdmin);
        }

        genBuffSendRegister(ACCESS_REG_PPLM, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Sending PPLM (Configuring port FEC) raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

string MlxlinkCommander::speedToFecSpeedStr(const string &speed, u_int32_t numOfLanes)
{
    string fecSpeedStrFormat = "";
    string numberOfLanesStr = to_string(numOfLanes) + "x";
    if (_protoActive == IB) {
        string speedStr = speed;
        if (speedStr.find("IB-") != string::npos) {
            speedStr = speedStr.substr(3);
        }
        fecSpeedStrFormat = toLowerCase(speedStr);
    } else {
        if (speed == "800G") {
            fecSpeedStrFormat = "800g_" + numberOfLanesStr;
        }
        if (speed == "400G") {
            fecSpeedStrFormat = "400g_" + numberOfLanesStr;
        }
        if (speed == "200G") {
            fecSpeedStrFormat = "200g_" + numberOfLanesStr;
        }
        if (speed == "100G") {
            if (numOfLanes == 4) {
                fecSpeedStrFormat = "100g";
            } else {
                fecSpeedStrFormat = "100g_" + numberOfLanesStr;
            }
        }
        if (speed == "50G") {
            if (numOfLanes == 1) {
                fecSpeedStrFormat = "50g_" + numberOfLanesStr;
            } else {
                fecSpeedStrFormat = "50g";
            }
        }
        if (speed == "100GbE") {
            fecSpeedStrFormat = "100g";
        }
        if (speed == "50GbE") {
            fecSpeedStrFormat = "50g";
        }
        if (speed == "25GbE" || speed == "25G") {
            fecSpeedStrFormat = "25g";
        }
        if (speed == "40GbE" || speed == "40G" || speed == "10GbE" || speed == "10G") {
            fecSpeedStrFormat = "10g_40g";
        }
        if (speed == "56GbE") {
            fecSpeedStrFormat = "56g";
        }
    }
    return fecSpeedStrFormat;
}

u_int32_t MlxlinkCommander::fecToBit(const string &fec, const string &speedStrG)
{
    string fecToCheck = fec;
    u_int32_t fecAdmin = FEC_MODE_MASK_AU;

    // Work with different RS and LL FEC for HDR, NDR and ETH PAM4 speeds
    if ((speedStrG == "ndr" || speedStrG == "hdr") ||
        (speedStrG.find("x") != string::npos && speedStrG != "100g_4x" && speedStrG != "50g_2x")) {
        if (fec == _mlxlinkMaps->_fecModeMask[FEC_MODE_MASK_RS_528].second) {
            fecToCheck += "-544";
        } else if (fec == _mlxlinkMaps->_fecModeMask[FEC_MODE_MASK_LL_271].second && speedStrG != "hdr") {
            fecToCheck += "-272";
        }
    }
    for (auto it = _mlxlinkMaps->_fecModeMask.begin(); it != _mlxlinkMaps->_fecModeMask.end(); it++) {
        if (it->second.second == fecToCheck) {
            fecAdmin = it->first;
        }
    }
    return fecAdmin;
}

u_int32_t MlxlinkCommander::getFecCapForCheck(const string &speedStr)
{
    u_int32_t fecCapMask = 0;
    resetParser(ACCESS_REG_PPLM);
    updatePortType();
    updateField("local_port", _localPort);
    genBuffSendRegister(ACCESS_REG_PPLM, MACCESS_REG_METHOD_GET);

    try {
        fecCapMask = getFieldValue(string(_protoActive == IB ? "ib_" : "") + "fec_override_cap_" + speedStr);
    } catch (MlxRegException &exc){
        throw MlxRegException("\nFEC configuration is not available for this speed: " + speedStr);
    }

    return fecCapMask;
}

void MlxlinkCommander::checkPplmCap()
{
    string speedFec = _userInput._speedFec;
    string uiSpeed = _userInput._speedFec;
    if (_linkUP && _userInput._speedFec.empty()) {
        speedFec = speedToFecSpeedStr(_speedStrG, _numOfLanes);
        uiSpeed = _speedStrG;
    }
    // Validate the speed
    if (!_userInput._speedFec.empty()) {
        vector<string> supportedSpeeds = MlxlinkRecord::split(SupportedSpeeds2Str(_protoActive, _deviceCapability,
                                                                                  _protoCapabilityEx), ",");
        string speedToCheck = _userInput._speedFec;
        speedToCheck = toUpperCase(speedToCheck);
        if (_protoCapabilityEx) {
            if (speedToCheck == "50G") {
                speedToCheck += "_2X";
            } else if (speedToCheck == "100G") {
                speedToCheck += "_4X";
            }
        }
        if (!isIn(speedToCheck, supportedSpeeds)) {
            string validSpeeds = "";
            if (!supportedSpeeds.empty()) {
                validSpeeds = ", valid FEC speed configurations are [";
                for (auto it = _mlxlinkMaps->_fecPerSpeed.begin(); it != _mlxlinkMaps->_fecPerSpeed.end(); it++) {
                    if (isIn(it->first, supportedSpeeds)) {
                        validSpeeds += it->first + ",";
                    }
                }
                validSpeeds = !validSpeeds.empty()? deleteLastChar(validSpeeds) : validSpeeds;
                validSpeeds = validSpeeds + "]";
            }
            throw MlxRegException("\nFEC speed %s is not valid%s", uiSpeed.c_str(), validSpeeds.c_str());
        }
    }
    // Validate the FEC for the speed
    if (speedFec == "10g" || speedFec == "40g") {
        speedFec = "10g_40g";
    }
    if (speedFec == "50g_2x") {
        speedFec = "50g";
    }
    if (speedFec =="100g_4x") {
        speedFec = "100g";
    }
    _userInput._speedFec = speedFec;
    u_int32_t fecCap = getFecCapForCheck(_userInput._speedFec);
    if (_userInput._pplmFec != "AU" && !(fecToBit(_userInput._pplmFec, _userInput._speedFec) & fecCap)) {
        string supportedFec = fecMaskToUserInputStr(fecCap);
        string validFecs = fecMaskToUserInputStr(BIT_MASK_ALL_DWORD);
        string errorMsg = _userInput._pplmFec + " FEC is not supported in " + uiSpeed + " speed, ";
        if (validFecs.find(_userInput._pplmFec) == string::npos) {
            errorMsg = _userInput._pplmFec + " FEC configuration is not valid, ";
        }
        if (supportedFec.empty()) {
            errorMsg += "it's not available for this speed";
        } else {
            errorMsg += "valid FEC configurations are [" + supportedFec + "]";
        }
        throw MlxRegException("\n" + errorMsg);
    }
}

void MlxlinkCommander::getSltpAlevOut(u_int32_t lane)
{
    resetParser(ACCESS_REG_SLTP);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_GET);

    _userInput._sltpParams[OB_ALEV_OUT] = getFieldValue("ob_alev_out");
}

void MlxlinkCommander::getSltpRegAndLeva(u_int32_t lane)
{
    resetParser(ACCESS_REG_SLTP);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_GET);

    _userInput._sltpParams[OB_REG] = getFieldValue("ob_reg");
    _userInput._sltpParams[OB_LEVA] = getFieldValue("ob_leva");
}

u_int32_t MlxlinkCommander::getLaneSpeed(u_int32_t lane)
{
    resetParser(ACCESS_REG_SLTP);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_GET);

    return getFieldValue("lane_speed");
}

void MlxlinkCommander::validateNumOfParamsForNDRGen()
{
    u_int32_t params;
    string errMsg = "Invalid set of Transmitter Parameters, ";
    errMsg += "valid parameters for the active speed are: ";
    if (isSpeed100GPerLane(_protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
        params = PARAMS_7NM_LAST;
        errMsg += "fir_pre3,fir_pre2,fir_pre1,fir_main,fir_post1";
    } else if (isSpeed50GPerLane(_protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
        params = FIR_POST1;
        errMsg += "fir_pre2,fir_pre1,fir_main,fir_post1";
    } else {
        params = FIR_MAIN;
        errMsg += "fir_pre1,fir_main,fir_post1";
    }
    if (_userInput._sltpParams.size() != params) {
        throw MlxRegException(errMsg);
    }
    for (map<u_int32_t, u_int32_t>::iterator it = _userInput._sltpParams.begin();
        it != _userInput._sltpParams.end(); it++) {
        if (((int)it->second) > MAX_SBYTE || ((int)it->second) < MIN_SBYTE) {
            throw MlxRegException("Invalid Transmitter Parameters values");
        }
    }
}

void MlxlinkCommander::checkSltpParamsSize()
{
    u_int32_t sltpParamsSize = OB_REG;
    if (_productTechnology == PRODUCT_16NM) {
        sltpParamsSize = OB_ALEV_OUT;
        for (map<u_int32_t, u_int32_t>::iterator it = _userInput._sltpParams.begin();
                it != _userInput._sltpParams.end(); it++) {
            if (((int)it->second) > MAX_SBYTE || ((int)it->second) < MIN_SBYTE) {
                throw MlxRegException("Invalid Transmitter Parameters values");
            }
        }
    } else if (_productTechnology == PRODUCT_7NM) {
        validateNumOfParamsForNDRGen();
    } else if (_userInput._advancedMode) {
        sltpParamsSize = PARAMS_40NM_LAST;
    }
    if (_userInput._sltpParams.size() != sltpParamsSize && _productTechnology != PRODUCT_7NM) {
        throw MlxRegException("Invalid set of Transmitter Parameters");
    }
}

void MlxlinkCommander::updateSltp28_40nmFields()
{
    updateField("polarity", _userInput._sltpParams[POLARITY]);
    updateField("ob_tap0", _userInput._sltpParams[OB_TAP0]);
    updateField("ob_tap1", _userInput._sltpParams[OB_TAP1]);
    updateField("ob_tap2", _userInput._sltpParams[OB_TAP2]);
    updateField("ob_bias", _userInput._sltpParams[OB_BIAS]);
    updateField("ob_preemp_mode", _userInput._sltpParams[OB_PREEMP_MODE]);
    updateField("ob_reg", _userInput._sltpParams[OB_REG]);
    updateField("ob_leva", _userInput._sltpParams[OB_LEVA]);
}

void MlxlinkCommander::updateSltp16nmFields()
{
    updateField("pre_2_tap", _userInput._sltpParams[PRE_2_TAP]);
    updateField("pre_tap", _userInput._sltpParams[PRE_TAP]);
    updateField("main_tap", _userInput._sltpParams[MAIN_TAP]);
    updateField("post_tap", _userInput._sltpParams[POST_TAP]);
    updateField("ob_m2lp", _userInput._sltpParams[OB_M2LP]);
    updateField("ob_amp", _userInput._sltpParams[OB_AMP]);
    updateField("ob_alev_out", _userInput._sltpParams[OB_ALEV_OUT]);
}

void MlxlinkCommander::updateSltp7nmFields()
{
    u_int32_t indexCorrection = 0;
    if (isSpeed100GPerLane(
            _protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
        updateField("fir_pre3", _userInput._sltpParams[FIR_PRE3]);
        updateField("fir_pre2", _userInput._sltpParams[FIR_PRE2]);
    } else if (isSpeed50GPerLane(
            _protoActive == IB? _activeSpeed : _activeSpeedEx, _protoActive)) {
        updateField("fir_pre2", _userInput._sltpParams[FIR_PRE2]);
        indexCorrection = 1;
    } else {
        indexCorrection = 2;
    }
    updateField("fir_pre1", _userInput._sltpParams[FIR_PRE1 - indexCorrection]);
    updateField("fir_main", _userInput._sltpParams[FIR_MAIN - indexCorrection]);
    updateField("fir_post1", _userInput._sltpParams[FIR_POST1 - indexCorrection]);
}

string MlxlinkCommander::getSltpStatus()
{
    resetParser(ACCESS_REG_SLTP);
    updatePortType();
    updateField("local_port", _localPort);
    string statusStr = "Invalid parameters";
    u_int32_t status = getFieldValue("ob_bad_stat");
    if (status) {
        switch (_productTechnology) {
            case PRODUCT_40NM:
            case PRODUCT_28NM:
                statusStr = _mlxlinkMaps->_SLTPBadSetStatus2Str[status];
                break;
            case PRODUCT_16NM:
                statusStr = _mlxlinkMaps->_SLTP16BadSetStatus2Str[status];
                break;
            case PRODUCT_7NM:
                statusStr = _mlxlinkMaps->_SLTP7BadSetStatus2Str[status];
                break;
         }
    }
    return statusStr;
}

void MlxlinkCommander::sendSltp()
{
    MlxlinkRecord::printCmdLine("Configuring Port Transmitter Parameters", _jsonRoot);

    checkSltpParamsSize();

    if (_userInput._sltpLane && _userInput._lane >= _numOfLanes) {
        throw MlxRegException("Could Not find Lane " + to_string(_userInput._lane));
    }
    if (_userInput._txPolicy && _productTechnology < PRODUCT_7NM ) {
        throw MlxRegException("--" SLTP_TX_POLICY_FLAG " flag is not valid for this device");
    }

    try {
        if ((_devID == DeviceSpectrum2 || _devID == DeviceQuantum || _devID == DeviceQuantum2)
                && _userInput._db) {
            u_int32_t portGroup = getPortGroup(_localPort);
            MlxlinkRecord::printWar("Port " + to_string(_userInput._labelPort) +
                    " is mapped to group " + to_string(portGroup) + ".\nPlease "
                    "notice that the new settings will be implemented in all ports "
                    "mapped to group " + to_string(portGroup), _jsonRoot);
        }
        u_int32_t laneSpeed = 0;
        for (u_int32_t i = 0; i < _numOfLanes; i++) {
            if (_userInput._sltpLane && _userInput._lane != i) {
                continue;
            }
            if (_userInput._db && i != 0) {
                break;
            }
            laneSpeed = getLaneSpeed(i);
            if (_productTechnology < PRODUCT_16NM && !_userInput._advancedMode) {
                getSltpRegAndLeva(i);
            } else if (_productTechnology == PRODUCT_16NM) {
                getSltpAlevOut(i);
            }
            resetParser(ACCESS_REG_SLTP);
            updatePortType();
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_LOCAL);
            updateField("lane_speed", laneSpeed);
            updateField("lane", i);
            updateField("tx_policy", _userInput._txPolicy);
            switch (_productTechnology) {
                case PRODUCT_40NM:
                case PRODUCT_28NM:
                    updateSltp28_40nmFields();
                    break;
                case PRODUCT_16NM:
                    updateSltp16nmFields();
                    break;
                case PRODUCT_7NM:
                    updateSltp7nmFields();
                    break;
            }
            updateField("c_db", _userInput._db || _userInput._txPolicy);
            genBuffSendRegister(ACCESS_REG_SLTP, MACCESS_REG_METHOD_SET);
        }
    } catch (MlxRegException &exc) {
        string errorMsg = getSltpStatus();
        _allUnhandledErrors += string("Configuring Port Transmitter Parameters raised the following exception:\n"
                                      "Failed to send parameter set: ") + errorMsg +"\n";
    }
}

string MlxlinkCommander::getLoopbackStr(u_int32_t loopbackCapMask)
{
    string loopbackStr = "";
    for (map<u_int32_t, string>::iterator it = _mlxlinkMaps->_loopbackModeList.begin();
            it != _mlxlinkMaps->_loopbackModeList.end(); it++) {
        if ((it->first != PHY_REMOTE_LOOPBACK) && (it->first & loopbackCapMask)
                && !it->second.empty()) {
            loopbackStr += it->second + ",";
        }
    }
    return deleteLastChar(loopbackStr);
}

void MlxlinkCommander::checkPplrCap()
{
    string regName = "PPLR";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    u_int32_t loopBackCap = getFieldValue("lb_cap");
    u_int32_t loopBackVal = getLoopbackMode(_userInput._pplrLB);
    if (loopBackVal != PHY_NO_LOOPBACK) {
        if (!(loopBackCap & getLoopbackMode(_userInput._pplrLB))) {
            string supportedLoopbacks = getLoopbackStr(loopBackCap);
            throw MlxRegException("selected loopback not supported\n"
                    "Supported Loopback modes for the device: [%s]",
                    supportedLoopbacks.c_str());
        }
    }
    if (loopBackVal == PHY_REMOTE_LOOPBACK && _productTechnology < PRODUCT_7NM) {
        string warMsg = "Remote loopback mode pre-request (all should be satisfied):\n";
        warMsg += "1. Remote loopback is supported only in force mode.\n";
        warMsg += "   please use the --link_mode_force flag if force mode not configured\n";
        warMsg += "2. Remote loopback is supported for 25G/50G per lane only.\n";
        warMsg += "3. If the NIC has 2 ports, please make sure that both ports are in the same speed.";
        MlxlinkRecord::printWar(warMsg, _jsonRoot);
    }
}

void MlxlinkCommander::sendPplr()
{
    try {
        MlxlinkRecord::printCmdLine("Configuring Port Loopback", _jsonRoot);

        checkPplrCap();
        string regName = "PPLR";
        resetParser(regName);
        updatePortType();

        updateField("local_port", _localPort);
        updateField("lb_en", getLoopbackMode(_userInput._pplrLB));

        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Sending PPLR (Configuring port loopback) raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

u_int32_t MlxlinkCommander::getLoopbackMode(const string &lb)
{
    if (lb == "NO") {
        return PHY_NO_LOOPBACK;
    }
    if (lb == "RM") {
        return PHY_REMOTE_LOOPBACK;
    }
    if (lb == "PH") {
        return PHY_LOCAL_LOOPBACK;
    }
    if (lb == "EX") {
        return EXTERNAL_LOCAL_LOOPBACK;
    }
    throw MlxRegException(
            "Invalid loopback option: %s, see tool usage \"%s --help\"",
            lb.c_str(), MLXLINK_EXEC);
}

void MlxlinkCommander::sendPepc()
{
    try {
        gearboxBlock(PEPC_SET_FLAG);

        if (_isHCA || _devID == DeviceSwitchIB || _devID == DeviceSwitchIB2
                || _devID == DeviceQuantum || _devID == DeviceQuantum2) {
            throw MlxRegException("\"--" PEPC_SET_FLAG "\" option is not supported for HCA and InfiniBand switches");
        }
        MlxlinkRecord::printCmdLine("Configuring External PHY", _jsonRoot);
        string regName = "PEPC";

        // Get old values of PEPC fields
        resetParser(regName);
        updateField("local_port", _localPort);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
        u_int32_t forceMode_int = getFieldValue("twisted_pair_force_mode");
        u_int32_t anMode_int = getFieldValue("twisted_pair_an_mode");

        // Set new values of PEPC fields
        resetParser(regName);
        updateField("local_port", _localPort);
        if (_userInput._sendPepcForceMode) {
            updateField("twisted_pair_force_mode", pepc_force_mode_to_int(_userInput._forceMode));
        } else {
            updateField("twisted_pair_force_mode", forceMode_int);
        }
        updateField("twisted_pair_an_mode", anMode_int);
        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Sending PEPC (Configuring External PHY parameters) raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

u_int32_t MlxlinkCommander::getPortGroup(u_int32_t localPort)
{
    string regName = "PGMR";
    resetParser(regName);

    updateField("local_port", (localPort -1));
    updateField("group", 0); // it will not affect the request
    updateField("pnat", PNAT_LOCAL);
    updateField("pg_sel", TX_LOCAL_PORT);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    u_int32_t groupNum = getFieldValue("group_of_port");

    return groupNum;
}

void MlxlinkCommander::setTxGroupMapping()
{
    try {
        if (_devID != DeviceSpectrum2 && _devID != DeviceQuantum && _devID != DeviceQuantum2) {
            throw MlxRegException("Port group mapping supported for Spectrum-2 and Quantum switches only!");
        }
        MlxlinkRecord::printCmdLine("Configuring Ports-Group Mapping", _jsonRoot);
        handleLabelPorts(_userInput._labelPorts);

        string regName = "PGMR";
        resetParser(regName);

        updateField("local_port", 1); // it will not affect the request
        updateField("group", _userInput._setGroup);
        updateField("pnat", PNAT_LOCAL);
        updateField("pg_sel", TX_GROUP);
        u_int32_t blockSelector, bitMask;
        u_int32_t blocksToSet[4] = {0,0,0,0};
        u_int32_t localPort = 0;
        for (vector<PortGroup>::iterator it = _localPortsPerGroup.begin();
                it != _localPortsPerGroup.end(); it++) {
            localPort =it->localPort;
            blockSelector = (localPort-1)/MAX_DWORD_BLOCK_SIZE;
            bitMask = (u_int32_t)pow(2.0, (int)((localPort-1) - (blockSelector * MAX_DWORD_BLOCK_SIZE)));
            blocksToSet[blockSelector] |= (bitMask);
        }
        updateField("ports_mapping_of_group[0]", blocksToSet[0]);
        updateField("ports_mapping_of_group[1]", blocksToSet[1]);
        updateField("ports_mapping_of_group[2]", blocksToSet[2]);
        updateField("ports_mapping_of_group[3]", blocksToSet[3]);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        string errorMsg = string(exc.what());
        if (errorMsg == OPERATIONAL_ERROR_STR) {
            errorMsg = "Invalid configuration values";
        }
        _allUnhandledErrors += string("Configuring ports group mapping "
                                      "raised the following exception: ") +
                                      errorMsg + string("\n");
    }
}

///////////////////////////////////////////////


// Cable operation
// Cable helper functions

bool MlxlinkCommander::isPassiveQSFP()
{
    switch (_cableIdentifier) {
        case IDENTIFIER_QSFP28:
        case IDENTIFIER_QSFP_PLUS:
            return (_cableMediaType == PASSIVE);
    }
    return false;
}

bool MlxlinkCommander::isSFP51Paging()
{
    // TODO check page 0 byte 64 bit 4, if set, then SFP51, else SFP.
    bool sfpQsaCable = (_cableIdentifier == IDENTIFIER_SFP ||
                        _cableIdentifier == IDENTIFIER_QSA);
    bool readSfp51 = false;
    if (_ddmSupported && sfpQsaCable) {
        readSfp51 = true;
    }
    return readSfp51;
}

void MlxlinkCommander::printOuptputVector(vector<MlxlinkCmdPrint> &cmdOut)
{
    for (vector<MlxlinkCmdPrint>::iterator ptr = cmdOut.begin()
            ; ptr < cmdOut.end(); ptr++) {
        cout << *ptr;
    }
}

void MlxlinkCommander::initCablesCommander()
{
    gearboxBlock(CABLE_FLAG);

    if (_plugged && !_mngCableUnplugged) {
        _cablesCommander = new MlxlinkCablesCommander(_jsonRoot);
        _cablesCommander->_mf = _mf;
        _cablesCommander->_regLib = _regLib;
        _cablesCommander->_gvmiAddress = _gvmiAddress;
        _cablesCommander->_mlxlinkLogger = _mlxlinkLogger;
        _cablesCommander->_moduleNumber = _moduleNumber;
        _cablesCommander->_slotIndex = _slotIndex;
        _cablesCommander->_localPort = _localPort;
        _cablesCommander->_numOfLanes = _numOfLanes;
        _cablesCommander->_cableIdentifier = _cableIdentifier;
        _cablesCommander->_mlxlinkMaps = _mlxlinkMaps;
        _cablesCommander->_sfp51Paging = isSFP51Paging();
        _cablesCommander->_passiveQsfp = isPassiveQSFP();
    } else {
        throw MlxRegException("No plugged cable detected");
    }
}

void MlxlinkCommander::showCableDump()
{
    try {
        initCablesCommander();
        if (_plugged && !_mngCableUnplugged) {
            vector<MlxlinkCmdPrint> dumpOutput = _cablesCommander->getPagesToDump();
            printOuptputVector(dumpOutput);
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += string("Dumping EEPROM pages raised the "\
              "following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::showCableDDM()
{
    try {
        initCablesCommander();
        if (_plugged && !_mngCableUnplugged) {
            if (_ddmSupported) {
                vector<MlxlinkCmdPrint> ddmOutput = _cablesCommander->getCableDDM();
                printOuptputVector(ddmOutput);
            } else {
                throw MlxRegException(string("Cable does not support DDM"));
            }
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += "Showing DDM info raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

vector<u_int8_t> MlxlinkCommander::validateBytes(const vector<string> &strBytes)
{
    vector<u_int8_t> intData;
    u_int32_t byteVal = 0;
    for (u_int32_t i = 0; i < strBytes.size(); i++) {
        strToUint32((char *)strBytes[i].c_str(), byteVal);
        if (byteVal > 255) {
            throw MlxRegException("Invalid byte value %d. It must be within range [0-255].", byteVal);
        }
        intData.push_back(byteVal);
    }
    return intData;
}

void MlxlinkCommander::writeCableEEPROM()
{
    try {
        initCablesCommander();
        MlxlinkRecord::printCmdLine("Writing To Cable EEPROM", _jsonRoot);
        if (_plugged && !_mngCableUnplugged) {
            vector<u_int8_t> bytesToWrite = validateBytes(_userInput._bytesToWrite);
             _cablesCommander->writeToEEPROM(_userInput._page , _userInput._offset, bytesToWrite);
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += "Writing cable EEPROM raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::readCableEEPROM()
{
    try {
        initCablesCommander();
        if (_plugged && !_mngCableUnplugged) {
            MlxlinkCmdPrint bytesOutput =
                    _cablesCommander->readFromEEPRM(_userInput._page , _userInput._offset, _userInput._len);
            cout << bytesOutput;
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += "Reading cable EEPROM raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::performModulePrbsCommands()
{
    try {
        initCablesCommander();
        if (_cmisCable) {
            if (_cableMediaType == ACTIVE || _cableMediaType == OPTICAL_MODULE) {
                if (_userInput.modulePrbsParams[MODULE_PRBS_SELECT] != "HOST" &&
                    _userInput.modulePrbsParams[MODULE_PRBS_SELECT] != "MEDIA") {
                    throw MlxRegException("Invalid module side PRBS select, please check the help menu");
                }
                _cablesCommander->_modulePrbsParams = _userInput.modulePrbsParams;
                if (_userInput.isPrbsModeProvided) {
                    ModuleAccess_t prbsModuleAccess = MODULE_PRBS_ACCESS_BOTH;
                    if (_userInput.isPrbsChProvided && !_userInput.isPrbsGenProvided) {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_CH;
                    } else if (!_userInput.isPrbsChProvided && _userInput.isPrbsGenProvided) {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_GEN;
                    } else if (_userInput.isPrbsChProvided && _userInput.isPrbsGenProvided) {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_CH_GEN;
                    }
                    if (_userInput.modulePrbsParams[MODULE_PRBS_GEN_RATE] == _userInput.modulePrbsParams[MODULE_PRBS_CH_RATE] &&
                        _userInput.modulePrbsParams[MODULE_PRBS_GEN_PAT] == _userInput.modulePrbsParams[MODULE_PRBS_CH_PAT] &&
                        _userInput.modulePrbsParams[MODULE_PRBS_GEN_SWAP] == _userInput.modulePrbsParams[MODULE_PRBS_CH_SWAP] &&
                        _userInput.modulePrbsParams[MODULE_PRBS_GEN_INV] == _userInput.modulePrbsParams[MODULE_PRBS_CH_INV] &&
                        _userInput.modulePrbsParams[MODULE_PRBS_GEN_LANES] == _userInput.modulePrbsParams[MODULE_PRBS_GEN_LANES]) {
                        prbsModuleAccess = MODULE_PRBS_ACCESS_BOTH;
                    }
                    _cablesCommander->handlePrbsTestMode(_userInput.modulePrbsParams[MODULE_PRBS_MODE], prbsModuleAccess);
                } else {
                    _cablesCommander->showPrbsTestMode();
                }

                if (_userInput.isPrbsShowDiagProvided) {
                    _cablesCommander->showPrpsDiagInfo();
                }

                if (_userInput.isPrbsClearDiagProvided) {
                    _cablesCommander->clearPrbsDiagInfo();
                }
            } else {
                throw MlxRegException("The PRBS test mode supported over Active/Optical modules only");
            }
        } else {
            throw MlxRegException("The PRBS test mode supported for CMIS modules only");
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += "Module PRBS test mode raised the following exception: ";
        _allUnhandledErrors += exc.what_s();
        _allUnhandledErrors += "\n";
    }
}

void MlxlinkCommander::initEyeOpener()
{
    try {
        gearboxBlock(MARGIN_SCAN_FLAG);
        if (_linkUP || _userInput._pcie) {
            _eyeOpener = new MlxlinkEyeOpener(_jsonRoot);
            _eyeOpener->_mf = _mf;
            _eyeOpener->_regLib = _regLib;
            _eyeOpener->_gvmiAddress = _gvmiAddress;
            _eyeOpener->_mlxlinkLogger = _mlxlinkLogger;
            _eyeOpener->localPort = _localPort;
            _eyeOpener->depth = _dpn.depth;
            _eyeOpener->pcieIndex = _dpn.pcieIndex;
            _eyeOpener->node = _dpn.node;
            _eyeOpener->portType = _portType;
            _eyeOpener->numOfLanes = _userInput._pcie? _numOfLanesPcie : _numOfLanes;
            _eyeOpener->lane = _userInput.gradeScanPerLane? _userInput._lane : -1 ;
            _eyeOpener->pciePort = _userInput._pcie;
            _eyeOpener->isPam4Speed = _isPam4Speed ||
                    ((_linkSpeed == IB_LINK_SPEED_HDR) && (_protoActive == IB));
            _eyeOpener->activeSpeedStr = _speedStrG;

            if (_userInput.measureTime < 0) {
                if (_userInput._pcie) {
                    _userInput.measureTime = DFLT_MSUR_TIME_PCIE;
                } else {
                    _userInput.measureTime = DFLT_MSUR_TIME_PORT;
                }
            }
            _eyeOpener->setMeasureTime(_userInput.measureTime);
            _eyeOpener->setEyeSel(_userInput.eyeSelect);
            _eyeOpener->setNonInteractiveMode(_userInput.force);

            _eyeOpener->enableGradeScan();
        } else {
            throw MlxRegException("port must be active");
        }
    } catch (MlxRegException &exc) {
        _allUnhandledErrors += string("Reading SerDes receive eye grade raised the following"\
                 " exception:\n") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::initErrInj()
{
    try {
        gearboxBlock(PREI_RX_ERR_INJ_FLAG);

        if (!_isHCA) {
            throw MlxRegException("This feature supporting NIC's only");
        }
        if (_productTechnology != PRODUCT_28NM) {
            throw MlxRegException("This feature supporting 28nm products only");
        }
        if (_prbsTestMode) {
            throw MlxRegException("This feature not working while PRBS test mode is active");
        }
        if (!_linkUP) {
            throw MlxRegException("Port must be active");
        }
        if (!isSpeed25GPerLane(_activeSpeed, _protoActive)) {
            throw MlxRegException("This feature supporting 25G per lane speeds only");
        }
        if (_fecActive != FEC_MODE_NO_FEC) {
            throw MlxRegException("This feature supporting links running with NO-FEC only");
        }

        _errInjector = new MlxlinkErrInjCommander(_jsonRoot);
        _errInjector->_regLib = _regLib;
        _errInjector->_mlxlinkLogger = _mlxlinkLogger;
        _errInjector->_localPort = _localPort;
        _errInjector->_force = _userInput.force;

        if (_userInput.mixerOffset0 >= 0 || _userInput.mixerOffset1 >= 0) {
            _errInjector->_mixerOffset0 = _userInput.mixerOffset0;
            _errInjector->_mixerOffset1 = _userInput.mixerOffset1;
            _errInjector->updateMixerOffsets();
        } else {
            _errInjector->showMixersOffset();
        }

    } catch (MlxRegException &exc) {
        _allUnhandledErrors += string("Reading RX error injection raised the following"\
                 " exception:\n") + string(exc.what()) + string("\n");
    }
}

bool MlxlinkCommander::isPPHCRSupported()
{
    bool supported = true;
    try {
        string regName = "PPHCR";
        resetParser(regName);
        updateField("local_port", 1);
        updateField("pnat", 1);

        genBuffSendRegister(PPHCR_REG, MACCESS_REG_METHOD_GET);
    } catch (MlxRegException &exc) {
        supported = false;
    }
    return supported;
}

void MlxlinkCommander::initPortInfo()
{
    try {
         if (!isPPHCRSupported()) {
             throw MlxRegException("FEC Histogram is not supported for the current device");
         }
         if (_userInput._pcie) {
             throw MlxRegException("FEC Histogram is not available for PCIe links");
         }
         if (_prbsTestMode) {
             throw MlxRegException("FEC Histogram is valid with normal link operation only");
         }
         if (!_linkUP) {
             throw MlxRegException("FEC Histogram is valid with active link operation only");
         }

         _portInfo = new MlxlinkPortInfo(_jsonRoot);
         _portInfo->_regLib = _regLib;
         _portInfo->_mlxlinkLogger = _mlxlinkLogger;
         _portInfo->_localPort = _localPort;
         _portInfo->_portType = _portType;
         _portInfo->_fecActive = _fecActive;
         _portInfo->init();

         if (_userInput.showFecHistogram) {
             _portInfo->showHistogram();
         } else if (_userInput.clearFecHistogram) {
             _portInfo->clearHistogram();
         }
     } catch (MlxRegException &exc) {
         _allUnhandledErrors += string("Providing FEC histogram cause the following"\
                  " exception:\n") + string(exc.what()) + string("\n");
     }
}

void MlxlinkCommander::setAmBerCollectorFields()
{
    _amberCollector->_regLib = _regLib;
    _amberCollector->_mlxlinkLogger = _mlxlinkLogger;
    _amberCollector->_pnat = _userInput._pcie ? PNAT_PCIE : PNAT_LOCAL;
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
    _amberCollector->_mstDevName = _device;
}


void MlxlinkCommander::initAmBerCollector()
{
    if (!_amberCollector) {
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
    _pcieInfoCmd.toJsonFormat(_jsonRoot);
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

    bool errorExist = _allUnhandledErrors != "";
    _jsonRoot[JSON_STATUS_SECTION][JSON_STATUS_CODE] = errorExist? 1 : 0;
    _jsonRoot[JSON_STATUS_SECTION][JSON_MSG] = errorExist?
                                    _allUnhandledErrors : "success";

    if (!_jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION]) {
        _jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION] = "N/A";
    }
}

