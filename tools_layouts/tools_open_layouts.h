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
 *
 */

/***
 *** This file was generated at "2014-11-12 13:19:54"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_
 ***/
#ifndef TOOLS_OPEN_LAYOUTS_H
#define TOOLS_OPEN_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"/* Description -   */
/* Size in bytes - 4 */
struct tools_open_pmdio_addr_data {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Data (Clause 22) / Address/Data (Clause 45) */
	/* 0.0 - 0.15 */
	 u_int16_t data;
	/* Description - Address (Clause 45)
This field is only valid for Address + Read and Address + Write operations, providing the address. For other Clause 45 operations the data field provides the address when appropriate.
 */
	/* 0.16 - 4.31 */
	 u_int16_t addr;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_mnv_hdr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tlv type */
	/* 0.0 - 0.15 */
	 u_int16_t type;
	/* Description - size of tlv data in dwords (not including header) */
	/* 0.18 - 0.29 */
	 u_int16_t length;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type Modifier. E.G.: Port number when the config is port related */
	/* 4.16 - 4.23 */
	 u_int8_t type_mod;
	/* Description - Shadow: i.e if set the Fw will not update the tlv immediately but wait for a command */
	/* 4.24 - 4.24 */
	 u_int8_t shadow;
	/* Description - Pad count: for non dword alligned tlvs */
	/* 4.25 - 4.26 */
	 u_int8_t pad_cnt;
	/* Description - Data version can be set by caller or left as 0. */
	/* 4.28 - 8.31 */
	 u_int8_t version;
};

/* Description -   */
/* Size in bytes - 264 */
struct tools_open_pmdio {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 000 - NOP
001 - Address (reserved for Clause 22)
010 - Read
011 - Write
100 - Post Read Increment Address (reserved for Clause 22)
110 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
111 - Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22)
 */
	/* 0.0 - 0.2 */
	 u_int8_t operation;
	/* Description - MDIO I/F definition:
00 - Clause 22
01 - Clause 45
 */
	/* 0.8 - 0.9 */
	 u_int8_t clause;
	/* Description - Local port number */
	/* 0.16 - 0.23 */
	 u_int8_t local_port;
	/* Description - Lock bit. Setting this bit will lock the access to port's MDIO
Used for operations that requires continuous MDIO accesses.

In order to guarantee atomicity of some operations, the port MDIO interface can be locked to a specific interface.
When the lock bit is set, no MDIO accesses through another interface (FW/driver/tools) are allowed on the port.
An attempt to set the lock bit while it is locked by another interface should return a RESOURCE/_BUSY status.
 */
	/* 0.31 - 4.31 */
	 u_int8_t lock;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reg Address (Clause 22) / MDIO Manageable Device address (Clause 45) */
	/* 4.0 - 4.4 */
	 u_int8_t reg_adr_mmd;
	/* Description - Index of last entry in the operations list. 0 means single operation (backward compatible).
Valid values are 0..63
 */
	/* 4.8 - 4.15 */
	 u_int8_t last_op_idx;
	/* Description - Number of operations actually executed by FW. Driver write 0 to this field. FW increment the field with any execution of an entry in the operations list. */
	/* 4.16 - 4.23 */
	 u_int8_t num_ops_done;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - addr/data entry */
	/* 8.0 - 264.31 */
	 struct tools_open_pmdio_addr_data mdio_trans[64];
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_pmdic {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number */
	/* 0.16 - 0.23 */
	 u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit 0 - NOP
Bit 1 - Address (reserved for Clause 22)
Bit 2 - Read
Bit 3 - Write
Bit 4 - Post Read Increment Address (reserved for Clause 22)
Bit 6 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
Bit 7- Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22)
 */
	/* 4.0 - 4.7 */
	 u_int8_t operation_cap;
	/* Description - MDIO I/F definition:
00 - Clause 22
01 - Clause 45
 */
	/* 4.24 - 4.25 */
	 u_int8_t clause;
	/* Description - MDIO present:
00 - MDIO not present
01 - External MDIO present
 */
	/* 4.30 - 8.31 */
	 u_int8_t mdio_preset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bit 0 External Phy FW master
