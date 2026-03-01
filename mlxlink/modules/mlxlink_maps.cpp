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

#include "mlxlink_maps.h"

MlxlinkMaps* MlxlinkMaps::instance = NULL;

MlxlinkMaps* MlxlinkMaps::getInstance()
{
    if (!instance)
    {
        instance = new MlxlinkMaps();
    }
    return instance;
}

void MlxlinkMaps::initPublicStrings()
{
    _showErrorsTitle = "Errors";
}

void MlxlinkMaps::initPortStateMapping()
{
    _pmFsmState[PHY_MNGR_DISABLED] = "Disable";
    _pmFsmState[PHY_MNGR_OPEN_PORT] = "Port PLL Down";
    _pmFsmState[PHY_MNGR_POLLING] = "Polling";
    _pmFsmState[PHY_MNGR_ACTIVE_LINKUP] = "Active";
    _pmFsmState[PHY_MNGR_CLOSE_PORT] = "Close port";
    _pmFsmState[PHY_MNGR_PHYSICAL_LINKUP] = "Physical LinkUp";
    _pmFsmState[PHY_MNGR_SLEEP] = "Sleep";
    _pmFsmState[PHY_MNGR_RX_DISABLE] = "Rx disable";
    _pmFsmState[PHY_MNGR_SIGNAL_DETECT] = "Signal detect";
    _pmFsmState[PHY_MNGR_RECEIVER_DETECT] = "Receiver detect";
    _pmFsmState[PHY_MNGR_SYNC_PEER] = "Sync peer";
    _pmFsmState[PHY_MNGR_NEGOTIATION] = "Negotiation";
    _pmFsmState[PHY_MNGR_TRAINING] = "Training";
    _pmFsmState[PHY_MNGR_SUB_FSM_ACTIVE] = "SubFSM active";

    _phyMgrStateForTableDisplay[PHY_MNGR_DISABLED] = "DIS";
    _phyMgrStateForTableDisplay[PHY_MNGR_OPEN_PORT] = "OPEN";
    _phyMgrStateForTableDisplay[PHY_MNGR_POLLING] = "POL";
    _phyMgrStateForTableDisplay[PHY_MNGR_ACTIVE_LINKUP] = "ACT";
    _phyMgrStateForTableDisplay[PHY_MNGR_CLOSE_PORT] = "CLOSE";
    _phyMgrStateForTableDisplay[PHY_MNGR_PHYSICAL_LINKUP] = "PHY_UP";
    _phyMgrStateForTableDisplay[PHY_MNGR_SLEEP] = "SLEEP";
    _phyMgrStateForTableDisplay[PHY_MNGR_RX_DISABLE] = "RX_DISABLE";
    _phyMgrStateForTableDisplay[PHY_MNGR_SIGNAL_DETECT] = "SIGNAL_DETECT";
    _phyMgrStateForTableDisplay[PHY_MNGR_RECEIVER_DETECT] = "RECEIVER_DETECT";
    _phyMgrStateForTableDisplay[PHY_MNGR_SYNC_PEER] = "SYNC_PEER";
    _phyMgrStateForTableDisplay[PHY_MNGR_NEGOTIATION] = "NEGOTIATION";
    _phyMgrStateForTableDisplay[PHY_MNGR_TRAINING] = "TRAINING";
    _phyMgrStateForTableDisplay[PHY_MNGR_SUB_FSM_ACTIVE] = "SUBFSM_ACTIVE";

    _networkProtocols[IB] = "InfiniBand";
    _networkProtocols[ETH] = "Ethernet";
    _networkProtocols[NVLINK] = "NVLink";

    _proFileFecInUse[PRO_FILE_FEC_IN_USE_IB_SPEC] = "IB spec / legacy";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_INTERNAL_PORTS] = "Internal ports (Backplane)";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_PASSIVE_COPPER_SHORT] = "Passive copper - Short";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_PASSIVE_COPPER_MEDIUM] = "Passive copper - Medium";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_PASSIVE_COPPER_LONG] = "Passive copper - Long";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_ACTIVE_OPTICS] = "Active optics / copper short reach (<20m)";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_OPTICS_LONG_REACH] = "Optics long reach (>20m)";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_NO_FEC] = "NO-FEC";
    _proFileFecInUse[PRO_FILE_FEC_IN_USE_FEC_ON] = "FEC-ON";

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

    _ibPhyFsmState[IB_AN_FSM_DISABLED] = "N/A";
    _ibPhyFsmState[IB_AN_FSM_INITIALY] = "Initializing";
    _ibPhyFsmState[IB_AN_FSM_RCVR_CFG] = "Recover Config";
    _ibPhyFsmState[IB_AN_FSM_CFG_TEST] = "Config Test";
    _ibPhyFsmState[IB_AN_FSM_WAIT_RMT_TEST] = "Wait Remote Test";
    _ibPhyFsmState[IB_AN_FSM_WAIT_CFG_ENHANCED] = "Wait Config Enhanced";
    _ibPhyFsmState[IB_AN_FSM_CFG_IDLE] = "Config Idle";
    _ibPhyFsmState[IB_AN_FSM_LINK_UP] = "LinkUp";

    _anDisableList[AN_DISABLE_NORMAL] = "ON";
    _anDisableList[AN_DISABLE_FORCE] = "FORCE";

    _slrgFomMode[SLRG_FOM_MODE_EYEC] = "SLRG_FOM_MODE_EYEC";
    _slrgFomMode[SLRG_FOM_MODE_EYEO] = "SLRG_FOM_MODE_EYEO";
    _slrgFomMode[SLRG_FOM_MODE_EYEM] = "SLRG_FOM_MODE_EYEM";
    _slrgFomMode[SLRG_FOM_MODE_BER] = "SLRG_FOM_MODE_BER";
    _slrgFomMode[SLRG_FOM_MODE_EYEC_VN] = "SLRG_FOM_MODE_EYEC_VN";
    _slrgFomMode[SLRG_FOM_MODE_EYEC_VP] = "SLRG_FOM_MODE_EYEC_VP";
    _slrgFomMode[SLRG_FOM_MODE_EYEM_VN] = "SLRG_FOM_MODE_EYEM_VN";
    _slrgFomMode[SLRG_FOM_MODE_EYEM_VP] = "SLRG_FOM_MODE_EYEM_VP";

    _slrgFomMode5nm[SLRG_FOM_MODE_EYE_OPEN] = "SLRG_FOM_MODE_EYE_OPEN";
    _slrgFomMode5nm[SLRG_FOM_MODE_EYEO_SNR] = "SLRG_FOM_MODE_EYEO_SNR";
    _slrgFomMode5nm[SLRG_FOM_MODE_NORM_SNR] = "SLRG_FOM_MODE_NORM_SNR";
    _slrgFomMode5nm[SLRG_FOM_MODE_EYE_LVLN] = "SLRG_FOM_MODE_EYE_LVLN";
    _slrgFomMode5nm[SLRG_FOM_MODE_EYE_LVLP] = "SLRG_FOM_MODE_EYE_LVLP";
    _slrgFomMode5nm[SLRG_FOM_MODE_THRES_NERR] = "SLRG_FOM_MODE_THRES_NERR";
    _slrgFomMode5nm[SLRG_FOM_MODE_CDR_NERR] = "SLRG_FOM_MODE_CDR_NERR";
    _slrgFomMode5nm[SLRG_FOM_MODE_CSDET_NERR] = "SLRG_FOM_MODE_CSDET_NERR";
    _slrgFomMode5nm[SLRG_FOM_MODE_MLSE_NERR] = "SLRG_FOM_MODE_MLSE_NERR";
    _slrgFomMode5nm[SLRG_FOM_MODE_SFEC_NERR] = "SLRG_FOM_MODE_SFEC_NERR";

    _networkPorts["NETWORK"] = NETWORK_PORT_TYPE;
    _networkPorts["PCIE"] = NETWORK_PORT_TYPE_LAST;
    _networkPorts["GEARBOX_HOST"] = NETWORK_PORT_TYPE_NEAR;
    _networkPorts["INTERNAL_IC_LR"] = NETWORK_PORT_TYPE_IC_LR;
    _networkPorts["GEARBOX_LINE"] = NETWORK_PORT_TYPE_FAR;

    _pcieDevStatus[PCIE_DEVICE_STATUS_CORRECTABLE_ERROR] = "Correctable Error detected";
    _pcieDevStatus[PCIE_DEVICE_STATUS_NON_FATAL_ERROR] = "Non-Fatal Error detected";
    _pcieDevStatus[PCIE_DEVICE_STATUS_FATAL_ERROR] = "Fatal Error detected";
    _pcieDevStatus[PCIE_DEVICE_STATUS_UNSUP_REQ] = "Unsupported Request detected";
    _pcieDevStatus[PCIE_DEVICE_STATUS_AUX] = "AUX power";
    _pcieDevStatus[PCIE_DEVICE_STATUS_TRANSACTION_PEN] = "Transaction Pending";
}

void MlxlinkMaps::phyHstFsmHdrStateMapping()
{
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_DISABLED] = "DISABLED";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_ADAPTATION] = "ADAPTATION";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_DESKEW_FIX_REVERSALS] = "DESKEW_FIX_REVERSALS";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_WAIT_TS2] = "WAIT_TS2";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_WAIT_MCB] = "WAIT_MCB";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_MCB_AN] = "MCB_AN";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_RECEIVER_READY] = "RECEIVER_READY";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_LINKUP] = "LINKUP";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_SUBFSM_FAIL] = "SUBFSM_FAIL";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_BASIC_DETECT] = "BASIC_DETECT";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_BASIC_STABILITY] = "BASIC_STABILITY";
    _phyHstFsmHdrState[PHY_HST_FSM_HDR_CONFIG] = "CONFIG";
    _phyHstFsmHdrState[PHY_HST_HDR_ERROR] = "ERROR";
}

void MlxlinkMaps::initFecAndLoopbackMapping()
{
    _fecModeActive[FEC_MODE_NO_FEC] = "No FEC";
    _fecModeActive[FEC_MODE_FIRECODE_FEC] = "Firecode FEC";
    _fecModeActive[FEC_MODE_STANDARD_RS_FEC_528_514] = "Standard RS-FEC - RS(528,514)";
    _fecModeActive[FEC_MODE_STANDARD_LL_FEC_271_257] = "Standard LL RS-FEC - RS(271,257)";
    _fecModeActive[FEC_MODE_INTERLEAVED_QUAD_RS_FEC_544_514] = "Interleaved Quad RS-FEC - (544,514)";
    _fecModeActive[FEC_MODE_INTERLEAVED_STANDARD_RS_FEC_544_514] = "Interleaved_Standard_RS-FEC - (544,514)";
    _fecModeActive[FEC_MODE_STANDARD_RS_FEC_544_514] = "Standard_RS-FEC - (544,514)";
    _fecModeActive[FEC_MODE_ZERO_LATENCY_FEC] = "Zero_Latency_FEC";
    _fecModeActive[FEC_MODE_RS_FEC_272_257] = "Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)";
    _fecModeActive[FEC_MODE_INTERLEAVED_RS_FEC_272_257] = "Interleaved_Ethernet_Consortium_LL_50G_RS_FEC -(272,257+1)";
    _fecModeActive[FEC_MODE_INTERLEAVED_RS_FEC_544_514_PLR] = "Interleaved_Standard_RS_FEC_PLR - (544,514)";
    _fecModeActive[FEC_MODE_RS_FEC_544_514_PLR] = "RS-FEC - (544,514) + PLR";
    _fecModeActive[FEC_MODE_RS_FEC_271_257_PLR] = "LL-FEC - (271,257) + PLR";
    _fecModeActive[FEC_MODE_RS_FEC_PLR_272_257] = "Ethernet_Consortium_LL_50G_RS_FEC_PLR -(272,257+1)";
    _fecModeActive[FEC_MODE_INTERLEAVED_RS_FEC_PLR_272_257] =
      "Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1)";

    _fecModeActiveForTableDispaly[FEC_MODE_NO_FEC] = "NO_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_FIRECODE_FEC] = "FC_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_STANDARD_RS_FEC_528_514] = "KR4_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_STANDARD_LL_FEC_271_257] = "LL_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_INTERLEAVED_QUAD_RS_FEC_544_514] = "Quad_KP4_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_INTERLEAVED_STANDARD_RS_FEC_544_514] = "Int_KP4_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_STANDARD_RS_FEC_544_514] = "KP4_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_ZERO_LATENCY_FEC] = "ZL_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_RS_FEC_272_257] = "ELL_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_INTERLEAVED_RS_FEC_272_257] = "Int_ELL_FEC";
    _fecModeActiveForTableDispaly[FEC_MODE_INTERLEAVED_RS_FEC_544_514_PLR] = "Int_KP4_FEC_PLR";
    _fecModeActiveForTableDispaly[FEC_MODE_RS_FEC_544_514_PLR] = "Int_KP4_FEC_PLR";
    _fecModeActiveForTableDispaly[FEC_MODE_RS_FEC_271_257_PLR] = "Int_KP4_FEC_PLR";
    _fecModeActiveForTableDispaly[FEC_MODE_RS_FEC_PLR_272_257] = "ELL_FEC_PLR";
    _fecModeActiveForTableDispaly[FEC_MODE_INTERLEAVED_RS_FEC_PLR_272_257] = "Int_ELL_FEC_PLR";

    _fecModeMask[FEC_MODE_MASK_AU] = make_pair("Auto-FEC", "AU");
    _fecModeMask[FEC_MODE_MASK_NF] = make_pair("No-FEC", "NF");
    _fecModeMask[FEC_MODE_MASK_FC] = make_pair("Firecode_FEC", "FC");
    _fecModeMask[FEC_MODE_MASK_RS_528] = make_pair("RS-FEC (528,514)", "RS");
    _fecModeMask[FEC_MODE_MASK_RS_544_514_QUAD] = make_pair("Interleaved_Quad_RS_FEC - (544,514)", "RS-544Q");
    _fecModeMask[FEC_MODE_MASK_LL_271] = make_pair("LL_RS-FEC (271,257)", "LL");
    _fecModeMask[FEC_MODE_MASK_DF_RS] = make_pair("Interleaved_RS-FEC (544,514)", "DF-RS");
    _fecModeMask[FEC_MODE_MASK_RS_544] = make_pair("RS-FEC (544,514)", "RS-544");
    _fecModeMask[FEC_MODE_MASK_LL_272] = make_pair("LL_RS-FEC (272,257+1)", "LL-272");
    _fecModeMask[FEC_MODE_MASK_DF_LL_272] = make_pair("Interleaved_LL_RS-FEC (272,257+1)", "DF-LL");

    _fecPerSpeed.push_back(make_pair("1600G_8X", ""));
    _fecPerSpeed.push_back(make_pair("800G_4X", ""));
    _fecPerSpeed.push_back(make_pair("400G_2X", ""));
    _fecPerSpeed.push_back(make_pair("200G_1X", ""));

    _fecPerSpeed.push_back(make_pair("800G_8X", ""));
    _fecPerSpeed.push_back(make_pair("400G_4X", ""));
    _fecPerSpeed.push_back(make_pair("200G_2X", ""));
    _fecPerSpeed.push_back(make_pair("100G_1X", ""));

    _fecPerSpeed.push_back(make_pair("400G_8X", ""));
    _fecPerSpeed.push_back(make_pair("200G_4X", ""));
    _fecPerSpeed.push_back(make_pair("100G_2X", ""));
    _fecPerSpeed.push_back(make_pair("50G_1X", ""));
    _fecPerSpeed.push_back(make_pair("50G_2X", ""));
    _fecPerSpeed.push_back(make_pair("100G_4X", ""));

    _fecPerSpeed.push_back(make_pair("100G", ""));
    _fecPerSpeed.push_back(make_pair("56G", ""));
    _fecPerSpeed.push_back(make_pair("50G", ""));
    _fecPerSpeed.push_back(make_pair("40G", ""));
    _fecPerSpeed.push_back(make_pair("25G", ""));
    _fecPerSpeed.push_back(make_pair("10G", ""));

    _loopbackModeList[LOOPBACK_MODE_NO] = make_pair("NO", "No Loopback");
    _loopbackModeList[LOOPBACK_MODE_REMOTE] = make_pair("RM", "PHY Remote Loopback");
    _loopbackModeList[LOOPBACK_MODE_LOCAL] = make_pair("PH", "PHY Local Loopback");
    _loopbackModeList[LOOPBACK_MODE_EXTERNAL] = make_pair("EX", "External Local Loopback");
    _loopbackModeList[LOOPBACK_MODE_LL] = make_pair("LL", "Link Layer Local Loopback");
}

