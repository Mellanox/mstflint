/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */

#ifndef ICMD_LAYOUTS_H
#define ICMD_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 16 */
struct connectib_FW_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0x0.16 - 0x0.31 */
     u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description -  */
    /* 0x4.0 - 0x4.15 */
     u_int16_t SUBMINOR;
    /* Description -  */
    /* 0x4.16 - 0x4.31 */
     u_int16_t MINOR;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description -  */
    /* 0x8.8 - 0x8.15 */
     u_int8_t Hour;
    /* Description -  */
    /* 0x8.16 - 0x8.23 */
     u_int8_t Minutes;
    /* Description -  */
    /* 0x8.24 - 0x8.31 */
     u_int8_t Seconds;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
    /* Description -  */
    /* 0xc.0 - 0xc.7 */
     u_int8_t Day;
    /* Description -  */
    /* 0xc.8 - 0xc.15 */
     u_int8_t Month;
    /* Description -  */
    /* 0xc.16 - 0xc.31 */
     u_int16_t Year;
};


/* Description -   */
/* Size in bytes - 16 */
struct connectib_icmd_set_port_sniffer {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t gvmi;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.0 */
	 u_int8_t sx_rx_;
	/* Description -  */
	/* 0x4.16 - 0x4.16 */
	 u_int8_t attach_detach_;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	 u_int8_t port;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t sniffer_qpn;
};


/* Description -   */
/* Size in bytes - 36 */
struct connectib_icmd_get_fw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0x0.0 - 0x10.31 */
     struct connectib_FW_VERSION fw_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
    /* Description - Hash gen file signature */
    /* 0x10.0 - 0x10.15 */
     u_int16_t hash_signature;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
    /* Description -  */
    /* 0x14.24 - 0x24.23 */
     char psid[17];
};


/* Description -   */
/* Size in bytes - 16 */
struct connectx4_icmd_mh_sync {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - input mailbox: state of sync: IDLE, GET_READY, GO */
    /* 0x0.0 - 0x0.3 */
     u_int8_t input_state;
    /* Description - input mailbox: sync_type - 0x01 = FW_RESET */
    /* 0x0.8 - 0x0.15 */
     u_int8_t input_sync_type;
    /* Description - input mailbox: when set - ignore inactive hosts */
    /* 0x0.31 - 0x0.31 */
     u_int8_t input_ignore_inactive_hosts;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - output mailbox: state of sync: IDLE, GET_READY, GO */
    /* 0x4.0 - 0x4.3 */
     u_int8_t fsm_state;
    /* Description - output mailbox: sync_type - 0x01 = FW_RESET */
    /* 0x4.8 - 0x4.15 */
     u_int8_t fsm_sync_type;
    /* Description - output mailbox: when set - ignore inactive hosts */
    /* 0x4.31 - 0x4.31 */
     u_int8_t fsm_ignore_inactive_hosts;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description - output mailbox: bit per host - indicates hosts already issued GET_READY */
    /* 0x8.0 - 0x8.3 */
     u_int8_t fsm_host_ready;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
    /* Description - output mailbox: NIC uptime since last reset in microsecondes at the moment of first GET_READY */
    /* 0xc.0 - 0x10.31 */
     u_int32_t fsm_start_uptime;
};


