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

MlxlinkUi::MlxlinkUi() :
    CommandLineRequester(MLXLINK_EXEC " OPTIONS"),
    _cmdParser(MLXLINK_EXEC)
{
}

MlxlinkUi::~MlxlinkUi()
{
    if (_mlxlinkCommander) {
         delete _mlxlinkCommander;
    }
}

void MlxlinkUi::createMlxlinkCommander()
{
    _mlxlinkCommander = new MlxlinkCommander();
}

void MlxlinkUi::printSynopsisHeader()
{
    printf(
        IDENT "NAME:\n"
        IDENT2 MLXLINK_EXEC "\n\n"
        IDENT "SYNOPSIS:\n"
        IDENT2 MLXLINK_EXEC " [OPTIONS]\n\n"
        IDENT "DESCRIPTION:\n"
        IDENT2 "The " MLXLINK_EXEC " tool is used to check and debug link status and issues related to them.\n"
        IDENT2 "The tool can be used on different links and cables (passive, active, transceiver and backplane).\n");
    printf("\n");
    printf(IDENT "OPTIONS:\n");
    MlxlinkRecord::printFlagLine(HELP_FLAG_SHORT, HELP_FLAG, "", "Display help message.");
    MlxlinkRecord::printFlagLine(VERSION_FLAG_SHORT, VERSION_FLAG, "",
                  "Display version info.");
    MlxlinkRecord::printFlagLine(DEVICE_FLAG_SHORT, DEVICE_FLAG, "device",
                  "Perform operation for a specified mst device");
    MlxlinkRecord::printFlagLine(LABEL_PORT_FLAG_SHORT, LABEL_PORT_FLAG, "port_number",
                  "Port Number");
    MlxlinkRecord::printFlagLine(PORT_TYPE_FLAG_SHORT, PORT_TYPE_FLAG, "port_type",
                                 "Port Type [NETWORK(Default)/PCIE]");
    MlxlinkRecord::printFlagLine(DEPTH_FLAG_SHORT, DEPTH_FLAG, "depth", "depth level of the DUT of some hierarchy (PCIE only)");
    MlxlinkRecord::printFlagLine(PCIE_INDEX_FLAG_SHORT, PCIE_INDEX_FLAG, "pcie_index", "PCIe index number (Internal domain index) (PCIE only)");
    MlxlinkRecord::printFlagLine(NODE_FLAG_SHORT, NODE_FLAG, "node", "the node within each depth (PCIE only)");
    MlxlinkRecord::printFlagLine(PRINT_JSON_OUTPUT_FLAG_SHORT, PRINT_JSON_OUTPUT_FLAG, "", "Print the output in json format");
}

void MlxlinkUi::printSynopsisQueries()
{
    printf(IDENT "QUERIES:\n");
    MlxlinkRecord::printFlagLine(PCIE_LINKS_FLAG_SHORT, PCIE_LINKS_FLAG, "",
                  "Show valid PCIe links (PCIE only)");
    MlxlinkRecord::printFlagLine(MODULE_INFO_FLAG_SHORT, MODULE_INFO_FLAG, "",
                  "Show Module Info");
    MlxlinkRecord::printFlagLine(BER_FLAG_SHORT, BER_FLAG, "",
                  "Show Physical Counters and BER Info");
    MlxlinkRecord::printFlagLine(EYE_OPENING_FLAG_SHORT, EYE_OPENING_FLAG, "",
                  "Show Eye Opening Info");
    MlxlinkRecord::printFlagLine(FEC_DATA_FLAG_SHORT, FEC_DATA_FLAG, "", "Show FEC Capabilities");
    MlxlinkRecord::printFlagLine(SLTP_SHOW_FLAG_SHORT, SLTP_SHOW_FLAG, "", "Show Transmitter Info");
    MlxlinkRecord::printFlagLine(SHOW_TX_GROUP_MAP_FLAG_SHORT, SHOW_TX_GROUP_MAP_FLAG, "group_num",
                      "Display all label ports mapped to group <group_num> (for Spectrum-2 and Quantum devices)");
    MlxlinkRecord::printFlagLine(DEVICE_DATA_FLAG_SHORT, DEVICE_DATA_FLAG, "", "General Device Info");
    MlxlinkRecord::printFlagLine(BER_MONITOR_INFO_FLAG_SHORT, BER_MONITOR_INFO_FLAG, "", "Show BER Monitor Info (not supported for HCA)");
    MlxlinkRecord::printFlagLine(PEPC_SHOW_FLAG_SHORT, PEPC_SHOW_FLAG, "", "Show External PHY Info (for Ethernet switches only)");
}

