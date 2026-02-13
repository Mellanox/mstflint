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

#include "mlxlink_ui.h"
#include <mlxreg/mlxreg_lib/mlxreg_parser.h>
#include <pci_library/PCILibrary.h>
MlxlinkUi::MlxlinkUi() : CommandLineRequester(MLXLINK_EXEC " OPTIONS"), _cmdParser(MLXLINK_EXEC)
{
    _mlxlinkCommander = nullptr;
    _mf = nullptr;
}

MlxlinkUi::~MlxlinkUi()
{
    if (_mlxlinkCommander)
    {
        delete _mlxlinkCommander;
    }
}

void MlxlinkUi::createMlxlinkCommander()
{
    _mlxlinkCommander = new MlxlinkCommander();
}

void MlxlinkUi::initRegAccessLib()
{
    MlxRegLib::isAccessRegisterSupported(_mf);

    _mlxlinkCommander->_mf = _mf;

    _mlxlinkCommander->_regLib =
      new MlxRegLib(_mlxlinkCommander->_mf, _mlxlinkCommander->_extAdbFile, _mlxlinkCommander->_useExtAdb);

    _mlxlinkCommander->_userInput = _userInput;

    if (_mlxlinkCommander->_regLib->isIBDevice() &&
        !_mlxlinkCommander->_regLib->isAccessRegisterGMPSupported(MACCESS_REG_METHOD_GET))
    {
        MlxlinkRecord::printWar("Warning: AccessRegisterGMP Get() method is not supported.\n"
                                "         mlxlink has limited functionality",
                                _mlxlinkCommander->_jsonRoot);
    }

    _mlxlinkCommander->_gvmiAddress = _userInput._gvmiAddress;
    _mlxlinkCommander->_devID = _mlxlinkCommander->_regLib->getDevId();
    _mlxlinkCommander->_isHCA = dm_dev_is_hca(_mlxlinkCommander->_devID);
    if (_mlxlinkCommander->_isHCA)
    {
        _mlxlinkCommander->_isDPNvSupported = _mlxlinkCommander->checkDPNvSupport();
        dynamic_cast<MlxlinkCommander*>(_mlxlinkCommander)->setPlaneIndex(_userInput.planeIndex);
    }
}

bool MlxlinkUi::isSwitch()
{
    return !_mlxlinkCommander->_isHCA;
}

void MlxlinkUi::updateSysFsPath(string& sysfsPath)
{
    if (sysfsPath.empty())
    {
        // based on arch only asic0 is possible at the moment : "/sys/module/sx_core/asic0/module#/".
        sysfsPath = SW_CONTROLLED_MODULE_PATH + to_string(_mlxlinkCommander->_moduleNumber);
    }
}
void MlxlinkUi::initPortInfo()
{
    if (isSwitch() && ((!_userInput._portSpecified && _userInput._csvBer != "") ||
                       (_userInput._showMultiPortInfo || _userInput._showMultiPortModuleInfo)))
    {
        _mlxlinkCommander->findFirstValidPort();
    }

    // only init PCI domain for "--port_type PCIE --show_links" command.
    if (_userInput._pcie && _userInput._links && !isSwitch())
    {
        initPCIDomain();
    }

    _mlxlinkCommander->labelToLocalPort();
    _mlxlinkCommander->validatePortType(_userInput._portType);
    _mlxlinkCommander->updateSwControlStatus();
    if (!_userInput._pcie)
    {
        _mlxlinkCommander->checkValidFW();
    }
    if (!(_mlxlinkCommander->_mf->tp == MST_PCICONF && (dm_is_gpu(static_cast<dm_dev_id_t>(_mlxlinkCommander->_devID)))))
    {
        _mlxlinkCommander->getProductTechnology();
    }
    if (!_userInput._pcie)
    {
        _mlxlinkCommander->_prbsTestMode = _mlxlinkCommander->inPrbsTestMode();
        if (!_mlxlinkCommander->_isSwControled &&
            (_userInput._networkCmds != 0 || _userInput._ddm || _userInput._dump || _userInput._write ||
             _userInput._read || _userInput.isModuleConfigParamsProvided || _userInput.isPrbsSelProvided ||
             _userInput._csvBer != ""))
        {
            _mlxlinkCommander->getCableParams();
        }
        if (_mlxlinkCommander->_isSwControled && _userInput._sysfsPath.empty())
        {
            updateSysFsPath(_mlxlinkCommander->_userInput._sysfsPath);
        }
    }
    else if (!_userInput._sendDpn)
    {
        _mlxlinkCommander->initValidDPNList();
    }
    _mlxlinkCommander->updateDPNDomain();
}

void MlxlinkUi::initMlxlinkCommander()
{
    createMlxlinkCommander();

    initRegAccessLib();

    initPortInfo();
}

void MlxlinkUi::printSynopsisHeader()
{
    printf(IDENT "NAME:\n" IDENT2 MLXLINK_EXEC "\n\n" IDENT "SYNOPSIS:\n" IDENT2 MLXLINK_EXEC " [OPTIONS]\n\n" IDENT
                 "DESCRIPTION:\n" IDENT2 "The " MLXLINK_EXEC
                 " tool is used to check and debug link status and issues related to them.\n" IDENT2
                 "The tool can be used on different links and cables (passive, active, transceiver and backplane).\n");
    printf("\n");
    printf(IDENT "OPTIONS:\n");
    MlxlinkRecord::printFlagLine(HELP_FLAG_SHORT, HELP_FLAG, "", "Display help message.");
    MlxlinkRecord::printFlagLine(VERSION_FLAG_SHORT, VERSION_FLAG, "", "Display version info.");
    MlxlinkRecord::printFlagLine(DEVICE_FLAG_SHORT, DEVICE_FLAG, "device",
                                 "Perform operation for a specified mst device");
    MlxlinkRecord::printFlagLine(LABEL_PORT_FLAG_SHORT, LABEL_PORT_FLAG, "port_number", "Port Number");
    MlxlinkRecord::printFlagLine(PORT_TYPE_FLAG_SHORT, PORT_TYPE_FLAG, "port_type",
                                 "Port Type [NETWORK(Default)/PCIE]");
    MlxlinkRecord::printFlagLine(DEPTH_FLAG_SHORT, DEPTH_FLAG, "depth",
                                 "depth level of the DUT of some hierarchy (PCIE only)");
    MlxlinkRecord::printFlagLine(PCIE_INDEX_FLAG_SHORT, PCIE_INDEX_FLAG, "pcie_index",
                                 "PCIe index number (Internal domain index) (PCIE only)");
    MlxlinkRecord::printFlagLine(NODE_FLAG_SHORT, NODE_FLAG, "node", "the node within each depth (PCIE only)");
    MlxlinkRecord::printFlagLine(PRINT_JSON_OUTPUT_FLAG_SHORT, PRINT_JSON_OUTPUT_FLAG, "",
                                 "Print the output in json format");
}

void MlxlinkUi::printSynopsisQueries()
{
    printf(IDENT "QUERIES:\n");
    MlxlinkRecord::printFlagLine(PCIE_LINKS_FLAG_SHORT, PCIE_LINKS_FLAG, "", "Show valid PCIe links (PCIE only)");
    MlxlinkRecord::printFlagLine(PLR_INFO_FLAG_SHORT, PLR_INFO_FLAG, "", "Show PLR Info");
    MlxlinkRecord::printFlagLine(KR_INFO_FLAG_SHORT, KR_INFO_FLAG, "", "Show KR Info");
    MlxlinkRecord::printFlagLine(MODULE_INFO_FLAG_SHORT, MODULE_INFO_FLAG, "", "Show Module Info");
    MlxlinkRecord::printFlagLine(BER_FLAG_SHORT, BER_FLAG, "", "Show Physical Counters and BER Info");
    MlxlinkRecord::printFlagLine(EYE_OPENING_FLAG_SHORT, EYE_OPENING_FLAG, "", "Show Eye Opening Info");
    MlxlinkRecord::printFlagLine(FEC_DATA_FLAG_SHORT, FEC_DATA_FLAG, "", "Show FEC Capabilities");
    MlxlinkRecord::printFlagLine(SLTP_SHOW_FLAG_SHORT, SLTP_SHOW_FLAG, "", "Show Transmitter Info");
    MlxlinkRecord::printFlagLine(RX_RECOVERY_COUNTERS_FLAG_SHORT, RX_RECOVERY_COUNTERS_FLAG, "",
                                 "Show Rx Recovery Counters");
    MlxlinkRecord::printFlagLine(
      SHOW_TX_GROUP_MAP_FLAG_SHORT, SHOW_TX_GROUP_MAP_FLAG, "group_num",
      "Display all label ports mapped to group <group_num> (for Spectrum-2 and Quantum devices)");
    MlxlinkRecord::printFlagLine(DEVICE_DATA_FLAG_SHORT, DEVICE_DATA_FLAG, "", "General Device Info");
    MlxlinkRecord::printFlagLine(BER_MONITOR_INFO_FLAG_SHORT, BER_MONITOR_INFO_FLAG, "",
                                 "Show BER Monitor Info (not supported for HCA)");
    MlxlinkRecord::printFlagLine(PEPC_SHOW_FLAG_SHORT, PEPC_SHOW_FLAG, "",
                                 "Show External PHY Info (for Ethernet switches only)");
    MlxlinkRecord::printFlagLineWithAcronym(MULTI_PORT_INFO_FLAG_SHORT, MULTI_PORT_INFO_FLAG,
                                            MULTI_PORT_INFO_ACRONYM_FLAG_SHORT, MULTI_PORT_INFO_ACRONYM_FLAG, "",
                                            "Show Multi Port Info Table");
    MlxlinkRecord::printFlagLineWithAcronym(
      MULTI_PORT_MODULE_INFO_FLAG_SHORT, MULTI_PORT_MODULE_INFO_FLAG, MULTI_PORT_MODULE_INFO_ACRONYM_FLAG_SHORT,
      MULTI_PORT_MODULE_INFO_ACRONYM_FLAG, "", "Show Multi Port Module Info Table");
}

