
/* Copyright (c) 2013-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

 

/***
         *** This file was generated at "2023-01-17 10:38:00"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/tools_open/mlxconfig_4th_gen.adb --file-prefix mlxconfig_4th_gen --prefix mlxconfig_4th_gen_ --no-adb-utils
         ***/
#ifndef MLXCONFIG_4TH_GEN_LAYOUTS_H
#define MLXCONFIG_4TH_GEN_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 8 */
struct mlxconfig_4th_gen_nv_hdr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tlv type */
	/* 0x0.0 - 0x0.15 */
	u_int16_t type;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - size of tlv data in dwords (not including header) */
	/* 0x0.18 - 0x0.29 */
	u_int16_t length;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type Modifier. E.G.: Port number when the config is port related */
	/* 0x4.16 - 0x4.23 */
	u_int8_t type_mod;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Shadow: i.e if set the Fw will not update the tlv immediately but wait for a command */
	/* 0x4.24 - 0x4.24 */
	u_int8_t shadow;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Pad count: for non dword alligned tlvs */
	/* 0x4.25 - 0x4.26 */
	u_int8_t pad_cnt;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Data version can be set by caller or left as 0. */
	/* 0x4.28 - 0x4.31 */
	u_int8_t version;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_bar_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Base 2 log of the size of the physical functions first BAR, in MBs. E.g. for 8MB the value is 3. */
	/* 0x0.0 - 0x0.31 */
	u_int32_t log_uar_bar_size;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VLAN ID for network boot. */
	/* 0x0.0 - 0x0.11 */
	u_int16_t boot_vlan;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0  None  disable legacy boot.
1  PXE (DHCP/TFTP boot).
2  iSCSI
3  PXE + iSCSI
4-255  Reserved
 */
	/* 0x0.16 - 0x0.23 */
	u_int8_t legacy_boot_protocol;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of retries to attempt in case of boot failure.
7 indicate indefinite retries.
 */
	/* 0x0.24 - 0x0.26 */
	u_int8_t boot_retry_conut;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1  Enable VLAN mode for network boot. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t boot_vlan_en;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0  disable boot option ROM: disables installation of the UNDI/16 driver. The option ROM is still required to expose CLP, UEFI and so on.
1  enable boot option ROM
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t boot_option_rom_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_boot_settings_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Select which IP protocol version will be used by flexboot */
	/* 0x0.8 - 0x0.9 */
	u_int8_t ip_ver;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_infiniband_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - P_key to be used by PXE boot. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t boot_pkey;
};

/* Description -   */
/* Size in bytes - 256 */
struct mlxconfig_4th_gen_mnva {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct mlxconfig_4th_gen_nv_hdr nv_hdr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.24 - 0x88.23 */
	u_int8_t data[128];
};

/* Description -   */
/* Size in bytes - 8 */
struct mlxconfig_4th_gen_mnvia {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct mlxconfig_4th_gen_nv_hdr nv_hdr;
};