/* Description -   */
/* Size in bytes - 8 */
struct connectx4_icmd_query_cap_general {
    /*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - When set, the device supports emulating link down for all the associ
    ated functions

    using
    "
    ICMD_SET_VIRTUAL_
    PARAMETERS
    -
    Set Device
    Virtual Parameters
    " */
    /* 0x0.22 - 0x0.22 */
    u_int8_t virtual_link_down;
    /* Description - When set, the device supports using a memory buffer as a mailbox for
    the ICMD, instead of the normal ICMD Mailbox. */
    /* 0x0.23 - 0x0.23 */
    u_int8_t icmd_exmb;
    /* Description - If set, CAPI is supported. */
    /* 0x0.24 - 0x0.24 */
    u_int8_t capi;
    /* Description - If set, QCAM register is supported.
    See Table  612, "
    QCAM - QoS Capa
    bilities Mask Register Layout
    ," on page  816
    . */
    /* 0x0.25 - 0x0.25 */
    u_int8_t qcam_reg;
    /* Description - If set, MCAM register is supported.
    See Table  1053, "
    MCAM - Manage
    ment Capabilities Mask Register Layout
    ," on page  1180
    . */
    /* 0x0.26 - 0x0.26 */
    u_int8_t mcam_reg;
    /* Description - If set, PCAM register is supported.
    See Table  696, "
    PCAM - Ports Capa
    bilities Mask Register Layout
    ," on page  905 */
    /* 0x0.27 - 0x0.27 */
    u_int8_t pcam_reg;
    /* Description - When set, multi-host synchronization through the device is supported.

    See Section  25.4.3, "
    ICMD_MH_SYNC - Multi-Host Synchronization
    ," on
    page  1190
    . */
    /* 0x0.28 - 0x0.28 */
    u_int8_t mh_sync;
    /* Description - If set, ICMD_ACCESS_REGISTER supports every register. (in the
    past it supported some of them). */
    /* 0x0.29 - 0x0.29 */
    u_int8_t allow_icmd_access_reg_on_all_registers;
    /* Description - When set, ICMD_QUERY_FW_INFO returns the
    psid
    field. */
    /* 0x0.30 - 0x0.30 */
    u_int8_t fw_info_psid;
    /* Description - When set, ICMD_ACCESS_REGISTER supports the following regis
    ters:
    NVDA
    NVDI
    NVIA
    NVQC */
    /* 0x0.31 - 0x0.31 */
    u_int8_t nv_access;
    /*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - If set, wake on phy activity is supported. */
    /* 0x4.0 - 0x4.0 */
    u_int8_t wol_p;
    /* Description - If set, wake on unicast packet is supported. */
    /* 0x4.1 - 0x4.1 */
    u_int8_t wol_u;
    /* Description - If set, wake on multicast packet is supported. */
    /* 0x4.2 - 0x4.2 */
    u_int8_t wol_m;
    /* Description - If set, wake on broadcast packet is supported. */
    /* 0x4.3 - 0x4.3 */
    u_int8_t wol_b;
    /* Description - If set, wake on ARP is supported. */
    /* 0x4.4 - 0x4.4 */
    u_int8_t wol_a;
    /* Description - If set, wake on magic packet is supported. */
    /* 0x4.5 - 0x4.5 */
    u_int8_t wol_g;
    /* Description - If set, wake on secured magic packet is supported. */
    /* 0x4.6 - 0x4.6 */
    u_int8_t wol_s;
    /* Description - If set, reset on magic packet is supported. */
    /* 0x4.8 - 0x4.8 */
    u_int8_t rol_g;
    /* Description - If set, reset on secured magic packet is supported. */
    /* 0x4.9 - 0x4.9 */
    u_int8_t rol_s;
    /* Description - If set, FPGA device is supported by the device. See TBD */
    /* 0x4.10 - 0x4.10 */
    u_int8_t fpga;
};




struct connectib_itrace_ctrl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - threashhold of logging to print from:
0 - LOG_DEBUG
1 - LOG_INFO
2 - LOG_WARNING
3 - LOG_ERROR */
        /* 0x0.0 - 0x0.7 */
         u_int8_t log_level;
        /* Description - added delay (usec) to prevent log event lost */
        /* 0x0.16 - 0x0.31 */
         u_int16_t log_delay;
};

struct connectib_itrace {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - bit numbers:
0=DEBUG_INIT
1=INIT
2=ICM
3=ICM_FREE_LIST
4=LOG_MOD_HOST_MNG
5=CMD_IF
6=PHY_IB
7=PHY_RX_ADAP
8=PHY_EYE_OPN
9=PHY_GENERAL
10=PHY_MANAGER
11=PWR
12=FLR
13=ICM_ACCESS
14=MAD
15=RXT_CHECKS
16=I2C
17=TRANSPORT
18=FW_LL
19=RX_ERRORS
20=CMDIF_DRIVER
21=PROFILING
22=MANAGEMENT
23=FLASH
24=STEERING
25=IFARM
26=ICMD
27=PCI
28=DC_CLEANUP
29=PHY_ETH
30=VIRT */
        /* 0x0.0 - 0x4.31 */
         u_int32_t unit_mask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x8.31 */
         struct connectib_itrace_ctrl ctrl;
};