void MlxlinkUi::printSynopsisCommands()
{
    printf(IDENT "COMMANDS:\n");
    MlxlinkRecord::printFlagLine(PAOS_FLAG_SHORT, PAOS_FLAG, "port_state",
                                 "Configure Port State [UP(up)/DN(down)/TG(toggle)]");
    MlxlinkRecord::printFlagLine(PMAOS_FLAG_SHORT, PMAOS_FLAG, "module_state",
                                "Configure Module State [UP(up)/DN(down)/TG(toggle)]");
    MlxlinkRecord::printFlagLine(
      PTYS_FLAG_SHORT, PTYS_FLAG, "speeds",
      "Configure Speeds "
      "[XDR,NDR,HDR,EDR,FDR10,FDR,QDR,DDR,SDR,1600G_8X,800G_4X,400G_2X,200G_1X,800G_8X,400G_4X,200G_2X,100G_1X,400G_8X,200G_4X,100G_2X,"
      "50G_1X,100G,100G_4X,50G,50G_2X,25G,40G,10G,2.5G,1G]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PTYS_LINK_MODE_FORCE_FLAG_SHORT, PTYS_LINK_MODE_FORCE_FLAG, "",
                                 "Configure Link Mode Force (Disable AN)");
    MlxlinkRecord::printFlagLine(
      PPLR_FLAG_SHORT, PPLR_FLAG, "loopback",
      "Configure Loopback Mode [NO(no loopback)/RM(phy remote Rx-to-Tx loopback)/PH(internal phy Tx-to-Rx "
      "loopback)/EX(external loopback connector needed)/LL(link layer local loopback)]");
    MlxlinkRecord::printFlagLine(
      PPLM_FLAG_SHORT, PPLM_FLAG, "fec_override",
      "Configure FEC [AU(Auto)/NF(No-FEC)/FC(FireCode "
      "FEC)/RS(RS-FEC)/LL(LL-RS-FEC)/DF-RS(Interleaved_RS-FEC)/DF-LL(Interleaved_LL_RS-FEC)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(FEC_SPEED_FLAG_SHORT, FEC_SPEED_FLAG, "fec_speed",
                                 "Speed to Configure FEC "
                                 "[100G,56G,50G,40G,25G,10G,1600G_8X,800G_4X,400G_2X,200G_1X,800G_8X,400G_4x,400G_8X,200G_2X,200G_4X,100G_2X,50G_1X,"
                                 "100G_4X] (Default is Active Speed)");
    MlxlinkRecord::printFlagLine(SLTP_SET_FLAG_SHORT, SLTP_SET_FLAG, "params",
                                 "Configure Transmitter Parameters. "
                                 "For 7nm devices (lane rate specifies the valid Parameters): "
                                 "[fir_pre3,fir_pre2,fir_pre1,fir_main,fir_post1], "
                                 "For 16nm devices: [pre2Tap,preTap,mainTap,postTap,m2lp,amp], "
                                 "For 28nm devices: [Pol,tap0,tap1,tap2,bias,preemp_mode]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(LANE_FLAG_SHORT, LANE_FLAG, "transmitter_lane",
                                 "Transmitter Lane to Set (Optional - Default All Lanes)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(DATABASE_FLAG_SHORT, DATABASE_FLAG, "",
                                 "Save Transmitter Configuration for Current Speed Permanently (Optional)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(
      SLTP_TX_POLICY_FLAG_SHORT, SLTP_TX_POLICY_FLAG, "",
      "Set the parameters according to Data Base only, otherwise it will be set according to the best possible "
      "configuration chosen by the system (e.g. KR-startup) (Optional)");
    MlxlinkRecord::printFlagLine(SET_TX_GROUP_MAP_FLAG_SHORT, SET_TX_GROUP_MAP_FLAG, "group_num",
                                 "Map ports to group <group_num> (for Spectrum-2 and Quantum devices)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(TX_GROUP_PORTS_FLAG_SHORT, TX_GROUP_PORTS_FLAG, "ports",
                                 "Ports to be mapped [1,2,3,4,...,128]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(LINK_TRAINING_FLAG_SHORT, LINK_TRAINING_FLAG, "link_training",
                                 "Link Training [EN(enable)/DS(disable)/EN_EXT(enable_extra)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PHY_RECOVERY_FLAG_SHORT, PHY_RECOVERY_FLAG, "phy_recovery",
                                 "PHY Recovery [EN(enable)/DS(disable)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PHY_RECOVERY_TYPE_FLAG_SHORT, PHY_RECOVERY_TYPE_FLAG, "recovery_type",
                                 "PHY Recovery Type [host_serdes_feq/host_logic_re_lock]");
    MlxlinkRecord::printFlagLine(PRBS_MODE_FLAG_SHORT, PRBS_MODE_FLAG, "prbs_mode",
                                 "Physical Test Mode Configuration [EN(enable)/DS(disable)/TU(perform tuning)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPRT_PRBS_FLAG_SHORT, PPRT_PRBS_FLAG, "rx_prbs_mode",
                                 "RX PRBS Mode "
                                 "[PRBS31/PRBS23A/PRBS23B/PRBS23C/PRBS23D/PRBS7/PRBS11/PRBS11A/PRBS11B/PRBS11C/PRBS11D/"
                                 "PRBS9/IDLE/SQUARE_WAVEA/SQUARE_WAVEB/SQUARE_WAVEC/SQUARE_WAVED/PRBS13A/PRBS13B/"
                                 "PRBS13C/PRBS13D/SSPR/SSPRQ/LT_frames/PRBS15/PRBS28] (Optional - Default PRBS31)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPRT_MODULATION_FLAG_SHORT, PPRT_MODULATION_FLAG, "rx_modulation",
                                 "RX Modulation [NRZ/PAM4/PAM4_PRECODING/PAM4_NO_GRAY] (Optional - Default based on lane rate)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(
      PPTT_MODULATION_FLAG_SHORT, PPTT_MODULATION_FLAG, "tx_modulation",
      "TX Modulation [NRZ/PAM4/PAM4_PRECODING/PAM4_NO_GRAY] (Optional - Default based on lane rate)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(
      PPTT_PRBS_FLAG_SHORT, PPTT_PRBS_FLAG, "tx_prbs_mode",
      "TX PRBS Mode "
      "[PRBS31/PRBS23A/PRBS23B/PRBS23C/PRBS23D/PRBS7/PRBS11/PRBS11A/PRBS11B/PRBS11C/PRBS11D/PRBS9/IDLE/SQUARE_WAVEA/"
      "SQUARE_WAVEB/SQUARE_WAVEC/SQUARE_WAVED/PRBS13A/PRBS13B/PRBS13C/PRBS13D/SSPR/SSPRQ/LT_frames/PRBS15/PRBS28/"
      "SQUARE_WAVE3,SQUARE_WAVE13,SQUARE_WAVE30] (Optional - Default PRBS31] (Optional - Default PRBS31)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(
      PPRT_RATE_FLAG_SHORT, PPRT_RATE_FLAG, "rx_lane_rate",
      "RX Lane Rate "
      "[XDR,NDR,HDR,EDR,FDR10,FDR,QDR,DDR,SDR,1600G_8X,800G_4X,400G_2X,200G_1X,800G_8X,400G_8X,200G_4X,100G_2X,50G_1X,100G,100G_4X,50G,50G_"
      "2X,25G,40G,10G,2.5G,1G]  (Optional - Default 25G)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(
      PPTT_RATE_FLAG_SHORT, PPTT_RATE_FLAG, "tx_lane_rate",
      "TX Lane Rate "
      "[XDR,NDR,HDR,EDR,FDR10,FDR,QDR,DDR,SDR,1600G_8X,800G_4X,400G_2X,200G_1X,800G_8X,400G_8X,200G_4X,100G_2X,50G_1X,100G,100G_4X,50G,50G_"
      "2X,25G,40G,10G,2.5G,1G]  (Optional - Default 25G)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_INVERT_TX_POL_FLAG_SHORT, PRBS_INVERT_TX_POL_FLAG, "",
                                 "PRBS TX polarity inversion (Optional - Default No Inversion)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_INVERT_RX_POL_FLAG_SHORT, PRBS_INVERT_RX_POL_FLAG, "",
                                 "PRBS RX polarity inversion (Optional - Default No Inversion)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_DC_COUPLE_ALLOW_FLAG_SHORT, PRBS_DC_COUPLE_ALLOW_FLAG, "",
                                 "For DC coupled ports only: This flag must be set to enter test mode");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(FORCE_TX_ALLOWED_FLAG_SHORT, FORCE_TX_ALLOWED_FLAG, "",
                                 "Force TX allowed for PRBS test mode");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(SKIP_POWER_GOOD_CHECK_FLAG_SHORT, SKIP_POWER_GOOD_CHECK_FLAG, "",
                                 "Skip power good check for PRBS test mode");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(SYSFS_PATH_FLAG_SHORT, SYSFS_PATH_FLAG, "path", "Full path to sysfs files");
    printf(IDENT);
   MlxlinkRecord::printFlagLine(
      PRBS_LANES_FLAG_SHORT, PRBS_LANES_FLAG, "lanes",
      "PRBS lanes to set (one or more lane separated by comma)[0,1,2,...,7] (Optional - Default all lanes)");
    MlxlinkRecord::printFlagLine(BER_COLLECT_FLAG_SHORT, BER_COLLECT_FLAG, "csv_file",
                                 "Port Extended Information Collection [CSV File]");
    MlxlinkRecord::printFlagLine(AMBER_COLLECT_FLAG_SHORT, AMBER_COLLECT_FLAG, "csv_file",
                                 "AmBER Port Extended Information Collection For 16nm Products and Later [CSV File]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(BER_LIMIT_FLAG_SHORT, BER_LIMIT_FLAG, "limit_criteria",
                                 "BER Limit Criteria [Nominal(Default)/Corner/Drift] (Optional - Default Nominal)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(ITERATION_FLAG_SHORT, ITERATION_FLAG, "iteration",
                                 "Iteration Number of BER Collection");
    MlxlinkRecord::printFlagLine(PPCNT_CLEAR_FLAG_SHORT, PPCNT_CLEAR_FLAG, "", "Clear Counters");
    MlxlinkRecord::printFlagLine(PEPC_SET_FLAG_SHORT, PEPC_SET_FLAG, "",
                                 "Set External PHY (for Ethernet switches only)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PEPC_FORCE_MODE_FLAG_SHORT, PEPC_FORCE_MODE_FLAG, "twisted_pair_force_mode",
                                 "Twisted Pair Force Mode [MA(Master)/SL(Slave)]");
    MlxlinkRecord::printFlagLine(CABLE_FLAG_SHORT, CABLE_FLAG, "", "Perform operations on the cables");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_DUMP_FLAG_SHORT, CABLE_DUMP_FLAG, "", "Dump cable pages in raw format");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_DDM_FLAG_SHORT, CABLE_DDM_FLAG, "",
                                 "Get cable Digital Diagnostic Monitoring information");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_READ_FLAG_SHORT, CABLE_READ_FLAG, "",
                                 "Perform read operation from specific page");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(READ_LEN_FLAG_SHORT, READ_LEN_FLAG, "length",
                                 "Length of data to read in bytes (Optional - Default 1 byte)");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(WRITE_PAGE_FLAG_SHORT, WRITE_PAGE_FLAG, "pageNum",
                                 "Specific page number to read/write");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(WRITE_OFFSET_FLAG_SHORT, WRITE_OFFSET_FLAG, "offset",
                                 "Specific page offset to read/write");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_WRITE_FLAG_SHORT, CABLE_WRITE_FLAG, "bytes",
                                 "Perform write operation with specific data (list of bytes, separated by ',')");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(WRITE_PAGE_FLAG_SHORT, WRITE_PAGE_FLAG, "pageNum",
                                 "Specific page number to read/write");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(WRITE_OFFSET_FLAG_SHORT, WRITE_OFFSET_FLAG, "offset",
                                 "Specific page offset to read/write");

    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_SELECT_SHORT, CABLE_PRBS_SELECT, "side",
                                 "Module PRBS test mode side selector [MEDIA, HOST]");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_MODE_SHORT, CABLE_PRBS_MODE, "cmd",
                                 "Perform PRBS test mode on the Module [EN(Enable),DS(Disable)]");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(
      CABLE_PRBS_GEN_PAT_SHORT, CABLE_PRBS_GEN_PAT, "pattern",
      "Set PRBS generator pattern [PRBS31(default),PRBS23,PRBS7,PRBS11,PRBS9,PRBS13,SSPR,SSPRQ]");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_GEN_SWAP_SHORT, CABLE_PRBS_GEN_SWAP, "",
                                 "Enable PAM4 MSB <-> LSB generator swapping (Optional)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_GEN_INV_SHORT, CABLE_PRBS_GEN_INV, "",
                                 "Enable PRBS generator inversion (Optional)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_GEN_LANES_SHORT, CABLE_PRBS_GEN_LANES, "lanes",
                                 "PRBS generator lanes to set (one or more lane separated by comma)[0,1,2,3,4,5,6,7] "
                                 "(Optional - Default all lanes)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(
      CABLE_PRBS_CH_PAT_SHORT, CABLE_PRBS_CH_PAT, "pattern",
      "Set PRBS checker pattern [PRBS31(default),PRBS23,PRBS7,PRBS11,PRBS9,PRBS13,SSPR,SSPRQ]");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_CH_SWAP_SHORT, CABLE_PRBS_CH_SWAP, "",
                                 "Enable PAM4 MSB <-> LSB checker swapping (Optional)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_CH_INV_SHORT, CABLE_PRBS_CH_INV, "",
                                 "Enable PRBS checker inversion (Optional)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_CH_LANES_SHORT, CABLE_PRBS_CH_LANES, "lanes",
                                 "PRBS checker lanes to set (one or more lane separated by comma)[0,1,2,3,4,5,6,7] "
                                 "(Optional - Default all lanes)");
    printf(IDENT3);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_LANE_RATE_SHORT, CABLE_PRBS_LANE_RATE, "rate",
                                 "Set PRBS checker and generator lane rate "
                                 "[HDR(50G)(default),1.25G,SDR(2.5G),10.3125G,FDR(14G),EDR(25G),NDR(100G)]");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_SHOW_DIAG_SHORT, CABLE_PRBS_SHOW_DIAG, "",
                                 "Show PRBS diagnostic counters information");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(CABLE_PRBS_CLEAR_DIAG_SHORT, CABLE_PRBS_CLEAR_DIAG, "",
                                 "Clear PRBS diagnostic counters");

    MlxlinkRecord::printFlagLine(CABLE_DDM_FLAG_SHORT, CTRL_PARAM_FLAG, "", "Show Module Control Parameters");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(
      CTRL_PARAM_TX_EQ_FLAG_SHORT, CTRL_PARAM_TX_EQ_FLAG, "value",
      "Set Module Tx Input Equalization in dB [NE(No Equalization),1,2,3,4,5,6,7,8,9,10,11,12]");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(CTRL_PARAM_RX_EMPH_FLAG_SHORT, CTRL_PARAM_RX_EMPH_FLAG, "value",
                                 "Set Module RX Output Emphasis in dB. for CMIS, pre-emphasis value will be set "
                                 "[NE(No Equalization),0.5,1,1.5,2,2.5,3,3.5,4,5,6,7]");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(CTRL_PARAM_RX_POST_EMPH_FLAG_SHORT, CTRL_PARAM_RX_POST_EMPH_FLAG, "value",
                                 "Set Module Rx Post Emphasis in dB [NE(No Equalization),1,2,3,4,5,6,7]");
    printf(IDENT2);
    MlxlinkRecord::printFlagLine(
      CTRL_PARAM_RX_AMP_FLAG_SHORT, CTRL_PARAM_RX_AMP_FLAG, "value",
      "Set Module Rx Output Amplitude [0(100-400mV),1(300-600mV),2(400-800mV),3(600-1200mV)]");

    MlxlinkRecord::printFlagLine(MARGIN_SCAN_FLAG_SHORT, MARGIN_SCAN_FLAG, "", "Read the SerDes eye margins per lane");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(EYE_MEASURE_TIME_FLAG_SHORT, EYE_MEASURE_TIME_FLAG, "time",
                                 "Measure time in seconds for single eye [10/30/60/90/120/240/480/600/900] (Optional - "
                                 "Default 60 for PCIe and 30 for Network ports)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(EYE_SEL_FLAG_SHORT, EYE_SEL_FLAG, "eye_sel",
                                 "Eye selection for PAM4 [UP/MID/DOWN/ALL] (Optional - Default ALL)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(LANE_INDEX_FLAG_SHORT, LANE_INDEX_FLAG, "lane_index",
                                 "Run eye for specific lane index (Optional - Default all lanes)");

    MlxlinkRecord::printFlagLine(PREI_RX_ERR_INJ_FLAG_SHORT, PREI_RX_ERR_INJ_FLAG, "",
                                 "Enable the RX link deterioration");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PREI_MIXER_OFFSET_0_SHORT, PREI_MIXER_OFFSET_0, "value",
                                 "Fine change to the center of the eye 0x0 to 0x7ff");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PREI_MIXER_OFFSET_1_SHORT, PREI_MIXER_OFFSET_1, "value",
                                 "Coarse change to the center of the eye 0x0 to 0x3ff");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PREI_SHOW_MIXERS_FLAG_SHORT, PREI_SHOW_MIXERS_FLAG, "",
                                 "Show mixer offset 0 and mixer offset 1");

    MlxlinkRecord::printFlagLine(MPEINJ_PCIE_ERR_INJ_FLAG_SHORT, MPEINJ_PCIE_ERR_INJ_FLAG, "",
                                 "Start/show PCIe error injection");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(MPEINJ_ERR_TYPE_FLAG_SHORT, MPEINJ_ERR_TYPE_FLAG, "type",
                                 "PCIe error type [ABORT(0),BAD_DLLP_LCRC(1),BAD_TLP_LCRC(2),BAD_TLP_ECRC(3),"
                                 "ERR_MSG(4),MALFORMED_TLP(5),POISONED_TLP(6),UNEXPECTED_CPL(7),ACS_VIOLATION(8),"
                                 "SURPRISE_LINK_DOWN(100),RECEIVER_ERROR(101)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(MPEINJ_ERR_DURATION_FLAG_SHORT, MPEINJ_ERR_DURATION_FLAG, "duration",
                                 "Error duration, depend on the error type, refer to the UM for more info (Optional)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(MPEINJ_INJ_DELAY_FLAG_SHORT, MPEINJ_INJ_DELAY_FLAG, "delay",
                                 "Delay in micro-seconds before applying the error (Optional)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(MPEINJ_ERR_PARAMETERS_FLAG_SHORT, MPEINJ_ERR_PARAMETERS_FLAG, "params",
                                 "Comma-separated parameters for selected error type (param0,param1,param2,param3), "
                                 "refer to the UM for more info (Optional)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(MPEINJ_DBDF_FLAG_SHORT, MPEINJ_DBDF_FLAG, "dbdf",
                                 "Destination bus device function, e.g af:00.0 (Optional used for specific error "
                                 "type)");

    MlxlinkRecord::printFlagLine(PPHCR_FEC_HIST_FLAG_SHORT, PPHCR_FEC_HIST_FLAG, "",
                                 "Provide histogram of FEC errors. The result is divided to bins. "
                                 "Each bin is holding different number of errored bit within FEC protected block");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPHCR_SHOW_FEC_HIST_FLAG_SHORT, PPHCR_SHOW_FEC_HIST_FLAG, "",
                                 "Show FEC errors histograms");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT, PPHCR_CLEAR_HISTOGRAM_FLAG, "",
                                 "Clears FEC errors histograms");

    MlxlinkRecord::printFlagLine(FORCE_YES_FLAG_SHORT, FORCE_YES_FLAG, "",
                                 "Non-interactive mode, answer yes to all questions");
    MlxlinkRecord::printFlagLine(PLANE_FLAG_SHORT, PLANE_FLAG, "plane", "Plane port access, starts from 1");
}

