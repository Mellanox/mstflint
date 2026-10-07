
/*
* Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
*  Version: $Id$
*
*/
 

/***
         *** This file was generated at "2026-10-01 10:06:54"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils -o user/tools_layouts
         ***/
#ifndef REG_ACCESS_SWITCH_LAYOUTS_H
#define REG_ACCESS_SWITCH_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_ef_afe_snap_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.2 */
	/* access: RO */
	u_int8_t term_attn_ctrl;
	/* Description -  */
	/* 0x0.3 - 0x0.5 */
	/* access: RO */
	u_int8_t dc_gain;
	/* Description -  */
	/* 0x0.6 - 0x0.13 */
	/* access: RO */
	u_int8_t hf_gain;
	/* Description -  */
	/* 0x0.14 - 0x0.15 */
	/* access: RO */
	u_int8_t lf_gain;
	/* Description -  */
	/* 0x0.16 - 0x0.17 */
	/* access: RO */
	u_int8_t lf_pole;
	/* Description -  */
	/* 0x0.18 - 0x0.19 */
	/* access: RO */
	u_int8_t mf_gain;
	/* Description -  */
	/* 0x0.20 - 0x0.21 */
	/* access: RO */
	u_int8_t mf_pole;
	/* Description -  */
	/* 0x0.22 - 0x0.25 */
	/* access: RO */
	u_int8_t tah_amp_gain;
	/* Description -  */
	/* 0x0.26 - 0x0.31 */
	/* access: RO */
	u_int8_t adc_vref_val;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t cdr_offset;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - AFE (Analog Front End) configuration snapshot, 2 DWORDs. */
	/* 0x0.0 - 0x4.31 */
	/* access: RO */
	struct reg_access_switch_ef_afe_snap_v1_ext afe_snap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - BER exponent; BER = ber_coeff.ber_coeff_float  10^(ber_magnitude). */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t ber_magnitude;
	/* Description - BER coefficient integer part. */
	/* 0x8.8 - 0x8.11 */
	/* access: RO */
	u_int8_t ber_coeff;
	/* Description - BER coefficient fractional digit. */
	/* 0x8.12 - 0x8.15 */
	/* access: RO */
	u_int8_t ber_coeff_float;
	/* Description - Set by SerDes after storing the AFE snap. */
	/* 0x8.16 - 0x8.16 */
	/* access: RO */
	u_int8_t serdes_valid;
	/* Description - Set by PHY after writing the BER fields. */
	/* 0x8.17 - 0x8.17 */
	/* access: RO */
	u_int8_t phy_valid;
	/* Description - PHY-set flag: BER measurement is invalid (no PCS lock at measurement
start, or alignment lost mid-window). The picker must skip this entry. */
	/* 0x8.18 - 0x8.18 */
	/* access: RO */
	u_int8_t meas_invalid;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_hst_link_eth_enabled_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols active: see PTYS.ext_eth_proto_oper */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_eth_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_hst_link_ib_enabled_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t link_width_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_hst_link_nvlink_enabled_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink protocols activeSee:
PTYS - Extended Protocol NVLink - cap/oper Layout */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_nvlink_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pd_link_eth_enabled_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols active: see PTYS.ext_eth_proto_oper */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_eth_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pd_link_ib_enabled_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t link_width_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_c2p_link_enabled_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols admin state: see PTYS.ext_eth_proto_admin */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t core_to_phy_link_eth_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_c2p_link_enabled_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - bi link enabled speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t core_to_phy_link_proto_enabled;
	/* Description - IB link enabled width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t core_to_phy_link_width_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink protocols admin statesee:
PTYS - Extended Protocol NVLink - admin Layout */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t core_to_phy_link_nvlink_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_cable_cap_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is
supported, use for opcode definition PTYS.ext_eth_proto_capIf
PTYS.ext_eth_proto_capability mask is empty, use For opcode definition
PTYS.eth_proto_cap. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t cable_ext_eth_proto_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_cable_cap_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Cable support IB speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t cable_link_speed_cap;
	/* Description - Cable support IB width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t cable_link_width_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_cable_cap_nvlink_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Cable NVLink protocols cap:See:
PTYS - Extended Protocol NVLink - cap/oper Layout */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t cable_nvlink_proto_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_link_active_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols active: see PTYS.ext_eth_proto_oper */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_eth_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_link_active_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t link_width_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_link_active_nvlink_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink protocols activeSee:
PTYS - Extended Protocol NVLink - cap/oper Layout */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_nvlink_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_monitor_opcode_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Status opcode:PHY FW indication (0 - 1023):0 - No issue observed1 - Port is close by command (see PAOS).2,3,4,38,39,60,69 - AN failure5,6,7,8, 62,63,64,65,66 - Link training failure.9,10,11,12,13 - Logical mismatch between link partners14 - Remote fault received15,42,17,48,49,52, - Bad signal integrity16,24-32 - Cable compliance code mismatch (protocol mismatch between
cable and port) 23,22,19,18,50,55- internal error34,35 - Speed degradation56 - module_lanes_frequency_not_synced57 - signal not detected60 - no partner detected for long time68 - reserved70- link not healthy, BER doesn't meet criteria71 - serdes uphy fatal indication72 - serdes ophy fatal indication71 - Invalid_Port_Speed_Configuration128 - Troubleshooting in process1023- Info not availableMNG FW issues (1024 - 2047):1024 - Cable is unplugged1025 - Long Range for non Mellanox cable/module1026 - Bus stuck (I2C Data or clock shorted)1027 - Bad/unsupported EEPROM1028 - Part number list1029 - Unsupported cable1030 - Module temperature shutdown1031 - Shorted cable1032 - Power budget exceeded1033 - Management forced down the port1034 - Module is disabled by command1035 - System Power is Exceeded therefore the module is powered off.1036 - Module's PMD type is not enabled (see PMTPS).1040 - pcie system power slot Exceeded1042 - Module state machine fault1043,1044,1045,1046 - Module's stamping speed degeneration1047, 1048 - Modules DataPath FSM fault1050, 1051, 1052, 1053- Module Boot Error1054 - Module Forced to Low Power by command1055 - ELS laser fiber is contaminated1056 - ELS laser power control failure1057 - ELS unplugged1058 - ELS laser rampling timeout failure1059 - ELS laser power exceeded allowed power range1060 - ELS laser power subceeded allowed power range1061 - ELS TEC control loop failure1062 - ELS laser power tuning failure1063 - ELS laser wavelength tuning failure1064 - ELS laser health indication - high path loss1065 - ELS laser high loss power drop */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t monitor_opcode;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols admin state: see PTYS.ext_eth_proto_admin */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t phy_manager_link_eth_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB link enabled speed:Bit 0 - SDRBit 1 - DDRBit 2 - QDRBit 3 - FDR10Bit 4 - FDRBit 5 - EDRBit 6 - HDRBit 7 - NDRBit 8 - XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t phy_manager_link_proto_enabled;
	/* Description - IB link enabled width:Bit 0 - 1xBit 1 - 2xBit 2 - 4xOther - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t phy_manager_link_width_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink protocols admin state:see:
PTYS - Extended Protocol NVLink - admin Layout */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t phy_manager_link_nvlink_enabled;
};

/* Description -   */
/* Size in bytes - 68 */
struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Iteration results table. Array of 5 96-bit elements, 3 DWORDs
each (iter_table[0] at 00h08h, iter_table[4] at 30h38h). */
	/* 0x0.0 - 0x38.31 */
	/* access: RO */
	struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext iter_table[5];
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Debug mirror of PHY lt_x_index (last stored count). */
	/* 0x3c.0 - 0x3c.3 */
	/* access: RO */
	u_int8_t stores_done;
	/* Description - Index of the entry with the best BER. */
	/* 0x3c.4 - 0x3c.7 */
	/* access: RO */
	u_int8_t winner_idx;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Stamp mismatch detected during validation. */
	/* 0x40.0 - 0x40.0 */
	/* access: RO */
	u_int8_t protocol_violation;
	/* Description - Which entry had the stamp violation. */
	/* 0x40.1 - 0x40.4 */
	/* access: RO */
	u_int8_t violation_idx;
	/* Description - Which stamp was missing during validation.0: none1: no_serdes_stamp2: no_phy_stamp3: both */
	/* 0x40.5 - 0x40.6 */
	/* access: RO */
	u_int8_t violation_type;
	/* Description - force_best_afe_values was called. */
	/* 0x40.7 - 0x40.7 */
	/* access: RO */
	u_int8_t force_applied;
	/* Description - Last failure point in the LT-X store/force flow.0: ok1: reserved_12: phy_update_rejected3: force_no_valid_entry4: reserved_45: phy_bad_index_overflow */
	/* 0x40.8 - 0x40.11 */
	/* access: RO */
	u_int8_t last_fail_stage;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_ef_lt_x_port_info_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - LTX_EN_RESTORE retries this bringup (063). */
	/* 0x0.0 - 0x0.5 */
	/* access: RO */
	u_int8_t ltx_restore_count;
	/* Description - Complete LT-X cycles; saturates at 7. */
	/* 0x0.6 - 0x0.8 */
	/* access: RO */
	u_int8_t ltx_total_rounds_cnt;
	/* Description - BER iterations done. */
	/* 0x0.9 - 0x0.12 */
	/* access: RO */
	u_int8_t num_ber_meas_done;
	/* Description - Auto-fix-reversals swapped lanes. */
	/* 0x0.13 - 0x0.13 */
	/* access: RO */
	u_int8_t auto_reversals_applied;
	/* Description - Round count is below lt_x_full_cycle_limit. */
	/* 0x0.14 - 0x0.14 */
	/* access: RO */
	u_int8_t ltx_limiter_allow;
	/* Description - Sticky: load_best hit retry cap. */
	/* 0x0.15 - 0x0.15 */
	/* access: RO */
	u_int8_t ltx_reached_max_retry;
	/* Description - LT-X flow was entered. */
	/* 0x0.16 - 0x0.16 */
	/* access: RO */
	u_int8_t entered_ltx_flow;
	/* Description - BER-based flow in progress at snapshot. */
	/* 0x0.17 - 0x0.17 */
	/* access: RO */
	u_int8_t ber_based_in_progress;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The actual state of the Training control state diagram (IEEE 802.3dj Annex 178B Figure 178B-10).0: QUIET1: SEND_TRAINING2: TRAIN_START3: TRAIN_LOCAL4: TRAIN_REMOTE5: ISL_READY6: PATH_READY7: PATH_UP8: RECOVERY9: FAIL10: SEND_LOCAL11: RX_READY */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t train_ctl_state;
	/* Description - Enumerated variable that indicates the training pattern modulation and coding.0: PAM21: Reserved2: PAM4 without precoding3: PAM4 with precoding. */
	/* 0x0.8 - 0x0.9 */
	/* access: RO */
	u_int8_t local_mc_mode;
	/* Description - Enumerated variable that indicates the transmitted training pattern.0: synchronous PRBS131: free-running PRBS132: Reserved3: freerunningPRBS31 */
	/* 0x0.10 - 0x0.11 */
	/* access: RO */
	u_int8_t local_tp_mode;
	/* Description - The status of the ILT function. Valid only if apsu_oper = Enabled.0: FAIL: Training failed1: OK: Training OK2: Reserved3: IN_PROGRESS: Lane is being trained */
	/* 0x0.12 - 0x0.13 */
	/* access: RO */
	u_int8_t lane_training_status;
	/* Description - Set if the signal polarity was reverted */
	/* 0x0.18 - 0x0.18 */
	/* access: RO */
	u_int8_t polarity_correction;
	/* Description - Set if the transmitter is disabled (squelch). Used only if training_en_oper = Disable */
	/* 0x0.19 - 0x0.19 */
	/* access: RO */
	u_int8_t tx_disable;
	/* Description - Set if the Not ready to send bit in the ILT received frame is clear. */
	/* 0x0.20 - 0x0.20 */
	/* access: RO */
	u_int8_t remote_rts;
	/* Description - Set if the local transmitter is ready to send PCS data */
	/* 0x0.21 - 0x0.21 */
	/* access: RO */
	u_int8_t local_rts;
	/* Description - Set if the Receiver ready bit in the ILT received frame is set. */
	/* 0x0.22 - 0x0.22 */
	/* access: RO */
	u_int8_t remote_rx_ready;
	/* Description - Set if the local receiver finished training. */
	/* 0x0.23 - 0x0.23 */
	/* access: RO */
	u_int8_t local_rx_ready;
	/* Description - Set if the Receiver frame lock bit in the ILT received frame is set. */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t remote_tf_lock;
	/* Description - Set if the ILT frame position has been detected */
	/* 0x0.25 - 0x0.25 */
	/* access: RO */
	u_int8_t local_tf_lock;
	/* Description - Set if local receiver is receiving a good signal */
	/* 0x0.26 - 0x0.26 */
	/* access: RO */
	u_int8_t rx_ok;
	/* Description - Set if the invert_to timer expired */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t invert_to_done;
	/* Description - Set if the training process failed */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t training_failure;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - nLUT backchannel number of transmitted blocks */
	/* 0x4.0 - 0x4.9 */
	/* access: RO */
	u_int16_t bcnl_rx_block_cnt;
	/* Description - nLUT backchannel number of received blocks */
	/* 0x4.16 - 0x4.25 */
	/* access: RO */
	u_int16_t bcnl_tx_block_cnt;
	/* Description - Set if nLUT backchannel message failed to be received */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t bcnl_msg_rx_fail;
	/* Description - Set if nLUT backchannel message failed to be transmitted */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t bcnl_msg_tx_fail;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_ltx_logger_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t ltx_status;
	/* Description -  */
	/* 0x0.1 - 0x0.5 */
	/* access: RO */
	u_int8_t ltx_fail_reason;
	/* Description - Number of times the link quality by fec measure re-checked for the
current itteration */
	/* 0x0.6 - 0x0.10 */
	/* access: RO */
	u_int8_t ltx_retry_count;
	/* Description -  */
	/* 0x0.11 - 0x0.11 */
	/* access: RO */
	u_int8_t effective_errors;
	/* Description -  */
	/* 0x0.12 - 0x0.16 */
	/* access: RO */
	u_int8_t highest_non_zero_hist;
	/* Description -  */
	/* 0x0.17 - 0x0.24 */
	/* access: RO */
	u_int8_t raw_ber_magnitude;
	/* Description -  */
	/* 0x0.25 - 0x0.29 */
	/* access: RO */
	u_int8_t prbs_ber_magnitude;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of times the link quality by fec measure failed for the current
itteration */
	/* 0x4.6 - 0x4.10 */
	/* access: RO */
	u_int8_t ltx_retry_fail_count;
	/* Description -  */
	/* 0x4.17 - 0x4.20 */
	/* access: RO */
	u_int8_t raw_ber_mantissa;
	/* Description -  */
	/* 0x4.21 - 0x4.24 */
	/* access: RO */
	u_int8_t raw_ber_mantissa_float;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_cable_cap_eth_ext pddr_cable_cap_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_cable_cap_ib_ext pddr_cable_cap_ib_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_cable_cap_nvlink_ext pddr_cable_cap_nvlink_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_c2p_link_enabled_eth_ext pddr_c2p_link_enabled_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_c2p_link_enabled_ib_ext pddr_c2p_link_enabled_ib_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext pddr_c2p_link_enabled_nvlink_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_link_active_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_active_eth_ext pddr_link_active_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_active_ib_ext pddr_link_active_ib_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_active_nvlink_ext pddr_link_active_nvlink_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pd_link_eth_enabled_ext pd_link_eth_enabled_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pd_link_ib_enabled_ext pd_link_ib_enabled_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_hst_link_eth_enabled_ext hst_link_eth_enabled_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_hst_link_ib_enabled_ext hst_link_ib_enabled_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_hst_link_nvlink_enabled_ext hst_link_nvlink_enabled_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext pddr_phy_manager_link_enabled_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext pddr_phy_manager_link_enabled_ib_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext pddr_phy_manager_link_enabled_nvlink_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_monitor_opcode_ext pddr_monitor_opcode_ext;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_MRFV_CVB_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [Arcus2]: Index of LUT entry.[ArcusE]:CVB Voltage = -4 + 0.5 * cvb_data_indexcvb_data_index valid values 0 .. 15Process Sigma <-> DVDD (mV)-4.0: 856.00-3.5: 847.75-3.0: 839.50-2.5: 831.25-2.0: 823.00-1.5: 814.75-1.0: 806.50-0.5: 798.250 (nominal): 790.000.5: 781.751.0: 773.501.5: 765.252.0: 757.002.5: 748.753.0: 740.503.5: 732.254.0: 724.00Reserved when selector = 1 */
	/* 0x0.0 - 0x0.4 */
	/* access: RO */
	u_int8_t cvb_data_index;
	/* Description - [DWIP][Internal]Valid only if selector = 0.The minimum value of ISM cnt_out value, normalized by VDD value, which
is used to determine the selected LUT entry index. */
	/* 0x0.6 - 0x0.25 */
	/* access: RO */
	u_int32_t cnt_out;
	/* Description - MSB bits of the TAV voltage */
	/* 0x0.26 - 0x0.29 */
	/* access: RO */
	u_int8_t tav_cvb_voltage_msb;
	/* Description - [DWIP] [Internal]If selector = 0:0: LUT used.1: Default fuse value used.If selector = 1:0: Fuses are valid (either non-default or default value).1: Fuses are invalid but LUT entry not located. */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t selector_cause;
	/* Description - [Arcus]:0: cvb_data_index is valid1: cvb_voltage is valid[Arcus2]:0: cvb_data_index is valid, and cvb_voltage exposes the value in LUT or
the default fuse values.1: cvb_data_index is not valid, and cvb_voltage exposes non-default
values from fuses (if selector_cause = 0). */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t selector;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - CVB VoltageReturns required CVB voltage in mV.Reserved when selector = 0 */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t cvb_voltage;
	/* Description - The voltage type of the cvb_voltage0: DVDD1: AVDD2: VDD */
	/* 0x4.16 - 0x4.18 */
	/* access: INDEX */
	u_int8_t voltage_type;
	/* Description - TAV CVB VoltageReturns required TAV CVB voltage in mV.Used in Retimer only.Value of 0 means not valid voltage, host should ignore this value. */
	/* 0x4.20 - 0x4.31 */
	/* access: RO */
	u_int16_t tav_cvb_voltage;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_MRFV_PVS_MAIN_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VDD Main Data. PVS prefix in name exists due to historical reasons.Range 0.675 - 0.75Vdd = 750mV - (fuse value - 1)*5mV */
	/* 0x0.0 - 0x0.6 */
	/* access: RO */
	u_int8_t pvs_main_data;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_MRFV_PVS_TILE_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VDD tile Data. PVS prefix in name exists due to historical reasons.Range 0.675 - 0.72Vdd = 750mV - (fuse value - 1)*5mV */
	/* 0x0.0 - 0x0.6 */
	/* access: RO */
	u_int8_t pvs_tile_data;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_switch_MRFV_RAW_AND_VALUE_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Raw Fuses Highest bit. Indicates the highest bit in raw_fuses field
which is part of the fuse data.For example, if raw_fuses [15:0] contains the fuse data, this field's
value is 15. */
	/* 0x0.0 - 0x0.4 */
	/* access: RO */
	u_int8_t raw_fuses_highest_bit;
	/* Description - Value valid.0: value_base and value_exponent are NOT valid.1: value_base and value_exponent are valid.[Switch]:For the following fuse_ids (assuming a valid instance_id is
provided), the value is valid:11: raw_and_value_vdd.12: raw_and_value_pl_avdd.13: raw_and_value_pl_dvdd.16: raw_and_value_dvdd_sg. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t value_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Raw fuses.The only valid bits are bits 0 to <raw_fuses_highest_bit>. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t raw_fuses;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The exponent part of the value.This field is signed, and negative values are represented using 2's
complement. */
	/* 0x8.0 - 0x8.5 */
	/* access: RO */
	u_int8_t value_exponent;
	/* Description - The base part of the value.This field is signed, and negative values are represented using 2's
complement.The value is:value_base x 10 ^ value_exponent.Units:Power: [W].Voltage: [V].Time: [Sec].Current: [A].Capacitance: [F]. */
	/* 0x8.6 - 0x8.31 */
	/* access: RO */
	u_int32_t value_base;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_switch_MRFV_ULT_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t ult_lot_digit_1;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t ult_lot_digit_2;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t ult_lot_digit_3;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t ult_lot_digit_4;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t ult_lot_digit_5;
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ult_lot_digit_6;
	/* Description -  */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t ult_lot_digit_7;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t ult_lot_digit_8;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t ult_y;
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t ult_x;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t ult_wafer_number;
	/* Description -  */
	/* 0x8.29 - 0x8.31 */
	/* access: RO */
	u_int8_t ult_err_detection;
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_command_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Command data. It may be a request or a response data. */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	u_int32_t data[65];
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_crspace_access_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Starting address */
	/* 0x0.0 - 0x0.31 */
	/* access: WO */
	u_int32_t address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - CrSpace data */
	/* 0x4.0 - 0x100.31 */
	/* access: RW */
	u_int32_t data[64];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_device_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device indexThe first device should number 0 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t device_index;
	/* Description - The flash ID that the device is using. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t flash_id;
	/* Description - If set to 1', the fields related to the device are valid since the
line-card is powered on and plugged and matching the INI version.Note: this bit is not an indication to validity of the fields related to
the specific FW capabilities and version. */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t lc_pwr_on;
	/* Description - Thermal Shutdown. If set, the device was shut down due to thermal event. */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t thermal_sd;
	/* Description - If set to 1', the device is the flash owner. Otherwise, a shared flash
is used by this device (another device is the flash owner). */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t flash_owner;
	/* Description - If set, the device uses a flash */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t uses_flash;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: Amos Gearbox1: Abir Gearbox */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t device_type;
	/* Description - Major FW version number. Valid only after the FW is burnt. Otherwise,
the value should be 0'. */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t fw_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Sub-minor FW version number. Valid only after the FW is burnt.
Otherwise, the value should be 0'. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t fw_sub_minor;
	/* Description - Minor FW version number. Valid only after the FW is burnt. Otherwise,
the value should be 0'. */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t fw_minor;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximum write size (in D-Words) that the device supports for its PRM
commands. */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t max_cmd_write_size_supp;
	/* Description - Maximum read size (in D-Words) that the device supports for its PRM
commands. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t max_cmd_read_size_supp;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Device type ASCII name. Up to 8 chars */
	/* 0x10.24 - 0x18.23 */
	/* access: RO */
	u_int8_t device_type_name[8];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_slot_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the FW has completed the MDDC.device_enable command */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t active;
	/* Description - If set, the LC is powered on, matching the INI version and a new FW
version can be burnt (if necessary)0: Not ready1: Ready2: Error3: Reserved */
	/* 0x0.28 - 0x0.29 */
	/* access: RO */
	u_int8_t lc_ready;
	/* Description - If set, Shift Register is valid (after being provisioned) and data can
be sent from the switch ASIC to the line-card CPLD over Shift-Register. */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t sr_valid;
	/* Description - If set, the INI file is ready and the card is provisioned */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t provisioned;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - User-configured version number of the current INI file.Valid only when active or lc_ready are 1'. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t ini_file_version;
	/* Description - HW revision of the line-card as it appears in the current INI file.Valid only when active or lc_ready are 1'. */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t hw_revision;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Card type0x00: Buffalo 4x400G0x01: Buffalo 8x200G0x02: Buffalo 16x100G */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t card_type;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_slot_name_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot's ASCII name. Up to 20 chars */
	/* 0x0.24 - 0x14.23 */
	/* access: RO */
	u_int8_t slot_ascii_name[20];
};

/* Description -   */
/* Size in bytes - 80 */
struct reg_access_switch_module_latched_flag_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - when set, indicates modules supports rx los indication */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t rx_los_cap;
	/* Description - Valid for CMIS based modules onlyLatched modules Datapath fw fault flag */
	/* 0x0.22 - 0x0.22 */
	/* access: RO */
	u_int8_t dp_fw_fault;
	/* Description - Valid for CMIS based modules onlyLatched module fw fault flag */
	/* 0x0.23 - 0x0.23 */
	/* access: RO */
	u_int8_t mod_fw_fault;
	/* Description - Latched VCC flags of moduleBit 0: high_vcc_alarmBit 1: low_vcc_alarmBit 2: high_vcc_warningBit 3: low_vcc_warning */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t vcc_flags;
	/* Description - Latched temperature flags of moduleBit 0: high_temp_alarmBit 1: low_temp_alarmBit 2: high_temp_warningBit 3: low_temp_warning */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t temp_flags;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reserved for SFPBitmask for latched Tx adaptive equalization fault flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t tx_ad_eq_fault;
	/* Description - Bitmask for latched Tx cdr loss of lock flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t tx_cdr_lol;
	/* Description - Reserved for SFPBitmask for latched Tx loss of signal flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t tx_los;
	/* Description - Bitmask for latched Tx fault flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t tx_fault;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bitmask for latched Tx power low warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t tx_power_lo_war;
	/* Description - Bitmask for latched Tx power high warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t tx_power_hi_war;
	/* Description - Bitmask for latched Tx power low alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t tx_power_lo_al;
	/* Description - Bitmask for latched Tx power high alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t tx_power_hi_al;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Bitmask for latched Tx bias low warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t tx_bias_lo_war;
	/* Description - Bitmask for latched Tx bias high warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t tx_bias_hi_war;
	/* Description - Bitmask for latched Tx bias low alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t tx_bias_lo_al;
	/* Description - Bitmask for latched Tx bias high alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t tx_bias_hi_al;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bitmask for latched Rx cir loss of lock flag per lane.Bit 0 - lane 0 .. Bit 7 - lane 7 */
	/* 0x10.16 - 0x10.23 */
	/* access: RO */
	u_int8_t rx_cdr_lol;
	/* Description - Bitmask for latched Rx loss of signal flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t rx_los;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Bitmask for latched Rx power low warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x14.0 - 0x14.7 */
	/* access: RO */
	u_int8_t rx_power_lo_war;
	/* Description - Bitmask for latched Rx power high warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x14.8 - 0x14.15 */
	/* access: RO */
	u_int8_t rx_power_hi_war;
	/* Description - Bitmask for latched Rx power low alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x14.16 - 0x14.23 */
	/* access: RO */
	u_int8_t rx_power_lo_al;
	/* Description - Bitmask for latched Rx power high alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x14.24 - 0x14.31 */
	/* access: RO */
	u_int8_t rx_power_hi_al;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Bitmask for latched rx output valid change per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x18.0 - 0x18.7 */
	/* access: RO */
	u_int8_t rx_output_valid_change;
	/* Description - Bitmask per flag type in ELS module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it's
recommended to set event for module flags via trap.Bit 0: laser2_temp_hi_alBit 1: laser2_temp_lo_alBit 2: laser2_temp_hi_warBit 3: laser2_temp_lo_war */
	/* 0x18.24 - 0x18.27 */
	/* access: RO */
	u_int8_t laser_source_flag_in_use_msb;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser2 warning indication */
	/* 0x18.28 - 0x18.28 */
	/* access: RO */
	u_int8_t laser2_warning_flag;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser warning indication */
	/* 0x18.29 - 0x18.29 */
	/* access: RO */
	u_int8_t laser_warning_flag;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser2 fault indication */
	/* 0x18.30 - 0x18.30 */
	/* access: RO */
	u_int8_t laser2_fault_flag;
	/* Description - ELS laser fault indication */
	/* 0x18.31 - 0x18.31 */
	/* access: RO */
	u_int8_t laser_fault_flag;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - ELS laser bias low warning */
	/* 0x20.0 - 0x20.0 */
	/* access: RO */
	u_int8_t laser2_bias_lo_war;
	/* Description - ELS laser bias low warning */
	/* 0x20.1 - 0x20.1 */
	/* access: RO */
	u_int8_t laser_bias_lo_war;
	/* Description - ELS laser bias high warning */
	/* 0x20.2 - 0x20.2 */
	/* access: RO */
	u_int8_t laser2_bias_hi_war;
	/* Description - ELS laser bias high warning */
	/* 0x20.3 - 0x20.3 */
	/* access: RO */
	u_int8_t laser_bias_hi_war;
	/* Description - ELS laser bias low alarm */
	/* 0x20.4 - 0x20.4 */
	/* access: RO */
	u_int8_t laser2_bias_lo_al;
	/* Description - ELS laser bias low alarm */
	/* 0x20.5 - 0x20.5 */
	/* access: RO */
	u_int8_t laser_bias_lo_al;
	/* Description - ELS laser bias high alarm */
	/* 0x20.6 - 0x20.6 */
	/* access: RO */
	u_int8_t laser2_bias_hi_al;
	/* Description - ELS laser bias high alarm */
	/* 0x20.7 - 0x20.7 */
	/* access: RO */
	u_int8_t laser_bias_hi_al;
	/* Description - Bitmask per flag type in ELS module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it's
recommended to set event for module flags via trap.Bit 0: global_alarm_for_laserBit 1: global_warning_for_laserBit 2: laser_bias_hi_al_capBit 3: laser_bias_lo_al_capBit 4: laser_bias_hi_war_capBit 5: laser_bias_lo_war_capBit 6: laser_opt_pwr_hi_al_capBit 7: laser_opt_pwr_lo_al_capBit 8: laser_opt_pwr_hi_war_capBit 9: laser_opt_pwr_lo_war_capBit 10: laser_temp_hi_alBit 11: laser_temp_lo_alBit 12: laser_temp_hi_warBit 13: laser_temp_lo_warBit 14: global_alarm_for_laser2Bit 15: global_warning_for_laser2Bit 16: laser2_bias_hi_al_capBit 17: laser2_bias_lo_al_capBit 18: laser2_bias_hi_war_capBit 19: laser2_bias_lo_war_capBit 20: laser2_opt_pwr_hi_al_capBit 21: laser2_opt_pwr_lo_al_capBit 22: laser2_opt_pwr_hi_war_capBit 23: laser2_opt_pwr_lo_war_cap */
	/* 0x20.8 - 0x20.31 */
	/* access: RO */
	u_int32_t laser_source_flag_in_use;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Bitmask per flag type in Optical engine module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it's