/* Description -   */
/* Size in bytes - 4 */
struct connectx4_component_authentication_configuration {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0-NULL, 1-SHA256Digest, 3-2048 bit RSA */
	/* 0x0.0 - 0x0.7 */
	u_int8_t auth_type;
	/* Description - used for authenticating Factory Re-COnfiguration Responses */
	/* 0x0.27 - 0x0.27 */
	u_int8_t frc_en;
	/* Description - used for signing NVCONFIG at MLNX level */
	/* 0x0.28 - 0x0.28 */
	u_int8_t mlnx_nvconfig_en;
	/* Description - used for authenticating NVCONFIG at OEM level */
	/* 0x0.29 - 0x0.29 */
	u_int8_t vendor_nvconfig_en;
	/* Description - used for authenticating CS tokens at OEM level */
	/* 0x0.30 - 0x0.30 */
	u_int8_t cs_token_en;
	/* Description - Used for authenticating firmware, DBG_FW, DBG Tokens */
	/* 0x0.31 - 0x0.31 */
	u_int8_t fw_en;
};

/* Description -   */
/* Size in bytes - 544 */
struct connectx4_file_public_keys_3 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - public key exponent, FW should use an exponent of 65537 */
	/* 0x0.0 - 0x0.31 */
	u_int32_t keypair_exp;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - UUID of this key created by server when it generates a keypair */
	/* 0x4.0 - 0x10.31 */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - 4096 bit public-key */
	/* 0x14.0 - 0x210.31 */
	u_int32_t key[128];
/*---------------- DWORD[133] (Offset 0x214) ----------------*/
	/* Description - configuration bits to enable authentication for each component */
	/* 0x214.0 - 0x214.31 */
	struct connectx4_component_authentication_configuration component_authentication_configuration;
};

/* Description -   */
/* Size in bytes - 4352 */
struct connectx4_public_keys_3 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10fc.31 */
	struct connectx4_file_public_keys_3 file_public_keys_3[8];
};

/* Description -   */
/* Size in bytes - 1536 */
struct connectx4_secure_boot_signatures {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - boot signature of itocs: */
	/* 0x0.0 - 0x1fc.31 */
	u_int32_t boot_signature[128];
/*---------------- DWORD[128] (Offset 0x200) ----------------*/
	/* Description - fw critical signature of itcos: HW_BOOT_INI, PCIE_PHY_UC_COMMANDS, PCIE_LINK_CODE */
	/* 0x200.0 - 0x3fc.31 */
	u_int32_t critical_signature[128];
/*---------------- DWORD[256] (Offset 0x400) ----------------*/
	/* Description - fw non critical signatures of all other itocs  */
	/* 0x400.0 - 0x5fc.31 */
	u_int32_t non_critical_signature[128];
};

/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct connectx4_hw_pointer_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - pointer */
    /* 0x0.0 - 0x0.31 */
    u_int32_t ptr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - crc16 as calculated by HW */
    /* 0x4.0 - 0x4.15 */
    u_int16_t crc;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct connectx4_hw_pointers_arava {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct connectx4_hw_pointer_entry boot_record_ptr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	struct connectx4_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	struct connectx4_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	struct connectx4_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	struct connectx4_hw_pointer_entry authentication_start_pointer;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	struct connectx4_hw_pointer_entry authentication_end_pointer;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	struct connectx4_hw_pointer_entry digest_pointer;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	struct connectx4_hw_pointer_entry digest_recovery_key_pointer;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	struct connectx4_hw_pointer_entry fw_window_start_pointer;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	struct connectx4_hw_pointer_entry fw_window_end_pointer;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	struct connectx4_hw_pointer_entry hmac_start_pointer;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	struct connectx4_hw_pointer_entry hmac_end_pointer;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	struct connectx4_hw_pointer_entry public_key_pointer;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	struct connectx4_hw_pointer_entry reserved_ptr13_pointer;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	struct connectx4_hw_pointer_entry reserved_ptr14_pointer;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	struct connectx4_hw_pointer_entry reserved_ptr15_pointer;
};