void MlxlinkMaps::ethSpeedMapping()
{
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

    _ETHSpeed2Str[ETH_LINK_SPEED_100_BaseTx] = "BaseTx100M";
    _ETHSpeed2Str[ETH_LINK_SPEED_1000_BaseT] = "BaseT1000M";
    _ETHSpeed2Str[ETH_LINK_SPEED_10M] = "BaseT10M";
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
}

void MlxlinkMaps::extEthSpeedMapping()
{
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_1000BASE_X] = 1;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_5GBASE_R] = 5;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_XFI] = 10;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_XLAUI_4] = 40;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_25GAUI_1] = 25;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_50GAUI_2] = 50;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_50GAUI_1] = 50;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_CAUI_4] = 100;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_100GAUI_2] = 100;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_100GAUI_1] = 100;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_200GAUI_4] = 200;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_200GAUI_2] = 200;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_200GAUI_1] = 200;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_400GAUI_8] = 400;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_400GAUI_4] = 400;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_400GAUI_2] = 400;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_800GAUI_8] = 800;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_800GAUI_4] = 800;
    _EthExtSpeed2gNum[ETH_LINK_SPEED_EXT_1_6TAUI_8] = 1600;

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
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_100GAUI_1] = "100G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_200GAUI_4] = "200G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_200GAUI_2] = "200G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_200GAUI_1] = "200G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_400GAUI_8] = "400G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_400GAUI_4] = "400G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_400GAUI_2] = "400G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_800GAUI_8] = "800G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_800GAUI_4] = "800G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_1_6TAUI_8] = "1600G";
    _EthExtSpeed2Str[ETH_LINK_SPEED_EXT_SGMII_10M] = "10M";
}

void MlxlinkMaps::ibSpeedMapping()
{
    _IBSpeed2gNum[IB_LINK_SPEED_SDR] = 10;
    _IBSpeed2gNum[IB_LINK_SPEED_DDR] = 20;
    _IBSpeed2gNum[IB_LINK_SPEED_QDR] = 40;
    _IBSpeed2gNum[IB_LINK_SPEED_FDR10] = 40;
    _IBSpeed2gNum[IB_LINK_SPEED_FDR] = 56;
    _IBSpeed2gNum[IB_LINK_SPEED_EDR] = 100;
    _IBSpeed2gNum[IB_LINK_SPEED_HDR] = 200;
    _IBSpeed2gNum[IB_LINK_SPEED_NDR] = 400;
    _IBSpeed2gNum[IB_LINK_SPEED_XDR] = 800;

    _IBSpeed2Str[IB_LINK_SPEED_SDR] = "IB-SDR";
    _IBSpeed2Str[IB_LINK_SPEED_DDR] = "IB-DDR";
    _IBSpeed2Str[IB_LINK_SPEED_QDR] = "IB-QDR";
    _IBSpeed2Str[IB_LINK_SPEED_FDR10] = "IB-FDR10";
    _IBSpeed2Str[IB_LINK_SPEED_FDR] = "IB-FDR";
    _IBSpeed2Str[IB_LINK_SPEED_EDR] = "IB-EDR";
    _IBSpeed2Str[IB_LINK_SPEED_HDR] = "IB-HDR";
    _IBSpeed2Str[IB_LINK_SPEED_NDR] = "IB-NDR";
    _IBSpeed2Str[IB_LINK_SPEED_XDR] = "IB-XDR";
}

void MlxlinkMaps::nvlinkSpeedMapping()
{
    _NVLINKSpeed2Str[NVLINK_SPEED_SDR] = "NVLink-SDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_DDR] = "NVLink-DDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_QDR] = "NVLink-QDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_FDR10] = "NVLink-FDR10";
    _NVLINKSpeed2Str[NVLINK_SPEED_FDR] = "NVLink-FDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_EDR] = "NVLink-EDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_HDR] = "NVLink-HDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_NDR] = "NVLink-NDR";
    _NVLINKSpeed2Str[NVLINK_SPEED_XDR] = "NVLink-XDR";
}

void MlxlinkMaps::speedToLanesMapping()
{
    _ETHSpeed2Lanes[ETH_LINK_SPEED_100_BaseTx] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_BaseT] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_SGMII] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_1000_KX] = 1;
    _ETHSpeed2Lanes[ETH_LINK_SPEED_10M] = 1;
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

    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_SGMII_10M] = 1;
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
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_100GAUI_1] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_200GAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_200GAUI_2] = 2;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_200GAUI_1] = 1;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_400GAUI_8] = 8;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_400GAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_400GAUI_2] = 2;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_800GAUI_8] = 8;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_800GAUI_4] = 4;
    _ExtETHSpeed2Lanes[ETH_LINK_SPEED_EXT_1_6TAUI_8] = 8;
}

void MlxlinkMaps::initPortSpeedMapping()
{
    ethSpeedMapping();
    extEthSpeedMapping();
    ibSpeedMapping();
    nvlinkSpeedMapping();
    speedToLanesMapping();
}