void MlxlinkUi::printSynopsis()
{
    printSynopsisHeader();
    printf("\n");
    printSynopsisQueries();
    printf("\n");
    printSynopsisCommands();
}

void MlxlinkUi::printHelp()
{
    printSynopsis();
    printf("\n");
    printf(IDENT "Examples:\n");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "get info of <device>, <port_number>",
           MLXLINK_EXEC " -d <device> -p <port_number>");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n",
           "get info of <device>, <port_number> and BER Counters",
           MLXLINK_EXEC " -d <device> -p <port_number> -c");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n",
           "get info of <device>, <port_number> and Transmitter Parameters",
           MLXLINK_EXEC " -d <device> -p <port_number> --show_serdes_tx");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Port State",
           MLXLINK_EXEC " -d <device> -p <port_number> --port_state UP");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Port Speeds",
           MLXLINK_EXEC " -d <device> -p <port_number> --speeds 25G,50G,100G");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure FEC", MLXLINK_EXEC " -d <device> -p <port_number> --fec RS");
    printf(
           IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Port for Physical Test Mode",
           MLXLINK_EXEC
           " -d <device> -p <port_number> --test_mode EN (--rx_prbs PRBS31 --rx_rate 25G --rx_modulation PAM4_PRECODING --tx_prbs PRBS7 --tx_modulation NRZ "
           "--tx_rate 10G)");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Perform PRBS Tuning",
           MLXLINK_EXEC " -d <device> -p <port_number> --test_mode TU");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Cable operations", MLXLINK_EXEC " -d <device> --cable options");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Dump cable EEPROM pages", MLXLINK_EXEC " -d <device> --cable --dump");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Get cable DDM info", MLXLINK_EXEC " -d <device> --cable --ddm");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Read from cable",
           MLXLINK_EXEC
           " -d <device> --cable --read --page <page number> --offset <bytes offset> --length <number of bytes>");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Write to cable",
           MLXLINK_EXEC
           " -d <device> --cable --write <bytes separated by comma> --page <page number> --offset <bytes offset> ");
    if (_userInput._advancedMode)
    {
        printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters (on lane, to database)",
               MLXLINK_EXEC " -d <device> -p <port_number> --serdes_tx "
                            "<polarity>,<ob_tap0>,<ob_tap1>,<ob_tap2>,<ob_bias>,<ob_preemp_mode>,<ob_reg>,<ob_leva> "
                            "(--serdes_tx_lane <lane number>) (--database)");
    }
    else
    {
        printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters (on lane, to database)",
               MLXLINK_EXEC " -d <device> -p <port_number> --serdes_tx "
                            "<polarity>,<ob_tap0>,<ob_tap1>,<ob_tap2>,<ob_bias>,<ob_preemp_mode> (--serdes_tx_lane "
                            "<lane number>) (--database)");
    }
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters for 16nm devices",
           MLXLINK_EXEC
           " -d <device> -p <port_number> --serdes_tx <pre_2_tap>,<pre_tap>,<main_tap>,<post_tap>,<ob_m2lp>,<ob_amp>");
}

void MlxlinkUi::validateMandatoryParams()
{
    if (_userInput._device == "")
    {
        throw MlxRegException("Please provide a device name");
    }
    if (_userInput._links && _userInput._portType != "PCIE")
    {
        throw MlxRegException("The --" PCIE_LINKS_FLAG " option is valid only with --port_type PCIE");
    }
    if (_userInput._links &&
        (_userInput._showEyeInfo || _userInput._showSltp || _userInput._showCounters || _userInput._showSlrp))
    {
        throw MlxRegException("No options allowed to use while querying --" PCIE_LINKS_FLAG);
    }
    if ((_userInput._labelPort == 0) && (_userInput._portType != "PCIE"))
    {
        throw MlxRegException("Please provide a valid port number");
    }
}

void MlxlinkUi::validatePCIeParams()
{
    bool dpnFlags = _userInput._sendNode || _userInput._sendDepth || _userInput._sendPcieIndex;

    if (_userInput._portType == "PCIE")
    {
        _userInput._pcie = true;

        if (_userInput._uniqueCmds)
        {
            throw MlxRegException("Command flags are not available for PCIE");
        }

        if (_userInput._networkCmds)
        {
            throw MlxRegException("FEC and Module Info flags are not available for PCIE");
        }

        if (_userInput._uniquePcieCmds > 1)
        {
            throw MlxRegException("Commands are mutually exclusive!");
        }

        replace(_sendRegFuncMap.begin(), _sendRegFuncMap.end(), SHOW_PDDR, SHOW_PCIE);

        if (dpnFlags)
        {
            if (!(_userInput._sendNode && _userInput._sendDepth && _userInput._sendPcieIndex))
            {
                throw MlxRegException("The --depth, --pcie_index and --node must be specified for PCIE");
            }
            else
            {
                _userInput._sendDpn = true;
            }
        }
        if (_userInput._portSpecified)
        {
            if (dpnFlags)
            {
                throw MlxRegException("For PCIE port, either port flag or depth, pcie_index and node flags should be "
                                      "specified");
            }
        }
        // Extended PCIe info is only valid when depth/pcie_index/node are provided
        if (_userInput._extendedPcie && !_userInput._sendDpn)
        {
            throw MlxRegException("The --" EXTENDED_PCIE_FLAG
                                  " flag is valid only when --depth, --pcie_index and --node are specified");
        }
    }
    else if (dpnFlags)
    {
        throw MlxRegException("The --depth, --node and --pcie_index flags are valid only with --port_type PCIE");
    }
    else if (_userInput._extendedPcie)
    {
        throw MlxRegException("The --" EXTENDED_PCIE_FLAG " flag is valid only with --port_type PCIE");
    }
}

void MlxlinkUi::validateGeneralCmdsParams()
{
    if (_userInput._uniqueCmds > 1)
    {
        throw MlxRegException("Commands are mutually exclusive!");
    }
    if (isIn(SEND_PAOS, _sendRegFuncMap) && !checkPaosCmd(_userInput._paosCmd))
    {
        throw MlxRegException("Please provide a valid paos command [UP(up)/DN(down)/TG(toggle)]");
    }
    if (isIn(SEND_PMAOS, _sendRegFuncMap) && !checkPmaosCmd(_userInput._pmaosCmd))
    {
        throw MlxRegException("Please provide a valid pmaos command [UP(up)/DN(down)/TG(toggle)]");
    }
    if (!isIn(SEND_PPLM, _sendRegFuncMap) && _userInput._speedFec != "")
    {
        throw MlxRegException("The --fec_speed flag is valid only with --fec flag");
    }
    if (isIn(SEND_SLTP, _sendRegFuncMap))
    {
        if (_userInput._sltpLane && _userInput._db)
        {
            throw MlxRegException("Lane and Database flags are mutually exclusive");
        }
    }
    else if (_userInput._sltpLane || _userInput._db || _userInput._txPolicy)
    {
        throw MlxRegException(LANE_FLAG
                              ", --" DATABASE_FLAG " and --" SLTP_TX_POLICY_FLAG
                              " flags are valid only with Configure Transmitter Parameters flag (--" SLTP_SET_FLAG ")");
    }
}

void MlxlinkUi::validatePRBSParams()
{
    bool prbsFlags = _userInput._sendPprt || _userInput._sendPptt || _userInput._pprtRate != "" ||
                     _userInput._pprtRate != "" || _userInput._prbsTxInv || _userInput._prbsRxInv ||
                     _userInput._prbsDcCoupledAllow ||
                     _userInput._prbsLanesToSet.size() > 0 || !_userInput._pprtModulation.empty() ||
                     !_userInput._ppttModulation.empty();
    if (isIn(SEND_PRBS, _sendRegFuncMap))
    {
        if (!checkPrbsCmd(_userInput._prbsMode))
        {
            throw MlxRegException("you must provide a valid PRBS test mode [DS/EN/TU]");
        }
    }
    if (_userInput._prbsMode != "EN" && prbsFlags)
    { // add check for lanes flag to work with PRBS and eye scan only
        throw MlxRegException("PRBS parameters flags valid only with PRBS Enable flag (--test_mode EN)");
    }
}

