
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2010-2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
 

/***
 *** This file was generated at "2014-07-08 14:00:09"
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
/* Size in bytes - 4 */
struct tools_open_bar_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Base 2 log of the size of the physical functions first BAR, in MBs. E.g. for 8MB the value is 3. */
	/* 0.0 - 4.31 */
	 u_int32_t log_uar_bar_size;
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
/* Size in bytes - 256 */
union tools_open_nv_cfg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 8.31 */
	 struct tools_open_wol wol;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_vpi_settings vpi_settings;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_bar_size bar_size;
	/* Description -  */
	/* 0.0 - 4.31 */
	 struct tools_open_sriov sriov;
};

/* Description -   */
/* Size in bytes - 1048576 */
union tools_open_tools_open {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Non-Volatile Cfg Tlvs */
	/* 0.0 - 256.31 */
	 union tools_open_nv_cfg NVConfig;
	/* Description - Misc NV Registers, this is temporary untill we integrate with fw db */
	/* 0.0 - 256.31 */
	 union tools_open_mnv_cfg MNV_Reg;
	/* Description - Register for accessing FW managed external PHY */
	/* 0.0 - 264.31 */
	 union tools_open_phy_reg Phy_Reg;
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
/* sriov */
void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t* ptr_buff);
void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE* file, int indent_level);
int tools_open_sriov_size();
#define TOOLS_OPEN_SRIOV_SIZE    (0x4)
void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE* file);
/* bar_size */
void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t* ptr_buff);
void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE* file, int indent_level);
int tools_open_bar_size_size();
#define TOOLS_OPEN_BAR_SIZE_SIZE    (0x4)
void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE* file);
/* vpi_settings */
void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t* ptr_buff);
void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE* file, int indent_level);
int tools_open_vpi_settings_size();
#define TOOLS_OPEN_VPI_SETTINGS_SIZE    (0x4)
void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE* file);
/* wol */
void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t* ptr_buff);
void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t* ptr_buff);
void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE* file, int indent_level);
int tools_open_wol_size();
#define TOOLS_OPEN_WOL_SIZE    (0x8)
void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE* file);
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
