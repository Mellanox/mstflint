/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#ifndef MLX5_IFC_USER_SPACE_STUB_H
#define MLX5_IFC_USER_SPACE_STUB_H

/* 
 *    We are using several structure definitions from Linux kernel header files in this user space code.
 * While this violates the typical assumption that kernel headers should not be used in user space code,
 * we have determined that these specific structures have not been modified for years and are unlikely
 * to be modified in the future.
 *
 *    As a result, we have decided to replicate the necessary definitions directly in our codebase rather
 * than include the kernel headers.
 *
 *    However, it should be noted that if, under very rare circumstances, these replicated definitions
 * are updated in the Linux kernel codebase, we will need to ensure that any necessary changes are
 * propagated to our codebase to avoid potential issues. 
*/

enum {
	MLX5_CMD_OP_QUERY_HCA_CAP                 = 0x100,
	MLX5_CMD_OP_QUERY_ADAPTER                 = 0x101,
	MLX5_CMD_OP_INIT_HCA                      = 0x102,
	MLX5_CMD_OP_TEARDOWN_HCA                  = 0x103,
	MLX5_CMD_OP_ENABLE_HCA                    = 0x104,
	MLX5_CMD_OP_DISABLE_HCA                   = 0x105,
	MLX5_CMD_OP_QUERY_PAGES                   = 0x107,
	MLX5_CMD_OP_MANAGE_PAGES                  = 0x108,
	MLX5_CMD_OP_SET_HCA_CAP                   = 0x109,
	MLX5_CMD_OP_QUERY_ISSI                    = 0x10a,
	MLX5_CMD_OP_SET_ISSI                      = 0x10b,
	MLX5_CMD_OP_SET_DRIVER_VERSION            = 0x10d,
	MLX5_CMD_OP_QUERY_SF_PARTITION            = 0x111,
	MLX5_CMD_OP_ALLOC_SF                      = 0x113,
	MLX5_CMD_OP_DEALLOC_SF                    = 0x114,
	MLX5_CMD_OP_CREATE_MKEY                   = 0x200,
	MLX5_CMD_OP_QUERY_MKEY                    = 0x201,
	MLX5_CMD_OP_DESTROY_MKEY                  = 0x202,
	MLX5_CMD_OP_QUERY_SPECIAL_CONTEXTS        = 0x203,
	MLX5_CMD_OP_PAGE_FAULT_RESUME             = 0x204,
	MLX5_CMD_OP_ALLOC_MEMIC                   = 0x205,
	MLX5_CMD_OP_DEALLOC_MEMIC                 = 0x206,
	MLX5_CMD_OP_MODIFY_MEMIC                  = 0x207,
	MLX5_CMD_OP_CREATE_EQ                     = 0x301,
	MLX5_CMD_OP_DESTROY_EQ                    = 0x302,
	MLX5_CMD_OP_QUERY_EQ                      = 0x303,
	MLX5_CMD_OP_GEN_EQE                       = 0x304,
	MLX5_CMD_OP_CREATE_CQ                     = 0x400,
	MLX5_CMD_OP_DESTROY_CQ                    = 0x401,
	MLX5_CMD_OP_QUERY_CQ                      = 0x402,
	MLX5_CMD_OP_MODIFY_CQ                     = 0x403,
	MLX5_CMD_OP_CREATE_QP                     = 0x500,
	MLX5_CMD_OP_DESTROY_QP                    = 0x501,
	MLX5_CMD_OP_RST2INIT_QP                   = 0x502,
	MLX5_CMD_OP_INIT2RTR_QP                   = 0x503,
	MLX5_CMD_OP_RTR2RTS_QP                    = 0x504,
	MLX5_CMD_OP_RTS2RTS_QP                    = 0x505,
	MLX5_CMD_OP_SQERR2RTS_QP                  = 0x506,
	MLX5_CMD_OP_2ERR_QP                       = 0x507,
	MLX5_CMD_OP_2RST_QP                       = 0x50a,
	MLX5_CMD_OP_QUERY_QP                      = 0x50b,
	MLX5_CMD_OP_SQD_RTS_QP                    = 0x50c,
	MLX5_CMD_OP_INIT2INIT_QP                  = 0x50e,
	MLX5_CMD_OP_CREATE_PSV                    = 0x600,
	MLX5_CMD_OP_DESTROY_PSV                   = 0x601,
	MLX5_CMD_OP_CREATE_SRQ                    = 0x700,
	MLX5_CMD_OP_DESTROY_SRQ                   = 0x701,
	MLX5_CMD_OP_QUERY_SRQ                     = 0x702,
	MLX5_CMD_OP_ARM_RQ                        = 0x703,
	MLX5_CMD_OP_CREATE_XRC_SRQ                = 0x705,
	MLX5_CMD_OP_DESTROY_XRC_SRQ               = 0x706,
	MLX5_CMD_OP_QUERY_XRC_SRQ                 = 0x707,
	MLX5_CMD_OP_ARM_XRC_SRQ                   = 0x708,
	MLX5_CMD_OP_CREATE_DCT                    = 0x710,
	MLX5_CMD_OP_DESTROY_DCT                   = 0x711,
	MLX5_CMD_OP_DRAIN_DCT                     = 0x712,
	MLX5_CMD_OP_QUERY_DCT                     = 0x713,
	MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION     = 0x714,
	MLX5_CMD_OP_CREATE_XRQ                    = 0x717,
	MLX5_CMD_OP_DESTROY_XRQ                   = 0x718,
	MLX5_CMD_OP_QUERY_XRQ                     = 0x719,
	MLX5_CMD_OP_ARM_XRQ                       = 0x71a,
	MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY     = 0x725,
	MLX5_CMD_OP_SET_XRQ_DC_PARAMS_ENTRY       = 0x726,
	MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS        = 0x727,
	MLX5_CMD_OP_RELEASE_XRQ_ERROR             = 0x729,
	MLX5_CMD_OP_MODIFY_XRQ                    = 0x72a,
	MLX5_CMD_OP_QUERY_ESW_FUNCTIONS           = 0x740,
	MLX5_CMD_OP_QUERY_VPORT_STATE             = 0x750,
	MLX5_CMD_OP_MODIFY_VPORT_STATE            = 0x751,
	MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT       = 0x752,
	MLX5_CMD_OP_MODIFY_ESW_VPORT_CONTEXT      = 0x753,
	MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT       = 0x754,
	MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT      = 0x755,
	MLX5_CMD_OP_QUERY_ROCE_ADDRESS            = 0x760,
	MLX5_CMD_OP_SET_ROCE_ADDRESS              = 0x761,
	MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT       = 0x762,
	MLX5_CMD_OP_MODIFY_HCA_VPORT_CONTEXT      = 0x763,
	MLX5_CMD_OP_QUERY_HCA_VPORT_GID           = 0x764,
	MLX5_CMD_OP_QUERY_HCA_VPORT_PKEY          = 0x765,
	MLX5_CMD_OP_QUERY_VNIC_ENV                = 0x76f,
	MLX5_CMD_OP_QUERY_VPORT_COUNTER           = 0x770,
	MLX5_CMD_OP_ALLOC_Q_COUNTER               = 0x771,
	MLX5_CMD_OP_DEALLOC_Q_COUNTER             = 0x772,
	MLX5_CMD_OP_QUERY_Q_COUNTER               = 0x773,
	MLX5_CMD_OP_SET_MONITOR_COUNTER           = 0x774,
	MLX5_CMD_OP_ARM_MONITOR_COUNTER           = 0x775,
	MLX5_CMD_OP_SET_PP_RATE_LIMIT             = 0x780,
	MLX5_CMD_OP_QUERY_RATE_LIMIT              = 0x781,
	MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT      = 0x782,
	MLX5_CMD_OP_DESTROY_SCHEDULING_ELEMENT     = 0x783,
	MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT       = 0x784,
	MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT      = 0x785,
	MLX5_CMD_OP_CREATE_QOS_PARA_VPORT         = 0x786,
	MLX5_CMD_OP_DESTROY_QOS_PARA_VPORT        = 0x787,
	MLX5_CMD_OP_ALLOC_PD                      = 0x800,
	MLX5_CMD_OP_DEALLOC_PD                    = 0x801,
	MLX5_CMD_OP_ALLOC_UAR                     = 0x802,
	MLX5_CMD_OP_DEALLOC_UAR                   = 0x803,
	MLX5_CMD_OP_CONFIG_INT_MODERATION         = 0x804,
	MLX5_CMD_OP_ACCESS_REG                    = 0x805,
	MLX5_CMD_OP_ATTACH_TO_MCG                 = 0x806,
	MLX5_CMD_OP_DETACH_FROM_MCG               = 0x807,
	MLX5_CMD_OP_GET_DROPPED_PACKET_LOG        = 0x80a,
	MLX5_CMD_OP_MAD_IFC                       = 0x50d,
	MLX5_CMD_OP_QUERY_MAD_DEMUX               = 0x80b,
	MLX5_CMD_OP_SET_MAD_DEMUX                 = 0x80c,
	MLX5_CMD_OP_NOP                           = 0x80d,
	MLX5_CMD_OP_ALLOC_XRCD                    = 0x80e,
	MLX5_CMD_OP_DEALLOC_XRCD                  = 0x80f,
	MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN        = 0x816,
	MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN      = 0x817,
	MLX5_CMD_OP_QUERY_CONG_STATUS             = 0x822,
	MLX5_CMD_OP_MODIFY_CONG_STATUS            = 0x823,
	MLX5_CMD_OP_QUERY_CONG_PARAMS             = 0x824,
	MLX5_CMD_OP_MODIFY_CONG_PARAMS            = 0x825,
	MLX5_CMD_OP_QUERY_CONG_STATISTICS         = 0x826,
	MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT           = 0x827,
	MLX5_CMD_OP_DELETE_VXLAN_UDP_DPORT        = 0x828,
	MLX5_CMD_OP_SET_L2_TABLE_ENTRY            = 0x829,
	MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY          = 0x82a,
	MLX5_CMD_OP_DELETE_L2_TABLE_ENTRY         = 0x82b,
	MLX5_CMD_OP_SET_WOL_ROL                   = 0x830,
	MLX5_CMD_OP_QUERY_WOL_ROL                 = 0x831,
	MLX5_CMD_OP_CREATE_LAG                    = 0x840,
	MLX5_CMD_OP_MODIFY_LAG                    = 0x841,
	MLX5_CMD_OP_QUERY_LAG                     = 0x842,
	MLX5_CMD_OP_DESTROY_LAG                   = 0x843,
	MLX5_CMD_OP_CREATE_VPORT_LAG              = 0x844,
	MLX5_CMD_OP_DESTROY_VPORT_LAG             = 0x845,
	MLX5_CMD_OP_CREATE_TIR                    = 0x900,
	MLX5_CMD_OP_MODIFY_TIR                    = 0x901,
	MLX5_CMD_OP_DESTROY_TIR                   = 0x902,
	MLX5_CMD_OP_QUERY_TIR                     = 0x903,
	MLX5_CMD_OP_CREATE_SQ                     = 0x904,
	MLX5_CMD_OP_MODIFY_SQ                     = 0x905,
	MLX5_CMD_OP_DESTROY_SQ                    = 0x906,
	MLX5_CMD_OP_QUERY_SQ                      = 0x907,
	MLX5_CMD_OP_CREATE_RQ                     = 0x908,
	MLX5_CMD_OP_MODIFY_RQ                     = 0x909,
	MLX5_CMD_OP_SET_DELAY_DROP_PARAMS         = 0x910,
	MLX5_CMD_OP_DESTROY_RQ                    = 0x90a,
	MLX5_CMD_OP_QUERY_RQ                      = 0x90b,
	MLX5_CMD_OP_CREATE_RMP                    = 0x90c,
	MLX5_CMD_OP_MODIFY_RMP                    = 0x90d,
	MLX5_CMD_OP_DESTROY_RMP                   = 0x90e,
	MLX5_CMD_OP_QUERY_RMP                     = 0x90f,
	MLX5_CMD_OP_CREATE_TIS                    = 0x912,
	MLX5_CMD_OP_MODIFY_TIS                    = 0x913,
	MLX5_CMD_OP_DESTROY_TIS                   = 0x914,
	MLX5_CMD_OP_QUERY_TIS                     = 0x915,
	MLX5_CMD_OP_CREATE_RQT                    = 0x916,
	MLX5_CMD_OP_MODIFY_RQT                    = 0x917,
	MLX5_CMD_OP_DESTROY_RQT                   = 0x918,
	MLX5_CMD_OP_QUERY_RQT                     = 0x919,
	MLX5_CMD_OP_SET_FLOW_TABLE_ROOT		  = 0x92f,
	MLX5_CMD_OP_CREATE_FLOW_TABLE             = 0x930,
	MLX5_CMD_OP_DESTROY_FLOW_TABLE            = 0x931,
	MLX5_CMD_OP_QUERY_FLOW_TABLE              = 0x932,
	MLX5_CMD_OP_CREATE_FLOW_GROUP             = 0x933,
	MLX5_CMD_OP_DESTROY_FLOW_GROUP            = 0x934,
	MLX5_CMD_OP_QUERY_FLOW_GROUP              = 0x935,
	MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY          = 0x936,
	MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY        = 0x937,
	MLX5_CMD_OP_DELETE_FLOW_TABLE_ENTRY       = 0x938,
	MLX5_CMD_OP_ALLOC_FLOW_COUNTER            = 0x939,
	MLX5_CMD_OP_DEALLOC_FLOW_COUNTER          = 0x93a,
	MLX5_CMD_OP_QUERY_FLOW_COUNTER            = 0x93b,
	MLX5_CMD_OP_MODIFY_FLOW_TABLE             = 0x93c,
	MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT = 0x93d,
	MLX5_CMD_OP_DEALLOC_PACKET_REFORMAT_CONTEXT = 0x93e,
	MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT = 0x93f,
	MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT   = 0x940,
	MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT = 0x941,
	MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT   = 0x942,
	MLX5_CMD_OP_FPGA_CREATE_QP                = 0x960,
	MLX5_CMD_OP_FPGA_MODIFY_QP                = 0x961,
	MLX5_CMD_OP_FPGA_QUERY_QP                 = 0x962,
	MLX5_CMD_OP_FPGA_DESTROY_QP               = 0x963,
	MLX5_CMD_OP_FPGA_QUERY_QP_COUNTERS        = 0x964,
	MLX5_CMD_OP_CREATE_GENERAL_OBJECT         = 0xa00,
	MLX5_CMD_OP_MODIFY_GENERAL_OBJECT         = 0xa01,
	MLX5_CMD_OP_QUERY_GENERAL_OBJECT          = 0xa02,
	MLX5_CMD_OP_DESTROY_GENERAL_OBJECT        = 0xa03,
	MLX5_CMD_OP_CREATE_UCTX                   = 0xa04,
	MLX5_CMD_OP_DESTROY_UCTX                  = 0xa06,
	MLX5_CMD_OP_CREATE_UMEM                   = 0xa08,
	MLX5_CMD_OP_DESTROY_UMEM                  = 0xa0a,
	MLX5_CMD_OP_SYNC_STEERING                 = 0xb00,
	MLX5_CMD_OP_QUERY_VHCA_STATE              = 0xb0d,
	MLX5_CMD_OP_MODIFY_VHCA_STATE             = 0xb0e,
	MLX5_CMD_OP_MAX
};

struct mlx5_ifc_access_register_out_bits {
	u8         status[0x8];
	u8         reserved_at_8[0x18];

	u8         syndrome[0x20];

	u8         reserved_at_40[0x40];

	u8         register_data[][0x20];
};

struct mlx5_ifc_access_register_in_bits {
	u8         opcode[0x10];
	u8         reserved_at_10[0x10];

	u8         reserved_at_20[0x10];
	u8         op_mod[0x10];

	u8         reserved_at_40[0x10];
	u8         register_id[0x10];

	u8         argument[0x20];

	u8         register_data[][0x20];
};

#endif /* MLX5_IFC_USER_SPACE_STUB_H */