void MlxlinkMaps::initPrbsMapping()
{
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
    _prbsModesList[23] = "LT_FRAMES";
    _prbsModesList[24] = "PRBS15";
    _prbsModesList[25] = "PRBS28";
    _prbsModesList[26] = "SQUARE_WAVE3";
    _prbsModesList[27] = "SQUARE_WAVE13";
    _prbsModesList[28] = "SQUARE_WAVE30";

    // Initialize PRBS modulation mapping
    _prbsModulationValue["NRZ"] = PRBS_MODULATION_NRZ;
    _prbsModulationValue["PAM4"] = PRBS_MODULATION_PAM4_ENCODING;
    _prbsModulationValue["PAM4_PRECODING"] = PRBS_MODULATION_PAM4_PRECODING;
    _prbsModulationValue["PAM4_NO_GRAY"] = PRBS_MODULATION_PAM4_NO_GRAY;

    _prbsLaneRateList[0] = "2.5G";
    _prbsLaneRateList[1] = "5G";
    _prbsLaneRateList[2] = "10G";
    _prbsLaneRateList[3] = "10.3125G";
    _prbsLaneRateList[4] = "14.0625G";
    _prbsLaneRateList[5] = "25.78125G";
    _prbsLaneRateList[6] = "53.125G";
    _prbsLaneRateList[7] = "106.25G";
    _prbsLaneRateList[8] = "212.5G";
    _prbsLaneRateList[9] = "N/A";
    _prbsLaneRateList[10] = "1.25G";
    _prbsLaneRateList[11] = "3.125G";
    _prbsLaneRateList[12] = "12.89G";

    // 1G
    _prbsLaneRate["1G"] = {LANE_RATE_1G_CAP, PRBS_1G};
    // 2.5G
    _prbsLaneRate["XAUI"] = {LANE_RATE_XAUI_CAP, PRBS_XAUI};
    _prbsLaneRate["2.5G"] = {LANE_RATE_XAUI_CAP, PRBS_XAUI};
    // 50G-KR4
    _prbsLaneRate["50GE-KR4"] = {LANE_RATE_50G_CAP, PRBS_50G};
    _prbsLaneRate["12.89G"] = {LANE_RATE_50G_CAP, PRBS_50G};
    // SDR
    _prbsLaneRate["IB-SDR"] = {LANE_RATE_SDR_CAP, PRBS_SDR};
    _prbsLaneRate["SDR"] = {LANE_RATE_SDR_CAP, PRBS_SDR};
    // DDR
    _prbsLaneRate["IB-DDR"] = {LANE_RATE_DDR_CAP, PRBS_DDR};
    _prbsLaneRate["DDR"] = {LANE_RATE_DDR_CAP, PRBS_DDR};
    _prbsLaneRate["5G"] = {LANE_RATE_DDR_CAP, PRBS_DDR};
    // QDR
    _prbsLaneRate["IB-QDR"] = {LANE_RATE_QDR_CAP, PRBS_QDR};
    _prbsLaneRate["QDR"] = {LANE_RATE_QDR_CAP, PRBS_QDR};
    // FDR10
    _prbsLaneRate["IB-FDR10"] = {LANE_RATE_FDR10_CAP, PRBS_FDR10};
    _prbsLaneRate["FDR10"] = {LANE_RATE_FDR10_CAP, PRBS_FDR10};
    _prbsLaneRate["10G"] = {LANE_RATE_FDR10_CAP, PRBS_FDR10};
    _prbsLaneRate["40G"] = {LANE_RATE_FDR10_CAP, PRBS_FDR10};
    // FDR
    _prbsLaneRate["IB-FDR"] = {LANE_RATE_FDR_CAP, PRBS_FDR};
    _prbsLaneRate["FDR"] = {LANE_RATE_FDR_CAP, PRBS_FDR};
    _prbsLaneRate["14G"] = {LANE_RATE_FDR_CAP, PRBS_FDR};
    // EDR
    _prbsLaneRate["IB-EDR"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["EDR"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["25G"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["50G"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["50G_2X"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["100G"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    _prbsLaneRate["100G_4X"] = {LANE_RATE_EDR_CAP, PRBS_EDR};
    // HDR
    _prbsLaneRate["IB-HDR"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    _prbsLaneRate["HDR"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    _prbsLaneRate["50G_1X"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    _prbsLaneRate["100G_2X"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    _prbsLaneRate["200G_4X"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    _prbsLaneRate["400G_8X"] = {LANE_RATE_HDR_CAP, PRBS_HDR};
    // NDR
    _prbsLaneRate["IB-NDR"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    _prbsLaneRate["NDR"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    _prbsLaneRate["100G_1X"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    _prbsLaneRate["200G_2X"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    _prbsLaneRate["400G_4X"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    _prbsLaneRate["800G_8X"] = {LANE_RATE_NDR_CAP, PRBS_NDR};
    // XDR
    _prbsLaneRate["IB-XDR"] = {LANE_RATE_XDR_CAP, PRBS_XDR};
    _prbsLaneRate["XDR"] = {LANE_RATE_XDR_CAP, PRBS_XDR};
    _prbsLaneRate["200G_1X"] = {LANE_RATE_XDR_CAP, PRBS_XDR};
    _prbsLaneRate["400G_2X"] = {LANE_RATE_XDR_CAP, PRBS_XDR};
    _prbsLaneRate["800G_4X"] = {LANE_RATE_XDR_CAP, PRBS_XDR};
    _prbsLaneRate["1600G_8X"] = {LANE_RATE_XDR_CAP, PRBS_XDR};

    _prbsRxTuningStatus[0] = "PRBS mode tuning was not performed.";
    _prbsRxTuningStatus[1] = "Performing PRBS mode tuning.";
    _prbsRxTuningStatus[2] = "PRBS mode tuning completed.";
    _prbsRxTuningStatus[3] = "Signal Detect in progress.";

    _prbsLaneRateCap[LANE_RATE_1G_CAP] = "1G (1.25 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_SDR_CAP] = "SDR (2.5 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_XAUI_CAP] = "XAUI/2.5G (3.125 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_DDR_CAP] = "DDR/5G (5 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_QDR_CAP] = "QDR (10 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_FDR10_CAP] = "FDR10/10G/40G (10.3125 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_FDR_CAP] = "FDR/14G (14.0625 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_EDR_CAP] = "EDR/25G/50G/100G (25.78125 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_50G_CAP] = "50GE-KR4/12.89G (12.89 Gb/s)";
    _prbsLaneRateCap[LANE_RATE_HDR_CAP] = "HDR/50G/100G/200G/400G (26.5625Gbd/53.125Gb/s)";
    _prbsLaneRateCap[LANE_RATE_NDR_CAP] = "NDR/100G/200G/400G/800G (53.125Gbd/106.25Gb/s)";
    _prbsLaneRateCap[LANE_RATE_XDR_CAP] = "XDR/200G/400G/800G/1600G (106.25Gbd/212.5Gb/s)";

    _prbsLockStatus[0] = "Not locked";
    _prbsLockStatus[1] = "Locked";

    _prbsEStatus[0] = "PRBS RX is disabled";
    _prbsEStatus[1] = "PRBS RX is enabled";

    _prbsPStatus[0] = "No polarity inversion";
    _prbsPStatus[1] = "PRBS RX polarity inversion.";

    _prbsModulation[PRBS_MODULATION_NRZ] = "NRZ test pattern";
    _prbsModulation[PRBS_MODULATION_PAM4_ENCODING] = "PAM4 encoding";
    _prbsModulation[PRBS_MODULATION_PAM4_PRECODING] = "PAM4 with precoding";
    _prbsModulation[PRBS_MODULATION_PAM4_NO_GRAY] = "PAM4 without gray no precoding";
}

void MlxlinkMaps::initPpbmcAndPepcMapping()
{
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

    _pepcTwistedPairAn[0] = "Normal operation - AN is determine by MDI";
    _pepcTwistedPairAn[1] = "Disable AN";

    _pepcTwistedPairForceMode[0] = "Master mode";
    _pepcTwistedPairForceMode[1] = "Slave mode";

    _pepcTwistedPairAnMode[0] = "auto Master/Slave mode for AN links";
    _pepcTwistedPairAnMode[1] = "Master mode";
    _pepcTwistedPairAnMode[2] = "Slave mode";
}

void MlxlinkMaps::initLinkDownInfoMapping()
{
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
    _pddrLinkDownE2EReasonOpcode[9] = "Minor Error threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[10] = "Physical layer retransmission timeout";
    _pddrLinkDownE2EReasonOpcode[11] = "Heartbeat errors";
    _pddrLinkDownE2EReasonOpcode[12] = "Link Layer credit monitoring watchdog";
    _pddrLinkDownE2EReasonOpcode[13] = "Link Layer integrity threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[14] = "Link Layer buffer overrun";
    _pddrLinkDownE2EReasonOpcode[15] = "Down by outband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[16] = "Down by outband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[17] = "Down by inband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[18] = "Down by inband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[19] = "Down by verification GW";
    _pddrLinkDownE2EReasonOpcode[20] = "Received Remote Fault";
    _pddrLinkDownE2EReasonOpcode[21] = "Received TS1";
    _pddrLinkDownE2EReasonOpcode[22] = "Down by management command";
    _pddrLinkDownE2EReasonOpcode[23] = "Cable was unplugged";
    _pddrLinkDownE2EReasonOpcode[24] = "Cable access issue";
    _pddrLinkDownE2EReasonOpcode[25] = "Thermal shutdown";
    _pddrLinkDownE2EReasonOpcode[26] = "Current issue";
    _pddrLinkDownE2EReasonOpcode[27] = "Power budget";
    _pddrLinkDownE2EReasonOpcode[28] = "MNG forced down the port";
    _pddrLinkDownE2EReasonOpcode[100] = "Peer - No link down indication";
    _pddrLinkDownE2EReasonOpcode[101] = "Peer - Unknown reason";
    _pddrLinkDownE2EReasonOpcode[102] = "Peer - Hi_SER / Hi_BER";
    _pddrLinkDownE2EReasonOpcode[103] = "Peer - Block_Lock loss";
    _pddrLinkDownE2EReasonOpcode[104] = "Peer - Alignment loss";
    _pddrLinkDownE2EReasonOpcode[105] = "Peer - FEC sync loss";
    _pddrLinkDownE2EReasonOpcode[106] = "Peer - PLL lock loss";
    _pddrLinkDownE2EReasonOpcode[107] = "Peer - FIFO overflow";
    _pddrLinkDownE2EReasonOpcode[108] = "Peer - false SKIP condition";
    _pddrLinkDownE2EReasonOpcode[109] = "Peer - Minor Error threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[110] = "Peer - Physical layer retransmission timeout";
    _pddrLinkDownE2EReasonOpcode[111] = "Peer - Heartbeat errors";
    _pddrLinkDownE2EReasonOpcode[112] = "Peer - Link Layer credit monitoring watchdog";
    _pddrLinkDownE2EReasonOpcode[113] = "Peer - Link Layer integrity threshold exceeded";
    _pddrLinkDownE2EReasonOpcode[114] = "Peer - Link Layer buffer overrun";
    _pddrLinkDownE2EReasonOpcode[115] = "Peer - Down by outband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[116] = "Peer - Down by outband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[117] = "Peer - Down by inband command with healthy link";
    _pddrLinkDownE2EReasonOpcode[118] = "Peer - Down by inband command for link with hi ber";
    _pddrLinkDownE2EReasonOpcode[119] = "Peer - Down by verification GW";
    _pddrLinkDownE2EReasonOpcode[120] = "Peer - Received Remote Fault";
    _pddrLinkDownE2EReasonOpcode[121] = "Peer - Received TS1";
    _pddrLinkDownE2EReasonOpcode[122] = "Peer - Down by management command";
    _pddrLinkDownE2EReasonOpcode[123] = "Peer - Cable was unplugged";
    _pddrLinkDownE2EReasonOpcode[124] = "Peer - Cable access issue";
    _pddrLinkDownE2EReasonOpcode[125] = "Peer - Thermal shutdown";
    _pddrLinkDownE2EReasonOpcode[126] = "Peer - Current issue";
    _pddrLinkDownE2EReasonOpcode[127] = "Peer - Power budget";
    _pddrLinkDownE2EReasonOpcode[128] = "Peer - MNG forced down the port";
}

void MlxlinkMaps::initLinkUpInfo()
{
    _upReasonPwr[UP_REASON_PWR_NO_DOWN_COMMAND] = "No down command / unknown";
    _upReasonPwr[UP_REASON_PWR_KEEP_LINK_UP_ON_BOOT] = "Keep link up on boot";
    _upReasonPwr[UP_REASON_PWR_KEEP_LINK_UP_ETH_IB] = "Keep link up Eth/IB";
    _upReasonPwr[UP_REASON_PWR_KEEP_LINK_UP_ON_STANDBY] = "Keep link up on standby";

    _upReasonDrv[UP_REASON_DRV_NO_DOWN_COMMAND] = "No down command / unknown";
    _upReasonDrv[UP_REASON_DRV_UP_BY_AT_LEAST_ONE_OF_THE_HOSTS] = "Up by at least one of the hosts";

    _upReasonMng[UP_REASON_MNG_NO_DOWN_COMMAND] = "No down command / unknown";
    _upReasonMng[UP_REASON_MNG_BMC_FORCE_LINKUP] = "BMC force linkup";
    _upReasonMng[UP_REASON_MNG_WOL_FORCE_LINKUP] = "WOL force linkup";
    _upReasonMng[UP_REASON_MNG_ANS_FORCE_LINKUP] = "ASN.1 force link up";

    _fastLinkUpStatus[FAST_LINK_UP_STATUS_UNKOWN] = "Unknown";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_FAST_LINKUP_WAS_PERFORMED] = "Fast Link-UP was performed.";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_REGULAR_LINK_UP_DUE_CABLE_CHANGE] =
      "Regular link-up flow was performed due to changes in cable";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_REGULAR_LINK_UP_DUE_PROTOCOL_CHANGE] =
      "Regular link-up flow was performed due to changes in protocol (speed or FEC)";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_REGULAR_LINK_UP_DUE_NON_FASTBOOT] =
      "Regular link-up flow was performed due to a non-fastbootable FW version (PCNR is not supported)";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_REGULAR_LINK_UP_DUE_CABLE_MLPN_FLOW] =
      "Regular link-up performed due to MLPN flow";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_REGULAR_LINK_UP_DUE_CABLE_MLPN_PCNR] =
      "No Regular link-up performed due to PCNR.tuning_override configuration while port was in “down” state.";
    _fastLinkUpStatus[FAST_LINK_UP_STATUS_INVALID_FASTBOOT] =
      "Invalid fastboot data struct (0xCAFECAFE magic value is not present. For example, SW reset was executed before "
      "finish saving data during PCNR flow)";
}

void MlxlinkMaps::initSltpStatusMapping()
{
    _SltpEdrParams[SLTP_EDR_POLARITY] = PRM_FIELD{"polarity", "Pol", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_TAP0] = PRM_FIELD{"ob_tap0", "tap0", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_TAP1] = PRM_FIELD{"ob_tap1", "tap1", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_TAP2] = PRM_FIELD{"ob_tap2", "tap2", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_BIAS] = PRM_FIELD{"ob_bias", "bias", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_PREEMP_MODE] =
      PRM_FIELD{"ob_preemp_mode", "preemp_mode", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_REG] = PRM_FIELD{"ob_reg", "reg", FIELD_ACCESS_ADVANCED, false, LINK_SPEED_ALL};
    _SltpEdrParams[SLTP_EDR_OB_LEVA] = PRM_FIELD{"ob_leva", "leva", FIELD_ACCESS_ADVANCED, false, LINK_SPEED_ALL};

    _SltpHdrParams[SLTP_HDR_PRE_2_TAP] = PRM_FIELD{"pre_2_tap", "pre2Tap", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_PRE_TAP] = PRM_FIELD{"pre_tap", "preTap", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_MAIN_TAP] = PRM_FIELD{"main_tap", "mainTap", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_POST_TAP] = PRM_FIELD{"post_tap", "postTap", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_OB_M2LP] = PRM_FIELD{"ob_m2lp", "m2lp", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_OB_AMP] = PRM_FIELD{"ob_amp", "amp", FIELD_ACCESS_RW, false, LINK_SPEED_ALL};
    _SltpHdrParams[SLTP_HDR_OB_ALEV_OUT] = PRM_FIELD{"ob_alev_out", "alev_out", FIELD_ACCESS_W, false, LINK_SPEED_ALL};

    _SltpNdrParams[SLTP_NDR_FIR_PRE3] = PRM_FIELD{"fir_pre3", "fir_pre3", FIELD_ACCESS_RW, true, LINK_SPEED_100G_LANE};
    _SltpNdrParams[SLTP_NDR_FIR_PRE2] =
      PRM_FIELD{"fir_pre2", "fir_pre2", FIELD_ACCESS_RW, true, LINK_SPEED_100G_LANE | LINK_SPEED_50G_LANE};
    _SltpNdrParams[SLTP_NDR_FIR_PRE1] = PRM_FIELD{"fir_pre1", "fir_pre1", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpNdrParams[SLTP_NDR_FIR_MAIN] = PRM_FIELD{"fir_main", "fir_main", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpNdrParams[SLTP_NDR_FIR_POST1] = PRM_FIELD{"fir_post1", "fir_post1", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpNdrParams[SLTP_NDR_DRV_AMP] = PRM_FIELD{"drv_amp", "drv_amp", FIELD_ACCESS_R, false, LINK_SPEED_ALL};

    _SltpXdrParams[SLTP_XDR_TAP0] = PRM_FIELD{"tap0", "fir_pre4", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP1] =
      PRM_FIELD{"tap1", "fir_pre3", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE | LINK_SPEED_100G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP2] = PRM_FIELD{"tap2", "fir_pre2", FIELD_ACCESS_RW, true,
                                              LINK_SPEED_200G_LANE | LINK_SPEED_100G_LANE | LINK_SPEED_50G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP3] = PRM_FIELD{"tap3", "fir_pre1", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpXdrParams[SLTP_XDR_TAP4] = PRM_FIELD{"tap4", "fir_main", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpXdrParams[SLTP_XDR_TAP5] = PRM_FIELD{"tap5", "fir_post1", FIELD_ACCESS_RW, true, LINK_SPEED_ALL};
    _SltpXdrParams[SLTP_XDR_TAP6] = PRM_FIELD{"tap6", "fir_post2", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP7] = PRM_FIELD{"tap7", "fir_post3", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP8] = PRM_FIELD{"tap8", "fir_post4", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP9] = PRM_FIELD{"tap9", "fir_post5", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP10] = PRM_FIELD{"tap10", "fir_post6", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_TAP11] = PRM_FIELD{"tap11", "fir_post7", FIELD_ACCESS_RW, true, LINK_SPEED_200G_LANE};
    _SltpXdrParams[SLTP_XDR_DRV_AMP] = PRM_FIELD{"drv_amp", "drv_amp", FIELD_ACCESS_R, false, LINK_SPEED_ALL};

    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_INVALID_PRE3] = "pre3 is out of range";
    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_INVALID_PRE2] = "pre2 is out of range";
    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_INVALID_PRE1] = "pre1 is out of range";
    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_INVALID_MAIN] = "main tap is out of range";
    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_INVALID_POST] = "sum of taps is out of range";
    _SLTP7BadSetStatus2Str[BAD_STAT_7NM_TAP_SPEED_MISMATCH] = "taps not aligned with speed";

    _SLTP16BadSetStatus2Str[SET_STATUS16_INVALID_PARM] =
      "taps values can't be set to serdes due to internal limitations. ";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_M2LP_AMP] =
      "ob_m2lp, ob_amp and ob_alev is in legal range each, "
      "but the total combination can't be set to serdes due to internal "
      "limitations.";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_M2LP] = "Illegal ob_m2lp";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_AMP] = "Illegal ob_amp";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_ALEV_OUT] = "Illegal ob_alev_out";
    _SLTP16BadSetStatus2Str[SET_STATUS16_ILLEGAL_TAPS] = "Illegal taps";
    _SLTP16BadSetStatus2Str[SET_STATUS16_UNKNOWN] = "Unknown failure status";

    _SLTPBadSetStatus2Str[SET_STATUS16_INVALID_PARM] = "Invalid parameter";
    _SLTPBadSetStatus2Str[SET_STATUS_ILLEGAL_OB_BAIS] = "Illegal ob_bais value";
    _SLTPBadSetStatus2Str[SET_STATUS_ILLEGAL_OB_TAPS_POLARITY] = "Illegal ob_taps polarity (distance between taps)";
    _SLTPBadSetStatus2Str[SET_STATUS_UNKNOWN] = "Unknown failure status";
}

void MlxlinkMaps::initPSCDRateMaskMapping()
{
    _PSCDRateMask2Str[PSCD_RATE_MASK_312P5_MBPS] = "312.5M";
    _PSCDRateStr2Mask[_PSCDRateMask2Str[PSCD_RATE_MASK_312P5_MBPS]] = PSCD_RATE_MASK_312P5_MBPS;

    _PSCDRateMask2Str[PSCD_RATE_MASK_53P125_GBPS] = "53.125G";
    _PSCDRateStr2Mask[_PSCDRateMask2Str[PSCD_RATE_MASK_53P125_GBPS]] = PSCD_RATE_MASK_53P125_GBPS;

    _PSCDRateMask2Str[PSCD_RATE_MASK_106P25_GBPS] = "106.25G";
    _PSCDRateStr2Mask[_PSCDRateMask2Str[PSCD_RATE_MASK_106P25_GBPS]] = PSCD_RATE_MASK_106P25_GBPS;

    _PSCDRateMask2Str[PSCD_RATE_MASK_200_GBPS] = "200G";
    _PSCDRateStr2Mask[_PSCDRateMask2Str[PSCD_RATE_MASK_200_GBPS]] = PSCD_RATE_MASK_200_GBPS;

    _PSCDRateMask2Str[PSCD_RATE_MASK_212P5_GBPS] = "212.5G";
    _PSCDRateStr2Mask[_PSCDRateMask2Str[PSCD_RATE_MASK_212P5_GBPS]] = PSCD_RATE_MASK_212P5_GBPS;
}

void MlxlinkMaps::initPSCDRoleMaskMapping()
{
    _PSCDRoleMask2Str[PSCD_ROLE_MASK_TLM] = "TLM";
    _PSCDRoleStr2Mask[_PSCDRoleMask2Str[PSCD_ROLE_MASK_TLM]] = PSCD_ROLE_MASK_TLM;

    _PSCDRoleMask2Str[PSCD_ROLE_MASK_RLM] = "RLM";
    _PSCDRoleStr2Mask[_PSCDRoleMask2Str[PSCD_ROLE_MASK_RLM]] = PSCD_ROLE_MASK_RLM;

    _PSCDRoleMask2Str[PSCD_ROLE_MASK_TCLM] = "TCLM";
    _PSCDRoleStr2Mask[_PSCDRoleMask2Str[PSCD_ROLE_MASK_TCLM]] = PSCD_ROLE_MASK_TCLM;
}

void MlxlinkMaps::initPSCDModeBRoleMaskMapping()
{
    _PSCDModeBRoleMask2Str[PSCD_MODE_B_ROLE_MASK_PRIMARY] = "PRIMARY";
    _PSCDModeBRoleStr2Mask[_PSCDModeBRoleMask2Str[PSCD_MODE_B_ROLE_MASK_PRIMARY]] = PSCD_MODE_B_ROLE_MASK_PRIMARY;

    _PSCDModeBRoleMask2Str[PSCD_MODE_B_ROLE_MASK_SECONDARY] = "SECONDARY";
    _PSCDModeBRoleStr2Mask[_PSCDModeBRoleMask2Str[PSCD_MODE_B_ROLE_MASK_SECONDARY]] = PSCD_MODE_B_ROLE_MASK_SECONDARY;
}

void MlxlinkMaps::initPpttParamsMapping()
{
    _ppttParams[LANE_RATE_ADMIN] = PRM_FIELD{"lane_rate_admin", "lane_rate_admin", FIELD_ACCESS_RW, false};
}

void MlxlinkMaps::initPpttSpeedMapping()
{
    _ppttSpeedMapping[PPTT_SDR] = ETH_LINK_SPEED_EXT_2_5GBASE_X;
    _ppttSpeedMapping[PPTT_DDR] = ETH_LINK_SPEED_EXT_5GBASE_R;
    _ppttSpeedMapping[PPTT_QDR] = ETH_LINK_SPEED_10M;
    _ppttSpeedMapping[PPTT_FDR10] = ETH_LINK_SPEED_10M;
    _ppttSpeedMapping[PPTT_FDR] = ETH_LINK_SPEED_10M;
    _ppttSpeedMapping[PPTT_EDR] = ETH_LINK_SPEED_25G_CR | ETH_LINK_SPEED_25G_KR | ETH_LINK_SPEED_25G_SR;
    _ppttSpeedMapping[PPTT_HDR] = ETH_LINK_SPEED_EXT_50GAUI_1;
    _ppttSpeedMapping[PPTT_NDR] = ETH_LINK_SPEED_EXT_100GAUI_1;
    _ppttSpeedMapping[PPTT_XDR] = LINK_SPEED_200G_LANE;
    _ppttSpeedMapping[PPTT_1GE] = ETH_LINK_SPEED_EXT_1000BASE_X;
    _ppttSpeedMapping[PPTT_XAUI] = ETH_LINK_SPEED_EXT_XLAUI_4;
    _ppttSpeedMapping[PPTT_50GE_KR4] = ETH_LINK_SPEED_50G_KR4;
    _ppttSpeedMapping[PPTT_RESERVED] = 0;
}

void MlxlinkMaps::cmisIbComlianceMapping()
{
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_SDR] = "SDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_DDR] = "DDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_QDR] = "QDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_FDR] = "FDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_EDR] = "EDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_HDR] = "HDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_NDR] = "NDR";
    _cableComplianceCmisIb[CMIS_IB_COMPLIANCE_CODE_XDR] = "XDR";
}

void MlxlinkMaps::cimsCableBreakoutMapping()
{
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_UNSPECIFIED] = "Unspecified";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_QSFPDD] = "X to X";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_2QSFP_or_2QSFPDD] = "X to 2xQSFP or 2xX (depopulated / 4 lanes)";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_4SFPDD_or_4QSFP] = "X to 4xDSFP or 4xQSFP (depopulated / 2 lanes)";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_8SFP] = "X to 8xSFP";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_QSFP_or_QSFPDD] =
      "X (depopulated / 4 lanes) to QSFP or X (depopulated / 4 lanes)";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_2QSFP] =
      "X (depopulated / 4 lanes) to 2xX(depopulated / 2 lanes) or 2xSFP-DD";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_QSFPDD_to_4SFP] = "X (depopulated / 4 lanes) to 4xSFP";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_SFPDD_to_SFPDD] = "X(/ 2 lane module) to X";
    _cimsCableBreakout[CMIS_CABLE_BREAKOUT_SFPDD_to_2SFPDD] = "X(/ 2 lane module) to 2xSFP";
}