void MlxlinkUi::printSynopsisCommands()
{
    printf(IDENT "COMMANDS:\n");
    MlxlinkRecord::printFlagLine(PAOS_FLAG_SHORT, PAOS_FLAG, "port_state",
                  "Configure Port State [UP(up)/DN(down)/TG(toggle)]");
    MlxlinkRecord::printFlagLine(PTYS_FLAG_SHORT, PTYS_FLAG, "speeds",
                  "Configure Speeds [NDR,HDR,EDR,FDR10,FDR,QDR,DDR,SDR,400G_8X,200G_4X,100G_2X,50G_1X,100G,100G_4X,50G,50G_2X,25G,40X,10G,2.5G,1G]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PTYS_LINK_MODE_FORCE_FLAG_SHORT, PTYS_LINK_MODE_FORCE_FLAG, "",
                  "Configure Link Mode Force (Disable AN)");
    MlxlinkRecord::printFlagLine(PPLR_FLAG_SHORT, PPLR_FLAG, "loopback",
                  "Configure Loopback Mode [NO(no loopback)/RM(phy remote Rx-to-Tx loopback)/PH(internal phy Tx-to-Rx loopback)/EX(external loopback connector needed)/EX(external Tx-to-Rx loopback)]");
    MlxlinkRecord::printFlagLine(PPLM_FLAG_SHORT, PPLM_FLAG, "fec_override",
                  "Configure FEC [AU(Auto)/NF(No-FEC)/FC(FireCode FEC)/RS(RS-FEC)/LL(LL-RS-FEC)/DF-RS(Interleaved_RS-FEC)/DF-LL(Interleaved_LL_RS-FEC)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(FEC_SPEED_FLAG_SHORT, FEC_SPEED_FLAG, "fec_speed",
                  "Speed to Configure FEC [100G,56G,50G,40G,25G,10G,800G_8X,400G_4x,400G_8X,200G_2X,200G_4X,100G_2X,50G_1X,100G_4X] (Default is Active Speed)");
    MlxlinkRecord::printFlagLine(SLTP_SET_FLAG_SHORT, SLTP_SET_FLAG, "params",
                  "Configure Transmitter Parameters For 16nm devices: [pre2Tap,preTap,mainTap,postTap,m2lp,amp] For 28nm devices: [Pol,tap0,tap1,tap2,bias,preemp_mode]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(LANE_FLAG_SHORT, LANE_FLAG, "transmitter_lane",
                  "Transmitter Lane to Set (Optional - Default All Lanes)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(DATABASE_FLAG_SHORT, DATABASE_FLAG, "", "Save Transmitter Configuration for Current Speed Permanently (Optional)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(SLTP_TX_POLICY_FLAG_SHORT, SLTP_TX_POLICY_FLAG, "", "Set the parameters according to Data Base only, otherwise it will be set according to the best possible configuration chosen by the system (e.g. KR-startup) (Optional)");
    MlxlinkRecord::printFlagLine(SET_TX_GROUP_MAP_FLAG_SHORT, SET_TX_GROUP_MAP_FLAG, "group_num",
                      "Map ports to group <group_num> (for Spectrum-2 and Quantum devices)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(TX_GROUP_PORTS_FLAG_SHORT, TX_GROUP_PORTS_FLAG, "ports",
                      "Ports to be mapped [1,2,3,4,...,128]");
    MlxlinkRecord::printFlagLine(PRBS_MODE_FLAG_SHORT, PRBS_MODE_FLAG, "prbs_mode",
                  "Physical Test Mode Configuration [EN(enable)/DS(disable)/TU(perform tuning)]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPRT_PRBS_FLAG_SHORT, PPRT_PRBS_FLAG, "rx_prbs_mode",
                  "RX PRBS Mode [PRBS31/PRBS23A/PRBS23B/PRBS23C/PRBS23D/PRBS7/PRBS11/PRBS11A/PRBS11B/PRBS11C/PRBS11D/PRBS9/IDLE/SQUARE_WAVEA/SQUARE_WAVEB/SQUARE_WAVEC/SQUARE_WAVED/PRBS13A/PRBS13B/PRBS13C/PRBS13D/SSPR/SSPRQ/LT_frames/PRBS15/PRBS28] (Optional - Default PRBS31)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPTT_PRBS_FLAG_SHORT, PPTT_PRBS_FLAG, "tx_prbs_mode",
                  "TX PRBS Mode [PRBS31/PRBS23A/PRBS23B/PRBS23C/PRBS23D/PRBS7/PRBS11/PRBS11A/PRBS11B/PRBS11C/PRBS11D/PRBS9/IDLE/SQUARE_WAVEA/SQUARE_WAVEB/SQUARE_WAVEC/SQUARE_WAVED/PRBS13A/PRBS13B/PRBS13C/PRBS13D/SSPR/SSPRQ/LT_frames/PRBS15/PRBS28/SQUARE_WAVE3,SQUARE_WAVE13,SQUARE_WAVE30] (Optional - Default PRBS31] (Optional - Default PRBS31)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPRT_RATE_FLAG_SHORT, PPRT_RATE_FLAG, "rx_lane_rate",
                  "RX Lane Rate [HDR,EDR,FDR10,FDR,QDR,DDR,SDR,400G_8X,200G_4X,100G_2X,50G_1X,100G,100G_4X,50G,50G_2X,25G,40X,10G,2.5G,1G]  (Optional - Default 25G)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPTT_RATE_FLAG_SHORT, PPTT_RATE_FLAG, "tx_lane_rate",
                  "TX Lane Rate [HDR,EDR,FDR10,FDR,QDR,DDR,SDR,400G_8X,200G_4X,100G_2X,50G_1X,100G,100G_4X,50G,50G_2X,25G,40X,10G,2.5G,1G]  (Optional - Default 25G)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_INVERT_TX_POL_FLAG_SHORT, PRBS_INVERT_TX_POL_FLAG, "",
                  "PRBS TX polarity inversion (Optional - Default No Inversion)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_INVERT_RX_POL_FLAG_SHORT, PRBS_INVERT_RX_POL_FLAG, "",
                  "PRBS RX polarity inversion (Optional - Default No Inversion)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PRBS_LANES_FLAG_SHORT, PRBS_LANES_FLAG, "lanes",
                  "PRBS lanes to set (one or more lane separated by comma)[0,1,2,...,7] (Optional - Default all lanes)");
    MlxlinkRecord::printFlagLine(BER_COLLECT_FLAG_SHORT, BER_COLLECT_FLAG, "csv_file",
                  "Port Extended Information Collection [CSV File]");
    MlxlinkRecord::printFlagLine(AMBER_COLLECT_FLAG_SHORT, AMBER_COLLECT_FLAG, "csv_file",
                  "AmBER Port Extended Information Collection For 16nm Products and Later [CSV File]");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(BER_LIMIT_FLAG_SHORT, BER_LIMIT_FLAG, "limit_criteria",
                  "BER Limit Criteria [Nominal(Default)/Corner/Drift] (Optional - Default Nominal)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(ITERATION_FLAG_SHORT, ITERATION_FLAG, "iteration", "Iteration Number of BER Collection");
    MlxlinkRecord::printFlagLine(PPCNT_CLEAR_FLAG_SHORT, PPCNT_CLEAR_FLAG, "",
                  "Clear Counters");
    MlxlinkRecord::printFlagLine(PEPC_SET_FLAG_SHORT, PEPC_SET_FLAG, "",
                  "Set External PHY (for Ethernet switches only)");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PEPC_FORCE_MODE_FLAG_SHORT, PEPC_FORCE_MODE_FLAG, "twisted_pair_force_mode",
                  "Twisted Pair Force Mode [MA(Master)/SL(Slave)]");
    MlxlinkRecord::printFlagLine(CABLE_FLAG_SHORT, CABLE_FLAG, "",
            "Perform operations on the cables");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(CABLE_DUMP_FLAG_SHORT, CABLE_DUMP_FLAG, "",
            "Dump cable pages in raw format");
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

    MlxlinkRecord::printFlagLine(MARGIN_SCAN_FLAG_SHORT, MARGIN_SCAN_FLAG, "",
            "Read the SerDes eye margins per lane");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(EYE_MEASURE_TIME_FLAG_SHORT, EYE_MEASURE_TIME_FLAG, "time",
            "Measure time in seconds for single eye [10/30/60/90/120/240/480/600/900] (Optional - Default 60 for PCIe and 30 for Network ports)");
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

    MlxlinkRecord::printFlagLine(PPHCR_FEC_HIST_FLAG_SHORT, PPHCR_FEC_HIST_FLAG, "",
            "Provide histogram of FEC errors. The result is divided to bins. "\
            "Each bin is holding different number of errored bit within FEC protected block");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPHCR_SHOW_FEC_HIST_FLAG_SHORT, PPHCR_SHOW_FEC_HIST_FLAG, "",
            "Show FEC errors histograms");
    printf(IDENT);
    MlxlinkRecord::printFlagLine(PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT, PPHCR_CLEAR_HISTOGRAM_FLAG, "",
            "Clears FEC errors histograms");

    MlxlinkRecord::printFlagLine(FORCE_YES_FLAG_SHORT, FORCE_YES_FLAG, "",
            "Non-interactive mode, answer yes to all questions");
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
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure FEC",
           MLXLINK_EXEC " -d <device> -p <port_number> --fec RS");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Port for Physical Test Mode",
           MLXLINK_EXEC " -d <device> -p <port_number> --test_mode EN (--rx_prbs PRBS31 --rx_rate 25G --tx_prbs PRBS7 --tx_rate 10G)");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Perform PRBS Tuning",
           MLXLINK_EXEC " -d <device> -p <port_number> --test_mode TU");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Cable operations",
           MLXLINK_EXEC " -d <device> --cable options");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Dump cable EEPROM pages",
           MLXLINK_EXEC " -d <device> --cable --dump");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Get cable DDM info",
           MLXLINK_EXEC " -d <device> --cable --ddm");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Read from cable",
           MLXLINK_EXEC " -d <device> --cable --read --page <page number> --offset <bytes offset> --length <number of bytes>");
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Write to cable",
           MLXLINK_EXEC " -d <device> --cable --write <bytes separated by comma> --page <page number> --offset <bytes offset> ");
    if (_mlxlinkCommander->_userInput._advancedMode) {
        printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters (on lane, to database)",
               MLXLINK_EXEC " -d <device> -p <port_number> --serdes_tx <polarity>,<ob_tap0>,<ob_tap1>,<ob_tap2>,<ob_bias>,<ob_preemp_mode>,<ob_reg>,<ob_leva> (--serdes_tx_lane <lane number>) (--database)");
    } else {
        printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters (on lane, to database)",
               MLXLINK_EXEC " -d <device> -p <port_number> --serdes_tx <polarity>,<ob_tap0>,<ob_tap1>,<ob_tap2>,<ob_bias>,<ob_preemp_mode> (--serdes_tx_lane <lane number>) (--database)");
    }
    printf(IDENT2 "%-40s: \n" IDENT3 "%s\n", "Configure Transmitter Parameters for 16nm devices",
            MLXLINK_EXEC " -d <device> -p <port_number> --serdes_tx <pre_2_tap>,<pre_tap>,<main_tap>,<post_tap>,<ob_m2lp>,<ob_amp>");

}

