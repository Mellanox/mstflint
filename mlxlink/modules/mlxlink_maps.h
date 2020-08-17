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

#ifndef MLXLINK_MAPS_H
#define MLXLINK_MAPS_H

#include <errno.h>
#include <cstdio>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <mlxreg/mlxreg_lib.h>
#include <mlxreg/mlxreg_parser.h>
#include "mlxlink_user_input.h"
#include "printutil/mlxlink_cmd_print.h"

typedef enum {
    NO, UP, DN, TG
} PAOS_CMD;

enum CABLE_TYPE {
    UNIDENTIFIED, ACTIVE, OPTICAL_MODULE, PASSIVE, UNPLUGGED
};

enum PCIE_LINK_SPEED {
    GEN1 = 1, GEN2 = 2, GEN3 = 4, GEN4 = 16,
};

enum POWER_CLASS {
    POWER_CLASS0,
    POWER_CLASS1,
    POWER_CLASS2,
    POWER_CLASS3,
    POWER_CLASS4,
    POWER_CLASS5,
    POWER_CLASS6,
    POWER_CLASS7,
    POWER_CLASS8
};

enum PRBS_MODES {
    PRBS_TX,
    PRBS_RX
};
enum PRBS_TX_MODE {
    SQUARE_WAVEA = 13,
    SQUARE_WAVEB,
    SQUARE_WAVEC,
    SQUARE_WAVED
};

enum PRBS_RX_MODE {
    SQUARE_WAVE = 13
};

enum PRBS_RX_TX_MODE {
    PRBS31,
    PRBS23A,
    PRBS23B,
    PRBS23C,
    PRBS23D,
    PRBS7,
    PRBS11,
    PRBS11A,
    PRBS11B,
    PRBS11C,
    PRBS11D,
    PRBS9,
    IDLE,
    PRBS13A = 17,
    PRBS13B,
    PRBS13C,
    PRBS13D,
    SSPR,
    SSPRQ
};

enum PRBS_CAP {
    PRBS31_CAP = 0x1,
    PRBS23A_CAP = 0x2,
    PRBS23B_CAP = 0x4,
    PRBS23C_CAP = 0x8,
    PRBS23D_CAP = 0x10,
    PRBS7_CAP = 0x20,
    PRBS11_CAP = 0x40,
    PRBS11A_CAP = 0x80,
    PRBS11B_CAP = 0x100,
    PRBS11C_CAP = 0x200,
    PRBS11D_CAP = 0x400,
    PRBS9_CAP = 0x800,
    PRBSIDLE_CAP = 0x1000,
    SQUARE_WAVEA_CAP = 0x2000,
    SQUARE_WAVEB_CAP = 0x4000,
    SQUARE_WAVEC_CAP = 0x8000,
    SQUARE_WAVED_CAP = 0x10000,
    PRBS13A_CAP = 0x20000,
    PRBS13B_CAP = 0x40000,
    PRBS13C_CAP = 0x80000,
    PRBS13D_CAP = 0x100000,
    SSPR_CAP = 0x200000,
    SSPRQ_CAP = 0x400000
};

enum LANE_RATE_CAP {
    LANE_RATE_1G_CAP    = 0x1,
    LANE_RATE_SDR_CAP   = 0x2,
    LANE_RATE_XAUI_CAP  = 0x4,
    LANE_RATE_DDR_CAP   = 0x8,
    LANE_RATE_QDR_CAP   = 0x10,
    LANE_RATE_FDR10_CAP = 0x20,
    LANE_RATE_FDR_CAP   = 0x40,
    LANE_RATE_EDR_CAP   = 0x80,
    LANE_RATE_50G_CAP   = 0x100,
    LANE_RATE_HDR_CAP   = 0x200,
};

enum PRBS_LANE_RATE {
    PRBS_SDR,
    PRBS_DDR,
    PRBS_QDR,
    PRBS_FDR10,
    PRBS_FDR,
    PRBS_EDR,
    PRBS_HDR,
    PRBS_1G = 10,
    PRBS_XAUI = 11,
    PRBS_50G = 12
};