void MlxlinkMaps::rxTxCdrCapMapping()
{
    _txInputFreq[0] = "Tx_input_lanes_1_8";
    _txInputFreq[1] = "Tx_input_lanes_1_4_and_5-8";
    _txInputFreq[2] = "Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8";
    _txInputFreq[3] = "Lanes_may_be_asynchronous_in_frequency";

    _rxTxCdrCap[RX_TX_CDR_CAP_NO_CDR] = "No CDR";
    _rxTxCdrCap[RX_TX_CDR_CAP_BUILD_IN_CDR_WITH_ON_OFF_CONTROL] = "Build-in CDR with on/off control";
    _rxTxCdrCap[RX_TX_CDR_CAP_BUILD_IN_CDR_WITHOUT_ON_OFF_CONTROL] = "Build-in CDR without on/off control";

    _moduleRxAmp[0] = "100-400 mV (P-P)";
    _moduleRxAmp[1] = "300-600 mV (P-P)";
    _moduleRxAmp[2] = "400-800 mV (P-P)";
    _moduleRxAmp[3] = "600-1200 mV (P-P)";
    _moduleRxAmp[4] = "Custom";
    _moduleRxAmp[5] = "Custom";
    _moduleRxAmp[6] = "Custom";
    _moduleRxAmp[7] = "Custom";
    _moduleRxAmp[8] = "Custom";
    _moduleRxAmp[9] = "Custom";
    _moduleRxAmp[10] = "Custom";
    _moduleRxAmp[11] = "Custom";
    _moduleRxAmp[12] = "Custom";
    _moduleRxAmp[13] = "Custom";
    _moduleRxAmp[14] = "Custom";
    _moduleRxAmp[15] = "Custom";

    _moduleRxAmpCap[PMCR_RX_AMP_BIT0] = "0 (" + _moduleRxAmp[0] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT1] = "1 (" + _moduleRxAmp[1] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT2] = "2 (" + _moduleRxAmp[2] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT3] = "3 (" + _moduleRxAmp[3] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT4] = "4 (" + _moduleRxAmp[4] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT5] = "5 (" + _moduleRxAmp[5] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT6] = "6 (" + _moduleRxAmp[6] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT7] = "7 (" + _moduleRxAmp[7] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT8] = "8 (" + _moduleRxAmp[8] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT9] = "9 (" + _moduleRxAmp[9] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT10] = "10 (" + _moduleRxAmp[10] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT11] = "11 (" + _moduleRxAmp[11] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT12] = "12 (" + _moduleRxAmp[12] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT13] = "13 (" + _moduleRxAmp[13] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT14] = "14 (" + _moduleRxAmp[14] + ")";
    _moduleRxAmpCap[PMCR_RX_AMP_BIT15] = "15 (" + _moduleRxAmp[15] + ")";
}

void MlxlinkMaps::rxPowerTypeMapping()
{
    _rxPowerType[RX_POWER_TYPE_OMA] = "OMA";
    _rxPowerType[RX_POWER_TYPE_AVERAGE_POWER] = "Average power";
}

void MlxlinkMaps::maxReadReqSizeMapping()
{
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_128B] = "128B";
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_256B] = "256B";
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_512B] = "512B";
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_1024B] = "1024B";
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_2048B] = "2048B";
    _maxReadReqSize[MAX_READ_REQUEST_SIZE_4096B] = "4096B";
}

void MlxlinkMaps::pwrStatusMapping()
{
    _pwrStatus[PWR_STATUS_0] = "PCI power report could not be read";
    _pwrStatus[PWR_STATUS_1] = "Sufficient power reported";
    _pwrStatus[PWR_STATUS_2] = "Insufficient power reported";
}

void MlxlinkMaps::portTypeMapping()
{
    _portType[PORT_TYPE_EP_MPEIN] = "PCI Express Endpoint port";
    _portType[PORT_TYPE_RC_MPEIN] = "Root Port of PCI Express Root Complex";
    _portType[PORT_TYPE_UP_MPEIN] = "PCI Express Upstream port";
    _portType[PORT_TYPE_DP_MPEIN] = "PCI Express Downstream port";
}

void MlxlinkMaps::linkPeerMaxSpeedMapping()
{
    _linkPeerMaxSpeed[LINK_PEER_MAX_SPEED_2_5G] = "2.5G - (Gen1)";
    _linkPeerMaxSpeed[LINK_PEER_MAX_SPEED_5G] = "5G - (Gen2)";
    _linkPeerMaxSpeed[LINK_PEER_MAX_SPEED_8G] = "8G - (Gen3)";
    _linkPeerMaxSpeed[LINK_PEER_MAX_SPEED_16G] = "16G - (Gen4)";
    _linkPeerMaxSpeed[LINK_PEER_MAX_SPEED_32G] = "32G (Gen5)";
}