void MlxlinkUi::validateMandatoryParams()
{
    if (_mlxlinkCommander->_device == "") {
        throw MlxRegException("Please provide a device name");
    }
    if (_mlxlinkCommander->_userInput._links &&
            _mlxlinkCommander->_userInput._portType != "PCIE") {
        throw MlxRegException("The --" PCIE_LINKS_FLAG " option is valid only with --port_type PCIE");
    }
    if (_mlxlinkCommander->_userInput._links &&
            (_mlxlinkCommander->_userInput._showEyeInfo || _mlxlinkCommander->_userInput._showSltp ||
                    _mlxlinkCommander->_userInput._showCounters ||  _mlxlinkCommander->_userInput._showSlrp )) {
        throw MlxRegException("No options allowed to use while querying --" PCIE_LINKS_FLAG);
    }
    if ((_mlxlinkCommander->_userInput._labelPort == 0) && (_mlxlinkCommander->_userInput._portType != "PCIE")) {
        throw MlxRegException("Please provide a valid port number");
    }
}

void MlxlinkUi::validatePCIeParams()
{
    bool dpnFlags = _mlxlinkCommander->_userInput._sendNode ||
                _mlxlinkCommander->_userInput._sendDepth ||
                _mlxlinkCommander->_userInput._sendPcieIndex;

    if (_mlxlinkCommander->_userInput._portType == "PCIE") {
        _mlxlinkCommander->_userInput._pcie = true;
        if (_mlxlinkCommander->_uniqueCmds) {
            throw MlxRegException("Command flags are not available for PCIE");
        }
        if (_mlxlinkCommander->_networkCmds) {
            throw MlxRegException("FEC and Module Info flags are not available for PCIE");
        }

        replace(_sendRegFuncMap.begin(), _sendRegFuncMap.end(), SHOW_PDDR, SHOW_PCIE);

        if (dpnFlags) {
            if (!(_mlxlinkCommander->_userInput._sendNode &&
                _mlxlinkCommander->_userInput._sendDepth &&
                _mlxlinkCommander->_userInput._sendPcieIndex)) {
                throw MlxRegException("The --depth, --pcie_index and --node must be specified for PCIE");
            } else {
                _mlxlinkCommander->_userInput._sendDpn = true;
            }
        }
        if (_mlxlinkCommander->_userInput._portSpecified) {
            if (dpnFlags) {
                throw MlxRegException("For PCIE port, either port flag or depth, pcie_index and node flags should be specified");
           }
        }
    } else if (dpnFlags) {
        throw MlxRegException("The --depth, --node and --pcie_index flags are valid only with --port_type PCIE");
    }
}

void MlxlinkUi::validateGeneralCmdsParams()
{
    if (_mlxlinkCommander->_uniqueCmds > 1) {
        throw MlxRegException("Commands are mutually exclusive!");
    }
    if (isIn(SEND_PAOS, _sendRegFuncMap) && !checkPaosCmd(_mlxlinkCommander->_userInput._paosCmd)) {
        throw MlxRegException(
                  "Please provide a valid paos command [UP(up)/DN(down)/TG(toggle)]");
    }
    if (!isIn(SEND_PPLM, _sendRegFuncMap) && _mlxlinkCommander->_userInput._speedFec != "") {
        throw MlxRegException(
                  "The --fec_speed flag is valid only with --fec flag");
    }
    if (isIn(SEND_SLTP, _sendRegFuncMap)) {
        if (_mlxlinkCommander->_userInput._sltpLane && _mlxlinkCommander->_userInput._db) {
            throw MlxRegException(
                      "Lane and Database flags are mutually exclusive");
        }
    } else if (_mlxlinkCommander->_userInput._sltpLane || _mlxlinkCommander->_userInput._db ||
               _mlxlinkCommander->_userInput._txPolicy) {
        throw MlxRegException(LANE_FLAG ", --" DATABASE_FLAG " and --" SLTP_TX_POLICY_FLAG
                              " flags are valid only with Configure Transmitter Parameters flag (--" SLTP_SET_FLAG ")");
    }
}

void MlxlinkUi::validatePRBSParams()
{
    bool prbsFlags = _mlxlinkCommander->_userInput._sendPprt ||
                    _mlxlinkCommander->_userInput._sendPptt ||
                    _mlxlinkCommander->_userInput._pprtRate != "" ||
                    _mlxlinkCommander->_userInput._pprtRate != "" ||
                    _mlxlinkCommander->_userInput._prbsTxInv ||
                    _mlxlinkCommander->_userInput._prbsRxInv ||
                    _mlxlinkCommander->_userInput._prbsLanesToSet.size() > 0;
    if (isIn(SEND_PRBS, _sendRegFuncMap)) {
        if (!checkPrbsCmd(_mlxlinkCommander->_userInput._prbsMode)) {
            throw MlxRegException(
                      "you must provide a valid PRBS test mode [DS/EN/TU]");
        }
        if (_mlxlinkCommander->_userInput._prbsMode == "DS" ||
                _mlxlinkCommander->_userInput._prbsMode == "TU") {
            if (prbsFlags) {
                throw MlxRegException(
                          "PRBS parameters flags valid only with PRBS Enable flag (--test_mode EN)");
            }
        }
    } else if (prbsFlags) { // add check for lanes flag to work with PRBS and eye scan only
        throw MlxRegException("PRBS parameters flags valid only with PRBS Enable flag (--test_mode EN)");
    }
}

void MlxlinkUi::validateModulePRBSParams()
{
    if (!_mlxlinkCommander->_userInput.isPrbsSelProvided && (_mlxlinkCommander->_userInput.isPrbsModeProvided ||
                                                             _mlxlinkCommander->_userInput.isPrbsChProvided ||
                                                             _mlxlinkCommander->_userInput.isPrbsGenProvided ||
                                                             _mlxlinkCommander->_userInput.isPrbsShowDiagProvided ||
                                                             _mlxlinkCommander->_userInput.isPrbsClearDiagProvided)) {
        throw MlxRegException("Please select PRBS module side using --" CABLE_PRBS_SELECT " [MEDIA|HOST] flag!");
    }

    if (!_mlxlinkCommander->_userInput.isPrbsModeProvided && (_mlxlinkCommander->_userInput.isPrbsChProvided ||
                                                              _mlxlinkCommander->_userInput.isPrbsGenProvided)) {
        throw MlxRegException("--" CABLE_PRBS_MODE " flag should be provided!");
    }

    if (_mlxlinkCommander->_userInput.isPrbsModeProvided && (_mlxlinkCommander->_userInput.isPrbsShowDiagProvided ||
                                                             _mlxlinkCommander->_userInput.isPrbsClearDiagProvided)) {
        throw MlxRegException("PRBS Module Diagnostic info flags are not working while configuring the PRBS test mode!");
    }

    if (_mlxlinkCommander->_userInput.isPrbsShowDiagProvided && _mlxlinkCommander->_userInput.isPrbsClearDiagProvided) {
        throw MlxRegException("are mutually exclusive, please select one command only");
    }
}