recommended to set event for module flags via trap.Bit 0: els_input_power_hi_alBit 1: els_input_power_lo_alBit 2: els_input_power_hi_warBit 3: els_input_power_lo_warBit 4: lane_temp_hi_alBit 5: lane_temp_lo_alBit 6: lane_temp_hi_warBit 7: lane_temp_lo_war */
	/* 0x24.0 - 0x24.15 */
	/* access: RO */
	u_int16_t optical_engine_flag_in_use;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser temperature low warning */
	/* 0x24.16 - 0x24.16 */
	/* access: RO */
	u_int8_t laser2_temp_lo_war;
	/* Description - ELS laser temperature low warning */
	/* 0x24.17 - 0x24.17 */
	/* access: RO */
	u_int8_t laser_temp_lo_war;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser temperature high warning */
	/* 0x24.18 - 0x24.18 */
	/* access: RO */
	u_int8_t laser2_temp_hi_war;
	/* Description - ELS laser temperature high warning */
	/* 0x24.19 - 0x24.19 */
	/* access: RO */
	u_int8_t laser_temp_hi_war;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser temperature low alarm */
	/* 0x24.20 - 0x24.20 */
	/* access: RO */
	u_int8_t laser2_temp_lo_al;
	/* Description - ELS laser temperature low alarm */
	/* 0x24.21 - 0x24.21 */
	/* access: RO */
	u_int8_t laser_temp_lo_al;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser temperature high alarm */
	/* 0x24.22 - 0x24.22 */
	/* access: RO */
	u_int8_t laser2_temp_hi_al;
	/* Description - ELS laser temperature high alarm */
	/* 0x24.23 - 0x24.23 */
	/* access: RO */
	u_int8_t laser_temp_hi_al;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser optical power low warning */
	/* 0x24.24 - 0x24.24 */
	/* access: RO */
	u_int8_t laser2_opt_pwr_lo_war;
	/* Description - ELS laser optical power low warning */
	/* 0x24.25 - 0x24.25 */
	/* access: RO */
	u_int8_t laser_opt_pwr_lo_war;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser optical power high warning */
	/* 0x24.26 - 0x24.26 */
	/* access: RO */
	u_int8_t laser2_opt_pwr_hi_war;
	/* Description - ELS laser optical power high warning */
	/* 0x24.27 - 0x24.27 */
	/* access: RO */
	u_int8_t laser_opt_pwr_hi_war;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser optical power low alarm */
	/* 0x24.28 - 0x24.28 */
	/* access: RO */
	u_int8_t laser2_opt_pwr_lo_al;
	/* Description - ELS laser optical power low alarm */
	/* 0x24.29 - 0x24.29 */
	/* access: RO */
	u_int8_t laser_opt_pwr_lo_al;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
ELS laser optical power high alarm */
	/* 0x24.30 - 0x24.30 */
	/* access: RO */
	u_int8_t laser2_opt_pwr_hi_al;
	/* Description - ELS laser optical power high alarm */
	/* 0x24.31 - 0x24.31 */
	/* access: RO */
	u_int8_t laser_opt_pwr_hi_al;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Bitmask for latched ELS input power low warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x28.0 - 0x28.7 */
	/* access: RO */
	u_int8_t els_input_power_lo_war;
	/* Description - Bitmask for latched ELS input power high warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x28.8 - 0x28.15 */
	/* access: RO */
	u_int8_t els_input_power_hi_war;
	/* Description - Bitmask for latched ELS input power low alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x28.16 - 0x28.23 */
	/* access: RO */
	u_int8_t els_input_power_lo_al;
	/* Description - Bitmask for latched ELS input power high alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x28.24 - 0x28.31 */
	/* access: RO */
	u_int8_t els_input_power_hi_al;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Bitmask for latched OE lane temperature low warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x2c.0 - 0x2c.7 */
	/* access: RO */
	u_int8_t lane_temp_lo_war;
	/* Description - Bitmask for latched OE lane temperature high warning flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x2c.8 - 0x2c.15 */
	/* access: RO */
	u_int8_t lane_temp_hi_war;
	/* Description - Bitmask for latched OE lane temperature low alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x2c.16 - 0x2c.23 */
	/* access: RO */
	u_int8_t lane_temp_lo_al;
	/* Description - Bitmask for latched OE lane temperature high alarm flag per lane.Bit 0 - lane 0... Bit 7 - lane 7 */
	/* 0x2c.24 - 0x2c.31 */
	/* access: RO */
	u_int8_t lane_temp_hi_al;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_switch_pddr_apsu_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The actual state of the RTS update state diagram (IEEE 802.3dj Annex 178B Figure 178B-9).0: START1: WAIT_ADJACENT2: SWITCH_CLOCK3: TX_CLOCK_READY4: FORWARD_RTS */
	/* 0x0.5 - 0x0.7 */
	/* access: RO */
	u_int8_t rts_update_state;
	/* Description - The status of the RTS function. Valid only if apsu_oper = Enabled.0: FAIL: Any lane training failed1: OK: All lanes are OK2: READY: remote_rts is true and training_status is READY3: IN_PROGRESS: training_status is IN_PROGRESS or remote_rts is false and training_status is READY */
	/* 0x0.12 - 0x0.13 */
	/* access: RO */
	u_int8_t training_status;
	/* Description - The status of the RTS function.0: FAIL: Any lane training failed1: TRAINED: training_status is IN_PROGRESS or remote_rts isfalse and training_status is READY2: READY: remote_rts is true and training_status is READY3: OK: All lanes are OK */
	/* 0x0.15 - 0x0.16 */
	/* access: RO */
	u_int8_t rts_status;
	/* Description - Set when ln_local_rx_ready and ln_remote_rx_ready are true for all lanes of the port */
	/* 0x0.18 - 0x0.18 */
	/* access: RO */
	u_int8_t isl_ready;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Peer type. Can be written by the FW in FW control mode and by the SW in independent mode.4: Not detected1: CPO detected2: LPO detected3: FRO detected6: TRO detected7: Not supported */
	/* 0x4.4 - 0x4.6 */
	/* access: RO */
	u_int8_t remote_type;
	/* Description - Set if the remote peer is an Nvidia device. */
	/* 0x4.9 - 0x4.9 */
	/* access: RO */
	u_int8_t peer_detected;
	/* Description - Set if the Not ready to send bit in the ILT received frame is clear for all lanes in the port */
	/* 0x4.10 - 0x4.10 */
	/* access: RO */
	u_int8_t rts_rx_all;
	/* Description - Set when all lanes in the port are ready to send PCS data */
	/* 0x4.11 - 0x4.11 */
	/* access: RO */
	u_int8_t rts_tx_all;
	/* Description - Remote host. Can be written by the FW in FW control mode and by the SW in independent mode.0: Spectrum1: ConnectX */
	/* 0x4.25 - 0x4.27 */
	/* access: RO */
	u_int8_t remote_host_iud;
	/* Description - Indicates that interafce uses recovered clock for transmission.0: For hosts: Spectrum, Quantum, ConnectX1: For retimers: Arcus */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t uses_recovered_clock;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Per-lane APSU status. Array of 8 96-bit elements, 3 DWORDs each
(lane_data[0] at 08h-10h, lane_data[7] at 5Ch-64h). */
	/* 0x8.0 - 0x64.31 */
	/* access: RW */
	struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext lane_data[8];
};

/* Description -   */
/* Size in bytes - 168 */
struct reg_access_switch_pddr_cpo_module_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Represent the OE SN, which matched to the sub module or local port */
	/* 0x0.0 - 0xc.31 */
	/* access: RO */
	u_int32_t oe_sn[4];
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Represent the ELS SN, which matched to the sub module or local port */
	/* 0x10.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t laser_source_sn[4];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Relevant for virtual modules based system. represent the ELS FW version. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t laser_source_fw_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - ELS laser index, relevant when no 8x split. */
	/* 0x24.0 - 0x24.5 */
	/* access: RO */
	u_int8_t els_laser_index;
	/* Description - Sub module */
	/* 0x24.8 - 0x24.11 */
	/* access: RO */
	u_int8_t sub_module;
	/* Description - OE index */
	/* 0x24.16 - 0x24.23 */
	/* access: RO */
	u_int8_t oe_index;
	/* Description - ELS index */
	/* 0x24.24 - 0x24.31 */
	/* access: RO */
	u_int8_t els_index;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - (see above) */
	/* 0x28.0 - 0x28.3 */
	/* access: RO */
	u_int8_t oe_lane7_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.4 - 0x28.7 */
	/* access: RO */
	u_int8_t oe_lane6_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.8 - 0x28.11 */
	/* access: RO */
	u_int8_t oe_lane5_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.12 - 0x28.15 */
	/* access: RO */
	u_int8_t oe_lane4_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.16 - 0x28.19 */
	/* access: RO */
	u_int8_t oe_lane3_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.20 - 0x28.23 */
	/* access: RO */
	u_int8_t oe_lane2_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x28.24 - 0x28.27 */
	/* access: RO */
	u_int8_t oe_lane1_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x28.28 - 0x28.31 */
	/* access: RO */
	u_int8_t oe_lane0_to_els_logical_laser;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Bit mask of valid lanes. */
	/* 0x2c.24 - 0x2c.31 */
	/* access: RO */
	u_int8_t module_lane_mask;
};

/* Description -   */
/* Size in bytes - 140 */
struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Per-lane LT-X FEQ BER iteration database. Array of 2 544-bit
elements, 17 DWORDs each (lane_lt_x_feq_ber[0] at 00h40h,
lane_lt_x_feq_ber[1] at 44h84h). */
	/* 0x0.0 - 0x84.31 */
	/* access: RO */
	struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext lane_lt_x_feq_ber[2];
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Per-port LT-X state and counters. */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	struct reg_access_switch_ef_lt_x_port_info_v1_ext port_info;
};

/* Description -   */
/* Size in bytes - 244 */
struct reg_access_switch_pddr_link_down_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Which receiver caused last link down:0: Unknown1: Local_phy2: Remote_phy */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t down_blame;
	/* Description - For the last link down reason, indicates if the link drop was
intentional (e.g port down command, cable unplug etc...) or
unintentional (e.g Bad SI).down_intent is updated on the link drop according to local reason
information and updated again on LinkUp according to local + peer down
reason (only if negotiation took place during linkup flow)0: Unknown1: intentional2: unintentional */
	/* 0x0.4 - 0x0.7 */
	/* access: RO */
	u_int8_t down_intent;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - (see above) */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t local_reason_opcode;
	/* Description - Opcode of link down reason for local / remote side / last successful
recovery entry reason:Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is
set0: No_link_down_indication1: Unknown_reason2: Hi_BER3: Block_Lock_loss4: Alignment_loss5: FEC_sync_loss6: PLL_lock_loss7: FIFO_overflow8: false_SKIP_condition9: Minor_Error_threshold_exceeded10: Physical_layer_retransmission_timeout11: Heartbeat_errors12: Link_Layer_credit_monitoring_watchdog13: Link_Layer_integrity_threshold_exceeded14: Link_Layer_buffer_overrun15: Down_by_outband_command_with_healthy_link16: Down_by_outband_command_for_link_with_hi_ber17: Down_by_inband_command_with_healthy_link18: Down_by_inband_command_for_link_with_hi_ber19: Down_by_verification_GW20: Received_Remote_Fault21: Received_TS122: Down_by_management_command23: Cable_was_unplugged24: Cable_access_issue25: Cable_Thermal_shutdown26: Current_issue27: Power_budget28: Fast_recovery_raw_ber29: Fast_recovery_effective_ber30: Fast_recovery_symbol_ber31: Fast_recovery_credit_watchdog32: Peer_side_down_to_sleep_state33: Peer_side_down_to_disable_state34: Peer_side_down_to_disable_and_port_lock35: Peer_side_down_due_to_thermal_event36: Peer_side_down_due_to_force_event37: Peer_side_down_due_to_reset_event38: Reset_no_power_cycle39: Fast_recovery_tx_plr_trigger40: Down_due_to_HW_force_event42: L1_exit_failure43: too_many_link_error_recoveries44: Down_due_to_contain_mode45: BW_loss_threshold_exceeded46: ELS_laser_fault47: Hi_SER48: down_by_nmx_adminstate_cmd49: flua_ber_below_threshold_in_guard_time50: Received_Local_Fault51: Received_Link_Interruption52: Manual_debug_mode53: command_triggered_recovery58: Recovery_BW_loss_threshold_exceeded59: Peer_side_down_due_to_contain_mode60: module_unexpected_reset_or_low_power61: Down_due_to_contain_mode_rx62: Down_due_to_contain_mode_tx64: serdes uphy fatal indication65: serdes ophy fatal indication66: down_due_to_rs_fec_consec_bad_cw_threshold_exceeded */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t recovery_entry_reason;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - (see above) */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t remote_reason_opcode;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - see local_reason_opcode for local reason opcodefor remote reason opcode: local_reason_opcode+100 */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t e2e_reason_opcode;
	/* Description - TS1 opcode describes the reason the peer requested to ramp down the
link:0x8: TS1.Sleep0x9: TS1.Disable0xA: TS1.PortLock0xB: TS1.Thermal0xC: TS1.Clean0xD : TS1.Force0xE: TS1.reset_reqNote: This field is valid in case the local_reason_opcode = 21 or 32-38 */
	/* 0xc.12 - 0xc.15 */
	/* access: RO */
	u_int8_t ts1_opcode;
	/* Description - 0: no_info_or_no_l1_failure1: HW_timeout2: FW_timeout3: Recovery_failure */
	/* 0xc.16 - 0xc.19 */
	/* access: RO */
	u_int8_t l1_failure_reason;
	/* Description - last unsuccessful recovery event state0: no_info1: Retrain - no local receiver lock2: WaitRMT - local receiver locked, peer not locked3: IDLE - both local and remote transmitter locked8: Serdes_recovery9: Fix_reversals10: recovery_phyUp */
	/* 0xc.20 - 0xc.23 */
	/* access: RO */
	u_int8_t last_recovery_state;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of Symbol BER Windows that crossed alarm threshold */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t num_of_symbol_ber_alarms;
	/* Description - (see above) */
	/* 0x10.16 - 0x10.23 */
	/* access: RO */
	u_int8_t last_raw_ber_magnitude;
	/* Description - Last raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude) */
	/* 0x10.24 - 0x10.27 */
	/* access: RO */
	u_int8_t last_raw_ber_coef;
	/* Description - Number of last consecutive normal Raw BER windows */
	/* 0x10.28 - 0x10.31 */
	/* access: RO */
	u_int8_t cons_raw_norm_ber;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - (see above) */
	/* 0x14.0 - 0x14.7 */
	/* access: RO */
	u_int8_t max_raw_ber_magnitude;
	/* Description - Maximal raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude) */
	/* 0x14.8 - 0x14.11 */
	/* access: RO */
	u_int8_t max_raw_ber_coef;
	/* Description - (see above) */
	/* 0x14.16 - 0x14.23 */
	/* access: RO */
	u_int8_t min_raw_ber_magnitude;
	/* Description - Minimal raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude) */
	/* 0x14.24 - 0x14.27 */
	/* access: RO */
	u_int8_t min_raw_ber_coef;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Number of Raw BER Windows that crossed alarm threshold */
	/* 0x18.0 - 0x18.15 */
	/* access: RO */
	u_int16_t num_of_raw_ber_alarms;
	/* Description - Number of Effective BER Windows that crossed alarm threshold */
	/* 0x18.16 - 0x18.31 */
	/* access: RO */
	u_int16_t num_of_eff_ber_alarms;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time in msec to link down to disable state, once a paos down is set or a
link down event occurs.If the phy manager state is different then disable the timer will return
0. */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t time_to_link_down_to_disable;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Time in msec to link down to rx disable state, once a link down event
occurs.If the phy manager state is different then rx disable the timer will
return 0. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t time_to_link_down_to_rx_loss;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - (see above) */
	/* 0x24.0 - 0x24.7 */
	/* access: RO */
	u_int8_t min_eff_ber_magnitude;
	/* Description - Minimal effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude) */
	/* 0x24.8 - 0x24.11 */
	/* access: RO */
	u_int8_t min_eff_ber_coef;
	/* Description - (see above) */
	/* 0x24.16 - 0x24.23 */
	/* access: RO */
	u_int8_t last_eff_ber_magnitude;
	/* Description - Last effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude) */
	/* 0x24.24 - 0x24.27 */
	/* access: RO */
	u_int8_t last_eff_ber_coef;
	/* Description - Number of last consecutive normal Effective BER windows */
	/* 0x24.28 - 0x24.31 */
	/* access: RO */
	u_int8_t cons_eff_norm_ber;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - (see above) */
	/* 0x28.0 - 0x28.7 */
	/* access: RO */
	u_int8_t max_eff_ber_magnitude;
	/* Description - Maximal effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude) */
	/* 0x28.8 - 0x28.11 */
	/* access: RO */
	u_int8_t max_eff_ber_coef;
	/* Description - (see above) */
	/* 0x28.16 - 0x28.23 */
	/* access: RO */
	u_int8_t max_symbol_ber_magnitude;
	/* Description - Maximal symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude) */
	/* 0x28.24 - 0x28.27 */
	/* access: RO */
	u_int8_t max_symbol_ber_coef;
	/* Description - Number of last consecutive normal Symbol BER windows */
	/* 0x28.28 - 0x28.31 */
	/* access: RO */
	u_int8_t cons_symbol_norm_ber;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - (see above) */
	/* 0x2c.0 - 0x2c.7 */
	/* access: RO */
	u_int8_t min_symbol_ber_magnitude;
	/* Description - Minimal symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude) */
	/* 0x2c.8 - 0x2c.11 */
	/* access: RO */
	u_int8_t min_symbol_ber_coef;
	/* Description - (see above) */
	/* 0x2c.16 - 0x2c.23 */
	/* access: RO */
	u_int8_t last_symbol_ber_magnitude;
	/* Description - Last symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude) */
	/* 0x2c.24 - 0x2c.27 */
	/* access: RO */
	u_int8_t last_symbol_ber_coef;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Number of hi_ser events since last clear */
	/* 0x30.0 - 0x30.7 */
	/* access: RO */
	u_int8_t hi_ser_counter;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - PCS HW state on link-down, latched:Bits 0-7: Block lock (one bit per lane) - No FEC modeBits 8-15: AM lock (one bit per lane) - RS FEC modeBits 16-23: FEC lock (one bit per lane) - FC FEC modeBit 24: Align_statusBit 25: Hi_BERBit 26: Hi_SERBits 30:27: ReservedBit 31: Active. When set the value of the pcs_phy_state_latched is valid */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t pcs_phy_state_latched;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Opcode for APSU restart reason.0: apsu_restarted_due_to_fail1: apsu_restarted_due_to_link_fail */
	/* 0x38.0 - 0x38.7 */
	/* access: RO */
	u_int8_t apsu_restart_reason_opcode;
};

/* Description -   */
/* Size in bytes - 176 */
struct reg_access_switch_pddr_link_health_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: PASS1: FAIL */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t ltx_status_lane0;
	/* Description - 0: NONE1: EFFECTIVE2: HISTOGRAM3: EFFECTIVE_HISTOGRAM4: RAW5: EFFECTIVE_RAW6: HISTOGRAM_RAW7: EFFECTIVE_HISTOGRAM_RAW8: PRBS9: EFFECTIVE_PRBS10: HISTOGRAM_PRBS11: EFFECTIVE_HISTOGRAM_PRBS12: RAW_PRBS13: EFFECTIVE_RAW_PRBS14: HISTOGRAM_RAW_PRBS15: EFFECTIVE_HISTOGRAM_RAW_PRBS */
	/* 0x0.1 - 0x0.5 */
	/* access: RO */
	u_int8_t ltx_fail_reason_lane0;
	/* Description - Number of times the link quality by fec measure re-checked before the
link came up for lane0.A value of 0 means the link was ready after the first check.A value of 1 means the link needed to be checked twice, and so on. */
	/* 0x0.6 - 0x0.10 */
	/* access: RO */
	u_int8_t ltx_retry_count_lane0;
	/* Description -  */
	/* 0x0.11 - 0x0.15 */
	/* access: RO */
	u_int8_t ltx_retry_count_max_lane0;
	/* Description -  */
	/* 0x0.19 - 0x0.23 */
	/* access: RO */
	u_int8_t hist_target_lane0;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t raw_ber_mag_target_lane0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t raw_ber_mant_target_lane0;
	/* Description -  */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t ltx_logger_index_lane0;
	/* Description - Number of times the link quality by fec measure failed before the link
came up for lane0. */
	/* 0x4.8 - 0x4.12 */
	/* access: RO */
	u_int8_t ltx_retry_fail_count_lane0;
	/* Description -  */
	/* 0x4.13 - 0x4.16 */
	/* access: RO */
	u_int8_t raw_ber_mant_float_target_lane0;
	/* Description - Number of times the link quality by fec measure re-checked before the
link came up per port.A value of 0 means the link was ready after the first check.A value of 1 means the link needed to be checked twice, and so on. */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t fec_measure_retry_count;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 0: PASS1: FAIL */
	/* 0x8.0 - 0x8.0 */
	/* access: RO */
	u_int8_t ltx_status_lane1;
	/* Description - 0: NONE1: EFFECTIVE2: HISTOGRAM3: EFFECTIVE_HISTOGRAM4: RAW5: EFFECTIVE_RAW6: HISTOGRAM_RAW7: EFFECTIVE_HISTOGRAM_RAW8: PRBS9: EFFECTIVE_PRBS10: HISTOGRAM_PRBS11: EFFECTIVE_HISTOGRAM_PRBS12: RAW_PRBS13: EFFECTIVE_RAW_PRBS14: HISTOGRAM_RAW_PRBS15: EFFECTIVE_HISTOGRAM_RAW_PRBS */
	/* 0x8.1 - 0x8.5 */
	/* access: RO */
	u_int8_t ltx_fail_reason_lane1;
	/* Description -  */
	/* 0x8.6 - 0x8.10 */
	/* access: RO */
	u_int8_t ltx_retry_count_lane1;
	/* Description -  */
	/* 0x8.11 - 0x8.15 */
	/* access: RO */
	u_int8_t ltx_retry_count_max_lane1;
	/* Description -  */
	/* 0x8.19 - 0x8.23 */
	/* access: RO */
	u_int8_t hist_target_lane1;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t raw_ber_mag_target_lane1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.3 */
	/* access: RO */
	u_int8_t raw_ber_mant_target_lane1;
	/* Description -  */
	/* 0xc.4 - 0xc.7 */
	/* access: RO */
	u_int8_t ltx_logger_index_lane1;
	/* Description - Number of times the link quality by fec measure failed before the link
came up for lane0. */
	/* 0xc.8 - 0xc.12 */
	/* access: RO */
	u_int8_t ltx_retry_fail_count_lane1;
	/* Description -  */
	/* 0xc.13 - 0xc.16 */
	/* access: RO */
	u_int8_t raw_ber_mant_float_target_lane1;
	/* Description - Number of times the link quality by fec measure failed before the link
came up per port. */
	/* 0xc.24 - 0xc.27 */
	/* access: RO */
	u_int8_t fec_measure_retry_fail_count;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Ltx Logger Page Layout */
	/* 0x10.0 - 0x5c.31 */
	/* access: RO */
	struct reg_access_switch_ltx_logger_ext ltx_logger_lane0[10];
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Ltx Logger Page Layout */
	/* 0x60.0 - 0xac.31 */
	/* access: RO */
	struct reg_access_switch_ltx_logger_ext ltx_logger_lane1[10];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_pddr_link_partner_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - bitmask for supported info0 - field info is not valid.1 - field info is valid.Bit 0: partner_local_port_supportedBit 1: partner_module_type_supportedBit 2: partner_id_lsb_supportedBit 4: peer_ga_idBit 5: partner_id_39_25_supported */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t info_supported_mask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - local_port of link partnerValid only if bit 0 is set in info_supported_mask */
	/* 0x4.0 - 0x4.9 */
	/* access: RO */
	u_int16_t partner_local_port;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - module type of link partner.Module type connected:0: undefined1: Active_Optical_or_Copper_Cable2: Active_Optical_Transceiver3: Passive_Copper_cable5: Twisted_pair6: Far_End_Linear_Equalizer_Cable7: Linear_Optical_Transceiver - (Direct Drive)8: CPO9: Near_end_linear_equalizer_cable10: Fully_linear_equalizer_cable11: Half_retimed_tx_optical_transceiverValid only if bit 1 is set in info_supported_mask */
	/* 0x8.0 - 0x8.3 */
	/* access: RO */
	u_int8_t partner_module_type;
	/* Description - Valid only if Bit 4 is set in info_supported_mask.Indicates the peer port Geographical Adress (GA) OR Module ID in GPU
case */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t peer_ga_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - bits 39 to 25 bits of link partner unique ID:GUID IB InfiniBand linksMAC in Ethernet linksValid only if bit 5 is set in info_supported_mask */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t partner_id_39_25;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - 24 lsb bits of link partner unique ID:GUID IB InfiniBand linksMAC in Ethernet linksValid only if bit 2 is set in info_supported_mask */
	/* 0x10.0 - 0x10.23 */
	/* access: RO */
	u_int32_t partner_id_lsb;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_switch_pddr_link_up_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - invalid port access severity0 - No down command / unknown1 - BMC force linkup2 - WOL force linkup3 - ASN.1 force link up */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t up_reason_mng;
	/* Description - invalid port access severity0 - No down command / unknown1 - Up by at least one of the hosts */
	/* 0x0.8 - 0x0.11 */
	/* access: RO */
	u_int8_t up_reason_drv;
	/* Description - invalid port access severity0 - No down command / unknown1 - Keep link up on boot2 - Keep link up Eth/IB3 - Keep link up on standby */
	/* 0x0.16 - 0x0.19 */
	/* access: RO */
	u_int8_t up_reason_pwr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Time in msec to link up from disable until phy up state.While the phy manager did not reach phy up state the timer will return
0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at
force mode. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t time_to_link_up;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Indicates if fast link-up was performed in the link:0: Unknown1: Fast Link-UP was performed.2: Regular link-up flow was performed due to changes in cable3: Regular link-up flow was performed due to changes in protocol (speed
or FEC)4: Regular link-up flow was performed due to a non-fastbootable FW
version (PCNR is not supported)5: Regular link-up performed due to MLPN flow6: Regular link-up performed due to PCNR.tuning_override configuration
while port was in down state.7: Invalid fastboot data struct (0xCAFECAFE magic value is not present.
For example, SW reset was executed before finish saving data during PCNR
flow)8: fast link-up timeout9: fast link-up flaps issue10: fast link-up failed during link-up */
	/* 0x8.0 - 0x8.3 */
	/* access: RO */
	u_int8_t fast_link_up_status;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Ethernet:Time in msec to link up from phy up until active state.While the phy manager did not reach active state the timer will return
0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at
force mode.IB:Time in msec from entering recovery state until back to Active state in
case of successful recovery */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t time_to_link_up_phy_up_to_active;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Ethernet onlyTime in msec to link up from signal detect until phy up state.While the phy manager did not reach phy up state the timer will return
0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at
force mode. */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t time_to_link_up_sd_to_phy_up;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Ethernet:Time in msec to link up from disable until signal detect state.While the phy manager did not reach signal detect state the timer will
return 0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at
force mode. IB:Time in msec to link up from disable until partner is detected (exit of
Signal detect/receiver detect states). */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t time_to_link_up_disable_to_sd;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Ethernet onlyTime in msec to link up from disable until protocol detect state.While the phy manager did not reach protocol detect state the timer will
return 0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at
force mode. */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t time_to_link_up_disable_to_pd;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time in msec of phy2mod command response of module conf done in port up
case */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t time_of_module_conf_done_up;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Time in msec of phy2mod command response of module conf done in port
down case */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t time_of_module_conf_done_down;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Time in mSec that it takes for the port logical state to transition from
init to an active state.The timer reset to 0 ONLY when the logical port state goes down. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t time_logical_init_to_active;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Total time in sec of PCS state of Local Fault */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t total_time_pcs_local_fault;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Total time in sec of PCS state of Remote Fault */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t total_time_pcs_remote_fault;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Time duration of last hi_ser event.value reset every new hi_ser event. */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t time_on_last_hi_ser;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Duration of last phy data collection period conducted by FW Phy
following a single timeline event trigger. This indicates the overall
duration it took to complete the FW Phy data collection thread.Value is reset every new data collection trigger. If in the last trigger
there was no requirement to collect FW Phy data field should return 0.Value is in units of 1 [msec] */
	/* 0x34.0 - 0x34.15 */
	/* access: RO */
	u_int16_t last_phy_data_groups_collection_time;
	/* Description - Duration of last data collection period conducted by FW Phy following a
single timeline event trigger. This indicates the overall duration it
took to complete all different collection threads.Value is reset every new data collection trigger.Value is in units of 1 [msec] */
	/* 0x34.16 - 0x34.31 */
	/* access: RO */
	u_int16_t last_data_groups_collection_time;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Duration of last module data collection period conducted by FW Phy