void MlxlinkMaps::portStateMapping()
{
    _portState[PORT_STATE_0] = "Disable TS1";
    _portState[PORT_STATE_1] = "Disable Ack";
    _portState[PORT_STATE_2] = "Disable Wait";
    _portState[PORT_STATE_3] = "RESET";
    _portState[PORT_STATE_4] = "Loop Back Master Active";
    _portState[PORT_STATE_5] = "Loop Back Master Exit";
    _portState[PORT_STATE_6] = "Loop Back Slave Entry";
    _portState[PORT_STATE_7] = "Loop Back Slave Align";
    _portState[PORT_STATE_8] = "Loop Back Slave EB Threshold";
    _portState[PORT_STATE_9] = "Loop Back Slave Active";
    _portState[PORT_STATE_10] = "Loop Back Slave Idle";
    _portState[PORT_STATE_11] = "Loop Back Slave Exit";
    _portState[PORT_STATE_12] = "Detect Quiet";
    _portState[PORT_STATE_13] = "Detect Active 1";
    _portState[PORT_STATE_14] = "Detect Active 2";
    _portState[PORT_STATE_15] = "Polling Active";
    _portState[PORT_STATE_16] = "Polling Compliance Entry";
    _portState[PORT_STATE_17] = "Polling Compliance";
    _portState[PORT_STATE_18] = "Polling Compliance Exit";
    _portState[PORT_STATE_19] = "Polling Config";
    _portState[PORT_STATE_20] = "Config Width Start";
    _portState[PORT_STATE_21] = "Config Width Ack";
    _portState[PORT_STATE_22] = "Config Lane Wait";
    _portState[PORT_STATE_23] = "Config Lane Ack";
    _portState[PORT_STATE_24] = "Config Complete";
    _portState[PORT_STATE_25] = "Config Idle";
    _portState[PORT_STATE_26] = "L0s";
    _portState[PORT_STATE_27] = "L1 ENTER";
    _portState[PORT_STATE_28] = "L1 ACTIVE";
    _portState[PORT_STATE_29] = "L1 EXIT";
    _portState[PORT_STATE_30] = "Recover Receiver Lock";
    _portState[PORT_STATE_31] = "Recover Speed";
    _portState[PORT_STATE_32] = "Recover Config";
    _portState[PORT_STATE_33] = "Recover Idle";
    _portState[PORT_STATE_34] = "Recover ESpeed";
    _portState[PORT_STATE_35] = "Recover Equalization Phase 0";
    _portState[PORT_STATE_36] = "Recover Equalization Phase 1";
    _portState[PORT_STATE_37] = "Recover Equalization Phase 2";
    _portState[PORT_STATE_38] = "Recover Equalization Phase 3";
    _portState[PORT_STATE_39] = "Recover Equalization Idle";
    _portState[PORT_STATE_40] = "Force TS1";
    _portState[PORT_STATE_41] = "Force TS2";
    _portState[PORT_STATE_42] = "Force IDLE";
    _portState[PORT_STATE_43] = "Force COMP";
    _portState[PORT_STATE_44] = "Force Force disable";
}

void MlxlinkMaps::cmisModuleStMapping()
{
    _cimsModuleSt[CIMS_MODULE_ST_RESERVED] = "N/A";
    _cimsModuleSt[CIMS_MODULE_ST_LOWPWR_STATE] = "LowPwr state";
    _cimsModuleSt[CIMS_MODULE_ST_PWRUP_STATE] = "PwrUp state";
    _cimsModuleSt[CIMS_MODULE_ST_READY_STATE] = "Ready state";
    _cimsModuleSt[CIMS_MODULE_ST_PWRDN_STATE] = "PwrDn state";
    _cimsModuleSt[CIMS_MODULE_ST_FAULT_STATE] = "Fault state";
}

void MlxlinkMaps::tempFlagsMapping()
{
    _tempFlags[TEMP_FLAGS_NO_ALARM_WARN] = "N/A";
    _tempFlags[TEMP_FLAGS_HI_TEMP_ALARM] = "high_temp_alarm";
    _tempFlags[TEMP_FLAGS_LO_TEMP_ALARM] = "low_temp_alarm";
    _tempFlags[TEMP_FLAGS_HI_TEMP_WARNING] = "high_temp_warning";
    _tempFlags[TEMP_FLAGS_LO_TEMP_WARNING] = "low_temp_warning";
}

void MlxlinkMaps::vccFlagsMapping()
{
    _vccFlags[VCC_FLAGS_NO_ALARM_WARN] = "N/A";
    _vccFlags[VCC_FLAGS_HI_VCC_ALARM] = "high_vcc_alarm";
    _vccFlags[VCC_FLAGS_LO_VCC_ALARM] = "low_vcc_alarm";
    _vccFlags[VCC_FLAGS_HI_VCC_WARNING] = "high_vcc_warning";
    _vccFlags[VCC_FLAGS_LO_VCC_WARNING] = "low_vcc_warning";
}

void MlxlinkMaps::dataPathStateMapping()
{
    _dataPathSt[DATA_PATH_STATE_RES] = "N/A";
    _dataPathSt[DATA_PATH_STATE_DEACTIVATED] = "DPDeactivated";
    _dataPathSt[DATA_PATH_STATE_INIT] = "DPInit";
    _dataPathSt[DATA_PATH_STATE_DEINIT] = "DPDeinit";
    _dataPathSt[DATA_PATH_STATE_ACTIVATED] = "DPActivated";
    _dataPathSt[DATA_PATH_STATE_TX_TURN_ON] = "DPTxTurnOn";
    _dataPathSt[DATA_PATH_STATE_TX_TURN_OFF] = "DPTxTurnOff";
    _dataPathSt[DATA_PATH_STATE_INITALIZED] = "DPInitialized";
}

void MlxlinkMaps::errorCodeResMapping()
{
    _moduleOperSt[MODULE_OPER_STATUS_INIT] = "initializing";
    _moduleOperSt[MODULE_OPER_STATUS_PLUGGED_EN] = "plugged_enable";
    _moduleOperSt[MODULE_OPER_STATUS_UNPLUGGED] = "unplugged";
    _moduleOperSt[MODULE_OPER_STATUS_PLUGGED_WITH_ERROR] = "module_plugged_with_error";

    _moduleErrType[MODULE_ERROR_TYPE_POWER] = "Power_Budget_Exceeded";
    _moduleErrType[MODULE_ERROR_TYPE_LONG_RANGE] = "Long_Range_for_non_MLNX_cable_or_module";
    _moduleErrType[MODULE_ERROR_TYPE_BUS_STUCK] = "Bus_stuck - (I2C Data or clock shorted)";
    _moduleErrType[MODULE_ERROR_TYPE_BAD] = "bad_or_unsupported_EEPROM";
    _moduleErrType[MODULE_ERROR_TYPE_ENF] = "Enforce_part_number_list";
    _moduleErrType[MODULE_ERROR_TYPE_UNSUPPORTED] = "unsupported_cable";
    _moduleErrType[MODULE_ERROR_TYPE_HIGH_TEMP] = "unsupported_cable";
    _moduleErrType[MODULE_ERROR_TYPE_BAD_CBL] = "bad_cable - (Module/Cable is shorted)";
    _moduleErrType[MODULE_ERROR_TYPE_PMD] = "PMD_type_is_not_enabled";
    _moduleErrType[MODULE_ERROR_TYPE_PCIE] = "pcie_system_power_slot_Exceeded";

    _errorCodeRes[ERROR_CODE_RES_CONFIG_UNDEF] = "ConfigUndefined";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_SUCC] = "ConfigSuccess";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ] = "ConfigRejected";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_INV_APP_SEI] = "ConfigRejectedInvalidAppSel";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_INV_DATA_PTH] = "ConfigRejectedInvalidDataPath";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_INV_SI] = "ConfigRejectedInvalidSI";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_LANES_IN_USE] = "ConfigRejectedLanesInUse";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_PART_DATA_PTH] = "ConfigRejectedPartialDataPath";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_IN_PROG] = "ConfigInProgress";
    _errorCodeRes[ERROR_CODE_RES_CONFIG_REJ_INV_VS_SI] = "ConfigRejectedInvalidVS_SI";
}

void MlxlinkMaps::qsfpFarEndCableBreakoutMapping()
{
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_CABLE_FAR_END_IS_UNSPECIFIED] = "Far end is unspecified";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_4_CHANNELS_IMPLEM_OR_SEPAR_MOD_4_CHANNEL_CONN] =
      "Cable with single far-end with 4 channels implemented, or separable module with a 4-channel connector";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_2_CHANNELS_IMPLEM_OR_SEPAR_MOD_2_CHANNEL_CONN] =
      "Cable with single far-end with 4 channels implemented, or separable module with a 4-channel connector";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_1_CHANNELS_IMPLEM_OR_SEPAR_MOD_1_CHANNEL_CONN] =
      "Cable with single far-end with 1 channel implemented, or separable module with a 1-channel connector";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_4_FAR_ENDS_1_CHANNELS_IMPLEM_IN_EACH] =
      "4 far-ends with 1 channel implemented in each (i.e. 4x1 break out)";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_2_FAR_ENDS_2_CHANNELS_IMPLEM_IN_EACH] =
      "2 far-ends with 2 channels implemented in each (i.e. 2x2 break out)";
    _qsfpFarEndCableBreakout[QSFP_CABLE_BREAKOUT_2_FAR_ENDS_1_CHANNELS_IMPLEM_IN_EACH] =
      "2 far-ends with 1 channel implemented in each (i.e. 2x1 break out)";
}

void MlxlinkMaps::modulePrbsMapping()
{
    _modulePrbsSt[PMPT_STATUS_NORMAL_MODE] = "Normal mission mode";
    _modulePrbsSt[PMPT_STATUS_NOT_SUPPORTED] = "Module is disabled/not connected";
    _modulePrbsSt[PMPT_STATUS_CONFIG_ERROR] = "unsupported configuration setting";
    _modulePrbsSt[PMPT_STATUS_GEN_ONLY] = "PRBS Generator only";
    _modulePrbsSt[PMPT_STATUS_CH_ONLY] = "PRBS Checker only";
    _modulePrbsSt[PMPT_STATUS_BOTH] = "PRBS traffic both Checker and Generator";

    _modulePrbsSwapAdmin[0] = "NO MSB <-> LSB swapping";
    _modulePrbsSwapAdmin[1] = "MSB <-> LSB swapping";

    _modulePrbsInvAdmin[0] = "NO PRBS inversion";
    _modulePrbsInvAdmin[1] = "PRBS inversion";

    _modulePrbsModulation[0] = "NRZ test pattern";
    _modulePrbsModulation[1] = "PAM4 encoding";

    _modulePrbsRateCapToStr[0] = "Non Selected";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_1G] = "1.25 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_SDR] = "2.5 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_40G_40G] = "10.3125 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_FDR] = "14.0625 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_EDR] = "25.78125 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_HDR] = "53.125 Gb/s";
    _modulePrbsRateCapToStr[MODULE_PRBS_LANE_RATE_NDR] = "106.25 Gb/s";

    _modulePrbsRateStrToCap["1G"] = MODULE_PRBS_LANE_RATE_1G;
    _modulePrbsRateStrToCap["1.25G"] = MODULE_PRBS_LANE_RATE_1G;

    _modulePrbsRateStrToCap["IB-SDR"] = MODULE_PRBS_LANE_RATE_SDR;
    _modulePrbsRateStrToCap["SDR"] = MODULE_PRBS_LANE_RATE_SDR;
    _modulePrbsRateStrToCap["2.5G"] = MODULE_PRBS_LANE_RATE_SDR;

    _modulePrbsRateStrToCap["10G"] = MODULE_PRBS_LANE_RATE_40G_40G;
    _modulePrbsRateStrToCap["40G"] = MODULE_PRBS_LANE_RATE_40G_40G;
    _modulePrbsRateStrToCap["10.3125G"] = MODULE_PRBS_LANE_RATE_40G_40G;

    _modulePrbsRateStrToCap["IB-FDR"] = MODULE_PRBS_LANE_RATE_FDR;
    _modulePrbsRateStrToCap["FDR"] = MODULE_PRBS_LANE_RATE_FDR;
    _modulePrbsRateStrToCap["14G"] = MODULE_PRBS_LANE_RATE_FDR;
    _modulePrbsRateStrToCap["14.0625G"] = MODULE_PRBS_LANE_RATE_FDR;

    _modulePrbsRateStrToCap["IB-EDR"] = MODULE_PRBS_LANE_RATE_EDR;
    _modulePrbsRateStrToCap["EDR"] = MODULE_PRBS_LANE_RATE_EDR;
    _modulePrbsRateStrToCap["25G"] = MODULE_PRBS_LANE_RATE_EDR;
    _modulePrbsRateStrToCap["25.78125G"] = MODULE_PRBS_LANE_RATE_EDR;

    _modulePrbsRateStrToCap["IB-HDR"] = MODULE_PRBS_LANE_RATE_HDR;
    _modulePrbsRateStrToCap["HDR"] = MODULE_PRBS_LANE_RATE_HDR;
    _modulePrbsRateStrToCap["50G"] = MODULE_PRBS_LANE_RATE_HDR;
    _modulePrbsRateStrToCap["53.125G"] = MODULE_PRBS_LANE_RATE_HDR;

    _modulePrbsRateStrToCap["IB-NDR"] = MODULE_PRBS_LANE_RATE_NDR;
    _modulePrbsRateStrToCap["NDR"] = MODULE_PRBS_LANE_RATE_NDR;
    _modulePrbsRateStrToCap["100G"] = MODULE_PRBS_LANE_RATE_NDR;
    _modulePrbsRateStrToCap["106.25G"] = MODULE_PRBS_LANE_RATE_NDR;

    _modulePrbsModeCapToStr[PRBS31_CAP] = "PRBS31";
    _modulePrbsModeCapToStr[PRBS23A_CAP] = "PRBS23";
    _modulePrbsModeCapToStr[PRBS7_CAP] = "PRBS7";
    _modulePrbsModeCapToStr[PRBS11_CAP] = "PRBS11";
    _modulePrbsModeCapToStr[PRBS9_CAP] = "PRBS9";
    _modulePrbsModeCapToStr[PRBS13A_CAP] = "PRBS13";
    _modulePrbsModeCapToStr[SSPR_CAP] = "SSPR";
    _modulePrbsModeCapToStr[SSPRQ_CAP] = "SSPRQ";

    _modulePrbsModeStrToCap["PRBS31"] = PRBS31_CAP;
    _modulePrbsModeStrToCap["PRBS23"] = PRBS23A_CAP;
    _modulePrbsModeStrToCap["PRBS7"] = PRBS7_CAP;
    _modulePrbsModeStrToCap["PRBS11"] = PRBS11_CAP;
    _modulePrbsModeStrToCap["PRBS9"] = PRBS9_CAP;
    _modulePrbsModeStrToCap["PRBS13"] = PRBS13A_CAP;
    _modulePrbsModeStrToCap["SSPR"] = SSPR_CAP;
    _modulePrbsModeStrToCap["SSPRQ"] = SSPRQ_CAP;

    _modulePMPDStatus[PMPD_STATUS_NOT_SUPPORTED] = "Not Supported";
    _modulePMPDStatus[PMPD_STATUS_NORMAL_MODE] = "Normal Mode";
    _modulePMPDStatus[PMPD_STATUS_NOT_LOCKED] = "Not Locked";
    _modulePMPDStatus[PMPD_STATUS_LOCKED] = "Locked";

    _moduleScopeToStr[MODULE_PRBS_ACCESS_CH] = "Checker";
    _moduleScopeToStr[MODULE_PRBS_ACCESS_GEN] = "Generator";
    _moduleScopeToStr[MODULE_PRBS_ACCESS_BOTH] = "Module";
    _moduleScopeToStr[MODULE_PRBS_ACCESS_CH_GEN] = "Module";
}