enum PRBS_TUNING_STATUS {
    PRBS_TUNING_NOT_PERFORMED,
    PRBS_TUNING_PERFORMING,
    PRBS_TUNING_COMPLETE
};

enum FEC_MODE {
    NO_FEC = 1, FC_FEC = 2, RS_FEC = 4
};

enum FEC_REQUSET {
    FEC_REQUSET_NF = 0x1,
    FEC_REQUSET_FC = 0x2,
    FEC_REQUSET_RS528 = 0x4,
    FEC_REQUSET_RS271 = 0x8,
    FEC_REQUSET_RS277 = 0x10,
    FEC_REQUSET_RS163 = 0x20,
    FEC_REQUSET_ZLF = 0x40,
};

enum FECMode {
    FEC_MODE_NO_FEC = 0,
    FEC_MODE_FIRECODE_FEC = 1,
    FEC_MODE_STANDARD_RS_FEC_528_514 = 2,
    FEC_MODE_STANDARD_LL_FEC_271_257 = 3,
    FEC_MODE_MELLANOX_STRONG_FEC = 4,
    FEC_MODE_MELLANOX_LL_FEC = 5,
    FEC_MODE_STANDARD_RS_FEC_544_514 = 7,
    FEC_MODE_ZERO_LATENCY_FEC = 8,
    FEC_MODE_RS_FEC_272 = 9,
    FEC_MODE_RS_FEC_544_514_PLR = 12,
    FEC_MODE_RS_FEC_271_257_PLR = 13,
    //please add enums before this line
    FEC_MODE_END,
};

enum CABLE_IDENTIFIER {
    IDENTIFIER_QSFP28,
    IDENTIFIER_QSFP_PLUS,
    IDENTIFIER_SFP,
    IDENTIFIER_QSA,
    IDENTIFIER_BACKPLANE,
    IDENTIFIER_SFP_DD,
    IDENTIFIER_QSFP_DD,
    IDENTIFIER_QSFP_CMIS,
    IDENTIFIER_OSFP
};

enum CABLE_TECHNOLOGY {
    TECHNOLOGY_850NM_VCSEL = 0x0,
    TECHNOLOGY_1310NM_VCSEL,
    TECHNOLOGY_1550NM_VCSEL,
    TECHNOLOGY_1310NM_FP,
    TECHNOLOGY_1310NM_DFB,
    TECHNOLOGY_1550NM_DFB,
    TECHNOLOGY_1310NM_EML,
    TECHNOLOGY_1550NM_EML,
    TECHNOLOGY_OTHERS,
    TECHNOLOGY_1490NM_DFB,
    TECHNOLOGY_COP_UNEQ,
    TECHNOLOGY_COP_PASV,
    TECHNOLOGY_COP_NEAR_FAR_END,
    TECHNOLOGY_COP_FAR_END,
    TECHNOLOGY_COP_NEAR_END,
    TECHNOLOGY_COP_LINEAR
};

enum OUI {
    OTHER, MELLANOX, KNOWN_OUI
};

enum ProtoActive {
    IB = 1, ETH = 4
};
enum BAD_SET_STATUS_40_28NM {
    SET_STATUS_INVALID_PARM = 0,
    SET_STATUS_ILLEGAL_OB_BAIS = 0x1,
    SET_STATUS_ILLEGAL_OB_TAPS_POLARITY = 0x2,
    SET_STATUS_UNKNOWN
};

enum BAD_SET_STATUS_16NM {
    SET_STATUS16_INVALID_PARM = 0x1,
    SET_STATUS16_ILLEGAL_M2LP_AMP = 0x800,
    SET_STATUS16_ILLEGAL_M2LP = 0x1000,
    SET_STATUS16_ILLEGAL_AMP = 0x2000,
    SET_STATUS16_ILLEGAL_ALEV_OUT = 0x4000,
    SET_STATUS16_ILLEGAL_TAPS = 0x8000,
    SET_STATUS16_UNKNOWN
};