void MlxlinkUi::validatePhyRecoveryParams()
{
    bool phyRecoveryFlags =
      _userInput._phyRecovery != "" || _userInput._phyRecoveryType != "" || _userInput._wdTimerSpecified;
    if (isIn(SEND_PHY_RECOVERY, _sendRegFuncMap))
    {
        if (!checkPhyRecoveryCmd(_userInput._phyRecovery))
        {
            throw MlxRegException("Please provide a valid phy recovery command [EN/DS]");
        }
        else if (_userInput._phyRecovery == "EN")
        {
            if (_userInput._phyRecoveryType == "")
            {
                throw MlxRegException("recovery_type flag should be provided for phy_recovery EN command");
            }
            else if (_userInput._phyRecoveryType != "host_serdes_feq" &&
                     _userInput._phyRecoveryType != "host_logic_re_lock")
            {
                throw MlxRegException("Invalid Recovery Type!");
            }
            if (_userInput._wdTimerSpecified && _userInput._wdTimer <= 0)
            {
                throw MlxRegException("wd_timer flag must be greater than 0");
            }
        }
        else if (_userInput._phyRecovery == "DS")
        {
            if (_userInput._phyRecoveryType == "")
            {
                throw MlxRegException("recovery_type flag should be provided for PHY Recovery DS command");
            }
            else if (_userInput._phyRecoveryType != "host_serdes_feq" &&
                     _userInput._phyRecoveryType != "host_logic_re_lock")
            {
                throw MlxRegException("Invalid PHY Recovery Type!");
            }
            if (_userInput._wdTimerSpecified)
            {
                throw MlxRegException("WD Timer flag should not be provided for PHY Recovery DS command");
            }
        }
    }
    else if (phyRecoveryFlags)
    {
        throw MlxRegException("PHY Recovery flag should be provided!");
    }
}

void MlxlinkUi::validateLinkTrainingParams()
{
    if (isIn(SEND_LINK_TRAINING, _sendRegFuncMap))
    {
        if (!checkLinkTrainingCmd(_userInput._linkTraining))
        {
            throw MlxRegException("Please provide a valid link training command [EN/DS/EN_EXT]");
        }
    }
    else if (!_userInput._linkTraining.empty())
    {
        throw MlxRegException("Link Training flag should be provided!");
    }
}

void MlxlinkUi::validatePeriodicEqParams()
{
    if (_userInput._periodicEqIntervalSpecified)
    {
        if (_userInput._setPeriodicEqInterval < 0 || _userInput._setPeriodicEqInterval > 40000)
        {
            throw MlxRegException("Periodic EQ interval should be in range [0-40000]");
        }
        if (_userInput._setPeriodicEqInterval % 10 != 0)
        {
            throw MlxRegException("Periodic EQ interval should be a multiple of 10");
        }
    }
}

void MlxlinkUi::validateModulePRBSParams()
{
    if (!_userInput.isPrbsSelProvided &&
        (_userInput.isPrbsModeProvided || _userInput.isPrbsChProvided || _userInput.isPrbsGenProvided ||
         _userInput.isPrbsShowDiagProvided || _userInput.isPrbsClearDiagProvided))
    {
        throw MlxRegException("Please select PRBS module side using --" CABLE_PRBS_SELECT " [MEDIA|HOST] flag!");
    }

    if (!_userInput.isPrbsModeProvided && (_userInput.isPrbsChProvided || _userInput.isPrbsGenProvided ||
                                           !_userInput.modulePrbsParams[MODULE_PRBS_RATE].empty()))
    {
        throw MlxRegException("--" CABLE_PRBS_MODE " flag should be provided!");
    }
    if (_userInput.modulePrbsParams[MODULE_PRBS_MODE] == "DS" && _userInput.modulePrbsParams.size() > 2)
    {
        throw MlxRegException("PRBS module parameters flags are valid only with PRBS enable mode (--prbs_mode EN)");
    }

    if (_userInput.isPrbsModeProvided && (_userInput.isPrbsShowDiagProvided || _userInput.isPrbsClearDiagProvided))
    {
        throw MlxRegException("PRBS Module Diagnostic info flags are not working while configuring the PRBS test "
                              "mode!");
    }

    if (_userInput.isPrbsShowDiagProvided && _userInput.isPrbsClearDiagProvided)
    {
        throw MlxRegException("are mutually exclusive, please select one command only");
    }
}

void MlxlinkUi::validateSpeedAndCSVBerParams()
{
    bool berCollect = isIn(SEND_BER_COLLECT, _sendRegFuncMap);
    bool amBerCollect = isIn(SEND_AMBER_COLLECT, _sendRegFuncMap);
    if (berCollect && amBerCollect)
    {
        throw MlxRegException("--" BER_COLLECT_FLAG " and --" AMBER_COLLECT_FLAG " "
                              "are mutually exclusive, please select one command only");
    }
    if (berCollect || amBerCollect)
    {
        if (!endsWith(_userInput._csvBer, ".csv"))
        {
            throw MlxRegException("you must provide a valid .csv file");
        }
        if (!checkTestMode(_userInput._testMode))
        {
            throw MlxRegException("Please provide a valid test mode [Nominal(Default)/Corner/Drift]");
        }
    }
    else if (_userInput._testMode != "Nominal")
    {
        throw MlxRegException("BER Limit Criteria flag is valid only with Port Information Collection flag (--bc)");
    }
    if (isIn(SEND_PEPC, _sendRegFuncMap))
    {
        if (!_userInput._sendPepcForceMode)
        {
            throw MlxRegException("Please provide --twisted_pair_force_mode");
        }
        if (_userInput._sendPepcForceMode && !checkPepcForceMode(_userInput._forceMode))
        {
            throw MlxRegException("Please provide a valid twisted pair force mode [MA(Master)/SL(Slave)]");
        }
    }
    else
    {
        if (_userInput._sendPepcForceMode)
        {
            throw MlxRegException("Please provide --set_external_phy option to configure the twisted pair force mode");
        }
    }
    if (_userInput._linkModeForce && _userInput._ptysSpeeds.size() != 1)
    {
        throw MlxRegException("--link_mode_force should receive exactly one speed using --speeds");
    }
}

void MlxlinkUi::validateCableParams()
{
    bool readWriteFlags = _userInput._page >= 0 || _userInput._offset >= 0 || _userInput._len >= 0;
    bool prbsParamProvided = _userInput.modulePrbsParams.size();
    bool cablePrbsParamProvided = _userInput.isPrbsSelProvided || prbsParamProvided;
    bool cableConfigParamProvided = _userInput.isModuleConfigParamsProvided;
    bool paramSetProvided = _userInput.configParamsToSet.size();
    bool cableCommandProvided = _userInput._dump || _userInput._write || _userInput._read || _userInput._ddm ||
                                cablePrbsParamProvided || cableConfigParamProvided;

    if (!_userInput._cable && (cableCommandProvided || readWriteFlags))
    {
        throw MlxRegException("\"--" CABLE_FLAG "\" flag should be specified!");
    }
    else if (_userInput._cable)
    {
        if ((_userInput._uniqueCableCmds > 1) || !cableCommandProvided)
        {
            throw MlxRegException("Please choose one of " CABLE_FLAG " operations!");
        }
        if ((_userInput._read || _userInput._write) && (_userInput._page == -1 || _userInput._offset == -1))
        {
            throw MlxRegException("\"--" WRITE_PAGE_FLAG "\" and \"--" WRITE_OFFSET_FLAG
                                  "\" flags should be specified!");
        }
        if (!cableConfigParamProvided && paramSetProvided)
        {
            throw MlxRegException("--" CTRL_PARAM_FLAG " should be specified!");
        }

        if (readWriteFlags)
        {
            if (!_userInput._write && !_userInput._read)
            {
                throw MlxRegException("Read or Write flag should be specified!");
            }

            if (_userInput._read)
            {
                if (_userInput._len == -1)
                {
                    _userInput._len = 1; // default number of bytes to read
                }
                else if (_userInput._len == 0)
                {
                    throw MlxRegException("The length cannot be zero!");
                }
            }
            else if (_userInput._len >= 0)
            {
                throw MlxRegException("\"--" READ_LEN_FLAG "\" flag is working with read option only!");
            }
        }
    }
}

void MlxlinkUi::validateTxGroupParams()
{
    if (_userInput._showGroup >= 0)
    {
        if (!_userInput._labelPorts.empty())
        {
            throw MlxRegException("\"--" TX_GROUP_PORTS_FLAG "\" flag is working with " SET_TX_GROUP_MAP_FLAG " only!");
        }
    }

    if (_userInput._setGroup >= 0 && _userInput._showGroup >= 0)
    {
        throw MlxRegException("Choose one of operations!");
    }

    if (_userInput._setGroup >= 0)
    {
        if (_userInput._labelPorts.empty())
        {
            throw MlxRegException("\"--" TX_GROUP_PORTS_FLAG "\" should be specified!");
        }
    }
    if (_userInput._setGroup >= MAX_TX_GROUP_COUNT || _userInput._showGroup >= MAX_TX_GROUP_COUNT)
    {
        throw MlxRegException("Tx group is invalid, it can be in range [0-9]!");
    }
    if (_userInput._setGroup == -1 && !_userInput._labelPorts.empty())
    {
        throw MlxRegException("\"--" SET_TX_GROUP_MAP_FLAG "\" should be specified!");
    }
}

void MlxlinkUi::validateGradeScanParams()
{
    if (_userInput.eyeSelectSpecified)
    {
        if (_userInput._portType == "PCIE")
        {
            throw MlxRegException(EYE_SEL_FLAG " flag is working with Network ports only!");
        }
    }
}

void MlxlinkUi::validateErrInjParams()
{
    bool errInjEnable = _userInput.enableRxErrInj;
    bool showMixers = _userInput.showMixers;
    bool mixerControl = _userInput.mixerOffset0 >= 0 || _userInput.mixerOffset1 >= 0;
    if ((errInjEnable) && ((!mixerControl && !showMixers) || (mixerControl && showMixers)))
    {
        throw MlxRegException("Please provide either mixers offset configuration, "
                              "or show mixers option\n");
    }
    if (!errInjEnable && (showMixers || mixerControl))
    {
        throw MlxRegException(PREI_RX_ERR_INJ_FLAG " flag should be specified!");
    }
    if (mixerControl)
    {
        if (_userInput.mixerOffset0 > MAX_MIXER_OFFSET_0 || _userInput.mixerOffset1 > MAX_MIXER_OFFSET_1)
        {
            char errMsg[64];
            sprintf(errMsg, "For mixer_offset0 [0 to 0x%x] and mixer_offset1 [0 to 0x%x]", MAX_MIXER_OFFSET_0,
                    MAX_MIXER_OFFSET_1);
            throw MlxRegException("Invalid mixer offset value, " + string(errMsg));
        }
    }

    if (_userInput.isPcieErrInjProvided)
    {
        if (!_userInput._pcie)
        {
            throw MlxRegException("The PCIE error injection feature is applicable to the PCIe links only!");
        }
        if (_userInput.errorType.empty())
        {
            if (_userInput.errorDuration != -1 || !_userInput.dbdf.empty() || _userInput.injDelay != -1)
            {
                throw MlxRegException(MPEINJ_ERR_TYPE_FLAG " flag should be specified!");
            }
        }
    }
    if (_userInput.errorDuration != -1 || !_userInput.dbdf.empty() || _userInput.injDelay != -1 ||
        !_userInput.errorType.empty() || !_userInput.parameters.empty())
    {
        if (!_userInput.isPcieErrInjProvided)
        {
            throw MlxRegException(MPEINJ_PCIE_ERR_INJ_FLAG " flag should be specified!");
        }
    }
}

void MlxlinkUi::validatePortInfoParams()
{
    if (_userInput.enableFecHistogram && !_userInput.showFecHistogram && !_userInput.clearFecHistogram)
    {
        throw MlxRegException("Please provide one of FEC Histogram options: "
                              "--" PPHCR_SHOW_FEC_HIST_FLAG " or --" PPHCR_CLEAR_HISTOGRAM_FLAG);
    }
    if (!_userInput.enableFecHistogram && (_userInput.showFecHistogram || _userInput.clearFecHistogram))
    {
        throw MlxRegException(PPHCR_FEC_HIST_FLAG " flag should  be specified");
    }
    if (_userInput.showFecHistogram && _userInput.clearFecHistogram)
    {
        throw MlxRegException("Options are mutually exclusive, please select one option only");
    }
}