void MlxlinkMaps::qsfpComlianceMapping()
{
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_Unspecified] = "Unspecified";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40G_ACTIVE_CABLE_XLPPI] = "40G Active Cable (XLPPI)";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_LR4] = "40GBASE-LR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_SR4] = "40GBASE-SR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_CR4] = "40GBASE-CR4";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_SR] = "10GBASE-SR";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LR] = "10GBASE-LR";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LRM] = "10GBASE-LRM";
    _cableComplianceQsfp[QSFP_ETHERNET_COMPLIANCE_CODE_EXT] = "Extended Specification Compliance valid";
}

void MlxlinkMaps::sfpComplianceMapping()
{
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_Unspecified] = "Unspecified";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_SR] = "10G Base-SR";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LR] = "10G Base-LR";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LRM] = "10G Base-LRM";
    _cableComplianceSfp[SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_ER] = "10G Base-ER";
}

void MlxlinkMaps::techMapping()
{
    _tech[TECH_NA] = "N/A";
    _tech[TECH_40] = "40nm";
    _tech[TECH_28] = "28nm";
    _tech[TECH_16] = "16nm";
    _tech[TECH_7] = "7nm";
    _tech[TECH_5] = "5nm";
}

void MlxlinkMaps::extComplianceMapping()
{
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_Unspecified] = "Unspecified";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC_FEC] =
      "100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR4] = "100GBASE-SR4 or 25GBASE-SR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_LR4] = "100GBASE-LR4 or 25GBASE-LR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_ER4] = "100GBASE-ER4 or 25GBASE-ER";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR10] = "100GBASE-SR10";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_CWDM4] = "100G CWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_PSM4] = "100G PSM4 Parallel SMF";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC_FEC] =
      "100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_CR4] =
      "100GBASE-CR4, 25GBASE-CR CA-25G-L or 50GBASE-CR2 with RS (Clause91) FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_S] =
      "25GBASE-CR CA-25G-S or 50GBASE-CR2 with BASE-R (Clause 74 Fire code) FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_N] =
      "25GBASE-CR CA-25G-N or 50GBASE-CR2 with no FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_40GBASE_ER4] = "40GBASE-ER4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_4_x_10GBASE_SR] = "4 x 10GBASE-SR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_40G_PSM4] = "40G PSM4 Parallel SMF";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1I1_2D1] =
      "G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1S1_2D2] =
      "G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1L1_2D2] =
      "G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_10GBASE_T] = "10GBASE-T with SFI electrical interface";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_CLR4] = "100G CLR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC] = "100G AOC or 25GAUI C2M AOC. No FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC] = "100G ACC or 25GAUI C2M ACC. No FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_DWDM2] =
      "100GE-DWDM2 (DWDM transceiver using 2 wavelengths on a 1550 nm"
      " DWDM grid with a reach up to 80 km)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_1550NM_WDM] = "100G 1550nm WDM (4 wavelengths)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_10GBASE_T] = "10GBASE-T Short Reach (30 meters)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_5GBASE_T] = "5GBASE-T";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_2_5GBASE_T] = "2.5GBASE-T";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_40G_SWDM4] = "40G SWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_SWDM4] = "100G SWDM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_PAM4] = "100G PAM4 BiDi";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM10_MSA] =
      "4WDM-10 MSA (10km version of 100G CWDM4 with same RS(528,514) "
      "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM20_MSA] =
      "4WDM-10 MSA (20km version of 100G CWDM4 with same RS(528,514) "
      "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_4WDM40_MSA] =
      "4WDM-10 MSA (40km version of 100G CWDM4 with same RS(528,514) "
      "FEC in host system)";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_DR] = "100GBASE-DR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_FR] = "100G-FR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100G_LR] = "100G-LR, with CAUI-4 without FEC";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_400GBASE_SR4] = "100GBASE-SR1, 200GBASE-SR2 or 400GBASE-SR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_FR1] = "100GBASE-FR1 or 400GBASE-DR4-2";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_LR1] = "100GBASE-LR1";

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
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_400GBASE_VR4] = "100GBASE-VR1, 200GBASE-VR2 or 400GBASE-VR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_400GBASE_CR4] = "100GBASE-CR1, 200GBASE-CR2 or 400GBASE-CR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_CR] = "50GBASE-CR, 100GBASE-CR2, or 200GBASE-CR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_SR] = "50GBASE-SR, 100GBASE-SR2, or 200GBASE-SR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_FR] = "50GBASE-FR or 200GBASE-DR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_FR4] = "200GBASE-FR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_1550NM_PSM4] = "200G 1550 nm PSM4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_LR] = "50GBASE-LR";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_LR4] = "200GBASE-LR4";
    _cableComplianceExt[EXT_ETHERNET_COMPLIABCE_CODE_400GBASE_DR4] = "400GBASE-DR4, 400GAUI-4 C2M";
}

void MlxlinkMaps::hostComplianceMapping()
{
    _cmisHostCompliance[CMIS_COMPLIANCE_UNSPECIFIED] = "Unspecified";
    _cmisHostCompliance[CMIS_COMPLIANCE_1000_BASE_CX] = "1000BASE-CX";
    _cmisHostCompliance[CMIS_COMPLIANCE_XAUI] = "XAUI";
    _cmisHostCompliance[CMIS_COMPLIANCE_XFI] = "XFI";
    _cmisHostCompliance[CMIS_COMPLIANCE_SFI] = "SFI";
    _cmisHostCompliance[CMIS_COMPLIANCE_25G_AUI] = "25GAUI";
    _cmisHostCompliance[CMIS_COMPLIANCE_XL_AUI] = "XLAUI";
    _cmisHostCompliance[CMIS_COMPLIANCE_XL_PPI] = "XLPPI";
    _cmisHostCompliance[CMIS_COMPLIANCE_L_AUI2] = "LAUI-2";
    _cmisHostCompliance[CMIS_COMPLIANCE_50G_AUI2] = "50GAUI-2";
    _cmisHostCompliance[CMIS_COMPLIANCE_50G_AUI1] = "50GAUI-1";
    _cmisHostCompliance[CMIS_COMPLIANCE_C_AUI4] = "CAUI-4";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_AUI4] = "100GAUI-4";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_AUI2] = "100GAUI-2";
    _cmisHostCompliance[CMIS_COMPLIANCE_200G_AUI8] = "200GAUI-8";
    _cmisHostCompliance[CMIS_COMPLIANCE_200G_AUI4] = "200GAUI-4";
    _cmisHostCompliance[CMIS_COMPLIANCE_400G_AUI16] = "400GAUI-16";
    _cmisHostCompliance[CMIS_COMPLIANCE_400G_AUI8] = "400GAUI-8";
    _cmisHostCompliance[CMIS_COMPLIANCE_10G_BASE_CX4] = "10GBASE-CX4";
    _cmisHostCompliance[CMIS_COMPLIANCE_25G_CR_L] = "25GBASE-CR CA-L";
    _cmisHostCompliance[CMIS_COMPLIANCE_25G_CR_S] = "25GBASE-CR CA-S";
    _cmisHostCompliance[CMIS_COMPLIANCE_25G_CR_N] = "25GBASE-CR CA-N";
    _cmisHostCompliance[CMIS_COMPLIANCE_40G_BASE_CR4] = "40GBASE-CR4";
    _cmisHostCompliance[CMIS_COMPLIANCE_50G_BASE_CR] = "50GBASE-CR";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_BASE_CR10] = "100GBASE-CR10";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_BASE_CR4] = "100GBASE-CR4";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_BASE_CR2] = "100GBASE-CR2";
    _cmisHostCompliance[CMIS_COMPLIANCE_200G_BASE_CR4] = "200GBASE-CR4";
    _cmisHostCompliance[CMIS_COMPLIANCE_400G_CR8] = "400G CR8";
    _cmisHostCompliance[CMIS_COMPLIANCE_1000_BASE_T] = "1000BASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_2_5G_BASE_T] = "2.5GBASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_5G_BASE_T] = "5GBASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_10G_BASE_T] = "10GBASE-dT";
    _cmisHostCompliance[CMIS_COMPLIANCE_25_BASE_T] = "25GBASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_40_BASE_T] = "40GBASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_50_BASE_T] = "50GBASE-T";
    _cmisHostCompliance[CMIS_COMPLIANCE_SDR] = "IB SDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_DDR] = "IB DDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_QDR] = "IB QDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_FDR] = "IB FDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_EDR] = "IB EDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_HDR] = "IB HDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_NDR] = "IB NDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_XDR] = "IB XDR";
    _cmisHostCompliance[CMIS_COMPLIANCE_100G_BASE_R1] = "100GBASE-CR1";
    _cmisHostCompliance[CMIS_COMPLIANCE_200G_BASE_R2] = "200GBASE-CR2";
    _cmisHostCompliance[CMIS_COMPLIANCE_400G_BASE_R4] = "400GBASE-CR4";
    _cmisHostCompliance[CMIS_COMPLIANCE_800G_BASE_R8] = "800G-ETC-CR8 or 800GBASE-CR8";
}