void MlxlinkUi::validateSpeedAndCSVBerParams()
{
    bool berCollect = isIn(SEND_BER_COLLECT, _sendRegFuncMap);
    bool amBerCollect = isIn(SEND_AMBER_COLLECT, _sendRegFuncMap);
    if (berCollect && amBerCollect) {
        throw MlxRegException("--" BER_COLLECT_FLAG " and --" AMBER_COLLECT_FLAG " "\
                "are mutually exclusive, please select one command only");
    }
    if (berCollect || amBerCollect) {
        if (!endsWith(_mlxlinkCommander->_userInput._csvBer, ".csv")) {
            throw MlxRegException("you must provide a valid .csv file");
        }
        if (!checkTestMode(_mlxlinkCommander->_userInput._testMode)) {
            throw MlxRegException(
                      "Please provide a valid test mode [Nominal(Default)/Corner/Drift]");
        }
    } else if (_mlxlinkCommander->_userInput._testMode != "Nominal") {
        throw MlxRegException(
                  "BER Limit Criteria flag is valid only with Port Information Collection flag (--bc)");
    }
    if (isIn(SEND_PEPC, _sendRegFuncMap)) {
        if (!_mlxlinkCommander->_userInput._sendPepcForceMode) {
            throw MlxRegException(
                      "Please provide --twisted_pair_force_mode");
        }
        if (_mlxlinkCommander->_userInput._sendPepcForceMode &&
                !checkPepcForceMode(_mlxlinkCommander->_userInput._forceMode)) {
            throw MlxRegException(
                      "Please provide a valid twisted pair force mode [MA(Master)/SL(Slave)]");
        }
    } else {
        if (_mlxlinkCommander->_userInput._sendPepcForceMode) {
            throw MlxRegException(
                      "Please provide --set_external_phy option to configure the twisted pair force mode");
        }
    }
    if (_mlxlinkCommander->_linkModeForce && _mlxlinkCommander->_ptysSpeeds.size() != 1) {
        throw MlxRegException(
                  "--link_mode_force should receive exactly one speed using --speeds");
    }
}

void MlxlinkUi::validateCableParams()
{
    bool readWriteFlags = _mlxlinkCommander->_userInput._page >= 0 ||
                      _mlxlinkCommander->_userInput._offset >= 0 ||
                      _mlxlinkCommander->_userInput._len >= 0 ;
    bool prbsParamProvided = _mlxlinkCommander->_userInput.modulePrbsParams.size();
    bool cablePrbsParamProvided = _mlxlinkCommander->_userInput.isPrbsSelProvided || prbsParamProvided;
    bool cableCommandProvided = _mlxlinkCommander->_userInput._dump ||
                                _mlxlinkCommander->_userInput._write ||
                                _mlxlinkCommander->_userInput._read ||
                                _mlxlinkCommander->_userInput._ddm ||
                                cablePrbsParamProvided;

    if(!_mlxlinkCommander->_userInput._cable && (cableCommandProvided || readWriteFlags)){
        throw MlxRegException("\"--" CABLE_FLAG "\" flag should be specified!");
    } else if (_mlxlinkCommander->_userInput._cable) {
        if ((_mlxlinkCommander->_uniqueCableCmds > 1) || !cableCommandProvided) {
            throw MlxRegException("Please choose one of " CABLE_FLAG " operations!");
        }
        if ((_mlxlinkCommander->_userInput._read ||
                _mlxlinkCommander->_userInput._write) &&
                (_mlxlinkCommander->_userInput._page == -1 ||
                        _mlxlinkCommander->_userInput._offset == -1)) {
            throw MlxRegException("\"--" WRITE_PAGE_FLAG "\" and \"--" WRITE_OFFSET_FLAG "\" flags should be specified!");
        }
        if (readWriteFlags) {
            if (!_mlxlinkCommander->_userInput._write && !_mlxlinkCommander->_userInput._read) {
                throw MlxRegException("Read or Write flag should be specified!");
            }

            if (_mlxlinkCommander->_userInput._read) {
                if (_mlxlinkCommander->_userInput._len == -1) {
                    _mlxlinkCommander->_userInput._len = 1; // default number of bytes to read
                } else if (_mlxlinkCommander->_userInput._len == 0) {
                    throw MlxRegException("The length cannot be zero!");
                }
            } else if (_mlxlinkCommander->_userInput._len >= 0) {
                throw MlxRegException("\"--" READ_LEN_FLAG "\" flag is working with read option only!");
            }
        }
    }
}

void MlxlinkUi::validateTxGroupParams()
{
    if (_mlxlinkCommander->_userInput._showGroup >=0) {
        if (!_mlxlinkCommander->_userInput._labelPorts.empty()) {
            throw MlxRegException("\"--" TX_GROUP_PORTS_FLAG
                    "\" flag is working with " SET_TX_GROUP_MAP_FLAG " only!");
        }
    }

    if (_mlxlinkCommander->_userInput._setGroup >= 0 &&
            _mlxlinkCommander->_userInput._showGroup >= 0) {
        throw MlxRegException("Choose one of operations!");
    }

    if (_mlxlinkCommander->_userInput._setGroup >= 0) {
        if (_mlxlinkCommander->_userInput._labelPorts.empty()) {
            throw MlxRegException("\"--" TX_GROUP_PORTS_FLAG "\" should be specified!");
        }
    }
    if (_mlxlinkCommander->_userInput._setGroup >= MAX_TX_GROUP_COUNT ||
            _mlxlinkCommander->_userInput._showGroup >= MAX_TX_GROUP_COUNT ) {
        throw MlxRegException("Tx group is invalid, it can be in range [0-9]!");
    }
    if (_mlxlinkCommander->_userInput._setGroup == -1 &&
            !_mlxlinkCommander->_userInput._labelPorts.empty()) {
        throw MlxRegException("\"--" SET_TX_GROUP_MAP_FLAG "\" should be specified!");
    }
}

void MlxlinkUi::validateGradeScanParams()
{
    if(_mlxlinkCommander->_userInput.eyeSelectSpecified) {
        if (_mlxlinkCommander->_userInput._portType == "PCIE") {
            throw MlxRegException(EYE_SEL_FLAG " flag is working with Network ports only!");
        }
    }
}

void MlxlinkUi::validateErrInjParams()
{
    bool errInjEnable = _mlxlinkCommander->_userInput.enableRxErrInj;
    bool showMixers = _mlxlinkCommander->_userInput.showMixers;
    bool mixerControl = _mlxlinkCommander->_userInput.mixerOffset0 >= 0 ||
                        _mlxlinkCommander->_userInput.mixerOffset1 >= 0;
    if ((errInjEnable) &&
            ((!mixerControl && !showMixers) || (mixerControl && showMixers))) {
        throw MlxRegException("Please provide either mixers offset configuration, "\
                "or show mixers option\n");
    }
    if (!errInjEnable && (showMixers || mixerControl)) {
        throw MlxRegException(PREI_RX_ERR_INJ_FLAG " flag should be specified!");
    }
    if (mixerControl) {
        if (_mlxlinkCommander->_userInput.mixerOffset0 > MAX_MIXER_OFFSET_0
                || _mlxlinkCommander->_userInput.mixerOffset1 > MAX_MIXER_OFFSET_1) {
            char errMsg[64];
            sprintf(errMsg,
                    "For mixer_offset0 [0 to 0x%x] and mixer_offset1 [0 to 0x%x]",
                    MAX_MIXER_OFFSET_0, MAX_MIXER_OFFSET_1);
            throw MlxRegException("Invalid mixer offset value, " + string(errMsg));
        }
    }
}

void MlxlinkUi::validatePortInfoParams()
{
    if (_mlxlinkCommander->_userInput.enableFecHistogram &&
        !_mlxlinkCommander->_userInput.showFecHistogram &&
        !_mlxlinkCommander->_userInput.clearFecHistogram) {
            throw MlxRegException("Please provide one of FEC Histogram options: "\
                    "--" PPHCR_SHOW_FEC_HIST_FLAG " or --" PPHCR_CLEAR_HISTOGRAM_FLAG);
    }
    if (!_mlxlinkCommander->_userInput.enableFecHistogram &&
        (_mlxlinkCommander->_userInput.showFecHistogram ||
        _mlxlinkCommander->_userInput.clearFecHistogram)) {
            throw MlxRegException(PPHCR_FEC_HIST_FLAG " flag should  be specified");
    }
    if (_mlxlinkCommander->_userInput.showFecHistogram &&
        _mlxlinkCommander->_userInput.clearFecHistogram) {
            throw MlxRegException("Options are mutually exclusive, please select one option only");
    }
}