enum EXT_ETHERNET_COMPLIANCE_CODE {
    EXT_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC_FEC = 0x1,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR4 = 0x2,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_LR4 = 0x3,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_ER4 = 0x4,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR10 = 0x5,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_CWDM4 = 0x6,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_PSM4 = 0x7,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC_FEC = 0x8,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_CR4 = 0xB,
    EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_S = 0xC,
    EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_N = 0xD,
    EXT_ETHERNET_COMPLIANCE_CODE_40GBASE_ER4 = 0x10,
    EXT_ETHERNET_COMPLIANCE_CODE_4_x_10GBASE_SR = 0x11,
    EXT_ETHERNET_COMPLIANCE_CODE_40G_PSM4 = 0x12,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1I1_2D1 = 0x13,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1S1_2D2 = 0x14,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1L1_2D2 = 0x15,
    EXT_ETHERNET_COMPLIANCE_CODE_10GBASE_T = 0x16,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_CLR4 = 0x17,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC = 0x18,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC = 0x19,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_DWDM2 = 0X1A,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_1550NM_WDM = 0X1B,
    EXT_ETHERNET_COMPLIABCE_CODE_10GBASE_T = 0X1C,
    EXT_ETHERNET_COMPLIABCE_CODE_5GBASE_T = 0X1D,
    EXT_ETHERNET_COMPLIABCE_CODE_2_5GBASE_T = 0X1E,
    EXT_ETHERNET_COMPLIABCE_CODE_40G_SWDM4 = 0X1F,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_SWDM4 = 0X20,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_PAM4 = 0X21,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM10_MSA = 0X22,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM20_MSA = 0X23,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM40_MSA = 0X24,
    EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_DR = 0X25,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_FR = 0X26,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_LR = 0X27,
    EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_6 = 0X30,
    EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_6 = 0X31,
    EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_4 = 0X32,
    EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_4 = 0X33,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_CR = 0X40,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_SR = 0X41,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_FR  = 0X42,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_FR4 = 0X43,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_1550NM_PSM4 = 0X44,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_LR = 0X45,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_LR4 = 0X46,
};

enum QSFP_ETHERNET_COMPLIANCE_CODE {
    QSFP_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    QSFP_ETHERNET_COMPLIANCE_CODE_40G_ACTIVE_CABLE_XLPPI = 0x1,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_LR4 = 0x2,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_SR4 = 0x4,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_CR4 = 0x8,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_SR = 0x10,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LR = 0x20,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LRM= 0x40,
    QSFP_ETHERNET_COMPLIANCE_CODE_EXT = 0x80,
};

enum SFP_ETHERNET_COMPLIANCE_CODE {
    SFP_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_SR = 0x10,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LR = 0x20,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LRM = 0x40,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_ER = 0x80,
};