following a single timeline event trigger. This indicates the overall
duration it took to complete the System Module data collection thread.Value is reset every new data collection trigger. If in the last trigger
there was no requirement to collect module data field should return 0.Value is in units of 1 [msec] */
	/* 0x38.0 - 0x38.15 */
	/* access: RO */
	u_int16_t last_module_data_groups_collection_time;
	/* Description - Duration of last SerDes data collection period conducted by FW Phy
following a single timeline event trigger. This indicates the overall
duration it took to complete the FW Serdes data collection thread.Value is reset every new data collection trigger. If in the last trigger
there was no requirement to collect UPHY data field should return 0.Value is in units of 1 [msec] */
	/* 0x38.16 - 0x38.31 */
	/* access: RO */
	u_int16_t last_serdes_data_groups_collection_time;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Duration of the last APSU until data is transmitted in seconds */
	/* 0x40.0 - 0x40.11 */
	/* access: RO */
	u_int16_t apsu_total_time;
	/* Description - Duration of the last link training function of APSU in seconds */
	/* 0x40.16 - 0x40.27 */
	/* access: RO */
	u_int16_t apsu_ilt_time;
};

/* Description -   */
/* Size in bytes - 208 */
struct reg_access_switch_pddr_module_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - QSFP:Ethernet Compliance Codes bit mask (10/40G/100G)Byte131 per SFF-8636Bit 7 - Extended Specification Compliance validBit 6 - 10GBASE-LRMBit 5 - 10GBASE-LRBit 4 - 10GBASE-SRBit 3 - 40GBASE-CR4Bit 2 - 40GBASE-SR4Bit 1 - 40GBASE-LR4Bit 0 - 40G Active Cable (XLPPI)SFP:10G Ethernet Compliance CodesByte3 per SFF-8472:Bit 7 - 10G Base-ERBit 6 - 10G Base-LRMBit 5 - 10G Base-LRBit 4 - 10G Base-SRCMIS based (QSFP-DD/ SFP-DD / OSFP/OE)Byte 87 - Module Media Interface */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t ethernet_compliance_code;
	/* Description - Extended Specification Compliance Codesfor SFP:byte 36 per SFF-8472for QSFP:byte192 per SFF-8636 (QSFP28)for CMIS (SFP-DD / QSFP-DD/ OSFP/OE):Byte 86 - Host Electrical Interface */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t ext_ethernet_compliance_code;
	/* Description - Reserved for SFP.For QSFP:Byte113 per SFF-8636For CMIS based modules:XX naming is according to cable_identifier nameFor example: if cable_identifier = ,6 XX string is QSFP-DD0 - Unspecified1 - XX to XX2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)4 - XX to 8xSFP5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or
2xSFP-DD7 - XX (depopulated / 4 lanes) to 4xSFP8 - XX(/ 2 lane module) to XX9 - XX(/ 2 lane module) to 2xSFP */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t cable_breakout;
	/* Description - QSFP:Byte 147 per SFF-8636.SFP:SFP+ Cable Technology:byte8 per SFF-8472:Bit 3 - Active CableBit 2 - Passive CableCMIS based (QSFP-DD / OSFP/ SFP-DD/OE):Byte 2120x00: VCSEL_850nm0x01: VCSEL_1310nm0x02: VCSEL_1550nm0x03: FP_laser_1310nm0x04: DFB_laser_1310nm0x05: DFB_laser_1550nm0x06: EML_1310nm0x07: EML_1550nm0x08: others0x09: DFB_laser_1490nm0x0a: Passive_copper_cable_unequalized0x0b: Passive_copper_cable_equalized0x0c: Copper_cable_near_end_and_far_end_limiting_active_equailizer0x0d: Copper_cable_far_end_limiting_active_equailizer0x0e: Copper_cable_near_end_limiting_active_equializer0x0f: Copper_cable_linear_active_equalizers0x10: c_band_tunable_laser0x11: l_band_tunable_laser0x12: Copper_cable_near_end_and_far_end_linear_active_equalizers0x13: Copper_cable_far_end_linear_active_equalizers0x14:Copper_cable_near_end_linear_active_equalizersnote - passive copper = 0xbLinear coppers = 0xF or 0x12 or 0x13 or 0x14 */
	/* 0x0.24 - 0x0.31 */
	/* access: RW */
	u_int8_t cable_technology;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module maximum power consumption for SFP/QSFP:0: Power_Class_0 - (1.0 W max)1: Power_Class_1 - (1.5 W max)2: Power_Class_2 - (2.0 W max)3: Power_Class_3 - (2.5 W max)4: Power_Class_4 - (3.5 W max)5: Power_Class_5 - (4.0 W max)6: Power_Class_6 - (4.5 W max)7: Power_Class_7 - (5.0 W max)8: Power_Class_8 - (power from max_power field)Module maximum power consumption for SFP-DD:0: Power_Class_0 - (0.5 W max)1: Power_Class_1 - (1.0 W max)2: Power_Class_2 - (1.5 W max)3: Power_Class_3 - (2.0 W max)4: Power_Class_4 - (3.5 W max)5: Power_Class_5 - (5.0 W max)6: reserved7: reserved8: Power_Class_8 - (power from max_power field)Module maximum power consumption for QSFP-DD/OSFP:1 - Power_Class_1 - (1.5 W max)2 - Power_Class_2 - (3.5 W max)3 - Power_Class_3 - (7.0 W max)4 - Power_Class_4 - (8.0 W max)5 - Power_Class_5 - (10 W max)6 - Power_Class_6 - (12 W max)7 - Power_Class_7 - (14 W max)8 - Power_Class_8 - (power from max_power field) */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t cable_power_class;
	/* Description - 0: QSFP281: QSFP_Plus2: SFP28_or_SFP_Plus3: QSA - (QSFP->SFP)4: Backplane5: SFP_DD6: QSFP_DD7: QSFP_CMIS8: OSFP9: C2C10: DSFP11: QSFP_Split_Cable12: CPO13: OE14: ELS15: NPOidentifiers that are compliant to CMIS : 5,6,7,8,10,12,14,15 */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t cable_identifier;
	/* Description - Cable length in 1m units.For CMIS modules:bits 6:7 represent cable_length_multiplier for calculating cable length00 - 0.1 multiplier (0.1 to 6.3m)01- 1 multiplier (1 to 63m)10 - 10 multiplier (10 to 630m)11 - 100 multiplier (100 to 6300m)bits 0:5 represent cable_length_value for calculating cable length.length is calculated with cable_length_value * cable_length_multiplier */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t cable_length;
	/* Description - Cable vendor:0: Other1: Mellanox2: Known_OUI3: NVIDIA */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t cable_vendor;
	/* Description - Cable/module type:0: Unidentified1: Active_cable - (active copper / optics)2: Optical_Module - (separated)3: Passive_copper_cable_or_linear_copper - for distinguishing passive
copper and linear copper see cable_technology4: Cable_unplugged5: Twisted_pair6: CPO7: OE8: ELS */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t cable_type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t cable_tx_equalization;
	/* Description - For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-emphasis. */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t cable_rx_emphasis;
	/* Description - Reserved for SFP */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t cable_rx_amp;
	/* Description - Reserved for SFP, QSFPByte 201 for CMIS (QSFP-DD/ SFP-DD/
OSFP/ELS/OE)Other Cable ignore field. */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t max_power;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Reserved for SFP */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t cable_attenuation_5g;
	/* Description - Reserved for SFP */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t cable_attenuation_7g;
	/* Description - Reserved for SFP */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t cable_attenuation_12g;
	/* Description - Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)Other Cable ignore field. */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t cable_attenuation_25g;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Reserved for SFPBit 0 - TX CDR on/off on channel 0Bit 1 - TX CDR on/off on channel 1Bit 2 - TX CDR on/off on channel 2Bit 3 - TX CDR on/off on channel 3Bit 4 - TX CDR on/off on channel 4Bit 5 - TX CDR on/off on channel 5Bit 6 - TX CDR on/off on channel 6Bit 7 - TX CDR on/off on channel 7CDR on - when bit is set.CDR off - when bit is clear. */
	/* 0x10.0 - 0x10.7 */
	/* access: RO */
	u_int8_t tx_cdr_state;
	/* Description - Reserved for SFPBit 0 - RX CDR on/off on channel 0Bit 1 - RX CDR on/off on channel 1Bit 2 - RX CDR on/off on channel 2Bit 3 - RX CDR on/off on channel 3Bit 4 - RX CDR on/off on channel 4Bit 5 - RX CDR on/off on channel 5Bit 6 - RX CDR on/off on channel 6Bit 7 - RX CDR on/off on channel 7CDR on - when bit is set.CDR off - when bit is clear. */
	/* 0x10.8 - 0x10.15 */
	/* access: RO */
	u_int8_t rx_cdr_state;
	/* Description - 0 - No CDR1 - Build-in CDR with on/off control2 - Build-in CDR without on/off control */
	/* 0x10.16 - 0x10.19 */
	/* access: RO */
	u_int8_t tx_cdr_cap;
	/* Description - 0 - No CDR1 - Build-in CDR with on/off control2 - Build-in CDR without on/off control */
	/* 0x10.20 - 0x10.23 */
	/* access: RO */
	u_int8_t rx_cdr_cap;
	/* Description - Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)Rx post-emphasis. */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t cable_rx_post_emphasis;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - ASCII Vendor name left-aligned and padded on the right withASCII spaces (20h) */
	/* 0x14.0 - 0x20.31 */
	/* access: RO */
	u_int32_t vendor_name[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Vendor Part Number left-aligned and padded on the right with ASCII
spaces (20h) */
	/* 0x24.0 - 0x30.31 */
	/* access: RO */
	u_int32_t vendor_pn[4];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - ASCII Vendor revision aligned to right padded with 0h on the left */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t vendor_rev;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - If information is not available by the module: set to 0 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t fw_version;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Vendor Serial Number */
	/* 0x3c.0 - 0x48.31 */
	/* access: RO */
	u_int32_t vendor_sn[4];
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - U16 Supply Voltage Monitor as defined in SFF-8636/CMIS.Internally measured supply voltage in 100uV */
	/* 0x4c.0 - 0x4c.15 */
	/* access: RO */
	u_int16_t voltage;
	/* Description - S16 Module Temperature Monitor as defined in SFF-8636/CMIS.module temperature in 1/256 CValue of 0 may indicate not supported or real temperature value. */
	/* 0x4c.16 - 0x4c.31 */
	/* access: RO */
	u_int16_t temperature;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - RX measured power channel 1.measured in dBm/uW according to module_info_ext value */
	/* 0x50.0 - 0x50.15 */
	/* access: RO */
	u_int16_t rx_power_lane1;
	/* Description - RX measured power channel 0.measured in dBm/uW according to module_info_ext value */
	/* 0x50.16 - 0x50.31 */
	/* access: RO */
	u_int16_t rx_power_lane0;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - RX measured power channel 3.measured in dBm/uW according to module_info_ext value */
	/* 0x54.0 - 0x54.15 */
	/* access: RO */
	u_int16_t rx_power_lane3;
	/* Description - RX measured power channel 2.measured in dBm/uW according to module_info_ext value */
	/* 0x54.16 - 0x54.31 */
	/* access: RO */
	u_int16_t rx_power_lane2;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - RX measured power channel 5.measured in dBm/uW according to module_info_ext value */
	/* 0x58.0 - 0x58.15 */
	/* access: RO */
	u_int16_t rx_power_lane5;
	/* Description - RX measured power channel 4.measured in dBm/uW according to module_info_ext value */
	/* 0x58.16 - 0x58.31 */
	/* access: RO */
	u_int16_t rx_power_lane4;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - RX measured power channel 7.measured in dBm/uW according to module_info_ext value */
	/* 0x5c.0 - 0x5c.15 */
	/* access: RO */
	u_int16_t rx_power_lane7;
	/* Description - RX measured power channel 6.measured in dBm/uW according to module_info_ext value */
	/* 0x5c.16 - 0x5c.31 */
	/* access: RO */
	u_int16_t rx_power_lane6;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - TX measured power channel 1.measured in dBm/uW according to module_info_ext value */
	/* 0x60.0 - 0x60.15 */
	/* access: RO */
	u_int16_t tx_power_lane1;
	/* Description - TX measured power channel 0.measured in dBm/uW according to module_info_ext value */
	/* 0x60.16 - 0x60.31 */
	/* access: RO */
	u_int16_t tx_power_lane0;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - TX measured power channel 3.measured in dBm/uW according to module_info_ext value */
	/* 0x64.0 - 0x64.15 */
	/* access: RO */
	u_int16_t tx_power_lane3;
	/* Description - TX measured power channel 2.measured in dBm/uW according to module_info_ext value */
	/* 0x64.16 - 0x64.31 */
	/* access: RO */
	u_int16_t tx_power_lane2;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - TX measured power channel 5.measured in dBm/uW according to module_info_ext value */
	/* 0x68.0 - 0x68.15 */
	/* access: RO */
	u_int16_t tx_power_lane5;
	/* Description - TX measured power channel 4.measured in dBm/uW according to module_info_ext value */
	/* 0x68.16 - 0x68.31 */
	/* access: RO */
	u_int16_t tx_power_lane4;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - TX measured power channel 7.measured in dBm/uW according to module_info_ext value */
	/* 0x6c.0 - 0x6c.15 */
	/* access: RO */
	u_int16_t tx_power_lane7;
	/* Description - TX measured power channel 6.measured in dBm/uW according to module_info_ext value */
	/* 0x6c.16 - 0x6c.31 */
	/* access: RO */
	u_int16_t tx_power_lane6;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - (see above) */
	/* 0x70.0 - 0x70.15 */
	/* access: RO */
	u_int16_t tx_bias_lane1;
	/* Description - TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x70.16 - 0x70.31 */
	/* access: RO */
	u_int16_t tx_bias_lane0;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - (see above) */
	/* 0x74.0 - 0x74.15 */
	/* access: RO */
	u_int16_t tx_bias_lane3;
	/* Description - TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x74.16 - 0x74.31 */
	/* access: RO */
	u_int16_t tx_bias_lane2;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - (see above) */
	/* 0x78.0 - 0x78.15 */
	/* access: RO */
	u_int16_t tx_bias_lane5;
	/* Description - TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x78.16 - 0x78.31 */
	/* access: RO */
	u_int16_t tx_bias_lane4;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - (see above) */
	/* 0x7c.0 - 0x7c.15 */
	/* access: RO */
	u_int16_t tx_bias_lane7;
	/* Description - TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x7c.16 - 0x7c.31 */
	/* access: RO */
	u_int16_t tx_bias_lane6;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Alarm low temperature threshold in 1/256 C */
	/* 0x80.0 - 0x80.15 */
	/* access: RO */
	u_int16_t temperature_low_th;
	/* Description - Alarm high temperature threshold in 1/256 C */
	/* 0x80.16 - 0x80.31 */
	/* access: RO */
	u_int16_t temperature_high_th;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - Alarm low Voltage threshold in 100uV */
	/* 0x84.0 - 0x84.15 */
	/* access: RO */
	u_int16_t voltage_low_th;
	/* Description - Alarm high Voltage threshold in 100uV */
	/* 0x84.16 - 0x84.31 */
	/* access: RO */
	u_int16_t voltage_high_th;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Alarm low RX Power threshold in dBm.Taking only from channel 0. */
	/* 0x88.0 - 0x88.15 */
	/* access: RO */
	u_int16_t rx_power_low_th;
	/* Description - Alarm high RX Power threshold in dBm.Taking only from channel 0. */
	/* 0x88.16 - 0x88.31 */
	/* access: RO */
	u_int16_t rx_power_high_th;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - Alarm low TX Power threshold in dBm.Taking only from channel 0. */
	/* 0x8c.0 - 0x8c.15 */
	/* access: RO */
	u_int16_t tx_power_low_th;
	/* Description - Alarm high TX Power threshold in dBm.Taking only from channel 0. */
	/* 0x8c.16 - 0x8c.31 */
	/* access: RO */
	u_int16_t tx_power_high_th;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - Alarm low TX Bias current threshold in 2 uA.The real threshold value in uA units should be calculated as follows:tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x90.0 - 0x90.15 */
	/* access: RO */
	u_int16_t tx_bias_low_th;
	/* Description - Alarm high TX Bias current threshold in 2 uA.The real threshold value in uA units should be calculated as follows:tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x90.16 - 0x90.31 */
	/* access: RO */
	u_int16_t tx_bias_high_th;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - Nominal laser wavelength in nm */
	/* 0x94.0 - 0x94.15 */
	/* access: RO */
	u_int16_t wavelength;
	/* Description - SMF link lengthSFP per byte 14,15.QSFP per byte 142for CMIS based modules, per byte 132bit 9:8 - 00 length base in 1 km unitsbit 9:8 - 01 length base in 100m unitsbits 7:0 - length base */
	/* 0x94.16 - 0x94.25 */
	/* access: RO */
	u_int16_t smf_length;
	/* Description - when set, indicates rx_output_valid is supported by the module */
	/* 0x94.26 - 0x94.26 */
	/* access: RW */
	u_int8_t rx_output_valid_cap;
	/* Description - set in case of Linear Direct Drive module */
	/* 0x94.27 - 0x94.27 */
	/* access: RO */
	u_int8_t did_cap;
	/* Description - rx power measurement type0: OMA1: Average_power */
	/* 0x94.28 - 0x94.28 */
	/* access: RO */
	u_int8_t rx_power_type;
	/* Description - Valid for CMIS modules only.Module state:0: reserved1: LowPwr_state2: PwrUp_state3: Ready_state4: PwrDn_state5: Fault_state */
	/* 0x94.29 - 0x94.31 */
	/* access: RO */
	u_int8_t module_st;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - Byte 164 of SFF-8636For CMIS modules IB Protocols:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR */
	/* 0x98.0 - 0x98.9 */
	/* access: RO */
	u_int16_t ib_compliance_code;
	/* Description - Valid for CMIS modules only.This field is relevant for the following fields: tx_bias_lane[7:0],
tx_bias_high_th and tx_bias_low_th.The value of the above fields should be multiplied according to the
tx_bias_scaling_factor value.0: multiply_1x1: multiply_2x2: multiply_4x */
	/* 0x98.10 - 0x98.11 */
	/* access: RO */
	u_int8_t tx_bias_scaling_factor;
	/* Description - Valid for CMIS modules only.According to current Active set, value of Module Media Interface byte */
	/* 0x98.16 - 0x98.23 */
	/* access: RO */
	u_int8_t active_set_media_compliance_code;
	/* Description - Valid for CMIS modules only.According to current Active set, value of Host Electrical Interface byte */
	/* 0x98.24 - 0x98.31 */
	/* access: RO */
	u_int8_t active_set_host_compliance_code;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - Bitmask of width of IB Protocols */
	/* 0x9c.0 - 0x9c.5 */
	/* access: RO */
	u_int8_t ib_width;
	/* Description - monitoring capabilities maskBit 0 - temperature monitoring implementedBit 1 - voltage monitoring implementedBit 2 - tx power monitoring implementedBit 3 - rx power monitoring implementedBit 4 - tx bias monitoring implemented */
	/* 0x9c.8 - 0x9c.15 */
	/* access: RO */
	u_int8_t monitor_cap_mask;
	/* Description - Nominal bit rate in units of 100Mb/s */
	/* 0x9c.16 - 0x9c.23 */
	/* access: RO */
	u_int8_t nbr100;
	/* Description - Nominal bit rate in units of 250Mb/s */
	/* 0x9c.24 - 0x9c.31 */
	/* access: RO */
	u_int8_t nbr250;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - DataPath state for lane<i>1: DPDeactivated2: DPInit3: DPDeinit4: DPActivated5: DPTxTurnOn6: DPTxTurnOff7: DPInitialized */
	/* 0xa0.28 - 0xa4.27 */
	/* access: RO */
	u_int8_t dp_st_lane[8];
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - OM5 fiber length supported in units of 2m */
	/* 0xa4.0 - 0xa4.7 */
	/* access: RO */
	u_int8_t length_om5;
	/* Description - OM4 fiber length supported in units of 2mSFP in units of 10m */
	/* 0xa4.8 - 0xa4.15 */
	/* access: RO */
	u_int8_t length_om4;
	/* Description - OM3 fiber length supported in units of 2mSFP in units of 10m */
	/* 0xa4.16 - 0xa4.23 */
	/* access: RO */
	u_int8_t length_om3;
	/* Description - OM2 fiber length supported in units of 1mSFP in units of 10m */
	/* 0xa4.24 - 0xa4.31 */
	/* access: RO */
	u_int8_t length_om2;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - memory map revision */
	/* 0xa8.0 - 0xa8.7 */
	/* access: RO */
	u_int8_t memory_map_rev;
	/* Description - 16-bit integer value for the laser wavelength tolerance in nm divided by
200 (units of 0.005nm). */
	/* 0xa8.8 - 0xa8.23 */
	/* access: RO */
	u_int16_t wavelength_tolerance;
	/* Description - OM1 fiber length supported in units of 10m */
	/* 0xa8.24 - 0xa8.31 */
	/* access: RO */
	u_int8_t length_om1;
/*---------------- DWORD[43] (Offset 0xac) ----------------*/
	/* Description - memory map compliance in ASCII.SFF-8472 / SFF-8636/ CMIS */
	/* 0xac.0 - 0xac.31 */
	/* access: RO */
	u_int32_t memory_map_compliance;
/*---------------- DWORD[44] (Offset 0xb0) ----------------*/
	/* Description - ASCII code for vendor's date code.63:48- 2 digit for date code year, 00 = year 200047:32 - 2 digit for date code month.31:16 - 2 digit for day of the month code.15:0 - 2 digit LOT code. */
	/* 0xb0.0 - 0xb4.31 */
	/* access: RO */
	u_int64_t date_code;
/*---------------- DWORD[46] (Offset 0xb8) ----------------*/
	/* Description - vendor oui */
	/* 0xb8.0 - 0xb8.23 */
	/* access: RO */
	u_int32_t vendor_oui;
	/* Description - connector type based on SFF-8024 */
	/* 0xb8.24 - 0xb8.31 */
	/* access: RO */
	u_int8_t connector_type;
/*---------------- DWORD[47] (Offset 0xbc) ----------------*/
	/* Description - Rx output status indication per lane */
	/* 0xbc.0 - 0xbc.7 */
	/* access: RO */
	u_int8_t rx_output_valid;
	/* Description - cable attenuation at 53GHz */
	/* 0xbc.8 - 0xbc.15 */
	/* access: RO */
	u_int8_t cable_attenuation_53g;
	/* Description - Defines which Tx input lanes must be frequency synchronous.0: Tx_input_lanes_1_81: Tx_input_lanes_1_4_and_5-82: Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_83: Lanes_may_be_asynchronous_in_frequency */
	/* 0xbc.16 - 0xbc.17 */
	/* access: RO */
	u_int8_t tx_input_freq_sync;
	/* Description - Module advertisement for NVDA event data collection logger */
	/* 0xbc.19 - 0xbc.19 */
	/* access: RO */
	u_int8_t event_logger_cap;
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description - Relevant for CMIS modules only.Error Code response for ControlSet configuration of DataPath.0x0: ConfigUndefined0x1: ConfigSuccess0x2: ConfigRejected0x3: ConfigRejectedInvalidAppSel0x4: ConfigRejectedInvalidDataPath0x5: ConfigRejectedInvalidSI0x6: ConfigRejectedLanesInUse0x7: ConfigRejectedPartialDataPath0xC: ConfigInProgress0xD: ConfigRejectedInvalid_VS_SI - NVIDIA vendor only */
	/* 0xc0.0 - 0xc0.3 */
	/* access: RO */
	u_int8_t error_code;
	/* Description - Relevant for CMIS modules only0x0: Unknown_or_no_CDR0x1: Inphy_gen1_polaris0x2: Inphy_gen2_Atlas0x3: Marvell_Spica_Plus0x4: Brdcm_Portofino_or_gemera0x5: Nvidia_ArcusE0x6: Marvell_nova2or_ara0x7: Macom_linear_equalizer0x8: Semec_linear_equalizer0x9: Marvel_linear_equalizer0xA: Marvel_spica_5nm0xB: luxic_linear_equalizer0xC: Broadcom_sian2_or_30xD: Arcus2 */
	/* 0xc0.4 - 0xc0.7 */
	/* access: RO */
	u_int8_t cdr_vendor;
	/* Description - Fuse revition for Optical Engine. Relevant for Taipan */
	/* 0xc0.13 - 0xc0.15 */
	/* access: RO */
	u_int8_t oe_fuse_rev;
	/* Description - Maximum length of allowed fiber in meters */
	/* 0xc0.16 - 0xc0.31 */
	/* access: RO */
	u_int16_t max_fiber_length;
/*---------------- DWORD[49] (Offset 0xc4) ----------------*/
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
indicate the ELS laser fault:0: no_fault1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault */
	/* 0xc4.10 - 0xc4.12 */
	/* access: RO */
	u_int8_t els_laser2_fault_state;
	/* Description - Indicate the ELS laser fault.0: no_fault1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault */
	/* 0xc4.13 - 0xc4.15 */
	/* access: RO */
	u_int8_t els_laser_fault_state;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
Indicates the ELS laser operative state:0: laser_init1: laser_active2: laser_active_with_fault3: laser_down4: laser_down_with_fault */
	/* 0xc4.16 - 0xc4.19 */
	/* access: RO */
	u_int8_t els2_oper_state;
	/* Description - Indicates the ELS laser operative state:0: laser_init1: laser_active2: laser_active_with_fault3: laser_down4: laser_down_with_fault */
	/* 0xc4.20 - 0xc4.23 */
	/* access: RO */
	u_int8_t els_oper_state;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
Each bit represent the ELS's laser restriction. When restriction are on,
the laser can operate only in restricted power mode, for the safety of
the optical components. Restriction can be lifted only after fiber
testing.0: laser2_restriction_on1: laser2_restriction_off */
	/* 0xc4.24 - 0xc4.24 */
	/* access: RO */
	u_int8_t laser2_restriction;
	/* Description - Relevant for CPO product. Each bit represent the ELS's laser
restriction. When restriction are on, the laser can operate only in
restricted power mode, for the safety of the optical components.
Restriction can be lifted only after fiber testing.0: laser_restriction_on1: laser_restriction_off */
	/* 0xc4.25 - 0xc4.25 */
	/* access: RO */
	u_int8_t laser_restriction;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
Each bit represent the ELS's laser status CMIS name of field.0: laser2_off1: laser2_ramping2: laser2_on */
	/* 0xc4.26 - 0xc4.27 */
	/* access: RO */
	u_int8_t laser2_status;
	/* Description - Relevant for CPO product. Each bit represent the ELS's laser status CMIS
name of field.0: laser_off1: laser_ramping2: laser_on */
	/* 0xc4.28 - 0xc4.29 */
	/* access: RO */
	u_int8_t laser_status;
	/* Description - Relevant for CPO ETH switches. when 8x port split is applied, this
fields represent the ELS laser with the higher logical mapping index.
Each bit represent the ELS's laser.0: laser2_disabled1: laser2_enabled */
	/* 0xc4.30 - 0xc4.30 */
	/* access: RO */
	u_int8_t laser2_enabled;
	/* Description - Relevant for CPO product. Each bit represent the ELS's laser.0: laser_disabled1: laser_enabled */
	/* 0xc4.31 - 0xc4.31 */
	/* access: RO */
	u_int8_t laser_enabled;
/*---------------- DWORD[50] (Offset 0xc8) ----------------*/
	/* Description - Pluggable module production test version. Lower 32 bits. */
	/* 0xc8.0 - 0xc8.31 */
	/* access: RO */
	u_int32_t module_production_test_revision_lsb;
/*---------------- DWORD[51] (Offset 0xcc) ----------------*/
	/* Description - Module Hardware Revision Minor */
	/* 0xcc.0 - 0xcc.7 */
	/* access: RO */
	u_int8_t module_hw_revision_minor;
	/* Description - Module Hardware Revision Major */
	/* 0xcc.8 - 0xcc.15 */
	/* access: RO */
	u_int8_t module_hw_revision_major;
	/* Description - Pluggable module production test version. Upper 8 bits. */
	/* 0xcc.24 - 0xcc.31 */
	/* access: RO */
	u_int8_t module_production_test_revision_msb;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_switch_pddr_operation_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: protocol_was_not_negotiated - (force mode)1: MLPN_rev0_negotiated2: CL73_Ethernet_negotiated3: Protocol_according_to_Parallel_detect - (remote port in force
mode)4: Standard_IB_negotiated */
	/* 0x0.16 - 0x0.19 */
	/* access: RO */
	u_int8_t neg_mode_active;
	/* Description - Active protocol:Bit 0: InfiniBandBit 2: EthernetBit 3: NVLink */
	/* 0x0.20 - 0x0.23 */
	/* access: RO */
	u_int8_t proto_active;
	/* Description - Valid only for resilink link is operational, otherwise ignored.When cleared, fec_mode_active will represent the Ethernet equivalent FEC
of the resilink protocol.When set, fec_mode_active will represent the Resilink FEC protocol */
	/* 0x0.28 - 0x0.28 */
	/* access: INDEX */
	u_int8_t resilink_fec_ind;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - FW IB state machine:0x0: IB_AN_FSM_DISABLED0x1: IB_AN_FSM_INITIALY0x2: IB_AN_FSM_RCVR_CFG0x3: IB_AN_FSM_CFG_TEST0x4: IB_AN_FSM_WAIT_RMT_TEST0x5: IB_AN_FSM_WAIT_CFG_ENHANCED0x6: IB_AN_FSM_CFG_IDLE0x7: IB_AN_FSM_LINK_UP0x8: IB_AN_FSM_POLLING */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ib_phy_fsm_state;
	/* Description - Ethernet (CL73) Auto-negotiation FSM state:0x0: ETH_AN_FSM_ENABLE0x1: ETH_AN_FSM_XMIT_DISABLE0x2: ETH_AN_FSM_ABILITY_DETECT0x3: ETH_AN_FSM_ACK_DETECT0x4: ETH_AN_FSM_COMPLETE_ACK0x5: ETH_AN_FSM_AN_GOOD_CHECK0x6: ETH_AN_FSM_AN_GOOD0x7: ETH_AN_FSM_NEXT_PAGE_WAIT */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t eth_an_fsm_state;
	/* Description - FW Phy Manager FSM state:0: Disabled1: Open_port2: Polling3: Active4: Close_port5: Phy_up6: Sleep7: Rx_disable8: Signal_detect9: Receiver_detect10: Sync_peer11: Negotiation12: Training13: SubFSM_active14: Protocol_Detect15: Unkown16: Reserved17: Waiting_state */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t phy_mngr_fsm_state;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For IB:
PDDR - Phy Manager Link Enabled IB LayoutFor Ethernet:
PDDR - Phy Manager Link Enabled Eth LayoutFor NVLink:
PDDR - Phy Manager Link Enable NVLink Layout */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext phy_manager_link_enabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For IB:
PDDR - Core2phy Link Enabled IB LayoutFor Ethernet:
PDDR - Core2phy Link Enabled Eth LayoutFor NVLink:
PDDR - Core2phy Link Enabled NVLink Layout */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext core_to_phy_link_enabled;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - For IB:
PDDR - Cable Cap IB LayoutFor Ethernet:
PDDR - Cable Cap Eth LayoutFor NVLink:
PDDR - Cable Cap NVLink Layout */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext cable_proto_cap;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - For IB:
PDDR - Link Active IB LayoutFor Ethernet:
PDDR - Link Active Eth LayoutFor NVLink:
PDDR - Link Active NVLink Layout */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_link_active_auto_ext link_active;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - 0: No_loopback_active1: Phy_remote_loopback2: Phy_local_loopback -When set the port's egress traffic is looped
back to the receiver and the port transmitter is disabled.4: External_local_loopback -Enables the port's transmitter to link
with the port's receiver using an external loopback connector. */
	/* 0x18.0 - 0x18.11 */
	/* access: RO */
	u_int16_t loopback_mode;
	/* Description - Indicates for Mode B links if the port was chosen as primary or
secondary during linkup.0: Not_supported_or_not_chosen_yet.1: Primary2: Secondary */
	/* 0x18.14 - 0x18.15 */
	/* access: RO */
	u_int8_t pri_or_sec;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - FEC mode request.See . */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t fec_mode_request;
	/* Description - FEC mode active0: No_FEC1: Firecode_FEC2: Standard_RS_FEC - RS(528,514)3: Standard_LL_RS_FEC - RS(271,257)4: Interleaved_Quad_RS_FEC - (544,514)   Quad_KP4_FEC5: Interleaved_Quad_RS_FEC_PLR - 546,516) Quad_KP4_FEC6: Interleaved_Standard_RS-FEC - (544,514)7: Standard_RS_KP4_FEC - (544,514)8: Interleaved_Octet_RS_FEC_PLR -(546,516) Octet_KP4_FEC9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)11: Interleaved_Standard_RS_FEC_PLR - (544,514)12: RS-FEC - (544,514) + PLR- [Internal]13: LL-FEC - (271,257) + PLR- [Internal]14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]16: Interleaved_Double_RS_Half_KP4_FEC_PLR - (288,258)17: Interleaved_Quad_RS_Half_KP4_FEC_PLR - (288,258)18: Interleaved_Octet_RS_Half_KP4_FEC_PLR - (288,258) */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t fec_mode_active;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - FEC 100G (25Gb/s per lane) supported FEC include override masking,
should reflect current phy configuration after link is upBit 0 - No FECBit 2 - Standard RS-FEC - RS(528,514) */
	/* 0x20.0 - 0x20.3 */
	/* access: RO */
	u_int8_t eth_100g_fec_support;
	/* Description - FEC 25G/50G (25Gb/s per lane) supported FEC include override masking,
should reflect current phy configuration after link is upBit 0 - No FECBit 1 - Firecode FECBit 2 - Standard RS-FEC - RS(528,514) */
	/* 0x20.4 - 0x20.7 */
	/* access: RO */
	u_int8_t eth_25g_50g_fec_support;
	/* Description - The profile that has been selected:Bit 0 - IB spec / legacy (See profiles description)Bit 1 - internal ports (Backplane)Bit 2 - Passive copper - ShortBit 3 - Passive copper - MediumBit 4 - Passive copper - LongBit 5 - Active optics / copper short reach (<20m)Bit 6 - Optics long reach (>20m)Bit 7 - NO-FECBit 8 - FEC-ON */
	/* 0x20.16 - 0x20.31 */
	/* access: RO */
	u_int16_t profile_fec_in_use;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - For IB:
PDDR - Parallel Detect Link Enabled IB LayoutFor Ethernet:
PDDR - Parallel Detect Link Enabled Eth Layout */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext pd_link_enabled;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - For IB:
PDDR - HST Link Enabled IB LayoutFor Ethernet:
PDDR - HST Link Enabled Eth LayoutFor NVLink:
PDDR - HST Link Enabled NVLink Layout */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext phy_hst_link_enabled;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - PDDR - ETH AN Link Enabled Eth Layout */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t eth_an_link_enabled;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - 0: N/A - not supported or not enabled1: Attention2: Healthy */
	/* 0x38.0 - 0x38.3 */
	/* access: RO */
	u_int8_t link_health;
	/* Description - The metric type that caused the transition to Attention. Valid only
when link_health = 1 (Attention).0: N/A  no trigger active/supported or not enabled1: PLR_Tx_BW_Loss2: Recovery_BW_Loss3: Effective_BER4: symbol_error_count5: Raw_BER6: PLR_Rx_BW_Loss7: Port_total_BW_Loss8: Link_down_count9: Symbol_BER */
	/* 0x38.5 - 0x38.12 */
	/* access: RO */
	u_int8_t attention_trigger;
	/* Description - The index of the metric that caused the transition to Attention.
Valid only when link_health = 1 (Attention).0: N/A  no trigger active/supported or not enabled1: metric12: metric23: metric34: metric45: metric56: metric67: metric78: metric89: metric910: metric1011: metric1112: metric1213: metric1314: metric1415: metric15 */
	/* 0x38.13 - 0x38.19 */
	/* access: RO */
	u_int8_t attention_trigger_metric;
	/* Description - Indicates whether the current Attention state reflects the current
or a previously modified configuration.0: N/A  link health is not in Attention state1: Attention reflects a threshold crossing under the current
link health metrics configuration2: Attention was triggered under a previous configuration; one
or more associated metric parameters have since been modified */
	/* 0x38.20 - 0x38.21 */
	/* access: RO */
	u_int8_t link_health_config_changed;
	/* Description - Test mode FSM state exposure is supported only if PCAM.feature_cap_mask
bit 120 is set.Mode B links test mode FSM0: Disable - this state is shared by Mode A links and Mode B links
test mode FSM1: Open_lane2: Idle_mode_b3: Close_lane- Mode A links test mode FSM4: Receiver_detect5: Idle_mode_a6: Signal_detect7: Auto_fix_reversal_polarity8: Tuning_in_progress */
	/* 0x38.24 - 0x38.31 */
	/* access: RO */
	u_int8_t test_mode_fsm_state;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Local host class - Insertion loss0: Unspecified1: Host nominal (HN) - 4.45 to 13.95 dB2: Host low (HL) - 4.45 to 8.95 dB3: Host high (HH) - 4.55 to 18.5 dB4-7: Reserved */
	/* 0x3c.0 - 0x3c.2 */
	/* access: RO */
	u_int8_t local_host_class;
	/* Description - Remote host class - Insertion loss0: Unspecified1: Host nominal (HN) - 4.45 to 13.95 dB2: Host low (HL) - 4.45 to 8.95 dB3: Host high (HH) - 4.55 to 18.5 dB4-7: Reserved */
	/* 0x3c.4 - 0x3c.6 */
	/* access: RO */
	u_int8_t remote_host_class;
	/* Description - Channel differential loss in dB. The highest loss between receivers and
transmitters. */
	/* 0x3c.8 - 0x3c.12 */
	/* access: RO */
	u_int8_t channel_diff_loss;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_switch_pddr_phy_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port notifications bit maskBit 0 - Link partner advertised capabilitiesBit 1 - Speed degradation */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t port_notifications;
	/* Description - Bit 0: eth_base_pageBit 1: ib_base_pageBit 2: ib_base_page_rev2 - XDR onwardsBit 3: ConsortiumBit 4: MLPN_rev0Bit 5: MLPN_rev1Bit 6: NLPN_rev2 */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t negotiation_mask;
	/* Description - Remote device type:0 - Unknown (3rd party, Force, legacy MLPN)1 - CX42 - CX4_LX3 - CX54 - CX5_LX5 - CX66 - CX6_LX7 - CX6_DX8 - CX79 - Bluefield-210 - CX811 - Bluefield-312 - CX913 - CX1014-99 Reserved100 - SwitchIB101 - Spectrum102 - SwitchIB-2103 - Quantum104 - Spectrum-2105 - Spectrum-3106 - Quantum-2107 - Spectrum-4108 -Quantum-3109 - Quantum-4110 - Spectrum-5111 - Spectrum-6112 - Quantum-5113 - Quantum-6114 - Spectrum-7115-199 -Reserved200 - GB100 (OR 102/200)201 - GR100202 - GR150203 - Feinmann204 - GB10 - fusion205 - Rubin - fusion206-255 - Reserved */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t remote_device_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Link partner IB TS revision */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t lp_ib_revision;
	/* Description - IB TS revision */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ib_revision;
	/* Description - Negotiation attempt counter */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t num_of_negotiation_attempts;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Phy manager disable bit mask:Bit 0 - Module not present (module absence/cage power off)Bit 1 - PAOS commandBit 2 - MAD IB PortInfo down commandBit 3 - Long range cable (Non Mellanox)Bit 4 - Verification commandBit 5 - ekey commandBit 6 - High power - cable require higher power than allowed.Bit 7 - Unknown Identifier (Module)Bit 8 - PAOS up onceBit 9 - Stamping failureBit 10 - Calibration not doneBit 11 - Module LockingBit 12 - Cable lockingBit 13 - Power budget exceededBit 14 - Interrupt Event / Module TempBit 15 - TEC flow / module bring up issueBit 17 - SerDes task abort failedBit 18 - Default state is disable */
	/* 0x8.0 - 0x8.23 */
	/* access: RO */
	u_int32_t phy_manager_disable_mask;
	/* Description - IBP HW FSM Reflected State:0x10: sleeping_delay0x11: sleeping_quiet0x20: polling_active0x21: polling_quiet0x30: disable0x31: update_retimer0x40: config_debounce0x41: config_receiver0x42: config_wait_remote0x43: config_tx_reverse_lanes0x44: config_enhanced0x45: config_test0x46: confg_wait_remote_test0x47: config_wait_cfg_enhanced0x48: config_idle0x50: linkup0x51: Linkup_Tx_Idle0x52: Linkup_Tx_Empty-Recovery0x60: recover_retrain0x61: recover_wait_remote0x62: recover_idle0x63: Local_down_cmd0x64: Remote_down_cmd0x65: uphy_recovery_send_ts10x66: uphy_recovery_send_pam20x67: uphy_recovery_send_pam40x68: uphy_recovery_peq0x70: test- Force Modes0x80: Force_send_ts1 - command may be given only on disable state0x90: Force_send_ts20xA0: Force_Sent_Idle0xB0: Force_send_ts_Mlnx0xC0: Force_send_ts30xD0: Force_LinkUp- L10xE0: Go_To_Quiet0xE1: Retimer_Align0xE2: Quiet_Entry0xE3: Quiet0xE4: Wake0xE5: Wake_Tx_Sleep00xE6: Send_Announce0xE7: Tx_HS0xE8: Wait_For_Cdr_Lock */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t hw_link_phy_state;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - PCS HW state:Bits 0-7: Block lock (one bit per lane)Bits 8-15: AM lock (one bit per lane)Bits 16-23: FEC lock (one bit per lane)Bits 24: Align_statusBits 25: Hi_BERBits 26: Hi_SER */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t pcs_phy_state;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - IB ports:Link partner advertised speeds (first TS3)See ib_link_speed_enabled encoding.Ethernet ports:Link partner advertised Ethernet protocols active state: see
PTYS.lp_advertise */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t lp_proto_enabled;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Reserved when negotiation wasn't performed according to
port_notifications.Link partner advertised capabilities value.Advertised link partner FEC mode request */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t lp_fec_mode_request;
	/* Description - Reserved when negotiation wasn't performed according to
port_notifications.Link partner advertised capabilities value.Advertised link partner FEC mode supportBit 0 - No FECBit 1 - Firecode FECBit 2 - Standard RS-FEC - RS(528,514)Bit 3 - Standard LL RS-FEC - RS(271,257)Bit 4 - Mellanox Strong RS-FEC - RS(277,257)Bit 5 - Mellanox LL RS-FEC - RS(163,155)Bit 6 - ReservedBit 7 - Standard RS-FEC (544,514)Bit 8 - Zero Latency FECBit 12 - RS-FEC (544,514) + PLRBit 13 - LL-FEC (271,257) + PLR */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t lp_fec_mode_support;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Bit 0 - heartbeat_ack_receivedBit 1 - heartbeat_send_receivedBit 2 - heartbeat_errBit 3 - tx_width_reduction_done_1xBit 4 - tx_width_reduction_done_fullBit 5 - rx_width_reduction_done_1xBit 6 - rx_width_reduction_done_fullBit 7 - width_reduction_timeoutBit 8 - ibl_link_retrainBit 9 - rx_comskp_timeoutBit 10 - fifo_full_errBit 11 - ts_at_linkupBit 12 - minor_threshold_reachedBit 13 - link_failBit 14 - rx_eb_full_rBit 15 - rx_8_10_lane_errBit 16 - llr_link_retrain_setBit 17 - fc_timeoutBit 18 - phy_errorBit 19 - lli_errBit 20 - excessive_buffer_errBit 21 - remote_initBit 22 - plr_retry_expiredBit 23 - port_didnt_exit_plr_syncBit 24 - eq_failedBits 31-24 - Reserved */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t ib_last_link_down_reason;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Bit 0 - block_lock_failedBit 1 - skip_detectedBit 2 - fec_sync_failedBit 3 - fec_block_syncBit 4 - fec_block_sync_lost */
	/* 0x1c.24 - 0x20.23 */
	/* access: RO */
	u_int8_t eth_last_link_down_lane[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Bit 0 - Speed degradation database ValidBit 1 - Speed degradation SerDes Rx database validBIts 3-2 - reservedBit 4 - rx_reversalBit 5 - tx_reversalBit 7-6 - reservedBits 11:8 - failed_qdr/fdr10 - bit per lane.Bits 15:12 - failed_fdr - bit per lane.Bits 19:16- failed_edr - bit per lane.Bits 24:20 - peer_failed_testBits 26-25 - reservedBit 27 - first_test_speed */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t speed_deg_db;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Valid only when port_notifications.Speed degradation is asserted */
	/* 0x28.0 - 0x28.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane0;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - (see above) */
	/* 0x2c.0 - 0x2c.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane1;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - (see above) */
	/* 0x30.0 - 0x30.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane2;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - (see above) */
	/* 0x34.0 - 0x34.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane3;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - (see above) */
	/* 0x38.0 - 0x38.4 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane7;
	/* Description - (see above) */
	/* 0x38.8 - 0x38.12 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane6;
	/* Description - (see above) */
	/* 0x38.16 - 0x38.20 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane5;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x38.24 - 0x38.28 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane4;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - (see above) */
	/* 0x3c.0 - 0x3c.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_5;
	/* Description - kr_startup_debug_indication_<i> bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired */
	/* 0x3c.16 - 0x3c.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_4;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - (see above) */
	/* 0x40.0 - 0x40.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_7;
	/* Description - kr_startup_debug_indication_<i> bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired */
	/* 0x40.16 - 0x40.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_6;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - (see above) */
	/* 0x44.0 - 0x44.4 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane3;
	/* Description - (see above) */
	/* 0x44.8 - 0x44.12 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane2;
	/* Description - (see above) */
	/* 0x44.16 - 0x44.20 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane1;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x44.24 - 0x44.28 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane0;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Per lane KR startup state:0: KR_FSM_INITIALIZE1: KR_FSM_SEND_TRAINING2: KR_FSM_TRAIN_LOCAL_TX3: KR_FSM_TRAIN_LOCAL_RX4: KR_FSM_TRAIN_REMOTE5: KR_FSM_LINK_READY6: KR_FSM_SEND_DATA7: KR_FSM_NVLT8: KR_ABORT9: KR_TIMEOUT10: KR_FSM_IN_IDLE */
	/* 0x48.24 - 0x50.23 */
	/* access: RO */
	u_int8_t kr_startup_fsm_lane[8];
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - eth_an_debug bit mask:Bit 0 - Force link upBit 1 - No HCDBit 2 - Entered ACK_detectBit 3 - Entered GoodBit 4 - Entered Good_CheckBit 5 - Entered Extra_tuneBit 6 - Entered Fix_ReversalsBit 7 - Entered Next_PageBit 8 - Entered Sub-FSM FailBit 9 - Tuning timeoutBit 10 - No markers detected (during Good check)Bit 11 - Do KR-startupBits 15:18 - KR startup failure mask */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t eth_an_debug_indication;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - FW IB state machine:HDR GenBit 0 - entered IB_AN_FSM_DISABLEDBit 1 - entered IB_AN_FSM_INITIALYBit 2 - entered IB_AN_FSM_RCVR_CFGBit 3 - entered IB_AN_FSM_CFG_TESTBit 4 - entered IB_AN_FSM_WAIT_RMT_TESTBit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCEDBit 6 - entered IB_AN_FSM_CFG_IDLEBit 7 - entered IB_AN_FSM_LINK_UPBit 8 - Failed from CFG_IDLENDR Gen:Bit 0 - entered IB_AN_FSM_DISABLEDBit 1 - entered IB_AN_FSM_POLLINGBit 2 - entered IB_AN_FSM_INITIALYBit 3 - entered IB_AN_FSM_CFG_TESTBit 4 - entered IB_AN_FSM_WAIT_RMT_TESTBit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCEDBit 6 - entered IB_AN_FSM_CFG_IDLEBit 7 - entered IB_AN_FSM_SYNC_CHECKBit 8 - entered IB_AN_FSM_LINK_UPBit 9 - Failed from CFG_IDLEBit 10 - peer requested KRBit 11 - speed degradation needed - "best_grade" didn't reach threshold */
	/* 0x54.0 - 0x54.15 */
	/* access: RO */
	u_int16_t ib_phy_fsm_state_trace;
	/* Description -  */
	/* 0x54.16 - 0x54.20 */
	/* access: RO */
	u_int8_t rounds_waited_for_peer_to_end_test;
	/* Description - counts ETH Watchdog was performed (and closed the IB fsm). */
	/* 0x54.21 - 0x54.22 */
	/* access: RO */
	u_int8_t eth_an_watchdog_cnt;
	/* Description - count falls from Cfg_idle (before linkup) due cdr not lock */
	/* 0x54.23 - 0x54.25 */
	/* access: RO */
	u_int8_t fall_from_cfg_idle_cdr_cnt;
	/* Description - count falls from Cfg_idle (before linkup) due amps lock on PLU */
	/* 0x54.26 - 0x54.28 */
	/* access: RO */
	u_int8_t fall_from_cfg_idle_cnt;
	/* Description - count the cdr not locked after EQ */
	/* 0x54.29 - 0x54.31 */
	/* access: RO */
	u_int8_t cdr_not_locked_cnt;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - (see above) */
	/* 0x58.0 - 0x58.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_1;
	/* Description - kr_startup_debug_indication_<i> bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired */
	/* 0x58.16 - 0x58.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_0;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - (see above) */
	/* 0x5c.0 - 0x5c.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_3;
	/* Description - kr_startup_debug_indication_<i> bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired */
	/* 0x5c.16 - 0x5c.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_2;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Stages mask per lane:Bit 0: Single_preset_stageBit 1: multiple_preset_stageBit 2: LMS */
	/* 0x60.28 - 0x64.27 */
	/* access: RO */
	u_int8_t tx_tuning_stages_lane[8];
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - (see above) */
	/* 0x64.0 - 0x64.7 */
	/* access: RO */
	u_int8_t plu_tx_pwrup;
	/* Description - PLU power up status per lane */
	/* 0x64.8 - 0x64.15 */
	/* access: RO */
	u_int8_t plu_rx_pwrup;
	/* Description - (see above) */
	/* 0x64.16 - 0x64.23 */
	/* access: RO */
	u_int8_t plu_tx_polarity;
	/* Description - Configured PLU polarity per lane */
	/* 0x64.24 - 0x64.31 */
	/* access: RO */
	u_int8_t plu_rx_polarity;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x68.3 */
	/* access: RO */
	u_int8_t irisc_status;
	/* Description - 0 - Default as defined in IB Spec.1 - Override default with 64msec timeout for all speeds.2 - Reserved3 - Reserved */
	/* 0x68.4 - 0x68.5 */
	/* access: RO */
	u_int8_t ib_cfg_delay_timeout;
	/* Description - when set, signal_detected has valid value. */
	/* 0x68.6 - 0x68.6 */
	/* access: RO */
	u_int8_t sd_valid;
	/* Description - (see above) */
	/* 0x68.8 - 0x68.11 */
	/* access: RO */
	u_int8_t plu_tx_speed;
	/* Description - PLU configured speed: */
	/* 0x68.12 - 0x68.15 */
	/* access: RO */
	u_int8_t plu_rx_speed;
	/* Description - valid only when sd_valid is setBitmask per lane.When set signal has been detected on the lane */
	/* 0x68.24 - 0x68.31 */
	/* access: RO */
	u_int8_t signal_detected;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - Bit 0: com_codes_is_zeroBit 1: rx_cdr_check_force_modeBit 2: com_code_complianceBit 3: eth_56g_stampedBit 4: non_mlx_qsfp_transceiverBit 5: non_mlx_sfp_transceiverBit 6: ib_comp_codesBit 7: edr_compBit 8: fdr_comp */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t stamping_reason;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - Number of times that fast tuning (50ms) for KR lock failed to achieve
frame lock. */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t kr_frame_lock_tuning_failure_events_count;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Number of times that full tuning (0.5sec/3sec) for KR full tuning flow
failed to achieve desire SI performance */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t kr_full_tuning_failure_count;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - Bit 0: phy_test_modeBit 1: force_mode_en */
	/* 0x78.0 - 0x78.15 */
	/* access: RO */
	u_int16_t pm_debug_indication;
	/* Description - Bit 0: cause_plr_tx_max_outstanding_cells */
	/* 0x78.16 - 0x78.31 */
	/* access: RO */
	u_int16_t ib_debug_indication;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - Phy Manager catastrophic enum */
	/* 0x7c.0 - 0x7c.6 */
	/* access: RO */
	u_int8_t pm_catastrophic_enum;
	/* Description - When set, indicates the pm_catastrophic_enum is valid */
	/* 0x7c.7 - 0x7c.7 */
	/* access: RO */
	u_int8_t pm_cat_val;
	/* Description - Auto-neg catastrophic enum */
	/* 0x7c.8 - 0x7c.14 */
	/* access: RO */
	u_int8_t an_catastrophic_enum;
	/* Description - When set, indicates the an_catastrophic_enum is valid */
	/* 0x7c.15 - 0x7c.15 */
	/* access: RO */
	u_int8_t an_cat_val;
	/* Description - HST catastrophic enum */
	/* 0x7c.16 - 0x7c.22 */
	/* access: RO */
	u_int8_t hst_catastrophic_enum;
	/* Description - When set, indicates the hst_catastrophic_enum is valid */
	/* 0x7c.23 - 0x7c.23 */
	/* access: RO */
	u_int8_t hst_cat_val;
	/* Description - Parallel Detect catastrophic enum */
	/* 0x7c.24 - 0x7c.30 */
	/* access: RO */
	u_int8_t pd_catastrophic_enum;
	/* Description - When set, indicates the pd_catastrophic_enum is valid */
	/* 0x7c.31 - 0x7c.31 */
	/* access: RO */
	u_int8_t pd_cat_val;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Bit 0: speed_change_high_speed_moduleBit 1: False_positive_signal_detectBit 2: Nv2nv_forceBit 3: bad_kr_maskBit 4: kr_mlx_peerBit 5: entered_signal_detectBit 6: entered_rate_configBit 7: entered_activate_sunfsmBit 8: entered_doneBit 9: entered_subfsm_fail */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t pd_debug_indication;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - Parallel detect cycles counter */
	/* 0x84.0 - 0x84.5 */
	/* access: RO */
	u_int8_t pd_count;
	/* Description - False Positive signal detect count */
	/* 0x84.8 - 0x84.13 */
	/* access: RO */
	u_int8_t fp_signal_detect_count;
	/* Description - 0: speed1: FEC2: precoding3: Gray coding */
	/* 0x84.16 - 0x84.17 */
	/* access: RO */
	u_int8_t hst_mismatch_reason;
	/* Description - FSM 2 to call sub fsm of PSI that caused collisionsee fsm_mask in debug page for FSM numbering */
	/* 0x84.22 - 0x84.26 */
	/* access: RO */
	u_int8_t psi_collision2;
	/* Description - FSM 1 to call sub fsm of PSI that caused collisionsee fsm_mask in debug page for FSM numbering */
	/* 0x84.27 - 0x84.31 */
	/* access: RO */
	u_int8_t psi_collision1;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Bit 0: nonce_match_failBit 1: timeout - rst cause idle in nplnBit 2: hs_negBit 3: dme_neg */
	/* 0x88.0 - 0x88.7 */
	/* access: RO */
	u_int8_t nlpn_debug_ind_mask;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - phy 2 module requested speed, aka speed_apsel_valuebitmask according to PTYS.ext_ethernet_protocol for ETH speedsor ib_ext_protocols for IB speeds */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t phy2mod_speed_req;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - Bitmask per lane for phy2mod deactivate request status.0 - allow DP activation1 - Deactivate module DP */
	/* 0x90.0 - 0x90.7 */
	/* access: RO */
	u_int8_t phy2mod_deactivate_lanes;
	/* Description - Bitmask per lane for phy2mod request status.0 - ack1 - nack */
	/* 0x90.8 - 0x90.15 */
	/* access: RO */
	u_int8_t phy2mod_ack_lanes;
	/* Description - indicates module has one pll for all lanes of the module. */
	/* 0x90.29 - 0x90.29 */
	/* access: RO */
	u_int8_t one_pll_mod;
	/* Description - no_dme_module indicates module doesn't support low speed signaling such
as 312.5 MB/s for DME ETH AN signaling or SDR (2.5 GB/s) for IB low
speed AN. */
	/* 0x90.30 - 0x90.30 */
	/* access: RO */
	u_int8_t no_dme_mod;
	/* Description - eeprom present indication */
	/* 0x90.31 - 0x90.31 */
	/* access: RO */
	u_int8_t eeprom_prsnt;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.0 - 0x94.1 */
	/* access: RO */
	u_int8_t rx_bypass_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.2 - 0x94.3 */
	/* access: RO */
	u_int8_t rx_bypass_mux_plt1;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.4 - 0x94.5 */
	/* access: RO */
	u_int8_t tx_bypass_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.6 - 0x94.7 */
	/* access: RO */
	u_int8_t tx_bypass_mux_plt1;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.8 - 0x94.9 */
	/* access: RO */
	u_int8_t reconciliation_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.10 - 0x94.11 */
	/* access: RO */
	u_int8_t reconciliation_mux_plt1;
	/* Description - MacSec enabled plt0 split 0 */
	/* 0x94.12 - 0x94.12 */
	/* access: RO */
	u_int8_t macsec_en_plt0_s0;
	/* Description - MacSec enabled plt0 split 1 */
	/* 0x94.13 - 0x94.13 */
	/* access: RO */
	u_int8_t macsec_en_plt0_s1;
	/* Description - MacSec enabled plt1 split 0 */
	/* 0x94.14 - 0x94.14 */
	/* access: RO */
	u_int8_t macsec_en_plt1_s0;
	/* Description - MacSec enabled plt1 split 1 */
	/* 0x94.15 - 0x94.15 */
	/* access: RO */
	u_int8_t macsec_en_plt1_s1;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.16 - 0x94.19 */
	/* access: RO */
	u_int8_t cnt_rx_frame_received_ok_s0;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.20 - 0x94.23 */
	/* access: RO */
	u_int8_t cnt_rx_frame_received_ok_s1;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.24 - 0x94.27 */
	/* access: RO */
	u_int8_t port_xmit_pkts_inc_s0;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.28 - 0x94.31 */
	/* access: RO */
	u_int8_t port_xmit_pkts_inc_s1;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - rtt threshold in 1 ns units for NDR_4x speeds with KP4 FEC */
	/* 0x98.0 - 0x98.15 */
	/* access: RO */
	u_int16_t plr_rtt_ndr_4x_kp4_threshold;
	/* Description - rtt threshold in 1 ns units for HDR speeds */
	/* 0x98.16 - 0x98.31 */
	/* access: RO */
	u_int16_t plr_rtt_hdr_threshold;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - rtt threshold in 1 ns units for NDR_2x speeds with KP4 FEC */
	/* 0x9c.0 - 0x9c.15 */
	/* access: RO */
	u_int16_t plr_rtt_ndr_2x_kp4_threshold;
	/* Description - rtt threshold in 1 ns units for XDR_1x speeds with KP4 FEC */
	/* 0x9c.16 - 0x9c.31 */
	/* access: RO */
	u_int16_t plr_rtt_xdr_1x_kp4_threshold;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - rtt threshold in 1 ns units for NDR_2x speeds with ELL FEC */
	/* 0xa0.0 - 0xa0.15 */
	/* access: RO */
	u_int16_t plr_rtt_ndr_2x_ell_threshold;
	/* Description - rtt threshold in 1 ns units for NDR_4x speeds with ELL FEC */
	/* 0xa0.16 - 0xa0.31 */
	/* access: RO */
	u_int16_t plr_rtt_ndr_4x_ell_threshold;
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - rtt threshold in 1 ns units for XDR_1x speeds with ELL FEC */
	/* 0xa4.0 - 0xa4.15 */
	/* access: RO */
	u_int16_t plr_rtt_xdr_1x_ell_threshold;
	/* Description - rtt threshold in 1 ns units for XDR_2x speeds with KP4 FEC */
	/* 0xa4.16 - 0xa4.31 */
	/* access: RO */
	u_int16_t plr_rtt_xdr_2x_kp4_threshold;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - Device NV-Link Generation:0: nv_link_51: nv_link_62: nv_link_73: nv_link_8 */
	/* 0xa8.0 - 0xa8.4 */
	/* access: RO */
	u_int8_t nv_link_generation;
	/* Description - rtt threshold in 1 ns units for XDR_2x speeds with ELL FEC */
	/* 0xa8.16 - 0xa8.31 */
	/* access: RO */
	u_int16_t plr_rtt_xdr_2x_ell_threshold;
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description - (see above) */
	/* 0xc0.0 - 0xc0.3 */
	/* access: RO */
	u_int8_t mode_b_fsm_state_lane_0;
	/* Description - Mode B FSM state for lane[i]:0: STATE_0 1: STATE_1 2: STATE_2 3: STATE_3 4: STATE_4 Note: this FSM is applicable only to mode B links. */
	/* 0xc0.4 - 0xc0.7 */
	/* access: RO */
	u_int8_t mode_b_fsm_state_lane_1;
/*---------------- DWORD[51] (Offset 0xcc) ----------------*/
	/* Description - APSU (ILT/RTS) operational mode1: APSU enabled2: APSU disabled */
	/* 0xcc.0 - 0xcc.1 */
	/* access: RO */
	u_int8_t apsu_oper;
	/* Description - Hop count for TRO operational mode1: Hop count enabled2: Hop count disabled */
	/* 0xcc.3 - 0xcc.4 */
	/* access: RO */
	u_int8_t hop_count_oper;
	/* Description - Link Training peer detection operation mode1: Peer detection enabled2: Peer detection disabled */
	/* 0xcc.6 - 0xcc.7 */
	/* access: RO */
	u_int8_t lt_peer_det_oper;
	/* Description - nLUT operational mode.1: nLUT enabled2: nLUT disabled */
	/* 0xcc.9 - 0xcc.10 */
	/* access: RO */
	u_int8_t nlut_oper;
	/* Description - Control the training_en coperational mode1: Training enabled2: Training disabled */
	/* 0xcc.12 - 0xcc.13 */
	/* access: RO */
	u_int8_t training_en_oper;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_switch_pddr_troubleshooting_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Monitor_opcodes */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t group_opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Status opcode described in:PDDR - Monitor opcodes layout */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext status_opcode;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ASCII code messageAll Messages are terminated by a Null character \0' */
	/* 0xc.0 - 0xf4.31 */
	/* access: RO */
	u_int32_t status_message[59];
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_ppcl_cause_configurations_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: fw_default1: clear2: do_not_clearDetermine whether the PHY cause link reset operation */
	/* 0x0.0 - 0x0.1 */
	/* access: RW */
	u_int8_t clr_on_read_admin;
	/* Description - 0: fw_default1: clear2: do_not_clearDetermine whether the PHY cause list will be cleared on
cause_list_data read operation */
	/* 0x0.3 - 0x0.4 */
	/* access: RW */
	u_int8_t clr_on_link_rst_admin;
	/* Description - 0: do_not_clear1: clearIndicates whether the PHY cause list will be cleared on
cause_list_data read operation */
	/* 0x0.7 - 0x0.7 */
	/* access: RO */
	u_int8_t clr_on_read_oper;
	/* Description - 0: do_not_clear1: clearIndicates whether the PHY cause list will be cleared on link
reset operation */
	/* 0x0.10 - 0x0.10 */
	/* access: RO */
	u_int8_t clr_on_link_rst_oper;
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t nvlink_phy6_cause_list1;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t nvlink_phy6_cause_list2;
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_prm_register_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Register ID */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t register_id;
	/* Description - 0: Query1: Write */
	/* 0x0.22 - 0x0.23 */
	/* access: OP */
	u_int8_t method;
	/* Description - Return code of the Downstream Device to the register that was sent.0x0: OK - Operation was successfully executed0x1: BUSY0x4: NOT_SUPP_REG - The Switch register requested is not supported on
that device0x7: BAD_PARAM - Incomplete or erroneous parameter set0x70: INTERNAL_ERR - internal error */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Register data */
	/* 0x4.0 - 0x100.31 */
	/* access: RW */
	u_int32_t register_data[64];
};

/* Description -   */
/* Size in bytes - 12 */
union reg_access_switch_MRFV_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_CVB_ext MRFV_CVB_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_PVS_MAIN_ext MRFV_PVS_MAIN_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_PVS_TILE_ext MRFV_PVS_TILE_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_RAW_AND_VALUE_ext MRFV_RAW_AND_VALUE_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_ULT_ext MRFV_ULT_ext;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_ef_mcce_entry_v1_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - CDB error code from CDB A100. 0xFF00 indicates invalid / not applicable. */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t cdb_error_code;
	/* Description - MCC error code. Encoding matches error_code field in MCC register. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t mcc_error_code;
	/* Description - Module identifier associated with the error. */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t module_id;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_lane_2_module_mapping_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module number */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t module;
	/* Description - Reserved for HCA.Slot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available. */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t slot_index;
	/* Description - Indicates start offset of rx_lane, tx_lane inside the modules lanes in
8x granularity. relevant for modules with more than 8 lanes. such as OE.0: lanes_0-71: lanes_8_152: lanes_16_233: lanes_24_31 */
	/* 0x0.12 - 0x0.15 */
	/* access: RW */
	u_int8_t sub_module;
	/* Description - TX lane.When m_lane_m field is set, this field is ignored (Reserved).When rxtx field is cleared, this field is used for RX as well. */
	/* 0x0.16 - 0x0.19 */
	/* access: RW */
	u_int8_t tx_lane;
	/* Description - RX lane.When m_lane_m field is set, this field is ignored (Reserved).When rxtx field is clreared, for set operation this field is ignored and
for get operation may return invalid value, Rx mapping for get should be
taken from tx_lane. */
	/* 0x0.24 - 0x0.27 */
	/* access: RW */
	u_int8_t rx_lane;
	/* Description - Supported if PCAM.feature_cap_mask bit 116 is set, otherwise field is
not valid.Relevant for Mode B port only, Mode A port should ignore.indicates if module lane Tx or Rx is used.0: module_rx_lane_valid - Mode B lane uses module rx lane.tx lane value is not valid should be ignored1: module_tx_lane_valid - Mode B lane uses module tx lane.rx lane value is not valid should be ignored */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t mode_b_map;
};