void MlxlinkUi::paramValidate()
{
    validateMandatoryParams();
    validatePCIeParams();
    validateGeneralCmdsParams();
    validatePRBSParams();
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
    AddOptions(DEVICE_FLAG, DEVICE_FLAG_SHORT, "MstDevice",
               "Mellanox mst device name");
    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");
    AddOptions(PORT_TYPE_FLAG, PORT_TYPE_FLAG_SHORT, "port_type", "Port Type");
    AddOptions(DEPTH_FLAG, DEPTH_FLAG_SHORT, "depth", "depth");
    AddOptions(PCIE_INDEX_FLAG, PCIE_INDEX_FLAG_SHORT, "pcie_index", "PCIe Index");
    AddOptions(NODE_FLAG, NODE_FLAG_SHORT, "node", "node");
    AddOptions(LABEL_PORT_FLAG, LABEL_PORT_FLAG_SHORT, "LabelPort",
               "Label Port");
    AddOptions(PCIE_LINKS_FLAG, PCIE_LINKS_FLAG_SHORT, "", "Show valid PCIe links");
    AddOptions(BER_FLAG, BER_FLAG_SHORT, "", "Show BER Info");
    AddOptions(EYE_OPENING_FLAG, EYE_OPENING_FLAG_SHORT, "",
               "Show Eye Opening Info");
    AddOptions(MODULE_INFO_FLAG, MODULE_INFO_FLAG_SHORT, "",
               "Show Module Info");
    AddOptions(PPCNT_CLEAR_FLAG, PPCNT_CLEAR_FLAG_SHORT, "",
               "Clear PPCNT Counters");
    AddOptions(DEVICE_DATA_FLAG, DEVICE_DATA_FLAG_SHORT, "", "Device Info");
    AddOptions(BER_MONITOR_INFO_FLAG, BER_MONITOR_INFO_FLAG_SHORT, "", "Show BER Monitor Info");
    AddOptions(PEPC_SHOW_FLAG, PEPC_SHOW_FLAG_SHORT, "", "Show External PHY Info");
    AddOptions(PRINT_JSON_OUTPUT_FLAG, PRINT_JSON_OUTPUT_FLAG_SHORT, "", "Print the output in json format");

    AddOptions(FEC_DATA_FLAG, FEC_DATA_FLAG_SHORT, "", "FEC Data");
    AddOptions(PAOS_FLAG, PAOS_FLAG_SHORT, "PAOS", "Send PAOS");
    AddOptions(PTYS_FLAG, PTYS_FLAG_SHORT, "PTYS", "Send PTYS");
    AddOptions(PTYS_LINK_MODE_FORCE_FLAG, PTYS_LINK_MODE_FORCE_FLAG_SHORT, "", "Set Link Mode Force");
    AddOptions(PPLM_FLAG, PPLM_FLAG_SHORT, "PPLM", "Send PPLM");
    AddOptions(FEC_SPEED_FLAG, FEC_SPEED_FLAG_SHORT, "FECSPEED", "Send PPLM with Speed");
    AddOptions(PPLR_FLAG, PPLR_FLAG_SHORT, "PPLR", "Send PPLR");
    AddOptions(BER_COLLECT_FLAG, BER_COLLECT_FLAG_SHORT, "BERCollectFile",
               "BER Collection csv file");
    AddOptions(AMBER_COLLECT_FLAG, AMBER_COLLECT_FLAG_SHORT, "AMBERCollectFile",
               "AMBER Collection csv file");
    AddOptions(BER_LIMIT_FLAG, BER_LIMIT_FLAG_SHORT, "Mode",
               "Test Mode of Ber Collect (Nominal/Corner/Drift)");
    AddOptions(ITERATION_FLAG, ITERATION_FLAG_SHORT, "Iteration", "Iteration of BER Collect");
    AddOptions(PRBS_MODE_FLAG, PRBS_MODE_FLAG_SHORT, "PRBS",
               "Enable/Disable PRBS Test Mode");
    AddOptions(PPRT_PRBS_FLAG, PPRT_PRBS_FLAG_SHORT, "PPRT", "PPRT Mode");
    AddOptions(PPTT_PRBS_FLAG, PPTT_PRBS_FLAG_SHORT, "PPTT", "PPTT Mode");
    AddOptions(PPRT_RATE_FLAG, PPRT_RATE_FLAG_SHORT, "PPRT_RATE",
               "PPRT Lane Rate");
    AddOptions(PPTT_RATE_FLAG, PPTT_RATE_FLAG_SHORT, "PPTT_RATE",
               "PPTT Lane Rate");
    AddOptions(PRBS_LANES_FLAG, PRBS_LANES_FLAG_SHORT, "lanes",
               "PRBS lanes to set");
    AddOptions(PRBS_INVERT_TX_POL_FLAG, PRBS_INVERT_TX_POL_FLAG_SHORT, "",
               "PRBS TX polarity inversion");
    AddOptions(PRBS_INVERT_RX_POL_FLAG, PRBS_INVERT_RX_POL_FLAG_SHORT, "",
               "PRBS RX polarity inversion");

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
    AddOptions(CABLE_PRBS_GEN_RATE, CABLE_PRBS_GEN_RATE_SHORT, "rate", "");
    AddOptions(CABLE_PRBS_GEN_PAT, CABLE_PRBS_GEN_PAT_SHORT,"pattern", "");
    AddOptions(CABLE_PRBS_GEN_SWAP, CABLE_PRBS_GEN_SWAP_SHORT, "", "");
    AddOptions(CABLE_PRBS_GEN_INV, CABLE_PRBS_GEN_INV_SHORT, "rate", "");
    AddOptions(CABLE_PRBS_GEN_LANES, CABLE_PRBS_GEN_LANES_SHORT, "lanes", "");
    AddOptions(CABLE_PRBS_CH_RATE, CABLE_PRBS_CH_RATE_SHORT, "rate", "");
    AddOptions(CABLE_PRBS_CH_PAT, CABLE_PRBS_CH_PAT_SHORT, "pattern","");
    AddOptions(CABLE_PRBS_CH_SWAP, CABLE_PRBS_CH_SWAP_SHORT, "","");
    AddOptions(CABLE_PRBS_CH_INV, CABLE_PRBS_CH_INV_SHORT, "", "");
    AddOptions(CABLE_PRBS_CH_LANES, CABLE_PRBS_CH_LANES_SHORT, "lanes", "");
    AddOptions(CABLE_PRBS_SHOW_DIAG, CABLE_PRBS_SHOW_DIAG_SHORT, "", "");
    AddOptions(CABLE_PRBS_CLEAR_DIAG, CABLE_PRBS_CLEAR_DIAG_SHORT, "", "");

    AddOptions(SHOW_TX_GROUP_MAP_FLAG, SHOW_TX_GROUP_MAP_FLAG_SHORT, "group_num", "Display all label ports mapped to group <group_num>");
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
    AddOptions(EYE_MEASURE_TIME_FLAG, EYE_MEASURE_TIME_FLAG_SHORT, "time", "Max measure time in seconds for single eye diagram");
    AddOptions(LANE_INDEX_FLAG, LANE_INDEX_FLAG_SHORT, "lane", "Run eye for specific lane");
    AddOptions(EYE_SEL_FLAG, EYE_SEL_FLAG_SHORT, "eye_sel", "Run for specific eye");

    AddOptions(FORCE_YES_FLAG, FORCE_YES_FLAG_SHORT, "", "Non-interactive mode, answer yes to all questions");

    AddOptions(PREI_RX_ERR_INJ_FLAG, PREI_RX_ERR_INJ_FLAG_SHORT, "", "Get the RX link deterioration status");
    AddOptions(PREI_MIXER_OFFSET_0, PREI_MIXER_OFFSET_0_SHORT, "value", "Eye centering control");
    AddOptions(PREI_MIXER_OFFSET_1, PREI_MIXER_OFFSET_1_SHORT, "value", "Eye centering control");
    AddOptions(PREI_SHOW_MIXERS_FLAG, PREI_SHOW_MIXERS_FLAG_SHORT, "", "Show mixers offset values");

    AddOptions(PPHCR_FEC_HIST_FLAG, PPHCR_FEC_HIST_FLAG_SHORT, "", "Provide histogram of FEC errors");
    AddOptions(PPHCR_SHOW_FEC_HIST_FLAG, PPHCR_SHOW_FEC_HIST_FLAG_SHORT, "", "Show FEC errors histograms");
    AddOptions(PPHCR_CLEAR_HISTOGRAM_FLAG, PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT, "", "Clears FEC errors histograms");

    _cmdParser.AddRequester(this);
}