enum CMIS_PASSIVE_COPPER_COMPLIANCE {
    CMIS_COMPLIANCE_UNSPECIFIED = 0x0,
    CMIS_COMPLIANCE_1000_BASE_CX= 0x1,
    CMIS_COMPLIANCE_XAUI = 0x2,
    CMIS_COMPLIANCE_XFI= 0x3,
    CMIS_COMPLIANCE_SFI = 0x4,
    CMIS_COMPLIANCE_25G_AUI = 0x5,
    CMIS_COMPLIANCE_XL_AUI = 0x6,
    CMIS_COMPLIANCE_XL_PPI = 0x7,
    CMIS_COMPLIANCE_L_AUI2= 0x8,
    CMIS_COMPLIANCE_50G_AUI2 = 0x9,
    CMIS_COMPLIANCE_50G_AUI1 = 0xa,
    CMIS_COMPLIANCE_C_AUI4 = 0xb,
    CMIS_COMPLIANCE_100G_AUI4 = 0xc,
    CMIS_COMPLIANCE_100G_AUI2 = 0xd,
    CMIS_COMPLIANCE_200G_AUI8 = 0xe,
    CMIS_COMPLIANCE_200G_AUI4 = 0xf,
    CMIS_COMPLIANCE_400G_AUI16 = 0x10,
    CMIS_COMPLIANCE_400G_AUI8 = 0x11,
    CMIS_COMPLIANCE_10G_BASE_CX4 = 0x13,
    CMIS_COMPLIANCE_25G_CR_L = 0x14,
    CMIS_COMPLIANCE_25G_CR_S = 0x15,
    CMIS_COMPLIANCE_25G_CR_N = 0x16,
    CMIS_COMPLIANCE_40G_BASE_CR4 = 0x17,
    CMIS_COMPLIANCE_50G_BASE_CR = 0x18,
    CMIS_COMPLIANCE_100G_BASE_CR10 = 0x19,
    CMIS_COMPLIANCE_100G_BASE_CR4 = 0x1a,
    CMIS_COMPLIANCE_100G_BASE_CR2 = 0x1b,
    CMIS_COMPLIANCE_200G_BASE_CR4 = 0x1c,
    CMIS_COMPLIANCE_400G_CR8 = 0x1d,
    CMIS_COMPLIANCE_1000_BASE_T = 0x1e,
    CMIS_COMPLIANCE_2_5G_BASE_T = 0x1f,
    CMIS_COMPLIANCE_5G_BASE_T = 0x20,
    CMIS_COMPLIANCE_10G_BASE_T = 0x21,
    CMIS_COMPLIANCE_25_BASE_T = 0x22,
    CMIS_COMPLIANCE_40_BASE_T = 0x23,
    CMIS_COMPLIANCE_50_BASE_T = 0x24,
    CMIS_COMPLIANCE_SDR = 0x2c,
    CMIS_COMPLIANCE_DDR = 0x2d,
    CMIS_COMPLIANCE_QDR = 0x2e,
    CMIS_COMPLIANCE_FDR = 0x2f,
    CMIS_COMPLIANCE_EDR = 0x30,
    CMIS_COMPLIANCE_HDR = 0x31
};

enum CMIS_MM_COMPLIANCE_CODE {
    CMIS_COMPLIANCE_10G_BASE_SW = 0x1,
    CMIS_COMPLIANCE_10G_BASE_SR = 0x2,
    CMIS_COMPLIANCE_25G_BASE_SR = 0x3,
    CMIS_COMPLIANCE_40G_BASE_SR4 = 0x4,
    CMIS_COMPLIANCE_40G_SWDM4 = 0x5,
    CMIS_COMPLIANCE_40G_BIDI = 0x6,
    CMIS_COMPLIANCE_50G_BASE_SR = 0x7,
    CMIS_COMPLIANCE_100G_BASE_SR10 = 0x8,
    CMIS_COMPLIANCE_100G_BASE_SR4 = 0x9,
    CMIS_COMPLIANCE_100G_SWDM4 = 0xa,
    CMIS_COMPLIANCE_100G_BIDI = 0xb,
    CMIS_COMPLIANCE_100G_SR2 = 0xc,
    CMIS_COMPLIANCE_100G_SR = 0xd,
    CMIS_COMPLIANCE_200G_BASE_SR4 = 0xe,
    CMIS_COMPLIANCE_400G_BASE_SR16 = 0xf,
    CMIS_COMPLIANCE_400G_BASE_SR8 = 0x10,
    CMIS_COMPLIANCE_400G_SR4 = 0x11,
    CMIS_COMPLIANCE_800G_SR8 = 0x12,
    CMIS_COMPLIANCE_400G_BIDI = 0x1a
};