Used for external Phy FW burning. When set, the MDIO I/F is used for an external phy FW burn
 */
	/* 8.0 - 8.7 */
	 u_int8_t misc_cap;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_mnvia {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_mnv_hdr mnv_hdr;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_mnvi {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_mnv_hdr mnv_hdr;
};

/* Description -   */
/* Size in bytes - 256 */
struct tools_open_mnva {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_mnv_hdr mnv_hdr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.24 - 136.23 */
	 u_int8_t data[128];
};

/* Description -   */
/* Size in bytes - 28 */
struct tools_open_query_def_params_per_port {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.24 - 4.31 */
	 u_int8_t fw_default_config_payload_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 4.11 */
	 u_int16_t boot_vlan;
	/* Description -  */
	/* 4.16 - 4.19 */
	 u_int8_t boot_protocol;
	/* Description -  */
	/* 4.20 - 4.23 */
	 u_int8_t boot_retry_cnt;
	/* Description -  */
	/* 4.25 - 4.26 */
	 u_int8_t network_link_type;
	/* Description -  */
	/* 4.27 - 4.27 */
	 u_int8_t en_wol_magic;
	/* Description -  */
	/* 4.28 - 4.28 */
	 u_int8_t boot_vlan_en;
	/* Description -  */
	/* 4.29 - 4.29 */
	 u_int8_t boot_option_rom_en;
	/* Description -  */
	/* 4.30 - 4.30 */
	 u_int8_t pprx;
	/* Description -  */
	/* 4.31 - 8.31 */
	 u_int8_t pptx;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.0 - 8.15 */
	 u_int16_t boot_pkey;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 12.22 - 12.23 */
	 u_int8_t iscsi_boot_to_target;
	/* Description -  */
	/* 12.26 - 12.26 */
	 u_int8_t iscsi_vlan_en;
	/* Description -  */
	/* 12.27 - 12.27 */
	 u_int8_t iscsi_tcp_timestamps_en;
	/* Description -  */
	/* 12.28 - 12.28 */
	 u_int8_t iscsi_chap_mutual_auth_en;
	/* Description -  */
	/* 12.29 - 12.29 */
	 u_int8_t iscsi_chap_auth_en;
	/* Description -  */
	/* 12.30 - 12.30 */
	 u_int8_t iscsi_dhcp_params_en;
	/* Description -  */
	/* 12.31 - 16.31 */
	 u_int8_t iscsi_ipv4_dhcp_en;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 16.0 - 16.7 */
	 u_int8_t iscsi_lun_busy_retry_cnt;
	/* Description -  */
	/* 16.8 - 16.15 */
	 u_int8_t iscsi_link_up_delay_time;
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_query_def_params_global {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.24 - 4.31 */
	 u_int8_t fw_default_config_payload_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - default number of virtual functions */
	/* 4.0 - 4.7 */
	 u_int8_t num_vfs;
	/* Description - default uar bar size (log2 format) */
	/* 4.8 - 4.11 */
	 u_int8_t uar_bar_size;
	/* Description - maximum value allowed for the uar bar size (log2 base) */
	/* 4.12 - 4.15 */
	 u_int8_t max_uar_bar_size;
	/* Description - default value of sriov (enabled or disabled) */
	/* 4.31 - 8.31 */
	 u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 264 */
union tools_open_phy_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 12.31 */
	 struct tools_open_pmdic pmdic;
	/* Description -  */
	/* 0.0 - 264.31 */
	 struct tools_open_pmdio pmdio;
};

/* Description -   */
/* Size in bytes - 256 */
union tools_open_mnv_cfg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 256.31 */
	 struct tools_open_mnva mnva;
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_mnvi mnvi;
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_mnvia mnvia;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_vpi_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Default link type:
0  InfiniBand
1  Ethernet
 */
	/* 0.0 - 0.1 */
	 u_int8_t network_link_type;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_bar_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Base 2 log of the size of the physical functions first BAR, in MBs. E.g. for 8MB the value is 3. */
	/* 0.0 - 4.31 */
	 u_int32_t log_uar_bar_size;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_sriov {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of VFs that can be supported. */
	/* 0.0 - 0.15 */
	 u_int16_t total_vfs;
	/* Description - 1 when SRIOV is enabled: SRIOV capability will appear on the PCI configuration header. */
	/* 0.31 - 4.31 */
	 u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_wol {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on secure on password magic packet */
	/* 0.9 - 0.9 */
	 u_int8_t en_wol_psswd_magic;
	/* Description - Enable Wake on magic packet */
	/* 0.10 - 0.10 */
	 u_int8_t en_wol_magic;
	/* Description - Enable Wake on ARP */
	/* 0.11 - 0.11 */
	 u_int8_t en_wol_arp;
	/* Description - Enable Wake on broadcast message */
	/* 0.12 - 0.12 */
	 u_int8_t en_wol_bc;
	/* Description - Enable Wake on multicast message */
	/* 0.13 - 0.13 */
	 u_int8_t en_wol_mc;
	/* Description - Enable Wake on unicast message */
	/* 0.14 - 0.14 */
	 u_int8_t en_wol_uc;
	/* Description - Enable Wake on PHY activity */
	/* 0.15 - 0.15 */
	 u_int8_t en_wol_phy;
};

/* Description -   */
/* Size in bytes - 264 */
union tools_open_hcr_cmds {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 20.31 */
	 struct tools_open_query_def_params_global query_def_params_global;
	/* Description -  */
	/* 0.0 - 28.31 */
	 struct tools_open_query_def_params_per_port query_def_params_per_port;
};

/* Description -   */
/* Size in bytes - 512 */
union tools_open_access_registers {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Misc NV Registers, this is temporary untill we integrate with fw db */
	/* 0.0 - 256.31 */
	 union tools_open_mnv_cfg MNVReg;
	/* Description - Register for accessing FW managed external PHY */
	/* 0.0 - 264.31 */
	 union tools_open_phy_reg PhyReg;
};

/* Description -   */
/* Size in bytes - 256 */
union tools_open_nv_cfg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_wol wol;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_sriov sriov;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_bar_size bar_size;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_vpi_settings vpi_settings;
};

/* Description -   */
/* Size in bytes - 1048576 */
union tools_open_tools_open {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Non-Volatile Cfg Tlvs */
	/* 0.0 - 256.31 */
	 union tools_open_nv_cfg NVConfig;
	/* Description - various registers in specific use by the tools */
	/* 0.0 - 512.31 */
	 union tools_open_access_registers AceessRegisters;
	/* Description - Tools HCR commands structs */
	/* 0.0 - 264.31 */
	 union tools_open_hcr_cmds HcrCmds;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 4.31 */
	 u_int32_t hi;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 8.31 */
	 u_int32_t lo;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* pmdio_addr_data */
void tools_open_pmdio_addr_data_pack(const struct tools_open_pmdio_addr_data *ptr_struct, u_int8_t* ptr_buff);
void tools_open_pmdio_addr_data_unpack(struct tools_open_pmdio_addr_data *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_pmdio_addr_data_print(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file, int indent_level);
int tools_open_pmdio_addr_data_size();
#define TOOLS_OPEN_PMDIO_ADDR_DATA_SIZE    (0x4)
void tools_open_pmdio_addr_data_dump(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file);
/* mnv_hdr */
void tools_open_mnv_hdr_pack(const struct tools_open_mnv_hdr *ptr_struct, u_int8_t* ptr_buff);
void tools_open_mnv_hdr_unpack(struct tools_open_mnv_hdr *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_mnv_hdr_print(const struct tools_open_mnv_hdr *ptr_struct, FILE* file, int indent_level);
int tools_open_mnv_hdr_size();
#define TOOLS_OPEN_MNV_HDR_SIZE    (0x8)
void tools_open_mnv_hdr_dump(const struct tools_open_mnv_hdr *ptr_struct, FILE* file);
/* pmdio */
void tools_open_pmdio_pack(const struct tools_open_pmdio *ptr_struct, u_int8_t* ptr_buff);
void tools_open_pmdio_unpack(struct tools_open_pmdio *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_pmdio_print(const struct tools_open_pmdio *ptr_struct, FILE* file, int indent_level);
int tools_open_pmdio_size();
#define TOOLS_OPEN_PMDIO_SIZE    (0x108)
void tools_open_pmdio_dump(const struct tools_open_pmdio *ptr_struct, FILE* file);
/* pmdic */
void tools_open_pmdic_pack(const struct tools_open_pmdic *ptr_struct, u_int8_t* ptr_buff);
void tools_open_pmdic_unpack(struct tools_open_pmdic *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_pmdic_print(const struct tools_open_pmdic *ptr_struct, FILE* file, int indent_level);
int tools_open_pmdic_size();
#define TOOLS_OPEN_PMDIC_SIZE    (0xc)
void tools_open_pmdic_dump(const struct tools_open_pmdic *ptr_struct, FILE* file);
/* mnvia */
void tools_open_mnvia_pack(const struct tools_open_mnvia *ptr_struct, u_int8_t* ptr_buff);
void tools_open_mnvia_unpack(struct tools_open_mnvia *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_mnvia_print(const struct tools_open_mnvia *ptr_struct, FILE* file, int indent_level);
int tools_open_mnvia_size();
#define TOOLS_OPEN_MNVIA_SIZE    (0x8)
void tools_open_mnvia_dump(const struct tools_open_mnvia *ptr_struct, FILE* file);
/* mnvi */
void tools_open_mnvi_pack(const struct tools_open_mnvi *ptr_struct, u_int8_t* ptr_buff);
void tools_open_mnvi_unpack(struct tools_open_mnvi *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_mnvi_print(const struct tools_open_mnvi *ptr_struct, FILE* file, int indent_level);
int tools_open_mnvi_size();
#define TOOLS_OPEN_MNVI_SIZE    (0x8)
void tools_open_mnvi_dump(const struct tools_open_mnvi *ptr_struct, FILE* file);
/* mnva */
void tools_open_mnva_pack(const struct tools_open_mnva *ptr_struct, u_int8_t* ptr_buff);
void tools_open_mnva_unpack(struct tools_open_mnva *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_mnva_print(const struct tools_open_mnva *ptr_struct, FILE* file, int indent_level);
int tools_open_mnva_size();
#define TOOLS_OPEN_MNVA_SIZE    (0x100)
void tools_open_mnva_dump(const struct tools_open_mnva *ptr_struct, FILE* file);
/* query_def_params_per_port */
void tools_open_query_def_params_per_port_pack(const struct tools_open_query_def_params_per_port *ptr_struct, u_int8_t* ptr_buff);
void tools_open_query_def_params_per_port_unpack(struct tools_open_query_def_params_per_port *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_query_def_params_per_port_print(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file, int indent_level);
int tools_open_query_def_params_per_port_size();
#define TOOLS_OPEN_QUERY_DEF_PARAMS_PER_PORT_SIZE    (0x1c)
void tools_open_query_def_params_per_port_dump(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file);
/* query_def_params_global */
void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t* ptr_buff);
void tools_open_query_def_params_global_unpack(struct tools_open_query_def_params_global *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_query_def_params_global_print(const struct tools_open_query_def_params_global *ptr_struct, FILE* file, int indent_level);
int tools_open_query_def_params_global_size();
#define TOOLS_OPEN_QUERY_DEF_PARAMS_GLOBAL_SIZE    (0x14)
void tools_open_query_def_params_global_dump(const struct tools_open_query_def_params_global *ptr_struct, FILE* file);
/* phy_reg */
void tools_open_phy_reg_pack(const union tools_open_phy_reg *ptr_struct, u_int8_t* ptr_buff);
void tools_open_phy_reg_unpack(union tools_open_phy_reg *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_phy_reg_print(const union tools_open_phy_reg *ptr_struct, FILE* file, int indent_level);
int tools_open_phy_reg_size();
#define TOOLS_OPEN_PHY_REG_SIZE    (0x108)
void tools_open_phy_reg_dump(const union tools_open_phy_reg *ptr_struct, FILE* file);
/* mnv_cfg */
void tools_open_mnv_cfg_pack(const union tools_open_mnv_cfg *ptr_struct, u_int8_t* ptr_buff);
void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE* file, int indent_level);
int tools_open_mnv_cfg_size();
#define TOOLS_OPEN_MNV_CFG_SIZE    (0x100)
void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE* file);
/* vpi_settings */
void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t* ptr_buff);
void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE* file, int indent_level);
int tools_open_vpi_settings_size();
#define TOOLS_OPEN_VPI_SETTINGS_SIZE    (0x4)
void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE* file);
/* bar_size */
void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t* ptr_buff);
void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE* file, int indent_level);
int tools_open_bar_size_size();
#define TOOLS_OPEN_BAR_SIZE_SIZE    (0x4)
void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE* file);
/* sriov */
void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t* ptr_buff);
void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE* file, int indent_level);
int tools_open_sriov_size();
#define TOOLS_OPEN_SRIOV_SIZE    (0x4)
void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE* file);
/* wol */
void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t* ptr_buff);
void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE* file, int indent_level);
int tools_open_wol_size();
#define TOOLS_OPEN_WOL_SIZE    (0x8)
void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE* file);
/* hcr_cmds */
void tools_open_hcr_cmds_pack(const union tools_open_hcr_cmds *ptr_struct, u_int8_t* ptr_buff);
void tools_open_hcr_cmds_unpack(union tools_open_hcr_cmds *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_hcr_cmds_print(const union tools_open_hcr_cmds *ptr_struct, FILE* file, int indent_level);
int tools_open_hcr_cmds_size();
#define TOOLS_OPEN_HCR_CMDS_SIZE    (0x108)
void tools_open_hcr_cmds_dump(const union tools_open_hcr_cmds *ptr_struct, FILE* file);
/* access_registers */
void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t* ptr_buff);
void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE* file, int indent_level);
int tools_open_access_registers_size();
#define TOOLS_OPEN_ACCESS_REGISTERS_SIZE    (0x200)
void tools_open_access_registers_dump(const union tools_open_access_registers *ptr_struct, FILE* file);
/* nv_cfg */
void tools_open_nv_cfg_pack(const union tools_open_nv_cfg *ptr_struct, u_int8_t* ptr_buff);
void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE* file, int indent_level);
int tools_open_nv_cfg_size();
#define TOOLS_OPEN_NV_CFG_SIZE    (0x100)
void tools_open_nv_cfg_dump(const union tools_open_nv_cfg *ptr_struct, FILE* file);
/* tools_open */
void tools_open_tools_open_pack(const union tools_open_tools_open *ptr_struct, u_int8_t* ptr_buff);
void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_tools_open_print(const union tools_open_tools_open *ptr_struct, FILE* file, int indent_level);
int tools_open_tools_open_size();
#define TOOLS_OPEN_TOOLS_OPEN_SIZE    (0x100000)
void tools_open_tools_open_dump(const union tools_open_tools_open *ptr_struct, FILE* file);
/* uint64 */
void tools_open_uint64_pack(const struct tools_open_uint64 *ptr_struct, u_int8_t* ptr_buff);
void tools_open_uint64_unpack(struct tools_open_uint64 *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_uint64_print(const struct tools_open_uint64 *ptr_struct, FILE* file, int indent_level);
int tools_open_uint64_size();
#define TOOLS_OPEN_UINT64_SIZE    (0x8)
void tools_open_uint64_dump(const struct tools_open_uint64 *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // TOOLS_OPEN_LAYOUTS_H