/* Description -   */
/* Size in bytes - 8 */
struct icmd_hca_icmd_query_cap_general {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Golden TLV version.
 0: Legacy mode
1: Golden TLV includes TTL */
	/* 0x0.0 - 0x0.2 */
	u_int8_t golden_tlv_version;
	/* Description - If set, CWCAM register is supported. See TBD */
	/* 0x0.17 - 0x0.17 */
	u_int8_t cwcam_reg;
	/* Description - When set, the command supports capability groups in addition to the 
General Capability group */
	/* 0x0.20 - 0x0.20 */
	u_int8_t capability_groups;
	/* Description - When set, the device supports emulating link down for all the associ
ated functions
 
using 
"
ICMD_SET_VIRTUAL_
PARAMETERS
 - 
Set Device 
Virtual Parameters
" */
	/* 0x0.22 - 0x0.22 */
	u_int8_t virtual_link_down;
	/* Description - When set, the device supports using a memory buffer as a mailbox for 
the ICMD, instead of the normal ICMD Mailbox. */
	/* 0x0.23 - 0x0.23 */
	u_int8_t icmd_exmb;
	/* Description - If set, CAPI is supported. */
	/* 0x0.24 - 0x0.24 */
	u_int8_t capi;
	/* Description - If set, QCAM register is supported. 
 See Table  612, "
QCAM - QoS Capa
bilities Mask Register Layout
," on page  816
. */
	/* 0x0.25 - 0x0.25 */
	u_int8_t qcam_reg;
	/* Description - If set, MCAM register is supported. 
 See Table  1053, "
MCAM - Manage
ment Capabilities Mask Register Layout
," on page  1180
. */
	/* 0x0.26 - 0x0.26 */
	u_int8_t mcam_reg;
	/* Description - If set, PCAM register is supported. 
 See Table  696, "
PCAM - Ports Capa
bilities Mask Register Layout
," on page  905 */
	/* 0x0.27 - 0x0.27 */
	u_int8_t pcam_reg;
	/* Description - When set, multi-host synchronization through the device is supported. 
 
See Section  25.4.3, "
ICMD_MH_SYNC - Multi-Host Synchronization
," on 
page  1190
. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t mh_sync;
	/* Description - If set, ICMD_ACCESS_REGISTER supports every register. (in the 
past it supported some of them). */
	/* 0x0.29 - 0x0.29 */
	u_int8_t allow_icmd_access_reg_on_all_registers;
	/* Description - When set, ICMD_QUERY_FW_INFO returns the 
psid
 field. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t fw_info_psid;
	/* Description - When set, ICMD_ACCESS_REGISTER supports the following regis
ters:
NVDA
NVDI
NVIA
NVQC */
	/* 0x0.31 - 0x0.31 */
	u_int8_t nv_access;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If set, wake on phy activity is supported. */
	/* 0x4.0 - 0x4.0 */
	u_int8_t wol_p;
	/* Description - If set, wake on unicast packet is supported. */
	/* 0x4.1 - 0x4.1 */
	u_int8_t wol_u;
	/* Description - If set, wake on multicast packet is supported. */
	/* 0x4.2 - 0x4.2 */
	u_int8_t wol_m;
	/* Description - If set, wake on broadcast packet is supported. */
	/* 0x4.3 - 0x4.3 */
	u_int8_t wol_b;
	/* Description - If set, wake on ARP is supported. */
	/* 0x4.4 - 0x4.4 */
	u_int8_t wol_a;
	/* Description - If set, wake on magic packet is supported. */
	/* 0x4.5 - 0x4.5 */
	u_int8_t wol_g;
	/* Description - If set, wake on secured magic packet is supported. */
	/* 0x4.6 - 0x4.6 */
	u_int8_t wol_s;
	/* Description - If set, reset on magic packet is supported. */
	/* 0x4.8 - 0x4.8 */
	u_int8_t rol_g;
	/* Description - If set, reset on secured magic packet is supported. */
	/* 0x4.9 - 0x4.9 */
	u_int8_t rol_s;
	/* Description - If set, FPGA device is supported by the device. See TBD */
	/* 0x4.10 - 0x4.10 */
	u_int8_t fpga;
	/* Description - Indicate number of */
	/* 0x4.16 - 0x4.31 */
	u_int16_t num_of_diagnostic_counters;
};