enum CMIS_SM_COMPLIANCE_CODE {
    CMIS_COMPLIANCE_10G_BASE_LW = 0x1,
    CMIS_COMPLIANCE_10G_BASE_EW = 0x2,
    CMIS_COMPLIANCE_10G_ZW = 0x3,
    CMIS_COMPLIANCE_10G_BASE_LR = 0x4,
    CMIS_COMPLIANCE_10G_BASE_ER = 0x5,
    CMIS_COMPLIANCE_10G_BASE_ZR = 0x6,
    CMIS_COMPLIANCE_25G_BASE_LR = 0x7,
    CMIS_COMPLIANCE_25G_BASE_ER = 0x8,
    CMIS_COMPLIANCE_40G_BASE_LR4 = 0x9,
    CMIS_COMPLIANCE_40G_BASE_FR = 0xa,
    CMIS_COMPLIANCE_50G_BASE_FR = 0xb,
    CMIS_COMPLIANCE_50G_BASE_LR = 0xc,
    CMIS_COMPLIANCE_100G_BASE_LR4 = 0xd,
    CMIS_COMPLIANCE_100G_BASE_ER4 = 0xe,
    CMIS_COMPLIANCE_100G_PSM4 = 0xf,
    CMIS_COMPLIANCE_100G_CWDM4_OCP = 0x34,
    CMIS_COMPLIANCE_100G_CWDM4 = 0x10,
    CMIS_COMPLIANCE_100G_4WDM_10 = 0x11,
    CMIS_COMPLIANCE_100G_4WDM_20 = 0x12,
    CMIS_COMPLIANCE_100G_4WDM_40 = 0x13,
    CMIS_COMPLIANCE_100G_BASE_DR = 0x14,
    CMIS_COMPLIANCE_100G_FR = 0x15,
    CMIS_COMPLIANCE_100G_LR = 0x16,
    CMIS_COMPLIANCE_200G_BASE_DR4 = 0x17,
    CMIS_COMPLIANCE_200G_BASE_FR4 = 0x18,
    CMIS_COMPLIANCE_200G_BASE_LR4 = 0x19,
    CMIS_COMPLIANCE_400G_BASE_FR8 = 0x1a,
    CMIS_COMPLIANCE_400G_BASE_LR8 = 0x1b,
    CMIS_COMPLIANCE_400G_BASE_DR4 = 0x1c,
    CMIS_COMPLIANCE_400G_FR4 = 0x1d,
    CMIS_COMPLIANCE_400G_LR4 = 0x1e,
    CMIS_COMPLIANCE_10G_SR = 0x38,
    CMIS_COMPLIANCE_10G_LR = 0x39,
    CMIS_COMPLIANCE_25G_SR = 0x3a,
    CMIS_COMPLIANCE_25G_LR = 0x3b,
    CMIS_COMPLIANCE_10G_LR_BIDI = 0x3c,
    CMIS_COMPLIANCE_25G_LR_BIDI = 0x3d
};

enum PHY_MNGR_FSM_STATE {
    PHY_MNGR_DISABLED = 0,
    PHY_MNGR_OPEN_PORT = 1,
    PHY_MNGR_POLLING = 2,
    PHY_MNGR_ACTIVE_LINKUP = 3,
    PHY_MNGR_CLOSE_PORT = 4,
    PHY_MNGR_PHYSICAL_LINKUP = 5
};

enum IB_PHY_FSM_STATE {
    IB_AN_FSM_DISABLED = 0,
    IB_AN_FSM_INITIALY = 1,
    IB_AN_FSM_RCVR_CFG = 2,
    IB_AN_FSM_CFG_TEST = 3,
    IB_AN_FSM_WAIT_RMT_TEST = 4,
    IB_AN_FSM_WAIT_CFG_ENHANCED = 5,
    IB_AN_FSM_CFG_IDLE = 6,
    IB_AN_FSM_LINK_UP = 7
};

enum LOOPBACK_MODE{
    PHY_NO_LOOPBACK = 0,
    PHY_REMOTE_LOOPBACK = 1,
    PHY_LOCAL_LOOPBACK = 2,
    EXTERNAL_LOCAL_LOOPBACK = 4
};

enum AN_DISABLE {
    AN_DISABLE_NORMAL = 0,
    AN_DISABLE_FORCE  = 1
};