void MlxlinkMaps::mediaComplianceMapping()
{
    _mmfCompliance[CMIS_COMPLIANCE_UNSPECIFIED] = "Unspecified";
    _mmfCompliance[CMIS_COMPLIANCE_10G_BASE_SW] = "10GBASE-SW";
    _mmfCompliance[CMIS_COMPLIANCE_10G_BASE_SR] = "10GBASE-SR";
    _mmfCompliance[CMIS_COMPLIANCE_25G_BASE_SR] = "25GBASE-SR";
    _mmfCompliance[CMIS_COMPLIANCE_40G_BASE_SR4] = "40GBASE-SR4";
    _mmfCompliance[CMIS_COMPLIANCE_40G_SWDM4] = "40GE SWDM4";
    _mmfCompliance[CMIS_COMPLIANCE_40G_BIDI] = "40GE BiDi";
    _mmfCompliance[CMIS_COMPLIANCE_50G_BASE_SR] = "50GBASE-SR";
    _mmfCompliance[CMIS_COMPLIANCE_100G_BASE_SR10] = "100GBASE-SR10";
    _mmfCompliance[CMIS_COMPLIANCE_100G_BASE_SR4] = "100GBASE-SR4";
    _mmfCompliance[CMIS_COMPLIANCE_100G_SWDM4] = "100GE SWDM4";
    _mmfCompliance[CMIS_COMPLIANCE_100G_BIDI] = "100GE BiDi";
    _mmfCompliance[CMIS_COMPLIANCE_100G_SR2] = "100GBASE-SR2";
    _mmfCompliance[CMIS_COMPLIANCE_100G_SR] = "100G-SR";
    _mmfCompliance[CMIS_COMPLIANCE_200G_BASE_SR4] = "200GBASE-SR4";
    _mmfCompliance[CMIS_COMPLIANCE_400G_BASE_SR16] = "400GBASE-SR16";
    _mmfCompliance[CMIS_COMPLIANCE_400G_BASE_SR8] = "400G-SR8";
    _mmfCompliance[CMIS_COMPLIANCE_400G_SR4] = "400G-SR4";
    _mmfCompliance[CMIS_COMPLIANCE_800G_SR8] = "800G-SR8";
    _mmfCompliance[CMIS_COMPLIANCE_400G_BIDI] = "400GE BiDI";

    _smfCompliance[CMIS_COMPLIANCE_UNSPECIFIED] = "Unspecified";
    _smfCompliance[CMIS_COMPLIANCE_10G_BASE_LW] = "10GBASE-LW";
    _smfCompliance[CMIS_COMPLIANCE_10G_BASE_EW] = "10GBASE-EW";
    _smfCompliance[CMIS_COMPLIANCE_10G_ZW] = "10G-ZW";
    _smfCompliance[CMIS_COMPLIANCE_10G_BASE_LR] = "10GBASE-LR";
    _smfCompliance[CMIS_COMPLIANCE_10G_BASE_ER] = "10GBASE-ER";
    _smfCompliance[CMIS_COMPLIANCE_10G_BASE_ZR] = "10G-ZR";
    _smfCompliance[CMIS_COMPLIANCE_25G_BASE_LR] = "25GBASE-LR";
    _smfCompliance[CMIS_COMPLIANCE_25G_BASE_ER] = "25GBASE-ER";
    _smfCompliance[CMIS_COMPLIANCE_40G_BASE_LR4] = "40GBASE-LR4";
    _smfCompliance[CMIS_COMPLIANCE_40G_BASE_FR] = "40GBASE-FR";
    _smfCompliance[CMIS_COMPLIANCE_50G_BASE_FR] = "50GBASE-FR";
    _smfCompliance[CMIS_COMPLIANCE_50G_BASE_LR] = "50GBASE-LR";
    _smfCompliance[CMIS_COMPLIANCE_100G_BASE_LR4] = "100GBASE-LR4";
    _smfCompliance[CMIS_COMPLIANCE_100G_BASE_ER4] = "100GBASE-ER4";
    _smfCompliance[CMIS_COMPLIANCE_100G_PSM4] = "100G PSM4";
    _smfCompliance[CMIS_COMPLIANCE_100G_CWDM4_OCP] = "100G CWDM4-OCP";
    _smfCompliance[CMIS_COMPLIANCE_100G_CWDM4] = "100G CWDM4";
    _smfCompliance[CMIS_COMPLIANCE_100G_4WDM_10] = "100G 4WDM-10";
    _smfCompliance[CMIS_COMPLIANCE_100G_4WDM_20] = "100G 4WDM-20";
    _smfCompliance[CMIS_COMPLIANCE_100G_4WDM_40] = "100G 4WDM-40";
    _smfCompliance[CMIS_COMPLIANCE_100G_BASE_DR] = "100GBASE-DR";
    _smfCompliance[CMIS_COMPLIANCE_100G_FR] = "100G-FR";
    _smfCompliance[CMIS_COMPLIANCE_100G_LR] = "100G-LR";
    _smfCompliance[CMIS_COMPLIANCE_200G_BASE_DR4] = "200GBASE-DR4";
    _smfCompliance[CMIS_COMPLIANCE_200G_BASE_FR4] = "200GBASE-FR4";
    _smfCompliance[CMIS_COMPLIANCE_200G_BASE_LR4] = "200GBASE-LR4";
    _smfCompliance[CMIS_COMPLIANCE_400G_BASE_FR8] = "400GBASE-FR8";
    _smfCompliance[CMIS_COMPLIANCE_400G_BASE_LR8] = "400GBASE-LR8";
    _smfCompliance[CMIS_COMPLIANCE_400G_BASE_DR4] = "400GBASE-DR4";
    _smfCompliance[CMIS_COMPLIANCE_400G_FR4] = "400G-FR4";
    _smfCompliance[CMIS_COMPLIANCE_400G_LR4] = "400G-LR4";
    _smfCompliance[CMIS_COMPLIANCE_10G_SR] = "10G-SR";
    _smfCompliance[CMIS_COMPLIANCE_10G_LR] = "10G-LR";
    _smfCompliance[CMIS_COMPLIANCE_25G_SR] = "25G-SR";
    _smfCompliance[CMIS_COMPLIANCE_25G_LR] = "25G-LR";
    _smfCompliance[CMIS_COMPLIANCE_10G_LR_BIDI] = "10G-LR-BiDi";
    _smfCompliance[CMIS_COMPLIANCE_25G_LR_BIDI] = "25G-LR-BiDi";
}

void MlxlinkMaps::activeComplianceMapping()
{
    _activeCableCompliance[0] = "Undefined";
    _activeCableCompliance[1] = "Active Cable assembly with BER < 10-12";
    _activeCableCompliance[2] = "Active Cable assembly with BER < 5x10-5";
    _activeCableCompliance[3] = "Active Cable assembly with BER < 2.6x10-4";
    _activeCableCompliance[4] = "Active Cable assembly with BER < 10-6";
}

void MlxlinkMaps::pcieEnumMapping()
{
    _pcieErrType[PCIE_ERR_TYPE_ABORT] = PcieErrType{"ABORT", 0, 0, 0, false, false, false, false, false, false, ""};
    _pcieErrType[PCIE_ERR_TYPE_BAD_DLLP_LCRC] = PcieErrType{
      "BAD_DLLP_LCRC", 100000, 1, PCIE_MAX_DURATION_HW_COUNTERS, true, false, false, false, false, false, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_BAD_TLP_LCRC] = PcieErrType{
      "BAD_TLP_LCRC", 100000, 1, PCIE_MAX_DURATION_HW_COUNTERS, true, true, false, false, false, false, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_BAD_TLP_ECRC] = PcieErrType{
      "BAD_TLP_ECRC", 100000, 1, PCIE_MAX_DURATION_HW_COUNTERS, true, true, false, false, false, false, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_ERR_MSG] =
      PcieErrType{"ERR_MSG", 0, 1, PCIE_MAX_DURATION, true, true, false, false, false, false, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_MALFORMED_TLP] =
      PcieErrType{"MALFORMED_TLP", 0, 1, PCIE_MAX_DURATION, true, false, false, false, false, true, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_POISONED_TLP] =
      PcieErrType{"POISONED_TLP", 0, 1, PCIE_MAX_DURATION, true, true, false, false, false, true, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_UNEXPECTED_CPL] =
      PcieErrType{"UNEXPECTED_CPL", 0, 1, PCIE_MAX_DURATION, true, true, true, true, false, true, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_ACS_VIOLATION] =
      PcieErrType{"ACS_VIOLATION", 0, 1, PCIE_MAX_DURATION, true, false, false, false, false, false, "Packet"};
    _pcieErrType[PCIE_ERR_TYPE_SURP_LINK_DOWN] =
      PcieErrType{"SURPRISE_LINK_DOWN", 100000, 1, PCIE_MAX_DURATION, true, true, false, false, false, false, "usec"};
    _pcieErrType[PCIE_ERR_TYPE_RECEIVER_ERROR] =
      PcieErrType{"RECEIVER_ERROR", 100000, 0, PCIE_MAX_DURATION, true, false, false, false, false, false, "usec"};
}

void MlxlinkMaps::initCableComplianceMapping()
{
    qsfpComlianceMapping();
    sfpComplianceMapping();
    extComplianceMapping();
    hostComplianceMapping();
    mediaComplianceMapping();
    activeComplianceMapping();
    cmisIbComlianceMapping();
    cimsCableBreakoutMapping();
    qsfpFarEndCableBreakoutMapping();
    rxTxCdrCapMapping();
    cmisModuleStMapping();
    rxPowerTypeMapping();
    maxReadReqSizeMapping();
    pwrStatusMapping();
    portTypeMapping();
    linkPeerMaxSpeedMapping();
    portStateMapping();
    tempFlagsMapping();
    vccFlagsMapping();
    dataPathStateMapping();
    errorCodeResMapping();
    techMapping();
    modulePrbsMapping();
    pcieEnumMapping();
}

void MlxlinkMaps::initCableTechnologyMapping()
{
    _cableTechnologyQsfp[TECHNOLOGY_850NM_VCSEL] = "850 nm VCSEL";
    _cableTechnologyQsfp[TECHNOLOGY_1310NM_VCSEL] = "1310 nm VCSEL";
    _cableTechnologyQsfp[TECHNOLOGY_1550NM_VCSEL] = "1550 nm VCSEL";
    _cableTechnologyQsfp[TECHNOLOGY_1310NM_FP] = "1310 nm FP laser";
    _cableTechnologyQsfp[TECHNOLOGY_1310NM_DFB] = "1310 nm DFB laser";
    _cableTechnologyQsfp[TECHNOLOGY_1550NM_DFB] = "1550 nm DFB laser";
    _cableTechnologyQsfp[TECHNOLOGY_1310NM_EML] = "1310 nm EML";
    _cableTechnologyQsfp[TECHNOLOGY_1550NM_EML] = "1550 nm EML";
    _cableTechnologyQsfp[TECHNOLOGY_OTHERS] = "Other / Undefined";
    _cableTechnologyQsfp[TECHNOLOGY_1490NM_DFB] = "1490 nm DFB laser";
    _cableTechnologyQsfp[TECHNOLOGY_COP_UNEQ] = "Copper cable, passive, unequalized";
    _cableTechnologyQsfp[TECHNOLOGY_COP_PASV] = "Copper cable, passive, equalized";
    _cableTechnologyQsfp[TECHNOLOGY_COP_NEAR_FAR_END] = "Copper cable with near and far end limiting active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_COP_FAR_END] = "Copper cable with far end limiting active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_COP_NEAR_END] = "Copper cable with near end limiting active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_COP_LINEAR] = "Copper cable with linear active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_LASER_C_BAND] = "C-band tunable laser";
    _cableTechnologyQsfp[TECHNOLOGY_LASER_L_BAND] = "B-band tunable laser";
    _cableTechnologyQsfp[TECHNOLOGY_COP_LINEAR_NEAR_FAR_END] =
      "Copper cable with near end and far end linear active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_COP_LINEAR_FAR_END] = "Copper cable with far end linear active equalizers";
    _cableTechnologyQsfp[TECHNOLOGY_COP_LINEAR_NEAR_END] = "Copper cable with near end linear active equalizers";

    _cableTechnologySfp[0] = "N/A";
    _cableTechnologySfp[4] = "Passive";
    _cableTechnologySfp[8] = "Active";
}

void MlxlinkMaps::initCablePowerClassMapping()
{
    _sfpQsfpPowerClass[POWER_CLASS0] = "1.0 W max";
    _sfpQsfpPowerClass[POWER_CLASS1] = "1.5 W max";
    _sfpQsfpPowerClass[POWER_CLASS2] = "2.0 W max";
    _sfpQsfpPowerClass[POWER_CLASS3] = "2.5 W max";
    _sfpQsfpPowerClass[POWER_CLASS4] = "3.5 W max";
    _sfpQsfpPowerClass[POWER_CLASS5] = "4.0 W max";
    _sfpQsfpPowerClass[POWER_CLASS6] = "4.5 W max";
    _sfpQsfpPowerClass[POWER_CLASS7] = "5.0 W max";
    _sfpQsfpPowerClass[POWER_CLASS8] = "> 5.0 W max";

    _sfpddPowerClass[POWER_CLASS0] = "0.5 W max";
    _sfpddPowerClass[POWER_CLASS1] = "1.0 W max";
    _sfpddPowerClass[POWER_CLASS2] = "1.5 W max";
    _sfpddPowerClass[POWER_CLASS3] = "2.0 W max";
    _sfpddPowerClass[POWER_CLASS4] = "3.5 W max";
    _sfpddPowerClass[POWER_CLASS5] = "5.0 W max";
    _sfpddPowerClass[POWER_CLASS8] = "> 5.0 W max";

    _qsfpddOsfpPowerClass[POWER_CLASS1] = "1.5 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS2] = "3.5 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS3] = "7.0 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS4] = "8.0 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS5] = "10 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS6] = "12 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS7] = "14 W max";
    _qsfpddOsfpPowerClass[POWER_CLASS8] = "> 14 W max";

    _qsfpddPowerClassToValue[POWER_CLASS1] = 1.5;
    _qsfpddPowerClassToValue[POWER_CLASS2] = 3.5;
    _qsfpddPowerClassToValue[POWER_CLASS3] = 7.0;
    _qsfpddPowerClassToValue[POWER_CLASS4] = 8;
    _qsfpddPowerClassToValue[POWER_CLASS5] = 10;
    _qsfpddPowerClassToValue[POWER_CLASS6] = 12;
    _qsfpddPowerClassToValue[POWER_CLASS7] = 14;

    _sfpddPowerClassToValue[POWER_CLASS0] = 0.5;
    _sfpddPowerClassToValue[POWER_CLASS1] = 1.0;
    _sfpddPowerClassToValue[POWER_CLASS2] = 1.5;
    _sfpddPowerClassToValue[POWER_CLASS3] = 2.0;
    _sfpddPowerClassToValue[POWER_CLASS4] = 3.5;
    _sfpddPowerClassToValue[POWER_CLASS5] = 5.0;
}