/* FW_VERSION */
void connectib_FW_VERSION_pack(const struct connectib_FW_VERSION *ptr_struct, u_int8_t* ptr_buff);
void connectib_FW_VERSION_unpack(struct connectib_FW_VERSION *ptr_struct, const u_int8_t* ptr_buff);
void connectib_FW_VERSION_print(const struct connectib_FW_VERSION *ptr_struct, FILE* file, int indent_level);
int connectib_FW_VERSION_size(void);
#define CONNECTIB_FW_VERSION_SIZE    (0x10)
void connectib_FW_VERSION_dump(const struct connectib_FW_VERSION *ptr_struct, FILE* file);
/* icmd_get_fw_info */
void connectib_icmd_get_fw_info_pack(const struct connectib_icmd_get_fw_info *ptr_struct, u_int8_t* ptr_buff);
void connectib_icmd_get_fw_info_unpack(struct connectib_icmd_get_fw_info *ptr_struct, const u_int8_t* ptr_buff);
void connectib_icmd_get_fw_info_print(const struct connectib_icmd_get_fw_info *ptr_struct, FILE* file, int indent_level);
int connectib_icmd_get_fw_info_size(void);
#define CONNECTIB_ICMD_GET_FW_INFO_SIZE    (0x24)
void connectib_icmd_get_fw_info_dump(const struct connectib_icmd_get_fw_info *ptr_struct, FILE* file);
/* itrace */
void connectib_itrace_pack(const struct connectib_itrace *ptr_struct, u_int8_t* ptr_buff);
void connectib_itrace_unpack(struct connectib_itrace *ptr_struct, const u_int8_t* ptr_buff);
void connectib_itrace_print(const struct connectib_itrace *ptr_struct, FILE* file, int indent_level);
int connectib_itrace_size(void);
#define CONNECTIB_ITRACE_SIZE    (0x10)
void connectib_itrace_dump(const struct connectib_itrace *ptr_struct, FILE* file);
/* itrace_ctrl */
void connectib_itrace_ctrl_pack(const struct connectib_itrace_ctrl *ptr_struct, u_int8_t* ptr_buff);
void connectib_itrace_ctrl_unpack(struct connectib_itrace_ctrl *ptr_struct, const u_int8_t* ptr_buff);
void connectib_itrace_ctrl_print(const struct connectib_itrace_ctrl *ptr_struct, FILE* file, int indent_level);
int connectib_itrace_ctrl_size(void);
#define CONNECTIB_ITRACE_CTRL_SIZE    (0x4)
void connectib_itrace_ctrl_dump(const struct connectib_itrace_ctrl *ptr_struct, FILE* file);
/* icmd_mh_sync */
void connectx4_icmd_mh_sync_pack(const struct connectx4_icmd_mh_sync *ptr_struct, u_int8_t* ptr_buff);
void connectx4_icmd_mh_sync_unpack(struct connectx4_icmd_mh_sync *ptr_struct, const u_int8_t* ptr_buff);
void connectx4_icmd_mh_sync_print(const struct connectx4_icmd_mh_sync *ptr_struct, FILE* file, int indent_level);
int connectx4_icmd_mh_sync_size(void);
#define CONNECTX4_ICMD_MH_SYNC_SIZE    (0x10)
void connectx4_icmd_mh_sync_dump(const struct connectx4_icmd_mh_sync *ptr_struct, FILE* file);
/* icmd_query_cap_general */
void connectx4_icmd_query_cap_general_pack(const struct connectx4_icmd_query_cap_general *ptr_struct, u_int8_t *ptr_buff);
void connectx4_icmd_query_cap_general_unpack(struct connectx4_icmd_query_cap_general *ptr_struct, const u_int8_t *ptr_buff);
void connectx4_icmd_query_cap_general_print(const struct connectx4_icmd_query_cap_general *ptr_struct, FILE *fd, int indent_level);
unsigned int connectx4_icmd_query_cap_general_size(void);
int connectib_icmd_set_port_sniffer_size(void);
void connectib_icmd_set_port_sniffer_unpack(struct connectib_icmd_set_port_sniffer *ptr_struct, const u_int8_t* ptr_buff);
void connectib_icmd_set_port_sniffer_pack(const struct connectib_icmd_set_port_sniffer *ptr_struct, u_int8_t* ptr_buff);
#define CONNECTX4_ICMD_QUERY_CAP_GENERAL_SIZE    (0x8)
void connectx4_icmd_query_cap_general_dump(const struct connectx4_icmd_query_cap_general *ptr_struct, FILE *fd);