/* Description -   */
/* Size in bytes - 32 */
union reg_access_switch_mddq_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_device_info_ext mddq_device_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_slot_info_ext mddq_slot_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_slot_name_ext mddq_slot_name_ext;
};

/* Description -   */
/* Size in bytes - 260 */
union reg_access_switch_mddt_reg_payload_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_command_payload_ext command_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_crspace_access_payload_ext crspace_access_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_prm_register_payload_ext prm_register_payload_ext;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mgpir_hw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of devices of device_type. */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t num_of_devices;
	/* Description - Total number of modules within the specific ASIC, Bits [7:0].Note:For multi ASIC platforms, this field will provide the total number of
modules for all ASICs combined together.For single ASIC platforms, the value will be the same as
numfer_of_modulesFor QM-3 CPO (Taipan), return the total num of ELS and OE_MCU together.
First indexes represent the OE and the higher indexes are assigned to
ELS modules. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t num_of_modules_per_system;
	/* Description - Number of devices of device_type per flash. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t devices_per_flash;
	/* Description - Device type.0: No devices on system of that type.1: Gearbox2: Tiles3: No Info Available */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t device_type;
	/* Description - Slot index0: Main board */
	/* 0x0.28 - 0x0.31 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of modules within the specific ASIC, bits [7:0]. */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t num_of_modules;
	/* Description - Number of slots in the system. To eliminate receiving bad param'
status, the user should query that field with slot_index set to 0. */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t num_of_slots;
	/* Description - Maximum number of modules that can be connected per slot, bits [7:0].
Includes internal and external modules. */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t max_modules_per_slot;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Num of Resource Modules.Value of 0xff..ff means not valid. */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t num_of_resource_modules;
	/* Description - Total number of module i2c bus */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t total_num_of_module_i2c_bus;
	/* Description - Maximum lane count per submodule */
	/* 0x8.16 - 0x8.19 */
	/* access: RO */
	u_int8_t num_lanes_per_sub_module;
	/* Description - The maximum submodule index.0: Only one submodule 3: Four submodulesOther values are reserved */
	/* 0x8.24 - 0x8.27 */
	/* access: RO */
	u_int8_t max_sub_modules_index;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - [Switch][DWIP]Bits [15:8] of number of all modules on ASIC (chip/package). */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t num_of_modules_msb;
	/* Description - [Switch][DWIP]Bits [15:8] of number of all modules on system (tray). */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t num_of_modules_per_system_msb;
	/* Description - [Switch][DWIP]Bits [15:8] of number of top-level modules (e.g not including OEs and
ELSes) on ASIC (chip/package). */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t max_modules_per_slot_msb;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - [Switch][DWIP]Number of ELSes connected to ASIC (chip/package). */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t els_count_local;
	/* Description - [Switch][DWIP]Number of Optical Engines on ASIC (chip/package). */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t oe_count_local;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - [Switch][DWIP]Number of ELSes connected to system (tray). */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t els_count_global;
	/* Description - [Switch][DWIP]Number of Optical Engines on system (tray). */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t oe_count_global;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - [Switch][DWIP]Number of top-level non-mission modules on ASIC (chip/package).. */
	/* 0x18.0 - 0x18.15 */
	/* access: RO */
	u_int16_t tl_module_non_mission_count_local;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mgpir_hw_metadata_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [DWIP]Top Level Mission Modules base index for ASIC (chip/package). */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t tl_module_mission_base_index_local;
	/* Description - [DWIP]Top Level Mission Modules base index for system (tray). */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t tl_module_mission_base_index_global;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - [DWIP]Top Level Non-Mission Modules base index for ASIC (chip/package). */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t tl_module_non_mission_base_index_local;
	/* Description - [DWIP]Top Level Non-Mission Modules base index for system (tray). */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t tl_module_non_mission_base_index_global;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - [DWIP]ELS base index for ASIC (chip/package). */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t els_base_index_local;
	/* Description - [DWIP]ELS base index for system (tray). */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t els_base_index_global;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - [DWIP]Optical Engines base index for ASIC (chip/package). */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t oe_base_index_local;
	/* Description - [DWIP]Optical Engines base index for system (tray). */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t oe_base_index_global;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mmta_tec_power_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The required cooling level based on TEC power and Set Point.Cooling Level units are % i.e percentage.0% (no need to cool down) to 100% (max cooling resource, e.g fan, to
cool down the module). */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t cooling_level;
	/* Description - Temperature measurement units0: units of 0.125 Celsius degrees1: units of 1/256 Celsius degreesFor negative values 2's complement is used */
	/* 0x0.29 - 0x0.29 */
	/* access: INDEX */
	u_int8_t temp_unit;
	/* Description - Max TEC Power Reset:0: do not modify the value of the max temperature register1: clear the value of the max TEC Power and max Setpoint register */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t mtpr;
	/* Description - Max TEC Power Enable:0: disable measuring the max TEC Power and set point on a module1: enables measuring the max TEC Power and set point on a module */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t mtpe;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - TEC power reading from the module. Units of 1mW. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t tec_power;
	/* Description - The highest measured TEC power from the module.Reserved when mtece = 0Cleared by mtecr = 1 */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_tec_power;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Refers to module TEC Power low warning threshold. Units of 1mW. */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t tec_power_warning_low;
	/* Description - Refers to module TEC Power high warning threshold. Units of 1mW. */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t tec_power_warning_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Refers to module TEC Power low alarm threshold. Units of 1mW. */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t tec_power_alarm_low;
	/* Description - Refers to module TEC Power high alarm threshold. Units of 1mW. */
	/* 0xc.16 - 0xc.31 */
	/* access: RW */
	u_int16_t tec_power_alarm_high;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Laser set point measured from the laserUnits defined at temp_unit field */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t set_point_temperature;
	/* Description - The highest measured set point from the module.Reserved when mtece = 0Cleared by mtecr = 1 */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t max_set_point_temperature;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Refers to module set point low warning threshold Units defined at