enum ETH_LINK_SPEED {
    ETH_LINK_SPEED_UNKNOWN = 0x0,
    ETH_LINK_SPEED_1000_SGMII = 0x1,
    ETH_LINK_SPEED_1000_KX = 0x2,
    ETH_LINK_SPEED_10G_CX4 = 0x4,
    ETH_LINK_SPEED_10G_KX4 = 0x8,
    ETH_LINK_SPEED_10G_KR = 0x10,
    ETH_LINK_SPEED_20G_KR2 = 0x20,
    ETH_LINK_SPEED_40G_CR4 = 0x40,
    ETH_LINK_SPEED_40G_KR4 = 0x80,
    ETH_LINK_SPEED_56G_KR4 = 0x100,
    ETH_LINK_SPEED_56G_R4 = 0x100,
    ETH_LINK_SPEED_10G_CR = 0x1000,
    ETH_LINK_SPEED_10G_SR = 0x2000,
    ETH_LINK_SPEED_10G_LR = 0x4000,
    ETH_LINK_SPEED_40G_SR4 = 0x8000,
    ETH_LINK_SPEED_40G_LR4 = 0x10000,
    ETH_LINK_SPEED_56G_CR4 = 0x20000,
    ETH_LINK_SPEED_50G_SR2 = 0x40000,
    ETH_LINK_SPEED_50G_KR4 = 0x80000,
    ETH_LINK_SPEED_100G_CR4 = 0x100000,
    ETH_LINK_SPEED_100G_SR4 = 0x200000,
    ETH_LINK_SPEED_100G_KR4 = 0x400000,
    ETH_LINK_SPEED_100G_LR4 = 0x800000,
    ETH_LINK_SPEED_100_BaseTx = 0x01000000,
    ETH_LINK_SPEED_1000_BaseT = 0x02000000,
    ETH_LINK_SPEED_10G_BaseT = 0x04000000,
    ETH_LINK_SPEED_25G_CR = 0x8000000,
    ETH_LINK_SPEED_25G_KR = 0x10000000,
    ETH_LINK_SPEED_25G_SR = 0x20000000,
    ETH_LINK_SPEED_50G_CR2 = 0x40000000,
    ETH_LINK_SPEED_50G_KR2 = 0x80000000,
};

enum ETH_LINK_SPEED_EXT {
    ETH_LINK_SPEED_EXT_UNKNOWN = 0x0,
    ETH_LINK_SPEED_EXT_SGMII_100M = 0x1,
    ETH_LINK_SPEED_EXT_1000BASE_X = 0x2,
    ETH_LINK_SPEED_EXT_2_5GBASE_X = 0x4,
    ETH_LINK_SPEED_EXT_5GBASE_R = 0x8,
    ETH_LINK_SPEED_EXT_XFI = 0x10,
    ETH_LINK_SPEED_EXT_XLAUI_4 = 0x20,
    ETH_LINK_SPEED_EXT_25GAUI_1 = 0x40,
    ETH_LINK_SPEED_EXT_50GAUI_2 = 0x80,
    ETH_LINK_SPEED_EXT_50GAUI_1 = 0x100,
    ETH_LINK_SPEED_EXT_CAUI_4 = 0x200,
    ETH_LINK_SPEED_EXT_100GAUI_2 = 0x400,
    ETH_LINK_SPEED_EXT_Reserved_11 = 0x800,
    ETH_LINK_SPEED_EXT_200GAUI_4 = 0x1000,
    ETH_LINK_SPEED_EXT_Reserved_13 = 0x2000,
    ETH_LINK_SPEED_EXT_Reserved_14 = 0x4000,
    ETH_LINK_SPEED_EXT_400GAUI_8 = 0x8000,
};

enum IB_LINK_SPEED {
    IB_LINK_SPEED_SDR   = 0x1,
    IB_LINK_SPEED_DDR   = 0x2,
    IB_LINK_SPEED_QDR   = 0x4,
    IB_LINK_SPEED_FDR10 = 0x8,
    IB_LINK_SPEED_FDR   = 0x10,
    IB_LINK_SPEED_EDR   = 0x20,
    IB_LINK_SPEED_HDR   = 0x40,
};

enum PRBS_MODULATION {
    PRBS_NRZ = 0,
    PRBS_PAM4_ENCODING = 1
};