void MlxlinkUi::commandsCaller()
{
    for (vector<OPTION_TYPE>::iterator it = _sendRegFuncMap.begin();
         it != _sendRegFuncMap.end(); it++) {
        switch(*it) {
        case SHOW_PDDR:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Network Port Information\"");
            _mlxlinkCommander->showPddr();
           break;
        case SHOW_PCIE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"PCIE Port Information\"");
           _mlxlinkCommander->showPcie();
           break;
        case SHOW_MODULE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Module Info\"");
           _mlxlinkCommander->showModuleInfo();
           break;
        case SHOW_BER:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Physical Counters and BER Info\"");
            _mlxlinkCommander->showBer();
           break;
        case SHOW_EYE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Eye Opening Info\"");
           _mlxlinkCommander->showEye();
           break;
        case SHOW_FEC:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show FEC Capabilities\"");
           _mlxlinkCommander->showFEC();
           break;
        case SHOW_SLTP:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Transmitter Info\"");
           _mlxlinkCommander->showSltp();
           break;
        case SHOW_DEVICE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"General Device Info\"");
            _mlxlinkCommander->showDeviceData();
            break;
        case SHOW_BER_MONITOR:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Physical Counters and BER Info\"");
            _mlxlinkCommander->showBerMonitorInfo();
            break;
        case SHOW_EXTERNAL_PHY:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show External PHY Info\"");
            _mlxlinkCommander->showExternalPhy();
            break;
        case SHOW_PCIE_LINKS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Show Valid PCIe Links\"");
            _mlxlinkCommander->showPcieLinks();
            break;
        case SEND_BER_COLLECT:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Port Extended Information Collection\"");
            _mlxlinkCommander->collectBER();
            break;
        case SEND_AMBER_COLLECT:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"AmBER Collection\"");
            _mlxlinkCommander->collectAMBER();
            break;case SEND_PAOS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Configure Port State\"");
            _mlxlinkCommander->sendPaos();
            break;
        case SEND_PTYS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Configure Speeds\"");
            _mlxlinkCommander->sendPtys();
            break;
        case SEND_PPLM:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Configure FEC\"");
            _mlxlinkCommander->sendPplm();
            break;
        case SEND_PPLR:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Configure Loopback Mode\"");
            _mlxlinkCommander->sendPplr();
            break;
        case SEND_PRBS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Physical Test Mode Configuration\"");
            _mlxlinkCommander->handlePrbs();
            break;
        case SEND_SLTP:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Configure Transmitter Parameters\"");
            _mlxlinkCommander->sendSltp();
            break;
        case SEND_CLEAR_COUNTERS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger, "-> \"Clear Counters\"");
            _mlxlinkCommander->clearCounters();
            break;
        case SEND_PEPC:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Set External PHY\"");
            _mlxlinkCommander->sendPepc();
            break;
        case CABLE_SHOW_DUMP:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Dump cable pages\"");
            _mlxlinkCommander->showCableDump();
            break;
        case CABLE_SHOW_DDM:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Show DDM info\"");
            _mlxlinkCommander->showCableDDM();
            break;
        case CABLE_EEPROM_WRITE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Write to EEPROM\"");
            _mlxlinkCommander->writeCableEEPROM();
            break;
        case CABLE_EEPROM_READ:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Write to EEPROM\"");
             _mlxlinkCommander->readCableEEPROM();
            break;
        case SHOW_TX_GROUP_MAP:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Show TX Group Mapping\"");
            _mlxlinkCommander->showTxGroupMapping();
            break;
        case SET_TX_GROUP_MAP:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> \"Set TX Group Mapping\"");
            _mlxlinkCommander->setTxGroupMapping();
            break;
        case GRADE_SCAN_ENABLE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> EYE scan");
            _mlxlinkCommander->initEyeOpener();
            break;
        case ERR_INJ_ENABLE:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> Error injection");
            _mlxlinkCommander->initErrInj();
            break;
        case RS_FEC_HISTOGRAM:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> FEC histogram info");
            _mlxlinkCommander->initPortInfo();
            break;
        case CABLE_PRBS_CMDS:
            PRINT_LOG(_mlxlinkCommander->_mlxlinkLogger,"-> Cable PRBS Commands");
            _mlxlinkCommander->performModulePrbsCommands();
            break;
        default:
            break;
        }
    }
}

void MlxlinkUi::addCmd(OPTION_TYPE option)
{
    if (!isIn(option, _sendRegFuncMap)) {
        _sendRegFuncMap.push_back(option);
    }
}