void MlxlinkUi::validateMultiPortInfoParams()
{
    if ((_userInput._showMultiPortInfo || _userInput._showMultiPortModuleInfo) && _userInput._portSpecified)
    {
        throw MlxRegException("When using " MULTI_PORT_INFO_FLAG " or " MULTI_PORT_MODULE_INFO_FLAG " flags, "
                              "the port flag must not be specified!");
    }
}

void MlxlinkUi::validateBkvParams()
{
    if (isIn(SHOW_BKV, _sendRegFuncMap))
    {
        if (!_userInput.laneSpecified)
        {
            throw MlxRegException("The --" LANE_INDEX_FLAG " parameter is required when using --" BKV_GROUPS_FLAG
                                  " flag");
        }
    }
    if (isIn(SET_BKV_GROUP, _sendRegFuncMap))
    {
        if (_userInput._bkvRates.size() == 0 && !_userInput._bkvRoles.size() && !_userInput._bkvModeBRoles.size())
        {
            throw MlxRegException("At least one mask flag (--" BKV_RATES_FLAG ", --" BKV_ROLES_FLAG
                                  ", --" BKV_MODE_B_ROLES_FLAG ") is required when using --" SET_BKV_GROUP_FLAG
                                  " flag");
        }
    }
    if (isIn(SET_BKV_ENTRY, _sendRegFuncMap))
    {
        if (!_userInput._bkvEntrySpecified)
        {
            throw MlxRegException("The --" BKV_ENTRY_FLAG " parameter is required when using --" SET_BKV_ENTRY_FLAG
                                  " flag");
        }
        if (!_userInput._bkvAddressSpecified && !_userInput._bkvWdataSpecified && !_userInput._bkvWmaskSpecified)
        {
            throw MlxRegException("At least one entry flag (--" BKV_ADDRESS_FLAG ", --" BKV_WDATA_FLAG
                                  ", --" BKV_WMASK_FLAG ") is required when using --" SET_BKV_ENTRY_FLAG " flag");
        }
    }
}

void MlxlinkUi::strToInt32(char* str, u_int32_t& value)
{
    char* endp;
    value = strtol(str, &endp, 0);
    if (*endp)
    {
        throw MlxRegException("Argument: %s is invalid.", str);
    }
}

std::vector<string> MlxlinkUi::parseParamsFromLine(const string& paramsLine)
{
    std::vector<string> paramVector;
    string param;
    stringstream stream(paramsLine);
    while (getline(stream, param, ','))
    {
        if (param == "")
        {
            throw MlxRegException("Wrong input format");
        }
        paramVector.push_back(param.c_str());
    }
    return paramVector;
}

std::map<u_int32_t, u_int32_t> MlxlinkUi::getSltpParamsFromVector(const string& paramsLine)
{
    std::map<u_int32_t, u_int32_t> sltpParamsInt;
    std::vector<string> sltpParamsStr = parseParamsFromLine(paramsLine);

    for (u_int32_t i = 0; i < sltpParamsStr.size(); i++)
    {
        strToInt32((char*)sltpParamsStr[i].c_str(), sltpParamsInt[i]);
    }

    return sltpParamsInt;
}

std::map<u_int32_t, bool> MlxlinkUi::getprbsLanesFromParams(const string& paramsLine)
{
    std::vector<string> prbsLanesParams = parseParamsFromLine(paramsLine);

    std::map<u_int32_t, bool> prbsLanesToSet;
    u_int32_t lane = 0;
    vector<string>::iterator it = prbsLanesParams.begin();
    while (it != prbsLanesParams.end())
    {
        mlxreg::RegAccessParser::strToUint32((char*)(*it).c_str(), lane);
        prbsLanesToSet[lane] = true;
        it++;
    }
    return prbsLanesToSet;
}

void MlxlinkUi::handlePortStr(UserInput& userInput, const string& portStr)
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
        mlxreg::RegAccessParser::strToUint32((char*)portParts[1].c_str(), userInput._splitPort);
        userInput._splitProvided = true;
        if (portParts.size() > SECOND_LEVEL_PORT_ACCESS)
        {
            // it's the split part of Quantum-2 (xx/xx/split)
            mlxreg::RegAccessParser::strToUint32((char*)portParts[2].c_str(), userInput._secondSplitPort);
            userInput._secondSplitProvided = true;
        }
        else if (portParts.size() > THIRD_LEVEL_PORT_ACCESS)
        {
            throw MlxRegException("Failed to handle option port");
        }
    }

    mlxreg::RegAccessParser::strToUint32((char*)portParts[0].c_str(), userInput._labelPort);
    userInput._portSpecified = true;
}

void MlxlinkUi::checkStrLength(const string& str)
{
    if (str.size() > MAX_INPUT_LENGTH)
    {
        throw MlxRegException("Argument: %s... is invalid.", str.substr(0, MAX_INPUT_LENGTH).c_str());
    }
}

void MlxlinkUi::paramValidate()
{
    validateMandatoryParams();
    validatePCIeParams();
    validateGeneralCmdsParams();
    validateBkvParams();
    validatePRBSParams();
    validatePhyRecoveryParams();
    validateLinkTrainingParams();
    validatePeriodicEqParams();
    validateSpeedAndCSVBerParams();
    validateCableParams();
    validateModulePRBSParams();
    validateTxGroupParams();
    validateGradeScanParams();
    validateErrInjParams();
    validatePortInfoParams();
}