/* Description -   */
/* Size in bytes - 32 */
struct mlxconfig_4th_gen_nv_cx3_global_conf {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When TRUE, driver will be indicated to expose internal clock directly to user space applications */
	/* 0x0.27 - 0x0.27 */
	u_int8_t clock_map_to_user;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Defines the Port PHY parameters mode. 0x0: DEVICE_DEFAULT, 0x1: LEGACY, 0x2: ADVANCED */
	/* 0x0.28 - 0x0.29 */
	u_int8_t phy_param_mode;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Force vlan steering, ignoring driver configuraiton. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t steer_force_vlan;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, IEE1588 (PTP) HW timestamping capability is reported to the device driver. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t cq_timestamp;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_preboot_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VLAN ID for network boot. */
	/* 0x0.0 - 0x0.11 */
	u_int16_t boot_vlan;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0  None disable legacy boot.
1  PXE (DHCP/TFTP boot).
2  iSCSI

3  PXE + iSCSI
4-255  Reserved
 */
	/* 0x0.16 - 0x0.23 */
	u_int8_t legacy_boot_protocol;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of retries to attempt in case of boot failure.
7 indicate indefinite retries.
 */
	/* 0x0.24 - 0x0.26 */
	u_int8_t boot_retry_count;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 Enable VLAN mode for network boot */
	/* 0x0.30 - 0x0.30 */
	u_int8_t boot_vlan_en;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 disable boot option ROM: disables installation of the UNDI/16 driver. The option ROM is still required to expose CLP, UEFI and so on.
1 enable boot option ROM
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t boot_option_rom_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_sriov {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of VFs that can be supported. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t total_vfs;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 when SRIOV is enabled: SRIOV capability will appear on the PCI configuration header. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct mlxconfig_4th_gen_vpi_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Network link type:
0 - Reserved
1 - InfiniBand
2 - Ethernet
 */
	/* 0x0.0 - 0x0.1 */
	u_int8_t network_link_type;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - Reserved
1 - Infiniband
2 - Ethernet
Valid for CX4 and above only
when VPI network link type is selcted this field determines
the default link type when no cable is connected */
	/* 0x0.2 - 0x0.3 */
	u_int8_t default_link_type;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.4 - 0x0.5 */
	u_int8_t phy_type;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.6 - 0x0.7 */
	u_int8_t xfi_mode;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.8 - 0x0.8 */
	u_int8_t force_mode;
};

/* Description -   */
/* Size in bytes - 8 */
struct mlxconfig_4th_gen_wol {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on secure on password magic packet */
	/* 0x0.9 - 0x0.9 */
	u_int8_t en_wol_psswd_magic;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on magic packet */
	/* 0x0.10 - 0x0.10 */
	u_int8_t en_wol_magic;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on ARP */
	/* 0x0.11 - 0x0.11 */
	u_int8_t en_wol_arp;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on broadcast message */
	/* 0x0.12 - 0x0.12 */
	u_int8_t en_wol_bc;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on multicast message */
	/* 0x0.13 - 0x0.13 */
	u_int8_t en_wol_mc;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on unicast message */
	/* 0x0.14 - 0x0.14 */
	u_int8_t en_wol_uc;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on PHY activity */
	/* 0x0.15 - 0x0.15 */
	u_int8_t en_wol_phy;
};

/* Description -   */
/* Size in bytes - 256 */
union mlxconfig_4th_gen_mlxconfig_nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	struct mlxconfig_4th_gen_mnva mnva;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct mlxconfig_4th_gen_mnvia mnvia;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct mlxconfig_4th_gen_wol wol;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_infiniband_boot_settings infiniband_boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_boot_settings boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_preboot_boot_settings preboot_boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_sriov sriov;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_bar_size bar_size;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_vpi_settings vpi_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct mlxconfig_4th_gen_boot_settings_ext boot_settings_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct mlxconfig_4th_gen_nv_cx3_global_conf nv_cx3_global_conf;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* nv_hdr */
void mlxconfig_4th_gen_nv_hdr_pack(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_nv_hdr_unpack(struct mlxconfig_4th_gen_nv_hdr *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_nv_hdr_print(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_nv_hdr_size(void);
#define MLXCONFIG_4TH_GEN_NV_HDR_SIZE    (0x8)
void mlxconfig_4th_gen_nv_hdr_dump(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, FILE *fd);
/* bar_size */
void mlxconfig_4th_gen_bar_size_pack(const struct mlxconfig_4th_gen_bar_size *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_bar_size_unpack(struct mlxconfig_4th_gen_bar_size *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_bar_size_print(const struct mlxconfig_4th_gen_bar_size *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_bar_size_size(void);
#define MLXCONFIG_4TH_GEN_BAR_SIZE_SIZE    (0x4)
void mlxconfig_4th_gen_bar_size_dump(const struct mlxconfig_4th_gen_bar_size *ptr_struct, FILE *fd);
/* boot_settings */
void mlxconfig_4th_gen_boot_settings_pack(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_boot_settings_unpack(struct mlxconfig_4th_gen_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_boot_settings_print(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_boot_settings_size(void);
#define MLXCONFIG_4TH_GEN_BOOT_SETTINGS_SIZE    (0x4)
void mlxconfig_4th_gen_boot_settings_dump(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, FILE *fd);
/* boot_settings_ext */
void mlxconfig_4th_gen_boot_settings_ext_pack(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_boot_settings_ext_unpack(struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_boot_settings_ext_print(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_boot_settings_ext_size(void);
#define MLXCONFIG_4TH_GEN_BOOT_SETTINGS_EXT_SIZE    (0x4)
void mlxconfig_4th_gen_boot_settings_ext_dump(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, FILE *fd);
/* infiniband_boot_settings */
void mlxconfig_4th_gen_infiniband_boot_settings_pack(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_infiniband_boot_settings_unpack(struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_infiniband_boot_settings_print(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_infiniband_boot_settings_size(void);
#define MLXCONFIG_4TH_GEN_INFINIBAND_BOOT_SETTINGS_SIZE    (0x4)
void mlxconfig_4th_gen_infiniband_boot_settings_dump(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, FILE *fd);
/* mnva */
void mlxconfig_4th_gen_mnva_pack(const struct mlxconfig_4th_gen_mnva *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mnva_unpack(struct mlxconfig_4th_gen_mnva *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mnva_print(const struct mlxconfig_4th_gen_mnva *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_mnva_size(void);
#define MLXCONFIG_4TH_GEN_MNVA_SIZE    (0x100)
void mlxconfig_4th_gen_mnva_dump(const struct mlxconfig_4th_gen_mnva *ptr_struct, FILE *fd);
/* mnvia */
void mlxconfig_4th_gen_mnvia_pack(const struct mlxconfig_4th_gen_mnvia *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mnvia_unpack(struct mlxconfig_4th_gen_mnvia *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mnvia_print(const struct mlxconfig_4th_gen_mnvia *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_mnvia_size(void);
#define MLXCONFIG_4TH_GEN_MNVIA_SIZE    (0x8)
void mlxconfig_4th_gen_mnvia_dump(const struct mlxconfig_4th_gen_mnvia *ptr_struct, FILE *fd);
/* nv_cx3_global_conf */
void mlxconfig_4th_gen_nv_cx3_global_conf_pack(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_nv_cx3_global_conf_unpack(struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_nv_cx3_global_conf_print(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_nv_cx3_global_conf_size(void);
#define MLXCONFIG_4TH_GEN_NV_CX3_GLOBAL_CONF_SIZE    (0x20)
void mlxconfig_4th_gen_nv_cx3_global_conf_dump(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, FILE *fd);
/* preboot_boot_settings */
void mlxconfig_4th_gen_preboot_boot_settings_pack(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_preboot_boot_settings_unpack(struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_preboot_boot_settings_print(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_preboot_boot_settings_size(void);
#define MLXCONFIG_4TH_GEN_PREBOOT_BOOT_SETTINGS_SIZE    (0x4)
void mlxconfig_4th_gen_preboot_boot_settings_dump(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, FILE *fd);
/* sriov */
void mlxconfig_4th_gen_sriov_pack(const struct mlxconfig_4th_gen_sriov *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_sriov_unpack(struct mlxconfig_4th_gen_sriov *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_sriov_print(const struct mlxconfig_4th_gen_sriov *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_sriov_size(void);
#define MLXCONFIG_4TH_GEN_SRIOV_SIZE    (0x4)
void mlxconfig_4th_gen_sriov_dump(const struct mlxconfig_4th_gen_sriov *ptr_struct, FILE *fd);
/* vpi_settings */
void mlxconfig_4th_gen_vpi_settings_pack(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_vpi_settings_unpack(struct mlxconfig_4th_gen_vpi_settings *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_vpi_settings_print(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_vpi_settings_size(void);
#define MLXCONFIG_4TH_GEN_VPI_SETTINGS_SIZE    (0x4)
void mlxconfig_4th_gen_vpi_settings_dump(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, FILE *fd);
/* wol */
void mlxconfig_4th_gen_wol_pack(const struct mlxconfig_4th_gen_wol *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_wol_unpack(struct mlxconfig_4th_gen_wol *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_wol_print(const struct mlxconfig_4th_gen_wol *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_wol_size(void);
#define MLXCONFIG_4TH_GEN_WOL_SIZE    (0x8)
void mlxconfig_4th_gen_wol_dump(const struct mlxconfig_4th_gen_wol *ptr_struct, FILE *fd);
/* mlxconfig_nodes */
void mlxconfig_4th_gen_mlxconfig_nodes_pack(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mlxconfig_nodes_unpack(union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, const u_int8_t *ptr_buff);
void mlxconfig_4th_gen_mlxconfig_nodes_print(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int mlxconfig_4th_gen_mlxconfig_nodes_size(void);
#define MLXCONFIG_4TH_GEN_MLXCONFIG_NODES_SIZE    (0x100)
void mlxconfig_4th_gen_mlxconfig_nodes_dump(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // MLXCONFIG_4TH_GEN_LAYOUTS_H