ParseStatus MlxlinkUi::HandleOption(string name, string value)
{
    addCmd(SHOW_PDDR);
    if (name == PRINT_JSON_OUTPUT_FLAG) {
        MlxlinkRecord::jsonFormat = true;
        MlxlinkRecord::cOut = &cerr;
        MlxlinkRecord::stdOut = stderr;
        return PARSE_OK;
    } else if (name == HELP_FLAG) {
        printHelp();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
        print_version_string(MLXLINK_EXEC, NULL);
        return PARSE_OK_WITH_EXIT;
    } else if (name == DEVICE_FLAG) {
        _mlxlinkCommander->_device = value;
        return PARSE_OK;
    } else if (name == MODULE_INFO_FLAG) {
        addCmd(SHOW_MODULE);
        _mlxlinkCommander->_networkCmds++;
        return PARSE_OK;
    } else if (name == BER_FLAG) {
        addCmd(SHOW_BER);
        _mlxlinkCommander->_userInput._showCounters = true;
        return PARSE_OK;
    } else if (name == PPCNT_CLEAR_FLAG) {
        addCmd(SEND_CLEAR_COUNTERS);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == EYE_OPENING_FLAG) {
        addCmd(SHOW_EYE);
        _mlxlinkCommander->_userInput._showEyeInfo = true;
        return PARSE_OK;
    } else if (name == SLTP_SHOW_FLAG) {
        addCmd(SHOW_SLTP);
        _mlxlinkCommander->_userInput._showSltp = true;
        return PARSE_OK;
    } else if (name == SLTP_SET_FLAG) {
        string sltpParamsLine = toUpperCase(value);
        std::vector<string> sltpParams = _mlxlinkCommander->parseParamsFromLine(sltpParamsLine);
        _mlxlinkCommander->getSltpParamsFromVector(sltpParams);
        addCmd(SEND_SLTP);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == LANE_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._lane);
        _mlxlinkCommander->_userInput._sltpLane = true;
        return PARSE_OK;
    } else if (name == DATABASE_FLAG) {
        _mlxlinkCommander->_userInput._db = true;
        return PARSE_OK;
    } else if (name == SLTP_TX_POLICY_FLAG) {
        _mlxlinkCommander->_userInput._txPolicy = true;
        return PARSE_OK;
    } else if (name == GVMI_ADDRESS_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._gvmiAddress);
        return PARSE_OK;
    } else if (name == SLTP_SET_ADVANCED_FLAG) {
        _mlxlinkCommander->_userInput._advancedMode = true;
        return PARSE_OK;
    } else if (name == PORT_TYPE_FLAG) {
        _mlxlinkCommander->_userInput._portType = toUpperCase(value);
        return PARSE_OK;
    } else if (name == LABEL_PORT_FLAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->handlePortStr(value);
        return PARSE_OK;
    } else if (name == DEPTH_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._depth);
        _mlxlinkCommander->_userInput._sendDepth = true;
        return PARSE_OK;
    } else if (name == PCIE_INDEX_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._pcieIndex);
        _mlxlinkCommander->_userInput._sendPcieIndex = true;
        return PARSE_OK;
    } else if (name == NODE_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._node);
        _mlxlinkCommander->_userInput._sendNode = true;
        return PARSE_OK;
    } else if (name == PCIE_LINKS_FLAG) {
        addCmd(SHOW_PCIE_LINKS);
        _mlxlinkCommander->_userInput._links = true;
        return PARSE_OK;
    } else if (name == DEVICE_DATA_FLAG) {
        addCmd(SHOW_DEVICE);
        return PARSE_OK;
    } else if (name == FEC_DATA_FLAG) {
        addCmd(SHOW_FEC);
        _mlxlinkCommander->_networkCmds++;
        return PARSE_OK;
    } else if (name == PAOS_FLAG) {
        addCmd(SEND_PAOS);
        _mlxlinkCommander->_userInput._paosCmd = toUpperCase(value);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PTYS_FLAG) {
        addCmd(SEND_PTYS);
        _mlxlinkCommander->_ptysSpeeds = _mlxlinkCommander->parseParamsFromLine(toUpperCase(value));
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PPLM_FLAG) {
        addCmd(SEND_PPLM);
        _mlxlinkCommander->_userInput._pplmFec = toUpperCase(value);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == FEC_SPEED_FLAG) {
        _mlxlinkCommander->_userInput._speedFec = toLowerCase(value);
        return PARSE_OK;
    } else if (name == PPLR_FLAG) {
        addCmd(SEND_PPLR);
        _mlxlinkCommander->_userInput._pplrLB = toUpperCase(value);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PRBS_MODE_FLAG) {
        addCmd(SEND_PRBS);
        _mlxlinkCommander->_userInput._prbsMode = toUpperCase(value);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PPRT_PRBS_FLAG) {
        _mlxlinkCommander->_userInput._sendPprt = true;
        _mlxlinkCommander->_userInput._pprtMode = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PPTT_PRBS_FLAG) {
        _mlxlinkCommander->_userInput._sendPptt = true;
        _mlxlinkCommander->_userInput._ppttMode = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PPRT_RATE_FLAG) {
        _mlxlinkCommander->_userInput._pprtRate = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PPTT_RATE_FLAG) {
        _mlxlinkCommander->_userInput._ppttRate = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PRBS_LANES_FLAG) {
        std::vector<string> prbsLanesParams = _mlxlinkCommander->parseParamsFromLine(value);
        _mlxlinkCommander->getprbsLanesFromParams(prbsLanesParams);
        return PARSE_OK;
    } else if (name == PRBS_INVERT_TX_POL_FLAG){
        _mlxlinkCommander->_userInput._prbsTxInv = true;
        return PARSE_OK;
    } else if (name == PRBS_INVERT_RX_POL_FLAG){
        _mlxlinkCommander->_userInput._prbsRxInv = true;
        return PARSE_OK;
    } else if (name == BER_COLLECT_FLAG) {
        addCmd(SEND_BER_COLLECT);
        _mlxlinkCommander->_userInput._csvBer = value;
        return PARSE_OK;
    }  else if (name == AMBER_COLLECT_FLAG) {
        addCmd(SEND_AMBER_COLLECT);
        _mlxlinkCommander->_userInput._csvBer = value;
        return PARSE_OK;
    } else if (name == BER_LIMIT_FLAG) {
        _mlxlinkCommander->_userInput._testMode = toUpperCase(value);
        return PARSE_OK;
    } else if (name == ITERATION_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(), _mlxlinkCommander->_userInput._iteration);
        return PARSE_OK;
    } else if (name == BER_MONITOR_INFO_FLAG) {
        addCmd(SHOW_BER_MONITOR);
        return PARSE_OK;
    } else if (name == PEPC_SHOW_FLAG) {
        addCmd(SHOW_EXTERNAL_PHY);
        return PARSE_OK;
    } else if (name == PEPC_FORCE_MODE_FLAG) {
        _mlxlinkCommander->_userInput._sendPepcForceMode = true;
        _mlxlinkCommander->_userInput._forceMode = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PEPC_AN_MODE_FLAG) {
        _mlxlinkCommander->_userInput._sendPepcANMode = true;
        _mlxlinkCommander->_userInput._anMode = toUpperCase(value);
        return PARSE_OK;
    } else if (name == PEPC_SET_FLAG) {
        addCmd(SEND_PEPC);
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PTYS_LINK_MODE_FORCE_FLAG) {
        _mlxlinkCommander->_linkModeForce = true;
        return PARSE_OK;
    } else if (name == LOG_FLAG) {
        _mlxlinkCommander->_userInput._logFilePath = value;
        return PARSE_OK;
    } else if (name == CABLE_FLAG) {
        _mlxlinkCommander->_userInput._cable = true;
        return PARSE_OK;
    } else if (name == CABLE_DUMP_FLAG) {
        _mlxlinkCommander->_userInput._dump = true;
        addCmd(CABLE_SHOW_DUMP);
        _mlxlinkCommander->_uniqueCableCmds++;
        return PARSE_OK;
    } else if (name == CABLE_DDM_FLAG) {
        _mlxlinkCommander->_userInput._ddm = true;
        addCmd(CABLE_SHOW_DDM);
        _mlxlinkCommander->_uniqueCableCmds++;
        return PARSE_OK;
    } else if (name == CABLE_WRITE_FLAG) {
        _mlxlinkCommander->_userInput._write = true;
        _mlxlinkCommander->_userInput._bytesToWrite =
                _mlxlinkCommander->parseParamsFromLine(value);
        addCmd(CABLE_EEPROM_WRITE);
        _mlxlinkCommander->_uniqueCableCmds++;
        return PARSE_OK;
    } else if (name == WRITE_PAGE_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                (u_int32_t&)_mlxlinkCommander->_userInput._page);
        return PARSE_OK;
    } else if (name == WRITE_OFFSET_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                (u_int32_t&)_mlxlinkCommander->_userInput._offset);
        return PARSE_OK;
    } else if (name == CABLE_READ_FLAG) {
        _mlxlinkCommander->_userInput._read = true;
        _mlxlinkCommander->_uniqueCableCmds++;
        addCmd(CABLE_EEPROM_READ);
        return PARSE_OK;
    } else if (name == READ_LEN_FLAG) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                (u_int32_t&)_mlxlinkCommander->_userInput._len);
        return PARSE_OK;
    } else if (name == SHOW_TX_GROUP_MAP_FLAG) {
        addCmd(SHOW_TX_GROUP_MAP);
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                        (u_int32_t&)_mlxlinkCommander->_userInput._showGroup);
        return PARSE_OK;
    } else if (name == SET_TX_GROUP_MAP_FLAG) {
        addCmd(SET_TX_GROUP_MAP);
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                        (u_int32_t&)_mlxlinkCommander->_userInput._setGroup);
        return PARSE_OK;
    } else if (name == TX_GROUP_PORTS_FLAG) {
        _mlxlinkCommander->_userInput._labelPorts = _mlxlinkCommander->parseParamsFromLine(value);
        return PARSE_OK;
    } else if (name == MARGIN_SCAN_FLAG) {
        addCmd(GRADE_SCAN_ENABLE);
        return PARSE_OK;
    } else if (name == EYE_MEASURE_TIME_FLAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                        (u_int32_t&)_mlxlinkCommander->_userInput.measureTime);
        return PARSE_OK;
    } else if (name == FORCE_YES_FLAG) {
        _mlxlinkCommander->_userInput.force = true;
        return PARSE_OK;
    } else if (name == LANE_INDEX_FLAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                        (u_int32_t&)_mlxlinkCommander->_userInput._lane);
        _mlxlinkCommander->_userInput.gradeScanPerLane = true;
        return PARSE_OK;
    } else if (name == EYE_SEL_FLAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.eyeSelect = toUpperCase(value);
        _mlxlinkCommander->_userInput.eyeSelectSpecified = true;
        return PARSE_OK;
    } else if (name == PREI_RX_ERR_INJ_FLAG) {
        addCmd(ERR_INJ_ENABLE);
        _mlxlinkCommander->_userInput.enableRxErrInj = true;
        _mlxlinkCommander->_uniqueCmds++;
        return PARSE_OK;
    } else if (name == PREI_MIXER_OFFSET_0) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                                (u_int32_t&)_mlxlinkCommander->_userInput.mixerOffset0);
        return PARSE_OK;
    } else if (name == PREI_MIXER_OFFSET_1) {
        _mlxlinkCommander->strToUint32((char*) value.c_str(),
                                (u_int32_t&)_mlxlinkCommander->_userInput.mixerOffset1);
        return PARSE_OK;
    } else if (name == PREI_SHOW_MIXERS_FLAG) {
        _mlxlinkCommander->_userInput.showMixers = true;
        return PARSE_OK;
    } else if (name == PPHCR_FEC_HIST_FLAG) {
        addCmd(RS_FEC_HISTOGRAM);
        _mlxlinkCommander->_userInput.enableFecHistogram = true;
        return PARSE_OK;
    } else if (name == PPHCR_SHOW_FEC_HIST_FLAG) {
        _mlxlinkCommander->_userInput.showFecHistogram = true;
        return PARSE_OK;
    } else if (name == PPHCR_CLEAR_HISTOGRAM_FLAG) {
        _mlxlinkCommander->_userInput.clearFecHistogram = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_SELECT) {
        addCmd(CABLE_PRBS_CMDS);
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_SELECT] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsSelProvided = true;
        _mlxlinkCommander->_uniqueCableCmds++;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_MODE) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_MODE] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsModeProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_GEN_RATE) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_GEN_RATE] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_GEN_PAT) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_GEN_PAT] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_GEN_SWAP) {
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_GEN_SWAP] = "SWAP";
        _mlxlinkCommander->_userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_GEN_INV) {
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_GEN_INV] = "INV";
        _mlxlinkCommander->_userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_GEN_LANES) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_GEN_LANES] = value;
        _mlxlinkCommander->_userInput.isPrbsGenProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CH_RATE) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CH_RATE] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsChProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CH_PAT) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CH_PAT] = toUpperCase(value);
        _mlxlinkCommander->_userInput.isPrbsChProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CH_SWAP) {
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CH_SWAP] = "SWAP";
        _mlxlinkCommander->_userInput.isPrbsChProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CH_INV) {
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CH_INV] = "INV";
        _mlxlinkCommander->_userInput.isPrbsChProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CH_LANES) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CH_LANES] = value;
        _mlxlinkCommander->_userInput.isPrbsChProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_SHOW_DIAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_SHOW_DIAG] = value;
        _mlxlinkCommander->_userInput.isPrbsShowDiagProvided = true;
        return PARSE_OK;
    } else if (name == CABLE_PRBS_CLEAR_DIAG) {
        _mlxlinkCommander->checkStrLength(value);
        _mlxlinkCommander->_userInput.modulePrbsParams[MODULE_PRBS_CLEAR_DIAG] = value;
        _mlxlinkCommander->_userInput.isPrbsClearDiagProvided = true;
        return PARSE_OK;
    }
    return PARSE_ERROR;
}

