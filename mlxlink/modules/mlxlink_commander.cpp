/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
    _splitted = false;
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
    _uniqueCmds = 0;
    _networkCmds = 0;
    _activeSpeed = 0;
    _activeSpeedEx = 0;
    _protoCapability = 0;
    _linkSpeed = 0;
    _protoCapabilityEx = false;
    _ddmSupported = false;
    _cmisCable = false;
    _qsfpCable = false;
    _mngCableUnplugged = false;
    _isPam4Speed = false;
    _ignorePortType = true;
    _lanesLockStatus = false;
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

void MlxlinkCommander::validatePortType(const string &portTypeStr)
{
    if (portTypeStr != "NETWORK" && portTypeStr != "PCIE") {
        throw MlxRegException(
                  "Please provide a valid Port Type [NETWORK(Default)/PCIE]");
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
        updatePortType();
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
        updatePortType();

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
        string regName = "SLRG";
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);
        updateField("pnat", (_userInput._pcie) ? PNAT_PCIE : PNAT_LOCAL);

        genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

        _productTechnology = getVersion(getFieldValue("version"));
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
    case DeviceSpectrum4:
        return MAX_LOCAL_PORT_SPECTRUM2;
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
        } else if (_userInput._specifiedPort){
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
        labelToSpectLocalPort();
    } else if (dm_dev_is_ib_switch(_devID)) {
        labelToIBLocalPort();
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
    if(!_userInput._specifiedPort &&
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
    } else if (_userInput._specifiedPort) {
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
    if (_splitted) {
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
        if ((getFieldValue("lane0_module_mapping") & 0xFF) + 1
                == _userInput._labelPort) {
            checkWidthSplit(localPort);
            if (_splitted) {
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
            if ((getFieldValue("lane0_module_mapping") & 0xFF) + 1
                    == _userInput._labelPort) {
                return;
            }
        }
    }
    throw MlxRegException(
                "Failed to find Local Port, please provide valid Port Number");
}

void MlxlinkCommander::checkWidthSplit(u_int32_t localPort)
{
    if (!_splitted) {
        checkUnSplit(localPort);
        return;
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

void MlxlinkCommander::checkUnSplit(u_int32_t localPort)
{
    if (localPort) {
    }
    return;
    /*if (_numOfLanes == 4) {
       return;
       } else if (_numOfLanes == 2) {
       throw MlxRegException("Port is Splitted! please provide label port and lane, ex: " + convertToString(_labelPort) + "/2");
       } else if (_numOfLanes == 1) {
       //TODO - 4x-1x
       if (localPort) {}
       //throw MlxRegException("Port is Splitted! please provide label port and lane, ex: " + convertToString(_labelPort) + "/4");
       }*/
}

void MlxlinkCommander::labelToIBLocalPort()
{
    u_int32_t labelPort = _userInput._labelPort;
    if (_splitted && _devID != DeviceQuantum && _devID != DeviceQuantum2) {
        throw MlxRegException("No split in IB!");
    }
    bool ibSplitReady = isIBSplitReady();
    if (_devID == DeviceQuantum || _devID == DeviceQuantum2) {
        toIBLabelPort(labelPort, ibSplitReady);
    } else if (labelPort > maxLocalPort()) {
        throw MlxRegException("Invalid port number!");
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
        throw MlxRegException("Port %d is not splitted physically from switch "
                "side, Use this command to split it physically:\n"
                "interface ib <port/ports range> module-type qsfp-split-2",
                _userInput._labelPort);
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

void MlxlinkCommander::toIBLabelPort(u_int32_t &labelPort,bool ibSplitReady)
{
    if (labelPort > (maxLocalPort()-2)/2) {
        throw MlxRegException("Invalid port number!");
    }
    if (ibSplitReady) {
        if (!_splitted) {
            labelPort = (_userInput._labelPort*2) - 1;
        } else {
            switch(_userInput._splitPort){
            case 2:
                labelPort = (_userInput._labelPort*2) - (2-_userInput._splitPort);
                break;
            default:
                throw MlxRegException("Invalid split number!");
            }
        }
    } else if (_splitted) {
        throw MlxRegException("Split mode is not ready!"
                "\nThis command is used to set the split mode ready from switch "
                "side:\nsystem profile ib split-ready");
    }
}

void MlxlinkCommander::checkStrLength(const string &str)
{
    if (str.size() > MAX_LABEL_PORT_LENGTH) {
        throw MlxRegException("Argument: " + str +" is invalid.");
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
        updatePortType();

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
        _moduleNumber = (getFieldValue("lane0_module_mapping") & 0xFF);
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

bool MlxlinkCommander::checkPaosDown()
{
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

u_int32_t MlxlinkCommander::getPtysCap()
{
    string regName = "PTYS";
    resetParser(regName);
    updatePortType();

    updateField("local_port", _localPort);
    updateField("proto_mask", _protoActive);
    updateField("an_disable_admin", 0);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    string proto = (_protoActive == IB) ? "ib" : "eth";
    return getFieldValue(proto + "_proto_capability");
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
        if ((getFieldValue("lane0_module_mapping") & 0xFF) + 1
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
            _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
            break;
        case 8:
            break;
        }
    }
}

void MlxlinkCommander::fillIbPortGroupMap(u_int32_t localPort,u_int32_t labelPort,
        u_int32_t group, bool splitReady)
{
    if (splitReady) {
        _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 1));
        _localPortsPerGroup.push_back(PortGroup(localPort+1, labelPort, group, 2));
    } else {
        _localPortsPerGroup.push_back(PortGroup(localPort, labelPort, group, 0));
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
            labelPort = (getFieldValue("lane0_module_mapping") & 0xFF) + 1;
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

void MlxlinkCommander::handleLabelPorts(std::vector<string> labelPortsStr)
{
    u_int32_t labelPort = 0;
    int localPort = -1;
    if (labelPortsStr.size() > maxLocalPort()) {
        throw MlxRegException("The number of ports is invalid");
    }
    bool ibSplitReady = (_devID == DeviceQuantum || _devID == DeviceQuantum2)? isIBSplitReady() : false;
    bool spect2WithGb = (_devID == DeviceSpectrum2)? isSpect2WithGb() : false;
    for (vector<string>::iterator it = labelPortsStr.begin();
            it != labelPortsStr.end(); ++it) {
        strToUint32((char *)(*it).c_str(), labelPort);
        if (_devID == DeviceSpectrum2) {
            localPort = handleEthLocalPort(labelPort, spect2WithGb);
        } else if (_devID == DeviceQuantum || _devID == DeviceQuantum2) {
            localPort = handleIBLocalPort(labelPort, ibSplitReady);
        }
        if (localPort < 0) {
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
                            cableVendor != MELLANOX);
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
            getCableLengthStr(cableLength, _cmisCable), ANSI_COLOR_RESET, true, valid);
}

void MlxlinkCommander::prepareAttenuationAndFwSection(bool valid)
{
    string cableAttenuation = "N/A";
    string attenuationTitle = "Attenuation (5g,7g,12g";
    string moduleFWVersion = "N/A";
    bool passive = _cableMediaType == PASSIVE;
    if (_cmisCable) {
        attenuationTitle += ",25g";
    }
    attenuationTitle += ") [dB]";
    if (_cableIdentifier != IDENTIFIER_SFP) {
        if (passive) {
            cableAttenuation = getFieldStr("cable_attenuation_5g") + ","
                    + getFieldStr("cable_attenuation_7g") + ","
                    + getFieldStr("cable_attenuation_12g");
            if (_cmisCable) {
                cableAttenuation += "," + getFieldStr("cable_attenuation_25g");
            }
        }
        if (!passive) {
            u_int32_t moduleFWVer = getFieldValue("fw_version");
            u_int32_t moduleFWVerChip = (moduleFWVer & 0xFF000000) >> 24;
            u_int32_t moduleFWVerQtr  = (moduleFWVer & 0x00FF0000) >> 16;
            u_int32_t moduleFWVerFree = (moduleFWVer & 0x0000FFFF);
            if (moduleFWVer) {
                moduleFWVersion =  to_string(moduleFWVerChip) + "." +
                                    to_string(moduleFWVerQtr) + "." +
                                    to_string(moduleFWVerFree);
            }
        }
    }

    setPrintVal(_moduleInfoCmd, attenuationTitle,
            cableAttenuation, ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "FW Version",
            moduleFWVersion, ANSI_COLOR_RESET, true, valid);

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
    string powerClassStr = getPowerClass(_mlxlinkMaps,_cableIdentifier, getFieldValue("cable_power_class"),
                                         getFieldValue("max_power"));

    setPrintVal(_moduleInfoCmd, "Digital Diagnostic Monitoring",
            _ddmSupported ? "Yes" : "No", ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd,"Power Class",
            (_plugged && _cableMediaType != PASSIVE) ? powerClassStr : "N/A",
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "CDR RX", _plugged ? rxCdrState : "N/A",
            ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd,"CDR TX", _plugged ? txCdrState : "N/A",
            ANSI_COLOR_RESET, true, valid);
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

string MlxlinkCommander::loopAllLanesStr(vector<AmberField> &fields, string str)
{
    string strVal = "";
    for (u_int32_t lane = 0; lane < LANES_NUM; lane++) {
        string laneStr = to_string(lane);
        strVal += AmberField::getValueFromFields(fields, str + laneStr) + "_";
    }
    strVal = deleteLastChar(strVal);
    return strVal;
}

void MlxlinkCommander::prepareBerModuleInfoNdr(bool valid)
{
    initAmBerCollector();
    _amberCollector->init();

    vector<AmberField> moduleInfoFields =  _amberCollector->getModuleStatus();
    u_int32_t hiLoTempAlarmWarn;
    strToUint32((char *)(AmberField::getValueFromFields(moduleInfoFields, "Temperature Alarm", true).c_str()), hiLoTempAlarmWarn);
    u_int32_t hiTempAlarm = hiLoTempAlarmWarn & 1;
    u_int32_t loTempAlarm = hiLoTempAlarmWarn & 2;
    setPrintVal(_moduleInfoCmd, "Temperature Alarm [hi, low]",
                "[" + to_string(hiTempAlarm) + "," + to_string(loTempAlarm) + "]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    u_int32_t hiTempWarn = hiLoTempAlarmWarn & 4;
    u_int32_t loTempWarn = hiLoTempAlarmWarn & 8;
    setPrintVal(_moduleInfoCmd, "Temperature Warning [hi , low]",
                "[" + to_string(hiTempWarn) + "," + to_string(loTempWarn) + "]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    u_int32_t hiLoVccAlarmWarn;
    strToUint32((char *)(AmberField::getValueFromFields(moduleInfoFields, "Voltage Alarm", true).c_str()), hiLoVccAlarmWarn);
    u_int32_t hiVccAlarm = hiLoVccAlarmWarn & 1;
    u_int32_t loVccAlarm = hiLoVccAlarmWarn & 2;
    setPrintVal(_moduleInfoCmd, "Voltage Alarm [hi , low]",
                "[" + to_string(hiVccAlarm) + "," + to_string(loVccAlarm) + "]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    u_int32_t hiVccWarn = hiLoVccAlarmWarn & 4;
    u_int32_t loVccWarn = hiLoVccAlarmWarn & 8;
    setPrintVal(_moduleInfoCmd, "Voltage Warning",
                "[" + to_string(hiVccWarn) + "," + to_string(loVccWarn) + "]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txBiasHiAlStr = AmberField::getValueFromFields(moduleInfoFields, "tx_bias_hi_al");
    findAndReplace(txBiasHiAlStr, "_", ",");
    string txBiasLoAlStr = AmberField::getValueFromFields(moduleInfoFields, "tx_bias_lo_al");
    findAndReplace(txBiasLoAlStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx bias Alaram [hi, low]",
                "[[" + getStringByActiveLanes(txBiasHiAlStr,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(txBiasLoAlStr,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txBiasHiStr = AmberField::getValueFromFields(moduleInfoFields, "tx_bias_hi_war");
    findAndReplace(txBiasHiStr, "_", ",");
    string txBiasLoStr = AmberField::getValueFromFields(moduleInfoFields, "tx_bias_lo_war");
    findAndReplace(txBiasLoStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx Bias Warning [hi, low]",
                "[[" + getStringByActiveLanes(txBiasHiStr,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(txBiasLoStr,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string rxPowerHiAl = AmberField::getValueFromFields(moduleInfoFields, "rx_power_hi_al");
    findAndReplace(rxPowerHiAl, "_", ",");
    string rxPowerLoAl = AmberField::getValueFromFields(moduleInfoFields, "rx_power_lo_al");
    findAndReplace(rxPowerLoAl, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx power Alaram [hi, low]",
                "[[" + getStringByActiveLanes(rxPowerHiAl,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(rxPowerLoAl,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string rxPowerHighWarStr = AmberField::getValueFromFields(moduleInfoFields, "rx_power_hi_war");
    findAndReplace(rxPowerHighWarStr, "_", ",");
    string rxPowerLowWarStr = AmberField::getValueFromFields(moduleInfoFields, "rx_power_lo_war");
    findAndReplace(rxPowerLowWarStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx power Warning [hi, low]",
                "[[" + getStringByActiveLanes(rxPowerHighWarStr,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(rxPowerLowWarStr,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txPowerHighStr = AmberField::getValueFromFields(moduleInfoFields, "tx_power_hi_al");
    findAndReplace(txPowerHighStr, "_", ",");
    string txPowerLowStr = AmberField::getValueFromFields(moduleInfoFields, "tx_power_lo_al");
    findAndReplace(txPowerLowStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx power Alaram [hi, low]",
                "[[" + getStringByActiveLanes(txPowerHighStr,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(txPowerLowStr,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txPowerHiWarStr = AmberField::getValueFromFields(moduleInfoFields, "tx_power_hi_war");
    findAndReplace(txPowerHiWarStr, "_", ",");
    string txPowerLowWarStr = AmberField::getValueFromFields(moduleInfoFields, "tx_power_lo_war");
    findAndReplace(txPowerLowWarStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx power Warning [hi, low]",
                "[[" + getStringByActiveLanes(txPowerHiWarStr,_numOfLanes) + "]" + ',' + "[" + getStringByActiveLanes(txPowerLowWarStr,_numOfLanes) + "]]",
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string cableWStr = AmberField::getValueFromFields(moduleInfoFields, "ib_width");
    findAndReplace(cableWStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "IB Cable Width",
                cableWStr,
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Memory Map Revision",
                AmberField::getValueFromFields(moduleInfoFields, "Memory map rev"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Linear Direct Drive",
                AmberField::getValueFromFields(moduleInfoFields, "linear direct drive"),
                ANSI_COLOR_RESET, true, valid);
    string cableBreakoutStr = AmberField::getValueFromFields(moduleInfoFields, "cable_breakout");
    findAndReplace(cableBreakoutStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Cable Breakout",
                cableBreakoutStr,
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "SMF Length",
                AmberField::getValueFromFields(moduleInfoFields, "smf_length"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "MAX Power",
                AmberField::getValueFromFields(moduleInfoFields, "max_power"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Rx AMP",
                AmberField::getValueFromFields(moduleInfoFields, "cable_rx_amp"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Rx Emphasis",
                AmberField::getValueFromFields(moduleInfoFields, "cable_rx_emphasis"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Rx Post Emphasis",
                AmberField::getValueFromFields(moduleInfoFields, "cable_rx_post_emphasis"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Cable Tx Equalization",
                AmberField::getValueFromFields(moduleInfoFields, "cable_tx_equalization"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Wavelength Tolerance",
                AmberField::getValueFromFields(moduleInfoFields, "wavelength_tolerance"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Module State",
                AmberField::getValueFromFields(moduleInfoFields, "Module_st"),
                ANSI_COLOR_RESET, true, valid);
    string dpStr = loopAllLanesStr(moduleInfoFields,"dp_st_lane");
    findAndReplace(dpStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "DataPath state [per lane]",
                getStringByActiveLanes(dpStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid);
    string rxOutStr = AmberField::getValueFromFields(moduleInfoFields, "rx_output_valid");
    findAndReplace(rxOutStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx Output Valid",
                getStringByActiveLanes(rxOutStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid);
    string rxInStr = AmberField::getValueFromFields(moduleInfoFields, "rx_input_valid");
    findAndReplace(rxInStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx Input Valid",
                getStringByActiveLanes(rxInStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Nominal bit rate",
                AmberField::getValueFromFields(moduleInfoFields, "nbr250"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Rx Power Type",
                AmberField::getValueFromFields(moduleInfoFields, "Rx Power Type"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Manufacturing Date",
                AmberField::getValueFromFields(moduleInfoFields, "date_code"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Active Set Host Compliance Code",
                AmberField::getValueFromFields(moduleInfoFields, "active_set_host_compliance_code"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Active Set Media Compliance Code",
                AmberField::getValueFromFields(moduleInfoFields, "active_set_media_compliance_code"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Error Code Response",
                AmberField::getValueFromFields(moduleInfoFields, "error_code_response"),
                ANSI_COLOR_RESET, true, valid);
    setPrintVal(_moduleInfoCmd, "Module FW Fault",
                AmberField::getValueFromFields(moduleInfoFields, "Mod_fw_fault"),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    setPrintVal(_moduleInfoCmd, "DataPath FW Fault",
                AmberField::getValueFromFields(moduleInfoFields, "Dp_fw_fault"),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txStr = AmberField::getValueFromFields(moduleInfoFields, "tx_fault");
    findAndReplace(txStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx Fault [per lane]",
                getStringByActiveLanes(txStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txLosStr = AmberField::getValueFromFields(moduleInfoFields, "tx_los");
    findAndReplace(txLosStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx LOS [per lane]",
                getStringByActiveLanes(txLosStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txCdrStr = AmberField::getValueFromFields(moduleInfoFields, "tx_cdr_lol");
    findAndReplace(txCdrStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx CDR LOL [per lane]",
                getStringByActiveLanes(txCdrStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string rxLosStr = AmberField::getValueFromFields(moduleInfoFields, "rx_los");
    findAndReplace(rxLosStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx LOS [per lane]",
                getStringByActiveLanes(rxLosStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string rxCdrLolStr = AmberField::getValueFromFields(moduleInfoFields, "rx_cdr_lol");
    findAndReplace(rxCdrLolStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Rx CDR LOL [per lane]",
                getStringByActiveLanes(rxCdrLolStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);
    string txAdEqFaultStr = AmberField::getValueFromFields(moduleInfoFields, "tx_ad_eq_fault");
    findAndReplace(txAdEqFaultStr, "_", ",");
    setPrintVal(_moduleInfoCmd, "Tx Adaptive EQ Fault [per lane]",
                getStringByActiveLanes(txAdEqFaultStr,_numOfLanes),
                ANSI_COLOR_RESET, true, valid && _ddmSupported);

}

void MlxlinkCommander::showModuleInfo()
{
    try {
        string regName = "PMAOS";
        resetParser(regName);
        updateField("module", _moduleNumber);
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
                    complianceLabel +=
                            getCompliance(extCompliance, _mlxlinkMaps->_cableComplianceExt);
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
    sltpLanes[laneNumber].push_back(to_string(readSignedByte(getFieldValue("ob_m2lp"))));
    sltpLanes[laneNumber].push_back(getFieldStr("ob_amp"));
}

void MlxlinkCommander::prepareSltp7nm(std::vector<std::vector<string> > &sltpLanes,
        u_int32_t laneNumber)
{
    // Arch is not ready, update once we get final arch by end of Feb.21
    (void) sltpLanes;
    (void) laneNumber;
    /*sltpLanes[laneNumber].push_back(getFieldStr("fir_pre1"));
    sltpLanes[laneNumber].push_back(getFieldStr("fir_pre2"));
    sltpLanes[laneNumber].push_back(getFieldStr("fir_pre3"));
    sltpLanes[laneNumber].push_back(getFieldStr("fir_post1"));
    sltpLanes[laneNumber].push_back(getFieldStr("drv_amp"));
    sltpLanes[laneNumber].push_back(getFieldStr("tx_fir_scale_ctrl"));
    sltpLanes[laneNumber].push_back(getFieldStr("fir_c0"));
    */
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
        _linkUP = (phyMngrFsmState == PHY_MNGR_ACTIVE_LINKUP || phyMngrFsmState == PHY_MNGR_PHYSICAL_LINKUP);
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
        string color = MlxlinkRecord::state2Color(phyMngrFsmState);
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
        if (_productTechnology >= PRODUCT_16NM) {
            _protoCapabilityEx = true;
        }
        stringstream value;
        value << "0x" << std::hex << setfill('0') << setw(8) << speeds_mask \
                << " (" << supported_speeds << ")" << setfill(' ');
        string extStr = "";
        if (_protoCapabilityEx && _protoActive == ETH) {
            extStr = " (Ext.)";
        }
        string title = "Enabled Link Speed" + extStr;
        setPrintVal(_supportedInfoCmd, title,
                value.str(),color, true, !_prbsTestMode, true);
        // Supported cable speed
        supported_speeds = SupportedSpeeds2Str(_protoActive, _protoCapability,
                _protoCapabilityEx);
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
        if (_prbsTestMode) {
            showTestMode();
        } else {
            std::cout << _operatingInfoCmd;
            std::cout << _supportedInfoCmd;
            std::cout << _troubInfoCmd;
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
        if (_productTechnology < PRODUCT_16NM) {
            _protoCapability = getFieldValue("eth_proto_capability");
        }
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
    pprtMap["pprtLockStatus"] = prbsMaskToLockStatus(statusMask, numOfLanesToUse, _lanesLockStatus);
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

void MlxlinkCommander::showBer()
{
    if (_userInput._pcie){
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

        setPrintTitle(_berInfoCmd,"Physical Counters and BER Info", BER_INFO_LAST);

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

        if (_protoActive == IB) {
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
    setPrintVal(_testModeBerInfoCmd, "PRBS Errors", getStringFromVector(errors),
            ANSI_COLOR_RESET, true, _lanesLockStatus, true);
    setPrintVal(_testModeBerInfoCmd, "PRBS BER",
            getFieldStr("raw_ber_coef") + "E-" + getFieldStr("raw_ber_magnitude"),
            ANSI_COLOR_RESET, true, _lanesLockStatus, true);

    cout <<_testModeBerInfoCmd;
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
            MPCNT_PERFORMANCE_INFO_LAST);
    setPrintVal(_mpcntPerfInfCmd, "RX Errors",getFieldStr("rx_errors"));
    setPrintVal(_mpcntPerfInfCmd, "TX Errors",getFieldStr("tx_errors"));
    setPrintVal(_mpcntPerfInfCmd, "CRC Error dllp",getFieldStr("crc_error_dllp"));
    setPrintVal(_mpcntPerfInfCmd, "CRC Error tlp",getFieldStr("crc_error_tlp"));

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
        } else if (_validDpns.size() > 1 && !_userInput._specifiedPort){
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
    (void) numOfLanesToUse;
    /*
     * TODO: implement NDR eye information
     */
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

void MlxlinkCommander::showFEC()
{
    try {
        /*string regName = "PPLM";
           //std::vector<u_int32_t> _buffer;
           //RegAccessParser parser = getRegAccessParser(regName);
           //resetParser(regName);

           updateField("local_port", _localPort);

           genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
           u_int32_t FECSupported100G = getFieldValue("fec_override_cap_100g");
           u_int32_t FECSupported25G50G = getFieldValue("fec_override_cap_50g");
           u_int32_t FECAdmin100G = getFieldValue("fec_override_admin_100g");
           u_int32_t FECAdmin25G50G = getFieldValue("fec_override_admin_50g");

           u_int32_t FEC100G = (FECAdmin100G) ? FECAdmin100G : FECSupported100G;
           u_int32_t FEC25G50G = (FECAdmin25G50G) ? FECAdmin25G50G : FECSupported25G50G;

           std::vector<string> showFecValues;
           showFecValues.push_back("0x" + convertIntToHexString(FEC100G) + " (" + FEC2Str100G(FEC100G) + ")");
           showFecValues.push_back("0x" + convertIntToHexString(FEC25G50G) + " (" + FEC2Str50G25G(FEC25G50G) + ")");
           showFecValues.push_back("0x" + convertIntToHexString(_fecModeRequest) + " (" + FECReq2Str(_fecModeRequest, _linkUP) + ")");
           printCmdOutput(_showFecTitle, _showFecLines, showFecValues);*/
        string fecCap100,fecCap50,fecCap40,fecCap25,fecCap10;
        if (_protoActive == IB || _prbsTestMode) {
            fecCap100 = "0x0 (N/A)";
            fecCap50 = "0x0 (N/A)";
            fecCap40 = "0x0 (N/A)";
            fecCap25 = "0x0 (N/A)";
            fecCap10 = "0x0 (N/A)";
        } else {
            string supportedSpeeds = EthSupportedSpeeds2Str(getPtysCap());
            if (supportedSpeeds.find("100G") != string::npos) {
                if (_devID == DeviceConnectX4) {
                    fecCap100 = "0x4 (RS-FEC(528,514))";
                } else {
                    fecCap100 = "0x5 (No-FEC, RS-FEC(528,514))";
                }
            } else {
                fecCap100 = "0x0 (N/A)";
            }
            if (supportedSpeeds.find("50G") != string::npos) {
                fecCap50 = "0x7 (No-FEC, FireCode FEC, RS-FEC(528,514))";
            } else {
                fecCap50 = "0x0 (N/A)";
            }
            if (supportedSpeeds.find("40G") != string::npos) {
                fecCap40 = "0x3 (No-FEC, FireCode FEC)";
            } else {
                fecCap40 = "0x0 (N/A)";
            }
            if (supportedSpeeds.find("25G") != string::npos) {
                fecCap25 = "0x7 (No-FEC, FireCode FEC, RS-FEC(528,514))";
            } else {
                fecCap25 = "0x0 (N/A)";
            }
            if (supportedSpeeds.find("10G") != string::npos) {
                fecCap10 = "0x3 (No-FEC, FireCode FEC)";
            } else {
                fecCap10 = "0x0 (N/A)";
            }
        }

        setPrintTitle(_fecCapInfoCmd, HEADER_FEC_INFO, FEC_CAP_INFO_LASE);
        setPrintVal(_fecCapInfoCmd, "FEC Capability 100GbE", fecCap100,
                ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_fecCapInfoCmd, "FEC Capability 50GbE", fecCap50,
                ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_fecCapInfoCmd, "FEC Capability 40GbE", fecCap40,
                ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_fecCapInfoCmd, "FEC Capability 25GbE", fecCap25,
                ANSI_COLOR_RESET, true, true, true);
        setPrintVal(_fecCapInfoCmd, "FEC Capability 10GbE", fecCap10,
                ANSI_COLOR_RESET, true, true, true);

        cout << _fecCapInfoCmd;

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
        resetParser(regName);
        updatePortType();

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
            _mlxlinkMaps->_sltpHeader = "firPre1,firPre2,firPre3,firPost0,drvAmp,FS Control,fir_c0";
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
            resetParser(regName);
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
            valid = true;
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
        if(!_userInput._sendDpn && !_userInput._specifiedPort) {
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

void MlxlinkCommander::collectBER()
{
    try {
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
        if (_splitted) {
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
        _allUnhandledErrors += string("Collecting BER and producing report raised the following exception: ") + string(exc.what()) + string("\n");
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

void MlxlinkCommander::sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown)
{
    try {
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

    u_int32_t laneRateCap = _mlxlinkMaps->_prbsLaneRate[laneRate].capMask ?
                _mlxlinkMaps->_prbsLaneRate[laneRate].capMask : (u_int32_t)LANE_RATE_EDR_CAP;

    if (!(laneRateCap & getFieldValue("lane_rate_cap"))) {
        throw MlxRegException("Device does not support lane rate " + laneRate + " in physical test mode.");
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
        u_int32_t protoCap = getPtysCap();
        string regName = "PTYS";
        resetParser(regName);
        updatePortType();

        updateField("local_port", _localPort);
        updateField("proto_mask", _protoActive);
        u_int32_t ptysMask = 0x0;
        u_int32_t ptysExtMask = 0x0;
        string proto = (_protoActive == IB) ? "ib" : "eth";
        for (u_int32_t i = 0; i < _ptysSpeeds.size(); i++) {
            if (_protoActive == ETH && _productTechnology >= PRODUCT_16NM) {
                ptysExtMask |= ptysSpeedToExtMask(_ptysSpeeds[i]);
            } else {
                ptysMask |= ptysSpeedToMask(_ptysSpeeds[i], protoCap);
            }
        }

        if (_linkModeForce == true) {
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
                updateField("ext_eth_proto_admin", ptysExtMask);
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

u_int32_t MlxlinkCommander::ptysSpeedToExtMask(const string & speed)
{
    checkSupportedSpeed(speed, _protoCapability, true);
    if(_protoActive == IB)
        return ptysSpeedToMask(speed, _protoActive);
    return ptysSpeedToExtMaskETH(speed);
}

u_int32_t MlxlinkCommander::ptysSpeedToMask(const string & speed, u_int32_t protoCap)
{
    checkSupportedSpeed(speed, protoCap);
    return (_protoActive == IB) ?
           ptysSpeedToMaskIB(speed) : ptysSpeedToMaskETH(speed);
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
        if (_protoActive == IB) {
            throw MlxRegException("FEC Configuration is Valid for ETHERNET only!");
        }
        if (!_linkUP && _userInput._speedFec == "") {
            throw MlxRegException("When Port is Not Active, You Must Specify the Speed to Configure FEC (--fec_speed <speed>)");
        }

        checkPplmCap();

        string regName = "PPLM";
        resetParser(regName);
        updatePortType();
        updateField("local_port", _localPort);

        string fecSpeed = toLowerCase(_userInput._speedFec);
        string speedStrG = (_linkUP && _userInput._speedFec == "") ?
                                 speedToStr(_speedStrG, _numOfLanes) : fecSpeed;

        if (speedStrG != "100g") {
            updateField("fec_override_admin_100g", 0);
        }
        if (speedStrG != "50g" && speedStrG != "25g") {
            updateField("fec_override_admin_50g", 0);
            updateField("fec_override_admin_25g", 0);
        }
        if (speedStrG != "10g" && speedStrG != "40g") {
            updateField("fec_override_admin_10g_40g", 0);
        }
        if (speedStrG == "10g" || speedStrG == "40g") {
            speedStrG = "10g_40g";
        }
        if (speedStrG != "56g") {
            updateField("fec_override_admin_56g", 0);
        }
        string fieldToUpdate = "fec_override_admin_" + speedStrG;
        updateField(fieldToUpdate, fecToBit(_userInput._pplmFec, speedStrG));
        if (speedStrG == "50g") {
            updateField("fec_override_admin_25g", fecToBit(_userInput._pplmFec, speedStrG));
        } else if (speedStrG == "25g") {
            updateField("fec_override_admin_50g", fecToBit(_userInput._pplmFec, speedStrG));
        }
        genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
    } catch (const std::exception &exc) {
        _allUnhandledErrors += string("Sending PPLM (Configuring port FEC) raised the following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::checkPplmCap()
{
    if (_userInput._pplmFec == "AU") {
        return;
    }
    string regName = "PPLM";
    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);
    string speedStrG = (_linkUP && _userInput._speedFec.empty()) ?
            speedToStr(_speedStrG, _numOfLanes) : toLowerCase(_userInput._speedFec);
    string originalSpeed = speedStrG;
    if (speedStrG == "10g" || speedStrG == "40g") {
        speedStrG = "10g_40g";
    }
    if (!(fecToBit(_userInput._pplmFec, speedStrG) & getFieldValue("fec_override_cap_" + speedStrG))) {
        throw MlxRegException(FEC2Str(_userInput._pplmFec, speedStrG) +
                " is not supported in " + originalSpeed);
    }
    string supportedSpeeds = EthSupportedSpeeds2Str(getPtysCap());
    if (_linkUP && !_userInput._speedFec.empty() &&
            supportedSpeeds.find(toUpperCase(_userInput._speedFec)) == string::npos) {
        throw MlxRegException("FEC speed " + _userInput._speedFec +
                " is not supported, supported speeds are: [" + supportedSpeeds + "]");
    }
}

void MlxlinkCommander::getSltpAlevOut(u_int32_t lane)
{
    string regName = "SLTP";

    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    _userInput._sltpParams[OB_ALEV_OUT] = getFieldValue("ob_alev_out");
}

void MlxlinkCommander::getSltpRegAndLeva(u_int32_t lane)
{
    string regName = "SLTP";

    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    _userInput._sltpParams[OB_REG] = getFieldValue("ob_reg");
    _userInput._sltpParams[OB_LEVA] = getFieldValue("ob_leva");
}

u_int32_t MlxlinkCommander::getLaneSpeed(u_int32_t lane)
{
    string regName = "SLTP";

    resetParser(regName);
    updatePortType();
    updateField("local_port", _localPort);
    updateField("pnat", PNAT_LOCAL);
    updateField("lane", lane);

    genBuffSendRegister(regName, MACCESS_REG_METHOD_GET);

    return getFieldValue("lane_speed");
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
    } else if (_userInput._advancedMode) {
        sltpParamsSize = PARAMS_40NM_LAST;
    }
    if (_userInput._sltpParams.size() != sltpParamsSize) {
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
    // Arch is not ready, update once we get final arch by end of Feb.21
    /*updateField("fir_pre1", _userInput._sltpParams[FIR_PRE1]);
    updateField("fir_pre2", _userInput._sltpParams[FIR_PRE2]);
    updateField("fir_pre3", _userInput._sltpParams[FIR_PRE3]);
    updateField("fir_post1", _userInput._sltpParams[FIR_POST1]);
    updateField("drv_amp", _userInput._sltpParams[DRV_AMP]);
    updateField("tx_fir_scale_ctrl", _userInput._sltpParams[TX_FIR_SCALE_CTRL]);*/
}

void MlxlinkCommander::sendSltp()
{
    MlxlinkRecord::printCmdLine("Configuring Port Transmitter Parameters", _jsonRoot);
    checkSltpParamsSize();
    string regName = "SLTP";
    if (_userInput._sltpLane && _userInput._lane >= _numOfLanes) {
        throw MlxRegException(
                  "Could Not find Lane " + to_string(_userInput._lane));
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
            resetParser(regName);
            updatePortType();
            updateField("local_port", _localPort);
            updateField("pnat", PNAT_LOCAL);
            updateField("lane_speed", laneSpeed);
            updateField("lane", i);
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
            updateField("c_db", _userInput._db);
            genBuffSendRegister(regName, MACCESS_REG_METHOD_SET);
        }
    } catch (MlxRegException &exc) {
        u_int32_t ob_bad_stat = getFieldValue("ob_bad_stat");
        _allUnhandledErrors += string("Configuring Port "
                "Transmitter Parameters raised the following exception:\n"
                "Failed to send parameter set: ") +
                string( _productTechnology == PRODUCT_16NM ?
                        _mlxlinkMaps->_SLTP16BadSetStatus2Str[ob_bad_stat].c_str() :
                        _mlxlinkMaps->_SLTPBadSetStatus2Str[ob_bad_stat].c_str())+"\n";
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
    if (loopBackVal == PHY_REMOTE_LOOPBACK) {
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
    if (_plugged && !_mngCableUnplugged) {
        _cablesCommander = new MlxlinkCablesCommander(_jsonRoot);
        _cablesCommander->_mf = _mf;
        _cablesCommander->_regLib = _regLib;
        _cablesCommander->_gvmiAddress = _gvmiAddress;
        _cablesCommander->_mlxlinkLogger = _mlxlinkLogger;
        _cablesCommander->_moduleNumber = _moduleNumber;
        _cablesCommander->_localPort = _localPort;
        _cablesCommander->_numOfLanes = _numOfLanes;
        _cablesCommander->_cableIdentifier = _cableIdentifier;
        _cablesCommander->_sfp51Paging = isSFP51Paging();
        _cablesCommander->_passiveQsfp = isPassiveQSFP();
    } else {
        _allUnhandledErrors += "No plugged cable detected";
    }
}

void MlxlinkCommander::showCableDump()
{
    try {
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
        if (_plugged && !_mngCableUnplugged) {
            if (_ddmSupported) {
                vector<MlxlinkCmdPrint> ddmOutput = _cablesCommander->getCableDDM();
                printOuptputVector(ddmOutput);
            } else {
                throw MlxRegException(string("Cable does not support DDM"));
            }
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += string( "Showing DDM info raised the following"\
                " exception: ") + string(exc.what()) + string("\n");
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
        MlxlinkRecord::printCmdLine("Writing To Cable EEPROM", _jsonRoot);
        if (_plugged && !_mngCableUnplugged) {
            vector<u_int8_t> bytesToWrite = validateBytes(_userInput._bytesToWrite);
             _cablesCommander->writeToEEPROM(_userInput._page , _userInput._offset, bytesToWrite);
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += string("Writing cable EEPROM raised the "\
                "following exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::readCableEEPROM()
{
    try {
        if (_plugged && !_mngCableUnplugged) {
            MlxlinkCmdPrint bytesOutput =
                    _cablesCommander->readFromEEPRM(_userInput._page , _userInput._offset, _userInput._len);
            cout << bytesOutput;
        }
    } catch(MlxRegException &exc) {
        _allUnhandledErrors += string("Reading cable EEPROM raised the following"\
                " exception: ") + string(exc.what()) + string("\n");
    }
}

void MlxlinkCommander::initEyeOpener()
{
    try {
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
}

void MlxlinkCommander::initAmBerCollector()
{
    _amberCollector = new MlxlinkAmBerCollector(_jsonRoot);
    setAmBerCollectorFields();
}

void MlxlinkCommander::prepareJsonOut()
{
    _operatingInfoCmd.toJsonFormat(_jsonRoot);
    _supportedInfoCmd.toJsonFormat(_jsonRoot);
    _troubInfoCmd.toJsonFormat(_jsonRoot);
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