temp_unit field */
	/* 0x14.0 - 0x14.15 */
	/* access: RW */
	u_int16_t set_point_temperature_warning_low;
	/* Description - Refers to module TEC Power high warning threshold Units defined at
temp_unit field */
	/* 0x14.16 - 0x14.31 */
	/* access: RW */
	u_int16_t set_point_temperature_warning_high;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Refers to module set point low alarm thresholdUnits defined at temp_unit field */
	/* 0x18.0 - 0x18.15 */
	/* access: RW */
	u_int16_t set_point_temperature_alarm_low;
	/* Description - Refers to module set point high alarm thresholdUnits defined at temp_unit field */
	/* 0x18.16 - 0x18.31 */
	/* access: RW */
	u_int16_t set_point_temperature_alarm_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The minimum allowed cooling level */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t min_cooling_level;
	/* Description - The maximum allowed cooling level */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t max_cooling_level;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_mmta_temprature_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1: ref_module field valid.This bit is set only when the <module_msb, module> concatenation refers
to the index of a top-level module. In such a case, the ref_module field
refers to the index of the component with the highest current
temperature of that component type. */
	/* 0x0.25 - 0x0.25 */
	/* access: RO */
	u_int8_t ref_module_valid;
	/* Description - Temperature measurement units0: units of 0.125 Celsius degrees1: units of 1/256 Celsius degreesFor negative values 2's complement is used */
	/* 0x0.26 - 0x0.26 */
	/* access: INDEX */
	u_int8_t temp_unit;
	/* Description - Temperature Warning Event Enable (MMTA Trap)0: do_not_generate_event1: generate_events2: generate_single_event */
	/* 0x0.27 - 0x0.28 */
	/* access: RW */
	u_int8_t twee;
	/* Description - Temperature Warning Enable:0: all fields are set1: only twee field is set, all other fields reserved */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t twe;
	/* Description - Max Temperature Reset:0: do not modify the value of the max temperature register1: clear the value of the max temperature register */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t mtr;
	/* Description - Max Temperature Enable:0: disable measuring the max temperature on a sensor1: enables measuring the max temperature on a sensor */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t mte;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Temperature reading from the moduleUnits defined at temp_unit field */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t temperature;
	/* Description - The highest measured temperature from the module.Reserved when mte = 0Cleared by mtr = 1 */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_temperature;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Refers to module temperature low warning thresholdUnits defined at temp_unit field */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t temperature_warning_low;
	/* Description - Refers to module temperature high warning thresholdUnits defined at temp_unit field */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t temperature_warning_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Refers to module temperature low alarm thresholdUnits defined at temp_unit field */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t temperature_alarm_low;
	/* Description - Refers to module temperature high alarm thresholdUnits defined at temp_unit field */
	/* 0xc.16 - 0xc.31 */
	/* access: RW */
	u_int16_t temperature_alarm_high;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Indicates the index of the OE or ELS component, whose information is
reflected in this structure. */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t ref_module;
};

/* Description -   */
/* Size in bytes - 248 */
union reg_access_switch_pddr_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_switch_module_latched_flag_info_ext module_latched_flag_info_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_apsu_info_page_ext pddr_apsu_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xa4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_cpo_module_page_ext pddr_cpo_module_page_ext;
	/* Description -  */
	/* 0x0.0 - 0x88.31 */
	/* access: RW */
	struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext pddr_fec_measure_ltx_nvl5_ext;
	/* Description -  */
	/* 0x0.0 - 0xf0.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_down_info_page_ext pddr_link_down_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xac.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_health_page_ext pddr_link_health_page_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_partner_info_ext pddr_link_partner_info_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_link_up_info_page_ext pddr_link_up_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xcc.31 */
	/* access: RW */
	struct reg_access_switch_pddr_module_info_ext pddr_module_info_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_operation_info_page_ext pddr_operation_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_phy_info_page_ext pddr_phy_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_switch_pddr_troubleshooting_page_ext pddr_troubleshooting_page_ext;
};

/* Description -   */
/* Size in bytes - 20 */
union reg_access_switch_ppcl_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_switch_ppcl_cause_configurations_ext ppcl_cause_configurations_ext;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	/* access: RW */
	struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext ppcl_cause_list_for_nvlink_phy_gen6_ext;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_MMAM_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - (Global) Module number bits [7:0]. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - [Switch][DWIP](Global) Module number bits [15:8].Switch: Global module indexes.For read operation, supported concatenated module number ranges is -Base: 0Count: <MGPIR.num_of_modules_per_system_msb, MGPIR.num_of_modules_per_system> */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t module_msb;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Geographical Address of the ASIC which controls the moduleReserved when module type is chip2chip or backplane. */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t ga;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Local module number bits [7:0]. */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t local_module;
	/* Description - [Switch][DWIP]Local module number bits [15:8]. */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t local_module_msb;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - module_type:0: Backplane_with_4_lanes1: QSFP2: SFP3: No_Cage4: Backplane_with_single_lane8: Backplane_with_two_lanes10: Chip2Chip4x11: Chip2Chip2x12: Chip2Chip1x14: QSFP_DD15: OSFP16: SFP_DD17: DSFP18: Chip2Chip8x19: Twisted_Pair20: Backplane_with_8_lanes21: Loopback 22: OE_16x23: OSFP_ELS24: QSFP_2x25: CPO_32x26: ELS_1627: CPO_64x28: QSFP_1x29: NPO_16x30: OSFP_4x */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t module_type;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_switch_MRFV_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Fuse Index0: cvb - CVB Main Die, used for Retimer1: ULT2: vdd_main_die - (used in SPC-4, SPC-5)3: vdd_tile_0 - (used in SPC-4, SPC-5)4: vdd_tile_1 - (used in SPC-4, SPC-5)5: vdd_tile_2 - (used in SPC-4, SPC-5)6: vdd_tile_3 - (used in SPC-4, SPC-5)7: vdd_tile_4 - (used in SPC-4, SPC-5)8: vdd_tile_5 - (used in SPC-4, SPC-5)9: vdd_tile_6 - (used in SPC-4, SPC-5)10: vdd_tile_7 - (used in SPC-4, SPC-5)[Switch]:11: raw_and_value_vdd - Use instance_id for the specific instance. Valid on SPC6.12: raw_and_value_pl_avdd - Use instance_id for the specific instance. Valid on SPC6.13: raw_and_value_pl_dvdd - Use instance_id for the specific instance. Valid on SPC6.15: raw_and_value_opt_fuse_rev - Valid on SPC6 CPO.16: raw_and_value_dvdd_sg - Use instance_id for the specific instance. Valid on SPC6 CPO.17: raw_and_value_opt_lot_code_0 - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.18: raw_and_value_opt_lot_code_1 - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.19: raw_and_value_opt_ops_reserved - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.20: raw_and_value_opt_vendor_code - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.21: raw_and_value_opt_wafer_id - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.22: raw_and_value_opt_x_coordinate - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.23: raw_and_value_opt_y_coordinate - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.24: raw_and_value_opt_fab_code - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.[Retimer][Switch]25: raw_and_value_ws_tp_version_0_31 -
Valid starting SPC6, QM5, ArcusE.26: raw_and_value_ft_tp_version_0_31 -
Valid starting SPC6, QM5, ArcusE.27: raw_and_value_fuse_ver_0_3 - Use instance_id for the specific instance. Valid starting SPC6, QM5, ArcusE.28: raw_and_value_fuse_ver_4_7 -
Use instance_id for the specific instance. Valid starting SPC6, QM5, ArcusE.
[NIC_only][DWIP]:30: raw_and_value_dvdd[NIC_only][DWIP]:31: raw_and_value_vddpOther values reserved. */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t fuse_id;
	/* Description - [DWIP]:Instance ID. For a fuse that has multiple instances, this field provides
the Instance ID.For the common case where it's a single instance per asic, instance ID 0
denotes the main/die [0] instance, and subsequent instance ID X denotes
the instance of tile [X-1] / die [X].For a given fuse_id, if an invalid instance_id is provided, fm field
will have a value of 1 (Fuse mismatch found). */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t instance_id;
	/* Description - Fuse Mismatch0: No fuse mismatch1: Fuse mismatch found2-3: ReservedFor further details see fm_sel field. */
	/* 0x0.24 - 0x0.25 */
	/* access: RO */
	u_int8_t fm;
	/* Description - Fuse Mismatch 20: No fuse mismatch1: Fuse mismatch found2-3: ReservedFor further details see fm_sel field. */
	/* 0x0.26 - 0x0.27 */
	/* access: RO */
	u_int8_t fm2;
	/* Description - Fuse Mismatch Selection0: fm field should be used to read Fuse Mismatch status relating to fuse_id field.
1: fm2 field should be used to read Fuse Mismatch status relating to fuse_id field.
For supporting platforms, fm field reflects HW status bit regarding fuse mismatch. */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t fm_sel;
	/* Description - [DWIP]1: module_index_msb and module_index fields contain a valid index. */
	/* 0x0.29 - 0x0.29 */
	/* access: INDEX */
	u_int8_t module_index_valid;
	/* Description - Valid bit0: Fuse reading is not supported for this system1: Response is valid2-3: ReservedReserved (0) when there is a value of 1 in fuse_id-related fuse mismatch field (fm or fm2, see definition of fm_sel) */
	/* 0x0.30 - 0x0.31 */
	/* access: RO */
	u_int8_t v;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - [DWIP]:<module_index_msb, module_index> specifies the element in which the fuse
resides, if not part of the ASIC itself.Switch: Local indexes.Supported range is -Base: MGPIR.tl_oe_base_index_localCount: MGPIR.tl_oe_count_local */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t module_index;
	/* Description - [DWIP]:<module_index_msb, module_index> specifies the element in which the fuse
resides, if not part of the ASIC itself.Currently only valid elements are Optical Engines.Switch: Local indexes.Supported range is -Base: MGPIR.tl_oe_base_index_localCount: MGPIR.tl_oe_count_local */
	/* 0x4.8 - 0x4.15 */
	/* access: INDEX */
	u_int8_t module_index_msb;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - DataSee 
MRFV entry - CVB LayoutSee 
MRFV entry - ULT LayoutSee 
MRFV entry - VDD_MAIN LayoutSee

MRFV entry - VDD_Tile LayoutSee

MRFV entry - RAW_AND_VALUE LayoutReserved when fm = 1 */
	/* 0x10.0 - 0x18.31 */
	/* access: RO */
	union reg_access_switch_MRFV_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_PPCR_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port[9:8]Reserved for HCA */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Indicate whether asymmetry is enabled or not.0: DISABLED1: ENABLEDFor HCA, reserved if PPCR.asymmetry_enable_supported=0 */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t asymmetry_enable;
	/* Description - Indicate whether asymmetry_enable supported or not.Reserved for switch.0: NOT_SUPPORTED1: SUPPORTED */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t asymmetry_enable_supported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Aggregated Port number to be reflected in MAD.0 means N/A */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t aggregated_port;
	/* Description - Plane number to be reflected in MAD.0 means N/A */
	/* 0x8.16 - 0x8.18 */
	/* access: RW */
	u_int8_t plane;
	/* Description - When planarized  the FW
shall respond to Hierarchy Info.Split with the following split value.In this use case it represents the split of the APort.When split = 0, the FW shall send Hierarchy Info without the split
field. (meaning it is NA)When Non planarized (num_of_planes = 0), Hierarchy Info.Split will
reflect the actual split value, when 2X- it'll hold the location within
the 4x.0: NA1: Split 1.2: Split 2.3-7: ReservedReserved for HCA */
	/* 0x8.24 - 0x8.26 */
	/* access: RW */
	u_int8_t split;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The number of planes comprising this Aggregated port */
	/* 0xc.0 - 0xc.7 */
	/* access: RW */
	u_int8_t num_of_planes;
	/* Description - Planarization Type0: non planarized1: planirized_gen12-7: Reserved */
	/* 0xc.16 - 0xc.18 */
	/* access: RW */
	u_int8_t p_type;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_icam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups0: REG_IDs 0x3800 to 0x387F1: REG_IDs 0x3880 to 0x38FF */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t access_reg_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported infrastructure's access register bitmask. Based on
access_reg_group index.When bit is set to 1', The register is supported in the device.For example, when access_reg_group == 1:Bit 112: ICSRBit0 is at 08h.bit0Bit 127 is at 14h.bit31 */
	/* 0x8.0 - 0x14.31 */
	/* access: RO */
	u_int32_t infr_access_reg_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 1040 */
struct reg_access_switch_icsr_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Base cr-space address for reading */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t base_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of cr-space consecutive reads.Each read is 4B (DWord)Range 1..256 */
	/* 0x8.0 - 0x8.8 */
	/* access: OP */
	u_int16_t num_reads;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The cr-space read data */
	/* 0x10.0 - 0x40c.31 */
	/* access: RO */
	u_int32_t data[256];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_switch_mcce_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of valid entries currently held in the error log (015). */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t error_count;
	/* Description - Operation to perform.0x0: no_op0x1: clear - Clear all error log entries. */
	/* 0x0.7 - 0x0.7 */
	/* access: OP */
	u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Error log entries. Array of 15 32-bit elements, one DWORD each
See MCCE Entry Fields */
	/* 0x4.0 - 0x3c.31 */
	/* access: RO */
	struct reg_access_switch_ef_mcce_entry_v1_ext entries[15];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mddq_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index0: Reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - 0: Reserved1: slot_info2: device_info - for a device on the slot. If there are no devices on
the slot, data_valid will be 0'.3: slot_name - Name of the slot (string) */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t query_type;
	/* Description - Slot info event enableWhen set to 1', each change in the MDDQ.slot_info.provisioned /
sr_valid / active / ready will generate an DSDSC event. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t sie;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Request message sequential number.The first message number should be 0 */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t request_message_sequence;
	/* Description - Response message sequential number.For a specific request, the response message sequential number is the
following one.In addition, the last message should be 0. */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t response_message_sequence;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Index related to the specific query_type.For query_type = 1,2,3 this field is neglected. */
	/* 0x8.0 - 0x8.7 */
	/* access: INDEX */
	u_int8_t query_index;
	/* Description - If set, the data in the data field is valid and contain the information
for the queried index.Note: This field is not reflecting any validity of the data while
accessing a non-existing queryF entity. Querying with an out of range
index will lead to BAD_PARAM status of the register. */
	/* 0x8.31 - 0x8.31 */
	/* access: RO */
	u_int8_t data_valid;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Properties of that field are based on query_type.For slot information query_type data - see
MDDQ slot_info LayoutFor devices on slot query_type data - see
MDDQ device_info Register LayoutFor slot name query_type data - see
MDDQ slot_name Layout */
	/* 0x10.0 - 0x2c.31 */
	/* access: RO */
	union reg_access_switch_mddq_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 272 */
struct reg_access_switch_mddt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t device_index;
	/* Description - Slot index */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: PRM_Register1: Command2: CrSpace_access */
	/* 0x4.0 - 0x4.1 */
	/* access: OP */
	u_int8_t type;
	/* Description - Write size in D-Words. */
	/* 0x4.16 - 0x4.23 */
	/* access: OP */
	u_int8_t write_size;
	/* Description - Read size in D-Words. */
	/* 0x4.24 - 0x4.31 */
	/* access: OP */
	u_int8_t read_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - PayloadFor PRM Register type payload - See
PRM Register Payload LayoutFor Command type payload - See
Command Payload LayoutFor CrSpace type payload - See
CrSpace access Payload Layout */
	/* 0xc.0 - 0x10c.31 */
	/* access: RW */
	union reg_access_switch_mddt_reg_payload_auto_ext payload;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mdsr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: The debug session ended successfully1: Failed to execute the operation. See additional_info for more
details.2: Debug session active. See type_of_token for more details.3: No token applied4: Challenge provided, no token installed yet, see type_of_token for
details.5: Timeout before token installed, see type_of_token for details6: Timeout of active token.7-15: ReservedNote: Status might be 0' even when debug query is not allowed and
additional_info field will expose the reason. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - 0: No additional information available1: There is no debug session in progress2: FW is not secured, debug session cannot be ended3: Fail - Debug end request cannot be accepted.
4: Fail - Host is not allowed to query debug session5: Debug session active6: Debug FW is running, cannot remove CRDT token */
	/* 0x0.8 - 0x0.13 */
	/* access: RO */
	u_int8_t additional_info;
	/* Description - 0: CS token 1: Debug FW token 2: FRC token3: RMCS token4: RMDT token5: CRCS token6: CRDT token8: MTFA token0xFF: All tokens. Relevant only when end=1 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_of_token;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Set to 1' to end debug session.Setting to 0' will not trigger any operation. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t revoke_version;
	/* Description - Used to revoke token version from device. Relevant only when end=1. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t end;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time left in seconds.In case that status is 2 (debug session active) - time left for token
operationIn case that status is 4 (challenge provided, no token installed yet) -
time left for token installationFor any other status, field should be zero */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t time_left;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - First DW of token config TLV value, set to 0 if no token config. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t token_config;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_mfcdr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module numberValid when query_type = 1, else this field is ignored */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Local port MSBValid when query_type = 0, else this field is ignored */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local portValid when query_type = 0, else this field is ignored */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Selector of query type0: local_port based query1: module based query */
	/* 0x0.31 - 0x0.31 */
	/* access: INDEX */
	u_int8_t query_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: N/A1: Fake cable detected2: NVIDIA Cable detected3: Non-Nvidia Cable detected */
	/* 0x4.0 - 0x4.1 */
	/* access: RO */
	u_int8_t status;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_mfkv_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When this bit is set, it indicates that it is allowed for the boot