void MlxlinkMaps::initEnhancedDebugMapping()
{
    _downBlame[DOWN_BLAME_UNKOWN] = "Unknown";
    _downBlame[DOWN_BLAME_LOCAL_PHY] = "Local_phy";
    _downBlame[DOWN_BLAME_REMOTE_PHY] = "Remote_phy";

    _localReasonOpcode[LOCAL_REASON_OPCODE_NO_LINK_DOWN_INDICAION] = "No_link_down_indication";
    _localReasonOpcode[LOCAL_REASON_OPCODE_UNKWON_REASON] = "Unknown_reason";
    _localReasonOpcode[LOCAL_REASON_OPCODE_HI_BER] = "Hi_BER";
    _localReasonOpcode[LOCAL_REASON_OPCODE_BLOCK_LOCK_LOSS] = "Block_Lock_loss";
    _localReasonOpcode[LOCAL_REASON_OPCODE_ALIGNMENT_LOSS] = "Alignment_loss";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FEC_SYNC_LOSS] = "FEC_sync_loss";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PLL_LOCK_LOSS] = "PLL_lock_loss";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FIFO_OVERFLOW] = "FIFO_overflow";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FALSE_SKIP_CONDITION] = "false_SKIP_condition";
    _localReasonOpcode[LOCAL_REASON_OPCODE_MINOR_ERROR_THRESHOLD_EXCEEDED] = "Minor_Error_threshold_exceeded";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PHYSICAL_LAYER_RETRANSMISSION_TIMEOUT] =
      "Physical_layer_retransmission_timeout";
    _localReasonOpcode[LOCAL_REASON_OPCODE_HEARTBEAT_ERRORS] = "Heartbeat_errors";
    _localReasonOpcode[LOCAL_REASON_OPCODE_LINK_LAYER_CREDIT_MONITORING_WATCHDOG] =
      "Link_Layer_credit_monitoring_watchdog";
    _localReasonOpcode[LOCAL_REASON_OPCODE_LINK_LAYER_INTEGRITY_THRESHOLD_EXCEEDED] =
      "Link_Layer_integrity_threshold_exceeded";
    _localReasonOpcode[LOCAL_REASON_OPCODE_LINK_LAYER_BUFFER_OVERRUN] = "Link_Layer_buffer_overrun";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_OUTBAND_COMMAND_WITH_HEALTHY_LINK] =
      "Down_by_outband_command_with_healthy_link";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_OUTBAND_COMMAND_FOR_LINK_WITH_HI_BER] =
      "Down_by_outband_command_for_link_with_hi_ber";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_INBAND_COMMAND_WITH_HEALTHY_LINK] =
      "Down_by_inband_command_with_healthy_link";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_INBAND_COMMAND_FOR_LINK_WITH_HI_BER] =
      "Down_by_inband_command_for_link_with_hi_ber";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_VERIFICATION_GW] = "Down_by_verification_GW";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RECEIVED_REMOTE_FAULT] = "Received_Remote_Fault";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RECEIVED_TS1] = "Received_TS1";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_MANAGEMENT_COMMAND] = "Down_by_management_command";
    _localReasonOpcode[LOCAL_REASON_OPCODE_CABLE_WAS_UNPLUGGED] = "Cable_was_unplugged";
    _localReasonOpcode[LOCAL_REASON_OPCODE_CABLE_ACCESS_ISSUE] = "Cable_access_issue";
    _localReasonOpcode[LOCAL_REASON_OPCODE_THERMAL_SHUTDOWN] = "Thermal_shutdown";
    _localReasonOpcode[LOCAL_REASON_OPCODE_CURRENT_ISSUE] = "Current_issue";
    _localReasonOpcode[LOCAL_REASON_OPCODE_POWER_BUDGET] = "Power_budget";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FAST_RECOVERY_EFFECTIVE_BER] = "Fast_recovery_raw_ber";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FAST_RECOVERY_EFFECTIVE_BER] = "Fast_recovery_effective_ber";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FAST_RECOVERY_SYMBOL_BER] = "Fast_recovery_symbol_ber";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FAST_RECOVERY_CREDIT_WATCHDOG] = "Fast_recovery_credit_watchdog";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_TO_SLEEP_STATE] = "Peer_side_down_to_sleep_state";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_TO_DISABLE_STATE] = "Peer_side_down_to_disable_state";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_TO_DISABLE_AND_PORT_LOCK] =
      "Peer_side_down_to_disable_and_port_lock";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_DUE_TO_THERMAL_EVENT] = "Peer_side_down_due_to_thermal_event";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_DUE_TO_FORCE_EVENT] = "Peer_side_down_due_to_force_event";
    _localReasonOpcode[LOCAL_REASON_OPCODE_PEER_SIDE_DOWN_DUE_TO_RESET_EVENT] = "Peer_side_down_due_to_reset_event";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RESET_NO_POWER_CYCLE] = "Reset_no_power_cycle";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FAST_RECOVERY_TX_PLR_TRIGGER] = "Fast_recovery_tx_plr_trigger";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_DUE_TO_HW_FORCE_EVENT] = "Down_due_to_hw_force_event";
    _localReasonOpcode[LOCAL_REASON_OPCODE_L1_EXIT_FAILURE] = "L1_exit_failure";
    _localReasonOpcode[LOCAL_REASON_OPCODE_TOO_MANY_LINK_ERROR_RECOVERIES] = "Too_many_link_error_recoveries";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_DUE_TO_CONTAIN_MODE] = "Down_due_to_contain_mode";
    _localReasonOpcode[LOCAL_REASON_OPCODE_BW_LOSS_THRESHOLD_EXCEEDED] = "BW_loss_threshold_exceeded";
    _localReasonOpcode[LOCAL_REASON_OPCODE_ELS_LASER_FAULT] = "ELS_laser_fault";
    _localReasonOpcode[LOCAL_REASON_OPCODE_HI_SER] = "Hi_SER";
    _localReasonOpcode[LOCAL_REASON_OPCODE_DOWN_BY_NMX_ADMINSTATE_CMD] = "Down_by_nmx_adminstate_cmd";
    _localReasonOpcode[LOCAL_REASON_OPCODE_FLUA_BER_BELOW_THRESHOLD_IN_GUARD_TIME] =
      "FLUA_BER_below_threshold_in_guard_time";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RECEIVED_LOCAL_FAULT] = "Received_local_fault";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RECEIVED_LINK_INTERRUPTION] = "Received_link_interruption";
    _localReasonOpcode[LOCAL_REASON_OPCODE_MANUAL_DEBUG_MODE] = "Manual_debug_mode";
    _localReasonOpcode[LOCAL_REASON_OPCODE_RESERVED] = "N/A";
}

void MlxlinkMaps::initPprmOperationRecoveryMapping()
{
    _pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_LOG] = "host_logic_re_lock";
    _pprmOperRecovery[PPRM_OPERATION_RECOVERY_HOST_SERDES] = "host_serdes_feq";
    _pprmOperRecovery[PPRM_OPERATION_RECOVERY_MODULE_TX] = "module_tx_disable";
    _pprmOperRecovery[PPRM_OPERATION_RECOVERY_MODULE_DATA_PATH] = "module_datapath_full_toggle";
}

void MlxlinkMaps::initPprmRecoveryStatusMapping()
{
    // Relevant for "host_logic_re_lock", "host_serdes_feq", "module_tx_disable", "module_datapath_full_toggle"
    _pprmRecoveryStatus[PPRM_RECOVERY_STATUS_FW_DEFAULT] = "FW Default";
    _pprmRecoveryStatus[PPRM_RECOVERY_STATUS_ENABLE] = "Enable";
    _pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE] = "Disable";
    _pprmRecoveryStatus[PPRM_RECOVERY_STATUS_DISABLE_SUPPORT_IN_NEGOTIATION] = "Disable Support In Negotiation";
}

void MlxlinkMaps::initPpcntGroupsMapping()
{
    _ppcntGroups[PPCNT_IEEE_802_3_COUNTERS_GROUP] = PPCNT_IEEE_802_3_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_RFC_2863_GROUP] = PPCNT_RFC_2863_GROUP;
    _ppcntGroups[PPCNT_RFC_2819_GROUP] = PPCNT_RFC_2819_GROUP;
    _ppcntGroups[PPCNT_RFC_3635_GROUP] = PPCNT_RFC_3635_GROUP;
    _ppcntGroups[PPCNT_ETHERNET_EXTENDED_GROUP] = PPCNT_ETHERNET_EXTENDED_GROUP;
    _ppcntGroups[PPCNT_DISC_COUNTERS_GROUP] = PPCNT_DISC_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_PER_PRIORITY_COUNTERS_GROUP] = PPCNT_PER_PRIORITY_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_PER_TRAFFIC_CLASS_COUNTERS_GROUP] = PPCNT_PER_TRAFFIC_CLASS_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_PHY_GROUP] = PPCNT_PHY_GROUP;
    _ppcntGroups[PPCNT_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_GROUP] = PPCNT_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_STATISTICAL_GROUP] = PPCNT_STATISTICAL_GROUP;
    _ppcntGroups[PPCNT_IB_PORT_COUNTERS_GROUP] = PPCNT_IB_PORT_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_EXT_IB_PORT_COUNTERS_GROUP] = PPCNT_EXT_IB_PORT_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_PLR_GROUP] = PPCNT_PLR_GROUP;
    _ppcntGroups[PPCNT_HISTOGRAM_GROUP] = PPCNT_HISTOGRAM_GROUP;
    _ppcntGroups[PPCNT_IB_PKTS_GROUP] = PPCNT_IB_PKTS_GROUP;
    _ppcntGroups[PPCNT_IB_GEN_COUNTERS_GROUP] = PPCNT_IB_GEN_COUNTERS_GROUP;
    _ppcntGroups[PPCNT_ALL_GROUPS] = PPCNT_ALL_GROUPS;
}

void MlxlinkMaps::initCableTypeForTableView()
{
    _cableTypeForTableDisplay[UNIDENTIFIED] = "UNIDENT";
    _cableTypeForTableDisplay[ACTIVE] = "AOC/ACC";
    _cableTypeForTableDisplay[OPTICAL_MODULE] = "AOM";
    _cableTypeForTableDisplay[PASSIVE] = "DAC";
    _cableTypeForTableDisplay[UNPLUGGED] = "UNPLUGD";
    _cableTypeForTableDisplay[TWISTED_PAIR] = "TP";
    _cableTypeForTableDisplay[CPO] = "CPO";
    _cableTypeForTableDisplay[OE] = "OE";
    _cableTypeForTableDisplay[ELS] = "ELS";
}

void MlxlinkMaps::initTableHeaders()
{
    _multiPortInfoTableHeader = {{"Port", SHIFT_8},
                                 {"State", SHIFT_8},
                                 {"Speed", SHIFT_8},
                                 {"FEC", SHIFT_15},
                                 {"Cable Type/LEN", SHIFT_20},
                                 {"TTLU", SHIFT_15},
                                 {"Time Since Clear/CL", SHIFT_20},
                                 {"FOM", SHIFT_20},
                                 {"Net BER", SHIFT_20},
                                 {"Link Down", SHIFT_10},
                                 {"F. C. Zero Hist", SHIFT_20}};

    // Need to add here localPort string, done when used in mlxlinkCommander
    _multiPortModuleInfoTableHeader = {{"Cable S/N", SHIFT_15},  {"Cable P/N", SHIFT_20}, {"Cable Len", SHIFT_15},
                                       {"Cable Type", SHIFT_15}, {"State", SHIFT_15},     {"Speed", SHIFT_8},
                                       {"FEC", SHIFT_15},        {"Net BER", SHIFT_20}};

    _bkvGroupsTableHeader = {{"Group #", SHIFT_10}, {"Supported Entries", SHIFT_20}, {"Filled Indication", SHIFT_20}};

    _bkvGroupEntriesTableHeader = {
      {"Entry ID", SHIFT_10}, {"Address", SHIFT_15}, {"WData", SHIFT_15}, {"WMask", SHIFT_15}};
}

void MlxlinkMaps::initPlrRejectModeMapping()
{
    _plrRejectMode[PLR_REJECT_MODE_PLR_MARGIN] = "rejection based on PLR margin";
    _plrRejectMode[PLR_REJECT_MODE_CRC_AND_CS] = "rejection based on CRC and CS";
    _plrRejectMode[PLR_REJECT_MODE_CS] = "rejection based on CS";
}

void MlxlinkMaps::initKrMapping()
{
    // According to arch - the enums here are based on "xdr_lt_cap" instead of kr_ext_cap.
    _krExtOper[KR_EXT_OPER_LT_DISABLED] = "LT is Disabled";
    _krExtOper[KR_EXT_OPER_LT_ENABLED_REGULAR_KR] = "LT Enabled Regular KR";
    _krExtOper[KR_EXT_OPER_LT_ENABLED_EXT_KR_ASYNC] = "LT Enabled Ext KR Async Mode";

    _krPrbsType[KR_PRBS_TYPE_PRBS13] = "PRBS13";
    _krPrbsType[KR_PRBS_TYPE_PRBS31] = "PRBS31";
}

MlxlinkMaps::MlxlinkMaps()
{
    initPublicStrings();
    initPortStateMapping();
    initFecAndLoopbackMapping();
    initPortSpeedMapping();
    initPrbsMapping();
    initPpbmcAndPepcMapping();
    initLinkDownInfoMapping();
    initLinkUpInfo();
    initSltpStatusMapping();
    initPSCDRateMaskMapping();
    initPSCDRoleMaskMapping();
    initPSCDModeBRoleMaskMapping();
    initCableComplianceMapping();
    initCableTechnologyMapping();
    initCableTypeForTableView();
    initCablePowerClassMapping();
    initEnhancedDebugMapping();
    phyHstFsmHdrStateMapping();
    initPpttParamsMapping();
    initPpttSpeedMapping();
    initPpcntGroupsMapping();
    initTableHeaders();
    initPlrRejectModeMapping();
    initKrMapping();
    initPprmOperationRecoveryMapping();
    initPprmRecoveryStatusMapping();
}

MlxlinkMaps::~MlxlinkMaps() {}