void MlxlinkUi::initCmdParser()
{
    AddOptions(DEVICE_FLAG, DEVICE_FLAG_SHORT, "MstDevice", "Mellanox mst device name");
    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");
    AddOptions(PORT_TYPE_FLAG, PORT_TYPE_FLAG_SHORT, "port_type", "Port Type");
    AddOptions(DEPTH_FLAG, DEPTH_FLAG_SHORT, "depth", "depth");
    AddOptions(PCIE_INDEX_FLAG, PCIE_INDEX_FLAG_SHORT, "pcie_index", "PCIe Index");
    AddOptions(NODE_FLAG, NODE_FLAG_SHORT, "node", "node");
    AddOptions(LABEL_PORT_FLAG, LABEL_PORT_FLAG_SHORT, "LabelPort", "Label Port");
    AddOptions(PCIE_LINKS_FLAG, PCIE_LINKS_FLAG_SHORT, "", "Show valid PCIe links");
    AddOptions(EXTENDED_PCIE_FLAG, EXTENDED_PCIE_FLAG_SHORT, "", "Show extended PCIe link info");
    AddOptions(BER_FLAG, BER_FLAG_SHORT, "", "Show BER Info");
    AddOptions(EYE_OPENING_FLAG, EYE_OPENING_FLAG_SHORT, "", "Show Eye Opening Info");
    AddOptions(MODULE_INFO_FLAG, MODULE_INFO_FLAG_SHORT, "", "Show Module Info");
    AddOptions(PPCNT_CLEAR_FLAG, PPCNT_CLEAR_FLAG_SHORT, "", "Clear PPCNT Counters");
    AddOptions(DEVICE_DATA_FLAG, DEVICE_DATA_FLAG_SHORT, "", "Device Info");
    AddOptions(BER_MONITOR_INFO_FLAG, BER_MONITOR_INFO_FLAG_SHORT, "", "Show BER Monitor Info");
    AddOptions(PEPC_SHOW_FLAG, PEPC_SHOW_FLAG_SHORT, "", "Show External PHY Info");
    AddOptions(PRINT_JSON_OUTPUT_FLAG, PRINT_JSON_OUTPUT_FLAG_SHORT, "", "Print the output in json format");
    AddOptions(MULTI_PORT_INFO_FLAG, MULTI_PORT_INFO_FLAG_SHORT, "", "Show multi ports info table");
    AddOptions(MULTI_PORT_INFO_ACRONYM_FLAG, MULTI_PORT_INFO_ACRONYM_FLAG_SHORT, "", "Show multi port info table");
    AddOptions(MULTI_PORT_MODULE_INFO_FLAG, MULTI_PORT_MODULE_INFO_FLAG_SHORT, "", "Show multi port module info table");
    AddOptions(MULTI_PORT_MODULE_INFO_ACRONYM_FLAG, MULTI_PORT_MODULE_INFO_ACRONYM_FLAG_SHORT, "",
               "Show multi port module info table");
    AddOptions(PLR_INFO_FLAG, PLR_INFO_FLAG_SHORT, "", "Show PLR Info");
    AddOptions(KR_INFO_FLAG, KR_INFO_FLAG_SHORT, "", "Show KR Info");
    AddOptions(PERIODIC_EQ_FLAG, PERIODIC_EQ_FLAG_SHORT, "", "Show Link PEQ (Periodic Equalization) Info");
    AddOptions(RX_RECOVERY_COUNTERS_FLAG, RX_RECOVERY_COUNTERS_FLAG_SHORT, "", "Show Rx Recovery Counters");
    AddOptions(LINK_TRAINING_FLAG, LINK_TRAINING_FLAG_SHORT, "Mode", "Enable/Disable/Enable_Extra Link Training");
    AddOptions(BKV_GROUPS_FLAG, BKV_GROUPS_FLAG_SHORT, "", "Show BKV Groups Info");
    AddOptions(BKV_GROUP_FLAG, BKV_GROUP_FLAG_SHORT, "group_id", "Show BKV Group Info");
    AddOptions(SET_BKV_GROUP_FLAG, SET_BKV_GROUP_FLAG_SHORT, "group_id", "Set BKV Group Masks");
    AddOptions(BKV_RATES_FLAG, BKV_RATES_FLAG_SHORT, "bkv_rates",
               "BKV Rates separated by comma: "
               "[312.5M,53.125G,106.25G,200G,212.5G] (Optional)");
    AddOptions(BKV_ROLES_FLAG, BKV_ROLES_FLAG_SHORT, "bkv_roles",
               "BKV Roles separated by comma: "
               "[TLM,RLM,TCLM] (Optional)");
    AddOptions(BKV_MODE_B_ROLES_FLAG, BKV_MODE_B_ROLES_FLAG_SHORT, "bkv_mode_b_roles",
               "BKV Mode B Roles separated by comma: "
               "[PRIMARY,SECONDARY] (Optional)");
    AddOptions(SET_BKV_ENTRY_FLAG, SET_BKV_ENTRY_FLAG_SHORT, "group_id", "Set BKV Group Entry");
    AddOptions(BKV_ENTRY_FLAG, BKV_ENTRY_FLAG_SHORT, "entry_id", "BKV Entry ID");
    AddOptions(BKV_ADDRESS_FLAG, BKV_ADDRESS_FLAG_SHORT, "address", "BKV Entry Address");
    AddOptions(BKV_WDATA_FLAG, BKV_WDATA_FLAG_SHORT, "wdata", "BKV Entry Write Data");
    AddOptions(BKV_WMASK_FLAG, BKV_WMASK_FLAG_SHORT, "wmask", "BKV Entry Write Mask");

    AddOptions(SET_LINK_PEQ_FLAG, SET_LINK_PEQ_FLAG_SHORT, "PEQ_TIME", "Set Link PEQ (Periodic Equalization)");
    AddOptions(FEC_DATA_FLAG, FEC_DATA_FLAG_SHORT, "", "FEC Data");
    AddOptions(PAOS_FLAG, PAOS_FLAG_SHORT, "PAOS", "Send PAOS");
    AddOptions(PMAOS_FLAG, PMAOS_FLAG_SHORT, "PMAOS", "Send PMAOS");
    AddOptions(PTYS_FLAG, PTYS_FLAG_SHORT, "PTYS", "Send PTYS");
    AddOptions(PTYS_LINK_MODE_FORCE_FLAG, PTYS_LINK_MODE_FORCE_FLAG_SHORT, "", "Set Link Mode Force");
    AddOptions(PPLM_FLAG, PPLM_FLAG_SHORT, "PPLM", "Send PPLM");
    AddOptions(FEC_SPEED_FLAG, FEC_SPEED_FLAG_SHORT, "FECSPEED", "Send PPLM with Speed");
    AddOptions(PPLR_FLAG, PPLR_FLAG_SHORT, "PPLR", "Send PPLR");
    AddOptions(BER_COLLECT_FLAG, BER_COLLECT_FLAG_SHORT, "BERCollectFile", "BER Collection csv file");
    AddOptions(AMBER_COLLECT_FLAG, AMBER_COLLECT_FLAG_SHORT, "AMBERCollectFile", "AMBER Collection csv file");
    AddOptions(BER_LIMIT_FLAG, BER_LIMIT_FLAG_SHORT, "Mode", "Test Mode of Ber Collect (Nominal/Corner/Drift)");
    AddOptions(ITERATION_FLAG, ITERATION_FLAG_SHORT, "Iteration", "Iteration of BER Collect");
    AddOptions(PHY_RECOVERY_FLAG, PHY_RECOVERY_FLAG_SHORT, "Recovery", "Enable/Disable PHY Recovery");
    AddOptions(PHY_RECOVERY_TYPE_FLAG, PHY_RECOVERY_TYPE_FLAG_SHORT, "Recovery_Type", "Recovery Type");
    AddOptions(PRBS_MODE_FLAG, PRBS_MODE_FLAG_SHORT, "PRBS", "Enable/Disable PRBS Test Mode");
    AddOptions(PPRT_PRBS_FLAG, PPRT_PRBS_FLAG_SHORT, "PPRT", "PPRT Mode");
    AddOptions(PPTT_PRBS_FLAG, PPTT_PRBS_FLAG_SHORT, "PPTT", "PPTT Mode");
    AddOptions(PPRT_MODULATION_FLAG, PPRT_MODULATION_FLAG_SHORT, "PPRT_MODULATION",
               "PPRT Modulation (NRZ/PAM4/PAM4_PRECODING/PAM4_NO_GRAY)");
    AddOptions(PPTT_MODULATION_FLAG, PPTT_MODULATION_FLAG_SHORT, "PPTT_MODULATION",
              "PPTT Modulation (NRZ/PAM4/PAM4_PRECODING/PAM4_NO_GRAY)");
    AddOptions(PPRT_RATE_FLAG, PPRT_RATE_FLAG_SHORT, "PPRT_RATE", "PPRT Lane Rate");
    AddOptions(PPTT_RATE_FLAG, PPTT_RATE_FLAG_SHORT, "PPTT_RATE", "PPTT Lane Rate");
    AddOptions(PRBS_LANES_FLAG, PRBS_LANES_FLAG_SHORT, "lanes", "PRBS lanes to set");
    AddOptions(PRBS_INVERT_TX_POL_FLAG, PRBS_INVERT_TX_POL_FLAG_SHORT, "", "PRBS TX polarity inversion");
    AddOptions(PRBS_INVERT_RX_POL_FLAG, PRBS_INVERT_RX_POL_FLAG_SHORT, "", "PRBS RX polarity inversion");
    AddOptions(PRBS_DC_COUPLE_ALLOW_FLAG, PRBS_DC_COUPLE_ALLOW_FLAG_SHORT, "", "Allow PRBS for DC coupled ports");
    AddOptions(FORCE_TX_ALLOWED_FLAG, FORCE_TX_ALLOWED_FLAG_SHORT, "", "Force TX allowed for PRBS test mode");
    AddOptions(SKIP_POWER_GOOD_CHECK_FLAG, SKIP_POWER_GOOD_CHECK_FLAG_SHORT, "",
               "Skip power good check for PRBS test mode");
    AddOptions(SYSFS_PATH_FLAG, SYSFS_PATH_FLAG_SHORT, "path", "Full path to sysfs files");

    AddOptions(CABLE_FLAG, CABLE_FLAG_SHORT, "", "Cable operations");
    AddOptions(CABLE_DUMP_FLAG, CABLE_DUMP_FLAG_SHORT, "", "Dump cable EEPROM pages");
    AddOptions(CABLE_DDM_FLAG, CABLE_DDM_FLAG_SHORT, "", "Show DDM information");
    AddOptions(CABLE_WRITE_FLAG, CABLE_WRITE_FLAG_SHORT, "bytes", "Perform write operation");
    AddOptions(CABLE_READ_FLAG, CABLE_READ_FLAG_SHORT, "", "Perform read operation");
    AddOptions(WRITE_PAGE_FLAG, WRITE_PAGE_FLAG_SHORT, "pageNum", "Specify page number");
    AddOptions(WRITE_OFFSET_FLAG, WRITE_OFFSET_FLAG_SHORT, "offset", "Specify page offset");
    AddOptions(READ_LEN_FLAG, READ_LEN_FLAG_SHORT, "length", "Length of data to read in bytes");

    AddOptions(CABLE_PRBS_SELECT, CABLE_PRBS_SELECT_SHORT, "side", "");
    AddOptions(CABLE_PRBS_MODE, CABLE_PRBS_MODE_SHORT, "cmd", "");
    AddOptions(CABLE_PRBS_GEN_PAT, CABLE_PRBS_GEN_PAT_SHORT, "pattern", "");
    AddOptions(CABLE_PRBS_GEN_SWAP, CABLE_PRBS_GEN_SWAP_SHORT, "", "");
    AddOptions(CABLE_PRBS_GEN_INV, CABLE_PRBS_GEN_INV_SHORT, "", "");
    AddOptions(CABLE_PRBS_GEN_LANES, CABLE_PRBS_GEN_LANES_SHORT, "lanes", "");
    AddOptions(CABLE_PRBS_CH_PAT, CABLE_PRBS_CH_PAT_SHORT, "pattern", "");
    AddOptions(CABLE_PRBS_CH_SWAP, CABLE_PRBS_CH_SWAP_SHORT, "", "");
    AddOptions(CABLE_PRBS_CH_INV, CABLE_PRBS_CH_INV_SHORT, "", "");
    AddOptions(CABLE_PRBS_CH_LANES, CABLE_PRBS_CH_LANES_SHORT, "lanes", "");
    AddOptions(CABLE_PRBS_LANE_RATE, CABLE_PRBS_LANE_RATE_SHORT, "rate", "");
    AddOptions(CABLE_PRBS_SHOW_DIAG, CABLE_PRBS_SHOW_DIAG_SHORT, "", "");
    AddOptions(CABLE_PRBS_CLEAR_DIAG, CABLE_PRBS_CLEAR_DIAG_SHORT, "", "");

    AddOptions(CTRL_PARAM_FLAG, CTRL_PARAM_FLAG_SHORT, "", "Cable Control Params");
    AddOptions(CTRL_PARAM_TX_EQ_FLAG, CTRL_PARAM_TX_EQ_FLAG_SHORT, "value", "TX Eq override");
    AddOptions(CTRL_PARAM_RX_EMPH_FLAG, CTRL_PARAM_RX_EMPH_FLAG_SHORT, "value", "RX Emp override");
    AddOptions(CTRL_PARAM_RX_POST_EMPH_FLAG, CTRL_PARAM_RX_POST_EMPH_FLAG_SHORT, "value", "RX post emp");
    AddOptions(CTRL_PARAM_RX_AMP_FLAG, CTRL_PARAM_RX_AMP_FLAG_SHORT, "value", "RX Amp");

    AddOptions(SHOW_TX_GROUP_MAP_FLAG, SHOW_TX_GROUP_MAP_FLAG_SHORT, "group_num",
               "Display all label ports mapped to group <group_num>");
    AddOptions(SET_TX_GROUP_MAP_FLAG, SET_TX_GROUP_MAP_FLAG_SHORT, "group_num", "Map ports to group <group_num>");
    AddOptions(TX_GROUP_PORTS_FLAG, TX_GROUP_PORTS_FLAG_SHORT, "ports", "Ports to be mapped [1,2,3,4,..,128]");

    AddOptions(SLTP_SHOW_FLAG, SLTP_SHOW_FLAG_SHORT, "", "get SLTP");
    AddOptions(SLTP_SET_FLAG, SLTP_SET_FLAG_SHORT, "set", "set SLTP");
    AddOptions(SLTP_SET_ADVANCED_FLAG, SLTP_SET_ADVANCED_FLAG_SHORT, "", "set SLTP");
    AddOptions(SLTP_TX_POLICY_FLAG, SLTP_TX_POLICY_FLAG_SHORT, "", "set TX Policy");
    AddOptions(LANE_FLAG, LANE_FLAG_SHORT, "lane", "Lane");
    AddOptions(DATABASE_FLAG, DATABASE_FLAG_SHORT, "", "DB");
    AddOptions(GVMI_ADDRESS_FLAG, GVMI_ADDRESS_FLAG_SHORT, "gvmi", "GVMI");
    AddOptions(PEPC_SET_FLAG, PEPC_SET_FLAG_SHORT, "", "set External PHY");
    AddOptions(PEPC_FORCE_MODE_FLAG, PEPC_FORCE_MODE_FLAG_SHORT, "Twisted_Pair_Force_Mode", "Twisted Pair Force Mode");

    AddOptions(MARGIN_SCAN_FLAG, MARGIN_SCAN_FLAG_SHORT, "", "Read the SerDes receive eye diagram for each lane");
    AddOptions(EYE_MEASURE_TIME_FLAG, EYE_MEASURE_TIME_FLAG_SHORT, "time",
               "Max measure time in seconds for single eye diagram");
    AddOptions(LANE_INDEX_FLAG, LANE_INDEX_FLAG_SHORT, "lane", "Run eye for specific lane");
    AddOptions(EYE_SEL_FLAG, EYE_SEL_FLAG_SHORT, "eye_sel", "Run for specific eye");

    AddOptions(FORCE_YES_FLAG, FORCE_YES_FLAG_SHORT, "", "Non-interactive mode, answer yes to all questions");

    AddOptions(PREI_RX_ERR_INJ_FLAG, PREI_RX_ERR_INJ_FLAG_SHORT, "", "Get the RX link deterioration status");
    AddOptions(PREI_MIXER_OFFSET_0, PREI_MIXER_OFFSET_0_SHORT, "value", "Eye centering control");
    AddOptions(PREI_MIXER_OFFSET_1, PREI_MIXER_OFFSET_1_SHORT, "value", "Eye centering control");
    AddOptions(PREI_SHOW_MIXERS_FLAG, PREI_SHOW_MIXERS_FLAG_SHORT, "", "Show mixers offset values");

    AddOptions(MPEINJ_PCIE_ERR_INJ_FLAG, MPEINJ_PCIE_ERR_INJ_FLAG_SHORT, "", "");
    AddOptions(MPEINJ_ERR_TYPE_FLAG, MPEINJ_ERR_TYPE_FLAG_SHORT, "type", "");
    AddOptions(MPEINJ_ERR_DURATION_FLAG, MPEINJ_ERR_DURATION_FLAG_SHORT, "duration", "");
    AddOptions(MPEINJ_INJ_DELAY_FLAG, MPEINJ_INJ_DELAY_FLAG_SHORT, "delay", "");
    AddOptions(MPEINJ_DBDF_FLAG, MPEINJ_DBDF_FLAG_SHORT, "dbdf", "");
    AddOptions(MPEINJ_ERR_PARAMETERS_FLAG, MPEINJ_ERR_PARAMETERS_FLAG_SHORT, "params", "");
    AddOptions(PPHCR_FEC_HIST_FLAG, PPHCR_FEC_HIST_FLAG_SHORT, "", "Provide histogram of FEC errors");
    AddOptions(PPHCR_SHOW_FEC_HIST_FLAG, PPHCR_SHOW_FEC_HIST_FLAG_SHORT, "", "Show FEC errors histograms");
    AddOptions(PPHCR_CLEAR_HISTOGRAM_FLAG, PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT, "", "Clears FEC errors histograms");
    AddOptions(PLANE_FLAG, PLANE_FLAG_SHORT, "plane", "plane index");

    _cmdParser.AddRequester(this);
}