FW to program the FW key version related EFUSEs if needed.Once set to 1, this configuration will be relevant only for the
upcoming boot, thus this configuration will be set back to 0 upon
next boot. */
	/* 0x0.0 - 0x0.0 */
	/* access: RW */
	u_int8_t efuses_prog_en;
	/* Description - Firmware key version status.0: equal - EFUSEs value is equal to the currently running FW image
maximal value. No change is possible.1: update_required - EFUSEs value is smaller than the currently
running FW image maximal value. An update to the EFUSEs is
required.2: pending_image - There is pending image, MFKV is rejected3: reserved - Reserved */
	/* 0x0.1 - 0x0.2 */
	/* access: RO */
	u_int8_t fw_key_ver_stat;
	/* Description - 0: do_not_revoke - Do not revoke EFUSE programming (no-op)1: revoke - Revoke pending EFUSE programming. This command is
possible only if reset did not occur from EFUSE programming
request, and the EFUSE programming revocation request */
	/* 0x0.3 - 0x0.3 */
	/* access: RW */
	u_int8_t revoke_efuse_prog;
	/* Description - 0: no_pending_prog - No pending EFUSE programming command1: pending_prog - There is pending MFKV command */
	/* 0x0.4 - 0x0.4 */
	/* access: RO */
	u_int8_t pending_efuse_prog;
	/* Description -  */
	/* 0x0.8 - 0x0.9 */
	/* access: RO */
	u_int8_t fuse_failure;
	/* Description - Index of the key to revoke.0: NCORE_FW1: PSC_BL12: PSC_FW3: OEMAll other values are reserved. */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t index;
	/* Description - EFUSE key version */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t efuses_key_ver;
	/* Description - Image key version */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t img_key_ver;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_switch_mfmc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash select - selects the flash device.Only zero is supported for NICs with a single flash device.Range between 0 .. MFPA.flash_num -1 */
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t fs;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Power of 2 of the write protect block count0: 1 block1: 2 blocks2: 4 blocks3: 8 blocks etc.Range 0..5Note that per flash device there may be invalid configurationsReserved when wrp_en = 0 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t wrp_block_count;
	/* Description - Block size0: write protect sub-sector blocks1: write protect sector blocksReserved when wrp_en = 0Note that not all block sizes are supported on all flash device, need to
check MFPA capabilities */
	/* 0x4.16 - 0x4.17 */
	/* access: RW */
	u_int8_t block_size;
	/* Description - External WP signal: EROT/GPIO indication (1 = asserted). */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t hw_wp_gpio;
	/* Description - Write protect enableSet write protect of flash device */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t wrp_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Power of 2 for sub_sector size in 4Kbytes.0: 4Kbyte.1: 8 Kbyte2: 16Kbyte.Etc. */
	/* 0x8.0 - 0x8.5 */
	/* access: RO */
	u_int8_t sub_sector_protect_size;
	/* Description - Power of 2 for sector size in 4Kbytes.0: 4Kbyte.1: 8 Kbyte2: 16Kbyte.Etc. */
	/* 0x8.8 - 0x8.13 */
	/* access: RO */
	u_int8_t sector_protect_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Quad enable IO bit in the device status register */
	/* 0x10.24 - 0x10.24 */
	/* access: RW */
	u_int8_t quad_en;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The number of dummy clock cycles subsequent to all FAST READ commands.Reserved if not supported by the device */
	/* 0x18.0 - 0x18.3 */
	/* access: RW */
	u_int8_t dummy_clock_cycles;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_switch_mgpir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see
Hardware Info Layout */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mgpir_hw_info_ext hw_info;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - [Switch][DWIP]Hardware meta-data, see
Hardware Metadata Layout */
	/* 0x20.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_switch_mgpir_hw_metadata_ext hw_metadata;
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_switch_mkdc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates the successful completion of the instruction or the reason it
failed:0: OK1: BAD_SESSION_ID2: BAD_KEEP_ALIVE_COUNTER3: BAD_SOURCE_ADDRESS4: SESSION_TIMEOUTOther values are Reserved. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t error_code;
	/* Description - Unique debug session identifier. */
	/* 0x0.16 - 0x0.31 */
	/* access: INDEX */
	u_int16_t session_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Running counter that states the current sequence number of each
keep-alive session. */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t current_keep_alive_counter;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Running counter that states the expected next sequence number of each
keep-alive session. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t next_keep_alive_counter;
};

/* Description -   */
/* Size in bytes - 144 */
struct reg_access_switch_mmta_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - module number bits [7:0].Switch: Local module indexes.For read operation, supported concatenated module number ranges are -Range 1 base: MGPIR.tl_module_mission_base_index_localRange 1 count: <MGPIR.max_modules_per_slot_msb, MGPIR.max_modules_per_slot> - MGPIR.tl_module_non_mission_count_localRange 2 base: MGPIR.tl_module_non_mission_base_index_localRange 2 count: MGPIR.tl_module_non_mission_count_localRange 3 base: MGPIR.els_base_index_localRange 3 count: MGPIR.els_count_localRange 4 base: MGPIR.oe_base_index_localRange 4 count: MGPIR.oe_count_localFor write operation, only ranges 1 and 2 above are supported. */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - module number bits [15:8].Switch: Local module indexes.For read operation, supported concatenated module number ranges are -Range 1 base: MGPIR.tl_module_mission_base_index_localRange 1 count: <MGPIR.max_modules_per_slot_msb, MGPIR.max_modules_per_slot> - MGPIR.tl_module_non_mission_count_localRange 2 base: MGPIR.tl_module_non_mission_base_index_localRange 2 count: MGPIR.tl_module_non_mission_count_localRange 3 base: MGPIR.els_base_index_localRange 3 count: MGPIR.els_count_localRange 4 base: MGPIR.oe_base_index_localRange 4 count: MGPIR.oe_count_localFor write operation, only ranges 1 and 2 above are supported. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t module_msb;
	/* Description - Supported measurements bit maskBit 0: Temperature - ELS. Only set if the concatenation of <module_msb,
module> refers to the index of a top-level module or ELS.Bit 1: TEC Power. Only set if the concatenation of <module_msb, module>
refers to the index of a top-level module.Bit 2: Second Temperature - Optical Engines. Only set if the
concatenation of <module_msb, module> refers to the index of a top-level
module or OE.Other are reserved. */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t supported_measurements;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 8 characters long module name */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t module_name_hi;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - (see above) */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t module_name_lo;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Temperature, see Module Temperature Layout */
	/* 0xc.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_switch_mmta_temprature_ext module_temperature;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - TEC Power, see Module TEC Power Layout */
	/* 0x24.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_switch_mmta_tec_power_ext module_tec_power;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Second Temperature, see
Module Temperature Layout.Note: When there is more than one Optical Engine:1) The temperature field shall be populated by the highest of the
current OE temperatures.2) The max_temperature field shall be populated by the highest of any
temperatures that had been measured, over all OEs. */
	/* 0x44.0 - 0x58.31 */
	/* access: RW */
	struct reg_access_switch_mmta_temprature_ext module_second_temperature;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mord_v2_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - See Resource Dump section in the Adapters PRM. */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t segment_type;
	/* Description - Sequence number. 0 on first call of dump and incremented on each more
dump. */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t seq_num;
	/* Description - If set, then vhca_id field is valid. Otherwise dump resources on my
vhca_id.Not supported in Switch. */
	/* 0x0.29 - 0x0.29 */
	/* access: WO */
	u_int8_t vhca_id_valid;
	/* Description - If set, data is dumped in the register in inline_data field. otherwise
dump to mkey.Supports only inline dump = 1 */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t inline_dump;
	/* Description - If set, the device has additional information that has not been dumped
yet. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t more_dump;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - vhca_id where the resource is allocated.Not supported in Switch. */
	/* 0x4.0 - 0x4.15 */
	/* access: WO */
	u_int16_t vhca_id;
	/* Description - Number of data records. */
	/* 0x4.16 - 0x4.28 */
	/* access: OP */
	u_int16_t data_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - First object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the
next call in case dump_more==1. */
	/* 0x8.0 - 0x8.31 */
	/* access: INDEX */
	u_int32_t index1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Second object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the
next call in case dump_more==1. */
	/* 0xc.0 - 0xc.31 */
	/* access: INDEX */
	u_int32_t index2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The amount of objects to dump starting for index 2.SW shall read this field upon command done and shall provide it on the
next call in case dump_more==1.Range is 0..0xfff0. When the segment's num_of_obj2_supports_all is set,
the special value of 0xffff represents all. When the segment's
num_of_objx_supports_active is set, the special value of 0xfffe
represents active. The value of 0x0 and 0x1 are allowed even if the
supported_num_of_obj2 is 0. */
	/* 0x10.0 - 0x10.15 */
	/* access: INDEX */
	u_int16_t num_of_obj2;
	/* Description - The amount of objects to dump starting for index 1SW shall read this field upon command done and shall provide it on the
next call in case dump_more==1.Range is 0..0xfff0. When the segment's num_of_obj1_supports_all is set,
the special value of 0xffff represents all. When the segment's
num_of_objx_supports_active is set, the special value of 0xfffe
represents active. The value of 0x0 and 0x1 are allowed even if the
supported_num_of_obj1 is 0. */
	/* 0x10.16 - 0x10.31 */
	/* access: INDEX */
	u_int16_t num_of_obj1;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - An opaque provided by the device. SW shall read the device_opaque upon
command done and shall provide it on the next call in case dump_more==1.
On first call, device_opaque shall be 0. */
	/* 0x18.0 - 0x1c.31 */
	/* access: INDEX */
	u_int64_t device_opaque;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Memory key to dump to.Valid when inline_dump==0.Not supported in Switch. */
	/* 0x20.0 - 0x20.31 */
	/* access: WO */
	u_int32_t mkey;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - In write, the size of maximum allocated buffer that the device can use.In read, the actual written size.In granularity of Bytes.Not supported in Switch. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t size;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - VA address (absolute address) of memory where to start dumping.Valid when inline_dump==0.Not supported in Switch. */
	/* 0x28.0 - 0x2c.31 */
	/* access: WO */
	u_int64_t address;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Data that is dumped in case of inline mode.Valid when inline_dump==1. */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t *inline_data;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mpein_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - PCIe index number (internal domain index)Reserved when access is from the host, but can be used when operating in
Socket-Direct mode. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version0: multi_topology_unaware_sw1: multi_topology_aware_sw */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Max Link Speed:Bit 0: 2.5G - (Gen1)Bit 1: 5G - (Gen2)Bit 2: 8G - (Gen3)Bit 4: 16G - (Gen4)Bit 5: 32G (Gen5)Bit 6: 32G PAM-4 (Gen6) */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t link_speed_enabled;
	/* Description - Maximum Link Width enabled:1: 1x2: 2x4: 4x8: 8x16: 16x */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t link_width_enabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Current Link Speed:Bit 0: 2.5G (Gen1)Bit 1: 5G (Gen2)Bit 2: 8G (Gen3)Bit 4: 16G (Gen4)Bit 5: 32G (Gen5)Bit 6: 32G PAM-4 (Gen6) */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - Negotiated Link Width, pcie_link_width active:1: 1x2: 2x4: 4x8: 8x16: 16x */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t link_width_active;
	/* Description - The physical lane position of logical lane0 */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t lane0_physical_position;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of Total Virtual Functions (for all PFs) */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t num_of_vfs;
	/* Description - Number of Physical Functions (PFs) */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t num_of_pfs;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Bus Device Function - only for function0 */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t bdf0;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Reversal mode of the link:0 - straight1 - reversalNote: together with lane0_physical_position provide the physical lane. */
	/* 0x18.0 - 0x18.0 */
	/* access: RO */
	u_int8_t lane_reversal;
	/* Description - common clock mode:0 - separate clock mode1 - common clock mode */
	/* 0x18.1 - 0x18.1 */
	/* access: RO */
	u_int8_t cmn_clk_mode;
	/* Description - Indicates the specific type of this PCI Express Function. Note that
different Functions in a multi-Function device can generally be of
different types.0 - PCI Express Endpoint port4 - Root Port of PCI Express Root Complex5 - PCI Express Upstream port6 - PCI Express Downstream port */
	/* 0x18.12 - 0x18.15 */
	/* access: RO */
	u_int8_t port_type;
	/* Description - Indicates the status of PCI power consumption limitations.0: PCI power report could not be read.1: Sufficient power reported.2: Insufficient power reported.3-7: Reserved */
	/* 0x18.16 - 0x18.18 */
	/* access: RO */
	u_int8_t pwr_status;
	/* Description - Max payload size in bytes:0 - 128B1 - 256B2 - 512B3 - 1024B4 - 2048B5 - 4096B */
	/* 0x18.24 - 0x18.27 */
	/* access: RO */
	u_int8_t max_payload_size;
	/* Description - Max read request size in bytes:0 - 128B1 - 256B2 - 512B3 - 1024B4 - 2048B5 - 4096B */
	/* 0x18.28 - 0x18.31 */
	/* access: RO */
	u_int8_t max_read_request_size;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Power reported by the PCI device. The units are in Watts.0: Power is unknown. */
	/* 0x1c.0 - 0x1c.11 */
	/* access: RO */
	u_int16_t pci_power;
	/* Description - Peer Max Link Speed:Bit 0: 2.5G - (Gen1)Bit 1: 5G - (Gen2)Bit 2: 8G - (Gen3)Bit 4: 16G - (Gen4)Bit 5: 32G (Gen5)Bit 6: 32G PAM-4 (Gen6) */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t link_peer_max_speed;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - FLIT is supported for the current active speed */
	/* 0x20.0 - 0x20.0 */
	/* access: RO */
	u_int8_t flit_sup;
	/* Description - Precoding is supported for the current active speed */
	/* 0x20.1 - 0x20.1 */
	/* access: RO */
	u_int8_t precode_sup;
	/* Description - FLIT is active for the current speed */
	/* 0x20.8 - 0x20.8 */
	/* access: RO */
	u_int8_t flit_active;
	/* Description - precoding is active for the current speed */
	/* 0x20.9 - 0x20.9 */
	/* access: RO */
	u_int8_t precode_active;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - device_status bit mask:Bit 0: Correctable_errorBit 1: Non_Fatal_Error_detectionBit 2: Fatal_Error_detectedBit 3: Unsupported_request_detectedBit 4: AUX_powerBit 5: Transaction_Pending */
	/* 0x24.16 - 0x24.31 */
	/* access: RO */
	u_int16_t device_status;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_mpir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of PCIe buses available for the host to connect ot the device.0' when operating in non-Socket-Direct mode. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t host_buses;
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - internal domain index */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version0: multi_topology_unaware_sw1: multi_topology_aware_sw */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
	/* Description - Socket-Direct mode indication.0: non-Socket-Direct mode (single host or multi-host)1: Socket-Direct mode, for querying host */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t sdm;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - sunbordinate bus - the highest bus number that subordinates to switch.Default value of 0' in case it is not a switch port. */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t subordinate_bus;
	/* Description - secondary bus - the internal logic bus in the switch.Default value of 0' in case it is not a switch port. */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t secondary_bus;
	/* Description - if segment valid is set this field has the segment number of the PCIe
hierarchy of the link.segment_cap = 1 : segment base that was captured in Flit modesegment_cap = 0 : segment base that was set by softwarereserved when pcie_segment is not set in MPCAM */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t segment_base;
	/* Description - when set segment base is valid, else it is invalidmust be set if segment_cap is set.reserved when pcie_segment is not set in MPCAM */
	/* 0x4.24 - 0x4.24 */
	/* access: RO */
	u_int8_t segment_valid;
	/* Description - segment number (base) was captured in Flit mode.reserved when pcie_segment is not set in MPCAM */
	/* 0x4.25 - 0x4.25 */
	/* access: RO */
	u_int8_t segment_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - PCIe device number. */
	/* 0x8.3 - 0x8.7 */
	/* access: RO */
	u_int8_t device;
	/* Description - 2-bit expansion of the local port. Represents the local_port[9:8] bits */
	/* 0x8.12 - 0x8.13 */
	/* access: RO */
	u_int8_t lp_msb;
	/* Description - PCIe bus number. */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t bus;
	/* Description - Local port number */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t local_port;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Slot number */
	/* 0xc.0 - 0xc.12 */
	/* access: RO */
	u_int16_t slot_number;
	/* Description - number of PCIe connected deices / EP on the current port. */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t num_con_devices;
	/* Description - Host index associated with the pcie_inex */
	/* 0xc.24 - 0xc.30 */
	/* access: RO */
	u_int8_t host_index;
	/* Description - If set to 1', slot_number field is supported. */
	/* 0xc.31 - 0xc.31 */
	/* access: RO */
	u_int8_t slot_cap;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_mrsr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Reset/shutdown command:0: clear state of reset_at_pci_disable, and return to default, which is
Hot Reset. In case of Unmanaged Switch, returns BAD_PARAM.1: Immediate software reset (switch soft reset). of
6: reset_at_pci_disable - All reset will be done at PCI_DISABLE. See
MCAM bit48. Note: when no PCI (e.g. unmanaged switches or for Retimers)
will do All Reset without waiting for PCI_DISABLE7: fw_link_reset_at_pci_disable - PCIe FW Link Reset, core is up [SPC-4
onwards, QM-3 onwards]. In case of Unmanaged Switch, returns BAD_PARAM. */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t command;
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_switch_msgi_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ASIC serial number (ASCII string) */
	/* 0x0.0 - 0x14.31 */
	/* access: RO */
	u_int32_t serial_number[6];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - ASIC part number (ASCII string) */
	/* 0x20.0 - 0x30.31 */
	/* access: RO */
	u_int32_t part_number[5];
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Revision (ASCII string) */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t revision;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Product Name (ASCII string) */
	/* 0x40.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t product_name[16];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mspmer_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device Index0: Main_board_or_NIC */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t device_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Status0: Success1: Physical monitor is not supported2: Device index is not valid */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - Clear Counters0: don't clear counters1: clear counters */
	/* 0x4.16 - 0x4.16 */
	/* access: OP */
	u_int8_t clr;
	/* Description - Prevention Enable0: Notification only. Prevention is disabled1: Prevention is enabledIn Spectrum-4 only, controlled by NV_SWITCH_PHY_SEC_CONF.pvpm. See
NV_SWITCH_PHY_SEC_CONF Layout */
	/* 0x4.24 - 0x4.24 */
	/* access: RO */
	u_int8_t prev_en;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - 31: FMON - Frequency MONitor30: VMON - Voltage MONitor29: SCPM - Secure Canary Path Monitor0: General */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t supported_physical_monitor;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Frequency Monitor  CounterStuck at 0xF, cleared only at hard reset (RST_) or power down or clr
bit. */
	/* 0x14.0 - 0x14.3 */
	/* access: RO */
	u_int8_t fmon_ctr;
	/* Description - Voltage Monitor CounterStuck at 0xF, cleared only at hard reset (RST_) or power down or clr
bit. */
	/* 0x14.4 - 0x14.7 */
	/* access: RO */
	u_int8_t vmon_ctr;
	/* Description - Security Canary Path Monitor CounterA circuit macro used to flag timing slack violations as part of
mitigations for physical security attacks.Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr
bit. */
	/* 0x14.8 - 0x14.11 */
	/* access: RO */
	u_int8_t scpm_ctr;
	/* Description - General Error indicationCleared only at hard reset (RST_) or power down or clr bit. */
	/* 0x14.12 - 0x14.12 */
	/* access: RO */
	u_int8_t general_err;
};

/* Description -   */
/* Size in bytes - 112 */
struct reg_access_switch_mtcq_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device number.For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1
while index 0 indicates the host device. */
	/* 0x0.0 - 0x0.11 */
	/* access: INDEX */
	u_int16_t device_index;
	/* Description - Indicates the status of the desired token we are generating the
challenge for.0x0 - OK0x1 - TOKEN_ALREADY_APPLIED0x2 - TOKEN_NOT_SUPPORTED0x3 - NO_KEY_CONFIGURED (there is no public_key that can be used for
this token)0x4 - INTERFACE_NOT_ALLOWED (asking for local token from remote
interface, or remote token from local interface)0x5 - TOKEN_APPLY_TIMEOUT_EXPIRED */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t status;
	/* Description - The token which a challenge is generated for.0: RMCS - (ReMote Customer Support)1: RMDT - (ReMote Debug Token)2: CRCS - (Challenge-Response Customer Support) - supported from
Spectrum-4 and above3: CRDT - (Challenge-Response Debug Token) - supported from Spectrum-4
and above5: MTDT6: FRC - (Factory ReCustomization)7: MTFAOther: Reserved */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t token_opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The UUID of the key used to generate the challenge. */
	/* 0x4.0 - 0x10.31 */
	/* access: RO */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Device base MAC address / unique identifier. */
	/* 0x14.0 - 0x18.31 */
	/* access: RO */
	u_int64_t base_mac;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Device PSID */
	/* 0x1c.0 - 0x28.31 */
	/* access: RO */
	u_int32_t psid[4];
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Device FW version */
	/* 0x2c.0 - 0x2c.7 */
	/* access: RO */
	u_int8_t fw_version_39_32;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - (see above) */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t fw_version_31_0;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Source address of debug requester. DLID for
InfinibandValid only for RMCS/RMDT. */
	/* 0x34.0 - 0x40.31 */
	/* access: RO */
	u_int32_t source_address[4];
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Unique debug session identifier.See details in REMOTE_DEBUG_KEEP_ALIVE.Valid only for RMCS. */
	/* 0x44.0 - 0x44.15 */
	/* access: RO */
	u_int16_t session_id;
	/* Description - Version of the challenge format. */
	/* 0x44.24 - 0x44.31 */
	/* access: RO */
	u_int8_t challenge_version;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Random generated field. Used for randomness and replay-protection. */
	/* 0x48.0 - 0x64.31 */
	/* access: RO */
	u_int32_t challenge[8];
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Current device's token rachet value. */
	/* 0x68.0 - 0x6c.31 */
	/* access: RO */
	u_int64_t token_ratchet;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_switch_mtecr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of sensors supported by the ASIC+platformThis includes the ASIC, ambient sensors, module sensors, Gearboxes etc.This actually is equal to sum of all 1' in sensor_mapKnown sensors:See MTMP.sensor_index description. */
	/* 0x0.0 - 0x0.11 */
	/* access: RO */
	u_int16_t sensor_count;
	/* Description - Last sensor index that is available in the system to read from.e.g. when 32modules: 64+32-1 = 95 */
	/* 0x0.16 - 0x0.27 */
	/* access: RO */
	u_int16_t last_sensor;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of sensors supported by the device that are on the ASIC.Exposes how many ASIC diodes exist.The FW exposes all of them as sensor[0] */
	/* 0x4.0 - 0x4.6 */
	/* access: RO */
	u_int8_t internal_sensor_count;
	/* Description - Slot index0: Main board */
	/* 0x4.28 - 0x4.31 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Mapping of system sensors supported by the device. Each bit represents a
sensor.This field is size variable based on the last_sensor field and in
granularity of 32bits.Per bit:0: Not connected or not supported1: Supports temperature measurementsIn case of last_sensor = 704 (22*32):sensor_warning[0] bit31 is sensor_warning[703]sensor_warning[0] bit0 is sensor_warning[703-31]sensor_warning[21] bit31 is sensor_warning[31]sensor_warning[21] bit0 is sensor_warning[0]In case if last_sensor = 259 (22*32):Note: roundup(259,32)=288sensor_warning[0] bit31 is sensor_warning[287]sensor_warning[0] bit0 is sensor_warning[287-31=256]sensor_warning[8] bit31 is sensor_warning[31]sensor_warning[8] bit0 is sensor_warning[0]sensor_warning[9..21] are not used64-192 of sensor_index are mapped to the modules sequentially (module 0
is mapped to sensor_index 64, module 1 to sensor_index 65 and so on). */
	/* 0x8.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t sensor_map[22];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mtsh_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Unit time of time which each bin is counting. Unit is equal totime_measure_unit in time_unitFor exmple:time_unit = 0time_measure_unit = 500Each bit tick is 500 useconds */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t time_measure_unit;
	/* Description - See MTMP.sensor_index (for MTMP.i = 0 and MTMP.ig = 0). */
	/* 0x0.16 - 0x0.27 */
	/* access: INDEX */
	u_int16_t sensor_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Unit time of0 - useconds1 - miliseconds */
	/* 0x4.0 - 0x4.1 */
	/* access: RO */
	u_int8_t time_unit;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Each element indicates the duration that the device was in this thermal