class MlxlinkMaps{
private:
    MlxlinkMaps();
    static MlxlinkMaps* instance;
    void initPublicStrings();
    void initPortStateMapping();
    void initFecAndLoopbackMapping();
    void ethSpeedMapping();
    void extEthSpeedMapping();
    void ibSpeedMapping();
    void speedToLanesMapping();
    void initPortSpeedMapping();
    void initPrbsMapping();
    void initPpbmcAndPepcMapping();
    void initLinkDownInfoMapping();
    void initSltpStatusMapping();
    void qsfpComlianceMapping();
    void sfpComplianceMapping();
    void extComplianceMapping();
    void hostComplianceMapping();
    void mediaComplianceMapping();
    void activeComplianceMapping();
    void initCableComplianceMapping();
    void initCableTechnologyMapping();
    void initCablePowerClassMapping();

public:
    static MlxlinkMaps* getInstance();
    virtual ~MlxlinkMaps();

    std::map<u_int32_t, std::string> _pmFsmState;
    std::map<u_int32_t, u_int32_t>   _ETHSpeed2gRate;
    std::map<u_int32_t, u_int32_t>   _IBSpeed2gRate;
    std::map<u_int32_t, std::string> _ibPhyFsmState;
    std::map<u_int32_t, std::string> _groupMap;
    std::map<u_int32_t, std::string> _speedsListETH;
    std::map<u_int32_t, std::string> _speedsListIB;
    std::map<u_int32_t, std::string> _prbsModesList;
    std::map<u_int32_t, std::string> _prbsLaneRateList;
    std::map<u_int32_t, std::string> _pepcStatus;
    std::map<u_int32_t, string>      _IBSpeed2Str;
    std::map<u_int32_t, string>      _EthExtSpeed2Str;
    std::map<u_int32_t, u_int32_t>   _IBSpeed2gNum;
    std::map<u_int32_t, u_int32_t>   _ETHSpeed2gNum;
    std::map<u_int32_t, string>      _ETHSpeed2Str;
    std::map<u_int32_t, u_int32_t>   _EthExtSpeed2gNum;
    std::map<u_int32_t, u_int32_t>   _ETHSpeed2Lanes;
    std::map<u_int32_t, u_int32_t>   _ExtETHSpeed2Lanes;
    std::map<u_int32_t, string>      _SLTPBadSetStatus2Str;
    std::map<u_int32_t, string>      _SLTP16BadSetStatus2Str;
    std::map<u_int32_t, std::string> _ethANFsmState;
    std::map<u_int32_t, std::string> _fecModeActive;
    std::map<u_int32_t, std::string> _loopbackModeList;
    std::map<u_int32_t, std::string> _anDisableList;
    std::map<u_int32_t, std::string> _cableComplianceSfp;
    std::map<u_int32_t, std::string> _cableComplianceQsfp;
    std::map<u_int32_t, std::string> _cableComplianceExt;
    std::map<u_int32_t, std::string> _cmisHostCompliance;
    std::map<u_int32_t, std::string> _mmfCompliance;
    std::map<u_int32_t, std::string> _smfCompliance;
    std::map<u_int32_t, std::string> _activeCableCompliance;
    std::map<u_int32_t, std::string> _sfpQsfpPowerClass;
    std::map<u_int32_t, std::string> _sfpddPowerClass;
    std::map<u_int32_t, std::string> _qsfpddOsfpPowerClass;
    std::map<u_int32_t, float>       _qsfpddPowerClassToValue;
    std::map<u_int32_t, float>       _sfpddPowerClassToValue;
    std::map<u_int32_t, std::string> _cableTechnologyQsfp;
    std::map<u_int32_t, std::string> _cableTechnologySfp;
    std::map<u_int32_t, std::string> _ppbmcBerMonitorState;
    std::map<u_int32_t, std::string> _ppbmcBerMonitorType;
    std::map<u_int32_t, std::string> _pepcTwistedPairAn;
    std::map<u_int32_t, std::string> _pepcTwistedPairForceMode;
    std::map<u_int32_t, std::string> _pepcTwistedPairAnMode;
    std::map<u_int32_t, std::string> _pddrLinkDownBlame;
    std::map<u_int32_t, std::string> _pddrLinkDownE2EReasonOpcode;

    string _sltpHeader;
    string _berCollectTitle;
    string _showErrorsTitle;
};

#endif /* MLXLINK_MAPS_H */