void MlxlinkUi::commandsCaller()
{
    for (vector<OPTION_TYPE>::iterator it = _sendRegFuncMap.begin(); it != _sendRegFuncMap.end(); it++)
    {
        switch (*it)
        {
            case SHOW_PDDR:
                _mlxlinkCommander->showPddr();
                break;
            case SHOW_PCIE:
                _mlxlinkCommander->showPcie();
                break;
            case SHOW_MODULE:
                _mlxlinkCommander->showModuleInfo();
                break;
            case SHOW_BER:
                _mlxlinkCommander->showBer();
                break;
            case SHOW_EYE:
                _mlxlinkCommander->showEye();
                break;
            case SHOW_FEC:
                _mlxlinkCommander->showFEC();
                break;
            case SHOW_SLTP:
                _mlxlinkCommander->showSltp();
                break;
            case SHOW_BKV:
                _mlxlinkCommander->showBkv();
                break;
            case SHOW_BKV_GROUP:
                _mlxlinkCommander->showBkvGroup();
                break;
            case SET_BKV_GROUP:
                _mlxlinkCommander->setBkvGroup();
                break;
            case SET_BKV_ENTRY:
                _mlxlinkCommander->setBkvEntry();
                break;
            case SHOW_DEVICE:
                _mlxlinkCommander->showDeviceData();
                break;
            case SHOW_BER_MONITOR:
                _mlxlinkCommander->showBerMonitorInfo();
                break;
            case SHOW_EXTERNAL_PHY:
                _mlxlinkCommander->showExternalPhy();
                break;
            case SHOW_PCIE_LINKS:
                _mlxlinkCommander->showPcieLinks();
                break;
            case SEND_BER_COLLECT:
                _mlxlinkCommander->collectBER();
                break;
            case SEND_AMBER_COLLECT:
                _mlxlinkCommander->collectAMBER();
                break;
            case SEND_PAOS:
                _mlxlinkCommander->sendPaos();
                break;
            case SEND_PMAOS:
                _mlxlinkCommander->sendPmaos();
                break;
            case SEND_PTYS:
                _mlxlinkCommander->sendPtys();
                break;
            case SEND_PPLM:
                _mlxlinkCommander->sendPplm();
                break;
            case SEND_PPLR:
                _mlxlinkCommander->sendPplr();
                break;
            case SEND_PHY_RECOVERY:
                _mlxlinkCommander->handlePhyRecovery();
                break;
            case SEND_LINK_TRAINING:
                _mlxlinkCommander->handleLinkTraining();
                break;
            case SEND_PRBS:
                _mlxlinkCommander->handlePrbs();
                break;
            case SEND_SLTP:
                _mlxlinkCommander->sendSltp();
                break;
            case SEND_CLEAR_COUNTERS:
                _mlxlinkCommander->clearCounters();
                break;
            case SEND_PEPC:
                _mlxlinkCommander->sendPepc();
                break;
            case CABLE_SHOW_DUMP:
                _mlxlinkCommander->showCableDump();
                break;
            case CABLE_SHOW_DDM:
                _mlxlinkCommander->showCableDDM();
                break;
            case CABLE_EEPROM_WRITE:
                _mlxlinkCommander->writeCableEEPROM();
                break;
            case CABLE_EEPROM_READ:
                _mlxlinkCommander->readCableEEPROM();
                break;
            case SHOW_TX_GROUP_MAP:
                _mlxlinkCommander->showTxGroupMapping();
                break;
            case SET_TX_GROUP_MAP:
                _mlxlinkCommander->setTxGroupMapping();
                break;
            case GRADE_SCAN_ENABLE:
                _mlxlinkCommander->initEyeOpener();
                break;
            case ERR_INJ_ENABLE:
                _mlxlinkCommander->handleRxErrInj();
                break;
            case RS_FEC_HISTOGRAM:
                _mlxlinkCommander->initPortInfo();
                break;
            case CABLE_PRBS_CMDS:
                _mlxlinkCommander->performModulePrbsCommands();
                break;
            case CABLE_CTRL_PARM:
                _mlxlinkCommander->performControlParams();
                break;
            case PCIE_ERROR_INJ:
                _mlxlinkCommander->handlePCIeErrInj();
                break;
            case SHOW_MULTI_PORT_INFO:
                _mlxlinkCommander->showMultiPortInfo();
                break;
            case SHOW_MULTI_PORT_MODULE_INFO:
                _mlxlinkCommander->showMultiPortModuleInfo();
                break;
            case SHOW_PLR:
                _mlxlinkCommander->showPlr();
                break;
            case SHOW_KR:
                _mlxlinkCommander->showKr();
                break;
            case SHOW_RX_RECOVERY_COUNTERS:
                _mlxlinkCommander->showRxRecoveryCounters();
                break;
            case SHOW_PERIODIC_EQ:
                _mlxlinkCommander->showPeriodicEq();
                break;
            case SET_PERIODIC_EQ:
                _mlxlinkCommander->setPeriodicEq();
                break;
            default:
                break;
        }
    }
}

void MlxlinkUi::addCmd(OPTION_TYPE option)
{
    if (!isIn(option, _sendRegFuncMap))
    {
        _sendRegFuncMap.push_back(option);
    }
}