state. The total time equals to the element value * unit_time_measure.thermal_state[0]: Normalthermal_state[1]: High Warning.thermal_state[2]: High Critical.thermal_state[3]: Low Critical. */
	/* 0x10.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t thermal_state[8];
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_switch_pddr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Supported only when indicated by PCAM0: Network_port1: Near_End_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the
aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number.: */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Module index type selector:0: CPO_or_pluggable_modules1: OE2: ELS */
	/* 0x0.24 - 0x0.25 */
	/* access: INDEX */
	u_int8_t module_ind_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - page select index:0: Operational_info_page1: Troubleshooting_info_page2: Phy_info_page3: Module_info_page6: link_down_info8: Link_up_info9: Module_latched_flag_info_page11: link_partner_info_page14: cpo_module_info_page15: link_health_fec_measure_info_page16: APSU_info_page17: link_health_fec_measure_nvl5_page */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t page_select;
	/* Description - Module info extended configurations.resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power,
tx_power_high_th, tx_power_low_th in module info page0: dbm1: uW */
	/* 0x4.29 - 0x4.30 */
	/* access: OP */
	u_int8_t module_info_ext;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Operation Info Page LayoutTroubleshooting info Page layoutPhy Info Page LayoutModule Info Page LayoutLink Down Info Page LayoutLink Up Info Page LayoutModule Latched Flag Info Page LayoutLink Partner Info Page LayoutCPO Module Page LayoutLink Health FEC Measure Info Page LayoutAPSU Info Page LayoutLink Health FEC Measure NVL5 Page Layout */
	/* 0x8.0 - 0xfc.31 */
	/* access: RO */
	union reg_access_switch_pddr_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_switch_pguid_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - System GUID.Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x4.0 - 0x10.31 */
	/* access: RO */
	u_int32_t sys_guid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Node GUID.Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x14.0 - 0x20.31 */
	/* access: RO */
	u_int32_t node_guid[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Port GUID.Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x24.0 - 0x30.31 */
	/* access: RO */
	u_int32_t port_guid[4];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Allocated GUID.Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x34.0 - 0x40.31 */
	/* access: RO */
	u_int32_t allocated_guid[4];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_plib_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - In IB port: InfiniBand port remapping for local_portIn Ethernet port: Label port remapping for local_portNote: ib_port number can only be updated when a port admin state is
DISABLED. */
	/* 0x0.0 - 0x0.9 */
	/* access: RW */
	u_int16_t ib_port;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Valid only for Ethernet Switches.Label split mapping for local_portValid values:For Spectrum 1 to 4: 1, 2, 4, 8For Spectrum 5, 6: 1...6, 8 */
	/* 0x4.0 - 0x4.3 */
	/* access: RW */
	u_int8_t split_num;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_pllp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Front panel label of the portNote:PLIB.ib_port provides IB port in IB and label_port in EthMOLP provides the 16bit mirror header value */
	/* 0x0.0 - 0x0.9 */
	/* access: RO */
	u_int16_t label_port;
	/* Description - Local port[9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Defines the split permutation state of each IPIL into local ports by the
following format: total number of ports, Lanes 1-4 configuration, Lanes
5-8 configuration0: See split_num, see split_stat, see split_stat1: 1, -, - (One port of 8x according to speed capability)2: 2, 1 port of 4x, 1 port of 4x3: 3, 1 port of 4x, 2 ports of 2x4: 3, 2 ports of 2x, 1 port of 4x5: 4, 2 ports of 2x, 2 ports of 2x6: 5, 1 port of 4x, 4 ports of 1x7: 5, 4 ports of 1x, 1 port of 4x8: 6, 2 ports of 2x, 4 ports of 1x9: 6, 4 ports of 1x, 2 ports of 2x10: 7, -, -11: 8, 4 ports of 1x, 4 ports of 1x15: undefined configurationSupported from SPC5 onwardNote: This field is valid only when the sum of local ports width in the
IPIL is 8 otherwise split_info return undefined value */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t split_info;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The position of this local port within each split IPIL port.When no split: split_num should be 0When split to 2: split_num should be 0,1When split to 3: split_num should be 02When split to 4: split_num should be 03When split to 5: split_num should be 04When split to 6: split_num should be 05When split to 7: split_num should be 06When split to 8: split_num should be 07Split to 8 exists only for ETH */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t split_num;
	/* Description - Inter port in Label number.Gives mapping of the basic port unit / MPO
 inside the label (cage),
From the lowest lanes of the module to the highest.e.g Label of 8x lanes, with 2 ipilipil 1 - will be port mapped to lanes 1-4ipil 2 - will be port mapped to lanes 5-8When ipil_stat is 0 (no ipil): ipil_num should be 0.When ipil_stat is 1: ipil_num should be 1,2When ipil_stat is 2: ipil_num should be 14When ipil_stat is 3: ipil_num should be 18 */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t ipil_num;
	/* Description - Defines the split of each IPIL into local ports.0: no split1: split to 2 local ports2: split to 4 local ports3: split to 8 local ports4: split to 3 local ports5: split to 5 local ports6: split to 6local ports7: split to 7local ports */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t split_stat;
	/* Description - Inter port in Label status.Number of inter port units / MPOs inside the label (cage). Determined
strictly by the form factor.0: 1 inter port in label1: 2 inter port in label2: 4 inter port in label3: 8 inter port in label. */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t ipil_stat;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Valid only for Ethernet Switches.Slot_number mapping for local_port */
	/* 0x8.0 - 0x8.3 */
	/* access: RO */
	u_int8_t slot_num;
	/* Description - [DWIP]ELS index, bits [7:0]. */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t els_index;
	/* Description - [DWIP]ELS index, bits [15:8]. */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t els_index_msb;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Connectivity Type0: N/A1: not-wired 2: wire to front panel3: wired to Switch4: wired to GPU5: wired to NICDescribes the internal wiring on the port.Quantum: Supported from Quantum-3 and above.Spectrum: Only relevant value is 0. */
	/* 0xc.0 - 0xc.2 */
	/* access: RO */
	u_int8_t conn_type;
	/* Description - [DWIP]Indicates whether cartridge_id field is valid. */
	/* 0xc.3 - 0xc.3 */
	/* access: RO */
	u_int8_t cartridge_id_valid;
	/* Description - [DWIP]Cartridge ID. Only valid if cartridge_id_valid = 1. */
	/* 0xc.4 - 0xc.7 */
	/* access: RO */
	u_int8_t cartridge_id;
	/* Description - Remote ASIC IdReserved when conn_type = 0/1/2Quantum: Supported from Quantum-3 and above.Spectrum: Reserved as 0.Obsolete and not updated by FW. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t rmt_id;
	/* Description - 0: Mission port1: FNM  portSupported from Quantum-3 and above */
	/* 0xc.16 - 0xc.16 */
	/* access: RO */
	u_int8_t is_fnm;
	/* Description - Mission Port as FNM 0: Mission port1: Mission port treated as FNM port.When set, the port shall be configured as a FNM port.Reserved when is_fnm is set.Note: This configuration does not change port type as stated in is_fnm
field.Quantum: Supported from Quantum-3 and above.Spectrum: Only relevant value is 0. */
	/* 0xc.17 - 0xc.17 */
	/* access: RO */
	u_int8_t maf;
	/* Description - [DWIP]module_msb and module fields are valid. */
	/* 0xc.18 - 0xc.18 */
	/* access: RO */
	u_int8_t module_valid;
	/* Description - [DWIP]els_index_msb and els_index fields are valid. */
	/* 0xc.19 - 0xc.19 */
	/* access: RO */
	u_int8_t els_valid;
	/* Description - [DWIP]Logical lane index of this port within the cartridge (0-based). Only
valid if cartridge_id_valid = 1. */
	/* 0xc.20 - 0xc.22 */
	/* access: RO */
	u_int8_t cartridge_lane_index;
	/* Description - [DWIP]Top-level module ID, bits [15:8]. */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t module_msb;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - 0: N/A (when FW has no info)1: ETH (for Eth devices)2: IB3: NVLinkSupported from Quantum-3 and above */
	/* 0x10.0 - 0x10.2 */
	/* access: RO */
	u_int8_t protocol;
	/* Description - [DWIP]Sub Module ID.Indicates start offset of module lanes in 8x granularity */
	/* 0x10.20 - 0x10.23 */
	/* access: RO */
	u_int8_t sub_module;
	/* Description - [DWIP]Top-level module ID, bits [7:0]. */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t module;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - [DWIP]Resource label portThe label port for the resource module.Value of 0xFFFF means field is not valid. */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t resource_label_port;
	/* Description - [DWIP]Optical engine identifier, which represents the OE index which the port
is connected to.Value of 0xFFFF means field is not valid. */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t oe_identifier;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_pmaos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module state (reserved while admin_status is disabled):0: initializing 1: plugged_enabled2: unplugged3: module_plugged_with_error - (details in error_type).5: unknown */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - [Retimer][Switch]1: SeRBI check failure indication. */
	/* 0x0.4 - 0x0.4 */
	/* access: RO */
	u_int8_t serbi_failure;
	/* Description - Module administrative state (the desired state of the module):1: enabled2: disabled_by_configuration3: enabled_once - if the module is active and then unplugged, or
module experienced an error event, the operational status should go
to disabled and can only be enabled upon explicit enable command.0xe: disconnect_cableNote - To disable a module, all ports associated with the port must
be disabled first.Note 2 - disconnect cable will shut down the optical module in
ungraceful manner. Not supported for OE/ELS.Note 3 - Disabling OE in QM-3 CPO will not cause to the OE to power disable. User will need to set all the modules to disable, which will cause the power enable to go down.Note 4 - Disabling OE in QM3-CPO will cause the ELS to go down as well as part of the HW flow. Before setting the ELS back up, OE should be set to up beforehand. */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t admin_status;
	/* Description - Module number bits [7:0].Switch: Local module indexes. Supported concatenated module number ranges are -Range 1 base: MGPIR.tl_module_mission_base_index_localRange 1 count: <MGPIR.max_modules_per_slot_msb, MGPIR.max_modules_per_slot> - MGPIR.tl_module_non_mission_count_localRange 2 base: MGPIR.tl_module_non_mission_base_index_localRange 2 count: MGPIR.tl_module_non_mission_count_local */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module Reset toggleNOTE: setting reset while module is plugged-in will result in transition
of oper_status to initialization. */
	/* 0x0.31 - 0x0.31 */
	/* access: OP */
	u_int8_t rst;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event Generation on operational state change:0: Do_not_generate_event1: Generate_Event2: Generate_Single_EventNot supported by secondary ASICs. */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t e;
	/* Description - [Switch][DWIP]1: ref_module field valid. */
	/* 0x4.2 - 0x4.2 */
	/* access: RO */
	u_int8_t ref_module_valid;
	/* Description - Module error details:0x0: Power_Budget_Exceeded0x1: Long_Range_for_non_MLNX_cable_or_module0x2: Bus_stuck - (I2C Data or clock shorted)0x3: bad_or_unsupported_EEPROM0x4: Enforce_part_number_list0x5: unsupported_cable0x6: High_Temperature0x7: bad_cable - (Module/Cable is shorted)0x8: PMD_type_is_not_enabled - (see PMTPS)


0xc: pcie_system_power_slot_Exceeded


[DWIP] 0xf: Boot_error
[DWIP] 0x10: Recovery_error
[DWIP] 0x11: Submodule_failure
[DWIP] 0x12: serbi_check_failure
[DWIP] 0x13: els_critical_indication
Valid only when oper_status = 4'b0011 */
	/* 0x4.8 - 0x4.12 */
	/* access: RO */
	u_int8_t error_type;
	/* Description - This notification can occur only if module passed initialization process0x0: No notifications.0x1: Speed degradation  the module is not enabled in its full speed due
to incompatible transceiver/cableValid only when oper_status = 4'b0001. */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t operational_notification;
	/* Description - [Switch][DWIP]Module number bits [15:8].Switch: Local module indexes. Supported concatenated module number ranges are -Range 1 base: MGPIR.tl_module_mission_base_index_localRange 1 count: <MGPIR.max_modules_per_slot_msb, MGPIR.max_modules_per_slot> - MGPIR.tl_module_non_mission_count_localRange 2 base: MGPIR.tl_module_non_mission_base_index_localRange 2 count: MGPIR.tl_module_non_mission_count_local */
	/* 0x4.20 - 0x4.27 */
	/* access: INDEX */
	u_int8_t module_msb;
	/* Description - When in multi ASIC module sharing systems,This flag will be asserted in case primary and secondary FW versions are
not compatible. */
	/* 0x4.28 - 0x4.28 */
	/* access: RO */
	u_int8_t rev_incompatible;
	/* Description - Indicates whether the ASIC serves as a the modules secondary (=1) or
primary (=0) device. */
	/* 0x4.29 - 0x4.29 */
	/* access: RO */
	u_int8_t secondary;
	/* Description - Event update enable. If this bit is set, event generation will be
updated based on the e field. Only relevant on Set operations.Not supported by secondary ASICs. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t ee;
	/* Description - Admin status update enable. If this bit is set, admin state will be
updated based on admin_state field. Only relevant on Set() operations. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t ase;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - [Switch][DWIP]Reference module index. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t ref_module;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_switch_pmdr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.0 - 0x0.1 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the
aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - When set, port_width field value is valid. otherwise ignored */
	/* 0x0.10 - 0x0.10 */
	/* access: RO */
	u_int8_t width_valid;
	/* Description - 0 if there is no MCM tile arch */
	/* 0x0.12 - 0x0.12 */
	/* access: RO */
	u_int8_t mcm_tile_valid;
	/* Description - 0 if there is no Gearbox/Retimer arch */
	/* 0x0.13 - 0x0.13 */
	/* access: RO */
	u_int8_t gb_valid;
	/* Description - Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - [7:0] bits for Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - 0 - 40nm products1 - 28nm products3 - 16nm products4 - 7nm products5 - 5nm products SerDes Gen7.0/ 7.56 - 5nm products SerDes Gen8.0 */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t version;
	/* Description - 0 - Invalid1 - Valid2 - Bad Param (Values are not ready yet - during polling)3 - Invalid index of local_port or label_port */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - PPORT number. The full 14-bit pport value is assembled from three fields:
bits [7:0] from pport field,
bits [9:8] from pport_msb field,
bits [13:10] from pport_msb_ext field. */
	/* 0x4.6 - 0x4.7 */
	/* access: RO */
	u_int8_t pport_msb;
	/* Description - Logical cluster number */
	/* 0x4.8 - 0x4.14 */
	/* access: RO */
	u_int8_t cluster;
	/* Description -  */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t module;
	/* Description - PPORT number. The full 14-bit pport value is assembled from three fields:
bits [7:0] from pport field,
bits [9:8] from pport_msb field,
bits [13:10] from pport_msb_ext field. */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t pport;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t ib_port;
	/* Description - lane mask of active lanes on moduleBit 0: Lane 0Bit 1: Lane 1Bit 2: Lane 2Bit 3: Lane 3Bit 4: Lane 4Bit 5: Lane 5Bit 6: Lane 6Bit 7: Lane 7 */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t module_lane_mask;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t swid;
	/* Description - Number of ports the label port is split to.0 - split to 11 - split to 22 - split to 43 - split to 84 - split to 35 - split to 56 - split to 67 - split to 7 */
	/* 0x8.24 - 0x8.26 */
	/* access: RO */
	u_int8_t split;
	/* Description - DataPath number in GB/Retimer of the port */
	/* 0x8.27 - 0x8.31 */
	/* access: RO */
	u_int8_t gb_dp_num;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Local port index for the label port chosen (valid when pnat=1). The full
14-bit value is assembled from three fields:
bits [7:0] from local_port_query field,
bits [9:8] from lp_query_msb field,
bits [13:10] from lp_query_msb_ext field. */
	/* 0xc.0 - 0xc.1 */
	/* access: RO */
	u_int8_t lp_query_msb;
	/* Description - MSB Label port bits [9:8] index. */
	/* 0xc.2 - 0xc.3 */
	/* access: RO */
	u_int8_t lbp_query_msb;
	/* Description - MSB tile_pport bits [7:6] index. */
	/* 0xc.4 - 0xc.5 */
	/* access: RO */
	u_int8_t tile_pport_msb;
	/* Description - Port width of logical lanes.According to number of port width, indicates how many lanes shall be
considered in lane<i>_physical_tx/rx0 - port is unmapped */
	/* 0xc.6 - 0xc.9 */
	/* access: RO */
	u_int8_t port_width;
	/* Description - Local port index for the label port chosen (valid when pnat=1). The full
14-bit value is assembled from three fields:
bits [7:0] from local_port_query field,
bits [9:8] from lp_query_msb field,
bits [13:10] from lp_query_msb_ext field. */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t local_port_query;
	/* Description - Label port index for the local port chosen (in case pnat field is 0'). */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t label_port_query;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of the Gearbox/Retimer the local_port is related to.valid only when gb_valid is 1 */
	/* 0x10.0 - 0x10.6 */
	/* access: RO */
	u_int8_t gearbox_die_num;
	/* Description -  */
	/* 0x10.8 - 0x10.12 */
	/* access: RO */
	u_int8_t tile_pport;
	/* Description - Number of common PLLs mapped to port rx lanes. */
	/* 0x10.13 - 0x10.15 */
	/* access: RO */
	u_int8_t pll_cnt_rx;
	/* Description - Number of the MCM Tile the local_port is related to.valid only when mcm_tile_valid is 1 */
	/* 0x10.16 - 0x10.23 */
	/* access: RO */
	u_int8_t mcm_tile_num;
	/* Description -  */
	/* 0x10.24 - 0x10.27 */
	/* access: RO */
	u_int8_t tile_cluster;
	/* Description - Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available. */
	/* 0x10.28 - 0x10.31 */
	/* access: RO */
	u_int8_t slot_index;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - (see above) */
	/* 0x14.0 - 0x14.2 */
	/* access: RO */
	u_int8_t lane0_physical_rx;
	/* Description - (see above) */
	/* 0x14.3 - 0x14.5 */
	/* access: RO */
	u_int8_t lane1_physical_rx;
	/* Description - (see above) */
	/* 0x14.6 - 0x14.8 */
	/* access: RO */
	u_int8_t lane2_physical_rx;
	/* Description - (see above) */
	/* 0x14.9 - 0x14.11 */
	/* access: RO */
	u_int8_t lane3_physical_rx;
	/* Description - (see above) */
	/* 0x14.12 - 0x14.14 */
	/* access: RO */
	u_int8_t lane4_physical_rx;
	/* Description - (see above) */
	/* 0x14.15 - 0x14.17 */
	/* access: RO */
	u_int8_t lane5_physical_rx;
	/* Description - (see above) */
	/* 0x14.18 - 0x14.20 */
	/* access: RO */
	u_int8_t lane6_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.21 - 0x14.23 */
	/* access: RO */
	u_int8_t lane7_physical_rx;
	/* Description - Number of common PLLs mapped to port for tx lanes. */
	/* 0x14.24 - 0x14.26 */
	/* access: RO */
	u_int8_t pll_cnt_tx;
	/* Description - largest VL number of the port.for e.g if vl_num = 3VL<0-3>_lane_map are only valid */
	/* 0x14.27 - 0x14.31 */
	/* access: RO */
	u_int8_t vl_num;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - (see above) */
	/* 0x18.0 - 0x18.2 */
	/* access: RO */
	u_int8_t lane0_physical_tx;
	/* Description - (see above) */
	/* 0x18.3 - 0x18.5 */
	/* access: RO */
	u_int8_t lane1_physical_tx;
	/* Description - (see above) */
	/* 0x18.6 - 0x18.8 */
	/* access: RO */
	u_int8_t lane2_physical_tx;
	/* Description - (see above) */
	/* 0x18.9 - 0x18.11 */
	/* access: RO */
	u_int8_t lane3_physical_tx;
	/* Description - (see above) */
	/* 0x18.12 - 0x18.14 */
	/* access: RO */
	u_int8_t lane4_physical_tx;
	/* Description - (see above) */
	/* 0x18.15 - 0x18.17 */
	/* access: RO */
	u_int8_t lane5_physical_tx;
	/* Description - (see above) */
	/* 0x18.18 - 0x18.20 */
	/* access: RO */
	u_int8_t lane6_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.21 - 0x18.23 */
	/* access: RO */
	u_int8_t lane7_physical_tx;
	/* Description - minimal index of pll group of pll that port uses for tx lanes.For all common pll's that are mapped to the port: [pll_index, pll_index+
1, ... pll_index + pll_cnt] */
	/* 0x18.24 - 0x18.31 */
	/* access: RO */
	u_int8_t pll_index;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - (see above) */
	/* 0x1c.0 - 0x1c.3 */
	/* access: RO */
	u_int8_t VL0_lane_map;
	/* Description - (see above) */
	/* 0x1c.4 - 0x1c.7 */
	/* access: RO */
	u_int8_t VL1_lane_map;
	/* Description - (see above) */
	/* 0x1c.8 - 0x1c.11 */
	/* access: RO */
	u_int8_t VL2_lane_map;
	/* Description - (see above) */
	/* 0x1c.12 - 0x1c.15 */
	/* access: RO */
	u_int8_t VL3_lane_map;
	/* Description - (see above) */
	/* 0x1c.16 - 0x1c.19 */
	/* access: RO */
	u_int8_t VL4_lane_map;
	/* Description - (see above) */
	/* 0x1c.20 - 0x1c.23 */
	/* access: RO */
	u_int8_t VL5_lane_map;
	/* Description - (see above) */
	/* 0x1c.24 - 0x1c.27 */
	/* access: RO */
	u_int8_t VL6_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.28 - 0x1c.31 */
	/* access: RO */
	u_int8_t VL7_lane_map;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - (see above) */
	/* 0x20.0 - 0x20.3 */
	/* access: RO */
	u_int8_t VL8_lane_map;
	/* Description - (see above) */
	/* 0x20.4 - 0x20.7 */
	/* access: RO */
	u_int8_t VL9_lane_map;
	/* Description - (see above) */
	/* 0x20.8 - 0x20.11 */
	/* access: RO */
	u_int8_t VL10_lane_map;
	/* Description - (see above) */
	/* 0x20.12 - 0x20.15 */
	/* access: RO */
	u_int8_t VL11_lane_map;
	/* Description - (see above) */
	/* 0x20.16 - 0x20.19 */
	/* access: RO */
	u_int8_t VL12_lane_map;
	/* Description - (see above) */
	/* 0x20.20 - 0x20.23 */
	/* access: RO */
	u_int8_t VL13_lane_map;
	/* Description - (see above) */
	/* 0x20.24 - 0x20.27 */
	/* access: RO */
	u_int8_t VL14_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.28 - 0x20.31 */
	/* access: RO */
	u_int8_t VL15_lane_map;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - (see above) */
	/* 0x24.0 - 0x24.3 */
	/* access: RO */
	u_int8_t VL16_lane_map;
	/* Description - (see above) */
	/* 0x24.4 - 0x24.7 */
	/* access: RO */
	u_int8_t VL17_lane_map;
	/* Description - (see above) */
	/* 0x24.8 - 0x24.11 */
	/* access: RO */
	u_int8_t VL18_lane_map;
	/* Description - (see above) */
	/* 0x24.12 - 0x24.15 */
	/* access: RO */
	u_int8_t VL19_lane_map;
	/* Description - (see above) */
	/* 0x24.16 - 0x24.19 */
	/* access: RO */
	u_int8_t VL20_lane_map;
	/* Description - (see above) */
	/* 0x24.20 - 0x24.23 */
	/* access: RO */
	u_int8_t VL21_lane_map;
	/* Description - (see above) */
	/* 0x24.24 - 0x24.27 */
	/* access: RO */
	u_int8_t VL22_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.28 - 0x24.31 */
	/* access: RO */
	u_int8_t VL23_lane_map;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - (see above) */
	/* 0x28.0 - 0x28.3 */
	/* access: RO */
	u_int8_t VL24_lane_map;
	/* Description - (see above) */
	/* 0x28.4 - 0x28.7 */
	/* access: RO */
	u_int8_t VL25_lane_map;
	/* Description - (see above) */
	/* 0x28.8 - 0x28.11 */
	/* access: RO */
	u_int8_t VL26_lane_map;
	/* Description - (see above) */
	/* 0x28.12 - 0x28.15 */
	/* access: RO */
	u_int8_t VL27_lane_map;
	/* Description - (see above) */
	/* 0x28.16 - 0x28.19 */
	/* access: RO */
	u_int8_t VL28_lane_map;
	/* Description - (see above) */
	/* 0x28.20 - 0x28.23 */
	/* access: RO */
	u_int8_t VL29_lane_map;
	/* Description - (see above) */
	/* 0x28.24 - 0x28.27 */
	/* access: RO */
	u_int8_t VL30_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.28 - 0x28.31 */
	/* access: RO */
	u_int8_t VL31_lane_map;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Local port index for the label port chosen (valid when pnat=1). The full
14-bit value is assembled from three fields:
bits [7:0] from local_port_query field,
bits [9:8] from lp_query_msb field,
bits [13:10] from lp_query_msb_ext field. */
	/* 0x3c.0 - 0x3c.3 */
	/* access: RO */
	u_int8_t lp_query_msb_ext;
	/* Description - PPORT number. The full 14-bit pport value is assembled from three fields:
bits [7:0] from pport field,
bits [9:8] from pport_msb field,
bits [13:10] from pport_msb_ext field. */
	/* 0x3c.4 - 0x3c.7 */
	/* access: RO */
	u_int8_t pport_msb_ext;
	/* Description - For SP5. Represent the fiber connector index on front panel */
	/* 0x3c.16 - 0x3c.23 */
	/* access: RO */
	u_int8_t fiber_connector_index;
	/* Description - Indicates start offset of rx_lane, tx_lane inside the modules lanes in
8x granularity. relevant for modules with more than 8 lanes. such as OE.0: lanes_0-71: lanes_8_152: lanes_16_233: lanes_24_31 */
	/* 0x3c.28 - 0x3c.31 */
	/* access: RO */
	u_int8_t sub_module;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - (see above) */
	/* 0x40.0 - 0x40.3 */
	/* access: RO */
	u_int8_t oe_lane7_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.4 - 0x40.7 */
	/* access: RO */
	u_int8_t oe_lane6_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.8 - 0x40.11 */
	/* access: RO */
	u_int8_t oe_lane5_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.12 - 0x40.15 */
	/* access: RO */
	u_int8_t oe_lane4_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.16 - 0x40.19 */
	/* access: RO */
	u_int8_t oe_lane3_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.20 - 0x40.23 */
	/* access: RO */
	u_int8_t oe_lane2_to_els_logical_laser;
	/* Description - (see above) */
	/* 0x40.24 - 0x40.27 */
	/* access: RO */
	u_int8_t oe_lane1_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.28 - 0x40.31 */
	/* access: RO */
	u_int8_t oe_lane0_to_els_logical_laser;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - ELS module index */
	/* 0x44.0 - 0x44.7 */
	/* access: RO */
	u_int8_t els_module_index;
	/* Description - Indicates whether the port is associated with a virtual module (vmod).0: no_vmod_indication1: vmod_indication */
	/* 0x44.9 - 0x44.9 */
	/* access: RO */
	u_int8_t cpo_module_indication;
	/* Description - ELS label index */
	/* 0x44.10 - 0x44.15 */
	/* access: RO */
	u_int8_t els_index;
	/* Description - Lane mask representing the active lanes associated with the local port
as determined by the agreed link protocol during link up.0: N/A (not supported or link is down)Bit 0: Lane 0Bit 1: Lane 1Bit 2: Lane 2Bit 3: Lane 3Bit 4: Lane 4Bit 5: Lane 5Bit 6: Lane 6Bit 7: Lane 7Note: supported only if indication by PCAM.feature_group=1.bit 6. */
	/* 0x44.16 - 0x44.23 */
	/* access: RO */
	u_int8_t active_module_lane_mask;
	/* Description - Optical engine MCU index. If system has no MCU on the OE, this field
represent the OE index. */
	/* 0x44.24 - 0x44.30 */
	/* access: RO */
	u_int8_t oe_mcu_index;
	/* Description - CPO indication:0 - not CPO1 - CPO */
	/* 0x44.31 - 0x44.31 */
	/* access: RO */
	u_int8_t cpo_indication;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_switch_pmlp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: unmap_local_port1: x1 - lane 0 is used2: x2 - lanes 0,1 are used4: x4 - lanes 0,1,2 and 3 are used8: x8 - lanes 0-7 are usedOther - reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t width;
	/* Description - Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the
aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Module lane mapping:0 - Local to Module mapping include module lanes mapping1 - Local to Module mapping only, without lane mappingWhen this operational is set (1'), the following fields are ignored in
SET command and should return the value 0 in GET commands:PMLP.rxtxPMLP.lane<i>_module_mapping.tx_lanePMLP.lane<i>_module_mapping.rx_lane */
	/* 0x0.28 - 0x0.28 */
	/* access: OP */
	u_int8_t m_lane_m;
	/* Description - Use different configuration for RX and TX.If this bit is cleared, the TX value is used for both RX and TX. When
set, the RX configuration is taken from the separate field. This is to
enable backward compatible implementation. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t rxtx;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module SerDes for lane iUp to 8 SerDes in a module can be mapped to a local port.
. */
	/* 0x4.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_switch_lane_2_module_mapping_ext lane_module_mapping[8];
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_switch_ppcl_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: nvlink_phy_gen6 */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t generation;
	/* Description - 0: Network Port1: Near-End Port (For Gearbox - Host side)2: internal IC Port3: Far-End Port (For Gearbox - Line side)4: Main Die to Die (USR / SCC)5: Tile Die to Die (USR / SCC) */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port isinterpreted:0: Local_port_number1: IB_port_number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: cause_list1: cause_configuration */
	/* 0x4.0 - 0x4.5 */
	/* access: INDEX */
	u_int8_t page_select;
	/* Description - Selects which cause list buffer is returned when reading the
cause_list_data page.0: Current cause list - reflects all causes raised since the last clear
operation.1: Link-down snapshot - a capture of the cause list saved at the moment
of the last link-down event. */
	/* 0x4.30 - 0x4.30 */
	/* access: INDEX */
	u_int8_t link_down_snapshot_sel;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Page Data:PPCL - Cause List For NVLink PHY Gen 6 LayoutPPCL - Cause Configurations Layout */
	/* 0x8.0 - 0x18.31 */
	/* access: RW */
	union reg_access_switch_ppcl_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 1040 */
union reg_access_switch_reg_access_switch_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_MMAM_ext MMAM_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_switch_MRFV_ext MRFV_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_PPCR_ext PPCR_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_switch_icam_reg_ext icam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x40c.31 */
	/* access: RW */
	struct reg_access_switch_icsr_ext icsr_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_switch_mcce_reg_ext mcce_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_ext mddq_ext;
	/* Description -  */
	/* 0x0.0 - 0x10c.31 */
	/* access: RW */
	struct reg_access_switch_mddt_reg_ext mddt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mdsr_reg_ext mdsr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_switch_mfcdr_reg_ext mfcdr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_switch_mfkv_reg_ext mfkv_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_switch_mfmc_reg_ext mfmc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	/* access: RW */
	struct reg_access_switch_mgpir_ext mgpir_ext;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	/* access: RW */
	struct reg_access_switch_mkdc_reg_ext mkdc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8c.31 */
	/* access: RW */
	struct reg_access_switch_mmta_reg_ext mmta_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x30.31 */
	/* access: RW */
	struct reg_access_switch_mord_v2_ext mord_v2_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mpein_reg_ext mpein_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_mpir_ext mpir_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_switch_mrsr_ext mrsr_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_switch_msgi_ext msgi_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mspmer_ext mspmer_ext;
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	/* access: RW */
	struct reg_access_switch_mtcq_reg_ext mtcq_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_switch_mtecr_ext mtecr_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mtsh_reg_ext mtsh_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	/* access: RW */
	struct reg_access_switch_pddr_reg_ext pddr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_switch_pguid_reg_ext pguid_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_plib_reg_ext plib_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_switch_pllp_reg_ext pllp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_pmaos_reg_ext pmaos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_switch_pmdr_reg_ext pmdr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_switch_pmlp_reg_ext pmlp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_switch_ppcl_reg_ext ppcl_reg_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* ef_afe_snap_v1_ext */
void reg_access_switch_ef_afe_snap_v1_ext_pack(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_afe_snap_v1_ext_unpack(struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_afe_snap_v1_ext_print(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_afe_snap_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_AFE_SNAP_V1_EXT_SIZE    (0x8)
void reg_access_switch_ef_afe_snap_v1_ext_dump(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, FILE *fd);
/* ef_lt_x_feq_ber_entry_v1_ext */
void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_pack(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_unpack(struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_print(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_LT_X_FEQ_BER_ENTRY_V1_EXT_SIZE    (0xc)
void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_dump(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, FILE *fd);
/* hst_link_eth_enabled_ext */
void reg_access_switch_hst_link_eth_enabled_ext_pack(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_hst_link_eth_enabled_ext_unpack(struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_hst_link_eth_enabled_ext_print(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_hst_link_eth_enabled_ext_size(void);
#define REG_ACCESS_SWITCH_HST_LINK_ETH_ENABLED_EXT_SIZE    (0x4)
void reg_access_switch_hst_link_eth_enabled_ext_dump(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, FILE *fd);
/* hst_link_ib_enabled_ext */
void reg_access_switch_hst_link_ib_enabled_ext_pack(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_hst_link_ib_enabled_ext_unpack(struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_hst_link_ib_enabled_ext_print(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_hst_link_ib_enabled_ext_size(void);
#define REG_ACCESS_SWITCH_HST_LINK_IB_ENABLED_EXT_SIZE    (0x4)
void reg_access_switch_hst_link_ib_enabled_ext_dump(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, FILE *fd);
/* hst_link_nvlink_enabled_ext */
void reg_access_switch_hst_link_nvlink_enabled_ext_pack(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_hst_link_nvlink_enabled_ext_unpack(struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_hst_link_nvlink_enabled_ext_print(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_hst_link_nvlink_enabled_ext_size(void);
#define REG_ACCESS_SWITCH_HST_LINK_NVLINK_ENABLED_EXT_SIZE    (0x4)
void reg_access_switch_hst_link_nvlink_enabled_ext_dump(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, FILE *fd);
/* pd_link_eth_enabled_ext */
void reg_access_switch_pd_link_eth_enabled_ext_pack(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pd_link_eth_enabled_ext_unpack(struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pd_link_eth_enabled_ext_print(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pd_link_eth_enabled_ext_size(void);
#define REG_ACCESS_SWITCH_PD_LINK_ETH_ENABLED_EXT_SIZE    (0x4)
void reg_access_switch_pd_link_eth_enabled_ext_dump(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, FILE *fd);
/* pd_link_ib_enabled_ext */
void reg_access_switch_pd_link_ib_enabled_ext_pack(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pd_link_ib_enabled_ext_unpack(struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pd_link_ib_enabled_ext_print(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pd_link_ib_enabled_ext_size(void);
#define REG_ACCESS_SWITCH_PD_LINK_IB_ENABLED_EXT_SIZE    (0x4)
void reg_access_switch_pd_link_ib_enabled_ext_dump(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, FILE *fd);
/* pddr_c2p_link_enabled_eth_ext */
void reg_access_switch_pddr_c2p_link_enabled_eth_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_eth_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_eth_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_c2p_link_enabled_eth_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_ETH_EXT_SIZE    (0x4)
void reg_access_switch_pddr_c2p_link_enabled_eth_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, FILE *fd);
/* pddr_c2p_link_enabled_ib_ext */
void reg_access_switch_pddr_c2p_link_enabled_ib_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_ib_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_ib_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_c2p_link_enabled_ib_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_IB_EXT_SIZE    (0x4)
void reg_access_switch_pddr_c2p_link_enabled_ib_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, FILE *fd);
/* pddr_c2p_link_enabled_nvlink_ext */
void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_NVLINK_EXT_SIZE    (0x4)
void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, FILE *fd);
/* pddr_cable_cap_eth_ext */
void reg_access_switch_pddr_cable_cap_eth_ext_pack(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_eth_ext_unpack(struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_eth_ext_print(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_cable_cap_eth_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_CABLE_CAP_ETH_EXT_SIZE    (0x4)
void reg_access_switch_pddr_cable_cap_eth_ext_dump(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd);
/* pddr_cable_cap_ib_ext */
void reg_access_switch_pddr_cable_cap_ib_ext_pack(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_ib_ext_unpack(struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_ib_ext_print(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_cable_cap_ib_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_CABLE_CAP_IB_EXT_SIZE    (0x4)
void reg_access_switch_pddr_cable_cap_ib_ext_dump(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd);
/* pddr_cable_cap_nvlink_ext */
void reg_access_switch_pddr_cable_cap_nvlink_ext_pack(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_nvlink_ext_unpack(struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_cable_cap_nvlink_ext_print(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_cable_cap_nvlink_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_CABLE_CAP_NVLINK_EXT_SIZE    (0x4)
void reg_access_switch_pddr_cable_cap_nvlink_ext_dump(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, FILE *fd);
/* pddr_link_active_eth_ext */
void reg_access_switch_pddr_link_active_eth_ext_pack(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_eth_ext_unpack(struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_eth_ext_print(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_active_eth_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_ETH_EXT_SIZE    (0x4)
void reg_access_switch_pddr_link_active_eth_ext_dump(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, FILE *fd);
/* pddr_link_active_ib_ext */
void reg_access_switch_pddr_link_active_ib_ext_pack(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_ib_ext_unpack(struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_ib_ext_print(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_active_ib_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_IB_EXT_SIZE    (0x4)
void reg_access_switch_pddr_link_active_ib_ext_dump(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, FILE *fd);
/* pddr_link_active_nvlink_ext */
void reg_access_switch_pddr_link_active_nvlink_ext_pack(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_nvlink_ext_unpack(struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_active_nvlink_ext_print(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_active_nvlink_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_NVLINK_EXT_SIZE    (0x4)
void reg_access_switch_pddr_link_active_nvlink_ext_dump(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, FILE *fd);
/* pddr_monitor_opcode_ext */
void reg_access_switch_pddr_monitor_opcode_ext_pack(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_monitor_opcode_ext_unpack(struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_monitor_opcode_ext_print(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_monitor_opcode_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_MONITOR_OPCODE_EXT_SIZE    (0x4)
void reg_access_switch_pddr_monitor_opcode_ext_dump(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, FILE *fd);
/* pddr_phy_manager_link_enabled_eth_ext */
void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_ETH_EXT_SIZE    (0x4)
void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, FILE *fd);
/* pddr_phy_manager_link_enabled_ib_ext */
void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_IB_EXT_SIZE    (0x4)
void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, FILE *fd);
/* pddr_phy_manager_link_enabled_nvlink_ext */
void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_NVLINK_EXT_SIZE    (0x4)
void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, FILE *fd);
/* ef_lt_x_feq_ber_db_v1_ext */
void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_pack(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_unpack(struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_print(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_LT_X_FEQ_BER_DB_V1_EXT_SIZE    (0x44)
void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_dump(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, FILE *fd);
/* ef_lt_x_port_info_v1_ext */
void reg_access_switch_ef_lt_x_port_info_v1_ext_pack(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_port_info_v1_ext_unpack(struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_lt_x_port_info_v1_ext_print(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_lt_x_port_info_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_LT_X_PORT_INFO_V1_EXT_SIZE    (0x4)
void reg_access_switch_ef_lt_x_port_info_v1_ext_dump(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, FILE *fd);
/* ef_pddr_apsu_lane_data_v1_ext */
void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_pack(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_unpack(struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_print(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_PDDR_APSU_LANE_DATA_V1_EXT_SIZE    (0xc)
void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_dump(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, FILE *fd);
/* ltx_logger_ext */
void reg_access_switch_ltx_logger_ext_pack(const struct reg_access_switch_ltx_logger_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ltx_logger_ext_unpack(struct reg_access_switch_ltx_logger_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ltx_logger_ext_print(const struct reg_access_switch_ltx_logger_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ltx_logger_ext_size(void);
#define REG_ACCESS_SWITCH_LTX_LOGGER_EXT_SIZE    (0x8)
void reg_access_switch_ltx_logger_ext_dump(const struct reg_access_switch_ltx_logger_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_cable_proto_cap_auto_ext */
void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_CABLE_PROTO_CAP_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_core_to_phy_link_enabled_auto_ext */
void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_CORE_TO_PHY_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_link_active_auto_ext */
void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_link_active_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_LINK_ACTIVE_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_pd_link_enabled_auto_ext */
void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PD_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_phy_hst_link_enabled_auto_ext */
void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PHY_HST_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_phy_manager_link_enabled_auto_ext */
void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PHY_MANAGER_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_troubleshooting_page_status_opcode_auto_ext */
void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_pack(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_unpack(union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_print(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_TROUBLESHOOTING_PAGE_STATUS_OPCODE_AUTO_EXT_SIZE    (0x4)
void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_dump(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_switch_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_uint64_size(void);
#define REG_ACCESS_SWITCH_UINT64_SIZE    (0x8)
void reg_access_switch_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* MRFV_CVB_ext */
void reg_access_switch_MRFV_CVB_ext_pack(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_CVB_ext_unpack(struct reg_access_switch_MRFV_CVB_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_CVB_ext_print(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_CVB_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_CVB_EXT_SIZE    (0x8)
void reg_access_switch_MRFV_CVB_ext_dump(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, FILE *fd);
/* MRFV_PVS_MAIN_ext */
void reg_access_switch_MRFV_PVS_MAIN_ext_pack(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_PVS_MAIN_ext_unpack(struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_PVS_MAIN_ext_print(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_PVS_MAIN_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_PVS_MAIN_EXT_SIZE    (0x4)
void reg_access_switch_MRFV_PVS_MAIN_ext_dump(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd);
/* MRFV_PVS_TILE_ext */
void reg_access_switch_MRFV_PVS_TILE_ext_pack(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_PVS_TILE_ext_unpack(struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_PVS_TILE_ext_print(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_PVS_TILE_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_PVS_TILE_EXT_SIZE    (0x4)
void reg_access_switch_MRFV_PVS_TILE_ext_dump(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd);
/* MRFV_RAW_AND_VALUE_ext */
void reg_access_switch_MRFV_RAW_AND_VALUE_ext_pack(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_RAW_AND_VALUE_ext_unpack(struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_RAW_AND_VALUE_ext_print(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_RAW_AND_VALUE_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_RAW_AND_VALUE_EXT_SIZE    (0xc)
void reg_access_switch_MRFV_RAW_AND_VALUE_ext_dump(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, FILE *fd);
/* MRFV_ULT_ext */
void reg_access_switch_MRFV_ULT_ext_pack(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_ULT_ext_unpack(struct reg_access_switch_MRFV_ULT_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_ULT_ext_print(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_ULT_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_ULT_EXT_SIZE    (0xc)
void reg_access_switch_MRFV_ULT_ext_dump(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, FILE *fd);
/* command_payload_ext */
void reg_access_switch_command_payload_ext_pack(const struct reg_access_switch_command_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_unpack(struct reg_access_switch_command_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_print(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_command_payload_ext_size(void);
#define REG_ACCESS_SWITCH_COMMAND_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_command_payload_ext_dump(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd);
/* crspace_access_payload_ext */
void reg_access_switch_crspace_access_payload_ext_pack(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_unpack(struct reg_access_switch_crspace_access_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_print(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_crspace_access_payload_ext_size(void);
#define REG_ACCESS_SWITCH_CRSPACE_ACCESS_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_crspace_access_payload_ext_dump(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd);
/* mddq_device_info_ext */
void reg_access_switch_mddq_device_info_ext_pack(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_device_info_ext_unpack(struct reg_access_switch_mddq_device_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_device_info_ext_print(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_device_info_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_DEVICE_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_device_info_ext_dump(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd);
/* mddq_slot_info_ext */
void reg_access_switch_mddq_slot_info_ext_pack(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_info_ext_unpack(struct reg_access_switch_mddq_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_info_ext_print(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_slot_info_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_SLOT_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_slot_info_ext_dump(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd);
/* mddq_slot_name_ext */
void reg_access_switch_mddq_slot_name_ext_pack(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_name_ext_unpack(struct reg_access_switch_mddq_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_name_ext_print(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_slot_name_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_SLOT_NAME_EXT_SIZE    (0x20)
void reg_access_switch_mddq_slot_name_ext_dump(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd);
/* module_latched_flag_info_ext */
void reg_access_switch_module_latched_flag_info_ext_pack(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_module_latched_flag_info_ext_unpack(struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_module_latched_flag_info_ext_print(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_module_latched_flag_info_ext_size(void);
#define REG_ACCESS_SWITCH_MODULE_LATCHED_FLAG_INFO_EXT_SIZE    (0x50)
void reg_access_switch_module_latched_flag_info_ext_dump(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, FILE *fd);
/* pddr_apsu_info_page_ext */
void reg_access_switch_pddr_apsu_info_page_ext_pack(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_apsu_info_page_ext_unpack(struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_apsu_info_page_ext_print(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_apsu_info_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_APSU_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_apsu_info_page_ext_dump(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, FILE *fd);
/* pddr_cpo_module_page_ext */
void reg_access_switch_pddr_cpo_module_page_ext_pack(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_cpo_module_page_ext_unpack(struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_cpo_module_page_ext_print(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_cpo_module_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_CPO_MODULE_PAGE_EXT_SIZE    (0xa8)
void reg_access_switch_pddr_cpo_module_page_ext_dump(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, FILE *fd);
/* pddr_fec_measure_ltx_nvl5_ext */
void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_pack(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_unpack(struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_print(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_FEC_MEASURE_LTX_NVL5_EXT_SIZE    (0x8c)
void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_dump(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, FILE *fd);
/* pddr_link_down_info_page_ext */
void reg_access_switch_pddr_link_down_info_page_ext_pack(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_down_info_page_ext_unpack(struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_down_info_page_ext_print(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_down_info_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_DOWN_INFO_PAGE_EXT_SIZE    (0xf4)
void reg_access_switch_pddr_link_down_info_page_ext_dump(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, FILE *fd);
/* pddr_link_health_page_ext */
void reg_access_switch_pddr_link_health_page_ext_pack(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_health_page_ext_unpack(struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_health_page_ext_print(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_health_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_HEALTH_PAGE_EXT_SIZE    (0xb0)
void reg_access_switch_pddr_link_health_page_ext_dump(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, FILE *fd);
/* pddr_link_partner_info_ext */
void reg_access_switch_pddr_link_partner_info_ext_pack(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_partner_info_ext_unpack(struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_partner_info_ext_print(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_partner_info_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_PARTNER_INFO_EXT_SIZE    (0x30)
void reg_access_switch_pddr_link_partner_info_ext_dump(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, FILE *fd);
/* pddr_link_up_info_page_ext */
void reg_access_switch_pddr_link_up_info_page_ext_pack(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_up_info_page_ext_unpack(struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_link_up_info_page_ext_print(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_link_up_info_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_LINK_UP_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_link_up_info_page_ext_dump(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, FILE *fd);
/* pddr_module_info_ext */
void reg_access_switch_pddr_module_info_ext_pack(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_module_info_ext_unpack(struct reg_access_switch_pddr_module_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_module_info_ext_print(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_module_info_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_MODULE_INFO_EXT_SIZE    (0xd0)
void reg_access_switch_pddr_module_info_ext_dump(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_ext */
void reg_access_switch_pddr_operation_info_page_ext_pack(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_ext_unpack(struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_operation_info_page_ext_print(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_operation_info_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_operation_info_page_ext_dump(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, FILE *fd);
/* pddr_phy_info_page_ext */
void reg_access_switch_pddr_phy_info_page_ext_pack(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_info_page_ext_unpack(struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_phy_info_page_ext_print(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_phy_info_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_PHY_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_phy_info_page_ext_dump(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, FILE *fd);
/* pddr_troubleshooting_page_ext */
void reg_access_switch_pddr_troubleshooting_page_ext_pack(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_troubleshooting_page_ext_unpack(struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_troubleshooting_page_ext_print(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_troubleshooting_page_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_TROUBLESHOOTING_PAGE_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_troubleshooting_page_ext_dump(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd);
/* ppcl_cause_configurations_ext */
void reg_access_switch_ppcl_cause_configurations_ext_pack(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ppcl_cause_configurations_ext_unpack(struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ppcl_cause_configurations_ext_print(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ppcl_cause_configurations_ext_size(void);
#define REG_ACCESS_SWITCH_PPCL_CAUSE_CONFIGURATIONS_EXT_SIZE    (0x4)
void reg_access_switch_ppcl_cause_configurations_ext_dump(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, FILE *fd);
/* ppcl_cause_list_for_nvlink_phy_gen6_ext */
void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_pack(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_unpack(struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_print(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_size(void);
#define REG_ACCESS_SWITCH_PPCL_CAUSE_LIST_FOR_NVLINK_PHY_GEN6_EXT_SIZE    (0x14)
void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_dump(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, FILE *fd);
/* prm_register_payload_ext */
void reg_access_switch_prm_register_payload_ext_pack(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_unpack(struct reg_access_switch_prm_register_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_print(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_prm_register_payload_ext_size(void);
#define REG_ACCESS_SWITCH_PRM_REGISTER_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_prm_register_payload_ext_dump(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd);
/* MRFV_data_auto_ext */
void reg_access_switch_MRFV_data_auto_ext_pack(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_data_auto_ext_unpack(union reg_access_switch_MRFV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_data_auto_ext_print(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_DATA_AUTO_EXT_SIZE    (0xc)
void reg_access_switch_MRFV_data_auto_ext_dump(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, FILE *fd);
/* ef_mcce_entry_v1_ext */
void reg_access_switch_ef_mcce_entry_v1_ext_pack(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ef_mcce_entry_v1_ext_unpack(struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ef_mcce_entry_v1_ext_print(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ef_mcce_entry_v1_ext_size(void);
#define REG_ACCESS_SWITCH_EF_MCCE_ENTRY_V1_EXT_SIZE    (0x4)
void reg_access_switch_ef_mcce_entry_v1_ext_dump(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, FILE *fd);
/* lane_2_module_mapping_ext */
void reg_access_switch_lane_2_module_mapping_ext_pack(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_lane_2_module_mapping_ext_unpack(struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_lane_2_module_mapping_ext_print(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_lane_2_module_mapping_ext_size(void);
#define REG_ACCESS_SWITCH_LANE_2_MODULE_MAPPING_EXT_SIZE    (0x4)
void reg_access_switch_lane_2_module_mapping_ext_dump(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd);
/* mddq_data_auto_ext */
void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_DATA_AUTO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_data_auto_ext_dump(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd);
/* mddt_reg_payload_auto_ext */
void reg_access_switch_mddt_reg_payload_auto_ext_pack(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_unpack(union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_print(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_payload_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_PAYLOAD_AUTO_EXT_SIZE    (0x104)
void reg_access_switch_mddt_reg_payload_auto_ext_dump(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd);
/* mgpir_hw_info_ext */
void reg_access_switch_mgpir_hw_info_ext_pack(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_info_ext_unpack(struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_info_ext_print(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mgpir_hw_info_ext_size(void);
#define REG_ACCESS_SWITCH_MGPIR_HW_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mgpir_hw_info_ext_dump(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd);
/* mgpir_hw_metadata_ext */
void reg_access_switch_mgpir_hw_metadata_ext_pack(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_metadata_ext_unpack(struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_metadata_ext_print(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mgpir_hw_metadata_ext_size(void);
#define REG_ACCESS_SWITCH_MGPIR_HW_METADATA_EXT_SIZE    (0x20)
void reg_access_switch_mgpir_hw_metadata_ext_dump(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, FILE *fd);
/* mmta_tec_power_ext */
void reg_access_switch_mmta_tec_power_ext_pack(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_tec_power_ext_unpack(struct reg_access_switch_mmta_tec_power_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_tec_power_ext_print(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_tec_power_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_TEC_POWER_EXT_SIZE    (0x20)
void reg_access_switch_mmta_tec_power_ext_dump(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd);
/* mmta_temprature_ext */
void reg_access_switch_mmta_temprature_ext_pack(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_temprature_ext_unpack(struct reg_access_switch_mmta_temprature_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_temprature_ext_print(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_temprature_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_TEMPRATURE_EXT_SIZE    (0x18)
void reg_access_switch_mmta_temprature_ext_dump(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd);
/* pddr_reg_page_data_auto_ext */
void reg_access_switch_pddr_reg_page_data_auto_ext_pack(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_reg_page_data_auto_ext_unpack(union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_reg_page_data_auto_ext_print(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_REG_PAGE_DATA_AUTO_EXT_SIZE    (0xf8)
void reg_access_switch_pddr_reg_page_data_auto_ext_dump(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* ppcl_reg_page_data_auto_ext */
void reg_access_switch_ppcl_reg_page_data_auto_ext_pack(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ppcl_reg_page_data_auto_ext_unpack(union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ppcl_reg_page_data_auto_ext_print(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ppcl_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_PPCL_REG_PAGE_DATA_AUTO_EXT_SIZE    (0x14)
void reg_access_switch_ppcl_reg_page_data_auto_ext_dump(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* MMAM_ext */
void reg_access_switch_MMAM_ext_pack(const struct reg_access_switch_MMAM_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MMAM_ext_unpack(struct reg_access_switch_MMAM_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MMAM_ext_print(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MMAM_ext_size(void);
#define REG_ACCESS_SWITCH_MMAM_EXT_SIZE    (0x10)
void reg_access_switch_MMAM_ext_dump(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd);
/* MRFV_ext */
void reg_access_switch_MRFV_ext_pack(const struct reg_access_switch_MRFV_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MRFV_ext_unpack(struct reg_access_switch_MRFV_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MRFV_ext_print(const struct reg_access_switch_MRFV_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MRFV_ext_size(void);
#define REG_ACCESS_SWITCH_MRFV_EXT_SIZE    (0x40)
void reg_access_switch_MRFV_ext_dump(const struct reg_access_switch_MRFV_ext *ptr_struct, FILE *fd);
/* PPCR_ext */
void reg_access_switch_PPCR_ext_pack(const struct reg_access_switch_PPCR_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_PPCR_ext_unpack(struct reg_access_switch_PPCR_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_PPCR_ext_print(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_PPCR_ext_size(void);
#define REG_ACCESS_SWITCH_PPCR_EXT_SIZE    (0x10)
void reg_access_switch_PPCR_ext_dump(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd);
/* icam_reg_ext */
void reg_access_switch_icam_reg_ext_pack(const struct reg_access_switch_icam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_unpack(struct reg_access_switch_icam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_print(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icam_reg_ext_size(void);
#define REG_ACCESS_SWITCH_ICAM_REG_EXT_SIZE    (0x18)
void reg_access_switch_icam_reg_ext_dump(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd);
/* icsr_ext */
void reg_access_switch_icsr_ext_pack(const struct reg_access_switch_icsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_unpack(struct reg_access_switch_icsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_print(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icsr_ext_size(void);
#define REG_ACCESS_SWITCH_ICSR_EXT_SIZE    (0x410)
void reg_access_switch_icsr_ext_dump(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd);
/* mcce_reg_ext */
void reg_access_switch_mcce_reg_ext_pack(const struct reg_access_switch_mcce_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mcce_reg_ext_unpack(struct reg_access_switch_mcce_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mcce_reg_ext_print(const struct reg_access_switch_mcce_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mcce_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MCCE_REG_EXT_SIZE    (0x40)
void reg_access_switch_mcce_reg_ext_dump(const struct reg_access_switch_mcce_reg_ext *ptr_struct, FILE *fd);
/* mddq_ext */
void reg_access_switch_mddq_ext_pack(const struct reg_access_switch_mddq_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_unpack(struct reg_access_switch_mddq_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_print(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_EXT_SIZE    (0x30)
void reg_access_switch_mddq_ext_dump(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd);
/* mddt_reg_ext */
void reg_access_switch_mddt_reg_ext_pack(const struct reg_access_switch_mddt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_unpack(struct reg_access_switch_mddt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_print(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_EXT_SIZE    (0x110)
void reg_access_switch_mddt_reg_ext_dump(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd);
/* mdsr_reg_ext */
void reg_access_switch_mdsr_reg_ext_pack(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_unpack(struct reg_access_switch_mdsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_print(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mdsr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDSR_REG_EXT_SIZE    (0x30)
void reg_access_switch_mdsr_reg_ext_dump(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd);
/* mfcdr_reg_ext */
void reg_access_switch_mfcdr_reg_ext_pack(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mfcdr_reg_ext_unpack(struct reg_access_switch_mfcdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mfcdr_reg_ext_print(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mfcdr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MFCDR_REG_EXT_SIZE    (0x8)
void reg_access_switch_mfcdr_reg_ext_dump(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, FILE *fd);
/* mfkv_reg_ext */
void reg_access_switch_mfkv_reg_ext_pack(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mfkv_reg_ext_unpack(struct reg_access_switch_mfkv_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mfkv_reg_ext_print(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mfkv_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MFKV_REG_EXT_SIZE    (0x18)
void reg_access_switch_mfkv_reg_ext_dump(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, FILE *fd);
/* mfmc_reg_ext */
void reg_access_switch_mfmc_reg_ext_pack(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mfmc_reg_ext_unpack(struct reg_access_switch_mfmc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mfmc_reg_ext_print(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mfmc_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MFMC_REG_EXT_SIZE    (0x1c)
void reg_access_switch_mfmc_reg_ext_dump(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd);
/* mgpir_ext */
void reg_access_switch_mgpir_ext_pack(const struct reg_access_switch_mgpir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mgpir_ext_unpack(struct reg_access_switch_mgpir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mgpir_ext_print(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mgpir_ext_size(void);
#define REG_ACCESS_SWITCH_MGPIR_EXT_SIZE    (0xa0)
void reg_access_switch_mgpir_ext_dump(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd);
/* mkdc_reg_ext */
void reg_access_switch_mkdc_reg_ext_pack(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_unpack(struct reg_access_switch_mkdc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_print(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mkdc_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MKDC_REG_EXT_SIZE    (0x2c)
void reg_access_switch_mkdc_reg_ext_dump(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd);
/* mmta_reg_ext */
void reg_access_switch_mmta_reg_ext_pack(const struct reg_access_switch_mmta_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_reg_ext_unpack(struct reg_access_switch_mmta_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_reg_ext_print(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_REG_EXT_SIZE    (0x90)
void reg_access_switch_mmta_reg_ext_dump(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd);
/* mord_v2_ext */
void reg_access_switch_mord_v2_ext_pack(const struct reg_access_switch_mord_v2_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mord_v2_ext_unpack(struct reg_access_switch_mord_v2_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mord_v2_ext_print(const struct reg_access_switch_mord_v2_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mord_v2_ext_size(void);
#define REG_ACCESS_SWITCH_MORD_V2_EXT_SIZE    (0x30)
void reg_access_switch_mord_v2_ext_dump(const struct reg_access_switch_mord_v2_ext *ptr_struct, FILE *fd);
/* mpein_reg_ext */
void reg_access_switch_mpein_reg_ext_pack(const struct reg_access_switch_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mpein_reg_ext_unpack(struct reg_access_switch_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mpein_reg_ext_print(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mpein_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MPEIN_REG_EXT_SIZE    (0x30)
void reg_access_switch_mpein_reg_ext_dump(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd);
/* mpir_ext */
void reg_access_switch_mpir_ext_pack(const struct reg_access_switch_mpir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mpir_ext_unpack(struct reg_access_switch_mpir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mpir_ext_print(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mpir_ext_size(void);
#define REG_ACCESS_SWITCH_MPIR_EXT_SIZE    (0x10)
void reg_access_switch_mpir_ext_dump(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd);
/* mrsr_ext */
void reg_access_switch_mrsr_ext_pack(const struct reg_access_switch_mrsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mrsr_ext_unpack(struct reg_access_switch_mrsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mrsr_ext_print(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mrsr_ext_size(void);
#define REG_ACCESS_SWITCH_MRSR_EXT_SIZE    (0x8)
void reg_access_switch_mrsr_ext_dump(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd);
/* msgi_ext */
void reg_access_switch_msgi_ext_pack(const struct reg_access_switch_msgi_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_msgi_ext_unpack(struct reg_access_switch_msgi_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_msgi_ext_print(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_msgi_ext_size(void);
#define REG_ACCESS_SWITCH_MSGI_EXT_SIZE    (0x80)
void reg_access_switch_msgi_ext_dump(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd);
/* mspmer_ext */
void reg_access_switch_mspmer_ext_pack(const struct reg_access_switch_mspmer_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mspmer_ext_unpack(struct reg_access_switch_mspmer_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mspmer_ext_print(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mspmer_ext_size(void);
#define REG_ACCESS_SWITCH_MSPMER_EXT_SIZE    (0x30)
void reg_access_switch_mspmer_ext_dump(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd);
/* mtcq_reg_ext */
void reg_access_switch_mtcq_reg_ext_pack(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_unpack(struct reg_access_switch_mtcq_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_print(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mtcq_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MTCQ_REG_EXT_SIZE    (0x70)
void reg_access_switch_mtcq_reg_ext_dump(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd);
/* mtecr_ext */
void reg_access_switch_mtecr_ext_pack(const struct reg_access_switch_mtecr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mtecr_ext_unpack(struct reg_access_switch_mtecr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mtecr_ext_print(const struct reg_access_switch_mtecr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mtecr_ext_size(void);
#define REG_ACCESS_SWITCH_MTECR_EXT_SIZE    (0x60)
void reg_access_switch_mtecr_ext_dump(const struct reg_access_switch_mtecr_ext *ptr_struct, FILE *fd);
/* mtsh_reg_ext */
void reg_access_switch_mtsh_reg_ext_pack(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mtsh_reg_ext_unpack(struct reg_access_switch_mtsh_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mtsh_reg_ext_print(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mtsh_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MTSH_REG_EXT_SIZE    (0x30)
void reg_access_switch_mtsh_reg_ext_dump(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, FILE *fd);
/* pddr_reg_ext */
void reg_access_switch_pddr_reg_ext_pack(const struct reg_access_switch_pddr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pddr_reg_ext_unpack(struct reg_access_switch_pddr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pddr_reg_ext_print(const struct reg_access_switch_pddr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pddr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PDDR_REG_EXT_SIZE    (0x100)
void reg_access_switch_pddr_reg_ext_dump(const struct reg_access_switch_pddr_reg_ext *ptr_struct, FILE *fd);
/* pguid_reg_ext */
void reg_access_switch_pguid_reg_ext_pack(const struct reg_access_switch_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pguid_reg_ext_unpack(struct reg_access_switch_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pguid_reg_ext_print(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pguid_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PGUID_REG_EXT_SIZE    (0x60)
void reg_access_switch_pguid_reg_ext_dump(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd);
/* plib_reg_ext */
void reg_access_switch_plib_reg_ext_pack(const struct reg_access_switch_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_plib_reg_ext_unpack(struct reg_access_switch_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_plib_reg_ext_print(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_plib_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PLIB_REG_EXT_SIZE    (0x10)
void reg_access_switch_plib_reg_ext_dump(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd);
/* pllp_reg_ext */
void reg_access_switch_pllp_reg_ext_pack(const struct reg_access_switch_pllp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pllp_reg_ext_unpack(struct reg_access_switch_pllp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pllp_reg_ext_print(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pllp_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PLLP_REG_EXT_SIZE    (0x18)
void reg_access_switch_pllp_reg_ext_dump(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd);
/* pmaos_reg_ext */
void reg_access_switch_pmaos_reg_ext_pack(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmaos_reg_ext_unpack(struct reg_access_switch_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmaos_reg_ext_print(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmaos_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMAOS_REG_EXT_SIZE    (0x10)
void reg_access_switch_pmaos_reg_ext_dump(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd);
/* pmdr_reg_ext */
void reg_access_switch_pmdr_reg_ext_pack(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmdr_reg_ext_unpack(struct reg_access_switch_pmdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmdr_reg_ext_print(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmdr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMDR_REG_EXT_SIZE    (0x48)
void reg_access_switch_pmdr_reg_ext_dump(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd);
/* pmlp_reg_ext */
void reg_access_switch_pmlp_reg_ext_pack(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmlp_reg_ext_unpack(struct reg_access_switch_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmlp_reg_ext_print(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmlp_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMLP_REG_EXT_SIZE    (0x40)
void reg_access_switch_pmlp_reg_ext_dump(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd);
/* ppcl_reg_ext */
void reg_access_switch_ppcl_reg_ext_pack(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_ppcl_reg_ext_unpack(struct reg_access_switch_ppcl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_ppcl_reg_ext_print(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_ppcl_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PPCL_REG_EXT_SIZE    (0x1c)
void reg_access_switch_ppcl_reg_ext_dump(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, FILE *fd);
/* reg_access_switch_Nodes */
void reg_access_switch_reg_access_switch_Nodes_pack(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_unpack(union reg_access_switch_reg_access_switch_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_print(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_reg_access_switch_Nodes_size(void);
#define REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE    (0x410)
void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_SWITCH_LAYOUTS_H