int MlxlinkUi::run(int argc, char **argv)
{
    int exit_code = 0;
    createMlxlinkCommander();
    initCmdParser();
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT) {
        return exit_code;
    } else if ((rc == PARSE_ERROR) || (rc == PARSE_ERROR_SHOW_USAGE)) {
        throw MlxRegException(
                  "failed to parse arguments. "
                  + string(_cmdParser.GetErrDesc()));
    }
    paramValidate();
    _mlxlinkCommander->_mf = mopen(_mlxlinkCommander->_device.c_str());;
    if (!_mlxlinkCommander->_mf) {
        throw MlxRegException(
                  "Failed to open device: \"" + _mlxlinkCommander->_device + "\", "
                  + strerror(errno));
    }
    if (!MlxRegLib::isDeviceSupported(_mlxlinkCommander->_mf)) {
        throw MlxRegException("Device is not supported");
    }
    MlxRegLib::isAccessRegisterSupported(_mlxlinkCommander->_mf);
    _mlxlinkCommander->_regLib = new MlxRegLib(_mlxlinkCommander->_mf,
            _mlxlinkCommander->_extAdbFile, _mlxlinkCommander->_useExtAdb);
    if (_mlxlinkCommander->_regLib->isIBDevice() &&
            !_mlxlinkCommander->_regLib->isAccessRegisterGMPSupported(
                    MACCESS_REG_METHOD_GET)) {
        MlxlinkRecord::printWar("Warning: AccessRegisterGMP Get() method is not supported.\n"
                 "         mlxlink has limited functionality", _mlxlinkCommander->_jsonRoot);
    }

    _mlxlinkCommander->_gvmiAddress = _mlxlinkCommander->_userInput._gvmiAddress;
    _mlxlinkCommander->_devID = _mlxlinkCommander->_regLib->getDevId();
    _mlxlinkCommander->_isHCA = dm_dev_is_hca(_mlxlinkCommander->_devID);
    _mlxlinkCommander->labelToLocalPort();
    _mlxlinkCommander->validatePortType(_mlxlinkCommander->_userInput._portType);
    if (!_mlxlinkCommander->_userInput._pcie) {
        _mlxlinkCommander->checkValidFW();
    }
    _mlxlinkCommander->getProductTechnology();

    if (!_mlxlinkCommander->_userInput._pcie) {
        _mlxlinkCommander->_prbsTestMode = _mlxlinkCommander->inPrbsTestMode();
        _mlxlinkCommander->getCableParams();
    } else if (!_mlxlinkCommander->_userInput._sendDpn) {
        _mlxlinkCommander->initValidDPNList();
    }

    if (_mlxlinkCommander->_userInput._logFilePath != "") {
        _mlxlinkCommander->_mlxlinkLogger = new MlxlinkLogger(_mlxlinkCommander->_userInput._logFilePath);
    }
    commandsCaller();
    if (_mlxlinkCommander->_allUnhandledErrors != "") {
        exit_code = 1;
        if (!MlxlinkRecord::jsonFormat) {
            MlxlinkRecord::printErrorsSection(
                    _mlxlinkCommander->_mlxlinkMaps->_showErrorsTitle,
                    _mlxlinkCommander->_allUnhandledErrors);
        }
    }

    if (MlxlinkRecord::jsonFormat) {
        _mlxlinkCommander->prepareJsonOut();
        cout << _mlxlinkCommander->_jsonRoot.toStyledString();
    }

    cout << endl;
    return exit_code;
}