ParseStatus MlxlinkUi::HandleOption(string name, string value)
{
    addCmd(SHOW_PDDR);
    if (name == PRINT_JSON_OUTPUT_FLAG)
    {
        MlxlinkRecord::jsonFormat = true;
        MlxlinkRecord::cOut = &cerr;
        MlxlinkRecord::stdOut = stderr;
        return PARSE_OK;
    }
    else if (name == PLANE_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)(_userInput.planeIndex));
        return PARSE_OK;
    }
    else if (name == HELP_FLAG)
    {
        printHelp();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == VERSION_FLAG)
    {
        print_version_string(MLXLINK_EXEC, NULL);
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == DEVICE_FLAG)
    {
        _userInput._device = value;
        return PARSE_OK;
    }
    else if (name == MODULE_INFO_FLAG)
    {
        addCmd(SHOW_MODULE);
        _userInput._showModule = true;
        _userInput._networkCmds++;
        return PARSE_OK;
    }
    else if (name == BER_FLAG)
    {
        addCmd(SHOW_BER);
        _userInput._showCounters = true;
        return PARSE_OK;
    }
    else if (name == PPCNT_CLEAR_FLAG)
    {
        addCmd(SEND_CLEAR_COUNTERS);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == EYE_OPENING_FLAG)
    {
        addCmd(SHOW_EYE);
        _userInput._showEyeInfo = true;
        return PARSE_OK;
    }
    else if (name == PLR_INFO_FLAG)
    {
        addCmd(SHOW_PLR);
        _userInput._showPlr = true;
        return PARSE_OK;
    }
    else if (name == KR_INFO_FLAG)
    {
        addCmd(SHOW_KR);
        _userInput._showKr = true;
        return PARSE_OK;
    }
    else if (name == RX_RECOVERY_COUNTERS_FLAG)
    {
        addCmd(SHOW_RX_RECOVERY_COUNTERS);
        _userInput._showRxRecoveryCounters = true;
        return PARSE_OK;
    }
    else if (name == PERIODIC_EQ_FLAG)
    {
        addCmd(SHOW_PERIODIC_EQ);
        _userInput._showPeriodicEq = true;
        return PARSE_OK;
    }
    else if (name == SET_LINK_PEQ_FLAG)
    {
        addCmd(SET_PERIODIC_EQ);
        _userInput._periodicEqIntervalSpecified = true;
        _userInput._setPeriodicEqInterval = stoi(value, nullptr, 0);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == SLTP_SHOW_FLAG)
    {
        addCmd(SHOW_SLTP);
        _userInput._showSltp = true;
        return PARSE_OK;
    }
    else if (name == BKV_GROUPS_FLAG)
    {
        addCmd(SHOW_BKV);
        return PARSE_OK;
    }
    else if (name == BKV_GROUP_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvGroupId);
        addCmd(SHOW_BKV_GROUP);
        return PARSE_OK;
    }
    else if (name == SET_BKV_GROUP_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvGroupId);
        addCmd(SET_BKV_GROUP);
        return PARSE_OK;
    }
    else if (name == BKV_RATES_FLAG)
    {
        _userInput._bkvRates = parseParamsFromLine(toUpperCase(value));
        return PARSE_OK;
    }
    else if (name == BKV_ROLES_FLAG)
    {
        _userInput._bkvRoles = parseParamsFromLine(toUpperCase(value));
        return PARSE_OK;
    }
    else if (name == BKV_MODE_B_ROLES_FLAG)
    {
        _userInput._bkvModeBRoles = parseParamsFromLine(toUpperCase(value));
        return PARSE_OK;
    }
    else if (name == SET_BKV_ENTRY_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvGroupId);
        addCmd(SET_BKV_ENTRY);
        return PARSE_OK;
    }
    else if (name == BKV_ENTRY_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvEntry);
        _userInput._bkvEntrySpecified = true;
        return PARSE_OK;
    }
    else if (name == BKV_ADDRESS_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvAddress);
        _userInput._bkvAddressSpecified = true;
        return PARSE_OK;
    }
    else if (name == BKV_WDATA_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvWdata);
        _userInput._bkvWdataSpecified = true;
        return PARSE_OK;
    }
    else if (name == BKV_WMASK_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._bkvWmask);
        _userInput._bkvWmaskSpecified = true;
        return PARSE_OK;
    }
    else if (name == SLTP_SET_FLAG)
    {
        _userInput._sltpParams = getSltpParamsFromVector(toUpperCase(value));
        addCmd(SEND_SLTP);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == LANE_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._lane);
        _userInput._sltpLane = true;
        return PARSE_OK;
    }
    else if (name == DATABASE_FLAG)
    {
        _userInput._db = true;
        return PARSE_OK;
    }
    else if (name == SLTP_TX_POLICY_FLAG)
    {
        _userInput._txPolicy = true;
        return PARSE_OK;
    }
    else if (name == GVMI_ADDRESS_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._gvmiAddress);
        return PARSE_OK;
    }
    else if (name == SLTP_SET_ADVANCED_FLAG)
    {
        _userInput._advancedMode = true;
        return PARSE_OK;
    }
    else if (name == PORT_TYPE_FLAG)
    {
        _userInput._portType = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == LABEL_PORT_FLAG)
    {
        checkStrLength(value);
        handlePortStr(_userInput, value);
        return PARSE_OK;
    }
    else if (name == DEPTH_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._depth);
        _userInput._sendDepth = true;
        return PARSE_OK;
    }
    else if (name == PCIE_INDEX_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._pcieIndex);
        _userInput._sendPcieIndex = true;
        return PARSE_OK;
    }
    else if (name == NODE_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._node);
        _userInput._sendNode = true;
        return PARSE_OK;
    }
    else if (name == PCIE_LINKS_FLAG)
    {
        addCmd(SHOW_PCIE_LINKS);
        _userInput._links = true;
        return PARSE_OK;
    }
    else if (name == EXTENDED_PCIE_FLAG)
    {
        _userInput._extendedPcie = true;
        return PARSE_OK;
    }
    else if (name == DEVICE_DATA_FLAG)
    {
        addCmd(SHOW_DEVICE);
        return PARSE_OK;
    }
    else if (name == FEC_DATA_FLAG)
    {
        addCmd(SHOW_FEC);
        _userInput._networkCmds++;
        return PARSE_OK;
    }
    else if (name == PAOS_FLAG)
    {
        addCmd(SEND_PAOS);
        _userInput._paosCmd = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PMAOS_FLAG)
    {
        addCmd(SEND_PMAOS);
        _userInput._pmaosCmd = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PTYS_FLAG)
    {
        addCmd(SEND_PTYS);
        _userInput._ptysSpeeds = parseParamsFromLine(toUpperCase(value));
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PPLM_FLAG)
    {
        addCmd(SEND_PPLM);
        _userInput._pplmFec = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == FEC_SPEED_FLAG)
    {
        _userInput._speedFec = toLowerCase(value);
        return PARSE_OK;
    }
    else if (name == PPLR_FLAG)
    {
        addCmd(SEND_PPLR);
        _userInput._pplrLB = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PHY_RECOVERY_FLAG)
    {
        addCmd(SEND_PHY_RECOVERY);
        _userInput._phyRecovery = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PHY_RECOVERY_TYPE_FLAG)
    {
        _userInput._phyRecoveryType = value;
        return PARSE_OK;
    }
    else if (name == LINK_TRAINING_FLAG)
    {
        addCmd(SEND_LINK_TRAINING);
        _userInput._linkTraining = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PRBS_MODE_FLAG)
    {
        addCmd(SEND_PRBS);
        _userInput._prbsMode = toUpperCase(value);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PPRT_PRBS_FLAG)
    {
        _userInput._sendPprt = true;
        _userInput._pprtMode = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PPTT_PRBS_FLAG)
    {
        _userInput._sendPptt = true;
        _userInput._ppttMode = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PPRT_MODULATION_FLAG)
    {
        _userInput._pprtModulation = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PPTT_MODULATION_FLAG)
    {
        _userInput._ppttModulation = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PPRT_RATE_FLAG)
    {
        _userInput._pprtRate = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PPTT_RATE_FLAG)
    {
        _userInput._ppttRate = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PRBS_LANES_FLAG)
    {
        _userInput._prbsLanesToSet = getprbsLanesFromParams(value);
        return PARSE_OK;
    }
    else if (name == PRBS_INVERT_TX_POL_FLAG)
    {
        _userInput._prbsTxInv = true;
        return PARSE_OK;
    }
    else if (name == PRBS_INVERT_RX_POL_FLAG)
    {
        _userInput._prbsRxInv = true;
        return PARSE_OK;
    }
    else if (name == PRBS_DC_COUPLE_ALLOW_FLAG)
    {
        _userInput._prbsDcCoupledAllow = true;
        return PARSE_OK;
    }
    else if (name == FORCE_TX_ALLOWED_FLAG)
    {
        _userInput._forceTxAllowed = true;
        return PARSE_OK;
    }
    else if (name == SKIP_POWER_GOOD_CHECK_FLAG)
    {
        _userInput._skipPowerGoodCheck = true;
        return PARSE_OK;
    }
    else if (name == SYSFS_PATH_FLAG)
    {
        _userInput._sysfsPath = value;
        _userInput._sysfsPathGiven = true;
        return PARSE_OK;
    }
    else if (name == BER_COLLECT_FLAG)
    {
        addCmd(SEND_BER_COLLECT);
        _userInput._csvBer = value;
        return PARSE_OK;
    }
    else if (name == AMBER_COLLECT_FLAG)
    {
        addCmd(SEND_AMBER_COLLECT);
        _userInput._csvBer = value;
        return PARSE_OK;
    }
    else if (name == BER_LIMIT_FLAG)
    {
        _userInput._testMode = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == ITERATION_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), _userInput._iteration);
        return PARSE_OK;
    }
    else if (name == BER_MONITOR_INFO_FLAG)
    {
        addCmd(SHOW_BER_MONITOR);
        return PARSE_OK;
    }
    else if (name == PEPC_SHOW_FLAG)
    {
        addCmd(SHOW_EXTERNAL_PHY);
        return PARSE_OK;
    }
    else if (name == PEPC_FORCE_MODE_FLAG)
    {
        _userInput._sendPepcForceMode = true;
        _userInput._forceMode = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PEPC_AN_MODE_FLAG)
    {
        _userInput._sendPepcANMode = true;
        _userInput._anMode = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == PEPC_SET_FLAG)
    {
        addCmd(SEND_PEPC);
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PTYS_LINK_MODE_FORCE_FLAG)
    {
        _userInput._linkModeForce = true;
        return PARSE_OK;
    }
    else if (name == CABLE_FLAG)
    {
        _userInput._cable = true;
        return PARSE_OK;
    }
    else if (name == CABLE_DUMP_FLAG)
    {
        _userInput._dump = true;
        addCmd(CABLE_SHOW_DUMP);
        _userInput._uniqueCableCmds++;
        return PARSE_OK;
    }
    else if (name == CABLE_DDM_FLAG)
    {
        _userInput._ddm = true;
        addCmd(CABLE_SHOW_DDM);
        _userInput._uniqueCableCmds++;
        return PARSE_OK;
    }
    else if (name == CABLE_WRITE_FLAG)
    {
        _userInput._write = true;
        _userInput._bytesToWrite = parseParamsFromLine(value);
        addCmd(CABLE_EEPROM_WRITE);
        _userInput._uniqueCableCmds++;
        return PARSE_OK;
    }
    else if (name == WRITE_PAGE_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._page);
        return PARSE_OK;
    }
    else if (name == WRITE_OFFSET_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._offset);
        return PARSE_OK;
    }
    else if (name == CABLE_READ_FLAG)
    {
        _userInput._read = true;
        _userInput._uniqueCableCmds++;
        addCmd(CABLE_EEPROM_READ);
        return PARSE_OK;
    }
    else if (name == READ_LEN_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._len);
        return PARSE_OK;
    }
    else if (name == SHOW_TX_GROUP_MAP_FLAG)
    {
        addCmd(SHOW_TX_GROUP_MAP);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._showGroup);
        return PARSE_OK;
    }
    else if (name == SET_TX_GROUP_MAP_FLAG)
    {
        addCmd(SET_TX_GROUP_MAP);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._setGroup);
        return PARSE_OK;
    }
    else if (name == TX_GROUP_PORTS_FLAG)
    {
        _userInput._labelPorts = parseParamsFromLine(value);
        return PARSE_OK;
    }
    else if (name == MARGIN_SCAN_FLAG)
    {
        addCmd(GRADE_SCAN_ENABLE);
        _userInput._uniquePcieCmds++;
        return PARSE_OK;
    }
    else if (name == EYE_MEASURE_TIME_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput.measureTime);
        return PARSE_OK;
    }
    else if (name == FORCE_YES_FLAG)
    {
        _userInput.force = true;
        return PARSE_OK;
    }
    else if (name == LANE_INDEX_FLAG)
    {
        checkStrLength(value);
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput._lane);
        _userInput.gradeScanPerLane = true;
        _userInput.laneSpecified = true;
        return PARSE_OK;
    }
    else if (name == EYE_SEL_FLAG)
    {
        checkStrLength(value);
        _userInput.eyeSelect = toUpperCase(value);
        _userInput.eyeSelectSpecified = true;
        return PARSE_OK;
    }
    else if (name == PREI_RX_ERR_INJ_FLAG)
    {
        addCmd(ERR_INJ_ENABLE);
        _userInput.enableRxErrInj = true;
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == PREI_MIXER_OFFSET_0)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput.mixerOffset0);
        return PARSE_OK;
    }
    else if (name == PREI_MIXER_OFFSET_1)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput.mixerOffset1);
        return PARSE_OK;
    }
    else if (name == PREI_SHOW_MIXERS_FLAG)
    {
        _userInput.showMixers = true;
        return PARSE_OK;
    }
    else if (name == PPHCR_FEC_HIST_FLAG)
    {
        addCmd(RS_FEC_HISTOGRAM);
        _userInput.enableFecHistogram = true;
        return PARSE_OK;
    }
    else if (name == PPHCR_SHOW_FEC_HIST_FLAG)
    {
        _userInput.showFecHistogram = true;
        return PARSE_OK;
    }
    else if (name == PPHCR_CLEAR_HISTOGRAM_FLAG)
    {
        _userInput.clearFecHistogram = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_SELECT)
    {
        addCmd(CABLE_PRBS_CMDS);
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_SELECT] = toUpperCase(value);
        _userInput.isPrbsSelProvided = true;
        _userInput._uniqueCableCmds++;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_MODE)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_MODE] = toUpperCase(value);
        _userInput.isPrbsModeProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_GEN_PAT)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_GEN_PAT] = toUpperCase(value);
        _userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_GEN_SWAP)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_GEN_SWAP] = "SWAP";
        _userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_GEN_INV)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_GEN_INV] = "INV";
        _userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_GEN_LANES)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_GEN_LANES] = value;
        _userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_CH_PAT)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_CH_PAT] = toUpperCase(value);
        _userInput.isPrbsChProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_CH_SWAP)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_CH_SWAP] = "SWAP";
        _userInput.isPrbsChProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_CH_INV)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_CH_INV] = "INV";
        _userInput.isPrbsChProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_CH_LANES)
    {
        _userInput.modulePrbsParams[MODULE_PRBS_CH_LANES] = value;
        _userInput.isPrbsChProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_LANE_RATE)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_RATE] = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_SHOW_DIAG)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_SHOW_DIAG] = value;
        _userInput.isPrbsShowDiagProvided = true;
        return PARSE_OK;
    }
    else if (name == CABLE_PRBS_CLEAR_DIAG)
    {
        checkStrLength(value);
        _userInput.modulePrbsParams[MODULE_PRBS_CLEAR_DIAG] = value;
        _userInput.isPrbsClearDiagProvided = true;
        return PARSE_OK;
    }
    else if (name == CTRL_PARAM_FLAG)
    {
        addCmd(CABLE_CTRL_PARM);
        _userInput.isModuleConfigParamsProvided = true;
        return PARSE_OK;
    }
    else if (name == CTRL_PARAM_TX_EQ_FLAG)
    {
        checkStrLength(value);
        _userInput.configParamsToSet.push_back(make_pair(CABLE_CONTROL_PARAMETERS_SET_TX_EQ, value));
        return PARSE_OK;
    }
    else if (name == CTRL_PARAM_RX_EMPH_FLAG)
    {
        checkStrLength(value);
        _userInput.configParamsToSet.push_back(make_pair(CABLE_CONTROL_PARAMETERS_SET_RX_EMPH, value));
        return PARSE_OK;
    }
    else if (name == CTRL_PARAM_RX_POST_EMPH_FLAG)
    {
        checkStrLength(value);
        _userInput.configParamsToSet.push_back(make_pair(CABLE_CONTROL_PARAMETERS_SET_RX_POST_EMPH, value));
        return PARSE_OK;
    }
    else if (name == CTRL_PARAM_RX_AMP_FLAG)
    {
        checkStrLength(value);
        _userInput.configParamsToSet.push_back(make_pair(CABLE_CONTROL_PARAMETERS_SET_RX_AMP, value));
        return PARSE_OK;
    }
    else if (name == MPEINJ_PCIE_ERR_INJ_FLAG)
    {
        addCmd(PCIE_ERROR_INJ);
        _userInput.isPcieErrInjProvided = true;
        _userInput._uniquePcieCmds++;
        return PARSE_OK;
    }
    else if (name == MPEINJ_ERR_TYPE_FLAG)
    {
        _userInput.errorType = toUpperCase(value);
        return PARSE_OK;
    }
    else if (name == MPEINJ_ERR_DURATION_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput.errorDuration);
        return PARSE_OK;
    }
    else if (name == MPEINJ_INJ_DELAY_FLAG)
    {
        RegAccessParser::strToUint32((char*)value.c_str(), (u_int32_t&)_userInput.injDelay);
        return PARSE_OK;
    }
    else if (name == MPEINJ_ERR_PARAMETERS_FLAG)
    {
        _userInput.parameters = parseParamsFromLine(value);
        return PARSE_OK;
    }
    else if (name == MPEINJ_DBDF_FLAG)
    {
        _userInput.dbdf = value;
        return PARSE_OK;
    }
    else if (name == MULTI_PORT_INFO_ACRONYM_FLAG || name == MULTI_PORT_INFO_FLAG)
    {
        addCmd(SHOW_MULTI_PORT_INFO);
        _userInput._showMultiPortInfo = true;
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    else if (name == MULTI_PORT_MODULE_INFO_ACRONYM_FLAG || name == MULTI_PORT_MODULE_INFO_FLAG)
    {
        addCmd(SHOW_MULTI_PORT_MODULE_INFO);
        _userInput._showMultiPortModuleInfo = true;
        _userInput._uniqueCmds++;
        return PARSE_OK;
    }
    return PARSE_ERROR;
}

int MlxlinkUi::run(int argc, char** argv)
{
    int exit_code = 0;

    initCmdParser();

    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT)
    {
        return exit_code;
    }
    else if ((rc == PARSE_ERROR) || (rc == PARSE_ERROR_SHOW_USAGE))
    {
        throw MlxRegException("failed to parse arguments. " + string(_cmdParser.GetErrDesc()));
    }

    if (_userInput._forceSplit && !_userInput._secondSplitProvided)
    {
        _userInput._secondSplitProvided = _userInput._forceSplit;
        _userInput._secondSplitPort = _userInput._forceSplitValue;
    }

    paramValidate();

    _mf = mopen(_userInput._device.c_str());

    if (!_mf)
    {
        throw MlxRegException("Failed to open device: \"" + _userInput._device + "\", " + strerror(errno));
    }
    if (!MlxRegLib::isDeviceSupported(_mf))
    {
        mclose(_mf);
        throw MlxRegException("Device is not supported");
    }

    initMlxlinkCommander();

    commandsCaller();

    if (_mlxlinkCommander->_allUnhandledErrors != "")
    {
        exit_code = 1;
        if (!MlxlinkRecord::jsonFormat)
        {
            MlxlinkRecord::printErrorsSection(_mlxlinkCommander->_mlxlinkMaps->_showErrorsTitle,
                                              _mlxlinkCommander->_allUnhandledErrors);
        }
    }

    if (MlxlinkRecord::jsonFormat)
    {
        _mlxlinkCommander->prepareJsonOut();
        cout << _mlxlinkCommander->_jsonRoot.toStyledString();
    }

    cout << endl;
    return exit_code;
}

// SetPCIDomain should not throw exceptions, even if failed to set domain.
// we use try/catch to cover any unexpected errors.
void MlxlinkUi::initPCIDomain()
{
    try
    {
        PCILibrary::SetPCIDomain();
    }
    catch (const std::exception& exc)
    {
        MlxlinkRecord::printWar(
          "Warning: Failed to set one or more PCI domains, use \"export MFT_PRINT_LOG=1\" to get more details.",
          _mlxlinkCommander->_jsonRoot);
    }
}