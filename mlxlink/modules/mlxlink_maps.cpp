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

#include "mlxlink_maps.h"

MlxlinkMaps* MlxlinkMaps::instance = NULL;

MlxlinkMaps* MlxlinkMaps::getInstance()
{
    if (!instance) {
        instance = new MlxlinkMaps();
    }
    return instance;
}

MlxlinkMaps::MlxlinkMaps() {
    _berCollectTitle =
            "Test Mode (Nominal/Corner/Drift),Protocol,Speed [Gb/s],Active FEC,Iteration Number,Device PN,FW Version,Device ID,Port Number,Media,Cable PN,Length [m],Attenuation [dB],"
                    "Test time [Min],Raw Errors Lane 0,Raw Errors Lane 1,Raw Errors Lane 2,Raw Errors Lane 3,Link Down,Total Raw BER,Raw BER limit,"
                    "Effective Errors,Effective BER,Result,System Voltage,Chip Start Temp,Chip End Temp,Module Start Temp,Module End Temp,Active RTN,Device SN,Cable SN,RX End BW [Gb/s]";

    _pmFsmState[PHY_MNGR_DISABLED] = "Disable";
    _pmFsmState[PHY_MNGR_OPEN_PORT] = "Port PLL Down";
    _pmFsmState[PHY_MNGR_POLLING] = "Polling";
    _pmFsmState[PHY_MNGR_ACTIVE_LINKUP] = "Active";
    _pmFsmState[PHY_MNGR_CLOSE_PORT] = "Close port";
    _pmFsmState[PHY_MNGR_PHYSICAL_LINKUP] = "Physical LinkUp";

    _ethANFsmState[0x0] = "ETH_AN_FSM_ENABLE";
    _ethANFsmState[0x1] = "ETH_AN_FSM_XMIT_DISABLE";
    _ethANFsmState[0x2] = "ETH_AN_FSM_ABILITY_DETECT";
    _ethANFsmState[0x3] = "ETH_AN_FSM_ACK_DETECT";
    _ethANFsmState[0x4] = "ETH_AN_FSM_COMPLETE_ACK";
    _ethANFsmState[0x5] = "ETH_AN_FSM_AN_GOOD_CHECK";
    _ethANFsmState[0x6] = "LinkUp";
    _ethANFsmState[0x7] = "ETH_AN_FSM_NEXT_PAGE_WAIT";
    _ethANFsmState[0x8] = "ETH_AN_FSM_LINK_STAT_CHECK";
    _ethANFsmState[0x9] = "ETH_AN_FSM_EXTRA_TUNE";
    _ethANFsmState[0xa] = "ETH_AN_FSM_FIX_REVERSALS";
    _ethANFsmState[0xb] = "ETH_AN_FSM_IB_FAIL";
    _ethANFsmState[0xc] = "ETH_AN_FSM_POST_LOCK_TUNE";

    _ibPhyFsmState[IB_AN_FSM_DISABLED] = "Disabled";
    _ibPhyFsmState[IB_AN_FSM_INITIALY] = "Initializing";
    _ibPhyFsmState[IB_AN_FSM_RCVR_CFG] = "Recover Config";
    _ibPhyFsmState[IB_AN_FSM_CFG_TEST] = "Config Test";
    _ibPhyFsmState[IB_AN_FSM_WAIT_RMT_TEST] = "Wait Remote Test";
    _ibPhyFsmState[IB_AN_FSM_WAIT_CFG_ENHANCED] =
            "Wait Config Enhanced";
    _ibPhyFsmState[IB_AN_FSM_CFG_IDLE] = "Config Idle";
    _ibPhyFsmState[IB_AN_FSM_LINK_UP] = "LinkUp";

    _fecModeActive[FEC_MODE_NO_FEC] = "No FEC";
    _fecModeActive[FEC_MODE_FIRECODE_FEC] = "Firecode FEC";
    _fecModeActive[FEC_MODE_STANDARD_RS_FEC_528_514] =
            "Standard RS-FEC - RS(528,514)";
    _fecModeActive[FEC_MODE_STANDARD_LL_FEC_271_257] =
            "Standard LL RS-FEC - RS(271,257)";
    _fecModeActive[FEC_MODE_STANDARD_RS_FEC_544_514] =
            "Standard RS-FEC (544,514)";
    _fecModeActive[FEC_MODE_MELLANOX_STRONG_FEC] =
            "Mellanox Strong RS-FEC - RS(277,257)";
    _fecModeActive[FEC_MODE_MELLANOX_LL_FEC] =
            "Mellanox LL RS-FEC - RS(163,155)";
    _fecModeActive[FEC_MODE_ZERO_LATENCY_FEC] =
            "Zero Latency FEC";
    _fecModeActive[FEC_MODE_RS_FEC_544_514_PLR] =
            "RS-FEC (544,514) + PLR";
    _fecModeActive[FEC_MODE_RS_FEC_271_257_PLR] =
            "LL-FEC (271,257) + PLR";

    _loopbackModeList[PHY_NO_LOOPBACK] = "No Loopback";
    _loopbackModeList[PHY_REMOTE_LOOPBACK] = "PHY Remote Loopback";
    _loopbackModeList[PHY_LOCAL_LOOPBACK] = "PHY Local Loopback";
    _loopbackModeList[EXTERNAL_LOCAL_LOOPBACK] =
            "External Local Loopback";

    _anDisableList[AN_DISABLE_NORMAL] = "ON";
    _anDisableList[AN_DISABLE_FORCE] = "FORCE";

    _speedsListETH[0] = "100";
    _speedsListETH[1] = "1G";
    _speedsListETH[2] = "10G";
    _speedsListETH[3] = "20G";
    _speedsListETH[4] = "25G";
    _speedsListETH[5] = "40G";
    _speedsListETH[6] = "50G";
    _speedsListETH[7] = "56G";
    _speedsListETH[8] = "100G";
    _speedsListIB[9] = "SDR";
    _speedsListIB[0] = "DDR";
    _speedsListIB[1] = "QDR";
    _speedsListIB[2] = "FDR10";
    _speedsListIB[3] = "FDR";
    _speedsListIB[4] = "EDR";
    _speedsListIB[5] = "HDR";

    _prbsModesList[0] = "PRBS31";
    _prbsModesList[1] = "PRBS23A";
    _prbsModesList[2] = "PRBS23B";
    _prbsModesList[3] = "PRBS23C";
    _prbsModesList[4] = "PRBS23D";
    _prbsModesList[5] = "PRBS7";
    _prbsModesList[6] = "PRBS11";
    _prbsModesList[7] = "PRBS11A";
    _prbsModesList[8] = "PRBS11B";
    _prbsModesList[9] = "PRBS11C";
    _prbsModesList[10] = "PRBS11D";
    _prbsModesList[11] = "PRBS9";
    _prbsModesList[12] = "IDLE";
    _prbsModesList[13] = "SQUARE_WAVEA";
    _prbsModesList[14] = "SQUARE_WAVEB";
    _prbsModesList[15] = "SQUARE_WAVEC";
    _prbsModesList[16] = "SQUARE_WAVED";
    _prbsModesList[17] = "PRBS13A";
    _prbsModesList[18] = "PRBS13B";
    _prbsModesList[19] = "PRBS13C";
    _prbsModesList[20] = "PRBS13D";
    _prbsModesList[21] = "SSPR";
    _prbsModesList[22] = "SSPRQ";

    _prbsLaneRateList[0] = "SDR (2.5 Gb/s)";
    _prbsLaneRateList[1] = "DDR/5G (5 Gb/s)";
    _prbsLaneRateList[2] = "QDR (10 Gb/s)";
    _prbsLaneRateList[3] = "FDR10/10G/40G (10.3125 Gb/s)";
    _prbsLaneRateList[4] = "FDR/14G (14.0625 Gb/s)";
    _prbsLaneRateList[5] = "EDR/25G/50G/100G (25.78125 Gb/s)";
    _prbsLaneRateList[6] = "1G (1.25 Gb/s)";
    _prbsLaneRateList[7] = "XAUI/2.5G (3.125 Gb/s)";
    _prbsLaneRateList[8] = "50GE-KR4/12.89G (12.89 Gb/s)";
    _prbsLaneRateList[9] =
            "HDR/50GE/100GE/200GE/400GE (26.5625Gbd/53.125Gb/s)";

    _ppbmcBerMonitorState[0] = "No BER Monitor support";
    _ppbmcBerMonitorState[1] = "Normal";
    _ppbmcBerMonitorState[2] = "Warning";
    _ppbmcBerMonitorState[3] = "Alarm";

    _ppbmcBerMonitorType[0] = "Post FEC / No FEC BER monitoring";
    _ppbmcBerMonitorType[1] = "Pre FEC BER monitoring";

    _pepcStatus[0] = "Good";
    _pepcStatus[1] = "No support of the required configuration";
    _pepcStatus[2] = "Unknown External PHY";
    _pepcStatus[15] = "No External PHY";

    _pepcTwistedPairAn[0] =
            "Normal operation - AN is determine by MDI";
    _pepcTwistedPairAn[1] = "Disable AN";

    _pepcTwistedPairForceMode[0] = "Master mode";
    _pepcTwistedPairForceMode[1] = "Slave mode";

    _pepcTwistedPairAnMode[0] =
            "auto Master/Slave mode for AN links";
    _pepcTwistedPairAnMode[1] = "Master mode";
    _pepcTwistedPairAnMode[2] = "Slave mode";

    _pddrLinkDownBlame[0] = "Unknown";
    _pddrLinkDownBlame[1] = "Local phy";
    _pddrLinkDownBlame[2] = "Remote phy";

    _pddrLinkDownE2EReasonOpcode[0] = "No link down indication";
    _pddrLinkDownE2EReasonOpcode[1] = "Unknown reason";
    _pddrLinkDownE2EReasonOpcode[2] = "Hi_SER / Hi_BER";
    _pddrLinkDownE2EReasonOpcode[3] = "Block_Lock loss";
    _pddrLinkDownE2EReasonOpcode[4] = "Alignment loss";
    _pddrLinkDownE2EReasonOpcode[5] = "FEC sync loss";
    _pddrLinkDownE2EReasonOpcode[6] = "PLL lock loss";
    _pddrLinkDownE2EReasonOpcode[7] = "FIFO overflow";
    _pddrLinkDownE2EReasonOpcode[8] = "false SKIP condition";
    _pddrLinkDownE2EReasonOpcode[9] =
            "Minor Error threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[10] =
            "Physical layer retransmission timeout";
    _pddrLinkDownE2EReasonOpcode[11] = "Heartbeat errors";
    _pddrLinkDownE2EReasonOpcode[12] =
            "Link Layer credit monitoring watchdog";
    _pddrLinkDownE2EReasonOpcode[13] =
            "Link Layer integrity threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[14] = "Link Layer buffer overrun";
    _pddrLinkDownE2EReasonOpcode[15] =
            "Down by outband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[16] =
            "Down by outband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[17] =
            "Down by inband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[18] =
            "Down by inband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[19] = "Down by verification GW";
    _pddrLinkDownE2EReasonOpcode[20] = "Received Remote Fault";
    _pddrLinkDownE2EReasonOpcode[21] = "Received TS1";
    _pddrLinkDownE2EReasonOpcode[22] =
            "Down by management command";
    _pddrLinkDownE2EReasonOpcode[23] = "Cable was unplugged";
    _pddrLinkDownE2EReasonOpcode[24] = "Cable access issue";
    _pddrLinkDownE2EReasonOpcode[25] = "Thermal shutdown";
    _pddrLinkDownE2EReasonOpcode[26] = "Current issue";
    _pddrLinkDownE2EReasonOpcode[27] = "Power budget";
    _pddrLinkDownE2EReasonOpcode[28] = "MNG forced down the port";
    _pddrLinkDownE2EReasonOpcode[100] =
            "Peer - No link down indication";
    _pddrLinkDownE2EReasonOpcode[101] = "Peer - Unknown reason";
    _pddrLinkDownE2EReasonOpcode[102] = "Peer - Hi_SER / Hi_BER";
    _pddrLinkDownE2EReasonOpcode[103] = "Peer - Block_Lock loss";
    _pddrLinkDownE2EReasonOpcode[104] = "Peer - Alignment loss";
    _pddrLinkDownE2EReasonOpcode[105] = "Peer - FEC sync loss";
    _pddrLinkDownE2EReasonOpcode[106] = "Peer - PLL lock loss";
    _pddrLinkDownE2EReasonOpcode[107] = "Peer - FIFO overflow";
    _pddrLinkDownE2EReasonOpcode[108] =
            "Peer - false SKIP condition";
    _pddrLinkDownE2EReasonOpcode[109] =
            "Peer - Minor Error threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[110] =
            "Peer - Physical layer retransmission timeout";
    _pddrLinkDownE2EReasonOpcode[111] = "Peer - Heartbeat errors";
    _pddrLinkDownE2EReasonOpcode[112] =
            "Peer - Link Layer credit monitoring watchdog";
    _pddrLinkDownE2EReasonOpcode[113] =
            "Peer - Link Layer integrity threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[114] =
            "Peer - Link Layer buffer overrun";
    _pddrLinkDownE2EReasonOpcode[115] =
            "Peer - Down by outband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[116] =
            "Peer - Down by outband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[117] =
            "Peer - Down by inband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[118] =
            "Peer - Down by inband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[119] =
            "Peer - Down by verification GW";
    _pddrLinkDownE2EReasonOpcode[120] =
            "Peer - Received Remote Fault";
    _pddrLinkDownE2EReasonOpcode[121] = "Peer - Received TS1";
    _pddrLinkDownE2EReasonOpcode[122] =
            "Peer - Down by management command";
    _pddrLinkDownE2EReasonOpcode[123] =
            "Peer - Cable was unplugged";
    _pddrLinkDownE2EReasonOpcode[124] =
            "Peer - Cable access issue";
    _pddrLinkDownE2EReasonOpcode[125] = "Peer - Thermal shutdown";
    _pddrLinkDownE2EReasonOpcode[126] = "Peer - Current issue";
    _pddrLinkDownE2EReasonOpcode[127] = "Peer - Power budget";
    _pddrLinkDownE2EReasonOpcode[128] =
            "Peer - MNG forced down the port";

    _ETHSpeed2gNum[ETH_LINK_SPEED_10G_KR] = 10;
    _ETHSpeed2gNum[ETH_LINK_SPEED_10G_CR] = 10;
    _ETHSpeed2gNum[ETH_LINK_SPEED_10G_SR] = 10;
    _ETHSpeed2gNum[ETH_LINK_SPEED_10G_LR] = 10;
    _ETHSpeed2gNum[ETH_LINK_SPEED_20G_KR2] = 20;
    _ETHSpeed2gNum[ETH_LINK_SPEED_25G_CR] = 25;
    _ETHSpeed2gNum[ETH_LINK_SPEED_25G_KR] = 25;
    _ETHSpeed2gNum[ETH_LINK_SPEED_25G_SR] = 25;
    _ETHSpeed2gNum[ETH_LINK_SPEED_40G_CR4] = 40;
    _ETHSpeed2gNum[ETH_LINK_SPEED_40G_KR4] = 40;
    _ETHSpeed2gNum[ETH_LINK_SPEED_40G_LR4] = 40;
    _ETHSpeed2gNum[ETH_LINK_SPEED_40G_SR4] = 40;
    _ETHSpeed2gNum[ETH_LINK_SPEED_50G_CR2] = 50;
    _ETHSpeed2gNum[ETH_LINK_SPEED_50G_KR2] = 50;
    _ETHSpeed2gNum[ETH_LINK_SPEED_50G_SR2] = 50;
    _ETHSpeed2gNum[ETH_LINK_SPEED_50G_KR4] = 50;
    _ETHSpeed2gNum[ETH_LINK_SPEED_56G_R4] = 56;
    _ETHSpeed2gNum[ETH_LINK_SPEED_100G_CR4] = 100;
    _ETHSpeed2gNum[ETH_LINK_SPEED_100G_KR4] = 100;
    _ETHSpeed2gNum[ETH_LINK_SPEED_100G_LR4] = 100;
    _ETHSpeed2gNum[ETH_LINK_SPEED_100G_SR4] = 100;

    _IBSpeed2gNum[IB_LINK_SPEED_SDR] = 10;
    _IBSpeed2gNum[IB_LINK_SPEED_DDR] = 20;
    _IBSpeed2gNum[IB_LINK_SPEED_QDR] = 40;
    _IBSpeed2gNum[IB_LINK_SPEED_FDR10] = 40;
    _IBSpeed2gNum[IB_LINK_SPEED_FDR] = 56;
    _IBSpeed2gNum[IB_LINK_SPEED_EDR] = 100;
    _IBSpeed2gNum[IB_LINK_SPEED_HDR] = 200;

    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_1000BASE_X] = 1;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_5GBASE_R] = 5;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_XFI] = 10;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_XLAUI_4] = 40;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_25GAUI_1] = 25;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_50GAUI_2] = 50;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_50GAUI_1] = 50;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_CAUI_4] = 100;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_100GAUI_2] = 100;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_200GAUI_4] = 200;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_400GAUI_8] = 400;

    _ETHSpeed2Str[ETH_LINK_SPEED_100_BaseTx] = "BaseTx100M";
    _ETHSpeed2Str[ETH_LINK_SPEED_1000_BaseT] = "BaseT1000M";
    _ETHSpeed2Str[ETH_LINK_SPEED_1000_SGMII] = "CX";
    _ETHSpeed2Str[ETH_LINK_SPEED_1000_KX] = "KX";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_CX4] = "CX4";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_KX4] = "KX4";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_BaseT] = "BaseT10G";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_KR] = "10GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_CR] = "10GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_SR] = "10GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_10G_LR] = "10GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_20G_KR2] = "20GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_25G_CR] = "25GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_25G_KR] = "25GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_25G_SR] = "25GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_40G_CR4] = "40GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_40G_KR4] = "40GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_40G_LR4] = "40GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_40G_SR4] = "40GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_50G_CR2] = "50GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_50G_KR2] = "50GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_50G_SR2] = "50GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_50G_KR4] = "50GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_56G_R4] = "56GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_100G_CR4] = "100GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_100G_KR4] = "100GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_100G_LR4] = "100GbE";
    _ETHSpeed2Str[ETH_LINK_SPEED_100G_SR4] = "100GbE";

    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_SGMII_100M] = "100M";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_1000BASE_X] = "1G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_2_5GBASE_X] = "2.5G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_5GBASE_R] = "5G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_XFI] = "10G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_XLAUI_4] = "40G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_25GAUI_1] = "25G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_50GAUI_2] = "50G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_50GAUI_1] = "50G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_CAUI_4] = "100G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_100GAUI_2] = "100G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_200GAUI_4] = "200G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_400GAUI_8] = "400G";

    _IBSpeed2Str[IB_LINK_SPEED_SDR] = "IB-SDR";
    _IBSpeed2Str[IB_LINK_SPEED_DDR] = "IB-DDR";
    _IBSpeed2Str[IB_LINK_SPEED_QDR] = "IB-QDR";
    _IBSpeed2Str[IB_LINK_SPEED_FDR10] = "IB-FDR10";
    _IBSpeed2Str[IB_LINK_SPEED_FDR] = "IB-FDR";
    _IBSpeed2Str[IB_LINK_SPEED_EDR] = "IB-EDR";
    _IBSpeed2Str[IB_LINK_SPEED_HDR] = "IB-HDR";

    _ETHSpeed2Lanes[ETH_LINK_SPEED_100_BaseTx] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_BaseT] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_SGMII] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_KX] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_CX4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_KX4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_BaseT] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_KR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_CR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_SR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10G_LR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_20G_KR2] = 2;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_25G_CR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_25G_KR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_25G_SR] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_40G_CR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_40G_KR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_40G_LR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_40G_SR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_50G_CR2] = 2;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_50G_KR2] = 2;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_50G_SR2] = 2;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_50G_KR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_56G_R4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_100G_CR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_100G_KR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_100G_LR4] = 4;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_100G_SR4] = 4;

    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_SGMII_100M] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_1000BASE_X] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_2_5GBASE_X] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_5GBASE_R] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_XFI] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_XLAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_25GAUI_1] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_50GAUI_2] = 2;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_50GAUI_1] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_CAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_100GAUI_2] = 2;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_200GAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_400GAUI_8] = 8;

    _SLTP16BadSetStatus2Str[SET_STATUS16_INVALID_PARM] =
            "Invalid parameter";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_M2LP] =
            "Illegal ob_m2lp";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_AMP] =
            "Illegal ob_amp";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_ALEV_OUT] =
            "Illegal ob_alev_out";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_TAPS] =
            "Illegal taps";
    _SLTP16BadSetStatus2Str[SET_STATUS16_UNKNOWN] =
            "Unknown failure status";

    _SLTPBadSetStatus2Str[SET_STATUS16_INVALID_PARM] =
            "Invalid parameter";
    _SLTPBadSetStatus2Str[SET_STATUS_ILLEGAL_OB_BAIS] =
            "Illegal ob_bais value";
    _SLTPBadSetStatus2Str[SET_STATUS_ILLEGAL_OB_TAPS_POLARITY] =
            "Illegal ob_taps polarity (distance between taps)";
    _SLTPBadSetStatus2Str[SET_STATUS_UNKNOWN] =
            "Unknown failure status";

    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_Unspecified] =
            "Unspecified";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40G_ACTIVE_CABLE_XLPPI] =
            "40G Active Cable (XLPPI)";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_LR4] =
            "40GBASE-LR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_SR4] =
            "40GBASE-SR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_CR4] =
            "40GBASE-CR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_SR] =
            "10GBASE-SR";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LR] =
            "10GBASE-LR";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LRM] =
            "10GBASE-LRM";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_EXT] =
            "Extended Specification Compliance valid";

    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_Unspecified] =
            "Unspecified";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_SR] =
            "10G Base-SR";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LR] =
            "10G Base-LR";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LRM] =
            "10G Base-LRM";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_ER] =
            "10G Base-ER";

    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_Unspecified] =
            "Unspecified";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC_FEC] =
            "100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR4] =
            "100GBASE-SR4 or 25GBASE-SR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_LR4] =
            "100GBASE-LR4 or 25GBASE-LR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_ER4] =
            "100GBASE-ER4 or 25GBASE-ER";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR10] =
            "100GBASE-SR10";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_CWDM4] =
            "100G CWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_PSM4] =
            "100G PSM4 Parallel SMF";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC_FEC] =
            "100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_CR4] =
            "100GBASE-CR4 or 25GBASE-CR CA-L";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_S] =
            "25GBASE-CR CA-S";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_N] =
            "25GBASE-CR CA-N";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_40GBASE_ER4] =
            "40GBASE-ER4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_4_x_10GBASE_SR] =
            "4 x 10GBASE-SR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_40G_PSM4] =
            "40G PSM4 Parallel SMF";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1I1_2D1] =
            "G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1S1_2D2] =
            "G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1L1_2D2] =
            "G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_10GBASE_T] =
            "10GBASE-T with SFI electrical interface";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_CLR4] =
            "100G CLR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC] =
            "100G AOC or 25GAUI C2M AOC. No FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC] =
            "100G ACC or 25GAUI C2M ACC. No FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_DWDM2] =
            "100GE-DWDM2 (DWDM transceiver using 2 wavelengths on a 1550 nm"
                    " DWDM grid with a reach up to 80 km)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_1550NM_WDM] =
            "100G 1550nm WDM (4 wavelengths)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_10GBASE_T] =
            "10GBASE-T Short Reach (30 meters)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_5GBASE_T] =
            "5GBASE-T";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_2_5GBASE_T] =
            "2.5GBASE-T";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_40G_SWDM4] =
            "40G SWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_SWDM4] =
            "100G SWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_PAM4] =
            "100G PAM4 BiDi";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM10_MSA] =
            "4WDM-10 MSA (10km version of 100G CWDM4 with same RS(528,514) "
                    "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM20_MSA] =
            "4WDM-10 MSA (20km version of 100G CWDM4 with same RS(528,514) "
                    "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM40_MSA] =
            "4WDM-10 MSA (40km version of 100G CWDM4 with same RS(528,514) "
                    "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_DR] =
            "100GBASE-DR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_FR] =
            "100G-FR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_LR] =
            "100G-LR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_6] =
            "Active Copper Cable with 50GAUI, 100GAUI-2 or 200GAUI-4 C2M. "
                    "Providing a worst BER of 10^(-6) or below";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_6] =
            "Active Optical Cable with 50GAUI, 100GAUI-2 or 200GAUI-4 C2M. "
                    "Providing a worst BER of 10^(-6) or below";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_4] =
            "Active Copper Cable with 50GAUI, 100GAUI-2 or 200GAUI-4 C2M. "
                    "Providing a worst BER of 2.6x10^(-4) for ACC, 10^(-5) for AUI, "
                    "or below";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_4] =
            "Active Optical Cable with 50GAUI, 100GAUI-2 or 200GAUI-4 C2M. "
                    "Providing a worst BER of 2.6x10^(-4) for AOC, 10^(-5) for AUI, "
                    "or below";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_CR] =
            "50GBASE-CR, 100GBASE-CR2, or 200GBASE-CR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_SR] =
            "50GBASE-SR, 100GBASE-SR2, or 200GBASE-SR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_FR] =
            "50GBASE-FR or 200GBASE-DR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_FR4] =
            "200GBASE-FR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_1550NM_PSM4] =
            "200G 1550 nm PSM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_LR] =
            "50GBASE-LR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_LR4] =
            "200GBASE-LR4";

    _cableTechnologyQsfp[0] = "850 nm VCSEL";
    _cableTechnologyQsfp[1] = "1310 nm VCSEL";
    _cableTechnologyQsfp[2] = "1550 nm VCSEL";
    _cableTechnologyQsfp[3] = "1310 nm FP";
    _cableTechnologyQsfp[4] = "1310 nm DFB";
    _cableTechnologyQsfp[5] = "1550 nm DFB";
    _cableTechnologyQsfp[6] = "1310 nm EML";
    _cableTechnologyQsfp[7] = "1550 nm EML";
    _cableTechnologyQsfp[8] = "Other / Undefined";
    _cableTechnologyQsfp[9] = "1490 nm DFB";
    _cableTechnologyQsfp[10] = "Copper cable unequalized";
    _cableTechnologyQsfp[11] = "Copper cable passive equalized";
    _cableTechnologyQsfp[12] =
            "Copper cable, near and far end limiting active equalizers";
    _cableTechnologyQsfp[13] =
            "Copper cable, far end limiting active equalizers";
    _cableTechnologyQsfp[14] =
            "Copper cable, near end limiting active equalizers";
    _cableTechnologyQsfp[15] =
            "Copper cable, linear active equalizers";

    _cableTechnologySfp[0] = "N/A";
    _cableTechnologySfp[4] = "Passive";
    _cableTechnologySfp[8] = "Active";

    _sltpHeader = "";
    _showErrorsTitle = "Errors";
}

MlxlinkMaps::~MlxlinkMaps() {
}