void connectx4_public_keys_3_pack(const struct connectx4_public_keys_3 *ptr_struct, u_int8_t *ptr_buff);
void connectx4_public_keys_3_unpack(struct connectx4_public_keys_3 *ptr_struct, const u_int8_t *ptr_buff);
void connectx4_public_keys_3_print(const struct connectx4_public_keys_3 *ptr_struct, FILE *fd, int indent_level);
unsigned int connectx4_public_keys_3_size(void);
#define CONNECTX4_PUBLIC_KEYS_3_SIZE    (0x1100)
void connectx4_public_keys_3_dump(const struct connectx4_public_keys_3 *ptr_struct, FILE *fd);
/* secure_boot_signatures */
void connectx4_secure_boot_signatures_pack(const struct connectx4_secure_boot_signatures *ptr_struct, u_int8_t *ptr_buff);
void connectx4_secure_boot_signatures_unpack(struct connectx4_secure_boot_signatures *ptr_struct, const u_int8_t *ptr_buff);
void connectx4_secure_boot_signatures_print(const struct connectx4_secure_boot_signatures *ptr_struct, FILE *fd, int indent_level);
unsigned int connectx4_secure_boot_signatures_size(void);
#define CONNECTX4_SECURE_BOOT_SIGNATURES_SIZE    (0x600)
void connectx4_secure_boot_signatures_dump(const struct connectx4_secure_boot_signatures *ptr_struct, FILE *fd);
/* file_public_keys_3 */
void connectx4_file_public_keys_3_pack(const struct connectx4_file_public_keys_3 *ptr_struct, u_int8_t *ptr_buff);
void connectx4_file_public_keys_3_unpack(struct connectx4_file_public_keys_3 *ptr_struct, const u_int8_t *ptr_buff);
void connectx4_file_public_keys_3_print(const struct connectx4_file_public_keys_3 *ptr_struct, FILE *fd, int indent_level);
unsigned int connectx4_file_public_keys_3_size(void);
#define CONNECTX4_FILE_PUBLIC_KEYS_3_SIZE    (0x220)
void connectx4_file_public_keys_3_dump(const struct connectx4_file_public_keys_3 *ptr_struct, FILE *fd);
void connectx4_hw_pointers_arava_pack(const struct connectx4_hw_pointers_arava *ptr_struct, u_int8_t *ptr_buff);
void connectx4_hw_pointers_arava_unpack(struct connectx4_hw_pointers_arava *ptr_struct, const u_int8_t *ptr_buff);
void connectx4_hw_pointers_arava_print(const struct connectx4_hw_pointers_arava *ptr_struct, FILE *fd, int indent_level);
unsigned int connectx4_hw_pointers_arava_size(void);
#define CONNECTX4_HW_POINTERS_ARAVA_SIZE    (0x80)
void connectx4_hw_pointers_arava_dump(const struct connectx4_hw_pointers_arava *ptr_struct, FILE *fd);
unsigned int icmd_hca_icmd_query_cap_general_size(void);
#define ICMD_HCA_ICMD_QUERY_CAP_GENERAL_SIZE    (0x8)
void icmd_hca_icmd_query_cap_general_pack(const struct icmd_hca_icmd_query_cap_general *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_query_cap_general_unpack(struct icmd_hca_icmd_query_cap_general *ptr_struct, const u_int8_t *ptr_buff);

#define CONNECTX5_NV_DATA_SIZE    (0x10000)

#ifdef __cplusplus
}
#endif
#endif
